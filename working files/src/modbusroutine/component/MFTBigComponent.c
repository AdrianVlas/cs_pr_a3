#include "header.h"

//начальный регистр в карте памяти
#define BEGIN_ADR_REGISTER 5966
//макс к-во обектов
#define TOTAL_OBJ 128
#define REGISTER_FOR_OBJ 6

int privateMFTBigGetReg1(int adrReg);
int privateMFTBigGetReg2(int adrReg);

int getMFTBigModbusRegister(int);//получить содержимое регистра
int getMFTBigModbusBit(int);//получить содержимое бита
int setMFTBigModbusRegister(int, int);//получить содержимое регистра
int setMFTBigModbusBit(int, int);//получить содержимое бита

void setMFTBigCountObject(int);//записать к-во обектов
void preMFTBigReadAction(void);//action до чтения
void postMFTBigReadAction(void);//action после чтения
void preMFTBigWriteAction(void);//action до записи
void postMFTBigWriteAction(void);//action после записи
void loadMFTBigActualData(void);

COMPONENT_OBJ *mftbigcomponent;

/**************************************/
//подготовка компонента МФТ
/**************************************/
void constructorMFTBigComponent(COMPONENT_OBJ *mftbigcomp)
{
  mftbigcomponent = mftbigcomp;

  mftbigcomponent->countObject = 128;//к-во обектов

  mftbigcomponent->getModbusRegister = getMFTBigModbusRegister;//получить содержимое регистра
  mftbigcomponent->getModbusBit      = getMFTBigModbusBit;//получить содержимое бита
  mftbigcomponent->setModbusRegister = setMFTBigModbusRegister;//получить содержимое регистра
  mftbigcomponent->setModbusBit      = setMFTBigModbusBit;//получить содержимое бита

  mftbigcomponent->setCountObject  = setMFTBigCountObject;//записать к-во обектов
  mftbigcomponent->preReadAction   = preMFTBigReadAction;//action до чтения
  mftbigcomponent->postReadAction  = postMFTBigReadAction;//action после чтения
  mftbigcomponent->preWriteAction  = preMFTBigWriteAction;//action до записи
  mftbigcomponent->postWriteAction = postMFTBigWriteAction;//action после записи

  mftbigcomponent->isActiveActualData = 0;
}//prepareDVinConfig

void loadMFTBigActualData(void) {
  //ActualData
  for(int i=0; i<100; i++) tempReadArray[i] = i;
}//loadActualData() 

int getMFTBigModbusRegister(int adrReg)
{
  //получить содержимое регистра
  if(privateMFTBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(privateMFTBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  if(mftbigcomponent->isActiveActualData) loadMFTBigActualData(); //ActualData
  mftbigcomponent->isActiveActualData = 0;

  superSetOperativMarker(mftbigcomponent, adrReg);

  return tempReadArray[adrReg-BEGIN_ADR_REGISTER];
}//getDOUTBigModbusRegister(int adrReg)
int getMFTBigModbusBit(int adrBit)
{
  //получить содержимое регистра
  superSetOperativMarker(mftbigcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setMFTBigModbusRegister(int adrReg, int dataReg)
{
  //записать содержимое регистра
  if(privateMFTBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(privateMFTBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  superSetOperativMarker(mftbigcomponent, adrReg);
  superSetTempWriteArray(dataReg);//записать в буфер

  switch((adrReg-BEGIN_ADR_REGISTER)%REGISTER_FOR_OBJ) {
   case 0:
    if(dataReg>60000) return MARKER_ERRORDIAPAZON;
    return dataReg;
   case 1:
    if(dataReg>60000) return MARKER_ERRORDIAPAZON;
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
  }//switch
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setMFTBigModbusBit(int adrBit, int x)
{
  UNUSED(x);
  //получить содержимое регистра
  superSetOperativMarker(mftbigcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void setMFTBigCountObject(int cntObj) {
//записать к-во обектов
  if(cntObj<0) return;
  if(cntObj>=TOTAL_OBJ) return;
  mftbigcomponent->countObject = cntObj;
}//
void preMFTBigReadAction(void) {
//action до чтения
  mftbigcomponent->operativMarker[0] = -1;
  mftbigcomponent->operativMarker[1] = -1;//оперативный маркер
  mftbigcomponent->isActiveActualData = 1;
}//
void postMFTBigReadAction(void) {
//action после чтения
  if(mftbigcomponent->operativMarker[0]<0) return;//не было чтения
}//
void preMFTBigWriteAction(void) {
//action до записи
  mftbigcomponent->operativMarker[0] = -1;
  mftbigcomponent->operativMarker[1] = -1;//оперативный маркер
  mftbigcomponent->isActiveActualData = 1;
}//
void postMFTBigWriteAction(void) {
//action после записи
  if(mftbigcomponent->operativMarker[0]<0) return;//не было записи
  int offset = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//найти смещение TempWriteArray
  int countRegister = mftbigcomponent->operativMarker[1]-mftbigcomponent->operativMarker[0]+1;
  if(mftbigcomponent->operativMarker[1]<0) countRegister = 1;
}//

int privateMFTBigGetReg1(int adrReg)
{
  //проверить внутренний периметр
  int count_register = mftbigcomponent->countObject*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg1(int adrReg)
int privateMFTBigGetReg2(int adrReg)
{
  //проверить внешний периметр
  int count_register = TOTAL_OBJ*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
