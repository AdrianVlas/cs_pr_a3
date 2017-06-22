#include "header.h"

//начальный регистр в карте памяти
#define BEGIN_ADR_REGISTER 4674
//макс к-во обектов
#define TOTAL_OBJ 128
#define REGISTER_FOR_OBJ 10

int privateSZSBigGetReg1(int adrReg);
int privateSZSBigGetReg2(int adrReg);

int getSZSBigModbusRegister(int);//получить содержимое регистра
int getSZSBigModbusBit(int);//получить содержимое бита
int setSZSBigModbusRegister(int, int);//получить содержимое регистра
int setSZSBigModbusBit(int, int);//получить содержимое бита

void setSZSBigCountObject(void);//записать к-во обектов
void preSZSBigReadAction(void);//action до чтения
void postSZSBigReadAction(void);//action после чтения
void preSZSBigWriteAction(void);//action до записи
void postSZSBigWriteAction(void);//action после записи
void loadSZSBigActualData(void);

COMPONENT_OBJ *szsbigcomponent;

/**************************************/
//подготовка компонента СЗС
/**************************************/
void constructorSZSBigComponent(COMPONENT_OBJ *szsbigcomp)
{
  szsbigcomponent = szsbigcomp;

  szsbigcomponent->countObject = 0;//к-во обектов

  szsbigcomponent->getModbusRegister = getSZSBigModbusRegister;//получить содержимое регистра
  szsbigcomponent->getModbusBit      = getSZSBigModbusBit;//получить содержимое бита
  szsbigcomponent->setModbusRegister = setSZSBigModbusRegister;//получить содержимое регистра
  szsbigcomponent->setModbusBit      = setSZSBigModbusBit;//получить содержимое бита

  szsbigcomponent->preReadAction   = preSZSBigReadAction;//action до чтения
  szsbigcomponent->postReadAction  = postSZSBigReadAction;//action после чтения
  szsbigcomponent->preWriteAction  = preSZSBigWriteAction;//action до записи
  szsbigcomponent->postWriteAction = postSZSBigWriteAction;//action после записи

  szsbigcomponent->isActiveActualData = 0;
}//prepareDVinConfig

void loadSZSBigActualData(void) {
  //ActualData
  for(int i=0; i<100; i++) tempReadArray[i] = i;
}//loadActualData() 

int getSZSBigModbusRegister(int adrReg)
{
  //получить содержимое регистра
  if(privateSZSBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(privateSZSBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  if(szsbigcomponent->isActiveActualData) loadSZSBigActualData(); //ActualData
  szsbigcomponent->isActiveActualData = 0;

  superSetOperativMarker(szsbigcomponent, adrReg);

  return tempReadArray[adrReg-BEGIN_ADR_REGISTER];
}//getDOUTBigModbusRegister(int adrReg)
int getSZSBigModbusBit(int adrBit)
{
  //получить содержимое регистра
  superSetOperativMarker(szsbigcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setSZSBigModbusRegister(int adrReg, int dataReg)
{
  //записать содержимое регистра
  if(privateSZSBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(privateSZSBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  superSetOperativMarker(szsbigcomponent, adrReg);
  superSetTempWriteArray(dataReg);//записать в буфер

  switch((adrReg-BEGIN_ADR_REGISTER)%REGISTER_FOR_OBJ) {
   case 0:
    if(dataReg>2) return MARKER_ERRORDIAPAZON;
    return dataReg;
   case 1:
    if(dataReg>320) return MARKER_ERRORDIAPAZON;
    if(dataReg<5) return MARKER_ERRORDIAPAZON;
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
  }//switch
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setSZSBigModbusBit(int adrBit, int x)
{
  UNUSED(x);
  //получить содержимое регистра
  superSetOperativMarker(szsbigcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void setSZSBigCountObject(void) {
//записать к-во обектов
}//
void preSZSBigReadAction(void) {
//action до чтения
  szsbigcomponent->operativMarker[0] = -1;
  szsbigcomponent->operativMarker[1] = -1;//оперативный маркер
  szsbigcomponent->isActiveActualData = 1;
}//
void postSZSBigReadAction(void) {
//action после чтения
  if(szsbigcomponent->operativMarker[0]<0) return;//не было чтения
}//
void preSZSBigWriteAction(void) {
//action до записи
  szsbigcomponent->operativMarker[0] = -1;
  szsbigcomponent->operativMarker[1] = -1;//оперативный маркер
  szsbigcomponent->isActiveActualData = 1;
}//
void postSZSBigWriteAction(void) {
//action после записи
  if(szsbigcomponent->operativMarker[0]<0) return;//не было записи
//  int offset = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//найти смещение TempWriteArray
//  int countRegister = szsbigcomponent->operativMarker[1]-szsbigcomponent->operativMarker[0]+1;
//  if(szsbigcomponent->operativMarker[1]<0) countRegister = 1;
}//

int privateSZSBigGetReg1(int adrReg)
{
  //проверить внутренний периметр
  int count_register = szsbigcomponent->countObject*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg1(int adrReg)
int privateSZSBigGetReg2(int adrReg)
{
  //проверить внешний периметр
  int count_register = TOTAL_OBJ*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
