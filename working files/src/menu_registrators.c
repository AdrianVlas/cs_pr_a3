#include "header.h"

/*****************************************************/
//Формуємо екран відображення заголовків реєстраторів
/*****************************************************/
void make_ekran_list_registrators(void)
{
  int index_language = index_language_in_array(settings_fix_prt.language);
  
  unsigned int position_temp = current_state_menu2.index_position;
  unsigned int index_in_ekran = (position_temp >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;
  
  //Копіюємо  рядки у робочий екран
  for (size_t i = 0; i < MAX_ROW_LCD; i++)
  {
    //Наступні рядки треба перевірити, чи їх требе відображати у текучій коффігурації
    if (index_in_ekran < MAX_ROW_LIST_REGISTRATORS_M2)
      for (size_t j = 0; j < MAX_COL_LCD; j++) working_ekran[i][j] = name_string_registrators[index_language][index_in_ekran][j];
    else
      for (size_t j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = ' ';

    index_in_ekran++;
  }

  //Курсор по горизонталі відображається на першій позиції
  current_state_menu2.position_cursor_x = 0;
  //Відображення курору по вертикалі
  current_state_menu2.position_cursor_y = position_temp & (MAX_ROW_LCD - 1);
  //Курсор видимий
  current_state_menu2.cursor_on = 1;
  //Курсор не мигає
  current_state_menu2.cursor_blinking_on = 0;
  //Обновити повністю весь екран
  current_state_menu2.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/

/*****************************************************/
/*
Функція переміщення по меню записів Реєстратора програмних подій/Журналу подій

Вхідні параметри
(1 << BIT_REWRITE) - перемалювати меню
(1 << BIT_KEY_DOWN) - рухатися вниз
(1 << BIT_KEY_UP) - рухатися вверх
*/
/*****************************************************/
void move_into_ekran_event_registraqtors(unsigned int action, int max_row)
{
  if (max_row == 0) current_state_menu2.index_position = 0;
  else
  {
    if (action & ((1 << BIT_REWRITE) | (1 << BIT_KEY_DOWN)))
    {
      if (action & (1 << BIT_KEY_DOWN)) current_state_menu2.index_position++;
      if(current_state_menu2.index_position >= max_row) current_state_menu2.index_position = 0;
    }
    else if (action & (1 << BIT_KEY_UP))
    {
      if(--current_state_menu2.index_position < 0) current_state_menu2.index_position = max_row - 1;
    }
  }
}
/*****************************************************/

/*****************************************************/
//Формуємо екран відображення подій Журналу подій
/*****************************************************/
void make_ekran_list_event_log(void)
{
  int32_t index_language = index_language_in_array(settings_fix_prt.language);
  log_record_check_ok  = false;
  
  if (*current_state_menu2.p_max_row == 0)
  {
    //Копіюємо  рядки у робочий екран
    for (size_t i = 0; i < MAX_ROW_LCD; i++)
    {
      //Наступні рядки треба перевірити, чи їх требе відображати у текучій коффігурації
        for (size_t j = 0; j < MAX_COL_LCD; j++) working_ekran[i][j] = (i < 2) ? information_no_records[index_language][i][j] : ' ';
    }

    //Курсор по горизонталі відображається на першій позиції
    current_state_menu2.position_cursor_x = 0;
    //Відображення курору по вертикалі
    current_state_menu2.position_cursor_y = 0;
    //Курсор не видимий
    current_state_menu2.cursor_on = 0;
    //Курсор не мигає
    current_state_menu2.cursor_blinking_on = 0;
  }
  else
  {
    uint32_t position_temp = current_state_menu2.index_position;
    uint32_t index_in_ekran = ((position_temp << 1) >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;
    
    uint32_t record_read_ok, record_check_ok, id_input, n_input, out_input, event_state, NNC;
    for (size_t i = 0; i < MAX_ROW_LCD; i++)
    {
      uint32_t index_in_ekran_tmp = index_in_ekran >> 1;
      if (index_in_ekran_tmp < (uint32_t)(*current_state_menu2.p_max_row))
      {
        if ((i & 0x1) == 0)
        {
          //Перший рідок з двох на відображення запису
          
          //Подаємо команду на читання вибраного запису
          number_record_of_log_into_menu = index_in_ekran_tmp;
          _SET_STATE(control_tasks_dataflash, TASK_MAMORY_READ_DATAFLASH_FOR_LOG_MENU_BIT);

          uint32_t delta_time = 0;
          uint32_t time_start = TIM4->CNT;
          while (
                 ((control_tasks_dataflash &  MASKA_FOR_BIT(TASK_MAMORY_READ_DATAFLASH_FOR_LOG_MENU_BIT )) != 0) &&
                 (delta_time < MAX_TIMEOUT_WAITING_REQUESTED_DATA)  
                )   
          {
            uint32_t current_time_tim4 = TIM4->CNT;

            if (current_time_tim4 >= time_start)
              delta_time = current_time_tim4 - time_start;
            else 
              delta_time = current_time_tim4 + 0x10000 - time_start;

            //Робота з Watchdog
            watchdog_routine();
          }
          
          if ((control_tasks_dataflash &  MASKA_FOR_BIT(TASK_MAMORY_READ_DATAFLASH_FOR_LOG_MENU_BIT )) != 0)
          {
            //Ми не дочекалися завершення читання з мікросхеми DataFalash
            record_read_ok = false;
            _CLEAR_STATE(control_tasks_dataflash, TASK_MAMORY_READ_DATAFLASH_FOR_LOG_MENU_BIT);

            //Копіюємо  рядки у робочий екран
            for (size_t j = 0; j < MAX_ROW_LCD; j++)
            {
              //Наступні рядки треба перевірити, чи їх требе відображати у текучій коффігурації
              for (size_t k = 0; k < MAX_COL_LCD; j++) working_ekran[j][k] = (j < 2) ? information_timeout[index_language][j][k] : ' ';
            }
            
            //Курсор по горизонталі відображається на першій позиції
            current_state_menu2.position_cursor_x = 0;
            //Відображення курору по вертикалі
            current_state_menu2.position_cursor_y = 0;
            //Курсор не видимий
            current_state_menu2.cursor_on = 0;
            //Курсор не мигає
            current_state_menu2.cursor_blinking_on = 0;
            
            //Зупиняємо подальший вивід інформації
            break;
          }
          else
          {
            //Відбулося успішне зитування запису Журналу подій з мікросхеми DataFlash
            record_read_ok = true;
            
            //Перевіряємо достовірність даних
            uint32_t param;
            if (buffer_for_menu_read_record[0] == LABEL_START_RECORD_LOG)
            {
              param = (buffer_for_menu_read_record[ 8] << (0*8)) | 
                      (buffer_for_menu_read_record[ 9] << (1*8)) | 
                      (buffer_for_menu_read_record[10] << (2*8)) |
                      (buffer_for_menu_read_record[11] << (3*8));

              event_state = (param >> SFIFT_PARAM_INTERNAL_BITS) & MASKA_PARAM_INTERNAL_BITS;
              id_input  = (param >> SFIFT_PARAM_ID ) & MASKA_PARAM_ID ;
              n_input   = (param >> SFIFT_PARAM_N  ) & MASKA_PARAM_N  ;
              out_input = (param >> SFIFT_PARAM_OUT) & MASKA_PARAM_OUT;
              
              NNC = buffer_for_menu_read_record[12];
              
              record_check_ok = true;
            }
            else record_check_ok = false;
            
            if (index_in_ekran_tmp == position_temp) 
            {
              log_record_check_ok = record_check_ok;
              if (record_check_ok == true)
              {
                for (size_t j = 0; j < 7; j++) log_into_menu_time_label[j] = buffer_for_menu_read_record[1 + j];
              }
            }
            
            if (record_check_ok == true)
            {
              unsigned int part = 0;
              uint8_t *p = ((uint8_t*)array_p_name_out[id_input - _ID_FB_FIRST_ALL]) + (index_language*number_output_signals_logical_nodes[id_input - _ID_FB_FIRST_ALL] + (out_input - 1))*(MAX_COL_LCD + 1);
              unsigned int number_digit, first_index_number;
              
              unsigned int number_logical_node_tmp;
              if (
                  (id_input == ID_FB_BUTTON) &&
                  ((n_input - 1) >= NUMBER_FIX_BUTTONS)  
                 )
              {
                number_logical_node_tmp = n_input - NUMBER_FIX_BUTTONS;
              }
              else number_logical_node_tmp = n_input;
              
              size_t k = 0;
              for (size_t j = 0; j < MAX_COL_LCD; j++) 
              {
                switch (part)
                {
                case 0:
                  {
                    working_ekran[i][j] = ' ';
                    part++;
                    k = 0;
                
                    break;
                  }
                case 1:
                  {
                    uint8_t symbol;
                    if (
                        (id_input == ID_FB_BUTTON) &&
                        ((n_input - 1) < NUMBER_FIX_BUTTONS)  
                       )
                    {
                      symbol = name_fix_buttons[n_input - 1][k];
                    }
                    else
                    {
                      symbol = name_f_blocks[index_language][id_input - _ID_FB_FIRST_ALL][k];
                    }
                
                    if (symbol != ' ') 
                    {
                      working_ekran[i][j] = symbol;
                      k++;
                  
                      break;
                    }
                    else 
                    {
                      if (id_input == ID_FB_CONTROL_BLOCK) part += 2;
                      else 
                      {
                        if (
                            (
                             (id_input == ID_FB_BUTTON) &&
                             ((n_input - 1) < NUMBER_FIX_BUTTONS)  
                            )
                            ||
                            (
                             (id_input == ID_FB_EVENT_LOG)
                            ) 
                           )   
                        {
                          number_logical_node_tmp = 0;
                        }
                        else
                        {
                          number_digit = max_number_digit_in_number(number_logical_node_tmp);
                          first_index_number = j;
                        }
                        part++;
                      }
                      k = 0;
                    }
                  }
                case 2:
                  {
                    if (part == 2)
                    {
                      if (number_logical_node_tmp != 0)
                      {
                        /*
                        Заповнюємо значення зправа  на ліво
                        індекс = first_index_number + number_digit - 1 - (j - first_index_number) =
                        = first_index_number + number_digit - 1 - j + first_index_number =
                        = 2xfirst_index_number + number_digit - 1 - j =
                        */
                        working_ekran[i][2*first_index_number + number_digit - 1 - j] = (number_logical_node_tmp % 10) + 0x30;
                        number_logical_node_tmp /= 10;
                      }
                      else
                      {
                        working_ekran[i][j] = '.';
                        part++;
                        k = 0;
                      }
                
                      break;
                    }
                  }
                default:
                  {
                    working_ekran[i][j] = *(p + k++);
                    break;
                  }
                }
              }

              if (position_temp == index_in_ekran)
              {
                current_state_menu2.position_cursor_x = 0;
              }
            }
            else
            {
              for (size_t j = 0; j < MAX_COL_LCD; j++) working_ekran[i][j] = info_data_corrupted[index_language][0][j];
            }
          }
        }
        else
        {
          //Другий рідок з двох на відображення запису
          
          if (record_check_ok == true)
          {
            uint32_t number = index_in_ekran_tmp;
            uint32_t number_digit = max_number_digit_in_number(number);
            uint32_t number_digit_NNC, NNC_tmp;
            uint32_t cor = 0;
            
            if ((id_input == ID_FB_GROUP_ALARM) && (NNC != 0))
            {
              number_digit_NNC = max_number_digit_in_number(NNC);
              NNC_tmp = NNC;
            }
            for (size_t j = 0; j < MAX_COL_LCD; j++) 
            {
              if (j < 5)
              {
                uint8_t symbol = passive_active[index_language][event_state][j];
                working_ekran[i][j] = symbol;
                if (symbol == ' ') cor++;
              }
              else if ((j >= 5) && (j <= 9))
              {
                if ((id_input == ID_FB_GROUP_ALARM) && (NNC != 0))
                {
                  if (j == 5) working_ekran[i][5 - cor] = '(';
                  else if (j < (5 + number_digit_NNC + 1))
                  {
                    /*
                    Заповнюємо значення зправа  на ліво
                    індекс = (6 - cor) + number_digit_NNC - 1 - ((j - cor) - (6 - cor)) =
                    = (6 - cor) + number_digit_NNC - 1 - (j - cor) + (6 - cor) =
                    = 2*(6 - cor) + number_digit_NNC - 1 - (j - cor) =
                    */
                    working_ekran[i][2*(6 - cor) + number_digit_NNC - 1 - (j - cor)] = (NNC_tmp % 10) + 0x30;
                    NNC_tmp /= 10;
                  }
                  else if (j == (5 + number_digit_NNC + 1))  working_ekran[i][j - cor] = ')';
                  else if (j <= 9) working_ekran[i][j - cor] = ' ';
                  
                  if (j == 9) 
                  {
                    for (size_t k = 0; k < cor; k++ ) working_ekran[i][9 - k] = ' ';
                  }
                }
                else working_ekran[i][j] = ' ';
              }
              else
              {
                if (j < (MAX_COL_LCD - number_digit)) working_ekran[i][j] = ' ';
                else
                {
                  /*
                  Заповнюємо значення зправа  на ліво
                  індекс = (MAX_COL_LCD - number_digit) + number_digit - 1 - (j - (MAX_COL_LCD - number_digit)) =
                  = MAX_COL_LCD - number_digit + number_digit - 1 - (j - MAX_COL_LCD + number_digit) =
                  = MAX_COL_LCD - 1 - j + MAX_COL_LCD - number_digit =
                  = 2*MAX_COL_LCD - number_digit - 1 - j =
                  */
                  working_ekran[i][2*MAX_COL_LCD - number_digit - 1 - j] = (number % 10) + 0x30;
                  number /= 10;
                }
              }
            }
          }
          else
          {
            for (size_t j = 0; j < MAX_COL_LCD; j++) working_ekran[i][j] = info_data_corrupted[index_language][1][j];
          }
        }
      }
      else
      {
        for (size_t j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = ' ';
      }
      
      index_in_ekran++;
    }
  
    if (
        (record_read_ok == true) &&
        (record_check_ok == true)
       )   
    {
      //Курсор по горизонталі відображається на першій позиції
      current_state_menu2.position_cursor_x = 0;
      //Відображення курору по вертикалі
      current_state_menu2.position_cursor_y = (position_temp<<1) & (MAX_ROW_LCD - 1);
      //Курсор видимий
      current_state_menu2.cursor_on = 1;
    }
    else
    {
      //Курсор невидимий
      current_state_menu2.cursor_on = 0;
    }
    //Курсор не мигає
    current_state_menu2.cursor_blinking_on = 0;
  }
  //Обновити повністю весь екран
  current_state_menu2.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/

/*****************************************************/
//Формуємо екран відображення подій реєстратора програмих подій
/*****************************************************/
void make_ekran_list_event_pr_err(void)
{
  int32_t index_language = index_language_in_array(settings_fix_prt.language);
  pr_err_record_check_ok  = false;
  
  if (*current_state_menu2.p_max_row == 0)
  {
    //Копіюємо  рядки у робочий екран
    for (size_t i = 0; i < MAX_ROW_LCD; i++)
    {
      //Наступні рядки треба перевірити, чи їх требе відображати у текучій коффігурації
        for (size_t j = 0; j < MAX_COL_LCD; j++) working_ekran[i][j] = (i < 2) ? information_no_records[index_language][i][j] : ' ';
    }

    //Курсор по горизонталі відображається на першій позиції
    current_state_menu2.position_cursor_x = 0;
    //Відображення курору по вертикалі
    current_state_menu2.position_cursor_y = 0;
    //Курсор не видимий
    current_state_menu2.cursor_on = 0;
    //Курсор не мигає
    current_state_menu2.cursor_blinking_on = 0;
  }
  else
  {

    uint32_t position_temp = current_state_menu2.index_position;
    uint32_t index_in_ekran = ((position_temp<<1) >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;
    
    uint32_t record_read_ok, record_check_ok, event_state;
    for (size_t i = 0; i < MAX_ROW_LCD; i++)
    {
      uint32_t index_in_ekran_tmp = index_in_ekran >> 1;
      if (index_in_ekran_tmp < (uint32_t)(*current_state_menu2.p_max_row))
      {
        if ((i & 0x1) == 0)
        {
          //Пергий рідок з двох на відображення запису
          
          //Подаємо команду на читання вибраного запису
          number_record_of_pr_err_into_menu = index_in_ekran_tmp;
          _SET_STATE(control_tasks_dataflash, TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_MENU_BIT);

          uint32_t delta_time = 0;
          uint32_t time_start = TIM4->CNT;
          while (
                 ((control_tasks_dataflash &  MASKA_FOR_BIT(TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_MENU_BIT )) != 0) &&
                 (delta_time < MAX_TIMEOUT_WAITING_REQUESTED_DATA)  
                )   
          {
            uint32_t current_time_tim4 = TIM4->CNT;

            if (current_time_tim4 >= time_start)
              delta_time = current_time_tim4 - time_start;
            else 
              delta_time = current_time_tim4 + 0x10000 - time_start;

            //Робота з Watchdog
            watchdog_routine();
          }
          
          if ((control_tasks_dataflash &  MASKA_FOR_BIT(TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_MENU_BIT )) != 0)
          {
            //Ми не дочекалися завершення читання з мікросхеми DataFalash
            record_read_ok = false;
            _CLEAR_STATE(control_tasks_dataflash, TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_MENU_BIT);

            //Копіюємо  рядки у робочий екран
            for (size_t j = 0; j < MAX_ROW_LCD; j++)
            {
              //Наступні рядки треба перевірити, чи їх требе відображати у текучій коффігурації
              for (size_t k = 0; k < MAX_COL_LCD; j++) working_ekran[j][k] = (j < 2) ? information_timeout[index_language][j][k] : ' ';
            }
            
            //Курсор по горизонталі відображається на першій позиції
            current_state_menu2.position_cursor_x = 0;
            //Відображення курору по вертикалі
            current_state_menu2.position_cursor_y = 0;
            //Курсор не видимий
            current_state_menu2.cursor_on = 0;
            //Курсор не мигає
            current_state_menu2.cursor_blinking_on = 0;
            
            //Зупиняємо подальший вивід інформації
            break;
          }
          else
          {
            //Відбулося успішне зитування запису реєстратора програмних подій з мікросхеми DataFlash
            record_read_ok = true;
            
            //Перевіряємо достовірність даних
            size_t event_number;
            if (buffer_for_menu_read_record[0] == LABEL_START_RECORD_PR_ERR)
            {
              event_number = buffer_for_menu_read_record[8] | ((buffer_for_menu_read_record[9] & 0x7f) << 8);
              if ((event_number >= 1) && (event_number <= NUMBER_ERRORS))
              {
                event_state = (buffer_for_menu_read_record[9] >> 7) & 0x1;
                record_check_ok = true;
              }
              else record_check_ok = false;
            }
            else record_check_ok = false;
            if (index_in_ekran_tmp == position_temp) 
            {
              pr_err_record_check_ok = record_check_ok;
              if (record_check_ok == true)
              {
                for (size_t j = 0; j < 7; j++) pr_err_into_menu_time_label[j] = buffer_for_menu_read_record[1 + j];
              }
            }
            
            if (record_check_ok == true)
            {
              if (event_number <= _NUMBER_ERRORS_WITHOUT_DIGITAL_OUTPUTS)
              {
                for (size_t j = 0; j < MAX_COL_LCD; j++) working_ekran[i][j] = name_string_pr_err[index_language][event_number - 1][j];
              }
              else
              {
                uint32_t first_index = first_index_array_name_error_rele[index_language];

                uint32_t number = event_number - _NUMBER_ERRORS_WITHOUT_DIGITAL_OUTPUTS;
                uint32_t number_digit = max_number_digit_in_number(number);
              
                for (unsigned int j = 0; j < MAX_COL_LCD; j++) 
                {
                  if (j < first_index) working_ekran[i][j] = name_string_pr_err[index_language][_NUMBER_ERRORS_WITHOUT_DIGITAL_OUTPUTS][j];
                  else if ((j - first_index) < number_digit)
                  {
                    /*
                    Заповнюємо значення зправа  на ліво
                    індекс = first_index + number_digit - 1 - (j - first_index) =
                    = first_index + number_digit - 1 - j + first_index =
                    = 2first_index + number_digit - 1 - j =
                    */
                    working_ekran[i][2*first_index + number_digit - 1 - j] = (number % 10) + 0x30;
                    number /= 10;
                  }
                  else working_ekran[i][j] = name_string_pr_err[index_language][_NUMBER_ERRORS_WITHOUT_DIGITAL_OUTPUTS][j - number_digit];
                }
              }
            }
            else
            {
              for (size_t j = 0; j < MAX_COL_LCD; j++) working_ekran[i][j] = info_data_corrupted[index_language][0][j];
            }
          }
        }
        else
        {
          //Другий рідок з двох на відображення запису
          
          if (record_check_ok == true)
          {
           uint32_t number = index_in_ekran_tmp;
            uint32_t number_digit = max_number_digit_in_number(number);
            for (size_t j = 0; j < MAX_COL_LCD; j++) 
            {
              if (j < 5)
              {
                working_ekran[i][j] = passive_active[index_language][event_state][j];
              }
              else
              {
                if (j < (MAX_COL_LCD - number_digit)) working_ekran[i][j] = ' ';
                else
                {
                  /*
                  Заповнюємо значення зправа  на ліво
                  індекс = (MAX_COL_LCD - number_digit) + number_digit - 1 - (j - (MAX_COL_LCD - number_digit)) =
                  = MAX_COL_LCD - number_digit + number_digit - 1 - (j - MAX_COL_LCD + number_digit) =
                  = MAX_COL_LCD - 1 - j + MAX_COL_LCD - number_digit =
                  = 2*MAX_COL_LCD - number_digit - 1 - j =
                  */
                  working_ekran[i][2*MAX_COL_LCD - number_digit - 1 - j] = (number % 10) + 0x30;
                  number /= 10;
                }
              }
            }
          }
          else
          {
            for (size_t j = 0; j < MAX_COL_LCD; j++) working_ekran[i][j] = info_data_corrupted[index_language][1][j];
          }
        }
      }
      else
      {
        for (size_t j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = ' ';
      }
      
      index_in_ekran++;
    }
  
    if (
        (record_read_ok == true) &&
        (record_check_ok == true)
       )   
    {
      //Курсор по горизонталі відображається на першій позиції
      current_state_menu2.position_cursor_x = 0;
      //Відображення курору по вертикалі
      current_state_menu2.position_cursor_y = (position_temp<<1) & (MAX_ROW_LCD - 1);
      //Курсор видимий
      current_state_menu2.cursor_on = 1;
    }
    else
    {
      //Курсор невидимий
      current_state_menu2.cursor_on = 0;
    }
    //Курсор не мигає
    current_state_menu2.cursor_blinking_on = 0;
  }
  //Обновити повністю весь екран
  current_state_menu2.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/

/*****************************************************/
//Формуємо екран відображення дати реєстраторів
/*****************************************************/
void make_ekran_data_reg(void)
{
  uint8_t name_string[2][MAX_COL_LCD + 1] = 
  {
    "   XX-XX-20XX    ",
    "   XX:XX:XX.XX   "
  };
  
  uint8_t *point_into_menu_time_label;
  if (current_state_menu2.current_level == LOG_DATA_MENU2_LEVEL) point_into_menu_time_label = log_into_menu_time_label;
  else if (current_state_menu2.current_level == PR_ERR_DATA_MENU2_LEVEL) point_into_menu_time_label = pr_err_into_menu_time_label;
  else
  {
    //Якщо сюди дійшла програма, значить відбулася недопустива помилка, тому треба зациклити програму, щоб вона пішла на перезагрузку
    total_error_sw_fixed(7);
  }
  
  /******************************************/
  //Заповнюємо поля відповідними цифрами
  /******************************************/
  //День
  name_string[ROW_R_Y_][COL_DY1_R] = (point_into_menu_time_label[4] >>  4) + 0x30;
  name_string[ROW_R_Y_][COL_DY2_R] = (point_into_menu_time_label[4] & 0xf) + 0x30;

  //Місяць
  name_string[ROW_R_Y_][COL_MY1_R] = (point_into_menu_time_label[5] >>  4) + 0x30;
  name_string[ROW_R_Y_][COL_MY2_R] = (point_into_menu_time_label[5] & 0xf) + 0x30;

  //Рік
  name_string[ROW_R_Y_][COL_SY1_R] = (point_into_menu_time_label[6] >>  4) + 0x30;
  name_string[ROW_R_Y_][COL_SY2_R] = (point_into_menu_time_label[6] & 0xf) + 0x30;

  //Година
  name_string[ROW_R_T_][COL_HT1_R] = (point_into_menu_time_label[3] >>  4) + 0x30;
  name_string[ROW_R_T_][COL_HT2_R] = (point_into_menu_time_label[3] & 0xf) + 0x30;

  //Хвилини
  name_string[ROW_R_T_][COL_MT1_R] = (point_into_menu_time_label[2] >>  4) + 0x30;
  name_string[ROW_R_T_][COL_MT2_R] = (point_into_menu_time_label[2] & 0xf) + 0x30;

  //Секунди
  name_string[ROW_R_T_][COL_ST1_R] = (point_into_menu_time_label[1] >>  4) + 0x30;
  name_string[ROW_R_T_][COL_ST2_R] = (point_into_menu_time_label[1] & 0xf) + 0x30;

  //Соті секунд
  name_string[ROW_R_T_][COL_HST1_R] = (point_into_menu_time_label[0] >>  4) + 0x30;
  name_string[ROW_R_T_][COL_HST2_R] = (point_into_menu_time_label[0] & 0xf) + 0x30;

  //Копіюємо  рядки у робочий екран
  for (size_t i = 0; i < MAX_ROW_LCD; i++)
  {
    for (size_t j = 0; j < MAX_COL_LCD; j++)  working_ekran[i][j] = (i < 2) ? name_string[i][j] : ' ';
  }

  //Курсор по горизонталі відображається на першій позиції
  current_state_menu2.position_cursor_x = 0;
  //Відображення курору по вертикалі
  current_state_menu2.position_cursor_y = 0;
  //Курсор не видимий
  current_state_menu2.cursor_on = 0;
  //Курсор не мигає
  current_state_menu2.cursor_blinking_on = 0;
  //Обновити повністю весь екран
  current_state_menu2.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/

/*****************************************************/
//
/*****************************************************/
/*****************************************************/
