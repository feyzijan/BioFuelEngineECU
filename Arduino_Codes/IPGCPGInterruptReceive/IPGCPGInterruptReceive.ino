// Define pins
const int ipg_in = 3;
const int cpg_1_in = 2;

// Volatile variables
volatile int ipg_pwm_value = 0;
volatile int prev_time = 0;

// IPG Pulse counter
int ipg_counter = 0;

// Variables for frequency calculation
long frequency;
char frequency_flag;

// Duty cycle
char dc = 78;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  // Attach Interrupts
  attachInterrupt(digitalPinToInterrupt(ipg_in), ipg_rising, RISING);
  //attachInterrupt(digitalPinToInterrupt(cpg_1_in), cpg_1_rising, RISING);
}

void loop() {
  // put your main code here, to run repeatedly:

  //Print frequency
  if(frequency_flag == 1) {
    frequency =  1000000.0 * dc / ( ipg_pwm_value * 255.0); 
    Serial.print(" Frequency :");
    Serial.print(frequency);
    Serial.println();
    Serial.println(" IPGCount:");
    Serial.println(ipg_counter);
    frequency_flag = 0;
  }


}


void ipg_rising() {
  attachInterrupt(digitalPinToInterrupt(ipg_in), ipg_falling, FALLING);
  prev_time = micros();
  ipg_counter +=1;
}
 
void ipg_falling() {
  attachInterrupt(digitalPinToInterrupt(ipg_in), ipg_rising, RISING);
  ipg_pwm_value = micros()-prev_time;
  Serial.println(" Micros:");
  Serial.println(ipg_pwm_value);
  frequency_flag = 1;
}

void cpg_1_falling() {

}

void cpg_1_rising() {
  ipg_counter = 0;
  Serial.println(" CPGInterrupt");
}



/* Notes on ISR
delayMicroseconds() // works in ISR
LOW,CHANGE,RISING,FALLING modes available
Pıns available: 2,3,18,19,20,21
*/

