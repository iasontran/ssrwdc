#include "usart.h"

void initSerial(){
  UBRR0L = 8; // Baud rate 9600
  UCSR0B |= (1 << RXEN0 | 1 << TXEN0 | 1 << RXCIE0);// | 1 << RXCIE0); // Enable receiver and transmitter
  UCSR0C = (1 << USBS0) | (3 << UCSZ00); // Set frame format: 8 data, 2 stop bits
}

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

uint8_t receive_data(){

  while(!(UCSR0A & (1 << UDRE0))); // Wait for data to be received

return UDR0; // Get and return received data from buffer

}
