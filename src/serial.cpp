
#include "serial.h"

void initSerial(){
  UBRR0L = 103; // Baud rate 9600
  UCSR0B |= (1 << RXEN0 | 1 << TXEN0 | 1 << RXCIE0);// | 1 << RXCIE0); // Enable receiver and transmitter
  UCSR0C = (1 << USBS0) | (3 << UCSZ00); // Set frame format: 8 data, 2 stop bits
}
<<<<<<< HEAD
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
  i = 0;
  while (i < (strLength - 1)) {
    newChar = USART0_receive();
    USART0_Transmit(newChar);
    if (newChar == '\0') {
      break;
    }
    else {
      str2[i] = newChar;
      i++;
    }
  }
  str2[i] = 0;
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
=======

void transmit_data(uint8_t data[]){
  int i = 0;

  while (data[i] != 0x00) {
    transmit_part(data[i]);
    i++;
  }
  
}

void transmit_part(uint8_t data) {
  while(!(UCSR0A & (1 << UDRE0))); // Wait for empty transmit buffer


  UDR0 = data; // Put data into buffer, sends the data
}

unsigned char receive_data(){
  //while(!(UCSR0A & (1 << RXC0))); // Wait for data to be received
  return UDR0; // Get and return received data from buffer
}

//void flush_data(){
  //unsigned char dummy;
  //while(UCSR0A & (1 << RXC0)) dummy = UDR0;
//}
>>>>>>> 86ef2a16af433e9794dcadf98fee3a3631927799
