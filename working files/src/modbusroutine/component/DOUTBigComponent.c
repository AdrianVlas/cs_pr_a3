//#include <QtWidgets>
#include "header.h"

//��������� ������� � ����� ������
#define BEGIN_ADR_REGISTER 1156
//���� �-�� �������
#define TOTAL_OBJ 128
#define REGISTER_FOR_OBJ 13
int privateDOUTBigGetReg1(int adrReg);
int privateDOUTBigGetReg2(int adrReg);

int getDOUTBigModbusRegister(int);//�������� ���������� ��������
int getDOUTBigModbusBit(int);//�������� ���������� ����
int setDOUTBigModbusRegister(int, int);// ��������
int setDOUTBigModbusBit(int, int);// ����

void setDOUTBigCountObject(void);//�������� �-�� �������
void preDOUTBigReadAction(void);//action �� ������
void postDOUTBigReadAction(void);//action ����� ������
void preDOUTBigWriteAction(void);//action �� ������
int postDOUTBigWriteAction(void);//action ����� ������
//void loadDOUTBigActualData(void);

COMPONENT_OBJ *doutbigcomponent;

/**************************************/
//���������� ���������� ��
/**************************************/
void constructorDOUTBigComponent(COMPONENT_OBJ *doutcomp)
{
  doutbigcomponent = doutcomp;
  doutbigcomponent->countObject = 0;//�-�� �������

  doutbigcomponent->getModbusRegister = getDOUTBigModbusRegister;//�������� ���������� ��������
  doutbigcomponent->getModbusBit      = getDOUTBigModbusBit;//�������� ���������� ����
  doutbigcomponent->setModbusRegister = setDOUTBigModbusRegister;// ��������
  doutbigcomponent->setModbusBit      = setDOUTBigModbusBit;// ����

  doutbigcomponent->preReadAction   = preDOUTBigReadAction;//action �� ������
  doutbigcomponent->postReadAction  = postDOUTBigReadAction;//action ����� ������
  doutbigcomponent->preWriteAction  = preDOUTBigWriteAction;//action �� ������
  doutbigcomponent->postWriteAction = postDOUTBigWriteAction;//action ����� ������

  doutbigcomponent->isActiveActualData = 0;
}//prepareDVinConfig

/*
void loadDOUTBigActualData(void) {
 setDOUTBigCountObject(); //�������� �-�� �������

  //ActualData
  __LN_OUTPUT_LED *arr = (__LN_OUTPUT_LED*)(spca_of_p_prt[ID_FB_OUTPUT - _ID_FB_FIRST_VAR]);
   for(int item=0; item<doutbigcomponent->countObject; item++) {
   int value = arr[item].settings.control;//��������� ����. item
   tempReadArray[item*REGISTER_FOR_OBJ+0] = value;

   value = arr[item].settings.param[OUTPUT_LED_LOGIC_INPUT] & 0xffff;//RIN0 ����. item
   tempReadArray[item*REGISTER_FOR_OBJ+1] = value;
   value = (arr[item].settings.param[OUTPUT_LED_LOGIC_INPUT] >> 16) & 0x7fff;//RIN1 ����. item
   tempReadArray[item*REGISTER_FOR_OBJ+2] = value;

   value = arr[item].settings.param[OUTPUT_LED_RESET] & 0xffff;//Reset0 ����. item
   tempReadArray[item*REGISTER_FOR_OBJ+3] = value;
   value = (arr[item].settings.param[OUTPUT_LED_RESET] >> 16) & 0x7fff;//Reset1 ����. item
   tempReadArray[item*REGISTER_FOR_OBJ+4] = value;

   value = arr[item].settings.param[OUTPUT_LED_BL_IMP] & 0xffff;//BL-IMP0 ����. item
   tempReadArray[item*REGISTER_FOR_OBJ+5] = value;
   value = (arr[item].settings.param[OUTPUT_LED_BL_IMP] >> 16) & 0x7fff;//BL-IMP1 ����. item
   tempReadArray[item*REGISTER_FOR_OBJ+6] = value;

   value = arr[item].settings.param[OUTPUT_LED_MEANDER1_MEANDER2] & 0xffff;//C1/C2 0 ����. item
   tempReadArray[item*REGISTER_FOR_OBJ+7] = value;
   value = (arr[item].settings.param[OUTPUT_LED_MEANDER1_MEANDER2] >> 16) & 0x7fff;//C1/C2 1 ���� item
   tempReadArray[item*REGISTER_FOR_OBJ+8] = value;

   value = arr[item].settings.param[OUTPUT_LED_MEANDER1] & 0xffff;//��������� �1 0 ���.���� item
   tempReadArray[item*REGISTER_FOR_OBJ+9] = value;
   value = (arr[item].settings.param[OUTPUT_LED_MEANDER1] >> 16) & 0x7fff;//��������� �1 1 ���.���� item
   tempReadArray[item*REGISTER_FOR_OBJ+10] = value;

   value = arr[item].settings.param[OUTPUT_LED_MEANDER2] & 0xffff;//��������� �2 0 ���.���� item
   tempReadArray[item*REGISTER_FOR_OBJ+11] = value;
   value = (arr[item].settings.param[OUTPUT_LED_MEANDER2] >> 16) & 0x7fff;//��������� �2 1 ���.����. item
   tempReadArray[item*REGISTER_FOR_OBJ+12] = value;
  }//for
*/
  /*
  ...
  
  �� ����� "��������� C1" � "��������� C2" ����� ���������� ����� ����������, ����� id ������ ���������� ID_FB_MEANDER, n �� ���� ������������ ������� ���������� � ������������, out ������ ���������� 1, �� � ���������� � ������ �����
  */
//}//loadActualData() 

int getDOUTBigModbusRegister(int adrReg)
{
  //�������� ���������� ��������
  if(privateDOUTBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(doutbigcomponent->isActiveActualData)// loadDOUTBigActualData(); //ActualData
                                           setDOUTBigCountObject(); //�������� �-�� �������
  doutbigcomponent->isActiveActualData = 0;
  if(privateDOUTBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;//MARKER_ERRORPERIMETR;

  superSetOperativMarker(doutbigcomponent, adrReg);

  __LN_OUTPUT_LED *arr = (__LN_OUTPUT_LED*)(spca_of_p_prt[ID_FB_OUTPUT - _ID_FB_FIRST_VAR]);
//  int offset = i+doutbigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;
  int offset = adrReg-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//������ ����������
  switch(offset%REGISTER_FOR_OBJ) {//������ �������� 
   case 0://��������� ����. item
    return arr[idxSubObj].settings.control;// = (tempWriteArray[offsetTempWriteArray+i]);
   //break;

   case 1://RIN 0 ����. item
        //arr1[idxSubObj].param[OUTPUT_LED_LOGIC_INPUT] = 
         return arr[idxSubObj].settings.param[OUTPUT_LED_LOGIC_INPUT] & 0xffff;// &= (uint32_t)~0xffff;
        //arr1[idxSubObj].param[OUTPUT_LED_LOGIC_INPUT] = arr[idxSubObj].param[OUTPUT_LED_LOGIC_INPUT] |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
//   break;
   case 2://RIN 1 ����. item
        return (arr[idxSubObj].settings.param[OUTPUT_LED_LOGIC_INPUT]  >> 16) & 0x7fff;// &= (uint32_t)~(0x7fff<<16);
//        arr[idxSubObj].param[OUTPUT_LED_LOGIC_INPUT] |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
//   break; 

   case 3://Reset 0 ����. item
        //arr1[idxSubObj].param[OUTPUT_LED_RESET] = 
        return arr[idxSubObj].settings.param[OUTPUT_LED_RESET] & 0xffff;// &= (uint32_t)~0xffff;
//        arr1[idxSubObj].param[OUTPUT_LED_RESET] = arr[idxSubObj].param[OUTPUT_LED_RESET] |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
  // break;
   case 4://Reset 1 ����. item
        //arr1[idxSubObj].param[OUTPUT_LED_RESET] = 
        return (arr[idxSubObj].settings.param[OUTPUT_LED_RESET]  >> 16) & 0x7fff;// &= (uint32_t)~(0x7fff<<16);
//        arr1[idxSubObj].param[OUTPUT_LED_RESET] = arr[idxSubObj].param[OUTPUT_LED_RESET] |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
//   break; 

   case 5://BL-IMP 0 ����. item
        //arr1[idxSubObj].param[OUTPUT_LED_BL_IMP] = 
        return arr[idxSubObj].settings.param[OUTPUT_LED_BL_IMP] & 0xffff;// &= (uint32_t)~0xffff;
//        arr1[idxSubObj].param[OUTPUT_LED_BL_IMP] = arr[idxSubObj].param[OUTPUT_LED_BL_IMP] |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
//   break;
   case 6://BL-IMP 1 ����. item
//        arr1[idxSubObj].param[OUTPUT_LED_BL_IMP] = 
        return (arr[idxSubObj].settings.param[OUTPUT_LED_BL_IMP]  >> 16) & 0x7fff;// &= (uint32_t)~(0x7fff<<16);
//        arr1[idxSubObj].param[OUTPUT_LED_BL_IMP] = arr[idxSubObj].param[OUTPUT_LED_BL_IMP] |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
//   break; 

   case 7://C1/C2 0 ����. item
//        arr1[idxSubObj].param[OUTPUT_LED_MEANDER1_MEANDER2] = 
        return arr[idxSubObj].settings.param[OUTPUT_LED_MEANDER1_MEANDER2] & 0xffff;// &= (uint32_t)~0xffff;
//        arr1[idxSubObj].param[OUTPUT_LED_MEANDER1_MEANDER2] = arr[idxSubObj].param[OUTPUT_LED_MEANDER1_MEANDER2] |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
  // break;
   case 8://C1/C2 1 ����. item
        //arr1[idxSubObj].param[OUTPUT_LED_MEANDER1_MEANDER2] = 
        return (arr[idxSubObj].settings.param[OUTPUT_LED_MEANDER1_MEANDER2]  >> 16) & 0x7fff;// &= (uint32_t)~(0x7fff<<16);
//        arr1[idxSubObj].param[OUTPUT_LED_MEANDER1_MEANDER2] = arr[idxSubObj].param[OUTPUT_LED_MEANDER1_MEANDER2] |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
//   break; 

   case 9://��������� �1 0 ����. item
        //arr1[idxSubObj].param[OUTPUT_LED_MEANDER1] = 
        return arr[idxSubObj].settings.param[OUTPUT_LED_MEANDER1] & 0xffff;// &= (uint32_t)~0xffff;
 //       arr1[idxSubObj].param[OUTPUT_LED_MEANDER1] = arr[idxSubObj].param[OUTPUT_LED_MEANDER1] |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
 //  break;
   case 10://��������� �1 1 ����. item
        //arr1[idxSubObj].param[OUTPUT_LED_MEANDER1] = 
        return (arr[idxSubObj].settings.param[OUTPUT_LED_MEANDER1]  >> 16) & 0x7fff;// &= (uint32_t)~(0x7fff<<16);
//        arr1[idxSubObj].param[OUTPUT_LED_MEANDER1] = arr[idxSubObj].param[OUTPUT_LED_MEANDER1] |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
//   break; 

   case 11://��������� �2 0 ����. item
        //arr1[idxSubObj].param[OUTPUT_LED_MEANDER2] = 
        return arr[idxSubObj].settings.param[OUTPUT_LED_MEANDER2] & 0xffff;// &= (uint32_t)~0xffff;
//        arr1[idxSubObj].param[OUTPUT_LED_MEANDER2] = arr[idxSubObj].param[OUTPUT_LED_MEANDER2] |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
//   break;
   case 12://��������� �2 1 ����. item
        //arr1[idxSubObj].param[OUTPUT_LED_MEANDER2] = 
        return (arr[idxSubObj].settings.param[OUTPUT_LED_MEANDER2]  >> 16) & 0x7fff;// &= (uint32_t)~(0x7fff<<16);
//        arr1[idxSubObj].param[OUTPUT_LED_MEANDER2] = arr[idxSubObj].param[OUTPUT_LED_MEANDER2] |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
  // break; 
 }//switch


  return 0;//tempReadArray[adrReg-BEGIN_ADR_REGISTER];
}//getDOUTBigModbusRegister(int adrReg)
int getDOUTBigModbusBit(int adrBit)
{
  //�������� ���������� ��������
  superSetOperativMarker(doutbigcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setDOUTBigModbusRegister(int adrReg, int dataReg)
{
  //�������� ���������� ��������
  if(privateDOUTBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(doutbigcomponent->isActiveActualData) setDOUTBigCountObject(); //�-�� �������
  doutbigcomponent->isActiveActualData = 0;
  if(privateDOUTBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;//MARKER_ERRORPERIMETR;

  superSetOperativMarker(doutbigcomponent, adrReg);
  superSetTempWriteArray(dataReg);//�������� � �����

  switch((adrReg-BEGIN_ADR_REGISTER)%REGISTER_FOR_OBJ) {
   case 0:
   break; 
   case 1:
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
   break; 
   case 2:
    //�������� ���������� ������������
    if(superControlParam(dataReg)) return MARKER_ERRORDIAPAZON;
   break; 
   case 3:
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
   break; 
   case 4:
    //�������� ���������� ������������
    if(superControlParam(dataReg)) return MARKER_ERRORDIAPAZON;
   break; 
   case 5:
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
   break; 
   case 6:
    //�������� ���������� ������������
    if(superControlParam(dataReg)) return MARKER_ERRORDIAPAZON;
   break; 
   case 7:
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
   break; 
   case 8:
    //�������� ���������� ������������
    if(superControlParam(dataReg)) return MARKER_ERRORDIAPAZON;
   break; 
   case 9:
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
   break; 
   case 10:
    //�������� ���������� ������������
    if(superControlParam(dataReg)) return MARKER_ERRORDIAPAZON;
   break; 
   case 11:
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
   break; 
   case 12:
    //�������� ���������� ������������
    if(superControlParam(dataReg)) return MARKER_ERRORDIAPAZON;
   break; 
  default: return MARKER_OUTPERIMETR;
  }//switch
  return 0;
}//getDOUTBigModbusRegister(int adrReg)
int setDOUTBigModbusBit(int adrReg, int x)
{
  UNUSED(x);
  //�������� ���������� ��������
  superSetOperativMarker(doutbigcomponent, adrReg);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void setDOUTBigCountObject(void) {
//�������� �-�� �������
  int cntObj = current_config.n_output; //ʳ������ ���������� ������
  if(cntObj<0) return;
  if(cntObj>TOTAL_OBJ) return;
  doutbigcomponent->countObject = cntObj;
}//
void preDOUTBigReadAction(void) {
//action �� ������
  doutbigcomponent->operativMarker[0] = -1;
  doutbigcomponent->operativMarker[1] = -1;//����������� ������
  doutbigcomponent->isActiveActualData = 1;
}//
void postDOUTBigReadAction(void) {
//action ����� ������
  if(doutbigcomponent->operativMarker[0]<0) return;//�� ���� ������
}//
void preDOUTBigWriteAction(void) {
//action �� ������
  doutbigcomponent->operativMarker[0] = -1;
  doutbigcomponent->operativMarker[1] = -1;//����������� ������
  doutbigcomponent->isActiveActualData = 1;
}//
int postDOUTBigWriteAction(void) {
//action ����� ������
  if(doutbigcomponent->operativMarker[0]<0) return 0;//�� ���� ������
  int offsetTempWriteArray = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//����� �������� TempWriteArray
  int countRegister = doutbigcomponent->operativMarker[1]-doutbigcomponent->operativMarker[0]+1;
  if(doutbigcomponent->operativMarker[1]<0) countRegister = 1;

   __settings_for_OUTPUT_LED *arr  = (__settings_for_OUTPUT_LED*)(sca_of_p[ID_FB_OUTPUT - _ID_FB_FIRST_VAR]);
   __settings_for_OUTPUT_LED *arr1 = (__settings_for_OUTPUT_LED*)(sca_of_p_edit[ID_FB_OUTPUT - _ID_FB_FIRST_VAR]);
  for(int i=0; i<countRegister; i++) {
  int offset = i+doutbigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//������ ����������
  switch(offset%REGISTER_FOR_OBJ) {//������ �������� 
   case 0://��������� ����. item
    arr[idxSubObj].control = (tempWriteArray[offsetTempWriteArray+i]);
   break;

   case 1://RIN 0 ����. item
        arr1[idxSubObj].param[OUTPUT_LED_LOGIC_INPUT] = arr[idxSubObj].param[OUTPUT_LED_LOGIC_INPUT] &= (uint32_t)~0xffff;
        arr1[idxSubObj].param[OUTPUT_LED_LOGIC_INPUT] = arr[idxSubObj].param[OUTPUT_LED_LOGIC_INPUT] |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
   break;
   case 2://RIN 1 ����. item
        arr1[idxSubObj].param[OUTPUT_LED_LOGIC_INPUT] = arr[idxSubObj].param[OUTPUT_LED_LOGIC_INPUT] &= (uint32_t)~(0x7fff<<16);
        arr1[idxSubObj].param[OUTPUT_LED_LOGIC_INPUT] = arr[idxSubObj].param[OUTPUT_LED_LOGIC_INPUT] |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
   break; 

   case 3://Reset 0 ����. item
        arr1[idxSubObj].param[OUTPUT_LED_RESET] = arr[idxSubObj].param[OUTPUT_LED_RESET] &= (uint32_t)~0xffff;
        arr1[idxSubObj].param[OUTPUT_LED_RESET] = arr[idxSubObj].param[OUTPUT_LED_RESET] |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
   break;
   case 4://Reset 1 ����. item
        arr1[idxSubObj].param[OUTPUT_LED_RESET] = arr[idxSubObj].param[OUTPUT_LED_RESET] &= (uint32_t)~(0x7fff<<16);
        arr1[idxSubObj].param[OUTPUT_LED_RESET] = arr[idxSubObj].param[OUTPUT_LED_RESET] |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
   break; 

   case 5://BL-IMP 0 ����. item
        arr1[idxSubObj].param[OUTPUT_LED_BL_IMP] = arr[idxSubObj].param[OUTPUT_LED_BL_IMP] &= (uint32_t)~0xffff;
        arr1[idxSubObj].param[OUTPUT_LED_BL_IMP] = arr[idxSubObj].param[OUTPUT_LED_BL_IMP] |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
   break;
   case 6://BL-IMP 1 ����. item
        arr1[idxSubObj].param[OUTPUT_LED_BL_IMP] = arr[idxSubObj].param[OUTPUT_LED_BL_IMP] &= (uint32_t)~(0x7fff<<16);
        arr1[idxSubObj].param[OUTPUT_LED_BL_IMP] = arr[idxSubObj].param[OUTPUT_LED_BL_IMP] |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
   break; 

   case 7://C1/C2 0 ����. item
        arr1[idxSubObj].param[OUTPUT_LED_MEANDER1_MEANDER2] = arr[idxSubObj].param[OUTPUT_LED_MEANDER1_MEANDER2] &= (uint32_t)~0xffff;
        arr1[idxSubObj].param[OUTPUT_LED_MEANDER1_MEANDER2] = arr[idxSubObj].param[OUTPUT_LED_MEANDER1_MEANDER2] |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
   break;
   case 8://C1/C2 1 ����. item
        arr1[idxSubObj].param[OUTPUT_LED_MEANDER1_MEANDER2] = arr[idxSubObj].param[OUTPUT_LED_MEANDER1_MEANDER2] &= (uint32_t)~(0x7fff<<16);
        arr1[idxSubObj].param[OUTPUT_LED_MEANDER1_MEANDER2] = arr[idxSubObj].param[OUTPUT_LED_MEANDER1_MEANDER2] |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
   break; 

   case 9://��������� �1 0 ����. item
        arr1[idxSubObj].param[OUTPUT_LED_MEANDER1] = arr[idxSubObj].param[OUTPUT_LED_MEANDER1] &= (uint32_t)~0xffff;
        arr1[idxSubObj].param[OUTPUT_LED_MEANDER1] = arr[idxSubObj].param[OUTPUT_LED_MEANDER1] |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
   break;
   case 10://��������� �1 1 ����. item
        arr1[idxSubObj].param[OUTPUT_LED_MEANDER1] = arr[idxSubObj].param[OUTPUT_LED_MEANDER1] &= (uint32_t)~(0x7fff<<16);
        arr1[idxSubObj].param[OUTPUT_LED_MEANDER1] = arr[idxSubObj].param[OUTPUT_LED_MEANDER1] |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
   break; 

   case 11://��������� �2 0 ����. item
        arr1[idxSubObj].param[OUTPUT_LED_MEANDER2] = arr[idxSubObj].param[OUTPUT_LED_MEANDER2] &= (uint32_t)~0xffff;
        arr1[idxSubObj].param[OUTPUT_LED_MEANDER2] = arr[idxSubObj].param[OUTPUT_LED_MEANDER2] |= (tempWriteArray[offsetTempWriteArray+i] & 0xffff);
   break;
   case 12://��������� �2 1 ����. item
        arr1[idxSubObj].param[OUTPUT_LED_MEANDER2] = arr[idxSubObj].param[OUTPUT_LED_MEANDER2] &= (uint32_t)~(0x7fff<<16);
        arr1[idxSubObj].param[OUTPUT_LED_MEANDER2] = arr[idxSubObj].param[OUTPUT_LED_MEANDER2] |= ((tempWriteArray[offsetTempWriteArray+i] & 0x7fff)<<16);//
   break; 
 }//switch
  }//for
  config_settings_modified |= MASKA_FOR_BIT(BIT_CHANGED_SETTINGS);
  restart_timeout_idle_new_settings = true;
 return 0;
}//

int privateDOUTBigGetReg1(int adrReg)
{
  //��������� ���������� ��������
  int count_register = doutbigcomponent->countObject*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg1(int adrReg)
int privateDOUTBigGetReg2(int adrReg)
{
  //��������� ������� ��������
  int count_register = TOTAL_OBJ*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
