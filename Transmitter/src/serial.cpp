#include "serial.h"
void initSerial(){
  USART_Init(MYUBRR);
}
void Serial_putString(const char str1[]){
  uint8_t i = 0;
  for (i = 0; i < 14; i++) {
    USART0_Transmit((str1[i]));
    //if(str1[i] == "\n"){
    //  return;
    //}
  }
}
void Serial_getString(char str2[], uint8_t strLength){
  char newChar;
  uint8_t i;
  for (i = 0; i < strLength; i++) {
    newChar = USART0_receive();
    //USART0_Transmit(newChar);
    if (newChar == '\0') {
      break;
    }
    else
      str2[i] = newChar;
  }
  str2[13] = '\0';
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
