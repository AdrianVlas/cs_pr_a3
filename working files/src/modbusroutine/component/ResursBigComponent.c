#include "header.h"

//начальный регистр в карте памяти
#define BEGIN_ADR_REGISTER 63002
//макс к-во обектов
#define REGISTER_FOR_OBJ 7

int privateResursBigGetReg2(int adrReg);

int getResursBigModbusRegister(int);//получить содержимое регистра
int getResursBigModbusBit(int);//получить содержимое бита
int setResursBigModbusRegister(int, int);//получить содержимое регистра
int setResursBigModbusBit(int, int);//получить содержимое бита

void preResursBigReadAction(void);//action до чтения
void postResursBigReadAction(void);//action после чтения
void preResursBigWriteAction(void);//action до записи
int postResursBigWriteAction(void);//action после записи
void loadResursBigActualData(void);
void config_and_settingsResursBig(void);//action активации

COMPONENT_OBJ *resursbigcomponent;

/**************************************/
//подготовка компонента Юстировки
/**************************************/
void constructorResursBigComponent(COMPONENT_OBJ *resursbigcomp)
{
  resursbigcomponent = resursbigcomp;

  resursbigcomponent->countObject = 1;//к-во обектов

  resursbigcomponent->getModbusRegister = getResursBigModbusRegister;//получить содержимое регистра
  resursbigcomponent->getModbusBit      = getResursBigModbusBit;//получить содержимое бита
  resursbigcomponent->setModbusRegister = setResursBigModbusRegister;//получить содержимое регистра
  resursbigcomponent->setModbusBit      = setResursBigModbusBit;//получить содержимое бита

  resursbigcomponent->preReadAction   = preResursBigReadAction;//action до чтения
  resursbigcomponent->postReadAction  = postResursBigReadAction;//action после чтения
  resursbigcomponent->preWriteAction  = preResursBigWriteAction;//action до записи
  resursbigcomponent->postWriteAction = postResursBigWriteAction;//action после записи
  resursbigcomponent->config_and_settings = config_and_settingsResursBig;//action активации

  resursbigcomponent->isActiveActualData = 0;
}//prepareDVinConfig

void loadResursBigActualData(void) {
  //ActualData
  tempReadArray[0] = restart_resurs_count&0xffff;
  tempReadArray[1] = resurs_global&0xffff;
  tempReadArray[2] = (resurs_global>>16)&0xffff;
  tempReadArray[3] = resurs_global_min&0xffff;
  tempReadArray[4] = (resurs_global_min>>16)&0xffff;
  tempReadArray[5] = resurs_global_max&0xffff;
  tempReadArray[6] = (resurs_global_max>>16)&0xffff;
}//loadActualData() 

int getResursBigModbusRegister(int adrReg)
{
  //получить содержимое регистра
  if(privateResursBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  if(resursbigcomponent->isActiveActualData) loadResursBigActualData(); //ActualData
  resursbigcomponent->isActiveActualData = 0;

  superSetOperativMarker(resursbigcomponent, adrReg);

  int offset = adrReg-BEGIN_ADR_REGISTER;
  if(offset==0) return MARKER_ERRORPERIMETR;//reset resurs

  return tempReadArray[offset];
}//getDOUTBigModbusRegister(int adrReg)
int getResursBigModbusBit(int x)
{
  //получить содержимое регистра
  UNUSED(x);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setResursBigModbusRegister(int adrReg, int dataReg)
{
  //записать содержимое регистра
  if(privateResursBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  superSetOperativMarker(resursbigcomponent, adrReg);
  superSetTempWriteArray(dataReg);//записать в буфер

  int offset = adrReg-BEGIN_ADR_REGISTER;
  if(offset>0) return MARKER_ERRORDIAPAZON;//Только чтение, кроме смещения 0

  return 0;
}//getDOUTBigModbusRegister(int adrReg)
int setResursBigModbusBit(int x, int y)
{
  UNUSED(x);
  UNUSED(y);
  //записать содержимое bit
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void preResursBigReadAction(void) {
//action до чтения
  resursbigcomponent->operativMarker[0] = -1;
  resursbigcomponent->operativMarker[1] = -1;//оперативный маркер
  resursbigcomponent->isActiveActualData = 1;
}//
void postResursBigReadAction(void) {
//action после чтения
  if(resursbigcomponent->operativMarker[0]<0) return;//не было чтения
}//
void preResursBigWriteAction(void) {
//action до записи
  resursbigcomponent->operativMarker[0] = -1;
  resursbigcomponent->operativMarker[1] = -1;//оперативный маркер
  resursbigcomponent->isActiveActualData = 1;
}//

int postResursBigWriteAction(void) {
  int resetResurs = 0;//reset resurs
//action после записи
  if(resursbigcomponent->operativMarker[0]<0) return 0;//не было записи
  int offsetTempWriteArray = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//найти смещение TempWriteArray
  int countRegister = resursbigcomponent->operativMarker[1]-resursbigcomponent->operativMarker[0]+1;

  //int flag = 0;
  for(int i=0; i<countRegister; i++) {
  int offset = i+resursbigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;

  switch(offset%(REGISTER_FOR_OBJ)) {//индекс регистра 
  case 0:
      resetResurs = tempWriteArray[offsetTempWriteArray+i];//reset resurs
      if(resetResurs!=0)
      {
        //сброс значений
        resurs_global = 0;    
        resurs_global_min = 4294967295;    
        resurs_global_max = 0;
      }//if
  break;
 }//switch
  }//for

 return 0;
}//

int privateResursBigGetReg2(int adrReg)
{
  //проверить внешний периметр
  int count_register = REGISTER_FOR_OBJ+1;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)

void config_and_settingsResursBig(void)
{
//action активации
}

