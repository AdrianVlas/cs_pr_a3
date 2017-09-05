#include "header.h"

//начальный регистр в карте памяти
#define BEGIN_ADR_REGISTER 7880
//макс к-во обектов
#define TOTAL_OBJ 128
#define REGISTER_FOR_OBJ 5

int privateTSBigGetReg1(int adrReg);
int privateTSBigGetReg2(int adrReg);

int getTSBigModbusRegister(int);//получить содержимое регистра
int getTSBigModbusBit(int);//получить содержимое бита
int setTSBigModbusRegister(int, int);//получить содержимое регистра
int setTSBigModbusBit(int, int);//получить содержимое бита

void setTSBigCountObject(void);//записать к-во обектов
void preTSBigReadAction(void);//action до чтения
void postTSBigReadAction(void);//action после чтения
void preTSBigWriteAction(void);//action до записи
int postTSBigWriteAction(void);//action после записи
void loadTSBigActualData(void);
int getTSmallModbusBeginAdrRegister(void);
void repairEditArrayTS(int countRegister, __settings_for_TS *arr, __settings_for_TS *arr1);

COMPONENT_OBJ *tsbigcomponent;

/**************************************/
//подготовка компонента телесигнализации
/**************************************/
void constructorTSBigComponent(COMPONENT_OBJ *tsbigcomp)
{
  tsbigcomponent = tsbigcomp;

  tsbigcomponent->countObject = 0;//к-во обектов

  tsbigcomponent->getModbusRegister = getTSBigModbusRegister;//получить содержимое регистра
  tsbigcomponent->getModbusBit      = getTSBigModbusBit;//получить содержимое бита
  tsbigcomponent->setModbusRegister = setTSBigModbusRegister;//получить содержимое регистра
  tsbigcomponent->setModbusBit      = setTSBigModbusBit;//получить содержимое бита

  tsbigcomponent->preReadAction   = preTSBigReadAction;//action до чтения
  tsbigcomponent->postReadAction  = postTSBigReadAction;//action после чтения
  tsbigcomponent->preWriteAction  = preTSBigWriteAction;//action до записи
  tsbigcomponent->postWriteAction = postTSBigWriteAction;//action после записи

  tsbigcomponent->isActiveActualData = 0;
}//prepareDVinConfig

int getTSBigModbusRegister(int adrReg)
{
  //получить содержимое регистра
extern int pointInterface;//метка интерфейса 0-USB 1-RS485
  if(privateTSBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(tsbigcomponent->isActiveActualData) setTSBigCountObject(); //записать к-во обектов
  tsbigcomponent->isActiveActualData = 0;
  if(privateTSBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  superSetOperativMarker(tsbigcomponent, adrReg);

  int offset = adrReg-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//индекс субобъекта
  __settings_for_TS *arr =  ((config_settings_modified & MASKA_FOR_BIT(BIT_USB_LOCKS)) == 0 ) ? &(((__LN_TS*)(spca_of_p_prt[ID_FB_TS - _ID_FB_FIRST_VAR])) + idxSubObj)->settings : (((__settings_for_TS*)(sca_of_p[ID_FB_TS - _ID_FB_FIRST_VAR])) + idxSubObj);
  if(pointInterface)//метка интерфейса 0-USB 1-RS485
                        arr =  ((config_settings_modified & MASKA_FOR_BIT(BIT_RS485_LOCKS)) == 0 ) ? &(((__LN_TS*)(spca_of_p_prt[ID_FB_TS - _ID_FB_FIRST_VAR])) + idxSubObj)->settings : (((__settings_for_TS*)(sca_of_p[ID_FB_TS - _ID_FB_FIRST_VAR])) + idxSubObj);

  switch(offset%REGISTER_FOR_OBJ) {//индекс регистра 
   case 0:
   //In TC 0  item
    return arr->param[TS_LOGIC_INPUT] & 0xffff;//LEDIN 0 СД item
   case 1:
    return (arr->param[TS_LOGIC_INPUT] >> 16) & 0x7fff;//LEDIN 1 СД item

   case 2:
   //Block TC 0  item
    return arr->param[TS_BLOCK] & 0xffff;//LEDIN 0 СД item
   case 3:
    return (arr->param[TS_BLOCK] >> 16) & 0x7fff;//LEDIN 1 СД item

   case 4:
   //Адрес ТС 0  item
   return getTSmallModbusBeginAdrRegister() + idxSubObj;
  }//switch
  return 0;
}//getDOUTBigModbusRegister(int adrReg)
int getTSBigModbusBit(int x)
{
  //получить содержимое регистра
  UNUSED(x);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setTSBigModbusRegister(int adrReg, int dataReg)
{
extern int upravlSetting;//флаг Setting
extern int upravlSchematic;//флаг Shematic
  //записать содержимое регистра
  if(privateTSBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(tsbigcomponent->isActiveActualData) setTSBigCountObject(); 
  tsbigcomponent->isActiveActualData = 0;
  if(privateTSBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  superSetOperativMarker(tsbigcomponent, adrReg);
  superSetTempWriteArray(dataReg);//записать в буфер

  switch((adrReg-BEGIN_ADR_REGISTER)%REGISTER_FOR_OBJ) {
   case 0:
    upravlSchematic = 1;//флаг Shematic
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
   break; 
   case 1:
    //контроль параметров ранжирования
    upravlSchematic = 1;//флаг Shematic
    if(superControlParam(dataReg)) return MARKER_ERRORDIAPAZON;
   break; 
   case 2:
    upravlSchematic = 1;//флаг Shematic
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
   break; 
   case 3:
    //контроль параметров ранжирования
    upravlSchematic = 1;//флаг Shematic
    if(superControlParam(dataReg)) return MARKER_ERRORDIAPAZON;
   break; 
   case 4:
    //контроль параметров ранжирования
    upravlSetting = 1;//флаг Setting
    if(superControlParam(dataReg)) return MARKER_ERRORDIAPAZON;
   break; 
  default: return MARKER_OUTPERIMETR;
  }//switch
  return 0;
}//getDOUTBigModbusRegister(int adrReg)
int setTSBigModbusBit(int x, int y)
{
  UNUSED(x);
  UNUSED(y);
  //получить содержимое регистра
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void setTSBigCountObject(void) {
//записать к-во обектов
  int cntObj = current_config.n_ts;    //Кількість блоків сигналізацій
  if(cntObj<0) return;
  if(cntObj>TOTAL_OBJ) return;
  tsbigcomponent->countObject = cntObj;
}//
void preTSBigReadAction(void) {
//action до чтения
  tsbigcomponent->operativMarker[0] = -1;
  tsbigcomponent->operativMarker[1] = -1;//оперативный маркер
  tsbigcomponent->isActiveActualData = 1;
}//
void postTSBigReadAction(void) {
//action после чтения
  if(tsbigcomponent->operativMarker[0]<0) return;//не было чтения
}//
void preTSBigWriteAction(void) {
//action до записи
  tsbigcomponent->operativMarker[0] = -1;
  tsbigcomponent->operativMarker[1] = -1;//оперативный маркер
  tsbigcomponent->isActiveActualData = 1;
}//
int postTSBigWriteAction(void) {
extern int upravlSetting;//флаг Setting
extern int upravlSchematic;//флаг Shematic
//action после записи
  if(tsbigcomponent->operativMarker[0]<0) return 0;//не было записи
  int offsetTempWriteArray = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//найти смещение TempWriteArray
  int countRegister = tsbigcomponent->operativMarker[1]-tsbigcomponent->operativMarker[0]+1;
  if(tsbigcomponent->operativMarker[1]<0) countRegister = 1;

   __settings_for_TS *arr  = (__settings_for_TS*)(sca_of_p[ID_FB_TS - _ID_FB_FIRST_VAR]);
   __settings_for_TS *arr1 = (__settings_for_TS*)(sca_of_p_edit[ID_FB_TS - _ID_FB_FIRST_VAR]);
//загрузка edit массва
  for(int i=0; i<countRegister; i++) {
  int offset = i+tsbigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//индекс субобъекта
  switch(offset%REGISTER_FOR_OBJ) {//индекс регистра 

   case 0://In TC 0
        arr1[idxSubObj].param[TS_LOGIC_INPUT]  &= (uint32_t)~0xffff;
        arr1[idxSubObj].param[TS_LOGIC_INPUT]  |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
   break;
   case 1://In TC 1
        arr1[idxSubObj].param[TS_LOGIC_INPUT]  &= (uint32_t)~(0x7fff<<16);
        arr1[idxSubObj].param[TS_LOGIC_INPUT]  |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
   break; 

   case 2://Block TC 0
        arr1[idxSubObj].param[TS_BLOCK]  &= (uint32_t)~0xffff;
        arr1[idxSubObj].param[TS_BLOCK]  |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
   break;
   case 3://Block TC 1
        arr1[idxSubObj].param[TS_BLOCK]  &= (uint32_t)~(0x7fff<<16);
        arr1[idxSubObj].param[TS_BLOCK]  |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
   break; 

 }//switch
  }//for

  //контроль валидности
  for(int i=0; i<countRegister; i++) {
  int offset = i+tsbigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//индекс субобъекта
  switch(offset%REGISTER_FOR_OBJ) {//индекс регистра 

   case 0://In TC 0
   case 1://In TC 1
        if(superValidParam(arr1[idxSubObj].param[TS_LOGIC_INPUT])) 
                {//контроль валидности
                repairEditArrayTS(countRegister, arr, arr1);//восстановить edit массив
                return 2;//уйти
        }//if
  break;

   case 2://Block TC 0
   case 3://Block TC 1
        if(superValidParam(arr1[idxSubObj].param[TS_BLOCK]))
                {//контроль валидности
                repairEditArrayTS(countRegister, arr, arr1);//восстановить edit массив
                return 2;//уйти
        }//if
  break;
 }//switch
  }//for

//контроль пройден - редактирование
  for(int i=0; i<countRegister; i++) {
  int offset = i+tsbigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//индекс субобъекта
  switch(offset%REGISTER_FOR_OBJ) {//индекс регистра 

   case 0://In TC 0
        arr1[idxSubObj].param[TS_LOGIC_INPUT] = arr[idxSubObj].param[TS_LOGIC_INPUT] &= (uint32_t)~0xffff;
        arr1[idxSubObj].param[TS_LOGIC_INPUT] = arr[idxSubObj].param[TS_LOGIC_INPUT] |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
   break;
   case 1://In TC 1
        arr1[idxSubObj].param[TS_LOGIC_INPUT] = arr[idxSubObj].param[TS_LOGIC_INPUT] &= (uint32_t)~(0x7fff<<16);
        arr1[idxSubObj].param[TS_LOGIC_INPUT] = arr[idxSubObj].param[TS_LOGIC_INPUT] |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
   break; 

   case 2://Block TC 0
        arr1[idxSubObj].param[TS_BLOCK] = arr[idxSubObj].param[TS_BLOCK] &= (uint32_t)~0xffff;
        arr1[idxSubObj].param[TS_BLOCK] = arr[idxSubObj].param[TS_BLOCK] |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
   break;
   case 3://Block TC 1
        arr1[idxSubObj].param[TS_BLOCK] = arr[idxSubObj].param[TS_BLOCK] &= (uint32_t)~(0x7fff<<16);
        arr1[idxSubObj].param[TS_BLOCK] = arr[idxSubObj].param[TS_BLOCK] |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
   break; 

   case 4://Адрес ТС
   break;

 }//switch
  }//for

  if(upravlSetting)//флаг Setting
     config_settings_modified |= MASKA_FOR_BIT(BIT_CHANGED_SETTINGS);
  if(upravlSchematic)//флаг Shematic
     config_settings_modified |= MASKA_FOR_BIT(BIT_CHANGED_SCHEMATIC);
  restart_timeout_idle_new_settings = true;
 return 0;
}//

void repairEditArrayTS(int countRegister, __settings_for_TS *arr, __settings_for_TS *arr1) {
  //восстановить edit массив
  for(int i=0; i<countRegister; i++) {
  int offset = i+tsbigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//индекс субобъекта
  switch(offset%REGISTER_FOR_OBJ) {//индекс регистра 

   case 0://In TC 0
   case 1://In TC 1
        arr1[idxSubObj].param[TS_LOGIC_INPUT] = arr[idxSubObj].param[TS_LOGIC_INPUT];
   break; 

   case 2://Block TC 0
   case 3://Block TC 1
        arr1[idxSubObj].param[TS_BLOCK] = arr[idxSubObj].param[TS_BLOCK];
   break; 

 }//switch
  }//for
}//repairEditArray(int countRegister, __settings_for_TS *arr, __settings_for_TS *arr1) 

int privateTSBigGetReg1(int adrReg)
{
  //проверить внутренний периметр
  int count_register = tsbigcomponent->countObject*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg1(int adrReg)
int privateTSBigGetReg2(int adrReg)
{
  //проверить внешний периметр
  int count_register = TOTAL_OBJ*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
