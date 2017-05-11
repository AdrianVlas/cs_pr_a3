
#include "LUFKey.h"

CLUFKey::CLUFKey(void) {
}

CLUFKey::~CLUFKey(void) {
}

CLUFKey::CLUFKey(char chM,char chI) {
/*
memset(static_cast<void*>(arrPchIn),0xcc,sizeof(char*)*shCLULed_1_0_AmtIn);
    memset(static_cast<void*>(arrPchSchIn),0xcc,sizeof(char*)*TOTAL_LED_VISIO_IN);
    memset(static_cast<void*>(arrPchAlternator),0xcc,sizeof(char*)*2);
    memset(static_cast<void*>(arrOut),0,sizeof(char  )*TOTAL_LED_VISIO_OUTPUT);
    memset(static_cast<void*>(&m_LedCfgSuit),0,sizeof(LedCfgSuit));
*/
	chMaxIteratoin = chM;
	chIteration = chI;
//	chNumInput  = static_cast<char>(shCLULed_1_0_AmtIn);
	chNumOutput = static_cast<char>(shCLUFKey_x_y_AmtOut);
	for (long i = 0; i < chNumOutput; i++)
        arrOut[i] = 0;
    chKeyPres = 0;    
}

void FKey_Op(void *pObj){
long i;
	CLUFKey *pCLUFKey = static_cast<CLUFKey*>(pObj);
//find Index
i = pCLUFKey->shShemasOrdNumStng;
    i--;
    //Look State
    i = static_cast<char*>(pCLUFKey->pIn)[0];
    if(i!= 0)
    pCLUFKey->chKeyPres = i;
    pCLUFKey->arrOut[0] = i;
    //static_cast<char*>(pCLUFKey->pIn)[0];
}
