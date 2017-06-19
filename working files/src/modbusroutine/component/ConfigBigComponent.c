#include "variables_external_m.h"

//начальный регистр в карте памяти
#define BEGIN_ADR_REGISTER 800
#define REGISTER_FOR_OBJ 15

int getConfigBigModbusRegister(int);//получить содержимое регистра
int getConfigBigModbusBit(int);//получить содержимое бита
int setConfigBigModbusRegister(int, int);// регистра
int setConfigBigModbusBit(int, int);// бита
int privateConfigBigGetReg2(int adrReg);

void setConfigBigCountObject(int);//записать к-во обектов
void preConfigBigReadAction();//action до чтения
void postConfigBigReadAction();//action после чтения
void preConfigBigWriteAction();//action до записи
void postConfigBigWriteAction();//action после записи
void loadConfigBigActualData();

COMPONENT_OBJ *configbigcomponent;

/**************************************/
//подготовка компонента ДВ
/**************************************/
void constructorConfigBigComponent(COMPONENT_OBJ *configbigcomp)
{
  configbigcomponent = configbigcomp;

  configbigcomponent->countObject = 1;//к-во обектов

  configbigcomponent->getModbusRegister = getConfigBigModbusRegister;//получить содержимое регистра
  configbigcomponent->getModbusBit      = getConfigBigModbusBit;//получить содержимое бита
  configbigcomponent->setModbusRegister = setConfigBigModbusRegister;//егистра
  configbigcomponent->setModbusBit      = setConfigBigModbusBit;// бита

  configbigcomponent->setCountObject  = setConfigBigCountObject;//записать к-во обектов
  configbigcomponent->preReadAction   = preConfigBigReadAction;//action до чтения
  configbigcomponent->postReadAction  = postConfigBigReadAction;//action после чтения
  configbigcomponent->preWriteAction  = preConfigBigWriteAction;//action до записи
  configbigcomponent->postWriteAction = postConfigBigWriteAction;//action после записи

  configbigcomponent->isActiveActualData = 0;
}//constructorConfigBigComponent(COMPONENT_OBJ *configbigcomp)

void loadConfigBigActualData() {
  //ActualData
  for(int i=0; i<100; i++) tempReadArray[i] = i;
}//loadActualData() 

int getConfigBigModbusRegister(int adrReg)
{
  //получить содержимое регистра
  if(privateConfigBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  if(configbigcomponent->isActiveActualData) loadConfigBigActualData(); //ActualData
  configbigcomponent->isActiveActualData = 0;

  superSetOperativMarker(configbigcomponent, adrReg);

  return tempReadArray[adrReg-BEGIN_ADR_REGISTER];
}//getDVModbusRegister(int adrReg)
int getConfigBigModbusBit(int adrBit)
{
  //получить содержимое регистра
  superSetOperativMarker(configbigcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDVModbusRegister(int adrReg)
int setConfigBigModbusRegister(int adrReg, int dataReg)
{
  //записать содержимое регистра
/*
  extern COMPONENT_OBJ *andbigcomponent;
  extern COMPONENT_OBJ *orbigcomponent;
  extern COMPONENT_OBJ *xorbigcomponent;
  extern COMPONENT_OBJ *notbigcomponent;
  extern COMPONENT_OBJ *dtrbigcomponent;
  extern COMPONENT_OBJ *gibigcomponent;
  extern COMPONENT_OBJ *mftbigcomponent;
  extern COMPONENT_OBJ *szsbigcomponent;
  extern COMPONENT_OBJ *cgsbigcomponent;
  extern COMPONENT_OBJ *tsbigcomponent;
  extern COMPONENT_OBJ *tssmallcomponent;
  extern COMPONENT_OBJ *tubigcomponent;
  extern COMPONENT_OBJ *tusmallcomponent;
*/
  if(privateConfigBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  superSetOperativMarker(configbigcomponent, adrReg);
  superSetTempWriteArray(dataReg);//записать в буфер
  if(dataReg>127) return MARKER_ERRORDIAPAZON;
  return dataReg;
/*
  if(dataReg>127) return MARKER_ERRORDIAPAZON;
  switch(adrReg-BEGIN_ADR_REGISTER) {
   case 0:
    andbigcomponent->setCountObject(dataReg);
   return dataReg;
   case 1:
    orbigcomponent->setCountObject(dataReg);
   return dataReg;
   case 2:
    xorbigcomponent->setCountObject(dataReg);
   return dataReg;
   case 3:
    notbigcomponent->setCountObject(dataReg);
   return dataReg;
   case 4:
    dtrbigcomponent->setCountObject(dataReg);
   return dataReg;
   case 5:
    gibigcomponent->setCountObject(dataReg);
   return dataReg;
   case 6:
    mftbigcomponent->setCountObject(dataReg);
   return dataReg;
   case 7:
    szsbigcomponent->setCountObject(dataReg);
   return dataReg;
   case 8:
    cgsbigcomponent->setCountObject(dataReg);
   return dataReg;
   case 9:
    tssmallcomponent->setCountObject(dataReg);
    tsbigcomponent->setCountObject(dataReg);
   return dataReg;
   case 10:
    tusmallcomponent->setCountObject(dataReg);
    tubigcomponent->setCountObject(dataReg);
   return dataReg;
   case 11:
   return dataReg;
   case 12:
   return dataReg;
   case 13:
   return dataReg;
   case 14:
   return dataReg;
  }//switch
  return MARKER_OUTPERIMETR;
*/
}//getDVModbusRegister(int adrReg)
int setConfigBigModbusBit(int adrBit, int )
{
  //записать содержимое bit
  superSetOperativMarker(configbigcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDVModbusRegister(int adrReg)

void setConfigBigCountObject(int) {
//записать к-во обектов
}//
void preConfigBigReadAction() {
//action до чтения
  configbigcomponent->operativMarker[0] = -1;
  configbigcomponent->operativMarker[1] = -1;//оперативный маркер
  configbigcomponent->isActiveActualData = 1;
}//
void postConfigBigReadAction() {
//action после чтения
  if(configbigcomponent->operativMarker[0]<0) return;//не было чтения
}//
void preConfigBigWriteAction() {
//action до записи
  configbigcomponent->operativMarker[0] = -1;
  configbigcomponent->operativMarker[1] = -1;//оперативный маркер
  configbigcomponent->isActiveActualData = 1;
}//
void postConfigBigWriteAction() {
//action после записи
  if(configbigcomponent->operativMarker[0]<0) return;//не было записи
  int offset = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//найти смещение TempWriteArray
  int countRegister = configbigcomponent->operativMarker[1]-configbigcomponent->operativMarker[0]+1;
  if(configbigcomponent->operativMarker[1]<0) countRegister = 1;
}//

int privateConfigBigGetReg2(int adrReg)
{
  //проверить внешний периметр
  int count_register = REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
