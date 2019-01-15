//============================================================================
// Name        : 327_proj3_test.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <iterator>
#include <string.h>

#include "../includes/constants.h"
#include "Stringtopointer.h"
#include "../includes/StringParserClass.h"
#include "../includes/FileIO.h"
#include "test.h"

using namespace std;

//two utility functions for looping through vector and printing
//its contents to std::out (the Console)
void outputvectorrow(string i){
	std::cout<<i<<std::endl;
}
void dumpVecToStdOut(vector<string> myVector){
	for_each(myVector.begin(), myVector.end(), outputvectorrow);
}

int typicalrun(string &inputfile,string &startTag,string &endTag,string &outputfile){
vector<string> myStrings;
int iret = SUCCESS;

//open file, if not there ask for a different file or exit
std::string	filecontents;
iret = KP_FileIO::getFileContents(inputfile.c_str(),filecontents );
if (iret != SUCCESS)
	return iret;

//we cant manipulate String contents easily, so make a copy in a dynamically allocated array
//incidently this class shows the principles of RAII, allocated memory is automatically
//deallocated in the destructor
String_to_pointer stp(filecontents);
char* pChar = stp.getPointerToStringBegginning();

//create an instance of the stringparser
KP_StringParserClass::StringParserClass myClass;

//what tags are we searching for?
iret = myClass.setTags(startTag.c_str(),endTag.c_str());
if (iret != SUCCESS)
	return iret;

//pull out the data
iret = myClass.getDataBetweenTags(pChar, myStrings);
if (iret != SUCCESS)
	return iret;

//serialize to file
iret = KP_FileIO::writeVectortoFile(outputfile,myStrings);
if (iret != SUCCESS)
	return iret;

//dump to standard output
//dumpVecToStdOut(myStrings);
}

int main(int argc, char *argv[]){

	vector<string> myStrings;
	int iret = SUCCESS;

	//TODO verify that correct number of params are entered
	//TODO otherwise return output WRONG_NUMB_ARGS and return FAIL_WRONG_NUMBER_ARGS
	if(argc < 4) {
		cout << WRONG_NUMB_ARGS << endl;
		return FAIL_WRONG_NUMBER_ARGS;
	}

	//harvest all the user info
	string inputfile = argv[1];
	string startTag = argv[2];
	string endTag = argv[3];
	string outputfile = argv[4];
	//lets test the inputs
	testfileIO(inputfile, outputfile);

	//now lets test the string parsing
	testStringParser(startTag,endTag);

	cout<<"Score is:"<<getScore()<<endl;
	typicalrun(inputfile,startTag,endTag,outputfile);
}
