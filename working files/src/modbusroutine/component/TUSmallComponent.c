#include "header.h"

//��������� ������� � ����� ������
#define BEGIN_ADR_REGISTER 208
//��������� bit � ����� ������
#define BEGIN_ADR_BIT 18128
#define BIT_FOR_OBJ 1
//���� �-�� �������
#define TOTAL_OBJ 128
int privateTUSmallGetReg1(int adrReg);
int privateTUSmallGetReg2(int adrReg);
int privateTUSmallGetBit1(int adrBit);
int privateTUSmallGetBit2(int adrBit);

int getTUSmallModbusRegister(int);//�������� ���������� ��������
int getTUSmallModbusBit(int);//�������� ���������� ����
int setTUSmallModbusRegister(int, int);//�������� ���������� ��������
int setTUSmallModbusBit(int, int);//�������� ���������� ����

void setTUSmallCountObject(void);//�������� �-�� �������
void preTUSmallReadAction(void);//action �� ������
void postTUSmallReadAction(void);//action ����� ������
void preTUSmallWriteAction(void);//action �� ������
int postTUSmallWriteAction(void);//action ����� ������
void loadTUSmallActualData(void);
int getTUmallModbusBeginAdrRegister(void);

COMPONENT_OBJ *tusmallcomponent;

int getTUmallModbusBeginAdrRegister(void)
{
  //�������� ����� ��� ��������
 return BEGIN_ADR_REGISTER;
}//getTSmallModbusBeginAdrRegister(void)

/**************************************/
//���������� ���������� ��������������
/**************************************/
void constructorTUSmallComponent(COMPONENT_OBJ *tusmallcomp)
{
  tusmallcomponent = tusmallcomp;

  tusmallcomponent->countObject = 0;//�-�� �������

  tusmallcomponent->getModbusRegister = getTUSmallModbusRegister;//�������� ���������� ��������
  tusmallcomponent->getModbusBit      = getTUSmallModbusBit;//�������� ���������� ����
  tusmallcomponent->setModbusRegister = setTUSmallModbusRegister;//�������� ���������� ��������
  tusmallcomponent->setModbusBit      = setTUSmallModbusBit;//�������� ���������� ����

  tusmallcomponent->preReadAction   = preTUSmallReadAction;//action �� ������
  tusmallcomponent->postReadAction  = postTUSmallReadAction;//action ����� ������
  tusmallcomponent->preWriteAction  = preTUSmallWriteAction;//action �� ������
  tusmallcomponent->postWriteAction = postTUSmallWriteAction;//action ����� ������

  tusmallcomponent->isActiveActualData = 0;
}//prepareDVinConfig
/*
void loadTUSmallActualData(void) {
 setTUSmallCountObject(); //�������� �-�� �������

  //ActualData
  int cnt_treg = tusmallcomponent->countObject/16;
  if(tusmallcomponent->countObject%16) cnt_treg++;
  for(int ii=0; ii<cnt_treg; ii++) tempReadArray[ii] = 0;
   __LN_TU *arr = (__LN_TU*)(spca_of_p_prt[ID_FB_TU - _ID_FB_FIRST_VAR]);
  for(int item=0; item<tusmallcomponent->countObject; item++) {
   int ireg = item/16;

   int value = arr[item].active_state[TU_OUT  >> 3] & (1 << (TU_OUT  & ((1 << 3) - 1)));
   
   int tudata = 0;
   if(value) tudata=1;
   tempReadArray[ireg] |= (tudata&0x1)<<(item%16);
  }//for
}//loadActualData() 
*/

int getTUSmallModbusRegister(int x)
{
  //�������� ���������� ��������
  UNUSED(x);
  return MARKER_OUTPERIMETR;

}//getDVModbusRegister(int adrReg)
int getTUSmallModbusBit(int x)
{
  //�������� ���������� bit
  UNUSED(x);
  return MARKER_OUTPERIMETR;

}//getTUSmallModbusBit(int adrBit)
int setTUSmallModbusRegister(int adrReg, int dataReg)
{
  if(privateTUSmallGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(tusmallcomponent->isActiveActualData) setTUSmallCountObject(); //�������� �-�� �������
  tusmallcomponent->isActiveActualData = 0;
  if(privateTUSmallGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

//  UNUSED(x);
  //�������� ���������� ��������
  superSetOperativMarker(tusmallcomponent, adrReg);
  superSetTempWriteArray(dataReg);//�������� � �����

  return 0;
}//getDVModbusRegister(int adrReg)
int setTUSmallModbusBit(int adrBit, int dataBit)
{
  if(privateTUSmallGetBit2(adrBit)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(tusmallcomponent->isActiveActualData) setTUSmallCountObject(); //�������� �-�� �������
  tusmallcomponent->isActiveActualData = 0;
  if(privateTUSmallGetBit1(adrBit)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;
//  UNUSED(x);
  //�������� ���������� bit
  superSetOperativMarker(tusmallcomponent, adrBit);
  superSetTempWriteArray(dataBit);//�������� � �����

  return 0;
}//getDVModbusRegister(int adrReg)

void setTUSmallCountObject(void) {
//�������� �-�� �������
  int cntObj = current_config.n_tu;    //ʳ������ ����� �����������
  if(cntObj<0) return;
  if(cntObj>TOTAL_OBJ) return;
  tusmallcomponent->countObject = cntObj;
}//
void preTUSmallReadAction(void) {
//action �� ������
  tusmallcomponent->operativMarker[0] = -1;
  tusmallcomponent->operativMarker[1] = -1;//����������� ������
  tusmallcomponent->isActiveActualData = 1;
}//
void postTUSmallReadAction(void) {
//action ����� ������
  if(tusmallcomponent->operativMarker[0]<0) return;//�� ���� ������
}//
void preTUSmallWriteAction(void) {
//action �� ������
  tusmallcomponent->operativMarker[0] = -1;
  tusmallcomponent->operativMarker[1] = -1;//����������� ������
  tusmallcomponent->isActiveActualData = 1;
}//
int postTUSmallWriteAction(void) {
//action ����� ������
 return 0;
}//

int privateTUSmallGetReg1(int adrReg)
{
  //��������� ���������� ��������
  int count_register = tusmallcomponent->countObject/16;
  if(tusmallcomponent->countObject%16) count_register++;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg1(int adrReg)

int privateTUSmallGetReg2(int adrReg)
{
  //��������� ������� ��������
  int count_register = TOTAL_OBJ/16;
  if(TOTAL_OBJ%16) count_register++;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)

int privateTUSmallGetBit1(int adrBit)
{
  //��������� ���������� ��������
  int count_bit = BIT_FOR_OBJ*tusmallcomponent->countObject;
  if(adrBit>=BEGIN_ADR_BIT && adrBit<(BEGIN_ADR_BIT+count_bit)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg1(int adrReg)

int privateTUSmallGetBit2(int adrBit)
{
  //��������� ������� ��������
  int count_bit = BIT_FOR_OBJ*TOTAL_OBJ;
  if(adrBit>=BEGIN_ADR_BIT && adrBit<(BEGIN_ADR_BIT+count_bit)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
