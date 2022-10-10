/******************************************************************************
 *
 * Module: File Handling
 *
 * File Name: FileHandling.h
 *
 * Description: Handling Files to input data and key and to output encrypted data in file
 *
 *******************************************************************************/

#ifndef FILEHANDLING_H_
#define FILEHANDLING_H_

#include "DES_DataTypes.h"
#include "DES_KeyTypes.h"
/********************************************************************************
* Function Description :
* Input : 1. Reference to key to fill in it value of key read from file (output)
*         2. Filename containing key .txt file
* Description : open the file , Read each hexadecimal digit as characters and convert
* to number then concatenate each 16 digit in one 64 Bit variable (var) then assign
* the 64 bit value to the key
**********************************************************************************/
void DES_InputKeyHandling(DES_KeyType* key, char KeyFileName[]);
/********************************************************************************
* Function Description :
* Input : 1. Reference to Data Blocks to fill in it value of Data Blocks read from file (output)
*         2. Filename containing Hex Data.txt file
*         3. Size is number of blocks filled while reading the file
* Description : open the file , Read each hexadecimal digit as characters and convert
* to number then concatenate each 16 digit in one 64 Bit variable (var) then assign
* the 64 bit value to the first data block [1 Block = 64 bits] then go to next block
**********************************************************************************/
void DES_InputDataHandling(DES_DataType Blocks[], char DataFileName[], uint32* size);

#endif /* FILEHANDLING_H_ */
