// Author:
// Net ID:
// Date:
// Assignment:
//
// Description: File description
//----------------------------------------------------------------------//
#include <avr/io.h>
#include <avr/interrupt.h>
//#include <Arduino.h>
#include "Timer.h"
#include <string.h>
#include "serial.h"
int main() {
  initSerial();

    char newChar;
    // //char newChar ='B';
    char inputString1[13] = "Hello world \0";
    char inputString2[13] = "print Bowen \0";
    char str[13] = "";

    while(1)
    {

      //Serial_getString(str,13);
      //Serial_putString(str);
      //newChar = USART0_receive();
      newChar = 'A';
      USART0_Transmit(newChar);
      //_delay_ms(1000);
      // Serial_putString(inputString2);
      // // USART0_Transmit('B');
      //  _delay_ms(1000);

    }
  return 0;
}
