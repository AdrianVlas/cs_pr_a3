#include "header.h"

const uint8_t name_f_blocks[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_PARAM_LIST_LOGICAL_NODES][MAX_COL_LCD + 1] = 
{
  {
    "                ",
    " Д.Вх           ",
    " В.Р            ",
    " Св             ",
    " СЗС            ",
    " ШГС            ",
    " И              ",
    " ИЛИ            ",
    " И-ИЛИ          ",
    " НЕ             ",
    " МФТ            ",
    " D-Тр           ",
    " ГПС            "
  },
  {
    "                ",
    "Д.Вх            ",
    "В.Р             ",
    "Св              ",
    "СЗС             ",
    "ШГС             ",
    "І               ",
    "АБО             ",
    "В.АБО           ",
    "НЕ              ",
    "МФТ             ",
    "D-Тр            ",
    "ГПС             "
  },
  {
    "                ",
    "D.In            ",
    "O.R             ",
    "LED             ",
    "СЗС             ",
    "ШГС             ",
    "AND             ",
    "OR              ",
    "XOR             ",
    "NOT             ",
    "MFT             ",
    "D-Tr            ",
    "PSG             "
  },
  {
    "                ",
    "Д.Вх            ",
    "В.Р             ",
    "Св              ",
    "СЗС             ",
    "ШГС             ",
    "И               ",
    "ИЛИ             ",
    "И-ИЛИ           ",
    "НЕ              ",
    "МФТ             ",
    "D-Тр            ",
    "ГПС             "
  }
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
void move_into_param_list_logical_nodes(unsigned int action, int max_row)
{
  __CONFIG *p_config = (current_state_menu2.edition == ED_VIEWING) ? &current_config_prt : &current_config;
  unsigned int logical_node_shown[NUMBER_ALL_BLOCKS];
  if (current_state_menu2.current_level == PARAM_LIST_LOGICAL_NODES_FOR_INPUT_MENU2_LEVEL)
  {
    
    logical_node_shown[ 0] = (FIX_BLOCK_SIGNALS_IN > 0) ? true: false;
    logical_node_shown[ 1] = ((p_config->n_input*0                     ) != 0);
    logical_node_shown[ 2] = ((p_config->n_output*OUTPUT_LED_SIGNALS_IN) != 0);
    logical_node_shown[ 3] = ((p_config->n_led*OUTPUT_LED_SIGNALS_IN   ) != 0);
    logical_node_shown[ 4] = ((p_config->n_alarm*ALARM_SIGNALS_IN      ) != 0);
    logical_node_shown[ 5] = ((p_config->n_group_alarm*0               ) != 0);
    logical_node_shown[ 6] = ((p_config->n_and*AND_SIGNALS_IN          ) != 0);
    logical_node_shown[ 7] = ((p_config->n_or*OR_SIGNALS_IN            ) != 0);
    logical_node_shown[ 8] = ((p_config->n_xor*2                       ) != 0);
    logical_node_shown[ 9] = ((p_config->n_not*1                       ) != 0);
    logical_node_shown[10] = ((p_config->n_timer*TIMER_SIGNALS_IN      ) != 0);
    logical_node_shown[11] = ((p_config->n_trigger*TRIGGER_SIGNALS_IN  ) != 0);
    logical_node_shown[12] = ((p_config->n_meander*0                   ) != 0);
  }
  else
  {
    logical_node_shown[ 0] = (FIX_BLOCK_SIGNALS_OUT > 0) ? true: false;
    logical_node_shown[ 1] = ((p_config->n_input*INPUT_SIGNALS_OUT            ) != 0);
    logical_node_shown[ 2] = ((p_config->n_output*OUTPUT_LED_SIGNALS_OUT      ) != 0);
    logical_node_shown[ 3] = ((p_config->n_led*OUTPUT_LED_SIGNALS_OUT         ) != 0);
    logical_node_shown[ 4] = ((p_config->n_alarm*ALARM_SIGNALS_OUT            ) != 0);
    logical_node_shown[ 5] = ((p_config->n_group_alarm*GROUP_ALARM_SIGNALS_OUT) != 0);
    logical_node_shown[ 6] = ((p_config->n_and*STANDARD_LOGIC_SIGNALS_OUT     ) != 0);
    logical_node_shown[ 7] = ((p_config->n_or*STANDARD_LOGIC_SIGNALS_OUT      ) != 0);
    logical_node_shown[ 8] = ((p_config->n_xor*STANDARD_LOGIC_SIGNALS_OUT     ) != 0);
    logical_node_shown[ 9] = ((p_config->n_not*STANDARD_LOGIC_SIGNALS_OUT     ) != 0);
    logical_node_shown[10] = ((p_config->n_timer*TIMER_SIGNALS_OUT            ) != 0);
    logical_node_shown[11] = ((p_config->n_trigger*TRIGGER_SIGNALS_OUT        ) != 0);
    logical_node_shown[12] = ((p_config->n_meander*MEANDER_SIGNALS_OUT        ) != 0);
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
void make_ekran_param_list_logical_node(void)
{
  if (current_state_menu2.edition == ED_WARNING_EDITION_BUSY)
  {
    const uint8_t information_about_info[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
    {
      "Ред.не разрешено",
      "Ред.не дозволене",
      "Ed.isn't allowed",
      "Ред.не разрешено",
    };

    make_ekran_about_info(false, information_about_info);
  }
  else
  {
    __CONFIG *p_config = (current_state_menu2.edition == ED_VIEWING) ? &current_config_prt : &current_config;
    unsigned int logical_node_shown[NUMBER_ALL_BLOCKS];
    if (current_state_menu2.current_level == PARAM_LIST_LOGICAL_NODES_FOR_INPUT_MENU2_LEVEL)
    {
      logical_node_shown[ 0] = (FIX_BLOCK_SIGNALS_IN > 0) ? true: false;
      logical_node_shown[ 1] = ((p_config->n_input*0                     ) != 0);
      logical_node_shown[ 2] = ((p_config->n_output*OUTPUT_LED_SIGNALS_IN) != 0);
      logical_node_shown[ 3] = ((p_config->n_led*OUTPUT_LED_SIGNALS_IN   ) != 0);
      logical_node_shown[ 4] = ((p_config->n_alarm*ALARM_SIGNALS_IN      ) != 0);
      logical_node_shown[ 5] = ((p_config->n_group_alarm*0               ) != 0);
      logical_node_shown[ 6] = ((p_config->n_and*AND_SIGNALS_IN          ) != 0);
      logical_node_shown[ 7] = ((p_config->n_or*OR_SIGNALS_IN            ) != 0);
      logical_node_shown[ 8] = ((p_config->n_xor*2                       ) != 0);
      logical_node_shown[ 9] = ((p_config->n_not*1                       ) != 0);
      logical_node_shown[10] = ((p_config->n_timer*TIMER_SIGNALS_IN      ) != 0);
      logical_node_shown[11] = ((p_config->n_trigger*TRIGGER_SIGNALS_IN  ) != 0);
      logical_node_shown[12] = ((p_config->n_meander*0                   ) != 0);
    }     
    else
    {
      logical_node_shown[ 0] = (FIX_BLOCK_SIGNALS_OUT > 0) ? true: false;
      logical_node_shown[ 1] = ((p_config->n_input*INPUT_SIGNALS_OUT            ) != 0);
      logical_node_shown[ 2] = ((p_config->n_output*OUTPUT_LED_SIGNALS_OUT      ) != 0);
      logical_node_shown[ 3] = ((p_config->n_led*OUTPUT_LED_SIGNALS_OUT         ) != 0);
      logical_node_shown[ 4] = ((p_config->n_alarm*ALARM_SIGNALS_OUT            ) != 0);
      logical_node_shown[ 5] = ((p_config->n_group_alarm*GROUP_ALARM_SIGNALS_OUT) != 0);
      logical_node_shown[ 6] = ((p_config->n_and*STANDARD_LOGIC_SIGNALS_OUT     ) != 0);
      logical_node_shown[ 7] = ((p_config->n_or*STANDARD_LOGIC_SIGNALS_OUT      ) != 0);
      logical_node_shown[ 8] = ((p_config->n_xor*STANDARD_LOGIC_SIGNALS_OUT     ) != 0);
      logical_node_shown[ 9] = ((p_config->n_not*STANDARD_LOGIC_SIGNALS_OUT     ) != 0);
      logical_node_shown[10] = ((p_config->n_timer*TIMER_SIGNALS_OUT            ) != 0);
      logical_node_shown[11] = ((p_config->n_trigger*TRIGGER_SIGNALS_OUT        ) != 0);
      logical_node_shown[12] = ((p_config->n_meander*MEANDER_SIGNALS_OUT        ) != 0);
    };
  
    const uint8_t name_string[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_PARAM_LIST_LOGICAL_NODES][MAX_COL_LCD + 1] = 
    {
      {
        " Общий блок     ",
        " Д.Входы        ",
        " В.Реле         ",
        " Светоиндикаторы",
        " СЗС            ",
        " ШГС            ",
        " И              ",
        " ИЛИ            ",
        " Искл.ИЛИ       ",
        " НЕ             ",
        " МФ-Таймер      ",
        " D-Триггер      ",
        " ГПС            "
      },
      {
        " Загальний блок ",
        " Д.Входи        ",
        " В.Реле         ",
        " Світоіндикатори",
        " СЗС            ",
        " ШГС            ",
        " І              ",
        " АБО            ",
        " Викл.АБО       ",
        " НЕ             ",
        " МФ-Таймер      ",
        " D-Триґер       ",
        " ГПС            "
      },
      {
        " General block  ",
        " D.Inputs       ",
        " O.Relays       ",
        " LEDs           ",
        " СЗС            ",
        " ШГС            ",
        " AND            ",
        " OR             ",
        " XOR            ",
        " NOT            ",
        " MF-Timer       ",
        " D-Trigger      ",
        " PSG            "
      },
      {
        " Общий блок     ",
        " Д.Входы        ",
        " В.Реле         ",
        " Светоиндикаторы",
        " СЗС            ",
        " ШГС            ",
        " И              ",
        " ИЛИ            ",
        " Искл.ИЛИ       ",
        " НЕ             ",
        " МФ-Таймер      ",
        " D-Триггер      ",
        " ГПС            "
      }
    };
    int index_language = index_language_in_array(select_struct_settings_fix()->language);
  
    unsigned int additional_current = 0;
    unsigned int position_temp = current_state_menu2.index_position;

    uint8_t name_string_tmp[MAX_ROW_FOR_PARAM_LIST_LOGICAL_NODES][MAX_COL_LCD + 1];
    for(size_t index_1 = 0; index_1 < MAX_ROW_FOR_PARAM_LIST_LOGICAL_NODES; index_1++)
    {
      if (logical_node_shown[index_1] != true)
      {
        if ((index_1 - additional_current) < position_temp) position_temp--;
        additional_current++;

        for(size_t index_2 = 0; index_2 < MAX_COL_LCD; index_2++)
        {
          name_string_tmp[MAX_ROW_FOR_PARAM_LIST_LOGICAL_NODES - additional_current][index_2] = ' ';
        }
        name_string_tmp[MAX_ROW_FOR_PARAM_LIST_LOGICAL_NODES - additional_current][MAX_COL_LCD] = '\0';
      }
      else
      {
        for(size_t index_2 = 0; index_2 < (MAX_COL_LCD + 1); index_2++)
        {
          name_string_tmp[index_1 - additional_current][index_2] = name_string[index_language][index_1][index_2];
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
        working_ekran[i][j] = (index_in_ekran < (MAX_ROW_FOR_PARAM_LIST_LOGICAL_NODES - additional_current)) ? name_string_tmp[index_in_ekran][j] : ' ';
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
void make_ekran_param_list_inputs_of_selected_logical_node(void)
{
  if (current_state_menu2.edition == ED_WARNING_EDITION_BUSY)
  {
    const uint8_t information_about_info[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
    {
      "Ред.не разрешено",
      "Ред.не дозволене",
      "Ed.isn't allowed",
      "Ред.не разрешено",
    };

    make_ekran_about_info(false, information_about_info);
  }
  else
  {
    const uint8_t name_fix_block_in_signals[MAX_NAMBER_LANGUAGE][FIX_BLOCK_SIGNALS_IN][MAX_COL_LCD + 1] =
    {
      {NAME_FIX_BLOCK_IN_SIGNALS_RU},  
      {NAME_FIX_BLOCK_IN_SIGNALS_UA},  
      {NAME_FIX_BLOCK_IN_SIGNALS_EN},  
      {NAME_FIX_BLOCK_IN_SIGNALS_KZ}
    };
  
    const uint8_t name_output_led_in_signals[MAX_NAMBER_LANGUAGE][OUTPUT_LED_SIGNALS_IN][MAX_COL_LCD + 1] =
    {
      {NAME_OUTPUT_LED_IN_SIGNALS_RU},  
      {NAME_OUTPUT_LED_IN_SIGNALS_UA},  
      {NAME_OUTPUT_LED_IN_SIGNALS_EN},  
      {NAME_OUTPUT_LED_IN_SIGNALS_KZ}
    };
  
    const uint8_t name_alarm_in_signals[MAX_NAMBER_LANGUAGE][ALARM_SIGNALS_IN][MAX_COL_LCD + 1] =
    {
      {NAME_ALARM_IN_SIGNALS_RU},  
      {NAME_ALARM_IN_SIGNALS_UA},  
      {NAME_ALARM_IN_SIGNALS_EN},  
      {NAME_ALARM_IN_SIGNALS_KZ}
    };

    const uint8_t name_standard_logic_in_signals[MAX_NAMBER_LANGUAGE][1][MAX_COL_LCD + 1] =
    {
      {NAME_STANDARD_LOGIC_IN_SIGNALS_RU},  
      {NAME_STANDARD_LOGIC_IN_SIGNALS_UA},  
      {NAME_STANDARD_LOGIC_IN_SIGNALS_EN},  
      {NAME_STANDARD_LOGIC_IN_SIGNALS_KZ}
    };

    const uint8_t name_timer_in_signals[MAX_NAMBER_LANGUAGE][TIMER_SIGNALS_IN][MAX_COL_LCD + 1] =
    {
      {NAME_TIMER_IN_SIGNALS_RU},  
      {NAME_TIMER_IN_SIGNALS_UA},  
      {NAME_TIMER_IN_SIGNALS_EN},  
      {NAME_TIMER_IN_SIGNALS_KZ}
    };
  
    const uint8_t name_trigger_in_signals[MAX_NAMBER_LANGUAGE][TRIGGER_SIGNALS_IN][MAX_COL_LCD + 1] =
    {
      {NAME_TRIGGER_IN_SIGNALS_RU},  
      {NAME_TRIGGER_IN_SIGNALS_UA},  
      {NAME_TRIGGER_IN_SIGNALS_EN},  
      {NAME_TRIGGER_IN_SIGNALS_KZ}
    };

    const uint8_t * const array_p_name[NUMBER_ALL_BLOCKS] = 
    {
      (const uint8_t*)name_fix_block_in_signals, 
      NULL, 
      (const uint8_t*)name_output_led_in_signals, 
      (const uint8_t*)name_output_led_in_signals, 
      (const uint8_t*)name_alarm_in_signals, 
      NULL, 
      (const uint8_t*)name_standard_logic_in_signals, 
      (const uint8_t*)name_standard_logic_in_signals, 
      (const uint8_t*)name_standard_logic_in_signals, 
      (const uint8_t*)name_standard_logic_in_signals, 
      (const uint8_t*)name_timer_in_signals, 
      (const uint8_t*)name_trigger_in_signals, 
      NULL
    };
    int index_language = index_language_in_array(select_struct_settings_fix()->language);
    unsigned int position_temp = current_state_menu2.index_position;
  
    unsigned int type_logical_node, number_logical_node;

    enum _menu2_levels ekran_before = previous_level_in_current_level_menu2[current_state_menu2.current_level];
    if (ekran_before == PARAM_LIST_LOGICAL_NODES_FOR_INPUT_MENU2_LEVEL)
    {
      number_logical_node = 1;
      type_logical_node = ID_FB_CONTROL_BLOCK;
    }
    else if (
             (ekran_before >= __BEGIN_PARAM_LIST_SELECTED_TYPE_LOGICAL_NODE_MENU2_LEVEL) &&
             (ekran_before <  __NEXT_AFTER_PARAM_LIST_SELECTED_TYPE_LOGICAL_NODE_MENU2_LEVEL)
            )   
    {
      number_logical_node = current_state_menu2.number_selection + 1; /*1 додаємо, індексація починається з нуля, а позначення у param  має іти з 1*/
    
      ekran_before = previous_level_in_current_level_menu2[ekran_before];
      if (ekran_before == PARAM_LIST_LOGICAL_NODES_FOR_INPUT_MENU2_LEVEL)
      {
        type_logical_node = position_in_current_level_menu2[ekran_before] + _ID_FB_FIRST_ALL;
      }
    }
  
    unsigned int error = false;
    unsigned int max_row = current_state_menu2.max_row;
    if (
        (ekran_before == PARAM_LIST_LOGICAL_NODES_FOR_INPUT_MENU2_LEVEL) &&
        (max_row != 0) &&
        (array_p_name[type_logical_node - _ID_FB_FIRST_ALL] != NULL)
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
          uint8_t *p = ((uint8_t*)array_p_name[type_logical_node - _ID_FB_FIRST_ALL]) + (index_language*max_row + index_in_ekran)*(MAX_COL_LCD + 1);
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
      const uint8_t information_error[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
      {
        "     Ошибка     ",
        "    Помилка     ",
        "     Error      ",
        "     Ошибка     "
      };

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
Функція переміщення по меню

Вхідні параметри
(1 << BIT_REWRITE) - перемалювати меню
(1 << BIT_KEY_DOWN) - рухатися вниз
(1 << BIT_KEY_UP) - рухатися вверх
*/
/*****************************************************/
void move_into_param_view_chosen_of_selected_logical_node(unsigned int action, int max_row)
{
  if (max_row == 1) current_state_menu2.index_position = 0;
  else
  {
    unsigned int type_logical_node, number_logical_node;
    int index;

    unsigned int error = false;

    enum _menu2_levels ekran_before = previous_level_in_current_level_menu2[current_state_menu2.current_level];
    if (ekran_before == PARAM_LIST_INPUTS_OF_SELECTED_LOGICAL_NODE_MENU2_LEVEL)
    {
      index = position_in_current_level_menu2[ekran_before];

      ekran_before = previous_level_in_current_level_menu2[ekran_before];
      if (ekran_before == PARAM_LIST_LOGICAL_NODES_FOR_INPUT_MENU2_LEVEL)
      {
        number_logical_node = 1;
        type_logical_node = ID_FB_CONTROL_BLOCK;
      }
      else if (
               (ekran_before >= __BEGIN_PARAM_LIST_SELECTED_TYPE_LOGICAL_NODE_MENU2_LEVEL) &&
               (ekran_before <  __NEXT_AFTER_PARAM_LIST_SELECTED_TYPE_LOGICAL_NODE_MENU2_LEVEL)
              )   
      {
        number_logical_node = current_state_menu2.number_selection + 1; /*1 додаємо, індексація починається з нуля, а позначення у param  має іти з 1*/
    
        ekran_before = previous_level_in_current_level_menu2[ekran_before];
        if (ekran_before == PARAM_LIST_LOGICAL_NODES_FOR_INPUT_MENU2_LEVEL)
        {
          type_logical_node = position_in_current_level_menu2[ekran_before] + _ID_FB_FIRST_ALL;
        }
      }
      else error = true;
    }
    else error = true;

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
            p_param = ((__LN_AND*)spca_of_p_prt[ID_FB_AND - _ID_FB_FIRST_ALL] + (number_logical_node - 1))->settings.param;
          }
          else
          {
            p_param = ((__settings_for_AND*)spca_of_p_prt[ID_FB_AND - _ID_FB_FIRST_ALL] + (number_logical_node - 1))->param;
          }
            
          break;
        }
      case ID_FB_OR:
        {
          if (current_state_menu2.edition == ED_VIEWING)
          {
            p_param = ((__LN_OR*)spca_of_p_prt[ID_FB_OR - _ID_FB_FIRST_ALL] + (number_logical_node - 1))->settings.param;
          }
          else
          {
            p_param = ((__settings_for_OR*)spca_of_p_prt[ID_FB_OR - _ID_FB_FIRST_ALL] + (number_logical_node - 1))->param;
          }
      
          break;
        }
      case ID_FB_XOR:
        {
          if (current_state_menu2.edition == ED_VIEWING)
          {
            p_param = ((__LN_XOR*)spca_of_p_prt[ID_FB_XOR - _ID_FB_FIRST_ALL] + (number_logical_node - 1))->settings.param;
          }
          else
          {
            p_param = ((__settings_for_XOR*)spca_of_p_prt[ID_FB_XOR - _ID_FB_FIRST_ALL] + (number_logical_node - 1))->param;
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
                 (p_param[current_state_menu2.index_position] == 0)
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
                 (p_param[current_state_menu2.index_position] == 0)
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
void make_ekran_param_view_chosen_of_selected_logical_node(void)
{
  if (current_state_menu2.edition == ED_WARNING_EDITION_BUSY)
  {
    const uint8_t information_about_info[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
    {
      "Ред.не разрешено",
      "Ред.не дозволене",
      "Ed.isn't allowed",
      "Ред.не разрешено",
    };

    make_ekran_about_info(false, information_about_info);
  }
  else
  {
    const uint8_t name_fix_block_out_signals[MAX_NAMBER_LANGUAGE][FIX_BLOCK_SIGNALS_OUT][MAX_COL_LCD + 1] =
    {
      {NAME_FIX_BLOCK_OUT_SIGNALS_RU},  
      {NAME_FIX_BLOCK_OUT_SIGNALS_UA},  
      {NAME_FIX_BLOCK_OUT_SIGNALS_EN},  
      {NAME_FIX_BLOCK_OUT_SIGNALS_KZ}
    };
  
    const uint8_t name_input_out_signals[MAX_NAMBER_LANGUAGE][INPUT_SIGNALS_OUT][MAX_COL_LCD + 1] =
    {
      {NAME_INPUT_OUT_SIGNALS_RU},  
      {NAME_INPUT_OUT_SIGNALS_UA},  
      {NAME_INPUT_OUT_SIGNALS_EN},  
      {NAME_INPUT_OUT_SIGNALS_KZ}
    };
  
    const uint8_t name_output_led_out_signals[MAX_NAMBER_LANGUAGE][OUTPUT_LED_SIGNALS_OUT][MAX_COL_LCD + 1] =
    {
      {NAME_OUTPUT_LED_OUT_SIGNALS_RU},  
      {NAME_OUTPUT_LED_OUT_SIGNALS_UA},  
      {NAME_OUTPUT_LED_OUT_SIGNALS_EN},  
      {NAME_OUTPUT_LED_OUT_SIGNALS_KZ}
    };
  
    const uint8_t name_alarm_out_signals[MAX_NAMBER_LANGUAGE][ALARM_SIGNALS_OUT][MAX_COL_LCD + 1] =
    {
      {NAME_ALARM_OUT_SIGNALS_RU},  
      {NAME_ALARM_OUT_SIGNALS_UA},  
      {NAME_ALARM_OUT_SIGNALS_EN},  
      {NAME_ALARM_OUT_SIGNALS_KZ}
    };

    const uint8_t name_group_alarm_out_signals[MAX_NAMBER_LANGUAGE][GROUP_ALARM_SIGNALS_OUT][MAX_COL_LCD + 1] =
    {
      {NAME_GROUP_ALARM_OUT_SIGNALS_RU},  
      {NAME_GROUP_ALARM_OUT_SIGNALS_UA},  
      {NAME_GROUP_ALARM_OUT_SIGNALS_EN},  
      {NAME_GROUP_ALARM_OUT_SIGNALS_KZ}
    };

    const uint8_t name_standard_logic_out_signals[MAX_NAMBER_LANGUAGE][STANDARD_LOGIC_SIGNALS_OUT][MAX_COL_LCD + 1] =
    {
      {NAME_STANDARD_LOGIC_OUT_SIGNALS_RU},  
      {NAME_STANDARD_LOGIC_OUT_SIGNALS_UA},  
      {NAME_STANDARD_LOGIC_OUT_SIGNALS_EN},  
      {NAME_STANDARD_LOGIC_OUT_SIGNALS_KZ}
    };

    const uint8_t name_timer_out_signals[MAX_NAMBER_LANGUAGE][TIMER_SIGNALS_OUT][MAX_COL_LCD + 1] =
    {
      {NAME_TIMER_OUT_SIGNALS_RU},  
      {NAME_TIMER_OUT_SIGNALS_UA},  
      {NAME_TIMER_OUT_SIGNALS_EN},  
      {NAME_TIMER_OUT_SIGNALS_KZ}
    };
  
    const uint8_t name_trigger_out_signals[MAX_NAMBER_LANGUAGE][TRIGGER_SIGNALS_OUT][MAX_COL_LCD + 1] =
    {
      {NAME_TRIGGER_OUT_SIGNALS_RU},  
      {NAME_TRIGGER_OUT_SIGNALS_UA},  
      {NAME_TRIGGER_OUT_SIGNALS_EN},  
      {NAME_TRIGGER_OUT_SIGNALS_KZ}
    };

    const uint8_t name_meander_out_signals[MAX_NAMBER_LANGUAGE][MEANDER_SIGNALS_OUT][MAX_COL_LCD + 1] =
    {
      {NAME_MEANDER_OUT_SIGNALS_RU},  
      {NAME_MEANDER_OUT_SIGNALS_UA},  
      {NAME_MEANDER_OUT_SIGNALS_EN},  
      {NAME_MEANDER_OUT_SIGNALS_KZ}
    };

    const uint8_t * const array_p_name[NUMBER_ALL_BLOCKS] = 
    {
      (const uint8_t*)name_fix_block_out_signals, 
      (const uint8_t*)name_input_out_signals, 
      (const uint8_t*)name_output_led_out_signals, 
      (const uint8_t*)name_output_led_out_signals, 
      (const uint8_t*)name_alarm_out_signals, 
      (const uint8_t*)name_group_alarm_out_signals, 
      (const uint8_t*)name_standard_logic_out_signals, 
      (const uint8_t*)name_standard_logic_out_signals, 
      (const uint8_t*)name_standard_logic_out_signals, 
      (const uint8_t*)name_standard_logic_out_signals, 
      (const uint8_t*)name_timer_out_signals, 
      (const uint8_t*)name_trigger_out_signals, 
      (const uint8_t*)name_meander_out_signals
    };
    const unsigned int array_max_signal_out[NUMBER_ALL_BLOCKS] = 
    {
      FIX_BLOCK_SIGNALS_OUT, 
      INPUT_SIGNALS_OUT, 
      OUTPUT_LED_SIGNALS_OUT, 
      OUTPUT_LED_SIGNALS_OUT, 
      ALARM_SIGNALS_OUT, 
      GROUP_ALARM_SIGNALS_OUT, 
      STANDARD_LOGIC_SIGNALS_OUT, 
      STANDARD_LOGIC_SIGNALS_OUT, 
      STANDARD_LOGIC_SIGNALS_OUT, 
      STANDARD_LOGIC_SIGNALS_OUT, 
      TIMER_SIGNALS_OUT, 
      TRIGGER_SIGNALS_OUT, 
      MEANDER_SIGNALS_OUT
    };

    int index_language = index_language_in_array(select_struct_settings_fix()->language);
    unsigned int position_temp = current_state_menu2.index_position;
  
    unsigned int type_logical_node, number_logical_node;
    int index;
    unsigned int error = false;

    enum _menu2_levels ekran_before = previous_level_in_current_level_menu2[current_state_menu2.current_level];
    if (ekran_before == PARAM_LIST_INPUTS_OF_SELECTED_LOGICAL_NODE_MENU2_LEVEL)
    {
      index = position_in_current_level_menu2[ekran_before];

      ekran_before = previous_level_in_current_level_menu2[ekran_before];
      if (ekran_before == PARAM_LIST_LOGICAL_NODES_FOR_INPUT_MENU2_LEVEL)
      {
        number_logical_node = 1;
        type_logical_node = ID_FB_CONTROL_BLOCK;
      }
      else if (
               (ekran_before >= __BEGIN_PARAM_LIST_SELECTED_TYPE_LOGICAL_NODE_MENU2_LEVEL) &&
               (ekran_before <  __NEXT_AFTER_PARAM_LIST_SELECTED_TYPE_LOGICAL_NODE_MENU2_LEVEL)
              )   
      {
        number_logical_node = current_state_menu2.number_selection + 1; /*1 додаємо, індексація починається з нуля, а позначення у param  має іти з 1*/
    
        ekran_before = previous_level_in_current_level_menu2[ekran_before];
        if (ekran_before == PARAM_LIST_LOGICAL_NODES_FOR_INPUT_MENU2_LEVEL)
        {
          type_logical_node = position_in_current_level_menu2[ekran_before] + _ID_FB_FIRST_ALL;
        }
      }
      else error = true;
    }
    else error = true;
  
    unsigned int max_row = current_state_menu2.max_row;
    if (
        (error == false) &&
        (max_row != 0) &&
        (array_p_name[type_logical_node - _ID_FB_FIRST_ALL] != NULL)
       )   
    {
      unsigned int index_in_ekran = (position_temp >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;
  
      //Формуємо рядки  рядки у робочий екран
      uint32_t *p_param;
      switch (type_logical_node)
      {
      case ID_FB_CONTROL_BLOCK:
        {
          __SETTINGS_FIX *p_settings_fix = (current_state_menu2.edition == ED_VIEWING) ? &settings_fix_prt : &settings_fix;
          p_param = &p_settings_fix->param[index];
          break;
        }
      case ID_FB_OUTPUT:
      case ID_FB_LED:
        {
          if (current_state_menu2.edition == ED_VIEWING)
          {
            p_param = &(((__LN_OUTPUT_LED*)spca_of_p_prt[type_logical_node - _ID_FB_FIRST_ALL] + (number_logical_node - 1))->settings.param[index]);
          }
          else
          { 
            p_param = &(((__settings_for_OUTPUT_LED*)spca_of_p_prt[type_logical_node - _ID_FB_FIRST_ALL] + (number_logical_node - 1))->param[index]);
          }
            
          break;
        }
      case ID_FB_ALARM:
        {
          if (current_state_menu2.edition == ED_VIEWING)
          {
            p_param = &(((__LN_ALARM*)spca_of_p_prt[ID_FB_ALARM - _ID_FB_FIRST_ALL] + (number_logical_node - 1))->settings.param[index]);
          }
          else
          {
            p_param = &(((__settings_for_ALARM*)spca_of_p_prt[ID_FB_ALARM - _ID_FB_FIRST_ALL] + (number_logical_node - 1))->param[index]);
          }
            
          break;
        }
      case ID_FB_AND:
        {
          if (current_state_menu2.edition == ED_VIEWING)
          {
            p_param = ((__LN_AND*)spca_of_p_prt[ID_FB_AND - _ID_FB_FIRST_ALL] + (number_logical_node - 1))->settings.param;
          }
          else
          {
            p_param = ((__settings_for_AND*)spca_of_p_prt[ID_FB_AND - _ID_FB_FIRST_ALL] + (number_logical_node - 1))->param;
          }
            
          break;
        }
      case ID_FB_OR:
        {
          if (current_state_menu2.edition == ED_VIEWING)
          {
            p_param = ((__LN_OR*)spca_of_p_prt[ID_FB_OR - _ID_FB_FIRST_ALL] + (number_logical_node - 1))->settings.param;
          }
          else
          {
            p_param = ((__settings_for_OR*)spca_of_p_prt[ID_FB_OR - _ID_FB_FIRST_ALL] + (number_logical_node - 1))->param;
          }
            
          break;
        }
      case ID_FB_XOR:
        {
          if (current_state_menu2.edition == ED_VIEWING)
          {
            p_param = ((__LN_XOR*)spca_of_p_prt[ID_FB_XOR - _ID_FB_FIRST_ALL] + (number_logical_node - 1))->settings.param;
          }
          else
          {
            p_param = ((__settings_for_XOR*)spca_of_p_prt[ID_FB_XOR - _ID_FB_FIRST_ALL] + (number_logical_node - 1))->param;
          }
            
          break;
        }
      case ID_FB_NOT:
        {
          if (current_state_menu2.edition == ED_VIEWING)
          {
            p_param = &(((__LN_NOT*)spca_of_p_prt[ID_FB_NOT - _ID_FB_FIRST_ALL] + (number_logical_node - 1))->settings.param);
          }
          else
          {
            p_param = &(((__settings_for_NOT*)spca_of_p_prt[ID_FB_NOT - _ID_FB_FIRST_ALL] + (number_logical_node - 1))->param);
          }
            
          break;
        }
       case ID_FB_TIMER:
        {
          if (current_state_menu2.edition == ED_VIEWING)
          {
            p_param = &(((__LN_TIMER*)spca_of_p_prt[ID_FB_TIMER - _ID_FB_FIRST_ALL] + (number_logical_node - 1))->settings.param[index]);
          }
          else
          {
            p_param = &(((__settings_for_TIMER*)spca_of_p_prt[ID_FB_TIMER - _ID_FB_FIRST_ALL] + (number_logical_node - 1))->param[index]);
          }
          
          break;
        }
      case ID_FB_TRIGGER:
        {
          if (current_state_menu2.edition == ED_VIEWING)
          {
            p_param = &(((__LN_TRIGGER*)spca_of_p_prt[ID_FB_TRIGGER - _ID_FB_FIRST_ALL] + (number_logical_node - 1))->settings.param[index]);
          }
          else
          {
            p_param = &(((__settings_for_TRIGGER*)spca_of_p_prt[ID_FB_TRIGGER - _ID_FB_FIRST_ALL] + (number_logical_node - 1))->param[index]);
          }
          
          break;
        }
      default:
        {
          //Якщо сюди дійшла програма, значить відбулася недопустива помилка, тому треба зациклити програму, щоб вона пішла на перезагрузку
          total_error_sw_fixed(10);
        }
      }
        
      for (size_t i = 0; i < MAX_ROW_LCD; i++)
      {
        //Шукаємо рядок, який треба відобразити
        while (
               (index_in_ekran != 0) &&
               (index_in_ekran < max_row) &&
               (p_param[index_in_ekran] == 0)
              )
        {
          index_in_ekran++;
        } 
          
        //Наступні рядки треба перевірити, чи їх требе відображати
        if (index_in_ekran < max_row)
        {
          uint32_t param = p_param[index_in_ekran];
          if (param != 0)
          {
            unsigned int id_input   = (param >> SFIFT_PARAM_ID ) & MASKA_PARAM_ID ;
            unsigned int n_input    = (param >> SFIFT_PARAM_N  ) & MASKA_PARAM_N  ;
            unsigned int out_input  = (param >> SFIFT_PARAM_OUT) & MASKA_PARAM_OUT;
        
            unsigned int part = 0;
            uint8_t *p = ((uint8_t*)array_p_name[id_input - _ID_FB_FIRST_ALL]) + (index_language*array_max_signal_out[id_input - _ID_FB_FIRST_ALL] + (out_input - 1))*(MAX_COL_LCD + 1);
            unsigned int number_digit, first_index_number, number_logical_node_tmp = n_input;
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
                  uint8_t symbol = name_f_blocks[index_language][id_input - _ID_FB_FIRST_ALL][k];
              
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
                      number_digit = max_number_digit_in_number(n_input);
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

            if (position_temp == index_in_ekran)
            {
              current_state_menu2.position_cursor_x = 0;
            }
          }
          else
          {
            const uint8_t information_error[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
            {
              "     Пусто      ",
              "     Пусто      ",
              "     Empty      ",
              "     Пусто      "
            };
            const uint32_t cursor_x_error[MAX_NAMBER_LANGUAGE] = {4, 4, 4, 4};

            for (size_t j = 0; j < MAX_COL_LCD; j++) working_ekran[i][j] = information_error[index_language][j];
            if (position_temp == index_in_ekran)
            {
              current_state_menu2.position_cursor_x = cursor_x_error[index_language];
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
      const uint8_t information_error[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
      {
        "     Ошибка     ",
        "    Помилка     ",
        "     Error      ",
        "     Ошибка     "
      };

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
//
/*****************************************************/
/*****************************************************/
