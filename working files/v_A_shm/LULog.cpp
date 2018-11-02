
#include "LULog.hpp"
#include "IStng.h"
#include "I_Shm.h"
CLULog::CLULog(void) {
}

CLULog::~CLULog(void) {
}


CLULog::CLULog(char chM,char chI) {
	chMaxIteratoin = chM;
	chIteration = chI;
    chNumOutput = static_cast<char>(shCLULog_x_y_AmtOut);
	for (long i = 0; i < chNumOutput; i++)
        arrOut[i] = 0;
}


/*
*((_LOG_INPUT*)spca_of_p_prt[ID_FB_EVENT_LOG - _ID_FB_FIRST_VAR]) |=
 (_LOG_INPUT)(1 << EVENT_LOG_WORK);
 
if(
	(*((__LOG_INPUT*)spca_of_p_prt[ID_FB_EVENT_LOG - ID_FB_FIRST_VAR])) 
	& ((_LOG_INPUT)(1 << EVENT_LOG_WORK))
)
{
YE syhnal
}
else
{
Nemye syhnal
}

*/

void Log_Op(void *pObj){
long i;
__LOG_INPUT l1;
__LOG_INPUT *pLOG_INPUT; 
	CLULog *pCLULog = static_cast<CLULog*>(pObj);
//find Index
i = pCLULog->shShemasOrdNumStng;
    i--;
    //Look State

// *((_LOG_INPUT*)spca_of_p_prt[ID_FB_EVENT_LOG - _ID_FB_FIRST_VAR]) |=
//  (_LOG_INPUT)(1 << EVENT_LOG_WORK);
//  
pLOG_INPUT = reinterpret_cast<__LOG_INPUT*>(
spca_of_p_prt[ID_FB_EVENT_LOG - _ID_FB_FIRST_VAR]);
//l1 = *pLOG_INPUT;
l1 = static_cast<__LOG_INPUT>(1 << EVENT_LOG_WORK);
 if( (l1&(*pLOG_INPUT)) != 0)
 {
    pCLULog->arrOut[0] = 1;// Fix Sig
 }
 else
 {
    pCLULog->arrOut[0] = 0;// No Sig
 }
//    
    
    
}
void CLULog::UpdateCLULog(void){

//Set OutPut parameters
pOut = static_cast<void*>(arrOut);

}






