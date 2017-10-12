#pragma once
//#include "lubase.h"
//const short shCLUTimer_x_y_AmtOut = 1;
//const short shCLUTimer_x_y_AmtIn  = 0;
#ifndef LU_EXEC_INFO
#define LU_EXEC_INFO
typedef struct LUExecInfo_tag{
//char  chCurrentIteration; 
short shTIMStartedVal;
short shTIMTerminatedVal;

}LUExecInfoDsc;


#endif


#define SIZE_LU_EXEC_INFO sizeof( LUExecInfoDsc )

typedef union{

    char   chArRamPrgEvt [SIZE_LU_EXEC_INFO];
    long    lArRamPrgEvt [SIZE_LU_EXEC_INFO>>2];

    struct{
        LUExecInfoDsc hldrLUExecInfo ;
        
        
    };
    
}UNN_LUExecRec;
#define MAX_AMOUNT_ITERATION 7
typedef union{

//    char   chArRamPrgEvt [SIZE_LU_EXEC_INFO];
//    long    lArRamPrgEvt [SIZE_LU_EXEC_INFO>>2];

    struct{
        UNN_LUExecRec arLUExecInfo[MAX_AMOUNT_ITERATION] ;
        char chStateExec;
        
    };
    
}UNN_LUStatInfoData;






//friend class CLUBase;
class CStatInfoStore 
 {
public:
    CStatInfoStore(void);
    ~CStatInfoStore(void);
    char m_chStateInfoStore;
//    char m_AmtRegisteredLU;
    
    
};
extern CStatInfoStore hldrCStatInfoStore;
