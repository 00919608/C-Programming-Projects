/*
 * Stringtopointer.cpp
 *
 *  Created on: Oct 8, 2017
 *      Author: keith
 */
#include <string.h>
#include "Stringtopointer.h"
const int SPACE_FOR_TERMINATING_NULL_CHAR = 1;

//make a dynamic copy of myString with pChar pointing to start
String_to_pointer::String_to_pointer(const std::string &myString): pChar(0),aString(myString) {
}

//clean up any allocated memory
String_to_pointer::~String_to_pointer() {
	clear();
}

//very dangerous to expose private data!
char* String_to_pointer::getPointerToStringBegginning(){
	resetPointer();
	return pChar;
}

void String_to_pointer::clear(){
	if(pChar)
		delete [] pChar;
	pChar = 0;
}

void String_to_pointer::resetPointer(){
	clear();
	//how many chars (+1 for the null!)
	int len = strlen(aString.c_str())+SPACE_FOR_TERMINATING_NULL_CHAR;

	if(len>SPACE_FOR_TERMINATING_NULL_CHAR){
		pChar = new char[len];
		strncpy(pChar,aString.c_str(),len);
		*(pChar+len)=0;
	}
}

void String_to_pointer::changeString(const std::string &myString){
	aString = myString;
	clear();
}

