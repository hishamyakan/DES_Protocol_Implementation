/******************************************************************************
 *
 * Module: Key Handling
 *
 * File Name: KeyHandling.cpp
 *
 * Description: Handling Key to use for each round
 *
 *******************************************************************************/
#include"KeyHandling.h"

/* Write Bit value in 48 Bits key */
#define KEY_WRITE_BIT_48(KEY,POS,VALUE) (KEY = (KEY&~((uint64)1<<POS)) | ((uint64)VALUE<<POS))

/*to store 56 bit keyvalue from shift operation for the next round*/
DES_KeyType keyparamaterized;


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

/********************************************************************************
* Function Description :
* Input : Reference to key to fill in it value of 56 bit value variable (key56)
* Description : -Read each Bit value from values 1...64 map to read actual bits
*                63..0 using this equation (64 - PC_1[i]) example PC_1[0] = 57
*                becomes 64-57 = 7 , 7 is the bit I need to actually read
*               -Write in bits 1..56 but also map to the actual bits 55..0 using
*                this equation (55 - i) example i = 0 we write on Bit 55
**********************************************************************************/
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
	LCS(keyvar.values_28.upper, leftshiftschedule[round - 1]); //TODO Add the array
	LCS(keyvar.values_28.lower, leftshiftschedule[round - 1]);

	return keyvar.value_56;
}


DES_KeyType KEY_generation(DES_KeyType& keyvalue, uint8 round)
{
	if (round == 1)
	{
		KEY_PC1(keyvalue);

		// keyvalue->value_56 = KEY_leftcircularshift(keyvalue->value_56, round);
		// keyparamaterized.value_56 = keyvalue->value_56;
		//
		// keyvalue->value_48 = KEY_permutedchoice2(keyvalue->value_56);


	}
	// else
	// {
		keyvalue.value_56 = KEY_leftcircularshift(keyparamaterized.value_56, round);
		keyparamaterized.value_56 = keyvalue.value_56;

		keyvalue.value_48 = KEY_permutedchoice2(keyvalue.value_56);

	//}

	return keyvalue;
}
