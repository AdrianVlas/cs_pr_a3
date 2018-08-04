/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "LUGoos.hpp"
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

CLUGoose::CLUGoose(void) {
}

CLUGoose::~CLUGoose(void) {
}
void CLUGoose::UpdateCLUGoose(void) {
    //Set Input parameters
    pIn = static_cast<void*> (arrPchIn);
    //Set OutPut parameters
    pOut = static_cast<void*> (arrOut);

}



CLUGoose::CLUGoose(char chM,char chI) {
register long i;
    chMaxIteratoin = chM;
    chIteration = chI;
    chNumInput  = static_cast<char> (TOTAL_Goose__1_8_IN);//TOTAL_Ts__2_1_IN
    chNumOutput = static_cast<char> (TOTAL_Goose__1_8_OUTPUT);//shCLUTs_x_y_AmtOut
    chTypeLogicFunction = LU_OP_NOT;
    LogicFunc = Goose__1_8_Op; //
    for (i = 0; i < chNumInput; i++)
        arrPchIn[i] = reinterpret_cast<char*> (0xcccccccc); //&chGblGround;
    for (i = 0; i < chNumOutput; i++)
        arrOut[i] = 0;
    //chError = 0;
    chIn_C = 0;

    
}
void Goose__1_8_Op  (void *pObj){
CLUGoose& rCLUGoose = *(static_cast<CLUGoose *> (pObj));
register    long  j, l,k;
__LN_INPUT_GOOSE_BLOCK *pMmsBlock = static_cast<__LN_INPUT_GOOSE_BLOCK *>(rCLUGoose.pvCfgLN);
    
    //        if(chGBL_BP_StopLUTs == rCLUTs.shShemasOrdNumStng)
    //    asm volatile(
    //    "bkpt 1"
    //    );
    j = *(rCLUGoose.arrPchIn[Goose__1_8_IN_NAME__BLOCK_G  - 1]);
    //l = rCLUGoose.arrPchIn[Goose__1_8_IN_NAME__BLOCK_G - 1];
    k = rCLUGoose.chIn_C;
    if( j == 0 ){
        
        l = pMmsBlock->internal_input_ctrl[(Goose__1_8_OUT_NAME__CO_1-1) / 8] & (1 << ((Goose__1_8_OUT_NAME__CO_1-1) % 8));
        
        if (l > 0) {
            j = pMmsBlock->internal_input[(Goose__1_8_OUT_NAME__CO_1-1) / 8] & (1 << ((Goose__1_8_OUT_NAME__CO_1-1) % 8));
            if (j > 0){
                //rCLUGoose.arrOut[0] = 1;
                k |= 1 << ((Goose__1_8_OUT_NAME__CO_1-1) % 8); l = 1;
            }
            else{
            //rCLUGoose.arrOut[0] = 0;
                k &=~( 1 << ((Goose__1_8_OUT_NAME__CO_1-1) % 8));l = 0;
            }
           
        }
        else{
           if(k & (1 << ((Goose__1_8_OUT_NAME__CO_1-1) % 8)) ) 
                l = 1;
        }
        rCLUGoose.arrOut[(Goose__1_8_OUT_NAME__CO_1-1)] = l;//k & (1 << ((Goose__1_8_OUT_NAME__CO_1-1) % 8));
        
        
        
        
        l = pMmsBlock->internal_input_ctrl[(Goose__1_8_OUT_NAME__CO_2-1) / 8] & (1 << ((Goose__1_8_OUT_NAME__CO_2-1) % 8));
        
        if (l > 0) {
            j = pMmsBlock->internal_input[(Goose__1_8_OUT_NAME__CO_2-1) / 8] & (1 << ((Goose__1_8_OUT_NAME__CO_2-1) % 8));
            if (j > 0){
                //rCLUGoose.arrOut[(Goose__1_8_OUT_NAME__CO_2-1)] = 1;
                 k |= 1 << ((Goose__1_8_OUT_NAME__CO_2-1) % 8); l = 1;
            }
            else{
                k &=~( 1 << ((Goose__1_8_OUT_NAME__CO_2-1) % 8)); l = 0;
                }
        } else{
           if(k & (1 << ((Goose__1_8_OUT_NAME__CO_2-1) % 8)) ) 
                l = 1;
        }
        rCLUGoose.arrOut[(Goose__1_8_OUT_NAME__CO_2-1)] =  l;//k & (1 << ((Goose__1_8_OUT_NAME__CO_2-1) % 8));  
      
        l = pMmsBlock->internal_input_ctrl[(Goose__1_8_OUT_NAME__CO_3-1) / 8] & (1 << ((Goose__1_8_OUT_NAME__CO_3-1) % 8));
        
        if (l > 0) {
            j = pMmsBlock->internal_input[(Goose__1_8_OUT_NAME__CO_3-1) / 8] & (1 << ((Goose__1_8_OUT_NAME__CO_3-1) % 8));
            if (j > 0){
                //rCLUGoose.arrOut[(Goose__1_8_OUT_NAME__CO_3-1)] = 1;
                 k |= 1 << ((Goose__1_8_OUT_NAME__CO_3-1) % 8);l = 1;
            }
            else{
            //rCLUGoose.arrOut[0] = 0;
                k &=~( 1 << ((Goose__1_8_OUT_NAME__CO_3-1) % 8)); l = 0;
            }
            
        }else{
           if(k & (1 << ((Goose__1_8_OUT_NAME__CO_3-1) % 8)) ) 
                l = 1;
        }
        rCLUGoose.arrOut[(Goose__1_8_OUT_NAME__CO_3-1)] = l;
        l = pMmsBlock->internal_input_ctrl[(Goose__1_8_OUT_NAME__CO_4-1) / 8] & (1 << ((Goose__1_8_OUT_NAME__CO_4-1) % 8));
        
        if (l > 0) {
            j = pMmsBlock->internal_input[(Goose__1_8_OUT_NAME__CO_4-1) / 8] & (1 << ((Goose__1_8_OUT_NAME__CO_4-1) % 8));
            if (j > 0){
                //rCLUGoose.arrOut[(Goose__1_8_OUT_NAME__CO_4-1)] = 1;
                 k |= 1 << ((Goose__1_8_OUT_NAME__CO_4-1) % 8); l = 1;
            } 
            else{
            //rCLUGoose.arrOut[0] = 0;
                k &=~( 1 << ((Goose__1_8_OUT_NAME__CO_4-1) % 8));l = 0;
            }
        } else{
           if(k & (1 << ((Goose__1_8_OUT_NAME__CO_4-1) % 8)) ) 
                l = 1;
        }
        rCLUGoose.arrOut[(Goose__1_8_OUT_NAME__CO_4-1)] = l;        
        l = pMmsBlock->internal_input_ctrl[(Goose__1_8_OUT_NAME__CO_5-1) / 8] & (1 << ((Goose__1_8_OUT_NAME__CO_5-1) % 8));
        
        if (l > 0) {
            j = pMmsBlock->internal_input[(Goose__1_8_OUT_NAME__CO_5-1) / 8] & (1 << ((Goose__1_8_OUT_NAME__CO_5-1) % 8));
            if (j > 0){
                //rCLUGoose.arrOut[(Goose__1_8_OUT_NAME__CO_5-1)] = 1;
                 k |= 1 << ((Goose__1_8_OUT_NAME__CO_5-1) % 8); l = 1;
            }
            else{
            //rCLUGoose.arrOut[0] = 0;
                k &=~( 1 << ((Goose__1_8_OUT_NAME__CO_5-1) % 8));l = 0;
            }
            
        } else{
           if(k & (1 << ((Goose__1_8_OUT_NAME__CO_5-1) % 8)) ) 
                l = 1;
        }
        rCLUGoose.arrOut[(Goose__1_8_OUT_NAME__CO_5-1)] = l;
        l = pMmsBlock->internal_input_ctrl[(Goose__1_8_OUT_NAME__CO_6-1) / 8] & (1 << ((Goose__1_8_OUT_NAME__CO_6-1) % 8));
        
        if (l > 0) {
            j = pMmsBlock->internal_input[(Goose__1_8_OUT_NAME__CO_6-1) / 8] & (1 << ((Goose__1_8_OUT_NAME__CO_6-1) % 8));
            if (j > 0){
                //rCLUGoose.arrOut[(Goose__1_8_OUT_NAME__CO_6-1)] = 1;
                 k |= 1 << ((Goose__1_8_OUT_NAME__CO_6-1) % 8); l = 1;
            }else{
            //rCLUGoose.arrOut[0] = 0;
                k &=~( 1 << ((Goose__1_8_OUT_NAME__CO_6-1) % 8));l = 0;
            }     
        } else{
           if(k & (1 << ((Goose__1_8_OUT_NAME__CO_6-1) % 8)) ) 
                l = 1;
        }
        rCLUGoose.arrOut[(Goose__1_8_OUT_NAME__CO_6-1)] = l;        
        l = pMmsBlock->internal_input_ctrl[(Goose__1_8_OUT_NAME__CO_7-1) / 8] & (1 << ((Goose__1_8_OUT_NAME__CO_7-1) % 8));
        
        if (l > 0) {
            j = pMmsBlock->internal_input[(Goose__1_8_OUT_NAME__CO_7-1) / 8] & (1 << ((Goose__1_8_OUT_NAME__CO_7-1) % 8));
            if (j > 0){
               // rCLUGoose.arrOut[(Goose__1_8_OUT_NAME__CO_7-1)] = 1;
                 k |= 1 << ((Goose__1_8_OUT_NAME__CO_7-1) % 8); l = 1;
            }else{
            //rCLUGoose.arrOut[0] = 0;
                k &=~( 1 << ((Goose__1_8_OUT_NAME__CO_7-1) % 8));l = 0;
            }
        }        else{
           if(k & (1 << ((Goose__1_8_OUT_NAME__CO_7-1) % 8)) ) 
                l = 1;
        }
        
        rCLUGoose.arrOut[(Goose__1_8_OUT_NAME__CO_7-1)] = l;
        l = pMmsBlock->internal_input_ctrl[(Goose__1_8_OUT_NAME__CO_8-1) / 8] & (1 << ((Goose__1_8_OUT_NAME__CO_8-1) % 8));
        
        if (l > 0) {
            j = pMmsBlock->internal_input[(Goose__1_8_OUT_NAME__CO_8-1) / 8] & (1 << ((Goose__1_8_OUT_NAME__CO_8-1) % 8));
            if (j > 0){
                //rCLUGoose.arrOut[(Goose__1_8_OUT_NAME__CO_8-1)] = 1;
                 k |= 1 << ((Goose__1_8_OUT_NAME__CO_8-1) % 8);l = 1;
            }else{
            //rCLUGoose.arrOut[0] = 0;
                k &=~( 1 << ((Goose__1_8_OUT_NAME__CO_1-1) % 8));l = 0;
            }            
        } else{
           if(k & (1 << ((Goose__1_8_OUT_NAME__CO_8-1) % 8)) ) 
                l = 1;
        }
        rCLUGoose.arrOut[(Goose__1_8_OUT_NAME__CO_8-1)] = l;
       
    rCLUGoose.chIn_C = k;
    pMmsBlock->active_state[((Goose__1_8_OUT_NAME__CO_8-1) / 8)] = k;
    }
    else{
        
        rCLUGoose.arrOut[0] = 0;
        rCLUGoose.arrOut[1] = 0;
        rCLUGoose.arrOut[2] = 0;
        rCLUGoose.arrOut[3] = 0;
        rCLUGoose.arrOut[4] = 0;
        rCLUGoose.arrOut[5] = 0;
        rCLUGoose.arrOut[6] = 0;
        rCLUGoose.arrOut[7] = 0;
        pMmsBlock->active_state[((Goose__1_8_OUT_NAME__CO_8-1) / 8)] = 0;
    }
    
}
