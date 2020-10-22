#include "header.h"

//начальный регистр в карте памяти
#define BEGIN_ADR_REGISTER 2275
//начальный bit в карте памяти
#define BEGIN_ADR_BIT 50000
#define BIT_FOR_OBJ 1

int privateTANDSmallGetReg2(int adrReg);
int privateTANDSmallGetBit2(int adrBit);

int getTANDSmallModbusRegister(int);//получить содержимое регистра
int getTANDSmallModbusBit(int);//получить содержимое бита
int setTANDSmallModbusRegister(int, int);//получить содержимое регистра
int setTANDSmallModbusBit(int, int);//получить содержимое бита

void setTANDSmallCountObject(void);//записать к-во обектов
void preTANDSmallReadAction(void);//action до чтения
void postTANDSmallReadAction(void);//action после чтения
void preTANDSmallWriteAction(void);//action до записи
int  postTANDSmallWriteAction(void);//action после записи
void loadTANDSmallActualData(void);
void config_and_settingsTANDSmall(void);//action активации

COMPONENT_OBJ *tandsmallcomponent;

/**************************************/
//подготовка компонента Технологический AND
/**************************************/
void constructorTANDSmallComponent(COMPONENT_OBJ *tandsmallcomp)
{
  tandsmallcomponent = tandsmallcomp;

  tandsmallcomponent->countObject = 128;//к-во обектов

  tandsmallcomponent->getModbusRegister = getTANDSmallModbusRegister;//получить содержимое регистра
  tandsmallcomponent->getModbusBit      = getTANDSmallModbusBit;//получить содержимое бита
  tandsmallcomponent->setModbusRegister = setTANDSmallModbusRegister;//получить содержимое регистра
  tandsmallcomponent->setModbusBit      = setTANDSmallModbusBit;//получить содержимое бита

  tandsmallcomponent->preReadAction   = preTANDSmallReadAction;//action до чтения
  tandsmallcomponent->postReadAction  = postTANDSmallReadAction;//action после чтения
  tandsmallcomponent->preWriteAction  = preTANDSmallWriteAction;//action до записи
  tandsmallcomponent->postWriteAction = postTANDSmallWriteAction;//action после записи
  tandsmallcomponent->config_and_settings = config_and_settingsTANDSmall;//action активации

  tandsmallcomponent->isActiveActualData = 0;
}//prepareDVinConfig

void loadTANDSmallActualData(void) {
  //ActualData
extern int pointInterface;//метка интерфейса 0-USB 1-RS485
   int cnt_treg = tandsmallcomponent->countObject/16;
   if(tandsmallcomponent->countObject%16) cnt_treg++;
   for(int ii=0; ii<cnt_treg; ii++) tempReadArray[ii] = 0;

   __LN_AND *arr = (__LN_AND*)(spca_of_p_prt[ID_FB_AND - _ID_FB_FIRST_VAR]);
   for(int item=0; item<tandsmallcomponent->countObject; item++) {
   int ireg = item/16;
   int value = arr[item].active_state[0];
   int tdata = 0;
   if(value) tdata=1;
   tempReadArray[ireg] |= tdata<<(item%16);
  }//for

}//loadTANDSmallActualData() 

int getTANDSmallModbusRegister(int adrReg)
{
  //получить содержимое регистра
  if(privateTANDSmallGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(tandsmallcomponent->isActiveActualData) loadTANDSmallActualData(); //ActualData
  tandsmallcomponent->isActiveActualData = 0;

  superSetOperativMarker(tandsmallcomponent, adrReg);

  return tempReadArray[adrReg-BEGIN_ADR_REGISTER];
}//getTANDSmallModbusRegister(int adrReg)
int getTANDSmallModbusBit(int adrBit)
{
  //получить содержимое bit
  if(privateTANDSmallGetBit2(adrBit)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(tandsmallcomponent->isActiveActualData) loadTANDSmallActualData();
  tandsmallcomponent->isActiveActualData = 0;

  superSetOperativMarker(tandsmallcomponent, adrBit);

  short tmp   = tempReadArray[(adrBit-BEGIN_ADR_BIT)/16];
  short maska = 1<<((adrBit-BEGIN_ADR_BIT)%16);
  if(tmp&maska) return 1;
  return 0;
}//getTANDSmallModbusBit(int adrReg)
int setTANDSmallModbusRegister(int x, int y)
{
  UNUSED(x);
  UNUSED(y);
  //записать содержимое регистра
  return MARKER_OUTPERIMETR;
}//setTANDSmallModbusRegister(int x, int y)
int setTANDSmallModbusBit(int x, int y)
{
  UNUSED(x);
  UNUSED(y);
  //получить содержимое регистра
  return MARKER_OUTPERIMETR;
}//setTANDSmallModbusBit(int x, int y)

void preTANDSmallReadAction(void) {
//action до чтения
  tandsmallcomponent->operativMarker[0] = -1;
  tandsmallcomponent->operativMarker[1] = -1;//оперативный маркер
  tandsmallcomponent->isActiveActualData = 1;
}//
void postTANDSmallReadAction(void) {
//action после чтения
  if(tandsmallcomponent->operativMarker[0]<0) return;//не было чтения
}//
void preTANDSmallWriteAction(void) {
//action до записи
  tandsmallcomponent->operativMarker[0] = -1;
  tandsmallcomponent->operativMarker[1] = -1;//оперативный маркер
  tandsmallcomponent->isActiveActualData = 1;
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

void config_and_settingsTANDSmall(void)
{
//action активации
}

