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

#include "adc.h"
#include <util/delay.h>
#include "usart.h"
#define WAIT 0
#define MESSAGE_AVAILABLE 1
#define TIMER_INT 2
#define BUFFER_SIZE 64

uint8_t* test_encrypt_cbc(uint8_t *key);
static void test_decrypt_cbc(uint8_t *key, uint8_t *input);
static void phex(uint8_t* str);
static void test_encrypt_ctr(void);
static void test_decrypt_ctr(void);
volatile uint8_t received;
volatile uint8_t received_block[64];
volatile int received_cnt;
int state = 0;

volatile uint8_t adcValue = 0;
volatile int j = 0;
volatile int state2 = WAIT;
bool bufferFull = false;

int main() {
  init(); // Initialization due to use of Arduino libraries
  sei();
  initSerial();
  initTimer1();
  initTimer0();
  initLCD();
  displayOn();
  initLED();
  received_cnt = 0;

  setUpADC();
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

  /*
  char* fileName = "Write.txt"; //File name here, must be small
  char* fileValue = "Custom words";//whatever you want to write here
  int n = 0;
  write(fileName,fileValue);
  */

  while(1) {
    /*
     * State Machine:
     * 0 = Grab key size
     * 1 = Key is grabbed, do nothing unless program hasn't executed
     */
     switch(state2) {
       case TIMER_INT:
         if (j < BUFFER_SIZE) {
          adcVal[j] = ADCH;
          j++;
         }
         else {
          j = 0;
          bufferFull = true;
         }
         state = WAIT;
       break;
     }
     if (bufferFull) {
       // Begin encryption process
       AES_init_ctx_iv(&ctx1, key, iv);
       AES_CBC_encrypt_buffer(&ctx1, adcVal, 64);
       while (j < BUFFER_SIZE) {
         transmit_part(adcVal[j]);
         j++;
       }
       j = 0;
       bufferFull = false;
     }

    /*
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
          PORTG |= (1<<PORTG5);
          // Begin encryption process
          AES_init_ctx_iv(&ctx1, key, iv);
          AES_CBC_encrypt_buffer(&ctx1, adcVal, 64);
          transmit_data(adcVal);
          // // Begin decryption process
          // AES_init_ctx_iv(&ctx2, key, iv);
          // AES_CBC_decrypt_buffer(&ctx2, in, 64);


        }
        break;
    }
    */
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
// ISR(USART0_RX_vect) {
//
//   if (received_cnt != 64) {
//     LED_On();
//     received = receive_data();
//     received_block[received_cnt] = received;
//     received_cnt++;
//     LED_Off();
//   }
//
// }


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
