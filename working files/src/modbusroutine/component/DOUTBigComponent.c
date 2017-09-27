//#include <QtWidgets>
#include "header.h"

//��������� ������� � ����� ������
#define BEGIN_ADR_REGISTER 1156
//���� �-�� �������
#define TOTAL_OBJ 128
#define REGISTER_FOR_OBJ 13
int privateDOUTBigGetReg1(int adrReg);
int privateDOUTBigGetReg2(int adrReg);

int getDOUTBigModbusRegister(int);//�������� ���������� ��������
int getDOUTBigModbusBit(int);//�������� ���������� ����
int setDOUTBigModbusRegister(int, int);// ��������
int setDOUTBigModbusBit(int, int);// ����

void setDOUTBigCountObject(void);//�������� �-�� �������
void preDOUTBigReadAction(void);//action �� ������
void postDOUTBigReadAction(void);//action ����� ������
void preDOUTBigWriteAction(void);//action �� ������
int postDOUTBigWriteAction(void);//action ����� ������
void config_and_settingsDOUTBig(void);//action ���������
void repairEditArrayDOUT(int countRegister, __settings_for_OUTPUT_LED *arr, __settings_for_OUTPUT_LED *arr1);

COMPONENT_OBJ *doutbigcomponent;

/**************************************/
//���������� ���������� ��
/**************************************/
void constructorDOUTBigComponent(COMPONENT_OBJ *doutcomp)
{
  doutbigcomponent = doutcomp;
  doutbigcomponent->countObject = 0;//�-�� �������

  doutbigcomponent->getModbusRegister = getDOUTBigModbusRegister;//�������� ���������� ��������
  doutbigcomponent->getModbusBit      = getDOUTBigModbusBit;//�������� ���������� ����
  doutbigcomponent->setModbusRegister = setDOUTBigModbusRegister;// ��������
  doutbigcomponent->setModbusBit      = setDOUTBigModbusBit;// ����

  doutbigcomponent->preReadAction   = preDOUTBigReadAction;//action �� ������
  doutbigcomponent->postReadAction  = postDOUTBigReadAction;//action ����� ������
  doutbigcomponent->preWriteAction  = preDOUTBigWriteAction;//action �� ������
  doutbigcomponent->postWriteAction = postDOUTBigWriteAction;//action ����� ������
  doutbigcomponent->config_and_settings = config_and_settingsDOUTBig;//action ���������

  doutbigcomponent->isActiveActualData = 0;
}//prepareDVinConfig

int getDOUTBigModbusRegister(int adrReg)
{
  //�������� ���������� ��������
extern int pointInterface;//����� ���������� 0-USB 1-RS485
  if(privateDOUTBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(doutbigcomponent->isActiveActualData)// loadDOUTBigActualData(); //ActualData
                                           setDOUTBigCountObject(); //�������� �-�� �������
  doutbigcomponent->isActiveActualData = 0;
  if(privateDOUTBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;//MARKER_ERRORPERIMETR;

  superSetOperativMarker(doutbigcomponent, adrReg);

  int offset = adrReg-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//������ ����������
  __settings_for_OUTPUT_LED *arr =  ((config_settings_modified & MASKA_FOR_BIT(BIT_USB_LOCKS)) == 0 ) ? &(((__LN_OUTPUT_LED*)(spca_of_p_prt[ID_FB_OUTPUT - _ID_FB_FIRST_VAR])) + idxSubObj)->settings : (((__settings_for_OUTPUT_LED*)(sca_of_p[ID_FB_OUTPUT - _ID_FB_FIRST_VAR])) + idxSubObj);
  if(pointInterface)//����� ���������� 0-USB 1-RS485
                        arr =  ((config_settings_modified & MASKA_FOR_BIT(BIT_RS485_LOCKS)) == 0 ) ? &(((__LN_OUTPUT_LED*)(spca_of_p_prt[ID_FB_OUTPUT - _ID_FB_FIRST_VAR])) + idxSubObj)->settings : (((__settings_for_OUTPUT_LED*)(sca_of_p[ID_FB_OUTPUT - _ID_FB_FIRST_VAR])) + idxSubObj);
  switch(offset%REGISTER_FOR_OBJ) {//������ �������� 
   case 0://��������� ����. item
    return arr->control;

   case 1://RIN 0 ����. item
         return arr->param[OUTPUT_LED_LOGIC_INPUT] & 0xffff;

   case 2://RIN 1 ����. item
        return (arr->param[OUTPUT_LED_LOGIC_INPUT]  >> 16) & 0x7fff;

   case 3://Reset 0 ����. item
        return arr->param[OUTPUT_LED_RESET] & 0xffff;

   case 4://Reset 1 ����. item
        return (arr->param[OUTPUT_LED_RESET]  >> 16) & 0x7fff;

   case 5://BL-IMP 0 ����. item
        return arr->param[OUTPUT_LED_BL_IMP] & 0xffff;

   case 6://BL-IMP 1 ����. item
        return (arr->param[OUTPUT_LED_BL_IMP]  >> 16) & 0x7fff;

   case 7://C1/C2 0 ����. item
        return arr->param[OUTPUT_LED_MEANDER1_MEANDER2] & 0xffff;

   case 8://C1/C2 1 ����. item
        return (arr->param[OUTPUT_LED_MEANDER1_MEANDER2]  >> 16) & 0x7fff;

   case 9://��������� �1 0 ����. item
        return arr->param[OUTPUT_LED_MEANDER1] & 0xffff;

   case 10://��������� �1 1 ����. item
        return (arr->param[OUTPUT_LED_MEANDER1]  >> 16) & 0x7fff;

   case 11://��������� �2 0 ����. item
        return arr->param[OUTPUT_LED_MEANDER2] & 0xffff;

   case 12://��������� �2 1 ����. item
        return (arr->param[OUTPUT_LED_MEANDER2]  >> 16) & 0x7fff;

 }//switch

  return 0;
}//getDOUTBigModbusRegister(int adrReg)
int getDOUTBigModbusBit(int x)
{
  //�������� ���������� ��������
  UNUSED(x);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setDOUTBigModbusRegister(int adrReg, int dataReg)
{
extern int upravlSetting;//���� Setting
extern int upravlSchematic;//���� Shematic
  //�������� ���������� ��������
  if(privateDOUTBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(doutbigcomponent->isActiveActualData) setDOUTBigCountObject(); //�-�� �������
  doutbigcomponent->isActiveActualData = 0;
  if(privateDOUTBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;//MARKER_ERRORPERIMETR;

  superSetOperativMarker(doutbigcomponent, adrReg);
  superSetTempWriteArray(dataReg);//�������� � �����

  switch((adrReg-BEGIN_ADR_REGISTER)%REGISTER_FOR_OBJ) {
   case 0:
     upravlSetting = 1;//���� Setting
   break; 
   case 1:
    upravlSchematic = 1;//���� Shematic
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
   break; 
   case 2:
    //�������� ���������� ������������
    upravlSchematic = 1;//���� Shematic
    if(superControlParam(dataReg)) return MARKER_ERRORDIAPAZON;
   break; 
   case 3:
    upravlSchematic = 1;//���� Shematic
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
   break; 
   case 4:
    //�������� ���������� ������������
    upravlSchematic = 1;//���� Shematic
    if(superControlParam(dataReg)) return MARKER_ERRORDIAPAZON;
   break; 
   case 5:
    upravlSchematic = 1;//���� Shematic
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
   break; 
   case 6:
    //�������� ���������� ������������
    upravlSchematic = 1;//���� Shematic
    if(superControlParam(dataReg)) return MARKER_ERRORDIAPAZON;
   break; 
   case 7:
    upravlSchematic = 1;//���� Shematic
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
   break; 
   case 8:
    //�������� ���������� ������������
    upravlSchematic = 1;//���� Shematic
    if(superControlParam(dataReg)) return MARKER_ERRORDIAPAZON;
   break; 
   case 9:
    upravlSchematic = 1;//���� Shematic
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
   break; 
   case 10:
    //�������� ���������� ������������
    upravlSchematic = 1;//���� Shematic
    if(superControlParam_gi(dataReg)) return MARKER_ERRORDIAPAZON;
   break; 
   case 11:
    upravlSchematic = 1;//���� Shematic
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
   break; 
   case 12:
    //�������� ���������� ������������
    upravlSchematic = 1;//���� Shematic
    if(superControlParam_gi(dataReg)) return MARKER_ERRORDIAPAZON;
   break; 
  default: return MARKER_OUTPERIMETR;
  }//switch
  return 0;
}//getDOUTBigModbusRegister(int adrReg)
int setDOUTBigModbusBit(int x, int y)
{
  UNUSED(x);
  UNUSED(y);
  //�������� ���������� ��������
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void setDOUTBigCountObject(void) {
//�������� �-�� �������
  int cntObj = current_config.n_output; //ʳ������ ���������� ������
  if(cntObj<0) return;
  if(cntObj>TOTAL_OBJ) return;
  doutbigcomponent->countObject = cntObj;
}//
void preDOUTBigReadAction(void) {
//action �� ������
  doutbigcomponent->operativMarker[0] = -1;
  doutbigcomponent->operativMarker[1] = -1;//����������� ������
  doutbigcomponent->isActiveActualData = 1;
}//
void postDOUTBigReadAction(void) {
//action ����� ������
  if(doutbigcomponent->operativMarker[0]<0) return;//�� ���� ������
}//
void preDOUTBigWriteAction(void) {
//action �� ������
  doutbigcomponent->operativMarker[0] = -1;
  doutbigcomponent->operativMarker[1] = -1;//����������� ������
  doutbigcomponent->isActiveActualData = 1;
}//
int postDOUTBigWriteAction(void) {
extern int upravlSetting;//���� Setting
extern int upravlSchematic;//���� Shematic
extern int pointInterface;//����� ���������� 0-USB 1-RS485
//action ����� ������
  if(doutbigcomponent->operativMarker[0]<0) return 0;//�� ���� ������
  int offsetTempWriteArray = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//����� �������� TempWriteArray
  int countRegister = doutbigcomponent->operativMarker[1]-doutbigcomponent->operativMarker[0]+1;
  if(doutbigcomponent->operativMarker[1]<0) countRegister = 1;

   __settings_for_OUTPUT_LED *arr  = (__settings_for_OUTPUT_LED*)(sca_of_p[ID_FB_OUTPUT - _ID_FB_FIRST_VAR]);
   __settings_for_OUTPUT_LED *arr1 = (__settings_for_OUTPUT_LED*)(sca_of_p_edit[ID_FB_OUTPUT - _ID_FB_FIRST_VAR]);
//�������� edit ������
  for(int i=0; i<countRegister; i++) {
  int offset = i+doutbigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//������ ����������
  switch(offset%REGISTER_FOR_OBJ) {//������ �������� 
   case 1://RIN 0 ����. item
        arr1[idxSubObj].param[OUTPUT_LED_LOGIC_INPUT]  &= (uint32_t)~0xffff;
        arr1[idxSubObj].param[OUTPUT_LED_LOGIC_INPUT]  |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
   break;
   case 2://RIN 1 ����. item
        arr1[idxSubObj].param[OUTPUT_LED_LOGIC_INPUT]  &= (uint32_t)~(0x7fff<<16);
        arr1[idxSubObj].param[OUTPUT_LED_LOGIC_INPUT]  |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
   break; 

   case 3://Reset 0 ����. item
        arr1[idxSubObj].param[OUTPUT_LED_RESET]  &= (uint32_t)~0xffff;
        arr1[idxSubObj].param[OUTPUT_LED_RESET]  |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
   break;
   case 4://Reset 1 ����. item
        arr1[idxSubObj].param[OUTPUT_LED_RESET]  &= (uint32_t)~(0x7fff<<16);
        arr1[idxSubObj].param[OUTPUT_LED_RESET]  |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
   break; 

   case 5://BL-IMP 0 ����. item
        arr1[idxSubObj].param[OUTPUT_LED_BL_IMP]  &= (uint32_t)~0xffff;
        arr1[idxSubObj].param[OUTPUT_LED_BL_IMP]  |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
   break;
   case 6://BL-IMP 1 ����. item
        arr1[idxSubObj].param[OUTPUT_LED_BL_IMP]  &= (uint32_t)~(0x7fff<<16);
        arr1[idxSubObj].param[OUTPUT_LED_BL_IMP]  |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
   break; 

   case 7://C1/C2 0 ����. item
        arr1[idxSubObj].param[OUTPUT_LED_MEANDER1_MEANDER2]  &= (uint32_t)~0xffff;
        arr1[idxSubObj].param[OUTPUT_LED_MEANDER1_MEANDER2]  |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
   break;
   case 8://C1/C2 1 ����. item
        arr1[idxSubObj].param[OUTPUT_LED_MEANDER1_MEANDER2]  &= (uint32_t)~(0x7fff<<16);
        arr1[idxSubObj].param[OUTPUT_LED_MEANDER1_MEANDER2]  |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
   break; 

   case 9://��������� �1 0 ����. item
        arr1[idxSubObj].param[OUTPUT_LED_MEANDER1]  &= (uint32_t)~0xffff;
        arr1[idxSubObj].param[OUTPUT_LED_MEANDER1]  |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
   break;
   case 10://��������� �1 1 ����. item
        arr1[idxSubObj].param[OUTPUT_LED_MEANDER1]  &= (uint32_t)~(0x7fff<<16);
        arr1[idxSubObj].param[OUTPUT_LED_MEANDER1]  |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
   break; 

   case 11://��������� �2 0 ����. item
        arr1[idxSubObj].param[OUTPUT_LED_MEANDER2]  &= (uint32_t)~0xffff;
        arr1[idxSubObj].param[OUTPUT_LED_MEANDER2]  |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
   break;
   case 12://��������� �2 1 ����. item
        arr1[idxSubObj].param[OUTPUT_LED_MEANDER2]  &= (uint32_t)~(0x7fff<<16);
        arr1[idxSubObj].param[OUTPUT_LED_MEANDER2]  |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
   break; 
 }//switch
  }//for

  //�������� ����������
  for(int i=0; i<countRegister; i++) {
  int offset = i+doutbigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//������ ����������

  switch(offset%REGISTER_FOR_OBJ) {//������ �������� 
   case 1://RIN 0 ����. item
   case 2://RIN 1 ����. item
        if(superValidParam(arr1[idxSubObj].param[OUTPUT_LED_LOGIC_INPUT])) 
                {//�������� ����������
                repairEditArrayDOUT(countRegister, arr, arr1);//������������ edit ������
                return 2;//����
        }//if
  break;

   case 3://Reset 0 ����. item
   case 4://Reset 1 ����. item
        if(superValidParam(arr1[idxSubObj].param[OUTPUT_LED_RESET]))
                {//�������� ����������
                repairEditArrayDOUT(countRegister, arr, arr1);//������������ edit ������
                return 2;//����
        }//if
  break;
   case 5://BL-IMP 0 ����. item
   case 6://BL-IMP 1 ����. item
        if(superValidParam(arr1[idxSubObj].param[OUTPUT_LED_BL_IMP])) 
                {//�������� ����������
                repairEditArrayDOUT(countRegister, arr, arr1);//������������ edit ������
                return 2;//����
        }//if
  break;
   case 7://C1/C2 0 ����. item
   case 8://C1/C2 1 ����. item
        if(superValidParam(arr1[idxSubObj].param[OUTPUT_LED_MEANDER1_MEANDER2]))
                {//�������� ����������
                repairEditArrayDOUT(countRegister, arr, arr1);//������������ edit ������
                return 2;//����
        }//if
  break;
   case 9://��������� �1 0 ����. item
   case 10://��������� �1 1 ����. item
        if(superValidParam(arr1[idxSubObj].param[OUTPUT_LED_MEANDER1])) 
                {//�������� ����������
                repairEditArrayDOUT(countRegister, arr, arr1);//������������ edit ������
                return 2;//����
        }//if
  break;
   case 11://��������� �2 0 ����. item
   case 12://��������� �2 1 ����. item
        if(superValidParam(arr1[idxSubObj].param[OUTPUT_LED_MEANDER2]))
                {//�������� ����������
                repairEditArrayDOUT(countRegister, arr, arr1);//������������ edit ������
                return 2;//����
        }//if
  break;
 }//switch
  }//for

//�������� ������� - ��������������
  for(int i=0; i<countRegister; i++) {
  int offset = i+doutbigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//������ ����������
  switch(offset%REGISTER_FOR_OBJ) {//������ �������� 
   case 0://��������� ����. item
    arr1[idxSubObj].control = arr[idxSubObj].control = (tempWriteArray[offsetTempWriteArray+i]);
   break;

   case 1://RIN 0 ����. item
        arr1[idxSubObj].param[OUTPUT_LED_LOGIC_INPUT] = arr[idxSubObj].param[OUTPUT_LED_LOGIC_INPUT] &= (uint32_t)~0xffff;
        arr1[idxSubObj].param[OUTPUT_LED_LOGIC_INPUT] = arr[idxSubObj].param[OUTPUT_LED_LOGIC_INPUT] |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
   break;
   case 2://RIN 1 ����. item
        arr1[idxSubObj].param[OUTPUT_LED_LOGIC_INPUT] = arr[idxSubObj].param[OUTPUT_LED_LOGIC_INPUT] &= (uint32_t)~(0x7fff<<16);
        arr1[idxSubObj].param[OUTPUT_LED_LOGIC_INPUT] = arr[idxSubObj].param[OUTPUT_LED_LOGIC_INPUT] |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
   break; 

   case 3://Reset 0 ����. item
        arr1[idxSubObj].param[OUTPUT_LED_RESET] = arr[idxSubObj].param[OUTPUT_LED_RESET] &= (uint32_t)~0xffff;
        arr1[idxSubObj].param[OUTPUT_LED_RESET] = arr[idxSubObj].param[OUTPUT_LED_RESET] |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
   break;
   case 4://Reset 1 ����. item
        arr1[idxSubObj].param[OUTPUT_LED_RESET] = arr[idxSubObj].param[OUTPUT_LED_RESET] &= (uint32_t)~(0x7fff<<16);
        arr1[idxSubObj].param[OUTPUT_LED_RESET] = arr[idxSubObj].param[OUTPUT_LED_RESET] |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
   break; 

   case 5://BL-IMP 0 ����. item
        arr1[idxSubObj].param[OUTPUT_LED_BL_IMP] = arr[idxSubObj].param[OUTPUT_LED_BL_IMP] &= (uint32_t)~0xffff;
        arr1[idxSubObj].param[OUTPUT_LED_BL_IMP] = arr[idxSubObj].param[OUTPUT_LED_BL_IMP] |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
   break;
   case 6://BL-IMP 1 ����. item
        arr1[idxSubObj].param[OUTPUT_LED_BL_IMP] = arr[idxSubObj].param[OUTPUT_LED_BL_IMP] &= (uint32_t)~(0x7fff<<16);
        arr1[idxSubObj].param[OUTPUT_LED_BL_IMP] = arr[idxSubObj].param[OUTPUT_LED_BL_IMP] |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
   break; 

   case 7://C1/C2 0 ����. item
        arr1[idxSubObj].param[OUTPUT_LED_MEANDER1_MEANDER2] = arr[idxSubObj].param[OUTPUT_LED_MEANDER1_MEANDER2] &= (uint32_t)~0xffff;
        arr1[idxSubObj].param[OUTPUT_LED_MEANDER1_MEANDER2] = arr[idxSubObj].param[OUTPUT_LED_MEANDER1_MEANDER2] |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
   break;
   case 8://C1/C2 1 ����. item
        arr1[idxSubObj].param[OUTPUT_LED_MEANDER1_MEANDER2] = arr[idxSubObj].param[OUTPUT_LED_MEANDER1_MEANDER2] &= (uint32_t)~(0x7fff<<16);
        arr1[idxSubObj].param[OUTPUT_LED_MEANDER1_MEANDER2] = arr[idxSubObj].param[OUTPUT_LED_MEANDER1_MEANDER2] |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
   break; 

   case 9://��������� �1 0 ����. item
        arr1[idxSubObj].param[OUTPUT_LED_MEANDER1] = arr[idxSubObj].param[OUTPUT_LED_MEANDER1] &= (uint32_t)~0xffff;
        arr1[idxSubObj].param[OUTPUT_LED_MEANDER1] = arr[idxSubObj].param[OUTPUT_LED_MEANDER1] |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
   break;
   case 10://��������� �1 1 ����. item
        arr1[idxSubObj].param[OUTPUT_LED_MEANDER1] = arr[idxSubObj].param[OUTPUT_LED_MEANDER1] &= (uint32_t)~(0x7fff<<16);
        arr1[idxSubObj].param[OUTPUT_LED_MEANDER1] = arr[idxSubObj].param[OUTPUT_LED_MEANDER1] |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
   break; 

   case 11://��������� �2 0 ����. item
        arr1[idxSubObj].param[OUTPUT_LED_MEANDER2] = arr[idxSubObj].param[OUTPUT_LED_MEANDER2] &= (uint32_t)~0xffff;
        arr1[idxSubObj].param[OUTPUT_LED_MEANDER2] = arr[idxSubObj].param[OUTPUT_LED_MEANDER2] |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
   break;
   case 12://��������� �2 1 ����. item
        arr1[idxSubObj].param[OUTPUT_LED_MEANDER2] = arr[idxSubObj].param[OUTPUT_LED_MEANDER2] &= (uint32_t)~(0x7fff<<16);
        arr1[idxSubObj].param[OUTPUT_LED_MEANDER2] = arr[idxSubObj].param[OUTPUT_LED_MEANDER2] |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
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

void repairEditArrayDOUT(int countRegister, __settings_for_OUTPUT_LED *arr, __settings_for_OUTPUT_LED *arr1) {
  //������������ edit ������
  for(int i=0; i<countRegister; i++) {
  int offset = i+doutbigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//������ ����������
  switch(offset%REGISTER_FOR_OBJ) {//������ �������� 
   case 1://RIN 0 ����. item
   case 2://RIN 1 ����. item
        arr1[idxSubObj].param[OUTPUT_LED_LOGIC_INPUT] = arr[idxSubObj].param[OUTPUT_LED_LOGIC_INPUT];
   break; 

   case 3://Reset 0 ����. item
   case 4://Reset 1 ����. item
        arr1[idxSubObj].param[OUTPUT_LED_RESET] = arr[idxSubObj].param[OUTPUT_LED_RESET];
   break; 

   case 5://BL-IMP 0 ����. item
   case 6://BL-IMP 1 ����. item
        arr1[idxSubObj].param[OUTPUT_LED_BL_IMP] = arr[idxSubObj].param[OUTPUT_LED_BL_IMP];
   break; 

   case 7://C1/C2 0 ����. item
   case 8://C1/C2 1 ����. item
        arr1[idxSubObj].param[OUTPUT_LED_MEANDER1_MEANDER2] = arr[idxSubObj].param[OUTPUT_LED_MEANDER1_MEANDER2];
   break; 

   case 9://��������� �1 0 ����. item
   case 10://��������� �1 1 ����. item
        arr1[idxSubObj].param[OUTPUT_LED_MEANDER1] = arr[idxSubObj].param[OUTPUT_LED_MEANDER1];
   break; 

   case 11://��������� �2 0 ����. item
   case 12://��������� �2 1 ����. item
        arr1[idxSubObj].param[OUTPUT_LED_MEANDER2] = arr[idxSubObj].param[OUTPUT_LED_MEANDER2];
   break; 
 }//switch
  }//for
}//repairEditArray(int countRegister, __settings_for_OUTPUT_LED *arr, __settings_for_OUTPUT_LED *arr1) 

int privateDOUTBigGetReg1(int adrReg)
{
  //��������� ���������� ��������
  int count_register = doutbigcomponent->countObject*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg1(int adrReg)
int privateDOUTBigGetReg2(int adrReg)
{
  //��������� ������� ��������
  int count_register = TOTAL_OBJ*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)

void config_and_settingsDOUTBig(void)
{
//action ���������
}

