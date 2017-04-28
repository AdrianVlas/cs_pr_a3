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




#ifdef __cplusplus
extern "C" {
#endif

long ChangeCfgLULed(void* pv);

extern void  TmrCalls(void);
#ifdef __cplusplus
}
#endif
extern long CreateSchematic(void);
extern long InitSchematic(void);
extern long ReInitSchematic(void);

extern void DoCalcWrp(void);
extern void  TmrCalls(void);
extern long RegisterHundlerLUCfg(void* pv);

#endif
