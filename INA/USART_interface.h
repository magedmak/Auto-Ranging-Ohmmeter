/************************************************************************************************/
/*                                   Name    : Mohamed Basuoni                                  */
/*                                   Date    : 5/11/2021                                        */
/*                                   SWC     : USART                                            */
/*                                   Version : 1.0                                              */
/************************************************************************************************/

#ifndef USART_INTERFACE_H
#define USART_INTERFACE_H

void USART_voidInit(void);

void USART_voidSendByte(u8 Copy_u8TxByte);

u8 USART_u8ReceiveByte(void);

void USART_voidSendString(u8 *Copy_pu8String);

void USART_voidReceiveString(u8 *Copy_pu8String);


#endif
