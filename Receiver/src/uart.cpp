#include "uart.h"


void USART_Init( unsigned int ubrr)
{
  UBRR0H = (unsigned char)(ubrr>>8);
  UBRR0L = (unsigned char)ubrr;
  UCSR0B = (1<<RXEN0)|(1<<TXEN0);;//enable rx tx
  UCSR0C = (1<<UCSZ00) | (1 << UCSZ01);//8 data 2 stop

  UBRR1H = (unsigned char)(ubrr>>8);
  UBRR1L = (unsigned char)ubrr;
  UCSR1B = (1<<RXEN1)|(1<<TXEN1);;//enable rx tx
  UCSR1C = (1<<UCSZ10) | (1 << UCSZ11);//8 data 1 stop

}

void USART0_Transmit(uint8_t data)
{
   /* Wait for empty transmit buffer */
   while ( !( UCSR0A & (1<<UDRE0)) );
   /* Put data into buffer, sends the data */
   UDR0 = data;
}
uint8_t USART0_receive(void){

 while(!(UCSR0A & (1<<RXC0)));
 return UDR0;

}
void USART1_Transmit(uint8_t data)
{
   /* Wait for empty transmit buffer */
   while ( !( UCSR1A & (1<<UDRE1)) );
   /* Put data into buffer, sends the data */
   UDR1 = data;
}
uint8_t USART1_receive(void){

 while(!(UCSR1A & (1<<RXC1)));
 return UDR1;

}
void USART0_Flush( void )
{
uint8_t dummy;
while ( UCSR0A & (1<<RXC0) ) dummy = UDR0;
}
void USART1_Flush( void )
{
uint8_t dummy;
while ( UCSR1A & (1<<RXC1) ) dummy = UDR1;
}
