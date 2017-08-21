#include "header.h"

//начальный регистр в карте памяти
#define BEGIN_ADR_REGISTER 4792
//макс к-во обектов
#define TOTAL_OBJ 128
#define REGISTER_FOR_OBJ 10

int privateSZSBigGetReg1(int adrReg);
int privateSZSBigGetReg2(int adrReg);

int getSZSBigModbusRegister(int);//получить содержимое регистра
int getSZSBigModbusBit(int);//получить содержимое бита
int setSZSBigModbusRegister(int, int);//получить содержимое регистра
int setSZSBigModbusBit(int, int);//получить содержимое бита

void setSZSBigCountObject(void);//записать к-во обектов
void preSZSBigReadAction(void);//action до чтения
void postSZSBigReadAction(void);//action после чтения
void preSZSBigWriteAction(void);//action до записи
int postSZSBigWriteAction(void);//action после записи
//void loadSZSBigActualData(void);

COMPONENT_OBJ *szsbigcomponent;

/**************************************/
//подготовка компонента СЗС
/**************************************/
void constructorSZSBigComponent(COMPONENT_OBJ *szsbigcomp)
{
  szsbigcomponent = szsbigcomp;

  szsbigcomponent->countObject = 0;//к-во обектов

  szsbigcomponent->getModbusRegister = getSZSBigModbusRegister;//получить содержимое регистра
  szsbigcomponent->getModbusBit      = getSZSBigModbusBit;//получить содержимое бита
  szsbigcomponent->setModbusRegister = setSZSBigModbusRegister;//получить содержимое регистра
  szsbigcomponent->setModbusBit      = setSZSBigModbusBit;//получить содержимое бита

  szsbigcomponent->preReadAction   = preSZSBigReadAction;//action до чтения
  szsbigcomponent->postReadAction  = postSZSBigReadAction;//action после чтения
  szsbigcomponent->preWriteAction  = preSZSBigWriteAction;//action до записи
  szsbigcomponent->postWriteAction = postSZSBigWriteAction;//action после записи

  szsbigcomponent->isActiveActualData = 0;
}//prepareDVinConfig
/*
void loadSZSBigActualData(void) {
 setSZSBigCountObject(); //записать к-во обектов
  //ActualData
   __LN_ALARM *arr = (__LN_ALARM*)(spca_of_p_prt[ID_FB_ALARM - _ID_FB_FIRST_VAR]);
   for(int item=0; item<szsbigcomponent->countObject; item++) {
   //Режим работы СЗС item
   int value = arr[item].settings.control & 0x3;
   tempReadArray[item*REGISTER_FOR_OBJ+0] = value;

   //Таймер СЗС  item
   value = arr[item].settings.set_delay[ALARM_SET_DELAY_PERIOD];
   tempReadArray[item*REGISTER_FOR_OBJ+1] = value / 100;

   //LSSIN1 0 СЗС  item
   value = arr[item].settings.param[ALARM_LOGIC_INPUT] & 0xffff;//LEDIN 0 СД item
   tempReadArray[item*REGISTER_FOR_OBJ+2] = value;
   value = (arr[item].settings.param[ALARM_LOGIC_INPUT] >> 16) & 0x7fff;//LEDIN 1 СД item
   tempReadArray[item*REGISTER_FOR_OBJ+3] = value;

   //Mute-I 0 СЗС   item
   value = arr[item].settings.param[ALARM_IN_MUTE] & 0xffff;//LEDIN 0 СД item
   tempReadArray[item*REGISTER_FOR_OBJ+4] = value;
   value = (arr[item].settings.param[ALARM_IN_MUTE] >> 16) & 0x7fff;//LEDIN 1 СД item
   tempReadArray[item*REGISTER_FOR_OBJ+5] = value;

   //Block-I 0 СЗС    item
   value = arr[item].settings.param[ALARM_IN_BLOCK] & 0xffff;//LEDIN 0 СД item
   tempReadArray[item*REGISTER_FOR_OBJ+6] = value;
   value = (arr[item].settings.param[ALARM_IN_BLOCK] >> 16) & 0x7fff;//LEDIN 1 СД item
   tempReadArray[item*REGISTER_FOR_OBJ+7] = value;

   //Reset-I 0 СЗС   item
   value = arr[item].settings.param[ALARM_RESET] & 0xffff;//LEDIN 0 СД item
   tempReadArray[item*REGISTER_FOR_OBJ+8] = value;
   value = (arr[item].settings.param[ALARM_RESET] >> 16) & 0x7fff;//LEDIN 1 СД item
   tempReadArray[item*REGISTER_FOR_OBJ+9] = value;
   }//for
}//loadActualData() 
*/

int getSZSBigModbusRegister(int adrReg)
{
  //получить содержимое регистра
extern int pointInterface;//метка интерфейса 0-USB 1-RS485
  if(privateSZSBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(szsbigcomponent->isActiveActualData) setSZSBigCountObject(); //к-во обектов
  szsbigcomponent->isActiveActualData = 0;
  if(privateSZSBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  superSetOperativMarker(szsbigcomponent, adrReg);
/*
   __LN_ALARM *arr = (__LN_ALARM*)(spca_of_p_prt[ID_FB_ALARM - _ID_FB_FIRST_VAR]);
  int offset = adrReg-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//индекс субобъекта
  switch(offset%REGISTER_FOR_OBJ) {//индекс регистра 
   case 0:
   //Режим работы СЗС item
    return arr[idxSubObj].settings.control & 0x3;

   case 1:
   //Таймер СЗС  item
    return arr[idxSubObj].settings.set_delay[ALARM_SET_DELAY_PERIOD]/100;

   case 2:
   //LSSIN1 0 СЗС  item
    return arr[idxSubObj].settings.param[ALARM_LOGIC_INPUT] & 0xffff;//LEDIN 0 СД item
   case 3:
    return (arr[idxSubObj].settings.param[ALARM_LOGIC_INPUT] >> 16) & 0x7fff;//LEDIN 1 СД item

   case 4:
   //Mute-I 0 СЗС   item
    return arr[idxSubObj].settings.param[ALARM_IN_MUTE] & 0xffff;//LEDIN 0 СД item
   case 5:
    return (arr[idxSubObj].settings.param[ALARM_IN_MUTE] >> 16) & 0x7fff;//LEDIN 1 СД item

   case 6:
   //Block-I 0 СЗС    item
    return arr[idxSubObj].settings.param[ALARM_IN_BLOCK] & 0xffff;//LEDIN 0 СД item
   case 7:
    return (arr[idxSubObj].settings.param[ALARM_IN_BLOCK] >> 16) & 0x7fff;//LEDIN 1 СД item

   case 8:
   //Reset-I 0 СЗС   item
    return arr[idxSubObj].settings.param[ALARM_RESET] & 0xffff;//LEDIN 0 СД item
   case 9:
    return (arr[idxSubObj].settings.param[ALARM_RESET] >> 16) & 0x7fff;//LEDIN 1 СД item
  }//switch
*/
  int offset = adrReg-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//индекс субобъекта
  __settings_for_ALARM *arr =  ((config_settings_modified & MASKA_FOR_BIT(BIT_USB_LOCKS)) == 0 ) ? &(((__LN_ALARM*)(spca_of_p_prt[ID_FB_ALARM - _ID_FB_FIRST_VAR])) + idxSubObj)->settings : (((__settings_for_ALARM*)(sca_of_p[ID_FB_ALARM - _ID_FB_FIRST_VAR])) + idxSubObj);
  if(pointInterface)//метка интерфейса 0-USB 1-RS485
                        arr =  ((config_settings_modified & MASKA_FOR_BIT(BIT_RS485_LOCKS)) == 0 ) ? &(((__LN_ALARM*)(spca_of_p_prt[ID_FB_ALARM - _ID_FB_FIRST_VAR])) + idxSubObj)->settings : (((__settings_for_ALARM*)(sca_of_p[ID_FB_ALARM - _ID_FB_FIRST_VAR])) + idxSubObj);

  switch(offset%REGISTER_FOR_OBJ) {//индекс регистра 
   case 0:
   //Режим работы СЗС item
    return arr->control & 0x3;

   case 1:
   //Таймер СЗС  item
    return arr->set_delay[ALARM_SET_DELAY_PERIOD]/100;

   case 2:
   //LSSIN1 0 СЗС  item
    return arr->param[ALARM_LOGIC_INPUT] & 0xffff;//LEDIN 0 СД item
   case 3:
    return (arr->param[ALARM_LOGIC_INPUT] >> 16) & 0x7fff;//LEDIN 1 СД item

   case 4:
   //Mute-I 0 СЗС   item
    return arr->param[ALARM_IN_MUTE] & 0xffff;//LEDIN 0 СД item
   case 5:
    return (arr->param[ALARM_IN_MUTE] >> 16) & 0x7fff;//LEDIN 1 СД item

   case 6:
   //Block-I 0 СЗС    item
    return arr->param[ALARM_IN_BLOCK] & 0xffff;//LEDIN 0 СД item
   case 7:
    return (arr->param[ALARM_IN_BLOCK] >> 16) & 0x7fff;//LEDIN 1 СД item

   case 8:
   //Reset-I 0 СЗС   item
    return arr->param[ALARM_RESET] & 0xffff;//LEDIN 0 СД item
   case 9:
    return (arr->param[ALARM_RESET] >> 16) & 0x7fff;//LEDIN 1 СД item
  }//switch
  return 0;
}//getDOUTBigModbusRegister(int adrReg)
int getSZSBigModbusBit(int x)
{
  //получить содержимое регистра
  UNUSED(x);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setSZSBigModbusRegister(int adrReg, int dataReg)
{
  //записать содержимое регистра
  if(privateSZSBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(szsbigcomponent->isActiveActualData) setSZSBigCountObject(); //к-во обектов
  szsbigcomponent->isActiveActualData = 0;
  if(privateSZSBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  superSetOperativMarker(szsbigcomponent, adrReg);
  superSetTempWriteArray(dataReg);//записать в буфер

  switch((adrReg-BEGIN_ADR_REGISTER)%REGISTER_FOR_OBJ) {
   case 0:
    if(dataReg>2) return MARKER_ERRORDIAPAZON;
   break; 
   case 1:
    if(dataReg>320) return MARKER_ERRORDIAPAZON;
    if(dataReg<5) return MARKER_ERRORDIAPAZON;
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
  default: return MARKER_OUTPERIMETR;
  }//switch
  return 0;
}//getDOUTBigModbusRegister(int adrReg)
int setSZSBigModbusBit(int x, int y)
{
  UNUSED(x);
  UNUSED(y);
  //получить содержимое регистра
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void setSZSBigCountObject(void) {
//записать к-во обектов
  int cntObj = current_config.n_alarm;  //Кількість генераторів меандру
  if(cntObj<0) return;
  if(cntObj>TOTAL_OBJ) return;
  szsbigcomponent->countObject = cntObj;
}//
void preSZSBigReadAction(void) {
//action до чтения
  szsbigcomponent->operativMarker[0] = -1;
  szsbigcomponent->operativMarker[1] = -1;//оперативный маркер
  szsbigcomponent->isActiveActualData = 1;
}//
void postSZSBigReadAction(void) {
//action после чтения
  if(szsbigcomponent->operativMarker[0]<0) return;//не было чтения
}//
void preSZSBigWriteAction(void) {
//action до записи
  szsbigcomponent->operativMarker[0] = -1;
  szsbigcomponent->operativMarker[1] = -1;//оперативный маркер
  szsbigcomponent->isActiveActualData = 1;
}//
int postSZSBigWriteAction(void) {
//action после записи
  if(szsbigcomponent->operativMarker[0]<0) return 0;//не было записи
  int offsetTempWriteArray = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//найти смещение TempWriteArray
  int countRegister = szsbigcomponent->operativMarker[1]-szsbigcomponent->operativMarker[0]+1;
  if(szsbigcomponent->operativMarker[1]<0) countRegister = 1;

//   __LN_ALARM *arr = (__LN_ALARM*)(spca_of_p_prt[ID_FB_ALARM - _ID_FB_FIRST_VAR]);
   __settings_for_ALARM *arr  = (__settings_for_ALARM*)(sca_of_p[ID_FB_ALARM - _ID_FB_FIRST_VAR]);
   __settings_for_ALARM *arr1 = (__settings_for_ALARM*)(sca_of_p_edit[ID_FB_ALARM - _ID_FB_FIRST_VAR]);
  for(int i=0; i<countRegister; i++) {
  int offset = i+szsbigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//индекс субобъекта
  switch(offset%REGISTER_FOR_OBJ) {//индекс регистра 
   case 0://Режим работы СЗС
    arr1[idxSubObj].control = arr[idxSubObj].control = (tempWriteArray[offsetTempWriteArray+i]) &0x3;
   break;

   case 1://Таймер СЗС
       arr1[idxSubObj].set_delay[ALARM_SET_DELAY_PERIOD] = arr[idxSubObj].set_delay[ALARM_SET_DELAY_PERIOD] = (tempWriteArray[offsetTempWriteArray+i]*100);
   break;

   case 2://LSSIN1 0
        arr1[idxSubObj].param[ALARM_LOGIC_INPUT] = arr[idxSubObj].param[ALARM_LOGIC_INPUT] &= (uint32_t)~0xffff;
        arr1[idxSubObj].param[ALARM_LOGIC_INPUT] = arr[idxSubObj].param[ALARM_LOGIC_INPUT] |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
   break;
   case 3://LSSIN1 1
        arr1[idxSubObj].param[ALARM_LOGIC_INPUT] = arr[idxSubObj].param[ALARM_LOGIC_INPUT] &= (uint32_t)~(0x7fff<<16);
        arr1[idxSubObj].param[ALARM_LOGIC_INPUT] = arr[idxSubObj].param[ALARM_LOGIC_INPUT] |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
   break; 

   case 4://Mute-I 0
        arr1[idxSubObj].param[ALARM_IN_MUTE] = arr[idxSubObj].param[ALARM_IN_MUTE] &= (uint32_t)~0xffff;
        arr1[idxSubObj].param[ALARM_IN_MUTE] = arr[idxSubObj].param[ALARM_IN_MUTE] |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
   break;
   case 5://Mute-I 1
        arr1[idxSubObj].param[ALARM_IN_MUTE] = arr[idxSubObj].param[ALARM_IN_MUTE] &= (uint32_t)~(0x7fff<<16);
        arr1[idxSubObj].param[ALARM_IN_MUTE] = arr[idxSubObj].param[ALARM_IN_MUTE] |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
   break; 

   case 6://Block-I 0
        arr1[idxSubObj].param[ALARM_IN_BLOCK] = arr[idxSubObj].param[ALARM_IN_BLOCK] &= (uint32_t)~0xffff;
        arr1[idxSubObj].param[ALARM_IN_BLOCK] = arr[idxSubObj].param[ALARM_IN_BLOCK] |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
   break;
   case 7://Block-I 1
        arr1[idxSubObj].param[ALARM_IN_BLOCK] = arr[idxSubObj].param[ALARM_IN_BLOCK] &= (uint32_t)~(0x7fff<<16);
        arr1[idxSubObj].param[ALARM_IN_BLOCK] = arr[idxSubObj].param[ALARM_IN_BLOCK] |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
   break; 

   case 8://Reset-I 0
        arr1[idxSubObj].param[ALARM_RESET] = arr[idxSubObj].param[ALARM_RESET] &= (uint32_t)~0xffff;
        arr1[idxSubObj].param[ALARM_RESET] = arr[idxSubObj].param[ALARM_RESET] |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
   break;
   case 9://Reset-I 1
        arr1[idxSubObj].param[ALARM_RESET] = arr[idxSubObj].param[ALARM_RESET] &= (uint32_t)~(0x7fff<<16);
        arr1[idxSubObj].param[ALARM_RESET] = arr[idxSubObj].param[ALARM_RESET] |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
   break; 

 }//switch
  }//for
  config_settings_modified |= MASKA_FOR_BIT(BIT_CHANGED_SETTINGS);
  restart_timeout_idle_new_settings = true;
  return 0;
}//

int privateSZSBigGetReg1(int adrReg)
{
  //проверить внутренний периметр
  int count_register = szsbigcomponent->countObject*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg1(int adrReg)
int privateSZSBigGetReg2(int adrReg)
{
  //проверить внешний периметр
  int count_register = TOTAL_OBJ*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
