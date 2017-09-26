#include "header.h"

//начальный регистр в карте памяти
#define BEGIN_ADR_REGISTER 200
//начальный bit в карте памяти
#define BEGIN_ADR_BIT 18000
#define BIT_FOR_OBJ 1
//макс к-во обектов
#define TOTAL_OBJ 128
int privateTSSmallGetReg1(int adrReg);
int privateTSSmallGetReg2(int adrReg);
int privateTSSmallGetBit1(int adrBit);
int privateTSSmallGetBit2(int adrBit);

int getTSSmallModbusRegister(int);//получить содержимое регистра
int getTSSmallModbusBit(int);//получить содержимое бита
int setTSSmallModbusRegister(int, int);//получить содержимое регистра
int setTSSmallModbusBit(int, int);//получить содержимое бита

void setTSSmallCountObject(void);//записать к-во обектов
void preTSSmallReadAction(void);//action до чтения
void postTSSmallReadAction(void);//action после чтения
void preTSSmallWriteAction(void);//action до записи
int postTSSmallWriteAction(void);//action после записи
void loadTSSmallActualData(int beginOffset, int endOffset);
int getTSmallModbusBeginAdrRegister(void);
void config_and_settingsTSSmall(void);//action активации

COMPONENT_OBJ *tssmallcomponent;

int getTSmallModbusBeginAdrRegister(void)
{
  //получить адрес нач регистра
 return BEGIN_ADR_REGISTER;
}//getTSmallModbusBeginAdrRegister(void)

/**************************************/
//подготовка компонента телесигнализации
/**************************************/
void constructorTSSmallComponent(COMPONENT_OBJ *tssmallcomp)
{
  tssmallcomponent = tssmallcomp;

  tssmallcomponent->countObject = 0;//к-во обектов

  tssmallcomponent->getModbusRegister = getTSSmallModbusRegister;//получить содержимое регистра
  tssmallcomponent->getModbusBit      = getTSSmallModbusBit;//получить содержимое бита
  tssmallcomponent->setModbusRegister = setTSSmallModbusRegister;//получить содержимое регистра
  tssmallcomponent->setModbusBit      = setTSSmallModbusBit;//получить содержимое бита

  tssmallcomponent->preReadAction   = preTSSmallReadAction;//action до чтения
  tssmallcomponent->postReadAction  = postTSSmallReadAction;//action после чтения
  tssmallcomponent->preWriteAction  = preTSSmallWriteAction;//action до записи
  tssmallcomponent->postWriteAction = postTSSmallWriteAction;//action после записи
  tssmallcomponent->config_and_settings = config_and_settingsTSSmall;//action активации

  tssmallcomponent->isActiveActualData = 0;
}//prepareDVinConfig

void loadTSSmallActualData(int beginOffset, int endOffset) {
  //ActualData
//  setTSSmallCountObject(); //записать к-во обектов

  int cnt_treg = tssmallcomponent->countObject/16;
  if(tssmallcomponent->countObject%16) cnt_treg++;
  for(int ii=0; ii<cnt_treg; ii++) tempReadArray[ii] = 0;
   __LN_TS *arr = (__LN_TS*)(spca_of_p_prt[ID_FB_TS - _ID_FB_FIRST_VAR]);
  for(int item=0; item<tssmallcomponent->countObject; item++) {
   int ireg = item/16;

   int value =0;
   if(item>=beginOffset && item<endOffset) {
   //Встановлюємо MUTEX (1)
   arr[item].internal_input[TS_INT_MUTEX >> 3] |= (1 << (TS_INT_MUTEX & ((1 << 3) - 1)));
   
   //Чиатання стану
   value = arr[item].active_state[TS_OUT  >> 3] & (1 << (TS_OUT  & ((1 << 3) - 1)));

   //Встановлюємо про те що читання відбулося (2)
   arr[item].internal_input[TS_INT_READING >> 3] |= (1 << (TS_INT_READING & ((1 << 3) - 1)));


   //Скидаємо MUTEX (3)
   arr[item].internal_input[TS_INT_MUTEX >> 3] &= (uint8_t)(~(1 << (TS_INT_MUTEX & ((1 << 3) - 1))));
   }//if
   
   int tsdata = 0;
   if(value) tsdata=1;
   tempReadArray[ireg] |= (tsdata&0x1)<<(item%16);
  }//for
}//loadActualData() 

int getTSSmallModbusRegister(int adrReg)
{
  //получить содержимое регистра
//extern int cntBit;//к-во бит для чтения
extern int globalcntReg;//к-во регистров для чтения
extern int globalbeginAdrReg;
  if(privateTSSmallGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(tssmallcomponent->isActiveActualData) {
    setTSSmallCountObject(); //записать к-во обектов
    int begin = globalbeginAdrReg-BEGIN_ADR_REGISTER;
    if(begin<0) globalcntReg += begin;
    if(privateTSSmallGetReg1(adrReg+globalcntReg-1)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;
    int beginOffset = (adrReg-BEGIN_ADR_REGISTER)*16;
    int endOffset   = (adrReg-BEGIN_ADR_REGISTER +globalcntReg)*16;
    loadTSSmallActualData(beginOffset, endOffset);  //ActualData
  }//if
  tssmallcomponent->isActiveActualData = 0;

  return tempReadArray[adrReg-BEGIN_ADR_REGISTER];
}//getDVModbusRegister(int adrReg)
int getTSSmallModbusBit(int adrBit)
{
  //получить содержимое bit
extern int globalcntBit;//к-во бит для чтения
extern int globalbeginAdrBit;
  if(privateTSSmallGetBit2(adrBit)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(tssmallcomponent->isActiveActualData) {
    setTSSmallCountObject(); //записать к-во обектов
    int begin = globalbeginAdrBit-BEGIN_ADR_BIT;
    if(begin<0) globalcntBit += begin;
    if(privateTSSmallGetBit1(adrBit +globalcntBit-1)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;
    int beginOffset = adrBit-BEGIN_ADR_BIT;
    int endOffset   = adrBit-BEGIN_ADR_BIT +globalcntBit;
    loadTSSmallActualData(beginOffset, endOffset);  //ActualData
  }//if
  tssmallcomponent->isActiveActualData = 0;

  superSetOperativMarker(tssmallcomponent, adrBit);

  short tmp   = tempReadArray[(adrBit-BEGIN_ADR_BIT)/16];
  short maska = 1<<((adrBit-BEGIN_ADR_BIT)%16);
  if(tmp&maska) return 1;
  return 0;
}//getDVModbusRegister(int adrReg)
int setTSSmallModbusRegister(int x, int y)
{
  UNUSED(x);
  UNUSED(y);
  //записать содержимое регистра
  return MARKER_OUTPERIMETR;
}//getDVModbusRegister(int adrReg)
int setTSSmallModbusBit(int x, int y)
{
  UNUSED(x);
  UNUSED(y);
  //записать содержимое bit
  return MARKER_OUTPERIMETR;
}//getDVModbusRegister(int adrReg)

void setTSSmallCountObject(void) {
//записать к-во обектов
  int cntObj = current_config.n_ts;    //Кількість блоків сигналізацій
  if(cntObj<0) return;
  if(cntObj>TOTAL_OBJ) return;
  tssmallcomponent->countObject = cntObj;
}//
void preTSSmallReadAction(void) {
//action до чтения
  tssmallcomponent->operativMarker[0] = -1;
  tssmallcomponent->operativMarker[1] = -1;//оперативный маркер
  tssmallcomponent->isActiveActualData = 1;
}//
void postTSSmallReadAction(void) {
//action после чтения
  if(tssmallcomponent->operativMarker[0]<0) return;//не было чтения
}//
void preTSSmallWriteAction(void) {
//action до записи
  tssmallcomponent->operativMarker[0] = -1;
  tssmallcomponent->operativMarker[1] = -1;//оперативный маркер
  tssmallcomponent->isActiveActualData = 1;
}//
int postTSSmallWriteAction(void) {
//action после записи
  return 0;
}//

int privateTSSmallGetReg1(int adrReg)
{
  //проверить внутренний периметр
  int count_register = tssmallcomponent->countObject/16;
  if(tssmallcomponent->countObject%16) count_register++;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg1(int adrReg)

int privateTSSmallGetReg2(int adrReg)
{
  //проверить внешний периметр
  int count_register = TOTAL_OBJ/16;
  if(TOTAL_OBJ%16) count_register++;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)

int privateTSSmallGetBit1(int adrBit)
{
  //проверить внутренний периметр
  int count_bit = BIT_FOR_OBJ*tssmallcomponent->countObject;
  if(adrBit>=BEGIN_ADR_BIT && adrBit<(BEGIN_ADR_BIT+count_bit)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg1(int adrReg)

int privateTSSmallGetBit2(int adrBit)
{
  //проверить внешний периметр
  int count_bit = BIT_FOR_OBJ*TOTAL_OBJ;
  if(adrBit>=BEGIN_ADR_BIT && adrBit<(BEGIN_ADR_BIT+count_bit)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)

void config_and_settingsTSSmall(void)
{
//action активации
}

