#pragma once
#include "lubase.h"
const short shCLUFKey_x_y_AmtOut = 1;
const short shCLUFKey_x_y_AmtIn  = 0;

class CLUFKey :
public CLUBase {
public:
    CLUFKey(void);
    ~CLUFKey(void);
	CLUFKey(char chM,char chI) ;
    char arrOut [shCLUFKey_x_y_AmtOut];
    friend void FKey_Op(void *pObj);
};

extern void FKey_Op(void *pObj);

