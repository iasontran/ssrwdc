#include "serial.h"

void initSerial(){
  UBRR0L = 103; // Baud rate 9600
  UCSR0B |= (1 << RXEN0 | 1 << TXEN0 | 1 << RXCIE0);// | 1 << RXCIE0); // Enable receiver and transmitter
  UCSR0C = (1 << USBS0) | (3 << UCSZ00); // Set frame format: 8 data, 2 stop bits
}
