#include "header.h"

//начальный регистр в карте пам€ти
#define BEGIN_ADR_REGISTER 61949
//макс к-во обектов
#define REGISTER_FOR_OBJ 9

int privateRegProBigGetReg2(int adrReg);

int getRegProBigModbusRegister(int);//получить содержимое регистра
int getRegProBigModbusBit(int);//получить содержимое бита
int setRegProBigModbusRegister(int, int);//получить содержимое регистра
int setRegProBigModbusBit(int, int);//получить содержимое бита

void preRegProBigReadAction(void);//action до чтени€
void postRegProBigReadAction(void);//action после чтени€
void preRegProBigWriteAction(void);//action до записи
int  postRegProBigWriteAction(void);//action после записи

COMPONENT_OBJ *regprobigcomponent;

/**************************************/
//подготовка компонента регистратор pro
/**************************************/
void constructorRegProBigComponent(COMPONENT_OBJ *regprobigcomp)
{
  regprobigcomponent = regprobigcomp;

  regprobigcomponent->countObject = 1;//к-во обектов

  regprobigcomponent->getModbusRegister = getRegProBigModbusRegister;//получить содержимое регистра
  regprobigcomponent->getModbusBit      = getRegProBigModbusBit;//получить содержимое бита
  regprobigcomponent->setModbusRegister = setRegProBigModbusRegister;//получить содержимое регистра
  regprobigcomponent->setModbusBit      = setRegProBigModbusBit;//получить содержимое бита

  regprobigcomponent->preReadAction   = preRegProBigReadAction;//action до чтени€
  regprobigcomponent->postReadAction  = postRegProBigReadAction;//action после чтени€
  regprobigcomponent->preWriteAction  = preRegProBigWriteAction;//action до записи
  regprobigcomponent->postWriteAction = postRegProBigWriteAction;//action после записи

  regprobigcomponent->isActiveActualData = 0;
}//prepareDVinConfig

int getRegProBigModbusRegister(int adrReg)
{
  //получить содержимое регистра
  if(privateRegProBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  superSetOperativMarker(regprobigcomponent, adrReg);

  int offsetRegister = adrReg-BEGIN_ADR_REGISTER;

  uint32_t word = buffer_for_USB_read_record_log[8] | (buffer_for_USB_read_record_log[9] << 8);
  switch(offsetRegister)
    {
    case 0://ќчистить регистратор программных ошибок
      return MARKER_ERRORPERIMETR;
    case 1://номер запису дл€ читанн€;
      return number_record_of_pr_err_into_USB;
    case 2:// оличество событий в регистраторе программных ошибок
      return 0;//info_rejestrator_err.number_records;
    case 3://статус событи€
      return ((word >> 16) & 0x1);
    case 4://год мес€ц
      return ((buffer_for_USB_read_record_log[7] << 8) | buffer_for_USB_read_record_log[6]);
    case 5://день часы
      return ((buffer_for_USB_read_record_log[5] << 8) | buffer_for_USB_read_record_log[4]);
    case 6://минуты секунды
      return ((buffer_for_USB_read_record_log[3] << 8) | buffer_for_USB_read_record_log[2]);
    case 7://миллисекунды
      return ((buffer_for_USB_read_record_log[1] >> 4)*10 + (buffer_for_USB_read_record_log[1] &  0xf))*100;
    case 8://идентификатор объекта
      return (word & 0x7fff);
    }//switch
  return 0;
}//getDOUTBigModbusRegister(int adrReg)

int getRegProBigModbusBit(int x)
{
  //получить содержимое регистра
  UNUSED(x);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setRegProBigModbusRegister(int adrReg, int dataReg)
{
  //записать содержимое регистра
  if(privateRegProBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  superSetOperativMarker(regprobigcomponent, adrReg);
  superSetTempWriteArray(dataReg);//записать в буфер

  int offsetRegister = adrReg-BEGIN_ADR_REGISTER;

  switch(offsetRegister)
    {
    case 0://ќчистить регистратор программных ошибок
      return 0;
    case 1://номер запису дл€ читанн€;
      return 0;
    }//switch

  return MARKER_ERRORPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setRegProBigModbusBit(int x, int y)
{
  UNUSED(x);
  UNUSED(y);
  //получить содержимое регистра
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void preRegProBigReadAction(void)
{
//action до чтени€
  regprobigcomponent->operativMarker[0] = -1;
  regprobigcomponent->operativMarker[1] = -1;//оперативный маркер
  regprobigcomponent->isActiveActualData = 1;
}//
void postRegProBigReadAction(void)
{
//action после чтени€
  if(regprobigcomponent->operativMarker[0]<0) return;//не было чтени€
}//
void preRegProBigWriteAction(void)
{
//action до записи
  regprobigcomponent->operativMarker[0] = -1;
  regprobigcomponent->operativMarker[1] = -1;//оперативный маркер
  regprobigcomponent->isActiveActualData = 1;
}//
int postRegProBigWriteAction(void)
{
//action после записи
  if(regprobigcomponent->operativMarker[0]<0) return 0;//не было записи
  int offsetTempWriteArray = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//найти смещение TempWriteArray
  int countRegister = regprobigcomponent->operativMarker[1]-regprobigcomponent->operativMarker[0]+1;
  if(regprobigcomponent->operativMarker[1]<0) countRegister = 1;

  for(int i=0; i<countRegister; i++)
    {
      int offset = i+regprobigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;

      switch(offset)  //индекс регистра входа
        {
        case 0://ќчистить регистратор программных ошибок
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
              //ѕов≥домити, що операц≥€ тимчасово недоступна
              return 2;//уйти на ошибку
            }
          else
            {
              clean_rejestrators |= (unsigned int)(MASKA_FOR_BIT(CLEAN_PR_ERR_BIT));
            }
        }
        break;
        case 1://номер запису дл€ читанн€;
        {
          number_record_of_pr_err_into_USB = tempWriteArray[offsetTempWriteArray+i];
        }
        break;
        default:
          return 2;//уйти на ошибку
        }//switch

    }//for
  return 0;
}//

int privateRegProBigGetReg2(int adrReg)
{
  //проверить внешний периметр
  int count_register = REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
