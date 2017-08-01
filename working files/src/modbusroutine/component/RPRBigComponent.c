
//#include <QtWidgets>
#include "header.h"

//начальный регистр в карте памяти
#define BEGIN_ADR_REGISTER 14000
//макс к-во обектов
#define REGISTER_FOR_OBJ 1

int privateRPRBigGetReg2(int adrReg);

int getRPRBigModbusRegister(int);//получить содержимое регистра
int getRPRBigModbusBit(int);//получить содержимое бита
int setRPRBigModbusRegister(int, int);//получить содержимое регистра
int setRPRBigModbusBit(int, int);//получить содержимое бита

void setRPRBigCountObject(void);//записать к-во обектов
void preRPRBigReadAction(void);//action до чтения
void postRPRBigReadAction(void);//action после чтения
void preRPRBigWriteAction(void);//action до записи
int postRPRBigWriteAction(void);//action после записи
void loadRPRBigActualData(void);
int getRPRSmallModbusBeginAdrRegister(void);

COMPONENT_OBJ *rprbigcomponent;

/**************************************/
//подготовка компонента ранжирование пользовательских регистров
/**************************************/
void constructorRPRBigComponent(COMPONENT_OBJ *rprbigcomp)
{
  rprbigcomponent = rprbigcomp;

  rprbigcomponent->countObject = 125;//к-во обектов

  rprbigcomponent->getModbusRegister = getRPRBigModbusRegister;//получить содержимое регистра
  rprbigcomponent->getModbusBit      = getRPRBigModbusBit;//получить содержимое бита
  rprbigcomponent->setModbusRegister = setRPRBigModbusRegister;//получить содержимое регистра
  rprbigcomponent->setModbusBit      = setRPRBigModbusBit;//получить содержимое бита

  rprbigcomponent->preReadAction   = preRPRBigReadAction;//action до чтения
  rprbigcomponent->postReadAction  = postRPRBigReadAction;//action после чтения
  rprbigcomponent->preWriteAction  = preRPRBigWriteAction;//action до записи
  rprbigcomponent->postWriteAction = postRPRBigWriteAction;//action после записи

  rprbigcomponent->isActiveActualData = 0;
}//prepareDVinConfig

void loadRPRBigActualData(void)
{
  /*
  Читання/запис здійснється з полів (коментарі додані у файлі type_definition.h для структури типу __CONFIG)
  settings_fix_prt/settings_fix/settings_fix_edit->user_register[]
  
  */
  //ActualData
  for(int i=0; i<100; i++) tempReadArray[i] = i;
  /*
  Читання/запис здійснється у 
  settings_fix_prt/settings_fix/settings_fix_edit.user_register[номер регістру]
*/
}//loadActualData()

int getRPRBigModbusRegister(int adrReg)
{
  //получить содержимое регистра
  if(privateRPRBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  if(rprbigcomponent->isActiveActualData) loadRPRBigActualData(); //ActualData
  rprbigcomponent->isActiveActualData = 0;

  superSetOperativMarker(rprbigcomponent, adrReg);

  return tempReadArray[adrReg-BEGIN_ADR_REGISTER];
}//getDOUTBigModbusRegister(int adrReg)
int getRPRBigModbusBit(int adrBit)
{
  //получить содержимое регистра
  superSetOperativMarker(rprbigcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setRPRBigModbusRegister(int adrReg, int dataReg)
{
  //записать содержимое регистра
  if(privateRPRBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  superSetOperativMarker(rprbigcomponent, adrReg);
  superSetTempWriteArray(dataReg);//записать в буфер
//нельзя записывать адреса small компонента
  if(adrReg>=getRPRSmallModbusBeginAdrRegister() &&
      (adrReg<rprbigcomponent->countObject*getRPRSmallModbusBeginAdrRegister())) return MARKER_ERRORDIAPAZON;

  return 0;
}//getDOUTBigModbusRegister(int adrReg)
int setRPRBigModbusBit(int adrBit, int x)
{
  UNUSED(x);
  //получить содержимое регистра
  superSetOperativMarker(rprbigcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void setRPRBigCountObject(void)
{
//записать к-во обектов
}//
void preRPRBigReadAction(void)
{
//action до чтения
  rprbigcomponent->operativMarker[0] = -1;
  rprbigcomponent->operativMarker[1] = -1;//оперативный маркер
  rprbigcomponent->isActiveActualData = 1;
}//
void postRPRBigReadAction(void)
{
//action после чтения
  if(rprbigcomponent->operativMarker[0]<0) return;//не было чтения
}//
void preRPRBigWriteAction(void)
{
//action до записи
  rprbigcomponent->operativMarker[0] = -1;
  rprbigcomponent->operativMarker[1] = -1;//оперативный маркер
  rprbigcomponent->isActiveActualData = 1;
}//
int postRPRBigWriteAction(void)
{
//action после записи
  if(rprbigcomponent->operativMarker[0]<0) return 0;//не было записи
  int offset = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//найти смещение TempWriteArray
  int countRegister = rprbigcomponent->operativMarker[1]-rprbigcomponent->operativMarker[0]+1;
  if(rprbigcomponent->operativMarker[1]<0) countRegister = 1;

  for(int i=0; i<countRegister; i++)
      rprAdresRegister[i+rprbigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER] = tempWriteArray[offset+i];
  /*
        qDebug()<<"offset= "<<offset;

        qDebug()<<"operativMarker[0]= "<<rprbigcomponent->operativMarker[0];
        qDebug()<<"operativMarker[1]= "<<rprbigcomponent->operativMarker[1];

        qDebug()<<"rprAdresRegister[0]= "<<rprAdresRegister[0];
        qDebug()<<"rprAdresRegister[1]= "<<rprAdresRegister[1];
        qDebug()<<"rprAdresRegister[2]= "<<rprAdresRegister[2];
        qDebug()<<"rprAdresRegister[3]= "<<rprAdresRegister[3];
        qDebug()<<"rprAdresRegister[4]= "<<rprAdresRegister[4];
        qDebug()<<"rprAdresRegister[5]= "<<rprAdresRegister[5];
        qDebug()<<"rprAdresRegister[6]= "<<rprAdresRegister[6];
        qDebug()<<"rprAdresRegister[7]= "<<rprAdresRegister[7];
        qDebug()<<"rprAdresRegister[8]= "<<rprAdresRegister[8];
        qDebug()<<"rprAdresRegister[9]= "<<rprAdresRegister[9];
  */
  /*
  Читання/запис здійснється з полів (коментарі додані у файлі type_definition.h для структури типу __CONFIG)
  settings_fix_prt/settings_fix/settings_fix_edit->user_register[]
  
  */
  config_settings_modified |= MASKA_FOR_BIT(BIT_CHANGED_SETTINGS);
  restart_timeout_idle_new_settings = true;
 return 0;
}//

int privateRPRBigGetReg2(int adrReg)
{
  //проверить внешний периметр
  int count_register = rprbigcomponent->countObject*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
