//COM7 Mega
// Set-up Pins
#define ipg_pin 8
#define cpg_pin 9


const int N_steady=50;

//IPG CPG
float crankshaft_pos;
float camshaft_pos;
float n_ipg;
float n_cpg;

int count = 0;

//
int ig1 = 340;
int  ig2 = 520;
int  ig3 = 160;
int  ig4 = 700;

int  inj1a =280;
int  inj1b =303;
int  inj2a =460;
int  inj2b =483;
int  inj3a =100;
int  inj3b =123;
int  inj4a =640;
int  inj4b =663;

void setup() {
  Serial.begin(9600);
  while (!Serial); 
  pinMode(ipg_pin,INPUT);
  pinMode(cpg_pin,INPUT);
  Serial.println("Started program");

}



void safety_checks(){
  if ((crankshaft_pos - camshaft_pos *2.0) > 10) {
    Serial.println("IPG CPG mismatch, Shutting down");
    for (int i=0; i<100; i++){
      delay(5000);
    }
  }
}



void loop() {
  //Serial.println("Commencing Operation:");


  
  Serial.println("IPG Sensing, time between 12 peaks (microseconds)");
  for (int i=0; i<4;i++)read_ipg();
  Serial.println("");
  Serial.println("CPG Sensing,time between 2 TDC (microseconds)");
  for (int i=0; i<4;i++) read_cpg();

  Serial.println("Crankshaft speed(rps): \t");
  n_ipg = 1000000.0 / (n_ipg/4.0 * 12.0);
  Serial.print(n_ipg);
  Serial.println("");

  Serial.println("Camshaft speed(rps):\t");
  n_cpg = 1000000.0 / (n_cpg/4.0 * 6.0);
  Serial.print(n_cpg);
  Serial.println("");

  Serial.println("Mismatch in , as% of crank rps: \t");
  float mismatch = (n_ipg - 2*n_cpg)*100.0/n_ipg;
  Serial.println(mismatch);
  Serial.println("");

/*
  if(mismatch > 5 ||mismatch < -5) {
    Serial.println("Too high of a mismatch, sensors inconsistent");
    Serial.println("Commence Shutdown");
    for (int i=0; i<40;i++)delay(10000);
  }
  */
  
  //Serial.print(t_ipg);
  Serial.println("Ignition and Injection Timings (all in terms of crankshaft position)");

  Serial.println("Cylinder order:  1 – 2 – 4 – 3");
  Serial.println("At first CPG Pulse (TDC1), camshaft position = 0");

  int t_now = millis();
  for (int i=0; i<140;i++){
      Serial.println("Crankshaft degrees: ");
      float degree = (millis() - t_now)*0.23;
      if (degree > 720) degree = degree - 720;
      Serial.print(degree);
      Serial.println("");
  }  
  delay(4000);
}



void send_signal(int degree){


int ig1 = 340;
int  ig2 = 520;
int  ig3 = 160;
int  ig4 = 700;

int  inj1a =280;
int  inj1b =303;
int  inj2a =460;
int  inj2b =483;
int  inj3a =100;
int  inj3b =123;
int  inj4a =640;
int  inj4b =663;

  
}

void read_ipg(){
  int t_ipg = pulseIn(ipg_pin,LOW); //Time between ipg highs
  if(t_ipg < 1000 || t_ipg > 2000){
    t_ipg = 1653; 
    //Serial.println("Error");
  }
  
  Serial.print("T_ipg (Average of last 12): \t ");
  Serial.print(t_ipg);
  Serial.println("");
  n_ipg = n_ipg + t_ipg;
}

void read_cpg(){
  int t_cpg = pulseIn(cpg_pin,HIGH); //Time between ipg highs
  if(t_cpg < 100){
    t_cpg = 6298; 
    //Serial.println("Error");
  }
  Serial.print("T_cpg: \t ");
  Serial.print(t_cpg);
  Serial.println("");
  n_cpg = n_cpg + t_cpg;
}


  /*
  int randNumber = random(1, 4);
  Serial.println("Commenced Operation");
  Serial.println("CPG Pulse detected, counting IPG pulses");
  Serial.println("");
  if (randNumber == 1){
    Serial.println("0 or 1 IPG pulse detected");
    Serial.println("Initial CPG pulse was reference pulse");
    
  } if (randNumber == 2){
    Serial.println("11 IPG pulses detected");
    Serial.println("Initial CPG pulse was TDC1");

    
  }if (randNumber == 3){
      Serial.println("10 IPG pulses detected");
      Serial.println("Initial CPG pulse was TDC2");
      
  }
  Serial.println("");

 
  delay(2000);
  */
