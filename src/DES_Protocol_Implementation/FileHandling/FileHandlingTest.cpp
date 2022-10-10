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
    DES_InputKeyHandling(&key,kfilename);
    printf("Key : %lld\n",  key.value_64);
    char dfilename[] = { "Sample.txt" };
    DES_DataType Blocks[20] = {0};
    uint32 size = 0;
    DES_InputDataHandling(Blocks,dfilename,&size);
    for (int i = 0 ; i <size ; i++)
    {
        printf("Block %d : ", i+1);
        printf(" %lld   ", Blocks[i].data.value_64);
    }
    return 0;
}
