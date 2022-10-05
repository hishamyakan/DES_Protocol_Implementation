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
     WRITE_BIT(
    		 i,
    		 permPlainText,
    		 READ_BIT(( initialpermutationTable[i]-1),plainText)
			 );
	}

}


void DataHandler::initialPermutation(DES_Data &plainText , DES_Data & permPlainText){

	for(int i = 0; i< 64; i++){
     WRITE_BIT(
    		 i,
    		 permPlainText.value_64,
    		 READ_BIT(( initialpermutationTable[i]-1),plainText.value_64)
			 );
	}
}

void DataHandler::expansionPermutation(DES_Data &permPlainText, uint48 &EP_48) {
	for(int i = 0; i< 48; i++){
     WRITE_BIT_48(
    		 i,
    		 EP_48,
    		 READ_BIT(( expansion_D_BOX[i]-1),permPlainText.values_32.lower)
			 );
	}

}

DES_Data DataHandler::dataHandleRound(DES_Data &plainText, DES_KeyType &roundKey) {


	//Step 1
	DES_Data permPlainText;
	permPlainText.value_64 = 0;

	initialPermutation(plainText, permPlainText);


}
