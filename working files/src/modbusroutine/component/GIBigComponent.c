#include "variables_external_m.h"

//начальный регистр в карте памяти
#define BEGIN_ADR_REGISTER 4418
//макс к-во обектов
#define TOTAL_OBJ 128
#define REGISTER_FOR_OBJ 2

int privateGIBigGetReg1(int adrReg);
int privateGIBigGetReg2(int adrReg);

int getGIBigModbusRegister(int);//получить содержимое регистра
int getGIBigModbusBit(int);//получить содержимое бита
int setGIBigModbusRegister(int, int);//получить содержимое регистра
int setGIBigModbusBit(int, int);//получить содержимое бита

void setGIBigCountObject(int);//записать к-во обектов
void preGIBigReadAction();//action до чтения
void postGIBigReadAction();//action после чтения
void preGIBigWriteAction();//action до записи
void postGIBigWriteAction();//action после записи
void loadGIBigActualData();

COMPONENT_OBJ *gibigcomponent;

/**************************************/
//подготовка компонента генераторов импульсов
/**************************************/
void constructorGIBigComponent(COMPONENT_OBJ *gibigcomp)
{
  gibigcomponent = gibigcomp;

  gibigcomponent->countObject = 0;//к-во обектов

  gibigcomponent->getModbusRegister = getGIBigModbusRegister;//получить содержимое регистра
  gibigcomponent->getModbusBit      = getGIBigModbusBit;//получить содержимое бита
  gibigcomponent->setModbusRegister = setGIBigModbusRegister;//получить содержимое регистра
  gibigcomponent->setModbusBit      = setGIBigModbusBit;//получить содержимое бита

  gibigcomponent->setCountObject  = setGIBigCountObject;//записать к-во обектов
  gibigcomponent->preReadAction   = preGIBigReadAction;//action до чтения
  gibigcomponent->postReadAction  = postGIBigReadAction;//action после чтения
  gibigcomponent->preWriteAction  = preGIBigWriteAction;//action до записи
  gibigcomponent->postWriteAction = postGIBigWriteAction;//action после записи

  gibigcomponent->isActiveActualData = 0;
}//prepareDVinConfig

void loadGIBigActualData() {
  //ActualData
  for(int i=0; i<100; i++) tempReadArray[i] = i;
}//loadActualData() 

int getGIBigModbusRegister(int adrReg)
{
  //получить содержимое регистра
  if(privateGIBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(privateGIBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  if(gibigcomponent->isActiveActualData) loadGIBigActualData(); //ActualData
  gibigcomponent->isActiveActualData = 0;

  superSetOperativMarker(gibigcomponent, adrReg);

  return tempReadArray[adrReg-BEGIN_ADR_REGISTER];
}//getDOUTBigModbusRegister(int adrReg)
int getGIBigModbusBit(int adrBit)
{
  //получить содержимое регистра
  superSetOperativMarker(gibigcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setGIBigModbusRegister(int adrReg, int dataReg)
{
  //записать содержимое регистра
  if(privateGIBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(privateGIBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  superSetOperativMarker(gibigcomponent, adrReg);
  superSetTempWriteArray(dataReg);//записать в буфер

  switch((adrReg-BEGIN_ADR_REGISTER)%REGISTER_FOR_OBJ) {
   case 0:
   return dataReg;
   case 1:
    if(dataReg>100) return MARKER_ERRORDIAPAZON;
    if(dataReg<5) return MARKER_ERRORDIAPAZON;
    return dataReg;
  }//switch
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setGIBigModbusBit(int adrBit, int )
{
  //получить содержимое регистра
  superSetOperativMarker(gibigcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void setGIBigCountObject(int cntObj) {
//записать к-во обектов
  if(cntObj<0) return;
  if(cntObj>=TOTAL_OBJ) return;
  gibigcomponent->countObject = cntObj;
}//
void preGIBigReadAction() {
//action до чтения
  gibigcomponent->operativMarker[0] = -1;
  gibigcomponent->operativMarker[1] = -1;//оперативный маркер
  gibigcomponent->isActiveActualData = 1;
}//
void postGIBigReadAction() {
//action после чтения
  if(gibigcomponent->operativMarker[0]<0) return;//не было чтения
}//
void preGIBigWriteAction() {
//action до записи
  gibigcomponent->operativMarker[0] = -1;
  gibigcomponent->operativMarker[1] = -1;//оперативный маркер
  gibigcomponent->isActiveActualData = 1;
}//
void postGIBigWriteAction() {
//action после записи
  if(gibigcomponent->operativMarker[0]<0) return;//не было записи
  int offset = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//найти смещение TempWriteArray
  int countRegister = gibigcomponent->operativMarker[1]-gibigcomponent->operativMarker[0]+1;
  if(gibigcomponent->operativMarker[1]<0) countRegister = 1;
}//

int privateGIBigGetReg1(int adrReg)
{
  //проверить внутренний периметр
  int count_register = gibigcomponent->countObject*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg1(int adrReg)
int privateGIBigGetReg2(int adrReg)
{
  //проверить внешний периметр
  int count_register = TOTAL_OBJ*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
