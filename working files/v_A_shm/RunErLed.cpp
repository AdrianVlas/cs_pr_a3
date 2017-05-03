
#include "RunErLed.h"
#include <string.h>
#include "stm32f2xx.h"
#include "stm32f2xx_it.h"
#include "Ereg.h"
#include "prtTmr.h"
//#include "LULss.h"
#include "IStng.h"

CLURunErrorLed::CLURunErrorLed(void) {

}

CLURunErrorLed::~CLURunErrorLed(void) {

}
void CLURunErrorLed::UpdateRunErrorLed(void){

}
char chGBL_BP_StopRunErrorLed = 0;
char chErrorState = 0;
void CLURunErrorLed::EvalRunErrorLed(void){
long lStateLed;

    if(chGBL_BP_StopRunErrorLed == 1)
    asm(
                "bkpt 1"
                );
//State Led
    lStateLed = RUN_ERROR_LED_HIDE;
    if(chErrorState&1 )
     lStateLed = RUN_ERROR_LED_RED;
    else{
        if(chErrorState&2 )
     lStateLed = RUN_ERROR_LED_YELLOW;
     else 
     if(chErrorState&4)
     lStateLed = RUN_ERROR_LED_GREEN;
    } 
     LedStateUI32Bit.ul_val &= static_cast<unsigned long>(
        ~((1<< LED_IDX_EROR_C_BIT)|(1<< LED_IDX_RUN_BIT))   );
    
    if(lStateLed == RUN_ERROR_LED_GREEN){
        
        LedStateUI32Bit.ul_val |= (1<< LED_IDX_RUN_BIT);
    }
    else if(lStateLed == RUN_ERROR_LED_RED){
            // LedStateUI32Bit.ul_val &= static_cast<unsigned long>(
            // ~((1<< LED_IDX_BLOCK_BIT)|(1<< LED_IDX_ALARM_BIT))   );
            LedStateUI32Bit.ul_val |= (1<< LED_IDX_EROR_C_BIT);
    }
    else if(lStateLed == RUN_ERROR_LED_YELLOW){
            //LedStateUI32Bit.ul_val &=
            LedStateUI32Bit.ul_val |= (1<< LED_IDX_EROR_C_BIT)|(1<< LED_IDX_RUN_BIT);
    }
    
}

