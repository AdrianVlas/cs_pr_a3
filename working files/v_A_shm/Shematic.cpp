#ifdef VISUAL_STUDIO
#include "StdAfx.h"
#endif
#include <stdlib.h>
#include "Shematic.h"
//#include "StructElem.h"
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
#include "CLUTs.hpp"
#include "LULan.hpp "
#include "LUMms.hpp "
#include "LUGoos.hpp"
//#include <conio.h>
#include <string.h>
#include <ctime>
#include "stng.h"
#include "IStng.h"
#include "I_Shm.h"
#include "I_Shm.h"
#include "MALed.hpp"
#include "RunErLed.hpp"
#include "LUTestLed.h"
#include "LULog.hpp"
#include "FixblWrp.hpp"
#include "StatInfo.h"
//#include "../inc/variables_external.h"
//#include "../inc/libraries.h"



__CONFIG_CPP preSetUP = {
    0, //uint32_t device_id;
    10, 10, 10,
    1, //uint32_t n_and;
    1, //uint32_t n_or;
    1, //uint32_t n_xor;
    1, //uint32_t n_not;
    1, //uint32_t n_timers;
    1, //uint32_t n_triggers;
    1, //uint32_t n_alarms;
    1, //uint32_t n_meanders;
    2, 2, 2, 2, 2, 2, 2, 2//uint8_t time_config[7+1];

};

long long LL_CryaCrya @ "NonZeroIniVars_RAM1" = 15;
UNN_LogicUnitArea gLUAreaMem  = {

};
/*
UNN_LogicUnitArea gLUAreaMem @ "NonZeroIniVars_RAM1" = {

};
*/
LUAreaAuxVar gblLUAreaAuxVar  = {
    0, //.short shAmountPlacedLogicUnit;//counter placed
    0, //.short shIdxLUAreaListElem;    //Index LU Area List Elem
    (SIZE_MEM_BLK - sizeof (LUAreaListElem)), sizeof (LUAreaListElem), //.long  lAmountFreeMem, lAmountUsedMem;
     static_cast<void*>( &(gLUAreaMem.chArRamPrgEvt[((SIZE_MEM_BLK) - 1)])),
	static_cast<void*>(0)

};



/*
//Declare 5 Points & 1 struct element
InPoint ar5Points[TOTAL_POINTS];
StructElem s3And = StructElem(3);
 */

UNN_LogicUnitArea lcUArea;

short shAmountTotalElem = 0;
long lAmountOccupyMem = 0;
 //long lIdxHead
 //long lIdxTail
short shIdxLUnit = 0;
 //Next List Header
 //Prev List Header
 //Insert function
 //Delete function
/*
*	Main Object
*
*/
Shematic sh;

char chGblGround = 0;
char chGblVcc    = 1;

CMuteAlarmLed eMuteAlarmLed;
CLURunErrorLed eRunErrorLed;
CLUTestLed eLUTestLed;
        
Shematic::Shematic(void) {
    //Debug Code
    ar_n_Output_Dsc[0].UN_BitFld_LUInInfo.sBitFld_LUInInfo.bfInfo_OrdNumOut
            = ar_n__Output_Dsc[0].bfInfo_OrdNumOut;
    ar_n_Output_Dsc[0].UN_BitFld_LUInInfo.sBitFld_LUInInfo.bfInfo_OrdNumStng
            = ar_n__Output_Dsc[0].bfInfo_OrdNumStng;
    ar_n_Output_Dsc[0].UN_BitFld_LUInInfo.sBitFld_LUInInfo.bfInfo_IdLUStng
            = ar_n__Output_Dsc[0].bfInfo_IdLUStng;
    //Debug Code
    memset(static_cast<void*>(arIdxLUAreaListElem),0,sizeof(short)*TOTAL_LU);
    pLUAreaList = static_cast<void*>(&gLUAreaMem.headLUAreaList);
    pExecSeq = static_cast<void*>(0);
	LL_CryaCrya++;
    chInitTerminated = 0;
    chMaxIteratoin = 2;
    chIteration = 0;
    shIdxSumNLedPlusNOutSeq = 0; 
    shIdxSumNTUPlusNLANSeq  = 0; 
    shIdxSum8ElemSeq        = 0; 

}

void Shematic::Init_(void) {

//-void *memset(void *s, int c, size_t n);
chInitTerminated = 0;
memset(static_cast<void*>(&gLUAreaMem),0,sizeof(SIZE_LU_AREA_LIST_ITEM));
memset(static_cast<void*>(&gblLUAreaAuxVar),0,sizeof(gblLUAreaAuxVar));
gblLUAreaAuxVar.lAmountFreeMem = (SIZE_MEM_BLK - sizeof (LUAreaListElem));
gblLUAreaAuxVar.lAmountUsedMem = sizeof (LUAreaListElem);
gblLUAreaAuxVar.pvHead =
static_cast<void*>(&(gLUAreaMem.chArRamPrgEvt[((SIZE_MEM_BLK) - 1)]));
p_current_config_prt = static_cast<void*>(&current_config_prt);
chMaxIteratoin = 
(static_cast<__CONFIG* >(p_current_config_prt))->n_output
+((static_cast<__CONFIG* >(p_current_config_prt))->n_led         )
+((static_cast<__CONFIG* >(p_current_config_prt))->n_alarm       )
+((static_cast<__CONFIG* >(p_current_config_prt))->n_group_alarm )
+((static_cast<__CONFIG* >(p_current_config_prt))->n_and         )
+((static_cast<__CONFIG* >(p_current_config_prt))->n_or          )
+((static_cast<__CONFIG* >(p_current_config_prt))->n_xor         )
+((static_cast<__CONFIG* >(p_current_config_prt))->n_not         )
+((static_cast<__CONFIG* >(p_current_config_prt))->n_timer       )
+((static_cast<__CONFIG* >(p_current_config_prt))->n_trigger);

chSumNLedPlusNOut = (static_cast<__CONFIG* >(p_current_config_prt))->n_output
+((static_cast<__CONFIG* >(p_current_config_prt))->n_led         );

shSum8Elem =  ((static_cast<__CONFIG* >(p_current_config_prt))->n_alarm       )
+((static_cast<__CONFIG* >(p_current_config_prt))->n_group_alarm )
+((static_cast<__CONFIG* >(p_current_config_prt))->n_and         )
+((static_cast<__CONFIG* >(p_current_config_prt))->n_or          )
+((static_cast<__CONFIG* >(p_current_config_prt))->n_xor         )
+((static_cast<__CONFIG* >(p_current_config_prt))->n_not         )
+((static_cast<__CONFIG* >(p_current_config_prt))->n_timer       )
+((static_cast<__CONFIG* >(p_current_config_prt))->n_trigger); 
//Max Amount sequently linked Elem [1]-[2]-[3]-[4]-[5]-[6]-[7]-[8]-[9]
chIteration = 5;
ClrTmrVars();
if(chInitTerminated != 1)
Init2();


chInitTerminated = 1;
}

char chStateOptimisation = 1;




void Shematic::DoCalc(void) {

    register long i, j;
    register long lDwnCtr;
/*    register void* pv;

    struct {
        //long lId,lsizeobj;
        char chIteration;
        short shAmountCalcLU, shRes;
        void *pV;
        LUAreaListElem* arrLUAreaListElem;
        CLUBase* pCLUBase;
    } sLV;
    sLV.shAmountCalcLU = gblLUAreaAuxVar.shAmountPlacedLogicUnit;
    sLV.arrLUAreaListElem = &gLUAreaMem.headLUAreaList;
    sLV.chIteration = chIteration;*/
    i = 0;
    if(chInitTerminated == 0)
        return;
    TmrCalls();
    j = CBGSig::m_chCounterCall;    
    if(j >= 8)//100
        CBGSig::m_chCounterCall = 0;
    else
        CBGSig::m_chCounterCall = ++j;
    j = CBGSig::chMeasUpdateInterval;    
    if(j >= 20)//100
        CBGSig::chMeasUpdateInterval = 0;
    else
        CBGSig::chMeasUpdateInterval = ++j;
    
    //if(CBGSig::chMeasUpdateInterval == 0){
    for (long lIdChanell, ii = 0 ; ii < I_U ; ii++)    {                   // Early Worked
        lIdChanell  = CBGSig::ChanelsNames[ii];                            // Defacto must
                                                                           // be Inactive
        if(CBGSig::meas[lIdChanell] > measurement[lIdChanell])             // Code
            CBGSig::DMeas[lIdChanell] = i =                                // q
                    CBGSig::meas[lIdChanell] - measurement[lIdChanell];    // q
        else                                                               // q
            CBGSig::DMeas[lIdChanell] = i =                                // q
                    measurement[lIdChanell] - CBGSig::meas[lIdChanell];    // q
        j = CBGSig::PickUPs[ii];                                           // q
        //if (CBGSig::DMeas[lIdChanell] > static_cast<unsigned long>(j)  ) // q
                                                                           // q
        ;                                                                  // q
        if (i > j  )//static_cast<unsigned long>(j)                        // q
            CBGSig::m_chCounterCall = 0;
        //else

    }
    if(CBGSig::chMeasUpdateInterval == 0){

        memcpy(reinterpret_cast<void*>(CBGSig::meas),
               reinterpret_cast<void*>(measurement), I_U*sizeof(long));

        i = CBGSig::m_chIdxGrupSamples;
        j = I_U*1;//sizeof(long)
        //lDwnCtr = reinterpret_cast<long>(&(CBGSig::measbuf[i][0]));

        memcpy(reinterpret_cast<void*>(&(CBGSig::measbuf[i][0])),
                //reinterpret_cast<void*>(PMeas), I_U*sizeof(long));
                reinterpret_cast<void*>(measurement), I_U*sizeof(long));
        i++;
        if(i > 2)
            i = 0;
        CBGSig::m_chIdxGrupSamples = i;
        
    }

    if(CBGSig::chNeedTimerCalculated >0){
        CBGSig::m_chCounterCall = 0;//It`s initiated Recalc when Timer work
        CBGSig::chNeedTimerCalculated = 0;
    }
   
//    CBGSig::chNeedRefrash = 1;        
        
    i = 0;    
//    UpdateStateDI();
    if( (chErrorState&1) != 0){
        //Set to 0 DOState

        eRunErrorLed.EvalRunErrorLed();
        return;
    }
    if(chStateOptimisation == 0){
        DoCalcLUSources();
        FBWrp_Op(pCFixBlockWrp);
        //  j = (static_cast<__CONFIG* >(p_current_config_prt))-> n_group_alarm;
        //  i = arIdxLUAreaListElem[LU_BGS-1];
        //  LUIterator(j,i);
        lDwnCtr = chIteration;
        CLUBase::m_AuxInfo.ch = 0;
        do{
            //Startovyi Iterator
            //i = arIdxLUAreaListElem[LU_LSS-1];
            i = shIdxSum8ElemSeq;
            j = shSum8Elem;//kolichestvo elementov
            LUIterator(j,i);
            //Startovyi Iterator
            i = arIdxLUAreaListElem[LU_OUTPUT-1];
            //kolichestvo elementov
            j = chSumNLedPlusNOut;
            LUIterator(j,i);//
            //i = arIdxLUAreaListElem[LU_TU-1];
            i = shIdxSumNTUPlusNLANSeq;
            j = chSumNTUPlusNLAN;
            LUIterator(j,i);//
            CLUBase::m_AuxInfo.ch++;
            //Predpolagaemyi uroven` vlozenosti
        }while(--lDwnCtr);
        
/*        while (sLV.shAmountCalcLU--) {
            pv = reinterpret_cast<void*>( &sLV.arrLUAreaListElem[i]);
            sLV.pCLUBase = reinterpret_cast<CLUBase*>( (reinterpret_cast<LUAreaListElem*> (pv))->pvLU);//(CLUBase*)
            pv = reinterpret_cast<void*>( sLV.pCLUBase); //->LogicFunc;
            if ((reinterpret_cast<CLUBase*>( pv))->shShemasOrdNumStng != 0 //&&
                    ) {
                j = (reinterpret_cast<CLUBase*>( pv))->shShemasIdLUStng;
                switch (j) {
                    case STNG_EXTENDED:
                    //    break;
                    default:
                    {
                        //if (j > STNG_EXTENDED && j < STNG_LU_UPPER_BOUND) {
                        if (j >= TARAS_ALAS_STNG_LU_INPUT && j < TARAS_ALAS_STNG_LU_UPPER_BOUND) {
                            if ((reinterpret_cast<CLUBase*>( pv))->LogicFunc != Null_OP) {
                                (reinterpret_cast<CLUBase*>( pv))->LogicFunc( reinterpret_cast<void*>(sLV.pCLUBase));
                            }

                        }
                    }
                }

            }
            i++;
        }
        */
    }
else{ 
        if(chStateOptimisation == 1){
            DoCalcLUSources();FBWrp_Op(pCFixBlockWrp); 
			DoCalcLU_V01();
        }
        else
            DoCalcLU();
    }
    eMuteAlarmLed.EvalMuteAlarmLed();
    eRunErrorLed.EvalRunErrorLed();
    eLUTestLed.CalCLUTestLedSchematic();
        //run Error
}

Shematic::~Shematic(void) {
}

void Shematic::printResult(void) {
    /*    int c = 0;
        long lIdxPoint = NUM_IN_POINTS;
        char chAmtInitPoints = NUM_OUT_POINTS-1;
        InPoint*pInPont = &ar5Points[lIdxPoint];
        printf("Result schematic:\n");
        do{
            printf("State ar5Points[");printf("%hhX %s",lIdxPoint,"]=");
            putchar((int)pInPont ->chState+0x30);printf(" \n");
            lIdxPoint++;
            pInPont = &ar5Points[lIdxPoint];//Next Pointer

        }while(chAmtInitPoints--);
        pInPont = &ar5Points[lIdxPoint];

        c = getch();*/

}

void Shematic::PrintPointsState(void) {
    // Print state All Points which Shematic Use
    // Name Logic Unit
}

void Shematic::PrintShematicElemPointsState(void) {
    //Print Only Points Using?
}

//void Shematic::SetupCircutLinks(void *pv) {
//    //register long ik;
//    Init2LcVarArea& rsLV  = *((Init2LcVarArea*)pv);
//    rsLV.arrLUAreaListElem = &gLUAreaMem.headLUAreaList;
//}
//#ifdef RAND_MAX
// #define RAND_MAX 256
//#endif
//static long first_value,last_value;
//random_number = first_value + rand() % last_value;

static long arNum[300] @ "ZeroInivars_RAM1";
static short shCounterCalls_GLB;

long Shematic::GetTrueOrderNum(void) {
    register long i, j;

    struct {
        char chNeedAnotherNumber, chCtrCalls;
    } sLV;
    volatile long random_number;

    sLV.chNeedAnotherNumber = 0;
    srand(time(0));
    // i = (long) rand() % 255; //255 Max diapason
    i = static_cast<long>(rand() % 255); //255 Max diapason

    random_number = i + 1; //1 - min diapason
    sLV.chCtrCalls = 0;
    do {

        for (j = 0; j < 300 && arNum[j] != 0; j++) {

            if (random_number == arNum[j]) {
                j = 300;
                sLV.chNeedAnotherNumber = 1;
                break;
            }
            if(arNum[j+1] == 0){
                sLV.chNeedAnotherNumber = 0;
                break;
            }
        }
        //Another Number
        if (sLV.chNeedAnotherNumber) {
            sLV.chCtrCalls++;
            i = static_cast<long>( rand() % 255); //255 Max diapason
            random_number = i + 1;
        }
    } while (sLV.chNeedAnotherNumber && sLV.chCtrCalls < 250);
    if (sLV.chCtrCalls >= 250) {
        //Clr Mem
        for (j = 0; j < 300; j++)
            arNum[j] = 0;
        shCounterCalls_GLB = 0;
    }
    i = shCounterCalls_GLB;
    arNum[i] = random_number;
    shCounterCalls_GLB = i+1;

    return random_number;
}

void Shematic::CreateTestSchema(void) {
    /*
    register long i,j;
    void* pv;
    struct
        {
            //short shAmtLU,shIdxLUOut;//
                    long lOrderNumber;
            short shAmtLUDsc,shIdx;
                    short shIdxLUOutDsc, shIdxLU;
                    //SBitFld_LUInInfo locSBitFld;

        } sLV;


            //sLV.locSBitFldCRefInfo =
            //SetUP DOUT
            //Form Additional Info
            sLV.shAmtLUDsc = preSetUP.n_and;
            sLV.shIdxLUOutDsc = sLV.shIdxLU = sLV.shIdx = 0;//
            sLV.shIdxLUOutDsc = MAX_AMOUNT_LU_OUTPUT+MAX_AMOUNT_LU_LED;
            //SetUP Led
            //SetUP And
            while(sLV.shIdx < sLV.shAmtLUDsc){

                    sLV.lOrderNumber = GetTrueOrderNum();//Take OrdNum F-Block From Taras Area
                    locSBitFldCRefInfo.bfInfo_OrdNumOut  = 1;//Now use All ones
                    locSBitFldCRefInfo.bfInfo_IdLUStng   = STNG_LU_INPUT;
                    locSBitFldCRefInfo.bfInfo_BaseID     = sLV.lOrderNumber;
                    for (long j = 0; j < 8 ; j++){//Create data for each Input
                            locSBitFldCRefInfo.bfInfo_OrdNumStng = ORD_INPUT_01+j;
                            arrSBitFldCRefInfo[sLV.shIdxLUOutDsc+j] = locSBitFldCRefInfo;
                    }
                    //locSBitFld.bfInfo_OrdNumOut
                    //locSBitFld.bfInfo_OrdNumStng
                    //locSBitFld.bfInfo_IdLUStng
            }


            //SetUP OR
            sLV.shIdxLUOutDsc = MAX_AMOUNT_LU_OUTPUT+MAX_AMOUNT_LU_LED
            +(MAX_AMOUNT_LU_AND*8);
            sLV.shAmtLUDsc = preSetUP.n_or;sLV.shIdx = 0;
            while(sLV.shIdx < sLV.shAmtLUDsc){

                    sLV.lOrderNumber = GetTrueOrderNum();//Take OrdNum F-Block From Taras Area
                    locSBitFldCRefInfo.bfInfo_OrdNumOut  = 1;//Now use All ones
                    locSBitFldCRefInfo.bfInfo_IdLUStng   = STNG_LU_INPUT;
                    locSBitFldCRefInfo.bfInfo_BaseID     = sLV.lOrderNumber;
                    for (long j = 0; j < 8 ; j++){//Create data for each Input
                            locSBitFldCRefInfo.bfInfo_OrdNumStng = ORD_INPUT_01+j;
                            arrSBitFldCRefInfo[sLV.shIdxLUOutDsc+j] = locSBitFldCRefInfo;
                    }
                    //locSBitFld.bfInfo_OrdNumOut
                    //locSBitFld.bfInfo_OrdNumStng
                    //locSBitFld.bfInfo_IdLUStng
            }
            //SetUP XOR
            sLV.shIdxLUOutDsc = MAX_AMOUNT_LU_OUTPUT+MAX_AMOUNT_LU_LED
            +(MAX_AMOUNT_LU_AND*8)+(MAX_AMOUNT_LU_OR*8 );
            sLV.shAmtLUDsc = preSetUP.n_xor;sLV.shIdx = 0;
            while(sLV.shIdx < sLV.shAmtLUDsc){

                    sLV.lOrderNumber = GetTrueOrderNum();//Take OrdNum F-Block From Taras Area
                    locSBitFldCRefInfo.bfInfo_OrdNumOut  = 1;//Now use All ones
                    locSBitFldCRefInfo.bfInfo_IdLUStng   = STNG_LU_INPUT;
                    locSBitFldCRefInfo.bfInfo_BaseID     = sLV.lOrderNumber;
                    for (long j = 0; j < 8 ; j++){//Create data for each Input
                            locSBitFldCRefInfo.bfInfo_OrdNumStng = ORD_INPUT_01+j;
                            arrSBitFldCRefInfo[sLV.shIdxLUOutDsc+j] = locSBitFldCRefInfo;
                    }
                    //locSBitFld.bfInfo_OrdNumOut
                    //locSBitFld.bfInfo_OrdNumStng
                    //locSBitFld.bfInfo_IdLUStng
            }
            //SetUP NOT
            sLV.shIdxLUOutDsc = MAX_AMOUNT_LU_OUTPUT+MAX_AMOUNT_LU_LED
            +(MAX_AMOUNT_LU_AND*8)+(MAX_AMOUNT_LU_OR*8 )+(MAX_AMOUNT_LU_XOR*2);
            sLV.shAmtLUDsc = preSetUP.n_not;sLV.shIdx = 0;
            while(sLV.shIdx < sLV.shAmtLUDsc){

                    sLV.lOrderNumber = GetTrueOrderNum();//Take OrdNum F-Block From Taras Area
                    locSBitFldCRefInfo.bfInfo_OrdNumOut  = 1;//Now use All ones
                    locSBitFldCRefInfo.bfInfo_IdLUStng   = STNG_LU_INPUT;
                    locSBitFldCRefInfo.bfInfo_BaseID     = sLV.lOrderNumber;
                    for (long j = 0; j < 8 ; j++){//Create data for each Input
                            locSBitFldCRefInfo.bfInfo_OrdNumStng = ORD_INPUT_01+j;
                            arrSBitFldCRefInfo[sLV.shIdxLUOutDsc+j] = locSBitFldCRefInfo;
                    }
                    //locSBitFld.bfInfo_OrdNumOut
                    //locSBitFld.bfInfo_OrdNumStng
                    //locSBitFld.bfInfo_IdLUStng
            }
     */
}

struct GlobalObjectMap_tag {

    CLUDInput_0_1 *arPCLUDInput_0_1[MAX_AMOUNT_LU_INPUT];  // NUM_STNG_IN
    CLUDout_1_0   *arPCLUDout_1_0  [MAX_AMOUNT_LU_OUTPUT]; // NUM_STNG_OUT
    CLULed        *arPCLULed       [MAX_AMOUNT_LU_LED];    // NUM_STNG_LED
    CLUNot_1_1    *arPCLUNot_1_1   [MAX_AMOUNT_LU_NOT];
    CLUOr_8_1     *arPCLUOr_8_1    [MAX_AMOUNT_LU_OR];
    CLUAnd_8_1    *arPCLUAnd_8_1   [MAX_AMOUNT_LU_AND];
    CLUXor_8_1    *arPCLUXor_8_1   [MAX_AMOUNT_LU_XOR];
    CMft          *arCMft          [MAX_AMOUNT_LU_TIMERS];
    CLUFKey       *arPCLUFKey      [MAX_AMOUNT_LU_FKey];
    CLULss        *arPCLULss       [MAX_AMOUNT_LU_LSS];
    CBGSig        *arPCBGSig       [MAX_AMOUNT_LU_BGS];
    CLUTrig       *arPCLUTrig      [MAX_AMOUNT_LU_TRIG];
    CPulseAlternator *arPCPulseAlternator[MAX_AMOUNT_LU_ALT];
    CLUTu       *arPCLUTu      [MAX_AMOUNT_LU_TU];
    CLUTs       *arPCLUTs      [MAX_AMOUNT_LU_TS];
    CLUGoose *arPCLUGoose      [MAX_AMOUNT_LU_GOOSE];
    CLUMms   *arPCLUMms        [MAX_AMOUNT_LU_MMS];
    CLULan   *arPCLULan        [MAX_AMOUNT_LU_LAN];
    CLULog       *arPCLULog      [MAX_AMOUNT_LU_LOG];// MAX_AMOUNT_LU_TS
    
} GlobalObjectMap @ "variables_RAM1";
//Place 3 Unit

void Shematic::Init1(void) {
    long i, j;
    void* pv;
    //char **pCh;

    struct {
        char* pCh;
        char** arrPchIn;
        LUAreaListElem* arrLUAreaListElem;
        CLUBase *pCLUBase, *pCLURef;
        void *pV;
        long lId, lsizeobj;
        short shAmtLU, shIdxLUOut; //
        short shAmtLUDsc, shIdx;
        short shIdxLUOutDsc, shIdxLU; //shCountCmd;
        char chVal, chErrCount, chBrk1, chBrk2;
        //unsigned char uchVal;
    } sLV;
    sLV.shIdx = sLV.shIdxLU = 0;
    sLV.chVal = static_cast<char> (preSetUP.n_input);
    sLV.arrLUAreaListElem = &gLUAreaMem.headLUAreaList;
    sLV.chErrCount = sLV.chBrk1 = sLV.chBrk2 = 0;
    sLV.shIdxLUOutDsc = 1;
    DetectCircutLinks();
    if (sLV.chVal) {

        CLUDInput_0_1 locCLUDInput_0_1(10, 0); // = CLUDInput_0_1(0,10);
        j = i = 0;
        do {
            j = InsertLU(LU_INPUT, static_cast<void*> (&locCLUDInput_0_1));

            if (j) {//Success Bield
                //Additional Obj SetUP

                i = gblLUAreaAuxVar.shAmountPlacedLogicUnit;
                pv = static_cast<void*>( &sLV.arrLUAreaListElem[i - 1]);
                sLV.pCLUBase = static_cast<CLUBase*>( ( static_cast<LUAreaListElem*>(pv) )->pvLU);
                sLV.pCLUBase->shShemasIdLUStng = STNG_LU_INPUT;
                //sLV.uchVal = arrSBitFldCRefInfo[sLV.shIdxLUOutDsc-1].bfInfo_BaseID;
                sLV.pCLUBase->shShemasOrdNumStng = static_cast<unsigned char>(arrSBitFldCRefInfo[sLV.shIdxLUOutDsc-1].bfInfo_BaseID);
                    sLV.shIdxLUOutDsc++; //Temporary Numeration Discass It!!!!;
                CLUDInput_0_1* locPCLUDInput_0_1 = static_cast<CLUDInput_0_1*>(sLV.pCLUBase);
                locPCLUDInput_0_1->pOut = static_cast<void*>( locPCLUDInput_0_1->arrOut);
                CLUDInput_0_1& locRef_CLUDInput_0_1 = *(static_cast<CLUDInput_0_1*>(sLV.pCLUBase));
                locRef_CLUDInput_0_1.chTypeLogicFunction = LU_OP_READ_DI;
                locRef_CLUDInput_0_1.LogicFunc = READ_DI_Op; //???

                GlobalObjectMap.arPCLUDInput_0_1[sLV.shIdx++] = static_cast<CLUDInput_0_1*>(sLV.pCLUBase);
                sLV.shIdxLU++;
            }//Else Error

        } while (sLV.shIdxLU < preSetUP.n_input && j);
        //Check State j
    }
    sLV.shIdx = 0;
    if (preSetUP.n_output != 0) {
        sLV.shIdxLU = 0;
        j = 0;
        CLUDout_1_0 locCLUDout_1_0(10, 0); // = CLUDout_1_0(0,10);
        do {
            j = InsertLU(LU_OUTPUT, static_cast<void*> (&locCLUDout_1_0));
            if (j) {//Success Bield
                //Additional Obj SetUP
                i = gblLUAreaAuxVar.shAmountPlacedLogicUnit;
                pv = static_cast<void*>(&sLV.arrLUAreaListElem[i - 1]);
                sLV.pCLUBase = static_cast<CLUBase*>(
                        (static_cast<LUAreaListElem*>(pv))->pvLU);
                sLV.pCLUBase->shShemasIdLUStng = STNG_LU_OUTPUT;
                sLV.pCLUBase->shShemasOrdNumStng = arrSBitFldCRefInfo[sLV.shIdxLUOutDsc-1].bfInfo_BaseID;
                        sLV.shIdxLUOutDsc++; //Temporary Numeration Discass It!!!!;
                CLUDout_1_0* locPCLUDout_1_0 = static_cast<CLUDout_1_0*>(sLV.pCLUBase);
                locPCLUDout_1_0->pIn = static_cast<void*> (locPCLUDout_1_0->arrPchIn);
                locPCLUDout_1_0->chTypeLogicFunction = LU_OP_SET_OUT;
                locPCLUDout_1_0->LogicFunc = SET_OUT_Op; //???

                GlobalObjectMap.arPCLUDout_1_0[sLV.shIdx++] = static_cast<CLUDout_1_0*>(sLV.pCLUBase);
                sLV.shIdxLU++;
            }

        } while (sLV.shIdxLU < preSetUP.n_output && j);
    }
    sLV.shIdx = 0;
    if (preSetUP.n_led != 0) {
        volatile short shIdxLU = 0;
        j = 0; //sLV.shIdxLU = 0;
        CLULed locCLULed(10, 0); // = CLULed(0,10);
        do {
            j = InsertLU(LU_LED, static_cast<void*>(&locCLULed));
            //sLV.shIdxLU++;
            if (j) {//Success Bield
                //Additional Obj SetUP
                i = gblLUAreaAuxVar.shAmountPlacedLogicUnit;
                //pv = (void*) &sLV.arrLUAreaListElem[i - 1];
                //sLV.pCLUBase = (CLUBase*) ((LUAreaListElem*) pv)->pvLU;
				pv = static_cast<void*>( &sLV.arrLUAreaListElem[i - 1]);
                sLV.pCLUBase = static_cast<CLUBase*>( ( static_cast<LUAreaListElem*>(pv) )->pvLU);
                sLV.pCLUBase->shShemasIdLUStng = STNG_LU_LED;
                sLV.pCLUBase->shShemasOrdNumStng = arrSBitFldCRefInfo[sLV.shIdxLUOutDsc-1].bfInfo_BaseID;
                        sLV.shIdxLUOutDsc++; //Temporary Numeration Discass It!!!!;
                CLULed* locPCLULed = static_cast<CLULed*>(sLV.pCLUBase);
                locPCLULed->pIn = static_cast<void*>(locPCLULed->arrPchIn);
                CLULed& locRef_CLULed = *(static_cast<CLULed*>(sLV.pCLUBase));
                locRef_CLULed.chTypeLogicFunction = LU_OP_SET_LED;
                locRef_CLULed.LogicFunc = SET_LED_Op; //???
                GlobalObjectMap.arPCLULed[sLV.shIdx++] = static_cast<CLULed*>(sLV.pCLUBase);
                shIdxLU++; //
            }

        } while (shIdxLU < preSetUP.n_led && j);
    }
    sLV.shIdx = 0;
    if (preSetUP.n_and != 0) {
        sLV.shIdxLU = 0;
        j = 0;
        CLUAnd_8_1 locCLUAnd_8_1(10, 0); // = CLUAnd_8_1(0,10);
        do {
            j = InsertLU(LU_AND, static_cast<void*>(&locCLUAnd_8_1));
            if (j) {//Success Bield
                //Additional Obj SetUP
                i = gblLUAreaAuxVar.shAmountPlacedLogicUnit;
                //pv = (void*) &sLV.arrLUAreaListElem[i - 1];
                //sLV.pCLUBase = (CLUBase*) ((LUAreaListElem*) pv)->pvLU;
				pv = static_cast<void*>( &sLV.arrLUAreaListElem[i - 1]);
                sLV.pCLUBase = static_cast<CLUBase*>( ( static_cast<LUAreaListElem*>(pv) )->pvLU);
                sLV.pCLUBase->shShemasIdLUStng = STNG_LU_AND;
                sLV.pCLUBase->shShemasOrdNumStng = arrSBitFldCRefInfo[sLV.shIdxLUOutDsc-1].bfInfo_BaseID;
                        sLV.shIdxLUOutDsc++; //Temporary Numeration Discass It!!!!;
                CLUAnd_8_1* locPCLUAnd_8_1 = static_cast<CLUAnd_8_1*>(sLV.pCLUBase);
                locPCLUAnd_8_1->pOut = static_cast<void*>(locPCLUAnd_8_1->arrOut  );
                locPCLUAnd_8_1->pIn  = static_cast<void*>(locPCLUAnd_8_1->arrPchIn);
                CLUAnd_8_1& locRef_CLUAnd_8_1 = *(static_cast<CLUAnd_8_1*>(sLV.pCLUBase));
                locRef_CLUAnd_8_1.chTypeLogicFunction = LU_OP_AND; //
                locRef_CLUAnd_8_1.LogicFunc = AND_Op_8_1; //???

                GlobalObjectMap.arPCLUAnd_8_1[sLV.shIdx++] = static_cast<CLUAnd_8_1*>(sLV.pCLUBase);
                sLV.shIdxLU++;
            }

        } while (sLV.shIdxLU < preSetUP.n_and && j);
    }

    if (preSetUP.n_or != 0) {
        sLV.shIdx = sLV.shIdxLU = 0;
        j = 0;
        CLUOr_8_1 locCLUOr_8_1(10, 0); // = CLUOr_8_1(0,10);
        do {
            j = InsertLU(LU_OR, static_cast<void*>(&locCLUOr_8_1));
            if (j) {//Success Bield
                //Additional Obj SetUP
                i = gblLUAreaAuxVar.shAmountPlacedLogicUnit;
                //pv = (void*) &sLV.arrLUAreaListElem[i - 1];
                //sLV.pCLUBase = (CLUBase*) ((LUAreaListElem*) pv)->pvLU;
				pv = static_cast<void*>( &sLV.arrLUAreaListElem[i - 1]);
                sLV.pCLUBase = static_cast<CLUBase*>( ( static_cast<LUAreaListElem*>(pv) )->pvLU);
                sLV.pCLUBase->shShemasIdLUStng = STNG_LU_OR;
                sLV.pCLUBase->shShemasOrdNumStng =
                        sLV.shIdxLUOutDsc++; //Temporary Numeration Discass It!!!!;
                CLUOr_8_1* locPCLUOr_8_1 = static_cast<CLUOr_8_1*>(sLV.pCLUBase);
                locPCLUOr_8_1->pOut = static_cast<void*>(locPCLUOr_8_1->arrOut  );
                locPCLUOr_8_1->pIn  = static_cast<void*>(locPCLUOr_8_1->arrPchIn);
                CLUOr_8_1& locRef_CLUOr_8_1 = *(static_cast<CLUOr_8_1*>(sLV.pCLUBase));
                locRef_CLUOr_8_1.LogicFunc(sLV.pCLUBase);
                GlobalObjectMap.arPCLUOr_8_1[sLV.shIdx++] = static_cast<CLUOr_8_1*>(sLV.pCLUBase);
                sLV.shIdxLU++;
            }

        } while (sLV.shIdxLU < preSetUP.n_or && j);
    }
    if (preSetUP.n_xor != 0) {
        sLV.shIdx = sLV.shIdxLU = 0;
        j = 0;
        CLUXor_8_1 locCLUXor_8_1(10, 0); // = CLUXor_8_1(0,10);
        do {
            j = InsertLU(LU_XOR, static_cast<void*>(&locCLUXor_8_1));
            if (j) {//Success Bield
                //Additional Obj SetUP
                i = gblLUAreaAuxVar.shAmountPlacedLogicUnit;
                //pv = (void*) &sLV.arrLUAreaListElem[i - 1];
                //sLV.pCLUBase = (CLUBase*) ((LUAreaListElem*) pv)->pvLU;
				pv = static_cast<void*>( &sLV.arrLUAreaListElem[i - 1]);
                sLV.pCLUBase = static_cast<CLUBase*>( ( static_cast<LUAreaListElem*>(pv) )->pvLU);
                sLV.pCLUBase->shShemasIdLUStng = STNG_LU_XOR;
                sLV.pCLUBase->shShemasOrdNumStng =
                        sLV.shIdxLUOutDsc++; //Temporary Numeration Discass It!!!!;
                CLUXor_8_1* locPCLUXor_8_1 = static_cast<CLUXor_8_1*>(sLV.pCLUBase);
                locPCLUXor_8_1->pOut =  static_cast<void*>(locPCLUXor_8_1->arrOut  );
                locPCLUXor_8_1->pIn  =  static_cast<void*>(locPCLUXor_8_1->arrPchIn);
                CLUXor_8_1& locRef_CLUXor_8_1 = *(static_cast<CLUXor_8_1*>(sLV.pCLUBase));
                locRef_CLUXor_8_1.LogicFunc(sLV.pCLUBase);
                GlobalObjectMap.arPCLUXor_8_1[sLV.shIdx++] = static_cast<CLUXor_8_1*>(sLV.pCLUBase);
                sLV.shIdxLU++;
            }

        } while (sLV.shIdxLU < preSetUP.n_xor && j);
    }
    if (preSetUP.n_not != 0) {
        sLV.shIdx = sLV.shIdxLU = 0;
        j = 0;
        CLUNot_1_1 locCLUNot_1_1(10, 0); // = CLUNot_1_1(0,10);
        do {
            j = InsertLU(LU_NOT, static_cast<void*>(&locCLUNot_1_1));
            if (j) {//Success Bield
                //Additional Obj SetUP
                i = gblLUAreaAuxVar.shAmountPlacedLogicUnit;
                //pv = (void*) &sLV.arrLUAreaListElem[i - 1];
                //sLV.pCLUBase = (CLUBase*) ((LUAreaListElem*) pv)->pvLU;
				pv = static_cast<void*>( &sLV.arrLUAreaListElem[i - 1]);
                sLV.pCLUBase = static_cast<CLUBase*>( ( static_cast<LUAreaListElem*>(pv) )->pvLU);
                sLV.pCLUBase->shShemasIdLUStng = STNG_LU_NOT;
                sLV.pCLUBase->shShemasOrdNumStng =
                        sLV.shIdxLUOutDsc++; //Temporary Numeration Discass It!!!!;
                CLUNot_1_1* locPCLUNot_1_1 = static_cast<CLUNot_1_1*>(sLV.pCLUBase);
                locPCLUNot_1_1->pOut = static_cast<void*>(locPCLUNot_1_1->arrOut  );
                locPCLUNot_1_1->pIn  = static_cast<void*>(locPCLUNot_1_1->arrPchIn);
                CLUNot_1_1& locRef_CLUNot_1_1 = *(static_cast<CLUNot_1_1*>(sLV.pCLUBase));
                locRef_CLUNot_1_1.LogicFunc(sLV.pCLUBase);
                GlobalObjectMap.arPCLUNot_1_1[sLV.shIdx++] = static_cast<CLUNot_1_1*>(sLV.pCLUBase);
                sLV.shIdxLU++;
            }

        } while (sLV.shIdxLU < preSetUP.n_not && j);
    }

    //1 Place points In MemArea
    //Place Unit
    //If I try delete operation It shold move all data for efficiently
    //memory Use

    //SetUP Links
    sLV.arrLUAreaListElem = &gLUAreaMem.headLUAreaList;
    //Find 1st DO
    i = j = sLV.shIdxLUOutDsc = sLV.shIdxLU = 0;
    sLV.lId = 0;
    pv = static_cast<void*>(&sLV.arrLUAreaListElem[i]); //Last Elem
    sLV.shAmtLU = gblLUAreaAuxVar.shAmountPlacedLogicUnit;
    sLV.shAmtLUDsc = 10 + 10 + 8 * 1; //Demo Variant
    while (sLV.shAmtLUDsc && sLV.chBrk2 == 0) {
        while (sLV.shIdxLU < sLV.shAmtLU && sLV.chBrk1 == 0) {
            i = sLV.shIdxLU;
            pv = static_cast<void*>(&sLV.arrLUAreaListElem[i]);
            sLV.pCLUBase = static_cast<CLUBase*>( (static_cast<LUAreaListElem*>(pv))->pvLU);
            j = sLV.shIdxLUOutDsc;
            if (sLV.pCLUBase->shShemasIdLUStng == ar_n_output_CRDsc[j].shBaseIdLUStng &&
                    sLV.pCLUBase->shShemasOrdNumStng == ar_n_output_CRDsc[j].shBaseOrdNumStng) {
                sLV.pV = pv; //save pv
                sLV.chVal = sLV.pCLUBase->chNumOutput;
                for (sLV.shIdx = 0; sLV.shIdx < sLV.pCLUBase->chNumInput; sLV.shIdx++) {//sLV.pCLUBase->chNumOutput
                    //Find
                    //,,pv = (void*)&sLV.arrLUAreaListElem[0];//Last Elem
                    sLV.chVal = 0;
                    i = 0;
                    sLV.pCh = static_cast<char*>(0);
                    j = sLV.shIdxLUOutDsc + sLV.shIdx;
                    while (i < sLV.shAmtLU) {
                        pv = static_cast<void*>(&sLV.arrLUAreaListElem[i]);
                        sLV.pCLURef = static_cast<CLUBase*>( (static_cast<LUAreaListElem*>(pv))->pvLU);
                        if ((sLV.pCLURef->shShemasIdLUStng == ar_n_output_CRDsc[j].shRefIdLUStng) &&
                                (sLV.pCLURef->shShemasOrdNumStng == ar_n_output_CRDsc[j].shRefOrdNumStng)
                                && (sLV.shIdx == (ar_n_output_CRDsc[j].chRefOrdNumOut - 1))) {
                            sLV.pCh = static_cast<char*>(sLV.pCLURef->pOut);
                            sLV.pCh += ar_n_output_CRDsc[j].chRefOrdNumOut - 1;
                            sLV.chVal++; //Counter success
                            break;
                        }
                        i++;
                    }
                    if (sLV.pCh) {
                        sLV.arrPchIn = static_cast<char**>(sLV.pCLUBase->pIn);
                        sLV.arrPchIn[sLV.shIdx] = sLV.pCh;
                        j++;
                        //Check Next Statment
                        if (sLV.pCLUBase->shShemasIdLUStng != ar_n_output_CRDsc[j].shBaseIdLUStng
                                || sLV.pCLUBase->shShemasOrdNumStng != ar_n_output_CRDsc[j].shBaseOrdNumStng
                                ) {
                            sLV.shIdx = sLV.pCLUBase->chNumInput;
                            break; //goto ;//Break For
                        }
                    }
                }
                if (sLV.chVal) {//Succes SetUP
                    if (sLV.shAmtLUDsc >= sLV.chVal) {
                        sLV.shAmtLUDsc -= sLV.chVal;
                        sLV.shIdxLUOutDsc += sLV.chVal;
                        //goto;
                    } else {
                        //Fix Error
                        sLV.chErrCount++; //Wrong Setup Val
                        sLV.chBrk2 |= 1; //goto;Stop Execution
                    }

                } else {
                    sLV.chErrCount++; //Fix Error
                    //Not Found Out Elem Situation
                    //sLV.chBrk2 |= ;//goto;
                    sLV.lId |= 2;
                }
                sLV.chBrk1 |= 1;
            }
            //.if(sLV.chBrk1==0){
            //.
            //.}Next Iteration while(sLV.shIdxLU<sLV.shAmtLU)
            sLV.shIdxLU++;
        }
        sLV.shIdxLU = 0;
        sLV.chBrk1 = 0;
        //Check Error
        if (sLV.lId & 2) {
            //Not Found Out Elem Situation
            sLV.shAmtLUDsc -= 1;
            sLV.shIdxLUOutDsc += 1;
            sLV.lId &= ~2;
        }
    }
    //Scan Info on Leds


}

long Shematic::EvalSizeObj(long lId) {
    long lsizeObj;
    switch (lId) {
        case BASE_POINT:
            lsizeObj = SIZE_BASE_IN_POINT;
            break;
        case POINT:
            lsizeObj = SIZE_IN_POINT;
            break;
        case EXTENDED:
            lsizeObj = sizeof (ExtPoint);
            break;

        case LU_INPUT:
            lsizeObj = sizeof (CLUDInput_0_1);
            break;
        case LU_OUTPUT:
            lsizeObj = sizeof (CLUDout_1_0);
            break;
        case LU_LED:
            lsizeObj = sizeof (CLULed);
            break;
        case LU_FKEY:
            lsizeObj = sizeof (CLUFKey);
            break;
        case LU_ALARMS:
        case LU_LSS:
            lsizeObj = sizeof (CLULss);
            break;
        case LU_BGS:
            lsizeObj = sizeof (CBGSig);
            break;
        case LU_AND:
            lsizeObj = sizeof (CLUAnd_8_1);
            break;
        case LU_OR:
            lsizeObj = sizeof (CLUOr_8_1);
            break;
        case LU_XOR:
            lsizeObj = sizeof (CLUXor_8_1);
            break;
        case LU_NOT:
            lsizeObj = sizeof (CLUNot_1_1);
            break;
        case LU_MFT:
        case LU_TIMERS:
            lsizeObj = sizeof (CMft);
            break;
        case LU_TRIGGERS:
            lsizeObj = sizeof (CLUTrig);
            break;
        case LU_MEANDERS:
            lsizeObj = sizeof (CPulseAlternator);
            break;
        case LU_TU:
            lsizeObj = sizeof (CLUTu);
            break;
        case LU_TS:
            lsizeObj = sizeof (CLUTs);
            break;
            case LU_GOOSE:
            lsizeObj = sizeof (CLUGoose);
            break;
        case LU_MMS:
            lsizeObj = sizeof (CLUMms);
            break;
        case LU_LAN:
            lsizeObj = sizeof ( CLULan);
            break;
        case LU_LOG:
            lsizeObj = sizeof (CLULog);
            break;
        case LU_STNG_FIX:
            lsizeObj = sizeof (CFixBlockWrp);
            break;
        case ID_OBJ:
            lsizeObj = sizeof (CFixBlockWrp);
            break;

        default:
            lsizeObj = 0;
    }
    //ExitEval
    return lsizeObj;
}

long Shematic::InsertLU(long lId, void*pvObjImage) {
    register long i;
    register void* pv;
intptr_t iIptr_t;
    struct {
        intptr_t lId, lsizeobj;
        void *pV;
        LUAreaListElem* arrLUAreaListElem;
        CLUBase* pCLUBase;
    } sLV;
    //check Id
    sLV.lsizeobj = 0;
    i = EvalSizeObj(lId);
    if (i) {

        //Check pvObjImage
        if (pvObjImage != 0) {
            //check Free Memory
            pv = static_cast<void*>(&gblLUAreaAuxVar);
            if ((static_cast<LUAreaAuxVar*>(pv))->lAmountFreeMem >=
                    static_cast<long>(i + SIZE_LU_AREA_LIST_ITEM)) {
                sLV.lId = lId; //Save Id
                sLV.lsizeobj = i;
                sLV.pV = pv;
                sLV.arrLUAreaListElem = &gLUAreaMem.headLUAreaList;
                i = (static_cast<LUAreaAuxVar*>(pv))->shAmountPlacedLogicUnit; //Now Index in LUAreaListElem

                if (i) {
                    i--; //Detect Head
                    pv = static_cast<void*>(&sLV.arrLUAreaListElem[i]); //Last Elem
                    //Mem Area
                    iIptr_t = reinterpret_cast<intptr_t>(( static_cast<LUAreaListElem*>(pv))->pvLU);
                    //Add size
                    iIptr_t -= sLV.lsizeobj; //((LUAreaListElem*)pv)->shSizeLU;
                    //gblLUAreaAuxVar.pvHead -= ((LUAreaListElem*)pv)->shSizeLU
                    memcpy(reinterpret_cast<void*>(iIptr_t), pvObjImage, sLV.lsizeobj);
                    pv = static_cast<void*>(&sLV.arrLUAreaListElem[i + 1]); //Next
                    (static_cast<LUAreaListElem*>(pv))->shSizeLU = static_cast<short>(sLV.lsizeobj);
                    (static_cast<LUAreaListElem*>(pv))->shIdLU   = static_cast<short>(sLV.lId);
                    (static_cast<LUAreaListElem*>(pv))->pvLU     = reinterpret_cast<void*>(iIptr_t);
                    gblLUAreaAuxVar.pvHead = reinterpret_cast<void*>(iIptr_t); // (lId - sLV.lId);//For check Only
                    //sLV.pCLUBase = ((LUAreaListElem*) pv)->pvLU;
                    sLV.pCLUBase = static_cast<CLUBase*> (
                            (static_cast<LUAreaListElem*> (pv))->pvLU);
                } else {
                    pv = static_cast<void*>(&gLUAreaMem.headLUAreaList);

                    //First Init
                    iIptr_t = reinterpret_cast<intptr_t>(&gLUAreaMem.chArRamPrgEvt[SIZE_MEM_BLK]);
                    iIptr_t -= (sLV.lsizeobj);
                    (static_cast<LUAreaListElem*>(pv))->pvLU = reinterpret_cast<void*>(iIptr_t);
                    memcpy(reinterpret_cast<void*>(iIptr_t), pvObjImage, sLV.lsizeobj);
                    (static_cast<LUAreaListElem*>(pv) )->shSizeLU = static_cast<short>(sLV.lsizeobj);
                    (static_cast<LUAreaListElem*>(pv) )->shIdLU =   static_cast<short>(sLV.lId);
                    gblLUAreaAuxVar.pvHead = gblLUAreaAuxVar.pvTail =
                            (static_cast<LUAreaListElem*> (pv))->pvLU;
                    //sLV.pCLUBase = (CLUBase*) ((LUAreaListElem*) pv)->pvLU;
                    sLV.pCLUBase = static_cast<CLUBase*> (
                            (static_cast<LUAreaListElem*> (pv))->pvLU);
                }
                //Bield Obj in Mem


                //((LUAreaAuxVar*)pv)-> pvHead
                sLV.pCLUBase->SetOrderNumber(); //((LUAreaAuxVar*)pv)->shAmountPlacedLogicUnit += 1;
                pv = static_cast<void*>(&gblLUAreaAuxVar);
                //?!!!((LUAreaAuxVar*) pv)->lAmountFreeMem -= ((short) sLV.lsizeobj + SIZE_LU_AREA_LIST_ITEM);
                //?!!!((LUAreaAuxVar*) pv)->lAmountUsedMem += ((short) sLV.lsizeobj + SIZE_LU_AREA_LIST_ITEM);
                (static_cast<LUAreaAuxVar*> (pv))->lAmountFreeMem -= (sLV.lsizeobj + SIZE_LU_AREA_LIST_ITEM);
                (static_cast<LUAreaAuxVar*>(pv))->lAmountUsedMem += ( sLV.lsizeobj + SIZE_LU_AREA_LIST_ITEM);

            } else sLV.lsizeobj = 0;
        }
        return static_cast<long>(sLV.lsizeobj);
    }



    return 0; //AmountObj
}

void Shematic::DetectCircutLinks(void) {
    //Register Data In CrossRef Array
    long i, j;
    //    char **pCh;

    struct {
        short shAmtLU, shIdx;
        short shCounterScanedObj;
        long lBaseOrdNumStng;
        SBitFld_LUInInfo locSBitFld;
    } sLV;

    sLV.shIdx = sLV.shAmtLU = 0;
    if (preSetUP.n_input != 0) {
        //Detect Number Input
        sLV.shCounterScanedObj = 0;
        sLV.shAmtLU = preSetUP.n_input;
        sLV.lBaseOrdNumStng = 0;
        j = i = 0;
        ResetarNum();
        do {
            //Get Obj by Index
            GetHIDLU(&sLV.lBaseOrdNumStng, sLV.shCounterScanedObj); //HashIdLU
            //In test read data from External Storage
            if (sLV.lBaseOrdNumStng) {//Element present
                // i = sLV.shCounterScanedObj;
                arrSBitFldCRefInfo[i+ j].bfInfo_BaseID = sLV.lBaseOrdNumStng;
                arrSBitFldCRefInfo[i+ j].bfInfo_OrdNumIn = 1;
                arrSBitFldCRefInfo[i+ j].sBitLUInputInfo = ar_n__Output_Dsc[j];
                j++;
            }
        } while (++sLV.shCounterScanedObj < sLV.shAmtLU);
    }
    if (preSetUP.n_output != 0) {
        //Detect Number Input
        sLV.shCounterScanedObj = 0;
        sLV.shAmtLU = preSetUP.n_output;
        j = 0; //Idx in OutPut for Test
        sLV.shIdx += preSetUP.n_input;
        i = sLV.shIdx;//Offset Output
        ResetarNum();
        do {
            //Get Obj
            GetHIDLU(&sLV.lBaseOrdNumStng, sLV.shCounterScanedObj);
            //In test read data from External Storage
            if (sLV.lBaseOrdNumStng) {//Element present
                i = sLV.shCounterScanedObj+sLV.shIdx;
                arrSBitFldCRefInfo[i].bfInfo_BaseID = sLV.lBaseOrdNumStng;
                arrSBitFldCRefInfo[i].bfInfo_OrdNumIn = 1;
                arrSBitFldCRefInfo[i].sBitLUInputInfo = ar_n__Output_Dsc[j];//Take data from Taras
                j++;
            }
        } while (++sLV.shCounterScanedObj < sLV.shAmtLU);
    }
    if (preSetUP.n_led != 0) {
        //Detect Number Input
        sLV.shCounterScanedObj = 0;
        sLV.shAmtLU = preSetUP.n_led;
        j = 0; //Idx in OutPut for Test
        sLV.shIdx += preSetUP.n_output*shCLUDout_1_0_AmtIn;
        ResetarNum();
        do {
            //Get Obj
            GetHIDLU(&sLV.lBaseOrdNumStng, sLV.shCounterScanedObj); //HashIdLU
            //In test read data from External Storage
            if (sLV.lBaseOrdNumStng) {//Element present
                 i = sLV.shCounterScanedObj+sLV.shIdx;
                arrSBitFldCRefInfo[i].bfInfo_BaseID = sLV.lBaseOrdNumStng;
                arrSBitFldCRefInfo[i].bfInfo_OrdNumIn = 1;
                arrSBitFldCRefInfo[i].sBitLUInputInfo = ar_n__Output_Dsc[j];
                j++;
            }

        } while (++sLV.shCounterScanedObj < sLV.shAmtLU);
    }
    if (preSetUP.n_and != 0) {
        //Detect Number Input
        sLV.shCounterScanedObj = 0;
        sLV.shAmtLU = preSetUP.n_and;
        j = 0; //Idx in OutPut for Test
        sLV.shIdx += preSetUP.n_led*shCLULed_1_0_AmtIn;
        i = sLV.shIdx;
        ResetarNum();
        do {
            //Get Obj
            GetHIDLU(&sLV.lBaseOrdNumStng, sLV.shCounterScanedObj); //HashIdLU
            //In test read data from External Storage
            if (sLV.lBaseOrdNumStng) {//Element present
                 i = sLV.shCounterScanedObj*shCLUAnd_8_1_AmtIn+sLV.shIdx;
                SBitFld_LUInInfo locSBitFld_LUInInfo;//LUInInfoDsc locLUInInfoDsc;
                for (long ik = 0; ik < shCLUAnd_8_1_AmtIn; ik++) {
                    arrSBitFldCRefInfo[i+ik].bfInfo_BaseID = sLV.lBaseOrdNumStng;
                    arrSBitFldCRefInfo[i+ik].bfInfo_OrdNumIn = 1+ik;

                    locSBitFld_LUInInfo.bfInfo_OrdNumOut  = ar_n_And_Dsc[j].UN_BitFld_LUInInfo.sBitFld_LUInInfo.bfInfo_OrdNumOut;
                    locSBitFld_LUInInfo.bfInfo_IdLUStng   = ar_n_And_Dsc[j].UN_BitFld_LUInInfo.sBitFld_LUInInfo.bfInfo_IdLUStng;
                    locSBitFld_LUInInfo.bfInfo_OrdNumStng = ar_n_And_Dsc[j].UN_BitFld_LUInInfo.sBitFld_LUInInfo.bfInfo_OrdNumStng;
                    arrSBitFldCRefInfo[i+ik].sBitLUInputInfo = locSBitFld_LUInInfo;
                            //ar_n_And_Dsc[j+i+ik].UN_BitFld_LUInInfo.sBitFld_LUInInfo;
                    j++;//Can take change in any aviable way

                }


            }

        } while (++sLV.shCounterScanedObj < sLV.shAmtLU);
    }
    if (preSetUP.n_or != 0) {
        //Detect Number Input
        sLV.shCounterScanedObj = 0;
        sLV.shAmtLU = preSetUP.n_or;
         j = 0; //Idx in OutPut for Test
        sLV.shIdx += preSetUP.n_and*shCLUAnd_8_1_AmtIn;
        i = sLV.shIdx;
        ResetarNum();
        do {
            //Get Obj
            GetHIDLU(&sLV.lBaseOrdNumStng, sLV.shCounterScanedObj);
            //In test read data from External Storage
            if (sLV.lBaseOrdNumStng) {//Element present
                 i = sLV.shCounterScanedObj*shCLUOr_8_1_AmtIn+sLV.shIdx;
                SBitFld_LUInInfo locSBitFld_LUInInfo;//LUInInfoDsc locLUInInfoDsc;
                for (long ik = 0; ik < shCLUOr_8_1_AmtIn; ik++) {
                    arrSBitFldCRefInfo[i+ik].bfInfo_BaseID = sLV.lBaseOrdNumStng;
                    arrSBitFldCRefInfo[i+ik].bfInfo_OrdNumIn = 1+ik;

                    locSBitFld_LUInInfo.bfInfo_OrdNumOut  = ar_n_Or_Dsc[j].UN_BitFld_LUInInfo.sBitFld_LUInInfo.bfInfo_OrdNumOut;
                    locSBitFld_LUInInfo.bfInfo_IdLUStng   = ar_n_Or_Dsc[j].UN_BitFld_LUInInfo.sBitFld_LUInInfo.bfInfo_IdLUStng;
                    locSBitFld_LUInInfo.bfInfo_OrdNumStng = ar_n_Or_Dsc[j].UN_BitFld_LUInInfo.sBitFld_LUInInfo.bfInfo_OrdNumStng;
                    arrSBitFldCRefInfo[i+ik].sBitLUInputInfo = locSBitFld_LUInInfo;

                    j++;//Can take change in any aviable way
                }
            }
        } while (++sLV.shCounterScanedObj < sLV.shAmtLU);
    }
    if (preSetUP.n_xor != 0) {
        //Detect Number Input
        sLV.shCounterScanedObj = 0;
        sLV.shAmtLU = preSetUP.n_xor;
         j = 0; //Idx in OutPut for Test
        sLV.shIdx += preSetUP.n_or*shCLUOr_8_1_AmtIn;
        i = sLV.shIdx;
        ResetarNum();
        do {
            //Get Obj
            GetHIDLU(&sLV.lBaseOrdNumStng, sLV.shCounterScanedObj);
            //In test read data from External Storage
            if (sLV.lBaseOrdNumStng) {//Element present
                 i = sLV.shCounterScanedObj*shCLUXor_2_1_AmtIn+sLV.shIdx;
                SBitFld_LUInInfo locSBitFld_LUInInfo;//LUInInfoDsc locLUInInfoDsc;
                for (long ik = 0; ik < shCLUXor_2_1_AmtIn; ik++) {
                    arrSBitFldCRefInfo[i+ik].bfInfo_BaseID = sLV.lBaseOrdNumStng;
                    arrSBitFldCRefInfo[i+ik].bfInfo_OrdNumIn = 1+ik;

                    locSBitFld_LUInInfo.bfInfo_OrdNumOut  = ar_n_Xor_Dsc[j].UN_BitFld_LUInInfo.sBitFld_LUInInfo.bfInfo_OrdNumOut;
                    locSBitFld_LUInInfo.bfInfo_IdLUStng   = ar_n_Xor_Dsc[j].UN_BitFld_LUInInfo.sBitFld_LUInInfo.bfInfo_IdLUStng;
                    locSBitFld_LUInInfo.bfInfo_OrdNumStng = ar_n_Xor_Dsc[j].UN_BitFld_LUInInfo.sBitFld_LUInInfo.bfInfo_OrdNumStng;
                    arrSBitFldCRefInfo[i+ik].sBitLUInputInfo = locSBitFld_LUInInfo;

                    j++;//Can take change in any aviable way
                }
            }

        } while (++sLV.shCounterScanedObj < sLV.shAmtLU);
    }
    if (preSetUP.n_not != 0) {
        //Detect Number Input
        sLV.shCounterScanedObj = 0;
        sLV.shAmtLU = preSetUP.n_not;
         j = 0; //Idx in OutPut for Test
        sLV.shIdx += preSetUP.n_xor*shCLUXor_2_1_AmtIn;
        i = sLV.shIdx;
        ResetarNum();
        do {
            //Get Obj
            GetHIDLU(&sLV.lBaseOrdNumStng, sLV.shCounterScanedObj);
            //In test read data from External Storage
            if (sLV.lBaseOrdNumStng) {//Element present
                 i = sLV.shCounterScanedObj*shCLUNot_1_1_AmtIn+sLV.shIdx;
                SBitFld_LUInInfo locSBitFld_LUInInfo;//LUInInfoDsc locLUInInfoDsc;
                for (long ik = 0; ik < shCLUNot_1_1_AmtIn; ik++) {
                    arrSBitFldCRefInfo[i+ik].bfInfo_BaseID = sLV.lBaseOrdNumStng;
                    arrSBitFldCRefInfo[i+ik].bfInfo_OrdNumIn = 1+ik;

                    locSBitFld_LUInInfo.bfInfo_OrdNumOut  = ar_n_Not_Dsc[j].UN_BitFld_LUInInfo.sBitFld_LUInInfo.bfInfo_OrdNumOut;
                    locSBitFld_LUInInfo.bfInfo_IdLUStng   = ar_n_Not_Dsc[j].UN_BitFld_LUInInfo.sBitFld_LUInInfo.bfInfo_IdLUStng;
                    locSBitFld_LUInInfo.bfInfo_OrdNumStng = ar_n_Not_Dsc[j].UN_BitFld_LUInInfo.sBitFld_LUInInfo.bfInfo_OrdNumStng;
                    arrSBitFldCRefInfo[i+ik].sBitLUInputInfo = locSBitFld_LUInInfo;

                    j++;//Can take change in any aviable way
                }
            }
        } while (++sLV.shCounterScanedObj < sLV.shAmtLU);
    }
    sLV.shIdx = 0;
//Set Actual Links
    if (preSetUP.n_input != 0) {
        //Detect Number Input
        sLV.shCounterScanedObj = 0;
        sLV.shAmtLU = preSetUP.n_input;
        sLV.lBaseOrdNumStng = 0;
        j = i = 0;
        SBitFld_LUInInfo locSBitFld_LUInInfo;
        short shRelativeNumber = 0;
        short shIdLUStng       = 0;
        short shIdx_arrSBitFldCRefInfo = 0;
        do {
            //Change offset on real Number
            i = sLV.shCounterScanedObj; //
            locSBitFld_LUInInfo = arrSBitFldCRefInfo[i].sBitLUInputInfo;
            shIdLUStng          = locSBitFld_LUInInfo.bfInfo_IdLUStng;
            //Get Index in LU sequence
            switch (shIdLUStng) {
                case STNG_LU_AND:
                    shIdx_arrSBitFldCRefInfo = preSetUP.n_input
                     + preSetUP.n_output + preSetUP.n_led;
                    break;

                case STNG_LU_OR:
                     shIdx_arrSBitFldCRefInfo = preSetUP.n_input
                     + preSetUP.n_output + preSetUP.n_led + shCLUAnd_8_1_AmtIn*preSetUP.n_and;
                    break;

                case STNG_LU_XOR:
                    shIdx_arrSBitFldCRefInfo = preSetUP.n_input
                     + preSetUP.n_output + preSetUP.n_led + shCLUAnd_8_1_AmtIn*preSetUP.n_and
                     + shCLUOr_8_1_AmtIn*preSetUP.n_or ;
                    break;

                case STNG_LU_INPUT:
                    shIdx_arrSBitFldCRefInfo = 0;
                    break;

                case STNG_LU_OUTPUT:
                    shIdx_arrSBitFldCRefInfo = preSetUP.n_input;
                    break;

                case STNG_LU_LED:
                    shIdx_arrSBitFldCRefInfo = preSetUP.n_input
                        +preSetUP.n_output;
                    break;

                case STNG_LU_NOT:
                       shIdx_arrSBitFldCRefInfo = preSetUP.n_input
                     + preSetUP.n_output + preSetUP.n_led + shCLUAnd_8_1_AmtIn*preSetUP.n_and
                     + shCLUOr_8_1_AmtIn*preSetUP.n_or + shCLUXor_2_1_AmtIn*preSetUP.n_xor ;
                    break;


                default:
                    shIdx_arrSBitFldCRefInfo = -1;
            }

            shRelativeNumber = locSBitFld_LUInInfo.bfInfo_OrdNumStng;
            if(shIdx_arrSBitFldCRefInfo!= (-1)){
                //Find Element
                j = shIdx_arrSBitFldCRefInfo + shRelativeNumber-1; // Only Now
                locSBitFld_LUInInfo.bfInfo_OrdNumStng = arrSBitFldCRefInfo[j].bfInfo_BaseID; //sLV.lBaseOrdNumStng
                arrSBitFldCRefInfo[i].sBitLUInputInfo.bfInfo_OrdNumStng
                        = locSBitFld_LUInInfo.bfInfo_OrdNumStng;
            }

        } while (++sLV.shCounterScanedObj < sLV.shAmtLU);
        sLV.shIdx += preSetUP.n_input;
    }

    if (preSetUP.n_output != 0) {
        sLV.shCounterScanedObj = 0;
        sLV.shAmtLU = preSetUP.n_output;
        sLV.lBaseOrdNumStng = 0;
        do {
            i = sLV.shIdx + sLV.shCounterScanedObj;
            ChangeStngOrdnumRelOnBase(i);
        } while (++sLV.shCounterScanedObj < sLV.shAmtLU);
        sLV.shIdx += sLV.shCounterScanedObj;
    }
    if (preSetUP.n_led != 0) {
        sLV.shCounterScanedObj = 0;
        sLV.shAmtLU = preSetUP.n_led;
        sLV.lBaseOrdNumStng = 0;
        do {
            i = sLV.shIdx + sLV.shCounterScanedObj;
            ChangeStngOrdnumRelOnBase(i);
        } while (++sLV.shCounterScanedObj < sLV.shAmtLU);
        sLV.shIdx += sLV.shCounterScanedObj;
    }
    if (preSetUP.n_and != 0) {
        sLV.shCounterScanedObj = 0;
        sLV.shAmtLU = preSetUP.n_and;
        sLV.lBaseOrdNumStng = 0;
        do {
            i = sLV.shIdx + shCLUAnd_8_1_AmtIn*sLV.shCounterScanedObj;
            for(long ik = 0; ik < shCLUAnd_8_1_AmtIn; ik++){
                ChangeStngOrdnumRelOnBase(i+ik);
            }
        } while (++sLV.shCounterScanedObj < sLV.shAmtLU);
        sLV.shIdx += shCLUAnd_8_1_AmtIn*sLV.shCounterScanedObj;
    }
    if (preSetUP.n_or != 0) {
        sLV.shCounterScanedObj = 0;
        sLV.shAmtLU = preSetUP.n_or;
        sLV.lBaseOrdNumStng = 0;
        do {
            i = sLV.shIdx + shCLUOr_8_1_AmtIn*sLV.shCounterScanedObj;
            for(long ik = 0; ik < shCLUOr_8_1_AmtIn; ik++){
                ChangeStngOrdnumRelOnBase(i+ik);
            }
        } while (++sLV.shCounterScanedObj < sLV.shAmtLU);
        sLV.shIdx += shCLUOr_8_1_AmtIn*sLV.shCounterScanedObj;
    }
    if (preSetUP.n_xor != 0) {
        sLV.shCounterScanedObj = 0;
        sLV.shAmtLU = preSetUP.n_xor;
        sLV.lBaseOrdNumStng = 0;
        do {
            i = sLV.shIdx + shCLUXor_2_1_AmtIn*sLV.shCounterScanedObj;
            for(long ik = 0; ik < shCLUXor_2_1_AmtIn; ik++){
                ChangeStngOrdnumRelOnBase(i+ik);
            }
        } while (++sLV.shCounterScanedObj < sLV.shAmtLU);
        sLV.shIdx += shCLUXor_2_1_AmtIn*sLV.shCounterScanedObj;
    }
    if (preSetUP.n_not != 0) {
        sLV.shCounterScanedObj = 0;
        sLV.shAmtLU = preSetUP.n_not;
        sLV.lBaseOrdNumStng = 0;
        do {
            i = sLV.shIdx + shCLUNot_1_1_AmtIn*sLV.shCounterScanedObj;
            for(long ik = 0; ik < shCLUNot_1_1_AmtIn; ik++){
                ChangeStngOrdnumRelOnBase(i+ik);
            }
        } while (++sLV.shCounterScanedObj < sLV.shAmtLU);
        sLV.shIdx += shCLUNot_1_1_AmtIn*sLV.shCounterScanedObj;
    }

}
void Shematic::ChangeRelativeOnEvalLinks(void){

//Scan OutPut




}

void Shematic::ChangeStngOrdnumRelOnBase(long lIdxScanedObj) {
    register long i,j;
    SBitFld_LUInInfo locSBitFld_LUInInfo;
    short shRelativeNumber = 0;
    short shIdLUStng       = 0;
    short shIdx_arrSBitFldCRefInfo = 0;
    i = j = 0;
 //   do {
            //Change offset on real Number
            i = lIdxScanedObj; //i = sLV.shCounterScanedObj; //
    locSBitFld_LUInInfo = arrSBitFldCRefInfo[i].sBitLUInputInfo;
    shIdLUStng = locSBitFld_LUInInfo.bfInfo_IdLUStng;
    //Get Index in LU sequence
    switch (shIdLUStng) {
        case STNG_LU_AND:
            shIdx_arrSBitFldCRefInfo = preSetUP.n_input
                    + preSetUP.n_output + preSetUP.n_led;
            break;

        case STNG_LU_OR:
            shIdx_arrSBitFldCRefInfo = preSetUP.n_input
                    + preSetUP.n_output + preSetUP.n_led + shCLUAnd_8_1_AmtIn * preSetUP.n_and;
            break;

        case STNG_LU_XOR:
            shIdx_arrSBitFldCRefInfo = preSetUP.n_input
                    + preSetUP.n_output + preSetUP.n_led + shCLUAnd_8_1_AmtIn * preSetUP.n_and
                    + shCLUOr_8_1_AmtIn * preSetUP.n_or;
            break;

        case STNG_LU_INPUT:
            shIdx_arrSBitFldCRefInfo = 0;
            break;

        case STNG_LU_OUTPUT:
            shIdx_arrSBitFldCRefInfo = preSetUP.n_input;
            break;

        case STNG_LU_LED:
            shIdx_arrSBitFldCRefInfo = preSetUP.n_input
                    + preSetUP.n_output;
            break;

        case STNG_LU_NOT:
            shIdx_arrSBitFldCRefInfo = preSetUP.n_input
                    + preSetUP.n_output + preSetUP.n_led + shCLUAnd_8_1_AmtIn * preSetUP.n_and
                    + shCLUOr_8_1_AmtIn * preSetUP.n_or + shCLUXor_2_1_AmtIn * preSetUP.n_xor;
            break;


        default:
            shIdx_arrSBitFldCRefInfo = -1;
    }

    shRelativeNumber = locSBitFld_LUInInfo.bfInfo_OrdNumStng;
    if (shIdx_arrSBitFldCRefInfo != (-1)) {
        //Find Element
        j = shIdx_arrSBitFldCRefInfo + shRelativeNumber - 1; //Only Now
        locSBitFld_LUInInfo.bfInfo_OrdNumStng = arrSBitFldCRefInfo[j].bfInfo_BaseID; //sLV.lBaseOrdNumStng
        arrSBitFldCRefInfo[i].sBitLUInputInfo.bfInfo_OrdNumStng
                = locSBitFld_LUInInfo.bfInfo_OrdNumStng;
    }

//        } while (++sLV.shCounterScanedObj < sLV.shAmtLU);

}

long Shematic::Init2(void) {
    register long  j;
//    register void* pv;
    Init2LcVarArea lsLcVarArea;//lsLc -local struct Local Area
    lsLcVarArea.arrLUAreaListElem = &gLUAreaMem.headLUAreaList;
    lsLcVarArea.chErrCount = 0;
	shLssLUAreaListElemIndex = 0;
    p_current_config_prt = static_cast<void*>(&current_config_prt);
    //DetectCircutLinks();
    lsLcVarArea.shCounterInitCLUObj = 1;
    eLUTestLed.LinkTestLedTimers();
    if( current_config_prt.n_input ){
        CLUDInput_0_1 locCLUDInput_0_1(10, 0); // = CLUDInput_0_1(0,10);
        short shLC__n_input = current_config_prt.n_input;
        short shCounterInitCLUDIn = 0;
        lsLcVarArea.shIdxGlobalObjectMapPointers = 0;
        j = 0;
        do {
            j = InsertLU(LU_INPUT, static_cast<void*>(&locCLUDInput_0_1));

            if (j) {//Success Bield
                SetupCLUDInput_0_1StngParam(static_cast<void*>(&lsLcVarArea));
                shCounterInitCLUDIn++;
            }//Else Error
            else{
                lsLcVarArea.chErrCount |= 1;//Insert Data Error
            }

        } while (shCounterInitCLUDIn < shLC__n_input && j);
    }
    if (current_config_prt.n_output != 0) {
        CLUDout_1_0 locCLUDout_1_0(10, 0);
        short shLC__n_output = current_config_prt.n_output;
        short shCounterInitCLUDout = 0;
        lsLcVarArea.shIdxGlobalObjectMapPointers = 0;
        j = 0;
        do {
            j = InsertLU(LU_OUTPUT, static_cast<void*>(&locCLUDout_1_0));

            if (j) {//Success Bield
                SetupCLUDout_1_0StngParam(static_cast<void*>(&lsLcVarArea));
                shCounterInitCLUDout++;
            }//Else Error
             else{
                lsLcVarArea.chErrCount |= 1;//Insert Data Error
            }
        } while (shCounterInitCLUDout < shLC__n_output && j);
    }
    if (current_config_prt.n_led != 0) {
        CLULed locCLULed(10, 0);
        short shLC__n_led = current_config_prt.n_led;
        short shCounterInitCLULed = 0;

        lsLcVarArea.shIdxGlobalObjectMapPointers = 0;
        j = 0;
        do {
            j = InsertLU(LU_LED, static_cast<void*>(&locCLULed));
        if (j) {//Success Bield
                SetupCLULedStngParam(static_cast<void*>(&lsLcVarArea));
                shCounterInitCLULed++;
            }//Else Error
            else{
                    lsLcVarArea.chErrCount |= 1;//Insert Data Error
            }
        } while (shCounterInitCLULed < shLC__n_led && j);
    }
    if (current_config_prt.n_button != 0) {

        CLUFKey locCLUFKey(10, 0);
        short shLC__n_button = current_config_prt.n_button;
        short shCounterInitCLUFKey = 0;

        lsLcVarArea.shIdxGlobalObjectMapPointers = 0;
        j = 0;
        do {
            j = InsertLU(LU_FKEY, static_cast<void*>(&locCLUFKey));
        if (j) {//Success Bield
                SetupCLUFKeyStngParam(static_cast<void*>(&lsLcVarArea));
                shCounterInitCLUFKey++;
            }//Else Error
        else{
                lsLcVarArea.chErrCount |= 1;//Insert Data Error
            }
        } while (shCounterInitCLUFKey < shLC__n_button && j);

    }
    if (current_config_prt.n_alarm != 0) {

        CLULss locCLULss(10, 0);
        short shLC__n_alarm = current_config_prt.n_alarm;
        short shCounterInitCLULss = 0;

        lsLcVarArea.shIdxGlobalObjectMapPointers = 0;
        j = 0;
        do {
            j = InsertLU(LU_LSS, static_cast<void*>(&locCLULss));
        if (j) {//Success Bield
                SetupCLULssStngParam(static_cast<void*>(&lsLcVarArea));
                shCounterInitCLULss++;
            }//Else Error
        else{
                lsLcVarArea.chErrCount |= 1;//Insert Data Error
            }
        } while (shCounterInitCLULss < shLC__n_alarm && j);

    }
    if (current_config_prt.n_group_alarm != 0) {

        CBGSig locCBGSig(10, 0);
        short shLC__n_group_alarm = current_config_prt.n_group_alarm;
        short shCounterInitCBGSig = 0;

        lsLcVarArea.shIdxGlobalObjectMapPointers = 0;
        j = 0;
        do {
            j = InsertLU(LU_BGS, static_cast<void*>(&locCBGSig));
        if (j) {//Success Bield
                SetupCBGSigStngParam(static_cast<void*>(&lsLcVarArea));
                shCounterInitCBGSig++;
            }//Else Error
        else{
                lsLcVarArea.chErrCount |= 1;//Insert Data Error
            }    
        } while (shCounterInitCBGSig < shLC__n_group_alarm && j);

    }

    if (current_config_prt.n_and != 0) {
        CLUAnd_8_1 locCLUAnd_8_1(10, 0);
        short shLC__n_and = current_config_prt.n_and;
        short shCounterInitCLUAnd = 0;
        lsLcVarArea.shIdxGlobalObjectMapPointers = 0;
        j = 0;
        do {
            j = InsertLU(LU_AND, static_cast<void*>(&locCLUAnd_8_1));
        if (j) {//Success Bield
                SetupCLUAnd_8_1StngParam(static_cast<void*>(&lsLcVarArea));
                shCounterInitCLUAnd++;
            }//Else Error
         else{
                lsLcVarArea.chErrCount |= 1;//Insert Data Error
            }    
        } while (shCounterInitCLUAnd < shLC__n_and && j);
    }
    if (current_config_prt.n_or != 0) {
        CLUOr_8_1 locCLUOr_8_1(10, 0);
        short shLC__n_or = current_config_prt.n_or;
        short shCounterInitCLUOr = 0;
        lsLcVarArea.shIdxGlobalObjectMapPointers = 0;
        j = 0;
        do {
            j = InsertLU(LU_OR, static_cast<void*>(&locCLUOr_8_1));
        if (j) {//Success Bield
                SetupCLUOr_8_1StngParam(static_cast<void*>(&lsLcVarArea));
                shCounterInitCLUOr++;
            }//Else Error
        else{
                lsLcVarArea.chErrCount |= 1;//Insert Data Error
            }
        } while (shCounterInitCLUOr < shLC__n_or && j);
    }
    if (current_config_prt.n_xor != 0) {
        CLUXor_8_1 locCLUXor_8_1(10, 0);
        short shLC__n_xor = current_config_prt.n_xor;
        short shCounterInitCLUXor = 0;
        lsLcVarArea.shIdxGlobalObjectMapPointers = 0;
        j = 0;
        do {
            j = InsertLU(LU_XOR, static_cast<void*>(&locCLUXor_8_1));
        if (j) {//Success Bield
                SetupCLUXor_8_1StngParam(static_cast<void*>(&lsLcVarArea));
                shCounterInitCLUXor++;
            }
         else{
                lsLcVarArea.chErrCount |= 1;//Insert Data Error
            }
            //Else Error
        } while (shCounterInitCLUXor < shLC__n_xor && j);
    }
    if (current_config_prt.n_not != 0) {
        CLUNot_1_1 locCLUNot_1_1(10, 0);
        short shLC__n_not = current_config_prt.n_not;
        short shCounterInitCLUNot = 0;
        lsLcVarArea.shIdxGlobalObjectMapPointers = 0;
        j = 0;
        do {
            j = InsertLU(LU_NOT, static_cast<void*>(&locCLUNot_1_1));
        if (j) {//Success Bield
                SetupCLUNot_1_1StngParam(static_cast<void*>(&lsLcVarArea));
                shCounterInitCLUNot++;
            }//Else Error
         else{
                lsLcVarArea.chErrCount |= 1;//Insert Data Error
            }    
        } while (shCounterInitCLUNot < shLC__n_not && j);
    }
    if (current_config_prt.n_timer != 0) {
        CMft locCMft(10, 0);
        short shLC__n_timers = current_config_prt.n_timer;
        short shCounterInitCMft = 0;
        lsLcVarArea.shIdxGlobalObjectMapPointers = 0;
        j = 0;
        do {
            j = InsertLU(LU_MFT, static_cast<void*>(&locCMft));
        if (j) {//Success Bield
                SetupCLUMft_2_1StngParam(static_cast<void*>(&lsLcVarArea));
                shCounterInitCMft++;
            }//Else Error
          else{
                lsLcVarArea.chErrCount |= 1;//Insert Data Error
            }   
        } while (shCounterInitCMft < shLC__n_timers && j);
    }
    if (current_config_prt.n_trigger != 0) {

        CLUTrig locCLUTrig(10, 0);
        short shLC__n_trigger = current_config_prt.n_trigger;
        short shCounterInitCLUTrig = 0;

        lsLcVarArea.shIdxGlobalObjectMapPointers = 0;
        j = 0;
        do {
            j = InsertLU(LU_TRIGGERS, static_cast<void*>(&locCLUTrig));
        if (j) {//Success Bield
                SetupCLUTrigStngParam(static_cast<void*>(&lsLcVarArea));
                shCounterInitCLUTrig++;
            }//Else Error
         else{
                lsLcVarArea.chErrCount |= 1;//Insert Data Error
            }
        } while (shCounterInitCLUTrig < shLC__n_trigger && j);

    }
    if (current_config_prt.n_meander != 0) {

        CPulseAlternator locCPulseAlternator(10, 0);
        short shLC__n_meander = current_config_prt.n_meander;
        short shCounterInitCPulseAlternator = 0;

        lsLcVarArea.shIdxGlobalObjectMapPointers = 0;
        j = 0;
        do {
            j = InsertLU(LU_MEANDERS, static_cast<void*>(&locCPulseAlternator));
        if (j) {//Success Bield
                SetupCPulseAlternatorStngParam(static_cast<void*>(&lsLcVarArea));
                shCounterInitCPulseAlternator++;
            }//Else Error
             else{
                lsLcVarArea.chErrCount |= 1;//Insert Data Error
            }
        } while (shCounterInitCPulseAlternator < shLC__n_meander && j);

    }
    if (current_config_prt.n_tu != 0) {

        CLUTu locCLUTu(10, 0);
        short shLC__n_tu = current_config_prt.n_tu;
        short shCounterInitCLUTu = 0;

        lsLcVarArea.shIdxGlobalObjectMapPointers = 0;
        j = 0;
        do {
            j = InsertLU(LU_TU, static_cast<void*>(&locCLUTu));
        if (j) {//Success Bield
                SetupCLUTuStngParam(static_cast<void*>(&lsLcVarArea));
                shCounterInitCLUTu++;
            }//Else Error
             else{
                lsLcVarArea.chErrCount |= 1;//Insert Data Error
            }
        } while (shCounterInitCLUTu < shLC__n_tu && j);

    }
    if (current_config_prt.n_ts != 0) {

        CLUTs locCLUTs(10, 0);
        short shLC__n_ts = current_config_prt.n_ts;
        short shCounterInitCLUTs = 0;

        lsLcVarArea.shIdxGlobalObjectMapPointers = 0;
        j = 0;
        do {
            j = InsertLU(LU_TS, static_cast<void*>(&locCLUTs));
        if (j) {//Success Bield
                SetupCLUTsStngParam(static_cast<void*>(&lsLcVarArea));
                shCounterInitCLUTs++;
            }//Else Error
             else{
                lsLcVarArea.chErrCount |= 1;//Insert Data Error
            }
        } while (shCounterInitCLUTs < shLC__n_ts && j);

    }
       if (current_config_prt.n_input_GOOSE_block != 0) {

        CLUGoose locCLUGs(10, 0);
        short shLC__n_gs = current_config_prt.n_input_GOOSE_block;
        short shCounterInitCLUGs = 0;

        lsLcVarArea.shIdxGlobalObjectMapPointers = 0;
        j = 0;
        do {
            j = InsertLU(LU_GOOSE, static_cast<void*>(&locCLUGs));
        if (j) {//Success Bield
                SetupCLUGooseStngParam(static_cast<void*>(&lsLcVarArea));
                shCounterInitCLUGs++;
            }//Else Error
             else{
                lsLcVarArea.chErrCount |= 1;//Insert Data Error
            }
        } while (shCounterInitCLUGs < shLC__n_gs && j);

    }

   if (current_config_prt.n_input_MMS_block != 0) {

        CLUMms locCLUMms(10, 0);
        short shLC__n_mms = current_config_prt.n_input_MMS_block;
        short shCounterInitCLUMms = 0;

        lsLcVarArea.shIdxGlobalObjectMapPointers = 0;
        j = 0;
        do {
            j = InsertLU(LU_MMS, static_cast<void*>(&locCLUMms));
        if (j) {//Success Bield
                SetupCLUMmsStngParam(static_cast<void*>(&lsLcVarArea));
                shCounterInitCLUMms++;
            }//Else Error
             else{
                lsLcVarArea.chErrCount |= 1;//Insert Data Error
            }
        } while (shCounterInitCLUMms < shLC__n_mms && j);

    }

   if (current_config_prt.n_network_output_block != 0) {

        CLULan locCLULan(10, 0);
        short shLC__n_Lan = current_config_prt.n_network_output_block;
        short shCounterInitCLULan = 0;

        lsLcVarArea.shIdxGlobalObjectMapPointers = 0;
        j = 0;
        do {
            j = InsertLU(LU_LAN, static_cast<void*>(&locCLULan));
        if (j) {//Success Bield
                SetupCLULanStngParam(static_cast<void*>(&lsLcVarArea));
                shCounterInitCLULan++;
            }//Else Error
             else{
                lsLcVarArea.chErrCount |= 1;//Insert Data Error
            }
        } while (shCounterInitCLULan < shLC__n_Lan && j);
    }

    if (current_config_prt.n_log != 0) {

        CLULog locCLULog(10, 0);
        short shLC__n_log = 1;//current_config_prt.n_ts;
        short shCounterInitCLULog = 0;

        lsLcVarArea.shIdxGlobalObjectMapPointers = 0;
        j = 0;
        do {
            j = InsertLU(LU_LOG, static_cast<void*>(&locCLULog));
        if (j) {//Success Bield
                SetupCLULogStngParam(static_cast<void*>(&lsLcVarArea));
                shCounterInitCLULog++;
            }//Else Error
             else{
                lsLcVarArea.chErrCount |= 1;//Insert Data Error
            }
        } while (shCounterInitCLULog < shLC__n_log && j);

    }
    if(lsLcVarArea.chErrCount == 0){
        CFixBlockWrp locCFixBlockWrp(0,10);
        pCFixBlockWrp = static_cast<void*>(0);
         //FBWrp_Op(static_cast<void*>(&locCFixBlockWrp));
        j = 0;
        j = InsertLU(LU_STNG_FIX, static_cast<void*>(&locCFixBlockWrp));
        if (j == 0) 
            lsLcVarArea.chErrCount |= 1;//Insert Data Error
        else{
                 register void* pv;
                 register long l;
                 l = gblLUAreaAuxVar.shAmountPlacedLogicUnit;
                pv = static_cast<void*>(&(lsLcVarArea.arrLUAreaListElem[l-1])); 
                lsLcVarArea.pCLUBase = static_cast<CLUBase*>(
                        (static_cast<LUAreaListElem*>(pv))->pvLU);
                lsLcVarArea.pCLUBase->shShemasIdLUStng =  TARAS_ALAS_STNG_LU_STNG_FIX;
                lsLcVarArea.pCLUBase->shShemasOrdNumStng = 1;
                 ;//lsLcVarArea->shIdxGlobalObjectMapPointers + 1
                //lsLcVarArea->shCounterInitCLUObj++;
                CFixBlockWrp &lRefCFixBlockWrp = *(static_cast<CFixBlockWrp*>(lsLcVarArea.pCLUBase));
                lRefCFixBlockWrp.pOut = static_cast<void*>(lRefCFixBlockWrp.arrOut);
                lRefCFixBlockWrp.pIn   = static_cast<void*>(lRefCFixBlockWrp.arrPchIn);
                    for(l = 0; l < lRefCFixBlockWrp.chNumInput;l++)
                        lRefCFixBlockWrp.arrPchIn[l] = &chGblGround;
                  
                    lRefCFixBlockWrp.chTypeLogicFunction = LU_OP_STNG_FIX;
      #pragma calls=  FBWrp_Op 
        
                    lRefCFixBlockWrp.LogicFunc = FBWrp_Op;
                    lRefCFixBlockWrp.LogicFunc(static_cast<void*>(lsLcVarArea.pCLUBase));
            pCFixBlockWrp = static_cast<void*> (static_cast<void*>(lsLcVarArea.pCLUBase));   
            
            
                AllocInfo lAllocInfo = {0, 0,0,0};
                //lAllocInfo
                j = gblLUAreaAuxVar.shAmountPlacedLogicUnit ;//Fix Block Exclude
                j--;
                lAllocInfo.shSize = j<<2;//Link Add
                j = 0;
                j = AllocateObj(static_cast<void*>(&lAllocInfo));
                if (j == 0){ 
                    lsLcVarArea.chErrCount |= 1;//Insert Data Error
                    
                }
                else{
                pExecSeq   = lAllocInfo.pvDsc;
                j = lAllocInfo.shSize; shSizeExecSeq = j;
                j>>= 2;
                for (long k = 0; k < j; k++){
                    static_cast<long*>(pExecSeq)[k] = static_cast<long>(0xfccccccc);//Init Default Value
                }
                j = FillArr_n_linkVal();
                    if (j != 0)
                    lsLcVarArea.chErrCount |= 1;//Insert Data Error
                }
            //Alloc Mem for arrShCalcLUOrderNumsSchmHighLevel[] */
            
            }
        
    }
    //
    eRunErrorLed.UpdateRunErrorLed();
SetupCircutLinks2(static_cast<void*>(&lsLcVarArea));

eLUTestLed.UpdateCLUTestLed();
eMuteAlarmLed.UpdateMuteAlarmLed();
//Sort Element Now it 14-09-2018
return lsLcVarArea.chErrCount;

}

void Shematic::SetupCLUDInput_0_1StngParam(void *pv){
    register long i;
    register Init2LcVarArea *pInit2LcVarArea = static_cast<Init2LcVarArea*>(pv);
    i = gblLUAreaAuxVar.shAmountPlacedLogicUnit;
    pv = static_cast<void*>(&(pInit2LcVarArea->arrLUAreaListElem[i-1]));
    
    //pInit2LcVarArea->pCLUBase = (CLUBase*) ((LUAreaListElem*) pv)->pvLU;
    pInit2LcVarArea->pCLUBase = static_cast<CLUBase*>(
                        (static_cast<LUAreaListElem*>(pv))->pvLU);

    pInit2LcVarArea->pCLUBase->shShemasIdLUStng = TARAS_ALAS_STNG_LU_INPUT;
    i = pInit2LcVarArea->shCounterInitCLUObj-1; //sLV.shIdxLUOutDsc-1
    //---
    //pInit2LcVarArea->pCLUBase->shShemasOrdNumStng = static_cast<unsigned char>(
    //arrSBitFldCRefInfo[i].bfInfo_BaseID);
    //---
    pInit2LcVarArea->pCLUBase->shShemasOrdNumStng = 
        pInit2LcVarArea->shIdxGlobalObjectMapPointers + 1;//

    pInit2LcVarArea->shCounterInitCLUObj++;// sLV.shIdxLUOutDsc++;
    CLUDInput_0_1* locPCLUDInput_0_1 = static_cast<CLUDInput_0_1*>(pInit2LcVarArea->pCLUBase);
    locPCLUDInput_0_1->pOut = static_cast<void*>(locPCLUDInput_0_1->arrOut);
    locPCLUDInput_0_1->arrOut[0] = 0;
    CLUDInput_0_1& locRef_CLUDInput_0_1 =
            *(static_cast<CLUDInput_0_1*>(pInit2LcVarArea->pCLUBase));
    locRef_CLUDInput_0_1.chTypeLogicFunction = LU_OP_READ_DI;
    locRef_CLUDInput_0_1.LogicFunc = READ_DI_Op; //???
    //locRef_CLUDInput_0_1.LogicFunc(pInit2LcVarArea->pCLUBase);
    bool bbVar = false;
    do{
        //register char* pCh;
        __LN_INPUT *pLN_INPUT;
        short shRelativeIndexLU = 0;
        //__LN_OUTPUT_LED slc_LN_OUTPUT_LED;
        pLN_INPUT = reinterpret_cast<__LN_INPUT*>( spca_of_p_prt[ID_FB_INPUT - _ID_FB_FIRST_VAR]);
        i = EvalIdxinarrLUAreaListElem(TARAS_ALAS_STNG_LU_INPUT);//locRef_CLULed.
        shRelativeIndexLU = locRef_CLUDInput_0_1.shLUBieldOrdNum - i-1;
        locRef_CLUDInput_0_1.pvCfgLN = static_cast<void*> (pLN_INPUT + shRelativeIndexLU);
        //int32_t set_delay[INPUT_SET_DELAYS];//Dopusk DV
        //uint32_t control;//Postiynyy Zminnyy
        //INDEX_CTRL_INPUT_TYPE_SIGNAL 0-Postiynyy; 1- Zminnyy
        i = pLN_INPUT[shRelativeIndexLU].settings.control;
        locRef_CLUDInput_0_1.bbTypeSig = i&(1<<INDEX_CTRL_INPUT_TYPE_SIGNAL);
        locRef_CLUDInput_0_1.shTDelay  = pLN_INPUT[shRelativeIndexLU].settings.set_delay[0];

    }while(bbVar);


    i = pInit2LcVarArea->shIdxGlobalObjectMapPointers;//
    if( i == 0){
        arIdxLUAreaListElem[LU_INPUT-1] = gblLUAreaAuxVar.shAmountPlacedLogicUnit-1;
    }
UpdateDICfgSuit(i,locRef_CLUDInput_0_1.bbTypeSig,locRef_CLUDInput_0_1.shTDelay);
    GlobalObjectMap.arPCLUDInput_0_1[i] = static_cast<CLUDInput_0_1*>(
            pInit2LcVarArea->pCLUBase); //sLV.pCLUBase;
     
    pInit2LcVarArea->shIdxGlobalObjectMapPointers++;//sLV.shIdx++
}
void Shematic::SetupCLUDout_1_0StngParam(void *pv){
    register long i,j;
    register Init2LcVarArea *pInit2LcVarArea = static_cast<Init2LcVarArea*>(pv);
    i = gblLUAreaAuxVar.shAmountPlacedLogicUnit;
    pv = static_cast<void*>(&(pInit2LcVarArea->arrLUAreaListElem[i-1]));

    //pInit2LcVarArea->pCLUBase = (CLUBase*) ((LUAreaListElem*) pv)->pvLU;
    pInit2LcVarArea->pCLUBase = static_cast<CLUBase*>(
	(static_cast<LUAreaListElem*>(pv))->pvLU);

    pInit2LcVarArea->pCLUBase->shShemasIdLUStng =  TARAS_ALAS_STNG_LU_OUTPUT;
    i = pInit2LcVarArea->shCounterInitCLUObj - 1;
    //---
    //arrSBitFldCRefInfo[i].bfInfo_BaseID);
    //pInit2LcVarArea->pCLUBase->shShemasOrdNumStng = static_cast<unsigned char>(
    //---
    pInit2LcVarArea->pCLUBase->shShemasOrdNumStng = 
            pInit2LcVarArea->shIdxGlobalObjectMapPointers + 1;//?

    pInit2LcVarArea->shCounterInitCLUObj++;// sLV.shIdxLUOutDsc++;
    CLUDout_1_0* locPCLUDout_1_0 = static_cast<CLUDout_1_0*>(pInit2LcVarArea->pCLUBase);
    locPCLUDout_1_0->pIn = static_cast<void*>(locPCLUDout_1_0->arrPchIn);
    locPCLUDout_1_0->pOut = static_cast<void*>(locPCLUDout_1_0->arrOut);
    locPCLUDout_1_0->arrPchSchIn[0] = &chGblGround;
    for(i = 0; i < TOTAL_RELE_VISIO_IN;i++)
    locPCLUDout_1_0->arrPchIn[i] = &chGblGround;
    locPCLUDout_1_0->chTypeLogicFunction = LU_OP_SET_OUT;
    locPCLUDout_1_0->LogicFunc = SET_OUT_Op; //???
    bool bbVar = false;
    do{
        //register char* pCh;
        __LN_OUTPUT_LED *pLN_OUTPUT;
        short shRelativeIndexLU = 0;
        bool bbSel;
        pLN_OUTPUT = reinterpret_cast<__LN_OUTPUT_LED*>( spca_of_p_prt[ID_FB_OUTPUT - _ID_FB_FIRST_VAR]);
        i = EvalIdxinarrLUAreaListElem(TARAS_ALAS_STNG_LU_OUTPUT);//locRef_CLULed.
        shRelativeIndexLU = locPCLUDout_1_0->shLUBieldOrdNum - i-1;
        locPCLUDout_1_0->pvCfgLN = static_cast<void*> (pLN_OUTPUT+shRelativeIndexLU);
        //int32_t set_delay[INPUT_SET_DELAYS];//Dopusk DV
        //uint32_t control;//Postiynyy Zminnyy
        //INDEX_CTRL_INPUT_TYPE_SIGNAL 0-Postiynyy; 1- Zminnyy
        j = pLN_OUTPUT[shRelativeIndexLU].settings.control;
        bbSel = j&(1<< INDEX_CTRL_OUTPUT_LED_N_T);
        locPCLUDout_1_0->m_ReleyCfgSuit.chSel1 = bbSel;
        bbSel = j&(1<< INDEX_CTRL_OUTPUT_LED_C_I);
        locPCLUDout_1_0->m_ReleyCfgSuit.chSel2 = bbSel;
        bbSel = j&(1<< INDEX_CTRL_OUTPUT_LED_SI_EI);
        locPCLUDout_1_0->m_ReleyCfgSuit.chSel3 = bbSel;
        bbSel = pLN_OUTPUT[shRelativeIndexLU].d_trigger_state[OUTPUT_LED_D_TRIGGER_1/8];
        locPCLUDout_1_0->m_chQTrg06 = bbSel;
    }while(bbVar);
    locPCLUDout_1_0->UpdateCLUDout_1_0();
    j = pInit2LcVarArea->shIdxGlobalObjectMapPointers;
    if( j == 0){
        arIdxLUAreaListElem[LU_OUTPUT-1] = gblLUAreaAuxVar.shAmountPlacedLogicUnit-1;
    }
    GlobalObjectMap.arPCLUDout_1_0[j] = static_cast<CLUDout_1_0*>(
       pInit2LcVarArea->pCLUBase);
    pInit2LcVarArea->shIdxGlobalObjectMapPointers++;//sLV.shIdx++
}
void Shematic::SetupCLULedStngParam(void *pv){
    register long i,j;
    register Init2LcVarArea *pInit2LcVarArea = static_cast<Init2LcVarArea*>(pv);

    i = gblLUAreaAuxVar.shAmountPlacedLogicUnit;
    pv = static_cast<void*>(&(pInit2LcVarArea->arrLUAreaListElem[i-1]));
    pInit2LcVarArea->shIdxLUOut = i-1;
    //pInit2LcVarArea->pCLUBase = (CLUBase*) ((LUAreaListElem*) pv)->pvLU;
    pInit2LcVarArea->pCLUBase = static_cast<CLUBase*>(
                        (static_cast<LUAreaListElem*>(pv))->pvLU);
    pInit2LcVarArea->pCLUBase->shShemasIdLUStng =  TARAS_ALAS_STNG_LU_LED;
    i = pInit2LcVarArea->shCounterInitCLUObj - 1;

    //~arrSBitFldCRefInfo[i].bfInfo_BaseID);
    //~pInit2LcVarArea->pCLUBase->shShemasOrdNumStng = static_cast<unsigned char>(
    pInit2LcVarArea->pCLUBase->shShemasOrdNumStng = 
        pInit2LcVarArea->shIdxGlobalObjectMapPointers + 1;//Now Hash code?

    pInit2LcVarArea->shCounterInitCLUObj++;// sLV.shIdxLUOutDsc++;
    CLULed* locPCLULed = static_cast<CLULed*>(pInit2LcVarArea->pCLUBase);
    locPCLULed->pIn = static_cast<void*>(locPCLULed->arrPchIn);
    CLULed& locRef_CLULed = *(static_cast<CLULed*>(pInit2LcVarArea->pCLUBase));
    locRef_CLULed.arrPchSchIn[0] = &chGblGround;
    for(i = 0; i < TOTAL_LED_VISIO_IN;i++)
    locRef_CLULed.arrPchIn[i] = &chGblGround;
    locRef_CLULed.chTypeLogicFunction = LU_OP_SET_LED;
    locRef_CLULed.LogicFunc = SET_LED_Op; //???
    locRef_CLULed.pOut = static_cast<void*>(locRef_CLULed.arrOut);
    bool bbVar = false;
    do{
        //register char* pCh;
        __LN_OUTPUT_LED *pLN_OUTPUT_LED;
        short shRelativeIndexLU = 0;
        bool bbSel1,bbSel2,bbSel3;
        //__LN_OUTPUT_LED slc_LN_OUTPUT_LED;
        pLN_OUTPUT_LED = reinterpret_cast<__LN_OUTPUT_LED*>( spca_of_p_prt[ID_FB_LED - _ID_FB_FIRST_VAR]);
        j = EvalIdxinarrLUAreaListElem(TARAS_ALAS_STNG_LU_LED);//locRef_CLULed.
        shRelativeIndexLU = locRef_CLULed.shLUBieldOrdNum - j;
shRelativeIndexLU -= 1; 
        locRef_CLULed.pvCfgLN = static_cast<void*> (pLN_OUTPUT_LED+shRelativeIndexLU);
        j = pLN_OUTPUT_LED[shRelativeIndexLU].settings.control;
        
        bbSel1 = j&(1<< INDEX_CTRL_OUTPUT_LED_N_T);
        bbSel2 = j&(1<< INDEX_CTRL_OUTPUT_LED_C_I);
        bbSel3 = j&(1<< INDEX_CTRL_OUTPUT_LED_SI_EI);
        locRef_CLULed.m_LedCfgSuit.chSel1 = bbSel1;
        locRef_CLULed.m_LedCfgSuit.chSel2 = bbSel2;
        locRef_CLULed.m_LedCfgSuit.chSel3 = bbSel3;
        bbSel1 = pLN_OUTPUT_LED[shRelativeIndexLU].d_trigger_state[OUTPUT_LED_D_TRIGGER_1/8];
        locRef_CLULed.m_chQTrg06 = bbSel1;
        
    }while(bbVar);
    locRef_CLULed.UpdateCLULed();
    //-LUCfgInfo sLcLUCfgInfo;
    //-sLcLUCfgInfo.pvLUClass = static_cast<void*>(locPCLULed);
    //-sLcLUCfgInfo.pvCfgSuit = static_cast<void*>(&(locPCLULed->m_LedCfgSuit));
    //-sLcLUCfgInfo.pvChangeSuitFn = reinterpret_cast<void*>(0);
    //-i = ChangeCfgLULed(static_cast<void*>(&sLcLUCfgInfo));
    j = pInit2LcVarArea->shIdxGlobalObjectMapPointers;
    if( j == 0){
        arIdxLUAreaListElem[LU_LED-1] = gblLUAreaAuxVar.shAmountPlacedLogicUnit-1;
    }
    locRef_CLULed.arrPchIn[LED_IN_NAME__TEST_M-1 ] = &(eLUTestLed.arrOut[TEST_LED_OUT_NAME_TEST_M]);
    locRef_CLULed.arrPchIn[LED_IN_NAME__TLEDIN-1 ] = &(eLUTestLed.arrOut[TEST_LED_OUT_NAME_TEST_M+1+j]);

    GlobalObjectMap.arPCLULed[j] = static_cast<CLULed*>(
      pInit2LcVarArea->pCLUBase);
    pInit2LcVarArea->shIdxGlobalObjectMapPointers++;//sLV.shIdx++
}
void Shematic::SetupCLUAnd_8_1StngParam(void *pv){
    register long i,j;
    register Init2LcVarArea *pInit2LcVarArea = static_cast<Init2LcVarArea*>(pv);
    i = gblLUAreaAuxVar.shAmountPlacedLogicUnit;
    pv = static_cast<void*>(&(pInit2LcVarArea->arrLUAreaListElem[i-1]));
    pInit2LcVarArea->shIdxLUOut = i-1;
    //pInit2LcVarArea->pCLUBase = (CLUBase*) ((LUAreaListElem*) pv)->pvLU;
	pInit2LcVarArea->pCLUBase = static_cast<CLUBase*>(
                        (static_cast<LUAreaListElem*>(pv))->pvLU);
    pInit2LcVarArea->pCLUBase->shShemasIdLUStng =  TARAS_ALAS_STNG_LU_AND;
    i = pInit2LcVarArea->shCounterInitCLUObj - 1;

    //pInit2LcVarArea->pCLUBase->shShemasOrdNumStng = static_cast<unsigned char>(
    //arrSBitFldCRefInfo[i].bfInfo_BaseID);
    pInit2LcVarArea->pCLUBase->shShemasOrdNumStng = 
        pInit2LcVarArea->shIdxGlobalObjectMapPointers + 1;

    pInit2LcVarArea->shCounterInitCLUObj++;// sLV.shIdxLUOutDsc++;
    CLUAnd_8_1* locPCLUAnd_8_1 = static_cast<CLUAnd_8_1*>(pInit2LcVarArea->pCLUBase);
    locPCLUAnd_8_1->pOut = static_cast<void*>(locPCLUAnd_8_1->arrOut);
    locPCLUAnd_8_1->pIn  = static_cast<void*>(locPCLUAnd_8_1->arrPchIn);
    CLUAnd_8_1& locRef_CLUAnd_8_1 = *(static_cast<CLUAnd_8_1*>(pInit2LcVarArea->pCLUBase));
    locRef_CLUAnd_8_1.chTypeLogicFunction = LU_OP_AND; //
     for(i = 0; i < locRef_CLUAnd_8_1.chNumInput;i++)
    locRef_CLUAnd_8_1.arrPchIn[i] = &chGblVcc;
    locRef_CLUAnd_8_1.LogicFunc = AND_Op_8_1;//AND_Op_8_1; //???
    bool bbVar = false;
     
     do{
         __LN_AND *pLN_AND;
         short shRelativeIndexLU = 0;
         pLN_AND = reinterpret_cast<__LN_AND *>(spca_of_p_prt[ID_FB_AND - _ID_FB_FIRST_VAR]);
        i = EvalIdxinarrLUAreaListElem(TARAS_ALAS_STNG_LU_AND);//locRef_CLULed.
        shRelativeIndexLU = locRef_CLUAnd_8_1.shLUBieldOrdNum - i-1;
        locRef_CLUAnd_8_1.pvCfgLN = static_cast<void*> (pLN_AND+shRelativeIndexLU); 
     }while(bbVar);
    
    j = pInit2LcVarArea->shIdxGlobalObjectMapPointers;
    if( j == 0){
        arIdxLUAreaListElem[LU_AND-1] = gblLUAreaAuxVar.shAmountPlacedLogicUnit-1;
        if(shIdxSum8ElemSeq == 0)
            shIdxSum8ElemSeq = arIdxLUAreaListElem[LU_AND-1]; 
    }
    GlobalObjectMap.arPCLUAnd_8_1[j] = static_cast<CLUAnd_8_1*>(pInit2LcVarArea->pCLUBase);
    pInit2LcVarArea->shIdxGlobalObjectMapPointers++;//sLV.shIdx++
}
void Shematic::SetupCLUOr_8_1StngParam(void *pv){
    register long i,j;
    register Init2LcVarArea *pInit2LcVarArea = static_cast<Init2LcVarArea*>(pv);
    i = gblLUAreaAuxVar.shAmountPlacedLogicUnit;
    pv = static_cast<void*>(&(pInit2LcVarArea->arrLUAreaListElem[i-1]));
    pInit2LcVarArea->shIdxLUOut = i-1;
    //pInit2LcVarArea->pCLUBase = (CLUBase*) ((LUAreaListElem*) pv)->pvLU;
	pInit2LcVarArea->pCLUBase = static_cast<CLUBase*>(
                        (static_cast<LUAreaListElem*>(pv))->pvLU);
    pInit2LcVarArea->pCLUBase->shShemasIdLUStng =  TARAS_ALAS_STNG_LU_OR;
    i = pInit2LcVarArea->shCounterInitCLUObj - 1;
    //pInit2LcVarArea->pCLUBase->shShemasOrdNumStng = static_cast<unsigned char>(
    //arrSBitFldCRefInfo[i].bfInfo_BaseID);
    pInit2LcVarArea->shCounterInitCLUObj++;// sLV.shIdxLUOutDsc++;
     pInit2LcVarArea->pCLUBase->shShemasOrdNumStng = 
        pInit2LcVarArea->shIdxGlobalObjectMapPointers + 1;
    CLUOr_8_1* locPCLUOr_8_1 = static_cast<CLUOr_8_1*>(pInit2LcVarArea->pCLUBase);
    locPCLUOr_8_1->pOut = static_cast<void*>(locPCLUOr_8_1->arrOut);
    locPCLUOr_8_1->pIn  = static_cast<void*>(locPCLUOr_8_1->arrPchIn);
    CLUOr_8_1& locRef_CLUOr_8_1 = *(static_cast<CLUOr_8_1*>(pInit2LcVarArea->pCLUBase));
    for(i = 0; i < locRef_CLUOr_8_1.chNumInput;i++)
    locRef_CLUOr_8_1.arrPchIn[i] = &chGblGround;
    locRef_CLUOr_8_1.chTypeLogicFunction = LU_OP_OR;
    locRef_CLUOr_8_1.LogicFunc = OR_Op_8_1;//OR_Op_8_1;
    bool bbVar = false;
    do{
        ;
        __LN_OR *pLN_OR;
         short shRelativeIndexLU = 0;
         pLN_OR = reinterpret_cast<__LN_OR *>(spca_of_p_prt[ID_FB_OR - _ID_FB_FIRST_VAR]);
        i = EvalIdxinarrLUAreaListElem(TARAS_ALAS_STNG_LU_OR);//locRef_CLULed.
        shRelativeIndexLU = locRef_CLUOr_8_1.shLUBieldOrdNum - i-1;
        locRef_CLUOr_8_1.pvCfgLN = static_cast<void*> (pLN_OR+shRelativeIndexLU); 
    }while(bbVar);
    locRef_CLUOr_8_1.LogicFunc(pInit2LcVarArea->pCLUBase);
    j = pInit2LcVarArea->shIdxGlobalObjectMapPointers;
    if( j == 0){
        arIdxLUAreaListElem[LU_OR-1] = gblLUAreaAuxVar.shAmountPlacedLogicUnit-1;
        if(shIdxSum8ElemSeq == 0)
            shIdxSum8ElemSeq =  arIdxLUAreaListElem[LU_OR-1];
    }
    GlobalObjectMap.arPCLUOr_8_1[j] =
      static_cast<CLUOr_8_1*>(pInit2LcVarArea->pCLUBase);
    pInit2LcVarArea->shIdxGlobalObjectMapPointers++;//sLV.shIdx++
}
void Shematic::SetupCLUXor_8_1StngParam(void *pv){
    register long i,j;
    register Init2LcVarArea *pInit2LcVarArea = static_cast<Init2LcVarArea*>(pv);
    i = gblLUAreaAuxVar.shAmountPlacedLogicUnit;
    pv = static_cast<void*>(&(pInit2LcVarArea->arrLUAreaListElem[i-1]));
    //pInit2LcVarArea->pCLUBase = (CLUBase*) ((LUAreaListElem*) pv)->pvLU;
	pInit2LcVarArea->pCLUBase = static_cast<CLUBase*>(
                        (static_cast<LUAreaListElem*>(pv))->pvLU);
    pInit2LcVarArea->pCLUBase->shShemasIdLUStng =  TARAS_ALAS_STNG_LU_XOR;
    i = pInit2LcVarArea->shCounterInitCLUObj - 1;
    //pInit2LcVarArea->pCLUBase->shShemasOrdNumStng = static_cast<unsigned char>(
    //arrSBitFldCRefInfo[i].bfInfo_BaseID);
    pInit2LcVarArea->pCLUBase->shShemasOrdNumStng = 
        pInit2LcVarArea->shIdxGlobalObjectMapPointers + 1;

    pInit2LcVarArea->shCounterInitCLUObj++;// sLV.shIdxLUOutDsc++;
    CLUXor_8_1* locPCLUXor_8_1 = static_cast<CLUXor_8_1*>(pInit2LcVarArea->pCLUBase);
    locPCLUXor_8_1->pOut = static_cast<void*>(locPCLUXor_8_1->arrOut);
    locPCLUXor_8_1->pIn  = static_cast<void*>(locPCLUXor_8_1->arrPchIn);
    CLUXor_8_1& locRef_CLUXor_8_1 = *(static_cast<CLUXor_8_1*>(pInit2LcVarArea->pCLUBase));
    for(i = 0; i < locRef_CLUXor_8_1.chNumInput;i++)
    locRef_CLUXor_8_1.arrPchIn[i] = &chGblGround;
    locRef_CLUXor_8_1.chTypeLogicFunction = LU_OP_XOR;
    locRef_CLUXor_8_1.LogicFunc = XOR_Op_8_1;
    bool bbVar = false;
    do{
        __LN_XOR *pLN_XOR;
         short shRelativeIndexLU = 0;
         pLN_XOR = reinterpret_cast<__LN_XOR *>(spca_of_p_prt[ID_FB_XOR - _ID_FB_FIRST_VAR]);
        i = EvalIdxinarrLUAreaListElem(TARAS_ALAS_STNG_LU_XOR);//locRef_CLULed.
        shRelativeIndexLU = locRef_CLUXor_8_1.shLUBieldOrdNum - i-1;
        locRef_CLUXor_8_1.pvCfgLN = static_cast<void*> (pLN_XOR+shRelativeIndexLU); 
   
    }while(bbVar);
    locRef_CLUXor_8_1.LogicFunc(pInit2LcVarArea->pCLUBase);
    j = pInit2LcVarArea->shIdxGlobalObjectMapPointers;
    if( j == 0){
        arIdxLUAreaListElem[LU_XOR-1] = gblLUAreaAuxVar.shAmountPlacedLogicUnit-1;
        if(shIdxSum8ElemSeq == 0)
            shIdxSum8ElemSeq =  arIdxLUAreaListElem[LU_XOR-1];
    }
    GlobalObjectMap.arPCLUXor_8_1[j] =
      static_cast<CLUXor_8_1*>(pInit2LcVarArea->pCLUBase);
    pInit2LcVarArea->shIdxGlobalObjectMapPointers++;//sLV.shIdx++
}
void Shematic::SetupCLUNot_1_1StngParam(void *pv){
    register long i,j;
    register Init2LcVarArea *pInit2LcVarArea = static_cast<Init2LcVarArea*>(pv);
    i = gblLUAreaAuxVar.shAmountPlacedLogicUnit;
    pv = static_cast<void*>(&(pInit2LcVarArea->arrLUAreaListElem[i-1]));
    //pInit2LcVarArea->pCLUBase = (CLUBase*) ((LUAreaListElem*) pv)->pvLU;
	pInit2LcVarArea->pCLUBase = static_cast<CLUBase*>(
                        (static_cast<LUAreaListElem*>(pv))->pvLU);
    pInit2LcVarArea->pCLUBase->shShemasIdLUStng =  TARAS_ALAS_STNG_LU_NOT;
    i = pInit2LcVarArea->shCounterInitCLUObj - 1;
    //pInit2LcVarArea->pCLUBase->shShemasOrdNumStng = static_cast<unsigned char>(
    //arrSBitFldCRefInfo[i].bfInfo_BaseID);
     pInit2LcVarArea->pCLUBase->shShemasOrdNumStng = 
        pInit2LcVarArea->shIdxGlobalObjectMapPointers + 1;

    pInit2LcVarArea->shCounterInitCLUObj++;// sLV.shIdxLUOutDsc++;
    CLUNot_1_1* locPCLUNot_1_1 = static_cast<CLUNot_1_1*>(pInit2LcVarArea->pCLUBase);
    locPCLUNot_1_1->pOut = static_cast<void*>(locPCLUNot_1_1->arrOut);
    locPCLUNot_1_1->pIn  = static_cast<void*>(locPCLUNot_1_1->arrPchIn);
    CLUNot_1_1& locRef_CLUNot_1_1 = *(static_cast<CLUNot_1_1*>(pInit2LcVarArea->pCLUBase));
    for(i = 0; i < locRef_CLUNot_1_1.chNumInput;i++)
    locRef_CLUNot_1_1.arrPchIn[i] = &chGblGround;
    locRef_CLUNot_1_1.chTypeLogicFunction = LU_OP_NOT;
    locRef_CLUNot_1_1.LogicFunc = NOT_Op_1_1;
    //locRef_CLUNot_1_1.LogicFunc = NOT_Op_1_1;
    //locRef_CLUNot_1_1.LogicFunc(pInit2LcVarArea->pCLUBase);
    
    bool bbVar = false;
    do{
        __LN_NOT *pLN_NOT;
         short shRelativeIndexLU = 0;
         pLN_NOT = reinterpret_cast<__LN_NOT *>(spca_of_p_prt[ID_FB_NOT - _ID_FB_FIRST_VAR]);
        i = EvalIdxinarrLUAreaListElem(TARAS_ALAS_STNG_LU_NOT);//locRef_CLULed.
        shRelativeIndexLU = locRef_CLUNot_1_1.shLUBieldOrdNum - i-1;
        locRef_CLUNot_1_1.pvCfgLN = static_cast<void*> (pLN_NOT+shRelativeIndexLU); 
   
    }while(bbVar);
    j = pInit2LcVarArea->shIdxGlobalObjectMapPointers;
    if( j == 0){
        arIdxLUAreaListElem[LU_NOT-1] = gblLUAreaAuxVar.shAmountPlacedLogicUnit-1;
        if(shIdxSum8ElemSeq == 0)
            shIdxSum8ElemSeq =  arIdxLUAreaListElem[LU_NOT-1];
    }
    GlobalObjectMap.arPCLUNot_1_1[j] =
      static_cast<CLUNot_1_1*>(pInit2LcVarArea->pCLUBase);
    pInit2LcVarArea->shIdxGlobalObjectMapPointers++;//sLV.shIdx++
}
void Shematic::SetupCLUFKeyStngParam(void *pv){
    register long i,j;
    register Init2LcVarArea *pInit2LcVarArea = static_cast<Init2LcVarArea*>(pv);
    i = gblLUAreaAuxVar.shAmountPlacedLogicUnit;
    pv = static_cast<void*>(&(pInit2LcVarArea->arrLUAreaListElem[i-1]));
    //pInit2LcVarArea->pCLUBase = (CLUBase*) ((LUAreaListElem*) pv)->pvLU;
	pInit2LcVarArea->pCLUBase = static_cast<CLUBase*>(
                        (static_cast<LUAreaListElem*>(pv))->pvLU);
    pInit2LcVarArea->pCLUBase->shShemasIdLUStng =  TARAS_ALAS_STNG_LU_KEY;
    i = pInit2LcVarArea->shCounterInitCLUObj - 1;

    //pInit2LcVarArea->pCLUBase->shShemasOrdNumStng = static_cast<unsigned char>(
    //arrSBitFldCRefInfo[i].bfInfo_BaseID);
    pInit2LcVarArea->pCLUBase->shShemasOrdNumStng = 
        pInit2LcVarArea->shIdxGlobalObjectMapPointers + 1;//
    pInit2LcVarArea->shCounterInitCLUObj++;// sLV.shIdxLUOutDsc++;

    CLUFKey* locPCLUFKey = static_cast<CLUFKey*>(pInit2LcVarArea->pCLUBase);
    locPCLUFKey->pOut = static_cast<void*>(locPCLUFKey->arrOut);
    //locPCLUNot_1_1->pIn  = static_cast<void*>(locPCLUNot_1_1->arrPchIn);
    CLUFKey& locRef_CLUFKey = *(static_cast<CLUFKey*>(pInit2LcVarArea->pCLUBase));
    
    /*for(i = 0; i < locRef_CLUNot_1_1.chNumInput;i++)
    locRef_CLUNot_1_1.arrPchIn[i] = &chGblGround;*/
    locRef_CLUFKey.chTypeLogicFunction = LU_OP_F_KEY;
    locRef_CLUFKey.LogicFunc = FKey_Op;
    locRef_CLUFKey.LogicFunc(pInit2LcVarArea->pCLUBase);
     bool bbVar = false;
    do{
        __LN_BUTTON *pLN_BUTTON_TU;
        short shRelativeIndexLU = 0;
     pLN_BUTTON_TU = reinterpret_cast<__LN_BUTTON*>( spca_of_p_prt[ID_FB_BUTTON - _ID_FB_FIRST_VAR]);   
     j = EvalIdxinarrLUAreaListElem(TARAS_ALAS_STNG_LU_KEY);
        shRelativeIndexLU = locRef_CLUFKey.shLUBieldOrdNum - j - 1;
    locRef_CLUFKey.pvCfgLN = static_cast<void*> (pLN_BUTTON_TU+shRelativeIndexLU);     
    locRef_CLUFKey.pIn = static_cast<void*>(&(pLN_BUTTON_TU[shRelativeIndexLU].active_state[0]));
    }while(bbVar);
    j = pInit2LcVarArea->shIdxGlobalObjectMapPointers;
    if( j == 0){
        arIdxLUAreaListElem[LU_FKEY-1] = gblLUAreaAuxVar.shAmountPlacedLogicUnit-1;
    }
    GlobalObjectMap.arPCLUFKey[j] = locPCLUFKey;
    //  static_cast<CLUFKey*>(pInit2LcVarArea->pCLUBase);
    pInit2LcVarArea->shIdxGlobalObjectMapPointers++;//sLV.shIdx++

}
void Shematic::SetupCLULssStngParam(void *pv){
    register long i,j;
    register Init2LcVarArea *pInit2LcVarArea = static_cast<Init2LcVarArea*>(pv);
    i = gblLUAreaAuxVar.shAmountPlacedLogicUnit;
    pv = static_cast<void*>(&(pInit2LcVarArea->arrLUAreaListElem[i-1]));
    //pInit2LcVarArea->pCLUBase = (CLUBase*) ((LUAreaListElem*) pv)->pvLU;
	pInit2LcVarArea->pCLUBase = static_cast<CLUBase*>(
                        (static_cast<LUAreaListElem*>(pv))->pvLU);
    pInit2LcVarArea->pCLUBase->shShemasIdLUStng =  TARAS_ALAS_STNG_LU_ALARMS;
    i = pInit2LcVarArea->shCounterInitCLUObj - 1;

    //pInit2LcVarArea->pCLUBase->shShemasOrdNumStng = static_cast<unsigned char>(
    //arrSBitFldCRefInfo[i].bfInfo_BaseID);
    pInit2LcVarArea->pCLUBase->shShemasOrdNumStng = 
        pInit2LcVarArea->shIdxGlobalObjectMapPointers + 1;//
    pInit2LcVarArea->shCounterInitCLUObj++;// sLV.shIdxLUOutDsc++;

    CLULss* locPCLULss = static_cast<CLULss*>(pInit2LcVarArea->pCLUBase);
    locPCLULss->pOut = static_cast<void*>(locPCLULss->arrOut);
    locPCLULss->pIn  = static_cast<void*>(locPCLULss->arrPchIn);
    CLULss& locRef_CLULss = *(static_cast<CLULss*> (pInit2LcVarArea->pCLUBase));
    locRef_CLULss.UpdateCLss();
    
    for(i = 0; i < locRef_CLULss.chNumInput;i++)
        locRef_CLULss.arrPchIn[i] = &chGblGround;
    locRef_CLULss.LinkLssTimers();
    locRef_CLULss.chTypeLogicFunction = LU_OP_LSS;
    locRef_CLULss.LogicFunc = LssOp;
    locRef_CLULss.LogicFunc(pInit2LcVarArea->pCLUBase);
    bool bbVar = false;
    do{
        __LN_ALARM *p__LN_ALARM;
        short shRelativeIndexLU = 0;
        //bool bbSel;
        p__LN_ALARM = reinterpret_cast<__LN_ALARM*>( spca_of_p_prt[ID_FB_ALARM - _ID_FB_FIRST_VAR]);
        j = EvalIdxinarrLUAreaListElem(TARAS_ALAS_STNG_LU_ALARMS);
        shRelativeIndexLU = locRef_CLULss.shLUBieldOrdNum - j - 1;
        locRef_CLULss.pvCfgLN = static_cast<void*> (p__LN_ALARM+shRelativeIndexLU);
        j = p__LN_ALARM[shRelativeIndexLU].settings.control;
        locRef_CLULss.m_LssCfgSuit.chSel = j;
        i = p__LN_ALARM[shRelativeIndexLU].settings.set_delay[0];
        locRef_CLULss.m_LssCfgSuit.lTCs = i /5;
                
    }while(bbVar);
    j = pInit2LcVarArea->shIdxGlobalObjectMapPointers;
    if( j == 0){
        arIdxLUAreaListElem[LU_LSS-1] = gblLUAreaAuxVar.shAmountPlacedLogicUnit-1;
        if(shIdxSum8ElemSeq == 0)
            shIdxSum8ElemSeq =  arIdxLUAreaListElem[LU_LSS-1];
    }
    GlobalObjectMap.arPCLULss[j] = locPCLULss;      //static_cast<CLULss*>(pInit2LcVarArea->pCLUBase);
    
    pInit2LcVarArea->shIdxGlobalObjectMapPointers++;//sLV.shIdx++

}
extern const uint32_t group_alarm_analog_ctrl_patten[][2];
void Shematic::SetupCBGSigStngParam(void *pv){
    register long i,j;
    register Init2LcVarArea *pInit2LcVarArea = static_cast<Init2LcVarArea*>(pv);
    i = gblLUAreaAuxVar.shAmountPlacedLogicUnit;
    pv = static_cast<void*>(&(pInit2LcVarArea->arrLUAreaListElem[i-1]));
    //pInit2LcVarArea->pCLUBase = (CLUBase*) ((LUAreaListElem*) pv)->pvLU;
	pInit2LcVarArea->pCLUBase = static_cast<CLUBase*>(
                        (static_cast<LUAreaListElem*>(pv))->pvLU);
    pInit2LcVarArea->pCLUBase->shShemasIdLUStng =  TARAS_ALAS_STNG_LU_BGS;
    i = pInit2LcVarArea->shCounterInitCLUObj - 1;

    //pInit2LcVarArea->pCLUBase->shShemasOrdNumStng = static_cast<unsigned char>(
    //arrSBitFldCRefInfo[i].bfInfo_BaseID);
    pInit2LcVarArea->pCLUBase->shShemasOrdNumStng = 
        pInit2LcVarArea->shIdxGlobalObjectMapPointers + 1;//
    pInit2LcVarArea->shCounterInitCLUObj++;// sLV.shIdxLUOutDsc++;

    CBGSig* locPCBGSig = static_cast<CBGSig*>(pInit2LcVarArea->pCLUBase);
	locPCBGSig->UpdateCBGSig();
    locPCBGSig->pOut = static_cast<void*>(locPCBGSig->arrOut);
    locPCBGSig->pIn  = static_cast<void*>(locPCBGSig->arrPchIn);
    CBGSig& locRef_CBGSig = *(static_cast<CBGSig*>(pInit2LcVarArea->pCLUBase));
    
    for(i = 0; i < locRef_CBGSig.chNumInput;i++)
    locRef_CBGSig.arrPchIn[i] = &chGblGround;
	locRef_CBGSig.LinkBGSigTimers();
    locRef_CBGSig.chTypeLogicFunction = LU_OP_BGS;
    locRef_CBGSig.LogicFunc = BGSig_Op;
    locRef_CBGSig.LogicFunc(pInit2LcVarArea->pCLUBase);
   
    do {
        __LN_GROUP_ALARM *pLN_GROUP_ALARM;
        short shRelativeIndexLU = 0;
        volatile char chMaskaI = 0,chShiftI = 0;
    pLN_GROUP_ALARM = 
    reinterpret_cast<__LN_GROUP_ALARM*>( spca_of_p_prt[ID_FB_GROUP_ALARM - _ID_FB_FIRST_VAR]);  
    j = EvalIdxinarrLUAreaListElem(TARAS_ALAS_STNG_LU_BGS);
    shRelativeIndexLU = locRef_CBGSig.shLUBieldOrdNum - j;
    shRelativeIndexLU -= 1;
    locRef_CBGSig.pvCfgLN = static_cast<void*>(pLN_GROUP_ALARM+shRelativeIndexLU);
    j = pLN_GROUP_ALARM[shRelativeIndexLU].settings.control;
    locRef_CBGSig.m_BGSigSuit.chCheckBgs =  j&(1<< INDEX_CTRL_GROUP_ALARM_CTRL_STATE);      
    locRef_CBGSig.m_BGSigSuit.chStateGS  =  j&(1<< INDEX_CTRL_GROUP_ALARM_STATE);     
    locRef_CBGSig.m_BGSigSuit.lIust  = pLN_GROUP_ALARM[shRelativeIndexLU].settings.pickup[0];  
    j = pLN_GROUP_ALARM[shRelativeIndexLU].settings.set_delay[0];
    locRef_CBGSig.m_BGSigSuit.lTWait = j /5;
    chMaskaI = (1 << group_alarm_analog_ctrl_patten[INDEX_CTRL_GROUP_ALARM_I - _MAX_INDEX_CTRL_GROUP_ALARM_BITS_SETTINGS][1]) - 1;
    chShiftI = group_alarm_analog_ctrl_patten[INDEX_CTRL_GROUP_ALARM_I - _MAX_INDEX_CTRL_GROUP_ALARM_BITS_SETTINGS][0];


    i = pLN_GROUP_ALARM[shRelativeIndexLU].settings.analog_input_control;
        i >>= chShiftI;
        i  &= chMaskaI; 
    if (i > 0)
        locRef_CBGSig.m_chNumberAnalogChanell = i - 1;
    else
        locRef_CBGSig.m_chNumberAnalogChanell = i;//--!!!Mean not Selected Index Really!!!!
    
        CBGSig::PickUPs     [shRelativeIndexLU]  = locRef_CBGSig.m_BGSigSuit.lIust;
        CBGSig::ChanelsNames[shRelativeIndexLU]  = locRef_CBGSig.m_chNumberAnalogChanell;
    }while(false);
    j = pInit2LcVarArea->shIdxGlobalObjectMapPointers;
    if( j == 0){
        arIdxLUAreaListElem[LU_BGS-1] = gblLUAreaAuxVar.shAmountPlacedLogicUnit-1;
        if(shIdxSum8ElemSeq == 0)
            shIdxSum8ElemSeq =  arIdxLUAreaListElem[LU_BGS-1];
    }
    GlobalObjectMap.arPCBGSig[j] =
      static_cast<CBGSig*>(pInit2LcVarArea->pCLUBase);
    pInit2LcVarArea->shIdxGlobalObjectMapPointers++;//sLV.shIdx++

}

void Shematic::SetupCLUMft_2_1StngParam(void *pv){
    register long i,j;
    register Init2LcVarArea *pInit2LcVarArea = static_cast<Init2LcVarArea*>(pv);
    i = gblLUAreaAuxVar.shAmountPlacedLogicUnit;
    pv = static_cast<void*>(&(pInit2LcVarArea->arrLUAreaListElem[i-1]));
    //pInit2LcVarArea->pCLUBase = (CLUBase*) ((LUAreaListElem*) pv)->pvLU;
    pInit2LcVarArea->pCLUBase = static_cast<CLUBase*> (
            (static_cast<LUAreaListElem*> (pv))->pvLU);
    pInit2LcVarArea->pCLUBase->shShemasIdLUStng =  TARAS_ALAS_STNG_LU_MFT;
    i = pInit2LcVarArea->shCounterInitCLUObj - 1;
//    pInit2LcVarArea->pCLUBase->shShemasOrdNumStng = static_cast<unsigned char>(
//    arrSBitFldCRefInfo[i].bfInfo_BaseID);
    pInit2LcVarArea->pCLUBase->shShemasOrdNumStng = 
        pInit2LcVarArea->shIdxGlobalObjectMapPointers + 1;
    
    pInit2LcVarArea->shCounterInitCLUObj++;// sLV.shIdxLUOutDsc++;
    //CLUNot_1_1* locPCLUNot_1_1 = static_cast<CLUNot_1_1*>(pInit2LcVarArea->pCLUBase);
    //locPCLUNot_1_1->pOut = static_cast<void*>(locPCLUNot_1_1->arrOut);
    //locPCLUNot_1_1->pIn  = static_cast<void*>(locPCLUNot_1_1->arrPchIn);
    CMft& rCMft = *(static_cast<CMft*>(pInit2LcVarArea->pCLUBase));
    for(i = 0; i < rCMft.chNumInput;i++)
    rCMft.arrPchIn[i] = &chGblGround;

    rCMft.UpdateCMft();
    i = rCMft.LinkMftTimers();
    if(i== 5){
       rCMft.chTypeLogicFunction = LU_OP_MFT; //
       rCMft.LogicFunc = Mft_Op;
        bool bbVar = false;
        do{
            __LN_TIMER *pLN_TIMER;
            short shRelativeIndexLU = 0;
            pLN_TIMER = reinterpret_cast<__LN_TIMER*>(spca_of_p_prt[ID_FB_TIMER - _ID_FB_FIRST_VAR]);
            j = EvalIdxinarrLUAreaListElem(TARAS_ALAS_STNG_LU_MFT);
            shRelativeIndexLU = rCMft.shLUBieldOrdNum - j;
            shRelativeIndexLU -= 1;
            rCMft.pvCfgLN = static_cast<void*>(pLN_TIMER + shRelativeIndexLU);
            long lT1,lT2;
            lT1 = pLN_TIMER[shRelativeIndexLU].settings.set_delay[TIMER_SET_DELAY_PAUSE];
            lT2 = pLN_TIMER[shRelativeIndexLU].settings.set_delay[TIMER_SET_DELAY_WORK ];
            //rCMft.m_MftSuit.lTpause 
            //rCMft.m_MftSuit.lTWork  
            rCMft.m_MftSuit.lTpause = lT1 /5;
            rCMft.m_MftSuit.lTWork  = lT2 /5;
            rCMft.m_MftSuit.lTdelay = lT2 /5;
        }while(bbVar);
       
    }
    //rCMft.LogicFunc(pInit2LcVarArea->pCLUBase);
    //???
    j = pInit2LcVarArea->shIdxGlobalObjectMapPointers;
    if( j == 0){
        arIdxLUAreaListElem[LU_MFT-1] = gblLUAreaAuxVar.shAmountPlacedLogicUnit-1;
        if(shIdxSum8ElemSeq == 0)
            shIdxSum8ElemSeq =  arIdxLUAreaListElem[LU_MFT-1];
    }
    GlobalObjectMap.arCMft[j] =
      static_cast<CMft*>(pInit2LcVarArea->pCLUBase);
    pInit2LcVarArea->shIdxGlobalObjectMapPointers++;//sLV.shIdx++
}
void Shematic::SetupCLUTrigStngParam(void *pv){
    register long i,j;
    register Init2LcVarArea *pInit2LcVarArea = static_cast<Init2LcVarArea*>(pv);
    i = gblLUAreaAuxVar.shAmountPlacedLogicUnit;
    pv = static_cast<void*>(&(pInit2LcVarArea->arrLUAreaListElem[i-1]));
    //pInit2LcVarArea->pCLUBase = (CLUBase*) ((LUAreaListElem*) pv)->pvLU;
    pInit2LcVarArea->pCLUBase = static_cast<CLUBase*> (
            (static_cast<LUAreaListElem*> (pv))->pvLU);
    pInit2LcVarArea->pCLUBase->shShemasIdLUStng = TARAS_ALAS_STNG_LU_TRIGGER;
    i = pInit2LcVarArea->shCounterInitCLUObj - 1;

    //pInit2LcVarArea->pCLUBase->shShemasOrdNumStng = static_cast<unsigned char>(
    //arrSBitFldCRefInfo[i].bfInfo_BaseID);
    pInit2LcVarArea->pCLUBase->shShemasOrdNumStng = 
        pInit2LcVarArea->shIdxGlobalObjectMapPointers + 1;//
    pInit2LcVarArea->shCounterInitCLUObj++;// sLV.shIdxLUOutDsc++;

    CLUTrig* locPCLUTrig = static_cast<CLUTrig*>(pInit2LcVarArea->pCLUBase);
    //locPCLUFKey->pOut = static_cast<void*>(locPCLUFKey->arrOut);
    //locPCLUNot_1_1->pIn  = static_cast<void*>(locPCLUNot_1_1->arrPchIn);
    CLUTrig& locRef_CLUTrig = *(static_cast<CLUTrig*>(pInit2LcVarArea->pCLUBase));
    locRef_CLUTrig.UpdateCLUTrig();
    
    for(i = 0; i < locRef_CLUTrig.chNumInput;i++)
    locRef_CLUTrig.arrPchIn[i] = &chGblGround;
    locRef_CLUTrig.chTypeLogicFunction = LU_OP_D_TRG__4_2;
    locRef_CLUTrig.LogicFunc = DTRG_Op_4_2;
    locRef_CLUTrig.LogicFunc(pInit2LcVarArea->pCLUBase);
    bool bbVar = false;
    do{
        __LN_TRIGGER *pLN_TRIGGER;
        short shRelativeIndexLU = 0;
        //bool bbSel;
        pLN_TRIGGER = reinterpret_cast<__LN_TRIGGER*>( spca_of_p_prt[ID_FB_TRIGGER - _ID_FB_FIRST_VAR]);
        j = EvalIdxinarrLUAreaListElem(TARAS_ALAS_STNG_LU_TRIGGER);
        shRelativeIndexLU = locRef_CLUTrig.shLUBieldOrdNum - j - 1;
        locRef_CLUTrig.pvCfgLN = static_cast<void*> (pLN_TRIGGER+shRelativeIndexLU);
        j = static_cast<long>(
                pLN_TRIGGER[shRelativeIndexLU].settings.param[0]);//control
        
    }while(bbVar );
    j = pInit2LcVarArea->shIdxGlobalObjectMapPointers;
    if( j == 0){
        arIdxLUAreaListElem[LU_TRIGGERS-1] = gblLUAreaAuxVar.shAmountPlacedLogicUnit-1;
        if(shIdxSum8ElemSeq == 0)
            shIdxSum8ElemSeq =  arIdxLUAreaListElem[LU_TRIGGERS-1];    
    }
    GlobalObjectMap.arPCLUTrig[j] = locPCLUTrig;
    //  static_cast<CLUTrig*>(pInit2LcVarArea->pCLUBase);
    pInit2LcVarArea->shIdxGlobalObjectMapPointers++;//sLV.shIdx++

}

void Shematic::SetupCPulseAlternatorStngParam(void *pv){
    register long i,j;
    register Init2LcVarArea *pInit2LcVarArea = static_cast<Init2LcVarArea*>(pv);
    i = gblLUAreaAuxVar.shAmountPlacedLogicUnit;
    pv = static_cast<void*>(&(pInit2LcVarArea->arrLUAreaListElem[i-1]));
    //pInit2LcVarArea->pCLUBase = (CLUBase*) ((LUAreaListElem*) pv)->pvLU;
	pInit2LcVarArea->pCLUBase = static_cast<CLUBase*>(
                        (static_cast<LUAreaListElem*>(pv))->pvLU);
    pInit2LcVarArea->pCLUBase->shShemasIdLUStng =  TARAS_ALAS_STNG_LU_MEANDERS;
    i = pInit2LcVarArea->shCounterInitCLUObj - 1;

    //pInit2LcVarArea->pCLUBase->shShemasOrdNumStng = static_cast<unsigned char>(
    //arrSBitFldCRefInfo[i].bfInfo_BaseID);
    pInit2LcVarArea->pCLUBase->shShemasOrdNumStng = 
        pInit2LcVarArea->shIdxGlobalObjectMapPointers + 1;//
    pInit2LcVarArea->shCounterInitCLUObj++;// sLV.shIdxLUOutDsc++;

    CPulseAlternator* locPCPulseAlternator = static_cast<CPulseAlternator*>(pInit2LcVarArea->pCLUBase);
    locPCPulseAlternator->pOut = static_cast<void*>(locPCPulseAlternator->arrOut);
    //locPCLUNot_1_1->pIn  = static_cast<void*>(locPCLUNot_1_1->arrPchIn);
    CPulseAlternator& locRef_CPulseAlternator = *(static_cast<CPulseAlternator*>(pInit2LcVarArea->pCLUBase));
    //locRef_CPulseAlternator.LogicFunc(pInit2LcVarArea->pCLUBase);
//    /-*for(i = 0; i < locRef_CLUNot_1_1.chNumInput;i++)
//    locRef_CLUNot_1_1.arrPchIn[i] = &chGblGround;*=/
    locRef_CPulseAlternator.chTypeLogicFunction = LU_OP_MEANDR;
    locRef_CPulseAlternator.LogicFunc = PulseAlt_Op;
    __LN_MEANDER *pLN_MEANDER;
    short shRelativeIndexLU = 0;
    pLN_MEANDER = reinterpret_cast<__LN_MEANDER*> (spca_of_p_prt[ID_FB_MEANDER - _ID_FB_FIRST_VAR]);
    i = EvalIdxinarrLUAreaListElem(TARAS_ALAS_STNG_LU_MEANDERS); //locRef_CLULed.
    shRelativeIndexLU = locRef_CPulseAlternator.shLUBieldOrdNum - i - 1;
    locRef_CPulseAlternator.pvCfgLN = static_cast<void*> (pLN_MEANDER+shRelativeIndexLU);
    j = pLN_MEANDER[shRelativeIndexLU].settings.set_delay[MEANDER_SET_DELAY_PERIOD];
    locRef_CPulseAlternator.m_PulseAltCfgSuit.shTAlternator = j/5;
    locRef_CPulseAlternator.m_NodeTicAlt.lTmrVal = locRef_CPulseAlternator.m_PulseAltCfgSuit.shTAlternator;
    locRef_CPulseAlternator.LinkPulseAltTimer();
    j = pInit2LcVarArea->shIdxGlobalObjectMapPointers;
    if( j == 0){
        arIdxLUAreaListElem[LU_MEANDERS-1] = gblLUAreaAuxVar.shAmountPlacedLogicUnit-1;
        if(shIdxSum8ElemSeq == 0)
            shIdxSum8ElemSeq =  arIdxLUAreaListElem[LU_MEANDERS-1];
    }
    GlobalObjectMap.arPCPulseAlternator[j] =
      static_cast<CPulseAlternator*>(pInit2LcVarArea->pCLUBase);
    pInit2LcVarArea->shIdxGlobalObjectMapPointers++;//sLV.shIdx++

}
void Shematic::SetupCLUTuStngParam(void *pv){
    register long i,j;
    register Init2LcVarArea *pInit2LcVarArea = static_cast<Init2LcVarArea*>(pv);
    i = gblLUAreaAuxVar.shAmountPlacedLogicUnit;
    pv = static_cast<void*>(&(pInit2LcVarArea->arrLUAreaListElem[i-1]));
    //pInit2LcVarArea->pCLUBase = (CLUBase*) ((LUAreaListElem*) pv)->pvLU;
	pInit2LcVarArea->pCLUBase = static_cast<CLUBase*>(
                        (static_cast<LUAreaListElem*>(pv))->pvLU);
    pInit2LcVarArea->pCLUBase->shShemasIdLUStng =  TARAS_ALAS_STNG_LU_TU;
    i = pInit2LcVarArea->shCounterInitCLUObj - 1;

    //pInit2LcVarArea->pCLUBase->shShemasOrdNumStng = static_cast<unsigned char>(
    //arrSBitFldCRefInfo[i].bfInfo_BaseID);
    pInit2LcVarArea->pCLUBase->shShemasOrdNumStng = 
        pInit2LcVarArea->shIdxGlobalObjectMapPointers + 1;//
    pInit2LcVarArea->shCounterInitCLUObj++;// sLV.shIdxLUOutDsc++;

    CLUTu* locPCLUTu = static_cast<CLUTu*>(pInit2LcVarArea->pCLUBase);
    locPCLUTu->pOut = static_cast<void*>(locPCLUTu->arrOut);
    locPCLUTu->pIn  = static_cast<void*>(locPCLUTu->arrPchIn);
    CLUTu& locRef_CLUTu = *(static_cast<CLUTu*>(pInit2LcVarArea->pCLUBase));
    for(i = 0; i < locRef_CLUTu.chNumInput;i++)
    locRef_CLUTu.arrPchIn[i] = &chGblGround;
    locRef_CLUTu.chTypeLogicFunction = LU_OP_TU;
    locRef_CLUTu.LogicFunc = TU_Op;
    //locRef_CLUTu.LogicFunc(pInit2LcVarArea->pCLUBase);
    bool bbVar = false;
    do {
        __LN_TU *pLN_TU;
        short shRelativeIndexLU = 0;
        pLN_TU = reinterpret_cast<__LN_TU *> (spca_of_p_prt[ID_FB_TU - _ID_FB_FIRST_VAR]);
        i = EvalIdxinarrLUAreaListElem(TARAS_ALAS_STNG_LU_TU); //locRef_CLULed.
        shRelativeIndexLU = locRef_CLUTu.shLUBieldOrdNum - i - 1;
        locRef_CLUTu.pvCfgLN = static_cast<void*> (pLN_TU + shRelativeIndexLU);
        j = static_cast<long>(
                pLN_TU[shRelativeIndexLU].settings.param[0]);//control
    } while (bbVar);
    locRef_CLUTu.LogicFunc(pInit2LcVarArea->pCLUBase);
    j = pInit2LcVarArea->shIdxGlobalObjectMapPointers;
    if( j == 0){
        arIdxLUAreaListElem[LU_TU-1] = gblLUAreaAuxVar.shAmountPlacedLogicUnit-1;
        if(shIdxSumNTUPlusNLANSeq == 0)
        shIdxSumNTUPlusNLANSeq = arIdxLUAreaListElem[LU_TU-1];
    }
    GlobalObjectMap.arPCLUTu[j] =
      static_cast<CLUTu*>(pInit2LcVarArea->pCLUBase);
    pInit2LcVarArea->shIdxGlobalObjectMapPointers++;//sLV.shIdx++

}
void Shematic::SetupCLUTsStngParam(void *pv){
    register long i,j;
    register Init2LcVarArea *pInit2LcVarArea = static_cast<Init2LcVarArea*>(pv);
    i = gblLUAreaAuxVar.shAmountPlacedLogicUnit;
    pv = static_cast<void*>(&(pInit2LcVarArea->arrLUAreaListElem[i-1]));
    //pInit2LcVarArea->pCLUBase = (CLUBase*) ((LUAreaListElem*) pv)->pvLU;
	pInit2LcVarArea->pCLUBase = static_cast<CLUBase*>(
                        (static_cast<LUAreaListElem*>(pv))->pvLU);
    pInit2LcVarArea->pCLUBase->shShemasIdLUStng =  TARAS_ALAS_STNG_LU_TS;
    i = pInit2LcVarArea->shCounterInitCLUObj - 1;

    //pInit2LcVarArea->pCLUBase->shShemasOrdNumStng = static_cast<unsigned char>(
    //arrSBitFldCRefInfo[i].bfInfo_BaseID);
    pInit2LcVarArea->pCLUBase->shShemasOrdNumStng = 
        pInit2LcVarArea->shIdxGlobalObjectMapPointers + 1;//
    pInit2LcVarArea->shCounterInitCLUObj++;// sLV.shIdxLUOutDsc++;

    CLUTs* locPCLUTs = static_cast<CLUTs*>(pInit2LcVarArea->pCLUBase);
    locPCLUTs->pOut = static_cast<void*>(locPCLUTs->arrOut);
    locPCLUTs->pIn  = static_cast<void*>(locPCLUTs->arrPchIn);
    CLUTs& locRef_CLUTs = *(static_cast<CLUTs*>(pInit2LcVarArea->pCLUBase));
    for(i = 0; i < locRef_CLUTs.chNumInput;i++)
    locRef_CLUTs.arrPchIn[i] = &chGblGround;
    locRef_CLUTs.chTypeLogicFunction = LU_OP_TS;
    locRef_CLUTs.LogicFunc = Ts__2_1_Op;
    
     bool bbVar = false;
    do {
        __LN_TS *pLN_TS;
        short shRelativeIndexLU = 0;
        pLN_TS = reinterpret_cast<__LN_TS *> (spca_of_p_prt[ID_FB_TS - _ID_FB_FIRST_VAR]);
        i = EvalIdxinarrLUAreaListElem(TARAS_ALAS_STNG_LU_TS); //locRef_CLULed.
        shRelativeIndexLU = locRef_CLUTs.shLUBieldOrdNum - i - 1;
        locRef_CLUTs.pvCfgLN = static_cast<void*> (pLN_TS + shRelativeIndexLU);
    } while (bbVar);
    locRef_CLUTs.LogicFunc(pInit2LcVarArea->pCLUBase);
    j = pInit2LcVarArea->shIdxGlobalObjectMapPointers;
    if( j == 0){
        arIdxLUAreaListElem[LU_TS-1] = gblLUAreaAuxVar.shAmountPlacedLogicUnit-1;
        if(shIdxSumNTUPlusNLANSeq == 0)
        shIdxSumNTUPlusNLANSeq = arIdxLUAreaListElem[LU_TS-1];
    }
    GlobalObjectMap.arPCLUTs[j] =
      static_cast<CLUTs*>(pInit2LcVarArea->pCLUBase);
    pInit2LcVarArea->shIdxGlobalObjectMapPointers++;//sLV.shIdx++

}
void Shematic::SetupCLUGooseStngParam(void *pv){
    register long i,j;
    register Init2LcVarArea *pInit2LcVarArea = static_cast<Init2LcVarArea*>(pv);
    i = gblLUAreaAuxVar.shAmountPlacedLogicUnit;
    pv = static_cast<void*>(&(pInit2LcVarArea->arrLUAreaListElem[i-1]));
    //pInit2LcVarArea->pCLUBase = (CLUBase*) ((LUAreaListElem*) pv)->pvLU;
	pInit2LcVarArea->pCLUBase = static_cast<CLUBase*>(
                        (static_cast<LUAreaListElem*>(pv))->pvLU);
    pInit2LcVarArea->pCLUBase->shShemasIdLUStng =  TARAS_ALAS_STNG_LU_GOOSE;
    i = pInit2LcVarArea->shCounterInitCLUObj - 1;

    //pInit2LcVarArea->pCLUBase->shShemasOrdNumStng = static_cast<unsigned char>(
    //arrSBitFldCRefInfo[i].bfInfo_BaseID);
    pInit2LcVarArea->pCLUBase->shShemasOrdNumStng = 
        pInit2LcVarArea->shIdxGlobalObjectMapPointers + 1;//
    pInit2LcVarArea->shCounterInitCLUObj++;// sLV.shIdxLUOutDsc++;

    CLUGoose* locPCLUGs = static_cast<CLUGoose*>(pInit2LcVarArea->pCLUBase);
    locPCLUGs->pOut = static_cast<void*>(locPCLUGs->arrOut);
    locPCLUGs->pIn  = static_cast<void*>(locPCLUGs->arrPchIn);
    CLUGoose& locRef_CLUGs = *(static_cast<CLUGoose*>(pInit2LcVarArea->pCLUBase));
    
    for(i = 0; i < locRef_CLUGs.chNumInput;i++)
    locRef_CLUGs.arrPchIn[i] = &chGblGround;
    locRef_CLUGs.chTypeLogicFunction = LU_OP_GOOSE;
    locRef_CLUGs.LogicFunc = Goose__1_8_Op;
    
     bool bbVar = false;
    do {
        __LN_INPUT_GOOSE_BLOCK *pLN_GOOSE;
        short shRelativeIndexLU = 0;
        pLN_GOOSE = reinterpret_cast<__LN_INPUT_GOOSE_BLOCK *> (spca_of_p_prt[ID_FB_INPUT_GOOSE_BLOCK - _ID_FB_FIRST_VAR]);
        i = EvalIdxinarrLUAreaListElem(TARAS_ALAS_STNG_LU_GOOSE); //locRef_CLULed.
        shRelativeIndexLU = locRef_CLUGs.shLUBieldOrdNum - i - 1;
        locRef_CLUGs.pvCfgLN = static_cast<void*> (pLN_GOOSE + shRelativeIndexLU);
    } while (bbVar);
    locRef_CLUGs.LogicFunc(pInit2LcVarArea->pCLUBase);
    j = pInit2LcVarArea->shIdxGlobalObjectMapPointers;
    if( j == 0){
        arIdxLUAreaListElem[LU_GOOSE-1] = gblLUAreaAuxVar.shAmountPlacedLogicUnit-1;
        if(shIdxSumNTUPlusNLANSeq == 0)
        shIdxSumNTUPlusNLANSeq = arIdxLUAreaListElem[LU_GOOSE-1];
    }
    GlobalObjectMap.arPCLUGoose[j] =
      static_cast<CLUGoose*>(pInit2LcVarArea->pCLUBase);
    pInit2LcVarArea->shIdxGlobalObjectMapPointers++;//sLV.shIdx++

}
void Shematic::SetupCLUMmsStngParam(void *pv){
    register long i,j;
    register Init2LcVarArea *pInit2LcVarArea = static_cast<Init2LcVarArea*>(pv);
    i = gblLUAreaAuxVar.shAmountPlacedLogicUnit;
    pv = static_cast<void*>(&(pInit2LcVarArea->arrLUAreaListElem[i-1]));
    //pInit2LcVarArea->pCLUBase = (CLUBase*) ((LUAreaListElem*) pv)->pvLU;
	pInit2LcVarArea->pCLUBase = static_cast<CLUBase*>(
                        (static_cast<LUAreaListElem*>(pv))->pvLU);
    pInit2LcVarArea->pCLUBase->shShemasIdLUStng =  TARAS_ALAS_STNG_LU_MMS;
    i = pInit2LcVarArea->shCounterInitCLUObj - 1;

    //pInit2LcVarArea->pCLUBase->shShemasOrdNumStng = static_cast<unsigned char>(
    //arrSBitFldCRefInfo[i].bfInfo_BaseID);
    pInit2LcVarArea->pCLUBase->shShemasOrdNumStng = 
        pInit2LcVarArea->shIdxGlobalObjectMapPointers + 1;//
    pInit2LcVarArea->shCounterInitCLUObj++;// sLV.shIdxLUOutDsc++;

    CLUMms* locPCLUMms = static_cast<CLUMms*>(pInit2LcVarArea->pCLUBase);
    locPCLUMms->pOut = static_cast<void*>(locPCLUMms->arrOut);
    locPCLUMms->pIn  = static_cast<void*>(locPCLUMms->arrPchIn);
    CLUMms& locRef_CLUMms = *(static_cast<CLUMms*>(pInit2LcVarArea->pCLUBase));
    for(i = 0; i < locRef_CLUMms.chNumInput;i++)
    locRef_CLUMms.arrPchIn[i] = &chGblGround;
    locRef_CLUMms.chTypeLogicFunction = LU_OP_MMS;
    locRef_CLUMms.LogicFunc = Mms__2_8_Op;
    
     bool bbVar = false;
    do {
        __LN_INPUT_MMS_BLOCK *pLN_MMS;
        short shRelativeIndexLU = 0;
        pLN_MMS = reinterpret_cast<__LN_INPUT_MMS_BLOCK *> (spca_of_p_prt[ID_FB_INPUT_MMS_BLOCK - _ID_FB_FIRST_VAR]);
        i = EvalIdxinarrLUAreaListElem(TARAS_ALAS_STNG_LU_MMS); //locRef_CLULed.
        shRelativeIndexLU = locRef_CLUMms.shLUBieldOrdNum - i - 1;
        locRef_CLUMms.pvCfgLN = static_cast<void*> (pLN_MMS + shRelativeIndexLU);
    } while (bbVar);
    locRef_CLUMms.LogicFunc(pInit2LcVarArea->pCLUBase);
    j = pInit2LcVarArea->shIdxGlobalObjectMapPointers;
    if( j == 0){
        arIdxLUAreaListElem[LU_MMS-1] = gblLUAreaAuxVar.shAmountPlacedLogicUnit-1;
        if(shIdxSumNTUPlusNLANSeq == 0)
        shIdxSumNTUPlusNLANSeq = arIdxLUAreaListElem[LU_MMS-1];
    }
    GlobalObjectMap.arPCLUMms[j] =
      static_cast<CLUMms*>(pInit2LcVarArea->pCLUBase);
    pInit2LcVarArea->shIdxGlobalObjectMapPointers++;//sLV.shIdx++

}
void Shematic::SetupCLULanStngParam(void *pv){
    register long i,j;
    register Init2LcVarArea *pInit2LcVarArea = static_cast<Init2LcVarArea*>(pv);
    i = gblLUAreaAuxVar.shAmountPlacedLogicUnit;
    pv = static_cast<void*>(&(pInit2LcVarArea->arrLUAreaListElem[i-1]));
    //pInit2LcVarArea->pCLUBase = (CLUBase*) ((LUAreaListElem*) pv)->pvLU;
	pInit2LcVarArea->pCLUBase = static_cast<CLUBase*>(
                        (static_cast<LUAreaListElem*>(pv))->pvLU);
    pInit2LcVarArea->pCLUBase->shShemasIdLUStng =  TARAS_ALAS_STNG_LU_LAN;
    i = pInit2LcVarArea->shCounterInitCLUObj - 1;

    //pInit2LcVarArea->pCLUBase->shShemasOrdNumStng = static_cast<unsigned char>(
    //arrSBitFldCRefInfo[i].bfInfo_BaseID);
    pInit2LcVarArea->pCLUBase->shShemasOrdNumStng = 
        pInit2LcVarArea->shIdxGlobalObjectMapPointers + 1;//
    pInit2LcVarArea->shCounterInitCLUObj++;// sLV.shIdxLUOutDsc++;

    CLULan* locPCLULan = static_cast<CLULan*>(pInit2LcVarArea->pCLUBase);
    locPCLULan->pOut = static_cast<void*>(locPCLULan->arrOut);
    locPCLULan->pIn  = static_cast<void*>(locPCLULan->arrPchIn);
    CLULan& locRef_CLULan = *(static_cast<CLULan*>(pInit2LcVarArea->pCLUBase));
    for(i = 0; i < locRef_CLULan.chNumInput;i++)
    locRef_CLULan.arrPchIn[i] = &chGblGround;
    locRef_CLULan.chTypeLogicFunction = LU_OP_LAN;
    locRef_CLULan.LogicFunc = Lan__9_8_Op;
    
     bool bbVar = false;
    do {
        __LN_NETWORK_OUTPUT_BLOCK *pLN_LAN;
        short shRelativeIndexLU = 0;
        pLN_LAN = reinterpret_cast<__LN_NETWORK_OUTPUT_BLOCK *> (spca_of_p_prt[ID_FB_NETWORK_OUTPUT_BLOCK - _ID_FB_FIRST_VAR]);
        i = EvalIdxinarrLUAreaListElem(TARAS_ALAS_STNG_LU_LAN); //locRef_CLULed.
        shRelativeIndexLU = locRef_CLULan.shLUBieldOrdNum - i - 1;
        locRef_CLULan.pvCfgLN = static_cast<void*> (pLN_LAN + shRelativeIndexLU);
    } while (bbVar);
    locRef_CLULan.LogicFunc(pInit2LcVarArea->pCLUBase);
    j = pInit2LcVarArea->shIdxGlobalObjectMapPointers;
    if( j == 0){
        arIdxLUAreaListElem[LU_LAN-1] = gblLUAreaAuxVar.shAmountPlacedLogicUnit-1;
        if(shIdxSumNTUPlusNLANSeq == 0)
        shIdxSumNTUPlusNLANSeq = arIdxLUAreaListElem[LU_LAN-1];
    }
    GlobalObjectMap.arPCLULan[j] =
      static_cast<CLULan*>(pInit2LcVarArea->pCLUBase);
    pInit2LcVarArea->shIdxGlobalObjectMapPointers++;//sLV.shIdx++

}

void Shematic::SetupCLULogStngParam(void *pv){//Check It Separatly
    register long i,j;
    register Init2LcVarArea *pInit2LcVarArea = static_cast<Init2LcVarArea*>(pv);
    i = gblLUAreaAuxVar.shAmountPlacedLogicUnit;
    pv = static_cast<void*>(&(pInit2LcVarArea->arrLUAreaListElem[i-1]));
 //   #warning SetupCLULogStngParam not Complite. It may contain Error!!!  
    //pInit2LcVarArea->pCLUBase = (CLUBase*) ((LUAreaListElem*) pv)->pvLU;
	pInit2LcVarArea->pCLUBase = static_cast<CLUBase*>(
                        (static_cast<LUAreaListElem*>(pv))->pvLU);
    pInit2LcVarArea->pCLUBase->shShemasIdLUStng =  TARAS_ALAS_STNG_LU_LOG;
    i = pInit2LcVarArea->shCounterInitCLUObj - 1;

    //pInit2LcVarArea->pCLUBase->shShemasOrdNumStng = static_cast<unsigned char>(
    //arrSBitFldCRefInfo[i].bfInfo_BaseID);
    pInit2LcVarArea->pCLUBase->shShemasOrdNumStng = 
        pInit2LcVarArea->shIdxGlobalObjectMapPointers + 1;//
    pInit2LcVarArea->shCounterInitCLUObj++;// sLV.shIdxLUOutDsc++;

    CLULog* locPCLULog = static_cast<CLULog*>(pInit2LcVarArea->pCLUBase);
    locPCLULog->pOut = static_cast<void*>(locPCLULog->arrOut);
    //locPCLUTs->pIn  = static_cast<void*>(locPCLUTs->arrPchIn);
    
    CLULog& locRef_CLULog = *(static_cast<CLULog*>(pInit2LcVarArea->pCLUBase));
//    for(i = 0; i < locRef_CLUTs.chNumInput;i++)
//    locRef_CLUTs.arrPchIn[i] = &chGblGround;
    locRef_CLULog.chTypeLogicFunction = LU_OP_LOG;
    locRef_CLULog.LogicFunc = Log_Op;
    locRef_CLULog.LogicFunc(pInit2LcVarArea->pCLUBase);
    
//     bool bbVar = false;
//    do {
//        __LN_TS *pLN_TS;
//        short shRelativeIndexLU = 0;
//        pLN_TS = reinterpret_cast<__LN_TS *> (spca_of_p_prt[ID_FB_TS - _ID_FB_FIRST_VAR]);
//        i = EvalIdxinarrLUAreaListElem(TARAS_ALAS_STNG_LU_TS); //locRef_CLULed.
//        shRelativeIndexLU = locRef_CLUTs.shLUBieldOrdNum - i - 1;
//        locRef_CLUTs.pvCfgLN = static_cast<void*> (pLN_TS + shRelativeIndexLU);
//    } while (bbVar);
    
    j = pInit2LcVarArea->shIdxGlobalObjectMapPointers;
    if( j == 0){
        arIdxLUAreaListElem[LU_LOG-1] = gblLUAreaAuxVar.shAmountPlacedLogicUnit-1;
    }
    GlobalObjectMap.arPCLULog[j] =
      static_cast<CLULog*>(pInit2LcVarArea->pCLUBase);
    pInit2LcVarArea->shIdxGlobalObjectMapPointers++;//sLV.shIdx++

}

void GetHIDLU(void*pv, long lIdxLUinStng) {
    register long i;
    i = Shematic::GetTrueOrderNum();
    *(static_cast<long*>(pv)) = i;
	//Aux OP
	LL_CryaCrya += lIdxLUinStng>>16;
}

void ResetarNum(void) {
    for (long j = 0; j < 300; j++)
        arNum[j] = 0;
	shCounterCalls_GLB = 0;
}

long  Shematic::EvalIdxibnarrSBitFldCRefInfo(long lLUStng) {
    register long j;
    switch (lLUStng) {
        case STNG_LU_AND:
            j = current_config_prt.n_input
             + current_config_prt.n_output + current_config_prt.n_led;
            break;

        case STNG_LU_OR:
             j = current_config_prt.n_input
             + current_config_prt.n_output + current_config_prt.n_led + shCLUAnd_8_1_AmtIn*current_config_prt.n_and;
            break;

        case STNG_LU_XOR:
            j = current_config_prt.n_input
             + current_config_prt.n_output + current_config_prt.n_led + shCLUAnd_8_1_AmtIn*current_config_prt.n_and
             + shCLUOr_8_1_AmtIn*current_config_prt.n_or ;
            break;

        case STNG_LU_INPUT:
            j = 0;
            break;

        case STNG_LU_OUTPUT:
            j = current_config_prt.n_input;
            break;

        case STNG_LU_LED:
            j = current_config_prt.n_input
                +current_config_prt.n_output;
            break;

        case STNG_LU_NOT:
            j = current_config_prt.n_input
                    + current_config_prt.n_output + current_config_prt.n_led
                    + shCLUAnd_8_1_AmtIn * current_config_prt.n_and
                    + shCLUOr_8_1_AmtIn  * current_config_prt.n_or
                    + shCLUXor_2_1_AmtIn * current_config_prt.n_xor;
            break;
        case STNG_LU_MFT:
            j = current_config_prt.n_input
                    + current_config_prt.n_output + current_config_prt.n_led
                    + shCLUAnd_8_1_AmtIn * current_config_prt.n_and
                    + shCLUOr_8_1_AmtIn  * current_config_prt.n_or
                    + shCLUXor_2_1_AmtIn * current_config_prt.n_xor
                    + shCLUNot_1_1_AmtIn * current_config_prt.n_not;
            break;

        default:
            j = -1;
    }
      return j;

}/*
long  Shematic::EvalIdxinarrLUAreaListElem(long lLUStng) {
    register long j;
    switch (lLUStng) {
        case STNG_LU_AND:
            j = current_config_prt.n_input
             + current_config_prt.n_output + current_config_prt.n_led;
            break;

        case STNG_LU_OR:
             j = current_config_prt.n_input
             + current_config_prt.n_output + current_config_prt.n_led + current_config_prt.n_and;
            break;

        case STNG_LU_XOR:
            j = current_config_prt.n_input
             + current_config_prt.n_output + current_config_prt.n_led + current_config_prt.n_and
             + current_config_prt.n_or ;
            break;

        case STNG_LU_INPUT:
            j = 0;
            break;

        case STNG_LU_OUTPUT:
            j = current_config_prt.n_input;
            break;

        case STNG_LU_LED:
            j = current_config_prt.n_input
                +current_config_prt.n_output;
            break;

        case STNG_LU_NOT:
               j = current_config_prt.n_input
             + current_config_prt.n_output + current_config_prt.n_led + current_config_prt.n_and
             + current_config_prt.n_or + current_config_prt.n_xor ;
            break;
        case STNG_LU_MFT:
               j = current_config_prt.n_input
             + current_config_prt.n_output + current_config_prt.n_led + current_config_prt.n_and
             + current_config_prt.n_or + current_config_prt.n_xor + current_config_prt.n_not;
            break;

        default:
            j = -1;
    }
      return j;

}*/
long  Shematic::EvalIdxinarrLUAreaListElem(long lLUStng) {
    register long j;
    switch (lLUStng) {

        case TARAS_ALAS_STNG_LU_INPUT:
            j = 0;
            break;
        case TARAS_ALAS_STNG_LU_OUTPUT:
            j = current_config_prt.n_input;
            break;
        case TARAS_ALAS_STNG_LU_LED:
            j = current_config_prt.n_input
                    + current_config_prt.n_output;
            break;
        case TARAS_ALAS_STNG_LU_KEY:
            j = current_config_prt.n_input
                    + current_config_prt.n_output
                    + current_config_prt.n_led;
            break;
        case TARAS_ALAS_STNG_LU_ALARMS:
            j = current_config_prt.n_input
                    + current_config_prt.n_output
                    + current_config_prt.n_led
                    + current_config_prt.n_button;
            break;
        case TARAS_ALAS_STNG_LU_BGS:
            j = current_config_prt.n_input
                    + current_config_prt.n_output
                    + current_config_prt.n_led
                    + current_config_prt.n_button
                    + current_config_prt.n_alarm;
            break;
        case TARAS_ALAS_STNG_LU_AND:
            j = current_config_prt.n_input
                    + current_config_prt.n_output
                    + current_config_prt.n_led
                    + current_config_prt.n_button
                    + current_config_prt.n_alarm
                    + current_config_prt.n_group_alarm;
            break;
        case TARAS_ALAS_STNG_LU_OR:
            j = current_config_prt.n_input
                    + current_config_prt.n_output
                    + current_config_prt.n_led
                    + current_config_prt.n_button
                    + current_config_prt.n_alarm
                    + current_config_prt.n_group_alarm
                    + current_config_prt.n_and;
            break;
        case TARAS_ALAS_STNG_LU_XOR:
            j = current_config_prt.n_input
                    + current_config_prt.n_output
                    + current_config_prt.n_led
                    + current_config_prt.n_button
                    + current_config_prt.n_alarm
                    + current_config_prt.n_group_alarm
                    + current_config_prt.n_and
                    + current_config_prt.n_or;
            break;
        case TARAS_ALAS_STNG_LU_NOT:
            j = current_config_prt.n_input
                    + current_config_prt.n_output
                    + current_config_prt.n_led
                    + current_config_prt.n_button
                    + current_config_prt.n_alarm
                    + current_config_prt.n_group_alarm
                    + current_config_prt.n_and
                    + current_config_prt.n_or
                    + current_config_prt.n_xor;
            break;
        case TARAS_ALAS_STNG_LU_TIMER:
            j = current_config_prt.n_input
                    + current_config_prt.n_output
                    + current_config_prt.n_led
                    + current_config_prt.n_button
                    + current_config_prt.n_alarm
                    + current_config_prt.n_group_alarm
                    + current_config_prt.n_and
                    + current_config_prt.n_or
                    + current_config_prt.n_xor
                    + current_config_prt.n_not;
            break;
        case TARAS_ALAS_STNG_LU_TRIGGER:
            j = current_config_prt.n_input
                    + current_config_prt.n_output
                    + current_config_prt.n_led
                    + current_config_prt.n_button
                    + current_config_prt.n_alarm
                    + current_config_prt.n_group_alarm
                    + current_config_prt.n_and
                    + current_config_prt.n_or
                    + current_config_prt.n_xor
                    + current_config_prt.n_not
                    + current_config_prt.n_timer;
            break;
        case TARAS_ALAS_STNG_LU_MEANDERS:
            j = current_config_prt.n_input
                    + current_config_prt.n_output
                    + current_config_prt.n_led
                    + current_config_prt.n_button
                    + current_config_prt.n_alarm
                    + current_config_prt.n_group_alarm
                    + current_config_prt.n_and
                    + current_config_prt.n_or
                    + current_config_prt.n_xor
                    + current_config_prt.n_not
                    + current_config_prt.n_timer
                    + current_config_prt.n_trigger;
            break;
        case TARAS_ALAS_STNG_LU_TU:
            j = current_config_prt.n_input
                    + current_config_prt.n_output
                    + current_config_prt.n_led
                    + current_config_prt.n_button
                    + current_config_prt.n_alarm
                    + current_config_prt.n_group_alarm
                    + current_config_prt.n_and
                    + current_config_prt.n_or
                    + current_config_prt.n_xor
                    + current_config_prt.n_not
                    + current_config_prt.n_timer
                    + current_config_prt.n_trigger
            +current_config_prt.n_meander;
            break;
        case TARAS_ALAS_STNG_LU_TS:
            j = current_config_prt.n_input
                    + current_config_prt.n_output
                    + current_config_prt.n_led
                    + current_config_prt.n_button
                    + current_config_prt.n_alarm
                    + current_config_prt.n_group_alarm
                    + current_config_prt.n_and
                    + current_config_prt.n_or
                    + current_config_prt.n_xor
                    + current_config_prt.n_not
                    + current_config_prt.n_timer
                    + current_config_prt.n_trigger
            +current_config_prt.n_meander
            +current_config_prt.n_tu;
            break;
                case TARAS_ALAS_STNG_LU_GOOSE:
                        j = current_config_prt.n_input
                    + current_config_prt.n_output
                    + current_config_prt.n_led
                    + current_config_prt.n_button
                    + current_config_prt.n_alarm
                    + current_config_prt.n_group_alarm
                    + current_config_prt.n_and
                    + current_config_prt.n_or
                    + current_config_prt.n_xor
                    + current_config_prt.n_not
                    + current_config_prt.n_timer
                    + current_config_prt.n_trigger
            +current_config_prt.n_meander
            +current_config_prt.n_tu
            +current_config_prt.n_ts;
            break;  
        case TARAS_ALAS_STNG_LU_MMS:
                        j = current_config_prt.n_input
                    + current_config_prt.n_output
                    + current_config_prt.n_led
                    + current_config_prt.n_button
                    + current_config_prt.n_alarm
                    + current_config_prt.n_group_alarm
                    + current_config_prt.n_and
                    + current_config_prt.n_or
                    + current_config_prt.n_xor
                    + current_config_prt.n_not
                    + current_config_prt.n_timer
                    + current_config_prt.n_trigger
            +current_config_prt.n_meander
            +current_config_prt.n_tu
            +current_config_prt.n_ts
            +current_config_prt.n_input_GOOSE_block;
            break;  
          case TARAS_ALAS_STNG_LU_LAN:
                        j = current_config_prt.n_input
                    + current_config_prt.n_output
                    + current_config_prt.n_led
                    + current_config_prt.n_button
                    + current_config_prt.n_alarm
                    + current_config_prt.n_group_alarm
                    + current_config_prt.n_and
                    + current_config_prt.n_or
                    + current_config_prt.n_xor
                    + current_config_prt.n_not
                    + current_config_prt.n_timer
                    + current_config_prt.n_trigger
            +current_config_prt.n_meander
            +current_config_prt.n_tu
            +current_config_prt.n_ts
            +current_config_prt.n_input_GOOSE_block
            +current_config_prt.n_input_MMS_block;
            break;  
        case TARAS_ALAS_STNG_LU_LOG:
                        j = current_config_prt.n_input
                    + current_config_prt.n_output
                    + current_config_prt.n_led
                    + current_config_prt.n_button
                    + current_config_prt.n_alarm
                    + current_config_prt.n_group_alarm
                    + current_config_prt.n_and
                    + current_config_prt.n_or
                    + current_config_prt.n_xor
                    + current_config_prt.n_not
                    + current_config_prt.n_timer
                    + current_config_prt.n_trigger
            +current_config_prt.n_meander
            +current_config_prt.n_tu
            +current_config_prt.n_ts
            +current_config_prt.n_input_GOOSE_block 
            +current_config_prt.n_input_MMS_block
            +current_config_prt.n_network_output_block;
            break;
        case TARAS_ALAS_STNG_LU_STNG_FIX:
               j =  gblLUAreaAuxVar.shAmountPlacedLogicUnit-1;
            break;
        default:
            j = -1;
    }
      return j;

}
long  Shematic::EvalAmtIn_arrLUAreaListElem(long lLUStng) {
    register long j;
    switch (lLUStng) {
        case TARAS_ALAS_STNG_LU_INPUT:
            j = current_config_prt.n_input;
            break;
        case TARAS_ALAS_STNG_LU_OUTPUT:
            j = current_config_prt.n_output;
            break;
        case TARAS_ALAS_STNG_LU_LED:
            j = current_config_prt.n_led;
            break;
        case TARAS_ALAS_STNG_LU_KEY:
            j = current_config_prt.n_button;
            break;
        case TARAS_ALAS_STNG_LU_ALARMS:
            j = current_config_prt.n_alarm;
            break;
        case TARAS_ALAS_STNG_LU_BGS:
            j = current_config_prt.n_group_alarm;
            break;
        case TARAS_ALAS_STNG_LU_AND:
            j = current_config_prt.n_and;
            break;
        case TARAS_ALAS_STNG_LU_OR:
            j = current_config_prt.n_or;
            break;
        case TARAS_ALAS_STNG_LU_XOR:
            j = current_config_prt.n_xor;
            break;
        case TARAS_ALAS_STNG_LU_NOT:
            j = current_config_prt.n_not;
            break;
        case TARAS_ALAS_STNG_LU_TIMER:
            j = current_config_prt.n_timer;
            break;
        case TARAS_ALAS_STNG_LU_TRIGGER:
            j = current_config_prt.n_trigger;
            break;
        case TARAS_ALAS_STNG_LU_MEANDERS:
            j = current_config_prt.n_meander;
            break;
        case TARAS_ALAS_STNG_LU_TU:
            j = current_config_prt.n_tu;
            break;
        case TARAS_ALAS_STNG_LU_TS:
            j = current_config_prt.n_ts;
            break;
        case TARAS_ALAS_STNG_LU_GOOSE:
            j = current_config_prt.n_input_GOOSE_block;
            break;
        case TARAS_ALAS_STNG_LU_MMS:
            j = current_config_prt.n_input_MMS_block;
            break;
        case TARAS_ALAS_STNG_LU_LAN:
            j = current_config_prt.n_network_output_block;
            break;
            
        case TARAS_ALAS_STNG_LU_LOG:
            j = current_config_prt.n_log;
            break;
        /*
        case STNG_LU_AND:
            j = current_config_prt.n_and;
            break;

        case STNG_LU_OR:
             j = current_config_prt.n_or;
            break;

        case STNG_LU_XOR:
            j = current_config_prt.n_xor;
            break;

        case STNG_LU_INPUT:
            j = current_config_prt.n_input;
            break;

        case STNG_LU_OUTPUT:
            j = current_config_prt.n_output;
            break;

        case STNG_LU_LED:
            j = current_config_prt.n_led;
            break;

        case STNG_LU_NOT:
               j = current_config_prt.n_not;
            break;
        case STNG_LU_MFT:
               j = current_config_prt.n_timer;
            break;
*/
        default:
            j = -1;
    }
      return j;

}


long  Shematic::FillSBitFld_LUInInfo(void *pvIn,void *pvOut){
    //Now use Index in ordered CrCRefInfo
register long i,j;
volatile CLUBase* plcCLUBase;
//i =

plcCLUBase = (static_cast<LUCRefExchParam*>( pvIn))->pCLUBase;

j = plcCLUBase->shShemasIdLUStng;
i = EvalIdxibnarrSBitFldCRefInfo(j);
j = (static_cast<LUCRefExchParam*>( pvIn))->shLU_ObjScanIndex;
j *= plcCLUBase->chNumInput;
i += j;
i += (static_cast<LUCRefExchParam*>( pvIn))->chLU_OrdNumIn;
*(static_cast<SBitFld_LUInInfo*>(pvOut) ) = arrSBitFldCRefInfo[i].sBitLUInputInfo;
    return 0;
//Alternative Variant?
    //Use ((CLUBase*)plcCLUBase)->shShemasIdLUStng && shShemasIdLUStng
    //to Find Record
    //then Use ((LUCRefExchParam*) pvIn)->chLU_OrdNumIn to fix Input
}

long  Shematic::FillSBitFld_LUInInfo2(void *pvIn,void *pvOut){
    //Now use Index in ordered CrCRefInfo
register long i,j;
volatile CLUBase* plcCLUBase;
union {
//__LN_INPUT        *pLN_INPUT      ;
__LN_OUTPUT_LED   *pLN_OUTPUT_LED ;
//__LN_BUTTON_TU    *pLN_BUTTON_TU  ;
__LN_ALARM        *pLN_ALARM      ;
__LN_GROUP_ALARM  *pLN_GROUP_ALARM;
__LN_AND          *pLN_AND        ;
__LN_OR           *pLN_OR         ;
__LN_XOR          *pLN_XOR        ;
__LN_NOT          *pLN_NOT        ;
__LN_TIMER        *pLN_TIMER      ;
__LN_TRIGGER      *pLN_TRIGGER    ;
//__LN_MEANDER      *pLN_MEANDER    ;
__LN_TU           *pLN_TU;
__LN_TS* pLN_TS ;
__LN_INPUT_GOOSE_BLOCK          *pLN_GOOSE;
__LN_INPUT_MMS_BLOCK            *pLN_MMS;
__LN_NETWORK_OUTPUT_BLOCK       *pLN_LAN;
}UN_LN;
short shRelativeIndexLU = 0;
SBitFld_LUInInfo locSBitFld;
char locChOrdNumIn = (static_cast<LUCRefExchParam*>( pvIn))->chLU_OrdNumIn;
plcCLUBase = (static_cast<LUCRefExchParam*>( pvIn))->pCLUBase;
j = plcCLUBase->shShemasIdLUStng;
i = EvalIdxinarrLUAreaListElem(j);//
shRelativeIndexLU = plcCLUBase->shLUBieldOrdNum - i-1;
    switch (j) {
//        case TARAS_ALAS_STNG_LU_INPUT:
//            UN_LN.pLN_INPUT = reinterpret_cast<__LN_INPUT*>( spca_of_p_prt[ID_FB_INPUT - _ID_FB_FIRST_VAR]);
//            break;
        case TARAS_ALAS_STNG_LU_OUTPUT:
            UN_LN.pLN_OUTPUT_LED = reinterpret_cast<__LN_OUTPUT_LED*>( spca_of_p_prt[ID_FB_OUTPUT - _ID_FB_FIRST_VAR]);
            i = UN_LN.pLN_OUTPUT_LED[shRelativeIndexLU].settings.param[locChOrdNumIn];
            
            break;
        case TARAS_ALAS_STNG_LU_LED:
            UN_LN.pLN_OUTPUT_LED = reinterpret_cast<__LN_OUTPUT_LED*>( spca_of_p_prt[ID_FB_LED - _ID_FB_FIRST_VAR]);
             i = UN_LN.pLN_OUTPUT_LED[shRelativeIndexLU].settings.param[locChOrdNumIn];
            
            break;
//        case TARAS_ALAS_STNG_LU_KEY:
//            UN_LN.pLN_INPUT = reinterpret_cast<__LN_BUTTON_TU*>( spca_of_p_prt[ID_FB_BUTTON - _ID_FB_FIRST_VAR]);
//            break;
        case TARAS_ALAS_STNG_LU_ALARMS:
            UN_LN.pLN_ALARM = reinterpret_cast<__LN_ALARM*>( spca_of_p_prt[ID_FB_ALARM - _ID_FB_FIRST_VAR]);
            i = UN_LN.pLN_ALARM[shRelativeIndexLU].settings.param[locChOrdNumIn];
            break;
        case TARAS_ALAS_STNG_LU_BGS:
            UN_LN.pLN_GROUP_ALARM = reinterpret_cast<__LN_GROUP_ALARM*>( spca_of_p_prt[ID_FB_GROUP_ALARM - _ID_FB_FIRST_VAR]);
            break;
        case TARAS_ALAS_STNG_LU_AND:
            UN_LN.pLN_AND = reinterpret_cast<__LN_AND*>( spca_of_p_prt[ID_FB_AND - _ID_FB_FIRST_VAR]);
            i = UN_LN.pLN_AND[shRelativeIndexLU].settings.param[locChOrdNumIn];
            break;
        case TARAS_ALAS_STNG_LU_OR:
            UN_LN.pLN_OR = reinterpret_cast<__LN_OR*>( spca_of_p_prt[ID_FB_OR - _ID_FB_FIRST_VAR]);
            i = UN_LN.pLN_OR[shRelativeIndexLU].settings.param[locChOrdNumIn];
            break;
        case TARAS_ALAS_STNG_LU_XOR:
            UN_LN.pLN_XOR = reinterpret_cast<__LN_XOR*>( spca_of_p_prt[ID_FB_XOR - _ID_FB_FIRST_VAR]);
            i = UN_LN.pLN_XOR[shRelativeIndexLU].settings.param[locChOrdNumIn];
            break;
        case TARAS_ALAS_STNG_LU_NOT:
            UN_LN.pLN_NOT = reinterpret_cast<__LN_NOT*>( spca_of_p_prt[ID_FB_NOT - _ID_FB_FIRST_VAR]);
            i = UN_LN.pLN_NOT[shRelativeIndexLU].settings.param[locChOrdNumIn];
            break;            
        case TARAS_ALAS_STNG_LU_TIMER:
            UN_LN.pLN_TIMER = reinterpret_cast<__LN_TIMER*>( spca_of_p_prt[ID_FB_TIMER - _ID_FB_FIRST_VAR]);
            i = UN_LN.pLN_TIMER[shRelativeIndexLU].settings.param[locChOrdNumIn];
            break;
        case TARAS_ALAS_STNG_LU_TRIGGER:
            UN_LN.pLN_TRIGGER = reinterpret_cast<__LN_TRIGGER*>( spca_of_p_prt[ID_FB_TRIGGER - _ID_FB_FIRST_VAR]);
            i = UN_LN.pLN_TRIGGER[shRelativeIndexLU].settings.param[locChOrdNumIn];
            break;
//        case TARAS_ALAS_STNG_LU_MEANDERS:
//            UN_LN.pLN_INPUT = reinterpret_cast<__LN_MEANDER*>( spca_of_p_prt[ID_FB_MEANDER - _ID_FB_FIRST_VAR]);
//            break;
        case TARAS_ALAS_STNG_LU_TU:
            UN_LN.pLN_TU = reinterpret_cast<__LN_TU*>( spca_of_p_prt[ID_FB_TU - _ID_FB_FIRST_VAR]);
            i = UN_LN.pLN_TU[shRelativeIndexLU].settings.param[locChOrdNumIn];
            break;
            
        case TARAS_ALAS_STNG_LU_TS:
            UN_LN.pLN_TS = reinterpret_cast<__LN_TS*>( spca_of_p_prt[ID_FB_TS - _ID_FB_FIRST_VAR]);
            i = UN_LN.pLN_TS[shRelativeIndexLU].settings.param[locChOrdNumIn];
            break;
        case TARAS_ALAS_STNG_LU_GOOSE:
            UN_LN.pLN_GOOSE = reinterpret_cast<__LN_INPUT_GOOSE_BLOCK*>( spca_of_p_prt[ID_FB_INPUT_GOOSE_BLOCK - _ID_FB_FIRST_VAR]);
            i = UN_LN.pLN_GOOSE[shRelativeIndexLU].settings.param[locChOrdNumIn];
            break;
        case TARAS_ALAS_STNG_LU_MMS:
            UN_LN.pLN_MMS = reinterpret_cast<__LN_INPUT_MMS_BLOCK*>( spca_of_p_prt[ID_FB_INPUT_MMS_BLOCK - _ID_FB_FIRST_VAR]);
            i = UN_LN.pLN_MMS[shRelativeIndexLU].settings.param[locChOrdNumIn];
            break;
        case TARAS_ALAS_STNG_LU_LAN:
            UN_LN.pLN_LAN = reinterpret_cast<__LN_NETWORK_OUTPUT_BLOCK*>( spca_of_p_prt[ID_FB_NETWORK_OUTPUT_BLOCK - _ID_FB_FIRST_VAR]);
            i = UN_LN.pLN_LAN[shRelativeIndexLU].settings.param[locChOrdNumIn];
            break;
            
        case TARAS_ALAS_STNG_LU_LOG:
            UN_LN.pLN_TS = reinterpret_cast<__LN_TS*>( spca_of_p_prt[ID_FB_TS - _ID_FB_FIRST_VAR]);
            i = UN_LN.pLN_TS[shRelativeIndexLU].settings.param[locChOrdNumIn];
            break;
            
        default:
            ;
    }
    
//Detect type Elem
//i = EvalIdxibnarrSBitFldCRefInfo(j);
//j = (static_cast<LUCRefExchParam*>( pvIn))->shLU_ObjScanIndex;
//j *= plcCLUBase->chNumInput;
//i += j;
//i += (static_cast<LUCRefExchParam*>( pvIn))->chLU_OrdNumIn;
// *(static_cast<SBitFld_LUInInfo*>(pvOut) ) = arrSBitFldCRefInfo[i].sBitLUInputInfo;
/*    long param = i;
          unsigned int id_input   = (param >> SFIFT_PARAM_ID ) & MASKA_PARAM_ID ;//Typ Funktsional?noho bloku
            unsigned int n_input    = (param >> SFIFT_PARAM_N  ) & MASKA_PARAM_N  ;//Poryadkovyy nomer       
            unsigned int out_input  = (param >> SFIFT_PARAM_OUT) & MASKA_PARAM_OUT;//Nomer vykhodu       
            */
locSBitFld.bfInfo_IdLUStng = 
        (i >> SFIFT_PARAM_ID ) & MASKA_PARAM_ID ;//Typ Funktsional?noho bloku
locSBitFld.bfInfo_OrdNumStng = 
        (i >> SFIFT_PARAM_N  ) & MASKA_PARAM_N  ;//Poryadkovyy nomer
locSBitFld.bfInfo_OrdNumOut = 
        (i >> SFIFT_PARAM_OUT) & MASKA_PARAM_OUT;//Nomer vykhodu  
         *(static_cast<SBitFld_LUInInfo*>(pvOut) ) = locSBitFld;   
    return 0;

}
void Shematic::SetupCircutLinks(void *pv) {
    register long i,j;

//	short shAmtPlacedLU;
//	short shAmtLUDscElem;//SBitFldCRefInfo Elem

struct {
	short shAmtLU, shIdx;
        short shCounterScanedObj,shCounterFindObj;
        short shAmtLookObj;
        long lBaseOrdNumStng;
        SBitFldCRefInfo *pSBitFldCRefInfo;
        LUCrossRefDsc lcLUCrossRefData;
        CLUBase  *pCLURef;//*pCLUBase,
} sLV;
SBitFld_LUInInfo locSBitFld;
LUCRefExchParam lcLUCRefExchParam;
Init2LcVarArea& rsLV = *(static_cast<Init2LcVarArea*>(pv));
    i = j = 0;

    sLV.shIdx = sLV.shAmtLU = 0;
//    rsLV = *((Init2LcVarArea*) pv);
    sLV.pSBitFldCRefInfo = &arrSBitFldCRefInfo[0]; //Table Links
    rsLV.arrLUAreaListElem = &gLUAreaMem.headLUAreaList;


    if (current_config_prt.n_output != 0) {
        sLV.shCounterScanedObj = 0;
        sLV.shAmtLU = current_config_prt.n_output;
        j = 0; //Idx in OutPut for Test
        sLV.shIdx += current_config_prt.n_input;
        i = sLV.shIdx; //Offset Output
        do {
            //Type Obj == STNG_LU_OUTPUT order num == sLV.shCounterScanedObj+sLV.shIdx
            i = sLV.shCounterScanedObj + sLV.shIdx;
            pv = static_cast<void*>(&rsLV.arrLUAreaListElem[i]);
            //rsLV.pCLUBase = (CLUBase*) ((LUAreaListElem*) pv)->pvLU;
            rsLV.pCLUBase = static_cast<CLUBase*> (
                    (static_cast<LUAreaListElem*> (pv))->pvLU);

            //Take info 2 Possible Variants
            //1-st STNG_LU_OUTPUT And shShemasOrdNumStng
            //2-nd use Index in ordered CrCRefInfo
            for (long ik = 0; ik < rsLV.pCLUBase->chNumInput; ik++) {
                lcLUCRefExchParam.shLU_ObjScanIndex = sLV.shCounterScanedObj;
                lcLUCRefExchParam.chLU_OrdNumIn = ik;// + 1; in function use as Idx
                lcLUCRefExchParam.pCLUBase = rsLV.pCLUBase;
                FillSBitFld_LUInInfo( static_cast<void*>(&lcLUCRefExchParam),
				static_cast<void*>(&locSBitFld) );
                //Have OutPut Param
                sLV.lcLUCrossRefData.shRefIdLUStng   = locSBitFld.bfInfo_IdLUStng;
                sLV.lcLUCrossRefData.shRefOrdNumStng = locSBitFld.bfInfo_OrdNumStng;
                sLV.lcLUCrossRefData.chRefOrdNumOut  = locSBitFld.bfInfo_OrdNumOut;
                 //Find Obj
                j = EvalIdxinarrLUAreaListElem(sLV.lcLUCrossRefData.shRefIdLUStng);
                if(j!=(-1)){
                    sLV.shCounterFindObj = 0;
                    sLV.shAmtLookObj = EvalAmtIn_arrLUAreaListElem(sLV.lcLUCrossRefData.shRefIdLUStng);
                    if(sLV.shAmtLookObj == (-1))
                        sLV.shAmtLookObj = gblLUAreaAuxVar.shAmountPlacedLogicUnit-j;//Test Only
                    //i = j+sLV.shCounterFindObj;
                    rsLV.chVal = 0;rsLV.pCh = static_cast<char*>(0);
                    while ((sLV.shCounterFindObj)<sLV.shAmtLookObj && rsLV.chVal!=1) {
                        i = j+sLV.shCounterFindObj;
                        pv = static_cast<void*>(&rsLV.arrLUAreaListElem[i]);
                        //sLV.pCLURef = (CLUBase*) ((LUAreaListElem*) pv)->pvLU;
                        sLV.pCLURef = static_cast<CLUBase*> (
                                (static_cast<LUAreaListElem*> (pv))->pvLU);
                        if ((sLV.pCLURef->shShemasIdLUStng == sLV.lcLUCrossRefData.shRefIdLUStng) &&
                                (sLV.pCLURef->shShemasOrdNumStng == sLV.lcLUCrossRefData.shRefOrdNumStng)
                            ){//Set UP Logic
                            rsLV.pCh = static_cast<char*>(sLV.pCLURef->pOut);
                            rsLV.pCh += sLV.lcLUCrossRefData.chRefOrdNumOut -1;//As Idx
                            rsLV.chVal = 1;
                            break;
                        }
                    sLV.shCounterFindObj++;
                    }
                    if (rsLV.pCh) {
                        rsLV.arrPchIn = static_cast<char**>(rsLV.pCLUBase->pIn);
                        rsLV.arrPchIn[ik] = rsLV.pCh;

                    }
                    if(rsLV.chVal != 1)
                        rsLV.chErrCount++;//Is need?
                }
            }
        } while (++sLV.shCounterScanedObj < sLV.shAmtLU);
    }
    if (current_config_prt.n_led != 0) {
        sLV.shCounterScanedObj = 0;
        sLV.shAmtLU = current_config_prt.n_led;
        j = 0; //Idx in OutPut for Test
        sLV.shIdx += current_config_prt.n_output;
        rsLV.shIdx = sLV.shIdx; rsLV.pV = static_cast<void*>(&sLV.shCounterScanedObj);
        do{
            SetupCLUInternalRef(static_cast<void*>(&rsLV));

        }while (++sLV.shCounterScanedObj < sLV.shAmtLU);
    }
    if (current_config_prt.n_and != 0) {
        sLV.shCounterScanedObj = 0;
        sLV.shAmtLU = current_config_prt.n_and;
        j = 0; //Idx in OutPut for Test
        sLV.shIdx += current_config_prt.n_led;
        rsLV.shIdx = sLV.shIdx; rsLV.pV = static_cast<void*>(&sLV.shCounterScanedObj);
        do {
            SetupCLUInternalRef(static_cast<void*>(&rsLV));
        } while (++sLV.shCounterScanedObj < sLV.shAmtLU);
    }
    if (current_config_prt.n_or != 0) {
        sLV.shCounterScanedObj = 0;
        sLV.shAmtLU = current_config_prt.n_or;
        j = 0;
        sLV.shIdx += current_config_prt.n_and;
        rsLV.shIdx = sLV.shIdx; rsLV.pV = static_cast<void*>(&sLV.shCounterScanedObj);
        do {
            SetupCLUInternalRef(static_cast<void*>(&rsLV));
        } while (++sLV.shCounterScanedObj < sLV.shAmtLU);
    }
    if (current_config_prt.n_xor != 0) {
	sLV.shCounterScanedObj = 0;
        sLV.shAmtLU = current_config_prt.n_xor;
        j = 0; //Idx in OutPut for Test
        sLV.shIdx += current_config_prt.n_or;
        rsLV.shIdx = sLV.shIdx; rsLV.pV = static_cast<void*>(&sLV.shCounterScanedObj);
        do {
            SetupCLUInternalRef(static_cast<void*>(&rsLV));
        } while (++sLV.shCounterScanedObj < sLV.shAmtLU);
    }
    if (current_config_prt.n_not != 0) {
	sLV.shCounterScanedObj = 0;
        sLV.shAmtLU = current_config_prt.n_not;
        j = 0; //Idx in OutPut for Test
        sLV.shIdx += current_config_prt.n_xor;
        rsLV.shIdx = sLV.shIdx; rsLV.pV = static_cast<void*>(&sLV.shCounterScanedObj);
        do {
            SetupCLUInternalRef(static_cast<void*>(&rsLV));
        } while (++sLV.shCounterScanedObj < sLV.shAmtLU);
    }

}

//	while (shAmtLUDscElem
//	&& sLV.chBreakScanLUDscLoop == 0) {
//		//Get Reference on Link Data
//		//sLV.shIdxFldCRefInfo =0;?
//		//
//		while(sLV.shIdxLU < shAmtPlacedLU
//		&& sLV.chBreakScanPlacedLULoop == 0){
//			i = sLV.shIdxLU;
//			pv = (void*) &rsLV.arrLUAreaListElem[i];
//			rsLV.pCLUBase = (CLUBase*) ((LUAreaListElem*) pv)->pvLU;
//
//			j = sLV.shIdxFldCRefInfo;
//			if (rsLV.pCLUBase->shShemasIdLUStng == ar_n_output_CRDsc[j].shBaseIdLUStng &&
//                    rsLV.pCLUBase->shShemasOrdNumStng == ar_n_output_CRDsc[j].shBaseOrdNumStng) {
//
//
//			}
//		}
//
//	}

void Shematic::SetupLULinks(void *pv) {
//	register long i,j;
	//First Param Index in CrrefArray
	//Second Param Id & Type LU
	pv = static_cast<void*>(&LL_CryaCrya);
	*(static_cast<short*>(pv)) = 1000;
}


void Shematic::SetupCLUInternalRef(void *pv){
    register long i,j;
//   register Init2LcVarArea *pInit2LcVarArea = (Init2LcVarArea *)pv;
	SBitFld_LUInInfo locSBitFld;
    LUCRefExchParam lcLUCRefExchParam;
    register Init2LcVarArea& rsLV = *(static_cast<Init2LcVarArea*>(pv));
    volatile short& shCounterScanedObj = *(static_cast<short*>(rsLV.pV));


    i = shCounterScanedObj + rsLV.shIdx;
    pv = static_cast<void*>(&rsLV.arrLUAreaListElem[i]);
    //rsLV.pCLUBase = (CLUBase*) ((LUAreaListElem*) pv)->pvLU;static_cast<CLUBase*>(
    rsLV.pCLUBase = static_cast<CLUBase*>((static_cast<LUAreaListElem*>(pv))->pvLU);
    for (long ik = 0; ik < rsLV.pCLUBase->chNumInput; ik++) {
        lcLUCRefExchParam.shLU_ObjScanIndex = shCounterScanedObj;
        lcLUCRefExchParam.chLU_OrdNumIn = ik;// + 1; in function use as Idx
        lcLUCRefExchParam.pCLUBase = rsLV.pCLUBase;
        FillSBitFld_LUInInfo(static_cast<void*>(&lcLUCRefExchParam), static_cast<void*>(&locSBitFld));
        //Have OutPut Param
        //-lcLUCRefExchParam.shRefIdLUStng   = locSBitFld.bfInfo_IdLUStng;
        //-lcLUCRefExchParam.shRefOrdNumStng = locSBitFld.bfInfo_OrdNumStng;
        //-lcLUCRefExchParam.chRefOrdNumOut  = locSBitFld.bfInfo_OrdNumOut;
         //Find Obj
        j = EvalIdxinarrLUAreaListElem(static_cast<long>(locSBitFld.bfInfo_IdLUStng));
        if(j!=(-1)){
             short shCounterFindObj = 0;
             short shAmtLookObj = 0;

            shAmtLookObj = static_cast<short>(EvalAmtIn_arrLUAreaListElem(static_cast<long>(locSBitFld.bfInfo_IdLUStng)));
            if(shAmtLookObj == (-1))
                shAmtLookObj = gblLUAreaAuxVar.shAmountPlacedLogicUnit-j;

            rsLV.chVal = 0;rsLV.pCh = static_cast<char*>(0);
            while ((shCounterFindObj) < shAmtLookObj && rsLV.chVal != 1) {
                i = j + shCounterFindObj;
                pv = static_cast<void*>(&rsLV.arrLUAreaListElem[i]);
                //rsLV.pCLURef = (CLUBase*) ((LUAreaListElem*) pv)->pvLU;
                rsLV.pCLURef = static_cast<CLUBase*>((static_cast<LUAreaListElem*>(pv))->pvLU);
                if ((rsLV.pCLURef->shShemasIdLUStng == static_cast<short>(locSBitFld.bfInfo_IdLUStng)) &&
                        (rsLV.pCLURef->shShemasOrdNumStng == static_cast<short>(locSBitFld.bfInfo_OrdNumStng))
                        ) {//Set UP Logic
                    rsLV.pCh = static_cast<char*>(rsLV.pCLURef->pOut);
                    rsLV.pCh += static_cast<unsigned char>(locSBitFld.bfInfo_OrdNumOut - 1); //As Idx
                    rsLV.chVal = 1;
                    break;
                }
                shCounterFindObj++;
            }
            if (rsLV.pCh) {
                rsLV.arrPchIn = static_cast<char**>(rsLV.pCLUBase->pIn);
                rsLV.arrPchIn[ik] = rsLV.pCh;
            }
            if(rsLV.chVal != 1)
                rsLV.chErrCount++;//Is need?
        }
    }
}
void Shematic::SetupCircutLinks2(void *pv) {
    register long i,j;

//	short shAmtPlacedLU;
//	short shAmtLUDscElem;//SBitFldCRefInfo Elem

struct {
	short shAmtLU, shIdx;
        short shCounterScanedObj,shCounterFindObj;
        short shAmtLookObj;
        long lBaseOrdNumStng;
        SBitFldCRefInfo *pSBitFldCRefInfo;
        LUCrossRefDsc lcLUCrossRefData;
        CLUBase  *pCLURef;//*pCLUBase,
} sLV;
SBitFld_LUInInfo locSBitFld;
LUCRefExchParam lcLUCRefExchParam;
Init2LcVarArea& rsLV = *(static_cast<Init2LcVarArea*>(pv));
    i = j = 0;
//    	    asm volatile(
//                "bkpt 1"
//                );
    sLV.shIdx = sLV.shAmtLU = 0;
//    rsLV = *((Init2LcVarArea*) pv);
    sLV.pSBitFldCRefInfo = &arrSBitFldCRefInfo[0]; //Table Links
    rsLV.arrLUAreaListElem = &gLUAreaMem.headLUAreaList;


    if (current_config_prt.n_output != 0) {
        sLV.shCounterScanedObj = 0;
        sLV.shAmtLU = current_config_prt.n_output;
        j = 0; //Idx in OutPut for Test
        sLV.shIdx += current_config_prt.n_input;
        i = sLV.shIdx; //Offset Output
        do {
            //Type Obj == STNG_LU_OUTPUT order num == sLV.shCounterScanedObj+sLV.shIdx
            i = sLV.shCounterScanedObj + sLV.shIdx;
            pv = static_cast<void*>(&rsLV.arrLUAreaListElem[i]);
            //rsLV.pCLUBase = (CLUBase*) ((LUAreaListElem*) pv)->pvLU;
            rsLV.pCLUBase = static_cast<CLUBase*> (
                    (static_cast<LUAreaListElem*> (pv))->pvLU);

            //Take info 2 Possible Variants
            //1-st STNG_LU_OUTPUT And shShemasOrdNumStng
            //2-nd use Index in ordered CrCRefInfo
            for (long ik = 0; ik < rsLV.pCLUBase->chNumInput; ik++) {
                lcLUCRefExchParam.shLU_ObjScanIndex = sLV.shCounterScanedObj;
                lcLUCRefExchParam.chLU_OrdNumIn = ik;// + 1; in function use as Idx
                lcLUCRefExchParam.pCLUBase = rsLV.pCLUBase;rsLV.chVal = 0;
                FillSBitFld_LUInInfo2( static_cast<void*>(&lcLUCRefExchParam),
				static_cast<void*>(&locSBitFld) );
                //Have OutPut Param
                sLV.lcLUCrossRefData.shRefIdLUStng   = locSBitFld.bfInfo_IdLUStng;
                sLV.lcLUCrossRefData.shRefOrdNumStng = locSBitFld.bfInfo_OrdNumStng;
                sLV.lcLUCrossRefData.chRefOrdNumOut  = locSBitFld.bfInfo_OrdNumOut;
                if(sLV.lcLUCrossRefData.shRefIdLUStng == 0 && sLV.lcLUCrossRefData.shRefOrdNumStng ==0)
                    {j = (-1);rsLV.chVal = 1;}
                else {
//                    asm volatile(
//                        "bkpt 1"
//                        );
                 //Find Obj
                j = EvalIdxinarrLUAreaListElem(sLV.lcLUCrossRefData.shRefIdLUStng);
                }
                if(j!=(-1)){
                    sLV.shCounterFindObj = 0;
                    sLV.shAmtLookObj = EvalAmtIn_arrLUAreaListElem(sLV.lcLUCrossRefData.shRefIdLUStng);
                    if(sLV.shAmtLookObj == (-1))
                        sLV.shAmtLookObj = gblLUAreaAuxVar.shAmountPlacedLogicUnit-j;//Test Only
                    //i = j+sLV.shCounterFindObj;
                    rsLV.chVal = 0;rsLV.pCh = static_cast<char*>(0);
                    while ((sLV.shCounterFindObj)<sLV.shAmtLookObj && rsLV.chVal!=1) {
                        i = j+sLV.shCounterFindObj;
                        pv = static_cast<void*>(&rsLV.arrLUAreaListElem[i]);
                        //sLV.pCLURef = (CLUBase*) ((LUAreaListElem*) pv)->pvLU;
                        sLV.pCLURef = static_cast<CLUBase*> (
                                (static_cast<LUAreaListElem*> (pv))->pvLU);
                        if ((sLV.pCLURef->shShemasIdLUStng == sLV.lcLUCrossRefData.shRefIdLUStng) &&
                                (sLV.pCLURef->shShemasOrdNumStng == sLV.lcLUCrossRefData.shRefOrdNumStng)
                            ){//Set UP Logic
                            rsLV.pCh = static_cast<char*>(sLV.pCLURef->pOut);
                            rsLV.pCh += sLV.lcLUCrossRefData.chRefOrdNumOut -1;//As Idx
                            rsLV.chVal = 1;
//                            asm volatile(
//                                "bkpt 1"
//                                );
                            break;
                        }
                    sLV.shCounterFindObj++;
                    }
                    if (rsLV.pCh) {
                        rsLV.arrPchIn = static_cast<char**>(rsLV.pCLUBase->pIn);
                        rsLV.arrPchIn[ik] = rsLV.pCh;

                    }
                    if(rsLV.chVal != 1)
                        rsLV.chErrCount++;//Is need?
                }
                else{
                    if(rsLV.chVal != 1){
                    rsLV.chErrCount |= 2;//Insert Data Error
                    return;
                    }
                }
                
            }
        } while (++sLV.shCounterScanedObj < sLV.shAmtLU);
    }
    if (current_config_prt.n_led != 0) {
        sLV.shCounterScanedObj = 0;
        sLV.shAmtLU = current_config_prt.n_led;
        j = 0; //Idx in OutPut for Test
        sLV.shIdx += current_config_prt.n_output;
        rsLV.shIdx = sLV.shIdx; rsLV.pV = static_cast<void*>(&sLV.shCounterScanedObj);
        do{
            SetupCLUInternalRefLed(static_cast<void*>(&rsLV));

        }while (++sLV.shCounterScanedObj < sLV.shAmtLU);
    }
    else{
        sLV.shIdx += current_config_prt.n_output;
    }
    if (current_config_prt.n_alarm != 0) {
        sLV.shCounterScanedObj = 0;
        sLV.shAmtLU = current_config_prt.n_alarm;
        j = 0; //Idx in OutPut for Test
        sLV.shIdx += current_config_prt.n_led + current_config_prt.n_button;
        rsLV.shIdx = sLV.shIdx; rsLV.pV = static_cast<void*>(&sLV.shCounterScanedObj);
        do{
            SetupCLUInternalRef2(static_cast<void*>(&rsLV));

        }while (++sLV.shCounterScanedObj < sLV.shAmtLU);
    }
    else{
        sLV.shIdx += current_config_prt.n_led + current_config_prt.n_button;
    }
    
    if (current_config_prt.n_and != 0) {
        sLV.shCounterScanedObj = 0;
        sLV.shAmtLU = current_config_prt.n_and;
        j = 0; //Idx in OutPut for Test
        sLV.shIdx += current_config_prt.n_alarm 
        + current_config_prt.n_group_alarm;
        rsLV.shIdx = sLV.shIdx; rsLV.pV = static_cast<void*>(&sLV.shCounterScanedObj);
        do {
            SetupCLUInternalRef2(static_cast<void*>(&rsLV));
        } while (++sLV.shCounterScanedObj < sLV.shAmtLU);
    }
    else{
        sLV.shIdx += current_config_prt.n_alarm 
        + current_config_prt.n_group_alarm;
    }
    if (current_config_prt.n_or != 0) {
        sLV.shCounterScanedObj = 0;
        sLV.shAmtLU = current_config_prt.n_or;
        j = 0;
        sLV.shIdx += current_config_prt.n_and;
        rsLV.shIdx = sLV.shIdx; rsLV.pV = static_cast<void*>(&sLV.shCounterScanedObj);
        do {
            SetupCLUInternalRef2(static_cast<void*>(&rsLV));
        } while (++sLV.shCounterScanedObj < sLV.shAmtLU);
    }
    else{
        sLV.shIdx += current_config_prt.n_and;
    }
    if (current_config_prt.n_xor != 0) {
	sLV.shCounterScanedObj = 0;
        sLV.shAmtLU = current_config_prt.n_xor;
        j = 0; //Idx in OutPut for Test
        sLV.shIdx += current_config_prt.n_or;
        rsLV.shIdx = sLV.shIdx; rsLV.pV = static_cast<void*>(&sLV.shCounterScanedObj);
        do {
            SetupCLUInternalRef2(static_cast<void*>(&rsLV));
        } while (++sLV.shCounterScanedObj < sLV.shAmtLU);
    }
    else{
        sLV.shIdx += current_config_prt.n_or;
    }
    if (current_config_prt.n_not != 0) {
	sLV.shCounterScanedObj = 0;
        sLV.shAmtLU = current_config_prt.n_not;
        j = 0; //Idx in OutPut for Test
        sLV.shIdx += current_config_prt.n_xor;
        rsLV.shIdx = sLV.shIdx; rsLV.pV = static_cast<void*>(&sLV.shCounterScanedObj);
        do {
            SetupCLUInternalRef2(static_cast<void*>(&rsLV));
        } while (++sLV.shCounterScanedObj < sLV.shAmtLU);
    }
    else{
        sLV.shIdx += current_config_prt.n_xor;
    }
    if (current_config_prt.n_timer != 0) {
	sLV.shCounterScanedObj = 0;
        sLV.shAmtLU = current_config_prt.n_timer;
        j = 0; //Idx in OutPut for Test
        sLV.shIdx += current_config_prt.n_not;
        rsLV.shIdx = sLV.shIdx; rsLV.pV = static_cast<void*>(&sLV.shCounterScanedObj);
        do {
            SetupCLUInternalRef2(static_cast<void*>(&rsLV));
        } while (++sLV.shCounterScanedObj < sLV.shAmtLU);
    }
    else{
        sLV.shIdx += current_config_prt.n_not;
    }
    if (current_config_prt.n_trigger != 0) {
	sLV.shCounterScanedObj = 0;
        sLV.shAmtLU = current_config_prt.n_trigger;
        j = 0; //Idx in OutPut for Test
        sLV.shIdx += current_config_prt.n_timer;
        rsLV.shIdx = sLV.shIdx; rsLV.pV = static_cast<void*>(&sLV.shCounterScanedObj);
        do {
            SetupCLUInternalRef2(static_cast<void*>(&rsLV));
        } while (++sLV.shCounterScanedObj < sLV.shAmtLU);
    }
    else{
        sLV.shIdx += current_config_prt.n_timer;
    }
    if (current_config_prt.n_tu != 0) {
	sLV.shCounterScanedObj = 0;
        sLV.shAmtLU = current_config_prt.n_tu;
        j = 0; //Idx in OutPut for Test
        sLV.shIdx += current_config_prt.n_trigger+ current_config_prt.n_meander;
        rsLV.shIdx = sLV.shIdx; rsLV.pV = static_cast<void*>(&sLV.shCounterScanedObj);
        do {
            SetupCLUInternalRef2(static_cast<void*>(&rsLV));
        } while (++sLV.shCounterScanedObj < sLV.shAmtLU);
    }
    else{
        sLV.shIdx += current_config_prt.n_trigger + current_config_prt.n_meander;
    }
    if (current_config_prt.n_ts != 0) {
	sLV.shCounterScanedObj = 0;
        sLV.shAmtLU = current_config_prt.n_ts;
        j = 0; //Idx in OutPut for Test
        sLV.shIdx += current_config_prt.n_tu;
        rsLV.shIdx = sLV.shIdx; rsLV.pV = static_cast<void*>(&sLV.shCounterScanedObj);
        do {
            SetupCLUInternalRef2(static_cast<void*>(&rsLV));
        } while (++sLV.shCounterScanedObj < sLV.shAmtLU);
    }
    else{
        sLV.shIdx += current_config_prt.n_tu;
    }
   if (current_config_prt.n_input_GOOSE_block != 0) {
	sLV.shCounterScanedObj = 0;
        sLV.shAmtLU = current_config_prt.n_input_GOOSE_block;
        j = 0; //Idx in OutPut for Test
        sLV.shIdx += current_config_prt.n_ts;
        rsLV.shIdx = sLV.shIdx; rsLV.pV = static_cast<void*>(&sLV.shCounterScanedObj);
        do {
            SetupCLUInternalRef2(static_cast<void*>(&rsLV));
        } while (++sLV.shCounterScanedObj < sLV.shAmtLU);
    }
    else{
        sLV.shIdx += current_config_prt.n_ts;
    }
    if (current_config_prt.n_input_MMS_block != 0) {
	sLV.shCounterScanedObj = 0;
        sLV.shAmtLU = current_config_prt.n_input_MMS_block;
        j = 0; //Idx in OutPut for Test
        sLV.shIdx += current_config_prt.n_input_GOOSE_block;
        rsLV.shIdx = sLV.shIdx; rsLV.pV = static_cast<void*>(&sLV.shCounterScanedObj);
        do {
            SetupCLUInternalRef2(static_cast<void*>(&rsLV));
        } while (++sLV.shCounterScanedObj < sLV.shAmtLU);
    }
    else{
        sLV.shIdx += current_config_prt.n_input_GOOSE_block;
    }
    if (current_config_prt.n_network_output_block != 0) {
	sLV.shCounterScanedObj = 0;
        sLV.shAmtLU = current_config_prt.n_network_output_block;
        j = 0; //Idx in OutPut for Test
        sLV.shIdx += current_config_prt.n_input_MMS_block;
        rsLV.shIdx = sLV.shIdx; rsLV.pV = static_cast<void*>(&sLV.shCounterScanedObj);
        do {
            SetupCLUInternalRef2(static_cast<void*>(&rsLV));
        } while (++sLV.shCounterScanedObj < sLV.shAmtLU);
    }
    else{
        sLV.shIdx += current_config_prt.n_input_MMS_block;
    }
    
    
    
    
//#warning eRunErrorLed.pOut not Complite. It may contain Error!!!
}

void Shematic::SetupCLUInternalRef2(void *pv){
    register long i,j;
//   register Init2LcVarArea *pInit2LcVarArea = (Init2LcVarArea *)pv;
	SBitFld_LUInInfo locSBitFld;
    LUCRefExchParam lcLUCRefExchParam;
    register Init2LcVarArea& rsLV = *(static_cast<Init2LcVarArea*>(pv));
    volatile short& shCounterScanedObj = *(static_cast<short*>(rsLV.pV));
if(rsLV.chErrCount != 0)
return;

    i = shCounterScanedObj + rsLV.shIdx;
    pv = static_cast<void*>(&rsLV.arrLUAreaListElem[i]);
    //rsLV.pCLUBase = (CLUBase*) ((LUAreaListElem*) pv)->pvLU;static_cast<CLUBase*>(
    rsLV.pCLUBase = static_cast<CLUBase*>((static_cast<LUAreaListElem*>(pv))->pvLU);
    for (long ik = 0; ik < rsLV.pCLUBase->chNumInput; ik++) {
        lcLUCRefExchParam.shLU_ObjScanIndex = shCounterScanedObj;
        lcLUCRefExchParam.chLU_OrdNumIn = ik;// + 1; in function use as Idx
        lcLUCRefExchParam.pCLUBase = rsLV.pCLUBase;
        FillSBitFld_LUInInfo2(static_cast<void*>(&lcLUCRefExchParam), static_cast<void*>(&locSBitFld));
        
        //if(sLV.lcLUCrossRefData.shRefIdLUStng == 0 && sLV.lcLUCrossRefData.shRefOrdNumStng ==0)
        if(locSBitFld.bfInfo_IdLUStng == 0 && locSBitFld.bfInfo_OrdNumStng ==0)
            {j = (-1);rsLV.chVal = 1;}
        else {
//            asm volatile(
//                "bkpt 1"
//            );
        }    
         //Find Obj
        j = EvalIdxinarrLUAreaListElem(static_cast<long>(locSBitFld.bfInfo_IdLUStng));
        if(j==(-2)){
         
            rsLV.pCh = static_cast<char*>(0);
            //rsLV.pCh = static_cast<char*>(rsLV.pCLURef->pOut);
            rsLV.pCh = static_cast<char*>(eRunErrorLed.pOut);
            rsLV.pCh += static_cast<unsigned char>(locSBitFld.bfInfo_OrdNumOut - 1); //As Idx
            if (rsLV.pCh) {
                rsLV.arrPchIn = static_cast<char**>(rsLV.pCLUBase->pIn);
                rsLV.arrPchIn[ik] = rsLV.pCh;
            }
        }else
        if(j!=(-1)){
             short shCounterFindObj = 0;
             short shAmtLookObj = 0;

            shAmtLookObj = static_cast<short>(EvalAmtIn_arrLUAreaListElem(static_cast<long>(locSBitFld.bfInfo_IdLUStng)));
            if(shAmtLookObj == (-1))
                shAmtLookObj = gblLUAreaAuxVar.shAmountPlacedLogicUnit-j;

            rsLV.chVal = 0;rsLV.pCh = static_cast<char*>(0);
            while ((shCounterFindObj) < shAmtLookObj && rsLV.chVal != 1) {
                i = j + shCounterFindObj;
                pv = static_cast<void*>(&rsLV.arrLUAreaListElem[i]);
                //rsLV.pCLURef = (CLUBase*) ((LUAreaListElem*) pv)->pvLU;
                rsLV.pCLURef = static_cast<CLUBase*>((static_cast<LUAreaListElem*>(pv))->pvLU);
                if ((rsLV.pCLURef->shShemasIdLUStng == static_cast<short>(locSBitFld.bfInfo_IdLUStng)) &&
                        (rsLV.pCLURef->shShemasOrdNumStng == static_cast<short>(locSBitFld.bfInfo_OrdNumStng))
                        ) {//Set UP Logic
                    rsLV.pCh = static_cast<char*>(rsLV.pCLURef->pOut);
                    rsLV.pCh += static_cast<unsigned char>(locSBitFld.bfInfo_OrdNumOut - 1); //As Idx
                    rsLV.chVal = 1;
//                     asm volatile(
//                    "bkpt 1"
//                    );
                    break;
                }
                shCounterFindObj++;
            }
            if (rsLV.pCh) {
                rsLV.arrPchIn = static_cast<char**>(rsLV.pCLUBase->pIn);
                rsLV.arrPchIn[ik] = rsLV.pCh;
            }
            if(rsLV.chVal != 1)
                rsLV.chErrCount++;//Is need?
        }
        else{
                if(rsLV.chVal != 1){
                rsLV.chErrCount |= 2;//Insert Data Error
                return;
                }
        }            
    }
}
void Shematic::SetupCLUInternalRefLed(void *pv){
    register long i,j;
//   register Init2LcVarArea *pInit2LcVarArea = (Init2LcVarArea *)pv;
	SBitFld_LUInInfo locSBitFld;
    LUCRefExchParam lcLUCRefExchParam;
    register Init2LcVarArea& rsLV = *(static_cast<Init2LcVarArea*>(pv));
    volatile short& shCounterScanedObj = *(static_cast<short*>(rsLV.pV));
if(rsLV.chErrCount != 0)
return;

    i = shCounterScanedObj + rsLV.shIdx;
    pv = static_cast<void*>(&rsLV.arrLUAreaListElem[i]);
    //rsLV.pCLUBase = (CLUBase*) ((LUAreaListElem*) pv)->pvLU;static_cast<CLUBase*>(
    rsLV.pCLUBase = static_cast<CLUBase*>((static_cast<LUAreaListElem*>(pv))->pvLU);
    for (long ik = 0; ik < OUTPUT_LED_SIGNALS_IN_TOTAL; ik++) {//rsLV.pCLUBase->chNumInput
        lcLUCRefExchParam.shLU_ObjScanIndex = shCounterScanedObj;
        lcLUCRefExchParam.chLU_OrdNumIn = ik;// + 1; in function use as Idx
        lcLUCRefExchParam.pCLUBase = rsLV.pCLUBase;
        FillSBitFld_LUInInfo2(static_cast<void*>(&lcLUCRefExchParam), static_cast<void*>(&locSBitFld));
        
        //if(sLV.lcLUCrossRefData.shRefIdLUStng == 0 && sLV.lcLUCrossRefData.shRefOrdNumStng ==0)
        if(locSBitFld.bfInfo_IdLUStng == 0 && locSBitFld.bfInfo_OrdNumStng ==0)
            {j = (-1);rsLV.chVal = 1;}
        else {
//            asm volatile(
//                "bkpt 1"
//            );
        }    
         //Find Obj
        j = EvalIdxinarrLUAreaListElem(static_cast<long>(locSBitFld.bfInfo_IdLUStng));
        if(j==(-2)){
         
            rsLV.pCh = static_cast<char*>(0);
            //rsLV.pCh = static_cast<char*>(rsLV.pCLURef->pOut);
            rsLV.pCh = static_cast<char*>(eRunErrorLed.pOut);
            rsLV.pCh += static_cast<unsigned char>(locSBitFld.bfInfo_OrdNumOut - 1); //As Idx
            if (rsLV.pCh) {
                rsLV.arrPchIn = static_cast<char**>(rsLV.pCLUBase->pIn);
                rsLV.arrPchIn[ik] = rsLV.pCh;
            }
        }else
        if(j!=(-1)){
             short shCounterFindObj = 0;
             short shAmtLookObj = 0;

            shAmtLookObj = static_cast<short>(EvalAmtIn_arrLUAreaListElem(static_cast<long>(locSBitFld.bfInfo_IdLUStng)));
            if(shAmtLookObj == (-1))
                shAmtLookObj = gblLUAreaAuxVar.shAmountPlacedLogicUnit-j;

            rsLV.chVal = 0;rsLV.pCh = static_cast<char*>(0);
            while ((shCounterFindObj) < shAmtLookObj && rsLV.chVal != 1) {
                i = j + shCounterFindObj;
                pv = static_cast<void*>(&rsLV.arrLUAreaListElem[i]);
                //rsLV.pCLURef = (CLUBase*) ((LUAreaListElem*) pv)->pvLU;
                rsLV.pCLURef = static_cast<CLUBase*>((static_cast<LUAreaListElem*>(pv))->pvLU);
                if ((rsLV.pCLURef->shShemasIdLUStng == static_cast<short>(locSBitFld.bfInfo_IdLUStng)) &&
                        (rsLV.pCLURef->shShemasOrdNumStng == static_cast<short>(locSBitFld.bfInfo_OrdNumStng))
                        ) {//Set UP Logic
                    rsLV.pCh = static_cast<char*>(rsLV.pCLURef->pOut);
                    rsLV.pCh += static_cast<unsigned char>(locSBitFld.bfInfo_OrdNumOut - 1); //As Idx
                    rsLV.chVal = 1;
//                     asm volatile(
//                    "bkpt 1"
//                    );
                    break;
                }
                shCounterFindObj++;
            }
            if (rsLV.pCh) {
                rsLV.arrPchIn = static_cast<char**>(rsLV.pCLUBase->pIn);
                rsLV.arrPchIn[ik] = rsLV.pCh;
            }
            if(rsLV.chVal != 1)
                rsLV.chErrCount++;//Is need?
        }
        else{
                if(rsLV.chVal != 1){
                rsLV.chErrCount |= 2;//Insert Data Error
                return;
                }
        }            
    }
}

long Shematic::Init(void) {

//-void *memset(void *s, int c, size_t n);
chInitTerminated = 0;
memset(static_cast<void*>(&gLUAreaMem),0,sizeof(SIZE_LU_AREA_LIST_ITEM));
memset(static_cast<void*>(&gblLUAreaAuxVar),0,sizeof(gblLUAreaAuxVar));
gblLUAreaAuxVar.lAmountFreeMem = (SIZE_MEM_BLK - sizeof (LUAreaListElem));
gblLUAreaAuxVar.lAmountUsedMem = sizeof (LUAreaListElem);
gblLUAreaAuxVar.pvHead =
static_cast<void*>(&(gLUAreaMem.chArRamPrgEvt[((SIZE_MEM_BLK) - 1)]));
p_current_config_prt = static_cast<void*>(&current_config_prt);
chMaxIteratoin = 
(static_cast<__CONFIG* >(p_current_config_prt))->n_output
+((static_cast<__CONFIG* >(p_current_config_prt))->n_led         )
+((static_cast<__CONFIG* >(p_current_config_prt))->n_alarm       )
+((static_cast<__CONFIG* >(p_current_config_prt))->n_group_alarm )
+((static_cast<__CONFIG* >(p_current_config_prt))->n_and         )
+((static_cast<__CONFIG* >(p_current_config_prt))->n_or          )
+((static_cast<__CONFIG* >(p_current_config_prt))->n_xor         )
+((static_cast<__CONFIG* >(p_current_config_prt))->n_not         )
+((static_cast<__CONFIG* >(p_current_config_prt))->n_timer       )
+((static_cast<__CONFIG* >(p_current_config_prt))->n_trigger);

chSumNLedPlusNOut = (static_cast<__CONFIG* >(p_current_config_prt))->n_output
+((static_cast<__CONFIG* >(p_current_config_prt))->n_led         );

shSum8Elem =  ((static_cast<__CONFIG* >(p_current_config_prt))->n_alarm       )
+((static_cast<__CONFIG* >(p_current_config_prt))->n_group_alarm )
+((static_cast<__CONFIG* >(p_current_config_prt))->n_and         )
+((static_cast<__CONFIG* >(p_current_config_prt))->n_or          )
+((static_cast<__CONFIG* >(p_current_config_prt))->n_xor         )
+((static_cast<__CONFIG* >(p_current_config_prt))->n_not         )
+((static_cast<__CONFIG* >(p_current_config_prt))->n_timer       )
+((static_cast<__CONFIG* >(p_current_config_prt))->n_trigger); 
chSumNTUPlusNLAN = ((static_cast<__CONFIG* >(p_current_config_prt))->n_tu)
+((static_cast<__CONFIG* >(p_current_config_prt))->n_input_GOOSE_block   )
+((static_cast<__CONFIG* >(p_current_config_prt))->n_input_MMS_block     )
+((static_cast<__CONFIG* >(p_current_config_prt))->n_network_output_block)
+((static_cast<__CONFIG* >(p_current_config_prt))->n_ts         );
//Max Amount sequently linked Elem [1]-[2]-[3]-[4]-[5]-[6]-[7]-[8]-[9]
chIteration = 5;
ClrTmrVars();
long lRes;
if(chInitTerminated != 1)
lRes = Init2();
//.TIM3InitInfo sInitT3Info = {
//.0xffff,(2000-1),1
//.};
//TIM3ReInit(static_cast<void*>(&sInitT3Info));

chInitTerminated = 1;
return lRes;
}
void Shematic::DoCalcStatInfo(void) {
    register long i, j;
    register long lDwnCtr;
i = 0;
    if(chInitTerminated == 0)
        return;
    TmrCalls();
    j = CBGSig::m_chCounterCall;    
    if(j >= 8)//100
        CBGSig::m_chCounterCall = 0;
    else
        CBGSig::m_chCounterCall = ++j;
    j = CBGSig::chMeasUpdateInterval;    
    if(j >= 20)//100
        CBGSig::chMeasUpdateInterval = 0;
    else
        CBGSig::chMeasUpdateInterval = ++j;
    
    //if(CBGSig::chMeasUpdateInterval == 0){
        for (long lIdChanell, ii = 0 ; ii < I_U ; ii++)    {
            lIdChanell  = CBGSig::ChanelsNames[ii];
            
            if(CBGSig::meas[lIdChanell] > measurement[lIdChanell])
                CBGSig::DMeas[lIdChanell] = i = 
                CBGSig::meas[lIdChanell] - measurement[lIdChanell];
            else
                CBGSig::DMeas[lIdChanell] = i =
                measurement[lIdChanell] - CBGSig::meas[lIdChanell];
             j = CBGSig::PickUPs[ii];    
            //if (CBGSig::DMeas[lIdChanell] > static_cast<unsigned long>(j)  )
            
                ;
            if (i > j  )//static_cast<unsigned long>(j)
                CBGSig::m_chCounterCall = 0;
            //else
                
            }
        if(CBGSig::chMeasUpdateInterval == 0){
            
             memcpy(reinterpret_cast<void*>(CBGSig::meas),
            reinterpret_cast<void*>(measurement), I_U*sizeof(long));
            i = CBGSig::m_chIdxGrupSamples;
            j = I_U*1;//sizeof(long)
//            lDwnCtr = reinterpret_cast<long>(&(CBGSig::measbuf[i][0]));
            
            memcpy(reinterpret_cast<void*>(&(CBGSig::measbuf[i][0])),
            //reinterpret_cast<void*>(PMeas), I_U*sizeof(long));
            reinterpret_cast<void*>(measurement), I_U*sizeof(long));
            i++;
            if(i > 2)
            i = 0;
            CBGSig::m_chIdxGrupSamples = i;
        
        }        
    //}    
    if(CBGSig::chNeedTimerCalculated >0)    
         CBGSig::m_chCounterCall = 0;//It`s initiated Recalc when Timer work    
   
//    CBGSig::chNeedRefrash = 1;        
        
    i = 0;    
//    UpdateStateDI();
    if( (chErrorState&1) != 0){
        //Set to 0 DOState

        eRunErrorLed.EvalRunErrorLed();
        return;
    }
    
    DoCalcLUSourcesStatInfo();
    FBWrp_Op(pCFixBlockWrp);
    lDwnCtr = chIteration;
    CLUBase::m_AuxInfo.ch = 0;
    do{
        //Startovyi Iterator
        //i = arIdxLUAreaListElem[LU_LSS-1];
        i = shIdxSum8ElemSeq;
        j = shSum8Elem;//kolichestvo elementov
        LUIteratorStatInfo(j,i);    
        //Startovyi Iterator    
        i = arIdxLUAreaListElem[LU_OUTPUT-1];
        //kolichestvo elementov
        j = chSumNLedPlusNOut;
        LUIteratorStatInfo(j,i);// LUIterator(j,i);//
        //i = arIdxLUAreaListElem[LU_TU-1];
        i = shIdxSumNTUPlusNLANSeq;
        j = chSumNTUPlusNLAN;
        LUIteratorStatInfo(j,i);//
        CLUBase::m_AuxInfo.ch++;
    //Predpolagaemyi uroven` vlozenosti
    }while(--lDwnCtr);
    
    eMuteAlarmLed.EvalMuteAlarmLed();
    eRunErrorLed.EvalRunErrorLed();
    eLUTestLed.CalCLUTestLedSchematic();
}
long Shematic::AllocateObj(void*pvObjImage) {
    register long i;
    register void* pv;
    intptr_t iIptr;

    struct {
        intptr_t lId, lsizeobj;
        void *pV;
        LUAreaListElem* arrLUAreaListElem;
        AllocInfo* pAllocInfo;
    } sLV;
    //check Id
    sLV.lsizeobj = 0;
    //i = EvalSizeObj(lId);//
    //if (i) {

        //Check pvObjImage
        if (pvObjImage != 0) {
            i = (static_cast<AllocInfo*>(pvObjImage))->shSize;
            //check Free Memory
            pv = static_cast<void*>(&gblLUAreaAuxVar);
            if ((static_cast<LUAreaAuxVar*>(pv))->lAmountFreeMem >=
                    static_cast<long>(i + SIZE_LU_AREA_LIST_ITEM)) {
                sLV.lId = ID_OBJ; //Save Id
                sLV.lsizeobj = (static_cast<AllocInfo*>(pvObjImage))->shSize;
                sLV.pV = pv;
                sLV.arrLUAreaListElem = &gLUAreaMem.headLUAreaList;
                i = (static_cast<LUAreaAuxVar*>(pv))->shAmountPlacedLogicUnit; //Now Index in LUAreaListElem

                if (i) {
                    i--; //Detect Head
                    pv = static_cast<void*>(&sLV.arrLUAreaListElem[i]); //Last Elem
                    //Mem Area
                    iIptr = reinterpret_cast<intptr_t>(( static_cast<LUAreaListElem*>(pv))->pvLU);
                    //Add size
                    iIptr -= sLV.lsizeobj; //((LUAreaListElem*)pv)->shSizeLU;
                    //
                    
                    pv = static_cast<void*>(&sLV.arrLUAreaListElem[i + 1]); //Next
                    (static_cast<LUAreaListElem*>(pv))->shSizeLU = static_cast<short>(sLV.lsizeobj);
                    (static_cast<LUAreaListElem*>(pv))->shIdLU   = static_cast<short>(sLV.lId);
                    (static_cast<LUAreaListElem*>(pv))->pvLU     = reinterpret_cast<void*>(iIptr);
                    gblLUAreaAuxVar.pvHead = reinterpret_cast<void*>(iIptr); // (lId - sLV.lId);//For check Only
                    //sLV.pCLUBase = ((LUAreaListElem*) pv)->pvLU;
                    
                } else {
                    pv = static_cast<void*>(&gLUAreaMem.headLUAreaList);

                    //First Init
                    iIptr = reinterpret_cast<intptr_t>(&gLUAreaMem.chArRamPrgEvt[SIZE_MEM_BLK]);
                    iIptr -= (sLV.lsizeobj);
                    (static_cast<LUAreaListElem*>(pv))->pvLU = reinterpret_cast<void*>(iIptr);
                    (static_cast<LUAreaListElem*>(pv) )->shSizeLU = static_cast<short>(sLV.lsizeobj);
                    (static_cast<LUAreaListElem*>(pv) )->shIdLU =   static_cast<short>(sLV.lId);
                    gblLUAreaAuxVar.pvHead = gblLUAreaAuxVar.pvTail =
                            (static_cast<LUAreaListElem*> (pv))->pvLU;
                    //sLV.pCLUBase = (CLUBase*) ((LUAreaListElem*) pv)->pvLU;
                    
                }
                //Bield Obj in Mem
                if( ((static_cast<AllocInfo*>(pvObjImage))->shBF)&1 ){
                    memcpy(reinterpret_cast<void*>(iIptr),
                    (static_cast<AllocInfo*>(pvObjImage))->pvSrc, sLV.lsizeobj);
                    }
                (static_cast<AllocInfo*>(pvObjImage))->pvDsc = reinterpret_cast<void*>(iIptr);
                pv = static_cast<void*>(&gblLUAreaAuxVar);
                //?!!!((LUAreaAuxVar*) pv)->lAmountFreeMem -= ((short) sLV.lsizeobj + SIZE_LU_AREA_LIST_ITEM);
                //?!!!((LUAreaAuxVar*) pv)->lAmountUsedMem += ((short) sLV.lsizeobj + SIZE_LU_AREA_LIST_ITEM);
                (static_cast<LUAreaAuxVar*> (pv))->lAmountFreeMem -= (sLV.lsizeobj + SIZE_LU_AREA_LIST_ITEM);
                (static_cast<LUAreaAuxVar*>(pv))->lAmountUsedMem += ( sLV.lsizeobj + SIZE_LU_AREA_LIST_ITEM);

            } else sLV.lsizeobj = 0;
        }
        return static_cast<long>(sLV.lsizeobj);
    //}i = EvalSizeObj(lId);//



    
}
//=====================================================================================================
//''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
//FillArr_n_linkVal Added 08-10-2018
//....................................................................................................
//=====================================================================================================
long  Shematic::FillArr_n_linkVal(void ){
long n,l;
void* pv;
CLUBase *pB;

short shCounterFindObj = 0;
short shAmtLookObj = 0;
struct {
        char chVal;
        //short shKey;
        //char *pCh;
        //CLUBase *pCLURef;
        LUAreaListElem* arrLUAreaListElem;
        union {
        long* pLOrderCalcNum;
        short* pShOrderCalcNum;
        char  *pCh;
        }P;
} rsLV;
    //pv = static_cast<void*>(&current_config_prt);
            
    //shAmtLookObj = gblLUAreaAuxVar.shAmountPlacedLogicUnit-j;
    shAmtLookObj = (static_cast<__CONFIG* >(p_current_config_prt))->n_input
                    + (static_cast<__CONFIG* >(p_current_config_prt))->n_output
                    + (static_cast<__CONFIG* >(p_current_config_prt))->n_led
                    + (static_cast<__CONFIG* >(p_current_config_prt))->n_button
                    + (static_cast<__CONFIG* >(p_current_config_prt))->n_alarm
                    + (static_cast<__CONFIG* >(p_current_config_prt))->n_group_alarm
                    + (static_cast<__CONFIG* >(p_current_config_prt))->n_and
                    + (static_cast<__CONFIG* >(p_current_config_prt))->n_or
                    + (static_cast<__CONFIG* >(p_current_config_prt))->n_xor
                    + (static_cast<__CONFIG* >(p_current_config_prt))->n_not
                    + (static_cast<__CONFIG* >(p_current_config_prt))->n_timer
                    + (static_cast<__CONFIG* >(p_current_config_prt))->n_trigger
                    + (static_cast<__CONFIG* >(p_current_config_prt))->n_meander
                    + (static_cast<__CONFIG* >(p_current_config_prt))->n_tu
                    + (static_cast<__CONFIG* >(p_current_config_prt))->n_ts;
    rsLV.arrLUAreaListElem = &gLUAreaMem.headLUAreaList;
    rsLV.chVal = 0;//rsLV.pCh = static_cast<char*>(0);
    
    while ((shCounterFindObj) < shAmtLookObj && rsLV.chVal == 0) {
                //i = j + shCounterFindObj;
        pv = static_cast<void*>(&rsLV.arrLUAreaListElem[shCounterFindObj]);
        //rsLV.pCLURef = (CLUBase*) ((LUAreaListElem*) pv)->pvLU;
        pB = static_cast<CLUBase*>((static_cast<LUAreaListElem*>(pv))->pvLU);//rsLV.pCLURef

                switch (pB->chTypeLogicFunction ) {
                    case LU_OP_READ_DI: //TARAS_ALAS_STNG_LU_INPUT:
            //            UN_LN.pLN_INPUT = reinterpret_cast<__LN_INPUT*>( spca_of_p_prt[ID_FB_INPUT - _ID_FB_FIRST_VAR]);
                           n = (static_cast<__LN_INPUT*>(pB-> pvCfgLN))->settings._n;
                           l = (static_cast<__LN_INPUT*>(pB-> pvCfgLN))->settings._link;
                        break;
                    case LU_OP_SET_OUT: //TARAS_ALAS_STNG_LU_OUTPUT:
                        //UN_LN.pLN_OUTPUT_LED = reinterpret_cast<__LN_OUTPUT_LED*>( spca_of_p_prt[ID_FB_OUTPUT - _ID_FB_FIRST_VAR]);
                        //i = UN_LN.pLN_OUTPUT_LED[shRelativeIndexLU].settings._n;
                        n = (static_cast<__LN_OUTPUT_LED*>(pB-> pvCfgLN))->settings._n;
                        l = (static_cast<__LN_OUTPUT_LED*>(pB-> pvCfgLN))->settings._link;
                        
                        break;
                    case LU_OP_SET_LED: //TARAS_ALAS_STNG_LU_LED:
                        //UN_LN.pLN_OUTPUT_LED = reinterpret_cast<__LN_OUTPUT_LED*>( spca_of_p_prt[ID_FB_LED - _ID_FB_FIRST_VAR]);
                        //i = UN_LN.pLN_OUTPUT_LED[shRelativeIndexLU].settings._n;
                            n = (static_cast<__LN_OUTPUT_LED*>(pB-> pvCfgLN))->settings._n;
                            l = (static_cast<__LN_OUTPUT_LED*>(pB-> pvCfgLN))->settings._link;
                        break;
                    case LU_OP_F_KEY: //TARAS_ALAS_STNG_LU_KEY:
            //            UN_LN.pLN_INPUT = reinterpret_cast<__LN_BUTTON_TU*>( spca_of_p_prt[ID_FB_BUTTON - _ID_FB_FIRST_VAR]);
                            n = (static_cast<__LN_BUTTON*>(pB-> pvCfgLN))->settings._n;
                            l = (static_cast<__LN_BUTTON*>(pB-> pvCfgLN))->settings._link;
                        break;
                    case LU_OP_LSS: //TARAS_ALAS_STNG_LU_ALARMS:
                        //UN_LN.pLN_ALARM = reinterpret_cast<__LN_ALARM*>( spca_of_p_prt[ID_FB_ALARM - _ID_FB_FIRST_VAR]);
                        //i = UN_LN.pLN_ALARM[shRelativeIndexLU].settings._n;
                        n = (static_cast<__LN_ALARM*>(pB-> pvCfgLN))->settings._n;
                        l = (static_cast<__LN_ALARM*>(pB-> pvCfgLN))->settings._link;
                        break;
                    case LU_OP_BGS:  //TARAS_ALAS_STNG_LU_BGS:
                        //UN_LN.pLN_GROUP_ALARM = reinterpret_cast<__LN_GROUP_ALARM*>( spca_of_p_prt[ID_FB_GROUP_ALARM - _ID_FB_FIRST_VAR]);
                        n = (static_cast<__LN_GROUP_ALARM*>(pB-> pvCfgLN))->settings._n;
                        l = (static_cast<__LN_GROUP_ALARM*>(pB-> pvCfgLN))->settings._link;
                        break;
                    case LU_OP_AND: //TARAS_ALAS_STNG_LU_AND:
                        //UN_LN.pLN_AND = reinterpret_cast<__LN_AND*>( spca_of_p_prt[ID_FB_AND - _ID_FB_FIRST_VAR]);
                        //i = UN_LN.pLN_AND[shRelativeIndexLU].settings._n;
                        n = (static_cast<__LN_AND*>(pB-> pvCfgLN))->settings._n;
                        l = (static_cast<__LN_AND*>(pB-> pvCfgLN))->settings._link;
                        break;
                    case LU_OP_OR: //TARAS_ALAS_STNG_LU_OR:
                        //UN_LN.pLN_OR = reinterpret_cast<__LN_OR*>( spca_of_p_prt[ID_FB_OR - _ID_FB_FIRST_VAR]);
                       //i = UN_LN.pLN_OR[shRelativeIndexLU].settings._n;
                       n = (static_cast<__LN_OR*>(pB-> pvCfgLN))->settings._n;
                       l = (static_cast<__LN_OR*>(pB-> pvCfgLN))->settings._link;
                        break;
                    case LU_OP_XOR: //TARAS_ALAS_STNG_LU_XOR:
                        //UN_LN.pLN_XOR = reinterpret_cast<__LN_XOR*>( spca_of_p_prt[ID_FB_XOR - _ID_FB_FIRST_VAR]);
                        //i = UN_LN.pLN_XOR[shRelativeIndexLU].settings._n;
                        n = (static_cast<__LN_XOR*>(pB-> pvCfgLN))->settings._n;
                        l = (static_cast<__LN_XOR*>(pB-> pvCfgLN))->settings._link;
                        break;
                    case LU_OP_NOT: //TARAS_ALAS_STNG_LU_NOT:
                        //UN_LN.pLN_NOT = reinterpret_cast<__LN_NOT*>( spca_of_p_prt[ID_FB_NOT - _ID_FB_FIRST_VAR]);
                        //i = UN_LN.pLN_NOT[shRelativeIndexLU].settings._n;
                        n = (static_cast<__LN_NOT*>(pB-> pvCfgLN))->settings._n;
                        l = (static_cast<__LN_NOT*>(pB-> pvCfgLN))->settings._link;
                        break;            
                    case LU_OP_MFT: //TARAS_ALAS_STNG_LU_TIMER:
                        //UN_LN.pLN_TIMER = reinterpret_cast<__LN_TIMER*>( spca_of_p_prt[ID_FB_TIMER - _ID_FB_FIRST_VAR]);
                        //i = UN_LN.pLN_TIMER[shRelativeIndexLU].settings._n;
                        n = (static_cast<__LN_TIMER*>(pB-> pvCfgLN))->settings._n;
                        l = (static_cast<__LN_TIMER*>(pB-> pvCfgLN))->settings._link;
                        break;
                    case LU_OP_D_TRG__4_2: //TARAS_ALAS_STNG_LU_TRIGGER:
                        //UN_LN.pLN_TRIGGER = reinterpret_cast<__LN_TRIGGER*>( spca_of_p_prt[ID_FB_TRIGGER - _ID_FB_FIRST_VAR]);
                        //i = UN_LN.pLN_TRIGGER[shRelativeIndexLU].settings._n;
                        n = (static_cast<__LN_TRIGGER*>(pB-> pvCfgLN))->settings._n;
                        l = (static_cast<__LN_TRIGGER*>(pB-> pvCfgLN))->settings._link;
                        break;
                    case LU_OP_MEANDR:  //TARAS_ALAS_STNG_LU_MEANDERS:
            //            UN_LN.pLN_INPUT = reinterpret_cast<__LN_MEANDER*>( spca_of_p_prt[ID_FB_MEANDER - _ID_FB_FIRST_VAR]);
                            n = (static_cast<__LN_MEANDER*>(pB-> pvCfgLN))->settings._n;
                            l = (static_cast<__LN_MEANDER*>(pB-> pvCfgLN))->settings._link;
            
                        break;
                    case LU_OP_TU: //TARAS_ALAS_STNG_LU_TU:
                        //UN_LN.pLN_TU = reinterpret_cast<__LN_TU*>( spca_of_p_prt[ID_FB_TU - _ID_FB_FIRST_VAR]);
                        //i = UN_LN.pLN_TU[shRelativeIndexLU].settings._n;
                        n = (static_cast<__LN_TU*>(pB-> pvCfgLN))->settings._n;
                        l = (static_cast<__LN_TU*>(pB-> pvCfgLN))->settings._link;
                        break;
                        
                    case LU_OP_TS: //TARAS_ALAS_STNG_LU_TS:
                        //UN_LN.pLN_TS = reinterpret_cast<__LN_TS*>( spca_of_p_prt[ID_FB_TS - _ID_FB_FIRST_VAR]);
                        //i = UN_LN.pLN_TS[shRelativeIndexLU].settings._n;
                        n = (static_cast<__LN_TS*>(pB-> pvCfgLN))->settings._n;
                        l = (static_cast<__LN_TS*>(pB-> pvCfgLN))->settings._link;
                        break;
                    case LU_OP_GOOSE: //TARAS_ALAS_STNG_LU_TS:
                        //UN_LN.pLN_TS = reinterpret_cast<__LN_INPUT_GOOSE_BLOCK>( spca_of_p_prt[ID_FB_TS - _ID_FB_FIRST_VAR]);
                        //i = UN_LN.pLN_TS[shRelativeIndexLU].settings._n;
                        n = (static_cast<__LN_INPUT_GOOSE_BLOCK*>(pB-> pvCfgLN))->settings._n;
                        l = (static_cast<__LN_INPUT_GOOSE_BLOCK*>(pB-> pvCfgLN))->settings._link;
                        break;
                    case LU_OP_MMS: //TARAS_ALAS_STNG_LU_TS:
                        //UN_LN.pLN_TS = reinterpret_cast<__LN_INPUT_MMS_BLOCK*>( spca_of_p_prt[ID_FB_TS - _ID_FB_FIRST_VAR]);
                        //i = UN_LN.pLN_TS[shRelativeIndexLU].settings._n;
                        n = (static_cast<__LN_INPUT_MMS_BLOCK*>(pB-> pvCfgLN))->settings._n;
                        l = (static_cast<__LN_INPUT_MMS_BLOCK*>(pB-> pvCfgLN))->settings._link;
                        break;
                    case LU_OP_LAN: //TARAS_ALAS_STNG_LU_TS:
                        //UN_LN.pLN_TS = reinterpret_cast<__LN_TS*>( spca_of_p_prt[ID_FB_TS - _ID_FB_FIRST_VAR]);
                        //i = UN_LN.pLN_TS[shRelativeIndexLU].settings._n;
                        n = (static_cast<__LN_NETWORK_OUTPUT_BLOCK*>(pB-> pvCfgLN))->settings._n;
                        l = (static_cast<__LN_NETWORK_OUTPUT_BLOCK*>(pB-> pvCfgLN))->settings._link;
                        break;
                     //TARAS_ALAS_STNG_LU_LOG:
                        //UN_LN.pLN_TS = reinterpret_cast<__LN_TS*>( spca_of_p_prt[ID_FB_TS - _ID_FB_FIRST_VAR]);
                        //i = UN_LN.pLN_TS[shRelativeIndexLU].settings._n;
                        //break;
                        
                    default:
                        ;
                }
                //Put Data in Array

        if ( n <= shAmtLookObj && n >0){
            //short *pSh = static_cast<short*>(pExecSeq);
            //pSh[n] = pB->shLUBieldOrdNum;
            //( static_cast<long*>(pExecSeq))[n-1] = pB->shLUBieldOrdNum;
            rsLV.P.pLOrderCalcNum = static_cast<long*>(pExecSeq)+(n-1);
            rsLV.P.pLOrderCalcNum[0]  =  pB->shLUBieldOrdNum;
            rsLV.P.pShOrderCalcNum[1] = l;//Link Field
            // static_cast<short*>(pExecSeq)[n]   = l;//Link Field
            
        }
        else if (n < 0){
				break;//rsLV.chVal |= 1;
        }
        else{
            rsLV.chVal |= 2;
        }
        shCounterFindObj++;
        
    }
    shAmountExecSeqElem = shCounterFindObj;
    return rsLV.chVal;

}            








 short shLssLUAreaListElemIndex; 
void GetLssMuteAlarmBlockAddr(void* pv){
register long i,j;
struct {
LUAreaListElem* arrLUAreaListElem;
MuteAlarmInOutParam *pInOutParam; 
CLULss *pCLULss;
//char* pCh;
    } sLV;
sLV.pInOutParam = static_cast<MuteAlarmInOutParam*>(pv);
sLV.arrLUAreaListElem = &gLUAreaMem.headLUAreaList;
sLV.pInOutParam->pChBlock = static_cast<char*>(0);
sLV.pInOutParam->pChAlarm = static_cast<char*>(0);
sLV.pInOutParam->pChMute  = static_cast<char*>(0); 
if(shLssLUAreaListElemIndex == 0){
j = sh.EvalIdxinarrLUAreaListElem(TARAS_ALAS_STNG_LU_ALARMS);
shLssLUAreaListElemIndex = j;
}
else
j = shLssLUAreaListElemIndex;
i = sLV.pInOutParam->lIndexLss + j;

pv = static_cast<void*>( &sLV.arrLUAreaListElem[i ]);
sLV.pCLULss = static_cast<CLULss*>( ( static_cast<LUAreaListElem*>(pv) )->pvLU);
pv = static_cast<void*>(sLV.pCLULss->arrPchIn[LSS_IN_NAME__BLOCK_I-1]);
sLV.pInOutParam->pChBlock = static_cast<char*>(pv);
sLV.pInOutParam->pChAlarm = static_cast<char*>(&(sLV.pCLULss->arrOut[LSS_OUT_NAME_ALARM-1]));
sLV.pInOutParam->pChMute  = static_cast<char*>(&(sLV.pCLULss->arrOut[LSS_OUT_NAME_MUTE-1]));
}
void GetLUTestLedInDataAddrOld(void* pv){
register long i,j;
struct {
LUAreaListElem* arrLUAreaListElem;
TestLedInOutParam *pInOutParam; 
CLUFKey *pCLUFKey;
//char* pCh;
    } sLV;
sLV.pInOutParam = static_cast<TestLedInOutParam*>(pv);
sLV.arrLUAreaListElem = &gLUAreaMem.headLUAreaList;
sLV.pInOutParam->pChTest  = static_cast<char*>(0); 
sLV.pInOutParam->pChReset = static_cast<char*>(0); 

//Only Now find Elem Test
j = sh.EvalIdxinarrLUAreaListElem(TARAS_ALAS_STNG_LU_KEY);
i = j + FIX_BUTTON_TEST;
pv = static_cast<void*>( &sLV.arrLUAreaListElem[i ]);
sLV.pCLUFKey = static_cast<CLUFKey*>( ( static_cast<LUAreaListElem*>(pv) )->pvLU);    
sLV.pInOutParam->pChTest = static_cast<char*>(&(sLV.pCLUFKey->arrOut[0]));
//Set Reset to VCC
sLV.pInOutParam->pChReset = &chGblVcc;
}
void GetLUTestLedInDataAddr(void* pv){
register long i,j;
SBitFld_LUInInfo locSBitFld;
struct {
LUAreaListElem* arrLUAreaListElem;
TestLedInOutParam *pInOutParam; 
CLUBase* pCLUBase;
//char* pCh;
    } sLV;
sLV.pInOutParam = static_cast<TestLedInOutParam*>(pv);
sLV.arrLUAreaListElem = &gLUAreaMem.headLUAreaList;
sLV.pInOutParam->pChTest  = static_cast<char*>(0); 
sLV.pInOutParam->pChReset = static_cast<char*>(0); 

i = settings_fix_prt.param[FIX_BLOCK_TEST_INPUT];
locSBitFld.bfInfo_IdLUStng = 
        (i >> SFIFT_PARAM_ID ) & MASKA_PARAM_ID ;//Typ Funktsional?noho bloku
locSBitFld.bfInfo_OrdNumStng = 
        (i >> SFIFT_PARAM_N  ) & MASKA_PARAM_N  ;//Poryadkovyy nomer
locSBitFld.bfInfo_OrdNumOut = 
        (i >> SFIFT_PARAM_OUT) & MASKA_PARAM_OUT;//Nomer vykhodu;

j = sh.EvalIdxinarrLUAreaListElem(static_cast<long>(locSBitFld.bfInfo_IdLUStng));
 if(j!=(-1)){
    i = j+locSBitFld.bfInfo_OrdNumStng - 1;
    pv = static_cast<void*>( &sLV.arrLUAreaListElem[i ]);
    sLV.pCLUBase = static_cast<CLUBase*>( ( static_cast<LUAreaListElem*>(pv) )->pvLU);
    pv = sLV.pCLUBase->pOut;
    j = locSBitFld.bfInfo_OrdNumOut - 1;
    if(pv!= 0)
    sLV.pInOutParam->pChTest = static_cast<char*>(pv)+j;
    }
i = settings_fix_prt.param[FIX_BLOCK_TEST_RESET];
locSBitFld.bfInfo_IdLUStng = 
        (i >> SFIFT_PARAM_ID ) & MASKA_PARAM_ID ;//Typ Funktsional?noho bloku
locSBitFld.bfInfo_OrdNumStng = 
        (i >> SFIFT_PARAM_N  ) & MASKA_PARAM_N  ;//Poryadkovyy nomer
locSBitFld.bfInfo_OrdNumOut = 
        (i >> SFIFT_PARAM_OUT) & MASKA_PARAM_OUT;//Nomer vykhodu

j = sh.EvalIdxinarrLUAreaListElem(static_cast<long>(locSBitFld.bfInfo_IdLUStng));
 if(j!=(-1)){
    i = j+locSBitFld.bfInfo_OrdNumStng - 1;
    pv = static_cast<void*>( &sLV.arrLUAreaListElem[i ]);
    sLV.pCLUBase = static_cast<CLUBase*>( ( static_cast<LUAreaListElem*>(pv) )->pvLU);
    pv = sLV.pCLUBase->pOut;
    j = locSBitFld.bfInfo_OrdNumOut - 1;
    if(pv!= 0)
    sLV.pInOutParam->pChReset = static_cast<char*>(pv)+j;
    }

}
void GetMuteAlarmBlockAddr(void* pv){
register long i,j;
SBitFld_LUInInfo locSBitFld;

struct {
LUAreaListElem* arrLUAreaListElem;
MuteAlarmInOutParam *pInOutParam; 
CLUBase* pCLUBase;
//char* pCh;
    } sLV;
    
sLV.pInOutParam = static_cast<MuteAlarmInOutParam*>(pv);
sLV.arrLUAreaListElem = &gLUAreaMem.headLUAreaList;
sLV.pInOutParam->pChBlock = static_cast<char*>(0);
sLV.pInOutParam->pChAlarm = static_cast<char*>(0);
sLV.pInOutParam->pChMute  = static_cast<char*>(0); 

i = settings_fix_prt.param[FIX_BLOCK_ALARM];
locSBitFld.bfInfo_IdLUStng = 
        (i >> SFIFT_PARAM_ID ) & MASKA_PARAM_ID ;//Typ Funktsional?noho bloku
locSBitFld.bfInfo_OrdNumStng = 
        (i >> SFIFT_PARAM_N  ) & MASKA_PARAM_N  ;//Poryadkovyy nomer
locSBitFld.bfInfo_OrdNumOut = 
        (i >> SFIFT_PARAM_OUT) & MASKA_PARAM_OUT;//Nomer vykhodu;

j = sh.EvalIdxinarrLUAreaListElem(static_cast<long>(locSBitFld.bfInfo_IdLUStng));
 if(j!=(-1)){
    i = j+locSBitFld.bfInfo_OrdNumStng - 1;
    pv = static_cast<void*>( &sLV.arrLUAreaListElem[i ]);
    sLV.pCLUBase = static_cast<CLUBase*>( ( static_cast<LUAreaListElem*>(pv) )->pvLU);
    pv = sLV.pCLUBase->pOut;
    j = locSBitFld.bfInfo_OrdNumOut - 1;
    if(pv!= 0)
    sLV.pInOutParam->pChAlarm = static_cast<char*>(pv)+j;
    }
i = settings_fix_prt.param[FIX_BLOCK_BLOCK];
locSBitFld.bfInfo_IdLUStng = 
        (i >> SFIFT_PARAM_ID ) & MASKA_PARAM_ID ;//Typ Funktsional?noho bloku
locSBitFld.bfInfo_OrdNumStng = 
        (i >> SFIFT_PARAM_N  ) & MASKA_PARAM_N  ;//Poryadkovyy nomer
locSBitFld.bfInfo_OrdNumOut = 
        (i >> SFIFT_PARAM_OUT) & MASKA_PARAM_OUT;//Nomer vykhodu

j = sh.EvalIdxinarrLUAreaListElem(static_cast<long>(locSBitFld.bfInfo_IdLUStng));
 if(j!=(-1)){
    i = j+locSBitFld.bfInfo_OrdNumStng - 1;
    pv = static_cast<void*>( &sLV.arrLUAreaListElem[i ]);
    sLV.pCLUBase = static_cast<CLUBase*>( ( static_cast<LUAreaListElem*>(pv) )->pvLU);
    pv = sLV.pCLUBase->pOut;
    j = locSBitFld.bfInfo_OrdNumOut - 1;
    if(pv!= 0)
    sLV.pInOutParam->pChBlock = static_cast<char*>(pv)+j;
    }
i = settings_fix_prt.param[FIX_BLOCK_MUTE];
locSBitFld.bfInfo_IdLUStng = 
        (i >> SFIFT_PARAM_ID ) & MASKA_PARAM_ID ;//Typ Funktsional?noho bloku
locSBitFld.bfInfo_OrdNumStng = 
        (i >> SFIFT_PARAM_N  ) & MASKA_PARAM_N  ;//Poryadkovyy nomer;
locSBitFld.bfInfo_OrdNumOut = 
        (i >> SFIFT_PARAM_OUT) & MASKA_PARAM_OUT;//Nomer vykhodu;

j = sh.EvalIdxinarrLUAreaListElem(static_cast<long>(locSBitFld.bfInfo_IdLUStng));
 if(j!=(-1)){
    i = j+locSBitFld.bfInfo_OrdNumStng - 1;
    pv = static_cast<void*>( &sLV.arrLUAreaListElem[i ]);
    sLV.pCLUBase = static_cast<CLUBase*>( ( static_cast<LUAreaListElem*>(pv) )->pvLU);
    pv = sLV.pCLUBase->pOut;
    j = locSBitFld.bfInfo_OrdNumOut - 1;
    if(pv!= 0)
    sLV.pInOutParam->pChMute  = static_cast<char*>(pv)+j;
    }

}  
//""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
//``````````````````````````````````````````````````````````````````````````````````
//==================================================================================
//--- 			 Interface function for CPP Schematic     -----------
//==================================================================================
//..................................................................................
//""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
long InitSchematic(void){
//    	    asm volatile(
//                "bkpt 1"
//                );

return sh.Init();;
}

void DoCalcWrp(void){

sh.DoCalc();
//sh.DoCalcLUSources();
    UpdateOutDiagn();
    
}

void DoCalcStatInfoWrp(void){
sh.DoCalcStatInfo();
//sh.DoCalcLUSources();
}



CStatInfoStore hldrCStatInfoStore;



