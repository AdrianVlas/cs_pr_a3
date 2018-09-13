/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "LUMms.hpp"
#include "../inc/constants.h"

#include <stdbool.h>
#include <math.h>
//#include <arm_math.h>//ID n OUT
#include <stdlib.h>
#include <string.h>
#include "stm32f2xx.h"
#include "hw_config.h"
#include "../inc/macroses.h"
#include "../inc/type_definition.h"
#include "../inc/variables_external.h"//

CLUMms::CLUMms(void) {
}

CLUMms::~CLUMms(void) {
}
//char chGBL_BP_StopLUMms = 0;
CLUMms::CLUMms(char chM,char chI) {
register long i;
    chMaxIteratoin = chM;
    chIteration = chI;
    chNumInput  = static_cast<char> (TOTAL_Mms__2_8_IN);//TOTAL_Ts__2_1_IN
    chNumOutput = static_cast<char> (TOTAL_Mms__2_8_OUTPUT);//shCLUTs_x_y_AmtOut
    chTypeLogicFunction = LU_OP_NOT;
    LogicFunc = Mms__2_8_Op; //
    for (i = 0; i < chNumInput; i++)
        arrPchIn[i] = reinterpret_cast<char*> (0xcccccccc); //&chGblGround;
    for (i = 0; i < chNumOutput; i++)
        arrOut[i] = 0;
    //chError = 0; 

    
}
void  Mms__2_8_Op  (void *pObj){
CLUMms& rCLUMms = *(static_cast<CLUMms *> (pObj));
    long  j, l,k;

     __LN_INPUT_MMS_BLOCK *pMmsBlock = static_cast<__LN_INPUT_MMS_BLOCK *>(rCLUMms.pvCfgLN);
//            if(chGBL_BP_StopLUMms == rCLUTs.shShemasOrdNumStng)
//        asm volatile(
//        "bkpt 1"
//        );
    j = *(rCLUMms.arrPchIn[Mms__2_8_IN_NAME__BLOCK_M  - 1]);
    l = *(rCLUMms.arrPchIn[Mms__2_8_IN_NAME__BLOCK_LR - 1]);
    k = 0;
    if( j == 0 && l == 0){
       
        l = pMmsBlock->internal_input_ctrl[(Mms__2_8_OUT_NAME__CO_1-1) / 8] & (1 << ((Mms__2_8_OUT_NAME__CO_1-1) % 8));
        rCLUMms.arrOut[(Mms__2_8_OUT_NAME__CO_1-1)] = 0;
        if (l > 0) {
            j = pMmsBlock->internal_input[(Mms__2_8_OUT_NAME__CO_1-1) / 8] & (1 << ((Mms__2_8_OUT_NAME__CO_1-1) % 8));
            if (j > 0)
                rCLUMms.arrOut[0] = 1;
                k |= 1 << ((Mms__2_8_OUT_NAME__CO_1-1) % 8);
        } 
        l = pMmsBlock->internal_input_ctrl[(Mms__2_8_OUT_NAME__CO_2-1) / 8] & (1 << ((Mms__2_8_OUT_NAME__CO_2-1) % 8));
        rCLUMms.arrOut[(Mms__2_8_OUT_NAME__CO_2-1)] = 0;
        if (l > 0) {
            j = pMmsBlock->internal_input[(Mms__2_8_OUT_NAME__CO_2-1) / 8] & (1 << ((Mms__2_8_OUT_NAME__CO_2-1) % 8));
            if (j > 0)
                rCLUMms.arrOut[(Mms__2_8_OUT_NAME__CO_2-1)] = 1;
                 k |= 1 << ((Mms__2_8_OUT_NAME__CO_2-1) % 8);
        } 
        l = pMmsBlock->internal_input_ctrl[(Mms__2_8_OUT_NAME__CO_3-1) / 8] & (1 << ((Mms__2_8_OUT_NAME__CO_3-1) % 8));
        rCLUMms.arrOut[(Mms__2_8_OUT_NAME__CO_3-1)] = 0;
        if (l > 0) {
            j = pMmsBlock->internal_input[(Mms__2_8_OUT_NAME__CO_3-1) / 8] & (1 << ((Mms__2_8_OUT_NAME__CO_3-1) % 8));
            if (j > 0)
                rCLUMms.arrOut[(Mms__2_8_OUT_NAME__CO_3-1)] = 1;
                 k |= 1 << ((Mms__2_8_OUT_NAME__CO_3-1) % 8);
        }
        l = pMmsBlock->internal_input_ctrl[(Mms__2_8_OUT_NAME__CO_4-1) / 8] & (1 << ((Mms__2_8_OUT_NAME__CO_4-1) % 8));
        rCLUMms.arrOut[(Mms__2_8_OUT_NAME__CO_4-1)] = 0;
        if (l > 0) {
            j = pMmsBlock->internal_input[(Mms__2_8_OUT_NAME__CO_4-1) / 8] & (1 << ((Mms__2_8_OUT_NAME__CO_4-1) % 8));
            if (j > 0)
                rCLUMms.arrOut[(Mms__2_8_OUT_NAME__CO_4-1)] = 1;
                 k |= 1 << ((Mms__2_8_OUT_NAME__CO_4-1) % 8);
        } 
        l = pMmsBlock->internal_input_ctrl[(Mms__2_8_OUT_NAME__CO_5-1) / 8] & (1 << ((Mms__2_8_OUT_NAME__CO_5-1) % 8));
        rCLUMms.arrOut[(Mms__2_8_OUT_NAME__CO_5-1)] = 0;
        if (l > 0) {
            j = pMmsBlock->internal_input[(Mms__2_8_OUT_NAME__CO_5-1) / 8] & (1 << ((Mms__2_8_OUT_NAME__CO_5-1) % 8));
            if (j > 0)
                rCLUMms.arrOut[(Mms__2_8_OUT_NAME__CO_5-1)] = 1;
                 k |= 1 << ((Mms__2_8_OUT_NAME__CO_5-1) % 8);
        }
        l = pMmsBlock->internal_input_ctrl[(Mms__2_8_OUT_NAME__CO_6-1) / 8] & (1 << ((Mms__2_8_OUT_NAME__CO_6-1) % 8));
        rCLUMms.arrOut[(Mms__2_8_OUT_NAME__CO_6-1)] = 0;
        if (l > 0) {
            j = pMmsBlock->internal_input[(Mms__2_8_OUT_NAME__CO_6-1) / 8] & (1 << ((Mms__2_8_OUT_NAME__CO_6-1) % 8));
            if (j > 0)
                rCLUMms.arrOut[(Mms__2_8_OUT_NAME__CO_6-1)] = 1;
                 k |= 1 << ((Mms__2_8_OUT_NAME__CO_6-1) % 8);
        } 
        l = pMmsBlock->internal_input_ctrl[(Mms__2_8_OUT_NAME__CO_7-1) / 8] & (1 << ((Mms__2_8_OUT_NAME__CO_7-1) % 8));
        rCLUMms.arrOut[(Mms__2_8_OUT_NAME__CO_7-1)] = 0;
        if (l > 0) {
            j = pMmsBlock->internal_input[(Mms__2_8_OUT_NAME__CO_7-1) / 8] & (1 << ((Mms__2_8_OUT_NAME__CO_7-1) % 8));
            if (j > 0)
                rCLUMms.arrOut[(Mms__2_8_OUT_NAME__CO_7-1)] = 1;
                 k |= 1 << ((Mms__2_8_OUT_NAME__CO_7-1) % 8);
        } 
        l = pMmsBlock->internal_input_ctrl[(Mms__2_8_OUT_NAME__CO_8-1) / 8] & (1 << ((Mms__2_8_OUT_NAME__CO_8-1) % 8));
        rCLUMms.arrOut[(Mms__2_8_OUT_NAME__CO_8-1)] = 0;
        if (l > 0) {
            j = pMmsBlock->internal_input[(Mms__2_8_OUT_NAME__CO_8-1) / 8] & (1 << ((Mms__2_8_OUT_NAME__CO_8-1) % 8));
            if (j > 0)
                rCLUMms.arrOut[(Mms__2_8_OUT_NAME__CO_8-1)] = 1;
                 k |= 1 << ((Mms__2_8_OUT_NAME__CO_8-1) % 8);
        } 
//        if(chGBL_BP_StopLUMms == rCLUMms.shShemasOrdNumStng && k != 0)
//        asm volatile(
//        "bkpt 1"
//        );
        pMmsBlock->active_state[((Mms__2_8_OUT_NAME__CO_8-1) / 8)] = k;
    }
    else{
        pMmsBlock->active_state[((Mms__2_8_OUT_NAME__CO_8-1) / 8)] = 0;
        rCLUMms.arrOut[0] = 0;
        rCLUMms.arrOut[1] = 0;
        rCLUMms.arrOut[2] = 0;
        rCLUMms.arrOut[3] = 0;
        rCLUMms.arrOut[4] = 0;
        rCLUMms.arrOut[5] = 0;
        rCLUMms.arrOut[6] = 0;
        rCLUMms.arrOut[7] = 0;
    }
    
}
