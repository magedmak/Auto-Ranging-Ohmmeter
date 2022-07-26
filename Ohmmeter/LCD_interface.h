/************************************************************************************************/
/*                                   Name    : Mohamed Basuoni                                  */
/*                                   Date    : 18/9/2021                                        */
/*                                   SWC     : LCD                                              */
/*                                   Version : 1.0                                              */
/************************************************************************************************/
#ifndef LCD_INTERFACE_H
#define LCD_INTERFACE_H

#define LCD_u8_LINE_1  1
#define LCD_u8_LINE_2  2



void LCD_voidInit(void);

void LCD_voidWriteChar(u8 Copy_u8Char);

void LCD_voidWriteString(u8 Copy_u8String[]);

void LCD_voidWriteNumber(u16 Copy_u16Number);

void LCD_voidWriteCmnd(u8 Copy_u8Cmnd);

u8 LCD_u8GoToXY(u8 Copy_u8LineNumber,u8 Copy_u8_CharLocation);

#endif
