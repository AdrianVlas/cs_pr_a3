#include "header.h"

/*****************************************************/
//������� ����� ����������� ��������� ����������
/*****************************************************/
void make_ekran_list_registrators(void)
{
  const uint8_t name_string[MAX_NAMBER_LANGUAGE][MAX_ROW_LIST_REGISTRATORS_M2][MAX_COL_LCD + 1] = 
  {
    {
      " ������ ������� ",
      " ����� ��������."
    },
    {
      " ������ ����   ",
      " ����� �������."
    },
    {
      " Event Log      ",
      " Diagn.Archive  "
    },
    {
      " ������ ������� ",
      " ����� ��������."
    }
  };

  int index_language = index_language_in_array(settings_fix_prt.language);
  
  unsigned int position_temp = current_state_menu2.index_position;
  unsigned int index_in_ekran = (position_temp >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;
  
  //�������  ����� � ������� �����
  for (size_t i = 0; i < MAX_ROW_LCD; i++)
  {
    //������� ����� ����� ���������, �� �� ����� ���������� � ������� ������������
    if (index_in_ekran < MAX_ROW_LIST_REGISTRATORS_M2)
      for (size_t j = 0; j < MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_language][index_in_ekran][j];
    else
      for (size_t j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = ' ';

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
  //�������� ������� ���� �����
  current_state_menu2.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/

/*****************************************************/
/*
������� ���������� �� ���� ������ ���������� ���������� ����/������� ����

����� ���������
(1 << BIT_REWRITE) - ������������ ����
(1 << BIT_KEY_DOWN) - �������� ����
(1 << BIT_KEY_UP) - �������� �����
*/
/*****************************************************/
void move_into_ekran_event_registraqtors(unsigned int action, int max_row)
{
  if (max_row == 0) current_state_menu2.index_position = 0;
  else
  {
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
}
/*****************************************************/


/*****************************************************/
//������� ����� ����������� ���� ���������� ��������� ����
/*****************************************************/
void make_ekran_list_event_pr_err(void)
{
  int32_t index_language = index_language_in_array(settings_fix_prt.language);
  pr_err_record_check_ok  = false;
  
  if (*current_state_menu2.p_max_row == 0)
  {
    const uint8_t information[MAX_NAMBER_LANGUAGE][2][MAX_COL_LCD + 1] = 
    {
      {
        "      ���       ",
        "    �������     "
      },
      {
        "     ����       ",
        "    ������     "
      },
      {
        "    Records     ",
        "   are absent   "
      },
      {
        "      ���       ",
        "    �������     "
      }
    };

    //�������  ����� � ������� �����
    for (size_t i = 0; i < MAX_ROW_LCD; i++)
    {
      //������� ����� ����� ���������, �� �� ����� ���������� � ������� ������������
        for (size_t j = 0; j < MAX_COL_LCD; j++) working_ekran[i][j] = (i < 2) ? information[index_language][i][j] : ' ';
    }

    //������ �� ���������� ������������ �� ������ �������
    current_state_menu2.position_cursor_x = 0;
    //³���������� ������ �� ��������
    current_state_menu2.position_cursor_y = 0;
    //������ �� �������
    current_state_menu2.cursor_on = 0;
    //������ �� ����
    current_state_menu2.cursor_blinking_on = 0;
  }
  else
  {

    uint32_t position_temp = current_state_menu2.index_position;
    uint32_t index_in_ekran = ((position_temp<<1) >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;
    
    uint32_t record_read_ok, record_check_ok, event_state;
    for (size_t i = 0; i < MAX_ROW_LCD; i++)
    {
      uint32_t index_in_ekran_tmp = index_in_ekran >> 1;
      if (index_in_ekran_tmp < (uint32_t)(*current_state_menu2.p_max_row))
      {
        const uint8_t info_data_corrupted[MAX_NAMBER_LANGUAGE][2][MAX_COL_LCD + 1] = 
        {
          {
            "     ������     ",
            "   ����������   "
          },
          {
            "      ���      ",
            "   ���������   "
          },
          {
            "      Data      ",
            " are corrupted  "
          },
          {
            "     ������     ",
            "   ����������   "
          }
        };
        if ((i & 0x1) == 0)
        {
          //������ ���� � ���� �� ����������� ������
          
          //������ ������� �� ������� ��������� ������
          number_record_of_pr_err_into_menu = index_in_ekran_tmp;
          _SET_STATE(control_tasks_dataflash, TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_MENU_BIT);

          uint32_t delta_time = 0;
          uint32_t time_start = TIM4->CNT;
          while (
                 ((control_tasks_dataflash &  MASKA_FOR_BIT(TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_MENU_BIT )) != 0) &&
                 (delta_time < MAX_TIMEOUT_WAITING_REQUESTED_DATA)  
                )   
          {
            uint32_t current_time_tim4 = TIM4->CNT;

            if (current_time_tim4 >= time_start)
              delta_time = current_time_tim4 - time_start;
            else 
              delta_time = current_time_tim4 + 0x10000 - time_start;

            //������ � Watchdog
            watchdog_routine();
          }
          
          if ((control_tasks_dataflash &  MASKA_FOR_BIT(TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_MENU_BIT )) != 0)
          {
            //�� �� ���������� ���������� ������� � ��������� DataFalash
            record_read_ok = false;
            _CLEAR_STATE(control_tasks_dataflash, TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_MENU_BIT);

            const uint8_t information[MAX_NAMBER_LANGUAGE][2][MAX_COL_LCD + 1] = 
            {
              {
               "    Time-out    ",
               " �������� ����� "
              },
              {
               "    Time-out    ",
               " ���������� ���."
              },
              {
               "    Time-out    ",
               "    is over     "
              },
              {
               "    Time-out    ",
               " �������� ����� "
              }
            };

            //�������  ����� � ������� �����
            for (size_t j = 0; j < MAX_ROW_LCD; j++)
            {
              //������� ����� ����� ���������, �� �� ����� ���������� � ������� ������������
              for (size_t k = 0; k < MAX_COL_LCD; j++) working_ekran[j][k] = (j < 2) ? information[index_language][j][k] : ' ';
            }
            
            //������ �� ���������� ������������ �� ������ �������
            current_state_menu2.position_cursor_x = 0;
            //³���������� ������ �� ��������
            current_state_menu2.position_cursor_y = 0;
            //������ �� �������
            current_state_menu2.cursor_on = 0;
            //������ �� ����
            current_state_menu2.cursor_blinking_on = 0;
            
            //��������� ��������� ���� ����������
            break;
          }
          else
          {
            //³������� ������ ��������� ������ ���������� ���������� ���� � ��������� DataFlash
            record_read_ok = true;
            
            //���������� ����������� �����
            size_t event_number;
            if (buffer_for_menu_read_record[0] == LABEL_START_RECORD_PR_ERR)
            {
              event_number = buffer_for_menu_read_record[8] | ((buffer_for_menu_read_record[9] & 0x7f) << 8);
              if ((event_number >= 1) && (event_number <= _NUMBER_ERRORS))
              {
                event_state = (buffer_for_menu_read_record[9] >> 7) & 0x1;
                record_check_ok = true;
              }
              else record_check_ok = false;
            }
            else record_check_ok = false;
            if (index_in_ekran_tmp == position_temp) 
            {
              pr_err_record_check_ok = record_check_ok;
              if (record_check_ok == true)
              {
                for (size_t j = 0; j < 7; j++) pr_err_into_menu_time_label[j] = buffer_for_menu_read_record[1 + j];
              }
            }
            
            if (record_check_ok == true)
            {
              const uint8_t name_string[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_DIAGNOSTYKA][MAX_COL_LCD + 1] = 
              {
                {
                  NAME_DIAGN_RU
                },
                {
                  NAME_DIAGN_UA
                },
                {
                  NAME_DIAGN_EN
                },
                {
                  NAME_DIAGN_KZ
                }
              };
              for (size_t j = 0; j < MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_language][event_number - 1][j];
            }
            else
            {
              for (size_t j = 0; j < MAX_COL_LCD; j++) working_ekran[i][j] = info_data_corrupted[index_language][0][j];
            }
          }
        }
        else
        {
          //������ ���� � ���� �� ����������� ������
          
          if (record_check_ok == true)
          {
            const uint8_t passive_active[MAX_NAMBER_LANGUAGE][2][5] = 
            {
              {"����.", "���. "},
              {"���. ", "���. "},
              {"Pass.", "Act. "},
              {"����.", "���. "}
            };
            
           uint32_t number = index_in_ekran_tmp;
            uint32_t number_digit = max_number_digit_in_number(number);
            for (size_t j = 0; j < MAX_COL_LCD; j++) 
            {
              if (j < 5)
              {
                working_ekran[i][j] = passive_active[index_language][event_state][j];
              }
              else
              {
                if (j < (MAX_COL_LCD - number_digit)) working_ekran[i][j] = ' ';
                else
                {
                  working_ekran[i][2*MAX_COL_LCD - number_digit - 1 - j] = (number % 10) + 0x30;
                  number /= 10;
                }
              }
            }
          }
          else
          {
            for (size_t j = 0; j < MAX_COL_LCD; j++) working_ekran[i][j] = info_data_corrupted[index_language][1][j];
          }
        }
      }
      else
      {
        for (size_t j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = ' ';
      }
      
      index_in_ekran++;
    }
  
    if (record_read_ok == true)
    {
      //������ �� ���������� ������������ �� ������ �������
      current_state_menu2.position_cursor_x = 0;
      //³���������� ������ �� ��������
      current_state_menu2.position_cursor_y = (position_temp<<1) & (MAX_ROW_LCD - 1);
      //������ �������
      current_state_menu2.cursor_on = 1;
      //������ �� ����
      current_state_menu2.cursor_blinking_on = 0;
    }
  }
  //�������� ������� ���� �����
  current_state_menu2.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/

/*****************************************************/
//������� ����� ����������� ���� ���������� ��������� ����
/*****************************************************/
void make_ekran_data_pr_err(void)
{
  uint8_t name_string[2][MAX_COL_LCD + 1] = 
  {
    "   XX-XX-20XX    ",
    "   XX:XX:XX.XX   "
  };
  
  /******************************************/
  //���������� ���� ���������� �������
  /******************************************/
  //����
  name_string[ROW_R_Y_][COL_DY1_R] = (pr_err_into_menu_time_label[4] >>  4) + 0x30;
  name_string[ROW_R_Y_][COL_DY2_R] = (pr_err_into_menu_time_label[4] & 0xf) + 0x30;

  //̳����
  name_string[ROW_R_Y_][COL_MY1_R] = (pr_err_into_menu_time_label[5] >>  4) + 0x30;
  name_string[ROW_R_Y_][COL_MY2_R] = (pr_err_into_menu_time_label[5] & 0xf) + 0x30;

  //г�
  name_string[ROW_R_Y_][COL_SY1_R] = (pr_err_into_menu_time_label[6] >>  4) + 0x30;
  name_string[ROW_R_Y_][COL_SY2_R] = (pr_err_into_menu_time_label[6] & 0xf) + 0x30;

  //������
  name_string[ROW_R_T_][COL_HT1_R] = (pr_err_into_menu_time_label[3] >>  4) + 0x30;
  name_string[ROW_R_T_][COL_HT2_R] = (pr_err_into_menu_time_label[3] & 0xf) + 0x30;

  //�������
  name_string[ROW_R_T_][COL_MT1_R] = (pr_err_into_menu_time_label[2] >>  4) + 0x30;
  name_string[ROW_R_T_][COL_MT2_R] = (pr_err_into_menu_time_label[2] & 0xf) + 0x30;

  //�������
  name_string[ROW_R_T_][COL_ST1_R] = (pr_err_into_menu_time_label[1] >>  4) + 0x30;
  name_string[ROW_R_T_][COL_ST2_R] = (pr_err_into_menu_time_label[1] & 0xf) + 0x30;

  //��� ������
  name_string[ROW_R_T_][COL_HST1_R] = (pr_err_into_menu_time_label[0] >>  4) + 0x30;
  name_string[ROW_R_T_][COL_HST2_R] = (pr_err_into_menu_time_label[0] & 0xf) + 0x30;

  //�������  ����� � ������� �����
  for (size_t i = 0; i < MAX_ROW_LCD; i++)
  {
    for (size_t j = 0; j < MAX_COL_LCD; j++)  working_ekran[i][j] = (i < 2) ? name_string[i][j] : ' ';
  }

  //������ �� ���������� ������������ �� ������ �������
  current_state_menu2.position_cursor_x = 0;
  //³���������� ������ �� ��������
  current_state_menu2.position_cursor_y = 0;
  //������ �� �������
  current_state_menu2.cursor_on = 0;
  //������ �� ����
  current_state_menu2.cursor_blinking_on = 0;
  //�������� ������� ���� �����
  current_state_menu2.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/

/*****************************************************/
//
/*****************************************************/
/*****************************************************/
