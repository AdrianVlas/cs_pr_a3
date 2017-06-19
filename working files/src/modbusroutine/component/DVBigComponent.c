//#include <QtWidgets>
#include "variables_external_m.h"

//начальный регистр в карте памяти
#define BEGIN_ADR_REGISTER 900
//макс к-во обектов
#define TOTAL_OBJ 128
#define REGISTER_FOR_OBJ 2

int privateDVBigGetReg1(int adrReg);
int privateDVBigGetReg2(int adrReg);

int getDVBigModbusRegister(int);//получить содержимое регистра
int getDVBigModbusBit(int);//получить содержимое бита
int setDVBigModbusRegister(int, int);// регистра
int setDVBigModbusBit(int, int);// бита

void setDVBigCountObject(int);//записать к-во обектов
void preDVBigReadAction();//action до чтения
void postDVBigReadAction();//action после чтения
void preDVBigWriteAction();//action до записи
void postDVBigWriteAction();//action после записи
void loadDVBigActualData();

COMPONENT_OBJ *dvbigcomponent;

/**************************************/
//подготовка компонента ДВ
/**************************************/
void constructorDVBigComponent(COMPONENT_OBJ *dvbigcomp)
{
  dvbigcomponent = dvbigcomp;

  dvbigcomponent->countObject = 0;//к-во обектов

  dvbigcomponent->getModbusRegister = getDVBigModbusRegister;//получить содержимое регистра
  dvbigcomponent->getModbusBit      = getDVBigModbusBit;//получить содержимое бита
  dvbigcomponent->setModbusRegister = setDVBigModbusRegister;// регистра
  dvbigcomponent->setModbusBit      = setDVBigModbusBit;// бита

  dvbigcomponent->setCountObject  = setDVBigCountObject;//записать к-во обектов
  dvbigcomponent->preReadAction   = preDVBigReadAction;//action до чтения
  dvbigcomponent->postReadAction  = postDVBigReadAction;//action после чтения
  dvbigcomponent->preWriteAction  = preDVBigWriteAction;//action до записи
  dvbigcomponent->postWriteAction = postDVBigWriteAction;//action после записи

  dvbigcomponent->isActiveActualData = 0;
}//prepareDVinConfig

void loadDVBigActualData() {
  //ActualData
  for(int i=0; i<100; i++) tempReadArray[i] = i;
}//loadActualData() 

int getDVBigModbusRegister(int adrReg)
{
  //получить содержимое регистра
  if(privateDVBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(privateDVBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  if(dvbigcomponent->isActiveActualData) loadDVBigActualData(); //ActualData
  dvbigcomponent->isActiveActualData = 0;

  superSetOperativMarker(dvbigcomponent, adrReg);

  return tempReadArray[adrReg-BEGIN_ADR_REGISTER];
}//getDOUTBigModbusRegister(int adrReg)
int getDVBigModbusBit(int adrReg)
{
  //получить содержимое регистра
  superSetOperativMarker(dvbigcomponent, adrReg);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setDVBigModbusRegister(int adrReg, int dataReg)
{
  //записать содержимое регистра
  if(privateDVBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(privateDVBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  superSetOperativMarker(dvbigcomponent, adrReg);
  superSetTempWriteArray(dataReg);//записать в буфер

  switch((adrReg-BEGIN_ADR_REGISTER)%REGISTER_FOR_OBJ) {
   case 0:
   return dataReg;
   case 1:
    if(dataReg>60) return MARKER_ERRORDIAPAZON;
    return dataReg;
  }//switch
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setDVBigModbusBit(int adrBit, int )
{
  //получить содержимое регистра
  superSetOperativMarker(dvbigcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void setDVBigCountObject(int cntObj) {
//записать к-во обектов
  if(cntObj<0) return;
  if(cntObj>=TOTAL_OBJ) return;
  dvbigcomponent->countObject = cntObj;
}//
void preDVBigReadAction() {
//action до чтения
  dvbigcomponent->operativMarker[0] = -1;
  dvbigcomponent->operativMarker[1] = -1;//оперативный маркер
  dvbigcomponent->isActiveActualData = 1;
}//
void postDVBigReadAction() {
//action после чтения
  if(dvbigcomponent->operativMarker[0]<0) return;//не было чтения
}//
void preDVBigWriteAction() {
//action до записи
  dvbigcomponent->operativMarker[0] = -1;
  dvbigcomponent->operativMarker[1] = -1;//оперативный маркер
  dvbigcomponent->isActiveActualData = 1;
}//
void postDVBigWriteAction() {
//action после записи
  if(dvbigcomponent->operativMarker[0]<0) return;//не было записи
  int offset = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//найти смещение TempWriteArray
  int countRegister = dvbigcomponent->operativMarker[1]-dvbigcomponent->operativMarker[0]+1;
  if(dvbigcomponent->operativMarker[1]<0) countRegister = 1;

        qDebug()<<"offset= "<<offset;

        qDebug()<<"operativMarker[0]= "<<dvbigcomponent->operativMarker[0];
        qDebug()<<"operativMarker[1]= "<<dvbigcomponent->operativMarker[1];

}//

int privateDVBigGetReg1(int adrReg)
{
  //проверить внутренний периметр
  int count_register = dvbigcomponent->countObject*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg1(int adrReg)
int privateDVBigGetReg2(int adrReg)
{
  //проверить внешний периметр
  int count_register = TOTAL_OBJ*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
