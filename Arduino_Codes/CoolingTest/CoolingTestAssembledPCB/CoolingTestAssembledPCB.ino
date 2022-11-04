 // Run on Arduino Uno //
 
 // Define analog inputs 
#define pin1 14
#define pin2 15

// Imports
#include <Wire.h>
#include "Adafruit_MCP9808.h"

// Variables
float timer;

// Create the MCP9808 temperature sensor object
Adafruit_MCP9808 tempsensor = Adafruit_MCP9808();

/* Setup Pins, Serial Monitor, and check that Temp Sensor is active
 * and set sensor resolution
 */
void setup() {
  pinMode(pin1, INPUT);
  pinMode(pin2, INPUT);
  
  Serial.begin(9600);
  while (!Serial); // wait for serial terminal to be opened on PC
  Serial.println("Beginning sensing on the pcb and outside");
  
   if (!tempsensor.begin(0x18)) {
    Serial.println("Couldn't find MCP9808!");
    while (1);
  }
  tempsensor.setResolution(0);// Mode Resolution SampleTime
}
/* Take readings from multiple sensors and output these to serial
 * so they can be saved by Putty
 */
void loop() {
  tempsensor.wake();
  
  // On board LM Temperature Sensors
  int v1 = analogRead(pin1);
  int v2 = analogRead(pin2);
  float temp1 = v1* 25.0 / 2.98 * 5.0 / 1024.0; 
  float temp2 = v2* 25.0 / 2.98 * 5.0 / 1024.0; // 10mV per Degree change
  
  Serial.print("T1(onheater):");
  Serial.print(temp1);
  Serial.print("\t");
  Serial.print("T2: ");
  Serial.print(temp2);
  Serial.print("\t");

  //MCP Sensor - Outside by the grill
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
