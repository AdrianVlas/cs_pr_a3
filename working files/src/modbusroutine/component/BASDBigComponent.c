#include "header.h"

//начальный регистр в карте памяти
#define BEGIN_ADR_REGISTER 4413
#define REGISTER_FOR_OBJ 6

int getBASDBigModbusRegister(int);//получить содержимое регистра
int getBASDBigModbusBit(int);//получить содержимое Бита
int setBASDBigModbusRegister(int, int);//регистра
int setBASDBigModbusBit(int, int);// Бита
int privateBASDBigGetReg2(int adrReg);

void setBASDBigCountObject(void);
void preBASDBigReadAction(void);//action до чтения
void postBASDBigReadAction(void);//action после чтения
void preBASDBigWriteAction(void);//action до записи
void postBASDBigWriteAction(void);//action после записи
void loadBASDBigActualData(void);

COMPONENT_OBJ *basdbigcomponent;
/**************************************/
//подготовка компонента маркерных светоиндикаторов block\alarm
/**************************************/
void constructorBASDBigComponent(COMPONENT_OBJ *basdbigcomp)
{
  basdbigcomponent = basdbigcomp;

  basdbigcomponent->countObject = 1;//к-во обектов

  basdbigcomponent->getModbusRegister = getBASDBigModbusRegister;//получить содержимое регистра
  basdbigcomponent->getModbusBit      = getBASDBigModbusBit;//получить содержимое бита
  basdbigcomponent->setModbusRegister = setBASDBigModbusRegister;// регистра
  basdbigcomponent->setModbusBit      = setBASDBigModbusBit;//бита

  basdbigcomponent->preReadAction   = preBASDBigReadAction;//action до чтения
  basdbigcomponent->postReadAction  = postBASDBigReadAction;//action после чтения
  basdbigcomponent->preWriteAction  = preBASDBigWriteAction;//action до записи
  basdbigcomponent->postWriteAction = postBASDBigWriteAction;//action после записи

  basdbigcomponent->isActiveActualData = 0;

}//prepareDVinConfig

void loadBASDBigActualData(void) {
  //ActualData
  for(int i=0; i<100; i++) tempReadArray[i] = i;
}//loadActualData() 

int getBASDBigModbusRegister(int adrReg)
{
  //получить содержимое регистра
  if(privateBASDBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  if(basdbigcomponent->isActiveActualData) loadBASDBigActualData(); //ActualData
  basdbigcomponent->isActiveActualData = 0;

  superSetOperativMarker(basdbigcomponent, adrReg);

  return tempReadArray[adrReg-BEGIN_ADR_REGISTER];
}//getDVModbusRegister(int adrReg)
int getBASDBigModbusBit(int adrBit)
{
  //получить содержимое регистра
  superSetOperativMarker(basdbigcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getBASDBigModbusBit(int adrReg)
int setBASDBigModbusRegister(int adrReg, int dataReg)
{
  //записать содержимое регистра
  if(privateBASDBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  superSetOperativMarker(basdbigcomponent, adrReg);
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
  }//switch
  return MARKER_OUTPERIMETR;
}//setDVModbusRegister(int adrReg)
int setBASDBigModbusBit(int adrBit, int x)
{
  UNUSED(x);
  //получить содержимое регистра
  superSetOperativMarker(basdbigcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getBASDBigModbusBit(int adrReg)

void setBASDBigCountObject(void) {
//записать к-во обектов
}//

void preBASDBigReadAction(void) {
//action до чтения
  basdbigcomponent->operativMarker[0] = -1;
  basdbigcomponent->operativMarker[1] = -1;//оперативный маркер
  basdbigcomponent->isActiveActualData = 1;
}//
void postBASDBigReadAction(void) {
//action после чтения
  if(basdbigcomponent->operativMarker[0]<0) return;//не было чтения
}//
void preBASDBigWriteAction(void) {
//action до записи
  basdbigcomponent->operativMarker[0] = -1;
  basdbigcomponent->operativMarker[1] = -1;//оперативный маркер
  basdbigcomponent->isActiveActualData = 1;
}//
void postBASDBigWriteAction(void) {
//action после записи
  if(basdbigcomponent->operativMarker[0]<0) return;//не было записи
//  int offset = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//найти смещение TempWriteArray
//  int countRegister = basdbigcomponent->operativMarker[1]-basdbigcomponent->operativMarker[0]+1;
//  if(basdbigcomponent->operativMarker[1]<0) countRegister = 1;
}//

int privateBASDBigGetReg2(int adrReg)
{
  //проверить внешний периметр
  int count_register = REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
