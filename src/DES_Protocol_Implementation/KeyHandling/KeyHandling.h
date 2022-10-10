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

inline uint8 READ_BIT(uint64 KEY, uint8 POS) {return ( KEY & ((uint64)1<<POS) )?1:0;}

inline void WRITE_BIT_56(uint8 bitNum, uint56* key,  uint8 value)
{
    if(value == STD_HIGH)
        key->value |= ((uint64)1<<bitNum);
    else
        key->value &= ~((uint64)1<<bitNum);
}

void KEY_PC1(DES_KeyType* key);

#endif /* KEYHANDLING_H_ */
