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
