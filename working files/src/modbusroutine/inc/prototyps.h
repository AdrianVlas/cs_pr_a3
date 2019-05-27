#ifndef __PROTOTYPS_H
#define __PROTOTYPS_H

void global_component_installation(void);
int  superReader20(int);
int  superReader20Pro(int);
int  superReaderRegister(int);
int  superWriterRegister(int, int);
int  superReaderBit(int);
int  superWriterBit(int, int);
void superPreReadAction(void);
void superPostReadAction(void);
void superPreWriteAction(void);
int  superPostWriteAction(void);
void superConfig_and_settings(void);
void superSetOperativMarker(COMPONENT_OBJ *component, int adrReg);
void superSetTempWriteArray(int dataReg);
int  superFindTempWriteArrayOffset(int adr);
int finderMinimum(unsigned int data, int size, unsigned int *arr);
void finderDubl(int idx, int size, unsigned int *arr);
void superSortParam(int size, unsigned int *param);
int superControlParam(int param);
int superControlParam_gi(int param);
int superValidParam(unsigned int param);

void constructorYustBigComponent(COMPONENT_OBJ *);
void constructorDVBigComponent(COMPONENT_OBJ *);
void constructorDVSmallComponent(COMPONENT_OBJ *);
void constructorDOUTSmallComponent(COMPONENT_OBJ *);
void constructorDOUTBigComponent(COMPONENT_OBJ *);
void constructorSDISmallComponent(COMPONENT_OBJ *);
void constructorSDIBigComponent(COMPONENT_OBJ *);
void constructorRMTKeySmallComponent(COMPONENT_OBJ *);
void constructorConfigBigComponent(COMPONENT_OBJ *);
void constructorGIBigComponent(COMPONENT_OBJ *);
void constructorSZSBigComponent(COMPONENT_OBJ *);
void constructorCGSBigComponent(COMPONENT_OBJ *);
void constructorMFTBigComponent(COMPONENT_OBJ *);
void constructorDTRBigComponent(COMPONENT_OBJ *);
void constructorTSSmallComponent(COMPONENT_OBJ *);
void constructorTSBigComponent(COMPONENT_OBJ *);
void constructorTUSmallComponent(COMPONENT_OBJ *);
void constructorTUBigComponent(COMPONENT_OBJ *);
void constructorT1SmallComponent(COMPONENT_OBJ *);
void constructorT2SmallComponent(COMPONENT_OBJ *);
void constructorANDBigComponent(COMPONENT_OBJ *);
void constructorORBigComponent(COMPONENT_OBJ *);
void constructorXORBigComponent(COMPONENT_OBJ *);
void constructorNOTBigComponent(COMPONENT_OBJ *);
void constructorCommonSmallComponent(COMPONENT_OBJ *);
void constructorCommonBigComponent(COMPONENT_OBJ *);
void constructorMEBigComponent(COMPONENT_OBJ *);
void constructorRegProBigComponent(COMPONENT_OBJ *);
void constructorRPRBigComponent(COMPONENT_OBJ *);
void constructorRPRSmallComponent(COMPONENT_OBJ *);
void constructorKEYSmallComponent(COMPONENT_OBJ *);
void constructorAISmallComponent(COMPONENT_OBJ *);
void constructorPKVBigComponent(COMPONENT_OBJ *);
void constructorIUSmallComponent(COMPONENT_OBJ *);
void constructorOLANBigComponent(COMPONENT_OBJ *);
void constructorIMMSBigComponent(COMPONENT_OBJ *);
void constructorIGOOSEBigComponent(COMPONENT_OBJ *);

#endif
