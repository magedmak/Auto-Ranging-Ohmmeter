/************************************************************************************************/
/*                                   Name    : Mohamed Basuoni                                  */
/*                                   Date    : 18/9/2021                                        */
/*                                   SWC     : LCD                                              */
/*                                   Version : 1.0                                              */
/************************************************************************************************/
#ifndef LCD_CONFIG_H
#define LCD_CONFIG_H


//  PORT D
/* Macros for Data Pins 4-bits Mode */
#define LCD_u8_PD7_PORT        DIO_u8_PORTD
#define LCD_u8_PD7_PIN         DIO_u8_PIN3


#define LCD_u8_PD6_PORT        DIO_u8_PORTD
#define LCD_u8_PD6_PIN         DIO_u8_PIN2

#define LCD_u8_PD5_PORT        DIO_u8_PORTD
#define LCD_u8_PD5_PIN         DIO_u8_PIN1

#define LCD_u8_PD4_PORT        DIO_u8_PORTD
#define LCD_u8_PD4_PIN         DIO_u8_PIN0



/* Options : 1- LCD_u8_8_BIT_MODE
             2- LCD_u8_4_BIT_MODE */

#define LCD_u8_MODE        LCD_u8_4_BIT_MODE

/* Config For LCD PINs */

/*Options : -For PORT: 1- DIO_u8_PORTA
                       2- DIO_u8_PORTB
                       3- DIO_u8_PORTC
                       4- DIO_u8_PORTD

             -For PIN: 1- DIO_u8_PIN0
                       2- DIO_u8_PIN1
                       3- DIO_u8_PIN2
                       4- DIO_u8_PIN3
                       1- DIO_u8_PIN4
                       2- DIO_u8_PIN5
                       3- DIO_u8_PIN6
                       4- DIO_u8_PIN7                   */



/* RS Pin*/
#define LCD_u8_RS_PORT              DIO_u8_PORTB
#define LCD_u8_RS_PIN               DIO_u8_PIN0

/* RW Pin*/
#define LCD_u8_RW_PORT              DIO_u8_PORTB
#define LCD_u8_RW_PIN               DIO_u8_PIN1


/* ENABLE Pin */
#define LCD_u8_EN_PORT               DIO_u8_PORTB
#define LCD_u8_EN_PIN                DIO_u8_PIN2

/* DATA Pins */
#define LCD_u8_DATA_PORT             DIO_u8_PORTD


#endif
