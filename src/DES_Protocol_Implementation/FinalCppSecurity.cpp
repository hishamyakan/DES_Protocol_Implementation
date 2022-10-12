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
#include <fstream>
#include "DES_DataTypes.h"
#include "DES_KeyTypes.h"
#include "KeyHandling.h"
#include "DataHandler.h"
#include "FileHandling.h"
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


#define N 16

/*Boolean value to check whether all keys were generated or not*/
bool keyGenerated = false;

/*Array of input keys to their respective rounds*/
DES_KeyType InputKeys[16] = {0};

/*Enum that represents the type of operation to be performed*/
typedef enum{

	ENCRYPT , DECRYPT

}DES_OpType;

/*Description:
 * Generates all input keys to their respective rounds and stores
 * their values inside the global array InputKeys[]*/
void generateKeys(DES_KeyType &key){

	DES_KeyType first_key = key;

	/*Step 1 : Permutation Choice 1*/

	KEY_PC1(first_key);

	//	cout<<"Key After PC1:";
	//	cout<<hex<<uppercase<<first_key.value_64<<endl;

	/*Step 2 : Circular Shift Left + Permutation Choice 2*/
	for(int i = 1 ; i <= 16 ; i++){

		DES_KeyType nextKey , roundKey;

		nextKey.value_64 = 0 ;
		roundKey.value_64 = 0 ;

		nextKey.value_56 = KEY_leftcircularshift(first_key.value_56, i);
		roundKey.value_48 =KEY_permutedchoice2(nextKey.value_56);

		InputKeys[i-1] = roundKey;

		first_key = nextKey;

		//		cout<<hex<<uppercase<<InputKeys[i-1].value_64<<endl;
	}

	/*Acknowledging that all input Keys Are generated*/
	keyGenerated = true;


}

/*Description:
 * Performs either DES encryption or decryption based on the passed operation type.
 * It encrypts the given plainText and key and produces the result in the same variable data*/
void PerformOperation(DES_DataType & data,DES_KeyType &key , DES_OpType type){

	/*If input keys are not generated, generate them*/
	if(!keyGenerated){
		generateKeys(key);
	}

	DES_Data current = data.data  , temp ;

	temp.value_64 = 0 ;

	//Step 1 : Initial Permutation for Data and Permutation Choice 1 to the key

	initialPermutation(current,temp);


	//	cout<<"Data After Initial Permutation:";
	//	cout<<hex<<uppercase<<temp.value_64<<endl;


	//Step 2 : Perform Rounds

	for(int i = 1 ; i <= N ; i++){

		DES_Data output;
		output.value_64 = 0 ;

		DES_KeyType roundKey;
		if(type == ENCRYPT){
			roundKey = InputKeys[i-1];
		}
		else{
			roundKey = InputKeys[16-i];
		}

		DataHandler::dataHandleRound(temp, roundKey, output);

		//		cout<<"After Round "<<i<<":"<<endl;
		//		cout<<"Data:";
		//		cout<<hex<<uppercase<<output.value_64<<endl;
		//		cout<<"Input Key:";
		//		cout<<hex<<uppercase<<roundKey.value_64<<endl;

		temp = output;
	}

	//Step 3 : 32 bit Swap

	uint64 temporary = temp.values_32.lower ;
	temp.values_32.lower = temp.values_32.upper;
	temp.values_32.upper = temporary;

	//	cout<<"Data After 32- Bit Swap: "<<hex<<uppercase<<temp.value_64<<endl;

	//Step 4: Inverse Initial Permutation
	current.value_64 = 0;
	finalPermutation(temp, current);

	//	cout<<"Data After Inverse Permutation: "<<hex<<uppercase<<current.value_64<<endl;
	//Step 5: Modify final values:
	data.data = current;


}


DES_DataType buffer[1000];
volatile int buffer_size = 0 ;

int main(void){

	FILE *f ;


	string DataPath = "C:\\Users\\DELL\\Desktop\\DES_SAMPLE\\Data.txt";
	string KeyPath ="C:\\Users\\DELL\\Desktop\\DES_SAMPLE\\Key.txt";
	string OutPath = "C:\\Users\\DELL\\Desktop\\DES_SAMPLE\\yakan.txt";

	f=fopen(DataPath.c_str(),"rb");
	ifstream KeyFile(KeyPath);
	ofstream OutFile(OutPath);

	DES_KeyType key;


	KeyFile>>hex>>key.value_64;

	cout<<"Key is "<<hex<<uppercase<<key.value_64<<endl;

	DES_DataType plainText;
	plainText.data.value_64 = 0;

	char temp;

	do{

		plainText.data.value_64 = 0 ;
		bool flag = false;

		for(int i = 0 ; i < 8 ; i++){

			flag = false;

			temp = fgetc(f);

			if(temp == ' '){
				flag = true;
				break;
			}
			if(int(temp) == -1)
				break;

			plainText.array[8-i-1].upper = GetDecimal(temp);

			temp = fgetc(f);

			plainText.array[8-i-1 ].lower = GetDecimal(temp);

		}

		if(int(temp) == -1)
			break;
		//		printf("****** %c ******* %d \n",temp,temp);

		if(flag != true){
			//			cout<<"I Recieved "<<hex<<uppercase<<plainText.data.value_64<<endl;

			PerformOperation(plainText, key, ENCRYPT);

						cout<<"CipherText: "<<hex<<uppercase<<plainText.data.value_64<<endl;
			//TODO
			//			if(buffer_size < 1000){
			//
			//				buffer[buffer_size++] = plainText;
			//
			//			}
			//
			//			else{
			/*************/


			for(int j = 7 ; j >= 0 ; j--){


				OutFile<<hex<<uppercase<<(int)plainText.array[j].upper;
				OutFile<<hex<<uppercase<<(int)plainText.array[j].lower;

			}


		//TODO
		//				buffer_size = 0 ;
		//			}
		/*************/
		//			OutFile<<hex<<uppercase<<plainText.data.value_64;
		//			for(int i = 7 ; i >= 0 ; i--){
		//
		//				//				char value = plainText.array[i].upper;
		//				//
		//				//				if( plainText.array[i].upper >= 'A' && plainText.array[i].upper <= 'Z'){
		//				//
		//				//					value+=
		//				//
		//				//				}
		//				OutFile<<hex<<uppercase<<(int)plainText.array[i].upper;
		//				OutFile<<hex<<uppercase<<(int)plainText.array[i].lower;
		//
		//			}

	}


}while(int(temp) != -1);

//TODO
//	for(int i = 0 ; i < buffer_size ; i++){
//
//		for(int j = 7 ; j >= 0 ; j--){
//
//
//			OutFile<<hex<<uppercase<<(int)buffer[i].array[j].upper;
//			OutFile<<hex<<uppercase<<(int)buffer[i].array[j].lower;
//
//		}
//
//	}
cout<<"end";
//	string DataPath , KeyPath , OutputPath ;
//
//	cout<<"Enter the path of the file containing the plainText content:"<<endl;
//
//	cin>>DataPath;
//
//	cout<<"Enter the path of the file containing the Key content:"<<endl;
//
//	cin>>KeyPath ;
//
//	cout<<"Enter the path of the file to hold the ciphertext content:"<<endl;
//
//	cin>>OutputPath ;
//
//	ifstream DataFile(DataPath) , KeyFile(KeyPath);
//
//	ofstream OutputFile(OutputPath);
//
//	DES_Data plainText  ;
//
//	plainText.value_64 = 0 ;
//
//	DES_KeyType key ;
//
//	KeyFile>>hex>>key.value_64;
//
//	cout<<"Key is "<<hex<<uppercase<<key.value_64<<endl;
//
//	while(DataFile>>hex>>plainText.value_64){
//
//		DES_DataType temp ;
//		temp.data = plainText;
//
//		PerformOperation(temp, key, ENCRYPT);
//
//		OutputFile<<hex<<uppercase<<temp.data.value_64<<" ";
//	}

/****************************************************************/


//	DES_Data plainText;
//	plainText.value_64 = 0x123456ABCD132536;
//
//
//	DES_Data  permPlainText;
//	permPlainText.value_64 = 0x0;
//
//
//	DES_DataType firstData ;
//	firstData.data.value_64 = plainText.value_64;
//	DES_KeyType firstKey ;
//	firstKey.value_64 = 0xAABB09182736CCDD;

//	encrypt(firstData, firstKey);
//
//	cout<<endl<<"CipherText: "<<hex<<uppercase<<firstData.data.value_64<<endl;
//	cout<<endl<<"Final Key: "<<hex<<uppercase<<firstKey.value_64<<endl;
//
//	encrypt(firstData,firstKey);

//	generateKeys(firstKey);

//	PerformOperation(firstData,firstKey, ENCRYPT);
//
//	cout<<endl<<"CipherText: "<<hex<<uppercase<<firstData.data.value_64<<endl;
//
//	PerformOperation(firstData,firstKey, DECRYPT);
//
//	cout<<endl<<"PlainText: "<<hex<<uppercase<<firstData.data.value_64<<endl;

#ifdef back
initialPermutation(plainText, permPlainText);
cout<<"After Initial Perm: ";
cout<<hex<<uppercase<<permPlainText.value_64<<endl;

DES_Data res;
cout<<"Round 1 : ";

DataHandler::dataHandleRound(permPlainText, k,res);
cout<<hex<<uppercase<<res.values_32.upper<<" ";
cout<<hex<<uppercase<<res.values_32.lower<<endl;

cout<<"Round 2 : ";

k.value_48.value = 0x0;
k.value_48.value = 0x4568581ABCCE;
permPlainText.value_64 = 0x0;
DataHandler::dataHandleRound(res, k,permPlainText);
cout<<hex<<uppercase<<permPlainText.values_32.upper<<" ";
cout<<hex<<uppercase<<permPlainText.values_32.lower<<endl;


DES_Data res2;
res2.value_64 = 0x0;
res2.values_32.lower = permPlainText.values_32.upper;
res2.values_32.upper = permPlainText.values_32.lower;
cout<<hex<<uppercase<<permPlainText.values_32.upper<<" "<<permPlainText.values_32.lower<<endl;
DES_Data res3;
res3.value_64 = 0x0;
finalPermutation(res2, res3);

//cout<<hex<<uppercase<<res3.values_32.upper<<" "<<res3.values_32.lower<<endl;

//Decrypt

cout<<"Dec"<<endl;
DES_Data d1,d2 , d3 ,d4 ,d5;
DES_KeyType DK;
DK.value_48.value = 0x4568581ABCCE;
initialPermutation(res3,d1);




cout<<hex<<uppercase<<d1.values_32.upper<<" "<<d1.values_32.lower<<endl;

cout<<"Round 1 Dec ";
DataHandler::dataHandleRound(d1, DK,d2);
cout<<hex<<uppercase<<d2.values_32.upper<<" ";
cout<<hex<<uppercase<<d2.values_32.lower<<endl;

cout<<"Round 2 Dec ";

DK.value_48.value = 0x0;
DK.value_48.value = 0x194CD072DE8C;
DataHandler::dataHandleRound(d2, DK,d3);
cout<<hex<<uppercase<<d3.values_32.upper<<" ";
cout<<hex<<uppercase<<d3.values_32.lower<<endl;


d4.values_32.upper = d3.values_32.lower;
d4.values_32.lower = d3.values_32.upper;


cout<<"Result: ";
cout<<hex<<uppercase<<d4.value_64<<endl;

d5.value_64 =0x0;
finalPermutation(d4, d5);
cout<<hex<<uppercase<<d5.value_64<<endl;


#endif



return 0;
}




#ifdef needed
void encrypt(DES_DataType & data , DES_KeyType &key){



	DES_Data current = data.data  , temp ;
	DES_KeyType current_key = key , final_key;

	final_key.value_64 = 0;
	temp.value_64 = 0 ;

	//Step 1 : Initial Permutation for Data and Permutation Choice 1 to the key

	initialPermutation(current,temp);

	KEY_PC1(current_key);
	cout<<"Data After Initial Permutation:";
	cout<<hex<<uppercase<<temp.value_64<<endl;
	cout<<"Key After PC1:";
	cout<<hex<<uppercase<<current_key.value_64<<endl;


	//Step 2 : Perform Rounds

	for(int i = 1 ; i <= N ; i++){

		DES_KeyType nextKey , roundKey;
		nextKey.value_64 = 0 ;
		roundKey.value_64 = 0 ;

		//Key for the next round
		nextKey.value_56 = KEY_leftcircularshift(current_key.value_56, i);
		//Input Key to the Data Block
		roundKey.value_48 =KEY_permutedchoice2(nextKey.value_56);

		DES_Data output;
		output.value_64 = 0 ;

		DataHandler::dataHandleRound(temp, roundKey, output);

		cout<<"After Round "<<i<<":"<<endl;
		cout<<"Data:";
		cout<<hex<<uppercase<<output.value_64<<endl;
		cout<<"Input Key:";
		cout<<hex<<uppercase<<roundKey.value_64<<endl;

		current_key = nextKey;
		temp = output;
		if(i == 16){
			final_key = roundKey;
		}
	}

	//Step 3 : 32 bit Swap

	uint64 temporary = temp.values_32.lower ;
	temp.values_32.lower = temp.values_32.upper;
	temp.values_32.upper = temporary;

	cout<<"Data After 32- Bit Swap: "<<hex<<uppercase<<temp.value_64<<endl;

	//Step 4: Inverse Initial Permutation
	current.value_64 = 0;
	finalPermutation(temp, current);

	cout<<"Data After Inverse Permutation: "<<hex<<uppercase<<current.value_64<<endl;
	//Step 5: Modify final values:
	data.data = current;
	key = current_key;

}
#endif




