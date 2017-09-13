#include "header.h"

//��������� ������� � ����� ������
#define BEGIN_ADR_REGISTER 6088
//���� �-�� �������
#define TOTAL_OBJ 128
#define REGISTER_FOR_OBJ 6

int privateMFTBigGetReg1(int adrReg);
int privateMFTBigGetReg2(int adrReg);

int getMFTBigModbusRegister(int);//�������� ���������� ��������
int getMFTBigModbusBit(int);//�������� ���������� ����
int setMFTBigModbusRegister(int, int);//�������� ���������� ��������
int setMFTBigModbusBit(int, int);//�������� ���������� ����

void setMFTBigCountObject(void);//�������� �-�� �������
void preMFTBigReadAction(void);//action �� ������
void postMFTBigReadAction(void);//action ����� ������
void preMFTBigWriteAction(void);//action �� ������
int postMFTBigWriteAction(void);//action ����� ������
void repairEditArrayMFT(int countRegister, __settings_for_TIMER *arr, __settings_for_TIMER *arr1);

COMPONENT_OBJ *mftbigcomponent;

/**************************************/
//���������� ���������� ���
/**************************************/
void constructorMFTBigComponent(COMPONENT_OBJ *mftbigcomp)
{
  mftbigcomponent = mftbigcomp;

  mftbigcomponent->countObject = 0;//�-�� �������

  mftbigcomponent->getModbusRegister = getMFTBigModbusRegister;//�������� ���������� ��������
  mftbigcomponent->getModbusBit      = getMFTBigModbusBit;//�������� ���������� ����
  mftbigcomponent->setModbusRegister = setMFTBigModbusRegister;//�������� ���������� ��������
  mftbigcomponent->setModbusBit      = setMFTBigModbusBit;//�������� ���������� ����

  mftbigcomponent->preReadAction   = preMFTBigReadAction;//action �� ������
  mftbigcomponent->postReadAction  = postMFTBigReadAction;//action ����� ������
  mftbigcomponent->preWriteAction  = preMFTBigWriteAction;//action �� ������
  mftbigcomponent->postWriteAction = postMFTBigWriteAction;//action ����� ������

  mftbigcomponent->isActiveActualData = 0;
}//prepareDVinConfig

int getMFTBigModbusRegister(int adrReg)
{
  //�������� ���������� ��������
extern int pointInterface;//����� ���������� 0-USB 1-RS485
  if(privateMFTBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(mftbigcomponent->isActiveActualData) setMFTBigCountObject(); //�-�� �������
  mftbigcomponent->isActiveActualData = 0;
  if(privateMFTBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  superSetOperativMarker(mftbigcomponent, adrReg);

  int offset = adrReg-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//������ ����������
  __settings_for_TIMER *arr =  ((config_settings_modified & MASKA_FOR_BIT(BIT_USB_LOCKS)) == 0 ) ? &(((__LN_TIMER*)(spca_of_p_prt[ID_FB_TIMER - _ID_FB_FIRST_VAR])) + idxSubObj)->settings : (((__settings_for_TIMER*)(sca_of_p[ID_FB_TIMER - _ID_FB_FIRST_VAR])) + idxSubObj);
  if(pointInterface)//����� ���������� 0-USB 1-RS485
                        arr =  ((config_settings_modified & MASKA_FOR_BIT(BIT_RS485_LOCKS)) == 0 ) ? &(((__LN_TIMER*)(spca_of_p_prt[ID_FB_TIMER - _ID_FB_FIRST_VAR])) + idxSubObj)->settings : (((__settings_for_TIMER*)(sca_of_p[ID_FB_TIMER - _ID_FB_FIRST_VAR])) + idxSubObj);

  switch(offset%REGISTER_FOR_OBJ) {//������ �������� 
   case 0:
   //������ �����  item
    return arr->set_delay[TIMER_SET_DELAY_PAUSE]/10;

   case 1:
   //������ ������   item
   return arr->set_delay[TIMER_SET_DELAY_WORK]/10;

   case 2:
   //MFT-IN 1 0 item
   return arr->param[TIMER_LOGIC_INPUT] & 0xffff;

   case 3:
   return  (arr->param[TIMER_LOGIC_INPUT] >> 16) & 0x7fff;

   case 4:
   //Reset-I  0 item
   return arr->param[TIMER_RESET] & 0xffff;
   case 5:
   return (arr->param[TIMER_RESET] >> 16) & 0x7fff;
  }//switch
  return 0;
}//getDOUTBigModbusRegister(int adrReg)
int getMFTBigModbusBit(int x)
{
  //�������� ���������� ��������
  UNUSED(x);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setMFTBigModbusRegister(int adrReg, int dataReg)
{
  //�������� ���������� ��������
extern int upravlSetting;//���� Setting
extern int upravlSchematic;//���� Shematic
  if(privateMFTBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(mftbigcomponent->isActiveActualData) setMFTBigCountObject(); //�-�� �������
  mftbigcomponent->isActiveActualData = 0;
  if(privateMFTBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  superSetOperativMarker(mftbigcomponent, adrReg);
  superSetTempWriteArray(dataReg);//�������� � �����

  switch((adrReg-BEGIN_ADR_REGISTER)%REGISTER_FOR_OBJ) {
   case 0:
    upravlSetting = 1;//���� Setting
    if(((unsigned short)dataReg)>60000) return MARKER_ERRORDIAPAZON;
   break; 
   case 1:
     upravlSetting = 1;//���� Setting
    if(((unsigned short)dataReg)>60000) return MARKER_ERRORDIAPAZON;
   break; 
   case 2:
    upravlSchematic = 1;//���� Shematic
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
   break; 
   case 3:
    //�������� ���������� ������������
    upravlSchematic = 1;//���� Shematic
    if(superControlParam(dataReg)) return MARKER_ERRORDIAPAZON;
   break; 
   case 4:
    upravlSchematic = 1;//���� Shematic
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
   break; 
   case 5:
    //�������� ���������� ������������
    upravlSchematic = 1;//���� Shematic
    if(superControlParam(dataReg)) return MARKER_ERRORDIAPAZON;
   break; 
  default: return MARKER_OUTPERIMETR;
  }//switch
  return 0;
}//getDOUTBigModbusRegister(int adrReg)
int setMFTBigModbusBit(int x, int y)
{
  UNUSED(x);
  UNUSED(y);
  //�������� ���������� ��������
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void setMFTBigCountObject(void) {
//�������� �-�� �������
  int cntObj = current_config.n_timer;   //ʳ������ �������
  if(cntObj<0) return;
  if(cntObj>TOTAL_OBJ) return;
  mftbigcomponent->countObject = cntObj;
}//
void preMFTBigReadAction(void) {
//action �� ������
  mftbigcomponent->operativMarker[0] = -1;
  mftbigcomponent->operativMarker[1] = -1;//����������� ������
  mftbigcomponent->isActiveActualData = 1;
}//
void postMFTBigReadAction(void) {
//action ����� ������
  if(mftbigcomponent->operativMarker[0]<0) return;//�� ���� ������
}//
void preMFTBigWriteAction(void) {
//action �� ������
  mftbigcomponent->operativMarker[0] = -1;
  mftbigcomponent->operativMarker[1] = -1;//����������� ������
  mftbigcomponent->isActiveActualData = 1;
}//
int postMFTBigWriteAction(void) {
//action ����� ������
extern int upravlSetting;//���� Setting
extern int upravlSchematic;//���� Shematic
extern int pointInterface;//����� ���������� 0-USB 1-RS485
  if(mftbigcomponent->operativMarker[0]<0) return 0;//�� ���� ������
  int offsetTempWriteArray = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//����� �������� TempWriteArray
  int countRegister = mftbigcomponent->operativMarker[1]-mftbigcomponent->operativMarker[0]+1;
  if(mftbigcomponent->operativMarker[1]<0) countRegister = 1;

   __settings_for_TIMER *arr  = (__settings_for_TIMER*)(sca_of_p[ID_FB_TIMER - _ID_FB_FIRST_VAR]);
   __settings_for_TIMER *arr1 = (__settings_for_TIMER*)(sca_of_p_edit[ID_FB_TIMER - _ID_FB_FIRST_VAR]);
//�������� edit ������
  for(int i=0; i<countRegister; i++) {
  int offset = i+mftbigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//������ ����������
  switch(offset%REGISTER_FOR_OBJ) {//������ �������� 
   case 2://MFT-IN 0 item
        arr1[idxSubObj].param[TIMER_LOGIC_INPUT]  &= (uint32_t)~0xffff;
        arr1[idxSubObj].param[TIMER_LOGIC_INPUT]  |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
   break;
   case 3://MFT-IN 1 item
        arr1[idxSubObj].param[TIMER_LOGIC_INPUT]  &= (uint32_t)~(0x7fff<<16);
        arr1[idxSubObj].param[TIMER_LOGIC_INPUT]  |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
   break; 

   case 4://Reset-I 0 item
        arr1[idxSubObj].param[TIMER_RESET]  &= (uint32_t)~0xffff;
        arr1[idxSubObj].param[TIMER_RESET]  |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
   break;
   case 5://Reset-I 1 item
        arr1[idxSubObj].param[TIMER_RESET]  &= (uint32_t)~(0x7fff<<16);
        arr1[idxSubObj].param[TIMER_RESET]  |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
   break; 
 }//switch
  }//for

  //�������� ����������
  for(int i=0; i<countRegister; i++) {
  int offset = i+mftbigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//������ ����������
  switch(offset%REGISTER_FOR_OBJ) {//������ �������� 

   case 2://MFT-IN 0 item
   case 3://MFT-IN 1 item
        if(superValidParam(arr1[idxSubObj].param[TIMER_LOGIC_INPUT])) 
                {//�������� ����������
                repairEditArrayMFT(countRegister, arr, arr1);//������������ edit ������
                return 2;//����
        }//if
  break;

   case 4://Reset-I 0 item
   case 5://Reset-I 1 item
        if(superValidParam(arr1[idxSubObj].param[TIMER_RESET]))
                {//�������� ����������
                repairEditArrayMFT(countRegister, arr, arr1);//������������ edit ������
                return 2;//����
        }//if
  break;

 }//switch
  }//for

//�������� ������� - ��������������
  for(int i=0; i<countRegister; i++) {
  int offset = i+mftbigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//������ ����������
  switch(offset%REGISTER_FOR_OBJ) {//������ �������� 
   case 0://������ �����
    {
    arr1[idxSubObj].set_delay[TIMER_SET_DELAY_PAUSE] = arr[idxSubObj].set_delay[TIMER_SET_DELAY_PAUSE] = ((unsigned short)(tempWriteArray[offsetTempWriteArray+i]))*10;
    }
   break;
   case 1://������ ������
    {
    arr1[idxSubObj].set_delay[TIMER_SET_DELAY_WORK] = arr[idxSubObj].set_delay[TIMER_SET_DELAY_WORK] = ((unsigned short)(tempWriteArray[offsetTempWriteArray+i]))*10;
    }
   break;

   case 2://MFT-IN 0 item
        arr1[idxSubObj].param[TIMER_LOGIC_INPUT] = arr[idxSubObj].param[TIMER_LOGIC_INPUT] &= (uint32_t)~0xffff;
        arr1[idxSubObj].param[TIMER_LOGIC_INPUT] = arr[idxSubObj].param[TIMER_LOGIC_INPUT] |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
   break;
   case 3://MFT-IN 1 item
        arr1[idxSubObj].param[TIMER_LOGIC_INPUT] = arr[idxSubObj].param[TIMER_LOGIC_INPUT] &= (uint32_t)~(0x7fff<<16);
        arr1[idxSubObj].param[TIMER_LOGIC_INPUT] = arr[idxSubObj].param[TIMER_LOGIC_INPUT] |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
   break; 

   case 4://Reset-I 0 item
        arr1[idxSubObj].param[TIMER_RESET] = arr[idxSubObj].param[TIMER_RESET] &= (uint32_t)~0xffff;
        arr1[idxSubObj].param[TIMER_RESET] = arr[idxSubObj].param[TIMER_RESET] |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
   break;
   case 5://Reset-I 1 item
        arr1[idxSubObj].param[TIMER_RESET] = arr[idxSubObj].param[TIMER_RESET] &= (uint32_t)~(0x7fff<<16);
        arr1[idxSubObj].param[TIMER_RESET] = arr[idxSubObj].param[TIMER_RESET] |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
   break; 
 }//switch
  }//for

  if(upravlSetting)//���� Setting
     config_settings_modified |= MASKA_FOR_BIT(BIT_CHANGED_SETTINGS);
  if(upravlSchematic)//���� Shematic
     config_settings_modified |= MASKA_FOR_BIT(BIT_CHANGED_SCHEMATIC);
  if(pointInterface)//����� ���������� 0-USB 1-RS485
     config_settings_modified |= MASKA_FOR_BIT(BIT_RS485_LOCKS);
  else 
     config_settings_modified |= MASKA_FOR_BIT(BIT_USB_LOCKS);
  restart_timeout_idle_new_settings = true;
 return 0;
}//

void repairEditArrayMFT(int countRegister, __settings_for_TIMER *arr, __settings_for_TIMER *arr1) {
  //������������ edit ������
  for(int i=0; i<countRegister; i++) {
  int offset = i+mftbigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//������ ����������
  switch(offset%REGISTER_FOR_OBJ) {//������ �������� 
   case 2://MFT-IN 0 item
   case 3://MFT-IN 1 item
        arr1[idxSubObj].param[TIMER_LOGIC_INPUT] = arr[idxSubObj].param[TIMER_LOGIC_INPUT];
   break; 

   case 4://Reset-I 0 item
   case 5://Reset-I 1 item
        arr1[idxSubObj].param[TIMER_RESET] = arr[idxSubObj].param[TIMER_RESET];
   break; 
 }//switch
  }//for
}//repairEditArray(int countRegister, __settings_for_TIMER *arr, __settings_for_TIMER *arr1) 

int privateMFTBigGetReg1(int adrReg)
{
  //��������� ���������� ��������
  int count_register = mftbigcomponent->countObject*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg1(int adrReg)
int privateMFTBigGetReg2(int adrReg)
{
  //��������� ������� ��������
  int count_register = TOTAL_OBJ*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
