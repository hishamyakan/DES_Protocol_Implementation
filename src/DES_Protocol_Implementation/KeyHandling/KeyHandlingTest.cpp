/******************************************************************************
 *
 * Module: Key Handling Test
 *
 * File Name: KeyHandlingTest.cpp
 *
 * Description: Testing Key Handling to use for each round
 *
 *******************************************************************************/

#include <stdio.h>
#include "KeyHandling.h"

using namespace std;
/* Applying Permutation as Follow : */
/* Loop on PC_1 Array and at each index Read Bit in key at this index */
/* Mapping Required between indeces as indexing in PC_1 is  1......64  and Actual indexing is 63....0 in a 64_Bit key*/
/* Read Bit at certain Acutal index after mapping */
int main()
{
    DES_KeyType key;
    key.value_64 = 0x0123456789ABCDEF; /* 81985529216486895 */
    KEY_PC1(&key);
    printf("%lld",key.value_56.value ); /* expected output F0CCAA0AACCF00 =  67779025106161408 */
    return 0;
}
