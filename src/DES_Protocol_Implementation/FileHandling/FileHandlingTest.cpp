/******************************************************************************
 *
 * Module: File Handling Test
 *
 * File Name: FileHandlingTest.cpp
 *
 * Description: Testing File Handling to input data and key and to output encrypted data in file
 *
 *******************************************************************************/
#include <stdio.h>
#include "FileHandling.h"
using namespace std;

int main()
{
    char kfilename[] = { "Key.txt" };
    DES_KeyType key;
    DES_InputKeyHandling(&key, kfilename);
    printf("Key : %lld\n", key.value_64);
    char dfilename[] = { "Sample.txt" };
    char ofilename[] = { "Output.txt" };
    DES_DataType Blocks[20] = { 0 };
    char output[20 * 16];
    uint32 size = 0;
    DES_InputDataHandling(Blocks, dfilename, &size);
    DES_OutputDataHandling(Blocks, ofilename, output);
    return 0;
}
