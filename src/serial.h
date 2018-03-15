#ifndef SERIAL_H
#define SERIAL_H

#include <Arduino.h>
#include <avr/io.h>

#define CPU_FREQ 16000000

void initSerial();
void transmit_data(uint8_t data[]);
void transmit_part(uint8_t data);
uint8_t receive_data();
void flush_data();

#endif
