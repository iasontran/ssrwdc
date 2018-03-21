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
bool initiateSDReader(); // Sets up SDReader to be used
bool closeSDReader();    //Close SDReader
void getKey(char* key);  //Grab the key
void sdWrite(char* fileName, char* value); //function to write to a file
void sdRead(char* fileName); //function to read from a specified file


#endif
