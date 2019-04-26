// **********************************************
// * Receiver motor control
// * Connor Van Meter
// **********************************************

/*
Required connections between Arduino and qik 2s9v1:

      Arduino   qik 2s9v1
-------------------------
           5V - VCC
          GND - GND
Digital Pin 2 - TX
Digital Pin 3 - RX
Digital Pin 4 - RESET
*/

#include <SoftwareSerial.h> //for motor driver board
#include <PololuQik.h> //for motor driver board
#include <SPI.h> //*****************************
#include <nRF24L01.h> //for the transceiver
#include <RF24.h>
#include <printf.h>

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";

PololuQik2s9v1 qik(2, 3, 4);

int joyPos[2];

void setup()
{
  Serial.begin(115200);
  //printf_begin();
  Serial.println("qik 2s9v1 dual serial motor controller");
  
  qik.init();
  
  Serial.print("Firmware version: ");
  Serial.write(qik.getFirmwareVersion());
  Serial.println();
  radio.begin();
  radio.openReadingPipe(1, address); // 00001
  radio.setPALevel(RF24_PA_MIN);
}

void loop()
{
  delay(5);
  radio.startListening();
  //Serial.println("--------------------");
  //Serial.println("Waiting");
  //radio.printDetails();
  //Serial.println("--------------------");
  if ( radio.available()) {
    //Serial.println("--------------------");
    //Serial.println("Connected");
    while (radio.available()) {
      radio.read(&joyPos, sizeof(joyPos));
      Serial.print("Joystick - X value / joyPos[0]: ");
      Serial.print(joyPos[0]);
      Serial.println();
      Serial.print("Joystick - Y value / joyPos[1]: ");
      Serial.print(joyPos[1]);
      Serial.println();


      qik.setM1Speed(0); //Make sure no movement outside of joystick movement
      qik.setM0Speed(0); //Make sure no movement outside of joystick movement


      //--------------DON'T MOVE-----------------------//
      if((joyPos[1] == 510) and (507 <= joyPos[0] <= 509)){ // If Y-position is 0 and X-position is 0, then DON'T MOVE
        qik.setM1Speed(0); //right motor
        qik.setM0Speed(0); //left motor
        Serial.println("--------------------");
        Serial.println("DON'T MOVE");
        Serial.println("--------------------");
        Serial.println();
        Serial.println();        
      }
      //delay(5);

      //----------------GO FORWARD---------------------//
      if((500 <= joyPos[1] <= 520) and (joyPos[0] == 1023)){ // If Y-position is 0 and X-position is up, then 
        qik.setM1Speed(127); //right motor
        qik.setM0Speed(127); //left motor
        Serial.println("--------------------");
        Serial.println("GO FORWARD");
        Serial.println("--------------------");
        Serial.println();
        Serial.println();
      }
      //delay(5);

//      //--------------GO FORWARD *SPEED CONTROL* -----------------------//
//      if((500 <= joyPos[1] <= 520) and (600 <= joyPos[0] <= 1000)){ // If Y-position is 0 and X-position is right, then 
//        qik.setM1Speed(-63); //right motor
//        qik.setM0Speed(63); //left motor
//        Serial.println("GO FORWARD *SPEED CONTROL*");
//        Serial.println();
//        Serial.println();
//      }
//      //delay(5);

      //--------------GO BACKWARDS------------------------//
      if((500 <= joyPos[1] <= 520) and (joyPos[0] == 0)){ // If Y-position is left and X-position is 0, then 
        qik.setM1Speed(-127); //right motor
        qik.setM0Speed(-127); //left motor
        Serial.println("--------------------");
        Serial.println("GO BACKWARDS");
        Serial.println("--------------------");
        Serial.println();
        Serial.println();
      }
      //delay(5);

      //--------------TURN LEFT-----------------------//
      if((joyPos[1] == 0) and (490 <= joyPos[0] <= 527)){ // If Y-position is up and X-position is 0, then 
        qik.setM1Speed(127); //right motor
        qik.setM0Speed(-127); //left motor
        Serial.println("--------------------");
        Serial.println("TURN LEFT");
        Serial.println("--------------------");
        Serial.println();
        Serial.println();

      }
      //delay(5);
     
      //--------------TURN RIGHT--------------------------//
      if((joyPos[1] == 1023) and (490 <= joyPos[0] <= 527)){ // If Y-position is down and X-position is 0, then 
        qik.setM1Speed(-127); //right motor
        qik.setM0Speed(127); //left motor
        Serial.println("--------------------");
        Serial.println("TURN RIGHT");
        Serial.println("--------------------");
        Serial.println();
        Serial.println();

      }
     
      delay(5);
    }
  }
}
