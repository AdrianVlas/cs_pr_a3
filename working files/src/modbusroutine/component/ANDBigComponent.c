#include "header.h"

//начальный регистр в карте памяти
#define BEGIN_ADR_REGISTER 8904
//макс к-во обектов
#define TOTAL_OBJ 128
#define REGISTER_FOR_OBJ 16

int privateANDBigGetReg1(int adrReg);
int privateANDBigGetReg2(int adrReg);

int getANDBigModbusRegister(int);//получить содержимое регистра
int getANDBigModbusBit(int);//получить содержимое бита
int setANDBigModbusRegister(int, int);// регистр
int setANDBigModbusBit(int, int);// бит

void setANDBigCountObject(void);
void preANDBigReadAction(void);//action до чтения
void postANDBigReadAction(void);//action после чтения
void preANDBigWriteAction(void);//action до записи
int postANDBigWriteAction(void);//action после записи
//void loadANDBigActualData(void);

COMPONENT_OBJ *andbigcomponent;

/**************************************/
//подготовка компонента AND
/**************************************/
void constructorANDBigComponent(COMPONENT_OBJ *andbigcomp)
{
  andbigcomponent = andbigcomp;

  andbigcomponent->countObject = 0;//к-во обектов

  andbigcomponent->getModbusRegister = getANDBigModbusRegister;//получить содержимое регистра
  andbigcomponent->getModbusBit      = getANDBigModbusBit;//получить содержимое бита
  andbigcomponent->setModbusRegister = setANDBigModbusRegister;//записать регистр
  andbigcomponent->setModbusBit      = setANDBigModbusBit;//записать бит

  andbigcomponent->preReadAction   = preANDBigReadAction;//action до чтения
  andbigcomponent->postReadAction  = postANDBigReadAction;//action после чтения
  andbigcomponent->preWriteAction  = preANDBigWriteAction;//action до записи
  andbigcomponent->postWriteAction = postANDBigWriteAction;//action после записи

  andbigcomponent->isActiveActualData = 0;
}//prepareDVinConfig

/*
void loadANDBigActualData(void) {
 setANDBigCountObject(); //записать к-во обектов

  //ActualData
   __LN_AND *arr = (__LN_AND*)(spca_of_p_prt[ID_FB_AND - _ID_FB_FIRST_VAR]);
   for(int item=0; item<andbigcomponent->countObject; item++) {
     
     for (int i = 0; i < AND_SIGNALS_IN; i ++)
     {
        int value = arr[item].settings.param[i] & 0xffff;//
        tempReadArray[item*REGISTER_FOR_OBJ+2*i+0] = value;
        value = (arr[item].settings.param[i] >> 16) & 0x7fff;//
        tempReadArray[item*REGISTER_FOR_OBJ+2*i+1] = value;
     }
  }//for
*/
  /*
  Для тих компонетів, де є не один однотипний вхід а декілька (ст. логіка і Журнал подій) після запису треба відсортувати щоб 0-і були вкінці, а числа(id;n; out) іншли в сторону зростання
  */
//}//loadActualData() 

int getANDBigModbusRegister(int adrReg)
{
  //получить содержимое регистра
extern int pointInterface;//метка интерфейса 0-USB 1-RS485
  if(privateANDBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(andbigcomponent->isActiveActualData) setANDBigCountObject(); //к-во обектов
  andbigcomponent->isActiveActualData = 0;
  if(privateANDBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  superSetOperativMarker(andbigcomponent, adrReg);
/*
   __LN_AND *arr = (__LN_AND*)(spca_of_p_prt[ID_FB_AND - _ID_FB_FIRST_VAR]);
  int offset = adrReg-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//индекс субобъекта
  int idxParam = (offset/2)%AND_SIGNALS_IN;//индекс param
  switch(offset%2) {//индекс регистра 
   case 0:
        return  arr[idxSubObj].settings.param[idxParam] & 0xffff;//
   case 1:
        return  (arr[idxSubObj].settings.param[idxParam] >> 16) & 0x7fff;//
  }//switch
*/
  int offset = adrReg-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//индекс субобъекта
  int idxParam = (offset/2)%AND_SIGNALS_IN;//индекс param
  __settings_for_AND *arr =  ((config_settings_modified & MASKA_FOR_BIT(BIT_USB_LOCKS)) == 0 ) ? &(((__LN_AND*)(spca_of_p_prt[ID_FB_AND - _ID_FB_FIRST_VAR])) + idxSubObj)->settings : (((__settings_for_AND*)(sca_of_p[ID_FB_AND - _ID_FB_FIRST_VAR])) + idxSubObj);
  if(pointInterface)//метка интерфейса 0-USB 1-RS485
                        arr =  ((config_settings_modified & MASKA_FOR_BIT(BIT_RS485_LOCKS)) == 0 ) ? &(((__LN_AND*)(spca_of_p_prt[ID_FB_AND - _ID_FB_FIRST_VAR])) + idxSubObj)->settings : (((__settings_for_AND*)(sca_of_p[ID_FB_AND - _ID_FB_FIRST_VAR])) + idxSubObj);

  switch(offset%2) {//индекс регистра 
   case 0:
        return  arr->param[idxParam] & 0xffff;//
   case 1:
        return  (arr->param[idxParam] >> 16) & 0x7fff;//
  }//switch
  return 0;
}//getDOUTBigModbusRegister(int adrReg)
int getANDBigModbusBit(int adrBit)
{
  //получить содержимое бита
  superSetOperativMarker(andbigcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setANDBigModbusRegister(int adrReg, int dataReg)
{
  //записать содержимое регистра
  if(privateANDBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(andbigcomponent->isActiveActualData) setANDBigCountObject(); //к-во обектов
  andbigcomponent->isActiveActualData = 0;
  if(privateANDBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  superSetOperativMarker(andbigcomponent, adrReg);
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
   break; 
   default: return MARKER_OUTPERIMETR;
  }//switch
  return 0;
}//setDOUTBigModbusRegister(int adrReg)
int setANDBigModbusBit(int adrBit, int x)
{
  UNUSED(x);
  //получить содержимое бита
  superSetOperativMarker(andbigcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//setDOUTBigModbusRegister(int adrReg)

void setANDBigCountObject(void) {
//записать к-во обектов
  int cntObj = current_config.n_and;                       //Кількість елементів "І"
  if(cntObj<0) return;
  if(cntObj>TOTAL_OBJ) return;
  andbigcomponent->countObject = cntObj;
}//

void preANDBigReadAction(void) {
//action до чтения
  andbigcomponent->operativMarker[0] = -1;
  andbigcomponent->operativMarker[1] = -1;//оперативный маркер
  andbigcomponent->isActiveActualData = 1;
}//preANDBigReadAction() 

void postANDBigReadAction(void) {
//action после чтения
  if(andbigcomponent->operativMarker[0]<0) return;//не было чтения
}//postANDBigReadAction() 

void preANDBigWriteAction(void) {
//action до записи
  andbigcomponent->operativMarker[0] = -1;
  andbigcomponent->operativMarker[1] = -1;//оперативный маркер
  andbigcomponent->isActiveActualData = 1;
}//preANDBigWriteAction() 

int postANDBigWriteAction(void) {
//action после записи
  if(andbigcomponent->operativMarker[0]<0) return 0;//не было записи
  int offsetTempWriteArray = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//найти смещение TempWriteArray
  int countRegister = andbigcomponent->operativMarker[1]-andbigcomponent->operativMarker[0]+1;
  if(andbigcomponent->operativMarker[1]<0) countRegister = 1;

   __settings_for_AND *arr = (__settings_for_AND*)(sca_of_p[ID_FB_AND - _ID_FB_FIRST_VAR]);
   __settings_for_AND *arr1 = (__settings_for_AND*)(sca_of_p_edit[ID_FB_AND - _ID_FB_FIRST_VAR]);
  for(int i=0; i<countRegister; i++) {
  int offset = i+andbigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;
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
   superSortParam(AND_SIGNALS_IN, &(arr1[idxSubObj].param[0]));//сортировка
   superSortParam(AND_SIGNALS_IN, &(arr[idxSubObj].param[0]));//сортировка
  }//for
  config_settings_modified |= MASKA_FOR_BIT(BIT_CHANGED_SCHEMATIC);
  restart_timeout_idle_new_settings = true;
 return 0;
}//postANDBigWriteAction() 

int privateANDBigGetReg1(int adrReg)
{
  //проверить внутренний периметр
  int count_register = andbigcomponent->countObject*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg1(int adrReg)
int privateANDBigGetReg2(int adrReg)
{
  //проверить внешний периметр
  int count_register = TOTAL_OBJ*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
