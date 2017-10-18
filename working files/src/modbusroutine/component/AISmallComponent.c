#include "header.h"

//��������� ������� � ����� ������
#define BEGIN_ADR_REGISTER 700
//���� �-�� �������
#define REGISTER_FOR_OBJ 5

int privateAISmallGetReg2(int adrReg);

int getAISmallModbusRegister(int);//�������� ���������� ��������
int getAISmallModbusBit(int);//�������� ���������� ����
int setAISmallModbusRegister(int, int);//�������� ���������� ��������
int setAISmallModbusBit(int, int);//�������� ���������� ����

void preAISmallReadAction(void);//action �� ������
void postAISmallReadAction(void);//action ����� ������
void preAISmallWriteAction(void);//action �� ������
int postAISmallWriteAction(void);//action ����� ������
void config_and_settingsAISmall(void);//action ���������

COMPONENT_OBJ *aismallcomponent;

/**************************************/
//���������� ���������� ������ �����
/**************************************/
void constructorAISmallComponent(COMPONENT_OBJ *aismallcomp)
{
  aismallcomponent = aismallcomp;

  aismallcomponent->countObject = 1;//�-�� �������

  aismallcomponent->getModbusRegister = getAISmallModbusRegister;//�������� ���������� ��������
  aismallcomponent->getModbusBit      = getAISmallModbusBit;//�������� ���������� ����
  aismallcomponent->setModbusRegister = setAISmallModbusRegister;//�������� ���������� ��������
  aismallcomponent->setModbusBit      = setAISmallModbusBit;//�������� ���������� ����

  aismallcomponent->preReadAction   = preAISmallReadAction;//action �� ������
  aismallcomponent->postReadAction  = postAISmallReadAction;//action ����� ������
  aismallcomponent->preWriteAction  = preAISmallWriteAction;//action �� ������
  aismallcomponent->postWriteAction = postAISmallWriteAction;//action ����� ������
  aismallcomponent->config_and_settings = config_and_settingsAISmall;//action ���������

  aismallcomponent->isActiveActualData = 0;
}//prepareDVinConfig

int getAISmallModbusRegister(int adrReg)
{
  //�������� ���������� ��������
  if(privateAISmallGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  superSetOperativMarker(aismallcomponent, adrReg);

  int offset = adrReg-BEGIN_ADR_REGISTER;
  switch(offset%REGISTER_FOR_OBJ) {//������ �������� 
   case 0://���������� Ucv
    return measurement[IM_U]/4;
   case 1://��� Iin1
    return measurement[IM_I1];
   case 2://��� Iin2
    return measurement[IM_I2];
   case 3://��� Iin3
    return measurement[IM_I3];
   case 4://��� Iin4
    return measurement[IM_I4];
  }//switch

  return 0;
}//getDOUTModbusRegister(int adrReg)
int getAISmallModbusBit(int x)
{
  //�������� ���������� bit
  UNUSED(x);

  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setAISmallModbusRegister(int x, int y)
{
  UNUSED(x);
  UNUSED(y);
  //�������� ���������� ��������
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setAISmallModbusBit(int x, int y)
{
  UNUSED(x);
  UNUSED(y);
  //�������� ���������� bit
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void preAISmallReadAction(void) {
//action �� ������
  aismallcomponent->operativMarker[0] = -1;
  aismallcomponent->operativMarker[1] = -1;//����������� ������
  aismallcomponent->isActiveActualData = 1;
}//
void postAISmallReadAction(void) {
//action ����� ������
  if(aismallcomponent->operativMarker[0]<0) return;//�� ���� ������
}//
void preAISmallWriteAction(void) {
//action �� ������
  aismallcomponent->operativMarker[0] = -1;
  aismallcomponent->operativMarker[1] = -1;//����������� ������
  aismallcomponent->isActiveActualData = 1;
}//
int postAISmallWriteAction(void) {
//action ����� ������
return 0;
}//

int privateAISmallGetReg2(int adrReg)
{
  //��������� ������� ��������
  int count_register = REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)

void config_and_settingsAISmall(void)
{
//action ���������
}

