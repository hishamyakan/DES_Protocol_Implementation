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

void DES_InputKeyHandling(DES_KeyType* key, char KeyFileName[]);
void DES_InputDataHandling(DES_DataType Blocks[], char DataFileName[], uint32* size);

#endif /* FILEHANDLING_H_ */
