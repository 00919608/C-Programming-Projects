/*
 * StringParserClass.cpp
 *
 *  Created on: Oct 8, 2017
 *      Author: keith
 */

#include <string>
#include <string.h>
#include<iostream>
#include "../327_proj3_test/includes/constants.h"
#include "../327_proj3_test/includes/StringParserClass.h"
using namespace std;
char* inBetween;
//dont forget to initialize member variables
KP_StringParserClass::StringParserClass::StringParserClass() :
		pStartTag(0), pEndTag(0), areTagsSet(false) {
}
void KP_StringParserClass::StringParserClass::cleanup() {
	delete pEndTag;
	delete pStartTag;
	pEndTag = NULL;
	pStartTag = pEndTag;
}
//call cleanup to release any allocated memory
KP_StringParserClass::StringParserClass::~StringParserClass() {
	cleanup();
}
//these are the start tag and the end tags that we want to find,
//presumably the data of interest is between them, please make a
//COPY of what pStartTag and pEndTag point to.  In other words
//DO NOT SET pStartTag = pStart
//returns:
//SUCCESS
//ERROR_TAGS_NULL if either pStart or pEnd is null
int KP_StringParserClass::StringParserClass::setTags(const char *pStart,
		const char *pEnd) {
	if (pStart == NULL && pEnd == NULL) {
		return ERROR_TAGS_NULL;
	} else {
		pStartTag = strdup(pStart);
		pEndTag = strdup(pEnd);
		areTagsSet = true;
		return SUCCESS;
	}
}

//First clears myVector
//going to search thru pDataToSearchThru, looking for info bracketed by
//pStartTag and pEndTag, will add that data to myStrings
//returns
//SUCCESS  finished searching for data between tags, results in myStrings (0 or more entries)
//ERROR_TAGS_NULL if either pStart or pEnd is null
//ERROR_DATA_NULL pDataToSearchThru is null
int KP_StringParserClass::StringParserClass::getDataBetweenTags(
		char *pDataToSearchThru, std::vector<std::string> &myVector) {
	myVector.clear();
	if (pStartTag == 0 || pEndTag == 0) {
		return ERROR_TAGS_NULL;
	}
	if (pDataToSearchThru == NULL) {
		return ERROR_DATA_NULL;
	}
	char* p;
	int a;
	while (findTag(pStartTag, pDataToSearchThru, p) == SUCCESS) {
		a = findTag(pStartTag, pDataToSearchThru, p);
		pDataToSearchThru = *(&p);
		string sNonce;
		char *pEnd;
		char* pStart = *(&p);
		char *pNonceStart = 0;
		char *pNonceEnd = 0;
		if (a == SUCCESS) {
			pNonceStart = pDataToSearchThru;
			pStart = pNonceStart;
			a = findTag(pEndTag, pStart, pEnd);
			switch (a) {
			case SUCCESS:
				pNonceEnd = pStart;
				sNonce.assign(pNonceStart, *(&pNonceEnd) - pNonceStart);
				myVector.push_back(sNonce);
				pStart = pEnd;
				pDataToSearchThru = pEnd;
				break;
			}
		}
	}
	return SUCCESS;
}
//Searches a string starting at pStart for pTagToLookFor
//returns:
//SUCCESS  found pTagToLookFor, pStart points to beginning of tag and pEnd points to end of tag
//FAIL did not find pTagToLookFor and pEnd points to 0
//ERROR_TAGS_NULL if either pStart or pEnd is null
int KP_StringParserClass::StringParserClass::findTag(char *pTagToLookFor,
		char *&pStart, char *&pEnd) {
	if (pStart == 0 || pEnd == 0) {
		return ERROR_TAGS_NULL;
	}
	if (pTagToLookFor == 0 || pStart == 0) {
		return FAIL;
	}
	pEnd = 0;
	int iLen = strlen(pStart);
	int lenTag = strlen(pTagToLookFor);
	for (int i = 0; i < iLen; ++i) {
		if (*(pStart) == *pTagToLookFor) {
			if (strncmp((pStart), pTagToLookFor, lenTag) == 0) {
				pEnd = pStart + lenTag;
				return SUCCESS;
			}
		}
		pStart++;
	}
	return FAIL;
}

