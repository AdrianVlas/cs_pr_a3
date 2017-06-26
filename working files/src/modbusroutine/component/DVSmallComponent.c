#include "header.h"

//начальный регистр в карте памяти
#define BEGIN_ADR_REGISTER 400
//начальный bit в карте памяти
#define BEGIN_ADR_BIT 20000
#define BIT_FOR_OBJ 1
//макс к-во обектов
#define TOTAL_OBJ 128
int privateDVSmallGetReg1(int adrReg);
int privateDVSmallGetReg2(int adrReg);
int privateDVSmallGetBit1(int adrBit);
int privateDVSmallGetBit2(int adrBit);

int getDVSmallModbusRegister(int);//получить содержимое регистра
int getDVSmallModbusBit(int);//получить содержимое бита
int setDVSmallModbusRegister(int, int);//получить содержимое регистра
int setDVSmallModbusBit(int, int);//получить содержимое бита

void setDVSmallCountObject(void);//записать к-во обектов
void preDVSmallReadAction(void);//action до чтения
void postDVSmallReadAction(void);//action после чтения
void preDVSmallWriteAction(void);//action до записи
void postDVSmallWriteAction(void);//action после записи
void loadDVSmallActualData(void);

COMPONENT_OBJ *dvsmallcomponent;

/**************************************/
//подготовка компонента ДВ
/**************************************/
void constructorDVSmallComponent(COMPONENT_OBJ *dvsmallcomp)
{
  dvsmallcomponent = dvsmallcomp;

  dvsmallcomponent->countObject = 0;//к-во обектов

  dvsmallcomponent->getModbusRegister = getDVSmallModbusRegister;//получить содержимое регистра
  dvsmallcomponent->getModbusBit      = getDVSmallModbusBit;//получить содержимое бита
  dvsmallcomponent->setModbusRegister = setDVSmallModbusRegister;//получить содержимое регистра
  dvsmallcomponent->setModbusBit      = setDVSmallModbusBit;//получить содержимое бита

  dvsmallcomponent->preReadAction   = preDVSmallReadAction;//action до чтения
  dvsmallcomponent->postReadAction  = postDVSmallReadAction;//action после чтения
  dvsmallcomponent->preWriteAction  = preDVSmallWriteAction;//action до записи
  dvsmallcomponent->postWriteAction = postDVSmallWriteAction;//action после записи

  dvsmallcomponent->isActiveActualData = 0;
}//prepareDVinConfig

void loadDVSmallActualData(void) {
  //ActualData
   setDVSmallCountObject(); //записать к-во обектов

   int cnt_treg = dvsmallcomponent->countObject/16;
   if(dvsmallcomponent->countObject%16) cnt_treg++;
   for(int ii=0; ii<cnt_treg; ii++) tempReadArray[ii] = 0;
   __LN_INPUT *arr = (__LN_INPUT*)(spca_of_p_prt[ID_FB_INPUT - _ID_FB_FIRST_VAR]);
   for(int item=0; item<dvsmallcomponent->countObject; item++) {
   int ireg = item/16;
   int value = arr[item].active_state[INPUT_OUT >> 3] & (1 << (INPUT_OUT & ((1 << 3) - 1)));
   int dvdata = 0;
   if(value) dvdata=1;
   tempReadArray[ireg] |= dvdata<<(item%16);
  }//for
}//loadActualData() 

int getDVSmallModbusRegister(int adrReg)
{
  //получить содержимое регистра
  if(privateDVSmallGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(dvsmallcomponent->isActiveActualData) loadDVSmallActualData(); //ActualData
  dvsmallcomponent->isActiveActualData = 0;
  if(privateDVSmallGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;//MARKER_ERRORPERIMETR;

  superSetOperativMarker(dvsmallcomponent, adrReg);

  return tempReadArray[adrReg-BEGIN_ADR_REGISTER];
}//getDVModbusRegister(int adrReg)
int getDVSmallModbusBit(int adrBit)
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
int setDVSmallModbusRegister(int adrReg, int x)
{
  UNUSED(x);
  //записать содержимое регистра
  superSetOperativMarker(dvsmallcomponent, adrReg);
  return MARKER_OUTPERIMETR;
}//getDVModbusRegister(int adrReg)
int setDVSmallModbusBit(int adrBit, int x)
{
  UNUSED(x);
  //получить содержимое регистра
  superSetOperativMarker(dvsmallcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDVModbusRegister(int adrReg)

void setDVSmallCountObject(void) {
//записать к-во обектов
  int cntObj = current_config.n_input; //Кількість дискретних входів
  if(cntObj<0) return;
  if(cntObj>TOTAL_OBJ) return;
  dvsmallcomponent->countObject = cntObj;
}//
void preDVSmallReadAction(void) {
//action до чтения
  dvsmallcomponent->operativMarker[0] = -1;
  dvsmallcomponent->operativMarker[1] = -1;//оперативный маркер
  dvsmallcomponent->isActiveActualData = 1;
}//
void postDVSmallReadAction(void) {
//action после чтения
  if(dvsmallcomponent->operativMarker[0]<0) return;//не было чтения
}//
void preDVSmallWriteAction(void) {
//action до записи
  dvsmallcomponent->operativMarker[0] = -1;
  dvsmallcomponent->operativMarker[1] = -1;//оперативный маркер
  dvsmallcomponent->isActiveActualData = 1;
}//
void postDVSmallWriteAction(void) {
//action после записи
}//

int privateDVSmallGetReg1(int adrReg)
{
  //проверить внутренний периметр
  int count_register = dvsmallcomponent->countObject/16;
  if(dvsmallcomponent->countObject%16) count_register++;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg1(int adrReg)

int privateDVSmallGetReg2(int adrReg)
{
  //проверить внешний периметр
  int count_register = TOTAL_OBJ/16;
  if(TOTAL_OBJ%16) count_register++;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)

int privateDVSmallGetBit1(int adrBit)
{
  //проверить внутренний периметр
  int count_bit = BIT_FOR_OBJ*dvsmallcomponent->countObject;
  if(adrBit>=BEGIN_ADR_BIT && adrBit<(BEGIN_ADR_BIT+count_bit)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg1(int adrReg)

int privateDVSmallGetBit2(int adrBit)
{
  //проверить внешний периметр
  int count_bit = BIT_FOR_OBJ*TOTAL_OBJ;
  if(adrBit>=BEGIN_ADR_BIT && adrBit<(BEGIN_ADR_BIT+count_bit)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
