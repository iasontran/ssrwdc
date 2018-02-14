// Team:           17052
// Written by:		 Jake Reed
// Date:           2/1/2018
//----------------------------------------------------------------------//
#include "adc.h"
#include <Arduino.h>


int main(){
  sei();
  setUpADC();

  Serial.begin(9600);
  uint8_t adcValue = 0;
  while(1){
    adcValue = 0x00;
    adcValue = adcValue | ADCH;
    Serial.println(adcValue, BIN);
}
}
