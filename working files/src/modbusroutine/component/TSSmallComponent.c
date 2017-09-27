#include "header.h"

//��������� ������� � ����� ������
#define BEGIN_ADR_REGISTER 200
//��������� bit � ����� ������
#define BEGIN_ADR_BIT 18000
#define BIT_FOR_OBJ 1
//���� �-�� �������
#define TOTAL_OBJ 128
int privateTSSmallGetReg1(int adrReg);
int privateTSSmallGetReg2(int adrReg);
int privateTSSmallGetBit1(int adrBit);
int privateTSSmallGetBit2(int adrBit);

int getTSSmallModbusRegister(int);//�������� ���������� ��������
int getTSSmallModbusBit(int);//�������� ���������� ����
int setTSSmallModbusRegister(int, int);//�������� ���������� ��������
int setTSSmallModbusBit(int, int);//�������� ���������� ����

void setTSSmallCountObject(void);//�������� �-�� �������
void preTSSmallReadAction(void);//action �� ������
void postTSSmallReadAction(void);//action ����� ������
void preTSSmallWriteAction(void);//action �� ������
int postTSSmallWriteAction(void);//action ����� ������
void loadTSSmallActualData(int beginOffset, int endOffset);
int getTSmallModbusBeginAdrRegister(void);
void config_and_settingsTSSmall(void);//action ���������

COMPONENT_OBJ *tssmallcomponent;

int getTSmallModbusBeginAdrRegister(void)
{
  //�������� ����� ��� ��������
 return BEGIN_ADR_REGISTER;
}//getTSmallModbusBeginAdrRegister(void)

/**************************************/
//���������� ���������� ����������������
/**************************************/
void constructorTSSmallComponent(COMPONENT_OBJ *tssmallcomp)
{
  tssmallcomponent = tssmallcomp;

  tssmallcomponent->countObject = 0;//�-�� �������

  tssmallcomponent->getModbusRegister = getTSSmallModbusRegister;//�������� ���������� ��������
  tssmallcomponent->getModbusBit      = getTSSmallModbusBit;//�������� ���������� ����
  tssmallcomponent->setModbusRegister = setTSSmallModbusRegister;//�������� ���������� ��������
  tssmallcomponent->setModbusBit      = setTSSmallModbusBit;//�������� ���������� ����

  tssmallcomponent->preReadAction   = preTSSmallReadAction;//action �� ������
  tssmallcomponent->postReadAction  = postTSSmallReadAction;//action ����� ������
  tssmallcomponent->preWriteAction  = preTSSmallWriteAction;//action �� ������
  tssmallcomponent->postWriteAction = postTSSmallWriteAction;//action ����� ������
  tssmallcomponent->config_and_settings = config_and_settingsTSSmall;//action ���������

  tssmallcomponent->isActiveActualData = 0;
}//prepareDVinConfig

void loadTSSmallActualData(int beginOffset, int endOffset) {
  //ActualData
//  setTSSmallCountObject(); //�������� �-�� �������

  int cnt_treg = tssmallcomponent->countObject/16;
  if(tssmallcomponent->countObject%16) cnt_treg++;
  for(int ii=0; ii<cnt_treg; ii++) tempReadArray[ii] = 0;
   __LN_TS *arr = (__LN_TS*)(spca_of_p_prt[ID_FB_TS - _ID_FB_FIRST_VAR]);
  for(int item=0; item<tssmallcomponent->countObject; item++) {
   int ireg = item/16;

   int value =0;
   if(item>=beginOffset && item<endOffset) {
   //������������ MUTEX (1)
   arr[item].internal_input[TS_INT_MUTEX >> 3] |= (1 << (TS_INT_MUTEX & ((1 << 3) - 1)));
   
   //�������� �����
   value = arr[item].active_state[TS_OUT  >> 3] & (1 << (TS_OUT  & ((1 << 3) - 1)));

   //������������ ��� �� �� ������� �������� (2)
   arr[item].internal_input[TS_INT_READING >> 3] |= (1 << (TS_INT_READING & ((1 << 3) - 1)));


   //������� MUTEX (3)
   arr[item].internal_input[TS_INT_MUTEX >> 3] &= (uint8_t)(~(1 << (TS_INT_MUTEX & ((1 << 3) - 1))));
   }//if
   
   int tsdata = 0;
   if(value) tsdata=1;
   tempReadArray[ireg] |= (tsdata&0x1)<<(item%16);
  }//for
}//loadActualData() 

int getTSSmallModbusRegister(int adrReg)
{
  //�������� ���������� ��������
//extern int cntBit;//�-�� ��� ��� ������
extern int globalcntReg;//�-�� ��������� ��� ������
extern int globalbeginAdrReg;
  if(privateTSSmallGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(tssmallcomponent->isActiveActualData) {
    setTSSmallCountObject(); //�������� �-�� �������
    int begin = globalbeginAdrReg-BEGIN_ADR_REGISTER;
    if(begin<0) globalcntReg += begin;
    if(privateTSSmallGetReg1(adrReg+globalcntReg-1)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;
    int beginOffset = (adrReg-BEGIN_ADR_REGISTER)*16;
    int endOffset   = (adrReg-BEGIN_ADR_REGISTER +globalcntReg)*16;
    loadTSSmallActualData(beginOffset, endOffset);  //ActualData
  }//if
  tssmallcomponent->isActiveActualData = 0;

  return tempReadArray[adrReg-BEGIN_ADR_REGISTER];
}//getDVModbusRegister(int adrReg)
int getTSSmallModbusBit(int adrBit)
{
  //�������� ���������� bit
extern int globalcntBit;//�-�� ��� ��� ������
extern int globalbeginAdrBit;
  if(privateTSSmallGetBit2(adrBit)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(tssmallcomponent->isActiveActualData) {
    setTSSmallCountObject(); //�������� �-�� �������
    int begin = globalbeginAdrBit-BEGIN_ADR_BIT;
    if(begin<0) globalcntBit += begin;
    if(privateTSSmallGetBit1(adrBit +globalcntBit-1)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;
    int beginOffset = adrBit-BEGIN_ADR_BIT;
    int endOffset   = adrBit-BEGIN_ADR_BIT +globalcntBit;
    loadTSSmallActualData(beginOffset, endOffset);  //ActualData
  }//if
  tssmallcomponent->isActiveActualData = 0;

  superSetOperativMarker(tssmallcomponent, adrBit);

  short tmp   = tempReadArray[(adrBit-BEGIN_ADR_BIT)/16];
  short maska = 1<<((adrBit-BEGIN_ADR_BIT)%16);
  if(tmp&maska) return 1;
  return 0;
}//getDVModbusRegister(int adrReg)
int setTSSmallModbusRegister(int x, int y)
{
  UNUSED(x);
  UNUSED(y);
  //�������� ���������� ��������
  return MARKER_OUTPERIMETR;
}//getDVModbusRegister(int adrReg)
int setTSSmallModbusBit(int x, int y)
{
  UNUSED(x);
  UNUSED(y);
  //�������� ���������� bit
  return MARKER_OUTPERIMETR;
}//getDVModbusRegister(int adrReg)

void setTSSmallCountObject(void) {
//�������� �-�� �������
  int cntObj = current_config.n_ts;    //ʳ������ ����� �����������
  if(cntObj<0) return;
  if(cntObj>TOTAL_OBJ) return;
  tssmallcomponent->countObject = cntObj;
}//
void preTSSmallReadAction(void) {
//action �� ������
  tssmallcomponent->operativMarker[0] = -1;
  tssmallcomponent->operativMarker[1] = -1;//����������� ������
  tssmallcomponent->isActiveActualData = 1;
}//
void postTSSmallReadAction(void) {
//action ����� ������
  if(tssmallcomponent->operativMarker[0]<0) return;//�� ���� ������
}//
void preTSSmallWriteAction(void) {
//action �� ������
  tssmallcomponent->operativMarker[0] = -1;
  tssmallcomponent->operativMarker[1] = -1;//����������� ������
  tssmallcomponent->isActiveActualData = 1;
}//
int postTSSmallWriteAction(void) {
//action ����� ������
  return 0;
}//

int privateTSSmallGetReg1(int adrReg)
{
  //��������� ���������� ��������
  int count_register = tssmallcomponent->countObject/16;
  if(tssmallcomponent->countObject%16) count_register++;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg1(int adrReg)

int privateTSSmallGetReg2(int adrReg)
{
  //��������� ������� ��������
  int count_register = TOTAL_OBJ/16;
  if(TOTAL_OBJ%16) count_register++;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)

int privateTSSmallGetBit1(int adrBit)
{
  //��������� ���������� ��������
  int count_bit = BIT_FOR_OBJ*tssmallcomponent->countObject;
  if(adrBit>=BEGIN_ADR_BIT && adrBit<(BEGIN_ADR_BIT+count_bit)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg1(int adrReg)

int privateTSSmallGetBit2(int adrBit)
{
  //��������� ������� ��������
  int count_bit = BIT_FOR_OBJ*TOTAL_OBJ;
  if(adrBit>=BEGIN_ADR_BIT && adrBit<(BEGIN_ADR_BIT+count_bit)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)

void config_and_settingsTSSmall(void)
{
//action ���������
}

