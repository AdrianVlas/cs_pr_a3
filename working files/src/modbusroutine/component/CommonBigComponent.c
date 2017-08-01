#include "header.h"

//��������� ������� � ����� ������
#define BEGIN_ADR_REGISTER 13781
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
//void loadCommonBigActualData(void);

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

  commonbigcomponent->isActiveActualData = 0;
}//prepareDVinConfig
/*
void loadCommonBigActualData(void) {
  //ActualData
   __SETTINGS_FIX *arr = &settings_fix;
   for(int item=0; item<commonbigcomponent->countObject; item++) {
   //������� 0
   int value = arr->param[FIX_BLOCK_ALARM] & 0xffff;//
   tempReadArray[item*REGISTER_FOR_OBJ+0] = value;
   value = (arr->param[FIX_BLOCK_ALARM] >> 16) & 0x7fff;//
   tempReadArray[item*REGISTER_FOR_OBJ+1] = value;

   //������ 0
   value = arr->param[FIX_BLOCK_MUTE] & 0xffff;//
   tempReadArray[item*REGISTER_FOR_OBJ+2] = value;
   value = (arr->param[FIX_BLOCK_MUTE] >> 16) & 0x7fff;//
   tempReadArray[item*REGISTER_FOR_OBJ+3] = value;

   //����. 0
   value = arr->param[FIX_BLOCK_BLOCK] & 0xffff;//
   tempReadArray[item*REGISTER_FOR_OBJ+4] = value;
   value = (arr->param[FIX_BLOCK_BLOCK] >> 16) & 0x7fff;//
   tempReadArray[item*REGISTER_FOR_OBJ+5] = value;

   //����.����. 0
   value = arr->param[FIX_BLOCK_TEST_INPUT] & 0xffff;//
   tempReadArray[item*REGISTER_FOR_OBJ+6] = value;
   value = (arr->param[FIX_BLOCK_TEST_INPUT] >> 16) & 0x7fff;//
   tempReadArray[item*REGISTER_FOR_OBJ+7] = value;

   //����.�����. 0
   value = arr->param[FIX_BLOCK_TEST_RESET] & 0xffff;//
   tempReadArray[item*REGISTER_FOR_OBJ+8] = value;
   value = (arr->param[FIX_BLOCK_TEST_RESET] >> 16) & 0x7fff;//
   tempReadArray[item*REGISTER_FOR_OBJ+9] = value;
  }//for
}//loadActualData() 
*/

int getCommonBigModbusRegister(int adrReg)
{
  //�������� ���������� ��������
  if(privateCommonBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

//  if(commonbigcomponent->isActiveActualData) loadCommonBigActualData(); //ActualData
//  commonbigcomponent->isActiveActualData = 0;

  superSetOperativMarker(commonbigcomponent, adrReg);

   __SETTINGS_FIX *arr = &settings_fix;
  int offset = adrReg-BEGIN_ADR_REGISTER;
  switch(offset%REGISTER_FOR_OBJ) {//������ �������� 
  case 0:
   //������� 0
   return arr->param[FIX_BLOCK_ALARM] & 0xffff;//
  case 1:
   return (arr->param[FIX_BLOCK_ALARM] >> 16) & 0x7fff;//

  case 2:
   //������ 0
   return arr->param[FIX_BLOCK_MUTE] & 0xffff;//
  case 3:
   return (arr->param[FIX_BLOCK_MUTE] >> 16) & 0x7fff;//

  case 4:
   //����. 0
   return arr->param[FIX_BLOCK_BLOCK] & 0xffff;//
  case 5:
   return (arr->param[FIX_BLOCK_BLOCK] >> 16) & 0x7fff;//

  case 6:
   //����.����. 0
   //return arr->param[FIX_BLOCK_TEST_INPUT] & 0xffff;//
  case 7:
   //return (arr->param[FIX_BLOCK_TEST_INPUT] >> 16) & 0x7fff;//

  case 8:
   //����.�����. 0
   //return arr->param[FIX_BLOCK_TEST_RESET] & 0xffff;//
  case 9:
   //return (arr->param[FIX_BLOCK_TEST_RESET] >> 16) & 0x7fff;//
    break;
  }//switch

  return 0;//tempReadArray[adrReg-BEGIN_ADR_REGISTER];
}//getDOUTBigModbusRegister(int adrReg)
int getCommonBigModbusBit(int adrBit)
{
  //�������� ���������� bit
  superSetOperativMarker(commonbigcomponent, adrBit);
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
int setCommonBigModbusBit(int adrBit, int x)
{
  UNUSED(x);
  //�������� ���������� ��������
  superSetOperativMarker(commonbigcomponent, adrBit);
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
  if(commonbigcomponent->operativMarker[0]<0) return 0;//�� ���� ������
  int offsetTempWriteArray = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//����� �������� TempWriteArray
  int countRegister = commonbigcomponent->operativMarker[1]-commonbigcomponent->operativMarker[0]+1;
  if(commonbigcomponent->operativMarker[1]<0) countRegister = 1;

//   __SETTINGS_FIX *arr = &settings_fix;
  __SETTINGS_FIX *arr = &settings_fix, *arr1 = &settings_fix_edit;
  for(int i=0; i<countRegister; i++) {
  int offset = i+commonbigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;
  switch(offset) {//������ �������� 
   case 0://������� 0
        arr1->param[FIX_BLOCK_ALARM] = arr->param[FIX_BLOCK_ALARM] &= (uint32_t)~0xffff;
        arr1->param[FIX_BLOCK_ALARM] = arr->param[FIX_BLOCK_ALARM] |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
   break; 
   case 1://������� 1
        arr1->param[FIX_BLOCK_ALARM] = arr->param[FIX_BLOCK_ALARM] &= (uint32_t)~(0x7fff<<16);
        arr1->param[FIX_BLOCK_ALARM] = arr->param[FIX_BLOCK_ALARM] |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
   break; 

   case 2://������ 0
        arr1->param[FIX_BLOCK_MUTE] = arr->param[FIX_BLOCK_MUTE] &= (uint32_t)~0xffff;
        arr1->param[FIX_BLOCK_MUTE] = arr->param[FIX_BLOCK_MUTE] |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
   break; 
   case 3://������ 1
        arr1->param[FIX_BLOCK_MUTE] = arr->param[FIX_BLOCK_MUTE] &= (uint32_t)~(0x7fff<<16);
        arr1->param[FIX_BLOCK_MUTE] = arr->param[FIX_BLOCK_MUTE] |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
   break; 

   case 4://����. 0
        arr1->param[FIX_BLOCK_BLOCK] = arr->param[FIX_BLOCK_BLOCK] &= (uint32_t)~0xffff;
        arr1->param[FIX_BLOCK_BLOCK] = arr->param[FIX_BLOCK_BLOCK] |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
   break; 
   case 5://����. 1
        arr1->param[FIX_BLOCK_BLOCK] = arr->param[FIX_BLOCK_BLOCK] &= (uint32_t)~(0x7fff<<16);
        arr1->param[FIX_BLOCK_BLOCK] = arr->param[FIX_BLOCK_BLOCK] |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
   break; 

   case 6://����.����. 0
//        arr1->param[FIX_BLOCK_TEST_INPUT] = arr->param[FIX_BLOCK_TEST_INPUT] &= (uint32_t)~0xffff;
        //arr1->param[FIX_BLOCK_TEST_INPUT] = arr->param[FIX_BLOCK_TEST_INPUT] |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
   break; 
   case 7://����.����. 1
//        arr1->param[FIX_BLOCK_TEST_INPUT] = arr->param[FIX_BLOCK_TEST_INPUT] &= (uint32_t)~(0x7fff<<16);
        //arr1->param[FIX_BLOCK_TEST_INPUT] = arr->param[FIX_BLOCK_TEST_INPUT] |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//

   case 8://����.�����. 0
//        arr1->param[FIX_BLOCK_TEST_RESET] = arr->param[FIX_BLOCK_TEST_RESET] &= (uint32_t)~0xffff;
//        arr1->param[FIX_BLOCK_TEST_RESET] = arr->param[FIX_BLOCK_TEST_RESET] |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
   break; 
   case 9://����.�����. 1
        //arr1->param[FIX_BLOCK_TEST_RESET] = arr->param[FIX_BLOCK_TEST_RESET] &= (uint32_t)~(0x7fff<<16);
        //arr1->param[FIX_BLOCK_TEST_RESET] = arr->param[FIX_BLOCK_TEST_RESET] |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
   break; 
 }//switch
  }//for
  config_settings_modified |= MASKA_FOR_BIT(BIT_CHANGED_SETTINGS);
  restart_timeout_idle_new_settings = true;
 return 0;
}//

int privateCommonBigGetReg2(int adrReg)
{
  //��������� ������� ��������
  int count_register = REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
