#include "header.h"

//начальный регистр в карте памяти
#define BEGIN_ADR_REGISTER 2282
//начальный bit в карте памяти
#define BEGIN_ADR_BIT 50128
#define BIT_FOR_OBJ 1

int privateTORSmallGetReg2(int adrReg);
int privateTORSmallGetBit2(int adrBit);

int getTORSmallModbusRegister(int);//получить содержимое регистра
int getTORSmallModbusBit(int);//получить содержимое бита
int setTORSmallModbusRegister(int, int);//получить содержимое регистра
int setTORSmallModbusBit(int, int);//получить содержимое бита

void setTORSmallCountObject(void);//записать к-во обектов
void preTORSmallReadAction(void);//action до чтения
void postTORSmallReadAction(void);//action после чтения
void preTORSmallWriteAction(void);//action до записи
int  postTORSmallWriteAction(void);//action после записи
void loadTORSmallActualData(void);
void config_and_settingsTORSmall(void);//action активации

COMPONENT_OBJ *torsmallcomponent;

/**************************************/
//подготовка компонента Технологический OR
/**************************************/
void constructorTORSmallComponent(COMPONENT_OBJ *torsmallcomp)
{
  torsmallcomponent = torsmallcomp;

  torsmallcomponent->countObject = 128;//к-во обектов

  torsmallcomponent->getModbusRegister = getTORSmallModbusRegister;//получить содержимое регистра
  torsmallcomponent->getModbusBit      = getTORSmallModbusBit;//получить содержимое бита
  torsmallcomponent->setModbusRegister = setTORSmallModbusRegister;//получить содержимое регистра
  torsmallcomponent->setModbusBit      = setTORSmallModbusBit;//получить содержимое бита

  torsmallcomponent->preReadAction   = preTORSmallReadAction;//action до чтения
  torsmallcomponent->postReadAction  = postTORSmallReadAction;//action после чтения
  torsmallcomponent->preWriteAction  = preTORSmallWriteAction;//action до записи
  torsmallcomponent->postWriteAction = postTORSmallWriteAction;//action после записи
  torsmallcomponent->config_and_settings = config_and_settingsTORSmall;//action активации

  torsmallcomponent->isActiveActualData = 0;
}//prepareDVinConfig

void loadTORSmallActualData(void) {
  //ActualData
extern int pointInterface;//метка интерфейса 0-USB 1-RS485
   int cnt_treg = torsmallcomponent->countObject/16;
   if(torsmallcomponent->countObject%16) cnt_treg++;
   for(int ii=0; ii<cnt_treg; ii++) tempReadArray[ii] = 0;

   __LN_OR *arr = (__LN_OR*)(spca_of_p_prt[ID_FB_OR - _ID_FB_FIRST_VAR]);
   for(int item=0; item<torsmallcomponent->countObject; item++) {
   int ireg = item/16;
   int value = arr[item].active_state[0];
   int tdata = 0;
   if(value) tdata=1;
   tempReadArray[ireg] |= tdata<<(item%16);
  }//for

}//loadTORSmallActualData() 

int getTORSmallModbusRegister(int adrReg)
{
  //получить содержимое регистра
  if(privateTORSmallGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(torsmallcomponent->isActiveActualData) loadTORSmallActualData(); //ActualData
  torsmallcomponent->isActiveActualData = 0;

  superSetOperativMarker(torsmallcomponent, adrReg);

  return tempReadArray[adrReg-BEGIN_ADR_REGISTER];
}//getTORSmallModbusRegister(int adrReg)
int getTORSmallModbusBit(int adrBit)
{
  //получить содержимое bit
  if(privateTORSmallGetBit2(adrBit)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(torsmallcomponent->isActiveActualData) loadTORSmallActualData();
  torsmallcomponent->isActiveActualData = 0;

  superSetOperativMarker(torsmallcomponent, adrBit);

  short tmp   = tempReadArray[(adrBit-BEGIN_ADR_BIT)/16];
  short maska = 1<<((adrBit-BEGIN_ADR_BIT)%16);
  if(tmp&maska) return 1;
  return 0;
}//getTORSmallModbusBit(int adrReg)
int setTORSmallModbusRegister(int x, int y)
{
  UNUSED(x);
  UNUSED(y);
  //записать содержимое регистра
  return MARKER_OUTPERIMETR;
}//setTORSmallModbusRegister(int x, int y)
int setTORSmallModbusBit(int x, int y)
{
  UNUSED(x);
  UNUSED(y);
  //получить содержимое регистра
  return MARKER_OUTPERIMETR;
}//setTORSmallModbusBit(int x, int y)

void preTORSmallReadAction(void) {
//action до чтения
  torsmallcomponent->operativMarker[0] = -1;
  torsmallcomponent->operativMarker[1] = -1;//оперативный маркер
  torsmallcomponent->isActiveActualData = 1;
}//
void postTORSmallReadAction(void) {
//action после чтения
  if(torsmallcomponent->operativMarker[0]<0) return;//не было чтения
}//
void preTORSmallWriteAction(void) {
//action до записи
  torsmallcomponent->operativMarker[0] = -1;
  torsmallcomponent->operativMarker[1] = -1;//оперативный маркер
  torsmallcomponent->isActiveActualData = 1;
}//
int postTORSmallWriteAction(void) {
//action после записи
 return 0;
}//

int privateTORSmallGetReg2(int adrReg)
{
  //проверить внешний периметр
  int count_register = TOTAL_OBJ/16;
  if(TOTAL_OBJ%16) count_register++;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)

int privateTORSmallGetBit2(int adrBit)
{
  //проверить внешний периметр
  int count_bit = BIT_FOR_OBJ*TOTAL_OBJ;
  if(adrBit>=BEGIN_ADR_BIT && adrBit<(BEGIN_ADR_BIT+count_bit)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)

void config_and_settingsTORSmall(void)
{
//action активации
}

