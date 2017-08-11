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
//void loadXORBigActualData(void);

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

  xorbigcomponent->isActiveActualData = 0;
}//prepareDVinConfig
/*
void loadXORBigActualData(void) {
 setXORBigCountObject(); //�������� �-�� �������
  //ActualData
   __LN_XOR *arr = (__LN_XOR*)(spca_of_p_prt[ID_FB_XOR - _ID_FB_FIRST_VAR]);
   for(int item=0; item<xorbigcomponent->countObject; item++) {

     for (int i = 0; i < 2; i ++)
     {
        int value = arr[item].settings.param[i] & 0xffff;//LEDIN 0 �� item
        tempReadArray[item*REGISTER_FOR_OBJ+2*i+0] = value;
        value = (arr[item].settings.param[i] >> 16) & 0x7fff;//LEDIN 1 �� item
        tempReadArray[item*REGISTER_FOR_OBJ+2*i+1] = value;
     }
   }//for
}//loadActualData() 
*/

int getXORBigModbusRegister(int adrReg)
{
  //�������� ���������� ��������
  if(privateXORBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(xorbigcomponent->isActiveActualData) setXORBigCountObject(); //�-�� �������
  xorbigcomponent->isActiveActualData = 0;
  if(privateXORBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  superSetOperativMarker(xorbigcomponent, adrReg);

   __LN_XOR *arr = (__LN_XOR*)(spca_of_p_prt[ID_FB_XOR - _ID_FB_FIRST_VAR]);
  int offset = adrReg-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//������ ����������
  int idxParam = (offset/2)%AND_SIGNALS_IN;//������ param
  switch(offset%2) {//������ �������� 
   case 0:
        return  arr[idxSubObj].settings.param[idxParam] & 0xffff;//
   case 1:
        return  (arr[idxSubObj].settings.param[idxParam] >> 16) & 0x7fff;//
  }//switch

  return 0;//tempReadArray[adrReg-BEGIN_ADR_REGISTER];
}//getDOUTBigModbusRegister(int adrReg)
int getXORBigModbusBit(int adrBit)
{
  //�������� ���������� ��������
  superSetOperativMarker(xorbigcomponent, adrBit);
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
int setXORBigModbusBit(int adrBit, int x)
{
  UNUSED(x);
  //�������� ���������� bit
  superSetOperativMarker(xorbigcomponent, adrBit);
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
//action ����� ������
  if(xorbigcomponent->operativMarker[0]<0) return 0;//�� ���� ������
  int offsetTempWriteArray = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//����� �������� TempWriteArray
  int countRegister = xorbigcomponent->operativMarker[1]-xorbigcomponent->operativMarker[0]+1;
  if(xorbigcomponent->operativMarker[1]<0) countRegister = 1;

//   __LN_XOR *arr = (__LN_XOR*)(spca_of_p_prt[ID_FB_XOR - _ID_FB_FIRST_VAR]);
   __settings_for_XOR *arr  = (__settings_for_XOR*)(sca_of_p[ID_FB_XOR - _ID_FB_FIRST_VAR]);
   __settings_for_XOR *arr1 = (__settings_for_XOR*)(sca_of_p_edit[ID_FB_XOR - _ID_FB_FIRST_VAR]);
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
   superSortParam(2, &(arr1[idxSubObj].param[0]));//����������
   superSortParam(2, &(arr[idxSubObj].param[0]));//����������
  }//for
  config_settings_modified |= MASKA_FOR_BIT(BIT_CHANGED_SCHEMATIC);
  restart_timeout_idle_new_settings = true;
 return 0;
}//

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
