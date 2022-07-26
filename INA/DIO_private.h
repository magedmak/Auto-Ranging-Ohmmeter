/************************************************************************************************/
/*                                   Name    : Mohamed Basuoni                                  */
/*                                   Date    : 11/9/2021                                        */
/*                                   SWC     : DIO                                              */
/*                                   Version : 1.0                                              */
/************************************************************************************************/
#ifndef DIO_PRIVATE_H
#define DIO_PRIVATE_H

/* Registers Definition for DIO */

        /* PORTA Registers */
#define DIO_u8_PORTA_REG *((volatile u8*)0X3B)
#define DIO_u8_DDRA_REG  *((volatile u8*)0X3A)
#define DIO_u8_PINA_REG  *((volatile u8*)0X39)
							 
        /* PORTB Registers */ 
#define DIO_u8_PORTB_REG *((volatile u8*)0X38)
#define DIO_u8_DDRB_REG  *((volatile u8*)0X37)
#define DIO_u8_PINB_REG  *((volatile u8*)0X36)
							 
        /* PORTC Registers */ 
#define DIO_u8_PORTC_REG *((volatile u8*)0X35)
#define DIO_u8_DDRC_REG  *((volatile u8*)0X34)
#define DIO_u8_PINC_REG  *((volatile u8*)0X33)
							 
	    /* PORTD Registers */ 
#define DIO_u8_PORTD_REG *((volatile u8*)0X32)
#define DIO_u8_DDRD_REG  *((volatile u8*)0X31)
#define DIO_u8_PIND_REG  *((volatile u8*)0X30)


#define DIO_u8_IN_INIT        0
#define DIO_u8_OUT_INIT       1



#define DIO_u8_IN_FLOATING    0
#define DIO_u8_IN_PULLED_UP   1
#define DIO_u8_OUT_LOW        0
#define DIO_u8_OUT_HIGH       1

#define PRIVATE_u8_CONC(b7,b6,b5,b4,b3,b2,b1,b0)       PRIVATE_u8_CONC_HELP(b7,b6,b5,b4,b3,b2,b1,b0)
#define PRIVATE_u8_CONC_HELP(b7,b6,b5,b4,b3,b2,b1,b0)  0b##b7##b6##b5##b4##b3##b2##b1##b0
#endif

