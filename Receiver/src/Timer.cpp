/// Author:         Garrett Vanhoy
// Net ID:         gvanhoy
// Date:           28 January 2017
// Assignment:     Lab 3
//----------------------------------------------------------------------//

#include "timer.h"

/* Initialize timer 0, you should not turn the timer on here. You will need to
* use CTC mode
*/
#include <avr/io.h>

#define F_OSC (16000000)
#define PRESCALER (64)
#define PERIOD (0.001)


void initTimer0(){
  // set the timer mode to CTC
  ////TCCR0A |= (1 << WGM01)

  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS11);

  // set the prescaler to 8
  ////TCCR0B |= (1 << CS01);
  // set the period OCR
  //OCR0A = (F_OSC/PRESCALER) * PERIOD;

  // TODO: enable interrupt:
  //TIMSK0 |= (1 << OCIE0A);
 }
// bool timer_flag_raised() {
//   return TIFR0 & (1 << OCF0A);
// }
//
// void clear_timer_flag() {
//   TIFR0 |= (1 << OCF0A);
// }

/* This delays the program an amount specified by unsigned int delay.
*/
void delayUs(unsigned int delay){
  // OCR0A = 2*delay;
  //
  //calculate number of ticks
  unsigned int delays = 2 * delay -1;
  // calculate the TOP value and assign it to OCR1A
  OCR1AH = delays >> 8;
  //16 bit register
  OCR1AL = delays & 0x00FF;
  // // Make sure the flag is down:
  // clear_timer_flag();
  //
  // // Clear the timer:
  // TCNT0 = 0;
  //
  // clear the timer
  TCNT1H = 0;
  TCNT1L = 0;
  // // Set prescaler to 8 AND turn on timer:
  // TCCR0B |= (1 << CS01);
  //

  // Turn on the timer
  TCCR1B |= (1 << WGM12);
  //
  TCCR1B |= (1 << CS11);
  // // Poll flag until set:
  // while (!timer_flag_raised());
  //

  // Do nothing while the OCF0A flag is not up
  while (!(TIFR1 & (1 << OCF1A)));
  // TCCR0B &= ~((1 << CS02) | (1 << CS01) | (1 << CS00));

  // Clear the OCF0A flag
  TIFR1 |= (1 << OCF1A);
  // Turn off the timer
  TCCR1B &= ~(1 << CS10 | 1 << CS11 | 1 << CS12);
}
