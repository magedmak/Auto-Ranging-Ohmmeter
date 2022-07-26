/************************************************************************************************/
/*                                   Name    : Mohamed Basuoni                                  */
/*                                   Date    : 8/10/2021                                        */
/*                                   SWC     : GI                                               */
/*                                   Version : 1.0                                              */
/************************************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GI_interface.h"
#include "GI_private.h"

void GI_voidEnable(void){
	SET_BIT(GI_u8_STATUS_REG,7);
}

void GI_voidDisable(void){
	CLR_BIT(GI_u8_STATUS_REG,7);
}
