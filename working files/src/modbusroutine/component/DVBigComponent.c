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

void setDVBigCountObject(int);//записать к-во обектов
void preDVBigReadAction(void);//action до чтения
void postDVBigReadAction(void);//action после чтения
void preDVBigWriteAction(void);//action до записи
void postDVBigWriteAction(void);//action после записи
void loadDVBigActualData(void);

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

  dvbigcomponent->setCountObject  = setDVBigCountObject;//записать к-во обектов
  dvbigcomponent->preReadAction   = preDVBigReadAction;//action до чтения
  dvbigcomponent->postReadAction  = postDVBigReadAction;//action после чтения
  dvbigcomponent->preWriteAction  = preDVBigWriteAction;//action до записи
  dvbigcomponent->postWriteAction = postDVBigWriteAction;//action после записи

  dvbigcomponent->isActiveActualData = 0;
}//prepareDVinConfig

void loadDVBigActualData(void) {
  //ActualData
  for(int i=0; i<100; i++) tempReadArray[i] = i;
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
  
  
}//loadActualData() 

int getDVBigModbusRegister(int adrReg)
{
  //получить содержимое регистра
  if(privateDVBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(privateDVBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  if(dvbigcomponent->isActiveActualData) loadDVBigActualData(); //ActualData
  dvbigcomponent->isActiveActualData = 0;

  superSetOperativMarker(dvbigcomponent, adrReg);

  return tempReadArray[adrReg-BEGIN_ADR_REGISTER];
}//getDOUTBigModbusRegister(int adrReg)
int getDVBigModbusBit(int adrReg)
{
  //получить содержимое регистра
  superSetOperativMarker(dvbigcomponent, adrReg);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setDVBigModbusRegister(int adrReg, int dataReg)
{
  //записать содержимое регистра
  if(privateDVBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(privateDVBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  superSetOperativMarker(dvbigcomponent, adrReg);
  superSetTempWriteArray(dataReg);//записать в буфер

  switch((adrReg-BEGIN_ADR_REGISTER)%REGISTER_FOR_OBJ) {
   case 0:
   return dataReg;
   case 1:
    if(dataReg>60) return MARKER_ERRORDIAPAZON;
    return dataReg;
  }//switch
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setDVBigModbusBit(int adrBit, int x)
{
  UNUSED(x);
  //получить содержимое регистра
  superSetOperativMarker(dvbigcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void setDVBigCountObject(int cntObj) {
//записать к-во обектов
  if(cntObj<0) return;
  if(cntObj>=TOTAL_OBJ) return;
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
void postDVBigWriteAction(void) {
//action после записи
  if(dvbigcomponent->operativMarker[0]<0) return;//не было записи
  int offset = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//найти смещение TempWriteArray
  int countRegister = dvbigcomponent->operativMarker[1]-dvbigcomponent->operativMarker[0]+1;
  if(dvbigcomponent->operativMarker[1]<0) countRegister = 1;


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
