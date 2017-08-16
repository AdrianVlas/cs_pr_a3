#include "header.h"

//начальный регистр в карте памяти
#define BEGIN_ADR_REGISTER 61968
//макс к-во обектов
#define REGISTER_FOR_OBJ NUMBER_ANALOG_CANALES

int privateYustBigGetReg2(int adrReg);

int getYustBigModbusRegister(int);//получить содержимое регистра
int getYustBigModbusBit(int);//получить содержимое бита
int setYustBigModbusRegister(int, int);//получить содержимое регистра
int setYustBigModbusBit(int, int);//получить содержимое бита

void preYustBigReadAction(void);//action до чтения
void postYustBigReadAction(void);//action после чтения
void preYustBigWriteAction(void);//action до записи
int postYustBigWriteAction(void);//action после записи
void loadYustBigActualData(void);

COMPONENT_OBJ *yustbigcomponent;

/**************************************/
//подготовка компонента Юстировки
/**************************************/
void constructorYustBigComponent(COMPONENT_OBJ *yustbigcomp)
{
  yustbigcomponent = yustbigcomp;

  yustbigcomponent->countObject = 1;//к-во обектов

  yustbigcomponent->getModbusRegister = getYustBigModbusRegister;//получить содержимое регистра
  yustbigcomponent->getModbusBit      = getYustBigModbusBit;//получить содержимое бита
  yustbigcomponent->setModbusRegister = setYustBigModbusRegister;//получить содержимое регистра
  yustbigcomponent->setModbusBit      = setYustBigModbusBit;//получить содержимое бита

  yustbigcomponent->preReadAction   = preYustBigReadAction;//action до чтения
  yustbigcomponent->postReadAction  = postYustBigReadAction;//action после чтения
  yustbigcomponent->preWriteAction  = preYustBigWriteAction;//action до записи
  yustbigcomponent->postWriteAction = postYustBigWriteAction;//action после записи

  yustbigcomponent->isActiveActualData = 0;
}//prepareDVinConfig

void loadYustBigActualData(void) {
  //ActualData
  for(int i=0; i<NUMBER_ANALOG_CANALES; i++) tempReadArray[i] = ustuvannja[i];
  /*
  Амплітудне юстування
  
  масиви юстування знаходиться у 
  ustuvannja_meas - працює вимірювальна система (не рухати!)
  ustuvannja - контейнер
  edit_ustuvannja - для редагування
  
  Алгоритм запису
  У changed_ustuvannja записати CHANGED_ETAP_EXECUTION (це блокує перевірку на достовірність ustuvannja_meas і ustuvannja)
  У кіцевому результати зробити зміни у ustuvannja (можна використовувати edit_ustuvannja як масив для редагування з можливістю відновлення з ustuvannja)
  
  Для відміни внесення юстування у changed_ustuvannja записати CHANGED_ETAP_NONE але тоді ustuvannja_meas мусить дорівнювати ustuvannja бо інакше самодіагностика буде сваритися
  Для активації змін у changed_ustuvannja записати CHANGED_ETAP_ENDED. Дальше все зробить вимірювальна система
  
  бажано запис юстування робити по спеціальному секретному паролю
  я для цього використловував password_ustuvannja. Спочатку записував туди 0x1978 і цим дозволяв запис юстування. запис іншого числа  блокував запис юстування.

  else if (address_data == MA_POSSIBILITY_USTUVANNJA)
  {
    Повідомлення про те, чи можна проводити операцю юстування
     0 - операція юстування є забороненою
     1 - операція юстування є дозволеною
    if (password_ustuvannja == 0x1978) temp_value = 1;
    else temp_value = 0;
  }
  else if ((address_data >= MA_ADDRESS_FIRST_USTUVANNJA ) && (address_data <= MA_ADDRESS_LAST_USTUVANNJA))
  {
    temp_value = ustuvannja[address_data - MA_ADDRESS_FIRST_USTUVANNJA ];
  }
  
  Юстування зміщення каналів
  У змфінну ustuvannja_measure_shift записати 0 (перед тим перевірити, що вона рівна -1)
  */
}//loadActualData() 

int getYustBigModbusRegister(int adrReg)
{
  //получить содержимое регистра
  if(privateYustBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  if(yustbigcomponent->isActiveActualData) loadYustBigActualData(); //ActualData
  yustbigcomponent->isActiveActualData = 0;

  superSetOperativMarker(yustbigcomponent, adrReg);

  return tempReadArray[adrReg-BEGIN_ADR_REGISTER];
}//getDOUTBigModbusRegister(int adrReg)
int getYustBigModbusBit(int x)
{
  //получить содержимое регистра
  UNUSED(x);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setYustBigModbusRegister(int adrReg, int dataReg)
{
  //записать содержимое регистра
  if(privateYustBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  superSetOperativMarker(yustbigcomponent, adrReg);
  superSetTempWriteArray(dataReg);//записать в буфер

  return 0;
}//getDOUTBigModbusRegister(int adrReg)
int setYustBigModbusBit(int x, int y)
{
  UNUSED(x);
  UNUSED(y);
  //записать содержимое bit
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void preYustBigReadAction(void) {
//action до чтения
  yustbigcomponent->operativMarker[0] = -1;
  yustbigcomponent->operativMarker[1] = -1;//оперативный маркер
  yustbigcomponent->isActiveActualData = 1;
}//
void postYustBigReadAction(void) {
//action после чтения
  if(yustbigcomponent->operativMarker[0]<0) return;//не было чтения
}//
void preYustBigWriteAction(void) {
//action до записи
  yustbigcomponent->operativMarker[0] = -1;
  yustbigcomponent->operativMarker[1] = -1;//оперативный маркер
  yustbigcomponent->isActiveActualData = 1;
}//
int postYustBigWriteAction(void) {
  /*
  Амплітудне юстування
  
  масиви юстування знаходиться у 
  ustuvannja_meas - працює вимірювальна система (не рухати!)
  ustuvannja - контейнер
  edit_ustuvannja - для редагування
  
  Алгоритм запису
  У changed_ustuvannja записати CHANGED_ETAP_EXECUTION (це блокує перевірку на достовірність ustuvannja_meas і ustuvannja)
  У кіцевому результати зробити зміни у ustuvannja (можна використовувати edit_ustuvannja як масив для редагування з можливістю відновлення з ustuvannja)
  
  Для відміни внесення юстування у changed_ustuvannja записати CHANGED_ETAP_NONE але тоді ustuvannja_meas мусить дорівнювати ustuvannja бо інакше самодіагностика буде сваритися
  
  Для активації змін у changed_ustuvannja записати CHANGED_ETAP_ENDED. Дальше все зробить вимірювальна система
  
  бажано запис юстування робити по спеціальному секретному паролю
  я для цього використловував password_ustuvannja. Спочатку записував туди 0x1978 і цим дозволяв запис юстування. запис іншого числа  блокував запис юстування.

  else if (address_data == MA_POSSIBILITY_USTUVANNJA)
  {
    Повідомлення про те, чи можна проводити операцю юстування
     0 - операція юстування є забороненою
     1 - операція юстування є дозволеною
    if (password_ustuvannja == 0x1978) temp_value = 1;
    else temp_value = 0;
  }
  else if ((address_data >= MA_ADDRESS_FIRST_USTUVANNJA ) && (address_data <= MA_ADDRESS_LAST_USTUVANNJA))
  {
    temp_value = ustuvannja[address_data - MA_ADDRESS_FIRST_USTUVANNJA ];
  }
  
  Юстування зміщення каналів
  У змфінну ustuvannja_measure_shift записати 0 (перед тим перевірити, що вона рівна -1)
  */
//action после записи
  if(yustbigcomponent->operativMarker[0]<0) return 0;//не было записи
  int offsetTempWriteArray = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//найти смещение TempWriteArray
  int countRegister = yustbigcomponent->operativMarker[1]-yustbigcomponent->operativMarker[0]+1;
  if(yustbigcomponent->operativMarker[1]<0) countRegister = 1;

//  for(int i=0; i<countRegister; i++) ustuvannja[i] = tempWriteArray[offsetTempWriteArray+i];
  for(int i=0; i<countRegister; i++) {
  int offset = i+yustbigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;
//  int idxSubObj = offset/REGISTER_FOR_OBJ;//индекс субобъекта
//  int idx_SIGNALS_IN = (offset%REGISTER_FOR_OBJ)/2;//индекс входа субобъекта

  switch(offset%(REGISTER_FOR_OBJ+1)) {//индекс регистра входа
  case 0:
  case 1:
  case 2:
  case 3:
  case 4:
      ustuvannja[offset%(REGISTER_FOR_OBJ+1)] = tempWriteArray[offsetTempWriteArray+i];
  break;
  case 5:
   if(ustuvannja_measure_shift==-1) ustuvannja_measure_shift =0;
  break;
 }//switch
  }//for


  changed_ustuvannja = CHANGED_ETAP_EXECUTION;// (це блокує перевірку на достовірність ustuvannja_meas і ustuvannja)
  config_settings_modified |= MASKA_FOR_BIT(BIT_CHANGED_SETTINGS);
  restart_timeout_idle_new_settings = true;
 return 0;
}//

int privateYustBigGetReg2(int adrReg)
{
  //проверить внешний периметр
  int count_register = REGISTER_FOR_OBJ+1;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
