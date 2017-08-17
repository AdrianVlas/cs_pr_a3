//#include <QtWidgets>
#include "header.h"

//��������� ������� � ����� ������
#define BEGIN_ADR_REGISTER 900
//���� �-�� �������
#define TOTAL_OBJ 128
#define REGISTER_FOR_OBJ 2

int privateDVBigGetReg1(int adrReg);
int privateDVBigGetReg2(int adrReg);

int getDVBigModbusRegister(int);//�������� ���������� ��������
int getDVBigModbusBit(int);//�������� ���������� ����
int setDVBigModbusRegister(int, int);// ��������
int setDVBigModbusBit(int, int);// ����

void setDVBigCountObject(void);//�������� �-�� �������
void preDVBigReadAction(void);//action �� ������
void postDVBigReadAction(void);//action ����� ������
void preDVBigWriteAction(void);//action �� ������
int postDVBigWriteAction(void);//action ����� ������
//void loadDVBigActualData(void);

COMPONENT_OBJ *dvbigcomponent;

/**************************************/
//���������� ���������� ��
/**************************************/
void constructorDVBigComponent(COMPONENT_OBJ *dvbigcomp)
{
  dvbigcomponent = dvbigcomp;

  dvbigcomponent->countObject = 0;//�-�� �������

  dvbigcomponent->getModbusRegister = getDVBigModbusRegister;//�������� ���������� ��������
  dvbigcomponent->getModbusBit      = getDVBigModbusBit;//�������� ���������� ����
  dvbigcomponent->setModbusRegister = setDVBigModbusRegister;// ��������
  dvbigcomponent->setModbusBit      = setDVBigModbusBit;// ����

  dvbigcomponent->preReadAction   = preDVBigReadAction;//action �� ������
  dvbigcomponent->postReadAction  = postDVBigReadAction;//action ����� ������
  dvbigcomponent->preWriteAction  = preDVBigWriteAction;//action �� ������
  dvbigcomponent->postWriteAction = postDVBigWriteAction;//action ����� ������

  dvbigcomponent->isActiveActualData = 0;
}//prepareDVinConfig
/*
void loadDVBigActualData(void) {
 setDVBigCountObject(); //�������� �-�� �������

  //ActualData
   __LN_INPUT *arr = (__LN_INPUT*)(spca_of_p_prt[ID_FB_INPUT - _ID_FB_FIRST_VAR]);
   for(int item=0; item<dvbigcomponent->countObject; item++) {
   int value = (((arr[item].settings.control & (1 << INDEX_CTRL_INPUT_TYPE_SIGNAL)) !=0) << 0) | (1 << 1) | ((V110_V220 != 0) << 2);
   tempReadArray[item*REGISTER_FOR_OBJ+0] = value;
   value = arr[item].settings.set_delay[INPUT_SET_DELAY_DOPUSK];
   tempReadArray[item*REGISTER_FOR_OBJ+1] = value;
  }//for
*/
  /*
  1. ������ ��������� �������� ��������� ��������������� ����� ��������� �� � ��� Small
  2. ���� �������� � ���������� ***_prt, �� ��� �������� __LN_XXX � ��� ����� �������� ��� �������� __settings_for_���
  __LN_XXX ������ � ���� _settings_for_���
  
  3. 
  enum _XXX__output_signals - ������������ ������ ������ (���������� � 0 ��� ��� �������������� ��'���� �����, ��� ����� ��������� � 1, ����� ������ 1 ��� ������������ ��'���� ��� ������ �������� ��� ����������� ������������� ��'����)
  enum _XXX_d_trigger  - ����� ��� �����
  enum _XXX_input_signal - ������������ ������ �����
  enum _settings_delay_of_XXX - ������������ ��� ��������
  enum __index_ctrl_xxx - ������������ ��� "������" ���������
  enum _settings_pickup_of_XXX ������������ ��� �������
  
  4. ���� �������������
  uint32_t param[XXX_SIGNALS_IN] - ������ ������, ���� ���������� �� ����� ����. �������� (id; N; out) id - � enum _id_fb; N � out ����������� � 1-��
  
  int32_t pickup[GROUP_ALARM_PICKUPS] - ������� (� ������� �� ��-�������)
  int32_t set_delay[XXX_SET_DELAYS] - �������� (� ������� �� ��)
  uint32_t control - ����������
  uint32_t analog_input_control - ��� ��� ���� ���������� ������
  
  */
//}//loadActualData() 

int getDVBigModbusRegister(int adrReg)
{
extern int pointInterface;//����� ���������� 0-USB 1-RS485
  //�������� ���������� ��������
  if(privateDVBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(dvbigcomponent->isActiveActualData) setDVBigCountObject(); //�-�� �������
  dvbigcomponent->isActiveActualData = 0;
  if(privateDVBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;//MARKER_ERRORPERIMETR;

  superSetOperativMarker(dvbigcomponent, adrReg);
/*
   __LN_INPUT *arr = (__LN_INPUT*)(spca_of_p_prt[ID_FB_INPUT - _ID_FB_FIRST_VAR]);
  int offset = adrReg-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//������ ����������
  switch(offset%REGISTER_FOR_OBJ) {//������ �������� 
   case 0:
     return (((arr[idxSubObj].settings.control & (1 << INDEX_CTRL_INPUT_TYPE_SIGNAL)) !=0) << 0) | (1 << 1) | ((V110_V220 != 0) << 2);
   case 1:
     return arr[idxSubObj].settings.set_delay[INPUT_SET_DELAY_DOPUSK];
 }//switch
*/

  int offset = adrReg-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//������ ����������
  __settings_for_INPUT *arr =  ((config_settings_modified & MASKA_FOR_BIT(BIT_USB_LOCKS)) == 0 ) ? &(((__LN_INPUT*)(spca_of_p_prt[ID_FB_INPUT - _ID_FB_FIRST_VAR])) + idxSubObj)->settings : (((__settings_for_INPUT*)(sca_of_p[ID_FB_INPUT - _ID_FB_FIRST_VAR])) + idxSubObj);
  if(pointInterface)//����� ���������� 0-USB 1-RS485
                        arr =  ((config_settings_modified & MASKA_FOR_BIT(BIT_RS485_LOCKS)) == 0 ) ? &(((__LN_INPUT*)(spca_of_p_prt[ID_FB_INPUT - _ID_FB_FIRST_VAR])) + idxSubObj)->settings : (((__settings_for_INPUT*)(sca_of_p[ID_FB_INPUT - _ID_FB_FIRST_VAR])) + idxSubObj);
  switch(offset%REGISTER_FOR_OBJ) {//������ �������� 
   case 0:
//     return (((arr[idxSubObj].settings.control & (1 << INDEX_CTRL_INPUT_TYPE_SIGNAL)) !=0) << 0) | (1 << 1) | ((V110_V220 != 0) << 2);
     return (((arr->control & (1 << INDEX_CTRL_INPUT_TYPE_SIGNAL)) !=0) << 0) | (1 << 1) | ((V110_V220 != 0) << 2);
   case 1:
//     return arr[idxSubObj].settings.set_delay[INPUT_SET_DELAY_DOPUSK];
     return arr->set_delay[INPUT_SET_DELAY_DOPUSK];
 }//switch

  return 0;
}//getDOUTBigModbusRegister(int adrReg)
int getDVBigModbusBit(int x)
{
  //�������� ���������� ��������
  UNUSED(x);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setDVBigModbusRegister(int adrReg, int dataReg)
{
  //�������� ���������� ��������
  if(privateDVBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(dvbigcomponent->isActiveActualData) setDVBigCountObject(); //�-�� �������
  dvbigcomponent->isActiveActualData = 0;
  if(privateDVBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;//MARKER_ERRORPERIMETR;

  superSetOperativMarker(dvbigcomponent, adrReg);
  superSetTempWriteArray(dataReg);//�������� � �����

  switch((adrReg-BEGIN_ADR_REGISTER)%REGISTER_FOR_OBJ) {
   case 0:
   break; 
   case 1:
    if(dataReg>60) return MARKER_ERRORDIAPAZON;
   break; 
  default: return MARKER_OUTPERIMETR;
  }//switch
  return 0;
}//getDOUTBigModbusRegister(int adrReg)
int setDVBigModbusBit(int x, int y)
{
  UNUSED(x);
  UNUSED(y);
  //�������� ���������� ��������
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void setDVBigCountObject(void) {
//�������� �-�� �������
  int cntObj = current_config.n_input; //ʳ������ ���������� �����
  if(cntObj<0) return;
  if(cntObj>TOTAL_OBJ) return;
  dvbigcomponent->countObject = cntObj;
}//
void preDVBigReadAction(void) {
//action �� ������
  dvbigcomponent->operativMarker[0] = -1;
  dvbigcomponent->operativMarker[1] = -1;//����������� ������
  dvbigcomponent->isActiveActualData = 1;
}//
void postDVBigReadAction(void) {
//action ����� ������
  if(dvbigcomponent->operativMarker[0]<0) return;//�� ���� ������
}//
void preDVBigWriteAction(void) {
//action �� ������
  dvbigcomponent->operativMarker[0] = -1;
  dvbigcomponent->operativMarker[1] = -1;//����������� ������
  dvbigcomponent->isActiveActualData = 1;
}//
int postDVBigWriteAction(void) {
//action ����� ������
  if(dvbigcomponent->operativMarker[0]<0) return 0;//�� ���� ������
  int offsetTempWriteArray = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//����� �������� TempWriteArray
  int countRegister = dvbigcomponent->operativMarker[1]-dvbigcomponent->operativMarker[0]+1;
  if(dvbigcomponent->operativMarker[1]<0) countRegister = 1;

   __settings_for_INPUT *arr  = (__settings_for_INPUT*)(sca_of_p[ID_FB_INPUT - _ID_FB_FIRST_VAR]);
   __settings_for_INPUT *arr1 = (__settings_for_INPUT*)(sca_of_p_edit[ID_FB_INPUT - _ID_FB_FIRST_VAR]);
  for(int i=0; i<countRegister; i++) {
  int offset = i+dvbigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//������ ����������
  switch(offset%REGISTER_FOR_OBJ) {//������ �������� 
   case 0://control
        arr1[idxSubObj].control = arr[idxSubObj].control = (tempWriteArray[offsetTempWriteArray+i]);
   break;
   case 1://
        arr1[idxSubObj].set_delay[INPUT_SET_DELAY_DOPUSK] = arr[idxSubObj].set_delay[INPUT_SET_DELAY_DOPUSK] = (tempWriteArray[offsetTempWriteArray+i]);
   break;
 }//switch
  }//for
  config_settings_modified |= MASKA_FOR_BIT(BIT_CHANGED_SETTINGS);
  restart_timeout_idle_new_settings = true;
 return 0;
}//

int privateDVBigGetReg1(int adrReg)
{
  //��������� ���������� ��������
  int count_register = dvbigcomponent->countObject*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg1(int adrReg)
int privateDVBigGetReg2(int adrReg)
{
  //��������� ������� ��������
  int count_register = TOTAL_OBJ*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
