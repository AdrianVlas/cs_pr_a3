
#include "RunErLed.h"
#include <string.h>
#include "stm32f2xx.h"
#include "stm32f2xx_it.h"
#include "Ereg.h"
#include "prtTmr.h"
//#include "LULss.h"
#include "IStng.h"
//#include "../inc/macroses.h"
#include "../inc/const_global.h"
//#include "../inc/variables_external.h"
extern uint8_t fix_block_active_state[];
extern unsigned int diagnostyka[2];
extern uint32_t *set_diagnostyka;
//#include "../inc/variables_external.h"
#include "../inc/const_menu2_diagnostyka.h"

// const unsigned long long  NON_FATAL_BIT_MASK  =  static_cast<unsigned long long>( 
// (1 << (ERROR_START_VIA_I2C_BIT                       ))
// | (static_cast<unsigned long long>(1) << (ERROR_INFO_REJESTRATOR_LOG_EEPROM_BIT         )) 
// | (static_cast<unsigned long long>(1) << (ERROR_INFO_REJESTRATOR_LOG_EEPROM_EMPTY_BIT   )) 
// | (static_cast<unsigned long long>(1) << (ERROR_INFO_REJESTRATOR_LOG_COMPARISON_BIT     )) 
// | (static_cast<unsigned long long>(1) << (ERROR_INFO_REJESTRATOR_LOG_CONTROL_BIT        )) 
// | (static_cast<unsigned long long>(1) << (ERROR_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT      )) 
// | (static_cast<unsigned long long>(1) << (ERROR_INFO_REJESTRATOR_PR_ERR_EEPROM_EMPTY_BIT)) 
// | (static_cast<unsigned long long>(1) << (ERROR_INFO_REJESTRATOR_PR_ERR_COMPARISON_BIT  )) 
// | (static_cast<unsigned long long>(1) << (ERROR_INFO_REJESTRATOR_PR_ERR_CONTROL_BIT     )) 
// | (static_cast<unsigned long long>(1) << (RTC_BATTERY_LOW_BIT                           )) 
// | (static_cast<unsigned long long>(1) << (RTC_OSCILLATOR_STOPED_BIT                     )) 
// | (static_cast<unsigned long long>(1) << (RTC_OSCILLATOR_FAIL_BIT                       )) 

// | (static_cast<unsigned long long>(1) << (RTC_UPDATING_HALTED_BIT                       )) 
// | (static_cast<unsigned long long>(1) << (RTC_WORK_FIELD_NOT_SET_BIT                    )) 
// | (static_cast<unsigned long long>(1) << (ERROR_LOG_OVERLOAD_BIT                        )) 
// | (static_cast<unsigned long long>(1) << (ERROR_LOG_LOSS_INFORMATION_BIT                )) 
// | (static_cast<unsigned long long>(1) << (ERROR_PR_ERR_OVERLOAD_BIT                     )) 
// | (static_cast<unsigned long long>(1) << (ERROR_PR_ERR_LOSS_INFORMATION_BIT             )) 
// | (static_cast<unsigned long long>(1) << (ERROR_LCD_BIT                                 )) 
// );

// const unsigned long long  FATAL_BIT_MASK  = static_cast<unsigned long long>(
 // (1<< (ERROR_USTUVANNJA_EEPROM_BIT))                 
// | (static_cast<unsigned long long>(1)<< (ERROR_USTUVANNJA_EEPROM_EMPTY_BIT             ))
// | (static_cast<unsigned long long>(1)<< (ERROR_USTUVANNJA_EEPROM_COMPARISON_BIT        ))
// | (static_cast<unsigned long long>(1)<< (ERROR_USTUVANNJA_EEPROM_CONTROL_BIT           ))
// | (static_cast<unsigned long long>(1)<< (ERROR_USTUVANNJA_EEPROM_ADJUSTMENT_ID_FAIL_BIT))
// | (static_cast<unsigned long long>(1)<< (ERROR_CONFIG_EEPROM_DEVICE_ID_FAIL_BIT        ))
// | (static_cast<unsigned long long>(1)<< (ERROR_CONFIG_EEPROM_BIT                       ))
// | (static_cast<unsigned long long>(1)<< (ERROR_CONFIG_EEPROM_EMPTY_BIT                 ))
// | (static_cast<unsigned long long>(1)<< (ERROR_CONFIG_EEPROM_COMPARISON_BIT            ))
// | (static_cast<unsigned long long>(1)<< (ERROR_CONFIG_EEPROM_CONTROL_BIT               ))
// | (static_cast<unsigned long long>(1)<< (ERROR_NO_FREE_DYNAMIC_MEMORY_BIT              ))
// | (static_cast<unsigned long long>(1)<< (ERROR_PRT_MEMORY_BIT                          ))
// | (static_cast<unsigned long long>(1)<< (ERROR_SETTINGS_EEPROM_BIT                     ))
// | (static_cast<unsigned long long>(1)<< (ERROR_SETTINGS_EEPROM_EMPTY_BIT               ))
// | (static_cast<unsigned long long>(1)<< (ERROR_SETTINGS_EEPROM_COMPARISON_BIT          ))
// | (static_cast<unsigned long long>(1)<< (ERROR_SETTINGS_EEPROM_CONTROL_BIT             ))
// | (static_cast<unsigned long long>(1)<< (ERROR_TRG_FUNC_EEPROM_BIT                     ))
// | (static_cast<unsigned long long>(1)<< (ERROR_TRG_FUNC_EEPROM_EMPTY_BIT               ))
// | (static_cast<unsigned long long>(1)<< (ERROR_TRG_FUNC_EEPROM_COMPARISON_BIT          ))
// | (static_cast<unsigned long long>(1)<< (ERROR_TRG_FUNC_EEPROM_CONTROL_BIT             ))
   
// | (static_cast<unsigned long long>(1)<< (ERROR_GND_ADC_TEST_BIT                        ))
// | (static_cast<unsigned long long>(1)<< (ERROR_VREF_ADC_TEST_BIT                       ))
// | (static_cast<unsigned long long>(1)<< (ERROR_VDD_ADC_TEST_BIT                        ))
// | (static_cast<unsigned long long>(1)<< (ERROR_GND_ADC_TEST_COARSE_BIT                 ))
// | (static_cast<unsigned long long>(1)<< (ERROR_VREF_ADC_TEST_COARSE_BIT                ))
// | (static_cast<unsigned long long>(1)<< (ERROR_VDD_ADC_TEST_COARSE_BIT                 ))
// | (static_cast<unsigned long long>(1)<< (ERROR_DIGITAL_OUTPUTS_BIT                     ))
// | (static_cast<unsigned long long>(1)<< (ERROR_SPI_DF_BIT                              ))
// | (static_cast<unsigned long long>(1)<< (ERROR_EXTERNAL_SRAM_BIT                       ))
// | (static_cast<unsigned long long>(1)<< (ERROR_INTERNAL_FLASH_BIT                      ))
// );




CLURunErrorLed::CLURunErrorLed(void) {

}

CLURunErrorLed::~CLURunErrorLed(void) {

}
void CLURunErrorLed::UpdateRunErrorLed(void){
//Set Input parameters
pIn = static_cast<void*>(arrPchIn);
//Set OutPut parameters
pOut = static_cast<void*>(arrOut);
}

char chGBL_BP_StopRunErrorLed = 0;
char chErrorState = 0;


void CLURunErrorLed::EvalRunErrorLed(void){
long lStateLed;
char *pCh;
//typedef struct{
//    union {
//    unsigned char  arCh[8];
//    unsigned short arSh[4];
//    unsigned long  arL[2];
//    unsigned long long llVal;
//    }UNN_DiagnFld;
//}SWrp;//*pSwrp;
//register SWrp *pSwrp;
//register UNN_DiagnFld *pDiagn;


    //pSwrp = reinterpret_cast<SWrp*>(&diagnostyka[0]);
    //pSwrp = reinterpret_cast<SWrp*>(set_diagnostyka);
    if(chGBL_BP_StopRunErrorLed == 1)
    asm volatile(
                "bkpt 1"
                );
//State Led
    lStateLed = RUN_ERROR_LED_HIDE;
    chErrorState &= ~7;
//    if(pSwrp->UNN_DiagnFld.llVal == 0)
//        chErrorState = 4;
//    else{    
//        if((pSwrp->UNN_DiagnFld.llVal)&(FATAL_BIT_MASK))
//            chErrorState |= 1;
//        else{
//            if((pSwrp->UNN_DiagnFld.llVal)&(NON_FATAL_BIT_MASK))
//                chErrorState |= 2;
//        }
//    }
    pCh = reinterpret_cast<char*>(fix_block_active_state);
    if( (*pCh)&((1<<FIX_BLOCK_AVAR_DEFECT)|(1<<FIX_BLOCK_DEFECT))){
        ;
        if((*pCh)&( 1 << FIX_BLOCK_AVAR_DEFECT )){
            chErrorState |= 1;
            arrOut[0] = 1;
        }    
        else{
                if((*pCh)&(1<<FIX_BLOCK_DEFECT)){
                    chErrorState |= 2;
                    arrOut[1] = 1;
                }
            }
    }
    else{
        if( (*pCh)&(1<<FIX_BLOCK_RUN) )
        chErrorState = 4;
        arrOut[0] = 0;
        arrOut[1] = 0;
}
    
    
    if(chErrorState&1 ){
    
     lStateLed = RUN_ERROR_LED_RED;
        DoStateUI32Bit.ul_val = 0;
        LedStateUI32Bit.ul_val = 0;
        DoHdwUI32Bit.ul_val = 0;
    }
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

