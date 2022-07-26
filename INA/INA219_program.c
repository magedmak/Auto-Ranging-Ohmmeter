/************************************************************************************************/
/*                                   Name    : Mohamed Basuoni                                  */
/*                                   Date    : 18/5/2022                                        */
/*                                   SWC     : INA219 Current Sensor                            */
/*                                   Version : 1.0                                              */
/************************************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "I2C_interface.h"
#include "USART_interface.h"


#include "INA219_interface.h"
#include "INA219_private.h"
#include "INA219_config.h"

/* Global parameters */
u16 ina219_calibrationValue = 4096;
u8 ina219_currentDivider_mA = 10;
u8 ina219_powerMultiplier_mW = 2;




void INA219_voidInit(void){
	TWI_voidInit(0x50);
	//setCalibration_16V_400mA();
}


u8   INA219_u8Write2Bytes(u16 Copy_u16Byte,u8 Copy_u8ByteAddress){
	u8            Local_u8ErrorState = STD_TYPES_OK;
	TWI_ERR_STATE Local_EnuTWIErrorsState = TWI_OK;

	/* Send Start Condition  (Step 1) */
	Local_EnuTWIErrorsState = TWI_EnuSendStartCondition();
	if(Local_EnuTWIErrorsState != TWI_OK){
		Local_u8ErrorState = STD_TYPES_NOK;
		return Local_u8ErrorState;
	}
	/* Send Slave Address + Write operation (Step 2) */
	Local_EnuTWIErrorsState = TWI_EnuSendSlaveAddressWrite(0x40);
	if(Local_EnuTWIErrorsState != TWI_OK){
		Local_u8ErrorState = STD_TYPES_NOK;
		return Local_u8ErrorState;
	}

	/* Send Register Address (Step 3)*/
	Local_EnuTWIErrorsState = TWI_EnuSendDataByte(Copy_u8ByteAddress);
	if(Local_EnuTWIErrorsState != TWI_OK){
		Local_u8ErrorState = STD_TYPES_NOK;
		return Local_u8ErrorState;
	}


	/* (Step 4) Send Data */
	Local_EnuTWIErrorsState = TWI_EnuSendDataByte((u8)(Copy_u16Byte>>8));
	if(Local_EnuTWIErrorsState != TWI_OK){
		Local_u8ErrorState = STD_TYPES_NOK;
		return Local_u8ErrorState;
	}

	/* (Step 5) Send rest of Data */
	Local_EnuTWIErrorsState = TWI_EnuSendDataByte((u8)Copy_u16Byte);
	if(Local_EnuTWIErrorsState != TWI_OK){
		Local_u8ErrorState = STD_TYPES_NOK;
		return Local_u8ErrorState;
	}
	/* (Step 6) Send Stop Condition */
	Local_EnuTWIErrorsState = TWI_EnuSendStopCondition();
	if(Local_EnuTWIErrorsState != TWI_OK){
		Local_u8ErrorState = STD_TYPES_NOK;
		return Local_u8ErrorState;
	}
	return Local_u8ErrorState;
}

u8   INA219_u8Read2Bytes (u16 *Copy_pu16RecByte, u8 Copy_u8ByteAddress){
	u8            Local_u8ErrorState = STD_TYPES_OK;
	TWI_ERR_STATE Local_EnuTWIErrorsState = TWI_OK;
	u16 MSB = 0;
	u8 LSB = 0;

	if(Copy_pu16RecByte != NULL){
		/* (step 1) Send Start Condition  */
		Local_EnuTWIErrorsState = TWI_EnuSendStartCondition();
		if(Local_EnuTWIErrorsState != TWI_OK){
			Local_u8ErrorState = STD_TYPES_NOK;
			return Local_u8ErrorState;
		}
		/* Send Slave Address + Write operation (Step 2) */
		Local_EnuTWIErrorsState = TWI_EnuSendSlaveAddressWrite(INA219_ADDRESS);
		if(Local_EnuTWIErrorsState != TWI_OK){
			Local_u8ErrorState = STD_TYPES_NOK;
			return Local_u8ErrorState;
		}
		/* Send The rest of Byte Address (step 3)*/
		Local_EnuTWIErrorsState = TWI_EnuSendDataByte(Copy_u8ByteAddress);
		if(Local_EnuTWIErrorsState != TWI_OK){
			Local_u8ErrorState = STD_TYPES_NOK;
			return Local_u8ErrorState;
		}
		/* (Step 4) Repeated Start Condition */
		Local_EnuTWIErrorsState = TWI_EnuSendRepStartCondition();
		if(Local_EnuTWIErrorsState != TWI_OK){
			Local_u8ErrorState = STD_TYPES_NOK;
			return Local_u8ErrorState;
		}
		/* Step 5 => Send Slave Address + Read Operation */
		Local_EnuTWIErrorsState = TWI_EnuSendSlaveAddressRead(INA219_ADDRESS);
		if(Local_EnuTWIErrorsState != TWI_OK){
			Local_u8ErrorState = STD_TYPES_NOK;
			return Local_u8ErrorState;
		}
		/* Step 6 => Read Data */
		Local_EnuTWIErrorsState = TWI_EnuReadDataByte(&MSB);
		if(Local_EnuTWIErrorsState != TWI_OK){
			Local_u8ErrorState = STD_TYPES_NOK;
			return Local_u8ErrorState;
		}
		/* Step 7 => Read rest of Data */
		Local_EnuTWIErrorsState = TWI_EnuReadDataByte(&LSB);
		*Copy_pu16RecByte = ( (u16)MSB<<8 | LSB );
		if(Local_EnuTWIErrorsState != TWI_OK){
			Local_u8ErrorState = STD_TYPES_NOK;
			return Local_u8ErrorState;
		}
		/* (Step 8) Send Stop Condition */
		Local_EnuTWIErrorsState = TWI_EnuSendStopCondition();
		if(Local_EnuTWIErrorsState != TWI_OK){
			Local_u8ErrorState = STD_TYPES_NOK;
			return Local_u8ErrorState;
		}
	}
	else{
		Local_u8ErrorState = STD_TYPES_NOK;
	}
	return Local_u8ErrorState;
}

u8 setCalibration_16V_400mA(void){
	u8 Local_u8ErrorState = STD_TYPES_OK;

	INA219_u8Write2Bytes(ina219_calibrationValue,INA219_REG_CALIBRATION);

	u16 config = (INA219_CONFIG_BVOLTAGERANGE_16V |
			INA219_CONFIG_GAIN_1_40MV |
			INA219_CONFIG_BADCRES_12BIT |
			INA219_CONFIG_SADCRES_12BIT_1S_532US |
			INA219_CONFIG_MODE_SANDBVOLT_CONTINUOUS);

	INA219_u8Write2Bytes(config,INA219_REG_CONFIG);


	return Local_u8ErrorState;
}



f64 INA219_GetBusVoltage_V(void){
	u16 value = 0;

	INA219_u8Read2Bytes(&value,INA219_REG_BUSVOLTAGE);

	f64  ActualValue = ((value >> 3) * 4) * 0.001;

	return ActualValue;
}


f64 INA219_GetShuntVoltage_mV(void){
	u16 value = 0;

	INA219_u8Read2Bytes(&value,INA219_REG_SHUNTVOLTAGE);

	f64  ActualValue = value * 0.01;

	return ActualValue;
}


f64 INA219_GetLoadVoltage_mV(void){
	u16 BusValue = 0;
	u16 ShuntValue = 0;
	INA219_u8Read2Bytes(&BusValue,INA219_REG_BUSVOLTAGE);
	INA219_u8Read2Bytes(&ShuntValue,INA219_REG_SHUNTVOLTAGE);

	f64  ActualValue = ((BusValue >> 3) * 4) + (ShuntValue * 0.01) ;

	return ActualValue;
}


f64 INA219_GetLoadVoltage_V(void){
	u16 BusValue = 0;
	u16 ShuntValue = 0;
	INA219_u8Read2Bytes(&BusValue,INA219_REG_BUSVOLTAGE);
	INA219_u8Read2Bytes(&ShuntValue,INA219_REG_SHUNTVOLTAGE);

	f64  ActualValue = (((BusValue >> 3) * 4) + (ShuntValue * 0.01))/1000 ;

	return ActualValue;
}


f64 INA219_GetCurrent_mA(void) {
	u16 value = 0;


	/* Sometimes a sharp load will reset the INA219, which will
	reset the cal register, meaning CURRENT and POWER will not be available avoid this by always setting a cal value */

	INA219_u8Write2Bytes(ina219_calibrationValue,INA219_REG_CALIBRATION);

	INA219_u8Read2Bytes(&value,INA219_REG_CURRENT);

	f64  ActualValue = (f64)value / ina219_currentDivider_mA;

	return ActualValue;
}

f64 INA219_GetLoadPower_mW(void){
	u16 value = 0;

	/* Sometimes a sharp load will reset the INA219, which will
	reset the cal register, meaning CURRENT and POWER will not be available avoid this by always setting a cal value */

	INA219_u8Write2Bytes(ina219_calibrationValue,INA219_REG_CALIBRATION);

	INA219_u8Read2Bytes(&value,INA219_REG_POWER);

	f64  ActualValue = (f64)value * ina219_powerMultiplier_mW;

	return ActualValue;
}
