/*
 * DataHandler.cpp
 *
 *  Created on: Oct 4, 2022
 *      Author: Hesham
 */

#include "DataHandler.h"




DataHandler::DataHandler() {
	// TODO Auto-generated constructor stub

}

DataHandler::~DataHandler() {
	// TODO Auto-generated destructor stub
}

void DataHandler::initialPermutation(uint64 &plainText, uint64 &permPlainText) {

	for(int i = 0; i< 64; i++){

//	cout<<i<<" ";
//	PRINT_BINARY(permPlainText,64);
     WRITE_BIT(
    		 i,
    		 permPlainText,
    		 READ_BIT(( initialpermutationTable[i]-1),plainText)
			 );
	}

}
