#include "header.h"

//начальный регистр в карте памяти
#define BEGIN_ADR_REGISTER 200
//начальный bit в карте памяти
#define BEGIN_ADR_BIT 18000
#define BIT_FOR_OBJ 1
//макс к-во обектов
#define TOTAL_OBJ 128
int privateTSSmallGetReg1(int adrReg);
int privateTSSmallGetReg2(int adrReg);
int privateTSSmallGetBit1(int adrBit);
int privateTSSmallGetBit2(int adrBit);

int getTSSmallModbusRegister(int);//получить содержимое регистра
int getTSSmallModbusBit(int);//получить содержимое бита
int setTSSmallModbusRegister(int, int);//получить содержимое регистра
int setTSSmallModbusBit(int, int);//получить содержимое бита

void setTSSmallCountObject(void);//записать к-во обектов
void preTSSmallReadAction(void);//action до чтения
void postTSSmallReadAction(void);//action после чтения
void preTSSmallWriteAction(void);//action до записи
int postTSSmallWriteAction(void);//action после записи
void loadTSSmallActualData(void);
int getTSmallModbusBeginAdrRegister(void);

COMPONENT_OBJ *tssmallcomponent;

int getTSmallModbusBeginAdrRegister(void)
{
  //получить адрес нач регистра
 return BEGIN_ADR_REGISTER;
}//getTSmallModbusBeginAdrRegister(void)

/**************************************/
//подготовка компонента телесигнализации
/**************************************/
void constructorTSSmallComponent(COMPONENT_OBJ *tssmallcomp)
{
  tssmallcomponent = tssmallcomp;

  tssmallcomponent->countObject = 0;//к-во обектов

  tssmallcomponent->getModbusRegister = getTSSmallModbusRegister;//получить содержимое регистра
  tssmallcomponent->getModbusBit      = getTSSmallModbusBit;//получить содержимое бита
  tssmallcomponent->setModbusRegister = setTSSmallModbusRegister;//получить содержимое регистра
  tssmallcomponent->setModbusBit      = setTSSmallModbusBit;//получить содержимое бита

  tssmallcomponent->preReadAction   = preTSSmallReadAction;//action до чтения
  tssmallcomponent->postReadAction  = postTSSmallReadAction;//action после чтения
  tssmallcomponent->preWriteAction  = preTSSmallWriteAction;//action до записи
  tssmallcomponent->postWriteAction = postTSSmallWriteAction;//action после записи

  tssmallcomponent->isActiveActualData = 0;
}//prepareDVinConfig

void loadTSSmallActualData(void) {
  //ActualData
  setTSSmallCountObject(); //записать к-во обектов

  int cnt_treg = tssmallcomponent->countObject/16;
  if(tssmallcomponent->countObject%16) cnt_treg++;
  for(int ii=0; ii<cnt_treg; ii++) tempReadArray[ii] = 0;
   __LN_TS *arr = (__LN_TS*)(spca_of_p_prt[ID_FB_TS - _ID_FB_FIRST_VAR]);
  for(int item=0; item<tssmallcomponent->countObject; item++) {
   int ireg = item/16;

   int value = arr[item].active_state[TU_OUT  >> 3] & (1 << (TU_OUT  & ((1 << 3) - 1)));
   
   int tsdata = 0;
   if(value) tsdata=1;
   tempReadArray[ireg] |= (tsdata&0x1)<<(item%16);
  }//for

  /*
  Загальну кількість завжди треба брати з конфігурації current_config_prt типу __CONFIG (для читання поточного стану) і/або current_config/current_config_edit (для редагування)
  
  1) spca_of_p_prt (масив вказівників на динамічну пам'ять, де знаходяться актуальні дані - для читання стану)
  2) Індекс функц.блоку береться з enum _id_fb (const_settings.h) - _ID_FB_FIRST_VAR. Наприклад, для ТС spca_of_p_prt[ID_FB_TS - _ID_FB_FIRST_VAR]
   - це вказівник на першу адресу всіх ТС-ів
  3) У цій пам'яті знаходиться масив типу __LN_XXX (Наприклад для ТС __LN_TS)
  4) Вкзівник треба перемістити на потрібний елемент. Наприклад: (((__LN_TS*)spca_of_p_prt[ID_FB_TS - _ID_FB_FIRST_VAR]) + item), де item  - це номер ТС-у, який нас цікавить
    Всі типи описані у файлі type_definition.h.
  __settings_for_XXX - це вкорочена структура тільки налаштувань (працює з масивом вказівників sca_of_p і sca_of_p_edit)
  __LN_XXX - це hjpibhtyf структура налаштувань, станів і службової інформації (працює тільки з масивом spca_of_p_prt)
  5) Стан зчитуєтться з поля active_state відповідної струтури
  6) Номера бітів визначвені enum _XXX_output_signals (для ТС - це enum _TS_output_signals const_settings.h).
  
  Наприклад зитування стану виходу дисткртного входу за номером _n
  __LN_INPUT *arr = (__LN_INPUT*)(spca_of_p_prt[ID_FB_INPUT - _ID_FB_FIRST_VAR]);
  value = arr[_n].active_state[INPUT_OUT >> 3] & (1 << (INPUT_OUT & ((1 << 3) - 1)));
  */
}//loadActualData() 

int getTSSmallModbusRegister(int adrReg)
{
  //получить содержимое регистра
  if(privateTSSmallGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(tssmallcomponent->isActiveActualData) loadTSSmallActualData(); //ActualData
  tssmallcomponent->isActiveActualData = 0;
  if(privateTSSmallGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  superSetOperativMarker(tssmallcomponent, adrReg);

  return tempReadArray[adrReg-BEGIN_ADR_REGISTER];
}//getDVModbusRegister(int adrReg)
int getTSSmallModbusBit(int adrBit)
{
  //получить содержимое bit
  if(privateTSSmallGetBit2(adrBit)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(tssmallcomponent->isActiveActualData) loadTSSmallActualData();
  tssmallcomponent->isActiveActualData = 0;
  if(privateTSSmallGetBit1(adrBit)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  superSetOperativMarker(tssmallcomponent, adrBit);

  short tmp   = tempReadArray[(adrBit-BEGIN_ADR_BIT)/16];
  short maska = 1<<((adrBit-BEGIN_ADR_BIT)%16);
  if(tmp&maska) return 1;
  return 0;
}//getDVModbusRegister(int adrReg)
int setTSSmallModbusRegister(int adrReg, int x)
{
  UNUSED(x);
  //записать содержимое регистра
  superSetOperativMarker(tssmallcomponent, adrReg);
  return MARKER_OUTPERIMETR;
}//getDVModbusRegister(int adrReg)
int setTSSmallModbusBit(int adrBit, int x)
{
  UNUSED(x);
  //записать содержимое bit
  superSetOperativMarker(tssmallcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDVModbusRegister(int adrReg)

void setTSSmallCountObject(void) {
//записать к-во обектов
  int cntObj = current_config.n_ts;    //Кількість блоків сигналізацій
  if(cntObj<0) return;
  if(cntObj>TOTAL_OBJ) return;
  tssmallcomponent->countObject = cntObj;
}//
void preTSSmallReadAction(void) {
//action до чтения
  tssmallcomponent->operativMarker[0] = -1;
  tssmallcomponent->operativMarker[1] = -1;//оперативный маркер
  tssmallcomponent->isActiveActualData = 1;
}//
void postTSSmallReadAction(void) {
//action после чтения
  if(tssmallcomponent->operativMarker[0]<0) return;//не было чтения
}//
void preTSSmallWriteAction(void) {
//action до записи
  tssmallcomponent->operativMarker[0] = -1;
  tssmallcomponent->operativMarker[1] = -1;//оперативный маркер
  tssmallcomponent->isActiveActualData = 1;
}//
int postTSSmallWriteAction(void) {
//action после записи
  return 0;
}//

int privateTSSmallGetReg1(int adrReg)
{
  //проверить внутренний периметр
  int count_register = tssmallcomponent->countObject/16;
  if(tssmallcomponent->countObject%16) count_register++;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg1(int adrReg)

int privateTSSmallGetReg2(int adrReg)
{
  //проверить внешний периметр
  int count_register = TOTAL_OBJ/16;
  if(TOTAL_OBJ%16) count_register++;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)

int privateTSSmallGetBit1(int adrBit)
{
  //проверить внутренний периметр
  int count_bit = BIT_FOR_OBJ*tssmallcomponent->countObject;
  if(adrBit>=BEGIN_ADR_BIT && adrBit<(BEGIN_ADR_BIT+count_bit)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg1(int adrReg)

int privateTSSmallGetBit2(int adrBit)
{
  //проверить внешний периметр
  int count_bit = BIT_FOR_OBJ*TOTAL_OBJ;
  if(adrBit>=BEGIN_ADR_BIT && adrBit<(BEGIN_ADR_BIT+count_bit)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
