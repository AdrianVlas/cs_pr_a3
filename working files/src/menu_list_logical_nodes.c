#include "header.h"

/*****************************************************/
//Формуємо екран відображення списку функціональних блоків певного типу
/*****************************************************/
void make_ekran_list_logical_nodes(void)
{
  const uint8_t name_timer[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
  {
    {" БФ-Таймер      "},
    {" БФ-Таймер      "},
    {" MF-Timer       "},
    {" БФ-Таймер      "}
  };
  const unsigned int first_index_number_timer[MAX_NAMBER_LANGUAGE] = {10, 10, 9, 10};

  const uint8_t name_meander[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
  {
    {" ГПС            "},
    {" ГПС            "},
    {" PSG            "},
    {" ГПС            "}
  };
  const unsigned int first_index_number_meander[MAX_NAMBER_LANGUAGE] = {4, 4, 4, 4};

  const uint8_t name_input[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
  {
    {" Д.Вх.          "},
    {" Д.Вх.          "},
    {" DI             "},
    {" Д.Вх.          "}
  };
  const unsigned int first_index_number_input[MAX_NAMBER_LANGUAGE] = {6, 6, 3, 6};
  
  const uint8_t name_output[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
  {
    {" В.Реле          "},
    {" В.Реле          "},
    {" DO              "},
    {" В.Реле          "}
  };
  const unsigned int first_index_number_output[MAX_NAMBER_LANGUAGE] = {7, 7, 3, 7};
  
  const uint8_t name_led[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
  {
    {" Св.             "},
    {" Св.             "},
    {" LED             "},
    {" Св.             "}
  };
  const unsigned int first_index_number_led[MAX_NAMBER_LANGUAGE] = {4, 4, 4, 4};
  
  int index_language;
  if (current_state_menu2.edition == ED_VIEWING) index_language = index_language_in_array(settings_fix_prt.language);
  else if (
           (current_state_menu2.edition == ED_EDITION) ||
           (current_state_menu2.edition == ED_CONFIRM_CHANGES)
          )  
  {
    index_language = index_language_in_array(settings_fix_edit.language);
  }
  else
  {
    index_language = index_language_in_array(settings_fix.language);
  }
  
  const uint8_t *p_name;
  const unsigned int *p_first_index_number;
  switch (current_state_menu2.current_level)
  {
  case LIST_TIMERS_MENU2_LEVEL:
    {
      p_name = name_timer[index_language];
      p_first_index_number = &first_index_number_timer[index_language];
      break;
    }
  case LIST_MEANDERS_MENU2_LEVEL:
    {
      p_name = name_meander[index_language];
      p_first_index_number = &first_index_number_meander[index_language];
      break;
    }
  case LIST_INPUTS_MENU2_LEVEL:
    {
      p_name = name_input[index_language];
      p_first_index_number = &first_index_number_input[index_language];
      break;
    }
  case LIST_OUTPUTS_MENU2_LEVEL:
    {
      p_name = name_output[index_language];
      p_first_index_number = &first_index_number_output[index_language];
      break;
    }
  case LIST_LEDS_MENU2_LEVEL:
    {
      p_name = name_led[index_language];
      p_first_index_number = &first_index_number_led[index_language];
      break;
    }
  default:
    {
      //Якщо сюди дійшла програма, значить відбулася недопустива помилка, тому треба зациклити програму, щоб вона пішла на перезагрузку
      total_error_sw_fixed(85);
    }
  }

  unsigned int position_temp = current_state_menu2.index_position;
  unsigned int index_in_ekran = (position_temp >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;
  unsigned int max_row = (current_state_menu2.p_max_row == NULL) ? current_state_menu2.max_row : *current_state_menu2.p_max_row;

  //Формуємо рядки  рядки у робочий екран
  for (size_t i = 0; i < MAX_ROW_LCD; i++)
  {
    //Наступні рядки треба перевірити, чи їх требе відображати у текучій конфігурації
    if (index_in_ekran < max_row)
    {
      unsigned int number = index_in_ekran + 1;
      unsigned int number_digit = max_number_digit_in_number(number);

      for (size_t j = 0; j < MAX_COL_LCD; j++)
      {
        if ((j < *p_first_index_number) || (j >= (*p_first_index_number + number_digit)))
        {
          working_ekran[i][j] = p_name[j];
        }
        else
        {
          /*
          Заповнюємо значення зправа  на ліво
          індекс = *p_first_index_number + number_digit - 1 - (j - *p_first_index_number) =
          = *p_first_index_number + number_digit - 1 - j + *p_first_index_number =
          = 2x(*p_first_index_number) + number_digit - 1 - j =
          */
          working_ekran[i][2*(*p_first_index_number) + number_digit - 1 - j] = (number % 10) + 0x30;
          number /= 10;
        }
      }
    }
    else
    {
      for (size_t j = 0; j < MAX_COL_LCD; j++) working_ekran[i][j] = ' ';
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
//
/*****************************************************/
/*****************************************************/
