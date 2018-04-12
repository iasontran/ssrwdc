// Author:
// Net ID:
// Date:
// Assignment:     Lab 4
//
//
// Requirements:
//----------------------------------------------------------------------//
#include "SD_Writer.h"
  /*
    SD card read/write

   This example shows how to read and write data to and from an SD card file
   The circuit:
   * SD card attached to SPI bus as follows:
   ** MOSI - pin 51
   ** MISO - pin 50
   ** CLK - pin 52
   ** CS - pin 53 (for MKRZero SD: SDCARD_SS_PIN)
   ** DO - PIN 50
   **DI - PIN51
   created   Nov 2010
   by David A. Mellis
   modified 9 Apr 2012
   by Tom Igoe

   This example code is in the public domain.

   */
  // #include <Arduino.h>
  #include <SPI.h>
  #include <SD.h>

  File myFileA;
  // set up variables using the SD utility library functions:
//use A17 portk7 pin 23 as pull-up resistor. when logic low card is inserted
//so when logic high do nothing
const int chipSelect = 53;

bool write(char* fileName, char* fileValue){

  Serial.begin(9600);
  PCICR |= 1 << PCIE2; //enable pins 23-16
  PCMSK2 |= 1 << PCINT23; // enable pin 23
  DDRK &= ~(1<< DDK7);
  PORTK |= (1 << PORTK7); //internal pullup resistor

   Serial.print("Initializing SD card...");
   // On the Ethernet Shield, CS is pin 4. It's set as an output by default.
   // Note that even if it's not used as the CS pin, the hardware SS pin
   // (10 on most Arduino boards, 53 on the Mega) must be left as an output
   // or the SD library functions will not work.
    pinMode(53, OUTPUT);

   if (!SD.begin(53)) {
     Serial.println("initialization failed!");
     return 0;
   }
   Serial.println("initialization done.");
   // open the file. note that only one file can be open at a time,
     // so you have to close this one before opening another.
     myFileA = SD.open(fileName, FILE_WRITE);

     // if the file opened okay, write to it:
     if (myFileA) {
       Serial.print("Writing to JAKE.txt...");
       myFileA.println(fileValue);
       // close the file:
       myFileA.close();
       Serial.println("done.");
     } else {
       // if the file didn't open, print an error:
       Serial.println("error opening JAKE.txt");
       return false;
     }

     // re-open the file for reading:
     myFileA = SD.open(fileName);
     if (myFileA) {
       Serial.println("JAKE.txt:");

       // read from the file until there's nothing else in it:
       while (myFileA.available()) {
         Serial.write(myFileA.read());
         return true;
       }
       // close the file:
       myFileA.close();
     } else {
       // if the file didn't open, print an error:
       Serial.println("error opening JAKE.txt");

     }
     return false;
   }
