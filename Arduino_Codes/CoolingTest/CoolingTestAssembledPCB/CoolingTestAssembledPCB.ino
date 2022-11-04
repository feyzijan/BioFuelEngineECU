 // With Arduino Uno
 // Define analog inputs 
#define pin1 14
#define pin2 15

#include <Wire.h>
#include "Adafruit_MCP9808.h"

float timer;

// Create the MCP9808 temperature sensor object
Adafruit_MCP9808 tempsensor = Adafruit_MCP9808();

void setup() {
  pinMode(pin1, INPUT);
  pinMode(pin2, INPUT);
  
  Serial.begin(9600);
  while (!Serial); //waits for serial terminal to be open
  Serial.println("Beginning sensing on the pcb and outside");
  
  
   if (!tempsensor.begin(0x18)) {
    Serial.println("Couldn't find MCP9808!");
    while (1);
  }
  tempsensor.setResolution(0);// Mode Resolution SampleTime
}

void loop() {
  tempsensor.wake();
  
  // On board LM Sensors
  int v1 = analogRead(pin1);
  int v2 = analogRead(pin2);
  float temp1 = v1* 25.0 / 2.98 * 5.0 / 1024.0; 
  float temp2 = v2* 25.0 / 2.98 * 5.0 / 1024.0; // 10mV per Degree change
  
  //Serial.print("Temp 1 Value (Digital): ");
  //Serial.print(v1);
  Serial.print("T1(onheater):");
  Serial.print(temp1);
  
  Serial.print("\t");
  //Serial.print("Temp 2 Value (Digital): ");
  //Serial.print(v2);
  Serial.print("T2: ");
  Serial.print(temp2);
  Serial.print("\t");

  //MCP Sensor - Outside by the grill
  
  //Serial.println("");
  float c = tempsensor.readTempC();
  Serial.print("T3(Outside): "); 
  Serial.print(c, 4);

  // timer
  Serial.print("\t");
  timer = millis();
  Serial.print(timer);

  Serial.println("");
 
  delay(800);
  tempsensor.shutdown_wake(1); // shutdown MSP9808 - power consumption ~0.1 mikro Ampere, stops temperature sampling
  delay(200);

}
