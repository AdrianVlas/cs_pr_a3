#ifdef VISUAL_STUDIO
#include "StdAfx.h"
#endif
#include "LUXor_8_1.h"
#include <string.h>
#include "IStng.h"

void XOR_Op_8_1(void *pObj) {
    register bool bbl;
    CLUXor_8_1& refCLUXor = *(static_cast<CLUXor_8_1 *> (pObj));
    bbl = static_cast<bool>(*(refCLUXor.arrPchIn[0])^*(refCLUXor.arrPchIn[1]));
    refCLUXor.arrOut[0] = static_cast<char>(bbl);
        
    register __LN_XOR *pLN_XOR =  static_cast<__LN_XOR*>((reinterpret_cast<CLUXor_8_1 *> (pObj))->pvCfgLN);
    pLN_XOR->active_state[( STANDARD_LOGIC_OUT/8) ] = bbl<< STANDARD_LOGIC_OUT;
}

CLUXor_8_1::CLUXor_8_1(void) {
}

CLUXor_8_1::CLUXor_8_1(char chM, char chI)//,LUOutDsc* pLUOutDsc)
{
    chMaxIteratoin = chM;
    chIteration = chI;
    chNumInput = static_cast<char> (shCLUXor_2_1_AmtIn);
    chNumOutput = static_cast<char> (shCLUXor_2_1_AmtOut);
    chTypeLogicFunction = LU_OP_NOT;
    LogicFunc = NOT_Op; //???

    //Set Input parameters
    //	pIn  = reinterpret_cast<void*>(arrPchIn);
    //	pOut = reinterpret_cast<void*>( arrOut );
    //Set OutPut parameters

}

CLUXor_8_1::~CLUXor_8_1(void) {
}

