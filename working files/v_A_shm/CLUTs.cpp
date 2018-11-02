
#include "CLUTs.hpp"
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




char chGBL_BP_StopLUTs = 0;
void Ts__2_1_Op  (void *pObj){
CLUTs& rCLUTs = *(static_cast<CLUTs *> (pObj));
    long k, j, l; //

    k = 0;
    if(chGBL_BP_StopLUTs == rCLUTs.shShemasOrdNumStng)
    asm volatile(
    "bkpt 1"
    );  
    __LN_TS* pLN_TS = static_cast<__LN_TS *>(rCLUTs.pvCfgLN);
    j = *(rCLUTs.arrPchIn[Ts__2_1_IN_NAME__CI-1]);
    l = *(rCLUTs.arrPchIn[Ts__2_1_IN_NAME__BLOCK-1]);
    if((j > 0)&&(l == 0))
    k |= 1;
    
    if(k == 0) {
        //l = *(rCLUTs.arrPchIn[Ts__2_1_IN_NAME__INF_REQ-1]);//???
        
        k = pLN_TS->add_input_state[(TS_SIGNALS_ADD_INPUT/8)] & (1<<(TS_READING%8));
        l = !k;
        if(rCLUTs.chIn_C == 0 && k > 0){
        //reset Ts
            rCLUTs.chQ = 0;
        }
    }else
        if (k == 1){ 
        rCLUTs.chQ = 1;
        
        }
    rCLUTs.chIn_C = l;
    j = rCLUTs.chQ;
    rCLUTs.arrOut[Ts__2_1_OUT_NAME_CO-1] =  static_cast<bool>(j);
    //Additional Operation for Comm Req 
    pLN_TS->active_state[TS_OUT/8] =  static_cast<bool>(j) << (TS_OUT%8);
    
}
CLUTs::CLUTs(void) {
}

CLUTs::~CLUTs(void) {
}

CLUTs::CLUTs(char chM,char chI) {
register long i;
    chMaxIteratoin = chM;
    chIteration = chI;
    chNumInput  = static_cast<char> (TOTAL_Ts__2_1_IN);//TOTAL_Ts__2_1_IN
    chNumOutput = static_cast<char> (TOTAL_Ts__2_1_OUTPUT);//shCLUTs_x_y_AmtOut
    chTypeLogicFunction = LU_OP_NOT;
    LogicFunc = Ts__2_1_Op; //
    for (i = 0; i < chNumInput; i++)
        arrPchIn[i] = reinterpret_cast<char*> (0xcccccccc); //&chGblGround;
    for (i = 0; i < chNumOutput; i++)
        arrOut[i] = 0;
    //chError = 0; 
    chQ = chIn_C = 0;
    
}
void CLUTs::UpdateCLUTs(void){
//Set Input parameters
pIn = static_cast<void*>(arrPchIn);
//Set OutPut parameters
pOut = static_cast<void*>(arrOut);

}

