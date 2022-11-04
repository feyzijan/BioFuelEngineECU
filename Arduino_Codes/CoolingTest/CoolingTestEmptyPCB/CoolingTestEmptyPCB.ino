#include <Wire.h>
#include "Adafruit_MCP9808.h"


// Create the MCP9808 temperature sensor object
Adafruit_MCP9808 tempsensor = Adafruit_MCP9808();

#define tempPin 0

float timer;

void setup() {
  Serial.begin(9600);
  while (!Serial); //waits for serial terminal to be open
  Serial.println("Started Test");
  if (!tempsensor.begin(0x18)) {
    Serial.println("Couldn't find MCP9808!");
    while (1);
  }
   Serial.println("Found MCP9808!");

  tempsensor.setResolution(0);// Mode Resolution SampleTime

}



void loop() {
  // MCP Sensor - Inside
  tempsensor.wake();
  Serial.println("");
  //
  float c = tempsensor.readTempC();
  //Serial.print("Temp(MCP): "); 
  Serial.print(c, 4); 
  //Serial.print("*C"); 
  //
  
  Serial.print("\t");
  
  //LM335Z Sensor - Outside
  int rawvoltage= analogRead(tempPin);
  float millivolts= (rawvoltage/1024.0) * 5000;
  float celsius= (millivolts/10.0) - 273.15;
  
  //Serial.print("Temp(LM335): ");
  Serial.print(celsius);
  //Serial.println("*C");
  //
  Serial.print("\t");
  timer = millis();
  Serial.print(timer);

  delay(800);
  tempsensor.shutdown_wake(1); // shutdown MSP9808 - power consumption ~0.1 mikro Ampere, stops temperature sampling
  delay(200);
}
