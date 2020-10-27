
#include "LUBGS.hpp"
#include "../inc/constants.h"
#include <stdio.h>
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
#include "FixblWrp.hpp"


volatile unsigned long measurement_DBG[10] = {
0,0,0,0,90000,0,0,0,0,0,
};
unsigned long *PMeas = const_cast<unsigned long*>(&measurement_DBG[0]);

#ifdef DEBUG_MODE
BGSigDbgRecord  ArrBGSigDbgRec[AMOIUNT_DBG_REC] @ "variables_RAM1";
#endif

unsigned int uiIdxArrBGSigDbgRec = 0;
CBGSig::CBGSig(void):CLUBase()  {
m_NodeTWait.lTmrVal  = 0;
m_NodeTWait.next     = 0;
m_NodeTReset.lTmrVal = 0;
m_NodeTReset.next    = 0;
m_NodeTElongation.lTmrVal = 0;
m_NodeTElongation.next    = 0;
m_NodeTImp6ms.lTmrVal = 0;
m_NodeTImp6ms.next    = 0;
m_NodeTImpNNP.lTmrVal = 0;
m_NodeTImpNNP.next    = 0;
m_NodeTImpNNM.lTmrVal = 0;
m_NodeTImpNNM.next    = 0;
m_BGSigSuit.chStateGS  = 0;
m_BGSigSuit.chCheckBgs = 0;
m_BGSigSuit.lTWait     = 0;

m_BGSigSuit.chStateGS  = 0;
m_BGSigSuit.chCheckBgs = 0;
m_BGSigSuit.lTWait     = 0;
//m_BGSigSuit.lTReset    = 0;
m_chLinkedTimers = 0; //Field bit
m_chStateTWait   = 0;
m_chStateTReset  = 0;
m_lIfix = m_lMeasIti_mn_1 = 0;
m_chNumberAnalogChanell = 0;
}

CBGSig::~CBGSig(void) {
}

CBGSig::CBGSig(char chM,char chI){
    chMaxIteratoin = chM;
    chIteration = chI;
    
chNumInput  = static_cast<char>(TOTAL_BGS_VISIO_IN);//
chNumOutput = static_cast<char>(TOTAL_BGS_VISIO_OUT);
memset(static_cast<void*>(arrPchIn),0xcc,sizeof(char*)*TOTAL_BGS_VISIO_IN);
memset(static_cast<void*>(arrOut),0,sizeof(char  )*TOTAL_BGS_VISIO_OUT);
memset(static_cast<void*>(&m_BGSigSuit),0,sizeof(BGSigSuit));
m_NodeTWait.lTmrVal  = 0;
m_NodeTWait.next     = 0;
m_NodeTReset.lTmrVal = 0;
m_NodeTReset.next    = 0;
m_NodeTElongation.lTmrVal = 0;
m_NodeTElongation.next    = 0;
m_NodeTImp6ms.lTmrVal = 0;
m_NodeTImp6ms.next    = 0;
m_NodeTImpNNP.lTmrVal = 0;
m_NodeTImpNNP.next    = 0;
m_NodeTImpNNM.lTmrVal = 0;
m_NodeTImpNNM.next    = 0;
m_BGSigSuit.chStateGS  = 0;
m_BGSigSuit.chCheckBgs = 0;
m_BGSigSuit.lTWait     = 0;
//m_BGSigSuit.lTReset    = 0;
m_chLinkedTimers = 0; //Field bit
m_chStateTWait   = 0;
m_chStateTReset  = 0;
m_lInew = m_lIfix = m_lMeasIti_mn_1 = m_lKcDeltaIy = 0;
m_lIti =  m_lNNC = m_lNNP = m_lIp = m_lIc = 0;
m_chNumberAnalogChanell = 0;
 m_chWRIfix = 0;m_chIfixDir = 0;
 m_chWRIp   = 0;
 m_chWRIc   = 0;
 m_chWR_NNC = 0;
 m_chWR_NNP = 0;
m_chStdpCE = m_chStdpOV = 0;
m_chSttElongation = m_chStt6MsImp = 0;
m_chSttImpNNP = m_chSttImpNNM = 0;
ch_DTrg = 0;
ch_C1 = 0;
m_chDeltaIBus = chTzatrState = 0;
m_Iteration = 0;
}
 char CBGSig::m_chCounterCall = 99;
  char CBGSig::chAlreadyCalculated = 0;
    char CBGSig::chNeedTimerCalculated = 0;
       char CBGSig::chMeasUpdateInterval = 0;
 unsigned int CBGSig::meas[NUMBER_ANALOG_CANALES] = {
 0,0,0,0,0
 };
 
 unsigned int CBGSig::DMeas[NUMBER_ANALOG_CANALES] = {
 0,0,0,0,0
 };
 
unsigned int CBGSig::PickUPs [NUMBER_ANALOG_CANALES] = {
 0,0,0,0,0
 };
 
unsigned char CBGSig::ChanelsNames[NUMBER_ANALOG_CANALES] = {
 0,0,0,0,0
 };

 char CBGSig::m_chIdxGrupSamples = 0;
 unsigned int  CBGSig::measbuf[3][I_U] = {
 {0,0,0,0},
  {0,0,0,0},
   {0,0,0,0}
};
 
long CBGSig::LinkBGSigTimers(void) {
    register long i = 0;
    //Insert TpauseMft
    chGlSem++;
    this->m_chCounterCall = 99;
    if (PushTmrNode(&m_NodeTWait)) {//static_cast<void*>(
        i++;
        m_chLinkedTimers |= 2;
    }
    //Insert TdelayMft
    if (PushTmrNode(&m_NodeTReset)) {//static_cast<void*>(
        i++;
        m_chLinkedTimers |= 4;
    }
    //Insert 
    if (PushTmrNode(&m_NodeTElongation)) {
        i++;
        m_chLinkedTimers |= 8;
    }
   //Insert 
    if (PushTmrNode(&m_NodeTImp6ms)) {
        i++;
        m_chLinkedTimers |= 0x10;
    }
   //Insert 
    if (PushTmrNode(&m_NodeTImpNNP)) {
        i++;
        m_chLinkedTimers |= 0x20;
    }
   //Insert 
    if (PushTmrNode(&m_NodeTImpNNM)) {
        i++;
        m_chLinkedTimers |= 0x40;
    }

    chGlSem--;
    return i;
}

long CBGSig::lTWait(long lActivKey) {

    register long *plTmrVal = &m_NodeTWait.lTmrVal;
    if (lActivKey) {
        if (m_chStateTWait == 0) {
            lActivKey = m_BGSigSuit.lTWait;
            *plTmrVal = lActivKey;
            if (*plTmrVal != lActivKey)
                *plTmrVal = lActivKey; //Possible Clear in Int
            m_chStateTWait = 1;

        } else {
            lActivKey = *plTmrVal;
            if (lActivKey == 0) {
                return 1; //End of Interval
            }
        }
    } else {
        m_chStateTWait = 0;
        *plTmrVal = 0; //m_NodeTpause.lTmrVal = 0;
    }
    return 0;
}

long CBGSig::TClrTrg(long lActivKey) {
    register long *plTmrVal = &m_NodeTReset.lTmrVal;
    if (lActivKey) {
        if (m_chStateTReset == 0) {
            lActivKey = 1;
            *plTmrVal = lActivKey;
            if (*plTmrVal != lActivKey)
                *plTmrVal = lActivKey; //Possible Clear in Int
            m_chStateTReset = 1;

        } else {
            lActivKey = *plTmrVal;
            if (lActivKey == 0) {
                return 1; //End of Interval
            }
        }
    } else {
        m_chStateTReset = 0;
        *plTmrVal = 0; //m_NodeTpause.lTmrVal = 0;
    }
    return 0;
}

long CBGSig::TElongation( long lActivKey) {
    register long *plTmrVal = &m_NodeTElongation.lTmrVal;

    if (lActivKey) {
        lActivKey = 2;//1ms //m_MftSuit.lTdelay;
        *plTmrVal = lActivKey;
        if (*plTmrVal != lActivKey)
            *plTmrVal = lActivKey; //lResetKey == 0!
        if(m_chSttElongation >=1)
            m_chSttElongation |= 2;
        else
            m_chSttElongation = 1;//Activated
        
        return 1;
    
    } else {
        if ((m_chSttElongation & 1) !=0) {//Activated
            lActivKey = *plTmrVal;
            if (lActivKey != 0)
                return 1; //
            else {
                    m_chSttElongation = 0;
                    *plTmrVal = 0;
            }
        }

    }
    return 0;
}
long CBGSig::TImp6ms( long lActivKey) {
    register long *plTmrVal = &m_NodeTImp6ms.lTmrVal;
    if (lActivKey) {
        if (m_chStt6MsImp == 0) {
            lActivKey = 3;//6ms //m_MftSuit.lTWork;
            *plTmrVal = lActivKey;
            if (*plTmrVal != lActivKey)
                *plTmrVal = lActivKey;
            m_chStt6MsImp = 1;
            if(lActivKey != 0)
                return 1;
        } else {
            lActivKey = *plTmrVal;
            if (lActivKey != 0)
                return 1; //
        }
    } else {
        if (m_chStt6MsImp == 1) {//Activated
            lActivKey = *plTmrVal;
            if (lActivKey != 0)
                return 1; //
            else{
                    m_chStt6MsImp = 0;
                    *plTmrVal = 0;
            }
        }
    }
    return 0;
}
long CBGSig::TImpNNP( long lActivKey) {
    register long *plTmrVal = &m_NodeTImpNNP .lTmrVal;
    if (lActivKey) {
        if (m_chSttImpNNP == 0) {
            lActivKey = 20;//100ms //m_MftSuit.lTWork;
            *plTmrVal = lActivKey;
            if (*plTmrVal != lActivKey)
                *plTmrVal = lActivKey;
            m_chSttImpNNP = 1;
            if(lActivKey != 0)
                return 1;
        } else {
            lActivKey = *plTmrVal;
            if (lActivKey != 0)
                return 1; //
        }
    } else {
        if (m_chSttImpNNP == 1) {//Activated
            lActivKey = *plTmrVal;
            if (lActivKey != 0)
                return 1; //
            else{
                    m_chSttImpNNP = 0;
                    *plTmrVal = 0;
            }
        }
    }
    return 0;
}
long CBGSig::TImpNNM( long lActivKey) {
    register long *plTmrVal = &m_NodeTImpNNM .lTmrVal;
    if (lActivKey) {
        if (m_chSttImpNNM == 0) {
            lActivKey = 20;//100ms m_MftSuit.lTWork;
            *plTmrVal = lActivKey;
            if (*plTmrVal != lActivKey)
                *plTmrVal = lActivKey;
            m_chSttImpNNM = 1;
            if(lActivKey != 0)
                return 1;
        } else {
            lActivKey = *plTmrVal;
            if (lActivKey != 0)
                return 1; //
        }
    } else {
        if (m_chSttImpNNM == 1) {//Activated
            lActivKey = *plTmrVal;
            if (lActivKey != 0)
                return 1; //
            else{
                    m_chSttImpNNM = 0;
                    *plTmrVal = 0;
            }
        }
    }
    return 0;
}

void CBGSig::UpdateCBGSig(void) {
//Set Input parameters
pIn = static_cast<void*>(arrPchIn);
//Set OutPut parameters
pOut = static_cast<void*>(arrOut);
//LinkMftTimers();
//pInit2LcVarArea->pCLUBase->shShemasIdLUStng =  STNG_LU_NOT;

//Set Operation
//Set Type Operation
}
//long CBGSig::LinkBGSigTimers(void) {
//    register long i = 0;
//    //Insert TpauseMft
//    chGlSem++;
//    
//    if (PushTmrNode(&m_NodeTWait)) {//static_cast<void*>(
//        i++;
//        m_chLinkedTimers |= 2;
//    }
//    //Insert TdelayMft
//    if (PushTmrNode(&m_NodeTReset)) {//static_cast<void*>(
//        i++;
//        m_chLinkedTimers |= 4;
//    }
//
//    chGlSem--;
//    return i;
//}
short shIdxBeg, shIdxEnd; long lT = 777;
char shIdxBGSBkpt = 0;

void BGSig_Op(void *pObj) {
register long i;
    CBGSig& rCBGSig = *(static_cast<CBGSig*> (pObj));
    i = rCBGSig.m_chCounterCall;
    i |= rCBGSig.chAlreadyCalculated;//CLUBase::m_AuxInfo.ch;
   if(i == 0){
//       rCBGSig.m_chCounterCall = 0;
        if(rCBGSig.shLUBieldOrdNum == shIdxBGSBkpt)
   asm(
               "bkpt 1"
               );
//    rCBGSig.CalcBusGrSigSchematicDbg();
#ifdef DEBUG_MODE
      if(pObj == pvCBGSigDbg){
    
           rCBGSig.CalcBusGrSigSchematicDBG1();
            uiIdxArrBGSigDbgRec++;
            if (uiIdxArrBGSigDbgRec >= AMOIUNT_DBG_REC)
                uiIdxArrBGSigDbgRec = 0;
            if(shIdxBGSBkpt == 97){    //Signal for Print
                do{
                   for( i = shIdxBeg; (i < (shIdxBeg +10)) &&(i < shIdxEnd); i++){
                    //printf("Iter = %ld,  \n", lT);//shIdxBeg
                    printf("Iter = #%ld# >>Iti = %ld It_01 = %ld It_02 = %ld <<\n", ArrBGSigDbgRec[i].luIterLU, ArrBGSigDbgRec[i].luIti, ArrBGSigDbgRec[i].luIt_01, ArrBGSigDbgRec[i].luIt_02);lT = atol("1234567");lT += atol("2345671");lT = atol("3456758");lT += atol("23456651");lT = atol("3456744");
                    printf("          [D_In = %d D_Clr = %d D_Q = %d D_notQ = %d  ", ArrBGSigDbgRec[i].chD_In,ArrBGSigDbgRec[i].chD_Clr,ArrBGSigDbgRec[i].chD_Q,ArrBGSigDbgRec[i].chD_notQ);lT = atol("1234567");lT += atol("2345671");lT = atol("3456758");lT += atol("23456651");lT = atol("3456744");
                    printf("InImpNovyi = %d, Novyi = %d,DeltaIFix = %d, TzatrOut = %d ] \n", ArrBGSigDbgRec[i].chFixUnitIn,ArrBGSigDbgRec[i].chDeltaIBUS,ArrBGSigDbgRec[i].chDeltaIFix,ArrBGSigDbgRec[i].chTwaitOut);
                    printf("          [Ifix = %ld  Ip = %ld Ic = %ld uNCC = %ld] \n", ArrBGSigDbgRec[i].luIfix, ArrBGSigDbgRec[i].luIp, ArrBGSigDbgRec[i].luIc, ArrBGSigDbgRec[i].luNCC);
                    lT = atol("8234567");lT += atol("7345671");lT = atol("4456758");lT += atol("33456651");lT = atol("1456744");
                    printf("\n");
                     lT = atol("1234567");lT += atol("2345671");lT = atol("3456758");lT += atol("23456651");lT = atol("3456744");
                    }shIdxBeg += 10; lT = atol("1234567");lT += atol("2345671");lT = atol("3456758");lT += atol("23456651");lT = atol("3456744");
                }while( shIdxBeg < shIdxEnd );
            }
        }
        else{
            rCBGSig.CalcBusGrSigSchematic();
        }
#else
		
         rCBGSig.CalcBusGrSigSchematic();

#endif
    }
}

#include "LUBgsp1.cpp"
//static char chGLB_DTrg = 0;
//static char chGLB_C1 = 0;
void CBGSig::CalcBusGrSigSchematicDbg(void) {
    register long  rl_Val,i;
    register long  lRamainderNNP, lRamainderNNC;
//#pragma data_alignment=4 
//    char arChIntermediaResult[(TOTAL_BGS_LU)];
memset(static_cast<void*>(arrOut),0,sizeof(char  )*TOTAL_BGS_VISIO_OUT);

    i = EvalDeltaIbusDbg();

    if (ch_C1 == 0 && (i) == 1) {
        ch_DTrg = 1;
    }
    ch_C1 = i;
    i = 0;
    bool bbDeltaItminusIf;
    if (ch_DTrg == 1) {
        long j, Iti;
        Iti = measurement_DBG[m_chNumberAnalogChanell];
        
        if ( (Iti > m_lIfix) ) {
            j = Iti - m_lIfix;
        } else {
            j = m_lIfix - Iti;
        }
        
        i = (m_BGSigSuit.lIust * measurement_DBG[4]) / lU_NOM;
                i *=9; i/=10;//i *= 58981;i>>=16;//0.9 koeff
        if (j >= i)
            i = 1;
        else
            i = 0;
    }
    bbDeltaItminusIf = i;
    bool bbTDelay,bbT1ms;
    bbTDelay = lTWait(bbDeltaItminusIf);
    if(bbTDelay && m_chWRIp == 0){
        m_lIp = m_lIfix;
        m_lIc = measurement_DBG[m_chNumberAnalogChanell];
        if (m_BGSigSuit.chCheckBgs == 0) {
            m_lNNC = m_lIc / (m_lKcDeltaIy);
            m_lNNP = m_lIp / (m_lKcDeltaIy);
            lRamainderNNC  = m_lIc % (m_lKcDeltaIy);
            if(lRamainderNNC>=(m_lKcDeltaIy>>1))
                m_lNNC++;
            lRamainderNNP = m_lIp % (m_lKcDeltaIy);
            if(lRamainderNNP>=(m_lKcDeltaIy>>1))
                m_lNNP++;
            
        } else {
            //m_lNNC = (m_lIc - m_lKcDeltaIy) / m_lKcDeltaIy;
            //m_lNNP = (m_lIp - m_lKcDeltaIy) / m_lKcDeltaIy;
            m_lNNC = (m_lIc ) / m_lKcDeltaIy;
            
            m_lNNP = (m_lIp ) / m_lKcDeltaIy;
            
            //lRamainderNNC   = (m_lIc - m_lKcDeltaIy) % m_lKcDeltaIy;
            lRamainderNNC   = (m_lIc ) % m_lKcDeltaIy;
            if(lRamainderNNC>0)
                lRamainderNNC--;
            if(lRamainderNNC>=(m_lKcDeltaIy>>1))
                m_lNNC++;
            //lRamainderNNP  = (m_lIp - m_lKcDeltaIy) % m_lKcDeltaIy;
            lRamainderNNP  = (m_lIp ) % m_lKcDeltaIy;
            if(lRamainderNNP>0)
                lRamainderNNP--;
            if(lRamainderNNP>=(m_lKcDeltaIy>>1))
                m_lNNP++;
            
            if(m_lNNC>0)
                m_lNNC--;
            //else{}
            if(m_lNNP>0)
                m_lNNP--;
            //else{}
        }
        m_chWRIp = 1;
    }
    else {
        if (bbTDelay == false)
        m_chWRIp = false;
    }
    ;bbT1ms = bbTDelay || ((!bbDeltaItminusIf) &&(ch_DTrg == 1));
    if(TClrTrg(bbT1ms))
    ch_DTrg = 0;

    
    if(m_BGSigSuit.chStateGS){
        rl_Val = m_lNNC - m_lNNP;
        if (rl_Val > 0)
            arrOut[BGS_OUT_NAME_NNP - 1] = 1;
        rl_Val = m_lNNP - m_lNNC;
        if (rl_Val > 0)
            arrOut[BGS_OUT_NAME_NNM - 1] = 1;
        if (m_lNNC >= 1)
            arrOut[BGS_OUT_NAME_CC - 1] = 1;
        arrOut[BGS_OUT_NAME_NNC_INF-1] = m_lNNC;
        
        if (m_BGSigSuit.chCheckBgs > 0){
            rl_Val = m_lKcDeltaIy;//(m_lKcDeltaIy*58981)>>16;
            
            
            if (measurement_DBG[m_chNumberAnalogChanell] <= static_cast<unsigned long>(rl_Val) ){
                m_chStdpCE = 1;
            }
            else{
            rl_Val *= 11;rl_Val /= 10;
                if( (measurement_DBG[m_chNumberAnalogChanell] <= static_cast<unsigned long>(rl_Val)) 
                &&  (m_chStdpCE == 1) )
                    m_chStdpCE = 1;
                else
                    m_chStdpCE = 0;
            }
            
            if( m_chStdpCE == 1)
                arrOut[BGS_OUT_NAME_CE - 1] = 1;
            else
                arrOut[BGS_OUT_NAME_CE - 1] = 0;
        }else{
            arrOut[BGS_OUT_NAME_CE - 1] = 0;
        }
        

       if (measurement_DBG[m_chNumberAnalogChanell] > 2000){
            m_chStdpOV = 1;
        }
        else{
            if( (m_chStdpOV == 1) && (measurement_DBG[m_chNumberAnalogChanell] > 1800) )
                m_chStdpOV = 1;
            else
                m_chStdpOV = 0;
        }
        if( m_chStdpOV == 1)
            arrOut[BGS_OUT_NAME_OC  - 1] = 1;
        else
            arrOut[BGS_OUT_NAME_OC  - 1] = 0;
         

    }
    else{
        arrOut[BGS_OUT_NAME_NNP - 1] = 0;
        arrOut[BGS_OUT_NAME_NNM - 1] = 0;
        arrOut[BGS_OUT_NAME_CC  - 1] = 0;
        arrOut[BGS_OUT_NAME_NNC_INF-1] = 0;
        arrOut[BGS_OUT_NAME_CE  - 1] = 0;
        arrOut[BGS_OUT_NAME_OC  - 1] = 0;
    }
    register __LN_GROUP_ALARM *pLN_GROUP_ALARM = static_cast<__LN_GROUP_ALARM *>(pvCfgLN);
    
   rl_Val = 0;
    rl_Val |= static_cast<bool>(arrOut[BGS_OUT_NAME_NNP -1])<<( GROUP_ALARM_OUT_NNP%8);
    rl_Val |= static_cast<bool>(arrOut[BGS_OUT_NAME_NNM -1])<<( GROUP_ALARM_OUT_NNM%8);
    rl_Val |= static_cast<bool>(arrOut[BGS_OUT_NAME_CC  -1])<<( GROUP_ALARM_OUT_CC %8);
    rl_Val |= static_cast<bool>(arrOut[BGS_OUT_NAME_OC  -1])<<( GROUP_ALARM_OUT_OC %8);
    rl_Val |= static_cast<bool>(arrOut[BGS_OUT_NAME_CE  -1])<<( GROUP_ALARM_OUT_CE %8);
    pLN_GROUP_ALARM->active_state[(GROUP_ALARM_OUT_OC /8) ] = rl_Val;
    i = m_lNNC;
    if(i < 0)
        pLN_GROUP_ALARM->NNC = 0;//arrOut[BGS_OUT_NAME_NNC_INF-1];
    else
        pLN_GROUP_ALARM->NNC = i;//arrOut[BGS_OUT_NAME_NNC_INF-1];
    rl_Val = 0;
    
    if(m_chStateTWait)
        rl_Val |= 1;
   if(m_chStateTReset)
        rl_Val |= 1<<1;//Be Careful you don`t difer bits of each LU
        
    i = CBGSig::chNeedTimerCalculated;
    if(rl_Val>0)
        i |= 1<<shShemasOrdNumStng;
    else
        i &= ~(1<<shShemasOrdNumStng);
    CBGSig::chNeedTimerCalculated = i;//It`s Need for Call recalc because Timer work

    
}
void CBGSig::CalcBusGrSigSchematic1(void) {
    register long  rl_Val,i;
    register long  lRamainderNNP, lRamainderNNC;
 // #pragma data_alignment=4 
 //    char arChIntermediaResult[(TOTAL_BGS_LU)];
 memset(static_cast<void*>(arrOut),0,sizeof(char  )*TOTAL_BGS_VISIO_OUT);

//    i = EvalDeltaIbus();
    i = EvalDeltaIbus(static_cast<void*>(CBGSig::measbuf));

    if (ch_C1 == 0 && (i) == 1) {
        ch_DTrg = 1;
    }
    ch_C1 = i;
    i = 0;
    bool bbDeltaItminusIf;
    if (ch_DTrg == 1) {
        long j, Iti;
        Iti = measurement[m_chNumberAnalogChanell];
        if (Iti > m_lIfix) {
            j = Iti - m_lIfix;
        } else {
            j = m_lIfix - Iti;
        }
        i = (m_BGSigSuit.lIust * measurement[4]) / lU_NOM;
        i *=9; i/=10;//i *= 58981;i>>=16;//0.9 koeff
        if (j > i)
            i = 1;
        else
            i = 0;
    }
    bbDeltaItminusIf = i;
    bool bbTDelay,bbT1ms;
    bbTDelay = lTWait(bbDeltaItminusIf);
    if(bbTDelay && m_chWRIp == 0){
        m_lIp = m_lIfix;
        m_lIc = measurement[m_chNumberAnalogChanell];
        m_lIcMulUnom  = m_lIc*lU_NOM;
        m_lIpMulUnom  = m_lIp*lU_NOM;
        m_lIyMulU     = m_BGSigSuit.lIust * measurement[4];
        
        m_lNNC = ( m_lIcMulUnom )/(m_lIyMulU);//(m_lKcDeltaIy);
        m_lNNP = ( m_lIpMulUnom )/(m_lIyMulU);//(m_lKcDeltaIy);
        
        lRamainderNNC   = (m_lIcMulUnom) % m_lIyMulU;  //lRamainderNNC  = m_lIc % (m_lKcDeltaIy);
        if(lRamainderNNC>=(m_lIyMulU>>1))              //if(lRamainderNNC>=(m_lKcDeltaIy>>1))
            m_lNNC++;                                  //    m_lNNC++;
        lRamainderNNP  =  (m_lIpMulUnom )%(m_lIyMulU); //lRamainderNNP = m_lIp % (m_lKcDeltaIy);
        if(lRamainderNNP>=(m_lIyMulU>>1))              //if(lRamainderNNP>=(m_lKcDeltaIy>>1))
            m_lNNP++;                                  //    m_lNNP++;
        
        if (m_BGSigSuit.chCheckBgs > 0) {
            if(m_lNNC>0)
                m_lNNC--;
            //else{}
            if(m_lNNP>0)
                m_lNNP--;
            
            
        }  

        m_chWRIp = 1;
    
    }
    else {
        if (bbTDelay == false)
        m_chWRIp = false;
    }
    bbT1ms = bbTDelay || ((!bbDeltaItminusIf) &&(ch_DTrg == 1));
    if(TClrTrg(bbT1ms))
    ch_DTrg = 0;
    
    if(m_BGSigSuit.chStateGS){
        rl_Val = m_lNNC - m_lNNP;
        if (rl_Val > 0)
            arrOut[BGS_OUT_NAME_NNP - 1] = 1;
        rl_Val = m_lNNP - m_lNNC;
        if (rl_Val > 0)
            arrOut[BGS_OUT_NAME_NNM - 1] = 1;
        if (m_lNNC >= 1)
            arrOut[BGS_OUT_NAME_CC - 1] = 1;
        arrOut[BGS_OUT_NAME_NNC_INF-1] = m_lNNC;
        

        
        if (m_BGSigSuit.chCheckBgs > 0){
            rl_Val = m_lKcDeltaIy;//(m_lKcDeltaIy*58981)>>16;
            rl_Val *= 9;rl_Val /= 10;
            
            if (measurement[m_chNumberAnalogChanell] <= static_cast<unsigned long>(rl_Val) ){
                m_chStdpCE = 1;
            }
            else{
                rl_Val *= 11;rl_Val /= 10;
                if( (measurement[m_chNumberAnalogChanell] <= static_cast<unsigned long>(rl_Val)) 
                &&  (m_chStdpCE == 1) )
                    m_chStdpCE = 1;
                else
                    m_chStdpCE = 0;
            }
            
            if( m_chStdpCE == 1)
                arrOut[BGS_OUT_NAME_CE - 1] = 1;
            else
                arrOut[BGS_OUT_NAME_CE - 1] = 0;
        }else{
            arrOut[BGS_OUT_NAME_CE - 1] = 0;
        }
        
        
        
        if (measurement[m_chNumberAnalogChanell] > 2000){
            m_chStdpOV = 1;
            
        }
        else{
            if( (m_chStdpOV == 1) && (measurement[m_chNumberAnalogChanell] > 1800) )
                m_chStdpOV = 1;
            else
                m_chStdpOV = 0;
        }
        
        if( m_chStdpOV == 1)
            arrOut[BGS_OUT_NAME_OC  - 1] = 1;
        else
            arrOut[BGS_OUT_NAME_OC  - 1] = 0;
            
    }
    else{
        arrOut[BGS_OUT_NAME_NNP - 1] = 0;
        arrOut[BGS_OUT_NAME_NNM - 1] = 0;
        arrOut[BGS_OUT_NAME_CC  - 1] = 0;
        arrOut[BGS_OUT_NAME_NNC_INF-1] = 0;
        arrOut[BGS_OUT_NAME_CE  - 1] = 0;
        arrOut[BGS_OUT_NAME_OC  - 1] = 0;
    }
    register __LN_GROUP_ALARM *pLN_GROUP_ALARM = static_cast<__LN_GROUP_ALARM *>(pvCfgLN);
    
   rl_Val = 0;
    rl_Val |= static_cast<bool>(arrOut[BGS_OUT_NAME_NNP -1])<<( GROUP_ALARM_OUT_NNP%8);
    rl_Val |= static_cast<bool>(arrOut[BGS_OUT_NAME_NNM -1])<<( GROUP_ALARM_OUT_NNM%8);
    rl_Val |= static_cast<bool>(arrOut[BGS_OUT_NAME_CC  -1])<<( GROUP_ALARM_OUT_CC %8);
    rl_Val |= static_cast<bool>(arrOut[BGS_OUT_NAME_OC  -1])<<( GROUP_ALARM_OUT_OC %8);
    rl_Val |= static_cast<bool>(arrOut[BGS_OUT_NAME_CE  -1])<<( GROUP_ALARM_OUT_CE %8);
    pLN_GROUP_ALARM->active_state[(GROUP_ALARM_OUT_OC /8) ] = rl_Val;
    pLN_GROUP_ALARM->NNC = 0;
    if(m_BGSigSuit.chStateGS){
         i = m_lNNC;
        if(i < 0)
            pLN_GROUP_ALARM->NNC = 0;//arrOut[BGS_OUT_NAME_NNC_INF-1];
        else
            pLN_GROUP_ALARM->NNC = i;//arrOut[BGS_OUT_NAME_NNC_INF-1];
    }    
    rl_Val = 0;
    
    if(m_chStateTWait)
        rl_Val |= 1;
   if(m_chStateTReset)
        rl_Val |= 1<<1;//Be Careful you don`t difer bits of each LU
        
    i = CBGSig::chNeedTimerCalculated;
    if(rl_Val>0)
        i |= 1<<shShemasOrdNumStng;
    else
        i &= ~(1<<shShemasOrdNumStng);
    CBGSig::chNeedTimerCalculated = i;//It`s Need for Call recalc because Timer work

}
//long Ibus, long lTinterval
// UCV - від 54 до 253 В.
// IIN1, IIN2, IIN3, IIN4 ==  0,005 до 5 А.
char chBkpt = 0;
long CBGSig::EvalDeltaIbusDbg(void) {
    register long i, j,Iti;
    //Kc = Ucurr_power/Unom_power
    //Num Analog Chanel
    Iti = measurement_DBG[m_chNumberAnalogChanell];
    if((chBkpt != 0) && (m_chNumberAnalogChanell==1))asm(
                "bkpt 1"
                );
//    Iti = measurement_DBG[m_chNumberAnalogChanell];
    if (Iti > m_lMeasIti_mn_1) {
        j = Iti - m_lMeasIti_mn_1;
//        m_chIfixDir |= 2;
//        m_chIfixDir &= ~4;
    } else {
        j = m_lMeasIti_mn_1 - Iti;
        //m_chIfixDir |= 4;
        //m_chIfixDir &= ~2;
    }
    //i = (m_BGSigSuit.lIust * measurement[4]) / lU_NOM;
    i = (m_BGSigSuit.lIust * measurement_DBG[4]) / lU_NOM;
m_lKcDeltaIy = i;
i*=9;i/=10;
    if (ch_DTrg == 1)
    {
        i = 0;
    }
    else{
    
        if (j > i) {//Novyi New-made
            if (m_chWRIfix == 0) {
                m_lIfix = m_lMeasIti_mn_1;
                m_chWRIfix = 1;
                i = 1;
            }
            
        } else{ i = 0;m_chWRIfix = 0;
            if (m_chWRIfix == 0 && ch_DTrg == 0 
            && ch_C1 == 0 && m_chIfixDir != 0) {
                j = m_lIfix;
                if (j<Iti)
                    i = Iti - j;
                else
                    i = j - Iti;
                if(i > m_lKcDeltaIy ){
                    // asm(
                    // "bkpt 1"
                    // );
                    i = 1;
                }
                else i = 0;
            }
        }
    }    
    m_lMeasIti_mn_1 = Iti;
    

    return i;
}
long CBGSig::EvalDeltaIbus(void) {
    register long i, j,Iti;
    //Kc = Ucurr_power/Unom_power
    //Num Analog Chanel
    Iti = measurement[m_chNumberAnalogChanell];
    if((chBkpt != 0) && (m_chNumberAnalogChanell==1))asm(
                "bkpt 1"
                );
//    Iti = measurement[m_chNumberAnalogChanell];
    if (Iti > m_lMeasIti_mn_1) {
        j = Iti - m_lMeasIti_mn_1;
    } else {
        j = m_lMeasIti_mn_1 - Iti;
    }
    //i = (m_BGSigSuit.lIust * measurement[4]) / lU_NOM;
    i = (m_BGSigSuit.lIust * measurement[4]) / lU_NOM;
m_lKcDeltaIy = i;
i*=9;i/=10;//i *= 58981;i>>=16;//0.9 koeff
    if (ch_DTrg == 1)
    {
        i = 0;
    }
    else{
        if (j > i) {//Novyi New-made
            if (m_chWRIfix == 0) {
                m_lIfix = m_lMeasIti_mn_1;
                m_chWRIfix = 1;
                i = 1;
            }
            
        } else{ i = 0;m_chWRIfix = 0;
            if (m_chWRIfix == 0 && ch_DTrg == 0 
            && ch_C1 == 0 && m_chIfixDir != 0) {
                j = m_lIfix;
                if (j<Iti)
                    i = Iti - j;
                else
                    i = j - Iti;
                if(i > m_lKcDeltaIy ){
                    // asm(
                    // "bkpt 1"
                    // );
                    i = 1;
                }
                else i = 0;
            }
        
        
        }
    }    
    m_lMeasIti_mn_1 = Iti;
    

    return i;
}
// long CBGSig::StoreIfixTimeFix(long lTime, long lIbus, long lActive) {
// register long i;

//     return 0;
// }

long CBGSig::EvalDeltaIbusDbg(void*pv) {
    register long i, j,Iti;
    //Kc = Ucurr_power/Unom_power
    //Num Analog Chanel
//    Iti = measurement_DBG[m_chNumberAnalogChanell];
    Iti = *(static_cast<long*>(pv)+m_chNumberAnalogChanell);
    if((chBkpt != 0) && (m_chNumberAnalogChanell==1))asm(
                "bkpt 1"
                );
//    Iti = measurement_DBG[m_chNumberAnalogChanell];
    if (Iti > m_lMeasIti_mn_1) {
        j = Iti - m_lMeasIti_mn_1;
//        m_chIfixDir |= 2;
//        m_chIfixDir &= ~4;
    } else {
        j = m_lMeasIti_mn_1 - Iti;
        //m_chIfixDir |= 4;
        //m_chIfixDir &= ~2;
    }
    //i = (m_BGSigSuit.lIust * measurement[4]) / lU_NOM;
    i = (m_BGSigSuit.lIust * measurement_DBG[4]) / lU_NOM;
m_lKcDeltaIy = i;
i*=9;i/=10;
    if (ch_DTrg == 1)
    {
        i = 0;
    }
    else{
    
        if (j > i) {//Novyi New-made
            if (m_chWRIfix == 0) {
                m_lIfix = m_lMeasIti_mn_1;
                m_chWRIfix = 1;
                i = 1;
            }
            
        } else{ i = 0;m_chWRIfix = 0;
            if (m_chWRIfix == 0 && ch_DTrg == 0 
            && ch_C1 == 0 && m_chIfixDir != 0) {
                j = m_lIfix;
                if (j<Iti)
                    i = Iti - j;
                else
                    i = j - Iti;
                if(i > m_lKcDeltaIy ){
                    // asm(
                    // "bkpt 1"
                    // );
                    i = 1;
                }
                else i = 0;
            }
        }
    }    
    m_lMeasIti_mn_1 = Iti;
    

    return i;
}
long CBGSig::EvalDeltaIbus(void *pv) {
    register long i, j,Ii,Ip;
    volatile long lRetVal;
    lRetVal = 0;
    //Kc = Ucurr_power/Unom_power
    //Num Analog Chanel
    i = CBGSig::m_chIdxGrupSamples;
//Look Oldest Val
  
    Ip =  *(static_cast<long*>(pv)+m_chNumberAnalogChanell
    + (i*I_U*1) );
    if(i == 0)
        i = 2;
    else i--;     
    Ii = *(static_cast<long*>(pv)+m_chNumberAnalogChanell+ (i*I_U*1) );
    
    if((chBkpt != 0) && (m_chNumberAnalogChanell==1))asm(
                "bkpt 1"
                );
//    Iti = measurement[m_chNumberAnalogChanell];
    if (Ii > Ip) {
        j = Ii - Ip;
    } else {
        j = Ip - Ii;
    }
    //i = (m_BGSigSuit.lIust * measurement[4]) / lU_NOM;
    i = (m_BGSigSuit.lIust * measurement[4]) / lU_NOM;
    m_lKcDeltaIy = i;
    i*=9;i/=10;//i *= 58981;i>>=16;//0.9 koeff

    if (ch_DTrg == 1)
    {
        i = 0;
    }
    else{
        if (j > i) {//Novyi New-made
            if (m_chWRIfix == 0) {
                m_lIfix = Ip;
                m_chWRIfix = 1;
                lRetVal = 1;
            }
            
        } else{ 
            i = CBGSig::m_chIdxGrupSamples;
            i++;
            if(i > 2)
            i = 0;
            Ip =  *(static_cast<long*>(pv)+m_chNumberAnalogChanell
            + (i*I_U*1) );
            if (Ii > Ip) {
                j = Ii - Ip;
            } else {
                j = Ip - Ii;
            }
            i = m_lKcDeltaIy;
            i*=9;i/=10;
            if (j > i) {//Novyi New-made
                if (m_chWRIfix == 0) {
                    m_lIfix = Ip;
                    m_chWRIfix = 1;
                    lRetVal = 1;
                }
              //Break;  
            }
            else{
                 m_chWRIfix = 0;
                if (m_chWRIfix == 0  
                 && ch_C1 == 0 && m_chIfixDir != 0){
                j = m_lIfix;
                if (j<Ii)
                    i = Ii - j;
                else
                    i = j - Ii;
                if(i > m_lKcDeltaIy ){
                    // asm(
                    // "bkpt 1"
                    // );
                    lRetVal = 1;
                }
                else i = 0;; //Nothing Means

                } 
            }

        }
    }    
 
    

    return lRetVal;
}
enum PBGS_BIT_POS { 

BGS_DV_BLOCK_CMD_BIT  = 1,  

BGS_DV_BLOCK_INVERSE_CMD_BIT  ,  
BGS_MENU_STATE_BIT,
BGS_MENU_CTRL_STATE_BIT,
BGS_NOT7_STATE_BIT,
//BGS_AND8_STATE_BIT,
//BGS_OR9_STATE_BIT,
//BGS_TRESET_STATE_BIT,
BGS_TWAIT_STATE_BIT,
BGS_NOT13_STATE_BIT,
BGS_NOT26_STATE_BIT,
BGS_AND14_STATE_BIT,
BGS_AND15_STATE_BIT,
BGS_AND16_STATE_BIT,
BGS_AND17_STATE_BIT,
BGS_MUX_NNC_STATE_BIT,
BGS_MUX_NNP_STATE_BIT,//16
BGS_PO_NNP_STATE_BIT,
BGS_PO_NNM_STATE_BIT,
BGS_PO_NCC_STATE_BIT,
BGS_AND30_STATE_BIT,
BGS_AND31_STATE_BIT,
BGS_AND32_STATE_BIT,
BGS_AND35_STATE_BIT,
BGS_AND36_STATE_BIT,
BGS_AND37_STATE_BIT,
BGS_PO_CE_STATE_BIT,
BGS_PO_OC_STATE_BIT,
BGS_PICKUP_3U0_STATE_BIT,
BGS_TMR_3U0_STATE_BIT,
TOTAL_BGS_BITS//30
//LU_GEN_OP_EV_FIX_IBUS
};

void CBGSig::CalcBusGrSigSchematic(void) {
    register unsigned long  rUl_1,rUl_2;
//    register unsigned long u32_bit_hld1 = 0;  
    union 
    {
        unsigned char   uchAr [4];
        unsigned short  ushAr [2];
        unsigned long   ulVal;
    }unnBF1;//,unnBF2;
 union { //register
   struct {
      unsigned int  PO_DeltaIbus: 1;
      unsigned int  DTrgInv:1;
      unsigned int  PO_Ifix:1;
      unsigned int  PO_Inew:1;
      unsigned int  PO_DeltaIbusFix:1;
      unsigned int  PO_DeltaIbusNew:1;
      unsigned int  Delay1ms:1;
      unsigned int  Imp6ms :1;
      unsigned int  PoIp:1;
      unsigned int  PoIc:1;
      unsigned int  PO_NNC_NCH:1;
      unsigned int  PO_NNP_NCH:1;
      unsigned int  PO_NNC_CH :1;
      unsigned int  PO_NNP_CH :1;
      
   } bool_vars;
  long lVl;
  
}wrp;
    //long  lRamainderNNP, lRamainderNNC;
struct{
long Ii,Ip,Ifix,It_02,U;
void* pv;
char chNotImp6ms;//,chIdxGrupSamplesFix
}sLV;    
    volatile bool boolWl, boolTzatr;
    wrp.lVl = 0;
    unnBF1.ulVal = 0;
    m_Iteration++;
    if((measurement[4] >= l_1D15_UNOM) || (measurement[4] <= l_0D80_UNOM))
		sLV.U = lU_NOM;
	else
		sLV.U = measurement[4];
   
//#pragma data_alignment=4 
//    char arChIntermediaResult[(TOTAL_BGS_LU)];
memset(static_cast<void*>(arrOut),0,sizeof(char  )*TOTAL_BGS_VISIO_OUT);
    sLV.pv = static_cast<void*>(CBGSig::measbuf);
    sLV.It_02 = *(static_cast<long*>(sLV.pv)+m_chNumberAnalogChanell+ (CBGSig::m_chIdxGrupSamples*I_U*1) );   
    
    boolWl = false;    
    do{
        register long i_l, j_l,Ii,Ip;
        i_l = CBGSig::m_chIdxGrupSamples;
        i_l++;
        if(i_l > 2)
            i_l = 0;
        Ip =  *(static_cast<long*>(sLV.pv)+m_chNumberAnalogChanell+ (i_l*I_U*1) );//I_U-Means index U- last number
        i_l = CBGSig::m_chIdxGrupSamples;
        if(i_l == 0)
            i_l = 2;
        else i_l--;     
        Ii = *(static_cast<long*>(sLV.pv)+m_chNumberAnalogChanell+ (i_l*I_U*1) );
    
//        if((chBkpt != 0) && (m_chNumberAnalogChanell==1))
//            asm(
//            "bkpt 1"
//            );
        sLV.Ii = Ii;sLV.Ip = Ip;m_lIti = Ii;
         
        if (Ii > Ip) {
           j_l = Ii - Ip;
        } else {
            j_l = Ip - Ii;
        }
        //!..i_l = (m_BGSigSuit.lIust * measurement[4]) / lU_NOM;
        i_l = (m_BGSigSuit.lIust * sLV.U) / lU_NOM;
        m_lKcDeltaIy = i_l;
        i_l*=9;i_l/=10;//i *    
        if (j_l > i_l) {//Novyi New-made
            if(m_chDeltaIBus == 0 ){//if(m_chDeltaIBus == 0){
                wrp.bool_vars.PO_DeltaIbus = true;sLV.Ifix = Ip;m_chDeltaIBus = 1;
            }else{
                m_chDeltaIBus = 0;
            }    
        }
        else{
            i_l = CBGSig::m_chIdxGrupSamples;
            Ip =  *(static_cast<long*>(sLV.pv)+m_chNumberAnalogChanell+ (i_l*I_U*1) );

            //ArrBGSigDbgRec[uiIdxArrBGSigDbgRec].luIt_02 = sLV.Ip;
            sLV.Ip = Ip;
            if (Ii > Ip) {
                j_l = Ii - Ip;
            } else {
                j_l = Ip - Ii;
            }
            i_l = m_lKcDeltaIy;
            i_l*=9;i_l/=10;
            if (j_l > i_l) {//Novyi New-made
                //if(m_chDeltaIBus != i_l){
                if(m_chDeltaIBus == 0){
                    wrp.bool_vars.PO_DeltaIbus = true;sLV.Ifix = Ip;m_chDeltaIBus = 1;
                }else{
                m_chDeltaIBus = 0;
                }
            }else{
                m_chDeltaIBus = 0;//wrp.bool_vars.PO_DeltaIbus = false;// !!! Only for Dbg
            }
            
        }
            
            
       // boolWl = false;    

    }while(boolWl);
    
     
    
    //?if(TClrTrg(chTzatrState))
    if(TClrTrg(m_chWRIc))
        ch_DTrg = 0;//Clear Trigger
    else if (ch_C1 == 0 && (wrp.bool_vars.PO_DeltaIbus) == 1) {
        ch_DTrg = 1;//DTrgInv = !ch_DTrg;
        
    }
   /*. if(TClrTrg(chTzatrState))
        ch_DTrg = 0;//Clear Trigger
    else if (ch_C1 == 0 && (wrp.bool_vars.PO_DeltaIbus) == 1) {
        ch_DTrg = 1;//DTrgInv = !ch_DTrg;
        
    }
    схоже що це можливо неправильно? Насправді це робота попередньому фронту
	*/
	
    //wrp.bool_vars.DTrgInv = !ch_DTrg;
    rUl_2 = (~static_cast<unsigned long>(ch_DTrg))&1;
    //i++;//
    //i &= 1;
    wrp.bool_vars.DTrgInv = rUl_2;
    
    ch_C1 = wrp.bool_vars.PO_DeltaIbus;
    rUl_1 = (TElongation(wrp.bool_vars.DTrgInv));
    rUl_1 &= wrp.bool_vars.PO_DeltaIbus;
    //if(i && wrp.bool_vars.PO_DeltaIbus){
    //?if(rUl_1 != 0 && chTzatrState == 0){
    if(rUl_1 != 0 ){ //&& m_chIfixDir==0 - fix state and4 or WR input prev stte
        if (m_chWRIfix == 0) {//chTzatrState == 0 <-This is early code chahged to chTzatrState
                //m_lIfix =  sLV.Ip;//!????
                m_lIfix = sLV.Ifix; 
                m_chWRIfix = 1;
                m_lInew = sLV.Ii;//m_lIti
                wrp.bool_vars.PO_Ifix = true;wrp.bool_vars.PO_Inew = 1;
            };
    }else{
        ;//Clr Ifix Module
        m_chWRIfix = 0;//wrp.bool_vars.PO_Ifix = false;
    }
    
    if (ch_DTrg == 1 ) {//&& wrp.bool_vars.PO_Ifix
        long i_l,j_l, Iti;
        //!????Iti = measurement[m_chNumberAnalogChanell];<<== Error//
        Iti = sLV.Ii;
        if (Iti > m_lIfix) {
            j_l = Iti - m_lIfix;
        } else {
            j_l = m_lIfix - Iti;
        }
        //!..i_l = (m_BGSigSuit.lIust * measurement[4]) / lU_NOM;
        i_l = (m_BGSigSuit.lIust * sLV.U) / lU_NOM;
        i_l *=9; i_l/=10;
        if (j_l > i_l){
            wrp.bool_vars.PO_DeltaIbusFix = rUl_1 = 1;//i_l = 1;
        }    
        else
            rUl_1 = 0;
        if (Iti > m_lInew) {
            j_l = Iti - m_lInew;
        } else {
            j_l = m_lInew - Iti;
        }
        //!..i_l = (m_BGSigSuit.lIust * measurement[4]) / lU_NOM;
        i_l = (m_BGSigSuit.lIust * sLV.U) / lU_NOM;
        i_l *=9; i_l/=10;
        if (j_l > i_l){
            wrp.bool_vars.PO_DeltaIbusNew = 1;//i_l = 1;
        }    
        else
            rUl_2 = 0;
        //if(rUl_2 == 0 && rUl_1 == 0)
        //asm(
        //       "bkpt 1"
        //       );
        
    
    }else{
		
	}	
    
    rUl_1 = wrp.bool_vars.PO_DeltaIbusFix;
    rUl_1 |= wrp.bool_vars.PO_DeltaIbusNew;
    rUl_2 = (~rUl_1)&1;
    unnBF1.ushAr[0] |= (rUl_2) << BGS_NOT7_STATE_BIT;
    
    
    
    rUl_1 = (lTWait(rUl_1));
    //if()
    unnBF1.ulVal |= (rUl_1)<< BGS_TWAIT_STATE_BIT;
    chTzatrState = rUl_1;
    rUl_2 &= ch_DTrg;//(unnBF1.ulVal&( 1<< BGS_NOT7_STATE_BIT)) && ch_DTrg==1; 
    
    if(TClrTrg(rUl_1|rUl_2))
        ch_DTrg = 0;//Clear Trigger
    m_chWRIc = rUl_1|rUl_2;//! Temp Debug Code    
    
    rUl_1 = ( 1<< BGS_TWAIT_STATE_BIT);
    rUl_1 &= unnBF1.ulVal;
    rUl_2 =  (TImp6ms(rUl_1));
    //Inversion cmd
    rUl_1 = (~rUl_2)&1;
    unnBF1.ulVal |= rUl_1 << BGS_NOT26_STATE_BIT;
    sLV.chNotImp6ms = rUl_1;
    //if((unnBF1.ulVal&( 1<< BGS_TWAIT_STATE_BIT))&& m_chWRIp == 0){
    boolTzatr = chTzatrState;

    if( boolTzatr && m_chWRIp == 0){
        long  lRamainderNNP, lRamainderNNC;
        m_lIp = m_lIfix;
        //m_lIc = measurement[m_chNumberAnalogChanell];//!???
        m_lIc = sLV.Ii;
        m_lIcMulUnom  = m_lIc*lU_NOM;
        m_lIpMulUnom  = m_lIp*lU_NOM;
        //!..m_lIyMulU     = m_BGSigSuit.lIust * measurement[4];
        m_lIyMulU     = m_BGSigSuit.lIust * sLV.U;
        
        m_lNNC = ( m_lIcMulUnom )/(m_lIyMulU);//(m_lKcDeltaIy);
        m_lNNP = ( m_lIpMulUnom )/(m_lIyMulU);//(m_lKcDeltaIy);
        
        lRamainderNNC   = (m_lIcMulUnom) % m_lIyMulU;  //lRamainderNNC  = m_lIc % (m_lKcDeltaIy);
        if(lRamainderNNC>=(m_lIyMulU>>1))              //if(lRamainderNNC>=(m_lKcDeltaIy>>1))
            m_lNNC++;                                  //    m_lNNC++;
        lRamainderNNP  =  (m_lIpMulUnom )%(m_lIyMulU); //lRamainderNNP = m_lIp % (m_lKcDeltaIy);
        if(lRamainderNNP>=(m_lIyMulU>>1))              //if(lRamainderNNP>=(m_lKcDeltaIy>>1))
            m_lNNP++;                                  //    m_lNNP++;
        
        if (m_BGSigSuit.chCheckBgs > 0) {
            if(m_lNNC>0)
                m_lNNC--;
            //else{}
            if(m_lNNP>0)
                m_lNNP--;
            
            
        }  

        m_chWRIp = 1;
    
    }
    else {
        if ((unnBF1.ulVal&( 1<< BGS_TWAIT_STATE_BIT)) == 0)
        m_chWRIp = 0;
    }

//   rl_Val = (unnBF1.ulVal&( 1<< )|( 1<< ))!= 0; //OR operation
//   rl_Val = unnBF1.ulVal&(( 1<< )|( 1<< )) == ( 1<< )|( 1<< ); 
//   unnBF1.ulVal |= (rl_Val)<<  
    
    if(m_BGSigSuit.chStateGS){
        rUl_1 = 0;
        long d = m_lNNC - m_lNNP;
        if (d > 0){
            if(sLV.chNotImp6ms){
                rUl_1 = 1;
            }
        }else{
            rUl_2 = d;
        }
        rUl_2 =  (TImpNNP(rUl_1));
        arrOut[BGS_OUT_NAME_NNP - 1] = rUl_2;
        rUl_1 = 0;
        d = m_lNNP - m_lNNC;
        if (d > 0){
            if(sLV.chNotImp6ms){
                rUl_1 = 1;
            }
            
        }
        rUl_2 =  (TImpNNM(rUl_1));    
        arrOut[BGS_OUT_NAME_NNM - 1] = rUl_2;
        if (m_lNNC >= 1){
        
            arrOut[BGS_OUT_NAME_CC - 1] = 1;
        }    
        arrOut[BGS_OUT_NAME_NNC_INF-1] = m_lNNC;
        

        
        if (m_BGSigSuit.chCheckBgs > 0){
            rUl_2 = m_lKcDeltaIy;//(m_lKcDeltaIy*58981)>>16;
            rUl_2 *= 9;rUl_2 /= 10;
            
            if (measurement[m_chNumberAnalogChanell] <= static_cast<unsigned long>(rUl_2) ){//!???
                m_chStdpCE = 1;
            }
            else{
                rUl_2 *= 11;rUl_2 /= 10;
                if( (measurement[m_chNumberAnalogChanell] <= static_cast<unsigned long>(rUl_2))//!??? 
                &&  (m_chStdpCE == 1) )
                    m_chStdpCE = 1;
                else
                    m_chStdpCE = 0;
            }
            
            if( m_chStdpCE == 1)
                arrOut[BGS_OUT_NAME_CE - 1] = 1;
            else
                arrOut[BGS_OUT_NAME_CE - 1] = 0;
        }else{
            arrOut[BGS_OUT_NAME_CE - 1] = 0;
        }
        
        
        
        if (measurement[m_chNumberAnalogChanell] > 2000){//!???
            m_chStdpOV = 1;
            
        }
        else{
            if( (m_chStdpOV == 1) && (measurement[m_chNumberAnalogChanell] > 1800) )//!???
                m_chStdpOV = 1;
            else
                m_chStdpOV = 0;
        }
        
        if( m_chStdpOV == 1)
            arrOut[BGS_OUT_NAME_OC  - 1] = 1;
        else
            arrOut[BGS_OUT_NAME_OC  - 1] = 0;
            
    }
    else{
        arrOut[BGS_OUT_NAME_NNP - 1] = 0;
        arrOut[BGS_OUT_NAME_NNM - 1] = 0;
        arrOut[BGS_OUT_NAME_CC  - 1] = 0;
        arrOut[BGS_OUT_NAME_NNC_INF-1] = 0;
        arrOut[BGS_OUT_NAME_CE  - 1] = 0;
        arrOut[BGS_OUT_NAME_OC  - 1] = 0;
    }
    register __LN_GROUP_ALARM *pLN_GROUP_ALARM = static_cast<__LN_GROUP_ALARM *>(pvCfgLN);
    
   rUl_2 = 0;
    rUl_2 |= static_cast<bool>(arrOut[BGS_OUT_NAME_NNP -1])<<( GROUP_ALARM_OUT_NNP%8);
    rUl_2 |= static_cast<bool>(arrOut[BGS_OUT_NAME_NNM -1])<<( GROUP_ALARM_OUT_NNM%8);
    rUl_2 |= static_cast<bool>(arrOut[BGS_OUT_NAME_CC  -1])<<( GROUP_ALARM_OUT_CC %8);
    rUl_2 |= static_cast<bool>(arrOut[BGS_OUT_NAME_OC  -1])<<( GROUP_ALARM_OUT_OC %8);
    rUl_2 |= static_cast<bool>(arrOut[BGS_OUT_NAME_CE  -1])<<( GROUP_ALARM_OUT_CE %8);
    pLN_GROUP_ALARM->active_state[(GROUP_ALARM_OUT_OC /8) ] = rUl_2;
    pLN_GROUP_ALARM->NNC = 0;
    if(m_BGSigSuit.chStateGS){
         rUl_1 = m_lNNC;
        if(m_lNNC < 0)
            pLN_GROUP_ALARM->NNC = 0;//arrOut[BGS_OUT_NAME_NNC_INF-1];
        else
            pLN_GROUP_ALARM->NNC = rUl_1;//arrOut[BGS_OUT_NAME_NNC_INF-1];
    }    
    rUl_2 = 0;
    
    if(m_chStateTWait)
        rUl_2 |= 1;
   if(m_chStateTReset)
        rUl_2 |= 1<<1;//Be Careful you don`t difer bits of each LU
    if( (m_chSttElongation&3) != 3)
        rUl_2 |= 1<<2;
    if(m_chStt6MsImp)
        rUl_2 |= 1<<3;
    if(m_chSttImpNNP)
        rUl_2 |= 1<<4;
    if(m_chSttImpNNM)
        rUl_2 |= 1<<5;        
    rUl_1 = CBGSig::chNeedTimerCalculated;
    if(rUl_2>0)
        rUl_1 |= 1<<shShemasOrdNumStng;
    else
        rUl_1 &= ~(1<<shShemasOrdNumStng);
    CBGSig::chNeedTimerCalculated = rUl_1;//It`s Need for Call recalc because Timer work

}

void CBGSig::CalcBusGrSigSchematicDBG1(void) {
    register unsigned long  rUl_1,rUl_2;
//    register unsigned long u32_bit_hld1 = 0;  
    union 
    {
        unsigned char   uchAr [4];
        unsigned short  ushAr [2];
        unsigned long   ulVal;
    }unnBF1;//,unnBF2;
 union { //register
   struct {
      unsigned int  PO_DeltaIbus: 1;
      unsigned int  DTrgInv:1;
      unsigned int  PO_Ifix:1;
      unsigned int  PO_Inew:1;
      unsigned int  PO_DeltaIbusFix:1;
      unsigned int  PO_DeltaIbusNew:1;
      unsigned int  Delay1ms:1;
      unsigned int  Imp6ms :1;
      unsigned int  PoIp:1;
      unsigned int  PoIc:1;
      unsigned int  PO_NNC_NCH:1;
      unsigned int  PO_NNP_NCH:1;
      unsigned int  PO_NNC_CH :1;
      unsigned int  PO_NNP_CH :1;
      
   } bool_vars;
  long lVl;
  
}wrp;
    //long  lRamainderNNP, lRamainderNNC;
struct{
long Ii,Ip,Ifix,It_02,U;
void* pv;
char chNotImp6ms;//,chIdxGrupSamplesFix
}sLV;    
    volatile bool boolWl, boolTzatr;
    wrp.lVl = 0;
    unnBF1.ulVal = 0;
    m_Iteration++;
	if((measurement[4] >= l_1D15_UNOM) || (measurement[4] <= l_0D80_UNOM))
		sLV.U = lU_NOM;
	else
		sLV.U = measurement[4];
    ArrBGSigDbgRec[uiIdxArrBGSigDbgRec].luIterLU = m_Iteration;
//#pragma data_alignment=4 
//    char arChIntermediaResult[(TOTAL_BGS_LU)];
memset(static_cast<void*>(arrOut),0,sizeof(char  )*TOTAL_BGS_VISIO_OUT);
    sLV.pv = static_cast<void*>(CBGSig::measbuf);
    sLV.It_02 = *(static_cast<long*>(sLV.pv)+m_chNumberAnalogChanell+ (CBGSig::m_chIdxGrupSamples*I_U*1) );
    ArrBGSigDbgRec[uiIdxArrBGSigDbgRec].luIt_02 = sLV.It_02;
    boolWl = false;
    do{
        register long i_l, j_l,Ii,Ip;
        i_l = CBGSig::m_chIdxGrupSamples;
        i_l++;
        if(i_l > 2)
            i_l = 0;
        Ip =  *(static_cast<long*>(sLV.pv)+m_chNumberAnalogChanell+ (i_l*I_U*1) );//I_U-Means index U- last number
        i_l = CBGSig::m_chIdxGrupSamples;
        if(i_l == 0)
            i_l = 2;
        else i_l--;     
        Ii = *(static_cast<long*>(sLV.pv)+m_chNumberAnalogChanell+ (i_l*I_U*1) );
    
//        if((chBkpt != 0) && (m_chNumberAnalogChanell==1))
//            asm(
//            "bkpt 1"
//            );
        sLV.Ii = Ii;sLV.Ip = Ip;m_lIti = Ii;
        ArrBGSigDbgRec[uiIdxArrBGSigDbgRec].luIti   = sLV.Ii; ArrBGSigDbgRec[uiIdxArrBGSigDbgRec].luIt_01 = sLV.Ip; 
        if (Ii > Ip) {
           j_l = Ii - Ip;
        } else {
            j_l = Ip - Ii;
        }
        //..i_l = (m_BGSigSuit.lIust * measurement[4]) / lU_NOM;
        i_l = (m_BGSigSuit.lIust * sLV.U) / lU_NOM;
        m_lKcDeltaIy = i_l;
        i_l*=9;i_l/=10;//i *    
        if (j_l > i_l) {//Novyi New-made
            if(m_chDeltaIBus == 0 ){//if(m_chDeltaIBus == 0){
                wrp.bool_vars.PO_DeltaIbus = true;sLV.Ifix = Ip;m_chDeltaIBus = 1;
            }else{
                m_chDeltaIBus = 0;
            }    
        }
        else{
            i_l = CBGSig::m_chIdxGrupSamples;
            Ip =  *(static_cast<long*>(sLV.pv)+m_chNumberAnalogChanell+ (i_l*I_U*1) );
            //ArrBGSigDbgRec[uiIdxArrBGSigDbgRec].luIt_02 = sLV.Ip;
            sLV.Ip = Ip;
            if (Ii > Ip) {
                j_l = Ii - Ip;
            } else {
                j_l = Ip - Ii;
            }
            i_l = m_lKcDeltaIy;
            i_l*=9;i_l/=10;
            if (j_l > i_l) {//Novyi New-made
                //if(m_chDeltaIBus != i_l){
                if(m_chDeltaIBus == 0){
                    wrp.bool_vars.PO_DeltaIbus = true;sLV.Ifix = Ip;m_chDeltaIBus = 1;
                }else{
                m_chDeltaIBus = 0;
                }
            }else{
                m_chDeltaIBus = 0;//wrp.bool_vars.PO_DeltaIbus = false;// !!! Only for Dbg
            }
            
        }
            
            
       // boolWl = false;
    }while(boolWl);
    
     
    ArrBGSigDbgRec[uiIdxArrBGSigDbgRec].chDeltaIBUS = wrp.bool_vars.PO_DeltaIbus;
    if(TClrTrg(chTzatrState))
        ch_DTrg = 0;//Clear Trigger
    else if (ch_C1 == 0 && (wrp.bool_vars.PO_DeltaIbus) == 1) {
        ch_DTrg = 1;//DTrgInv = !ch_DTrg;
        
    }
    
    //wrp.bool_vars.DTrgInv = !ch_DTrg;
    rUl_2 = (~static_cast<unsigned long>(ch_DTrg))&1;
    //i++;//
    //i &= 1;
    wrp.bool_vars.DTrgInv = rUl_2;
    ArrBGSigDbgRec[uiIdxArrBGSigDbgRec].chD_notQ = wrp.bool_vars.DTrgInv;
    ch_C1 = wrp.bool_vars.PO_DeltaIbus;
    rUl_1 = (TElongation(wrp.bool_vars.DTrgInv));
    rUl_1 &= wrp.bool_vars.PO_DeltaIbus;
    //if(i && wrp.bool_vars.PO_DeltaIbus){
    if(rUl_1 != 0 && chTzatrState == 0){
        if (m_chWRIfix == 0) {//chTzatrState == 0 <-This is early code chahged to chTzatrState
                //m_lIfix =  sLV.Ip;//!????
                m_lIfix = sLV.Ifix; 
                m_chWRIfix = 1;
                m_lInew = sLV.Ii;//m_lIti
                wrp.bool_vars.PO_Ifix = true;
            };
    }else{
        ;//Clr Ifix Module
        m_chWRIfix = 0;//wrp.bool_vars.PO_Ifix = false;
    }
    ArrBGSigDbgRec[uiIdxArrBGSigDbgRec].chFixUnitIn = rUl_1 ;
    ArrBGSigDbgRec[uiIdxArrBGSigDbgRec].luIfix =  m_lIfix;
    if (ch_DTrg == 1 ) {//&& wrp.bool_vars.PO_Ifix
        long i_l,j_l, Iti;
        //!????Iti = measurement[m_chNumberAnalogChanell];<<== Error//
        Iti = sLV.Ii;
        if (Iti > m_lIfix) {
            j_l = Iti - m_lIfix;
        } else {
            j_l = m_lIfix - Iti;
        }
        //..i_l = (m_BGSigSuit.lIust * measurement[4]) / lU_NOM;
        i_l = (m_BGSigSuit.lIust * sLV.U) / lU_NOM;
        i_l *=9; i_l/=10;
        if (j_l > i_l){
            wrp.bool_vars.PO_DeltaIbusFix = rUl_1 = 1;//i_l = 1;
        }    
        else
            rUl_1 = 0;
        if (Iti > m_lInew) {
            j_l = Iti - m_lInew;
        } else {
            j_l = m_lInew - Iti;
        }
        //..i_l = (m_BGSigSuit.lIust * measurement[4]) / lU_NOM;
        i_l = (m_BGSigSuit.lIust * sLV.U) / lU_NOM;
        i_l *=9; i_l/=10;
        if (j_l > i_l){
            wrp.bool_vars.PO_DeltaIbusNew = 1;//i_l = 1;
        }    
        else
            rUl_2 = 0;
        //if(rUl_2 == 0 && rUl_1 == 0)
        //asm(
        //       "bkpt 1"
        //       );
        
    
    }
    
    ArrBGSigDbgRec[uiIdxArrBGSigDbgRec].chDeltaIFix = wrp.bool_vars.PO_DeltaIbusFix;
    rUl_1 = wrp.bool_vars.PO_DeltaIbusFix;
    rUl_1 |= wrp.bool_vars.PO_DeltaIbusNew;
    rUl_2 = (~rUl_1)&1;
    unnBF1.ushAr[0] |= (rUl_2) << BGS_NOT7_STATE_BIT;
    
    
    rUl_1 = (lTWait(rUl_1));
    //if()
    unnBF1.ulVal |= (rUl_1)<< BGS_TWAIT_STATE_BIT;
    chTzatrState = rUl_1;
    rUl_2 &= ch_DTrg;//(unnBF1.ulVal&( 1<< BGS_NOT7_STATE_BIT)) && ch_DTrg==1; 
    
    if(TClrTrg(rUl_1|rUl_2))
        ch_DTrg = 0;//Clear Trigger
        
    ArrBGSigDbgRec[uiIdxArrBGSigDbgRec].chD_In = ch_C1;
    ArrBGSigDbgRec[uiIdxArrBGSigDbgRec].chD_Clr = rUl_1|rUl_2;
    ArrBGSigDbgRec[uiIdxArrBGSigDbgRec].chD_Q  = ch_DTrg;//ArrBGSigDbgRec[uiIdxArrBGSigDbgRec].chD_notQ    
    
    rUl_1 = ( 1<< BGS_TWAIT_STATE_BIT);
    rUl_1 &= unnBF1.ulVal;
    rUl_2 =  (TImp6ms(rUl_1));
    //Inversion cmd
    rUl_1 = (~rUl_2)&1;
    unnBF1.ulVal |= rUl_1 << BGS_NOT26_STATE_BIT;
    sLV.chNotImp6ms = rUl_1;
    //if((unnBF1.ulVal&( 1<< BGS_TWAIT_STATE_BIT))&& m_chWRIp == 0){
    boolTzatr = chTzatrState;
    ArrBGSigDbgRec[uiIdxArrBGSigDbgRec].chTwaitOut = boolTzatr;
    if( boolTzatr && m_chWRIp == 0){
        long  lRamainderNNP, lRamainderNNC;
        m_lIp = m_lIfix;
        //m_lIc = measurement[m_chNumberAnalogChanell];//!???
        m_lIc = sLV.Ii;
        m_lIcMulUnom  = m_lIc*lU_NOM;
        m_lIpMulUnom  = m_lIp*lU_NOM;
        //..m_lIyMulU     = m_BGSigSuit.lIust * measurement[4];
        m_lIyMulU     = m_BGSigSuit.lIust * sLV.U;
        
        m_lNNC = ( m_lIcMulUnom )/(m_lIyMulU);//(m_lKcDeltaIy);
        m_lNNP = ( m_lIpMulUnom )/(m_lIyMulU);//(m_lKcDeltaIy);
        
        lRamainderNNC   = (m_lIcMulUnom) % m_lIyMulU;  //lRamainderNNC  = m_lIc % (m_lKcDeltaIy);
        if(lRamainderNNC>=(m_lIyMulU>>1))              //if(lRamainderNNC>=(m_lKcDeltaIy>>1))
            m_lNNC++;                                  //    m_lNNC++;
        lRamainderNNP  =  (m_lIpMulUnom )%(m_lIyMulU); //lRamainderNNP = m_lIp % (m_lKcDeltaIy);
        if(lRamainderNNP>=(m_lIyMulU>>1))              //if(lRamainderNNP>=(m_lKcDeltaIy>>1))
            m_lNNP++;                                  //    m_lNNP++;
        
        if (m_BGSigSuit.chCheckBgs > 0) {
            if(m_lNNC>0)
                m_lNNC--;
            //else{}
            if(m_lNNP>0)
                m_lNNP--;
            
            
        }  

        m_chWRIp = 1;
    
    }
    else {
        if ((unnBF1.ulVal&( 1<< BGS_TWAIT_STATE_BIT)) == 0)
        m_chWRIp = 0;
    }
    ArrBGSigDbgRec[uiIdxArrBGSigDbgRec].luIp  = m_lIp;
    ArrBGSigDbgRec[uiIdxArrBGSigDbgRec].luIc  = m_lIc;
    ArrBGSigDbgRec[uiIdxArrBGSigDbgRec].luNCC = m_lNNC;

//   rl_Val = (unnBF1.ulVal&( 1<< )|( 1<< ))!= 0; //OR operation
//   rl_Val = unnBF1.ulVal&(( 1<< )|( 1<< )) == ( 1<< )|( 1<< ); 
//   unnBF1.ulVal |= (rl_Val)<<  
    
    if(m_BGSigSuit.chStateGS){
        rUl_1 = 0;
        long d = m_lNNC - m_lNNP;
        if (d > 0){
            if(sLV.chNotImp6ms){
                rUl_1 = 1;
            }
        }else{
            rUl_2 = d;
        }
        rUl_2 =  (TImpNNP(rUl_1));
        arrOut[BGS_OUT_NAME_NNP - 1] = rUl_2;
        rUl_1 = 0;
        d = m_lNNP - m_lNNC;
        if (d > 0){
            if(sLV.chNotImp6ms){
                rUl_1 = 1;
            }
            
        }
        rUl_2 =  (TImpNNM(rUl_1));    
        arrOut[BGS_OUT_NAME_NNM - 1] = rUl_2;
        if (m_lNNC >= 1){
        
            arrOut[BGS_OUT_NAME_CC - 1] = 1;
        }    
        arrOut[BGS_OUT_NAME_NNC_INF-1] = m_lNNC;
        

        
        if (m_BGSigSuit.chCheckBgs > 0){
            rUl_2 = m_lKcDeltaIy;//(m_lKcDeltaIy*58981)>>16;
            rUl_2 *= 9;rUl_2 /= 10;
            
            if (measurement[m_chNumberAnalogChanell] <= static_cast<unsigned long>(rUl_2) ){//!???
                m_chStdpCE = 1;
            }
            else{
                rUl_2 *= 11;rUl_2 /= 10;
                if( (measurement[m_chNumberAnalogChanell] <= static_cast<unsigned long>(rUl_2))//!??? 
                &&  (m_chStdpCE == 1) )
                    m_chStdpCE = 1;
                else
                    m_chStdpCE = 0;
            }
            
            if( m_chStdpCE == 1)
                arrOut[BGS_OUT_NAME_CE - 1] = 1;
            else
                arrOut[BGS_OUT_NAME_CE - 1] = 0;
        }else{
            arrOut[BGS_OUT_NAME_CE - 1] = 0;
        }
        
        
        
        if (measurement[m_chNumberAnalogChanell] > 2000){//!???
            m_chStdpOV = 1;
            
        }
        else{
            if( (m_chStdpOV == 1) && (measurement[m_chNumberAnalogChanell] > 1800) )//!???
                m_chStdpOV = 1;
            else
                m_chStdpOV = 0;
        }
        
        if( m_chStdpOV == 1)
            arrOut[BGS_OUT_NAME_OC  - 1] = 1;
        else
            arrOut[BGS_OUT_NAME_OC  - 1] = 0;
            
    }
    else{
        arrOut[BGS_OUT_NAME_NNP - 1] = 0;
        arrOut[BGS_OUT_NAME_NNM - 1] = 0;
        arrOut[BGS_OUT_NAME_CC  - 1] = 0;
        arrOut[BGS_OUT_NAME_NNC_INF-1] = 0;
        arrOut[BGS_OUT_NAME_CE  - 1] = 0;
        arrOut[BGS_OUT_NAME_OC  - 1] = 0;
    }
    register __LN_GROUP_ALARM *pLN_GROUP_ALARM = static_cast<__LN_GROUP_ALARM *>(pvCfgLN);
    
   rUl_2 = 0;
    rUl_2 |= static_cast<bool>(arrOut[BGS_OUT_NAME_NNP -1])<<( GROUP_ALARM_OUT_NNP%8);
    rUl_2 |= static_cast<bool>(arrOut[BGS_OUT_NAME_NNM -1])<<( GROUP_ALARM_OUT_NNM%8);
    rUl_2 |= static_cast<bool>(arrOut[BGS_OUT_NAME_CC  -1])<<( GROUP_ALARM_OUT_CC %8);
    rUl_2 |= static_cast<bool>(arrOut[BGS_OUT_NAME_OC  -1])<<( GROUP_ALARM_OUT_OC %8);
    rUl_2 |= static_cast<bool>(arrOut[BGS_OUT_NAME_CE  -1])<<( GROUP_ALARM_OUT_CE %8);
    pLN_GROUP_ALARM->active_state[(GROUP_ALARM_OUT_OC /8) ] = rUl_2;
    pLN_GROUP_ALARM->NNC = 0;
    if(m_BGSigSuit.chStateGS){
         rUl_1 = m_lNNC;
        if(m_lNNC < 0)
            pLN_GROUP_ALARM->NNC = 0;//arrOut[BGS_OUT_NAME_NNC_INF-1];
        else
            pLN_GROUP_ALARM->NNC = rUl_1;//arrOut[BGS_OUT_NAME_NNC_INF-1];
    }    
    rUl_2 = 0;
    
    if(m_chStateTWait)
        rUl_2 |= 1;
   if(m_chStateTReset)
        rUl_2 |= 1<<1;//Be Careful you don`t difer bits of each LU
    if( (m_chSttElongation&3) != 3)
        rUl_2 |= 1<<2;
    if(m_chStt6MsImp)
        rUl_2 |= 1<<3;
    if(m_chSttImpNNP)
        rUl_2 |= 1<<4;
    if(m_chSttImpNNM)
        rUl_2 |= 1<<5;        
    rUl_1 = CBGSig::chNeedTimerCalculated;
    if(rUl_2>0)
        rUl_1 |= 1<<shShemasOrdNumStng;
    else
        rUl_1 &= ~(1<<shShemasOrdNumStng);
    CBGSig::chNeedTimerCalculated = rUl_1;//It`s Need for Call recalc because Timer work

}
void* pvCBGSigDbg;
/*
long CBGSig::EvalDeltaIbusFix(long Ibus, long Ifix, long lActive){
register long i;

    return 0;
}
long CBGSig::EvalIptp (long lI, long lT, long lActive){
register long i;

    return 0;
}
long CBGSig::EvalIctc (long lI, long lT, long lActive){
register long i;

    return 0;
}

long CBGSig::EvalNNC_NCH(long lActivate){
register long i;

    return 0;
}
long CBGSig::EvalNNP_NCH(long lActivate){
register long i;

    return 0;
}
long CBGSig::EvalNNC_CH (long lActivate){
register long i;

    return 0;
}
long CBGSig::EvalNNP_CH (long lActivate){
register long i;

    return 0;
}
long CBGSig::EvalCE (long lActivate){
register long i;

    return 0;
}
long CBGSig::EvalOC(void){
register long i;

    return 0;
}

long CBGSig::EvalNNP(long lNNC, long lNNP){
register long i;

    return 0;
}
long CBGSig::EvalNNM(long lNNC, long lNNP){
register long i;

    return 0;
}
long CBGSig::EvalNCC(long lNCC){
register long i;

    return 0;
}
*/



