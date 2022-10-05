/*
 * DataHandler.h
 *
 *  Created on: Oct 4, 2022
 *      Author: Hesham
 */

#ifndef DATAHANDLER_H_
#define DATAHANDLER_H_

#include "std_types.h"
#include "DES_DataTypes.h"
#include "DES_KeyTypes.h"


//#define WRITE_BIT(bitNum , permPlainText ,  value) permPlainText |= ( (uint64)value <<bitNum )
#define READ_BIT(bitNum ,PlainText) ((PlainText)&((uint64)1<<bitNum))?1:0

inline void WRITE_BIT(uint8 bitNum , uint64 &permPlainText ,  uint8 value){

	 permPlainText |= ((uint64)value<<bitNum);
}

inline void WRITE_BIT_48(uint8 bitNum , uint48 &permPlainText ,  uint8 value){

	 permPlainText.value |= ((uint64)value<<bitNum);
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

// Expansion D-box Table

const uint8 expansion_D_BOX[48]
      = { 32, 1,  2,  3,  4,  5,  4,  5,  6,  7,  8,  9,
          8,  9,  10, 11, 12, 13, 12, 13, 14, 15, 16, 17,
          16, 17, 18, 19, 20, 21, 20, 21, 22, 23, 24, 25,
          24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32, 1 };


class DataHandler {

private:


	DataHandler();
	~DataHandler();
	DataHandler(const DataHandler &other) = delete;


public:


	/*
	 * Function: initialPermutation
	 *
	 *
	 *
	 * */
	static void initialPermutation(uint64 &plainText , uint64 & permPlainText);

	static void initialPermutation(DES_Data &plainText , DES_Data & permPlainText);

	static void expansionPermutation(DES_Data &permPlainText , uint48 &EP_48);





	//Note :No Need for the round number
	static DES_Data dataHandleRound(DES_Data &plainText,DES_KeyType &roundKey);



};

#endif /* DATAHANDLER_H_ */
