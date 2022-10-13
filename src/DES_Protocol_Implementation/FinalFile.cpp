//============================================================================
// Name        : FinalFile.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : DES Encryption in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
using namespace std;

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
/* Boolean Values */
#ifndef FALSE
#define FALSE       (0u)
#endif
#ifndef TRUE
#define TRUE        (1u)
#endif

#define STD_HIGH          (1u)
#define STD_LOW           (0u)

#define STD_ON			  (1u)
#define STD_OFF			  (0u)

#define NULL_PTR    ((void*)0)

#define READ_BIT(bitNum ,PlainText) ((PlainText)&((uint64)1<<bitNum))?1:0

#define SIZE 56

#define LCS(KEY,NUM) ( KEY = (KEY<<NUM) | (KEY >> ((28-NUM))))

#define KEY_WRITE_BIT_48(KEY,POS,VALUE) (KEY = (KEY&~((uint64)1<<POS)) | ((uint64)VALUE<<POS))

/*******************************************************************************
 *                             Type Declarations                               *
 *******************************************************************************/
typedef unsigned char         uint8;          /*           0 .. 255              */
typedef signed char           sint8;          /*        -128 .. +127             */
typedef unsigned short        uint16;         /*           0 .. 65535            */
typedef signed short          sint16;         /*      -32768 .. +32767           */
typedef unsigned long         uint32;         /*           0 .. 4294967295       */
typedef signed long           sint32;         /* -2147483648 .. +2147483647      */
typedef unsigned long long    uint64;         /*       0 .. 18446744073709551615  */
typedef signed long long      sint64;         /* -9223372036854775808 .. 9223372036854775807 */
typedef float                 float32;
typedef double                float64;

typedef struct{

	uint64 value : 48 ;
	uint64 : 0;

}uint48;


typedef struct uint28_2{

	uint64 lower : 28 ;
	uint64 upper : 28 ;
	uint64 : 0 ;
}uint28_2; /* Two 28-bit values (upper and lower)*/


typedef struct{

	uint64 value : 56 ;
	uint64 : 0;

}uint56; /*56-bit value*/


typedef union DES_KeyType{

	uint64 value_64; /*64-bit value*/

	/*OR*/

	uint56 value_56 ; /*56-bit value*/

	/*OR*/

	uint28_2 values_28; /* Two 26-bit values (upper and lower)*/

	/*OR*/

	uint48 value_48; /*48-bit value*/

}DES_KeyType;


typedef struct uint32_2{

	uint64 lower : 32 ;
	uint64 upper : 32 ;

}uint32_2; /* Two 32-bit values (upper and lower)*/


typedef union DES_Data{

	uint64 value_64; /*64 bit value*/

	/*OR*/

	uint32_2 values_32; /* Two 32-bit values (upper and lower)*/

}DES_Data;



typedef struct{

	uint64 S0 : 6;
	uint64 S1 : 6;
	uint64 S2 : 6;
	uint64 S3 : 6;
	uint64 S4 : 6;
	uint64 S5 : 6;
	uint64 S6 : 6;
	uint64 S7 : 6;
	uint64 : 0;
}uint6_8; /*8 6-bit values*/

typedef struct{

	uint64 S0 : 4;
	uint64 S1 : 4;
	uint64 S2 : 4;
	uint64 S3 : 4;
	uint64 S4 : 4;
	uint64 S5 : 4;
	uint64 S6 : 4;
	uint64 S7 : 4;
	uint64 : 0;

}uint4_8; /*8 4-bit values*/

typedef union{

	uint48 value_48; /*48-bit value*/

	/*OR*/

	uint6_8 values_6;/*8 6-bit values*/

}DES_SBox_Input;

typedef union{

	uint32 value_32; /*32_bit value*/

	/*OR*/

	uint4_8 values_4; /*8 4-bit values*/

}DES_SBox_Output;


typedef struct{

	uint8 lower : 4;
	uint8 upper : 4;

}uint4_2;

typedef union DES_DataType{

	DES_Data data; /*64-bit value or 2 32-bit values*/
	/*OR*/
	uint4_2 array[8]; /*8 8-bit values with access to upper and lower half bytes*/

}DES_DataType;

/*Enum that represents the type of operation to be performed*/
typedef enum{

	ENCRYPT , DECRYPT

}DES_OpType;

/*******************************************************************************
 *                              Global Variables                               *
 *******************************************************************************/
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
const int permutation[32]
					  = { 16, 7, 20, 21, 29, 12, 28, 17, 1,  15, 23,
							  26, 5, 18, 31, 10, 2,  8,  24, 14, 32, 27,
							  3,  9, 19, 13, 30, 6,  22, 11, 4,  25 };

// Final Permutation Table
const int final_perm[64]
					 = { 40, 8,  48, 16, 56, 24, 64, 32, 39, 7,  47,
							 15, 55, 23, 63, 31, 38, 6,  46, 14, 54, 22,
							 62, 30, 37, 5,  45, 13, 53, 21, 61, 29, 36,
							 4,  44, 12, 52, 20, 60, 28, 35, 3,  43, 11,
							 51, 19, 59, 27, 34, 2,  42, 10, 50, 18, 58,
							 26, 33, 1,  41, 9,  49, 17, 57, 25 };

const uint8 permutedchoice2table[48]{
	14,17,11,24,1,5,3,28,
	15,6,21,10,23,19,12,4,
	26,8,16,7,27,20,13,2,
	41,52,31,37,47,55,30,40,
	51,45,33,48,44,49,39,56,
	34,53,46,42,50,36,29,32
};

const uint8 leftshiftschedule[16]{
	1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1
};


/*Boolean value to check whether all keys were generated or not*/
bool keyGenerated = false;

/*Array of input keys to their respective rounds*/
DES_KeyType InputKeys[16] = {0};

/*******************************************************************************
 *                              Inline Functions                               *
 *******************************************************************************/
inline void WRITE_BIT(uint8 bitNum , uint64 &permPlainText ,  uint8 value){

	permPlainText |= ((uint64)value<<bitNum);
}

inline void WRITE_BIT_48(uint8 bitNum , uint48 &permPlainText ,  uint8 value){

	permPlainText.value |= ((uint64)value<<bitNum);
}

inline void WRITE_BIT_32(uint8 bitNum , uint32 &permPlainText ,  uint8 value){

	permPlainText |= ((uint64)value<<bitNum);
}

inline void initialPermutation(DES_Data &plainText , DES_Data & permPlainText){

	for(int i = 0; i< 64; i++){
		WRITE_BIT(
				63-i,
				permPlainText.value_64,
				READ_BIT((63-( initialpermutationTable[i]-1)),plainText.value_64)
		);
	}
}

inline void finalPermutation(DES_Data& input, DES_Data& output) {
	for (int i = 0; i < 64; i++) {
		WRITE_BIT(
				63-i,
				output.value_64,
				READ_BIT((63-(final_perm[i] - 1)), input.value_64)
		);
	}
}

/* Read Bit value in 64 Bits key */
inline uint8 READ_BIT2(uint64 KEY, uint8 POS) {return ( KEY & ((uint64)1<<POS) )?1:0;}

/* Write Bit value in 56 Bits key */
inline void WRITE_BIT_56(uint8 bitNum, uint56* key,  uint8 value)
{
	if(value == STD_HIGH)
		key->value |= ((uint64)1<<bitNum);
	else
		key->value &= ~((uint64)1<<bitNum);
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

/*******************************************************************************
 *                               Data Functions                                *
 *******************************************************************************/

void expansionPermutation(const DES_Data &permPlainText, uint48 &EP_48) {
	for(int i = 0; i< 48; i++){
		WRITE_BIT_48(
				47-i,
				EP_48,
				READ_BIT((31-( expansion_D_BOX[i]-1)),permPlainText.values_32.lower)
		);
	}

}

void xorDataKey(uint48& EP_48, DES_KeyType& k, uint48& output)
{
	output.value =  (EP_48.value)^(k.value_48.value);
}

void Permutation(DES_SBox_Output &output, uint32 &P_32) {
	for(int i = 0; i< 32; i++){
		WRITE_BIT_32(
				31-i,
				P_32,
				READ_BIT((31-( permutation[i]-1)),output.value_32)
		);
	}

}

void xorLeftPerm(uint32 &P_32, const DES_Data &permPlainText, uint32 &output)
{
	output =  (P_32)^(permPlainText.values_32.upper);
}


void sbox(DES_SBox_Input& input, DES_SBox_Output& output) {

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


void dataHandleRound(const DES_Data &permPlainText, DES_KeyType &roundKey, DES_Data &res) {

	// for final perm
	//DES_Data finalPermInput;
	res.values_32.upper = permPlainText.values_32.lower;

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

	uint32 P_32 = 0;
	Permutation(des_Sbox_Output, P_32);

	//Step 6
	xorLeftPerm(P_32, permPlainText, P_32);

	//Step 7
	res.values_32.lower = P_32;

}

/*******************************************************************************
 *                               Key Functions                                 *
 *******************************************************************************/
void KEY_PC1(DES_KeyType& key)
{
	uint8 value = 0;
	uint56 key56;
	key56.value = (uint64)0;
	uint8 PC_1[SIZE] = {  57, 49, 41, 33, 25, 17, 9,      \
			1, 58, 50, 42, 34, 26, 18,  \
			10, 2, 59, 51, 43, 35, 27,  \
			19, 11, 3, 60, 52, 44, 36,  \
			63, 55, 47, 39, 31, 23, 15, \
			7, 62, 54, 46, 38, 30, 22,  \
			14, 6, 61, 53, 45, 37, 29,  \
			21, 13, 5, 28, 20, 12, 4
	};
	for (uint8 i = 0 ; i < 56; i++)
	{
		value = READ_BIT2(key.value_64, 64 - PC_1[i]);
		WRITE_BIT_56( 55 - i,&key56, value);
	}
	key.value_56.value = key56.value;
}

//DES_KeyType keyparamaterized;

uint48 KEY_permutedchoice2(uint56 keyvalue)
{
	uint8 i = 1;
	uint8 posvalue = 0; //value of given position
	uint48 key48;
	key48.value = (uint64)0;
	for (i; i <= 48; i++)
	{
		posvalue = READ_BIT2(keyvalue.value, 56 - permutedchoice2table[i - 1]);
		KEY_WRITE_BIT_48(key48.value, 48 - i, posvalue);
	}

	return key48;
}


uint56 KEY_leftcircularshift(uint56 keyvalue, uint8 round)
{
	DES_KeyType keyvar;
	keyvar.value_56 = keyvalue;
	LCS(keyvar.values_28.upper, leftshiftschedule[round - 1]);
	LCS(keyvar.values_28.lower, leftshiftschedule[round - 1]);

	return keyvar.value_56;
}

/*Description:
 * Generates all input keys to their respective rounds and stores
 * their values inside the global array InputKeys[]*/
void generateKeys(DES_KeyType &key){

	DES_KeyType first_key = key;

	/*Step 1 : Permutation Choice 1*/

	KEY_PC1(first_key);

	/*Step 2 : Circular Shift Left + Permutation Choice 2*/
	for(int i = 1 ; i <= 16 ; i++){

		DES_KeyType nextKey , roundKey;

		nextKey.value_64 = 0 ;
		roundKey.value_64 = 0 ;

		nextKey.value_56 = KEY_leftcircularshift(first_key.value_56, i);
		roundKey.value_48 =KEY_permutedchoice2(nextKey.value_56);

		InputKeys[i-1] = roundKey;

		first_key = nextKey;

	}

	/*Acknowledging that all input Keys Are generated*/
	keyGenerated = true;


}

char GetDecimal(char c)
{
	/* 0 : 9 */
	if ((c >= 48) && (c <= 57 )) return c-48;
	/* A : F */
	if ((c >= 65) && (c <= 70 )) return c-55;
	/* a : f */
	if ((c >= 97) && (c <= 102 )) return c-87;
}
/*******************************************************************************
 *                        Encryption/Decryption Function                       *
 *******************************************************************************/

/*Description:
 * Performs either DES encryption or decryption based on the passed operation type.
 * It encrypts the given plainText and key and produces the result in the same variable data*/
void PerformOperation(DES_DataType & data,DES_KeyType &key , DES_OpType type){

	/*If input keys are not generated, generate them*/
	if(!keyGenerated){
		generateKeys(key);
	}

	DES_Data current = data.data  , temp ;

	temp.value_64 = 0 ;

	//Step 1 : Initial Permutation for Data and Permutation Choice 1 to the key

	initialPermutation(current,temp);


	//	cout<<"Data After Initial Permutation:";
	//	cout<<hex<<uppercase<<temp.value_64<<endl;


	//Step 2 : Perform Rounds

	for(int i = 1 ; i <= 16 ; i++){

		DES_Data output;
		output.value_64 = 0 ;

		DES_KeyType roundKey;
		if(type == ENCRYPT){
			roundKey = InputKeys[i-1];
		}
		else{
			roundKey = InputKeys[16-i];
		}

		dataHandleRound(temp, roundKey, output);

		//		cout<<"After Round "<<i<<":"<<endl;
		//		cout<<"Data:";
		//		cout<<hex<<uppercase<<output.value_64<<endl;
		//		cout<<"Input Key:";
		//		cout<<hex<<uppercase<<roundKey.value_64<<endl;

		temp = output;
	}

	//Step 3 : 32 bit Swap

	uint64 temporary = temp.values_32.lower ;
	temp.values_32.lower = temp.values_32.upper;
	temp.values_32.upper = temporary;

	//	cout<<"Data After 32- Bit Swap: "<<hex<<uppercase<<temp.value_64<<endl;

	//Step 4: Inverse Initial Permutation
	current.value_64 = 0;
	finalPermutation(temp, current);

	//	cout<<"Data After Inverse Permutation: "<<hex<<uppercase<<current.value_64<<endl;
	//Step 5: Modify final values:
	data.data = current;
}


/*******************************************************************************
 *                               Main Function                                 *
 *******************************************************************************/
int main(void){

	FILE *f ;

	string DataPath = "C:\\Users\\DELL\\Desktop\\DES_SAMPLE\\Data.txt";
	string KeyPath ="C:\\Users\\DELL\\Desktop\\DES_SAMPLE\\Key.txt";
	string OutPath = "C:\\Users\\DELL\\Desktop\\DES_SAMPLE\\yakan.txt";

	f=fopen(DataPath.c_str(),"rb");
	ifstream KeyFile(KeyPath);
	ofstream OutFile(OutPath);

	DES_KeyType key;


	KeyFile>>hex>>key.value_64;

	cout<<"Key is "<<hex<<uppercase<<key.value_64<<endl;

	DES_DataType plainText;
	plainText.data.value_64 = 0;

	char temp;

	do{

		plainText.data.value_64 = 0 ;
		bool flag = false;

		for(int i = 0 ; i < 8 ; i++){

			flag = false;

			temp = fgetc(f);

			if(temp == ' '){
				flag = true;
				break;
			}
			if(int(temp) == -1)
				break;

			plainText.array[8-i-1].upper = GetDecimal(temp);

			temp = fgetc(f);

			plainText.array[8-i-1 ].lower = GetDecimal(temp);

		}

		if(int(temp) == -1)
			break;

		if(flag != true){

			PerformOperation(plainText, key, ENCRYPT);

			cout<<"CipherText: "<<hex<<uppercase<<plainText.data.value_64<<endl;

			for(int j = 7 ; j >= 0 ; j--){


				OutFile<<hex<<uppercase<<(int)plainText.array[j].upper;
				OutFile<<hex<<uppercase<<(int)plainText.array[j].lower;

			}

		}


	}while(int(temp) != -1);

	cout<<"end";

	return 0;
}
