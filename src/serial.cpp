#include "serial.h"
void initSerial(){
  USART_Init(MYUBRR);
  test();
}
