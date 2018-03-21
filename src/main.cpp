// Author:
// Net ID:
// Date:
// Assignment:     Lab 4
//
// Description: This file contains a programmatic overall description of the
// program. It should never contain assignments to special function registers
// for the exception key one-line code such as checking the state of the pin.
//
// Requirements:
//----------------------------------------------------------------------//

//Begin Includes//
#include <Arduino.h>
#include <avr/io.h>
#include "timer.h"
#include <SD_Reader.H>
#include <SD_writer.H>
//End Includes//

//begin Glabal Variavles//
bool programExecuted = false;
bool written = false;
const int keySize = 32; //32 bytes 256 bits
int state = 0; // set state 0
//end Glabal Variables//

int main(void){

  init(); //necessary for atom ide using arduino libraries
  sei();

  char x[keySize]; //Holds key in char format
  uint8_t key[keySize]; //key in uint8_t format
  int j,i; //loop variables

  /*char* fileName = "Write.txt"; //File name here, must be small
  char* fileValue = "Custom words";//whatever you want to write here
      int n = 0;
write(fileName,fileValue);
}*/

while(1){
  /*begin State Machine
    0 =  grab the keySize
    1 = Key is grabbed do nothing unless program hasnt executed
  */
  switch(state){
    case 0:
      if(!initiateSDReader()){
          state = 0; //If the SDReader isnt properly initialized try again
          break;
        }
      delayMs(1000); // delay to allow sd card to be read
      getKey(x);
      closeSDReader();
      Serial.println("\nWhat the Function Returns:"); //output for debugging
      j = 0; //Set loop variable to 0
      while (j<keySize){
        Serial.print(x[j]); //print out each value of x up to the keySize
        key[j] = (uint8_t)(x[j]);
        j++;

//  Serial.print(j);
      }
      i = 0; //set loop value to zero
      Serial.println("\nWhat it returns in uint8_t format:"); //output for debugging
      while(i<keySize){
        Serial.print(key[i]);
        i++;
      }

      Serial.println("\ndone printing var");
      Serial.println("program has executed...");
      programExecuted = true; //program has executed properly
                              //Key should now be stored in both 'x' and 'key'


      state = 1;
      break;
case 1:

      if (!programExecuted){
        state = 0;  //If program hasnt executed properly go to state 0
        break;
      }
      else {
        Serial.print("."); //Wait
        delay(1000);

  break;
            }
break;

}//End state machine


} //end while



  return 0;
}


// Necessary for atom to run arduino libraries /////
void loop(){                                      //
  unsigned long z = millis(); //not needed        //
  Serial.println(z);          //not needed        //
}                                                 //
////////////////////////////////////////////////////

//Interupt based on the card detect pin, when High do nothing//
ISR (PCINT2_vect){

  Serial.println("ERROR!!!:  \n No Card Inserted!");
    programExecuted == false; //if the card is removed reset program till
                              //card is inserted
    state = 0;                //set state back to 0
    delay(1000);              //delay to give card a chance to be fully inserted
    Serial.println("Checking For Card!");

}
//End Intererupt//
