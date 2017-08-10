#include "header.h"

//начальный регистр в карте памяти
#define BEGIN_ADR_REGISTER 408
//начальный bit в карте памяти
#define BEGIN_ADR_BIT 20131
#define BIT_FOR_OBJ 1
//макс к-во обектов
#define TOTAL_OBJ 128

int privateKEYSmallGetReg2(int adrReg);
int privateKEYSmallGetReg1(int adrReg);
int privateKEYSmallGetBit2(int adrReg);
int privateKEYSmallGetBit1(int adrReg);

int getKEYSmallModbusRegister(int);//получить содержимое регистра
int getKEYSmallModbusBit(int);//получить содержимое бита
int setKEYSmallModbusRegister(int, int);//получить содержимое регистра
int setKEYSmallModbusBit(int, int);//получить содержимое бита

void setKEYSmallCountObject(void);//записать к-во обектов
void preKEYSmallReadAction(void);//action до чтения
void postKEYSmallReadAction(void);//action после чтения
void preKEYSmallWriteAction(void);//action до записи
int postKEYSmallWriteAction(void);//action после записи
void loadKEYSmallActualData(void);
void loadRMTKeySmallActualData(void);

COMPONENT_OBJ *keysmallcomponent;

/**************************************/
//подготовка компонента ранжирование клавиш
/**************************************/
void constructorKEYSmallComponent(COMPONENT_OBJ *keysmallcomp)
{
  keysmallcomponent = keysmallcomp;

  keysmallcomponent->countObject = 0;//к-во обектов

  keysmallcomponent->getModbusRegister = getKEYSmallModbusRegister;//получить содержимое регистра
  keysmallcomponent->getModbusBit      = getKEYSmallModbusBit;//получить содержимое бита
  keysmallcomponent->setModbusRegister = setKEYSmallModbusRegister;//получить содержимое регистра
  keysmallcomponent->setModbusBit      = setKEYSmallModbusBit;//получить содержимое бита

  keysmallcomponent->preReadAction   = preKEYSmallReadAction;//action до чтения
  keysmallcomponent->postReadAction  = postKEYSmallReadAction;//action после чтения
  keysmallcomponent->preWriteAction  = preKEYSmallWriteAction;//action до записи
  keysmallcomponent->postWriteAction = postKEYSmallWriteAction;//action после записи

  keysmallcomponent->isActiveActualData = 0;
}//prepareDVinConfig

void loadKEYSmallActualData(void) {
  //ActualData
  int keyOffset = 3;

  setKEYSmallCountObject(); //записать к-во обектов

  int cnt_treg = keysmallcomponent->countObject/16;
  if(keysmallcomponent->countObject%16) cnt_treg++;
  for(int ii=0; ii<cnt_treg; ii++) tempReadArray[ii] = 0;
  loadRMTKeySmallActualData();

   __LN_BUTTON *arr = (__LN_BUTTON*)(spca_of_p_prt[ID_FB_BUTTON - _ID_FB_FIRST_VAR]);
  for(int item=0; item<keysmallcomponent->countObject; item++) {
   int ireg = (item+keyOffset)/16;
   int value = arr[item].active_state[BUTTON_OUT >> 3] & (1 << (BUTTON_OUT & ((1 << 3) - 1)));
   int keydata = 0;
   if(value) keydata=1;
   tempReadArray[ireg] |= (keydata&0x1)<<((item+keyOffset)%16);
  }//for
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
  if(privateKEYSmallGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;//MARKER_ERRORPERIMETR;

  superSetOperativMarker(keysmallcomponent, adrReg);

  return tempReadArray[adrReg-BEGIN_ADR_REGISTER];
}//getDOUTModbusRegister(int adrReg)
int getKEYSmallModbusBit(int adrBit)
{
  //получить содержимое bit
  int keyOffset = 3;

  if(privateKEYSmallGetBit2(adrBit)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(keysmallcomponent->isActiveActualData) loadKEYSmallActualData();
  keysmallcomponent->isActiveActualData = 0;
  if(privateKEYSmallGetBit1(adrBit)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  superSetOperativMarker(keysmallcomponent, adrBit);

  short tmp   = tempReadArray[(adrBit-BEGIN_ADR_BIT +keyOffset)/16];
  short maska = 1<<((adrBit-BEGIN_ADR_BIT +keyOffset)%16);
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

void setKEYSmallCountObject(void) {
//записать к-во обектов
  int cntObj = current_config.n_button;   //Кількість ФК
  if(cntObj<0) return;
  if(cntObj>TOTAL_OBJ) return;
  keysmallcomponent->countObject = cntObj;
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
int postKEYSmallWriteAction(void) {
//action после записи
 return 0;
}//

int privateKEYSmallGetReg1(int adrReg)
{
  //проверить внутренний периметр
  int keyOffset=3;
  int count_register = (keyOffset+keysmallcomponent->countObject)/16;
  if((keyOffset+keysmallcomponent->countObject)%16) count_register++;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateDOUTSmallGetReg2(int adrReg)
int privateKEYSmallGetReg2(int adrReg)
{
  //проверить внутренний периметр
  int keyOffset=3;
  int count_register = (keyOffset+TOTAL_OBJ)/16;
  if((keyOffset+TOTAL_OBJ)%16) count_register++;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateDOUTSmallGetReg2(int adrReg)

int privateKEYSmallGetBit1(int adrBit)
{
  //проверить внутренний периметр
  int count_bit = BIT_FOR_OBJ*keysmallcomponent->countObject;
  if(adrBit>=BEGIN_ADR_BIT && adrBit<(BEGIN_ADR_BIT+count_bit)) return 0;
  return MARKER_OUTPERIMETR;
}//privateDOUTSmallGetBit2(int adrBit)
int privateKEYSmallGetBit2(int adrBit)
{
  //проверить внутренний периметр
  int count_bit = BIT_FOR_OBJ*TOTAL_OBJ;
  if(adrBit>=BEGIN_ADR_BIT && adrBit<(BEGIN_ADR_BIT+count_bit)) return 0;
  return MARKER_OUTPERIMETR;
}//privateDOUTSmallGetBit2(int adrBit)
