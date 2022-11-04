// Define pins
#define ipg  8 //PB0
#define cpg 9 //PB1


int rpm = 3000;


void setup() {
  // put your setup code here, to run once:
  pinMode(ipg, OUTPUT);
  pinMode(cpg, OUTPUT);
  PORTB = B00000000;
}

void loop() {
  long period = 1000000 / (rpm/60);
  for(int i=0; i<5; i++) send_ipg(period);
  delayMicroseconds(10);
  for(int i=0; i<5; i++) send_cpg(period);
  //send_sync(1,period);
}

// long period = 1000000 / (rpm/60);
void send_ipg(long period){
    for(int i=0;i<24;i++){
    delayMicroseconds(period/12); //1667
    PORTB = B00000001; delayMicroseconds(10); PORTB = B00000000; // Set IPG High For 10micros then low
  }}

void send_cpg(long period){
  //First TDC Pulse
  PORTB = B00000010; delayMicroseconds(10); PORTB = B00000000; // Set CPG High For 10micros then low
  delayMicroseconds(period); //Wait for one crank rev
  //Second TDC Pulse
  PORTB = B00000010; delayMicroseconds(10); PORTB = B00000000; // Set CPG High For 10micros then low
  delayMicroseconds(period/12); // Wait for 1/12 crank rev
  //Reference Pulse
  PORTB = B00000010; delayMicroseconds(10); PORTB = B00000000; // Set CPG High For 10micros then low
  delayMicroseconds(period*11/12);  // Wait for 11/12 crank rev
}


void send_sync(int mode,int period){
  if(mode == 1){ // TDC1-TDC2
    PORTB = B00000010;// Turn on CPG, Turn off IPG 
    delayMicroseconds(10);
    PORTB = B00000000;
    delayMicroseconds(100);
    for(int i=0;i<10;i++){
    delayMicroseconds(period/12); //1667
    PORTB = B00000001;// Turn on IPG, Turn off CPG
    delayMicroseconds(10);
    PORTB = B00000000;// Turn off IPG and CPG
  }
    
  }

  if (mode ==2){ // TDC2- Ref
    PORTB = B00000010;// Turn on CPG, Turn off IPG 
    delayMicroseconds(10);
    PORTB = B00000000;
    delayMicroseconds(100);
    for(int i=0;i<1;i++){
    delayMicroseconds(period/12); //1667
    PORTB = B00000001;// Turn on IPG, Turn off CPG
    delayMicroseconds(10);
    PORTB = B00000000;// Turn off IPG and CPG
    
    }
  }

  if( mode ==3) { // Ref - TDC1
    PORTB = B00000010;// Turn on CPG, Turn off IPG 
    delayMicroseconds(10);
    PORTB = B00000000;
    delayMicroseconds(100);
    for(int i=0;i<1;i++){
    delayMicroseconds(period/9); //1667
    PORTB = B00000001;// Turn on IPG, Turn off CPG
    delayMicroseconds(10);
    PORTB = B00000000;// Turn off IPG and CPG
    
  }
}
}
