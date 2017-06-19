//#include "variables_external_m.h"
#include "header.h"

//начальный регистр в карте памяти
#define BEGIN_ADR_REGISTER 700
//макс к-во обектов
#define REGISTER_FOR_OBJ 5

int privateAISmallGetReg2(int adrReg);

int getAISmallModbusRegister(int);//получить содержимое регистра
int getAISmallModbusBit(int);//получить содержимое бита
int setAISmallModbusRegister(int, int);//получить содержимое регистра
int setAISmallModbusBit(int, int);//получить содержимое бита

void setAISmallCountObject(int);//записать к-во обектов
void preAISmallReadAction(void);//action до чтения
void postAISmallReadAction(void);//action после чтения
void preAISmallWriteAction(void);//action до записи
void postAISmallWriteAction(void);//action после записи
void loadAISmallActualData(void);

COMPONENT_OBJ *aismallcomponent;

/**************************************/
//подготовка компонента ранжирование пользовательских регистров
/**************************************/
void constructorAISmallComponent(COMPONENT_OBJ *aismallcomp)
{
  aismallcomponent = aismallcomp;

  aismallcomponent->countObject = 1;//к-во обектов

  aismallcomponent->getModbusRegister = getAISmallModbusRegister;//получить содержимое регистра
  aismallcomponent->getModbusBit      = getAISmallModbusBit;//получить содержимое бита
  aismallcomponent->setModbusRegister = setAISmallModbusRegister;//получить содержимое регистра
  aismallcomponent->setModbusBit      = setAISmallModbusBit;//получить содержимое бита

  aismallcomponent->setCountObject  = setAISmallCountObject;//записать к-во обектов
  aismallcomponent->preReadAction   = preAISmallReadAction;//action до чтения
  aismallcomponent->postReadAction  = postAISmallReadAction;//action после чтения
  aismallcomponent->preWriteAction  = preAISmallWriteAction;//action до записи
  aismallcomponent->postWriteAction = postAISmallWriteAction;//action после записи

  aismallcomponent->isActiveActualData = 0;
}//prepareDVinConfig

void loadAISmallActualData(void) {
  //ActualData
  for(int i=0; i<100; i++) tempReadArray[i] = i;
  /*
  1) Всі вимірювання у unsigned int measurement[NUMBER_ANALOG_CANALES] Всі вимірювання приведені у мілі-величини
  2) відповідність індексів до їх реальних каналів:
#define IM_I1         0
#define IM_I2         1
#define IM_I3         2
#define IM_I4         3
#define IM_U          4

  */
}//loadActualData() 

int getAISmallModbusRegister(int adrReg)
{
  //получить содержимое регистра
  if(privateAISmallGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  if(aismallcomponent->isActiveActualData) loadAISmallActualData(); //ActualData
  aismallcomponent->isActiveActualData = 0;

  superSetOperativMarker(aismallcomponent, adrReg);

  return tempReadArray[adrReg-BEGIN_ADR_REGISTER];
}//getDOUTModbusRegister(int adrReg)
int getAISmallModbusBit(int adrBit)
{
  //получить содержимое bit
  superSetOperativMarker(aismallcomponent, adrBit);

  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setAISmallModbusRegister(int adrReg, int x)
{
  UNUSED(x);
  //записать содержимое регистра
  superSetOperativMarker(aismallcomponent, adrReg);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setAISmallModbusBit(int adrBit, int x)
{
  UNUSED(x);
  //записать содержимое bit
  superSetOperativMarker(aismallcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void setAISmallCountObject(int x) {
//записать к-во обектов
  UNUSED(x);
}//
void preAISmallReadAction(void) {
//action до чтения
  aismallcomponent->operativMarker[0] = -1;
  aismallcomponent->operativMarker[1] = -1;//оперативный маркер
  aismallcomponent->isActiveActualData = 1;
}//
void postAISmallReadAction(void) {
//action после чтения
  if(aismallcomponent->operativMarker[0]<0) return;//не было чтения
}//
void preAISmallWriteAction(void) {
//action до записи
  aismallcomponent->operativMarker[0] = -1;
  aismallcomponent->operativMarker[1] = -1;//оперативный маркер
  aismallcomponent->isActiveActualData = 1;
}//
void postAISmallWriteAction(void) {
//action после записи
}//

int privateAISmallGetReg2(int adrReg)
{
  //проверить внешний периметр
  int count_register = REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
