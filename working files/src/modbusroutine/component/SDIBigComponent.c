#include "header.h"

//��������� ������� � ����� ������
#define BEGIN_ADR_REGISTER 3000
//���� �-�� �������
#define TOTAL_OBJ 128
#define REGISTER_FOR_OBJ 13

int privateSDIBigGetReg1(int adrReg);
int privateSDIBigGetReg2(int adrReg);

int getSDIBigModbusRegister(int);//�������� ���������� ��������
int getSDIBigModbusBit(int);//�������� ���������� ����
int setSDIBigModbusRegister(int, int);//�������� ���������� ��������
int setSDIBigModbusBit(int, int);//�������� ���������� ����

void setSDIBigCountObject(void);//�������� �-�� �������
void preSDIBigReadAction(void);//action �� ������
void postSDIBigReadAction(void);//action ����� ������
void preSDIBigWriteAction(void);//action �� ������
int postSDIBigWriteAction(void);//action ����� ������
void loadSDIBigActualData(void);

COMPONENT_OBJ *sdibigcomponent;

/**************************************/
//���������� ���������� ����������������
/**************************************/
void constructorSDIBigComponent(COMPONENT_OBJ *sdibigcomp)
{
  sdibigcomponent = sdibigcomp;

  sdibigcomponent->countObject = 0;//�-�� �������

  sdibigcomponent->getModbusRegister = getSDIBigModbusRegister;//�������� ���������� ��������
  sdibigcomponent->getModbusBit      = getSDIBigModbusBit;//�������� ���������� ����
  sdibigcomponent->setModbusRegister = setSDIBigModbusRegister;//�������� ���������� ��������
  sdibigcomponent->setModbusBit      = setSDIBigModbusBit;//�������� ���������� ����

  sdibigcomponent->preReadAction   = preSDIBigReadAction;//action �� ������
  sdibigcomponent->postReadAction  = postSDIBigReadAction;//action ����� ������
  sdibigcomponent->preWriteAction  = preSDIBigWriteAction;//action �� ������
  sdibigcomponent->postWriteAction = postSDIBigWriteAction;//action ����� ������

  sdibigcomponent->isActiveActualData = 0;
}//prepareDVinConfig
/*
void loadSDIBigActualData(void) {
 setSDIBigCountObject(); //�������� �-�� �������

  //ActualData
  __LN_OUTPUT_LED *arr = (__LN_OUTPUT_LED*)(spca_of_p_prt[ID_FB_LED - _ID_FB_FIRST_VAR]);
   for(int item=0; item<sdibigcomponent->countObject; item++) {
   int value = arr[item].settings.control;//��������� �� item
   tempReadArray[item*REGISTER_FOR_OBJ+0] = value;

   value = arr[item].settings.param[OUTPUT_LED_LOGIC_INPUT] & 0xffff;//LEDIN 0 �� item
   tempReadArray[item*REGISTER_FOR_OBJ+1] = value;
   value = (arr[item].settings.param[OUTPUT_LED_LOGIC_INPUT] >> 16) & 0x7fff;//LEDIN 1 �� item
   tempReadArray[item*REGISTER_FOR_OBJ+2] = value;

   value = arr[item].settings.param[OUTPUT_LED_RESET] & 0xffff;//Reset 0 �� item
   tempReadArray[item*REGISTER_FOR_OBJ+3] = value;
   value = (arr[item].settings.param[OUTPUT_LED_RESET] >> 16) & 0x7fff;//Reset 1 �� item
   tempReadArray[item*REGISTER_FOR_OBJ+4] = value;

   value = arr[item].settings.param[OUTPUT_LED_BL_IMP] & 0xffff;//BL-IMP 0 �� item
   tempReadArray[item*REGISTER_FOR_OBJ+5] = value;
   value = (arr[item].settings.param[OUTPUT_LED_BL_IMP] >> 16) & 0x7fff;//BL-IMP 1 �� item
   tempReadArray[item*REGISTER_FOR_OBJ+6] = value;

   value = arr[item].settings.param[OUTPUT_LED_MEANDER1_MEANDER2] & 0xffff;//C1/C2 0 �� item
   tempReadArray[item*REGISTER_FOR_OBJ+7] = value;
   value = (arr[item].settings.param[OUTPUT_LED_MEANDER1_MEANDER2] >> 16) & 0x7fff;//C1/C2 1 �� item
   tempReadArray[item*REGISTER_FOR_OBJ+8] = value;

   value = arr[item].settings.param[OUTPUT_LED_MEANDER1] & 0xffff;//��������� �1 ���.0 �� item
   tempReadArray[item*REGISTER_FOR_OBJ+9] = value;
   value = (arr[item].settings.param[OUTPUT_LED_MEANDER1] >> 16) & 0x7fff;//��������� �1 ���.1 �� item
   tempReadArray[item*REGISTER_FOR_OBJ+10] = value;

   value = arr[item].settings.param[OUTPUT_LED_MEANDER2] & 0xffff;//��������� �2 ���.0 �� item
   tempReadArray[item*REGISTER_FOR_OBJ+11] = value;
   value = (arr[item].settings.param[OUTPUT_LED_MEANDER2] >> 16) & 0x7fff;//��������� �2 ���. 1 �� item
   tempReadArray[item*REGISTER_FOR_OBJ+12] = value;
  }//for
}//loadActualData() 
*/

int getSDIBigModbusRegister(int adrReg)
{
  //�������� ���������� ��������
  if(privateSDIBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(sdibigcomponent->isActiveActualData) setSDIBigCountObject(); //�-�� �������
  sdibigcomponent->isActiveActualData = 0;
  if(privateSDIBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;//MARKER_ERRORPERIMETR;

  superSetOperativMarker(sdibigcomponent, adrReg);

  __LN_OUTPUT_LED *arr = (__LN_OUTPUT_LED*)(spca_of_p_prt[ID_FB_LED - _ID_FB_FIRST_VAR]);
  int offset = adrReg-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//������ ����������
  switch(offset%REGISTER_FOR_OBJ) {//������ �������� 
   case 0:
     return arr[idxSubObj].settings.control;//��������� �� item

   case 1:
     return arr[idxSubObj].settings.param[OUTPUT_LED_LOGIC_INPUT] & 0xffff;//LEDIN 0 �� item
   case 2:
     return (arr[idxSubObj].settings.param[OUTPUT_LED_LOGIC_INPUT] >> 16) & 0x7fff;//LEDIN 1 �� item

   case 3:
     return arr[idxSubObj].settings.param[OUTPUT_LED_RESET] & 0xffff;//Reset 0 �� item
   case 4:
     return (arr[idxSubObj].settings.param[OUTPUT_LED_RESET] >> 16) & 0x7fff;//Reset 1 �� item

   case 5:
     return arr[idxSubObj].settings.param[OUTPUT_LED_BL_IMP] & 0xffff;//BL-IMP 0 �� item
   case 6:
     return (arr[idxSubObj].settings.param[OUTPUT_LED_BL_IMP] >> 16) & 0x7fff;//BL-IMP 1 �� item

   case 7:
     return arr[idxSubObj].settings.param[OUTPUT_LED_MEANDER1_MEANDER2] & 0xffff;//C1/C2 0 �� item
   case 8:
     return (arr[idxSubObj].settings.param[OUTPUT_LED_MEANDER1_MEANDER2] >> 16) & 0x7fff;//C1/C2 1 �� item

   case 9:
     return arr[idxSubObj].settings.param[OUTPUT_LED_MEANDER1] & 0xffff;//��������� �1 ���.0 �� item
   case 10:
     return (arr[idxSubObj].settings.param[OUTPUT_LED_MEANDER1] >> 16) & 0x7fff;//��������� �1 ���.1 �� item

   case 11:
     return arr[idxSubObj].settings.param[OUTPUT_LED_MEANDER2] & 0xffff;//��������� �2 ���.0 �� item
   case 12:
     return (arr[idxSubObj].settings.param[OUTPUT_LED_MEANDER2] >> 16) & 0x7fff;//��������� �2 ���. 1 �� item
  }//switch

  return 0;//tempReadArray[adrReg-BEGIN_ADR_REGISTER];
}//getSDIBigModbusRegister(int adrReg)
int getSDIBigModbusBit(int adrBit)
{
  //�������� ���������� ��������
  superSetOperativMarker(sdibigcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getSDIBigModbusBit(int )
int setSDIBigModbusRegister(int adrReg, int dataReg)
{
  //�������� ���������� ��������
  if(privateSDIBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(sdibigcomponent->isActiveActualData) setSDIBigCountObject(); //�-�� �������
  sdibigcomponent->isActiveActualData = 0;
  if(privateSDIBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;//MARKER_ERRORPERIMETR;

  superSetOperativMarker(sdibigcomponent, adrReg);
  superSetTempWriteArray(dataReg);//�������� � �����

  switch((adrReg-BEGIN_ADR_REGISTER)%REGISTER_FOR_OBJ) {
   case 0:
    //�������� ���������� ������������
    if(superControlParam(dataReg)) return MARKER_ERRORDIAPAZON;
   break; 
   case 1:
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
   break; 
   case 2:
    //�������� ���������� ������������
    if(superControlParam(dataReg)) return MARKER_ERRORDIAPAZON;
   break; 
   case 3:
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
   break; 
   case 4:
    //�������� ���������� ������������
    if(superControlParam(dataReg)) return MARKER_ERRORDIAPAZON;
   break; 
   case 5:
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
   break; 
   case 6:
    //�������� ���������� ������������
    if(superControlParam(dataReg)) return MARKER_ERRORDIAPAZON;
   break; 
   case 7:
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
   break; 
   case 8:
    //�������� ���������� ������������
    if(superControlParam(dataReg)) return MARKER_ERRORDIAPAZON;
   break; 
   case 9:
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
   break; 
   case 10:
    //�������� ���������� ������������
    if(superControlParam_gi(dataReg)) return MARKER_ERRORDIAPAZON;
   break; 
   case 11:
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
   break; 
   case 12:
    //�������� ���������� ������������
    if(superControlParam_gi(dataReg)) return MARKER_ERRORDIAPAZON;
   break; 
  default: return MARKER_OUTPERIMETR;
  }//switch
  return 0;
}//getDOUTBigModbusRegister(int adrReg)
int setSDIBigModbusBit(int adrBit, int x)
{
  UNUSED(x);
  //�������� ���������� ��������
  superSetOperativMarker(sdibigcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void setSDIBigCountObject(void) {
//�������� �-�� �������
  int cntObj = current_config.n_led; //ʳ������ ���������� ��������������
  if(cntObj<0) return;
  if(cntObj>TOTAL_OBJ) return;
  sdibigcomponent->countObject = cntObj;
}//
void preSDIBigReadAction(void) {
//action �� ������
  sdibigcomponent->operativMarker[0] = -1;
  sdibigcomponent->operativMarker[1] = -1;//����������� ������
  sdibigcomponent->isActiveActualData = 1;
}//
void postSDIBigReadAction(void) {
//action ����� ������
  if(sdibigcomponent->operativMarker[0]<0) return;//�� ���� ������
}//
void preSDIBigWriteAction(void) {
//action �� ������
  sdibigcomponent->operativMarker[0] = -1;
  sdibigcomponent->operativMarker[1] = -1;//����������� ������
  sdibigcomponent->isActiveActualData = 1;
}//
int postSDIBigWriteAction(void) {
//action ����� ������
  if(sdibigcomponent->operativMarker[0]<0) return 0;//�� ���� ������
  int offsetTempWriteArray = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//����� �������� TempWriteArray
  int countRegister = sdibigcomponent->operativMarker[1]-sdibigcomponent->operativMarker[0]+1;
  if(sdibigcomponent->operativMarker[1]<0) countRegister = 1;

//  __LN_OUTPUT_LED *arr = (__LN_OUTPUT_LED*)(spca_of_p_prt[ID_FB_LED - _ID_FB_FIRST_VAR]);
   __settings_for_OUTPUT_LED *arr  = (__settings_for_OUTPUT_LED*)(sca_of_p[ID_FB_LED - _ID_FB_FIRST_VAR]);
   __settings_for_OUTPUT_LED *arr1 = (__settings_for_OUTPUT_LED*)(sca_of_p_edit[ID_FB_LED - _ID_FB_FIRST_VAR]);
  for(int i=0; i<countRegister; i++) {
  int offset = i+sdibigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//������ ����������
  switch(offset%REGISTER_FOR_OBJ) {//������ �������� 
   case 0://��������� ����. item
    arr1[idxSubObj].control = arr[idxSubObj].control = (tempWriteArray[offsetTempWriteArray+i]);
   break;

   case 1://RIN 0
        arr1[idxSubObj].param[OUTPUT_LED_LOGIC_INPUT] = arr[idxSubObj].param[OUTPUT_LED_LOGIC_INPUT] &= (uint32_t)~0xffff;
        arr1[idxSubObj].param[OUTPUT_LED_LOGIC_INPUT] = arr[idxSubObj].param[OUTPUT_LED_LOGIC_INPUT] |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
   break;
   case 2://RIN 1 
        arr1[idxSubObj].param[OUTPUT_LED_LOGIC_INPUT] = arr[idxSubObj].param[OUTPUT_LED_LOGIC_INPUT] &= (uint32_t)~(0x7fff<<16);
        arr1[idxSubObj].param[OUTPUT_LED_LOGIC_INPUT] = arr[idxSubObj].param[OUTPUT_LED_LOGIC_INPUT] |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
   break; 

   case 3://Reset 0 
        arr1[idxSubObj].param[OUTPUT_LED_RESET] = arr[idxSubObj].param[OUTPUT_LED_RESET] &= (uint32_t)~0xffff;
        arr1[idxSubObj].param[OUTPUT_LED_RESET] = arr[idxSubObj].param[OUTPUT_LED_RESET] |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
   break;
   case 4://Reset 1 
        arr1[idxSubObj].param[OUTPUT_LED_RESET] = arr[idxSubObj].param[OUTPUT_LED_RESET] &= (uint32_t)~(0x7fff<<16);
        arr1[idxSubObj].param[OUTPUT_LED_RESET] = arr[idxSubObj].param[OUTPUT_LED_RESET] |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
   break; 

   case 5://BL-IMP 0 
        arr1[idxSubObj].param[OUTPUT_LED_BL_IMP] = arr[idxSubObj].param[OUTPUT_LED_BL_IMP] &= (uint32_t)~0xffff;
        arr1[idxSubObj].param[OUTPUT_LED_BL_IMP] = arr[idxSubObj].param[OUTPUT_LED_BL_IMP] |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
   break;
   case 6://BL-IMP 1 
        arr1[idxSubObj].param[OUTPUT_LED_BL_IMP] = arr[idxSubObj].param[OUTPUT_LED_BL_IMP] &= (uint32_t)~(0x7fff<<16);
        arr1[idxSubObj].param[OUTPUT_LED_BL_IMP] = arr[idxSubObj].param[OUTPUT_LED_BL_IMP] |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
   break; 

   case 7://C1/C2 0 
        arr1[idxSubObj].param[OUTPUT_LED_MEANDER1_MEANDER2] = arr[idxSubObj].param[OUTPUT_LED_MEANDER1_MEANDER2] &= (uint32_t)~0xffff;
        arr1[idxSubObj].param[OUTPUT_LED_MEANDER1_MEANDER2] = arr[idxSubObj].param[OUTPUT_LED_MEANDER1_MEANDER2] |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
   break;
   case 8://C1/C2 1 
        arr1[idxSubObj].param[OUTPUT_LED_MEANDER1_MEANDER2] = arr[idxSubObj].param[OUTPUT_LED_MEANDER1_MEANDER2] &= (uint32_t)~(0x7fff<<16);
        arr1[idxSubObj].param[OUTPUT_LED_MEANDER1_MEANDER2] = arr[idxSubObj].param[OUTPUT_LED_MEANDER1_MEANDER2] |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
   break; 

   case 9://��������� �1 0 
        arr1[idxSubObj].param[OUTPUT_LED_MEANDER1] = arr[idxSubObj].param[OUTPUT_LED_MEANDER1] &= (uint32_t)~0xffff;
        arr1[idxSubObj].param[OUTPUT_LED_MEANDER1] = arr[idxSubObj].param[OUTPUT_LED_MEANDER1] |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
   break;
   case 10://��������� �1 1 
        arr1[idxSubObj].param[OUTPUT_LED_MEANDER1] = arr[idxSubObj].param[OUTPUT_LED_MEANDER1] &= (uint32_t)~(0x7fff<<16);
        arr1[idxSubObj].param[OUTPUT_LED_MEANDER1] = arr[idxSubObj].param[OUTPUT_LED_MEANDER1] |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
   break; 

   case 11://��������� �2 0 
        arr1[idxSubObj].param[OUTPUT_LED_MEANDER2] = arr[idxSubObj].param[OUTPUT_LED_MEANDER2] &= (uint32_t)~0xffff;
        arr1[idxSubObj].param[OUTPUT_LED_MEANDER2] = arr[idxSubObj].param[OUTPUT_LED_MEANDER2] |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
   break;
   case 12://��������� �2 1 
        arr1[idxSubObj].param[OUTPUT_LED_MEANDER2] = arr[idxSubObj].param[OUTPUT_LED_MEANDER2] &= (uint32_t)~(0x7fff<<16);
        arr1[idxSubObj].param[OUTPUT_LED_MEANDER2] = arr[idxSubObj].param[OUTPUT_LED_MEANDER2] |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
   break; 
 }//switch
  }//for
  config_settings_modified |= MASKA_FOR_BIT(BIT_CHANGED_SETTINGS);
  restart_timeout_idle_new_settings = true;
 return 0;
}//

int privateSDIBigGetReg1(int adrReg)
{
  //��������� ���������� ��������
  int count_register = sdibigcomponent->countObject*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg1(int adrReg)
int privateSDIBigGetReg2(int adrReg)
{
  //��������� ������� ��������
  int count_register = TOTAL_OBJ*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
