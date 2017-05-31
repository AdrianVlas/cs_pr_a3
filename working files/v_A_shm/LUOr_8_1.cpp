#ifdef VISUAL_STUDIO
#include "StdAfx.h"
#endif
#include "LUOr_8_1.h"
#include <string.h>

void OR_Op_8_1(void *pObj) {
    //CLUOr_8_1 *pCLUOr_8_1 = (CLUOr_8_1*)pObj;
    register long i, j;
    register char* pCh;
    for (i = 0, j = 0; i < 8; i++) {
        pCh = (static_cast<CLUOr_8_1*> (pObj))->arrPchIn[i];
        if (pCh[0] == 1) {
            j = 1;
            break;
        }
    }

    (reinterpret_cast<CLUOr_8_1 *> (pObj))->arrOut[0] = static_cast<char> (j);
}
void OR_Opp_8_1(void *pObj) {
    //CLUOr_8_1 *pCLUOr_8_1 = (CLUOr_8_1*)pObj;
    register long i, j;
    i = 0; j = 0;
    //pCh = (static_cast<CLUAnd_8_1*> (pObj))->arrPchIn[i];
    j |= *((static_cast<CLUOr_8_1*> (pObj))->arrPchIn[i++]);//1
    j |= *((static_cast<CLUOr_8_1*> (pObj))->arrPchIn[i++]);//2
    j |= *((static_cast<CLUOr_8_1*> (pObj))->arrPchIn[i++]);//3
    j |= *((static_cast<CLUOr_8_1*> (pObj))->arrPchIn[i++]);//4
    j |= *((static_cast<CLUOr_8_1*> (pObj))->arrPchIn[i++]);//5
    j |= *((static_cast<CLUOr_8_1*> (pObj))->arrPchIn[i++]);//6
    j |= *((static_cast<CLUOr_8_1*> (pObj))->arrPchIn[i++]);//7
    j |= *((static_cast<CLUOr_8_1*> (pObj))->arrPchIn[i]);//8
    (reinterpret_cast<CLUOr_8_1 *> (pObj))->arrOut[0] = static_cast<char> (j);
}

CLUOr_8_1::CLUOr_8_1(void) {
}

CLUOr_8_1::CLUOr_8_1(char chM, char chI){
    chMaxIteratoin = chM;
    chIteration = chI;
    chNumInput = static_cast<char> (shCLUOr_8_1_AmtIn);
    chNumOutput = static_cast<char> (shCLUOr_8_1_AmtOut);
    chTypeLogicFunction = LU_OP_NOT;
    LogicFunc = NOT_Op; //???

    //Set Input parameters
    //pIn = reinterpret_cast<void*>(arrPchIn);

    //Set OutPut parameters
    //pOut = reinterpret_cast<void*>(arrOut);
}

CLUOr_8_1::~CLUOr_8_1(void) {
}

/*
#pragma inline=forced

#pragma optimize=[
*/



