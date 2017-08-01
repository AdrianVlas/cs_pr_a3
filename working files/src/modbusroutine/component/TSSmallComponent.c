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
void loadTSSmallActualData(void);
int getTSmallModbusBeginAdrRegister(void);

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

  tssmallcomponent->isActiveActualData = 0;
}//prepareDVinConfig

void loadTSSmallActualData(void) {
  //ActualData
  setTSSmallCountObject(); //�������� �-�� �������

  int cnt_treg = tssmallcomponent->countObject/16;
  if(tssmallcomponent->countObject%16) cnt_treg++;
  for(int ii=0; ii<cnt_treg; ii++) tempReadArray[ii] = 0;
   __LN_TS *arr = (__LN_TS*)(spca_of_p_prt[ID_FB_TS - _ID_FB_FIRST_VAR]);
  for(int item=0; item<tssmallcomponent->countObject; item++) {
   int ireg = item/16;

   int value = arr[item].active_state[TU_OUT  >> 3] & (1 << (TU_OUT  & ((1 << 3) - 1)));
   
   int tsdata = 0;
   if(value) tsdata=1;
   tempReadArray[ireg] |= (tsdata&0x1)<<(item%16);
  }//for

  /*
  �������� ������� ������ ����� ����� � ������������ current_config_prt ���� __CONFIG (��� ������� ��������� �����) �/��� current_config/current_config_edit (��� �����������)
  
  1) spca_of_p_prt (����� ��������� �� �������� ���'���, �� ����������� �������� ��� - ��� ������� �����)
  2) ������ �����.����� �������� � enum _id_fb (const_settings.h) - _ID_FB_FIRST_VAR. ���������, ��� �� spca_of_p_prt[ID_FB_TS - _ID_FB_FIRST_VAR]
   - �� �������� �� ����� ������ ��� ��-��
  3) � ��� ���'�� ����������� ����� ���� __LN_XXX (��������� ��� �� __LN_TS)
  4) ������� ����� ���������� �� �������� �������. ���������: (((__LN_TS*)spca_of_p_prt[ID_FB_TS - _ID_FB_FIRST_VAR]) + item), �� item  - �� ����� ��-�, ���� ��� ��������
    �� ���� ������ � ���� type_definition.h.
  __settings_for_XXX - �� ��������� ��������� ����� ����������� (������ � ������� ��������� sca_of_p � sca_of_p_edit)
  __LN_XXX - �� hjpibhtyf ��������� �����������, ����� � �������� ���������� (������ ����� � ������� spca_of_p_prt)
  5) ���� ���������� � ���� active_state �������� ��������
  6) ������ ��� ��������� enum _XXX_output_signals (��� �� - �� enum _TS_output_signals const_settings.h).
  
  ��������� ��������� ����� ������ ����������� ����� �� ������� _n
  __LN_INPUT *arr = (__LN_INPUT*)(spca_of_p_prt[ID_FB_INPUT - _ID_FB_FIRST_VAR]);
  value = arr[_n].active_state[INPUT_OUT >> 3] & (1 << (INPUT_OUT & ((1 << 3) - 1)));
  */
}//loadActualData() 

int getTSSmallModbusRegister(int adrReg)
{
  //�������� ���������� ��������
  if(privateTSSmallGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(tssmallcomponent->isActiveActualData) loadTSSmallActualData(); //ActualData
  tssmallcomponent->isActiveActualData = 0;
  if(privateTSSmallGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  superSetOperativMarker(tssmallcomponent, adrReg);

  return tempReadArray[adrReg-BEGIN_ADR_REGISTER];
}//getDVModbusRegister(int adrReg)
int getTSSmallModbusBit(int adrBit)
{
  //�������� ���������� bit
  if(privateTSSmallGetBit2(adrBit)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(tssmallcomponent->isActiveActualData) loadTSSmallActualData();
  tssmallcomponent->isActiveActualData = 0;
  if(privateTSSmallGetBit1(adrBit)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  superSetOperativMarker(tssmallcomponent, adrBit);

  short tmp   = tempReadArray[(adrBit-BEGIN_ADR_BIT)/16];
  short maska = 1<<((adrBit-BEGIN_ADR_BIT)%16);
  if(tmp&maska) return 1;
  return 0;
}//getDVModbusRegister(int adrReg)
int setTSSmallModbusRegister(int adrReg, int x)
{
  UNUSED(x);
  //�������� ���������� ��������
  superSetOperativMarker(tssmallcomponent, adrReg);
  return MARKER_OUTPERIMETR;
}//getDVModbusRegister(int adrReg)
int setTSSmallModbusBit(int adrBit, int x)
{
  UNUSED(x);
  //�������� ���������� bit
  superSetOperativMarker(tssmallcomponent, adrBit);
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
