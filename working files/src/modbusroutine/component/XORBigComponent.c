#include "header.h"

//��������� ������� � ����� ������
#define BEGIN_ADR_REGISTER 13000
//���� �-�� �������
#define TOTAL_OBJ 128
#define REGISTER_FOR_OBJ 4

int privateXORBigGetReg1(int adrReg);
int privateXORBigGetReg2(int adrReg);

int getXORBigModbusRegister(int);//�������� ���������� ��������
int getXORBigModbusBit(int);//�������� ���������� ����
int setXORBigModbusRegister(int, int);//�������� ���������� ��������
int setXORBigModbusBit(int, int);//�������� ���������� ����

void setXORBigCountObject(void);//�������� �-�� �������
void preXORBigReadAction(void);//action �� ������
void postXORBigReadAction(void);//action ����� ������
void preXORBigWriteAction(void);//action �� ������
int postXORBigWriteAction(void);//action ����� ������
void repairEditArrayXOR(int countRegister, __settings_for_XOR *arr, __settings_for_XOR *arr1);
void config_and_settingsXORBig(void);//action ���������

COMPONENT_OBJ *xorbigcomponent;

/**************************************/
//���������� ���������� XOR
/**************************************/
void constructorXORBigComponent(COMPONENT_OBJ *xorbigcomp)
{
  xorbigcomponent = xorbigcomp;

  xorbigcomponent->countObject = 0;//�-�� �������

  xorbigcomponent->getModbusRegister = getXORBigModbusRegister;//�������� ���������� ��������
  xorbigcomponent->getModbusBit      = getXORBigModbusBit;//�������� ���������� ����
  xorbigcomponent->setModbusRegister = setXORBigModbusRegister;//�������� ���������� ��������
  xorbigcomponent->setModbusBit      = setXORBigModbusBit;//�������� ���������� ����

  xorbigcomponent->preReadAction   = preXORBigReadAction;//action �� ������
  xorbigcomponent->postReadAction  = postXORBigReadAction;//action ����� ������
  xorbigcomponent->preWriteAction  = preXORBigWriteAction;//action �� ������
  xorbigcomponent->postWriteAction = postXORBigWriteAction;//action ����� ������
  xorbigcomponent->config_and_settings = config_and_settingsXORBig;//action ���������

  xorbigcomponent->isActiveActualData = 0;
}//prepareDVinConfig

int getXORBigModbusRegister(int adrReg)
{
  //�������� ���������� ��������
extern int pointInterface;//����� ���������� 0-USB 1-RS485
  if(privateXORBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(xorbigcomponent->isActiveActualData) setXORBigCountObject(); //�-�� �������
  xorbigcomponent->isActiveActualData = 0;
  if(privateXORBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  superSetOperativMarker(xorbigcomponent, adrReg);

  int offset = adrReg-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//������ ����������
  int idxParam = (offset/2)% 2;//������ param
  __settings_for_XOR *arr =  ((config_settings_modified & MASKA_FOR_BIT(BIT_USB_LOCKS)) == 0 ) ? &(((__LN_XOR*)(spca_of_p_prt[ID_FB_XOR - _ID_FB_FIRST_VAR])) + idxSubObj)->settings : (((__settings_for_XOR*)(sca_of_p[ID_FB_XOR - _ID_FB_FIRST_VAR])) + idxSubObj);
  if(pointInterface)//����� ���������� 0-USB 1-RS485
                        arr =  ((config_settings_modified & MASKA_FOR_BIT(BIT_RS485_LOCKS)) == 0 ) ? &(((__LN_XOR*)(spca_of_p_prt[ID_FB_XOR - _ID_FB_FIRST_VAR])) + idxSubObj)->settings : (((__settings_for_XOR*)(sca_of_p[ID_FB_XOR - _ID_FB_FIRST_VAR])) + idxSubObj);

  switch(offset%2) {//������ �������� 
   case 0:
        return  arr->param[idxParam] & 0xffff;//
   case 1:
        return  (arr->param[idxParam] >> 16) & 0x7fff;//
  }//switch
  return 0;
}//getDOUTBigModbusRegister(int adrReg)
int getXORBigModbusBit(int x)
{
  //�������� ���������� ��������
  UNUSED(x);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setXORBigModbusRegister(int adrReg, int dataReg)
{
  //�������� ���������� ��������
  if(privateXORBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(xorbigcomponent->isActiveActualData) setXORBigCountObject(); //�-�� �������
  xorbigcomponent->isActiveActualData = 0;
  if(privateXORBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  superSetOperativMarker(xorbigcomponent, adrReg);
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
  default: return MARKER_OUTPERIMETR;
  }//switch
  return 0;
}//getDOUTBigModbusRegister(int adrReg)
int setXORBigModbusBit(int x, int y)
{
  UNUSED(x);
  UNUSED(y);
  //�������� ���������� bit
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void setXORBigCountObject(void) {
//�������� �-�� �������
  int cntObj = current_config.n_xor;  //ʳ������ �������� "����.���"
  if(cntObj<0) return;
  if(cntObj>TOTAL_OBJ) return;
  xorbigcomponent->countObject = cntObj;
}//
void preXORBigReadAction(void) {
//action �� ������
  xorbigcomponent->operativMarker[0] = -1;
  xorbigcomponent->operativMarker[1] = -1;//����������� ������
  xorbigcomponent->isActiveActualData = 1;
}//
void postXORBigReadAction(void) {
//action ����� ������
  if(xorbigcomponent->operativMarker[0]<0) return;//�� ���� ������
}//
void preXORBigWriteAction(void) {
//action �� ������
  xorbigcomponent->operativMarker[0] = -1;
  xorbigcomponent->operativMarker[1] = -1;//����������� ������
  xorbigcomponent->isActiveActualData = 1;
}//
int postXORBigWriteAction(void) {
extern int pointInterface;//����� ���������� 0-USB 1-RS485
extern int upravlconfig_and_settings;//���� ��������� ����������
//action ����� ������
  if(xorbigcomponent->operativMarker[0]<0) return 0;//�� ���� ������
  int offsetTempWriteArray = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//����� �������� TempWriteArray
  int countRegister = xorbigcomponent->operativMarker[1]-xorbigcomponent->operativMarker[0]+1;
  if(xorbigcomponent->operativMarker[1]<0) countRegister = 1;

   __settings_for_XOR *arr  = (__settings_for_XOR*)(sca_of_p[ID_FB_XOR - _ID_FB_FIRST_VAR]);
   __settings_for_XOR *arr1 = (__settings_for_XOR*)(sca_of_p_edit[ID_FB_XOR - _ID_FB_FIRST_VAR]);
//�������� edit ������
  for(int i=0; i<countRegister; i++) {
  int offset = i+xorbigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//������ ����������
  int idx_SIGNALS_IN = (offset%REGISTER_FOR_OBJ)/2;//������ ����� ����������

  switch(offset%2) {//������ �������� �����
  case 0:
        arr1[idxSubObj].param[idx_SIGNALS_IN]  &= (uint32_t)~0xffff;
        arr1[idxSubObj].param[idx_SIGNALS_IN]  |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
  break;
  case 1:
        arr1[idxSubObj].param[idx_SIGNALS_IN]  &= (uint32_t)~(0x7fff<<16);
        arr1[idxSubObj].param[idx_SIGNALS_IN]  |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
  break;
 }//switch
  }//for

  //�������� ����������
  for(int i=0; i<countRegister; i++) {
  int offset = i+xorbigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//������ ����������
  int idx_SIGNALS_IN = (offset%REGISTER_FOR_OBJ)/2;//������ ����� ����������

  switch(offset%2) {//������ �������� �����
  case 0:
  case 1:
        if(superValidParam(arr1[idxSubObj].param[idx_SIGNALS_IN])) 
                {//�������� ����������
                repairEditArrayXOR(countRegister, arr, arr1);//������������ edit ������
                return 2;//����
        }//if
  break;
 }//switch
  }//for

//�������� ������� - ��������������
  for(int i=0; i<countRegister; i++) {
  int offset = i+xorbigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//������ ����������
  int idx_SIGNALS_IN = (offset%REGISTER_FOR_OBJ)/2;//������ ����� ����������

  switch(offset%2) {//������ �������� �����
  case 0:
        arr1[idxSubObj].param[idx_SIGNALS_IN] = arr[idxSubObj].param[idx_SIGNALS_IN] &= (uint32_t)~0xffff;
        arr1[idxSubObj].param[idx_SIGNALS_IN] = arr[idxSubObj].param[idx_SIGNALS_IN] |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
  break;
  case 1:
        arr1[idxSubObj].param[idx_SIGNALS_IN] = arr[idxSubObj].param[idx_SIGNALS_IN] &= (uint32_t)~(0x7fff<<16);
        arr1[idxSubObj].param[idx_SIGNALS_IN] = arr[idxSubObj].param[idx_SIGNALS_IN] |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
  break;
 }//switch
  }//for

  upravlconfig_and_settings=1;//���� ��������� ����������

  config_settings_modified |= MASKA_FOR_BIT(BIT_CHANGED_SCHEMATIC);
  if(pointInterface)//����� ���������� 0-USB 1-RS485
     config_settings_modified |= MASKA_FOR_BIT(BIT_RS485_LOCKS);
  else 
     config_settings_modified |= MASKA_FOR_BIT(BIT_USB_LOCKS);
  restart_timeout_idle_new_settings = true;
 return 0;
}//

void repairEditArrayXOR(int countRegister, __settings_for_XOR *arr, __settings_for_XOR *arr1) {
  //������������ edit ������
  for(int i=0; i<countRegister; i++) {
  int offset = i+xorbigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//������ ����������
  int idx_SIGNALS_IN = (offset%REGISTER_FOR_OBJ)/2;//������ ����� ����������

  switch(offset%2) {//������ �������� �����
  case 0:
  case 1:
        arr1[idxSubObj].param[idx_SIGNALS_IN] = arr[idxSubObj].param[idx_SIGNALS_IN];
  break;
 }//switch
  }//for
}//repairEditArray(int countRegister, __settings_for_XOR *arr, __settings_for_XOR *arr1) 

int privateXORBigGetReg1(int adrReg)
{
  //��������� ���������� ��������
  int count_register = xorbigcomponent->countObject*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg1(int adrReg)
int privateXORBigGetReg2(int adrReg)
{
  //��������� ������� ��������
  int count_register = TOTAL_OBJ*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)

void config_and_settingsXORBig(void)
{
extern int upravlconfig_and_settings;//���� ��������� ����������
//action ���������
  if(upravlconfig_and_settings==0) return;//���� ��������� ����������
   __settings_for_XOR *arr  = (__settings_for_XOR*)(sca_of_p[ID_FB_XOR - _ID_FB_FIRST_VAR]);
   __settings_for_XOR *arr1 = (__settings_for_XOR*)(sca_of_p_edit[ID_FB_XOR - _ID_FB_FIRST_VAR]);
  for(unsigned int i=0; i<current_config.n_xor; i++) 
  {
   superSortParam(2, &(arr1[i].param[0]));//����������
   superSortParam(2, &(arr[i].param[0]));//����������
  }//for
}

