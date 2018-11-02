
#include "LUTrig.hpp"
#include "IStng.h"

char chGBL_BP_StopLUTrig = 0;
void DTRG_Op_4_2(void *pObj) {
register    CLUTrig& refCLUDTrg = *(static_cast<CLUTrig *> (pObj));
register    long k, j, l; //
    //char *pCh;
    bool bbl = refCLUDTrg.chQ;
    k = 0;
    if(chGBL_BP_StopLUTrig == refCLUDTrg.shShemasOrdNumStng)
    asm volatile(
                "bkpt 1"
                );
//pCh = refCLUDTrg.arrPchIn[DTRG__4_2_IN_NAME__SET - 1];
    if (*(refCLUDTrg.arrPchIn[DTRG__4_2_IN_NAME__SET - 1])) //{
        k |= 1; //} 

    //pCh = refCLUDTrg.arrPchIn[DTRG__4_2_IN_NAME__CLR - 1];
    if (*(refCLUDTrg.arrPchIn[DTRG__4_2_IN_NAME__CLR - 1]))//{
        k |= 2; //}
    

    if (k == 0) {
    l = *(refCLUDTrg.arrPchIn[DTRG__4_2_IN_NAME__C_SLASH - 1]);
        if (refCLUDTrg.chIn_C == 0 && l > 0) {
        j = *(refCLUDTrg.arrPchIn[DTRG__4_2_IN_NAME__D - 1]);
            if ( j) {
                //set
                //refCLUDTrg.arrOut[DTRG__4_2_OUT_NAME_Q - 1] = 1;
                //refCLUDTrg.arrOut[DTRG__4_2_OUT_NAME_Q_INV - 1] = 0;
                refCLUDTrg.chQ = 1;
            }
            else{
                ;
                //refCLUDTrg.arrOut[DTRG__4_2_OUT_NAME_Q - 1] = 0;
                //refCLUDTrg.arrOut[DTRG__4_2_OUT_NAME_Q_INV - 1] = 1;
                refCLUDTrg.chQ = 0;
            }
        }
    } else
        if (k == 1) {
        refCLUDTrg.chQ = 1;
        
        //refCLUDTrg.arrOut[DTRG__4_2_OUT_NAME_Q - 1] = 1;
        //refCLUDTrg.arrOut[DTRG__4_2_OUT_NAME_Q_INV - 1] = 0;
    } else
        if (k == 2) {
        refCLUDTrg.chQ = 0;
        
        //refCLUDTrg.arrOut[DTRG__4_2_OUT_NAME_Q - 1] = 0;
        //refCLUDTrg.arrOut[DTRG__4_2_OUT_NAME_Q_INV - 1] = 1;
        
    } else if (k == 3) {
        refCLUDTrg.chError = 1;
        
    }
refCLUDTrg.chIn_C = *(refCLUDTrg.arrPchIn[DTRG__4_2_IN_NAME__C_SLASH - 1]);
l = refCLUDTrg.chQ ;
refCLUDTrg.arrOut[DTRG__4_2_OUT_NAME_Q - 1] = l;
refCLUDTrg.arrOut[DTRG__4_2_OUT_NAME_Q_INV - 1] = !l;//refCLUDTrg.chQ ;

__LN_TRIGGER *pLN_TRIGGER = reinterpret_cast<__LN_TRIGGER *>(refCLUDTrg.pvCfgLN);
pLN_TRIGGER->active_state   [(TRIGGER_OUT/8) ] = (static_cast<bool>(l))<<(TRIGGER_OUT%8);
if(bbl != static_cast<bool>(l) ){
    pLN_TRIGGER->d_trigger_state[TRIGGER_D_TRIGGER_1/8] = (static_cast<bool>(l))<<(TRIGGER_D_TRIGGER_1%8);
    chGlb_ActivatorWREeprom++;
}

}

CLUTrig::CLUTrig(void) {
}

CLUTrig::~CLUTrig(void) {
}
CLUTrig::CLUTrig(char chM,char chI) {
register long i;
    chMaxIteratoin = chM;
    chIteration = chI;
    chNumInput = static_cast<char> (shCLUTrig_x_y_AmtIn);
    chNumOutput = static_cast<char> (shCLUTrig_x_y_AmtOut);
    chTypeLogicFunction = LU_OP_NOT;
    LogicFunc = DTRG_Op_4_2; //
    for (i = 0; i < chNumInput; i++)
        arrPchIn[i] = reinterpret_cast<char*> (0xcccccccc); //&chGblGround;
    for (i = 0; i < chNumOutput; i++)
        arrOut[i] = 0;
    chError = 0; 
    chQ = chIn_C = 0;
}
void CLUTrig::UpdateCLUTrig(void){
//Set Input parameters
pIn = static_cast<void*>(arrPchIn);
//Set OutPut parameters
pOut = static_cast<void*>(arrOut);

}

