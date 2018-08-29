#include "header.h"

//начальный регистр в карте памяти
#define BEGIN_ADR_REGISTER 14536
//макс к-во обектов
#define TOTAL_OBJ 128
#define REGISTER_FOR_OBJ 18

int privateOLANBigGetReg1(int adrReg);
int privateOLANBigGetReg2(int adrReg);

int getOLANBigModbusRegister(int);//получить содержимое регистра
int getOLANBigModbusBit(int);//получить содержимое бита
int setOLANBigModbusRegister(int, int);//получить содержимое регистра
int setOLANBigModbusBit(int, int);//получить содержимое бита

void setOLANBigCountObject(void);//записать к-во обектов
void preOLANBigReadAction(void);//action до чтения
void postOLANBigReadAction(void);//action после чтения
void preOLANBigWriteAction(void);//action до записи
int postOLANBigWriteAction(void);//action после записи
void repairEditArrayOLAN(int countRegister, __settings_for_NETWORK_OUTPUT_BLOCK *arr, __settings_for_NETWORK_OUTPUT_BLOCK *arr1);
void config_and_settingsOLANBig(void);//action активации

COMPONENT_OBJ *olanbigcomponent;

/**************************************/
//подготовка компонента Output LAN
/**************************************/
void constructorOLANBigComponent(COMPONENT_OBJ *olanbigcomp)
{
  olanbigcomponent = olanbigcomp;

  olanbigcomponent->countObject = 0;//к-во обектов

  olanbigcomponent->getModbusRegister = getOLANBigModbusRegister;//получить содержимое регистра
  olanbigcomponent->getModbusBit      = getOLANBigModbusBit;//получить содержимое бита
  olanbigcomponent->setModbusRegister = setOLANBigModbusRegister;//получить содержимое регистра
  olanbigcomponent->setModbusBit      = setOLANBigModbusBit;//получить содержимое бита

  olanbigcomponent->preReadAction   = preOLANBigReadAction;//action до чтения
  olanbigcomponent->postReadAction  = postOLANBigReadAction;//action после чтения
  olanbigcomponent->preWriteAction  = preOLANBigWriteAction;//action до записи
  olanbigcomponent->postWriteAction = postOLANBigWriteAction;//action после записи
  olanbigcomponent->config_and_settings = config_and_settingsOLANBig;//action активации

  olanbigcomponent->isActiveActualData = 0;
}//prepareDVinConfig

int getOLANBigModbusRegister(int adrReg)
{
  //получить содержимое регистра
extern int pointInterface;//метка интерфейса 0-USB 1-RS485
  if(privateOLANBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(olanbigcomponent->isActiveActualData) setOLANBigCountObject(); //к-во обектов
  olanbigcomponent->isActiveActualData = 0;
  if(privateOLANBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  superSetOperativMarker(olanbigcomponent, adrReg);

  int offset = adrReg-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//индекс субобъекта
  int idxParam = (offset/2)%9;//индекс param
  __settings_for_NETWORK_OUTPUT_BLOCK *arr =  ((config_settings_modified & MASKA_FOR_BIT(BIT_USB_LOCKS)) == 0 ) ? &(((__LN_NETWORK_OUTPUT_BLOCK*)(spca_of_p_prt[ID_FB_NETWORK_OUTPUT_BLOCK - _ID_FB_FIRST_VAR])) + idxSubObj)->settings : (((__settings_for_NETWORK_OUTPUT_BLOCK*)(sca_of_p[ID_FB_NETWORK_OUTPUT_BLOCK - _ID_FB_FIRST_VAR])) + idxSubObj);
  if(pointInterface)//метка интерфейса 0-USB 1-RS485
                        arr =  ((config_settings_modified & MASKA_FOR_BIT(BIT_RS485_LOCKS)) == 0 ) ? &(((__LN_NETWORK_OUTPUT_BLOCK*)(spca_of_p_prt[ID_FB_NETWORK_OUTPUT_BLOCK - _ID_FB_FIRST_VAR])) + idxSubObj)->settings : (((__settings_for_NETWORK_OUTPUT_BLOCK*)(sca_of_p[ID_FB_NETWORK_OUTPUT_BLOCK - _ID_FB_FIRST_VAR])) + idxSubObj);

  switch(offset%2) {//индекс регистра 
   case 0:
        return  arr->param[idxParam] & 0xffff;//
   case 1:
        return  (arr->param[idxParam] >> 16) & 0x7fff;//
  }//switch
  return 0;
}//getDOUTBigModbusRegister(int adrReg)
int getOLANBigModbusBit(int x)
{
  //получить содержимое регистра
  UNUSED(x);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setOLANBigModbusRegister(int adrReg, int dataReg)
{
  //записать содержимое регистра
  if(privateOLANBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(olanbigcomponent->isActiveActualData) setOLANBigCountObject(); //к-во обектов
  olanbigcomponent->isActiveActualData = 0;
  if(privateOLANBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  superSetOperativMarker(olanbigcomponent, adrReg);
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
   case 16:
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
   break; 
   case 17:
    //контроль параметров ранжирования
    if(superControlParam(dataReg)) return MARKER_ERRORDIAPAZON;
   break; 
  default: return MARKER_OUTPERIMETR;
  }//switch
  return 0;
}//getDOUTBigModbusRegister(int adrReg)
int setOLANBigModbusBit(int x, int y)
{
  UNUSED(x);
  UNUSED(y);
  //получить содержимое регистра
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void setOLANBigCountObject(void) {
//записать к-во обектов
  int cntObj = current_config.n_network_output_block;    //Кількість елементів "АБО"
  if(cntObj<0) return;
  if(cntObj>TOTAL_OBJ) return;
  olanbigcomponent->countObject = cntObj;
}//
void preOLANBigReadAction(void) {
//action до чтения
  olanbigcomponent->operativMarker[0] = -1;
  olanbigcomponent->operativMarker[1] = -1;//оперативный маркер
  olanbigcomponent->isActiveActualData = 1;
}//
void postOLANBigReadAction(void) {
//action после чтения
  if(olanbigcomponent->operativMarker[0]<0) return;//не было чтения
}//
void preOLANBigWriteAction(void) {
//action до записи
  olanbigcomponent->operativMarker[0] = -1;
  olanbigcomponent->operativMarker[1] = -1;//оперативный маркер
  olanbigcomponent->isActiveActualData = 1;
}//
int postOLANBigWriteAction(void) {
extern int pointInterface;//метка интерфейса 0-USB 1-RS485
extern int upravlconfig_and_settings;//флаг активации компонента
//action после записи
  if(olanbigcomponent->operativMarker[0]<0) return 0;//не было записи
  int offsetTempWriteArray = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//найти смещение TempWriteArray
  int countRegister = olanbigcomponent->operativMarker[1]-olanbigcomponent->operativMarker[0]+1;
  if(olanbigcomponent->operativMarker[1]<0) countRegister = 1;

   __settings_for_NETWORK_OUTPUT_BLOCK *arr  = (__settings_for_NETWORK_OUTPUT_BLOCK*)(sca_of_p[ID_FB_NETWORK_OUTPUT_BLOCK - _ID_FB_FIRST_VAR]);
   __settings_for_NETWORK_OUTPUT_BLOCK *arr1 = (__settings_for_NETWORK_OUTPUT_BLOCK*)(sca_of_p_edit[ID_FB_NETWORK_OUTPUT_BLOCK - _ID_FB_FIRST_VAR]);
//загрузка edit массва
  for(int i=0; i<countRegister; i++) {
  int offset = i+olanbigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;
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
  int offset = i+olanbigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//индекс субобъекта
  int idx_SIGNALS_IN = (offset%REGISTER_FOR_OBJ)/2;//индекс входа субобъекта

  switch(offset%2) {//индекс регистра входа
  case 0:
  case 1:
        if(superValidParam(arr1[idxSubObj].param[idx_SIGNALS_IN])) 
                {//контроль валидности
                repairEditArrayOLAN(countRegister, arr, arr1);//восстановить edit массив
                return 2;//уйти
        }//if
  break;
 }//switch
  }//for

//контроль пройден - редактирование
  for(int i=0; i<countRegister; i++) {
  int offset = i+olanbigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;
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
  }//for

  upravlconfig_and_settings=1;//флаг активации компонента

  config_settings_modified |= MASKA_FOR_BIT(BIT_CHANGED_SCHEMATIC);
  if(pointInterface)//метка интерфейса 0-USB 1-RS485
     config_settings_modified |= MASKA_FOR_BIT(BIT_RS485_LOCKS);
  else 
     config_settings_modified |= MASKA_FOR_BIT(BIT_USB_LOCKS);
  restart_timeout_idle_new_settings = true;
 return 0;
}//

void repairEditArrayOLAN(int countRegister, __settings_for_NETWORK_OUTPUT_BLOCK *arr, __settings_for_NETWORK_OUTPUT_BLOCK *arr1) {
  //восстановить edit массив
  for(int i=0; i<countRegister; i++) {
  int offset = i+olanbigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;
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

int privateOLANBigGetReg1(int adrReg)
{
  //проверить внутренний периметр
  int count_register = olanbigcomponent->countObject*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg1(int adrReg)
int privateOLANBigGetReg2(int adrReg)
{
  //проверить внешний периметр
  int count_register = TOTAL_OBJ*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)

void config_and_settingsOLANBig(void)
{
}

