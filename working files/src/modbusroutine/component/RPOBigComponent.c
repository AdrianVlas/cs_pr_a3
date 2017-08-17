#include "header.h"

//��������� ������� � ����� ������
#define BEGIN_ADR_REGISTER 61949
//���� �-�� �������
#define REGISTER_FOR_OBJ 9

int privateRPOBigGetReg2(int adrReg);

int getRPOBigModbusRegister(int);//�������� ���������� ��������
int getRPOBigModbusBit(int);//�������� ���������� ����
int setRPOBigModbusRegister(int, int);//�������� ���������� ��������
int setRPOBigModbusBit(int, int);//�������� ���������� ����

void preRPOBigReadAction(void);//action �� ������
void postRPOBigReadAction(void);//action ����� ������
void preRPOBigWriteAction(void);//action �� ������
int postRPOBigWriteAction(void);//action ����� ������
void loadRPOBigActualData(void);

COMPONENT_OBJ *rpobigcomponent;

/**************************************/
//���������� ���������� ����������� ����������� ������
/**************************************/
void constructorRPOBigComponent(COMPONENT_OBJ *rpobigcomp)
{
  rpobigcomponent = rpobigcomp;

  rpobigcomponent->countObject = 1;//�-�� �������

  rpobigcomponent->getModbusRegister = getRPOBigModbusRegister;//�������� ���������� ��������
  rpobigcomponent->getModbusBit      = getRPOBigModbusBit;//�������� ���������� ����
  rpobigcomponent->setModbusRegister = setRPOBigModbusRegister;//�������� ���������� ��������
  rpobigcomponent->setModbusBit      = setRPOBigModbusBit;//�������� ���������� ����

  rpobigcomponent->preReadAction   = preRPOBigReadAction;//action �� ������
  rpobigcomponent->postReadAction  = postRPOBigReadAction;//action ����� ������
  rpobigcomponent->preWriteAction  = preRPOBigWriteAction;//action �� ������
  rpobigcomponent->postWriteAction = postRPOBigWriteAction;//action ����� ������

  rpobigcomponent->isActiveActualData = 0;
}//prepareDVinConfig

void loadRPOBigActualData(void) {
  //ActualData
  for(int i=0; i<100; i++) tempReadArray[i] = i;
}//loadActualData() 

int getRPOBigModbusRegister(int adrReg)
{
  //�������� ���������� ��������
  if(privateRPOBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  if(rpobigcomponent->isActiveActualData) loadRPOBigActualData(); //ActualData
  rpobigcomponent->isActiveActualData = 0;

  superSetOperativMarker(rpobigcomponent, adrReg);

  return tempReadArray[adrReg-BEGIN_ADR_REGISTER];
}//getDOUTBigModbusRegister(int adrReg)
int getRPOBigModbusBit(int x)
{
  //�������� ���������� ��������
  UNUSED(x);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setRPOBigModbusRegister(int adrReg, int dataReg)
{
  //�������� ���������� ��������
  if(privateRPOBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  superSetOperativMarker(rpobigcomponent, adrReg);
  superSetTempWriteArray(dataReg);//�������� � �����

  return 0;
}//getDOUTBigModbusRegister(int adrReg)
int setRPOBigModbusBit(int x, int y)
{
  UNUSED(x);
  UNUSED(y);
  //�������� ���������� ��������
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void preRPOBigReadAction(void) {
//action �� ������
  rpobigcomponent->operativMarker[0] = -1;
  rpobigcomponent->operativMarker[1] = -1;//����������� ������
  rpobigcomponent->isActiveActualData = 1;
}//
void postRPOBigReadAction(void) {
//action ����� ������
  if(rpobigcomponent->operativMarker[0]<0) return;//�� ���� ������
}//
void preRPOBigWriteAction(void) {
//action �� ������
  rpobigcomponent->operativMarker[0] = -1;
  rpobigcomponent->operativMarker[1] = -1;//����������� ������
  rpobigcomponent->isActiveActualData = 1;
}//
int postRPOBigWriteAction(void) {
//action ����� ������
  if(rpobigcomponent->operativMarker[0]<0) return 0;//�� ���� ������
//  int offset = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//����� �������� TempWriteArray
//  int countRegister = rpobigcomponent->operativMarker[1]-rpobigcomponent->operativMarker[0]+1;
//  if(rpobigcomponent->operativMarker[1]<0) countRegister = 1;
  config_settings_modified |= MASKA_FOR_BIT(BIT_CHANGED_SETTINGS);
  restart_timeout_idle_new_settings = true;
 return 0;
}//

int privateRPOBigGetReg2(int adrReg)
{
  //��������� ������� ��������
  int count_register = REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
