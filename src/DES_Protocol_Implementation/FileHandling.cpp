/******************************************************************************
 *
 * Module: File Handling
 *
 * File Name: FileHandling.c
 *
 * Description: Handling Files to input data and key and to output encrypted data in file
 *
 *******************************************************************************/
#include "FileHandling.h"
#include <fstream>

static char GetDecimal(char c);
char outputsize = 0;
/********************************************************************************
* Function Description :
* Input : 1. Reference to key to fill in it value of key read from file (output)
*         2. Filename containing key .txt file
* Description : open the file , Read each hexadecimal digit as characters and convert
* to number then concatenate each 16 digit in one 64 Bit variable (var) then assign
* the 64 bit value to the key
**********************************************************************************/
//1) Hexadecimal or ascii

//2) Padding (left or right)

void DES_InputKeyHandling(DES_KeyType* key, char KeyFileName[])
{
    FILE *f;
    char c;
    uint64_t var = 0;
    char x;
    f=fopen(KeyFileName,"rb");
    while((c=fgetc(f))!=EOF)
    {
        x = GetDecimal(c);
        var = (var << 4 )|x;
        key->value_64 = var;
    }
    fclose(f);
}
/********************************************************************************
* Function Description :
* Input : 1. Reference to Data Blocks to fill in it value of Data Blocks read from file (output)
*         2. Filename containing Hex Data.txt file
*         3. Size is number of blocks filled while reading the file
* Description : open the file , Read each hexadecimal digit as characters and convert
* to number then concatenate each 16 digit in one 64 Bit variable (var) then assign
* the 64 bit value to the first data block [1 Block = 64 bits] then go to next block
**********************************************************************************/
void DES_InputDataHandling(DES_DataType Blocks[], char DataFileName[], uint32* size)
{
    FILE *f;
    char c;
    uint64_t var = 0;
    char x;
    unsigned char shifts = 0;
    int cnt = 0;
    f=fopen(DataFileName,"rb");
    while((c=fgetc(f))!=EOF)
    {
        x = GetDecimal(c);
        if(shifts == 16 )
        {
            cnt++;
            var = 0 ;
            shifts = 0 ;
        }
        var = (var << 4 )|x;
        Blocks[cnt].data.value_64 = var;
        shifts++;
    }
    *size = cnt+1;
    outputsize = *size;
    fclose(f);
}

/********************************************************************************
* Function Description :
* Input : 1. Reference to Data Blocks
*         2. Filename containing the txt file to write to
*         3. Char array to store the result of conversion of each block value to hex
* Description : open the file , Read each block value as characters and convert
* to hex character and store each character in an array then write this array
* to the output file
**********************************************************************************/
void DES_OutputDataHandling(DES_DataType Blocks[], char DataFileName[], char writeData[])
{
    FILE* f;
    uint64 quotient, remainder;
    int i = (outputsize * 16), j = outputsize - 1;

    writeData[i--] = '\0';

    fopen_s(&f, DataFileName, "w");
    while (j >= 0) //data array size
    {
        quotient = Blocks[j--].data.value_64;

        while (quotient != 0)
        {
            remainder = quotient % 16;

            if (remainder < 10) {
                writeData[i--] = 48 + (char)remainder;
            }
            else
            {
                writeData[i--] = 55 + (char)remainder;
            }
            quotient = quotient / 16;
        }
    }

    while (writeData[++i] != '\0')
    {
        fprintf(f, "%c", writeData[i]);
    }

    fclose(f);

}





/********************************************************************************
* Function Description :
* Input : character (hexadecimal digit)to convert to numeric value
* Description : from 0:9 corresponds to 48 : 57
                from A:F corresponds to 65 : 70
                from a:f corresponds to 97 : 102
**********************************************************************************/
static char GetDecimal(char c)
{
    /* 0 : 9 */
    if ((c >= 48) && (c <= 57 )) return c-48;
    /* A : F */
    if ((c >= 65) && (c <= 70 )) return c-55;
    /* a : f */
    if ((c >= 97) && (c <= 102 )) return c-87;
}
