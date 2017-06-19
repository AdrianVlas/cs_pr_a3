#include "variables_external_m.h"

//начальный регистр в карте памяти
#define BEGIN_ADR_REGISTER 300
//начальный bit в карте памяти
#define BEGIN_ADR_BIT 19000
#define BIT_FOR_OBJ 1
//макс к-во обектов
#define TOTAL_OBJ 128
int privateDVSmallGetReg1(int adrReg);
int privateDVSmallGetReg2(int adrReg);
int privateDVSmallGetBit1(int adrBit);
int privateDVSmallGetBit2(int adrBit);

int getDVSmallModbusRegister(int);//получить содержимое регистра
int getDVSmallModbusBit(int);//получить содержимое бита
int setDVSmallModbusRegister(int, int);//получить содержимое регистра
int setDVSmallModbusBit(int, int);//получить содержимое бита

void setDVSmallCountObject(int);//записать к-во обектов
void preDVSmallReadAction();//action до чтения
void postDVSmallReadAction();//action после чтения
void preDVSmallWriteAction();//action до записи
void postDVSmallWriteAction();//action после записи
void loadDVSmallActualData();

COMPONENT_OBJ *dvsmallcomponent;

/**************************************/
//подготовка компонента ДВ
/**************************************/
void constructorDVSmallComponent(COMPONENT_OBJ *dvsmallcomp)
{
  dvsmallcomponent = dvsmallcomp;

  dvsmallcomponent->countObject = 0;//к-во обектов

  dvsmallcomponent->getModbusRegister = getDVSmallModbusRegister;//получить содержимое регистра
  dvsmallcomponent->getModbusBit      = getDVSmallModbusBit;//получить содержимое бита
  dvsmallcomponent->setModbusRegister = setDVSmallModbusRegister;//получить содержимое регистра
  dvsmallcomponent->setModbusBit      = setDVSmallModbusBit;//получить содержимое бита

  dvsmallcomponent->setCountObject  = setDVSmallCountObject;//записать к-во обектов
  dvsmallcomponent->preReadAction   = preDVSmallReadAction;//action до чтения
  dvsmallcomponent->postReadAction  = postDVSmallReadAction;//action после чтения
  dvsmallcomponent->preWriteAction  = preDVSmallWriteAction;//action до записи
  dvsmallcomponent->postWriteAction = postDVSmallWriteAction;//action после записи

  dvsmallcomponent->isActiveActualData = 0;
}//prepareDVinConfig

void loadDVSmallActualData() {
  //ActualData
  for(int i=0; i<100; i++) tempReadArray[i] = i;
}//loadActualData() 

int getDVSmallModbusRegister(int adrReg)
{
  //получить содержимое регистра
  if(privateDVSmallGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(privateDVSmallGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  if(dvsmallcomponent->isActiveActualData) loadDVSmallActualData(); //ActualData
  dvsmallcomponent->isActiveActualData = 0;

  superSetOperativMarker(dvsmallcomponent, adrReg);

  return tempReadArray[adrReg-BEGIN_ADR_REGISTER];
}//getDVModbusRegister(int adrReg)
int getDVSmallModbusBit(int adrBit)
{
  //получить содержимое bit
  if(privateDVSmallGetBit2(adrBit)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(privateDVSmallGetBit1(adrBit)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  if(dvsmallcomponent->isActiveActualData) loadDVSmallActualData();
  dvsmallcomponent->isActiveActualData = 0;

  superSetOperativMarker(dvsmallcomponent, adrBit);

  short tmp   = tempReadArray[(adrBit-BEGIN_ADR_BIT)/16];
  short maska = 1<<((adrBit-BEGIN_ADR_BIT)%16);
  if(tmp&maska) return 1;
  return 0;
}//getDVModbusBit(int adrReg)
int setDVSmallModbusRegister(int adrReg, int )
{
  //записать содержимое регистра
  superSetOperativMarker(dvsmallcomponent, adrReg);
  return MARKER_OUTPERIMETR;
}//getDVModbusRegister(int adrReg)
int setDVSmallModbusBit(int adrBit, int )
{
  //получить содержимое регистра
  superSetOperativMarker(dvsmallcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDVModbusRegister(int adrReg)

void setDVSmallCountObject(int cntObj) {
//записать к-во обектов
  if(cntObj<0) return;
  if(cntObj>=TOTAL_OBJ) return;
  dvsmallcomponent->countObject = cntObj;
}//
void preDVSmallReadAction() {
//action до чтения
  dvsmallcomponent->operativMarker[0] = -1;
  dvsmallcomponent->operativMarker[1] = -1;//оперативный маркер
  dvsmallcomponent->isActiveActualData = 1;
}//
void postDVSmallReadAction() {
//action после чтения
  if(dvsmallcomponent->operativMarker[0]<0) return;//не было чтения
}//
void preDVSmallWriteAction() {
//action до записи
  dvsmallcomponent->operativMarker[0] = -1;
  dvsmallcomponent->operativMarker[1] = -1;//оперативный маркер
  dvsmallcomponent->isActiveActualData = 1;
}//
void postDVSmallWriteAction() {
//action после записи
}//

int privateDVSmallGetReg1(int adrReg)
{
  //проверить внутренний периметр
  int count_register = dvsmallcomponent->countObject/16;
  if(dvsmallcomponent->countObject%16) count_register++;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg1(int adrReg)

int privateDVSmallGetReg2(int adrReg)
{
  //проверить внешний периметр
  int count_register = TOTAL_OBJ/16;
  if(TOTAL_OBJ%16) count_register++;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)

int privateDVSmallGetBit1(int adrBit)
{
  //проверить внутренний периметр
  int count_bit = BIT_FOR_OBJ*dvsmallcomponent->countObject;
  if(adrBit>=BEGIN_ADR_BIT && adrBit<(BEGIN_ADR_BIT+count_bit)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg1(int adrReg)

int privateDVSmallGetBit2(int adrBit)
{
  //проверить внешний периметр
  int count_bit = BIT_FOR_OBJ*TOTAL_OBJ;
  if(adrBit>=BEGIN_ADR_BIT && adrBit<(BEGIN_ADR_BIT+count_bit)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
