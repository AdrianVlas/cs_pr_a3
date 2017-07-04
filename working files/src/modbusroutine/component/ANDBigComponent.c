#include "header.h"

//��������� ������� � ����� ������
#define BEGIN_ADR_REGISTER 8917
//���� �-�� �������
#define TOTAL_OBJ 128
#define REGISTER_FOR_OBJ 16

int privateANDBigGetReg1(int adrReg);
int privateANDBigGetReg2(int adrReg);

int getANDBigModbusRegister(int);//�������� ���������� ��������
int getANDBigModbusBit(int);//�������� ���������� ����
int setANDBigModbusRegister(int, int);// �������
int setANDBigModbusBit(int, int);// ���

void setANDBigCountObject(void);
void preANDBigReadAction(void);//action �� ������
void postANDBigReadAction(void);//action ����� ������
void preANDBigWriteAction(void);//action �� ������
void postANDBigWriteAction(void);//action ����� ������
void loadANDBigActualData(void);

COMPONENT_OBJ *andbigcomponent;

/**************************************/
//���������� ���������� AND
/**************************************/
void constructorANDBigComponent(COMPONENT_OBJ *andbigcomp)
{
  andbigcomponent = andbigcomp;

  andbigcomponent->countObject = 0;//�-�� �������

  andbigcomponent->getModbusRegister = getANDBigModbusRegister;//�������� ���������� ��������
  andbigcomponent->getModbusBit      = getANDBigModbusBit;//�������� ���������� ����
  andbigcomponent->setModbusRegister = setANDBigModbusRegister;//�������� �������
  andbigcomponent->setModbusBit      = setANDBigModbusBit;//�������� ���

  andbigcomponent->preReadAction   = preANDBigReadAction;//action �� ������
  andbigcomponent->postReadAction  = postANDBigReadAction;//action ����� ������
  andbigcomponent->preWriteAction  = preANDBigWriteAction;//action �� ������
  andbigcomponent->postWriteAction = postANDBigWriteAction;//action ����� ������

  andbigcomponent->isActiveActualData = 0;
}//prepareDVinConfig

void loadANDBigActualData(void) {
 setANDBigCountObject(); //�������� �-�� �������

  //ActualData
   __LN_AND *arr = (__LN_AND*)(spca_of_p_prt[ID_FB_AND - _ID_FB_FIRST_VAR]);
   for(int item=0; item<andbigcomponent->countObject; item++) {
     
     for (int i = 0; i < AND_SIGNALS_IN; i ++)
     {
        int value = arr[item].settings.param[i] & 0xffff;//
        tempReadArray[item*REGISTER_FOR_OBJ+2*i+0] = value;
        value = (arr[item].settings.param[i] >> 16) & 0x7fff;//
        tempReadArray[item*REGISTER_FOR_OBJ+2*i+1] = value;
     }
  }//for
  /*
  ��� ��� ���������, �� � �� ���� ���������� ���� � ������� (��. ����� � ������ ����) ���� ������ ����� ����������� ��� 0-� ���� �����, � �����(id;n; out) ����� � ������� ���������
  */
}//loadActualData() 

int getANDBigModbusRegister(int adrReg)
{
  //�������� ���������� ��������
  if(privateANDBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(andbigcomponent->isActiveActualData) loadANDBigActualData(); //ActualData
  andbigcomponent->isActiveActualData = 0;
  if(privateANDBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  superSetOperativMarker(andbigcomponent, adrReg);

  return tempReadArray[adrReg-BEGIN_ADR_REGISTER];
}//getDOUTBigModbusRegister(int adrReg)
int getANDBigModbusBit(int adrBit)
{
  //�������� ���������� ����
  superSetOperativMarker(andbigcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setANDBigModbusRegister(int adrReg, int dataReg)
{
  //�������� ���������� ��������
  if(privateANDBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(andbigcomponent->isActiveActualData) setANDBigCountObject(); //�-�� �������
  andbigcomponent->isActiveActualData = 0;
  if(privateANDBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  superSetOperativMarker(andbigcomponent, adrReg);
  superSetTempWriteArray(dataReg);//�������� � �����

  switch((adrReg-BEGIN_ADR_REGISTER)%REGISTER_FOR_OBJ) {
   case 0:
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
   break; 
   case 1:
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
   case 6:
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
   break; 
   case 7:
   break; 
   case 8:
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
   break; 
   case 9:
   break; 
   case 10:
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
   break; 
   case 11:
   break; 
   case 12:
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
   break; 
   case 13:
   break; 
   case 14:
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
   break; 
   case 15:
   break; 
   default: return MARKER_OUTPERIMETR;
  }//switch
  return 0;
}//setDOUTBigModbusRegister(int adrReg)
int setANDBigModbusBit(int adrBit, int x)
{
  UNUSED(x);
  //�������� ���������� ����
  superSetOperativMarker(andbigcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//setDOUTBigModbusRegister(int adrReg)

void setANDBigCountObject(void) {
//�������� �-�� �������
  int cntObj = current_config.n_and;                       //ʳ������ �������� "�"
  if(cntObj<0) return;
  if(cntObj>TOTAL_OBJ) return;
  andbigcomponent->countObject = cntObj;
}//

void preANDBigReadAction(void) {
//action �� ������
  andbigcomponent->operativMarker[0] = -1;
  andbigcomponent->operativMarker[1] = -1;//����������� ������
  andbigcomponent->isActiveActualData = 1;
}//preANDBigReadAction() 

void postANDBigReadAction(void) {
//action ����� ������
  if(andbigcomponent->operativMarker[0]<0) return;//�� ���� ������
}//postANDBigReadAction() 

void preANDBigWriteAction(void) {
//action �� ������
  andbigcomponent->operativMarker[0] = -1;
  andbigcomponent->operativMarker[1] = -1;//����������� ������
  andbigcomponent->isActiveActualData = 1;
}//preANDBigWriteAction() 

void postANDBigWriteAction(void) {
//action ����� ������
  if(andbigcomponent->operativMarker[0]<0) return;//�� ���� ������
  int offsetTempWriteArray = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//����� �������� TempWriteArray
  int countRegister = andbigcomponent->operativMarker[1]-andbigcomponent->operativMarker[0]+1;
  if(andbigcomponent->operativMarker[1]<0) countRegister = 1;

   __settings_for_AND *arr = (__settings_for_AND*)(sca_of_p[ID_FB_AND - _ID_FB_FIRST_VAR]);
   __settings_for_AND *arr1 = (__settings_for_AND*)(sca_of_p_edit[ID_FB_AND - _ID_FB_FIRST_VAR]);
  for(int i=0; i<countRegister; i++) {
  int offset = i+andbigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//������ ����������
  int idx_SIGNALS_IN = (offset%REGISTER_FOR_OBJ)/2;//������ ����� ����������

  switch(offset%2) {//������ �������� �����
  case 0:
        arr[idxSubObj].param[idx_SIGNALS_IN] |= arr1[idxSubObj].param[idx_SIGNALS_IN] |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
  break;
  case 1:
        arr[idxSubObj].param[idx_SIGNALS_IN] |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
  break;
 }//switch
  }//for
}//postANDBigWriteAction() 

int privateANDBigGetReg1(int adrReg)
{
  //��������� ���������� ��������
  int count_register = andbigcomponent->countObject*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg1(int adrReg)
int privateANDBigGetReg2(int adrReg)
{
  //��������� ������� ��������
  int count_register = TOTAL_OBJ*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
