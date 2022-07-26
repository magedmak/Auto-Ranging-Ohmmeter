#include "STD_TYPES.h"
#include "BIT_MATH.h"
#define F_CPU 8000000UL
#include<avr/delay.h>

#include "GI_interface.h"
#include "DIO_interface.h"
#include "ADC_interface.h"
#include "alcd.h"

void initAll(void);
void setRange(u8 range);

u16 App_u16DigitalValue = 0xFFFF;
const u32 res_table[5] = {1000, 2180 , 10000, 100000, 2000000};

int main(void){
	initAll();
	u16 value = 0;


	while(1){
		u8 i;
		for(i=1; i<6; i++){
			setRange(i);
			_delay_ms(100);
			ADC_u8GetDigitalValueSync(ADC_u8_CHANNEL_5,&App_u16DigitalValue);
			if(App_u16DigitalValue <= 440){break;} // 2.15V => 440
		}

		if ((App_u16DigitalValue != 0xFFFF) && (App_u16DigitalValue < 1020)){                                                              //1020(1024) max analog read
			value =  ((App_u16DigitalValue * res_table[0])/(1023 - App_u16DigitalValue));                                                 //scale value = (Vref)5 * 1000
			LCD_u8GoToXY(1,0);
			LCD_voidWriteString("            ");
			LCD_u8GoToXY(1,0);
			LCD_voidWriteNumber(value);
			_delay_ms(2000);
			App_u16DigitalValue = 0xFFFF;
		}
		else if(App_u16DigitalValue >= 1020){
			LCD_u8GoToXY(1,0);
			LCD_voidWriteString("            ");
			LCD_u8GoToXY(1,0);
			LCD_voidWriteString("No Resistor");
			_delay_ms(1000);
		}
		else{
			LCD_u8GoToXY(1,0);
			LCD_voidWriteString("          ");
			LCD_u8GoToXY(1,0);
			LCD_voidWriteString("No Change");
		}
	}
	return 0;
}

void initAll(void){
	GI_voidEnable();
	DIO_voidInit();
	ADC_voidInit();
	LCD_voidInit();

	DIO_u8SetPinDirection (DIO_u8_PORTA,DIO_u8_PIN0,DIO_u8_OUTPUT);
	DIO_u8SetPinDirection (DIO_u8_PORTA,DIO_u8_PIN1,DIO_u8_OUTPUT);
	DIO_u8SetPinDirection (DIO_u8_PORTA,DIO_u8_PIN2,DIO_u8_OUTPUT);
	DIO_u8SetPinDirection (DIO_u8_PORTA,DIO_u8_PIN3,DIO_u8_OUTPUT);
	DIO_u8SetPinDirection (DIO_u8_PORTA,DIO_u8_PIN4,DIO_u8_OUTPUT);


	DIO_u8SetPinValue(DIO_u8_PORTA,DIO_u8_PIN0,DIO_u8_LOW);
	DIO_u8SetPinValue(DIO_u8_PORTA,DIO_u8_PIN1,DIO_u8_LOW);
	DIO_u8SetPinValue(DIO_u8_PORTA,DIO_u8_PIN2,DIO_u8_LOW);
	DIO_u8SetPinValue(DIO_u8_PORTA,DIO_u8_PIN3,DIO_u8_LOW);
	DIO_u8SetPinValue(DIO_u8_PORTA,DIO_u8_PIN4,DIO_u8_LOW);
}
void setRange(u8 range){

	if (range == 1){ // 1K range
		DIO_u8SetPinValue(DIO_u8_PORTA,DIO_u8_PIN0,DIO_u8_HIGH);
		DIO_u8SetPinValue(DIO_u8_PORTA,DIO_u8_PIN1,DIO_u8_LOW);
		DIO_u8SetPinValue(DIO_u8_PORTA,DIO_u8_PIN2,DIO_u8_LOW);
		DIO_u8SetPinValue(DIO_u8_PORTA,DIO_u8_PIN3,DIO_u8_LOW);
		DIO_u8SetPinValue(DIO_u8_PORTA,DIO_u8_PIN4,DIO_u8_LOW);
	}
	else if (range == 2){ // 2180 range
		DIO_u8SetPinValue(DIO_u8_PORTA,DIO_u8_PIN0,DIO_u8_LOW);
		DIO_u8SetPinValue(DIO_u8_PORTA,DIO_u8_PIN1,DIO_u8_HIGH);
		DIO_u8SetPinValue(DIO_u8_PORTA,DIO_u8_PIN2,DIO_u8_LOW);
		DIO_u8SetPinValue(DIO_u8_PORTA,DIO_u8_PIN3,DIO_u8_LOW);
		DIO_u8SetPinValue(DIO_u8_PORTA,DIO_u8_PIN4,DIO_u8_LOW);
	}
	else if (range == 3){ // 10K range
		DIO_u8SetPinValue(DIO_u8_PORTA,DIO_u8_PIN0,DIO_u8_LOW);
		DIO_u8SetPinValue(DIO_u8_PORTA,DIO_u8_PIN1,DIO_u8_LOW);
		DIO_u8SetPinValue(DIO_u8_PORTA,DIO_u8_PIN2,DIO_u8_HIGH);
		DIO_u8SetPinValue(DIO_u8_PORTA,DIO_u8_PIN3,DIO_u8_LOW);
		DIO_u8SetPinValue(DIO_u8_PORTA,DIO_u8_PIN4,DIO_u8_LOW);
	}
	else if (range == 4){ // 100K range
		DIO_u8SetPinValue(DIO_u8_PORTA,DIO_u8_PIN0,DIO_u8_LOW);
		DIO_u8SetPinValue(DIO_u8_PORTA,DIO_u8_PIN1,DIO_u8_LOW);
		DIO_u8SetPinValue(DIO_u8_PORTA,DIO_u8_PIN2,DIO_u8_LOW);
		DIO_u8SetPinValue(DIO_u8_PORTA,DIO_u8_PIN3,DIO_u8_HIGH);
		DIO_u8SetPinValue(DIO_u8_PORTA,DIO_u8_PIN4,DIO_u8_LOW);
	}
	else{ // 2M range
		DIO_u8SetPinValue(DIO_u8_PORTA,DIO_u8_PIN0,DIO_u8_LOW);
		DIO_u8SetPinValue(DIO_u8_PORTA,DIO_u8_PIN1,DIO_u8_LOW);
		DIO_u8SetPinValue(DIO_u8_PORTA,DIO_u8_PIN2,DIO_u8_LOW);
		DIO_u8SetPinValue(DIO_u8_PORTA,DIO_u8_PIN3,DIO_u8_LOW);
		DIO_u8SetPinValue(DIO_u8_PORTA,DIO_u8_PIN4,DIO_u8_HIGH);
	}
}
