// Author: Team 17052
// Date:12/1/17
// Assignment: Secure Wireless Protocol
//
// Description: This Program handles the encryption and decryption functions of
//              the Secure Wireless Protocol Project
// Requirements:
//               Secure an audio signal for transmission
//----------------------------------------------------------------------//

//Begin Includes//
#include <Arduino.h>
#include <avr/io.h>
#include "timer.h"
#include <SD_Reader.H>
#include <SD_writer.H>
#include "aes.hpp"
int state = 0; // set state 0
//End Includes//



int main(void){
  uint8_t iv[]  = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f };
  uint8_t in[]  = { 0xf5, 0x8c, 0x4c, 0x04, 0xd6, 0xe5, 0xf1, 0xba, 0x77, 0x9e, 0xab, 0xfb, 0x5f, 0x7b, 0xfb, 0xd6,
                    0x9c, 0xfc, 0x4e, 0x96, 0x7e, 0xdb, 0x80, 0x8d, 0x67, 0x9f, 0x77, 0x7b, 0xc6, 0x70, 0x2c, 0x7d,
                    0x39, 0xf2, 0x33, 0x69, 0xa9, 0xd9, 0xba, 0xcf, 0xa5, 0x30, 0xe2, 0x63, 0x04, 0x23, 0x14, 0x61,
                    0xb2, 0xeb, 0x05, 0xe2, 0xc3, 0x9b, 0xe9, 0xfc, 0xda, 0x6c, 0x19, 0x07, 0x8c, 0x6a, 0x9d, 0x1b };

  uint8_t ptx[]  = { 0xf5, 0x8c, 0x4c, 0x04, 0xd6, 0xe5, 0xf1, 0xba, 0x77, 0x9e, 0xab, 0xfb, 0x5f, 0x7b, 0xfb, 0xd6,
                    0x9c, 0xfc, 0x4e, 0x96, 0x7e, 0xdb, 0x80, 0x8d, 0x67, 0x9f, 0x77, 0x7b, 0xc6, 0x70, 0x2c, 0x7d,
                    0x39, 0xf2, 0x33, 0x69, 0xa9, 0xd9, 0xba, 0xcf, 0xa5, 0x30, 0xe2, 0x63, 0x04, 0x23, 0x14, 0x61,
                    0xb2, 0xeb, 0x05, 0xe2, 0xc3, 0x9b, 0xe9, 0xfc, 0xda, 0x6c, 0x19, 0x07, 0x8c, 0x6a, 0x9d, 0x1b };
  init(); //necessary for atom ide using arduino libraries
  sei();
  uint8_t key[getKeySize()]; //key in uint8_t format
  uint8_t* ctx;
  uint8_t *text;
  struct AES_ctx ctx1;
  struct AES_ctx ctx2;

while(1){

  /*begin State Machine
    0 =  grab the keySize
    1 = Key is grabbed do nothing unless program hasnt executed
  */

  switch(state){
    case 0:
    setKey(key);
    if(!isProgramExecuted())
    {
      state = 0;
      break;
    } //end if
      PORTG &= ~(1<<PORTG5);
    state = 1;
    break;
/////////end case 0//////////////
      case 1:
          if (!isProgramExecuted()) {
            state = 0;  //If program hasnt executed properly go to state 0
            break;
          }//end if
          else {
             PORTG |= (1<<PORTG5); // for indicatior light pin 4
            //Serial.print("."); //Wait

            // Serial.println("Passed in key for encrypt: ");
            // for (int i = 0; i < 32; i++) {
            //   Serial.print(key[i], HEX);
            // }
            // Serial.print("\n");

            uint8_t original[16];
              for (int i = 0; i < 16 /*64*/; i++) {
            //    Serial.print(in[i], HEX);
             original[i] = in[i];
                }
            long x;
            x = micros();
            AES_init_ctx_iv(&ctx1, key, iv);        //These two lines for encryption
            AES_CBC_encrypt_buffer(&ctx1, in, 16); //-------last number is size of input------------------//
             x = micros() - x;
             Serial.print("encryption took this long: ");
             Serial.print(x);
             Serial.println(" microseconds");
           //  Serial.println("Produced ciphertext: ");
           uint8_t testInput[16];
             for (int i = 0; i < 16 /*64*/; i++) {
           //    Serial.print(in[i], HEX);
            testInput[i] = in[i];
               }
//---------------------------------------------------------------------------//
               Serial.println("testInput encrypted|----|original");
               for (int i = 0; i < 32 /*64*/; i++) {
                 Serial.print(testInput[i]);
                 Serial.print("|----|");
                 Serial.println(original[i]);

                 }

//----------------------------------------------------------------------------//
           //  Serial.println("");
           //
           //  Serial.println("Expected plaintext: ");
           //  for (int i = 0; i < 64; i++) {
           //   Serial.print(ptx[i], HEX);
           //  }
           // Serial.println("");
           //
           //  Serial.println("Passed in key for decrypt: ");
           //  for (int i = 0; i < 32; i++) {
           //    Serial.print(key[i], HEX);
            // }
          //  Serial.print("\n");

          //  Serial.println("Decrypted plaintext: ");
            long y;
            y = micros();
            AES_init_ctx_iv(&ctx2, key, iv);             //these two lines for decryption
            AES_CBC_decrypt_buffer(&ctx2, testInput/*in*/, 16);       //----------------------//
            y = micros() - y;
            Serial.print("decryption took this long: ");
            Serial.print(y);
            Serial.println(" microseconds");
            // for (int i = 0; i < 64; i++) {
            //   Serial.print(in[i], HEX);
            // }
            // Serial.println("");
// //-------------------------------------------------------------------------//
//
//             Serial.println("Original|----|testInput");
//             for (int i = 0; i < 32 /*64*/; i++) {
//               Serial.print(original[i]);
//               Serial.print("|----|");
//               Serial.println(testInput[i]);
//
//               }

//-----------------------------------------------------------------------------//
            if (0 == memcmp((char*) original/*ptx*/, (char*) testInput/*in*/, 16)) {
                // Serial.println("SUCCESS!");
                // return;
            }
            else {
                Serial.println("FAILURE!");
                // return;
            }
            /*
            text = test_encrypt_cbc(key);
            Serial.println("Ciphertext in main: ");
            for (int i = 0; i < 64; i++) {
              Serial.print(text[i], HEX);
            }
            Serial.print("\n");
            test_decrypt_cbc(key, text);
            */
          //  delay(1000);
            break;
          }// end else
    }//end switch
  }//end while
  return 0;
}//End main


//Interupt based on the card detect pin, when High do nothing//
ISR (PCINT2_vect){
PORTG &= ~(1<<PORTG5);
  Serial.println("ERROR!!!:  \n No Card Inserted!");
    programExec(false); //if the card is removed reset program till
                              //card is inserted
    state = 0;                //set state back to 0
    delay(1000);              //delay to give card a chance to be fully inserted
    Serial.println("Checking For Card!");

}
//End Intererupt//
