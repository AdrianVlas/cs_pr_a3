
#include "LUBGS.hpp"
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

volatile unsigned long measurement_DBG[10] = {
0,0,0,0,90000,0,0,0,0,0,
};
unsigned long *PMeas = const_cast<unsigned long*>(&measurement_DBG[0]);


CBGSig::CBGSig(void):CLUBase()  {
m_NodeTWait.lTmrVal  = 0;
m_NodeTWait.next     = 0;
m_NodeTReset.lTmrVal = 0;
m_NodeTReset.next    = 0;

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

m_BGSigSuit.chStateGS  = 0;
m_BGSigSuit.chCheckBgs = 0;
m_BGSigSuit.lTWait     = 0;
//m_BGSigSuit.lTReset    = 0;
m_chLinkedTimers = 0; //Field bit
m_chStateTWait   = 0;
m_chStateTReset  = 0;
m_lIfix = m_lMeasIti_mn_1 = m_lKcDeltaIy = 0;
 m_lNNC = m_lNNP = m_lIp = m_lIc = 0;
m_chNumberAnalogChanell = 0;
 m_chWRIfix = 0;m_chIfixDir = 0;
 m_chWRIp   = 0;
 m_chWRIc   = 0;
 m_chWR_NNC = 0;
 m_chWR_NNP = 0;
m_chStdpCE = m_chStdpOV = 0;

ch_DTrg = 0;
ch_C1 = 0;


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

long CBGSig::lTReset(long lActivKey) {
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
    //rCBGSig.CalcBusGrSigSchematicDbg();
    rCBGSig.CalcBusGrSigSchematic();
    }
//    else{
//        rCBGSig.m_chCounterCall = ++i;
//    }
    
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
    if(lTReset(bbT1ms))
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
void CBGSig::CalcBusGrSigSchematic(void) {
    register long  rl_Val,i;
    register long  lRamainderNNP, lRamainderNNC;
//#pragma data_alignment=4 
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
        
        if (m_BGSigSuit.chCheckBgs == 0) {

            m_lNNC = ( m_lIcMulUnom )/(m_lIyMulU);//(m_lKcDeltaIy);
            m_lNNP = ( m_lIpMulUnom )/(m_lIyMulU);//(m_lKcDeltaIy);
            
            lRamainderNNC   = (m_lIcMulUnom) % m_lIyMulU;  //lRamainderNNC  = m_lIc % (m_lKcDeltaIy);
            if(lRamainderNNC>=(m_lIyMulU>>1))              //if(lRamainderNNC>=(m_lKcDeltaIy>>1))
                m_lNNC++;                                  //    m_lNNC++;
            lRamainderNNP  =  (m_lIpMulUnom )%(m_lIyMulU); //lRamainderNNP = m_lIp % (m_lKcDeltaIy);
            if(lRamainderNNP>=(m_lIyMulU>>1))              //if(lRamainderNNP>=(m_lKcDeltaIy>>1))
                m_lNNP++;                                  //    m_lNNP++;

            
            
        } else {
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
        }

        m_chWRIp = 1;
	
    }
    else {
        if (bbTDelay == false)
        m_chWRIp = false;
    }
    bbT1ms = bbTDelay || ((!bbDeltaItminusIf) &&(ch_DTrg == 1));
    if(lTReset(bbT1ms))
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



