//Author:
//Lab6

#ifndef SPI_H
#define SPI_H

#include <avr/io.h>

void init_spi();
void send_spi(unsigned char value);
void assert_cs();
void deassert_cs();

#endif
