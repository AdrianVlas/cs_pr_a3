#pragma once
#include "lubase.h"
const short shCLUDout_1_0_AmtIn  = 1;
const short shCLUDout_1_0_AmtOut = 0;
#include "DOAuxDsc.h"
typedef struct ReleySuit_tag{
char chSel1;
char chSel2;
char chSel3;
short shAlternatorC1;//Number
short shAlternatorC2;//Number
}ReleyCfgSuit;

class CLUDout_1_0 :
public CLUBase {
public:
    CLUDout_1_0(void);
    ~CLUDout_1_0(void);
    CLUDout_1_0(CLUDout_1_0&);
    CLUDout_1_0(char chM, char chI);
	void CalcReleySchematic(void);
    void UpdateCLUDout_1_0(void);
    char* arrPchIn[TOTAL_RELE_VISIO_IN]; //
    char* arrPchSchIn[shCLUDout_1_0_AmtIn];//
    char  arrStateIn[TOTAL_RELE_VISIO_IN ];
    char m_chQTrg06;
    char m_chInC06;
	char m_chErrorQTrg06;
	char  arrOut  [TOTAL_RELE_VISIO_OUTPUT];//Trash field
    short m_shAmountProcessedRec;
    short m_shStartRecord;
    LedShcemasDscRecord** m_pArShcemasDscRecords;//PConst
	ReleyCfgSuit m_ReleyCfgSuit;
    friend void PUT_Op_1_0(void *pObj);
    friend void SET_OUT_Op(void *pObj);
};
void UpdateOutDiagn(void);
extern const LedShcemasDscRecord* const arPReleShcemasDscRecords[];
extern const LedShcemasDscRecord* const arPDOShcemasStableDirectDscRecords[]; 
extern const LedShcemasDscRecord* const arPDOShcemasStableTriggerDscRecords[]; 
extern const LedShcemasDscRecord* const arPDOShcemasPulseC1SimpleDscRecords[]; 
extern const LedShcemasDscRecord* const arPDOShcemasPulseC1TrigDscRecords[]; 
extern const LedShcemasDscRecord* const arPDOShcemasPulseC2TrigDscRecords[]; 

extern const short shAmtDOShcemasDscRecords;
extern const short shAmtDOShcemasStableSimpleDscRecords;
extern const short shAmtDOShcemasStableTriggerDscRecords;
extern const short shAmtDOShcemasPulseC1SimpleModeDscRecords;
extern const short shAmtDOShcemasPulseC1TrigModeDscRecords;
extern const short shAmtDOShcemasPulseC2TrigModeDscRecords;

extern const short shAmtDOShcemasPulseC2SimpleModeDscRecords;
extern const LedShcemasDscRecord* const arPDOShcemasPulseC2SimpleDscRecords[];

