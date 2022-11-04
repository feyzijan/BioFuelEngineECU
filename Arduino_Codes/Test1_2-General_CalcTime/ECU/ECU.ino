//COM7 Mega
// Set-up Pins
#define iat_pin 2
#define ect_pin 3
#define map_pin 4
#define lambda_pin 5
#define fuel_temp_pin 6
#define pcb_temp_pin 7
#define ipg_pin 8
#define cpg_pin 40
#define pin_pcb 15


// Set-up Variables and constants
// - Air flow calculation
int IAT;
int MAP;
float m_air;
int N = 3000;
const float vol_eff = 0.7;
const int v_eng = 599; // *10e-6
const int n_cyl = 4;
const int R=287;

// - Fuel mass and time calculation
float Lambda;


const int q_inj = 875; // 10e-8
const int density_fuel = 779;
const float m_fuel_rate_possible = 1704; // mg/s
const int AFR_stoc = 9.75;

const float valve_angle = 1.134; // 65 degree in radians

float m_fuel;
float t_fuel;
float t_valve;


// Power and efficiency calculation
const int N_steady=3000;
const float w_steady = 314.159;
const int T = 35;
const int P_steady = 11000;
const int NCV = 3; // *10e7
float thermal_eff;

//IPG CPG
float crankshaft_pos;
float camshaft_pos;
float n_ipg;
float n_cpg;


// Safety and Side functions
int ECT;
int Fuel_T;
int PCB_temp;



void setup() {
  // put your setussssp code here, to run once:
  Serial.begin(9600);
  while (!Serial); 
  
  pinMode(2,INPUT);
  pinMode(3,INPUT);
  pinMode(4,INPUT);
  pinMode(5,INPUT);
  pinMode(6,INPUT);
  pinMode(7,INPUT);
  pinMode(8,INPUT);
  pinMode(9,INPUT);
  Serial.println("Started program");
  read_all_sensors();
  display_sensors();
}

/* Function to convert read sensor values to actual values
*TODO: Cant read pcb temp input for some reason
*/

void read_sensors() {
  IAT = pulseIn(iat_pin, HIGH)/2040.0*5.0*8.38 + 273.15 + 48.935 ;
  //T= 8.38 Vıat + 48.935 + 273.15
  MAP = pulseIn(map_pin, HIGH)/2040.0*5.0/2.91*100000;
  //P = V/2.91 * 10^5     -----2.91: 10e5Pa, 0:0
  //ECT = pulseIn(ect_pin, HIGH)/2040.0*5.0*26.155*-1 + 145.29 + 273.15;
  // T = -26.155V + 145.29 + 273.15
  //Lambda = pulseIn(lambda_pin, HIGH)/2040.0*5.0*15.04/5.0 + 7.35;
  // AFR = V*15.04/5+7.35
  //Fuel_T =pulseIn(fuel_temp_pin, HIGH)/2040.0*5.0*20 + 273.15;
  // Assume: 273.15 + 20*V
  //PCB_temp = pulseIn(pcb_temp_pin, HIGH, 200);//*250.0/204.0/1024.0
  // K = rawvoltage/1024.0 * 5000 / 10 - pcb_temp_pin
  //n_ipg = pulseIn(ipg_pin, HIGH, 500);
  //n_cpg = pulseIn(cpg_pin, HIGH, 500);
  //int temp = analogRead(pin_pcb);
  //PCB_temp = temp* 25.0 / 2.98 * 5.0 / 1024.0 + 273.15; 
}



void display_sensors(){
  Serial.println("");
  Serial.print("IAT(K):\t");
  Serial.print(IAT);
  Serial.println("");
  Serial.print("MAP(P):\t");
  Serial.print(MAP);
  Serial.println("");
  
  Serial.print("ECT(K):\t");
  Serial.print(ECT);
  Serial.println("");
  if (ECT < 373.15) {
    Serial.println("ECT cold enough, (<100C)- Not too hot - No change Needed");
  } else {
    Serial.println("ECT too high, (>100C)- Too hot - Pump more coolant");
  }
  
  Serial.print("Lambda:\t");
  Serial.print(Lambda);
  Serial.println("");
  if (Lambda<9.26 ) {
    Serial.println("AFR < 0.95AFR Stochiometric, Mixture too Rich");
    Serial.println("Pump less fuel");
  } else if(Lambda > 10.2375){
    Serial.println("AFR > 1.05AFR Stochiometric, Mixture too lean");
    Serial.println("Pump More fuel");
  } else {
    Serial.println("AFR withn 5% of AFR Stochiometric. Mixture balanced");
  }

  
  Serial.print("Fuel_T(K):\t");
  Serial.print(Fuel_T);
  Serial.println("");
  if (Fuel_T < 303.15) {
    Serial.println("Fuel Temp too low,(<30C): Heater Active");
  } else {
    Serial.println("Fuel Temp Sufficiently High (>30C): Heater Inactive");
  }
  
  Serial.print("PCB_temp:\t");
  Serial.print(PCB_temp);
  Serial.println("");
  /*Serial.print("F_ipg:\t");
  Serial.print(n_ipg);
  Serial.println("");
  Serial.print("F_cpg:\t");
  Serial.print(n_cpg);
  */
}


void safety_checks(){
  if (PCB_temp > 300  || (crankshaft_pos - camshaft_pos *2.0) > 10) {
    Serial.println("PCB Temp too high, Shutting down");
    for (int i=0; i<100; i++){
      delay(5000);
    }
  }
}


void calc_injection() {
  m_air = MAP/10.0 * 7.65 /IAT * vol_eff; // in mg per s
  //m_air = MAP * n_cyl * N * v_eng /1000000 /(R*IAT*2*60)*vol_eff;
  m_fuel = m_air / 9.75;
  //m_fuel = m_air / AFRstoc/4;
  t_fuel =   m_fuel*1000/m_fuel_rate_possible ; 
}

void send_injection(){
  analogWrite(2,255);
}

void display_calc(){
  Serial.print("m_air (mg/s):\t");
  Serial.print(m_air);
  Serial.println("");
  Serial.print("m_fuel(mg/s):\t");
  Serial.print(m_fuel);
  Serial.println("");
  Serial.print("t_fuel(ms):\t");
  Serial.print(t_fuel);
  Serial.println("");

}


void loop() {
  int initial_time = millis();
  read_sensors(); //Reads MAP,IAT,Lambda,IPG,CPG
  safety_checks();
  calc_injection();
  //send_injection();
  int calc_time = millis() - initial_time;
  Serial.println("Calculation time (microseconds)");
  Serial.println(calc_time);
  display_calc();
  // put your main code here, to run repeatedly:
  delay(2000);
  Serial.println("");
}



void read_all_sensors() {
  IAT = pulseIn(iat_pin, HIGH)/2040.0*5.0*8.38 + 273.15 + 48.935 ;
  //T= 8.38 Vıat + 48.935 + 273.15
  MAP = pulseIn(map_pin, HIGH)/2040.0*5.0/2.91*100000;
  //P = V/2.91 * 10^5     -----2.91: 10e5Pa, 0:0
  ECT = pulseIn(ect_pin, HIGH)/2040.0*5.0*26.155*-1 + 145.29 + 273.15;
  // T = -26.155V + 145.29 + 273.15
  Lambda = pulseIn(lambda_pin, HIGH)/2040.0*5.0*15.04/5.0 + 7.35;
  // AFR = V*15.04/5+7.35
  Fuel_T =pulseIn(fuel_temp_pin, HIGH)/2040.0*5.0*20 + 273.15;
  // Assume: 273.15 + 20*V
  PCB_temp = pulseIn(pcb_temp_pin, HIGH, 200);//*250.0/204.0/1024.0
  // K = rawvoltage/1024.0 * 5000 / 10 - pcb_temp_pin
  n_ipg = pulseIn(ipg_pin, HIGH, 500);
  n_cpg = pulseIn(cpg_pin, HIGH, 500);
  int temp = analogRead(pin_pcb);
  PCB_temp = temp* 25.0 / 2.98 * 5.0 / 1024.0 + 273.15; 
}
