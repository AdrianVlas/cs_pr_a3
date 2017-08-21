//#include <QtWidgets>
#include "header.h"

//начальный регистр в карте памяти
#define BEGIN_ADR_REGISTER 900
//макс к-во обектов
#define TOTAL_OBJ 128
#define REGISTER_FOR_OBJ 2

int privateDVBigGetReg1(int adrReg);
int privateDVBigGetReg2(int adrReg);

int getDVBigModbusRegister(int);//получить содержимое регистра
int getDVBigModbusBit(int);//получить содержимое бита
int setDVBigModbusRegister(int, int);// регистра
int setDVBigModbusBit(int, int);// бита

void setDVBigCountObject(void);//записать к-во обектов
void preDVBigReadAction(void);//action до чтения
void postDVBigReadAction(void);//action после чтения
void preDVBigWriteAction(void);//action до записи
int postDVBigWriteAction(void);//action после записи
//void loadDVBigActualData(void);

COMPONENT_OBJ *dvbigcomponent;

/**************************************/
//подготовка компонента ДВ
/**************************************/
void constructorDVBigComponent(COMPONENT_OBJ *dvbigcomp)
{
  dvbigcomponent = dvbigcomp;

  dvbigcomponent->countObject = 0;//к-во обектов

  dvbigcomponent->getModbusRegister = getDVBigModbusRegister;//получить содержимое регистра
  dvbigcomponent->getModbusBit      = getDVBigModbusBit;//получить содержимое бита
  dvbigcomponent->setModbusRegister = setDVBigModbusRegister;// регистра
  dvbigcomponent->setModbusBit      = setDVBigModbusBit;// бита

  dvbigcomponent->preReadAction   = preDVBigReadAction;//action до чтения
  dvbigcomponent->postReadAction  = postDVBigReadAction;//action после чтения
  dvbigcomponent->preWriteAction  = preDVBigWriteAction;//action до записи
  dvbigcomponent->postWriteAction = postDVBigWriteAction;//action после записи

  dvbigcomponent->isActiveActualData = 0;
}//prepareDVinConfig
/*
void loadDVBigActualData(void) {
 setDVBigCountObject(); //записать к-во обектов

  //ActualData
   __LN_INPUT *arr = (__LN_INPUT*)(spca_of_p_prt[ID_FB_INPUT - _ID_FB_FIRST_VAR]);
   for(int item=0; item<dvbigcomponent->countObject; item++) {
   int value = (((arr[item].settings.control & (1 << INDEX_CTRL_INPUT_TYPE_SIGNAL)) !=0) << 0) | (1 << 1) | ((V110_V220 != 0) << 2);
   tempReadArray[item*REGISTER_FOR_OBJ+0] = value;
   value = arr[item].settings.set_delay[INPUT_SET_DELAY_DOPUSK];
   tempReadArray[item*REGISTER_FOR_OBJ+1] = value;
  }//for
*/
  /*
  1. Адресу потрібного елементу вибраного функціонального блоку визначаємо як і для Small
  2. Якщо працюємо з структурою ***_prt, то тип береться __LN_XXX у всіх інших випадках тип береться __settings_for_ххх
  __LN_XXX включає у себе _settings_for_ххх
  
  3. 
  enum _XXX__output_signals - перечислення номерів виходів (починається з 0 але для параметрування зв'язків треба, щоб номер починався з 1, тобто додати 1 при встановлкенні зв'язку або відняти одиницію для розшифровки встановленого зв'язку)
  enum _XXX_d_trigger  - тільки для логіки
  enum _XXX_input_signal - перечислення номерів входів
  enum _settings_delay_of_XXX - перечислення всіх витримок
  enum __index_ctrl_xxx - перечислення всіх "ключів" управління
  enum _settings_pickup_of_XXX перечислення всіх уставок
  
  4. Поля налаштуванння
  uint32_t param[XXX_SIGNALS_IN] - адреса виходу, який заводиться на даний вхід. Кодується (id; N; out) id - з enum _id_fb; N і out починаються з 1-ці
  
  int32_t pickup[GROUP_ALARM_PICKUPS] - уставки (з точністю до мілі-величин)
  int32_t set_delay[XXX_SET_DELAYS] - витримки (з точністю до мс)
  uint32_t control - управліннгя
  uint32_t analog_input_control - для ШГС вибір аналогових каналів
  
  */
//}//loadActualData() 

int getDVBigModbusRegister(int adrReg)
{
extern int pointInterface;//метка интерфейса 0-USB 1-RS485
  //получить содержимое регистра
  if(privateDVBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(dvbigcomponent->isActiveActualData) setDVBigCountObject(); //к-во обектов
  dvbigcomponent->isActiveActualData = 0;
  if(privateDVBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;//MARKER_ERRORPERIMETR;

  superSetOperativMarker(dvbigcomponent, adrReg);
/*
   __LN_INPUT *arr = (__LN_INPUT*)(spca_of_p_prt[ID_FB_INPUT - _ID_FB_FIRST_VAR]);
  int offset = adrReg-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//индекс субобъекта
  switch(offset%REGISTER_FOR_OBJ) {//индекс регистра 
   case 0:
     return (((arr[idxSubObj].settings.control & (1 << INDEX_CTRL_INPUT_TYPE_SIGNAL)) !=0) << 0) | (1 << 1) | ((V110_V220 != 0) << 2);
   case 1:
     return arr[idxSubObj].settings.set_delay[INPUT_SET_DELAY_DOPUSK];
 }//switch
*/

  int offset = adrReg-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//индекс субобъекта
  __settings_for_INPUT *arr =  ((config_settings_modified & MASKA_FOR_BIT(BIT_USB_LOCKS)) == 0 ) ? &(((__LN_INPUT*)(spca_of_p_prt[ID_FB_INPUT - _ID_FB_FIRST_VAR])) + idxSubObj)->settings : (((__settings_for_INPUT*)(sca_of_p[ID_FB_INPUT - _ID_FB_FIRST_VAR])) + idxSubObj);
  if(pointInterface)//метка интерфейса 0-USB 1-RS485
                        arr =  ((config_settings_modified & MASKA_FOR_BIT(BIT_RS485_LOCKS)) == 0 ) ? &(((__LN_INPUT*)(spca_of_p_prt[ID_FB_INPUT - _ID_FB_FIRST_VAR])) + idxSubObj)->settings : (((__settings_for_INPUT*)(sca_of_p[ID_FB_INPUT - _ID_FB_FIRST_VAR])) + idxSubObj);
  switch(offset%REGISTER_FOR_OBJ) {//индекс регистра 
   case 0:
//     return (((arr[idxSubObj].settings.control & (1 << INDEX_CTRL_INPUT_TYPE_SIGNAL)) !=0) << 0) | (1 << 1) | ((V110_V220 != 0) << 2);
     return (((arr->control & (1 << INDEX_CTRL_INPUT_TYPE_SIGNAL)) !=0) << 0) | (1 << 1) | ((V110_V220 != 0) << 2);
   case 1:
//     return arr[idxSubObj].settings.set_delay[INPUT_SET_DELAY_DOPUSK];
     return arr->set_delay[INPUT_SET_DELAY_DOPUSK];
 }//switch

  return 0;
}//getDOUTBigModbusRegister(int adrReg)
int getDVBigModbusBit(int x)
{
  //получить содержимое регистра
  UNUSED(x);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setDVBigModbusRegister(int adrReg, int dataReg)
{
  //записать содержимое регистра
  if(privateDVBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(dvbigcomponent->isActiveActualData) setDVBigCountObject(); //к-во обектов
  dvbigcomponent->isActiveActualData = 0;
  if(privateDVBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;//MARKER_ERRORPERIMETR;

  superSetOperativMarker(dvbigcomponent, adrReg);
  superSetTempWriteArray(dataReg);//записать в буфер

  switch((adrReg-BEGIN_ADR_REGISTER)%REGISTER_FOR_OBJ) {
   case 0:
   break; 
   case 1:
    if(dataReg>60) return MARKER_ERRORDIAPAZON;
   break; 
  default: return MARKER_OUTPERIMETR;
  }//switch
  return 0;
}//getDOUTBigModbusRegister(int adrReg)
int setDVBigModbusBit(int x, int y)
{
  UNUSED(x);
  UNUSED(y);
  //получить содержимое регистра
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void setDVBigCountObject(void) {
//записать к-во обектов
  int cntObj = current_config.n_input; //Кількість дискретних входів
  if(cntObj<0) return;
  if(cntObj>TOTAL_OBJ) return;
  dvbigcomponent->countObject = cntObj;
}//
void preDVBigReadAction(void) {
//action до чтения
  dvbigcomponent->operativMarker[0] = -1;
  dvbigcomponent->operativMarker[1] = -1;//оперативный маркер
  dvbigcomponent->isActiveActualData = 1;
}//
void postDVBigReadAction(void) {
//action после чтения
  if(dvbigcomponent->operativMarker[0]<0) return;//не было чтения
}//
void preDVBigWriteAction(void) {
//action до записи
  dvbigcomponent->operativMarker[0] = -1;
  dvbigcomponent->operativMarker[1] = -1;//оперативный маркер
  dvbigcomponent->isActiveActualData = 1;
}//
int postDVBigWriteAction(void) {
//action после записи
  if(dvbigcomponent->operativMarker[0]<0) return 0;//не было записи
  int offsetTempWriteArray = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//найти смещение TempWriteArray
  int countRegister = dvbigcomponent->operativMarker[1]-dvbigcomponent->operativMarker[0]+1;
  if(dvbigcomponent->operativMarker[1]<0) countRegister = 1;

   __settings_for_INPUT *arr  = (__settings_for_INPUT*)(sca_of_p[ID_FB_INPUT - _ID_FB_FIRST_VAR]);
   __settings_for_INPUT *arr1 = (__settings_for_INPUT*)(sca_of_p_edit[ID_FB_INPUT - _ID_FB_FIRST_VAR]);
  for(int i=0; i<countRegister; i++) {
  int offset = i+dvbigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//индекс субобъекта
  switch(offset%REGISTER_FOR_OBJ) {//индекс регистра 
   case 0://control
        arr1[idxSubObj].control = arr[idxSubObj].control = (tempWriteArray[offsetTempWriteArray+i]);
   break;
   case 1://
        arr1[idxSubObj].set_delay[INPUT_SET_DELAY_DOPUSK] = arr[idxSubObj].set_delay[INPUT_SET_DELAY_DOPUSK] = (tempWriteArray[offsetTempWriteArray+i]);
   break;
 }//switch
  }//for
  config_settings_modified |= MASKA_FOR_BIT(BIT_CHANGED_SETTINGS);
  restart_timeout_idle_new_settings = true;
 return 0;
}//

int privateDVBigGetReg1(int adrReg)
{
  //проверить внутренний периметр
  int count_register = dvbigcomponent->countObject*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg1(int adrReg)
int privateDVBigGetReg2(int adrReg)
{
  //проверить внешний периметр
  int count_register = TOTAL_OBJ*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
