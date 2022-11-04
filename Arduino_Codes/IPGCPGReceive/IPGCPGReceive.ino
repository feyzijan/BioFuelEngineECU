// Define pins
const int ipg = 22;
const int cpg_1 = 24;
const int cpg_2 = 26;


// Define variables
long ipg_val;
long cpg_1_val;
long cpg_2_val;
float frequency;
long dc = 78;

void setup() {
  // Configure pins
  pinMode(ipg, INPUT);
  pinMode(cpg_1, INPUT);
  pinMode(cpg_2, INPUT);

  Serial.begin(9600);

  }

void loop() {

  //
  ipg_val = pulseIn(ipg, HIGH); //default 1s wait

  
  /* Forcing scales for graph
  Serial.print(1510); // To freeze the lower limit
  Serial.print(" ");
  Serial.print(1540); // To freeze the upper limit
  Serial.println();
  */

  Serial.println("IPG : ");
  Serial.print(ipg_val);
  Serial.println();

  frequency =  1000000.0 * dc / ( ipg_val * 255.0); 
  Serial.print("Frequency:");
  Serial.print(frequency);
  Serial.println();

  delay(1000);


  /*
  //CPG1
  cpg_2_val = pulseIn(cpg1_in, HIGH); //default 1s wait
  Serial.println("CPG: ");
  Serial.print(cpg_2_val);
  Serial.println();

  */

}

