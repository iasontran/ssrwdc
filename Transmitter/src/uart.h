#ifndef UART_H
#define UART_H
#include  <Arduino.h>
#include <stdio.h>
#include  <avr/interrupt.h>
#include  <util/delay.h>
#include  <avr/io.h>
#include <SoftwareSerial.h>
#define FOSC 16000000 //Clock Speed
#ifndef BAUD
#define BAUD 115200
#endif

#define MYUBRR 8

#ifndef F_CPU
#define F_CPU 16000000
#endif

void USART_Init(unsigned int ubrr);
void USART0_Transmit(unsigned char data);
unsigned char USART0_receive(void);
void USART1_Transmit(unsigned char data);
unsigned char USART1_receive(void);
void USART0_Flush( void );
void USART1_Flush( void );
#endif
