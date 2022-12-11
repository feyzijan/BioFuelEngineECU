//initializes/defines the output pin of the LM335 temperature sensor
int outputPin= 0;
//this sets the ground pin to LOW and the input voltage pin to high
void setup()
{
Serial.begin(9600);
}

//main loop
void loop()
{
int rawvoltage= analogRead(outputPin);
float millivolts= (rawvoltage/1024.0) * 5000;
float celsius= (millivolts/10.0) - 273.15;

Serial.print(celsius);
Serial.println(" degrees Celsius");


}
