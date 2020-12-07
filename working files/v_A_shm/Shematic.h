#pragma once

#define NUM_IN_POINTS  8
#define NUM_OUT_POINTS 4
#define TOTAL_POINTS (NUM_IN_POINTS+NUM_OUT_POINTS)
#define TOTAL_SHEMATIC_MEM 0

//GetHashId by Index LU in Setting Mem
void GetHIDLU(void*pv,long lIdxLUinStng );

//Identificator Logic Unit

enum ID_LU { 
    BASE_POINT = 1,
    POINT    ,
    EXTENDED ,
    LU_AND   ,
    LU_OR    ,
    LU_XOR   ,
    LU_TIMERS,
    LU_TRIGGERS,
    LU_ALARMS,
    LU_MEANDERS,
    LU_INPUT ,
    LU_OUTPUT ,
    LU_LED,
    LU_NOT,
    LU_MFT,
    LU_FKEY,
    LU_LSS,
    LU_BGS,
    LU_TU,
    LU_TS,
    LU_GOOSE,
    LU_MMS,
    LU_LAN,
    LU_LOG,
    LU_STNG_FIX,
    TOTAL_LU,
    ID_OBJ
};

typedef struct config_tag{ 
    long device_id;                   // Тип пристрою
    //  long n_AmtPoints;
    long n_input;                  //Кількість дискретних входів 0i1O
    long n_output;                 //Кількість дискретних виходів 1i0O
    long n_led;                    //Кількість  1i0O
    long n_and;                       // Кількість елементів "І" 8i1O
    long n_or;                        // Кількість елементів "АБО" 8i1O
    long n_xor;                       // Кількість елементів "Викл.АБО"2i1O
    long n_not;                       // Кількість елементів "НЕ" 1i1O
    long n_timers;                    // Кількість таймерів 1i1O
    long n_triggers;                  // Кількість триґерів 2i1O
    long n_alarms;                    // Кількість блоків сигналізацій
    long n_meanders;                  // Кількість генераторів меандру 0i1O
    //
 
  unsigned char time_config[7+1];       // Час останніх змін уставок-витримок-управління
                                        // Останній байт масиву сигналізує мітку звідки зміни були проведені
                                        // 0 - мінімальні параметри
                                        // 1 - клавіатура
                                        // 2 - USB
                                        // 3 - RS-485
   
} __CONFIG_CPP; 

#ifdef __cplusplus
extern "C" {
#endif

extern long InitSchematic(void);
extern long ReInitSchematic(void);

extern void DoCalcWrp(void);
extern void DoCalcStatInfoWrp(void);
#ifdef __cplusplus
}
#endif




//extern InPoint ar5Points[];
class Shematic
{
    char  chInitTerminated;

    void* pLUAreaList;
    void* p_current_config_prt;//__CONFIG *
    void* pCFixBlockWrp;
    void* pExecSeq;

    short arIdxLUAreaListElem[TOTAL_LU];

    char  chMaxIteratoin;
    char  chIteration;
    char  chSumNLedPlusNOut;
    char  chSumNTUPlusNLAN;

    short shSum8Elem;
    short shIdxSumNLedPlusNOutSeq;
    short shIdxSumNTUPlusNLANSeq;
    short shIdxSum8ElemSeq;
    short shSizeExecSeq;short shAmountExecSeqElem;

public:
    Shematic(void);
    ~Shematic(void);
    void DoCalc(void);
    void DoCalcStatInfo(void);
    void DoCalcLU_V01(void);
    void DoCalcLU(void);
    void DoCalcLUSources(void);
    void DoCalcLUSourcesStatInfo(void);
    void LUSelector( long lIdxLU);
    void* LUSelectorRV( long lIdxLU);
    void LUIterator(long AmountCalcLU, long lIdxLU);
    void LUIteratorStatInfo(long AmountCalcLU, long lIdxLU);
    void Init_(void);
    long Init(void);
    void Init1(void);
    void PrintPointsState(void);
    void PrintShematicElemPointsState(void);
    void printResult(void);
    long InsertLU(long lId, void*pvObjImage);
    long EvalSizeObj(long lId);
    long AllocateObj(void*pvObjImage);
    void ChangeRelativeOnEvalLinks(void);
    void ChangeStngOrdnumRelOnBase(long lIdxScanedObj);
    void SetupCircutLinks(void *pv);
    void SetupCircutLinks2(void *pv);
    void CreateTestSchema(void);
    static long GetTrueOrderNum(void);
    void DetectCircutLinks(void);
    void SetupLULinks(void *pv);
    //	friend void GetHIDLU(void**ppv,long lIdxLUinStng );
    long Init2(void);
    void SetupCLUDInput_0_1StngParam(void *pv);
    void SetupCLUDout_1_0StngParam(void *pv);
    void SetupCLULedStngParam(void *pv);
    void SetupCLUAnd_8_1StngParam(void *pv);
    void SetupCLUOr_8_1StngParam(void *pv);
    void SetupCLUXor_8_1StngParam(void *pv);
    void SetupCLUNot_1_1StngParam(void *pv);
    void SetupCLUMft_2_1StngParam(void *pv);
    void SetupCLUFKeyStngParam(void *pv);
    void SetupCLULssStngParam(void *pv);
    void SetupCBGSigStngParam(void *pv);
    void SetupCLUTrigStngParam(void *pv);
    void SetupCPulseAlternatorStngParam(void *pv);
    void SetupCLUTuStngParam(void *pv);
    void SetupCLUTsStngParam(void *pv);
    void SetupCLUGooseStngParam(void *pv);
    void SetupCLUMmsStngParam(void *pv);
    void SetupCLULanStngParam(void *pv);
    void SetupCLULogStngParam(void *pv);
    long FillSBitFld_LUInInfo(void *pvIn,void *pvOut);
    long FillSBitFld_LUInInfo2(void *pvIn,void *pvOut);
    long EvalIdxibnarrSBitFldCRefInfo(long lLUStng);
    long EvalIdxinarrLUAreaListElem(long lLUStng);
    long EvalAmtIn_arrLUAreaListElem(long lLUStng);
    void SetupCLUInternalRef(void *pv);
    void SetupCLUInternalRef2(void *pv);
    void SetupCLUInternalRefLed(void *pv);
    long FillArr_n_linkVal(void );
	friend long InitSchematic(void);
	friend long ReInitSchematic(void);
	friend void DoCalcWrp(void);
	friend void DoCalcStatInfoWrp(void);
	friend void GetLssMuteAlarmBlockAddr(void* pv);
    friend void GetLUTestLedInDataAddr(void* pv);
};

typedef struct tag_LUAreaParamDsc{
    short shAmountPlacedLogicUnit;//counter placed
    short shIdxLUAreaListElem;    //Index LU Area List Elem
    long  lAmountFreeMem, lAmountUsedMem;
    void *pvHead, *pvTail;


}LUAreaAuxVar;

#ifndef LU_OUT_DSC
#define LU_OUT_DSC
typedef struct tag_LUInputDsc {
    short shIdLUStng;   // Type LU Described in settings
    short shOrdNumStng; // Order Num LU Described in settings
    char  chOrdNumOut;  // this LU Out Order Num
    //char *pStateOut;
}LUOutDsc;//In future compres in BitField

//Use (disjoint types)
typedef struct LUInInfo_Tag{
    union{
	    
        struct{
            //long  OrdNumStng :14;
            //long  shIdLUStng : 9;
            //long  chOrdNumOut: 9;
            // 16 Порядковий номер виходу функціонального блоку (нумерація іде натуральними числами)
            // 8  Порядковий номер функціонального блоку (нумерація іде натуральними числами)
            // 8  ID-функціонального блоку (нумерація іде натуральними числами)
            long bfInfo_OrdNumOut : 16;
            long bfInfo_OrdNumStng : 8;
            long bfInfo_IdLUStng : 8;
        }sBitFld_LUInInfo;
        char chArUrgData [4];
        long lArUrgData [1];
            
    }UN_BitFld_LUInInfo;

}LUInInfoDsc;
/* Try to insert SBitFld_LUInInfo        
 * to exclude sBitFld_LUInInfo           
 * from UN_BitFld_LUInInfo it            
 * take you mutch easy code conversion   
 * 
 */
 
 


typedef struct SBitFld_LUInInfo_tag{
    long  bfInfo_OrdNumOut : 16;
    long  bfInfo_OrdNumStng:  8;
    long  bfInfo_IdLUStng  :  8;
}SBitFld_LUInInfo;

typedef struct tag_LUCrossRefDsc {
    short shBaseIdLUStng;
    short shBaseOrdNumStng;
    //	char  shBaseOrdNumIn ;//For more free Defining
    short shRefIdLUStng;   // Type LU Described in settings
    short shRefOrdNumStng; // Order Num LU Described in settings
    char  chRefOrdNumOut;  // this LU Out Order Num
    //char *pStateOut;
}LUCrossRefDsc;

typedef struct tag_SBitFldCRefInfo{
    //long  bfInfo_OrdNumOut : 4;
    //long  bfInfo_OrdNumStng: 8;
    //long  bfInfo_IdLUStng  : 6;
    //long  bfInfo_BaseID    : 8;
    //long  bfInfo_OrdNumIn  : 5;
    SBitFld_LUInInfo sBitLUInputInfo;
    long  bfInfo_BaseID    : 8;
    long  bfInfo_OrdNumIn  : 5;
}SBitFldCRefInfo;







#endif
typedef struct tag_LUAreaListElem {
    short shIdLU;   // Type LU enum ID_LU
    short shSizeLU; // In bytes
    void* pvLU;     // Pointer on LU in Memory
    // For speeding calc Insert fields short shIdLUStng short shOrdNumStng
}LUAreaListElem;
/*
typedef struct tag_LULinksInfo{
	char shIdLU;  //Type LU enum ID_LU
	char chRes;
	short shRes;
	LUOutDsc[] arLUOutDsc
	
}LULinksInfo;
*/
typedef struct tag_AllocInfo{
	short shBF; // Bit Flags Fld 0-Need Move
    short shSize; //In bytes
    void* pvSrc; //Pointer on Area obj in Memory
    void* pvDsc; //Pointer on Area obj in Alloc Memory
	
}AllocInfo;

#define SIZE_LU_AREA_LIST_ITEM sizeof(LUAreaListElem)
/*
typedef union {
	char   chArRamPrgEvt [SIZE_MEM_BLK];
	long    lArRamPrgEvt [SIZE_MEM_BLK>>2];
	struct	{
		//LUAreaListElem area
		//free mem
		//LU data starting from the end of UNN_LU_AreaMap
	}
}UNN_LU_AreaMap;
*/
#define SIZE_MEM_BLK (1024*32)
typedef union 
{

    char chArRamPrgEvt [SIZE_MEM_BLK];
    long lArRamPrgEvt [SIZE_MEM_BLK >> 2];
    LUAreaListElem headLUAreaList;

    struct {
        //BmRamPrgEvtDsc hldrLUHeaderArea;
        //BrRamPrgEvtDsc hldrLUDataArea; 
        //BsRamPrgEvtDsc hldrLUTailArea;
    } RamvtFld;
    
}UNN_LogicUnitArea;


void ResetarNum(void);
extern  short shLssLUAreaListElemIndex; 
extern  const short arrShCalcLUOrderNumsSchmPage2[];
extern  const char  arrChCalcLUOrderNumsSchmPage2[];
extern  char chErrorState;



