#include "header.h"

//начальный регистр в карте памяти
#define BEGIN_ADR_REGISTER 308
//начальный bit в карте памяти
#define BEGIN_ADR_BIT 19128
//макс к-во обектов
#define REGISTER_FOR_OBJ 1
#define BIT_FOR_OBJ 3

int privateKEYSmallGetReg2(int adrReg);
int privateKEYSmallGetBit2(int adrReg);

int getKEYSmallModbusRegister(int);//получить содержимое регистра
int getKEYSmallModbusBit(int);//получить содержимое бита
int setKEYSmallModbusRegister(int, int);//получить содержимое регистра
int setKEYSmallModbusBit(int, int);//получить содержимое бита

void setKEYSmallCountObject(int);//записать к-во обектов
void preKEYSmallReadAction(void);//action до чтения
void postKEYSmallReadAction(void);//action после чтения
void preKEYSmallWriteAction(void);//action до записи
void postKEYSmallWriteAction(void);//action после записи
void loadKEYSmallActualData(void);

COMPONENT_OBJ *keysmallcomponent;

/**************************************/
//подготовка компонента ранжирование пользовательских регистров
/**************************************/
void constructorKEYSmallComponent(COMPONENT_OBJ *keysmallcomp)
{
  keysmallcomponent = keysmallcomp;

  keysmallcomponent->countObject = 1;//к-во обектов

  keysmallcomponent->getModbusRegister = getKEYSmallModbusRegister;//получить содержимое регистра
  keysmallcomponent->getModbusBit      = getKEYSmallModbusBit;//получить содержимое бита
  keysmallcomponent->setModbusRegister = setKEYSmallModbusRegister;//получить содержимое регистра
  keysmallcomponent->setModbusBit      = setKEYSmallModbusBit;//получить содержимое бита

  keysmallcomponent->setCountObject  = setKEYSmallCountObject;//записать к-во обектов
  keysmallcomponent->preReadAction   = preKEYSmallReadAction;//action до чтения
  keysmallcomponent->postReadAction  = postKEYSmallReadAction;//action после чтения
  keysmallcomponent->preWriteAction  = preKEYSmallWriteAction;//action до записи
  keysmallcomponent->postWriteAction = postKEYSmallWriteAction;//action после записи

  keysmallcomponent->isActiveActualData = 0;
}//prepareDVinConfig

void loadKEYSmallActualData(void) {
  //ActualData
  for(int i=0; i<100; i++) tempReadArray[i] = i;
  /*
  Підхід аналогічний до ТС
  +
  Індекси кнопок визначені enum _fix_button:
  - спрчатку ідуть кнопки з фіксованою функціональностю
  - NUMBER_FIX_BUTTONS - це індекс першої вільнопрограмованої кнопки
  - NUMBER_GENERAL_BUTTONS - це кількість вільнопрограмованих кнопок
  
  */
}//loadActualData() 

int getKEYSmallModbusRegister(int adrReg)
{
  //получить содержимое регистра
  if(privateKEYSmallGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  if(keysmallcomponent->isActiveActualData) loadKEYSmallActualData(); //ActualData
  keysmallcomponent->isActiveActualData = 0;

  superSetOperativMarker(keysmallcomponent, adrReg);

  return tempReadArray[adrReg-BEGIN_ADR_REGISTER];
}//getDOUTModbusRegister(int adrReg)
int getKEYSmallModbusBit(int adrBit)
{
  //получить содержимое bit
  if(privateKEYSmallGetBit2(adrBit)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  if(keysmallcomponent->isActiveActualData) loadKEYSmallActualData();
  keysmallcomponent->isActiveActualData = 0;

  superSetOperativMarker(keysmallcomponent, adrBit);

  short tmp   = tempReadArray[(adrBit-BEGIN_ADR_BIT)/16];
  short maska = 1<<((adrBit-BEGIN_ADR_BIT)%16);
  if(tmp&maska) return 1;
  return 0;
}//getDOUTBigModbusRegister(int adrReg)
int setKEYSmallModbusRegister(int adrReg, int x)
{
  UNUSED(x);
  //записать содержимое регистра
  superSetOperativMarker(keysmallcomponent, adrReg);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setKEYSmallModbusBit(int adrBit, int x)
{
  UNUSED(x);
  //получить содержимое регистра
  superSetOperativMarker(keysmallcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void setKEYSmallCountObject(int x) {
  UNUSED(x);
//записать к-во обектов
}//
void preKEYSmallReadAction(void) {
//action до чтения
  keysmallcomponent->operativMarker[0] = -1;
  keysmallcomponent->operativMarker[1] = -1;//оперативный маркер
  keysmallcomponent->isActiveActualData = 1;
}//
void postKEYSmallReadAction(void) {
//action после чтения
  if(keysmallcomponent->operativMarker[0]<0) return;//не было чтения
}//
void preKEYSmallWriteAction(void) {
//action до записи
  keysmallcomponent->operativMarker[0] = -1;
  keysmallcomponent->operativMarker[1] = -1;//оперативный маркер
  keysmallcomponent->isActiveActualData = 1;
}//
void postKEYSmallWriteAction(void) {
//action после записи
}//

int privateKEYSmallGetReg2(int adrReg)
{
  //проверить внешний периметр
  int count_register = REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateKEYSmallGetReg2(int adrReg)

int privateKEYSmallGetBit2(int adrBit)
{
  //проверить внешний периметр
  int count_bit = BIT_FOR_OBJ;
  if(adrBit>=BEGIN_ADR_BIT && adrBit<(BEGIN_ADR_BIT+count_bit)) return 0;
  return MARKER_OUTPERIMETR;
}//privateKEYSmallGetReg2(int adrReg)
