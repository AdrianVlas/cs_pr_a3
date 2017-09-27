#include "header.h"

//��������� ������� � ����� ������
#define BEGIN_ADR_REGISTER 8520
//���� �-�� �������
#define TOTAL_OBJ 128
#define REGISTER_FOR_OBJ 3

int privateTUBigGetReg1(int adrReg);
int privateTUBigGetReg2(int adrReg);

int getTUBigModbusRegister(int);//�������� ���������� ��������
int getTUBigModbusBit(int);//�������� ���������� ����
int setTUBigModbusRegister(int, int);//�������� ���������� ��������
int setTUBigModbusBit(int, int);//�������� ���������� ����

void setTUBigCountObject(void);//�������� �-�� �������
void preTUBigReadAction(void);//action �� ������
void postTUBigReadAction(void);//action ����� ������
void preTUBigWriteAction(void);//action �� ������
int postTUBigWriteAction(void);//action ����� ������
void loadTUBigActualData(void);
int getTUSmallModbusBeginAdrRegister(void);
void repairEditArrayTU(int countRegister, __settings_for_TU *arr, __settings_for_TU *arr1);
void config_and_settingsTUBig(void);//action ���������

COMPONENT_OBJ *tubigcomponent;

/**************************************/
//���������� ���������� ��������������
/**************************************/
void constructorTUBigComponent(COMPONENT_OBJ *tubigcomp)
{
  tubigcomponent = tubigcomp;

  tubigcomponent->countObject = 0;//�-�� �������

  tubigcomponent->getModbusRegister = getTUBigModbusRegister;//�������� ���������� ��������
  tubigcomponent->getModbusBit      = getTUBigModbusBit;//�������� ���������� ����
  tubigcomponent->setModbusRegister = setTUBigModbusRegister;//�������� ���������� ��������
  tubigcomponent->setModbusBit      = setTUBigModbusBit;//�������� ���������� ����

  tubigcomponent->preReadAction   = preTUBigReadAction;//action �� ������
  tubigcomponent->postReadAction  = postTUBigReadAction;//action ����� ������
  tubigcomponent->preWriteAction  = preTUBigWriteAction;//action �� ������
  tubigcomponent->postWriteAction = postTUBigWriteAction;//action ����� ������
  tubigcomponent->config_and_settings = config_and_settingsTUBig;//action ���������

  tubigcomponent->isActiveActualData = 0;
}//prepareDVinConfig

int getTUBigModbusRegister(int adrReg)
{
  //�������� ���������� ��������
extern int pointInterface;//����� ���������� 0-USB 1-RS485
  if(privateTUBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(tubigcomponent->isActiveActualData) setTUBigCountObject(); //�������� �-�� �������
  tubigcomponent->isActiveActualData = 0;
  if(privateTUBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  superSetOperativMarker(tubigcomponent, adrReg);

  int offset = adrReg-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//������ ����������
  __settings_for_TU *arr =  ((config_settings_modified & MASKA_FOR_BIT(BIT_USB_LOCKS)) == 0 ) ? &(((__LN_TU*)(spca_of_p_prt[ID_FB_TU - _ID_FB_FIRST_VAR])) + idxSubObj)->settings : (((__settings_for_TU*)(sca_of_p[ID_FB_TU - _ID_FB_FIRST_VAR])) + idxSubObj);
  if(pointInterface)//����� ���������� 0-USB 1-RS485
                        arr =  ((config_settings_modified & MASKA_FOR_BIT(BIT_RS485_LOCKS)) == 0 ) ? &(((__LN_TU*)(spca_of_p_prt[ID_FB_TU - _ID_FB_FIRST_VAR])) + idxSubObj)->settings : (((__settings_for_TU*)(sca_of_p[ID_FB_TU - _ID_FB_FIRST_VAR])) + idxSubObj);

  switch(offset%REGISTER_FOR_OBJ) {//������ �������� 
   case 0:
   //Block �� 0  item
    return arr->param[TU_BLOCK] & 0xffff;//
   case 1:
    return (arr->param[TU_BLOCK] >> 16) & 0x7fff;//

   case 2:
   //����� �� 0  item
    return getTUSmallModbusBeginAdrRegister() + idxSubObj;
  }//switch
  return 0;
}//getDOUTBigModbusRegister(int adrReg)
int getTUBigModbusBit(int x)
{
  //�������� ���������� ��������
  UNUSED(x);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setTUBigModbusRegister(int adrReg, int dataReg)
{
extern int upravlSetting;//���� Setting
extern int upravlSchematic;//���� Shematic
  //�������� ���������� ��������
  if(privateTUBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(tubigcomponent->isActiveActualData) setTUBigCountObject(); 
  tubigcomponent->isActiveActualData = 0;
  if(privateTUBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  superSetOperativMarker(tubigcomponent, adrReg);
  superSetTempWriteArray(dataReg);//�������� � �����

  switch((adrReg-BEGIN_ADR_REGISTER)%REGISTER_FOR_OBJ) {
   case 0:
    upravlSchematic = 1;//���� Shematic
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
   break; 
   case 1:
    //�������� ���������� ������������
    upravlSchematic = 1;//���� Shematic
    if(superControlParam(dataReg)) return MARKER_ERRORDIAPAZON;
   break; 
   case 2:
    upravlSetting = 1;//���� Setting
   break; 
  default: return MARKER_OUTPERIMETR;
  }//switch
  return 0;
}//getDOUTBigModbusRegister(int adrReg)
int setTUBigModbusBit(int x, int y)
{
  UNUSED(x);
  UNUSED(y);
  //�������� ���������� ��������
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void setTUBigCountObject(void) {
//�������� �-�� �������
  int cntObj = current_config.n_tu;    //ʳ������ ����� �����������
  if(cntObj<0) return;
  if(cntObj>TOTAL_OBJ) return;
  tubigcomponent->countObject = cntObj;
}//
void preTUBigReadAction(void) {
//action �� ������
  tubigcomponent->operativMarker[0] = -1;
  tubigcomponent->operativMarker[1] = -1;//����������� ������
  tubigcomponent->isActiveActualData = 1;
}//
void postTUBigReadAction(void) {
//action ����� ������
  if(tubigcomponent->operativMarker[0]<0) return;//�� ���� ������
}//
void preTUBigWriteAction(void) {
//action �� ������
  tubigcomponent->operativMarker[0] = -1;
  tubigcomponent->operativMarker[1] = -1;//����������� ������
  tubigcomponent->isActiveActualData = 1;
}//
int postTUBigWriteAction(void) {
extern int upravlSetting;//���� Setting
extern int upravlSchematic;//���� Shematic
extern int pointInterface;//����� ���������� 0-USB 1-RS485
//action ����� ������
  if(tubigcomponent->operativMarker[0]<0) return 0;//�� ���� ������
  int offsetTempWriteArray = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//����� �������� TempWriteArray
  int countRegister = tubigcomponent->operativMarker[1]-tubigcomponent->operativMarker[0]+1;
  if(tubigcomponent->operativMarker[1]<0) countRegister = 1;

   __settings_for_TU *arr  = (__settings_for_TU*)(sca_of_p[ID_FB_TU - _ID_FB_FIRST_VAR]);
   __settings_for_TU *arr1 = (__settings_for_TU*)(sca_of_p_edit[ID_FB_TU - _ID_FB_FIRST_VAR]);
//�������� edit ������
  for(int i=0; i<countRegister; i++) {
  int offset = i+tubigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//������ ����������
  switch(offset%REGISTER_FOR_OBJ) {//������ �������� 

   case 0://Block �� 0
        arr1[idxSubObj].param[TU_BLOCK]  &= (uint32_t)~0xffff;
        arr1[idxSubObj].param[TU_BLOCK]  |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
   break;
   case 1://Block �� 1
        arr1[idxSubObj].param[TU_BLOCK]  &= (uint32_t)~(0x7fff<<16);
        arr1[idxSubObj].param[TU_BLOCK]  |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
   break; 

 }//switch
  }//for

  //�������� ����������
  for(int i=0; i<countRegister; i++) {
  int offset = i+tubigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//������ ����������
  switch(offset%REGISTER_FOR_OBJ) {//������ �������� 

   case 0://Block �� 0
   case 1://Block �� 1
        if(superValidParam(arr1[idxSubObj].param[TU_BLOCK])) 
                {//�������� ����������
                repairEditArrayTU(countRegister, arr, arr1);//������������ edit ������
                return 2;//����
        }//if
  break;

 }//switch
  }//for

//�������� ������� - ��������������
  for(int i=0; i<countRegister; i++) {
  int offset = i+tubigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//������ ����������
  switch(offset%REGISTER_FOR_OBJ) {//������ �������� 

   case 0://Block �� 0
        arr1[idxSubObj].param[TU_BLOCK] = arr[idxSubObj].param[TU_BLOCK] &= (uint32_t)~0xffff;
        arr1[idxSubObj].param[TU_BLOCK] = arr[idxSubObj].param[TU_BLOCK] |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
   break;
   case 1://Block �� 1
        arr1[idxSubObj].param[TU_BLOCK] = arr[idxSubObj].param[TU_BLOCK] &= (uint32_t)~(0x7fff<<16);
        arr1[idxSubObj].param[TU_BLOCK] = arr[idxSubObj].param[TU_BLOCK] |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
   break; 

   case 2://����� ��
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

void repairEditArrayTU(int countRegister, __settings_for_TU *arr, __settings_for_TU *arr1) {
  //������������ edit ������
  for(int i=0; i<countRegister; i++) {
  int offset = i+tubigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//������ ����������
  switch(offset%REGISTER_FOR_OBJ) {//������ �������� 

   case 0://Block �� 0
   case 1://Block �� 1
        arr1[idxSubObj].param[TU_BLOCK] = arr[idxSubObj].param[TU_BLOCK];
   break; 
 }//switch
  }//for
}//repairEditArray(int countRegister, __settings_for_TU *arr, __settings_for_TU *arr1) 

int privateTUBigGetReg1(int adrReg)
{
  //��������� ���������� ��������
  int count_register = tubigcomponent->countObject*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg1(int adrReg)
int privateTUBigGetReg2(int adrReg)
{
  //��������� ������� ��������
  int count_register = TOTAL_OBJ*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)

void config_and_settingsTUBig(void)
{
//action ���������
}

