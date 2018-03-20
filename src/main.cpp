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


int main(void){
    sei();
  setUpADC();
  setUpDAC();
 // Serial.begin(9600);
  uint8_t adcValue = 0;




while(1){

    adcValue = ADCH;
    PORTA = adcValue;
    transmit_part(adcValue);

    PORTC &= ~(1 << PORTC7);
    _delay_us(125); //// need to adjust delay depending on how much delay comes
    // from the other programs
    PORTC |= (1 << PORTC7);
}
}
    /*
while(1){
  switch(state){
    case 0:
      if(!initiateSDReader()){
          state = 0;
          break;
        }
      delayMs(1000);
      getKey(x);
      closeSDReader();
      Serial.println("\nWhat the Function Returns:");
      j = 0;
      while (j<keySize){

        Serial.print(x[j]);
        key[j] = (uint8_t)(x[j]);
        j++;

//  Serial.print(j);
      }
      i = 0;
      Serial.println("\nWhat it returns in uint8_t format:");
      while(i<keySize){
        Serial.print(key[i]);
        i++;
      }

      Serial.println("\ndone printing var");
      Serial.println("program has executed...");
      programExecuted = true;




      state = 1;
      break;
case 1:

      if (!programExecuted){
        state = 0;
        break;
      }
      else {
        Serial.print(".");
        delay(1000);

  break;
            }
break;

}


}
//for(;;){
//  loop();
//}


  return 0;
}



void loop(){
  unsigned long z = millis();
  Serial.println(z);
}

ISR (PCINT2_vect){

  //do nothing

  Serial.println("ERROR!!!:  \n No Card Inserted!");
    programExecuted == false;
    state = 0;
    delay(1000);
    Serial.println("Checking For Card!");



}
*/
