
#include "CLUTs.hpp"
char chGBL_BP_StopLUTs = 0;
void Ts__2_1_Op  (void *pObj){
CLUTs& rCLUTs = *(static_cast<CLUTs *> (pObj));
    long k, j, l; //
    k = 0;
    if(chGBL_BP_StopLUTs == rCLUTs.shShemasOrdNumStng)
    asm(
    "bkpt 1"
    );  
    j = *(rCLUTs.arrPchIn[Ts__2_1_IN_NAME__CI-1]);
    l = *(rCLUTs.arrPchIn[Ts__2_1_IN_NAME__BLOCK-1]);
    if((j > 0)&&(l == 0))
    k |= 1;
    
    if(k == 0) {
        l = *(rCLUTs.arrPchIn[Ts__2_1_IN_NAME__INF_REQ-1]);//???
        if(rCLUTs.chIn_C == 0 && l > 0){
        //reset Ts
            rCLUTs.chQ = 0;
        }
    }else
        if (k == 1){ 
        rCLUTs.chQ = 1;
        j = k;
        }
    rCLUTs.chIn_C = l;
    rCLUTs.arrOut[Ts__2_1_OUT_NAME_CO-1] = j;
    //Additional Operation for Comm Req 
    
}
CLUTs::CLUTs(void) {
}

CLUTs::~CLUTs(void) {
}

CLUTs::CLUTs(char chM,char chI) {
register long i;
    chMaxIteratoin = chM;
    chIteration = chI;
    chNumInput  = static_cast<char> (TOTAL_Ts__2_1_IN);//shCLUTs_x_y_AmtIn
    chNumOutput = static_cast<char> (TOTAL_Ts__2_1_OUTPUT);//shCLUTs_x_y_AmtOut
    chTypeLogicFunction = LU_OP_NOT;
    LogicFunc = Ts__2_1_Op; //
    for (i = 0; i < chNumInput; i++)
        arrPchIn[i] = reinterpret_cast<char*> (0xcccccccc); //&chGblGround;
    for (i = 0; i < chNumOutput; i++)
        arrOut[i] = 0;
    //chError = 0; 
    chQ = chIn_C = 0;
    
}
void CLUTs::UpdateCLUTs(void){
//Set Input parameters
pIn = static_cast<void*>(arrPchIn);
//Set OutPut parameters
pOut = static_cast<void*>(arrOut);

}

