#pragma once
#include "lubase.h"
const short shCLUTs_x_y_AmtOut = 1;
const short shCLUTs_x_y_AmtIn  = 2;

enum Ts__2_1_INPUT_NAMES{
Ts__2_1_IN_NAME__CI = 1,//Connection Input
Ts__2_1_IN_NAME__BLOCK,
Ts__2_1_IN_NAME__INF_REQ,//Addr Request Variable
TOTAL_Ts__2_1_IN = Ts__2_1_IN_NAME__INF_REQ
};

enum Ts__2_1_OUTPUT_NAMES{
Ts__2_1_OUT_NAME_CO = 1,//CO - means connection Out

TOTAL_Ts__2_1_OUTPUT = Ts__2_1_OUT_NAME_CO
};





class CLUTs :
public CLUBase {
public:
    CLUTs(void);
    ~CLUTs(void);
    CLUTs(char chM,char chI);
    void UpdateCLUTs(void);
    
    char* arrPchIn[TOTAL_Ts__2_1_IN];// 
	char  arrOut  [TOTAL_Ts__2_1_OUTPUT];//
//    char chError;
    char chQ;
    char chIn_C;
    friend void  Ts__2_1_Op  (void *pObj);
};
extern void Ts__2_1_Op  (void *pObj);
