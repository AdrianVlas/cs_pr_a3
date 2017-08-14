
#include "LUTu.h"
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

CLUTu::CLUTu(void) {
}

CLUTu::~CLUTu(void) {
}
CLUTu::CLUTu(char chM,char chI) {
	chMaxIteratoin = chM;
	chIteration = chI;
    chNumOutput = static_cast<char>(shCLUTU_x_y_AmtOut);
	for (long i = 0; i < chNumOutput; i++)
        arrOut[i] = 0;
}
void TU_Op(void *pObj){
long i,j;

	CLUTu *pCLUTu = static_cast<CLUTu*>(pObj);
    __LN_TU *pLN_TU = static_cast<__LN_TU *>(pCLUTu->pvCfgLN);
    i = pLN_TU->active_state[0];
//find Index
// i = pCLUTu->shShemasOrdNumStng;
    // i--;
    //Look State
    j = *(pCLUTu->arrPchIn[TU__1_1_IN_NAME__BLOCK-1]); 
    pCLUTu->arrOut[TU__1_1_OUT_NAME_CO-1] = i && (!j);
    
}
void CLUTu::UpdateCLUTu(void){
//Set Input parameters
pIn = static_cast<void*>(arrPchIn);
//Set OutPut parameters
pOut = static_cast<void*>(arrOut);

}




