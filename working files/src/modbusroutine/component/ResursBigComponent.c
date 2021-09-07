#include "header.h"

//��������� ������� � ����� ������
#define BEGIN_ADR_REGISTER 63002
//���� �-�� �������
#define REGISTER_FOR_OBJ 7

int privateResursBigGetReg2(int adrReg);

int getResursBigModbusRegister(int);//�������� ���������� ��������
int getResursBigModbusBit(int);//�������� ���������� ����
int setResursBigModbusRegister(int, int);//�������� ���������� ��������
int setResursBigModbusBit(int, int);//�������� ���������� ����

void preResursBigReadAction(void);//action �� ������
void postResursBigReadAction(void);//action ����� ������
void preResursBigWriteAction(void);//action �� ������
int postResursBigWriteAction(void);//action ����� ������
void loadResursBigActualData(void);
void config_and_settingsResursBig(void);//action ���������

COMPONENT_OBJ *resursbigcomponent;

/**************************************/
//���������� ���������� ���������
/**************************************/
void constructorResursBigComponent(COMPONENT_OBJ *resursbigcomp)
{
  resursbigcomponent = resursbigcomp;

  resursbigcomponent->countObject = 1;//�-�� �������

  resursbigcomponent->getModbusRegister = getResursBigModbusRegister;//�������� ���������� ��������
  resursbigcomponent->getModbusBit      = getResursBigModbusBit;//�������� ���������� ����
  resursbigcomponent->setModbusRegister = setResursBigModbusRegister;//�������� ���������� ��������
  resursbigcomponent->setModbusBit      = setResursBigModbusBit;//�������� ���������� ����

  resursbigcomponent->preReadAction   = preResursBigReadAction;//action �� ������
  resursbigcomponent->postReadAction  = postResursBigReadAction;//action ����� ������
  resursbigcomponent->preWriteAction  = preResursBigWriteAction;//action �� ������
  resursbigcomponent->postWriteAction = postResursBigWriteAction;//action ����� ������
  resursbigcomponent->config_and_settings = config_and_settingsResursBig;//action ���������

  resursbigcomponent->isActiveActualData = 0;
}//prepareDVinConfig

void loadResursBigActualData(void) {
  //ActualData
  tempReadArray[0] = restart_resurs_count&0xffff;
  tempReadArray[1] = resurs_global&0xffff;
  tempReadArray[2] = (resurs_global>>16)&0xffff;
  tempReadArray[3] = resurs_global_min&0xffff;
  tempReadArray[4] = (resurs_global_min>>16)&0xffff;
  tempReadArray[5] = resurs_global_max&0xffff;
  tempReadArray[6] = (resurs_global_max>>16)&0xffff;
}//loadActualData() 

int getResursBigModbusRegister(int adrReg)
{
  //�������� ���������� ��������
  if(privateResursBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  if(resursbigcomponent->isActiveActualData) loadResursBigActualData(); //ActualData
  resursbigcomponent->isActiveActualData = 0;

  superSetOperativMarker(resursbigcomponent, adrReg);

  int offset = adrReg-BEGIN_ADR_REGISTER;
  if(offset==0) return MARKER_ERRORPERIMETR;//reset resurs

  return tempReadArray[offset];
}//getDOUTBigModbusRegister(int adrReg)
int getResursBigModbusBit(int x)
{
  //�������� ���������� ��������
  UNUSED(x);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setResursBigModbusRegister(int adrReg, int dataReg)
{
  //�������� ���������� ��������
  if(privateResursBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  superSetOperativMarker(resursbigcomponent, adrReg);
  superSetTempWriteArray(dataReg);//�������� � �����

  int offset = adrReg-BEGIN_ADR_REGISTER;
  if(offset>0) return MARKER_ERRORDIAPAZON;//������ ������, ����� �������� 0

  return 0;
}//getDOUTBigModbusRegister(int adrReg)
int setResursBigModbusBit(int x, int y)
{
  UNUSED(x);
  UNUSED(y);
  //�������� ���������� bit
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void preResursBigReadAction(void) {
//action �� ������
  resursbigcomponent->operativMarker[0] = -1;
  resursbigcomponent->operativMarker[1] = -1;//����������� ������
  resursbigcomponent->isActiveActualData = 1;
}//
void postResursBigReadAction(void) {
//action ����� ������
  if(resursbigcomponent->operativMarker[0]<0) return;//�� ���� ������
}//
void preResursBigWriteAction(void) {
//action �� ������
  resursbigcomponent->operativMarker[0] = -1;
  resursbigcomponent->operativMarker[1] = -1;//����������� ������
  resursbigcomponent->isActiveActualData = 1;
}//

int postResursBigWriteAction(void) {
  int resetResurs = 0;//reset resurs
//action ����� ������
  if(resursbigcomponent->operativMarker[0]<0) return 0;//�� ���� ������
  int offsetTempWriteArray = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//����� �������� TempWriteArray
  int countRegister = resursbigcomponent->operativMarker[1]-resursbigcomponent->operativMarker[0]+1;

  //int flag = 0;
  for(int i=0; i<countRegister; i++) {
  int offset = i+resursbigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;

  switch(offset%(REGISTER_FOR_OBJ)) {//������ �������� 
  case 0:
      resetResurs = tempWriteArray[offsetTempWriteArray+i];//reset resurs
      if(resetResurs!=0)
      {
        //����� ��������
        resurs_global = 0;    
        resurs_global_min = 4294967295;    
        resurs_global_max = 0;
      }//if
  break;
 }//switch
  }//for

 return 0;
}//

int privateResursBigGetReg2(int adrReg)
{
  //��������� ������� ��������
  int count_register = REGISTER_FOR_OBJ+1;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)

void config_and_settingsResursBig(void)
{
//action ���������
}

