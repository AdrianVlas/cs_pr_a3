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
//void loadAISmallActualData(void);

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

  aismallcomponent->isActiveActualData = 0;
}//prepareDVinConfig
/*
void loadAISmallActualData(void) {
  //ActualData
  for(int i=0; i<5; i++) 
  switch(i) {
   case 0://Напряжение Ucv
    tempReadArray[i] = (short) measurement[IM_U];
   break;
   case 1://Ток Iin1
    tempReadArray[i] = (short) measurement[IM_I1];
   break;
   case 2://Ток Iin2
    tempReadArray[i] = (short) measurement[IM_I2];
   break;
   case 3://Ток Iin3
    tempReadArray[i] = (short) measurement[IM_I3];
   break;
   case 4://Ток Iin4
    tempReadArray[i] = (short) measurement[IM_I4];
   break;
  }//switch
*/
  /*
  1) Всі вимірювання у unsigned int measurement[NUMBER_ANALOG_CANALES] Всі вимірювання приведені у мілі-величини
  2) відповідність індексів до їх реальних каналів:
#define IM_I1         0
#define IM_I2         1
#define IM_I3         2
#define IM_I4         3
#define IM_U          4

  */
//}//loadActualData() 

int getAISmallModbusRegister(int adrReg)
{
  //получить содержимое регистра
  if(privateAISmallGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

//  if(aismallcomponent->isActiveActualData) loadAISmallActualData(); //ActualData
//  aismallcomponent->isActiveActualData = 0;

  superSetOperativMarker(aismallcomponent, adrReg);

  int offset = adrReg-BEGIN_ADR_REGISTER;
  switch(offset%REGISTER_FOR_OBJ) {//индекс регистра 
   case 0://Напряжение Ucv
    return measurement[IM_U];
   case 1://Ток Iin1
    return measurement[IM_I1];
   case 2://Ток Iin2
    return measurement[IM_I2];
   case 3://Ток Iin3
    return measurement[IM_I3];
   case 4://Ток Iin4
    return measurement[IM_I4];
  }//switch

  return 0;//tempReadArray[adrReg-BEGIN_ADR_REGISTER];
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
