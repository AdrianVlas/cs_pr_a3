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

  notbigcomponent->isActiveActualData = 0;
}//prepareDVinConfig
/*
void loadNOTBigActualData(void) {
 setNOTBigCountObject(); //�������� �-�� �������
  //ActualData
   __LN_NOT *arr = (__LN_NOT*)(spca_of_p_prt[ID_FB_NOT - _ID_FB_FIRST_VAR]);
   for(int item=0; item<notbigcomponent->countObject; item++) {

     for (int i = 0; i < 1; i ++)
     {
        int value = arr[item].settings.param[i] & 0xffff;//
        tempReadArray[item*REGISTER_FOR_OBJ+2*i+0] = value;
        value = (arr[item].settings.param[i] >> 16) & 0x7fff;//
        tempReadArray[item*REGISTER_FOR_OBJ+2*i+1] = value;
     }
   }//for
}//loadActualData() 
*/

int getNOTBigModbusRegister(int adrReg)
{
  //�������� ���������� ��������
  if(privateNOTBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(notbigcomponent->isActiveActualData) setNOTBigCountObject(); //�-�� �������
  notbigcomponent->isActiveActualData = 0;
  if(privateNOTBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  superSetOperativMarker(notbigcomponent, adrReg);

   __LN_NOT *arr = (__LN_NOT*)(spca_of_p_prt[ID_FB_NOT - _ID_FB_FIRST_VAR]);
  int offset = adrReg-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//������ ����������
  switch(offset%REGISTER_FOR_OBJ) {//������ �������� 
   case 0:
        return arr[idxSubObj].settings.param[0] & 0xffff;//
   case 1:
        return (arr[idxSubObj].settings.param[0] >> 16) & 0x7fff;//
  }//switch

  return 0;//tempReadArray[adrReg-BEGIN_ADR_REGISTER];
}//getDOUTBigModbusRegister(int adrReg)
int getNOTBigModbusBit(int adrBit)
{
  //�������� ���������� ��������
  superSetOperativMarker(notbigcomponent, adrBit);
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
int setNOTBigModbusBit(int adrBit, int x)
{
  UNUSED(x);
  //�������� ���������� ��������
  superSetOperativMarker(notbigcomponent, adrBit);
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
  if(notbigcomponent->operativMarker[0]<0) return 0;//�� ���� ������
  int offsetTempWriteArray = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//����� �������� TempWriteArray
  int countRegister = notbigcomponent->operativMarker[1]-notbigcomponent->operativMarker[0]+1;
  if(notbigcomponent->operativMarker[1]<0) countRegister = 1;

//   __LN_NOT *arr = (__LN_NOT*)(spca_of_p_prt[ID_FB_NOT - _ID_FB_FIRST_VAR]);
   __settings_for_NOT *arr  = (__settings_for_NOT*)(sca_of_p[ID_FB_NOT - _ID_FB_FIRST_VAR]);
   __settings_for_NOT *arr1 = (__settings_for_NOT*)(sca_of_p_edit[ID_FB_NOT - _ID_FB_FIRST_VAR]);
  for(int i=0; i<countRegister; i++) {
  int offset = i+notbigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//������ ����������

        arr1[idxSubObj].param[0] = arr[idxSubObj].param[0] &= (uint32_t)~0xffff;
        arr1[idxSubObj].param[0] = arr[idxSubObj].param[0] |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);

        arr1[idxSubObj].param[0] = arr[idxSubObj].param[0] &= (uint32_t)~(0x7fff<<16);
        arr1[idxSubObj].param[0] = arr[idxSubObj].param[0] |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
  }//for
  config_settings_modified |= MASKA_FOR_BIT(BIT_CHANGED_SCHEMATIC);
  restart_timeout_idle_new_settings = true;
 return 0;
}//

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
