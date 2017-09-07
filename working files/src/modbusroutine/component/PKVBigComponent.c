#include "header.h"

//начальный регистр в карте памяти
#define BEGIN_ADR_REGISTER 14200
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
int postPKVBigWriteAction(void);//action после записи
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
/*
    unsigned char *label_to_time_array;
    if (copying_time == 0) label_to_time_array = time;
    else label_to_time_array = time_copy;
*/
    unsigned char *label_to_time_array;
    if (copying_time == 2) label_to_time_array = time_copy;
    else label_to_time_array = time;
    
  for(int i=0; i<REGISTER_FOR_OBJ; i++) {
   switch(i) {
    case 0://Время активации пароля после простоя
    tempReadArray[i] = settings_fix.timeout_deactivation_password_interface_USB;
    break;
    case 1://Проверка/установка пароля
    tempReadArray[i] = 0;
    break;
    case 2://Тайм-аут применения изменений
    tempReadArray[i] = settings_fix.timeout_idle_new_settings;
    break;
    case 3://Язык пользовательского интерфейса
    tempReadArray[i] = settings_fix.language;
    break;
    case 4://
    tempReadArray[i] = 0;
    break;
    case 5://Скорость порта связи
    tempReadArray[i] = settings_fix.baud_RS485;
    break;
    case 6://Количество стоп-бит
    tempReadArray[i] = settings_fix.number_stop_bit_RS485;
    break;
    case 7://Паритет
    tempReadArray[i] = settings_fix.pare_bit_RS485;
    break;
//    case 8://Задержка приёма
//    tempReadArray[i] = settings_fix.time_out_1_RS485;
//    break;
//    case 9://Скорость порта связи 2
//    tempReadArray[i] = settings_fix.baud_RS485;
//    break;
//    case 10://Количество стоп-бит 2
//    tempReadArray[i] = settings_fix.number_stop_bit_RS485;
//    break;
//    case 11://Паритет 2
//    tempReadArray[i] = settings_fix.pare_bit_RS485;
//    break;
//    case 12://Задержка приёма 2
//    tempReadArray[i] = settings_fix.time_out_1_RS485;
    case 8://
    case 9://
    case 10://
    case 11://
    case 12://
     tempReadArray[i] = 0;
    break;

    case 13://Адрес устройства в сети
    tempReadArray[i] = settings_fix.address;
    break;
    case 14://Таймаут конца фрейма
     tempReadArray[i] = 0;
    break;
    case 15://
    tempReadArray[i] = 0;
    break;
    case 16://Символ 1 и 2
    tempReadArray[i] = settings_fix.name_of_cell[0] + ((settings_fix.name_of_cell[1]<<8)&0xFF00);
    break;
    case 17://Символ 3 и 4
    tempReadArray[i] = settings_fix.name_of_cell[2] + ((settings_fix.name_of_cell[3]<<8)&0xFF00);
    break;
    case 18://Символ 5 и 6
    tempReadArray[i] = settings_fix.name_of_cell[4] + ((settings_fix.name_of_cell[5]<<8)&0xFF00);
    break;
    case 19://Символ 7 и 8
    tempReadArray[i] = settings_fix.name_of_cell[6] + ((settings_fix.name_of_cell[7]<<8)&0xFF00);
    break;
    case 20://Символ 9 и 10
    tempReadArray[i] = settings_fix.name_of_cell[8] + ((settings_fix.name_of_cell[9]<<8)&0xFF00);
    break;
    case 21://Символ 11 и 12
    tempReadArray[i] = settings_fix.name_of_cell[10] + ((settings_fix.name_of_cell[11]<<8)&0xFF00);
    break;
    case 22://Символ 13 и 14
    tempReadArray[i] = settings_fix.name_of_cell[12] + ((settings_fix.name_of_cell[13]<<8)&0xFF00);
    break;
    case 23://Символ 15 и 16
    tempReadArray[i] = settings_fix.name_of_cell[14] + ((settings_fix.name_of_cell[15]<<8)&0xFF00);
    break;

    case 24://Год
    tempReadArray[i] = *(label_to_time_array + 6);
    break;
    case 25://Месяц
    tempReadArray[i] = *(label_to_time_array + 5);
    break;
    case 26://День
    tempReadArray[i] = *(label_to_time_array + 4);
    break;
    case 27://Час
    tempReadArray[i] = *(label_to_time_array + 3);
    break;
    case 28://Минуты
    tempReadArray[i] = *(label_to_time_array + 2);
    break;
    case 29://Секунды
    tempReadArray[i] = *(label_to_time_array + 1);
    break;
    case 30://Сотые секунды
    tempReadArray[i] = *(label_to_time_array + 0);
    break;

    case 31://Часовой пояс
    case 32://Переход на Зимнее/Летнее время
    case 33://Месяц перехода на Летнее время
    case 34://Неделя месяца перехода на Летнее время
    case 35://День недели перехода на Летнее время
    case 36://Час недели перехода на Летнее время
    case 37://Месяц перехода на Зимнее время
    case 38://Неделя месяца перехода на Зимнее время
    case 39://День недели перехода на Зимнее время
    case 40://Час недели перехода на Зимнее время
    case 41://Синхронизация времени
    case 42://Время утраты синхронизации
    tempReadArray[i] = 0;
    break;
   }//switch
  }//for
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
int getPKVBigModbusBit(int x)
{
  //получить содержимое регистра
  UNUSED(x);
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
   break; 
   case 1: //14001
   break; 
   case 2: //14002
    if(dataReg>3600) return MARKER_ERRORDIAPAZON;
    if(dataReg<60) return MARKER_ERRORDIAPAZON;
   break; 
   case 3: //14003
    if(dataReg>5) return MARKER_ERRORDIAPAZON;
    if(dataReg<1) return MARKER_ERRORDIAPAZON;
   break; 
   case 4: //14004
   break; 
   case 5: //14005
    if(dataReg>6) return MARKER_ERRORDIAPAZON;
   break; 
   case 6: //14006
    if(dataReg>2) return MARKER_ERRORDIAPAZON;
    if(dataReg<1) return MARKER_ERRORDIAPAZON;
   break; 
   case 7: //14007
    if(dataReg>2) return MARKER_ERRORDIAPAZON;
   break; 
   case 8: //14008
    if(dataReg>1500) return MARKER_ERRORDIAPAZON;
    if(dataReg<15) return MARKER_ERRORDIAPAZON;
   break; 
   case 9: //14009
    if(dataReg>6) return MARKER_ERRORDIAPAZON;
   break; 
   case 10: //14010
    if(dataReg>2) return MARKER_ERRORDIAPAZON;
    if(dataReg<1) return MARKER_ERRORDIAPAZON;
   break; 
   case 11: //14011
    if(dataReg>2) return MARKER_ERRORDIAPAZON;
   break; 
   case 12: //14012
    if(dataReg>1500) return MARKER_ERRORDIAPAZON;
    if(dataReg<15) return MARKER_ERRORDIAPAZON;
   break; 
   case 13: //14013
    if(dataReg>247) return MARKER_ERRORDIAPAZON;
    if(dataReg<1) return MARKER_ERRORDIAPAZON;
   break; 
   case 14: //14014
    if(dataReg<3) return MARKER_ERRORDIAPAZON;
   break; 
   case 15: //14015
   case 16: //14015
   case 17: //14015
   case 18: //14015
   case 19: //14015
   case 20: //14015
   case 21: //14015
   case 22: //14015
   case 23: //14015
   break; 
   case 24: //14224
    if(dataReg&0xff00) return MARKER_ERRORDIAPAZON;
    if(dataReg>0x99) return MARKER_ERRORDIAPAZON;
    if((dataReg&0xf)>9) return MARKER_ERRORDIAPAZON;
   break; 
   case 25: //14225
    if(dataReg&0xff00) return MARKER_ERRORDIAPAZON;
    if(dataReg==0) return MARKER_ERRORDIAPAZON;
    if(dataReg>0x12) return MARKER_ERRORDIAPAZON;
    if((dataReg&0xf)>9) return MARKER_ERRORDIAPAZON;
//    if(dataReg==0xA || dataReg==0xB || dataReg==0xC || dataReg==0xD || dataReg==0xE || dataReg==0xF) return MARKER_ERRORDIAPAZON;
   break; 
   case 26: //14226
    if(dataReg&0xff00) return MARKER_ERRORDIAPAZON;
    if(dataReg==0) return MARKER_ERRORDIAPAZON;
    if(dataReg>0x31) return MARKER_ERRORDIAPAZON;
    if((dataReg&0xf)>9) return MARKER_ERRORDIAPAZON;
   break; 
   case 27: //14227
    if(dataReg&0xff00) return MARKER_ERRORDIAPAZON;
    if(dataReg>0x23) return MARKER_ERRORDIAPAZON;
    if((dataReg&0xf)>9) return MARKER_ERRORDIAPAZON;
   break; 
   case 28: //14228
   case 29: //14229
    if(dataReg&0xff00) return MARKER_ERRORDIAPAZON;
    if(dataReg>0x59) return MARKER_ERRORDIAPAZON;
    if((dataReg&0xf)>9) return MARKER_ERRORDIAPAZON;
   break; 
   case 30: //14230
    if(dataReg&0xff00) return MARKER_ERRORDIAPAZON;
    if(dataReg>0x99) return MARKER_ERRORDIAPAZON;
    if((dataReg&0xf)>9) return MARKER_ERRORDIAPAZON;
   break; 
   case 31: //14031
//    if(dataReg>32767) dataReg -=32768;
    if(dataReg>720) return MARKER_ERRORDIAPAZON;
    if(dataReg<-720) return MARKER_ERRORDIAPAZON;
   break; 
   case 32: //14032
    if(dataReg&0xff00) return MARKER_ERRORDIAPAZON;
    if(dataReg>1) return MARKER_ERRORDIAPAZON;
   break; 
   case 33: //14033
    if(dataReg>12) return MARKER_ERRORDIAPAZON;
    if(dataReg<1) return MARKER_ERRORDIAPAZON;
   break; 
   case 34: //14034
    if(dataReg>5) return MARKER_ERRORDIAPAZON;
    if(dataReg<1) return MARKER_ERRORDIAPAZON;
   break; 
   case 35: //14035
    if(dataReg>7) return MARKER_ERRORDIAPAZON;
    if(dataReg<1) return MARKER_ERRORDIAPAZON;
   break; 
   case 36: //14036
    if(dataReg>23) return MARKER_ERRORDIAPAZON;
   break; 
   case 37: //14037
    if(dataReg>12) return MARKER_ERRORDIAPAZON;
    if(dataReg<1) return MARKER_ERRORDIAPAZON;
   break; 
   case 38: //14038
    if(dataReg>5) return MARKER_ERRORDIAPAZON;
    if(dataReg<1) return MARKER_ERRORDIAPAZON;
   break; 
   case 39: //14039
    if(dataReg>7) return MARKER_ERRORDIAPAZON;
    if(dataReg<1) return MARKER_ERRORDIAPAZON;
   break; 
   case 40: //14040
    if(dataReg>23) return MARKER_ERRORDIAPAZON;
   break; 
   case 41: //14041
    if(dataReg>2) return MARKER_ERRORDIAPAZON;
   break; 
   case 42: //14042
   break; 
  default: return MARKER_OUTPERIMETR;
  }//switch

  return 0;
}//getDOUTBigModbusRegister(int adrReg)
int setPKVBigModbusBit(int x, int y)
{
  UNUSED(x);
  UNUSED(y);
  //получить содержимое регистра
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
int postPKVBigWriteAction(void) {
//action после записи
  if(pkvbigcomponent->operativMarker[0]<0) return 0;//не было записи
  int offsetTempWriteArray = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//найти смещение TempWriteArray
  int countRegister = pkvbigcomponent->operativMarker[1]-pkvbigcomponent->operativMarker[0]+1;
  if(pkvbigcomponent->operativMarker[1]<0) countRegister = 1;

    unsigned char *label_to_time_array = time_edit;
    for(int i=0; i<7; i++) time_edit[i] = time[i];
   // if (copying_time == 0) label_to_time_array = time;
  //  else label_to_time_array = time_copy;
  
  __SETTINGS_FIX *arr = &settings_fix, *arr1 = &settings_fix_edit;
  for(int i=0; i<countRegister; i++) {
  int offset = i+pkvbigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;
  switch(offset) {//индекс регистра 
    case 0://Время активации пароля после простоя
    arr1->timeout_deactivation_password_interface_USB = arr->timeout_deactivation_password_interface_USB = (tempWriteArray[offsetTempWriteArray+i]);
    config_settings_modified |= MASKA_FOR_BIT(BIT_CHANGED_SETTINGS);
    restart_timeout_idle_new_settings = true;
    break;
    case 1://Проверка/установка пароля
    //tempReadArray[i] = 0;
    config_settings_modified |= MASKA_FOR_BIT(BIT_CHANGED_SETTINGS);
    restart_timeout_idle_new_settings = true;
    break;
    case 2://Тайм-аут применения изменений
    arr1->timeout_idle_new_settings = arr->timeout_idle_new_settings = (tempWriteArray[offsetTempWriteArray+i]);
    config_settings_modified |= MASKA_FOR_BIT(BIT_CHANGED_SETTINGS);
    restart_timeout_idle_new_settings = true;
    break;
    case 3://Язык пользовательского интерфейса
    arr1->language = arr->language = (tempWriteArray[offsetTempWriteArray+i]);
    config_settings_modified |= MASKA_FOR_BIT(BIT_CHANGED_SETTINGS);
    restart_timeout_idle_new_settings = true;
    break;
    case 4://
    //tempReadArray[i] = 0;
//    config_settings_modified |= MASKA_FOR_BIT(BIT_CHANGED_SETTINGS);
//    restart_timeout_idle_new_settings = true;
    break;
    case 5://Скорость порта связи
    arr1->baud_RS485 = arr->baud_RS485 = (tempWriteArray[offsetTempWriteArray+i]);
    config_settings_modified |= MASKA_FOR_BIT(BIT_CHANGED_SETTINGS);
    restart_timeout_idle_new_settings = true;
    break;
    case 6://Количество стоп-бит
    arr1->number_stop_bit_RS485 = arr->number_stop_bit_RS485 = (tempWriteArray[offsetTempWriteArray+i]);
    config_settings_modified |= MASKA_FOR_BIT(BIT_CHANGED_SETTINGS);
    restart_timeout_idle_new_settings = true;
    break;
    case 7://Паритет
    arr1->pare_bit_RS485 = arr->pare_bit_RS485 = (tempWriteArray[offsetTempWriteArray+i]);
    config_settings_modified |= MASKA_FOR_BIT(BIT_CHANGED_SETTINGS);
    restart_timeout_idle_new_settings = true;
    break;
//    case 8://Задержка приёма
//    tempReadArray[i] = settings_fix.time_out_1_RS485;
//    break;
//    case 9://Скорость порта связи 2
//    tempReadArray[i] = settings_fix.baud_RS485;
//    break;
//    case 10://Количество стоп-бит 2
//    tempReadArray[i] = settings_fix.number_stop_bit_RS485;
//    break;
//    case 11://Паритет 2
//    tempReadArray[i] = settings_fix.pare_bit_RS485;
//    break;
//    case 12://Задержка приёма 2
//    tempReadArray[i] = settings_fix.time_out_1_RS485;
    case 8://
    case 9://
    case 10://
    case 11://
    case 12://
    // tempReadArray[i] = 0;
//    config_settings_modified |= MASKA_FOR_BIT(BIT_CHANGED_SETTINGS);
//    restart_timeout_idle_new_settings = true;
    break;

    case 13://Адрес устройства в сети
    arr1->address = arr->address = (tempWriteArray[offsetTempWriteArray+i]);
    config_settings_modified |= MASKA_FOR_BIT(BIT_CHANGED_SETTINGS);
    restart_timeout_idle_new_settings = true;
    break;
    case 14://Таймаут конца фрейма
    // tempReadArray[i] = 0;
    config_settings_modified |= MASKA_FOR_BIT(BIT_CHANGED_SETTINGS);
    restart_timeout_idle_new_settings = true;
    break;
    case 15://
    //tempReadArray[i] = 0;
    config_settings_modified |= MASKA_FOR_BIT(BIT_CHANGED_SETTINGS);
    restart_timeout_idle_new_settings = true;
    break;
    case 16://Символ 1 и 2
     arr1->name_of_cell[0] = arr->name_of_cell[0] = (tempWriteArray[offsetTempWriteArray+i]);
// + ((settings_fix.name_of_cell[1]<<8)&0xFF00);
    config_settings_modified |= MASKA_FOR_BIT(BIT_CHANGED_SETTINGS);
    restart_timeout_idle_new_settings = true;
    break;
    case 17://Символ 3 и 4
     arr1->name_of_cell[2] = arr->name_of_cell[2] = (tempWriteArray[offsetTempWriteArray+i]);
//+ ((settings_fix.name_of_cell[3]<<8)&0xFF00);
    config_settings_modified |= MASKA_FOR_BIT(BIT_CHANGED_SETTINGS);
    restart_timeout_idle_new_settings = true;
    break;
    case 18://Символ 5 и 6
     arr1->name_of_cell[4] = arr->name_of_cell[4] = (tempWriteArray[offsetTempWriteArray+i]);
//+ ((settings_fix.name_of_cell[5]<<8)&0xFF00);
    config_settings_modified |= MASKA_FOR_BIT(BIT_CHANGED_SETTINGS);
    restart_timeout_idle_new_settings = true;
    break;
    case 19://Символ 7 и 8
     arr1->name_of_cell[6] = arr->name_of_cell[6] = (tempWriteArray[offsetTempWriteArray+i]);
//+ ((settings_fix.name_of_cell[7]<<8)&0xFF00);
    config_settings_modified |= MASKA_FOR_BIT(BIT_CHANGED_SETTINGS);
    restart_timeout_idle_new_settings = true;
    break;
    case 20://Символ 9 и 10
     arr1->name_of_cell[8] = arr->name_of_cell[8] = (tempWriteArray[offsetTempWriteArray+i]);
//+ ((settings_fix.name_of_cell[9]<<8)&0xFF00);
    config_settings_modified |= MASKA_FOR_BIT(BIT_CHANGED_SETTINGS);
    restart_timeout_idle_new_settings = true;
    break;
    case 21://Символ 11 и 12
     arr1->name_of_cell[10] = arr->name_of_cell[10] = (tempWriteArray[offsetTempWriteArray+i]);
//+ ((settings_fix.name_of_cell[11]<<8)&0xFF00);
    config_settings_modified |= MASKA_FOR_BIT(BIT_CHANGED_SETTINGS);
    restart_timeout_idle_new_settings = true;
    break;
    case 22://Символ 13 и 14
     arr1->name_of_cell[12] = arr->name_of_cell[12] = (tempWriteArray[offsetTempWriteArray+i]);
//+ ((settings_fix.name_of_cell[13]<<8)&0xFF00);
    config_settings_modified |= MASKA_FOR_BIT(BIT_CHANGED_SETTINGS);
    restart_timeout_idle_new_settings = true;
    break;
    case 23://Символ 15 и 16
     arr1->name_of_cell[14] = arr->name_of_cell[14] = (tempWriteArray[offsetTempWriteArray+i]);
//+ ((settings_fix.name_of_cell[15]<<8)&0xFF00);
    config_settings_modified |= MASKA_FOR_BIT(BIT_CHANGED_SETTINGS);
    restart_timeout_idle_new_settings = true;
    break;

    case 24://Год
     *(label_to_time_array + 6) = (tempWriteArray[offsetTempWriteArray+i]);
    _SET_BIT(control_i2c_taskes, TASK_START_WRITE_RTC_BIT);
    _SET_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT);
    break;
    case 25://Месяц
     *(label_to_time_array + 5) = (tempWriteArray[offsetTempWriteArray+i]);
    _SET_BIT(control_i2c_taskes, TASK_START_WRITE_RTC_BIT);
    _SET_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT);
    break;
    case 26://День
     *(label_to_time_array + 4) = (tempWriteArray[offsetTempWriteArray+i]);
    _SET_BIT(control_i2c_taskes, TASK_START_WRITE_RTC_BIT);
    _SET_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT);
    break;
    case 27://Час
     *(label_to_time_array + 3) = (tempWriteArray[offsetTempWriteArray+i]);
    _SET_BIT(control_i2c_taskes, TASK_START_WRITE_RTC_BIT);
    _SET_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT);
    break;
    case 28://Минуты
     *(label_to_time_array + 2) = (tempWriteArray[offsetTempWriteArray+i]);
    _SET_BIT(control_i2c_taskes, TASK_START_WRITE_RTC_BIT);
    _SET_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT);
    break;
    case 29://Секунды
     *(label_to_time_array + 1) = (tempWriteArray[offsetTempWriteArray+i]);
    _SET_BIT(control_i2c_taskes, TASK_START_WRITE_RTC_BIT);
    _SET_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT);
    break;
    case 30://Сотые секунды
     *(label_to_time_array + 0) = (tempWriteArray[offsetTempWriteArray+i]);
    _SET_BIT(control_i2c_taskes, TASK_START_WRITE_RTC_BIT);
    _SET_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT);
    break;

    case 31://Часовой пояс
    case 32://Переход на Зимнее/Летнее время
    case 33://Месяц перехода на Летнее время
    case 34://Неделя месяца перехода на Летнее время
    case 35://День недели перехода на Летнее время
    case 36://Час недели перехода на Летнее время
    case 37://Месяц перехода на Зимнее время
    case 38://Неделя месяца перехода на Зимнее время
    case 39://День недели перехода на Зимнее время
    case 40://Час недели перехода на Зимнее время
    case 41://Синхронизация времени
    case 42://Время утраты синхронизации
    //tempReadArray[i] = 0;
//    config_settings_modified |= MASKA_FOR_BIT(BIT_CHANGED_SETTINGS);
//    restart_timeout_idle_new_settings = true;
    break;
 }//switch
  }//for
 return 0;
}//

int privatePKVBigGetReg2(int adrReg)
{
  //проверить внешний периметр
  int count_register = REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
