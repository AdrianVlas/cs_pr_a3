#include "header.h"

//��������� ������� � ����� ������
#define BEGIN_ADR_REGISTER 15500
//���� �-�� �������
#define REGISTER_FOR_OBJ 2
//���� �-�� �������
#define TOTAL_OBJ 128

int privateRegBigGetReg1(int adrReg);
int privateRegBigGetReg2(int adrReg);

void setRegBigCountObject(void);
int getRegBigModbusRegister(int);//�������� ���������� ��������
int getRegBigModbusBit(int);//�������� ���������� ����
int setRegBigModbusRegister(int, int);//�������� ���������� ��������
int setRegBigModbusBit(int, int);//�������� ���������� ����

void preRegBigReadAction(void);//action �� ������
void postRegBigReadAction(void);//action ����� ������
void preRegBigWriteAction(void);//action �� ������
int postRegBigWriteAction(void);//action ����� ������
void loadRegBigActualData(void);

COMPONENT_OBJ *regbigcomponent;

/**************************************/
//���������� ���������� �����������
/**************************************/
void constructorRegBigComponent(COMPONENT_OBJ *regbigcomp)
{
  regbigcomponent = regbigcomp;

  regbigcomponent->countObject = 0;//�-�� �������

  regbigcomponent->getModbusRegister = getRegBigModbusRegister;//�������� ���������� ��������
  regbigcomponent->getModbusBit      = getRegBigModbusBit;//�������� ���������� ����
  regbigcomponent->setModbusRegister = setRegBigModbusRegister;//�������� ���������� ��������
  regbigcomponent->setModbusBit      = setRegBigModbusBit;//�������� ���������� ����

  regbigcomponent->preReadAction   = preRegBigReadAction;//action �� ������
  regbigcomponent->postReadAction  = postRegBigReadAction;//action ����� ������
  regbigcomponent->preWriteAction  = preRegBigWriteAction;//action �� ������
  regbigcomponent->postWriteAction = postRegBigWriteAction;//action ����� ������

  regbigcomponent->isActiveActualData = 0;
}//prepareDVinConfig

void loadRegBigActualData(void) {
 setRegBigCountObject(); //�������� �-�� �������
  //ActualData
//   __LN_AND *arr = (__LN_AND*)(spca_of_p_prt[ID_FB_INPUT - _ID_FB_FIRST_VAR]);
   //����� ������ ������������ ������� ������������ 
   int value = 0;//arr[item].settings.param[0];
   tempReadArray[0] = value;

   //����� ������ ��������������� ������� ������������
   value = 0;//arr[item].settings.param[1];
   tempReadArray[1] = value;

   //���������� �������������
   value = 0;//arr[item].settings.param[1];
   tempReadArray[2] = value;

   //������� �����������
   value = 0;//arr[item].settings.param[1];
   tempReadArray[3] = value;

   //�������� ������ 0
   value = 0;//arr[item].settings.param[0];
   tempReadArray[4] = value;
   //�������� ������ 1
   value = 0;//arr[item].settings.param[1];
   tempReadArray[5] = value;

   for(int item=0; item<regbigcomponent->countObject; item++) {
   //���� item 0
   value = 0;//arr[item].settings.param[0];
   tempReadArray[6+item*REGISTER_FOR_OBJ+0] = value;
   //���� item 1
   value = 0;//arr[item].settings.param[1];
   tempReadArray[6+item*REGISTER_FOR_OBJ+1] = value;
  }//for
}//loadActualData() 

int getRegBigModbusRegister(int adrReg)
{
  //�������� ���������� ��������
  if(privateRegBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(regbigcomponent->isActiveActualData) loadRegBigActualData(); //ActualData
  regbigcomponent->isActiveActualData = 0;
  if(privateRegBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  superSetOperativMarker(regbigcomponent, adrReg);

  return tempReadArray[adrReg-BEGIN_ADR_REGISTER];
}//getDOUTBigModbusRegister(int adrReg)
int getRegBigModbusBit(int adrBit)
{
  //�������� ���������� ��������
  superSetOperativMarker(regbigcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setRegBigModbusRegister(int adrReg, int dataReg)
{
  //�������� ���������� ��������
  if(privateRegBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(regbigcomponent->isActiveActualData) setRegBigCountObject(); //�-�� �������
  regbigcomponent->isActiveActualData = 0;
  if(privateRegBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  superSetOperativMarker(regbigcomponent, adrReg);
  superSetTempWriteArray(dataReg);//�������� � �����

  switch(adrReg-BEGIN_ADR_REGISTER) {
   case 0: //12000
    if(dataReg>250) return MARKER_ERRORDIAPAZON;
    if(dataReg<5) return MARKER_ERRORDIAPAZON;
   break; 
   case 1: //12001
    if(dataReg>1250) return MARKER_ERRORDIAPAZON;
    if(dataReg<5) return MARKER_ERRORDIAPAZON;
   break; 
    case 2://12002
    if(dataReg>99) return MARKER_ERRORDIAPAZON;
   case 3: //12003
    if(dataReg>99) return MARKER_ERRORDIAPAZON;
   break; 
  }//switch

  return 0;
}//getDOUTBigModbusRegister(int adrReg)
int setRegBigModbusBit(int adrBit, int x)
{
  UNUSED(x);
  //�������� ���������� ��������
  superSetOperativMarker(regbigcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void setRegBigCountObject(void) {
//�������� �-�� �������
  int cntObj = current_config.n_log;    //ʳ������ ��������� ������� ����
  if(cntObj<0) return;
  if(cntObj>TOTAL_OBJ) return;
  regbigcomponent->countObject = cntObj;
}//

void preRegBigReadAction(void) {
//action �� ������
  regbigcomponent->operativMarker[0] = -1;
  regbigcomponent->operativMarker[1] = -1;//����������� ������
  regbigcomponent->isActiveActualData = 1;
}//
void postRegBigReadAction(void) {
//action ����� ������
  if(regbigcomponent->operativMarker[0]<0) return;//�� ���� ������
}//
void preRegBigWriteAction(void) {
//action �� ������
  regbigcomponent->operativMarker[0] = -1;
  regbigcomponent->operativMarker[1] = -1;//����������� ������
  regbigcomponent->isActiveActualData = 1;
}//
int postRegBigWriteAction(void) {
//action ����� ������
  if(regbigcomponent->operativMarker[0]<0) return 0;//�� ���� ������
  //int offsetTempWriteArray = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//����� �������� TempWriteArray
  int countRegister = regbigcomponent->operativMarker[1]-regbigcomponent->operativMarker[0]+1;
  if(regbigcomponent->operativMarker[1]<0) countRegister = 1;

//   __LOG_INPUT *arr = (__LOG_INPUT*)(spca_of_p_prt[ID_FB_EVENT_LOG - _ID_FB_FIRST_VAR]) + 1;
  for(int i=0; i<countRegister; i++) {
  int offset = i+regbigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;
//  int idxSubObj = offset/REGISTER_FOR_OBJ;//������ ����������
//  int clrME = 6;
  switch(offset%REGISTER_FOR_OBJ) {//������ �������� 
//   case 0://�������� ������ 0
//   break;
//   case 1://�������� ������ 1
//   break;

   case 0://���� 0 item
//        arr[clrME+idxSubObj] &= ~0xffff;
//        arr[clrME+idxSubObj] |= (tempWriteArray[clrME+offsetTempWriteArray+i] & 0xffff);
   break;
   case 1://���� 1 item
//        arr[clrME+idxSubObj] &= ~(0x7fff<<16);
//        arr[clrME+idxSubObj] |= ((tempWriteArray[clrME+offsetTempWriteArray+i] & 0x7fff)<<16);//
   break; 

 }//switch
  }//for
  config_settings_modified |= MASKA_FOR_BIT(BIT_CHANGED_SETTINGS);
  restart_timeout_idle_new_settings = true;
  return 0;
}//

int privateRegBigGetReg1(int adrReg)
{
  //��������� ������� ��������
  int count_register = 6+regbigcomponent->countObject*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
int privateRegBigGetReg2(int adrReg)
{
  //��������� ������� ��������
  int count_register = 6+TOTAL_OBJ*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
