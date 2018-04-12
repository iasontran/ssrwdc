// Group:          211
// Members:		   Derek McMullen			dmcmullen
// 				       Jake Reed				jakereed
//				       Chris Hughes        		cbhughes
// Date:          2 October 2017
// Assignment:    Lab 5
//----------------------------------------------------------------------//

#include "timer.h"

/* Initialize timer 0, you should not turn the timer on here. You will need to
* use CTC mode
*/
// void initTimer0(){
//   // set timer 0 to ctc mode with 8 prescaler
//   // for a microsecond timer
//   TCCR0B |= (1 << WGM02) | (1 << CS01);
//   OCR0A = 2;
// }

void initTimer1(){
// set timer 1 to ctc mode with 64 prescaler and enable interupt for
// output compare reg A, for interrupt every .000124s or almost 8khz

// OCRnA Equation: f(clock)/(prescaler * OCRnA) = f(timer interrupt)
  TCCR1B |= (1 << CS11) | (1 << CS10) | (1 << WGM12);
  OCR1A = 64; //4k
  TIMSK1 |= (1 << OCIE1A);

}

// /* This delays the program an amount specified by unsigned int delay.
// */
// void delayUs(unsigned int del){
// unsigned int x = 0;
// TIFR0 |= (1 << OCF0A);
// TCNT0 = 0x00;
// while (x < del){
// if (TIFR0 & (1 << OCF0A)){
//   x++;
//   TIFR0 |= (1 << OCF0A);
//    }
//  }
// }
