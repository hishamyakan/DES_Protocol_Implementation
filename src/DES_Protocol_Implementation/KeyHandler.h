
#ifndef KEYHANDLER_H_
#define KEYHANDLER_H_

#include "DES_DataTypes.h"
#include "DES_KeyTypes.h"

#define READ_BIT(KEY,POS) ( KEY & ((uint64)1<<POS) )?1:0

#define WRITE_BIT(KEY,POS,VALUE) (KEY = (KEY&~((uint64)1<<POS)) | ((uint64)VALUE<<POS))

#define LCS(KEY,NUM) ( KEY = (KEY>>NUM) | (KEY << ((28-NUM))))

inline void WRITE_BIT_56(uint8 bitNum, uint56* key,  uint8 value)
{
    if(value == STD_HIGH)
        key->value |= ((uint64)1<<bitNum);
    else
        key->value &= ~((uint64)1<<bitNum);
}


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

uint56 KEY_leftcircularshift(uint56 keyvalue,uint8 round);

uint48 KEY_permutedchoice2(uint56 keyvalue);

DES_KeyType KEY_generation(DES_KeyType keyvalue, uint8 round);






#endif /* KEYHANDLER_H_*/
