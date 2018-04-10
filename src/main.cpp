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
#include "adc.h"
#include <util/delay.h>
#include <avr/io.h>
#include "usart.h"
#include "timer.h"

volatile uint8_t adcValue = 0;

int main(void){
  sei();
  setUpADC();
  initSerial();
//  setUpDAC();
  initTimer1();

while(1){

 adcValue = ADCH;

//   //transmit_part(adcValue);
// //Serial.println(adcValue);
//   // PORTA = adcValue;
//   //  PORTC &= ~(1 << PORTC7);
//   // //_delay_us(125); //// need to adjust delay depending on how much delay comes
//   //   // // // from the other programs
//   //  PORTC |= (1 << PORTC7);
 }
}

// Timer one interrupt should be at 8khz per g.711 audio
// This timer should signal time to sample audio as well as when to
// apply to DAC when ran on receiving device
ISR(TIMER1_COMPA_vect){
  transmit_part(adcValue);
}
// ISR(USART0_RX_vect){
//
//
//     adcValue = receive_data();
//
//   }
