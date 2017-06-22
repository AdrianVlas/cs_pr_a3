#include "header.h"

//начальный регистр в карте памяти
#define BEGIN_ADR_REGISTER 14000
//макс к-во обектов
#define REGISTER_FOR_OBJ 43

int privatePKVBigGetReg2(int adrReg);

int getPKVBigModbusRegister(int);//получить содержимое регистра
int getPKVBigModbusBit(int);//получить содержимое бита
int setPKVBigModbusRegister(int, int);//получить содержимое регистра
int setPKVBigModbusBit(int, int);//получить содержимое бита

void prePKVBigReadAction(void);//action до чтения
void postPKVBigReadAction(void);//action после чтения
void prePKVBigWriteAction(void);//action до записи
void postPKVBigWriteAction(void);//action после записи
void loadPKVBigActualData(void);

COMPONENT_OBJ *pkvbigcomponent;

/**************************************/
//подготовка компонента пароль коммуникация время
/**************************************/
void constructorPKVBigComponent(COMPONENT_OBJ *pkvbigcomp)
{
  pkvbigcomponent = pkvbigcomp;

  pkvbigcomponent->countObject = 1;//к-во обектов

  pkvbigcomponent->getModbusRegister = getPKVBigModbusRegister;//получить содержимое регистра
  pkvbigcomponent->getModbusBit      = getPKVBigModbusBit;//получить содержимое бита
  pkvbigcomponent->setModbusRegister = setPKVBigModbusRegister;//получить содержимое регистра
  pkvbigcomponent->setModbusBit      = setPKVBigModbusBit;//получить содержимое бита

  pkvbigcomponent->preReadAction   = prePKVBigReadAction;//action до чтения
  pkvbigcomponent->postReadAction  = postPKVBigReadAction;//action после чтения
  pkvbigcomponent->preWriteAction  = prePKVBigWriteAction;//action до записи
  pkvbigcomponent->postWriteAction = postPKVBigWriteAction;//action после записи

  pkvbigcomponent->isActiveActualData = 0;
}//prepareDVinConfig

void loadPKVBigActualData(void) {
  //ActualData
  for(int i=0; i<100; i++) tempReadArray[i] = i;
  /*
  Читання/запис здійснється з полів (коментарі додані у файлі type_definition.h для структури типу __CONFIG)
  settings_fix_prt/settings_fix/settings_fix_edit
  
  14200 - timeout_deactivation_password_interface_USB/timeout_deactivation_password_interface_RS485
  14201 - password_interface_USB/password_interface_RS485 (тільки запис. див. опис у ТЗ моєму)
  14202 - timeout_idle_new_settings (одиниці, як у карті пам'яті)
  14203 - language
  
  14205 - baud_RS485
  14206 - number_stop_bit_RS485
  14207 - pare_bit_RS485
  14208 - time_out_1_RS485
  
  14213 - address
  
  14216-14223 - name_of_cell
  
  14224-14225
  ------------
  uint8_t *label_to_time_array;
  if (copying_time == 0) label_to_time_array = time;
  else label_to_time_array = time_copy;
  Формат BCD
  0 - десяті і соті секунди (на запис тільки 0) (0x0-0x99)
  1 - секунди (0x0-0x59)
  2 - хвилини (0x0-0x59)
  3 - година (0x0-0x23)
  4 - день місяця (0x1-0x31)
  5 - місяць (0x1-0x12)
  6 - рік (0x0-0x99)
  
   При записі по адресі 0 (присторою) є широкосмуговий запис дати і часу. Прийняти і обробити паакет без відповіді
  
  Для запису записати записувані значення у time_edit і виконати такий код
            if (check_data_for_data_time_menu() == 1)
            {
              //Дані достовірні
              //Виставляємо повідомлення запису часу в RTC
              //При цьому виставляємо біт блокування негайного запуску операції, щоб засинхронізуватися з роботою вимірювальної системи
              _SET_BIT(control_i2c_taskes, TASK_START_WRITE_RTC_BIT);
              _SET_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT);
            }
            else error = ERROR_ILLEGAL_DATA_VALUE;  
  ------------
  */
}//loadActualData() 

int getPKVBigModbusRegister(int adrReg)
{
  //получить содержимое регистра
  if(privatePKVBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if((adrReg-BEGIN_ADR_REGISTER)==1) return MARKER_ERRORPERIMETR;

  if(pkvbigcomponent->isActiveActualData) loadPKVBigActualData(); //ActualData
  pkvbigcomponent->isActiveActualData = 0;

  superSetOperativMarker(pkvbigcomponent, adrReg);

  return tempReadArray[adrReg-BEGIN_ADR_REGISTER];
}//getDOUTBigModbusRegister(int adrReg)
int getPKVBigModbusBit(int adrBit)
{
  //получить содержимое регистра
  superSetOperativMarker(pkvbigcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setPKVBigModbusRegister(int adrReg, int dataReg)
{
  //записать содержимое регистра
  if(privatePKVBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  superSetOperativMarker(pkvbigcomponent, adrReg);
  superSetTempWriteArray(dataReg);//записать в буфер

  switch(adrReg-BEGIN_ADR_REGISTER) {
   case 0: //14000
    if(dataReg>3600) return MARKER_ERRORDIAPAZON;
    if(dataReg<30) return MARKER_ERRORDIAPAZON;
    return dataReg;
   case 1: //14001
    return dataReg;
   case 2: //14002
    if(dataReg>3600) return MARKER_ERRORDIAPAZON;
    if(dataReg<60) return MARKER_ERRORDIAPAZON;
    return dataReg;
   case 3: //14003
    if(dataReg>5) return MARKER_ERRORDIAPAZON;
    if(dataReg<1) return MARKER_ERRORDIAPAZON;
    return dataReg;
   case 4: //14004
    return dataReg;
   case 5: //14005
    if(dataReg>6) return MARKER_ERRORDIAPAZON;
    return dataReg;
   case 6: //14006
    if(dataReg>2) return MARKER_ERRORDIAPAZON;
    if(dataReg<1) return MARKER_ERRORDIAPAZON;
    return dataReg;
   case 7: //14007
    if(dataReg>2) return MARKER_ERRORDIAPAZON;
    return dataReg;
   case 8: //14008
    if(dataReg>1500) return MARKER_ERRORDIAPAZON;
    if(dataReg<15) return MARKER_ERRORDIAPAZON;
    return dataReg;
   case 9: //14009
    if(dataReg>6) return MARKER_ERRORDIAPAZON;
    return dataReg;
   case 10: //14010
    if(dataReg>2) return MARKER_ERRORDIAPAZON;
    if(dataReg<1) return MARKER_ERRORDIAPAZON;
    return dataReg;
   case 11: //14011
    if(dataReg>2) return MARKER_ERRORDIAPAZON;
    return dataReg;
   case 12: //14012
    if(dataReg>1500) return MARKER_ERRORDIAPAZON;
    if(dataReg<15) return MARKER_ERRORDIAPAZON;
    return dataReg;
   case 13: //14013
    if(dataReg>247) return MARKER_ERRORDIAPAZON;
    if(dataReg<1) return MARKER_ERRORDIAPAZON;
    return dataReg;
   case 14: //14014
    if(dataReg<3) return MARKER_ERRORDIAPAZON;
    return dataReg;
   case 15: //14015
   case 16: //14015
   case 17: //14015
   case 18: //14015
   case 19: //14015
   case 20: //14015
   case 21: //14015
   case 22: //14015
   case 23: //14015
    return dataReg;
   case 24: //14024
    if(dataReg>99) return MARKER_ERRORDIAPAZON;
    return dataReg;
   case 25: //14025
    if(dataReg>12) return MARKER_ERRORDIAPAZON;
    if(dataReg<1) return MARKER_ERRORDIAPAZON;
    return dataReg;
   case 26: //14026
    if(dataReg>31) return MARKER_ERRORDIAPAZON;
    if(dataReg<1) return MARKER_ERRORDIAPAZON;
    return dataReg;
   case 27: //14027
    if(dataReg>23) return MARKER_ERRORDIAPAZON;
    return dataReg;
   case 28: //14028
   case 29: //14029
    if(dataReg>59) return MARKER_ERRORDIAPAZON;
    return dataReg;
   case 30: //14030
    if(dataReg>99) return MARKER_ERRORDIAPAZON;
    return dataReg;
   case 31: //14031
    if(dataReg>32767) dataReg -=32768;
    if(dataReg>720) return MARKER_ERRORDIAPAZON;
    if(dataReg<-720) return MARKER_ERRORDIAPAZON;
    return dataReg;
   case 32: //14032
    if(dataReg>1) return MARKER_ERRORDIAPAZON;
    return dataReg;
   case 33: //14033
    if(dataReg>12) return MARKER_ERRORDIAPAZON;
    if(dataReg<1) return MARKER_ERRORDIAPAZON;
    return dataReg;
   case 34: //14034
    if(dataReg>5) return MARKER_ERRORDIAPAZON;
    if(dataReg<1) return MARKER_ERRORDIAPAZON;
    return dataReg;
   case 35: //14035
    if(dataReg>7) return MARKER_ERRORDIAPAZON;
    if(dataReg<1) return MARKER_ERRORDIAPAZON;
    return dataReg;
   case 36: //14036
    if(dataReg>23) return MARKER_ERRORDIAPAZON;
    return dataReg;
   case 37: //14037
    if(dataReg>12) return MARKER_ERRORDIAPAZON;
    if(dataReg<1) return MARKER_ERRORDIAPAZON;
    return dataReg;
   case 38: //14038
    if(dataReg>5) return MARKER_ERRORDIAPAZON;
    if(dataReg<1) return MARKER_ERRORDIAPAZON;
    return dataReg;
   case 39: //14039
    if(dataReg>7) return MARKER_ERRORDIAPAZON;
    if(dataReg<1) return MARKER_ERRORDIAPAZON;
    return dataReg;
   case 40: //14040
    if(dataReg>23) return MARKER_ERRORDIAPAZON;
    return dataReg;
   case 41: //14041
    if(dataReg>2) return MARKER_ERRORDIAPAZON;
    return dataReg;
   case 42: //14042
    return dataReg;
  }//switch

  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setPKVBigModbusBit(int adrBit, int x)
{
  UNUSED(x);
  //получить содержимое регистра
  superSetOperativMarker(pkvbigcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void prePKVBigReadAction(void) {
//action до чтения
  pkvbigcomponent->operativMarker[0] = -1;
  pkvbigcomponent->operativMarker[1] = -1;//оперативный маркер
  pkvbigcomponent->isActiveActualData = 1;
}//
void postPKVBigReadAction(void) {
//action после чтения
  if(pkvbigcomponent->operativMarker[0]<0) return;//не было чтения
}//
void prePKVBigWriteAction(void) {
//action до записи
  pkvbigcomponent->operativMarker[0] = -1;
  pkvbigcomponent->operativMarker[1] = -1;//оперативный маркер
  pkvbigcomponent->isActiveActualData = 1;
}//
void postPKVBigWriteAction(void) {
//action после записи
  if(pkvbigcomponent->operativMarker[0]<0) return;//не было записи
//  int offset = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//найти смещение TempWriteArray
//  int countRegister = pkvbigcomponent->operativMarker[1]-pkvbigcomponent->operativMarker[0]+1;
//  if(pkvbigcomponent->operativMarker[1]<0) countRegister = 1;
}//

int privatePKVBigGetReg2(int adrReg)
{
  //проверить внешний периметр
  int count_register = REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
