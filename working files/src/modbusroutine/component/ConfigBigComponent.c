#include "header.h"

//начальный регистр в карте памяти
#define BEGIN_ADR_REGISTER 800
#define REGISTER_FOR_OBJ 16

int getConfigBigModbusRegister(int);//получить содержимое регистра
int getConfigBigModbusBit(int);//получить содержимое бита
int setConfigBigModbusRegister(int, int);// регистра
int setConfigBigModbusBit(int, int);// бита
int privateConfigBigGetReg2(int adrReg);

void preConfigBigReadAction(void);//action до чтения
void postConfigBigReadAction(void);//action после чтения
void preConfigBigWriteAction(void);//action до записи
int postConfigBigWriteAction(void);//action после записи
void config_and_settingsConfigBig(void);//action активации

COMPONENT_OBJ *configbigcomponent;

/**************************************/
//подготовка компонента ДВ
/**************************************/
void constructorConfigBigComponent(COMPONENT_OBJ *configbigcomp)
{
  configbigcomponent = configbigcomp;

  configbigcomponent->countObject = 1;//к-во обектов

  configbigcomponent->getModbusRegister = getConfigBigModbusRegister;//получить содержимое регистра
  configbigcomponent->getModbusBit      = getConfigBigModbusBit;//получить содержимое бита
  configbigcomponent->setModbusRegister = setConfigBigModbusRegister;//егистра
  configbigcomponent->setModbusBit      = setConfigBigModbusBit;// бита

  configbigcomponent->preReadAction   = preConfigBigReadAction;//action до чтения
  configbigcomponent->postReadAction  = postConfigBigReadAction;//action после чтения
  configbigcomponent->preWriteAction  = preConfigBigWriteAction;//action до записи
  configbigcomponent->postWriteAction = postConfigBigWriteAction;//action после записи
  configbigcomponent->config_and_settings = config_and_settingsConfigBig;//action активации

  configbigcomponent->isActiveActualData = 0;
}//constructorConfigBigComponent(COMPONENT_OBJ *configbigcomp)

int getConfigBigModbusRegister(int adrReg)
{
  //получить содержимое регистра
  if(privateConfigBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  superSetOperativMarker(configbigcomponent, adrReg);

  int offset = adrReg-BEGIN_ADR_REGISTER;
  switch(offset%REGISTER_FOR_OBJ) {//индекс регистра 
   case 0: //AND
    return current_config.n_and;
   break;
   case 1: //OR
    return current_config.n_or;
   break;
   case 2: //XOR
    return current_config.n_xor;
   break;
   case 3: //NOT
    return current_config.n_not;
   break;
   case 4: //D-trg
    return current_config.n_trigger;
   break;
   case 5: //GI
    return current_config.n_meander;
   break;
   case 6: //MFT
    return current_config.n_timer;
   break;
   case 7: //SZS
    return current_config.n_alarm;
   break;
   case 8: //ШГС
    return current_config.n_group_alarm;
   break;
   case 9: //TS
    return current_config.n_ts;
   break;
   case 10: //TU
    return current_config.n_tu;
   break;
   case 11: //субмодули журнала
    return current_config.n_log;
   break;
   case 12: //GOOSE in
    return 0;
   break;
   case 13: //GOOSE out
    return 0;
   break;
   case 14: //MMS in
    return 0;
   break;
   case 15: //MMS out
    return 0;
  }//switch

  return 0;
}//getDVModbusRegister(int adrReg)
int getConfigBigModbusBit(int x)
{
  //получить содержимое регистра
  UNUSED(x);
  return MARKER_OUTPERIMETR;
}//getDVModbusRegister(int adrReg)
int setConfigBigModbusRegister(int adrReg, int dataReg)
{
  //записать содержимое регистра
  if(privateConfigBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  superSetOperativMarker(configbigcomponent, adrReg);
  superSetTempWriteArray(dataReg);//записать в буфер
  if(dataReg>128) return MARKER_ERRORDIAPAZON;
  return 0;
}//getDVModbusRegister(int adrReg)
int setConfigBigModbusBit(int x, int y)
{
  UNUSED(x);
  UNUSED(y);
  //записать содержимое bit
  return MARKER_OUTPERIMETR;
}//getDVModbusRegister(int adrReg)

void preConfigBigReadAction(void) {
//action до чтения
  configbigcomponent->operativMarker[0] = -1;
  configbigcomponent->operativMarker[1] = -1;//оперативный маркер
  configbigcomponent->isActiveActualData = 1;
}//
void postConfigBigReadAction(void) {
//action после чтения
  if(configbigcomponent->operativMarker[0]<0) return;//не было чтения
}//
void preConfigBigWriteAction(void) {
//action до записи
  configbigcomponent->operativMarker[0] = -1;
  configbigcomponent->operativMarker[1] = -1;//оперативный маркер
  configbigcomponent->isActiveActualData = 1;
}//
int postConfigBigWriteAction(void) {
extern int pointInterface;//метка интерфейса 0-USB 1-RS485
//action после записи
  if(configbigcomponent->operativMarker[0]<0) return 0;//не было записи
  int offsetTempWriteArray = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//найти смещение TempWriteArray
  int countRegister = configbigcomponent->operativMarker[1]-configbigcomponent->operativMarker[0]+1;
  if(configbigcomponent->operativMarker[1]<0) countRegister = 1;

  for(int i=0; i<countRegister; i++) {
  int offset = i+configbigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;
  switch(offset) {//индекс регистра 
   case 0://AND
    current_config_edit.n_and = (tempWriteArray[offsetTempWriteArray+i]);
   break; 
   case 1://OR
    current_config_edit.n_or = (tempWriteArray[offsetTempWriteArray+i]);
   break; 
   case 2://XOR
    current_config_edit.n_xor = (tempWriteArray[offsetTempWriteArray+i]);
   break; 
   case 3://NOT
    current_config_edit.n_not = (tempWriteArray[offsetTempWriteArray+i]);
   break; 
   case 4://D-trg
    current_config_edit.n_trigger = (tempWriteArray[offsetTempWriteArray+i]);
   break; 
   case 5://GI
    current_config_edit.n_meander = (tempWriteArray[offsetTempWriteArray+i]);
   break; 
   case 6://MFT
    current_config_edit.n_timer = (tempWriteArray[offsetTempWriteArray+i]);
   break; 
   case 7://SZS
    current_config_edit.n_alarm = (tempWriteArray[offsetTempWriteArray+i]);
   break; 
   case 8://ШГС
    current_config_edit.n_group_alarm = (tempWriteArray[offsetTempWriteArray+i]);
   break; 
   case 9://TS
    current_config_edit.n_ts = (tempWriteArray[offsetTempWriteArray+i]);
   break; 
   case 10://TU
    current_config_edit.n_tu = (tempWriteArray[offsetTempWriteArray+i]);
   break; 
   case 11://субмодули журнала
    current_config_edit.n_log = (tempWriteArray[offsetTempWriteArray+i]);
   break; 
   case 12: //GOOSE in
   case 13: //GOOSE out
   case 14: //MMS in
   case 15: //MMS out
   break;
 }//switch
  }//for

 __result_dym_mem_select result_1 = action_after_changing_of_configuration(); //перевірити обов'язково результат
 if (result_1 == DYN_MEM_SELECT_OK) config_settings_modified |= (MASKA_FOR_BIT(BIT_CHANGED_CONFIGURATION) | MASKA_FOR_BIT(BIT_CHANGED_SETTINGS) | MASKA_FOR_BIT(BIT_CHANGED_SCHEMATIC));
 else
 {
   //Відбулася помилка з виділенням динамічної пам'яті
   if (result_1 == DYN_MEM_NO_ENOUGH_MEM)
   {
     /*
     Повідомити треба верхній рівень про те, що під час процесу виділення динамічної пам'яті ВДАЛОСЯ повернути систему до попереднього стану
     Тому прилад може продовжувати функціонувати, хоч цю зміну віі відкинув
     */
//    return SUPER_ERROR1;
                return 2;//уйти
   }
   else
   {
     if (set_diagnostyka != NULL) _SET_BIT(set_diagnostyka, ERROR_NO_FREE_DYNAMIC_MEMORY_BIT);
     /*
     Повідомити треба верхній рівень про те, що під час процесу виділення динамічної пам'яті навіть НЕ ВДАЛОСЯ зробити відкат до попереднього стану
     
     ПРИЛАД ТРЕБА ПІСЛЯ ВІДПОВІДІ ЗАБЛОКУВАТИ І ПЕРЕЗАПУСТИТИ!!!
     */
//    return SUPER_ERROR1;
                return 2;//уйти
   }
 }
  if(pointInterface)//метка интерфейса 0-USB 1-RS485
     config_settings_modified |= MASKA_FOR_BIT(BIT_RS485_LOCKS);
  else 
     config_settings_modified |= MASKA_FOR_BIT(BIT_USB_LOCKS);
 return 0;
}//

int privateConfigBigGetReg2(int adrReg)
{
  //проверить внешний периметр
  int count_register = REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)

void config_and_settingsConfigBig(void)
{
//action активации
}

