#pragma once
const short shCLULed_1_0_AmtIn  = 1;
const short shCLULed_1_0_AmtOut = 0;
#include "lubase.h"
#include "LedAuxDsc.h"

//#ifndef I_PRT_TIMER_H
typedef struct LedSuit_tag{
char chSel1;//INDEX_CTRL_OUTPUT_LED_N_T);
char chSel2;//INDEX_CTRL_OUTPUT_LED_C_I);
char chSel3;//INDEX_CTRL_OUTPUT_LED_SI_EI
short shAlternatorC1;//Number
short shAlternatorC2;//Number
}LedCfgSuit;
//#endif


class CLULed :
	public CLUBase
{
public:
	CLULed(void);
	~CLULed(void);
	CLULed(CLULed&);
	CLULed(char chM,char chI);
	void CalcLedSchematic(void);
	char* arrPchIn[TOTAL_LED_VISIO_IN];//
	char* arrPchSchIn[shCLULed_1_0_AmtIn];//
//	char* arrPchAlternator[2];//
	char  arrOut  [TOTAL_LED_VISIO_OUTPUT];//Trash field
	LedCfgSuit m_LedCfgSuit;
	friend void PUT_Op_1_0_    (void *pObj);
	friend void SET_LED_Op(void *pObj);
	friend void ChangeLedCfgSuit(void *pObj);
};


//typedef long(*fnPvrL)(void *pv);
//enum G{
//
//}






