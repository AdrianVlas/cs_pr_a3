#include "header.h"

//начальный регистр в карте пам€ти
#define BEGIN_ADR_REGISTER 600
//начальный bit в карте пам€ти
#define BEGIN_ADR_BIT  22000
#define REGISTER_FOR_OBJ 2
#define BIT_FOR_OBJ 18

int privateCommonSmallGetReg2(int adrReg);
int privateCommonSmallGetBit2(int adrBit);

int getCommonSmallModbusRegister(int);//получить содержимое регистра
int getCommonSmallModbusBit(int);//получить содержимое бита
int setCommonSmallModbusRegister(int, int);// регистра
int setCommonSmallModbusBit(int, int);// бита

void setCommonSmallCountObject(int);//записать к-во обектов
void preCommonSmallReadAction(void);//action до чтени€
void postCommonSmallReadAction(void);//action после чтени€
void preCommonSmallWriteAction(void);//action до записи
void postCommonSmallWriteAction(void);//action после записи
void loadCommonSmallActualData(void);

COMPONENT_OBJ *commonsmallcomponent;

/**************************************/
//подготовка компонента ќбщие
/**************************************/
void constructorCommonSmallComponent(COMPONENT_OBJ *commonsmallcomp)
{
  commonsmallcomponent = commonsmallcomp;

  commonsmallcomponent->countObject = 1;//к-во обектов

  commonsmallcomponent->getModbusRegister = getCommonSmallModbusRegister;//получить содержимое регистра
  commonsmallcomponent->getModbusBit      = getCommonSmallModbusBit;//получить содержимое бита
  commonsmallcomponent->setModbusRegister = setCommonSmallModbusRegister;// регистра
  commonsmallcomponent->setModbusBit      = setCommonSmallModbusBit;// бита

  commonsmallcomponent->setCountObject  = setCommonSmallCountObject;//записать к-во обектов
  commonsmallcomponent->preReadAction   = preCommonSmallReadAction;//action до чтени€
  commonsmallcomponent->postReadAction  = postCommonSmallReadAction;//action после чтени€
  commonsmallcomponent->preWriteAction  = preCommonSmallWriteAction;//action до записи
  commonsmallcomponent->postWriteAction = postCommonSmallWriteAction;//action после записи

  commonsmallcomponent->isActiveActualData = 0;
}//prepareDVinConfig

void loadCommonSmallActualData(void) {
  //ActualData
  for(int i=0; i<100; i++) tempReadArray[i] = i;
  /*
  1) —тан знаход€тьс€ у масив≥ uint8_t fix_block_active_state[DIV_TO_HIGHER(FIX_BLOCK_SIGNALS_OUT, 8)];
  2) —п≥вв≥дношенн€ м≥ж номерами б≥т≥в ≥ њх назвами Ї у enum _FIX_BLOCK_output_signals
  */
}//loadActualData() 

int getCommonSmallModbusRegister(int adrReg)
{
  //получить содержимое регистра
  if(privateCommonSmallGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  if(commonsmallcomponent->isActiveActualData) loadCommonSmallActualData(); //ActualData
  commonsmallcomponent->isActiveActualData = 0;

  superSetOperativMarker(commonsmallcomponent, adrReg);

  return tempReadArray[adrReg-BEGIN_ADR_REGISTER];
}//getDVModbusRegister(int adrReg)
int getCommonSmallModbusBit(int adrBit)
{
  //получить содержимое bit
  if(privateCommonSmallGetBit2(adrBit)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  if(commonsmallcomponent->isActiveActualData) loadCommonSmallActualData();
  commonsmallcomponent->isActiveActualData = 0;

  superSetOperativMarker(commonsmallcomponent, adrBit);

  short tmp   = tempReadArray[(adrBit-BEGIN_ADR_BIT)/16];
  short maska = 1<<((adrBit-BEGIN_ADR_BIT)%16);
  if(tmp&maska) return 1;
  return 0;
}//getDVModbusRegister(int adrReg)
int setCommonSmallModbusRegister(int adrReg, int dataReg)
{
  //записать содержимое регистра
  if(privateCommonSmallGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  superSetOperativMarker(commonsmallcomponent, adrReg);
  superSetTempWriteArray(dataReg);//записать в буфер

  switch(adrReg-BEGIN_ADR_REGISTER) {
   case 0:
   return MARKER_ERRORPERIMETR;
   case 1:
   return dataReg;
  }//switch
  return MARKER_OUTPERIMETR;
}//getDVModbusRegister(int adrReg)
int setCommonSmallModbusBit(int adrBit, int dataBit)
{
  //записать содержимое bit
  if(privateCommonSmallGetBit2(adrBit)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  superSetOperativMarker(commonsmallcomponent, adrBit);

  switch(adrBit-BEGIN_ADR_BIT) {
   case 16: 
  //    qDebug()<<"16="<<dataBit;
   return dataBit;
   case 17:
//      qDebug()<<"17="<<dataBit;
   return dataBit;
  }//switch
  return MARKER_ERRORPERIMETR;
}//setCommonSmallModbusBit(int adrBit, int adrData)

void setCommonSmallCountObject(int x) {
  UNUSED(x);
//записать к-во обектов
}//
void preCommonSmallReadAction(void) {
//action до чтени€
  commonsmallcomponent->operativMarker[0] = -1;
  commonsmallcomponent->operativMarker[1] = -1;
  commonsmallcomponent->isActiveActualData = 1;//оперативный маркер
}//
void postCommonSmallReadAction(void) {
//action после чтени€
  if(commonsmallcomponent->operativMarker[0]<0) return;//не было чтени€
}//
void preCommonSmallWriteAction(void) {
//action до записи
  commonsmallcomponent->operativMarker[0] = -1;
  commonsmallcomponent->operativMarker[1] = -1;//оперативный маркер
  commonsmallcomponent->isActiveActualData = 1;
}//
void postCommonSmallWriteAction(void) {
//action после записи
}//

int privateCommonSmallGetReg2(int adrReg)
{
  //проверить внешний периметр
  int count_register = REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
int privateCommonSmallGetBit2(int adrBit)
{
  //проверить внешний периметр
  int count_bit = BIT_FOR_OBJ;
  if(adrBit>=BEGIN_ADR_BIT && adrBit<(BEGIN_ADR_BIT+count_bit)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
