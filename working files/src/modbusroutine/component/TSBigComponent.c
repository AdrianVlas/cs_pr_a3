#include "header.h"

//��������� ������� � ����� ������
#define BEGIN_ADR_REGISTER 7880
//���� �-�� �������
#define TOTAL_OBJ 128
#define REGISTER_FOR_OBJ 5

int privateTSBigGetReg1(int adrReg);
int privateTSBigGetReg2(int adrReg);

int getTSBigModbusRegister(int);//�������� ���������� ��������
int getTSBigModbusBit(int);//�������� ���������� ����
int setTSBigModbusRegister(int, int);//�������� ���������� ��������
int setTSBigModbusBit(int, int);//�������� ���������� ����

void setTSBigCountObject(void);//�������� �-�� �������
void preTSBigReadAction(void);//action �� ������
void postTSBigReadAction(void);//action ����� ������
void preTSBigWriteAction(void);//action �� ������
int postTSBigWriteAction(void);//action ����� ������
void loadTSBigActualData(void);
int getTSmallModbusBeginAdrRegister(void);
void repairEditArrayTS(int countRegister, __settings_for_TS *arr, __settings_for_TS *arr1);

COMPONENT_OBJ *tsbigcomponent;

/**************************************/
//���������� ���������� ����������������
/**************************************/
void constructorTSBigComponent(COMPONENT_OBJ *tsbigcomp)
{
  tsbigcomponent = tsbigcomp;

  tsbigcomponent->countObject = 0;//�-�� �������

  tsbigcomponent->getModbusRegister = getTSBigModbusRegister;//�������� ���������� ��������
  tsbigcomponent->getModbusBit      = getTSBigModbusBit;//�������� ���������� ����
  tsbigcomponent->setModbusRegister = setTSBigModbusRegister;//�������� ���������� ��������
  tsbigcomponent->setModbusBit      = setTSBigModbusBit;//�������� ���������� ����

  tsbigcomponent->preReadAction   = preTSBigReadAction;//action �� ������
  tsbigcomponent->postReadAction  = postTSBigReadAction;//action ����� ������
  tsbigcomponent->preWriteAction  = preTSBigWriteAction;//action �� ������
  tsbigcomponent->postWriteAction = postTSBigWriteAction;//action ����� ������

  tsbigcomponent->isActiveActualData = 0;
}//prepareDVinConfig

int getTSBigModbusRegister(int adrReg)
{
  //�������� ���������� ��������
extern int pointInterface;//����� ���������� 0-USB 1-RS485
  if(privateTSBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(tsbigcomponent->isActiveActualData) setTSBigCountObject(); //�������� �-�� �������
  tsbigcomponent->isActiveActualData = 0;
  if(privateTSBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  superSetOperativMarker(tsbigcomponent, adrReg);

  int offset = adrReg-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//������ ����������
  __settings_for_TS *arr =  ((config_settings_modified & MASKA_FOR_BIT(BIT_USB_LOCKS)) == 0 ) ? &(((__LN_TS*)(spca_of_p_prt[ID_FB_TS - _ID_FB_FIRST_VAR])) + idxSubObj)->settings : (((__settings_for_TS*)(sca_of_p[ID_FB_TS - _ID_FB_FIRST_VAR])) + idxSubObj);
  if(pointInterface)//����� ���������� 0-USB 1-RS485
                        arr =  ((config_settings_modified & MASKA_FOR_BIT(BIT_RS485_LOCKS)) == 0 ) ? &(((__LN_TS*)(spca_of_p_prt[ID_FB_TS - _ID_FB_FIRST_VAR])) + idxSubObj)->settings : (((__settings_for_TS*)(sca_of_p[ID_FB_TS - _ID_FB_FIRST_VAR])) + idxSubObj);

  switch(offset%REGISTER_FOR_OBJ) {//������ �������� 
   case 0:
   //In TC 0  item
    return arr->param[TS_LOGIC_INPUT] & 0xffff;//LEDIN 0 �� item
   case 1:
    return (arr->param[TS_LOGIC_INPUT] >> 16) & 0x7fff;//LEDIN 1 �� item

   case 2:
   //Block TC 0  item
    return arr->param[TS_BLOCK] & 0xffff;//LEDIN 0 �� item
   case 3:
    return (arr->param[TS_BLOCK] >> 16) & 0x7fff;//LEDIN 1 �� item

   case 4:
   //����� �� 0  item
   return getTSmallModbusBeginAdrRegister() + idxSubObj;
  }//switch
  return 0;
}//getDOUTBigModbusRegister(int adrReg)
int getTSBigModbusBit(int x)
{
  //�������� ���������� ��������
  UNUSED(x);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setTSBigModbusRegister(int adrReg, int dataReg)
{
extern int upravlSetting;//���� Setting
extern int upravlSchematic;//���� Shematic
  //�������� ���������� ��������
  if(privateTSBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(tsbigcomponent->isActiveActualData) setTSBigCountObject(); 
  tsbigcomponent->isActiveActualData = 0;
  if(privateTSBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  superSetOperativMarker(tsbigcomponent, adrReg);
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
    upravlSchematic = 1;//���� Shematic
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
   break; 
   case 3:
    //�������� ���������� ������������
    upravlSchematic = 1;//���� Shematic
    if(superControlParam(dataReg)) return MARKER_ERRORDIAPAZON;
   break; 
   case 4:
    //�������� ���������� ������������
    upravlSetting = 1;//���� Setting
    if(superControlParam(dataReg)) return MARKER_ERRORDIAPAZON;
   break; 
  default: return MARKER_OUTPERIMETR;
  }//switch
  return 0;
}//getDOUTBigModbusRegister(int adrReg)
int setTSBigModbusBit(int x, int y)
{
  UNUSED(x);
  UNUSED(y);
  //�������� ���������� ��������
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void setTSBigCountObject(void) {
//�������� �-�� �������
  int cntObj = current_config.n_ts;    //ʳ������ ����� �����������
  if(cntObj<0) return;
  if(cntObj>TOTAL_OBJ) return;
  tsbigcomponent->countObject = cntObj;
}//
void preTSBigReadAction(void) {
//action �� ������
  tsbigcomponent->operativMarker[0] = -1;
  tsbigcomponent->operativMarker[1] = -1;//����������� ������
  tsbigcomponent->isActiveActualData = 1;
}//
void postTSBigReadAction(void) {
//action ����� ������
  if(tsbigcomponent->operativMarker[0]<0) return;//�� ���� ������
}//
void preTSBigWriteAction(void) {
//action �� ������
  tsbigcomponent->operativMarker[0] = -1;
  tsbigcomponent->operativMarker[1] = -1;//����������� ������
  tsbigcomponent->isActiveActualData = 1;
}//
int postTSBigWriteAction(void) {
extern int upravlSetting;//���� Setting
extern int upravlSchematic;//���� Shematic
extern int pointInterface;//����� ���������� 0-USB 1-RS485
//action ����� ������
  if(tsbigcomponent->operativMarker[0]<0) return 0;//�� ���� ������
  int offsetTempWriteArray = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//����� �������� TempWriteArray
  int countRegister = tsbigcomponent->operativMarker[1]-tsbigcomponent->operativMarker[0]+1;
  if(tsbigcomponent->operativMarker[1]<0) countRegister = 1;

   __settings_for_TS *arr  = (__settings_for_TS*)(sca_of_p[ID_FB_TS - _ID_FB_FIRST_VAR]);
   __settings_for_TS *arr1 = (__settings_for_TS*)(sca_of_p_edit[ID_FB_TS - _ID_FB_FIRST_VAR]);
//�������� edit ������
  for(int i=0; i<countRegister; i++) {
  int offset = i+tsbigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//������ ����������
  switch(offset%REGISTER_FOR_OBJ) {//������ �������� 

   case 0://In TC 0
        arr1[idxSubObj].param[TS_LOGIC_INPUT]  &= (uint32_t)~0xffff;
        arr1[idxSubObj].param[TS_LOGIC_INPUT]  |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
   break;
   case 1://In TC 1
        arr1[idxSubObj].param[TS_LOGIC_INPUT]  &= (uint32_t)~(0x7fff<<16);
        arr1[idxSubObj].param[TS_LOGIC_INPUT]  |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
   break; 

   case 2://Block TC 0
        arr1[idxSubObj].param[TS_BLOCK]  &= (uint32_t)~0xffff;
        arr1[idxSubObj].param[TS_BLOCK]  |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
   break;
   case 3://Block TC 1
        arr1[idxSubObj].param[TS_BLOCK]  &= (uint32_t)~(0x7fff<<16);
        arr1[idxSubObj].param[TS_BLOCK]  |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
   break; 

 }//switch
  }//for

  //�������� ����������
  for(int i=0; i<countRegister; i++) {
  int offset = i+tsbigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//������ ����������
  switch(offset%REGISTER_FOR_OBJ) {//������ �������� 

   case 0://In TC 0
   case 1://In TC 1
        if(superValidParam(arr1[idxSubObj].param[TS_LOGIC_INPUT])) 
                {//�������� ����������
                repairEditArrayTS(countRegister, arr, arr1);//������������ edit ������
                return 2;//����
        }//if
  break;

   case 2://Block TC 0
   case 3://Block TC 1
        if(superValidParam(arr1[idxSubObj].param[TS_BLOCK]))
                {//�������� ����������
                repairEditArrayTS(countRegister, arr, arr1);//������������ edit ������
                return 2;//����
        }//if
  break;
 }//switch
  }//for

//�������� ������� - ��������������
  for(int i=0; i<countRegister; i++) {
  int offset = i+tsbigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//������ ����������
  switch(offset%REGISTER_FOR_OBJ) {//������ �������� 

   case 0://In TC 0
        arr1[idxSubObj].param[TS_LOGIC_INPUT] = arr[idxSubObj].param[TS_LOGIC_INPUT] &= (uint32_t)~0xffff;
        arr1[idxSubObj].param[TS_LOGIC_INPUT] = arr[idxSubObj].param[TS_LOGIC_INPUT] |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
   break;
   case 1://In TC 1
        arr1[idxSubObj].param[TS_LOGIC_INPUT] = arr[idxSubObj].param[TS_LOGIC_INPUT] &= (uint32_t)~(0x7fff<<16);
        arr1[idxSubObj].param[TS_LOGIC_INPUT] = arr[idxSubObj].param[TS_LOGIC_INPUT] |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
   break; 

   case 2://Block TC 0
        arr1[idxSubObj].param[TS_BLOCK] = arr[idxSubObj].param[TS_BLOCK] &= (uint32_t)~0xffff;
        arr1[idxSubObj].param[TS_BLOCK] = arr[idxSubObj].param[TS_BLOCK] |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
   break;
   case 3://Block TC 1
        arr1[idxSubObj].param[TS_BLOCK] = arr[idxSubObj].param[TS_BLOCK] &= (uint32_t)~(0x7fff<<16);
        arr1[idxSubObj].param[TS_BLOCK] = arr[idxSubObj].param[TS_BLOCK] |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
   break; 

   case 4://����� ��
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

void repairEditArrayTS(int countRegister, __settings_for_TS *arr, __settings_for_TS *arr1) {
  //������������ edit ������
  for(int i=0; i<countRegister; i++) {
  int offset = i+tsbigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//������ ����������
  switch(offset%REGISTER_FOR_OBJ) {//������ �������� 

   case 0://In TC 0
   case 1://In TC 1
        arr1[idxSubObj].param[TS_LOGIC_INPUT] = arr[idxSubObj].param[TS_LOGIC_INPUT];
   break; 

   case 2://Block TC 0
   case 3://Block TC 1
        arr1[idxSubObj].param[TS_BLOCK] = arr[idxSubObj].param[TS_BLOCK];
   break; 

 }//switch
  }//for
}//repairEditArray(int countRegister, __settings_for_TS *arr, __settings_for_TS *arr1) 

int privateTSBigGetReg1(int adrReg)
{
  //��������� ���������� ��������
  int count_register = tsbigcomponent->countObject*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg1(int adrReg)
int privateTSBigGetReg2(int adrReg)
{
  //��������� ������� ��������
  int count_register = TOTAL_OBJ*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
