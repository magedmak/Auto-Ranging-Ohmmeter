/************************************************************************************************/
/*                                   Name    : Mohamed Basuoni                                  */
/*                                   Date    : 18/5/2022                                        */
/*                                   SWC     : INA219 Current Sensor                            */
/*                                   Version : 1.0                                              */
/************************************************************************************************/

#ifndef INA219_INTERFACE_H
#define INA219_INTERFACE_H

void INA219_voidInit(void);


u8   INA219_u8Write2Bytes(u16 Copy_u16Byte,u8 Copy_u8ByteAddress);


u8   INA219_u8Read2Bytes(u16 *Copy_pu16RecByte, u8 Copy_u8ByteAddress);


u8 SetCalibration_26V_3A(void);


u8 SetCalibration_16V_400mA(void);


f64 INA219_GetBusVoltage_V(void);


f64 INA219_GetShuntVoltage_mV(void);


f64 INA219_GetLoadVoltage_mV(void);


f64 INA219_GetLoadVoltage_V(void);


f64 INA219_GetCurrent_mA(void);


f64 INA219_GetLoadPower_mW(void);


#endif
