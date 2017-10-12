#ifndef I_SCHEMATIC_H
#define I_SCHEMATIC_H

#ifndef LU_CFG_INFO
#define LU_CFG_INFO
typedef struct LUCfgInfo_tag{
void* pvLUClass;
void* pvCfgSuit;
void* pvChangeSuitFn;

}LUCfgInfo;


#endif

typedef struct TIM3_InitInfo_tag{
unsigned short shARR;
unsigned short shPSC;
unsigned short shRes;

}TIM3InitInfo;



#ifdef __cplusplus
extern "C" {
#endif

long ChangeCfgLULed(void* pv);

extern void  TmrCalls(void);
extern  void TIM3ReInit(void* pv);

#ifdef __cplusplus
}
#endif
extern long CreateSchematic(void);
extern long InitSchematic(void);
extern long ReInitSchematic(void);

extern void DoCalcWrp(void);
extern void DoCalcStatInfoWrp(void);
extern void  TmrCalls(void);
extern long RegisterHundlerLUCfg(void* pv);

extern void  CheckingDIRegs(void);

extern char chGlb_ActivatorWREeprom;
extern const long TIM9_BASE_CPP;

#endif
