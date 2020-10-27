#include "header.h"

//начальный регистр в карте памяти
#define BEGIN_ADR_REGISTER 2291
//начальный bit в карте памяти
#define BEGIN_ADR_BIT 50256
#define BIT_FOR_OBJ 1

int privateTXORSmallGetReg2(int adrReg);
int privateTXORSmallGetBit2(int adrBit);

int getTXORSmallModbusRegister(int);//получить содержимое регистра
int getTXORSmallModbusBit(int);//получить содержимое бита
int setTXORSmallModbusRegister(int, int);//получить содержимое регистра
int setTXORSmallModbusBit(int, int);//получить содержимое бита

void setTXORSmallCountObject(void);//записать к-во обектов
void preTXORSmallReadAction(void);//action до чтения
void postTXORSmallReadAction(void);//action после чтения
void preTXORSmallWriteAction(void);//action до записи
int  postTXORSmallWriteAction(void);//action после записи
void loadTXORSmallActualData(void);
void config_and_settingsTXORSmall(void);//action активации

COMPONENT_OBJ *txorsmallcomponent;

/**************************************/
//подготовка компонента Технологический XOR
/**************************************/
void constructorTXORSmallComponent(COMPONENT_OBJ *txorsmallcomp)
{
  txorsmallcomponent = txorsmallcomp;

  txorsmallcomponent->countObject = 128;//к-во обектов

  txorsmallcomponent->getModbusRegister = getTXORSmallModbusRegister;//получить содержимое регистра
  txorsmallcomponent->getModbusBit      = getTXORSmallModbusBit;//получить содержимое бита
  txorsmallcomponent->setModbusRegister = setTXORSmallModbusRegister;//получить содержимое регистра
  txorsmallcomponent->setModbusBit      = setTXORSmallModbusBit;//получить содержимое бита

  txorsmallcomponent->preReadAction   = preTXORSmallReadAction;//action до чтения
  txorsmallcomponent->postReadAction  = postTXORSmallReadAction;//action после чтения
  txorsmallcomponent->preWriteAction  = preTXORSmallWriteAction;//action до записи
  txorsmallcomponent->postWriteAction = postTXORSmallWriteAction;//action после записи
  txorsmallcomponent->config_and_settings = config_and_settingsTXORSmall;//action активации

  txorsmallcomponent->isActiveActualData = 0;
}//prepareDVinConfig

void loadTXORSmallActualData(void) {
  //ActualData
extern int pointInterface;//метка интерфейса 0-USB 1-RS485
   int cnt_treg = txorsmallcomponent->countObject/16;
   if(txorsmallcomponent->countObject%16) cnt_treg++;
   for(int ii=0; ii<cnt_treg; ii++) tempReadArray[ii] = 0;

   __LN_XOR *arr = (__LN_XOR*)(spca_of_p_prt[ID_FB_XOR - _ID_FB_FIRST_VAR]);
   for(int item=0; item<txorsmallcomponent->countObject; item++) {
   int ireg = item/16;
   int value = arr[item].active_state[0];
   int tdata = 0;
   if(value) tdata=1;
   tempReadArray[ireg] |= tdata<<(item%16);
  }//for

}//loadTXORSmallActualData() 

int getTXORSmallModbusRegister(int adrReg)
{
  //получить содержимое регистра
  if(privateTXORSmallGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(txorsmallcomponent->isActiveActualData) loadTXORSmallActualData(); //ActualData
  txorsmallcomponent->isActiveActualData = 0;

  superSetOperativMarker(txorsmallcomponent, adrReg);

  return tempReadArray[adrReg-BEGIN_ADR_REGISTER];
}//getTXORSmallModbusRegister(int adrReg)
int getTXORSmallModbusBit(int adrBit)
{
  //получить содержимое bit
  if(privateTXORSmallGetBit2(adrBit)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(txorsmallcomponent->isActiveActualData) loadTXORSmallActualData();
  txorsmallcomponent->isActiveActualData = 0;

  superSetOperativMarker(txorsmallcomponent, adrBit);

  short tmp   = tempReadArray[(adrBit-BEGIN_ADR_BIT)/16];
  short maska = 1<<((adrBit-BEGIN_ADR_BIT)%16);
  if(tmp&maska) return 1;
  return 0;
}//getTORSmallModbusBit(int adrReg)
int setTXORSmallModbusRegister(int x, int y)
{
  UNUSED(x);
  UNUSED(y);
  //записать содержимое регистра
  return MARKER_OUTPERIMETR;
}//setTXORSmallModbusRegister(int x, int y)
int setTXORSmallModbusBit(int x, int y)
{
  UNUSED(x);
  UNUSED(y);
  //получить содержимое регистра
  return MARKER_OUTPERIMETR;
}//setTXORSmallModbusBit(int x, int y)

void preTXORSmallReadAction(void) {
//action до чтения
  txorsmallcomponent->operativMarker[0] = -1;
  txorsmallcomponent->operativMarker[1] = -1;//оперативный маркер
  txorsmallcomponent->isActiveActualData = 1;
}//
void postTXORSmallReadAction(void) {
//action после чтения
  if(txorsmallcomponent->operativMarker[0]<0) return;//не было чтения
}//
void preTXORSmallWriteAction(void) {
//action до записи
  txorsmallcomponent->operativMarker[0] = -1;
  txorsmallcomponent->operativMarker[1] = -1;//оперативный маркер
  txorsmallcomponent->isActiveActualData = 1;
}//
int postTXORSmallWriteAction(void) {
//action после записи
 return 0;
}//

int privateTXORSmallGetReg2(int adrReg)
{
  //проверить внешний периметр
  int count_register = TOTAL_OBJ/16;
  if(TOTAL_OBJ%16) count_register++;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)

int privateTXORSmallGetBit2(int adrBit)
{
  //проверить внешний периметр
  int count_bit = BIT_FOR_OBJ*TOTAL_OBJ;
  if(adrBit>=BEGIN_ADR_BIT && adrBit<(BEGIN_ADR_BIT+count_bit)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)

void config_and_settingsTXORSmall(void)
{
//action активации
}

