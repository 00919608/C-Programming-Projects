/*
 * FileReader.h
 *
 *  Created on: Oct 8, 2017
 *      Author: keith
 */

#ifndef FILEIO_H_
#define FILEIO_H_

#include <string>
#include <vector>

namespace KP_FileIO{
	//trys to open filename, and return its contents in contents
	//it will strip out only \n's (char return\line feed)
	//returns:
	//SUCCESS all worked, contents string contains all in the file
	//COULD_NOT_OPEN_FILE_TO_READ contents string is cleared
	int getFileContents(const std::string &filename, std::string &contents);

	//trys to open filename, and serialize  myEntryVector contents to it
	//returns:
	//SUCCESS all worked, filename contains myEntryVector strings
	//COULD_NOT_OPEN_FILE_TO_WRITE
	int writeVectortoFile(const std::string filename,std::vector<std::string> &myEntryVector);
}

#endif /* FILEIO_H_ */
