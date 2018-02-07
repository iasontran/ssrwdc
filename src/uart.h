#ifndef UART_H
#define UART_H

// void init_uart();
// void send_uart(unsigned char data);
void USART_Init(unsigned int ubrr);
void USART_Transmit(unsigned char data);
int test(void);

#endif
