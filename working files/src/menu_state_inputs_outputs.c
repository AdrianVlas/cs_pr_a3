#include "header.h"

#define ROWS_ONE_PART   2

/*****************************************************/
//������� ����������, ������ ������� � � ����
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
������� ���������� �� ����

������ ���������
(1 << BIT_REWRITE) - ������������ ����
(1 << BIT_KEY_DOWN) - �������� ����
(1 << BIT_KEY_UP) - �������� �����
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
//������� ����� ����������� ��������� ������ �����-������
/*****************************************************/
void make_ekran_list_inputs_outputs(void)
{
  const uint8_t name_string[MAX_NAMBER_LANGUAGE][MAX_ROW_INPUT_OUTPUT_M2][MAX_COL_LCD + 1] = 
  {
    {
      " ����.���       ",
      " ����.������    ",
      " ����.�������   "
    },
    {
      " ���� ���       ",
      " ���� �����    ",
      " ���� ������   "
    },
    {
      " Inputs G.Alarms",
      " Inputs state   ",
      " Outputs state  "
    },
    {
      " ����.���       ",
      " ʳ�� ��f����  ",
      " ��f�� ��f����  "
    }
  };
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
        name_string_tmp[index_1 - additional_current][index_2] = name_string[index_language][index_1][index_2];
      }
    }
  }
  unsigned int index_in_ekran = (position_temp >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;
  
  //�������  ����� � ������� �����
  for (size_t i = 0; i < MAX_ROW_LCD; i++)
  {
    //�������� ����� ����� ���������, �� �� ����� ���������� � ������� ������������
    for (size_t j = 0; j < MAX_COL_LCD; j++) 
    {
      working_ekran[i][j] =  (index_in_ekran < (MAX_ROW_INPUT_OUTPUT_M2 - additional_current)) ? name_string_tmp[index_in_ekran][j] : ' ';
    }
    index_in_ekran++;
  }

  //������ �� ���������� ������������ �� ������ �������
  current_state_menu2.position_cursor_x = 0;
  //³���������� ������ �� ��������
  current_state_menu2.position_cursor_y = position_temp & (MAX_ROW_LCD - 1);
  //������ �������
  current_state_menu2.cursor_on = 1;
  //������ �� ����
  current_state_menu2.cursor_blinking_on = 0;
  //�������� �������� ���� �����
  current_state_menu2.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/

/*****************************************************/
/*
������� ���������� �� ���� (��� ������� � ���������� ���������)

������ ���������
(1 << BIT_REWRITE) - ������������ ����
(1 << BIT_KEY_DOWN) - �������� ����
(1 << BIT_KEY_UP) - �������� �����
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
//������� ����� ������ ����� ��� ������
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
      if (current_state_menu2.current_level == ANALOG_INPUTS_MENU2_LEVEL)
      {
        __LN_GROUP_ALARM *arr = (__LN_GROUP_ALARM*)(spca_of_p_prt[ID_FB_GROUP_ALARM - _ID_FB_FIRST_VAR]);
        value = arr[_n].active_state[GROUP_ALARM_OUT_CC >> 3] & (1 << (GROUP_ALARM_OUT_CC & ((1 << 3) - 1)));
      }
      else if (current_state_menu2.current_level == INPUTS_MENU2_LEVEL)
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
  
    //�������  ����� � ������� �����
    for (size_t i = 0; i < ROWS_ONE_PART; i++)
    {
      //�������� ����� ����� ���������, �� �� ����� ����������
      for (size_t j = 0; j < MAX_COL_LCD; j++)
      {
        working_ekran[row + i][j] = name_string[i][j];
      }
    }
    
    in_out += number_inputs_or_outputs_in_row*(MAX_ROW_LCD/ROWS_ONE_PART);
    row += ROWS_ONE_PART;
  }

  //³���������� ������ �� ��������
  current_state_menu2.position_cursor_x = 0;
  //³���������� ������ �� ��������
  current_state_menu2.position_cursor_y = 0;
  //������ ���������
  current_state_menu2.cursor_on = 0;
  //������ �� ����
  current_state_menu2.cursor_blinking_on = 0;
  //�������� �������� ���� �����
  current_state_menu2.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/

/*****************************************************/
//
/*****************************************************/
/*****************************************************/

#undef ROWS_ONE_PART  
