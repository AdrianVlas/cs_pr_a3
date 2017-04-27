#pragma once
#include "lubase.h"
const short shCLUTU_x_y_AmtOut = 1;
const short shCLUTU_x_y_AmtIn  = 0;

class CLUTu :
public CLUBase {
public:
    CLUTu(void);
    ~CLUTu(void);
	CLUTu(char chM,char chI);
    char arrOut [shCLUTU_x_y_AmtOut];
    friend void TU_Op(void *pObj);
};
extern void TU_Op(void *pObj);


