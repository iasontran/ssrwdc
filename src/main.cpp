// Team:           17052
// Written by:		 Jake Reed
// Date:           2/1/2018
//----------------------------------------------------------------------//
#include "adc.h"
#include <Arduino.h>
#include <util/delay.h>

int main(){
  sei();
  setUpADC();
  setUpDAC();
  Serial.begin(9600);
  uint8_t adcValue = 0;
  while(1){

    adcValue = ADCH;
    PORTA = adcValue;
    PORTC &= ~(1 << PORTC7);
    _delay_us(125); //// need to adjust delay depending on how much delay comes
    // from the other programs
    PORTC |= (1 << PORTC7);
}
}
