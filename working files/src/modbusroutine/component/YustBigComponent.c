#include "header.h"

//��������� ������� � ����� ������
#define BEGIN_ADR_REGISTER 61968
//���� �-�� �������
#define REGISTER_FOR_OBJ NUMBER_ANALOG_CANALES

int privateYustBigGetReg2(int adrReg);

int getYustBigModbusRegister(int);//�������� ���������� ��������
int getYustBigModbusBit(int);//�������� ���������� ����
int setYustBigModbusRegister(int, int);//�������� ���������� ��������
int setYustBigModbusBit(int, int);//�������� ���������� ����

void preYustBigReadAction(void);//action �� ������
void postYustBigReadAction(void);//action ����� ������
void preYustBigWriteAction(void);//action �� ������
int postYustBigWriteAction(void);//action ����� ������
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
  for(int i=0; i<NUMBER_ANALOG_CANALES; i++) tempReadArray[i] = ustuvannja[i];
  /*
  ��������� ���������
  
  ������ ��������� ����������� � 
  ustuvannja_meas - ������ ����������� ������� (�� ������!)
  ustuvannja - ���������
  edit_ustuvannja - ��� �����������
  
  �������� ������
  � changed_ustuvannja �������� CHANGED_ETAP_EXECUTION (�� ����� �������� �� ����������� ustuvannja_meas � ustuvannja)
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
  
  ��������� ������� ������
  � ������� ustuvannja_measure_shift �������� 0 (����� ��� ���������, �� ���� ���� -1)
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
int getYustBigModbusBit(int x)
{
  //�������� ���������� ��������
  UNUSED(x);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setYustBigModbusRegister(int adrReg, int dataReg)
{
  //�������� ���������� ��������
  if(privateYustBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  superSetOperativMarker(yustbigcomponent, adrReg);
  superSetTempWriteArray(dataReg);//�������� � �����

  return 0;
}//getDOUTBigModbusRegister(int adrReg)
int setYustBigModbusBit(int x, int y)
{
  UNUSED(x);
  UNUSED(y);
  //�������� ���������� bit
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
int postYustBigWriteAction(void) {
  /*
  ��������� ���������
  
  ������ ��������� ����������� � 
  ustuvannja_meas - ������ ����������� ������� (�� ������!)
  ustuvannja - ���������
  edit_ustuvannja - ��� �����������
  
  �������� ������
  � changed_ustuvannja �������� CHANGED_ETAP_EXECUTION (�� ����� �������� �� ����������� ustuvannja_meas � ustuvannja)
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
  
  ��������� ������� ������
  � ������� ustuvannja_measure_shift �������� 0 (����� ��� ���������, �� ���� ���� -1)
  */
//action ����� ������
  if(yustbigcomponent->operativMarker[0]<0) return 0;//�� ���� ������
  int offsetTempWriteArray = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//����� �������� TempWriteArray
  int countRegister = yustbigcomponent->operativMarker[1]-yustbigcomponent->operativMarker[0]+1;
  if(yustbigcomponent->operativMarker[1]<0) countRegister = 1;

//  for(int i=0; i<countRegister; i++) ustuvannja[i] = tempWriteArray[offsetTempWriteArray+i];
  for(int i=0; i<countRegister; i++) {
  int offset = i+yustbigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;
//  int idxSubObj = offset/REGISTER_FOR_OBJ;//������ ����������
//  int idx_SIGNALS_IN = (offset%REGISTER_FOR_OBJ)/2;//������ ����� ����������

  switch(offset%(REGISTER_FOR_OBJ+1)) {//������ �������� �����
  case 0:
  case 1:
  case 2:
  case 3:
  case 4:
      ustuvannja[offset%(REGISTER_FOR_OBJ+1)] = tempWriteArray[offsetTempWriteArray+i];
  break;
  case 5:
   if(ustuvannja_measure_shift==-1) ustuvannja_measure_shift =0;
  break;
 }//switch
  }//for


  changed_ustuvannja = CHANGED_ETAP_EXECUTION;// (�� ����� �������� �� ����������� ustuvannja_meas � ustuvannja)
  config_settings_modified |= MASKA_FOR_BIT(BIT_CHANGED_SETTINGS);
  restart_timeout_idle_new_settings = true;
 return 0;
}//

int privateYustBigGetReg2(int adrReg)
{
  //��������� ������� ��������
  int count_register = REGISTER_FOR_OBJ+1;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
