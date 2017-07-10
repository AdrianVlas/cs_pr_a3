#include "header.h"

//��������� ������� � ����� ������
#define BEGIN_ADR_REGISTER 598
//��������� bit � ����� ������
#define BEGIN_ADR_BIT 21968
#define REGISTER_FOR_OBJ 1
#define BIT_FOR_OBJ 3

int privateSDI3ColorSmallGetReg2(int adrReg);
int privateSDI3ColorSmallGetBit2(int adrBit);

int getSDI3ColorSmallModbusRegister(int);//�������� ���������� ��������
int getSDI3ColorSmallModbusBit(int);//�������� ���������� ����
int setSDI3ColorSmallModbusRegister(int, int);//�������� ���������� ��������
int setSDI3ColorSmallModbusBit(int, int);//�������� ���������� ����

void setSDI3ColorSmallCountObject(void);//�������� �-�� �������
void preSDI3ColorSmallReadAction(void);//action �� ������
void postSDI3ColorSmallReadAction(void);//action ����� ������
void preSDI3ColorSmallWriteAction(void);//action �� ������
int postSDI3ColorSmallWriteAction(void);//action ����� ������
void loadSDI3ColorSmallActualData(void);

COMPONENT_OBJ *sdi3colorsmallcomponent;

/**************************************/
//���������� ���������� ���������������� 2 �����
/**************************************/
void constructorSDI3ColorSmallComponent(COMPONENT_OBJ *sdi3colorsmallcomp)
{
  sdi3colorsmallcomponent = sdi3colorsmallcomp;

  sdi3colorsmallcomponent->countObject = 2;//�-�� �������

  sdi3colorsmallcomponent->getModbusRegister = getSDI3ColorSmallModbusRegister;//�������� ���������� ��������
  sdi3colorsmallcomponent->getModbusBit      = getSDI3ColorSmallModbusBit;//�������� ���������� ����
  sdi3colorsmallcomponent->setModbusRegister = setSDI3ColorSmallModbusRegister;//�������� ���������� ��������
  sdi3colorsmallcomponent->setModbusBit      = setSDI3ColorSmallModbusBit;//�������� ���������� ����

  sdi3colorsmallcomponent->preReadAction   = preSDI3ColorSmallReadAction;//action �� ������
  sdi3colorsmallcomponent->postReadAction  = postSDI3ColorSmallReadAction;//action ����� ������
  sdi3colorsmallcomponent->preWriteAction  = preSDI3ColorSmallWriteAction;//action �� ������
  sdi3colorsmallcomponent->postWriteAction = postSDI3ColorSmallWriteAction;//action ����� ������
 
  sdi3colorsmallcomponent->isActiveActualData = 0;
}//prepareDVinConfig

void loadSDI3ColorSmallActualData(void) {
  //ActualData
  for(int i=0; i<100; i++) tempReadArray[i] = i;
}//loadActualData() 

int getSDI3ColorSmallModbusRegister(int adrReg)
{
  //�������� ���������� ��������
  if(privateSDI3ColorSmallGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  if(sdi3colorsmallcomponent->isActiveActualData) loadSDI3ColorSmallActualData(); //ActualData
  sdi3colorsmallcomponent->isActiveActualData = 0;

  superSetOperativMarker(sdi3colorsmallcomponent, adrReg);

  return tempReadArray[adrReg-BEGIN_ADR_REGISTER];
}//getDVModbusRegister(int adrReg)
int getSDI3ColorSmallModbusBit(int adrBit)
{
  //�������� ���������� ��������
  if(privateSDI3ColorSmallGetBit2(adrBit)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  if(sdi3colorsmallcomponent->isActiveActualData) loadSDI3ColorSmallActualData();
  sdi3colorsmallcomponent->isActiveActualData = 0;

  superSetOperativMarker(sdi3colorsmallcomponent, adrBit);

  short tmp   = tempReadArray[(adrBit-BEGIN_ADR_BIT)/16];
  short maska = 1<<((adrBit-BEGIN_ADR_BIT)%16);
  if(tmp&maska) return 1;
  return 0;
}//getDVModbusRegister(int adrReg)
int setSDI3ColorSmallModbusRegister(int adrReg, int x)
{
  UNUSED(x);
  //�������� ���������� ��������
  superSetOperativMarker(sdi3colorsmallcomponent, adrReg);
  return MARKER_OUTPERIMETR;
}//getDVModbusRegister(int adrReg)
int setSDI3ColorSmallModbusBit(int adrBit, int x)
{
  UNUSED(x);
  //�������� ���������� ��������
  superSetOperativMarker(sdi3colorsmallcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDVModbusRegister(int adrReg)

void setSDI3ColorSmallCountObject(void) {
//�������� �-�� �������
}//
void preSDI3ColorSmallReadAction(void) {
//action �� ������
  sdi3colorsmallcomponent->operativMarker[0] = -1;
  sdi3colorsmallcomponent->operativMarker[1] = -1;//����������� ������
  sdi3colorsmallcomponent->isActiveActualData = 1;
}//
void postSDI3ColorSmallReadAction(void) {
//action ����� ������
  if(sdi3colorsmallcomponent->operativMarker[0]<0) return;//�� ���� ������
}//
void preSDI3ColorSmallWriteAction(void) {
//action �� ������
  sdi3colorsmallcomponent->operativMarker[0] = -1;
  sdi3colorsmallcomponent->operativMarker[1] = -1;//����������� ������
  sdi3colorsmallcomponent->isActiveActualData = 1;
}//
int postSDI3ColorSmallWriteAction(void) {
//action ����� ������
 return 0;
}//

int privateSDI3ColorSmallGetReg2(int adrReg)
{
  //��������� ������� ��������
  int count_register = REGISTER_FOR_OBJ*sdi3colorsmallcomponent->countObject;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateSDI3ColorSmallGetReg2(int adrReg)
int privateSDI3ColorSmallGetBit2(int adrBit)
{
  //��������� ������� ��������
  int count_bit = BIT_FOR_OBJ*sdi3colorsmallcomponent->countObject;
  if(adrBit>=BEGIN_ADR_BIT && adrBit<(BEGIN_ADR_BIT+count_bit)) return 0;
  return MARKER_OUTPERIMETR;
}//privateSDI3ColorSmallGetBit2(int adrReg)
