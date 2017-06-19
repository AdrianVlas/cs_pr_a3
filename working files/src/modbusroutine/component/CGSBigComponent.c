#include "header.h"

//начальный регистр в карте памяти
#define BEGIN_ADR_REGISTER 5954
//макс к-во обектов
#define REGISTER_FOR_OBJ 3

int privateCGSBigGetReg2(int adrReg);

int getCGSBigModbusRegister(int);//получить содержимое регистра
int getCGSBigModbusBit(int);//получить содержимое бита
int setCGSBigModbusRegister(int, int);// регистра
int setCGSBigModbusBit(int, int);// бита

void setCGSBigCountObject(int);//записать к-во обектов
void preCGSBigReadAction(void);//action до чтения
void postCGSBigReadAction(void);//action после чтения
void preCGSBigWriteAction(void);//action до записи
void postCGSBigWriteAction(void);//action после записи
void loadCGSBigActualData(void);

COMPONENT_OBJ *cgsbigcomponent;
/**************************************/
//подготовка компонента ШГС
/**************************************/
void constructorCGSBigComponent(COMPONENT_OBJ *cgsbigcomp)
{
  cgsbigcomponent = cgsbigcomp;

  cgsbigcomponent->countObject = 4;//к-во обектов

  cgsbigcomponent->getModbusRegister = getCGSBigModbusRegister;//получить содержимое регистра
  cgsbigcomponent->getModbusBit      = getCGSBigModbusBit;//получить содержимое бита
  cgsbigcomponent->setModbusRegister = setCGSBigModbusRegister;//регистра
  cgsbigcomponent->setModbusBit      = setCGSBigModbusBit;// бита

  cgsbigcomponent->setCountObject  = setCGSBigCountObject;//записать к-во обектов
  cgsbigcomponent->preReadAction   = preCGSBigReadAction;//action до чтения
  cgsbigcomponent->postReadAction  = postCGSBigReadAction;//action после чтения
  cgsbigcomponent->preWriteAction  = preCGSBigWriteAction;//action до записи
  cgsbigcomponent->postWriteAction = postCGSBigWriteAction;//action после записи

  cgsbigcomponent->isActiveActualData = 0;
}//prepareDVinConfig

void loadCGSBigActualData(void) {
  //ActualData
  for(int i=0; i<100; i++) tempReadArray[i] = i;
}//loadActualData() 

int getCGSBigModbusRegister(int adrReg)
{
  //получить содержимое регистра
  if(privateCGSBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  if(cgsbigcomponent->isActiveActualData) loadCGSBigActualData(); //ActualData
  cgsbigcomponent->isActiveActualData = 0;

  superSetOperativMarker(cgsbigcomponent, adrReg);

  return tempReadArray[adrReg-BEGIN_ADR_REGISTER];
}//getDOUTBigModbusRegister(int adrReg)
int getCGSBigModbusBit(int adrBit)
{
  //получить содержимое регистра
  superSetOperativMarker(cgsbigcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setCGSBigModbusRegister(int adrReg, int dataReg)
{
  //записать содержимое регистра
  if(privateCGSBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  superSetOperativMarker(cgsbigcomponent, adrReg);
  superSetTempWriteArray(dataReg);//записать в буфер

  switch((adrReg-BEGIN_ADR_REGISTER)%REGISTER_FOR_OBJ) {
   case 0:
    return dataReg;
   case 1:
    if(dataReg>500) return MARKER_ERRORDIAPAZON;
    if(dataReg<5)   return MARKER_ERRORDIAPAZON;
    return dataReg;
   case 2:
    if(dataReg>320) return MARKER_ERRORDIAPAZON;
   return dataReg;
  }//switch
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setCGSBigModbusBit(int adrBit, int x)
{
  UNUSED(x);
  //получить содержимое регистра
  superSetOperativMarker(cgsbigcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void setCGSBigCountObject(int x) {
  UNUSED(x);
//записать к-во обектов
}//
void preCGSBigReadAction(void) {
//action до чтения
  cgsbigcomponent->operativMarker[0] = -1;
  cgsbigcomponent->operativMarker[1] = -1;//оперативный маркер
  cgsbigcomponent->isActiveActualData = 1;
}//
void postCGSBigReadAction(void) {
//action после чтения
  if(cgsbigcomponent->operativMarker[0]<0) return;//не было чтения
}//
void preCGSBigWriteAction(void) {
//action до записи
  cgsbigcomponent->operativMarker[0] = -1;
  cgsbigcomponent->operativMarker[1] = -1;//оперативный маркер
  cgsbigcomponent->isActiveActualData = 1;
}//
void postCGSBigWriteAction(void) {
//action после записи
  if(cgsbigcomponent->operativMarker[0]<0) return;//не было записи
  int offset = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//найти смещение TempWriteArray
  int countRegister = cgsbigcomponent->operativMarker[1]-cgsbigcomponent->operativMarker[0]+1;
  if(cgsbigcomponent->operativMarker[1]<0) countRegister = 1;
}//

int privateCGSBigGetReg2(int adrReg)
{
  //проверить внешний периметр
  int count_register = cgsbigcomponent->countObject*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
