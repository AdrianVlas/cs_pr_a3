#ifdef VISUAL_STUDIO
#include "StdAfx.h"
#endif
#include "LULed.h"
//#include "libraries.h"
#include <string.h>
#include "stm32f2xx.h"
#include "stm32f2xx_it.h"
#include "Ereg.h"
#include "prtTmr.h"

/*
void PUT_Op_1_0_    (void *pObj)
{
//CLUNot_1_1& refCLUNot_1_1 = pObj;
//CLULed *pCLULed = (CLULed*)pObj;

}
*/
CLULed::CLULed(void){
    
}
//typedef long(*fnPvrL)(void *pv);
CLULed::CLULed(char chM,char chI){

    memset(static_cast<void*> (arrPchIn),    0xcc, sizeof (char*)*TOTAL_LED_VISIO_IN);
    memset(static_cast<void*> (arrPchSchIn), 0xcc, sizeof (char*)*shCLULed_1_0_AmtIn);
//    memset(static_cast<void*> (arrPchAlternator), 0xcc, sizeof (char*)*2);
    memset(static_cast<void*> (arrOut),        0, sizeof (char)*TOTAL_LED_VISIO_OUTPUT);
    memset(static_cast<void*> (&m_LedCfgSuit), 0, sizeof (LedCfgSuit));

    chMaxIteratoin = chM;
    chIteration = chI;
    chNumInput = static_cast<char> (TOTAL_LED_VISIO_IN);//shCLULed_1_0_AmtIn
    chNumOutput = static_cast<char> (TOTAL_LED_VISIO_OUTPUT);//shCLULed_1_0_AmtOut
    
    

    //Set Input parameters
    //pIn = (void*)arrPchIn;
    //pOut = (void*)arrOut;
    //Set OutPut parameters
/*
char* arrPchIn[shCLULed_1_0_AmtIn];//
    char* arrPchSchIn[TOTAL_LED_VISIO_IN];//
    char* arrPchAlternator[2];//
    char  arrOut  [TOTAL_LED_VISIO_OUTPUT];//Trash field
    LedCfgSuit m_LedCfgSuit;
*/
}

CLULed::~CLULed(void){
    
}
//void ChangeLedCfgSuit(void *pObj){
//
//}

char chGLBIn1_5 = 0;
char chGLBIn6_12 = 0;
long lGLBInChek_6_12 = 0;
long lGLBInChek_8_72 = 0;

void SET_LED_Op(void *pObj) {
CLULed& rCLULed = *(static_cast<CLULed*> (pObj));
/*
    register long i;
    bool bbState;
    CLULed& rCLULed = *(static_cast<CLULed*> (pObj));

    struct {
        short*pLASh;
        long L_Vl;
        char chVal;
        short shVal;
    } sLV;
    */
    if (chGLBIn1_5) {
        asm(
        "bkpt 1"
        );
        /*
         *    i = rCLULed.shShemasOrdNumStng;
    i--;
    bbState = false;
    bbState = rCLULed.arrOut[0];
    if (bbState) {
        LedStateUI32Bit.ul_val |=   (1) << i;
    } else {
        LedStateUI32Bit.ul_val &= ~((1) << i);
    } 
         */
}  
    
rCLULed.CalcLedSchematic();

//LedStateUI32Bit.ul_val =  ((long)bbState)<< i;

return;

}

#include "LULedp1.cpp"
static char chGLB_QTrg = 0;static char chGLB_InC = 0;
void CLULed::CalcLedSchematic(void){
register long rl_Val,i;

#pragma data_alignment=4
char arChIntermediaResult[(TOTAL_LU_CALC_POINT)];
const LedShcemasDscRecord* pLUShcemasDscRec;// = &arPLedShcemasDscRecords;

arChIntermediaResult[OFFSET_OUT_IN_MNU_NORMAL_SELECTOR        ] = 0;//Now Default
arChIntermediaResult[OFFSET_OUT_IN_MNU_TRIGGER_SELECTOR       ] = 0;//Now Default
arChIntermediaResult[OFFSET_OUT_IN_MNU_STABLE_SELECTOR        ] = 0;//Now Default
arChIntermediaResult[OFFSET_OUT_IN_MNU_PULSE_SELECTOR         ] = 0;//Now Default
arChIntermediaResult[OFFSET_OUT_IN_MNU_PULSE_SIMPLE_SELECTOR  ] = 0;//Now Default
arChIntermediaResult[OFFSET_OUT_IN_MNU_PULSE_EXTANDED_SELECTOR] = 0;//Now Default

char *pCh = (this->arrPchIn[(LED_IN_NAME__LEDIN - 1)]);
arChIntermediaResult[OFFSET_OUT_IN_00_LEDIN                   ] = pCh[0];//Now Default
pCh = (this->arrPchIn[(LED_IN_NAME__RESET - 1)]);
arChIntermediaResult[OFFSET_OUT_IN_01_RESET                   ] = pCh[0];//Now Default
pCh = (this->arrPchIn[(LED_IN_NAME__BL_IMP - 1)]);
arChIntermediaResult[OFFSET_OUT_IN_02_BL_IMP                  ] = pCh[0];//Now Default
pCh = (this->arrPchIn[(LED_IN_NAME__C1_C2 - 1)]);
arChIntermediaResult[OFFSET_OUT_IN_03_C1_C2_SELECTOR          ] = pCh[0];//Now Default

arChIntermediaResult[OFFSET_OUT_IN_04_C1                      ] = 0;//Now Default
arChIntermediaResult[OFFSET_OUT_IN_05_C2                      ] = 0;//Now Default
if(pCh[0] == 0){
//C1
pCh = (this->arrPchIn[(LED_IN_NAME__C1 - 1)]);
arChIntermediaResult[OFFSET_OUT_IN_04_C1] = pCh[0];

}
else{
//C2
pCh = (this->arrPchIn[(LED_IN_NAME__C2 - 1)]);
arChIntermediaResult[OFFSET_OUT_IN_05_C2] = pCh[0];
}


if(this->m_LedCfgSuit.chSel1 == 0){
arChIntermediaResult[OFFSET_OUT_IN_MNU_NORMAL_SELECTOR] = 1;
}
else{
arChIntermediaResult[OFFSET_OUT_IN_MNU_TRIGGER_SELECTOR] = 1;
}
if(this->m_LedCfgSuit.chSel2 == 0){
arChIntermediaResult[OFFSET_OUT_IN_MNU_STABLE_SELECTOR] = 1;
}
else{
arChIntermediaResult[OFFSET_OUT_IN_MNU_PULSE_SELECTOR] = 1;
}
if(this->m_LedCfgSuit.chSel3 == 0){
arChIntermediaResult[OFFSET_OUT_IN_MNU_PULSE_SIMPLE_SELECTOR] = 1;
}
else{
arChIntermediaResult[OFFSET_OUT_IN_MNU_PULSE_EXTANDED_SELECTOR] = 1;
}




for (i = OFFSET_OUT_Not06__1_1; i < OFFSET_OUT_And23__2_1; i++)//OFFSET_OUT_Or_22__3_1
    arChIntermediaResult[i] = 0xcc;
    rl_Val = 0;
    long k, j, l;
    short shCounterProcessedRec = Not06__1_1;

    do {
pLUShcemasDscRec = arPLedShcemasDscRecords[shCounterProcessedRec - Not06__1_1];
        i = pLUShcemasDscRec->chTypeOperation;
        switch (i) {
            case LU_GEN_OP_AND:
                rl_Val = 1;
                for (i = 0; (i < pLUShcemasDscRec->chAmtIn)&&(rl_Val == 1); i++) {
                    k = pLUShcemasDscRec->pInputDscData[i].shOrderNumLU;
                    l = arShOffsets[k];
                    j = l + pLUShcemasDscRec->pInputDscData[i].shIndexOut;
                    rl_Val &= arChIntermediaResult[j];
                }
                k = pLUShcemasDscRec->chOrderNumLU;
                i = arShOffsets[k];//shCounterProcessedRec must be LED_SCHEMATIC_LU_ORDER_NUMS
                arChIntermediaResult[i] = rl_Val;
                shCounterProcessedRec++;
                break;
            case LU_GEN_OP_OR:
                rl_Val = 0;
                for (i = 0; (i < pLUShcemasDscRec->chAmtIn)&&( rl_Val == 0); i++) {
                    k = pLUShcemasDscRec->pInputDscData[i].shOrderNumLU;
                    l = arShOffsets[k];
                    j = l + pLUShcemasDscRec->pInputDscData[i].shIndexOut;
                    rl_Val |= arChIntermediaResult[j];
                }
                k = pLUShcemasDscRec->chOrderNumLU;
                i = arShOffsets[k];
                arChIntermediaResult[i] = rl_Val;
                shCounterProcessedRec++;
                break;
            case LU_GEN_OP_XOR:
                i = pLUShcemasDscRec->pInputDscData[0].shOrderNumLU;
                rl_Val = arShOffsets[i];
                i = rl_Val + pLUShcemasDscRec->pInputDscData[0].shIndexOut;
                j = arChIntermediaResult[i];
                i = pLUShcemasDscRec->pInputDscData[1].shOrderNumLU;
                rl_Val = arShOffsets[i];
                i = rl_Val + pLUShcemasDscRec->pInputDscData[1].shIndexOut;
                rl_Val = j^arChIntermediaResult[i];
                k = pLUShcemasDscRec->chOrderNumLU;
                i = arShOffsets[k];
                arChIntermediaResult[i] = rl_Val;
                shCounterProcessedRec++;
                break;
            case LU_GEN_OP_NOT:
                LUShcemasInDataDsc const *pLUShcemasInDataDsc;
                rl_Val = 0;
                pLUShcemasInDataDsc = pLUShcemasDscRec->pInputDscData;
                i = pLUShcemasInDataDsc[0].shOrderNumLU;
                rl_Val = arShOffsets[i];
                i = rl_Val + pLUShcemasInDataDsc[0].shIndexOut;
                rl_Val = arChIntermediaResult[i];
                k = pLUShcemasDscRec->chOrderNumLU;
                i = arShOffsets[k];
                arChIntermediaResult[i] = !rl_Val;
                shCounterProcessedRec++;
                break;
            case LU_GEN_OP_RS_TRIGGER:
                long lIdxInC;
                k = pLUShcemasDscRec->pInputDscData[0].shOrderNumLU;
                l = arShOffsets[k];
                lIdxInC = l + pLUShcemasDscRec->pInputDscData[0].shIndexOut;
                
                rl_Val = chGLB_QTrg;
                k = pLUShcemasDscRec->pInputDscData[1].shOrderNumLU;
                l = arShOffsets[k];
                j = l + pLUShcemasDscRec->pInputDscData[1].shIndexOut; //

                l = arShOffsets[IN_MNU_NORMAL_SELECTOR];
                if (arChIntermediaResult[j] || arChIntermediaResult[l]) {
                    chGLB_QTrg = rl_Val = 0; //Clr
                } else {
                    //k = pLUShcemasDscRec->pInputDscData[0].shOrderNumLU;
                    //l = arShOffsets[k];
                    //j = l + pLUShcemasDscRec->pInputDscData[0].shIndexOut;
                    if ((chGLB_InC == 0) && (arChIntermediaResult[lIdxInC] > 0))
                        chGLB_QTrg = rl_Val = 1;
                }
                //Work on change from 0 to 1
                //rl_Val = chGLB_QTrg;
                k = pLUShcemasDscRec->chOrderNumLU;
                i = arShOffsets[k];
                arChIntermediaResult[i] = rl_Val;
                arChIntermediaResult[i+1] = !rl_Val;
                chGLB_InC = arChIntermediaResult[lIdxInC];
                shCounterProcessedRec++;
                break;
                //Read Input Data

                //Eval Function
                //Put Result
                
            default:
                shCounterProcessedRec++;
                asm(
                    "bkpt 1"
                    );
        }
  
    } while (shCounterProcessedRec < And23__2_1);//IN_MNU_NORMAL_SELECTOR
    
    this->arrOut[(LED_OUT_NAME__LED_STATE_OUTPUT-1)] = arChIntermediaResult[OFFSET_OUT_Or_11__2_1];
    bool bbState = false;
    bbState = arChIntermediaResult[OFFSET_OUT_Or_22__3_1                   ]; //rCLULed.arrOut[0];
    char *pCh1,*pCh2;
    pCh1 = (this->arrPchIn[(LED_IN_NAME__TEST_M - 1)]);
    arChIntermediaResult[OFFSET_OUT_And23__2_1] = bbState
    && (!(*pCh1));
    
    pCh2 = this->arrPchIn[(LED_IN_NAME__TLEDIN - 1)];
    arChIntermediaResult[OFFSET_OUT_And24__2_1] = *pCh1 && *pCh2;

    bbState = arChIntermediaResult[OFFSET_OUT_And24__2_1] || arChIntermediaResult[OFFSET_OUT_And23__2_1];
    i = this->shShemasOrdNumStng;
    i--;
 /*   if (bbState) {
        LedStateUI32Bit.ul_val |= (1) << i;
    } else {
        LedStateUI32Bit.ul_val &= ~((1) << i); //Phis write to Led
    }*/
}

