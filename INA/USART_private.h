/************************************************************************************************/
/*                                   Name    : Mohamed Basuoni                                  */
/*                                   Date    : 5/11/2021                                        */
/*                                   SWC     : USART                                            */
/*                                   Version : 1.0                                              */
/************************************************************************************************/
#ifndef USART_PRIVATE_H
#define USART_PRIVATE_H

#define USART_u8_UDR_REG             *((volatile u8*)0x2C)
#define USART_u8_UCSRA_REG           *((volatile u8*)0x2B)
#define USART_u8_UCSRB_REG           *((volatile u8*)0x2A)
#define USART_u8_UCSRC_REG           *((volatile u8*)0x40)

#define USART_u8_UBRRH_REG           *((volatile u8*)0x40)
#define USART_u8_UBRRL_REG           *((volatile u8*)0x29)


#endif

