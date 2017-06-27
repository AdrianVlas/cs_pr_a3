#include "header.h"

//начальный регистр в карте пам€ти
#define BEGIN_ADR_REGISTER 4670
#define REGISTER_FOR_OBJ 6

int getBASDBigModbusRegister(int);//получить содержимое регистра
int getBASDBigModbusBit(int);//получить содержимое Ѕита
int setBASDBigModbusRegister(int, int);//регистра
int setBASDBigModbusBit(int, int);// Ѕита
int privateBASDBigGetReg2(int adrReg);

void setBASDBigCountObject(void);
void preBASDBigReadAction(void);//action до чтени€
void postBASDBigReadAction(void);//action после чтени€
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

  basdbigcomponent->preReadAction   = preBASDBigReadAction;//action до чтени€
  basdbigcomponent->postReadAction  = postBASDBigReadAction;//action после чтени€
  basdbigcomponent->preWriteAction  = preBASDBigWriteAction;//action до записи
  basdbigcomponent->postWriteAction = postBASDBigWriteAction;//action после записи

  basdbigcomponent->isActiveActualData = 0;

}//prepareDVinConfig

void loadBASDBigActualData(void) {
  //ActualData
  __SETTINGS_FIX *arr = &settings_fix_prt;

  int value;
  value = arr->param[FIX_BLOCK_BLOCK] & 0xffff;//RIN0 ƒ¬ых. item
  tempReadArray[0] = value;
  value = (arr->param[FIX_BLOCK_BLOCK] >> 16) & 0x7fff;//RIN1 ƒ¬ых. item
  tempReadArray[1] = value;

  value = arr->param[FIX_BLOCK_ALARM] & 0xffff;//RIN0 ƒ¬ых. item
  tempReadArray[2] = value;
  value = (arr->param[FIX_BLOCK_ALARM] >> 16) & 0x7fff;//RIN1 ƒ¬ых. item
  tempReadArray[3] = value;

  value = arr->param[FIX_BLOCK_MUTE] & 0xffff;//RIN0 ƒ¬ых. item
  tempReadArray[4] = value;
  value = (arr->param[FIX_BLOCK_MUTE] >> 16) & 0x7fff;//RIN1 ƒ¬ых. item
  tempReadArray[5] = value;
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
   break; 
   case 1:
   break; 
   case 2:
   break; 
   case 3:
   break; 
   case 4:
   break; 
   case 5:
   break; 
   default: return MARKER_OUTPERIMETR;
  }//switch
  return 0;
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
//action до чтени€
  basdbigcomponent->operativMarker[0] = -1;
  basdbigcomponent->operativMarker[1] = -1;//оперативный маркер
  basdbigcomponent->isActiveActualData = 1;
}//
void postBASDBigReadAction(void) {
//action после чтени€
  if(basdbigcomponent->operativMarker[0]<0) return;//не было чтени€
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
