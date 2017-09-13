#include "header.h"

//��������� ������� � ����� ������
#define BEGIN_ADR_REGISTER 61948
//���� �-�� �������
#define REGISTER_FOR_OBJ 3

int privateRegProBigGetReg2(int adrReg);

int getRegProBigModbusRegister(int);//�������� ���������� ��������
int getRegProBigModbusBit(int);//�������� ���������� ����
int setRegProBigModbusRegister(int, int);//�������� ���������� ��������
int setRegProBigModbusBit(int, int);//�������� ���������� ����

void preRegProBigReadAction(void);//action �� ������
void postRegProBigReadAction(void);//action ����� ������
void preRegProBigWriteAction(void);//action �� ������
int  postRegProBigWriteAction(void);//action ����� ������

COMPONENT_OBJ *regprobigcomponent;

/**************************************/
//���������� ���������� ����������� pro
/**************************************/
void constructorRegProBigComponent(COMPONENT_OBJ *regprobigcomp)
{
  regprobigcomponent = regprobigcomp;

  regprobigcomponent->countObject = 1;//�-�� �������

  regprobigcomponent->getModbusRegister = getRegProBigModbusRegister;//�������� ���������� ��������
  regprobigcomponent->getModbusBit      = getRegProBigModbusBit;//�������� ���������� ����
  regprobigcomponent->setModbusRegister = setRegProBigModbusRegister;//�������� ���������� ��������
  regprobigcomponent->setModbusBit      = setRegProBigModbusBit;//�������� ���������� ����

  regprobigcomponent->preReadAction   = preRegProBigReadAction;//action �� ������
  regprobigcomponent->postReadAction  = postRegProBigReadAction;//action ����� ������
  regprobigcomponent->preWriteAction  = preRegProBigWriteAction;//action �� ������
  regprobigcomponent->postWriteAction = postRegProBigWriteAction;//action ����� ������

  regprobigcomponent->isActiveActualData = 0;
}//prepareDVinConfig

int getRegProBigModbusRegister(int adrReg)
{
  //�������� ���������� ��������
  if(privateRegProBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  superSetOperativMarker(regprobigcomponent, adrReg);

  int offsetRegister = adrReg-BEGIN_ADR_REGISTER;

  switch(offsetRegister)
    {
    case 0://������ ��������� ������ ����������
    case 1://�������� ����������� ����������� ������
      return MARKER_ERRORPERIMETR;
    case 2://����� ������ ��� �������;
      return info_rejestrator_pr_err.number_records;//number_record_of_pr_err_into_USB;
    }//switch
  return 0;
}//getDOUTBigModbusRegister(int adrReg)

int getRegProBigModbusBit(int x)
{
  //�������� ���������� ��������
  UNUSED(x);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setRegProBigModbusRegister(int adrReg, int dataReg)
{
  //�������� ���������� ��������
  if(privateRegProBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  superSetOperativMarker(regprobigcomponent, adrReg);
  superSetTempWriteArray(dataReg);//�������� � �����

  int offsetRegister = adrReg-BEGIN_ADR_REGISTER;

  switch(offsetRegister)
    {
    case 0://������ ��������� ������ ����������
    case 1://�������� ����������� ����������� ������
      return 0;
    }//switch

  return MARKER_ERRORPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setRegProBigModbusBit(int x, int y)
{
  UNUSED(x);
  UNUSED(y);
  //�������� ���������� ��������
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void preRegProBigReadAction(void)
{
//action �� ������
  regprobigcomponent->operativMarker[0] = -1;
  regprobigcomponent->operativMarker[1] = -1;//����������� ������
  regprobigcomponent->isActiveActualData = 1;
}//
void postRegProBigReadAction(void)
{
//action ����� ������
  if(regprobigcomponent->operativMarker[0]<0) return;//�� ���� ������
}//
void preRegProBigWriteAction(void)
{
//action �� ������
  regprobigcomponent->operativMarker[0] = -1;
  regprobigcomponent->operativMarker[1] = -1;//����������� ������
  regprobigcomponent->isActiveActualData = 1;
}//
int postRegProBigWriteAction(void)
{
extern int upravlYust;//���� ���������
//action ����� ������
  if(regprobigcomponent->operativMarker[0]<0) return 0;//�� ���� ������
  int offsetTempWriteArray = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//����� �������� TempWriteArray
  int countRegister = regprobigcomponent->operativMarker[1]-regprobigcomponent->operativMarker[0]+1;
  if(regprobigcomponent->operativMarker[1]<0) countRegister = 1;

  for(int i=0; i<countRegister; i++)
    {
      int offset = i+regprobigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;

      switch(offset)  //������ �������� �����
        {
        case 0://������ ��������� ������ ����������
          if(upravlYust!=0x1978) return 2;//���� ���������
          changed_ustuvannja = CHANGED_ETAP_EXECUTION;
          serial_number_dev = tempWriteArray[offsetTempWriteArray+i];//��������;
          changed_ustuvannja = CHANGED_ETAP_ENDED;
         _SET_BIT(control_i2c_taskes, TASK_START_WRITE_USTUVANNJA_EEPROM_BIT);
         return 0;
        case 1://�������� ����������� ����������� ������
        {
          if (
            (current_state_menu2.current_level == PR_ERR_LIST_MENU2_LEVEL) ||
            (current_state_menu2.current_level == PR_ERR_DATA_MENU2_LEVEL)
            ||
            (
              (control_tasks_dataflash & (
                 MASKA_FOR_BIT(TASK_WRITE_PR_ERR_RECORDS_INTO_DATAFLASH_BIT   ) |
                 MASKA_FOR_BIT(TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_USB_BIT  ) |
                 MASKA_FOR_BIT(TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_RS485_BIT) |
                 MASKA_FOR_BIT(TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_MENU_BIT )
               )
              ) != 0
            )
            ||
            ((clean_rejestrators & MASKA_FOR_BIT(CLEAN_PR_ERR_BIT)) != 0)
          )
            {
              //���������, �� �������� ��������� ����������
              return 2;//���� �� ������
            }
          else
            {
              clean_rejestrators |= (unsigned int)(MASKA_FOR_BIT(CLEAN_PR_ERR_BIT));
            }
        }
        break;
        default:
          return 2;//���� �� ������
        }//switch

    }//for
  return 0;
}//

int privateRegProBigGetReg2(int adrReg)
{
  //��������� ������� ��������
  int count_register = REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
