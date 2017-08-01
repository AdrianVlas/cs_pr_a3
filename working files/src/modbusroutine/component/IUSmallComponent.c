#include "header.h"

//начальный регистр в карте пам€ти
#define BEGIN_ADR_REGISTER 0
#define REGISTER_FOR_OBJ 16

int getIUModbusRegister(int);//получить содержимое регистра
int getIUModbusBit(int);//получить содержимое бита
int setIUModbusRegister(int, int);//получить содержимое регистра
int setIUModbusBit(int, int);//получить содержимое бита

void preIUSmallReadAction(void);//action до чтени€
void postIUSmallReadAction(void);//action после чтени€
void preIUSmallWriteAction(void);//action до записи
int postIUSmallWriteAction(void);//action после записи
//void loadIUSmallActualData(void);

int privateIUGetReg2(int adrReg);

COMPONENT_OBJ *iucomponent;

/**************************************/
//подготовка компонента идентификаци€ устройства
/**************************************/
void constructorIUSmallComponent(COMPONENT_OBJ *iucomp)
{
  iucomponent = iucomp;

  iucomponent->countObject = 1;//к-во обектов

  iucomponent->getModbusRegister = getIUModbusRegister;//получить содержимое регистра
  iucomponent->getModbusBit      = getIUModbusBit;//получить содержимое бита
  iucomponent->setModbusRegister = setIUModbusRegister;//получить содержимое регистра
  iucomponent->setModbusBit      = setIUModbusBit;//получить содержимое бита

  iucomponent->preReadAction   = preIUSmallReadAction;//action до чтени€
  iucomponent->postReadAction  = postIUSmallReadAction;//action после чтени€
  iucomponent->preWriteAction  = preIUSmallWriteAction;//action до записи
  iucomponent->postWriteAction = postIUSmallWriteAction;//action после записи

  iucomponent->isActiveActualData = 0;
}//prepareDVinConfig
/*
void loadIUSmallActualData(void) {
  //ActualData
//  for(int i=0; i<100; i++) tempReadArray[i] = i+22;
  for(int ii=0; ii<16; ii++)
    switch (ii)
    {
    case 0://MA_SERIAL_NUMBER:
      {
        tempReadArray[ii] = serial_number_dev;//serial_number_dev;
        break;
      }

    case 1://MA_NAME_CHAR_1_2:
      {
        tempReadArray[ii] = ('i' << 8) + 'K';
        break;
      }
    case 2://MA_NAME_CHAR_3_4:
      {
        tempReadArray[ii] = ('v' << 8) + 'e';
        break;
      }
    case 3://MA_NAME_CHAR_5_6:
      {
        tempReadArray[ii] = ('r' << 8) + 'p';
        break;
      }
    case 4://MA_NAME_CHAR_7_8:
      {
        tempReadArray[ii] = ('b' << 8) + 'i';
        break;
      }
    case 5://MA_NAME_CHAR_9_10:
      {
        tempReadArray[ii] = ('r' << 8) + 'o';
        break;
      }
    case 6://MA_NAME_CHAR_11_12:
      {
        tempReadArray[ii] = ('R' << 8) + 'M';
        break;
      }
    case 7://MA_NAME_CHAR_13_14:
      {
        tempReadArray[ii] = ('S' << 8) + 'Z';
        break;
      }
    case 8://MA_NAME_CHAR_15_16:
      {
        tempReadArray[ii] = ('5' << 8) + '0';
        break;
      }
    case 9://MA_NAME_CHAR_17_18:
      {
        tempReadArray[ii] = ('_' << 8) + 'L';
        break;
      }
    case 10://MA_VERSION_SW:
      {
        tempReadArray[ii] = (VERSIA_PZ << 8) + MODYFIKACIA_VERSII_PZ;
        break;
      }
    case 11://MA_DATA_COMP_1:
      {
        tempReadArray[ii] = (YEAR_VER << 8) + MONTH_VER;
        break;
      }
    case 12://MA_DATA_COMP_2:
      {
        tempReadArray[ii] = (DAY_VER << 8);
        break;
      }
    case 13://MA_TIME_COMP:
      {
        tempReadArray[ii] = (HOUR_VER << 8) + MINUTE_VER;
        break;
      }
    case 14://MA_VERSION_GMM:
      {
        tempReadArray[ii] = (VERSIA_GMM << 8) + MODYFIKACIA_VERSII_GMM;
        break;
      }
    case 15://MA_ZBIRKA_SW:
      {
        tempReadArray[ii] = ZBIRKA_VERSII_PZ;
        break;
      }
    default:
      {
        //Ќа пол€ €к≥ у дан≥й конф≥гурац≥њ немаЇ в≥дпов≥даЇмо нул€ми
        tempReadArray[ii] = 0;
        break;
      }
    }//switch
}//loadActualData() 
*/

int getIUModbusRegister(int adrReg)
{
  //получить содержимое регистра
  if(privateIUGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

//  if(iucomponent->isActiveActualData) loadIUSmallActualData(); //ActualData
//  iucomponent->isActiveActualData = 0;

  superSetOperativMarker(iucomponent, adrReg);

  int offset = adrReg-BEGIN_ADR_REGISTER;
  switch(offset%REGISTER_FOR_OBJ) {//индекс регистра 
    case 0://MA_SERIAL_NUMBER:
        return serial_number_dev;//serial_number_dev;

    case 1://MA_NAME_CHAR_1_2:
        return ('i' << 8) + 'K';

    case 2://MA_NAME_CHAR_3_4:
        return ('v' << 8) + 'e';

    case 3://MA_NAME_CHAR_5_6:
        return ('r' << 8) + 'p';

    case 4://MA_NAME_CHAR_7_8:
        return ('b' << 8) + 'i';

    case 5://MA_NAME_CHAR_9_10:
        return ('r' << 8) + 'o';

    case 6://MA_NAME_CHAR_11_12:
        return ('R' << 8) + 'M';

    case 7://MA_NAME_CHAR_13_14:
        return ('S' << 8) + 'Z';

    case 8://MA_NAME_CHAR_15_16:
        return ('5' << 8) + '0';

    case 9://MA_NAME_CHAR_17_18:
        return ('_' << 8) + 'L';

    case 10://MA_VERSION_SW:
        return (VERSIA_PZ << 8) + MODYFIKACIA_VERSII_PZ;

    case 11://MA_DATA_COMP_1:
        return (YEAR_VER << 8) + MONTH_VER;

    case 12://MA_DATA_COMP_2:
        return (DAY_VER << 8);

    case 13://MA_TIME_COMP:
        return (HOUR_VER << 8) + MINUTE_VER;

    case 14://MA_VERSION_GMM:
        return (VERSIA_GMM << 8) + MODYFIKACIA_VERSII_GMM;

    case 15://MA_ZBIRKA_SW:
        return ZBIRKA_VERSII_PZ;
  }//switch

  return 0;//tempReadArray[adrReg-BEGIN_ADR_REGISTER];
}//getDVModbusRegister(int adrReg)
int getIUModbusBit(int adrBit) {
  //получить содержимое bit
  superSetOperativMarker(iucomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getIUModbusBit(int )
int setIUModbusRegister(int adrReg, int x) {
  UNUSED(x);
  //записать содержимое регистра
  superSetOperativMarker(iucomponent, adrReg);
  return MARKER_OUTPERIMETR;
}//setIUModbusRegister(int, int)
int setIUModbusBit(int adrBit, int x) {
  UNUSED(x);
  //записать содержимое bit
  superSetOperativMarker(iucomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//setIUModbusBit(int, int )

void preIUSmallReadAction(void) {
//action до чтени€
  iucomponent->operativMarker[0] = -1;
  iucomponent->operativMarker[1] = -1;//оперативный маркер
  iucomponent->isActiveActualData = 1;
}//
void postIUSmallReadAction(void) {
//action после чтени€
  if(iucomponent->operativMarker[0]<0) return;//не было чтени€
}//
void preIUSmallWriteAction(void) {
//action до записи
  iucomponent->operativMarker[0] = -1;
  iucomponent->operativMarker[1] = -1;//оперативный маркер
  iucomponent->isActiveActualData = 1;
}//
int postIUSmallWriteAction(void) {
//action после записи
 return 0;
}//

int privateIUGetReg2(int adrReg)
{
  //проверить внешний периметр
  int count_register = REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)

