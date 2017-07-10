#pragma once
#include "lubase.h"
const short shCLUMFT_x_y_AmtOut = 1;
const short shCLUMFT_x_y_AmtIn  = 2;
#include "prtTmr.hpp"
#include "MftAuxDsc.h"
typedef struct MftSuit_tag{
char chTypeMft;
long lTpause;
long lTdelay;
long lTWork;
}MftSuit;

typedef struct TmrDsc_tag{
char *m_P__chStateTmr;
long *m_P__lTCmpVal;
long *m_P__lTmrVal;
}TmrDsc;



class CMft :
public CLUBase {
public:
    CMft(void);
    ~CMft(void);
    CMft(char chM,char chI);
    char* arrPchIn[TOTAL_MFT_IN ];//
    char  arrOut  [TOTAL_MFT_OUTPUT];//
    char  arrStateIn[TOTAL_MFT_IN ];
//    long TpauseMft(long lActivKey);
//    long TdelayMft(long lResetKey,long lInKey);
//    long TWorkMft (long lResetKey,long lInKey);
    long TPauseMftDir(long lActivKey);
    long TPauseMftInv(long lActivKey);
    long TDelayMftDir(long lResetKey, long lInKey);
    long TWorkMftDir(long lResetKey, long lInKey);
    long TWorkMftInv(long lResetKey, long lInKey);
    
    char m_chLinkedTimers; //Field bit
    char m_chStateTpauseDir;
    char m_chStateTpauseInv;

    char m_chStateTdelay;
    char m_chStateTWorkDir ;
    char m_chStateTWorkInv ;
    char m_chInPulsDir;
    char m_chInPulsInv;

    MftSuit m_MftSuit;
    TmrNode m_NodeTpauseDir;
    TmrNode m_NodeTpauseInv;

    TmrNode m_NodeTdelay;
    TmrNode m_NodeTWorkDir;
    TmrNode m_NodeTWorkInv;
    

    long LinkMftTimers(void);
    void UpdateCMft(void);
    friend long SetMftSuit(void* pv);
    friend void Mft_Op(void *pObj);
    friend long MftEvalTpauseTmr(long lActivKey,TmrDsc *pTmrDsc);
    friend long MftEvalTDelayTmr(long lActivKey,long lInKey,TmrDsc *pTmrDsc);
    friend long MftEvalTPulseTmr(long lActivKey,long lInKey,TmrDsc *pTmrDsc);
    
};

