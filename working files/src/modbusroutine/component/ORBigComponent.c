#include "header.h"

//начальный регистр в карте памяти
#define BEGIN_ADR_REGISTER 10965
//макс к-во обектов
#define TOTAL_OBJ 128
#define REGISTER_FOR_OBJ 16

int privateORBigGetReg1(int adrReg);
int privateORBigGetReg2(int adrReg);

int getORBigModbusRegister(int);//получить содержимое регистра
int getORBigModbusBit(int);//получить содержимое бита
int setORBigModbusRegister(int, int);//получить содержимое регистра
int setORBigModbusBit(int, int);//получить содержимое бита

void setORBigCountObject(void);//записать к-во обектов
void preORBigReadAction(void);//action до чтения
void postORBigReadAction(void);//action после чтения
void preORBigWriteAction(void);//action до записи
void postORBigWriteAction(void);//action после записи
void loadORBigActualData(void);

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

  orbigcomponent->preReadAction   = preORBigReadAction;//action до чтения
  orbigcomponent->postReadAction  = postORBigReadAction;//action после чтения
  orbigcomponent->preWriteAction  = preORBigWriteAction;//action до записи
  orbigcomponent->postWriteAction = postORBigWriteAction;//action после записи

  orbigcomponent->isActiveActualData = 0;
}//prepareDVinConfig

void loadORBigActualData(void) {
 setORBigCountObject(); //записать к-во обектов
  //ActualData
   __LN_OR *arr = (__LN_OR*)(spca_of_p_prt[ID_FB_OR - _ID_FB_FIRST_VAR]);
   for(int item=0; item<orbigcomponent->countObject; item++) {

     for (int i = 0; i < OR_SIGNALS_IN; i ++)
     {
        int value = arr[item].settings.param[i] & 0xffff;//LEDIN 0 СД item
        tempReadArray[item*REGISTER_FOR_OBJ+2*i+0] = value;
        value = (arr[item].settings.param[i] >> 16) & 0x7fff;//LEDIN 1 СД item
        tempReadArray[item*REGISTER_FOR_OBJ+2*i+1] = value;
     }
     
//     //OR item.1 0
//   int value = arr[item].settings.param[0];
//   tempReadArray[item*REGISTER_FOR_OBJ+0] = value;
//   //OR item.2 1
//   value = arr[item].settings.param[1];
//   tempReadArray[item*REGISTER_FOR_OBJ+1] = value;
//
//   //OR item.1 0
//   value = arr[item].settings.param[0];
//   tempReadArray[item*REGISTER_FOR_OBJ+2] = value;
//   //OR item.2 1
//   value = arr[item].settings.param[1];
//   tempReadArray[item*REGISTER_FOR_OBJ+3] = value;
//
//   //OR item.1 0
//   value = arr[item].settings.param[0];
//   tempReadArray[item*REGISTER_FOR_OBJ+4] = value;
//   //OR item.2 1
//   value = arr[item].settings.param[1];
//   tempReadArray[item*REGISTER_FOR_OBJ+5] = value;
//
//   //OR item.1 0
//   value = arr[item].settings.param[0];
//   tempReadArray[item*REGISTER_FOR_OBJ+6] = value;
//   //OR item.2 1
//   value = arr[item].settings.param[1];
//   tempReadArray[item*REGISTER_FOR_OBJ+7] = value;
//
//   //OR item.1 0
//   value = arr[item].settings.param[0];
//   tempReadArray[item*REGISTER_FOR_OBJ+8] = value;
//   //OR item.2 1
//   value = arr[item].settings.param[1];
//   tempReadArray[item*REGISTER_FOR_OBJ+9] = value;
//
//   //OR item.1 0
//   value = arr[item].settings.param[0];
//   tempReadArray[item*REGISTER_FOR_OBJ+10] = value;
//   //OR item.2 1
//   value = arr[item].settings.param[1];
//   tempReadArray[item*REGISTER_FOR_OBJ+11] = value;
//
//   //OR item.1 0
//   value = arr[item].settings.param[0];
//   tempReadArray[item*REGISTER_FOR_OBJ+12] = value;
//   //OR item.2 1
//   value = arr[item].settings.param[1];
//   tempReadArray[item*REGISTER_FOR_OBJ+13] = value;
//
//   //OR item.1 0
//   value = arr[item].settings.param[0];
//   tempReadArray[item*REGISTER_FOR_OBJ+14] = value;
//   //OR item.2 1
//   value = arr[item].settings.param[1];
//   tempReadArray[item*REGISTER_FOR_OBJ+15] = value;

   }//for
}//loadActualData() 

int getORBigModbusRegister(int adrReg)
{
  //получить содержимое регистра
  if(privateORBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(orbigcomponent->isActiveActualData) loadORBigActualData(); //ActualData
  orbigcomponent->isActiveActualData = 0;
  if(privateORBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

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
   break; 
   case 1:
   break; 
   case 2:
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
   break; 
   case 3:
   break; 
   case 4:
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
   break; 
   case 5:
   break; 
   case 6:
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
   break; 
   case 7:
   break; 
   case 8:
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
   break; 
   case 9:
   break; 
   case 10:
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
   break; 
   case 11:
   break; 
   case 12:
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
   break; 
   case 13:
   break; 
   case 14:
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
   break; 
   case 15:
   break; 
  default: return MARKER_OUTPERIMETR;
  }//switch
  return 0;
}//getDOUTBigModbusRegister(int adrReg)
int setORBigModbusBit(int adrBit, int x)
{
  UNUSED(x);
  //получить содержимое регистра
  superSetOperativMarker(orbigcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void setORBigCountObject(void) {
//записать к-во обектов
  int cntObj = current_config.n_or;    //Кількість елементів "АБО"
  if(cntObj<0) return;
  if(cntObj>TOTAL_OBJ) return;
  orbigcomponent->countObject = cntObj;
}//
void preORBigReadAction(void) {
//action до чтения
  orbigcomponent->operativMarker[0] = -1;
  orbigcomponent->operativMarker[1] = -1;//оперативный маркер
  orbigcomponent->isActiveActualData = 1;
}//
void postORBigReadAction(void) {
//action после чтения
  if(orbigcomponent->operativMarker[0]<0) return;//не было чтения
}//
void preORBigWriteAction(void) {
//action до записи
  orbigcomponent->operativMarker[0] = -1;
  orbigcomponent->operativMarker[1] = -1;//оперативный маркер
  orbigcomponent->isActiveActualData = 1;
}//
void postORBigWriteAction(void) {
//action после записи
  if(orbigcomponent->operativMarker[0]<0) return;//не было записи
//  int offset = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//найти смещение TempWriteArray
//  int countRegister = orbigcomponent->operativMarker[1]-orbigcomponent->operativMarker[0]+1;
//  if(orbigcomponent->operativMarker[1]<0) countRegister = 1;
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
