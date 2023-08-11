#pragma once
#include "lubase.h"
#include "prtTmr.hpp"

#include "LssAuxDsc.h"
typedef struct LssCfgSuit_tag{
char chSel;
long lTCs;
}LssCfgSuit;
const short shCLULss_x_y_AmtOut = 1;
const short shCLULss_x_y_AmtIn  = 0;

class CLULss :
public CLUBase {
public:
    CLULss(void);
    ~CLULss(void);
    CLULss(char chM,char chI);
    void CalcLssSchematic(void);
    void CalcLssSchematicOpt(void);
    void CalcLssSchematicOpt3(void);
    void CalcLssSchematicOptManual(void);
    char* arrPchIn[TOTAL_LSS_IN];
    char  arrOut  [TOTAL_LSS_OUTPUT];//Trash field
    LssCfgSuit m_LssCfgSuit;
    TmrNode m_Node1_1Ms;
    TmrNode m_Node1_2Ms;
    TmrNode m_Node1_3Ms;
    TmrNode m_Node4_2Ms;
    TmrNode m_NodeCs;
    char m_chLinkedTimers; //Field bit
    char m_chStateT1_1Ms;
    char m_chStateT1_2Ms;
    char m_chStateT1_3Ms;
    char m_chStateT4_2Ms;//Timer 4 on 2 ms
    char m_chStateTCs;
    char m_chQTrg29;
    char m_chQTrg11;
    char m_chErrorQTrg29;
    char m_chInC29;
    char m_chInC11;
    char m_chErrorQTrg11;
    short m_shAmountProcessedRec;
    short m_shStartRecord;
     LedShcemasDscRecord** m_pArLssShcemasDscRecords;//PConst
    long T1_1Ms(long lActivKey);
    long T1_2Ms(long lActivKey);
    long T1_3Ms(long lActivKey);
    long T4_2Ms(long lActivKey);
    long TCs(long lActivKey);
//	void inline SetStateTrg(long lIdTrg, void* pvState);
//	void inline ClrStateTrg(long lIdTrg, void* pvState);
    inline void SetStateVarchQTrg(long lIdTrg, char&chQTrg);
    inline void SetStateVarchInC (long lIdTrg, char&chInC);
    inline void SetStateVarchErrorQTrg(long lIdTrg, char&chErrorQTrg);
    inline long GetStateVarchQTrg(long lIdTrg);
    inline long GetStateVarchErrorQTrg(long lIdTrg);
    inline long GetStateVarchInC (long lIdTrg);
    inline void SetTrg(long lIdTrg);
    inline void ClrTrg(long lIdTrg);
    void UpdateCLss(void);
    long LinkLssTimers(void);
    friend void LssOp (void *pObj);
};

extern void LssOp (void *pObj);

extern const LedShcemasDscRecord* const arPLssShcemasSimpleModeDscRecords[];
extern const short shPLssShcemasSimpleModeDscRecords;
extern const LedShcemasDscRecord* const arPLssShcemasTriggerModeDscRecords[];
extern const short shPLssShcemasTriggerModeDscRecords;
