#include "header.h"

//��������� ������� � ����� ������
#define BEGIN_ADR_REGISTER 4664
#define REGISTER_FOR_OBJ 6

int getRESDBigModbusRegister(int);//�������� ���������� ��������
int getRESDBigModbusBit(int);//�������� ���������� ����
int setRESDBigModbusRegister(int, int);//�������� ���������� ��������
int setRESDBigModbusBit(int, int);//�������� ���������� ����

void setRESDBigCountObject(void);//�������� �-�� �������
void preRESDBigReadAction(void);//action �� ������
void postRESDBigReadAction(void);//action ����� ������
void preRESDBigWriteAction(void);//action �� ������
int postRESDBigWriteAction(void);//action ����� ������
void loadRESDBigActualData(void);

int privateRESDBigGetReg2(int adrReg);

COMPONENT_OBJ *resdbigcomponent;

/**************************************/
//���������� ���������� ��������� ���������������� run\error
/**************************************/
void constructorRESDBigComponent(COMPONENT_OBJ *resdbigcomp)
{
  resdbigcomponent = resdbigcomp;

  resdbigcomponent->countObject = 1;//�-�� �������

  resdbigcomponent->getModbusRegister = getRESDBigModbusRegister;//�������� ���������� ��������
  resdbigcomponent->getModbusBit      = getRESDBigModbusBit;//�������� ���������� ����
  resdbigcomponent->setModbusRegister = setRESDBigModbusRegister;//�������� ���������� ��������
  resdbigcomponent->setModbusBit      = setRESDBigModbusBit;//�������� ���������� ����

  resdbigcomponent->preReadAction   = preRESDBigReadAction;//action �� ������
  resdbigcomponent->postReadAction  = postRESDBigReadAction;//action ����� ������
  resdbigcomponent->preWriteAction  = preRESDBigWriteAction;//action �� ������
  resdbigcomponent->postWriteAction = postRESDBigWriteAction;//action ����� ������

  resdbigcomponent->isActiveActualData = 0;
}//prepareDVinConfig

void loadRESDBigActualData(void) {
  //ActualData
  for(int i=0; i<100; i++) tempReadArray[i] = i;
  /*
  �������/����� ��������� � 
  settings_fix_prt/settings_fix/settings_fix_edit.param[����]
  
  ���������� ������ ����� ��������� � enum _FIX_BLOCK_input_signals
  */
}//loadActualData() 

int getRESDBigModbusRegister(int adrReg)
{
  //�������� ���������� ��������
  if(privateRESDBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  if(resdbigcomponent->isActiveActualData) loadRESDBigActualData(); //ActualData
  resdbigcomponent->isActiveActualData = 0;

  superSetOperativMarker(resdbigcomponent, adrReg);

  return tempReadArray[adrReg-BEGIN_ADR_REGISTER];
}//getDVModbusRegister(int adrReg)
int getRESDBigModbusBit(int adrBit)
{
  //�������� ���������� ��������
  superSetOperativMarker(resdbigcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDVModbusRegister(int adrReg)
int setRESDBigModbusRegister(int adrReg, int dataReg)
{
  //�������� ���������� ��������
  if(privateRESDBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  superSetOperativMarker(resdbigcomponent, adrReg);
  superSetTempWriteArray(dataReg);//�������� � �����

  switch((adrReg-BEGIN_ADR_REGISTER)%REGISTER_FOR_OBJ) {
   case 0:
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
   break; 
   case 1:
   break; 
   case 2:
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
   break; 
   case 3:
   break; 
   case 4:
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
   break; 
   case 5:
   break; 
  default: return MARKER_OUTPERIMETR;
  }//switch
  return 0;
}//getDVModbusRegister(int adrReg)
int setRESDBigModbusBit(int adrBit, int x)
{
  UNUSED(x);
  //�������� ���������� ��������
  superSetOperativMarker(resdbigcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDVModbusRegister(int adrReg)

void setRESDBigCountObject(void) {
//�������� �-�� �������
}//
void preRESDBigReadAction(void) {
//action �� ������
  resdbigcomponent->operativMarker[0] = -1;
  resdbigcomponent->operativMarker[1] = -1;//����������� ������
  resdbigcomponent->isActiveActualData = 1;
}//
void postRESDBigReadAction(void) {
//action ����� ������
  if(resdbigcomponent->operativMarker[0]<0) return;//�� ���� ������
}//
void preRESDBigWriteAction(void) {
//action �� ������
  resdbigcomponent->operativMarker[0] = -1;
  resdbigcomponent->operativMarker[1] = -1;//����������� ������
  resdbigcomponent->isActiveActualData = 1;
}//
int postRESDBigWriteAction(void) {
//action ����� ������
  if(resdbigcomponent->operativMarker[0]<0) return 0;//�� ���� ������
//  int offset = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//����� �������� TempWriteArray
//  int countRegister = resdbigcomponent->operativMarker[1]-resdbigcomponent->operativMarker[0]+1;
//  if(resdbigcomponent->operativMarker[1]<0) countRegister = 1;

  config_settings_modified |= MASKA_FOR_BIT(BIT_CHANGED_SETTINGS);
  restart_timeout_idle_new_settings = true;
 return 0;
}//

int privateRESDBigGetReg2(int adrReg)
{
  //��������� ������� ��������
  int count_register = REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
