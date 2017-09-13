#include "header.h"

//��������� ������� � ����� ������
#define BEGIN_ADR_REGISTER 6072
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
//void loadCGSBigActualData(void);

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

int getCGSBigModbusRegister(int adrReg)
{
  //�������� ���������� ��������
extern int pointInterface;//����� ���������� 0-USB 1-RS485
  if(privateCGSBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  superSetOperativMarker(cgsbigcomponent, adrReg);

  int offset = adrReg-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//������ ����������
  __settings_for_GROUP_ALARM *arr =  ((config_settings_modified & MASKA_FOR_BIT(BIT_USB_LOCKS)) == 0 ) ? &(((__LN_GROUP_ALARM*)(spca_of_p_prt[ID_FB_GROUP_ALARM - _ID_FB_FIRST_VAR])) + idxSubObj)->settings : (((__settings_for_GROUP_ALARM*)(sca_of_p[ID_FB_GROUP_ALARM - _ID_FB_FIRST_VAR])) + idxSubObj);
  if(pointInterface)//����� ���������� 0-USB 1-RS485
                        arr =  ((config_settings_modified & MASKA_FOR_BIT(BIT_RS485_LOCKS)) == 0 ) ? &(((__LN_GROUP_ALARM*)(spca_of_p_prt[ID_FB_GROUP_ALARM - _ID_FB_FIRST_VAR])) + idxSubObj)->settings : (((__settings_for_GROUP_ALARM*)(sca_of_p[ID_FB_GROUP_ALARM - _ID_FB_FIRST_VAR])) + idxSubObj);

  switch(offset%REGISTER_FOR_OBJ) {//������ �������� 
  case 0:
   //��������� �� item
   return arr->control &0x3;

  case 1:
   //������� ��� �� item
   return (arr->analog_input_control >> group_alarm_analog_ctrl_patten[INDEX_CTRL_GROUP_ALARM_I - _MAX_INDEX_CTRL_GROUP_ALARM_BITS_SETTINGS][0]) & ((1 << group_alarm_analog_ctrl_patten[INDEX_CTRL_GROUP_ALARM_I - _MAX_INDEX_CTRL_GROUP_ALARM_BITS_SETTINGS][1]) - 1);

  case 2:
   //���������� ���� �� item
   return arr->pickup[GROUP_ALARM_PICKUP_DELTA_I];

  case 3:
   //����� t��� �� item
   return arr->set_delay[GROUP_ALARM_SET_DELAY_DELAY]/100;
  }//switch
  return 0;
}//getDOUTBigModbusRegister(int adrReg)
int getCGSBigModbusBit(int x)
{
  //�������� ���������� ��������
  UNUSED(x);
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
int setCGSBigModbusBit(int x, int y)
{
  UNUSED(x);
  UNUSED(y);
  //�������� ���������� ��������
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
extern int pointInterface;//����� ���������� 0-USB 1-RS485
  if(cgsbigcomponent->operativMarker[0]<0) return 0;//�� ���� ������
  int offsetTempWriteArray = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//����� �������� TempWriteArray
  int countRegister = cgsbigcomponent->operativMarker[1]-cgsbigcomponent->operativMarker[0]+1;
  if(cgsbigcomponent->operativMarker[1]<0) countRegister = 1;

   __settings_for_GROUP_ALARM *arr  = (__settings_for_GROUP_ALARM*)(sca_of_p[ID_FB_GROUP_ALARM - _ID_FB_FIRST_VAR]);
   __settings_for_GROUP_ALARM *arr1 = (__settings_for_GROUP_ALARM*)(sca_of_p_edit[ID_FB_GROUP_ALARM - _ID_FB_FIRST_VAR]);
  for(int i=0; i<countRegister; i++) {
  int offset = i+cgsbigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//������ ����������
  switch(offset%REGISTER_FOR_OBJ) {//������ �������� 
   case 0://��������� �� item
     arr1[idxSubObj].control = arr[idxSubObj].control  &= (uint32_t)~0x3;
     arr1[idxSubObj].control = arr[idxSubObj].control  |= (tempWriteArray[offsetTempWriteArray+i]) & 0x3;
   break; 
  case 1:{//������� ��� �� item
      uint32_t maska = (1 << group_alarm_analog_ctrl_patten[_MAX_INDEX_CTRL_GROUP_ALARM_BITS_SETTINGS - _MAX_INDEX_CTRL_GROUP_ALARM_BITS_SETTINGS][1]) - 1;
      uint32_t shift = group_alarm_analog_ctrl_patten[_MAX_INDEX_CTRL_GROUP_ALARM_BITS_SETTINGS - _MAX_INDEX_CTRL_GROUP_ALARM_BITS_SETTINGS][0];

	  arr1[idxSubObj].analog_input_control = arr[idxSubObj].analog_input_control &= ((uint32_t)(~(maska << shift)));// | (tempWriteArray[offsetTempWriteArray+i]) << shift);
	  arr1[idxSubObj].analog_input_control = arr[idxSubObj].analog_input_control |= (tempWriteArray[offsetTempWriteArray+i]) << shift;
  } break; 
   case 2://���������� ���� �� item
    {
    arr1[idxSubObj].pickup[GROUP_ALARM_PICKUP_DELTA_I] = arr[idxSubObj].pickup[GROUP_ALARM_PICKUP_DELTA_I] = (tempWriteArray[offsetTempWriteArray+i]);
    }
   break; 
   case 3://����� t��� �� item
    arr1[idxSubObj].set_delay[GROUP_ALARM_SET_DELAY_DELAY] = arr[idxSubObj].set_delay[GROUP_ALARM_SET_DELAY_DELAY] = (tempWriteArray[offsetTempWriteArray+i])*100;
   break; 
 }//switch
  }//for
  config_settings_modified |= MASKA_FOR_BIT(BIT_CHANGED_SETTINGS);
  if(pointInterface)//����� ���������� 0-USB 1-RS485
     config_settings_modified |= MASKA_FOR_BIT(BIT_RS485_LOCKS);
  else 
     config_settings_modified |= MASKA_FOR_BIT(BIT_USB_LOCKS);
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
