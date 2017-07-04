#include <string.h>
#include "LUTestLed.h"

extern void GetLUTestLedInDataAddr(void* pv);


CLUTestLed::CLUTestLed(void) {
    memset(static_cast<void*> (arrPchIn),    0xcc, sizeof (char*)*TOTAL_TEST_LED_IN);
    memset(static_cast<void*> (m_arChQTrg), 0, sizeof (char)*TEST_LED_OUT_NAME_TLED22);
    memset(static_cast<void*> (m_arChInC), 0, sizeof (char)*TEST_LED_OUT_NAME_TLED22);
    memset(static_cast<void*> (arrOut),        0, sizeof (char)*TOTAL_TEST_LED_OUTPUT);
    memset(static_cast<void*> (&m_NodeTicAltZp5ms), 0, sizeof (TmrNode));
    memset(static_cast<void*> (&m_Node1_1Ms), 0, sizeof (TmrNode));
m_chOutGen = m_chLinkedTimers = 0;
 
 m_chStateT1_1Ms = m_chStateAltZp5ms = 0;
//    chMaxIteratoin = chM;
//    chIteration = chI;
    chNumInput  = static_cast<char>(TOTAL_TEST_LED_IN);//shCLULed_1_0_AmtIn
    chNumOutput = static_cast<char>(TOTAL_TEST_LED_OUTPUT);//shCLULed_1_0_AmtOut



//Set Input parameters
pIn = static_cast<void*>(arrPchIn);//Set OutPut parameters
pOut = static_cast<void*>(arrOut);
}

CLUTestLed::~CLUTestLed(void) {
}


void CLUTestLed::UpdateCLUTestLed(void) {
TestLedInOutParam lcTestLedInOutParam = {arrPchIn[(TEST_LED_IN_NAME__TEST_K-1)],arrPchIn[(TEST_LED_IN_NAME__RESET_I-1)]};

//Find Obj for TEST sig

//Find Obj for RESET-TEST operation
GetLUTestLedInDataAddr(static_cast<void*>( &lcTestLedInOutParam));
arrPchIn[(TEST_LED_IN_NAME__TEST_K-1)]  = lcTestLedInOutParam.pChTest ;
arrPchIn[(TEST_LED_IN_NAME__RESET_I-1)] = lcTestLedInOutParam.pChReset;
}
long CLUTestLed::LinkTestLedTimers(void) {
    register long i = 0;
    //Insert TpauseMft
    chGlSem++;
    
    if (PushTmrNode(&m_Node1_1Ms)) {//static_cast<void*>(
        i++;
        m_chLinkedTimers |= 2;
    }
    //Insert TdelayMft
    if (PushTmrNode(&m_NodeTicAltZp5ms)) {//static_cast<void*>(
        i++;
        m_chLinkedTimers |= 4;
    }
    
    chGlSem--;
    return i;
}

long CLUTestLed::TAltZp5ms(long lActivKey){
register long *plTmrVal = &m_NodeTicAltZp5ms.lTmrVal;
bool bbState = false;
    long lReInit = 0;
  
    lActivKey = *plTmrVal;
    if (lActivKey == 0)
    lReInit = 1; 
if (lReInit) {
    bbState = !(m_chStateAltZp5ms & 2); //m_chStateAltZp5msdelay = 0;
    m_chStateAltZp5ms &= ~2;
    m_chStateAltZp5ms |= bbState << 1;

    *plTmrVal = (500/7);
    
    }
    return (m_chStateAltZp5ms & 2) >> 1;    
}

long CLUTestLed::T1_1Ms(long lActivKey){

register long *plTmrVal = &m_Node1_1Ms.lTmrVal;
register long lResetKey = 0;
    if (lActivKey) {
        if (m_chStateT1_1Ms == 0) {
            lActivKey = 1;//m_chStateT1_1Ms
            *plTmrVal = lActivKey;
            if (*plTmrVal != lActivKey)
                *plTmrVal = lActivKey;
            m_chStateT1_1Ms = 1;
            return 1;
        } else {
            lActivKey = *plTmrVal;
            if (lActivKey != 0)
                return 1; //
        }
    } else {
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
char chIdxLed = 0;
char chTest_K = 0;
void CLUTestLed::CalCLUTestLedSchematic(void){
register long i,j;
 long lZp5secAlt;

j = m_chStateAltZp5ms;
lZp5secAlt = TAltZp5ms(m_chStateAltZp5ms);

    if( *(arrPchIn[(TEST_LED_IN_NAME__RESET_I-1)]) == 1 ){
        chTest_K = chIdxLed = 0;
        memset(static_cast<void*>(arrOut),0,TOTAL_TEST_LED_OUTPUT);
        //void *memset(void *s, int c, size_t n);


    }
    
//Check Activate --> Set Test-M & reinit Index
    if( (*(arrPchIn[(TEST_LED_IN_NAME__TEST_K-1)]) == 1) ){
        if( chTest_K == 0){
            if(chIdxLed){
                arrOut[chIdxLed] = 0;
                chIdxLed = 0;
            }    
            arrOut[TEST_LED_OUT_NAME_TEST_M] = 1;
            chTest_K = 1;
        }
    }
    else
        chTest_K = 0;    
    if(arrOut[TEST_LED_OUT_NAME_TEST_M] == 1)
    {
    
        ;//Check 0.5 Sec
        if(j == 0 && lZp5secAlt>0){
        
            i = chIdxLed;
            if(i == 0){
                i = TEST_LED_OUT_NAME_TLED00;
                arrOut[i] = lZp5secAlt;
            }
            else{//Clr Previous
                arrOut[i] = 0;
                i++;
                if(i>TEST_LED_OUT_NAME_TLED22){
                    i = 0;//chIdxLed = 0;
                    arrOut[TEST_LED_OUT_NAME_TEST_M] = 0;
                }
                else{
                    arrOut[i] = 1;
                    
                }
                
            }
        chIdxLed = i;    
        }
    }
//


}

