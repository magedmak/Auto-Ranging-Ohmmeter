/*
 * main.c
 *
 *  Created on: May 21, 2022
 *      Author: MGM
 */

#include "STD_TYPES.h"
#define F_CPU 8000000UL
#include <avr/delay.h>
#include <stdlib.h>
#include <string.h>
#include "DIO_interface.h"
#include "INA219_interface.h"
#include "USART_interface.h"


int main(void){
	DIO_voidInit();
	USART_voidInit();
	INA219_voidInit();

	f64 num = 0;
	u8 Label[32] = "INA219 Readings\r";
	USART_voidSendString(Label);
	u8 ValueStr[32];

	while(1){
		/*strcpy(Label,"\rBus Voltage (V) = ");
		USART_voidSendString(Label);
		num = (INA219_GetBusVoltage_V());
		dtostrf(num,-6,6,ValueStr);
		USART_voidSendString(ValueStr);

		strcpy(Label,"\rShunt Voltage (mV) = ");
		USART_voidSendString(Label);
		num = (INA219_GetShuntVoltage_mV());
		dtostrf(num,-6,6,ValueStr);
		USART_voidSendString(ValueStr);

		strcpy(Label,"\rLoad Voltage (mV) = ");
		USART_voidSendString(Label);
		num = (INA219_GetLoadVoltage_mV());
		dtostrf(num,-6,6,ValueStr);
		USART_voidSendString(ValueStr);*/

		strcpy(Label,"\rCurrent (mA) = ");
		USART_voidSendString(Label);
		num = (INA219_GetCurrent_mA());
		dtostrf(num,-6,6,ValueStr);
		USART_voidSendString(ValueStr);

		/*strcpy(Label,"\rLoad Power (mW) = ");
		USART_voidSendString(Label);
		num = (INA219_GetLoadPower_mW());
		dtostrf(num,-6,6,ValueStr);
		USART_voidSendString(ValueStr);*/
		_delay_ms(2000);
	}
	return 0;
}

