/************************************************************************************************/
/*                                   Name    : Mohamed Basuoni                                  */
/*                                   Date    : 18/9/2021                                        */
/*                                   SWC     : LCD                                              */
/*                                   Version : 1.0                                              */
/************************************************************************************************/

/* Library Layer */
#include <stdio.h>
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#define  F_CPU 8000000UL
#include <avr/delay.h>

/* MCAL */
#include "DIO_interface.h"


/*   HAL  */
#include "LCD_interface.h"
#include "LCD_private.h"
#include "LCD_config.h"



void LCD_voidInit(void){
	_delay_ms(35);
#if  (LCD_u8_MODE == LCD_u8_8_BIT_MODE)
	/* Send Function Set */
	LCD_voidWriteCmnd(0b00111000);
#elif (LCD_u8_MODE == LCD_u8_4_BIT_MODE)
	/* Send First Step of Function Set Command */
	/*1- Rs = 0 Select Command Register */
	DIO_u8SetPinValue(LCD_u8_RS_PORT,LCD_u8_RS_PIN,DIO_u8_LOW);
	/*2- Rw = 0 Write Operation      */
	DIO_u8SetPinValue(LCD_u8_RW_PORT,LCD_u8_RW_PIN,DIO_u8_LOW);

	DIO_u8SetPortValue(LCD_u8_DATA_PORT,0b00100000);
	/*         Send Enable Pulse         */
	DIO_u8SetPinValue(LCD_u8_EN_PORT,LCD_u8_EN_PIN,DIO_u8_HIGH);
	_delay_us(1);
	DIO_u8SetPinValue(LCD_u8_EN_PORT,LCD_u8_EN_PIN,DIO_u8_LOW);
	LCD_voidWriteCmnd(0b00101000);
#else
#error "Wrong Choice"
#endif
	_delay_us(40);
	/* Send Display on/off Control */
	LCD_voidWriteCmnd(0b00001111);
	_delay_us(40);
	/* Send Display Clear */
	LCD_voidWriteCmnd(0b00000001);
	_delay_ms(2);
	/* Send Entry Mode Set */
	LCD_voidWriteCmnd(0b00000110);
}

void LCD_voidWriteCmnd(u8 Copy_u8Cmnd){
	/*1- Rs = 0 Select Command Register */
	DIO_u8SetPinValue(LCD_u8_RS_PORT,LCD_u8_RS_PIN,DIO_u8_LOW);
	/*2- Rw = 0 Write Operation      */
	DIO_u8SetPinValue(LCD_u8_RW_PORT,LCD_u8_RW_PIN,DIO_u8_LOW);

#if (LCD_u8_MODE == LCD_u8_8_BIT_MODE)
	/*3- Send Data Byte to LCD       */
	DIO_u8SetPortValue(LCD_u8_DATA_PORT,Copy_u8Cmnd);
	/*4- Send Enable Pulse   		   */
	DIO_u8SetPinValue(LCD_u8_EN_PORT,LCD_u8_EN_PIN,DIO_u8_HIGH);
	_delay_us(1);
	DIO_u8SetPinValue(LCD_u8_EN_PORT,LCD_u8_EN_PIN,DIO_u8_LOW);
#elif  (LCD_u8_MODE == LCD_u8_4_BIT_MODE)
	/*3- Send Most 4-bits to LCD       */
	PRIVATE_voidSetHalfPort(Copy_u8Cmnd);
	//DIO_u8SetPortValue(LCD_u8_DATA_PORT,Copy_u8Cmnd);
	/*4- Send Enable Pulse   		   */
	DIO_u8SetPinValue(LCD_u8_EN_PORT,LCD_u8_EN_PIN,DIO_u8_HIGH);
	_delay_us(1);
	DIO_u8SetPinValue(LCD_u8_EN_PORT,LCD_u8_EN_PIN,DIO_u8_LOW);
	/*5- Send Least 4-bits to LCD       */
	PRIVATE_voidSetHalfPort(Copy_u8Cmnd<<4);
	//DIO_u8SetPortValue(LCD_u8_DATA_PORT,Copy_u8Cmnd<<4);
	/*6- Send Enable Pulse   		   */
	DIO_u8SetPinValue(LCD_u8_EN_PORT,LCD_u8_EN_PIN,DIO_u8_HIGH);
	_delay_us(1);
	DIO_u8SetPinValue(LCD_u8_EN_PORT,LCD_u8_EN_PIN,DIO_u8_LOW);
#else
#error "Wrong Choice"

#endif
}

void LCD_voidWriteChar(u8 Copy_u8Char){
	/*1- Rs = 1 Select Data Register */
	DIO_u8SetPinValue(LCD_u8_RS_PORT,LCD_u8_RS_PIN,DIO_u8_HIGH);
	/*2- Rw = 0 Write Operation      */
	DIO_u8SetPinValue(LCD_u8_RW_PORT,LCD_u8_RW_PIN,DIO_u8_LOW);
#if (LCD_u8_MODE == LCD_u8_8_BIT_MODE)
	/*3- Send Data Byte to LCD       */
	DIO_u8SetPortValue(LCD_u8_DATA_PORT,Copy_u8Char);
	/*4- Send Enable Pulse   		   */
	DIO_u8SetPinValue(LCD_u8_EN_PORT,LCD_u8_EN_PIN,DIO_u8_HIGH);
	_delay_us(1);
	DIO_u8SetPinValue(LCD_u8_EN_PORT,LCD_u8_EN_PIN,DIO_u8_LOW);
#elif  (LCD_u8_MODE == LCD_u8_4_BIT_MODE)
	/*3- Send Most 4-bits to LCD       */
	PRIVATE_voidSetHalfPort(Copy_u8Char);
	//DIO_u8SetPortValue(LCD_u8_DATA_PORT,Copy_u8Char);
	/*4- Send Enable Pulse   		   */
	DIO_u8SetPinValue(LCD_u8_EN_PORT,LCD_u8_EN_PIN,DIO_u8_HIGH);
	_delay_us(1);
	DIO_u8SetPinValue(LCD_u8_EN_PORT,LCD_u8_EN_PIN,DIO_u8_LOW);

	/*5- Send Least 4-bits to LCD       */
	PRIVATE_voidSetHalfPort(Copy_u8Char<<4);
	//DIO_u8SetPortValue(LCD_u8_DATA_PORT,Copy_u8Char<<4);
	/*6- Send Enable Pulse   		   */
	DIO_u8SetPinValue(LCD_u8_EN_PORT,LCD_u8_EN_PIN,DIO_u8_HIGH);
	_delay_us(1);
	DIO_u8SetPinValue(LCD_u8_EN_PORT,LCD_u8_EN_PIN,DIO_u8_LOW);

#else
#error "Wrong Choice"

#endif
}

void LCD_voidWriteString(u8 Copy_u8String[]){
	DIO_u8SetPinValue(LCD_u8_RS_PORT,LCD_u8_RS_PIN,DIO_u8_HIGH);
	DIO_u8SetPinValue(LCD_u8_RW_PORT,LCD_u8_RW_PIN,DIO_u8_LOW);
	u8 Local_u8StringIndex;

	for(Local_u8StringIndex=0 ; Copy_u8String[Local_u8StringIndex]!='\0' ; Local_u8StringIndex++){
		LCD_voidWriteChar(Copy_u8String[Local_u8StringIndex]);
	}
}

void LCD_voidWriteNumber(u16 Copy_u16Number){
	u8 Local_u16Number[6];
	DIO_u8SetPinValue(LCD_u8_RS_PORT,LCD_u8_RS_PIN,DIO_u8_HIGH);
	DIO_u8SetPinValue(LCD_u8_RW_PORT,LCD_u8_RW_PIN,DIO_u8_LOW);
	sprintf(Local_u16Number,"%u",Copy_u16Number);
	LCD_voidWriteString(Local_u16Number);
}



u8 LCD_u8GoToXY(u8 Copy_u8LineNumber,u8 Copy_u8_CharLocation){
	u8 Local_u8ErrorState = STD_TYPES_OK;
	if(Copy_u8_CharLocation<40){
		switch(Copy_u8LineNumber){
		case LCD_u8_LINE_1:
			LCD_voidWriteCmnd(0x80 + Copy_u8_CharLocation);
			break;
		case LCD_u8_LINE_2:
			LCD_voidWriteCmnd(0xC0 + Copy_u8_CharLocation);
			break;
		default:
			Local_u8ErrorState = STD_TYPES_NOK;
		}
	}
	else{
		Local_u8ErrorState = STD_TYPES_NOK;
	}
	return Local_u8ErrorState;
}
static void PRIVATE_voidSetHalfPort(u8 Copy_u8Data){
	if(GET_BIT(Copy_u8Data,7)){
		DIO_u8SetPinValue(LCD_u8_PD7_PORT,LCD_u8_PD7_PIN,DIO_u8_HIGH);
	}
	else{
		DIO_u8SetPinValue(LCD_u8_PD7_PORT,LCD_u8_PD7_PIN,DIO_u8_LOW);
	}
	if(GET_BIT(Copy_u8Data,6)){
		DIO_u8SetPinValue(LCD_u8_PD6_PORT,LCD_u8_PD6_PIN,DIO_u8_HIGH);
	}
	else{
		DIO_u8SetPinValue(LCD_u8_PD6_PORT,LCD_u8_PD6_PIN,DIO_u8_LOW);
	}
	if(GET_BIT(Copy_u8Data,5)){
		DIO_u8SetPinValue(LCD_u8_PD5_PORT,LCD_u8_PD5_PIN,DIO_u8_HIGH);
	}
	else{
		DIO_u8SetPinValue(LCD_u8_PD5_PORT,LCD_u8_PD5_PIN,DIO_u8_LOW);
	}
	if(GET_BIT(Copy_u8Data,4)){
		DIO_u8SetPinValue(LCD_u8_PD4_PORT,LCD_u8_PD4_PIN,DIO_u8_HIGH);
	}
	else{
		DIO_u8SetPinValue(LCD_u8_PD4_PORT,LCD_u8_PD4_PIN,DIO_u8_LOW);
	}

}
