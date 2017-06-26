#include "header.h"

//начальный регистр в карте памяти
#define BEGIN_ADR_REGISTER 13013
//макс к-во обектов
#define TOTAL_OBJ 128
#define REGISTER_FOR_OBJ 4

int privateXORBigGetReg1(int adrReg);
int privateXORBigGetReg2(int adrReg);

int getXORBigModbusRegister(int);//получить содержимое регистра
int getXORBigModbusBit(int);//получить содержимое бита
int setXORBigModbusRegister(int, int);//получить содержимое регистра
int setXORBigModbusBit(int, int);//получить содержимое бита

void setXORBigCountObject(void);//записать к-во обектов
void preXORBigReadAction(void);//action до чтения
void postXORBigReadAction(void);//action после чтения
void preXORBigWriteAction(void);//action до записи
void postXORBigWriteAction(void);//action после записи
void loadXORBigActualData(void);

COMPONENT_OBJ *xorbigcomponent;

/**************************************/
//подготовка компонента XOR
/**************************************/
void constructorXORBigComponent(COMPONENT_OBJ *xorbigcomp)
{
  xorbigcomponent = xorbigcomp;

  xorbigcomponent->countObject = 0;//к-во обектов

  xorbigcomponent->getModbusRegister = getXORBigModbusRegister;//получить содержимое регистра
  xorbigcomponent->getModbusBit      = getXORBigModbusBit;//получить содержимое бита
  xorbigcomponent->setModbusRegister = setXORBigModbusRegister;//получить содержимое регистра
  xorbigcomponent->setModbusBit      = setXORBigModbusBit;//получить содержимое бита

  xorbigcomponent->preReadAction   = preXORBigReadAction;//action до чтения
  xorbigcomponent->postReadAction  = postXORBigReadAction;//action после чтения
  xorbigcomponent->preWriteAction  = preXORBigWriteAction;//action до записи
  xorbigcomponent->postWriteAction = postXORBigWriteAction;//action после записи

  xorbigcomponent->isActiveActualData = 0;
}//prepareDVinConfig

void loadXORBigActualData(void) {
 setXORBigCountObject(); //записать к-во обектов
  //ActualData
   __LN_XOR *arr = (__LN_XOR*)(spca_of_p_prt[ID_FB_INPUT - _ID_FB_FIRST_VAR]);
   for(int item=0; item<xorbigcomponent->countObject; item++) {
   //XOR item.1 0
   int value = arr[item].settings.param[0];
   tempReadArray[item*REGISTER_FOR_OBJ+0] = value;
   //XOR item.1 1
   value = arr[item].settings.param[1];
   tempReadArray[item*REGISTER_FOR_OBJ+1] = value;

   //XOR item.2 0
   value = arr[item].settings.param[0];
   tempReadArray[item*REGISTER_FOR_OBJ+2] = value;
   //XOR item.2 1
   value = arr[item].settings.param[1];
   tempReadArray[item*REGISTER_FOR_OBJ+3] = value;

   }//for
}//loadActualData() 

int getXORBigModbusRegister(int adrReg)
{
  //получить содержимое регистра
  if(privateXORBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(xorbigcomponent->isActiveActualData) loadXORBigActualData(); //ActualData
  xorbigcomponent->isActiveActualData = 0;
  if(privateXORBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  superSetOperativMarker(xorbigcomponent, adrReg);

  return tempReadArray[adrReg-BEGIN_ADR_REGISTER];
}//getDOUTBigModbusRegister(int adrReg)
int getXORBigModbusBit(int adrBit)
{
  //получить содержимое регистра
  superSetOperativMarker(xorbigcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setXORBigModbusRegister(int adrReg, int dataReg)
{
  //записать содержимое регистра
  if(privateXORBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(privateXORBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  superSetOperativMarker(xorbigcomponent, adrReg);
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
int setXORBigModbusBit(int adrBit, int x)
{
  UNUSED(x);
  //записать содержимое bit
  superSetOperativMarker(xorbigcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void setXORBigCountObject(void) {
//записать к-во обектов
  int cntObj = current_config.n_xor;  //Кількість елементів "Викл.АБО"
  if(cntObj<0) return;
  if(cntObj>TOTAL_OBJ) return;
  xorbigcomponent->countObject = cntObj;
}//
void preXORBigReadAction(void) {
//action до чтения
  xorbigcomponent->operativMarker[0] = -1;
  xorbigcomponent->operativMarker[1] = -1;//оперативный маркер
  xorbigcomponent->isActiveActualData = 1;
}//
void postXORBigReadAction(void) {
//action после чтения
  if(xorbigcomponent->operativMarker[0]<0) return;//не было чтения
}//
void preXORBigWriteAction(void) {
//action до записи
  xorbigcomponent->operativMarker[0] = -1;
  xorbigcomponent->operativMarker[1] = -1;//оперативный маркер
  xorbigcomponent->isActiveActualData = 1;
}//
void postXORBigWriteAction(void) {
//action после записи
  if(xorbigcomponent->operativMarker[0]<0) return;//не было записи
//  int offset = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//найти смещение TempWriteArray
//  int countRegister = xorbigcomponent->operativMarker[1]-xorbigcomponent->operativMarker[0]+1;
//  if(xorbigcomponent->operativMarker[1]<0) countRegister = 1;
}//

int privateXORBigGetReg1(int adrReg)
{
  //проверить внутренний периметр
  int count_register = xorbigcomponent->countObject*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg1(int adrReg)
int privateXORBigGetReg2(int adrReg)
{
  //проверить внешний периметр
  int count_register = TOTAL_OBJ*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
