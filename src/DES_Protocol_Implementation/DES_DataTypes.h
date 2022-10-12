/******************************************************************************
 *
 * Module: DES Data Types
 *
 * File Name: DES_DataTypes.h
 *
 * Description: types for DES Encryption Data
 *
 *******************************************************************************/

#ifndef DES_DATATYPES_H_
#define DES_DATATYPES_H_

#include "std_types.h"

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
	uint4_2 array[8];

//	/*AND*/
//
//	DES_SBox_Input input; /*48-bit value or 8 6-bit values*/
//
//	/*AND*/
//
//	DES_SBox_Output output;  /*32-bit value or 8 4-bit values*/

}DES_DataType;

#endif /* DES_DATATYPES_H_ */
