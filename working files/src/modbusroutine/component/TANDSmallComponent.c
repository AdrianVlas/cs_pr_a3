#include "header.h"

//начальный регистр в карте памяти
#define BEGIN_ADR_REGISTER 2275
//начальный bit в карте памяти
#define BEGIN_ADR_BIT 50000
#define BIT_FOR_OBJ 1
//макс к-во обектов
//#define TOTAL_OBJ 128
//int privateTANDSmallGetReg1(int adrReg);
int privateTANDSmallGetReg2(int adrReg);
//int privateTANDSmallGetBit1(int adrBit);
int privateTANDSmallGetBit2(int adrBit);

int getTANDSmallModbusRegister(int);//получить содержимое регистра
int getTANDSmallModbusBit(int);//получить содержимое бита
int setTANDSmallModbusRegister(int, int);//получить содержимое регистра
int setTANDSmallModbusBit(int, int);//получить содержимое бита

void setTANDSmallCountObject(void);//записать к-во обектов
void preTANDSmallReadAction(void);//action до чтения
void postTANDSmallReadAction(void);//action после чтения
void preTANDSmallWriteAction(void);//action до записи
int postTANDSmallWriteAction(void);//action после записи
//void loadDVSmallActualData(void);

COMPONENT_OBJ *tandsmallcomponent;

/**************************************/
//подготовка компонента Технологический AND
/**************************************/
void constructorTANDSmallComponent(COMPONENT_OBJ *tandsmallcomp)
{
  tandsmallcomponent = dvsmallcomp;

  tandsmallcomponent->countObject = 128;//к-во обектов

  tandsmallcomponent->getModbusRegister = getTANDSmallModbusRegister;//получить содержимое регистра
  tandsmallcomponent->getModbusBit      = getTANDSmallModbusBit;//получить содержимое бита
  tandsmallcomponent->setModbusRegister = setTANDSmallModbusRegister;//получить содержимое регистра
  tandsmallcomponent->setModbusBit      = setTANDSmallModbusBit;//получить содержимое бита

  tandsmallcomponent->preReadAction   = preTANDSmallReadAction;//action до чтения
  tandsmallcomponent->postReadAction  = postTANDSmallReadAction;//action после чтения
  tandsmallcomponent->preWriteAction  = preTANDSmallWriteAction;//action до записи
  tandsmallcomponent->postWriteAction = postTANDSmallWriteAction;//action после записи

  tandsmallcomponent->isActiveActualData = 0;
}//prepareDVinConfig

void loadTANDSmallActualData(void) {
  //ActualData
   int cnt_treg = tandsmallcomponent->countObject/16;
   if(tandsmallcomponent->countObject%16) cnt_treg++;
   for(int ii=0; ii<cnt_treg; ii++) tempReadArray[ii] = 0;
/*
   __LN_INPUT *arr = (__LN_INPUT*)(spca_of_p_prt[ID_FB_INPUT - _ID_FB_FIRST_VAR]);
   for(int item=0; item<tandsmallcomponent->countObject; item++) {
   int ireg = item/16;
   int value = arr[item].active_state[INPUT_OUT >> 3] & (1 << (INPUT_OUT & ((1 << 3) - 1)));
   int dvdata = 0;
   if(value) dvdata=1;
   tempReadArray[ireg] |= dvdata<<(item%16);
  }//for
*/
}//loadActualData() 

int getTANDSmallModbusRegister(int adrReg)
{
  //получить содержимое регистра
  if(privateDVSmallGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(dvsmallcomponent->isActiveActualData) loadDVSmallActualData(); //ActualData
  dvsmallcomponent->isActiveActualData = 0;
  if(privateDVSmallGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;//MARKER_ERRORPERIMETR;

  superSetOperativMarker(dvsmallcomponent, adrReg);

  return tempReadArray[adrReg-BEGIN_ADR_REGISTER];
}//getDVModbusRegister(int adrReg)
int getTANDSmallModbusBit(int adrBit)
{
  //получить содержимое bit
  if(privateDVSmallGetBit2(adrBit)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(dvsmallcomponent->isActiveActualData) loadDVSmallActualData();
  dvsmallcomponent->isActiveActualData = 0;
  if(privateDVSmallGetBit1(adrBit)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;//MARKER_ERRORPERIMETR;

  superSetOperativMarker(dvsmallcomponent, adrBit);

  short tmp   = tempReadArray[(adrBit-BEGIN_ADR_BIT)/16];
  short maska = 1<<((adrBit-BEGIN_ADR_BIT)%16);
  if(tmp&maska) return 1;
  return 0;
}//getDVModbusBit(int adrReg)
int setTANDSmallModbusRegister(int x, int y)
{
  UNUSED(x);
  UNUSED(y);
  //записать содержимое регистра
  return MARKER_OUTPERIMETR;
}//getDVModbusRegister(int adrReg)
int setTANDSmallModbusBit(int x, int y)
{
  UNUSED(x);
  UNUSED(y);
  //получить содержимое регистра
  return MARKER_OUTPERIMETR;
}//getDVModbusRegister(int adrReg)

void setTANDSmallCountObject(void) {
//записать к-во обектов
  int cntObj = current_config.n_input; //Кількість дискретних входів
  if(cntObj<0) return;
  if(cntObj>TOTAL_OBJ) return;
  dvsmallcomponent->countObject = cntObj;
}//
void preTANDSmallReadAction(void) {
//action до чтения
  dvsmallcomponent->operativMarker[0] = -1;
  dvsmallcomponent->operativMarker[1] = -1;//оперативный маркер
  dvsmallcomponent->isActiveActualData = 1;
}//
void postTANDSmallReadAction(void) {
//action после чтения
  if(dvsmallcomponent->operativMarker[0]<0) return;//не было чтения
}//
void preTANDSmallWriteAction(void) {
//action до записи
  dvsmallcomponent->operativMarker[0] = -1;
  dvsmallcomponent->operativMarker[1] = -1;//оперативный маркер
  dvsmallcomponent->isActiveActualData = 1;
}//
int postTANDSmallWriteAction(void) {
//action после записи
 return 0;
}//

int privateTANDSmallGetReg2(int adrReg)
{
  //проверить внешний периметр
  int count_register = TOTAL_OBJ/16;
  if(TOTAL_OBJ%16) count_register++;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)

int privateTANDSmallGetBit2(int adrBit)
{
  //проверить внешний периметр
  int count_bit = BIT_FOR_OBJ*TOTAL_OBJ;
  if(adrBit>=BEGIN_ADR_BIT && adrBit<(BEGIN_ADR_BIT+count_bit)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
