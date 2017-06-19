
#include "variables_external_m.h"

//начальный регистр в карте памяти
#define BEGIN_ADR_REGISTER 200
//начальный bit в карте памяти
#define BEGIN_ADR_BIT 18000
#define BIT_FOR_OBJ 1
//макс к-во обектов
#define TOTAL_OBJ 128
int privateDOUTSmallGetReg1(int adrReg);
int privateDOUTSmallGetReg2(int adrReg);
int privateDOUTSmallGetBit1(int adrBit);
int privateDOUTSmallGetBit2(int adrBit);

int getDOUTSmallModbusRegister(int);//получить содержимое регистра
int getDOUTSmallModbusBit(int);//получить содержимое бита
int setDOUTSmallModbusRegister(int, int);//записать регистр
int setDOUTSmallModbusBit(int, int);//записать бит

void setDOUTSmallCountObject(int);//записать к-во обектов
void preDOUTSmallReadAction();//action до чтения
void postDOUTSmallReadAction();//action после чтения
void preDOUTSmallWriteAction();//action до записи
void postDOUTSmallWriteAction();//action после записи
void loadDOUTSmallActualData();

COMPONENT_OBJ *doutsmallcomponent;

/**************************************/
//подготовка компонента ДВ
/**************************************/
void constructorDOUTSmallComponent(COMPONENT_OBJ *doutcomp)
{
  doutsmallcomponent = doutcomp;
  doutsmallcomponent->countObject = 0;//к-во обектов

  doutsmallcomponent->getModbusRegister = getDOUTSmallModbusRegister;//получить содержимое регистра
  doutsmallcomponent->getModbusBit      = getDOUTSmallModbusBit;//получить содержимое бита
  doutsmallcomponent->setModbusRegister = setDOUTSmallModbusRegister;// регистра
  doutsmallcomponent->setModbusBit      = setDOUTSmallModbusBit;// бита

  doutsmallcomponent->setCountObject  = setDOUTSmallCountObject;//записать к-во обектов
  doutsmallcomponent->preReadAction   = preDOUTSmallReadAction;//action до чтения
  doutsmallcomponent->postReadAction  = postDOUTSmallReadAction;//action после чтения
  doutsmallcomponent->preWriteAction  = preDOUTSmallWriteAction;//action до записи
  doutsmallcomponent->postWriteAction = postDOUTSmallWriteAction;//action после записи
 
  doutsmallcomponent->isActiveActualData = 0;
}//prepareDVinConfig

void loadDOUTSmallActualData() {
  //ActualData
  for(int i=0; i<100; i++) tempReadArray[i] = i;
  tempReadArray[0] = 55;//0xf2f2;
  tempReadArray[1] = 0;//xffff;
}//loadActualData() 

int getDOUTSmallModbusRegister(int adrReg) {
  //получить содержимое регистра
  if(privateDOUTSmallGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(privateDOUTSmallGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  if(doutsmallcomponent->isActiveActualData) loadDOUTSmallActualData(); //ActualData
  doutsmallcomponent->isActiveActualData = 0;

  superSetOperativMarker(doutsmallcomponent, adrReg);

  return tempReadArray[adrReg-BEGIN_ADR_REGISTER];
}//getDOUTModbusRegister(int adrReg)
int getDOUTSmallModbusBit(int adrBit) {
  //получить содержимое bit
  if(privateDOUTSmallGetBit2(adrBit)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(privateDOUTSmallGetBit1(adrBit)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  if(doutsmallcomponent->isActiveActualData) loadDOUTSmallActualData();
  doutsmallcomponent->isActiveActualData = 0;

  superSetOperativMarker(doutsmallcomponent, adrBit);

  short tmp   = tempReadArray[(adrBit-BEGIN_ADR_BIT)/16];
  short maska = 1<<((adrBit-BEGIN_ADR_BIT)%16);
  if(tmp&maska) return 1;
  return 0;
}//getDOUTModbusBit(int adrReg)
int setDOUTSmallModbusRegister(int adrReg, int) {
  //записать содержимое регистра
  superSetOperativMarker(doutsmallcomponent, adrReg);
  return MARKER_OUTPERIMETR;
}//getDOUTModbusRegister(int adrReg)
int setDOUTSmallModbusBit(int adrBit, int ) {
  //получить содержимое регистра
  superSetOperativMarker(doutsmallcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDOUTModbusRegister(int adrReg)

void setDOUTSmallCountObject(int cntObj) {
//записать к-во обектов
  if(cntObj<0) return;
  if(cntObj>=TOTAL_OBJ) return;
  doutsmallcomponent->countObject = cntObj;
}//
void preDOUTSmallReadAction() {
//action до чтения
  doutsmallcomponent->operativMarker[0] = -1;
  doutsmallcomponent->operativMarker[1] = -1;//оперативный маркер
  doutsmallcomponent->isActiveActualData = 1;
}//
void postDOUTSmallReadAction() {
//action после чтения
  if(doutsmallcomponent->operativMarker[0]<0) return;//не было чтения
}//
void preDOUTSmallWriteAction() {
//action до записи
  doutsmallcomponent->operativMarker[0] = -1;
  doutsmallcomponent->operativMarker[1] = -1;//оперативный маркер
  doutsmallcomponent->isActiveActualData = 1;
}//
void postDOUTSmallWriteAction() {
//action после записи
}//

int privateDOUTSmallGetReg1(int adrReg)
{
  //проверить внутренний периметр
  int count_register = doutsmallcomponent->countObject/16;
  if(doutsmallcomponent->countObject%16) count_register++;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg1(int adrReg)

int privateDOUTSmallGetReg2(int adrReg)
{
  //проверить внешний периметр
  int count_register = TOTAL_OBJ/16;
  if(TOTAL_OBJ%16) count_register++;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)

int privateDOUTSmallGetBit1(int adrBit)
{
  //проверить внутренний периметр
  int count_bit = BIT_FOR_OBJ*doutsmallcomponent->countObject;
  if(adrBit>=BEGIN_ADR_BIT && adrBit<(BEGIN_ADR_BIT+count_bit)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg1(int adrReg)

int privateDOUTSmallGetBit2(int adrBit)
{
  //проверить внешний периметр
  int count_bit = BIT_FOR_OBJ*TOTAL_OBJ;
  if(adrBit>=BEGIN_ADR_BIT && adrBit<(BEGIN_ADR_BIT+count_bit)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
