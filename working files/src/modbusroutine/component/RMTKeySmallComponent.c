#include "header.h"

//��������� ������� � ����� ������
#define BEGIN_ADR_REGISTER 408
//��������� bit � ����� ������
#define BEGIN_ADR_BIT 20128
//���� �-�� �������
#define BIT_FOR_OBJ 1

int privateRMTKeySmallGetReg2(int adrReg);
int privateRMTKeySmallGetBit2(int adrReg);

int getRMTKeySmallModbusRegister(int);//�������� ���������� ��������
int getRMTKeySmallModbusBit(int);//�������� ���������� ����
int setRMTKeySmallModbusRegister(int, int);//�������� ���������� ��������
int setRMTKeySmallModbusBit(int, int);//�������� ���������� ����

void setRMTKeySmallCountObject(void);//�������� �-�� �������
void preRMTKeySmallReadAction(void);//action �� ������
void postRMTKeySmallReadAction(void);//action ����� ������
void preRMTKeySmallWriteAction(void);//action �� ������
int postRMTKeySmallWriteAction(void);//action ����� ������
void loadRMTKeySmallActualData(void);

COMPONENT_OBJ *rmtkeysmallcomponent;

/**************************************/
//���������� ���������� ������������ ������ MUTE RESET TEST
/**************************************/
void constructorRMTKeySmallComponent(COMPONENT_OBJ *rmtkeysmallcomp)
{
  rmtkeysmallcomponent = rmtkeysmallcomp;

  rmtkeysmallcomponent->countObject = 3;//�-�� �������

  rmtkeysmallcomponent->getModbusRegister = getRMTKeySmallModbusRegister;//�������� ���������� ��������
  rmtkeysmallcomponent->getModbusBit      = getRMTKeySmallModbusBit;//�������� ���������� ����
  rmtkeysmallcomponent->setModbusRegister = setRMTKeySmallModbusRegister;//�������� ���������� ��������
  rmtkeysmallcomponent->setModbusBit      = setRMTKeySmallModbusBit;//�������� ���������� ����

  rmtkeysmallcomponent->preReadAction   = preRMTKeySmallReadAction;//action �� ������
  rmtkeysmallcomponent->postReadAction  = postRMTKeySmallReadAction;//action ����� ������
  rmtkeysmallcomponent->preWriteAction  = preRMTKeySmallWriteAction;//action �� ������
  rmtkeysmallcomponent->postWriteAction = postRMTKeySmallWriteAction;//action ����� ������

  rmtkeysmallcomponent->isActiveActualData = 0;
}//prepareDVinConfig

void loadRMTKeySmallActualData(void) {
  //ActualData
  setRMTKeySmallCountObject(); //�������� �-�� �������

   tempReadArray[0] = 0;
   __LN_BUTTON *arr = (__LN_BUTTON*)(spca_of_p_prt[ID_FB_BUTTON - _ID_FB_FIRST_VAR]);

   int value = arr[FIX_BUTTON_RESET].active_state[BUTTON_OUT >> 3] & (1 << (BUTTON_OUT & ((1 << 3) - 1)));
   int keydata = 0;
   if(value) keydata=1;
   tempReadArray[0] |= (keydata&0x1)<<(0);

   value = arr[FIX_BUTTON_MUTE].active_state[BUTTON_OUT >> 3] & (1 << (BUTTON_OUT & ((1 << 3) - 1)));
   keydata = 0;
   if(value) keydata=1;
   tempReadArray[0] |= (keydata&0x1)<<(1);

   value = arr[FIX_BUTTON_TEST].active_state[BUTTON_OUT >> 3] & (1 << (BUTTON_OUT & ((1 << 3) - 1)));
   keydata = 0;
   if(value) keydata=1;
   tempReadArray[0] |= (keydata&0x1)<<(2);

}//loadActualData() 

int getRMTKeySmallModbusRegister(int adrReg)
{
  //�������� ���������� ��������
  if(privateRMTKeySmallGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  if(rmtkeysmallcomponent->isActiveActualData) loadRMTKeySmallActualData(); //ActualData
  rmtkeysmallcomponent->isActiveActualData = 0;

  superSetOperativMarker(rmtkeysmallcomponent, adrReg);

  return tempReadArray[adrReg-BEGIN_ADR_REGISTER];
}//getDOUTModbusRegister(int adrReg)
int getRMTKeySmallModbusBit(int adrBit)
{
  //�������� ���������� bit
  if(privateRMTKeySmallGetBit2(adrBit)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  if(rmtkeysmallcomponent->isActiveActualData) loadRMTKeySmallActualData();
  rmtkeysmallcomponent->isActiveActualData = 0;

  superSetOperativMarker(rmtkeysmallcomponent, adrBit);

  short tmp   = tempReadArray[(adrBit-BEGIN_ADR_BIT)/16];
  short maska = 1<<((adrBit-BEGIN_ADR_BIT)%16);
  if(tmp&maska) return 1;
  return 0;
}//getDOUTBigModbusRegister(int adrReg)
int setRMTKeySmallModbusRegister(int x, int y)
{
  UNUSED(x);
  UNUSED(y);
  //�������� ���������� ��������
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setRMTKeySmallModbusBit(int x, int y)
{
  UNUSED(x);
  UNUSED(y);
  //�������� ���������� ��������
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void setRMTKeySmallCountObject(void) {
//�������� �-�� �������
}//
void preRMTKeySmallReadAction(void) {
//action �� ������
  rmtkeysmallcomponent->operativMarker[0] = -1;
  rmtkeysmallcomponent->operativMarker[1] = -1;//����������� ������
  rmtkeysmallcomponent->isActiveActualData = 1;
}//
void postRMTKeySmallReadAction(void) {
//action ����� ������
  if(rmtkeysmallcomponent->operativMarker[0]<0) return;//�� ���� ������
}//
void preRMTKeySmallWriteAction(void) {
//action �� ������
  rmtkeysmallcomponent->operativMarker[0] = -1;
  rmtkeysmallcomponent->operativMarker[1] = -1;//����������� ������
  rmtkeysmallcomponent->isActiveActualData = 1;
}//
int postRMTKeySmallWriteAction(void) {
//action ����� ������
  return 0;
}//

int privateRMTKeySmallGetReg2(int adrReg)
{
  //��������� ���������� ��������
  int count_register = rmtkeysmallcomponent->countObject/16;
  if(rmtkeysmallcomponent->countObject%16) count_register++;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateDOUTSmallGetReg2(int adrReg)

int privateRMTKeySmallGetBit2(int adrBit)
{
  //��������� ���������� ��������
  int count_bit = BIT_FOR_OBJ*rmtkeysmallcomponent->countObject;
  if(adrBit>=BEGIN_ADR_BIT && adrBit<(BEGIN_ADR_BIT+count_bit)) return 0;
  return MARKER_OUTPERIMETR;
}//privateDOUTSmallGetBit2(int adrBit)
