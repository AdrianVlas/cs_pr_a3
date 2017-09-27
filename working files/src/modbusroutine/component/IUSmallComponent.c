#include "header.h"

//��������� ������� � ����� ������
#define BEGIN_ADR_REGISTER 0
#define REGISTER_FOR_OBJ 16

int getIUModbusRegister(int);//�������� ���������� ��������
int getIUModbusBit(int);//�������� ���������� ����
int setIUModbusRegister(int, int);//�������� ���������� ��������
int setIUModbusBit(int, int);//�������� ���������� ����

void preIUSmallReadAction(void);//action �� ������
void postIUSmallReadAction(void);//action ����� ������
void preIUSmallWriteAction(void);//action �� ������
int postIUSmallWriteAction(void);//action ����� ������
void config_and_settingsIUSmall(void);//action ���������

int privateIUGetReg2(int adrReg);

COMPONENT_OBJ *iucomponent;

/**************************************/
//���������� ���������� ������������� ����������
/**************************************/
void constructorIUSmallComponent(COMPONENT_OBJ *iucomp)
{
  iucomponent = iucomp;

  iucomponent->countObject = 1;//�-�� �������

  iucomponent->getModbusRegister = getIUModbusRegister;//�������� ���������� ��������
  iucomponent->getModbusBit      = getIUModbusBit;//�������� ���������� ����
  iucomponent->setModbusRegister = setIUModbusRegister;//�������� ���������� ��������
  iucomponent->setModbusBit      = setIUModbusBit;//�������� ���������� ����

  iucomponent->preReadAction   = preIUSmallReadAction;//action �� ������
  iucomponent->postReadAction  = postIUSmallReadAction;//action ����� ������
  iucomponent->preWriteAction  = preIUSmallWriteAction;//action �� ������
  iucomponent->postWriteAction = postIUSmallWriteAction;//action ����� ������
  iucomponent->config_and_settings = config_and_settingsIUSmall;//action ���������

  iucomponent->isActiveActualData = 0;
}//prepareDVinConfig

int getIUModbusRegister(int adrReg)
{
  //�������� ���������� ��������
  if(privateIUGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  superSetOperativMarker(iucomponent, adrReg);

  int offset = adrReg-BEGIN_ADR_REGISTER;
  switch(offset%REGISTER_FOR_OBJ) {//������ �������� 
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
  //�������� ���������� bit
  UNUSED(x);
  return MARKER_OUTPERIMETR;
}//getIUModbusBit(int )
int setIUModbusRegister(int x, int y) {
  UNUSED(x);
  UNUSED(y);
  //�������� ���������� ��������
  return MARKER_OUTPERIMETR;
}//setIUModbusRegister(int, int)
int setIUModbusBit(int x, int y) {
  UNUSED(x);
  UNUSED(y);
  //�������� ���������� bit
  return MARKER_OUTPERIMETR;
}//setIUModbusBit(int, int )

void preIUSmallReadAction(void) {
//action �� ������
  iucomponent->operativMarker[0] = -1;
  iucomponent->operativMarker[1] = -1;//����������� ������
  iucomponent->isActiveActualData = 1;
}//
void postIUSmallReadAction(void) {
//action ����� ������
  if(iucomponent->operativMarker[0]<0) return;//�� ���� ������
}//
void preIUSmallWriteAction(void) {
//action �� ������
  iucomponent->operativMarker[0] = -1;
  iucomponent->operativMarker[1] = -1;//����������� ������
  iucomponent->isActiveActualData = 1;
}//
int postIUSmallWriteAction(void) {
//action ����� ������
 return 0;
}//

int privateIUGetReg2(int adrReg)
{
  //��������� ������� ��������
  int count_register = REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)

void config_and_settingsIUSmall(void)
{
//action ���������
}

