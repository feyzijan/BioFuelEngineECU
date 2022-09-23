const int ignition_pin = 11;
const int signal_length = 40;

void setup() {
  
  Serial.begin(9600);
  while(!Serial);
  // put your setup code here, to run once:
  TCCR2B = TCCR2B & B11111000 | B00000111; // for PWM frequency of 30.64 Hz for Pin 3 and 11
  pinMode(ignition_pin, OUTPUT);

  delay(5000);
  int loop_start = 0;

  for (int i = 0; i <25;i++) {
    loop_start = millis(); //new line
    analogWrite(ignition_pin,255);
    delay(signal_length);
    analogWrite(ignition_pin,0); 
    delay(signal_length);
    Serial.println(millis()-loop_start); //new line
    
  }

}


void loop() {


  // put your main code here, to run repeatedly:

}
