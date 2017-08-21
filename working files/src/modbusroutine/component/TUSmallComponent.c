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
int getTUSmallModbusBeginAdrRegister(void);
void setTUSmallActualData(int beginOffset, int endOffset, int *localArr);
void postTUSmallWriteRegister(void);
void postTUSmallWriteBit(void);

COMPONENT_OBJ *tusmallcomponent;

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

int getTUSmallModbusBeginAdrRegister(void)
{
  //�������� ����� ��� ��������
 return BEGIN_ADR_REGISTER;
}//getTSmallModbusBeginAdrRegister(void)

void setTUSmallActualData(int beginOffset, int endOffset, int *localArr) {
int i=0;
__LN_TU *arr = (__LN_TU*)(spca_of_p_prt[ID_FB_TU - _ID_FB_FIRST_VAR]);
  for(int item=beginOffset; item<endOffset; item++) {

   if(item<tusmallcomponent->countObject) {
     if(localArr[i]) {
//        qDebug()<<"itemLocalArr= "<<item;
//
//������������ MUTEX (1)
arr[item].internal_input[TU_INT_MUTEX >> 3] |= (1 << (TU_INT_MUTEX & ((1 << 3) - 1)));

//������������ ��� �� �� ����� ���������� ���� �� (2)
arr[item].internal_input[TU_INT_ACTIVATION >> 3] |= (1 << (TU_INT_ACTIVATION & ((1 << 3) - 1)));


//������� MUTEX (3)
arr[item].internal_input[TU_INT_MUTEX >> 3] &= (uint8_t)(~(1 << (TU_INT_MUTEX & ((1 << 3) - 1))));
     }//if
   }//if
   i++;
  }//for
}//setTUSmallActualData(int beginOffset, int endOffset, int *localArr)

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
  extern  int upravlFlag;//���� ������� ���������� 1-���� ����������
  if(privateTUSmallGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(tusmallcomponent->isActiveActualData)  setTUSmallCountObject(); //�������� �-�� �������
  tusmallcomponent->isActiveActualData = 0;
  if(privateTUSmallGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;
  
  superSetOperativMarker(tusmallcomponent, adrReg);
  superSetTempWriteArray(dataReg);//�������� � �����
  upravlFlag=1;//���� ������� ���������� 1-���� ����������

  return 0;
}//getDVModbusRegister(int adrReg)
int setTUSmallModbusBit(int adrBit, int dataBit)
{
  extern int upravlFlag;//���� ������� ���������� 1-���� ����������
  if(privateTUSmallGetBit2(adrBit)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(tusmallcomponent->isActiveActualData)  setTUSmallCountObject(); //�������� �-�� �������
  tusmallcomponent->isActiveActualData = 0;
  if(privateTUSmallGetBit1(adrBit)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;
  
  superSetOperativMarker(tusmallcomponent, adrBit);
  superSetTempWriteArray(dataBit);//�������� � �����
  upravlFlag=1;//���� ������� ���������� 1-���� ����������

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
//action ����� ������
  if(tusmallcomponent->operativMarker[0]<0) return 0;//�� ���� ������

  if(tusmallcomponent->operativMarker[0]<BEGIN_ADR_BIT)  postTUSmallWriteRegister();
  else postTUSmallWriteBit();
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

void postTUSmallWriteBit(void) 
{
  int offsetTempWriteArray = superFindTempWriteArrayOffset(BEGIN_ADR_BIT);//����� �������� TempWriteArray
  int countBit = tusmallcomponent->operativMarker[1]-tusmallcomponent->operativMarker[0]+1;
  if(tusmallcomponent->operativMarker[1]<0) countBit = 1;

 int localArr[150];
 for(int i=0; i<150; i++) localArr[i] = 0;

 for(int i=0; i<countBit; i++) localArr[i]=tempWriteArray[offsetTempWriteArray+i];
 int offsetLocA = tusmallcomponent->operativMarker[0]-BEGIN_ADR_BIT;

 int beginOffset = offsetLocA;
 int endOffset   = (offsetLocA +countBit);
 setTUSmallActualData(beginOffset, endOffset, localArr);
}//postTUSmallWriteBit

void postTUSmallWriteRegister(void) 
{
  int offsetTempWriteArray = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//����� �������� TempWriteArray
  int countRegister = tusmallcomponent->operativMarker[1]-tusmallcomponent->operativMarker[0]+1;
  if(tusmallcomponent->operativMarker[1]<0) countRegister = 1;


  int offsetLocA = tusmallcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;

    int beginOffset = offsetLocA*16;
    int endOffset   = (offsetLocA +countRegister)*16;

 int localArr[150];
 for(int i=0; i<150; i++) localArr[i] = 0;
//���������� �� ���������
    int cntB=0;//������� ���
    for (int i=0; i<countRegister; i++) {//������� ���������

      if (tempWriteArray[offsetTempWriteArray+i]==0) {
        cntB+=16;
        continue;
      }//if
      else {
        for (int b=0; b<16; b++) {
          localArr[cntB] = 0;
          if ((tempWriteArray[offsetTempWriteArray+i]&(1<<b))!=0) {
            localArr[cntB] = 1;
          }//if
          cntB++;
        }//for
      }
    }//for

 setTUSmallActualData(beginOffset, endOffset, localArr);
}//postTUSmallWriteRegister() 
