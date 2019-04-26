// **********************************************
// * Transmitter motor control
// * Connor Van Meter
// **********************************************

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <printf.h>

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";
int joyPos[2];

void setup() {
  Serial.begin(115200);
  //printf_begin();
  radio.begin();
  radio.openWritingPipe(address); // 00001
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop() {
  delay(5);
    radio.stopListening();
    //int xValue = analogRead(A0);
    //delay(100); //A small delay is needed between analog pin
                  //reads, otherwise we get the same value twice
    //int yValue = analogRead(A1);

    

  joyPos[0] = analogRead(A0); //x position
  delay(100); //A small delay is needed between analog pin
              //reads, otherwise we get the same value twice
  joyPos[1] = analogRead(A1); //y position

  Serial.println("--------------------------------------------------"); //check what values the joystick is giving
  Serial.print("Joystick - X value: ");									//
  Serial.print(joyPos[0]);									            //
  Serial.println();														//
  Serial.print("Joystick - Y value: ");									//
  Serial.print(joyPos[1]);												//
  Serial.println();														//
  Serial.println();														//
  
  radio.write(&joyPos, sizeof(joyPos)); //Send the array with the joystick position
  //radio.printDetails();
  Serial.println("--------------------------------------------------");
  //radio.write(&xValue, sizeof(xValue));;
  //radio.write(&yValue, sizeof(yValue));;

  delay(5);
}
