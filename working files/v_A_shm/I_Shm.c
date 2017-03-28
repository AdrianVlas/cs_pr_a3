
#include "IStng.h"
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
    register long i, lRes, lCtrElem;
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

    return i;
}

//#include "../inc/variables_external.h" зараз поки що не йде


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