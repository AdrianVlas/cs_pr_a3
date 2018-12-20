#include "header.h"

const uint8_t (* const array_p_name[NUMBER_VAR_BLOCKS])[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
{
  &name_input,
  &name_output,
  &name_led,
  &name_button,
  &name_alarm,
  &name_group_alarm,
  &name_and,
  &name_or,
  &name_xor,
  &name_not,
  &name_timer,
  &name_trigger,
  &name_meander,
  &name_tu,
  &name_ts,
  &name_input_GOOSE_block,
  &name_input_MMS_block,
  &name_network_output_block,
  &name_log
};
const unsigned int (* const array_p_first_index_number[NUMBER_VAR_BLOCKS])[MAX_NAMBER_LANGUAGE] = 
{
  &first_index_number_input,
  &first_index_number_output,
  &first_index_number_led,
  &first_index_number_button,
  &first_index_number_alarm,
  &first_index_number_group_alarm,
  &first_index_number_and,
  &first_index_number_or,
  &first_index_number_xor,
  &first_index_number_not,
  &first_index_number_timer,
  &first_index_number_trigger,
  &first_index_number_meander,
  &first_index_number_tu,
  &first_index_number_ts,
  &first_index_number_input_GOOSE_block,
  &first_index_number_input_MMS_block,
  &first_index_number_network_output_block,
  &first_index_number_log
};

/*****************************************************/
//Формуємо екран відображення списку функціональних блоків певного типу
/*****************************************************/
void make_ekran_list_logical_nodes(void)
{
  int index_language = index_language_in_array(select_struct_settings_fix()->language);
  
  const uint8_t *p_name;
  const unsigned int *p_first_index_number;
  enum _menu2_levels current_level = current_state_menu2.current_level;
  if (
      (
       (current_level >= __BEGIN_EDITOR_LIST_SELECTED_TYPE_LOGICAL_NODE_FOR_INPUT_MENU2_LEVEL) &&
       (current_level <  __NEXT_AFTER_EDITOR_LIST_SELECTED_TYPE_LOGICAL_NODE_FOR_INPUT_MENU2_LEVEL)
      )
//      ||  
//      (
//       (current_level >= __BEGIN_EDITOR_LIST_SELECTED_TYPE_LOGICAL_NODE_FOR_OUTPUT_MENU2_LEVEL) &&
//       (current_level <  __NEXT_AFTER_EDITOR_LIST_SELECTED_TYPE_LOGICAL_NODE_FOR_OUTPUT_MENU2_LEVEL)
//      )
     )   
  {
    intptr_t index = position_in_current_level_menu2[previous_level_in_current_level_menu2[current_level]] - NUMBER_FIX_BLOCKS; 
    p_name = (*array_p_name[index])[index_language];
    p_first_index_number = &(*array_p_first_index_number[index])[index_language];
  }
  else
  {
    switch (current_level)
    {
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
    case LIST_ALARMS_MENU2_LEVEL:
      {
        p_name = name_alarm[index_language];
        p_first_index_number = &first_index_number_alarm[index_language];
        break;
      }
    case LIST_GROUP_ALARMS_MENU2_LEVEL:
      {
        p_name = name_group_alarm[index_language];
        p_first_index_number = &first_index_number_group_alarm[index_language];
        break;
      }
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
    default:
      {
        //Якщо сюди дійшла програма, значить відбулася недопустива помилка, тому треба зациклити програму, щоб вона пішла на перезагрузку
        total_error_sw_fixed(85);
      }
    }
  }

  unsigned int position_temp = current_state_menu2.index_position;
  unsigned int index_in_ekran = (position_temp >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;
  unsigned int max_row = (current_state_menu2.p_max_row == NULL) ? current_state_menu2.max_row : *current_state_menu2.p_max_row;

  //Формуємо рядки у робочий екран
  for (size_t i = 0; i < MAX_ROW_LCD; i++)
  {
    //Наступні рядки треба перевірити, чи їх требе відображати у текучій конфігурації
    if (index_in_ekran < max_row)
    {
      if (
          (
           (current_level == EDITOR_LIST_BUTTONS_FOR_INPUT_MENU2_LEVEL ) /*||
           (current_level == EDITOR_LIST_BUTTONS_FOR_OUTPUT_MENU2_LEVEL)*/
          )
          &&  
          (index_in_ekran < NUMBER_FIX_BUTTONS)    
         )
      {
        for (size_t j = 0; j < MAX_COL_LCD; j++) working_ekran[i][j] = name_fix_buttons[index_in_ekran][j];
      }
      else
      {
          
        unsigned int number = index_in_ekran + 1;
        if (
            (current_level == EDITOR_LIST_BUTTONS_FOR_INPUT_MENU2_LEVEL ) /*||
            (current_level == EDITOR_LIST_BUTTONS_FOR_OUTPUT_MENU2_LEVEL)*/
           )
        {
          number -= NUMBER_FIX_BUTTONS;
        }
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
  current_state_menu2.cursor_blinking_on = (current_state_menu2.edition < ED_EDITION) ? 0 : 1;
  //Обновити повністю весь екран
  current_state_menu2.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/

/*****************************************************/
//
/*****************************************************/
/*****************************************************/
