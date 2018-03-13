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

    // char newChar = 'A';
    // //char newChar ='B';
    char inputString[100] = "this is the message to transmit \n\0";

    char inputString1[100] = "A \n\0";
    char inputString2[100] = "B \n\0";
    char inputString3[100] = "c \n\0";

    while(1)
    {
      // //newChar = USART1_receive();
      //  USART0_Transmit(newChar);
      //  USART1_Transmit(newChar);
      Serial_putString(inputString);
      _delay_ms(50);
      Serial_putString(inputString1);
      _delay_ms(50);
      Serial_putString(inputString2);
      _delay_ms(50);
      Serial_putString(inputString3);
      _delay_ms(50);
    }
  return 0;
}
