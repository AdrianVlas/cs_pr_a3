#include "header.h"

//начальный регистр в карте памяти
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
void preMEBigReadAction(void);//action до чтения
void postMEBigReadAction(void);//action после чтения
void preMEBigWriteAction(void);//action до записи
int postMEBigWriteAction(void);//action после записи
void loadMEBigActualData(void);

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

  mebigcomponent->preReadAction   = preMEBigReadAction;//action до чтения
  mebigcomponent->postReadAction  = postMEBigReadAction;//action после чтения
  mebigcomponent->preWriteAction  = preMEBigWriteAction;//action до записи
  mebigcomponent->postWriteAction = postMEBigWriteAction;//action после записи

  mebigcomponent->isActiveActualData = 0;
}//prepareDVinConfig

void loadMEBigActualData(void) {
 setMEBigCountObject(); //записать к-во обектов
  //ActualData
 //!!!!!!!!!!
   __LOG_INPUT *arr = (__LOG_INPUT*)(spca_of_p_prt[ID_FB_EVENT_LOG - _ID_FB_FIRST_VAR]) + 1;
   //Очистить журнал 0
   int value = 0;//arr[item].settings.param[0];
   tempReadArray[0] = value;
   //Очистить журнал 1
   value = 0;//arr[item].settings.param[1];
   tempReadArray[1] = value;

   for(int item=0; item<mebigcomponent->countObject; item++) {
   //Вход item 0
        value = arr[item] & 0xffff;//
        tempReadArray[2+item*REGISTER_FOR_OBJ+2*item+0] = value;
        value = (arr[item] >> 16) & 0x7fff;//
        tempReadArray[2+item*REGISTER_FOR_OBJ+2*item+1] = value;
  }//for
}//loadActualData() 

int getMEBigModbusRegister(int adrReg)
{
  //получить содержимое регистра
  if(privateMEBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(mebigcomponent->isActiveActualData) loadMEBigActualData(); //ActualData
  mebigcomponent->isActiveActualData = 0;
  if(privateMEBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  superSetOperativMarker(mebigcomponent, adrReg);

  return tempReadArray[adrReg-BEGIN_ADR_REGISTER];
}//getDOUTBigModbusRegister(int adrReg)
int getMEBigModbusBit(int adrBit)
{
  //получить содержимое регистра
  superSetOperativMarker(mebigcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void setMEBigCountObject(void) {
//записать к-во обектов
  int cntObj = current_config.n_log*LOG_SIGNALS_IN;    //Кількість субмодулів Журналу подій
  if (cntObj > 128) cntObj = 128;
  if(cntObj<0) return;
  if(cntObj>TOTAL_OBJ) return;
  mebigcomponent->countObject = cntObj;
}//
int setMEBigModbusRegister(int adrReg, int dataReg)
{
  //записать содержимое регистра
  if(privateMEBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(mebigcomponent->isActiveActualData) setMEBigCountObject(); //к-во обектов
  mebigcomponent->isActiveActualData = 0;
  if(privateMEBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  superSetOperativMarker(mebigcomponent, adrReg);
  superSetTempWriteArray(dataReg);//записать в буфер

  return 0;
}//getDOUTBigModbusRegister(int adrReg)
int setMEBigModbusBit(int adrBit, int x)
{
  UNUSED(x);
  //получить содержимое регистра
  superSetOperativMarker(mebigcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void preMEBigReadAction(void) {
//action до чтения
  mebigcomponent->operativMarker[0] = -1;
  mebigcomponent->operativMarker[1] = -1;//оперативный маркер
  mebigcomponent->isActiveActualData = 1;
}//
void postMEBigReadAction(void) {
//action после чтения
  if(mebigcomponent->operativMarker[0]<0) return;//не было чтения
}//
void preMEBigWriteAction(void) {
//action до записи
  mebigcomponent->operativMarker[0] = -1;
  mebigcomponent->operativMarker[1] = -1;//оперативный маркер
  mebigcomponent->isActiveActualData = 1;
}//
int postMEBigWriteAction(void) {
//action после записи
  if(mebigcomponent->operativMarker[0]<0) return 0;//не было записи
//  int offsetTempWriteArray = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//найти смещение TempWriteArray
  int countRegister = mebigcomponent->operativMarker[1]-mebigcomponent->operativMarker[0]+1;
  if(mebigcomponent->operativMarker[1]<0) countRegister = 1;

//   __LOG_INPUT *arr = (__LOG_INPUT*)(spca_of_p_prt[ID_FB_EVENT_LOG - _ID_FB_FIRST_VAR]) + 1;
//   __settings_for_INPUT *arr  = (__settings_for_INPUT*)(sca_of_p[ID_FB_EVENT_LOG - _ID_FB_FIRST_VAR]);
//   __settings_for_INPUT *arr1 = (__settings_for_INPUT*)(sca_of_p_edit[ID_FB_EVENT_LOG - _ID_FB_FIRST_VAR]);
  for(int i=0; i<countRegister; i++) {
  int offset = i+mebigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;
 // int idxSubObj = offset/REGISTER_FOR_OBJ;//индекс субобъекта
//  int clrME = 2;
  switch(offset%REGISTER_FOR_OBJ) {//индекс регистра 
//   case 0://Очистить журнал 0
//   break;
//   case 1://Очистить журнал 1
//   break;

   case 0://Вход 0 item
//        arr1[clrME+idxSubObj] = arr[clrME+idxSubObj] &= (uint32_t)~0xffff;
//        arr1[clrME+idxSubObj] = arr[clrME+idxSubObj] |= (tempWriteArray[clrME+offsetTempWriteArray+i] & 0xffff);
   break;
   case 1://Вход 1 item
//        arr1[clrME+idxSubObj] = arr[clrME+idxSubObj] &= (uint32_t)~(0x7fff<<16);
//        arr1[clrME+idxSubObj] = arr[clrME+idxSubObj] |= ((tempWriteArray[clrME+offsetTempWriteArray+i] & 0x7fff)<<16);//
   break; 

 }//switch
  }//for
  config_settings_modified |= MASKA_FOR_BIT(BIT_CHANGED_SETTINGS);
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
