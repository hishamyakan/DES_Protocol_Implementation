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


#define READ_BIT_BY_INDEX(DATA, INDEX) ((DATA)&((uint64)1<<INDEX))?1:0

#define PRINT_BINARY(DATA,SIZE) { \
		for(int i = (SIZE)-1 ; i>= 0 ; i--){ \
			\
			printf("%d" , ((DATA)&((uint64)1<<i))?1:0); \
			\
		}\
		puts("\n") ;\
}\

#define y 0
#ifdef y
















int main(void){


//	DES_Data plainText2;
//	plainText2.value_64= 0xF0F0E0E0C0C0A0A0;
//			//0b0000001000000010000000100000001000000000000000000000000000000000;
//
//
//	DES_Data  permPlainText2;
//	permPlainText2.value_64= 0;
//
//	DataHandler::initialPermutation(plainText2, permPlainText2);
//	PRINT_BINARY(permPlainText2.value_64,32);
//
//	uint48 EP_48;
//	EP_48.value = 0;
//	DataHandler::expansionPermutation(permPlainText2, EP_48);
//	PRINT_BINARY(EP_48.value,48);
//	uint48 EP_48;
//	EP_48.value = 0xDFFF0000FFF0;
//	DES_KeyType k;
//	k.value_48.value = 0x0000FFFF0000;


	DES_KeyType k;
	k.value_48.value = 0x194CD072DE8C;

	DES_Data plainText;
	plainText.value_64 = 0x123456ABCD132536;

	DES_Data  permPlainText;
	permPlainText.value_64 = 0x0;


	DataHandler::initialPermutation(plainText, permPlainText);
	cout<<"After Initial Perm: ";
	cout<<hex<<uppercase<<permPlainText.value_64<<endl;


	DES_Data res;
	DataHandler::dataHandleRound(permPlainText, k,res);
	cout<<hex<<uppercase<<res.values_32.upper<<" ";
	cout<<hex<<uppercase<<res.values_32.lower<<endl;

	k.value_64 = 0x0;
	k.value_48.value = 0x4568581ABCCE;
	permPlainText.value_64 = 0x0;
	DES_Data res2;
	DataHandler::dataHandleRound(res, k,res2);
	cout<<hex<<uppercase<<res2.values_32.upper<<" ";
	cout<<hex<<uppercase<<res2.values_32.lower<<endl;


	k.value_64 = 0x0;
	res.value_64 = 0x0;

	k.value_48.value = 0x06EDA4ACF5B5;



	DataHandler::dataHandleRound(res2, k,res);
	cout<<hex<<uppercase<<res.values_32.upper<<" ";
	cout<<hex<<uppercase<<res.values_32.lower<<endl;




//	PRINT_BINARY(permPlainText.values_32.lower, 32);
//	PRINT_BINARY(permPlainText.values_32.upper, 32);


//	    DES_KeyType k;
//		k.value_48.value = 0x4568581ABCCE;
////		DES_Data plainText ;
////		plainText.value_64 = 0x123456ABCD132536;
//		DES_Data  permPlainText;
//		permPlainText.value_64 = 0x18CA18AD5A78E394;
//
//	DES_Data permPlainText2 =DataHandler::dataHandleRound(permPlainText, k);
//	cout<<hex<<uppercase<<permPlainText2.values_32.upper<<" ";
//	cout<<hex<<uppercase<<permPlainText2.values_32.lower<<endl;

//	PRINT_BINARY(permPlainText.values_32.lower, 32);
//	PRINT_BINARY(permPlainText.values_32.upper, 32);



	return 0;
}
#endif












#ifdef x

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
	DES_Data plainText2;
	plainText2.value_64= 0b0000001000000010000000100000001000000000000000000000000000000000;

	DES_Data plainText3;
	plainText3.value_64 = 0x40404040;
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
	DES_Data  permPlainText2;
	permPlainText2.value_64= 0;
	DES_Data  permPlainText3;
	permPlainText3.value_64= 0;




	DES_Data trial;
	trial.value_64 = 0b0001001000110100010101101010101111001101000100110010010100110110;

	DES_Data res;
	DataHandler::initialPermutation(trial, res);
	cout<<res.value_64<<endl;
	PRINT_BINARY(res.value_64,64);

//	WRITE_BIT(0,permPlainText,READ_BIT(4,plainText));
//	WRITE_BIT(50,permPlainText,READ_BIT(2,plainText));



//	PRINT_BINARY(READ_BIT(1, plainText),1);

//	DataHandler::initialPermutation(plainText2, permPlainText2);
//	PRINT_BINARY(permPlainText2.value_64,64);
//	DataHandler::initialPermutation(plainText3, permPlainText3);
//	PRINT_BINARY(permPlainText3.value_64,64);



	return EXIT_SUCCESS;
}

#endif
