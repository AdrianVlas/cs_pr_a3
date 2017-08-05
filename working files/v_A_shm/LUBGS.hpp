#pragma once
#include "lubase.h"
const short shCLUBGSig_x_y_AmtOut = 1;
const short shCLUBGSig_x_y_AmtIn  = 0;
const long lU_NOM = 220000;
#include "prtTmr.hpp"
#include "BgsAux.h"
#include <stdint.h>
#include "../inc/const_measurement.h"
#include "../inc/const_global.h"
extern volatile unsigned long measurement_DBG[10];
extern unsigned int measurement[];
typedef struct BgsSuit_tag{
char chStateGS;
char chCheckBgs;
long lTWait;
//long lTReset;
long lIust;
}BGSigSuit;



class CBGSig :
public CLUBase {
public:
    CBGSig(void);
    ~CBGSig(void);
    //CBGSig(CBGSig&);
    CBGSig(char chM, char chI);
    void CalcBusGrSigSchematicDbg(void);
    void CalcBusGrSigSchematic(void);
    long lTWait(long lActivKey);
    long lTReset(long lActivKey);
    char* arrPchIn[TOTAL_BGS_VISIO_IN]; //
    char arrOut [TOTAL_BGS_VISIO_OUT]; //Tra
static char m_chCounterCall;
static char m_chIdxGrupSamples;
static char chAlreadyCalculated;
static char chNeedTimerCalculated;
static char chMeasUpdateInterval;

static unsigned int  meas  [NUMBER_ANALOG_CANALES]; 
static unsigned int  DMeas        [NUMBER_ANALOG_CANALES]; 
static unsigned int  PickUPs      [NUMBER_ANALOG_CANALES]; 
static unsigned char ChanelsNames [NUMBER_ANALOG_CANALES]; 
static unsigned int  measbuf[3][I_U]; 

    char m_chLinkedTimers; //Field bit
    char m_chStateTWait;
    char m_chStateTReset;
    char m_chNumberAnalogChanell;
	char m_chWRIfix,m_chIfixDir;
    char m_chStdpCE, m_chStdpOV ;
	char m_chWRIp;
	char m_chWRIc;
	char m_chWR_NNC;
	char m_chWR_NNP;
	 char ch_DTrg;
     char ch_C1;
    BGSigSuit m_BGSigSuit;
    TmrNode m_NodeTWait;
    TmrNode m_NodeTReset;
    long m_lMeasIti_mn_1,m_lKcDeltaIy;
    long m_lNNC,m_lNNP;
    long m_lIfix,m_lIp,m_lIc;
    long LinkBGSigTimers(void);
    void UpdateCBGSig(void);
    //long Ibus, long lTinterval
    long EvalDeltaIbus(void); //Ibus- Current for check lTinterval - IntervalTime
    long EvalDeltaIbusDbg(void); //Ibus- Current for check lTinterval - IntervalTime
    long EvalDeltaIbus(void *pv); //Ibus- Current for check lTinterval - IntervalTime
    long EvalDeltaIbusDbg(void *pv); //Ibus- Current for check lTinterval - IntervalTime
    
    //long StoreIfixTimeFix(long lTime, long lIbus, long lActive);
    long EvalDeltaIbusFix(long Ibus, long Ifix, long lActive);
    long EvalIptp(long lI, long lT, long lActive);
    long EvalIctc(long lI, long lT, long lActive);
	
//    long EvalNNC_NCH(long lActivate);
//    long EvalNNP_NCH(long lActivate);
//    long EvalNNC_CH(long lActivate);
//    long EvalNNP_CH(long lActivate);
//    long EvalCE(long lActivate);
//    long EvalOC(void);
//    long EvalNNP(long lNNC, long lNNP);
//    long EvalNNM(long lNNC, long lNNP);
//    long EvalNCC(long lNCC);
    
    friend long SetBGSigSuit(void* pv);
    friend void BGSig_Op(void *pObj);
};

extern void BGSig_Op(void *pObj);
extern unsigned long *PMeas;


