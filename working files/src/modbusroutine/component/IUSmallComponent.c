#include "header.h"

//начальный регистр в карте памяти
#define BEGIN_ADR_REGISTER 0
#define REGISTER_FOR_OBJ 16

int getIUModbusRegister(int);//получить содержимое регистра
int getIUModbusBit(int);//получить содержимое бита
int setIUModbusRegister(int, int);//получить содержимое регистра
int setIUModbusBit(int, int);//получить содержимое бита

void preIUSmallReadAction(void);//action до чтения
void postIUSmallReadAction(void);//action после чтения
void preIUSmallWriteAction(void);//action до записи
int postIUSmallWriteAction(void);//action после записи
void config_and_settingsIUSmall(void);//action активации

int privateIUGetReg2(int adrReg);

COMPONENT_OBJ *iucomponent;

/**************************************/
//подготовка компонента идентификация устройства
/**************************************/
void constructorIUSmallComponent(COMPONENT_OBJ *iucomp)
{
  iucomponent = iucomp;

  iucomponent->countObject = 1;//к-во обектов

  iucomponent->getModbusRegister = getIUModbusRegister;//получить содержимое регистра
  iucomponent->getModbusBit      = getIUModbusBit;//получить содержимое бита
  iucomponent->setModbusRegister = setIUModbusRegister;//получить содержимое регистра
  iucomponent->setModbusBit      = setIUModbusBit;//получить содержимое бита

  iucomponent->preReadAction   = preIUSmallReadAction;//action до чтения
  iucomponent->postReadAction  = postIUSmallReadAction;//action после чтения
  iucomponent->preWriteAction  = preIUSmallWriteAction;//action до записи
  iucomponent->postWriteAction = postIUSmallWriteAction;//action после записи
  iucomponent->config_and_settings = config_and_settingsIUSmall;//action активации

  iucomponent->isActiveActualData = 0;
}//prepareDVinConfig

int getIUModbusRegister(int adrReg)
{
  //получить содержимое регистра
  if(privateIUGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

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
int getIUModbusBit(int x) {
  //получить содержимое bit
  UNUSED(x);
  return MARKER_OUTPERIMETR;
}//getIUModbusBit(int )
int setIUModbusRegister(int x, int y) {
  UNUSED(x);
  UNUSED(y);
  //записать содержимое регистра
  return MARKER_OUTPERIMETR;
}//setIUModbusRegister(int, int)
int setIUModbusBit(int x, int y) {
  UNUSED(x);
  UNUSED(y);
  //записать содержимое bit
  return MARKER_OUTPERIMETR;
}//setIUModbusBit(int, int )

void preIUSmallReadAction(void) {
//action до чтения
  iucomponent->operativMarker[0] = -1;
  iucomponent->operativMarker[1] = -1;//оперативный маркер
  iucomponent->isActiveActualData = 1;
}//
void postIUSmallReadAction(void) {
//action после чтения
  if(iucomponent->operativMarker[0]<0) return;//не было чтения
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

void config_and_settingsIUSmall(void)
{
//action активации
}

