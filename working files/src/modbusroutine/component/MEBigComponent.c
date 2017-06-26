#include "header.h"

//начальный регистр в карте памяти
#define BEGIN_ADR_REGISTER 15000
//макс к-во обектов
#define REGISTER_FOR_OBJ 2
//макс к-во обектов
#define TOTAL_OBJ 128

int privateMEBigGetReg1(int adrReg);
int privateMEBigGetReg2(int adrReg);

int getMEBigModbusRegister(int);//получить содержимое регистра
int getMEBigModbusBit(int);//получить содержимое бита
int setMEBigModbusRegister(int, int);//получить содержимое регистра
int setMEBigModbusBit(int, int);//получить содержимое бита

void setMEBigCountObject(void);
void preMEBigReadAction(void);//action до чтения
void postMEBigReadAction(void);//action после чтения
void preMEBigWriteAction(void);//action до записи
void postMEBigWriteAction(void);//action после записи
void loadMEBigActualData(void);

COMPONENT_OBJ *mebigcomponent;

/**************************************/
//подготовка компонента журнал событий
/**************************************/
void constructorMEBigComponent(COMPONENT_OBJ *mebigcomp)
{
  mebigcomponent = mebigcomp;

  mebigcomponent->countObject = 0;//к-во обектов

  mebigcomponent->getModbusRegister = getMEBigModbusRegister;//получить содержимое регистра
  mebigcomponent->getModbusBit      = getMEBigModbusBit;//получить содержимое регистра
  mebigcomponent->setModbusRegister = setMEBigModbusRegister;//получить содержимое регистра
  mebigcomponent->setModbusBit      = setMEBigModbusBit;//получить содержимое регистра

  mebigcomponent->preReadAction   = preMEBigReadAction;//action до чтения
  mebigcomponent->postReadAction  = postMEBigReadAction;//action после чтения
  mebigcomponent->preWriteAction  = preMEBigWriteAction;//action до записи
  mebigcomponent->postWriteAction = postMEBigWriteAction;//action после записи

  mebigcomponent->isActiveActualData = 0;
}//prepareDVinConfig

void loadMEBigActualData(void) {
 setMEBigCountObject(); //записать к-во обектов
  //ActualData
//   __LN_AND *arr = (__LN_AND*)(spca_of_p_prt[ID_FB_INPUT - _ID_FB_FIRST_VAR]);
   //Очистить журнал 0
   int value = 0;//arr[item].settings.param[0];
   tempReadArray[0] = value;
   //Очистить журнал 1
   value = 0;//arr[item].settings.param[1];
   tempReadArray[1] = value;

   for(int item=0; item<mebigcomponent->countObject; item++) {
   //Вход item 0
   value = 0;//arr[item].settings.param[0];
   tempReadArray[2+item*REGISTER_FOR_OBJ+0] = value;
   //Вход item 1
   value = 0;//arr[item].settings.param[1];
   tempReadArray[2+item*REGISTER_FOR_OBJ+1] = value;
  }//for
}//loadActualData() 

int getMEBigModbusRegister(int adrReg)
{
  //получить содержимое регистра
  if(privateMEBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(mebigcomponent->isActiveActualData) loadMEBigActualData(); //ActualData
  mebigcomponent->isActiveActualData = 0;
  if(privateMEBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  superSetOperativMarker(mebigcomponent, adrReg);

  return tempReadArray[adrReg-BEGIN_ADR_REGISTER];
}//getDOUTBigModbusRegister(int adrReg)
int getMEBigModbusBit(int adrBit)
{
  //получить содержимое регистра
  superSetOperativMarker(mebigcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void setMEBigCountObject(void) {
//записать к-во обектов
  int cntObj = current_config.n_log;    //Кількість субмодулів Журналу подій
  if(cntObj<0) return;
  if(cntObj>TOTAL_OBJ) return;
  mebigcomponent->countObject = cntObj;
}//
int setMEBigModbusRegister(int adrReg, int dataReg)
{
  //записать содержимое регистра
  if(privateMEBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  superSetOperativMarker(mebigcomponent, adrReg);
  superSetTempWriteArray(dataReg);//записать в буфер

  return 0;
}//getDOUTBigModbusRegister(int adrReg)
int setMEBigModbusBit(int adrBit, int x)
{
  UNUSED(x);
  //получить содержимое регистра
  superSetOperativMarker(mebigcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void preMEBigReadAction(void) {
//action до чтения
  mebigcomponent->operativMarker[0] = -1;
  mebigcomponent->operativMarker[1] = -1;//оперативный маркер
  mebigcomponent->isActiveActualData = 1;
}//
void postMEBigReadAction(void) {
//action после чтения
  if(mebigcomponent->operativMarker[0]<0) return;//не было чтения
}//
void preMEBigWriteAction(void) {
//action до записи
  mebigcomponent->operativMarker[0] = -1;
  mebigcomponent->operativMarker[1] = -1;//оперативный маркер
  mebigcomponent->isActiveActualData = 1;
}//
void postMEBigWriteAction(void) {
//action после записи
  if(mebigcomponent->operativMarker[0]<0) return;//не было записи
//  int offset = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//найти смещение TempWriteArray
//  int countRegister = mebigcomponent->operativMarker[1]-mebigcomponent->operativMarker[0]+1;
//  if(mebigcomponent->operativMarker[1]<0) countRegister = 1;
}//

int privateMEBigGetReg1(int adrReg)
{
  //проверить внутренний периметр
  int count_register = 2+mebigcomponent->countObject*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
int privateMEBigGetReg2(int adrReg)
{
  //проверить внешний периметр
  int count_register = 2+TOTAL_OBJ*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
