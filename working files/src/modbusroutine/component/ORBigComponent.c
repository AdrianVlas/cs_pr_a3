#include "variables_external_m.h"

//начальный регистр в карте памяти
#define BEGIN_ADR_REGISTER 9299
//макс к-во обектов
#define TOTAL_OBJ 128
#define REGISTER_FOR_OBJ 16

int privateORBigGetReg1(int adrReg);
int privateORBigGetReg2(int adrReg);

int getORBigModbusRegister(int);//получить содержимое регистра
int getORBigModbusBit(int);//получить содержимое бита
int setORBigModbusRegister(int, int);//получить содержимое регистра
int setORBigModbusBit(int, int);//получить содержимое бита

void setORBigCountObject(int);//записать к-во обектов
void preORBigReadAction();//action до чтения
void postORBigReadAction();//action после чтения
void preORBigWriteAction();//action до записи
void postORBigWriteAction();//action после записи
void loadORBigActualData();

COMPONENT_OBJ *orbigcomponent;

/**************************************/
//подготовка компонента OR
/**************************************/
void constructorORBigComponent(COMPONENT_OBJ *orbigcomp)
{
  orbigcomponent = orbigcomp;

  orbigcomponent->countObject = 0;//к-во обектов

  orbigcomponent->getModbusRegister = getORBigModbusRegister;//получить содержимое регистра
  orbigcomponent->getModbusBit      = getORBigModbusBit;//получить содержимое бита
  orbigcomponent->setModbusRegister = setORBigModbusRegister;//получить содержимое регистра
  orbigcomponent->setModbusBit      = setORBigModbusBit;//получить содержимое бита

  orbigcomponent->setCountObject  = setORBigCountObject;//записать к-во обектов
  orbigcomponent->preReadAction   = preORBigReadAction;//action до чтения
  orbigcomponent->postReadAction  = postORBigReadAction;//action после чтения
  orbigcomponent->preWriteAction  = preORBigWriteAction;//action до записи
  orbigcomponent->postWriteAction = postORBigWriteAction;//action после записи

  orbigcomponent->isActiveActualData = 0;
}//prepareDVinConfig

void loadORBigActualData() {
  //ActualData
  for(int i=0; i<100; i++) tempReadArray[i] = i;
}//loadActualData() 

int getORBigModbusRegister(int adrReg)
{
  //получить содержимое регистра
  if(privateORBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(privateORBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  if(orbigcomponent->isActiveActualData) loadORBigActualData(); //ActualData
  orbigcomponent->isActiveActualData = 0;

  superSetOperativMarker(orbigcomponent, adrReg);

  return tempReadArray[adrReg-BEGIN_ADR_REGISTER];
}//getDOUTBigModbusRegister(int adrReg)
int getORBigModbusBit(int adrReg)
{
  //получить содержимое регистра
  superSetOperativMarker(orbigcomponent, adrReg);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setORBigModbusRegister(int adrReg, int dataReg)
{
  //записать содержимое регистра
  if(privateORBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(privateORBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  superSetOperativMarker(orbigcomponent, adrReg);
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
}//getDOUTBigModbusRegister(int adrReg)
int setORBigModbusBit(int adrBit, int )
{
  //получить содержимое регистра
  superSetOperativMarker(orbigcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void setORBigCountObject(int cntObj) {
//записать к-во обектов
  if(cntObj<0) return;
  if(cntObj>=TOTAL_OBJ) return;
  orbigcomponent->countObject = cntObj;
}//
void preORBigReadAction() {
//action до чтения
  orbigcomponent->operativMarker[0] = -1;
  orbigcomponent->operativMarker[1] = -1;//оперативный маркер
  orbigcomponent->isActiveActualData = 1;
}//
void postORBigReadAction() {
//action после чтения
  if(orbigcomponent->operativMarker[0]<0) return;//не было чтения
}//
void preORBigWriteAction() {
//action до записи
  orbigcomponent->operativMarker[0] = -1;
  orbigcomponent->operativMarker[1] = -1;//оперативный маркер
  orbigcomponent->isActiveActualData = 1;
}//
void postORBigWriteAction() {
//action после записи
  if(orbigcomponent->operativMarker[0]<0) return;//не было записи
  int offset = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//найти смещение TempWriteArray
  int countRegister = orbigcomponent->operativMarker[1]-orbigcomponent->operativMarker[0]+1;
  if(orbigcomponent->operativMarker[1]<0) countRegister = 1;
}//

int privateORBigGetReg1(int adrReg)
{
  //проверить внутренний периметр
  int count_register = orbigcomponent->countObject*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg1(int adrReg)
int privateORBigGetReg2(int adrReg)
{
  //проверить внешний периметр
  int count_register = TOTAL_OBJ*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
