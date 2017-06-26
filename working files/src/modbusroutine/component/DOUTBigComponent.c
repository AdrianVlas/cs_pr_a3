//#include <QtWidgets>
#include "header.h"

//начальный регистр в карте памяти
#define BEGIN_ADR_REGISTER 1156
//макс к-во обектов
#define TOTAL_OBJ 128
#define REGISTER_FOR_OBJ 11
int privateDOUTBigGetReg1(int adrReg);
int privateDOUTBigGetReg2(int adrReg);

int getDOUTBigModbusRegister(int);//получить содержимое регистра
int getDOUTBigModbusBit(int);//получить содержимое бита
int setDOUTBigModbusRegister(int, int);// регистра
int setDOUTBigModbusBit(int, int);// бита

void setDOUTBigCountObject(void);//записать к-во обектов
void preDOUTBigReadAction(void);//action до чтения
void postDOUTBigReadAction(void);//action после чтения
void preDOUTBigWriteAction(void);//action до записи
void postDOUTBigWriteAction(void);//action после записи
void loadDOUTBigActualData(void);

COMPONENT_OBJ *doutbigcomponent;

/**************************************/
//подготовка компонента ДВ
/**************************************/
void constructorDOUTBigComponent(COMPONENT_OBJ *doutcomp)
{
  doutbigcomponent = doutcomp;
  doutbigcomponent->countObject = 0;//к-во обектов

  doutbigcomponent->getModbusRegister = getDOUTBigModbusRegister;//получить содержимое регистра
  doutbigcomponent->getModbusBit      = getDOUTBigModbusBit;//получить содержимое бита
  doutbigcomponent->setModbusRegister = setDOUTBigModbusRegister;// регистра
  doutbigcomponent->setModbusBit      = setDOUTBigModbusBit;// бита

  doutbigcomponent->preReadAction   = preDOUTBigReadAction;//action до чтения
  doutbigcomponent->postReadAction  = postDOUTBigReadAction;//action после чтения
  doutbigcomponent->preWriteAction  = preDOUTBigWriteAction;//action до записи
  doutbigcomponent->postWriteAction = postDOUTBigWriteAction;//action после записи

  doutbigcomponent->isActiveActualData = 0;
}//prepareDVinConfig

void loadDOUTBigActualData(void) {
 setDOUTBigCountObject(); //записать к-во обектов

  //ActualData
  __LN_OUTPUT_LED *arr = (__LN_OUTPUT_LED*)(spca_of_p_prt[ID_FB_OUTPUT - _ID_FB_FIRST_VAR]);
   for(int item=0; item<doutbigcomponent->countObject; item++) {
   int value = arr[item].settings.control;//Параметры ДВых. item
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
  /*
  ...
  
  на входи "Генератор C1" і "Генератор C2" можна встановити тільки генеротори, тобто id мусить дорівнювати ID_FB_MEANDER, n не може перевищувати кількість генераторів у конфігурації, out мусить дорівнювати 1, бо у генератора є єдиний вихід
  */
}//loadActualData() 

int getDOUTBigModbusRegister(int adrReg)
{
  //получить содержимое регистра
  if(privateDOUTBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(doutbigcomponent->isActiveActualData) loadDOUTBigActualData(); //ActualData
  doutbigcomponent->isActiveActualData = 0;
  if(privateDOUTBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;//MARKER_ERRORPERIMETR;

  superSetOperativMarker(doutbigcomponent, adrReg);

  return tempReadArray[adrReg-BEGIN_ADR_REGISTER];
}//getDOUTBigModbusRegister(int adrReg)
int getDOUTBigModbusBit(int adrBit)
{
  //получить содержимое регистра
  superSetOperativMarker(doutbigcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setDOUTBigModbusRegister(int adrReg, int dataReg)
{
  //записать содержимое регистра
  if(privateDOUTBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
//  if(privateDOUTBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  superSetOperativMarker(doutbigcomponent, adrReg);
  superSetTempWriteArray(dataReg);//записать в буфер

  switch((adrReg-BEGIN_ADR_REGISTER)%REGISTER_FOR_OBJ) {
   case 0:
   break; 
   case 1:
//    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
   break; 
   case 2:
   break; 
   case 3:
//    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
   break; 
   case 4:
   break; 
   case 5:
//    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
   break; 
   case 6:
   break; 
   case 7:
//    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
   break; 
   case 8:
   break; 
   case 9:
//    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
   break; 
   case 10:
   break; 
  default: return MARKER_OUTPERIMETR;
  }//switch
  return 0;
}//getDOUTBigModbusRegister(int adrReg)
int setDOUTBigModbusBit(int adrReg, int x)
{
  UNUSED(x);
  //получить содержимое регистра
  superSetOperativMarker(doutbigcomponent, adrReg);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void setDOUTBigCountObject(void) {
//записать к-во обектов
  int cntObj = current_config.n_output; //Кількість дискретних виходів
  if(cntObj<0) return;
  if(cntObj>TOTAL_OBJ) return;
  doutbigcomponent->countObject = cntObj;
}//
void preDOUTBigReadAction(void) {
//action до чтения
  doutbigcomponent->operativMarker[0] = -1;
  doutbigcomponent->operativMarker[1] = -1;//оперативный маркер
  doutbigcomponent->isActiveActualData = 1;
}//
void postDOUTBigReadAction(void) {
//action после чтения
  if(doutbigcomponent->operativMarker[0]<0) return;//не было чтения
}//
void preDOUTBigWriteAction(void) {
//action до записи
  doutbigcomponent->operativMarker[0] = -1;
  doutbigcomponent->operativMarker[1] = -1;//оперативный маркер
  doutbigcomponent->isActiveActualData = 1;
}//
void postDOUTBigWriteAction(void) {
//action после записи
  if(doutbigcomponent->operativMarker[0]<0) return;//не было записи
/*
  int offset = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//найти смещение TempWriteArray
  int countRegister = doutbigcomponent->operativMarker[1]-doutbigcomponent->operativMarker[0]+1;
  if(doutbigcomponent->operativMarker[1]<0) countRegister = 1;

        qDebug()<<"offsetOUT= "<<offset;

        qDebug()<<"operativMarkerOUT[0]= "<<doutbigcomponent->operativMarker[0];
        qDebug()<<"operativMarkerOUT[1]= "<<doutbigcomponent->operativMarker[1];
*/
}//

int privateDOUTBigGetReg1(int adrReg)
{
  //проверить внутренний периметр
  int count_register = doutbigcomponent->countObject*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg1(int adrReg)
int privateDOUTBigGetReg2(int adrReg)
{
  //проверить внешний периметр
  int count_register = TOTAL_OBJ*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
