#include "header.h"

//начальный регистр в карте памяти
#define BEGIN_ADR_REGISTER 3000
//макс к-во обектов
#define TOTAL_OBJ 128
#define REGISTER_FOR_OBJ 11

int privateSDIBigGetReg1(int adrReg);
int privateSDIBigGetReg2(int adrReg);

int getSDIBigModbusRegister(int);//получить содержимое регистра
int getSDIBigModbusBit(int);//получить содержимое бита
int setSDIBigModbusRegister(int, int);//получить содержимое регистра
int setSDIBigModbusBit(int, int);//получить содержимое бита

void setSDIBigCountObject(void);//записать к-во обектов
void preSDIBigReadAction(void);//action до чтения
void postSDIBigReadAction(void);//action после чтения
void preSDIBigWriteAction(void);//action до записи
void postSDIBigWriteAction(void);//action после записи
void loadSDIBigActualData(void);

COMPONENT_OBJ *sdibigcomponent;

/**************************************/
//подготовка компонента светоиндикаторов
/**************************************/
void constructorSDIBigComponent(COMPONENT_OBJ *sdibigcomp)
{
  sdibigcomponent = sdibigcomp;

  sdibigcomponent->countObject = 14;//к-во обектов

  sdibigcomponent->getModbusRegister = getSDIBigModbusRegister;//получить содержимое регистра
  sdibigcomponent->getModbusBit      = getSDIBigModbusBit;//получить содержимое бита
  sdibigcomponent->setModbusRegister = setSDIBigModbusRegister;//получить содержимое регистра
  sdibigcomponent->setModbusBit      = setSDIBigModbusBit;//получить содержимое бита

  sdibigcomponent->preReadAction   = preSDIBigReadAction;//action до чтения
  sdibigcomponent->postReadAction  = postSDIBigReadAction;//action после чтения
  sdibigcomponent->preWriteAction  = preSDIBigWriteAction;//action до записи
  sdibigcomponent->postWriteAction = postSDIBigWriteAction;//action после записи

  sdibigcomponent->isActiveActualData = 0;
}//prepareDVinConfig

void loadSDIBigActualData(void) {
  //ActualData
  for(int i=0; i<100; i++) tempReadArray[i] = i;
}//loadActualData() 

int getSDIBigModbusRegister(int adrReg)
{
  //получить содержимое регистра
  if(privateSDIBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
//  if(privateSDIBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  if(sdibigcomponent->isActiveActualData) loadSDIBigActualData(); //ActualData
  sdibigcomponent->isActiveActualData = 0;

  superSetOperativMarker(sdibigcomponent, adrReg);

  return tempReadArray[adrReg-BEGIN_ADR_REGISTER];
}//getSDIBigModbusRegister(int adrReg)
int getSDIBigModbusBit(int adrBit)
{
  //получить содержимое регистра
  superSetOperativMarker(sdibigcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getSDIBigModbusBit(int )
int setSDIBigModbusRegister(int adrReg, int dataReg)
{
  //записать содержимое регистра
  if(privateSDIBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
//  if(privateSDIBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  superSetOperativMarker(sdibigcomponent, adrReg);
  superSetTempWriteArray(dataReg);//записать в буфер

  switch((adrReg-BEGIN_ADR_REGISTER)%REGISTER_FOR_OBJ) {
   case 0:
   return dataReg;
   case 1:
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
    return dataReg;
   case 2:
   return dataReg;
   case 3:
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
    return dataReg;
   case 4:
   return dataReg;
   case 5:
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
    return dataReg;
   case 6:
   return dataReg;
   case 7:
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
    return dataReg;
   case 8:
   return dataReg;
   case 9:
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
    return dataReg;
   case 10:
   return dataReg;
  }//switch
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setSDIBigModbusBit(int adrBit, int x)
{
  UNUSED(x);
  //получить содержимое регистра
  superSetOperativMarker(sdibigcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void setSDIBigCountObject(void) {
//записать к-во обектов
//  if(cntObj<0) return;
//  if(cntObj>TOTAL_OBJ) return;
//  sdibigcomponent->countObject = cntObj;
}//
void preSDIBigReadAction(void) {
//action до чтения
  sdibigcomponent->operativMarker[0] = -1;
  sdibigcomponent->operativMarker[1] = -1;//оперативный маркер
  sdibigcomponent->isActiveActualData = 1;
}//
void postSDIBigReadAction(void) {
//action после чтения
  if(sdibigcomponent->operativMarker[0]<0) return;//не было чтения
}//
void preSDIBigWriteAction(void) {
//action до записи
  sdibigcomponent->operativMarker[0] = -1;
  sdibigcomponent->operativMarker[1] = -1;//оперативный маркер
  sdibigcomponent->isActiveActualData = 1;
}//
void postSDIBigWriteAction(void) {
//action после записи
  if(sdibigcomponent->operativMarker[0]<0) return;//не было записи
//  int offset = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//найти смещение TempWriteArray
//  int countRegister = sdibigcomponent->operativMarker[1]-sdibigcomponent->operativMarker[0]+1;
//  if(sdibigcomponent->operativMarker[1]<0) countRegister = 1;
}//

int privateSDIBigGetReg2(int adrReg)
{
  //проверить внутренний периметр
  int count_register = sdibigcomponent->countObject*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg1(int adrReg)
//int privateSDIBigGetReg2(int adrReg)
//{
  //проверить внешний периметр
//  int count_register = TOTAL_OBJ*REGISTER_FOR_OBJ;
//  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
//  return MARKER_OUTPERIMETR;
//}//privateGetReg2(int adrReg)
