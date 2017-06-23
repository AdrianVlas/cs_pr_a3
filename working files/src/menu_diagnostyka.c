#include "header.h"

#define NUMBER_ROW_FOR_NO_ERRORS 2

const uint8_t name_string_diagnostyka[MAX_NAMBER_LANGUAGE][NUMBER_ROW_FOR_NO_ERRORS + MAX_ROW_FOR_DIAGNOSTYKA][MAX_COL_LCD + 1] = 
{
  {
    "      Нет       ",
    "     ошибок     ",
    NAME_DIAGN_RU
  },
  {
    "     Немає      ",
    "    помилок     ",
    NAME_DIAGN_UA
  },
  {
    "       No       ",
    "     errors     ",
    NAME_DIAGN_EN
  },
  {
    "      Кате      ",
    "      жок       ",
    NAME_DIAGN_KZ
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
void move_into_diagnostics(unsigned int action, int max_row)
{
  size_t n_diagn_states = 0;
  
  switch (diagnostyka_arrays_located)
  {
  case DIAGN_ARRAYS_ALL:
    {
      n_diagn_states = NUMBER_ERRORS;
      break;
    }
  case DIAGN_ARRAYS_SHORT:
  case DIAGN_ARRAYS_ERROR:
    {
      n_diagn_states = _NUMBER_ERRORS_WITHOUT_DIGITAL_OUTPUTS;
      break;
    }
  default:
    {
      break;
    }
  }
  size_t _n = DIV_TO_HIGHER(n_diagn_states, 32);
  
  uint32_t present_diagnostyka = false;
  for (size_t i = 0; i < _n; i++)
  {
    diagnostyka_tmp_low[i] = diagnostyka[i];
    if (diagnostyka_tmp_low[i] != 0) present_diagnostyka = true;
  }
  
//  unsigned int diagnostyka_tmp[2] = {diagnostyka[0], diagnostyka[1]};
//  if (
//      (diagnostyka_tmp[0] == 0) &&
//      (diagnostyka_tmp[1] == 0)
//     ) 
  if (present_diagnostyka == false)
  {
    current_state_menu2.index_position = 0;
  }
  else
  {
    if (action & ((1 << BIT_REWRITE) | (1 << BIT_KEY_DOWN)))
    {
      if (action & (1 << BIT_KEY_DOWN)) current_state_menu2.index_position++;
      do
      {
        if(current_state_menu2.index_position >= max_row) current_state_menu2.index_position = 0;
        while (_CHECK_SET_BIT(diagnostyka_tmp_low/*diagnostyka_tmp*/, current_state_menu2.index_position) == 0)
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
        while (_CHECK_SET_BIT(diagnostyka_tmp_low/*diagnostyka_tmp*/, current_state_menu2.index_position) == 0)
        {
          if(--current_state_menu2.index_position < 0) current_state_menu2.index_position = max_row - 1;
        }
      }
      while (current_state_menu2.index_position < 0);
    }
  }
}
/*****************************************************/

/*****************************************************/
//Формуємо екран відображення діагностики
/*****************************************************/
void make_ekran_diagnostics(void)
{
  
  unsigned int position_temp = current_state_menu2.index_position;
  int index_language = index_language_in_array(settings_fix_prt.language);
    
  size_t n_diagn_states = 0;
  
  switch (diagnostyka_arrays_located)
  {
  case DIAGN_ARRAYS_ALL:
    {
      n_diagn_states = NUMBER_ERRORS;
      break;
    }
  case DIAGN_ARRAYS_SHORT:
  case DIAGN_ARRAYS_ERROR:
    {
      n_diagn_states = _NUMBER_ERRORS_WITHOUT_DIGITAL_OUTPUTS;
      break;
    }
  default:
    {
      break;
    }
  }
  size_t _n = DIV_TO_HIGHER(n_diagn_states, 32);
  
  uint32_t present_diagnostyka = false;
  for (size_t i = 0; ((present_diagnostyka == false) && (i < _n)); i++)
  {
    if (diagnostyka_tmp_low[i] != 0) present_diagnostyka = true;
  }
  
//  if (
//      (diagnostyka[0] == 0) &&
//      (diagnostyka[1] == 0)
//     )
  if (present_diagnostyka == false)  
  {
    //Це означає, що ніякої помилки не зафіксовано
     
    //Текучу позицію в сипску переводимо на сам початок
    current_state_menu2.index_position = 0;
    position_in_current_level_menu2[current_state_menu2.current_level] = 0;

    //Копіюємо  рядки у робочий екран
    for (size_t i = 0; i < MAX_ROW_LCD; i++)
    {
      //Копіюємо в робочий екран інформацію, що нічого не відранжовано
      for (size_t j = 0; j < MAX_COL_LCD; j++)working_ekran[i][j] = (i < NUMBER_ROW_FOR_NO_ERRORS) ? name_string_diagnostyka[index_language][i][j] : ' ';
    }
    //Курсор не видимий
    current_state_menu2.cursor_on = 0;
  }
  else
  {
    /************************************************************/
    //Формуємо список із помилок які реально присутні
    /************************************************************/
    uint8_t name_string_tmp[MAX_ROW_FOR_DIAGNOSTYKA][MAX_COL_LCD + 1];
    int32_t index_first_rele_error = -1;
    int32_t index_last_before_rele_error = -1;

    int32_t offset = 0, offset_extra = 0;
    for(intptr_t index_1 = 0; index_1 < (MAX_ROW_FOR_DIAGNOSTYKA - offset); index_1++)
    {
      while (
             (index_1 < (_NUMBER_ERRORS_WITHOUT_DIGITAL_OUTPUTS - offset)) &&
             (_CHECK_SET_BIT(diagnostyka_tmp_low, (index_1 + offset)) == 0)
            )   
      {
        if (current_state_menu2.index_position >= ((int)(index_1 + offset))) position_temp--;
        offset++;
      }
      if (
          (index_1 < (_NUMBER_ERRORS_WITHOUT_DIGITAL_OUTPUTS - offset)) &&
          (_CHECK_SET_BIT(diagnostyka_tmp_low, (index_1 + offset)) != 0)
         )   
      {
        index_last_before_rele_error = index_1;
      }
      
      if (index_1 == (_NUMBER_ERRORS_WITHOUT_DIGITAL_OUTPUTS - offset))
      {
        if (diagnostyka_arrays_located == DIAGN_ARRAYS_ALL)
        {
          for (size_t index_2 = index_1; index_2 < (NUMBER_ERRORS - offset - offset_extra); index_2++ )
          {
            while (
                   (index_2 < (NUMBER_ERRORS - offset - offset_extra)) &&
                   (_CHECK_SET_BIT(diagnostyka_tmp_low, (index_2 + offset + offset_extra)) == 0)
                  )   
            {
              if (current_state_menu2.index_position >= ((int)(index_2 + offset + offset_extra))) position_temp--;
              offset_extra++;
            }

            if (
                (index_first_rele_error < 0) &&
                (index_2 < (NUMBER_ERRORS - offset - offset_extra)) &&
                (_CHECK_SET_BIT(diagnostyka_tmp_low, (index_2 + offset + offset_extra)) != 0)
                    )   
            {
              index_first_rele_error = index_1;
            }
          }
        }
        else offset++;
      }
      
      if (index_1 < (MAX_ROW_FOR_DIAGNOSTYKA - offset - (offset_extra == current_config_prt.n_output)))
      {
        for(size_t index_2 = 0; index_2 < (MAX_COL_LCD + 1); index_2++)
          name_string_tmp[index_1][index_2] = name_string_diagnostyka[index_language][NUMBER_ROW_FOR_NO_ERRORS + index_1 + offset][index_2];
      }
      else
      {
        size_t index_2;
        for(index_2 = 0; index_2 < MAX_COL_LCD; index_2++) name_string_tmp[index_1][index_2] = ' ';
        name_string_tmp[index_1][index_2] = '\0';
      }
    }
    /************************************************************/
    
    int32_t index_in_ekran = (position_temp >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;
    //Копіюємо  рядки у робочий екран
    int32_t index_1 = 0;
    uint32_t index_2 = 0;
    for (size_t i = 0; i< MAX_ROW_LCD; i++)
    {
      if (index_in_ekran < ((int32_t)n_diagn_states - offset - offset_extra))
      {
        if (index_in_ekran <= index_last_before_rele_error)
        {
          for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string_tmp[index_in_ekran][j];
        }
        else
        {
          if (index_first_rele_error >= 0)
          {
            while (
                   (index_1 < (index_in_ekran - index_first_rele_error + 1)) &&
                   (index_2 < current_config_prt.n_output)  
                  )   
            {
              if (_CHECK_SET_BIT(diagnostyka_tmp_low, (_NUMBER_ERRORS_WITHOUT_DIGITAL_OUTPUTS + index_2)) != 0) index_1++;
               
              index_2++;
            }
           
            if (index_2 <= current_config_prt.n_output)
            {
              uint32_t first_index = first_index_array_name_error_rele[index_language];

              uint32_t number = index_2;
              uint32_t number_digit = max_number_digit_in_number(number);
              
              for (unsigned int j = 0; j < MAX_COL_LCD; j++) 
              {
                if (j < first_index) working_ekran[i][j] = name_string_tmp[index_first_rele_error][j];
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
                else working_ekran[i][j] = name_string_tmp[index_first_rele_error][j - number_digit];
              }
            }
            else
            {
              for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = information_error[index_language][j];
            }
          }
          else
          {
            for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = information_error[index_language][j];
          }
        }
      }
      else
      {
        for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] =  ' ';
      }

      index_in_ekran++;
    }

    //Курсор видимий
    current_state_menu2.cursor_on = 1;
  }

  //Курсор по горизонталі відображається на першій позиції
  current_state_menu2.position_cursor_x = 0;
  //Відображення курору по вертикалі
  current_state_menu2.position_cursor_y = position_temp & (MAX_ROW_LCD - 1);

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

#undef NUMBER_ROW_FOR_NO_ERRORS

