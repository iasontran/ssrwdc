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
int state = 0; // set state 0
//End Includes//


int main(void){

  init(); //necessary for atom ide using arduino libraries
  sei();
  uint8_t key[getKeySize()]; //key in uint8_t format


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
    setKey(key);
    if(!isProgramExecuted())
    {
      state = 0;
      break;
    } //end if
    state = 1;
    break;
/////////end case 0//////////////
case 1:

    if (!isProgramExecuted())
    {
      state = 0;  //If program hasnt executed properly go to state 0
      break;
    }//end if
    else
     {
      Serial.print("."); //Wait
      delay(1000);
        break;
    }//end else
///////////////end case 1///////////////
}//End state machine


  }//end while(1)
return 0;
}//End main


//Interupt based on the card detect pin, when High do nothing//
ISR (PCINT2_vect){

  Serial.println("ERROR!!!:  \n No Card Inserted!");
    programExec(false); //if the card is removed reset program till
                              //card is inserted
    state = 0;                //set state back to 0
    delay(1000);              //delay to give card a chance to be fully inserted
    Serial.println("Checking For Card!");

}
//End Intererupt//


// Necessary for atom to run arduino libraries /////
void loop(){                                      //
  unsigned long z = millis(); //not needed        //
  Serial.println(z);          //not needed        //
}                                                 //
////////////////////////////////////////////////////
