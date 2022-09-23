 // Define analog input
const int lambda_pin = 4;


void setup() {
  // setup pins
  pinMode(lambda_pin, INPUT);
  
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  int vin = analogRead(lambda_pin);
  double afr = double(vin) / 204.8 * 15.04 / 5.0 + 7.35;

  Serial.print("V Value (Digital): ");
  Serial.print(vin);
  Serial.print("\n");

  Serial.print("V Value (Analog) : ");
  Serial.print(double(vin)/204.8);
  Serial.print("\n");

  Serial.print("AFR:");
  Serial.print(afr);
  Serial.print("\n");


  delay(1500);

}
