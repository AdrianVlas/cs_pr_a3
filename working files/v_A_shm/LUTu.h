#pragma once
#include "lubase.h"
const short shCLUTU_x_y_AmtOut = 1;
const short shCLUTU_x_y_AmtIn  = 1;

enum TU__1_1_INPUT_NAMES{
TU__1_1_IN_NAME__CI = 1,//Connection Input
TU__1_1_IN_NAME__BLOCK,
TU__1_1_IN_NAME__INF_REQ,//Addr Request Variable
TOTAL_TU__1_1_IN = TU__1_1_IN_NAME__INF_REQ
};

enum TU__1_1_OUTPUT_NAMES{
TU__1_1_OUT_NAME_CO = 1,//CO - means connection Out

TOTAL_TU__1_1_OUTPUT = TU__1_1_OUT_NAME_CO
};

class CLUTu :
public CLUBase {
public:
    CLUTu(void);
    ~CLUTu(void);
	CLUTu(char chM,char chI);
    void UpdateCLUTu(void);
    char  arrOut  [shCLUTU_x_y_AmtOut];
    char* arrPchIn[TOTAL_TU__1_1_IN];// 
	
    friend void TU_Op(void *pObj);
};
extern void TU_Op(void *pObj);


