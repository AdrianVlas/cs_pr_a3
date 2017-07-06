#ifndef I_SETTING_H
#define I_SETTING_H

#include <stdint.h>
#include "../inc/const_settings.h"
#include "../inc/macroses.h"
#include "../inc/const_global.h"
#include "../inc/const_menu_ver2.h"
#include "../inc/const_modbus_memory_map.h"
#include "../inc/type_definition.h"


enum TARAS_ALIAS_ID_LU_STNG { 

TARAS_ALAS_STNG_LU_AND  = ID_FB_AND,  
TARAS_ALAS_STNG_LU_OR   = ID_FB_OR ,  
TARAS_ALAS_STNG_LU_XOR  = ID_FB_XOR,
TARAS_ALAS_STNG_LU_TIMER = ID_FB_TIMER,
TARAS_ALAS_STNG_LU_TRIGGER = ID_FB_TRIGGER,
//Light sound Signaling
TARAS_ALAS_STNG_LU_ALARMS = ID_FB_ALARM,
//BGS Bus group Signaling
TARAS_ALAS_STNG_LU_BGS = ID_FB_GROUP_ALARM,
TARAS_ALAS_STNG_LU_MEANDERS = ID_FB_MEANDER,
TARAS_ALAS_STNG_LU_INPUT = ID_FB_INPUT,
TARAS_ALAS_STNG_LU_OUTPUT = ID_FB_OUTPUT,
TARAS_ALAS_STNG_LU_LED   = ID_FB_LED ,
TARAS_ALAS_STNG_LU_NOT   = ID_FB_NOT ,
TARAS_ALAS_STNG_LU_MFT   = ID_FB_TIMER,
TARAS_ALAS_STNG_LU_KEY  = ID_FB_BUTTON,
TARAS_ALAS_STNG_LU_TU = ID_FB_TU,
TARAS_ALAS_STNG_LU_TS = ID_FB_TS,

TARAS_ALAS_STNG_LU_UPPER_BOUND = _ID_FB_LAST_ALL
};
extern char chGlb_ActivatorWREeprom;






extern __CONFIG current_config_prt; 
extern __SETTINGS_FIX settings_fix_prt;
extern uintptr_t *spca_of_p_prt[];
//Define this by enum
extern const char chAmtSchematicElement; //Amount Types
extern char chGlbAmountRegisteredElem;
extern long lGlbRegisteredElemField;  


typedef long(*fnPvrL)(void *pv);
extern fnPvrL arrChangeCfgFnptr[];
extern long ChangeCfg(void* pv);


#endif
