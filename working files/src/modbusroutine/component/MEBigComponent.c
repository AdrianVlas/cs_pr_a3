#include "header.h"

//начальный регистр в карте памяти
#define BEGIN_ADR_REGISTER 11000
//макс к-во обектов
#define REGISTER_FOR_OBJ 132

int privateMEBigGetReg2(int adrReg);

int getMEBigModbusRegister(int);//получить содержимое регистра
int getMEBigModbusBit(int);//получить содержимое бита
int setMEBigModbusRegister(int, int);//получить содержимое регистра
int setMEBigModbusBit(int, int);//получить содержимое бита

void setMEBigCountObject(int);//записать к-во обектов
void preMEBigReadAction(void);//action до чтения
void postMEBigReadAction(void);//action после чтения
void preMEBigWriteAction(void);//action до записи
void postMEBigWriteAction(void);//action после записи
void loadMEBigActualData(void);

COMPONENT_OBJ *mebigcomponent;

/**************************************/
//подготовка компонента журнал событий
/**************************************/
void constructorMEBigComponent(COMPONENT_OBJ *mebigcomp)
{
  mebigcomponent = mebigcomp;

  mebigcomponent->countObject = 1;//к-во обектов

  mebigcomponent->getModbusRegister = getMEBigModbusRegister;//получить содержимое регистра
  mebigcomponent->getModbusBit      = getMEBigModbusBit;//получить содержимое регистра
  mebigcomponent->setModbusRegister = setMEBigModbusRegister;//получить содержимое регистра
  mebigcomponent->setModbusBit      = setMEBigModbusBit;//получить содержимое регистра

  mebigcomponent->setCountObject  = setMEBigCountObject;//записать к-во обектов
  mebigcomponent->preReadAction   = preMEBigReadAction;//action до чтения
  mebigcomponent->postReadAction  = postMEBigReadAction;//action после чтения
  mebigcomponent->preWriteAction  = preMEBigWriteAction;//action до записи
  mebigcomponent->postWriteAction = postMEBigWriteAction;//action после записи

  mebigcomponent->isActiveActualData = 0;
}//prepareDVinConfig

void loadMEBigActualData(void) {
  //ActualData
  for(int i=0; i<100; i++) tempReadArray[i] = i;
}//loadActualData() 

int getMEBigModbusRegister(int adrReg)
{
  //получить содержимое регистра
  if(privateMEBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  if(mebigcomponent->isActiveActualData) loadMEBigActualData(); //ActualData
  mebigcomponent->isActiveActualData = 0;

  superSetOperativMarker(mebigcomponent, adrReg);

  return tempReadArray[adrReg-BEGIN_ADR_REGISTER];
}//getDOUTBigModbusRegister(int adrReg)
int getMEBigModbusBit(int adrBit)
{
  //получить содержимое регистра
  superSetOperativMarker(mebigcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setMEBigModbusRegister(int adrReg, int dataReg)
{
  //записать содержимое регистра
  if(privateMEBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  superSetOperativMarker(mebigcomponent, adrReg);
  superSetTempWriteArray(dataReg);//записать в буфер

  return dataReg;
}//getDOUTBigModbusRegister(int adrReg)
int setMEBigModbusBit(int adrBit, int x)
{
  UNUSED(x);
  //получить содержимое регистра
  superSetOperativMarker(mebigcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void setMEBigCountObject(int x) {
  UNUSED(x);
//записать к-во обектов
}//
void preMEBigReadAction(void) {
//action до чтения
  mebigcomponent->operativMarker[0] = -1;
  mebigcomponent->operativMarker[1] = -1;//оперативный маркер
  mebigcomponent->isActiveActualData = 1;
}//
void postMEBigReadAction(void) {
//action после чтения
  if(mebigcomponent->operativMarker[0]<0) return;//не было чтения
}//
void preMEBigWriteAction(void) {
//action до записи
  mebigcomponent->operativMarker[0] = -1;
  mebigcomponent->operativMarker[1] = -1;//оперативный маркер
  mebigcomponent->isActiveActualData = 1;
}//
void postMEBigWriteAction(void) {
//action после записи
  if(mebigcomponent->operativMarker[0]<0) return;//не было записи
  int offset = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//найти смещение TempWriteArray
  int countRegister = mebigcomponent->operativMarker[1]-mebigcomponent->operativMarker[0]+1;
  if(mebigcomponent->operativMarker[1]<0) countRegister = 1;
}//

int privateMEBigGetReg2(int adrReg)
{
  //проверить внешний периметр
  int count_register = REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
