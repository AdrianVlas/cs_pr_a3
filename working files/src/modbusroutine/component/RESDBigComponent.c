#include "header.h"

//начальный регистр в карте памяти
#define BEGIN_ADR_REGISTER 4664
#define REGISTER_FOR_OBJ 6

int getRESDBigModbusRegister(int);//получить содержимое регистра
int getRESDBigModbusBit(int);//получить содержимое бита
int setRESDBigModbusRegister(int, int);//получить содержимое регистра
int setRESDBigModbusBit(int, int);//получить содержимое бита

void setRESDBigCountObject(void);//записать к-во обектов
void preRESDBigReadAction(void);//action до чтения
void postRESDBigReadAction(void);//action после чтения
void preRESDBigWriteAction(void);//action до записи
int postRESDBigWriteAction(void);//action после записи
void loadRESDBigActualData(void);

int privateRESDBigGetReg2(int adrReg);

COMPONENT_OBJ *resdbigcomponent;

/**************************************/
//подготовка компонента маркерных светоиндикаторов run\error
/**************************************/
void constructorRESDBigComponent(COMPONENT_OBJ *resdbigcomp)
{
  resdbigcomponent = resdbigcomp;

  resdbigcomponent->countObject = 1;//к-во обектов

  resdbigcomponent->getModbusRegister = getRESDBigModbusRegister;//получить содержимое регистра
  resdbigcomponent->getModbusBit      = getRESDBigModbusBit;//получить содержимое бита
  resdbigcomponent->setModbusRegister = setRESDBigModbusRegister;//получить содержимое регистра
  resdbigcomponent->setModbusBit      = setRESDBigModbusBit;//получить содержимое бита

  resdbigcomponent->preReadAction   = preRESDBigReadAction;//action до чтения
  resdbigcomponent->postReadAction  = postRESDBigReadAction;//action после чтения
  resdbigcomponent->preWriteAction  = preRESDBigWriteAction;//action до записи
  resdbigcomponent->postWriteAction = postRESDBigWriteAction;//action после записи

  resdbigcomponent->isActiveActualData = 0;
}//prepareDVinConfig

void loadRESDBigActualData(void) {
  //ActualData
  for(int i=0; i<100; i++) tempReadArray[i] = i;
  /*
  Читання/запис здійснється у 
  settings_fix_prt/settings_fix/settings_fix_edit.param[вхід]
  
  відповідність номерів входів визначено у enum _FIX_BLOCK_input_signals
  */
}//loadActualData() 

int getRESDBigModbusRegister(int adrReg)
{
  //получить содержимое регистра
  if(privateRESDBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  if(resdbigcomponent->isActiveActualData) loadRESDBigActualData(); //ActualData
  resdbigcomponent->isActiveActualData = 0;

  superSetOperativMarker(resdbigcomponent, adrReg);

  return tempReadArray[adrReg-BEGIN_ADR_REGISTER];
}//getDVModbusRegister(int adrReg)
int getRESDBigModbusBit(int adrBit)
{
  //получить содержимое регистра
  superSetOperativMarker(resdbigcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDVModbusRegister(int adrReg)
int setRESDBigModbusRegister(int adrReg, int dataReg)
{
  //записать содержимое регистра
  if(privateRESDBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  superSetOperativMarker(resdbigcomponent, adrReg);
  superSetTempWriteArray(dataReg);//записать в буфер

  switch((adrReg-BEGIN_ADR_REGISTER)%REGISTER_FOR_OBJ) {
   case 0:
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
   break; 
   case 1:
   break; 
   case 2:
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
   break; 
   case 3:
   break; 
   case 4:
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
   break; 
   case 5:
   break; 
  default: return MARKER_OUTPERIMETR;
  }//switch
  return 0;
}//getDVModbusRegister(int adrReg)
int setRESDBigModbusBit(int adrBit, int x)
{
  UNUSED(x);
  //получить содержимое регистра
  superSetOperativMarker(resdbigcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDVModbusRegister(int adrReg)

void setRESDBigCountObject(void) {
//записать к-во обектов
}//
void preRESDBigReadAction(void) {
//action до чтения
  resdbigcomponent->operativMarker[0] = -1;
  resdbigcomponent->operativMarker[1] = -1;//оперативный маркер
  resdbigcomponent->isActiveActualData = 1;
}//
void postRESDBigReadAction(void) {
//action после чтения
  if(resdbigcomponent->operativMarker[0]<0) return;//не было чтения
}//
void preRESDBigWriteAction(void) {
//action до записи
  resdbigcomponent->operativMarker[0] = -1;
  resdbigcomponent->operativMarker[1] = -1;//оперативный маркер
  resdbigcomponent->isActiveActualData = 1;
}//
int postRESDBigWriteAction(void) {
//action после записи
  if(resdbigcomponent->operativMarker[0]<0) return 0;//не было записи
//  int offset = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//найти смещение TempWriteArray
//  int countRegister = resdbigcomponent->operativMarker[1]-resdbigcomponent->operativMarker[0]+1;
//  if(resdbigcomponent->operativMarker[1]<0) countRegister = 1;

  config_settings_modified |= MASKA_FOR_BIT(BIT_CHANGED_SETTINGS);
  restart_timeout_idle_new_settings = true;
 return 0;
}//

int privateRESDBigGetReg2(int adrReg)
{
  //проверить внешний периметр
  int count_register = REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
