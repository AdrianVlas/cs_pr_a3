#include "header.h"

//начальный регистр в карте памяти
#define BEGIN_ADR_REGISTER 408
//начальный bit в карте памяти
#define BEGIN_ADR_BIT 20128
#define REGISTER_FOR_OBJ 1
#define BIT_FOR_OBJ 2

int privateSDI2ColorSmallGetReg2(int adrReg);
int privateSDI2ColorSmallGetBit2(int adrReg);

int getSDI2ColorSmallModbusRegister(int);//получить содержимое регистра
int getSDI2ColorSmallModbusBit(int);//получить содержимое бита
int setSDI2ColorSmallModbusRegister(int, int);//получить содержимое регистра
int setSDI2ColorSmallModbusBit(int, int);//получить содержимое бита

void setSDI2ColorSmallCountObject(int);//записать к-во обектов
void preSDI2ColorSmallReadAction(void);//action до чтения
void postSDI2ColorSmallReadAction(void);//action после чтения
void preSDI2ColorSmallWriteAction(void);//action до записи
void postSDI2ColorSmallWriteAction(void);//action после записи
void loadSDI2ColorSmallActualData(void);

COMPONENT_OBJ *sdi2colorsmallcomponent;

/**************************************/
//подготовка компонента светоиндикаторов 2 цвета
/**************************************/
void constructorSDI2ColorSmallComponent(COMPONENT_OBJ *sdi2colorsmallcomp)
{
  sdi2colorsmallcomponent = sdi2colorsmallcomp;

  sdi2colorsmallcomponent->countObject = 3;//к-во обектов

  sdi2colorsmallcomponent->getModbusRegister = getSDI2ColorSmallModbusRegister;//получить содержимое регистра
  sdi2colorsmallcomponent->getModbusBit      = getSDI2ColorSmallModbusBit;//получить содержимое бита
  sdi2colorsmallcomponent->setModbusRegister = setSDI2ColorSmallModbusRegister;//получить содержимое регистра
  sdi2colorsmallcomponent->setModbusBit      = setSDI2ColorSmallModbusBit;//получить содержимое бита

  sdi2colorsmallcomponent->setCountObject  = setSDI2ColorSmallCountObject;//записать к-во обектов
  sdi2colorsmallcomponent->preReadAction   = preSDI2ColorSmallReadAction;//action до чтения
  sdi2colorsmallcomponent->postReadAction  = postSDI2ColorSmallReadAction;//action после чтения
  sdi2colorsmallcomponent->preWriteAction  = preSDI2ColorSmallWriteAction;//action до записи
  sdi2colorsmallcomponent->postWriteAction = postSDI2ColorSmallWriteAction;//action после записи

  sdi2colorsmallcomponent->isActiveActualData = 0;
}//prepareDVinConfig

void loadSDI2ColorSmallActualData(void) {
  //ActualData
  for(int i=0; i<100; i++) tempReadArray[i] = i;
}//loadActualData() 

int getSDI2ColorSmallModbusRegister(int adrReg)
{
  //получить содержимое регистра
  if(privateSDI2ColorSmallGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  if(sdi2colorsmallcomponent->isActiveActualData) loadSDI2ColorSmallActualData(); //ActualData
  sdi2colorsmallcomponent->isActiveActualData = 0;

  superSetOperativMarker(sdi2colorsmallcomponent, adrReg);

  return tempReadArray[adrReg-BEGIN_ADR_REGISTER];
}//getDVModbusRegister(int adrReg)
int getSDI2ColorSmallModbusBit(int adrBit)
{
  //получить содержимое bit
  if(privateSDI2ColorSmallGetBit2(adrBit)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  if(sdi2colorsmallcomponent->isActiveActualData) loadSDI2ColorSmallActualData();
  sdi2colorsmallcomponent->isActiveActualData = 0;

  superSetOperativMarker(sdi2colorsmallcomponent, adrBit);

  short tmp   = tempReadArray[(adrBit-BEGIN_ADR_BIT)/16];
  short maska = 1<<((adrBit-BEGIN_ADR_BIT)%16);
  if(tmp&maska) return 1;
  return 0;
}//getDVModbusRegister(int adrReg)
int setSDI2ColorSmallModbusRegister(int adrReg, int x)
{
  UNUSED(x);
  //записать содержимое регистра
  superSetOperativMarker(sdi2colorsmallcomponent, adrReg);
  return MARKER_OUTPERIMETR;
}//getDVModbusRegister(int adrReg)
int setSDI2ColorSmallModbusBit(int adrBit, int x)
{
  UNUSED(x);
  //получить содержимое регистра
  superSetOperativMarker(sdi2colorsmallcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDVModbusRegister(int adrReg)

void setSDI2ColorSmallCountObject(int x) {
  UNUSED(x);
//записать к-во обектов
}//
void preSDI2ColorSmallReadAction(void) {
//action до чтения
  sdi2colorsmallcomponent->operativMarker[0] = -1;
  sdi2colorsmallcomponent->operativMarker[1] = -1;//оперативный маркер
  sdi2colorsmallcomponent->isActiveActualData = 1;
}//
void postSDI2ColorSmallReadAction(void) {
//action после чтения
  if(sdi2colorsmallcomponent->operativMarker[0]<0) return;//не было чтения
}//
void preSDI2ColorSmallWriteAction(void) {
//action до записи
  sdi2colorsmallcomponent->operativMarker[0] = -1;
  sdi2colorsmallcomponent->operativMarker[1] = -1;//оперативный маркер
  sdi2colorsmallcomponent->isActiveActualData = 1;
}//
void postSDI2ColorSmallWriteAction(void) {
//action после записи
}//

int privateSDI2ColorSmallGetReg2(int adrReg)
{
  //проверить внешний периметр
  int count_register = REGISTER_FOR_OBJ*sdi2colorsmallcomponent->countObject;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateSDI2ColorSmallGetReg2(int adrReg)
int privateSDI2ColorSmallGetBit2(int adrBit)
{
  //проверить внешний периметр
  int count_bit = BIT_FOR_OBJ*sdi2colorsmallcomponent->countObject;
  if(adrBit>=BEGIN_ADR_BIT && adrBit<(BEGIN_ADR_BIT+count_bit)) return 0;
  return MARKER_OUTPERIMETR;
}//privateSDI2ColorSmallGetBit2(int adrReg)
