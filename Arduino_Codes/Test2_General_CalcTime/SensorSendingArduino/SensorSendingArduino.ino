//For Arduino Mega
/*This script sends 5 variable sensor values, which can be 
 * toggled at will with the IR Remote
 * 
 * TO - DO: Set default values to sensible values
 */

int iat_dc = 100; // Initial Value: 3.92V = 
float iat_v;

int ect_dc = 100; // Initial Value: 1.96V = xxx degrees celsius
float ect_v;

int map_dc =  37; // Initial Value: 2.84V = xxx pascals
float map_v;

int lambda_dc = 41; // 0.8V = 9.75 AFR (stoichiometric)
float lambda_v;

int fuel_temp_dc = 128; // 2.5V = xxx degrees celsius
float fuel_temp_v;

int pcb_temp_dc = 128; // 2.5V = xxx degrees celsius
float pcb_temp_v;

int ipg_dc = 150;
int cpg_dc = 75;

// Declare IR Object
#include "IRremote.h"
const int receiver = 8;
IRrecv irrecv(receiver);    
decode_results results;  


// Setup Pins
//PWM pins: D2 to D13(490 Hz)-  D4,D13 :(980 Hz)
#define iat_pin 2
#define ect_pin 3
#define map_pin 7
#define lambda_pin 5
#define fuel_temp_pin 6
#define pcb_temp_pin 9
#define ipg_pin 10
#define cpg_pin 11


void setup() {
  // Set pins as outputs
  pinMode(iat_pin, OUTPUT);
  pinMode(ect_pin, OUTPUT);
  pinMode(map_pin, OUTPUT);
  pinMode(lambda_pin, OUTPUT);
  pinMode(pcb_temp_pin, OUTPUT);
  //pinMode(ipg_pin, OUTPUT);
  //pinMode(cpg_pin, OUTPUT);
  pinMode(receiver, INPUT);

  send_outputs(); // Start sending all signals
  
  Serial.begin(9600);
  while (!Serial); 
  display_outputs();        //Display outputs in serial
  irrecv.enableIRIn(); // Start the Remote
  

}



void loop() {
  if (irrecv.decode(&results)) // Just checks for Remote input
  {
    translateIR(); //Interpret Input
    Serial.println(""); 
    send_outputs();
    irrecv.resume(); // receive the next value
  }  
}

void send_outputs(){
    analogWrite(iat_pin,iat_dc);
    analogWrite(ect_pin,ect_dc);
    analogWrite(map_pin,map_dc);
    analogWrite(lambda_pin,lambda_dc);
    analogWrite(fuel_temp_pin,fuel_temp_dc);
    analogWrite(pcb_temp_pin,pcb_temp_dc);
    //analogWrite(ipg_pin,ipg_dc);
    //analogWrite(cpg_pin,cpg_dc);
  
}

void display_outputs(){
    Serial.print("IAT(V) = ");
    iat_v = iat_dc*5.0/256.0;
    Serial.print(iat_v);
    Serial.println("");
    Serial.print("ECT(V) = ");
    ect_v = ect_dc*5.0/256.0;
    Serial.print(ect_v);
    Serial.println("");
    Serial.print("MAP(V) = ");
    map_v = map_dc*5.0/256.0;
    Serial.print(map_v);
    Serial.println("");
    Serial.print("Lambda(V) = ");
    lambda_v = lambda_dc*5.0/256.0;
    Serial.print(lambda_v);
    Serial.println("");
    Serial.print("Fuel Temp(V) = ");
    fuel_temp_v = fuel_temp_dc*5.0/256.0;
    Serial.print(fuel_temp_v);
    Serial.println("");
    Serial.print("PCB Temp(V) = ");
    pcb_temp_v = pcb_temp_dc*5.0/256.0;
    Serial.print(pcb_temp_v);
    Serial.println("");
    /*Serial.println("IPG DC = ");
    Serial.print(ipg_dc);
    Serial.println("");
    Serial.println("CPG DC = ");
    Serial.print(cpg_dc); 
    */
    
}

// TODO: Write cases

void translateIR() // takes action based on IR code received
{
  switch(results.value)
  {
  case 0xFFA25D: 
    Serial.println("POWER");
    Serial.println("PCB_temp (V) = ");
    pcb_temp_dc = 255;  
    break;
  
  case 0xFF629D: 
    Serial.println("VOL+");
    Serial.println("Increase all inputs");
    pcb_temp_dc = pcb_temp_dc *1.1;
    iat_dc = iat_dc *1.1;
    ect_dc = ect_dc *1.1;
    map_dc = map_dc *1.1;
    lambda_dc = lambda_dc * 1.1;
    fuel_temp_dc = fuel_temp_dc *1.1;
    break;
    
  case 0xFFA857: 
    Serial.println("VOL-"); 
    Serial.println("Decrease all inputs ");
    pcb_temp_dc = pcb_temp_dc *0.9;
    iat_dc = iat_dc *0.9;
    ect_dc = ect_dc *0.9;
    map_dc = map_dc *0.9;
    lambda_dc = lambda_dc * 0.9;
    fuel_temp_dc = fuel_temp_dc *0.9;
    break;
  
  case 0xFF22DD: 
    Serial.println("FAST BACK"); 
    //Serial.println("IPG, CPG DC = ");
    //Serial.print(--ipg_dc);
    //Serial.print(--ipg_dc);
    //Serial.print(--cpg_dc);  
    break;
  
  case 0xFFC23D: 
    Serial.println("FAST FORWARD");  
    //Serial.print(++ipg_dc);
    //Serial.print(++ipg_dc);
    //Serial.print(++cpg_dc);
    break;

  case 0xFF6897: 
    Serial.println("0");
    Serial.println("IAT (V) = ");
    iat_dc = iat_dc *1.1;
    iat_v = iat_dc*5.0/256.0;
    Serial.print(iat_v); 
    break;
    
  case 0xFF30CF: 
    Serial.println("1");    
    Serial.println("IAT (V) = ");
    iat_dc = iat_dc *0.9;
    iat_v = iat_dc*5.0/256.0;
    Serial.print(iat_v); 
    break;
    
  case 0xFF18E7: 
    Serial.println("2");  
    Serial.println("ECT (V)= ");
    ect_dc = ect_dc *1.1;
    ect_v = ect_dc*5.0/256.0;
    Serial.print(ect_v);  
    break;
    
  case 0xFF7A85:
    Serial.println("3"); 
    Serial.println("ECT (V) = ");
    ect_dc = ect_dc *0.9;
    ect_v = ect_dc*5.0/256.0;
    Serial.print(ect_v);
    break;
    
  case 0xFF10EF:
    Serial.println("4");
    Serial.println("MAP (V) = ");
    map_dc = map_dc *1.1;
    map_v = map_dc*5.0/256.0;
    Serial.print(map_v);
    break;
    
  case 0xFF38C7:
    Serial.println("5");  
    Serial.println("MAP (V) = ");
    map_dc = map_dc *0.9;
    map_v = map_dc*5.0/256.0;
    Serial.print(map_v);
    break;
    
  case 0xFF5AA5: 
    Serial.println("6");   
    Serial.println("lambda (V) = ");
    lambda_dc = lambda_dc * 1.1;
    lambda_v = lambda_dc*5.0/256.0;
    Serial.print(lambda_v);
    break;
    
  case 0xFF42BD: 
    Serial.println("7"); 
    Serial.println("lambda (V) = ");
    lambda_dc =  lambda_dc*0.9;
    lambda_v = lambda_dc*5.0/256.0;
    Serial.print(lambda_v);
    break;
    
  case 0xFF4AB5: 
    Serial.println("8"); 
    Serial.println("fuel_temp (V) = ");
    fuel_temp_dc = fuel_temp_dc * 1.1;
    fuel_temp_v = fuel_temp_dc*5.0/256.0;
    Serial.print(fuel_temp_v);
    break;
    
  case 0xFF52AD: 
    Serial.println("9");  
    Serial.println("fuel_temp (V) = ");
    fuel_temp_dc = fuel_temp_dc *0.9;
    fuel_temp_v = fuel_temp_dc*5.0/256.0;
    Serial.print(fuel_temp_v);
    break;
    
  case 0xFFFFFFFF: Serial.println(" REPEAT"); break;  
  
  case 0xFFE21D: 
    Serial.println("FUNC/STOP"); 
    break;
  
  case 0xFF02FD: Serial.println("PAUSE");    break;
  case 0xFFE01F: Serial.println("DOWN");    break;
  case 0xFF906F: Serial.println("UP");    break;
  case 0xFF9867: Serial.println("EQ");    break;
  case 0xFFB04F: Serial.println("ST/REPT");    break;
  
  default: 
    Serial.println(" other button   ");
  }
  delay(500); // Do not get immediate repeat
}
