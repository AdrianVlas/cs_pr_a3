#include "header.h"

//��������� ������� � ����� ������
#define BEGIN_ADR_REGISTER 6091
//���� �-�� �������
#define REGISTER_FOR_OBJ 4

int privateCGSBigGetReg2(int adrReg);

int getCGSBigModbusRegister(int);//�������� ���������� ��������
int getCGSBigModbusBit(int);//�������� ���������� ����
int setCGSBigModbusRegister(int, int);// ��������
int setCGSBigModbusBit(int, int);// ����

void setCGSBigCountObject(void);//�������� �-�� �������
void preCGSBigReadAction(void);//action �� ������
void postCGSBigReadAction(void);//action ����� ������
void preCGSBigWriteAction(void);//action �� ������
int postCGSBigWriteAction(void);//action ����� ������
void loadCGSBigActualData(void);

COMPONENT_OBJ *cgsbigcomponent;
/**************************************/
//���������� ���������� ���
/**************************************/
void constructorCGSBigComponent(COMPONENT_OBJ *cgsbigcomp)
{
  cgsbigcomponent = cgsbigcomp;

  cgsbigcomponent->countObject = 4;//�-�� �������

  cgsbigcomponent->getModbusRegister = getCGSBigModbusRegister;//�������� ���������� ��������
  cgsbigcomponent->getModbusBit      = getCGSBigModbusBit;//�������� ���������� ����
  cgsbigcomponent->setModbusRegister = setCGSBigModbusRegister;//��������
  cgsbigcomponent->setModbusBit      = setCGSBigModbusBit;// ����

  cgsbigcomponent->preReadAction   = preCGSBigReadAction;//action �� ������
  cgsbigcomponent->postReadAction  = postCGSBigReadAction;//action ����� ������
  cgsbigcomponent->preWriteAction  = preCGSBigWriteAction;//action �� ������
  cgsbigcomponent->postWriteAction = postCGSBigWriteAction;//action ����� ������

  cgsbigcomponent->isActiveActualData = 0;
}//prepareDVinConfig

void loadCGSBigActualData(void) {
  //ActualData
   __LN_GROUP_ALARM *arr = (__LN_GROUP_ALARM*)(spca_of_p_prt[ID_FB_GROUP_ALARM - _ID_FB_FIRST_VAR]);
   for(int item=0; item<cgsbigcomponent->countObject; item++) {

   //��������� �� item
   int value = arr[item].settings.control &0x3;
   tempReadArray[item*REGISTER_FOR_OBJ+0] = value;

   //������� ��� �� item
   value = (arr[item].settings.analog_input_control >> group_alarm_analog_ctrl_patten[INDEX_CTRL_GROUP_ALARM_I - _MAX_INDEX_CTRL_GROUP_ALARM_BITS_SETTINGS][0]) & ((1 << group_alarm_analog_ctrl_patten[INDEX_CTRL_GROUP_ALARM_I - _MAX_INDEX_CTRL_GROUP_ALARM_BITS_SETTINGS][1]) - 1);
   tempReadArray[item*REGISTER_FOR_OBJ+1] = value;

   //���������� ���� �� item
   value = arr[item].settings.pickup[GROUP_ALARM_PICKUP_DELTA_I];
   tempReadArray[item*REGISTER_FOR_OBJ+2] = value;

   //����� t��� �� item
   value = arr[item].settings.set_delay[GROUP_ALARM_SET_DELAY_DELAY];
   tempReadArray[item*REGISTER_FOR_OBJ+3] = value / 100;
   }//for

  /*
  ...
  
  �������������� �������� ��������� ������
  1) ���� analog_input_control ������� �� ��������
  2) ����� ������� ��� ���������� �� � ������� ���, �� ��� ��� ��������� � 
  
const uint32_t group_alarm_analog_ctrl_patten[MAX_INDEX_CTRL_GROUP_ALARM - _MAX_INDEX_CTRL_GROUP_ALARM_BITS_SETTINGS][2] = {{0, 8}};  
  
  ���������
  � ������ ������� ��� ������ ���������� � ������� �������(��������) � �������� ��� ����� ������� �������� ����� ����� � 0-��� ��� analog_input_control � ����� 8 ��. ����� [0-7]
  �� �������� ������� ����� ���������� ������:
  0 - �� �������� ������� ���������� ������ (����� �������� - �������� 0 �� �����)
  1 - I1
  2 - I2
  3 - i3
  4 - I4
  
  ����������� �����: (NUMBER_ANALOG_CANALES - 1) - �� ������� ����� - �� �������.
  
  */
}//loadActualData() 

int getCGSBigModbusRegister(int adrReg)
{
  //�������� ���������� ��������
  if(privateCGSBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  if(cgsbigcomponent->isActiveActualData) loadCGSBigActualData(); //ActualData
  cgsbigcomponent->isActiveActualData = 0;

  superSetOperativMarker(cgsbigcomponent, adrReg);

  return tempReadArray[adrReg-BEGIN_ADR_REGISTER];
}//getDOUTBigModbusRegister(int adrReg)
int getCGSBigModbusBit(int adrBit)
{
  //�������� ���������� ��������
  superSetOperativMarker(cgsbigcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setCGSBigModbusRegister(int adrReg, int dataReg)
{
  //�������� ���������� ��������
  if(privateCGSBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  superSetOperativMarker(cgsbigcomponent, adrReg);
  superSetTempWriteArray(dataReg);//�������� � �����

  switch((adrReg-BEGIN_ADR_REGISTER)%REGISTER_FOR_OBJ) {
   case 0://��������� �� item
   case 1://������� ��� �� item
   break; 
   case 2://���������� ���� �� item
    if(dataReg>500) return MARKER_ERRORDIAPAZON;
    if(dataReg<5)   return MARKER_ERRORDIAPAZON;
   break; 
   case 3://����� t��� �� item
    if(dataReg>320) return MARKER_ERRORDIAPAZON;
   break; 
  default: return MARKER_OUTPERIMETR;
  }//switch
  return 0;
}//getDOUTBigModbusRegister(int adrReg)
int setCGSBigModbusBit(int adrBit, int x)
{
  UNUSED(x);
  //�������� ���������� ��������
  superSetOperativMarker(cgsbigcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void setCGSBigCountObject(void) {
//�������� �-�� �������
}//
void preCGSBigReadAction(void) {
//action �� ������
  cgsbigcomponent->operativMarker[0] = -1;
  cgsbigcomponent->operativMarker[1] = -1;//����������� ������
  cgsbigcomponent->isActiveActualData = 1;
}//
void postCGSBigReadAction(void) {
//action ����� ������
  if(cgsbigcomponent->operativMarker[0]<0) return;//�� ���� ������
}//
void preCGSBigWriteAction(void) {
//action �� ������
  cgsbigcomponent->operativMarker[0] = -1;
  cgsbigcomponent->operativMarker[1] = -1;//����������� ������
  cgsbigcomponent->isActiveActualData = 1;
}//
int postCGSBigWriteAction(void) {
//action ����� ������
  if(cgsbigcomponent->operativMarker[0]<0) return 0;//�� ���� ������
  int offsetTempWriteArray = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//����� �������� TempWriteArray
  int countRegister = cgsbigcomponent->operativMarker[1]-cgsbigcomponent->operativMarker[0]+1;
  if(cgsbigcomponent->operativMarker[1]<0) countRegister = 1;

//   __LN_GROUP_ALARM *arr = (__LN_GROUP_ALARM*)(spca_of_p_prt[ID_FB_GROUP_ALARM - _ID_FB_FIRST_VAR]);
   __settings_for_GROUP_ALARM *arr  = (__settings_for_GROUP_ALARM*)(sca_of_p[ID_FB_GROUP_ALARM - _ID_FB_FIRST_VAR]);
   __settings_for_GROUP_ALARM *arr1 = (__settings_for_GROUP_ALARM*)(sca_of_p_edit[ID_FB_GROUP_ALARM - _ID_FB_FIRST_VAR]);
  for(int i=0; i<countRegister; i++) {
  int offset = i+cgsbigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;
  switch(offset) {//������ ��������
   case 0://��������� �� item
     arr1[0].control = arr[0].control  &= (uint32_t)~0x3;
     arr1[0].control = arr[0].control  |= (tempWriteArray[offsetTempWriteArray+i]) & 0x3;
   break; 
   case 1://������� ��� �� item
     arr1[1].analog_input_control = arr[1].analog_input_control = (tempWriteArray[offsetTempWriteArray+i]) << 
        (group_alarm_analog_ctrl_patten[INDEX_CTRL_GROUP_ALARM_I - _MAX_INDEX_CTRL_GROUP_ALARM_BITS_SETTINGS][0]) 
              & ((1 << group_alarm_analog_ctrl_patten[INDEX_CTRL_GROUP_ALARM_I - _MAX_INDEX_CTRL_GROUP_ALARM_BITS_SETTINGS][1]) - 1);
   break; 
   case 2://���������� ���� �� item
    arr1[2].pickup[GROUP_ALARM_PICKUP_DELTA_I] = arr[2].pickup[GROUP_ALARM_PICKUP_DELTA_I] = (tempWriteArray[offsetTempWriteArray+i]);
   break; 
   case 3://����� t��� �� item
    arr1[3].set_delay[GROUP_ALARM_SET_DELAY_DELAY] = arr[3].set_delay[GROUP_ALARM_SET_DELAY_DELAY] = (tempWriteArray[offsetTempWriteArray+i]);
   break; 
 }//switch
  }//for
  config_settings_modified |= MASKA_FOR_BIT(BIT_CHANGED_SETTINGS);
  restart_timeout_idle_new_settings = true;
 return 0;
}//

int privateCGSBigGetReg2(int adrReg)
{
  //��������� ������� ��������
  int count_register = cgsbigcomponent->countObject*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
