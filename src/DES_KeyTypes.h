/******************************************************************************
 *
 * Module: DES Key Types
 *
 * File Name: DES_KeyTypes.h
 *
 * Description: Key types for DES Encryption
 *
 *******************************************************************************/

#ifndef DES_KEYTYPES_H_
#define DES_KEYTYPES_H_

#include "std_types.h"

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

#endif /* DES_KEYTYPES_H_ */
