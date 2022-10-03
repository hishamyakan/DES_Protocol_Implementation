/*
 ============================================================================
 Name        : Security2.c
 Author      :
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#include "DES_DataTypes.h"
#include "DES_KeyTypes.h"

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

	return EXIT_SUCCESS;
}
