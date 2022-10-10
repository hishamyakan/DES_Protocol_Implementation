
#include "KeyHandler.h"

DES_KeyType keyparamaterized;

uint48 KEY_permutedchoice2(uint56 keyvalue)
{
	uint8 i = 1;
	uint8 posvalue = 0; //value of given position
	uint48 key48;
	key48.value= (uint64)0;
	for (i; i <= 48; i++)
	{
		posvalue = READ_BIT(keyvalue.value,56-permutedchoice2table[i - 1]);
		WRITE_BIT(key48.value, 48-i, posvalue);
	}
	
	return key48;
}


uint56 KEY_leftcircularshift(uint56 keyvalue,uint8 round)
{
	DES_KeyType keyvar;
	keyvar.value_56 = keyvalue;
	LCS(keyvar.values_28.upper, leftshiftschedule[round - 1]);
	LCS(keyvar.values_28.lower, leftshiftschedule[round - 1]);
	
	return keyvar.value_56;
}


DES_KeyType KEY_generation(DES_KeyType keyvalue, uint8 round)
{
	if (round == 1)
	{
		//permutation choice 1

		keyvalue.value_56 = KEY_leftcircularshift(keyvalue.value_56, round);
		keyparamaterized.value_56 = keyvalue.value_56;

		keyvalue.value_48 = KEY_permutedchoice2(keyvalue.value_56);

		
	}
	else
	{
		keyvalue.value_56 = KEY_leftcircularshift(keyparamaterized.value_56, round);
		keyparamaterized.value_56 = keyvalue.value_56;

		keyvalue.value_48 = KEY_permutedchoice2(keyvalue.value_56);

	}
	
	return keyvalue;
}

