#include "header.h"

//начальный регистр в карте памяти
#define BEGIN_ADR_REGISTER 61967
//макс к-во обектов
#define REGISTER_FOR_OBJ 7

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
void config_and_settingsYustBig(void);//action активации

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
  yustbigcomponent->config_and_settings = config_and_settingsYustBig;//action активации

  yustbigcomponent->isActiveActualData = 0;
}//prepareDVinConfig

void loadYustBigActualData(void) {
  //ActualData
  for(int i=1; i<7; i++) tempReadArray[i] = ustuvannja[i-1];
}//loadActualData() 

int getYustBigModbusRegister(int adrReg)
{
  //получить содержимое регистра
  if(privateYustBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  if(yustbigcomponent->isActiveActualData) loadYustBigActualData(); //ActualData
  yustbigcomponent->isActiveActualData = 0;

  superSetOperativMarker(yustbigcomponent, adrReg);

  int offset = adrReg-BEGIN_ADR_REGISTER;
  if(offset==0) return MARKER_ERRORPERIMETR;//Разрешение юстировки

  return tempReadArray[offset];
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
extern int upravlYust;//флаг юстировки
//action после записи
  if(yustbigcomponent->operativMarker[0]<0) return 0;//не было записи
  int offsetTempWriteArray = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//найти смещение TempWriteArray
  int countRegister = yustbigcomponent->operativMarker[1]-yustbigcomponent->operativMarker[0]+1;
  if(yustbigcomponent->operativMarker[1]<0) countRegister = 1;

  int flag2 = 0;
  for(int i=0; i<countRegister; i++) {
  int offset = i+yustbigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;
    switch(offset%(REGISTER_FOR_OBJ)) {//индекс регистра входа
     case 0://Разрешение юстировки
      flag2 = 1;
      upravlYust = tempWriteArray[offsetTempWriteArray+i];//флаг юстировки
     break;
    }//switch
  }//for
 if(flag2==1 && countRegister==1) return 0;//уйти если была запись только Разрешение юстировки

  if(upravlYust!=0x1978) return 2;//флаг юстировки

  int flag = 0;
  for(int i=0; i<countRegister; i++) {
  int offset = i+yustbigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;

  switch(offset%(REGISTER_FOR_OBJ)) {//индекс регистра входа
  case 1:
  case 2:
  case 3:
  case 4:
  case 5:
      flag = 1;
      changed_ustuvannja = CHANGED_ETAP_EXECUTION;
      ustuvannja[(offset%(REGISTER_FOR_OBJ))-1] = tempWriteArray[offsetTempWriteArray+i];
  break;
  case 6:
      if(ustuvannja_measure_shift==-1) ustuvannja_measure_shift =0;
  break;
 }//switch
  }//for

if(flag) {
   changed_ustuvannja = CHANGED_ETAP_ENDED;
   _SET_BIT(control_i2c_taskes, TASK_START_WRITE_USTUVANNJA_EEPROM_BIT);
}//if
 return 0;
}//

int privateYustBigGetReg2(int adrReg)
{
  //проверить внешний периметр
  int count_register = REGISTER_FOR_OBJ+1;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)

void config_and_settingsYustBig(void)
{
//action активации
}

