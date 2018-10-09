//Code for pump activation: 

//##########################
//For questions please contact acanna@unisa.it
//Antonietta Canna, PhD Student, Salerno, Italy
//###########################

// General Setting
#include <SoftwareSerial.h>
#define MAX_SEQ_LENGTH 100

#define PUMP6_MASK (1)
#define PUMP5_MASK (1 << 1)
#define PUMP4_MASK (1 << 2)
#define PUMP3_MASK (1 << 3)
#define PUMP2_MASK (1 << 4)
#define PUMP1_MASK (1 << 5)

#define PUMP1_ID 2
#define PUMP2_ID 3
#define PUMP3_ID 4
#define PUMP4_ID 5
#define PUMP5_ID 6
#define PUMP6_ID 7

SoftwareSerial SerialCommands(10, 11); 

//pumps on digital I/O pin
int pumps[6] = {7,6,5,4,3,2};

//Request To Send GPIO
int RTS = 13;

//commands list [pump_number, ml, wait(s)]...[-1, -1, -1]
char commands[MAX_SEQ_LENGTH*3];
/*char commands[] = {0,1,2,
                   1,1,2,
                   2,1,2,
                   3,1,2,
                   4,1,2,
                   5,1,2,
                   0,0,-1};*/

//calibation value
int one_ml[6] = {600,   //0
                 600,   //1
                 600,   //2
                 600,   //3
                 600,   //4
                 600};  //5

int i=0;

void pump_it(char* command){
  if(command[0] & PUMP1_MASK)
  {
    digitalWrite(PUMP1_ID, HIGH);   // turn the PUMP on (HIGH is the voltage level)
  }
  if(command[0] & PUMP2_MASK)
  {
    digitalWrite(PUMP2_ID, HIGH);   // turn the PUMP on (HIGH is the voltage level)
  }
  if(command[0] & PUMP3_MASK)
  {
    digitalWrite(PUMP3_ID, HIGH);   // turn the PUMP on (HIGH is the voltage level)
  }
  if(command[0] & PUMP4_MASK)
  {
    digitalWrite(PUMP4_ID, HIGH);   // turn the PUMP on (HIGH is the voltage level)
  }
  if(command[0] & PUMP5_MASK)
  {
    digitalWrite(PUMP5_ID, HIGH);   // turn the PUMP on (HIGH is the voltage level)
  }
  if(command[0] & PUMP6_MASK)
  {
    digitalWrite(PUMP6_ID, HIGH);   // turn the PUMP on (HIGH is the voltage level)
  }
  
  delay(((int)command[1])*one_ml_ptr[(int)command[0]]);              // inject `command[1]` ml
  
  if(command[0] & PUMP1_MASK)
  {
    digitalWrite(PUMP1_ID, LOW);    // turn the PUMP off by making the voltage LOW
  }
  if(command[0] & PUMP2_MASK)
  {
    digitalWrite(PUMP2_ID, LOW);    // turn the PUMP off by making the voltage LOW
  }
  if(command[0] & PUMP3_MASK)
  {
    digitalWrite(PUMP3_ID, LOW);    // turn the PUMP off by making the voltage LOW
  }
  if(command[0] & PUMP4_MASK)
  {
    digitalWrite(PUMP4_ID, LOW);    // turn the PUMP off by making the voltage LOW
  }
  if(command[0] & PUMP5_MASK)
  {
    digitalWrite(PUMP5_ID, LOW);    // turn the PUMP off by making the voltage LOW
  }
  if(command[0] & PUMP6_MASK)
  {
    digitalWrite(PUMP6_ID, LOW);    // turn the PUMP off by making the voltage LOW
  }
  delay(((int)command[2]) * 1000);              //  wait for `command[2]` seconds                                           //  wait for `command[2]` seconds
}

// the setup routine runs once when you press reset:
void setup() {
  // Open serial communications to PC console and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  // Serial communications
  SerialCommands.begin(9600);

  // initialize the digital pin as an output.
  pinMode(RTS, OUTPUT);
  digitalWrite(RTS, LOW);
  for(i=0; i<6; i++)
    pinMode(pumps[i], OUTPUT);
}

int j=0;
// the loop routine runs over and over again forever:
void loop() {
  i=0;
  //digitalWrite(RTS, HIGH);
  while(i<MAX_SEQ_LENGTH){
    if (SerialCommands.available()){
      commands[i]=SerialCommands.read();
    Serial.print(commands[i+0],HEX);
    Serial.println("");
      if(commands[i]==-1)
        break;
      i++;
    }
  }
  //digitalWrite(RTS, LOW);

  //Serial.println("PRINT");
  
  /*i=0;
  while(i<MAX_SEQ_LENGTH){
    Serial.print(commands[i+0],DEC);
    Serial.print(" ");
    Serial.print(commands[i+1],DEC);
    Serial.print(" ");
    Serial.print(commands[i+2],DEC);
    Serial.println("");
    if(commands[i+2]==-1)
      break;
    i+=3;
  }*/
  
  //Serial.println("INJECT");
  i=0;
  while(commands[i+2]!=-1){
    SerialCommands.write(commands[i+0]);
    Serial.print(commands[i+0],HEX);
    pump_it(&commands[i]);
    i+=3;
  }
}





