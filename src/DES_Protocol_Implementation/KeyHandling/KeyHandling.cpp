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

/*to store 56 bit keyvalue from shift operation for the next round*/
DES_KeyType keyparamaterized;

/********************************************************************************
* Function Description :
* Input : Reference to key to fill in it value of 56 bit value variable (key56)
* Description : -Read each Bit value from values 1...64 map to read actual bits
*                63..0 using this equation (64 - PC_1[i]) example PC_1[0] = 57
*                becomes 64-57 = 7 , 7 is the bit I need to actually read
*               -Write in bits 1..56 but also map to the actual bits 55..0 using
*                this equation (55 - i) example i = 0 we write on Bit 55
**********************************************************************************/
void KEY_PC1(DES_KeyType* key)
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
		value = READ_BIT(key->value_64, 64 - PC_1[i]);
		WRITE_BIT_56( 55 - i,&key56, value);
	}
    key->value_56.value = key56.value;
}

DES_KeyType keyparamaterized;

uint48 KEY_permutedchoice2(uint56 keyvalue)
{
	uint8 i = 1;
	uint8 posvalue = 0; //value of given position
	uint48 key48;
	key48.value = (uint64)0;
	for (i; i <= 48; i++)
	{
		posvalue = READ_BIT(keyvalue.value, 56 - permutedchoice2table[i - 1]);
		WRITE_BIT_48(key48.value, 48 - i, posvalue);
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


DES_KeyType KEY_generation(DES_KeyType* keyvalue, uint8 round)
{
	if (round == 1)
	{
		KEY_PC1(keyvalue);

		keyvalue->value_56 = KEY_leftcircularshift(keyvalue->value_56, round);
		keyparamaterized.value_56 = keyvalue->value_56;

		keyvalue->value_48 = KEY_permutedchoice2(keyvalue->value_56);


	}
	else
	{
		keyvalue->value_56 = KEY_leftcircularshift(keyparamaterized.value_56, round);
		keyparamaterized.value_56 = keyvalue->value_56;

		keyvalue->value_48 = KEY_permutedchoice2(keyvalue->value_56);

	}

	return *keyvalue;
}
