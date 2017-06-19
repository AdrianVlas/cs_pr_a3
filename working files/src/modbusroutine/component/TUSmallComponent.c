#include "header.h"

//начальный регистр в карте памяти
#define BEGIN_ADR_REGISTER 508
//начальный bit в карте памяти
#define BEGIN_ADR_BIT 21128
#define BIT_FOR_OBJ 1
//макс к-во обектов
#define TOTAL_OBJ 128
int privateTUSmallGetReg1(int adrReg);
int privateTUSmallGetReg2(int adrReg);
int privateTUSmallGetBit1(int adrBit);
int privateTUSmallGetBit2(int adrBit);

int getTUSmallModbusRegister(int);//получить содержимое регистра
int getTUSmallModbusBit(int);//получить содержимое бита
int setTUSmallModbusRegister(int, int);//получить содержимое регистра
int setTUSmallModbusBit(int, int);//получить содержимое бита

void setTUSmallCountObject(int);//записать к-во обектов
void preTUSmallReadAction(void);//action до чтения
void postTUSmallReadAction(void);//action после чтения
void preTUSmallWriteAction(void);//action до записи
void postTUSmallWriteAction(void);//action после записи
void loadTUSmallActualData(void);

COMPONENT_OBJ *tusmallcomponent;

/**************************************/
//подготовка компонента телеуправление
/**************************************/
void constructorTUSmallComponent(COMPONENT_OBJ *tusmallcomp)
{
  tusmallcomponent = tusmallcomp;

  tusmallcomponent->countObject = 0;//к-во обектов

  tusmallcomponent->getModbusRegister = getTUSmallModbusRegister;//получить содержимое регистра
  tusmallcomponent->getModbusBit      = getTUSmallModbusBit;//получить содержимое бита
  tusmallcomponent->setModbusRegister = setTUSmallModbusRegister;//получить содержимое регистра
  tusmallcomponent->setModbusBit      = setTUSmallModbusBit;//получить содержимое бита

  tusmallcomponent->setCountObject  = setTUSmallCountObject;//записать к-во обектов
  tusmallcomponent->preReadAction   = preTUSmallReadAction;//action до чтения
  tusmallcomponent->postReadAction  = postTUSmallReadAction;//action после чтения
  tusmallcomponent->preWriteAction  = preTUSmallWriteAction;//action до записи
  tusmallcomponent->postWriteAction = postTUSmallWriteAction;//action после записи

  tusmallcomponent->isActiveActualData = 0;
}//prepareDVinConfig

void loadTUSmallActualData(void) {
  //ActualData
  for(int i=0; i<100; i++) tempReadArray[i] = i;
}//loadActualData() 

int getTUSmallModbusRegister(int adrReg)
{
  //получить содержимое регистра
  if(privateTUSmallGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(privateTUSmallGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  if(tusmallcomponent->isActiveActualData) loadTUSmallActualData(); //ActualData
  tusmallcomponent->isActiveActualData = 0;

  superSetOperativMarker(tusmallcomponent, adrReg);

  return tempReadArray[adrReg-BEGIN_ADR_REGISTER];
}//getDVModbusRegister(int adrReg)
int getTUSmallModbusBit(int adrBit)
{
  //получить содержимое bit
  if(privateTUSmallGetBit2(adrBit)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(privateTUSmallGetBit1(adrBit)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  if(tusmallcomponent->isActiveActualData) loadTUSmallActualData();
  tusmallcomponent->isActiveActualData = 0;

  superSetOperativMarker(tusmallcomponent, adrBit);

  short tmp   = tempReadArray[(adrBit-BEGIN_ADR_BIT)/16];
  short maska = 1<<((adrBit-BEGIN_ADR_BIT)%16);
  if(tmp&maska) return 1;
  return 0;
}//getTUSmallModbusBit(int adrBit)
int setTUSmallModbusRegister(int adrReg, int x)
{
  UNUSED(x);
  //записать содержимое регистра
  superSetOperativMarker(tusmallcomponent, adrReg);
  return MARKER_OUTPERIMETR;
}//getDVModbusRegister(int adrReg)
int setTUSmallModbusBit(int adrBit, int x)
{
  UNUSED(x);
  //записать содержимое bit
  superSetOperativMarker(tusmallcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDVModbusRegister(int adrReg)

void setTUSmallCountObject(int cntObj) {
//записать к-во обектов
  if(cntObj<0) return;
  if(cntObj>=TOTAL_OBJ) return;
  tusmallcomponent->countObject = cntObj;
}//
void preTUSmallReadAction(void) {
//action до чтения
  tusmallcomponent->operativMarker[0] = -1;
  tusmallcomponent->operativMarker[1] = -1;//оперативный маркер
  tusmallcomponent->isActiveActualData = 1;
}//
void postTUSmallReadAction(void) {
//action после чтения
  if(tusmallcomponent->operativMarker[0]<0) return;//не было чтения
}//
void preTUSmallWriteAction(void) {
//action до записи
  tusmallcomponent->operativMarker[0] = -1;
  tusmallcomponent->operativMarker[1] = -1;//оперативный маркер
  tusmallcomponent->isActiveActualData = 1;
}//
void postTUSmallWriteAction(void) {
//action после записи
}//

int privateTUSmallGetReg1(int adrReg)
{
  //проверить внутренний периметр
  int count_register = tusmallcomponent->countObject/16;
  if(tusmallcomponent->countObject%16) count_register++;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg1(int adrReg)

int privateTUSmallGetReg2(int adrReg)
{
  //проверить внешний периметр
  int count_register = TOTAL_OBJ/16;
  if(TOTAL_OBJ%16) count_register++;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)

int privateTUSmallGetBit1(int adrBit)
{
  //проверить внутренний периметр
  int count_bit = BIT_FOR_OBJ*tusmallcomponent->countObject;
  if(adrBit>=BEGIN_ADR_BIT && adrBit<(BEGIN_ADR_BIT+count_bit)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg1(int adrReg)

int privateTUSmallGetBit2(int adrBit)
{
  //проверить внешний периметр
  int count_bit = BIT_FOR_OBJ*TOTAL_OBJ;
  if(adrBit>=BEGIN_ADR_BIT && adrBit<(BEGIN_ADR_BIT+count_bit)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
