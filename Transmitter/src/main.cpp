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

    char newChar ;
    // //char newChar ='B';
    //char inputString1[8] = "ABCDEFG\0";
    //char inputString2[13] = "print Bowen \0";
    char str[8] = "Hello   ";
    int a = 0;
    int i = 0;
    while(1)
    {
      if(a == 0) {

        i = (i+1)%8;
        str[6] = (char)(i+65);
      }
      //Serial_getString(str,13);
      //Serial_putString(str);
      newChar = str[a];
      a = (a+1)%8;
      //newChar = USART0_receive();
      USART0_Transmit(newChar);
      _delay_ms(100);
      // Serial_putString(inputString2);
      // // USART0_Transmit('B');
      //  _delay_ms(1000);

    }
  return 0;
}
