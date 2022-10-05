/*
 * DataHandler.cpp
 *
 *  Created on: Oct 4, 2022
 *      Author: Hesham
 */

#include "DataHandler.h"
#include <map>

using namespace std;




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

void DataHandler::xorDataKey(uint48& EP_48, DES_KeyType& k, uint48& output)
{
	output.value =  (EP_48.value)^(k.value_48.value);
}

void DataHandler::Permutation(DES_SBox_Output &output, uint32 &P_32) {
	for(int i = 0; i< 32; i++){
     WRITE_BIT_32(
    		 i,
    		 P_32,
    		 READ_BIT(( permutation[i]-1),output.value_32)
			 );
	}

}

void DataHandler::xorLeftPerm(uint32 &P_32, DES_Data &permPlainText, uint32 &output)
{
	output =  (P_32)^(permPlainText.values_32.upper);
}

DES_Data DataHandler::dataHandleRound(DES_Data &plainText, DES_KeyType &roundKey) {

	//Output of The Round
	DES_Data result;

	//Step 1
	DES_Data permPlainText;
	permPlainText.value_64 = 0;

	initialPermutation(plainText, permPlainText);

	//Step 2
	 uint48 EP_48;
	 EP_48.value = 0;
	expansionPermutation(permPlainText, EP_48);


	//Step 3
	xorDataKey(EP_48, roundKey, EP_48);

	//Step 4
	DES_SBox_Input des_Sbox_Input;
	des_Sbox_Input.value_48 = EP_48;

	DES_SBox_Output des_Sbox_Output;
	des_Sbox_Output.value_32 = 0;
	sbox(des_Sbox_Input, des_Sbox_Output);

	//Step 5

	uint32 P_32;
	Permutation(des_Sbox_Output, P_32);

	//Step 6
	xorLeftPerm(P_32, permPlainText, P_32);

	//Step 7





	return result;
}

void DataHandler::sbox(DES_SBox_Input& input, DES_SBox_Output& output) {

	// a bit mask to extract the center and side bits 
	int middle_4_bit_mask = 0b011110;

	// since the output of the bit mask will be 6 bits for just the side bits 
	// 0b100001 => 0b11 
	map<int, int> row_index{ { 33, 3 }, { 32, 2 }, {1, 1}, {0, 0} };

	int col_i, row_i;
	// Box 0
	col_i = (input.values_6.S0 & middle_4_bit_mask) >> 1;
	row_i = row_index[input.values_6.S0 & ~middle_4_bit_mask];
	//cout << row_i << " " << col_i << " " << (int)sboxTable[0][row_i][col_i] << endl;
	output.values_4.S0 = sboxTable[0][row_i][col_i];

	// Box 1
	col_i = (input.values_6.S1 & middle_4_bit_mask) >> 1;
	row_i = row_index[input.values_6.S1 & ~middle_4_bit_mask];
	//cout << row_i << " " << col_i << " " << (int)sboxTable[1][row_i][col_i] << endl;
	output.values_4.S1 = sboxTable[1][row_i][col_i];

	// Box 2
	col_i = (input.values_6.S2 & middle_4_bit_mask) >> 1;
	row_i = row_index[input.values_6.S2 & ~middle_4_bit_mask];
	//cout << row_i << " " << col_i << " " << (int)sboxTable[2][row_i][col_i] << endl;
	output.values_4.S2 = sboxTable[2][row_i][col_i];

	// Box 3
	col_i = (input.values_6.S3 & middle_4_bit_mask) >> 1;
	row_i = row_index[input.values_6.S3 & ~middle_4_bit_mask];
	//cout << row_i << " " << col_i << " " << (int)sboxTable[3][row_i][col_i] << endl;
	output.values_4.S3 = sboxTable[3][row_i][col_i];

	// Box 4
	col_i = (input.values_6.S4 & middle_4_bit_mask) >> 1;
	row_i = row_index[input.values_6.S4 & ~middle_4_bit_mask];
	//cout << row_i << " " << col_i << " " << (int)sboxTable[4][row_i][col_i] << endl;
	output.values_4.S4 = sboxTable[4][row_i][col_i];

	// Box 5
	col_i = (input.values_6.S5 & middle_4_bit_mask) >> 1;
	row_i = row_index[input.values_6.S5 & ~middle_4_bit_mask];
	//cout << row_i << " " << col_i << " " << (int)sboxTable[5][row_i][col_i] << endl;
	output.values_4.S5 = sboxTable[5][row_i][col_i];

	// Box 6
	col_i = (input.values_6.S6 & middle_4_bit_mask) >> 1;
	row_i = row_index[input.values_6.S6 & ~middle_4_bit_mask];
	//cout << row_i << " " << col_i << " " << (int)sboxTable[6][row_i][col_i] << endl;
	output.values_4.S6 = sboxTable[6][row_i][col_i];

	// Box 7
	col_i = (input.values_6.S7 & middle_4_bit_mask) >> 1;
	row_i = row_index[input.values_6.S7 & ~middle_4_bit_mask];
	//cout << row_i << " " << col_i << " " << (int)sboxTable[7][row_i][col_i] << endl;
	output.values_4.S7 = sboxTable[7][row_i][col_i];
}
