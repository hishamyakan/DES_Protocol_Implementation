/*
 ============================================================================
 Name        : Security2.c
 Author      :
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <iostream>

#include <stdio.h>
#include <stdlib.h>

#include "DES_DataTypes.h"
#include "DES_KeyTypes.h"

#include "DataHandler.h"

using namespace std;




#define PRINT_BINARY(DATA,SIZE) { \
		for(int i = (SIZE)-1 ; i>= 0 ; i--){ \
			\
			printf("%d" , ((DATA)&((uint64)1<<i))?1:0); \
			\
		}\
		puts("\n") ;\
}\


int main(void) {

//		DES_DataType number ;
//
//		number.data.value_64 = 0 ;
//
//		number.data.values_32.upper = ~0;
//
//
//		PRINT_BINARY(number.data.value_64 , 64);
//
//
//			number.input.value_48.value = ~0;
//			number.input.values_6.S0 = 0 ;
//			number.input.values_6.S7 = 0 ;
//
//		PRINT_BINARY(number.input.value_48.value , 48);
//
//
//		number.output.value_32 = ~0;
//		number.output.values_4.S0 = 0 ;
//
//		number.output.values_4.S7 = 0 ;
//
//		PRINT_BINARY(number.output.value_32 , 32);
//


//		DES_KeyType key;
//		key.value_64 = ~0 ;
//		key.value_56.value = 0;
//		key.value_48.value = ~0 ;
//		PRINT_BINARY(key.value_64, 64);
//
//
//		key.value_64 = 0 ;
//		key.values_28.upper = ~0 ;
//		PRINT_BINARY(key.value_64, 64);



	uint64 plainText1 = 0x202020200000000;
	uint64 plainText2 = 0b0000001000000010000000100000001000000000000000000000000000000000;

	uint64 plainText3 = 0x40404040;
//	uint64 plainText2 = 0b0000\
//						  0010\
//						  0000\
//						  0010\
//						  0000\
//						  0010\
//						  0000\
//						  0010\
//						  1000\
//						  0000\
//						  1000\
//						  0000\
//						  1000\
//						  0000\
//						  1000\
//						  0000;
	//PRINT_BINARY(plainText,64);
	uint64  permPlainText2 = 0;
	uint64  permPlainText3 = 0;




	//PRINT_BINARY(permPlainText,64);

//	WRITE_BIT(0,permPlainText,READ_BIT(4,plainText));
//	WRITE_BIT(50,permPlainText,READ_BIT(2,plainText));



//	PRINT_BINARY(READ_BIT(1, plainText),1);

	DataHandler::initialPermutation(plainText2, permPlainText2);
	PRINT_BINARY(permPlainText2,64);
	DataHandler::initialPermutation(plainText3, permPlainText3);
	PRINT_BINARY(permPlainText3,64);



	return EXIT_SUCCESS;
}
