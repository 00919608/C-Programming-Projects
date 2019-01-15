/*
 * Stringtopointer.h
 *
 *  Created on: Oct 8, 2017
 *      Author: keith
 */

#ifndef STRINGTOPOINTER_H_
#define STRINGTOPOINTER_H_
#include <string>
/**
 * Helper class to convert from string to dynamically allocated array
 * memory is automatically deleted in the destructor
 *
 * NOTE: I did not bother to test this class very much.
 * Let me know if there are any errors
 */
class String_to_pointer {
public:
	//make a dynamic copy of myString with pChar pointing to start
	String_to_pointer(const std::string &myString);

	//calls clear
	virtual ~String_to_pointer();

	//very dangerous to expose private data!
	char* getPointerToStringBegginning();
	void changeString(const std::string &myString);

private:
	void clear();	//deallocates memory

	void resetPointer();
	char* pChar;
	std::string aString;
};

#endif /* STRINGTOPOINTER_H_ */
