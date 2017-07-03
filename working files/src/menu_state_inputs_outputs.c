#include "header.h"

#define ROWS_ONE_PART   2

/*****************************************************/
//Функція визначення, скільки розрядів є у числі
/*****************************************************/
unsigned int max_number_digit_in_number(int max_item)
{
  unsigned int number_digit = 1;
  while (max_item  >= 10)
  {
    number_digit++;
    max_item /= 10;
  }
  
  return number_digit;
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
void move_into_ekran_list_inputs_outputs(unsigned int action, int max_row)
{
  if (action & ((1 << BIT_REWRITE) | (1 << BIT_KEY_DOWN)))
  {
    if (action & (1 << BIT_KEY_DOWN)) current_state_menu2.index_position++;
    do
    {
      if(current_state_menu2.index_position >= max_row) current_state_menu2.index_position = 0;
      while (
             (
              (current_state_menu2.index_position == INDEX_INOUT_OUTPUT_M2_ANALOG_INPUT) &&
              (current_config_prt.n_group_alarm == 0)
             )
             ||  
             (
              (current_state_menu2.index_position == INDEX_INOUT_OUTPUT_M2_INPUT) &&
              (current_config_prt.n_input == 0)
             )
             ||  
             (
              (current_state_menu2.index_position == INDEX_INOUT_OUTPUT_M2_OUTPUT) &&
              (current_config_prt.n_output == 0)
             )
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
             (
              (current_state_menu2.index_position == INDEX_INOUT_OUTPUT_M2_ANALOG_INPUT) &&
              (current_config_prt.n_group_alarm == 0)
             )
             ||  
             (
              (current_state_menu2.index_position == INDEX_INOUT_OUTPUT_M2_INPUT) &&
              (current_config_prt.n_input == 0)
             )
             ||  
             (
              (current_state_menu2.index_position == INDEX_INOUT_OUTPUT_M2_OUTPUT) &&
              (current_config_prt.n_output == 0)
             )
            )
      {
        if(--current_state_menu2.index_position < 0) current_state_menu2.index_position = max_row - 1;
      }
    }
    while (current_state_menu2.index_position < 0);
  }
}
/*****************************************************/

/*****************************************************/
//Формуємо екран відображення заголовків станів входів-виходів
/*****************************************************/
void make_ekran_list_inputs_outputs(void)
{
  int index_language = index_language_in_array(settings_fix_prt.language);

  unsigned int additional_current = 0;
  unsigned int position_temp = current_state_menu2.index_position;

  uint8_t name_string_tmp[MAX_ROW_INPUT_OUTPUT_M2][MAX_COL_LCD + 1];
  for(size_t index_1 = 0; index_1 < MAX_ROW_INPUT_OUTPUT_M2; index_1++)
  {
    if (
        (
         (index_1 == INDEX_INOUT_OUTPUT_M2_ANALOG_INPUT) &&
         (current_config_prt.n_group_alarm == 0)
        )
        ||  
        (
         (index_1 == INDEX_INOUT_OUTPUT_M2_INPUT) &&
         (current_config_prt.n_input == 0)
        )
        ||  
        (
         (index_1 == INDEX_INOUT_OUTPUT_M2_OUTPUT) &&
         (current_config_prt.n_output == 0)
        )
       )
    {
      if ((index_1 - additional_current) < position_temp) position_temp--;
      additional_current++;

      for(size_t index_2 = 0; index_2 < MAX_COL_LCD; index_2++)
      {
        name_string_tmp[MAX_ROW_INPUT_OUTPUT_M2 - additional_current][index_2] = ' ';
      }
      name_string_tmp[MAX_ROW_INPUT_OUTPUT_M2 - additional_current][MAX_COL_LCD] = '\0';
    }
    else
    {
      for(size_t index_2 = 0; index_2 < (MAX_COL_LCD + 1); index_2++)
      {
        name_string_tmp[index_1 - additional_current][index_2] = name_string_inputs_outputs[index_language][index_1][index_2];
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
      working_ekran[i][j] =  (index_in_ekran < (MAX_ROW_INPUT_OUTPUT_M2 - additional_current)) ? name_string_tmp[index_in_ekran][j] : ' ';
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
/*
Функція переміщення по меню (без винятків і додаткових алгоритмів)

Вхідні параметри
(1 << BIT_REWRITE) - перемалювати меню
(1 << BIT_KEY_DOWN) - рухатися вниз
(1 << BIT_KEY_UP) - рухатися вверх
*/
/*****************************************************/
void move_into_ekran_input_or_output(unsigned int action, int max_row_tmp)
{
  int max_row = DIV_TO_HIGHER(max_row_tmp, (MAX_COL_LCD/(max_number_digit_in_number(max_row_tmp) + 1))*(MAX_ROW_LCD/ROWS_ONE_PART));
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
/*****************************************************/

/*******************************************************/
//Формуємо екрвн станів входів або виходів
/*******************************************************/
void make_ekran_state_inputs_or_outputs(void)
{
  unsigned int max_number_digit = max_number_digit_in_number(*current_state_menu2.p_max_row); 
  unsigned int number_inputs_or_outputs_in_row = MAX_COL_LCD/(max_number_digit + 1);
  
  unsigned int in_out = current_state_menu2.index_position*number_inputs_or_outputs_in_row*(MAX_ROW_LCD/ROWS_ONE_PART) + 1;
  unsigned int row = 0;
  while (row < MAX_ROW_LCD)
  {
    uint8_t name_string[ROWS_ONE_PART][MAX_COL_LCD + 1] = 
    {
      "                ",
      "                "
    };
  
    for (size_t i = 0; i < number_inputs_or_outputs_in_row; i++)
    {
      unsigned int value = in_out + i;
      for (size_t j = 0; j < max_number_digit; j++)
      {
        unsigned int digit = value % 10;
        value /= 10;
      
        name_string[0][i*(max_number_digit + 1) + (max_number_digit + 1 - 1) - j] = digit + 0x30;
        if (value == 0) break;
      }
    
      int _n = in_out + i - 1;
      if (current_state_menu2.current_level == INPUTS_MENU2_LEVEL)
      {
        __LN_INPUT *arr = (__LN_INPUT*)(spca_of_p_prt[ID_FB_INPUT - _ID_FB_FIRST_VAR]);
        value = arr[_n].active_state[INPUT_OUT >> 3] & (1 << (INPUT_OUT & ((1 << 3) - 1)));
      }
      else
      {
        __LN_OUTPUT_LED *arr = (__LN_OUTPUT_LED*)(spca_of_p_prt[ID_FB_OUTPUT - _ID_FB_FIRST_VAR]);
        value = arr[_n].active_state[OUTPUT_LED_OUT >> 3] & (1 << (OUTPUT_LED_OUT & ((1 << 3) - 1)));
      }
      name_string[1][i*(max_number_digit + 1) + (max_number_digit + 1 - 1)] = (value != 0) +  + 0x30;
      if ((_n + 1) >= *current_state_menu2.p_max_row ) break;
    }
  
    //Копіюємо  рядки у робочий екран
    for (size_t i = 0; i < ROWS_ONE_PART; i++)
    {
      //Наступні рядки треба перевірити, чи їх требе відображати
      for (size_t j = 0; j < MAX_COL_LCD; j++)
      {
        working_ekran[row + i][j] = name_string[i][j];
      }
    }
    
    in_out += number_inputs_or_outputs_in_row*(MAX_ROW_LCD/ROWS_ONE_PART);
    row += ROWS_ONE_PART;
  }

  //Відображення курору по вертикалі
  current_state_menu2.position_cursor_x = 0;
  //Відображення курору по вертикалі
  current_state_menu2.position_cursor_y = 0;
  //Курсор невидимий
  current_state_menu2.cursor_on = 0;
  //Курсор не мигає
  current_state_menu2.cursor_blinking_on = 0;
  //Обновити повністю весь екран
  current_state_menu2.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/

#undef ROWS_ONE_PART  

/*****************************************************/
/*
Функція переміщення по меню кількості кіл ШГС

Вхідні параметри
(1 << BIT_REWRITE) - перемалювати меню
(1 << BIT_KEY_DOWN) - рухатися вниз
(1 << BIT_KEY_UP) - рухатися вверх
*/
/*****************************************************/
void move_into_ekran_state_analog_inputs(unsigned int action, int max_row)
{
  if (action & ((1 << BIT_REWRITE) | (1 << BIT_KEY_DOWN)))
  {
    if (action & (1 << BIT_KEY_DOWN)) current_state_menu2.index_position += MAX_ROW_LCD;
    if(current_state_menu2.index_position >= max_row) current_state_menu2.index_position = 0;
  }
  else if (action & (1 << BIT_KEY_UP))
  {
    current_state_menu2.index_position -= MAX_ROW_LCD;
    if(current_state_menu2.index_position < 0) current_state_menu2.index_position = max_row - MAX_ROW_LCD;
  }
  current_state_menu2.index_position &= (1 << MAX_ROW_LCD) - 1;
}
/*****************************************************/

/*****************************************************/
//Формуємо екран відображення списку функціональних ШГС
/*****************************************************/
void make_ekran_state_analog_inputs(void)
{
  int32_t index_language = index_language_in_array(select_struct_settings_fix()->language);
  
  uint32_t max_row = (current_state_menu2.p_max_row == NULL) ? current_state_menu2.max_row : *current_state_menu2.p_max_row;
  uint32_t position_temp = current_state_menu2.index_position;
  uint32_t index_in_ekran = (position_temp >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;
  for (size_t i = 0; i < MAX_ROW_LCD; i++)
  {
    if (index_in_ekran < max_row)
    {
      unsigned int index_in_ekran_tmp = index_in_ekran;

      __LN_GROUP_ALARM *arr = (__LN_GROUP_ALARM*)(spca_of_p_prt[ID_FB_GROUP_ALARM - _ID_FB_FIRST_VAR]);
      uint32_t value = arr[index_in_ekran_tmp++/*інкрементую, щоб нумерація з цього моменту починалася з 1*/].NNC;
      unsigned int number_digit_value = max_number_digit_in_number(value);
      
      unsigned int part = 0;
      const uint8_t nnc[MAX_NAMBER_LANGUAGE][2 + 1] = {"КЦ", "КК", "NC", "КЦ"};
      unsigned int number_digit, first_index_number;
            
      size_t k = 0;
      for (size_t j = 0; j < MAX_COL_LCD; j++) 
      {
        if (j < (MAX_COL_LCD - (number_digit_value + 1)))
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
              symbol = name_f_blocks[index_language][ID_FB_GROUP_ALARM - _ID_FB_FIRST_ALL][k];
          
              if (symbol != ' ') 
              {
                working_ekran[i][j] = symbol;
                k++;
               
                break;
              }
              else 
              {
                number_digit = max_number_digit_in_number(index_in_ekran_tmp);
                first_index_number = j;
                part++;

                k = 0;
              }
            }
          case 2:
            {
              if (part == 2)
              {
                if (index_in_ekran_tmp != 0)
                {
                  /*
                  Заповнюємо значення зправа  на ліво
                  індекс = first_index_number + number_digit - 1 - (j - first_index_number) =
                  = first_index_number + number_digit - 1 - j + first_index_number =
                  = 2xfirst_index_number + number_digit - 1 - j =
                  */
                  working_ekran[i][2*first_index_number + number_digit - 1 - j] = (index_in_ekran_tmp % 10) + 0x30;
                  index_in_ekran_tmp /= 10;
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
          case 3:
            {
              uint8_t symbol = nnc[index_language][k++];
              if (symbol == '\0')
              {
                symbol = ' ';
                part++;
                k = 0;
              }
              working_ekran[i][j] = symbol;
            
              break;
            }
          default:
            {
              working_ekran[i][j] = ' ';
              break;
            }
          }
        }
        else if (j == (MAX_COL_LCD - (number_digit_value + 1))) 
        {
          working_ekran[i][j] = ' ';
        }
        else
        {
          /*
          Заповнюємо значення зправа  на ліво
          індекс = (MAX_COL_LCD - number_digit_value) + number_digit - 1 - (j - (MAX_COL_LCD - number_digit_value)) =
          = (MAX_COL_LCD - number_digit_value) + number_digit - 1 - j + (MAX_COL_LCD - number_digit_value) =
          = 2*(MAX_COL_LCD - number_digit_value) + number_digit - 1 - j =
          = 2*MAX_COL_LCD - 2*number_digit_value + number_digit - 1 - j =
          = 2*MAX_COL_LCD - number_digit_value - 1 - j =
          */
           working_ekran[i][2*MAX_COL_LCD - number_digit_value - 1 - j] = (value % 10) + 0x30;
           value /= 10;
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
  current_state_menu2.position_cursor_y = 0;
  //Курсор невидимий
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
