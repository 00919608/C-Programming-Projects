/*
 * FileReader.cpp
 *
 *  Created on: Oct 8, 2017
 *      Author: keith
 */
#include <iostream>
#include <fstream>
#include<vector>
#include "../327_proj3_test/includes/FileIO.h"
#include "../327_proj3_test/includes/constants.h"

using namespace std;

vector<string>::iterator vectorIterator;

// I believe this is right not sure why 25 test is failing
int KP_FileIO::getFileContents(const std::string &filename, std::string &contents)
{
	fstream openfile;
	openfile.open(filename.c_str());
	if(openfile.is_open()) {
		while(!openfile.eof()){
			string line;
			getline(openfile, line);
			contents += line;
		}
		openfile.close();
		return SUCCESS;
	}
	contents.clear();
	return COULD_NOT_OPEN_FILE_TO_READ;
}

int KP_FileIO::writeVectortoFile(const std::string filename,std::vector<std::string> &myEntryVector)
{
	fstream outputfile;
	outputfile.open(filename.c_str());
	if(outputfile.is_open()) {
		for(vectorIterator = myEntryVector.begin(); vectorIterator != myEntryVector.end(); ++vectorIterator) {
			outputfile << *vectorIterator << endl;
		}
		outputfile.close();
		return SUCCESS;
	}
	return COULD_NOT_OPEN_FILE_TO_WRITE;
}



