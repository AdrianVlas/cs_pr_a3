/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "LULan.hpp"
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




char chGBL_BP_StopLULan = 0;

void Lan__9_8_Op(void *pObj) {
    CLULan &rCLULan = *(static_cast<CLULan *> (pObj));
    long k, j, l; //


    //        if(chGBL_BP_StopLUTs == rCLUTs.shShemasOrdNumStng)
    //    asm volatile(
    //    "bkpt 1"
    //    );
   
//    __LN_TS* pLN_TS = static_cast<__LN_TS *> (rCLUTs.pvCfgLN);
//        j = *(rCLUTs.arrPchIn[Ts__2_1_IN_NAME__CI - 1]);
//    l = *(rCLUTs.arrPchIn[Ts__2_1_IN_NAME__BLOCK - 1]);
    
    __LN_NETWORK_OUTPUT_BLOCK* pN =  static_cast<__LN_NETWORK_OUTPUT_BLOCK *>(rCLULan.pvCfgLN);
    
    l = *(rCLULan.arrPchIn[(Lan__9_8_IN_NAME__BLOCK_L-1)]);

    if (l != 0) {
        rCLULan.arrOut[0] = 0;
        rCLULan.arrOut[1] = 0;
        rCLULan.arrOut[2] = 0;
        rCLULan.arrOut[3] = 0;
        rCLULan.arrOut[4] = 0;
        rCLULan.arrOut[5] = 0;
        rCLULan.arrOut[6] = 0;
        rCLULan.arrOut[7] = 0;
        pN->active_state[0] = 0;

    } else {
        k = 0;
        rCLULan.arrOut[0] = j = *(rCLULan.arrPchIn[0]);
        k |= static_cast<bool>(j) << 0;
        rCLULan.arrOut[1] = j = *(rCLULan.arrPchIn[1]);
        k |= static_cast<bool>(j) << 1;
        rCLULan.arrOut[2] = j = *(rCLULan.arrPchIn[2]);
        k |= static_cast<bool>(j) << 2;
        rCLULan.arrOut[3] = j = *(rCLULan.arrPchIn[3]);
        k |= static_cast<bool>(j) << 3;
        rCLULan.arrOut[4] = j = *(rCLULan.arrPchIn[4]);
        k |= static_cast<bool>(j) << 4;
        rCLULan.arrOut[5] = j = *(rCLULan.arrPchIn[5]);
        k |= static_cast<bool>(j) << 5;
        rCLULan.arrOut[6] = j = *(rCLULan.arrPchIn[6]);
        k |= static_cast<bool>(j) << 6;
        rCLULan.arrOut[7] = j = *(rCLULan.arrPchIn[7]);
        k |= static_cast<bool>(j) << 7;
        pN->active_state[0] = k;
    }

    

    
}

CLULan::CLULan(void) {
}

CLULan::~CLULan(void) {
}

CLULan::CLULan(char chM,char chI) {

    register long i;
    
    chMaxIteratoin = chM;
    chIteration = chI;
    chNumInput = static_cast<char> (TOTAL_Lan__9_8_IN); //TOTAL_Ts__2_1_IN
    chNumOutput = static_cast<char> (TOTAL_Lan__9_8_OUTPUT); //shCLUTs_x_y_AmtOut
    chTypeLogicFunction = LU_OP_NOT;
    LogicFunc = Lan__9_8_Op; //
    for (i = 0; i < chNumInput; i++)
        arrPchIn[i] = reinterpret_cast<char*> (0xcccccccc); //&chGblGround;
    for (i = 0; i < chNumOutput; i++)
        arrOut[i] = 0;
    //chError = 0; 
    //chQ = chIn_C = 0;
}

void CLULan::UpdateCLULan(void) {
    //Set Input parameters
    pIn = static_cast<void*> (arrPchIn);
    //Set OutPut parameters
    pOut = static_cast<void*> (arrOut);

}





