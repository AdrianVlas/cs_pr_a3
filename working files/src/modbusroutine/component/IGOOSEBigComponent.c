#include "header.h"

//начальный регистр в карте памяти
#define BEGIN_ADR_REGISTER 13768
//макс к-во обектов
#define TOTAL_OBJ 128
#define REGISTER_FOR_OBJ 2

int privateIGOOSEBigGetReg1(int adrReg);
int privateIGOOSEBigGetReg2(int adrReg);

int getIGOOSEBigModbusRegister(int);//получить содержимое регистра
int getIGOOSEBigModbusBit(int);//получить содержимое бита
int setIGOOSEBigModbusRegister(int, int);//получить содержимое регистра
int setIGOOSEBigModbusBit(int, int);//получить содержимое бита

void setIGOOSEBigCountObject(void);//записать к-во обектов
void preIGOOSEBigReadAction(void);//action до чтения
void postIGOOSEBigReadAction(void);//action после чтения
void preIGOOSEBigWriteAction(void);//action до записи
int postIGOOSEBigWriteAction(void);//action после записи
void loadIGOOSEBigActualData(void);
void repairEditArrayIGOOSE(int countRegister, __settings_for_INPUT_GOOSE_BLOCK *arr, __settings_for_INPUT_GOOSE_BLOCK *arr1);
void config_and_settingsIGOOSEBig(void);//action активации

COMPONENT_OBJ *igoosebigcomponent;

/**************************************/
//подготовка компонента input GOOSE
/**************************************/
void constructorIGOOSEBigComponent(COMPONENT_OBJ *igoosebigcomp)
{
  igoosebigcomponent = igoosebigcomp;

  igoosebigcomponent->countObject = 0;//к-во обектов

  igoosebigcomponent->getModbusRegister = getIGOOSEBigModbusRegister;//получить содержимое регистра
  igoosebigcomponent->getModbusBit      = getIGOOSEBigModbusBit;//получить содержимое бита
  igoosebigcomponent->setModbusRegister = setIGOOSEBigModbusRegister;//получить содержимое регистра
  igoosebigcomponent->setModbusBit      = setIGOOSEBigModbusBit;//получить содержимое бита

  igoosebigcomponent->preReadAction   = preIGOOSEBigReadAction;//action до чтения
  igoosebigcomponent->postReadAction  = postIGOOSEBigReadAction;//action после чтения
  igoosebigcomponent->preWriteAction  = preIGOOSEBigWriteAction;//action до записи
  igoosebigcomponent->postWriteAction = postIGOOSEBigWriteAction;//action после записи
  igoosebigcomponent->config_and_settings = config_and_settingsIGOOSEBig;//action активации

  igoosebigcomponent->isActiveActualData = 0;
}//prepareDVinConfig

int getIGOOSEBigModbusRegister(int adrReg)
{
  //получить содержимое регистра
extern int pointInterface;  
  if(privateIGOOSEBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(igoosebigcomponent->isActiveActualData) setIGOOSEBigCountObject(); //к-во обектов
  igoosebigcomponent->isActiveActualData = 0;
  if(privateIGOOSEBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  superSetOperativMarker(igoosebigcomponent, adrReg);

  int offset = adrReg-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//индекс субобъекта
  __settings_for_INPUT_GOOSE_BLOCK *arr =  ((config_settings_modified & MASKA_FOR_BIT(BIT_USB_LOCKS)) == 0 ) ? &(((__LN_INPUT_GOOSE_BLOCK*)(spca_of_p_prt[ID_FB_INPUT_GOOSE_BLOCK - _ID_FB_FIRST_VAR])) + idxSubObj)->settings : (((__settings_for_INPUT_GOOSE_BLOCK*)(sca_of_p[ID_FB_INPUT_GOOSE_BLOCK - _ID_FB_FIRST_VAR])) + idxSubObj);
  if(pointInterface)//метка интерфейса 0-USB 1-RS485
                        arr =  ((config_settings_modified & MASKA_FOR_BIT(BIT_RS485_LOCKS)) == 0 ) ? &(((__LN_INPUT_GOOSE_BLOCK*)(spca_of_p_prt[ID_FB_INPUT_GOOSE_BLOCK - _ID_FB_FIRST_VAR])) + idxSubObj)->settings : (((__settings_for_INPUT_GOOSE_BLOCK*)(sca_of_p[ID_FB_INPUT_GOOSE_BLOCK - _ID_FB_FIRST_VAR])) + idxSubObj);

  switch(offset%REGISTER_FOR_OBJ) {//индекс регистра 
   case 0:
        return arr->param[0] & 0xffff;//
   case 1:
        return (arr->param[0] >> 16) & 0x7fff;//
  }//switch
  return 0;
}//getIGOOSEBigModbusRegister(int adrReg)
int getIGOOSEBigModbusBit(int x)
{
  //получить содержимое регистра
  UNUSED(x);
  return MARKER_OUTPERIMETR;
}//getIGOOSEBigModbusRegister(int adrReg)
int setIGOOSEBigModbusRegister(int adrReg, int dataReg)
{
  //записать содержимое регистра
  if(privateIGOOSEBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(igoosebigcomponent->isActiveActualData) setIGOOSEBigCountObject(); //к-во обектов
  igoosebigcomponent->isActiveActualData = 0;
  if(privateIGOOSEBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  superSetOperativMarker(igoosebigcomponent, adrReg);
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
}//getIGOOSEBigModbusRegister(int adrReg)
int setIGOOSEBigModbusBit(int x, int y)
{
  UNUSED(x);
  UNUSED(y);
  //получить содержимое регистра
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void setIGOOSEBigCountObject(void) {
//записать к-во обектов
  int cntObj = current_config.n_input_GOOSE_block;   //Кількість елементів IGOOSE
  if(cntObj<0) return;
  if(cntObj>TOTAL_OBJ) return;
  igoosebigcomponent->countObject = cntObj;
}//
void preIGOOSEBigReadAction(void) {
//action до чтения
  igoosebigcomponent->operativMarker[0] = -1;
  igoosebigcomponent->operativMarker[1] = -1;//оперативный маркер
  igoosebigcomponent->isActiveActualData = 1;
}//
void postIGOOSEBigReadAction(void) {
//action после чтения
  if(igoosebigcomponent->operativMarker[0]<0) return;//не было чтения
}//
void preIGOOSEBigWriteAction(void) {
//action до записи
  igoosebigcomponent->operativMarker[0] = -1;
  igoosebigcomponent->operativMarker[1] = -1;//оперативный маркер
  igoosebigcomponent->isActiveActualData = 1;
}//
int postIGOOSEBigWriteAction(void) {
//action после записи
extern int pointInterface;//метка интерфейса 0-USB 1-RS485
  if(igoosebigcomponent->operativMarker[0]<0) return 0;//не было записи
  int offsetTempWriteArray = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//найти смещение TempWriteArray
  int countRegister = igoosebigcomponent->operativMarker[1]-igoosebigcomponent->operativMarker[0]+1;
  if(igoosebigcomponent->operativMarker[1]<0) countRegister = 1;

   __settings_for_INPUT_GOOSE_BLOCK *arr  = (__settings_for_INPUT_GOOSE_BLOCK*)(sca_of_p[ID_FB_INPUT_GOOSE_BLOCK - _ID_FB_FIRST_VAR]);
   __settings_for_INPUT_GOOSE_BLOCK *arr1 = (__settings_for_INPUT_GOOSE_BLOCK*)(sca_of_p_edit[ID_FB_INPUT_GOOSE_BLOCK - _ID_FB_FIRST_VAR]);
//загрузка edit массва
  for(int i=0; i<countRegister; i++) {
  int offset = i+igoosebigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//индекс субобъекта
  switch(offset%2) {//индекс регистра входа
  case 0:

        arr1[idxSubObj].param[0]  &= (uint32_t)~0xffff;
        arr1[idxSubObj].param[0]  |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
  break;
  case 1:

        arr1[idxSubObj].param[0]  &= (uint32_t)~(0x7fff<<16);
        arr1[idxSubObj].param[0]  |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
  break;
  }//switch
  }//for

  //контроль валидности
  for(int i=0; i<countRegister; i++) {
  int offset = i+igoosebigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//индекс субобъекта

  switch(offset%2) {//индекс регистра входа
  case 0:
  case 1:
        if(superValidParam(arr1[idxSubObj].param[0])) 
                {//контроль валидности
                repairEditArrayIGOOSE(countRegister, arr, arr1);//восстановить edit массив
                return 2;//уйти
        }//if
  break;
 }//switch
  }//for

//контроль пройден - редактирование
  for(int i=0; i<countRegister; i++) {
  int offset = i+igoosebigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;
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

  config_settings_modified |= MASKA_FOR_BIT(BIT_CHANGED_SCHEMATIC);
  if(pointInterface)//метка интерфейса 0-USB 1-RS485
     config_settings_modified |= MASKA_FOR_BIT(BIT_RS485_LOCKS);
  else 
     config_settings_modified |= MASKA_FOR_BIT(BIT_USB_LOCKS);
  restart_timeout_idle_new_settings = true;
 return 0;
}//

void repairEditArrayIGOOSE(int countRegister, __settings_for_INPUT_GOOSE_BLOCK *arr, __settings_for_INPUT_GOOSE_BLOCK *arr1) {
  //восстановить edit массив
  for(int i=0; i<countRegister; i++) {
  int offset = i+igoosebigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//индекс субобъекта

  switch(offset%2) {//индекс регистра входа
  case 0:
  case 1:
        arr1[idxSubObj].param[0] = arr[idxSubObj].param[0];
  break;
 }//switch
  }//for
}//repairEditArray(int countRegister, __settings_for_INPUT_GOOSE_BLOCK *arr, __settings_for_INPUT_GOOSE_BLOCK *arr1) 

int privateIGOOSEBigGetReg1(int adrReg)
{
  //проверить внутренний периметр
  int count_register = igoosebigcomponent->countObject*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg1(int adrReg)
int privateIGOOSEBigGetReg2(int adrReg)
{
  //проверить внешний периметр
  int count_register = TOTAL_OBJ*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)

void config_and_settingsIGOOSEBig(void)
{
//action активации
}

