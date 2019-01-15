/*
 * test.cpp
 *
 *  Created on: Oct 8, 2017
 *      Author: keith
 */

#include "test.h"
/*
 * test.cpp
 *
 *  Created on: Oct 8, 2017
 *      Author: keith
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <time.h>
#include "../includes/constants.h"
#include "Stringtopointer.h"
#include "../includes/StringParserClass.h"
#include "../includes/FileIO.h"

using namespace std;

const int ZERO_POINTS = 0;  //for retests
const int ONE_POINTS = 1;
const int TWO_POINTS = 2;
const int THREE_POINTS = 3;
const int FIVE_POINTS = 5;
const int TEN_POINTS = 10;
const int FIFTEEN_POINTS = 15;


//tracks how many points you will get out of 100
//yeah, yeah its a global
int total_points =0;

//this is a template class, its mostly here as a helper for me
//the T and U are generic params, I can substitute any type for them
//they must be comparable with ==, templates are extremely hard to get right BTW
template<typename T, typename U>
bool EXPECT_EQ(T expectedVal, U actualVal,string testnumb = "", int pts=ONE_POINTS){
	bool bout = (expectedVal == actualVal);
	if (bout){
		cout<<"SUCCESS "+testnumb;
		total_points+=pts;
	}
	else
		cout<<"FAIL "+ testnumb<< " Expected:"<<expectedVal<<"  got:"<<actualVal;
	cout<<endl;
	return bout;
}

const std::string TEST_DATA_NON_EXISTANT 		= "./data/notthere/nonexistantfile";
const std::string TEST_DATA_SMALL_OUT 			= "./output/testdata_small.out";
const std::string TEST_DATA_SMALL_OUT_VALUE 	= "Asmalllizard";

void testfileIO(const std::string &userEnteredInputFile, const std::string &userEnteredOutputFile){
	string contents;
	string filename;

	vector<string> mv;
	mv.push_back("A");
	mv.push_back("small");
	mv.push_back("lizard");

	//test read from user supplied input file
	EXPECT_EQ (SUCCESS, KP_FileIO::getFileContents(userEnteredInputFile, contents),"25",FIVE_POINTS);
	//TODO probably should confirm that it also has right contents

	//test read and write to a bogus file
	filename = TEST_DATA_NON_EXISTANT;
	EXPECT_EQ (COULD_NOT_OPEN_FILE_TO_READ, KP_FileIO::getFileContents(filename, contents),"1",FIVE_POINTS);
	EXPECT_EQ (COULD_NOT_OPEN_FILE_TO_WRITE, KP_FileIO::writeVectortoFile(filename, mv),"2",FIVE_POINTS);

	//test write real
	EXPECT_EQ (SUCCESS, KP_FileIO::writeVectortoFile(userEnteredOutputFile, mv),"3",FIVE_POINTS);

	//test read real
	contents.clear();
	EXPECT_EQ (SUCCESS, KP_FileIO::getFileContents(userEnteredOutputFile, contents),"4",FIVE_POINTS);
	EXPECT_EQ (true, TEST_DATA_SMALL_OUT_VALUE == contents,"5",FIVE_POINTS);
}

const std::string TEST_STRING 		 		= "<li class=\"nav-twilight\"><a href=\"/mylittlepony/en_US/ponies/twilight-sparkle.cfm\".<to>Twilight Sparkle</to><to>Pinkie Pie</to></li>";
const std::string TEST_STRING_NO_END_TAG 	= "<li class=\"nav-twilight\"><a href=\"/mylittlepony/en_US/ponies/twilight-sparkle.cfm\".<to>Twilight Sparkle<to></li>";
const std::string TEST_STRING_NO_START_TAG 	= "<li class=\"nav-twilight\"><a href=\"/mylittlepony/en_US/ponies/twilight-sparkle.cfm\".</to>Twilight Sparkle</to></li>";

const std::string TS_FIRST_NONCE 			= "Twilight Sparkle";
const std::string TS_SECOND_NONCE 			= "Pinkie Pie";

const std::string BOGUS_TAG = "-------";

void testStringParser(const std::string &startTag,const std::string &endTag){
	vector<string> mv;
	KP_StringParserClass::StringParserClass sp;

	//verify correct null behaviour
	char* pChar =0;
	EXPECT_EQ (ERROR_TAGS_NULL, sp.getDataBetweenTags(pChar, mv),"6",FIVE_POINTS);

	//verify correct null tag behaviour
	EXPECT_EQ (ERROR_TAGS_NULL, sp.setTags(0, 0),"7",FIVE_POINTS);

	//set tags
	String_to_pointer stp_start(startTag);
	String_to_pointer stp_end(endTag);

	EXPECT_EQ (SUCCESS, sp.setTags(stp_start.getPointerToStringBegginning(), stp_end.getPointerToStringBegginning()),"8",FIVE_POINTS);

	//now that tags are set verify that it fails if there is no data
	EXPECT_EQ (ERROR_DATA_NULL, sp.getDataBetweenTags(pChar, mv),"9",FIVE_POINTS);

	//we cant manipulate String contents easily, so make a copy in a dynamically allocated array
	//incidently this class shows the principles of RAII, allocated memory is automatically
	//deallocated in the destructor
	String_to_pointer stp(TEST_STRING);
	pChar = stp.getPointerToStringBegginning();

	EXPECT_EQ (SUCCESS, sp.getDataBetweenTags(pChar, mv),"10",FIVE_POINTS);
	EXPECT_EQ (2, mv.size(),"11",FIVE_POINTS);
	EXPECT_EQ (TS_FIRST_NONCE, mv[0],"12",TWO_POINTS);
	EXPECT_EQ (TS_SECOND_NONCE, mv[1],"13",THREE_POINTS);

	//make sure they clear the vector and not append to it
	pChar = stp.getPointerToStringBegginning();
	EXPECT_EQ (SUCCESS, sp.getDataBetweenTags(pChar, mv),"14",ZERO_POINTS); //already tested
	EXPECT_EQ (2, mv.size(),"15",FIVE_POINTS);								//if one then it was cleared if 2 not

	//try with no end tag
	stp.changeString(TEST_STRING_NO_END_TAG);
	pChar = stp.getPointerToStringBegginning();
	EXPECT_EQ (SUCCESS, sp.getDataBetweenTags(pChar, mv),"16",FIVE_POINTS);
	EXPECT_EQ (0, mv.size(),"17",FIVE_POINTS);

	//try with no start tag
	stp.changeString(TEST_STRING_NO_START_TAG);
	pChar = stp.getPointerToStringBegginning();
	EXPECT_EQ (SUCCESS, sp.getDataBetweenTags(pChar, mv),"18",FIVE_POINTS);
	EXPECT_EQ (0, mv.size(),"19",FIVE_POINTS);

	//make sure they made a deep copy of the tags
	//the following 2 lines should not affect start and end tags in sp
	stp_start.changeString(BOGUS_TAG);
	stp_end.changeString(BOGUS_TAG);

	//try with no start tag
	stp.changeString(TEST_STRING);
	pChar = stp.getPointerToStringBegginning();

	mv.clear();
	EXPECT_EQ (SUCCESS, sp.getDataBetweenTags(pChar, mv),"20",ZERO_POINTS);	//already tested
	EXPECT_EQ (2, mv.size(),"21",TEN_POINTS);
}

int getScore(){
	return total_points;
}




