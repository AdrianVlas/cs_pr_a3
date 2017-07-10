#include "header.h"

//��������� ������� � ����� ������
#define BEGIN_ADR_REGISTER 400
//��������� bit � ����� ������
#define BEGIN_ADR_BIT 20000
#define BIT_FOR_OBJ 1
//���� �-�� �������
#define TOTAL_OBJ 128
int privateDVSmallGetReg1(int adrReg);
int privateDVSmallGetReg2(int adrReg);
int privateDVSmallGetBit1(int adrBit);
int privateDVSmallGetBit2(int adrBit);

int getDVSmallModbusRegister(int);//�������� ���������� ��������
int getDVSmallModbusBit(int);//�������� ���������� ����
int setDVSmallModbusRegister(int, int);//�������� ���������� ��������
int setDVSmallModbusBit(int, int);//�������� ���������� ����

void setDVSmallCountObject(void);//�������� �-�� �������
void preDVSmallReadAction(void);//action �� ������
void postDVSmallReadAction(void);//action ����� ������
void preDVSmallWriteAction(void);//action �� ������
int postDVSmallWriteAction(void);//action ����� ������
void loadDVSmallActualData(void);

COMPONENT_OBJ *dvsmallcomponent;

/**************************************/
//���������� ���������� ��
/**************************************/
void constructorDVSmallComponent(COMPONENT_OBJ *dvsmallcomp)
{
  dvsmallcomponent = dvsmallcomp;

  dvsmallcomponent->countObject = 0;//�-�� �������

  dvsmallcomponent->getModbusRegister = getDVSmallModbusRegister;//�������� ���������� ��������
  dvsmallcomponent->getModbusBit      = getDVSmallModbusBit;//�������� ���������� ����
  dvsmallcomponent->setModbusRegister = setDVSmallModbusRegister;//�������� ���������� ��������
  dvsmallcomponent->setModbusBit      = setDVSmallModbusBit;//�������� ���������� ����

  dvsmallcomponent->preReadAction   = preDVSmallReadAction;//action �� ������
  dvsmallcomponent->postReadAction  = postDVSmallReadAction;//action ����� ������
  dvsmallcomponent->preWriteAction  = preDVSmallWriteAction;//action �� ������
  dvsmallcomponent->postWriteAction = postDVSmallWriteAction;//action ����� ������

  dvsmallcomponent->isActiveActualData = 0;
}//prepareDVinConfig

void loadDVSmallActualData(void) {
  //ActualData
   setDVSmallCountObject(); //�������� �-�� �������

   int cnt_treg = dvsmallcomponent->countObject/16;
   if(dvsmallcomponent->countObject%16) cnt_treg++;
   for(int ii=0; ii<cnt_treg; ii++) tempReadArray[ii] = 0;
   __LN_INPUT *arr = (__LN_INPUT*)(spca_of_p_prt[ID_FB_INPUT - _ID_FB_FIRST_VAR]);
   for(int item=0; item<dvsmallcomponent->countObject; item++) {
   int ireg = item/16;
   int value = arr[item].active_state[INPUT_OUT >> 3] & (1 << (INPUT_OUT & ((1 << 3) - 1)));
   int dvdata = 0;
   if(value) dvdata=1;
   tempReadArray[ireg] |= dvdata<<(item%16);
  }//for
}//loadActualData() 

int getDVSmallModbusRegister(int adrReg)
{
  //�������� ���������� ��������
  if(privateDVSmallGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(dvsmallcomponent->isActiveActualData) loadDVSmallActualData(); //ActualData
  dvsmallcomponent->isActiveActualData = 0;
  if(privateDVSmallGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;//MARKER_ERRORPERIMETR;

  superSetOperativMarker(dvsmallcomponent, adrReg);

  return tempReadArray[adrReg-BEGIN_ADR_REGISTER];
}//getDVModbusRegister(int adrReg)
int getDVSmallModbusBit(int adrBit)
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
int setDVSmallModbusRegister(int adrReg, int x)
{
  UNUSED(x);
  //�������� ���������� ��������
  superSetOperativMarker(dvsmallcomponent, adrReg);
  return MARKER_OUTPERIMETR;
}//getDVModbusRegister(int adrReg)
int setDVSmallModbusBit(int adrBit, int x)
{
  UNUSED(x);
  //�������� ���������� ��������
  superSetOperativMarker(dvsmallcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDVModbusRegister(int adrReg)

void setDVSmallCountObject(void) {
//�������� �-�� �������
  int cntObj = current_config.n_input; //ʳ������ ���������� �����
  if(cntObj<0) return;
  if(cntObj>TOTAL_OBJ) return;
  dvsmallcomponent->countObject = cntObj;
}//
void preDVSmallReadAction(void) {
//action �� ������
  dvsmallcomponent->operativMarker[0] = -1;
  dvsmallcomponent->operativMarker[1] = -1;//����������� ������
  dvsmallcomponent->isActiveActualData = 1;
}//
void postDVSmallReadAction(void) {
//action ����� ������
  if(dvsmallcomponent->operativMarker[0]<0) return;//�� ���� ������
}//
void preDVSmallWriteAction(void) {
//action �� ������
  dvsmallcomponent->operativMarker[0] = -1;
  dvsmallcomponent->operativMarker[1] = -1;//����������� ������
  dvsmallcomponent->isActiveActualData = 1;
}//
int postDVSmallWriteAction(void) {
//action ����� ������
 return 0;
}//

int privateDVSmallGetReg1(int adrReg)
{
  //��������� ���������� ��������
  int count_register = dvsmallcomponent->countObject/16;
  if(dvsmallcomponent->countObject%16) count_register++;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg1(int adrReg)

int privateDVSmallGetReg2(int adrReg)
{
  //��������� ������� ��������
  int count_register = TOTAL_OBJ/16;
  if(TOTAL_OBJ%16) count_register++;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)

int privateDVSmallGetBit1(int adrBit)
{
  //��������� ���������� ��������
  int count_bit = BIT_FOR_OBJ*dvsmallcomponent->countObject;
  if(adrBit>=BEGIN_ADR_BIT && adrBit<(BEGIN_ADR_BIT+count_bit)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg1(int adrReg)

int privateDVSmallGetBit2(int adrBit)
{
  //��������� ������� ��������
  int count_bit = BIT_FOR_OBJ*TOTAL_OBJ;
  if(adrBit>=BEGIN_ADR_BIT && adrBit<(BEGIN_ADR_BIT+count_bit)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
