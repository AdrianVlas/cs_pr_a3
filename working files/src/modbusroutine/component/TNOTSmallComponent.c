#include "header.h"

//начальный регистр в карте памяти
#define BEGIN_ADR_REGISTER 2299
//начальный bit в карте памяти
#define BEGIN_ADR_BIT 50384
#define BIT_FOR_OBJ 1

int privateTNOTSmallGetReg2(int adrReg);
int privateTNOTSmallGetBit2(int adrBit);

int getTNOTSmallModbusRegister(int);//получить содержимое регистра
int getTNOTSmallModbusBit(int);//получить содержимое бита
int setTNOTSmallModbusRegister(int, int);//получить содержимое регистра
int setTNOTSmallModbusBit(int, int);//получить содержимое бита

void setTNOTSmallCountObject(void);//записать к-во обектов
void preTNOTSmallReadAction(void);//action до чтения
void postTNOTSmallReadAction(void);//action после чтения
void preTNOTSmallWriteAction(void);//action до записи
int  postTNOTSmallWriteAction(void);//action после записи
void loadTNOTSmallActualData(void);
void config_and_settingsTNOTSmall(void);//action активации

COMPONENT_OBJ *tnotsmallcomponent;

/**************************************/
//подготовка компонента Технологический XOR
/**************************************/
void constructorTXORSmallComponent(COMPONENT_OBJ *tnotsmallcomp)
{
  tnotsmallcomponent = tnotsmallcomp;

  tnotsmallcomponent->countObject = 128;//к-во обектов

  tnotsmallcomponent->getModbusRegister = getTNOTSmallModbusRegister;//получить содержимое регистра
  tnotsmallcomponent->getModbusBit      = getTNOTSmallModbusBit;//получить содержимое бита
  tnotsmallcomponent->setModbusRegister = setTNOTSmallModbusRegister;//получить содержимое регистра
  tnotsmallcomponent->setModbusBit      = setTNOTSmallModbusBit;//получить содержимое бита

  tnotsmallcomponent->preReadAction   = preTNOTSmallReadAction;//action до чтения
  tnotsmallcomponent->postReadAction  = postTNOTSmallReadAction;//action после чтения
  tnotsmallcomponent->preWriteAction  = preTNOTSmallWriteAction;//action до записи
  tnotsmallcomponent->postWriteAction = postTNOTSmallWriteAction;//action после записи
  tnotsmallcomponent->config_and_settings = config_and_settingsTNOTSmall;//action активации

  tnotsmallcomponent->isActiveActualData = 0;
}//prepareDVinConfig

void loadTNOTSmallActualData(void) {
  //ActualData
extern int pointInterface;//метка интерфейса 0-USB 1-RS485
   int cnt_treg = tnotsmallcomponent->countObject/16;
   if(tnotsmallcomponent->countObject%16) cnt_treg++;
   for(int ii=0; ii<cnt_treg; ii++) tempReadArray[ii] = 0;

   __LN_NOT *arr = (__LN_NOT*)(spca_of_p_prt[ID_FB_NOT - _ID_FB_FIRST_VAR]);
   for(int item=0; item<tnotsmallcomponent->countObject; item++) {
   int ireg = item/16;
   int value = arr[item].active_state[0];
   int tdata = 0;
   if(value) tdata=1;
   tempReadArray[ireg] |= tdata<<(item%16);
  }//for

}//loadTXORSmallActualData() 

int getTNOTSmallModbusRegister(int adrReg)
{
  //получить содержимое регистра
  if(privateTNOTSmallGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(tnotsmallcomponent->isActiveActualData) loadTNOTSmallActualData(); //ActualData
  tnotsmallcomponent->isActiveActualData = 0;

  superSetOperativMarker(tnotsmallcomponent, adrReg);

  return tempReadArray[adrReg-BEGIN_ADR_REGISTER];
}//getTXORSmallModbusRegister(int adrReg)
int getTNOTSmallModbusBit(int adrBit)
{
  //получить содержимое bit
  if(privateTNOTSmallGetBit2(adrBit)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(tnotsmallcomponent->isActiveActualData) loadTNOTSmallActualData();
  tnotsmallcomponent->isActiveActualData = 0;

  superSetOperativMarker(tnotsmallcomponent, adrBit);

  short tmp   = tempReadArray[(adrBit-BEGIN_ADR_BIT)/16];
  short maska = 1<<((adrBit-BEGIN_ADR_BIT)%16);
  if(tmp&maska) return 1;
  return 0;
}//getTORSmallModbusBit(int adrReg)
int setTNOTSmallModbusRegister(int x, int y)
{
  UNUSED(x);
  UNUSED(y);
  //записать содержимое регистра
  return MARKER_OUTPERIMETR;
}//setTXORSmallModbusRegister(int x, int y)
int setTNOTSmallModbusBit(int x, int y)
{
  UNUSED(x);
  UNUSED(y);
  //получить содержимое регистра
  return MARKER_OUTPERIMETR;
}//setTXORSmallModbusBit(int x, int y)

void preTNOTSmallReadAction(void) {
//action до чтения
  tnotsmallcomponent->operativMarker[0] = -1;
  tnotsmallcomponent->operativMarker[1] = -1;//оперативный маркер
  tnotsmallcomponent->isActiveActualData = 1;
}//
void postTNOTSmallReadAction(void) {
//action после чтения
  if(tnotsmallcomponent->operativMarker[0]<0) return;//не было чтения
}//
void preTNOTSmallWriteAction(void) {
//action до записи
  tnotsmallcomponent->operativMarker[0] = -1;
  tnotsmallcomponent->operativMarker[1] = -1;//оперативный маркер
  tnotsmallcomponent->isActiveActualData = 1;
}//
int postTNOTSmallWriteAction(void) {
//action после записи
 return 0;
}//

int privateTNOTSmallGetReg2(int adrReg)
{
  //проверить внешний периметр
  int count_register = TOTAL_OBJ/16;
  if(TOTAL_OBJ%16) count_register++;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)

int privateTNOTSmallGetBit2(int adrBit)
{
  //проверить внешний периметр
  int count_bit = BIT_FOR_OBJ*TOTAL_OBJ;
  if(adrBit>=BEGIN_ADR_BIT && adrBit<(BEGIN_ADR_BIT+count_bit)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)

void config_and_settingsTNOTSmall(void)
{
//action активации
}

