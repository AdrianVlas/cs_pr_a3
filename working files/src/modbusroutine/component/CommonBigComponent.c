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
void postCommonBigWriteAction(void);//action после записи
void loadCommonBigActualData(void);

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

void loadCommonBigActualData(void) {
  //ActualData
//   __LN_AND *arr = (__LN_AND*)(spca_of_p_prt[ID_FB_INPUT - _ID_FB_FIRST_VAR]);
   for(int item=0; item<commonbigcomponent->countObject; item++) {
   //Тревога 0
   int value = 0;//arr[item].settings.param[0];
   tempReadArray[item*REGISTER_FOR_OBJ+0] = value;
   //Тревога 1
   value = 0;//arr[item].settings.param[1];
   tempReadArray[item*REGISTER_FOR_OBJ+1] = value;

   //Тишина 0
   value = 0;//arr[item].settings.param[0];
   tempReadArray[item*REGISTER_FOR_OBJ+2] = value;
   //Тишина 1
   value = 0;//arr[item].settings.param[1];
   tempReadArray[item*REGISTER_FOR_OBJ+3] = value;

   //Блок. 0
   value = 0;//arr[item].settings.param[0];
   tempReadArray[item*REGISTER_FOR_OBJ+4] = value;
   //Блок. 1
   value = 0;//arr[item].settings.param[1];
   tempReadArray[item*REGISTER_FOR_OBJ+5] = value;

   //Тест.Вход. 0
   value = 0;//arr[item].settings.param[0];
   tempReadArray[item*REGISTER_FOR_OBJ+6] = value;
   //Тест.Вход. 1
   value = 0;//arr[item].settings.param[1];
   tempReadArray[item*REGISTER_FOR_OBJ+7] = value;

   //Тест.Сброс. 0
   value = 0;//arr[item].settings.param[0];
   tempReadArray[item*REGISTER_FOR_OBJ+8] = value;
   //Тест.Сброс. 1
   value = 0;//arr[item].settings.param[1];
   tempReadArray[item*REGISTER_FOR_OBJ+9] = value;
  }//for
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
   case 6:
   break; 
   case 7:
   break; 
   case 8:
   break; 
   case 9:
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
void postCommonBigWriteAction(void) {
//action после записи
  if(commonbigcomponent->operativMarker[0]<0) return;//не было записи
//  int offset = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//найти смещение TempWriteArray
//  int countRegister = commonbigcomponent->operativMarker[1]-commonbigcomponent->operativMarker[0]+1;
//  if(commonbigcomponent->operativMarker[1]<0) countRegister = 1;
}//

int privateCommonBigGetReg2(int adrReg)
{
  //проверить внешний периметр
  int count_register = REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
