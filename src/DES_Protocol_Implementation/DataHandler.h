/*
 * DataHandler.h
 *
 *  Created on: Oct 4, 2022
 *      Author: Hesham
 */

#ifndef DATAHANDLER_H_
#define DATAHANDLER_H_

#include "std_types.h"

#define WRITE_BIT(bitNum , permPlainText ,  value)  permPlainText |= (value<<bitNum)
#define READ_BIT(bitNum ,PlainText) PlainText&(1<<bitNum)

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

	static void initialPermutation(uint64 &plainText , uint64 & permPlainText){

		for(uint8 i = 0; i< 64; i++){

	     WRITE_BIT( i,permPlainText,READ_BIT(( initialpermutationTable[i]-1),plainText) );
		}

	}


};

#endif /* DATAHANDLER_H_ */
