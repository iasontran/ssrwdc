// Author:
// Net ID:
// Date:
// Assignment:     Lab 3
//
// Description: This file contains a programmatic overall description of the
// program. It should never contain assignments to special function registers
// for the exception key one-line code such as checking the state of the pin.
//
// Requirements:
//----------------------------------------------------------------------//

#include <avr/io.h>
#include "lcd.h"
#include "timer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <Arduino.h>
#include "SPI.h"
#include "serial.h"
int main(){
  init_spi();
  int a = 0;
  int i = 0b00000001;
  int j = 0b00000001;

  initTimer0();
  initLCD();
  initSerial();
  moveCursor(0, 0);

  char str1[40] = "";
  char str2[40] = "";
  char str3[40] = "";
  char newChar;
  // //
  // //
   while(1){
    assert_cs();
    send_spi(~i);
    send_spi(j);
    i = i << 1;
    if(i > 0b10000000){
      i = 1;
      j = j << 1;
    }
    //j = j << 1;
    if(j > 0b10000000){
      j = 1;
    }
    deassert_cs();
    assert_cs();

    newChar = USART1_receive();
    //USART1_Transmit(newChar);
    str1[a] = newChar;
    a = (a+1)%8;
    if (a == 0){
      initLCD();
      writeString(str1);
    }

    /*
    Serial_getString(str2, 13);
    //sprintf(str2, "%c", USART0_receive());
    initLCD();
    sprintf(str1, "The input is");
    writeString(str1);
    moveCursor(1, 0);
    //Serial_getString(str2, 20);
    //Serial.print(str2);
    //sprintf(str2, "%s", str3);
    writeString(str2);
    //sprintf(str2, "\0");
    //strcpy(str3, "");
    //sprintf(str2, "");
    // strcpy(str3, str1);
    // strcat(str3, str2);
    // strcat(str3, "\n");
    // Serial.write(str3);
*/
    //USART0_Flush();

  }

   return 0;
}
