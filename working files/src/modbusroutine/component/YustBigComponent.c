#include "header.h"

//��������� ������� � ����� ������
#define BEGIN_ADR_REGISTER 61967
//���� �-�� �������
#define REGISTER_FOR_OBJ 7

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
void config_and_settingsYustBig(void);//action ���������

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
  yustbigcomponent->config_and_settings = config_and_settingsYustBig;//action ���������

  yustbigcomponent->isActiveActualData = 0;
}//prepareDVinConfig

void loadYustBigActualData(void) {
  //ActualData
  for(int i=1; i<7; i++) tempReadArray[i] = ustuvannja[i-1];
}//loadActualData() 

int getYustBigModbusRegister(int adrReg)
{
  //�������� ���������� ��������
  if(privateYustBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  if(yustbigcomponent->isActiveActualData) loadYustBigActualData(); //ActualData
  yustbigcomponent->isActiveActualData = 0;

  superSetOperativMarker(yustbigcomponent, adrReg);

  int offset = adrReg-BEGIN_ADR_REGISTER;
  if(offset==0) return MARKER_ERRORPERIMETR;//���������� ���������

  return tempReadArray[offset];
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
extern int upravlYust;//���� ���������
//action ����� ������
  if(yustbigcomponent->operativMarker[0]<0) return 0;//�� ���� ������
  int offsetTempWriteArray = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//����� �������� TempWriteArray
  int countRegister = yustbigcomponent->operativMarker[1]-yustbigcomponent->operativMarker[0]+1;
  if(yustbigcomponent->operativMarker[1]<0) countRegister = 1;

  int flag2 = 0;
  for(int i=0; i<countRegister; i++) {
  int offset = i+yustbigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;
    switch(offset%(REGISTER_FOR_OBJ)) {//������ �������� �����
     case 0://���������� ���������
      flag2 = 1;
      upravlYust = tempWriteArray[offsetTempWriteArray+i];//���� ���������
     break;
    }//switch
  }//for
 if(flag2==1 && countRegister==1) return 0;//���� ���� ���� ������ ������ ���������� ���������

  if(upravlYust!=0x1978) return 2;//���� ���������

  int flag = 0;
  for(int i=0; i<countRegister; i++) {
  int offset = i+yustbigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;

  switch(offset%(REGISTER_FOR_OBJ)) {//������ �������� �����
  case 1:
  case 2:
  case 3:
  case 4:
  case 5:
      flag = 1;
      changed_ustuvannja = CHANGED_ETAP_EXECUTION;
      ustuvannja[(offset%(REGISTER_FOR_OBJ))-1] = tempWriteArray[offsetTempWriteArray+i];
  break;
  case 6:
      if(ustuvannja_measure_shift==-1) ustuvannja_measure_shift =0;
  break;
 }//switch
  }//for

if(flag) {
   changed_ustuvannja = CHANGED_ETAP_ENDED;
   _SET_BIT(control_i2c_taskes, TASK_START_WRITE_USTUVANNJA_EEPROM_BIT);
}//if
 return 0;
}//

int privateYustBigGetReg2(int adrReg)
{
  //��������� ������� ��������
  int count_register = REGISTER_FOR_OBJ+1;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)

void config_and_settingsYustBig(void)
{
//action ���������
}

