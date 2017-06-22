#include "header.h"

//��������� ������� � ����� ������
#define BEGIN_ADR_REGISTER 61968
//���� �-�� �������
#define REGISTER_FOR_OBJ 33

int privateYustBigGetReg2(int adrReg);

int getYustBigModbusRegister(int);//�������� ���������� ��������
int getYustBigModbusBit(int);//�������� ���������� ����
int setYustBigModbusRegister(int, int);//�������� ���������� ��������
int setYustBigModbusBit(int, int);//�������� ���������� ����

void preYustBigReadAction(void);//action �� ������
void postYustBigReadAction(void);//action ����� ������
void preYustBigWriteAction(void);//action �� ������
void postYustBigWriteAction(void);//action ����� ������
void loadYustBigActualData(void);

COMPONENT_OBJ *yustbigcomponent;

/**************************************/
//���������� ���������� ���������
/**************************************/
void constructorYustBigComponent(COMPONENT_OBJ *yustbigcomp)
{
  yustbigcomponent = yustbigcomp;

  yustbigcomponent->countObject = 1;//�-�� �������

  yustbigcomponent->getModbusRegister = getYustBigModbusRegister;//�������� ���������� ��������
  yustbigcomponent->getModbusBit      = getYustBigModbusBit;//�������� ���������� ����
  yustbigcomponent->setModbusRegister = setYustBigModbusRegister;//�������� ���������� ��������
  yustbigcomponent->setModbusBit      = setYustBigModbusBit;//�������� ���������� ����

  yustbigcomponent->preReadAction   = preYustBigReadAction;//action �� ������
  yustbigcomponent->postReadAction  = postYustBigReadAction;//action ����� ������
  yustbigcomponent->preWriteAction  = preYustBigWriteAction;//action �� ������
  yustbigcomponent->postWriteAction = postYustBigWriteAction;//action ����� ������

  yustbigcomponent->isActiveActualData = 0;
}//prepareDVinConfig

void loadYustBigActualData(void) {
  //ActualData
  for(int i=0; i<100; i++) tempReadArray[i] = i;
  /*
  ������ ��������� ����������� � 
  ustuvannja_meas - ������ ����������� ������� (�� ������!)
  ustuvannja - ���������
  edit_ustuvannja - ��� �����������
  
  �������� ������
  � changed_ustuvannja �������� CHANGED_ETAP_EXECUTION (�� ����� �������� �� ������������ ustuvannja_meas � ustuvannja)
  � ������� ���������� ������� ���� � ustuvannja (����� ��������������� edit_ustuvannja �� ����� ��� ����������� � ��������� ���������� � ustuvannja)
  
  ��� ����� �������� ��������� � changed_ustuvannja �������� CHANGED_ETAP_NONE ��� ��� ustuvannja_meas ������ ���������� ustuvannja �� ������ �������������� ���� ���������
  ��� ��������� ��� � changed_ustuvannja �������� CHANGED_ETAP_ENDED. ������ ��� ������� ����������� �������
  
  ������ ����� ��������� ������ �� ������������ ���������� ������
  � ��� ����� ��������������� password_ustuvannja. �������� ��������� ���� 0x1978 � ��� �������� ����� ���������. ����� ������ �����  �������� ����� ���������.

  else if (address_data == MA_POSSIBILITY_USTUVANNJA)
  {
    ����������� ��� ��, �� ����� ��������� ������� ���������
     0 - �������� ��������� � �����������
     1 - �������� ��������� � ����������
    if (password_ustuvannja == 0x1978) temp_value = 1;
    else temp_value = 0;
  }
  else if ((address_data >= MA_ADDRESS_FIRST_USTUVANNJA ) && (address_data <= MA_ADDRESS_LAST_USTUVANNJA))
  {
    temp_value = ustuvannja[address_data - MA_ADDRESS_FIRST_USTUVANNJA ];
  }
  */
}//loadActualData() 

int getYustBigModbusRegister(int adrReg)
{
  //�������� ���������� ��������
  if(privateYustBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  if(yustbigcomponent->isActiveActualData) loadYustBigActualData(); //ActualData
  yustbigcomponent->isActiveActualData = 0;

  superSetOperativMarker(yustbigcomponent, adrReg);

  return tempReadArray[adrReg-BEGIN_ADR_REGISTER];
}//getDOUTBigModbusRegister(int adrReg)
int getYustBigModbusBit(int adrBit)
{
  //�������� ���������� ��������
  superSetOperativMarker(yustbigcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setYustBigModbusRegister(int adrReg, int dataReg)
{
  //�������� ���������� ��������
  if(privateYustBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  superSetOperativMarker(yustbigcomponent, adrReg);
  superSetTempWriteArray(dataReg);//�������� � �����

  return dataReg;
}//getDOUTBigModbusRegister(int adrReg)
int setYustBigModbusBit(int adrBit, int x)
{
  UNUSED(x);
  //�������� ���������� bit
  superSetOperativMarker(yustbigcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void preYustBigReadAction(void) {
//action �� ������
  yustbigcomponent->operativMarker[0] = -1;
  yustbigcomponent->operativMarker[1] = -1;//����������� ������
  yustbigcomponent->isActiveActualData = 1;
}//
void postYustBigReadAction(void) {
//action ����� ������
  if(yustbigcomponent->operativMarker[0]<0) return;//�� ���� ������
}//
void preYustBigWriteAction(void) {
//action �� ������
  yustbigcomponent->operativMarker[0] = -1;
  yustbigcomponent->operativMarker[1] = -1;//����������� ������
  yustbigcomponent->isActiveActualData = 1;
}//
void postYustBigWriteAction(void) {
//action ����� ������
  if(yustbigcomponent->operativMarker[0]<0) return;//�� ���� ������
//  int offset = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//����� �������� TempWriteArray
//  int countRegister = yustbigcomponent->operativMarker[1]-yustbigcomponent->operativMarker[0]+1;
//  if(yustbigcomponent->operativMarker[1]<0) countRegister = 1;
}//

int privateYustBigGetReg2(int adrReg)
{
  //��������� ������� ��������
  int count_register = REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
