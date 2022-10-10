/**
 * Description: Data Handler Functions
 * Authors: Hisham Yakan, Mohamed Mostafa
 *
 */
#include "std_types.h"
#include "DES_DataTypes.h"
#include "DES_KeyTypes.h"

#define READ_BIT(bitNum ,PlainText) ((PlainText)&((uint64)1<<bitNum))?1:0
inline void WRITE_BIT(uint8 bitNum, uint64& permPlainText, uint8 value) {
	permPlainText |= ((uint64)value << bitNum);
}
inline void WRITE_BIT_48(uint8 bitNum, uint48& permPlainText, uint8 value) {
	permPlainText.value |= ((uint64)value << bitNum);
}
inline void WRITE_BIT_32(uint8 bitNum, uint32& permPlainText, uint8 value) {
	permPlainText |= ((uint64)value << bitNum);
}

const uint8 initialpermutationTable[64] = {
	58, 50, 42, 34, 26, 18, 10, 2,  60, 52, 44,
	36, 28, 20, 12, 4,  62, 54, 46, 38, 30, 22,
	14, 6,  64, 56, 48, 40, 32, 24, 16, 8,  57,
	49, 41, 33, 25, 17, 9,  1,  59, 51, 43, 35,
	27, 19, 11, 3,  61, 53, 45, 37, 29, 21, 13,
	5,  63, 55, 47, 39, 31, 23, 15, 7
};

// Expansion D-box Table
const uint8 expansion_D_BOX[48] = {
	32, 1,  2,  3,  4,  5,  4,  5,  6,  7,  8,  9,
	8,  9,  10, 11, 12, 13, 12, 13, 14, 15, 16, 17,
	16, 17, 18, 19, 20, 21, 20, 21, 22, 23, 24, 25,
	24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32, 1
};

/* 8 Boxes, 4 Rows, 16 Column */
const uint8 sboxTable[8][4][16] = {
	{ 14, 4,  13, 1, 2,  15, 11, 8,  3,  10, 6,  12, 5,
	  9,  0,  7,  0, 15, 7,  4,  14, 2,  13, 1,  10, 6,
	  12, 11, 9,  5, 3,  8,  4,  1,  14, 8,  13, 6,  2,
	  11, 15, 12, 9, 7,  3,  10, 5,  0,  15, 12, 8,  2,
	  4,  9,  1,  7, 5,  11, 3,  14, 10, 0,  6,  13 },
	{ 15, 1,  8,  14, 6,  11, 3, 4,  9,  7,  2,  13, 12,
	  0,  5,  10, 3,  13, 4,  7, 15, 2,  8,  14, 12, 0,
	  1,  10, 6,  9,  11, 5,  0, 14, 7,  11, 10, 4,  13,
	  1,  5,  8,  12, 6,  9,  3, 2,  15, 13, 8,  10, 1,
	  3,  15, 4,  2,  11, 6,  7, 12, 0,  5,  14, 9 },
	{ 10, 0,  9,  14, 6,  3,  15, 5,  1,  13, 12,
	  7,  11, 4,  2,  8,  13, 7,  0,  9,  3,  4,
	  6,  10, 2,  8,  5,  14, 12, 11, 15, 1,  13,
	  6,  4,  9,  8,  15, 3,  0,  11, 1,  2,  12,
	  5,  10, 14, 7,  1,  10, 13, 0,  6,  9,  8,
	  7,  4,  15, 14, 3,  11, 5,  2,  12 },
	{ 7,  13, 14, 3,  0,  6,  9,  10, 1,  2, 8,  5,  11,
	  12, 4,  15, 13, 8,  11, 5,  6,  15, 0, 3,  4,  7,
	  2,  12, 1,  10, 14, 9,  10, 6,  9,  0, 12, 11, 7,
	  13, 15, 1,  3,  14, 5,  2,  8,  4,  3, 15, 0,  6,
	  10, 1,  13, 8,  9,  4,  5,  11, 12, 7, 2,  14 },
	{ 2,  12, 4, 1,  7,  10, 11, 6, 8,  5,  3,  15, 13,
	  0,  14, 9, 14, 11, 2,  12, 4, 7,  13, 1,  5,  0,
	  15, 10, 3, 9,  8,  6,  4,  2, 1,  11, 10, 13, 7,
	  8,  15, 9, 12, 5,  6,  3,  0, 14, 11, 8,  12, 7,
	  1,  14, 2, 13, 6,  15, 0,  9, 10, 4,  5,  3 },
	{ 12, 1,  10, 15, 9,  2,  6,  8,  0,  13, 3, 4, 14,
	  7,  5,  11, 10, 15, 4,  2,  7,  12, 9,  5, 6, 1,
	  13, 14, 0,  11, 3,  8,  9,  14, 15, 5,  2, 8, 12,
	  3,  7,  0,  4,  10, 1,  13, 11, 6,  4,  3, 2, 12,
	  9,  5,  15, 10, 11, 14, 1,  7,  6,  0,  8, 13 },
	{ 4,  11, 2,  14, 15, 0,  8, 13, 3,  12, 9,  7,  5,
	  10, 6,  1,  13, 0,  11, 7, 4,  9,  1,  10, 14, 3,
	  5,  12, 2,  15, 8,  6,  1, 4,  11, 13, 12, 3,  7,
	  14, 10, 15, 6,  8,  0,  5, 9,  2,  6,  11, 13, 8,
	  1,  4,  10, 7,  9,  5,  0, 15, 14, 2,  3,  12 },
	{ 13, 2,  8, 4,  6,  15, 11, 1,  10, 9, 3, 14, 5,
	  0,  12, 7, 1,  15, 13, 8,  10, 3,  7, 4, 12, 5,
	  6,  11, 0, 14, 9,  2,  7,  11, 4,  1, 9, 12, 14,
	  2,  0,  6, 10, 13, 15, 3,  5,  8,  2, 1, 14, 7,
	  4,  10, 8, 13, 15, 12, 9,  0,  3,  5, 6, 11 }
};

// Straight Permutation Table
const int permutation[32] = {
	16, 7, 20, 21, 29, 12, 28, 17, 1,  15, 23,
	26, 5, 18, 31, 10, 2,  8,  24, 14, 32, 27,
	3,  9, 19, 13, 30, 6,  22, 11, 4,  25
};

// Final Permutation Table
const int final_perm[64] = {
	40, 8,  48, 16, 56, 24, 64, 32, 39, 7,  47,
	15, 55, 23, 63, 31, 38, 6,  46, 14, 54, 22,
	62, 30, 37, 5,  45, 13, 53, 21, 61, 29, 36,
	4,  44, 12, 52, 20, 60, 28, 35, 3,  43, 11,
	51, 19, 59, 27, 34, 2,  42, 10, 50, 18, 58,
	26, 33, 1,  41, 9,  49, 17, 57, 25
};

void DataHandlerInitialPermutation(DES_Data& plainText, DES_Data& permPlainText) {

	for (int i = 0; i < 64; i++) {
		WRITE_BIT(
			63 - i,
			permPlainText.value_64,
			READ_BIT((63 - (initialpermutationTable[i] - 1)), plainText.value_64)
		);
	}
}

void DataHandlerExpansionPermutation(DES_Data& permPlainText, uint48& EP_48) {
	for (int i = 0; i < 48; i++) {
		WRITE_BIT_48(
			47 - i,
			EP_48,
			READ_BIT((31 - (expansion_D_BOX[i] - 1)), permPlainText.values_32.lower)
		);
	}

}

inline void DataHanlderXorDataKey(uint48& EP_48, DES_KeyType& k, uint48& output) {
	output.value = (EP_48.value) ^ (k.value_48.value);
}

void DataHandlerPermutation(DES_SBox_Output& output, uint32& P_32) {
	for (int i = 0; i < 32; i++) {
		WRITE_BIT_32(
			31 - i,
			P_32,
			READ_BIT((31 - (permutation[i] - 1)), output.value_32)
		);
	}

}

void DataHandlerFinalPermutation(DES_Data& input, DES_Data& output) {
	for (int i = 0; i < 64; i++) {
		WRITE_BIT(
			63 - i,
			output.value_64,
			READ_BIT((63 - (final_perm[i] - 1)), input.value_64)
		);
	}
}

inline void DataHandlerXorLeftPerm(uint32& P_32, DES_Data& permPlainText, uint32& output) {
	output = (P_32) ^ (permPlainText.values_32.upper);
}

inline int RowIndex(const uint64& value) {
	switch (value)
	{
	case 33:
		return 3;
		break;
	case 32:
		return 2;
	default:
		return value;
		break;
	}
}
void DataHandlerSbox(DES_SBox_Input& input, DES_SBox_Output& output) {

	// a bit mask to extract the center and side bits 
	int middle_4_bit_mask = 0b011110;

	// since the output of the bit mask will be 6 bits for just the side bits 
	// 0b100001 => 0b11 

	int col_i, row_i;
	// Box 0
	col_i = (input.values_6.S0 & middle_4_bit_mask) >> 1;
	row_i = RowIndex(input.values_6.S0 & ~middle_4_bit_mask);
	output.values_4.S0 = sboxTable[7][row_i][col_i];

	// Box 1
	col_i = (input.values_6.S1 & middle_4_bit_mask) >> 1;
	row_i = RowIndex(input.values_6.S1 & ~middle_4_bit_mask);
	output.values_4.S1 = sboxTable[6][row_i][col_i];

	// Box 2
	col_i = (input.values_6.S2 & middle_4_bit_mask) >> 1;
	row_i = RowIndex(input.values_6.S2 & ~middle_4_bit_mask);
	output.values_4.S2 = sboxTable[5][row_i][col_i];

	// Box 3
	col_i = (input.values_6.S3 & middle_4_bit_mask) >> 1;
	row_i = RowIndex(input.values_6.S3 & ~middle_4_bit_mask);
	output.values_4.S3 = sboxTable[4][row_i][col_i];

	// Box 4
	col_i = (input.values_6.S4 & middle_4_bit_mask) >> 1;
	row_i = RowIndex(input.values_6.S4 & ~middle_4_bit_mask);
	output.values_4.S4 = sboxTable[3][row_i][col_i];

	// Box 5
	col_i = (input.values_6.S5 & middle_4_bit_mask) >> 1;
	row_i = RowIndex(input.values_6.S5 & ~middle_4_bit_mask);
	output.values_4.S5 = sboxTable[2][row_i][col_i];

	// Box 6
	col_i = (input.values_6.S6 & middle_4_bit_mask) >> 1;
	row_i = RowIndex(input.values_6.S6 & ~middle_4_bit_mask);
	output.values_4.S6 = sboxTable[1][row_i][col_i];

	// Box 7
	col_i = (input.values_6.S7 & middle_4_bit_mask) >> 1;
	row_i = RowIndex(input.values_6.S7 & ~middle_4_bit_mask);
	output.values_4.S7 = sboxTable[0][row_i][col_i];
}


void DataHandlerRound(DES_Data& permPlainText, DES_KeyType& roundKey, DES_Data& res) {



	// for final perm
	//DES_Data finalPermInput;
	res.values_32.upper = permPlainText.values_32.lower;

	//Step 2
	uint48 EP_48;
	EP_48.value = 0;
	DataHandlerExpansionPermutation(permPlainText, EP_48);


	//Step 3
	DataHanlderXorDataKey(EP_48, roundKey, EP_48);

	//Step 4
	DES_SBox_Input des_Sbox_Input;
	des_Sbox_Input.value_48 = EP_48;

	DES_SBox_Output des_Sbox_Output;
	des_Sbox_Output.value_32 = 0;
	DataHandlerSbox(des_Sbox_Input, des_Sbox_Output);

	//Step 5

	uint32 P_32 = 0;
	DataHandlerPermutation(des_Sbox_Output, P_32);

	//Step 6
	DataHandlerXorLeftPerm(P_32, permPlainText, P_32);

	//Step 7
	res.values_32.lower = P_32;


	//return finalPermInput;
}
