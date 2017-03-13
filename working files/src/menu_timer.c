#include "header.h"

/*****************************************************/
//������� ����� ����������� ������� ���������� ��� �������������������� �������
/*****************************************************/
void make_ekran_delay_timer(void)
{
  if (
      (current_state_menu2.edition == ED_WARNING_EDITION_BUSY) ||
      (current_state_menu2.edition == ED_WARNING_ENTER_ESC)
     )   
  {
    const uint8_t information_about_info[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
    {
      "���.�� ���������",
      "���.�� ���������",
      "Ed.isn't allowed",
      "���.�� ���������",
    };

    const uint8_t information_about_error[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
    {
      " ���.�� ��������",
      " ���.�� �������",
      "  Out of Limits ",
      "���.�� �������� "
    };

    enum _edition_stats edition = current_state_menu2.edition;
    make_ekran_about_info(((edition == ED_WARNING_EDITION_BUSY) ? false : true), ((edition == ED_WARNING_EDITION_BUSY) ? information_about_info : information_about_error));
  }
  else
  {
    const uint8_t name_string[MAX_NAMBER_LANGUAGE][TIMER_SET_DELAYS][MAX_COL_LCD + 1] = 
    {
      {
        "  ������ �����  ",
        " ������ ������  "
      },
      {
        "  ������ �����  ",
        " ������ ������  "
      },
      {
        "  Pause Timer   ",
        " Operation Timer"
      },
      {
        "  ������ �����  ",
        " ������ ������  "
      }
    };
    
    int index_language = index_language_in_array(select_struct_settings_fix()->language);
  
    unsigned int position_temp = current_state_menu2.index_position;
    //�������� �� ��� �������� position_temp ������� ��� ����, �� �� ���� ������� �� ������������� ��� ����� (����� + ��������)
    unsigned int index_in_ekran = ((position_temp << 1) >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;
  
    unsigned int first_symbol;
    uint32_t vaga, value;
  
    __settings_for_TIMER *p_settings_for_timer;
    if (current_state_menu2.edition == ED_VIEWING) p_settings_for_timer = &((((__LN_TIMER*)spca_of_p_prt[ID_FB_TIMER - _ID_FB_FIRST_VAR]) + current_state_menu2.number_selection)->settings);
    else if (current_state_menu2.edition == ED_CAN_BE_EDITED) p_settings_for_timer = (((__settings_for_TIMER*)sca_of_p[ID_FB_TIMER - _ID_FB_FIRST_VAR]) + current_state_menu2.number_selection);
    else p_settings_for_timer = (((__settings_for_TIMER*)sca_of_p_edit[ID_FB_TIMER - _ID_FB_FIRST_VAR]) + current_state_menu2.number_selection);
    size_t col_begin, col_end, col_comma;
  
    for (size_t i = 0; i < MAX_ROW_LCD; i++)
    {
      unsigned int index_in_ekran_tmp = index_in_ekran >> 1;
      if (index_in_ekran_tmp < TIMER_SET_DELAYS)
      {
        if ((i & 0x1) == 0)
        {
          //� ��������� ����� ����� �������� ���������
          for (size_t j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_language][index_in_ekran_tmp][j];
          first_symbol = 0; //�������, �� �� ������ �������� ������ �� ���������

          switch (index_in_ekran_tmp)
          {
          case TIMER_SET_DELAY_PAUSE:
            {
              vaga = 100000; //������������ ������� ����������
              col_begin = COL_DELAY_TIMER_PAUSE_BEGIN;
              col_end = COL_DELAY_TIMER_PAUSE_END;
              col_comma = COL_DELAY_TIMER_PAUSE_COMMA;
            
              value = p_settings_for_timer->set_delay[TIMER_SET_DELAY_PAUSE];
            
              break;
            }
          case TIMER_SET_DELAY_WORK:
            {
              vaga = 100000; //������������ ������� ����������
              col_begin = COL_DELAY_TIMER_WORK_BEGIN;
              col_end = COL_DELAY_TIMER_WORK_END;
              col_comma = COL_DELAY_TIMER_WORK_COMMA;
            
              value = p_settings_for_timer->set_delay[TIMER_SET_DELAY_WORK];
            
              break;
            }
          }
        }
        else
        {
          //� ������� ����� ����� �������� ��������
          for (size_t j = 0; j < MAX_COL_LCD; j++)
          {
            if (
                ((j < col_begin) ||  (j > col_end )) &&
                (j != (col_end + 2))
               )working_ekran[i][j] = ' ';
            else if (j == col_comma )working_ekran[i][j] = ',';
            else if (j == (col_end + 2)) working_ekran[i][j] = odynyci_vymirjuvannja[index_language][INDEX_SECOND];
            else
              calc_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol, j, col_comma, 0);
          }
        }
        
      }
      else
        for (size_t j = 0; j < MAX_COL_LCD; j++) working_ekran[i][j] = ' ';

      index_in_ekran++;
    }

    //³���������� ������ �� �������� � ������ ������ �� ���� � ��� �� ��������� ������
    current_state_menu2.position_cursor_y = ((position_temp<<1) + 1) & (MAX_ROW_LCD - 1);
    //������ �� ���������� ������������ �� ������� ������ � �������, ���� �� �� � ����� �����������, ������ ������� ���� ��������� � ������ main_manu_function_ver2
    if (current_state_menu2.edition <= ED_CAN_BE_EDITED)
    {
      int last_position_cursor_x = MAX_COL_LCD;
      switch (current_state_menu2.index_position)
      {
      case TIMER_SET_DELAY_PAUSE:
        {
          current_state_menu2.position_cursor_x = COL_DELAY_TIMER_PAUSE_BEGIN;
          last_position_cursor_x = COL_DELAY_TIMER_PAUSE_END;
          break;
        }
      case TIMER_SET_DELAY_WORK:
        {
          current_state_menu2.position_cursor_x = COL_DELAY_TIMER_WORK_BEGIN;
          last_position_cursor_x = COL_DELAY_TIMER_WORK_END;
          break;
        }
      }

      //ϳ������� ������ �� ������� �������
      while (
             ((working_ekran[current_state_menu2.position_cursor_y][current_state_menu2.position_cursor_x + 1]) == ' ') && 
             (current_state_menu2.position_cursor_x < (last_position_cursor_x -1))
             )
      {
        current_state_menu2.position_cursor_x++;
      }

      //������ ������� ���, ��� �� ��� ����� ������
      if (
          ((working_ekran[current_state_menu2.position_cursor_y][current_state_menu2.position_cursor_x]) != ' ') && 
          (current_state_menu2.position_cursor_x > 0)
         )
      {
        current_state_menu2.position_cursor_x--;
      }
    }
    //������ �������
    current_state_menu2.cursor_on = 1;
    //������ �� ����
    if(current_state_menu2.edition <= ED_CAN_BE_EDITED) current_state_menu2.cursor_blinking_on = 0;
    else current_state_menu2.cursor_blinking_on = 1;
  }
  //�������� �������� ���� �����
  current_state_menu2.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/

/*****************************************************/
/*
������������ Enter � ���� ����������� �������� �������������������� �������
*/
/*****************************************************/
enum _result_pressed_enter_during_edition press_enter_in_delay_timer(void)
{
  enum _result_pressed_enter_during_edition result = RPEDE_NONE;
  switch (current_state_menu2.edition)
  {
  case ED_VIEWING:
  case ED_CAN_BE_EDITED:
    {
      switch (current_state_menu2.index_position)
      {
      case TIMER_SET_DELAY_PAUSE:
        {
          current_state_menu2.position_cursor_x = COL_DELAY_TIMER_PAUSE_BEGIN;
          break;
        }
      case TIMER_SET_DELAY_WORK:
        {
          current_state_menu2.position_cursor_x = COL_DELAY_TIMER_WORK_BEGIN;
          break;
        }
      }
      break;
    }
  case ED_EDITION:
    {
      //����������, �� ���� ������ ��������
      result = RPEDE_DATA_NOT_CHANGED;
      
      __settings_for_TIMER *p_settings_for_timer_edit = (((__settings_for_TIMER*)sca_of_p_edit[ID_FB_TIMER - _ID_FB_FIRST_VAR]) + current_state_menu2.number_selection);
      __settings_for_TIMER *p_settings_for_timer_cont = (((__settings_for_TIMER*)sca_of_p[ID_FB_TIMER - _ID_FB_FIRST_VAR]) + current_state_menu2.number_selection);
      switch (current_state_menu2.index_position)
      {
      case TIMER_SET_DELAY_PAUSE:
        {
          if (p_settings_for_timer_cont->set_delay[TIMER_SET_DELAY_PAUSE] != p_settings_for_timer_edit->set_delay[TIMER_SET_DELAY_PAUSE]) 
          {
            if (check_data_setpoint(p_settings_for_timer_edit->set_delay[TIMER_SET_DELAY_PAUSE], TIMEOUT_TIMER_PAUSE_MIN, TIMEOUT_TIMER_PAUSE_MAX) == 1)
            {
              p_settings_for_timer_cont->set_delay[TIMER_SET_DELAY_PAUSE] = p_settings_for_timer_edit->set_delay[TIMER_SET_DELAY_PAUSE];
              config_settings_modified |= MASKA_CHANGED_SETTINGS;
              result = RPEDE_DATA_CHANGED_OK;
            }
            else result = RPEDE_DATA_CHANGED_OUT_OF_RANGE;
          }

          break;
        }
      case TIMER_SET_DELAY_WORK:
        {
          if (p_settings_for_timer_cont->set_delay[TIMER_SET_DELAY_WORK] != p_settings_for_timer_edit->set_delay[TIMER_SET_DELAY_WORK]) 
          {
            if (check_data_setpoint(p_settings_for_timer_edit->set_delay[TIMER_SET_DELAY_WORK], TIMEOUT_TIMER_WORK_MIN, TIMEOUT_TIMER_WORK_MAX) == 1)
            {
              p_settings_for_timer_cont->set_delay[TIMER_SET_DELAY_WORK] = p_settings_for_timer_edit->set_delay[TIMER_SET_DELAY_WORK];
              config_settings_modified |= MASKA_CHANGED_SETTINGS;
              result = RPEDE_DATA_CHANGED_OK;
            }
            else result = RPEDE_DATA_CHANGED_OUT_OF_RANGE;
          }

          break;
        }
      }

      break;
    }
  }
  
  return result;
}
/*****************************************************/

/*****************************************************/
/*
������������ ESC � ���� �������� �������������������� �������
*/
/*****************************************************/
void press_esc_in_delay_timer(void)
{
  __settings_for_TIMER *p_settings_for_timer_edit = (((__settings_for_TIMER*)sca_of_p_edit[ID_FB_TIMER - _ID_FB_FIRST_VAR]) + current_state_menu2.number_selection);
  __settings_for_TIMER *p_settings_for_timer_cont = (((__settings_for_TIMER*)sca_of_p[ID_FB_TIMER - _ID_FB_FIRST_VAR]) + current_state_menu2.number_selection);
  switch (current_state_menu2.index_position)
  {
  case TIMER_SET_DELAY_PAUSE:
    {
      p_settings_for_timer_edit->set_delay[TIMER_SET_DELAY_PAUSE] = p_settings_for_timer_cont->set_delay[TIMER_SET_DELAY_PAUSE];
      break;
    }
  case TIMER_SET_DELAY_WORK:
    {
      p_settings_for_timer_edit->set_delay[TIMER_SET_DELAY_WORK] = p_settings_for_timer_cont->set_delay[TIMER_SET_DELAY_WORK];
      break;
    }
  }
}
/*****************************************************/

/*****************************************************/
//���� �������� ��-�������
/*****************************************************
������ ���������
(1 << BIT_KEY_DOWN) - �������� ������ ����
(1 << BIT_KEY_UP)   - �������� ������ �����
(1 << BIT_KEY_RIGHT)- �������� ������ ��������
(1 << BIT_KEY_LEFT) - �������� ������ ������

������ ���������
  ����
*****************************************************/
void change_delay_timer(unsigned int action)
{
  //������� ����� � �������� ����
  if (action & ((1 << BIT_KEY_DOWN) | (1 << BIT_KEY_UP)))
  {
    int32_t *p_value = (((__settings_for_TIMER*)sca_of_p_edit[ID_FB_TIMER - _ID_FB_FIRST_VAR]) + current_state_menu2.number_selection)->set_delay;
    unsigned int col_end, col_comma;
    switch (current_state_menu2.index_position)
    {
    case TIMER_SET_DELAY_PAUSE:
      {
        col_end = COL_DELAY_TIMER_PAUSE_END;
        col_comma = COL_DELAY_TIMER_PAUSE_COMMA;
        break;
      }
    case TIMER_SET_DELAY_WORK:
      {
        col_end = COL_DELAY_TIMER_WORK_END;
        col_comma = COL_DELAY_TIMER_WORK_COMMA;
        break;
      }
    }
    
    intptr_t index = current_state_menu2.index_position;
    p_value[index] = edit_setpoint(((action & (1 << BIT_KEY_UP)) != 0), p_value[index], 1, col_comma, col_end, 10);
  }
  else if (
           ((action & (1 << BIT_KEY_LEFT )) != 0) ||
           ((action & (1 << BIT_KEY_RIGHT)) != 0)
          )   
  {
    int col_begin, col_end, col_comma;
    switch (current_state_menu2.index_position)
    {
    case TIMER_SET_DELAY_PAUSE:
      {
        col_begin = COL_DELAY_TIMER_PAUSE_BEGIN;
        col_end = COL_DELAY_TIMER_PAUSE_END;
        col_comma = COL_DELAY_TIMER_PAUSE_COMMA;
        break;
      }
    case TIMER_SET_DELAY_WORK:
      {
        col_begin = COL_DELAY_TIMER_WORK_BEGIN;
        col_end = COL_DELAY_TIMER_WORK_END;
        col_comma = COL_DELAY_TIMER_WORK_COMMA;
        break;
      }
    }
    
    if (action & (1 << BIT_KEY_LEFT ))
    {
      current_state_menu2.position_cursor_x--;
      if (current_state_menu2.position_cursor_x == col_comma )current_state_menu2.position_cursor_x--;
      if ((current_state_menu2.position_cursor_x < col_begin) ||
          (current_state_menu2.position_cursor_x > col_end))
        current_state_menu2.position_cursor_x = col_end;
    }
    else
    {
      current_state_menu2.position_cursor_x++;
      if (current_state_menu2.position_cursor_x == col_comma )current_state_menu2.position_cursor_x++;
      if ((current_state_menu2.position_cursor_x < col_begin) ||
          (current_state_menu2.position_cursor_x > col_end))
        current_state_menu2.position_cursor_x = col_begin;
    }
    
  }
}
/*****************************************************/

/*****************************************************/
//
/*****************************************************/
/*****************************************************/
