//#include <QtWidgets>

#include "header.h"

//��������� ������� � ����� ������
#define BEGIN_ADR_REGISTER 600
//��������� bit � ����� ������
#define BEGIN_ADR_BIT  22000
#define REGISTER_FOR_OBJ 2
#define BIT_FOR_OBJ 18

int privateCommonSmallGetReg2(int adrReg);
int privateCommonSmallGetBit2(int adrBit);

int getCommonSmallModbusRegister(int);//�������� ���������� ��������
int getCommonSmallModbusBit(int);//�������� ���������� ����
int setCommonSmallModbusRegister(int, int);// ��������
int setCommonSmallModbusBit(int, int);// ����

void preCommonSmallReadAction(void);//action �� ������
void postCommonSmallReadAction(void);//action ����� ������
void preCommonSmallWriteAction(void);//action �� ������
int postCommonSmallWriteAction(void);//action ����� ������
void config_and_settingsCommonSmall(void);//action ���������
void loadCommonSmallActualData(void);

COMPONENT_OBJ *commonsmallcomponent;

/**************************************/
//���������� ���������� �����
/**************************************/
void constructorCommonSmallComponent(COMPONENT_OBJ *commonsmallcomp)
{
  commonsmallcomponent = commonsmallcomp;

  commonsmallcomponent->countObject = 1;//�-�� �������

  commonsmallcomponent->getModbusRegister = getCommonSmallModbusRegister;//�������� ���������� ��������
  commonsmallcomponent->getModbusBit      = getCommonSmallModbusBit;//�������� ���������� ����
  commonsmallcomponent->setModbusRegister = setCommonSmallModbusRegister;// ��������
  commonsmallcomponent->setModbusBit      = setCommonSmallModbusBit;// ����

  commonsmallcomponent->preReadAction   = preCommonSmallReadAction;//action �� ������
  commonsmallcomponent->postReadAction  = postCommonSmallReadAction;//action ����� ������
  commonsmallcomponent->preWriteAction  = preCommonSmallWriteAction;//action �� ������
  commonsmallcomponent->postWriteAction = postCommonSmallWriteAction;//action ����� ������
  commonsmallcomponent->config_and_settings = config_and_settingsCommonSmall;//action ���������

  commonsmallcomponent->isActiveActualData = 0;
}//prepareDVinConfig

void loadCommonSmallActualData(void)
{
  //ActualData
  for(int i=0; i<2; i++) tempReadArray[i] = 0;
  for(int bit=0; bit<18; bit++)
    {

      switch(bit)
        {
        case 0://Run
//          if() 
//                              tempReadArray[0] |= (1<<bit);
          break;
        case 1://������������� �����
          if(fix_block_active_state[FIX_BLOCK_DEFECT >> 3] & (1 << (FIX_BLOCK_DEFECT & ((1 << 3) - 1)))) 
                              tempReadArray[0] |= (1<<bit);
          break;
        case 2://������������� ���������
          if(fix_block_active_state[FIX_BLOCK_AVAR_DEFECT >> 3] & (1 << (FIX_BLOCK_AVAR_DEFECT & ((1 << 3) - 1))))
                              tempReadArray[0] |= (1<<bit);
          break;
        case 3://������ ������ ��� �����
          if(fix_block_active_state[FIX_BLOCK_SCHEME_INCORRECT >> 3 ] & (1 << (FIX_BLOCK_SCHEME_INCORRECT & ((1 << 3) - 1))))
                              tempReadArray[0] |= (1<<bit);
          break;
        case 4://������ ������ ���������
          if(fix_block_active_state[FIX_BLOCK_D_TRIGGER_STATE_INCORRECT >> 3 ] & (1 << (FIX_BLOCK_D_TRIGGER_STATE_INCORRECT & ((1 << 3) - 1))))
                              tempReadArray[0] |= (1<<bit);
          break;
        case 5://��������� ������������
          if(fix_block_active_state[FIX_BLOCK_SETTINGS_CHANGED >> 8] & (1 << (FIX_BLOCK_SETTINGS_CHANGED & ((1 << 3) - 1))))
                              tempReadArray[0] |= (1<<bit);
          break;
        case 6://������ ���������� - �� ��� �� ���� �������
          if(fix_block_active_state[0] & 0x1)
                              tempReadArray[0] |= (1<<bit);
          break;
        case 7://������ �������
          {
          
          __LOG_INPUT *arr = (__LOG_INPUT*)(spca_of_p_prt[ID_FB_EVENT_LOG - _ID_FB_FIRST_VAR]);
          int value = arr[0] & (1 << (EVENT_LOG_WORK & ((1 << 5) - 1)));
          
          if (value) tempReadArray[0] |= (1<<bit);
          break;
          }
        case 8://������ ������������ - ����
                              tempReadArray[0] |= 0;//(1<<bit);
          break;
        case 9://����� ����������������
          tempReadArray[0] |= 0;
          break;
        case 10://���� ���������� �������\������������� -����
                              tempReadArray[0] |= 0;//(1<<bit);
          break;
        case 11://�������
        case 12://�������
        case 13://�������
        case 14://�������
          tempReadArray[0] |= 0;
          break;
        case 15://�������� ������ �������
        //  tempReadArray[0] |= 0;
          break;
        case 16://��������� ������������ (�������)
          break;
        case 17://����� ����� - ������ ����, ���� ���� ����� ���� ��������
          break;
        default:
          ;
        }//switch

    }//for
}//loadActualData()

int getCommonSmallModbusRegister(int adrReg)
{
  //�������� ���������� ��������
  if(privateCommonSmallGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  if(commonsmallcomponent->isActiveActualData) loadCommonSmallActualData(); //ActualData
  commonsmallcomponent->isActiveActualData = 0;

  superSetOperativMarker(commonsmallcomponent, adrReg);

  if((adrReg-BEGIN_ADR_REGISTER)==1) return MARKER_ERRORPERIMETR;//�������� 1 ������ ������

  return tempReadArray[adrReg-BEGIN_ADR_REGISTER];
}//getDVModbusRegister(int adrReg)
int getCommonSmallModbusBit(int adrBit)
{
  //�������� ���������� bit
  if(privateCommonSmallGetBit2(adrBit)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  if(commonsmallcomponent->isActiveActualData) loadCommonSmallActualData();
  commonsmallcomponent->isActiveActualData = 0;

  superSetOperativMarker(commonsmallcomponent, adrBit);
  switch(adrBit-BEGIN_ADR_BIT)
  {
   case 15:
   case 16:
   case 17:
   return MARKER_ERRORPERIMETR;//��������  ������ ������
  }//switch

  short tmp   = tempReadArray[(adrBit-BEGIN_ADR_BIT)/16];
  short maska = 1<<((adrBit-BEGIN_ADR_BIT)%16);
  if(tmp&maska) return 1;
  return 0;
}//getDVModbusRegister(int adrReg)
int setCommonSmallModbusRegister(int adrReg, int dataReg)
{
  extern int upravlFlag;//���� ������� ���������� 1-���� ����������
  //�������� ���������� ��������
  if(privateCommonSmallGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  superSetOperativMarker(commonsmallcomponent, adrReg);
  superSetTempWriteArray(dataReg&0x3);//�������� � �����

  switch(adrReg-BEGIN_ADR_REGISTER)
    {
    case 0:
      return MARKER_ERRORPERIMETR;
    case 1:
   break; 
   default: return MARKER_OUTPERIMETR;
    }//switch
  return 0;
}//getDVModbusRegister(int adrReg)
int setCommonSmallModbusBit(int adrBit, int dataBit)
{
  extern int upravlFlag;//���� ������� ���������� 1-���� ����������
  //�������� ���������� bit
  if(privateCommonSmallGetBit2(adrBit)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  superSetOperativMarker(commonsmallcomponent, adrBit);
  superSetTempWriteArray(dataBit);//�������� � �����

  switch(adrBit-BEGIN_ADR_BIT)
    {
    case 15://�������� ������ �������
      upravlFlag=1;//���� ������� ���������� 1-���� ����������
      return dataBit;
    case 16://��������� ������������
      upravlFlag=1;//���� ������� ���������� 1-���� ����������
      return dataBit;
    case 17://
      upravlFlag=1;//���� ������� ���������� 1-���� ����������
      return dataBit;
    }//switch
  return MARKER_ERRORPERIMETR;
}//setCommonSmallModbusBit(int adrBit, int adrData)

void preCommonSmallReadAction(void)
{
//action �� ������
  commonsmallcomponent->operativMarker[0] = -1;
  commonsmallcomponent->operativMarker[1] = -1;
  commonsmallcomponent->isActiveActualData = 1;//����������� ������
}//
void postCommonSmallReadAction(void)
{
//action ����� ������
  if(commonsmallcomponent->operativMarker[0]<0) return;//�� ���� ������
}//
void preCommonSmallWriteAction(void)
{
//action �� ������
  commonsmallcomponent->operativMarker[0] = -1;
  commonsmallcomponent->operativMarker[1] = -1;//����������� ������
  commonsmallcomponent->isActiveActualData = 1;
}//
int postCommonSmallWriteAction(void)
{
//action ����� ������
extern int globalResetFlag;//���� ����������� ������
  if(commonsmallcomponent->operativMarker[0]<0) return 0;//�� ���� ������
  switch(commonsmallcomponent->operativMarker[0])
    {
    case (BEGIN_ADR_REGISTER+1):
    {
      //������ ������� ��������
      switch(tempWriteArray[0]&3)
        {
        case 1://��������� ������������
          //qDebug()<<"1111111111111111111111";
//          fix_block_active_state[0] &= ~0x1;//��������� ����
//          fix_block_active_state[0] |= tempWriteArray[0]&1;
          break;
        case 2://����� �����
          //qDebug()<<"2222222222222222222222222";
//          fix_block_active_state[0] &= ~0x2;//��������� ����
//          fix_block_active_state[0] |= tempWriteArray[0]&2;
          break;
        case 3://��������� ������������
          //����� �����
          break;
        }//switch
    }//case (BEGIN_ADR_REGISTER+1):
    break;

    case (BEGIN_ADR_BIT+15):
    {
     //�������� ������ �������
  if (
    (current_state_menu2.current_level == LOG_LIST_MENU2_LEVEL) ||
    (current_state_menu2.current_level == LOG_DATA_MENU2_LEVEL)
    ||  
    (
     (control_tasks_dataflash & (
                                 MASKA_FOR_BIT(TASK_WRITE_LOG_RECORDS_INTO_DATAFLASH_BIT   ) |
                                 MASKA_FOR_BIT(TASK_MAMORY_READ_DATAFLASH_FOR_LOG_USB_BIT  ) |
                                 MASKA_FOR_BIT(TASK_MAMORY_READ_DATAFLASH_FOR_LOG_RS485_BIT) |
                                 MASKA_FOR_BIT(TASK_MAMORY_READ_DATAFLASH_FOR_LOG_MENU_BIT )
                                )
     ) != 0
    )
    ||
    ((clean_rejestrators & MASKA_FOR_BIT(CLEAN_LOG_BIT)) != 0)
   )
{
return 3;
	//���������, �� �������� ��������� ����������
}
else
{
    clean_rejestrators |= (unsigned int)(MASKA_FOR_BIT(CLEAN_LOG_BIT));
}
  }//case (BEGIN_ADR_REGISTER+1):
    break;
    case (BEGIN_ADR_BIT+16):
    {
  extern int pointInterface;
  if(pointInterface==0) {//����� ���������� 0-USB 1-RS485
if(tempWriteArray[0]==1) {
       superConfig_and_settings();//������������ ���������
       set_config_and_settings(1, USB_PARAMS_FIX_CHANGES);//����� �-��� 5
      }
if(tempWriteArray[0]==0) 
       set_config_and_settings(0, USB_PARAMS_FIX_CHANGES);//����� �-��� 5
}//if
  if(pointInterface==1) {//����� ���������� 0-USB 1-RS485
if(tempWriteArray[0]==1) {
       superConfig_and_settings();//������������ ���������
       set_config_and_settings(1, RS485_PARAMS_FIX_CHANGES);//����� �-��� 5
    }//if
if(tempWriteArray[0]==0) 
       set_config_and_settings(0, RS485_PARAMS_FIX_CHANGES);//����� �-��� 5
}//if
    }//case (BEGIN_ADR_REGISTER+1):
    break;
    case (BEGIN_ADR_BIT+17):
    {
      //����� �����
      globalResetFlag=1;//���� ����������� ������
    }//case (BEGIN_ADR_REGISTER+1):
    break;
    }//switch
  if(commonsmallcomponent->operativMarker[1]<0) return 0;//�� ���� ������
  switch(commonsmallcomponent->operativMarker[1])
    {
    case (BEGIN_ADR_BIT+17):
    {
      //����� �����
      fix_block_active_state[0] &= ~0x2;//��������� ����
      fix_block_active_state[0] |= tempWriteArray[1]&1;
    }//case (BEGIN_ADR_REGISTER+1):
    break;
    }//switch
 return 0;
}//

int privateCommonSmallGetReg2(int adrReg)
{
  //��������� ������� ��������
  int count_register = REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
int privateCommonSmallGetBit2(int adrBit)
{
  //��������� ������� ��������
  int count_bit = BIT_FOR_OBJ;
  if(adrBit>=BEGIN_ADR_BIT && adrBit<(BEGIN_ADR_BIT+count_bit)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)

void config_and_settingsCommonSmall(void)
{
//action ���������
}

