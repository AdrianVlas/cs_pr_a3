#include "header.h"

//начальный регистр в карте памяти
#define BEGIN_ADR_REGISTER 61949
//макс к-во обектов
#define REGISTER_FOR_OBJ 9

int privateRPOBigGetReg2(int adrReg);

int getRPOBigModbusRegister(int);//получить содержимое регистра
int getRPOBigModbusBit(int);//получить содержимое бита
int setRPOBigModbusRegister(int, int);//получить содержимое регистра
int setRPOBigModbusBit(int, int);//получить содержимое бита

void setRPOBigCountObject(int);//записать к-во обектов
void preRPOBigReadAction(void);//action до чтения
void postRPOBigReadAction(void);//action после чтения
void preRPOBigWriteAction(void);//action до записи
void postRPOBigWriteAction(void);//action после записи
void loadRPOBigActualData(void);

COMPONENT_OBJ *rpobigcomponent;

/**************************************/
//подготовка компонента Регистратор Программных Ошибок
/**************************************/
void constructorRPOBigComponent(COMPONENT_OBJ *rpobigcomp)
{
  rpobigcomponent = rpobigcomp;

  rpobigcomponent->countObject = 1;//к-во обектов

  rpobigcomponent->getModbusRegister = getRPOBigModbusRegister;//получить содержимое регистра
  rpobigcomponent->getModbusBit      = getRPOBigModbusBit;//получить содержимое бита
  rpobigcomponent->setModbusRegister = setRPOBigModbusRegister;//получить содержимое регистра
  rpobigcomponent->setModbusBit      = setRPOBigModbusBit;//получить содержимое бита

  rpobigcomponent->setCountObject  = setRPOBigCountObject;//записать к-во обектов
  rpobigcomponent->preReadAction   = preRPOBigReadAction;//action до чтения
  rpobigcomponent->postReadAction  = postRPOBigReadAction;//action после чтения
  rpobigcomponent->preWriteAction  = preRPOBigWriteAction;//action до записи
  rpobigcomponent->postWriteAction = postRPOBigWriteAction;//action после записи

  rpobigcomponent->isActiveActualData = 0;
}//prepareDVinConfig

void loadRPOBigActualData(void) {
  //ActualData
  for(int i=0; i<100; i++) tempReadArray[i] = i;
}//loadActualData() 

int getRPOBigModbusRegister(int adrReg)
{
  //получить содержимое регистра
  if(privateRPOBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  if(rpobigcomponent->isActiveActualData) loadRPOBigActualData(); //ActualData
  rpobigcomponent->isActiveActualData = 0;

  superSetOperativMarker(rpobigcomponent, adrReg);

  return tempReadArray[adrReg-BEGIN_ADR_REGISTER];
}//getDOUTBigModbusRegister(int adrReg)
int getRPOBigModbusBit(int adrBit)
{
  //получить содержимое регистра
  superSetOperativMarker(rpobigcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setRPOBigModbusRegister(int adrReg, int dataReg)
{
  //записать содержимое регистра
  if(privateRPOBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  superSetOperativMarker(rpobigcomponent, adrReg);
  superSetTempWriteArray(dataReg);//записать в буфер

  return dataReg;
}//getDOUTBigModbusRegister(int adrReg)
int setRPOBigModbusBit(int adrBit, int x)
{
  UNUSED(x);
  //получить содержимое регистра
  superSetOperativMarker(rpobigcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void setRPOBigCountObject(int x) {
//записать к-во обектов
  UNUSED(x);
}//
void preRPOBigReadAction(void) {
//action до чтения
  rpobigcomponent->operativMarker[0] = -1;
  rpobigcomponent->operativMarker[1] = -1;//оперативный маркер
  rpobigcomponent->isActiveActualData = 1;
}//
void postRPOBigReadAction(void) {
//action после чтения
  if(rpobigcomponent->operativMarker[0]<0) return;//не было чтения
}//
void preRPOBigWriteAction(void) {
//action до записи
  rpobigcomponent->operativMarker[0] = -1;
  rpobigcomponent->operativMarker[1] = -1;//оперативный маркер
  rpobigcomponent->isActiveActualData = 1;
}//
void postRPOBigWriteAction(void) {
//action после записи
  if(rpobigcomponent->operativMarker[0]<0) return;//не было записи
  int offset = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//найти смещение TempWriteArray
  int countRegister = rpobigcomponent->operativMarker[1]-rpobigcomponent->operativMarker[0]+1;
  if(rpobigcomponent->operativMarker[1]<0) countRegister = 1;
}//

int privateRPOBigGetReg2(int adrReg)
{
  //проверить внешний периметр
  int count_register = REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
