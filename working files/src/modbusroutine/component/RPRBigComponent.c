
//#include <QtWidgets>
#include "header.h"

//��������� ������� � ����� ������
#define BEGIN_ADR_REGISTER 14000
//���� �-�� �������
#define REGISTER_FOR_OBJ 1

int privateRPRBigGetReg2(int adrReg);

int getRPRBigModbusRegister(int);//�������� ���������� ��������
int getRPRBigModbusBit(int);//�������� ���������� ����
int setRPRBigModbusRegister(int, int);//�������� ���������� ��������
int setRPRBigModbusBit(int, int);//�������� ���������� ����

void setRPRBigCountObject(void);//�������� �-�� �������
void preRPRBigReadAction(void);//action �� ������
void postRPRBigReadAction(void);//action ����� ������
void preRPRBigWriteAction(void);//action �� ������
int postRPRBigWriteAction(void);//action ����� ������
void loadRPRBigActualData(void);
int getRPRSmallModbusBeginAdrRegister(void);

COMPONENT_OBJ *rprbigcomponent;

/**************************************/
//���������� ���������� ������������ ���������������� ���������
/**************************************/
void constructorRPRBigComponent(COMPONENT_OBJ *rprbigcomp)
{
  rprbigcomponent = rprbigcomp;

  rprbigcomponent->countObject = 125;//�-�� �������

  rprbigcomponent->getModbusRegister = getRPRBigModbusRegister;//�������� ���������� ��������
  rprbigcomponent->getModbusBit      = getRPRBigModbusBit;//�������� ���������� ����
  rprbigcomponent->setModbusRegister = setRPRBigModbusRegister;//�������� ���������� ��������
  rprbigcomponent->setModbusBit      = setRPRBigModbusBit;//�������� ���������� ����

  rprbigcomponent->preReadAction   = preRPRBigReadAction;//action �� ������
  rprbigcomponent->postReadAction  = postRPRBigReadAction;//action ����� ������
  rprbigcomponent->preWriteAction  = preRPRBigWriteAction;//action �� ������
  rprbigcomponent->postWriteAction = postRPRBigWriteAction;//action ����� ������

  rprbigcomponent->isActiveActualData = 0;
}//prepareDVinConfig

//void loadRPRBigActualData(void)
//{
  /*
  �������/����� ��������� � ���� (�������� ����� � ���� type_definition.h ��� ��������� ���� __CONFIG)
  settings_fix_prt/settings_fix/settings_fix_edit->user_register[]
  
  */
  //ActualData
  //for(int i=0; i<100; i++) tempReadArray[i] = i;
  /*
  �������/����� ��������� � 
  settings_fix_prt/settings_fix/settings_fix_edit.user_register[����� �������]
*/
//}//loadActualData()

int getRPRBigModbusRegister(int adrReg)
{
  //�������� ���������� ��������
  if(privateRPRBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

//  if(rprbigcomponent->isActiveActualData) loadRPRBigActualData(); //ActualData
//  rprbigcomponent->isActiveActualData = 0;

  int offset = adrReg-BEGIN_ADR_REGISTER;

  superSetOperativMarker(rprbigcomponent, adrReg);

  return settings_fix.user_register[offset];//tempReadArray[adrReg-BEGIN_ADR_REGISTER];
}//getDOUTBigModbusRegister(int adrReg)
int getRPRBigModbusBit(int x)
{
  //�������� ���������� ��������
  UNUSED(x);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setRPRBigModbusRegister(int adrReg, int dataReg)
{
  //�������� ���������� ��������
  if(privateRPRBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  superSetOperativMarker(rprbigcomponent, adrReg);
  superSetTempWriteArray(dataReg);//�������� � �����
//������ ���������� ������ small ����������
  if(adrReg>=getRPRSmallModbusBeginAdrRegister() &&
      (adrReg<rprbigcomponent->countObject*getRPRSmallModbusBeginAdrRegister())) return MARKER_ERRORDIAPAZON;

  return 0;
}//getDOUTBigModbusRegister(int adrReg)
int setRPRBigModbusBit(int x, int y)
{
  UNUSED(x);
  UNUSED(y);
  //�������� ���������� ��������
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void setRPRBigCountObject(void)
{
//�������� �-�� �������
}//
void preRPRBigReadAction(void)
{
//action �� ������
  rprbigcomponent->operativMarker[0] = -1;
  rprbigcomponent->operativMarker[1] = -1;//����������� ������
  rprbigcomponent->isActiveActualData = 1;
}//
void postRPRBigReadAction(void)
{
//action ����� ������
  if(rprbigcomponent->operativMarker[0]<0) return;//�� ���� ������
}//
void preRPRBigWriteAction(void)
{
//action �� ������
  rprbigcomponent->operativMarker[0] = -1;
  rprbigcomponent->operativMarker[1] = -1;//����������� ������
  rprbigcomponent->isActiveActualData = 1;
}//
int postRPRBigWriteAction(void)
{
//action ����� ������
  if(rprbigcomponent->operativMarker[0]<0) return 0;//�� ���� ������
  int offset = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//����� �������� TempWriteArray
  int countRegister = rprbigcomponent->operativMarker[1]-rprbigcomponent->operativMarker[0]+1;
  if(rprbigcomponent->operativMarker[1]<0) countRegister = 1;

  for(int i=0; i<countRegister; i++)
      settings_fix.user_register[i+rprbigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER] =
      settings_fix_edit.user_register[i+rprbigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER] = tempWriteArray[offset+i];
  /*
        qDebug()<<"offset= "<<offset;

        qDebug()<<"operativMarker[0]= "<<rprbigcomponent->operativMarker[0];
        qDebug()<<"operativMarker[1]= "<<rprbigcomponent->operativMarker[1];

        qDebug()<<"rprAdresRegister[0]= "<<rprAdresRegister[0];
        qDebug()<<"rprAdresRegister[1]= "<<rprAdresRegister[1];
        qDebug()<<"rprAdresRegister[2]= "<<rprAdresRegister[2];
        qDebug()<<"rprAdresRegister[3]= "<<rprAdresRegister[3];
        qDebug()<<"rprAdresRegister[4]= "<<rprAdresRegister[4];
        qDebug()<<"rprAdresRegister[5]= "<<rprAdresRegister[5];
        qDebug()<<"rprAdresRegister[6]= "<<rprAdresRegister[6];
        qDebug()<<"rprAdresRegister[7]= "<<rprAdresRegister[7];
        qDebug()<<"rprAdresRegister[8]= "<<rprAdresRegister[8];
        qDebug()<<"rprAdresRegister[9]= "<<rprAdresRegister[9];
  */
  /*
  �������/����� ��������� � ���� (�������� ����� � ���� type_definition.h ��� ��������� ���� __CONFIG)
  settings_fix_prt/settings_fix/settings_fix_edit->user_register[]
  
  */
  config_settings_modified |= MASKA_FOR_BIT(BIT_CHANGED_SETTINGS);
  restart_timeout_idle_new_settings = true;
 return 0;
}//

int privateRPRBigGetReg2(int adrReg)
{
  //��������� ������� ��������
  int count_register = rprbigcomponent->countObject*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
