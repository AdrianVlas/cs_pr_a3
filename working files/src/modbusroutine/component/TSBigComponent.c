#include "variables_external_m.h"

//начальный регистр в карте памяти
#define BEGIN_ADR_REGISTER 7753
//макс к-во обектов
#define TOTAL_OBJ 128
#define REGISTER_FOR_OBJ 4

int privateTSBigGetReg1(int adrReg);
int privateTSBigGetReg2(int adrReg);

int getTSBigModbusRegister(int);//получить содержимое регистра
int getTSBigModbusBit(int);//получить содержимое бита
int setTSBigModbusRegister(int, int);//получить содержимое регистра
int setTSBigModbusBit(int, int);//получить содержимое бита

void setTSBigCountObject(int);//записать к-во обектов
void preTSBigReadAction();//action до чтения
void postTSBigReadAction();//action после чтения
void preTSBigWriteAction();//action до записи
void postTSBigWriteAction();//action после записи
void loadTSBigActualData();

COMPONENT_OBJ *tsbigcomponent;

/**************************************/
//подготовка компонента телесигнализации
/**************************************/
void constructorTSBigComponent(COMPONENT_OBJ *tsbigcomp)
{
  tsbigcomponent = tsbigcomp;

  tsbigcomponent->countObject = 0;//к-во обектов

  tsbigcomponent->getModbusRegister = getTSBigModbusRegister;//получить содержимое регистра
  tsbigcomponent->getModbusBit      = getTSBigModbusBit;//получить содержимое бита
  tsbigcomponent->setModbusRegister = setTSBigModbusRegister;//получить содержимое регистра
  tsbigcomponent->setModbusBit      = setTSBigModbusBit;//получить содержимое бита

  tsbigcomponent->setCountObject  = setTSBigCountObject;//записать к-во обектов
  tsbigcomponent->preReadAction   = preTSBigReadAction;//action до чтения
  tsbigcomponent->postReadAction  = postTSBigReadAction;//action после чтения
  tsbigcomponent->preWriteAction  = preTSBigWriteAction;//action до записи
  tsbigcomponent->postWriteAction = postTSBigWriteAction;//action после записи

  tsbigcomponent->isActiveActualData = 0;
}//prepareDVinConfig

void loadTSBigActualData() {
  //ActualData
  for(int i=0; i<100; i++) tempReadArray[i] = i;
}//loadActualData() 

int getTSBigModbusRegister(int adrReg)
{
  //получить содержимое регистра
  if(privateTSBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(privateTSBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  if(tsbigcomponent->isActiveActualData) loadTSBigActualData(); //ActualData
  tsbigcomponent->isActiveActualData = 0;

  superSetOperativMarker(tsbigcomponent, adrReg);

  return tempReadArray[adrReg-BEGIN_ADR_REGISTER];
}//getDOUTBigModbusRegister(int adrReg)
int getTSBigModbusBit(int adrBit)
{
  //получить содержимое регистра
  superSetOperativMarker(tsbigcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setTSBigModbusRegister(int adrReg, int dataReg)
{
  //записать содержимое регистра
  if(privateTSBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(privateTSBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  superSetOperativMarker(tsbigcomponent, adrReg);
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
int setTSBigModbusBit(int adrBit, int )
{
  //получить содержимое регистра
  superSetOperativMarker(tsbigcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void setTSBigCountObject(int cntObj) {
//записать к-во обектов
  if(cntObj<0) return;
  if(cntObj>=TOTAL_OBJ) return;
  tsbigcomponent->countObject = cntObj;
}//
void preTSBigReadAction() {
//action до чтения
  tsbigcomponent->operativMarker[0] = -1;
  tsbigcomponent->operativMarker[1] = -1;//оперативный маркер
  tsbigcomponent->isActiveActualData = 1;
}//
void postTSBigReadAction() {
//action после чтения
  if(tsbigcomponent->operativMarker[0]<0) return;//не было чтения
}//
void preTSBigWriteAction() {
//action до записи
  tsbigcomponent->operativMarker[0] = -1;
  tsbigcomponent->operativMarker[1] = -1;//оперативный маркер
  tsbigcomponent->isActiveActualData = 1;
}//
void postTSBigWriteAction() {
//action после записи
  if(tsbigcomponent->operativMarker[0]<0) return;//не было записи
  int offset = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//найти смещение TempWriteArray
  int countRegister = tsbigcomponent->operativMarker[1]-tsbigcomponent->operativMarker[0]+1;
  if(tsbigcomponent->operativMarker[1]<0) countRegister = 1;
}//

int privateTSBigGetReg1(int adrReg)
{
  //проверить внутренний периметр
  int count_register = tsbigcomponent->countObject*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg1(int adrReg)
int privateTSBigGetReg2(int adrReg)
{
  //проверить внешний периметр
  int count_register = TOTAL_OBJ*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
