/******************************************************************************
 *
 * Module: Key Handling
 *
 * File Name: KeyHandling.h
 *
 * Description: Handling Key to use for each round
 *
 *******************************************************************************/

#ifndef KEYHANDLING_H_
#define KEYHANDLING_H_

#include "DES_KeyTypes.h"

#define SIZE 56

// /* Read Bit value in 64 Bits key */
//#define READ_BIT(KEY,POS) ( KEY & ((uint64)1<<POS) )?1:0

///* Write Bit value in 48 Bits key */
//#define WRITE_BIT_48(KEY,POS,VALUE) (KEY = (KEY&~((uint64)1<<POS)) | ((uint64)VALUE<<POS))

#define LCS(KEY,NUM) ( KEY = (KEY<<NUM) | (KEY >> ((28-NUM)))) // To check


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
/********************************************************************************
* Function Description :
* Input : Reference to key to fill in it value of 56 bit value variable (key56)
* Description : -Read each Bit value from values 1...64 map to read actual bits
*                63..0 using this equation (64 - PC_1[i]) example PC_1[0] = 57
*                becomes 64-57 = 7 , 7 is the bit I need to actually read
*               -Write in bits 1..56 but also map to the actual bits 55..0 using
*                this equation (55 - i) example i = 0 we write on Bit 55
**********************************************************************************/
void KEY_PC1(DES_KeyType& key);

uint56 KEY_leftcircularshift(uint56 keyvalue, uint8 round);

uint48 KEY_permutedchoice2(uint56 keyvalue);

DES_KeyType KEY_generation(DES_KeyType* keyvalue, uint8 round);

#endif /* KEYHANDLING_H_ */
