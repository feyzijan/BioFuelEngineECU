//Variables that change
int N;
int crank_speed;

// Variables to recalculate constantly
float t_valve;

float m_rate_air;
float m_rate_fuel_desired;
float m_rate_fuel_achieved;
float AFR_achieved;
float crankshaft_position; // from ipg, cpg
float vol_eff; // linearly increases with RPM

float t_inj_stoc;
float t_inj_stoc2;
float a_stoc;

// Extra variables to recalculate constantly
float brake_power;
float n_thermal;
float bsfc;

// Constants
const int N_start = 300; // starter motor
const int N_end = 3000;
const int N_step = 5;
const int step_time = 55; //ms
const int MAP = 25000;
const int IAT = 300; //K
const int Torque = 35; 
const int R = 287;
const int v_engine = 599; //cm^3 -> 10e-6
const int q_inj = 875; // * 10e-8 volumetric flow rate of single bosch fuel injector 
const int density_fuel = 779; // fuel density
const long NCV = 30000000;
const int n_cylinder = 4;
const float AFR_stoc = 9.75;
const float m_rate_fuel_possible = 0.027265;//Change to real value = q_rate_inj * denisty_fuel * n_cylinder;
const float valve_angle = 1.134; // 65 degree in radians
const float pi = 3.14159;


/* Function to Calculate Air Flow
Change to use pointers possibly
*/
float calc_air_flow(){
  m_rate_air = MAP * n_cylinder * v_engine *N * vol_eff /(60 *2 * R * IAT);
  return m_rate_air;
}


void update_values(){
  t_valve = valve_angle / ((N*2*pi)/60); // time the air intake valve is open for a cylinder
  
  //vol_eff = -2.19494048e-08,  1.57291667e-04,  4.60178571e-01
  
  m_rate_air = MAP * n_cylinder* N * v_engine/1000000/(R*IAT*2*60)*vol_eff;
  brake_power = 2*pi*Torque/60*N; 
  
  //m_rate_fuel_desired = m_rate_air / 9.75;
  
  n_thermal = brake_power / (m_rate_fuel_desired * NCV);// Divide by duty cycle later
  bsfc = m_rate_fuel_desired / brake_power;


  
  t_inj_stoc = m_rate_air * t_valve / (m_rate_fuel_possible*AFR_stoc); //stoichiometric injection duration (using valve opening time)
  t_inj_stoc2 = m_rate_air / (m_rate_fuel_possible * AFR_stoc * (N/2/60)); // # stoichiometric injection duration (not using valve opening time)
  a_stoc = t_inj_stoc * (N/2/60);  // stoichiometric duty cycle of injection pulses at a given speed

  

}
#include <LiquidCrystal.h>
const int rs = 7, en = 8, d4 = 9, d5 = 10, d6 = 11, d7 = 12;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

float my_rpm = 297;
float my_air;
float my_fuel;
void setup() { 
  Serial.begin(9600);
  Serial.print(calc_air_flow());
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Open up trans");
  delay(5000);
  
}



float my_rpm = 297;
float my_air;
float my_fuel;
void loop() {
  my_rpm = my_rpm +3;
  my_air = 10.3518 * my_rpm/3000.0 ; // in mg per s - 0.8 extra
  my_fuel = my_air / 9.75;
  lcd.setCursor(0, 0);
  lcd.print("RPM:");
  lcd.print(my_rpm);
  lcd.setCursor(8, 0);
  lcd.print("Air:");
  lcd.print(my_air);
  lcd.setCursor(0, 1);
  lcd.print("Fuel:");
  lcd.print(my_fuel);
  lcd.print("       ");
  delay(50);

}
