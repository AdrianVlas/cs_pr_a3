
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
extern /*unsigned int diagnostyka[2]*/uint32_t *diagnostyka;
//#include "../inc/variables_external.h"
#include "../inc/const_menu2_diagnostyka.h"
const unsigned long long  NON_FATAL_BIT_MASK  =  static_cast<unsigned long long>( 
(1 << (ERROR_START_VIA_I2C_BIT                       ))
| (static_cast<unsigned long long>(1) << (ERROR_INFO_REJESTRATOR_LOG_EEPROM_BIT         )) 
| (static_cast<unsigned long long>(1) << (ERROR_INFO_REJESTRATOR_LOG_EEPROM_EMPTY_BIT   )) 
| (static_cast<unsigned long long>(1) << (ERROR_INFO_REJESTRATOR_LOG_COMPARISON_BIT     )) 
| (static_cast<unsigned long long>(1) << (ERROR_INFO_REJESTRATOR_LOG_CONTROL_BIT        )) 
| (static_cast<unsigned long long>(1) << (ERROR_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT      )) 
| (static_cast<unsigned long long>(1) << (ERROR_INFO_REJESTRATOR_PR_ERR_EEPROM_EMPTY_BIT)) 
| (static_cast<unsigned long long>(1) << (ERROR_INFO_REJESTRATOR_PR_ERR_COMPARISON_BIT  )) 
| (static_cast<unsigned long long>(1) << (ERROR_INFO_REJESTRATOR_PR_ERR_CONTROL_BIT     )) 
| (static_cast<unsigned long long>(1) << (RTC_BATTERY_LOW_BIT                           )) 
| (static_cast<unsigned long long>(1) << (RTC_OSCILLATOR_STOPED_BIT                     )) 
| (static_cast<unsigned long long>(1) << (RTC_OSCILLATOR_FAIL_BIT                       )) 

| (static_cast<unsigned long long>(1) << (RTC_UPDATING_HALTED_BIT                       )) 
| (static_cast<unsigned long long>(1) << (RTC_WORK_FIELD_NOT_SET_BIT                    )) 
| (static_cast<unsigned long long>(1) << (ERROR_LOG_OVERLOAD_BIT                        )) 
| (static_cast<unsigned long long>(1) << (ERROR_LOG_LOSS_INFORMATION_BIT                )) 
| (static_cast<unsigned long long>(1) << (ERROR_PR_ERR_OVERLOAD_BIT                     )) 
| (static_cast<unsigned long long>(1) << (ERROR_PR_ERR_LOSS_INFORMATION_BIT             )) 
| (static_cast<unsigned long long>(1) << (ERROR_LCD_BIT                                 )) 
);

const unsigned long long  FATAL_BIT_MASK  = static_cast<unsigned long long>(
 (1<< (ERROR_USTUVANNJA_EEPROM_BIT))                 
| (static_cast<unsigned long long>(1)<< (ERROR_USTUVANNJA_EEPROM_EMPTY_BIT             ))
| (static_cast<unsigned long long>(1)<< (ERROR_USTUVANNJA_EEPROM_COMPARISON_BIT        ))
| (static_cast<unsigned long long>(1)<< (ERROR_USTUVANNJA_EEPROM_CONTROL_BIT           ))
| (static_cast<unsigned long long>(1)<< (ERROR_USTUVANNJA_EEPROM_ADJUSTMENT_ID_FAIL_BIT))
| (static_cast<unsigned long long>(1)<< (ERROR_CONFIG_EEPROM_DEVICE_ID_FAIL_BIT        ))
| (static_cast<unsigned long long>(1)<< (ERROR_CONFIG_EEPROM_BIT                       ))
| (static_cast<unsigned long long>(1)<< (ERROR_CONFIG_EEPROM_EMPTY_BIT                 ))
| (static_cast<unsigned long long>(1)<< (ERROR_CONFIG_EEPROM_COMPARISON_BIT            ))
| (static_cast<unsigned long long>(1)<< (ERROR_CONFIG_EEPROM_CONTROL_BIT               ))
| (static_cast<unsigned long long>(1)<< (ERROR_NO_FREE_DYNAMIC_MEMORY_BIT              ))
| (static_cast<unsigned long long>(1)<< (ERROR_PRT_MEMORY_BIT                          ))
| (static_cast<unsigned long long>(1)<< (ERROR_SETTINGS_EEPROM_BIT                     ))
| (static_cast<unsigned long long>(1)<< (ERROR_SETTINGS_EEPROM_EMPTY_BIT               ))
| (static_cast<unsigned long long>(1)<< (ERROR_SETTINGS_EEPROM_COMPARISON_BIT          ))
| (static_cast<unsigned long long>(1)<< (ERROR_SETTINGS_EEPROM_CONTROL_BIT             ))
| (static_cast<unsigned long long>(1)<< (ERROR_TRG_FUNC_EEPROM_BIT                     ))
| (static_cast<unsigned long long>(1)<< (ERROR_TRG_FUNC_EEPROM_EMPTY_BIT               ))
| (static_cast<unsigned long long>(1)<< (ERROR_TRG_FUNC_EEPROM_COMPARISON_BIT          ))
| (static_cast<unsigned long long>(1)<< (ERROR_TRG_FUNC_EEPROM_CONTROL_BIT             ))
   
| (static_cast<unsigned long long>(1)<< (ERROR_GND_ADC_TEST_BIT                        ))
| (static_cast<unsigned long long>(1)<< (ERROR_VREF_ADC_TEST_BIT                       ))
| (static_cast<unsigned long long>(1)<< (ERROR_VDD_ADC_TEST_BIT                        ))
| (static_cast<unsigned long long>(1)<< (ERROR_GND_ADC_TEST_COARSE_BIT                 ))
| (static_cast<unsigned long long>(1)<< (ERROR_VREF_ADC_TEST_COARSE_BIT                ))
| (static_cast<unsigned long long>(1)<< (ERROR_VDD_ADC_TEST_COARSE_BIT                 ))
| (static_cast<unsigned long long>(1)<< (ERROR_DIGITAL_OUTPUTS_BIT                     ))
| (static_cast<unsigned long long>(1)<< (ERROR_SPI_DF_BIT                              ))
| (static_cast<unsigned long long>(1)<< (ERROR_EXTERNAL_SRAM_BIT                       ))
| (static_cast<unsigned long long>(1)<< (ERROR_INTERNAL_FLASH_BIT                      ))
);




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

typedef struct{
    union {
    unsigned char  arCh[8];
    unsigned short arSh[4];
    unsigned long  arL[2];
    unsigned long long llVal;
    }UNN_DiagnFld;
}SWrp;//*pSwrp;
register SWrp *pSwrp;
//register UNN_DiagnFld *pDiagn;


    pSwrp = reinterpret_cast<SWrp*>(&diagnostyka[0]);
    if(chGBL_BP_StopRunErrorLed == 1)
    asm(
                "bkpt 1"
                );
//State Led
    lStateLed = RUN_ERROR_LED_HIDE;
    chErrorState &= ~7;
    if(pSwrp->UNN_DiagnFld.llVal == 0)
        chErrorState = 4;
    else{    
        if((pSwrp->UNN_DiagnFld.llVal)&(FATAL_BIT_MASK))
            chErrorState |= 1;
        else{
            if((pSwrp->UNN_DiagnFld.llVal)&(NON_FATAL_BIT_MASK))
                chErrorState |= 2;
        }
    }
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

