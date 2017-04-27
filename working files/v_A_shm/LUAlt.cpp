
#include "LUAlt.hpp"
#include <string.h>
CPulseAlternator::CPulseAlternator(void) :CLUBase() {
m_chLinkedTimers = 0; //Field bit
m_chStateT       = 0;
m_PulseAltCfgSuit.shTAlternator = 0;
m_NodeTicAlt.lTmrVal = 0;
m_NodeTicAlt.next    = 0;

}

CPulseAlternator::~CPulseAlternator(void) {
}


CPulseAlternator::CPulseAlternator(char chM,char chI)  {
    chMaxIteratoin = chM;
    chIteration = chI;
    m_chLinkedTimers = 0; //Field bit
    m_chStateT = 0;
    m_PulseAltCfgSuit.shTAlternator = 0;
    m_NodeTicAlt.lTmrVal = 0;
    m_NodeTicAlt.next = 0;
//chNumInput  = static_cast<char>(shCLUPulseAlternator_x_y_AmtIn);//
chNumOutput = static_cast<char>(shCLUPulseAlternator_x_y_AmtOut);
	
}
void CPulseAlternator::UpdateCPulseAlt(void){
//Set Input parameters
pIn = static_cast<void*>(arrPchIn);
//Set OutPut parameters
pOut = static_cast<void*>(arrOut);
for(long i = 0; i < chNumInput;i++)
arrOut[i] = 0;
//LinkMftTimers();
//pInit2LcVarArea->pCLUBase->shShemasIdLUStng =  STNG_LU_NOT;
;
//Set Operation
//Set Type Operation
}
long CPulseAlternator::LinkPulseAltTimer(void) {
    register long i = 0;
    //Insert TpauseMft
    chGlSem++;
    
    if (PushTmrNode(&m_NodeTicAlt)) {//static_cast<void*>(
        i++;
        m_chLinkedTimers |= 2;
    }

    
    chGlSem--;
    return i;
}
long CPulseAlternator::TAlt(long lActivKey){
  
    register long *plTmrVal = &m_NodeTicAlt.lTmrVal;
//    if (lActivKey) {
//	
//	} else {
//        ;
//        m_chStateT = 0;
//        *plTmrVal = 0; //m_NodeTpause.lTmrVal = 0;
//    }
//    return 0;
    bool bbState = false;
    long lReInit = 0;
  
    lActivKey = *plTmrVal;
    if (lActivKey == 0)
    lReInit = 1;    
if (lReInit) {
    bbState = !(m_chStateT & 2); //m_chStateTdelay = 0;
    m_chStateT &= ~2;
    m_chStateT |= bbState << 1;

    *plTmrVal = m_PulseAltCfgSuit.shTAlternator;
    
    }
    return (m_chStateT & 2) >> 1;
}
void PulseAlt_Op(void *pObj){

    register long i, j;

    CPulseAlternator& rPulseAlt = *(static_cast<CPulseAlternator*> (pObj));
    j = rPulseAlt.arrOut[0];
    i = rPulseAlt.TAlt(j);
	
rPulseAlt.arrOut[0] = static_cast<char>(i);

}
