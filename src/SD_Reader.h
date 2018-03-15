// Author:
// Net ID:
// Date:
// Assignment:     Lab 4
//
// Description: .
//
// Requirements:
//----------------------------------------------------------------------//
#ifndef SD_Reader_H
#define SD_Reader_H


 //#include <Arduino.h>
//#include <avr/io.h>
#include <string.h>
using namespace std;
bool initiateSDReader();
bool closeSDReader();
void getKey(char* key);
void sdWrite(char* fileName, char* value);
void sdRead(char* fileName);

#endif
