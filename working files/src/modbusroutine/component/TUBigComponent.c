#include "header.h"

//начальный регистр в карте памяти
#define BEGIN_ADR_REGISTER 8520
//макс к-во обектов
#define TOTAL_OBJ 128
#define REGISTER_FOR_OBJ 3

int privateTUBigGetReg1(int adrReg);
int privateTUBigGetReg2(int adrReg);

int getTUBigModbusRegister(int);//получить содержимое регистра
int getTUBigModbusBit(int);//получить содержимое бита
int setTUBigModbusRegister(int, int);//получить содержимое регистра
int setTUBigModbusBit(int, int);//получить содержимое бита

void setTUBigCountObject(void);//записать к-во обектов
void preTUBigReadAction(void);//action до чтения
void postTUBigReadAction(void);//action после чтения
void preTUBigWriteAction(void);//action до записи
int postTUBigWriteAction(void);//action после записи
void loadTUBigActualData(void);
int getTUmallModbusBeginAdrRegister(void);

COMPONENT_OBJ *tubigcomponent;

/**************************************/
//подготовка компонента телеуправление
/**************************************/
void constructorTUBigComponent(COMPONENT_OBJ *tubigcomp)
{
  tubigcomponent = tubigcomp;

  tubigcomponent->countObject = 0;//к-во обектов

  tubigcomponent->getModbusRegister = getTUBigModbusRegister;//получить содержимое регистра
  tubigcomponent->getModbusBit      = getTUBigModbusBit;//получить содержимое бита
  tubigcomponent->setModbusRegister = setTUBigModbusRegister;//получить содержимое регистра
  tubigcomponent->setModbusBit      = setTUBigModbusBit;//получить содержимое бита

  tubigcomponent->preReadAction   = preTUBigReadAction;//action до чтения
  tubigcomponent->postReadAction  = postTUBigReadAction;//action после чтения
  tubigcomponent->preWriteAction  = preTUBigWriteAction;//action до записи
  tubigcomponent->postWriteAction = postTUBigWriteAction;//action после записи

  tubigcomponent->isActiveActualData = 0;
}//prepareDVinConfig

/*
void loadTUBigActualData(void) {
int getTUmallModbusBeginAdrRegister(void);
 setTUBigCountObject(); //записать к-во обектов

  //ActualData
   __LN_TU *arr = (__LN_TU*)(spca_of_p_prt[ID_FB_TU - _ID_FB_FIRST_VAR]);
   for(int item=0; item<tubigcomponent->countObject; item++) {

   //Block ТУ 0  item
   int value = arr[item].settings.param[TU_BLOCK] & 0xffff;//
   tempReadArray[item*REGISTER_FOR_OBJ+0] = value;
   value = (arr[item].settings.param[TU_BLOCK] >> 16) & 0x7fff;//
   tempReadArray[item*REGISTER_FOR_OBJ+1] = value;

   //Адрес ТУ 0  item
   value = getTUmallModbusBeginAdrRegister() + item;
   tempReadArray[item*REGISTER_FOR_OBJ+2] = value;
   }//for
}//loadActualData() 
*/

int getTUBigModbusRegister(int adrReg)
{
  //получить содержимое регистра
  if(privateTUBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(tubigcomponent->isActiveActualData) setTUBigCountObject(); //записать к-во обектов
  tubigcomponent->isActiveActualData = 0;
  if(privateTUBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  superSetOperativMarker(tubigcomponent, adrReg);

   __LN_TU *arr = (__LN_TU*)(spca_of_p_prt[ID_FB_TU - _ID_FB_FIRST_VAR]);
  int offset = adrReg-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//индекс субобъекта
  switch(offset%REGISTER_FOR_OBJ) {//индекс регистра 
   case 0:
   //Block ТУ 0  item
    return arr[idxSubObj].settings.param[TU_BLOCK] & 0xffff;//
   case 1:
    return (arr[idxSubObj].settings.param[TU_BLOCK] >> 16) & 0x7fff;//

   case 2:
   //Адрес ТУ 0  item
    return getTUmallModbusBeginAdrRegister() + idxSubObj;
  }//switch

  return 0;//tempReadArray[adrReg-BEGIN_ADR_REGISTER];
}//getDOUTBigModbusRegister(int adrReg)
int getTUBigModbusBit(int adrBit)
{
  //получить содержимое регистра
  superSetOperativMarker(tubigcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setTUBigModbusRegister(int adrReg, int dataReg)
{
  //записать содержимое регистра
  if(privateTUBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(tubigcomponent->isActiveActualData) setTUBigCountObject(); 
  tubigcomponent->isActiveActualData = 0;
  if(privateTUBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  superSetOperativMarker(tubigcomponent, adrReg);
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
   break; 
  default: return MARKER_OUTPERIMETR;
  }//switch
  return 0;
}//getDOUTBigModbusRegister(int adrReg)
int setTUBigModbusBit(int adrBit, int x)
{
  UNUSED(x);
  //получить содержимое регистра
  superSetOperativMarker(tubigcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void setTUBigCountObject(void) {
//записать к-во обектов
  int cntObj = current_config.n_tu;    //Кількість блоків сигналізацій
  if(cntObj<0) return;
  if(cntObj>TOTAL_OBJ) return;
  tubigcomponent->countObject = cntObj;
}//
void preTUBigReadAction(void) {
//action до чтения
  tubigcomponent->operativMarker[0] = -1;
  tubigcomponent->operativMarker[1] = -1;//оперативный маркер
  tubigcomponent->isActiveActualData = 1;
}//
void postTUBigReadAction(void) {
//action после чтения
  if(tubigcomponent->operativMarker[0]<0) return;//не было чтения
}//
void preTUBigWriteAction(void) {
//action до записи
  tubigcomponent->operativMarker[0] = -1;
  tubigcomponent->operativMarker[1] = -1;//оперативный маркер
  tubigcomponent->isActiveActualData = 1;
}//
int postTUBigWriteAction(void) {
//action после записи
  if(tubigcomponent->operativMarker[0]<0) return 0;//не было записи
  int offsetTempWriteArray = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//найти смещение TempWriteArray
  int countRegister = tubigcomponent->operativMarker[1]-tubigcomponent->operativMarker[0]+1;
  if(tubigcomponent->operativMarker[1]<0) countRegister = 1;

//   __LN_TU *arr = (__LN_TU*)(spca_of_p_prt[ID_FB_TU - _ID_FB_FIRST_VAR]);
   __settings_for_TU *arr  = (__settings_for_TU*)(sca_of_p[ID_FB_TU - _ID_FB_FIRST_VAR]);
   __settings_for_TU *arr1 = (__settings_for_TU*)(sca_of_p_edit[ID_FB_TU - _ID_FB_FIRST_VAR]);
  for(int i=0; i<countRegister; i++) {
  int offset = i+tubigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//индекс субобъекта
  switch(offset%REGISTER_FOR_OBJ) {//индекс регистра 

   case 0://Block ТУ 0
        arr1[idxSubObj].param[TU_BLOCK] = arr[idxSubObj].param[TU_BLOCK] &= (uint32_t)~0xffff;
        arr1[idxSubObj].param[TU_BLOCK] = arr[idxSubObj].param[TU_BLOCK] |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
   break;
   case 1://Block ТУ 1
        arr1[idxSubObj].param[TU_BLOCK] = arr[idxSubObj].param[TU_BLOCK] &= (uint32_t)~(0x7fff<<16);
        arr1[idxSubObj].param[TU_BLOCK] = arr[idxSubObj].param[TU_BLOCK] |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
   break; 

   case 2://Адрес ТС
//    arr[idxSubObj].settings.set_delay[ALARM_SET_DELAY_PERIOD] = (tempWriteArray[offsetTempWriteArray+i]);
   break;

 }//switch
  }//for
  config_settings_modified |= MASKA_FOR_BIT(BIT_CHANGED_SETTINGS);
  restart_timeout_idle_new_settings = true;
 return 0;
}//

int privateTUBigGetReg1(int adrReg)
{
  //проверить внутренний периметр
  int count_register = tubigcomponent->countObject*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg1(int adrReg)
int privateTUBigGetReg2(int adrReg)
{
  //проверить внешний периметр
  int count_register = TOTAL_OBJ*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
