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
//void loadAISmallActualData(void);

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

  aismallcomponent->isActiveActualData = 0;
}//prepareDVinConfig
/*
void loadAISmallActualData(void) {
  //ActualData
  for(int i=0; i<5; i++) 
  switch(i) {
   case 0://���������� Ucv
    tempReadArray[i] = (short) measurement[IM_U];
   break;
   case 1://��� Iin1
    tempReadArray[i] = (short) measurement[IM_I1];
   break;
   case 2://��� Iin2
    tempReadArray[i] = (short) measurement[IM_I2];
   break;
   case 3://��� Iin3
    tempReadArray[i] = (short) measurement[IM_I3];
   break;
   case 4://��� Iin4
    tempReadArray[i] = (short) measurement[IM_I4];
   break;
  }//switch
*/
  /*
  1) �� ���������� � unsigned int measurement[NUMBER_ANALOG_CANALES] �� ���������� �������� � ��-��������
  2) ���������� ������� �� �� �������� ������:
#define IM_I1         0
#define IM_I2         1
#define IM_I3         2
#define IM_I4         3
#define IM_U          4

  */
//}//loadActualData() 

int getAISmallModbusRegister(int adrReg)
{
  //�������� ���������� ��������
  if(privateAISmallGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

//  if(aismallcomponent->isActiveActualData) loadAISmallActualData(); //ActualData
//  aismallcomponent->isActiveActualData = 0;

  superSetOperativMarker(aismallcomponent, adrReg);

  int offset = adrReg-BEGIN_ADR_REGISTER;
  switch(offset%REGISTER_FOR_OBJ) {//������ �������� 
   case 0://���������� Ucv
    return measurement[IM_U];
   case 1://��� Iin1
    return measurement[IM_I1];
   case 2://��� Iin2
    return measurement[IM_I2];
   case 3://��� Iin3
    return measurement[IM_I3];
   case 4://��� Iin4
    return measurement[IM_I4];
  }//switch

  return 0;//tempReadArray[adrReg-BEGIN_ADR_REGISTER];
}//getDOUTModbusRegister(int adrReg)
int getAISmallModbusBit(int adrBit)
{
  //�������� ���������� bit
  superSetOperativMarker(aismallcomponent, adrBit);

  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setAISmallModbusRegister(int adrReg, int x)
{
  UNUSED(x);
  //�������� ���������� ��������
  superSetOperativMarker(aismallcomponent, adrReg);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setAISmallModbusBit(int adrBit, int x)
{
  UNUSED(x);
  //�������� ���������� bit
  superSetOperativMarker(aismallcomponent, adrBit);
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
