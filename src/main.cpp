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
#include "timer.h"

// Libraries used for circular buffer
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>


#define BUFFER_SIZE 300
#define WAIT 0
#define MESSAGE_AVAILABLE 1
#define TIMER_INT 2

volatile uint8_t adcValue = 0;
volatile uint8_t adcValue2 = 0;
volatile int state = WAIT;

uint8_t queue[BUFFER_SIZE];
volatile int i = 0;
volatile int k = 0;
volatile int bufferFull = 0;

// Circular buffer struct
typedef struct {
  uint8_t *buffer;
  size_t head;
  size_t tail;
  size_t size;
} circular_buf_t;

// int circular_buf_reset(circular_buf_t * cbuf);
// int circular_buf_put(circular_buf_t * cbuf, uint8_t data);
// int circular_buf_get(circular_buf_t * cbuf, uint8_t * data);
// bool circular_buf_empty(circular_buf_t cbuf);
// bool circular_buf_full(circular_buf_t cbuf);
// static char *itohexa_helper(char *dest, unsigned x);
// char *itohexa(char *dest, unsigned x);

// Circular buffer functions
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



int main(void){
  sei();
//  Serial.begin(9600);
  //setUpADC();
  initSerial();
  setUpDAC();


  initTimer1();
//  Serial.println("Buffer Contents");
circular_buf_t rxCbuf;
 rxCbuf.size = BUFFER_SIZE;
 circular_buf_reset(&rxCbuf); // set head/tail to 0
 rxCbuf.buffer = malloc(rxCbuf.size);
while(1){
  if (state == MESSAGE_AVAILABLE){
    adcValue = receive_data();
    if(!circular_buf_full(rxCbuf)){
   circular_buf_put(&rxCbuf, adcValue);
 }
    state = WAIT;
  }
  else if (state == TIMER_INT){

    i = circular_buf_get(&rxCbuf,  &adcValue2);
    if(i == -1){
      circular_buf_reset(&rxCbuf);
    }
    else{
    PORTA = adcValue2;
     PORTC &= ~(1 << PORTC7);
    //_delay_us(125); //// need to adjust delay depending on how much delay comes
      // // // from the other programs
     PORTC |= (1 << PORTC7);
   }
     state = WAIT;

  }


}
}
// Timer one interrupt should be at 8khz per g.711 audio
// This timer should signal time to sample audio as well as when to
// apply to DAC when ran on receiving device
ISR(TIMER1_COMPA_vect){
state = TIMER_INT;
}
ISR(USART0_RX_vect){
  state = MESSAGE_AVAILABLE;
  }
