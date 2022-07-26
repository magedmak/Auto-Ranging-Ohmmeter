/************************************************************************************************/
/*                                   Name    : Mohamed Basuoni                                  */
/*                                   Date    : 13/11/2021                                        */
/*                                   SWC     : I2C                                              */
/*                                   Version : 1.0                                              */
/************************************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "USART_interface.h"

#include "I2C_interface.h"
#include "I2C_private.h"
#include "I2C_config.h"

void TWI_voidInit(u8 Copy_u8SlaveAddress){

	/* Enable TWI and Enable ACK */
	SET_BIT(TWI_u8_TWCR_REG,2);
	SET_BIT(TWI_u8_TWCR_REG,6);
	/* Set Clk 100KHz with no Prescaler */
	CLR_BIT(TWI_u8_TWSR_REG,1);
	CLR_BIT(TWI_u8_TWSR_REG,0);

	TWI_u8_TWBR_REG = 32;
	/* Assign my Own Address => TWAR */
	TWI_u8_TWAR_REG = Copy_u8SlaveAddress<<1;
}

TWI_ERR_STATE TWI_EnuSendStartCondition(void){
	TWI_ERR_STATE Local_EnuErrorState = TWI_OK;
	//	/* Send Start Condition */
	SET_BIT(TWI_u8_TWCR_REG,5);
	//	/* Clear Flag to Start the new job */
	SET_BIT(TWI_u8_TWCR_REG,7);
	/* Wait for The Flag */
	while(!GET_BIT(TWI_u8_TWCR_REG,7));
	/* Check Status Code (ACK) */
	if((TWI_u8_TWSR_REG & 0xF8) != 0x08){
		USART_voidSendString("Start Problem");
		Local_EnuErrorState = TWI_SC_ERROR;
	}
	else{
		/* Clear Start Condition Bit */
		//CLR_BIT(TWI_u8_TWCR_REG,5);
	}
	return Local_EnuErrorState;
}

TWI_ERR_STATE TWI_EnuSendRepStartCondition(void){
	TWI_ERR_STATE Local_EnuErrorState = TWI_OK;
	/* Send Start Condition */
	SET_BIT(TWI_u8_TWCR_REG,5);
	/* Clear Flag to Start the new job */
	SET_BIT(TWI_u8_TWCR_REG,7);
	/* Wait for The Flag */
	while(!GET_BIT(TWI_u8_TWCR_REG,7));
	/* Check Status Code (ACK) */
	if((TWI_u8_TWSR_REG & 0xF8) != 0x10){
		USART_voidSendString("REPStart Problem");
		Local_EnuErrorState = TWI_RSC_ERROR;
	}
	else{
		/* Clear Start Condition Bit */
		//CLR_BIT(TWI_u8_TWCR_REG,5);
	}
	return Local_EnuErrorState;
}

TWI_ERR_STATE TWI_EnuSendSlaveAddressWrite(u8 Copy_u8SlaveAddress){
	TWI_ERR_STATE Local_EnuErrorState= TWI_OK;
	/* Write Slave Address into TWDR Reg + 0(Write) */
	TWI_u8_TWDR_REG = Copy_u8SlaveAddress<<1 ;
	/* Select Write Operation */
	CLR_BIT(TWI_u8_TWDR_REG,0);
	/* Clear Start Condition Bit */
	CLR_BIT(TWI_u8_TWCR_REG,5);
	/* Clear Flag to Start New Job*/
	SET_BIT(TWI_u8_TWCR_REG,7);
	/* Wait for The Flag */
	while(!GET_BIT(TWI_u8_TWCR_REG,7));
	/* Check Status Code (ACK) */
	if((TWI_u8_TWSR_REG & 0xF8) != 0x18){
		USART_voidSendString("Write address Problem");
		Local_EnuErrorState = TWI_SLA_W_ERROR;
	}
	return Local_EnuErrorState;
}

TWI_ERR_STATE TWI_EnuSendDataByte(u8 Copy_u8Byte){
	TWI_ERR_STATE Local_EnuErrorState= TWI_OK;
	/* Write Byte TWDR Reg */
	TWI_u8_TWDR_REG = Copy_u8Byte;
	/* Clear Flag to Start New Job*/
	SET_BIT(TWI_u8_TWCR_REG,7);
	/* Wait for The Flag*/
	while(!GET_BIT(TWI_u8_TWCR_REG,7));
	/* Check Status Code (ACK) */
	if((TWI_u8_TWSR_REG & 0xF8) != 0x28){
		USART_voidSendString("send data Problem");
		Local_EnuErrorState = TWI_DATA_T_ERROR;
	}

	return Local_EnuErrorState;
}

TWI_ERR_STATE TWI_EnuSendSlaveAddressRead (u8 Copy_u8SlaveAddress){
	TWI_ERR_STATE Local_EnuErrorState= TWI_OK;
	/* Write Slave Address into TWDR Reg + 0(Write) */
	TWI_u8_TWDR_REG = Copy_u8SlaveAddress<<1 ;
	/* Select Write Operation */
	SET_BIT(TWI_u8_TWDR_REG,0);
	/* Clear Start Condition Bit */
	CLR_BIT(TWI_u8_TWCR_REG,5);
	/* Clear Flag to Start New Job*/
	SET_BIT(TWI_u8_TWCR_REG,7);
	/* Wait for The Flag */
		while(!GET_BIT(TWI_u8_TWCR_REG,7));
	/* Check Status Code (ACK) */
	if((TWI_u8_TWSR_REG & 0xF8) != 0x40){
		USART_voidSendString("Read Address Problem");
		Local_EnuErrorState = TWI_SLA_R_ERROR;
	}
	return Local_EnuErrorState;
}

TWI_ERR_STATE TWI_EnuReadDataByte(u8* Copy_Pu8RecByte){
	TWI_ERR_STATE Local_EnuErrorState= TWI_OK;
	if(Copy_Pu8RecByte != NULL){
		/* Start Job Of Reading */
		SET_BIT(TWI_u8_TWCR_REG,7);
		/* Wait for The Flag*/
		while(!GET_BIT(TWI_u8_TWCR_REG,7));
		/* Check Status Code (ACK) */
		if((TWI_u8_TWSR_REG & 0xF8) != 0x50){
			USART_voidSendString("Read Data Problem");
			Local_EnuErrorState = TWI_DATA_R_ERROR;
		}
		else{ /* Valid Data */
			*Copy_Pu8RecByte = TWI_u8_TWDR_REG;
		}
	}
	else{
		Local_EnuErrorState = TWI_NULL_POINTER;
	}
	return Local_EnuErrorState;

}

TWI_ERR_STATE TWI_EnuSendStopCondition(void){
	TWI_ERR_STATE Local_EnuErrorState= TWI_OK;
	/* Send Stop Condition */
	SET_BIT(TWI_u8_TWCR_REG,4);
	/* Clear Flag to Start the new job */
	SET_BIT(TWI_u8_TWCR_REG,7);

	return Local_EnuErrorState;

}
