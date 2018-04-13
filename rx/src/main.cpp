/*
 *
 *
 *
 */
#include <Arduino.h>
#include <avr/io.h>
#include <SD_Reader.H>
#include <SD_writer.H>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "aes.hpp"
#include "timer.h"
#include "lcd.h"
#include "led.h"

// Libraries used for circular buffer
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "adc.h"
#include <util/delay.h>
#include "usart.h"

#define BUFFER_SIZE 64
#define WAIT 0
#define MESSAGE_AVAILABLE 1
#define TIMER_INT 2

uint8_t* test_encrypt_cbc(uint8_t *key);
static void test_decrypt_cbc(uint8_t *key, uint8_t *input);
static void phex(uint8_t* str);
static void test_encrypt_ctr(void);
static void test_decrypt_ctr(void);
volatile uint8_t received;
volatile uint8_t received_block[64];
volatile int received_cnt;
int state = 0;

volatile int j = 0;
volatile int k = 0;
uint8_t adcValue = 0;
uint8_t adcValue2 = 0;
volatile int state2 = WAIT;
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

int main() {
  init(); // Initialization due to use of Arduino libraries
  sei();
  initSerial();
  initTimer1();
  setUpDAC();
  initSerial();

  // Hardcoded initialization vector for encryption/decryption
  uint8_t iv[]  = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f };
  // Input plaintext block array to be passed through encryption and decryption
  uint8_t in[]  = { 0xf5, 0x8c, 0x4c, 0x04, 0xd6, 0xe5, 0xf1, 0xba, 0x77, 0x9e, 0xab, 0xfb, 0x5f, 0x7b, 0xfb, 0xd6,
                    0x9c, 0xfc, 0x4e, 0x96, 0x7e, 0xdb, 0x80, 0x8d, 0x67, 0x9f, 0x77, 0x7b, 0xc6, 0x70, 0x2c, 0x7d,
                    0x39, 0xf2, 0x33, 0x69, 0xa9, 0xd9, 0xba, 0xcf, 0xa5, 0x30, 0xe2, 0x63, 0x04, 0x23, 0x14, 0x61,
                    0xb2, 0xeb, 0x05, 0xe2, 0xc3, 0x9b, 0xe9, 0xfc, 0xda, 0x6c, 0x19, 0x07, 0x8c, 0x6a, 0x9d, 0x1b };
  // Expected plaintext block to be used for testing
  uint8_t ptx[]  = { 0xf5, 0x8c, 0x4c, 0x04, 0xd6, 0xe5, 0xf1, 0xba, 0x77, 0x9e, 0xab, 0xfb, 0x5f, 0x7b, 0xfb, 0xd6,
                    0x9c, 0xfc, 0x4e, 0x96, 0x7e, 0xdb, 0x80, 0x8d, 0x67, 0x9f, 0x77, 0x7b, 0xc6, 0x70, 0x2c, 0x7d,
                    0x39, 0xf2, 0x33, 0x69, 0xa9, 0xd9, 0xba, 0xcf, 0xa5, 0x30, 0xe2, 0x63, 0x04, 0x23, 0x14, 0x61,
                    0xb2, 0xeb, 0x05, 0xe2, 0xc3, 0x9b, 0xe9, 0xfc, 0xda, 0x6c, 0x19, 0x07, 0x8c, 0x6a, 0x9d, 0x1b };
  uint8_t adcVal[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };


  uint8_t key[getKeySize()]; //key in uint8_t format
  uint8_t *text;
  struct AES_ctx ctx1;
  struct AES_ctx ctx2;

  circular_buf_t rxCbuf;
  rxCbuf.size = BUFFER_SIZE;
  circular_buf_reset(&rxCbuf); // set head/tail to 0
  rxCbuf.buffer = malloc(rxCbuf.size);

  AES_init_ctx_iv(&ctx2, key, iv);
  uint8_t decrypted[64];

  while(1) {
    /*
     * State Machine:
     * 0 = Grab key size
     * 1 = Key is grabbed, do nothing unless program hasn't executed
     */
    switch(state){
      case 0:
        setKey(key);
        if(!isProgramExecuted()) {
          state = 0;
          break;
        }
        PORTG &= ~(1<<PORTG5);
        state = 1;
      break;
      case 1:
        if (!isProgramExecuted()) {
          state = 0;  //If program hasnt executed properly go to state 0
          break;
        } else {
          // If circular buffer is full, grab entire buffer and store in
          // array for decryption and pass to decryption process
          if (circular_buf_full(rxCbuf)) {
            for (j = 0; j < BUFFER_SIZE; j++) {
              circular_buf_get(&rxCbuf,  &adcVal[j]);
            }
            AES_CBC_decrypt_buffer(&ctx2, adcVal, 64);
            memcpy(decrypted, adcVal, sizeof(adcVal));
          }
          switch(state2){
            case MESSAGE_AVAILABLE:
              adcValue = receive_data();
              if(!(circular_buf_full(rxCbuf))){
                circular_buf_put(&rxCbuf, adcValue);
              }
              state = WAIT;
            break;
            case TIMER_INT:
              PORTA = decrypted[k];
              PORTC &= ~(1 << PORTC7);
              PORTC |= (1 << PORTC7);
              if (k == BUFFER_SIZE - 1) {
                k = 0;
              } else {
                k++;
              }
              state2 = WAIT;
            break;
          }
          PORTG |= (1<<PORTG5);
        }
        break;
    }
  }

  return 0;
}

/*
 * Prints string as hex.
 */
static void phex(uint8_t* str){
  uint8_t len = 32;
  for (unsigned char i = 0; i < len; ++i) {
    Serial.println(str[i], HEX);
  }
}

/*
 * Interrupt for receiving data via USART
 */
ISR(USART0_RX_vect) {
  state = MESSAGE_AVAILABLE;
}

ISR(TIMER1_COMPA_vect){
  state2 = TIMER_INT;
}

/*
 * Interrupt for card detection, performs nothing when pin is high.
 */
ISR (PCINT2_vect) {
  PORTG &= ~(1<<PORTG5);
  // Serial.println("ERROR!!!:  \n No Card Inserted!");
  // If the card is removed, reset program until card is inserted
  programExec(false);
  state = 0;  // Reset state to 0
  // delay(1000); // Delay for card insertion
  // Serial.println("Checking For Card!");
}
