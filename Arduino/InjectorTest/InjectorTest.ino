//Define pins
const int injector_pin = 3;






void setup() {
  // put your setup code here, to run once:
  TCCR2B = TCCR2B & B11111000 | B00000111; // for PWM frequency of 30.64 Hz for Pin 3 and 11
  pinMode(injector_pin, OUTPUT);
  analogWrite(injector_pin,255);
}


void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(injector_pin,255);
  delay(1000);
  analogWrite(injector_pin,0);
  delay(1000);


}