#include "header.h"

//начальный регистр в карте памяти
#define BEGIN_ADR_REGISTER 3000
//макс к-во обектов
#define TOTAL_OBJ 128
#define REGISTER_FOR_OBJ 13

int privateSDIBigGetReg1(int adrReg);
int privateSDIBigGetReg2(int adrReg);

int getSDIBigModbusRegister(int);//получить содержимое регистра
int getSDIBigModbusBit(int);//получить содержимое бита
int setSDIBigModbusRegister(int, int);//получить содержимое регистра
int setSDIBigModbusBit(int, int);//получить содержимое бита

void setSDIBigCountObject(void);//записать к-во обектов
void preSDIBigReadAction(void);//action до чтения
void postSDIBigReadAction(void);//action после чтения
void preSDIBigWriteAction(void);//action до записи
int postSDIBigWriteAction(void);//action после записи
void loadSDIBigActualData(void);
void repairEditArraySDI(int countRegister, __settings_for_OUTPUT_LED *arr, __settings_for_OUTPUT_LED *arr1);

COMPONENT_OBJ *sdibigcomponent;

/**************************************/
//подготовка компонента светоиндикаторов
/**************************************/
void constructorSDIBigComponent(COMPONENT_OBJ *sdibigcomp)
{
  sdibigcomponent = sdibigcomp;

  sdibigcomponent->countObject = 0;//к-во обектов

  sdibigcomponent->getModbusRegister = getSDIBigModbusRegister;//получить содержимое регистра
  sdibigcomponent->getModbusBit      = getSDIBigModbusBit;//получить содержимое бита
  sdibigcomponent->setModbusRegister = setSDIBigModbusRegister;//получить содержимое регистра
  sdibigcomponent->setModbusBit      = setSDIBigModbusBit;//получить содержимое бита

  sdibigcomponent->preReadAction   = preSDIBigReadAction;//action до чтения
  sdibigcomponent->postReadAction  = postSDIBigReadAction;//action после чтения
  sdibigcomponent->preWriteAction  = preSDIBigWriteAction;//action до записи
  sdibigcomponent->postWriteAction = postSDIBigWriteAction;//action после записи

  sdibigcomponent->isActiveActualData = 0;
}//prepareDVinConfig

int getSDIBigModbusRegister(int adrReg)
{
  //получить содержимое регистра
extern int pointInterface;//метка интерфейса 0-USB 1-RS485
  if(privateSDIBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(sdibigcomponent->isActiveActualData) setSDIBigCountObject(); //к-во обектов
  sdibigcomponent->isActiveActualData = 0;
  if(privateSDIBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;//MARKER_ERRORPERIMETR;

  superSetOperativMarker(sdibigcomponent, adrReg);

  int offset = adrReg-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//индекс субобъекта
  __settings_for_OUTPUT_LED *arr =  ((config_settings_modified & MASKA_FOR_BIT(BIT_USB_LOCKS)) == 0 ) ? &(((__LN_OUTPUT_LED*)(spca_of_p_prt[ID_FB_LED - _ID_FB_FIRST_VAR])) + idxSubObj)->settings : (((__settings_for_OUTPUT_LED*)(sca_of_p[ID_FB_LED - _ID_FB_FIRST_VAR])) + idxSubObj);
  if(pointInterface)//метка интерфейса 0-USB 1-RS485
                        arr =  ((config_settings_modified & MASKA_FOR_BIT(BIT_RS485_LOCKS)) == 0 ) ? &(((__LN_OUTPUT_LED*)(spca_of_p_prt[ID_FB_LED - _ID_FB_FIRST_VAR])) + idxSubObj)->settings : (((__settings_for_OUTPUT_LED*)(sca_of_p[ID_FB_LED - _ID_FB_FIRST_VAR])) + idxSubObj);

  switch(offset%REGISTER_FOR_OBJ) {//индекс регистра 
   case 0:
     return arr->control;//Параметры СД item

   case 1:
     return arr->param[OUTPUT_LED_LOGIC_INPUT] & 0xffff;//LEDIN 0 СД item
   case 2:
     return (arr->param[OUTPUT_LED_LOGIC_INPUT] >> 16) & 0x7fff;//LEDIN 1 СД item

   case 3:
     return arr->param[OUTPUT_LED_RESET] & 0xffff;//Reset 0 СД item
   case 4:
     return (arr->param[OUTPUT_LED_RESET] >> 16) & 0x7fff;//Reset 1 СД item

   case 5:
     return arr->param[OUTPUT_LED_BL_IMP] & 0xffff;//BL-IMP 0 СД item
   case 6:
     return (arr->param[OUTPUT_LED_BL_IMP] >> 16) & 0x7fff;//BL-IMP 1 СД item

   case 7:
     return arr->param[OUTPUT_LED_MEANDER1_MEANDER2] & 0xffff;//C1/C2 0 СД item
   case 8:
     return (arr->param[OUTPUT_LED_MEANDER1_MEANDER2] >> 16) & 0x7fff;//C1/C2 1 СД item

   case 9:
     return arr->param[OUTPUT_LED_MEANDER1] & 0xffff;//Генератор С1 Имп.0 СД item
   case 10:
     return (arr->param[OUTPUT_LED_MEANDER1] >> 16) & 0x7fff;//Генератор С1 Имп.1 СД item

   case 11:
     return arr->param[OUTPUT_LED_MEANDER2] & 0xffff;//Генератор С2 Имп.0 СД item
   case 12:
     return (arr->param[OUTPUT_LED_MEANDER2] >> 16) & 0x7fff;//Генератор С2 Имп. 1 СД item
  }//switch

  return 0;
}//getSDIBigModbusRegister(int adrReg)
int getSDIBigModbusBit(int x)
{
  //получить содержимое регистра
  UNUSED(x);
  return MARKER_OUTPERIMETR;
}//getSDIBigModbusBit(int )
int setSDIBigModbusRegister(int adrReg, int dataReg)
{
extern int upravlSetting;//флаг Setting
extern int upravlSchematic;//флаг Shematic
  //записать содержимое регистра
  if(privateSDIBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(sdibigcomponent->isActiveActualData) setSDIBigCountObject(); //к-во обектов
  sdibigcomponent->isActiveActualData = 0;
  if(privateSDIBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;//MARKER_ERRORPERIMETR;

  superSetOperativMarker(sdibigcomponent, adrReg);
  superSetTempWriteArray(dataReg);//записать в буфер

  switch((adrReg-BEGIN_ADR_REGISTER)%REGISTER_FOR_OBJ) {
   case 0:
     upravlSetting = 1;//флаг Setting
   break; 
   case 1:
    upravlSchematic = 1;//флаг Shematic
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
   break; 
   case 2:
    //контроль параметров ранжирования
    upravlSchematic = 1;//флаг Shematic
    if(superControlParam(dataReg)) return MARKER_ERRORDIAPAZON;
   break; 
   case 3:
    upravlSchematic = 1;//флаг Shematic
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
   break; 
   case 4:
    //контроль параметров ранжирования
    upravlSchematic = 1;//флаг Shematic
    if(superControlParam(dataReg)) return MARKER_ERRORDIAPAZON;
   break; 
   case 5:
    upravlSchematic = 1;//флаг Shematic
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
   break; 
   case 6:
    //контроль параметров ранжирования
    upravlSchematic = 1;//флаг Shematic
    if(superControlParam(dataReg)) return MARKER_ERRORDIAPAZON;
   break; 
   case 7:
    upravlSchematic = 1;//флаг Shematic
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
   break; 
   case 8:
    //контроль параметров ранжирования
    upravlSchematic = 1;//флаг Shematic
    if(superControlParam(dataReg)) return MARKER_ERRORDIAPAZON;
   break; 
   case 9:
    upravlSchematic = 1;//флаг Shematic
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
   break; 
   case 10:
    //контроль параметров ранжирования
    upravlSchematic = 1;//флаг Shematic
    if(superControlParam_gi(dataReg)) return MARKER_ERRORDIAPAZON;
   break; 
   case 11:
    upravlSchematic = 1;//флаг Shematic
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
   break; 
   case 12:
    //контроль параметров ранжирования
    upravlSchematic = 1;//флаг Shematic
    if(superControlParam_gi(dataReg)) return MARKER_ERRORDIAPAZON;
   break; 
  default: return MARKER_OUTPERIMETR;
  }//switch
  return 0;
}//getDOUTBigModbusRegister(int adrReg)
int setSDIBigModbusBit(int x, int y)
{
  UNUSED(x);
  UNUSED(y);
  //получить содержимое регистра
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void setSDIBigCountObject(void) {
//записать к-во обектов
  int cntObj = current_config.n_led; //Кількість дискретних світлоіндикаторів
  if(cntObj<0) return;
  if(cntObj>TOTAL_OBJ) return;
  sdibigcomponent->countObject = cntObj;
}//
void preSDIBigReadAction(void) {
//action до чтения
  sdibigcomponent->operativMarker[0] = -1;
  sdibigcomponent->operativMarker[1] = -1;//оперативный маркер
  sdibigcomponent->isActiveActualData = 1;
}//
void postSDIBigReadAction(void) {
//action после чтения
  if(sdibigcomponent->operativMarker[0]<0) return;//не было чтения
}//
void preSDIBigWriteAction(void) {
//action до записи
  sdibigcomponent->operativMarker[0] = -1;
  sdibigcomponent->operativMarker[1] = -1;//оперативный маркер
  sdibigcomponent->isActiveActualData = 1;
}//
int postSDIBigWriteAction(void) {
extern int upravlSetting;//флаг Setting
extern int upravlSchematic;//флаг Shematic
extern int pointInterface;//метка интерфейса 0-USB 1-RS485
//action после записи
  if(sdibigcomponent->operativMarker[0]<0) return 0;//не было записи
  int offsetTempWriteArray = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//найти смещение TempWriteArray
  int countRegister = sdibigcomponent->operativMarker[1]-sdibigcomponent->operativMarker[0]+1;
  if(sdibigcomponent->operativMarker[1]<0) countRegister = 1;

   __settings_for_OUTPUT_LED *arr  = (__settings_for_OUTPUT_LED*)(sca_of_p[ID_FB_LED - _ID_FB_FIRST_VAR]);
   __settings_for_OUTPUT_LED *arr1 = (__settings_for_OUTPUT_LED*)(sca_of_p_edit[ID_FB_LED - _ID_FB_FIRST_VAR]);
//загрузка edit массва
  for(int i=0; i<countRegister; i++) {
  int offset = i+sdibigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//индекс субобъекта
  switch(offset%REGISTER_FOR_OBJ) {//индекс регистра 
   case 1://RIN 0
        arr1[idxSubObj].param[OUTPUT_LED_LOGIC_INPUT]  &= (uint32_t)~0xffff;
        arr1[idxSubObj].param[OUTPUT_LED_LOGIC_INPUT]  |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
   break;
   case 2://RIN 1 
        arr1[idxSubObj].param[OUTPUT_LED_LOGIC_INPUT]  &= (uint32_t)~(0x7fff<<16);
        arr1[idxSubObj].param[OUTPUT_LED_LOGIC_INPUT]  |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
   break; 

   case 3://Reset 0 
        arr1[idxSubObj].param[OUTPUT_LED_RESET]  &= (uint32_t)~0xffff;
        arr1[idxSubObj].param[OUTPUT_LED_RESET]  |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
   break;
   case 4://Reset 1 
        arr1[idxSubObj].param[OUTPUT_LED_RESET]  &= (uint32_t)~(0x7fff<<16);
        arr1[idxSubObj].param[OUTPUT_LED_RESET]  |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
   break; 

   case 5://BL-IMP 0 
        arr1[idxSubObj].param[OUTPUT_LED_BL_IMP]  &= (uint32_t)~0xffff;
        arr1[idxSubObj].param[OUTPUT_LED_BL_IMP]  |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
   break;
   case 6://BL-IMP 1 
        arr1[idxSubObj].param[OUTPUT_LED_BL_IMP]  &= (uint32_t)~(0x7fff<<16);
        arr1[idxSubObj].param[OUTPUT_LED_BL_IMP]  |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
   break; 

   case 7://C1/C2 0 
        arr1[idxSubObj].param[OUTPUT_LED_MEANDER1_MEANDER2]  &= (uint32_t)~0xffff;
        arr1[idxSubObj].param[OUTPUT_LED_MEANDER1_MEANDER2]  |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
   break;
   case 8://C1/C2 1 
        arr1[idxSubObj].param[OUTPUT_LED_MEANDER1_MEANDER2]  &= (uint32_t)~(0x7fff<<16);
        arr1[idxSubObj].param[OUTPUT_LED_MEANDER1_MEANDER2]  |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
   break; 

   case 9://Генератор С1 0 
        arr1[idxSubObj].param[OUTPUT_LED_MEANDER1]  &= (uint32_t)~0xffff;
        arr1[idxSubObj].param[OUTPUT_LED_MEANDER1]  |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
   break;
   case 10://Генератор С1 1 
        arr1[idxSubObj].param[OUTPUT_LED_MEANDER1]  &= (uint32_t)~(0x7fff<<16);
        arr1[idxSubObj].param[OUTPUT_LED_MEANDER1]  |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
   break; 

   case 11://Генератор С2 0 
        arr1[idxSubObj].param[OUTPUT_LED_MEANDER2]  &= (uint32_t)~0xffff;
        arr1[idxSubObj].param[OUTPUT_LED_MEANDER2]  |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
   break;
   case 12://Генератор С2 1 
        arr1[idxSubObj].param[OUTPUT_LED_MEANDER2]  &= (uint32_t)~(0x7fff<<16);
        arr1[idxSubObj].param[OUTPUT_LED_MEANDER2]  |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
   break; 
 }//switch
  }//for

  //контроль валидности
  for(int i=0; i<countRegister; i++) {
  int offset = i+sdibigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//индекс субобъекта

  switch(offset%REGISTER_FOR_OBJ) {//индекс регистра 
   case 1://RIN 0 ДВых. item
   case 2://RIN 1 ДВых. item
        if(superValidParam(arr1[idxSubObj].param[OUTPUT_LED_LOGIC_INPUT]))
                {//контроль валидности
                repairEditArraySDI(countRegister, arr, arr1);//восстановить edit массив
                return 2;//уйти
        }//if
  break;

   case 3://Reset 0 ДВых. item
   case 4://Reset 1 ДВых. item
        if(superValidParam(arr1[idxSubObj].param[OUTPUT_LED_RESET])) 
                {//контроль валидности
                repairEditArraySDI(countRegister, arr, arr1);//восстановить edit массив
                return 2;//уйти
        }//if
  break;
   case 5://BL-IMP 0 ДВых. item
   case 6://BL-IMP 1 ДВых. item
        if(superValidParam(arr1[idxSubObj].param[OUTPUT_LED_BL_IMP])) 
                {//контроль валидности
                repairEditArraySDI(countRegister, arr, arr1);//восстановить edit массив
                return 2;//уйти
        }//if
  break;
   case 7://C1/C2 0 ДВых. item
   case 8://C1/C2 1 ДВых. item
        if(superValidParam(arr1[idxSubObj].param[OUTPUT_LED_MEANDER1_MEANDER2])) 
                {//контроль валидности
                repairEditArraySDI(countRegister, arr, arr1);//восстановить edit массив
                return 2;//уйти
        }//if
  break;
   case 9://Генератор С1 0 ДВых. item
   case 10://Генератор С1 1 ДВых. item
        if(superValidParam(arr1[idxSubObj].param[OUTPUT_LED_MEANDER1]))
                {//контроль валидности
                repairEditArraySDI(countRegister, arr, arr1);//восстановить edit массив
                return 2;//уйти
        }//if
  break;
   case 11://Генератор С2 0 ДВых. item
   case 12://Генератор С2 1 ДВых. item
        if(superValidParam(arr1[idxSubObj].param[OUTPUT_LED_MEANDER2]))
                {//контроль валидности
                repairEditArraySDI(countRegister, arr, arr1);//восстановить edit массив
                return 2;//уйти
        }//if
  break;
 }//switch
  }//for

//контроль пройден - редактирование
  for(int i=0; i<countRegister; i++) {
  int offset = i+sdibigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//индекс субобъекта
  switch(offset%REGISTER_FOR_OBJ) {//индекс регистра 
   case 0://Параметры ДВых. item
    arr1[idxSubObj].control = arr[idxSubObj].control = (tempWriteArray[offsetTempWriteArray+i]);
   break;

   case 1://RIN 0
        arr1[idxSubObj].param[OUTPUT_LED_LOGIC_INPUT] = arr[idxSubObj].param[OUTPUT_LED_LOGIC_INPUT] &= (uint32_t)~0xffff;
        arr1[idxSubObj].param[OUTPUT_LED_LOGIC_INPUT] = arr[idxSubObj].param[OUTPUT_LED_LOGIC_INPUT] |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
   break;
   case 2://RIN 1 
        arr1[idxSubObj].param[OUTPUT_LED_LOGIC_INPUT] = arr[idxSubObj].param[OUTPUT_LED_LOGIC_INPUT] &= (uint32_t)~(0x7fff<<16);
        arr1[idxSubObj].param[OUTPUT_LED_LOGIC_INPUT] = arr[idxSubObj].param[OUTPUT_LED_LOGIC_INPUT] |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
   break; 

   case 3://Reset 0 
        arr1[idxSubObj].param[OUTPUT_LED_RESET] = arr[idxSubObj].param[OUTPUT_LED_RESET] &= (uint32_t)~0xffff;
        arr1[idxSubObj].param[OUTPUT_LED_RESET] = arr[idxSubObj].param[OUTPUT_LED_RESET] |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
   break;
   case 4://Reset 1 
        arr1[idxSubObj].param[OUTPUT_LED_RESET] = arr[idxSubObj].param[OUTPUT_LED_RESET] &= (uint32_t)~(0x7fff<<16);
        arr1[idxSubObj].param[OUTPUT_LED_RESET] = arr[idxSubObj].param[OUTPUT_LED_RESET] |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
   break; 

   case 5://BL-IMP 0 
        arr1[idxSubObj].param[OUTPUT_LED_BL_IMP] = arr[idxSubObj].param[OUTPUT_LED_BL_IMP] &= (uint32_t)~0xffff;
        arr1[idxSubObj].param[OUTPUT_LED_BL_IMP] = arr[idxSubObj].param[OUTPUT_LED_BL_IMP] |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
   break;
   case 6://BL-IMP 1 
        arr1[idxSubObj].param[OUTPUT_LED_BL_IMP] = arr[idxSubObj].param[OUTPUT_LED_BL_IMP] &= (uint32_t)~(0x7fff<<16);
        arr1[idxSubObj].param[OUTPUT_LED_BL_IMP] = arr[idxSubObj].param[OUTPUT_LED_BL_IMP] |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
   break; 

   case 7://C1/C2 0 
        arr1[idxSubObj].param[OUTPUT_LED_MEANDER1_MEANDER2] = arr[idxSubObj].param[OUTPUT_LED_MEANDER1_MEANDER2] &= (uint32_t)~0xffff;
        arr1[idxSubObj].param[OUTPUT_LED_MEANDER1_MEANDER2] = arr[idxSubObj].param[OUTPUT_LED_MEANDER1_MEANDER2] |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
   break;
   case 8://C1/C2 1 
        arr1[idxSubObj].param[OUTPUT_LED_MEANDER1_MEANDER2] = arr[idxSubObj].param[OUTPUT_LED_MEANDER1_MEANDER2] &= (uint32_t)~(0x7fff<<16);
        arr1[idxSubObj].param[OUTPUT_LED_MEANDER1_MEANDER2] = arr[idxSubObj].param[OUTPUT_LED_MEANDER1_MEANDER2] |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
   break; 

   case 9://Генератор С1 0 
        arr1[idxSubObj].param[OUTPUT_LED_MEANDER1] = arr[idxSubObj].param[OUTPUT_LED_MEANDER1] &= (uint32_t)~0xffff;
        arr1[idxSubObj].param[OUTPUT_LED_MEANDER1] = arr[idxSubObj].param[OUTPUT_LED_MEANDER1] |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
   break;
   case 10://Генератор С1 1 
        arr1[idxSubObj].param[OUTPUT_LED_MEANDER1] = arr[idxSubObj].param[OUTPUT_LED_MEANDER1] &= (uint32_t)~(0x7fff<<16);
        arr1[idxSubObj].param[OUTPUT_LED_MEANDER1] = arr[idxSubObj].param[OUTPUT_LED_MEANDER1] |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
   break; 

   case 11://Генератор С2 0 
        arr1[idxSubObj].param[OUTPUT_LED_MEANDER2] = arr[idxSubObj].param[OUTPUT_LED_MEANDER2] &= (uint32_t)~0xffff;
        arr1[idxSubObj].param[OUTPUT_LED_MEANDER2] = arr[idxSubObj].param[OUTPUT_LED_MEANDER2] |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
   break;
   case 12://Генератор С2 1 
        arr1[idxSubObj].param[OUTPUT_LED_MEANDER2] = arr[idxSubObj].param[OUTPUT_LED_MEANDER2] &= (uint32_t)~(0x7fff<<16);
        arr1[idxSubObj].param[OUTPUT_LED_MEANDER2] = arr[idxSubObj].param[OUTPUT_LED_MEANDER2] |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
   break; 
 }//switch
  }//for

  if(upravlSetting)//флаг Setting
     config_settings_modified |= MASKA_FOR_BIT(BIT_CHANGED_SETTINGS);
  if(upravlSchematic)//флаг Shematic
     config_settings_modified |= MASKA_FOR_BIT(BIT_CHANGED_SCHEMATIC);
  if(pointInterface)//метка интерфейса 0-USB 1-RS485
     config_settings_modified |= MASKA_FOR_BIT(BIT_RS485_LOCKS);
  else 
     config_settings_modified |= MASKA_FOR_BIT(BIT_USB_LOCKS);
  restart_timeout_idle_new_settings = true;
 return 0;
}//

void repairEditArraySDI(int countRegister, __settings_for_OUTPUT_LED *arr, __settings_for_OUTPUT_LED *arr1) {
  //восстановить edit массив
  for(int i=0; i<countRegister; i++) {
  int offset = i+sdibigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//индекс субобъекта
  switch(offset%REGISTER_FOR_OBJ) {//индекс регистра 
   case 1://RIN 0
   case 2://RIN 1 
        arr1[idxSubObj].param[OUTPUT_LED_LOGIC_INPUT] = arr[idxSubObj].param[OUTPUT_LED_LOGIC_INPUT];
   break; 

   case 3://Reset 0 
   case 4://Reset 1 
        arr1[idxSubObj].param[OUTPUT_LED_RESET] = arr[idxSubObj].param[OUTPUT_LED_RESET];
   break; 

   case 5://BL-IMP 0 
   case 6://BL-IMP 1 
        arr1[idxSubObj].param[OUTPUT_LED_BL_IMP] = arr[idxSubObj].param[OUTPUT_LED_BL_IMP];
   break; 

   case 7://C1/C2 0 
   case 8://C1/C2 1 
        arr1[idxSubObj].param[OUTPUT_LED_MEANDER1_MEANDER2] = arr[idxSubObj].param[OUTPUT_LED_MEANDER1_MEANDER2];
   break; 

   case 9://Генератор С1 0 
   case 10://Генератор С1 1 
        arr1[idxSubObj].param[OUTPUT_LED_MEANDER1] = arr[idxSubObj].param[OUTPUT_LED_MEANDER1];
   break; 

   case 11://Генератор С2 0 
   case 12://Генератор С2 1 
        arr1[idxSubObj].param[OUTPUT_LED_MEANDER2] = arr[idxSubObj].param[OUTPUT_LED_MEANDER2];
   break; 
 }//switch
  }//for
}//repairEditArray(int countRegister, __settings_for_OUTPUT_LED *arr, __settings_for_OUTPUT_LED *arr1) 

int privateSDIBigGetReg1(int adrReg)
{
  //проверить внутренний периметр
  int count_register = sdibigcomponent->countObject*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg1(int adrReg)
int privateSDIBigGetReg2(int adrReg)
{
  //проверить внешний периметр
  int count_register = TOTAL_OBJ*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
