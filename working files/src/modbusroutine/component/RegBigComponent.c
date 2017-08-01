#include "header.h"

//начальный регистр в карте пам€ти
#define BEGIN_ADR_REGISTER 15500
//макс к-во обектов
#define REGISTER_FOR_OBJ 2
//макс к-во обектов
#define TOTAL_OBJ 128

int privateRegBigGetReg1(int adrReg);
int privateRegBigGetReg2(int adrReg);

void setRegBigCountObject(void);
int getRegBigModbusRegister(int);//получить содержимое регистра
int getRegBigModbusBit(int);//получить содержимое бита
int setRegBigModbusRegister(int, int);//получить содержимое регистра
int setRegBigModbusBit(int, int);//получить содержимое бита

void preRegBigReadAction(void);//action до чтени€
void postRegBigReadAction(void);//action после чтени€
void preRegBigWriteAction(void);//action до записи
int postRegBigWriteAction(void);//action после записи
void loadRegBigActualData(void);

COMPONENT_OBJ *regbigcomponent;

/**************************************/
//подготовка компонента регистратор
/**************************************/
void constructorRegBigComponent(COMPONENT_OBJ *regbigcomp)
{
  regbigcomponent = regbigcomp;

  regbigcomponent->countObject = 0;//к-во обектов

  regbigcomponent->getModbusRegister = getRegBigModbusRegister;//получить содержимое регистра
  regbigcomponent->getModbusBit      = getRegBigModbusBit;//получить содержимое бита
  regbigcomponent->setModbusRegister = setRegBigModbusRegister;//получить содержимое регистра
  regbigcomponent->setModbusBit      = setRegBigModbusBit;//получить содержимое бита

  regbigcomponent->preReadAction   = preRegBigReadAction;//action до чтени€
  regbigcomponent->postReadAction  = postRegBigReadAction;//action после чтени€
  regbigcomponent->preWriteAction  = preRegBigWriteAction;//action до записи
  regbigcomponent->postWriteAction = postRegBigWriteAction;//action после записи

  regbigcomponent->isActiveActualData = 0;
}//prepareDVinConfig

void loadRegBigActualData(void) {
 setRegBigCountObject(); //записать к-во обектов
  //ActualData
//   __LN_AND *arr = (__LN_AND*)(spca_of_p_prt[ID_FB_INPUT - _ID_FB_FIRST_VAR]);
   //¬рем€ записи доаварийного массива регистратора 
   int value = 0;//arr[item].settings.param[0];
   tempReadArray[0] = value;

   //¬рем€ записи послеаварийного массива регистратора
   value = 0;//arr[item].settings.param[1];
   tempReadArray[1] = value;

   // оличество регистраторов
   value = 0;//arr[item].settings.param[1];
   tempReadArray[2] = value;

   //“екущий регистратор
   value = 0;//arr[item].settings.param[1];
   tempReadArray[3] = value;

   //ќчистить журнал 0
   value = 0;//arr[item].settings.param[0];
   tempReadArray[4] = value;
   //ќчистить журнал 1
   value = 0;//arr[item].settings.param[1];
   tempReadArray[5] = value;

   for(int item=0; item<regbigcomponent->countObject; item++) {
   //¬ход item 0
   value = 0;//arr[item].settings.param[0];
   tempReadArray[6+item*REGISTER_FOR_OBJ+0] = value;
   //¬ход item 1
   value = 0;//arr[item].settings.param[1];
   tempReadArray[6+item*REGISTER_FOR_OBJ+1] = value;
  }//for
}//loadActualData() 

int getRegBigModbusRegister(int adrReg)
{
  //получить содержимое регистра
  if(privateRegBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(regbigcomponent->isActiveActualData) loadRegBigActualData(); //ActualData
  regbigcomponent->isActiveActualData = 0;
  if(privateRegBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  superSetOperativMarker(regbigcomponent, adrReg);

  return tempReadArray[adrReg-BEGIN_ADR_REGISTER];
}//getDOUTBigModbusRegister(int adrReg)
int getRegBigModbusBit(int adrBit)
{
  //получить содержимое регистра
  superSetOperativMarker(regbigcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setRegBigModbusRegister(int adrReg, int dataReg)
{
  //записать содержимое регистра
  if(privateRegBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(regbigcomponent->isActiveActualData) setRegBigCountObject(); //к-во обектов
  regbigcomponent->isActiveActualData = 0;
  if(privateRegBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  superSetOperativMarker(regbigcomponent, adrReg);
  superSetTempWriteArray(dataReg);//записать в буфер

  switch(adrReg-BEGIN_ADR_REGISTER) {
   case 0: //12000
    if(dataReg>250) return MARKER_ERRORDIAPAZON;
    if(dataReg<5) return MARKER_ERRORDIAPAZON;
   break; 
   case 1: //12001
    if(dataReg>1250) return MARKER_ERRORDIAPAZON;
    if(dataReg<5) return MARKER_ERRORDIAPAZON;
   break; 
    case 2://12002
    if(dataReg>99) return MARKER_ERRORDIAPAZON;
   case 3: //12003
    if(dataReg>99) return MARKER_ERRORDIAPAZON;
   break; 
  }//switch

  return 0;
}//getDOUTBigModbusRegister(int adrReg)
int setRegBigModbusBit(int adrBit, int x)
{
  UNUSED(x);
  //получить содержимое регистра
  superSetOperativMarker(regbigcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void setRegBigCountObject(void) {
//записать к-во обектов
  int cntObj = current_config.n_log;    // ≥льк≥сть субмодул≥в ∆урналу под≥й
  if(cntObj<0) return;
  if(cntObj>TOTAL_OBJ) return;
  regbigcomponent->countObject = cntObj;
}//

void preRegBigReadAction(void) {
//action до чтени€
  regbigcomponent->operativMarker[0] = -1;
  regbigcomponent->operativMarker[1] = -1;//оперативный маркер
  regbigcomponent->isActiveActualData = 1;
}//
void postRegBigReadAction(void) {
//action после чтени€
  if(regbigcomponent->operativMarker[0]<0) return;//не было чтени€
}//
void preRegBigWriteAction(void) {
//action до записи
  regbigcomponent->operativMarker[0] = -1;
  regbigcomponent->operativMarker[1] = -1;//оперативный маркер
  regbigcomponent->isActiveActualData = 1;
}//
int postRegBigWriteAction(void) {
//action после записи
  if(regbigcomponent->operativMarker[0]<0) return 0;//не было записи
  //int offsetTempWriteArray = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//найти смещение TempWriteArray
  int countRegister = regbigcomponent->operativMarker[1]-regbigcomponent->operativMarker[0]+1;
  if(regbigcomponent->operativMarker[1]<0) countRegister = 1;

//   __LOG_INPUT *arr = (__LOG_INPUT*)(spca_of_p_prt[ID_FB_EVENT_LOG - _ID_FB_FIRST_VAR]) + 1;
  for(int i=0; i<countRegister; i++) {
  int offset = i+regbigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;
//  int idxSubObj = offset/REGISTER_FOR_OBJ;//индекс субобъекта
//  int clrME = 6;
  switch(offset%REGISTER_FOR_OBJ) {//индекс регистра 
//   case 0://ќчистить журнал 0
//   break;
//   case 1://ќчистить журнал 1
//   break;

   case 0://¬ход 0 item
//        arr[clrME+idxSubObj] &= ~0xffff;
//        arr[clrME+idxSubObj] |= (tempWriteArray[clrME+offsetTempWriteArray+i] & 0xffff);
   break;
   case 1://¬ход 1 item
//        arr[clrME+idxSubObj] &= ~(0x7fff<<16);
//        arr[clrME+idxSubObj] |= ((tempWriteArray[clrME+offsetTempWriteArray+i] & 0x7fff)<<16);//
   break; 

 }//switch
  }//for
  config_settings_modified |= MASKA_FOR_BIT(BIT_CHANGED_SETTINGS);
  restart_timeout_idle_new_settings = true;
  return 0;
}//

int privateRegBigGetReg1(int adrReg)
{
  //проверить внешний периметр
  int count_register = 6+regbigcomponent->countObject*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
int privateRegBigGetReg2(int adrReg)
{
  //проверить внешний периметр
  int count_register = 6+TOTAL_OBJ*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
