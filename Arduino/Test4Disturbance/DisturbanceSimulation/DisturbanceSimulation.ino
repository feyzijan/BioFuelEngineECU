// Set-up Variables and constants


int N = 3000;

float m_air;
float Lambda;


float m_fuel_desired;
float m_fuel_realised;
float t_fuel;
float t_valve;

float new_rpm = 3000.0;

float adjustment;
float new_power;
const int Pinitial = 4392; //with 40 percent efficiency

#include <LiquidCrystal.h>
const int rs = 7, en = 8, d4 = 9, d5 = 10, d6 = 11, d7 = 12;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int count;
float sum_lam;
void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Open up Steady");
  delay(5000);
  //while (!Serial); 
  adjustment = 1;
  count = 0;
}

void loop() {
  count++;
  calc_injection(adjustment);
  //display_calc();

  Serial.println("");

  int rando = random(97,103); 
  
  Serial.print("Dist:");
  Serial.print(rando);
  lcd.setCursor(0, 0);
  lcd.print("Dist:");
  lcd.print(rando);
  if(rando < 100){
    lcd.print(" ");
  }
  float random_impulse = rando /100.0;
  m_fuel_realised = m_fuel_desired * random_impulse;
  
  //Serial.print("Fuel_actual_:\t ");
  //Serial.println(m_fuel_realised);
  //Serial.print("NewPower:\t");
  new_power = 4392.0 * m_fuel_realised /1.01617;
  //Serial.println(new_power);
  //Serial.println("");
  Serial.print("RPM");
  new_rpm = new_power/1.466;
  int temp = round(new_rpm);
  Serial.print(new_rpm);
  lcd.setCursor(8, 0);
  lcd.print("RPM:");
  lcd.print(temp);
  //lcd.print("_");


  lcd.setCursor(0, 1);
  
  //Serial.println("");
  
  Serial.print("AFR:");
  Lambda = m_air/m_fuel_realised;
  Serial.print(Lambda);
  lcd.print("AFR:");
  lcd.print(Lambda);
  //lcd.print("_");
  
  if (new_rpm >3000) {
    //Serial.println("Too much fuel injected, pump less fuel next time");
    adjustment = 3000.0/new_rpm;
  } else{
    //Serial.println("Too little fuel injected, pump more fuel next time");
    adjustment = new_rpm/3000;
  }

  sum_lam = sum_lam + Lambda;
  lcd.setCursor(8, 1);
  lcd.print("Av:");
  lcd.print(sum_lam/count);
  
  
  //Serial.print("Adjust fuel next time by a factor of:\t");
  //Serial.println(adjustment);
  //Serial.println("");

  delay(1000);
}



void calc_injection(float adjustment) {
  m_air = 10.3518 * new_rpm/3000.0 ; // in mg per s - 0.8 extra
  //m_air = MAP * n_cyl * N * v_eng /1000000 /(R*IAT*2*60)*vol_eff;
  m_fuel_desired = 10.3518/9.75 * adjustment;
  //m_fuel = m_air / AFRstoc/4;
  t_fuel =   m_fuel_desired*1000.0/1704 ; 
}

void display_calc(){
  //Serial.print("----Air and Fuel flow calculations---");
  Serial.println("");
  //Serial.print("M_air(g/s):\t");
  Serial.print(m_air);
  Serial.println("");
  //Serial.print("M_fuel_desired(g/s):\t");
  Serial.print(m_fuel_desired);
  Serial.println("");
  //Serial.print("t_fuel(ms):\t");
  Serial.print(t_fuel);
}
