#include "variables_external_m.h"

//начальный регистр в карте памяти
#define BEGIN_ADR_REGISTER 61968
//макс к-во обектов
#define REGISTER_FOR_OBJ 33

int privateYustBigGetReg2(int adrReg);

int getYustBigModbusRegister(int);//получить содержимое регистра
int getYustBigModbusBit(int);//получить содержимое бита
int setYustBigModbusRegister(int, int);//получить содержимое регистра
int setYustBigModbusBit(int, int);//получить содержимое бита

void setYustBigCountObject(int);//записать к-во обектов
void preYustBigReadAction();//action до чтения
void postYustBigReadAction();//action после чтения
void preYustBigWriteAction();//action до записи
void postYustBigWriteAction();//action после записи
void loadYustBigActualData();

COMPONENT_OBJ *yustbigcomponent;

/**************************************/
//подготовка компонента Юстировки
/**************************************/
void constructorYustBigComponent(COMPONENT_OBJ *yustbigcomp)
{
  yustbigcomponent = yustbigcomp;

  yustbigcomponent->countObject = 1;//к-во обектов

  yustbigcomponent->getModbusRegister = getYustBigModbusRegister;//получить содержимое регистра
  yustbigcomponent->getModbusBit      = getYustBigModbusBit;//получить содержимое бита
  yustbigcomponent->setModbusRegister = setYustBigModbusRegister;//получить содержимое регистра
  yustbigcomponent->setModbusBit      = setYustBigModbusBit;//получить содержимое бита

  yustbigcomponent->setCountObject  = setYustBigCountObject;//записать к-во обектов
  yustbigcomponent->preReadAction   = preYustBigReadAction;//action до чтения
  yustbigcomponent->postReadAction  = postYustBigReadAction;//action после чтения
  yustbigcomponent->preWriteAction  = preYustBigWriteAction;//action до записи
  yustbigcomponent->postWriteAction = postYustBigWriteAction;//action после записи

  yustbigcomponent->isActiveActualData = 0;
}//prepareDVinConfig

void loadYustBigActualData() {
  //ActualData
  for(int i=0; i<100; i++) tempReadArray[i] = i;
}//loadActualData() 

int getYustBigModbusRegister(int adrReg)
{
  //получить содержимое регистра
  if(privateYustBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  if(yustbigcomponent->isActiveActualData) loadYustBigActualData(); //ActualData
  yustbigcomponent->isActiveActualData = 0;

  superSetOperativMarker(yustbigcomponent, adrReg);

  return tempReadArray[adrReg-BEGIN_ADR_REGISTER];
}//getDOUTBigModbusRegister(int adrReg)
int getYustBigModbusBit(int adrBit)
{
  //получить содержимое регистра
  superSetOperativMarker(yustbigcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setYustBigModbusRegister(int adrReg, int dataReg)
{
  //записать содержимое регистра
  if(privateYustBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  superSetOperativMarker(yustbigcomponent, adrReg);
  superSetTempWriteArray(dataReg);//записать в буфер

  return dataReg;
}//getDOUTBigModbusRegister(int adrReg)
int setYustBigModbusBit(int adrBit, int )
{
  //записать содержимое bit
  superSetOperativMarker(yustbigcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void setYustBigCountObject(int ) {
//записать к-во обектов
}//
void preYustBigReadAction() {
//action до чтения
  yustbigcomponent->operativMarker[0] = -1;
  yustbigcomponent->operativMarker[1] = -1;//оперативный маркер
  yustbigcomponent->isActiveActualData = 1;
}//
void postYustBigReadAction() {
//action после чтения
  if(yustbigcomponent->operativMarker[0]<0) return;//не было чтения
}//
void preYustBigWriteAction() {
//action до записи
  yustbigcomponent->operativMarker[0] = -1;
  yustbigcomponent->operativMarker[1] = -1;//оперативный маркер
  yustbigcomponent->isActiveActualData = 1;
}//
void postYustBigWriteAction() {
//action после записи
  if(yustbigcomponent->operativMarker[0]<0) return;//не было записи
  int offset = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//найти смещение TempWriteArray
  int countRegister = yustbigcomponent->operativMarker[1]-yustbigcomponent->operativMarker[0]+1;
  if(yustbigcomponent->operativMarker[1]<0) countRegister = 1;
}//

int privateYustBigGetReg2(int adrReg)
{
  //проверить внешний периметр
  int count_register = REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
