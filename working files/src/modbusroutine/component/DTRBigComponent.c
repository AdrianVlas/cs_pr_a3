#include "header.h"

//начальный регистр в карте памяти
#define BEGIN_ADR_REGISTER 6734
//макс к-во обектов
#define TOTAL_OBJ 128
#define REGISTER_FOR_OBJ 8

int privateDTRBigGetReg1(int adrReg);
int privateDTRBigGetReg2(int adrReg);

int getDTRBigModbusRegister(int);//получить содержимое регистра
int getDTRBigModbusBit(int);//получить содержимое бита
int setDTRBigModbusRegister(int, int);// регистра
int setDTRBigModbusBit(int, int);// бита

void setDTRBigCountObject(void);//записать к-во обектов
void preDTRBigReadAction(void);//action до чтения
void postDTRBigReadAction(void);//action после чтения
void preDTRBigWriteAction(void);//action до записи
void postDTRBigWriteAction(void);//action после записи
void loadDTRBigActualData(void);

COMPONENT_OBJ *dtrbigcomponent;

/**************************************/
//подготовка компонента D-триггер
/**************************************/
void constructorDTRBigComponent(COMPONENT_OBJ *dtrbigcomp)
{
  dtrbigcomponent = dtrbigcomp;

  dtrbigcomponent->countObject = 128;//к-во обектов

  dtrbigcomponent->getModbusRegister = getDTRBigModbusRegister;//получить содержимое регистра
  dtrbigcomponent->getModbusBit      = getDTRBigModbusBit;//получить содержимое бита
  dtrbigcomponent->setModbusRegister = setDTRBigModbusRegister;// регистра
  dtrbigcomponent->setModbusBit      = setDTRBigModbusBit;// бита

  dtrbigcomponent->preReadAction   = preDTRBigReadAction;//action до чтения
  dtrbigcomponent->postReadAction  = postDTRBigReadAction;//action после чтения
  dtrbigcomponent->preWriteAction  = preDTRBigWriteAction;//action до записи
  dtrbigcomponent->postWriteAction = postDTRBigWriteAction;//action после записи

  dtrbigcomponent->isActiveActualData = 0;
}//prepareDVinConfig

void loadDTRBigActualData(void) {
  //ActualData
  for(int i=0; i<100; i++) tempReadArray[i] = i;
}//loadActualData() 

int getDTRBigModbusRegister(int adrReg)
{
  //получить содержимое регистра
  if(privateDTRBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(privateDTRBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  if(dtrbigcomponent->isActiveActualData) loadDTRBigActualData(); //ActualData
  dtrbigcomponent->isActiveActualData = 0;

  superSetOperativMarker(dtrbigcomponent, adrReg);

  return tempReadArray[adrReg-BEGIN_ADR_REGISTER];
}//getDOUTBigModbusRegister(int adrReg)
int getDTRBigModbusBit(int adrBit)
{
  //получить содержимое регистра
  superSetOperativMarker(dtrbigcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setDTRBigModbusRegister(int adrReg, int dataReg)
{
  //записать содержимое регистра
  if(privateDTRBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(privateDTRBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  superSetOperativMarker(dtrbigcomponent, adrReg);
  superSetTempWriteArray(dataReg);//записать в буфер

  switch((adrReg-BEGIN_ADR_REGISTER)%REGISTER_FOR_OBJ) {
   case 0:
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
    return dataReg;
   case 1:
   return dataReg;
   case 2:
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
    return dataReg;
   case 3:
   return dataReg;
   case 4:
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
    return dataReg;
   case 5:
   return dataReg;
   case 6:
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
    return dataReg;
   case 7:
   return dataReg;
  }//switch
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setDTRBigModbusBit(int adrBit, int x)
{
  UNUSED(x);
  //получить содержимое регистра
  superSetOperativMarker(dtrbigcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void setDTRBigCountObject(void) {
//записать к-во обектов
}//
void preDTRBigReadAction(void) {
//action до чтения
  dtrbigcomponent->operativMarker[0] = -1;
  dtrbigcomponent->operativMarker[1] = -1;//оперативный маркер
  dtrbigcomponent->isActiveActualData = 1;
}//
void postDTRBigReadAction(void) {
//action после чтения
  if(dtrbigcomponent->operativMarker[0]<0) return;//не было чтения
}//
void preDTRBigWriteAction(void) {
//action до записи
  dtrbigcomponent->operativMarker[0] = -1;
  dtrbigcomponent->operativMarker[1] = -1;//оперативный маркер
  dtrbigcomponent->isActiveActualData = 1;
}//
void postDTRBigWriteAction(void) {
//action после записи
  if(dtrbigcomponent->operativMarker[0]<0) return;//не было записи
//  int offset = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//найти смещение TempWriteArray
//  int countRegister = dtrbigcomponent->operativMarker[1]-dtrbigcomponent->operativMarker[0]+1;
//  if(dtrbigcomponent->operativMarker[1]<0) countRegister = 1;
}//

int privateDTRBigGetReg1(int adrReg)
{
  //проверить внутренний периметр
  int count_register = dtrbigcomponent->countObject*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg1(int adrReg)
int privateDTRBigGetReg2(int adrReg)
{
  //проверить внешний периметр
  int count_register = TOTAL_OBJ*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
