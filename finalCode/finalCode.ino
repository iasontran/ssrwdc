
/*
Secure Wireless Protocol
Team 17052

This code is devloped for the Arduino Mega 2560
Input: A0
CE, CS for nrf24l01: 48,49
CS for SD READER: 53

*/

#include <SD.h>
#include <RF24.h>
#include <SPI.h>
#include <RF24Audio.h>
#include <aes.hpp>
#include "printf.h"    // General includes for radio and audio lib

RF24 radio(48,49);    // Set radio up using pins 48 (CE) 49 (CS)
RF24Audio rfAudio(radio,0); // Set up the audio using the radio, and set to radio number 0
uint8_t keyOne[32]; //key in uint8_t format
int talkButton = 3;
File myFile;

void setup() {      
  delay(1000);
  Serial.begin(115200);
 Serial.print("Initializing SD card...");
delay(1000);
  while(!SD.begin(53)) {
    Serial.println("initialization failed!");
    //while (1);
  }
  Serial.println("initialization done.");

 

//**************GET KEY******************
  myFile = SD.open("test.txt", FILE_READ); //open file
   int i = 0; // loop variabl
   char temp;
   // if the file opened okay, read from it:
   if (myFile) {
     Serial.println("Reading from test.txt...");

     while (myFile.available()) {
       //as long as there is something to read, store it in key
         temp = myFile.read(); //note multiple keys may be stored in key
         Serial.print(temp, BIN);
         Serial.print(" ");
         keyOne[i] = (uint8_t) temp;
         Serial.print(keyOne[i], BIN); 
         Serial.println("");
         i++;

       }
       myFile.close();
}
     
     Serial.println("KEY:");
     for(int k=0; k<32;k++){
      Serial.println(keyOne[k], BIN);
     }
     Serial.println(" ");

  printf_begin();
  radio.begin();
  radio.printDetails();
  rfAudio.begin(keyOne);

 pinMode(talkButton, INPUT_PULLUP);
  //sets interrupt to check for button talk abutton press
  attachInterrupt(digitalPinToInterrupt(talkButton), talk, CHANGE);
  
  //sets the default state for each module to recevie

  // ************CHANGE FOR EACH RX/TX DEVICE, ie if device is reciever set to rfAudio.recieve(), 
  // if its transmitter, set to rfAudio.transmit()

rfAudio.receive();
//rfAudio.transmit();
}



// Called in response to interrupt. If sd card is out, change states to end transmission
// and call setup to re-init device

void talk()
{
  delay(2000);
   if (!digitalRead(talkButton)){
    
      // ************CHANGE FOR EACH RX/TX DEVICE, ie if device is transmitter set to rfAudio.recieve(), 
  // if its receiver, set to rfAudio.transmit()
   rfAudio.transmit();
//rfAudio.receive();

  }
  else{
  detachInterrupt(digitalPinToInterrupt(talkButton));
   Serial.println("CARD OUT");
    setup();
  }
}



void loop()
{
}
