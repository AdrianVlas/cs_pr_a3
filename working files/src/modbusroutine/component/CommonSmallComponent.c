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
        case 0://Неисправность общая
          if(fix_block_active_state[FIX_BLOCK_DEFECT >> 3] & (1 << (FIX_BLOCK_DEFECT & ((1 << 3) - 1)))) 
                              tempReadArray[0] |= (1<<bit);
          break;
        case 1://Неисправность аварийная
          if(fix_block_active_state[FIX_BLOCK_AVAR_DEFECT >> 3] & (1 << (FIX_BLOCK_AVAR_DEFECT & ((1 << 3) - 1))))
                              tempReadArray[0] |= (1<<bit);
          break;
        case 2://Ошибка работы лог схемы
          if(fix_block_active_state[FIX_BLOCK_SCHEME_INCORRECT >> 3 ] & (1 << (FIX_BLOCK_SCHEME_INCORRECT & ((1 << 3) - 1))))
                              tempReadArray[0] |= (1<<bit);
          break;
        case 3://Ошибка работы триггеров
          if(fix_block_active_state[FIX_BLOCK_D_TRIGGER_STATE_INCORRECT >> 3 ] & (1 << (FIX_BLOCK_D_TRIGGER_STATE_INCORRECT & ((1 << 3) - 1))))
                              tempReadArray[0] |= (1<<bit);
          break;
        case 4://Изменение конфигурации
          if(fix_block_active_state[FIX_BLOCK_SETTINGS_CHANGED >> 8] & (1 << (FIX_BLOCK_SETTINGS_CHANGED & ((1 << 3) - 1))))
                              tempReadArray[0] |= (1<<bit);
          break;
        case 5://Пароль установлен - ти маєш це поле зробити
          if(fix_block_active_state[0] & 0x1)
                              tempReadArray[0] |= (1<<bit);
          break;
        case 6://Запуск журнала
          {
          
          __LOG_INPUT *arr = (__LOG_INPUT*)(spca_of_p_prt[ID_FB_EVENT_LOG - _ID_FB_FIRST_VAR]);
          int value = arr[0] & (1 << (EVENT_LOG_WORK & ((1 << 5) - 1)));
          
          if (value) tempReadArray[0] |= (1<<bit);
          break;
          }
        case 7://Запуск регистратора - немає
                              tempReadArray[0] |= 0;//(1<<bit);
          break;
        case 8://Время синхронизировано
          tempReadArray[0] |= 0;
          break;
        case 9://Ключ управления местное\дистанционное -немає
//          if(fix_block_active_state[0] & 0x1)
                              tempReadArray[0] |= 0;//(1<<bit);
          break;
        case 10://Пропуск
        case 11://Пропуск
        case 12://Пропуск
        case 13://Пропуск
        case 14://Пропуск
        case 15://Пропуск
          tempReadArray[0] |= 0;
          break;
        case 16://Активация конфигурации (команда)
          if(fix_block_active_state[0] & 0x1)
                              tempReadArray[1] |= (1<<(bit-16));
          break;
        case 17://Сброс общий - покищо немає, якщо буде також буде командою
          if(fix_block_active_state[0] & 0x1)
                              tempReadArray[1] |= (1<<(bit-16));
          break;
        default:
          ;
        }//switch

    }//for
  /*
  1) Стан знаходяться у масиві uint8_t fix_block_active_state[DIV_TO_HIGHER(FIX_BLOCK_SIGNALS_OUT, 8)];
  2) Співвідношення між номерами бітів і їх назвами є у enum _FIX_BLOCK_output_signals
  */
}//loadActualData()

int getCommonSmallModbusRegister(int adrReg)
{
  //получить содержимое регистра
  if(privateCommonSmallGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  if(commonsmallcomponent->isActiveActualData) loadCommonSmallActualData(); //ActualData
  commonsmallcomponent->isActiveActualData = 0;

  superSetOperativMarker(commonsmallcomponent, adrReg);

  return tempReadArray[adrReg-BEGIN_ADR_REGISTER];
}//getDVModbusRegister(int adrReg)
int getCommonSmallModbusBit(int adrBit)
{
  //получить содержимое bit
  if(privateCommonSmallGetBit2(adrBit)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  if(commonsmallcomponent->isActiveActualData) loadCommonSmallActualData();
  commonsmallcomponent->isActiveActualData = 0;

  superSetOperativMarker(commonsmallcomponent, adrBit);

  short tmp   = tempReadArray[(adrBit-BEGIN_ADR_BIT)/16];
  short maska = 1<<((adrBit-BEGIN_ADR_BIT)%16);
  if(tmp&maska) return 1;
  return 0;
}//getDVModbusRegister(int adrReg)
int setCommonSmallModbusRegister(int adrReg, int dataReg)
{
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
   default: return MARKER_OUTPERIMETR;
    }//switch
  return 0;
}//getDVModbusRegister(int adrReg)
int setCommonSmallModbusBit(int adrBit, int dataBit)
{
  //записать содержимое bit
  if(privateCommonSmallGetBit2(adrBit)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  superSetOperativMarker(commonsmallcomponent, adrBit);
  superSetTempWriteArray(dataBit);//записать в буфер

  switch(adrBit-BEGIN_ADR_BIT)
    {
    case 16:
      //    qDebug()<<"16="<<dataBit;
      return dataBit;
    case 17:
//      qDebug()<<"17="<<dataBit;
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
          //qDebug()<<"333333333333333333333333333333";
//          fix_block_active_state[0] &= ~0x3;//Прорубить окно
//          fix_block_active_state[0] |= tempWriteArray[0]&3;
          break;
        }//switch
    }//case (BEGIN_ADR_REGISTER+1):
    break;
    case (BEGIN_ADR_BIT+16):
    {
    //      qDebug()<<"111111111111111111111111";
      //Активация конфигурации
//      fix_block_active_state[0] &= ~0x2;//Прорубить окно
//      fix_block_active_state[0] |= tempWriteArray[0]&1;
//int tt=0;
if(tempWriteArray[0]==1) 
       set_config_and_settings(1, USB_PARAMS_FIX_CHANGES);//ЧЕРЕЗ ф-цию 5
if(tempWriteArray[0]==0) 
       set_config_and_settings(0, USB_PARAMS_FIX_CHANGES);//ЧЕРЕЗ ф-цию 5
                        //                   tt = 1;
    }//case (BEGIN_ADR_REGISTER+1):
    break;
    case (BEGIN_ADR_BIT+17):
    {
  //        qDebug()<<"222222222222222222222222";
      //Общий сброс
//      fix_block_active_state[0] &= ~0x2;//Прорубить окно
//      fix_block_active_state[0] |= tempWriteArray[1]&1;
    }//case (BEGIN_ADR_REGISTER+1):
    break;
    }//switch
  if(commonsmallcomponent->operativMarker[1]<0) return 0;//не было записи
  switch(commonsmallcomponent->operativMarker[1])
    {
    case (BEGIN_ADR_BIT+17):
    {
//          qDebug()<<"333333333333333333333333";
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
