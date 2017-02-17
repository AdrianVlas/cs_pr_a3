#include "header.h"

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
      for(enum _menu2_levels i = MAIN_MANU2_LEVEL; i < MAX_NUMBER_MENU2_LEVEL; i++)
      {
        if ((i == PASSWORD_MENU2_LEVEL)/* || (i == EKRAN_LEVEL_SET_NEW_PASSWORD)*/) position_in_current_level_menu2[i] = INDEX_PASSWORD_M2_LINE1;
        else  position_in_current_level_menu2[i] = 0;
      }
  
      //Визначення початкового стану екрану
      current_state_menu2.current_level = MAIN_MANU2_LEVEL;
      current_state_menu2.index_position = position_in_current_level_menu2[current_state_menu2.current_level];
      current_state_menu2.position_cursor_y = current_state_menu2.index_position;
      current_state_menu2.p_max_row = NULL;
      current_state_menu2.max_row = MAX_ROW_MAIN_M2;
      current_state_menu2.func_move = move_into_main;
      current_state_menu2.func_show = make_ekran_main;
      current_state_menu2.func_press_enter = press_enter_in_main;
      current_state_menu2.func_press_esc = NULL;
      current_state_menu2.func_change = NULL;
      current_state_menu2.edition = ED_VIEWING;
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
  enum _id_fb block = _ID_FB_FIRST_ALL;
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
            if (modified == 0) point_2 = (uint8_t *)(&settings_fix);
          }
          
          point_1 = (uint8_t *)(&settings_fix_prt);
          
          break;
        }
      case ID_FB_INPUT:
        {
          if (item == 0)
          {
            size_of_block = sizeof(__settings_for_INPUT);
            n_item = current_config_prt.n_input;
            if (modified == 0) point_2 = (uint8_t *)(sca_of_p[ID_FB_INPUT - _ID_FB_FIRST_VAR]);
          }

          point_1 = (uint8_t *)(&(((__LN_INPUT*)spca_of_p_prt[ID_FB_INPUT - _ID_FB_FIRST_VAR]) + item)->settings) ;

          break;
        }
      case ID_FB_OUTPUT:
        {
          if (item == 0)
          {
            size_of_block = sizeof(__settings_for_OUTPUT);
            n_item = current_config_prt.n_output;
            if  (modified == 0) point_2 = (uint8_t *)(sca_of_p[ID_FB_OUTPUT - _ID_FB_FIRST_VAR]);
          }

          point_1 = (uint8_t *)(&(((__LN_OUTPUT*)spca_of_p_prt[ID_FB_OUTPUT - _ID_FB_FIRST_VAR]) + item)->settings) ;

          break;
        }
      case ID_FB_LED:
        {
          if (item == 0)
          {
            size_of_block = sizeof(__settings_for_LED);
            n_item = current_config_prt.n_led;
            if  (modified == 0) point_2 = (uint8_t *)(sca_of_p[ID_FB_LED - _ID_FB_FIRST_VAR]);
          }

          point_1 = (uint8_t *)(&(((__LN_LED*)spca_of_p_prt[ID_FB_LED - _ID_FB_FIRST_VAR]) + item)->settings) ;

          break;
        }
      case ID_FB_AND:
        {
          if (item == 0)
          {
            size_of_block = sizeof(__settings_for_AND);
            n_item = current_config_prt.n_and;
            if  (modified == 0) point_2 = (uint8_t *)(sca_of_p[ID_FB_AND - _ID_FB_FIRST_VAR]);
          }

          point_1 = (uint8_t *)(&(((__LN_AND*)spca_of_p_prt[ID_FB_AND - _ID_FB_FIRST_VAR]) + item)->settings) ;

          break;
        }
      case ID_FB_OR:
        {
          if (item == 0)
          {
            size_of_block = sizeof(__settings_for_OR);
            n_item = current_config_prt.n_or;
            if  (modified == 0) point_2 = (uint8_t *)(sca_of_p[ID_FB_OR - _ID_FB_FIRST_VAR]);
          }

          point_1 = (uint8_t *)(&(((__LN_OR*)spca_of_p_prt[ID_FB_OR - _ID_FB_FIRST_VAR]) + item)->settings) ;

          break;
        }
      case ID_FB_XOR:
        {
          if (item == 0)
          {
            size_of_block = sizeof(__settings_for_XOR);
            n_item = current_config_prt.n_xor;
            if  (modified == 0) point_2 = (uint8_t *)(sca_of_p[ID_FB_XOR - _ID_FB_FIRST_VAR]);
          }

          point_1 = (uint8_t *)(&(((__LN_XOR*)spca_of_p_prt[ID_FB_XOR - _ID_FB_FIRST_VAR]) + item)->settings) ;

          break;
        }
      case ID_FB_NOT:
        {
          if (item == 0)
          {
            size_of_block = sizeof(__settings_for_NOT);
            n_item = current_config_prt.n_not;
            if  (modified == 0) point_2 = (uint8_t *)(sca_of_p[ID_FB_NOT - _ID_FB_FIRST_VAR]);
          }

          point_1 = (uint8_t *)(&(((__LN_NOT*)spca_of_p_prt[ID_FB_NOT - _ID_FB_FIRST_VAR]) + item)->settings) ;

          break;
        }
      case ID_FB_TIMER:
        {
          if (item == 0)
          {
            size_of_block = sizeof(__settings_for_TIMER);
            n_item = current_config_prt.n_timer;
            if  (modified == 0) point_2 = (uint8_t *)(sca_of_p[ID_FB_TIMER - _ID_FB_FIRST_VAR]);
          }

          point_1 = (uint8_t *)(&(((__LN_TIMER*)spca_of_p_prt[ID_FB_TIMER - _ID_FB_FIRST_VAR]) + item)->settings) ;

          break;
        }
      case ID_FB_TRIGGER:
        {
          if (item == 0)
          {
            size_of_block = sizeof(__settings_for_TRIGGER);
            n_item = current_config_prt.n_trigger;
            if  (modified == 0) point_2 = (uint8_t *)(sca_of_p[ID_FB_TRIGGER - _ID_FB_FIRST_VAR]);
          }

          point_1 = (uint8_t *)(&(((__LN_TRIGGER*)spca_of_p_prt[ID_FB_TRIGGER - _ID_FB_FIRST_VAR]) + item)->settings) ;

          break;
        }
      case ID_FB_MEANDER:
        {
          if (item == 0)
          {
            size_of_block = sizeof(__settings_for_MEANDER);
            n_item = current_config_prt.n_meander;
            if  (modified == 0) point_2 = (uint8_t *)(sca_of_p[ID_FB_MEANDER - _ID_FB_FIRST_VAR]);
          }

          point_1 = (uint8_t *)(&(((__LN_MEANDER*)spca_of_p_prt[ID_FB_MEANDER - _ID_FB_FIRST_VAR]) + item)->settings) ;

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
      temp_value = *(point_1 + shift);
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
__result_dym_mem_select allocate_dynamic_memory_for_settings(__action_dym_mem_select make_remake_restore, unsigned int mem_for_prt, uintptr_t *p_sca_of_p_current[], uintptr_t *p_sca_of_p_control[], __CONFIG *current, __CONFIG *edited, __CONFIG *control)
{
  __result_dym_mem_select result = DYN_MEM_SELECT_OK;
  enum _id_fb index_1;
  
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
        {
          //Дискретний вихід
          n_prev = (make_remake_restore != MAKE_DYN_MEM) ? current->n_output : 0;
          p_current_field = &current->n_output;
          n_cur = edited->n_output;
          
          min_param = min_settings_OUTPUT;
          size = n_cur*((mem_for_prt == true) ? sizeof(__LN_OUTPUT) : sizeof(__settings_for_OUTPUT));
          break;
        }
      case ID_FB_LED:
        {
          //Світлоіндикатор
          n_prev = (make_remake_restore != MAKE_DYN_MEM) ? current->n_led : 0;
          p_current_field = &current->n_led;
          n_cur = edited->n_led;
          
          min_param = min_settings_LED;
          size = n_cur*((mem_for_prt == true) ? sizeof(__LN_LED) : sizeof(__settings_for_LED));
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
      default:
        {
          //Якщо сюди дійшла програма, значить відбулася недопустива помилка, тому треба зациклити програму, щоб вона пішла на перезагрузку
          total_error_sw_fixed(22);
        }
      }
    
      if ((make_remake_restore == MAKE_DYN_MEM) || (n_cur != n_prev))
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
            if (n_cur > n_prev)
            {
              //Викликаємо функцію встановлення нових налаштувань у мінімальні значення
              (*min_param)(mem_for_prt, ptr, n_prev, n_cur);
            }
          }
          else 
          {
            if ((make_remake_restore == MAKE_DYN_MEM) || (mem_for_prt != false) || (control == NULL)) result = DYN_MEM_TOTAL_ERROR;
            else result = DYN_MEM_NO_ENOUGH_MEM;
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
      (mem_for_prt != false) ||
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
      {
        //Дискретний вихід
        n_cur  = current->n_output;
        current->n_output = n_prev = control->n_output;
        
        copy_settings_LN = copy_settings_OUTPUT;
        size = n_prev*sizeof(__settings_for_OUTPUT);
        break;
      }
    case ID_FB_LED:
      {
        //Світлоіндимкатор
        n_cur  = current->n_led;
        current->n_led = n_prev = control->n_led;
        
        copy_settings_LN = copy_settings_LED;
        size = n_prev*sizeof(__settings_for_LED);
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
            if ( p_sca_of_p_control[index_1 - _ID_FB_FIRST_VAR] != NULL)
            {
              //Викликаємо функцію повернення нових налаштувань у попередні значення
              (*copy_settings_LN)(false, (p_sca_of_p_control == spca_of_p_prt), ptr, p_sca_of_p_control[index_1 - _ID_FB_FIRST_VAR], n_cur, n_prev);
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
      ((__LN_INPUT *)(base) + shift)->settings.delay.delay = KOEF_DOPUSK_DV_POST_MIN;
      ((__LN_INPUT *)(base) + shift)->settings.control = 0;
    }
    else 
    {
      ((__settings_for_INPUT *)(base) + shift)->delay.delay = KOEF_DOPUSK_DV_POST_MIN;
      ((__settings_for_INPUT *)(base) + shift)->control = 0;
    }
    
    if (mem_to_prt == true)
    {
      ((__LN_INPUT *)(base) + shift)->delay.delay = -1;
      for (size_t i = 0; i < DIV_TO_HIGHER(INPUT_SIGNALS, 8); i++)
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
    }
    else 
    {
      ((__settings_for_OUTPUT *)(base) + shift)->control = 0;
      ((__settings_for_OUTPUT *)(base) + shift)->param = 0;
    }
    
    if (mem_to_prt == true)
    {
      for (size_t i = 0; i < DIV_TO_HIGHER(OUTPUT_SIGNALS, 8); i++)
      {
        ((__LN_OUTPUT *)(base) + shift)->active_state[i] = 0;
      }
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
      ((__LN_LED *)(base) + shift)->settings.control = 0;
      ((__LN_LED *)(base) + shift)->settings.param = 0;
    }
    else 
    {
      ((__settings_for_LED *)(base) + shift)->control = 0;
      ((__settings_for_LED *)(base) + shift)->param = 0;
    }
    
    if (mem_to_prt == true)
    {
      for (size_t i = 0; i < DIV_TO_HIGHER(LED_SIGNALS, 8); i++)
      {
        ((__LN_LED *)(base) + shift)->active_state[i] = 0;
      }
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
      if (mem_to_prt == true) ((__LN_AND *)(base) + shift)->settings.param[i] = 0;
      else ((__settings_for_AND *)(base) + shift)->param[i] = 0;
    }
    
    if (mem_to_prt == true)
    {
      for (size_t i = 0; i < DIV_TO_HIGHER(AND_SIGNALS, 8); i++)
      {
        ((__LN_AND *)(base) + shift)->active_state[i] = 0;
        ((__LN_AND *)(base) + shift)->trigger_state[i] = 0;
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
      if (mem_to_prt == true) ((__LN_OR *)(base) + shift)->settings.param[i] = 0;
      else ((__settings_for_OR *)(base) + shift)->param[i] = 0;
    }
    
    if (mem_to_prt == true)
    {
      for (size_t i = 0; i < DIV_TO_HIGHER(OR_SIGNALS, 8); i++)
      {
        ((__LN_OR *)(base) + shift)->active_state[i] = 0;
        ((__LN_OR *)(base) + shift)->trigger_state[i] = 0;
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
      if (mem_to_prt == true) ((__LN_XOR *)(base) + shift)->settings.param[i] = 0;
      else ((__settings_for_XOR *)(base) + shift)->param[i] = 0;
    }
    
    if (mem_to_prt == true)
    {
      for (size_t i = 0; i < DIV_TO_HIGHER(XOR_SIGNALS, 8); i++)
      {
        ((__LN_XOR *)(base) + shift)->active_state[i] = 0;
        ((__LN_XOR *)(base) + shift)->trigger_state[i] = 0;
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
    if (mem_to_prt == true) ((__LN_NOT *)(base) + shift)->settings.param = 0;
    else ((__settings_for_NOT *)(base) + shift)->param = 0;
    
    if (mem_to_prt == true)
    {
      for (size_t i = 0; i < DIV_TO_HIGHER(NOT_SIGNALS, 8); i++)
      {
        ((__LN_NOT *)(base) + shift)->active_state[i] = 0;
        ((__LN_NOT *)(base) + shift)->trigger_state[i] = 0;
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
    }
    else 
    {
      ((__settings_for_TIMER *)(base) + shift)->param = 0;
      ((__settings_for_TIMER *)(base) + shift)->control = 0;
      ((__settings_for_TIMER *)(base) + shift)->delay.delay_pause = TIMEOUT_DF_PAUSE_MIN;
      ((__settings_for_TIMER *)(base) + shift)->delay.delay_work  = TIMEOUT_DF_WORK_MIN;
    }
    
    if (mem_to_prt == true)
    {
      ((__LN_TIMER *)(base) + shift)->delay.delay_pause = -1;
      ((__LN_TIMER *)(base) + shift)->delay.delay_work = -1;
      for (size_t i = 0; i < DIV_TO_HIGHER(TIMER_SIGNALS, 8); i++)
      {
        ((__LN_TIMER *)(base) + shift)->active_state[i] = 0;
        ((__LN_TIMER *)(base) + shift)->trigger_state[i] = 0;
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
    for (size_t i = 0; i < INPUT_TRIGGER_SIGNALS; i++)
    {
      if (mem_to_prt == true) ((__LN_TRIGGER *)(base) + shift)->settings.param[i] = 0;
      else ((__settings_for_TRIGGER *)(base) + shift)->param[i] = 0;
    }
    
    if (mem_to_prt == true)
    {
      for (size_t i = 0; i < DIV_TO_HIGHER(TRIGGER_SIGNALS, 8); i++)
      {
        ((__LN_TRIGGER *)(base) + shift)->active_state[i] = 0;
        ((__LN_TRIGGER *)(base) + shift)->trigger_state[i] = 0;
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
    for (size_t i = 0; i < INPUT_TRIGGER_SIGNALS; i++)
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
      ((__LN_MEANDER *)(base) + shift)->settings.delay.delay = TIMEOUT_MEANDER_MIN;
    }
    else 
    {
      ((__settings_for_MEANDER *)(base) + shift)->delay.delay = TIMEOUT_MEANDER_MIN;
    }
    
    if (mem_to_prt == true)
    {
      ((__LN_MEANDER *)(base) + shift)->delay.delay = -1;
      for (size_t i = 0; i < DIV_TO_HIGHER(MEANDER_SIGNALS, 8); i++)
      {
        ((__LN_MEANDER *)(base) + shift)->active_state[i] = 0;
        ((__LN_MEANDER *)(base) + shift)->trigger_state[i] = 0;
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
  for (enum _id_fb i = _ID_FB_FIRST_VAR; i < _ID_FB_LAST_VAR; i++)
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
      {
        size_block = current_config.n_output*sizeof(__settings_for_OUTPUT);
        break;
      }
    case ID_FB_LED:
      {
        size_block = current_config.n_led*sizeof(__settings_for_LED);
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
  
  for (enum _id_fb i = _ID_FB_FIRST_VAR; i < _ID_FB_LAST_VAR; i++)
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
          {
            //Дискретний вихід
            n_prev = source_conf->n_output;
            copy_settings_LN = copy_settings_OUTPUT;

            break;
          }
        case ID_FB_LED:
          {
            //Світлоіндимкатор
            n_prev = source_conf->n_led;
            copy_settings_LN = copy_settings_LED;

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
        default:
          {
            //Якщо сюди дійшла програма, значить відбулася недопустива помилка, тому треба зациклити програму, щоб вона пішла на перезагрузку
            total_error_sw_fixed(57);
          }
      }
      
      if ((n_prev != 0) && (target_dyn[i - _ID_FB_FIRST_VAR] != NULL))
      {
        //Викликаємо функцію повернення нових налаштувань у попередні значення
        (*copy_settings_LN)((target_dyn == spca_of_p_prt), (source_dyn == spca_of_p_prt), target_dyn[i - _ID_FB_FIRST_VAR], source_dyn[i - _ID_FB_FIRST_VAR], 0, n_prev);
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
1 - внести зміни у "для захистів" структурах і масивах
0 - відновити попердній стан по "для захисту" у стуктурах і масивах "контейнера" і "для редагування"

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
  if (direction)
  {
    __result_dym_mem_select result;
    //Активація внесених змін
    if (config_settings_modified & MASKA_CHANGED_CONFIGURATION)
    {
      __disable_interrupt();
      result = allocate_dynamic_memory_for_settings(REMAKE_DYN_MEM, true, spca_of_p_prt, NULL, &current_config_prt, &current_config, NULL);
    }

    if (result == DYN_MEM_SELECT_OK)
    {
      if (config_settings_modified & MASKA_CHANGED_SETTINGS)
      {
        //Відбувалися зміни у налаштуваннях
        __disable_interrupt(); /*конфігурація може записуватися, а може не записуватися, тому у цьому місці переривання вже можуть бути забороненими, або ще ні*/
        copy_settings(&current_config, &settings_fix_prt, &settings_fix, spca_of_p_prt, sca_of_p);
      }
      __enable_interrupt(); /*могла бути ситуація. що конфігурація змінювалася без зміни налаштувнь*/
    }
    else if (result == DYN_MEM_NO_ENOUGH_MEM) 
    {
      __enable_interrupt();
      /*
      при такому негативному резульаті зміни конфігурації все ж таки конфігурація повернулася 
      до свого попереднього стану, тому можна відновити інших більш пріоритетних систем, зокрема,
      системи захиств.
      У іншому випадку цього робити не можна. бо ми не знаємо, у якому стані зараз масиви налаштувань,
      які змінювалися у процесі зміни конфігурації
      */
    }
    
    
    if (result == DYN_MEM_SELECT_OK)
    {
      _SET_BIT(clear_diagnostyka, ERROR_NO_FREE_DYNAMIC_MEMORY_BIT);
      
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
      }
      
      //Записуємо час останньої зміни конфігурації
      uint8_t *label_to_time_array;
      if (copying_time == 0) label_to_time_array = time;
      else label_to_time_array = time_copy;
        
      for (size_t i = 0; i < 7; i++) settings_fix_prt.time_setpoints[i] = settings_fix.time_setpoints[i] = settings_fix_edit.time_setpoints[i] = *(label_to_time_array + i);
      settings_fix_prt.time_setpoints[7] = settings_fix.time_setpoints[7] = settings_fix_edit.time_setpoints[7] = (uint8_t)(source & 0xff);
      
      _SET_BIT(control_i2c_taskes, TASK_START_WRITE_SETTINGS_EEPROM_BIT);
    }
    else if (result == DYN_MEM_NO_ENOUGH_MEM) 
    {
      _SET_BIT(set_diagnostyka, ERROR_NO_FREE_DYNAMIC_MEMORY_BIT);
      
      error = 1;
    }
    else 
    {
      _SET_BIT(set_diagnostyka, ERROR_NO_FREE_DYNAMIC_MEMORY_BIT);
      
      error = 2;
    }
  }
  else
  {
    //Повернення до пстану до редагування
    if (config_settings_modified & MASKA_CHANGED_CONFIGURATION)
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
      else
      {
        _SET_BIT(clear_diagnostyka, ERROR_NO_FREE_DYNAMIC_MEMORY_BIT);
      }
    }
    
    if (
        (error == 0) &&
        (config_settings_modified & MASKA_CHANGED_SETTINGS)
       )   
    {
      //Відбувалися зміни у налаштуваннях
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
                                          current_config.n_and,
                                          current_config.n_or,
                                          current_config.n_xor,
                                          current_config.n_not,
                                          current_config.n_timer,
                                          current_config.n_trigger,
                                          current_config.n_meander
                                         };
    for (enum _id_fb i = _ID_FB_FIRST_VAR; i < _ID_FB_LAST_VAR; i++)
    {
      if (
           (i != ID_FB_INPUT) &&
           (i != ID_FB_MEANDER)
         )
      {
        uint32_t *p_param, *p_param_edit;
        intptr_t _n;
        switch (i)
        {
        case ID_FB_OUTPUT:
          {
            _n = 1;
            p_param      = &(((__settings_for_OUTPUT*)sca_of_p[i - _ID_FB_FIRST_VAR])->param);
            p_param_edit = &(((__settings_for_OUTPUT*)sca_of_p_edit[i - _ID_FB_FIRST_VAR])->param);
            break;
          }
        case ID_FB_LED:
          {
            _n = 1;
            p_param      = &(((__settings_for_LED*)sca_of_p[i - _ID_FB_FIRST_VAR])->param);
            p_param_edit = &(((__settings_for_LED*)sca_of_p_edit[i - _ID_FB_FIRST_VAR])->param);
            break;
          }
        case ID_FB_AND:
          {
            _n = NUMBER_IN_AND;
            p_param      = (((__settings_for_AND*)sca_of_p[i - _ID_FB_FIRST_VAR])->param);
            p_param_edit = (((__settings_for_AND*)sca_of_p_edit[i - _ID_FB_FIRST_VAR])->param);
            break;
          }
        case ID_FB_OR:
          {
            _n = NUMBER_IN_OR;
            p_param      = (((__settings_for_OR*)sca_of_p[i - _ID_FB_FIRST_VAR])->param);
            p_param_edit = (((__settings_for_OR*)sca_of_p_edit[i - _ID_FB_FIRST_VAR])->param);
            break;
          }
        case ID_FB_XOR:
          {
            _n = 2;
            p_param      = (((__settings_for_XOR*)sca_of_p[i - _ID_FB_FIRST_VAR])->param);
            p_param_edit = (((__settings_for_XOR*)sca_of_p_edit[i - _ID_FB_FIRST_VAR])->param);
            break;
          }
        case ID_FB_NOT:
          {
            _n = 1;
            p_param      = &(((__settings_for_NOT*)sca_of_p[i - _ID_FB_FIRST_VAR])->param);
            p_param_edit = &(((__settings_for_NOT*)sca_of_p_edit[i - _ID_FB_FIRST_VAR])->param);
            break;
          }
        case ID_FB_TIMER:
          {
            _n = 1;
            p_param      = &(((__settings_for_TIMER*)sca_of_p[i - _ID_FB_FIRST_VAR])->param);
            p_param_edit = &(((__settings_for_TIMER*)sca_of_p_edit[i - _ID_FB_FIRST_VAR])->param);
            break;
          }
        case ID_FB_TRIGGER:
          {
            _n = INPUT_TRIGGER_SIGNALS;
            p_param      = (((__settings_for_TRIGGER*)sca_of_p[i - _ID_FB_FIRST_VAR])->param);
            p_param_edit = (((__settings_for_TRIGGER*)sca_of_p_edit[i - _ID_FB_FIRST_VAR])->param);
            break;
          }
        default:
          {
            //Якщо сюди дійшла програма, значить відбулася недопустива помилка, тому треба зациклити програму, щоб вона пішла на перезагрузку
            total_error_sw_fixed(76);
          }
        }
        
        intptr_t shift = 0;
        for (intptr_t j = 0; j < _n; j++)
        {
          uint32_t param_input = *(p_param + j - shift);
          unsigned int id_input   = (param_input >> SFIFT_PARAM_ID ) & MASKA_PARAM_ID ;
          unsigned int n_input    = (param_input >> SFIFT_PARAM_N  ) & MASKA_PARAM_N  ;
//          unsigned int out_input  = (param_input >> SFIFT_PARAM_OUT) & MASKA_PARAM_OUT;
          
          //Робимо зміщення параметрування, щоб не було пропусків
          if (n_input > number[id_input - _ID_FB_FIRST_ALL])
          {
            *(p_param + j - shift) = *(p_param_edit + j - shift) = 0;
            
            for (intptr_t k = (j + 1); k < _n; k++)
            {
              *(p_param + (k - 1) - shift) = *(p_param_edit + (k - 1) - shift) = *(p_param + k - shift);
            }
            
            shift++;
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
