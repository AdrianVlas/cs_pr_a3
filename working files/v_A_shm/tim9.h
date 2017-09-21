#ifndef TIM9_SETTING_H
#define TIM9_SETTING_H

#include <stdint.h>
//#include "../inc/const_settings.h"
//#include "../inc/macroses.h"
//#include "../inc/const_global.h"
//#include "../inc/const_menu_ver2.h"
//#include "../inc/const_modbus_memory_map.h"
//#include "../inc/type_definition.h"
#include "header.h" 
#include "I_Shm.h"



extern void TIM9ReInit(void* pv);
//extern void TIM9_Int_Init(u16 arr,u16 psc);
//extern void TIM9_NVIC_Init(void);
//extern void TIM9_IRQHandler(void);
//void TIM3_Int_Init_(u16 arr,u16 psc);
extern void TIM9Stop(void);
extern void TIM9Start(void);
extern void TIM9_Init(void);

#endif
