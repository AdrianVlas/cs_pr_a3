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
     m_chQTrg06 = 0;
     m_chInC06  = 0;
     m_chErrorQTrg06 = 0;
    m_shStartRecord = 0;
    m_shAmountProcessedRec = 0;
    m_pArLedShcemasDscRecords = const_cast< LedShcemasDscRecord** >(
    &arPLedShcemasDscRecords[0]);

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
    if (chGLBIn1_5 == rCLULed.shShemasOrdNumStng) {
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
//static char chGLB_QTrg = 0;static char chGLB_InC = 0;
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
/* if(*pCh != 0 && this->shShemasOrdNumStng == 1)
        asm(
        "bkpt 1"
        ); */
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
arChIntermediaResult[IN_06_TEST_BL] = !( *(this->arrPchIn[(LED_IN_NAME__TEST_M - 1)]) );
arChIntermediaResult[IN_07_TIN    ] = *(this->arrPchIn[(LED_IN_NAME__TLEDIN - 1)]);
arChIntermediaResult[IN_08_TEST   ] = *(this->arrPchIn[(LED_IN_NAME__TEST_M - 1)]);
arChIntermediaResult[IN_06_TEST_BL] =  0;
arChIntermediaResult[IN_07_TIN    ] =  0;
arChIntermediaResult[IN_08_TEST   ] =  0;


for (i = OFFSET_OUT_LED_NOT_01__1_1; i < OFFSET_OUT_IN_MNU_NORMAL_SELECTOR; i++)//OFFSET_OUT_Or_22__3_1
    arChIntermediaResult[i] = 0xcc;
   

rl_Val = 0;
if(this->m_LedCfgSuit.chSel1 == 0){
arChIntermediaResult[OFFSET_OUT_IN_MNU_NORMAL_SELECTOR] = 1;
    m_shAmountProcessedRec = shAmtLedShcemasSimpleModeDscRecords + LED_NOT_01__1_1;
    m_shStartRecord = LED_NOT_01__1_1; 
   m_pArLedShcemasDscRecords = const_cast< LedShcemasDscRecord** >(
    &arPLedShcemasStableDirectDscRecords[0]);
    arChIntermediaResult[OFFSET_OUT_LED_AND_15__3_1] =  0;
    arChIntermediaResult[OFFSET_OUT_LED_AND_16__3_1] =  0;
    arChIntermediaResult[OFFSET_OUT_LED_D_TRG_06__4_2] =  0;

}
else{
arChIntermediaResult[OFFSET_OUT_IN_MNU_TRIGGER_SELECTOR] = 1;
    m_shAmountProcessedRec = shAmtLedShcemasTriggerModeDscRecords
    +LED_NOT_01__1_1;
    m_shStartRecord = LED_NOT_01__1_1; 
   m_pArLedShcemasDscRecords = const_cast< LedShcemasDscRecord** >(
    &arPLedShcemasStableTriggerDscRecords[0]);
    arChIntermediaResult[OFFSET_OUT_LED_AND_15__3_1]   =  0;
    arChIntermediaResult[OFFSET_OUT_LED_AND_16__3_1]   =  0;
    arChIntermediaResult[OFFSET_OUT_LED_D_TRG_06__4_2] =  0;
    arChIntermediaResult[OFFSET_OUT_LED_NOT_01__1_1]   =  0;
    arChIntermediaResult[OFFSET_OUT_LED_AND_02__2_1]   =  0;
    arChIntermediaResult[OFFSET_OUT_LED_AND_03__2_1]   =  0;
    arChIntermediaResult[OFFSET_OUT_LED_AND_04__2_1]   =  0;
    arChIntermediaResult[OFFSET_OUT_LED_Or_05__2_1]    =  0;
    
    rl_Val = 1;
}
if(this->m_LedCfgSuit.chSel2 == 0){
arChIntermediaResult[OFFSET_OUT_IN_MNU_STABLE_SELECTOR] = 1;
}
else{
arChIntermediaResult[OFFSET_OUT_IN_MNU_PULSE_SELECTOR] = 1;
    if(this->m_LedCfgSuit.chSel3 == 0){
    arChIntermediaResult[OFFSET_OUT_IN_MNU_PULSE_SIMPLE_SELECTOR] = 1;
        if(rl_Val == 0){
            m_shAmountProcessedRec = shAmtLedShcemasPulseC1SimpleModeDscRecords
            +LED_NOT_01__1_1;
            m_shStartRecord = LED_NOT_01__1_1; 
           m_pArLedShcemasDscRecords = const_cast< LedShcemasDscRecord** >(
            &arPLedShcemasPulseC1SimpleDscRecords[0]);
        }
        else{
            m_shAmountProcessedRec = shAmtLedShcemasPulseC1TrigModeDscRecords
            +LED_NOT_01__1_1;
            m_shStartRecord = LED_NOT_01__1_1; 
           m_pArLedShcemasDscRecords = const_cast< LedShcemasDscRecord** >(
            &arPLedShcemasPulseC1TrigDscRecords[0]);
        }

    
    }
    else{
        arChIntermediaResult[OFFSET_OUT_IN_MNU_PULSE_EXTANDED_SELECTOR] = 1;
            m_shAmountProcessedRec = shAmtLedShcemasPulseC2TrigModeDscRecords
            +LED_NOT_01__1_1;
        m_shStartRecord = LED_NOT_01__1_1; 
       m_pArLedShcemasDscRecords = const_cast< LedShcemasDscRecord** >(
        &arPLedShcemasPulseC2TrigDscRecords[0]);
    }
        arChIntermediaResult[OFFSET_OUT_LED_AND_15__3_1]   =  0;
        arChIntermediaResult[OFFSET_OUT_LED_AND_16__3_1]   =  0;
        arChIntermediaResult[OFFSET_OUT_LED_D_TRG_06__4_2] =  0;
        arChIntermediaResult[OFFSET_OUT_LED_NOT_01__1_1]   =  0;
        arChIntermediaResult[OFFSET_OUT_LED_AND_02__2_1]   =  0;
        arChIntermediaResult[OFFSET_OUT_LED_AND_03__2_1]   =  0;
        arChIntermediaResult[OFFSET_OUT_LED_AND_04__2_1]   =  0;
        arChIntermediaResult[OFFSET_OUT_LED_Or_05__2_1]    =  0;
        arChIntermediaResult[OFFSET_OUT_LED_AND_10__2_1]   = 0;
        arChIntermediaResult[OFFSET_OUT_LED_OR_11__2_1 ]   = 0;
        arChIntermediaResult[OFFSET_OUT_LED_OR_12__2_1 ]   = 0;
}

arChIntermediaResult[OFFSET_OUT_IN_LED_VCC   ] = 1;
arChIntermediaResult[OFFSET_OUT_IN_LED_GROUND] = 0;


 
    //Attention! Energy Saved Param should be Init First
//arChIntermediaResult[OFFSET_OUT_LED_D_TRG_06__4_2] = m_chQTrg06;
//arChIntermediaResult[OFFSET_OUT_LED_D_TRG_06__4_2+1] = !m_chQTrg06;    
    rl_Val = 0;
    long k, j, l;
    short shCounterProcessedRec = m_shStartRecord;//LED_NOT_01__1_1;

    do {
//pLUShcemasDscRec = arPLedShcemasDscRecords[shCounterProcessedRec - LED_NOT_01__1_1];
pLUShcemasDscRec =m_pArLedShcemasDscRecords[shCounterProcessedRec - LED_NOT_01__1_1];
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
            case LU_GEN_OP_NOT:
                do{
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
                }while(false);
                shCounterProcessedRec++;
                break;
            case LU_GEN_OP_D_TRIGGER_TYPE3:
            case LU_GEN_OP_D_TRIGGER:
              do{
                long lIdxInC;
                j = 0;
                    //Check Set
                k = pLUShcemasDscRec->pInputDscData[0].shOrderNumLU;
                l = arShOffsets[k ]  ;
                rl_Val = arChIntermediaResult[l+ (pLUShcemasDscRec->pInputDscData[0].shIndexOut)];
                if (rl_Val == 1) {
                    /*k = pLUShcemasDscRec->chOrderNumLU;
                    i = arShOffsets[k];
                    arChIntermediaResult[i] = 1;
                    arChIntermediaResult[i + 1] = 0;*/
//                    if (k == LSS_D_TRG_11__4_2) {
//                        j = 11;
//                        m_chQTrg11 = 1;
//
//                    } else if (k == LSS_D_TRG_29__4_2) {
//                        j = 29;
//                        m_chQTrg29 = 1;
//                    }
                    m_chQTrg06 = 1;
                    j = 6;
                }
                //Check Clr
                k = pLUShcemasDscRec->pInputDscData[1].shOrderNumLU;
                l = arShOffsets[k];
                rl_Val = arChIntermediaResult[l+(pLUShcemasDscRec->pInputDscData[1].shIndexOut)];
                if (rl_Val == 1) {
                    /*k = pLUShcemasDscRec->chOrderNumLU;
                    i = arShOffsets[k];
                    arChIntermediaResult[i] = 0;
                    arChIntermediaResult[i+ 1]   = 1;
*/
//                    if (k == LSS_D_TRG_11__4_2) {
//                        if(j == 11)
//                            m_chErrorQTrg11 = 1;//Fix Error
//                        m_chQTrg11 = 0;
//                    } else if (k == LSS_D_TRG_29__4_2) {
//                        if(j == 29)
//                            m_chErrorQTrg29 = 1;//Fix Error
//                        m_chQTrg29 = 0;
//                    }
                    if(j == 06)
                        m_chErrorQTrg06 = 1;//Fix Error
                    m_chQTrg06 = 0;    
                }
                else {
                        //Check D
                    j = 0;
                    k = pLUShcemasDscRec->pInputDscData[2].shOrderNumLU;
                    l = arShOffsets[k];
                    rl_Val = arChIntermediaResult[l+(pLUShcemasDscRec->pInputDscData[2].shIndexOut)];
                    if (rl_Val == 1) {
                        k = pLUShcemasDscRec->pInputDscData[3].shOrderNumLU;
                        lIdxInC = arShOffsets[k]+(pLUShcemasDscRec->pInputDscData[3].shIndexOut);
                        if (arChIntermediaResult[lIdxInC] > 0){
                            k = pLUShcemasDscRec->chOrderNumLU;
                           //Chek Curr Trigger
//                            if (k == LSS_D_TRG_11__4_2) {
//                                if(m_chInC11==0){
//                                    j++;
//                                    m_chQTrg11 = 1;
//                                }
//
//                            } else if (k == LSS_D_TRG_29__4_2) {
//                                j++;
//                                m_chQTrg29 = 1;
//                            }
                            if(m_chInC06 ==0 ){
                                j++;
                                m_chQTrg06 = 1;
                            }
                            /*if(j == 1){
                            //set Out
                            k = pLUShcemasDscRec->chOrderNumLU;
                            i = arShOffsets[k];
                            arChIntermediaResult[i ] = 1;
                            arChIntermediaResult[i+ 1] = 0;
                            }*/
                        }

                    }
                    k = pLUShcemasDscRec->chOrderNumLU;
//                    if (k == LSS_D_TRG_11__4_2) {
//
//                        k = pLUShcemasDscRec->pInputDscData[3].shOrderNumLU;
//                        lIdxInC = arShOffsets[k]+(pLUShcemasDscRec->pInputDscData[3].shIndexOut);
//                        m_chInC11 = arChIntermediaResult[lIdxInC];
//                    } else if (k == LSS_D_TRG_29__4_2) {
//
//                        k = pLUShcemasDscRec->pInputDscData[3].shOrderNumLU;
//                        lIdxInC = arShOffsets[k]+(pLUShcemasDscRec->pInputDscData[3].shIndexOut);
//                        m_chQTrg11 = arChIntermediaResult[lIdxInC];
//
//                    }
                    
                    
                }
                k = pLUShcemasDscRec->pInputDscData[3].shOrderNumLU;
                    lIdxInC = arShOffsets[k]+(pLUShcemasDscRec->pInputDscData[3].shIndexOut);
                    m_chInC06 = arChIntermediaResult[lIdxInC];
                    k = pLUShcemasDscRec->chOrderNumLU;
                    i = arShOffsets[k];
                    arChIntermediaResult[i] = m_chQTrg06;
                    arChIntermediaResult[i + 1] = !m_chQTrg06;
              }while(false);
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
  
    } while (shCounterProcessedRec < m_shAmountProcessedRec);//LED_OR_17__3_1
    //while (shCounterProcessedRec < m_shAmountProcessedRec);
    
    this->arrOut[(LED_OUT_NAME__LED_STATE_OUTPUT-1)] = arChIntermediaResult[OFFSET_OUT_LED_OR_17__3_1];
    bool bbState = false;
    bbState = arChIntermediaResult[OFFSET_OUT_LED_OR_17__3_1]; //
    char *pCh1,*pCh2;
    pCh1 = (this->arrPchIn[(LED_IN_NAME__TEST_M - 1)]);
    arChIntermediaResult[OFFSET_OUT_LED_AND_18__2_1] = bbState
    && (!(*pCh1));
    
    pCh2 = this->arrPchIn[(LED_IN_NAME__TLEDIN - 1)];
    arChIntermediaResult[OFFSET_OUT_LED_AND_19__2_1] = *pCh1 && *pCh2;

    bbState = arChIntermediaResult[OFFSET_OUT_LED_AND_19__2_1] 
    || arChIntermediaResult[OFFSET_OUT_LED_AND_18__2_1];
    i = this->shShemasOrdNumStng;
    i--;
    if (bbState) {
        LedStateUI32Bit.ul_val |= (1) << i;
    } else {
        LedStateUI32Bit.ul_val &= ~((1) << i); //Phis write to Led
    }
}

