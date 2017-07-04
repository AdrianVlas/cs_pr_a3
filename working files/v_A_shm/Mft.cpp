#include <string.h>
#include "Mft.h"
#include "IStng.h"





char chMftCmpVal;


CMft::CMft(void):CLUBase() {
m_NodeTpauseDir.lTmrVal = 0;
m_NodeTpauseDir.next    = 0;
m_NodeTpauseInv.lTmrVal = 0;
m_NodeTpauseInv.next    = 0;

m_NodeTdelay.lTmrVal = 0;
m_NodeTdelay.next    = 0;

m_NodeTWorkDir .lTmrVal = 0;
m_NodeTWorkDir .next    = 0;
m_NodeTWorkInv .lTmrVal = 0;
m_NodeTWorkInv .next    = 0;

m_MftSuit.chTypeMft = 0;
m_MftSuit.lTpause   = 0;
m_MftSuit.lTdelay   = 0;
m_MftSuit.lTWork    = 0;

m_chLinkedTimers    = 0;

m_chStateTpauseDir   = 0;
m_chStateTpauseInv   = 0;
   
m_chStateTdelay      = 0;
m_chStateTWorkDir    = 0;
m_chStateTWorkInv    = 0;


}
CMft::CMft(char chM,char chI){
    chMaxIteratoin = chM;
    chIteration = chI;

chNumInput  = static_cast<char>(TOTAL_MFT_IN);//
chNumOutput = static_cast<char>(TOTAL_MFT_OUTPUT);



m_NodeTpauseDir.lTmrVal = 0;
m_NodeTpauseDir.next    = 0;
m_NodeTpauseInv.lTmrVal = 0;
m_NodeTpauseInv.next    = 0;

m_NodeTdelay.lTmrVal = 0;
m_NodeTdelay.next    = 0;

m_NodeTWorkDir .lTmrVal = 0;
m_NodeTWorkDir .next    = 0;
m_NodeTWorkInv .lTmrVal = 0;
m_NodeTWorkInv .next    = 0;

m_MftSuit.chTypeMft = 0;
m_MftSuit.lTpause   = 0;
m_MftSuit.lTdelay   = 0;
m_MftSuit.lTWork    = 0;

m_chLinkedTimers    = 0;

m_chStateTpauseDir   = 0;
m_chStateTpauseInv   = 0;
   
m_chStateTdelay      = 0;
m_chStateTWorkDir    = 0;
m_chStateTWorkInv    = 0;
chMftCmpVal = 123;
}
CMft::~CMft(void) {
}
void CMft::UpdateCMft(void) {
//Set Input parameters
pIn = static_cast<void*>(arrPchIn);
//Set OutPut parameters
pOut = static_cast<void*>(arrOut);
//LinkMftTimers();
//pInit2LcVarArea->pCLUBase->shShemasIdLUStng =  STNG_LU_NOT;

//Set Operation
//Set Type Operation
}
    

long CMft::TPauseMftDir(long lActivKey) {
    
    register long *plTmrVal = &m_NodeTpauseDir.lTmrVal;
    if (lActivKey) {
        if (m_chStateTpauseDir == 0) {
            lActivKey = m_MftSuit.lTpause; //Load Timer
            *plTmrVal = lActivKey;
            if (*plTmrVal != lActivKey)
                *plTmrVal = lActivKey; //Possible Clear in Int
            m_chStateTpauseDir = 1;
        } else {
            lActivKey = *plTmrVal;
            if (lActivKey == 0) {
                return 1; //End of Interval
            }
        }
        
    } else {
        ;
        m_chStateTpauseDir = 0;
        *plTmrVal = 0; //m_NodeTpause.lTmrVal = 0;
    }
    return 0;
}
long CMft::TPauseMftInv(long lActivKey) {
    
    register long *plTmrVal = &m_NodeTpauseInv.lTmrVal;
    if (lActivKey) {
        if (m_chStateTpauseInv == 0) {
            lActivKey = m_MftSuit.lTpause; //Load Timer
            *plTmrVal = lActivKey;
            if (*plTmrVal != lActivKey)
                *plTmrVal = lActivKey; //Possible Clear in Int
            m_chStateTpauseInv = 1;
        } else {
            lActivKey = *plTmrVal;
            if (lActivKey == 0) {
                return 1; //End of Interval
            }
        }
        
    } else {
        ;
        m_chStateTpauseInv = 0;
        *plTmrVal = 0; //m_NodeTpause.lTmrVal = 0;
    }
    return 0;
}

long CMft::TDelayMftDir(long lResetKey, long lInKey) {
    register long *plTmrVal = &m_NodeTdelay.lTmrVal;

    if (lResetKey == 0) {
        if (lInKey) {
            lInKey = m_MftSuit.lTdelay;
            *plTmrVal = lInKey;
            if (*plTmrVal != lInKey)
                *plTmrVal = lInKey; //lResetKey == 0!
            m_chStateTdelay = 1;//Activated
            return 1;
        
        } else {
            if (m_chStateTdelay == 1) {//Activated
                lInKey = *plTmrVal;
                if (lInKey != 0)
                    return 1; //
                else {
                    lResetKey = 1;
                }
            }

        }
    }
    if (lResetKey) {
        m_chStateTdelay = 0;
        *plTmrVal = 0;
    }
    return 0;
}

long CMft::TWorkMftDir(long lResetKey, long lInKey) {
    register long *plTmrVal = &m_NodeTWorkDir .lTmrVal;

    if (lResetKey == 0) {
        if (lInKey) {
            if (m_chStateTWorkDir == 0) {
                lInKey = m_MftSuit.lTWork;
                *plTmrVal = lInKey;
                if (*plTmrVal != lInKey)
                    *plTmrVal = lInKey;
                m_chStateTWorkDir = 1;
                return 1;
            } else {
                lInKey = *plTmrVal;
                if (lInKey != 0)
                    return 1; //
            }
        } else {
            if (m_chStateTWorkDir == 1) {//Activated
                lInKey = *plTmrVal;
                if (lInKey != 0)
                    return 1; //
                else
                    lResetKey = 1;
            }
        }
    }
    if (lResetKey) {
        m_chStateTWorkDir = 0;
        *plTmrVal = 0;
    }    
    return 0;
}
long CMft::TWorkMftInv(long lResetKey, long lInKey) {
    register long *plTmrVal = &m_NodeTWorkInv .lTmrVal;

    if (lResetKey == 0) {
        if (lInKey) {
            if (m_chStateTWorkInv == 0) {
                lInKey = m_MftSuit.lTWork;
                *plTmrVal = lInKey;
                if (*plTmrVal != lInKey)
                    *plTmrVal = lInKey;
                m_chStateTWorkInv = 1;
                return 1;
            } else {
                lInKey = *plTmrVal;
                if (lInKey != 0)
                    return 1; //
            }
        } else {
            if (m_chStateTWorkInv == 1) {//Activated
                lInKey = *plTmrVal;
                if (lInKey != 0)
                    return 1; //
                else
                    lResetKey = 1;
            }
        }
    }
    if (lResetKey) {
        m_chStateTWorkInv = 0;
        *plTmrVal = 0;
    }    
    return 0;
}

long CMft::LinkMftTimers(void) {
    register long i = 0;
    //Insert TpauseMft
    chGlSem++;
    
    if (PushTmrNode(&m_NodeTpauseDir)) {//static_cast<void*>(
        i++;
        m_chLinkedTimers |= 2;
    }
    //
    if (PushTmrNode(&m_NodeTpauseInv)) {//static_cast<void*>(
        i++;
        m_chLinkedTimers |= 4;
    }
    //
    if (PushTmrNode(&m_NodeTdelay)) {//static_cast<void*>(
        i++;
        m_chLinkedTimers |= 8;
    }
    if (PushTmrNode(&m_NodeTWorkDir)) {//static_cast<void*>(
        i++;
        m_chLinkedTimers |= 0x10;
    }
    if (PushTmrNode(&m_NodeTWorkInv)) {//static_cast<void*>(
        i++;
        m_chLinkedTimers |= 0x20;
    }
    
    
    chGlSem--;
    return i;
}


void Mft_Op(void *pObj){

    register long i, j,k;
    //register char* pCh;
    union{
    char  arChEC[4];
    short arrShEC[2];
    long  lEC;
    } U_EC;
    U_EC.lEC = 0;
    CMft& rCMft = *(static_cast<CMft*>(pObj));
     	if(rCMft.shShemasOrdNumStng == chMftCmpVal){
            asm(
            "bkpt 1"
            );
        }
        
    i = static_cast<long>(*(rCMft.arrPchIn[MFT_IN_NAME__MFTIN-1]));
    j = static_cast<long>(*(rCMft.arrPchIn[MFT_IN_NAME__RESET_I-1]));
    
                
    if(CLUBase::m_AuxInfo.ch > 0){
        U_EC.arChEC[0]++;
        //j = static_cast<long>(*(rCMft.arrPchIn[1]));
        if(j == rCMft.arrStateIn[MFT_IN_NAME__RESET_I-1]){
            U_EC.arChEC[0]++;
            if(i == rCMft.arrStateIn[MFT_IN_NAME__MFTIN-1])
                U_EC.arChEC[0]++;
            return;//May be not Operation    
        }    
        
    }
    
    rCMft.arrStateIn[MFT_IN_NAME__MFTIN-1]    = i;
    rCMft.arrStateIn[MFT_IN_NAME__RESET_I-1]  = j;   
    //--i = static_cast<long>(*(rCMft.arrPchIn[0]));
    j = rCMft.TPauseMftDir(i);
    k = rCMft.TPauseMftInv(!i);
    
    i = static_cast<long>(*(rCMft.arrPchIn[1]));//Reset

    rCMft.arrOut[MFT_OUT_NAME__MFT_IMP_DIR_OUT-1] = 
    rCMft.TWorkMftDir(i,j);
    rCMft.arrOut[MFT_OUT_NAME__MFT_DEL_OUT-1] = 
    rCMft.TDelayMftDir(i,j);
    rCMft.arrOut[MFT_OUT_NAME__MFT_IMP_INV_OUT-1] = 
    rCMft.TWorkMftInv(i,k);
   
register __LN_TIMER *pLN_TIMER = reinterpret_cast<__LN_TIMER*>(rCMft.pvCfgLN);
    i = rCMft.arrOut[MFT_OUT_NAME__MFT_IMP_DIR_OUT-1];
    j = rCMft.arrOut[MFT_OUT_NAME__MFT_DEL_OUT-1]    ;
    k = rCMft.arrOut[MFT_OUT_NAME__MFT_IMP_INV_OUT-1];
    
    pLN_TIMER->active_state[(TIMER_OUT_RISE_IMPULSE /8) ] = i<< ( TIMER_OUT_RISE_IMPULSE %8);
    pLN_TIMER->active_state[(TIMER_OUT_RISE_DELAY /8)   ] = j<< ( TIMER_OUT_RISE_DELAY   %8)  ;
    pLN_TIMER->active_state[(TIMER_OUT_FALL_IMPULSE /8) ] = k<< ( TIMER_OUT_FALL_IMPULSE %8);    
   

    
}

long MftEvalTpauseTmr(long lActivKey,TmrDsc *pTmrDsc) {
    
    register long *plTmrVal = pTmrDsc->m_P__lTmrVal;//&m_NodeTpause.lTmrVal;
    if (lActivKey) {
        if (*(pTmrDsc->m_P__chStateTmr) == 0) {//m_chStateTpause == 0
            //lActivKey = m_MftSuit.lTpause; //Load Timer m_MftSuit.lTpause;
            lActivKey = *(pTmrDsc->m_P__lTCmpVal); //
            *plTmrVal = lActivKey;
            if (*plTmrVal != lActivKey)
                *plTmrVal = lActivKey; //Possible Clear in Int
            //m_chStateTpause = 1;
            *(pTmrDsc->m_P__chStateTmr) = 1;
        } else {
            lActivKey = *plTmrVal;
            if (lActivKey == 0) {
                return 1; //End of Interval
            }
        }
        
    } else {
        ;
        *(pTmrDsc->m_P__chStateTmr) = 0;//m_chStateTpause = 0;
        *plTmrVal = 0; //m_NodeTpause.lTmrVal = 0;
    }
    return 0;
}


long TWorkMftMftEvalTPulseTmr(long lResetKey, long lInKey,TmrDsc *pTmrDsc) {
    register long *plTmrVal = pTmrDsc->m_P__lTmrVal;//&m_NodeTWork .lTmrVal;

    if (lResetKey == 0) {
        if (lInKey) {
            if (*(pTmrDsc->m_P__chStateTmr) == 0) {
                lInKey = *(pTmrDsc->m_P__lTCmpVal);//m_MftSuit.lTWork;
                *plTmrVal = lInKey;
                if (*plTmrVal != lInKey)
                    *plTmrVal = lInKey;
                *(pTmrDsc->m_P__chStateTmr) = 1;
                return 1;
            } else {
                lInKey = *plTmrVal;
                if (lInKey != 0)
                    return 1; //
            }
        } else {
            if (*(pTmrDsc->m_P__chStateTmr) == 1) {//Activated
                lInKey = *plTmrVal;
                if (lInKey != 0)
                    return 1; //
                else
                    lResetKey = 1;
            }
        }
    }
    if (lResetKey) {
        *(pTmrDsc->m_P__chStateTmr) = 0;
        *plTmrVal = 0;
    }    
    return 0;
}
long MftEvalTDelayTmr(long lResetKey, long lInKey,TmrDsc *pTmrDsc) {
    register long *plTmrVal = pTmrDsc->m_P__lTmrVal;

    if (lResetKey == 0) {
        if (lInKey) {
            lInKey = *(pTmrDsc->m_P__lTCmpVal);//m_MftSuit.lTdelay;
            *plTmrVal = lInKey;
            if (*plTmrVal != lInKey)
                *plTmrVal = lInKey; //lResetKey == 0!
            *(pTmrDsc->m_P__chStateTmr) = 1;//Activated
            return 1;
        
        } else {
            if (*(pTmrDsc->m_P__chStateTmr) == 1) {//Activated
                lInKey = *plTmrVal;
                if (lInKey != 0)
                    return 1; //
                else {
                    lResetKey = 1;
                }
            }

        }
    }
    if (lResetKey) {
        *(pTmrDsc->m_P__chStateTmr) = 0;
        *plTmrVal = 0;
    }
    return 0;
}
/*
long CMft::TpauseMft__00(long lActivKey) {
    
    register long *plTmrVal = &m_NodeTpause.lTmrVal;
    if (lActivKey) {
        if (m_chStateTpause == 0) {
            lActivKey = m_MftSuit.lTpause; //Load Timer
            *plTmrVal = lActivKey;
            if (*plTmrVal != lActivKey)
                *plTmrVal = lActivKey; //Possible Clear in Int
            m_chStateTpause = 1;
        } else {
            lActivKey = *plTmrVal;
            if (lActivKey == 0) {
                return 1; //End of Interval
            }
        }
        
    } else {
        ;
        m_chStateTpause = 0;
        *plTmrVal = 0; //m_NodeTpause.lTmrVal = 0;
    }
    return 0;
}
*/
/*
long CMft::TdelayMft__00(long lResetKey, long lInKey) {
    register long *plTmrVal = &m_NodeTdelay.lTmrVal;
	
    if (lResetKey == 0) {
        if (lInKey) {
            lInKey = m_MftSuit.lTdelay;
            *plTmrVal = lInKey;
            if (*plTmrVal != lInKey)
                *plTmrVal = lInKey; //lResetKey == 0!
			m_chStateTdelay = 1;//Activated
            return 1;
       	
        } else {
            if (m_chStateTdelay == 1) {//Activated
                lInKey = *plTmrVal;
                if (lInKey != 0)
                    return 1; //
                else {
                    lResetKey = 1;
                }
            }

        }
    }
    if (lResetKey) {
        m_chStateTdelay = 0;
        *plTmrVal = 0;
    }
    return 0;
}
*/
/*
long CMft::TdelayMftInv(long lResetKey, long lInKey) {
    register long *plTmrVal = &m_NodeTdelay.lTmrVal;
	
    if (lResetKey == 0) {
        if (lInKey) {
            lInKey = m_MftSuit.lTdelay;
            *plTmrVal = lInKey;
            if (*plTmrVal != lInKey)
                *plTmrVal = lInKey; //lResetKey == 0!
			m_chStateTdelay = 1;//Activated
            return 1;
       	
        } else {
            if (m_chStateTdelay == 1) {//Activated
                lInKey = *plTmrVal;
                if (lInKey != 0)
                    return 1; //
                else {
                    lResetKey = 1;
                }
            }

        }
    }
    if (lResetKey) {
        m_chStateTdelay = 0;
        *plTmrVal = 0;
    }
    return 0;
}
*/

/*
long CMft::LinkMftTimers__00(void) {
    register long i = 0;
    //Insert TpauseMft
    chGlSem++;
    
    if (PushTmrNode(&m_NodeTpause)) {//static_cast<void*>(
        i++;
        m_chLinkedTimers |= 2;
    }
    //Insert TdelayMft
    if (PushTmrNode(&m_NodeTdelay)) {//static_cast<void*>(
        i++;
        m_chLinkedTimers |= 4;
    }
    //Insert TWorkMft 
    if (PushTmrNode(&m_NodeTWork)) {//static_cast<void*>(
        i++;
        m_chLinkedTimers |= 8;
    }
    chGlSem--;
    return i;
}
*/
/*
void Mft_OpOld(void *pObj){

    register long i, j;
    //register char* pCh;
	CMft& rCMft = *(static_cast<CMft*>(pObj));
	i = static_cast<long>(*(rCMft.arrPchIn[0]));
	j = rCMft.TpauseMft(i);
	i = static_cast<long>(*(rCMft.arrPchIn[1]));//Reset
	if(rCMft.m_MftSuit.chTypeMft == 1){
		
		i = rCMft.TWorkMft(i,j);
	}
	else{
		i = rCMft.TdelayMft(i,j);
	}
rCMft.arrOut[0] = static_cast<char>(i);
}
*/

