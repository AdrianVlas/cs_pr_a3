#pragma once
#include "lubase.h"
const short shCLULog_x_y_AmtOut = 1;
const short shCLULog_x_y_AmtIn  = 0;

enum LOG__0_1_INPUT_NAMES{
LOG__0_1_IN_NAME__INF_REQ,//Addr Request Variable
TOTAL_LOG__0_1_IN = LOG__0_1_IN_NAME__INF_REQ
};
enum LOG__0_1_OUTPUT_NAMES{
LOG__0_1_OUT_NAME_CO = 1,//CO - means connection Out

TOTAL_LOG__0_1_OUTPUT = LOG__0_1_OUT_NAME_CO
};


class CLULog :
public CLUBase {
public:
    CLULog(void);
    ~CLULog(void);
    CLULog(char chM,char chI);
    void UpdateCLULog(void);
    char  arrOut  [shCLULog_x_y_AmtOut];
    	
    friend void Log_Op(void *pObj);
};
extern void Log_Op(void *pObj);



