#include "header.h"

const uint8_t * const array_p_name_in[NUMBER_ALL_BLOCKS] = 
{
  (const uint8_t*)name_fix_block_in_signals, 
  NULL, 
  (const uint8_t*)name_output_led_in_signals, 
  (const uint8_t*)name_output_led_in_signals, 
  NULL, 
  (const uint8_t*)name_alarm_in_signals, 
  NULL, 
  (const uint8_t*)name_standard_logic_in_signals, 
  (const uint8_t*)name_standard_logic_in_signals, 
  (const uint8_t*)name_standard_logic_in_signals, 
  (const uint8_t*)name_standard_logic_in_signals, 
  (const uint8_t*)name_timer_in_signals, 
  (const uint8_t*)name_trigger_in_signals, 
  NULL, 
  (const uint8_t*)name_tu_in_signals,
  (const uint8_t*)name_ts_in_signals,
  (const uint8_t*)name_input_GOOSE_block_in_signals,
  (const uint8_t*)name_input_MMS_block_in_signals,
  (const uint8_t*)name_network_output_block_in_signals,
  NULL
};

const enum _menu2_levels levels_tmp[__NEXT_AFTER_EDITOR_LIST_SELECTED_TYPE_LOGICAL_NODE_FOR_OUTPUT_MENU2_LEVEL - __BEGIN_EDITOR_LIST_SELECTED_TYPE_LOGICAL_NODE_FOR_OUTPUT_MENU2_LEVEL] =
{
  EDITOR_LIST_INPUTS_FOR_OUTPUT_MENU2_LEVEL,
  EDITOR_LIST_OUTPUTS_FOR_OUTPUT_MENU2_LEVEL,
  EDITOR_LIST_LEDS_FOR_OUTPUT_MENU2_LEVEL,
  EDITOR_LIST_BUTTONS_FOR_OUTPUT_MENU2_LEVEL,
  EDITOR_LIST_ALARMS_FOR_OUTPUT_MENU2_LEVEL,
  EDITOR_LIST_GROUP_ALARMS_FOR_OUTPUT_MENU2_LEVEL,
  EDITOR_LIST_ANDS_FOR_OUTPUT_MENU2_LEVEL,
  EDITOR_LIST_ORS_FOR_OUTPUT_MENU2_LEVEL,
  EDITOR_LIST_XORS_FOR_OUTPUT_MENU2_LEVEL,
  EDITOR_LIST_NOTS_FOR_OUTPUT_MENU2_LEVEL,
  EDITOR_LIST_TIMERS_FOR_OUTPUT_MENU2_LEVEL,
  EDITOR_LIST_TRIGGERS_FOR_OUTPUT_MENU2_LEVEL,
  EDITOR_LIST_MEANDERS_FOR_OUTPUT_MENU2_LEVEL,
  EDITOR_LIST_TUS_FOR_OUTPUT_MENU2_LEVEL,
  EDITOR_LIST_TSS_FOR_OUTPUT_MENU2_LEVEL,
  EDITOR_LIST_INPUT_GOOSE_BLOCKS_FOR_OUTPUT_MENU2_LEVEL,
  EDITOR_LIST_INPUT_MMS_BLOCKS_FOR_OUTPUT_MENU2_LEVEL,
  EDITOR_LIST_NETWORK_OUTPUT_BLOCKS_FOR_OUTPUT_MENU2_LEVEL
};
/*****************************************************/
/*
Функція переміщення по меню

Вхідні параметри
(1 << BIT_REWRITE) - перемалювати меню
(1 << BIT_KEY_DOWN) - рухатися вниз
(1 << BIT_KEY_UP) - рухатися вверх
*/
/*****************************************************/
void move_into_editor_list_logical_nodes(unsigned int action, int max_row)
{
  __CONFIG *p_config;
  switch (current_state_menu2.edition)
  {
  case ED_VIEWING:
    {
      p_config = &current_config_prt;
      break;
    }
  case ED_CAN_BE_EDITED:
    {
      p_config = &current_config;
      break;
    }
  default:
    {
      p_config = &current_config_edit;
      break;
    }
  }
  unsigned int logical_node_shown[NUMBER_ALL_BLOCKS];
  if (current_state_menu2.current_level == EDITOR_LIST_LOGICAL_NODES_FOR_INPUT_MENU2_LEVEL)
  {
    
    logical_node_shown[ 0] = (FIX_BLOCK_SIGNALS_IN > 0) ? true: false;
    logical_node_shown[ 1] = ((p_config->n_input*0                                             ) != 0);
    logical_node_shown[ 2] = ((p_config->n_output*OUTPUT_LED_SIGNALS_IN                        ) != 0);
    logical_node_shown[ 3] = ((p_config->n_led*OUTPUT_LED_SIGNALS_IN                           ) != 0);
    logical_node_shown[ 4] = ((p_config->n_button*0                                            ) != 0);
    logical_node_shown[ 5] = ((p_config->n_alarm*ALARM_SIGNALS_IN                              ) != 0);
    logical_node_shown[ 6] = ((p_config->n_group_alarm*0                                       ) != 0);
    logical_node_shown[ 7] = ((p_config->n_and*AND_SIGNALS_IN                                  ) != 0);
    logical_node_shown[ 8] = ((p_config->n_or*OR_SIGNALS_IN                                    ) != 0);
    logical_node_shown[ 9] = ((p_config->n_xor*2                                               ) != 0);
    logical_node_shown[10] = ((p_config->n_not*1                                               ) != 0);
    logical_node_shown[11] = ((p_config->n_timer*TIMER_SIGNALS_IN                              ) != 0);
    logical_node_shown[12] = ((p_config->n_trigger*TRIGGER_SIGNALS_IN                          ) != 0);
    logical_node_shown[13] = ((p_config->n_meander*0                                           ) != 0);
    logical_node_shown[14] = ((p_config->n_tu*TU_SIGNALS_IN                                    ) != 0);
    logical_node_shown[15] = ((p_config->n_ts*TS_SIGNALS_IN                                    ) != 0);
    logical_node_shown[16] = ((p_config->n_input_GOOSE_block*INPUT_GOOSE_BLOCK_SIGNALS_IN      ) != 0);
    logical_node_shown[17] = ((p_config->n_input_MMS_block*INPUT_MMS_BLOCK_SIGNALS_IN          ) != 0);
    logical_node_shown[18] = ((p_config->n_network_output_block*NETWORK_OUTPUT_BLOCK_SIGNALS_IN) != 0);
    logical_node_shown[19] = ((p_config->n_log*LOG_SIGNALS_IN                                  ) != 0);
  }
  else
  {
    logical_node_shown[ 0] = (FIX_BLOCK_SIGNALS_OUT > 0) ? true: false;
    logical_node_shown[ 1] = ((p_config->n_input*INPUT_SIGNALS_OUT                              ) != 0);
    logical_node_shown[ 2] = ((p_config->n_output*OUTPUT_LED_SIGNALS_OUT                        ) != 0);
    logical_node_shown[ 3] = ((p_config->n_led*OUTPUT_LED_SIGNALS_OUT                           ) != 0);
    logical_node_shown[ 4] = ((p_config->n_button*BUTTON_SIGNALS_OUT                            ) != 0);
    logical_node_shown[ 5] = ((p_config->n_alarm*ALARM_SIGNALS_OUT                              ) != 0);
    logical_node_shown[ 6] = ((p_config->n_group_alarm*GROUP_ALARM_SIGNALS_OUT                  ) != 0);
    logical_node_shown[ 7] = ((p_config->n_and*STANDARD_LOGIC_SIGNALS_OUT                       ) != 0);
    logical_node_shown[ 8] = ((p_config->n_or*STANDARD_LOGIC_SIGNALS_OUT                        ) != 0);
    logical_node_shown[ 9] = ((p_config->n_xor*STANDARD_LOGIC_SIGNALS_OUT                       ) != 0);
    logical_node_shown[10] = ((p_config->n_not*STANDARD_LOGIC_SIGNALS_OUT                       ) != 0);
    logical_node_shown[11] = ((p_config->n_timer*TIMER_SIGNALS_OUT                              ) != 0);
    logical_node_shown[12] = ((p_config->n_trigger*TRIGGER_SIGNALS_OUT                          ) != 0);
    logical_node_shown[13] = ((p_config->n_meander*MEANDER_SIGNALS_OUT                          ) != 0);
    logical_node_shown[14] = ((p_config->n_tu*TU_SIGNALS_OUT                                    ) != 0);
    logical_node_shown[15] = ((p_config->n_ts*TS_SIGNALS_OUT                                    ) != 0);
    logical_node_shown[16] = ((p_config->n_input_GOOSE_block*INPUT_GOOSE_BLOCK_SIGNALS_OUT      ) != 0);
    logical_node_shown[17] = ((p_config->n_input_MMS_block*INPUT_MMS_BLOCK_SIGNALS_OUT          ) != 0);
    logical_node_shown[18] = ((p_config->n_network_output_block*NETWORK_OUTPUT_BLOCK_SIGNALS_OUT) != 0);
    logical_node_shown[19] = ((p_config->n_log*EVENT_LOG_SIGNALS_OUT                            ) != 0);
  };
  
  if (action & ((1 << BIT_REWRITE) | (1 << BIT_KEY_DOWN)))
  {
    if (action & (1 << BIT_KEY_DOWN)) current_state_menu2.index_position++;
    do
    {
      if (current_state_menu2.index_position >= max_row) current_state_menu2.index_position = 0;
      while (logical_node_shown[current_state_menu2.index_position] != true)
      {
        if(++current_state_menu2.index_position >= max_row) current_state_menu2.index_position = 0;
      }
    }
    while ((action & (1 << BIT_KEY_DOWN)) && (current_state_menu2.index_position >= max_row));
  }
  else if (action & (1 << BIT_KEY_UP))
  {
    current_state_menu2.index_position--;
    do
    {
      if(current_state_menu2.index_position < 0) current_state_menu2.index_position = max_row - 1;
      while (logical_node_shown[current_state_menu2.index_position] != true)
      {
        if(--current_state_menu2.index_position < 0) current_state_menu2.index_position = max_row - 1;
      }
    }
    while (current_state_menu2.index_position < 0);
  }
}
/*****************************************************/

/*****************************************************/
//Формуємо екран
/*****************************************************/
void make_ekran_editor_list_logical_node(void)
{
  if (
      (current_state_menu2.edition == ED_WARNING_EDITION_BUSY) ||
      (current_state_menu2.edition == ED_WARNING_ENTER_ESC)
     )   
  {
    enum _edition_stats edition = current_state_menu2.edition;
    make_ekran_about_info(((edition == ED_WARNING_EDITION_BUSY) ? 0 : 2), ((edition == ED_WARNING_EDITION_BUSY) ? information_no_edition : information_request));
  }
  else
  {
    __CONFIG *p_config;
    switch (current_state_menu2.edition)
    {
    case ED_VIEWING:
      {
        p_config = &current_config_prt;
        break;
      }
    case ED_CAN_BE_EDITED:
      {
        p_config = &current_config;
        break;
      }
    default:
      {
        p_config = &current_config_edit;
        break;
      }
    }
    unsigned int logical_node_shown[NUMBER_ALL_BLOCKS];
    if (current_state_menu2.current_level == EDITOR_LIST_LOGICAL_NODES_FOR_INPUT_MENU2_LEVEL)
    {
      logical_node_shown[ 0] = (FIX_BLOCK_SIGNALS_IN > 0) ? true: false;
      logical_node_shown[ 1] = ((p_config->n_input*0                                             ) != 0);
      logical_node_shown[ 2] = ((p_config->n_output*OUTPUT_LED_SIGNALS_IN                        ) != 0);
      logical_node_shown[ 3] = ((p_config->n_led*OUTPUT_LED_SIGNALS_IN                           ) != 0);
      logical_node_shown[ 4] = ((p_config->n_button*0                                            ) != 0);
      logical_node_shown[ 5] = ((p_config->n_alarm*ALARM_SIGNALS_IN                              ) != 0);
      logical_node_shown[ 6] = ((p_config->n_group_alarm*0                                       ) != 0);
      logical_node_shown[ 7] = ((p_config->n_and*AND_SIGNALS_IN                                  ) != 0);
      logical_node_shown[ 8] = ((p_config->n_or*OR_SIGNALS_IN                                    ) != 0);
      logical_node_shown[ 9] = ((p_config->n_xor*2                                               ) != 0);
      logical_node_shown[10] = ((p_config->n_not*1                                               ) != 0);
      logical_node_shown[11] = ((p_config->n_timer*TIMER_SIGNALS_IN                              ) != 0);
      logical_node_shown[12] = ((p_config->n_trigger*TRIGGER_SIGNALS_IN                          ) != 0);
      logical_node_shown[13] = ((p_config->n_meander*0                                           ) != 0);
      logical_node_shown[14] = ((p_config->n_tu*TU_SIGNALS_IN                                    ) != 0);
      logical_node_shown[15] = ((p_config->n_ts*TS_SIGNALS_IN                                    ) != 0);
      logical_node_shown[16] = ((p_config->n_input_GOOSE_block*INPUT_GOOSE_BLOCK_SIGNALS_IN      ) != 0);
      logical_node_shown[17] = ((p_config->n_input_MMS_block*INPUT_MMS_BLOCK_SIGNALS_IN          ) != 0);
      logical_node_shown[18] = ((p_config->n_network_output_block*NETWORK_OUTPUT_BLOCK_SIGNALS_IN) != 0);
      logical_node_shown[19] = ((p_config->n_log*LOG_SIGNALS_IN                                  ) != 0);
    }     
    else
    {
      logical_node_shown[ 0] = (FIX_BLOCK_SIGNALS_OUT > 0) ? true: false;
      logical_node_shown[ 1] = ((p_config->n_input*INPUT_SIGNALS_OUT                              ) != 0);
      logical_node_shown[ 2] = ((p_config->n_output*OUTPUT_LED_SIGNALS_OUT                        ) != 0);
      logical_node_shown[ 3] = ((p_config->n_led*OUTPUT_LED_SIGNALS_OUT                           ) != 0);
      logical_node_shown[ 4] = ((p_config->n_button*BUTTON_SIGNALS_OUT                            ) != 0);
      logical_node_shown[ 5] = ((p_config->n_alarm*ALARM_SIGNALS_OUT                              ) != 0);
      logical_node_shown[ 6] = ((p_config->n_group_alarm*GROUP_ALARM_SIGNALS_OUT                  ) != 0);
      logical_node_shown[ 7] = ((p_config->n_and*STANDARD_LOGIC_SIGNALS_OUT                       ) != 0);
      logical_node_shown[ 8] = ((p_config->n_or*STANDARD_LOGIC_SIGNALS_OUT                        ) != 0);
      logical_node_shown[ 9] = ((p_config->n_xor*STANDARD_LOGIC_SIGNALS_OUT                       ) != 0);
      logical_node_shown[10] = ((p_config->n_not*STANDARD_LOGIC_SIGNALS_OUT                       ) != 0);
      logical_node_shown[11] = ((p_config->n_timer*TIMER_SIGNALS_OUT                              ) != 0);
      logical_node_shown[12] = ((p_config->n_trigger*TRIGGER_SIGNALS_OUT                          ) != 0);
      logical_node_shown[13] = ((p_config->n_meander*MEANDER_SIGNALS_OUT                          ) != 0);
      logical_node_shown[14] = ((p_config->n_tu*TU_SIGNALS_OUT                                    ) != 0);
      logical_node_shown[15] = ((p_config->n_ts*TS_SIGNALS_OUT                                    ) != 0);
      logical_node_shown[16] = ((p_config->n_input_GOOSE_block*INPUT_GOOSE_BLOCK_SIGNALS_OUT      ) != 0);
      logical_node_shown[17] = ((p_config->n_input_MMS_block*INPUT_MMS_BLOCK_SIGNALS_OUT          ) != 0);
      logical_node_shown[18] = ((p_config->n_network_output_block*NETWORK_OUTPUT_BLOCK_SIGNALS_OUT) != 0);
      logical_node_shown[19] = ((p_config->n_log*EVENT_LOG_SIGNALS_OUT                            ) != 0);
    };
  
    int index_language = index_language_in_array(select_struct_settings_fix()->language);
  
    unsigned int additional_current = 0;
    unsigned int position_temp = current_state_menu2.index_position;

    uint8_t name_string_tmp[MAX_ROW_FOR_EDITOR_LIST_LOGICAL_NODES][MAX_COL_LCD + 1];
    for(size_t index_1 = 0; index_1 < MAX_ROW_FOR_EDITOR_LIST_LOGICAL_NODES; index_1++)
    {
      if (logical_node_shown[index_1] != true)
      {
        if ((index_1 - additional_current) < position_temp) position_temp--;
        additional_current++;

        for(size_t index_2 = 0; index_2 < MAX_COL_LCD; index_2++)
        {
          name_string_tmp[MAX_ROW_FOR_EDITOR_LIST_LOGICAL_NODES - additional_current][index_2] = ' ';
        }
        name_string_tmp[MAX_ROW_FOR_EDITOR_LIST_LOGICAL_NODES - additional_current][MAX_COL_LCD] = '\0';
      }
      else
      {
        for(size_t index_2 = 0; index_2 < (MAX_COL_LCD + 1); index_2++)
        {
          name_string_tmp[index_1 - additional_current][index_2] = name_string_editor_logical_nodes[index_language][index_1][index_2];
        }
      }
    }
    unsigned int index_in_ekran = (position_temp >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;
  
    //Копіюємо  рядки у робочий екран
    for (size_t i = 0; i < MAX_ROW_LCD; i++)
    {
      //Наступні рядки треба перевірити, чи їх требе відображати у текучій коффігурації
      for (size_t j = 0; j < MAX_COL_LCD; j++) 
      {
        working_ekran[i][j] = (index_in_ekran < (MAX_ROW_FOR_EDITOR_LIST_LOGICAL_NODES - additional_current)) ? name_string_tmp[index_in_ekran][j] : ' ';
      }
      index_in_ekran++;
    }

    //Курсор по горизонталі відображається на першій позиції
    current_state_menu2.position_cursor_x = 0;
    //Відображення курору по вертикалі
    current_state_menu2.position_cursor_y = position_temp & (MAX_ROW_LCD - 1);
    //Курсор видимий
    current_state_menu2.cursor_on = 1;
    //Курсор не мигає або мигає
    current_state_menu2.cursor_blinking_on = (current_state_menu2.edition < ED_EDITION) ? 0 : 1;
  }
  //Обновити повністю весь екран
  current_state_menu2.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/

/*****************************************************/
//Формуємо екран
/*****************************************************/
void make_ekran_editor_list_inputs_of_selected_logical_node(void)
{
  if (current_state_menu2.edition == ED_WARNING_EDITION_BUSY)
  {
    make_ekran_about_info(0, information_no_edition);
  }
  else
  {
    int index_language = index_language_in_array(select_struct_settings_fix()->language);
    unsigned int position_temp = current_state_menu2.index_position;
  
    unsigned int type_logical_node, number_logical_node;

    enum _menu2_levels ekran_before = previous_level_in_current_level_menu2[current_state_menu2.current_level];
    if (ekran_before == EDITOR_LIST_LOGICAL_NODES_FOR_INPUT_MENU2_LEVEL)
    {
      number_logical_node = 1;
      type_logical_node = ID_FB_CONTROL_BLOCK;
    }
    else if (
             (ekran_before >= __BEGIN_EDITOR_LIST_SELECTED_TYPE_LOGICAL_NODE_FOR_INPUT_MENU2_LEVEL) &&
             (ekran_before <  __NEXT_AFTER_EDITOR_LIST_SELECTED_TYPE_LOGICAL_NODE_FOR_INPUT_MENU2_LEVEL)
            )   
    {
      number_logical_node = current_state_menu2.number_selection + 1; /*1 додаємо, індексація починається з нуля, а позначення у param  має іти з 1*/
    
      ekran_before = previous_level_in_current_level_menu2[ekran_before];
      if (ekran_before == EDITOR_LIST_LOGICAL_NODES_FOR_INPUT_MENU2_LEVEL)
      {
        type_logical_node = position_in_current_level_menu2[ekran_before] + _ID_FB_FIRST_ALL;
      }
    }
  
    unsigned int error = false;
    unsigned int max_row = current_state_menu2.max_row;
    if (
        (ekran_before == EDITOR_LIST_LOGICAL_NODES_FOR_INPUT_MENU2_LEVEL) &&
        (max_row != 0) &&
        (array_p_name_in[type_logical_node - _ID_FB_FIRST_ALL] != NULL)
       )   
    {
      unsigned int index_in_ekran = (position_temp >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;
  
      //Формуємо рядки  рядки у робочий екран
      for (size_t i = 0; i < MAX_ROW_LCD; i++)
      {
        //Наступні рядки треба перевірити, чи їх требе відображати
        if (index_in_ekran < max_row)
        {
          unsigned int part = 0;
          uint8_t *p = ((uint8_t*)array_p_name_in[type_logical_node - _ID_FB_FIRST_ALL]) + (index_language*max_row + index_in_ekran)*(MAX_COL_LCD + 1);
          unsigned int number_digit, first_index_number, number_logical_node_tmp = number_logical_node;
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
                uint8_t symbol = name_f_blocks[index_language][type_logical_node - _ID_FB_FIRST_ALL][k];
              
                if (symbol != ' ') 
                {
                  working_ekran[i][j] = symbol;
                  k++;
                
                  break;
                }
                else 
                {
                  if (type_logical_node == ID_FB_CONTROL_BLOCK) part += 2;
                  else 
                  {
                    number_digit = max_number_digit_in_number(number_logical_node);
                    first_index_number = j;
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
        }
        else
        {
          for (size_t j = 0; j < MAX_COL_LCD; j++) working_ekran[i][j] = ' ';
        }

        index_in_ekran++;
      }
    }
    else
    {
      //Цього при правильній роботі програми не мало б бути
      error = true;
      for (size_t i = 0; i < MAX_ROW_LCD; i++)
      {
        for (size_t j = 0; j < MAX_COL_LCD; j++) working_ekran[i][j] = (i == 0) ? information_error[index_language][j] : ' ';
      }
    }
  

    //Курсор по горизонталі відображається на першій позиції
    current_state_menu2.position_cursor_x = 0;
    //Відображення курору по вертикалі
    current_state_menu2.position_cursor_y = (error == false) ? (position_temp & (MAX_ROW_LCD - 1)) : 0;
    //Курсор видимий
    current_state_menu2.cursor_on = (error == false) ? 1 : 0;
    //Курсор не мигає
    current_state_menu2.cursor_blinking_on = 0;
  }
  //Обновити повністю весь екран
  current_state_menu2.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/

/*****************************************************/
/*
Натискування Enter
*/
/*****************************************************/
enum _result_pressed_enter_during_edition press_enter_in_editor_list_logical_node(void)
{
  unsigned int error = false;
  unsigned int type_logical_node_in, number_logical_node_in;
  int index;
  size_t n_similar_input_signals;
  uint32_t *p_param_cont, *p_param_edit;

  //Оскільки ми багато чого могли змінити, тому коли вертаємося у список налаштованих функцій переходимо не на той сигнал з якого входили у редагування (бо його могли прибрати або залишити), а на перший відображуваний сигнал
  position_in_current_level_menu2[EDITOR_VIEW_CHOSEN_SIGNAL_OF_SELECTED_LOGICAL_NODE_MENU2_LEVEL] = 0;

  //Шукаємо тепер вхідну інформацію
  /*
                                                             1-е повернення                                                  2-е повернення                                  3-повернення  
  EDITOR_LIST_LOGICAL_NODES_FOR_OUTPUT_MENU2_LEVEL->EDITOR_VIEW_CHOSEN_SIGNAL_OF_SELECTED_LOGICAL_NODE_MENU2_LEVEL->EDITOR_LIST_INPUTS_OF_SELECTED_LOGICAL_NODE_MENU2_LEVEL->EDITOR_LIST_XXX_FOR_INPUT_MENU2_LEVEL->EDITOR_LIST_LOGICAL_NODES_FOR_INPUT_MENU2_LEVEL
                                                                                                                  |                                                        |
                                                                                                                  |                                                         ->EDITOR_LIST_LOGICAL_NODES_FOR_INPUT_MENU2_LEVEL (якщо був вибраний "Загальний блок")
                                                                                                                   ->EDITOR_LIST_LOGICAL_NODES_FOR_INPUT_MENU2_LEVEL (якщо вбув вибраний "Загальний блок")
  */
  enum _menu2_levels ekran_before = previous_level_in_current_level_menu2[previous_level_in_current_level_menu2[current_state_menu2.current_level]];
  if (ekran_before == EDITOR_LIST_LOGICAL_NODES_FOR_INPUT_MENU2_LEVEL)
  {
//    index = 0; //для даного випадку у цій змінній немає сенсу
//    number_logical_node_in = 1; //для даного випадку у цій змінній немає сенсу
    type_logical_node_in = ID_FB_EVENT_LOG;
  }
  else if (ekran_before == EDITOR_LIST_INPUTS_OF_SELECTED_LOGICAL_NODE_MENU2_LEVEL)
  {
    index = position_in_current_level_menu2[ekran_before];
    
    ekran_before = previous_level_in_current_level_menu2[ekran_before];
    if (ekran_before == EDITOR_LIST_LOGICAL_NODES_FOR_INPUT_MENU2_LEVEL)
    {   
      number_logical_node_in = 1;
      type_logical_node_in = ID_FB_CONTROL_BLOCK;
    }
    else if (
             (ekran_before >= __BEGIN_EDITOR_LIST_SELECTED_TYPE_LOGICAL_NODE_FOR_INPUT_MENU2_LEVEL) &&
             (ekran_before <  __NEXT_AFTER_EDITOR_LIST_SELECTED_TYPE_LOGICAL_NODE_FOR_INPUT_MENU2_LEVEL)
            )   
    {
      number_logical_node_in = position_in_current_level_menu2[ekran_before] + 1; /*1 додаємо, індексація починається з нуля, а позначення у param  має іти з 1*/
  
      ekran_before = previous_level_in_current_level_menu2[ekran_before];
      if (ekran_before == EDITOR_LIST_LOGICAL_NODES_FOR_INPUT_MENU2_LEVEL)
      {
        type_logical_node_in = position_in_current_level_menu2[ekran_before] + _ID_FB_FIRST_ALL;
      }
      else error = true;
    }
    else error = true;
  }
  else error = true;
      
  if (error == false)
  {
    n_similar_input_signals = array_n_similar_input_signals[type_logical_node_in - _ID_FB_FIRST_ALL];
    if (n_similar_input_signals != 0) 
    {
      switch (type_logical_node_in)
      {
      case ID_FB_CONTROL_BLOCK:
        {
          p_param_cont = &settings_fix.param[index*n_similar_input_signals];
          p_param_edit = &settings_fix_edit.param[index*n_similar_input_signals];
          break;
        }
      case ID_FB_OUTPUT:
      case ID_FB_LED:
        {
          p_param_cont = &(((__settings_for_OUTPUT_LED*)sca_of_p[type_logical_node_in - _ID_FB_FIRST_VAR] + (number_logical_node_in - 1))->param[index*n_similar_input_signals]);
          p_param_edit = &(((__settings_for_OUTPUT_LED*)sca_of_p_edit[type_logical_node_in - _ID_FB_FIRST_VAR] + (number_logical_node_in - 1))->param[index*n_similar_input_signals]);
          break;
        }
      case ID_FB_ALARM:
        {
          p_param_cont = &(((__settings_for_ALARM*)sca_of_p[ID_FB_ALARM - _ID_FB_FIRST_VAR] + (number_logical_node_in - 1))->param[index*n_similar_input_signals]);
          p_param_edit = &(((__settings_for_ALARM*)sca_of_p_edit[ID_FB_ALARM - _ID_FB_FIRST_VAR] + (number_logical_node_in - 1))->param[index*n_similar_input_signals]);
          break;
        }
      case ID_FB_AND:
        {
          p_param_cont = &(((__settings_for_AND*)sca_of_p[ID_FB_AND - _ID_FB_FIRST_VAR] + (number_logical_node_in - 1))->param[index*n_similar_input_signals]);
          p_param_edit = &(((__settings_for_AND*)sca_of_p_edit[ID_FB_AND - _ID_FB_FIRST_VAR] + (number_logical_node_in - 1))->param[index*n_similar_input_signals]);
          break;
        }
      case ID_FB_OR:
        {
          p_param_cont = &(((__settings_for_OR*)sca_of_p[ID_FB_OR - _ID_FB_FIRST_VAR] + (number_logical_node_in - 1))->param[index*n_similar_input_signals]);
          p_param_edit = &(((__settings_for_OR*)sca_of_p_edit[ID_FB_OR - _ID_FB_FIRST_VAR] + (number_logical_node_in - 1))->param[index*n_similar_input_signals]);
          break;
        }
      case ID_FB_XOR:
        {
          p_param_cont = &(((__settings_for_XOR*)sca_of_p[ID_FB_XOR - _ID_FB_FIRST_VAR] + (number_logical_node_in - 1))->param[index*n_similar_input_signals]);
          p_param_edit = &(((__settings_for_XOR*)sca_of_p_edit[ID_FB_XOR - _ID_FB_FIRST_VAR] + (number_logical_node_in - 1))->param[index*n_similar_input_signals]);
          break;
        }
      case ID_FB_NOT:
        {
          p_param_cont = &(((__settings_for_NOT*)sca_of_p[ID_FB_NOT - _ID_FB_FIRST_VAR] + (number_logical_node_in - 1))->param[index*n_similar_input_signals]);
          p_param_edit = &(((__settings_for_NOT*)sca_of_p_edit[ID_FB_NOT - _ID_FB_FIRST_VAR] + (number_logical_node_in - 1))->param[index*n_similar_input_signals]);
          break;
        }
       case ID_FB_TIMER:
        {
          p_param_cont = &(((__settings_for_TIMER*)sca_of_p[ID_FB_TIMER - _ID_FB_FIRST_VAR] + (number_logical_node_in - 1))->param[index*n_similar_input_signals]);
          p_param_edit = &(((__settings_for_TIMER*)sca_of_p_edit[ID_FB_TIMER - _ID_FB_FIRST_VAR] + (number_logical_node_in - 1))->param[index*n_similar_input_signals]);
          break;
        }
      case ID_FB_TRIGGER:
        {
          p_param_cont = &(((__settings_for_TRIGGER*)sca_of_p[ID_FB_TRIGGER - _ID_FB_FIRST_VAR] + (number_logical_node_in - 1))->param[index*n_similar_input_signals]);
          p_param_edit = &(((__settings_for_TRIGGER*)sca_of_p_edit[ID_FB_TRIGGER - _ID_FB_FIRST_VAR] + (number_logical_node_in - 1))->param[index*n_similar_input_signals]);
          break;
        }
      case ID_FB_TU:
        {
          p_param_cont = &(((__settings_for_TU*)sca_of_p[ID_FB_TU - _ID_FB_FIRST_VAR] + (number_logical_node_in - 1))->param[index*n_similar_input_signals]);
          p_param_edit = &(((__settings_for_TU*)sca_of_p_edit[ID_FB_TU - _ID_FB_FIRST_VAR] + (number_logical_node_in - 1))->param[index*n_similar_input_signals]);
          break;
        }
      case ID_FB_TS:
        {
          p_param_cont = &(((__settings_for_TS*)sca_of_p[ID_FB_TS - _ID_FB_FIRST_VAR] + (number_logical_node_in - 1))->param[index*n_similar_input_signals]);
          p_param_edit = &(((__settings_for_TS*)sca_of_p_edit[ID_FB_TS - _ID_FB_FIRST_VAR] + (number_logical_node_in - 1))->param[index*n_similar_input_signals]);
          break;
        }
      case ID_FB_INPUT_GOOSE_BLOCK:
        {
          p_param_cont = &(((__settings_for_INPUT_GOOSE_BLOCK*)sca_of_p[ID_FB_INPUT_GOOSE_BLOCK - _ID_FB_FIRST_VAR] + (number_logical_node_in - 1))->param[index*n_similar_input_signals]);
          p_param_edit = &(((__settings_for_INPUT_GOOSE_BLOCK*)sca_of_p_edit[ID_FB_INPUT_GOOSE_BLOCK - _ID_FB_FIRST_VAR] + (number_logical_node_in - 1))->param[index*n_similar_input_signals]);
          break;
        }
      case ID_FB_INPUT_MMS_BLOCK:
        {
          p_param_cont = &(((__settings_for_INPUT_MMS_BLOCK*)sca_of_p[ID_FB_INPUT_MMS_BLOCK - _ID_FB_FIRST_VAR] + (number_logical_node_in - 1))->param[index*n_similar_input_signals]);
          p_param_edit = &(((__settings_for_INPUT_MMS_BLOCK*)sca_of_p_edit[ID_FB_INPUT_MMS_BLOCK - _ID_FB_FIRST_VAR] + (number_logical_node_in - 1))->param[index*n_similar_input_signals]);
          break;
        }
      case ID_FB_NETWORK_OUTPUT_BLOCK:
        {
          p_param_cont = &(((__settings_for_NETWORK_OUTPUT_BLOCK*)sca_of_p[ID_FB_NETWORK_OUTPUT_BLOCK - _ID_FB_FIRST_VAR] + (number_logical_node_in - 1))->param[index*n_similar_input_signals]);
          p_param_edit = &(((__settings_for_NETWORK_OUTPUT_BLOCK*)sca_of_p_edit[ID_FB_NETWORK_OUTPUT_BLOCK - _ID_FB_FIRST_VAR] + (number_logical_node_in - 1))->param[index*n_similar_input_signals]);
          break;
        }
      case ID_FB_EVENT_LOG:
        {
          n_similar_input_signals *= current_config_edit.n_log;
          
          p_param_cont = ((__LOG_INPUT*)sca_of_p[ID_FB_EVENT_LOG - _ID_FB_FIRST_VAR]);
          p_param_edit = ((__LOG_INPUT*)sca_of_p_edit[ID_FB_EVENT_LOG - _ID_FB_FIRST_VAR]);
          break;
        }
      default:
        {
          //Якщо сюди дійшла програма, значить відбулася недопустива помилка, тому треба зациклити програму, щоб вона пішла на перезагрузку
          total_error_sw_fixed(117);
        }
      }
   
      for (size_t i = 0; i < n_similar_input_signals; i++) p_param_cont[i] = p_param_edit[i];
      config_settings_modified |= MASKA_FOR_BIT(BIT_CHANGED_SCHEMATIC);
    }
    else error = true;
  }
  
  if (error == true)
  {
    //Якщо сюди дійшла програма, значить відбулася недопустива помилка, тому треба зациклити програму, щоб вона пішла на перезагрузку
    total_error_sw_fixed(121);
  }
  
  return RPEDE_DATA_CHANGED_OK;
}
/*****************************************************/

/*****************************************************/
/*
Натискування ESC
*/
/*****************************************************/
void press_esc_in_editor_list_logical_node(void)
{
  unsigned int error = false;
  unsigned int type_logical_node_in, number_logical_node_in;
  int index;
  size_t n_similar_input_signals;
  uint32_t *p_param_cont, *p_param_edit;

  //Шукаємо тепер вхідну інформацію
  /*
                                                             1-е повернення                                                  2-е повернення                                  3-повернення  
  EDITOR_LIST_LOGICAL_NODES_FOR_OUTPUT_MENU2_LEVEL->EDITOR_VIEW_CHOSEN_SIGNAL_OF_SELECTED_LOGICAL_NODE_MENU2_LEVEL->EDITOR_LIST_INPUTS_OF_SELECTED_LOGICAL_NODE_MENU2_LEVEL->EDITOR_LIST_XXX_FOR_INPUT_MENU2_LEVEL->EDITOR_LIST_LOGICAL_NODES_FOR_INPUT_MENU2_LEVEL
                                                                                                                  |                                                        |
                                                                                                                  |                                                         ->EDITOR_LIST_LOGICAL_NODES_FOR_INPUT_MENU2_LEVEL (якщо був вибраний "Загальний блок")
                                                                                                                   ->EDITOR_LIST_LOGICAL_NODES_FOR_INPUT_MENU2_LEVEL (якщо вбув вибраний "Загальний блок")
  */
  enum _menu2_levels ekran_before = previous_level_in_current_level_menu2[previous_level_in_current_level_menu2[current_state_menu2.current_level]];
  if (ekran_before == EDITOR_LIST_LOGICAL_NODES_FOR_INPUT_MENU2_LEVEL)
  {
//    index = 0; //для даного випадку у цій змінній немає сенсу
//    number_logical_node_in = 1; //для даного випадку у цій змінній немає сенсу
    type_logical_node_in = ID_FB_EVENT_LOG;
  }
  else if (ekran_before == EDITOR_LIST_INPUTS_OF_SELECTED_LOGICAL_NODE_MENU2_LEVEL)
  {
    index = position_in_current_level_menu2[ekran_before];
    
    ekran_before = previous_level_in_current_level_menu2[ekran_before];
    if (ekran_before == EDITOR_LIST_LOGICAL_NODES_FOR_INPUT_MENU2_LEVEL)
    {   
      number_logical_node_in = 1;
      type_logical_node_in = ID_FB_CONTROL_BLOCK;
    }
    else if (
             (ekran_before >= __BEGIN_EDITOR_LIST_SELECTED_TYPE_LOGICAL_NODE_FOR_INPUT_MENU2_LEVEL) &&
             (ekran_before <  __NEXT_AFTER_EDITOR_LIST_SELECTED_TYPE_LOGICAL_NODE_FOR_INPUT_MENU2_LEVEL)
            )   
    {
      number_logical_node_in = position_in_current_level_menu2[ekran_before] + 1; /*1 додаємо, індексація починається з нуля, а позначення у param  має іти з 1*/
  
      ekran_before = previous_level_in_current_level_menu2[ekran_before];
      if (ekran_before == EDITOR_LIST_LOGICAL_NODES_FOR_INPUT_MENU2_LEVEL)
      {
        type_logical_node_in = position_in_current_level_menu2[ekran_before] + _ID_FB_FIRST_ALL;
      }
      else error = true;
    }
    else error = true;
  }
  else error = true;
      
  if (error == false)
  {
    n_similar_input_signals = array_n_similar_input_signals[type_logical_node_in - _ID_FB_FIRST_ALL];
    if (n_similar_input_signals != 0) 
    {
      switch (type_logical_node_in)
      {
      case ID_FB_CONTROL_BLOCK:
        {
          p_param_cont = &settings_fix.param[index*n_similar_input_signals];
          p_param_edit = &settings_fix_edit.param[index*n_similar_input_signals];
          break;
        }
      case ID_FB_OUTPUT:
      case ID_FB_LED:
        {
          p_param_cont = &(((__settings_for_OUTPUT_LED*)sca_of_p[type_logical_node_in - _ID_FB_FIRST_VAR] + (number_logical_node_in - 1))->param[index*n_similar_input_signals]);
          p_param_edit = &(((__settings_for_OUTPUT_LED*)sca_of_p_edit[type_logical_node_in - _ID_FB_FIRST_VAR] + (number_logical_node_in - 1))->param[index*n_similar_input_signals]);
          break;
        }
      case ID_FB_ALARM:
        {
          p_param_cont = &(((__settings_for_ALARM*)sca_of_p[ID_FB_ALARM - _ID_FB_FIRST_VAR] + (number_logical_node_in - 1))->param[index*n_similar_input_signals]);
          p_param_edit = &(((__settings_for_ALARM*)sca_of_p_edit[ID_FB_ALARM - _ID_FB_FIRST_VAR] + (number_logical_node_in - 1))->param[index*n_similar_input_signals]);
          break;
        }
      case ID_FB_AND:
        {
          p_param_cont = &(((__settings_for_AND*)sca_of_p[ID_FB_AND - _ID_FB_FIRST_VAR] + (number_logical_node_in - 1))->param[index*n_similar_input_signals]);
          p_param_edit = &(((__settings_for_AND*)sca_of_p_edit[ID_FB_AND - _ID_FB_FIRST_VAR] + (number_logical_node_in - 1))->param[index*n_similar_input_signals]);
          break;
        }
      case ID_FB_OR:
        {
          p_param_cont = &(((__settings_for_OR*)sca_of_p[ID_FB_OR - _ID_FB_FIRST_VAR] + (number_logical_node_in - 1))->param[index*n_similar_input_signals]);
          p_param_edit = &(((__settings_for_OR*)sca_of_p_edit[ID_FB_OR - _ID_FB_FIRST_VAR] + (number_logical_node_in - 1))->param[index*n_similar_input_signals]);
          break;
        }
      case ID_FB_XOR:
        {
          p_param_cont = &(((__settings_for_XOR*)sca_of_p[ID_FB_XOR - _ID_FB_FIRST_VAR] + (number_logical_node_in - 1))->param[index*n_similar_input_signals]);
          p_param_edit = &(((__settings_for_XOR*)sca_of_p_edit[ID_FB_XOR - _ID_FB_FIRST_VAR] + (number_logical_node_in - 1))->param[index*n_similar_input_signals]);
          break;
        }
      case ID_FB_NOT:
        {
          p_param_cont = &(((__settings_for_NOT*)sca_of_p[ID_FB_NOT - _ID_FB_FIRST_VAR] + (number_logical_node_in - 1))->param[index*n_similar_input_signals]);
          p_param_edit = &(((__settings_for_NOT*)sca_of_p_edit[ID_FB_NOT - _ID_FB_FIRST_VAR] + (number_logical_node_in - 1))->param[index*n_similar_input_signals]);
          break;
        }
       case ID_FB_TIMER:
        {
          p_param_cont = &(((__settings_for_TIMER*)sca_of_p[ID_FB_TIMER - _ID_FB_FIRST_VAR] + (number_logical_node_in - 1))->param[index*n_similar_input_signals]);
          p_param_edit = &(((__settings_for_TIMER*)sca_of_p_edit[ID_FB_TIMER - _ID_FB_FIRST_VAR] + (number_logical_node_in - 1))->param[index*n_similar_input_signals]);
          break;
        }
       case ID_FB_TRIGGER:
        {
          p_param_cont = &(((__settings_for_TRIGGER*)sca_of_p[ID_FB_TRIGGER - _ID_FB_FIRST_VAR] + (number_logical_node_in - 1))->param[index*n_similar_input_signals]);
          p_param_edit = &(((__settings_for_TRIGGER*)sca_of_p_edit[ID_FB_TRIGGER - _ID_FB_FIRST_VAR] + (number_logical_node_in - 1))->param[index*n_similar_input_signals]);
          break;
        }
      case ID_FB_TU:
        {
          p_param_cont = &(((__settings_for_TU*)sca_of_p[ID_FB_TU - _ID_FB_FIRST_VAR] + (number_logical_node_in - 1))->param[index*n_similar_input_signals]);
          p_param_edit = &(((__settings_for_TU*)sca_of_p_edit[ID_FB_TU - _ID_FB_FIRST_VAR] + (number_logical_node_in - 1))->param[index*n_similar_input_signals]);
          break;
        }
      case ID_FB_TS:
        {
          p_param_cont = &(((__settings_for_TS*)sca_of_p[ID_FB_TS - _ID_FB_FIRST_VAR] + (number_logical_node_in - 1))->param[index*n_similar_input_signals]);
          p_param_edit = &(((__settings_for_TS*)sca_of_p_edit[ID_FB_TS - _ID_FB_FIRST_VAR] + (number_logical_node_in - 1))->param[index*n_similar_input_signals]);
          break;
        }
      case ID_FB_INPUT_GOOSE_BLOCK:
        {
          p_param_cont = &(((__settings_for_INPUT_GOOSE_BLOCK*)sca_of_p[ID_FB_INPUT_GOOSE_BLOCK - _ID_FB_FIRST_VAR] + (number_logical_node_in - 1))->param[index*n_similar_input_signals]);
          p_param_edit = &(((__settings_for_INPUT_GOOSE_BLOCK*)sca_of_p_edit[ID_FB_INPUT_GOOSE_BLOCK - _ID_FB_FIRST_VAR] + (number_logical_node_in - 1))->param[index*n_similar_input_signals]);
          break;
        }
      case ID_FB_INPUT_MMS_BLOCK:
        {
          p_param_cont = &(((__settings_for_INPUT_MMS_BLOCK*)sca_of_p[ID_FB_INPUT_MMS_BLOCK - _ID_FB_FIRST_VAR] + (number_logical_node_in - 1))->param[index*n_similar_input_signals]);
          p_param_edit = &(((__settings_for_INPUT_MMS_BLOCK*)sca_of_p_edit[ID_FB_INPUT_MMS_BLOCK - _ID_FB_FIRST_VAR] + (number_logical_node_in - 1))->param[index*n_similar_input_signals]);
          break;
        }
      case ID_FB_NETWORK_OUTPUT_BLOCK:
        {
          p_param_cont = &(((__settings_for_NETWORK_OUTPUT_BLOCK*)sca_of_p[ID_FB_NETWORK_OUTPUT_BLOCK - _ID_FB_FIRST_VAR] + (number_logical_node_in - 1))->param[index*n_similar_input_signals]);
          p_param_edit = &(((__settings_for_NETWORK_OUTPUT_BLOCK*)sca_of_p_edit[ID_FB_NETWORK_OUTPUT_BLOCK - _ID_FB_FIRST_VAR] + (number_logical_node_in - 1))->param[index*n_similar_input_signals]);
          break;
        }
      case ID_FB_EVENT_LOG:
        {
          n_similar_input_signals *= current_config_edit.n_log;
          
          p_param_cont = ((__LOG_INPUT*)sca_of_p[ID_FB_EVENT_LOG - _ID_FB_FIRST_VAR]);
          p_param_edit = ((__LOG_INPUT*)sca_of_p_edit[ID_FB_EVENT_LOG - _ID_FB_FIRST_VAR]);
          break;
        }
      default:
        {
          //Якщо сюди дійшла програма, значить відбулася недопустива помилка, тому треба зациклити програму, щоб вона пішла на перезагрузку
          total_error_sw_fixed(119);
        }
      }
    }
    else error = true;
  }
  
  if (error == false)
  {
    if (current_state_menu2.edition == ED_EDITION)
    {
      unsigned int difference = false;
      size_t i = 0;
      while (
             (difference == false) &&
             (i < n_similar_input_signals)  
            ) 
      {
        if (p_param_edit[i] != p_param_cont[i])
        {
          difference = true;
          current_state_menu2.edition = ED_WARNING_ENTER_ESC;
          current_state_menu2.func_press_enter = press_enter_in_editor_list_logical_node;
        }
        i++;
      }
    }
    else if (current_state_menu2.edition == ED_WARNING_ENTER_ESC)
    {
      for (size_t i = 0; i < n_similar_input_signals; i++) p_param_edit[i] = p_param_cont[i];
      current_state_menu2.edition = ED_EDITION;
    }
  }
  else
  {
    //Якщо сюди дійшла програма, значить відбулася недопустива помилка, тому треба зациклити програму, щоб вона пішла на перезагрузку
    total_error_sw_fixed(120);
  }
}
/*****************************************************/

/*****************************************************/
/*
Функція переміщення по меню

Вхідні параметри
(1 << BIT_REWRITE) - перемалювати меню
(1 << BIT_KEY_DOWN) - рухатися вниз
(1 << BIT_KEY_UP) - рухатися вверх
*/
/*****************************************************/
void move_into_editor_view_chosen_of_selected_logical_node(unsigned int action, int max_row)
{
  if (max_row == 1) current_state_menu2.index_position = 0;
  else
  {
    unsigned int type_logical_node, number_logical_node;
    int index;

    unsigned int error = false;

    enum _menu2_levels ekran_before = previous_level_in_current_level_menu2[current_state_menu2.current_level];
    if (ekran_before == EDITOR_LIST_LOGICAL_NODES_FOR_INPUT_MENU2_LEVEL)
    {
//      index = 0; //для даного випадку у цій змінній немає сенсу
//      number_logical_node = 1; //для даного випадку у цій змінній немає сенсу
      type_logical_node = ID_FB_EVENT_LOG;
    }
    else if (ekran_before == EDITOR_LIST_INPUTS_OF_SELECTED_LOGICAL_NODE_MENU2_LEVEL)
    {
      index = position_in_current_level_menu2[ekran_before];

      ekran_before = previous_level_in_current_level_menu2[ekran_before];
      if (ekran_before == EDITOR_LIST_LOGICAL_NODES_FOR_INPUT_MENU2_LEVEL)
      {
        number_logical_node = 1;
        type_logical_node = ID_FB_CONTROL_BLOCK;
      }
      else if (
               (ekran_before >= __BEGIN_EDITOR_LIST_SELECTED_TYPE_LOGICAL_NODE_FOR_INPUT_MENU2_LEVEL) &&
               (ekran_before <  __NEXT_AFTER_EDITOR_LIST_SELECTED_TYPE_LOGICAL_NODE_FOR_INPUT_MENU2_LEVEL)
              )   
      {
        number_logical_node = current_state_menu2.number_selection + 1; /*1 додаємо, індексація починається з нуля, а позначення у param  має іти з 1*/
    
        ekran_before = previous_level_in_current_level_menu2[ekran_before];
        if (ekran_before == EDITOR_LIST_LOGICAL_NODES_FOR_INPUT_MENU2_LEVEL)
        {
          type_logical_node = position_in_current_level_menu2[ekran_before] + _ID_FB_FIRST_ALL;
        }
      }
      else error = true;
    }
    else error = true;

    size_t n_similar_input_signals;
    if (error == false) 
    {
      n_similar_input_signals = array_n_similar_input_signals[type_logical_node - _ID_FB_FIRST_ALL];
      if (n_similar_input_signals == 0) error = true;
    }

    if (error == false)
    {
      uint32_t *p_param;
      switch (type_logical_node)
      {
      case ID_FB_CONTROL_BLOCK:
        {
          __SETTINGS_FIX *p_settings_fix = (current_state_menu2.edition == ED_VIEWING) ? &settings_fix_prt : &settings_fix;
          p_param = &p_settings_fix->param[index];
          break;
        }
      case ID_FB_AND:
        {
          if (current_state_menu2.edition == ED_VIEWING)
          {
            p_param = &(((__LN_AND*)spca_of_p_prt[ID_FB_AND - _ID_FB_FIRST_VAR] + (number_logical_node - 1))->settings.param[index*n_similar_input_signals]);
          }
          else
          {
            p_param = &(((__settings_for_AND*)sca_of_p[ID_FB_AND - _ID_FB_FIRST_VAR] + (number_logical_node - 1))->param[index*n_similar_input_signals]);
          }
            
          break;
        }
      case ID_FB_OR:
        {
          if (current_state_menu2.edition == ED_VIEWING)
          {
            p_param = &(((__LN_OR*)spca_of_p_prt[ID_FB_OR - _ID_FB_FIRST_VAR] + (number_logical_node - 1))->settings.param[index*n_similar_input_signals]);
          }
          else
          {
            p_param = &(((__settings_for_OR*)sca_of_p[ID_FB_OR - _ID_FB_FIRST_VAR] + (number_logical_node - 1))->param[index*n_similar_input_signals]);
          }
      
          break;
        }
      case ID_FB_XOR:
        {
          if (current_state_menu2.edition == ED_VIEWING)
          {
            p_param = &(((__LN_XOR*)spca_of_p_prt[ID_FB_XOR - _ID_FB_FIRST_VAR] + (number_logical_node - 1))->settings.param[index*n_similar_input_signals]);
          }
          else
          {
            p_param = &(((__settings_for_XOR*)sca_of_p[ID_FB_XOR - _ID_FB_FIRST_VAR] + (number_logical_node - 1))->param[index*n_similar_input_signals]);
          }
      
          break;
        }
      case ID_FB_EVENT_LOG:
        {
          if (current_state_menu2.edition == ED_VIEWING)
          {
            n_similar_input_signals *= current_config_prt.n_log;
            p_param = ((__LOG_INPUT*)spca_of_p_prt[ID_FB_EVENT_LOG - _ID_FB_FIRST_VAR]) + 1;
          }
          else
          {
            n_similar_input_signals *=current_config.n_log;
            p_param = ((__LOG_INPUT*)sca_of_p[ID_FB_EVENT_LOG - _ID_FB_FIRST_VAR]);
          }
            
          break;
        }
      default:
        {
          //Якщо сюди дійшла програма, значить відбулася недопустива помилка, тому треба зациклити програму, щоб вона пішла на перезагрузку
          total_error_sw_fixed(92);
        }
      }
      if (action & ((1 << BIT_REWRITE) | (1 << BIT_KEY_DOWN)))
      {
        if (action & (1 << BIT_KEY_DOWN)) current_state_menu2.index_position++;
        do
        {
          if(current_state_menu2.index_position >= max_row) current_state_menu2.index_position = 0;
          while (
                 (current_state_menu2.index_position != 0) &&
                 ((p_param[current_state_menu2.index_position] & (uint32_t)(~(MASKA_PARAM_INTERNAL_BITS << SFIFT_PARAM_INTERNAL_BITS))) == 0)
                )
          {
            if(++current_state_menu2.index_position >= max_row) current_state_menu2.index_position = 0;
          }
        }
        while ((action & (1 << BIT_KEY_DOWN)) && (current_state_menu2.index_position >= max_row));
      }
      else if (action & (1 << BIT_KEY_UP))
      {
        current_state_menu2.index_position--;
        do
        {
          if(current_state_menu2.index_position < 0) current_state_menu2.index_position = max_row - 1;
          while (
                 (current_state_menu2.index_position != 0) &&
                 ((p_param[current_state_menu2.index_position] & (uint32_t)(~(MASKA_PARAM_INTERNAL_BITS << SFIFT_PARAM_INTERNAL_BITS))) == 0)
                )
          {
            if(--current_state_menu2.index_position < 0) current_state_menu2.index_position = max_row - 1;
          }
        }
        while (current_state_menu2.index_position < 0);
      }
    }
    else current_state_menu2.index_position = 0;
  }
}
/*****************************************************/

/*****************************************************/
//Формуємо екран
/*****************************************************/
void make_ekran_editor_view_chosen_of_selected_logical_node(void)
{
  if (current_state_menu2.edition == ED_WARNING_EDITION_BUSY)
  {
    make_ekran_about_info(0, information_no_edition);
  }
  else
  {
    int index_language = index_language_in_array(select_struct_settings_fix()->language);
    unsigned int position_temp = current_state_menu2.index_position;
  
    unsigned int type_logical_node, number_logical_node;
    int index;
    size_t n_similar_input_signals;
    unsigned int error = false;

    enum _menu2_levels ekran_before = previous_level_in_current_level_menu2[current_state_menu2.current_level];
    if (ekran_before == EDITOR_LIST_LOGICAL_NODES_FOR_INPUT_MENU2_LEVEL)
    {
//      index = 0; //для даного випадку у цій змінній немає сенсу
//      number_logical_node = 1; //для даного випадку у цій змінній немає сенсу
      type_logical_node = ID_FB_EVENT_LOG;
    }
    else if (ekran_before == EDITOR_LIST_INPUTS_OF_SELECTED_LOGICAL_NODE_MENU2_LEVEL)
    {
      index = position_in_current_level_menu2[ekran_before];

      ekran_before = previous_level_in_current_level_menu2[ekran_before];
      if (ekran_before == EDITOR_LIST_LOGICAL_NODES_FOR_INPUT_MENU2_LEVEL)
      {
        number_logical_node = 1;
        type_logical_node = ID_FB_CONTROL_BLOCK;
      }
      else if (
               (ekran_before >= __BEGIN_EDITOR_LIST_SELECTED_TYPE_LOGICAL_NODE_FOR_INPUT_MENU2_LEVEL) &&
               (ekran_before <  __NEXT_AFTER_EDITOR_LIST_SELECTED_TYPE_LOGICAL_NODE_FOR_INPUT_MENU2_LEVEL)
              )   
      {
        number_logical_node = current_state_menu2.number_selection + 1; /*1 додаємо, індексація починається з нуля, а позначення у param  має іти з 1*/
    
        ekran_before = previous_level_in_current_level_menu2[ekran_before];
        if (ekran_before == EDITOR_LIST_LOGICAL_NODES_FOR_INPUT_MENU2_LEVEL)
        {
          type_logical_node = position_in_current_level_menu2[ekran_before] + _ID_FB_FIRST_ALL;
        }
      }
      else error = true;
    }
    else error = true;
  
    unsigned int max_row = current_state_menu2.max_row;
    if (error == false) 
    {
      n_similar_input_signals = array_n_similar_input_signals[type_logical_node - _ID_FB_FIRST_ALL];
      if (n_similar_input_signals == 0) error = true;
    }
    if (
        (error == false) &&
        (max_row != 0)
       )   
    {
      //Формуємо рядки  рядки у робочий екран
      uint32_t *p_param;
      switch (type_logical_node)
      {
      case ID_FB_CONTROL_BLOCK:
        {
          __SETTINGS_FIX *p_settings_fix = (current_state_menu2.edition == ED_VIEWING) ? &settings_fix_prt : &settings_fix;
          p_param = &p_settings_fix->param[index*n_similar_input_signals];
          break;
        }
      case ID_FB_OUTPUT:
      case ID_FB_LED:
        {
          if (current_state_menu2.edition == ED_VIEWING)
          {
            p_param = &(((__LN_OUTPUT_LED*)spca_of_p_prt[type_logical_node - _ID_FB_FIRST_VAR] + (number_logical_node - 1))->settings.param[index*n_similar_input_signals]);
          }
          else
          { 
            p_param = &(((__settings_for_OUTPUT_LED*)sca_of_p[type_logical_node - _ID_FB_FIRST_VAR] + (number_logical_node - 1))->param[index*n_similar_input_signals]);
          }
            
          break;
        }
      case ID_FB_ALARM:
        {
          if (current_state_menu2.edition == ED_VIEWING)
          {
            p_param = &(((__LN_ALARM*)spca_of_p_prt[ID_FB_ALARM - _ID_FB_FIRST_VAR] + (number_logical_node - 1))->settings.param[index*n_similar_input_signals]);
          }
          else
          {
            p_param = &(((__settings_for_ALARM*)sca_of_p[ID_FB_ALARM - _ID_FB_FIRST_VAR] + (number_logical_node - 1))->param[index*n_similar_input_signals]);
          }
            
          break;
        }
      case ID_FB_AND:
        {
          if (current_state_menu2.edition == ED_VIEWING)
          {
            p_param = &(((__LN_AND*)spca_of_p_prt[ID_FB_AND - _ID_FB_FIRST_VAR] + (number_logical_node - 1))->settings.param[index*n_similar_input_signals]);
          }
          else
          {
            p_param = &(((__settings_for_AND*)sca_of_p[ID_FB_AND - _ID_FB_FIRST_VAR] + (number_logical_node - 1))->param[index*n_similar_input_signals]);
          }
            
          break;
        }
      case ID_FB_OR:
        {
          if (current_state_menu2.edition == ED_VIEWING)
          {
            p_param = &(((__LN_OR*)spca_of_p_prt[ID_FB_OR - _ID_FB_FIRST_VAR] + (number_logical_node - 1))->settings.param[index*n_similar_input_signals]);
          }
          else
          {
            p_param = &(((__settings_for_OR*)sca_of_p[ID_FB_OR - _ID_FB_FIRST_VAR] + (number_logical_node - 1))->param[index*n_similar_input_signals]);
          }
            
          break;
        }
      case ID_FB_XOR:
        {
          if (current_state_menu2.edition == ED_VIEWING)
          {
            p_param = &(((__LN_XOR*)spca_of_p_prt[ID_FB_XOR - _ID_FB_FIRST_VAR] + (number_logical_node - 1))->settings.param[index*n_similar_input_signals]);
          }
          else
          {
            p_param = &(((__settings_for_XOR*)sca_of_p[ID_FB_XOR - _ID_FB_FIRST_VAR] + (number_logical_node - 1))->param[index*n_similar_input_signals]);
          }
            
          break;
        }
      case ID_FB_NOT:
        {
          if (current_state_menu2.edition == ED_VIEWING)
          {
            p_param = &(((__LN_NOT*)spca_of_p_prt[ID_FB_NOT - _ID_FB_FIRST_VAR] + (number_logical_node - 1))->settings.param[index*n_similar_input_signals]);
          }
          else
          {
            p_param = &(((__settings_for_NOT*)sca_of_p[ID_FB_NOT - _ID_FB_FIRST_VAR] + (number_logical_node - 1))->param[index*n_similar_input_signals]);
          }
            
          break;
        }
       case ID_FB_TIMER:
        {
          if (current_state_menu2.edition == ED_VIEWING)
          {
            p_param = &(((__LN_TIMER*)spca_of_p_prt[ID_FB_TIMER - _ID_FB_FIRST_VAR] + (number_logical_node - 1))->settings.param[index]);
          }
          else
          {
            p_param = &(((__settings_for_TIMER*)sca_of_p[ID_FB_TIMER - _ID_FB_FIRST_VAR] + (number_logical_node - 1))->param[index]);
          }
          
          break;
        }
      case ID_FB_TRIGGER:
        {
          if (current_state_menu2.edition == ED_VIEWING)
          {
            p_param = &(((__LN_TRIGGER*)spca_of_p_prt[ID_FB_TRIGGER - _ID_FB_FIRST_VAR] + (number_logical_node - 1))->settings.param[index]);
          }
          else
          {
            p_param = &(((__settings_for_TRIGGER*)sca_of_p[ID_FB_TRIGGER - _ID_FB_FIRST_VAR] + (number_logical_node - 1))->param[index]);
          }
          
          break;
        }
      case ID_FB_TU:
        {
          if (current_state_menu2.edition == ED_VIEWING)
          {
            p_param = &(((__LN_TU*)spca_of_p_prt[ID_FB_TU - _ID_FB_FIRST_VAR] + (number_logical_node - 1))->settings.param[index]);
          }
          else
          {
            p_param = &(((__settings_for_TU*)sca_of_p[ID_FB_TU - _ID_FB_FIRST_VAR] + (number_logical_node - 1))->param[index]);
          }
          
          break;
        }
      case ID_FB_TS:
        {
          if (current_state_menu2.edition == ED_VIEWING)
          {
            p_param = &(((__LN_TS*)spca_of_p_prt[ID_FB_TS - _ID_FB_FIRST_VAR] + (number_logical_node - 1))->settings.param[index]);
          }
          else
          {
            p_param = &(((__settings_for_TS*)sca_of_p[ID_FB_TS - _ID_FB_FIRST_VAR] + (number_logical_node - 1))->param[index]);
          }
          
          break;
        }
      case ID_FB_INPUT_GOOSE_BLOCK:
        {
          if (current_state_menu2.edition == ED_VIEWING)
          {
            p_param = &(((__LN_INPUT_GOOSE_BLOCK*)spca_of_p_prt[ID_FB_INPUT_GOOSE_BLOCK - _ID_FB_FIRST_VAR] + (number_logical_node - 1))->settings.param[index*n_similar_input_signals]);
          }
          else
          {
            p_param = &(((__settings_for_INPUT_GOOSE_BLOCK*)sca_of_p[ID_FB_INPUT_GOOSE_BLOCK - _ID_FB_FIRST_VAR] + (number_logical_node - 1))->param[index*n_similar_input_signals]);
          }
            
          break;
        }
      case ID_FB_INPUT_MMS_BLOCK:
        {
          if (current_state_menu2.edition == ED_VIEWING)
          {
            p_param = &(((__LN_INPUT_MMS_BLOCK*)spca_of_p_prt[ID_FB_INPUT_MMS_BLOCK - _ID_FB_FIRST_VAR] + (number_logical_node - 1))->settings.param[index*n_similar_input_signals]);
          }
          else
          {
            p_param = &(((__settings_for_INPUT_MMS_BLOCK*)sca_of_p[ID_FB_INPUT_MMS_BLOCK - _ID_FB_FIRST_VAR] + (number_logical_node - 1))->param[index*n_similar_input_signals]);
          }
            
          break;
        }
      case ID_FB_NETWORK_OUTPUT_BLOCK:
        {
          if (current_state_menu2.edition == ED_VIEWING)
          {
            p_param = &(((__LN_NETWORK_OUTPUT_BLOCK*)spca_of_p_prt[ID_FB_NETWORK_OUTPUT_BLOCK - _ID_FB_FIRST_VAR] + (number_logical_node - 1))->settings.param[index*n_similar_input_signals]);
          }
          else
          {
            p_param = &(((__settings_for_NETWORK_OUTPUT_BLOCK*)sca_of_p[ID_FB_NETWORK_OUTPUT_BLOCK - _ID_FB_FIRST_VAR] + (number_logical_node - 1))->param[index*n_similar_input_signals]);
          }
            
          break;
        }
      case ID_FB_EVENT_LOG:
        {
          if (current_state_menu2.edition == ED_VIEWING)
          {
            n_similar_input_signals *= current_config_prt.n_log;
            p_param = ((__LOG_INPUT*)spca_of_p_prt[ID_FB_EVENT_LOG - _ID_FB_FIRST_VAR]) + 1;
          }
          else
          {
            n_similar_input_signals *= current_config.n_log;
            p_param = ((__LOG_INPUT*)sca_of_p[ID_FB_EVENT_LOG - _ID_FB_FIRST_VAR]);
          }
            
          break;
        }
      default:
        {
          //Якщо сюди дійшла програма, значить відбулася недопустива помилка, тому треба зациклити програму, щоб вона пішла на перезагрузку
          total_error_sw_fixed(10);
        }
      }
      
      unsigned   int index_in_ekran = (position_temp >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;
  
      for (size_t i = 0; i < MAX_ROW_LCD; i++)
      {
        //Шукаємо рядок, який треба відобразити
        while (
               (index_in_ekran != 0) &&
               (index_in_ekran < max_row) &&
               ((p_param[index_in_ekran] & (uint32_t)(~(MASKA_PARAM_INTERNAL_BITS << SFIFT_PARAM_INTERNAL_BITS))) == 0)
              )
        {
          index_in_ekran++;
        } 
          
        //Наступні рядки треба перевірити, чи їх требе відображати
        if (index_in_ekran < max_row)
        {
          uint32_t param = p_param[index_in_ekran] & (uint32_t)(~(MASKA_PARAM_INTERNAL_BITS << SFIFT_PARAM_INTERNAL_BITS));
          if (param != 0)
          {
            unsigned int id_input   = (param >> SFIFT_PARAM_ID ) & MASKA_PARAM_ID ;
            unsigned int n_input    = (param >> SFIFT_PARAM_N  ) & MASKA_PARAM_N  ;
            unsigned int out_input  = (param >> SFIFT_PARAM_OUT) & MASKA_PARAM_OUT;
        
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
            for (size_t j = 0; j < MAX_COL_LCD; j++) working_ekran[i][j] = information_empty[index_language][j];
            if (position_temp == index_in_ekran)
            {
              current_state_menu2.position_cursor_x = cursor_x_empty[index_language];
            }
          }
        }
        else
        {
          for (size_t j = 0; j < MAX_COL_LCD; j++) working_ekran[i][j] = ' ';
        }

        index_in_ekran++;
      }
    }
    else
    {
      //Цього при правильній роботі програми не мало б бути
      error = true;

      for (size_t i = 0; i < MAX_ROW_LCD; i++)
      {
        for (size_t j = 0; j < MAX_COL_LCD; j++) working_ekran[i][j] = (i == 0) ? information_error[index_language][j] : ' ';
      }
    }
  

    //Курсор по горизонталі відображається на першій позиції
    if (error != false) current_state_menu2.position_cursor_x = 0;
    //Відображення курору по вертикалі
    current_state_menu2.position_cursor_y = (error == false) ? (position_temp & (MAX_ROW_LCD - 1)) : 0;
    //Курсор видимий
    current_state_menu2.cursor_on = (error == false) ? 1 : 0;
    //Курсор не мигає
    current_state_menu2.cursor_blinking_on = 0;
  }
  //Обновити повністю весь екран
  current_state_menu2.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/

/*****************************************************/
//Формуємо екран
/*****************************************************/
void make_ekran_editor_edit_list_outputs_of_selected_logical_node(void)
{
  if (current_state_menu2.edition == ED_WARNING_ENTER)
  {
    make_ekran_about_info(0, information_about_info_1);
  }
  else
  {
    int index_language = index_language_in_array(select_struct_settings_fix()->language);
    unsigned int position_temp = current_state_menu2.index_position;
  
    unsigned int error = false;
    unsigned int type_logical_node_out, number_logical_node_out;

    enum _menu2_levels ekran_before = previous_level_in_current_level_menu2[current_state_menu2.current_level];
    if (ekran_before == EDITOR_LIST_LOGICAL_NODES_FOR_OUTPUT_MENU2_LEVEL)
    {
      number_logical_node_out = 1;
      if (position_in_current_level_menu2[ekran_before] == INDEX_EDITOR_LIST_LOGICAL_NODES_M2_CONTROL_BLOCK) type_logical_node_out = ID_FB_CONTROL_BLOCK;
      else type_logical_node_out = ID_FB_EVENT_LOG;
    }
    else if (
             (ekran_before >= __BEGIN_EDITOR_LIST_SELECTED_TYPE_LOGICAL_NODE_FOR_OUTPUT_MENU2_LEVEL) &&
             (ekran_before <  __NEXT_AFTER_EDITOR_LIST_SELECTED_TYPE_LOGICAL_NODE_FOR_OUTPUT_MENU2_LEVEL)
            )   
    {
      number_logical_node_out = position_in_current_level_menu2[ekran_before] + 1; /*1 додаємо, індексація починається з нуля, а позначення у param  має іти з 1*/
    
      ekran_before = previous_level_in_current_level_menu2[ekran_before];
      if (ekran_before == EDITOR_LIST_LOGICAL_NODES_FOR_OUTPUT_MENU2_LEVEL)
      {
        type_logical_node_out = position_in_current_level_menu2[ekran_before] + _ID_FB_FIRST_ALL;
      }
      else error = true;
    }
    else error = true;
  
    unsigned int max_row = current_state_menu2.max_row;
    unsigned int type_logical_node_in, number_logical_node_in;
    int index_in;
    size_t n_similar_input_signals;
    uint32_t *p_param;

    if (
        (error == false) &&
        (max_row != 0) &&
        (array_p_name_out[type_logical_node_out - _ID_FB_FIRST_ALL] != NULL)
       )   
    {
      //Шукаємо тепер вхідну інформацію
      /*
                                                                 1-е повернення                                                  2-е повернення                                  3-повернення  
      EDITOR_LIST_LOGICAL_NODES_FOR_OUTPUT_MENU2_LEVEL->EDITOR_VIEW_CHOSEN_SIGNAL_OF_SELECTED_LOGICAL_NODE_MENU2_LEVEL->EDITOR_LIST_INPUTS_OF_SELECTED_LOGICAL_NODE_MENU2_LEVEL->EDITOR_LIST_XXX_FOR_INPUT_MENU2_LEVEL->EDITOR_LIST_LOGICAL_NODES_FOR_INPUT_MENU2_LEVEL
                                                                                                                     |                                                        |
                                                                                                                     |                                                         ->EDITOR_LIST_LOGICAL_NODES_FOR_INPUT_MENU2_LEVEL (якщо був вибраний "Загальний блок")
                                                                                                                      ->EDITOR_LIST_LOGICAL_NODES_FOR_INPUT_MENU2_LEVEL (якщо вбув вибраний "Загальний блок")
      */
      ekran_before = previous_level_in_current_level_menu2[previous_level_in_current_level_menu2[ekran_before]];
      if (ekran_before == EDITOR_LIST_LOGICAL_NODES_FOR_INPUT_MENU2_LEVEL)
      {
//        index_in = 0; //для даного випадку у цій змінній немає сенсу
//        number_logical_node_in = 1; //для даного випадку у цій змінній немає сенсу
        type_logical_node_in = ID_FB_EVENT_LOG;
      }
      else if (ekran_before == EDITOR_LIST_INPUTS_OF_SELECTED_LOGICAL_NODE_MENU2_LEVEL)
      {
        index_in = position_in_current_level_menu2[ekran_before];
    
        ekran_before = previous_level_in_current_level_menu2[ekran_before];
        if (ekran_before == EDITOR_LIST_LOGICAL_NODES_FOR_INPUT_MENU2_LEVEL)
        {   
          number_logical_node_in = 1;
          type_logical_node_in = ID_FB_CONTROL_BLOCK;
        }
        else if (
                 (ekran_before >= __BEGIN_EDITOR_LIST_SELECTED_TYPE_LOGICAL_NODE_FOR_INPUT_MENU2_LEVEL) &&
                 (ekran_before <  __NEXT_AFTER_EDITOR_LIST_SELECTED_TYPE_LOGICAL_NODE_FOR_INPUT_MENU2_LEVEL)
                )   
        {
          number_logical_node_in = position_in_current_level_menu2[ekran_before] + 1; /*1 додаємо, індексація починається з нуля, а позначення у param  має іти з 1*/
    
          ekran_before = previous_level_in_current_level_menu2[ekran_before];
          if (ekran_before == EDITOR_LIST_LOGICAL_NODES_FOR_INPUT_MENU2_LEVEL)
          {
            type_logical_node_in = position_in_current_level_menu2[ekran_before] + _ID_FB_FIRST_ALL;
          }
          else error = true;
        }
        else error = true;
      }
      else error = true;
      
      if (error == false)
      {
        n_similar_input_signals = array_n_similar_input_signals[type_logical_node_in - _ID_FB_FIRST_ALL];
        if (n_similar_input_signals != 0) 
        {
          switch (type_logical_node_in)
          {
          case ID_FB_CONTROL_BLOCK:
            {
              p_param = &settings_fix_edit.param[index_in*n_similar_input_signals];
              break;
            }
          case ID_FB_OUTPUT:
          case ID_FB_LED:
            {
              p_param = &(((__settings_for_OUTPUT_LED*)sca_of_p_edit[type_logical_node_in - _ID_FB_FIRST_VAR] + (number_logical_node_in - 1))->param[index_in*n_similar_input_signals]);
              break;
            }
          case ID_FB_ALARM:
            {
              p_param = &(((__settings_for_ALARM*)sca_of_p_edit[ID_FB_ALARM - _ID_FB_FIRST_VAR] + (number_logical_node_in - 1))->param[index_in*n_similar_input_signals]);
              break;
            }
          case ID_FB_AND:
            {
              p_param = &(((__settings_for_AND*)sca_of_p_edit[ID_FB_AND - _ID_FB_FIRST_VAR] + (number_logical_node_in - 1))->param[index_in*n_similar_input_signals]);
              break;
            }
          case ID_FB_OR:
            {
              p_param = &(((__settings_for_OR*)sca_of_p_edit[ID_FB_OR - _ID_FB_FIRST_VAR] + (number_logical_node_in - 1))->param[index_in*n_similar_input_signals]);
              break;
            }
          case ID_FB_XOR:
            {
              p_param = &(((__settings_for_XOR*)sca_of_p_edit[ID_FB_XOR - _ID_FB_FIRST_VAR] + (number_logical_node_in - 1))->param[index_in*n_similar_input_signals]);
              break;
            }
          case ID_FB_NOT:
            {
              p_param = &(((__settings_for_NOT*)sca_of_p_edit[ID_FB_NOT - _ID_FB_FIRST_VAR] + (number_logical_node_in - 1))->param[index_in*n_similar_input_signals]);
              break;
            }
           case ID_FB_TIMER:
            {
              p_param = &(((__settings_for_TIMER*)sca_of_p_edit[ID_FB_TIMER - _ID_FB_FIRST_VAR] + (number_logical_node_in - 1))->param[index_in*n_similar_input_signals]);
              break;
            }
          case ID_FB_TRIGGER:
            {
              p_param = &(((__settings_for_TRIGGER*)sca_of_p_edit[ID_FB_TRIGGER - _ID_FB_FIRST_VAR] + (number_logical_node_in - 1))->param[index_in*n_similar_input_signals]);
              break;
            }
          case ID_FB_TU:
            {
              p_param = &(((__settings_for_TU*)sca_of_p_edit[ID_FB_TU - _ID_FB_FIRST_VAR] + (number_logical_node_in - 1))->param[index_in*n_similar_input_signals]);
              break;
            }
          case ID_FB_TS:
            {
              p_param = &(((__settings_for_TS*)sca_of_p_edit[ID_FB_TS - _ID_FB_FIRST_VAR] + (number_logical_node_in - 1))->param[index_in*n_similar_input_signals]);
              break;
            }
          case ID_FB_INPUT_GOOSE_BLOCK:
            {
              p_param = &(((__settings_for_INPUT_GOOSE_BLOCK*)sca_of_p_edit[ID_FB_INPUT_GOOSE_BLOCK - _ID_FB_FIRST_VAR] + (number_logical_node_in - 1))->param[index_in*n_similar_input_signals]);
              break;
            }
          case ID_FB_INPUT_MMS_BLOCK:
            {
              p_param = &(((__settings_for_INPUT_MMS_BLOCK*)sca_of_p_edit[ID_FB_INPUT_MMS_BLOCK - _ID_FB_FIRST_VAR] + (number_logical_node_in - 1))->param[index_in*n_similar_input_signals]);
              break;
            }
          case ID_FB_NETWORK_OUTPUT_BLOCK:
            {
              p_param = &(((__settings_for_NETWORK_OUTPUT_BLOCK*)sca_of_p_edit[ID_FB_NETWORK_OUTPUT_BLOCK - _ID_FB_FIRST_VAR] + (number_logical_node_in - 1))->param[index_in*n_similar_input_signals]);
              break;
            }
          case ID_FB_EVENT_LOG:
            {
              n_similar_input_signals *= current_config_edit.n_log;
              p_param = ((__LOG_INPUT*)sca_of_p_edit[ID_FB_EVENT_LOG - _ID_FB_FIRST_VAR]);
            
              break;
            }
          default:
            {
              //Якщо сюди дійшла програма, значить відбулася недопустива помилка, тому треба зациклити програму, щоб вона пішла на перезагрузку
              total_error_sw_fixed(110);
            }
          }
        }
        else error = true;
      }
    }
    else error = true;
    
    if (error == false)
    {
      unsigned int index_in_ekran = ((position_temp << 1) >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;
  
      //Формуємо рядки  рядки у робочий екран
      for (size_t i = 0; i < MAX_ROW_LCD; i++)
      {
        unsigned int index_in_ekran_tmp = index_in_ekran >> 1;
        //Наступні рядки треба перевірити, чи їх требе відображати
        if (index_in_ekran_tmp < max_row)
        {
          if ((i & 0x1) == 0)
          {
            //У непарному номері рядку виводимо заголовок
            unsigned int part = 0;
            
            uint8_t *p = ((uint8_t*)array_p_name_out[type_logical_node_out - _ID_FB_FIRST_ALL]) + (index_language*max_row + index_in_ekran_tmp)*(MAX_COL_LCD + 1);
            unsigned int number_digit, first_index_number;
            
            unsigned int number_logical_node_tmp;
            if (
                (type_logical_node_out == ID_FB_BUTTON) &&
                ((number_logical_node_out - 1) >= NUMBER_FIX_BUTTONS)  
               )
            {
              number_logical_node_tmp = number_logical_node_out - NUMBER_FIX_BUTTONS;
            }
            else number_logical_node_tmp = number_logical_node_out;
            
            intptr_t k = 0, l = 0, m = 0;
            for (size_t j = 0; j < MAX_COL_LCD; j++) 
            {
              switch (part)
              {
              case 0:
                {
                  uint8_t symbol;
                  if (
                      (type_logical_node_out == ID_FB_BUTTON) &&
                      ((number_logical_node_out - 1) < NUMBER_FIX_BUTTONS)  
                     )
                  {
                    symbol = name_fix_buttons[number_logical_node_out - 1][j];
                  }
                  else
                  {
                    symbol = name_f_blocks[index_language][type_logical_node_out - _ID_FB_FIRST_ALL][k];
                  }
             
                  if (symbol != ' ') 
                  {
                    working_ekran[i][j] = symbol;
                    k++;
                
                    break;
                  }
                  else 
                  {
                    if (type_logical_node_out == ID_FB_CONTROL_BLOCK) part += 2;
                    else 
                    {
                      if (
                          (
                           (type_logical_node_out == ID_FB_BUTTON) &&
                           ((number_logical_node_out - 1) < NUMBER_FIX_BUTTONS)  
                          )   
                          ||
                          (
                           (type_logical_node_out == ID_FB_EVENT_LOG)
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
                    l += k;
                    k = 0;
                  }
                }
              case 1:
                {
                  if (part == 1)
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
                      k++;
                    }
                    else
                    {
                      working_ekran[i][j] = '.';
                      part++;
                      l += (++k);
                      k = 0;
                    }
              
                    break;
                  }
                }
              default:
                {
                  uint8_t symbol = *(p + k++);
                  working_ekran[i][j] = symbol;
                  if (symbol != ' ') m = k;
                  break;
                }
              }
            }
            l += m;
            
            //Виводимо напис на середину
            k = MAX_COL_LCD - l;
            if (k > 0)
            {
              m = (k >> 1) + ((k & 0x1) != 0);
              for (intptr_t j = m; j < MAX_COL_LCD; j++)
              {
                if ((j - m) < l)
                {
                  working_ekran[i][MAX_COL_LCD - 1 - j] = working_ekran[i][MAX_COL_LCD - 1 - k++];
                }
                else
                {
                  working_ekran[i][MAX_COL_LCD - 1 - j] = ' ';
                }
              }
            }
          }
          else
          {
            //Шукаємо, чи сигнал на який вказаний курсор  налаштований як віхдний для вибраного функцонального блоку
            unsigned int present = false;
            for (size_t j = 0; j < n_similar_input_signals; j++)
            {
              uint32_t param = p_param[j] & (uint32_t)(~(MASKA_PARAM_INTERNAL_BITS << SFIFT_PARAM_INTERNAL_BITS));
              if (param != 0)
              {
                if (((param >> SFIFT_PARAM_ID ) & MASKA_PARAM_ID ) != type_logical_node_out   ) continue;
                
                if (type_logical_node_out != ID_FB_CONTROL_BLOCK)
                {
                  if (((param >> SFIFT_PARAM_N  ) & MASKA_PARAM_N  ) != number_logical_node_out ) continue;
                }
                
                if (((param >> SFIFT_PARAM_OUT) & MASKA_PARAM_OUT) != (index_in_ekran_tmp + 1)) continue;
                
                //Якщо у цьому місці виконується програма, то значить, що співпадіння зафіксоване
                present = true;
                break;
              }
            }
          
            for (size_t j = 0; j < MAX_COL_LCD; j++) working_ekran[i][j] = information_on_off[index_language][present][j];
            if (position_temp == index_in_ekran_tmp)
            {
              current_state_menu2.position_cursor_x = cursor_x_on_off[index_language][present];
            }
          }
        }
        else
        {
          for (size_t j = 0; j < MAX_COL_LCD; j++) working_ekran[i][j] = ' ';
        }

        index_in_ekran++;
      }
    }
    else
    {
      //Цього при правильній роботі програми не мало б бути
      for (size_t i = 0; i < MAX_ROW_LCD; i++)
      {
        for (size_t j = 0; j < MAX_COL_LCD; j++) working_ekran[i][j] = (i == 0) ? information_error[index_language][j] : ' ';
      }
    }

    //Курсор по горизонталі відображається на першій позиції
    if (error != false) current_state_menu2.position_cursor_x = 0;
    //Відображення курору по вертикалі
    current_state_menu2.position_cursor_y = (error == false) ? (((position_temp << 1) + 1) & (MAX_ROW_LCD - 1)) : 0;
    //Курсор видимий
    current_state_menu2.cursor_on = (error == false) ? 1 : 0;
    //Курсор не мигає або мигає (взагалі, це вікно мабо б відображатися тільки у режимі редагування)
    if(current_state_menu2.edition <= ED_CAN_BE_EDITED) current_state_menu2.cursor_blinking_on = 0;
    else current_state_menu2.cursor_blinking_on = 1;
  }
  //Обновити повністю весь екран
  current_state_menu2.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/

/*****************************************************/
//Зміна налаштувань бінарної інформації для виходів/світлоіндикаторів
/*****************************************************
Вхідні параметри
(1 << BIT_KEY_RIGHT)- натснуто кнопку праворуч
(1 << BIT_KEY_LEFT) - атиснуто кнопку ліворуч

Вхідні параметри
  Немає
*****************************************************/
void change_set_signal(unsigned int action)
{
  unsigned int error = false;
  unsigned int type_logical_node_out, number_logical_node_out;

  enum _menu2_levels ekran_before = previous_level_in_current_level_menu2[current_state_menu2.current_level];
  if (ekran_before == EDITOR_LIST_LOGICAL_NODES_FOR_OUTPUT_MENU2_LEVEL)
  {
    number_logical_node_out = 1;
    if (position_in_current_level_menu2[ekran_before] == INDEX_EDITOR_LIST_LOGICAL_NODES_M2_CONTROL_BLOCK) type_logical_node_out = ID_FB_CONTROL_BLOCK;
    else type_logical_node_out = ID_FB_EVENT_LOG;
  }
  else if (
           (ekran_before >= __BEGIN_EDITOR_LIST_SELECTED_TYPE_LOGICAL_NODE_FOR_OUTPUT_MENU2_LEVEL) &&
           (ekran_before <  __NEXT_AFTER_EDITOR_LIST_SELECTED_TYPE_LOGICAL_NODE_FOR_OUTPUT_MENU2_LEVEL)
          )   
  {
    number_logical_node_out = position_in_current_level_menu2[ekran_before] + 1; /*1 додаємо, індексація починається з нуля, а позначення у param  має іти з 1*/
    
    ekran_before = previous_level_in_current_level_menu2[ekran_before];
    if (ekran_before == EDITOR_LIST_LOGICAL_NODES_FOR_OUTPUT_MENU2_LEVEL)
    {
      type_logical_node_out = position_in_current_level_menu2[ekran_before] + _ID_FB_FIRST_ALL;
    }
    else error = true;
  }
  else error = true;
  
  unsigned int type_logical_node_in, number_logical_node_in;
  int index_in;
  size_t n_similar_input_signals;
  uint32_t *p_param;

  if (error == false)
  {
    //Шукаємо тепер вхідну інформацію
    /*
                                                               1-е повернення                                                  2-е повернення                                  3-повернення  
    EDITOR_LIST_LOGICAL_NODES_FOR_OUTPUT_MENU2_LEVEL->EDITOR_VIEW_CHOSEN_SIGNAL_OF_SELECTED_LOGICAL_NODE_MENU2_LEVEL->EDITOR_LIST_INPUTS_OF_SELECTED_LOGICAL_NODE_MENU2_LEVEL->EDITOR_LIST_XXX_FOR_INPUT_MENU2_LEVEL->EDITOR_LIST_LOGICAL_NODES_FOR_INPUT_MENU2_LEVEL
                                                                                                                    |                                                        |
                                                                                                                    |                                                         ->EDITOR_LIST_LOGICAL_NODES_FOR_INPUT_MENU2_LEVEL (якщо був вибраний "Загальний блок")
                                                                                                                     ->EDITOR_LIST_LOGICAL_NODES_FOR_INPUT_MENU2_LEVEL (якщо вбув вибраний "Загальний блок")
    */
    ekran_before = previous_level_in_current_level_menu2[previous_level_in_current_level_menu2[ekran_before]];
    if (ekran_before == EDITOR_LIST_LOGICAL_NODES_FOR_INPUT_MENU2_LEVEL)
    {
//      index_in = 0; //для даного випадку у цій змінній немає сенсу
//      number_logical_node_in = 1; //для даного випадку у цій змінній немає сенсу
      type_logical_node_in = ID_FB_EVENT_LOG;
    }
    else if (ekran_before == EDITOR_LIST_INPUTS_OF_SELECTED_LOGICAL_NODE_MENU2_LEVEL)
    {
      index_in = position_in_current_level_menu2[ekran_before];
    
      ekran_before = previous_level_in_current_level_menu2[ekran_before];
      if (ekran_before == EDITOR_LIST_LOGICAL_NODES_FOR_INPUT_MENU2_LEVEL)
      {   
        number_logical_node_in = 1;
        type_logical_node_in = ID_FB_CONTROL_BLOCK;
      }
      else if (
               (ekran_before >= __BEGIN_EDITOR_LIST_SELECTED_TYPE_LOGICAL_NODE_FOR_INPUT_MENU2_LEVEL) &&
               (ekran_before <  __NEXT_AFTER_EDITOR_LIST_SELECTED_TYPE_LOGICAL_NODE_FOR_INPUT_MENU2_LEVEL)
              )   
      {
        number_logical_node_in = position_in_current_level_menu2[ekran_before] + 1; /*1 додаємо, індексація починається з нуля, а позначення у param  має іти з 1*/
  
        ekran_before = previous_level_in_current_level_menu2[ekran_before];
        if (ekran_before == EDITOR_LIST_LOGICAL_NODES_FOR_INPUT_MENU2_LEVEL)
        {
          type_logical_node_in = position_in_current_level_menu2[ekran_before] + _ID_FB_FIRST_ALL;
        }
        else error = true;
      }
      else error = true;
    }
    else error = true;
      
    if (error == false)
    {
      n_similar_input_signals = array_n_similar_input_signals[type_logical_node_in - _ID_FB_FIRST_ALL];
      if (n_similar_input_signals != 0) 
      {
        switch (type_logical_node_in)
        {
        case ID_FB_CONTROL_BLOCK:
          {
            p_param = &settings_fix_edit.param[index_in*n_similar_input_signals];
            break;
          }
        case ID_FB_OUTPUT:
        case ID_FB_LED:
          {
            p_param = &(((__settings_for_OUTPUT_LED*)sca_of_p_edit[type_logical_node_in - _ID_FB_FIRST_VAR] + (number_logical_node_in - 1))->param[index_in*n_similar_input_signals]);
            break;
          }
        case ID_FB_ALARM:
          {
            p_param = &(((__settings_for_ALARM*)sca_of_p_edit[ID_FB_ALARM - _ID_FB_FIRST_VAR] + (number_logical_node_in - 1))->param[index_in*n_similar_input_signals]);
            break;
          }
        case ID_FB_AND:
          {
            p_param = &(((__settings_for_AND*)sca_of_p_edit[ID_FB_AND - _ID_FB_FIRST_VAR] + (number_logical_node_in - 1))->param[index_in*n_similar_input_signals]);
            break;
          }
        case ID_FB_OR:
          {
            p_param = &(((__settings_for_OR*)sca_of_p_edit[ID_FB_OR - _ID_FB_FIRST_VAR] + (number_logical_node_in - 1))->param[index_in*n_similar_input_signals]);
            break;
          }
        case ID_FB_XOR:
          {
            p_param = &(((__settings_for_XOR*)sca_of_p_edit[ID_FB_XOR - _ID_FB_FIRST_VAR] + (number_logical_node_in - 1))->param[index_in*n_similar_input_signals]);
            break;
          }
        case ID_FB_NOT:
          {
            p_param = &(((__settings_for_NOT*)sca_of_p_edit[ID_FB_NOT - _ID_FB_FIRST_VAR] + (number_logical_node_in - 1))->param[index_in*n_similar_input_signals]);
            break;
          }
         case ID_FB_TIMER:
          {
            p_param = &(((__settings_for_TIMER*)sca_of_p_edit[ID_FB_TIMER - _ID_FB_FIRST_VAR] + (number_logical_node_in - 1))->param[index_in*n_similar_input_signals]);
            break;
          }
        case ID_FB_TRIGGER:
          {
            p_param = &(((__settings_for_TRIGGER*)sca_of_p_edit[ID_FB_TRIGGER - _ID_FB_FIRST_VAR] + (number_logical_node_in - 1))->param[index_in*n_similar_input_signals]);
            break;
          }
        case ID_FB_TU:
          {
            p_param = &(((__settings_for_TU*)sca_of_p_edit[ID_FB_TU - _ID_FB_FIRST_VAR] + (number_logical_node_in - 1))->param[index_in*n_similar_input_signals]);
            break;
          }
        case ID_FB_TS:
          {
            p_param = &(((__settings_for_TS*)sca_of_p_edit[ID_FB_TS - _ID_FB_FIRST_VAR] + (number_logical_node_in - 1))->param[index_in*n_similar_input_signals]);
            break;
          }
        case ID_FB_INPUT_GOOSE_BLOCK:
          {
            p_param = &(((__settings_for_INPUT_GOOSE_BLOCK*)sca_of_p_edit[ID_FB_INPUT_GOOSE_BLOCK - _ID_FB_FIRST_VAR] + (number_logical_node_in - 1))->param[index_in*n_similar_input_signals]);
            break;
          }
        case ID_FB_INPUT_MMS_BLOCK:
          {
            p_param = &(((__settings_for_INPUT_MMS_BLOCK*)sca_of_p_edit[ID_FB_INPUT_MMS_BLOCK - _ID_FB_FIRST_VAR] + (number_logical_node_in - 1))->param[index_in*n_similar_input_signals]);
            break;
          }
        case ID_FB_NETWORK_OUTPUT_BLOCK:
          {
            p_param = &(((__settings_for_INPUT_MMS_BLOCK*)sca_of_p_edit[ID_FB_NETWORK_OUTPUT_BLOCK - _ID_FB_FIRST_VAR] + (number_logical_node_in - 1))->param[index_in*n_similar_input_signals]);
            break;
          }
        case ID_FB_EVENT_LOG:
          {
            n_similar_input_signals *= current_config_edit.n_log;
            p_param = ((__LOG_INPUT*)sca_of_p_edit[ID_FB_EVENT_LOG - _ID_FB_FIRST_VAR]);
            
            break;
          }
        default:
          {
            //Якщо сюди дійшла програма, значить відбулася недопустива помилка, тому треба зациклити програму, щоб вона пішла на перезагрузку
            total_error_sw_fixed(118);
          }
        }
      }
      else error = true;
    }
  }
   
  if (error == false)
  {
    if (
        ((action & (1 << BIT_KEY_LEFT )) != 0) ||
        ((action & (1 << BIT_KEY_RIGHT)) != 0)
       )   
    {
      unsigned int present = false;
      unsigned int index_position = current_state_menu2.index_position;
      for (size_t i = 0; i < n_similar_input_signals; i++)
      {
        uint32_t param = p_param[i] & (uint32_t)(~(MASKA_PARAM_INTERNAL_BITS << SFIFT_PARAM_INTERNAL_BITS));
        if (param != 0)
        {
          if (((param >> SFIFT_PARAM_ID ) & MASKA_PARAM_ID ) != type_logical_node_out  ) continue;

          if (type_logical_node_out != ID_FB_CONTROL_BLOCK)
          {
            if (((param >> SFIFT_PARAM_N  ) & MASKA_PARAM_N  ) != number_logical_node_out) continue;
          }
          
          if (((param >> SFIFT_PARAM_OUT) & MASKA_PARAM_OUT) != (index_position + 1)   ) continue;
          
          //Якщо у цьому місці виконується програма, то значить, що співпадіння зафіксоване
          present = true;

          /*Знімаємо цей сигнал Ввімк.->Вимк. і зсуваємо всі наступні, щоб не було пропусків*/
          size_t j = (i + 1);
          while (j < n_similar_input_signals)
          {     
            param =  p_param[j - 1] = p_param[j] & (uint32_t)(~(MASKA_PARAM_INTERNAL_BITS << SFIFT_PARAM_INTERNAL_BITS));
            if (param == 0) break;
            
            j++;
          }
          if (j == n_similar_input_signals) p_param[j - 1] = 0;

          break;
        }
      }
      
      if (present == false)
      {
        /*Пробуємо встановити цей сигнал Вимк.->Ввімк.*/
        size_t i = 0;
        while (
               ((p_param[i] & (uint32_t)(~(MASKA_PARAM_INTERNAL_BITS << SFIFT_PARAM_INTERNAL_BITS))) != 0) &&
               (i < n_similar_input_signals)
              )   
        {
          i++;
        }
        if (i < n_similar_input_signals)
        {
          p_param[i] = ((                                                  type_logical_node_out        & MASKA_PARAM_ID ) << SFIFT_PARAM_ID ) |
                       ((((type_logical_node_out != ID_FB_CONTROL_BLOCK) ? number_logical_node_out : 1) & MASKA_PARAM_N  ) << SFIFT_PARAM_N  ) |
                       ((                                                  (index_position + 1)         & MASKA_PARAM_OUT) << SFIFT_PARAM_OUT);
          
          
          //Пересортовуємо сигнали так, щоб  вони мали порядок прогрнозований (від меншого значення до більшого)
          for (size_t index_1 = 0; index_1 < n_similar_input_signals; index_1++)
          {
            uint32_t param_1;
//            do
//            {
              param_1 = p_param[index_1] & (uint32_t)(~(MASKA_PARAM_INTERNAL_BITS << SFIFT_PARAM_INTERNAL_BITS));
              for (size_t index_2 = (index_1 + 1); index_2 < n_similar_input_signals; index_2++)
              {
                uint32_t param_2 = p_param[index_2] & (uint32_t)(~(MASKA_PARAM_INTERNAL_BITS << SFIFT_PARAM_INTERNAL_BITS));
                if (
                    (param_2 != 0) &&
                    (
                     (param_1 > param_2) ||
                     (param_1 == 0) /*теоретично цього ніколи б не мало бути*/ 
                    )   
                   )  
                {
                  p_param[index_1] = param_2;
                  p_param[index_2] = param_1;
                  param_1 = param_2;/*v2*/
//                  break;
                }
              }
//            }
//            while (param_1 != (p_param[index_1] & (uint32_t)(~(MASKA_PARAM_INTERNAL_BITS << SFIFT_PARAM_INTERNAL_BITS))));
          }
        }
        else
        {
          //Перевищено допустиму кількість зафедених функцій
          current_state_menu2.edition = ED_WARNING_ENTER;
        }
      }
    }
  }
}
/*****************************************************/

/*****************************************************/
/*
Дії по  переходу на редагування сигналу, який заводиться на конкретний вхід функцонального елементу
*/
/*****************************************************/
void select_input_signal_ln(void)
{
  int position = position_in_current_level_menu2[EDITOR_VIEW_CHOSEN_SIGNAL_OF_SELECTED_LOGICAL_NODE_MENU2_LEVEL];
  enum _menu2_levels ekran_before = previous_level_in_current_level_menu2[EDITOR_VIEW_CHOSEN_SIGNAL_OF_SELECTED_LOGICAL_NODE_MENU2_LEVEL];
  
  int index = position_in_current_level_menu2[ekran_before];
  unsigned int number_logical_node;
  unsigned int type_logical_node;

  if (ekran_before == EDITOR_LIST_LOGICAL_NODES_FOR_INPUT_MENU2_LEVEL)
  {
//    number_logical_node = 1; //для даного випадку у цій змінній немає сенсу
    type_logical_node = ID_FB_EVENT_LOG;
  }
  else if ((ekran_before = previous_level_in_current_level_menu2[ekran_before]) == EDITOR_LIST_LOGICAL_NODES_FOR_INPUT_MENU2_LEVEL)
  {
    number_logical_node = 1;
    type_logical_node = ID_FB_CONTROL_BLOCK;
  }
  else if (
           (ekran_before >= __BEGIN_EDITOR_LIST_SELECTED_TYPE_LOGICAL_NODE_FOR_INPUT_MENU2_LEVEL) &&
           (ekran_before <  __NEXT_AFTER_EDITOR_LIST_SELECTED_TYPE_LOGICAL_NODE_FOR_INPUT_MENU2_LEVEL)
          )   
  {
    number_logical_node = position_in_current_level_menu2[ekran_before] + 1; /*1 додаємо, індексація починається з нуля, а позначення у param  має іти з 1*/
    
    ekran_before = previous_level_in_current_level_menu2[ekran_before];
    if (ekran_before == EDITOR_LIST_LOGICAL_NODES_FOR_INPUT_MENU2_LEVEL)
    {
      type_logical_node = _ID_FB_FIRST_ALL + position_in_current_level_menu2[ekran_before];
    }
  }

  if (ekran_before == EDITOR_LIST_LOGICAL_NODES_FOR_INPUT_MENU2_LEVEL)
  {
    size_t n_similar_input_signals = array_n_similar_input_signals[type_logical_node - _ID_FB_FIRST_ALL];
    if (n_similar_input_signals != 0)
    {
      uint32_t param;
      switch (type_logical_node)
      {
      case ID_FB_CONTROL_BLOCK:
        {
          param = settings_fix_edit.param[index*n_similar_input_signals + position];
          break;
        }
      case ID_FB_OUTPUT:
      case ID_FB_LED:
        {
          param = ((__settings_for_OUTPUT_LED*)sca_of_p_edit[type_logical_node - _ID_FB_FIRST_VAR] + (number_logical_node - 1))->param[index*n_similar_input_signals + position];
          break;
        }
      case ID_FB_ALARM:
        {
          param = ((__settings_for_ALARM*)sca_of_p_edit[ID_FB_ALARM - _ID_FB_FIRST_VAR] + (number_logical_node - 1))->param[index*n_similar_input_signals + position];
          break;
        }
      case ID_FB_AND:
        {
          param = ((__settings_for_AND*)sca_of_p_edit[ID_FB_AND - _ID_FB_FIRST_VAR] + (number_logical_node - 1))->param[index*n_similar_input_signals + position];
          break;
        }
      case ID_FB_OR:
        {
          param = ((__settings_for_OR*)sca_of_p_edit[ID_FB_OR - _ID_FB_FIRST_VAR] + (number_logical_node - 1))->param[index*n_similar_input_signals + position];
          break;
        }
      case ID_FB_XOR:
        {
          param = ((__settings_for_XOR*)sca_of_p_edit[ID_FB_XOR - _ID_FB_FIRST_VAR] + (number_logical_node - 1))->param[index*n_similar_input_signals + position];
          break;
        }
      case ID_FB_NOT:
        {
          param = ((__settings_for_NOT*)sca_of_p_edit[ID_FB_NOT - _ID_FB_FIRST_VAR] + (number_logical_node - 1))->param[index*n_similar_input_signals + position];
          break;
        }
      case ID_FB_TIMER:
        {
          param = ((__settings_for_TIMER*)sca_of_p_edit[ID_FB_TIMER - _ID_FB_FIRST_VAR] + (number_logical_node - 1))->param[index*n_similar_input_signals + position];
          break;
        }
      case ID_FB_TRIGGER:
        {
          param = ((__settings_for_TRIGGER*)sca_of_p_edit[ID_FB_TRIGGER - _ID_FB_FIRST_VAR] + (number_logical_node - 1))->param[index*n_similar_input_signals + position];
          break;
        }
      case ID_FB_TU:
        {
          param = ((__settings_for_TU*)sca_of_p_edit[ID_FB_TU - _ID_FB_FIRST_VAR] + (number_logical_node - 1))->param[index*n_similar_input_signals + position];
          break;
        }
      case ID_FB_TS:
        {
          param = ((__settings_for_TS*)sca_of_p_edit[ID_FB_TS - _ID_FB_FIRST_VAR] + (number_logical_node - 1))->param[index*n_similar_input_signals + position];
          break;
        }
      case ID_FB_INPUT_GOOSE_BLOCK:
        {
          param = ((__settings_for_INPUT_GOOSE_BLOCK*)sca_of_p_edit[ID_FB_INPUT_GOOSE_BLOCK - _ID_FB_FIRST_VAR] + (number_logical_node - 1))->param[index*n_similar_input_signals + position];
          break;
        }
      case ID_FB_INPUT_MMS_BLOCK:
        {
          param = ((__settings_for_INPUT_MMS_BLOCK*)sca_of_p_edit[ID_FB_INPUT_MMS_BLOCK - _ID_FB_FIRST_VAR] + (number_logical_node - 1))->param[index*n_similar_input_signals + position];
          break;
        }
      case ID_FB_NETWORK_OUTPUT_BLOCK:
        {
          param = ((__settings_for_NETWORK_OUTPUT_BLOCK*)sca_of_p_edit[ID_FB_NETWORK_OUTPUT_BLOCK - _ID_FB_FIRST_VAR] + (number_logical_node - 1))->param[index*n_similar_input_signals + position];
          break;
        }
      case ID_FB_EVENT_LOG:
        {
          n_similar_input_signals *= current_config_edit.n_log;
          param = (*((__LOG_INPUT*)sca_of_p_edit[ID_FB_EVENT_LOG - _ID_FB_FIRST_VAR] + position)) & (uint32_t)(~(MASKA_PARAM_INTERNAL_BITS << SFIFT_PARAM_INTERNAL_BITS));
            
          break;
        }
      default:
        {
          //Якщо сюди дійшла програма, значить відбулася недопустива помилка, тому треба зациклити програму, щоб вона пішла на перезагрузку
          total_error_sw_fixed(122);
        }
      }
    
      if (param != 0)
      {
        //До переходу у режим редагування був вибраний конкретний сигнал (а не була ситуація, коли ще жоден сигнал не був вибраним)
        unsigned int id_input   = (param >> SFIFT_PARAM_ID ) & MASKA_PARAM_ID ;
        unsigned int n_input    = (param >> SFIFT_PARAM_N  ) & MASKA_PARAM_N  ;
        unsigned int out_input  = (param >> SFIFT_PARAM_OUT) & MASKA_PARAM_OUT;
 
        current_state_menu2.current_level = EDITOR_LIST_OUTPUTS_OF_SELECTED_LOGICAL_NODE_MENU2_LEVEL;
        position_in_current_level_menu2[EDITOR_LIST_OUTPUTS_OF_SELECTED_LOGICAL_NODE_MENU2_LEVEL] = out_input - 1;
      
        if (
            (id_input == ID_FB_CONTROL_BLOCK) ||
            (id_input == ID_FB_EVENT_LOG)
           )   
        {
          previous_level_in_current_level_menu2[EDITOR_LIST_OUTPUTS_OF_SELECTED_LOGICAL_NODE_MENU2_LEVEL] = EDITOR_LIST_LOGICAL_NODES_FOR_OUTPUT_MENU2_LEVEL;
          if (id_input == ID_FB_CONTROL_BLOCK)
          {
            position_in_current_level_menu2[EDITOR_LIST_LOGICAL_NODES_FOR_OUTPUT_MENU2_LEVEL] = INDEX_EDITOR_LIST_LOGICAL_NODES_M2_CONTROL_BLOCK;
          }
          else
          {
            position_in_current_level_menu2[EDITOR_LIST_LOGICAL_NODES_FOR_OUTPUT_MENU2_LEVEL] = INDEX_EDITOR_LIST_LOGICAL_NODES_M2_LOG;
            current_state_menu2.number_selection = 0;
          }
        }
        else
        {
          enum _menu2_levels tmp = previous_level_in_current_level_menu2[EDITOR_LIST_OUTPUTS_OF_SELECTED_LOGICAL_NODE_MENU2_LEVEL] = levels_tmp[(id_input - 1) - 1];
          current_state_menu2.number_selection = position_in_current_level_menu2[tmp] = n_input - 1;
        
          previous_level_in_current_level_menu2[tmp] = EDITOR_LIST_LOGICAL_NODES_FOR_OUTPUT_MENU2_LEVEL;
          position_in_current_level_menu2[EDITOR_LIST_LOGICAL_NODES_FOR_OUTPUT_MENU2_LEVEL] = id_input - 1;
        }
      }
    }
  }
}
/*****************************************************/

/*****************************************************/
/*****************************************************/
//
/*****************************************************/
/*****************************************************/
