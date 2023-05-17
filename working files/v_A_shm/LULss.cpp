
#include "LULss.h"

#include <string.h>
#include "stm32f2xx.h"
#include "stm32f2xx_it.h"
#include "Ereg.h"
//include "prtTmr.h"
#include "IStng.h"

CLULss::CLULss(void) {
}

CLULss::~CLULss(void) {
	
}

CLULss::CLULss(char chM,char chI) {
/*
    memset(static_cast<void*>(arrPchIn),0xcc,sizeof(char*)*shCLULed_1_0_AmtIn);
        memset(static_cast<void*>(arrPchSchIn),0xcc,sizeof(char*)*TOTAL_LED_VISIO_IN);
        memset(static_cast<void*>(arrPchAlternator),0xcc,sizeof(char*)*2);
        memset(static_cast<void*>(arrOut),0,sizeof(char  )*TOTAL_LED_VISIO_OUTPUT);
        memset(static_cast<void*>(&m_LedCfgSuit),0,sizeof(LedCfgSuit));
     */
    memset(static_cast<void*> (&m_LssCfgSuit), 0, sizeof (LssCfgSuit));
    chMaxIteratoin = chM;
    chIteration = chI;
    chNumInput = static_cast<char> (TOTAL_LSS_IN);
    chNumOutput = static_cast<char> (TOTAL_LSS_OUTPUT);
    m_Node1_1Ms.lTmrVal = 0;
    m_Node1_1Ms.next = 0;
    m_Node1_2Ms.lTmrVal = 0;
    m_Node1_2Ms.next = 0;;
    m_Node1_3Ms.lTmrVal = 0;
    m_Node1_3Ms.next = 0;
    m_NodeCs.lTmrVal = 0;
    m_NodeCs.next = 0;
    m_chLinkedTimers = 0;
    m_chStateT1_1Ms = 0;
    m_chStateT1_2Ms = 0;
    m_chStateT1_3Ms = 0;
    m_chStateTCs = 0;
m_chQTrg29 = 0;
m_chQTrg11 = 0;
m_chInC29  = 0;
m_chInC11  = 0;	
m_chErrorQTrg29 = 0;
m_chErrorQTrg11 = 0;	
m_shStartRecord = 0;
m_shAmountProcessedRec = 0;
m_pArLssShcemasDscRecords = const_cast< LedShcemasDscRecord** >(
&arPLssShcemasSimpleModeDscRecords[0]);
//const_cast<const LedShcemasDscRecord*>();
}
void CLULss::UpdateCLss(void) {
//Set Input parameters
pIn = static_cast<void*>(arrPchIn);
//Set OutPut parameters
pOut = static_cast<void*>(arrOut);
memset(static_cast<void*>(arrOut),0,sizeof(char  )*TOTAL_LSS_OUTPUT);
memset(static_cast<void*>(arrPchIn),0xcc,sizeof(char*)*TOTAL_LSS_IN);
//LinkMftTimers();
//pInit2LcVarArea->pCLUBase->shShemasIdLUStng =  STNG_LU_NOT;

//Set Operation
//Set Type Operation
}
long CLULss::LinkLssTimers(void) {
    register long i = 0;
    //Insert TpauseMft
    chGlSem++;
    
    if (PushTmrNode(&m_Node1_1Ms)) {//static_cast<void*>(
        i++;
        m_chLinkedTimers |= 2;
    }
    //Insert TdelayMft
    if (PushTmrNode(&m_Node1_2Ms)) {//static_cast<void*>(
        i++;
        m_chLinkedTimers |= 4;
    }
    //Insert TWorkMft 
    if (PushTmrNode(&m_NodeCs)) {//static_cast<void*>(
        i++;
        m_chLinkedTimers |= 8;
    }
    if (PushTmrNode(&m_Node1_3Ms)) {//static_cast<void*>(
        i++;
        m_chLinkedTimers |= 0x10;
    }
    
    chGlSem--;
    return i;
}
long CLULss::T1_1Ms(long lActivKey) {
register long *plTmrVal = &m_Node1_1Ms.lTmrVal;
register long lResetKey = 0;
    if (lActivKey)
    {
        if (m_chStateT1_1Ms == 0) {
            lActivKey = 1;//m_MftSuit.lTWork;
            *plTmrVal = lActivKey;
            if (*plTmrVal != lActivKey)
                *plTmrVal = lActivKey;
            m_chStateT1_1Ms = 1;
            return 1;
        }
        else if (m_chStateT1_1Ms >= 1) {
            lActivKey = *plTmrVal;
            if (lActivKey != 0)
                return 1; //
            //else
            //return 0;//    m_chStateT1_1Ms = 0;//
        }
    }
    else
    {
        if (m_chStateT1_1Ms == 1) {//Activated
            lActivKey = *plTmrVal;
            if (lActivKey != 0)
                return 1; //
            else
                lResetKey = 1;
        }
    }
    if (lResetKey) {
        m_chStateT1_1Ms = 0;
        *plTmrVal = 0;
    }
    return 0;
}
long CLULss::T1_2Ms(long lActivKey){
register long *plTmrVal = &m_Node1_2Ms.lTmrVal;
register long lResetKey = 0;
    if (lActivKey) {
        if (m_chStateT1_2Ms == 0) {
            lActivKey = 1;//m_MftSuit.lTWork;
            *plTmrVal = lActivKey;
            if (*plTmrVal != lActivKey)
                *plTmrVal = lActivKey;
            m_chStateT1_2Ms = 1;
            return 1;
        } else {
            lActivKey = *plTmrVal;
            if (lActivKey != 0)
                return 1; //
        }
    } else {
        if (m_chStateT1_2Ms == 1) {//Activated
            lActivKey = *plTmrVal;
            if (lActivKey != 0)
                return 1; //
            else
                lResetKey = 1;
        }
    }
    if (lResetKey) {
        m_chStateT1_2Ms = 0;
        *plTmrVal = 0;
    }
    return 0;	
}
long CLULss::TCs(long lActivKey){
register long *plTmrVal = &m_NodeCs.lTmrVal;
    if (lActivKey) {
        if (m_chStateTCs == 0) {
            lActivKey = m_LssCfgSuit.lTCs; //Load Timer
            *plTmrVal = lActivKey;
            if (*plTmrVal != lActivKey)
                *plTmrVal = lActivKey; //Possible Clear in Int
            m_chStateTCs = 1;
        } else {
            lActivKey = *plTmrVal;
            if (lActivKey == 0) {
                return 1; //End of Interval
            }
        }
        
    } else {
        ;
        m_chStateTCs = 0;
        *plTmrVal = 0; //m_NodeTpause.lTmrVal = 0;
    }
    return 0;
}

long CLULss::T1_3Ms(long lActivKey) {
register long *plTmrVal = &m_Node1_3Ms.lTmrVal;
register long lResetKey = 0;
    if (lActivKey) {
        if (m_chStateT1_3Ms == 0) {
            lActivKey = 1;//m_MftSuit.lTWork;
            *plTmrVal = lActivKey;
            if (*plTmrVal != lActivKey)
                *plTmrVal = lActivKey;
            m_chStateT1_3Ms = 1;
            return 1;
        } else {
            lActivKey = *plTmrVal;
            if (lActivKey != 0)
                return 1; //
        }
    } else {
        if (m_chStateT1_3Ms == 1) {//Activated
            lActivKey = *plTmrVal;
            if (lActivKey != 0)
                return 1; //
            else
                lResetKey = 1;
        }
    }
    if (lResetKey) {
        m_chStateT1_3Ms = 0;
        *plTmrVal = 0;
    }
    return 0;
}


#include "LuLss_p1.cpp"
inline void CLULss::SetStateVarchQTrg(long lIdTrg, char&chQTrg) {
    if (lIdTrg == LSS_D_TRG_11__4_2) {
        m_chQTrg11 = chQTrg;
    } else if (lIdTrg == LSS_D_TRG_29__4_2) {
        m_chQTrg29 = chQTrg;
    }
}
inline void CLULss::SetStateVarchInC (long lIdTrg, char&chInC) {
    if (lIdTrg == LSS_D_TRG_11__4_2) {
        m_chInC11 = chInC;
    } else if (lIdTrg == LSS_D_TRG_29__4_2) {
        m_chInC29 = chInC;
    }
}
inline void CLULss::SetStateVarchErrorQTrg(long lIdTrg, char&chErrorQTrg){
    if (lIdTrg == LSS_D_TRG_11__4_2) {
            m_chErrorQTrg11 = chErrorQTrg; //Fix Error
        m_chQTrg11 = 0;
    } else if (lIdTrg == LSS_D_TRG_29__4_2) {
            m_chErrorQTrg29 = chErrorQTrg; //Fix Error
        m_chQTrg29 = 0;
    }  
}
inline long CLULss::GetStateVarchQTrg(long lIdTrg){
    register long QTrg;
    if (lIdTrg == LSS_D_TRG_11__4_2) {
        QTrg = m_chQTrg11;
    } else if (lIdTrg == LSS_D_TRG_29__4_2) {
        QTrg = m_chQTrg29;
    }
    return QTrg;
}
inline long CLULss::GetStateVarchInC (long lIdTrg) {
    register long lInC;
    if (lIdTrg == LSS_D_TRG_11__4_2) {
        lInC = m_chInC11;
    } else if (lIdTrg == LSS_D_TRG_29__4_2) {
        lInC = m_chInC29;
    }
    return lInC;
}
inline long CLULss::GetStateVarchErrorQTrg(long lIdTrg){
    register long lErrorQTrg;
    if (lIdTrg == LSS_D_TRG_11__4_2) {
            lErrorQTrg = m_chErrorQTrg11; //Fix Error
        m_chQTrg11 = 0;
    } else if (lIdTrg == LSS_D_TRG_29__4_2) {
           lErrorQTrg =  m_chErrorQTrg29; //Fix Error
        m_chQTrg29 = 0;
    } 
    return lErrorQTrg;
}
//static char chGLB_QTrg29 = 0;static char chGLB_InC29 = 0;
//static char chGLB_QTrg11 = 0;static char chGLB_InC11 = 0;
void CLULss::CalcLssSchematic(void){
register long rl_Val,i;
const LedShcemasDscRecord* pLUShcemasDscRec;// = &arPLedShcemasDscRecords;
#pragma data_alignment=4
char arChIntermediaResult[(TOTAL_LSS_LU_CALC_POINT)];
volatile bool boolchQTrg29 = m_chQTrg29,boolchQTrg11 = m_chQTrg11;

//for (i = OFFSET_OUT_LSS_NOT_01__1_1; i < OFFSET_OUT_IN_LSS_VCC; i++)//OFFSET_OUT_Or_22__3_1
//    arChIntermediaResult[i] = 0xcc;
    
arChIntermediaResult[ OFFSET_OUT_IN_LSS_NORMAL      ] = 0;//
arChIntermediaResult[ OFFSET_OUT_IN_LSS_TRIGGER     ] = 0;//
arChIntermediaResult[ OFFSET_OUT_IN_LSS_TIMELIMITED ] = 0;//
arChIntermediaResult[ OFFSET_OUT_IN_LSS_LSSIN1      ] = 0;//
arChIntermediaResult[ OFFSET_OUT_IN_LSS_MUTE_I      ] = 0;//
arChIntermediaResult[ OFFSET_OUT_IN_LSS_RESET_I     ] = 0;//arChIntermediaResult[  ] = 0;//
arChIntermediaResult[ OFFSET_OUT_IN_LSS_BLOCK_I     ] = 0;//
arChIntermediaResult[ OFFSET_OUT_LSS_D_TRG_11__4_2    ] = m_chQTrg11;
arChIntermediaResult[ OFFSET_OUT_LSS_D_TRG_11__4_2 + 1  ] = !m_chQTrg11;
arChIntermediaResult[ OFFSET_OUT_LSS_D_TRG_29__4_2    ] = m_chQTrg29;
arChIntermediaResult[ OFFSET_OUT_LSS_D_TRG_29__4_2 + 1  ] = !m_chQTrg29;

arChIntermediaResult[ OFFSET_OUT_IN_LSS_VCC      ] = 1;//
arChIntermediaResult[ OFFSET_OUT_IN_LSS_GROUND   ] = 0;//
char *pCh = (this->arrPchIn[(LSS_IN_NAME__LSSIN1 - 1)]);
arChIntermediaResult[OFFSET_OUT_IN_LSS_LSSIN1 ] = pCh[0];
pCh = (this->arrPchIn[(LSS_IN_NAME__MUTE_I - 1)]);
arChIntermediaResult[OFFSET_OUT_IN_LSS_MUTE_I ] = pCh[0];//
pCh = (this->arrPchIn[(LSS_IN_NAME__RESET_I - 1)]);
arChIntermediaResult[OFFSET_OUT_IN_LSS_RESET_I] = pCh[0];//
pCh = (this->arrPchIn[(LSS_IN_NAME__BLOCK_I - 1)]);
arChIntermediaResult[OFFSET_OUT_IN_LSS_BLOCK_I] = pCh[0];//

    if (m_LssCfgSuit.chSel == LSS_MODE_SIMPLE){
        arChIntermediaResult[ OFFSET_OUT_IN_LSS_NORMAL ] = 1; //
        m_shAmountProcessedRec = shPLssShcemasSimpleModeDscRecords;
        m_shStartRecord = LSS_NOT_01__1_1; 
        m_pArLssShcemasDscRecords = const_cast< LedShcemasDscRecord** >(
        &arPLssShcemasSimpleModeDscRecords[0]);
    }
    else {
        if (m_LssCfgSuit.chSel == LSS_MODE_TRIGGER){
            arChIntermediaResult[ OFFSET_OUT_IN_LSS_TRIGGER ] = 1; //
            }
    else
        if (m_LssCfgSuit.chSel == LSS_MODE_PERIOD){
        arChIntermediaResult[ OFFSET_OUT_IN_LSS_TIMELIMITED ] = 1; //
        }
        m_shAmountProcessedRec = shPLssShcemasTriggerModeDscRecords;  
        m_shStartRecord = LSS_NOT_01__1_1;
        m_pArLssShcemasDscRecords =  const_cast< LedShcemasDscRecord** >(
        &arPLssShcemasTriggerModeDscRecords[0]);      
    }

//for (i = OFFSET_OUT_LSS_NOT_01__1_1; i < OFFSET_OUT_IN_LSS_VCC; i++)//OFFSET_OUT_Or_22__3_1
//    arChIntermediaResult[i] = 0xcc;
rl_Val = 0;
long k, j, l;
short shCounterProcessedRec = m_shStartRecord;//LSS_NOT_01__1_1;
do{
    //pLUShcemasDscRec = arPLssShcemasDscRecords[shCounterProcessedRec - LSS_NOT_01__1_1];
    pLUShcemasDscRec = m_pArLssShcemasDscRecords[shCounterProcessedRec];
    i = pLUShcemasDscRec->chTypeOperation;
    switch (i) {
        case LU_GEN_OP_AND:
            rl_Val = 1;
            for (i = 0; (i < pLUShcemasDscRec->chAmtIn) &&(rl_Val == 1); i++) {
                k = pLUShcemasDscRec->pInputDscData[i].shOrderNumLU;
                l = arShLssOffsets[k];
                j = l + pLUShcemasDscRec->pInputDscData[i].shIndexOut;
                rl_Val &= arChIntermediaResult[j];
            }
            //arChIntermediaResult[shCounterProcessedRec++] = rl_Val;
            k = pLUShcemasDscRec->chOrderNumLU;
            i = arShLssOffsets[k]; //shCounterProcessedRec must be LED_SCHEMATIC_LU_ORDER_NUMS
            arChIntermediaResult[i] = rl_Val;
            shCounterProcessedRec++;
            break;
        case LU_GEN_OP_OR:
            rl_Val = 0;
            for (i = 0; (i < pLUShcemasDscRec->chAmtIn) &&(rl_Val == 0); i++) {
                k = pLUShcemasDscRec->pInputDscData[i].shOrderNumLU;
                l = arShLssOffsets[k];
                j = l + pLUShcemasDscRec->pInputDscData[i].shIndexOut;
                rl_Val |= arChIntermediaResult[j];
            }
            //arChIntermediaResult[shCounterProcessedRec++] = rl_Val;
            k = pLUShcemasDscRec->chOrderNumLU;
            i = arShLssOffsets[k]; //shCounterProcessedRec must be LED_SCHEMATIC_LU_ORDER_NUMS
            arChIntermediaResult[i] = rl_Val;
            shCounterProcessedRec++;
            break;    
        case LU_GEN_OP_NOT:
            do{
            LUShcemasInDataDsc const *pLUShcemasInDataDsc;
            rl_Val = 0;
            pLUShcemasInDataDsc = pLUShcemasDscRec->pInputDscData;
            i = pLUShcemasInDataDsc[0].shOrderNumLU;
            rl_Val = arShLssOffsets[i];
            i = rl_Val + pLUShcemasInDataDsc[0].shIndexOut;
            rl_Val = arChIntermediaResult[i];
                //arChIntermediaResult[shCounterProcessedRec++] = rl_Val;
            k = pLUShcemasDscRec->chOrderNumLU;
            l = arShLssOffsets[k]; //shCounterProcessedRec must be LED_SCHEMATIC_LU_ORDER_NUMS
            arChIntermediaResult[l] = !rl_Val;
            }while(false);
            shCounterProcessedRec++;
            break;
        case LU_GEN_OP_D_TRIGGER_TYPE3:
        case LU_GEN_OP_D_TRIGGER:
          do{
            long lIdxInC;
             char chInC,chErrorQTrg,chQTrg;
            chQTrg = GetStateVarchQTrg(pLUShcemasDscRec->chOrderNumLU);
            
            j = 0;
                //Check Set
            k = pLUShcemasDscRec->pInputDscData[0].shOrderNumLU;
            l = arShLssOffsets[k ]  ;
            rl_Val = arChIntermediaResult[l+ (pLUShcemasDscRec->pInputDscData[0].shIndexOut)];
            if (rl_Val == 1) {
                /*k = pLUShcemasDscRec->chOrderNumLU;
                i = arShLssOffsets[k];
                arChIntermediaResult[i] = 1;
                arChIntermediaResult[i + 1] = 0;
                if (k == LSS_D_TRG_11__4_2) {
                    j = 11;
                    m_chQTrg11 = 1;
                
                } else if (k == LSS_D_TRG_29__4_2) {
                    j = 29;
                    m_chQTrg29 = 1;
                }*/
                j = pLUShcemasDscRec->chOrderNumLU;
                chQTrg = 1;
            }
            //Check Clr
            k = pLUShcemasDscRec->pInputDscData[1].shOrderNumLU;
            l = arShLssOffsets[k];
            rl_Val = arChIntermediaResult[l+(pLUShcemasDscRec->pInputDscData[1].shIndexOut)];
            if (rl_Val == 1) {
                /*k = pLUShcemasDscRec->chOrderNumLU;
                i = arShLssOffsets[k];
                arChIntermediaResult[i] = 0;
                arChIntermediaResult[i+ 1]   = 1;
				
                if (k == LSS_D_TRG_11__4_2) {
                    if(j == 11)
                        m_chErrorQTrg11 = 1;//Fix Error
                    m_chQTrg11 = 0;
                } else if (k == LSS_D_TRG_29__4_2) {
                    if(j == 29)
                        m_chErrorQTrg29 = 1;//Fix Error
                    m_chQTrg29 = 0;
                }*/
                if(j == pLUShcemasDscRec->chOrderNumLU) {
                    chErrorQTrg = GetStateVarchErrorQTrg(pLUShcemasDscRec->chOrderNumLU);
                    chErrorQTrg = 1; //Fix Error
                    SetStateVarchErrorQTrg(pLUShcemasDscRec->chOrderNumLU, chErrorQTrg);
                }
                chQTrg = 0;  
            }
            else {
                    //Check C
                j = 0;
                k = pLUShcemasDscRec->pInputDscData[3].shOrderNumLU;
                l = arShLssOffsets[k];
                lIdxInC = arShLssOffsets[k]+(pLUShcemasDscRec->pInputDscData[3].shIndexOut);
                chInC = GetStateVarchInC(pLUShcemasDscRec->chOrderNumLU);
                if ((arChIntermediaResult[lIdxInC] > 0) && (chInC ==0 ) ){
                //Check D
                k = pLUShcemasDscRec->pInputDscData[2].shOrderNumLU;        
                chQTrg = arChIntermediaResult[l+(pLUShcemasDscRec->pInputDscData[2].shIndexOut)];  
                }
            }
            l = k = pLUShcemasDscRec->chOrderNumLU;
            i = arShLssOffsets[k];
            arChIntermediaResult[i] = chQTrg;
            arChIntermediaResult[i + 1] = !chQTrg;
            k = pLUShcemasDscRec->pInputDscData[3].shOrderNumLU;
            lIdxInC = arShLssOffsets[k]+(pLUShcemasDscRec->pInputDscData[3].shIndexOut);
            chInC = arChIntermediaResult[lIdxInC];
            
            SetStateVarchQTrg(l,chQTrg);
            SetStateVarchInC(l,chInC);
            
          }while(false);
            shCounterProcessedRec++;
            break;
        case LU_GEN_OP_DELAY1:
            do{
            LUShcemasInDataDsc const *pLUShcemasInDataDsc;
            rl_Val = 0;
            pLUShcemasInDataDsc = pLUShcemasDscRec->pInputDscData;
            i = pLUShcemasInDataDsc[0].shOrderNumLU;
            l = arShLssOffsets[i];
            i = l + pLUShcemasInDataDsc[0].shIndexOut;
            rl_Val = arChIntermediaResult[i];
            rl_Val = TCs(rl_Val);
            k = pLUShcemasDscRec->chOrderNumLU;
            l = arShLssOffsets[k]; //shCounterProcessedRec must be LED_SCHEMATIC_LU_ORDER_NUMS
            arChIntermediaResult[l] = rl_Val;
            }while(false);
            shCounterProcessedRec++;
            break;
        case LU_GEN_OP_PULSE:
            do{
            LUShcemasInDataDsc const *pLUShcemasInDataDsc;
            rl_Val = 0;
            pLUShcemasInDataDsc = pLUShcemasDscRec->pInputDscData;
            i = pLUShcemasInDataDsc[0].shOrderNumLU;
            l = arShLssOffsets[i];
            i = l + pLUShcemasInDataDsc[0].shIndexOut;
            rl_Val = arChIntermediaResult[i];
            j = 0;//
            k = pLUShcemasDscRec->chOrderNumLU;
            if (k == LSS_DELAY_05_1_1) {
                rl_Val = T1_1Ms(rl_Val);
            } else if (k == LSS_DELAY_06_1_1) {
                rl_Val = T1_2Ms(rl_Val);
            }
            k = pLUShcemasDscRec->chOrderNumLU;
            l = arShLssOffsets[k]; //shCounterProcessedRec must be LED_SCHEMATIC_LU_ORDER_NUMS
            arChIntermediaResult[l] = rl_Val;
            }while(false);
            shCounterProcessedRec++;
            break;
            
        default:
            ;
        } //switch    
    } while (shCounterProcessedRec < m_shAmountProcessedRec);//IN_SIMPLE_SELECTOR
arChIntermediaResult[ OFFSET_OUT_OUT_LSS_ALARM    ] = 
arChIntermediaResult[OFFSET_OUT_LSS_OR_27__2_1];//

arChIntermediaResult[ OFFSET_OUT_OUT_LSS_MUTE     ] = 
arChIntermediaResult[OFFSET_OUT_LSS_OR_28__2_1];// 
   
 this->arrOut [LSS_OUT_NAME_ALARM -1] = arChIntermediaResult[OFFSET_OUT_LSS_OR_27__2_1];       
 this->arrOut [LSS_OUT_NAME_MUTE  -1] = arChIntermediaResult[OFFSET_OUT_LSS_OR_28__2_1];      

}
void CLULss::CalcLssSchematicOpt(void){
register long rl_Val,i;
const LedShcemasDscRecord* pLUShcemasDscRec;// = &arPLedShcemasDscRecords;
#pragma data_alignment=4
char arChIntermediaResult[(TOTAL_LSS_LU_CALC_POINT)];
volatile bool boolchQTrg29 = m_chQTrg29,boolchQTrg11 = m_chQTrg11;

//for (i = OFFSET_OUT_LSS_NOT_01__1_1; i < OFFSET_OUT_IN_LSS_VCC; i++)//OFFSET_OUT_Or_22__3_1
//    arChIntermediaResult[i] = 0xcc;
arChIntermediaResult[ OFFSET_OUT_IN_LSS_NORMAL      ] = 0;//
arChIntermediaResult[ OFFSET_OUT_IN_LSS_TRIGGER     ] = 0;//
arChIntermediaResult[ OFFSET_OUT_IN_LSS_TIMELIMITED ] = 0;//
arChIntermediaResult[ OFFSET_OUT_IN_LSS_LSSIN1      ] = 0;//
arChIntermediaResult[ OFFSET_OUT_IN_LSS_MUTE_I      ] = 0;//
arChIntermediaResult[ OFFSET_OUT_IN_LSS_RESET_I     ] = 0;//arChIntermediaResult[  ] = 0;//
arChIntermediaResult[ OFFSET_OUT_IN_LSS_BLOCK_I     ] = 0;//

arChIntermediaResult[ OFFSET_OUT_LSS_D_TRG_11__4_2    ] = m_chQTrg11;
arChIntermediaResult[ OFFSET_OUT_LSS_D_TRG_11__4_2 + 1  ] = !m_chQTrg11;
arChIntermediaResult[ OFFSET_OUT_LSS_D_TRG_29__4_2    ] = m_chQTrg29;
arChIntermediaResult[ OFFSET_OUT_LSS_D_TRG_29__4_2 + 1  ] = !m_chQTrg29;

arChIntermediaResult[ OFFSET_OUT_IN_LSS_VCC      ] = 1;//
arChIntermediaResult[ OFFSET_OUT_IN_LSS_GROUND   ] = 0;//
char *pCh = (this->arrPchIn[(LSS_IN_NAME__LSSIN1 - 1)]);
arChIntermediaResult[OFFSET_OUT_IN_LSS_LSSIN1 ] = pCh[0];
pCh = (this->arrPchIn[(LSS_IN_NAME__MUTE_I - 1)]);
arChIntermediaResult[OFFSET_OUT_IN_LSS_MUTE_I ] = pCh[0];//
pCh = (this->arrPchIn[(LSS_IN_NAME__RESET_I - 1)]);
arChIntermediaResult[OFFSET_OUT_IN_LSS_RESET_I] = pCh[0];//
pCh = (this->arrPchIn[(LSS_IN_NAME__BLOCK_I - 1)]);
arChIntermediaResult[OFFSET_OUT_IN_LSS_BLOCK_I] = pCh[0];//

    if (m_LssCfgSuit.chSel == LSS_MODE_SIMPLE)
        arChIntermediaResult[ OFFSET_OUT_IN_LSS_NORMAL ] = 1; //
    else //{
        if (m_LssCfgSuit.chSel == LSS_MODE_TRIGGER)
            arChIntermediaResult[ OFFSET_OUT_IN_LSS_TRIGGER ] = 1; //
    else
        if (m_LssCfgSuit.chSel == LSS_MODE_PERIOD)
        arChIntermediaResult[ OFFSET_OUT_IN_LSS_TIMELIMITED ] = 1; //
    //}

//for (i = OFFSET_OUT_LSS_NOT_01__1_1; i < OFFSET_OUT_IN_LSS_VCC; i++)//OFFSET_OUT_Or_22__3_1
//    arChIntermediaResult[i] = 0xcc;
rl_Val = 0;
long k, j, l;
/*
if(){

}
else{
    if(){ Think About Mode selector
    
    }
}
*/
short shCounterProcessedRec = LSS_NOT_01__1_1;
do{
    pLUShcemasDscRec = arPLssShcemasDscRecords[shCounterProcessedRec - LSS_NOT_01__1_1];
    i = pLUShcemasDscRec->chTypeOperation;
    switch (i) {
        case LU_GEN_OP_AND:
            rl_Val = 1;
            for (i = 0; (i < pLUShcemasDscRec->chAmtIn) &&(rl_Val == 1); i++) {
                k = pLUShcemasDscRec->pInputDscData[i].shOrderNumLU;
                l = arShLssOffsets[k];
                j = l + pLUShcemasDscRec->pInputDscData[i].shIndexOut;
                rl_Val &= arChIntermediaResult[j];
            }
            //arChIntermediaResult[shCounterProcessedRec++] = rl_Val;
            k = pLUShcemasDscRec->chOrderNumLU;
            i = arShLssOffsets[k]; //shCounterProcessedRec must be LED_SCHEMATIC_LU_ORDER_NUMS
            arChIntermediaResult[i] = rl_Val;
            shCounterProcessedRec++;
            break;
        case LU_GEN_OP_OR:
            rl_Val = 0;
            for (i = 0; (i < pLUShcemasDscRec->chAmtIn) &&(rl_Val == 0); i++) {
                k = pLUShcemasDscRec->pInputDscData[i].shOrderNumLU;
                l = arShLssOffsets[k];
                j = l + pLUShcemasDscRec->pInputDscData[i].shIndexOut;
                rl_Val |= arChIntermediaResult[j];
            }
            //arChIntermediaResult[shCounterProcessedRec++] = rl_Val;
            k = pLUShcemasDscRec->chOrderNumLU;
            i = arShLssOffsets[k]; //shCounterProcessedRec must be LED_SCHEMATIC_LU_ORDER_NUMS
            arChIntermediaResult[i] = rl_Val;
            shCounterProcessedRec++;
            break;    
        case LU_GEN_OP_NOT:
            do{
            LUShcemasInDataDsc const *pLUShcemasInDataDsc;
            rl_Val = 0;
            pLUShcemasInDataDsc = pLUShcemasDscRec->pInputDscData;
            i = pLUShcemasInDataDsc[0].shOrderNumLU;
            rl_Val = arShLssOffsets[i];
            i = rl_Val + pLUShcemasInDataDsc[0].shIndexOut;
            rl_Val = arChIntermediaResult[i];
                //arChIntermediaResult[shCounterProcessedRec++] = rl_Val;
            k = pLUShcemasDscRec->chOrderNumLU;
            l = arShLssOffsets[k]; //shCounterProcessedRec must be LED_SCHEMATIC_LU_ORDER_NUMS
            arChIntermediaResult[l] = !rl_Val;
            }while(false);
            shCounterProcessedRec++;
            break;
        case LU_GEN_OP_D_TRIGGER_TYPE3:
        case LU_GEN_OP_D_TRIGGER:
          do{
            long lIdxInC;
             char chInC,chErrorQTrg,chQTrg;
            chQTrg = GetStateVarchQTrg(pLUShcemasDscRec->chOrderNumLU);
            
            j = 0;
                //Check Set
            k = pLUShcemasDscRec->pInputDscData[0].shOrderNumLU;
            l = arShLssOffsets[k ]  ;
            rl_Val = arChIntermediaResult[l+ (pLUShcemasDscRec->pInputDscData[0].shIndexOut)];
            if (rl_Val == 1) {

                j = pLUShcemasDscRec->chOrderNumLU;
                chQTrg = 1;
            }
            //Check Clr
            k = pLUShcemasDscRec->pInputDscData[1].shOrderNumLU;
            l = arShLssOffsets[k];
            rl_Val = arChIntermediaResult[l+(pLUShcemasDscRec->pInputDscData[1].shIndexOut)];
            if (rl_Val == 1) {

                if(j == pLUShcemasDscRec->chOrderNumLU) {
                    chErrorQTrg = GetStateVarchErrorQTrg(pLUShcemasDscRec->chOrderNumLU);
                    chErrorQTrg = 1; //Fix Error
                    SetStateVarchErrorQTrg(pLUShcemasDscRec->chOrderNumLU, chErrorQTrg);
                }
                chQTrg = 0;  
            }
            else {
                    //Check C
                j = 0;
                k = pLUShcemasDscRec->pInputDscData[3].shOrderNumLU;
                l = arShLssOffsets[k];
                lIdxInC = arShLssOffsets[k]+(pLUShcemasDscRec->pInputDscData[3].shIndexOut);
                chInC = GetStateVarchInC(pLUShcemasDscRec->chOrderNumLU);
                if ((arChIntermediaResult[lIdxInC] > 0) && (chInC ==0 ) ){
                //Check D
                k = pLUShcemasDscRec->pInputDscData[2].shOrderNumLU;        
                chQTrg = arChIntermediaResult[l+(pLUShcemasDscRec->pInputDscData[2].shIndexOut)];  
                }
            }
            l = k = pLUShcemasDscRec->chOrderNumLU;
            i = arShLssOffsets[k];
            arChIntermediaResult[i] = chQTrg;
            arChIntermediaResult[i + 1] = !chQTrg;
            k = pLUShcemasDscRec->pInputDscData[3].shOrderNumLU;
            lIdxInC = arShLssOffsets[k]+(pLUShcemasDscRec->pInputDscData[3].shIndexOut);
            chInC = arChIntermediaResult[lIdxInC];
            
            SetStateVarchQTrg(l,chQTrg);
            SetStateVarchInC(l,chInC);
            
          }while(false);
            shCounterProcessedRec++;
            break;
        case LU_GEN_OP_DELAY1:
            do{
            LUShcemasInDataDsc const *pLUShcemasInDataDsc;
            rl_Val = 0;
            pLUShcemasInDataDsc = pLUShcemasDscRec->pInputDscData;
            i = pLUShcemasInDataDsc[0].shOrderNumLU;
            l = arShLssOffsets[i];
            i = l + pLUShcemasInDataDsc[0].shIndexOut;
            rl_Val = arChIntermediaResult[i];
            rl_Val = TCs(rl_Val);
            k = pLUShcemasDscRec->chOrderNumLU;
            l = arShLssOffsets[k]; //shCounterProcessedRec must be LED_SCHEMATIC_LU_ORDER_NUMS
            arChIntermediaResult[l] = rl_Val;
            }while(false);
            shCounterProcessedRec++;
            break;
        case LU_GEN_OP_PULSE:
            do{
            LUShcemasInDataDsc const *pLUShcemasInDataDsc;
            rl_Val = 0;
            pLUShcemasInDataDsc = pLUShcemasDscRec->pInputDscData;
            i = pLUShcemasInDataDsc[0].shOrderNumLU;
            l = arShLssOffsets[i];
            i = l + pLUShcemasInDataDsc[0].shIndexOut;
            rl_Val = arChIntermediaResult[i];
            j = 0;//
            k = pLUShcemasDscRec->chOrderNumLU;
            if (k == LSS_DELAY_05_1_1) {
                rl_Val = T1_1Ms(rl_Val);
            } else if (k == LSS_DELAY_06_1_1) {
                rl_Val = T1_2Ms(rl_Val);
            }
            k = pLUShcemasDscRec->chOrderNumLU;
            l = arShLssOffsets[k]; //shCounterProcessedRec must be LED_SCHEMATIC_LU_ORDER_NUMS
            arChIntermediaResult[l] = rl_Val;
            }while(false);
            shCounterProcessedRec++;
            break;
            
        default:
            ;
        } //switch    
    } while (shCounterProcessedRec < IN_SIMPLE_SELECTOR);//IN_LSS_VCC
i = arChIntermediaResult[ OFFSET_OUT_OUT_LSS_ALARM    ] = 
arChIntermediaResult[OFFSET_OUT_LSS_OR_27__2_1];//

j = arChIntermediaResult[ OFFSET_OUT_OUT_LSS_MUTE     ] = 
arChIntermediaResult[OFFSET_OUT_LSS_OR_28__2_1];// 
   
   
 this->arrOut [LSS_OUT_NAME_ALARM -1] = i;//arChIntermediaResult[OFFSET_OUT_LSS_OR_27__2_1];       
 this->arrOut [LSS_OUT_NAME_MUTE  -1] = j;//arChIntermediaResult[OFFSET_OUT_LSS_OR_28__2_1];      
 
register __LN_ALARM *p__LN_ALARM =  static_cast<__LN_ALARM*>(pvCfgLN);
   //volatile bool boolchQTrg29 = chQTrg29,boolchQTrg11 = m_chQTrg11;
    p__LN_ALARM->active_state[(ALARM_OUT_ALARM/8) ] = (static_cast<bool>(i))<<(ALARM_OUT_ALARM%8);
    p__LN_ALARM->active_state[(ALARM_OUT_MUTE/8) ]  = (static_cast<bool>(j))<<(ALARM_OUT_MUTE%8) ;
    
    if(boolchQTrg29 != static_cast<bool>(m_chQTrg29) ){
    p__LN_ALARM->d_trigger_state[ALARM_D_TRIGGER_1/8] = (static_cast<bool>(m_chQTrg29))<<(ALARM_D_TRIGGER_1%8);
    chGlb_ActivatorWREeprom++;
    }
    if(boolchQTrg11 != static_cast<bool>(m_chQTrg11) ){
    p__LN_ALARM->d_trigger_state[ALARM_D_TRIGGER_2/8] = (static_cast<bool>(m_chQTrg11))<<(ALARM_D_TRIGGER_2%8);
    chGlb_ActivatorWREeprom++;
    }
    
}




typedef union U8_state_Unn{ 
   struct {
      unsigned int bt0 : 1; //1
      unsigned int bt1 : 1; //2
      unsigned int bt2 : 1; //3
      unsigned int bt3 : 1; //4
      unsigned int bt4 : 1; //5
      unsigned int bt5 : 1; //6
      unsigned int bt6 : 1; //7
      unsigned int bt7 : 1; //8
    } bool_val;
    unsigned char U8V;
} U8_state_wrp; 




//=====================================================================================================
//''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
//                  
//....................................................................................................
//=====================================================================================================
void CLULss::CalcLssSchematicOptManual(void){
    // ----------------    -------------------------
//.register long rl_Val,i;
//.const LedShcemasDscRecord* pLUShcemasDscRec;// 
//.#pragma data_alignment=4
//.char arChIntermediaResult[(TOTAL_LSS_LU_CALC_POINT)];
//.volatile bool boolchQTrg29 = m_chQTrg29,boolchQTrg11 = m_chQTrg11;
//..register unsigned long u32_bit_holder = 0;  

//..register union {
    union
    {
      struct
      {
            unsigned int LSS_NORMAL : 1;
            unsigned int LSS_TRIGGER : 1;
            unsigned int LSS_TIMELIMITED : 1;
            unsigned int LSS_LSSIN1 : 1;
            unsigned int LSS_MUTE_I : 1;
            unsigned int LSS_RESET_I : 1;
            unsigned int LSS_BLOCK_I : 1;
            unsigned int LSS_D_TRG_11__4_2_Q : 1;
            unsigned int LSS_D_TRG_11__4_2_NOT_Q : 1;
            unsigned int LSS_D_TRG_29__4_2_Q : 1;
            unsigned int LSS_D_TRG_29__4_2_NOT_Q : 1;
            unsigned int IN_LSS_VCC : 1;
            unsigned int IN_LSS_GROUND : 1;

      } bool_vars;
      long lVl;
    } wrp;

    wrp.lVl = 0;
    long lV; unsigned long rU;
        
    rU = 0;
    U8_state_wrp stt_LULss_Not01__1_1,
        stt_LULss_And02__3_1,
        stt_LULss_And03__3_1,
        stt_LULss_And04__3_1,
        stt_LULss_Not05__1_1,
        stt_LULss_And06__2_1,
        stt_LULss_And07__2_1,
        stt_LULss_And08__3_1,
        stt_LULss_Not09__1_1,
        stt_LULss_Not10__1_1,
        stt_LULss_Or_11__3_1,
        stt_LULss_Or_12__3_1,

        stt_LULss_DT_13__4_2,
        stt_LULss_Or_14__2_1,
        stt_LULss_DT_15__4_2,
        stt_LULss_Not16__1_1,
        stt_LULss_And17__3_1,
        stt_LULss_Or_18__3_1,
        stt_LULss_Or_19__2_1,
        
        stt_LULss_Not20__1_1,
        stt_LULss_And21__4_1,
        stt_LULss_And22__4_1,
        stt_LULss_And23__4_1,
        stt_LULss_And24__4_1,
        stt_LULss_Or_25__2_1,
        stt_LULss_Or_26__2_1,
        stt_LULss_T_IMP_27__1_1,
        stt_LULss_T_IMP_28__1_1,
        stt_LULss_T_T_0_29__1_1,
        stt_LULss_T_0_T_add1ms_29__1_1;
        // @TIMER_T_0,
        // @_TIMER_0_T
        // @_TIMER_IMPULSE;
stt_LULss_Not01__1_1.U8V = rU,
        stt_LULss_And02__3_1.U8V = rU,
        stt_LULss_And03__3_1.U8V = rU,
        stt_LULss_And04__3_1.U8V = rU,
        stt_LULss_Not05__1_1.U8V = rU,
        stt_LULss_And06__2_1.U8V = rU,
        stt_LULss_And07__2_1.U8V = rU,
        stt_LULss_And08__3_1.U8V = rU,
        stt_LULss_Not09__1_1.U8V = rU,
        stt_LULss_Not10__1_1.U8V = rU,
        stt_LULss_Or_11__3_1.U8V = rU,
        stt_LULss_Or_12__3_1.U8V = rU,

        stt_LULss_DT_13__4_2.U8V = rU,
        stt_LULss_Or_14__2_1.U8V = rU,
        stt_LULss_DT_15__4_2.U8V = rU,
        stt_LULss_Not16__1_1.U8V = rU,
        stt_LULss_And17__3_1.U8V = rU,
        stt_LULss_Or_18__3_1.U8V = rU,
        stt_LULss_Or_19__2_1.U8V = rU,
        
        stt_LULss_Not20__1_1.U8V = rU,
        stt_LULss_And21__4_1.U8V = rU,
        stt_LULss_And22__4_1.U8V = rU,
        stt_LULss_And23__4_1.U8V = rU,
        stt_LULss_And24__4_1.U8V = rU,
        stt_LULss_Or_25__2_1.U8V = rU,
        stt_LULss_Or_26__2_1.U8V = rU,
        stt_LULss_T_IMP_27__1_1.U8V = rU,
        stt_LULss_T_IMP_28__1_1.U8V = rU,
        stt_LULss_T_T_0_29__1_1.U8V = rU,
        stt_LULss_T_0_T_add1ms_29__1_1.U8V = rU;

    if (m_LssCfgSuit.chSel == LSS_MODE_SIMPLE)
      wrp.bool_vars.LSS_NORMAL = 1;//arChIntermediaResult[OFFSET_OUT_IN_LSS_NORMAL] = 1; //
    else if (m_LssCfgSuit.chSel == LSS_MODE_TRIGGER)
      wrp.bool_vars.LSS_TRIGGER = 1;//arChIntermediaResult[OFFSET_OUT_IN_LSS_TRIGGER] = 1; //
    else if (m_LssCfgSuit.chSel == LSS_MODE_PERIOD)
      wrp.bool_vars.LSS_TIMELIMITED = 1;//arChIntermediaResult[OFFSET_OUT_IN_LSS_TIMELIMITED] = 1;
   
    wrp.bool_vars.IN_LSS_VCC = 1;

    wrp.bool_vars.LSS_D_TRG_11__4_2_Q = m_chQTrg11;            // arChIntermediaResult[ OFFSET_OUT_LSS_D_TRG_11__4_2    ] = m_chQTrg11;
    rU = m_chQTrg11;
    wrp.bool_vars.LSS_D_TRG_11__4_2_NOT_Q = (~rU) & 1; // arChIntermediaResult[ OFFSET_OUT_LSS_D_TRG_11__4_2 + 1  ] = !m_chQTrg11;
stt_LULss_DT_15__4_2.bool_val.bt6 = wrp.bool_vars.LSS_D_TRG_11__4_2_NOT_Q;
stt_LULss_DT_15__4_2.bool_val.bt7 = wrp.bool_vars.LSS_D_TRG_11__4_2_Q;
    rU = m_chQTrg29;
    wrp.bool_vars.LSS_D_TRG_29__4_2_Q = rU;            // arChIntermediaResult[ OFFSET_OUT_LSS_D_TRG_29__4_2    ] = m_chQTrg29;
    wrp.bool_vars.LSS_D_TRG_29__4_2_NOT_Q = (~rU) & 1; // arChIntermediaResult[ OFFSET_OUT_LSS_D_TRG_29__4_2 + 1  ] = !m_chQTrg29;
stt_LULss_DT_13__4_2.bool_val.bt6 = wrp.bool_vars.LSS_D_TRG_29__4_2_NOT_Q;
stt_LULss_DT_13__4_2.bool_val.bt7 = wrp.bool_vars.LSS_D_TRG_29__4_2_Q;

    char *pCh = (this->arrPchIn[(LSS_IN_NAME__LSSIN1 - 1)]);
    wrp.bool_vars.LSS_LSSIN1 = pCh[0]; // arChIntermediaResult[OFFSET_OUT_IN_LSS_LSSIN1 ]
    pCh = (this->arrPchIn[(LSS_IN_NAME__MUTE_I - 1)]);
    wrp.bool_vars.LSS_MUTE_I = pCh[0]; // arChIntermediaResult[OFFSET_OUT_IN_LSS_MUTE_I ]
    pCh = (this->arrPchIn[(LSS_IN_NAME__RESET_I - 1)]);
    wrp.bool_vars.LSS_RESET_I = pCh[0]; // arChIntermediaResult[OFFSET_OUT_IN_LSS_RESET_I]
    pCh = (this->arrPchIn[(LSS_IN_NAME__BLOCK_I - 1)]);
    wrp.bool_vars.LSS_BLOCK_I = pCh[0]; // arChIntermediaResult[OFFSET_OUT_IN_LSS_BLOCK_I]

    // wrp.bool_vars.

    stt_LULss_Or_14__2_1.bool_val.bt0 = wrp.bool_vars.LSS_TRIGGER;
    stt_LULss_Or_14__2_1.bool_val.bt1 = wrp.bool_vars.LSS_TIMELIMITED;
    if((stt_LULss_Or_14__2_1.U8V &3) != 0){
        stt_LULss_Or_14__2_1.bool_val.bt7 = 1;
    }
    stt_LULss_And04__3_1.bool_val.bt0 = wrp.bool_vars.LSS_LSSIN1;
    stt_LULss_And04__3_1.bool_val.bt1 = wrp.bool_vars.LSS_NORMAL;
    stt_LULss_And04__3_1.bool_val.bt2 = wrp.bool_vars.LSS_MUTE_I;
    
    if((stt_LULss_And04__3_1.U8V &7) == 7){
        stt_LULss_And04__3_1.bool_val.bt7 = 1;
    } 
    rU = wrp.bool_vars.LSS_LSSIN1;
    stt_LULss_Not05__1_1.bool_val.bt7 = (~rU)&1;
    stt_LULss_Not09__1_1.bool_val.bt7 = (~rU)&1;
    stt_LULss_Not20__1_1.bool_val.bt7 = (~static_cast<unsigned int>(wrp.bool_vars.LSS_BLOCK_I))&1;

    stt_LULss_T_IMP_27__1_1.bool_val.bt0 = rU;
    lV = T1_1Ms(rU);
    //..dbg if(lV != 0){
    //..dbg asm(
    //..dbg             "bkpt 1"
    //..dbg );
    //..dbg }
    stt_LULss_T_IMP_27__1_1.bool_val.bt7 = lV;

    stt_LULss_And06__2_1.bool_val.bt0 = stt_LULss_Not05__1_1.bool_val.bt7;
    stt_LULss_And06__2_1.bool_val.bt1 = wrp.bool_vars.LSS_NORMAL;
    if((stt_LULss_And06__2_1.U8V &3) == 3){
        stt_LULss_And06__2_1.bool_val.bt7 = 1;
    } 
    rU = stt_LULss_T_IMP_27__1_1.bool_val.bt7;
    stt_LULss_Not16__1_1.bool_val.bt1 = rU;
    stt_LULss_Not16__1_1.bool_val.bt7 = (~rU)&1;

    stt_LULss_And07__2_1.bool_val.bt0 = rU;
    stt_LULss_And07__2_1.bool_val.bt1 = stt_LULss_Or_14__2_1.bool_val.bt7;
    if((stt_LULss_And07__2_1.U8V &3) == 3){
        stt_LULss_And07__2_1.bool_val.bt7 = 1;
    }
    stt_LULss_And17__3_1.bool_val.bt0 = wrp.bool_vars.LSS_D_TRG_11__4_2_Q;
    stt_LULss_And17__3_1.bool_val.bt1 = stt_LULss_Not16__1_1.bool_val.bt7;
    stt_LULss_And17__3_1.bool_val.bt2 = wrp.bool_vars.LSS_TIMELIMITED;
    if(( stt_LULss_And17__3_1.U8V &7) == 7){
         stt_LULss_And17__3_1.bool_val.bt7 = 1;
    } 

    rU = stt_LULss_And17__3_1.bool_val.bt7;
    stt_LULss_T_T_0_29__1_1.bool_val.bt0 = rU;
    lV = TCs(rU);//
    //.dbg-..if(lV != 0){
    //.dbg-..asm(
    //.dbg-..            "bkpt 1"
    //.dbg-..);
    //.dbg-..}
    stt_LULss_T_T_0_29__1_1.bool_val.bt1 = lV;
    //rU = lV;
    lV = T1_3Ms(stt_LULss_T_T_0_29__1_1.bool_val.bt1);//!@lV = T1_3Ms(rU);
    //.dbg-..if(lV != 0){
    //.dbg-..asm(
    //.dbg-..            "bkpt 1"
    //.dbg-..);
    //.dbg-..}
    stt_LULss_T_0_T_add1ms_29__1_1.bool_val.bt7 =  lV;

    stt_LULss_Or_18__3_1.bool_val.bt0 = stt_LULss_T_0_T_add1ms_29__1_1.bool_val.bt7;
    stt_LULss_Or_18__3_1.bool_val.bt1 = wrp.bool_vars.LSS_NORMAL;
    stt_LULss_Or_18__3_1.bool_val.bt2 = wrp.bool_vars.LSS_RESET_I;
    if((stt_LULss_Or_18__3_1.U8V &7) != 0){
        stt_LULss_Or_18__3_1.bool_val.bt7 = 1;
        //
    }

    stt_LULss_DT_15__4_2.bool_val.bt3 = wrp.bool_vars.IN_LSS_GROUND;
    stt_LULss_DT_15__4_2.bool_val.bt2 = wrp.bool_vars.IN_LSS_VCC;//!??
    stt_LULss_DT_15__4_2.bool_val.bt7 = static_cast<unsigned>(m_chQTrg11);

    //..rU = stt_LULss_T_IMP_27__1_1.bool_val.bt7;
    //?..stt_LULss_DT_15__4_2.bool_val.bt1 = stt_LULss_Or_18__3_1.bool_val.bt7;//!??
      //0- clr Should be                 @/NOW USE \@      0 - SYNCRO
      //1- D input                       @/NOW USE \@      1 CLR INPUT
      //2- C                             @/NOW USE \@      2 - D-INPUT
      //3 -SET inp                       @/NOW USE \@      3 SET -Input
      //5 - Q                            @/NOW USE \@      7 -Q
      //6 -q^                            @/NOW USE \@      6 -Q^

    //..if ( (stt_LULss_DT_15__4_2.U8V&3) == 0x0A)
    //..    m_chErrorQTrg11 = stt_LULss_DT_15__4_2.U8V;//!? Erroneus combination
      // RESET BLOCK
    if (stt_LULss_Or_18__3_1.bool_val.bt7 == 1)
    {                                     // dbg code(mean->).bt1 == 1 CLR INPUT
      stt_LULss_DT_15__4_2.U8V = 0;     //
      stt_LULss_DT_15__4_2.bool_val.bt6 = 1; // Q^
      stt_LULss_DT_15__4_2.bool_val.bt1 = 1; // Clr Inp
    }
    else
    {
      // SET BLOCK
      // if(){}
      // else{ D-INPUT C--INPUT BLOCK
      //?.bt0 - SYNCRO      .bt2 - D-INPUT
      
      if (
          (m_chInC11 == 0) //previous state  SYNCRO
          && (stt_LULss_T_IMP_27__1_1.bool_val.bt7 == 1) //current state SYNCRO
          && (stt_LULss_DT_15__4_2.bool_val.bt1 == 0)  // Clr Inp
        )
      {
            stt_LULss_DT_15__4_2.U8V &= (1 << 7) | (1 << 6);
            rU = wrp.bool_vars.IN_LSS_VCC;
            //?stt_LULss_DT_15__4_2.bool_val.bt2 = rU;// D-INPUT
            stt_LULss_DT_15__4_2.bool_val.bt7 = rU;          // Q
            //???stt_LULss_DT_15__4_2.bool_val.bt2 = wrp.bool_vars.IN_LSS_VCC;
             // Q^
            //.dbg-..if(rU != 0){
            //.dbg-..asm(
            //.dbg-..            "bkpt 1"
            //.dbg-..);
            //.dbg-..}
       }       
 
      stt_LULss_DT_15__4_2.bool_val.bt2 = wrp.bool_vars.IN_LSS_VCC; // D-INPUT  
      stt_LULss_DT_15__4_2.bool_val.bt1 = 0;                     // Clr    wrp.bool_vars.IN_LSS_GROUND
    }
    stt_LULss_DT_15__4_2.bool_val.bt0 = stt_LULss_T_IMP_27__1_1.bool_val.bt7;// C <- current state SYNCRO
    m_chInC11 = stt_LULss_DT_15__4_2.bool_val.bt0;
    rU = stt_LULss_DT_15__4_2.bool_val.bt7 ;// Q^
    m_chQTrg11= rU;
     stt_LULss_DT_15__4_2.bool_val.bt6 = (~(rU))&1;  
    //? rU = stt_LULss_DT_15__4_2.bool_val.bt7;
    stt_LULss_Not01__1_1.bool_val.bt0 = rU;
    stt_LULss_Not01__1_1.bool_val.bt7 = (~rU)&1;

    stt_LULss_And03__3_1.bool_val.bt0 = rU;//..stt_LULss_DT_15__4_2.bool_val.bt7;
    stt_LULss_And03__3_1.bool_val.bt1 = stt_LULss_Or_14__2_1.bool_val.bt7;
    stt_LULss_And03__3_1.bool_val.bt2 = wrp.bool_vars.LSS_MUTE_I;
    if(( stt_LULss_And03__3_1.U8V &7) == 7){
         stt_LULss_And03__3_1.bool_val.bt7 = 1;
    } 
    //.. rU = stt_LULss_DT_15__4_2.bool_val.bt7;
    stt_LULss_Not10__1_1.bool_val.bt0 = rU;
    stt_LULss_Not10__1_1.bool_val.bt7 = (~rU)&1;

    stt_LULss_Or_19__2_1.bool_val.bt0 = rU;//..stt_LULss_DT_15__4_2.bool_val.bt7;
    stt_LULss_Or_19__2_1.bool_val.bt1 = wrp.bool_vars.LSS_LSSIN1;
    if((stt_LULss_Or_19__2_1.U8V &3) != 0){
        stt_LULss_Or_19__2_1.bool_val.bt7 = 1;
    }


    stt_LULss_And08__3_1.bool_val.bt0 = stt_LULss_Not09__1_1.bool_val.bt7;
    stt_LULss_And08__3_1.bool_val.bt1 = stt_LULss_Not10__1_1.bool_val.bt7;
    stt_LULss_And08__3_1.bool_val.bt2 = stt_LULss_Or_14__2_1.bool_val.bt7;
    if(( stt_LULss_And08__3_1.U8V &7) == 7){
         stt_LULss_And08__3_1.bool_val.bt7 = 1;
    } 

    rU = stt_LULss_Not01__1_1.bool_val.bt7;
    stt_LULss_T_IMP_28__1_1.bool_val.bt0 = rU;
    lV = T1_2Ms(rU);
    //.dbg-.. if(lV != 0){
    //.dbg-.. asm(
    //.dbg-..             "bkpt 1"
    //.dbg-.. );
    //.dbg-.. }
    stt_LULss_T_IMP_28__1_1.bool_val.bt7 = lV;


    stt_LULss_Or_12__3_1.bool_val.bt0 = stt_LULss_And06__2_1.bool_val.bt7;
    stt_LULss_Or_12__3_1.bool_val.bt1 = stt_LULss_And07__2_1.bool_val.bt7;
    stt_LULss_Or_12__3_1.bool_val.bt2 = stt_LULss_And08__3_1.bool_val.bt7;
    if((stt_LULss_Or_12__3_1.U8V &7) != 0){
        stt_LULss_Or_12__3_1.bool_val.bt7 = 1;
        //
    }

    stt_LULss_And02__3_1.bool_val.bt0 = stt_LULss_T_IMP_28__1_1.bool_val.bt7;
    stt_LULss_And02__3_1.bool_val.bt1 = stt_LULss_Or_14__2_1.bool_val.bt7;
    stt_LULss_And02__3_1.bool_val.bt2 = wrp.bool_vars.LSS_LSSIN1;
    if(( stt_LULss_And02__3_1.U8V &7) == 7){
         stt_LULss_And02__3_1.bool_val.bt7 = 1;
    } 


    stt_LULss_Or_11__3_1.bool_val.bt0 = stt_LULss_And02__3_1.bool_val.bt7;
    stt_LULss_Or_11__3_1.bool_val.bt1 = stt_LULss_And03__3_1.bool_val.bt7;
    stt_LULss_Or_11__3_1.bool_val.bt2 = stt_LULss_And04__3_1.bool_val.bt7;
    if((stt_LULss_Or_11__3_1.U8V &7) != 0){
        stt_LULss_Or_11__3_1.bool_val.bt7 = 1;
        //
    }
    
//stt_LULss_DT_13__4_2
    stt_LULss_DT_13__4_2.bool_val.bt3 = wrp.bool_vars.IN_LSS_GROUND;

    stt_LULss_DT_13__4_2.bool_val.bt2 = wrp.bool_vars.IN_LSS_VCC;//!??
    stt_LULss_DT_13__4_2.bool_val.bt7 = wrp.bool_vars.LSS_D_TRG_29__4_2_Q;//static_cast<unsigned>(m_chQTrg29)
    //stt_LULss_DT_13__4_2.bool_val.bt6 = wrp.bool_vars.LSS_D_TRG_29__4_2_NOT_Q
    //
      //0- clr Should be                 @/NOW USE \@      0 - SYNCRO
      //1- D input                       @/NOW USE \@      1 CLR INPUT
      //2- C                             @/NOW USE \@      2 - D-INPUT
      //3 -SET inp                       @/NOW USE \@      3 SET -Input
      //5 - Q                            @/NOW USE \@      7 -Q
      //6 -q^                            @/NOW USE \@      6 -Q^

      // RESET BLOCK
    if (stt_LULss_Or_12__3_1.bool_val.bt7 == 1)
    {                                     // dbg code(mean->).bt1 == 1 CLR INPUT
      stt_LULss_DT_13__4_2.U8V = 0;     //
      stt_LULss_DT_13__4_2.bool_val.bt6 = 1; // Q^
      stt_LULss_DT_13__4_2.bool_val.bt1 = 1; // Clr Inp
    }
    else
    {
      // SET BLOCK
      // if(){}
      // else{ D-INPUT C--INPUT BLOCK
      //?.bt0 - SYNCRO      .bt2 - D-INPUT
      if (
          (m_chInC29 == 0) //previous state  SYNCRO
          && (stt_LULss_Or_11__3_1.bool_val.bt7 == 1) //current state SYNCRO
          && (stt_LULss_DT_13__4_2.bool_val.bt1 == 0)  // Clr Inp
        )
      {
            stt_LULss_DT_13__4_2.U8V &= (1 << 7) | (1 << 6);
            rU = wrp.bool_vars.IN_LSS_VCC;
            stt_LULss_DT_13__4_2.bool_val.bt2 = rU;
            stt_LULss_DT_13__4_2.bool_val.bt7 = rU;          // Q
            //???stt_LULss_DT_13__4_2.bool_val.bt2 = wrp.bool_vars.IN_LSS_VCC;
            stt_LULss_DT_13__4_2.bool_val.bt6 = (~rU)&1; // Q^
             //.dbg-..  if(rU != 0){
             //.dbg-..  asm(
             //.dbg-..              "bkpt 1"
             //.dbg-..  );
             //.dbg-..  }
      }           
 
      stt_LULss_DT_13__4_2.bool_val.bt2 = wrp.bool_vars.IN_LSS_VCC; // D
      stt_LULss_DT_13__4_2.bool_val.bt1 = 0;                     // Clr    wrp.bool_vars.IN_LSS_GROUND
    }
    rU = stt_LULss_Or_11__3_1.bool_val.bt7;
    m_chInC29 =  rU;
    stt_LULss_DT_13__4_2.bool_val.bt0 =  rU;// C <- current state SYNCRO
    rU = stt_LULss_DT_13__4_2.bool_val.bt7;
    m_chQTrg29 = rU;// 
    stt_LULss_DT_13__4_2.bool_val.bt6 = (~(rU))&1;

    stt_LULss_And21__4_1.bool_val.bt0 = wrp.bool_vars.LSS_NORMAL;
    stt_LULss_And21__4_1.bool_val.bt1 = wrp.bool_vars.LSS_LSSIN1;
    stt_LULss_And21__4_1.bool_val.bt2 = stt_LULss_Not20__1_1.bool_val.bt7;
    stt_LULss_And21__4_1.bool_val.bt3 = stt_LULss_DT_13__4_2.bool_val.bt6;
    if(( stt_LULss_And21__4_1.U8V &15) == 15){
         stt_LULss_And21__4_1.bool_val.bt7 = 1;
    } 

    stt_LULss_And22__4_1.bool_val.bt0 = wrp.bool_vars.LSS_NORMAL;
    stt_LULss_And22__4_1.bool_val.bt1 = wrp.bool_vars.LSS_LSSIN1;
    stt_LULss_And22__4_1.bool_val.bt2 = stt_LULss_Not20__1_1.bool_val.bt7;
    stt_LULss_And22__4_1.bool_val.bt3 = stt_LULss_DT_13__4_2.bool_val.bt7;
    if(( stt_LULss_And22__4_1.U8V &15) == 15){
         stt_LULss_And22__4_1.bool_val.bt7 = 1;
    } 


    stt_LULss_And23__4_1.bool_val.bt0 = stt_LULss_Or_14__2_1.bool_val.bt7;
    stt_LULss_And23__4_1.bool_val.bt1 = stt_LULss_DT_15__4_2.bool_val.bt7;
    stt_LULss_And23__4_1.bool_val.bt2 = stt_LULss_Not20__1_1.bool_val.bt7;
    stt_LULss_And23__4_1.bool_val.bt3 = stt_LULss_DT_13__4_2.bool_val.bt6;
    if(( stt_LULss_And23__4_1.U8V &15) == 15){
         stt_LULss_And23__4_1.bool_val.bt7 = 1;
    } 


    stt_LULss_And24__4_1.bool_val.bt0 = stt_LULss_Or_14__2_1.bool_val.bt7;
    stt_LULss_And24__4_1.bool_val.bt1 = stt_LULss_Or_19__2_1.bool_val.bt7;
    stt_LULss_And24__4_1.bool_val.bt2 = stt_LULss_Not20__1_1.bool_val.bt7;
    stt_LULss_And24__4_1.bool_val.bt3 = stt_LULss_DT_13__4_2.bool_val.bt7;
    if(( stt_LULss_And24__4_1.U8V &15) == 15){
         stt_LULss_And24__4_1.bool_val.bt7 = 1;
    } 

    stt_LULss_Or_25__2_1.bool_val.bt0 = stt_LULss_And21__4_1.bool_val.bt7;
    stt_LULss_Or_25__2_1.bool_val.bt1 = stt_LULss_And23__4_1.bool_val.bt7;
    if((stt_LULss_Or_25__2_1.U8V &3) != 0){
        stt_LULss_Or_25__2_1.bool_val.bt7 = 1;
    }

    stt_LULss_Or_26__2_1.bool_val.bt0 = stt_LULss_And22__4_1.bool_val.bt7;
    stt_LULss_Or_26__2_1.bool_val.bt1 = stt_LULss_And24__4_1.bool_val.bt7;
    if((stt_LULss_Or_26__2_1.U8V &3) != 0){
        stt_LULss_Or_26__2_1.bool_val.bt7 = 1;
    }
//
 
 







     
    lV = stt_LULss_Or_25__2_1.bool_val.bt7;
    rU = stt_LULss_Or_26__2_1.bool_val.bt7; 
   


 this->arrOut [LSS_OUT_NAME_ALARM -1] = lV;//arChIntermediaResult[OFFSET_OUT_LSS_OR_27__2_1];       
 this->arrOut [LSS_OUT_NAME_MUTE  -1] = rU;//arChIntermediaResult[OFFSET_OUT_LSS_OR_28__2_1];      
 
register __LN_ALARM *p__LN_ALARM =  static_cast<__LN_ALARM*>(pvCfgLN);
   //volatile bool boolchQTrg29 = chQTrg29,boolchQTrg11 = m_chQTrg11;
    p__LN_ALARM->active_state[(ALARM_OUT_ALARM/8) ] = (static_cast<bool>(lV))<<(ALARM_OUT_ALARM%8);
    p__LN_ALARM->active_state[(ALARM_OUT_MUTE/8) ]  = (static_cast<bool>(rU))<<(ALARM_OUT_MUTE%8) ;
    
    //?if(boolchQTrg29 != static_cast<bool>(m_chQTrg29) ){
    if(wrp.bool_vars.LSS_D_TRG_29__4_2_Q != (m_chQTrg29) ){
    p__LN_ALARM->d_trigger_state[ALARM_D_TRIGGER_1/8] = (static_cast<bool>(m_chQTrg29))<<(ALARM_D_TRIGGER_1%8);
    chGlb_ActivatorWREeprom++;
    }
    //?if(boolchQTrg11 != static_cast<bool>(m_chQTrg11) ){
    if(wrp.bool_vars.LSS_D_TRG_11__4_2_Q != (m_chQTrg11) ){
    p__LN_ALARM->d_trigger_state[ALARM_D_TRIGGER_2/8] = (static_cast<bool>(m_chQTrg11))<<(ALARM_D_TRIGGER_2%8);
    chGlb_ActivatorWREeprom++;
    }
















    
}
//
//--------------------------------------------------------------------------------------------------------
//````````````````````````````````````````````````````````````````````````````````````````````````````````





char chGBL_BP_StopLss = 0;
void LssOp	(void *pObj){
CLULss& rCLULss = *(static_cast<CLULss*>(pObj));
if(chGBL_BP_StopLss == rCLULss.shShemasOrdNumStng){
    asm(
                "bkpt 1"
                );
 //rCLULss.CalcLssSchematicOpt();//
 rCLULss.CalcLssSchematicOptManual();//
 return;
}
 rCLULss.CalcLssSchematicOptManual();//
}





