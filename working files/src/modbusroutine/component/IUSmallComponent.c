#include "header.h"

//начальный регистр в карте памяти
#define BEGIN_ADR_REGISTER 0
#define REGISTER_FOR_OBJ 16

int getIUModbusRegister(int);//получить содержимое регистра
int getIUModbusBit(int);//получить содержимое бита
int setIUModbusRegister(int, int);//получить содержимое регистра
int setIUModbusBit(int, int);//получить содержимое бита

void setIUSmallCountObject(int);//записать к-во обектов
void preIUSmallReadAction(void);//action до чтения
void postIUSmallReadAction(void);//action после чтения
void preIUSmallWriteAction(void);//action до записи
void postIUSmallWriteAction(void);//action после записи
void loadIUSmallActualData(void);

int privateIUGetReg2(int adrReg);

COMPONENT_OBJ *iucomponent;

/**************************************/
//подготовка компонента идентификация устройства
/**************************************/
void constructorIUSmallComponent(COMPONENT_OBJ *iucomp)
{
  iucomponent = iucomp;

  iucomponent->countObject = 1;//к-во обектов

  iucomponent->getModbusRegister = getIUModbusRegister;//получить содержимое регистра
  iucomponent->getModbusBit      = getIUModbusBit;//получить содержимое бита
  iucomponent->setModbusRegister = setIUModbusRegister;//получить содержимое регистра
  iucomponent->setModbusBit      = setIUModbusBit;//получить содержимое бита

  iucomponent->setCountObject  = setIUSmallCountObject;//записать к-во обектов
  iucomponent->preReadAction   = preIUSmallReadAction;//action до чтения
  iucomponent->postReadAction  = postIUSmallReadAction;//action после чтения
  iucomponent->preWriteAction  = preIUSmallWriteAction;//action до записи
  iucomponent->postWriteAction = postIUSmallWriteAction;//action после записи

  iucomponent->isActiveActualData = 0;
}//prepareDVinConfig

void loadIUSmallActualData(void) {
  //ActualData
  for(int i=0; i<100; i++) tempReadArray[i] = i+22;
//  tempReadArray[0] = 22;
}//loadActualData() 

int getIUModbusRegister(int adrReg)
{
  //получить содержимое регистра
  if(privateIUGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  if(iucomponent->isActiveActualData) loadIUSmallActualData(); //ActualData
  iucomponent->isActiveActualData = 0;

  superSetOperativMarker(iucomponent, adrReg);

  return tempReadArray[adrReg-BEGIN_ADR_REGISTER];
}//getDVModbusRegister(int adrReg)
int getIUModbusBit(int adrBit) {
  //получить содержимое bit
  superSetOperativMarker(iucomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getIUModbusBit(int )
int setIUModbusRegister(int adrReg, int x) {
  UNUSED(x);
  //записать содержимое регистра
  superSetOperativMarker(iucomponent, adrReg);
  return MARKER_OUTPERIMETR;
}//setIUModbusRegister(int, int)
int setIUModbusBit(int adrBit, int x) {
  UNUSED(x);
  //записать содержимое bit
  superSetOperativMarker(iucomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//setIUModbusBit(int, int )

void setIUSmallCountObject(int x) {
  UNUSED(x);
//записать к-во обектов
}//
void preIUSmallReadAction(void) {
//action до чтения
  iucomponent->operativMarker[0] = -1;
  iucomponent->operativMarker[1] = -1;//оперативный маркер
  iucomponent->isActiveActualData = 1;
}//
void postIUSmallReadAction(void) {
//action после чтения
  if(iucomponent->operativMarker[0]<0) return;//не было чтения
}//
void preIUSmallWriteAction(void) {
//action до записи
  iucomponent->operativMarker[0] = -1;
  iucomponent->operativMarker[1] = -1;//оперативный маркер
  iucomponent->isActiveActualData = 1;
}//
void postIUSmallWriteAction(void) {
//action после записи
}//

int privateIUGetReg2(int adrReg)
{
  //проверить внешний периметр
  int count_register = REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)

