//#include <QtWidgets>

#include "header.h"

//начальный регистр в карте памяти
#define BEGIN_ADR_REGISTER 600
//начальный bit в карте памяти
#define BEGIN_ADR_BIT  22000
#define REGISTER_FOR_OBJ 2
#define BIT_FOR_OBJ 18

int privateCommonSmallGetReg2(int adrReg);
int privateCommonSmallGetBit2(int adrBit);

int getCommonSmallModbusRegister(int);//получить содержимое регистра
int getCommonSmallModbusBit(int);//получить содержимое бита
int setCommonSmallModbusRegister(int, int);// регистра
int setCommonSmallModbusBit(int, int);// бита

void preCommonSmallReadAction(void);//action до чтения
void postCommonSmallReadAction(void);//action после чтения
void preCommonSmallWriteAction(void);//action до записи
int postCommonSmallWriteAction(void);//action после записи
void config_and_settingsCommonSmall(void);//action активации
void loadCommonSmallActualData(void);

COMPONENT_OBJ *commonsmallcomponent;

/**************************************/
//подготовка компонента Общие
/**************************************/
void constructorCommonSmallComponent(COMPONENT_OBJ *commonsmallcomp)
{
  commonsmallcomponent = commonsmallcomp;

  commonsmallcomponent->countObject = 1;//к-во обектов

  commonsmallcomponent->getModbusRegister = getCommonSmallModbusRegister;//получить содержимое регистра
  commonsmallcomponent->getModbusBit      = getCommonSmallModbusBit;//получить содержимое бита
  commonsmallcomponent->setModbusRegister = setCommonSmallModbusRegister;// регистра
  commonsmallcomponent->setModbusBit      = setCommonSmallModbusBit;// бита

  commonsmallcomponent->preReadAction   = preCommonSmallReadAction;//action до чтения
  commonsmallcomponent->postReadAction  = postCommonSmallReadAction;//action после чтения
  commonsmallcomponent->preWriteAction  = preCommonSmallWriteAction;//action до записи
  commonsmallcomponent->postWriteAction = postCommonSmallWriteAction;//action после записи
  commonsmallcomponent->config_and_settings = config_and_settingsCommonSmall;//action активации

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
          if(fix_block_active_state[FIX_BLOCK_RUN >> 3] & (1 << (FIX_BLOCK_RUN & ((1 << 3) - 1))))
            tempReadArray[0] |= (1<<bit);
          break;
        case 1://Неисправность общая
          if(fix_block_active_state[FIX_BLOCK_DEFECT >> 3] & (1 << (FIX_BLOCK_DEFECT & ((1 << 3) - 1))))
            tempReadArray[0] |= (1<<bit);
          break;
        case 2://Неисправность аварийная
          if(fix_block_active_state[FIX_BLOCK_AVAR_DEFECT >> 3] & (1 << (FIX_BLOCK_AVAR_DEFECT & ((1 << 3) - 1))))
            tempReadArray[0] |= (1<<bit);
          break;
        case 3://Ошибка работы лог схемы
          if(fix_block_active_state[FIX_BLOCK_SCHEME_INCORRECT >> 3 ] & (1 << (FIX_BLOCK_SCHEME_INCORRECT & ((1 << 3) - 1))))
            tempReadArray[0] |= (1<<bit);
          break;
        case 4://Ошибка работы триггеров
          if(fix_block_active_state[FIX_BLOCK_D_TRIGGER_STATE_INCORRECT >> 3 ] & (1 << (FIX_BLOCK_D_TRIGGER_STATE_INCORRECT & ((1 << 3) - 1))))
            tempReadArray[0] |= (1<<bit);
          break;
        case 5://Изменение конфигурации
          if(fix_block_active_state[FIX_BLOCK_SETTINGS_CHANGED >> 8] & (1 << (FIX_BLOCK_SETTINGS_CHANGED & ((1 << 3) - 1))))
            tempReadArray[0] |= (1<<bit);
          break;
        case 6://Пароль установлен - ти маєш це поле зробити
          if(fix_block_active_state[0] & 0x1)
            tempReadArray[0] |= (1<<bit);
          break;
        case 7://Запуск журнала
        {

          __LOG_INPUT *arr = (__LOG_INPUT*)(spca_of_p_prt[ID_FB_EVENT_LOG - _ID_FB_FIRST_VAR]);
          int value = arr[0] & (1 << (EVENT_LOG_WORK & ((1 << 5) - 1)));

          if (value) tempReadArray[0] |= (1<<bit);
          break;
        }
        case 8://Запуск регистратора - немає
          tempReadArray[0] |= 0;//(1<<bit);
          break;
        case 9://Время синхронизировано
          tempReadArray[0] |= 0;
          break;
        case 10://Ключ управления местное\дистанционное -немає
          tempReadArray[0] |= 0;//(1<<bit);
          break;
        case 11://НЦОП
          if(fix_block_active_state[FIX_BLOCK_VCE >> 8] & (1 << (FIX_BLOCK_VCE & ((1 << 3) - 1))))
            tempReadArray[0] |= (1<<bit);
          break;
        default:
          ;
        }//switch

    }//for
}//loadActualData()

int getCommonSmallModbusRegister(int adrReg)
{
  //получить содержимое регистра
  if(privateCommonSmallGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  if(commonsmallcomponent->isActiveActualData) loadCommonSmallActualData(); //ActualData
  commonsmallcomponent->isActiveActualData = 0;

  superSetOperativMarker(commonsmallcomponent, adrReg);

  if((adrReg-BEGIN_ADR_REGISTER)==1) return MARKER_ERRORPERIMETR;//смещение 1 только запись

  return tempReadArray[adrReg-BEGIN_ADR_REGISTER];
}//getDVModbusRegister(int adrReg)
int getCommonSmallModbusBit(int adrBit)
{
  //получить содержимое bit
  if(privateCommonSmallGetBit2(adrBit)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  if(commonsmallcomponent->isActiveActualData) loadCommonSmallActualData();
  commonsmallcomponent->isActiveActualData = 0;

  superSetOperativMarker(commonsmallcomponent, adrBit);
  switch(adrBit-BEGIN_ADR_BIT)
    {
    case 15:
    case 16:
    case 17:
      return MARKER_ERRORPERIMETR;//смещение  только запись
    }//switch

  short tmp   = tempReadArray[(adrBit-BEGIN_ADR_BIT)/16];
  short maska = 1<<((adrBit-BEGIN_ADR_BIT)%16);
  if(tmp&maska) return 1;
  return 0;
}//getDVModbusRegister(int adrReg)
int setCommonSmallModbusRegister(int adrReg, int dataReg)
{
  extern int upravlFlag;//флаг пакетов управления 1-есть управление
  //записать содержимое регистра
  if(privateCommonSmallGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  superSetOperativMarker(commonsmallcomponent, adrReg);
  superSetTempWriteArray(dataReg&0x3);//записать в буфер

  switch(adrReg-BEGIN_ADR_REGISTER)
    {
    case 0:
      return MARKER_ERRORPERIMETR;
    case 1:
      break;
    default:
      return MARKER_OUTPERIMETR;
    }//switch
  return 0;
}//getDVModbusRegister(int adrReg)
int setCommonSmallModbusBit(int adrBit, int dataBit)
{
  extern int upravlFlag;//флаг пакетов управления 1-есть управление
  //записать содержимое bit
  if(privateCommonSmallGetBit2(adrBit)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  superSetOperativMarker(commonsmallcomponent, adrBit);
  superSetTempWriteArray(dataBit);//записать в буфер

  switch(adrBit-BEGIN_ADR_BIT)
    {
    case 15://Очистить журнал Событий
      upravlFlag=1;//флаг пакетов управления 1-есть управление
      return dataBit;
    case 16://Активация конфигурации
      upravlFlag=1;//флаг пакетов управления 1-есть управление
      return dataBit;
    case 17://
      upravlFlag=1;//флаг пакетов управления 1-есть управление
      return dataBit;
    }//switch
  return MARKER_ERRORPERIMETR;
}//setCommonSmallModbusBit(int adrBit, int adrData)

void preCommonSmallReadAction(void)
{
//action до чтения
  commonsmallcomponent->operativMarker[0] = -1;
  commonsmallcomponent->operativMarker[1] = -1;
  commonsmallcomponent->isActiveActualData = 1;//оперативный маркер
}//
void postCommonSmallReadAction(void)
{
//action после чтения
  if(commonsmallcomponent->operativMarker[0]<0) return;//не было чтения
}//
void preCommonSmallWriteAction(void)
{
//action до записи
  commonsmallcomponent->operativMarker[0] = -1;
  commonsmallcomponent->operativMarker[1] = -1;//оперативный маркер
  commonsmallcomponent->isActiveActualData = 1;
}//
int postCommonSmallWriteAction(void)
{
//action после записи
  extern int globalResetFlag;//флаг глобального сброса
  if(commonsmallcomponent->operativMarker[0]<0) return 0;//не было записи
  switch(commonsmallcomponent->operativMarker[0])
    {
    case (BEGIN_ADR_REGISTER+1):
    {
      //запись второго регистра
      switch(tempWriteArray[0]&3)
        {
        case 1://Активация конфигурации
          //qDebug()<<"1111111111111111111111";
//          fix_block_active_state[0] &= ~0x1;//Прорубить окно
//          fix_block_active_state[0] |= tempWriteArray[0]&1;
          break;
        case 2://Общий сброс
          //qDebug()<<"2222222222222222222222222";
//          fix_block_active_state[0] &= ~0x2;//Прорубить окно
//          fix_block_active_state[0] |= tempWriteArray[0]&2;
          break;
        case 3://Активация конфигурации
          //Общий сброс
          break;
        }//switch
    }//case (BEGIN_ADR_REGISTER+1):
    break;

    case (BEGIN_ADR_BIT+15):
    {
      //Очистить журнал Событий
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
          //Повідомити, що операція тимчасово недоступна
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
      if(pointInterface==0)  //метка интерфейса 0-USB 1-RS485
        {
          if(tempWriteArray[0]==1)
            {
              superConfig_and_settings();//компонентная активация
              unsigned int result = set_config_and_settings(1, USB_PARAMS_FIX_CHANGES);//ЧЕРЕЗ ф-цию 5
              if (result != 0) 
              {
                if (result == 2)current_state_menu2.edition = ED_ERROR;
                return 3;
              }
            }
          if(tempWriteArray[0]==0)
          {
            unsigned int result = set_config_and_settings(0, USB_PARAMS_FIX_CHANGES);//ЧЕРЕЗ ф-цию 5
            if (result != 0) 
            {
              current_state_menu2.edition = ED_ERROR;
              return 3;
            }
          }
        }//if
      if(pointInterface==1)  //метка интерфейса 0-USB 1-RS485
        {
          if(tempWriteArray[0]==1)
            {
              superConfig_and_settings();//компонентная активация
              unsigned int result = set_config_and_settings(1, RS485_PARAMS_FIX_CHANGES);//ЧЕРЕЗ ф-цию 5
              if (result != 0) 
              {
                if (result == 2) current_state_menu2.edition = ED_ERROR;
                return 3;
              }
            }//if
          if(tempWriteArray[0]==0)
          {
            unsigned int result = set_config_and_settings(0, RS485_PARAMS_FIX_CHANGES);//ЧЕРЕЗ ф-цию 5
            if (result != 0) 
            {
              current_state_menu2.edition = ED_ERROR;
              return 3;
            }
          }
        }//if
    }//case (BEGIN_ADR_REGISTER+1):
    break;
    case (BEGIN_ADR_BIT+17):
    {
      //Общий сброс
      globalResetFlag=1;//флаг глобального сброса
    }//case (BEGIN_ADR_REGISTER+1):
    break;
    }//switch
  if(commonsmallcomponent->operativMarker[1]<0) return 0;//не было записи
  switch(commonsmallcomponent->operativMarker[1])
    {
    case (BEGIN_ADR_BIT+17):
    {
      //Общий сброс
      fix_block_active_state[0] &= ~0x2;//Прорубить окно
      fix_block_active_state[0] |= tempWriteArray[1]&1;
    }//case (BEGIN_ADR_REGISTER+1):
    break;
    }//switch
  return 0;
}//

int privateCommonSmallGetReg2(int adrReg)
{
  //проверить внешний периметр
  int count_register = REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
int privateCommonSmallGetBit2(int adrBit)
{
  //проверить внешний периметр
  int count_bit = BIT_FOR_OBJ;
  if(adrBit>=BEGIN_ADR_BIT && adrBit<(BEGIN_ADR_BIT+count_bit)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)

void config_and_settingsCommonSmall(void)
{
//action активации
}

