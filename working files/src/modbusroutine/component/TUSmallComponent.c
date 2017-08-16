#include "header.h"

//начальный регистр в карте памяти
#define BEGIN_ADR_REGISTER 208
//начальный bit в карте памяти
#define BEGIN_ADR_BIT 18128
#define BIT_FOR_OBJ 1
//макс к-во обектов
#define TOTAL_OBJ 128
int privateTUSmallGetReg1(int adrReg);
int privateTUSmallGetReg2(int adrReg);
int privateTUSmallGetBit1(int adrBit);
int privateTUSmallGetBit2(int adrBit);

int getTUSmallModbusRegister(int);//получить содержимое регистра
int getTUSmallModbusBit(int);//получить содержимое бита
int setTUSmallModbusRegister(int, int);//получить содержимое регистра
int setTUSmallModbusBit(int, int);//получить содержимое бита

void setTUSmallCountObject(void);//записать к-во обектов
void preTUSmallReadAction(void);//action до чтения
void postTUSmallReadAction(void);//action после чтения
void preTUSmallWriteAction(void);//action до записи
int postTUSmallWriteAction(void);//action после записи
void loadTUSmallActualData(void);
int getTUmallModbusBeginAdrRegister(void);

COMPONENT_OBJ *tusmallcomponent;

int getTUmallModbusBeginAdrRegister(void)
{
  //получить адрес нач регистра
 return BEGIN_ADR_REGISTER;
}//getTSmallModbusBeginAdrRegister(void)

/**************************************/
//подготовка компонента телеуправление
/**************************************/
void constructorTUSmallComponent(COMPONENT_OBJ *tusmallcomp)
{
  tusmallcomponent = tusmallcomp;

  tusmallcomponent->countObject = 0;//к-во обектов

  tusmallcomponent->getModbusRegister = getTUSmallModbusRegister;//получить содержимое регистра
  tusmallcomponent->getModbusBit      = getTUSmallModbusBit;//получить содержимое бита
  tusmallcomponent->setModbusRegister = setTUSmallModbusRegister;//получить содержимое регистра
  tusmallcomponent->setModbusBit      = setTUSmallModbusBit;//получить содержимое бита

  tusmallcomponent->preReadAction   = preTUSmallReadAction;//action до чтения
  tusmallcomponent->postReadAction  = postTUSmallReadAction;//action после чтения
  tusmallcomponent->preWriteAction  = preTUSmallWriteAction;//action до записи
  tusmallcomponent->postWriteAction = postTUSmallWriteAction;//action после записи

  tusmallcomponent->isActiveActualData = 0;
}//prepareDVinConfig
/*
void loadTUSmallActualData(void) {
 setTUSmallCountObject(); //записать к-во обектов

  //ActualData
  int cnt_treg = tusmallcomponent->countObject/16;
  if(tusmallcomponent->countObject%16) cnt_treg++;
  for(int ii=0; ii<cnt_treg; ii++) tempReadArray[ii] = 0;
   __LN_TU *arr = (__LN_TU*)(spca_of_p_prt[ID_FB_TU - _ID_FB_FIRST_VAR]);
  for(int item=0; item<tusmallcomponent->countObject; item++) {
   int ireg = item/16;

   int value = arr[item].active_state[TU_OUT  >> 3] & (1 << (TU_OUT  & ((1 << 3) - 1)));
   
   int tudata = 0;
   if(value) tudata=1;
   tempReadArray[ireg] |= (tudata&0x1)<<(item%16);
  }//for
}//loadActualData() 
*/

int getTUSmallModbusRegister(int x)
{
  //получить содержимое регистра
  UNUSED(x);
  return MARKER_OUTPERIMETR;

}//getDVModbusRegister(int adrReg)
int getTUSmallModbusBit(int x)
{
  //получить содержимое bit
  UNUSED(x);
  return MARKER_OUTPERIMETR;

}//getTUSmallModbusBit(int adrBit)
int setTUSmallModbusRegister(int adrReg, int dataReg)
{
  if(privateTUSmallGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(tusmallcomponent->isActiveActualData) setTUSmallCountObject(); //записать к-во обектов
  tusmallcomponent->isActiveActualData = 0;
  if(privateTUSmallGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

//  UNUSED(x);
  //записать содержимое регистра
  superSetOperativMarker(tusmallcomponent, adrReg);
  superSetTempWriteArray(dataReg);//записать в буфер

  return 0;
}//getDVModbusRegister(int adrReg)
int setTUSmallModbusBit(int adrBit, int dataBit)
{
  if(privateTUSmallGetBit2(adrBit)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(tusmallcomponent->isActiveActualData) setTUSmallCountObject(); //записать к-во обектов
  tusmallcomponent->isActiveActualData = 0;
  if(privateTUSmallGetBit1(adrBit)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;
//  UNUSED(x);
  //записать содержимое bit
  superSetOperativMarker(tusmallcomponent, adrBit);
  superSetTempWriteArray(dataBit);//записать в буфер

  return 0;
}//getDVModbusRegister(int adrReg)

void setTUSmallCountObject(void) {
//записать к-во обектов
  int cntObj = current_config.n_tu;    //Кількість блоків сигналізацій
  if(cntObj<0) return;
  if(cntObj>TOTAL_OBJ) return;
  tusmallcomponent->countObject = cntObj;
}//
void preTUSmallReadAction(void) {
//action до чтения
  tusmallcomponent->operativMarker[0] = -1;
  tusmallcomponent->operativMarker[1] = -1;//оперативный маркер
  tusmallcomponent->isActiveActualData = 1;
}//
void postTUSmallReadAction(void) {
//action после чтения
  if(tusmallcomponent->operativMarker[0]<0) return;//не было чтения
}//
void preTUSmallWriteAction(void) {
//action до записи
  tusmallcomponent->operativMarker[0] = -1;
  tusmallcomponent->operativMarker[1] = -1;//оперативный маркер
  tusmallcomponent->isActiveActualData = 1;
}//
int postTUSmallWriteAction(void) {
//action после записи
 return 0;
}//

int privateTUSmallGetReg1(int adrReg)
{
  //проверить внутренний периметр
  int count_register = tusmallcomponent->countObject/16;
  if(tusmallcomponent->countObject%16) count_register++;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg1(int adrReg)

int privateTUSmallGetReg2(int adrReg)
{
  //проверить внешний периметр
  int count_register = TOTAL_OBJ/16;
  if(TOTAL_OBJ%16) count_register++;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)

int privateTUSmallGetBit1(int adrBit)
{
  //проверить внутренний периметр
  int count_bit = BIT_FOR_OBJ*tusmallcomponent->countObject;
  if(adrBit>=BEGIN_ADR_BIT && adrBit<(BEGIN_ADR_BIT+count_bit)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg1(int adrReg)

int privateTUSmallGetBit2(int adrBit)
{
  //проверить внешний периметр
  int count_bit = BIT_FOR_OBJ*TOTAL_OBJ;
  if(adrBit>=BEGIN_ADR_BIT && adrBit<(BEGIN_ADR_BIT+count_bit)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
