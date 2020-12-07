#include "I_Shm.h"
#include "IStng.h"
#include "prtTmr.h"
#include "Tim9.c"
//""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
//``````````````````````````````````````````````````````````````````````````````````
//==================================================================================
//--- 			 Interface function for CPP Schematic     -----------
//==================================================================================
//..................................................................................
//""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
//~~~  
//~~~  
//~~~  
//~~~  
//~~~  
//~~~  
//~~~  
//~~~  
//,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,
//""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
/*
#include "header.h"
#include "../inc/libraries.h"
extern __CONFIG current_config_prt; 
 __CONFIG ccfg;
*/


char chGlb_ActivatorWREeprom = 0;

char chGlbAmountRegisteredElem = 0;
long lGlbRegisteredElemField = 0;
const char chAmtSchematicElement = 15;//
fnPvrL arrChangeCfgFnptr[16] = {
(fnPvrL)0,//00
(fnPvrL)0,//01
(fnPvrL)0,//02
(fnPvrL)0,//03
(fnPvrL)0,//04
(fnPvrL)0,//05
(fnPvrL)0,//06
(fnPvrL)0,//07
(fnPvrL)0,//08
(fnPvrL)0,//09
(fnPvrL)0,//10
(fnPvrL)0,//11
(fnPvrL)0,//12
(fnPvrL)0,//13
(fnPvrL)0,//14
(fnPvrL)0//15
//16
};

long ChangeCfg(void* pv){
    register long i, lRes, lCtrElem, lVl;

	lVl = InitSchematic();
    lRes = i = 0;
    lCtrElem = chGlbAmountRegisteredElem;
    if (lCtrElem)
    {
        do
        {
            while ((lGlbRegisteredElemField & (1 << i) == 0) && (i < chGlbAmountRegisteredElem))
                i++;
            lRes = (arrChangeCfgFnptr[i])(pv);
        } while (--lCtrElem > 0 && lRes == 0);
    }
  TIM9Stop();
  TIM9_Init();
  
  TIM9Start();
  DoCalcWrp();
  TIM9Stop();
  i = TIM_GetCounter(TIM9);
  //lCtrElem = i*417/10000;
  lCtrElem = i*834/10000;
  //lCtrElem = i*660/10000;
  TIM_SetCounter(TIM9,0);
    TIM9Start();
  //DoCalcStatInfoWrp();
  TIM9Stop();
  //Out Param in Terminal
  
    return lVl;
}

// long RegisterHundlerLUCfg(void* pv){
 const long TIM9_BASE_CPP = TIM9_BASE;

// return 0;

// }
/*
long ChangeCfgLULed(void* pv){
register void* pvO;
register long i;
volatile 
struct{
void *pVOrigin;
char *pCh;
short shRelativeIndexLU;
}sLv;
sLv.pVOrigin = pv;
pvO = (void*)((LUCfgInfo*)pv)->pvCfgSuit;
//Get Index Current LU
//sLv.shRelativeIndexLU = ((LUCfgInfo*)pv)->shRelativeIndexLU;
//((__LN_TIMER*)spca_of_p_prt[ID_FB_TIMER - _ID_FB_FIRST_VAR] + (number_logical_node - 1))->settings.param[index]
//p_param = &(((__LN_TIMER*)spca_of_p_prt[ID_FB_TIMER - _ID_FB_FIRST_VAR] + (number_logical_node - 1))->settings.param[index]);
//
//            unsigned int id_input   = (param >> SFIFT_PARAM_ID ) & MASKA_PARAM_ID ;//Typ Funktsionalnoho bloku
//            unsigned int n_input    = (param >> SFIFT_PARAM_N  ) & MASKA_PARAM_N  ;//Poryadkovyy nomer
//            unsigned int out_input  = (param >> SFIFT_PARAM_OUT) & MASKA_PARAM_OUT;//Nomer vykhodu //
sLv.pCh = (char*)( spca_of_p_prt[ID_FB_LED - _ID_FB_FIRST_VAR]);
sLv.pCh += sLv.shRelativeIndexLU * sizeof(__LN_OUTPUT_LED);


return 0;
}
*/
extern DICfgSuit sDiCfg;
long lIdxWr = 0;
unsigned char arChInRg[20000] @ "ZeroInivars_RAM1";
void CheckingDIRegs(void){
while(1){	
	//Read Data from Reg Then Save It
	;
	;
	RdHrdIn((void*)&DiHrdStateUI32Bit);
    UpdateStateDI(); 
	arChInRg[lIdxWr++] = sDiCfg.DiState.ul_val;
	if(lIdxWr >= 20000){
		lIdxWr = 0;
		asm volatile(
                "bkpt 1"
                );
	}
	
}

}
//#include "../inc/variables_external.h" zaraz poky shcho ne yde


//""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
//---
//extern char GetCmdStateVcs(void *p_in_param);
//..................................................................................
//""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
//~~~                             
//~~~                             
//``````````````````````````````````````````````````````````````````````````````````
//~~~   
//~~~   
//,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,
//""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
///////////////////////////////////////////////////////////////////////////////////
//=================================================================================
//Body func                                                                
//=================================================================================
//char GetCmdStateVcs(void *p_in_param)
//{
//    register I32 i; 
//	
//}
//----------------------------------------------------------------------------------
