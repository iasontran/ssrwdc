#include "serial.h"
#include <string.h>
void initSerial(){
  USART_Init(MYUBRR);
}
void Serial_putString(const char str1[]){
  uint8_t i = 0;
  while (str1[i]) {
    USART0_Transmit((str1[i]));
    i++;
  }
}
void Serial_getString(char str2[], uint8_t strLength){
  char newChar;
  uint8_t i;
  char len[3];
  for (i = 0; i < strLength+1; i++) {
    newChar = USART0_receive();
    //USART0_Transmit(newChar);
    if (newChar == '\0' || newChar == '\r' ) {
      //USART0_Flush();
      //str2[i] = '\0';
      itoa(i, len, 10);
      sprintf(&str2[13], "%s", len);
      return;
    }
    else
      str2[i] = newChar;
  }
  itoa(i, len, 10);
  sprintf(&str2[i], "%s", len);
  //str2[i] = i;
  //USART0_Flush();
}

uint8_t convertToByte(void) {
  // Gets a numerical 0-255 from the serial port.
  // Converts from string to number.
  char hundreds = '0';
  char tens = '0';
  char ones = '0';
  char thisChar = '0';
  do {
    hundreds = tens;
    tens = ones;
    ones = thisChar;
    thisChar = USART0_receive();
    USART0_Transmit(thisChar);
  } while (thisChar != '\r');
  return (100 * (hundreds - '0') + 10 * (tens - '0') + ones - '0');
}

void convertToAscii(uint8_t byte) {
  USART0_Transmit('0' + (byte / 100));
  USART0_Transmit('0' + ((byte / 10) % 10));
  USART0_Transmit('0' + (byte % 10));
}
