
#include "FixblWrp.hpp"
#include "../inc/constants.h"

#include <stdbool.h>
#include <math.h>
//#include <arm_math.h>
#include <stdlib.h>
#include <string.h>
#include "stm32f2xx.h"
#include "hw_config.h"
#include "../inc/macroses.h"
#include "../inc/type_definition.h"
#include "../inc/variables_external.h"//

extern uint8_t fix_block_active_state[];

extern uint32_t *set_diagnostyka;
//#include "../inc/variables_external.h"
#include "../inc/const_menu2_diagnostyka.h"



CFixBlockWrp::CFixBlockWrp(void) {
}

CFixBlockWrp::~CFixBlockWrp(void) {
}

CFixBlockWrp::CFixBlockWrp(char chM,char chI) {
chMaxIteratoin = chM;
	chIteration = chI;
chNumInput  = static_cast<char>(TOTAL_FIX_BLOCK_IN);//
chNumOutput = static_cast<char>(TOTAL_FIX_BLOCK_CMD);
memset(static_cast<void*>(arrPchIn),0xcc,sizeof(char*)*TOTAL_FIX_BLOCK_IN);
memset(static_cast<void*>(arrOut),0,sizeof(char  )*TOTAL_FIX_BLOCK_CMD);



}
void CFixBlockWrp::EvalCFixBlockWrpCmd(void){
//register long  rl_Val,i;

}

// 7. Таблиця налаштувань, розміри яких відомо на момент компіляції
// (Перечислення об’явлено у const_settings.h)
// enum _FIX_BLOCK_output_signals
// {
// FIX_BLOCK_DEFECT = 0, /*Загальна несправність*/
// FIX_BLOCK_AVAR_DEFECT, /*Аварійна несправність*/
// FIX_BLOCK_SETTINGS_CHANGED, /*Зміна налаштувань*/
// FIX_BLOCK_D_TRIGGER_STATE_INCORRECT, /*Заборонена комбінація на одному з D-
// Триґерів*/
// FIX_BLOCK_SCHEME_INCORRECT, /*У схеми не зафіксовано стаціонарного
// стану*/
// FIX_BLOCK_TEST_OUTPUT, /*Робота Тесту світлоіндикаторів*/
// FIX_BLOCK_SIGNALS_OUT /*Кількість вихідних сигналі загального блоку*/
// };
// enum _FIX_BLOCK_input_signals



//#pragma call_graph_root= "Shematic::Init2"
void FBWrp_Op(void *pObj){
CFixBlockWrp& rCFixBlockWrp = *(static_cast<CFixBlockWrp*> (pObj));
//char *pCh;
long l;
//rCFixBlockWrp.EvalCFixBlockWrpCmd();
    l = *(reinterpret_cast<unsigned char*>(fix_block_active_state));
    if(l&(1<<FIX_BLOCK_DEFECT)){
    rCFixBlockWrp.arrOut[ERROR_NC_CMD]         = 1;
    }
    else{
        
        rCFixBlockWrp.arrOut[ERROR_NC_CMD]         = 0;
    }
    if(l&(1<<FIX_BLOCK_AVAR_DEFECT)){
        rCFixBlockWrp.arrOut[ERROR_C_CMD]          = 1;
    }
    else{
        rCFixBlockWrp.arrOut[ERROR_C_CMD]          = 0;
    }
    
    if(l&(1<<(FIX_BLOCK_RUN))){
        rCFixBlockWrp.arrOut[RUN_CMD]              = 1;
    }
    else{
        rCFixBlockWrp.arrOut[RUN_CMD]              = 0;
    }
    if(l&(1<<FIX_BLOCK_SETTINGS_CHANGED)){
        rCFixBlockWrp.arrOut[CHANGE_SETTING_CMD]          = 1;
    }
    else{
        rCFixBlockWrp.arrOut[CHANGE_SETTING_CMD]          = 0;
    }    
    if(l&(1<<FIX_BLOCK_D_TRIGGER_STATE_INCORRECT)){
        rCFixBlockWrp.arrOut[TRIGER_FAULT_CMD]          = 1;
    }
    else{
        rCFixBlockWrp.arrOut[TRIGER_FAULT_CMD]          = 0;
    }    
    if(l&(1<<FIX_BLOCK_SCHEME_INCORRECT)){
        rCFixBlockWrp.arrOut[SHCEMATIC_FAULT_CMD]          = 1;
    }
    else{
        rCFixBlockWrp.arrOut[SHCEMATIC_FAULT_CMD]          = 0;
    }
    if(
    (measurement[4] >= l_1D15_UNOM) || (measurement[4] <= l_0D80_UNOM)
    )
        rCFixBlockWrp.arrOut[VCE_CMD]         = 1;
    else
        rCFixBlockWrp.arrOut[VCE_CMD]         = 0;




}


