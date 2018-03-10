#ifndef SERIAL_H
#define SERIAL_H
#include "uart.h"
void initSerial();
void Serial_putString(const char[]);
void Serial_getString(char[], uint8_t);
uint8_t convertToByte(void);
/* takes in up to three ascii digits, converts them to a byte when press enter */
void convertToAscii(uint8_t byte);
/* Prints a byte out as its 3-digit ascii equivalent */
#endif
