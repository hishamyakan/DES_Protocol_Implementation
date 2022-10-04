/*
 * DataHandler.h
 *
 *  Created on: Oct 4, 2022
 *      Author: Hesham
 */

#ifndef DATAHANDLER_H_
#define DATAHANDLER_H_

#include "std_types.h"

#include <iostream>

#include <stdio.h>
#include <stdlib.h>

#include "DES_DataTypes.h"
#include "DES_KeyTypes.h"



using namespace std;




#define PRINT_BINARY(DATA,SIZE) { \
		for(int i = (SIZE)-1 ; i>= 0 ; i--){ \
			\
			printf("%d" , ((DATA)&((uint64)1<<i))?1:0); \
			\
		}\
		puts("\n") ;\
}\

//#define WRITE_BIT(bitNum , permPlainText ,  value) permPlainText |= ( (uint64)value <<bitNum )
#define READ_BIT(bitNum ,PlainText) ((PlainText)&((uint64)1<<bitNum))?1:0

inline void WRITE_BIT(uint8 bitNum , uint64 &permPlainText ,  uint8 value){

	 permPlainText |= ((uint64)value<<bitNum);
}

const uint8 initialpermutationTable[64] =
				{
				58, 50, 42, 34, 26, 18, 10, 2,  60, 52, 44,
	            36, 28, 20, 12, 4,  62, 54, 46, 38, 30, 22,
	            14, 6,  64, 56, 48, 40, 32, 24, 16, 8,  57,
	            49, 41, 33, 25, 17, 9,  1,  59, 51, 43, 35,
	            27, 19, 11, 3,  61, 53, 45, 37, 29, 21, 13,
	            5,  63, 55, 47, 39, 31, 23, 15, 7
				};



class DataHandler {

private:



	DataHandler();
	~DataHandler();
	DataHandler(const DataHandler &other) = delete;


public:

	static void initialPermutation(uint64 &plainText , uint64 & permPlainText);


};

#endif /* DATAHANDLER_H_ */
