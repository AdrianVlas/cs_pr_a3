#include "header.h"

//начальный регистр в карте памяти
#define BEGIN_ADR_REGISTER 500
//начальный bit в карте памяти
#define BEGIN_ADR_BIT 21000
#define BIT_FOR_OBJ 1
//макс к-во обектов
#define TOTAL_OBJ 128
int privateTSSmallGetReg1(int adrReg);
int privateTSSmallGetReg2(int adrReg);
int privateTSSmallGetBit1(int adrBit);
int privateTSSmallGetBit2(int adrBit);

int getTSSmallModbusRegister(int);//получить содержимое регистра
int getTSSmallModbusBit(int);//получить содержимое бита
int setTSSmallModbusRegister(int, int);//получить содержимое регистра
int setTSSmallModbusBit(int, int);//получить содержимое бита

void setTSSmallCountObject(int);//записать к-во обектов
void preTSSmallReadAction(void);//action до чтения
void postTSSmallReadAction(void);//action после чтения
void preTSSmallWriteAction(void);//action до записи
void postTSSmallWriteAction(void);//action после записи
void loadTSSmallActualData(void);

COMPONENT_OBJ *tssmallcomponent;

/**************************************/
//подготовка компонента телесигнализации
/**************************************/
void constructorTSSmallComponent(COMPONENT_OBJ *tssmallcomp)
{
  tssmallcomponent = tssmallcomp;

  tssmallcomponent->countObject = 0;//к-во обектов

  tssmallcomponent->getModbusRegister = getTSSmallModbusRegister;//получить содержимое регистра
  tssmallcomponent->getModbusBit      = getTSSmallModbusBit;//получить содержимое бита
  tssmallcomponent->setModbusRegister = setTSSmallModbusRegister;//получить содержимое регистра
  tssmallcomponent->setModbusBit      = setTSSmallModbusBit;//получить содержимое бита

  tssmallcomponent->setCountObject  = setTSSmallCountObject;//записать к-во обектов
  tssmallcomponent->preReadAction   = preTSSmallReadAction;//action до чтения
  tssmallcomponent->postReadAction  = postTSSmallReadAction;//action после чтения
  tssmallcomponent->preWriteAction  = preTSSmallWriteAction;//action до записи
  tssmallcomponent->postWriteAction = postTSSmallWriteAction;//action после записи

  tssmallcomponent->isActiveActualData = 0;
}//prepareDVinConfig

void loadTSSmallActualData(void) {
  //ActualData
  for(int i=0; i<100; i++) tempReadArray[i] = i;
}//loadActualData() 

int getTSSmallModbusRegister(int adrReg)
{
  //получить содержимое регистра
  if(privateTSSmallGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(privateTSSmallGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  if(tssmallcomponent->isActiveActualData) loadTSSmallActualData(); //ActualData
  tssmallcomponent->isActiveActualData = 0;

  superSetOperativMarker(tssmallcomponent, adrReg);

  return tempReadArray[adrReg-BEGIN_ADR_REGISTER];
}//getDVModbusRegister(int adrReg)
int getTSSmallModbusBit(int adrBit)
{
  //получить содержимое bit
  if(privateTSSmallGetBit2(adrBit)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(privateTSSmallGetBit1(adrBit)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  if(tssmallcomponent->isActiveActualData) loadTSSmallActualData();
  tssmallcomponent->isActiveActualData = 0;

  superSetOperativMarker(tssmallcomponent, adrBit);

  short tmp   = tempReadArray[(adrBit-BEGIN_ADR_BIT)/16];
  short maska = 1<<((adrBit-BEGIN_ADR_BIT)%16);
  if(tmp&maska) return 1;
  return 0;
}//getDVModbusRegister(int adrReg)
int setTSSmallModbusRegister(int adrReg, int x)
{
  UNUSED(x);
  //записать содержимое регистра
  superSetOperativMarker(tssmallcomponent, adrReg);
  return MARKER_OUTPERIMETR;
}//getDVModbusRegister(int adrReg)
int setTSSmallModbusBit(int adrBit, int x)
{
  UNUSED(x);
  //записать содержимое bit
  superSetOperativMarker(tssmallcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDVModbusRegister(int adrReg)

void setTSSmallCountObject(int cntObj) {
//записать к-во обектов
  if(cntObj<0) return;
  if(cntObj>=TOTAL_OBJ) return;
  tssmallcomponent->countObject = cntObj;
}//
void preTSSmallReadAction(void) {
//action до чтения
  tssmallcomponent->operativMarker[0] = -1;
  tssmallcomponent->operativMarker[1] = -1;//оперативный маркер
  tssmallcomponent->isActiveActualData = 1;
}//
void postTSSmallReadAction(void) {
//action после чтения
  if(tssmallcomponent->operativMarker[0]<0) return;//не было чтения
}//
void preTSSmallWriteAction(void) {
//action до записи
  tssmallcomponent->operativMarker[0] = -1;
  tssmallcomponent->operativMarker[1] = -1;//оперативный маркер
  tssmallcomponent->isActiveActualData = 1;
}//
void postTSSmallWriteAction(void) {
//action после записи
}//

int privateTSSmallGetReg1(int adrReg)
{
  //проверить внутренний периметр
  int count_register = tssmallcomponent->countObject/16;
  if(tssmallcomponent->countObject%16) count_register++;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg1(int adrReg)

int privateTSSmallGetReg2(int adrReg)
{
  //проверить внешний периметр
  int count_register = TOTAL_OBJ/16;
  if(TOTAL_OBJ%16) count_register++;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)

int privateTSSmallGetBit1(int adrBit)
{
  //проверить внутренний периметр
  int count_bit = BIT_FOR_OBJ*tssmallcomponent->countObject;
  if(adrBit>=BEGIN_ADR_BIT && adrBit<(BEGIN_ADR_BIT+count_bit)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg1(int adrReg)

int privateTSSmallGetBit2(int adrBit)
{
  //проверить внешний периметр
  int count_bit = BIT_FOR_OBJ*TOTAL_OBJ;
  if(adrBit>=BEGIN_ADR_BIT && adrBit<(BEGIN_ADR_BIT+count_bit)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
