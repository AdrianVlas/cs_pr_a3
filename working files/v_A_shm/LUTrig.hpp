#pragma once
#include "lubase.h"
const short shCLUTrig_x_y_AmtIn  = 4;
const short shCLUTrig_x_y_AmtOut = 2;

enum DTRG__4_2_INPUT_NAMES{
DTRG__4_2_IN_NAME__SET = 1,
DTRG__4_2_IN_NAME__CLR      ,
DTRG__4_2_IN_NAME__D,
DTRG__4_2_IN_NAME__C_SLASH    ,
TOTAL_DTRG__4_2_IN = DTRG__4_2_IN_NAME__C_SLASH
};

enum DTRG__4_2_OUTPUT_NAMES{
DTRG__4_2_OUT_NAME_Q = 1,
DTRG__4_2_OUT_NAME_Q_INV,
TOTAL_DTRG__4_2_OUTPUT = DTRG__4_2_OUT_NAME_Q_INV
};



class CLUTrig :
public CLUBase {
public:
    CLUTrig(void);
    ~CLUTrig(void);
	CLUTrig(char chM,char chI);
    void UpdateCLUTrig(void);
	char* arrPchIn[shCLUTrig_x_y_AmtIn];// 
	char  arrOut  [shCLUTrig_x_y_AmtOut];//
    char chError;
    char chQ;
    char chIn_C;
  
	friend void DTRG_Op_4_2    (void *pObj);
};

extern void DTRG_Op_4_2    (void *pObj);


