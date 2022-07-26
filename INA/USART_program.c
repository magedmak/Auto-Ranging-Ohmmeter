/************************************************************************************************/
/*                                   Name    : Mohamed Basuoni                                  */
/*                                   Date    : 5/11/2021                                        */
/*                                   SWC     : USART                                            */
/*                                   Version : 1.0                                              */
/************************************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "USART_interface.h"
#include "USART_private.h"
#include "USART_config.h"


void USART_voidInit(void){
	u8 Local_u8UCSRCValue = 0x80;

	/* No Double Speed */
	CLR_BIT(USART_u8_UCSRA_REG,1);
	/* Enable RX Circuit */
	SET_BIT(USART_u8_UCSRB_REG,4);
	/* Enable TX Circuit */
	SET_BIT(USART_u8_UCSRB_REG,3);
	/* Select 8 Bits Data */
	CLR_BIT(USART_u8_UCSRB_REG,2);
	SET_BIT(Local_u8UCSRCValue,2);
	SET_BIT(Local_u8UCSRCValue,1);

	/* Asynchronous Mode */
	CLR_BIT(Local_u8UCSRCValue,6);

	/* No Parity Mode */
	CLR_BIT(Local_u8UCSRCValue,5);
	CLR_BIT(Local_u8UCSRCValue,4);

    /* Stop Bits = 2 */
	SET_BIT(Local_u8UCSRCValue,3);

	/* Update USCRC REG with The Value of Variable */
	USART_u8_UCSRC_REG = Local_u8UCSRCValue;

	/* Baud Rate = 9600 */
	u16 Local_u8UBRRValue = 51;

	USART_u8_UBRRL_REG = (u8)Local_u8UBRRValue ;
	USART_u8_UBRRH_REG = (u8)(Local_u8UBRRValue>>8) ;
}

void USART_voidSendByte(u8 Copy_u8TxByte){
    /* Wait For Tx Register to Be Empty */
	while(!GET_BIT(USART_u8_UCSRA_REG,5));
	/* Send Byte */
	USART_u8_UDR_REG = Copy_u8TxByte ;
}

u8 USART_u8ReceiveByte(void){
while (!GET_BIT(USART_u8_UCSRA_REG,7));
/* Read Data */
return USART_u8_UDR_REG;
}

void USART_voidSendString(u8 *Copy_pu8String)
{
	while(*Copy_pu8String != '\0')
	{
		USART_voidSendByte(*Copy_pu8String);
		Copy_pu8String++;
	}
}

void USART_voidReceiveString(u8 *Copy_pu8String)
{
	u8 i = 0;
	Copy_pu8String[i] = USART_u8ReceiveByte();
	while(Copy_pu8String[i] != '.')
	{
		i++;
		Copy_pu8String[i] = USART_u8ReceiveByte();
	}
	Copy_pu8String[i] = '\0';
}
