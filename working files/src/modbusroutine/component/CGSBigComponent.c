#include "header.h"

//начальный регистр в карте памяти
#define BEGIN_ADR_REGISTER 6091
//макс к-во обектов
#define REGISTER_FOR_OBJ 4

int privateCGSBigGetReg2(int adrReg);

int getCGSBigModbusRegister(int);//получить содержимое регистра
int getCGSBigModbusBit(int);//получить содержимое бита
int setCGSBigModbusRegister(int, int);// регистра
int setCGSBigModbusBit(int, int);// бита

void setCGSBigCountObject(void);//записать к-во обектов
void preCGSBigReadAction(void);//action до чтения
void postCGSBigReadAction(void);//action после чтения
void preCGSBigWriteAction(void);//action до записи
int postCGSBigWriteAction(void);//action после записи
void loadCGSBigActualData(void);

COMPONENT_OBJ *cgsbigcomponent;
/**************************************/
//подготовка компонента ШГС
/**************************************/
void constructorCGSBigComponent(COMPONENT_OBJ *cgsbigcomp)
{
  cgsbigcomponent = cgsbigcomp;

  cgsbigcomponent->countObject = 4;//к-во обектов

  cgsbigcomponent->getModbusRegister = getCGSBigModbusRegister;//получить содержимое регистра
  cgsbigcomponent->getModbusBit      = getCGSBigModbusBit;//получить содержимое бита
  cgsbigcomponent->setModbusRegister = setCGSBigModbusRegister;//регистра
  cgsbigcomponent->setModbusBit      = setCGSBigModbusBit;// бита

  cgsbigcomponent->preReadAction   = preCGSBigReadAction;//action до чтения
  cgsbigcomponent->postReadAction  = postCGSBigReadAction;//action после чтения
  cgsbigcomponent->preWriteAction  = preCGSBigWriteAction;//action до записи
  cgsbigcomponent->postWriteAction = postCGSBigWriteAction;//action после записи

  cgsbigcomponent->isActiveActualData = 0;
}//prepareDVinConfig

void loadCGSBigActualData(void) {
  //ActualData
   __LN_GROUP_ALARM *arr = (__LN_GROUP_ALARM*)(spca_of_p_prt[ID_FB_GROUP_ALARM - _ID_FB_FIRST_VAR]);
   for(int item=0; item<cgsbigcomponent->countObject; item++) {

   //Параметры ГС item
   int value = arr[item].settings.control &0x3;
   tempReadArray[item*REGISTER_FOR_OBJ+0] = value;

   //Входной ток ГС item
   value = (arr[item].settings.analog_input_control >> group_alarm_analog_ctrl_patten[INDEX_CTRL_GROUP_ALARM_I - _MAX_INDEX_CTRL_GROUP_ALARM_BITS_SETTINGS][0]) & ((1 << group_alarm_analog_ctrl_patten[INDEX_CTRL_GROUP_ALARM_I - _MAX_INDEX_CTRL_GROUP_ALARM_BITS_SETTINGS][1]) - 1);
   tempReadArray[item*REGISTER_FOR_OBJ+1] = value;

   //Приращение тока ГС item
   value = arr[item].settings.pickup[GROUP_ALARM_PICKUP_DELTA_I];
   tempReadArray[item*REGISTER_FOR_OBJ+2] = value;

   //Время tуст ГС item
   value = arr[item].settings.set_delay[GROUP_ALARM_SET_DELAY_DELAY];
   tempReadArray[item*REGISTER_FOR_OBJ+3] = value / 100;
   }//for

  /*
  ...
  
  параметрування вхідного аналового каналу
  1) поле analog_input_control розбите на сегменти
  2) кожен сегмент маж початковий біт і кількість бітів, які для ШГС визначено у 
  
const uint32_t group_alarm_analog_ctrl_patten[MAX_INDEX_CTRL_GROUP_ALARM - _MAX_INDEX_CTRL_GROUP_ALARM_BITS_SETTINGS][2] = {{0, 8}};  
  
  Пояснення
  у даному вупадку цей масвив складається з єдиного елемету(сегменту) і значення для цього єдиного сегменту треба взяти з 0-ого біту analog_input_control і брати 8 біт. Тобто [0-7]
  Це значення вищначає номер струмового каналу:
  0 - не заведено жодного струмового каналу (тільки читається - записати 0 не можна)
  1 - I1
  2 - I2
  3 - i3
  4 - I4
  
  Максимальне число: (NUMBER_ANALOG_CANALES - 1) - бо останній канал - це напруга.
  
  */
}//loadActualData() 

int getCGSBigModbusRegister(int adrReg)
{
  //получить содержимое регистра
  if(privateCGSBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  if(cgsbigcomponent->isActiveActualData) loadCGSBigActualData(); //ActualData
  cgsbigcomponent->isActiveActualData = 0;

  superSetOperativMarker(cgsbigcomponent, adrReg);

  return tempReadArray[adrReg-BEGIN_ADR_REGISTER];
}//getDOUTBigModbusRegister(int adrReg)
int getCGSBigModbusBit(int adrBit)
{
  //получить содержимое регистра
  superSetOperativMarker(cgsbigcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setCGSBigModbusRegister(int adrReg, int dataReg)
{
  //записать содержимое регистра
  if(privateCGSBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  superSetOperativMarker(cgsbigcomponent, adrReg);
  superSetTempWriteArray(dataReg);//записать в буфер

  switch((adrReg-BEGIN_ADR_REGISTER)%REGISTER_FOR_OBJ) {
   case 0://Параметры ГС item
   case 1://Входной ток ГС item
   break; 
   case 2://Приращение тока ГС item
    if(dataReg>500) return MARKER_ERRORDIAPAZON;
    if(dataReg<5)   return MARKER_ERRORDIAPAZON;
   break; 
   case 3://Время tуст ГС item
    if(dataReg>320) return MARKER_ERRORDIAPAZON;
   break; 
  default: return MARKER_OUTPERIMETR;
  }//switch
  return 0;
}//getDOUTBigModbusRegister(int adrReg)
int setCGSBigModbusBit(int adrBit, int x)
{
  UNUSED(x);
  //получить содержимое регистра
  superSetOperativMarker(cgsbigcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void setCGSBigCountObject(void) {
//записать к-во обектов
}//
void preCGSBigReadAction(void) {
//action до чтения
  cgsbigcomponent->operativMarker[0] = -1;
  cgsbigcomponent->operativMarker[1] = -1;//оперативный маркер
  cgsbigcomponent->isActiveActualData = 1;
}//
void postCGSBigReadAction(void) {
//action после чтения
  if(cgsbigcomponent->operativMarker[0]<0) return;//не было чтения
}//
void preCGSBigWriteAction(void) {
//action до записи
  cgsbigcomponent->operativMarker[0] = -1;
  cgsbigcomponent->operativMarker[1] = -1;//оперативный маркер
  cgsbigcomponent->isActiveActualData = 1;
}//
int postCGSBigWriteAction(void) {
//action после записи
  if(cgsbigcomponent->operativMarker[0]<0) return 0;//не было записи
  int offsetTempWriteArray = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//найти смещение TempWriteArray
  int countRegister = cgsbigcomponent->operativMarker[1]-cgsbigcomponent->operativMarker[0]+1;
  if(cgsbigcomponent->operativMarker[1]<0) countRegister = 1;

//   __LN_GROUP_ALARM *arr = (__LN_GROUP_ALARM*)(spca_of_p_prt[ID_FB_GROUP_ALARM - _ID_FB_FIRST_VAR]);
   __settings_for_GROUP_ALARM *arr  = (__settings_for_GROUP_ALARM*)(sca_of_p[ID_FB_GROUP_ALARM - _ID_FB_FIRST_VAR]);
   __settings_for_GROUP_ALARM *arr1 = (__settings_for_GROUP_ALARM*)(sca_of_p_edit[ID_FB_GROUP_ALARM - _ID_FB_FIRST_VAR]);
  for(int i=0; i<countRegister; i++) {
  int offset = i+cgsbigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;
  switch(offset) {//индекс регистра
   case 0://Параметры ГС item
     arr1[0].control = arr[0].control  &= (uint32_t)~0x3;
     arr1[0].control = arr[0].control  |= (tempWriteArray[offsetTempWriteArray+i]) & 0x3;
   break; 
   case 1://Входной ток ГС item
     arr1[1].analog_input_control = arr[1].analog_input_control = (tempWriteArray[offsetTempWriteArray+i]) << 
        (group_alarm_analog_ctrl_patten[INDEX_CTRL_GROUP_ALARM_I - _MAX_INDEX_CTRL_GROUP_ALARM_BITS_SETTINGS][0]) 
              & ((1 << group_alarm_analog_ctrl_patten[INDEX_CTRL_GROUP_ALARM_I - _MAX_INDEX_CTRL_GROUP_ALARM_BITS_SETTINGS][1]) - 1);
   break; 
   case 2://Приращение тока ГС item
    arr1[2].pickup[GROUP_ALARM_PICKUP_DELTA_I] = arr[2].pickup[GROUP_ALARM_PICKUP_DELTA_I] = (tempWriteArray[offsetTempWriteArray+i]);
   break; 
   case 3://Время tуст ГС item
    arr1[3].set_delay[GROUP_ALARM_SET_DELAY_DELAY] = arr[3].set_delay[GROUP_ALARM_SET_DELAY_DELAY] = (tempWriteArray[offsetTempWriteArray+i]);
   break; 
 }//switch
  }//for
  config_settings_modified |= MASKA_FOR_BIT(BIT_CHANGED_SETTINGS);
  restart_timeout_idle_new_settings = true;
 return 0;
}//

int privateCGSBigGetReg2(int adrReg)
{
  //проверить внешний периметр
  int count_register = cgsbigcomponent->countObject*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
