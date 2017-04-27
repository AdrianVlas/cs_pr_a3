
#include "LUTu.h"

CLUTu::CLUTu(void) {
}

CLUTu::~CLUTu(void) {
}
CLUTu::CLUTu(char chM,char chI) {
	chMaxIteratoin = chM;
	chIteration = chI;
    chNumOutput = static_cast<char>(shCLUTU_x_y_AmtOut);
	for (long i = 0; i < chNumOutput; i++)
        arrOut[i] = 0;
}
void TU_Op(void *pObj){
long i;
	CLUTu *pCLUTu = static_cast<CLUTu*>(pObj);
//find Index
i = pCLUTu->shShemasOrdNumStng;
    i--;
    //Look State
}




