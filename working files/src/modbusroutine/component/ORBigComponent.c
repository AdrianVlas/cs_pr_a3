#include "header.h"

//начальный регистр в карте памяти
#define BEGIN_ADR_REGISTER 10952
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
int postORBigWriteAction(void);//action после записи
void repairEditArrayOR(int countRegister, __settings_for_OR *arr, __settings_for_OR *arr1);

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

int getORBigModbusRegister(int adrReg)
{
  //получить содержимое регистра
extern int pointInterface;//метка интерфейса 0-USB 1-RS485
  if(privateORBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(orbigcomponent->isActiveActualData) setORBigCountObject(); //к-во обектов
  orbigcomponent->isActiveActualData = 0;
  if(privateORBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  superSetOperativMarker(orbigcomponent, adrReg);

  int offset = adrReg-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//индекс субобъекта
  int idxParam = (offset/2)%OR_SIGNALS_IN;//индекс param
  __settings_for_OR *arr =  ((config_settings_modified & MASKA_FOR_BIT(BIT_USB_LOCKS)) == 0 ) ? &(((__LN_OR*)(spca_of_p_prt[ID_FB_OR - _ID_FB_FIRST_VAR])) + idxSubObj)->settings : (((__settings_for_OR*)(sca_of_p[ID_FB_OR - _ID_FB_FIRST_VAR])) + idxSubObj);
  if(pointInterface)//метка интерфейса 0-USB 1-RS485
                        arr =  ((config_settings_modified & MASKA_FOR_BIT(BIT_RS485_LOCKS)) == 0 ) ? &(((__LN_OR*)(spca_of_p_prt[ID_FB_OR - _ID_FB_FIRST_VAR])) + idxSubObj)->settings : (((__settings_for_OR*)(sca_of_p[ID_FB_OR - _ID_FB_FIRST_VAR])) + idxSubObj);

  switch(offset%2) {//индекс регистра 
   case 0:
        return  arr->param[idxParam] & 0xffff;//
   case 1:
        return  (arr->param[idxParam] >> 16) & 0x7fff;//
  }//switch
  return 0;
}//getDOUTBigModbusRegister(int adrReg)
int getORBigModbusBit(int x)
{
  //получить содержимое регистра
  UNUSED(x);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setORBigModbusRegister(int adrReg, int dataReg)
{
  //записать содержимое регистра
  if(privateORBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(orbigcomponent->isActiveActualData) setORBigCountObject(); //к-во обектов
  orbigcomponent->isActiveActualData = 0;
  if(privateORBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  superSetOperativMarker(orbigcomponent, adrReg);
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
   case 10:
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
   break; 
   case 11:
    //контроль параметров ранжирования
    if(superControlParam(dataReg)) return MARKER_ERRORDIAPAZON;
   break; 
   case 12:
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
   break; 
   case 13:
    //контроль параметров ранжирования
    if(superControlParam(dataReg)) return MARKER_ERRORDIAPAZON;
   break; 
   case 14:
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
   break; 
   case 15:
    //контроль параметров ранжирования
    if(superControlParam(dataReg)) return MARKER_ERRORDIAPAZON;
   break; 
  default: return MARKER_OUTPERIMETR;
  }//switch
  return 0;
}//getDOUTBigModbusRegister(int adrReg)
int setORBigModbusBit(int x, int y)
{
  UNUSED(x);
  UNUSED(y);
  //получить содержимое регистра
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
int postORBigWriteAction(void) {
extern int pointInterface;//метка интерфейса 0-USB 1-RS485
//action после записи
  if(orbigcomponent->operativMarker[0]<0) return 0;//не было записи
  int offsetTempWriteArray = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//найти смещение TempWriteArray
  int countRegister = orbigcomponent->operativMarker[1]-orbigcomponent->operativMarker[0]+1;
  if(orbigcomponent->operativMarker[1]<0) countRegister = 1;

   __settings_for_OR *arr  = (__settings_for_OR*)(sca_of_p[ID_FB_OR - _ID_FB_FIRST_VAR]);
   __settings_for_OR *arr1 = (__settings_for_OR*)(sca_of_p_edit[ID_FB_OR - _ID_FB_FIRST_VAR]);
//загрузка edit массва
  for(int i=0; i<countRegister; i++) {
  int offset = i+orbigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//индекс субобъекта
  int idx_SIGNALS_IN = (offset%REGISTER_FOR_OBJ)/2;//индекс входа субобъекта

  switch(offset%2) {//индекс регистра входа
  case 0:
        arr1[idxSubObj].param[idx_SIGNALS_IN]  &= (uint32_t)~0xffff;
        arr1[idxSubObj].param[idx_SIGNALS_IN]  |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
  break;
  case 1:
        arr1[idxSubObj].param[idx_SIGNALS_IN]  &= (uint32_t)~(0x7fff<<16);
        arr1[idxSubObj].param[idx_SIGNALS_IN]  |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
  break;
 }//switch
  }//for

  //контроль валидности
  for(int i=0; i<countRegister; i++) {
  int offset = i+orbigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//индекс субобъекта
  int idx_SIGNALS_IN = (offset%REGISTER_FOR_OBJ)/2;//индекс входа субобъекта

  switch(offset%2) {//индекс регистра входа
  case 0:
  case 1:
        if(superValidParam(arr1[idxSubObj].param[idx_SIGNALS_IN])) 
                {//контроль валидности
                repairEditArrayOR(countRegister, arr, arr1);//восстановить edit массив
                return 2;//уйти
        }//if
  break;
 }//switch
  }//for

//контроль пройден - редактирование
  for(int i=0; i<countRegister; i++) {
  int offset = i+orbigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//индекс субобъекта
  int idx_SIGNALS_IN = (offset%REGISTER_FOR_OBJ)/2;//индекс входа субобъекта

  switch(offset%2) {//индекс регистра входа
  case 0:
        arr1[idxSubObj].param[idx_SIGNALS_IN] = arr[idxSubObj].param[idx_SIGNALS_IN] &= (uint32_t)~0xffff;
        arr1[idxSubObj].param[idx_SIGNALS_IN] = arr[idxSubObj].param[idx_SIGNALS_IN] |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
  break;
  case 1:
        arr1[idxSubObj].param[idx_SIGNALS_IN] = arr[idxSubObj].param[idx_SIGNALS_IN] &= (uint32_t)~(0x7fff<<16);
        arr1[idxSubObj].param[idx_SIGNALS_IN] = arr[idxSubObj].param[idx_SIGNALS_IN] |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
  break;
 }//switch
   superSortParam(OR_SIGNALS_IN, &(arr1[idxSubObj].param[0]));//сортировка
   superSortParam(OR_SIGNALS_IN, &(arr[idxSubObj].param[0]));//сортировка
  }//for

  config_settings_modified |= MASKA_FOR_BIT(BIT_CHANGED_SCHEMATIC);
  if(pointInterface)//метка интерфейса 0-USB 1-RS485
     config_settings_modified |= MASKA_FOR_BIT(BIT_RS485_LOCKS);
  else 
     config_settings_modified |= MASKA_FOR_BIT(BIT_USB_LOCKS);
  restart_timeout_idle_new_settings = true;
 return 0;
}//

void repairEditArrayOR(int countRegister, __settings_for_OR *arr, __settings_for_OR *arr1) {
  //восстановить edit массив
  for(int i=0; i<countRegister; i++) {
  int offset = i+orbigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//индекс субобъекта
  int idx_SIGNALS_IN = (offset%REGISTER_FOR_OBJ)/2;//индекс входа субобъекта

  switch(offset%2) {//индекс регистра входа
  case 0:
  case 1:
        arr1[idxSubObj].param[idx_SIGNALS_IN] = arr[idxSubObj].param[idx_SIGNALS_IN];
  break;
 }//switch
  }//for
}//repairEditArray(int countRegister, __settings_for_OR *arr, __settings_for_OR *arr1) 

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
