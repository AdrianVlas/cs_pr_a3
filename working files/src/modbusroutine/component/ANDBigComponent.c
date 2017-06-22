#include "header.h"

//начальный регистр в карте памяти
#define BEGIN_ADR_REGISTER 8267
//макс к-во обектов
#define TOTAL_OBJ 128
#define REGISTER_FOR_OBJ 16

int privateANDBigGetReg1(int adrReg);
int privateANDBigGetReg2(int adrReg);

int getANDBigModbusRegister(int);//получить содержимое регистра
int getANDBigModbusBit(int);//получить содержимое бита
int setANDBigModbusRegister(int, int);// регистр
int setANDBigModbusBit(int, int);// бит

void setANDBigCountObject(void);
void preANDBigReadAction(void);//action до чтения
void postANDBigReadAction(void);//action после чтения
void preANDBigWriteAction(void);//action до записи
void postANDBigWriteAction(void);//action после записи
void loadANDBigActualData(void);

COMPONENT_OBJ *andbigcomponent;

/**************************************/
//подготовка компонента AND
/**************************************/
void constructorANDBigComponent(COMPONENT_OBJ *andbigcomp)
{
  andbigcomponent = andbigcomp;

  andbigcomponent->countObject = 0;//к-во обектов

  andbigcomponent->getModbusRegister = getANDBigModbusRegister;//получить содержимое регистра
  andbigcomponent->getModbusBit      = getANDBigModbusBit;//получить содержимое бита
  andbigcomponent->setModbusRegister = setANDBigModbusRegister;//записать регистр
  andbigcomponent->setModbusBit      = setANDBigModbusBit;//записать бит

  andbigcomponent->preReadAction   = preANDBigReadAction;//action до чтения
  andbigcomponent->postReadAction  = postANDBigReadAction;//action после чтения
  andbigcomponent->preWriteAction  = preANDBigWriteAction;//action до записи
  andbigcomponent->postWriteAction = postANDBigWriteAction;//action после записи

  andbigcomponent->isActiveActualData = 0;
}//prepareDVinConfig

void loadANDBigActualData(void) {
  //ActualData
  for(int i=0; i<100; i++) tempReadArray[i] = i;
  /*
  Для тих компонетів, де є не один однотипний вхід а декілька (ст. логіка і Журнал подій) після запису треба відсортувати щоб 0-і були вкінці, а числа(id;n; out) іншли в сторону зростання
  */
}//loadActualData() 

int getANDBigModbusRegister(int adrReg)
{
  //получить содержимое регистра
  if(privateANDBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(privateANDBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  if(andbigcomponent->isActiveActualData) loadANDBigActualData(); //ActualData
  andbigcomponent->isActiveActualData = 0;

  superSetOperativMarker(andbigcomponent, adrReg);

  return tempReadArray[adrReg-BEGIN_ADR_REGISTER];
}//getDOUTBigModbusRegister(int adrReg)
int getANDBigModbusBit(int adrBit)
{
  //получить содержимое бита
  superSetOperativMarker(andbigcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setANDBigModbusRegister(int adrReg, int dataReg)
{
  //записать содержимое регистра
  if(privateANDBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(privateANDBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  superSetOperativMarker(andbigcomponent, adrReg);
  superSetTempWriteArray(dataReg);//записать в буфер

  switch((adrReg-BEGIN_ADR_REGISTER)%REGISTER_FOR_OBJ) {
   case 0:
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
    return dataReg;
   case 1:
   return dataReg;
   case 2:
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
    return dataReg;
   case 3:
   return dataReg;
   case 4:
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
    return dataReg;
   case 5:
   return dataReg;
   case 6:
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
    return dataReg;
   case 7:
   return dataReg;
   case 8:
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
    return dataReg;
   case 9:
   return dataReg;
   case 10:
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
    return dataReg;
   case 11:
   return dataReg;
   case 12:
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
    return dataReg;
   case 13:
   return dataReg;
   case 14:
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
    return dataReg;
   case 15:
   return dataReg;
  }//switch
  return MARKER_OUTPERIMETR;
}//setDOUTBigModbusRegister(int adrReg)
int setANDBigModbusBit(int adrBit, int x)
{
  UNUSED(x);
  //получить содержимое бита
  superSetOperativMarker(andbigcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//setDOUTBigModbusRegister(int adrReg)

void setANDBigCountObject(void) {
//записать к-во обектов
}//

void preANDBigReadAction(void) {
//action до чтения
  andbigcomponent->operativMarker[0] = -1;
  andbigcomponent->operativMarker[1] = -1;//оперативный маркер
  andbigcomponent->isActiveActualData = 1;
}//preANDBigReadAction() 

void postANDBigReadAction(void) {
//action после чтения
  if(andbigcomponent->operativMarker[0]<0) return;//не было чтения
}//postANDBigReadAction() 

void preANDBigWriteAction(void) {
//action до записи
  andbigcomponent->operativMarker[0] = -1;
  andbigcomponent->operativMarker[1] = -1;//оперативный маркер
  andbigcomponent->isActiveActualData = 1;
}//preANDBigWriteAction() 

void postANDBigWriteAction(void) {
//action после записи
  if(andbigcomponent->operativMarker[0]<0) return;//не было записи
//  int offset = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//найти смещение TempWriteArray
  //int countRegister = andbigcomponent->operativMarker[1]-andbigcomponent->operativMarker[0]+1;
//  if(andbigcomponent->operativMarker[1]<0) countRegister = 1;
}//postANDBigWriteAction() 

int privateANDBigGetReg1(int adrReg)
{
  //проверить внутренний периметр
  int count_register = andbigcomponent->countObject*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg1(int adrReg)
int privateANDBigGetReg2(int adrReg)
{
  //проверить внешний периметр
  int count_register = TOTAL_OBJ*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
