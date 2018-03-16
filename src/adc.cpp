// Team:           17052
// Written by:		 Jake Reed
// Date:           2/1/2018
//----------------------------------------------------------------------//

#include <avr/io.h>
#include <util/delay.h>
#include "ADC.h"

void setUpDAC(){
  DDRA |= (1 << DDA0) | (1 << DDA1) | (1 << DDA2) | (1 << DDA3) | (1 << DDA4) | (1 << DDA5) | (1 << DDA6) | (1 << DDA7);
  DDRC |= (1 << DDC7);
}
void setUpADC(){

//AREF set to reference voltage (5V)
ADMUX |= (1 << REFS0);
ADMUX &= ~(1 << REFS1);

// Set to 8-bit precision so read ADCH reg for 8bit result
ADMUX |= (1 << ADLAR);

//set ADC0 as single ended input with mux [5:0] = 0b00000000
ADMUX &= ~((1 << MUX4) | (1 << MUX3) | (1 << MUX2) | (1 << MUX1) | (1 << MUX0));
ADCSRB &= ~(1 << MUX5);

// set in free running mode
ADCSRB &= ~(1 << ADTS2 | 1 << ADTS1 | 1 << ADTS0);

// enable auto triggering and turn on ADC
ADCSRA |= (1 << ADATE) | (1 << ADEN);

// set the pre-scaler to 128 which should be ~9600 hz for sample freq
ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

//disable ADC pin 0 digital input
DIDR0 |= (1 << ADC0D);

//start the first conversion
ADCSRA |= (1 << ADSC);

}
