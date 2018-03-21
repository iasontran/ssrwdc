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
   * SD card attached to SPI bus as follows:
   ** MOSI - pin 51
   ** MISO - pin 50
   ** CLK - pin 52
   ** CS - pin 53 (for MKRZero SD: SDCARD_SS_PIN)
   ** DO - PIN 50
   **DI - PIN51
*/

  #include <SPI.h>
  #include <SD.h>
  File myFile;
//Set up variables using the SD utility library functions:
//use A17 portk7 pin 23 as pull-up resistor. when logic low card is inserted
//so when logic high do nothing
const int chipSelect = 53;

bool initiateSDReader(){

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
    pinMode(53, OUTPUT); //Set pin 53 as output

/*Self Explanatory below*/
   if (!SD.begin(53)) {
     Serial.println("initialization failed!");
     return 0;
   }
   Serial.println("initialization done.");
return 1;
}
/**/
//   Grab key from file specified in function and place in variable passed in//
void getKey(char* key){

   // open the file. *note that only one file can be open at a time,
   // so you **have** to close this one before opening another.

   myFile = SD.open("test.txt", FILE_READ); //open file
   int i = 0; // loop variabl

   // if the file opened okay, read from it:
   if (myFile) {
     Serial.println("Reading from test.txt...");

     while (myFile.available()) {
       //as long as there is something to read, store it in key
         key[i] = myFile.read(); //note multiple keys may be stored in key
         i++;

       }
}
return;
     }

// close the file:
bool closeSDReader(){
     if(myFile){
     myFile.close();
  return 1;
}
  else{
  Serial.println("no file is open");
return 0;
}
return 0;

}
//Function for writing to a specified file. File name must be small.
void sdWrite(char* fileName, char* value){

  myFile = SD.open(fileName,FILE_WRITE);

//if file is opened, write to it:
 if (myFile){
  myFile.println(value);
  myFile.close();
  Serial.print("writing to: ");
  Serial.println(fileName);
}

else{

Serial.print("error file with name: ");
Serial.print(fileName);
Serial.print(" not created");


}

}
//function for reading a file
void sdRead(char* fileName){

  if (myFile){
    myFile.close();
  }
  myFile = SD.open(fileName,FILE_READ);
  if (myFile) {
    Serial.print("Reading from ");
    Serial.println(fileName);
    char* val;
    int i = 0;
    while (myFile.available()) {
        val[i] = myFile.read();
        Serial.print(val[i]);
        i++;
}
}

      }
