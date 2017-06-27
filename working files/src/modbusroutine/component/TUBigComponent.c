#include "header.h"

//начальный регистр в карте пам€ти
#define BEGIN_ADR_REGISTER 8533
//макс к-во обектов
#define TOTAL_OBJ 128
#define REGISTER_FOR_OBJ 3

int privateTUBigGetReg1(int adrReg);
int privateTUBigGetReg2(int adrReg);

int getTUBigModbusRegister(int);//получить содержимое регистра
int getTUBigModbusBit(int);//получить содержимое бита
int setTUBigModbusRegister(int, int);//получить содержимое регистра
int setTUBigModbusBit(int, int);//получить содержимое бита

void setTUBigCountObject(void);//записать к-во обектов
void preTUBigReadAction(void);//action до чтени€
void postTUBigReadAction(void);//action после чтени€
void preTUBigWriteAction(void);//action до записи
void postTUBigWriteAction(void);//action после записи
void loadTUBigActualData(void);

COMPONENT_OBJ *tubigcomponent;

/**************************************/
//подготовка компонента телеуправление
/**************************************/
void constructorTUBigComponent(COMPONENT_OBJ *tubigcomp)
{
  tubigcomponent = tubigcomp;

  tubigcomponent->countObject = 0;//к-во обектов

  tubigcomponent->getModbusRegister = getTUBigModbusRegister;//получить содержимое регистра
  tubigcomponent->getModbusBit      = getTUBigModbusBit;//получить содержимое бита
  tubigcomponent->setModbusRegister = setTUBigModbusRegister;//получить содержимое регистра
  tubigcomponent->setModbusBit      = setTUBigModbusBit;//получить содержимое бита

  tubigcomponent->preReadAction   = preTUBigReadAction;//action до чтени€
  tubigcomponent->postReadAction  = postTUBigReadAction;//action после чтени€
  tubigcomponent->preWriteAction  = preTUBigWriteAction;//action до записи
  tubigcomponent->postWriteAction = postTUBigWriteAction;//action после записи

  tubigcomponent->isActiveActualData = 0;
}//prepareDVinConfig

void loadTUBigActualData(void) {
 setTUBigCountObject(); //записать к-во обектов

  //ActualData
   __LN_TU *arr = (__LN_TU*)(spca_of_p_prt[ID_FB_TU - _ID_FB_FIRST_VAR]);
   for(int item=0; item<tubigcomponent->countObject; item++) {

   //Block “” 0  item
   int value = arr[item].settings.param[TU_BLOCK] & 0xffff;//LEDIN 0 —ƒ item
   tempReadArray[item*REGISTER_FOR_OBJ+0] = value;
   value = (arr[item].settings.param[TU_BLOCK] >> 16) & 0x7fff;//LEDIN 1 —ƒ item
   tempReadArray[item*REGISTER_FOR_OBJ+1] = value;

   //јдрес “” 0  item
//   value = arr[item].settings.param[0];
   value = 18128 + item;
   tempReadArray[item*REGISTER_FOR_OBJ+2] = value;
   }//for
}//loadActualData() 

int getTUBigModbusRegister(int adrReg)
{
  //получить содержимое регистра
  if(privateTUBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(tubigcomponent->isActiveActualData) loadTUBigActualData(); //ActualData
  tubigcomponent->isActiveActualData = 0;
  if(privateTUBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  superSetOperativMarker(tubigcomponent, adrReg);

  return tempReadArray[adrReg-BEGIN_ADR_REGISTER];
}//getDOUTBigModbusRegister(int adrReg)
int getTUBigModbusBit(int adrBit)
{
  //получить содержимое регистра
  superSetOperativMarker(tubigcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setTUBigModbusRegister(int adrReg, int dataReg)
{
  //записать содержимое регистра
  if(privateTUBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(privateTUBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  superSetOperativMarker(tubigcomponent, adrReg);
  superSetTempWriteArray(dataReg);//записать в буфер

  switch((adrReg-BEGIN_ADR_REGISTER)%REGISTER_FOR_OBJ) {
   case 0:
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
   break; 
   case 1:
   break; 
   case 2:
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
   break; 
   case 3:
   break; 
  default: return MARKER_OUTPERIMETR;
  }//switch
  return 0;
}//getDOUTBigModbusRegister(int adrReg)
int setTUBigModbusBit(int adrBit, int x)
{
  UNUSED(x);
  //получить содержимое регистра
  superSetOperativMarker(tubigcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void setTUBigCountObject(void) {
//записать к-во обектов
  int cntObj = current_config.n_tu;    // ≥льк≥сть блок≥в сигнал≥зац≥й
  if(cntObj<0) return;
  if(cntObj>TOTAL_OBJ) return;
  tubigcomponent->countObject = cntObj;
}//
void preTUBigReadAction(void) {
//action до чтени€
  tubigcomponent->operativMarker[0] = -1;
  tubigcomponent->operativMarker[1] = -1;//оперативный маркер
  tubigcomponent->isActiveActualData = 1;
}//
void postTUBigReadAction(void) {
//action после чтени€
  if(tubigcomponent->operativMarker[0]<0) return;//не было чтени€
}//
void preTUBigWriteAction(void) {
//action до записи
  tubigcomponent->operativMarker[0] = -1;
  tubigcomponent->operativMarker[1] = -1;//оперативный маркер
  tubigcomponent->isActiveActualData = 1;
}//
void postTUBigWriteAction(void) {
//action после записи
  if(tubigcomponent->operativMarker[0]<0) return;//не было записи
//  int offset = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//найти смещение TempWriteArray
//  int countRegister = tubigcomponent->operativMarker[1]-tubigcomponent->operativMarker[0]+1;
//  if(tubigcomponent->operativMarker[1]<0) countRegister = 1;
}//

int privateTUBigGetReg1(int adrReg)
{
  //проверить внутренний периметр
  int count_register = tubigcomponent->countObject*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg1(int adrReg)
int privateTUBigGetReg2(int adrReg)
{
  //проверить внешний периметр
  int count_register = TOTAL_OBJ*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
