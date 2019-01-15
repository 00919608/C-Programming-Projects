/*
 * constants.h
 *
 *  Created on: Oct 8, 2017
 *      Author: keith
 */

#ifndef CONSTANTS_H_
#define CONSTANTS_H_
	#include <string>

	//common
	const int 	SUCCESS			 					=  0;

	//stringparser specific error conditions
	const int	FAIL 								= SUCCESS-1;
	const int	ERROR_NO_ERROR 						= SUCCESS-2;
	const int	ERROR_TAGS_NULL						= SUCCESS-3;
	const int	ERROR_DATA_NULL						= SUCCESS-4;

	//fileIO specific error conditions
	const int 	COULD_NOT_OPEN_FILE_TO_READ			= SUCCESS-5;
	const int 	COULD_NOT_OPEN_FILE_TO_WRITE		= SUCCESS-6;


	//test app specific info
	const int FAIL_WRONG_NUMBER_ARGS = -6;
	const int EXPECTED_NUMBER_ARGUMENTS =5;
	const std::string WRONG_NUMB_ARGS = "This program expects 4 arguments, inputfile starttag endtag outputfile";

#endif /* CONSTANTS_H_ */

