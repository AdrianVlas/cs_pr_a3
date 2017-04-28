
#include "MALed.hpp"
#include <string.h>
#include "stm32f2xx.h"
#include "stm32f2xx_it.h"
#include "Ereg.h"
#include "prtTmr.h"
//#include "LULss.h"
#include "IStng.h"
extern void GetLssMuteAlarmBlockAddr(void* pv);//wraper for EvalIdxinarrLUAreaListElem
CMuteAlarmLed::CMuteAlarmLed(void) {
}

CMuteAlarmLed::~CMuteAlarmLed(void) {
}
void CMuteAlarmLed::UpdateMuteAlarmLed(void) {
}
char chGBL_BP_StopMuteAlarmLed = 0;
//char ch
void CMuteAlarmLed::EvalMuteAlarmLed(void) {
long lStateLed;
MuteAlarmInOutParam locMuteAlarmInOutParam;
//Detect Amount LSS
short shLC__n_alarm = current_config_prt.n_alarm;
short shCounterScanCLULss = 0;
memset(static_cast<void*> (&locMuteAlarmInOutParam), 0, sizeof (MuteAlarmInOutParam));
struct {
char arrChCmd[TOTAL_MUTE_ALARM_LED_IN];

    } sLV;
    sLV.arrChCmd[MUTE_ALARM_LED_IN_NAME__BLOCK - 1] = 0;
    sLV.arrChCmd[MUTE_ALARM_LED_IN_NAME__ALARM - 1] = 0;
    sLV.arrChCmd[MUTE_ALARM_LED_IN_NAME__MUTE  - 1] = 0;
    if(chGBL_BP_StopMuteAlarmLed == 1)
    asm(
                "bkpt 1"
                );
//Hold command
    do{
        locMuteAlarmInOutParam.lIndexLss = shCounterScanCLULss;
        GetLssMuteAlarmBlockAddr(static_cast<void*> (&locMuteAlarmInOutParam));//
        sLV.arrChCmd[MUTE_ALARM_LED_IN_NAME__BLOCK - 1] |= locMuteAlarmInOutParam.pChBlock[0];
        sLV.arrChCmd[MUTE_ALARM_LED_IN_NAME__ALARM - 1] |= locMuteAlarmInOutParam.pChAlarm[0];
        sLV.arrChCmd[MUTE_ALARM_LED_IN_NAME__MUTE  - 1] |= locMuteAlarmInOutParam.pChMute [0];
    }while(++shCounterScanCLULss < shLC__n_alarm );
   
//State Led
    lStateLed = MUTE_ALARM_HIDE;
    //if(locMuteAlarmInOutParam.pChBlock[0]>0)
    if(sLV.arrChCmd[MUTE_ALARM_LED_IN_NAME__BLOCK - 1]>0)
     lStateLed = MUTE_ALARM_GREEN;
    else{
     //if(locMuteAlarmInOutParam.pChAlarm[0]>0)
     if( sLV.arrChCmd[MUTE_ALARM_LED_IN_NAME__ALARM - 1])
     lStateLed = MUTE_ALARM_RED;
     else 
    // if(locMuteAlarmInOutParam.pChMute[0]>0)
     if( sLV.arrChCmd[MUTE_ALARM_LED_IN_NAME__MUTE  - 1])
     lStateLed = MUTE_ALARM_YELLOW;
    } 
    LedStateUI32Bit.ul_val &= static_cast<unsigned long>(
        ~((1<< LED_IDX_BLOCK_BIT)|(1<< LED_IDX_ALARM_BIT))   );
    
    if(lStateLed == MUTE_ALARM_GREEN){
        
        LedStateUI32Bit.ul_val |= (1<< LED_IDX_BLOCK_BIT);
    }
    else if(lStateLed == MUTE_ALARM_RED){
            // LedStateUI32Bit.ul_val &= static_cast<unsigned long>(
            // ~((1<< LED_IDX_BLOCK_BIT)|(1<< LED_IDX_ALARM_BIT))   );
            LedStateUI32Bit.ul_val |= (1<< LED_IDX_ALARM_BIT);
    }
    else if(lStateLed == MUTE_ALARM_YELLOW){
            //LedStateUI32Bit.ul_val &=
            LedStateUI32Bit.ul_val |= (1<< LED_IDX_BLOCK_BIT)|(1<< LED_IDX_ALARM_BIT);
    }
}
 
