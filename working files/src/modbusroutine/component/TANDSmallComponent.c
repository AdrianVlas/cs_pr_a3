#include "header.h"

//��������� ������� � ����� ������
#define BEGIN_ADR_REGISTER 2275
//��������� bit � ����� ������
#define BEGIN_ADR_BIT 50000
#define BIT_FOR_OBJ 1
//���� �-�� �������
//#define TOTAL_OBJ 128
//int privateTANDSmallGetReg1(int adrReg);
int privateTANDSmallGetReg2(int adrReg);
//int privateTANDSmallGetBit1(int adrBit);
int privateTANDSmallGetBit2(int adrBit);

int getTANDSmallModbusRegister(int);//�������� ���������� ��������
int getTANDSmallModbusBit(int);//�������� ���������� ����
int setTANDSmallModbusRegister(int, int);//�������� ���������� ��������
int setTANDSmallModbusBit(int, int);//�������� ���������� ����

void setTANDSmallCountObject(void);//�������� �-�� �������
void preTANDSmallReadAction(void);//action �� ������
void postTANDSmallReadAction(void);//action ����� ������
void preTANDSmallWriteAction(void);//action �� ������
int postTANDSmallWriteAction(void);//action ����� ������
//void loadDVSmallActualData(void);

COMPONENT_OBJ *tandsmallcomponent;

/**************************************/
//���������� ���������� ��������������� AND
/**************************************/
void constructorTANDSmallComponent(COMPONENT_OBJ *tandsmallcomp)
{
  tandsmallcomponent = dvsmallcomp;

  tandsmallcomponent->countObject = 128;//�-�� �������

  tandsmallcomponent->getModbusRegister = getTANDSmallModbusRegister;//�������� ���������� ��������
  tandsmallcomponent->getModbusBit      = getTANDSmallModbusBit;//�������� ���������� ����
  tandsmallcomponent->setModbusRegister = setTANDSmallModbusRegister;//�������� ���������� ��������
  tandsmallcomponent->setModbusBit      = setTANDSmallModbusBit;//�������� ���������� ����

  tandsmallcomponent->preReadAction   = preTANDSmallReadAction;//action �� ������
  tandsmallcomponent->postReadAction  = postTANDSmallReadAction;//action ����� ������
  tandsmallcomponent->preWriteAction  = preTANDSmallWriteAction;//action �� ������
  tandsmallcomponent->postWriteAction = postTANDSmallWriteAction;//action ����� ������

  tandsmallcomponent->isActiveActualData = 0;
}//prepareDVinConfig

void loadTANDSmallActualData(void) {
  //ActualData
   int cnt_treg = tandsmallcomponent->countObject/16;
   if(tandsmallcomponent->countObject%16) cnt_treg++;
   for(int ii=0; ii<cnt_treg; ii++) tempReadArray[ii] = 0;
/*
   __LN_INPUT *arr = (__LN_INPUT*)(spca_of_p_prt[ID_FB_INPUT - _ID_FB_FIRST_VAR]);
   for(int item=0; item<tandsmallcomponent->countObject; item++) {
   int ireg = item/16;
   int value = arr[item].active_state[INPUT_OUT >> 3] & (1 << (INPUT_OUT & ((1 << 3) - 1)));
   int dvdata = 0;
   if(value) dvdata=1;
   tempReadArray[ireg] |= dvdata<<(item%16);
  }//for
*/
}//loadActualData() 

int getTANDSmallModbusRegister(int adrReg)
{
  //�������� ���������� ��������
  if(privateDVSmallGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(dvsmallcomponent->isActiveActualData) loadDVSmallActualData(); //ActualData
  dvsmallcomponent->isActiveActualData = 0;
  if(privateDVSmallGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;//MARKER_ERRORPERIMETR;

  superSetOperativMarker(dvsmallcomponent, adrReg);

  return tempReadArray[adrReg-BEGIN_ADR_REGISTER];
}//getDVModbusRegister(int adrReg)
int getTANDSmallModbusBit(int adrBit)
{
  //�������� ���������� bit
  if(privateDVSmallGetBit2(adrBit)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(dvsmallcomponent->isActiveActualData) loadDVSmallActualData();
  dvsmallcomponent->isActiveActualData = 0;
  if(privateDVSmallGetBit1(adrBit)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;//MARKER_ERRORPERIMETR;

  superSetOperativMarker(dvsmallcomponent, adrBit);

  short tmp   = tempReadArray[(adrBit-BEGIN_ADR_BIT)/16];
  short maska = 1<<((adrBit-BEGIN_ADR_BIT)%16);
  if(tmp&maska) return 1;
  return 0;
}//getDVModbusBit(int adrReg)
int setTANDSmallModbusRegister(int x, int y)
{
  UNUSED(x);
  UNUSED(y);
  //�������� ���������� ��������
  return MARKER_OUTPERIMETR;
}//getDVModbusRegister(int adrReg)
int setTANDSmallModbusBit(int x, int y)
{
  UNUSED(x);
  UNUSED(y);
  //�������� ���������� ��������
  return MARKER_OUTPERIMETR;
}//getDVModbusRegister(int adrReg)

void setTANDSmallCountObject(void) {
//�������� �-�� �������
  int cntObj = current_config.n_input; //ʳ������ ���������� �����
  if(cntObj<0) return;
  if(cntObj>TOTAL_OBJ) return;
  dvsmallcomponent->countObject = cntObj;
}//
void preTANDSmallReadAction(void) {
//action �� ������
  dvsmallcomponent->operativMarker[0] = -1;
  dvsmallcomponent->operativMarker[1] = -1;//����������� ������
  dvsmallcomponent->isActiveActualData = 1;
}//
void postTANDSmallReadAction(void) {
//action ����� ������
  if(dvsmallcomponent->operativMarker[0]<0) return;//�� ���� ������
}//
void preTANDSmallWriteAction(void) {
//action �� ������
  dvsmallcomponent->operativMarker[0] = -1;
  dvsmallcomponent->operativMarker[1] = -1;//����������� ������
  dvsmallcomponent->isActiveActualData = 1;
}//
int postTANDSmallWriteAction(void) {
//action ����� ������
 return 0;
}//

int privateTANDSmallGetReg2(int adrReg)
{
  //��������� ������� ��������
  int count_register = TOTAL_OBJ/16;
  if(TOTAL_OBJ%16) count_register++;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)

int privateTANDSmallGetBit2(int adrBit)
{
  //��������� ������� ��������
  int count_bit = BIT_FOR_OBJ*TOTAL_OBJ;
  if(adrBit>=BEGIN_ADR_BIT && adrBit<(BEGIN_ADR_BIT+count_bit)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
