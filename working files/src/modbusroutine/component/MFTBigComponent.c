#include "header.h"

//��������� ������� � ����� ������
#define BEGIN_ADR_REGISTER 6107
//���� �-�� �������
#define TOTAL_OBJ 128
#define REGISTER_FOR_OBJ 6

int privateMFTBigGetReg1(int adrReg);
int privateMFTBigGetReg2(int adrReg);

int getMFTBigModbusRegister(int);//�������� ���������� ��������
int getMFTBigModbusBit(int);//�������� ���������� ����
int setMFTBigModbusRegister(int, int);//�������� ���������� ��������
int setMFTBigModbusBit(int, int);//�������� ���������� ����

void setMFTBigCountObject(void);//�������� �-�� �������
void preMFTBigReadAction(void);//action �� ������
void postMFTBigReadAction(void);//action ����� ������
void preMFTBigWriteAction(void);//action �� ������
int postMFTBigWriteAction(void);//action ����� ������
void loadMFTBigActualData(void);

COMPONENT_OBJ *mftbigcomponent;

/**************************************/
//���������� ���������� ���
/**************************************/
void constructorMFTBigComponent(COMPONENT_OBJ *mftbigcomp)
{
  mftbigcomponent = mftbigcomp;

  mftbigcomponent->countObject = 0;//�-�� �������

  mftbigcomponent->getModbusRegister = getMFTBigModbusRegister;//�������� ���������� ��������
  mftbigcomponent->getModbusBit      = getMFTBigModbusBit;//�������� ���������� ����
  mftbigcomponent->setModbusRegister = setMFTBigModbusRegister;//�������� ���������� ��������
  mftbigcomponent->setModbusBit      = setMFTBigModbusBit;//�������� ���������� ����

  mftbigcomponent->preReadAction   = preMFTBigReadAction;//action �� ������
  mftbigcomponent->postReadAction  = postMFTBigReadAction;//action ����� ������
  mftbigcomponent->preWriteAction  = preMFTBigWriteAction;//action �� ������
  mftbigcomponent->postWriteAction = postMFTBigWriteAction;//action ����� ������

  mftbigcomponent->isActiveActualData = 0;
}//prepareDVinConfig

void loadMFTBigActualData(void) {
 setMFTBigCountObject(); //�������� �-�� �������
  //ActualData
   __LN_TIMER *arr = (__LN_TIMER*)(spca_of_p_prt[ID_FB_TIMER - _ID_FB_FIRST_VAR]);
   for(int item=0; item<mftbigcomponent->countObject; item++) {

   //������ �����  item
   int value = arr[item].settings.set_delay[TIMER_SET_DELAY_PAUSE]/10;
   tempReadArray[item*REGISTER_FOR_OBJ+0] = value;

   //������ ������   item
   value = arr[item].settings.set_delay[TIMER_SET_DELAY_WORK]/10;
   tempReadArray[item*REGISTER_FOR_OBJ+1] = value;

   //MFT-IN 1 0 item
   value = arr[item].settings.param[TIMER_LOGIC_INPUT] & 0xffff;//LEDIN 0 �� item
   tempReadArray[item*REGISTER_FOR_OBJ+2] = value;
   value = (arr[item].settings.param[TIMER_LOGIC_INPUT] >> 16) & 0x7fff;//LEDIN 1 �� item
   tempReadArray[item*REGISTER_FOR_OBJ+3] = value;

   //Reset-I  0 item
   value = arr[item].settings.param[TIMER_RESET] & 0xffff;//LEDIN 0 �� item
   tempReadArray[item*REGISTER_FOR_OBJ+4] = value;
   value = (arr[item].settings.param[TIMER_RESET] >> 16) & 0x7fff;//LEDIN 1 �� item
   tempReadArray[item*REGISTER_FOR_OBJ+5] = value;
   }//for

}//loadActualData() 

int getMFTBigModbusRegister(int adrReg)
{
  //�������� ���������� ��������
  if(privateMFTBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(mftbigcomponent->isActiveActualData) loadMFTBigActualData(); //ActualData
  mftbigcomponent->isActiveActualData = 0;
  if(privateMFTBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  superSetOperativMarker(mftbigcomponent, adrReg);

  return tempReadArray[adrReg-BEGIN_ADR_REGISTER];
}//getDOUTBigModbusRegister(int adrReg)
int getMFTBigModbusBit(int adrBit)
{
  //�������� ���������� ��������
  superSetOperativMarker(mftbigcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setMFTBigModbusRegister(int adrReg, int dataReg)
{
  //�������� ���������� ��������
  if(privateMFTBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(mftbigcomponent->isActiveActualData) setMFTBigCountObject(); //�-�� �������
  mftbigcomponent->isActiveActualData = 0;
  if(privateMFTBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  superSetOperativMarker(mftbigcomponent, adrReg);
  superSetTempWriteArray(dataReg);//�������� � �����

  switch((adrReg-BEGIN_ADR_REGISTER)%REGISTER_FOR_OBJ) {
   case 0:
    if(dataReg>60000) return MARKER_ERRORDIAPAZON;
   break; 
   case 1:
    if(dataReg>60000) return MARKER_ERRORDIAPAZON;
   break; 
   case 2:
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
   break; 
   case 3:
   break; 
   case 4:
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
   break; 
   case 5:
   break; 
  default: return MARKER_OUTPERIMETR;
  }//switch
  return 0;
}//getDOUTBigModbusRegister(int adrReg)
int setMFTBigModbusBit(int adrBit, int x)
{
  UNUSED(x);
  //�������� ���������� ��������
  superSetOperativMarker(mftbigcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void setMFTBigCountObject(void) {
//�������� �-�� �������
  int cntObj = current_config.n_timer;   //ʳ������ �������
  if(cntObj<0) return;
  if(cntObj>TOTAL_OBJ) return;
  mftbigcomponent->countObject = cntObj;
}//
void preMFTBigReadAction(void) {
//action �� ������
  mftbigcomponent->operativMarker[0] = -1;
  mftbigcomponent->operativMarker[1] = -1;//����������� ������
  mftbigcomponent->isActiveActualData = 1;
}//
void postMFTBigReadAction(void) {
//action ����� ������
  if(mftbigcomponent->operativMarker[0]<0) return;//�� ���� ������
}//
void preMFTBigWriteAction(void) {
//action �� ������
  mftbigcomponent->operativMarker[0] = -1;
  mftbigcomponent->operativMarker[1] = -1;//����������� ������
  mftbigcomponent->isActiveActualData = 1;
}//
int postMFTBigWriteAction(void) {
//action ����� ������
  if(mftbigcomponent->operativMarker[0]<0) return 0;//�� ���� ������
  int offsetTempWriteArray = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//����� �������� TempWriteArray
  int countRegister = mftbigcomponent->operativMarker[1]-mftbigcomponent->operativMarker[0]+1;
  if(mftbigcomponent->operativMarker[1]<0) countRegister = 1;

//   __LN_TIMER *arr = (__LN_TIMER*)(spca_of_p_prt[ID_FB_TIMER - _ID_FB_FIRST_VAR]);
   __settings_for_TIMER *arr  = (__settings_for_TIMER*)(sca_of_p[ID_FB_TIMER - _ID_FB_FIRST_VAR]);
   __settings_for_TIMER *arr1 = (__settings_for_TIMER*)(sca_of_p_edit[ID_FB_TIMER - _ID_FB_FIRST_VAR]);
  for(int i=0; i<countRegister; i++) {
  int offset = i+mftbigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//������ ����������
  switch(offset%REGISTER_FOR_OBJ) {//������ �������� 
   case 0://������ �����
    arr1[idxSubObj].set_delay[TIMER_SET_DELAY_PAUSE] = arr[idxSubObj].set_delay[TIMER_SET_DELAY_PAUSE] = (tempWriteArray[offsetTempWriteArray+i]);
   break;
   case 1://������ ������
    arr1[idxSubObj].set_delay[TIMER_SET_DELAY_WORK] = arr[idxSubObj].set_delay[TIMER_SET_DELAY_WORK] = (tempWriteArray[offsetTempWriteArray+i]);
   break;

   case 2://MFT-IN 0 item
        arr1[idxSubObj].param[TIMER_LOGIC_INPUT] = arr[idxSubObj].param[TIMER_LOGIC_INPUT] &= (uint32_t)~0xffff;
        arr1[idxSubObj].param[TIMER_LOGIC_INPUT] = arr[idxSubObj].param[TIMER_LOGIC_INPUT] |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
   break;
   case 3://MFT-IN 1 item
        arr1[idxSubObj].param[TIMER_LOGIC_INPUT] = arr[idxSubObj].param[TIMER_LOGIC_INPUT] &= (uint32_t)~(0x7fff<<16);
        arr1[idxSubObj].param[TIMER_LOGIC_INPUT] = arr[idxSubObj].param[TIMER_LOGIC_INPUT] |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
   break; 

   case 4://Reset-I 0 item
        arr1[idxSubObj].param[TIMER_RESET] = arr[idxSubObj].param[TIMER_RESET] &= (uint32_t)~0xffff;
        arr1[idxSubObj].param[TIMER_RESET] = arr[idxSubObj].param[TIMER_RESET] |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
   break;
   case 5://Reset-I 1 item
        arr1[idxSubObj].param[TIMER_RESET] = arr[idxSubObj].param[TIMER_RESET] &= (uint32_t)~(0x7fff<<16);
        arr1[idxSubObj].param[TIMER_RESET] = arr[idxSubObj].param[TIMER_RESET] |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
   break; 
 }//switch
  }//for
  config_settings_modified |= MASKA_FOR_BIT(BIT_CHANGED_SETTINGS);
  restart_timeout_idle_new_settings = true;
 return 0;
}//

int privateMFTBigGetReg1(int adrReg)
{
  //��������� ���������� ��������
  int count_register = mftbigcomponent->countObject*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg1(int adrReg)
int privateMFTBigGetReg2(int adrReg)
{
  //��������� ������� ��������
  int count_register = TOTAL_OBJ*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
