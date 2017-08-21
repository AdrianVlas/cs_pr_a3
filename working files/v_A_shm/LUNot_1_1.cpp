#ifdef VISUAL_STUDIO
#include "StdAfx.h"
#endif
#include "LUNot_1_1.h"
#include <string.h>
#include "IStng.h"

void NOT_Op_1_1    (void *pObj)
{
register bool bbl;
CLUNot_1_1& refCLUNot_1_1 = *(static_cast<CLUNot_1_1 *>(pObj));
//CLUNot_1_1 *pCLUNot_1_1 = (CLUNot_1_1*)pObj;
bbl = static_cast<bool>(!*(refCLUNot_1_1.arrPchIn[0]));
refCLUNot_1_1.arrOut[0] = static_cast<char>(bbl);
register __LN_NOT *pLN_NOT =  static_cast<__LN_NOT*>((reinterpret_cast<CLUNot_1_1 *> (pObj))->pvCfgLN);
    pLN_NOT->active_state[( STANDARD_LOGIC_OUT/8) ] = bbl<< STANDARD_LOGIC_OUT;

}
CLUNot_1_1::CLUNot_1_1(void):CLUBase()
{
}
CLUNot_1_1::CLUNot_1_1(char chM,char chI)//,LUOutDsc* pLUOutDsc)
{
register long i;	
	chMaxIteratoin = chM;
	chIteration = chI;
	chNumInput  = static_cast<char>(shCLUNot_1_1_AmtIn); 
	chNumOutput = static_cast<char>(shCLUNot_1_1_AmtOut);
	chTypeLogicFunction = LU_OP_NOT;
	LogicFunc  = NOT_Op_1_1;//NOT_Op;//???

	//Set Input parameters
	pIn = reinterpret_cast<void*>(arrPchIn);

	//Set OutPut parameters
	pOut = reinterpret_cast<void*>(arrOut);
for(i = 0; i < chNumInput;i++)
    arrPchIn[i] = reinterpret_cast<char*>(0xcccccccc);//&chGblGround;
	for(i = 0; i < chNumOutput;i++)
    arrOut[i] = 0;
}
CLUNot_1_1::~CLUNot_1_1(void)
{
}
