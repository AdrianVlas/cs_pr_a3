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
//void loadConfigBigActualData(void);

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

  configbigcomponent->isActiveActualData = 0;
}//constructorConfigBigComponent(COMPONENT_OBJ *configbigcomp)
/*
void loadConfigBigActualData(void) {
  //ActualData
//  if (
//      (config_settings_modified &
//     )
  for(int i=0; i<REGISTER_FOR_OBJ; i++) {
   switch(i) {
   case 0: //AND
    tempReadArray[i] = current_config.n_and;
   break;
   case 1: //OR
    tempReadArray[i] = current_config.n_or;
   break;
   case 2: //XOR
    tempReadArray[i] = current_config.n_xor;
   break;
   case 3: //NOT
    tempReadArray[i] = current_config.n_not;
   break;
   case 4: //D-trg
    tempReadArray[i] = current_config.n_trigger;
   break;
   case 5: //GI
    tempReadArray[i] = current_config.n_meander;
   break;
   case 6: //MFT
    tempReadArray[i] = current_config.n_timer;
   break;
   case 7: //SZS
    tempReadArray[i] = current_config.n_alarm;
   break;
   case 8: //ШГС
    tempReadArray[i] = current_config.n_group_alarm;
   break;
   case 9: //TS
    tempReadArray[i] = current_config.n_ts;
   break;
   case 10: //TU
    tempReadArray[i] = current_config.n_tu;
   break;
   case 11: //субмодули журнала
    tempReadArray[i] = current_config.n_log;
   break;
   case 12: //GOOSE in
    tempReadArray[i] = 0;
   break;
   case 13: //GOOSE out
    tempReadArray[i] = 0;
   break;
   case 14: //MMS in
    tempReadArray[i] = 0;
   break;
   case 15: //MMS out
    tempReadArray[i] = 0;
   break;
   }//switch
  }//for
*/
  /*
unsigned int config_settings_modified  
  
#define BIT_CHANGED_CONFIGURATION       0 - відбулася зміна конфгурації (інформація, що треба буде акутивовувати)
#define MASKA_CHANGED_CONFIGURATION     (1 << BIT_CHANGED_CONFIGURATION)
#define BIT_CHANGED_SETTINGS            1 - відбулася зміна налаштувань встановлюється або окремо, або разом з конфігурацією (інформація, що треба буде акутивовувати)
#define MASKA_CHANGED_SETTINGS          (1 << BIT_CHANGED_SETTINGS)
#define BIT_MENU_LOCKS                  2 - меню захопило "монополію" на зміну налаштувань (встановлюється або перевіряється)
#define MASKA_MENU_LOCKS                (1 << BIT_MENU_LOCKS)
#define BIT_USB_LOCKS                   3 - USB-інтерфейс захопив "монополію" на зміну налаштувань (встановлюється або перевіряється)
#define MASKA_USB_LOCKS                 (1 << BIT_USB_LOCKS)
#define BIT_RS485_LOCKS                 4 RS485-інтерфейс захопив "монополію" на зміну налаштувань (встановлюється або перевіряється)
#define MASKA_RS485_LOCKS               (1 << BIT_RS485_LOCKS)
  
  
2
  current_config_prt (логіка)
  current_config (контейнер)
  current_config_edit (для редагування)
  
3. Для того, щоб виконати зміну конфігурації треба
3.1 внести зміни у current_config_edit
3.2 якщо зміни допустимі. то виконати фунцію __result_dym_mem_select action_after_changing_of_configuration(void), яка вже сама внесе зміни у  current_config і виділить/аивільнить пам'ять у current_config і current_config_edit
3.3 Можливі результати виконання цієї функції у 
typedef enum _result_dyn_mem_select
{
  DYN_MEM_TOTAL_ERROR = 0, для відновлення роботи треба перезапкус
  PRT_MEM_ERROR, для відновлення роботи треба перезапкус
  DYN_MEM_NO_ENOUGH_MEM, перезапуску не потрібно
  DYN_MEM_SELECT_OK успішне викуонання
    
} __result_dym_mem_select;

3.4 якщо функція не змогла виконатися успішно, то у current_config_edit буде відновлено стан з  current_config  
  
  
  */
//}//loadActualData() 

int getConfigBigModbusRegister(int adrReg)
{
  //получить содержимое регистра
  if(privateConfigBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

//  if(configbigcomponent->isActiveActualData) loadConfigBigActualData(); //ActualData
//  configbigcomponent->isActiveActualData = 0;

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

  return 0;//tempReadArray[adrReg-BEGIN_ADR_REGISTER];
}//getDVModbusRegister(int adrReg)
int getConfigBigModbusBit(int adrBit)
{
  //получить содержимое регистра
  superSetOperativMarker(configbigcomponent, adrBit);
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
int setConfigBigModbusBit(int adrBit, int x)
{
  UNUSED(x);
  //записать содержимое bit
  superSetOperativMarker(configbigcomponent, adrBit);
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
//action после записи
  if(configbigcomponent->operativMarker[0]<0) return 0;//не было записи
  int offsetTempWriteArray = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//найти смещение TempWriteArray
  int countRegister = configbigcomponent->operativMarker[1]-configbigcomponent->operativMarker[0]+1;
  if(configbigcomponent->operativMarker[1]<0) countRegister = 1;

//   __SETTINGS_FIX *arr = &settings_fix;
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

// action_after_changing_of_configuration(); //перевірити обов'язково результат
 __result_dym_mem_select result_1 = action_after_changing_of_configuration(); //перевірити обов'язково результат
 if (result_1 == DYN_MEM_SELECT_OK) config_settings_modified |= (MASKA_FOR_BIT(BIT_CHANGED_CONFIGURATION) | MASKA_FOR_BIT(BIT_CHANGED_SETTINGS) | MASKA_FOR_BIT(BIT_CHANGED_SCHEMATIC));
 return 0;
}//

int privateConfigBigGetReg2(int adrReg)
{
  //проверить внешний периметр
  int count_register = REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
