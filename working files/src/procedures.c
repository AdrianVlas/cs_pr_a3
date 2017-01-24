#include "header.h"

/*****************************************************/
//Функція обновлення змінних при зміні конфігурації
/*****************************************************/
unsigned int action_after_changing_of_configuration(unsigned int new_configuration, __SETTINGS_OLD *target_label)
{
  unsigned int error_window = 0;
  
  /************************/
  //Спершу перевіряємо чи не знаходимося зараз ми у такому вікні, яке забороняє змінювати текучу конфігурацію
  /************************/
  //Перевірка "Перевірка фазування"
  if ((new_configuration & (1<<CTRL_PHASE_BIT_CONFIGURATION)) == 0)
  {
    if(
       (current_ekran.current_level == EKRAN_CHOOSE_SETTINGS_CTRL_PHASE)
       ||
       (current_ekran.current_level == EKRAN_SETPOINT_CTRL_PHASE)
       ||  
       (current_ekran.current_level == EKRAN_TIMEOUT_CTRL_PHASE)
       ||  
       (current_ekran.current_level == EKRAN_CONTROL_CTRL_PHASE)
      )
      error_window |= (1 << CTRL_PHASE_BIT_CONFIGURATION );
  }
  /************************/
  
  if (error_window == 0)
  {
    //Вводимо нову конфігурацю у цільову структуру
    target_label->configuration = new_configuration;
    
    unsigned int maska[N_BIG] = {0, 0, 0, 0, 0, 0, 0};

    //Перевіряємо, чи "Перевірка фазування" зараз знята з конфігурації
    if ((target_label->configuration & (1<<CTRL_PHASE_BIT_CONFIGURATION)) == 0)
    {
      //Виводим всі "Перевірки фазування"
      target_label->control_ctrl_phase &= (unsigned int)(~CTR_CTRL_PHASE_U | CTR_CTRL_PHASE_PHI | CTR_CTRL_PHASE_F | CTR_CTRL_PHASE_SEQ_TN1 | CTR_CTRL_PHASE_SEQ_TN2);
   
      //Формуємо маски функцій "Перевірка фазування"
      maska[0] = 0;
      maska[1] = 0;
      maska[2] = 0;
      maska[3] = 0;
      maska[4] = 0;
      maska[5] = 0;
      for (int i = 0; i < NUMBER_CTRL_PHASE_SIGNAL_FOR_RANG; i++)
        _SET_BIT(
                 maska, 
                 (
                  NUMBER_GENERAL_SIGNAL_FOR_RANG    + 
                  i
                 )
                );


      //Знімаємо всі функції для ранжування виходів
      for (int i = 0; i < NUMBER_OUTPUTS; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_outputs[N_BIG*i+j] &= ~maska[j];
      }
      //Знімаємо всі функції для ранжування світоіндикаторів
      for (int i = 0; i < NUMBER_LEDS; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_leds[N_BIG*i+j] &= ~maska[j];
      }
      //Знімаємо всі функції для ранжування аналогового, дискретного реєстраторів, тиші і скидання реле
      for (unsigned int j = 0; j < N_BIG; j++ ) 
      {
        target_label->ranguvannja_analog_registrator[j]  &= ~maska[j];
        target_label->ranguvannja_digital_registrator[j] &= ~maska[j];
        target_label->ranguvannja_silence[j] &= ~maska[j];
        target_label->ranguvannja_reset[j] &= ~maska[j];
      }
      //Знімаємо всі функції для ранжування сигналізацій
      for (int i = 0; i < NUMBER_ALARMS; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_alarms[N_BIG*i+j] &= ~maska[j];
      }
      //Знімаємо всі функції для ранжування оприділювальних функцій
      for (int i = 0; i < NUMBER_DEFINED_FUNCTIONS; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_df[N_BIG*i+j] &= ~maska[j];
      }
      //Знімаємо всі функції для ранжування оприділювальних триґерів
      for (int i = 0; i < NUMBER_DEFINED_TRIGGERS; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_set_dt[N_BIG*i+j] &= ~maska[j];
      }
  
      //Знімаємо всі функції для ранжування визначуваних "І"
      for(unsigned int i = 0; i < NUMBER_DEFINED_AND; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_and[N_BIG*i+j] &= ~maska[j];
      }
  
      //Знімаємо всі функції для ранжування визначуваних "АБО"
      for(unsigned int i = 0; i < NUMBER_DEFINED_OR; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_or[N_BIG*i+j] &= ~maska[j];
      }
  
      //Знімаємо всі функції для ранжування визначуваних "Викл.АБО"
      for(unsigned int i = 0; i < NUMBER_DEFINED_XOR; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_xor[N_BIG*i+j] &= ~maska[j];
      }
  
      //Знімаємо всі функції для ранжування визначуваних "НЕ"
      for(unsigned int i = 0; i < NUMBER_DEFINED_NOT; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_not[N_BIG*i+j] &= ~maska[j];
      }
    }

    //"Розширена логіка"
    for (unsigned int i = 0; i < N_BIG; i++ ) maska[i] = 0;

    //Формуємо маски тільки тих сигналів розширеної логіки, які виведені з конфігурації у кількісному значенні
    unsigned int array_defined_logic[NUMBER_DEFINED_ELEMENTS][2] =
    {
      {target_label->number_defined_df , NUMBER_DEFINED_FUNCTIONS},
      {target_label->number_defined_dt , NUMBER_DEFINED_TRIGGERS },
      {target_label->number_defined_and, NUMBER_DEFINED_AND      },
      {target_label->number_defined_or , NUMBER_DEFINED_OR       },
      {target_label->number_defined_xor, NUMBER_DEFINED_XOR      },
      {target_label->number_defined_not, NUMBER_DEFINED_NOT      }
    };
    const unsigned int others_signals[NUMBER_DEFINED_ELEMENTS] = {2, 3, 1, 1, 1, 1};
      
    unsigned int others_shift = NUMBER_GENERAL_SIGNAL_FOR_RANG;
    
    for (unsigned int index = 0; index < NUMBER_DEFINED_ELEMENTS; index++)
    {
      for (unsigned int i = 0; i < others_signals[index]*(array_defined_logic[index][1] - array_defined_logic[index][0]); i++)
        _SET_BIT(maska, (others_shift + others_signals[index]*array_defined_logic[index][0] + i));
       
      others_shift += others_signals[index]*array_defined_logic[index][1];
    }

    //Знімаємо всі функції для ранжування виходів
    for (int i = 0; i < NUMBER_OUTPUTS; i++)
    {
      for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_outputs[N_BIG*i+j] &= ~maska[j];
    }
    //Знімаємо всі функції для ранжування світоіндикаторів
    for (int i = 0; i < NUMBER_LEDS; i++)
    {
      for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_leds[N_BIG*i+j] &= ~maska[j];
    }
    //Знімаємо всі функції для ранжування аналогового, дискретного реєстраторів, тиші і скидання реле
    for (unsigned int j = 0; j < N_BIG; j++ ) 
    {
      target_label->ranguvannja_analog_registrator[j]  &= ~maska[j];
      target_label->ranguvannja_digital_registrator[j] &= ~maska[j];
      target_label->ranguvannja_silence[j] &= ~maska[j];
      target_label->ranguvannja_reset[j] &= ~maska[j];
    }
    //Знімаємо всі функції для ранжування сигналізацій
    for (int i = 0; i < NUMBER_ALARMS; i++)
    {
      for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_alarms[N_BIG*i+j] &= ~maska[j];
    }
    //Очищємо всі функції для ранжування оприділювальних функцій
    for (int i = 0; i < NUMBER_DEFINED_FUNCTIONS; i++)
    {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_df[N_BIG*i+j] &= ~maska[j];
    }
    //Очищємо всі функції для ранжування оприділювальних триґерів
    for (int i = 0; i < NUMBER_DEFINED_TRIGGERS; i++)
    {
      for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_set_dt[N_BIG*i+j] &= ~maska[j];
    }
  
    //Очищємо всі функції для ранжування визначуваних "І"
    for(unsigned int i = 0; i < NUMBER_DEFINED_AND; i++)
    {
      for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_and[N_BIG*i+j] &= ~maska[j];
    }
  
    //Очищємо всі функції для ранжування визначуваних "АБО"
    for(unsigned int i = 0; i < NUMBER_DEFINED_OR; i++)
    {
      for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_or[N_BIG*i+j] &= ~maska[j];
    }
  
    //Очищємо всі функції для ранжування визначуваних "Викл.АБО"
    for(unsigned int i = 0; i < NUMBER_DEFINED_XOR; i++)
    {
      for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_xor[N_BIG*i+j] &= ~maska[j];
    }
  
    //Очищємо всі функції для ранжування визначуваних "НЕ"
    for(unsigned int i = 0; i < NUMBER_DEFINED_NOT; i++)
    {
      for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_not[N_BIG*i+j] &= ~maska[j];
    }
  }
  
  return error_window;
}
/*****************************************************/

/*****************************************************/
//Функція обновлення змінних при зміні кількості елементів розширеної логіки
/*****************************************************/
void action_after_changing_number_el(__SETTINGS_OLD *target_label, unsigned int element)
{
  unsigned int maska[N_BIG] = {0, 0, 0, 0, 0, 0, 0};

  //Формуємо маски тільки тих сигналів розширеної логіки, які виведені з конфігурації у кількісному значенні
  unsigned int array_defined_logic[NUMBER_DEFINED_ELEMENTS][2] =
  {
    {target_label->number_defined_df , NUMBER_DEFINED_FUNCTIONS},
    {target_label->number_defined_dt , NUMBER_DEFINED_TRIGGERS },
    {target_label->number_defined_and, NUMBER_DEFINED_AND      },
    {target_label->number_defined_or , NUMBER_DEFINED_OR       },
    {target_label->number_defined_xor, NUMBER_DEFINED_XOR      },
    {target_label->number_defined_not, NUMBER_DEFINED_NOT      }
  };
  const unsigned int others_signals[NUMBER_DEFINED_ELEMENTS] = {2, 3, 1, 1, 1, 1};
  
  unsigned int others_shift = NUMBER_GENERAL_SIGNAL_FOR_RANG;
      
  for (unsigned int index = 0; index < element; index++)
  {
    others_shift += others_signals[index]*array_defined_logic[index][1];
  }
  
  //Формуємо маски функцій елемента Розширеної логіки
  for (unsigned int i = 0; i < others_signals[element]*(array_defined_logic[element][1] - array_defined_logic[element][0]); i++)
    _SET_BIT(maska, (others_shift + others_signals[element]*array_defined_logic[element][0] + i));
    
  //Знімаємо всі функції для ранжування виходів
  for (int i = 0; i < NUMBER_OUTPUTS; i++)
  {
    for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_outputs[N_BIG*i+j] &= ~maska[j];
  }
  //Знімаємо всі функції для ранжування світоіндикаторів
  for (int i = 0; i < NUMBER_LEDS; i++)
  {
    for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_leds[N_BIG*i+j] &= ~maska[j];
  }
  //Знімаємо всі функції для ранжування аналогового, дискретного реєстраторів, тиші і скидання реле
  for (unsigned int j = 0; j < N_BIG; j++ ) 
  {
    target_label->ranguvannja_analog_registrator[j]  &= ~maska[j];
    target_label->ranguvannja_digital_registrator[j] &= ~maska[j];
    target_label->ranguvannja_silence[j] &= ~maska[j];
    target_label->ranguvannja_reset[j] &= ~maska[j];
  }
  //Знімаємо всі функції для ранжування сигналізацій
  for (int i = 0; i < NUMBER_ALARMS; i++)
  {
    for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_alarms[N_BIG*i+j] &= ~maska[j];
  }
  //Очищємо всі функції для ранжування оприділювальних функцій
  for (int i = 0; i < NUMBER_DEFINED_FUNCTIONS; i++)
  {
    for (unsigned int j = 0; j < N_BIG; j++ ) 
    {
        target_label->ranguvannja_df[N_BIG*i+j] &= ~maska[j];
    }
  }
  //Очищємо всі функції для ранжування оприділювальних триґерів
  for (int i = 0; i < NUMBER_DEFINED_TRIGGERS; i++)
  {
    for (unsigned int j = 0; j < N_BIG; j++ ) 
    {
      target_label->ranguvannja_set_dt[N_BIG*i+j]    &= ~maska[j];
      target_label->ranguvannja_reset_dt[N_BIG*i+j]  &= ~maska[j];
    }
  }
  
  //Очищємо всі функції для ранжування визначуваних "І"
  for(unsigned int i = 0; i < NUMBER_DEFINED_AND; i++)
  {
    for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_and[N_BIG*i+j] &= ~maska[j];
  }
  
  //Очищємо всі функції для ранжування визначуваних "АБО"
  for(unsigned int i = 0; i < NUMBER_DEFINED_OR; i++)
  {
    for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_or[N_BIG*i+j] &= ~maska[j];
  }
  
  //Очищємо всі функції для ранжування визначуваних "Викл.АБО"
  for(unsigned int i = 0; i < NUMBER_DEFINED_XOR; i++)
  {
    for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_xor[N_BIG*i+j] &= ~maska[j];
  }
  
  //Очищємо всі функції для ранжування визначуваних "НЕ"
  for(unsigned int i = 0; i < NUMBER_DEFINED_NOT; i++)
  {
    for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_not[N_BIG*i+j] &= ~maska[j];
  }
}
/*****************************************************/

/*****************************************************/
//Функція, яка визначає кількість біт затримки, який допускається між байтами у RS-485 згідно з визначеними настройками
/*****************************************************/
void calculate_namber_bit_waiting_for_rs_485(void)
{
  unsigned int number_bits_rs_485_waiting_tmp = 10;
  
  //Підраховуємо кількість біт у байті
  if (current_settings.pare_bit_RS485 > 0) number_bits_rs_485_waiting_tmp++;
  if (current_settings.number_stop_bit_RS485 > 0) number_bits_rs_485_waiting_tmp++;
  
  //Врахування швидкості
  unsigned int multiplicator;
  switch (current_settings.speed_RS485)
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
  number_bits_rs_485_waiting_tmp *= (multiplicator*current_settings.time_out_1_RS485);
  number_bits_rs_485_waiting_tmp /= 10;
  
  number_bits_rs_485_waiting = number_bits_rs_485_waiting_tmp;
}
/*****************************************************/

/******************************************************
//Функція, яка фіксує зміни у настройках і запускає запис настройок у EEPROM
-----------------------------------------------------
setting_rang: 0 - запис уставок
              1 - запис ранжування
              2 - ігнорувати цей параметр

source:       0 - мінімальні параметри
              1 - клавіатура
              2 - USB
              3 - RS-485
---------------------------------------------------
******************************************************/
void fix_change_settings(unsigned int setting_rang, unsigned int source)
{
  if (setting_rang < 2)
  {
    unsigned char *point_to_target;
  
    if (setting_rang == 0) point_to_target = (&current_settings)->time_setpoints;
    else point_to_target = (&current_settings)->time_ranguvannja;
    
    //Записуємо час останніх змін
    unsigned char *label_to_time_array;
    if (copying_time == 0) label_to_time_array = time;
    else label_to_time_array = time_copy;
    for (unsigned int i = 0; i < 7; i++) *(point_to_target + i) = *(label_to_time_array + i);
    *(point_to_target + 7) = (unsigned char)(source & 0xff);
  }
  
  //Помічаємо, що таблиця змінилася і її треба буде з системи захистів зкопіювати у таблицю з якою працює система захистів
  changed_settings = CHANGED_ETAP_ENDED;
  if (_CHECK_SET_BIT(active_functions, RANG_SETTINGS_CHANGED) == 0) current_settings_interfaces = current_settings;
  
  //Запускаємо запис у EEPROM
  _SET_BIT(control_i2c_taskes, TASK_START_WRITE_SETTINGS_EEPROM_BIT);
}
/*****************************************************/

/*****************************************************/
/*
Активація внесених змін у налаштування через інтерфейси
*/
/*****************************************************/
unsigned int set_new_settings_from_interface(unsigned int source)
{
  unsigned int error = 0;
  
  //Вказівник на системний час
  unsigned char *label_to_time_array;
  if (copying_time == 0) label_to_time_array = time;
  else label_to_time_array = time_copy;
  
  if ((type_of_settings_changed & (1 << DEFAULT_SETTINGS_SET_BIT)) != 0)
  {
    for (unsigned int i = 0; i < 7; i++) current_settings_interfaces.time_setpoints[i] = current_settings_interfaces.time_ranguvannja[i] = *(label_to_time_array + i);
    current_settings_interfaces.time_setpoints[7] = current_settings_interfaces.time_ranguvannja[7] = 0;
  }
  
  if ((type_of_settings_changed & (1 << SETTINGS_DATA_CHANGED_BIT)) != 0)
  {
    for (unsigned int i = 0; i < 7; i++) current_settings_interfaces.time_setpoints[i] = *(label_to_time_array + i);
    current_settings_interfaces.time_setpoints[7] = source;
  }
  
  if ((type_of_settings_changed & (1 << RANGUVANNJA_DATA_CHANGED_BIT)) != 0)
  {
    for (unsigned int i = 0; i < 7; i++) current_settings_interfaces.time_ranguvannja[i] = *(label_to_time_array + i);
    current_settings_interfaces.time_ranguvannja[7] = source;
  }
  
  unsigned int reconfiguration_RS_485 = 0, reconfiguration_RS_485_with_reset_usart = 0;
  if (
      (current_settings.speed_RS485 != current_settings_interfaces.speed_RS485) ||
      (current_settings.pare_bit_RS485 != current_settings_interfaces.pare_bit_RS485) ||
      (current_settings.number_stop_bit_RS485 != current_settings_interfaces.number_stop_bit_RS485) ||
      (current_settings.time_out_1_RS485 != current_settings_interfaces.time_out_1_RS485)
     )
  {
    //Помічаємо, що треба переконфігурувати інтерфейс RS-485
    reconfiguration_RS_485 = 1;
    
    if (
        (current_settings.speed_RS485 != current_settings_interfaces.speed_RS485) ||
        (current_settings.pare_bit_RS485 != current_settings_interfaces.pare_bit_RS485) ||
        (current_settings.number_stop_bit_RS485 != current_settings_interfaces.number_stop_bit_RS485)
       )
    {
      //Помічаємо, що треба переконфігурувати USART для інтерфейсу RS-485
      reconfiguration_RS_485_with_reset_usart = 1;
    }
  }
  
  unsigned int change_timeout_ar = 0;
  if (
      (current_settings.prefault_number_periods != current_settings_interfaces.prefault_number_periods) ||
      (current_settings.postfault_number_periods != current_settings_interfaces.postfault_number_periods)
     ) 
  {
    //Помічаємо, що додатково ще треба буде виконати дії по зміні часових витримок аналогового реєстратора
    change_timeout_ar = 1;
    
    unsigned int semaphore_read_state_ar_record_copy = semaphore_read_state_ar_record;

    /*Встановлюємо симафор - суть якого полягає у тому, що якщо процес запису нової 
    аварії не йде - то на час його установлення новий запис починати не можна, якщо ж вже іде ноий запис,
    то він має продовжуватися і, навпаки, блокувати роботу аналогового реєстратора не можна*/
    semaphore_read_state_ar_record = 1;

    if (
        (state_ar_record == STATE_AR_NO_RECORD      ) ||
        (state_ar_record == STATE_AR_TEMPORARY_BLOCK)
       )   
    {
      /*На даний момент не йде запис текучого аналогового аварійного процесу,
      тому для зміни часових настройок тимчасово встановлюємо стан роботи
      аналогового реєстратора у заблокований режим*/
      state_ar_record = STATE_AR_TEMPORARY_BLOCK; 
      
    }
    else
    {
      //Операція тимчасово недоступна, бо іде робота аналогового реєстратора
      error = ERROR_SLAVE_DEVICE_BUSY;
      semaphore_read_state_ar_record = semaphore_read_state_ar_record_copy;
    }
  }
  
  unsigned int set_password_USB = false;
  if (
      (current_settings.password_interface_USB != current_settings_interfaces.password_interface_USB) &&
      (current_settings_interfaces.password_interface_USB != 0)  
     )   
  {
    set_password_USB = true;
  }
  
  unsigned int set_password_RS485 = false;
  if (
      (current_settings.password_interface_RS485 != current_settings_interfaces.password_interface_RS485) &&
      (current_settings_interfaces.password_interface_RS485 != 0)  
     )   
  {
    set_password_RS485 = true;
  }
  
  if (error == 0)
  {
    if ((type_of_settings_changed & (1 << DEFAULT_SETTINGS_SET_BIT)) != 0)
    {
      //Переводимо меню у висхідний стан
      for(unsigned int i=0; i<MAX_LEVEL_MENU; i++)
      {
        if ((i == EKRAN_LEVEL_PASSWORD) || (i == EKRAN_LEVEL_SET_NEW_PASSWORD)) position_in_current_level_menu[i] = INDEX_LINE_NUMBER_1_FOR_LEVEL_PASSWORD;
        else  position_in_current_level_menu[i] = 0;
        previous_level_in_current_level_menu[i] = -1;
      }
  
      //Визначення початкового стану екрану
      current_ekran.current_level = EKRAN_MAIN;
      current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
      current_ekran.position_cursor_y = current_ekran.index_position;
      current_ekran.edition = 0;
      current_ekran.cursor_on = 0;
      current_ekran.cursor_blinking_on = 0;  
    }
    
    if (set_password_USB   != false) password_set_USB   = 1;
    if (set_password_RS485 != false) password_set_RS485 = 1;
    
    //Помічаємо, що поля структури зараз будуть змінені
    changed_settings = CHANGED_ETAP_EXECUTION;
              
    //Копіюємо введені зміни у робочу структуру
    current_settings = current_settings_interfaces;
    if (reconfiguration_RS_485 != 0)
    {
      //Підраховуємо нову величину затримки у бітах, яка допускається між байтами у RS-485 згідно з визначеними настройками
      calculate_namber_bit_waiting_for_rs_485();
      //Виставляємо команду про переконфігурування RS-485
      if (reconfiguration_RS_485_with_reset_usart != 0) make_reconfiguration_RS_485 = 0xff;
    }
    if (
        (state_ar_record == STATE_AR_TEMPORARY_BLOCK) ||
        (semaphore_read_state_ar_record != 0)  
       )
    {
      /*
      Ця ситуація може бути, коли встановлюються мінімальні настройки,
      або коли змінюється ширина доаварійного або післяаварійного процесу
      аналогового реєстратора.
      При цьому завжди має бути, що змінна state_ar_record рівна величині
      STATE_AR_TEMPORARY_BLOCK і змінна semaphore_read_state_ar_record
      не рівна нулю. Ящо ці 
      умови не виконуються - то треба перезапустити прилад,
      бо програмне забезпечення себе веде непередбачуваним шляхом.
      */
      if(
         ((change_timeout_ar != 0)) &&
         (state_ar_record == STATE_AR_TEMPORARY_BLOCK) &&
         (semaphore_read_state_ar_record != 0)  
        )
      {
        //Виконуємо дії по зміні часових витримок аналогового реєстратора
        actions_after_changing_tiomouts_ar();

        //Розблоковуємо роботу аналогового реєстратора
        state_ar_record = STATE_AR_NO_RECORD;

        //Знімаємо семафор
        semaphore_read_state_ar_record = 0;
      }
      else
      {
        //Якщо сюди дійшла програма, значить відбулася недопустива помилка, тому треба зациклити програму, щоб вона пішла на перезагрузку
        total_error_sw_fixed(41);
      }
    }

    fix_change_settings(2, source);

    //Виставляємо признак, що на екрані треба обновити інформацію
    new_state_keyboard |= (1<<BIT_REWRITE);
  }
  
  return error;
}
/*****************************************************/

/******************************************************
Відновлення триґерних функцій
******************************************************/
void restore_trigger_functions(unsigned int *active_functions_point)
{
  active_functions[RANG_DT1_OUT >> 5] |= _CHECK_SET_BIT(active_functions_point, RANG_DT1_OUT);
  active_functions[RANG_DT2_OUT >> 5] |= _CHECK_SET_BIT(active_functions_point, RANG_DT2_OUT);
  active_functions[RANG_DT3_OUT >> 5] |= _CHECK_SET_BIT(active_functions_point, RANG_DT3_OUT);
  active_functions[RANG_DT4_OUT >> 5] |= _CHECK_SET_BIT(active_functions_point, RANG_DT4_OUT);
}
/*****************************************************/

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
  unsigned int clear_diagnostyka_tmp[3], set_diagnostyka_tmp[3];
  
  clear_diagnostyka_tmp[0] = clear_diagnostyka[0];
  clear_diagnostyka_tmp[1] = clear_diagnostyka[1];
  clear_diagnostyka_tmp[2] = clear_diagnostyka[2];

  set_diagnostyka_tmp[0] = set_diagnostyka[0];
  set_diagnostyka_tmp[1] = set_diagnostyka[1];
  set_diagnostyka_tmp[2] = set_diagnostyka[2];
    
  diagnostyka[0] &= (unsigned int)(~clear_diagnostyka_tmp[0]); 
  diagnostyka[0] |= set_diagnostyka_tmp[0]; 

  diagnostyka[1] &= (unsigned int)(~clear_diagnostyka_tmp[1]); 
  diagnostyka[1] |= set_diagnostyka_tmp[1]; 

  diagnostyka[2] &= (unsigned int)(~clear_diagnostyka_tmp[2]); 
  diagnostyka[2] |= set_diagnostyka_tmp[2]; 
  
  diagnostyka[2] &= USED_BITS_IN_LAST_INDEX; 

  clear_diagnostyka[0] &= (unsigned int)(~clear_diagnostyka_tmp[0]);
  clear_diagnostyka[1] &= (unsigned int)(~clear_diagnostyka_tmp[1]);
  clear_diagnostyka[2] &= (unsigned int)(~clear_diagnostyka_tmp[2]);
  
  set_diagnostyka[0] &= (unsigned int)(~set_diagnostyka_tmp[0]);
  set_diagnostyka[1] &= (unsigned int)(~set_diagnostyka_tmp[1]);
  set_diagnostyka[2] &= (unsigned int)(~set_diagnostyka_tmp[2]);
  /*****/
  
  //Визначаємо, чи відбулися зміни
  unsigned int value_changes[3], diagnostyka_now[3];
  /*
  Робимо копію тепершньої діагностики, бо ця функція працює на найнижчому пріоритеті,
  тому під час роботи може появитися нові значення, які ми не врахували у цій функції
  */
  diagnostyka_now[0] = diagnostyka[0];
  diagnostyka_now[1] = diagnostyka[1];
  diagnostyka_now[2] = diagnostyka[2];
  value_changes[0] = diagnostyka_before[0] ^ diagnostyka_now[0];
  value_changes[1] = diagnostyka_before[1] ^ diagnostyka_now[1];
  value_changes[2] = diagnostyka_before[2] ^ diagnostyka_now[2];
  
  /*
  У реєстраторі програмних подій має реєструватися тільки перехід з пасивного стану у активний
  таких подій як " Старт устр.    " і " Рестарт устр.  "
  тому перехід з активного у пачсивний ми ігноруємо і крім того затираємо біти, які його "засигналізували"
  */
  
  /*****/
  //Подія " Старт устр.    "
  /*****/
  if (_CHECK_SET_BIT(value_changes, EVENT_START_SYSTEM_BIT) != 0)
  {
    //Зафіксовано що подія " Старт устр.    " змінила свій стан
    if (_CHECK_SET_BIT(diagnostyka_now, EVENT_START_SYSTEM_BIT) == 0)
    {
      /*
      Новий стан події " Старт устр.    " є неактивний стан
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
  //Подія " Рестарт устр.  "
  /*****/
  if (_CHECK_SET_BIT(value_changes, EVENT_RESTART_SYSTEM_BIT) != 0)
  {
    //Зафіксовано що подія " Рестарт устр.  " змінила свій стан
    if (_CHECK_SET_BIT(diagnostyka_now, EVENT_RESTART_SYSTEM_BIT) == 0)
    {
      /*
      Новий стан події " Рестарт устр.  " є неактивний стан
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

  //Перевіряємо, чи треба виконувати дії поо зміні діагностики
  if (
      (value_changes[0] != 0) ||
      (value_changes[1] != 0) ||
      (value_changes[2] != 0)
     )
  {
    //Є біти, які треба встановити, або зняти
    
    /*****/
    //При можливості формуємо запис у реєстратор програмних помилок
    /*****/
    if (_CHECK_SET_BIT(diagnostyka, ERROR_PR_ERR_OVERLOAD_BIT) == 0)
    {
      /*
      Новий запис робимо тільки тоді, коли попередньо не було зафіксовано 
      переповнення буферу, інакше чикаємо, поки запис у реєстратор програмних подій
      знімить подію про переповнення буферу
      */
      
      //Визначаємо кількість доступних комірок у буфері для реєстратора програмних подій
      int number_empty_cells;
      unsigned int head = head_fifo_buffer_pr_err_records, tail = tail_fifo_buffer_pr_err_records;
      number_empty_cells = (int)(((unsigned int)tail) - ((unsigned int)head));
      while (number_empty_cells <= 0) number_empty_cells += MAX_NUMBER_RECORDS_PR_ERR_INTO_BUFFER;
      if (number_empty_cells == 1)
      {
        //Це є остання вільна комірка, то помічаємо, що з цим записом відбувається повне заповнення буферу
        _SET_BIT(diagnostyka, ERROR_PR_ERR_OVERLOAD_BIT);
        /*
        відбулася зміна стану діагностики, яку треба врахувати у даному записфі ,тому
        робимо повторноу копію тепершньої діагностики, яка може врахувати і ті зміни які відбулися
        між операціями копіювання стану діагностики на початку цієї функції і
        операцією, як зараз ми будемо виконувати
        */
        diagnostyka_now[0] = diagnostyka[0];
        diagnostyka_now[1] = diagnostyka[1];
        diagnostyka_now[2] = diagnostyka[2];
        
        //Підраховуємо нову кількість змін в діагностиці
        value_changes[0] = diagnostyka_before[0] ^ diagnostyka_now[0];
        value_changes[1] = diagnostyka_before[1] ^ diagnostyka_now[1];
        value_changes[2] = diagnostyka_before[2] ^ diagnostyka_now[2];
      }

      //Вираховуємо кількість змін сигналів
      unsigned int number_changes = 0;
      for(unsigned int i = 0; i < (8*sizeof(value_changes)); i++)
      {
        if (_CHECK_SET_BIT(value_changes, i) != 0) number_changes++;
      }

      if(number_changes != 0)
      {
        /*
        теоретично може бути ситуація, що ми знімали повідомлення про переповнення буферу
        FIFO для записів реєстратора програмних подій  і це була єдина зміна, али при цьому
        є тільки одна вільна комірка, тому ми знову виставили повідомлення про переповнення.
        Тому ми не можемо зняти це повідомлення - тому і не можемо робити нового запису, 
        бо фактично і зміни ніякої нема
        */
        
        //Визначаємо індекс у масиві буферу програмних помилок з якого трбе почати заповнювати дані
        unsigned int index_into_buffer_pr_err = head*SIZE_ONE_RECORD_PR_ERR;
      
        //Помічаємо мітку початку запису
        buffer_pr_err_records[index_into_buffer_pr_err + 0] = LABEL_START_RECORD_PR_ERR;

        //Час фіксації зміни у діагностиці
        if(
           (_CHECK_SET_BIT(diagnostyka, EVENT_START_SYSTEM_BIT   ) == 0) &&
           (_CHECK_SET_BIT(diagnostyka, EVENT_RESTART_SYSTEM_BIT ) == 0) &&
           (_CHECK_SET_BIT(diagnostyka, EVENT_STOP_SYSTEM_BIT    ) == 0)
          )
        {
          //Вже відбулося перше зчитуванння часу - тобто системний час у нас є
          unsigned char *label_to_time_array;
          if (copying_time == 0) label_to_time_array = time;
          else label_to_time_array = time_copy;
          for(unsigned int i = 0; i < 7; i++) buffer_pr_err_records[index_into_buffer_pr_err + 1 + i] = *(label_to_time_array + i);
        }
        else
        {
          //Ще не відбулося перше зчитуванння часу - тому покищо ці поля записуємо числом 0xff, а потім, коли системний час зчитається, то ми це поле обновимо
          for(unsigned int i = 0; i < 7; i++)  buffer_pr_err_records[index_into_buffer_pr_err + 1 + i] = 0xff;
        }

        buffer_pr_err_records[index_into_buffer_pr_err + 8] = number_changes & 0xff;
      
        //Записуємо попередній стан діагностики
        buffer_pr_err_records[index_into_buffer_pr_err + 9 ] =  diagnostyka_before[0]        & 0xff;
        buffer_pr_err_records[index_into_buffer_pr_err + 10] = (diagnostyka_before[0] >> 8 ) & 0xff;
        buffer_pr_err_records[index_into_buffer_pr_err + 11] = (diagnostyka_before[0] >> 16) & 0xff;
        buffer_pr_err_records[index_into_buffer_pr_err + 12] = (diagnostyka_before[0] >> 24) & 0xff;
        buffer_pr_err_records[index_into_buffer_pr_err + 13] =  diagnostyka_before[1]        & 0xff;
        buffer_pr_err_records[index_into_buffer_pr_err + 14] = (diagnostyka_before[1] >> 8 ) & 0xff;
        buffer_pr_err_records[index_into_buffer_pr_err + 15] = (diagnostyka_before[1] >> 16) & 0xff;
        buffer_pr_err_records[index_into_buffer_pr_err + 16] = (diagnostyka_before[1] >> 24) & 0xff;
        buffer_pr_err_records[index_into_buffer_pr_err + 17] =  diagnostyka_before[2]        & 0xff;
        buffer_pr_err_records[index_into_buffer_pr_err + 18] = (diagnostyka_before[2] >> 8 ) & 0xff;
        buffer_pr_err_records[index_into_buffer_pr_err + 19] = (diagnostyka_before[2] >> 16) & 0xff;

        //Записуємо теперішній стан діагностики
        buffer_pr_err_records[index_into_buffer_pr_err + 20] =  diagnostyka_now[0]        & 0xff;
        buffer_pr_err_records[index_into_buffer_pr_err + 21] = (diagnostyka_now[0] >> 8 ) & 0xff;
        buffer_pr_err_records[index_into_buffer_pr_err + 22] = (diagnostyka_now[0] >> 16) & 0xff;
        buffer_pr_err_records[index_into_buffer_pr_err + 23] = (diagnostyka_now[0] >> 24) & 0xff;
        buffer_pr_err_records[index_into_buffer_pr_err + 24] =  diagnostyka_now[1]        & 0xff;
        buffer_pr_err_records[index_into_buffer_pr_err + 25] = (diagnostyka_now[1] >> 8 ) & 0xff;
        buffer_pr_err_records[index_into_buffer_pr_err + 26] = (diagnostyka_now[1] >> 16) & 0xff;
        buffer_pr_err_records[index_into_buffer_pr_err + 27] = (diagnostyka_now[1] >> 24) & 0xff;
        buffer_pr_err_records[index_into_buffer_pr_err + 28] =  diagnostyka_now[2]        & 0xff;
        buffer_pr_err_records[index_into_buffer_pr_err + 29] = (diagnostyka_now[2] >> 8 ) & 0xff;
        buffer_pr_err_records[index_into_buffer_pr_err + 30] = (diagnostyka_now[2] >> 16) & 0xff;
        
        /*
        У реєстраторі програмних подій має реєструватися тільки перехід з пасивного стану у активний
        таких події як " Останов.устр.  " і ця подія не має бути активною у текучій діагностиці,
        бо це, фактично, подія, яка мала місце до останнього включення приладу в роботу.
        Тобто це подія "попереднього сеансу роботи"
        тому перехід з пасивного у фіксуємо ми фіксуємо і зразу затираємо цей біт у теперішній діагностіці,
        яка після цього буде зкомійомана у масив. який відповідає за попередній стан діагностики, так і у масив
        діагностики, який відповідає за текучий стан подій діагностики
        */
        if (_CHECK_SET_BIT(value_changes, EVENT_STOP_SYSTEM_BIT) != 0)
        {
          /*
          Cтан події " Останов.устр.  " змінився (допускається нашим програмним забезпеченням
          зміна з пасивного стану у активний стан)
          Тому робимо такі операції
          - знімаємо встановлений біт у масиві, який зараз буде копіюватися у масив попереднього стану
          - знімаємо встановлений біт у масиві, який відповідає за текучий стан подій діагностики
          */
          _CLEAR_BIT(diagnostyka_now, EVENT_STOP_SYSTEM_BIT);
          _CLEAR_BIT(diagnostyka, EVENT_STOP_SYSTEM_BIT);
        }

        //Фіксуємо попередній стан, який ми вже записали і відносно якого будемо визначати нові зміни
        diagnostyka_before[0] = diagnostyka_now[0];
        diagnostyka_before[1] = diagnostyka_now[1];
        diagnostyka_before[2] = diagnostyka_now[2];

        //Підготовлюємося до запуску запису у реєстратор програмних подій
          unsigned int next_index_into_fifo_buffer = head + 1;
          while(next_index_into_fifo_buffer >= MAX_NUMBER_RECORDS_PR_ERR_INTO_BUFFER) next_index_into_fifo_buffer -= MAX_NUMBER_RECORDS_PR_ERR_INTO_BUFFER;
          
          //Встановлюємо нове значення голови буфера FIFO 
          head_fifo_buffer_pr_err_records = next_index_into_fifo_buffer;
      }
    }
    /*****/
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
  uint8_t  *point_1 = (unsigned char*)(&current_config);
  uint8_t  *point_2 = (unsigned char*)(&current_config_prt); // з цими даними працюють захисти
  unsigned int i = 0, difference = 0;
  while ((difference == 0) && (i < sizeof(__CONFIG)))
  {
    //Контроль контрольної суми кофігурації для захистів
    temp_value = *(point_1++);
    crc_config_tmp += temp_value;

    //Контроль конфігурації для захистів з конфігурацією-контейнером
    if (modified != true)
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

  unsigned int block = 0, shift = 0;
  size_t size_of_block = 0;
  while(
        (difference == 0) &&
        (block < (1 + CA_MAX))
       )
  {
    if (size_of_block == 0)
    {
      //Визначаємо розмір нового блоку
      switch (block)
      {
      case 0:
        {
          size_of_block = sizeof(__SETTINGS_FIX);
          break;
        }
      case (1 + CA_INPUT):
        {
          size_of_block = current_config_prt.n_input*sizeof(__settings_for_INPUT);
          break;
        }
      case (1 + CA_OUTPUT):
        {
          size_of_block = current_config_prt.n_output*sizeof(__settings_for_OUTPUT);
          break;
        }
      case (1 + CA_LED):
        {
          size_of_block = current_config_prt.n_led*sizeof(__settings_for_LED);
          break;
        }
      case (1 + CA_STANDART_LOGIC_AND):
        {
          size_of_block = current_config_prt.n_and*sizeof(__settings_for_AND);
          break;
        }
      case (1 + CA_STANDART_LOGIC_OR):
        {
          size_of_block = current_config_prt.n_or*sizeof(__settings_for_OR);
          break;
        }
      case (1 + CA_STANDART_LOGIC_XOR):
        {
          size_of_block = current_config_prt.n_xor*sizeof(__settings_for_XOR);
          break;
        }
      case (1 + CA_STANDART_LOGIC_NOT):
        {
          size_of_block = current_config_prt.n_not*sizeof(__settings_for_NOT);
          break;
        }
      case (1 + CA_STANDART_LOGIC_TIMER):
        {
          size_of_block = current_config_prt.n_timer*sizeof(__settings_for_TIMER);
          break;
        }
      case (1 + CA_STANDART_LOGIC_TRIGGER):
        {
          size_of_block = current_config_prt.n_trigger*sizeof(__settings_for_TRIGGER);
          break;
        }
      case (1 + CA_MEANDER):
        {
          size_of_block = current_config_prt.n_meander*sizeof(__settings_for_MEANDER);
          break;
        }
      default:
        {
          //Якщо сюди дійшла програма, значить відбулася недопустива помилка, тому треба зациклити програму, щоб вона пішла на перезагрузку
          total_error_sw_fixed(5);
        }
      }

      //Визначаємо вказівник на початок блоку
      if (size_of_block != 0)
      {
        if (block == 0)
        {
          point_1 = (uint8_t *)(&settings_fix_prt);
          if (modified != true) point_2 = (uint8_t *)(&settings_fix);
        }
        else
        {
          point_1 = (uint8_t *)(spca_of_p_prt[block - 1]);
          if (modified != true) point_2 = (uint8_t *)(sca_of_p[block - 1]);
        }
      }
    }
      
    if (size_of_block != 0)
    {
      //Контроль контрольної суми налаштувань для захистів
      temp_value = *(point_1 + shift);
      crc_settings_tmp += temp_value;

      //Контроль налаштувань для захистів з налаштуваннями-контейнером
      if (modified != true)
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
        block++;
        size_of_block = 0;
      }
    }
    else 
    {
      shift = 0;
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
  unsigned char crc_trg_func_tmp = 0, temp_value_1;
  unsigned char  *point; 
  unsigned int i;
  
  point = (unsigned char*)(trigger_active_functions_ctrl);
  i = 0;  
  while (i < sizeof(trigger_active_functions_ctrl))
  {
    temp_value_1 = *(point);
    crc_trg_func_tmp += temp_value_1;
    point++;
    i++;
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
unsigned int control_info_rejestrator(__INFO_REJESTRATOR* info_rejestrator_point, unsigned char crc_info_rejestrator)
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
  static const char month_names[12*3] = "JanFebMarAprMayJunJulAugSepOctNovDec";
  
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
__result_dym_mem_select allocate_dynamic_memory_for_settings(unsigned int make_remake, unsigned int mem_for_prt, uintptr_t *p_sca_of_p_current[], uintptr_t *p_sca_of_p_control[], __CONFIG *current, __CONFIG *control)
{
  __result_dym_mem_select result = DYN_MEM_SELECT_OK;
  
  intptr_t index_1 = 0;
  while(
        (result == DYN_MEM_SELECT_OK) &&
        (index_1 < CA_MAX)
       )   
  {
    uint32_t n_prev, n_cur;
    size_t size;
    void (*min_param)(unsigned int, uintptr_t *, size_t, size_t);
    switch (index_1)
    {
    case CA_INPUT:
      {
        //Дискретний вхід
        n_prev = (control != NULL) ? control->n_input : 0;
        n_cur  = current->n_input;
        min_param = min_settings_INPUT;
        size = n_cur*((mem_for_prt == true) ? sizeof(__LN_INPUT) : sizeof(__settings_for_INPUT));
        break;
      }
    case CA_OUTPUT:
      {
        //Дискретний вихід
        n_prev = (control != NULL) ? control->n_output : 0;
        n_cur  = current->n_output;
        min_param = min_settings_OUTPUT;
        size = n_cur*((mem_for_prt == true) ? sizeof(__LN_OUTPUT) : sizeof(__settings_for_OUTPUT));
        break;
      }
    case CA_LED:
      {
        //Світлоіндикатор
        n_prev = (control != NULL) ? control->n_led : 0;
        n_cur  = current->n_led;
        min_param = min_settings_LED;
        size = n_cur*((mem_for_prt == true) ? sizeof(__LN_LED) : sizeof(__settings_for_LED));
        break;
      }
    case CA_STANDART_LOGIC_AND:
      {
        //Елемент "І"
        n_prev = (control != NULL) ? control->n_and : 0;
        n_cur  = current->n_and;
        min_param = min_settings_AND;
        size = n_cur*((mem_for_prt == true) ? sizeof(__LN_AND) : sizeof(__settings_for_AND));
        break;
      }
    case CA_STANDART_LOGIC_OR:
      {
        //Елемент "АБО"
        n_prev = (control != NULL) ? control->n_or : 0;
        n_cur  = current->n_or;
        min_param = min_settings_OR;
        size = n_cur*((mem_for_prt == true) ? sizeof(__LN_OR) : sizeof(__settings_for_OR));
        break;
      }
    case CA_STANDART_LOGIC_XOR:
      {
        //Елемент "Викл.АБО"
        n_prev = (control != NULL) ? control->n_xor : 0;
        n_cur  = current->n_xor;
        min_param = min_settings_XOR;
        size = n_cur*((mem_for_prt == true) ? sizeof(__LN_XOR) : sizeof(__settings_for_XOR));
        break;
      }
    case CA_STANDART_LOGIC_NOT:
      {
        //Елемент "НЕ"
        n_prev = (control != NULL) ? control->n_not : 0;
        n_cur  = current->n_not;
        min_param = min_settings_NOT;
        size = n_cur*((mem_for_prt == true) ? sizeof(__LN_NOT) : sizeof(__settings_for_NOT));
        break;
      }
    case CA_STANDART_LOGIC_TIMER:
      {
        //Елемент "Таймер"
        n_prev = (control != NULL) ? control->n_timer : 0;
        n_cur  = current->n_timer;
        min_param = min_settings_TIMER;
        size = n_cur*((mem_for_prt == true) ? sizeof(__LN_TIMER) : sizeof(__settings_for_TIMER));
        break;
      }
    case CA_STANDART_LOGIC_TRIGGER:
      {
        //Елемент "Триґер"
        n_prev = (control != NULL) ? control->n_trigger : 0;
        n_cur  = current->n_trigger;
        min_param = min_settings_TRIGGER;
        size = n_cur*((mem_for_prt == true) ? sizeof(__LN_TRIGGER) : sizeof(__settings_for_TRIGGER));
        break;
      }
    case CA_MEANDER:
      {
        //Функціональний блок "Генератор періодичних сигналів"
        n_prev = (control != NULL) ? control->n_meander : 0;
        n_cur  = current->n_meander;
        min_param = min_settings_MEANDER;
        size = n_cur*((mem_for_prt == true) ? sizeof(__LN_MEANDER) : sizeof(__settings_for_MEANDER));
        break;
      }
    default:
      {
        //Якщо сюди дійшла програма, значить відбулася недопустива помилка, тому треба зациклити програму, щоб вона пішла на перезагрузку
        total_error_sw_fixed(22);
      }
    }
    
    if ((make_remake == false) || (n_cur != n_prev))
    {
      //Іде або виділення пергий раз області пам'яті, або кількість функціональних блоків зміникася
      if(size == 0) 
      {
        free(p_sca_of_p_current[index_1]);
        p_sca_of_p_current[index_1] = NULL;
      }
      else
      {
        uintptr_t *ptr= (uintptr_t*)realloc(p_sca_of_p_current[index_1], size);
        if (ptr != NULL)
        {
          p_sca_of_p_current[index_1] = ptr;
          if ((make_remake == false) || (n_cur > n_prev))
          {
            //Викликаємо функцію встановлення нових налаштувань у мінімальні значення
            (*min_param)(mem_for_prt, ptr, ((make_remake == false) ? 0 : n_prev), n_cur);
          }
        }
        else 
        {
          if ((make_remake == false) || (mem_for_prt != false) || (control == NULL)) result = DYN_MEM_TOTAL_ERROR;
          else result = DYN_MEM_NO_ENOUGH_MEM;
        }
      }
    }

    //Готуємося до зміни наступного функціонального блоку (у випадку успішної зміни або неуспішної, але з можливістю відновлення)
    if (result == DYN_MEM_SELECT_OK) index_1++;
    else if (result == DYN_MEM_NO_ENOUGH_MEM) index_1--;
  }
  
  /*
  Цей while потрібен тільки у тому випадку, якщо пам'яті для новогого розміщення є недостатньо
  і є спроба повернутися до попередньої конфігурації
  */
  
  while(
        (result == DYN_MEM_NO_ENOUGH_MEM) && 
        (index_1 >= 0)
       )   
  {
    uint32_t n_prev, n_cur;
    size_t size;
    void (*copy_settings_LN)(unsigned int, unsigned int, uintptr_t *, uintptr_t *, size_t, size_t);
    switch (index_1)
    {
    case CA_INPUT:
      {
        //Дискретний вхід
        n_prev = (control != NULL) ? control->n_input : 0;
        n_cur  = current->n_input;
        copy_settings_LN = copy_settings_INPUT;
        size = n_prev*((mem_for_prt == true) ? sizeof(__LN_INPUT) : sizeof(__settings_for_INPUT));
        break;
      }
    case CA_OUTPUT:
      {
        //Дискретний вихід
        n_prev = (control != NULL) ? control->n_output : 0;
        n_cur  = current->n_output;
        copy_settings_LN = copy_settings_OUTPUT;
        size = n_prev*((mem_for_prt == true) ? sizeof(__LN_OUTPUT) : sizeof(__settings_for_OUTPUT));
        break;
      }
    case CA_LED:
      {
        //Світлоіндимкатор
        n_prev = (control != NULL) ? control->n_led : 0;
        n_cur  = current->n_led;
        copy_settings_LN = copy_settings_LED;
        size = n_prev*((mem_for_prt == true) ? sizeof(__LN_LED) : sizeof(__settings_for_LED));
        break;
      }
    case CA_STANDART_LOGIC_AND:
      {
        //Елемент "І"
        n_prev = (control != NULL) ? control->n_and : 0;
        n_cur  = current->n_and;
        copy_settings_LN = copy_settings_AND;
        size = n_prev*((mem_for_prt == true) ? sizeof(__LN_AND) : sizeof(__settings_for_AND));
        break;
      }
    case CA_STANDART_LOGIC_OR:
      {
        //Елемент "АБО"
        n_prev = (control != NULL) ? control->n_or : 0;
        n_cur  = current->n_or;
        copy_settings_LN = copy_settings_OR;
        size = n_prev*((mem_for_prt == true) ? sizeof(__LN_OR) : sizeof(__settings_for_OR));
        break;
      }
    case CA_STANDART_LOGIC_XOR:
      {
        //Елемент "Викл.АБО"
        n_prev = (control != NULL) ? control->n_xor : 0;
        n_cur  = current->n_xor;
        copy_settings_LN = copy_settings_XOR;
        size = n_prev*((mem_for_prt == true) ? sizeof(__LN_XOR) : sizeof(__settings_for_XOR));
        break;
      }
    case CA_STANDART_LOGIC_NOT:
      {
        //Елемент "НЕ"
        n_prev = (control != NULL) ? control->n_not : 0;
        n_cur  = current->n_not;
        copy_settings_LN = copy_settings_NOT;
        size = n_prev*((mem_for_prt == true) ? sizeof(__LN_NOT) : sizeof(__settings_for_NOT));
        break;
      }
    case CA_STANDART_LOGIC_TIMER:
      {
        //Елемент "Таймер"
        n_prev = (control != NULL) ? control->n_timer : 0;
        n_cur  = current->n_timer;
        copy_settings_LN = copy_settings_TIMER;
        size = n_prev*((mem_for_prt == true) ? sizeof(__LN_TIMER) : sizeof(__settings_for_TIMER));
        break;
      }
    case CA_STANDART_LOGIC_TRIGGER:
      {
        //Елемент "Триґер"
        n_prev = (control != NULL) ? control->n_trigger : 0;
        n_cur  = current->n_trigger;
        copy_settings_LN = copy_settings_TRIGGER;
        size = n_prev*((mem_for_prt == true) ? sizeof(__LN_TRIGGER) : sizeof(__settings_for_TRIGGER));
        break;
      }
    case CA_MEANDER:
      {
        //Функціональний блок "Генератор періодичних сигналів"
        n_prev = (control != NULL) ? control->n_meander : 0;
        n_cur  = current->n_meander;
        copy_settings_LN = copy_settings_MEANDER;
        size = n_prev*((mem_for_prt == true) ? sizeof(__LN_MEANDER) : sizeof(__settings_for_MEANDER));
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
        free(p_sca_of_p_current[index_1]);
        p_sca_of_p_current[index_1] = NULL;
      }
      else
      {
        uintptr_t *ptr= (uintptr_t*)realloc(p_sca_of_p_current[index_1], size);
        if (ptr != NULL)
        {
          p_sca_of_p_current[index_1] = ptr;
          if (n_prev > n_cur)
          {
            if ( p_sca_of_p_control[index_1] != NULL)
            {
              //Викликаємо функцію повернення нових налаштувань у попередні значення
              (*copy_settings_LN)(mem_for_prt, (p_sca_of_p_control == spca_of_p_prt), ptr, p_sca_of_p_control[index_1], n_cur, n_prev);
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
      ((__LN_INPUT *)(base) + shift)->settings.control = 0;
      ((__LN_INPUT *)(base) + shift)->settings.delay.delay = KOEF_DOPUSK_DV_POST_MIN;
      
      ((__LN_INPUT *)(base) + shift)->delay.delay = -1;
      for (size_t l = 0; l < BLOCK8_SIZE(INPUT_SIGNALS); l++) 
      {
        ((__LN_INPUT *)(base) + shift)->active_state[l] = 0;
      }
    }
    else
    {
      ((__settings_for_INPUT *)(base) + shift)->control = 0;
      ((__settings_for_INPUT *)(base) + shift)->delay.delay = KOEF_DOPUSK_DV_POST_MIN;
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
      ((__settings_for_INPUT *)(base_target) + shift)->delay.delay = ((__LN_INPUT *)(base_source) + shift)->settings.delay.delay;
    }
    else if ((mem_to_prt == true) && (mem_from_prt == false))
    {
      ((__LN_INPUT *)(base_target) + shift)->settings.control = ((__settings_for_INPUT *)(base_source) + shift)->control;
      ((__LN_INPUT *)(base_target) + shift)->settings.delay.delay = ((__settings_for_INPUT *)(base_source) + shift)->delay.delay;
    }
    else if ((mem_to_prt == false) && (mem_from_prt == false))
    {
      ((__settings_for_INPUT *)(base_target) + shift)->control = ((__settings_for_INPUT *)(base_source) + shift)->control;
      ((__settings_for_INPUT *)(base_target) + shift)->delay.delay = ((__settings_for_INPUT *)(base_source) + shift)->delay.delay;
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
//Встановлення мінімальних параметрів для дискретного виходу
/*****************************************************/
void min_settings_OUTPUT(unsigned int mem_to_prt, uintptr_t *base, size_t index_first, size_t index_last)
{
  for (size_t shift = index_first; shift < index_last; shift++)
  {
    if (mem_to_prt == true)
    {
      ((__LN_OUTPUT *)(base) + shift)->settings.control = 0;
      ((__LN_OUTPUT *)(base) + shift)->settings.param = 0;
      
      for (size_t l = 0; l < BLOCK8_SIZE(OUTPUT_SIGNALS); l++) 
      {
        ((__LN_OUTPUT *)(base) + shift)->active_state[l] = 0;
      }
    }
    else
    {
      ((__settings_for_OUTPUT *)(base) + shift)->control = 0;
      ((__settings_for_OUTPUT *)(base) + shift)->param = 0;
    }
  }
}
/*****************************************************/

/*****************************************************/
//Відновлення попередніх параметрів для дискретного виходу
/*****************************************************/
void copy_settings_OUTPUT(unsigned int mem_to_prt, unsigned int mem_from_prt, uintptr_t *base_target, uintptr_t *base_source, size_t index_target, size_t index_source)
{
  for (size_t shift = index_target; shift < index_source; shift++)
  {
    if ((mem_to_prt == false) && (mem_from_prt == true))
    {
      ((__settings_for_OUTPUT *)(base_target) + shift)->control = ((__LN_OUTPUT *)(base_source) + shift)->settings.control;
      ((__settings_for_OUTPUT *)(base_target) + shift)->param = ((__LN_OUTPUT *)(base_source) + shift)->settings.param;
    }
    else if ((mem_to_prt == true) && (mem_from_prt == false))
    {
      ((__LN_OUTPUT *)(base_target) + shift)->settings.control = ((__settings_for_OUTPUT *)(base_source) + shift)->control;
      ((__LN_OUTPUT *)(base_target) + shift)->settings.param = ((__settings_for_OUTPUT *)(base_source) + shift)->param;
    }
    else if ((mem_to_prt == false) && (mem_from_prt == false))
    {
      ((__settings_for_OUTPUT *)(base_target) + shift)->control = ((__settings_for_OUTPUT *)(base_source) + shift)->control;
      ((__settings_for_OUTPUT *)(base_target) + shift)->param = ((__settings_for_OUTPUT *)(base_source) + shift)->param;
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
//Встановлення мінімальних параметрів для світлоіндикатора
/*****************************************************/
void min_settings_LED(unsigned int mem_to_prt, uintptr_t *base, size_t index_first, size_t index_last)
{
  for (size_t shift = index_first; shift < index_last; shift++)
  {
    if (mem_to_prt == true)
    {
      ((__LN_OUTPUT *)(base) + shift)->settings.control = 0;
      ((__LN_OUTPUT *)(base) + shift)->settings.param = 0;
      
      for (size_t l = 0; l < BLOCK8_SIZE(LED_SIGNALS); l++) 
      {
        ((__LN_LED *)(base) + shift)->active_state[l] = 0;
      }
    }
    else
    {
      ((__settings_for_LED *)(base) + shift)->control = 0;
      ((__settings_for_LED *)(base) + shift)->param = 0;
    }
  }
}
/*****************************************************/

/*****************************************************/
//Відновлення попередніх параметрів для світлоіндикатора
/*****************************************************/
void copy_settings_LED(unsigned int mem_to_prt, unsigned int mem_from_prt, uintptr_t *base_target, uintptr_t *base_source, size_t index_target, size_t index_source)
{
  for (size_t shift = index_target; shift < index_source; shift++)
  {
    if ((mem_to_prt == false) && (mem_from_prt == true))
    {
      ((__settings_for_LED *)(base_target) + shift)->control = ((__LN_LED *)(base_source) + shift)->settings.control;
      ((__settings_for_LED *)(base_target) + shift)->param = ((__LN_LED *)(base_source) + shift)->settings.param;
    }
    else if ((mem_to_prt == true) && (mem_from_prt == false))
    {
      ((__LN_LED *)(base_target) + shift)->settings.control = ((__settings_for_LED *)(base_source) + shift)->control;
      ((__LN_LED *)(base_target) + shift)->settings.param = ((__settings_for_LED *)(base_source) + shift)->param;
    }
    else if ((mem_to_prt == false) && (mem_from_prt == false))
    {
      ((__settings_for_LED *)(base_target) + shift)->control = ((__settings_for_LED *)(base_source) + shift)->control;
      ((__settings_for_LED *)(base_target) + shift)->param = ((__settings_for_LED *)(base_source) + shift)->param;
    }
    else
    {
      //Якщо сюди дійшла програма, значить відбулася недопустива помилка, тому треба зациклити програму, щоб вона пішла на перезагрузку
      total_error_sw_fixed(92);
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
    for (size_t i = 0; i < NUMBER_IN_AND; i++)
    {
      if (mem_to_prt == true)
      {
        ((__LN_AND *)(base) + shift)->settings.param[i] = 0;
      
        for (size_t l = 0; l < BLOCK8_SIZE(AND_SIGNALS); l++) 
        {
          ((__LN_AND *)(base) + shift)->active_state[i] = 0;
          ((__LN_AND *)(base) + shift)->trigger_state[i] = 0;
        }
      }
      else
      {
        ((__settings_for_AND *)(base) + shift)->param[i] = 0;
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
    for (size_t i = 0; i < NUMBER_IN_AND; i++)
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
    for (size_t i = 0; i < NUMBER_IN_OR; i++)
    {
      if (mem_to_prt == true)
      {
        ((__LN_OR *)(base) + shift)->settings.param[i] = 0;
      
        for (size_t l = 0; l < BLOCK8_SIZE(OR_SIGNALS); l++) 
        {
          ((__LN_OR *)(base) + shift)->active_state[i] = 0;
          ((__LN_OR *)(base) + shift)->trigger_state[i] = 0;
        }
      }
      else
      {
        ((__settings_for_OR *)(base) + shift)->param[i] = 0;
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
    for (size_t i = 0; i < NUMBER_IN_OR; i++)
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
      if (mem_to_prt == true)
      {
        ((__LN_XOR *)(base) + shift)->settings.param[i] = 0;
      
        for (size_t l = 0; l < BLOCK8_SIZE(XOR_SIGNALS); l++) 
        {
          ((__LN_XOR *)(base) + shift)->active_state[i] = 0;
          ((__LN_XOR *)(base) + shift)->trigger_state[i] = 0;
        }
      }
      else
      {
        ((__settings_for_XOR *)(base) + shift)->param[i] = 0;
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
    if (mem_to_prt == true)
    {
      ((__LN_NOT *)(base) + shift)->settings.param = 0;
      
      for (size_t l = 0; l < BLOCK8_SIZE(NOT_SIGNALS); l++) 
      {
        ((__LN_NOT *)(base) + shift)->active_state[l] = 0;
        ((__LN_NOT *)(base) + shift)->trigger_state[l] = 0;
      }
    }
    else
    {
      ((__settings_for_NOT *)(base) + shift)->param = 0;
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
    if ((mem_to_prt == false) && (mem_from_prt == true))
    {
      ((__settings_for_NOT *)(base_target) + shift)->param = ((__LN_NOT *)(base_source) + shift)->settings.param;
    }
    else if ((mem_to_prt == true) && (mem_from_prt == false))
    {
      ((__LN_NOT *)(base_target) + shift)->settings.param = ((__settings_for_NOT *)(base_source) + shift)->param;
    }
    else if ((mem_to_prt == false) && (mem_from_prt == false))
    {
      ((__settings_for_NOT *)(base_target) + shift)->param = ((__settings_for_NOT *)(base_source) + shift)->param;
    }
    else
    {
      //Якщо сюди дійшла програма, значить відбулася недопустива помилка, тому треба зациклити програму, щоб вона пішла на перезагрузку
      total_error_sw_fixed(96);
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
      ((__LN_TIMER *)(base) + shift)->settings.param = 0;
      ((__LN_TIMER *)(base) + shift)->settings.control = 0;
      ((__LN_TIMER *)(base) + shift)->settings.delay.delay_pause = TIMEOUT_DF_PAUSE_MIN;
      ((__LN_TIMER *)(base) + shift)->settings.delay.delay_work  = TIMEOUT_DF_WORK_MIN;

      ((__LN_TIMER *)(base) + shift)->delay.delay_pause = -1;
      ((__LN_TIMER *)(base) + shift)->delay.delay_work = -1;
      for (size_t l = 0; l < BLOCK8_SIZE(TIMER_SIGNALS); l++) 
      {
        ((__LN_TIMER *)(base) + shift)->active_state[l] = 0;
        ((__LN_TIMER *)(base) + shift)->trigger_state[l] = 0;
      }
    }
    else
    {
      ((__settings_for_TIMER *)(base) + shift)->param = 0;
      ((__settings_for_TIMER *)(base) + shift)->control = 0;
      ((__settings_for_TIMER *)(base) + shift)->delay.delay_pause = TIMEOUT_DF_PAUSE_MIN;
      ((__settings_for_TIMER *)(base) + shift)->delay.delay_work  = TIMEOUT_DF_WORK_MIN;
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
      ((__settings_for_TIMER *)(base_target) + shift)->param             = ((__LN_TIMER *)(base_source) + shift)->settings.param;
      ((__settings_for_TIMER *)(base_target) + shift)->control           = ((__LN_TIMER *)(base_source) + shift)->settings.control;
      ((__settings_for_TIMER *)(base_target) + shift)->delay.delay_pause = ((__LN_TIMER *)(base_source) + shift)->settings.delay.delay_pause;
      ((__settings_for_TIMER *)(base_target) + shift)->delay.delay_work  = ((__LN_TIMER *)(base_source) + shift)->settings.delay.delay_work;
    }
    else if ((mem_to_prt == true) && (mem_from_prt == false))
    {
      ((__LN_TIMER *)(base_target) + shift)->settings.param             = ((__settings_for_TIMER *)(base_source) + shift)->param;
      ((__LN_TIMER *)(base_target) + shift)->settings.control           = ((__settings_for_TIMER *)(base_source) + shift)->control;
      ((__LN_TIMER *)(base_target) + shift)->settings.delay.delay_pause = ((__settings_for_TIMER *)(base_source) + shift)->delay.delay_pause;
      ((__LN_TIMER *)(base_target) + shift)->settings.delay.delay_work  = ((__settings_for_TIMER *)(base_source) + shift)->delay.delay_work;
    }
    else if ((mem_to_prt == false) && (mem_from_prt == false))
    {
      ((__settings_for_TIMER *)(base_target) + shift)->param             = ((__settings_for_TIMER *)(base_source) + shift)->param;
      ((__settings_for_TIMER *)(base_target) + shift)->control           = ((__settings_for_TIMER *)(base_source) + shift)->control;
      ((__settings_for_TIMER *)(base_target) + shift)->delay.delay_pause = ((__settings_for_TIMER *)(base_source) + shift)->delay.delay_pause;
      ((__settings_for_TIMER *)(base_target) + shift)->delay.delay_work  = ((__settings_for_TIMER *)(base_source) + shift)->delay.delay_work;
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
    if (mem_to_prt == true)
    {
      ((__LN_TRIGGER *)(base) + shift)->settings.set_param   = 0;
      ((__LN_TRIGGER *)(base) + shift)->settings.reset_param = 0;

      for (size_t l = 0; l < BLOCK8_SIZE(TRIGGER_SIGNALS); l++) 
      {
        ((__LN_TRIGGER *)(base) + shift)->active_state[l] = 0;
        ((__LN_TRIGGER *)(base) + shift)->trigger_state[l] = 0;
      }
    }
    else
    {
      ((__settings_for_TRIGGER *)(base) + shift)->set_param   = 0;
      ((__settings_for_TRIGGER *)(base) + shift)->reset_param = 0;
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
    if ((mem_to_prt == false) && (mem_from_prt == true))
    {
      ((__settings_for_TRIGGER *)(base_target) + shift)->set_param   = ((__LN_TRIGGER *)(base_source) + shift)->settings.set_param;
      ((__settings_for_TRIGGER *)(base_target) + shift)->reset_param = ((__LN_TRIGGER *)(base_source) + shift)->settings.reset_param;
    }
    else if ((mem_to_prt == true) && (mem_from_prt == false))
    {
      ((__LN_TRIGGER *)(base_target) + shift)->settings.set_param   = ((__settings_for_TRIGGER *)(base_source) + shift)->set_param;
      ((__LN_TRIGGER *)(base_target) + shift)->settings.reset_param = ((__settings_for_TRIGGER *)(base_source) + shift)->reset_param;
    }
    else if ((mem_to_prt == false) && (mem_from_prt == false))
    {
      ((__settings_for_TRIGGER *)(base_target) + shift)->set_param   = ((__settings_for_TRIGGER *)(base_source) + shift)->set_param;
      ((__settings_for_TRIGGER *)(base_target) + shift)->reset_param = ((__settings_for_TRIGGER *)(base_source) + shift)->reset_param;
    }
    else
    {
      //Якщо сюди дійшла програма, значить відбулася недопустива помилка, тому треба зациклити програму, щоб вона пішла на перезагрузку
      total_error_sw_fixed(98);
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
      ((__LN_MEANDER *)(base) + shift)->settings.delay.delay = TIMEOUT_MEANDER_MIN;

      ((__LN_MEANDER *)(base) + shift)->delay.delay = -1;
      for (size_t l = 0; l < BLOCK8_SIZE(MEANDER_SIGNALS); l++) 
      {
        ((__LN_MEANDER *)(base) + shift)->active_state[l] = 0;
        ((__LN_MEANDER *)(base) + shift)->trigger_state[l] = 0;
      }
    }
    else
    {
      ((__settings_for_MEANDER *)(base) + shift)->delay.delay = TIMEOUT_MEANDER_MIN;
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
      ((__settings_for_MEANDER *)(base_target) + shift)->delay.delay = ((__LN_MEANDER *)(base_source) + shift)->settings.delay.delay;
    }
    else if ((mem_to_prt == true) && (mem_from_prt == false))
    {
      ((__LN_MEANDER *)(base_target) + shift)->settings.delay.delay = ((__settings_for_MEANDER *)(base_source) + shift)->delay.delay;
    }
    else if ((mem_to_prt == false) && (mem_from_prt == false))
    {
      ((__settings_for_MEANDER *)(base_target) + shift)->delay.delay = ((__settings_for_MEANDER *)(base_source) + shift)->delay.delay;
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
//Розмір у байтах всіх налаштувань (фіксованих і змінних)
/*****************************************************/
size_t size_all_settings(void)
{
  size_t size = sizeof(__SETTINGS_FIX);
  for (size_t i = 0; i < CA_MAX; i++)
  {
    size_t size_block;
    switch (i)
    {
    case CA_INPUT:
      {
        size_block = current_config.n_input*sizeof(__settings_for_INPUT);
        break;
      }
    case CA_OUTPUT:
      {
        size_block = current_config.n_output*sizeof(__settings_for_OUTPUT);
        break;
      }
    case CA_LED:
      {
        size_block = current_config.n_led*sizeof(__settings_for_LED);
        break;
      }
    case CA_STANDART_LOGIC_AND:
      {
        size_block = current_config.n_and*sizeof(__settings_for_AND);
        break;
      }
    case CA_STANDART_LOGIC_OR:
      {
        size_block = current_config.n_or*sizeof(__settings_for_OR);
        break;
      }
    case CA_STANDART_LOGIC_XOR:
      {
        size_block = current_config.n_xor*sizeof(__settings_for_XOR);
        break;
      }
    case CA_STANDART_LOGIC_NOT:
      {
        size_block = current_config.n_not*sizeof(__settings_for_NOT);
        break;
      }
    case CA_STANDART_LOGIC_TIMER:
      {
        size_block = current_config.n_timer*sizeof(__settings_for_TIMER);
        break;
      }
    case CA_STANDART_LOGIC_TRIGGER:
      {
        size_block = current_config.n_trigger*sizeof(__settings_for_TRIGGER);
        break;
      }
    case CA_MEANDER:
      {
        size_block = current_config.n_meander*sizeof(__settings_for_MEANDER);
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

                     __SETTINGS_FIX *targret_fix, 
                     __SETTINGS_FIX *source_fix, 
                     uintptr_t *targret_dyn[], 
                     uintptr_t *source_dyn[]
                    )
{
  *targret_fix = *source_fix;
  
  for (size_t i = 0; i < CA_MAX; i++)
  {
    if (source_dyn[i] == NULL)  targret_dyn[i] = NULL;
    else
    {
      uint32_t n_prev;
      void (*copy_settings_LN)(unsigned int, unsigned int, uintptr_t *, uintptr_t *, size_t, size_t);
      switch (i)
      {
        case CA_INPUT:
          {
            //Дискретний вхід
            n_prev = source_conf->n_input;
            copy_settings_LN = copy_settings_INPUT;

            break;
          }
        case CA_OUTPUT:
          {
            //Дискретний вихід
            n_prev = source_conf->n_output;
            copy_settings_LN = copy_settings_OUTPUT;

            break;
          }
        case CA_LED:
          {
            //Світлоіндимкатор
            n_prev = source_conf->n_led;
            copy_settings_LN = copy_settings_LED;

            break;
          }
        case CA_STANDART_LOGIC_AND:
          {
            //Елемент "І"
            n_prev = source_conf->n_and;
            copy_settings_LN = copy_settings_AND;

            break;
          }
        case CA_STANDART_LOGIC_OR:
          {
            //Елемент "АБО"
            n_prev = source_conf->n_or;
            copy_settings_LN = copy_settings_OR;

            break;
          }
        case CA_STANDART_LOGIC_XOR:
          {
            //Елемент "Викл.АБО"
            n_prev = source_conf->n_xor;
            copy_settings_LN = copy_settings_XOR;

            break;
          }
        case CA_STANDART_LOGIC_NOT:
          {
            //Елемент "НЕ"
            n_prev = source_conf->n_not;
            copy_settings_LN = copy_settings_NOT;

            break;
          }
        case CA_STANDART_LOGIC_TIMER:
          {
            //Елемент "Таймер"
            n_prev = source_conf->n_timer;
            copy_settings_LN = copy_settings_TIMER;

            break;
          }
        case CA_STANDART_LOGIC_TRIGGER:
          {
            //Елемент "Триґер"
            n_prev = source_conf->n_trigger;
            copy_settings_LN = copy_settings_TRIGGER;

            break;
          }
        case CA_MEANDER:
          {
            //Функціональний блок "Генератор періодичних сигналів"
            n_prev = source_conf->n_meander;
            copy_settings_LN = copy_settings_MEANDER;

            break;
          }
        default:
          {
            //Якщо сюди дійшла програма, значить відбулася недопустива помилка, тому треба зациклити програму, щоб вона пішла на перезагрузку
            total_error_sw_fixed(57);
          }
      }
      
      if (n_prev != 0)
      {
        //Викликаємо функцію повернення нових налаштувань у попередні значення
        (*copy_settings_LN)((targret_dyn == spca_of_p_prt), (source_dyn == spca_of_p_prt), targret_dyn[i], source_dyn[i], 0, n_prev);
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
/*****************************************************/
//
/*****************************************************/
