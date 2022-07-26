/************************************************************************************************/
/*                                   Name    : Mohamed Basuoni                                  */
/*                                   Date    : 9/10/2021                                        */
/*                                   SWC     : ADC                                              */
/*                                   Version : 1.0                                              */
/************************************************************************************************/

#ifndef ADC_INTERFACE_H
#define ADC_INTERFACE_H

/* Macros For ADC Channels */

#define ADC_u8_CHANNEL_0              0
#define ADC_u8_CHANNEL_1              1
#define ADC_u8_CHANNEL_2              2
#define ADC_u8_CHANNEL_3              3
#define ADC_u8_CHANNEL_4              4
#define ADC_u8_CHANNEL_5              5
#define ADC_u8_CHANNEL_6              6
#define ADC_u8_CHANNEL_7              7
#define ADC_u8_CHANNEL_8              8
#define ADC_u8_CHANNEL_9              9
#define ADC_u8_CHANNEL_10             10
#define ADC_u8_CHANNEL_11             11
#define ADC_u8_CHANNEL_12             12

void ADC_voidInit(void);

u8 ADC_u8GetDigitalValueSync(u8 Copy_u8ChannelNum,u16* Copy_Pu16ReturnedDigitalValue);

u8 ADC_u8GetDigitalValueAsync(u8 Copy_u8ChannelNum,void(*Copy_ptrfunc)(u16));

u8 ADC_u8GetDiffDigitalValue(u8 Copy_u8ChannelNum0,u8 Copy_u8ChannelNum1,u16* Copy_Pu16ReturnedDigitalValue);


#endif
