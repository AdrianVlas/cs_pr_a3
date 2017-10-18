#pragma once
#include "lubase.h"
const short shCLUTimer_x_y_AmtOut = 1;
const short shCLUTimer_x_y_AmtIn  = 0;

#include "prtTmr.hpp"
#include "FixBlAux.h"
#include <stdint.h>

#include "../inc/const_measurement.h"
#include "../inc/const_global.h"


const long l_0D80_UNOM = 176000;
const long l_0D80_UNOM_X_1D1 = 194000;

const long l_1D15_UNOM = 253000;
const long l_1D15_UNOM_X_0D9 = 228000;








class CFixBlockWrp :
public CLUBase {
public:
    CFixBlockWrp(void);
    CFixBlockWrp(char chM,char chI);
    ~CFixBlockWrp(void);
    char* arrPchIn[TOTAL_FIX_BLOCK_IN]; //
    char arrOut   [TOTAL_FIX_BLOCK_CMD]; 
    void EvalCFixBlockWrpCmd(void);
    friend void FBWrp_Op(void *pObj);
};
    


extern void FBWrp_Op(void *pObj);
