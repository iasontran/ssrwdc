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

#define BUFFER_SIZE 32
#define FALSE 0
#define TRUE 1

volatile uint8_t adcValue = 0;
uint8_t queue[BUFFER_SIZE];
int i = 0;
volatile int bufferFull = 0;

int main(void){
  sei();
  Serial.begin(9600);
  setUpADC();
// initSerial();
//  setUpDAC();
  initTimer1();
  int k =0;
//  Serial.println("Buffer Contents");
while(1){
   //Serial.println(bufferFull);
  // Serial.println(i);


  if (bufferFull == 1){
      // Transmit buffer
      Serial.println("Contents");
      for(k =0;k<BUFFER_SIZE;k++){
        Serial.println(queue[k], BIN); // change to usart transmit
      }
      i = 0;
      bufferFull = 0;

  }

  //transmit_part(adcValue);
//Serial.println(adcValue);
  // PORTA = adcValue;
  //  PORTC &= ~(1 << PORTC7);
  // //_delay_us(125); //// need to adjust delay depending on how much delay comes
  //   // // // from the other programs
  //  PORTC |= (1 << PORTC7);
}
}

// Timer one interrupt should be at 8khz per g.711 audio
// This timer should signal time to sample audio as well as when to
// apply to DAC when ran on receiving device
ISR(TIMER1_COMPA_vect){
if(bufferFull == 0){
if(i < BUFFER_SIZE){
  queue[i] = ADCH;
  i++;

}
if(i == (BUFFER_SIZE)){
  bufferFull = 1;
}
}
}
// ISR(USART0_RX_vect){
//
//
//     adcValue = receive_data();
//
//   }
