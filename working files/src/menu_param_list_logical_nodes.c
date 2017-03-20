#include "header.h"

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
  unsigned int logical_node_shown[NUMBER_ALL_BLOCKS] = 
  {
    true,
    ((p_config->n_input*0                     ) != 0),
    ((p_config->n_output*OUTPUT_LED_SIGNALS_IN) != 0),
    ((p_config->n_led*OUTPUT_LED_SIGNALS_IN   ) != 0),
    ((p_config->n_alarm*ALARM_SIGNALS_IN      ) != 0),
    ((p_config->n_group_alarm*0               ) != 0),
    ((p_config->n_and*AND_SIGNALS_IN          ) != 0),
    ((p_config->n_or*OR_SIGNALS_IN            ) != 0),
    ((p_config->n_xor*2                       ) != 0),
    ((p_config->n_not*1                       ) != 0),
    ((p_config->n_timer*TIMER_SIGNALS_IN      ) != 0),
    ((p_config->n_trigger*TRIGGER_SIGNALS_IN  ) != 0),
    ((p_config->n_meander*0                   ) != 0)
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
  __CONFIG *p_config = (current_state_menu2.edition == ED_VIEWING) ? &current_config_prt : &current_config;
  unsigned int logical_node_shown[NUMBER_ALL_BLOCKS] = 
  {
    true,
    ((p_config->n_input*0                     ) != 0),
    ((p_config->n_output*OUTPUT_LED_SIGNALS_IN) != 0),
    ((p_config->n_led*OUTPUT_LED_SIGNALS_IN   ) != 0),
    ((p_config->n_alarm*ALARM_SIGNALS_IN      ) != 0),
    ((p_config->n_group_alarm*0               ) != 0),
    ((p_config->n_and*AND_SIGNALS_IN          ) != 0),
    ((p_config->n_or*OR_SIGNALS_IN            ) != 0),
    ((p_config->n_xor*2                       ) != 0),
    ((p_config->n_not*1                       ) != 0),
    ((p_config->n_timer*TIMER_SIGNALS_IN      ) != 0),
    ((p_config->n_trigger*TRIGGER_SIGNALS_IN  ) != 0),
    ((p_config->n_meander*0                   ) != 0)
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
  //Курсор не мигає
  current_state_menu2.cursor_blinking_on = 0;
  //Обновити повністю весь екран
  current_state_menu2.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/

/*****************************************************/
//Формуємо екран
/*****************************************************/
void make_ekran_param_list_inputs_of_selected_logical_node(void)
{
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
  if (ekran_before == PARAM_LIST_LOGICAL_NODES_MENU2_LEVEL)
  {
    number_logical_node = 1;
    type_logical_node = ID_FB_CONTROL_BLOCK;
  }
  else if (
           (ekran_before == PARAM_LIST_INPUTS_MENU2_LEVEL      ) ||
           (ekran_before == PARAM_LIST_OUTPUTS_MENU2_LEVEL     ) ||
           (ekran_before == PARAM_LIST_LEDS_MENU2_LEVEL        ) ||
           (ekran_before == PARAM_LIST_ALARMS_MENU2_LEVEL      ) ||
           (ekran_before == PARAM_LIST_GROUP_ALARMS_MENU2_LEVEL) ||
           (ekran_before == PARAM_LIST_ANDS_MENU2_LEVEL        ) ||
           (ekran_before == PARAM_LIST_ORS_MENU2_LEVEL         ) ||
           (ekran_before == PARAM_LIST_XORS_MENU2_LEVEL        ) ||
           (ekran_before == PARAM_LIST_NOTS_MENU2_LEVEL        ) ||
           (ekran_before == PARAM_LIST_TIMERS_MENU2_LEVEL      ) ||
           (ekran_before == PARAM_LIST_TRIGGERS_MENU2_LEVEL    )
          )   
  {
    number_logical_node = position_in_current_level_menu2[ekran_before] + 1; /*1 додаємо, індексація починається з нуля, а позначення у param  має іти з 1*/
    
    ekran_before = previous_level_in_current_level_menu2[ekran_before];
    if (ekran_before == PARAM_LIST_LOGICAL_NODES_MENU2_LEVEL)
    {
      type_logical_node = position_in_current_level_menu2[ekran_before] + _ID_FB_FIRST_ALL;
    }
  }
  
  unsigned int error = false;
  unsigned int max_row = current_state_menu2.max_row;
  if (
      (ekran_before == PARAM_LIST_LOGICAL_NODES_MENU2_LEVEL) &&
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
  //Обновити повністю весь екран
  current_state_menu2.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/

/*****************************************************/
//
/*****************************************************/
/*****************************************************/
