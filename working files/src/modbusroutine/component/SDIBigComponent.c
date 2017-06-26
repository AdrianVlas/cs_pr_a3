#include "header.h"

//начальный регистр в карте памяти
#define BEGIN_ADR_REGISTER 3000
//макс к-во обектов
#define TOTAL_OBJ 128
#define REGISTER_FOR_OBJ 13

int privateSDIBigGetReg1(int adrReg);
int privateSDIBigGetReg2(int adrReg);

int getSDIBigModbusRegister(int);//получить содержимое регистра
int getSDIBigModbusBit(int);//получить содержимое бита
int setSDIBigModbusRegister(int, int);//получить содержимое регистра
int setSDIBigModbusBit(int, int);//получить содержимое бита

void setSDIBigCountObject(void);//записать к-во обектов
void preSDIBigReadAction(void);//action до чтения
void postSDIBigReadAction(void);//action после чтения
void preSDIBigWriteAction(void);//action до записи
void postSDIBigWriteAction(void);//action после записи
void loadSDIBigActualData(void);

COMPONENT_OBJ *sdibigcomponent;

/**************************************/
//подготовка компонента светоиндикаторов
/**************************************/
void constructorSDIBigComponent(COMPONENT_OBJ *sdibigcomp)
{
  sdibigcomponent = sdibigcomp;

  sdibigcomponent->countObject = 0;//к-во обектов

  sdibigcomponent->getModbusRegister = getSDIBigModbusRegister;//получить содержимое регистра
  sdibigcomponent->getModbusBit      = getSDIBigModbusBit;//получить содержимое бита
  sdibigcomponent->setModbusRegister = setSDIBigModbusRegister;//получить содержимое регистра
  sdibigcomponent->setModbusBit      = setSDIBigModbusBit;//получить содержимое бита

  sdibigcomponent->preReadAction   = preSDIBigReadAction;//action до чтения
  sdibigcomponent->postReadAction  = postSDIBigReadAction;//action после чтения
  sdibigcomponent->preWriteAction  = preSDIBigWriteAction;//action до записи
  sdibigcomponent->postWriteAction = postSDIBigWriteAction;//action после записи

  sdibigcomponent->isActiveActualData = 0;
}//prepareDVinConfig

void loadSDIBigActualData(void) {
 setSDIBigCountObject(); //записать к-во обектов

  //ActualData
  __LN_OUTPUT_LED *arr = (__LN_OUTPUT_LED*)(spca_of_p_prt[ID_FB_LED - _ID_FB_FIRST_VAR]);
   for(int item=0; item<sdibigcomponent->countObject; item++) {
   int value = arr[item].settings.control;//Параметры СД item
   tempReadArray[item*REGISTER_FOR_OBJ+0] = value;

   value = arr[item].settings.param[OUTPUT_LED_LOGIC_INPUT] & 0xffff;//RIN0 ДВых. item
   tempReadArray[item*REGISTER_FOR_OBJ+1] = value;
   value = (arr[item].settings.param[OUTPUT_LED_LOGIC_INPUT] >> 16) & 0x7fff;//RIN1 ДВых. item
   tempReadArray[item*REGISTER_FOR_OBJ+2] = value;

   value = arr[item].settings.param[OUTPUT_LED_RESET] & 0xffff;//Reset0 ДВых. item
   tempReadArray[item*REGISTER_FOR_OBJ+3] = value;
   value = (arr[item].settings.param[OUTPUT_LED_RESET] >> 16) & 0x7fff;//Reset1 ДВых. item
   tempReadArray[item*REGISTER_FOR_OBJ+4] = value;

   value = arr[item].settings.param[OUTPUT_LED_BL_IMP] & 0xffff;//BL-IMP0 ДВых. item
   tempReadArray[item*REGISTER_FOR_OBJ+5] = value;
   value = (arr[item].settings.param[OUTPUT_LED_BL_IMP] >> 16) & 0x7fff;//BL-IMP1 ДВых. item
   tempReadArray[item*REGISTER_FOR_OBJ+6] = value;

   value = arr[item].settings.param[OUTPUT_LED_MEANDER1] & 0xffff;//C1/C2 0 ДВых. item
   tempReadArray[item*REGISTER_FOR_OBJ+7] = value;
   value = (arr[item].settings.param[OUTPUT_LED_MEANDER1] >> 16) & 0x7fff;//C1/C2 1 ДВых item
   tempReadArray[item*REGISTER_FOR_OBJ+8] = value;

   value = arr[item].settings.param[OUTPUT_LED_MEANDER2] & 0xffff;//Генератор С1 0 Имп.ДВых item
   tempReadArray[item*REGISTER_FOR_OBJ+9] = value;
   value = (arr[item].settings.param[OUTPUT_LED_MEANDER2] >> 16) & 0x7fff;//Генератор С1 1 Имп.ДВых. item
   tempReadArray[item*REGISTER_FOR_OBJ+10] = value;
  }//for
}//loadActualData() 

int getSDIBigModbusRegister(int adrReg)
{
  //получить содержимое регистра
  if(privateSDIBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(sdibigcomponent->isActiveActualData) loadSDIBigActualData(); //ActualData
  sdibigcomponent->isActiveActualData = 0;
  if(privateSDIBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;//MARKER_ERRORPERIMETR;

  superSetOperativMarker(sdibigcomponent, adrReg);

  return tempReadArray[adrReg-BEGIN_ADR_REGISTER];
}//getSDIBigModbusRegister(int adrReg)
int getSDIBigModbusBit(int adrBit)
{
  //получить содержимое регистра
  superSetOperativMarker(sdibigcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getSDIBigModbusBit(int )
int setSDIBigModbusRegister(int adrReg, int dataReg)
{
  //записать содержимое регистра
  if(privateSDIBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
//  if(privateSDIBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  superSetOperativMarker(sdibigcomponent, adrReg);
  superSetTempWriteArray(dataReg);//записать в буфер

  switch((adrReg-BEGIN_ADR_REGISTER)%REGISTER_FOR_OBJ) {
   case 0:
   break; 
   case 1:
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
   break; 
   case 2:
   break; 
   case 3:
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
   break; 
   case 4:
   break; 
   case 5:
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
   break; 
   case 6:
   break; 
   case 7:
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
   break; 
   case 8:
   break; 
   case 9:
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
   break; 
   case 10:
   break; 
  default: return MARKER_OUTPERIMETR;
  }//switch
  return 0;
}//getDOUTBigModbusRegister(int adrReg)
int setSDIBigModbusBit(int adrBit, int x)
{
  UNUSED(x);
  //получить содержимое регистра
  superSetOperativMarker(sdibigcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void setSDIBigCountObject(void) {
//записать к-во обектов
  int cntObj = current_config.n_led; //Кількість дискретних світлоіндикаторів
  if(cntObj<0) return;
  if(cntObj>TOTAL_OBJ) return;
  sdibigcomponent->countObject = cntObj;
}//
void preSDIBigReadAction(void) {
//action до чтения
  sdibigcomponent->operativMarker[0] = -1;
  sdibigcomponent->operativMarker[1] = -1;//оперативный маркер
  sdibigcomponent->isActiveActualData = 1;
}//
void postSDIBigReadAction(void) {
//action после чтения
  if(sdibigcomponent->operativMarker[0]<0) return;//не было чтения
}//
void preSDIBigWriteAction(void) {
//action до записи
  sdibigcomponent->operativMarker[0] = -1;
  sdibigcomponent->operativMarker[1] = -1;//оперативный маркер
  sdibigcomponent->isActiveActualData = 1;
}//
void postSDIBigWriteAction(void) {
//action после записи
  if(sdibigcomponent->operativMarker[0]<0) return;//не было записи
//  int offset = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//найти смещение TempWriteArray
//  int countRegister = sdibigcomponent->operativMarker[1]-sdibigcomponent->operativMarker[0]+1;
//  if(sdibigcomponent->operativMarker[1]<0) countRegister = 1;
}//

int privateSDIBigGetReg1(int adrReg)
{
  //проверить внутренний периметр
  int count_register = sdibigcomponent->countObject*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg1(int adrReg)
int privateSDIBigGetReg2(int adrReg)
{
  //проверить внешний периметр
  int count_register = TOTAL_OBJ*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
