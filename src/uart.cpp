#include "uart.h"
#include <avr/io.h>

#define FOSC 16000000 //Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1
#define F_CPU 16000000

#include  <avr/io.h>
#include  <Arduino.h>
#include  <avr/interrupt.h>
#include  <util/delay.h>
// #include
// #include
// #include


int test(void)
{
  USART_Init(MYUBRR); //MYUBRR = 51 for current settings
  char newChar = 'A';
  while(1)
  {
    newChar = USART_receive();
     USART_Transmit(newChar);
   _delay_ms(50);
  }
}

void USART_Init( unsigned int ubrr)
{
   /* Set baud rate */
   UBRR0H = (unsigned char)(ubrr>>8);
   UBRR0L = (unsigned char)ubrr;

   /* Enable receiver and transmitter */
   UCSR0B = (1<<RXEN0)|(1<<TXEN0);
   /* Set frame format: 8data, 2stop bit */
  // UCSR0C = (1<<USBS0)|(3<<UCSZ00);

    UCSR0C = (!(1<<USBS0))|(1<<UCSZ01)|(1<<UCSZ00);
}

void USART_Transmit(unsigned char data)
{
   /* Wait for empty transmit buffer */
   while ( !( UCSR0A & (1<<UDRE0)) );
   /* Put data into buffer, sends the data */
   UDR0 = data;
}
unsigned char USART_receive(void){

 while(!(UCSR0A & (1<<RXC0)));
 return UDR0;

}
