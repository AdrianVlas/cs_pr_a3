#include "header.h"

//��������� ������� � ����� ������
#define BEGIN_ADR_REGISTER 15000
//���� �-�� �������
#define REGISTER_FOR_OBJ 2
//���� �-�� �������
#define TOTAL_OBJ 128

int privateMEBigGetReg1(int adrReg);
int privateMEBigGetReg2(int adrReg);

int getMEBigModbusRegister(int);//�������� ���������� ��������
int getMEBigModbusBit(int);//�������� ���������� ����
int setMEBigModbusRegister(int, int);//�������� ���������� ��������
int setMEBigModbusBit(int, int);//�������� ���������� ����

void setMEBigCountObject(void);
void preMEBigReadAction(void);//action �� ������
void postMEBigReadAction(void);//action ����� ������
void preMEBigWriteAction(void);//action �� ������
int postMEBigWriteAction(void);//action ����� ������
void loadMEBigActualData(void);

COMPONENT_OBJ *mebigcomponent;

/**************************************/
//���������� ���������� ������ �������
/**************************************/
void constructorMEBigComponent(COMPONENT_OBJ *mebigcomp)
{
  mebigcomponent = mebigcomp;

  mebigcomponent->countObject = 0;//�-�� �������

  mebigcomponent->getModbusRegister = getMEBigModbusRegister;//�������� ���������� ��������
  mebigcomponent->getModbusBit      = getMEBigModbusBit;//�������� ���������� ��������
  mebigcomponent->setModbusRegister = setMEBigModbusRegister;//�������� ���������� ��������
  mebigcomponent->setModbusBit      = setMEBigModbusBit;//�������� ���������� ��������

  mebigcomponent->preReadAction   = preMEBigReadAction;//action �� ������
  mebigcomponent->postReadAction  = postMEBigReadAction;//action ����� ������
  mebigcomponent->preWriteAction  = preMEBigWriteAction;//action �� ������
  mebigcomponent->postWriteAction = postMEBigWriteAction;//action ����� ������

  mebigcomponent->isActiveActualData = 0;
}//prepareDVinConfig

void loadMEBigActualData(void) {
 setMEBigCountObject(); //�������� �-�� �������
  //ActualData
 //!!!!!!!!!!
   __LOG_INPUT *arr = (__LOG_INPUT*)(spca_of_p_prt[ID_FB_EVENT_LOG - _ID_FB_FIRST_VAR]) + 1;
   //�������� ������ 0
   int value = 0;//arr[item].settings.param[0];
   tempReadArray[0] = value;
   //�������� ������ 1
   value = 0;//arr[item].settings.param[1];
   tempReadArray[1] = value;

   for(int item=0; item<mebigcomponent->countObject; item++) {
   //���� item 0
        value = arr[item] & 0xffff;//
        tempReadArray[2+item*REGISTER_FOR_OBJ+2*item+0] = value;
        value = (arr[item] >> 16) & 0x7fff;//
        tempReadArray[2+item*REGISTER_FOR_OBJ+2*item+1] = value;
  }//for
}//loadActualData() 

int getMEBigModbusRegister(int adrReg)
{
  //�������� ���������� ��������
  if(privateMEBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(mebigcomponent->isActiveActualData) loadMEBigActualData(); //ActualData
  mebigcomponent->isActiveActualData = 0;
  if(privateMEBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  superSetOperativMarker(mebigcomponent, adrReg);

  return tempReadArray[adrReg-BEGIN_ADR_REGISTER];
}//getDOUTBigModbusRegister(int adrReg)
int getMEBigModbusBit(int adrBit)
{
  //�������� ���������� ��������
  superSetOperativMarker(mebigcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void setMEBigCountObject(void) {
//�������� �-�� �������
  int cntObj = current_config.n_log*LOG_SIGNALS_IN;    //ʳ������ ��������� ������� ����
  if (cntObj > 128) cntObj = 128;
  if(cntObj<0) return;
  if(cntObj>TOTAL_OBJ) return;
  mebigcomponent->countObject = cntObj;
}//
int setMEBigModbusRegister(int adrReg, int dataReg)
{
  //�������� ���������� ��������
  if(privateMEBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(mebigcomponent->isActiveActualData) setMEBigCountObject(); //�-�� �������
  mebigcomponent->isActiveActualData = 0;
  if(privateMEBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  superSetOperativMarker(mebigcomponent, adrReg);
  superSetTempWriteArray(dataReg);//�������� � �����

  return 0;
}//getDOUTBigModbusRegister(int adrReg)
int setMEBigModbusBit(int adrBit, int x)
{
  UNUSED(x);
  //�������� ���������� ��������
  superSetOperativMarker(mebigcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void preMEBigReadAction(void) {
//action �� ������
  mebigcomponent->operativMarker[0] = -1;
  mebigcomponent->operativMarker[1] = -1;//����������� ������
  mebigcomponent->isActiveActualData = 1;
}//
void postMEBigReadAction(void) {
//action ����� ������
  if(mebigcomponent->operativMarker[0]<0) return;//�� ���� ������
}//
void preMEBigWriteAction(void) {
//action �� ������
  mebigcomponent->operativMarker[0] = -1;
  mebigcomponent->operativMarker[1] = -1;//����������� ������
  mebigcomponent->isActiveActualData = 1;
}//
int postMEBigWriteAction(void) {
//action ����� ������
  if(mebigcomponent->operativMarker[0]<0) return 0;//�� ���� ������
//  int offsetTempWriteArray = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//����� �������� TempWriteArray
  int countRegister = mebigcomponent->operativMarker[1]-mebigcomponent->operativMarker[0]+1;
  if(mebigcomponent->operativMarker[1]<0) countRegister = 1;

//   __LOG_INPUT *arr = (__LOG_INPUT*)(spca_of_p_prt[ID_FB_EVENT_LOG - _ID_FB_FIRST_VAR]) + 1;
//   __settings_for_INPUT *arr  = (__settings_for_INPUT*)(sca_of_p[ID_FB_EVENT_LOG - _ID_FB_FIRST_VAR]);
//   __settings_for_INPUT *arr1 = (__settings_for_INPUT*)(sca_of_p_edit[ID_FB_EVENT_LOG - _ID_FB_FIRST_VAR]);
  for(int i=0; i<countRegister; i++) {
  int offset = i+mebigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;
 // int idxSubObj = offset/REGISTER_FOR_OBJ;//������ ����������
//  int clrME = 2;
  switch(offset%REGISTER_FOR_OBJ) {//������ �������� 
//   case 0://�������� ������ 0
//   break;
//   case 1://�������� ������ 1
//   break;

   case 0://���� 0 item
//        arr1[clrME+idxSubObj] = arr[clrME+idxSubObj] &= (uint32_t)~0xffff;
//        arr1[clrME+idxSubObj] = arr[clrME+idxSubObj] |= (tempWriteArray[clrME+offsetTempWriteArray+i] & 0xffff);
   break;
   case 1://���� 1 item
//        arr1[clrME+idxSubObj] = arr[clrME+idxSubObj] &= (uint32_t)~(0x7fff<<16);
//        arr1[clrME+idxSubObj] = arr[clrME+idxSubObj] |= ((tempWriteArray[clrME+offsetTempWriteArray+i] & 0x7fff)<<16);//
   break; 

 }//switch
  }//for
  config_settings_modified |= MASKA_FOR_BIT(BIT_CHANGED_SETTINGS);
  restart_timeout_idle_new_settings = true;
 return 0;
}//

int privateMEBigGetReg1(int adrReg)
{
  //��������� ���������� ��������
  int count_register = 2+mebigcomponent->countObject*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
int privateMEBigGetReg2(int adrReg)
{
  //��������� ������� ��������
  int count_register = 2+TOTAL_OBJ*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
