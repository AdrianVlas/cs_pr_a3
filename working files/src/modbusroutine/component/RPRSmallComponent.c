//#include <QtWidgets>
#include "header.h"

//начальный регистр в карте памяти
#define BEGIN_ADR_REGISTER 16
//начальный bit в карте памяти
#define BEGIN_ADR_BIT 16000
//к-во регистров на обект
#define REGISTER_FOR_OBJ 1
//к-во битов на обект
#define BIT_FOR_OBJ 1

int privateRPRSmallGetReg2(int adrReg);
int privateRPRSmallGetBit2(int adrReg);

int getRPRSmallModbusRegister(int);//получить содержимое регистра
int getRPRSmallModbusBit(int);//получить содержимое бита
int setRPRSmallModbusRegister(int, int);//получить содержимое регистра
int setRPRSmallModbusBit(int, int);//получить содержимое бита

void setRPRSmallCountObject(void);//записать к-во обектов
void preRPRSmallReadAction(void);//action до чтения
void postRPRSmallReadAction(void);//action после чтения
void preRPRSmallWriteAction(void);//action до записи
int postRPRSmallWriteAction(void);//action после записи
void loadRPRSmallActualData(void);
int getRPRSmallModbusBeginAdrRegister(void);

COMPONENT_OBJ *rprsmallcomponent;

int getRPRSmallModbusBeginAdrRegister(void)
{
  //получить адрес нач регистра
 return BEGIN_ADR_REGISTER;
}//getRPRSmallModbusBeginAdrRegister

/**************************************/
//подготовка компонента ранжирование пользовательских регистров
/**************************************/
void constructorRPRSmallComponent(COMPONENT_OBJ *rprsmallcomp)
{
  rprsmallcomponent = rprsmallcomp;

  rprsmallcomponent->countObject = 125;//к-во обектов

  rprsmallcomponent->getModbusRegister = getRPRSmallModbusRegister;//получить содержимое регистра
  rprsmallcomponent->getModbusBit      = getRPRSmallModbusBit;//получить содержимое бита
  rprsmallcomponent->setModbusRegister = setRPRSmallModbusRegister;//получить содержимое регистра
  rprsmallcomponent->setModbusBit      = setRPRSmallModbusBit;//получить содержимое бита

  rprsmallcomponent->preReadAction   = preRPRSmallReadAction;//action до чтения
  rprsmallcomponent->postReadAction  = postRPRSmallReadAction;//action после чтения
  rprsmallcomponent->preWriteAction  = preRPRSmallWriteAction;//action до записи
  rprsmallcomponent->postWriteAction = postRPRSmallWriteAction;//action после записи

  rprsmallcomponent->isActiveActualData = 0;
}//prepareDVinConfig

void loadRPRSmallActualData(void) {
  //ActualData
//      qDebug()<<"loadRPRSmallActualData=";//<<result;
  for(int i=0; i<rprsmallcomponent->countObject; i++) {
      int result = superReaderRegister(rprAdresRegister[i]);
      switch(result)
        {
        case MARKER_ERRORPERIMETR://ошибка периметра
        case MARKER_OUTPERIMETR:
          result = 0;
          break;
        }//switch

  tempReadArray[i] = (short)result;
  }//for
}//loadActualData() 

int getRPRSmallModbusRegister(int adrReg)
{
  //получить содержимое регистра
  if(privateRPRSmallGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  if(rprsmallcomponent->isActiveActualData) loadRPRSmallActualData(); //ActualData
  rprsmallcomponent->isActiveActualData = 0;

  superSetOperativMarker(rprsmallcomponent, adrReg);

  return tempReadArray[adrReg-BEGIN_ADR_REGISTER];
}//getDOUTModbusRegister(int adrReg)
int getRPRSmallModbusBit(int adrBit)
{
  //получить содержимое bit
  if(privateRPRSmallGetBit2(adrBit)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  if(rprsmallcomponent->isActiveActualData) loadRPRSmallActualData();
  rprsmallcomponent->isActiveActualData = 0;

  superSetOperativMarker(rprsmallcomponent, adrBit);

  short tmp   = tempReadArray[(adrBit-BEGIN_ADR_BIT)/16];
  short maska = 1<<((adrBit-BEGIN_ADR_BIT)%16);
  if(tmp&maska) return 1;
  return 0;
}//getDOUTBigModbusRegister(int adrReg)
int setRPRSmallModbusRegister(int adrReg, int x)
{
  UNUSED(x);
  //записать содержимое регистра
  superSetOperativMarker(rprsmallcomponent, adrReg);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setRPRSmallModbusBit(int adrBit, int x)
{
  UNUSED(x);
  //записать содержимое bit
  superSetOperativMarker(rprsmallcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void setRPRSmallCountObject(void) {
//записать к-во обектов
}//
void preRPRSmallReadAction(void) {
//action до чтения
  rprsmallcomponent->operativMarker[0] = -1;
  rprsmallcomponent->operativMarker[1] = -1;//оперативный маркер
  rprsmallcomponent->isActiveActualData = 1;
}//
void postRPRSmallReadAction(void) {
//action после чтения
  if(rprsmallcomponent->operativMarker[0]<0) return;//не было чтения
}//
void preRPRSmallWriteAction(void) {
//action до записи
  rprsmallcomponent->operativMarker[0] = -1;
  rprsmallcomponent->operativMarker[1] = -1;//оперативный маркер
  rprsmallcomponent->isActiveActualData = 1;
}//
int postRPRSmallWriteAction(void) {
//action после записи
 return 0;
}//

int privateRPRSmallGetReg2(int adrReg)
{
  //проверить внешний периметр
  int count_register = rprsmallcomponent->countObject;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
int privateRPRSmallGetBit2(int adrBit)
{
  //проверить внешний периметр
  int count_bit = 16*(rprsmallcomponent->countObject);
  if(adrBit>=BEGIN_ADR_BIT && adrBit<(BEGIN_ADR_BIT+count_bit)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetBit2(int adrBit)
