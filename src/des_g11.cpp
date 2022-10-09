/**
 * Description: Data Handler Functions
 * Authors: Hisham Yakan, Mohamed Mostafa
 *
 */

#define READ_BIT(bitNum ,PlainText) ((PlainText)&((uint64)1<<bitNum))?1:0
inline void WRITE_BIT(uint8 bitNum, uint64& permPlainText, uint8 value) { permPlainText |= ((uint64)value << bitNum); }