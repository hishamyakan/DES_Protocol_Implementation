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
    fclose(f);
}
static char GetDecimal(char c)
{
    /* 0 : 9 */
    if ((c >= 48) && (c <= 57 )) return c-48;
    /* A : F */
    if ((c >= 65) && (c <= 70 )) return c-55;
    /* a : f */
    if ((c >= 97) && (c <= 102 )) return c-87;
}
