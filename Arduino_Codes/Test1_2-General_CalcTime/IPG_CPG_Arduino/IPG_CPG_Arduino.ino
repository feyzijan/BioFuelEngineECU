//For Arduino Uno
/* This script sends IPG CPG signals of a given frequency
 * 
 * 
 */

// Define pins
const int cpg = 9;
const int ipg = 10; 


// Define variables
int dc = 78;

void setup() {
  // Configure pins
  pinMode(ipg, OUTPUT);
  pinMode(cpg, OUTPUT);

  // Toggle Frequency for Arduino UNO
  TCCR1B = TCCR1B & B11111000 | B00000101; // for PWM frequency of 30.64 Hz - Pins D9-D10

  // Start pwm 
  analogWrite(ipg,dc); // Start IPG first
}



void loop() {
  custom_cpg();
}

void send_ipg(float rpm){
  float rps = rpm/60.0;
  float ipg_time = 1000.0/rps/12.0; // Time in between the 30 degree pulses
}


void custom_cpg(float rpm){
  float rps = rpm/60.0;
  
  analogWrite(cpg,dc); // Start CPG Pulse 1
  delay(32); // Wait for 1 period
  analogWrite(cpg,0); // Turn off CPG Pulse 1

  delay(162); // Wait for 5 periods 

  analogWrite(cpg,dc); // Start CPG Pulse 2-3
  delay(65); // Wait for 2 periods
  analogWrite(cpg,0); // Turn off CPG Pulse 2-3

  delay(130); // Wait for 4 periods

  
}



//
/*TO:do
- Optimise memory by using chars
*/
