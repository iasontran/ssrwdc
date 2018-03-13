//Author:
//Lab6

#include "Timer.h"

/* Initialize timer 1, you should not turn the timer on here. You will need to
* use CTC mode
*/
void initTimer1(){
  TCCR1A &= ~(1 << WGM10 | 1 << WGM11);
  TCCR1B |= (1 << WGM12);
  TCCR1B &= ~(1 << WGM13);
}

/* This delays the program an amount specified by unsigned int delay.
*/
void delayUs(unsigned int delay){
  unsigned int numTicks = 2*delay - 1;
  // clear the timer
  TCNT1H = 0;
  TCNT1L = 0;
  // calculate the TOP value and assign it to OCR1A
  OCR1AH = numTicks >> 8;
  OCR1AL = numTicks & 0x00FF;
  // Turn on the timer
  TCCR1B |= (1 << CS11);
  // Do nothing while the OCF1A flag is not up
  while(!(TIFR1 & (1 << OCF1A)));
  // Clear the OCF1A flag
  TIFR1 |= (1 << OCF1A);
  // Turn off the timer
  TCCR1B &= ~(1 << CS11);
}
