#include "header.h"

//начальный регистр в карте памяти
#define BEGIN_ADR_REGISTER 14024
//макс к-во обектов
#define TOTAL_OBJ 128
#define REGISTER_FOR_OBJ 4

int privateIMMSBigGetReg1(int adrReg);
int privateIMMSBigGetReg2(int adrReg);

int getIMMSBigModbusRegister(int);//получить содержимое регистра
int getIMMSBigModbusBit(int);//получить содержимое бита
int setIMMSBigModbusRegister(int, int);//получить содержимое регистра
int setIMMSBigModbusBit(int, int);//получить содержимое бита

void setIMMSBigCountObject(void);//записать к-во обектов
void preIMMSBigReadAction(void);//action до чтения
void postIMMSBigReadAction(void);//action после чтения
void preIMMSBigWriteAction(void);//action до записи
int postIMMSBigWriteAction(void);//action после записи
void repairEditArrayIMMS(int countRegister, __settings_for_INPUT_MMS_BLOCK *arr, __settings_for_INPUT_MMS_BLOCK *arr1);
void config_and_settingsIMMSBig(void);//action активации

COMPONENT_OBJ *immsbigcomponent;

/**************************************/
//подготовка компонента IMMS
/**************************************/
void constructorIMMSBigComponent(COMPONENT_OBJ *immsbigcomp)
{
  immsbigcomponent = immsbigcomp;

  immsbigcomponent->countObject = 0;//к-во обектов

  immsbigcomponent->getModbusRegister = getIMMSBigModbusRegister;//получить содержимое регистра
  immsbigcomponent->getModbusBit      = getIMMSBigModbusBit;//получить содержимое бита
  immsbigcomponent->setModbusRegister = setIMMSBigModbusRegister;//получить содержимое регистра
  immsbigcomponent->setModbusBit      = setIMMSBigModbusBit;//получить содержимое бита

  immsbigcomponent->preReadAction   = preIMMSBigReadAction;//action до чтения
  immsbigcomponent->postReadAction  = postIMMSBigReadAction;//action после чтения
  immsbigcomponent->preWriteAction  = preIMMSBigWriteAction;//action до записи
  immsbigcomponent->postWriteAction = postIMMSBigWriteAction;//action после записи
  immsbigcomponent->config_and_settings = config_and_settingsIMMSBig;//action активации

  immsbigcomponent->isActiveActualData = 0;
}//prepareDVinConfig

int getIMMSBigModbusRegister(int adrReg)
{
  //получить содержимое регистра
extern int pointInterface;//метка интерфейса 0-USB 1-RS485
  if(privateIMMSBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(immsbigcomponent->isActiveActualData) setIMMSBigCountObject(); //к-во обектов
  immsbigcomponent->isActiveActualData = 0;
  if(privateIMMSBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  superSetOperativMarker(immsbigcomponent, adrReg);

  int offset = adrReg-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//индекс субобъекта
  int idxParam = (offset/2)% 2;//индекс param
  __settings_for_INPUT_MMS_BLOCK *arr =  ((config_settings_modified & MASKA_FOR_BIT(BIT_USB_LOCKS)) == 0 ) ? &(((__LN_INPUT_MMS_BLOCK*)(spca_of_p_prt[ID_FB_INPUT_MMS_BLOCK - _ID_FB_FIRST_VAR])) + idxSubObj)->settings : (((__settings_for_INPUT_MMS_BLOCK*)(sca_of_p[ID_FB_INPUT_MMS_BLOCK - _ID_FB_FIRST_VAR])) + idxSubObj);
  if(pointInterface)//метка интерфейса 0-USB 1-RS485
                        arr =  ((config_settings_modified & MASKA_FOR_BIT(BIT_RS485_LOCKS)) == 0 ) ? &(((__LN_INPUT_MMS_BLOCK*)(spca_of_p_prt[ID_FB_INPUT_MMS_BLOCK - _ID_FB_FIRST_VAR])) + idxSubObj)->settings : (((__settings_for_INPUT_MMS_BLOCK*)(sca_of_p[ID_FB_INPUT_MMS_BLOCK - _ID_FB_FIRST_VAR])) + idxSubObj);

  switch(offset%2) {//индекс регистра 
   case 0:
        return  arr->param[idxParam] & 0xffff;//
   case 1:
        return  (arr->param[idxParam] >> 16) & 0x7fff;//
  }//switch
  return 0;
}//getDOUTBigModbusRegister(int adrReg)
int getIMMSBigModbusBit(int x)
{
  //получить содержимое регистра
  UNUSED(x);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setIMMSBigModbusRegister(int adrReg, int dataReg)
{
  //записать содержимое регистра
  if(privateIMMSBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(immsbigcomponent->isActiveActualData) setIMMSBigCountObject(); //к-во обектов
  immsbigcomponent->isActiveActualData = 0;
  if(privateIMMSBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  superSetOperativMarker(immsbigcomponent, adrReg);
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
int setIMMSBigModbusBit(int x, int y)
{
  UNUSED(x);
  UNUSED(y);
  //записать содержимое bit
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void setIMMSBigCountObject(void) {
//записать к-во обектов
  int cntObj = current_config.n_input_MMS_block;  //Кількість елементів IMMS
  if(cntObj<0) return;
  if(cntObj>TOTAL_OBJ) return;
  immsbigcomponent->countObject = cntObj;
}//
void preIMMSBigReadAction(void) {
//action до чтения
  immsbigcomponent->operativMarker[0] = -1;
  immsbigcomponent->operativMarker[1] = -1;//оперативный маркер
  immsbigcomponent->isActiveActualData = 1;
}//
void postIMMSBigReadAction(void) {
//action после чтения
  if(immsbigcomponent->operativMarker[0]<0) return;//не было чтения
}//
void preIMMSBigWriteAction(void) {
//action до записи
  immsbigcomponent->operativMarker[0] = -1;
  immsbigcomponent->operativMarker[1] = -1;//оперативный маркер
  immsbigcomponent->isActiveActualData = 1;
}//
int postIMMSBigWriteAction(void) {
extern int pointInterface;//метка интерфейса 0-USB 1-RS485
extern int upravlconfig_and_settings;//флаг активации компонента
//action после записи
  if(immsbigcomponent->operativMarker[0]<0) return 0;//не было записи
  int offsetTempWriteArray = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//найти смещение TempWriteArray
  int countRegister = immsbigcomponent->operativMarker[1]-immsbigcomponent->operativMarker[0]+1;
  if(immsbigcomponent->operativMarker[1]<0) countRegister = 1;

   __settings_for_INPUT_MMS_BLOCK *arr  = (__settings_for_INPUT_MMS_BLOCK*)(sca_of_p[ID_FB_INPUT_MMS_BLOCK - _ID_FB_FIRST_VAR]);
   __settings_for_INPUT_MMS_BLOCK *arr1 = (__settings_for_INPUT_MMS_BLOCK*)(sca_of_p_edit[ID_FB_INPUT_MMS_BLOCK - _ID_FB_FIRST_VAR]);
//загрузка edit массва
  for(int i=0; i<countRegister; i++) {
  int offset = i+immsbigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;
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
  int offset = i+immsbigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//индекс субобъекта
  int idx_SIGNALS_IN = (offset%REGISTER_FOR_OBJ)/2;//индекс входа субобъекта

  switch(offset%2) {//индекс регистра входа
  case 0:
  case 1:
        if(superValidParam(arr1[idxSubObj].param[idx_SIGNALS_IN])) 
                {//контроль валидности
                repairEditArrayIMMS(countRegister, arr, arr1);//восстановить edit массив
                return 2;//уйти
        }//if
  break;
 }//switch
  }//for

//контроль пройден - редактирование
  for(int i=0; i<countRegister; i++) {
  int offset = i+immsbigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;
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

void repairEditArrayIMMS(int countRegister, __settings_for_INPUT_MMS_BLOCK *arr, __settings_for_INPUT_MMS_BLOCK *arr1) {
  //восстановить edit массив
  for(int i=0; i<countRegister; i++) {
  int offset = i+immsbigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//индекс субобъекта
  int idx_SIGNALS_IN = (offset%REGISTER_FOR_OBJ)/2;//индекс входа субобъекта

  switch(offset%2) {//индекс регистра входа
  case 0:
  case 1:
        arr1[idxSubObj].param[idx_SIGNALS_IN] = arr[idxSubObj].param[idx_SIGNALS_IN];
  break;
 }//switch
  }//for
}//repairEditArray(int countRegister, __settings_for_XOR *arr, __settings_for_XOR *arr1) 

int privateIMMSBigGetReg1(int adrReg)
{
  //проверить внутренний периметр
  int count_register = immsbigcomponent->countObject*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg1(int adrReg)
int privateIMMSBigGetReg2(int adrReg)
{
  //проверить внешний периметр
  int count_register = TOTAL_OBJ*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)

void config_and_settingsIMMSBig(void)
{
}

