#ifdef VISUAL_STUDIO
#include "StdAfx.h"
#endif
#include <stdlib.h>
#include "Shematic.h"
#include "stm32f2xx.h"
#include "BaseInPoint.h"
#include "InPoint.h"
#include "ExtPoint.h"
#include "LUBase.h"
#include "LUNot_1_1.h"
#include "LUDInput_0_1.h"
#include "LUDout_1_0.h"
#include "LUDInput_0_1.h"
#include "LULed.h"
#include "LUAnd_8_1.h"
#include "LUOr_8_1.h"
#include "LUXor_8_1.h"
#include "Mft.h"
#include "LULss.h"
#include "LUFKey.h"
#include "LUBGS.hpp"
#include "LUTrig.hpp"
#include "LUAlt.hpp"
#include "LUTu.h"
//#include <conio.h>
#include <string.h>
#include <ctime>
//#include "stng.h"
#include "IStng.h"
#include "I_Shm.h"

#include "MALed.hpp"
#include "RunErLed.hpp"
#include "LUTestLed.h"
#include "LULog.hpp"
#include "FixblWrp.hpp"
#include "StatInfo.h"
//#include "../inc/variables_external.h"
//#include "../inc/libraries.h"


void DiOp(void *pObj);
void DoOp(void *pObj);
void LedOp(void *pObj);
void ButtonOp(void *pObj);
void LssOptim(void *pObj);
void BGSOp(void *pObj);
void AndOp(void *pObj);
void OrOp(void *pObj);
void XorOp(void *pObj);
void NotOp(void *pObj);
void MftOp(void *pObj);
void TrgOp(void *pObj);
void AltOp(void *pObj);
void TuOp(void *pObj);


//#pragma inline
void Shematic::DoCalcLUSources(void){

 register long i,j,lAmtProcessObj;
 void* pv;
register LUAreaListElem*pLUAreaListElem;
short *parIdxLUAreaListElem;
// struct {
//     short shAmountCalcLU, shRes;
//     void *pV;
//     LUAreaListElem* arrLUAreaListElem;
//     CLUBase* pCLUBase;//
// } sLV;
//    sLV.shAmountCalcLU = gblLUAreaAuxVar.shAmountPlacedLogicUnit;
//    sLV.arrLUAreaListElem = &gLUAreaMem.headLUAreaList;
    //pLUAreaListElem = static_cast<LUAreaListElem*>(this->pLUAreaList);
    pLUAreaListElem = static_cast<LUAreaListElem*>(pLUAreaList);

    parIdxLUAreaListElem = arIdxLUAreaListElem;

    lAmtProcessObj = (static_cast<__CONFIG* >(p_current_config_prt))->n_input; //current_config_prt.n_input;
//////////////////////////////////////////////////////////////////
    short shCounterInitCLUDout = 0;
    i = parIdxLUAreaListElem[LU_INPUT-1];//Get Obj List Index
    
    while (shCounterInitCLUDout < lAmtProcessObj ) {
            j = i + shCounterInitCLUDout;
           // pv = (pLUAreaListElem[j]).pvLU;
           // READ_DI_Op(pv);//DiOp
            READ_DI_Op( pLUAreaListElem[j].pvLU );//DiOp
            shCounterInitCLUDout++;
    } 
/////////////////////////////////////////////////////////////////
    lAmtProcessObj = (static_cast<__CONFIG* >(p_current_config_prt))->n_button;
    shCounterInitCLUDout = 0;
    i = parIdxLUAreaListElem[LU_FKEY-1];        
    do {
            j = i + shCounterInitCLUDout;
            pv = (pLUAreaListElem[j]).pvLU;
            ButtonOp(pv);
    } while (++shCounterInitCLUDout < lAmtProcessObj );
//////////////////////////////////////////////////////////////////
    lAmtProcessObj = (static_cast<__CONFIG* >(p_current_config_prt))-> n_meander;   
    shCounterInitCLUDout = 0;
    i = parIdxLUAreaListElem[LU_MEANDERS-1];
    while (shCounterInitCLUDout < lAmtProcessObj ) {
            j = i + shCounterInitCLUDout;
            pv = (pLUAreaListElem[j]).pvLU;
            AltOp(pv);
            shCounterInitCLUDout++;
            
    } 
//////////////////////////////////////////////////////////////////  
    lAmtProcessObj = (static_cast<__CONFIG* >(p_current_config_prt))-> n_group_alarm;
    shCounterInitCLUDout = 0;
    CBGSig::chAlreadyCalculated = 0;
    i = parIdxLUAreaListElem[LU_BGS-1];
    while (shCounterInitCLUDout < lAmtProcessObj ) {
            j = i + shCounterInitCLUDout;
            pv = (pLUAreaListElem[j]).pvLU;
            BGSig_Op(pv);
            shCounterInitCLUDout++;
            
    }
CBGSig::chAlreadyCalculated = 1;    
//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////  
    i = parIdxLUAreaListElem[LU_LOG-1];
    // j = i + shCounterInitCLUDout;
    pv = (pLUAreaListElem[i]).pvLU;
    Log_Op(pv);  
/*

*/ 
//////////////////////////////////////////////////////////////////        
//    lAmtProcessObj = (static_cast<__CONFIG* >(p_current_config_prt))-> n_tu;
//    long lIdxCounter = 0;
//    i = parIdxLUAreaListElem[LU_TU-1];
//    
//    while (lIdxCounter < lAmtProcessObj ) {
//            j = i + lIdxCounter++;
//            pv = (pLUAreaListElem[j]).pvLU;
//            TuOp(pv);            
//    } 



}
//#pragma inline 
void Shematic::LUSelector( long lIdxLU){
register void* pv;
register LUAreaListElem*pLUAreaListElem;
#pragma calls=  Mft_Op, XOR_Op_8_1,TU_Op,DTRG_Op_4_2,OR_Op_8_1,NOT_Op_1_1,LssOp,Log_Op,SET_LED_Op,FKey_Op,SET_OUT_Op,READ_DI_Op,BGSig_Op,AND_Op_8_1,PulseAlt_Op
pLUAreaListElem = static_cast<LUAreaListElem*>(this->pLUAreaList);
pv = (pLUAreaListElem[lIdxLU]).pvLU;
(static_cast<CLUBase*>( pv))->LogicFunc( pv);
    
}
void* Shematic::LUSelectorRV( long lIdxLU){//Selector Return Value
register void* pv;
register LUAreaListElem*pLUAreaListElem;
#pragma calls=  Mft_Op, XOR_Op_8_1,TU_Op,DTRG_Op_4_2,OR_Op_8_1,NOT_Op_1_1,LssOp,Log_Op,SET_LED_Op,FKey_Op,SET_OUT_Op,READ_DI_Op,BGSig_Op,AND_Op_8_1,PulseAlt_Op
pLUAreaListElem = static_cast<LUAreaListElem*>(this->pLUAreaList);
pv = (pLUAreaListElem[lIdxLU]).pvLU;
(static_cast<CLUBase*>( pv))->LogicFunc( pv);
    return pv;
}
//    while (sLV.shAmountCalcLU--) {
//        pv = static_cast<void*>( &sLV.arrLUAreaListElem[i]);
//        sLV.pCLUBase = static_cast<CLUBase*>( (static_cast<LUAreaListElem*> (pv))->pvLU);//(CLUBase*)
//        pv = static_cast<void*>( sLV.pCLUBase); //->LogicFunc;
//       if ((static_cast<CLUBase*>( pv))->LogicFunc != Null_OP) {
//                        (static_cast<CLUBase*>( pv))->LogicFunc( reinterpret_cast<void*>(sLV.pCLUBase));
//                    }
//    }
//#pragma inline

void Shematic::LUIterator(long AmountCalcLU, long lIdxLU){
register void* pv;
register LUAreaListElem*pLUAreaListElem;

pLUAreaListElem = static_cast<LUAreaListElem*>(this->pLUAreaList);
//parIdxLUAreaListElem = arIdxLUAreaListElem;
    while (AmountCalcLU--) {
        pv = (pLUAreaListElem[lIdxLU++]).pvLU;
      #pragma calls=  FBWrp_Op, Mft_Op, XOR_Op_8_1,TU_Op,DTRG_Op_4_2,OR_Op_8_1,NOT_Op_1_1,LssOp,Log_Op,SET_LED_Op,FKey_Op,SET_OUT_Op,READ_DI_Op,BGSig_Op,AND_Op_8_1,PulseAlt_Op             
        (static_cast<CLUBase*>( pv))->LogicFunc( pv);
    }
}
void Shematic::LUIteratorStatInfo(long AmountCalcLU, long lIdxLU){
register void* pv;
register LUAreaListElem*pLUAreaListElem;

 CLUBase *pCLUBase;
 UNN_LUExecRec *pUNN_LUExecRec;
 long lVl;

pLUAreaListElem = static_cast<LUAreaListElem*>(this->pLUAreaList);
//parIdxLUAreaListElem = arIdxLUAreaListElem;
    while (AmountCalcLU--) {
        pv = (pLUAreaListElem[lIdxLU++]).pvLU;
        
        pCLUBase = static_cast<CLUBase*>(pv );//pLUAreaListElem[j].pvLU
        lVl = CLUBase::m_AuxInfo.ch;//pCLUBase ->chIteration;
        pUNN_LUExecRec = &(pCLUBase ->unnLUStatInfoData.arLUExecInfo[lVl]);
        
        pUNN_LUExecRec->hldrLUExecInfo.shTIMStartedVal = (reinterpret_cast<TIM_TypeDef *>( TIM9_BASE_CPP))->CNT;//TIM_GetCounter(TIM9);
      #pragma calls=  FBWrp_Op, Mft_Op, XOR_Op_8_1,TU_Op,DTRG_Op_4_2,OR_Op_8_1,NOT_Op_1_1,LssOp,Log_Op,SET_LED_Op,FKey_Op,SET_OUT_Op,READ_DI_Op,BGSig_Op,AND_Op_8_1,PulseAlt_Op             
        (static_cast<CLUBase*>( pv))->LogicFunc( pv);
        pUNN_LUExecRec->hldrLUExecInfo.shTIMTerminatedVal = (reinterpret_cast<TIM_TypeDef *>( TIM9_BASE_CPP))->CNT;  
    
    }
}

#include "Sch_Aux.cpp"
extern char chStateOptimisation;
void Shematic::DoCalcLU(void){
register union {
short* pOrderCalcNum;
char  *pCh;
}P;
long lAmtProcessObj,lIdxCounter;
long i,j;
//    TmrCalls();    
//    UpdateStateDI();
if(chStateOptimisation == 2)
   asm volatile(
       "bkpt 1"
       );
    DoCalcLUSources();
    P.pCh = const_cast<char*>(arrChCalcLUOrderNumsSchmPage2);

    lAmtProcessObj = sizeof(arrChCalcLUOrderNumsSchmPage2)>>1;
    lIdxCounter = 0;
    do {
        i = P.pOrderCalcNum[lIdxCounter];
        j = i >> 8;
        i &= 0xff;
        i += arIdxLUAreaListElem[j-1];
        LUSelector(i);
    } while (++lIdxCounter < lAmtProcessObj );
    i = arIdxLUAreaListElem[LU_OUTPUT-1];
    LUIterator((static_cast<__CONFIG* >(p_current_config_prt))->n_output,i);//
}





//`extern DICfgSuit sDiCfg;
//`void DiOp(void *pObj){
//`    long i;
//`    CLUDInput_0_1 *pCLUDInput_0_1 = static_cast<CLUDInput_0_1 *> (pObj);
//`    i = pCLUDInput_0_1->shShemasOrdNumStng;
//`    i--;
//`i = sDiCfg.DiState.ul_val;
//`    //if (DiHrdStateUI32Bit.ul_val & (1 << i))
//`    if (sDiCfg.DiState.ul_val & (1 << i))
//`        pCLUDInput_0_1->arrOut[0] = 1; //static_cast<char>(pCLUDInput_0_1->shLUBieldOrdNum);//Any value from Input
//`    else
//`        pCLUDInput_0_1->arrOut[0] = 0;
//`}
extern const long TIM9_BASE_CPP;// = TIM9_BASE;
//#pragma inline
void Shematic::DoCalcLUSourcesStatInfo(void){

 register long i,j,lAmtProcessObj;
 void* pv;
register LUAreaListElem*pLUAreaListElem;
short *parIdxLUAreaListElem;
 CLUBase *pCLUBase;
 UNN_LUExecRec *pUNN_LUExecRec;
 long lVl;

    pLUAreaListElem = static_cast<LUAreaListElem*>(pLUAreaList);

    parIdxLUAreaListElem = arIdxLUAreaListElem;

    lAmtProcessObj = (static_cast<__CONFIG* >(p_current_config_prt))->n_input; //current_config_prt.n_input;
//////////////////////////////////////////////////////////////////
    short shCounterInitCLUDout = 0;
    i = parIdxLUAreaListElem[LU_INPUT-1];//Get Obj List Index
    
    while (shCounterInitCLUDout < lAmtProcessObj ) {
            j = i + shCounterInitCLUDout;

            
            pCLUBase = static_cast<CLUBase*>(pLUAreaListElem[j].pvLU );
            lVl = pCLUBase ->chIteration;
            pUNN_LUExecRec = &(pCLUBase ->unnLUStatInfoData.arLUExecInfo[lVl]);
            
            pUNN_LUExecRec->hldrLUExecInfo.shTIMStartedVal = (reinterpret_cast<TIM_TypeDef *>( TIM9_BASE_CPP))->CNT;//TIM_GetCounter(TIM9);
            
            READ_DI_Op( pLUAreaListElem[j].pvLU );//DiOp
            pUNN_LUExecRec->hldrLUExecInfo.shTIMTerminatedVal = (reinterpret_cast<TIM_TypeDef *>( TIM9_BASE_CPP))->CNT;  
            
            shCounterInitCLUDout++;
    } 
/////////////////////////////////////////////////////////////////
    lAmtProcessObj = (static_cast<__CONFIG* >(p_current_config_prt))->n_button;
    shCounterInitCLUDout = 0;
    i = parIdxLUAreaListElem[LU_FKEY-1];        
    do {
            j = i + shCounterInitCLUDout;
            pv = (pLUAreaListElem[j]).pvLU;
            pCLUBase = static_cast<CLUBase*>(pLUAreaListElem[j].pvLU );
            lVl = pCLUBase ->chIteration;
            pUNN_LUExecRec = &(pCLUBase ->unnLUStatInfoData.arLUExecInfo[lVl]);
            
            pUNN_LUExecRec->hldrLUExecInfo.shTIMStartedVal = (reinterpret_cast<TIM_TypeDef *>( TIM9_BASE_CPP))->CNT;//TIM_GetCounter(TIM9);
                      
            ButtonOp(pv);
            pUNN_LUExecRec->hldrLUExecInfo.shTIMTerminatedVal = (reinterpret_cast<TIM_TypeDef *>( TIM9_BASE_CPP))->CNT;  
    } while (++shCounterInitCLUDout < lAmtProcessObj );
//////////////////////////////////////////////////////////////////
    lAmtProcessObj = (static_cast<__CONFIG* >(p_current_config_prt))-> n_meander;   
    shCounterInitCLUDout = 0;
    i = parIdxLUAreaListElem[LU_MEANDERS-1];
    while (shCounterInitCLUDout < lAmtProcessObj ) {
            j = i + shCounterInitCLUDout;
            pv = (pLUAreaListElem[j]).pvLU;
            pCLUBase = static_cast<CLUBase*>(pLUAreaListElem[j].pvLU );
            lVl = pCLUBase ->chIteration;
            pUNN_LUExecRec = &(pCLUBase ->unnLUStatInfoData.arLUExecInfo[lVl]);
            pUNN_LUExecRec->hldrLUExecInfo.shTIMStartedVal = (reinterpret_cast<TIM_TypeDef *>( TIM9_BASE_CPP))->CNT;//TIM_GetCounter(TIM9);
            
            AltOp(pv);
            pUNN_LUExecRec->hldrLUExecInfo.shTIMTerminatedVal = (reinterpret_cast<TIM_TypeDef *>( TIM9_BASE_CPP))->CNT;  
            shCounterInitCLUDout++;
            
    } 
//////////////////////////////////////////////////////////////////  
    lAmtProcessObj = (static_cast<__CONFIG* >(p_current_config_prt))-> n_group_alarm;
    shCounterInitCLUDout = 0;
    CBGSig::chAlreadyCalculated = 0;
    i = parIdxLUAreaListElem[LU_BGS-1];
    while (shCounterInitCLUDout < lAmtProcessObj ) {
            j = i + shCounterInitCLUDout;
            pv = (pLUAreaListElem[j]).pvLU;
            pCLUBase = static_cast<CLUBase*>(pLUAreaListElem[j].pvLU );
            lVl = pCLUBase ->chIteration;
            pUNN_LUExecRec = &(pCLUBase ->unnLUStatInfoData.arLUExecInfo[lVl]);
            
            pUNN_LUExecRec->hldrLUExecInfo.shTIMStartedVal = (reinterpret_cast<TIM_TypeDef *>( TIM9_BASE_CPP))->CNT;//TIM_GetCounter(TIM9);
                  
            BGSig_Op(pv);
            pUNN_LUExecRec->hldrLUExecInfo.shTIMTerminatedVal = (reinterpret_cast<TIM_TypeDef *>( TIM9_BASE_CPP))->CNT;              
            shCounterInitCLUDout++;
            
    }
CBGSig::chAlreadyCalculated = 1;    
//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////  
    i = parIdxLUAreaListElem[LU_LOG-1];
    // j = i + shCounterInitCLUDout;
    pv = (pLUAreaListElem[i]).pvLU;
    pCLUBase = static_cast<CLUBase*>(pv );//pLUAreaListElem[j].pvLU
    lVl = pCLUBase ->chIteration;
    pUNN_LUExecRec = &(pCLUBase ->unnLUStatInfoData.arLUExecInfo[lVl]);
    pUNN_LUExecRec->hldrLUExecInfo.shTIMStartedVal = (reinterpret_cast<TIM_TypeDef *>( TIM9_BASE_CPP))->CNT;//TIM_GetCounter(TIM9);
        
    Log_Op(pv);  
    pUNN_LUExecRec->hldrLUExecInfo.shTIMTerminatedVal = (reinterpret_cast<TIM_TypeDef *>( TIM9_BASE_CPP))->CNT;  


}

void DoOp(void *pObj){
    CLUDout_1_0& refCLUDout_1_0 = *(static_cast<CLUDout_1_0*> (pObj));
refCLUDout_1_0.CalcReleySchematic();
}
void LedOp(void *pObj){
CLULed& rCLULed = *(static_cast<CLULed*> (pObj));
rCLULed.CalcLedSchematic();    
}
//#pragma inline
void ButtonOp(void *pObj){
long i;
CLUFKey *pCLUFKey = static_cast<CLUFKey*>(pObj);
i = static_cast<char*>(pCLUFKey->pIn)[0];
    if(i!= 0)
    pCLUFKey->chKeyPres = i;
 //   if(i == 0)
 //   i = pCLUFKey->chKeyPres;
    pCLUFKey->arrOut[0] = i;    
}

void LssOptip(void *pObj){
CLULss& rCLULss = *(static_cast<CLULss*>(pObj));

rCLULss.CalcLssSchematic();	    
}
void BGSOp(void *pObj){
CBGSig& rCBGSig = *(static_cast<CBGSig*> (pObj));
rCBGSig.CalcBusGrSigSchematic();    
}
void AndOp(void *pObj){
register long i, j;
register char* pCh;
    i = 0;
    do{
        pCh = (static_cast<CLUOr_8_1*> (pObj))->arrPchIn[i++];
        j = pCh[0];
    }while((j != 0) && (i < 8));
//    for (i = 0, pCh = (static_cast<CLUAnd_8_1*> (pObj))->arrPchIn[0], j = 1; i < 8; i++) {
//        if (pCh[i] == 0) {
//            j = 0;
//            break;
//        }
//    }
(reinterpret_cast<CLUAnd_8_1 *> (pObj))->arrOut[0] = static_cast<char> (j);

}
void OrOp(void *pObj){
    register long i, j;
    register char* pCh;
    i = 0;
    do{
        pCh = (static_cast<CLUOr_8_1*> (pObj))->arrPchIn[i++];
        j = pCh[0];
    }while((j == 0) && (i < 8));
    

    (reinterpret_cast<CLUOr_8_1 *> (pObj))->arrOut[0] = static_cast<char> (j);
    
}
void XorOp(void *pObj){
CLUXor_8_1& refCLUXor = *(static_cast<CLUXor_8_1 *> (pObj));
    refCLUXor.arrOut[0] = *(refCLUXor.arrPchIn[0])^*(refCLUXor.arrPchIn[1]);    
}
void NotOp(void *pObj){
CLUNot_1_1& refCLUNot_1_1 = *(static_cast<CLUNot_1_1 *>(pObj));
refCLUNot_1_1.arrOut[0] = !*(refCLUNot_1_1.arrPchIn[0]);    
}
void MftOp(void *pObj){
    register long i;
    //register char* pCh;, j
	CMft& rCMft = *(static_cast<CMft*>(pObj));
	i = static_cast<long>(*(rCMft.arrPchIn[0]));
//	j = rCMft.TpauseMft(i);
//	i = static_cast<long>(*(rCMft.arrPchIn[1]));//Reset
//	if(rCMft.m_MftSuit.chTypeMft == 1){
//		
//		i = rCMft.TWorkMft(i,j);
//	}
//	else{
//		i = rCMft.TdelayMft(i,j);
//	}
rCMft.arrOut[0] = static_cast<char>(i);    
}
void TrgOp(void *pObj){
CLUTrig& refCLUDTrg = *(static_cast<CLUTrig *> (pObj));
    long k, j, l; //
    //char *pCh;
    k = 0;
//    if(chGBL_BP_StopLUTrig == refCLUDTrg.shShemasOrdNumStng)
//    asm volatile(
//                "bkpt 1"
//                );

    if (*(refCLUDTrg.arrPchIn[DTRG__4_2_IN_NAME__SET - 1])) //{
        k |= 1; //} 

    //pCh = refCLUDTrg.arrPchIn[DTRG__4_2_IN_NAME__CLR - 1];
    if (*(refCLUDTrg.arrPchIn[DTRG__4_2_IN_NAME__CLR - 1]))//{
        k |= 2; //}
    

    if (k == 0) {
    l = *(refCLUDTrg.arrPchIn[DTRG__4_2_IN_NAME__C_SLASH - 1]);
        if (refCLUDTrg.chIn_C == 0 && l > 0) {
        j = *(refCLUDTrg.arrPchIn[DTRG__4_2_IN_NAME__D - 1]);
            if ( j) {
                //set
                refCLUDTrg.arrOut[DTRG__4_2_OUT_NAME_Q - 1] = 1;
                refCLUDTrg.arrOut[DTRG__4_2_OUT_NAME_Q_INV - 1] = 0;
                refCLUDTrg.chQ = 1;
            }
            else{
                ;
                refCLUDTrg.arrOut[DTRG__4_2_OUT_NAME_Q - 1] = 0;
                refCLUDTrg.arrOut[DTRG__4_2_OUT_NAME_Q_INV - 1] = 1;
                refCLUDTrg.chQ = 0;
            }
        }
    } else
        if (k == 1) {
        refCLUDTrg.chQ = 1;
        //refCLUDTrg.chIn_C = 0;//
        refCLUDTrg.arrOut[DTRG__4_2_OUT_NAME_Q - 1] = 1;
        refCLUDTrg.arrOut[DTRG__4_2_OUT_NAME_Q_INV - 1] = 0;
    } else
        if (k == 2) {
        refCLUDTrg.chQ = 0;
        //refCLUDTrg.chIn_C = 0;//
        refCLUDTrg.arrOut[DTRG__4_2_OUT_NAME_Q - 1] = 0;
        refCLUDTrg.arrOut[DTRG__4_2_OUT_NAME_Q_INV - 1] = 1;
        
    } else if (k == 3) {
        refCLUDTrg.chError = 1;
        
    }
refCLUDTrg.chIn_C = *(refCLUDTrg.arrPchIn[DTRG__4_2_IN_NAME__C_SLASH - 1]);    
}
short shBkptIdAlt;
void AltOp(void *pObj){
    register long i, j;

    CPulseAlternator& rPulseAlt = *(static_cast<CPulseAlternator*> (pObj));
    j = rPulseAlt.arrOut[0];
        if(shBkptIdAlt == rPulseAlt.shShemasOrdNumStng)
   asm volatile(
       "bkpt 1"
       );
    i = rPulseAlt.TAlt(j);
	
rPulseAlt.arrOut[0] = static_cast<char>(i);
    register __LN_MEANDER *pLN_MEANDER = static_cast<__LN_MEANDER*>(rPulseAlt.pvCfgLN);
    pLN_MEANDER->active_state[( MEANDER_OUT/8) ] = i<< MEANDER_OUT;    
}
#pragma inline=forced
void TuOp(void *pObj){
long i;
	CLUTu *pCLUTu = static_cast<CLUTu*>(pObj);
//find Index
i = pCLUTu->shShemasOrdNumStng;
    i--;
    pCLUTu->arrOut[0] = 0;
}
#define MAX_AMOUNT_LINK_ITERATION 3
//Optimization Module Nazar
void Shematic::DoCalcLU_V01(void){
register union {
long* pLOrderCalcNum;
short* pShOrderCalcNum;
char  *pCh;
}P;
long lAmtProcessObj,lIdxCounter;
long i,l;
void* pv;
    struct {
    
    short shMarkerIteration;
    short shLocalIdxCounter;
    short shCounterLocalIteration;
    void *pV;
    LUAreaListElem* arrLUAreaListElem;
    CLUBase* pCLUBase;//SelectorCurrElem
//      bool bbStateChange;
    char chLUNumOut;
    short shLUStateOut,shLUStateOutChk;
    
      
    } sLV;
//?    TmrCalls();    
//?    UpdateStateDI();
/* if(chStateOptimisation == 1)
   asm volatile(
       "bkpt 1"
       ); */
       sLV.arrLUAreaListElem = static_cast<LUAreaListElem*>(this->pLUAreaList);
       //pLUAreaList = static_cast<void*>(&gLUAreaMem.headLUAreaList);
       sLV.shLocalIdxCounter = sLV.shMarkerIteration = sLV.shCounterLocalIteration = 0;
       sLV.chLUNumOut = sLV.shLUStateOutChk = sLV.shLUStateOut = 0;
    //DoCalcLUSources(); <- This function make Nazar Prg
    //P.pCh = const_cast<char*>(arrChCalcLUOrderNumsSchmPage2);
    P.pCh = static_cast<char*>(pExecSeq);

    //lAmtProcessObj = sizeof(arrChCalcLUOrderNumsSchmPage2)>>1;
    //?lAmtProcessObj = (shSizeExecSeq >> 2) - 1;
    lAmtProcessObj = shAmountExecSeqElem;
    lIdxCounter = 0;
    do {
        
          
         sLV.shLocalIdxCounter = lIdxCounter;
         i = P.pShOrderCalcNum[0] - 1;//Num Convert to Index
		 if (i >= 0xcccc || i < 0 ){
			 lIdxCounter++;
			 goto endwhile;
		 }
         l = P.pShOrderCalcNum[1]; 
//        j = i >> 8;//        i &= 0xff;//        i += arIdxLUAreaListElem[j-1];
        if (l>0){//Save State Outs
            pv = (sLV.arrLUAreaListElem[i]).pvLU;
            sLV.chLUNumOut = static_cast<CLUBase*>( pv)->chNumOutput;
            for (long lii = 0; lii < sLV.chLUNumOut;lii++)
            sLV.shLUStateOut |= static_cast<char*>((static_cast<CLUBase*>( pv)->pOut))[lii] << lii;
            //Read Out
        }
        pv = LUSelectorRV(i);
        if( l == 0 ){//|| sLV.shLocalIdxCounter == lIdxCounter
            lIdxCounter++;
            P.pLOrderCalcNum ++;//= lIdxCounter;
        }
        else{
            //Fix State            
            for (long lii = 0; lii < sLV.chLUNumOut;lii++)
            sLV.shLUStateOutChk |= static_cast<char*>((static_cast<CLUBase*>( pv)->pOut))[lii] << lii;
            
            if(sLV.shLUStateOutChk != sLV.shLUStateOut){
                long j = sLV.shLocalIdxCounter + 1;
                sLV.pV = static_cast<void*>(P.pCh);
                P.pLOrderCalcNum = &(static_cast<long*>(pExecSeq))[j];
                
                //
                while( j < lAmtProcessObj && P.pShOrderCalcNum[1] == l ){
                    pv = LUSelectorRV(j);
                    j++;
                    P.pLOrderCalcNum ++;//= j;
                }
                //Check State
                if(sLV.shMarkerIteration != lIdxCounter){
                    sLV.shCounterLocalIteration = 0;
                    sLV.shMarkerIteration = lIdxCounter;
                    
                }
                else{
                    sLV.shCounterLocalIteration++;
                    if(sLV.shCounterLocalIteration  > MAX_AMOUNT_LINK_ITERATION)
                        while(1);//Fix Fault
                        //Later insert in program Error
                        //Fix Schematic Error
                }
                P.pCh = static_cast<char*>(sLV.pV);//Restore pointer
                
            }
            else{//Defacto this is (state_curr_el == el(i)) 
                lIdxCounter++;
                P.pLOrderCalcNum = (static_cast<long*>(pExecSeq))+lIdxCounter;
                
            }
        }
 endwhile:       
       ; 
       
        
    } while (lIdxCounter < lAmtProcessObj );
    
//    i = arIdxLUAreaListElem[LU_OUTPUT-1];
//    LUIterator((static_cast<__CONFIG* >(p_current_config_prt))->n_output,i);//


}


//""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
//``````````````````````````````````````````````````````````````````````````````````
//==================================================================================
//--- 			 Optimized function for CPP Schematic     -----------
//==================================================================================
//..................................................................................
//""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
//#include "Tim9.c"










