#include "header.h"

//начальный регистр в карте памяти
#define BEGIN_ADR_REGISTER 13525
//макс к-во обектов
#define TOTAL_OBJ 128
#define REGISTER_FOR_OBJ 2

int privateNOTBigGetReg1(int adrReg);
int privateNOTBigGetReg2(int adrReg);

int getNOTBigModbusRegister(int);//получить содержимое регистра
int getNOTBigModbusBit(int);//получить содержимое бита
int setNOTBigModbusRegister(int, int);//получить содержимое регистра
int setNOTBigModbusBit(int, int);//получить содержимое бита

void setNOTBigCountObject(void);//записать к-во обектов
void preNOTBigReadAction(void);//action до чтения
void postNOTBigReadAction(void);//action после чтения
void preNOTBigWriteAction(void);//action до записи
void postNOTBigWriteAction(void);//action после записи
void loadNOTBigActualData(void);

COMPONENT_OBJ *notbigcomponent;

/**************************************/
//подготовка компонента NOT
/**************************************/
void constructorNOTBigComponent(COMPONENT_OBJ *notbigcomp)
{
  notbigcomponent = notbigcomp;

  notbigcomponent->countObject = 0;//к-во обектов

  notbigcomponent->getModbusRegister = getNOTBigModbusRegister;//получить содержимое регистра
  notbigcomponent->getModbusBit      = getNOTBigModbusBit;//получить содержимое бита
  notbigcomponent->setModbusRegister = setNOTBigModbusRegister;//получить содержимое регистра
  notbigcomponent->setModbusBit      = setNOTBigModbusBit;//получить содержимое бита

  notbigcomponent->preReadAction   = preNOTBigReadAction;//action до чтения
  notbigcomponent->postReadAction  = postNOTBigReadAction;//action после чтения
  notbigcomponent->preWriteAction  = preNOTBigWriteAction;//action до записи
  notbigcomponent->postWriteAction = postNOTBigWriteAction;//action после записи

  notbigcomponent->isActiveActualData = 0;
}//prepareDVinConfig

void loadNOTBigActualData(void) {
 setNOTBigCountObject(); //записать к-во обектов
  //ActualData
   __LN_NOT *arr = (__LN_NOT*)(spca_of_p_prt[ID_FB_NOT - _ID_FB_FIRST_VAR]);
   for(int item=0; item<notbigcomponent->countObject; item++) {

     for (int i = 0; i < 1; i ++)
     {
        int value = arr[item].settings.param[i] & 0xffff;//LEDIN 0 СД item
        tempReadArray[item*REGISTER_FOR_OBJ+2*i+0] = value;
        value = (arr[item].settings.param[i] >> 16) & 0x7fff;//LEDIN 1 СД item
        tempReadArray[item*REGISTER_FOR_OBJ+2*i+1] = value;
     }
//   //NOT item.1 0
//   int value = arr[item].settings.param[0];
//   tempReadArray[item*REGISTER_FOR_OBJ+0] = value;
//   //NOT item.1 1
//   value = arr[item].settings.param[1];
//   tempReadArray[item*REGISTER_FOR_OBJ+1] = value;
   }//for
}//loadActualData() 

int getNOTBigModbusRegister(int adrReg)
{
  //получить содержимое регистра
  if(privateNOTBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(notbigcomponent->isActiveActualData) loadNOTBigActualData(); //ActualData
  notbigcomponent->isActiveActualData = 0;
  if(privateNOTBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  superSetOperativMarker(notbigcomponent, adrReg);

  return tempReadArray[adrReg-BEGIN_ADR_REGISTER];
}//getDOUTBigModbusRegister(int adrReg)
int getNOTBigModbusBit(int adrBit)
{
  //получить содержимое регистра
  superSetOperativMarker(notbigcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setNOTBigModbusRegister(int adrReg, int dataReg)
{
  //записать содержимое регистра
  if(privateNOTBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(privateNOTBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  superSetOperativMarker(notbigcomponent, adrReg);
  superSetTempWriteArray(dataReg);//записать в буфер

  switch((adrReg-BEGIN_ADR_REGISTER)%REGISTER_FOR_OBJ) {
   case 0:
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
   break; 
   case 1:
   break; 
  default: return MARKER_OUTPERIMETR;
  }//switch
  return 0;
}//getDOUTBigModbusRegister(int adrReg)
int setNOTBigModbusBit(int adrBit, int x)
{
  UNUSED(x);
  //получить содержимое регистра
  superSetOperativMarker(notbigcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void setNOTBigCountObject(void) {
//записать к-во обектов
  int cntObj = current_config.n_not;   //Кількість елементів "НЕ"
  if(cntObj<0) return;
  if(cntObj>TOTAL_OBJ) return;
  notbigcomponent->countObject = cntObj;
}//
void preNOTBigReadAction(void) {
//action до чтения
  notbigcomponent->operativMarker[0] = -1;
  notbigcomponent->operativMarker[1] = -1;//оперативный маркер
  notbigcomponent->isActiveActualData = 1;
}//
void postNOTBigReadAction(void) {
//action после чтения
  if(notbigcomponent->operativMarker[0]<0) return;//не было чтения
}//
void preNOTBigWriteAction(void) {
//action до записи
  notbigcomponent->operativMarker[0] = -1;
  notbigcomponent->operativMarker[1] = -1;//оперативный маркер
  notbigcomponent->isActiveActualData = 1;
}//
void postNOTBigWriteAction(void) {
//action после записи
  if(notbigcomponent->operativMarker[0]<0) return;//не было записи
//  int offset = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//найти смещение TempWriteArray
//  int countRegister = notbigcomponent->operativMarker[1]-notbigcomponent->operativMarker[0]+1;
//  if(notbigcomponent->operativMarker[1]<0) countRegister = 1;
}//

int privateNOTBigGetReg1(int adrReg)
{
  //проверить внутренний периметр
  int count_register = notbigcomponent->countObject*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg1(int adrReg)
int privateNOTBigGetReg2(int adrReg)
{
  //проверить внешний периметр
  int count_register = TOTAL_OBJ*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
