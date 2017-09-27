
#include "header.h"

//��������� ������� � ����� ������
#define BEGIN_ADR_REGISTER 300
//��������� bit � ����� ������
#define BEGIN_ADR_BIT 19000
#define BIT_FOR_OBJ 1
//���� �-�� �������
#define TOTAL_OBJ 128
int privateDOUTSmallGetReg1(int adrReg);
int privateDOUTSmallGetReg2(int adrReg);
int privateDOUTSmallGetBit1(int adrBit);
int privateDOUTSmallGetBit2(int adrBit);

int getDOUTSmallModbusRegister(int);//�������� ���������� ��������
int getDOUTSmallModbusBit(int);//�������� ���������� ����
int setDOUTSmallModbusRegister(int, int);//�������� �������
int setDOUTSmallModbusBit(int, int);//�������� ���

void setDOUTSmallCountObject(void);//�������� �-�� �������
void preDOUTSmallReadAction(void);//action �� ������
void postDOUTSmallReadAction(void);//action ����� ������
void preDOUTSmallWriteAction(void);//action �� ������
int postDOUTSmallWriteAction(void);//action ����� ������
void config_and_settingsDOUTSmall(void);//action ���������
void loadDOUTSmallActualData(void);

COMPONENT_OBJ *doutsmallcomponent;

/**************************************/
//���������� ���������� ��
/**************************************/
void constructorDOUTSmallComponent(COMPONENT_OBJ *doutcomp)
{
  doutsmallcomponent = doutcomp;
  doutsmallcomponent->countObject = 0;//�-�� �������

  doutsmallcomponent->getModbusRegister = getDOUTSmallModbusRegister;//�������� ���������� ��������
  doutsmallcomponent->getModbusBit      = getDOUTSmallModbusBit;//�������� ���������� ����
  doutsmallcomponent->setModbusRegister = setDOUTSmallModbusRegister;// ��������
  doutsmallcomponent->setModbusBit      = setDOUTSmallModbusBit;// ����

  doutsmallcomponent->preReadAction   = preDOUTSmallReadAction;//action �� ������
  doutsmallcomponent->postReadAction  = postDOUTSmallReadAction;//action ����� ������
  doutsmallcomponent->preWriteAction  = preDOUTSmallWriteAction;//action �� ������
  doutsmallcomponent->postWriteAction = postDOUTSmallWriteAction;//action ����� ������
  doutsmallcomponent->config_and_settings = config_and_settingsDOUTSmall;//action ���������
 
  doutsmallcomponent->isActiveActualData = 0;
}//prepareDVinConfig

void loadDOUTSmallActualData(void) {
  //ActualData
   setDOUTSmallCountObject(); //�������� �-�� �������

   int cnt_treg = doutsmallcomponent->countObject/16;
   if(doutsmallcomponent->countObject%16) cnt_treg++;
   for(int ii=0; ii<cnt_treg; ii++) tempReadArray[ii] = 0;
  __LN_OUTPUT_LED *arr = (__LN_OUTPUT_LED*)(spca_of_p_prt[ID_FB_OUTPUT - _ID_FB_FIRST_VAR]);
   for(int item=0; item<doutsmallcomponent->countObject; item++) {
   int ireg = item/16;
   int value = arr[item].active_state[OUTPUT_LED_OUT >> 3] & (1 << (OUTPUT_LED_OUT & ((1 << 3) - 1)));
   int doutdata = 0;
   if(value) doutdata=1;
   tempReadArray[ireg] |= doutdata<<(item%16);
  }//for
}//loadActualData() 

int getDOUTSmallModbusRegister(int adrReg) {
  //�������� ���������� ��������
  if(privateDOUTSmallGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(doutsmallcomponent->isActiveActualData) loadDOUTSmallActualData(); //ActualData
  doutsmallcomponent->isActiveActualData = 0;
  if(privateDOUTSmallGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;//MARKER_ERRORPERIMETR;

  superSetOperativMarker(doutsmallcomponent, adrReg);

  return tempReadArray[adrReg-BEGIN_ADR_REGISTER];
}//getDOUTModbusRegister(int adrReg)
int getDOUTSmallModbusBit(int adrBit) {
  //�������� ���������� bit
  if(privateDOUTSmallGetBit2(adrBit)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(doutsmallcomponent->isActiveActualData) loadDOUTSmallActualData();
  doutsmallcomponent->isActiveActualData = 0;
  if(privateDOUTSmallGetBit1(adrBit)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;//MARKER_ERRORPERIMETR;

  superSetOperativMarker(doutsmallcomponent, adrBit);

  short tmp   = tempReadArray[(adrBit-BEGIN_ADR_BIT)/16];
  short maska = 1<<((adrBit-BEGIN_ADR_BIT)%16);
  if(tmp&maska) return 1;
  return 0;
}//getDOUTModbusBit(int adrReg)
int setDOUTSmallModbusRegister(int x, int y) {
  UNUSED(x);
  UNUSED(y);
  //�������� ���������� ��������
  return MARKER_OUTPERIMETR;
}//getDOUTModbusRegister(int adrReg)
int setDOUTSmallModbusBit(int x, int y) {
  UNUSED(x);
  UNUSED(y);
  //�������� ���������� ��������
  return MARKER_OUTPERIMETR;
}//getDOUTModbusRegister(int adrReg)

void setDOUTSmallCountObject(void) {
//�������� �-�� �������
  int cntObj = current_config.n_output; //ʳ������ ���������� ������
  if(cntObj<0) return;
  if(cntObj>TOTAL_OBJ) return;
  doutsmallcomponent->countObject = cntObj;
}//
void preDOUTSmallReadAction(void) {
//action �� ������
  doutsmallcomponent->operativMarker[0] = -1;
  doutsmallcomponent->operativMarker[1] = -1;//����������� ������
  doutsmallcomponent->isActiveActualData = 1;
}//
void postDOUTSmallReadAction(void) {
//action ����� ������
  if(doutsmallcomponent->operativMarker[0]<0) return;//�� ���� ������
}//
void preDOUTSmallWriteAction(void) {
//action �� ������
  doutsmallcomponent->operativMarker[0] = -1;
  doutsmallcomponent->operativMarker[1] = -1;//����������� ������
  doutsmallcomponent->isActiveActualData = 1;
}//
int postDOUTSmallWriteAction(void) {
//action ����� ������
 return 0;
}//

int privateDOUTSmallGetReg1(int adrReg)
{
  //��������� ���������� ��������
  int count_register = doutsmallcomponent->countObject/16;
  if(doutsmallcomponent->countObject%16) count_register++;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateDOUTSmallGetReg2(int adrReg)

int privateDOUTSmallGetReg2(int adrReg)
{
  //��������� ������� ��������
  int count_register = TOTAL_OBJ/16;
  if(TOTAL_OBJ%16) count_register++;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)

int privateDOUTSmallGetBit1(int adrBit)
{
  //��������� ���������� ��������
  int count_bit = BIT_FOR_OBJ*doutsmallcomponent->countObject;
  if(adrBit>=BEGIN_ADR_BIT && adrBit<(BEGIN_ADR_BIT+count_bit)) return 0;
  return MARKER_OUTPERIMETR;
}//privateDOUTSmallGetBit2(int adrBit)

int privateDOUTSmallGetBit2(int adrBit)
{
  //��������� ������� ��������
  int count_bit = BIT_FOR_OBJ*TOTAL_OBJ;
  if(adrBit>=BEGIN_ADR_BIT && adrBit<(BEGIN_ADR_BIT+count_bit)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)

void config_and_settingsDOUTSmall(void)
{
//action ���������
}

