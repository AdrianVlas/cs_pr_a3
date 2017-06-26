#include "header.h"

//начальный регистр в карте памяти
#define BEGIN_ADR_REGISTER 6107
//макс к-во обектов
#define TOTAL_OBJ 128
#define REGISTER_FOR_OBJ 6

int privateMFTBigGetReg1(int adrReg);
int privateMFTBigGetReg2(int adrReg);

int getMFTBigModbusRegister(int);//получить содержимое регистра
int getMFTBigModbusBit(int);//получить содержимое бита
int setMFTBigModbusRegister(int, int);//получить содержимое регистра
int setMFTBigModbusBit(int, int);//получить содержимое бита

void setMFTBigCountObject(void);//записать к-во обектов
void preMFTBigReadAction(void);//action до чтения
void postMFTBigReadAction(void);//action после чтения
void preMFTBigWriteAction(void);//action до записи
void postMFTBigWriteAction(void);//action после записи
void loadMFTBigActualData(void);

COMPONENT_OBJ *mftbigcomponent;

/**************************************/
//подготовка компонента МФТ
/**************************************/
void constructorMFTBigComponent(COMPONENT_OBJ *mftbigcomp)
{
  mftbigcomponent = mftbigcomp;

  mftbigcomponent->countObject = 0;//к-во обектов

  mftbigcomponent->getModbusRegister = getMFTBigModbusRegister;//получить содержимое регистра
  mftbigcomponent->getModbusBit      = getMFTBigModbusBit;//получить содержимое бита
  mftbigcomponent->setModbusRegister = setMFTBigModbusRegister;//получить содержимое регистра
  mftbigcomponent->setModbusBit      = setMFTBigModbusBit;//получить содержимое бита

  mftbigcomponent->preReadAction   = preMFTBigReadAction;//action до чтения
  mftbigcomponent->postReadAction  = postMFTBigReadAction;//action после чтения
  mftbigcomponent->preWriteAction  = preMFTBigWriteAction;//action до записи
  mftbigcomponent->postWriteAction = postMFTBigWriteAction;//action после записи

  mftbigcomponent->isActiveActualData = 0;
}//prepareDVinConfig

void loadMFTBigActualData(void) {
 setMFTBigCountObject(); //записать к-во обектов
  //ActualData
   __LN_TIMER *arr = (__LN_TIMER*)(spca_of_p_prt[ID_FB_INPUT - _ID_FB_FIRST_VAR]);
   for(int item=0; item<mftbigcomponent->countObject; item++) {

   //Таймер паузы  item
   int value = arr[item].settings.set_delay[0];
   tempReadArray[item*REGISTER_FOR_OBJ+0] = value;

   //Таймер работы   item
   value = arr[item].settings.set_delay[1];
   tempReadArray[item*REGISTER_FOR_OBJ+1] = value;

   //MFT-IN 1 0 item
   value = arr[item].settings.param[0];
   tempReadArray[item*REGISTER_FOR_OBJ+2] = value;
   //MFT-IN 1 1 item
   value = arr[item].settings.param[1];
   tempReadArray[item*REGISTER_FOR_OBJ+3] = value;

   //Reset-I  0 item
   value = arr[item].settings.param[0];
   tempReadArray[item*REGISTER_FOR_OBJ+4] = value;
   //Reset-I  1 item
   value = arr[item].settings.param[0];
   tempReadArray[item*REGISTER_FOR_OBJ+5] = value;
   }//for

}//loadActualData() 

int getMFTBigModbusRegister(int adrReg)
{
  //получить содержимое регистра
  if(privateMFTBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(mftbigcomponent->isActiveActualData) loadMFTBigActualData(); //ActualData
  mftbigcomponent->isActiveActualData = 0;
  if(privateMFTBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  superSetOperativMarker(mftbigcomponent, adrReg);

  return tempReadArray[adrReg-BEGIN_ADR_REGISTER];
}//getDOUTBigModbusRegister(int adrReg)
int getMFTBigModbusBit(int adrBit)
{
  //получить содержимое регистра
  superSetOperativMarker(mftbigcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setMFTBigModbusRegister(int adrReg, int dataReg)
{
  //записать содержимое регистра
  if(privateMFTBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(privateMFTBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  superSetOperativMarker(mftbigcomponent, adrReg);
  superSetTempWriteArray(dataReg);//записать в буфер

  switch((adrReg-BEGIN_ADR_REGISTER)%REGISTER_FOR_OBJ) {
   case 0:
    if(dataReg>60000) return MARKER_ERRORDIAPAZON;
   break; 
   case 1:
    if(dataReg>60000) return MARKER_ERRORDIAPAZON;
   break; 
   case 2:
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
   break; 
   case 3:
   break; 
   case 4:
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
   break; 
   case 5:
   break; 
  default: return MARKER_OUTPERIMETR;
  }//switch
  return 0;
}//getDOUTBigModbusRegister(int adrReg)
int setMFTBigModbusBit(int adrBit, int x)
{
  UNUSED(x);
  //получить содержимое регистра
  superSetOperativMarker(mftbigcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void setMFTBigCountObject(void) {
//записать к-во обектов
  int cntObj = current_config.n_timer;   //Кількість таймерів
  if(cntObj<0) return;
  if(cntObj>TOTAL_OBJ) return;
  mftbigcomponent->countObject = cntObj;
}//
void preMFTBigReadAction(void) {
//action до чтения
  mftbigcomponent->operativMarker[0] = -1;
  mftbigcomponent->operativMarker[1] = -1;//оперативный маркер
  mftbigcomponent->isActiveActualData = 1;
}//
void postMFTBigReadAction(void) {
//action после чтения
  if(mftbigcomponent->operativMarker[0]<0) return;//не было чтения
}//
void preMFTBigWriteAction(void) {
//action до записи
  mftbigcomponent->operativMarker[0] = -1;
  mftbigcomponent->operativMarker[1] = -1;//оперативный маркер
  mftbigcomponent->isActiveActualData = 1;
}//
void postMFTBigWriteAction(void) {
//action после записи
  if(mftbigcomponent->operativMarker[0]<0) return;//не было записи
//  int offset = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//найти смещение TempWriteArray
//  int countRegister = mftbigcomponent->operativMarker[1]-mftbigcomponent->operativMarker[0]+1;
//  if(mftbigcomponent->operativMarker[1]<0) countRegister = 1;
}//

int privateMFTBigGetReg1(int adrReg)
{
  //проверить внутренний периметр
  int count_register = mftbigcomponent->countObject*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg1(int adrReg)
int privateMFTBigGetReg2(int adrReg)
{
  //проверить внешний периметр
  int count_register = TOTAL_OBJ*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
