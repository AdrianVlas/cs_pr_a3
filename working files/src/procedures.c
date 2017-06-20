#include "header.h"

const uint8_t month_names[12*3] = "JanFebMarAprMayJunJulAugSepOctNovDec";

/*****************************************************/
//Функція, яка визначає кількість біт затримки, який допускається між байтами у RS-485 згідно з визначеними настройками
/*****************************************************/
void calculate_namber_bit_waiting_for_rs_485(void)
{
  unsigned int number_bits_rs_485_waiting_tmp = 10;
  
  //Підраховуємо кількість біт у байті
  if (settings_fix.pare_bit_RS485 > 0) number_bits_rs_485_waiting_tmp++;
  if (settings_fix.number_stop_bit_RS485 > 0) number_bits_rs_485_waiting_tmp++;
  
  //Врахування швидкості
  unsigned int multiplicator;
  switch (settings_fix.baud_RS485)
  {
  case 0:
    {
      multiplicator = 12; //9600
      break;
    }
  case 1:
    {
      multiplicator = 8;  //14400
      break;
    }
  case 2:
    {
      multiplicator = 6;  //19200
      break;
    }
  case 3:
    {
      multiplicator = 4;  //28800
      break;
    }
  case 4:
    {
      multiplicator = 3;  //38400
      break;
    }
  case 5:
    {
      multiplicator = 2;  //57600
      break;
    }
  default:
    {
      multiplicator = 1;  //115200
      break;
    }
  }
  number_bits_rs_485_waiting_tmp *= (multiplicator*settings_fix.time_out_1_RS485);
  number_bits_rs_485_waiting_tmp /= 10;
  
  number_bits_rs_485_waiting = number_bits_rs_485_waiting_tmp;
}
/*****************************************************/

///******************************************************
//Відновлення триґерних функцій
//******************************************************/
//void restore_trigger_functions(unsigned int *active_functions_point)
//{
//  active_functions[RANG_DT1_OUT >> 5] |= _CHECK_SET_BIT(active_functions_point, RANG_DT1_OUT);
//  active_functions[RANG_DT2_OUT >> 5] |= _CHECK_SET_BIT(active_functions_point, RANG_DT2_OUT);
//  active_functions[RANG_DT3_OUT >> 5] |= _CHECK_SET_BIT(active_functions_point, RANG_DT3_OUT);
//  active_functions[RANG_DT4_OUT >> 5] |= _CHECK_SET_BIT(active_functions_point, RANG_DT4_OUT);
//}
///*****************************************************/

/*****************************************************/
//Функція зміни інформації по діагностиці
/*****************************************************/
void changing_diagnostyka_state(void)
{
  /*****
  Визначаємо новий стан діагностики
  
  Алгоритм:
  - Копіюємо у тимчасові масиви біти, які треба скинути і які треба виставити у 
    діагностиці
  - Після цього копіювання більш пріоритетні ситстеми можуть добавляти (не 
    скидають ніколи!!!) нові біти у глобальні масиви
  - Біти , які ми будуть скидалися/встановлюватися очищаємо з глобальних масивів
    (якщо в процесі цього алгоритму більшпріоритетні системи добавили чи 
    добавлятимуть нові біти, то вони не скинуться, а опрацюються при наступному 
    виклику цієї функції)

  - Спочатку очищаємо біти а потім встановлюємо, бо фіксація події має більший 
    пріоритет за очищення
  *****/
  unsigned int clear_diagnostyka_tmp[2], set_diagnostyka_tmp[2];
  
  clear_diagnostyka_tmp[0] = clear_diagnostyka[0];
  clear_diagnostyka_tmp[1] = clear_diagnostyka[1];

  set_diagnostyka_tmp[0] = set_diagnostyka[0];
  set_diagnostyka_tmp[1] = set_diagnostyka[1];
    
  diagnostyka[0] &= (unsigned int)(~clear_diagnostyka_tmp[0]); 
  diagnostyka[0] |= set_diagnostyka_tmp[0]; 

  diagnostyka[1] &= (unsigned int)(~clear_diagnostyka_tmp[1]); 
  diagnostyka[1] |= set_diagnostyka_tmp[1]; 

  clear_diagnostyka[0] &= (unsigned int)(~clear_diagnostyka_tmp[0]);
  clear_diagnostyka[1] &= (unsigned int)(~clear_diagnostyka_tmp[1]);
  
  set_diagnostyka[0] &= (unsigned int)(~set_diagnostyka_tmp[0]);
  set_diagnostyka[1] &= (unsigned int)(~set_diagnostyka_tmp[1]);
  /*****/
  
  //Визначаємо, чи відбулися зміни
  unsigned int value_changes[2];
  value_changes[0] = diagnostyka_before[0] ^ diagnostyka[0];
  value_changes[1] = diagnostyka_before[1] ^ diagnostyka[1];
  
  /*
  У реєстраторі програмних подій має реєструватися тільки перехід з пасивного стану у активний
  таких подій як "Старт пристр." і "Рестарт пристр."
  тому перехід з активного у пачсивний ми ігноруємо і крім того затираємо біти, які його "засигналізували"
  */
  
  /*****/
  //Подія "Старт пристр."
  /*****/
  if (_CHECK_SET_BIT(value_changes, EVENT_START_SYSTEM_BIT) != 0)
  {
    //Зафіксовано що подія "Старт пристр." змінила свій стан
    if (_CHECK_SET_BIT(diagnostyka, EVENT_START_SYSTEM_BIT) == 0)
    {
      /*
      Новий стан події " Старт пристр." є неактивний стан
      Тому робимо так, щоб ця подія не попала у реєстратор програмних подій таким операціями
      - знімаємо встановлений біт про зміну стану діагностики
      - знімаємо повідомлення, що у попередньому стані діагностики ця подія була активною
      - у текучому стані діагностики нічого міняти не треба, бо цей сигнал є неактивним
      */
      _CLEAR_BIT(value_changes, EVENT_START_SYSTEM_BIT);
      _CLEAR_BIT(diagnostyka_before, EVENT_START_SYSTEM_BIT);
    }
  }
  /*****/
  
  /*****/
  //Подія "Рестарт пристр."
  /*****/
  if (_CHECK_SET_BIT(value_changes, EVENT_RESTART_SYSTEM_BIT) != 0)
  {
    //Зафіксовано що подія "Рестарт пристр." змінила свій стан
    if (_CHECK_SET_BIT(diagnostyka, EVENT_RESTART_SYSTEM_BIT) == 0)
    {
      /*
      Новий стан події "Рестарт пристр." є неактивний стан
      Тому робимо так, щоб ця подія не попала у реєстратор програмних подій таким операціями
      - знімаємо встановлений біт про зміну стану діагностики
      - знімаємо повідомлення, що у попередньому стані діагностики ця подія була активною
      - у текучому стані діагностики нічого міняти не треба, бо цей сигнал є неактивним
      */
      _CLEAR_BIT(value_changes, EVENT_RESTART_SYSTEM_BIT);
      _CLEAR_BIT(diagnostyka_before, EVENT_RESTART_SYSTEM_BIT);
    }
  }
  /*****/
        
  /*****/
  //Подія "Пр.Рестарт пр."
  /*****/
  if (_CHECK_SET_BIT(value_changes, EVENT_SOFT_RESTART_SYSTEM_BIT) != 0)
  {
    //Зафіксовано що подія "Пр.Рестарт пр." змінила свій стан
    if (_CHECK_SET_BIT(diagnostyka, EVENT_SOFT_RESTART_SYSTEM_BIT) == 0)
    {
      /*
      Новий стан події "Пр.Рестарт пр." є неактивний стан
      Тому робимо так, щоб ця подія не попала у реєстратор програмних подій таким операціями
      - знімаємо встановлений біт про зміну стану діагностики
      - знімаємо повідомлення, що у попередньому стані діагностики ця подія була активною
      - у текучому стані діагностики нічого міняти не треба, бо цей сигнал є неактивним
      */
      _CLEAR_BIT(value_changes, EVENT_SOFT_RESTART_SYSTEM_BIT);
      _CLEAR_BIT(diagnostyka_before, EVENT_SOFT_RESTART_SYSTEM_BIT);
    }
  }
  /*****/
        
  /*****/
  //Подія "Зм.конфіругації"
  /*****/
  if (_CHECK_SET_BIT(value_changes, EVENT_CHANGE_CONFIGURATION_BIT) != 0)
  {
    //Зафіксовано що подія "Зм.конфіругації" змінила свій стан
    if (_CHECK_SET_BIT(diagnostyka, EVENT_CHANGE_CONFIGURATION_BIT) == 0)
    {
      /*
      Новий стан події "Зм.конфіругації" є неактивний стан
      Тому робимо так, щоб ця подія не попала у реєстратор програмних подій таким операціями
      - знімаємо встановлений біт про зміну стану діагностики
      - знімаємо повідомлення, що у попередньому стані діагностики ця подія була активною
      - у текучому стані діагностики нічого міняти не треба, бо цей сигнал є неактивним
      */
      _CLEAR_BIT(value_changes, EVENT_CHANGE_CONFIGURATION_BIT);
      _CLEAR_BIT(diagnostyka_before, EVENT_CHANGE_CONFIGURATION_BIT);
    }
  }
  /*****/
        
  /*****/
  //Подія "Зм.налаштувань"
  /*****/
  if (_CHECK_SET_BIT(value_changes, EVENT_CHANGE_SETTINGS_BIT) != 0)
  {
    //Зафіксовано що подія "Зм.налаштувань" змінила свій стан
    if (_CHECK_SET_BIT(diagnostyka, EVENT_CHANGE_SETTINGS_BIT) == 0)
    {
      /*
      Новий стан події "Зм.налаштувань" є неактивний стан
      Тому робимо так, щоб ця подія не попала у реєстратор програмних подій таким операціями
      - знімаємо встановлений біт про зміну стану діагностики
      - знімаємо повідомлення, що у попередньому стані діагностики ця подія була активною
      - у текучому стані діагностики нічого міняти не треба, бо цей сигнал є неактивним
      */
      _CLEAR_BIT(value_changes, EVENT_CHANGE_SETTINGS_BIT);
      _CLEAR_BIT(diagnostyka_before, EVENT_CHANGE_SETTINGS_BIT);
    }
  }
  /*****/
        
  /*****/
  //Подія "Зуп.пристр."
  /*****/
  /*
  У реєстраторі програмних подій має реєструватися тільки перехід з пасивного стану у активний
  таких події як "Зуп.пристр." і ця подія не має бути активною у текучій діагностиці,
  бо це, фактично, подія, яка мала місце до останнього включення приладу в роботу.
  Тобто це подія "попереднього сеансу роботи"
  тому перехід з пасивного у фіксуємо ми фіксуємо і зразу затираємо цей біт у теперішній діагностіці,
  яка після цього буде зкопійомана у масив, який відповідає за попередній стан діагностики, так і у масив
  діагностики, який відповідає за текучий стан подій діагностики
  */
  if (_CHECK_SET_BIT(value_changes, EVENT_STOP_SYSTEM_BIT) != 0)
  {
    //Зафіксовано що подія "Зуп.пристр." змінила свій стан
    if (_CHECK_SET_BIT(diagnostyka, EVENT_STOP_SYSTEM_BIT) != 0)
    {
      /*
      Cтан події "Зуп.пристр." встановився
      Тому робимо такі операції, щоб вона попара у реєстратора програмних подій, але не відображалася у діагностиці
      - знімаємо встановлений біт у масиві, який зараз буде копіюватися у масив попереднього стану
      - знімаємо встановлений біт у масиві, який відповідає за текучий стан подій діагностики
      */
      _CLEAR_BIT(diagnostyka, EVENT_STOP_SYSTEM_BIT);
    }
  }
  /*****/
  
  //Визначаємо кількість доступних комірок у буфері для реєстратора програмних подій
  int32_t number_empty_cells;
  uint32_t head = head_fifo_buffer_pr_err_records, tail = tail_fifo_buffer_pr_err_records;
  number_empty_cells = (int32_t)(tail - head);
  if (
      (number_empty_cells == 0) &&
      (_CHECK_SET_BIT(diagnostyka, ERROR_PR_ERR_OVERLOAD_BIT) == 0)
     )
  {
    number_empty_cells = MAX_NUMBER_RECORDS_PR_ERR_INTO_BUFFER;
  }
  while (number_empty_cells < 0) number_empty_cells += MAX_NUMBER_RECORDS_PR_ERR_INTO_BUFFER;

  if (
      (
       (value_changes[0] != 0) ||
       (value_changes[1] != 0)
      )
      ||
      (
       (_CHECK_SET_BIT(diagnostyka, ERROR_PR_ERR_OVERLOAD_BIT) != 0) &&
       (number_empty_cells > 1)  
      )
     )
  {
    /***
    Час фіксації зміни у діагностиці
    ***/
    uint8_t *label_to_time_array;
    if (copying_time == 0) label_to_time_array = time;
    else label_to_time_array = time_copy;
    /***/
        
    /***
    Фіксація самих подій
    ***/
    size_t i = 0;
    while (
           (
            (number_empty_cells == 1) &&
            (_CHECK_SET_BIT(diagnostyka, ERROR_PR_ERR_OVERLOAD_BIT) == 0)  
           )
           ||
           (i < (8*sizeof(value_changes))) 
           ||
           (
            (_CHECK_SET_BIT(diagnostyka, ERROR_PR_ERR_OVERLOAD_BIT) != 0) &&
            (number_empty_cells > 1)
           )
          )
    {
      size_t event_number;
      uint32_t event_state;
      uint32_t fix_event = false;
      
      if (number_empty_cells <= 0) break;
      else if (
               (number_empty_cells == 1) &&
               (_CHECK_SET_BIT(diagnostyka, ERROR_PR_ERR_OVERLOAD_BIT) == 0)  
              )
      {
        event_number = ERROR_PR_ERR_OVERLOAD_BIT + 1;
        event_state = true;
        fix_event = true;

        _SET_BIT(diagnostyka, ERROR_PR_ERR_OVERLOAD_BIT);
        _SET_BIT(value_changes, ERROR_PR_ERR_OVERLOAD_BIT);
      }
      else if (i < 8*sizeof(value_changes))
      {
        if (_CHECK_SET_BIT(value_changes, i) != 0)
        {
          event_number = i + 1;
          event_state = (i != EVENT_STOP_SYSTEM_BIT) ? (_CHECK_SET_BIT(diagnostyka, i) != 0) : true;
          fix_event = true;
        }
          
        i++;
      }
      else
      {     
        event_number = ERROR_PR_ERR_OVERLOAD_BIT + 1;
        event_state = false;
        fix_event = true;

        _CLEAR_BIT(diagnostyka, ERROR_PR_ERR_OVERLOAD_BIT);
        _SET_BIT(value_changes, ERROR_PR_ERR_OVERLOAD_BIT);
      }  
      
      if (fix_event == true)
      {
        /***
        Визначаємо індекс у масиві буфері програмних помилок з якого треба почати заповнювати дані
        ***/
        uint32_t index_into_buffer_pr_err = head*SIZE_ONE_RECORD_PR_ERR;
        /***/
          
        /***
        Формуємо сам запис
        ***/
        //Помічаємо мітку початку запису
        buffer_pr_err_records[index_into_buffer_pr_err++] = LABEL_START_RECORD_PR_ERR;
        //Дата і час події
        for(size_t j = 0; j < 7; j++) buffer_pr_err_records[index_into_buffer_pr_err++] = *(label_to_time_array + j);
        //Подія (двобайтна) і її значення
        buffer_pr_err_records[index_into_buffer_pr_err++] =   event_number       & 0xff; /*Номер починається з "1" */
        buffer_pr_err_records[index_into_buffer_pr_err++] = ((event_number >> 8) & 0x7f) | (event_state << 7);
        /***/
          
        /***
        Дії по завершенню формування запису
        ***/
        //Кількість комірок доступних для запису
        number_empty_cells--;
          
        //Head буферу FIFO
        head++;
        while (head >= MAX_NUMBER_RECORDS_PR_ERR_INTO_BUFFER) head -= MAX_NUMBER_RECORDS_PR_ERR_INTO_BUFFER;
        /***/
      }
    }
    head_fifo_buffer_pr_err_records = head;
    /***/
    
    /***
    Фіксуємо попередній стан, який ми вже записали і відносно якого будемо визначати нові зміни
    ***/
    diagnostyka_before[0] = diagnostyka[0];
    diagnostyka_before[1] = diagnostyka[1];
    /***/
  }
}
/*****************************************************/

/*****************************************************/
//Підрахунок кількості втановлених одиничок у області пам'яті початок якої визначається вказівником source
/*****************************************************/
unsigned int count_number_set_bit(unsigned int* source, unsigned int total_number)
{
  unsigned int count = 0;
  unsigned int offset, shift;
  
  for (unsigned int i = 0; i < total_number; i++)  
  {
    offset = i >> 5; //Це є, фактично, ділення на 32
    shift  = (i & (32 - 1)); //Це є, фактично, визначення остачі від ділення на 32
    if ( ( (*(source + offset))  & ((unsigned int)(1 << shift)) ) != 0 ) count++;
  }

  return count;
}
/*****************************************************/

/*****************************************************/
//Контроль достовірності конфігурації
/*****************************************************/
void control_config(unsigned int modified)
{
  uint8_t crc_config_tmp = 0, temp_value;
  uint8_t  *point_1 = (unsigned char*)(&current_config_prt); // з цими даними працюють захисти
  uint8_t  *point_2 = (unsigned char*)(&current_config);
  unsigned int i = 0, difference = 0;
  while ((difference == 0) && (i < sizeof(__CONFIG)))
  {
    //Контроль контрольної суми кофігурації для захистів
    temp_value = *(point_1++);
    crc_config_tmp += temp_value;

    //Контроль конфігурації для захистів з конфігурацією-контейнером
    if ((modified & MASKA_CHANGED_CONFIGURATION) == 0)
    {
      if (temp_value != *(point_2++)) difference = 0xff;
    }

    i++;
  }
  
  if ((difference == 0) && (crc_config == crc_config_tmp))
  {
    //Контроль достовірності конфігурації пройшов успішно
    
    //Скидаємо повідомлення у слові діагностики
    _SET_BIT(clear_diagnostyka, ERROR_CONFIG_EEPROM_CONTROL_BIT);
  }
  else
  {
    //Контроль достовірності конфігурації не пройшов

    //Виствляємо повідомлення у слові діагностики
    _SET_BIT(set_diagnostyka, ERROR_CONFIG_EEPROM_CONTROL_BIT);
  }
}
/*****************************************************/

/*****************************************************/
//Контроль достовірності настройок
/*****************************************************/
void control_settings(unsigned int modified)
{
  uint8_t crc_settings_tmp = 0, temp_value;
  uint8_t  *point_1 = NULL, *point_2 = NULL; 
  unsigned int difference = 0;

  size_t size_of_block = 0;
  uint32_t n_item = 0;
  unsigned int item = 0, shift = 0;
  __id_fb block = _ID_FB_FIRST_ALL;
  while(
        (difference == 0) &&
        (block < _ID_FB_LAST_ALL)
       )
  {
    if (shift == 0)
    {
      //Визначаємо розмір нового блоку
      switch (block)
      {
      case ID_FB_CONTROL_BLOCK:
        {
          if (item == 0)
          {
            size_of_block = sizeof(__SETTINGS_FIX);
            n_item = 1;
          }
          
          if (modified == 0) point_2 = (uint8_t *)(&settings_fix);
          point_1 = (uint8_t *)(&settings_fix_prt);
          
          break;
        }
      case ID_FB_INPUT:
        {
          if (item == 0)
          {
            size_of_block = sizeof(__settings_for_INPUT);
            n_item = current_config_prt.n_input;
          }

          if  (modified == 0) point_2 = (uint8_t *)(((__settings_for_INPUT*)sca_of_p[ID_FB_INPUT - _ID_FB_FIRST_VAR]) + item);
          point_1 = (uint8_t *)(&(((__LN_INPUT*)spca_of_p_prt[ID_FB_INPUT - _ID_FB_FIRST_VAR]) + item)->settings) ;

          break;
        }
      case ID_FB_OUTPUT:
      case ID_FB_LED:
        {
          if (item == 0)
          {
            size_of_block = sizeof(__settings_for_OUTPUT_LED);
            n_item = (block == ID_FB_OUTPUT) ? current_config_prt.n_output : current_config_prt.n_led;
          }

          if  (modified == 0) point_2 = (uint8_t *)(((__settings_for_OUTPUT_LED*)sca_of_p[block - _ID_FB_FIRST_VAR]) + item);
          point_1 = (uint8_t *)(&(((__LN_OUTPUT_LED*)spca_of_p_prt[block - _ID_FB_FIRST_VAR]) + item)->settings) ;

          break;
        }
      case ID_FB_BUTTON:
        {
          if (item == 0)
          {
            size_of_block = 0;
            n_item = current_config_prt.n_button;
          }

          if  (modified == 0) point_2 = NULL;
          point_1 = NULL;

          break;
        }
      case ID_FB_ALARM:
        {
          if (item == 0)
          {
            size_of_block = sizeof(__settings_for_ALARM);
            n_item = current_config_prt.n_alarm;
          }

          if  (modified == 0) point_2 = (uint8_t *)(((__settings_for_ALARM*)sca_of_p[ID_FB_ALARM - _ID_FB_FIRST_VAR]) + item);
          point_1 = (uint8_t *)(&(((__LN_ALARM*)spca_of_p_prt[ID_FB_ALARM - _ID_FB_FIRST_VAR]) + item)->settings) ;

          break;
        }
      case ID_FB_GROUP_ALARM:
        {
          if (item == 0)
          {
            size_of_block = sizeof(__settings_for_GROUP_ALARM);
            n_item = current_config_prt.n_group_alarm;
          }

          if  (modified == 0) point_2 = (uint8_t *)(((__settings_for_GROUP_ALARM*)sca_of_p[ID_FB_GROUP_ALARM - _ID_FB_FIRST_VAR]) + item);
          point_1 = (uint8_t *)(&(((__LN_GROUP_ALARM*)spca_of_p_prt[ID_FB_GROUP_ALARM - _ID_FB_FIRST_VAR]) + item)->settings) ;

          break;
        }
      case ID_FB_AND:
        {
          if (item == 0)
          {
            size_of_block = sizeof(__settings_for_AND);
            n_item = current_config_prt.n_and;
          }

          if  (modified == 0) point_2 = (uint8_t *)(((__settings_for_AND*)sca_of_p[ID_FB_AND - _ID_FB_FIRST_VAR]) + item);
          point_1 = (uint8_t *)(&(((__LN_AND*)spca_of_p_prt[ID_FB_AND - _ID_FB_FIRST_VAR]) + item)->settings) ;

          break;
        }
      case ID_FB_OR:
        {
          if (item == 0)
          {
            size_of_block = sizeof(__settings_for_OR);
            n_item = current_config_prt.n_or;
          }

          if  (modified == 0) point_2 = (uint8_t *)(((__settings_for_OR*)sca_of_p[ID_FB_OR - _ID_FB_FIRST_VAR]) + item);
          point_1 = (uint8_t *)(&(((__LN_OR*)spca_of_p_prt[ID_FB_OR - _ID_FB_FIRST_VAR]) + item)->settings) ;

          break;
        }
      case ID_FB_XOR:
        {
          if (item == 0)
          {
            size_of_block = sizeof(__settings_for_XOR);
            n_item = current_config_prt.n_xor;
          }

          if  (modified == 0) point_2 = (uint8_t *)(((__settings_for_XOR*)sca_of_p[ID_FB_XOR - _ID_FB_FIRST_VAR]) + item);
          point_1 = (uint8_t *)(&(((__LN_XOR*)spca_of_p_prt[ID_FB_XOR - _ID_FB_FIRST_VAR]) + item)->settings) ;

          break;
        }
      case ID_FB_NOT:
        {
          if (item == 0)
          {
            size_of_block = sizeof(__settings_for_NOT);
            n_item = current_config_prt.n_not;
          }

          if  (modified == 0) point_2 = (uint8_t *)(((__settings_for_NOT*)sca_of_p[ID_FB_NOT - _ID_FB_FIRST_VAR]) + item);
          point_1 = (uint8_t *)(&(((__LN_NOT*)spca_of_p_prt[ID_FB_NOT - _ID_FB_FIRST_VAR]) + item)->settings) ;

          break;
        }
      case ID_FB_TIMER:
        {
          if (item == 0)
          {
            size_of_block = sizeof(__settings_for_TIMER);
            n_item = current_config_prt.n_timer;
          }

          if  (modified == 0) point_2 = (uint8_t *)(((__settings_for_TIMER*)sca_of_p[ID_FB_TIMER - _ID_FB_FIRST_VAR]) + item);
          point_1 = (uint8_t *)(&(((__LN_TIMER*)spca_of_p_prt[ID_FB_TIMER - _ID_FB_FIRST_VAR]) + item)->settings);

          break;
        }
      case ID_FB_TRIGGER:
        {
          if (item == 0)
          {
            size_of_block = sizeof(__settings_for_TRIGGER);
            n_item = current_config_prt.n_trigger;
          }

          if  (modified == 0) point_2 = (uint8_t *)(((__settings_for_TRIGGER*)sca_of_p[ID_FB_TRIGGER - _ID_FB_FIRST_VAR]) + item);
          point_1 = (uint8_t *)(&(((__LN_TRIGGER*)spca_of_p_prt[ID_FB_TRIGGER - _ID_FB_FIRST_VAR]) + item)->settings) ;

          break;
        }
      case ID_FB_MEANDER:
        {
          if (item == 0)
          {
            size_of_block = sizeof(__settings_for_MEANDER);
            n_item = current_config_prt.n_meander;
          }

          if  (modified == 0) point_2 = (uint8_t *)(((__settings_for_MEANDER*)sca_of_p[ID_FB_MEANDER - _ID_FB_FIRST_VAR]) + item);
          point_1 = (uint8_t *)(&(((__LN_MEANDER*)spca_of_p_prt[ID_FB_MEANDER - _ID_FB_FIRST_VAR]) + item)->settings) ;

          break;
        }
      case ID_FB_TU:
        {
          if (item == 0)
          {
            size_of_block = sizeof(__settings_for_TU);
            n_item = current_config_prt. n_tu;
          }

          if  (modified == 0) point_2 = (uint8_t *)(((__settings_for_TU*)sca_of_p[ID_FB_TU - _ID_FB_FIRST_VAR]) + item);
          point_1 = (uint8_t *)(&(((__LN_TU*)spca_of_p_prt[ID_FB_TU - _ID_FB_FIRST_VAR]) + item)->settings) ;

          break;
        }
      case ID_FB_TS:
        {
          if (item == 0)
          {
            size_of_block = sizeof(__settings_for_TS);
            n_item = current_config_prt.n_ts;
          }

          if  (modified == 0) point_2 = (uint8_t *)(((__settings_for_TS*)sca_of_p[ID_FB_TS - _ID_FB_FIRST_VAR]) + item);
          point_1 = (uint8_t *)(&(((__LN_TS*)spca_of_p_prt[ID_FB_TS - _ID_FB_FIRST_VAR]) + item)->settings) ;

          break;
        }
      case ID_FB_EVENT_LOG:
        {
          if (item == 0)
          {
            size_of_block = sizeof(__LOG_INPUT);
            size_of_block *= current_config_prt.n_log*LOG_SIGNALS_IN;
            n_item = 1;
          }

          if  (modified == 0) point_2 = (uint8_t *)((__LOG_INPUT*)sca_of_p[ID_FB_EVENT_LOG - _ID_FB_FIRST_VAR]);
          point_1 = (uint8_t *)((__LOG_INPUT*)spca_of_p_prt[ID_FB_EVENT_LOG - _ID_FB_FIRST_VAR] + 1);

          break;
        }
      default:
        {
          //Якщо сюди дійшла програма, значить відбулася недопустива помилка, тому треба зациклити програму, щоб вона пішла на перезагрузку
          total_error_sw_fixed(5);
        }
      }
    }
      
    if ((size_of_block != 0) && (n_item != 0))
    {
      //Контроль контрольної суми налаштувань для захистів
      if (
          (block != ID_FB_EVENT_LOG) ||
          ((shift % sizeof(__LOG_INPUT)) != (sizeof(__LOG_INPUT) - 1))  
         )   
      {
        temp_value = *(point_1 + shift);
      }
      else 
      {
        temp_value = *(point_1 + shift) & (uint8_t)(~(MASKA_PARAM_INTERNAL_BITS << (SFIFT_PARAM_INTERNAL_BITS % 8)));
      }
      crc_settings_tmp += temp_value;

      //Контроль налаштувань для захистів з налаштуваннями-контейнером
      if  (modified == 0)
      {
        if (point_2 != NULL)
        {
          if (temp_value != *(point_2 + shift)) difference = 0xff;
        }
        else
        {
          //Якщо сюди дійшла програма, значить відбулася недопустива помилка, тому треба зациклити програму, щоб вона пішла на перезагрузку
          total_error_sw_fixed(61);
        }
      }
          
      if ((++shift) >= size_of_block)
      {
        shift = 0;
        if ((++item) >= n_item)
        {
          item = 0;
          block++;
          size_of_block = 0;
          n_item = 0;
        }
      }
    }
    else 
    {
      size_of_block = 0;
      n_item = 0;
          
      shift = 0;
      item = 0;
      block++;
    }
  }
  
  if ((difference == 0) && (crc_settings == crc_settings_tmp))
  {
    //Контроль достовірності таблиці настройок пройшов успішно
    
    //Скидаємо повідомлення у слові діагностики
    _SET_BIT(clear_diagnostyka, ERROR_SETTINGS_EEPROM_CONTROL_BIT);
  }
  else
  {
    //Контроль достовірності таблиці настройок не пройшов

    //Виствляємо повідомлення у слові діагностики
    _SET_BIT(set_diagnostyka, ERROR_SETTINGS_EEPROM_CONTROL_BIT);
  }
}
/*****************************************************/

/*****************************************************/
//Контроль достовірності юстування
/*****************************************************/
void control_ustuvannja(void)
{
  unsigned char crc_ustuvannja_tmp = 0, temp_value_1, temp_value_2;
  unsigned char  *point_1; 
  unsigned char  *point_2; 
  unsigned int i = 0, difference = 0;

  /*
  У контрольу суму входить індетифікатор типу набору юстуючих коефіцієнтів,
  який займає розмір типу unsigned int
  */
  unsigned int adjustment_id_tmp = ADJUSTMENT_ID;
  point_1 = (unsigned char*)(&adjustment_id_tmp); 
  while (i < sizeof(unsigned int))
  {
    temp_value_1 = *(point_1);
    crc_ustuvannja_tmp += temp_value_1;
    point_1++;
    i++;
  }
  
  point_1 = (unsigned char*)(&ustuvannja); 
  point_2 = (unsigned char*)(&ustuvannja_meas);
  i = 0;
  while ((difference == 0) && (i < sizeof(ustuvannja)))
  {
    temp_value_1 = *(point_1);
    temp_value_2 = *(point_2);
    crc_ustuvannja_tmp += temp_value_1;
    if (temp_value_1 != temp_value_2) difference = 0xff;
    point_1++;
    point_2++;
    i++;
  }

  /*
  Не треба контролювати ідентичність серійног номеру, який працює з вимірювально системою,
  чи системою захистів, чи ще якоюсь високопріоритетною і високонадійною від завад системою,
  бо його просто не існує
  */
  point_1 = (unsigned char*)(&serial_number_dev); 
  i = 0;
  while ((difference == 0) && (i < sizeof(serial_number_dev)))
  {
    temp_value_1 = *(point_1);
    crc_ustuvannja_tmp += temp_value_1;
    point_1++;
    i++;
  }
  
  if ((difference == 0) && (crc_ustuvannja == crc_ustuvannja_tmp))
  {
    //Контроль достовірності юстування пройшов успішно
    
    //Скидаємо повідомлення у слові діагностики
    _SET_BIT(clear_diagnostyka, ERROR_USTUVANNJA_EEPROM_CONTROL_BIT);
  }
  else
  {
    //Контроль достовірності юстування не пройшов

    //Виствляємо повідомлення у слові діагностики
    _SET_BIT(set_diagnostyka, ERROR_USTUVANNJA_EEPROM_CONTROL_BIT);
  }
}
/*****************************************************/

/*****************************************************/
//Контроль достовірності триґерної інформації
/*****************************************************/
void control_trg_func(void)
{
  unsigned char crc_trg_func_tmp = 0;

  for (__id_fb block_tmp = _ID_FB_FIRST_ALL; block_tmp < _ID_FB_LAST_ALL; block_tmp++)
  {
    switch (block_tmp)
    {
    case ID_FB_OUTPUT:
    case ID_FB_LED:
      {
        size_t n_max_block = ((block_tmp == ID_FB_OUTPUT) ? current_config_prt.n_output : current_config_prt.n_led);
        size_t n_max = DIV_TO_HIGHER(TRIGGER_D_TRIGGER_TOTAL, 8);
        for (size_t n_block = 0; n_block < n_max_block; n_block++)
        {
          for (size_t n = 0; n < n_max; n++) crc_trg_func_tmp += (((__LN_OUTPUT_LED*)spca_of_p_prt[block_tmp - _ID_FB_FIRST_VAR]) + n_block)->d_trigger_state_tmp[n];
        }
        break;
      }
    case ID_FB_ALARM:
      {
        size_t n_max_block = current_config_prt.n_alarm;
        size_t n_max = DIV_TO_HIGHER(ALARM_D_TRIGGER_TOTAL, 8);
        for (size_t n_block = 0; n_block < n_max_block; n_block++)
        {
          for (size_t n = 0; n < n_max; n++) crc_trg_func_tmp += (((__LN_ALARM*)spca_of_p_prt[ID_FB_ALARM - _ID_FB_FIRST_VAR]) + n_block)->d_trigger_state_tmp[n];
        }
        break;
      }
    case ID_FB_TRIGGER:
      {
        size_t n_max_block = current_config_prt.n_trigger;
        size_t n_max = DIV_TO_HIGHER(TRIGGER_D_TRIGGER_TOTAL, 8);
        for (size_t n_block = 0; n_block < n_max_block; n_block++)
        {
          for (size_t n = 0; n < n_max; n++) crc_trg_func_tmp += (((__LN_TRIGGER*)spca_of_p_prt[ID_FB_TRIGGER - _ID_FB_FIRST_VAR]) + n_block)->d_trigger_state_tmp[n];
        }
        break;
      }
    }
  }
  
  if (crc_trg_func == crc_trg_func_tmp)
  {
    //Контроль достовірності юстування пройшов успішно
    
    //Скидаємо повідомлення у слові діагностики
    _SET_BIT(clear_diagnostyka, ERROR_TRG_FUNC_EEPROM_CONTROL_BIT);
  }
  else
  {
    //Контроль достовірності юстування не пройшов

    //Виствляємо повідомлення у слові діагностики
    _SET_BIT(set_diagnostyka, ERROR_TRG_FUNC_EEPROM_CONTROL_BIT);
  }
}
/*****************************************************/

/*****************************************************/
//Контроль достовірності інформації по реєстраторах
/*****************************************************/
unsigned int control_info_rejestrator(__INFO_REJESTRATOR* info_rejestrator_point, uint8_t crc_info_rejestrator)
{
  unsigned int result;
  unsigned char crc_info_rejestrator_tmp = 0, temp_value_1;
  unsigned char  *point = (unsigned char*)(info_rejestrator_point); 
  unsigned int i = 0;
  while (i < sizeof(__INFO_REJESTRATOR))
  {
    temp_value_1 = *(point);
    crc_info_rejestrator_tmp += temp_value_1;
    point++;
    i++;
  }
  
  if (crc_info_rejestrator == crc_info_rejestrator_tmp)
  {
    //Контроль достовірності реєстратора пройшов успішно
    result = 1;    
  }
  else
  {
    //Контроль достовірності реєстратора не пройшов
    result = 0;    
  }
  
  return result;
}
/*****************************************************/

/*****************************************************/
//Визначення номеру місяця з константи __DATE__
/*****************************************************/
int str_to_int_DATE_Mmm(void)
{
  
  int i = 0;
  while(i < 12)
  {
    if (
        (month_names[3*i + 0] == __DATE__[0]) &&
        (month_names[3*i + 1] == __DATE__[1]) &&
        (month_names[3*i + 2] == __DATE__[2])
       )
    {
      break;
    }
    
    i++;
  } 
  
  if (i < 12)
  { 
    i += 1; /*щоб нумерація місяців ішла з "1", а не з "0"*/
    return ((i / 10) << 4) + (i % 10);
  }
  else return 0;
}
/*****************************************************/


/*****************************************************/
//Зміна конфігурації
/*****************************************************/
__result_dym_mem_select allocate_dynamic_memory_for_settings(__action_dym_mem_select make_remake_restore, unsigned int mem_for_prt, uintptr_t *p_sca_of_p_current[], uintptr_t *p_sca_of_p_control[], __CONFIG *current, __CONFIG *edited, __CONFIG *control)
{
  __result_dym_mem_select result = DYN_MEM_SELECT_OK;
  __id_fb index_1;
  unsigned int can_be_restore = true;
  
  if (make_remake_restore != RESTORE_DYN_MEM)
  {
    index_1 = _ID_FB_FIRST_VAR;
    while(
          (result == DYN_MEM_SELECT_OK) &&
          (index_1 < _ID_FB_LAST_VAR)
         )    
    {
      uint32_t n_prev, n_cur;
      size_t size;
      void (*min_param)(unsigned int, uintptr_t *, size_t, size_t);
      uint32_t *p_current_field;
      switch (index_1)
      {
      case ID_FB_INPUT:
        {
          //Дискретний вхід
          n_prev = (make_remake_restore != MAKE_DYN_MEM) ? current->n_input : 0;
          p_current_field = &current->n_input;
          n_cur = edited->n_input;
          
          min_param = min_settings_INPUT;
          size = n_cur*((mem_for_prt == true) ? sizeof(__LN_INPUT) : sizeof(__settings_for_INPUT));
          break;
        }
      case ID_FB_OUTPUT:
      case ID_FB_LED:
        {
          //Дискретний вихід або Світлоіндикатор
          if (index_1 == ID_FB_OUTPUT)
          {
            n_prev = (make_remake_restore != MAKE_DYN_MEM) ? current->n_output : 0;
            p_current_field = &current->n_output;
            n_cur = edited->n_output;
          }
          else
          {
            n_prev = (make_remake_restore != MAKE_DYN_MEM) ? current->n_led : 0;
            p_current_field = &current->n_led;
            n_cur = edited->n_led;
          }
          
          min_param = min_settings_OUTPUT_LED;
          size = n_cur*((mem_for_prt == true) ? sizeof(__LN_OUTPUT_LED) : sizeof(__settings_for_OUTPUT_LED));
          break;
        }
      case ID_FB_BUTTON:
        {
          //ФК
          n_prev = (make_remake_restore != MAKE_DYN_MEM) ? current->n_button : 0;
          p_current_field = &current->n_button;
          n_cur = edited->n_button;
          
          min_param = min_settings_BUTTON;
          size = n_cur*((mem_for_prt == true) ? sizeof(__LN_BUTTON) : 0);
          break;
        }
      case ID_FB_ALARM:
        {
          //Елемент "СЗС"
          n_prev = (make_remake_restore != MAKE_DYN_MEM) ? current->n_alarm : 0;
          p_current_field = &current->n_alarm;
          n_cur = edited->n_alarm;
          
          min_param = min_settings_ALARM;
          size = n_cur*((mem_for_prt == true) ? sizeof(__LN_ALARM) : sizeof(__settings_for_ALARM));
          break;
        }
      case ID_FB_GROUP_ALARM:
        {
          //Елемент "ШГС"
          n_prev = (make_remake_restore != MAKE_DYN_MEM) ? current->n_group_alarm : 0;
          p_current_field = &current->n_group_alarm;
          n_cur = edited->n_group_alarm;
          
          min_param = min_settings_GROUP_ALARM;
          size = n_cur*((mem_for_prt == true) ? sizeof(__LN_GROUP_ALARM) : sizeof(__settings_for_GROUP_ALARM));
          break;
        }
      case ID_FB_AND:
        {
          //Елемент "І"
          n_prev = (make_remake_restore != MAKE_DYN_MEM) ? current->n_and : 0;
          p_current_field = &current->n_and;
          n_cur = edited->n_and;
          
          min_param = min_settings_AND;
          size = n_cur*((mem_for_prt == true) ? sizeof(__LN_AND) : sizeof(__settings_for_AND));
          break;
        }
      case ID_FB_OR:
        {
          //Елемент "АБО"
          n_prev = (make_remake_restore != MAKE_DYN_MEM) ? current->n_or : 0;
          p_current_field = &current->n_or;
          n_cur = edited->n_or;
          
          min_param = min_settings_OR;
          size = n_cur*((mem_for_prt == true) ? sizeof(__LN_OR) : sizeof(__settings_for_OR));
          break;
        }
      case ID_FB_XOR:
        {
          //Елемент "Викл.АБО"
          n_prev = (make_remake_restore != MAKE_DYN_MEM) ? current->n_xor : 0;
          p_current_field = &current->n_xor;
          n_cur = edited->n_xor;
          
          min_param = min_settings_XOR;
          size = n_cur*((mem_for_prt == true) ? sizeof(__LN_XOR) : sizeof(__settings_for_XOR));
          break;
        }
      case ID_FB_NOT:
        {
          //Елемент "НЕ"
          n_prev = (make_remake_restore != MAKE_DYN_MEM) ? current->n_not : 0;
          p_current_field = &current->n_not;
          n_cur = edited->n_not;
          
          min_param = min_settings_NOT;
          size = n_cur*((mem_for_prt == true) ? sizeof(__LN_NOT) : sizeof(__settings_for_NOT));
          break;
        }
      case ID_FB_TIMER:
        {
          //Елемент "Таймер"
          n_prev = (make_remake_restore != MAKE_DYN_MEM) ? current->n_timer : 0;
          p_current_field = &current->n_timer;
          n_cur = edited->n_timer;
          
          min_param = min_settings_TIMER;
          size = n_cur*((mem_for_prt == true) ? sizeof(__LN_TIMER) : sizeof(__settings_for_TIMER));
          break;
        }
      case ID_FB_TRIGGER:
        {
          //Елемент "Триґер"
          n_prev = (make_remake_restore != MAKE_DYN_MEM) ? current->n_trigger : 0;
          p_current_field = &current->n_trigger;
          n_cur = edited->n_trigger;
          
          min_param = min_settings_TRIGGER;
          size = n_cur*((mem_for_prt == true) ? sizeof(__LN_TRIGGER) : sizeof(__settings_for_TRIGGER));
          break;
        }
      case ID_FB_MEANDER:
        {
          //Функціональний блок "Генератор періодичних сигналів"
          n_prev = (make_remake_restore != MAKE_DYN_MEM) ? current->n_meander : 0;
          p_current_field = &current->n_meander;
          n_cur = edited->n_meander;
          
          min_param = min_settings_MEANDER;
          size = n_cur*((mem_for_prt == true) ? sizeof(__LN_MEANDER) : sizeof(__settings_for_MEANDER));
          break;
        }
      case ID_FB_TU:
        {
          //ТУ
          n_prev = (make_remake_restore != MAKE_DYN_MEM) ? current->n_tu : 0;
          p_current_field = &current->n_tu;
          n_cur = edited->n_tu;
          
          min_param = min_settings_TU;
          size = n_cur*((mem_for_prt == true) ? sizeof(__LN_TU) : sizeof(__settings_for_TU));
          break;
        }
      case ID_FB_TS:
        {
          //ТС
          n_prev = (make_remake_restore != MAKE_DYN_MEM) ? current->n_ts : 0;
          p_current_field = &current->n_ts;
          n_cur = edited->n_ts;
          
          min_param = min_settings_TS;
          size = n_cur*((mem_for_prt == true) ? sizeof(__LN_TS) : sizeof(__settings_for_TS));
          break;
        }
      case ID_FB_EVENT_LOG:
        {
          //Елемент "Журнал подій"
          n_prev = (make_remake_restore != MAKE_DYN_MEM) ? current->n_log : 0;
          p_current_field = &current->n_log;
          n_cur = edited->n_log;
          
          min_param = min_settings_LOG;
          size = n_cur*sizeof(__LOG_INPUT)*LOG_SIGNALS_IN;
          if ((mem_for_prt == true) && (n_cur != 0)) size += sizeof(__LOG_INPUT);
          break;
        }
      default:
        {
          //Якщо сюди дійшла програма, значить відбулася недопустива помилка, тому треба зациклити програму, щоб вона пішла на перезагрузку
          total_error_sw_fixed(22);
        }
      }
    
      if ((make_remake_restore == MAKE_DYN_MEM) || (n_cur != n_prev))
      {
        if ((mem_for_prt != false) && (n_cur < n_prev)) can_be_restore = false;
        
        //Іде або виділення пергий раз області пам'яті, або кількість функціональних блоків зміникася
        if(size == 0) 
        {
          free(p_sca_of_p_current[index_1 - _ID_FB_FIRST_VAR]);
          p_sca_of_p_current[index_1 - _ID_FB_FIRST_VAR] = NULL;
        }
        else
        {
          uintptr_t *ptr= (uintptr_t*)realloc(p_sca_of_p_current[index_1 - _ID_FB_FIRST_VAR], size);
          if (ptr != NULL)
          {
            p_sca_of_p_current[index_1 - _ID_FB_FIRST_VAR] = ptr;
            if (n_cur > n_prev)
            {
              //Викликаємо функцію встановлення нових налаштувань у мінімальні значення
              if (min_param != NULL) (*min_param)(mem_for_prt, ptr, n_prev, n_cur);
            }
          }
          else 
          {
            if (
                (make_remake_restore == MAKE_DYN_MEM) ||
                ((mem_for_prt != false) && (can_be_restore != true)) ||
                (control == NULL)
                ) 
            {
              result = DYN_MEM_TOTAL_ERROR;
            }
            else
            {
              result = DYN_MEM_NO_ENOUGH_MEM;
            }
          }
        }
      }

      //Готуємося до зміни наступного функціонального блоку (у випадку успішної зміни або неуспішної, але з можливістю відновлення)
      if (result == DYN_MEM_SELECT_OK) 
      {
        *p_current_field = n_cur;
        index_1++;
      }
      else if (result == DYN_MEM_NO_ENOUGH_MEM) index_1--;
    }
  }
  else
  {
    //Треб підготуватися для відновлення даних по контрльних даних
    index_1 = _ID_FB_LAST_VAR;
    index_1--;
  }
  
  /*
  Цей while потрібен тільки у тому випадку, якщо пам'яті для новогого розміщення є недостатньо
  і є спроба повернутися до попередньої конфігурації
  */
  
  /*****
  Контроль на те, чи не є можлива спроба відновлення даних у ситуаціції, коли це не можливо
  *****/
  if(
     (
      (
       (make_remake_restore == RESTORE_DYN_MEM) &&
       (result == DYN_MEM_SELECT_OK)  
      )   
      ||  
      (result == DYN_MEM_NO_ENOUGH_MEM)
     )
     && 
     (
      (make_remake_restore == MAKE_DYN_MEM) ||
      ((mem_for_prt != false) && (can_be_restore != true)) ||
      (control == NULL)
     )
    )   
  {
    //Якщо сюди дійшла програма, значить відбулася недопустива помилка, тому треба зациклити програму, щоб вона пішла на перезагрузку
    total_error_sw_fixed(66);
  }
  /*****/
  
  
  while(
        (
         (
          (make_remake_restore == RESTORE_DYN_MEM) &&
          (result == DYN_MEM_SELECT_OK)  
         )   
         ||  
         (result == DYN_MEM_NO_ENOUGH_MEM)
        )
        &&  
        (index_1 >= _ID_FB_FIRST_VAR)
       )   
  {
    uint32_t n_prev, n_cur;
    size_t size;
    void (*copy_settings_LN)(unsigned int, unsigned int, uintptr_t *, uintptr_t *, size_t, size_t);
    switch (index_1)
    {
    case ID_FB_INPUT:
      {
        //Дискретний вхід
        n_cur  = current->n_input;
        current->n_input = n_prev = control->n_input;
        
        copy_settings_LN = copy_settings_INPUT;
        size = n_prev*sizeof(__settings_for_INPUT);
        break;
      }
    case ID_FB_OUTPUT:
    case ID_FB_LED:
      {
        //Дискретний вихід або Світлоіндимкатор
        if (index_1 == ID_FB_OUTPUT)
        {
          n_cur  = current->n_output;
          current->n_output = n_prev = control->n_output;
        }
        else
        {
          n_cur  = current->n_led;
          current->n_led = n_prev = control->n_led;
        }
        
        copy_settings_LN = copy_settings_OUTPUT_LED;
        size = n_prev*sizeof(__settings_for_OUTPUT_LED);
        break;
      }
    case ID_FB_BUTTON:
      {
        //ФК
        n_cur  = current->n_button;
        current->n_button = n_prev = control->n_button;
        
        copy_settings_LN = NULL;
        size = n_prev*0;
        break;
      }
    case ID_FB_ALARM:
      {
        //Елемент "СЗС"
        n_cur  = current->n_alarm;
        current->n_alarm = n_prev = control->n_alarm;
        
        copy_settings_LN = copy_settings_ALARM;
        size = n_prev*sizeof(__settings_for_ALARM);
        break;
      }
    case ID_FB_GROUP_ALARM:
      {
        //Елемент "ШГС"
        n_cur  = current->n_group_alarm;
        current->n_group_alarm = n_prev = control->n_group_alarm;
        
        copy_settings_LN = copy_settings_GROUP_ALARM;
        size = n_prev*sizeof(__settings_for_GROUP_ALARM);
        break;
      }
    case ID_FB_AND:
      {
        //Елемент "І"
        n_cur  = current->n_and;
        current->n_and = n_prev = control->n_and;
        
        copy_settings_LN = copy_settings_AND;
        size = n_prev*sizeof(__settings_for_AND);
        break;
      }
    case ID_FB_OR:
      {
        //Елемент "АБО"
        n_cur  = current->n_or;
        current->n_or = n_prev = control->n_or;
        
        copy_settings_LN = copy_settings_OR;
        size = n_prev*sizeof(__settings_for_OR);
        break;
      }
    case ID_FB_XOR:
      {
        //Елемент "Викл.АБО"
        n_cur  = current->n_xor;
        current->n_xor = n_prev = control->n_xor;
        
        copy_settings_LN = copy_settings_XOR;
        size = n_prev*sizeof(__settings_for_XOR);
        break;
      }
    case ID_FB_NOT:
      {
        //Елемент "НЕ"
        n_cur  = current->n_not;
        current->n_not = n_prev = control->n_not;
        
        copy_settings_LN = copy_settings_NOT;
        size = n_prev*sizeof(__settings_for_NOT);
        break;
      }
    case ID_FB_TIMER:
      {
        //Елемент "Таймер"
        n_cur  = current->n_timer;
        current->n_timer = n_prev = control->n_timer;
        
        copy_settings_LN = copy_settings_TIMER;
        size = n_prev*sizeof(__settings_for_TIMER);
        break;
      }
    case ID_FB_TRIGGER:
      {
        //Елемент "Триґер"
        n_cur  = current->n_trigger;
        current->n_trigger = n_prev = control->n_trigger;
        
        copy_settings_LN = copy_settings_TRIGGER;
        size = n_prev*sizeof(__settings_for_TRIGGER);
        break;
      }
    case ID_FB_MEANDER:
      {
        //Функціональний блок "Генератор періодичних сигналів"
        n_cur  = current->n_meander;
        current->n_meander = n_prev = control->n_meander;
        
        copy_settings_LN = copy_settings_MEANDER;
        size = n_prev*sizeof(__settings_for_MEANDER);
        break;
      }
    case ID_FB_TU:
      {
        //ТУ
        n_cur  = current->n_tu;
        current->n_tu = n_prev = control->n_tu;
        
        copy_settings_LN = copy_settings_TU;
        size = n_prev*sizeof(__settings_for_TU);
        break;
      }
    case ID_FB_TS:
      {
        //ТС
        n_cur  = current->n_ts;
        current->n_ts = n_prev = control->n_ts;
        
        copy_settings_LN = copy_settings_TS;
        size = n_prev*sizeof(__settings_for_TS);
        break;
      }
    case ID_FB_EVENT_LOG:
      {
        //Елемент "Журнал подій"
        n_cur  = current->n_log;
        current->n_log = n_prev = control->n_log;
        
        copy_settings_LN = copy_settings_LOG;
        size = n_prev*sizeof(__LOG_INPUT)*LOG_SIGNALS_IN;
        break;
      }
    default:
      {
        //Якщо сюди дійшла програма, значить відбулася недопустива помилка, тому треба зациклити програму, щоб вона пішла на перезагрузку
        total_error_sw_fixed(42);
      }
    }
    
    if (n_cur != n_prev)
    {
      //Іде або виділення пергий раз області пам'яті, або кількість функціональних блоків зміникася
      if(size == 0) 
      {
        free(p_sca_of_p_current[index_1 - _ID_FB_FIRST_VAR]);
        p_sca_of_p_current[index_1 - _ID_FB_FIRST_VAR] = NULL;
      }
      else
      {
        uintptr_t *ptr= (uintptr_t*)realloc(p_sca_of_p_current[index_1 - _ID_FB_FIRST_VAR], size);
        if (ptr != NULL)
        {
          p_sca_of_p_current[index_1 - _ID_FB_FIRST_VAR] = ptr;
          if (n_prev > n_cur)
          {
            if (
                (can_be_restore == true) &&
                (p_sca_of_p_control != NULL) &&
                ( p_sca_of_p_control[index_1 - _ID_FB_FIRST_VAR] != NULL)
               )   
            {
              //Викликаємо функцію повернення нових налаштувань у попередні значення
              if (copy_settings_LN != NULL) (*copy_settings_LN)(false, (p_sca_of_p_control == spca_of_p_prt), ptr, p_sca_of_p_control[index_1 - _ID_FB_FIRST_VAR], n_cur, n_prev);
            }
            else
            {
              //Якщо сюди дійшла програма, значить відбулася недопустива помилка, тому треба зациклити програму, щоб вона пішла на перезагрузку
              total_error_sw_fixed(43);
            }
          }
        }
        else  result = DYN_MEM_TOTAL_ERROR;
      }
    }
    
    //Готуємося до зміни наступного функціонального блоку
    if (result != DYN_MEM_TOTAL_ERROR) index_1--;
  }
  
  return result;
}
/*****************************************************/

/*****************************************************/
//Встановлення мінімальних параметрів для дискретного входу
/*****************************************************/
void min_settings_INPUT(unsigned int mem_to_prt, uintptr_t *base, size_t index_first, size_t index_last)
{
  for (size_t shift = index_first; shift < index_last; shift++)
  {
    if (mem_to_prt == true) 
    {
      ((__LN_INPUT *)(base) + shift)->settings.set_delay[INPUT_SET_DELAY_DOPUSK] = KOEF_DOPUSK_DV_POST_MIN;
      ((__LN_INPUT *)(base) + shift)->settings.control = 0;
    }
    else 
    {
      ((__settings_for_INPUT *)(base) + shift)->set_delay[INPUT_SET_DELAY_DOPUSK] = KOEF_DOPUSK_DV_POST_MIN;
      ((__settings_for_INPUT *)(base) + shift)->control = 0;
    }
    
    if (mem_to_prt == true)
    {
//      for (size_t i = 0; i < INPUT_WORK_DELAYS; i++) ((__LN_INPUT *)(base) + shift)->work_delay[i] = -1;
      for (size_t i = 0; i < DIV_TO_HIGHER(INPUT_SIGNALS_OUT, 8); i++)
      {
        ((__LN_INPUT *)(base) + shift)->active_state[i] = 0;
      }
    }
  }
}
/*****************************************************/

/*****************************************************/
//Відновлення попередніх параметрів для дискретного входу
/*****************************************************/
void copy_settings_INPUT(unsigned int mem_to_prt, unsigned int mem_from_prt, uintptr_t *base_target, uintptr_t *base_source, size_t index_target, size_t index_source)
{
  for (size_t shift = index_target; shift < index_source; shift++)
  {
    if ((mem_to_prt == false) && (mem_from_prt == true))
    {
      ((__settings_for_INPUT *)(base_target) + shift)->control = ((__LN_INPUT *)(base_source) + shift)->settings.control;
      for (size_t i = 0; i < INPUT_SET_DELAYS; i++) ((__settings_for_INPUT *)(base_target) + shift)->set_delay[i] = ((__LN_INPUT *)(base_source) + shift)->settings.set_delay[i];
    }
    else if ((mem_to_prt == true) && (mem_from_prt == false))
    {
      ((__LN_INPUT *)(base_target) + shift)->settings.control = ((__settings_for_INPUT *)(base_source) + shift)->control;
      for (size_t i = 0; i < INPUT_SET_DELAYS; i++) ((__LN_INPUT *)(base_target) + shift)->settings.set_delay[i] = ((__settings_for_INPUT *)(base_source) + shift)->set_delay[i];
    }
    else if ((mem_to_prt == false) && (mem_from_prt == false))
    {
      ((__settings_for_INPUT *)(base_target) + shift)->control = ((__settings_for_INPUT *)(base_source) + shift)->control;
      for (size_t i = 0; i < INPUT_SET_DELAYS; i++) ((__settings_for_INPUT *)(base_target) + shift)->set_delay[i] = ((__settings_for_INPUT *)(base_source) + shift)->set_delay[i];
    }
    else
    {
      //Якщо сюди дійшла програма, значить відбулася недопустива помилка, тому треба зациклити програму, щоб вона пішла на перезагрузку
      total_error_sw_fixed(90);
    }
  }
}
/*****************************************************/

/*****************************************************/
//Встановлення мінімальних параметрів для дискретного виходу/світлоіндикатора
/*****************************************************/
void min_settings_OUTPUT_LED(unsigned int mem_to_prt, uintptr_t *base, size_t index_first, size_t index_last)
{
  for (size_t shift = index_first; shift < index_last; shift++)
  {
    if (mem_to_prt == true) 
    {
      ((__LN_OUTPUT_LED *)(base) + shift)->settings.control = 0;
      for (size_t i = 0; i < OUTPUT_LED_SIGNALS_IN_TOTAL; i++) ((__LN_OUTPUT_LED *)(base) + shift)->settings.param[i] = 0;
    }
    else 
    {
      ((__settings_for_OUTPUT_LED *)(base) + shift)->control = 0;
      for (size_t i = 0; i < OUTPUT_LED_SIGNALS_IN_TOTAL; i++) ((__settings_for_OUTPUT_LED *)(base) + shift)->param[i] = 0;
    }
    
    if (mem_to_prt == true)
    {
      for (size_t i = 0; i < DIV_TO_HIGHER(OUTPUT_LED_SIGNALS_OUT_TOTAL, 8); i++)
      {
        ((__LN_OUTPUT_LED *)(base) + shift)->active_state[i] = 0;
      }
      for (size_t i = 0; i < DIV_TO_HIGHER(OUTPUT_LED_D_TRIGGER_TOTAL, 8); i++)
      {
        ((__LN_OUTPUT_LED *)(base) + shift)->d_trigger_state[i] = 0;
        ((__LN_OUTPUT_LED *)(base) + shift)->d_trigger_state_tmp[i] = 0;
      }
    }
  }
}
/*****************************************************/

/*****************************************************/
//Відновлення попередніх параметрів для дискретного виходу/світлоіндикатора
/*****************************************************/
void copy_settings_OUTPUT_LED(unsigned int mem_to_prt, unsigned int mem_from_prt, uintptr_t *base_target, uintptr_t *base_source, size_t index_target, size_t index_source)
{
  for (size_t shift = index_target; shift < index_source; shift++)
  {
    if ((mem_to_prt == false) && (mem_from_prt == true))
    {
      ((__settings_for_OUTPUT_LED *)(base_target) + shift)->control = ((__LN_OUTPUT_LED *)(base_source) + shift)->settings.control;
      for (size_t i = 0; i < OUTPUT_LED_SIGNALS_IN_TOTAL; i++) ((__settings_for_OUTPUT_LED *)(base_target) + shift)->param[i] = ((__LN_OUTPUT_LED *)(base_source) + shift)->settings.param[i];
    }
    else if ((mem_to_prt == true) && (mem_from_prt == false))
    {
      ((__LN_OUTPUT_LED *)(base_target) + shift)->settings.control = ((__settings_for_OUTPUT_LED *)(base_source) + shift)->control;
      for (size_t i = 0; i < OUTPUT_LED_SIGNALS_IN_TOTAL; i++) ((__LN_OUTPUT_LED *)(base_target) + shift)->settings.param[i] = ((__settings_for_OUTPUT_LED *)(base_source) + shift)->param[i];
    }
    else if ((mem_to_prt == false) && (mem_from_prt == false))
    {
      ((__settings_for_OUTPUT_LED *)(base_target) + shift)->control = ((__settings_for_OUTPUT_LED *)(base_source) + shift)->control;
      for (size_t i = 0; i < OUTPUT_LED_SIGNALS_IN_TOTAL; i++) ((__settings_for_OUTPUT_LED *)(base_target) + shift)->param[i] = ((__settings_for_OUTPUT_LED *)(base_source) + shift)->param[i];
    }
    else
    {
      //Якщо сюди дійшла програма, значить відбулася недопустива помилка, тому треба зациклити програму, щоб вона пішла на перезагрузку
      total_error_sw_fixed(91);
    }
  }
}
/*****************************************************/

/*****************************************************/
//Встановлення мінімальних параметрів для ФК
/*****************************************************/
void min_settings_BUTTON(unsigned int mem_to_prt, uintptr_t *base, size_t index_first, size_t index_last)
{
  for (size_t shift = index_first; shift < index_last; shift++)
  {
    if (mem_to_prt == true)
    {
      for (size_t i = 0; i < DIV_TO_HIGHER(BUTTON_SIGNALS_OUT, 8); i++)
      {
        ((__LN_BUTTON *)(base) + shift)->active_state[i] = 0;
      }

      for (size_t i = 0; i < DIV_TO_HIGHER(BUTTON_SIGNALS_INT_IN, 8); i++)
      {
        ((__LN_BUTTON *)(base) + shift)->internal_input[i] = 0;
      }
    }
  }
}
/*****************************************************/

/*****************************************************/
//Встановлення мінімальних параметрів для елементу "СЗС"
/*****************************************************/
void min_settings_ALARM(unsigned int mem_to_prt, uintptr_t *base, size_t index_first, size_t index_last)
{
  for (size_t shift = index_first; shift < index_last; shift++)
  {
    if (mem_to_prt == true) 
    {
      ((__LN_ALARM *)(base) + shift)->settings.set_delay[ALARM_SET_DELAY_PERIOD] = TIMEOUT_ALARM_PERIOD_MIN;
      ((__LN_ALARM *)(base) + shift)->settings.control = 0;
      for (size_t i = 0; i < ALARM_SIGNALS_IN; i++) ((__LN_ALARM *)(base) + shift)->settings.param[i] = 0;
    }
    else 
    {
      ((__settings_for_ALARM *)(base) + shift)->set_delay[ALARM_SET_DELAY_PERIOD] = TIMEOUT_ALARM_PERIOD_MIN;
      ((__settings_for_ALARM *)(base) + shift)->control = 0;
      for (size_t i = 0; i < ALARM_SIGNALS_IN; i++) ((__settings_for_ALARM *)(base) + shift)->param[i] = 0;
    }
    
    if (mem_to_prt == true)
    {
//      for (size_t i = 0; i < ALARM_WORK_DELAYS; i++) ((__LN_ALARM *)(base) + shift)->work_delay[i] = -1;
      for (size_t i = 0; i < DIV_TO_HIGHER(ALARM_SIGNALS_OUT, 8); i++)
      {
        ((__LN_ALARM *)(base) + shift)->active_state[i] = 0;
      }
      for (size_t i = 0; i < DIV_TO_HIGHER(ALARM_D_TRIGGER_TOTAL, 8); i++)
      {
        ((__LN_ALARM *)(base) + shift)->d_trigger_state[i] = 0;
        ((__LN_ALARM *)(base) + shift)->d_trigger_state_tmp[i] = 0;
      }
    }
  }
}
/*****************************************************/

/*****************************************************/
//Відновлення попередніх параметрів для елементу "СЗС"
/*****************************************************/
void copy_settings_ALARM(unsigned int mem_to_prt, unsigned int mem_from_prt, uintptr_t *base_target, uintptr_t *base_source, size_t index_target, size_t index_source)
{
  for (size_t shift = index_target; shift < index_source; shift++)
  {
    if ((mem_to_prt == false) && (mem_from_prt == true))
    {
      for (size_t i = 0; i < ALARM_SET_DELAYS; i++) ((__settings_for_ALARM *)(base_target) + shift)->set_delay[i] = ((__LN_ALARM *)(base_source) + shift)->settings.set_delay[i];
      ((__settings_for_ALARM *)(base_target) + shift)->control = ((__LN_ALARM *)(base_source) + shift)->settings.control;
      for (size_t i = 0; i < ALARM_SIGNALS_IN; i++) ((__settings_for_ALARM *)(base_target) + shift)->param[i] = ((__LN_ALARM *)(base_source) + shift)->settings.param[i];
    }
    else if ((mem_to_prt == true) && (mem_from_prt == false))
    {
      for (size_t i = 0; i < ALARM_SET_DELAYS; i++)((__LN_ALARM *)(base_target) + shift)->settings.set_delay[i] = ((__settings_for_ALARM *)(base_source) + shift)->set_delay[i];
      ((__LN_ALARM *)(base_target) + shift)->settings.control = ((__settings_for_ALARM *)(base_source) + shift)->control;
      for (size_t i = 0; i < ALARM_SIGNALS_IN; i++) ((__LN_ALARM *)(base_target) + shift)->settings.param[i] = ((__settings_for_ALARM *)(base_source) + shift)->param[i];
    }
    else if ((mem_to_prt == false) && (mem_from_prt == false))
    {
      for (size_t i = 0; i < ALARM_SET_DELAYS; i++)((__settings_for_ALARM *)(base_target) + shift)->set_delay[i] = ((__settings_for_ALARM *)(base_source) + shift)->set_delay[i];
      ((__settings_for_ALARM *)(base_target) + shift)->control = ((__settings_for_ALARM *)(base_source) + shift)->control;
      for (size_t i = 0; i < ALARM_SIGNALS_IN; i++) ((__settings_for_ALARM *)(base_target) + shift)->param[i] = ((__settings_for_ALARM *)(base_source) + shift)->param[i];
    }
    else
    {
      //Якщо сюди дійшла програма, значить відбулася недопустива помилка, тому треба зациклити програму, щоб вона пішла на перезагрузку
      total_error_sw_fixed(12);
    }
  }
}
/*****************************************************/

/*****************************************************/
//Встановлення мінімальних параметрів для елементу "ШГС"
/*****************************************************/
void min_settings_GROUP_ALARM(unsigned int mem_to_prt, uintptr_t *base, size_t index_first, size_t index_last)
{
  for (size_t shift = index_first; shift < index_last; shift++)
  {
    if (mem_to_prt == true) 
    {
      ((__LN_GROUP_ALARM *)(base) + shift)->settings.pickup[GROUP_ALARM_PICKUP_DELTA_I] = PICKUP_ALARM_DELTA_I_MIN;
      ((__LN_GROUP_ALARM *)(base) + shift)->settings.set_delay[GROUP_ALARM_SET_DELAY_DELAY] = TIMEOUT_GROUP_ALARM_DELAY_MIN;
      ((__LN_GROUP_ALARM *)(base) + shift)->settings.control = 0;
      ((__LN_GROUP_ALARM *)(base) + shift)->settings.analog_input_control = 0;
    }
    else 
    {
      ((__settings_for_GROUP_ALARM *)(base) + shift)->pickup[GROUP_ALARM_PICKUP_DELTA_I] = PICKUP_ALARM_DELTA_I_MIN;
      ((__settings_for_GROUP_ALARM *)(base) + shift)->set_delay[GROUP_ALARM_SET_DELAY_DELAY] = TIMEOUT_GROUP_ALARM_DELAY_MIN;
      ((__settings_for_GROUP_ALARM *)(base) + shift)->control = 0;
      ((__settings_for_GROUP_ALARM *)(base) + shift)->analog_input_control = 0;
    }
    
    if (mem_to_prt == true)
    {
//      for (size_t i = 0; i < GROUP_ALARM_WORK_DELAYS; i++) ((__LN_GROUP_ALARM *)(base) + shift)->work_delay[i] = -1;
      for (size_t i = 0; i < DIV_TO_HIGHER(GROUP_ALARM_SIGNALS_OUT, 8); i++)
      {
        ((__LN_GROUP_ALARM *)(base) + shift)->active_state[i] = 0;
        ((__LN_GROUP_ALARM *)(base) + shift)->NNC_before = ((__LN_GROUP_ALARM *)(base) + shift)->NNC = 0;
      }
    }
  }
}
/*****************************************************/

/*****************************************************/
//Відновлення попередніх параметрів для елементу "ШГС"
/*****************************************************/
void copy_settings_GROUP_ALARM(unsigned int mem_to_prt, unsigned int mem_from_prt, uintptr_t *base_target, uintptr_t *base_source, size_t index_target, size_t index_source)
{
  for (size_t shift = index_target; shift < index_source; shift++)
  {
    if ((mem_to_prt == false) && (mem_from_prt == true))
    {
      for (size_t i = 0; i < GROUP_ALARM_PICKUPS; i++) ((__settings_for_GROUP_ALARM *)(base_target) + shift)->pickup[i] = ((__LN_GROUP_ALARM *)(base_source) + shift)->settings.pickup[i];
      for (size_t i = 0; i < GROUP_ALARM_SET_DELAYS; i++) ((__settings_for_GROUP_ALARM *)(base_target) + shift)->set_delay[i] = ((__LN_GROUP_ALARM *)(base_source) + shift)->settings.set_delay[i];
      ((__settings_for_GROUP_ALARM *)(base_target) + shift)->control = ((__LN_GROUP_ALARM *)(base_source) + shift)->settings.control;
      ((__settings_for_GROUP_ALARM *)(base_target) + shift)->analog_input_control = ((__LN_GROUP_ALARM *)(base_source) + shift)->settings.analog_input_control;
    }
    else if ((mem_to_prt == true) && (mem_from_prt == false))
    {
      for (size_t i = 0; i < GROUP_ALARM_PICKUPS; i++)((__LN_GROUP_ALARM *)(base_target) + shift)->settings.pickup[i] = ((__settings_for_GROUP_ALARM *)(base_source) + shift)->pickup[i];
      for (size_t i = 0; i < GROUP_ALARM_SET_DELAYS; i++)((__LN_GROUP_ALARM *)(base_target) + shift)->settings.set_delay[i] = ((__settings_for_GROUP_ALARM *)(base_source) + shift)->set_delay[i];
      ((__LN_GROUP_ALARM *)(base_target) + shift)->settings.control = ((__settings_for_GROUP_ALARM *)(base_source) + shift)->control;
      ((__LN_GROUP_ALARM *)(base_target) + shift)->settings.analog_input_control = ((__settings_for_GROUP_ALARM *)(base_source) + shift)->analog_input_control;
    }
    else if ((mem_to_prt == false) && (mem_from_prt == false))
    {
      for (size_t i = 0; i < GROUP_ALARM_PICKUPS; i++)((__settings_for_GROUP_ALARM *)(base_target) + shift)->pickup[i] = ((__settings_for_GROUP_ALARM *)(base_source) + shift)->pickup[i];
      for (size_t i = 0; i < GROUP_ALARM_SET_DELAYS; i++)((__settings_for_GROUP_ALARM *)(base_target) + shift)->set_delay[i] = ((__settings_for_GROUP_ALARM *)(base_source) + shift)->set_delay[i];
      ((__settings_for_GROUP_ALARM *)(base_target) + shift)->control = ((__settings_for_GROUP_ALARM *)(base_source) + shift)->control;
      ((__settings_for_GROUP_ALARM *)(base_target) + shift)->analog_input_control = ((__settings_for_GROUP_ALARM *)(base_source) + shift)->analog_input_control;
    }
    else
    {
      //Якщо сюди дійшла програма, значить відбулася недопустива помилка, тому треба зациклити програму, щоб вона пішла на перезагрузку
      total_error_sw_fixed(32);
    }
  }
}
/*****************************************************/

/*****************************************************/
//Встановлення мінімальних параметрів для елементу стандартної логіки "І"
/*****************************************************/
void min_settings_AND(unsigned int mem_to_prt, uintptr_t *base, size_t index_first, size_t index_last)
{
  for (size_t shift = index_first; shift < index_last; shift++)
  {
    for (size_t i = 0; i < AND_SIGNALS_IN; i++)
    {
      if (mem_to_prt == true) ((__LN_AND *)(base) + shift)->settings.param[i] = 0;
      else ((__settings_for_AND *)(base) + shift)->param[i] = 0;
    }
    
    if (mem_to_prt == true)
    {
      for (size_t i = 0; i < DIV_TO_HIGHER(STANDARD_LOGIC_SIGNALS_OUT, 8); i++)
      {
        ((__LN_AND *)(base) + shift)->active_state[i] = 0;
      }
    }
  }
}
/*****************************************************/

/*****************************************************/
//Відновлення попередніх параметрів для елементу стандартної логіки "І"
/*****************************************************/
void copy_settings_AND(unsigned int mem_to_prt, unsigned int mem_from_prt, uintptr_t *base_target, uintptr_t *base_source, size_t index_target, size_t index_source)
{
  for (size_t shift = index_target; shift < index_source; shift++)
  {
    for (size_t i = 0; i < AND_SIGNALS_IN; i++)
    {
      if ((mem_to_prt == false) && (mem_from_prt == true))
      {
        ((__settings_for_AND *)(base_target) + shift)->param[i] = ((__LN_AND *)(base_source) + shift)->settings.param[i];
      }
      else if ((mem_to_prt == true) && (mem_from_prt == false))
      {
        ((__LN_AND *)(base_target) + shift)->settings.param[i] = ((__settings_for_AND *)(base_source) + shift)->param[i];
      }
      else if ((mem_to_prt == false) && (mem_from_prt == false))
      {
        ((__settings_for_AND *)(base_target) + shift)->param[i] = ((__settings_for_AND *)(base_source) + shift)->param[i];
      }
      else
      {
        //Якщо сюди дійшла програма, значить відбулася недопустива помилка, тому треба зациклити програму, щоб вона пішла на перезагрузку
        total_error_sw_fixed(93);
      }
    }
  }
}
/*****************************************************/

/*****************************************************/
//Встановлення мінімальних параметрів для елементу стандартної логіки "АБО"
/*****************************************************/
void min_settings_OR(unsigned int mem_to_prt, uintptr_t *base, size_t index_first, size_t index_last)
{
  for (size_t shift = index_first; shift < index_last; shift++)
  {
    for (size_t i = 0; i < OR_SIGNALS_IN; i++)
    {
      if (mem_to_prt == true) ((__LN_OR *)(base) + shift)->settings.param[i] = 0;
      else ((__settings_for_OR *)(base) + shift)->param[i] = 0;
    }
    
    if (mem_to_prt == true)
    {
      for (size_t i = 0; i < DIV_TO_HIGHER(STANDARD_LOGIC_SIGNALS_OUT, 8); i++)
      {
        ((__LN_OR *)(base) + shift)->active_state[i] = 0;
      }
    }
  }
}
/*****************************************************/

/*****************************************************/
//Відновлення попередніх параметрів для елементу стандартної логіки "АБО"
/*****************************************************/
void copy_settings_OR(unsigned int mem_to_prt, unsigned int mem_from_prt, uintptr_t *base_target, uintptr_t *base_source, size_t index_target, size_t index_source)
{
  for (size_t shift = index_target; shift < index_source; shift++)
  {
    for (size_t i = 0; i < OR_SIGNALS_IN; i++)
    {
      if ((mem_to_prt == false) && (mem_from_prt == true))
      {
        ((__settings_for_OR *)(base_target) + shift)->param[i] = ((__LN_OR *)(base_source) + shift)->settings.param[i];
      }
      else if ((mem_to_prt == true) && (mem_from_prt == false))
      {
        ((__LN_OR *)(base_target) + shift)->settings.param[i] = ((__settings_for_OR *)(base_source) + shift)->param[i];
      }
      else if ((mem_to_prt == false) && (mem_from_prt == false))
      {
        ((__settings_for_OR *)(base_target) + shift)->param[i] = ((__settings_for_OR *)(base_source) + shift)->param[i];
      }
      else
      {
        //Якщо сюди дійшла програма, значить відбулася недопустива помилка, тому треба зациклити програму, щоб вона пішла на перезагрузку
        total_error_sw_fixed(94);
      }
    }
  }
}
/*****************************************************/

/*****************************************************/
//Встановлення мінімальних параметрів для елементу стандартної логіки "Викл.АБО"
/*****************************************************/
void min_settings_XOR(unsigned int mem_to_prt, uintptr_t *base, size_t index_first, size_t index_last)
{
  for (size_t shift = index_first; shift < index_last; shift++)
  {
    for (size_t i = 0; i < 2; i++)
    {
      if (mem_to_prt == true) ((__LN_XOR *)(base) + shift)->settings.param[i] = 0;
      else ((__settings_for_XOR *)(base) + shift)->param[i] = 0;
    }
    
    if (mem_to_prt == true)
    {
      for (size_t i = 0; i < DIV_TO_HIGHER(STANDARD_LOGIC_SIGNALS_OUT, 8); i++)
      {
        ((__LN_XOR *)(base) + shift)->active_state[i] = 0;
      }
    }
  }
}
/*****************************************************/

/*****************************************************/
//Відновлення попередніх параметрів для елементу стандартної логіки "Викл.АБО"
/*****************************************************/
void copy_settings_XOR(unsigned int mem_to_prt, unsigned int mem_from_prt, uintptr_t *base_target, uintptr_t *base_source, size_t index_target, size_t index_source)
{
  for (size_t shift = index_target; shift < index_source; shift++)
  {
    for (size_t i = 0; i < 2; i++)
    {
      if ((mem_to_prt == false) && (mem_from_prt == true))
      {
        ((__settings_for_XOR *)(base_target) + shift)->param[i] = ((__LN_XOR *)(base_source) + shift)->settings.param[i];
      }
      else if ((mem_to_prt == true) && (mem_from_prt == false))
      {
        ((__LN_XOR *)(base_target) + shift)->settings.param[i] = ((__settings_for_XOR *)(base_source) + shift)->param[i];
      }
      else if ((mem_to_prt == false) && (mem_from_prt == false))
      {
        ((__settings_for_XOR *)(base_target) + shift)->param[i] = ((__settings_for_XOR *)(base_source) + shift)->param[i];
      }
      else
      {
        //Якщо сюди дійшла програма, значить відбулася недопустива помилка, тому треба зациклити програму, щоб вона пішла на перезагрузку
        total_error_sw_fixed(95);
      }
    }
  }
}
/*****************************************************/

/*****************************************************/
//Встановлення мінімальних параметрів для елементу стандартної логіки "НЕ"
/*****************************************************/
void min_settings_NOT(unsigned int mem_to_prt, uintptr_t *base, size_t index_first, size_t index_last)
{
  for (size_t shift = index_first; shift < index_last; shift++)
  {
    for (size_t i = 0; i < 1; i++)
    {
      if (mem_to_prt == true) ((__LN_NOT *)(base) + shift)->settings.param[i] = 0;
      else ((__settings_for_NOT *)(base) + shift)->param[i] = 0;
    }
    
    if (mem_to_prt == true)
    {
      for (size_t i = 0; i < DIV_TO_HIGHER(STANDARD_LOGIC_SIGNALS_OUT, 8); i++)
      {
        ((__LN_NOT *)(base) + shift)->active_state[i] = 0;
      }
    }
  }
}
/*****************************************************/

/*****************************************************/
//Відновлення попередніх параметрів для елементу стандартної логіки "НЕ"
/*****************************************************/
void copy_settings_NOT(unsigned int mem_to_prt, unsigned int mem_from_prt, uintptr_t *base_target, uintptr_t *base_source, size_t index_target, size_t index_source)
{
  for (size_t shift = index_target; shift < index_source; shift++)
  {
    for (size_t i = 0; i < 1; i++)
    {
      if ((mem_to_prt == false) && (mem_from_prt == true))
      {
        ((__settings_for_NOT *)(base_target) + shift)->param[i] = ((__LN_NOT *)(base_source) + shift)->settings.param[i];
      }
      else if ((mem_to_prt == true) && (mem_from_prt == false))
      {
        ((__LN_NOT *)(base_target) + shift)->settings.param[i] = ((__settings_for_NOT *)(base_source) + shift)->param[i];
      }
      else if ((mem_to_prt == false) && (mem_from_prt == false))
      {
        ((__settings_for_NOT *)(base_target) + shift)->param[i] = ((__settings_for_NOT *)(base_source) + shift)->param[i];
      }
      else
      {
        //Якщо сюди дійшла програма, значить відбулася недопустива помилка, тому треба зациклити програму, щоб вона пішла на перезагрузку
        total_error_sw_fixed(96);
      }
    }
  }
}
/*****************************************************/

/*****************************************************/
//Встановлення мінімальних параметрів для елементу "Таймер"
/*****************************************************/
void min_settings_TIMER(unsigned int mem_to_prt, uintptr_t *base, size_t index_first, size_t index_last)
{
  for (size_t shift = index_first; shift < index_last; shift++)
  {
    if (mem_to_prt == true) 
    {
      for (size_t i = 0; i < TIMER_SIGNALS_IN; i++) ((__LN_TIMER *)(base) + shift)->settings.param[i] = 0;
      ((__LN_TIMER *)(base) + shift)->settings.set_delay[TIMER_SET_DELAY_PAUSE] = TIMEOUT_TIMER_PAUSE_MIN;
      ((__LN_TIMER *)(base) + shift)->settings.set_delay[TIMER_SET_DELAY_WORK]  = TIMEOUT_TIMER_WORK_MIN;
    }
    else 
    {
      for (size_t i = 0; i < TIMER_SIGNALS_IN; i++) ((__settings_for_TIMER *)(base) + shift)->param[i] = 0;
      ((__settings_for_TIMER *)(base) + shift)->set_delay[TIMER_SET_DELAY_PAUSE] = TIMEOUT_TIMER_PAUSE_MIN;
      ((__settings_for_TIMER *)(base) + shift)->set_delay[TIMER_SET_DELAY_WORK]  = TIMEOUT_TIMER_WORK_MIN;
    }
    
    if (mem_to_prt == true)
    {
//      for (size_t i = 0; i < TIMER_WORK_DELAYS; i++) ((__LN_TIMER *)(base) + shift)->work_delay[i] = -1;
      for (size_t i = 0; i < DIV_TO_HIGHER(TIMER_SIGNALS_OUT, 8); i++)
      {
        ((__LN_TIMER *)(base) + shift)->active_state[i] = 0;
      }
    }
  }
}
/*****************************************************/

/*****************************************************/
//Відновлення попередніх параметрів для елементу "Таймер"
/*****************************************************/
void copy_settings_TIMER(unsigned int mem_to_prt, unsigned int mem_from_prt, uintptr_t *base_target, uintptr_t *base_source, size_t index_target, size_t index_source)
{
  for (size_t shift = index_target; shift < index_source; shift++)
  {
    if ((mem_to_prt == false) && (mem_from_prt == true))
    {
      for (size_t i = 0; i < TIMER_SIGNALS_IN; i++) ((__settings_for_TIMER *)(base_target) + shift)->param[i] = ((__LN_TIMER *)(base_source) + shift)->settings.param[i];
      for (size_t i = 0; i < TIMER_SET_DELAYS; i++) ((__settings_for_TIMER *)(base_target) + shift)->set_delay[i] = ((__LN_TIMER *)(base_source) + shift)->settings.set_delay[i];
    }
    else if ((mem_to_prt == true) && (mem_from_prt == false))
    {
      for (size_t i = 0; i < TIMER_SIGNALS_IN; i++) ((__LN_TIMER *)(base_target) + shift)->settings.param[i] = ((__settings_for_TIMER *)(base_source) + shift)->param[i];
      for (size_t i = 0; i < TIMER_SET_DELAYS; i++)((__LN_TIMER *)(base_target) + shift)->settings.set_delay[i] = ((__settings_for_TIMER *)(base_source) + shift)->set_delay[i];
    }
    else if ((mem_to_prt == false) && (mem_from_prt == false))
    {
      for (size_t i = 0; i < TIMER_SIGNALS_IN; i++) ((__settings_for_TIMER *)(base_target) + shift)->param[i] = ((__settings_for_TIMER *)(base_source) + shift)->param[i];
      for (size_t i = 0; i < TIMER_SET_DELAYS; i++)((__settings_for_TIMER *)(base_target) + shift)->set_delay[i] = ((__settings_for_TIMER *)(base_source) + shift)->set_delay[i];
    }
    else
    {
      //Якщо сюди дійшла програма, значить відбулася недопустива помилка, тому треба зациклити програму, щоб вона пішла на перезагрузку
      total_error_sw_fixed(97);
    }
  }
}
/*****************************************************/

/*****************************************************/
//Встановлення мінімальних параметрів для елементу "Триґер"
/*****************************************************/
void min_settings_TRIGGER(unsigned int mem_to_prt, uintptr_t *base, size_t index_first, size_t index_last)
{
  for (size_t shift = index_first; shift < index_last; shift++)
  {
    for (size_t i = 0; i < TRIGGER_SIGNALS_IN; i++)
    {
      if (mem_to_prt == true) ((__LN_TRIGGER *)(base) + shift)->settings.param[i] = 0;
      else ((__settings_for_TRIGGER *)(base) + shift)->param[i] = 0;
    }
    
    if (mem_to_prt == true)
    {
      for (size_t i = 0; i < DIV_TO_HIGHER(TRIGGER_SIGNALS_OUT, 8); i++)
      {
        ((__LN_TRIGGER *)(base) + shift)->active_state[i] = 0;
      }
      for (size_t i = 0; i < DIV_TO_HIGHER(TRIGGER_D_TRIGGER_TOTAL, 8); i++)
      {
        ((__LN_TRIGGER *)(base) + shift)->d_trigger_state[i] = 0;
        ((__LN_TRIGGER *)(base) + shift)->d_trigger_state_tmp[i] = 0;
      }
    }
  }
}
/*****************************************************/

/*****************************************************/
//Відновлення попередніх параметрів для елементу "Триґер"
/*****************************************************/
void copy_settings_TRIGGER(unsigned int mem_to_prt, unsigned int mem_from_prt, uintptr_t *base_target, uintptr_t *base_source, size_t index_target, size_t index_source)
{
  for (size_t shift = index_target; shift < index_source; shift++)
  {
    for (size_t i = 0; i < TRIGGER_SIGNALS_IN; i++)
    {
      if ((mem_to_prt == false) && (mem_from_prt == true))
      {
        ((__settings_for_TRIGGER *)(base_target) + shift)->param[i] = ((__LN_TRIGGER *)(base_source) + shift)->settings.param[i];
      }
      else if ((mem_to_prt == true) && (mem_from_prt == false))
      {
        ((__LN_TRIGGER *)(base_target) + shift)->settings.param[i] = ((__settings_for_TRIGGER *)(base_source) + shift)->param[i];
      }
      else if ((mem_to_prt == false) && (mem_from_prt == false))
      {
        ((__settings_for_TRIGGER *)(base_target) + shift)->param[i] = ((__settings_for_TRIGGER *)(base_source) + shift)->param[i];
      }
      else
      {
        //Якщо сюди дійшла програма, значить відбулася недопустива помилка, тому треба зациклити програму, щоб вона пішла на перезагрузку
        total_error_sw_fixed(98);
      }
    }
  }
}
/*****************************************************/

/*****************************************************/
//Встановлення мінімальних параметрів для функціоанльного блоку "Генератор періодичних сигналів"
/*****************************************************/
void min_settings_MEANDER(unsigned int mem_to_prt, uintptr_t *base, size_t index_first, size_t index_last)
{
  for (size_t shift = index_first; shift < index_last; shift++)
  {
    if (mem_to_prt == true) 
    {
      ((__LN_MEANDER *)(base) + shift)->settings.set_delay[MEANDER_SET_DELAY_PERIOD] = TIMEOUT_MEANDER_PERIOD_MIN;
    }
    else 
    {
      ((__settings_for_MEANDER *)(base) + shift)->set_delay[MEANDER_SET_DELAY_PERIOD] = TIMEOUT_MEANDER_PERIOD_MIN;
    }
    
    if (mem_to_prt == true)
    {
//      for (size_t i = 0; i < MEANDER_WORK_DELAYS; i++) ((__LN_MEANDER *)(base) + shift)->work_delay[i] = -1;
      for (size_t i = 0; i < DIV_TO_HIGHER(MEANDER_SIGNALS_OUT, 8); i++)
      {
        ((__LN_MEANDER *)(base) + shift)->active_state[i] = 0;
      }
    }
  }
}
/*****************************************************/

/*****************************************************/
//Відновлення попередніх параметрів для функціоанльного блоку "Генератор періодичних сигналів"
/*****************************************************/
void copy_settings_MEANDER(unsigned int mem_to_prt, unsigned int mem_from_prt, uintptr_t *base_target, uintptr_t *base_source, size_t index_target, size_t index_source)
{
  for (size_t shift = index_target; shift < index_source; shift++)
  {
    if ((mem_to_prt == false) && (mem_from_prt == true))
    {
      for (size_t i = 0; i < MEANDER_SET_DELAYS; i++) ((__settings_for_MEANDER *)(base_target) + shift)->set_delay[i] = ((__LN_MEANDER *)(base_source) + shift)->settings.set_delay[i];
    }
    else if ((mem_to_prt == true) && (mem_from_prt == false))
    {
      for (size_t i = 0; i < MEANDER_SET_DELAYS; i++) ((__LN_MEANDER *)(base_target) + shift)->settings.set_delay[i] = ((__settings_for_MEANDER *)(base_source) + shift)->set_delay[i];
    }
    else if ((mem_to_prt == false) && (mem_from_prt == false))
    {
      for (size_t i = 0; i < MEANDER_SET_DELAYS; i++) ((__settings_for_MEANDER *)(base_target) + shift)->set_delay[i] = ((__settings_for_MEANDER *)(base_source) + shift)->set_delay[i];
    }
    else
    {
      //Якщо сюди дійшла програма, значить відбулася недопустива помилка, тому треба зациклити програму, щоб вона пішла на перезагрузку
      total_error_sw_fixed(99);
    }
  }
}
/*****************************************************/

/*****************************************************/
//Встановлення мінімальних параметрів для функціоанльного блоку "ТУ"
/*****************************************************/
void min_settings_TU(unsigned int mem_to_prt, uintptr_t *base, size_t index_first, size_t index_last)
{
  for (size_t shift = index_first; shift < index_last; shift++)
  {
    for (size_t i = 0; i < TU_SIGNALS_IN; i++)
    {
      if (mem_to_prt == true) ((__LN_TU *)(base) + shift)->settings.param[i] = 0;
      else ((__settings_for_TU *)(base) + shift)->param[i] = 0;
    }
    
    if (mem_to_prt == true)
    {
      for (size_t i = 0; i < DIV_TO_HIGHER(TU_SIGNALS_OUT, 8); i++)
      {
        ((__LN_TU *)(base) + shift)->active_state[i] = 0;
      }

      for (size_t i = 0; i < DIV_TO_HIGHER(TU_SIGNALS_INT_IN, 8); i++)
      {
        ((__LN_TU *)(base) + shift)->internal_input[i] = 0;
      }
    }
  }
}
/*****************************************************/

/*****************************************************/
//Відновлення попередніх параметрів для функціоанльного блоку "ТУ"
/*****************************************************/
void copy_settings_TU(unsigned int mem_to_prt, unsigned int mem_from_prt, uintptr_t *base_target, uintptr_t *base_source, size_t index_target, size_t index_source)
{
  for (size_t shift = index_target; shift < index_source; shift++)
  {
    for (size_t i = 0; i < TU_SIGNALS_IN; i++)
    {
      if ((mem_to_prt == false) && (mem_from_prt == true))
      {
        ((__settings_for_TU *)(base_target) + shift)->param[i] = ((__LN_TU *)(base_source) + shift)->settings.param[i];
      }
      else if ((mem_to_prt == true) && (mem_from_prt == false))
      {
        ((__LN_TU *)(base_target) + shift)->settings.param[i] = ((__settings_for_TU *)(base_source) + shift)->param[i];
      }
      else if ((mem_to_prt == false) && (mem_from_prt == false))
      {
        ((__settings_for_TU *)(base_target) + shift)->param[i] = ((__settings_for_TU *)(base_source) + shift)->param[i];
      }
      else
      {
        //Якщо сюди дійшла програма, значить відбулася недопустива помилка, тому треба зациклити програму, щоб вона пішла на перезагрузку
        total_error_sw_fixed(39);
      }
    }
  }
}
/*****************************************************/

/*****************************************************/
//Встановлення мінімальних параметрів для функціоанльного блоку "ТС"
/*****************************************************/
void min_settings_TS(unsigned int mem_to_prt, uintptr_t *base, size_t index_first, size_t index_last)
{
  for (size_t shift = index_first; shift < index_last; shift++)
  {
    for (size_t i = 0; i < TS_SIGNALS_IN; i++)
    {
      if (mem_to_prt == true) ((__LN_TS *)(base) + shift)->settings.param[i] = 0;
      else ((__settings_for_TS *)(base) + shift)->param[i] = 0;
    }
    
    if (mem_to_prt == true)
    {
      for (size_t i = 0; i < DIV_TO_HIGHER(TS_SIGNALS_OUT, 8); i++)
      {
        ((__LN_TS *)(base) + shift)->active_state[i] = 0;
      }

      for (size_t i = 0; i < DIV_TO_HIGHER(TS_SIGNALS_INT_IN, 8); i++)
      {
        ((__LN_TS *)(base) + shift)->internal_input[i] = 0;
      }
    }
  }
}
/*****************************************************/

/*****************************************************/
//Відновлення попередніх параметрів для функціоанльного блоку "ТС"
/*****************************************************/
void copy_settings_TS(unsigned int mem_to_prt, unsigned int mem_from_prt, uintptr_t *base_target, uintptr_t *base_source, size_t index_target, size_t index_source)
{
  for (size_t shift = index_target; shift < index_source; shift++)
  {
    for (size_t i = 0; i < TS_SIGNALS_IN; i++)
    {
      if ((mem_to_prt == false) && (mem_from_prt == true))
      {
        ((__settings_for_TS *)(base_target) + shift)->param[i] = ((__LN_TS *)(base_source) + shift)->settings.param[i];
      }
      else if ((mem_to_prt == true) && (mem_from_prt == false))
      {
        ((__LN_TS *)(base_target) + shift)->settings.param[i] = ((__settings_for_TS *)(base_source) + shift)->param[i];
      }
      else if ((mem_to_prt == false) && (mem_from_prt == false))
      {
        ((__settings_for_TS *)(base_target) + shift)->param[i] = ((__settings_for_TS *)(base_source) + shift)->param[i];
      }
      else
      {
        //Якщо сюди дійшла програма, значить відбулася недопустива помилка, тому треба зациклити програму, щоб вона пішла на перезагрузку
        total_error_sw_fixed(40);
      }
    }
  }
}
/*****************************************************/

/*****************************************************/
//Встановлення мінімальних параметрів для елементу "Журнал подій"
/*****************************************************/
void min_settings_LOG(unsigned int mem_to_prt, uintptr_t *base, size_t index_first, size_t index_last)
{
  for (size_t shift = index_first; shift < index_last; shift++)
  {
    for (size_t i = 0; i < LOG_SIGNALS_IN; i++)
    {
      if (mem_to_prt == true) *((__LOG_INPUT *)(base) + 1 + shift*LOG_SIGNALS_IN + i) = 0;
      else *((__LOG_INPUT *)(base) + shift*LOG_SIGNALS_IN + i) = 0;
    }
  }
  
  if ((mem_to_prt == true) && (index_first == 0)) *((__LOG_INPUT *)base) = 0;
}
/*****************************************************/

/*****************************************************/
//Відновлення попередніх параметрів для елементу "Журнал подій"
/*****************************************************/
void copy_settings_LOG(unsigned int mem_to_prt, unsigned int mem_from_prt, uintptr_t *base_target, uintptr_t *base_source, size_t index_target, size_t index_source)
{
  for (size_t shift = index_target; shift < index_source; shift++)
  {
    for (size_t i = 0; i < LOG_SIGNALS_IN; i++)
    {
      if ((mem_to_prt == false) && (mem_from_prt == true))
      {
        *((__LOG_INPUT *)(base_target) + shift*LOG_SIGNALS_IN + i) = *((__LOG_INPUT *)(base_source) + 1 + shift*LOG_SIGNALS_IN + i);
      }
      else if ((mem_to_prt == true) && (mem_from_prt == false))
      {
        *((__LOG_INPUT *)(base_target) + 1 + shift*LOG_SIGNALS_IN + i) = *((__LOG_INPUT *)(base_source) + shift*LOG_SIGNALS_IN + i);
      }
      else if ((mem_to_prt == false) && (mem_from_prt == false))
      {
        *((__LOG_INPUT *)(base_target) + shift*LOG_SIGNALS_IN + i) = *((__LOG_INPUT *)(base_source) + shift*LOG_SIGNALS_IN + i);
      }
      else
      {
        //Якщо сюди дійшла програма, значить відбулася недопустива помилка, тому треба зациклити програму, щоб вона пішла на перезагрузку
        total_error_sw_fixed(46);
      }
    }
  }
}
/*****************************************************/

/*****************************************************/
//Розмір у байтах всіх налаштувань (фіксованих і змінних)
/*****************************************************/
size_t size_all_settings(void)
{
  size_t size = sizeof(__SETTINGS_FIX);
  for (__id_fb i = _ID_FB_FIRST_VAR; i < _ID_FB_LAST_VAR; i++)
  {
    size_t size_block;
    switch (i)
    {
    case ID_FB_INPUT:
      {
        size_block = current_config.n_input*sizeof(__settings_for_INPUT);
        break;
      }
    case ID_FB_OUTPUT:
    case ID_FB_LED:
      {
        size_block = ((i == ID_FB_OUTPUT) ? current_config.n_output : current_config.n_led)*sizeof(__settings_for_OUTPUT_LED);
        break;
      }
    case ID_FB_BUTTON:
      {
        size_block = current_config.n_button*0;
        break;
      }
    case ID_FB_ALARM:
      {
        size_block = current_config.n_alarm*sizeof(__settings_for_ALARM);
        break;
      }
    case ID_FB_GROUP_ALARM:
      {
        size_block = current_config.n_group_alarm*sizeof(__settings_for_GROUP_ALARM);
        break;
      }
    case ID_FB_AND:
      {
        size_block = current_config.n_and*sizeof(__settings_for_AND);
        break;
      }
    case ID_FB_OR:
      {
        size_block = current_config.n_or*sizeof(__settings_for_OR);
        break;
      }
    case ID_FB_XOR:
      {
        size_block = current_config.n_xor*sizeof(__settings_for_XOR);
        break;
      }
    case ID_FB_NOT:
      {
        size_block = current_config.n_not*sizeof(__settings_for_NOT);
        break;
      }
    case ID_FB_TIMER:
      {
        size_block = current_config.n_timer*sizeof(__settings_for_TIMER);
        break;
      }
    case ID_FB_TRIGGER:
      {
        size_block = current_config.n_trigger*sizeof(__settings_for_TRIGGER);
        break;
      }
    case ID_FB_MEANDER:
      {
        size_block = current_config.n_meander*sizeof(__settings_for_MEANDER);
        break;
      }
    case ID_FB_TU:
      {
        size_block = current_config.n_tu*sizeof(__settings_for_TU);
        break;
      }
    case ID_FB_TS:
      {
        size_block = current_config.n_ts*sizeof(__settings_for_TS);
        break;
      }
    case ID_FB_EVENT_LOG:
      {
        size_block = current_config.n_log*sizeof(__LOG_INPUT)*LOG_SIGNALS_IN;
        break;
      }
    default:
      {
        //Якщо сюди дійшла програма, значить відбулася недопустива помилка, тому треба зациклити програму, щоб вона пішла на перезагрузку
        total_error_sw_fixed(52);
      } 
    }
    
    size += size_block;
  }
  
  return size;
  
}
/*****************************************************/

/*****************************************************/
//Відновлення налаштувань з контрольної версії
/*****************************************************/
void copy_settings(
                     __CONFIG *source_conf, 

                     __SETTINGS_FIX *target_fix, 
                     __SETTINGS_FIX *source_fix, 
                     uintptr_t *target_dyn[], 
                     uintptr_t *source_dyn[]
                    )
{
  *target_fix = *source_fix;
  
  for (__id_fb i = _ID_FB_FIRST_VAR; i < _ID_FB_LAST_VAR; i++)
  {
    if (source_dyn[i - _ID_FB_FIRST_VAR] != NULL)
    {
      uint32_t n_prev;
      void (*copy_settings_LN)(unsigned int, unsigned int, uintptr_t *, uintptr_t *, size_t, size_t);
      switch (i)
      {
        case ID_FB_INPUT:
          {
            //Дискретний вхід
            n_prev = source_conf->n_input;
            copy_settings_LN = copy_settings_INPUT;

            break;
          }
        case ID_FB_OUTPUT:
        case ID_FB_LED:
          {
            //Дискретний вихід або Світлоіндимкатор
            n_prev = (i == ID_FB_OUTPUT) ? source_conf->n_output : source_conf->n_led;
            copy_settings_LN = copy_settings_OUTPUT_LED;

            break;
          }
        case ID_FB_BUTTON:
          {
            //ФК
            n_prev = source_conf->n_button;
            copy_settings_LN = NULL;

            break;
          }
        case ID_FB_ALARM:
          {
            //Елемент "СЗС"
            n_prev = source_conf->n_alarm;
            copy_settings_LN = copy_settings_ALARM;

            break;
          }
        case ID_FB_GROUP_ALARM:
          {
            //Елемент "ШГС"
            n_prev = source_conf->n_group_alarm;
            copy_settings_LN = copy_settings_GROUP_ALARM;

            break;
          }
        case ID_FB_AND:
          {
            //Елемент "І"
            n_prev = source_conf->n_and;
            copy_settings_LN = copy_settings_AND;

            break;
          }
        case ID_FB_OR:
          {
            //Елемент "АБО"
            n_prev = source_conf->n_or;
            copy_settings_LN = copy_settings_OR;

            break;
          }
        case ID_FB_XOR:
          {
            //Елемент "Викл.АБО"
            n_prev = source_conf->n_xor;
            copy_settings_LN = copy_settings_XOR;

            break;
          }
        case ID_FB_NOT:
          {
            //Елемент "НЕ"
            n_prev = source_conf->n_not;
            copy_settings_LN = copy_settings_NOT;

            break;
          }
        case ID_FB_TIMER:
          {
            //Елемент "Таймер"
            n_prev = source_conf->n_timer;
            copy_settings_LN = copy_settings_TIMER;

            break;
          }
        case ID_FB_TRIGGER:
          {
            //Елемент "Триґер"
            n_prev = source_conf->n_trigger;
            copy_settings_LN = copy_settings_TRIGGER;

            break;
          }
        case ID_FB_MEANDER:
          {
            //Функціональний блок "Генератор періодичних сигналів"
            n_prev = source_conf->n_meander;
            copy_settings_LN = copy_settings_MEANDER;

            break;
          }
        case ID_FB_TU:
          {
            //ТУ
            n_prev = source_conf->n_tu;
            copy_settings_LN = copy_settings_TU;

            break;
          }
        case ID_FB_TS:
          {
            //ТС
            n_prev = source_conf->n_ts;
            copy_settings_LN = copy_settings_TS;

            break;
          }
        case ID_FB_EVENT_LOG:
          {
            //Елемент "Журнал подій"
            n_prev = source_conf->n_log;
            copy_settings_LN = copy_settings_LOG;

            break;
          }
        default:
          {
            //Якщо сюди дійшла програма, значить відбулася недопустива помилка, тому треба зациклити програму, щоб вона пішла на перезагрузку
            total_error_sw_fixed(57);
          }
      }
      
      if ((n_prev != 0) && 
          (
           (target_dyn[i - _ID_FB_FIRST_VAR] != NULL) || 
           (copy_settings_LN == NULL)
          )
         )   
      {
        //Викликаємо функцію повернення нових налаштувань у попередні значення
        if (copy_settings_LN != NULL) (*copy_settings_LN)((target_dyn == spca_of_p_prt), (source_dyn == spca_of_p_prt), target_dyn[i - _ID_FB_FIRST_VAR], source_dyn[i - _ID_FB_FIRST_VAR], 0, n_prev);
      }
      else
      {
        //Якщо сюди дійшла програма, значить відбулася недопустива помилка, тому треба зациклити програму, щоб вона пішла на перезагрузку
        total_error_sw_fixed(59);
      }
    }
  }
}
/*****************************************************/

/*****************************************************/
/*
Виконання змін у кнофігурації і налаштуваннях

Вхідна інформація
-----------------
direction:
1 - внести зміни у "для захистів" структурах і масивах
0 - відновити попердній стан по "для захисту" у стуктурах і масивах "контейнера" і "для редагування"

source - елементи з перерахування enum __source_fix_changes


Вихідна інформація про помилку
-----------------
0 - успішее виконання опреації
1 - недостатньо пам'яті, але вдалося відновити попередній сатн по "для захисту"
2 - недостатньо пам'яті і не вдалося відновити попередній стан по "для захисту"
*/
/*****************************************************/
unsigned int set_config_and_settings(unsigned int direction, unsigned int source)
{
  unsigned int error = 0;
  if (direction != 0)
  {
    unsigned int reconfiguration_RS_485 = false, reconfiguration_RS_485_with_reset_usart = false;
      unsigned int set_password_USB = false, set_password_RS485 = false;
    if (
        (settings_fix.baud_RS485 != settings_fix_prt.baud_RS485) ||
        (settings_fix.pare_bit_RS485 != settings_fix_prt.pare_bit_RS485) ||
        (settings_fix.number_stop_bit_RS485 != settings_fix_prt.number_stop_bit_RS485) ||
        (settings_fix.time_out_1_RS485 != settings_fix_prt.time_out_1_RS485)
       )
    {
      //Помічаємо, що треба переконфігурувати інтерфейс RS-485
      reconfiguration_RS_485 = true;
    
      if (
          (settings_fix.baud_RS485 != settings_fix_prt.baud_RS485) ||
          (settings_fix.pare_bit_RS485 != settings_fix_prt.pare_bit_RS485) ||
          (settings_fix.number_stop_bit_RS485 != settings_fix_prt.number_stop_bit_RS485)
         )
      {
        //Помічаємо, що треба переконфігурувати USART для інтерфейсу RS-485
        reconfiguration_RS_485_with_reset_usart = true;
      }
      
      if (
          (settings_fix.password_interface_USB != settings_fix_prt.password_interface_USB) &&
          (settings_fix.password_interface_USB != 0)  
         )   
      {
        set_password_USB = true;
      }
  
      if (
          (settings_fix.password_interface_RS485 != settings_fix_prt.password_interface_RS485) &&
          (settings_fix.password_interface_RS485 != 0)  
         )   
      {
        set_password_RS485 = true;
      }
    }

    __result_dym_mem_select result = DYN_MEM_SELECT_OK;
    //Активація внесених змін
    if (config_settings_modified & MASKA_CHANGED_CONFIGURATION)
    {
      __CONFIG current_config_tmp = current_config_prt;
      TIM_Cmd(TIM2, DISABLE); //Зупиняємо систему логіки
      result = allocate_dynamic_memory_for_settings(REMAKE_DYN_MEM, true, spca_of_p_prt, NULL, &current_config_prt, &current_config, &current_config_tmp);
      if (result == DYN_MEM_SELECT_OK)
      {
        //Фіксуємо, що відбулася зміна конфігурації
        _SET_BIT(set_diagnostyka, EVENT_CHANGE_CONFIGURATION_BIT);
      }
    }

    if (result == DYN_MEM_SELECT_OK)
    {
      if (config_settings_modified & MASKA_CHANGED_SETTINGS)
      {
        //Відбувалися зміни у налаштуваннях
        TIM_Cmd(TIM2, DISABLE); //Зупиняємо систему логіки
        copy_settings(&current_config, &settings_fix_prt, &settings_fix, spca_of_p_prt, sca_of_p);
        //Фіксуємо, що відбулася зміна налаштувань
        _SET_BIT(set_diagnostyka, EVENT_CHANGE_SETTINGS_BIT);
        
        /***
          Зміни у Андрієвій системі
        ***/
        unsigned int tmp;
        long res = ChangeCfg((void*)&tmp);
        if (res != 0) result = PRT_MEM_ERROR;
        /***/
      }
    }
    else if (result == DYN_MEM_NO_ENOUGH_MEM) 
    {
      TIM_Cmd(TIM2, ENABLE); //Відновлюємо роботу системи логіки
      /*
      при такому негативному резульаті зміни конфігурації все ж таки конфігурація повернулася 
      до свого попереднього стану, тому можна відновити інших більш пріоритетних систем, зокрема,
      системи захиств.
      У іншому випадку цього робити не можна, бо ми не знаємо, у якому стані зараз масиви налаштувань,
      які змінювалися у процесі зміни конфігурації
      */
    }
    
    
    if (result == DYN_MEM_SELECT_OK)
    {
      /*
      Дії по встановленню мінімальних налаштувань
      */
      if (source == DEFAULT_PARAMS_FIX_CHANGES)
      {
        enum _menu2_levels temp_value_level = current_state_menu2.current_level;
        while(
              (temp_value_level >= __BEGIN_SETTINGS_MENU2_LEVEL) &&
              (temp_value_level <  __NEXT_AFTER_SETTINGS_MENU2_LEVEL)
             )
        {
          temp_value_level = previous_level_in_current_level_menu2[temp_value_level];
        }
        if (temp_value_level != current_state_menu2.current_level)
        {
          current_state_menu2.current_level = temp_value_level;
          new_level_menu();
        }
        reconfiguration_RS_485 = true;
        reconfiguration_RS_485_with_reset_usart = true;
        set_password_USB = true;
        set_password_RS485 = true;
      }
      /***/

      /*
      Дії по зміні налаштувань RS-485
      */
      if (reconfiguration_RS_485 != 0)
      {
        //Підраховуємо нову величину затримки у бітах, яка допускається між байтами у RS-485 згідно з визначеними настройками
        calculate_namber_bit_waiting_for_rs_485();
        //Виставляємо команду про переконфігурування RS-485
        if (reconfiguration_RS_485_with_reset_usart != 0) make_reconfiguration_RS_485 = 0xff;
      }
      if (set_password_USB   != false) password_set_USB   = 1;
      if (set_password_RS485 != false) password_set_RS485 = 1;
      /***/
      
      _SET_BIT(clear_diagnostyka, ERROR_NO_FREE_DYNAMIC_MEMORY_BIT);
      _SET_BIT(clear_diagnostyka, ERROR_PRT_MEMORY_BIT);
      
      if (config_settings_modified & MASKA_CHANGED_CONFIGURATION)
      {
        //Записуємо час останньої зміни конфігурації
        uint8_t *label_to_time_array;
        if (copying_time == 0) label_to_time_array = time;
        else label_to_time_array = time_copy;
        
        for (size_t i = 0; i < 7; i++) current_config_prt.time_config[i] = current_config.time_config[i] = current_config_edit.time_config[i] = *(label_to_time_array + i);
        current_config_prt.time_config[7] = current_config.time_config[7] = current_config_edit.time_config[7] = (uint8_t)(source & 0xff);
        
        _SET_BIT(control_i2c_taskes, TASK_START_WRITE_CONFIG_EEPROM_BIT);
        
        //Зміна конфігурції може змінити розміри налаштувань. а це може вплинути на розміщення триґерної інформації, тому її також записуємо
        _SET_BIT(control_i2c_taskes, TASK_START_WRITE_TRG_FUNC_EEPROM_BIT);
        //Скидаємо можливу активну задачу самоконтролю по резервній копії для триґерної інформації
        periodical_tasks_TEST_TRG_FUNC_LOCK = false;
      }
      
      //Записуємо час останньої зміни конфігурації
      uint8_t *label_to_time_array;
      if (copying_time == 0) label_to_time_array = time;
      else label_to_time_array = time_copy;
        
      for (size_t i = 0; i < 7; i++) settings_fix_prt.time_setpoints[i] = settings_fix.time_setpoints[i] = settings_fix_edit.time_setpoints[i] = *(label_to_time_array + i);
      settings_fix_prt.time_setpoints[7] = settings_fix.time_setpoints[7] = settings_fix_edit.time_setpoints[7] = (uint8_t)(source & 0xff);
      
      _SET_BIT(control_i2c_taskes, TASK_START_WRITE_SETTINGS_EEPROM_BIT);
      
      /***
      Очікуємо, поки процес запису у EEPROM повністю завершиться
      ***/
      while(
            (
             (control_i2c_taskes[0]     != 0) ||
             (control_i2c_taskes[1]     != 0) ||
             (driver_i2c.state_execution > 0)
            )
            ||
            (
             (control_tasks_dataflash != 0) ||
             (state_execution_spi_df[INDEX_DATAFLASH_1] != TRANSACTION_EXECUTING_NONE) ||
             (state_execution_spi_df[INDEX_DATAFLASH_2] != TRANSACTION_EXECUTING_NONE)
            )
           )
      {
        //Робота з watchdogs
        if((control_word_of_watchdog & (UNITED_BITS_WATCHDOG & (uint32_t)(~(WATCHDOG_PROTECTION | WATCHDOG_PROTECTION_1)))) == (UNITED_BITS_WATCHDOG & (uint32_t)(~(WATCHDOG_PROTECTION | WATCHDOG_PROTECTION_1))))
        {
          //Змінюємо стан біту зовнішнього Watchdog на протилежний
          GPIO_WriteBit(
                        GPIO_EXTERNAL_WATCHDOG,
                        GPIO_PIN_EXTERNAL_WATCHDOG,
                        (BitAction)(1 - GPIO_ReadOutputDataBit(GPIO_EXTERNAL_WATCHDOG, GPIO_PIN_EXTERNAL_WATCHDOG))
                       );
          control_word_of_watchdog &= (UNITED_BITS_WATCHDOG & (uint32_t)(~(WATCHDOG_PROTECTION | WATCHDOG_PROTECTION_1)));
        }

        main_routines_for_i2c();
        changing_diagnostyka_state();//Підготовлюємо новий потенційно можливий запис для реєстратора програмних подій
        if (_CHECK_SET_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT) != 0)
        {
          //Повне роозблоковування обміну з мікросхемами для драйверу I2C
          _CLEAR_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT);
        }
      }
      /***/
      
      /***
      Подаємо команду на перезапуск
      ***/
      NVIC_SystemReset();
      /***/
    }
    else if (result == DYN_MEM_NO_ENOUGH_MEM) 
    {
      _SET_BIT(set_diagnostyka, ERROR_NO_FREE_DYNAMIC_MEMORY_BIT);
      _SET_BIT(clear_diagnostyka, ERROR_PRT_MEMORY_BIT);
      
      error = 1;
    }
    else 
    {
      if (result == DYN_MEM_TOTAL_ERROR)
      {
        _SET_BIT(set_diagnostyka, ERROR_NO_FREE_DYNAMIC_MEMORY_BIT);
        _SET_BIT(clear_diagnostyka, ERROR_PRT_MEMORY_BIT);
      }
      else if (result == PRT_MEM_ERROR)
      {
        _SET_BIT(set_diagnostyka, ERROR_PRT_MEMORY_BIT);
        _SET_BIT(clear_diagnostyka, ERROR_NO_FREE_DYNAMIC_MEMORY_BIT);
      }
      
      error = 2;
    }
  }
  
  if (
      (error == 1) ||
      (direction == 0)
     ) 
  {
    //Повернення до стану до редагування
    if (
        (error == 1) ||
        (config_settings_modified & MASKA_CHANGED_CONFIGURATION)
       )   
    {
      //Відбувалися зміни у конфігурації

      //Необхідно по даних "для захистів" відновити дані у "контейнері" і "для редагування"
      __result_dym_mem_select          result = allocate_dynamic_memory_for_settings(RESTORE_DYN_MEM, false, sca_of_p     , spca_of_p_prt, &current_config     , &current_config_prt, &current_config_prt);
      if (result == DYN_MEM_SELECT_OK) result = allocate_dynamic_memory_for_settings(RESTORE_DYN_MEM, false, sca_of_p_edit, sca_of_p     , &current_config_edit, &current_config    , &current_config    );
      
      if (result != DYN_MEM_SELECT_OK) 
      {
        _SET_BIT(set_diagnostyka, ERROR_NO_FREE_DYNAMIC_MEMORY_BIT);
        error = 2;
      }
      else if (error == 0)
      {
        _SET_BIT(clear_diagnostyka, ERROR_NO_FREE_DYNAMIC_MEMORY_BIT);
      }
    }
    
    if (
        (error == 1) ||
        (config_settings_modified & MASKA_CHANGED_SETTINGS)
       )   
    {
      //Відновлюємо зміни у налаштуваннях
      copy_settings(&current_config_prt, &settings_fix     , &settings_fix_prt, sca_of_p     , spca_of_p_prt);
      copy_settings(&current_config    , &settings_fix_edit, &settings_fix    , sca_of_p_edit, sca_of_p     );
    }
        
  }
  
  return error;
}
/*****************************************************/

/*****************************************************/
//Функція обновлення змінних при зміні конфігурації
/*****************************************************/
__result_dym_mem_select action_after_changing_of_configuration(void)
{
  /*
  Так, як функція allocate_dynamic_memory_for_settings встановлює нову конфінурацію і виділяє пам'ять під неї,
  а ми вже значення у конфігурацї змінили у стурктурі для редагування current_config_edit,
  то цю структуру спочатку копіюємо у тимчасову структуру, відновлюємо попереднє значення
  і тоді вже функцією allocate_dynamic_memory_for_settings виконуємо дії по встановленні нової конфігурації і виділенні
  динамічної пам'яті
  */
  __CONFIG current_config_tmp = current_config_edit;
  current_config_edit = current_config;
  __result_dym_mem_select result = allocate_dynamic_memory_for_settings(REMAKE_DYN_MEM, false, sca_of_p_edit, sca_of_p, &current_config_edit, &current_config_tmp , &current_config);
  if (result == DYN_MEM_SELECT_OK) 
  {
    result = allocate_dynamic_memory_for_settings(REMAKE_DYN_MEM, false, sca_of_p, spca_of_p_prt, &current_config, &current_config_edit, &current_config_prt);
    if (result == DYN_MEM_NO_ENOUGH_MEM)
    {
      //Треба відновити у пам'яті для редагування попередню конфігурацію
      __result_dym_mem_select result_1 =  allocate_dynamic_memory_for_settings(RESTORE_DYN_MEM, false, sca_of_p_edit, sca_of_p, &current_config_edit, &current_config, &current_config);
      if (result_1 == DYN_MEM_SELECT_OK) 
      {
        //Відновлюємо зміни у налаштуваннях
        copy_settings(&current_config, &settings_fix_edit, &settings_fix, sca_of_p_edit, sca_of_p);
      }
      else result = DYN_MEM_TOTAL_ERROR;
    }
  }
  if (result == DYN_MEM_SELECT_OK)
  {
    uint32_t number[NUMBER_ALL_BLOCKS] = {
                                          1,
                                          current_config.n_input, 
                                          current_config.n_output,
                                          current_config.n_led, 
                                          current_config.n_button, 
                                          current_config.n_alarm,
                                          current_config.n_group_alarm,
                                          current_config.n_and,
                                          current_config.n_or,
                                          current_config.n_xor,
                                          current_config.n_not,
                                          current_config.n_timer,
                                          current_config.n_trigger,
                                          current_config.n_meander,
                                          current_config.n_tu,
                                          current_config.n_ts,
                                          (current_config.n_log != 0) ? 1 : 0,
                                         };  
    for (__id_fb i = _ID_FB_FIRST_VAR; i < _ID_FB_LAST_VAR; i++)
    {
      if (
          (i != ID_FB_GROUP_ALARM) &&
          (i != ID_FB_INPUT) &&
          (i != ID_FB_BUTTON) &&
          (i != ID_FB_MEANDER)
         )
      {
        uint32_t *p_param, *p_param_edit;
        intptr_t _n;
        unsigned int moveable_inputs = false;
        for (size_t j = 0; j < number[i - _ID_FB_FIRST_ALL]; j++)
        {
          switch (i)
          {
          case ID_FB_OUTPUT:
          case ID_FB_LED:
            {
              _n = OUTPUT_LED_SIGNALS_IN_TOTAL;
              p_param      = (((__settings_for_OUTPUT_LED*)sca_of_p[i - _ID_FB_FIRST_VAR])[j].param);
              p_param_edit = (((__settings_for_OUTPUT_LED*)sca_of_p_edit[i - _ID_FB_FIRST_VAR])[j].param);
              break;
            }
          case ID_FB_ALARM:
            {
              _n = ALARM_SIGNALS_IN;
              p_param      = (((__settings_for_ALARM*)sca_of_p[i - _ID_FB_FIRST_VAR])[j].param);
              p_param_edit = (((__settings_for_ALARM*)sca_of_p_edit[i - _ID_FB_FIRST_VAR])[j].param);
              break;
            }
          case ID_FB_AND:
            {
              _n = AND_SIGNALS_IN;
              moveable_inputs = true;
              p_param      = (((__settings_for_AND*)sca_of_p[i - _ID_FB_FIRST_VAR])[j].param);
              p_param_edit = (((__settings_for_AND*)sca_of_p_edit[i - _ID_FB_FIRST_VAR])[j].param);
              break;
            }
          case ID_FB_OR:
            {
              _n = OR_SIGNALS_IN;
              moveable_inputs = true;
              p_param      = (((__settings_for_OR*)sca_of_p[i - _ID_FB_FIRST_VAR])[j].param);
              p_param_edit = (((__settings_for_OR*)sca_of_p_edit[i - _ID_FB_FIRST_VAR])[j].param);
              break;
            }
          case ID_FB_XOR:
            {
              _n = 2;
              moveable_inputs = true;
              p_param      = (((__settings_for_XOR*)sca_of_p[i - _ID_FB_FIRST_VAR])[j].param);
              p_param_edit = (((__settings_for_XOR*)sca_of_p_edit[i - _ID_FB_FIRST_VAR])[j].param);
              break;
            }
          case ID_FB_NOT:
            {
              _n = 1;
              p_param      = (((__settings_for_NOT*)sca_of_p[i - _ID_FB_FIRST_VAR])[j].param);
              p_param_edit = (((__settings_for_NOT*)sca_of_p_edit[i - _ID_FB_FIRST_VAR])[j].param);
              break;
            }
          case ID_FB_TIMER:
            {
              _n = TIMER_SIGNALS_IN;
              p_param      = (((__settings_for_TIMER*)sca_of_p[i - _ID_FB_FIRST_VAR])[j].param);
              p_param_edit = (((__settings_for_TIMER*)sca_of_p_edit[i - _ID_FB_FIRST_VAR])[j].param);
              break;
            }
          case ID_FB_TRIGGER:
            {
              _n = TRIGGER_SIGNALS_IN;
              p_param      = (((__settings_for_TRIGGER*)sca_of_p[i - _ID_FB_FIRST_VAR])[j].param);
              p_param_edit = (((__settings_for_TRIGGER*)sca_of_p_edit[i - _ID_FB_FIRST_VAR])[j].param);
              break;
            }
          case ID_FB_TU:
            {
              _n = TU_SIGNALS_IN;
              p_param      = (((__settings_for_TU*)sca_of_p[i - _ID_FB_FIRST_VAR])[j].param);
              p_param_edit = (((__settings_for_TU*)sca_of_p_edit[i - _ID_FB_FIRST_VAR])[j].param);
              break;
            }
          case ID_FB_TS:
            {
              _n = TS_SIGNALS_IN;
              p_param      = (((__settings_for_TS*)sca_of_p[i - _ID_FB_FIRST_VAR])[j].param);
              p_param_edit = (((__settings_for_TS*)sca_of_p_edit[i - _ID_FB_FIRST_VAR])[j].param);
              break;
            }
          case ID_FB_EVENT_LOG:
            {
              _n = LOG_SIGNALS_IN*current_config.n_log;
              moveable_inputs = true;
              p_param      = (__LOG_INPUT*)sca_of_p[i - _ID_FB_FIRST_VAR];
              p_param_edit = (__LOG_INPUT*)sca_of_p_edit[i - _ID_FB_FIRST_VAR];
              break;
            }
          default:
            {
              //Якщо сюди дійшла програма, значить відбулася недопустива помилка, тому треба зациклити програму, щоб вона пішла на перезагрузку
              total_error_sw_fixed(76);
            }
          }
        
          intptr_t shift = 0;
          for (intptr_t k = 0; k < _n; k++)
          {
            uint32_t param_input = *(p_param + k - shift);
            unsigned int id_input   = (param_input >> SFIFT_PARAM_ID ) & MASKA_PARAM_ID ;
            unsigned int n_input    = (param_input >> SFIFT_PARAM_N  ) & MASKA_PARAM_N  ;
//            unsigned int out_input  = (param_input >> SFIFT_PARAM_OUT) & MASKA_PARAM_OUT;
          
            //Робимо зміщення параметрування, щоб не було пропусків
            if (n_input > number[id_input - _ID_FB_FIRST_ALL])
            {
              *(p_param + k - shift) = *(p_param_edit + k - shift) = 0;
            
              if (
                  (_n > 1) &&
                  (moveable_inputs != false)  
                 )
              {
                for (intptr_t l = (k + 1); l < _n; l++)
                {
                  *(p_param + (l - 1) - shift) = *(p_param_edit + (l - 1) - shift) = *(p_param + l - shift);
                }
                *(p_param + (_n - 1) - shift) = *(p_param_edit + (_n - 1) - shift) = 0;
                
                shift++;
              }
            }
          }
        }
      }
    }
  }
  
  return result;
}
/*****************************************************/

/*****************************************************/
/*****************************************************/
//
/*****************************************************/
