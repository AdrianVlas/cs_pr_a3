#ifndef I_SETTING_H
#define I_SETTING_H

#include <stdint.h>
#include "../inc/const_settings.h"
#include "../inc/macroses.h"
#include "../inc/const_global.h"
#include "../inc/const_menu_ver2.h"
#include "../inc/const_modbus_memory_map.h"
#include "../inc/type_definition.h"
extern __CONFIG current_config_prt; 
//Define this by enum
extern const char chAmtSchematicElement; //Amount Types
extern char chGlbAmountRegisteredElem;
extern long lGlbRegisteredElemField;  


typedef long(*fnPvrL)(void *pv);
extern fnPvrL arrChangeCfgFnptr[];
extern long ChangeCfg(void* pv);


#endif
