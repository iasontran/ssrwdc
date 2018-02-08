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

#include <avr/io.h>
#include <SD_Reader.H>
#include <SD.H>
#include <Arduino.h>

int main(){
  sei();
  initiateSDReader();
  Serial.print("done");


  while(1){
//Serial.print(",");
  }

  return 0;
}
