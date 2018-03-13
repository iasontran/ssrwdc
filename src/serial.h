#ifndef SERIAL_H
#define SERIAL_H

#include <Arduino.h>
#include <avr/io.h>

#define CPU_FREQ 16000000

void initSerial();
<<<<<<< HEAD
void Serial_putString(const char[]);
void Serial_getString(char[], uint8_t);
uint8_t convertToByte(void);
/* takes in up to three ascii digits, converts them to a byte when press enter */
void convertToAscii(uint8_t byte);
/* Prints a byte out as its 3-digit ascii equivalent */
=======
void transmit_data(uint8_t data[]);
void transmit_part(uint8_t data);
unsigned char receive_data();
void flush_data();

>>>>>>> 86ef2a16af433e9794dcadf98fee3a3631927799
#endif
