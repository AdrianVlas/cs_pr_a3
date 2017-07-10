//#include <QtWidgets>
#include "header.h"

//��������� ������� � ����� ������
#define BEGIN_ADR_REGISTER 16
//��������� bit � ����� ������
#define BEGIN_ADR_BIT 16000
//�-�� ��������� �� �����
#define REGISTER_FOR_OBJ 1
//�-�� ����� �� �����
#define BIT_FOR_OBJ 1

int privateRPRSmallGetReg2(int adrReg);
int privateRPRSmallGetBit2(int adrReg);

int getRPRSmallModbusRegister(int);//�������� ���������� ��������
int getRPRSmallModbusBit(int);//�������� ���������� ����
int setRPRSmallModbusRegister(int, int);//�������� ���������� ��������
int setRPRSmallModbusBit(int, int);//�������� ���������� ����

void setRPRSmallCountObject(void);//�������� �-�� �������
void preRPRSmallReadAction(void);//action �� ������
void postRPRSmallReadAction(void);//action ����� ������
void preRPRSmallWriteAction(void);//action �� ������
int postRPRSmallWriteAction(void);//action ����� ������
void loadRPRSmallActualData(void);
int getRPRSmallModbusBeginAdrRegister(void);

COMPONENT_OBJ *rprsmallcomponent;

int getRPRSmallModbusBeginAdrRegister(void)
{
  //�������� ����� ��� ��������
 return BEGIN_ADR_REGISTER;
}//getRPRSmallModbusBeginAdrRegister

/**************************************/
//���������� ���������� ������������ ���������������� ���������
/**************************************/
void constructorRPRSmallComponent(COMPONENT_OBJ *rprsmallcomp)
{
  rprsmallcomponent = rprsmallcomp;

  rprsmallcomponent->countObject = 125;//�-�� �������

  rprsmallcomponent->getModbusRegister = getRPRSmallModbusRegister;//�������� ���������� ��������
  rprsmallcomponent->getModbusBit      = getRPRSmallModbusBit;//�������� ���������� ����
  rprsmallcomponent->setModbusRegister = setRPRSmallModbusRegister;//�������� ���������� ��������
  rprsmallcomponent->setModbusBit      = setRPRSmallModbusBit;//�������� ���������� ����

  rprsmallcomponent->preReadAction   = preRPRSmallReadAction;//action �� ������
  rprsmallcomponent->postReadAction  = postRPRSmallReadAction;//action ����� ������
  rprsmallcomponent->preWriteAction  = preRPRSmallWriteAction;//action �� ������
  rprsmallcomponent->postWriteAction = postRPRSmallWriteAction;//action ����� ������

  rprsmallcomponent->isActiveActualData = 0;
}//prepareDVinConfig

void loadRPRSmallActualData(void) {
  //ActualData
//      qDebug()<<"loadRPRSmallActualData=";//<<result;
  for(int i=0; i<rprsmallcomponent->countObject; i++) {
      int result = superReaderRegister(rprAdresRegister[i]);
      switch(result)
        {
        case MARKER_ERRORPERIMETR://������ ���������
        case MARKER_OUTPERIMETR:
          result = 0;
          break;
        }//switch

  tempReadArray[i] = (short)result;
  }//for
}//loadActualData() 

int getRPRSmallModbusRegister(int adrReg)
{
  //�������� ���������� ��������
  if(privateRPRSmallGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  if(rprsmallcomponent->isActiveActualData) loadRPRSmallActualData(); //ActualData
  rprsmallcomponent->isActiveActualData = 0;

  superSetOperativMarker(rprsmallcomponent, adrReg);

  return tempReadArray[adrReg-BEGIN_ADR_REGISTER];
}//getDOUTModbusRegister(int adrReg)
int getRPRSmallModbusBit(int adrBit)
{
  //�������� ���������� bit
  if(privateRPRSmallGetBit2(adrBit)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  if(rprsmallcomponent->isActiveActualData) loadRPRSmallActualData();
  rprsmallcomponent->isActiveActualData = 0;

  superSetOperativMarker(rprsmallcomponent, adrBit);

  short tmp   = tempReadArray[(adrBit-BEGIN_ADR_BIT)/16];
  short maska = 1<<((adrBit-BEGIN_ADR_BIT)%16);
  if(tmp&maska) return 1;
  return 0;
}//getDOUTBigModbusRegister(int adrReg)
int setRPRSmallModbusRegister(int adrReg, int x)
{
  UNUSED(x);
  //�������� ���������� ��������
  superSetOperativMarker(rprsmallcomponent, adrReg);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setRPRSmallModbusBit(int adrBit, int x)
{
  UNUSED(x);
  //�������� ���������� bit
  superSetOperativMarker(rprsmallcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void setRPRSmallCountObject(void) {
//�������� �-�� �������
}//
void preRPRSmallReadAction(void) {
//action �� ������
  rprsmallcomponent->operativMarker[0] = -1;
  rprsmallcomponent->operativMarker[1] = -1;//����������� ������
  rprsmallcomponent->isActiveActualData = 1;
}//
void postRPRSmallReadAction(void) {
//action ����� ������
  if(rprsmallcomponent->operativMarker[0]<0) return;//�� ���� ������
}//
void preRPRSmallWriteAction(void) {
//action �� ������
  rprsmallcomponent->operativMarker[0] = -1;
  rprsmallcomponent->operativMarker[1] = -1;//����������� ������
  rprsmallcomponent->isActiveActualData = 1;
}//
int postRPRSmallWriteAction(void) {
//action ����� ������
 return 0;
}//

int privateRPRSmallGetReg2(int adrReg)
{
  //��������� ������� ��������
  int count_register = rprsmallcomponent->countObject;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
int privateRPRSmallGetBit2(int adrBit)
{
  //��������� ������� ��������
  int count_bit = 16*(rprsmallcomponent->countObject);
  if(adrBit>=BEGIN_ADR_BIT && adrBit<(BEGIN_ADR_BIT+count_bit)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetBit2(int adrBit)
