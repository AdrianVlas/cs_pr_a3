#include "header.h"

//��������� ������� � ����� ������
#define BEGIN_ADR_REGISTER 13512
//���� �-�� �������
#define TOTAL_OBJ 128
#define REGISTER_FOR_OBJ 2

int privateNOTBigGetReg1(int adrReg);
int privateNOTBigGetReg2(int adrReg);

int getNOTBigModbusRegister(int);//�������� ���������� ��������
int getNOTBigModbusBit(int);//�������� ���������� ����
int setNOTBigModbusRegister(int, int);//�������� ���������� ��������
int setNOTBigModbusBit(int, int);//�������� ���������� ����

void setNOTBigCountObject(void);//�������� �-�� �������
void preNOTBigReadAction(void);//action �� ������
void postNOTBigReadAction(void);//action ����� ������
void preNOTBigWriteAction(void);//action �� ������
int postNOTBigWriteAction(void);//action ����� ������
void loadNOTBigActualData(void);
void repairEditArrayNOT(int countRegister, __settings_for_NOT *arr, __settings_for_NOT *arr1);
void config_and_settingsNOTBig(void);//action ���������

COMPONENT_OBJ *notbigcomponent;

/**************************************/
//���������� ���������� NOT
/**************************************/
void constructorNOTBigComponent(COMPONENT_OBJ *notbigcomp)
{
  notbigcomponent = notbigcomp;

  notbigcomponent->countObject = 0;//�-�� �������

  notbigcomponent->getModbusRegister = getNOTBigModbusRegister;//�������� ���������� ��������
  notbigcomponent->getModbusBit      = getNOTBigModbusBit;//�������� ���������� ����
  notbigcomponent->setModbusRegister = setNOTBigModbusRegister;//�������� ���������� ��������
  notbigcomponent->setModbusBit      = setNOTBigModbusBit;//�������� ���������� ����

  notbigcomponent->preReadAction   = preNOTBigReadAction;//action �� ������
  notbigcomponent->postReadAction  = postNOTBigReadAction;//action ����� ������
  notbigcomponent->preWriteAction  = preNOTBigWriteAction;//action �� ������
  notbigcomponent->postWriteAction = postNOTBigWriteAction;//action ����� ������
  notbigcomponent->config_and_settings = config_and_settingsNOTBig;//action ���������

  notbigcomponent->isActiveActualData = 0;
}//prepareDVinConfig

int getNOTBigModbusRegister(int adrReg)
{
  //�������� ���������� ��������
extern int pointInterface;  
  if(privateNOTBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(notbigcomponent->isActiveActualData) setNOTBigCountObject(); //�-�� �������
  notbigcomponent->isActiveActualData = 0;
  if(privateNOTBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  superSetOperativMarker(notbigcomponent, adrReg);

  int offset = adrReg-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//������ ����������
  __settings_for_NOT *arr =  ((config_settings_modified & MASKA_FOR_BIT(BIT_USB_LOCKS)) == 0 ) ? &(((__LN_NOT*)(spca_of_p_prt[ID_FB_NOT - _ID_FB_FIRST_VAR])) + idxSubObj)->settings : (((__settings_for_NOT*)(sca_of_p[ID_FB_NOT - _ID_FB_FIRST_VAR])) + idxSubObj);
  if(pointInterface)//����� ���������� 0-USB 1-RS485
                        arr =  ((config_settings_modified & MASKA_FOR_BIT(BIT_RS485_LOCKS)) == 0 ) ? &(((__LN_NOT*)(spca_of_p_prt[ID_FB_NOT - _ID_FB_FIRST_VAR])) + idxSubObj)->settings : (((__settings_for_NOT*)(sca_of_p[ID_FB_NOT - _ID_FB_FIRST_VAR])) + idxSubObj);

  switch(offset%REGISTER_FOR_OBJ) {//������ �������� 
   case 0:
        return arr->param[0] & 0xffff;//
   case 1:
        return (arr->param[0] >> 16) & 0x7fff;//
  }//switch
  return 0;
}//getDOUTBigModbusRegister(int adrReg)
int getNOTBigModbusBit(int x)
{
  //�������� ���������� ��������
  UNUSED(x);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setNOTBigModbusRegister(int adrReg, int dataReg)
{
  //�������� ���������� ��������
  if(privateNOTBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(notbigcomponent->isActiveActualData) setNOTBigCountObject(); //�-�� �������
  notbigcomponent->isActiveActualData = 0;
  if(privateNOTBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  superSetOperativMarker(notbigcomponent, adrReg);
  superSetTempWriteArray(dataReg);//�������� � �����

  switch((adrReg-BEGIN_ADR_REGISTER)%REGISTER_FOR_OBJ) {
   case 0:
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
   break; 
   case 1:
    //�������� ���������� ������������
    if(superControlParam(dataReg)) return MARKER_ERRORDIAPAZON;
   break; 
  default: return MARKER_OUTPERIMETR;
  }//switch
  return 0;
}//getDOUTBigModbusRegister(int adrReg)
int setNOTBigModbusBit(int x, int y)
{
  UNUSED(x);
  UNUSED(y);
  //�������� ���������� ��������
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void setNOTBigCountObject(void) {
//�������� �-�� �������
  int cntObj = current_config.n_not;   //ʳ������ �������� "��"
  if(cntObj<0) return;
  if(cntObj>TOTAL_OBJ) return;
  notbigcomponent->countObject = cntObj;
}//
void preNOTBigReadAction(void) {
//action �� ������
  notbigcomponent->operativMarker[0] = -1;
  notbigcomponent->operativMarker[1] = -1;//����������� ������
  notbigcomponent->isActiveActualData = 1;
}//
void postNOTBigReadAction(void) {
//action ����� ������
  if(notbigcomponent->operativMarker[0]<0) return;//�� ���� ������
}//
void preNOTBigWriteAction(void) {
//action �� ������
  notbigcomponent->operativMarker[0] = -1;
  notbigcomponent->operativMarker[1] = -1;//����������� ������
  notbigcomponent->isActiveActualData = 1;
}//
int postNOTBigWriteAction(void) {
//action ����� ������
extern int pointInterface;//����� ���������� 0-USB 1-RS485
  if(notbigcomponent->operativMarker[0]<0) return 0;//�� ���� ������
  int offsetTempWriteArray = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//����� �������� TempWriteArray
  int countRegister = notbigcomponent->operativMarker[1]-notbigcomponent->operativMarker[0]+1;
  if(notbigcomponent->operativMarker[1]<0) countRegister = 1;

   __settings_for_NOT *arr  = (__settings_for_NOT*)(sca_of_p[ID_FB_NOT - _ID_FB_FIRST_VAR]);
   __settings_for_NOT *arr1 = (__settings_for_NOT*)(sca_of_p_edit[ID_FB_NOT - _ID_FB_FIRST_VAR]);
//�������� edit ������
  for(int i=0; i<countRegister; i++) {
  int offset = i+notbigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//������ ����������
  switch(offset%2) {//������ �������� �����
  case 0:

        arr1[idxSubObj].param[0]  &= (uint32_t)~0xffff;
        arr1[idxSubObj].param[0]  |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
  break;
  case 1:

        arr1[idxSubObj].param[0]  &= (uint32_t)~(0x7fff<<16);
        arr1[idxSubObj].param[0]  |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
  break;
  }//switch
  }//for

  //�������� ����������
  for(int i=0; i<countRegister; i++) {
  int offset = i+notbigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//������ ����������

  switch(offset%2) {//������ �������� �����
  case 0:
  case 1:
        if(superValidParam(arr1[idxSubObj].param[0])) 
                {//�������� ����������
                repairEditArrayNOT(countRegister, arr, arr1);//������������ edit ������
                return 2;//����
        }//if
  break;
 }//switch
  }//for

//�������� ������� - ��������������
  for(int i=0; i<countRegister; i++) {
  int offset = i+notbigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//������ ����������
  switch(offset%2) {//������ �������� �����
  case 0:

        arr1[idxSubObj].param[0] = arr[idxSubObj].param[0] &= (uint32_t)~0xffff;
        arr1[idxSubObj].param[0] = arr[idxSubObj].param[0] |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
  break;
  case 1:

        arr1[idxSubObj].param[0] = arr[idxSubObj].param[0] &= (uint32_t)~(0x7fff<<16);
        arr1[idxSubObj].param[0] = arr[idxSubObj].param[0] |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
  break;
  }//switch
  }//for

  config_settings_modified |= MASKA_FOR_BIT(BIT_CHANGED_SCHEMATIC);
  if(pointInterface)//����� ���������� 0-USB 1-RS485
     config_settings_modified |= MASKA_FOR_BIT(BIT_RS485_LOCKS);
  else 
     config_settings_modified |= MASKA_FOR_BIT(BIT_USB_LOCKS);
  restart_timeout_idle_new_settings = true;
 return 0;
}//

void repairEditArrayNOT(int countRegister, __settings_for_NOT *arr, __settings_for_NOT *arr1) {
  //������������ edit ������
  for(int i=0; i<countRegister; i++) {
  int offset = i+notbigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//������ ����������

  switch(offset%2) {//������ �������� �����
  case 0:
  case 1:
        arr1[idxSubObj].param[0] = arr[idxSubObj].param[0];
  break;
 }//switch
  }//for
}//repairEditArray(int countRegister, __settings_for_NOT *arr, __settings_for_NOT *arr1) 

int privateNOTBigGetReg1(int adrReg)
{
  //��������� ���������� ��������
  int count_register = notbigcomponent->countObject*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg1(int adrReg)
int privateNOTBigGetReg2(int adrReg)
{
  //��������� ������� ��������
  int count_register = TOTAL_OBJ*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)

void config_and_settingsNOTBig(void)
{
//action ���������
}

