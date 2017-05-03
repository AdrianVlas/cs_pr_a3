#ifdef VISUAL_STUDIO
#include "StdAfx.h"
#endif
#include "LUDout_1_0.h"
#include <string.h>
#include "stm32f2xx.h"
#include "stm32f2xx_it.h"
#include "Ereg.h"
#include "prtTmr.h"

void PUT_Op_1_0(void *pObj) {
    CLUDout_1_0& refCLUDout_1_0 = *(static_cast<CLUDout_1_0*> (pObj));
    //CLUDout_1_0 *pCLUDout_1_0 = (CLUDout_1_0*)pObj;
    refCLUDout_1_0.CalcReleySchematic();
}

CLUDout_1_0::CLUDout_1_0(void) {
    
}
CLUDout_1_0::CLUDout_1_0(char chM,char chI)//,LUOutDsc* pLUOutDsc)
{
 //-void *memset(void *s, int c, size_t n);
    memset(static_cast<void*>(arrPchIn),0xcc,sizeof(char*)*TOTAL_RELE_VISIO_IN);
    memset(static_cast<void*>(arrPchSchIn),0xcc,sizeof(char*)*shCLUDout_1_0_AmtIn);
    //memset(static_cast<void*>(arrPchAlternator),0xcc,sizeof(char*)*2);
    memset(static_cast<void*>(arrOut),0,sizeof(char)*TOTAL_RELE_VISIO_OUTPUT);
    memset(static_cast<void*>(&m_ReleyCfgSuit),0,sizeof(ReleyCfgSuit));
    
    
    chMaxIteratoin = chM;
    chIteration = chI;
    chNumInput  = static_cast<char>(TOTAL_RELE_VISIO_IN );
    chNumOutput = static_cast<char>(TOTAL_RELE_VISIO_OUTPUT);
    //chTypeLogicFunction = LU_OP_SET_OUT;
    //LogicFunc  = SET_OUT_Op;//???

    //Set Input parameters
    //pIn = (void*)arrPchIn;
    //pOut = (void*)arrOut;
    //Set OutPut parameters
    //char* arrPchIn[shCLUDout_1_0_AmtIn]; //
    //char* arrPchSchIn[TOTAL_RELE_VISIO_IN];//
    //char* arrPchAlternator[2];//
    //char  arrOut  [TOTAL_RELE_VISIO_OUTPUT];//Trash field
    //ReleyCfgSuit m_ReleyCfgSuit;

}

CLUDout_1_0::~CLUDout_1_0(void) {
    
}
char chGBLBPStopSetOut = 0;
void SET_OUT_Op(void *pObj) {
    //CLUDout_1_0 *pCLUDout_1_0 = reinterpret_cast<CLUDout_1_0 *>(pObj);
    CLUDout_1_0& rCLUDout_1_0 = *(static_cast<CLUDout_1_0*> (pObj));
	if(chGBLBPStopSetOut == 1)
    asm(
                "bkpt 1"
                );
    rCLUDout_1_0.CalcReleySchematic();   
}
#include "Rele_p1.cpp"
static char chGLB_QTrg = 0;
static char chGLB_InC = 0;

void CLUDout_1_0::CalcReleySchematic(void){
register long rl_Val,i;

#pragma data_alignment=4
char arChIntermediaResult[(TOTAL_RELE_LU_CALC_POINT)];
const LedShcemasDscRecord* pLUShcemasDscRec;// = &arPLedShcemasDscRecords;
arChIntermediaResult[OFFSET_OUT_IN_RELE_TRIGGER_SELECTOR         ] = 0;//
arChIntermediaResult[OFFSET_OUT_IN_RELE_STABLE_SELECTOR          ] = 0;//
arChIntermediaResult[OFFSET_OUT_IN_RELE_PULSE_SELECTOR           ] = 0;//
arChIntermediaResult[OFFSET_OUT_IN_RELE_PULSE_SIMPLE_SELECTOR    ] = 0;//
arChIntermediaResult[OFFSET_OUT_IN_RELE_PULSE_EXTANDED_SELECTOR  ] = 0;//
arChIntermediaResult[OFFSET_OUT_IN_RELE__RIN                     ] = 0;//
arChIntermediaResult[OFFSET_OUT_IN_RELE__RESET                   ] = 0;//
arChIntermediaResult[OFFSET_OUT_IN_RELE__BL_IMP                  ] = 0;//
arChIntermediaResult[OFFSET_OUT_IN_RELE__C1_C2                   ] = 0;//
arChIntermediaResult[OFFSET_OUT_IN_RELE_C1                       ] = 0;//
arChIntermediaResult[OFFSET_OUT_IN_RELE_C2                       ] = 0;//

char *pCh = (this->arrPchIn[(RELEY_IN_NAME__RIN - 1)]);
arChIntermediaResult[OFFSET_OUT_IN_RELE__RIN ] = pCh[0];
pCh = (this->arrPchIn[(RELEY_IN_NAME__RESET - 1)]);
arChIntermediaResult[OFFSET_OUT_IN_RELE__RESET] = pCh[0];//
pCh = (this->arrPchIn[(RELEY_IN_NAME__BL_IMP - 1)]);
arChIntermediaResult[OFFSET_OUT_IN_RELE__BL_IMP] = pCh[0];//
pCh = (this->arrPchIn[(RELEY_IN_NAME__C1_C2 - 1)]);
arChIntermediaResult[OFFSET_OUT_IN_RELE__C1_C2] = pCh[0];//
if(this->m_ReleyCfgSuit.chSel1 == 0){
arChIntermediaResult[OFFSET_OUT_IN_RELE_NORMAL_SELECTOR] = 1;
}
else{
arChIntermediaResult[OFFSET_OUT_IN_RELE_TRIGGER_SELECTOR] = 1;
}
if(this->m_ReleyCfgSuit.chSel2 == 0){
arChIntermediaResult[OFFSET_OUT_IN_RELE_STABLE_SELECTOR] = 1;
}
else{
arChIntermediaResult[OFFSET_OUT_IN_RELE_PULSE_SELECTOR] = 1;
}
if(this->m_ReleyCfgSuit.chSel3 == 0){
arChIntermediaResult[OFFSET_OUT_IN_RELE_PULSE_SIMPLE_SELECTOR] = 1;
}
else{
arChIntermediaResult[OFFSET_OUT_IN_RELE_PULSE_EXTANDED_SELECTOR] = 1;
}

for (i = OFFSET_OUT_RELE_Not01__1_1; i < OFFSET_OUT_IN_RELE_NORMAL_SELECTOR; i++)//OFFSET_OUT_Or_22__3_1
    arChIntermediaResult[i] = 0xcc;
rl_Val = 0;
long k, j, l;
short shCounterProcessedRec = RELE_Not01__1_1;
  do {
    pLUShcemasDscRec = arPReleShcemasDscRecords[shCounterProcessedRec - RELE_Not01__1_1];
    i = pLUShcemasDscRec->chTypeOperation;
    switch (i) {
        case LU_GEN_OP_AND:
            rl_Val = 1;
            for (i = 0; (i < pLUShcemasDscRec->chAmtIn) &&(rl_Val == 1); i++) {
                k = pLUShcemasDscRec->pInputDscData[i].shOrderNumLU;
                l = arReleShOffsets[k];
                j = l + pLUShcemasDscRec->pInputDscData[i].shIndexOut;
                rl_Val &= arChIntermediaResult[j];
            }
            //arChIntermediaResult[shCounterProcessedRec++] = rl_Val;
            k = pLUShcemasDscRec->chOrderNumLU;
            i = arReleShOffsets[k]; //shCounterProcessedRec must be LED_SCHEMATIC_LU_ORDER_NUMS
            arChIntermediaResult[i] = rl_Val;
            shCounterProcessedRec++;
            break;
        case LU_GEN_OP_OR:
            rl_Val = 0;
            for (i = 0; (i < pLUShcemasDscRec->chAmtIn) &&(rl_Val == 0); i++) {
                k = pLUShcemasDscRec->pInputDscData[i].shOrderNumLU;
                l = arReleShOffsets[k];
                j = l + pLUShcemasDscRec->pInputDscData[i].shIndexOut;
                rl_Val |= arChIntermediaResult[j];
            }
            //arChIntermediaResult[shCounterProcessedRec++] = rl_Val;
            k = pLUShcemasDscRec->chOrderNumLU;
            i = arReleShOffsets[k]; //shCounterProcessedRec must be LED_SCHEMATIC_LU_ORDER_NUMS
            arChIntermediaResult[i] = rl_Val;
            shCounterProcessedRec++;
            break;
        case LU_GEN_OP_XOR:
            i = pLUShcemasDscRec->pInputDscData[0].shOrderNumLU;
            rl_Val = arReleShOffsets[i];
            i = rl_Val + pLUShcemasDscRec->pInputDscData[0].shIndexOut;
            j = arChIntermediaResult[i];
            i = pLUShcemasDscRec->pInputDscData[1].shOrderNumLU;
            rl_Val = arReleShOffsets[i];
            i = rl_Val + pLUShcemasDscRec->pInputDscData[1].shIndexOut;
            rl_Val = j^arChIntermediaResult[i];
            //arChIntermediaResult[shCounterProcessedRec++] = rl_Val;
            k = pLUShcemasDscRec->chOrderNumLU;
            l = arReleShOffsets[k]; //shCounterProcessedRec must be LED_SCHEMATIC_LU_ORDER_NUMS
            arChIntermediaResult[l] = rl_Val;
            shCounterProcessedRec++;
            break;
        case LU_GEN_OP_NOT:
            LUShcemasInDataDsc const *pLUShcemasInDataDsc;
            rl_Val = 0;
            pLUShcemasInDataDsc = pLUShcemasDscRec->pInputDscData;
            i = pLUShcemasInDataDsc[0].shOrderNumLU;
            rl_Val = arReleShOffsets[i];
            i = rl_Val + pLUShcemasInDataDsc[0].shIndexOut;
            rl_Val = arChIntermediaResult[i];
                //arChIntermediaResult[shCounterProcessedRec++] = rl_Val;
            k = pLUShcemasDscRec->chOrderNumLU;
            l = arReleShOffsets[k]; //shCounterProcessedRec must be LED_SCHEMATIC_LU_ORDER_NUMS
            arChIntermediaResult[l] = !rl_Val;
            shCounterProcessedRec++;
            break;
        case LU_GEN_OP_RS_TRIGGER:
            long lIdxInC;
            k = pLUShcemasDscRec->pInputDscData[0].shOrderNumLU;
            l = arReleShOffsets[k];
            lIdxInC = l + pLUShcemasDscRec->pInputDscData[0].shIndexOut;
                
            rl_Val = chGLB_QTrg;
            k = pLUShcemasDscRec->pInputDscData[2].shOrderNumLU;
            l = arReleShOffsets[k];
            j = l + pLUShcemasDscRec->pInputDscData[2].shIndexOut; //
            if (arChIntermediaResult[j]) {
                chGLB_QTrg = rl_Val = 0; //Clr
            } else {
                //k = pLUShcemasDscRec->pInputDscData[0].shOrderNumLU;
                //l = arReleShOffsets[k];
                //j = l + pLUShcemasDscRec->pInputDscData[0].shIndexOut;
                if ((chGLB_InC == 0) && (arChIntermediaResult[lIdxInC] > 0))
                    chGLB_QTrg = rl_Val = 1;
            }
            k = pLUShcemasDscRec->chOrderNumLU;
            i = arReleShOffsets[k];
            arChIntermediaResult[i] = rl_Val;
            arChIntermediaResult[i + 1] = !rl_Val;
            chGLB_InC = arChIntermediaResult[lIdxInC];
                shCounterProcessedRec++;
            break;

        default:
            shCounterProcessedRec++;
            asm(
                "bkpt 1"
                );
    }

  } while (shCounterProcessedRec < IN_RELE_NORMAL_SELECTOR);
    this->arrOut[(RELE_OUT_NAME__RELE_STATE_OUTPUT - 1)] = arChIntermediaResult[OFFSET_OUT_RELE_Or_07__2_1];
    bool bbState = false;
    bbState = arChIntermediaResult[OFFSET_OUT_RELE_Or_17__3_1];
    i = this->shShemasOrdNumStng;
    i--;
    if (bbState) {
        DoStateUI32Bit.ul_val |= (1) << i;
    } else {
        DoStateUI32Bit.ul_val &= ~((1) << i); //Phis write to Led
    }
}
