#include "header.h"

//��������� ������� � ����� ������
#define BEGIN_ADR_REGISTER 15000
//���� �-�� �������
#define REGISTER_FOR_OBJ 2
//���� �-�� �������
#define TOTAL_OBJ 128

int privateMEBigGetReg1(int adrReg);
int privateMEBigGetReg2(int adrReg);

int getMEBigModbusRegister(int);//�������� ���������� ��������
int getMEBigModbusBit(int);//�������� ���������� ����
int setMEBigModbusRegister(int, int);//�������� ���������� ��������
int setMEBigModbusBit(int, int);//�������� ���������� ����

void setMEBigCountObject(void);
void preMEBigReadAction(void);//action �� ������
void postMEBigReadAction(void);//action ����� ������
void preMEBigWriteAction(void);//action �� ������
int postMEBigWriteAction(void);//action ����� ������
void repairEditArrayME(int countRegister, __LOG_INPUT *arr, __LOG_INPUT *arr1);

COMPONENT_OBJ *mebigcomponent;

/**************************************/
//���������� ���������� ������ �������
/**************************************/
void constructorMEBigComponent(COMPONENT_OBJ *mebigcomp)
{
  mebigcomponent = mebigcomp;

  mebigcomponent->countObject = 0;//�-�� �������

  mebigcomponent->getModbusRegister = getMEBigModbusRegister;//�������� ���������� ��������
  mebigcomponent->getModbusBit      = getMEBigModbusBit;//�������� ���������� ��������
  mebigcomponent->setModbusRegister = setMEBigModbusRegister;//�������� ���������� ��������
  mebigcomponent->setModbusBit      = setMEBigModbusBit;//�������� ���������� ��������

  mebigcomponent->preReadAction   = preMEBigReadAction;//action �� ������
  mebigcomponent->postReadAction  = postMEBigReadAction;//action ����� ������
  mebigcomponent->preWriteAction  = preMEBigWriteAction;//action �� ������
  mebigcomponent->postWriteAction = postMEBigWriteAction;//action ����� ������

  mebigcomponent->isActiveActualData = 0;
}//prepareDVinConfig

int getMEBigModbusRegister(int adrReg)
{
extern int pointInterface;//����� ���������� 0-USB 1-RS485
  //�������� ���������� ��������
  if(privateMEBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(mebigcomponent->isActiveActualData) setMEBigCountObject(); //�������� �-�� �������
  mebigcomponent->isActiveActualData = 0;
  if(privateMEBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  superSetOperativMarker(mebigcomponent, adrReg);

  int offset = adrReg-BEGIN_ADR_REGISTER;

  switch(offset) {//������ �������� 
   case 0:
   //�-�� ������� 0
     return info_rejestrator_log.number_records & 0xffff;
   case 1:
   //�-�� ������� 1
    return (info_rejestrator_log.number_records >> 16) & 0x7fff;//
  }//switch

  __LOG_INPUT *arr =  ((config_settings_modified & MASKA_FOR_BIT(BIT_USB_LOCKS  )) == 0 ) ? (__LOG_INPUT*)(spca_of_p_prt[ID_FB_EVENT_LOG - _ID_FB_FIRST_VAR]) + 1 : ((__LOG_INPUT*)sca_of_p[ID_FB_EVENT_LOG - _ID_FB_FIRST_VAR]);
  int idxParam = ((offset-2)/2);//������ param
  if(pointInterface)//����� ���������� 0-USB 1-RS485
               arr =  ((config_settings_modified & MASKA_FOR_BIT(BIT_RS485_LOCKS)) == 0 ) ? (__LOG_INPUT*)(spca_of_p_prt[ID_FB_EVENT_LOG - _ID_FB_FIRST_VAR]) + 1 : ((__LOG_INPUT*)sca_of_p[ID_FB_EVENT_LOG - _ID_FB_FIRST_VAR]);

  switch((offset-2)%REGISTER_FOR_OBJ) {//������ �������� 
   case 0:
        return  arr[idxParam] & 0xffff;//
   case 1:
        return  (arr[idxParam] >> 16) & 0x7fff;//
  }//switch

  return 0;
}//getDOUTBigModbusRegister(int adrReg)
int getMEBigModbusBit(int x)
{
  //�������� ���������� ��������
  UNUSED(x);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void setMEBigCountObject(void) {
//�������� �-�� �������
  int cntObj = current_config.n_log*LOG_SIGNALS_IN;    //ʳ������ ��������� ������� ����
  if (cntObj > 128) cntObj = 128;
  if(cntObj<0) return;
  if(cntObj>TOTAL_OBJ) return;
  mebigcomponent->countObject = cntObj;
}//
int setMEBigModbusRegister(int adrReg, int dataReg)
{
extern int upravlSetting;//���� Setting
extern int upravlSchematic;//���� Shematic
  //�������� ���������� ��������
  if(privateMEBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(mebigcomponent->isActiveActualData) setMEBigCountObject(); //�-�� �������
  mebigcomponent->isActiveActualData = 0;
  if(privateMEBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  superSetOperativMarker(mebigcomponent, adrReg);
  superSetTempWriteArray(dataReg);//�������� � �����

  int offset = adrReg-BEGIN_ADR_REGISTER;

  switch(offset) {//������ �������� 
   case 0:
   case 1:
   //�-�� ������� 0
     upravlSetting = 1;//���� Setting
     break;
  }//switch

  int idxParam = ((offset-2)/2);//������ param
  if(idxParam<0) return 0;

  switch((offset-2)%REGISTER_FOR_OBJ) {//������ �������� 
   case 0:
        upravlSchematic = 1;//���� Shematic
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
     break;
   case 1:
        upravlSchematic = 1;//���� Shematic
    //�������� ���������� ������������
    if(superControlParam(dataReg)) return MARKER_ERRORDIAPAZON;
     break;

  }//switch

  return 0;
}//getDOUTBigModbusRegister(int adrReg)
int setMEBigModbusBit(int x, int y)
{
  UNUSED(x);
  UNUSED(y);
  //�������� ���������� ��������
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void preMEBigReadAction(void) {
//action �� ������
  mebigcomponent->operativMarker[0] = -1;
  mebigcomponent->operativMarker[1] = -1;//����������� ������
  mebigcomponent->isActiveActualData = 1;
}//
void postMEBigReadAction(void) {
//action ����� ������
  if(mebigcomponent->operativMarker[0]<0) return;//�� ���� ������
}//
void preMEBigWriteAction(void) {
//action �� ������
  mebigcomponent->operativMarker[0] = -1;
  mebigcomponent->operativMarker[1] = -1;//����������� ������
  mebigcomponent->isActiveActualData = 1;
}//
int postMEBigWriteAction(void) {
extern int upravlSetting;//���� Setting
extern int upravlSchematic;//���� Shematic
extern int pointInterface;//����� ���������� 0-USB 1-RS485
//action ����� ������
  if(mebigcomponent->operativMarker[0]<0) return 0;//�� ���� ������
  int offsetTempWriteArray = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//����� �������� TempWriteArray
  int countRegister = mebigcomponent->operativMarker[1]-mebigcomponent->operativMarker[0]+1;
  if(mebigcomponent->operativMarker[1]<0) countRegister = 1;

   __LOG_INPUT *arr  = (__LOG_INPUT*)(sca_of_p[ID_FB_EVENT_LOG - _ID_FB_FIRST_VAR]);
   __LOG_INPUT *arr1 = (__LOG_INPUT*)(sca_of_p_edit[ID_FB_EVENT_LOG - _ID_FB_FIRST_VAR]);
//�������� edit ������
  for(int i=0; i<countRegister; i++) {
  int offset = i+mebigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;

  int idxParam = ((offset-2)/2);//������ param
  if(idxParam<0) break;
  switch((offset-2)%REGISTER_FOR_OBJ) {//������ �������� 
   case 0://���� 0 item
        arr1[idxParam]  &= (uint32_t)~0xffff;
        arr1[idxParam]  |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
   break;
   case 1://���� 1 item
        arr1[idxParam]  &= (uint32_t)~(0x7fff<<16);
        arr1[idxParam]  |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
   break; 

 }//switch
  }//for

  //�������� ����������
  for(int i=0; i<countRegister; i++) {
  int offset = i+mebigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;
  int idxParam = ((offset-2)/2);//������ param
  if(idxParam<0) break;
  switch((offset-2)%REGISTER_FOR_OBJ) {//������ �������� 
   case 0://���� 0 item
   case 1://���� 1 item
        if(superValidParam(arr1[idxParam])) 
                {//�������� ����������
                repairEditArrayME(countRegister, arr, arr1);//������������ edit ������
                return 2;//����
        }//if
  break;
 }//switch
  }//for

//�������� ������� - ��������������
  for(int i=0; i<countRegister; i++) {
  int offset = i+mebigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;

  switch(offset) {//������ �������� 
   case 0:
   //�-�� ������� 0
     info_rejestrator_log.number_records &= (uint32_t)~0xffff;
     info_rejestrator_log.number_records |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
     break;
   case 1:
   //�-�� ������� 1
     info_rejestrator_log.number_records &= (uint32_t)~(0x7fff<<16);
     info_rejestrator_log.number_records |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
     break;
  }//switch

  int idxParam = ((offset-2)/2);//������ param
  if(idxParam<0) break;
  switch((offset-2)%REGISTER_FOR_OBJ) {//������ �������� 
   case 0://���� 0 item
        arr1[idxParam] = arr[idxParam] &= (uint32_t)~0xffff;
        arr1[idxParam] = arr[idxParam] |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
   break;
   case 1://���� 1 item
        arr1[idxParam] = arr[idxParam] &= (uint32_t)~(0x7fff<<16);
        arr1[idxParam] = arr[idxParam] |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
   break; 

 }//switch
  }//for

  if(upravlSetting)//���� Setting
     config_settings_modified |= MASKA_FOR_BIT(BIT_CHANGED_SETTINGS);
  if(upravlSchematic)//���� Shematic
     config_settings_modified |= MASKA_FOR_BIT(BIT_CHANGED_SCHEMATIC);
  if(pointInterface)//����� ���������� 0-USB 1-RS485
     config_settings_modified |= MASKA_FOR_BIT(BIT_RS485_LOCKS);
  else 
     config_settings_modified |= MASKA_FOR_BIT(BIT_USB_LOCKS);
  restart_timeout_idle_new_settings = true;
 return 0;
}//

void repairEditArrayME(int countRegister, __LOG_INPUT *arr, __LOG_INPUT *arr1) {
  //������������ edit ������
  for(int i=0; i<countRegister; i++) {
  int offset = i+mebigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;

  int idxParam = ((offset-2)/2);//������ param
  if(idxParam<0) break;
  switch((offset-2)%REGISTER_FOR_OBJ) {//������ �������� 
   case 0://���� 0 item
   case 1://���� 1 item
        arr1[idxParam] = arr[idxParam];
   break; 

 }//switch
  }//for
}//repairEditArray(int countRegister, __LOG_INPUT *arr, __LOG_INPUT *arr1) 

int privateMEBigGetReg1(int adrReg)
{
  //��������� ���������� ��������
  int count_register = 2+mebigcomponent->countObject*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
int privateMEBigGetReg2(int adrReg)
{
  //��������� ������� ��������
  int count_register = 2+TOTAL_OBJ*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
