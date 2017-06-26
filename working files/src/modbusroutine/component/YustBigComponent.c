#include "header.h"

//начальный регистр в карте памяти
#define BEGIN_ADR_REGISTER 61968
//макс к-во обектов
#define REGISTER_FOR_OBJ 33

int privateYustBigGetReg2(int adrReg);

int getYustBigModbusRegister(int);//получить содержимое регистра
int getYustBigModbusBit(int);//получить содержимое бита
int setYustBigModbusRegister(int, int);//получить содержимое регистра
int setYustBigModbusBit(int, int);//получить содержимое бита

void preYustBigReadAction(void);//action до чтения
void postYustBigReadAction(void);//action после чтения
void preYustBigWriteAction(void);//action до записи
void postYustBigWriteAction(void);//action после записи
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
  for(int i=0; i<REGISTER_FOR_OBJ; i++) tempReadArray[i] = ustuvannja[i];
  /*
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
int getYustBigModbusBit(int adrBit)
{
  //получить содержимое регистра
  superSetOperativMarker(yustbigcomponent, adrBit);
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
int setYustBigModbusBit(int adrBit, int x)
{
  UNUSED(x);
  //записать содержимое bit
  superSetOperativMarker(yustbigcomponent, adrBit);
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
void postYustBigWriteAction(void) {
//action после записи
  if(yustbigcomponent->operativMarker[0]<0) return;//не было записи
//  int offset = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//найти смещение TempWriteArray
//  int countRegister = yustbigcomponent->operativMarker[1]-yustbigcomponent->operativMarker[0]+1;
//  if(yustbigcomponent->operativMarker[1]<0) countRegister = 1;
}//

int privateYustBigGetReg2(int adrReg)
{
  //проверить внешний периметр
  int count_register = REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
