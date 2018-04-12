// Author:
// Net ID:
// Date:
// Assignment:     Lab 4
//
// Description: This file contains a programmatic overall description of the
// program. It should never contain assignments to special function registers
// for the exception key one-line code such as checking the state of the pin.
//
// Requirements:
//----------------------------------------------------------------------//
#include <Arduino.h>
#include "adc.h"
#include <util/delay.h>
#include <avr/io.h>
#include "usart.h"
// TX TIMER
#include "timer.h"

// RX
#include <util/delay.h>
#include "lcd.h"

// Libraries used for circular buffer
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#define BUFFER_SIZE 32
#define FALSE 0
#define TRUE 1

volatile uint8_t adcValue = 0;
uint8_t queue[BUFFER_SIZE];
volatile int i = 0;
volatile int bufferFull = 0;
volatile uint8_t value = 0;
volatile bool receivedVal = false;

// Circular buffer struct
typedef struct {
  uint8_t *buffer;
  size_t head;
  size_t tail;
  size_t size;
} circular_buf_t;

int circular_buf_reset(circular_buf_t * cbuf);
int circular_buf_put(circular_buf_t * cbuf, uint8_t data);
int circular_buf_get(circular_buf_t * cbuf, uint8_t * data);
bool circular_buf_empty(circular_buf_t cbuf);
bool circular_buf_full(circular_buf_t cbuf);
static char *itohexa_helper(char *dest, unsigned x);
char *itohexa(char *dest, unsigned x);

// Circular buffer functions

int circular_buf_reset(circular_buf_t * cbuf) {
  int r = -1;
  if(cbuf) {
    cbuf->head = 0;
    cbuf->tail = 0;
    r = 0;
  }
  return r;
}

int circular_buf_put(circular_buf_t * cbuf, uint8_t data) {
  int r = -1;
  if(cbuf) {
    cbuf->buffer[cbuf->head] = data;
    cbuf->head = (cbuf->head + 1) % cbuf->size;

    if(cbuf->head == cbuf->tail) {
      cbuf->tail = (cbuf->tail + 1) % cbuf->size;
    }

    r = 0;
  }
  return r;
}

int circular_buf_get(circular_buf_t * cbuf, uint8_t * data) {
  int r = -1;

  if(cbuf && data && !circular_buf_empty(*cbuf)) {
    *data = cbuf->buffer[cbuf->tail];
    cbuf->tail = (cbuf->tail + 1) % cbuf->size;

    r = 0;
  }

  return r;
}

bool circular_buf_empty(circular_buf_t cbuf) {
// We define empty as head == tail
  return (cbuf.head == cbuf.tail);
}

bool circular_buf_full(circular_buf_t cbuf) {
// We determine "full" case by head being one position behind the tail
// Note that this means we are wasting one space in the buffer!
// Instead, you could have an "empty" flag and determine buffer full that way
  return ((cbuf.head + 1) % cbuf.size) == cbuf.tail;
}

int main(void){
  sei();
  initTimer1();
  initSerial();
  initLCD();
  // Serial.begin(9600);
  // setUpADC();
  //  setUpDAC();
  //  Serial.println("Buffer Contents");

  // circular_buf_t txCbuf;
  // txCbuf.size = 32;
  // circular_buf_reset(&txCbuf); // set head/tail to 0
  // txCbuf.buffer = malloc(txCbuf.size);

  DDRB |= (1 << DDB7);
  circular_buf_t rxCbuf;
  rxCbuf.size = 84;
  circular_buf_reset(&rxCbuf); // set head/tail to 0
  rxCbuf.buffer = malloc(rxCbuf.size);
  displayOn();
  // char display[8];

  while(1){
  // Serial.println(bufferFull);
  // Serial.println(i);

  // TX CODE BEGIN
  // Populate buffer with uint8_t block values from ADC
  // for (unsigned int k = 0; k < txCbuf.size; k++) {
  //   circular_buf_put(&txCbuf, queue[k]);
  // }

  // Retrieve data from buffer to transmit
  // while(!circular_buf_empty(txCbuf)) {
  //   uint8_t data;
  //   circular_buf_get(&txCbuf, &data);
  //   Serial.print("Transmitting value from ADC: ");
  //   Serial.println(data);
  //   transmit_part(data);
  // }
  // i = 0; // Reset ADC interrupt buffer count
  // TX CODE END

  // RX CODE BEGIN
  // If a USART value is received, begin putting value into buffer
  if (receivedVal) {
    circular_buf_put(&rxCbuf, adcValue);
    receivedVal = false;
  }
  // If a buffer is full, proceed with grabbing buffer values
  if (circular_buf_full(rxCbuf)) {
    for (unsigned int k = 0; k < rxCbuf.size; k++) {
      circular_buf_get(&rxCbuf, &queue[k]);
      writeString(queue[k]);
      if (queue[k] == 255) {
        // PORTB |= (1 << PORTB7);
        // _delay_ms(250.0);
        // PORTB ^= (1 << PORTB7);
      }
    }
  }
  // RX CODE END

  /*
    if (bufferFull == 1){
      // Transmit buffer
      //  Serial.println("Contents");
      for(int k =0; k < BUFFER_SIZE; k++){
        transmit_part(queue[k]); // change to usart transmit
      }

      i = 0;
      bufferFull = 0;
    }
  */
//
// adcValue = ADCH;
// transmit_part(adcValue);
//   //transmit_part(adcValue);
// //Serial.println(adcValue);
//   // PORTA = adcValue;
//   //  PORTC &= ~(1 << PORTC7);
//   // //_delay_us(125); //// need to adjust delay depending on how much delay comes
//   //   // // // from the other programs
//   //  PORTC |= (1 << PORTC7);
  }
}

static char *itohexa_helper(char *dest, unsigned x) {
  if (x >= 16) {
    dest = itohexa_helper(dest, x/16);
  }
  *dest++ = "0123456789abcdef"[x & 15];
  return dest;
}

char *itohexa(char *dest, unsigned x) {
  *itohexa_helper(dest, x) = '\0';
  return dest;
}

// Timer one interrupt should be at 8khz per g.711 audio
// This timer should signal time to sample audio as well as when to
// // apply to DAC when ran on receiving device
//  ISR(TIMER1_COMPA_vect) {
//
//   if(i < BUFFER_SIZE) {
//     queue[i] = ADCH;
//     i++;
//   }
//
//
//   /*
//   if(bufferFull == 0) {
//     if(i < BUFFER_SIZE) {
//       queue[i] = ADCH;
//       i++;
//     }
//     if(i == (BUFFER_SIZE)) {
//       bufferFull = 1;
//     }
//   }
//   */
// }

ISR(USART0_RX_vect){
  adcValue = receive_data();
  receivedVal = true;
}
