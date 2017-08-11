#include "header.h"

//��������� ������� � ����� ������
#define BEGIN_ADR_REGISTER 10952
//���� �-�� �������
#define TOTAL_OBJ 128
#define REGISTER_FOR_OBJ 16

int privateORBigGetReg1(int adrReg);
int privateORBigGetReg2(int adrReg);

int getORBigModbusRegister(int);//�������� ���������� ��������
int getORBigModbusBit(int);//�������� ���������� ����
int setORBigModbusRegister(int, int);//�������� ���������� ��������
int setORBigModbusBit(int, int);//�������� ���������� ����

void setORBigCountObject(void);//�������� �-�� �������
void preORBigReadAction(void);//action �� ������
void postORBigReadAction(void);//action ����� ������
void preORBigWriteAction(void);//action �� ������
int postORBigWriteAction(void);//action ����� ������
//void loadORBigActualData(void);

COMPONENT_OBJ *orbigcomponent;

/**************************************/
//���������� ���������� OR
/**************************************/
void constructorORBigComponent(COMPONENT_OBJ *orbigcomp)
{
  orbigcomponent = orbigcomp;

  orbigcomponent->countObject = 0;//�-�� �������

  orbigcomponent->getModbusRegister = getORBigModbusRegister;//�������� ���������� ��������
  orbigcomponent->getModbusBit      = getORBigModbusBit;//�������� ���������� ����
  orbigcomponent->setModbusRegister = setORBigModbusRegister;//�������� ���������� ��������
  orbigcomponent->setModbusBit      = setORBigModbusBit;//�������� ���������� ����

  orbigcomponent->preReadAction   = preORBigReadAction;//action �� ������
  orbigcomponent->postReadAction  = postORBigReadAction;//action ����� ������
  orbigcomponent->preWriteAction  = preORBigWriteAction;//action �� ������
  orbigcomponent->postWriteAction = postORBigWriteAction;//action ����� ������

  orbigcomponent->isActiveActualData = 0;
}//prepareDVinConfig
/*
void loadORBigActualData(void) {
 setORBigCountObject(); //�������� �-�� �������
  //ActualData
   __LN_OR *arr = (__LN_OR*)(spca_of_p_prt[ID_FB_OR - _ID_FB_FIRST_VAR]);
   for(int item=0; item<orbigcomponent->countObject; item++) {

     for (int i = 0; i < OR_SIGNALS_IN; i ++)
     {
        int value = arr[item].settings.param[i] & 0xffff;//LEDIN 0 �� item
        tempReadArray[item*REGISTER_FOR_OBJ+2*i+0] = value;
        value = (arr[item].settings.param[i] >> 16) & 0x7fff;//LEDIN 1 �� item
        tempReadArray[item*REGISTER_FOR_OBJ+2*i+1] = value;
     }
   }//for
}//loadActualData() 
*/

int getORBigModbusRegister(int adrReg)
{
  //�������� ���������� ��������
  if(privateORBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(orbigcomponent->isActiveActualData) setORBigCountObject(); //�-�� �������
  orbigcomponent->isActiveActualData = 0;
  if(privateORBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  superSetOperativMarker(orbigcomponent, adrReg);

   __LN_OR *arr = (__LN_OR*)(spca_of_p_prt[ID_FB_OR - _ID_FB_FIRST_VAR]);
  int offset = adrReg-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//������ ����������
  int idxParam = (offset/2)%OR_SIGNALS_IN;//������ param
  switch(offset%2) {//������ �������� 
   case 0:
        return  arr[idxSubObj].settings.param[idxParam] & 0xffff;//
   case 1:
        return  (arr[idxSubObj].settings.param[idxParam] >> 16) & 0x7fff;//
  }//switch

  return 0;//tempReadArray[adrReg-BEGIN_ADR_REGISTER];
}//getDOUTBigModbusRegister(int adrReg)
int getORBigModbusBit(int adrReg)
{
  //�������� ���������� ��������
  superSetOperativMarker(orbigcomponent, adrReg);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setORBigModbusRegister(int adrReg, int dataReg)
{
  //�������� ���������� ��������
  if(privateORBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(orbigcomponent->isActiveActualData) setORBigCountObject(); //�-�� �������
  orbigcomponent->isActiveActualData = 0;
  if(privateORBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  superSetOperativMarker(orbigcomponent, adrReg);
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
   case 10:
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
   break; 
   case 11:
    //�������� ���������� ������������
    if(superControlParam(dataReg)) return MARKER_ERRORDIAPAZON;
   break; 
   case 12:
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
   break; 
   case 13:
    //�������� ���������� ������������
    if(superControlParam(dataReg)) return MARKER_ERRORDIAPAZON;
   break; 
   case 14:
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
   break; 
   case 15:
    //�������� ���������� ������������
    if(superControlParam(dataReg)) return MARKER_ERRORDIAPAZON;
   break; 
  default: return MARKER_OUTPERIMETR;
  }//switch
  return 0;
}//getDOUTBigModbusRegister(int adrReg)
int setORBigModbusBit(int adrBit, int x)
{
  UNUSED(x);
  //�������� ���������� ��������
  superSetOperativMarker(orbigcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void setORBigCountObject(void) {
//�������� �-�� �������
  int cntObj = current_config.n_or;    //ʳ������ �������� "���"
  if(cntObj<0) return;
  if(cntObj>TOTAL_OBJ) return;
  orbigcomponent->countObject = cntObj;
}//
void preORBigReadAction(void) {
//action �� ������
  orbigcomponent->operativMarker[0] = -1;
  orbigcomponent->operativMarker[1] = -1;//����������� ������
  orbigcomponent->isActiveActualData = 1;
}//
void postORBigReadAction(void) {
//action ����� ������
  if(orbigcomponent->operativMarker[0]<0) return;//�� ���� ������
}//
void preORBigWriteAction(void) {
//action �� ������
  orbigcomponent->operativMarker[0] = -1;
  orbigcomponent->operativMarker[1] = -1;//����������� ������
  orbigcomponent->isActiveActualData = 1;
}//
int postORBigWriteAction(void) {
//action ����� ������
  if(orbigcomponent->operativMarker[0]<0) return 0;//�� ���� ������
  int offsetTempWriteArray = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//����� �������� TempWriteArray
  int countRegister = orbigcomponent->operativMarker[1]-orbigcomponent->operativMarker[0]+1;
  if(orbigcomponent->operativMarker[1]<0) countRegister = 1;

//   __LN_OR *arr = (__LN_OR*)(spca_of_p_prt[ID_FB_OR - _ID_FB_FIRST_VAR]);
   __settings_for_OR *arr  = (__settings_for_OR*)(sca_of_p[ID_FB_OR - _ID_FB_FIRST_VAR]);
   __settings_for_OR *arr1 = (__settings_for_OR*)(sca_of_p_edit[ID_FB_OR - _ID_FB_FIRST_VAR]);
  for(int i=0; i<countRegister; i++) {
  int offset = i+orbigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;
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
   superSortParam(OR_SIGNALS_IN, &(arr1[idxSubObj].param[0]));//����������
   superSortParam(OR_SIGNALS_IN, &(arr[idxSubObj].param[0]));//����������
  }//for
  config_settings_modified |= MASKA_FOR_BIT(BIT_CHANGED_SCHEMATIC);
  restart_timeout_idle_new_settings = true;
 return 0;
}//

int privateORBigGetReg1(int adrReg)
{
  //��������� ���������� ��������
  int count_register = orbigcomponent->countObject*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg1(int adrReg)
int privateORBigGetReg2(int adrReg)
{
  //��������� ������� ��������
  int count_register = TOTAL_OBJ*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
