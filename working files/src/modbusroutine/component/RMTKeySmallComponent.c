#include "header.h"

//начальный регистр в карте памяти
#define BEGIN_ADR_REGISTER 408
//начальный bit в карте памяти
#define BEGIN_ADR_BIT 20128
//макс к-во обектов
#define BIT_FOR_OBJ 1

int privateRMTKeySmallGetReg2(int adrReg);
int privateRMTKeySmallGetBit2(int adrReg);

int getRMTKeySmallModbusRegister(int);//получить содержимое регистра
int getRMTKeySmallModbusBit(int);//получить содержимое бита
int setRMTKeySmallModbusRegister(int, int);//получить содержимое регистра
int setRMTKeySmallModbusBit(int, int);//получить содержимое бита

void setRMTKeySmallCountObject(void);//записать к-во обектов
void preRMTKeySmallReadAction(void);//action до чтения
void postRMTKeySmallReadAction(void);//action после чтения
void preRMTKeySmallWriteAction(void);//action до записи
int postRMTKeySmallWriteAction(void);//action после записи
void loadRMTKeySmallActualData(void);

COMPONENT_OBJ *rmtkeysmallcomponent;

/**************************************/
//подготовка компонента ранжирование клавиш MUTE RESET TEST
/**************************************/
void constructorRMTKeySmallComponent(COMPONENT_OBJ *rmtkeysmallcomp)
{
  rmtkeysmallcomponent = rmtkeysmallcomp;

  rmtkeysmallcomponent->countObject = 3;//к-во обектов

  rmtkeysmallcomponent->getModbusRegister = getRMTKeySmallModbusRegister;//получить содержимое регистра
  rmtkeysmallcomponent->getModbusBit      = getRMTKeySmallModbusBit;//получить содержимое бита
  rmtkeysmallcomponent->setModbusRegister = setRMTKeySmallModbusRegister;//получить содержимое регистра
  rmtkeysmallcomponent->setModbusBit      = setRMTKeySmallModbusBit;//получить содержимое бита

  rmtkeysmallcomponent->preReadAction   = preRMTKeySmallReadAction;//action до чтения
  rmtkeysmallcomponent->postReadAction  = postRMTKeySmallReadAction;//action после чтения
  rmtkeysmallcomponent->preWriteAction  = preRMTKeySmallWriteAction;//action до записи
  rmtkeysmallcomponent->postWriteAction = postRMTKeySmallWriteAction;//action после записи

  rmtkeysmallcomponent->isActiveActualData = 0;
}//prepareDVinConfig

void loadRMTKeySmallActualData(void) {
  //ActualData
  setRMTKeySmallCountObject(); //записать к-во обектов

   tempReadArray[0] = 0;
   __LN_BUTTON *arr = (__LN_BUTTON*)(spca_of_p_prt[ID_FB_BUTTON - _ID_FB_FIRST_VAR]);

   int value = arr[FIX_BUTTON_RESET].active_state[BUTTON_OUT >> 3] & (1 << (BUTTON_OUT & ((1 << 3) - 1)));
   int keydata = 0;
   if(value) keydata=1;
   tempReadArray[0] |= (keydata&0x1)<<(0);

   value = arr[FIX_BUTTON_MUTE].active_state[BUTTON_OUT >> 3] & (1 << (BUTTON_OUT & ((1 << 3) - 1)));
   keydata = 0;
   if(value) keydata=1;
   tempReadArray[0] |= (keydata&0x1)<<(1);

   value = arr[FIX_BUTTON_TEST].active_state[BUTTON_OUT >> 3] & (1 << (BUTTON_OUT & ((1 << 3) - 1)));
   keydata = 0;
   if(value) keydata=1;
   tempReadArray[0] |= (keydata&0x1)<<(2);

}//loadActualData() 

int getRMTKeySmallModbusRegister(int adrReg)
{
  //получить содержимое регистра
  if(privateRMTKeySmallGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  if(rmtkeysmallcomponent->isActiveActualData) loadRMTKeySmallActualData(); //ActualData
  rmtkeysmallcomponent->isActiveActualData = 0;

  superSetOperativMarker(rmtkeysmallcomponent, adrReg);

  return tempReadArray[adrReg-BEGIN_ADR_REGISTER];
}//getDOUTModbusRegister(int adrReg)
int getRMTKeySmallModbusBit(int adrBit)
{
  //получить содержимое bit
  if(privateRMTKeySmallGetBit2(adrBit)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  if(rmtkeysmallcomponent->isActiveActualData) loadRMTKeySmallActualData();
  rmtkeysmallcomponent->isActiveActualData = 0;

  superSetOperativMarker(rmtkeysmallcomponent, adrBit);

  short tmp   = tempReadArray[(adrBit-BEGIN_ADR_BIT)/16];
  short maska = 1<<((adrBit-BEGIN_ADR_BIT)%16);
  if(tmp&maska) return 1;
  return 0;
}//getDOUTBigModbusRegister(int adrReg)
int setRMTKeySmallModbusRegister(int x, int y)
{
  UNUSED(x);
  UNUSED(y);
  //записать содержимое регистра
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setRMTKeySmallModbusBit(int x, int y)
{
  UNUSED(x);
  UNUSED(y);
  //получить содержимое регистра
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void setRMTKeySmallCountObject(void) {
//записать к-во обектов
}//
void preRMTKeySmallReadAction(void) {
//action до чтения
  rmtkeysmallcomponent->operativMarker[0] = -1;
  rmtkeysmallcomponent->operativMarker[1] = -1;//оперативный маркер
  rmtkeysmallcomponent->isActiveActualData = 1;
}//
void postRMTKeySmallReadAction(void) {
//action после чтения
  if(rmtkeysmallcomponent->operativMarker[0]<0) return;//не было чтения
}//
void preRMTKeySmallWriteAction(void) {
//action до записи
  rmtkeysmallcomponent->operativMarker[0] = -1;
  rmtkeysmallcomponent->operativMarker[1] = -1;//оперативный маркер
  rmtkeysmallcomponent->isActiveActualData = 1;
}//
int postRMTKeySmallWriteAction(void) {
//action после записи
  return 0;
}//

int privateRMTKeySmallGetReg2(int adrReg)
{
  //проверить внутренний периметр
  int count_register = rmtkeysmallcomponent->countObject/16;
  if(rmtkeysmallcomponent->countObject%16) count_register++;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateDOUTSmallGetReg2(int adrReg)

int privateRMTKeySmallGetBit2(int adrBit)
{
  //проверить внутренний периметр
  int count_bit = BIT_FOR_OBJ*rmtkeysmallcomponent->countObject;
  if(adrBit>=BEGIN_ADR_BIT && adrBit<(BEGIN_ADR_BIT+count_bit)) return 0;
  return MARKER_OUTPERIMETR;
}//privateDOUTSmallGetBit2(int adrBit)
