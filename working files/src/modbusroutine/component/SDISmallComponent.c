#include "header.h"

//начальный регистр в карте памяти
#define BEGIN_ADR_REGISTER 500
//начальный bit в карте памяти
#define BEGIN_ADR_BIT 21000
#define BIT_FOR_OBJ 1
//макс к-во обектов
#define TOTAL_OBJ 128
int privateSDISmallGetReg1(int adrReg);
int privateSDISmallGetReg2(int adrReg);
int privateSDISmallGetBit1(int adrBit);
int privateSDISmallGetBit2(int adrBit);

int getSDISmallModbusRegister(int);//получить содержимое регистра
int getSDISmallModbusBit(int);//получить содержимое бита
int setSDISmallModbusRegister(int, int);//получить содержимое регистра
int setSDISmallModbusBit(int, int);//получить содержимое бита

void setSDISmallCountObject(void);//записать к-во обектов
void preSDISmallReadAction(void);//action до чтения
void postSDISmallReadAction(void);//action после чтения
void preSDISmallWriteAction(void);//action до записи
int postSDISmallWriteAction(void);//action после записи
void loadSDISmallActualData(void);

COMPONENT_OBJ *sdismallcomponent;

/**************************************/
//подготовка компонента светоиндикаторов
/**************************************/
void constructorSDISmallComponent(COMPONENT_OBJ *sdismallcomp)
{
  sdismallcomponent = sdismallcomp;

  sdismallcomponent->countObject = 0;//к-во обектов

  sdismallcomponent->getModbusRegister = getSDISmallModbusRegister;//получить содержимое регистра
  sdismallcomponent->getModbusBit      = getSDISmallModbusBit;//получить содержимое бита
  sdismallcomponent->setModbusRegister = setSDISmallModbusRegister;//получить содержимое регистра
  sdismallcomponent->setModbusBit      = setSDISmallModbusBit;//получить содержимое бита

  sdismallcomponent->preReadAction   = preSDISmallReadAction;//action до чтения
  sdismallcomponent->postReadAction  = postSDISmallReadAction;//action после чтения
  sdismallcomponent->preWriteAction  = preSDISmallWriteAction;//action до записи
  sdismallcomponent->postWriteAction = postSDISmallWriteAction;//action после записи

  sdismallcomponent->isActiveActualData = 0;
}//prepareDVinConfig

void loadSDISmallActualData(void) {
  //ActualData
   setSDISmallCountObject(); //записать к-во обектов

   int cnt_treg = sdismallcomponent->countObject/16;
   if(sdismallcomponent->countObject%16) cnt_treg++;
   for(int ii=0; ii<cnt_treg; ii++) tempReadArray[ii] = 0;
  __LN_OUTPUT_LED *arr = (__LN_OUTPUT_LED*)(spca_of_p_prt[ID_FB_LED - _ID_FB_FIRST_VAR]);
   for(int item=0; item<sdismallcomponent->countObject; item++) {
   int ireg = item/16;
   int value = arr[item].active_state[OUTPUT_LED_OUT >> 3] & (1 << (OUTPUT_LED_OUT & ((1 << 3) - 1)));
   int sdidata = 0;
   if(value) sdidata=1;
   tempReadArray[ireg] |= sdidata<<(item%16);
  }//for
}//loadActualData() 

int getSDISmallModbusRegister(int adrReg)
{
  //получить содержимое регистра
  if(privateSDISmallGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(sdismallcomponent->isActiveActualData) loadSDISmallActualData(); //ActualData
  sdismallcomponent->isActiveActualData = 0;
  if(privateSDISmallGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;//MARKER_ERRORPERIMETR;

  superSetOperativMarker(sdismallcomponent, adrReg);

  return tempReadArray[adrReg-BEGIN_ADR_REGISTER];
}//getDVModbusRegister(int adrReg)
int getSDISmallModbusBit(int adrBit)
{
  //получить содержимое регистра
  if(privateSDISmallGetBit2(adrBit)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(sdismallcomponent->isActiveActualData) loadSDISmallActualData();
  sdismallcomponent->isActiveActualData = 0;
  if(privateSDISmallGetBit1(adrBit)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;//MARKER_ERRORPERIMETR;

  superSetOperativMarker(sdismallcomponent, adrBit);

  short tmp   = tempReadArray[(adrBit-BEGIN_ADR_BIT)/16];
  short maska = 1<<((adrBit-BEGIN_ADR_BIT)%16);
  if(tmp&maska) return 1;
  return 0;
}//getDVModbusBit(int adrReg)
int setSDISmallModbusRegister(int adrReg, int x)
{
  UNUSED(x);
  //записать содержимое регистра
  superSetOperativMarker(sdismallcomponent, adrReg);
  return MARKER_OUTPERIMETR;
}//getDVModbusRegister(int adrReg)
int setSDISmallModbusBit(int adrBit, int x)
{
  UNUSED(x);
  //получить содержимое регистра
  superSetOperativMarker(sdismallcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDVModbusRegister(int adrReg)

void setSDISmallCountObject(void) {
//записать к-во обектов
  int cntObj = current_config.n_led; //Кількість дискретних світлоіндикаторів
  if(cntObj<0) return;
  if(cntObj>TOTAL_OBJ) return;
  sdismallcomponent->countObject = cntObj;
}//
void preSDISmallReadAction(void) {
//action до чтения
  sdismallcomponent->operativMarker[0] = -1;
  sdismallcomponent->operativMarker[1] = -1;//оперативный маркер
  sdismallcomponent->isActiveActualData = 1;
}//
void postSDISmallReadAction(void) {
//action после чтения
  if(sdismallcomponent->operativMarker[0]<0) return;//не было чтения
}//
void preSDISmallWriteAction(void) {
//action до записи
  sdismallcomponent->operativMarker[0] = -1;
  sdismallcomponent->operativMarker[1] = -1;//оперативный маркер
  sdismallcomponent->isActiveActualData = 1;
}//
int postSDISmallWriteAction(void) {
//action после записи
 return 0;
}//

int privateSDISmallGetReg1(int adrReg)
{
  //проверить внутренний периметр
  int count_register = sdismallcomponent->countObject/16;
  if(sdismallcomponent->countObject%16) count_register++;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg1(int adrReg)

int privateSDISmallGetReg2(int adrReg)
{
  //проверить внешний периметр
  int count_register = TOTAL_OBJ/16;
  if(TOTAL_OBJ%16) count_register++;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)

int privateSDISmallGetBit1(int adrBit)
{
  //проверить внутренний периметр
  int count_bit = BIT_FOR_OBJ*sdismallcomponent->countObject;
  if(adrBit>=BEGIN_ADR_BIT && adrBit<(BEGIN_ADR_BIT+count_bit)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg1(int adrReg)

int privateSDISmallGetBit2(int adrBit)
{
  //проверить внешний периметр
  int count_bit = BIT_FOR_OBJ*TOTAL_OBJ;
  if(adrBit>=BEGIN_ADR_BIT && adrBit<(BEGIN_ADR_BIT+count_bit)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
