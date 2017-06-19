#include "header.h"

//начальный регистр в карте памяти
#define BEGIN_ADR_REGISTER 12000
//макс к-во обектов
#define REGISTER_FOR_OBJ 135

int privateRegBigGetReg2(int adrReg);

int getRegBigModbusRegister(int);//получить содержимое регистра
int getRegBigModbusBit(int);//получить содержимое бита
int setRegBigModbusRegister(int, int);//получить содержимое регистра
int setRegBigModbusBit(int, int);//получить содержимое бита

void setRegBigCountObject(int);//записать к-во обектов
void preRegBigReadAction(void);//action до чтения
void postRegBigReadAction(void);//action после чтения
void preRegBigWriteAction(void);//action до записи
void postRegBigWriteAction(void);//action после записи
void loadRegBigActualData(void);

COMPONENT_OBJ *regbigcomponent;

/**************************************/
//подготовка компонента регистратор
/**************************************/
void constructorRegBigComponent(COMPONENT_OBJ *regbigcomp)
{
  regbigcomponent = regbigcomp;

  regbigcomponent->countObject = 1;//к-во обектов

  regbigcomponent->getModbusRegister = getRegBigModbusRegister;//получить содержимое регистра
  regbigcomponent->getModbusBit      = getRegBigModbusBit;//получить содержимое бита
  regbigcomponent->setModbusRegister = setRegBigModbusRegister;//получить содержимое регистра
  regbigcomponent->setModbusBit      = setRegBigModbusBit;//получить содержимое бита

  regbigcomponent->setCountObject  = setRegBigCountObject;//записать к-во обектов
  regbigcomponent->preReadAction   = preRegBigReadAction;//action до чтения
  regbigcomponent->postReadAction  = postRegBigReadAction;//action после чтения
  regbigcomponent->preWriteAction  = preRegBigWriteAction;//action до записи
  regbigcomponent->postWriteAction = postRegBigWriteAction;//action после записи

  regbigcomponent->isActiveActualData = 0;
}//prepareDVinConfig

void loadRegBigActualData(void) {
  //ActualData
  for(int i=0; i<100; i++) tempReadArray[i] = i;
}//loadActualData() 

int getRegBigModbusRegister(int adrReg)
{
  //получить содержимое регистра
  if(privateRegBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  if(regbigcomponent->isActiveActualData) loadRegBigActualData(); //ActualData
  regbigcomponent->isActiveActualData = 0;

  superSetOperativMarker(regbigcomponent, adrReg);

  return tempReadArray[adrReg-BEGIN_ADR_REGISTER];
}//getDOUTBigModbusRegister(int adrReg)
int getRegBigModbusBit(int adrBit)
{
  //получить содержимое регистра
  superSetOperativMarker(regbigcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setRegBigModbusRegister(int adrReg, int dataReg)
{
  //записать содержимое регистра
  if(privateRegBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  superSetOperativMarker(regbigcomponent, adrReg);
  superSetTempWriteArray(dataReg);//записать в буфер

  switch(adrReg-BEGIN_ADR_REGISTER) {
   case 0: //12000
    if(dataReg>250) return MARKER_ERRORDIAPAZON;
    if(dataReg<5) return MARKER_ERRORDIAPAZON;
    return dataReg;
   case 1: //12001
    if(dataReg>1250) return MARKER_ERRORDIAPAZON;
    if(dataReg<5) return MARKER_ERRORDIAPAZON;
    return dataReg;
    case 2://12002
    return MARKER_ERRORPERIMETR;
   case 3: //12003
    if(dataReg>99) return MARKER_ERRORDIAPAZON;
    return dataReg;
  }//switch

  return dataReg;
}//getDOUTBigModbusRegister(int adrReg)
int setRegBigModbusBit(int adrBit, int x)
{
  UNUSED(x);
  //получить содержимое регистра
  superSetOperativMarker(regbigcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void setRegBigCountObject(int x) {
  UNUSED(x);
//записать к-во обектов
}//
void preRegBigReadAction(void) {
//action до чтения
  regbigcomponent->operativMarker[0] = -1;
  regbigcomponent->operativMarker[1] = -1;//оперативный маркер
  regbigcomponent->isActiveActualData = 1;
}//
void postRegBigReadAction(void) {
//action после чтения
  if(regbigcomponent->operativMarker[0]<0) return;//не было чтения
}//
void preRegBigWriteAction(void) {
//action до записи
  regbigcomponent->operativMarker[0] = -1;
  regbigcomponent->operativMarker[1] = -1;//оперативный маркер
  regbigcomponent->isActiveActualData = 1;
}//
void postRegBigWriteAction(void) {
//action после записи
  if(regbigcomponent->operativMarker[0]<0) return;//не было записи
  int offset = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//найти смещение TempWriteArray
  int countRegister = regbigcomponent->operativMarker[1]-regbigcomponent->operativMarker[0]+1;
  if(regbigcomponent->operativMarker[1]<0) countRegister = 1;
}//

int privateRegBigGetReg2(int adrReg)
{
  //проверить внешний периметр
  int count_register = REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
