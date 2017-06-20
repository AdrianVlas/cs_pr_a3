#ifdef VISUAL_STUDIO
#include "StdAfx.h"
#endif
#include "LUAnd_8_1.h"
#include "IStng.h"

void AND_Op_8_1(void *pObj) {
    register long i, j;
    register char* pCh;

    for (i = 0 , j = 1; i < 8; i++) {
        pCh = (static_cast<CLUAnd_8_1*> (pObj))->arrPchIn[i];
        if (pCh[0] == 0) {
            j = 0;
            break;
        }
    }
    (reinterpret_cast<CLUAnd_8_1 *> (pObj))->arrOut[0] = static_cast<char> (j);
     register __LN_AND *pLN_AND; 
        pLN_AND = static_cast<__LN_AND*>((reinterpret_cast<CLUAnd_8_1 *> (pObj))->pvCfgLN);
    pLN_AND->active_state[( STANDARD_LOGIC_OUT/8) ] = j<< STANDARD_LOGIC_OUT;
    
}
void AND_Opp_8_1(void *pObj) {
    register long i, j;
    //register char* pCh;

//    for (i = 0, pCh = (static_cast<CLUAnd_8_1*> (pObj))->arrPchIn[0], j = 1; i < 8; i++) {
//        if (pCh[i] == 0) {
//            j = 0;
//            break;
//        }
//    }
    i = 0; j = 1;
    //pCh = (static_cast<CLUAnd_8_1*> (pObj))->arrPchIn[i];
    j &= *((static_cast<CLUAnd_8_1*> (pObj))->arrPchIn[i++]);//1
    j &= *((static_cast<CLUAnd_8_1*> (pObj))->arrPchIn[i++]);//2
    j &= *((static_cast<CLUAnd_8_1*> (pObj))->arrPchIn[i++]);//3
    j &= *((static_cast<CLUAnd_8_1*> (pObj))->arrPchIn[i++]);//4
    j &= *((static_cast<CLUAnd_8_1*> (pObj))->arrPchIn[i++]);//5
    j &= *((static_cast<CLUAnd_8_1*> (pObj))->arrPchIn[i++]);//6
    j &= *((static_cast<CLUAnd_8_1*> (pObj))->arrPchIn[i++]);//7
    j &= *((static_cast<CLUAnd_8_1*> (pObj))->arrPchIn[i]);//8
    (reinterpret_cast<CLUAnd_8_1 *> (pObj))->arrOut[0] = static_cast<char> (j);
}

CLUAnd_8_1::CLUAnd_8_1(void) : CLUBase() {
}

CLUAnd_8_1::CLUAnd_8_1(char chM, char chI){
    chMaxIteratoin = chM;
    chIteration = chI;
    chNumInput = static_cast<char> (shCLUAnd_8_1_AmtIn); //(char)8;
    chNumOutput = static_cast<char> (shCLUAnd_8_1_AmtOut);


    //Set Input parameters
    //pIn =arrPchIn;

    //Set OutPut parameters
    //pOut =arrOut;
}

CLUAnd_8_1::~CLUAnd_8_1(void) {
}
