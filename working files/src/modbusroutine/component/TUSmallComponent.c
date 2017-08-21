#include "header.h"

//начальный регистр в карте пам€ти
#define BEGIN_ADR_REGISTER 208
//начальный bit в карте пам€ти
#define BEGIN_ADR_BIT 18128
#define BIT_FOR_OBJ 1
//макс к-во обектов
#define TOTAL_OBJ 128
int privateTUSmallGetReg1(int adrReg);
int privateTUSmallGetReg2(int adrReg);
int privateTUSmallGetBit1(int adrBit);
int privateTUSmallGetBit2(int adrBit);

int getTUSmallModbusRegister(int);//получить содержимое регистра
int getTUSmallModbusBit(int);//получить содержимое бита
int setTUSmallModbusRegister(int, int);//получить содержимое регистра
int setTUSmallModbusBit(int, int);//получить содержимое бита

void setTUSmallCountObject(void);//записать к-во обектов
void preTUSmallReadAction(void);//action до чтени€
void postTUSmallReadAction(void);//action после чтени€
void preTUSmallWriteAction(void);//action до записи
int postTUSmallWriteAction(void);//action после записи
int getTUSmallModbusBeginAdrRegister(void);
void setTUSmallActualData(int beginOffset, int endOffset, int *localArr);
void postTUSmallWriteRegister(void);
void postTUSmallWriteBit(void);

COMPONENT_OBJ *tusmallcomponent;

/**************************************/
//подготовка компонента телеуправление
/**************************************/
void constructorTUSmallComponent(COMPONENT_OBJ *tusmallcomp)
{
  tusmallcomponent = tusmallcomp;

  tusmallcomponent->countObject = 0;//к-во обектов

  tusmallcomponent->getModbusRegister = getTUSmallModbusRegister;//получить содержимое регистра
  tusmallcomponent->getModbusBit      = getTUSmallModbusBit;//получить содержимое бита
  tusmallcomponent->setModbusRegister = setTUSmallModbusRegister;//получить содержимое регистра
  tusmallcomponent->setModbusBit      = setTUSmallModbusBit;//получить содержимое бита

  tusmallcomponent->preReadAction   = preTUSmallReadAction;//action до чтени€
  tusmallcomponent->postReadAction  = postTUSmallReadAction;//action после чтени€
  tusmallcomponent->preWriteAction  = preTUSmallWriteAction;//action до записи
  tusmallcomponent->postWriteAction = postTUSmallWriteAction;//action после записи

  tusmallcomponent->isActiveActualData = 0;
}//prepareDVinConfig

int getTUSmallModbusBeginAdrRegister(void)
{
  //получить адрес нач регистра
 return BEGIN_ADR_REGISTER;
}//getTSmallModbusBeginAdrRegister(void)

void setTUSmallActualData(int beginOffset, int endOffset, int *localArr) {
int i=0;
__LN_TU *arr = (__LN_TU*)(spca_of_p_prt[ID_FB_TU - _ID_FB_FIRST_VAR]);
  for(int item=beginOffset; item<endOffset; item++) {

   if(item<tusmallcomponent->countObject) {
     if(localArr[i]) {
//        qDebug()<<"itemLocalArr= "<<item;
//
//¬становлюЇмо MUTEX (1)
arr[item].internal_input[TU_INT_MUTEX >> 3] |= (1 << (TU_INT_MUTEX & ((1 << 3) - 1)));

//¬становлюЇмо про те що треба активувати дане “” (2)
arr[item].internal_input[TU_INT_ACTIVATION >> 3] |= (1 << (TU_INT_ACTIVATION & ((1 << 3) - 1)));


//—кидаЇмо MUTEX (3)
arr[item].internal_input[TU_INT_MUTEX >> 3] &= (uint8_t)(~(1 << (TU_INT_MUTEX & ((1 << 3) - 1))));
     }//if
   }//if
   i++;
  }//for
}//setTUSmallActualData(int beginOffset, int endOffset, int *localArr)

int getTUSmallModbusRegister(int x)
{
  //получить содержимое регистра
  UNUSED(x);
  return MARKER_OUTPERIMETR;

}//getDVModbusRegister(int adrReg)
int getTUSmallModbusBit(int x)
{
  //получить содержимое bit
  UNUSED(x);
  return MARKER_OUTPERIMETR;

}//getTUSmallModbusBit(int adrBit)
int setTUSmallModbusRegister(int adrReg, int dataReg)
{
  extern  int upravlFlag;//флаг пакетов управлени€ 1-есть управление
  if(privateTUSmallGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(tusmallcomponent->isActiveActualData)  setTUSmallCountObject(); //записать к-во обектов
  tusmallcomponent->isActiveActualData = 0;
  if(privateTUSmallGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;
  
  superSetOperativMarker(tusmallcomponent, adrReg);
  superSetTempWriteArray(dataReg);//записать в буфер
  upravlFlag=1;//флаг пакетов управлени€ 1-есть управление

  return 0;
}//getDVModbusRegister(int adrReg)
int setTUSmallModbusBit(int adrBit, int dataBit)
{
  extern int upravlFlag;//флаг пакетов управлени€ 1-есть управление
  if(privateTUSmallGetBit2(adrBit)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(tusmallcomponent->isActiveActualData)  setTUSmallCountObject(); //записать к-во обектов
  tusmallcomponent->isActiveActualData = 0;
  if(privateTUSmallGetBit1(adrBit)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;
  
  superSetOperativMarker(tusmallcomponent, adrBit);
  superSetTempWriteArray(dataBit);//записать в буфер
  upravlFlag=1;//флаг пакетов управлени€ 1-есть управление

  return 0;
}//getDVModbusRegister(int adrReg)

void setTUSmallCountObject(void) {
//записать к-во обектов
  int cntObj = current_config.n_tu;    // ≥льк≥сть блок≥в сигнал≥зац≥й
  if(cntObj<0) return;
  if(cntObj>TOTAL_OBJ) return;
  tusmallcomponent->countObject = cntObj;
}//
void preTUSmallReadAction(void) {
//action до чтени€
  tusmallcomponent->operativMarker[0] = -1;
  tusmallcomponent->operativMarker[1] = -1;//оперативный маркер
  tusmallcomponent->isActiveActualData = 1;
}//
void postTUSmallReadAction(void) {
//action после чтени€
  if(tusmallcomponent->operativMarker[0]<0) return;//не было чтени€
}//
void preTUSmallWriteAction(void) {
//action до записи
  tusmallcomponent->operativMarker[0] = -1;
  tusmallcomponent->operativMarker[1] = -1;//оперативный маркер
  tusmallcomponent->isActiveActualData = 1;
}//
int postTUSmallWriteAction(void) {
//action после записи
//action после записи
  if(tusmallcomponent->operativMarker[0]<0) return 0;//не было записи

  if(tusmallcomponent->operativMarker[0]<BEGIN_ADR_BIT)  postTUSmallWriteRegister();
  else postTUSmallWriteBit();
  return 0;
}//

int privateTUSmallGetReg1(int adrReg)
{
  //проверить внутренний периметр
  int count_register = tusmallcomponent->countObject/16;
  if(tusmallcomponent->countObject%16) count_register++;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg1(int adrReg)

int privateTUSmallGetReg2(int adrReg)
{
  //проверить внешний периметр
  int count_register = TOTAL_OBJ/16;
  if(TOTAL_OBJ%16) count_register++;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)

int privateTUSmallGetBit1(int adrBit)
{
  //проверить внутренний периметр
  int count_bit = BIT_FOR_OBJ*tusmallcomponent->countObject;
  if(adrBit>=BEGIN_ADR_BIT && adrBit<(BEGIN_ADR_BIT+count_bit)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg1(int adrReg)

int privateTUSmallGetBit2(int adrBit)
{
  //проверить внешний периметр
  int count_bit = BIT_FOR_OBJ*TOTAL_OBJ;
  if(adrBit>=BEGIN_ADR_BIT && adrBit<(BEGIN_ADR_BIT+count_bit)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)

void postTUSmallWriteBit(void) 
{
  int offsetTempWriteArray = superFindTempWriteArrayOffset(BEGIN_ADR_BIT);//найти смещение TempWriteArray
  int countBit = tusmallcomponent->operativMarker[1]-tusmallcomponent->operativMarker[0]+1;
  if(tusmallcomponent->operativMarker[1]<0) countBit = 1;

 int localArr[150];
 for(int i=0; i<150; i++) localArr[i] = 0;

 for(int i=0; i<countBit; i++) localArr[i]=tempWriteArray[offsetTempWriteArray+i];
 int offsetLocA = tusmallcomponent->operativMarker[0]-BEGIN_ADR_BIT;

 int beginOffset = offsetLocA;
 int endOffset   = (offsetLocA +countBit);
 setTUSmallActualData(beginOffset, endOffset, localArr);
}//postTUSmallWriteBit

void postTUSmallWriteRegister(void) 
{
  int offsetTempWriteArray = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//найти смещение TempWriteArray
  int countRegister = tusmallcomponent->operativMarker[1]-tusmallcomponent->operativMarker[0]+1;
  if(tusmallcomponent->operativMarker[1]<0) countRegister = 1;


  int offsetLocA = tusmallcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;

    int beginOffset = offsetLocA*16;
    int endOffset   = (offsetLocA +countRegister)*16;

 int localArr[150];
 for(int i=0; i<150; i++) localArr[i] = 0;
//распаковка вх регистров
    int cntB=0;//счетчик бит
    for (int i=0; i<countRegister; i++) {//счетчик регистров

      if (tempWriteArray[offsetTempWriteArray+i]==0) {
        cntB+=16;
        continue;
      }//if
      else {
        for (int b=0; b<16; b++) {
          localArr[cntB] = 0;
          if ((tempWriteArray[offsetTempWriteArray+i]&(1<<b))!=0) {
            localArr[cntB] = 1;
          }//if
          cntB++;
        }//for
      }
    }//for

 setTUSmallActualData(beginOffset, endOffset, localArr);
}//postTUSmallWriteRegister() 
