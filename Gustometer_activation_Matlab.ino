#include <SoftwareSerial.h>

#define MAX_SEQ_LENGTH 100

SoftwareSerial SerialCommands(10, 11); // RX, TX


//pumps on digital I/O pin
int pumps[6] = {7, 6, 5, 4, 3, 2};
int * pumps_ptr = &pumps[0];
//Request To Send GPIO
int RTS = 13;

//commands list [pump_number, ml, wait(s)]...[-1, -1, -1]


byte commands[MAX_SEQ_LENGTH * 3];

//calibation value
int one_ml[6] = {600,   //0 //1
                 600,   //1 //2
                 600,   //2 //3
                 600,   //3 //4
                 600,   //4 //5
                 600    //5 //6
                };  
int * one_ml_ptr = &one_ml[0];

int i = 0;

void pump_it(char* command) {
  digitalWrite(pumps_ptr[(int)command[0]], HIGH);   // turn the PUMP on (HIGH is the voltage level)
  delay(((int)command[1])*one_ml_ptr[(int)command[0]]);              // inject `command[1]` ml
  digitalWrite(pumps_ptr[(int)command[0]], LOW);    // turn the PUMP off by making the voltage LOW
  delay(((int)command[2]) * 1000);              //  wait for `command[2]` seconds
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
  for (i = 0; i < 6; i++)
    pinMode(pumps[i], OUTPUT);
  pumps_ptr--;
  one_ml_ptr--;
}

int j = 0;

// the loop routine runs over and over again forever:
void loop() {
  Serial.println("RECEIVE");

  i = 0;
  digitalWrite(RTS, HIGH);
  while (i < MAX_SEQ_LENGTH) {
    if (SerialCommands.available()) {
      commands[i] = SerialCommands.read();
      Serial.print(commands[i],HEX);
      Serial.println("");
      if (commands[i] == 255)
        break;
      i++;
    }
  }
  
  digitalWrite(RTS, LOW);

  Serial.println("PRINT");

  i=0;
  while(i<MAX_SEQ_LENGTH){
    Serial.print(commands[i+0],DEC);
    Serial.print(" ");
    Serial.print(commands[i+1],DEC);
    Serial.print(" ");
    Serial.print(commands[i+2],DEC);
    Serial.println("");
    if(commands[i+2]==255)
      break;
    i+=3;
  }

  Serial.println("DEBUG");
  Serial.print(pumps_ptr[6], DEC);
  Serial.println("");
 
  Serial.println("INJECT");
  i = 0;
  while (commands[i + 2] != 255){
    SerialCommands.write(commands[i + 0]);
    Serial.print(commands[i + 0], HEX);
    pump_it((char*)&commands[i]);
    i += 3;
  }
}