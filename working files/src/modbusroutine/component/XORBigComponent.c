#include "header.h"

//начальный регистр в карте памяти
#define BEGIN_ADR_REGISTER 13000
//макс к-во обектов
#define TOTAL_OBJ 128
#define REGISTER_FOR_OBJ 4

int privateXORBigGetReg1(int adrReg);
int privateXORBigGetReg2(int adrReg);

int getXORBigModbusRegister(int);//получить содержимое регистра
int getXORBigModbusBit(int);//получить содержимое бита
int setXORBigModbusRegister(int, int);//получить содержимое регистра
int setXORBigModbusBit(int, int);//получить содержимое бита

void setXORBigCountObject(void);//записать к-во обектов
void preXORBigReadAction(void);//action до чтения
void postXORBigReadAction(void);//action после чтения
void preXORBigWriteAction(void);//action до записи
int postXORBigWriteAction(void);//action после записи
//void loadXORBigActualData(void);

COMPONENT_OBJ *xorbigcomponent;

/**************************************/
//подготовка компонента XOR
/**************************************/
void constructorXORBigComponent(COMPONENT_OBJ *xorbigcomp)
{
  xorbigcomponent = xorbigcomp;

  xorbigcomponent->countObject = 0;//к-во обектов

  xorbigcomponent->getModbusRegister = getXORBigModbusRegister;//получить содержимое регистра
  xorbigcomponent->getModbusBit      = getXORBigModbusBit;//получить содержимое бита
  xorbigcomponent->setModbusRegister = setXORBigModbusRegister;//получить содержимое регистра
  xorbigcomponent->setModbusBit      = setXORBigModbusBit;//получить содержимое бита

  xorbigcomponent->preReadAction   = preXORBigReadAction;//action до чтения
  xorbigcomponent->postReadAction  = postXORBigReadAction;//action после чтения
  xorbigcomponent->preWriteAction  = preXORBigWriteAction;//action до записи
  xorbigcomponent->postWriteAction = postXORBigWriteAction;//action после записи

  xorbigcomponent->isActiveActualData = 0;
}//prepareDVinConfig
/*
void loadXORBigActualData(void) {
 setXORBigCountObject(); //записать к-во обектов
  //ActualData
   __LN_XOR *arr = (__LN_XOR*)(spca_of_p_prt[ID_FB_XOR - _ID_FB_FIRST_VAR]);
   for(int item=0; item<xorbigcomponent->countObject; item++) {

     for (int i = 0; i < 2; i ++)
     {
        int value = arr[item].settings.param[i] & 0xffff;//LEDIN 0 СД item
        tempReadArray[item*REGISTER_FOR_OBJ+2*i+0] = value;
        value = (arr[item].settings.param[i] >> 16) & 0x7fff;//LEDIN 1 СД item
        tempReadArray[item*REGISTER_FOR_OBJ+2*i+1] = value;
     }
   }//for
}//loadActualData() 
*/

int getXORBigModbusRegister(int adrReg)
{
  //получить содержимое регистра
extern int pointInterface;//метка интерфейса 0-USB 1-RS485
  if(privateXORBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(xorbigcomponent->isActiveActualData) setXORBigCountObject(); //к-во обектов
  xorbigcomponent->isActiveActualData = 0;
  if(privateXORBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  superSetOperativMarker(xorbigcomponent, adrReg);
/*
   __LN_XOR *arr = (__LN_XOR*)(spca_of_p_prt[ID_FB_XOR - _ID_FB_FIRST_VAR]);
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
  int idxParam = (offset/2)% 2;//индекс param
  __settings_for_XOR *arr =  ((config_settings_modified & MASKA_FOR_BIT(BIT_USB_LOCKS)) == 0 ) ? &(((__LN_XOR*)(spca_of_p_prt[ID_FB_XOR - _ID_FB_FIRST_VAR])) + idxSubObj)->settings : (((__settings_for_XOR*)(sca_of_p[ID_FB_XOR - _ID_FB_FIRST_VAR])) + idxSubObj);
  if(pointInterface)//метка интерфейса 0-USB 1-RS485
                        arr =  ((config_settings_modified & MASKA_FOR_BIT(BIT_RS485_LOCKS)) == 0 ) ? &(((__LN_XOR*)(spca_of_p_prt[ID_FB_XOR - _ID_FB_FIRST_VAR])) + idxSubObj)->settings : (((__settings_for_XOR*)(sca_of_p[ID_FB_XOR - _ID_FB_FIRST_VAR])) + idxSubObj);

  switch(offset%2) {//индекс регистра 
   case 0:
        return  arr->param[idxParam] & 0xffff;//
   case 1:
        return  (arr->param[idxParam] >> 16) & 0x7fff;//
  }//switch
  return 0;
}//getDOUTBigModbusRegister(int adrReg)
int getXORBigModbusBit(int x)
{
  //получить содержимое регистра
  UNUSED(x);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setXORBigModbusRegister(int adrReg, int dataReg)
{
  //записать содержимое регистра
  if(privateXORBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(xorbigcomponent->isActiveActualData) setXORBigCountObject(); //к-во обектов
  xorbigcomponent->isActiveActualData = 0;
  if(privateXORBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  superSetOperativMarker(xorbigcomponent, adrReg);
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
  default: return MARKER_OUTPERIMETR;
  }//switch
  return 0;
}//getDOUTBigModbusRegister(int adrReg)
int setXORBigModbusBit(int x, int y)
{
  UNUSED(x);
  UNUSED(y);
  //записать содержимое bit
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void setXORBigCountObject(void) {
//записать к-во обектов
  int cntObj = current_config.n_xor;  //Кількість елементів "Викл.АБО"
  if(cntObj<0) return;
  if(cntObj>TOTAL_OBJ) return;
  xorbigcomponent->countObject = cntObj;
}//
void preXORBigReadAction(void) {
//action до чтения
  xorbigcomponent->operativMarker[0] = -1;
  xorbigcomponent->operativMarker[1] = -1;//оперативный маркер
  xorbigcomponent->isActiveActualData = 1;
}//
void postXORBigReadAction(void) {
//action после чтения
  if(xorbigcomponent->operativMarker[0]<0) return;//не было чтения
}//
void preXORBigWriteAction(void) {
//action до записи
  xorbigcomponent->operativMarker[0] = -1;
  xorbigcomponent->operativMarker[1] = -1;//оперативный маркер
  xorbigcomponent->isActiveActualData = 1;
}//
int postXORBigWriteAction(void) {
//action после записи
  if(xorbigcomponent->operativMarker[0]<0) return 0;//не было записи
  int offsetTempWriteArray = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//найти смещение TempWriteArray
  int countRegister = xorbigcomponent->operativMarker[1]-xorbigcomponent->operativMarker[0]+1;
  if(xorbigcomponent->operativMarker[1]<0) countRegister = 1;

//   __LN_XOR *arr = (__LN_XOR*)(spca_of_p_prt[ID_FB_XOR - _ID_FB_FIRST_VAR]);
   __settings_for_XOR *arr  = (__settings_for_XOR*)(sca_of_p[ID_FB_XOR - _ID_FB_FIRST_VAR]);
   __settings_for_XOR *arr1 = (__settings_for_XOR*)(sca_of_p_edit[ID_FB_XOR - _ID_FB_FIRST_VAR]);
  for(int i=0; i<countRegister; i++) {
  int offset = i+xorbigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;
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

  //контроль валидности
  for(int i=0; i<countRegister; i++) {
  int offset = i+xorbigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//индекс субобъекта
  int idx_SIGNALS_IN = (offset%REGISTER_FOR_OBJ)/2;//индекс входа субобъекта

  switch(offset%2) {//индекс регистра входа
  case 0:
  case 1:
        if(superValidParam(arr1[idxSubObj].param[idx_SIGNALS_IN])) return 2;//контроль валидности
  break;
 }//switch
   superSortParam(2, &(arr1[idxSubObj].param[0]));//сортировка
   superSortParam(2, &(arr[idxSubObj].param[0]));//сортировка
  }//for

  config_settings_modified |= MASKA_FOR_BIT(BIT_CHANGED_SCHEMATIC);
  restart_timeout_idle_new_settings = true;
 return 0;
}//

int privateXORBigGetReg1(int adrReg)
{
  //проверить внутренний периметр
  int count_register = xorbigcomponent->countObject*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg1(int adrReg)
int privateXORBigGetReg2(int adrReg)
{
  //проверить внешний периметр
  int count_register = TOTAL_OBJ*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
