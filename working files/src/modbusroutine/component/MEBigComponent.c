#include "header.h"

//начальный регистр в карте пам€ти
#define BEGIN_ADR_REGISTER 15000
//макс к-во обектов
#define REGISTER_FOR_OBJ 2
//макс к-во обектов
#define TOTAL_OBJ 128

int privateMEBigGetReg1(int adrReg);
int privateMEBigGetReg2(int adrReg);

int getMEBigModbusRegister(int);//получить содержимое регистра
int getMEBigModbusBit(int);//получить содержимое бита
int setMEBigModbusRegister(int, int);//получить содержимое регистра
int setMEBigModbusBit(int, int);//получить содержимое бита

void setMEBigCountObject(void);
void preMEBigReadAction(void);//action до чтени€
void postMEBigReadAction(void);//action после чтени€
void preMEBigWriteAction(void);//action до записи
int postMEBigWriteAction(void);//action после записи
//void loadMEBigActualData(void);

COMPONENT_OBJ *mebigcomponent;

/**************************************/
//подготовка компонента журнал событий
/**************************************/
void constructorMEBigComponent(COMPONENT_OBJ *mebigcomp)
{
  mebigcomponent = mebigcomp;

  mebigcomponent->countObject = 0;//к-во обектов

  mebigcomponent->getModbusRegister = getMEBigModbusRegister;//получить содержимое регистра
  mebigcomponent->getModbusBit      = getMEBigModbusBit;//получить содержимое регистра
  mebigcomponent->setModbusRegister = setMEBigModbusRegister;//получить содержимое регистра
  mebigcomponent->setModbusBit      = setMEBigModbusBit;//получить содержимое регистра

  mebigcomponent->preReadAction   = preMEBigReadAction;//action до чтени€
  mebigcomponent->postReadAction  = postMEBigReadAction;//action после чтени€
  mebigcomponent->preWriteAction  = preMEBigWriteAction;//action до записи
  mebigcomponent->postWriteAction = postMEBigWriteAction;//action после записи

  mebigcomponent->isActiveActualData = 0;
}//prepareDVinConfig

int getMEBigModbusRegister(int adrReg)
{
extern int pointInterface;//метка интерфейса 0-USB 1-RS485
  //получить содержимое регистра
  if(privateMEBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(mebigcomponent->isActiveActualData) setMEBigCountObject(); //записать к-во обектов
  mebigcomponent->isActiveActualData = 0;
  if(privateMEBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  superSetOperativMarker(mebigcomponent, adrReg);

  int offset = adrReg-BEGIN_ADR_REGISTER;

  switch(offset) {//индекс регистра 
   case 0:
   // -во записей 0
     return info_rejestrator_log.number_records & 0xffff;
   case 1:
   // -во записей 1
    return (info_rejestrator_log.number_records >> 16) & 0x7fff;//
  }//switch

  __LOG_INPUT *arr =  ((config_settings_modified & MASKA_FOR_BIT(BIT_USB_LOCKS  )) == 0 ) ? (__LOG_INPUT*)(spca_of_p_prt[ID_FB_EVENT_LOG - _ID_FB_FIRST_VAR]) + 1 : ((__LOG_INPUT*)sca_of_p[ID_FB_EVENT_LOG - _ID_FB_FIRST_VAR]);
  int idxParam = ((offset-2)/2);//индекс param
  if(pointInterface)//метка интерфейса 0-USB 1-RS485
               arr =  ((config_settings_modified & MASKA_FOR_BIT(BIT_RS485_LOCKS)) == 0 ) ? (__LOG_INPUT*)(spca_of_p_prt[ID_FB_EVENT_LOG - _ID_FB_FIRST_VAR]) + 1 : ((__LOG_INPUT*)sca_of_p[ID_FB_EVENT_LOG - _ID_FB_FIRST_VAR]);

  switch((offset-2)%REGISTER_FOR_OBJ) {//индекс регистра 
   case 0:
        return  arr[idxParam] & 0xffff;//
   case 1:
        return  (arr[idxParam] >> 16) & 0x7fff;//
  }//switch

  return 0;
}//getDOUTBigModbusRegister(int adrReg)
int getMEBigModbusBit(int x)
{
  //получить содержимое регистра
  UNUSED(x);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void setMEBigCountObject(void) {
//записать к-во обектов
  int cntObj = current_config.n_log*LOG_SIGNALS_IN;    // ≥льк≥сть субмодул≥в ∆урналу под≥й
  if (cntObj > 128) cntObj = 128;
  if(cntObj<0) return;
  if(cntObj>TOTAL_OBJ) return;
  mebigcomponent->countObject = cntObj;
}//
int setMEBigModbusRegister(int adrReg, int dataReg)
{
extern int upravlSetting;//флаг Setting
extern int upravlSchematic;//флаг Shematic
  //записать содержимое регистра
  if(privateMEBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(mebigcomponent->isActiveActualData) setMEBigCountObject(); //к-во обектов
  mebigcomponent->isActiveActualData = 0;
  if(privateMEBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  superSetOperativMarker(mebigcomponent, adrReg);
  superSetTempWriteArray(dataReg);//записать в буфер

  int offset = adrReg-BEGIN_ADR_REGISTER;

  switch(offset) {//индекс регистра 
   case 0:
   case 1:
   // -во записей 0
     upravlSetting = 1;//флаг Setting
     break;
  }//switch

  int idxParam = ((offset-2)/2);//индекс param
  if(idxParam<0) return 0;

  switch((offset-2)%REGISTER_FOR_OBJ) {//индекс регистра 
   case 0:
        upravlSchematic = 1;//флаг Shematic
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
     break;
   case 1:
        upravlSchematic = 1;//флаг Shematic
    //контроль параметров ранжировани€
    if(superControlParam(dataReg)) return MARKER_ERRORDIAPAZON;
     break;

  }//switch

  return 0;
}//getDOUTBigModbusRegister(int adrReg)
int setMEBigModbusBit(int x, int y)
{
  UNUSED(x);
  UNUSED(y);
  //получить содержимое регистра
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void preMEBigReadAction(void) {
//action до чтени€
  mebigcomponent->operativMarker[0] = -1;
  mebigcomponent->operativMarker[1] = -1;//оперативный маркер
  mebigcomponent->isActiveActualData = 1;
}//
void postMEBigReadAction(void) {
//action после чтени€
  if(mebigcomponent->operativMarker[0]<0) return;//не было чтени€
}//
void preMEBigWriteAction(void) {
//action до записи
  mebigcomponent->operativMarker[0] = -1;
  mebigcomponent->operativMarker[1] = -1;//оперативный маркер
  mebigcomponent->isActiveActualData = 1;
}//
int postMEBigWriteAction(void) {
extern int upravlSetting;//флаг Setting
extern int upravlSchematic;//флаг Shematic
//action после записи
  if(mebigcomponent->operativMarker[0]<0) return 0;//не было записи
  int offsetTempWriteArray = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//найти смещение TempWriteArray
  int countRegister = mebigcomponent->operativMarker[1]-mebigcomponent->operativMarker[0]+1;
  if(mebigcomponent->operativMarker[1]<0) countRegister = 1;

   __LOG_INPUT *arr  = (__LOG_INPUT*)(sca_of_p[ID_FB_EVENT_LOG - _ID_FB_FIRST_VAR]);
   __LOG_INPUT *arr1 = (__LOG_INPUT*)(sca_of_p_edit[ID_FB_EVENT_LOG - _ID_FB_FIRST_VAR]);
  for(int i=0; i<countRegister; i++) {
  int offset = i+mebigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;

  switch(offset) {//индекс регистра 
   case 0:
   // -во записей 0
     info_rejestrator_log.number_records &= (uint32_t)~0xffff;
     info_rejestrator_log.number_records |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
     break;
   case 1:
   // -во записей 1
     info_rejestrator_log.number_records &= (uint32_t)~(0x7fff<<16);
     info_rejestrator_log.number_records |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
     break;
  }//switch

  int idxParam = ((offset-2)/2);//индекс param
  if(idxParam<0) break;
  switch((offset-2)%REGISTER_FOR_OBJ) {//индекс регистра 
   case 0://¬ход 0 item
        arr1[idxParam] = arr[idxParam] &= (uint32_t)~0xffff;
        arr1[idxParam] = arr[idxParam] |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
   break;
   case 1://¬ход 1 item
        arr1[idxParam] = arr[idxParam] &= (uint32_t)~(0x7fff<<16);
        arr1[idxParam] = arr[idxParam] |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
   break; 

 }//switch
  }//for

  //контроль валидности
  for(int i=0; i<countRegister; i++) {
  int offset = i+mebigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;
  int idxParam = ((offset-2)/2);//индекс param
  if(idxParam<0) break;
  switch((offset-2)%REGISTER_FOR_OBJ) {//индекс регистра 
   case 0://¬ход 0 item
   case 1://¬ход 1 item
        if(superValidParam(arr1[idxParam])) return 2;//контроль валидности
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

int privateMEBigGetReg1(int adrReg)
{
  //проверить внутренний периметр
  int count_register = 2+mebigcomponent->countObject*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
int privateMEBigGetReg2(int adrReg)
{
  //проверить внешний периметр
  int count_register = 2+TOTAL_OBJ*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
