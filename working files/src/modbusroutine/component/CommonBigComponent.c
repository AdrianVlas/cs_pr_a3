#include "variables_external_m.h"

//начальный регистр в карте памяти
#define BEGIN_ADR_REGISTER 10718
//макс к-во обектов
#define REGISTER_FOR_OBJ 10

int privateCommonBigGetReg2(int adrReg);

int getCommonBigModbusRegister(int);//получить содержимое регистра
int getCommonBigModbusBit(int);//получить содержимое бита
int setCommonBigModbusRegister(int, int);// регистра
int setCommonBigModbusBit(int, int);// бита

void setCommonBigCountObject(int);//записать к-во обектов
void preCommonBigReadAction();//action до чтения
void postCommonBigReadAction();//action после чтения
void preCommonBigWriteAction();//action до записи
void postCommonBigWriteAction();//action после записи
void loadCommonBigActualData();

COMPONENT_OBJ *commonbigcomponent;

/**************************************/
//подготовка компонента Общие
/**************************************/
void constructorCommonBigComponent(COMPONENT_OBJ *commonbigcomp)
{
  commonbigcomponent = commonbigcomp;

  commonbigcomponent->countObject = 1;//к-во обектов

  commonbigcomponent->getModbusRegister = getCommonBigModbusRegister;//получить содержимое регистра
  commonbigcomponent->getModbusBit      = getCommonBigModbusBit;//получить содержимое бита
  commonbigcomponent->setModbusRegister = setCommonBigModbusRegister;//регистра
  commonbigcomponent->setModbusBit      = setCommonBigModbusBit;// бита

  commonbigcomponent->setCountObject  = setCommonBigCountObject;//записать к-во обектов
  commonbigcomponent->preReadAction   = preCommonBigReadAction;//action до чтения
  commonbigcomponent->postReadAction  = postCommonBigReadAction;//action после чтения
  commonbigcomponent->preWriteAction  = preCommonBigWriteAction;//action до записи
  commonbigcomponent->postWriteAction = postCommonBigWriteAction;//action после записи

  commonbigcomponent->isActiveActualData = 0;
}//prepareDVinConfig

void loadCommonBigActualData() {
  //ActualData
  for(int i=0; i<100; i++) tempReadArray[i] = i;
}//loadActualData() 

int getCommonBigModbusRegister(int adrReg)
{
  //получить содержимое регистра
  if(privateCommonBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  if(commonbigcomponent->isActiveActualData) loadCommonBigActualData(); //ActualData
  commonbigcomponent->isActiveActualData = 0;

  superSetOperativMarker(commonbigcomponent, adrReg);

  return tempReadArray[adrReg-BEGIN_ADR_REGISTER];
}//getDOUTBigModbusRegister(int adrReg)
int getCommonBigModbusBit(int adrBit)
{
  //получить содержимое bit
  superSetOperativMarker(commonbigcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setCommonBigModbusRegister(int adrReg, int dataReg)
{
  //записать содержимое регистра
  if(privateCommonBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  superSetOperativMarker(commonbigcomponent, adrReg);
  superSetTempWriteArray(dataReg);//записать в буфер

  switch((adrReg-BEGIN_ADR_REGISTER)%REGISTER_FOR_OBJ) {
   case 0:
   return dataReg;
   case 1:
   return dataReg;
   case 2:
   return dataReg;
   case 3:
   return dataReg;
   case 4:
   return dataReg;
   case 5:
   return dataReg;
   case 6:
   return dataReg;
   case 7:
   return dataReg;
   case 8:
   return dataReg;
   case 9:
   return dataReg;
  }//switch
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setCommonBigModbusBit(int adrBit, int )
{
  //получить содержимое регистра
  superSetOperativMarker(commonbigcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void setCommonBigCountObject(int) {
//записать к-во обектов
}//
void preCommonBigReadAction() {
//action до чтения
  commonbigcomponent->operativMarker[0] = -1;
  commonbigcomponent->operativMarker[1] = -1;//оперативный маркер
  commonbigcomponent->isActiveActualData = 1;
}//
void postCommonBigReadAction() {
//action после чтения
  if(commonbigcomponent->operativMarker[0]<0) return;//не было чтения
}//
void preCommonBigWriteAction() {
//action до записи
  commonbigcomponent->operativMarker[0] = -1;
  commonbigcomponent->operativMarker[1] = -1;//оперативный маркер
  commonbigcomponent->isActiveActualData = 1;
}//
void postCommonBigWriteAction() {
//action после записи
  if(commonbigcomponent->operativMarker[0]<0) return;//не было записи
  int offset = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//найти смещение TempWriteArray
  int countRegister = commonbigcomponent->operativMarker[1]-commonbigcomponent->operativMarker[0]+1;
  if(commonbigcomponent->operativMarker[1]<0) countRegister = 1;
}//

int privateCommonBigGetReg2(int adrReg)
{
  //проверить внешний периметр
  int count_register = REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
