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
#include <Arduino.h>

#include <avr/io.h>
#include "timer.h"
//#include <>
#include <SD_Reader.H>
//#include <SD.H>
//#include <WProgram.h>

int main(void){

  init();
  sei();
  initiateSDReader();
  Serial.print("done");
  char x[64];
  getKey(x);
  closeSDReader();
  Serial.println();
  int j = 0;
while (x[j]){
  Serial.print(x[j]);
  j++;
//  Serial.print(j);
}
Serial.println("\ndone printing var");

while(1){}
//for(;;){
//  loop();
//}


  return 0;
}



void loop(){
  unsigned long z = millis();
  Serial.println(z);
}
