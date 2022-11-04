// Ignition and injection times, in crank degrees
int ig_1 = 340;
int ig_2 = 160; // First
int ig_3 = 520;
int ig_4 = 700;

int inj_1 =705;
int inj_2 =525;
int inj_3 =165; // First
int inj_4 =345;
//Injeciton order: 3-4-2-1
//Ignition Order: 2-1-3-4

//Cylinder Order 1-2-4-3
int time_step = 180;

volatile byte ig_counter = 0;
volatile byte inj_counter = 0;
volatile byte ig_flag = 0;
volatile byte inj_flag = 0;

long t_ig;
long t_inj;

void setup() {
  Serial.begin(9600); while(!Serial); Serial.println("Started");
  calc_timings();


  sei(); //Enable interrupts 
}

void loop() {
   t_ig = micros();
   t_inj = micros();
   
   if(ig_flag !=0){
    t_ig = micros() - t_ig;
    ig_flag = 0;
    Serial.print("Microseconds since Ignition interrupt: ");
    Serial.print(t_ig);
    Serial.println("");
    Serial.print("Ignition No: ");
    Serial.print(ig_counter);
    Serial.println("");
    //delay(10000);
   }
  if(inj_flag !=0){
    t_inj = micros() - t_inj;
    inj_flag = 0;
    Serial.print("Microseconds since Injection interrupt: ");
    Serial.print(t_inj);
    Serial.println("");
    Serial.print("Injection No: ");
    Serial.print(inj_counter);
    Serial.println("");
    //delay(10000);
   }

   
}

void calc_timings(){
  ig_2 = ig_2 * 13.8888 * 8.0;
  inj_3 =inj_3 * 13.8888 * 8.0;
  time_step= time_step * 13.888*8.0; //180 degrees
}

ISR(TIMER1_COMPA_vect){   
  OCR1A=time_step;
  sendIgnition(++ig_counter);
  if(ig_counter ==4){
    ig_counter = 0;
  }
  ig_flag = 1;  
}


ISR(TIMER2_COMPA_vect){  
  OCR2A=time_step;
  sendInjection(++inj_counter); 
  if(inj_counter ==4){
    inj_counter = 0;
  }
  inj_flag = 1;
}

void sendIgnition(int count){
}
void sendInjection(int count){
}

void timerSetup(int* first_ignition_bit, int* first_injection_bit){
    //Timer1 Setup for Ignition
  TCCR1A = 0; TCCR1B = 0; //Initialise all bits to zero
  TCNT1  = 0;           //Initialize counter value to 0
  TCCR1B=(1<<WGM12);    //Enable overflow at preset bit 
  OCR1A= *first_ignition_bit; // Overflow at first ignition
  TCCR1B|=(1<<CS01)|(1<<CS00); //Set 1/64 prescaler
  TIMSK1|=(1<<OCIE1A);   //Set the interrupt request
  
  //Timer 2 Setup for Injection
  TCCR2A = 0; TCCR2B = 0;//Initialise all bits to zero
  TCNT2  = 0;//initialize counter value to 0
  TCCR2A |= (1 << WGM21); //Enable overflow at preset bit 
  OCR2A = *first_injection_bit; // Overflow at first injection
  TCCR2B|=(1<<CS21)|(1<<CS00); //Set 1/64 prescaler 
  TIMSK2 |= (1 << OCIE2A);//Set the interrupt request
}
