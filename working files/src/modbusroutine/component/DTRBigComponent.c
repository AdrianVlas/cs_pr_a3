#include "header.h"

//��������� ������� � ����� ������
#define BEGIN_ADR_REGISTER 6856
//���� �-�� �������
#define TOTAL_OBJ 128
#define REGISTER_FOR_OBJ 8

int privateDTRBigGetReg1(int adrReg);
int privateDTRBigGetReg2(int adrReg);

int getDTRBigModbusRegister(int);//�������� ���������� ��������
int getDTRBigModbusBit(int);//�������� ���������� ����
int setDTRBigModbusRegister(int, int);// ��������
int setDTRBigModbusBit(int, int);// ����

void setDTRBigCountObject(void);//�������� �-�� �������
void preDTRBigReadAction(void);//action �� ������
void postDTRBigReadAction(void);//action ����� ������
void preDTRBigWriteAction(void);//action �� ������
int postDTRBigWriteAction(void);//action ����� ������
void loadDTRBigActualData(void);

COMPONENT_OBJ *dtrbigcomponent;

/**************************************/
//���������� ���������� D-�������
/**************************************/
void constructorDTRBigComponent(COMPONENT_OBJ *dtrbigcomp)
{
  dtrbigcomponent = dtrbigcomp;

  dtrbigcomponent->countObject = 0;//�-�� �������

  dtrbigcomponent->getModbusRegister = getDTRBigModbusRegister;//�������� ���������� ��������
  dtrbigcomponent->getModbusBit      = getDTRBigModbusBit;//�������� ���������� ����
  dtrbigcomponent->setModbusRegister = setDTRBigModbusRegister;// ��������
  dtrbigcomponent->setModbusBit      = setDTRBigModbusBit;// ����

  dtrbigcomponent->preReadAction   = preDTRBigReadAction;//action �� ������
  dtrbigcomponent->postReadAction  = postDTRBigReadAction;//action ����� ������
  dtrbigcomponent->preWriteAction  = preDTRBigWriteAction;//action �� ������
  dtrbigcomponent->postWriteAction = postDTRBigWriteAction;//action ����� ������

  dtrbigcomponent->isActiveActualData = 0;
}//prepareDVinConfig
/*
void loadDTRBigActualData(void) {
 setDTRBigCountObject(); //�������� �-�� �������
  //ActualData
   __LN_TRIGGER *arr = (__LN_TRIGGER*)(spca_of_p_prt[ID_FB_TRIGGER - _ID_FB_FIRST_VAR]);
   for(int item=0; item<dtrbigcomponent->countObject; item++) {

   //Set D-T 0  item
   int value = arr[item].settings.param[INPUT_TRIGGER_SET] & 0xffff;//
   tempReadArray[item*REGISTER_FOR_OBJ+0] = value;
   value = (arr[item].settings.param[INPUT_TRIGGER_SET] >> 16) & 0x7fff;//
   tempReadArray[item*REGISTER_FOR_OBJ+1] = value;

   //CLR D-T 0  item
   value = arr[item].settings.param[INPUT_TRIGGER_RESET] & 0xffff;//
   tempReadArray[item*REGISTER_FOR_OBJ+2] = value;
   value = (arr[item].settings.param[INPUT_TRIGGER_RESET] >> 16) & 0x7fff;//
   tempReadArray[item*REGISTER_FOR_OBJ+3] = value;

   //D D-T 0  item
   value = arr[item].settings.param[INPUT_TRIGGER_D] & 0xffff;//
   tempReadArray[item*REGISTER_FOR_OBJ+4] = value;
   value = (arr[item].settings.param[INPUT_TRIGGER_D] >> 16) & 0x7fff;//
   tempReadArray[item*REGISTER_FOR_OBJ+5] = value;

   //C D-T 0  item
   value = arr[item].settings.param[INPUT_TRIGGER_C] & 0xffff;//
   tempReadArray[item*REGISTER_FOR_OBJ+6] = value;
   value = (arr[item].settings.param[INPUT_TRIGGER_C] >> 16) & 0x7fff;//
   tempReadArray[item*REGISTER_FOR_OBJ+7] = value;

   }//for
}//loadActualData() 
*/

int getDTRBigModbusRegister(int adrReg)
{
  //�������� ���������� ��������
extern int pointInterface;//����� ���������� 0-USB 1-RS485
  if(privateDTRBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(dtrbigcomponent->isActiveActualData) setDTRBigCountObject(); //�-�� �������
  dtrbigcomponent->isActiveActualData = 0;
  if(privateDTRBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  superSetOperativMarker(dtrbigcomponent, adrReg);
/*
   __LN_TRIGGER *arr = (__LN_TRIGGER*)(spca_of_p_prt[ID_FB_TRIGGER - _ID_FB_FIRST_VAR]);
  int offset = adrReg-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//������ ����������
  switch(offset%REGISTER_FOR_OBJ) {//������ �������� 
  case 0:
   //Set D-T 0  item
   return arr[idxSubObj].settings.param[INPUT_TRIGGER_SET] & 0xffff;//
  case 1:
   return (arr[idxSubObj].settings.param[INPUT_TRIGGER_SET] >> 16) & 0x7fff;//

  case 2:
   //CLR D-T 0  item
   return arr[idxSubObj].settings.param[INPUT_TRIGGER_RESET] & 0xffff;//
  case 3:
   return (arr[idxSubObj].settings.param[INPUT_TRIGGER_RESET] >> 16) & 0x7fff;//

  case 4:
   //D D-T 0  item
   return arr[idxSubObj].settings.param[INPUT_TRIGGER_D] & 0xffff;//
  case 5:
   return (arr[idxSubObj].settings.param[INPUT_TRIGGER_D] >> 16) & 0x7fff;//

  case 6:
   //C D-T 0  item
   return arr[idxSubObj].settings.param[INPUT_TRIGGER_C] & 0xffff;//
  case 7:
   return (arr[idxSubObj].settings.param[INPUT_TRIGGER_C] >> 16) & 0x7fff;//
  }//switch
*/
  int offset = adrReg-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//������ ����������
  __settings_for_TRIGGER *arr =  ((config_settings_modified & MASKA_FOR_BIT(BIT_USB_LOCKS)) == 0 ) ? &(((__LN_TRIGGER*)(spca_of_p_prt[ID_FB_TRIGGER - _ID_FB_FIRST_VAR])) + idxSubObj)->settings : (((__settings_for_TRIGGER*)(sca_of_p[ID_FB_TRIGGER - _ID_FB_FIRST_VAR])) + idxSubObj);
  if(pointInterface)//����� ���������� 0-USB 1-RS485
                        arr =  ((config_settings_modified & MASKA_FOR_BIT(BIT_RS485_LOCKS)) == 0 ) ? &(((__LN_TRIGGER*)(spca_of_p_prt[ID_FB_TRIGGER - _ID_FB_FIRST_VAR])) + idxSubObj)->settings : (((__settings_for_TRIGGER*)(sca_of_p[ID_FB_TRIGGER - _ID_FB_FIRST_VAR])) + idxSubObj);

  switch(offset%REGISTER_FOR_OBJ) {//������ �������� 
  case 0:
   //Set D-T 0  item
   return arr->param[INPUT_TRIGGER_SET] & 0xffff;//
  case 1:
   return (arr->param[INPUT_TRIGGER_SET] >> 16) & 0x7fff;//

  case 2:
   //CLR D-T 0  item
   return arr->param[INPUT_TRIGGER_RESET] & 0xffff;//
  case 3:
   return (arr->param[INPUT_TRIGGER_RESET] >> 16) & 0x7fff;//

  case 4:
   //D D-T 0  item
   return arr->param[INPUT_TRIGGER_D] & 0xffff;//
  case 5:
   return (arr->param[INPUT_TRIGGER_D] >> 16) & 0x7fff;//

  case 6:
   //C D-T 0  item
   return arr->param[INPUT_TRIGGER_C] & 0xffff;//
  case 7:
   return (arr->param[INPUT_TRIGGER_C] >> 16) & 0x7fff;//
  }//switch
  return 0;
}//getDOUTBigModbusRegister(int adrReg)
int getDTRBigModbusBit(int x)
{
  //�������� ���������� ��������
  UNUSED(x);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setDTRBigModbusRegister(int adrReg, int dataReg)
{
  //�������� ���������� ��������
  if(privateDTRBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(dtrbigcomponent->isActiveActualData) setDTRBigCountObject(); //�-�� �������
  dtrbigcomponent->isActiveActualData = 0;
  if(privateDTRBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  superSetOperativMarker(dtrbigcomponent, adrReg);
  superSetTempWriteArray(dataReg);//�������� � �����

  switch((adrReg-BEGIN_ADR_REGISTER)%REGISTER_FOR_OBJ) {
   case 0:
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
   break; 
   case 1:
    //�������� ���������� ������������
    if(superControlParam(dataReg)) return MARKER_ERRORDIAPAZON;
   break; 
   case 2:
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
   break; 
   case 3:
    //�������� ���������� ������������
    if(superControlParam(dataReg)) return MARKER_ERRORDIAPAZON;
   break; 
   case 4:
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
   break; 
   case 5:
    //�������� ���������� ������������
    if(superControlParam(dataReg)) return MARKER_ERRORDIAPAZON;
   break; 
   case 6:
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
   break; 
   case 7:
    //�������� ���������� ������������
    if(superControlParam(dataReg)) return MARKER_ERRORDIAPAZON;
   break; 
   default: return MARKER_OUTPERIMETR;
  }//switch
  return 0;
}//getDOUTBigModbusRegister(int adrReg)
int setDTRBigModbusBit(int x, int y)
{
  UNUSED(x);
  UNUSED(y);
  //�������� ���������� ��������
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void setDTRBigCountObject(void) {
//�������� �-�� �������
  int cntObj = current_config.n_trigger;    //ʳ������ ������
  if(cntObj<0) return;
  if(cntObj>TOTAL_OBJ) return;
  dtrbigcomponent->countObject = cntObj;
}//
void preDTRBigReadAction(void) {
//action �� ������
  dtrbigcomponent->operativMarker[0] = -1;
  dtrbigcomponent->operativMarker[1] = -1;//����������� ������
  dtrbigcomponent->isActiveActualData = 1;
}//
void postDTRBigReadAction(void) {
//action ����� ������
  if(dtrbigcomponent->operativMarker[0]<0) return;//�� ���� ������
}//
void preDTRBigWriteAction(void) {
//action �� ������
  dtrbigcomponent->operativMarker[0] = -1;
  dtrbigcomponent->operativMarker[1] = -1;//����������� ������
  dtrbigcomponent->isActiveActualData = 1;
}//
int postDTRBigWriteAction(void) {
//action ����� ������
  if(dtrbigcomponent->operativMarker[0]<0) return 0;//�� ���� ������
  int offsetTempWriteArray = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//����� �������� TempWriteArray
  int countRegister = dtrbigcomponent->operativMarker[1]-dtrbigcomponent->operativMarker[0]+1;
  if(dtrbigcomponent->operativMarker[1]<0) countRegister = 1;

//   __LN_TRIGGER *arr = (__LN_TRIGGER*)(spca_of_p_prt[ID_FB_TRIGGER - _ID_FB_FIRST_VAR]);
   __settings_for_TRIGGER *arr  = (__settings_for_TRIGGER*)(sca_of_p[ID_FB_TRIGGER - _ID_FB_FIRST_VAR]);
   __settings_for_TRIGGER *arr1 = (__settings_for_TRIGGER*)(sca_of_p_edit[ID_FB_TRIGGER - _ID_FB_FIRST_VAR]);
  for(int i=0; i<countRegister; i++) {
  int offset = i+dtrbigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//������ ����������
  switch(offset%REGISTER_FOR_OBJ) {//������ �������� 
   case 0://Set D-T item
        arr1[idxSubObj].param[INPUT_TRIGGER_SET] = arr[idxSubObj].param[INPUT_TRIGGER_SET] &= (uint32_t)~0xffff;
        arr1[idxSubObj].param[INPUT_TRIGGER_SET] = arr[idxSubObj].param[INPUT_TRIGGER_SET] |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
   break;
   case 1://Set D-T item
        arr1[idxSubObj].param[INPUT_TRIGGER_SET] = arr[idxSubObj].param[INPUT_TRIGGER_SET] &= (uint32_t)~(0x7fff<<16);
        arr1[idxSubObj].param[INPUT_TRIGGER_SET] = arr[idxSubObj].param[INPUT_TRIGGER_SET] |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
   break; 

   case 2://CLR D-T item
        arr1[idxSubObj].param[INPUT_TRIGGER_RESET] = arr[idxSubObj].param[INPUT_TRIGGER_RESET] &= (uint32_t)~0xffff;
        arr1[idxSubObj].param[INPUT_TRIGGER_RESET] = arr[idxSubObj].param[INPUT_TRIGGER_RESET] |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
   break;
   case 3://CLR D-T item
        arr1[idxSubObj].param[INPUT_TRIGGER_RESET] = arr[idxSubObj].param[INPUT_TRIGGER_RESET] &= (uint32_t)~(0x7fff<<16);
        arr1[idxSubObj].param[INPUT_TRIGGER_RESET] = arr[idxSubObj].param[INPUT_TRIGGER_RESET] |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
   break; 

   case 4://D D-T item
        arr1[idxSubObj].param[INPUT_TRIGGER_D] = arr[idxSubObj].param[INPUT_TRIGGER_D] &= (uint32_t)~0xffff;
        arr1[idxSubObj].param[INPUT_TRIGGER_D] = arr[idxSubObj].param[INPUT_TRIGGER_D] |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
   break;
   case 5://D D-T item
        arr1[idxSubObj].param[INPUT_TRIGGER_D] = arr[idxSubObj].param[INPUT_TRIGGER_D] &= (uint32_t)~(0x7fff<<16);
        arr1[idxSubObj].param[INPUT_TRIGGER_D] = arr[idxSubObj].param[INPUT_TRIGGER_D] |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
   break; 

   case 6://C D-T item
        arr1[idxSubObj].param[INPUT_TRIGGER_C] = arr[idxSubObj].param[INPUT_TRIGGER_C] &= (uint32_t)~0xffff;
        arr1[idxSubObj].param[INPUT_TRIGGER_C] = arr[idxSubObj].param[INPUT_TRIGGER_C] |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
   break;
   case 7://C D-T item
        arr1[idxSubObj].param[INPUT_TRIGGER_C] = arr[idxSubObj].param[INPUT_TRIGGER_C] &= (uint32_t)~(0x7fff<<16);
        arr1[idxSubObj].param[INPUT_TRIGGER_C] = arr[idxSubObj].param[INPUT_TRIGGER_C] |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
   break; 

 }//switch
  }//for
  config_settings_modified |= MASKA_FOR_BIT(BIT_CHANGED_SETTINGS);
  restart_timeout_idle_new_settings = true;
 return 0;
}//

int privateDTRBigGetReg1(int adrReg)
{
  //��������� ���������� ��������
  int count_register = dtrbigcomponent->countObject*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg1(int adrReg)
int privateDTRBigGetReg2(int adrReg)
{
  //��������� ������� ��������
  int count_register = TOTAL_OBJ*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
