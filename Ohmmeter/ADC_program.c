/************************************************************************************************/
/*                                   Name    : Mohamed Basuoni                                  */
/*                                   Date    : 9/10/2021                                        */
/*                                   SWC     : ADC                                               */
/*                                   Version : 1.0                                              */
/************************************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* MCAL */
#include "ADC_interface.h"
#include "ADC_private.h"

static void (*ADC_PtrFunc)(u16) = NULL;
static u8 ADC_u8BusyFlag = ADC_u8_NOT_BUSY;

void ADC_voidInit(void){
	/*   Select Vref = 2.56v       */
	//	SET_BIT(ADC_u8_ADMUX_REG,7);
	//	SET_BIT(ADC_u8_ADMUX_REG,6);

	/*   Select Vref = 5v       */
	CLR_BIT(ADC_u8_ADMUX_REG,7);
	SET_BIT(ADC_u8_ADMUX_REG,6);

	/*    Select Right Adjustment   */
	CLR_BIT(ADC_u8_ADMUX_REG,5);

	/*    Select Conversion Mode    */
	CLR_BIT(ADC_u8_ADCSRA_REG,5);

	/*    Select Prescaler  = 64    */
	SET_BIT(ADC_u8_ADCSRA_REG,2);
	SET_BIT(ADC_u8_ADCSRA_REG,1);
	CLR_BIT(ADC_u8_ADCSRA_REG,0);

	/*        ADC Enable            */
	SET_BIT(ADC_u8_ADCSRA_REG,7);
}

u8 ADC_u8GetDigitalValueSync(u8 Copy_u8ChannelNum,u16* Copy_Pu16ReturnedDigitalValue){
	u8 Local_u8ErrorState = STD_TYPES_OK;
	u32 Local_u32TimeOutCounter = 0;
	if((Copy_u8ChannelNum < 32) && (Copy_Pu16ReturnedDigitalValue != NULL)){
		/*  Clear Channel Region              */
		ADC_u8_ADMUX_REG &= 0b11100000;
		/*  Select Channel Number             */
		ADC_u8_ADMUX_REG |=  Copy_u8ChannelNum;
		/*  Start Conversion                  */
		SET_BIT(ADC_u8_ADCSRA_REG,6);
		/*  Wait For The Flag                 */

		while((Local_u32TimeOutCounter < 1000000UL) && (!GET_BIT(ADC_u8_ADCSRA_REG,4))){         //counter estimatation
			Local_u32TimeOutCounter++;
		}
		/*  Check Flag */
		if(GET_BIT(ADC_u8_ADCSRA_REG,4)){
			/*  Clear Flag                        */
			SET_BIT(ADC_u8_ADCSRA_REG,4);

			/*  Read Digital Value                */
			*Copy_Pu16ReturnedDigitalValue = ADC_u16_ADCDATA_REG;
		}
		else{
			Local_u8ErrorState = STD_TYPES_NOK;
		}
	}
	else{
		Local_u8ErrorState = STD_TYPES_NOK;
	}
	return Local_u8ErrorState;
}

u8 ADC_u8GetDigitalValueAsync(u8 Copy_u8ChannelNum,void(*Copy_PtrFunc)(u16)){
	u8 Local_u8ErrorState = STD_TYPES_OK;
	/* Check Channel Number , Check Pointers */
	if((ADC_u8BusyFlag == ADC_u8_NOT_BUSY) && (Copy_u8ChannelNum < 32) && (Copy_PtrFunc != NULL)){
		/* Set Busy Flag into Busy Flag  */
		ADC_u8BusyFlag = ADC_u8_BUSY;
		/* Update Global Pointers With input addresses        */
		ADC_PtrFunc = Copy_PtrFunc;
		/* Clear Channel Register                */
		ADC_u8_ADMUX_REG &= 0b11100000;
		/* Select ADC Channel                    */
		ADC_u8_ADMUX_REG |= Copy_u8ChannelNum;
		/* ADC Interrupt Enable                  */
		SET_BIT(ADC_u8_ADCSRA_REG,3);
		/* ADC Start Conversion                  */
		SET_BIT(ADC_u8_ADCSRA_REG,6);
		//Call ISR When Conversion is Complete
	}
	else{
		Local_u8ErrorState = STD_TYPES_NOK;
	}
	return Local_u8ErrorState;
}


void __vector_16(void) __attribute__((signal));
void __vector_16(void){
	if((ADC_PtrFunc != NULL)){
		/* Call Notification Function        */
		ADC_PtrFunc(ADC_u16_ADCDATA_REG);
		/* Disable Interrupt                 */
		CLR_BIT(ADC_u8_ADCSRA_REG,3);
		/* Set Busy Flag into Not Busy Flag  */
		ADC_u8BusyFlag = ADC_u8_NOT_BUSY;
	}
}
