#include "header.h"

//��������� ������� � ����� ������
#define BEGIN_ADR_REGISTER 13768
//���� �-�� �������
#define REGISTER_FOR_OBJ 10

int privateCommonBigGetReg2(int adrReg);

int getCommonBigModbusRegister(int);//�������� ���������� ��������
int getCommonBigModbusBit(int);//�������� ���������� ����
int setCommonBigModbusRegister(int, int);// ��������
int setCommonBigModbusBit(int, int);// ����

void preCommonBigReadAction(void);//action �� ������
void postCommonBigReadAction(void);//action ����� ������
void preCommonBigWriteAction(void);//action �� ������
int postCommonBigWriteAction(void);//action ����� ������
void config_and_settingsCommonBig(void);//action ���������
void repairEditArrayCommon(int countRegister, __SETTINGS_FIX *arr, __SETTINGS_FIX *arr1);

COMPONENT_OBJ *commonbigcomponent;

/**************************************/
//���������� ���������� �����
/**************************************/
void constructorCommonBigComponent(COMPONENT_OBJ *commonbigcomp)
{
  commonbigcomponent = commonbigcomp;

  commonbigcomponent->countObject = 1;//�-�� �������

  commonbigcomponent->getModbusRegister = getCommonBigModbusRegister;//�������� ���������� ��������
  commonbigcomponent->getModbusBit      = getCommonBigModbusBit;//�������� ���������� ����
  commonbigcomponent->setModbusRegister = setCommonBigModbusRegister;//��������
  commonbigcomponent->setModbusBit      = setCommonBigModbusBit;// ����

  commonbigcomponent->preReadAction   = preCommonBigReadAction;//action �� ������
  commonbigcomponent->postReadAction  = postCommonBigReadAction;//action ����� ������
  commonbigcomponent->preWriteAction  = preCommonBigWriteAction;//action �� ������
  commonbigcomponent->postWriteAction = postCommonBigWriteAction;//action ����� ������
  commonbigcomponent->config_and_settings = config_and_settingsCommonBig;//action ���������

  commonbigcomponent->isActiveActualData = 0;
}//prepareDVinConfig

int getCommonBigModbusRegister(int adrReg)
{
  //�������� ���������� ��������
  if(privateCommonBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  superSetOperativMarker(commonbigcomponent, adrReg);

   __SETTINGS_FIX *arr = &settings_fix;
  int offset = adrReg-BEGIN_ADR_REGISTER;
  switch(offset%REGISTER_FOR_OBJ) {//������ �������� 
  case 0:
   //����. 0
   return arr->param[FIX_BLOCK_BLOCK] & 0xffff;//
  case 1:
   return (arr->param[FIX_BLOCK_BLOCK] >> 16) & 0x7fff;//

  case 2:
   //������� 0
   return arr->param[FIX_BLOCK_ALARM] & 0xffff;//
  case 3:
   return (arr->param[FIX_BLOCK_ALARM] >> 16) & 0x7fff;//

  case 4:
   //������ 0
   return arr->param[FIX_BLOCK_MUTE] & 0xffff;//
  case 5:
   return (arr->param[FIX_BLOCK_MUTE] >> 16) & 0x7fff;//

  case 6:
   //����.����. 0
  case 7:

  case 8:
   //����.�����. 0
  case 9:
    break;
  }//switch

  return 0;
}//getDOUTBigModbusRegister(int adrReg)
int getCommonBigModbusBit(int x)
{
  //�������� ���������� bit
  UNUSED(x);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setCommonBigModbusRegister(int adrReg, int dataReg)
{
  //�������� ���������� ��������
  if(privateCommonBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  superSetOperativMarker(commonbigcomponent, adrReg);
  superSetTempWriteArray(dataReg);//�������� � �����

  switch((adrReg-BEGIN_ADR_REGISTER)%REGISTER_FOR_OBJ) {
   case 0:
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
   break; 
   case 1:
    //�������� ���������� ������������
    if(superControlParam(dataReg)) return MARKER_ERRORDIAPAZON;
   break; 
   case 2:
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
   break; 
   case 3:
    //�������� ���������� ������������
    if(superControlParam(dataReg)) return MARKER_ERRORDIAPAZON;
   break; 
   case 4:
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
   break; 
   case 5:
    //�������� ���������� ������������
    if(superControlParam(dataReg)) return MARKER_ERRORDIAPAZON;
   break; 
   case 6:
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
   break; 
   case 7:
    //�������� ���������� ������������
    if(superControlParam(dataReg)) return MARKER_ERRORDIAPAZON;
   break; 
   case 8:
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
   break; 
   case 9:
    //�������� ���������� ������������
    if(superControlParam(dataReg)) return MARKER_ERRORDIAPAZON;
   break; 
   default: return MARKER_OUTPERIMETR;
  }//switch
  return 0;
}//getDOUTBigModbusRegister(int adrReg)
int setCommonBigModbusBit(int x, int y)
{
  UNUSED(x);
  UNUSED(y);
  //�������� ���������� ��������
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void preCommonBigReadAction(void) {
//action �� ������
  commonbigcomponent->operativMarker[0] = -1;
  commonbigcomponent->operativMarker[1] = -1;//����������� ������
  commonbigcomponent->isActiveActualData = 1;
}//
void postCommonBigReadAction(void) {
//action ����� ������
  if(commonbigcomponent->operativMarker[0]<0) return;//�� ���� ������
}//
void preCommonBigWriteAction(void) {
//action �� ������
  commonbigcomponent->operativMarker[0] = -1;
  commonbigcomponent->operativMarker[1] = -1;//����������� ������
  commonbigcomponent->isActiveActualData = 1;
}//
int postCommonBigWriteAction(void) {
//action ����� ������
extern int pointInterface;//����� ���������� 0-USB 1-RS485
  if(commonbigcomponent->operativMarker[0]<0) return 0;//�� ���� ������
  int offsetTempWriteArray = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//����� �������� TempWriteArray
  int countRegister = commonbigcomponent->operativMarker[1]-commonbigcomponent->operativMarker[0]+1;
  if(commonbigcomponent->operativMarker[1]<0) countRegister = 1;

  __SETTINGS_FIX *arr = &settings_fix, *arr1 = &settings_fix_edit;
//�������� edit ������
  for(int i=0; i<countRegister; i++) {
  int offset = i+commonbigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;
  switch(offset) {//������ �������� 
   case 0://����. 0
        arr1->param[FIX_BLOCK_BLOCK]  &= (uint32_t)~0xffff;
        arr1->param[FIX_BLOCK_BLOCK]  |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
   break; 
   case 1://����. 1
        arr1->param[FIX_BLOCK_BLOCK]  &= (uint32_t)~(0x7fff<<16);
        arr1->param[FIX_BLOCK_BLOCK]  |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
   break; 

   case 2://������� 0
        arr1->param[FIX_BLOCK_ALARM]  &= (uint32_t)~0xffff;
        arr1->param[FIX_BLOCK_ALARM]  |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
   break; 
   case 3://������� 1
        arr1->param[FIX_BLOCK_ALARM]  &= (uint32_t)~(0x7fff<<16);
        arr1->param[FIX_BLOCK_ALARM]  |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
   break; 

   case 4://������ 0
        arr1->param[FIX_BLOCK_MUTE]  &= (uint32_t)~0xffff;
        arr1->param[FIX_BLOCK_MUTE]  |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
   break; 
   case 5://������ 1
        arr1->param[FIX_BLOCK_MUTE]  &= (uint32_t)~(0x7fff<<16);
        arr1->param[FIX_BLOCK_MUTE]  |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
   break; 

 }//switch
  }//for

  //�������� ����������
  for(int i=0; i<countRegister; i++) {
  int offset = i+commonbigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;

  switch(offset) {//������ �������� 
   case 0://����. 0
   case 1://����. 1
        if(superValidParam(arr1->param[FIX_BLOCK_BLOCK]))
                {//�������� ����������
                repairEditArrayCommon(countRegister, arr, arr1);//������������ edit ������
                return 2;//����
        }//if
  break;
   case 2://������� 0
   case 3:
        if(superValidParam(arr1->param[FIX_BLOCK_ALARM])) 
                {//�������� ����������
                repairEditArrayCommon(countRegister, arr, arr1);//������������ edit ������
                return 2;//����
        }//if
  break;

   case 4://������ 0
   case 5://������ 1
        if(superValidParam(arr1->param[FIX_BLOCK_MUTE]))
                {//�������� ����������
                repairEditArrayCommon(countRegister, arr, arr1);//������������ edit ������
                return 2;//����
        }//if
  break;
 }//switch
  }//for

//�������� ������� - ��������������
  for(int i=0; i<countRegister; i++) {
  int offset = i+commonbigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;
  switch(offset) {//������ �������� 
   case 0://����. 0
        arr1->param[FIX_BLOCK_BLOCK] = arr->param[FIX_BLOCK_BLOCK] &= (uint32_t)~0xffff;
        arr1->param[FIX_BLOCK_BLOCK] = arr->param[FIX_BLOCK_BLOCK] |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
   break; 
   case 1://����. 1
        arr1->param[FIX_BLOCK_BLOCK] = arr->param[FIX_BLOCK_BLOCK] &= (uint32_t)~(0x7fff<<16);
        arr1->param[FIX_BLOCK_BLOCK] = arr->param[FIX_BLOCK_BLOCK] |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
   break; 

   case 2://������� 0
        arr1->param[FIX_BLOCK_ALARM] = arr->param[FIX_BLOCK_ALARM] &= (uint32_t)~0xffff;
        arr1->param[FIX_BLOCK_ALARM] = arr->param[FIX_BLOCK_ALARM] |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
   break; 
   case 3://������� 1
        arr1->param[FIX_BLOCK_ALARM] = arr->param[FIX_BLOCK_ALARM] &= (uint32_t)~(0x7fff<<16);
        arr1->param[FIX_BLOCK_ALARM] = arr->param[FIX_BLOCK_ALARM] |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
   break; 

   case 4://������ 0
        arr1->param[FIX_BLOCK_MUTE] = arr->param[FIX_BLOCK_MUTE] &= (uint32_t)~0xffff;
        arr1->param[FIX_BLOCK_MUTE] = arr->param[FIX_BLOCK_MUTE] |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
   break; 
   case 5://������ 1
        arr1->param[FIX_BLOCK_MUTE] = arr->param[FIX_BLOCK_MUTE] &= (uint32_t)~(0x7fff<<16);
        arr1->param[FIX_BLOCK_MUTE] = arr->param[FIX_BLOCK_MUTE] |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
   break; 

   case 6://����.����. 0
   break; 
   case 7://����.����. 1

   case 8://����.�����. 0
   break; 
   case 9://����.�����. 1
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

void repairEditArrayCommon(int countRegister, __SETTINGS_FIX *arr, __SETTINGS_FIX *arr1) {
  //������������ edit ������
  for(int i=0; i<countRegister; i++) {
  int offset = i+commonbigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;
  switch(offset) {//������ �������� 
   case 0://����. 0
   case 1://����. 1
        arr1->param[FIX_BLOCK_BLOCK] = arr->param[FIX_BLOCK_BLOCK];
   break; 

   case 2://������� 0
   case 3://������� 1
        arr1->param[FIX_BLOCK_ALARM] = arr->param[FIX_BLOCK_ALARM];
   break; 

   case 4://������ 0
   case 5://������ 1
        arr1->param[FIX_BLOCK_MUTE] = arr->param[FIX_BLOCK_MUTE];
   break; 

 }//switch
  }//for
}//repairEditArray(int countRegister, __SETTINGS_FIX *arr, __SETTINGS_FIX *arr1) 

int privateCommonBigGetReg2(int adrReg)
{
  //��������� ������� ��������
  int count_register = REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)

void config_and_settingsCommonBig(void)
{
//action ���������
}

