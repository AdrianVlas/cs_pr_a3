#include "header.h"

//начальный регистр в карте памяти
#define BEGIN_ADR_REGISTER 13781
//макс к-во обектов
#define REGISTER_FOR_OBJ 10

int privateCommonBigGetReg2(int adrReg);

int getCommonBigModbusRegister(int);//получить содержимое регистра
int getCommonBigModbusBit(int);//получить содержимое бита
int setCommonBigModbusRegister(int, int);// регистра
int setCommonBigModbusBit(int, int);// бита

void preCommonBigReadAction(void);//action до чтения
void postCommonBigReadAction(void);//action после чтения
void preCommonBigWriteAction(void);//action до записи
int postCommonBigWriteAction(void);//action после записи
//void loadCommonBigActualData(void);

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

  commonbigcomponent->preReadAction   = preCommonBigReadAction;//action до чтения
  commonbigcomponent->postReadAction  = postCommonBigReadAction;//action после чтения
  commonbigcomponent->preWriteAction  = preCommonBigWriteAction;//action до записи
  commonbigcomponent->postWriteAction = postCommonBigWriteAction;//action после записи

  commonbigcomponent->isActiveActualData = 0;
}//prepareDVinConfig
/*
void loadCommonBigActualData(void) {
  //ActualData
   __SETTINGS_FIX *arr = &settings_fix;
   for(int item=0; item<commonbigcomponent->countObject; item++) {
   //Тревога 0
   int value = arr->param[FIX_BLOCK_ALARM] & 0xffff;//
   tempReadArray[item*REGISTER_FOR_OBJ+0] = value;
   value = (arr->param[FIX_BLOCK_ALARM] >> 16) & 0x7fff;//
   tempReadArray[item*REGISTER_FOR_OBJ+1] = value;

   //Тишина 0
   value = arr->param[FIX_BLOCK_MUTE] & 0xffff;//
   tempReadArray[item*REGISTER_FOR_OBJ+2] = value;
   value = (arr->param[FIX_BLOCK_MUTE] >> 16) & 0x7fff;//
   tempReadArray[item*REGISTER_FOR_OBJ+3] = value;

   //Блок. 0
   value = arr->param[FIX_BLOCK_BLOCK] & 0xffff;//
   tempReadArray[item*REGISTER_FOR_OBJ+4] = value;
   value = (arr->param[FIX_BLOCK_BLOCK] >> 16) & 0x7fff;//
   tempReadArray[item*REGISTER_FOR_OBJ+5] = value;

   //Тест.Вход. 0
   value = arr->param[FIX_BLOCK_TEST_INPUT] & 0xffff;//
   tempReadArray[item*REGISTER_FOR_OBJ+6] = value;
   value = (arr->param[FIX_BLOCK_TEST_INPUT] >> 16) & 0x7fff;//
   tempReadArray[item*REGISTER_FOR_OBJ+7] = value;

   //Тест.Сброс. 0
   value = arr->param[FIX_BLOCK_TEST_RESET] & 0xffff;//
   tempReadArray[item*REGISTER_FOR_OBJ+8] = value;
   value = (arr->param[FIX_BLOCK_TEST_RESET] >> 16) & 0x7fff;//
   tempReadArray[item*REGISTER_FOR_OBJ+9] = value;
  }//for
}//loadActualData() 
*/

int getCommonBigModbusRegister(int adrReg)
{
  //получить содержимое регистра
  if(privateCommonBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

//  if(commonbigcomponent->isActiveActualData) loadCommonBigActualData(); //ActualData
//  commonbigcomponent->isActiveActualData = 0;

  superSetOperativMarker(commonbigcomponent, adrReg);

   __SETTINGS_FIX *arr = &settings_fix;
  int offset = adrReg-BEGIN_ADR_REGISTER;
  switch(offset%REGISTER_FOR_OBJ) {//индекс регистра 
  case 0:
   //Тревога 0
   return arr->param[FIX_BLOCK_ALARM] & 0xffff;//
  case 1:
   return (arr->param[FIX_BLOCK_ALARM] >> 16) & 0x7fff;//

  case 2:
   //Тишина 0
   return arr->param[FIX_BLOCK_MUTE] & 0xffff;//
  case 3:
   return (arr->param[FIX_BLOCK_MUTE] >> 16) & 0x7fff;//

  case 4:
   //Блок. 0
   return arr->param[FIX_BLOCK_BLOCK] & 0xffff;//
  case 5:
   return (arr->param[FIX_BLOCK_BLOCK] >> 16) & 0x7fff;//

  case 6:
   //Тест.Вход. 0
   //return arr->param[FIX_BLOCK_TEST_INPUT] & 0xffff;//
  case 7:
   //return (arr->param[FIX_BLOCK_TEST_INPUT] >> 16) & 0x7fff;//

  case 8:
   //Тест.Сброс. 0
   //return arr->param[FIX_BLOCK_TEST_RESET] & 0xffff;//
  case 9:
   //return (arr->param[FIX_BLOCK_TEST_RESET] >> 16) & 0x7fff;//
    break;
  }//switch

  return 0;//tempReadArray[adrReg-BEGIN_ADR_REGISTER];
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
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
   break; 
   case 1:
    //контроль параметров ранжирования
    if(superControlParam(dataReg)) return MARKER_ERRORDIAPAZON;
   break; 
   case 2:
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
   break; 
   case 3:
    //контроль параметров ранжирования
    if(superControlParam(dataReg)) return MARKER_ERRORDIAPAZON;
   break; 
   case 4:
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
   break; 
   case 5:
    //контроль параметров ранжирования
    if(superControlParam(dataReg)) return MARKER_ERRORDIAPAZON;
   break; 
   case 6:
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
   break; 
   case 7:
    //контроль параметров ранжирования
    if(superControlParam(dataReg)) return MARKER_ERRORDIAPAZON;
   break; 
   case 8:
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
   break; 
   case 9:
    //контроль параметров ранжирования
    if(superControlParam(dataReg)) return MARKER_ERRORDIAPAZON;
   break; 
   default: return MARKER_OUTPERIMETR;
  }//switch
  return 0;
}//getDOUTBigModbusRegister(int adrReg)
int setCommonBigModbusBit(int adrBit, int x)
{
  UNUSED(x);
  //получить содержимое регистра
  superSetOperativMarker(commonbigcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void preCommonBigReadAction(void) {
//action до чтения
  commonbigcomponent->operativMarker[0] = -1;
  commonbigcomponent->operativMarker[1] = -1;//оперативный маркер
  commonbigcomponent->isActiveActualData = 1;
}//
void postCommonBigReadAction(void) {
//action после чтения
  if(commonbigcomponent->operativMarker[0]<0) return;//не было чтения
}//
void preCommonBigWriteAction(void) {
//action до записи
  commonbigcomponent->operativMarker[0] = -1;
  commonbigcomponent->operativMarker[1] = -1;//оперативный маркер
  commonbigcomponent->isActiveActualData = 1;
}//
int postCommonBigWriteAction(void) {
//action после записи
  if(commonbigcomponent->operativMarker[0]<0) return 0;//не было записи
  int offsetTempWriteArray = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//найти смещение TempWriteArray
  int countRegister = commonbigcomponent->operativMarker[1]-commonbigcomponent->operativMarker[0]+1;
  if(commonbigcomponent->operativMarker[1]<0) countRegister = 1;

//   __SETTINGS_FIX *arr = &settings_fix;
  __SETTINGS_FIX *arr = &settings_fix, *arr1 = &settings_fix_edit;
  for(int i=0; i<countRegister; i++) {
  int offset = i+commonbigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;
  switch(offset) {//индекс регистра 
   case 0://Тревога 0
        arr1->param[FIX_BLOCK_ALARM] = arr->param[FIX_BLOCK_ALARM] &= (uint32_t)~0xffff;
        arr1->param[FIX_BLOCK_ALARM] = arr->param[FIX_BLOCK_ALARM] |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
   break; 
   case 1://Тревога 1
        arr1->param[FIX_BLOCK_ALARM] = arr->param[FIX_BLOCK_ALARM] &= (uint32_t)~(0x7fff<<16);
        arr1->param[FIX_BLOCK_ALARM] = arr->param[FIX_BLOCK_ALARM] |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
   break; 

   case 2://Тишина 0
        arr1->param[FIX_BLOCK_MUTE] = arr->param[FIX_BLOCK_MUTE] &= (uint32_t)~0xffff;
        arr1->param[FIX_BLOCK_MUTE] = arr->param[FIX_BLOCK_MUTE] |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
   break; 
   case 3://Тишина 1
        arr1->param[FIX_BLOCK_MUTE] = arr->param[FIX_BLOCK_MUTE] &= (uint32_t)~(0x7fff<<16);
        arr1->param[FIX_BLOCK_MUTE] = arr->param[FIX_BLOCK_MUTE] |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
   break; 

   case 4://Блок. 0
        arr1->param[FIX_BLOCK_BLOCK] = arr->param[FIX_BLOCK_BLOCK] &= (uint32_t)~0xffff;
        arr1->param[FIX_BLOCK_BLOCK] = arr->param[FIX_BLOCK_BLOCK] |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
   break; 
   case 5://Блок. 1
        arr1->param[FIX_BLOCK_BLOCK] = arr->param[FIX_BLOCK_BLOCK] &= (uint32_t)~(0x7fff<<16);
        arr1->param[FIX_BLOCK_BLOCK] = arr->param[FIX_BLOCK_BLOCK] |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
   break; 

   case 6://Тест.Вход. 0
//        arr1->param[FIX_BLOCK_TEST_INPUT] = arr->param[FIX_BLOCK_TEST_INPUT] &= (uint32_t)~0xffff;
        //arr1->param[FIX_BLOCK_TEST_INPUT] = arr->param[FIX_BLOCK_TEST_INPUT] |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
   break; 
   case 7://Тест.Вход. 1
//        arr1->param[FIX_BLOCK_TEST_INPUT] = arr->param[FIX_BLOCK_TEST_INPUT] &= (uint32_t)~(0x7fff<<16);
        //arr1->param[FIX_BLOCK_TEST_INPUT] = arr->param[FIX_BLOCK_TEST_INPUT] |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//

   case 8://Тест.Сброс. 0
//        arr1->param[FIX_BLOCK_TEST_RESET] = arr->param[FIX_BLOCK_TEST_RESET] &= (uint32_t)~0xffff;
//        arr1->param[FIX_BLOCK_TEST_RESET] = arr->param[FIX_BLOCK_TEST_RESET] |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
   break; 
   case 9://Тест.Сброс. 1
        //arr1->param[FIX_BLOCK_TEST_RESET] = arr->param[FIX_BLOCK_TEST_RESET] &= (uint32_t)~(0x7fff<<16);
        //arr1->param[FIX_BLOCK_TEST_RESET] = arr->param[FIX_BLOCK_TEST_RESET] |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
   break; 
 }//switch
  }//for
  config_settings_modified |= MASKA_FOR_BIT(BIT_CHANGED_SETTINGS);
  restart_timeout_idle_new_settings = true;
 return 0;
}//

int privateCommonBigGetReg2(int adrReg)
{
  //проверить внешний периметр
  int count_register = REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
