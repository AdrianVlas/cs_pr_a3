#include "header.h"

//начальный регистр в карте памяти
#define BEGIN_ADR_REGISTER 8010
//макс к-во обектов
#define TOTAL_OBJ 128
#define REGISTER_FOR_OBJ 4

int privateTUBigGetReg1(int adrReg);
int privateTUBigGetReg2(int adrReg);

int getTUBigModbusRegister(int);//получить содержимое регистра
int getTUBigModbusBit(int);//получить содержимое бита
int setTUBigModbusRegister(int, int);//получить содержимое регистра
int setTUBigModbusBit(int, int);//получить содержимое бита

void setTUBigCountObject(void);//записать к-во обектов
void preTUBigReadAction(void);//action до чтения
void postTUBigReadAction(void);//action после чтения
void preTUBigWriteAction(void);//action до записи
void postTUBigWriteAction(void);//action после записи
void loadTUBigActualData(void);

COMPONENT_OBJ *tubigcomponent;

/**************************************/
//подготовка компонента телеуправление
/**************************************/
void constructorTUBigComponent(COMPONENT_OBJ *tubigcomp)
{
  tubigcomponent = tubigcomp;

  tubigcomponent->countObject = 0;//к-во обектов

  tubigcomponent->getModbusRegister = getTUBigModbusRegister;//получить содержимое регистра
  tubigcomponent->getModbusBit      = getTUBigModbusBit;//получить содержимое бита
  tubigcomponent->setModbusRegister = setTUBigModbusRegister;//получить содержимое регистра
  tubigcomponent->setModbusBit      = setTUBigModbusBit;//получить содержимое бита

  tubigcomponent->preReadAction   = preTUBigReadAction;//action до чтения
  tubigcomponent->postReadAction  = postTUBigReadAction;//action после чтения
  tubigcomponent->preWriteAction  = preTUBigWriteAction;//action до записи
  tubigcomponent->postWriteAction = postTUBigWriteAction;//action после записи

  tubigcomponent->isActiveActualData = 0;
}//prepareDVinConfig

void loadTUBigActualData(void) {
  //ActualData
  for(int i=0; i<100; i++) tempReadArray[i] = i;
}//loadActualData() 

int getTUBigModbusRegister(int adrReg)
{
  //получить содержимое регистра
  if(privateTUBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(privateTUBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  if(tubigcomponent->isActiveActualData) loadTUBigActualData(); //ActualData
  tubigcomponent->isActiveActualData = 0;

  superSetOperativMarker(tubigcomponent, adrReg);

  return tempReadArray[adrReg-BEGIN_ADR_REGISTER];
}//getDOUTBigModbusRegister(int adrReg)
int getTUBigModbusBit(int adrBit)
{
  //получить содержимое регистра
  superSetOperativMarker(tubigcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setTUBigModbusRegister(int adrReg, int dataReg)
{
  //записать содержимое регистра
  if(privateTUBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(privateTUBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  superSetOperativMarker(tubigcomponent, adrReg);
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
  }//switch
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setTUBigModbusBit(int adrBit, int x)
{
  UNUSED(x);
  //получить содержимое регистра
  superSetOperativMarker(tubigcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void setTUBigCountObject(void) {
//записать к-во обектов
}//
void preTUBigReadAction(void) {
//action до чтения
  tubigcomponent->operativMarker[0] = -1;
  tubigcomponent->operativMarker[1] = -1;//оперативный маркер
  tubigcomponent->isActiveActualData = 1;
}//
void postTUBigReadAction(void) {
//action после чтения
  if(tubigcomponent->operativMarker[0]<0) return;//не было чтения
}//
void preTUBigWriteAction(void) {
//action до записи
  tubigcomponent->operativMarker[0] = -1;
  tubigcomponent->operativMarker[1] = -1;//оперативный маркер
  tubigcomponent->isActiveActualData = 1;
}//
void postTUBigWriteAction(void) {
//action после записи
  if(tubigcomponent->operativMarker[0]<0) return;//не было записи
//  int offset = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//найти смещение TempWriteArray
//  int countRegister = tubigcomponent->operativMarker[1]-tubigcomponent->operativMarker[0]+1;
//  if(tubigcomponent->operativMarker[1]<0) countRegister = 1;
}//

int privateTUBigGetReg1(int adrReg)
{
  //проверить внутренний периметр
  int count_register = tubigcomponent->countObject*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg1(int adrReg)
int privateTUBigGetReg2(int adrReg)
{
  //проверить внешний периметр
  int count_register = TOTAL_OBJ*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
