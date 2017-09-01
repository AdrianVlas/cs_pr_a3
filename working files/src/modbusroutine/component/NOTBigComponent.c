#include "header.h"

//начальный регистр в карте памяти
#define BEGIN_ADR_REGISTER 13512
//макс к-во обектов
#define TOTAL_OBJ 128
#define REGISTER_FOR_OBJ 2

int privateNOTBigGetReg1(int adrReg);
int privateNOTBigGetReg2(int adrReg);

int getNOTBigModbusRegister(int);//получить содержимое регистра
int getNOTBigModbusBit(int);//получить содержимое бита
int setNOTBigModbusRegister(int, int);//получить содержимое регистра
int setNOTBigModbusBit(int, int);//получить содержимое бита

void setNOTBigCountObject(void);//записать к-во обектов
void preNOTBigReadAction(void);//action до чтения
void postNOTBigReadAction(void);//action после чтения
void preNOTBigWriteAction(void);//action до записи
int postNOTBigWriteAction(void);//action после записи
void loadNOTBigActualData(void);

COMPONENT_OBJ *notbigcomponent;

/**************************************/
//подготовка компонента NOT
/**************************************/
void constructorNOTBigComponent(COMPONENT_OBJ *notbigcomp)
{
  notbigcomponent = notbigcomp;

  notbigcomponent->countObject = 0;//к-во обектов

  notbigcomponent->getModbusRegister = getNOTBigModbusRegister;//получить содержимое регистра
  notbigcomponent->getModbusBit      = getNOTBigModbusBit;//получить содержимое бита
  notbigcomponent->setModbusRegister = setNOTBigModbusRegister;//получить содержимое регистра
  notbigcomponent->setModbusBit      = setNOTBigModbusBit;//получить содержимое бита

  notbigcomponent->preReadAction   = preNOTBigReadAction;//action до чтения
  notbigcomponent->postReadAction  = postNOTBigReadAction;//action после чтения
  notbigcomponent->preWriteAction  = preNOTBigWriteAction;//action до записи
  notbigcomponent->postWriteAction = postNOTBigWriteAction;//action после записи

  notbigcomponent->isActiveActualData = 0;
}//prepareDVinConfig
/*
void loadNOTBigActualData(void) {
 setNOTBigCountObject(); //записать к-во обектов
  //ActualData
   __LN_NOT *arr = (__LN_NOT*)(spca_of_p_prt[ID_FB_NOT - _ID_FB_FIRST_VAR]);
   for(int item=0; item<notbigcomponent->countObject; item++) {

     for (int i = 0; i < 1; i ++)
     {
        int value = arr[item].settings.param[i] & 0xffff;//
        tempReadArray[item*REGISTER_FOR_OBJ+2*i+0] = value;
        value = (arr[item].settings.param[i] >> 16) & 0x7fff;//
        tempReadArray[item*REGISTER_FOR_OBJ+2*i+1] = value;
     }
   }//for
}//loadActualData() 
*/

int getNOTBigModbusRegister(int adrReg)
{
  //получить содержимое регистра
extern int pointInterface;  
  if(privateNOTBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(notbigcomponent->isActiveActualData) setNOTBigCountObject(); //к-во обектов
  notbigcomponent->isActiveActualData = 0;
  if(privateNOTBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  superSetOperativMarker(notbigcomponent, adrReg);

/*
   __LN_NOT *arr = (__LN_NOT*)(spca_of_p_prt[ID_FB_NOT - _ID_FB_FIRST_VAR]);
  int offset = adrReg-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//индекс субобъекта
  switch(offset%REGISTER_FOR_OBJ) {//индекс регистра 
   case 0:
        return arr[idxSubObj].settings.param[0] & 0xffff;//
   case 1:
        return (arr[idxSubObj].settings.param[0] >> 16) & 0x7fff;//
  }//switch
*/
  int offset = adrReg-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//индекс субобъекта
  __settings_for_NOT *arr =  ((config_settings_modified & MASKA_FOR_BIT(BIT_USB_LOCKS)) == 0 ) ? &(((__LN_NOT*)(spca_of_p_prt[ID_FB_NOT - _ID_FB_FIRST_VAR])) + idxSubObj)->settings : (((__settings_for_NOT*)(sca_of_p[ID_FB_NOT - _ID_FB_FIRST_VAR])) + idxSubObj);
  if(pointInterface)//метка интерфейса 0-USB 1-RS485
                        arr =  ((config_settings_modified & MASKA_FOR_BIT(BIT_RS485_LOCKS)) == 0 ) ? &(((__LN_NOT*)(spca_of_p_prt[ID_FB_NOT - _ID_FB_FIRST_VAR])) + idxSubObj)->settings : (((__settings_for_NOT*)(sca_of_p[ID_FB_NOT - _ID_FB_FIRST_VAR])) + idxSubObj);

  switch(offset%REGISTER_FOR_OBJ) {//индекс регистра 
   case 0:
        return arr->param[0] & 0xffff;//
   case 1:
        return (arr->param[0] >> 16) & 0x7fff;//
  }//switch
  return 0;
}//getDOUTBigModbusRegister(int adrReg)
int getNOTBigModbusBit(int x)
{
  //получить содержимое регистра
  UNUSED(x);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setNOTBigModbusRegister(int adrReg, int dataReg)
{
  //записать содержимое регистра
  if(privateNOTBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(notbigcomponent->isActiveActualData) setNOTBigCountObject(); //к-во обектов
  notbigcomponent->isActiveActualData = 0;
  if(privateNOTBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  superSetOperativMarker(notbigcomponent, adrReg);
  superSetTempWriteArray(dataReg);//записать в буфер

  switch((adrReg-BEGIN_ADR_REGISTER)%REGISTER_FOR_OBJ) {
   case 0:
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
   break; 
   case 1:
    //контроль параметров ранжирования
    if(superControlParam(dataReg)) return MARKER_ERRORDIAPAZON;
   break; 
  default: return MARKER_OUTPERIMETR;
  }//switch
  return 0;
}//getDOUTBigModbusRegister(int adrReg)
int setNOTBigModbusBit(int x, int y)
{
  UNUSED(x);
  UNUSED(y);
  //получить содержимое регистра
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void setNOTBigCountObject(void) {
//записать к-во обектов
  int cntObj = current_config.n_not;   //Кількість елементів "НЕ"
  if(cntObj<0) return;
  if(cntObj>TOTAL_OBJ) return;
  notbigcomponent->countObject = cntObj;
}//
void preNOTBigReadAction(void) {
//action до чтения
  notbigcomponent->operativMarker[0] = -1;
  notbigcomponent->operativMarker[1] = -1;//оперативный маркер
  notbigcomponent->isActiveActualData = 1;
}//
void postNOTBigReadAction(void) {
//action после чтения
  if(notbigcomponent->operativMarker[0]<0) return;//не было чтения
}//
void preNOTBigWriteAction(void) {
//action до записи
  notbigcomponent->operativMarker[0] = -1;
  notbigcomponent->operativMarker[1] = -1;//оперативный маркер
  notbigcomponent->isActiveActualData = 1;
}//
int postNOTBigWriteAction(void) {
//action после записи
  if(notbigcomponent->operativMarker[0]<0) return 0;//не было записи
  int offsetTempWriteArray = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//найти смещение TempWriteArray
  int countRegister = notbigcomponent->operativMarker[1]-notbigcomponent->operativMarker[0]+1;
  if(notbigcomponent->operativMarker[1]<0) countRegister = 1;

   __settings_for_NOT *arr  = (__settings_for_NOT*)(sca_of_p[ID_FB_NOT - _ID_FB_FIRST_VAR]);
   __settings_for_NOT *arr1 = (__settings_for_NOT*)(sca_of_p_edit[ID_FB_NOT - _ID_FB_FIRST_VAR]);
  for(int i=0; i<countRegister; i++) {
  int offset = i+notbigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//индекс субобъекта
  switch(offset%2) {//индекс регистра входа
  case 0:

        arr1[idxSubObj].param[0] = arr[idxSubObj].param[0] &= (uint32_t)~0xffff;
        arr1[idxSubObj].param[0] = arr[idxSubObj].param[0] |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
  break;
  case 1:

        arr1[idxSubObj].param[0] = arr[idxSubObj].param[0] &= (uint32_t)~(0x7fff<<16);
        arr1[idxSubObj].param[0] = arr[idxSubObj].param[0] |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
  break;
  }//switch
  }//for

  //контроль валидности
  for(int i=0; i<countRegister; i++) {
  int offset = i+notbigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//индекс субобъекта

  switch(offset%2) {//индекс регистра входа
  case 0:
  case 1:
        if(superValidParam(arr1[idxSubObj].param[0])) return 2;//контроль валидности
  break;
 }//switch
  }//for

  config_settings_modified |= MASKA_FOR_BIT(BIT_CHANGED_SCHEMATIC);
  restart_timeout_idle_new_settings = true;
 return 0;
}//

int privateNOTBigGetReg1(int adrReg)
{
  //проверить внутренний периметр
  int count_register = notbigcomponent->countObject*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg1(int adrReg)
int privateNOTBigGetReg2(int adrReg)
{
  //проверить внешний периметр
  int count_register = TOTAL_OBJ*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
