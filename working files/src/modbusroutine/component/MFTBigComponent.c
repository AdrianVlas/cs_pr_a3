#include "header.h"

//начальный регистр в карте памяти
#define BEGIN_ADR_REGISTER 6088
//макс к-во обектов
#define TOTAL_OBJ 128
#define REGISTER_FOR_OBJ 6

int privateMFTBigGetReg1(int adrReg);
int privateMFTBigGetReg2(int adrReg);

int getMFTBigModbusRegister(int);//получить содержимое регистра
int getMFTBigModbusBit(int);//получить содержимое бита
int setMFTBigModbusRegister(int, int);//получить содержимое регистра
int setMFTBigModbusBit(int, int);//получить содержимое бита

void setMFTBigCountObject(void);//записать к-во обектов
void preMFTBigReadAction(void);//action до чтения
void postMFTBigReadAction(void);//action после чтения
void preMFTBigWriteAction(void);//action до записи
int postMFTBigWriteAction(void);//action после записи
//void loadMFTBigActualData(void);

COMPONENT_OBJ *mftbigcomponent;

/**************************************/
//подготовка компонента МФТ
/**************************************/
void constructorMFTBigComponent(COMPONENT_OBJ *mftbigcomp)
{
  mftbigcomponent = mftbigcomp;

  mftbigcomponent->countObject = 0;//к-во обектов

  mftbigcomponent->getModbusRegister = getMFTBigModbusRegister;//получить содержимое регистра
  mftbigcomponent->getModbusBit      = getMFTBigModbusBit;//получить содержимое бита
  mftbigcomponent->setModbusRegister = setMFTBigModbusRegister;//получить содержимое регистра
  mftbigcomponent->setModbusBit      = setMFTBigModbusBit;//получить содержимое бита

  mftbigcomponent->preReadAction   = preMFTBigReadAction;//action до чтения
  mftbigcomponent->postReadAction  = postMFTBigReadAction;//action после чтения
  mftbigcomponent->preWriteAction  = preMFTBigWriteAction;//action до записи
  mftbigcomponent->postWriteAction = postMFTBigWriteAction;//action после записи

  mftbigcomponent->isActiveActualData = 0;
}//prepareDVinConfig
/*
void loadMFTBigActualData(void) {
 setMFTBigCountObject(); //записать к-во обектов
  //ActualData
   __LN_TIMER *arr = (__LN_TIMER*)(spca_of_p_prt[ID_FB_TIMER - _ID_FB_FIRST_VAR]);
   for(int item=0; item<mftbigcomponent->countObject; item++) {

   //Таймер паузы  item
   int value = arr[item].settings.set_delay[TIMER_SET_DELAY_PAUSE]/10;
   tempReadArray[item*REGISTER_FOR_OBJ+0] = value;

   //Таймер работы   item
   value = arr[item].settings.set_delay[TIMER_SET_DELAY_WORK]/10;
   tempReadArray[item*REGISTER_FOR_OBJ+1] = value;

   //MFT-IN 1 0 item
   value = arr[item].settings.param[TIMER_LOGIC_INPUT] & 0xffff;//LEDIN 0 СД item
   tempReadArray[item*REGISTER_FOR_OBJ+2] = value;
   value = (arr[item].settings.param[TIMER_LOGIC_INPUT] >> 16) & 0x7fff;//LEDIN 1 СД item
   tempReadArray[item*REGISTER_FOR_OBJ+3] = value;

   //Reset-I  0 item
   value = arr[item].settings.param[TIMER_RESET] & 0xffff;//LEDIN 0 СД item
   tempReadArray[item*REGISTER_FOR_OBJ+4] = value;
   value = (arr[item].settings.param[TIMER_RESET] >> 16) & 0x7fff;//LEDIN 1 СД item
   tempReadArray[item*REGISTER_FOR_OBJ+5] = value;
   }//for

}//loadActualData() 
*/
int getMFTBigModbusRegister(int adrReg)
{
  //получить содержимое регистра
  if(privateMFTBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(mftbigcomponent->isActiveActualData) setMFTBigCountObject(); //к-во обектов
  mftbigcomponent->isActiveActualData = 0;
  if(privateMFTBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  superSetOperativMarker(mftbigcomponent, adrReg);

   __LN_TIMER *arr = (__LN_TIMER*)(spca_of_p_prt[ID_FB_TIMER - _ID_FB_FIRST_VAR]);
  int offset = adrReg-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//индекс субобъекта
  switch(offset%REGISTER_FOR_OBJ) {//индекс регистра 
   case 0:
   //Таймер паузы  item
    return arr[idxSubObj].settings.set_delay[TIMER_SET_DELAY_PAUSE];///10;

   case 1:
   //Таймер работы   item
   return arr[idxSubObj].settings.set_delay[TIMER_SET_DELAY_WORK];///10;

   case 2:
   //MFT-IN 1 0 item
   return arr[idxSubObj].settings.param[TIMER_LOGIC_INPUT] & 0xffff;

   case 3:
   return  (arr[idxSubObj].settings.param[TIMER_LOGIC_INPUT] >> 16) & 0x7fff;

   case 4:
   //Reset-I  0 item
   return arr[idxSubObj].settings.param[TIMER_RESET] & 0xffff;
   case 5:
   return (arr[idxSubObj].settings.param[TIMER_RESET] >> 16) & 0x7fff;
  }//switch

  return 0;
}//getDOUTBigModbusRegister(int adrReg)
int getMFTBigModbusBit(int adrBit)
{
  //получить содержимое регистра
  superSetOperativMarker(mftbigcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setMFTBigModbusRegister(int adrReg, int dataReg)
{
  //записать содержимое регистра
  if(privateMFTBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(mftbigcomponent->isActiveActualData) setMFTBigCountObject(); //к-во обектов
  mftbigcomponent->isActiveActualData = 0;
  if(privateMFTBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  superSetOperativMarker(mftbigcomponent, adrReg);
  superSetTempWriteArray(dataReg);//записать в буфер

  switch((adrReg-BEGIN_ADR_REGISTER)%REGISTER_FOR_OBJ) {
   case 0:
    if(dataReg>60000) return MARKER_ERRORDIAPAZON;
   break; 
   case 1:
    if(dataReg>60000) return MARKER_ERRORDIAPAZON;
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
  default: return MARKER_OUTPERIMETR;
  }//switch
  return 0;
}//getDOUTBigModbusRegister(int adrReg)
int setMFTBigModbusBit(int adrBit, int x)
{
  UNUSED(x);
  //получить содержимое регистра
  superSetOperativMarker(mftbigcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void setMFTBigCountObject(void) {
//записать к-во обектов
  int cntObj = current_config.n_timer;   //Кількість таймерів
  if(cntObj<0) return;
  if(cntObj>TOTAL_OBJ) return;
  mftbigcomponent->countObject = cntObj;
}//
void preMFTBigReadAction(void) {
//action до чтения
  mftbigcomponent->operativMarker[0] = -1;
  mftbigcomponent->operativMarker[1] = -1;//оперативный маркер
  mftbigcomponent->isActiveActualData = 1;
}//
void postMFTBigReadAction(void) {
//action после чтения
  if(mftbigcomponent->operativMarker[0]<0) return;//не было чтения
}//
void preMFTBigWriteAction(void) {
//action до записи
  mftbigcomponent->operativMarker[0] = -1;
  mftbigcomponent->operativMarker[1] = -1;//оперативный маркер
  mftbigcomponent->isActiveActualData = 1;
}//
int postMFTBigWriteAction(void) {
//action после записи
  if(mftbigcomponent->operativMarker[0]<0) return 0;//не было записи
  int offsetTempWriteArray = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//найти смещение TempWriteArray
  int countRegister = mftbigcomponent->operativMarker[1]-mftbigcomponent->operativMarker[0]+1;
  if(mftbigcomponent->operativMarker[1]<0) countRegister = 1;

   __settings_for_TIMER *arr  = (__settings_for_TIMER*)(sca_of_p[ID_FB_TIMER - _ID_FB_FIRST_VAR]);
   __settings_for_TIMER *arr1 = (__settings_for_TIMER*)(sca_of_p_edit[ID_FB_TIMER - _ID_FB_FIRST_VAR]);
  for(int i=0; i<countRegister; i++) {
  int offset = i+mftbigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//индекс субобъекта
  switch(offset%REGISTER_FOR_OBJ) {//индекс регистра 
   case 0://Таймер паузы
    {
    int tt1 = (tempWriteArray[offsetTempWriteArray+i]);
    arr1[idxSubObj].set_delay[TIMER_SET_DELAY_PAUSE] = arr[idxSubObj].set_delay[TIMER_SET_DELAY_PAUSE] = (tempWriteArray[offsetTempWriteArray+i]);
    }
   break;
   case 1://Таймер работы
    {
    int tt1 = (tempWriteArray[offsetTempWriteArray+i]);
    arr1[idxSubObj].set_delay[TIMER_SET_DELAY_WORK] = arr[idxSubObj].set_delay[TIMER_SET_DELAY_WORK] = (tempWriteArray[offsetTempWriteArray+i]);
    }
   break;

   case 2://MFT-IN 0 item
        arr1[idxSubObj].param[TIMER_LOGIC_INPUT] = arr[idxSubObj].param[TIMER_LOGIC_INPUT] &= (uint32_t)~0xffff;
        arr1[idxSubObj].param[TIMER_LOGIC_INPUT] = arr[idxSubObj].param[TIMER_LOGIC_INPUT] |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
   break;
   case 3://MFT-IN 1 item
        arr1[idxSubObj].param[TIMER_LOGIC_INPUT] = arr[idxSubObj].param[TIMER_LOGIC_INPUT] &= (uint32_t)~(0x7fff<<16);
        arr1[idxSubObj].param[TIMER_LOGIC_INPUT] = arr[idxSubObj].param[TIMER_LOGIC_INPUT] |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
   break; 

   case 4://Reset-I 0 item
        arr1[idxSubObj].param[TIMER_RESET] = arr[idxSubObj].param[TIMER_RESET] &= (uint32_t)~0xffff;
        arr1[idxSubObj].param[TIMER_RESET] = arr[idxSubObj].param[TIMER_RESET] |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
   break;
   case 5://Reset-I 1 item
        arr1[idxSubObj].param[TIMER_RESET] = arr[idxSubObj].param[TIMER_RESET] &= (uint32_t)~(0x7fff<<16);
        arr1[idxSubObj].param[TIMER_RESET] = arr[idxSubObj].param[TIMER_RESET] |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
   break; 
 }//switch
  }//for
  config_settings_modified |= MASKA_FOR_BIT(BIT_CHANGED_SETTINGS);
  restart_timeout_idle_new_settings = true;
 return 0;
}//

int privateMFTBigGetReg1(int adrReg)
{
  //проверить внутренний периметр
  int count_register = mftbigcomponent->countObject*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg1(int adrReg)
int privateMFTBigGetReg2(int adrReg)
{
  //проверить внешний периметр
  int count_register = TOTAL_OBJ*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
