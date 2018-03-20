//Author:
//Lab6

#include "SPI.h"

#include <avr/io.h>

void init_spi() {

  //MOSI, SCK, SS pins set to output
  //Interrupt enabled
  //Prescalar = 128
  //Master mode

  // Set CS pin as an output
  DDRB |= (1 << DDB0) | (1 << DDB1) | (1 << DDB2);
  //deassert_cs(); // set CS pin high
  PORTB &= ~((1 << PORTB0) | (1 << PORTB1) | (1 << PORTB2));
  // set SPI mode to 0 (default)
  assert_cs();//CS low
  // Set as master:
  SPCR |= (1 << MSTR);

  // set SPI clock rate.
  // Sparkfun says 125kHZ max, so we need a prescaler of 128
  SPCR |= (1 << SPR1) | (1 << SPR0);

  // Enable SPI module:
  SPCR |= (1 << SPE);
}

void send_spi(unsigned char value) {
  // Start conversion:
  SPDR = value;
  // wait until transfer is complete:
  while (!(SPSR & (1<<SPIF)));
}

void assert_cs() {
  // assert CS low
  PORTB &= ~(1 << PORTB0);
}

void deassert_cs() {
  // deassert CS
  PORTB |= (1 << PORTB0);
}
