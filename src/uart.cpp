#include "uart.h"

int test(void)
{
   USART_Init(MYUBRR); //MYUBRR = 51 for current settings
   char newChar = "A";
   while(1)
   {
     //newChar = Serial.read();
     newChar = USART_receive();
      USART_Transmit(newChar);
	  _delay_ms(50);
   }
}

void USART_Init( unsigned int ubrr)
{
  UBRR0H = (unsigned char)(ubrr>>8);
  UBRR0L = (unsigned char)ubrr;
  UCSR0B = (1<<RXEN0)|(1<<TXEN0);;//enable rx tx
  UCSR0C = (1<<UCSZ00) | (1 << UCSZ01);//8 data 1 stop

  UBRR1H = (unsigned char)(ubrr>>8);
  UBRR1L = (unsigned char)ubrr;
  UCSR1B = (1<<RXEN1)|(1<<TXEN1);;//enable rx tx
  UCSR1C = (1<<UCSZ10) | (1 << UCSZ11);//8 data 1 stop

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
