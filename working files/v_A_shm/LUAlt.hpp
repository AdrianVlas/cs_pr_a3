#pragma once
#include "lubase.h"

#define SH_CLU_PULSE_ALTERNATOR_X_Y_AMT_IN 0

const short shCLUPulseAlternator_x_y_AmtOut = 1;
const short shCLUPulseAlternator_x_y_AmtIn  = SH_CLU_PULSE_ALTERNATOR_X_Y_AMT_IN;


#include "prtTmr.hpp"
typedef struct PulseAltSuit_tag{

short shTAlternator;//Number

}PulseAltCfgSuit;



class CPulseAlternator :
public CLUBase {
public:
    CPulseAlternator(void);
	CPulseAlternator(char chM,char chI); 
    ~CPulseAlternator(void);
#if (SH_CLU_PULSE_ALTERNATOR_X_Y_AMT_IN > 0)
    char* arrPchIn[shCLUPulseAlternator_x_y_AmtIn ]; //
    
#endif    
    char arrOut [shCLUPulseAlternator_x_y_AmtOut]; //
    long TAlt(long lActivKey);
    char m_chLinkedTimers; //Field bit
    char m_chStateT;
    PulseAltCfgSuit m_PulseAltCfgSuit;
    TmrNode m_NodeTicAlt;
    
    long LinkPulseAltTimer(void);
    void UpdateCPulseAlt(void);
    friend long SetPulseAltSuit(void* pv);
    friend void PulseAlt_Op(void *pObj);
};
extern void PulseAlt_Op(void *pObj);
