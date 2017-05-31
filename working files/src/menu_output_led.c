#include "header.h"


/*****************************************************/
//������� ����� ����������� ���� ����������� ����������� ������/��������������
/*****************************************************/
void make_ekran_control_output_led(void)
{
  if (
      (current_state_menu2.edition == ED_WARNING_EDITION_BUSY) ||
      (current_state_menu2.edition == ED_WARNING_ENTER_ESC)
     )   
  {
    enum _edition_stats edition = current_state_menu2.edition;
    make_ekran_about_info(((edition == ED_WARNING_EDITION_BUSY) ? 0 : 1), ((edition == ED_WARNING_EDITION_BUSY) ? information_no_edition : information_out_of_limits));
  }
  else
  {
    int index_language = index_language_in_array(select_struct_settings_fix()->language);
  
    unsigned int position_temp = current_state_menu2.index_position;
    //�������� �� ��� �������� position_temp ������� ��� ����, �� �� ���� ������� �� ������������� ��� ����� (����� + ��������)
    unsigned int index_in_ekran = ((position_temp << 1) >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;

    __id_fb id = (current_state_menu2.current_level == CTRL_OUTPUT_MENU2_LEVEL) ? ID_FB_OUTPUT : ID_FB_LED;
    __settings_for_OUTPUT_LED *p_settings;
    if (current_state_menu2.edition == ED_VIEWING) 
    {
      p_settings = &((((__LN_OUTPUT_LED*)spca_of_p_prt[id - _ID_FB_FIRST_VAR]) + current_state_menu2.number_selection)->settings);
    }
    else if (current_state_menu2.edition == ED_CAN_BE_EDITED) 
    {
      p_settings = (((__settings_for_OUTPUT_LED*)sca_of_p[id - _ID_FB_FIRST_VAR]) + current_state_menu2.number_selection);
    }
    else 
    {
      p_settings = (((__settings_for_OUTPUT_LED*)sca_of_p_edit[id - _ID_FB_FIRST_VAR]) + current_state_menu2.number_selection);
    }
  
    for (size_t i = 0; i < MAX_ROW_LCD; i++)
    {
      unsigned int index_in_ekran_tmp = index_in_ekran >> 1;
    
      if (index_in_ekran_tmp < MAX_INDEX_CTRL_OUTPUT_LED)
      {
        if ((i & 0x1) == 0)
        {
          //� ��������� ����� ����� �������� ���������
          for (size_t j = 0; j < MAX_COL_LCD; j++) working_ekran[i][j] = name_string_output_led_control[index_language][index_in_ekran_tmp][j];
        }
        else
        {
          //� ������� ����� ����� �������� ��������
          if (index_in_ekran_tmp == INDEX_CTRL_OUTPUT_LED_N_T)  
          {
            for (size_t j = 0; j < MAX_COL_LCD; j++) 
            {
              working_ekran[i][j] = information_output_led_control_N_T[index_language][p_settings->control & 0x1][j];
            }
            if (position_temp == index_in_ekran_tmp)
            {
              current_state_menu2.position_cursor_x = cursor_x_output_led_control_N_T[index_language][(p_settings->control >> INDEX_CTRL_OUTPUT_LED_N_T) & 0x1];
            }
          }
          else if (index_in_ekran_tmp == INDEX_CTRL_OUTPUT_LED_C_I)  
          {
            for (size_t j = 0; j < MAX_COL_LCD; j++)
            {
              working_ekran[i][j] = information_output_led_control_C_I[index_language][(p_settings->control >> INDEX_CTRL_OUTPUT_LED_C_I) & 0x1][j];
            }
            if (position_temp == index_in_ekran_tmp)
            {
              current_state_menu2.position_cursor_x = cursor_x_output_led_control_C_I[index_language][(p_settings->control >> INDEX_CTRL_OUTPUT_LED_C_I) & 0x1];
            }
          }
          else if (index_in_ekran_tmp == INDEX_CTRL_OUTPUT_LED_SI_EI)  
          {
            for (size_t j = 0; j < MAX_COL_LCD; j++) 
            {
              working_ekran[i][j] = information_output_led_control_SI_EI[index_language][(p_settings->control >> INDEX_CTRL_OUTPUT_LED_SI_EI) & 0x1][j];
            }
            if (position_temp == index_in_ekran_tmp)
            {
              current_state_menu2.position_cursor_x = cursor_x_output_led_control_SI_EI[index_language][(p_settings->control >> INDEX_CTRL_OUTPUT_LED_SI_EI) & 0x1];
            }
          }
          else if (
                   (index_in_ekran_tmp >= INDEX_CTRL_OUTPUT_LED_MEANDER1) &&
                   (index_in_ekran_tmp <= INDEX_CTRL_OUTPUT_LED_MEANDER2)
                  )   
          {
            unsigned int param_input;
            if (index_in_ekran_tmp == INDEX_CTRL_OUTPUT_LED_MEANDER1)
              param_input = p_settings->param[OUTPUT_LED_MEANDER1];
            else
              param_input = p_settings->param[OUTPUT_LED_MEANDER2];

            if (param_input == 0)
            {
              for (size_t j = 0; j < MAX_COL_LCD; j++) working_ekran[i][j] = information_empty[index_language][j];
              if (position_temp == index_in_ekran_tmp)
              {
                current_state_menu2.position_cursor_x = cursor_x_empty[index_language];
              }
            }
            else
            {
              unsigned int id_input   = (param_input >> SFIFT_PARAM_ID ) & MASKA_PARAM_ID ;
              unsigned int n_input    = (param_input >> SFIFT_PARAM_N  ) & MASKA_PARAM_N  ;
              unsigned int out_input  = (param_input >> SFIFT_PARAM_OUT) & MASKA_PARAM_OUT;
            
              if ((id_input != ID_FB_MEANDER) || (out_input != (MEANDER_OUT + 1)))
              {
                for (size_t j = 0; j < MAX_COL_LCD; j++) working_ekran[i][j] = information_error[index_language][j];
                if (position_temp == index_in_ekran_tmp)
                {
                  current_state_menu2.position_cursor_x = cursor_x_error[index_language];
                }
              }
              else
              {
                unsigned int number_symbols_in_name_tmp = number_symbols_in_name[index_language];
          
                unsigned int number_digit = max_number_digit_in_number(n_input);
                unsigned int empty_before = (MAX_COL_LCD - number_symbols_in_name_tmp - number_digit) >> 1;

                for (size_t j = 0; j < MAX_COL_LCD; j++)
                {
                  if ((j < empty_before) || (j >= (empty_before + number_symbols_in_name_tmp + number_digit))) working_ekran[i][j] = ' ';
                  else if (j < (empty_before + number_symbols_in_name_tmp)) working_ekran[i][j] = value_name[index_language][j - empty_before];
                  else
                  {
                    /*
                    ���������� �������� ������  �� ���
                    ������ = (empty_before + number_symbols_in_name_tmp) + number_digit - 1 - (j - (empty_before + number_symbols_in_name_tmp)) =
                    = (empty_before + number_symbols_in_name_tmp) + number_digit - 1 - j + (empty_before + number_symbols_in_name_tmp) =
                    = 2(empty_before + number_symbols_in_name_tmp) + number_digit - 1 - j =
                    */
                    working_ekran[i][2*(empty_before + number_symbols_in_name_tmp) + number_digit - 1 - j] = (n_input % 10) + 0x30;
                    n_input /= 10;
                  }
                }
                if (position_temp == index_in_ekran_tmp)
                {
                  current_state_menu2.position_cursor_x = empty_before - 1;
                }
              }
            }
          }
        }
      }
      else
        for (size_t j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = ' ';

      index_in_ekran++;
    }

    //³���������� ������ �� �������� � ������ ������ �� ���� � ��� �� ��������� ������
    current_state_menu2.position_cursor_y = ((position_temp << 1) + 1) & (MAX_ROW_LCD - 1);
    //������ �������
    current_state_menu2.cursor_on = 1;
    //������ �� ����
    if(current_state_menu2.edition <= ED_CAN_BE_EDITED) current_state_menu2.cursor_blinking_on = 0;
    else current_state_menu2.cursor_blinking_on = 1;
    //�������� ������� ���� �����
  }
  current_state_menu2.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/

/*****************************************************/
/*
������������ Enter � ��� ����������� ����������� ������/��������������
*/
/*****************************************************/
enum _result_pressed_enter_during_edition press_enter_in_control_output_led(void)
{
  __id_fb id = (current_state_menu2.current_level == CTRL_OUTPUT_MENU2_LEVEL) ? ID_FB_OUTPUT : ID_FB_LED;
  enum _result_pressed_enter_during_edition result = RPEDE_NONE;
  switch (current_state_menu2.edition)
  {
  case ED_EDITION:
    {
      //����������, �� ��� ������ ��������
      result = RPEDE_DATA_NOT_CHANGED;
      
      __settings_for_OUTPUT_LED *p_settings_edit = (((__settings_for_OUTPUT_LED*)sca_of_p_edit[id - _ID_FB_FIRST_VAR]) + current_state_menu2.number_selection);
      __settings_for_OUTPUT_LED *p_settings_cont = (((__settings_for_OUTPUT_LED*)sca_of_p[id - _ID_FB_FIRST_VAR]) + current_state_menu2.number_selection);

      if (
          (p_settings_cont->control != p_settings_edit->control) ||
          (p_settings_cont->param[OUTPUT_LED_MEANDER1] !=  p_settings_edit->param[OUTPUT_LED_MEANDER1]) ||
          (p_settings_cont->param[OUTPUT_LED_MEANDER2] != p_settings_edit->param[OUTPUT_LED_MEANDER2]) 
         )   
      {
        if (
            ((p_settings_edit->control & ((uint32_t)(~MASKA_CTRL_OUTPUT_LED_M2))) == 0) &&
            (((p_settings_edit->param[OUTPUT_LED_MEANDER1] >> SFIFT_PARAM_N ) & MASKA_PARAM_N) <= current_config.n_meander) &&
            (((p_settings_edit->param[OUTPUT_LED_MEANDER2] >> SFIFT_PARAM_N ) & MASKA_PARAM_N) <= current_config.n_meander)
           )   
        {
          p_settings_cont->control = p_settings_edit->control;
          p_settings_cont->param[OUTPUT_LED_MEANDER1] = p_settings_edit->param[OUTPUT_LED_MEANDER1];
          p_settings_cont->param[OUTPUT_LED_MEANDER2] = p_settings_edit->param[OUTPUT_LED_MEANDER2];
          
          config_settings_modified |= MASKA_CHANGED_SETTINGS;
          result = RPEDE_DATA_CHANGED_OK;
        }
        else result = RPEDE_DATA_CHANGED_OUT_OF_RANGE;
      }

      break;
    }
  }
  
  return result;
}
/*****************************************************/

/*****************************************************/
/*
������������ ESC � ��� ����������� ������/��������������
*/
/*****************************************************/
void press_esc_in_control_output_led(void)
{
  __id_fb id = (current_state_menu2.current_level == CTRL_OUTPUT_MENU2_LEVEL) ? ID_FB_OUTPUT : ID_FB_LED;

  __settings_for_OUTPUT_LED *p_settings_edit = (((__settings_for_OUTPUT_LED*)sca_of_p_edit[id - _ID_FB_FIRST_VAR]) + current_state_menu2.number_selection);
  __settings_for_OUTPUT_LED *p_settings_cont = (((__settings_for_OUTPUT_LED*)sca_of_p[id - _ID_FB_FIRST_VAR]) + current_state_menu2.number_selection);

  p_settings_edit->control = p_settings_cont->control;
  p_settings_edit->param[OUTPUT_LED_MEANDER1] = p_settings_cont->param[OUTPUT_LED_MEANDER1];
  p_settings_edit->param[OUTPUT_LED_MEANDER2] = p_settings_cont->param[OUTPUT_LED_MEANDER2];
}
/*****************************************************/

/*****************************************************/
//���� ����������� ������ ���������� ��� ������/��������������
/*****************************************************
����� ���������
(1 << BIT_KEY_RIGHT)- �������� ������ ��������
(1 << BIT_KEY_LEFT) - �������� ������ ������

����� ���������
  ����
*****************************************************/
void change_control_output_led(unsigned int action)
{
  //������� ����� � �������� ����
  __id_fb id = (current_state_menu2.current_level == CTRL_OUTPUT_MENU2_LEVEL) ? ID_FB_OUTPUT : ID_FB_LED;
  __settings_for_OUTPUT_LED *p_settings_edit = (((__settings_for_OUTPUT_LED*)sca_of_p_edit[id - _ID_FB_FIRST_VAR]) + current_state_menu2.number_selection);

  if (
      ((action & (1 << BIT_KEY_LEFT )) != 0) ||
      ((action & (1 << BIT_KEY_RIGHT)) != 0)
     )   
  {
    int16_t index_position = current_state_menu2.index_position;
    if (
        (index_position == INDEX_CTRL_OUTPUT_LED_N_T) ||
        (index_position == INDEX_CTRL_OUTPUT_LED_C_I) ||
        (index_position == INDEX_CTRL_OUTPUT_LED_SI_EI)
       )  
    {
      p_settings_edit->control ^= (uint32_t)(1 << index_position);
    }
    else 
    {
      int32_t n_meander = current_config.n_meander;
      if (n_meander > 0)
      {
        uint32_t *param_input;
        if (index_position == INDEX_CTRL_OUTPUT_LED_MEANDER1)
        {
          param_input = &(p_settings_edit->param[OUTPUT_LED_MEANDER1]);
        }
        else
        {
          param_input = &(p_settings_edit->param[OUTPUT_LED_MEANDER2]);
        }
      
        int n_input = ((*param_input) >> SFIFT_PARAM_N  ) & MASKA_PARAM_N  ;
        if ((action & (1 << BIT_KEY_RIGHT)) != 0) n_input++;
        else n_input--;
      
        if  (n_input < 1) n_input = n_meander;
        else if (n_input > n_meander) n_input = 1;
        *param_input = ((ID_FB_MEANDER & MASKA_PARAM_ID) << SFIFT_PARAM_ID) | ((n_input & MASKA_PARAM_N) << SFIFT_PARAM_N) | (((MEANDER_OUT + 1) & MASKA_PARAM_OUT) << SFIFT_PARAM_OUT);
      }
    }
  }
}
/*****************************************************/

/*****************************************************/
//
/*****************************************************/
/*****************************************************/
