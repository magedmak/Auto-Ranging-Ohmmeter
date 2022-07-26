/************************************************************************************************/
/*                                   Name    : Mohamed Basuoni                                  */
/*                                   Date    : 9/10/2021                                        */
/*                                   SWC     : ADC                                             */
/*                                   Version : 1.0                                              */
/************************************************************************************************/
#ifndef ADC_PRIVATE_H
#define ADC_PRIVATE_H

/*     Define ADC Registers   */

#define ADC_u8_SFIOR_REG                            *((volatile u8*)0X50)
#define ADC_u8_ADMUX_REG                            *((volatile u8*)0X27)
#define ADC_u8_ADCSRA_REG                           *((volatile u8*)0X26)

#define ADC_u8_ADCH_REG                             *((volatile u8*)0X25)
#define ADC_u8_ADCL_REG                             *((volatile u8*)0X24)

#define ADC_u16_ADCDATA_REG                         *((volatile u16*)0X24)       //Read two Register Low & High

#define ADC_u8_NOT_BUSY                              0
#define ADC_u8_BUSY                                  1

#endif

