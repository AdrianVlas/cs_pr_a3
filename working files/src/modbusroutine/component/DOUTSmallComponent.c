
#include "header.h"

//начальный регистр в карте памяти
#define BEGIN_ADR_REGISTER 300
//начальный bit в карте памяти
#define BEGIN_ADR_BIT 19000
#define BIT_FOR_OBJ 1
//макс к-во обектов
#define TOTAL_OBJ 128
int privateDOUTSmallGetReg1(int adrReg);
int privateDOUTSmallGetReg2(int adrReg);
int privateDOUTSmallGetBit1(int adrBit);
int privateDOUTSmallGetBit2(int adrBit);

int getDOUTSmallModbusRegister(int);//получить содержимое регистра
int getDOUTSmallModbusBit(int);//получить содержимое бита
int setDOUTSmallModbusRegister(int, int);//записать регистр
int setDOUTSmallModbusBit(int, int);//записать бит

void setDOUTSmallCountObject(void);//записать к-во обектов
void preDOUTSmallReadAction(void);//action до чтения
void postDOUTSmallReadAction(void);//action после чтения
void preDOUTSmallWriteAction(void);//action до записи
void postDOUTSmallWriteAction(void);//action после записи
void loadDOUTSmallActualData(void);

COMPONENT_OBJ *doutsmallcomponent;

/**************************************/
//подготовка компонента ДВ
/**************************************/
void constructorDOUTSmallComponent(COMPONENT_OBJ *doutcomp)
{
  doutsmallcomponent = doutcomp;
  doutsmallcomponent->countObject = 0;//к-во обектов

  doutsmallcomponent->getModbusRegister = getDOUTSmallModbusRegister;//получить содержимое регистра
  doutsmallcomponent->getModbusBit      = getDOUTSmallModbusBit;//получить содержимое бита
  doutsmallcomponent->setModbusRegister = setDOUTSmallModbusRegister;// регистра
  doutsmallcomponent->setModbusBit      = setDOUTSmallModbusBit;// бита

  doutsmallcomponent->preReadAction   = preDOUTSmallReadAction;//action до чтения
  doutsmallcomponent->postReadAction  = postDOUTSmallReadAction;//action после чтения
  doutsmallcomponent->preWriteAction  = preDOUTSmallWriteAction;//action до записи
  doutsmallcomponent->postWriteAction = postDOUTSmallWriteAction;//action после записи
 
  doutsmallcomponent->isActiveActualData = 0;
}//prepareDVinConfig

void loadDOUTSmallActualData(void) {
  //ActualData
   setDOUTSmallCountObject(); //записать к-во обектов

   int cnt_treg = doutsmallcomponent->countObject/16;
   if(doutsmallcomponent->countObject%16) cnt_treg++;
   for(int ii=0; ii<cnt_treg; ii++) tempReadArray[ii] = 0;
  __LN_OUTPUT_LED *arr = (__LN_OUTPUT_LED*)(spca_of_p_prt[ID_FB_OUTPUT - _ID_FB_FIRST_VAR]);
   for(int item=0; item<doutsmallcomponent->countObject; item++) {
   int ireg = item/16;
   int value = arr[item].active_state[OUTPUT_LED_OUT >> 3] & (1 << (OUTPUT_LED_OUT & ((1 << 3) - 1)));
   int doutdata = 0;
   if(value) doutdata=1;
   tempReadArray[ireg] |= doutdata<<(item%16);
  }//for
}//loadActualData() 

int getDOUTSmallModbusRegister(int adrReg) {
  //получить содержимое регистра
  if(privateDOUTSmallGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(doutsmallcomponent->isActiveActualData) loadDOUTSmallActualData(); //ActualData
  doutsmallcomponent->isActiveActualData = 0;
  if(privateDOUTSmallGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;//MARKER_ERRORPERIMETR;

  superSetOperativMarker(doutsmallcomponent, adrReg);

  return tempReadArray[adrReg-BEGIN_ADR_REGISTER];
}//getDOUTModbusRegister(int adrReg)
int getDOUTSmallModbusBit(int adrBit) {
  //получить содержимое bit
  if(privateDOUTSmallGetBit2(adrBit)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(doutsmallcomponent->isActiveActualData) loadDOUTSmallActualData();
  doutsmallcomponent->isActiveActualData = 0;
  if(privateDOUTSmallGetBit1(adrBit)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;//MARKER_ERRORPERIMETR;

  superSetOperativMarker(doutsmallcomponent, adrBit);

  short tmp   = tempReadArray[(adrBit-BEGIN_ADR_BIT)/16];
  short maska = 1<<((adrBit-BEGIN_ADR_BIT)%16);
  if(tmp&maska) return 1;
  return 0;
}//getDOUTModbusBit(int adrReg)
int setDOUTSmallModbusRegister(int adrReg, int x) {
  UNUSED(x);
  //записать содержимое регистра
  superSetOperativMarker(doutsmallcomponent, adrReg);
  return MARKER_OUTPERIMETR;
}//getDOUTModbusRegister(int adrReg)
int setDOUTSmallModbusBit(int adrBit, int x) {
  UNUSED(x);
  //получить содержимое регистра
  superSetOperativMarker(doutsmallcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDOUTModbusRegister(int adrReg)

void setDOUTSmallCountObject(void) {
//записать к-во обектов
  int cntObj = current_config.n_output; //Кількість дискретних виходів
  if(cntObj<0) return;
  if(cntObj>TOTAL_OBJ) return;
  doutsmallcomponent->countObject = cntObj;
}//
void preDOUTSmallReadAction(void) {
//action до чтения
  doutsmallcomponent->operativMarker[0] = -1;
  doutsmallcomponent->operativMarker[1] = -1;//оперативный маркер
  doutsmallcomponent->isActiveActualData = 1;
}//
void postDOUTSmallReadAction(void) {
//action после чтения
  if(doutsmallcomponent->operativMarker[0]<0) return;//не было чтения
}//
void preDOUTSmallWriteAction(void) {
//action до записи
  doutsmallcomponent->operativMarker[0] = -1;
  doutsmallcomponent->operativMarker[1] = -1;//оперативный маркер
  doutsmallcomponent->isActiveActualData = 1;
}//
void postDOUTSmallWriteAction(void) {
//action после записи
}//

int privateDOUTSmallGetReg1(int adrReg)
{
  //проверить внутренний периметр
  int count_register = doutsmallcomponent->countObject/16;
  if(doutsmallcomponent->countObject%16) count_register++;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateDOUTSmallGetReg2(int adrReg)

int privateDOUTSmallGetReg2(int adrReg)
{
  //проверить внешний периметр
  int count_register = TOTAL_OBJ/16;
  if(TOTAL_OBJ%16) count_register++;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)

int privateDOUTSmallGetBit1(int adrBit)
{
  //проверить внутренний периметр
  int count_bit = BIT_FOR_OBJ*doutsmallcomponent->countObject;
  if(adrBit>=BEGIN_ADR_BIT && adrBit<(BEGIN_ADR_BIT+count_bit)) return 0;
  return MARKER_OUTPERIMETR;
}//privateDOUTSmallGetBit2(int adrBit)

int privateDOUTSmallGetBit2(int adrBit)
{
  //проверить внешний периметр
  int count_bit = BIT_FOR_OBJ*TOTAL_OBJ;
  if(adrBit>=BEGIN_ADR_BIT && adrBit<(BEGIN_ADR_BIT+count_bit)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
