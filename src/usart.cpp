#include "usart.h"

void initSerial(){
  UBRR1L = 8; // Baud rate 9600
  UCSR1B |= (1 << RXEN1 | 1 << TXEN1 | 1 << RXCIE1);// | 1 << RXCIE0); // Enable receiver and transmitter
  UCSR1C = (1 << USBS1) | (3 << UCSZ10); // Set frame format: 8 data, 2 stop bits
}

void transmit_data(uint8_t data[]){
  int i = 0;

  while (data[i] != 0x00) {
    transmit_part(data[i]);
    i++;
  }

}

void transmit_part(uint8_t data) {
  while(!(UCSR1A & (1 << UDRE1))); // Wait for empty transmit buffer


  UDR1 = data; // Put data into buffer, sends the data
}

uint8_t receive_data(){

  while(!(UCSR1A & (1 << UDRE1))); // Wait for data to be received

return UDR1; // Get and return received data from buffer

}

//void flush_data(){
  //unsigned char dummy;
  //while(UCSR0A & (1 << RXC0)) dummy = UDR0;
//}
