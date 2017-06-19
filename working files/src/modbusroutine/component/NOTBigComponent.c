#include "variables_external_m.h"

//начальный регистр в карте памяти
#define BEGIN_ADR_REGISTER 10589
//макс к-во обектов
#define TOTAL_OBJ 128
#define REGISTER_FOR_OBJ 2

int privateNOTBigGetReg1(int adrReg);
int privateNOTBigGetReg2(int adrReg);

int getNOTBigModbusRegister(int);//получить содержимое регистра
int getNOTBigModbusBit(int);//получить содержимое бита
int setNOTBigModbusRegister(int, int);//получить содержимое регистра
int setNOTBigModbusBit(int, int);//получить содержимое бита

void setNOTBigCountObject(int);//записать к-во обектов
void preNOTBigReadAction();//action до чтения
void postNOTBigReadAction();//action после чтения
void preNOTBigWriteAction();//action до записи
void postNOTBigWriteAction();//action после записи
void loadNOTBigActualData();

COMPONENT_OBJ *notbigcomponent;

/**************************************/
//подготовка компонента NOT
/**************************************/
void constructorNOTBigComponent(COMPONENT_OBJ *notbigcomp)
{
  notbigcomponent = notbigcomp;

  notbigcomponent->countObject = 0;//к-во обектов

  notbigcomponent->getModbusRegister = getNOTBigModbusRegister;//получить содержимое регистра
  notbigcomponent->getModbusBit      = getNOTBigModbusBit;//получить содержимое бита
  notbigcomponent->setModbusRegister = setNOTBigModbusRegister;//получить содержимое регистра
  notbigcomponent->setModbusBit      = setNOTBigModbusBit;//получить содержимое бита

  notbigcomponent->setCountObject  = setNOTBigCountObject;//записать к-во обектов
  notbigcomponent->preReadAction   = preNOTBigReadAction;//action до чтения
  notbigcomponent->postReadAction  = postNOTBigReadAction;//action после чтения
  notbigcomponent->preWriteAction  = preNOTBigWriteAction;//action до записи
  notbigcomponent->postWriteAction = postNOTBigWriteAction;//action после записи

  notbigcomponent->isActiveActualData = 0;
}//prepareDVinConfig

void loadNOTBigActualData() {
  //ActualData
  for(int i=0; i<100; i++) tempReadArray[i] = i;
}//loadActualData() 

int getNOTBigModbusRegister(int adrReg)
{
  //получить содержимое регистра
  if(privateNOTBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(privateNOTBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  if(notbigcomponent->isActiveActualData) loadNOTBigActualData(); //ActualData
  notbigcomponent->isActiveActualData = 0;

  superSetOperativMarker(notbigcomponent, adrReg);

  return tempReadArray[adrReg-BEGIN_ADR_REGISTER];
}//getDOUTBigModbusRegister(int adrReg)
int getNOTBigModbusBit(int adrBit)
{
  //получить содержимое регистра
  superSetOperativMarker(notbigcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setNOTBigModbusRegister(int adrReg, int dataReg)
{
  //записать содержимое регистра
  if(privateNOTBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(privateNOTBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  superSetOperativMarker(notbigcomponent, adrReg);
  superSetTempWriteArray(dataReg);//записать в буфер

  switch((adrReg-BEGIN_ADR_REGISTER)%REGISTER_FOR_OBJ) {
   case 0:
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
    return dataReg;
   case 1:
   return dataReg;
  }//switch
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setNOTBigModbusBit(int adrBit, int )
{
  //получить содержимое регистра
  superSetOperativMarker(notbigcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void setNOTBigCountObject(int cntObj) {
//записать к-во обектов
  if(cntObj<0) return;
  if(cntObj>=TOTAL_OBJ) return;
  notbigcomponent->countObject = cntObj;
}//
void preNOTBigReadAction() {
//action до чтения
  notbigcomponent->operativMarker[0] = -1;
  notbigcomponent->operativMarker[1] = -1;//оперативный маркер
  notbigcomponent->isActiveActualData = 1;
}//
void postNOTBigReadAction() {
//action после чтения
  if(notbigcomponent->operativMarker[0]<0) return;//не было чтения
}//
void preNOTBigWriteAction() {
//action до записи
  notbigcomponent->operativMarker[0] = -1;
  notbigcomponent->operativMarker[1] = -1;//оперативный маркер
  notbigcomponent->isActiveActualData = 1;
}//
void postNOTBigWriteAction() {
//action после записи
  if(notbigcomponent->operativMarker[0]<0) return;//не было записи
  int offset = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//найти смещение TempWriteArray
  int countRegister = notbigcomponent->operativMarker[1]-notbigcomponent->operativMarker[0]+1;
  if(notbigcomponent->operativMarker[1]<0) countRegister = 1;
}//

int privateNOTBigGetReg1(int adrReg)
{
  //проверить внутренний периметр
  int count_register = notbigcomponent->countObject*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg1(int adrReg)
int privateNOTBigGetReg2(int adrReg)
{
  //проверить внешний периметр
  int count_register = TOTAL_OBJ*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
