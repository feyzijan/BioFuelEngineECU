 // Define analog inputs 
const int pin1 = 14;
const int pin2 = 15;

void setup() {
  // setup pins
  pinMode(pin1, INPUT);
  pinMode(pin2, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int v1 = analogRead(pin1);
  int v2 = analogRead(pin2);
  float temp1 = v1* 25.0 / 2.98 * 5.0 / 1024.0; 
  float temp2 = v2* 25.0 / 2.98 * 5.0 / 1024.0; // 10mV per Degree change
  


  Serial.print("Temp 1 Value (Digital): ");
  Serial.print(v1);
  Serial.print(" -Celsius: ");
  Serial.print(temp1);
  
  Serial.print("\n");
  Serial.print("Temp 2 Value (Digital): ");
  Serial.print(v2);
  Serial.print(" -Celsius: ");
  Serial.print(temp2);
  Serial.print("\n");
  delay(3000);

}
