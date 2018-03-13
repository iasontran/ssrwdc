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

    // //char newChar = 'A';
    // char newChar ='B';
    char outputString[100] = "";
    uint8_t newByte = 0;
    while(1)
    {

      // newChar = USART1_receive();
      // USART0_Transmit(newChar);
      // //USART1_Transmit(newChar);

      Serial_getString(outputString, 100);
      //Serial_putString(outputString);
      // newByte = convertToByte();
      // USART0_Transmit(newByte);
      //convertToAscii(newByte);
     ////_delay_ms(50);
    }
  return 0;
}
