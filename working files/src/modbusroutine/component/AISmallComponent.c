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

void preAISmallReadAction(void);//action до чтения
void postAISmallReadAction(void);//action после чтения
void preAISmallWriteAction(void);//action до записи
int postAISmallWriteAction(void);//action после записи
void config_and_settingsAISmall(void);//action активации

COMPONENT_OBJ *aismallcomponent;

/**************************************/
//подготовка компонента аналог входа
/**************************************/
void constructorAISmallComponent(COMPONENT_OBJ *aismallcomp)
{
  aismallcomponent = aismallcomp;

  aismallcomponent->countObject = 1;//к-во обектов

  aismallcomponent->getModbusRegister = getAISmallModbusRegister;//получить содержимое регистра
  aismallcomponent->getModbusBit      = getAISmallModbusBit;//получить содержимое бита
  aismallcomponent->setModbusRegister = setAISmallModbusRegister;//получить содержимое регистра
  aismallcomponent->setModbusBit      = setAISmallModbusBit;//получить содержимое бита

  aismallcomponent->preReadAction   = preAISmallReadAction;//action до чтения
  aismallcomponent->postReadAction  = postAISmallReadAction;//action после чтения
  aismallcomponent->preWriteAction  = preAISmallWriteAction;//action до записи
  aismallcomponent->postWriteAction = postAISmallWriteAction;//action после записи
  aismallcomponent->config_and_settings = config_and_settingsAISmall;//action активации

  aismallcomponent->isActiveActualData = 0;
}//prepareDVinConfig

int getAISmallModbusRegister(int adrReg)
{
  //получить содержимое регистра
  if(privateAISmallGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  superSetOperativMarker(aismallcomponent, adrReg);

  int offset = adrReg-BEGIN_ADR_REGISTER;
  switch(offset%REGISTER_FOR_OBJ) {//индекс регистра 
   case 0://Напряжение Ucv
    return measurement[IM_U]/4;
   case 1://Ток Iin1
    return measurement[IM_I1];
   case 2://Ток Iin2
    return measurement[IM_I2];
   case 3://Ток Iin3
    return measurement[IM_I3];
   case 4://Ток Iin4
    return measurement[IM_I4];
  }//switch

  return 0;
}//getDOUTModbusRegister(int adrReg)
int getAISmallModbusBit(int x)
{
  //получить содержимое bit
  UNUSED(x);

  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setAISmallModbusRegister(int x, int y)
{
  UNUSED(x);
  UNUSED(y);
  //записать содержимое регистра
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setAISmallModbusBit(int x, int y)
{
  UNUSED(x);
  UNUSED(y);
  //записать содержимое bit
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

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
int postAISmallWriteAction(void) {
//action после записи
return 0;
}//

int privateAISmallGetReg2(int adrReg)
{
  //проверить внешний периметр
  int count_register = REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)

void config_and_settingsAISmall(void)
{
//action активации
}

