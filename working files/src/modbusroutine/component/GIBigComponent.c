#include "header.h"

//��������� ������� � ����� ������
#define BEGIN_ADR_REGISTER 4664
//���� �-�� �������
#define TOTAL_OBJ 128
#define REGISTER_FOR_OBJ 1

int privateGIBigGetReg1(int adrReg);
int privateGIBigGetReg2(int adrReg);

int getGIBigModbusRegister(int);//�������� ���������� ��������
int getGIBigModbusBit(int);//�������� ���������� ����
int setGIBigModbusRegister(int, int);//�������� ���������� ��������
int setGIBigModbusBit(int, int);//�������� ���������� ����

void setGIBigCountObject(void);//�������� �-�� �������
void preGIBigReadAction(void);//action �� ������
void postGIBigReadAction(void);//action ����� ������
void preGIBigWriteAction(void);//action �� ������
int postGIBigWriteAction(void);//action ����� ������
//void loadGIBigActualData(void);

COMPONENT_OBJ *gibigcomponent;

/**************************************/
//���������� ���������� ����������� ���������
/**************************************/
void constructorGIBigComponent(COMPONENT_OBJ *gibigcomp)
{
  gibigcomponent = gibigcomp;

  gibigcomponent->countObject = 0;//�-�� �������

  gibigcomponent->getModbusRegister = getGIBigModbusRegister;//�������� ���������� ��������
  gibigcomponent->getModbusBit      = getGIBigModbusBit;//�������� ���������� ����
  gibigcomponent->setModbusRegister = setGIBigModbusRegister;//�������� ���������� ��������
  gibigcomponent->setModbusBit      = setGIBigModbusBit;//�������� ���������� ����

  gibigcomponent->preReadAction   = preGIBigReadAction;//action �� ������
  gibigcomponent->postReadAction  = postGIBigReadAction;//action ����� ������
  gibigcomponent->preWriteAction  = preGIBigWriteAction;//action �� ������
  gibigcomponent->postWriteAction = postGIBigWriteAction;//action ����� ������

  gibigcomponent->isActiveActualData = 0;
}//prepareDVinConfig
/*
void loadGIBigActualData(void) {
 setGIBigCountObject(); //�������� �-�� �������
  //ActualData
   __LN_MEANDER *arr = (__LN_MEANDER*)(spca_of_p_prt[ID_FB_MEANDER - _ID_FB_FIRST_VAR]);
   for(int item=0; item<gibigcomponent->countObject; item++) {

   int value = arr[item].settings.set_delay[0];
   tempReadArray[item*REGISTER_FOR_OBJ+0] = value;
   }//for

}//loadActualData() 
*/

int getGIBigModbusRegister(int adrReg)
{
  //�������� ���������� ��������
extern int pointInterface;//����� ���������� 0-USB 1-RS485
  if(privateGIBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(gibigcomponent->isActiveActualData) setGIBigCountObject(); //�-�� �������
  gibigcomponent->isActiveActualData = 0;
  if(privateGIBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  superSetOperativMarker(gibigcomponent, adrReg);
/*
   __LN_MEANDER *arr = (__LN_MEANDER*)(spca_of_p_prt[ID_FB_MEANDER - _ID_FB_FIRST_VAR]);
  int offset = adrReg-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//������ ����������
  switch(offset%REGISTER_FOR_OBJ) {//������ �������� 
   case 0:
   return arr[idxSubObj].settings.set_delay[0]/100;
 }//switch
*/
  int offset = adrReg-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//������ ����������
  __settings_for_MEANDER *arr =  ((config_settings_modified & MASKA_FOR_BIT(BIT_USB_LOCKS)) == 0 ) ? &(((__LN_MEANDER*)(spca_of_p_prt[ID_FB_MEANDER - _ID_FB_FIRST_VAR])) + idxSubObj)->settings : (((__settings_for_MEANDER*)(sca_of_p[ID_FB_MEANDER - _ID_FB_FIRST_VAR])) + idxSubObj);
  if(pointInterface)//����� ���������� 0-USB 1-RS485
                        arr =  ((config_settings_modified & MASKA_FOR_BIT(BIT_RS485_LOCKS)) == 0 ) ? &(((__LN_MEANDER*)(spca_of_p_prt[ID_FB_MEANDER - _ID_FB_FIRST_VAR])) + idxSubObj)->settings : (((__settings_for_MEANDER*)(sca_of_p[ID_FB_MEANDER - _ID_FB_FIRST_VAR])) + idxSubObj);
  switch(offset%REGISTER_FOR_OBJ) {//������ �������� 
   case 0:
   return arr->set_delay[0]/100;
 }//switch

  return 0;
}//getDOUTBigModbusRegister(int adrReg)
int getGIBigModbusBit(int x)
{
  //�������� ���������� ��������
  UNUSED(x);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setGIBigModbusRegister(int adrReg, int dataReg)
{
  //�������� ���������� ��������
  if(privateGIBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(gibigcomponent->isActiveActualData) setGIBigCountObject(); //�-�� �������
  gibigcomponent->isActiveActualData = 0;
  if(privateGIBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  superSetOperativMarker(gibigcomponent, adrReg);
  superSetTempWriteArray(dataReg);//�������� � �����

    if(dataReg>100) return MARKER_ERRORDIAPAZON;
    if(dataReg<5) return MARKER_ERRORDIAPAZON;

  return 0;
}//getDOUTBigModbusRegister(int adrReg)
int setGIBigModbusBit(int x, int y)
{
  UNUSED(x);
  UNUSED(y);
  //�������� ���������� ��������
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void setGIBigCountObject(void) {
//�������� �-�� �������
  int cntObj = current_config.n_meander;  //ʳ������ ���������� �������
  if(cntObj<0) return;
  if(cntObj>TOTAL_OBJ) return;
  gibigcomponent->countObject = cntObj;
}//
void preGIBigReadAction(void) {
//action �� ������
  gibigcomponent->operativMarker[0] = -1;
  gibigcomponent->operativMarker[1] = -1;//����������� ������
  gibigcomponent->isActiveActualData = 1;
}//
void postGIBigReadAction(void) {
//action ����� ������
  if(gibigcomponent->operativMarker[0]<0) return;//�� ���� ������
}//
void preGIBigWriteAction(void) {
//action �� ������
  gibigcomponent->operativMarker[0] = -1;
  gibigcomponent->operativMarker[1] = -1;//����������� ������
  gibigcomponent->isActiveActualData = 1;
}//
int postGIBigWriteAction(void) {
//action ����� ������
  if(gibigcomponent->operativMarker[0]<0) return 0;//�� ���� ������
  int offsetTempWriteArray = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//����� �������� TempWriteArray
  int countRegister = gibigcomponent->operativMarker[1]-gibigcomponent->operativMarker[0]+1;
  if(gibigcomponent->operativMarker[1]<0) countRegister = 1;

   __settings_for_MEANDER *arr  = (__settings_for_MEANDER*)(sca_of_p[ID_FB_MEANDER - _ID_FB_FIRST_VAR]);
   __settings_for_MEANDER *arr1 = (__settings_for_MEANDER*)(sca_of_p_edit[ID_FB_MEANDER - _ID_FB_FIRST_VAR]);
  for(int i=0; i<countRegister; i++) {
  int offset = i+gibigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//������ ����������

   arr1[idxSubObj].set_delay[0] = arr[idxSubObj].set_delay[0] = (tempWriteArray[offsetTempWriteArray+i])*100;

  }//for
  config_settings_modified |= MASKA_FOR_BIT(BIT_CHANGED_SETTINGS);
  restart_timeout_idle_new_settings = true;
 return 0;
}//

int privateGIBigGetReg1(int adrReg)
{
  //��������� ���������� ��������
  int count_register = gibigcomponent->countObject*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg1(int adrReg)
int privateGIBigGetReg2(int adrReg)
{
  //��������� ������� ��������
  int count_register = TOTAL_OBJ*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
