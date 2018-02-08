// Author:
// Net ID:
// Date:
// Assignment:     Lab 4
//
//
// Requirements:
//----------------------------------------------------------------------//
#include "SD_Reader.h"
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

  #include <SPI.h>
  #include <SD.h>
  #include <Arduino.h>

  File myFile;
  // set up variables using the SD utility library functions:
//use A17 portk7 as pull-up resistor. when logic low card is inserted
//so when logic high do nothing
const int chipSelect = 53;

void initiateSDReader(){
  sei();


  Serial.begin(9600);

   Serial.print("Initializing SD card...");
   // On the Ethernet Shield, CS is pin 4. It's set as an output by default.
   // Note that even if it's not used as the CS pin, the hardware SS pin
   // (10 on most Arduino boards, 53 on the Mega) must be left as an output
   // or the SD library functions will not work.
    pinMode(53, OUTPUT);

   if (!SD.begin(53)) {
     Serial.println("initialization failed!");
     return;
   }
   Serial.println("initialization done.");

   // open the file. note that only one file can be open at a time,
   // so you have to close this one before opening another.
   myFile = SD.open("test.txt", FILE_WRITE);

   // if the file opened okay, write to it:
   if (myFile) {
     Serial.print("Writing to test.txt...");
     myFile.println("testing 1, 2, 3.");
 	// close the file:
     myFile.close();
     Serial.println("done.");
   } else {
     // if the file didn't open, print an error:
     Serial.println("error opening test.txt");
   }
 }

 void loop()
 {
   Serial.println("loop");
 	// nothing happens after setup
 }
