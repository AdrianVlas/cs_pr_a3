#include "header.h"

/*****************************************************/
//������� ���� � ��� ����������� �� ���� ��������
/*****************************************************/
void main_manu_function(void)
{
  //���������� �� ����� ������ ���������
  if (new_state_keyboard !=0)
  {
    static unsigned int pervynna_vtorynna; //���� ��� ����������� ��� ������� �� �������� ������, ��� �� �������� �������
    
    //�������� � ����� �� ����� �������� ������ � �������� �������� 䳿
    switch (current_ekran.current_level)
    {
/******************************************************************************************************************************************/ 
    case EKRAN_LEVEL_PASSWORD:
    case EKRAN_LEVEL_PASSWORD_HARD:
      {
        //����� ��� �������� ����� ������� � ����������� ���� ����
        static __PREVIOUS_STATE_CURSOR previous_state_cursor;
        //����� ��� �������� ��������� ������
        static unsigned int new_password;
        static unsigned int number_symbols;
        
        //������� �� ��� ���� �����������
        new_state_keyboard &= (1<<BIT_KEY_ENTER)|(1<<BIT_KEY_ESC)|(1<<BIT_KEY_UP)|(1<<BIT_KEY_DOWN)|(1<<BIT_KEY_RIGHT)|(1<<BIT_KEY_LEFT)|(1<<BIT_REWRITE);

        if (new_state_keyboard !=0)
        {
          //�������� ����� �� ��������� ������
          if((new_state_keyboard & (1<<BIT_REWRITE)) !=0)
          {
            previous_state_cursor.position_cursor_x = current_ekran.position_cursor_x;              
            previous_state_cursor.cursor_on = current_ekran.cursor_on;
            previous_state_cursor.cursor_blinking_on = current_ekran.cursor_blinking_on;
            current_ekran.cursor_on = 1;
            current_ekran.cursor_blinking_on = 1;
            current_ekran.position_cursor_x = COL_NEW_PASSWORD_BEGIN;
            position_in_current_level_menu[current_ekran.current_level] = 1;
            //������� ����� ������ � ���� � ������� ������� �������� �������
            new_password = 0;
            number_symbols = 0;
            
            //������� ����� ���� password
            make_ekran_level_password(new_password, 0);
            //������� �� ���������� ������
            new_state_keyboard &= (unsigned int)(~(1<<BIT_REWRITE));
          }
          else
          {
            if (new_state_keyboard == (1<<BIT_KEY_ENTER))
            {
              //��������� ������ ENTER
              unsigned int password;
              if (current_ekran.current_level == EKRAN_LEVEL_PASSWORD)
                password = current_settings.password1;
              else if (current_ekran.current_level == EKRAN_LEVEL_PASSWORD_HARD)
                password = current_settings.password2;
              else
              {
                //���������� ����� ������ �� ���� � ����
                total_error_sw_fixed(70);
              }

              if (new_password == password)
              {
                //������ �������
                //���������� � ��������� ���� � ����� �����������
                current_ekran.current_level = previous_level_in_current_level_menu[current_ekran.current_level];
                current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
                current_ekran.edition = 1;
                current_ekran.position_cursor_x = previous_state_cursor.position_cursor_x;
                current_ekran.cursor_on = previous_state_cursor.cursor_on;
                current_ekran.cursor_blinking_on = previous_state_cursor.cursor_blinking_on;
              }
              else
              {
                //������ �� �������
                //���������� � ��������� ���� � ���������� ������ �����������
                current_ekran.current_level = previous_level_in_current_level_menu[current_ekran.current_level];
                current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
                current_ekran.edition = 0;
                current_ekran.position_cursor_x = previous_state_cursor.position_cursor_x;
                current_ekran.cursor_on = previous_state_cursor.cursor_on;
                current_ekran.cursor_blinking_on = previous_state_cursor.cursor_blinking_on;
              }

              //�������� �����������, �� ��������� ������ 
              new_state_keyboard &= (unsigned int)(~(1<<BIT_KEY_ENTER));
              //����������� �� ���������� ������
              new_state_keyboard |= (1<<BIT_REWRITE);
            }
            else if (new_state_keyboard == (1<<BIT_KEY_ESC))
            {
              //��������� ������ ESC

              //���������� � ��������� ���� � ���������� ������ �����������
              current_ekran.current_level = previous_level_in_current_level_menu[current_ekran.current_level];
              current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
              current_ekran.edition = 0;
              current_ekran.position_cursor_x = previous_state_cursor.position_cursor_x;
              current_ekran.cursor_on = previous_state_cursor.cursor_on;
              current_ekran.cursor_blinking_on = previous_state_cursor.cursor_blinking_on;
              
              //�������� �����������, �� ��������� ������ 
              new_state_keyboard &= (unsigned int)(~(1<<BIT_KEY_ESC));
              //����������� �� ���������� ������
              new_state_keyboard |= (1<<BIT_REWRITE);
            }
            else if (new_state_keyboard == (1<<BIT_KEY_UP))
            {
              //��������� ������ UP
              new_password = new_password*10 + 1;
              number_symbols++;
              current_ekran.position_cursor_x++;
              
              //������� ����� ���� password
              make_ekran_level_password(new_password, 1);
              //�������� �����������, �� ��������� ������ 
              new_state_keyboard &= (unsigned int)(~(1<<BIT_KEY_UP));
              //���������� �� �� ��������� ����������� ������� ������� ��� ������ (4) � ���� �� ���, �� ����������� �������� ����
              if (number_symbols >= 4) new_state_keyboard |= (1<<BIT_KEY_ENTER);
            }
            else if (new_state_keyboard == (1<<BIT_KEY_DOWN))
            {
              //��������� ������ DOWN
              new_password = new_password*10 + 3;
              number_symbols++;
              current_ekran.position_cursor_x++;

              //������� ����� ���� password
              make_ekran_level_password(new_password, 1);
              //�������� �����������, �� ��������� ������ 
              new_state_keyboard &= (unsigned int)(~(1<<BIT_KEY_DOWN));
              //���������� �� �� ��������� ����������� ������� ������� ��� ������ (4) � ���� �� ���, �� ����������� �������� ����
              if (number_symbols >= 4) new_state_keyboard |= (1<<BIT_KEY_ENTER);
            }
            else if (new_state_keyboard == (1<<BIT_KEY_RIGHT))
            {
              //��������� ������ RIGHT
              new_password = new_password*10 + 2;
              number_symbols++;
              current_ekran.position_cursor_x++;

              //������� ����� ���� password
              make_ekran_level_password(new_password, 1);
              //�������� �����������, �� ��������� ������ 
              new_state_keyboard &= (unsigned int)(~(1<<BIT_KEY_RIGHT));
              //���������� �� �� ��������� ����������� ������� ������� ��� ������ (4) � ���� �� ���, �� ����������� �������� ����
              if (number_symbols >= 4) new_state_keyboard |= (1<<BIT_KEY_ENTER);
            }
            else if (new_state_keyboard == (1<<BIT_KEY_LEFT))
            {
              //��������� ������ LEFT
              new_password = new_password*10 + 4;
              number_symbols++;
              current_ekran.position_cursor_x++;

              //������� ����� ���� password
              make_ekran_level_password(new_password, 1);
              //�������� �����������, �� ��������� ������ 
              new_state_keyboard &= (unsigned int)(~(1<<BIT_KEY_LEFT));
              //���������� �� �� ��������� ����������� ������� ������� ��� ������ (4) � ���� �� ���, �� ����������� �������� ����
              if (number_symbols >= 4) new_state_keyboard |= (1<<BIT_KEY_ENTER);
            }
            else
            {
              //��������� ����� ������� ������ - �� � ����������� ��������, ���� ������� ����������� ��� �������� ������ � ������ �����
              unsigned int temp_data = new_state_keyboard;
              new_state_keyboard &= ~temp_data;
            }
          }
          
        }
        break;
      }
/******************************************************************************************************************************************/ 

/******************************************************************************************************************************************/ 
    case EKRAN_LEVEL_SET_NEW_PASSWORD1:
    case EKRAN_LEVEL_SET_NEW_PASSWORD2:
      {
        //����� ��� �������� ��������� ������
        static unsigned int new_setting_password;
        static int number_symbols_new_setting_password;
        
        //������� �� ��� ���� �����������
        unsigned int maska_keyboard_bits = (1<<BIT_KEY_ENTER)| (1<<BIT_KEY_ESC)|(1<<BIT_REWRITE);
        
        if (current_ekran.edition == 1)
          maska_keyboard_bits |= (1<<BIT_KEY_RIGHT) | (1<<BIT_KEY_LEFT) | (1<<BIT_KEY_UP)|(1<<BIT_KEY_DOWN);
        
        new_state_keyboard &= maska_keyboard_bits;

        if (new_state_keyboard !=0)
        {
          unsigned int *p_password;
          if (current_ekran.current_level == EKRAN_LEVEL_SET_NEW_PASSWORD1)
            p_password = &current_settings.password1;
          else if (current_ekran.current_level == EKRAN_LEVEL_SET_NEW_PASSWORD2)
            p_password = &current_settings.password2;
          else
          {
            //���������� ����� ������ �� ���� � ����
            total_error_sw_fixed(69);
          }
            
          //�������� ����� �� ��������� ������
          if((new_state_keyboard & (1<<BIT_REWRITE)) !=0)
          {
            if (current_ekran.edition == 1)
            {
              current_ekran.cursor_on = 1;
              current_ekran.cursor_blinking_on = 1;
              current_ekran.position_cursor_x = COL_NEW_PASSWORD_BEGIN;
              position_in_current_level_menu[current_ekran.current_level] = 1;
              //������������ ��������� �������� ������ ������ � ������� ������� �������� �������
              new_setting_password = *p_password;
              number_symbols_new_setting_password = 0;
              
              unsigned int temp_value = new_setting_password;
              while (temp_value != 0)
              {
                number_symbols_new_setting_password++;
                temp_value /= 10;
              }
              if (number_symbols_new_setting_password == 0) number_symbols_new_setting_password = 1; //�� ������� ���� current_settings.password1 = 0, ��� ������� ������� ���� 0, �� ����� � "0"
            
              //������� ����� ���� password
              make_ekran_level_password(new_setting_password, 1);
              //������� �� ���������� ������
              new_state_keyboard &= (unsigned int)(~(1<<BIT_REWRITE));
            }
            else
            {
              //���������� � ��������� ���� � ���������� ������ �����������
              current_ekran.current_level = previous_level_in_current_level_menu[current_ekran.current_level];
              current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
              current_ekran.edition = 0;
              
              //���, ���� �������� ��� ����������� ������ �� ��������, �� ���� �� ��� ����� ������������
            }
          }
          else
          {
            if (new_state_keyboard == (1<<BIT_KEY_ENTER))
            {
              //��������� ������ ENTER
              if (current_ekran.edition == 1)
              {
                //�������� � ������ �����������
                if (current_settings.password1 == new_setting_password)
                {
                  //���������� �� ���������� �����
                  current_ekran.edition = 0;
                  current_ekran.current_level = previous_level_in_current_level_menu[current_ekran.current_level];
                  current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
                }
                else current_ekran.edition = 2;

                current_ekran.cursor_on = 0;
                current_ekran.cursor_blinking_on = 0;
              }
              else if (current_ekran.edition == 2)
              {
                //�������, �� ���� ��������� ����� ���� ������
                changed_settings = CHANGED_ETAP_EXECUTION;
                        
                //������� ���� �������� � ��
                *p_password = new_setting_password;

                //�������, �� ������� �������� � �� ����� ���� � ������� ������� ��������� � ������� � ���� ������ ������� ������� (��� �� �������� � � ������, �� �� ���� ��� ��� ����, �� ���������������� �������� �������, ��� �� � ������ ��� ��������������, ��� ������ �� ������� ���� ���������)
                changed_settings = CHANGED_ETAP_ENDED;
                
                //�� ������� ����� � ������� ��������� ��� ���� ������������, �� �� �� ���� �� ����. ������ ������� ������ ������� � ����
                //��� ��������� ����� � EEPROM ���������
                //��������� ����� � EEPROM
                if (_CHECK_SET_BIT(active_functions, RANG_SETTINGS_CHANGED) == 0) current_settings_interfaces = current_settings;
                _SET_BIT(control_i2c_taskes, TASK_START_WRITE_SETTINGS_EEPROM_BIT);
                
                //����� � ����� �����������
                current_ekran.edition = 0;
                //���������� �� ���������� �����
                current_ekran.current_level = previous_level_in_current_level_menu[current_ekran.current_level];
                current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
                current_ekran.cursor_on = 0;
                current_ekran.cursor_blinking_on = 0;
              }
              else if (current_ekran.edition == 3)
              {
                //����� � ����� �����������
                current_ekran.edition = 0;
                //���������� �� ���������� �����
                current_ekran.current_level = previous_level_in_current_level_menu[current_ekran.current_level];
                current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
                current_ekran.cursor_on = 0;
                current_ekran.cursor_blinking_on = 0;
              }
              else
              {
                //�� ��� ���� �������� ������ � �� ���� ���� � ������������� ����������� ��� �������
                current_ekran.edition = 3;
              }
                
              if(current_ekran.edition == 2) make_ekran_ask_rewrite();
              else if (current_ekran.edition == 0)
              {
                //����������� �� ���������� ������
                new_state_keyboard |= (1<<BIT_REWRITE);
              }
              else if (current_ekran.edition == 3)
              {
                const unsigned char information_about_error[MAX_NAMBER_LANGUAGE][MAX_COL_LCD] = 
                {
                  " �������.������ ",
                  " ������.������� ",
                  " Undefined error",
                  " �������.������ "
                };
                current_ekran.cursor_on = 0;
                current_ekran.cursor_blinking_on = 0;
                make_ekran_about_error(information_about_error);
              }

              //�������� �����������, �� ��������� ������ 
              new_state_keyboard &= (unsigned int)(~(1<<BIT_KEY_ENTER));
            }
            else if (new_state_keyboard == (1<<BIT_KEY_ESC))
            {
              //��������� ������ ESC

              //���������� � ��������� ���� � ���������� ������ �����������
              current_ekran.current_level = previous_level_in_current_level_menu[current_ekran.current_level];
              current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
              current_ekran.edition = 0;
              
              //�������� �����������, �� ��������� ������ 
              new_state_keyboard &= (unsigned int)(~(1<<BIT_KEY_ESC));
              //����������� �� ���������� ������
              new_state_keyboard |= (1<<BIT_REWRITE);
            }
            else if (new_state_keyboard == (1<<BIT_KEY_UP))
            {
              //��������� ������ UP
              unsigned int vaga = 1, temp_value, ostacha, vyshchi_rozrjady;
              int edit_rozrjad;
              
              for (int i=(current_ekran.position_cursor_x - 5 + 1); i<number_symbols_new_setting_password; i++) vaga *= 10;
              ostacha = new_setting_password % vaga;
              temp_value = (new_setting_password / vaga);
              edit_rozrjad = temp_value % 10;
              vyshchi_rozrjady = temp_value / 10;
              if (++edit_rozrjad > 4) 
              {
                if (ostacha == 0)
                {
                  edit_rozrjad = 0;
                  if (number_symbols_new_setting_password > 1)
                  {
                    number_symbols_new_setting_password--;
                    current_ekran.position_cursor_x--;
                    new_setting_password = vyshchi_rozrjady*vaga;
                  }
                  else
                  {
                    if (current_ekran.current_level != EKRAN_LEVEL_SET_NEW_PASSWORD1) edit_rozrjad = 1;
                    new_setting_password = vyshchi_rozrjady*vaga*10 + edit_rozrjad*vaga; 
                  }
                }
                else
                {
                  edit_rozrjad = 1;
                  new_setting_password = (vyshchi_rozrjady*vaga*10) + edit_rozrjad*vaga + ostacha;
                }
              }
              else
                new_setting_password = (vyshchi_rozrjady*vaga*10) + edit_rozrjad*vaga + ostacha;
              //������� ����� ���� password
              make_ekran_level_password(new_setting_password, 1);
              //�������� �����������, �� ��������� ������ 
              new_state_keyboard &= (unsigned int)(~(1<<BIT_KEY_UP));
            }
            else if (new_state_keyboard == (1<<BIT_KEY_DOWN))
            {
              //��������� ������ DOWN
              unsigned int vaga = 1, temp_value, ostacha, vyshchi_rozrjady;
              int edit_rozrjad;
              for (int i=(current_ekran.position_cursor_x - 5 + 1); i<number_symbols_new_setting_password; i++) vaga *= 10;
              ostacha = new_setting_password % vaga;
              temp_value = (new_setting_password / vaga);
              edit_rozrjad = temp_value % 10;
              vyshchi_rozrjady = temp_value / 10;
              edit_rozrjad--;
              if (edit_rozrjad < 0)
              {
                edit_rozrjad = 4;
                new_setting_password = (vyshchi_rozrjady*vaga*10) + edit_rozrjad*vaga + ostacha;
              }
              else if (edit_rozrjad == 0)
              {
                if ((vyshchi_rozrjady !=0) || (ostacha != 0))
                {
                  if (ostacha == 0)
                  {
                    edit_rozrjad = 0;
                    if (number_symbols_new_setting_password > 1)
                    {
                      number_symbols_new_setting_password--;
                      current_ekran.position_cursor_x--;
                      new_setting_password = vyshchi_rozrjady*vaga;
                    }
                    else
                    {
                      if (current_ekran.current_level != EKRAN_LEVEL_SET_NEW_PASSWORD1) edit_rozrjad = 4;
                      new_setting_password = vyshchi_rozrjady*vaga*10 + edit_rozrjad*vaga;
                    }
                  }
                  else
                  {
                    edit_rozrjad = 4;
                    new_setting_password = (vyshchi_rozrjady*vaga*10) + edit_rozrjad*vaga + ostacha;
                  }
                }
                else
                {
                  if (current_ekran.current_level != EKRAN_LEVEL_SET_NEW_PASSWORD1) new_setting_password = 4;
                  else new_setting_password = 0;
                }
                  
              }
              else
                new_setting_password = (vyshchi_rozrjady*vaga*10) + edit_rozrjad*vaga + ostacha;

              //������� ����� ���� password
              make_ekran_level_password(new_setting_password, 1);
              //�������� �����������, �� ��������� ������ 
              new_state_keyboard &= (unsigned int)(~(1<<BIT_KEY_DOWN));
            }
            else if (new_state_keyboard == (1<<BIT_KEY_RIGHT))
            {
              //��������� ������ RIGHT
              if (new_setting_password !=0)
              {
                if (++current_ekran.position_cursor_x > COL_NEW_PASSWORD_END) current_ekran.position_cursor_x = COL_NEW_PASSWORD_BEGIN;
                if (number_symbols_new_setting_password < (current_ekran.position_cursor_x - COL_NEW_PASSWORD_BEGIN + 1))
                {
                  new_setting_password = new_setting_password*10 + 1;
                  number_symbols_new_setting_password++;
                }
              }

              //������� ����� ���� password
              make_ekran_level_password(new_setting_password, 1);
              //�������� �����������, �� ��������� ������ 
              new_state_keyboard &= (unsigned int)(~(1<<BIT_KEY_RIGHT));
            }
            else if (new_state_keyboard == (1<<BIT_KEY_LEFT))
            {
              //��������� ������ LEFT
              if (new_setting_password !=0)
              {
                if (--current_ekran.position_cursor_x < COL_NEW_PASSWORD_BEGIN) current_ekran.position_cursor_x = COL_NEW_PASSWORD_BEGIN + number_symbols_new_setting_password - 1;
              }

              //������� ����� ���� password
              make_ekran_level_password(new_setting_password, 1);
              //�������� �����������, �� ��������� ������ 
              new_state_keyboard &= (unsigned int)(~(1<<BIT_KEY_LEFT));
            }
            else
            {
              //��������� ����� ������� ������ - �� � ����������� ��������, ���� ������� ����������� ��� �������� ������ � ������ �����
              unsigned int temp_data = new_state_keyboard;
              new_state_keyboard &= ~temp_data;
            }
          }
          
        }
        break;
      }
/******************************************************************************************************************************************/ 
      
/******************************************************************************************************************************************/      
    case EKRAN_MAIN:
      {
        //������� �� ��� ���� �����������
        new_state_keyboard &= (1<<BIT_KEY_ENTER)|(1<<BIT_KEY_UP)|(1<<BIT_KEY_DOWN)|(1<<BIT_REWRITE);
        //������ �������� 䳿, ���� ��������� ������ �� ��� ����� ��������, ��� ����� ������� �������� �����
        if (new_state_keyboard !=0)
        {
          //�������� ����� �� ��������� ������
          if((new_state_keyboard & (1<<BIT_REWRITE)) !=0)
          {
            do
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_EKRAN_MAIN) current_ekran.index_position = 0;
                
              if ((current_ekran.index_position == INDEX_ML1_CTRL_PHASE) && ((current_settings.configuration & (1<<CTRL_PHASE_BIT_CONFIGURATION)) == 0))
                current_ekran.index_position++;
            }
            while (current_ekran.index_position >= MAX_ROW_FOR_EKRAN_MAIN);
            position_in_current_level_menu[EKRAN_MAIN] = current_ekran.index_position;
            
            //������� ����� ���� ��������� ����
            make_ekran_main();
            //������� �� ���������� ������
            new_state_keyboard &= (unsigned int)(~(1<<BIT_REWRITE));
          }
          else
          {
            if (new_state_keyboard == (1<<BIT_KEY_ENTER))
            {
              int temp_current_level = current_ekran.current_level;
              
              //��������� ������ ENTER
              if(current_ekran.index_position == INDEX_ML1_TIME)
              {
                //�����'������� ����������� �����
                //���������� �� ���� ����-���������
                time_rewrite = 0;
                current_ekran.current_level = EKRAN_TIME;
                current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
                current_ekran.edition = 0;
                current_ekran.cursor_on = 0;
                current_ekran.cursor_blinking_on = 0;
                
                /**************************************************/
                //������ �� ���� �� ������� ������ ����� � ������
                /**************************************************/
                if(current_ekran.index_position == ROW_Y_)
                {
                  current_ekran.position_cursor_x = COL_DY1;
                }
                else if(current_ekran.index_position == ROW_T_)
                {
                  current_ekran.index_position = ROW_Y_;
                  current_ekran.position_cursor_x = COL_DY1;
                }
                else if(current_ekran.index_position == ROW_N_)
                {
                  current_ekran.index_position = ROW_K_;
                  current_ekran.position_cursor_x = COL_SK1;
                }
                else if(current_ekran.index_position == ROW_K_)
                {
                  current_ekran.position_cursor_x = COL_SK1;
                }
                /**************************************************/
              }
              else if(current_ekran.index_position == INDEX_ML1_MEASURMENTS)
              {
                //���������� �� ���� ������ ����������� ������� ���� ��������� ���������
                current_ekran.current_level = EKRAN_MEASURMENT;
                current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
                current_ekran.edition = 0;
                current_ekran.cursor_on = 1;
                current_ekran.cursor_blinking_on = 0;
              }
              else if(current_ekran.index_position == INDEX_ML1_INPUTS_OUTPUTS)
              {
                //���������� �� ���� ������ ����������� ������ ������ �����-������ ��� ����������� �� �������� �����
                current_ekran.current_level = EKRAN_LIST_INPUTS_OUTPUTS;
                current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
              }
              else if(current_ekran.index_position == INDEX_ML1_REGISTRATORS)
              {
                //���������� �� ���� ������ ����������� ������ ����������
                current_ekran.current_level = EKRAN_LIST_REGISTRATORS;
                current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
              }
              else if(current_ekran.index_position == INDEX_ML1_LANGUAGE)
              {
                //���������� �� ���� ������ ���� ����������� ����
                current_ekran.current_level = EKRAN_VIEW_SETTING_LANGUAGE;
                current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
              }
              else if(current_ekran.index_position == INDEX_ML1_SETTINGS)
              {
                //���������� �� ���� ���������
                current_ekran.current_level = EKRAN_CHOSE_SETTINGS;
                current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
                current_ekran.edition = 0;
                current_ekran.cursor_on = 1;
                current_ekran.cursor_blinking_on = 0;
              }
              else if(current_ekran.index_position == INDEX_ML1_DIAGNOSTYKA)
              {
                //���������� �� ���� ���������
                current_ekran.current_level = EKRAN_DIAGNOSTYKA;
                //��� ����, ��� ��� ������� ��������� ������ ������ ��������� �� ����� ������� ��������� �� �������
                position_in_current_level_menu[current_ekran.current_level] = 0;
                current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
                current_ekran.edition = 0;
              }
              else if(current_ekran.index_position == INDEX_ML1_KONF)
              {
                //���������� �� ���� ������������
                current_ekran.current_level = EKRAN_COFIGURATION;
                current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
                current_ekran.edition = 0;
                current_ekran.cursor_on = 1;
                current_ekran.cursor_blinking_on = 0;
              }
              else if(
                      (current_ekran.index_position == INDEX_ML1_CTRL_PHASE) 
                     )
              {
                //���������� �� ���� �������� ���������
                if(current_ekran.index_position == INDEX_ML1_CTRL_PHASE) current_ekran.current_level = EKRAN_CHOOSE_SETTINGS_CTRL_PHASE;
                
                current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
                current_ekran.edition = 0;
                current_ekran.cursor_on = 1;
                current_ekran.cursor_blinking_on = 0;
              }
              //� ���, ���� ������� ����� �������, �� �����'������� ����� � ���� ����� ���� �����������
              if (temp_current_level != current_ekran.current_level) 
                previous_level_in_current_level_menu[current_ekran.current_level] = temp_current_level;

              //����������� ������� �� ����������� ������ ������
              new_state_keyboard |= (1<<BIT_REWRITE);
              
              //�������� �����������, �� ��������� ������ 
              new_state_keyboard &= (unsigned int)(~(1<<BIT_KEY_ENTER));
            }
            else if (new_state_keyboard == (1<<BIT_KEY_UP))
            {
              //��������� ������ UP
              current_ekran.index_position--;
              do
              {
                if(current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_EKRAN_MAIN - 1;

                if ((current_ekran.index_position == INDEX_ML1_CTRL_PHASE) && ((current_settings.configuration & (1<<CTRL_PHASE_BIT_CONFIGURATION)) == 0))
                  current_ekran.index_position--;
              }
              while (current_ekran.index_position < 0);
              position_in_current_level_menu[EKRAN_MAIN] = current_ekran.index_position;
              
              //������� ����� ���� ��������� ����
              make_ekran_main();
              //�������� �����������, �� ��������� ������ 
              new_state_keyboard &= (unsigned int)(~(1<<BIT_KEY_UP));
            }
            else if (new_state_keyboard == (1<<BIT_KEY_DOWN))
            {
              //��������� ������ DOWN
              //current_ekran.index_position ����� ����� � ������� ������ ����
              current_ekran.index_position++;
              do
              {
                if(current_ekran.index_position >= MAX_ROW_FOR_EKRAN_MAIN) current_ekran.index_position = 0;
 
                if ((current_ekran.index_position == INDEX_ML1_CTRL_PHASE) && ((current_settings.configuration & (1<<CTRL_PHASE_BIT_CONFIGURATION)) == 0))
                  current_ekran.index_position++;
              }
              while (current_ekran.index_position >= MAX_ROW_FOR_EKRAN_MAIN);
              position_in_current_level_menu[EKRAN_MAIN] = current_ekran.index_position;
              
              //������� ����� ���� ��������� ����
              make_ekran_main();
              //�������� �����������, �� ��������� ������ 
              new_state_keyboard &= (unsigned int)(~(1<<BIT_KEY_DOWN));
            }
            else
            {
              //��������� ����� ������� ������ - �� � ����������� ��������, ���� ������� ����������� ��� �������� ������ � ������ �����
              unsigned int temp_data = new_state_keyboard;
              new_state_keyboard &= ~temp_data;
            }
          }
          
        }
        break;
      }
/******************************************************************************************************************************************/ 

/******************************************************************************************************************************************/ 
    case EKRAN_TIME:
      {
        //������� �� ��� ���� �����������
        unsigned int maska_keyboard_bits = (1<<BIT_KEY_ENTER)| (1<<BIT_KEY_ESC)|(1<<BIT_REWRITE);
        
        if (current_ekran.edition == 1)
          maska_keyboard_bits |= (1<<BIT_KEY_RIGHT) | (1<<BIT_KEY_LEFT) | (1<<BIT_KEY_UP)|(1<<BIT_KEY_DOWN);
        else if (current_ekran.edition == 0)
          maska_keyboard_bits |= (1<<BIT_KEY_UP)|(1<<BIT_KEY_DOWN);
        
        new_state_keyboard &= maska_keyboard_bits;
        //������ �������� 䳿, ���� ��������� ������ �� ��� ����� ��������, ��� ����� ������� �������� �����
        if (new_state_keyboard !=0)
        {
          //�������� ����� �� ��������� ������
          if((new_state_keyboard & (1<<BIT_REWRITE)) !=0)
          {
            if(current_ekran.index_position >= MAX_ROW_FOR_EKRAN_TIME) current_ekran.index_position = 0;
            /**************************************************/
            //������ �� ���� �� ������� ������ ����� � ������
            /**************************************************/
            if(current_ekran.index_position == ROW_Y_)
            {
              current_ekran.position_cursor_x = COL_DY1;
            }
            else if(current_ekran.index_position == ROW_T_)
            {
              current_ekran.index_position = ROW_Y_;
              current_ekran.position_cursor_x = COL_DY1;
            }
            else if(current_ekran.index_position == ROW_N_)
            {
              current_ekran.index_position = ROW_K_;
              current_ekran.position_cursor_x = COL_SK1;
            }
            else if(current_ekran.index_position == ROW_K_)
            {
              current_ekran.position_cursor_x = COL_SK1;
            }
            /**************************************************/
            position_in_current_level_menu[EKRAN_TIME] = current_ekran.index_position;

            if (current_ekran.edition == 0)
            {
              current_ekran.cursor_on = 0;
              current_ekran.cursor_blinking_on = 0;
            }

            //������� ����� ������-����
            make_ekran_time();
            //������� �� ���������� ������
            new_state_keyboard &= (unsigned int)(~(1<<BIT_REWRITE));
          }
          else
          {
            if (new_state_keyboard == (1<<BIT_KEY_ENTER))
            {
              //��������� ������ ENTER
              if(current_ekran.edition == 0)
              {
                //������� ������ ����� ���� � ����� ��� �����������
                for(unsigned int i=0; i < 7; i++) time_edit[i] = time[i]; /*��������������� time_copy � calibration_copy �� ����� �� �-��� main_manu_function() � main_routines_for_i2c() ������������ � ���������� ����*/ 
                calibration_edit = calibration;
                  
                //ϳ�������� �� ������ ����������� - �������� �������� ������
                current_ekran.cursor_on = 1;
                current_ekran.cursor_blinking_on = 1;
                if (current_settings.password1 != 0)
                {
                  //���������� �� ���� ������ ������
                  current_ekran.current_level = EKRAN_LEVEL_PASSWORD;
                  previous_level_in_current_level_menu[current_ekran.current_level] = EKRAN_TIME;
                  current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
                }
                else
                {
                  //���������� � ����� �����������
                  current_ekran.edition = 1;
                }
              }
              else if (current_ekran.edition == 1)
              {
                //���������� �� ���� ���� ��������
                unsigned int found_changes = 0, i = 0;
                while ((i < 7) && (found_changes == 0))
                {
                  if (time[i] != time_edit[i]) found_changes = 1; /*��������������� time_copy � calibration_copy �� ����� �� �-��� main_manu_function() � main_routines_for_i2c() ������������ � ���������� ����*/ 
                  i++;
                }
                if (found_changes == 0)
                {
                  if (calibration != calibration_edit) found_changes = 1;/*��������������� time_copy � calibration_copy �� ����� �� �-��� main_manu_function() � main_routines_for_i2c() ������������ � ���������� ����*/ 
                }
                
                //�������� � ������ �����������
                if (found_changes == 0) current_ekran.edition = 0;
                else current_ekran.edition = 2;

                current_ekran.cursor_on = 0;
                current_ekran.cursor_blinking_on = 0;
              }
              else if (current_ekran.edition == 2)
              {
                //���������� ������������ �����
                if (check_data_for_data_time_menu() ==1)
                {
                  //���� ���������
                  //������� ����� ��� ����������� ���� � ������ �����
                  for(unsigned int i=0; i < 7; i++) time[i] = time_edit[i];/*��������������� time_copy � calibration_copy �� ����� �� �-��� main_manu_function() � main_routines_for_i2c() ������������ � ���������� ����*/ 
                  calibration = calibration_edit;/*��������������� time_copy � calibration_copy �� ����� �� �-��� main_manu_function() � main_routines_for_i2c() ������������ � ���������� ����*/ 
                  current_ekran.edition = 0;
                  //����������� ����������� ������ ���� � RTC
                  //��� ����� ����������� �� ���������� ��������� ������� ��������, ��� ������������������ � ������� ����������� �������
                  _SET_BIT(control_i2c_taskes, TASK_START_WRITE_RTC_BIT);
                  _SET_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT);
                }
                else
                {
                  //���� ����������� - ����������� ��� ��
                  current_ekran.edition = 3;
                }

                //�������� � ������ �����������
                current_ekran.cursor_on = 0;
                current_ekran.cursor_blinking_on = 0;
              }
              else if (current_ekran.edition == 3)
              {
                //����� � ����� �����������
                current_ekran.edition = 0;
                current_ekran.cursor_on = 0;
                current_ekran.cursor_blinking_on = 0;
              }

              
              if(current_ekran.edition == 2) make_ekran_ask_rewrite();
              else if(current_ekran.edition == 3) 
              {
                const unsigned char information_about_error[MAX_NAMBER_LANGUAGE][MAX_COL_LCD] = 
                {
                  " �������� ������",
                  "  ������ ����  ",
                  "   False data   ",
                  " �������� ������"
                };
                make_ekran_about_error(information_about_error);
              }
              else
                //����������� �� ���������� ������
                new_state_keyboard |= (1<<BIT_REWRITE);
              
              //�������� �����������, �� ��������� ������ 
              new_state_keyboard &= (unsigned int)(~(1<<BIT_KEY_ENTER));
            }
            else if (new_state_keyboard == (1<<BIT_KEY_ESC))
            {
              //��������� ������ ESC

              if(current_ekran.edition == 0)
              {
                //����� � ����� ������������
                //���������� � ��������� ����
                current_ekran.current_level = previous_level_in_current_level_menu[current_ekran.current_level];
                current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
                current_ekran.edition = 0;
              }
              else
              {
                //����� � ����� ����������� ��� �������� ���
                current_ekran.edition = 0;
                current_ekran.cursor_on = 0;
                current_ekran.cursor_blinking_on = 0;
              }

              //����������� ������� �� ����������� ������ ������
              new_state_keyboard |= (1<<BIT_REWRITE);

              //�������� �����������, �� ��������� ������ 
              new_state_keyboard &= (unsigned int)(~(1<<BIT_KEY_ESC));
            }
            else if (new_state_keyboard == (1<<BIT_KEY_UP))
            {
              //��������� ������ UP
              if(current_ekran.edition == 0)
              {
                //���������� � ����� ������������
                current_ekran.index_position -=MAX_ROW_LCD;
                if(current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_EKRAN_TIME - MAX_ROW_LCD;
                /**************************************************/
                //������ �� ���� �� ������� ������ ����� � ������
                /**************************************************/
                if(current_ekran.index_position == ROW_Y_)
                {
                  current_ekran.position_cursor_x = COL_DY1;
                }
                else if(current_ekran.index_position == ROW_T_)
                {
                  current_ekran.index_position = ROW_Y_;
                  current_ekran.position_cursor_x = COL_DY1;
                }
                else if(current_ekran.index_position == ROW_N_)
                {
                  current_ekran.index_position = ROW_K_;
                  current_ekran.position_cursor_x = COL_SK1;
                }
                else if(current_ekran.index_position == ROW_K_)
                {
                  current_ekran.position_cursor_x = COL_SK1;
                }
                /**************************************************/
                position_in_current_level_menu[EKRAN_TIME] = current_ekran.index_position;
              }
              else
              {
                //����������� �����
                edit_time(1);
              }

              //������� ����� ���� 2
              make_ekran_time();
              //�������� �����������, �� ��������� ������ 
              new_state_keyboard &= (unsigned int)(~(1<<BIT_KEY_UP));
            }
            else if (new_state_keyboard == (1<<BIT_KEY_DOWN))
            {
              //��������� ������ DOWN
              if(current_ekran.edition == 0)
              {
                //���������� � ����� ������������
                current_ekran.index_position +=MAX_ROW_LCD;
                if(current_ekran.index_position >= MAX_ROW_FOR_EKRAN_TIME) current_ekran.index_position = 0;
                /**************************************************/
                //������ �� ���� �� ������� ������ ����� � ������
                /**************************************************/
                if(current_ekran.index_position == ROW_Y_)
                {
                  current_ekran.position_cursor_x = COL_DY1;
                }
                else if(current_ekran.index_position == ROW_T_)
                {
                  current_ekran.index_position = ROW_Y_;
                  current_ekran.position_cursor_x = COL_DY1;
                }
                else if(current_ekran.index_position == ROW_N_)
                {
                  current_ekran.index_position = ROW_K_;
                  current_ekran.position_cursor_x = COL_SK1;
                }
                else if(current_ekran.index_position == ROW_K_)
                {
                  current_ekran.position_cursor_x = COL_SK1;
                }
                /**************************************************/
                position_in_current_level_menu[EKRAN_TIME] = current_ekran.index_position;
              }
              else
              {
                //����������� �����
                edit_time(0);
              }

              //������� ����� ������-����
              make_ekran_time();
              //�������� �����������, �� ��������� ������ 
              new_state_keyboard &= (unsigned int)(~(1<<BIT_KEY_DOWN));
            }
            else if (new_state_keyboard == (1<<BIT_KEY_RIGHT))
            {
              if(current_ekran.index_position == ROW_Y_)
              {
                if(current_ekran.position_cursor_x == COL_DY1) current_ekran.position_cursor_x = COL_DY2;
                else if(current_ekran.position_cursor_x == COL_DY2) current_ekran.position_cursor_x = COL_MY1;
                else if(current_ekran.position_cursor_x == COL_MY1) current_ekran.position_cursor_x = COL_MY2;
                else if(current_ekran.position_cursor_x == COL_MY2) current_ekran.position_cursor_x = COL_SY1;
                else if(current_ekran.position_cursor_x == COL_SY1) current_ekran.position_cursor_x = COL_SY2;
                else if(current_ekran.position_cursor_x == COL_SY2)
                {
                  current_ekran.index_position = ROW_T_;
                  current_ekran.position_cursor_x = COL_HT1;
                }
              }
              else if(current_ekran.index_position == ROW_T_)
              {
                if(current_ekran.position_cursor_x == COL_HT1) current_ekran.position_cursor_x = COL_HT2;
                else if(current_ekran.position_cursor_x == COL_HT2) current_ekran.position_cursor_x = COL_MT1;
                else if(current_ekran.position_cursor_x == COL_MT1) current_ekran.position_cursor_x = COL_MT2;
                else if(current_ekran.position_cursor_x == COL_MT2) current_ekran.position_cursor_x = COL_ST1;
                else if(current_ekran.position_cursor_x == COL_ST1) current_ekran.position_cursor_x = COL_ST2;
                else if(current_ekran.position_cursor_x == COL_ST2)
                {
                  current_ekran.index_position = ROW_K_;
                  current_ekran.position_cursor_x = COL_SK1;
                }
              }
              else if(current_ekran.index_position == ROW_K_)
              {
                if(current_ekran.position_cursor_x == COL_SK1) current_ekran.position_cursor_x = COL_VK1;
                else if(current_ekran.position_cursor_x == COL_VK1) current_ekran.position_cursor_x = COL_VK2;
                else if(current_ekran.position_cursor_x == COL_VK2)
                {
                  current_ekran.index_position = ROW_Y_;
                  current_ekran.position_cursor_x = COL_DY1;
                }
              }
              //������� ����� ������-����
              make_ekran_time();
              //�������� �����������, �� ��������� ������ 
              new_state_keyboard &= (unsigned int)(~(1<<BIT_KEY_RIGHT));
            }
            else if (new_state_keyboard == (1<<BIT_KEY_LEFT))
            {
              if(current_ekran.index_position == ROW_Y_)
              {
                if(current_ekran.position_cursor_x == COL_SY2) current_ekran.position_cursor_x = COL_SY1;
                else if(current_ekran.position_cursor_x == COL_SY1) current_ekran.position_cursor_x = COL_MY2;
                else if(current_ekran.position_cursor_x == COL_MY2) current_ekran.position_cursor_x = COL_MY1;
                else if(current_ekran.position_cursor_x == COL_MY1) current_ekran.position_cursor_x = COL_DY2;
                else if(current_ekran.position_cursor_x == COL_DY2) current_ekran.position_cursor_x = COL_DY1;
                else if(current_ekran.position_cursor_x == COL_DY1)
                {
                  current_ekran.index_position = ROW_K_;
                  current_ekran.position_cursor_x = COL_VK2;
                }
              }
              else if(current_ekran.index_position == ROW_T_)
              {
                if(current_ekran.position_cursor_x == COL_ST2) current_ekran.position_cursor_x = COL_ST1;
                else if(current_ekran.position_cursor_x == COL_ST1) current_ekran.position_cursor_x = COL_MT2;
                else if(current_ekran.position_cursor_x == COL_MT2) current_ekran.position_cursor_x = COL_MT1;
                else if(current_ekran.position_cursor_x == COL_MT1) current_ekran.position_cursor_x = COL_HT2;
                else if(current_ekran.position_cursor_x == COL_HT2) current_ekran.position_cursor_x = COL_HT1;
                else if(current_ekran.position_cursor_x == COL_HT1)
                {
                  current_ekran.index_position = ROW_Y_;
                  current_ekran.position_cursor_x = COL_SY2;
                }
              }
              else if(current_ekran.index_position == ROW_K_)
              {
                if(current_ekran.position_cursor_x == COL_VK2) current_ekran.position_cursor_x = COL_VK1;
                else if(current_ekran.position_cursor_x == COL_VK1) current_ekran.position_cursor_x = COL_SK1;
                else if(current_ekran.position_cursor_x == COL_SK1)
                {
                  current_ekran.index_position = ROW_T_;
                  current_ekran.position_cursor_x = COL_ST2;
                }
              }
              //������� ����� ������-����
              make_ekran_time();
              //�������� �����������, �� ��������� ������ 
              new_state_keyboard &= (unsigned int)(~(1<<BIT_KEY_LEFT));
            }
            else
            {
              //��������� ����� ������� ������ - �� � ����������� ��������, ���� ������� ����������� ��� �������� ������ � ������ �����
              unsigned int temp_data = new_state_keyboard;
              new_state_keyboard &= ~temp_data;
            }
          }
        }
        break;
      }
/******************************************************************************************************************************************/ 

/******************************************************************************************************************************************/      
    case EKRAN_COFIGURATION:
      {
        //����� ��� ����������� ������������
        static unsigned int configuration_edit;
        
        //������� �� ��� ���� �����������
        unsigned int maska_keyboard_bits = (1<<BIT_KEY_ENTER)| (1<<BIT_KEY_ESC)|(1<<BIT_REWRITE);
        
        if (current_ekran.edition == 1)
          maska_keyboard_bits |= (1<<BIT_KEY_RIGHT) | (1<<BIT_KEY_LEFT) | (1<<BIT_KEY_UP)|(1<<BIT_KEY_DOWN);
        else if (current_ekran.edition == 0)
          maska_keyboard_bits |= (1<<BIT_KEY_UP)|(1<<BIT_KEY_DOWN);
        
        new_state_keyboard &= maska_keyboard_bits;
        //������ �������� 䳿, ���� ��������� ������ �� ��� ����� ��������, ��� ����� ������� �������� �����
        if (new_state_keyboard !=0)
        {
          //�������� ����� �� ��������� ������
          if((new_state_keyboard & (1<<BIT_REWRITE)) !=0)
          {
            if(current_ekran.index_position >= MAX_ROW_FOR_EKRAN_CONFIGURATION) current_ekran.index_position = 0;
            position_in_current_level_menu[EKRAN_COFIGURATION] = current_ekran.index_position;
            //������� ����� ������������
            make_ekran_configuration(configuration_edit);
            //������� �� ���������� ������
            new_state_keyboard &= (unsigned int)(~(1<<BIT_REWRITE));
          }
          else
          {
            if (new_state_keyboard == (1<<BIT_KEY_ENTER))
            {
              //��������� ������ ENTER
              if(current_ekran.edition == 0)
              {
                //������� ��������� � ��������� ��� �����������
                configuration_edit = current_settings.configuration;
                  
                //ϳ�������� �� ������ ����������� - �������� �������� ������
                current_ekran.cursor_on = 1;
                current_ekran.cursor_blinking_on = 1;
                if (current_settings.password1 != 0)
                {
                  //���������� �� ���� ������ ������
                  current_ekran.current_level = EKRAN_LEVEL_PASSWORD;
                  previous_level_in_current_level_menu[current_ekran.current_level] = EKRAN_COFIGURATION;
                  current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
                }
                else
                {
                  //���������� � ����� �����������
                  current_ekran.edition = 1;
                }
              }
              else if (current_ekran.edition == 1)
              {
                //���������� �� ���� ���� ��������
                if (configuration_edit == current_settings.configuration) current_ekran.edition = 0;
                else current_ekran.edition = 2;

                current_ekran.cursor_on = 0;
                current_ekran.cursor_blinking_on = 0;
              }
              else if (current_ekran.edition == 2)
              {
                //�������, �� ���� ��������� ����� ���� ������
                changed_settings = CHANGED_ETAP_EXECUTION;

                //���������� ��������
                action_after_changing_of_configuration(configuration_edit, &current_settings);
                //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                fix_change_settings(0, 1);
                current_ekran.edition = 0;
                
                //�������� � ������ �����������
                current_ekran.cursor_on = 1;
                current_ekran.cursor_blinking_on = 0;
              }
              
              if(current_ekran.edition == 2) make_ekran_ask_rewrite();
              else
                //����������� �� ���������� ������
                new_state_keyboard |= (1<<BIT_REWRITE);

              //�������� �����������, �� ��������� ������ 
              new_state_keyboard &= (unsigned int)(~(1<<BIT_KEY_ENTER));
            }
            else if (new_state_keyboard == (1<<BIT_KEY_ESC))
            {
              //��������� ������ ESC

              if(current_ekran.edition == 0)
              {
                //����� � ����� ������������
                //���������� � ��������� ����
                current_ekran.current_level = previous_level_in_current_level_menu[current_ekran.current_level];
                current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
              }
              else
              {
                //����� � ����� ����������� ��� �������� ���
                current_ekran.cursor_on = 1;
                current_ekran.cursor_blinking_on = 0;
              }
              current_ekran.edition = 0;

              //����������� ������� �� ����������� ������ ������
              new_state_keyboard |= (1<<BIT_REWRITE);
              //�������� �����������, �� ��������� ������ 
              new_state_keyboard &= (unsigned int)(~(1<<BIT_KEY_ESC));
            }
            else if (new_state_keyboard == (1<<BIT_KEY_UP))
            {
              //��������� ������ UP

              if(--current_ekran.index_position < 0 ) current_ekran.index_position = MAX_ROW_FOR_EKRAN_CONFIGURATION - 1;
              position_in_current_level_menu[EKRAN_COFIGURATION] = current_ekran.index_position;
              //������� ����� ������������
              make_ekran_configuration(configuration_edit);
              //�������� �����������, �� ��������� ������ 
              new_state_keyboard &= (unsigned int)(~(1<<BIT_KEY_UP));
            }
            else if (new_state_keyboard == (1<<BIT_KEY_DOWN))
            {
              //��������� ������ DOWN

              if(++current_ekran.index_position >= MAX_ROW_FOR_EKRAN_CONFIGURATION) current_ekran.index_position = 0;
              position_in_current_level_menu[EKRAN_COFIGURATION] = current_ekran.index_position;
              //������� ����� ������������
              make_ekran_configuration(configuration_edit);
              //�������� �����������, �� ��������� ������ 
              new_state_keyboard &= (unsigned int)(~(1<<BIT_KEY_DOWN));
            }
            else if ((new_state_keyboard == (1<<BIT_KEY_LEFT)) || (new_state_keyboard == (1<<BIT_KEY_RIGHT)))
            { 
              //��������� ������ LEFT ��� RIGHT

              configuration_edit ^= (1<<current_ekran.index_position);

              //������� ����� ������������
              make_ekran_configuration(configuration_edit);
              //�������� �����������, �� ��������� ������ 
              new_state_keyboard &= (unsigned int)(~((1<<BIT_KEY_LEFT) | (1<<BIT_KEY_RIGHT)));
            }
            else
            {
              //��������� ����� ������� ������ - �� � ����������� ��������, ���� ������� ����������� ��� �������� ������ � ������ �����
              unsigned int temp_data = new_state_keyboard;
              new_state_keyboard &= ~temp_data;
            }
          }
        }
        break;
      }
/******************************************************************************************************************************************/ 

/****************************************************************************************************************************************/      
    case EKRAN_MEASURMENT:
    case EKRAN_MEASURMENT_CURRENT:
    case EKRAN_MEASURMENT_VOLTAGE_TYPE:
    case EKRAN_MEASURMENT_VOLTAGE_PHASE:
    case EKRAN_MEASURMENT_VOLTAGE_LINE:
    case EKRAN_MEASURMENT_FREQUENCY:
    case EKRAN_MEASURMENT_ANGLE:
    case EKRAN_MEASURMENT_POWER:
    case EKRAN_CHOOSE_SETTINGS_ZDZ:
    case EKRAN_CHOOSE_SETTINGS_APV:
    case EKRAN_CHOOSE_TIMEOUT_GROUP1_APV:
    case EKRAN_CHOOSE_TIMEOUT_GROUP2_APV:
    case EKRAN_CHOOSE_TIMEOUT_GROUP3_APV:
    case EKRAN_CHOOSE_TIMEOUT_GROUP4_APV:
    case EKRAN_CHOOSE_SETTINGS_UROV:
    case EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP1_UROV:
    case EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP2_UROV:
    case EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP3_UROV:
    case EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP4_UROV:
    case EKRAN_CHOOSE_SETTINGS_ZOP:
    case EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP1_ZOP:
    case EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP2_ZOP:
    case EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP3_ZOP:
    case EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP4_ZOP:
    case EKRAN_CHOOSE_SETTINGS_UMIN:
    case EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP1_UMIN:
    case EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP2_UMIN:
    case EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP3_UMIN:
    case EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP4_UMIN:
    case EKRAN_CHOOSE_SETTINGS_UMAX:
    case EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP1_UMAX:
    case EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP2_UMAX:
    case EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP3_UMAX:
    case EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP4_UMAX:
    case EKRAN_CHOOSE_SETTINGS_AVR:
    case EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP1_AVR:
    case EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP2_AVR:
    case EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP3_AVR:
    case EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP4_AVR:
    case EKRAN_CHOOSE_SETTINGS_CTRL_PHASE:
    case EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP1_CTRL_PHASE:
    case EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP2_CTRL_PHASE:
    case EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP3_CTRL_PHASE:
    case EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP4_CTRL_PHASE:
    case EKRAN_TRANSFORMATOR_INFO:
    case EKRAN_CHOSE_SETTINGS:
    case EKRAN_LEVEL_CHOOSE_PASSWORDS:
    case EKRAN_LIST_INPUTS_FOR_RANGUVANNJA:
    case EKRAN_LIST_OUTPUTS_FOR_RANGUVANNJA:
    case EKRAN_LIST_LEDS_FOR_RANGUVANNJA:
    case EKRAN_CHOOSE_SETTINGS_SWITCHER:
    case EKRAN_CHOOSE_RANG_SWITCH:
    case EKRAN_CHOOSE_SETTINGS_UVV:
    case EKRAN_CHOSE_COMMUNICATION_PARAMETERS:
    case EKRAN_VIEW_NAME_OF_CELL:
    case EKRAN_CHOSE_SETTING_RS485:
    case EKRAN_VIEW_LIST_OF_REGISTRATORS:
    case EKRAN_VIEW_SETTINGS_OF_ANALOG_REGISTRATORS:
    case EKRAN_EXTENDED_LIGIC:
    case EKRAN_LIST_SETTINGS_FOR_DF:
    case EKRAN_LIST_DF_FOR_RANGUVANNJA:
    case EKRAN_LIST_DF_FOR_TIMEOUT_SETTINGS:
    case EKRAN_LIST_TYPE_SOURCE_DF1:
    case EKRAN_LIST_TYPE_SOURCE_DF2:
    case EKRAN_LIST_TYPE_SOURCE_DF3:
    case EKRAN_LIST_TYPE_SOURCE_DF4:
    case EKRAN_LIST_TYPE_SOURCE_DF5:
    case EKRAN_LIST_TYPE_SOURCE_DF6:
    case EKRAN_LIST_TYPE_SOURCE_DF7:
    case EKRAN_LIST_TYPE_SOURCE_DF8:
    case EKRAN_LIST_DT:
    case EKRAN_SET_RESET_DT1:
    case EKRAN_SET_RESET_DT2:
    case EKRAN_SET_RESET_DT3:
    case EKRAN_SET_RESET_DT4:
    case EKRAN_SET_DT1:
    case EKRAN_RESET_DT1:
    case EKRAN_SET_DT2:
    case EKRAN_RESET_DT2:
    case EKRAN_SET_DT3:
    case EKRAN_RESET_DT3:
    case EKRAN_SET_DT4:
    case EKRAN_RESET_DT4:
    case EKRAN_LIST_D_AND:
    case EKRAN_LIST_D_OR:
    case EKRAN_LIST_D_XOR:
    case EKRAN_LIST_D_NOT:
    case EKRAN_LIST_BUTTONS_FOR_RANGUVANNJA:
    case EKRAN_INFO:
    case EKRAN_DATE_TIME_PZ:
    case EKRAN_POINT_TIME_SETTINGS:
    case EKRAN_POINT_TIME_SETPOINT:
    case EKRAN_POINT_TIME_RANGUVANNJA:
    case EKRAN_DIAGNOSTYKA:
    case EKRAN_LIST_INPUTS_OUTPUTS:
    case EKRAN_STATE_INPUTS:
    case EKRAN_STATE_OUTPUTS:
    case EKRAN_LIST_REGISTRATORS:
    case EKRAN_LIST_ANALOG_REGISTRATOR_RECORDS:
    case EKRAN_LIST_DIGITAL_REGISTRATOR_RECORDS:
    case EKRAN_LIST_REGISTRATOR_PROGRAM_ERROR_RECORDS:
    case EKRAN_TITLES_DIGITAL_REGISTRATOR:
    case EKRAN_DATA_LADEL_DR:
    case EKRAN_CHANGES_SIGNALS_DR:
    case EKRAN_TITLES_PR_ERR_REGISTRATOR:
    case EKRAN_DATA_LADEL_PR_ERR:
    case EKRAN_CHANGES_DIAGNOSTICS_PR_ERR:
    case EKRAN_DATA_LADEL_AR:   
      {
        //������� �� ��� ���� �����������
        new_state_keyboard &= (1<<BIT_KEY_ENTER)|(1<<BIT_KEY_ESC)|(1<<BIT_KEY_UP)|(1<<BIT_KEY_DOWN)|(1<<BIT_REWRITE);
        //������ �������� 䳿, ���� ��������� ������ �� ��� ����� ��������, ��� ����� ������� �������� �����
        if (new_state_keyboard !=0)
        {
          //�������� ����� �� ��������� ������
          if((new_state_keyboard & (1<<BIT_REWRITE)) !=0)
          {
            if(current_ekran.current_level == EKRAN_MEASURMENT)
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_MEASURMENT) current_ekran.index_position = 0;
              position_in_current_level_menu[EKRAN_MEASURMENT] = current_ekran.index_position;
              //������� ����� ������ ����������
              make_ekran_measurement();
            }
            else if(current_ekran.current_level == EKRAN_MEASURMENT_VOLTAGE_TYPE)
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_MEASURMENT_VOLTAGE_TYPE) current_ekran.index_position = 0;
              position_in_current_level_menu[EKRAN_MEASURMENT_VOLTAGE_TYPE] = current_ekran.index_position;
              //������� ����� ������ ���� ������
              make_ekran_measurement_voltage_type();
            }
            else if(current_ekran.current_level == EKRAN_MEASURMENT_CURRENT)
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_MEASURMENT_CURRENT) current_ekran.index_position = 0;
              position_in_current_level_menu[EKRAN_MEASURMENT_CURRENT] = current_ekran.index_position;
              //������� ����� ���������� ������
              make_ekran_current(pervynna_vtorynna);
            }
            else if(current_ekran.current_level == EKRAN_MEASURMENT_VOLTAGE_PHASE)
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_MEASURMENT_VOLTAGE_PHASE) current_ekran.index_position = 0;
              position_in_current_level_menu[EKRAN_MEASURMENT_VOLTAGE_PHASE] = current_ekran.index_position;
              //������� ����� ���������� ������ ������
              make_ekran_voltage_phase(pervynna_vtorynna);
            }
            else if(current_ekran.current_level == EKRAN_MEASURMENT_VOLTAGE_LINE)
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_MEASURMENT_VOLTAGE_LINE) current_ekran.index_position = 0;
              position_in_current_level_menu[EKRAN_MEASURMENT_VOLTAGE_LINE] = current_ekran.index_position;
              //������� ����� ���������� ������� ������
              make_ekran_voltage_line(pervynna_vtorynna);
            }
            else if(current_ekran.current_level == EKRAN_MEASURMENT_FREQUENCY)
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_MEASURMENT_FREQUENCY) current_ekran.index_position = 0;
              position_in_current_level_menu[EKRAN_MEASURMENT_FREQUENCY] = current_ekran.index_position;
              //������� ����� ����������� �������
              make_ekran_frequency();
            }
            else if(current_ekran.current_level == EKRAN_MEASURMENT_ANGLE)
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_MEASURMENT_ANGLE) current_ekran.index_position = 0;
              position_in_current_level_menu[EKRAN_MEASURMENT_ANGLE] = current_ekran.index_position;
              //������� ����� ����������� ����
              make_ekran_angle();
            }
            else if(current_ekran.current_level == EKRAN_MEASURMENT_POWER)
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_MEASURMENT_POWER) current_ekran.index_position = 0;
              position_in_current_level_menu[EKRAN_MEASURMENT_POWER] = current_ekran.index_position;
              //������� ����� ����������� �����������
              make_ekran_power(pervynna_vtorynna);
            }
            else if (
                     (current_ekran.current_level == EKRAN_CHOOSE_SETTINGS_APV       )||
                     (current_ekran.current_level == EKRAN_CHOOSE_SETTINGS_UROV      )|| 
                     (current_ekran.current_level == EKRAN_CHOOSE_SETTINGS_ZOP       )|| 
                     (current_ekran.current_level == EKRAN_CHOOSE_SETTINGS_UMIN      )||
                     (current_ekran.current_level == EKRAN_CHOOSE_SETTINGS_UMAX      )||
                     (current_ekran.current_level == EKRAN_CHOOSE_SETTINGS_AVR       )||
                     (current_ekran.current_level == EKRAN_CHOOSE_SETTINGS_CTRL_PHASE)
                    )   
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_CHOSE_SETTINGS_PROTECTION_WITH_TWO_GROUP) current_ekran.index_position = 0;
              position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;

              //������� ����� �����1-...-�����N-��������� ��� ��� ������� �� ���������������� ����� �������
              make_ekran_chose_settings_protection_with_groups();
            }
            else if (
                     (
                      (current_ekran.current_level >= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP1_UROV) &&
                      (current_ekran.current_level <= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP4_UROV)
                     )
                     ||  
                     (
                      (current_ekran.current_level >= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP1_ZOP) &&
                      (current_ekran.current_level <= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP4_ZOP)
                     )
                     ||  
                     (
                      (current_ekran.current_level >= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP1_UMIN) &&
                      (current_ekran.current_level <= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP4_UMIN)
                     )
                     ||  
                     (
                      (current_ekran.current_level >= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP1_UMAX) &&
                      (current_ekran.current_level <= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP4_UMAX)
                     )
                     ||  
                     (
                      (current_ekran.current_level >= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP1_CTRL_PHASE) &&
                      (current_ekran.current_level <= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP4_CTRL_PHASE)
                     )
                    )
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_CHOSE_SETPOINTS_TIMEOUTS) current_ekran.index_position = 0;
              position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;

              //������� ����� �������-�������� ��� ������� � ���� � �� ����� �������
              make_ekran_chose_setpoint_and_timeout();
            }
            else if (
                     (
                      (current_ekran.current_level >= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP1_AVR) &&
                      (current_ekran.current_level <= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP4_AVR)
                     )
                    )
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_CHOSE_SETPOINTS_TIMEOUTS_AVR) current_ekran.index_position = 0;
              position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;

              //������� ����� ������� Umin-������� Umax-�������� ��� ��� � ����� � �� ����� �������
              make_ekran_chose_setpoint_and_timeout_avr();
            }
            else if (
                     (
                      (current_ekran.current_level >= EKRAN_CHOOSE_TIMEOUT_GROUP1_APV) &&
                      (current_ekran.current_level <= EKRAN_CHOOSE_TIMEOUT_GROUP4_APV)
                     )
                    )
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_CHOSE_SETTINGS_PROTECTION_WITH_TIMEOUT) current_ekran.index_position = 0;
              position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;

                //������� ����� �������� ��� ������� � ���� � ������ ���� �������
              make_ekran_chose_timeout();
            }
            else if (current_ekran.current_level == EKRAN_CHOOSE_SETTINGS_ZDZ)
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_CHOSE_SETTINGS_PROTECTION_WITH_CONTROL) current_ekran.index_position = 0;
              position_in_current_level_menu[EKRAN_CHOOSE_SETTINGS_ZDZ] = current_ekran.index_position;
              //������� ����� ��������� ��� ���
              make_ekran_chose_control();
            }
            else if (current_ekran.current_level == EKRAN_TRANSFORMATOR_INFO)
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_CHOSE_SETTINGS_PROTECTION_WITH_SETPOINTS_CONTROL) current_ekran.index_position = 0;
              
              position_in_current_level_menu[EKRAN_TRANSFORMATOR_INFO] = current_ekran.index_position;

              //������� ����� �������-���������
              make_ekran_chose_setpoint_control();
            }
            else if (current_ekran.current_level == EKRAN_CHOOSE_SETTINGS_SWITCHER)
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_CHOSE_SETTINGS_SWITCHER) current_ekran.index_position = 0;
              
              position_in_current_level_menu[EKRAN_CHOOSE_SETTINGS_SWITCHER] = current_ekran.index_position;

              //������� ����� �������-��������-���������-���������� ��������
              make_ekran_chose_settings_switcher();
            }
            else if (current_ekran.current_level == EKRAN_CHOOSE_RANG_SWITCH)
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_RANG_SWITCH) current_ekran.index_position = 0;
              
              position_in_current_level_menu[EKRAN_CHOOSE_RANG_SWITCH] = current_ekran.index_position;

              //������� ����� �����./�����.
              make_ekran_choose_CBOn_CBOff();
            }
            else if (current_ekran.current_level == EKRAN_CHOSE_SETTINGS)
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_CHOSE_SETTINGS) current_ekran.index_position = 0;
              while(
                    ((current_settings.configuration & (1 << EL_BIT_CONFIGURATION)) == 0)
                    &&
                    (current_ekran.index_position == INDEX_OF_EXTENDED_LOGIC)
                   )
              {
                if(++current_ekran.index_position >= MAX_ROW_FOR_CHOSE_SETTINGS) current_ekran.index_position = 0;
              }

              position_in_current_level_menu[EKRAN_CHOSE_SETTINGS] = current_ekran.index_position;
            
              //������� ����� ��������� ������������
              make_ekran_chose_settings();
            }
            else if (current_ekran.current_level == EKRAN_LEVEL_CHOOSE_PASSWORDS)
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_CHOOSE_PASSWORDS) current_ekran.index_position = 0;
              position_in_current_level_menu[EKRAN_LEVEL_CHOOSE_PASSWORDS] = current_ekran.index_position;
            
              //������� ����� ��������� ������
              make_ekran_chose_passwords();
            }
            else if (current_ekran.current_level == EKRAN_CHOOSE_SETTINGS_UVV)
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_CHOSE_SETTINGS_UVV) current_ekran.index_position = 0;
              position_in_current_level_menu[EKRAN_CHOOSE_SETTINGS_UVV] = current_ekran.index_position;
                //������� ����� ������ ��������� ���
              make_ekran_chose_settings_uvv();
            }
            else if (current_ekran.current_level == EKRAN_LIST_INPUTS_FOR_RANGUVANNJA)
            {
              if(current_ekran.index_position >= MAX_ROW_LIST_INPUTS_FOR_RANGUVANNJA) current_ekran.index_position = 0;
              position_in_current_level_menu[EKRAN_LIST_INPUTS_FOR_RANGUVANNJA] = current_ekran.index_position;
            
              //������� ����� ��������� ���������� ����� ��� ����������
              make_ekran_chose_of_inputs_outputs_leds_df_buttons_for_ranguvannja(0);
            }
            else if (current_ekran.current_level == EKRAN_LIST_OUTPUTS_FOR_RANGUVANNJA)
            {
              if(current_ekran.index_position >= MAX_ROW_LIST_OUTPUTS_FOR_RANGUVANNJA) current_ekran.index_position = 0;
              position_in_current_level_menu[EKRAN_LIST_OUTPUTS_FOR_RANGUVANNJA] = current_ekran.index_position;
            
              //������� ����� ��������� ���������� ������ ��� ����������
              make_ekran_chose_of_inputs_outputs_leds_df_buttons_for_ranguvannja(1);
            }
            else if (current_ekran.current_level == EKRAN_LIST_LEDS_FOR_RANGUVANNJA)
            {
              if(current_ekran.index_position >= MAX_ROW_LIST_LEDS_FOR_RANGUVANNJA) current_ekran.index_position = 0;
              position_in_current_level_menu[EKRAN_LIST_LEDS_FOR_RANGUVANNJA] = current_ekran.index_position;
            
              //������� ����� ��������� ������������� ��� ����������
              make_ekran_chose_of_inputs_outputs_leds_df_buttons_for_ranguvannja(2);
            }
            else if (current_ekran.current_level == EKRAN_CHOSE_COMMUNICATION_PARAMETERS)
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_CHOSE_COMMUNICATION_PARAMETERS) current_ekran.index_position = 0;
              position_in_current_level_menu[EKRAN_CHOSE_COMMUNICATION_PARAMETERS] = current_ekran.index_position;
              //������� ����� ������ ��������� ��������� �����������
              make_ekran_chose_communication_parameters();
            }
            else if (current_ekran.current_level == EKRAN_VIEW_NAME_OF_CELL)
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_VIEW_NAME_OF_CELL) current_ekran.index_position = 0;
              position_in_current_level_menu[EKRAN_VIEW_NAME_OF_CELL] = current_ekran.index_position;
              //������� ����� ����������� ����� ������
              make_ekran_name_of_cell();
            }
            else if (current_ekran.current_level == EKRAN_CHOSE_SETTING_RS485)
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_CHOSE_SETTING_RS485) current_ekran.index_position = 0;
              position_in_current_level_menu[EKRAN_CHOSE_SETTING_RS485] = current_ekran.index_position;
              //������� ����� ����������� ������ ��������� ��� ���������� RS-485
              make_ekran_chose_setting_rs485();
            }
            else if (current_ekran.current_level == EKRAN_VIEW_LIST_OF_REGISTRATORS)
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_LIST_OF_REGISTRATORS) current_ekran.index_position = 0;
              position_in_current_level_menu[EKRAN_VIEW_LIST_OF_REGISTRATORS] = current_ekran.index_position;
              //������� ����� ������ ����������
              make_ekran_chose_registrators();
            }
            else if (current_ekran.current_level == EKRAN_VIEW_SETTINGS_OF_ANALOG_REGISTRATORS)
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_SETTINGS_OF_ANALOG_REGISTRATOR) current_ekran.index_position = 0;
              position_in_current_level_menu[EKRAN_VIEW_SETTINGS_OF_ANALOG_REGISTRATORS] = current_ekran.index_position;
              //������� ����� ������ ��������� ����������� ����������
              make_ekran_settings_analog_registrators();
            }
            else if (current_ekran.current_level == EKRAN_EXTENDED_LIGIC)
            {
              do
              {
                if(current_ekran.index_position >= MAX_ROW_FOR_EXTENDED_LIGIC) current_ekran.index_position = 0;
                
//                if ((current_ekran.index_position == INDEX_OF_DEFINED_FUNCTIONS) && (current_settings.number_defined_df  == 0))
//                  current_ekran.index_position++;
//                if ((current_ekran.index_position == INDEX_OF_DEFINED_TRIGGERS) && (current_settings.number_defined_dt  == 0))
//                  current_ekran.index_position++;
//                if ((current_ekran.index_position == INDEX_OF_DEFINED_AND) && (current_settings.number_defined_and  == 0))
//                  current_ekran.index_position++;
//                if ((current_ekran.index_position == INDEX_OF_DEFINED_OR) && (current_settings.number_defined_or  == 0))
//                  current_ekran.index_position++;
//                if ((current_ekran.index_position == INDEX_OF_DEFINED_XOR) && (current_settings.number_defined_xor  == 0))
//                  current_ekran.index_position++;
//                if ((current_ekran.index_position == INDEX_OF_DEFINED_NOT) && (current_settings.number_defined_not  == 0))
//                  current_ekran.index_position++;
              }
              while (current_ekran.index_position >= MAX_ROW_FOR_EXTENDED_LIGIC);

              position_in_current_level_menu[EKRAN_EXTENDED_LIGIC] = current_ekran.index_position;
              //������� ����� ������ ����������� ��������� �����
              make_ekran_extended_logic();
            }
            else if (current_ekran.current_level == EKRAN_LIST_SETTINGS_FOR_DF)
            {
              if(current_ekran.index_position >= MAX_ROW_SETTINGS_DF) current_ekran.index_position = 0;
              position_in_current_level_menu[EKRAN_LIST_SETTINGS_FOR_DF] = current_ekran.index_position;
              //������� ����� ����������� ������ ��������� ��� �������������� �������
              make_ekran_chose_settings_df();
            }
            else if ((current_ekran.current_level == EKRAN_LIST_DF_FOR_RANGUVANNJA) || (current_ekran.current_level == EKRAN_LIST_DF_FOR_TIMEOUT_SETTINGS))
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_LIST_DF) current_ekran.index_position = 0;
              position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;
            
              //������� ����� ��������� �������������� �������
              make_ekran_chose_of_inputs_outputs_leds_df_buttons_for_ranguvannja(3);
            }
            else if ((current_ekran.current_level >= EKRAN_LIST_TYPE_SOURCE_DF1) && (current_ekran.current_level <= EKRAN_LIST_TYPE_SOURCE_DF8))
            {
              if(current_ekran.index_position >= MAX_ROW_LIST_TYPE_SOURCE_DF) current_ekran.index_position = 0;
              position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;
            
              //������� ����� ��������� ���� ������ �������������� �������
              make_ekran_list_type_source_df();
            }
            else if (current_ekran.current_level == EKRAN_LIST_DT)
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_LIST_DT) current_ekran.index_position = 0;
              position_in_current_level_menu[EKRAN_LIST_DT] = current_ekran.index_position;
              //������� ����� ��������� �������������� ������
              make_ekran_chose_of_inputs_outputs_leds_df_buttons_for_ranguvannja(5);
            }
            else if ((current_ekran.current_level >= EKRAN_SET_RESET_DT1) && (current_ekran.current_level <= EKRAN_SET_RESET_DT4))
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_LIST_SET_RESET_DT) current_ekran.index_position = 0;
              position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;
              //������� ����� ��������� ���������-����������� �������������� ������
              make_ekran_set_reset_trigger();
            }
            else if ((current_ekran.current_level >= EKRAN_SET_DT1) && (current_ekran.current_level <= EKRAN_RESET_DT4))
            {
              if(current_ekran.index_position >= MAX_ROW_LIST_TYPE_SOURCE_DT) current_ekran.index_position = 0;
              position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;
              //������� ����� ��������� ���� ������ �������������� ������
              make_ekran_list_type_source_dt();
            }
            else if (current_ekran.current_level == EKRAN_LIST_D_AND)
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_LIST_D_AND) current_ekran.index_position = 0;
              position_in_current_level_menu[EKRAN_LIST_D_AND] = current_ekran.index_position;
              //������� ����� ��������� ������������ "�"
              make_ekran_chose_of_inputs_outputs_leds_df_buttons_for_ranguvannja(6);
            }
            else if (current_ekran.current_level == EKRAN_LIST_D_OR)
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_LIST_D_OR) current_ekran.index_position = 0;
              position_in_current_level_menu[EKRAN_LIST_D_OR] = current_ekran.index_position;
              //������� ����� ��������� ������������ "���"
              make_ekran_chose_of_inputs_outputs_leds_df_buttons_for_ranguvannja(7);
            }
            else if (current_ekran.current_level == EKRAN_LIST_D_XOR)
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_LIST_D_XOR) current_ekran.index_position = 0;
              position_in_current_level_menu[EKRAN_LIST_D_XOR] = current_ekran.index_position;
              //������� ����� ��������� ������������ "����.���"
              make_ekran_chose_of_inputs_outputs_leds_df_buttons_for_ranguvannja(8);
            }
            else if (current_ekran.current_level == EKRAN_LIST_D_NOT)
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_LIST_D_NOT) current_ekran.index_position = 0;
              position_in_current_level_menu[EKRAN_LIST_D_NOT] = current_ekran.index_position;
              //������� ����� ��������� ������������ "��"
              make_ekran_chose_of_inputs_outputs_leds_df_buttons_for_ranguvannja(9);
            }
            else if (current_ekran.current_level == EKRAN_LIST_BUTTONS_FOR_RANGUVANNJA)
            {
              if(current_ekran.index_position >= MAX_ROW_LIST_BUTTONS_FOR_RANGUVANNJA) current_ekran.index_position = 0;
              position_in_current_level_menu[EKRAN_LIST_BUTTONS_FOR_RANGUVANNJA] = current_ekran.index_position;
            
              //������� ����� ��������� �������������� ������ ��� ����������
              make_ekran_chose_of_inputs_outputs_leds_df_buttons_for_ranguvannja(4);
            }
            else if (current_ekran.current_level == EKRAN_INFO)
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_INFO) current_ekran.index_position = 0;
              position_in_current_level_menu[EKRAN_INFO] = current_ekran.index_position;
              //������� ����� ����������
              make_ekran_info();
            }
            else if (current_ekran.current_level == EKRAN_DATE_TIME_PZ)
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_DATE_TIME_PZ) current_ekran.index_position = 0;
              position_in_current_level_menu[EKRAN_DATE_TIME_PZ] = current_ekran.index_position;
              //������� ����� ����������� ��� ���� � ���� ��������
              make_ekran_date_time_pz();
            }
            else if (current_ekran.current_level == EKRAN_POINT_TIME_SETTINGS)
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_POINT_TIME_SETTINGS) current_ekran.index_position = 0;
              position_in_current_level_menu[EKRAN_POINT_TIME_SETTINGS] = current_ekran.index_position;
              //������� ����� ������ ���� ������������
              make_ekran_chose_item_of_point_time_settings();
            }
            else if (current_ekran.current_level == EKRAN_POINT_TIME_SETPOINT)
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_POINT_TIME_SETPOINT_RANGUVANNJA) current_ekran.index_position = 0;
              position_in_current_level_menu[EKRAN_POINT_TIME_SETPOINT] = current_ekran.index_position;
              //������� ����� ����������� ��� �������� ��� � ��������-���������-����������� ����������
              make_ekran_time_settings(0);
            }
            else if (current_ekran.current_level == EKRAN_POINT_TIME_RANGUVANNJA)
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_POINT_TIME_SETPOINT_RANGUVANNJA) current_ekran.index_position = 0;
              position_in_current_level_menu[EKRAN_POINT_TIME_RANGUVANNJA] = current_ekran.index_position;
              //������� ����� ����������� ��� �������� ��� � ����������
              make_ekran_time_settings(1);
            }
            else if(current_ekran.current_level == EKRAN_DIAGNOSTYKA)
            {
              if(current_ekran.index_position >= ((int)MAX_ROW_FOR_DIAGNOSTYKA)) current_ekran.index_position = 0;
              
              if (
                  (diagnostyka[0] == 0) &&
                  (diagnostyka[1] == 0) &&
                  ((diagnostyka[2] & USED_BITS_IN_LAST_INDEX) == 0)
                 )
              {
                current_ekran.index_position = 0;
              }
              else
              {
                while (_CHECK_SET_BIT(diagnostyka, current_ekran.index_position) ==0)
                {
                  current_ekran.index_position++;
                  if(current_ekran.index_position >= ((int)MAX_ROW_FOR_DIAGNOSTYKA)) current_ekran.index_position = 0;
                }
              }
              position_in_current_level_menu[EKRAN_DIAGNOSTYKA] = current_ekran.index_position;
              //������� ����� ����������
              make_ekran_diagnostyka(diagnostyka);
            }
            else if (current_ekran.current_level == EKRAN_LIST_INPUTS_OUTPUTS)
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_LIST_INPUTS_OUTPUTS) current_ekran.index_position = 0;
              position_in_current_level_menu[EKRAN_LIST_INPUTS_OUTPUTS] = current_ekran.index_position;
              //������� ����� ������ ������ �����-������
              make_ekran_list_inputs_outputs();
            }
            else if ((current_ekran.current_level == EKRAN_STATE_INPUTS) || (current_ekran.current_level == EKRAN_STATE_OUTPUTS))
            {
              if (current_ekran.current_level == EKRAN_STATE_INPUTS)
              {
                if(current_ekran.index_position >= NUMBER_INPUTS) current_ekran.index_position = 0;
              }
              else
              {
                if(current_ekran.index_position >= NUMBER_OUTPUTS) current_ekran.index_position = 0;
              }
              
              position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;
              //������� ����� ������ ����� ��� ������� 
              make_ekran_state_inputs_or_outputs(current_ekran.current_level - EKRAN_STATE_INPUTS);
            }
            else if (current_ekran.current_level == EKRAN_LIST_REGISTRATORS)
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_LIST_REGISTRATORS) current_ekran.index_position = 0;
              position_in_current_level_menu[EKRAN_LIST_REGISTRATORS] = current_ekran.index_position;
              //������� ����� ������ ����������� ����������
              make_ekran_list_registrators();
            }
            else if (
                     (current_ekran.current_level == EKRAN_LIST_ANALOG_REGISTRATOR_RECORDS ) ||
                     (current_ekran.current_level == EKRAN_LIST_DIGITAL_REGISTRATOR_RECORDS) ||
                     (current_ekran.current_level == EKRAN_LIST_REGISTRATOR_PROGRAM_ERROR_RECORDS)
                    )
            {
              unsigned int number_records;
              unsigned int type_registrator;
  
              if (current_ekran.current_level == EKRAN_LIST_ANALOG_REGISTRATOR_RECORDS)
              {
                number_records = info_rejestrator_ar.number_records;
                type_registrator = INDEX_ML_ANALOG_REGISTRATOR_INFO;
              }
              else if (current_ekran.current_level == EKRAN_LIST_DIGITAL_REGISTRATOR_RECORDS)
              {
                number_records = info_rejestrator_dr.number_records;
                type_registrator = INDEX_ML_DIGITAL_REGISTRATOR_INFO;
              }
              else
              {
                number_records = info_rejestrator_pr_err.number_records;
                type_registrator = INDEX_ML_PROGRAM_ERROE_REGISTRATOR_INFO;
              }
              
              if(current_ekran.index_position >= ((int)number_records)) current_ekran.index_position = 0;
              position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;

              //������� ����� ����������� ������
              make_ekran_list_records_registrator(type_registrator);
            }
            else if (current_ekran.current_level == EKRAN_TITLES_DIGITAL_REGISTRATOR)
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_TITLES_DIGITAL_REGISTRATOR) current_ekran.index_position = 0;
              position_in_current_level_menu[EKRAN_TITLES_DIGITAL_REGISTRATOR] = current_ekran.index_position;
              //������� ����� ����������� ��������� ���� ��� ����������� ����������
              make_ekran_list_titles_for_record_of_digital_registrator();
            }
            else if (current_ekran.current_level == EKRAN_DATA_LADEL_DR)
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_EKRAN_DATA_LABEL) current_ekran.index_position = 0;
              position_in_current_level_menu[EKRAN_DATA_LADEL_DR] = current_ekran.index_position;
              //������� ����� ����������� ���� ���� ����������� ������ ����������� ����������
              make_ekran_data_and_time_of_records_registrator(0);
            }
            else if (current_ekran.current_level == EKRAN_CHANGES_SIGNALS_DR)
            {
              //������� ����� ����������� ��� ������� - ��������� � ����������� ���������
              make_ekran_changing_signals_digital_registrator();
            }
            else if (current_ekran.current_level == EKRAN_TITLES_PR_ERR_REGISTRATOR)
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_TITLES_PR_ERR_REGISTRATOR) current_ekran.index_position = 0;
              position_in_current_level_menu[EKRAN_TITLES_PR_ERR_REGISTRATOR] = current_ekran.index_position;
              //������� ����� ����������� ��������� ���� ��� ���������� ���������� ����
              make_ekran_list_titles_for_record_of_pr_err_registrator();
            }
            else if (current_ekran.current_level == EKRAN_DATA_LADEL_PR_ERR)
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_EKRAN_DATA_LABEL) current_ekran.index_position = 0;
              position_in_current_level_menu[EKRAN_DATA_LADEL_PR_ERR] = current_ekran.index_position;
              //������� ����� ����������� ���� ���� ����������� ������ ���������� ���������� ����
              make_ekran_data_and_time_of_records_registrator(1);
            }
            else if (current_ekran.current_level == EKRAN_CHANGES_DIAGNOSTICS_PR_ERR)
            {
              //������� ����� ����������� ��� ��������� - ��������� � ��������� ���������� ����
              make_ekran_changing_diagnostics_pr_err_registrator();
            }
            else if (current_ekran.current_level == EKRAN_DATA_LADEL_AR)
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_EKRAN_DATA_LABEL) current_ekran.index_position = 0;
              position_in_current_level_menu[EKRAN_DATA_LADEL_AR] = current_ekran.index_position;
              //������� ����� ����������� ���� ���� ����������� ������ ����������� ����������
              make_ekran_data_and_time_of_records_registrator(2);
            }
            
            //������� �� ���������� ������
            new_state_keyboard &= (unsigned int)(~(1<<BIT_REWRITE));
          }
          else
          {
            if (new_state_keyboard == (1<<BIT_KEY_ENTER))
            {
              //��������� ������ ENTER
              int temp_current_level = current_ekran.current_level;
              
              if (current_ekran.current_level == EKRAN_MEASURMENT)
              {
                //�� � ���� ����������� ������ ���������
                if(current_ekran.index_position == INDEX_ML_MEASURMENT_CURRENT)
                {
                  //���������� �� ���� ������ ����������� ��������� ������
                  current_ekran.current_level = EKRAN_MEASURMENT_CURRENT;
                
                  //�������� ���������� ���������� �� ��������� ������� �������������� - �������� , �� ���������� �� �������� ����� �������
                  pervynna_vtorynna = 0;
                }
                else if(current_ekran.index_position == INDEX_ML_MEASURMENT_VOLTAGE)
                {
                  //���������� �� ���� ������ ����������� ��������� ������
                  current_ekran.current_level = EKRAN_MEASURMENT_VOLTAGE_TYPE;
                
                  //�������� ���������� ���������� �� ��������� ������� �������������� - �������� , �� ���������� �� �������� ����� �������
                  pervynna_vtorynna = 0;
                }
                else if(current_ekran.index_position == INDEX_ML_MEASURMENT_FREQUENCY)
                {
                  //���������� �� ���� ������ ����������� ��������� ������
                  current_ekran.current_level = EKRAN_MEASURMENT_FREQUENCY;
                }
                else if(current_ekran.index_position == INDEX_ML_MEASURMENT_ANGLE)
                {
                  //���������� �� ���� ������ ����������� ��������� ����
                  current_ekran.current_level = EKRAN_MEASURMENT_ANGLE;
                }
                else if(current_ekran.index_position == INDEX_ML_MEASURMENT_POWER)
                {
                  //���������� �� ���� ������ ����������� ��������� �����������
                  current_ekran.current_level = EKRAN_MEASURMENT_POWER;
               
                  //�������� ���������� ���������� �� ��������� ������� �������������� - ��������, �� ���������� �� �������� ����� �������
                  pervynna_vtorynna = 0;
                }
                current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
                current_ekran.edition = 0;
                current_ekran.cursor_on = 1;
                current_ekran.cursor_blinking_on = 0;
              }
              else if (current_ekran.current_level == EKRAN_MEASURMENT_VOLTAGE_TYPE)
              {
                //�� � ���� ����������� ������ ���������
                if(current_ekran.index_position == INDEX_ML_MEASURMENT_VOLTAGE_PHASE)
                {
                  //���������� �� ���� ������ ����������� ��������� ������ ������
                  current_ekran.current_level = EKRAN_MEASURMENT_VOLTAGE_PHASE;
                
                  //�������� ���������� ���������� �� ��������� ������� �������������� - �������� , �� ���������� �� �������� ����� �������
                  pervynna_vtorynna = 0;
                }
                else if(current_ekran.index_position == INDEX_ML_MEASURMENT_VOLTAGE_LINE)
                {
                  //���������� �� ���� ������ ����������� ��������� ������� ������
                  current_ekran.current_level = EKRAN_MEASURMENT_VOLTAGE_LINE;
                
                  //�������� ���������� ���������� �� ��������� ������� �������������� - �������� , �� ���������� �� �������� ����� �������
                  pervynna_vtorynna = 0;
                }
                current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
                current_ekran.edition = 0;
                current_ekran.cursor_on = 1;
                current_ekran.cursor_blinking_on = 0;
              }
              else if (
                       (current_ekran.current_level == EKRAN_MEASURMENT_CURRENT) ||
                       (current_ekran.current_level == EKRAN_MEASURMENT_VOLTAGE_PHASE) ||
                       (current_ekran.current_level == EKRAN_MEASURMENT_VOLTAGE_LINE) ||
                       (current_ekran.current_level == EKRAN_MEASURMENT_POWER)
                      )   
              {
                //�� � ���� ����������� ��� ������, ������, �����������, �����, ������
                
                //������������� �� ������������ ��� �������� ������� � �������� �������
                pervynna_vtorynna ^= 0x1;
              }
              else if (current_ekran.current_level == EKRAN_CHOOSE_SETTINGS_ZDZ)
              {
                //������� ������ Enter � ���� ������ ��������� ��� ���
                if (current_ekran.index_position == INDEX_ML_WITH_CONTROL_CONTROL)
                {
                  //�����'������� ����������� �����
                  //���������� �� ���� ����������� ����������� ���������� ��� ���
                  current_ekran.current_level = EKRAN_CONTROL_ZDZ;
                } 
                current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
                current_ekran.edition = 0;
              }
              else if (current_ekran.current_level == EKRAN_CHOOSE_SETTINGS_APV)
              {
                //������� ������ Enter � ���� ������ �����1-...-�����N-��������� ���
                if(
                   (current_ekran.index_position >= INDEX_ML_GROUP1) &&
                   (current_ekran.index_position <= INDEX_ML_GROUP4)
                  )  
                {
                  //�����'������� ����������� �����
                  //���������� �� ���� ����������� ������ ����� ������� ��� ���
                  current_ekran.current_level = EKRAN_CHOOSE_TIMEOUT_GROUP1_APV + (current_ekran.index_position - INDEX_ML_GROUP1);
                }
                else if (current_ekran.index_position == INDEX_ML_CONTROL_WITH_GROUPS)
                {
                  //�����'������� ����������� �����
                  //���������� �� ���� ����������� ����������� ���������� ��� ���
                  current_ekran.current_level = EKRAN_CONTROL_APV;
                } 
                current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
                current_ekran.edition = 0;
                current_ekran.cursor_on = 1;
                current_ekran.cursor_blinking_on = 0;
              }
              else if (
                       (current_ekran.current_level >= EKRAN_CHOOSE_TIMEOUT_GROUP1_APV) &&
                       (current_ekran.current_level <= EKRAN_CHOOSE_TIMEOUT_GROUP4_APV)
                      )
              {
                //������� ������ Enter � ���� ������ �������� ���
                if(current_ekran.index_position == INDEX_ML_WITH_TIMEOUT_TIMEOUT)
                {
                  //�����'������� ����������� �����
                  //���������� �� ���� ����������� �������� ��� ���
                  current_ekran.current_level = EKRAN_TIMEOUT_APV_GROUP1 + (current_ekran.current_level - EKRAN_CHOOSE_TIMEOUT_GROUP1_APV);
                }
                current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
                current_ekran.edition = 0;
              }
              else if (current_ekran.current_level == EKRAN_CHOOSE_SETTINGS_UROV)
              {
                //������� ������ Enter � ���� ������ �����1-...-�����N-��������� ����
                if(
                   (current_ekran.index_position >= INDEX_ML_GROUP1) &&
                   (current_ekran.index_position <= INDEX_ML_GROUP4)
                  )  
                {
                  //�����'������� ����������� �����
                  //���������� �� ���� ����������� ������ ����� ������� ��� ����
                  current_ekran.current_level = EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP1_UROV + (current_ekran.index_position - INDEX_ML_GROUP1);
                }
                else if (current_ekran.index_position == INDEX_ML_CONTROL_WITH_GROUPS)
                {
                  //�����'������� ����������� �����
                  //���������� �� ���� ����������� ����������� ���������� ��� ����
                  current_ekran.current_level = EKRAN_CONTROL_UROV;
                } 
                current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
                current_ekran.edition = 0;
                current_ekran.cursor_on = 1;
                current_ekran.cursor_blinking_on = 0;
              }
              else if (
                       (current_ekran.current_level >= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP1_UROV) &&
                       (current_ekran.current_level <= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP4_UROV)
                      )
              {
                //������� ������ Enter � ���� ������ �������-�������� ����
                if(current_ekran.index_position == INDEX_ML_SETPOINT)
                {
                  //�����'������� ����������� �����
                  //���������� �� ���� ����������� ������� ��� ����
                  current_ekran.current_level = EKRAN_SETPOINT_UROV_GROUP1 + (current_ekran.current_level - EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP1_UROV);
                }
                else if(current_ekran.index_position == INDEX_ML_TIMEOUT)
                {
                  //�����'������� ����������� �����
                  //���������� �� ���� ����������� �������� ��� ����
                  current_ekran.current_level = EKRAN_TIMEOUT_UROV_GROUP1 + (current_ekran.current_level - EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP1_UROV);
                }
                current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
                current_ekran.edition = 0;
              }
              else if (current_ekran.current_level == EKRAN_CHOOSE_SETTINGS_ZOP)
              {
                //������� ������ Enter � ���� ������ �����1-...-�����N-��������� ���(���)
                if(
                   (current_ekran.index_position >= INDEX_ML_GROUP1) &&
                   (current_ekran.index_position <= INDEX_ML_GROUP4)
                  )  
                {
                  //�����'������� ����������� �����
                  //���������� �� ���� ����������� ������ ����� ������� ��� ���(���)
                  current_ekran.current_level = EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP1_ZOP + (current_ekran.index_position - INDEX_ML_GROUP1);
                }
                else if (current_ekran.index_position == INDEX_ML_CONTROL_WITH_GROUPS)
                {
                  //�����'������� ����������� �����
                  //���������� �� ���� ����������� ����������� ���������� ��� ���(���)
                  current_ekran.current_level = EKRAN_CONTROL_ZOP;
                } 
                current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
                current_ekran.edition = 0;
                current_ekran.cursor_on = 1;
                current_ekran.cursor_blinking_on = 0;
              }
              else if (
                       (current_ekran.current_level >= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP1_ZOP) &&
                       (current_ekran.current_level <= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP4_ZOP)
                      )
              {
                //������� ������ Enter � ���� ������ �������-�������� ���(���)
                if(current_ekran.index_position == INDEX_ML_SETPOINT)
                {
                  //�����'������� ����������� �����
                  //���������� �� ���� ����������� ������� ��� ���(���)
                  current_ekran.current_level = EKRAN_SETPOINT_ZOP_GROUP1 + (current_ekran.current_level - EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP1_ZOP);
                }
                else if(current_ekran.index_position == INDEX_ML_TIMEOUT)
                {
                  //�����'������� ����������� �����
                  //���������� �� ���� ����������� �������� ��� ���(���)
                  current_ekran.current_level = EKRAN_TIMEOUT_ZOP_GROUP1 + (current_ekran.current_level - EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP1_ZOP);
                }
                current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
                current_ekran.edition = 0;
              }
              else if (current_ekran.current_level == EKRAN_CHOOSE_SETTINGS_UMIN)
              {
                //������� ������ Enter � ���� ������ �����1-...-�����N-��������� Umin
                if(
                   (current_ekran.index_position >= INDEX_ML_GROUP1) &&
                   (current_ekran.index_position <= INDEX_ML_GROUP4)
                  )  
                {
                  //�����'������� ����������� �����
                  //���������� �� ���� ����������� ������ ����� ������� ��� Umin
                  current_ekran.current_level = EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP1_UMIN + (current_ekran.index_position - INDEX_ML_GROUP1);
                }
                else if (current_ekran.index_position == INDEX_ML_CONTROL_WITH_GROUPS)
                {
                  //�����'������� ����������� �����
                  //���������� �� ���� ����������� ����������� ���������� ��� Umin
                  current_ekran.current_level = EKRAN_CONTROL_UMIN;
                } 
                current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
                current_ekran.edition = 0;
                current_ekran.cursor_on = 1;
                current_ekran.cursor_blinking_on = 0;
              }
              else if (
                       (current_ekran.current_level >= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP1_UMIN) &&
                       (current_ekran.current_level <= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP4_UMIN)
                      )
              {
                //������� ������ Enter � ���� ������ �������-�������� Umin
                if(current_ekran.index_position == INDEX_ML_SETPOINT)
                {
                  //�����'������� ����������� �����
                  //���������� �� ���� ����������� ������� ��� Umin
                  current_ekran.current_level = EKRAN_SETPOINT_UMIN_GROUP1 + (current_ekran.current_level - EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP1_UMIN);
                }
                else if(current_ekran.index_position == INDEX_ML_TIMEOUT)
                {
                  //�����'������� ����������� �����
                  //���������� �� ���� ����������� �������� ��� Umin
                  current_ekran.current_level = EKRAN_TIMEOUT_UMIN_GROUP1 + (current_ekran.current_level - EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP1_UMIN);
                }
                current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
                current_ekran.edition = 0;
              }
              else if (current_ekran.current_level == EKRAN_CHOOSE_SETTINGS_UMAX)
              {
                //������� ������ Enter � ���� ������ �����1-...-�����N-��������� Umax
                if(
                   (current_ekran.index_position >= INDEX_ML_GROUP1) &&
                   (current_ekran.index_position <= INDEX_ML_GROUP4)
                  )  
                {
                  //�����'������� ����������� �����
                  //���������� �� ���� ����������� ������ ����� ������� ��� Umax
                  current_ekran.current_level = EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP1_UMAX + (current_ekran.index_position - INDEX_ML_GROUP1);
                }
                else if (current_ekran.index_position == INDEX_ML_CONTROL_WITH_GROUPS)
                {
                  //�����'������� ����������� �����
                  //���������� �� ���� ����������� ����������� ���������� ��� Umax
                  current_ekran.current_level = EKRAN_CONTROL_UMAX;
                } 
                current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
                current_ekran.edition = 0;
                current_ekran.cursor_on = 1;
                current_ekran.cursor_blinking_on = 0;
              }
              else if (
                       (current_ekran.current_level >= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP1_UMAX) &&
                       (current_ekran.current_level <= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP4_UMAX)
                      )
              {
                //������� ������ Enter � ���� ������ �������-�������� Umax
                if(current_ekran.index_position == INDEX_ML_SETPOINT)
                {
                  //�����'������� ����������� �����
                  //���������� �� ���� ����������� ������� ��� Umax
                  current_ekran.current_level = EKRAN_SETPOINT_UMAX_GROUP1 + (current_ekran.current_level - EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP1_UMAX);
                }
                else if(current_ekran.index_position == INDEX_ML_TIMEOUT)
                {
                  //�����'������� ����������� �����
                  //���������� �� ���� ����������� �������� ��� Umax
                  current_ekran.current_level = EKRAN_TIMEOUT_UMAX_GROUP1 + (current_ekran.current_level - EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP1_UMAX);
                }
                current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
                current_ekran.edition = 0;
              }
              else if (current_ekran.current_level == EKRAN_CHOOSE_SETTINGS_AVR)
              {
                //������� ������ Enter � ���� ������ �����1-...-�����N-��������� ���
                if(
                   (current_ekran.index_position >= INDEX_ML_GROUP1) &&
                   (current_ekran.index_position <= INDEX_ML_GROUP4)
                  )  
                {
                  //�����'������� ����������� �����
                  //���������� �� ���� ����������� ������ ����� ������� ��� ���
                  current_ekran.current_level = EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP1_AVR + (current_ekran.index_position - INDEX_ML_GROUP1);
                }
                else if (current_ekran.index_position == INDEX_ML_CONTROL_WITH_GROUPS)
                {
                  //�����'������� ����������� �����
                  //���������� �� ���� ����������� ����������� ���������� ��� ���
                  current_ekran.current_level = EKRAN_CONTROL_AVR;
                } 
                current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
                current_ekran.edition = 0;
                current_ekran.cursor_on = 1;
                current_ekran.cursor_blinking_on = 0;
              }
              else if (
                       (current_ekran.current_level >= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP1_AVR) &&
                       (current_ekran.current_level <= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP4_AVR)
                      )
              {
                //������� ������ Enter � ���� ������ �������-�������� ���
                if(current_ekran.index_position == INDEX_ML_SETPOINT_AVR_UMIN)
                {
                  //�����'������� ����������� �����
                  //���������� �� ���� ����������� ������� ��� ��� Umin
                  current_ekran.current_level = EKRAN_SETPOINT_AVR_UMIN_GROUP1 + (current_ekran.current_level - EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP1_AVR);
                }
                else if(current_ekran.index_position == INDEX_ML_SETPOINT_AVR_UMAX)
                {
                  //�����'������� ����������� �����
                  //���������� �� ���� ����������� ������� ��� ��� Umax
                  current_ekran.current_level = EKRAN_SETPOINT_AVR_UMAX_GROUP1 + (current_ekran.current_level - EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP1_AVR);
                }
                else if(current_ekran.index_position == INDEX_ML_TIMEOUT_AVR_GENERAL)
                {
                  //�����'������� ����������� �����
                  //���������� �� ���� ����������� �������� ��� ��� (��������)
                  current_ekran.current_level = EKRAN_TIMEOUT_AVR_GENERAL_GROUP1 + (current_ekran.current_level - EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP1_AVR);
                }
                else if(current_ekran.index_position == INDEX_ML_TIMEOUT_AVR_UMIN)
                {
                  //�����'������� ����������� �����
                  //���������� �� ���� ����������� �������� ��� ��� Umin
                  current_ekran.current_level = EKRAN_TIMEOUT_AVR_UMIN_GROUP1 + (current_ekran.current_level - EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP1_AVR);
                }
                else if(current_ekran.index_position == INDEX_ML_TIMEOUT_AVR_UMAX)
                {
                  //�����'������� ����������� �����
                  //���������� �� ���� ����������� �������� ��� ��� Umax
                  current_ekran.current_level = EKRAN_TIMEOUT_AVR_UMAX_GROUP1 + (current_ekran.current_level - EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP1_AVR);
                }
                current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
                current_ekran.edition = 0;
              }
              else if (current_ekran.current_level == EKRAN_CHOOSE_SETTINGS_CTRL_PHASE)
              {
                //������� ������ Enter � ���� ������ �����1-...-�����N-��������� "�������� ���������"
                if(
                   (current_ekran.index_position >= INDEX_ML_GROUP1) &&
                   (current_ekran.index_position <= INDEX_ML_GROUP4)
                  )  
                {
                  //�����'������� ����������� �����
                  //���������� �� ���� ����������� ������ ����� ������� ��� "�������� ���������"
                  current_ekran.current_level = EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP1_CTRL_PHASE + (current_ekran.index_position - INDEX_ML_GROUP1);
                }
                else if (current_ekran.index_position == INDEX_ML_CONTROL_WITH_GROUPS)
                {
                  //�����'������� ����������� �����
                  //���������� �� ���� ����������� ����������� ���������� ��� "�������� ���������"
                  current_ekran.current_level = EKRAN_CONTROL_CTRL_PHASE;
                } 
                current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
                current_ekran.edition = 0;
                current_ekran.cursor_on = 1;
                current_ekran.cursor_blinking_on = 0;
              }
              else if (
                       (current_ekran.current_level >= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP1_CTRL_PHASE) &&
                       (current_ekran.current_level <= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP4_CTRL_PHASE)
                      )
              {
                //������� ������ Enter � ���� ������ �������-�������� "�������� ���������"
                if(current_ekran.index_position == INDEX_ML_SETPOINT)
                {
                  //�����'������� ����������� �����
                  //���������� �� ���� ����������� ������� ��� "�������� ���������"
                  current_ekran.current_level = EKRAN_SETPOINT_CTRL_PHASE_GROUP1 + (current_ekran.current_level - EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP1_CTRL_PHASE);
                }
                else if(current_ekran.index_position == INDEX_ML_TIMEOUT)
                {
                  //�����'������� ����������� �����
                  //���������� �� ���� ����������� �������� ��� "�������� ���������"
                  current_ekran.current_level = EKRAN_TIMEOUT_CTRL_PHASE_GROUP1 + (current_ekran.current_level - EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP1_CTRL_PHASE);
                }
                current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
                current_ekran.edition = 0;
              }
              else if (current_ekran.current_level == EKRAN_TRANSFORMATOR_INFO)
              {
                //������� ������ Enter � ���� ������ �������-��������� ��������������
                if(current_ekran.index_position == INDEX_ML_WITH_SETPOINT_CONTROL_SETPOINT)
                {
                  //�����'������� ����������� �����
                  //���������� �� ���� ����������� ������� ��� ��������
                  current_ekran.current_level = EKRAN_TRANSFORMATOR_INFO_SETPOINT;
                }
                else if (current_ekran.index_position == INDEX_ML_WITH_SETPOINT_CONTROL_CONTROL)
                {
                  //�����'������� ����������� �����
                  //���������� �� ���� ����������� ����������� ���������� ��� ��������
                  current_ekran.current_level = EKRAN_TRANSFORMATOR_INFO_CONTROL;
                } 
                current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
                current_ekran.edition = 0;
                current_ekran.cursor_on = 1;
                current_ekran.cursor_blinking_on = 0;
              }
              else if (current_ekran.current_level == EKRAN_CHOOSE_SETTINGS_SWITCHER)
              {
                //������� ������ Enter � ���� ������ ��������� �����������
                if(current_ekran.index_position == INDEX_ML_SETPOINT_SWITCHER)
                {
                  //�����'������� ����������� �����
                  //���������� �� ���� ����������� ������� ��� ��������
                  current_ekran.current_level = EKRAN_SETPOINT_SWITCH;
                }
                else if (current_ekran.index_position == INDEX_ML_TIMEOUT_SWITCHER)
                {
                  //�����'������� ����������� �����
                  //���������� �� ���� ����������� �������� ��� ��������
                  current_ekran.current_level = EKRAN_TIMEOUT_SWITCH;
                } 
                else if (current_ekran.index_position == INDEX_ML_CONTROL_SWITCHER)
                {
                  //�����'������� ����������� �����
                  //���������� �� ���� ����������� ����������� ���������� ��� ��������
                  current_ekran.current_level = EKRAN_CONTROL_SWITCH;
                } 
                else if (current_ekran.index_position == INDEX_ML_RANG_SWITCHER)
                {
                  //�����'������� ����������� �����
                  //���������� �� ���� ����������� ���������� ��������� ���������
                  current_ekran.current_level = EKRAN_CHOOSE_RANG_SWITCH;
                } 
                current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
                current_ekran.edition = 0;
                current_ekran.cursor_on = 1;
                current_ekran.cursor_blinking_on = 0;
              }
              else if (current_ekran.current_level == EKRAN_CHOOSE_RANG_SWITCH)
              {
                //������� ������ Enter � ���� ������ �����./�����.
                if(current_ekran.index_position == INDEX_ML_RANG_OFF_CB)
                {
                  //�����'������� ����������� �����
                  //���������� �� ���� ����������� ���������� ������.
                  current_ekran.current_level = EKRAN_RANGUVANNJA_OFF_CB;
                  //��� ����, ��� ��� ������� ��������� ������ ������ ��������� �� ����� ��������� ������� ��������� �� �������
                  position_in_current_level_menu[current_ekran.current_level] = 0;
                }
                else if (current_ekran.index_position == INDEX_ML_RANG_ON_CB)
                {
                  //�����'������� ����������� �����
                  //���������� �� ���� ����������� ���������� ������.
                  current_ekran.current_level = EKRAN_RANGUVANNJA_ON_CB;
                  //��� ����, ��� ��� ������� ��������� ������ ������ ��������� �� ����� ��������� ������� ��������� �� �������
                  position_in_current_level_menu[current_ekran.current_level] = 0;
                } 
                current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
                current_ekran.edition = 0;
                current_ekran.cursor_on = 1;
                current_ekran.cursor_blinking_on = 0;
              }
              else if (current_ekran.current_level == EKRAN_CHOSE_SETTINGS)
              {
                //������� ������ Enter � ���� ������ ���������
                if(current_ekran.index_position == INDEX_OF_INFO)
                {
                  //�����'������� ����������� �����
                  //���������� �� ���� ����������� ���������� �� ���� ����������� ������������ � ���� ����� ���'��
                  current_ekran.current_level = EKRAN_INFO;
                }
                else if(current_ekran.index_position == INDEX_OF_SETTINGS_POINT)
                {
                  //�����'������� ����������� �����
                  //���������� �� ���� ����������� ������ ���� ���������
                  current_ekran.current_level = EKRAN_POINT_TIME_SETTINGS;
                }
                else if(current_ekran.index_position == INDEX_OF_INPUTS_RANGUVANNJA)
                {
                  //�����'������� ����������� �����
                  //���������� �� ���� ����������� ������ ���������� �����
                  current_ekran.current_level = EKRAN_LIST_INPUTS_FOR_RANGUVANNJA;
                }
                else if(current_ekran.index_position == INDEX_OF_OUTPUTS_RANGUVANNJA)
                {
                  //�����'������� ����������� �����
                  //���������� �� ���� ����������� ������ ���������� ������
                  current_ekran.current_level = EKRAN_LIST_OUTPUTS_FOR_RANGUVANNJA;
                }
                else if(current_ekran.index_position == INDEX_OF_LEDS_RANGUVANNJA)
                {
                  //�����'������� ����������� �����
                  //���������� �� ���� ����������� ������ ���������� ��������
                  current_ekran.current_level = EKRAN_LIST_LEDS_FOR_RANGUVANNJA;
                }
                else if(current_ekran.index_position == INDEX_OF_SWITCHER)
                {
                  //�����'������� ����������� �����
                  //���������� �� ���� ����������� ������ ��������� �����������
                  current_ekran.current_level = EKRAN_CHOOSE_SETTINGS_SWITCHER;
                }
                else if(current_ekran.index_position == INDEX_OF_TRANSFORMATOR)
                {
                  //�����'������� ����������� �����
                  //���������� �� ���� ����������� ��������� �������������
                  current_ekran.current_level = EKRAN_TRANSFORMATOR_INFO;
                }
                else if(current_ekran.index_position == INDEX_OF_CONTROL_INPUTS_OUTPUTS)
                {
                  //�����'������� ����������� �����
                  //���������� �� ���� ����������� ��������� ���
                  current_ekran.current_level = EKRAN_CHOOSE_SETTINGS_UVV;
                }
                else if(current_ekran.index_position == INDEX_OF_COMMUNICATION)
                {
                  //�����'������� ����������� �����
                  //���������� �� ���� ����������� ��������� �����������
                  current_ekran.current_level = EKRAN_CHOSE_COMMUNICATION_PARAMETERS;
                }
                else if(current_ekran.index_position == INDEX_OF_REGISTRATORS)
                {
                  //�����'������� ����������� �����
                  //���������� �� ���� ����������� ������ ������� ����������
                  current_ekran.current_level = EKRAN_VIEW_LIST_OF_REGISTRATORS;
                }
                else if(current_ekran.index_position == INDEX_OF_EXTENDED_LOGIC)
                {
                  //�����'������� ����������� �����
                  //���������� �� ���� ����������� ������ ��������� �����
                  current_ekran.current_level = EKRAN_EXTENDED_LIGIC;
                }
                else if(current_ekran.index_position == INDEX_OF_DEFINED_BUTTONS)
                {
                  //�����'������� ����������� �����
                  //���������� �� ���� ����������� ������ ������������ �������������� ������
                  current_ekran.current_level = EKRAN_LIST_BUTTONS_FOR_RANGUVANNJA;
                }
                else if(current_ekran.index_position == INDEX_OF_EXTRA_SETTINGS)
                {
                  //�����'������� ����������� �����
                  //���������� �� ���� ���������� ����������
                  current_ekran.current_level = EKRAN_CHOSE_EXTRA_SETTINGS;
                }
                else if(current_ekran.index_position == INDEX_OF_LIST_PASSWORDS)
                {
                  //�����'������� ����������� �����
                  //���������� �� ���� ������ ������
                  current_ekran.current_level = EKRAN_LEVEL_CHOOSE_PASSWORDS;
                }
//                else if(current_ekran.index_position == INDEX_OF_PASSWORD)
//                {
//                  //�����'������� ����������� �����
//                  //���������� �� ���� ���� ������
//                  current_ekran.current_level = EKRAN_LEVEL_SET_NEW_PASSWORD;
//                }
                current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
                current_ekran.edition = 0;
//                if (current_ekran.current_level != EKRAN_LEVEL_SET_NEW_PASSWORD) current_ekran.edition = 0;
//                else current_ekran.edition = 1;
              }
              else if (current_ekran.current_level == EKRAN_LEVEL_CHOOSE_PASSWORDS)
              {
                //������� ������ Enter � ���� ������ ������
                if(current_ekran.index_position == INDEX_OF_PASSWORD1)
                {
                  //�����'������� ����������� �����
                  //���������� �� ���� ���� ������
                  current_ekran.current_level = EKRAN_LEVEL_SET_NEW_PASSWORD1;
                }
                else
                {
                  //�����'������� ����������� �����
                  //���������� �� ���� ���� ������
                  current_ekran.current_level = EKRAN_LEVEL_SET_NEW_PASSWORD2;
                }
                current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
                current_ekran.edition = 1;
              }
              else if (current_ekran.current_level == EKRAN_LIST_INPUTS_FOR_RANGUVANNJA)
              {
                //�����'������� ����������� �����
                //���������� �� ���� ����������� ������ ���������� �������
                current_ekran.current_level = EKRAN_RANGUVANNJA_INPUT_1 + current_ekran.index_position;
                //��� ����, ��� ��� ������� ��������� ������ ������ ��������� �� ����� ��������� ������� ��������� �� �������
                position_in_current_level_menu[current_ekran.current_level] = 0;
                current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
                current_ekran.edition = 0;
              }
              else if (current_ekran.current_level == EKRAN_LIST_OUTPUTS_FOR_RANGUVANNJA)
              {
                //�����'������� ����������� �����
                //���������� �� ���� ����������� ������ ���������� �������
                current_ekran.current_level = EKRAN_RANGUVANNJA_OUTPUT_1 + current_ekran.index_position;
                //��� ����, ��� ��� ������� ��������� ������ ������ ��������� �� ����� ��������� ������� ��������� �� �������
                position_in_current_level_menu[current_ekran.current_level] = 0;
                current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
                current_ekran.edition = 0;
              }
              else if (current_ekran.current_level == EKRAN_LIST_LEDS_FOR_RANGUVANNJA)
              {
                //�����'������� ����������� �����
                //���������� �� ���� ����������� ������ ���������� �������
                current_ekran.current_level = EKRAN_RANGUVANNJA_LED_1 + current_ekran.index_position;
                //��� ����, ��� ��� ������� ��������� ������ ������ ��������� �� ����� ��������� ������� ��������� �� �������
                position_in_current_level_menu[current_ekran.current_level] = 0;
                current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
                current_ekran.edition = 0;
              }
              else if (current_ekran.current_level == EKRAN_CHOOSE_SETTINGS_UVV)
              {
                //������� ������ Enter � ���� ������ ���� ��������� ���
                if(current_ekran.index_position == INDEX_ML_UVV_DOPUSKT)
                {
                  //�����'������� ����������� �����
                  //���������� �� ���� ����������� ������ ���������� �����
                  current_ekran.current_level = EKRAN_DOPUSK_DV_UVV;
                }
                else if(current_ekran.index_position == INDEX_ML_UVV_TYPE_INPUT)
                {
                  //�����'������� ����������� �����
                  //���������� �� ���� ����������� ������ ���������� �����
                  current_ekran.current_level = EKRAN_TYPE_INPUT_UVV;
                }
                else if(current_ekran.index_position == INDEX_ML_UVV_TYPE_INPUT_SIGNAL)
                {
                  //�����'������� ����������� �����
                  //���������� �� ���� ����������� ������ ���������� �����
                  current_ekran.current_level = EKRAN_TYPE_INPUT_SIGNAL_UVV;
                }
                else if(current_ekran.index_position == INDEX_ML_UVV_TYPE_OUTPUT)
                {
                  //�����'������� ����������� �����
                  //���������� �� ���� ����������� ���� ������
                  current_ekran.current_level = EKRAN_TYPE_OUTPUT_UVV;
                }
                else if(current_ekran.index_position == INDEX_ML_UVV_TYPE_LED)
                {
                  //�����'������� ����������� �����
                  //���������� �� ���� ����������� ���� ���������������
                  current_ekran.current_level = EKRAN_TYPE_LED_UVV;
                }
                current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
                current_ekran.edition = 0;
              }
              else if (current_ekran.current_level == EKRAN_CHOSE_COMMUNICATION_PARAMETERS)
              {
                //������� ������ Enter � ���� ������ ���� ��������� �����������
                if(current_ekran.index_position == INDEX_ML_CHCP_NAME)
                {
                  //�����'������� ����������� �����
                  //���������� �� ���� ����������� ����� ������
                  current_ekran.current_level = EKRAN_VIEW_NAME_OF_CELL;
                }
                else if(current_ekran.index_position == INDEX_ML_CHCP_ADDRESS)
                {
                  //�����'������� ����������� �����
                  //���������� �� ���� ����������� �������� ������
                  current_ekran.current_level = EKRAN_ADDRESS;
                }
                else if(current_ekran.index_position == INDEX_ML_CHCP_SETTING_RS485)
                {
                  //�����'������� ����������� �����
                  //���������� �� ���� ����������� �������� ������
                  current_ekran.current_level = EKRAN_CHOSE_SETTING_RS485;
                }
                current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
                current_ekran.edition = 0;
              }
              else if (current_ekran.current_level == EKRAN_CHOSE_SETTING_RS485)
              {
                //������� ������ Enter � ���� ������ ���� ��������� RS-485
                if(current_ekran.index_position == INDEX_ML_CHSRS485_SPEED)
                {
                  //�����'������� ����������� �����
                  //���������� �� ���� ����������� �������� �����
                  current_ekran.current_level = EKRAN_VIEW_SPEED_RS485;
                }
                else if(current_ekran.index_position == INDEX_ML_CHSRS485_PARE_BIT)
                {
                  //�����'������� ����������� �����
                  //���������� �� ���� ����������� ���������� �� �����������
                  current_ekran.current_level = EKRAN_VIEW_PARE_RS485;
                }
                else if(current_ekran.index_position == INDEX_ML_CHSRS485_NUMBER_STOP_BIT)
                {
                  //�����'������� ����������� �����
                  //���������� �� ���� ����������� ���������� �� ����-���
                  current_ekran.current_level = EKRAN_VIEW_STOP_BITS_RS485;
                }
                else if(current_ekran.index_position == INDEX_ML_CHSRS485_TIMEOUT)
                {
                  //�����'������� ����������� �����
                  //���������� �� ���� ����������� ���������� �� time-out ���������� �������
                  current_ekran.current_level = EKRAN_VIEW_TIMEOUT_RS485;
                }
                current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
                current_ekran.edition = 0;
              }
              else if (current_ekran.current_level == EKRAN_VIEW_LIST_OF_REGISTRATORS)
              {
                if(current_ekran.index_position == INDEX_ML_DIGITAL_REGISTRATOR)
                {
                  //�����'������� ����������� �����
                  //���������� �� ���� ����������� ������ ���������� ������� ��� ����������� ����������
                  current_ekran.current_level = EKRAN_RANGUVANNJA_DIGITAL_REGISTRATOR;
                  //��� ����, ��� ��� ������� ��������� ������ ������ ��������� �� ����� ��������� ������� ��������� �� �������
                  position_in_current_level_menu[current_ekran.current_level] = 0;
                }
                else if(current_ekran.index_position == INDEX_ML_ANALOG_REGISTRATOR)
                {
                  //�����'������� ����������� �����
                  //���������� �� ���� ����������� ������ ��������� ��� ����������� ����������
                  current_ekran.current_level = EKRAN_VIEW_SETTINGS_OF_ANALOG_REGISTRATORS;
                }
                current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
                current_ekran.edition = 0;
              }
              else if (current_ekran.current_level == EKRAN_VIEW_SETTINGS_OF_ANALOG_REGISTRATORS)
              {
                if(current_ekran.index_position == INDEX_ML_SOURCE_ANALOG_REGISTRATOR)
                {
                  //�����'������� ����������� �����
                  //���������� �� ���� ����������� ������ ���������� ������� ��� ����������� ����������
                  current_ekran.current_level = EKRAN_RANGUVANNJA_ANALOG_REGISTRATOR;
                  //��� ����, ��� ��� ������� ��������� ������ ������ ��������� �� ����� ��������� ������� ��������� �� �������
                  position_in_current_level_menu[current_ekran.current_level] = 0;
                }
                else if(current_ekran.index_position == INDEX_ML_TIMEOUT_ANALOG_REGISTRATOR)
                {
                  //�����'������� ����������� �����
                  //���������� �� ���� ����������� �������� ��� ����������� ����������
                  current_ekran.current_level = EKRAN_TIMEOUT_ANALOG_REGISTRATOR;
                }
                current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
                current_ekran.edition = 0;
              }
              else if (current_ekran.current_level == EKRAN_EXTENDED_LIGIC)
              {
                if(current_ekran.index_position == INDEX_OF_GENERAL_PICKUP_EL)
                {
                  //�����'������� ����������� �����
                  //���������� �� ���� ����������� ��������� ������� ��� ��������� �����
                  current_ekran.current_level = EKRAN_GENERAL_PICKUPS_EL;
                }
                else if(current_ekran.index_position == INDEX_OF_DEFINED_FUNCTIONS)
                {
                  //�����'������� ����������� �����
                  //���������� �� ���� ����������� ������ ������������ �������������� �������
                  current_ekran.current_level = EKRAN_LIST_SETTINGS_FOR_DF;
                }
                else if(current_ekran.index_position == INDEX_OF_DEFINED_TRIGGERS)
                {
                  //�����'������� ����������� �����
                  //���������� �� ���� ����������� ������ �������������� ������
                  current_ekran.current_level = EKRAN_LIST_DT;
                }
                else if(current_ekran.index_position == INDEX_OF_DEFINED_AND)
                {
                  //�����'������� ����������� �����
                  //���������� �� ���� ����������� ������ ������������ "�"
                  current_ekran.current_level = EKRAN_LIST_D_AND;
                }
                else if(current_ekran.index_position == INDEX_OF_DEFINED_OR)
                {
                  //�����'������� ����������� �����
                  //���������� �� ���� ����������� ������ ������������ "���"
                  current_ekran.current_level = EKRAN_LIST_D_OR;
                }
                else if(current_ekran.index_position == INDEX_OF_DEFINED_XOR)
                {
                  //�����'������� ����������� �����
                  //���������� �� ���� ����������� ������ ������������ "����.���"
                  current_ekran.current_level = EKRAN_LIST_D_XOR;
                }
                else if(current_ekran.index_position == INDEX_OF_DEFINED_NOT)
                {
                  //�����'������� ����������� �����
                  //���������� �� ���� ����������� ������ ������������ "��"
                  current_ekran.current_level = EKRAN_LIST_D_NOT;
                }
                current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
                current_ekran.edition = 0;
              }
              else if (current_ekran.current_level == EKRAN_LIST_SETTINGS_FOR_DF)
              {
                //������� ������ Enter � ���� ������ ���� ��������� �������������� �������
                if(current_ekran.index_position == INDEX_ML_SETTING_DF_SOURCE)
                {
                  //�����'������� ����������� �����
                  //���������� �� ���� ����������� ������ �������������� ������� ��� �� ����������
                  current_ekran.current_level = EKRAN_LIST_DF_FOR_RANGUVANNJA;
                }
                else if(current_ekran.index_position == INDEX_ML_SETTING_DF_TIMEOUT)
                {
                  //�����'������� ����������� �����
                  //���������� �� ���� ����������� ������ �������������� ������� ��� �� �������������� ���� ����� � ������
                  current_ekran.current_level = EKRAN_LIST_DF_FOR_TIMEOUT_SETTINGS;
                }
                else if(current_ekran.index_position == INDEX_ML_SETTING_DF_TYPE)
                {
                  //�����'������� ����������� �����
                  //���������� �� ���� ����������� ���� �������������� �������
                  current_ekran.current_level = EKRAN_LIST_TYPE_DF;
                }
                current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
                current_ekran.edition = 0;
              }
              else if (current_ekran.current_level == EKRAN_LIST_DF_FOR_TIMEOUT_SETTINGS)
              {
                //�����'������� ����������� �����
                //���������� �� ���� ����������� ������ ���������� �������
                current_ekran.current_level = EKRAN_TIMEOUT_DF1 + current_ekran.index_position;
                current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
                current_ekran.edition = 0;
              }
              else if (current_ekran.current_level == EKRAN_LIST_DF_FOR_RANGUVANNJA)
              {
                //�����'������� ����������� �����
                //���������� �� ���� ����������� ������ ���� ������ ��� ���������� ����������� �������
                current_ekran.current_level = EKRAN_LIST_TYPE_SOURCE_DF1 + current_ekran.index_position;
                current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
                current_ekran.edition = 0;
              }
              else if ((current_ekran.current_level >= EKRAN_LIST_TYPE_SOURCE_DF1) && (current_ekran.current_level <= EKRAN_LIST_TYPE_SOURCE_DF8))
              {
                //�����'������� ����������� �����
                //���������� �� ���� ����������� ������ ���������� �������
                current_ekran.current_level = EKRAN_RANGUVANNJA_DF1_PLUS + 3*(current_ekran.current_level - EKRAN_LIST_TYPE_SOURCE_DF1) + current_ekran.index_position;
                //��� ����, ��� ��� ������� ��������� ������ ������ ��������� �� ����� ��������� ������� ��������� �� �������
                position_in_current_level_menu[current_ekran.current_level] = 0;
                current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
                current_ekran.edition = 0;
              }
              else if (current_ekran.current_level == EKRAN_LIST_DT)
              {
                //�����'������� ����������� �����
                //���������� �� ���� ����������� ��������� ���������-����������� �������������� ������
                current_ekran.current_level = EKRAN_SET_RESET_DT1 + current_ekran.index_position;
                current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
                current_ekran.edition = 0;
              }
              else if ((current_ekran.current_level >= EKRAN_SET_RESET_DT1) && (current_ekran.current_level <= EKRAN_SET_RESET_DT4))
              {
                //�����'������� ����������� �����
                //���������� �� ���� ����������� ��������� ������ ���������-����������� �������������� ������
                current_ekran.current_level = EKRAN_SET_DT1 + 2*(current_ekran.current_level - EKRAN_SET_RESET_DT1) + current_ekran.index_position;
                current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
                current_ekran.edition = 0;
              }
              else if ((current_ekran.current_level >= EKRAN_SET_DT1) && (current_ekran.current_level <= EKRAN_RESET_DT4))
              {
                //�����'������� ����������� �����
                //���������� �� ���� ����������� ������ ���������� �������
                current_ekran.current_level = EKRAN_RANGUVANNJA_SET_DT1_PLUS + 2*(current_ekran.current_level - EKRAN_SET_DT1) + current_ekran.index_position;
                //��� ����, ��� ��� ������� ��������� ������ ������ ��������� �� ����� ��������� ������� ��������� �� �������
                position_in_current_level_menu[current_ekran.current_level] = 0;
                current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
                current_ekran.edition = 0;
              }
              else if (current_ekran.current_level == EKRAN_LIST_D_AND)
              {
                //�����'������� ����������� �����
                //���������� �� ���� ����������� ������ ���������� �������
                current_ekran.current_level = EKRAN_RANGUVANNJA_D_AND1 + current_ekran.index_position;
                //��� ����, ��� ��� ������� ��������� ������ ������ ��������� �� ����� ��������� ������� ��������� �� �������
                position_in_current_level_menu[current_ekran.current_level] = 0;
                current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
                current_ekran.edition = 0;
              }
              else if (current_ekran.current_level == EKRAN_LIST_D_OR)
              {
                //�����'������� ����������� �����
                //���������� �� ���� ����������� ������ ���������� �������
                current_ekran.current_level = EKRAN_RANGUVANNJA_D_OR1 + current_ekran.index_position;
                //��� ����, ��� ��� ������� ��������� ������ ������ ��������� �� ����� ��������� ������� ��������� �� �������
                position_in_current_level_menu[current_ekran.current_level] = 0;
                current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
                current_ekran.edition = 0;
              }
              else if (current_ekran.current_level == EKRAN_LIST_D_XOR)
              {
                //�����'������� ����������� �����
                //���������� �� ���� ����������� ������ ���������� �������
                current_ekran.current_level = EKRAN_RANGUVANNJA_D_XOR1 + current_ekran.index_position;
                //��� ����, ��� ��� ������� ��������� ������ ������ ��������� �� ����� ��������� ������� ��������� �� �������
                position_in_current_level_menu[current_ekran.current_level] = 0;
                current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
                current_ekran.edition = 0;
              }
              else if (current_ekran.current_level == EKRAN_LIST_D_NOT)
              {
                //�����'������� ����������� �����
                //���������� �� ���� ����������� ������ ���������� �������
                current_ekran.current_level = EKRAN_RANGUVANNJA_D_NOT1 + current_ekran.index_position;
                //��� ����, ��� ��� ������� ��������� ������ ������ ��������� �� ����� ��������� ������� ��������� �� �������
                position_in_current_level_menu[current_ekran.current_level] = 0;
                current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
                current_ekran.edition = 0;
              }
              else if (current_ekran.current_level == EKRAN_LIST_BUTTONS_FOR_RANGUVANNJA)
              {
                //�����'������� ����������� �����
                //���������� �� ���� ����������� ������ ���������� �������
                current_ekran.current_level = EKRAN_RANGUVANNJA_BUTTON_1 + current_ekran.index_position;
                //��� ����, ��� ��� ������� ��������� ������ ������ ��������� �� ����� ��������� ������� ��������� �� �������
                position_in_current_level_menu[current_ekran.current_level] = 0;
                current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
                current_ekran.edition = 0;
              }
              else if (current_ekran.current_level == EKRAN_INFO)
              {
                //������� ������ Enter � ���� ���������� �� ���� �������� � ����� ���'��
                if(current_ekran.index_position == INDEX_ML_INFO_FIRMWARE)
                {
                  //�����'������� ����������� �����
                  //���������� �� ���� ����������� ����� � ���� ��������� ��������
                  current_ekran.current_level = EKRAN_DATE_TIME_PZ;

                  current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
                  current_ekran.edition = 0;
                }
              }
              else if (current_ekran.current_level == EKRAN_POINT_TIME_SETTINGS)
              {
                //������� ������ Enter � ���� ������ ���� �������� ���������
                if(current_ekran.index_position == INDEX_ML_TIME_SETPOINT)
                {
                  //�����'������� ����������� �����
                  //���������� �� ���� ����������� ���� �������� �������� �������-��������-����������� ����������
                  current_ekran.current_level = EKRAN_POINT_TIME_SETPOINT;
                }
                else if(current_ekran.index_position == INDEX_ML_TIME_RANGUVANNJA)
                {
                  //�����'������� ����������� �����
                  //���������� �� ���� ����������� ���� �������� �������� ����������
                  current_ekran.current_level = EKRAN_POINT_TIME_RANGUVANNJA;
                }
                current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
                current_ekran.edition = 0;
              }
              else if (current_ekran.current_level == EKRAN_LIST_INPUTS_OUTPUTS)
              {
                //������� ������ Enter � ���� ������ ������ �����-������
                if(current_ekran.index_position == INDEX_ML_STATE_INPUTS)
                {
                  //�����'������� ����������� �����
                  //���������� �� ���� ����������� ������ �����
                  current_ekran.current_level = EKRAN_STATE_INPUTS;
                }
                else
                {
                  //�����'������� ����������� �����
                  //���������� �� ���� ����������� ������ ������
                  current_ekran.current_level = EKRAN_STATE_OUTPUTS;
                }
                current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
                current_ekran.edition = 0;
              }
              else if (current_ekran.current_level == EKRAN_LIST_INPUTS_OUTPUTS)
              {
                //������� ������ Enter � ���� ������ ������ �����-������
                if(current_ekran.index_position == INDEX_ML_STATE_INPUTS)
                {
                  //�����'������� ����������� �����
                  //���������� �� ���� ����������� ������ �����
                  current_ekran.current_level = EKRAN_STATE_INPUTS;
                }
                else
                {
                  //�����'������� ����������� �����
                  //���������� �� ���� ����������� ������ ������
                  current_ekran.current_level = EKRAN_STATE_OUTPUTS;
                }
                current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
                current_ekran.edition = 0;
              }
              else if (current_ekran.current_level == EKRAN_LIST_REGISTRATORS)
              {
                //������� ������ Enter � ���� ������ ����������
                if(current_ekran.index_position == INDEX_ML_ANALOG_REGISTRATOR_INFO)
                {
                  //�����'������� ����������� �����
                  //���������� �� ���� ����������� ����������� ����������
                  current_ekran.current_level = EKRAN_LIST_ANALOG_REGISTRATOR_RECORDS;
                }
                else if(current_ekran.index_position == INDEX_ML_DIGITAL_REGISTRATOR_INFO)
                {
                  //�����'������� ����������� �����
                  //���������� �� ���� ����������� ����������� ����������
                  current_ekran.current_level = EKRAN_LIST_DIGITAL_REGISTRATOR_RECORDS;
                }
                else
                {
                  //�����'������� ����������� �����
                  //���������� �� ���� ����������� ���������� ���������� �������
                  current_ekran.current_level = EKRAN_LIST_REGISTRATOR_PROGRAM_ERROR_RECORDS;
                }
                current_ekran.index_position = 0; //��� ���������� ��� ���� � ������� ������ ���� ������ ����� �������� �� ��������� �����
                current_ekran.edition = 0;
              }
              else if (
                       (current_ekran.current_level == EKRAN_LIST_ANALOG_REGISTRATOR_RECORDS) &&
                       (info_rejestrator_ar.number_records > 0) &&
                       ((clean_rejestrators & CLEAN_AR) == 0)
                      )
              {
                //������� ������ Enter � ���� ������ ������ ����������� ���������� � ������� � ������ ��� �����������
                
                //�����'�������, ���� ����� ������ ����������� ���������� �� ���������� �����������
                number_record_of_ar_for_menu = current_ekran.index_position;
                
                //������ ������� ������� ���� � ����� ���'��
                control_tasks_dataflash |= TASK_MAMORY_READ_DATAFLASH_FOR_AR_MENU;
                
                //����������� �����������, �� ���� ���� �� ������ �������, �� ����� ����� �������������� ����� �������
                rewrite_ekran_once_more = 1;
                //����������� ����� �����, ���� ����� ���������� �� �ʲ
                current_ekran.current_level = EKRAN_DATA_LADEL_AR;
                current_ekran.index_position = 0; //��� ���������� ��� ���� � ������� ������ ���� ������ ����� �������� �� ��������� �����
                current_ekran.edition = 0;
              }
              else if (
                       (current_ekran.current_level == EKRAN_LIST_DIGITAL_REGISTRATOR_RECORDS) && 
                       (info_rejestrator_dr.number_records > 0) &&
                       ((clean_rejestrators & CLEAN_DR) == 0)
                      )
              {
                //������� ������ Enter � ���� ������ ������ ����������� ���������� � ������� � ������ ��� �����������
                
                //�����'�������, ���� ����� ������ ����������� ���������� �� ���������� �����������
                number_record_of_dr_for_menu = current_ekran.index_position;
                
                //����������� ����� ������� ������
                part_reading_dr_from_dataflash_for_menu = 0;
                //������ ������� ������� ���� � ����� ���'��
                control_tasks_dataflash |= TASK_MAMORY_READ_DATAFLASH_FOR_DR_MENU;
                
                //����������� �����������, �� ���� ���� �� ������ �������, �� ����� ����� �������������� ����� �������
                rewrite_ekran_once_more = 1;
                //����������� ����� �����, ���� ����� ���������� �� �ʲ
                current_ekran.current_level = EKRAN_TITLES_DIGITAL_REGISTRATOR;
                current_ekran.index_position = 0; //��� ���������� ��� ���� � ������� ������ ���� ������ ����� �������� �� ��������� �����
                current_ekran.edition = 0;
              }
              else if (current_ekran.current_level == EKRAN_TITLES_DIGITAL_REGISTRATOR)
              {
                //������� ������ Enter � ���� ������ ���� ���������� �� ������ ����������� ������
                if (rewrite_ekran_once_more == 0)
                {
                  if(current_ekran.index_position == INDEX_ML_TITLE_DR_DATA_AND_TIME)
                  {
                    //���������� �� ���� ����������� ���� ���� ������ ����������� ����������
                    current_ekran.current_level = EKRAN_DATA_LADEL_DR;
                  }
                  else if(current_ekran.index_position == INDEX_ML_TITLE_DR_CHANGES_SIGNALS)
                  {
                    //���������� �� ���� ����������� ������������ ��� ������� � ������ ����������� ����������
                    current_ekran.current_level = EKRAN_CHANGES_SIGNALS_DR;
                  }
                  current_ekran.index_position = 0;
                  current_ekran.edition = 0;
                }
              }
              else if (
                       (current_ekran.current_level == EKRAN_LIST_REGISTRATOR_PROGRAM_ERROR_RECORDS) &&
                       (info_rejestrator_pr_err.number_records > 0) &&
                       ((clean_rejestrators & CLEAN_PR_ERR) == 0)
                      )
              {
                //������� ������ Enter � ���� ������ ������ ���������� ���������� ���� � ������� � ������ ��� �����������
                
                //�����'�������, ���� ����� ������ ���������� ���������� ���� �� ���������� �����������
                number_record_of_pr_err_into_menu = current_ekran.index_position;
                
                //������ ������� ������� ���� � ����� ���'��
                control_tasks_dataflash |= TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_MENU;
                
                //����������� �����������, �� ���� ���� �� ������ �������, �� ����� ����� �������������� ����� �������
                rewrite_ekran_once_more = 1;
                //����������� ����� �����, ���� ����� ���������� �� �ʲ
                current_ekran.current_level = EKRAN_TITLES_PR_ERR_REGISTRATOR;
                current_ekran.index_position = 0; //��� ���������� ��� ���� � ������� ������ ���� ������ ����� �������� �� ��������� �����
                current_ekran.edition = 0;
              }
              else if (current_ekran.current_level == EKRAN_TITLES_PR_ERR_REGISTRATOR)
              {
                //������� ������ Enter � ���� ������ ���� ���������� �� ������ ����������� ������
                if (rewrite_ekran_once_more == 0)
                {
                  if(current_ekran.index_position == INDEX_ML_TITLE_PR_ERR_DATA_AND_TIME)
                  {
                    //���������� �� ���� ����������� ���� ���� ������ ���������� ���������� ����
                    current_ekran.current_level = EKRAN_DATA_LADEL_PR_ERR;
                  }
                  else if(current_ekran.index_position == INDEX_ML_TITLE_PR_ERR_CHANGES_DIAGNOSTICS)
                  {
                    //���������� �� ���� ����������� ������������ ��� ��������� � ������ ���������� ���������� ����
                    current_ekran.current_level = EKRAN_CHANGES_DIAGNOSTICS_PR_ERR;
                  }
                  current_ekran.index_position = 0;
                  current_ekran.edition = 0;
                }
              }
             
              //� ���, ���� ������� ����� �������, �� �����'������� ����� � ���� ����� ���� �����������
              if (temp_current_level != current_ekran.current_level) 
              {
                previous_level_in_current_level_menu[current_ekran.current_level] = temp_current_level;
              
                if(
                   ((current_ekran.current_level == EKRAN_LEVEL_SET_NEW_PASSWORD1) && (current_settings.password1 != 0)) ||
                    (current_ekran.current_level == EKRAN_LEVEL_SET_NEW_PASSWORD2)  
                  )   
                {
                  //� ��������, ���� �� ���������� ������� � ���� ���� ������, �� �������� ����� �������� ������ ������ �������, ���� �� ������������
                  if (current_ekran.current_level == EKRAN_LEVEL_SET_NEW_PASSWORD1) 
                  {
                    current_ekran.current_level = EKRAN_LEVEL_PASSWORD;
                    previous_level_in_current_level_menu[current_ekran.current_level] = EKRAN_LEVEL_SET_NEW_PASSWORD1;
                  }
                  else if (current_ekran.current_level == EKRAN_LEVEL_SET_NEW_PASSWORD2)
                  {
                    current_ekran.current_level = EKRAN_LEVEL_PASSWORD_HARD;
                    previous_level_in_current_level_menu[current_ekran.current_level] = EKRAN_LEVEL_SET_NEW_PASSWORD2;
                  }
                  else
                  {
                    //���������� ����� ������ �� ���� � ����
                    total_error_sw_fixed(71);
                  }
                  current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
                  current_ekran.cursor_on = 1;
                  current_ekran.cursor_blinking_on = 1;
                }
              }

              //�������� �����������, �� ��������� ������ 
              new_state_keyboard &= (unsigned int)(~(1<<BIT_KEY_ENTER));
              //����������� ������� �� ����������� ������ ������
              new_state_keyboard |= (1<<BIT_REWRITE);
            }
            else if (new_state_keyboard == (1<<BIT_KEY_ESC))
            {
              //���������� � ��������� ����
              current_ekran.current_level = previous_level_in_current_level_menu[current_ekran.current_level];
              current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
              current_ekran.edition = 0;

              //����������� ������� �� ����������� ������ ������
              new_state_keyboard |= (1<<BIT_REWRITE);
              //�������� �����������, �� ��������� ������ 
              new_state_keyboard &= (unsigned int)(~(1<<BIT_KEY_ESC));
            }
            else if (new_state_keyboard == (1<<BIT_KEY_UP))
            {
              //��������� ������ UP
              if(current_ekran.current_level == EKRAN_MEASURMENT)
              {
                if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_MEASURMENT - 1;
                position_in_current_level_menu[EKRAN_MEASURMENT] = current_ekran.index_position;
                //������� ����� ������ ��������� ����
                make_ekran_measurement();
              }
              else if(current_ekran.current_level == EKRAN_MEASURMENT_VOLTAGE_TYPE)
              {
                if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_MEASURMENT_VOLTAGE_TYPE - 1;
                position_in_current_level_menu[EKRAN_MEASURMENT_VOLTAGE_TYPE] = current_ekran.index_position;
                //������� ����� ������ ���� ������
                make_ekran_measurement_voltage_type();
              }
              else if(current_ekran.current_level == EKRAN_MEASURMENT_CURRENT)
              {
                if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_MEASURMENT_CURRENT - 1;
                position_in_current_level_menu[EKRAN_MEASURMENT_CURRENT] = current_ekran.index_position;
                //������� ����� ���������� ������ ����
                make_ekran_current(pervynna_vtorynna);
              }
              else if(current_ekran.current_level == EKRAN_MEASURMENT_VOLTAGE_PHASE)
              {
                if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_MEASURMENT_VOLTAGE_PHASE - 1;
                if(current_ekran.index_position < 0) 
                {
                  //����� �� ����� ������ ���� - �� ������ �������������
                  current_ekran.index_position = 0;
                }
                position_in_current_level_menu[EKRAN_MEASURMENT_VOLTAGE_PHASE] = current_ekran.index_position;
                //������� ����� ���������� ������ ����
                make_ekran_voltage_phase(pervynna_vtorynna);
              }
              else if(current_ekran.current_level == EKRAN_MEASURMENT_VOLTAGE_LINE)
              {
                if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_MEASURMENT_VOLTAGE_LINE - 1;
                if(current_ekran.index_position < 0) 
                {
                  //����� �� ����� ������ ���� - �� ������ �������������
                  current_ekran.index_position = 0;
                }
                position_in_current_level_menu[EKRAN_MEASURMENT_VOLTAGE_LINE] = current_ekran.index_position;
                //������� ����� ���������� ������ ����
                make_ekran_voltage_line(pervynna_vtorynna);
              }
              else if(current_ekran.current_level == EKRAN_MEASURMENT_FREQUENCY)
              {
                if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_MEASURMENT_FREQUENCY - 1;
                position_in_current_level_menu[EKRAN_MEASURMENT_FREQUENCY] = current_ekran.index_position;
                //������� ����� ���������� ������ ����
                make_ekran_frequency();
              }
              else if(current_ekran.current_level == EKRAN_MEASURMENT_ANGLE)
              {
                if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_MEASURMENT_ANGLE - 1;
                position_in_current_level_menu[EKRAN_MEASURMENT_ANGLE] = current_ekran.index_position;
                //������� ����� ���������� ����
                make_ekran_angle();
              }
              else if(current_ekran.current_level == EKRAN_MEASURMENT_POWER)
              {
                if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_MEASURMENT_POWER - 1;
                position_in_current_level_menu[EKRAN_MEASURMENT_POWER] = current_ekran.index_position;
                //������� ����� ����������� ���� �����������
                make_ekran_power(pervynna_vtorynna);
              }
              else if (
                       (current_ekran.current_level == EKRAN_CHOOSE_SETTINGS_APV       )||
                       (current_ekran.current_level == EKRAN_CHOOSE_SETTINGS_UROV      )|| 
                       (current_ekran.current_level == EKRAN_CHOOSE_SETTINGS_ZOP       )||
                       (current_ekran.current_level == EKRAN_CHOOSE_SETTINGS_UMIN      )||
                       (current_ekran.current_level == EKRAN_CHOOSE_SETTINGS_UMAX      )||
                       (current_ekran.current_level == EKRAN_CHOOSE_SETTINGS_AVR       )||
                       (current_ekran.current_level == EKRAN_CHOOSE_SETTINGS_CTRL_PHASE)
                      )   
              {
                if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_CHOSE_SETTINGS_PROTECTION_WITH_TWO_GROUP - 1;
                position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;
                //������� ����� �����1-...-�����N-��������� ��� ��� ������� �� ���������������� ����� �������
                make_ekran_chose_settings_protection_with_groups();
              }
              else if (
                       (
                        (current_ekran.current_level >= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP1_UROV) &&
                        (current_ekran.current_level <= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP4_UROV)
                       )
                       ||  
                       (
                        (current_ekran.current_level >= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP1_ZOP) &&
                        (current_ekran.current_level <= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP4_ZOP)
                       )
                       ||  
                       (
                        (current_ekran.current_level >= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP1_UMIN) &&
                        (current_ekran.current_level <= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP4_UMIN)
                       )
                       ||  
                       (
                        (current_ekran.current_level >= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP1_UMAX) &&
                        (current_ekran.current_level <= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP4_UMAX)
                       )
                       ||  
                       (
                        (current_ekran.current_level >= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP1_CTRL_PHASE) &&
                        (current_ekran.current_level <= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP4_CTRL_PHASE)
                       )
                      )
              {
                if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_CHOSE_SETPOINTS_TIMEOUTS - 1;
              
                position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;

                //������� ����� �������-�������� ��� ������� � ���� � �� ����� �������
                make_ekran_chose_setpoint_and_timeout();
              }
              else if (
                       (
                        (current_ekran.current_level >= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP1_AVR) &&
                        (current_ekran.current_level <= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP4_AVR)
                       )
                      )
              {
                if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_CHOSE_SETPOINTS_TIMEOUTS_AVR - 1;
              
                position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;

                //������� ����� ������� Umin-������� Umax-�������� ��� ��� � ��� � �� ����� �������
                make_ekran_chose_setpoint_and_timeout_avr();
              }
              else if (
                       (
                        (current_ekran.current_level >= EKRAN_CHOOSE_TIMEOUT_GROUP1_APV) &&
                        (current_ekran.current_level <= EKRAN_CHOOSE_TIMEOUT_GROUP4_APV)
                       )
                      )
              {
                if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_CHOSE_SETTINGS_PROTECTION_WITH_TIMEOUT - 1;
              
                position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;

                //������� ����� �������� ��� ������� � ���� � ������ ���� �������
                make_ekran_chose_timeout();
              }
              else if (current_ekran.current_level == EKRAN_CHOOSE_SETTINGS_ZDZ)
              {
                if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_CHOSE_SETTINGS_PROTECTION_WITH_CONTROL - 1;
                position_in_current_level_menu[EKRAN_CHOOSE_SETTINGS_ZDZ] = current_ekran.index_position;
                //������� ����� ��������� ��� ���
                make_ekran_chose_control();
              }
              else if (current_ekran.current_level == EKRAN_TRANSFORMATOR_INFO)
              {
                if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_CHOSE_SETTINGS_PROTECTION_WITH_SETPOINTS_CONTROL - 1;
              
                position_in_current_level_menu[EKRAN_TRANSFORMATOR_INFO] = current_ekran.index_position;

                //������� ����� �������-���������
                make_ekran_chose_setpoint_control();
              }
              else if (current_ekran.current_level == EKRAN_CHOOSE_SETTINGS_SWITCHER)
              {
                if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_CHOSE_SETTINGS_SWITCHER - 1;
              
                position_in_current_level_menu[EKRAN_CHOOSE_SETTINGS_SWITCHER] = current_ekran.index_position;

                //������� ����� �������-��������-���������-���������� ��������
                make_ekran_chose_settings_switcher();
              }
              else if (current_ekran.current_level == EKRAN_CHOOSE_RANG_SWITCH)
              {
                if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_RANG_SWITCH - 1;
              
                position_in_current_level_menu[EKRAN_CHOOSE_RANG_SWITCH] = current_ekran.index_position;

                //������� ����� �����./�����.
                make_ekran_choose_CBOn_CBOff();
              }
              else if (current_ekran.current_level == EKRAN_CHOSE_SETTINGS)
              {
                if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_CHOSE_SETTINGS - 1;
                while(
                      ((current_settings.configuration & (1 << EL_BIT_CONFIGURATION)) == 0)
                      &&
                      (current_ekran.index_position == INDEX_OF_EXTENDED_LOGIC)
                    )
                {
                  if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_CHOSE_SETTINGS - 1;
                }
                
                position_in_current_level_menu[EKRAN_CHOSE_SETTINGS] = current_ekran.index_position;
                //������� ����� ��������� ������������
                make_ekran_chose_settings();
              }
              else if (current_ekran.current_level == EKRAN_LEVEL_CHOOSE_PASSWORDS)
              {
                if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_CHOOSE_PASSWORDS - 1;
                position_in_current_level_menu[EKRAN_LEVEL_CHOOSE_PASSWORDS] = current_ekran.index_position;
                //������� ����� ��������� ������
                make_ekran_chose_passwords();
              }
              else if (current_ekran.current_level == EKRAN_LIST_INPUTS_FOR_RANGUVANNJA)
              {
                if(--current_ekran.index_position < 0) current_ekran.index_position =  MAX_ROW_LIST_INPUTS_FOR_RANGUVANNJA - 1;
                position_in_current_level_menu[EKRAN_LIST_INPUTS_FOR_RANGUVANNJA] = current_ekran.index_position;
                //������� ����� ��������� ���������� ����� ��� ����������
                make_ekran_chose_of_inputs_outputs_leds_df_buttons_for_ranguvannja(0);
              }
              else if (current_ekran.current_level == EKRAN_LIST_OUTPUTS_FOR_RANGUVANNJA)
              {
                if(--current_ekran.index_position < 0) current_ekran.index_position =  MAX_ROW_LIST_OUTPUTS_FOR_RANGUVANNJA - 1;
                position_in_current_level_menu[EKRAN_LIST_OUTPUTS_FOR_RANGUVANNJA] = current_ekran.index_position;
                //������� ����� ��������� ���������� ������ ��� ����������
                make_ekran_chose_of_inputs_outputs_leds_df_buttons_for_ranguvannja(1);
              }
              else if (current_ekran.current_level == EKRAN_LIST_LEDS_FOR_RANGUVANNJA)
              {
                if(--current_ekran.index_position < 0) current_ekran.index_position =  MAX_ROW_LIST_LEDS_FOR_RANGUVANNJA - 1;
                position_in_current_level_menu[EKRAN_LIST_LEDS_FOR_RANGUVANNJA] = current_ekran.index_position;
                //������� ����� ��������� ������������� ��� ����������
                make_ekran_chose_of_inputs_outputs_leds_df_buttons_for_ranguvannja(2);
              }
              else if (current_ekran.current_level == EKRAN_CHOOSE_SETTINGS_UVV)
              {
                if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_CHOSE_SETTINGS_UVV - 1;
                position_in_current_level_menu[EKRAN_CHOOSE_SETTINGS_UVV] = current_ekran.index_position;
                //������� ����� ������ ��������� ���
                make_ekran_chose_settings_uvv();
              }
              else if (current_ekran.current_level == EKRAN_CHOSE_COMMUNICATION_PARAMETERS)
              {
                if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_CHOSE_COMMUNICATION_PARAMETERS - 1;
                position_in_current_level_menu[EKRAN_CHOSE_COMMUNICATION_PARAMETERS] = current_ekran.index_position;
                //������� ����� ������ ��������� ��������� �����������
                make_ekran_chose_communication_parameters();
              }
              else if (current_ekran.current_level == EKRAN_VIEW_NAME_OF_CELL)
              {
                current_ekran.index_position -= MAX_ROW_LCD;
                if(current_ekran.index_position < 0) current_ekran.index_position = (MAX_ROW_FOR_VIEW_NAME_OF_CELL - 1) & (~(MAX_ROW_LCD - 1));
                position_in_current_level_menu[EKRAN_VIEW_NAME_OF_CELL] = current_ekran.index_position;
                //������� ����� ����������� ����� ������
                make_ekran_name_of_cell();
              }
              else if (current_ekran.current_level == EKRAN_CHOSE_SETTING_RS485)
              {
                if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_CHOSE_SETTING_RS485 - 1;
                position_in_current_level_menu[EKRAN_CHOSE_SETTING_RS485] = current_ekran.index_position;
               //������� ����� ����������� ������ ��������� ��� ���������� RS-485
               make_ekran_chose_setting_rs485();
              }
              else if (current_ekran.current_level == EKRAN_VIEW_LIST_OF_REGISTRATORS)
              {
                if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_LIST_OF_REGISTRATORS - 1;
                position_in_current_level_menu[EKRAN_VIEW_LIST_OF_REGISTRATORS] = current_ekran.index_position;
                //������� ����� ������ ����������
                make_ekran_chose_registrators();
              }
              else if (current_ekran.current_level == EKRAN_VIEW_SETTINGS_OF_ANALOG_REGISTRATORS)
              {
                if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_SETTINGS_OF_ANALOG_REGISTRATOR - 1;
                position_in_current_level_menu[EKRAN_VIEW_SETTINGS_OF_ANALOG_REGISTRATORS] = current_ekran.index_position;
                //������� ����� ������ ��������� ����������� ����������
                make_ekran_settings_analog_registrators();
              }
              else if (current_ekran.current_level == EKRAN_EXTENDED_LIGIC)
              {
                current_ekran.index_position--;
                do
                {
                  if(current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_EXTENDED_LIGIC - 1;

//                  if ((current_ekran.index_position == INDEX_OF_DEFINED_NOT) && (current_settings.number_defined_not  == 0))
//                    current_ekran.index_position--;
//                  if ((current_ekran.index_position == INDEX_OF_DEFINED_XOR) && (current_settings.number_defined_xor  == 0))
//                    current_ekran.index_position--;
//                  if ((current_ekran.index_position == INDEX_OF_DEFINED_OR) && (current_settings.number_defined_or  == 0))
//                    current_ekran.index_position--;
//                  if ((current_ekran.index_position == INDEX_OF_DEFINED_AND) && (current_settings.number_defined_and  == 0))
//                    current_ekran.index_position--;
//                  if ((current_ekran.index_position == INDEX_OF_DEFINED_TRIGGERS) && (current_settings.number_defined_dt  == 0))
//                    current_ekran.index_position--;
//                  if ((current_ekran.index_position == INDEX_OF_DEFINED_FUNCTIONS) && (current_settings.number_defined_df  == 0))
//                    current_ekran.index_position--;
                }
                while (current_ekran.index_position < 0);
                
                position_in_current_level_menu[EKRAN_EXTENDED_LIGIC] = current_ekran.index_position;
                //������� ����� ������ ����������� ��������� �����
                make_ekran_extended_logic();
              }
              else if (current_ekran.current_level == EKRAN_LIST_SETTINGS_FOR_DF)
              {
                if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_SETTINGS_DF - 1;
                position_in_current_level_menu[EKRAN_LIST_SETTINGS_FOR_DF] = current_ekran.index_position;
                //������� ����� ����������� ������ ��������� ��� �������������� �������
                make_ekran_chose_settings_df();
              }
              else if ((current_ekran.current_level == EKRAN_LIST_DF_FOR_RANGUVANNJA) || (current_ekran.current_level == EKRAN_LIST_DF_FOR_TIMEOUT_SETTINGS))
              {
                if(--current_ekran.index_position < 0) current_ekran.index_position =  MAX_ROW_FOR_LIST_DF - 1;
                position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;
                //������� ����� ��������� �������������� �������
                make_ekran_chose_of_inputs_outputs_leds_df_buttons_for_ranguvannja(3);
              }
              else if ((current_ekran.current_level >= EKRAN_LIST_TYPE_SOURCE_DF1) && (current_ekran.current_level <= EKRAN_LIST_TYPE_SOURCE_DF8))
              {
                if(--current_ekran.index_position < 0) current_ekran.index_position =  MAX_ROW_LIST_TYPE_SOURCE_DF - 1;
                position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;
                //������� ����� ��������� ���� ������ �������������� �������
                make_ekran_list_type_source_df();
              }
              else if (current_ekran.current_level == EKRAN_LIST_DT)
              {
                if(--current_ekran.index_position < 0) current_ekran.index_position =  MAX_ROW_FOR_LIST_DT - 1;
                position_in_current_level_menu[EKRAN_LIST_DT] = current_ekran.index_position;
                //������� ����� ��������� �������������� ������
                make_ekran_chose_of_inputs_outputs_leds_df_buttons_for_ranguvannja(5);
              }
              else if ((current_ekran.current_level >= EKRAN_SET_RESET_DT1) && (current_ekran.current_level <= EKRAN_SET_RESET_DT4))
              {
                if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_LIST_SET_RESET_DT - 1;
                position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;
                //������� ����� ��������� ���������-����������� �������������� ������
                make_ekran_set_reset_trigger();
              }
              else if ((current_ekran.current_level >= EKRAN_SET_DT1) && (current_ekran.current_level <= EKRAN_RESET_DT4))
              {
                if(--current_ekran.index_position < 0) current_ekran.index_position =  MAX_ROW_LIST_TYPE_SOURCE_DT - 1;
                position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;
                //������� ����� ��������� ���� ������ �������������� ������
                make_ekran_list_type_source_dt();
              }
              else if (current_ekran.current_level == EKRAN_LIST_D_AND)
              {
                if(--current_ekran.index_position < 0) current_ekran.index_position =  MAX_ROW_FOR_LIST_D_AND - 1;
                position_in_current_level_menu[EKRAN_LIST_D_AND] = current_ekran.index_position;
                //������� ����� ��������� ������������ "�"
                make_ekran_chose_of_inputs_outputs_leds_df_buttons_for_ranguvannja(6);
              }
              else if (current_ekran.current_level == EKRAN_LIST_D_OR)
              {
                if(--current_ekran.index_position < 0) current_ekran.index_position =  MAX_ROW_FOR_LIST_D_OR - 1;
                position_in_current_level_menu[EKRAN_LIST_D_OR] = current_ekran.index_position;
                //������� ����� ��������� ������������ "���"
                make_ekran_chose_of_inputs_outputs_leds_df_buttons_for_ranguvannja(7);
              }
              else if (current_ekran.current_level == EKRAN_LIST_D_XOR)
              {
                if(--current_ekran.index_position < 0) current_ekran.index_position =  MAX_ROW_FOR_LIST_D_XOR - 1;
                position_in_current_level_menu[EKRAN_LIST_D_XOR] = current_ekran.index_position;
                //������� ����� ��������� ������������ "����.���"
                make_ekran_chose_of_inputs_outputs_leds_df_buttons_for_ranguvannja(8);
              }
              else if (current_ekran.current_level == EKRAN_LIST_D_NOT)
              {
                if(--current_ekran.index_position < 0) current_ekran.index_position =  MAX_ROW_FOR_LIST_D_NOT - 1;
                position_in_current_level_menu[EKRAN_LIST_D_NOT] = current_ekran.index_position;
                //������� ����� ��������� ������������ "��"
                make_ekran_chose_of_inputs_outputs_leds_df_buttons_for_ranguvannja(9);
              }
              else if (current_ekran.current_level == EKRAN_LIST_BUTTONS_FOR_RANGUVANNJA)
              {
                if(--current_ekran.index_position < 0) current_ekran.index_position =  MAX_ROW_LIST_BUTTONS_FOR_RANGUVANNJA - 1;
                position_in_current_level_menu[EKRAN_LIST_BUTTONS_FOR_RANGUVANNJA] = current_ekran.index_position;
                //������� ����� ��������� �������������� ������ ��� ����������
                make_ekran_chose_of_inputs_outputs_leds_df_buttons_for_ranguvannja(4);
              }
              else if(current_ekran.current_level == EKRAN_INFO)
              {
                if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_INFO - 1;
                position_in_current_level_menu[EKRAN_INFO] = current_ekran.index_position;
                //������� ����� ����������
                make_ekran_info();
              }
              else if(current_ekran.current_level == EKRAN_DATE_TIME_PZ)
              {
                if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_DATE_TIME_PZ - 1;
                position_in_current_level_menu[EKRAN_DATE_TIME_PZ] = current_ekran.index_position;
                //������� ����� ����������� ��� ���� � ���� ��������
                make_ekran_date_time_pz();
              }
              else if(current_ekran.current_level == EKRAN_POINT_TIME_SETTINGS)
              {
                if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_POINT_TIME_SETTINGS - 1;
                position_in_current_level_menu[EKRAN_POINT_TIME_SETTINGS] = current_ekran.index_position;
                //������� ����� ������ ���� ������������
                make_ekran_chose_item_of_point_time_settings();
              }
              else if(current_ekran.current_level == EKRAN_POINT_TIME_SETPOINT)
              {
                if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_POINT_TIME_SETPOINT_RANGUVANNJA - 1;
                position_in_current_level_menu[EKRAN_POINT_TIME_SETPOINT] = current_ekran.index_position;
                //������� ����� ����������� ��� �������� ��� � ��������-���������-����������� ����������
                make_ekran_time_settings(0);
              }
              else if(current_ekran.current_level == EKRAN_POINT_TIME_RANGUVANNJA)
              {
                if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_POINT_TIME_SETPOINT_RANGUVANNJA - 1;
                position_in_current_level_menu[EKRAN_POINT_TIME_RANGUVANNJA] = current_ekran.index_position;
                //������� ����� ����������� ��� �������� ��� � ����������
                make_ekran_time_settings(1);
              }
              else if(current_ekran.current_level == EKRAN_DIAGNOSTYKA)
              {
                if (
                    (diagnostyka[0] == 0) &&
                    (diagnostyka[1] == 0) &&
                    ((diagnostyka[2] & USED_BITS_IN_LAST_INDEX) == 0)
                   )
                {
                  current_ekran.index_position = 0;
                }
                else
                {
                  if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_DIAGNOSTYKA - 1;
                  while (_CHECK_SET_BIT(diagnostyka, current_ekran.index_position) ==0)
                  {
                    current_ekran.index_position--;
                    if(current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_DIAGNOSTYKA - 1;
                  }
                }
                position_in_current_level_menu[EKRAN_DIAGNOSTYKA] = current_ekran.index_position;
                //������� ����� ����������
                make_ekran_diagnostyka(diagnostyka);
              }
              else if(current_ekran.current_level == EKRAN_LIST_INPUTS_OUTPUTS)
              {
                if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_LIST_INPUTS_OUTPUTS - 1;
                position_in_current_level_menu[EKRAN_LIST_INPUTS_OUTPUTS] = current_ekran.index_position;
                //������� ����� ������ ������ �����-������
                make_ekran_list_inputs_outputs();
              }
              else if ((current_ekran.current_level == EKRAN_STATE_INPUTS) || (current_ekran.current_level == EKRAN_STATE_OUTPUTS))
              {
                if (current_ekran.current_level == EKRAN_STATE_INPUTS)
                {
                  if(--current_ekran.index_position < 0) current_ekran.index_position = NUMBER_INPUTS - 1;
                }
                else
                {
                  if(--current_ekran.index_position < 0) current_ekran.index_position = NUMBER_OUTPUTS - 1;
                }
              
                position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;
                //������� ����� ������ ����� ��� ������� 
                make_ekran_state_inputs_or_outputs(current_ekran.current_level - EKRAN_STATE_INPUTS);
              }
              else if(current_ekran.current_level == EKRAN_LIST_REGISTRATORS)
              {
                if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_LIST_REGISTRATORS - 1;
                position_in_current_level_menu[EKRAN_LIST_REGISTRATORS] = current_ekran.index_position;
                //������� ����� ������ ����������
                make_ekran_list_registrators();
              }
              else if (
                       (current_ekran.current_level == EKRAN_LIST_ANALOG_REGISTRATOR_RECORDS ) ||
                       (current_ekran.current_level == EKRAN_LIST_DIGITAL_REGISTRATOR_RECORDS) ||
                       (current_ekran.current_level == EKRAN_LIST_REGISTRATOR_PROGRAM_ERROR_RECORDS)
                      )
              {
                unsigned int number_records;
                unsigned int type_registrator;
  
                if (current_ekran.current_level == EKRAN_LIST_ANALOG_REGISTRATOR_RECORDS)
                {
                  number_records = info_rejestrator_ar.number_records;
                  type_registrator = INDEX_ML_ANALOG_REGISTRATOR_INFO;
                }
                else if (current_ekran.current_level == EKRAN_LIST_DIGITAL_REGISTRATOR_RECORDS)
                {
                  number_records = info_rejestrator_dr.number_records;
                  type_registrator = INDEX_ML_DIGITAL_REGISTRATOR_INFO;
                }
                else
                {
                  number_records = info_rejestrator_pr_err.number_records;
                  type_registrator = INDEX_ML_PROGRAM_ERROE_REGISTRATOR_INFO;
                }
                
                --current_ekran.index_position;
                if((current_ekran.index_position < 0) || (current_ekran.index_position >= ((int)number_records))) 
                {
                  if (number_records == 0) current_ekran.index_position = 0;
                  else current_ekran.index_position = number_records - 1;
                }
                position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;

                //������� ����� ����������� ������
                make_ekran_list_records_registrator(type_registrator);
              }
              else if (current_ekran.current_level == EKRAN_TITLES_DIGITAL_REGISTRATOR)
              {
                if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_TITLES_DIGITAL_REGISTRATOR - 1;
                position_in_current_level_menu[EKRAN_TITLES_DIGITAL_REGISTRATOR] = current_ekran.index_position;
                //������� ����� ����������� ��������� ���� ��� ����������� ����������
                make_ekran_list_titles_for_record_of_digital_registrator();
              }
              else if (current_ekran.current_level == EKRAN_DATA_LADEL_DR)
              {
                if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_EKRAN_DATA_LABEL - 1;
                position_in_current_level_menu[EKRAN_DATA_LADEL_DR] = current_ekran.index_position;
                //������� ����� ����������� ���� ���� ����������� ������ ����������� ����������
                make_ekran_data_and_time_of_records_registrator(0);
              }
              else if (current_ekran.current_level == EKRAN_CHANGES_SIGNALS_DR)
              {
                current_ekran.index_position--;
                //������� ����� ����������� ��� ������� - ��������� � ����������� ���������
                make_ekran_changing_signals_digital_registrator();
              }
              else if (current_ekran.current_level == EKRAN_TITLES_PR_ERR_REGISTRATOR)
              {
                if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_TITLES_PR_ERR_REGISTRATOR - 1;
                position_in_current_level_menu[EKRAN_TITLES_PR_ERR_REGISTRATOR] = current_ekran.index_position;
                //������� ����� ����������� ��������� ���� ��� ����������� ����������
                make_ekran_list_titles_for_record_of_pr_err_registrator();
              }
              else if (current_ekran.current_level == EKRAN_DATA_LADEL_PR_ERR)
              {
                if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_EKRAN_DATA_LABEL - 1;
                position_in_current_level_menu[EKRAN_DATA_LADEL_PR_ERR] = current_ekran.index_position;
                //������� ����� ����������� ���� ���� ����������� ������ ���������� ���������� ����
                make_ekran_data_and_time_of_records_registrator(1);
              }
              else if (current_ekran.current_level == EKRAN_CHANGES_DIAGNOSTICS_PR_ERR)
              {
                current_ekran.index_position--;
                //������� ����� ����������� ��� ��������� - ��������� � ��������� ���������� ����
                make_ekran_changing_diagnostics_pr_err_registrator();
              }
              else if (current_ekran.current_level == EKRAN_DATA_LADEL_AR)
              {
                if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_EKRAN_DATA_LABEL - 1;
                position_in_current_level_menu[EKRAN_DATA_LADEL_AR] = current_ekran.index_position;
                //������� ����� ����������� ���� ���� ����������� ������ ����������� ����������
                make_ekran_data_and_time_of_records_registrator(2);
              }
              
              //�������� �����������, �� ��������� ������ 
              new_state_keyboard &= (unsigned int)(~(1<<BIT_KEY_UP));
            }
            else if (new_state_keyboard == (1<<BIT_KEY_DOWN))
            {
              //��������� ������ DOWN
              if(current_ekran.current_level == EKRAN_MEASURMENT)
              {
                if(++current_ekran.index_position >= MAX_ROW_FOR_MEASURMENT) current_ekran.index_position = 0;
                position_in_current_level_menu[EKRAN_MEASURMENT] = current_ekran.index_position;
                //������� ����� ������ ��������� ����
                make_ekran_measurement();
              }
              else if(current_ekran.current_level == EKRAN_MEASURMENT_VOLTAGE_TYPE)
              {
                if(++current_ekran.index_position >= MAX_ROW_FOR_MEASURMENT_VOLTAGE_TYPE) current_ekran.index_position = 0;
                position_in_current_level_menu[EKRAN_MEASURMENT_VOLTAGE_TYPE] = current_ekran.index_position;
                //������� ����� ������ ���� ������
                make_ekran_measurement_voltage_type();
              }
              else if(current_ekran.current_level == EKRAN_MEASURMENT_CURRENT)
              {
                if(++current_ekran.index_position >= MAX_ROW_FOR_MEASURMENT_CURRENT) current_ekran.index_position = 0;
                position_in_current_level_menu[EKRAN_MEASURMENT_CURRENT] = current_ekran.index_position;
                //������� ����� ���������� ������ ����
                make_ekran_current(pervynna_vtorynna);
              }
              else if(current_ekran.current_level == EKRAN_MEASURMENT_VOLTAGE_PHASE)
              {
                if(++current_ekran.index_position >= MAX_ROW_FOR_MEASURMENT_VOLTAGE_PHASE) current_ekran.index_position = 0;
                position_in_current_level_menu[EKRAN_MEASURMENT_VOLTAGE_PHASE] = current_ekran.index_position;
                //������� ����� ���������� ������ ����
                make_ekran_voltage_phase(pervynna_vtorynna);
              }
              else if(current_ekran.current_level == EKRAN_MEASURMENT_VOLTAGE_LINE)
              {
                if(++current_ekran.index_position >= MAX_ROW_FOR_MEASURMENT_VOLTAGE_LINE) current_ekran.index_position = 0;
                position_in_current_level_menu[EKRAN_MEASURMENT_VOLTAGE_LINE] = current_ekran.index_position;
                //������� ����� ���������� ������ ����
                make_ekran_voltage_line(pervynna_vtorynna);
              }
              else if(current_ekran.current_level == EKRAN_MEASURMENT_FREQUENCY)
              {
                if(++current_ekran.index_position >= MAX_ROW_FOR_MEASURMENT_FREQUENCY) current_ekran.index_position = 0;
                position_in_current_level_menu[EKRAN_MEASURMENT_FREQUENCY] = current_ekran.index_position;
                //������� ����� ���������� ������ ����
                make_ekran_frequency();
              }
              else if(current_ekran.current_level == EKRAN_MEASURMENT_ANGLE)
              {
                if(++current_ekran.index_position >= MAX_ROW_FOR_MEASURMENT_ANGLE) current_ekran.index_position = 0;
                position_in_current_level_menu[EKRAN_MEASURMENT_ANGLE] = current_ekran.index_position;
                //������� ����� ���������� ����
                make_ekran_angle();
              }
              else if(current_ekran.current_level == EKRAN_MEASURMENT_POWER)
              {
                if(++current_ekran.index_position >= MAX_ROW_FOR_MEASURMENT_POWER) current_ekran.index_position = 0;
                position_in_current_level_menu[EKRAN_MEASURMENT_POWER] = current_ekran.index_position;
                //������� ����� ����������� ���� �����������
                make_ekran_power(pervynna_vtorynna);
              }
              else if (
                       (current_ekran.current_level == EKRAN_CHOOSE_SETTINGS_APV       )||
                       (current_ekran.current_level == EKRAN_CHOOSE_SETTINGS_UROV      )||
                       (current_ekran.current_level == EKRAN_CHOOSE_SETTINGS_ZOP       )||
                       (current_ekran.current_level == EKRAN_CHOOSE_SETTINGS_UMIN      )||
                       (current_ekran.current_level == EKRAN_CHOOSE_SETTINGS_UMAX      )||
                       (current_ekran.current_level == EKRAN_CHOOSE_SETTINGS_AVR       )||
                       (current_ekran.current_level == EKRAN_CHOOSE_SETTINGS_CTRL_PHASE)
                      )   
              {
                if(++current_ekran.index_position >= MAX_ROW_FOR_CHOSE_SETTINGS_PROTECTION_WITH_TWO_GROUP) current_ekran.index_position = 0;
                position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;

                //������� ����� �����1-...-�����N-��������� ��� ��� ������� �� ���������������� ����� �������
                make_ekran_chose_settings_protection_with_groups();
              }
              else if (
                       (
                        (current_ekran.current_level >= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP1_UROV) &&
                        (current_ekran.current_level <= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP4_UROV)
                       )
                       ||  
                       (
                        (current_ekran.current_level >= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP1_ZOP) &&
                        (current_ekran.current_level <= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP4_ZOP)
                       )
                       ||  
                       (
                        (current_ekran.current_level >= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP1_UMIN) &&
                        (current_ekran.current_level <= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP4_UMIN)
                       )
                       ||  
                       (
                        (current_ekran.current_level >= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP1_UMAX) &&
                        (current_ekran.current_level <= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP4_UMAX)
                       )
                       ||  
                       (
                        (current_ekran.current_level >= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP1_CTRL_PHASE) &&
                        (current_ekran.current_level <= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP4_CTRL_PHASE)
                       )
                      )
              {
                if(++current_ekran.index_position >= MAX_ROW_FOR_CHOSE_SETPOINTS_TIMEOUTS) current_ekran.index_position = 0;
              
                position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;

                //������� ����� �������-�������� ��� ������� � ���� � �� ����� �������
                make_ekran_chose_setpoint_and_timeout();
              }
              else if (
                       (
                        (current_ekran.current_level >= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP1_AVR) &&
                        (current_ekran.current_level <= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP4_AVR)
                       )
                      )
              {
                if(++current_ekran.index_position >= MAX_ROW_FOR_CHOSE_SETPOINTS_TIMEOUTS_AVR) current_ekran.index_position = 0;
              
                position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;

                //������� ����� ������� Umin-������� Umax-�������� ��� ��� � ��� � �� ����� �������
                make_ekran_chose_setpoint_and_timeout_avr();
              }
              else if (
                       (
                        (current_ekran.current_level >= EKRAN_CHOOSE_TIMEOUT_GROUP1_APV) &&
                        (current_ekran.current_level <= EKRAN_CHOOSE_TIMEOUT_GROUP4_APV)
                       )
                      )
              {
                if(++current_ekran.index_position >= MAX_ROW_FOR_CHOSE_SETTINGS_PROTECTION_WITH_TIMEOUT) current_ekran.index_position = 0;
              
                position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;

                //������� ����� �������� ��� ������� � ���� � ������ ���� �������
                make_ekran_chose_timeout();
              }
              else if (current_ekran.current_level == EKRAN_CHOOSE_SETTINGS_ZDZ)
              {
                if(++current_ekran.index_position >= MAX_ROW_FOR_CHOSE_SETTINGS_PROTECTION_WITH_CONTROL) current_ekran.index_position = 0;
                position_in_current_level_menu[EKRAN_CHOOSE_SETTINGS_ZDZ] = current_ekran.index_position;
                //������� ����� ��������� ��� ���
                make_ekran_chose_control();
              }
              else if (current_ekran.current_level == EKRAN_TRANSFORMATOR_INFO)
              {
                if(++current_ekran.index_position >= MAX_ROW_FOR_CHOSE_SETTINGS_PROTECTION_WITH_SETPOINTS_CONTROL) current_ekran.index_position = 0;
              
                position_in_current_level_menu[EKRAN_TRANSFORMATOR_INFO] = current_ekran.index_position;

                //������� ����� �������-���������
                make_ekran_chose_setpoint_control();
              }
              else if (current_ekran.current_level == EKRAN_CHOOSE_SETTINGS_SWITCHER)
              {
                if(++current_ekran.index_position >= MAX_ROW_FOR_CHOSE_SETTINGS_SWITCHER) current_ekran.index_position = 0;
              
                position_in_current_level_menu[EKRAN_CHOOSE_SETTINGS_SWITCHER] = current_ekran.index_position;

                //������� ����� �������-��������-���������-���������� ��������
                make_ekran_chose_settings_switcher();
              }
              else if (current_ekran.current_level == EKRAN_CHOOSE_RANG_SWITCH)
              {
                if(++current_ekran.index_position >= MAX_ROW_FOR_RANG_SWITCH) current_ekran.index_position = 0;
              
                position_in_current_level_menu[EKRAN_CHOOSE_RANG_SWITCH] = current_ekran.index_position;

                //������� ����� �����./�����.
                make_ekran_choose_CBOn_CBOff();
              }
              else if (current_ekran.current_level == EKRAN_CHOSE_SETTINGS)
              {
                //��������� ������ DOWN
                if(++current_ekran.index_position >= MAX_ROW_FOR_CHOSE_SETTINGS) current_ekran.index_position = 0;
                while(
                      ((current_settings.configuration & (1 << EL_BIT_CONFIGURATION)) == 0)
                      &&
                      (current_ekran.index_position == INDEX_OF_EXTENDED_LOGIC)
                    )
                {
                  if(++current_ekran.index_position >= MAX_ROW_FOR_CHOSE_SETTINGS) current_ekran.index_position = 0;
                }
                
                position_in_current_level_menu[EKRAN_CHOSE_SETTINGS] = current_ekran.index_position;
            
                //������� ����� ��������� ������������
                make_ekran_chose_settings();
              }
              else if (current_ekran.current_level == EKRAN_LEVEL_CHOOSE_PASSWORDS)
              {
                //��������� ������ DOWN
                if(++current_ekran.index_position >= MAX_ROW_FOR_CHOOSE_PASSWORDS) current_ekran.index_position = 0;
                position_in_current_level_menu[EKRAN_LEVEL_CHOOSE_PASSWORDS] = current_ekran.index_position;
            
                //������� ����� ��������� ������
                make_ekran_chose_passwords();
              }
              else if (current_ekran.current_level == EKRAN_LIST_INPUTS_FOR_RANGUVANNJA)
              {
                //��������� ������ DOWN
                if(++current_ekran.index_position >= MAX_ROW_LIST_INPUTS_FOR_RANGUVANNJA) current_ekran.index_position = 0;
                position_in_current_level_menu[EKRAN_LIST_INPUTS_FOR_RANGUVANNJA] = current_ekran.index_position;
                //������� ����� ��������� ���������� ����� ��� ����������
                make_ekran_chose_of_inputs_outputs_leds_df_buttons_for_ranguvannja(0);
              }
              else if (current_ekran.current_level == EKRAN_LIST_OUTPUTS_FOR_RANGUVANNJA)
              {
                //��������� ������ DOWN
                if(++current_ekran.index_position >= MAX_ROW_LIST_OUTPUTS_FOR_RANGUVANNJA) current_ekran.index_position = 0;
                position_in_current_level_menu[EKRAN_LIST_OUTPUTS_FOR_RANGUVANNJA] = current_ekran.index_position;
                //������� ����� ��������� ���������� ������ ��� ����������
                make_ekran_chose_of_inputs_outputs_leds_df_buttons_for_ranguvannja(1);
              }
              else if (current_ekran.current_level == EKRAN_LIST_LEDS_FOR_RANGUVANNJA)
              {
                //��������� ������ DOWN
                if(++current_ekran.index_position >= MAX_ROW_LIST_LEDS_FOR_RANGUVANNJA) current_ekran.index_position = 0;
                position_in_current_level_menu[EKRAN_LIST_LEDS_FOR_RANGUVANNJA] = current_ekran.index_position;
                //������� ����� ��������� ������������� ��� ����������
                make_ekran_chose_of_inputs_outputs_leds_df_buttons_for_ranguvannja(2);
              }
              else if (current_ekran.current_level == EKRAN_CHOOSE_SETTINGS_UVV)
              {
                if(++current_ekran.index_position >= MAX_ROW_FOR_CHOSE_SETTINGS_UVV) current_ekran.index_position = 0;
                position_in_current_level_menu[EKRAN_CHOOSE_SETTINGS_UVV] = current_ekran.index_position;
                //������� ����� ������ ��������� ���
                make_ekran_chose_settings_uvv();
              }
              else if (current_ekran.current_level == EKRAN_CHOSE_COMMUNICATION_PARAMETERS)
              {
                if(++current_ekran.index_position >= MAX_ROW_FOR_CHOSE_COMMUNICATION_PARAMETERS) current_ekran.index_position = 0;
                position_in_current_level_menu[EKRAN_CHOSE_COMMUNICATION_PARAMETERS] = current_ekran.index_position;
                //������� ����� ������ ��������� ��������� �����������
                make_ekran_chose_communication_parameters();
              }
              else if (current_ekran.current_level == EKRAN_VIEW_NAME_OF_CELL)
              {
                current_ekran.index_position += MAX_ROW_LCD;
                if(current_ekran.index_position >= MAX_ROW_FOR_VIEW_NAME_OF_CELL) current_ekran.index_position = 0;
                position_in_current_level_menu[EKRAN_VIEW_NAME_OF_CELL] = current_ekran.index_position;
                //������� ����� ����������� ����� ������
                make_ekran_name_of_cell();
              }
              else if (current_ekran.current_level == EKRAN_CHOSE_SETTING_RS485)
              {
                if(++current_ekran.index_position >= MAX_ROW_FOR_CHOSE_SETTING_RS485) current_ekran.index_position = 0;
                position_in_current_level_menu[EKRAN_CHOSE_SETTING_RS485] = current_ekran.index_position;
               //������� ����� ����������� ������ ��������� ��� ���������� RS-485
                make_ekran_chose_setting_rs485();
              }
              else if (current_ekran.current_level == EKRAN_VIEW_LIST_OF_REGISTRATORS)
              {
                if(++current_ekran.index_position >= MAX_ROW_FOR_LIST_OF_REGISTRATORS) current_ekran.index_position = 0;
                position_in_current_level_menu[EKRAN_VIEW_LIST_OF_REGISTRATORS] = current_ekran.index_position;
                //������� ����� ������ ����������
                make_ekran_chose_registrators();
              }
              else if (current_ekran.current_level == EKRAN_VIEW_SETTINGS_OF_ANALOG_REGISTRATORS)
              {
                if(++current_ekran.index_position >= MAX_ROW_FOR_SETTINGS_OF_ANALOG_REGISTRATOR) current_ekran.index_position = 0;
                position_in_current_level_menu[EKRAN_VIEW_SETTINGS_OF_ANALOG_REGISTRATORS] = current_ekran.index_position;
                //������� ����� ������ ��������� ����������� ����������
                make_ekran_settings_analog_registrators();
              }
              else if (current_ekran.current_level == EKRAN_EXTENDED_LIGIC)
              {
                current_ekran.index_position++;
                do
                {
                  if(current_ekran.index_position >= MAX_ROW_FOR_EXTENDED_LIGIC) current_ekran.index_position = 0;
                
//                  if ((current_ekran.index_position == INDEX_OF_DEFINED_FUNCTIONS) && (current_settings.number_defined_df == 0))
//                    current_ekran.index_position++;
//                  if ((current_ekran.index_position == INDEX_OF_DEFINED_TRIGGERS) && (current_settings.number_defined_dt == 0))
//                    current_ekran.index_position++;
//                  if ((current_ekran.index_position == INDEX_OF_DEFINED_AND) && (current_settings.number_defined_and == 0))
//                    current_ekran.index_position++;
//                  if ((current_ekran.index_position == INDEX_OF_DEFINED_OR) && (current_settings.number_defined_or == 0))
//                    current_ekran.index_position++;
//                  if ((current_ekran.index_position == INDEX_OF_DEFINED_XOR) && (current_settings.number_defined_xor == 0))
//                    current_ekran.index_position++;
//                  if ((current_ekran.index_position == INDEX_OF_DEFINED_NOT) && (current_settings.number_defined_not == 0))
//                    current_ekran.index_position++;
                }
                while (current_ekran.index_position >= MAX_ROW_FOR_EXTENDED_LIGIC);
              
                position_in_current_level_menu[EKRAN_EXTENDED_LIGIC] = current_ekran.index_position;
                //������� ����� ������ ����������� ��������� �����
                make_ekran_extended_logic();
              }
              else if (current_ekran.current_level == EKRAN_LIST_SETTINGS_FOR_DF)
              {
                if(++current_ekran.index_position >= MAX_ROW_SETTINGS_DF) current_ekran.index_position = 0;
                position_in_current_level_menu[EKRAN_LIST_SETTINGS_FOR_DF] = current_ekran.index_position;
                //������� ����� ����������� ������ ��������� ��� �������������� �������
                make_ekran_chose_settings_df();
              }
              else if ((current_ekran.current_level == EKRAN_LIST_DF_FOR_RANGUVANNJA) || (current_ekran.current_level == EKRAN_LIST_DF_FOR_TIMEOUT_SETTINGS))
              {
                //��������� ������ DOWN
                if(++current_ekran.index_position >= MAX_ROW_FOR_LIST_DF) current_ekran.index_position = 0;
                position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;
                //������� ����� ��������� �������������� �������
                make_ekran_chose_of_inputs_outputs_leds_df_buttons_for_ranguvannja(3);
              }
              else if ((current_ekran.current_level >= EKRAN_LIST_TYPE_SOURCE_DF1) && (current_ekran.current_level <= EKRAN_LIST_TYPE_SOURCE_DF8))
              {
                //��������� ������ DOWN
                if(++current_ekran.index_position >= MAX_ROW_LIST_TYPE_SOURCE_DF) current_ekran.index_position = 0;
                position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;
                //������� ����� ��������� ���� ������ �������������� �������
                make_ekran_list_type_source_df();
              }
              else if (current_ekran.current_level == EKRAN_LIST_DT)
              {
                if(++current_ekran.index_position >= MAX_ROW_FOR_LIST_DT) current_ekran.index_position = 0;
                position_in_current_level_menu[EKRAN_LIST_DT] = current_ekran.index_position;
                //������� ����� ��������� �������������� ������
                make_ekran_chose_of_inputs_outputs_leds_df_buttons_for_ranguvannja(5);
              }
              else if ((current_ekran.current_level >= EKRAN_SET_RESET_DT1) && (current_ekran.current_level <= EKRAN_SET_RESET_DT4))
              {
                if(++current_ekran.index_position >= MAX_ROW_FOR_LIST_SET_RESET_DT) current_ekran.index_position = 0;
                position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;
                //������� ����� ��������� ���������-����������� �������������� ������
                make_ekran_set_reset_trigger();
              }
              else if ((current_ekran.current_level >= EKRAN_SET_DT1) && (current_ekran.current_level <= EKRAN_RESET_DT4))
              {
                if(++current_ekran.index_position >= MAX_ROW_LIST_TYPE_SOURCE_DT) current_ekran.index_position = 0;
                position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;
                //������� ����� ��������� ���� ������ �������������� ������
                make_ekran_list_type_source_dt();
              }
              else if (current_ekran.current_level == EKRAN_LIST_D_AND)
              {
                if(++current_ekran.index_position >= MAX_ROW_FOR_LIST_D_AND) current_ekran.index_position = 0;
                position_in_current_level_menu[EKRAN_LIST_D_AND] = current_ekran.index_position;
                //������� ����� ��������� ������������ "�"
                make_ekran_chose_of_inputs_outputs_leds_df_buttons_for_ranguvannja(6);
              }
              else if (current_ekran.current_level == EKRAN_LIST_D_OR)
              {
                if(++current_ekran.index_position >= MAX_ROW_FOR_LIST_D_OR) current_ekran.index_position = 0;
                position_in_current_level_menu[EKRAN_LIST_D_OR] = current_ekran.index_position;
                //������� ����� ��������� ������������ "���"
                make_ekran_chose_of_inputs_outputs_leds_df_buttons_for_ranguvannja(7);
              }
              else if (current_ekran.current_level == EKRAN_LIST_D_XOR)
              {
                if(++current_ekran.index_position >= MAX_ROW_FOR_LIST_D_XOR) current_ekran.index_position = 0;
                position_in_current_level_menu[EKRAN_LIST_D_XOR] = current_ekran.index_position;
                //������� ����� ��������� ������������ "����.���"
                make_ekran_chose_of_inputs_outputs_leds_df_buttons_for_ranguvannja(8);
              }
              else if (current_ekran.current_level == EKRAN_LIST_D_NOT)
              {
                if(++current_ekran.index_position >= MAX_ROW_FOR_LIST_D_NOT) current_ekran.index_position = 0;
                position_in_current_level_menu[EKRAN_LIST_D_NOT] = current_ekran.index_position;
                //������� ����� ��������� ������������ "��"
                make_ekran_chose_of_inputs_outputs_leds_df_buttons_for_ranguvannja(9);
              }
              else if (current_ekran.current_level == EKRAN_LIST_BUTTONS_FOR_RANGUVANNJA)
              {
                //��������� ������ DOWN
                if(++current_ekran.index_position >= MAX_ROW_LIST_BUTTONS_FOR_RANGUVANNJA) current_ekran.index_position = 0;
                position_in_current_level_menu[EKRAN_LIST_BUTTONS_FOR_RANGUVANNJA] = current_ekran.index_position;
                //������� ����� ��������� �������������� ������ ��� ����������
                make_ekran_chose_of_inputs_outputs_leds_df_buttons_for_ranguvannja(4);
              }
              else if(current_ekran.current_level == EKRAN_INFO)
              {
                if(++current_ekran.index_position >= MAX_ROW_FOR_INFO) current_ekran.index_position = 0;
                position_in_current_level_menu[EKRAN_INFO] = current_ekran.index_position;
                //������� ����� ����������
                make_ekran_info();
              }
              else if(current_ekran.current_level == EKRAN_DATE_TIME_PZ)
              {
                if(++current_ekran.index_position >= MAX_ROW_FOR_DATE_TIME_PZ) current_ekran.index_position = 0;
                position_in_current_level_menu[EKRAN_DATE_TIME_PZ] = current_ekran.index_position;
                //������� ����� ����������� ��� ���� � ���� ��������
                make_ekran_date_time_pz();
              }
              else if(current_ekran.current_level == EKRAN_POINT_TIME_SETTINGS)
              {
                if(++current_ekran.index_position >= MAX_ROW_FOR_POINT_TIME_SETTINGS) current_ekran.index_position = 0;
                position_in_current_level_menu[EKRAN_POINT_TIME_SETTINGS] = current_ekran.index_position;
                //������� ����� ������ ���� ������������
                make_ekran_chose_item_of_point_time_settings();
              }
              else if(current_ekran.current_level == EKRAN_POINT_TIME_SETPOINT)
              {
                if(++current_ekran.index_position >= MAX_ROW_FOR_POINT_TIME_SETPOINT_RANGUVANNJA) current_ekran.index_position = 0;
                position_in_current_level_menu[EKRAN_POINT_TIME_SETPOINT] = current_ekran.index_position;
                //������� ����� ����������� ��� �������� ��� � ��������-���������-����������� ����������
                make_ekran_time_settings(0);
              }
              else if(current_ekran.current_level == EKRAN_POINT_TIME_RANGUVANNJA)
              {
                if(++current_ekran.index_position >= MAX_ROW_FOR_POINT_TIME_SETPOINT_RANGUVANNJA) current_ekran.index_position = 0;
                position_in_current_level_menu[EKRAN_POINT_TIME_RANGUVANNJA] = current_ekran.index_position;
                //������� ����� ����������� ��� �������� ��� � �����������
                make_ekran_time_settings(1);
              }
              else if(current_ekran.current_level == EKRAN_DIAGNOSTYKA)
              {
                if (
                    (diagnostyka[0] == 0) &&
                    (diagnostyka[1] == 0) &&
                    ((diagnostyka[2] & USED_BITS_IN_LAST_INDEX) == 0)
                   )
                {
                  current_ekran.index_position = 0;
                }
                else
                {
                  if(++current_ekran.index_position >= ((int)MAX_ROW_FOR_DIAGNOSTYKA)) current_ekran.index_position = 0;
                  while (_CHECK_SET_BIT(diagnostyka, current_ekran.index_position) ==0)
                  {
                    current_ekran.index_position++;
                    if(current_ekran.index_position >= ((int)MAX_ROW_FOR_DIAGNOSTYKA)) current_ekran.index_position = 0;
                  }
                }
                position_in_current_level_menu[EKRAN_DIAGNOSTYKA] = current_ekran.index_position;
                //������� ����� ����������
                make_ekran_diagnostyka(diagnostyka);
              }
              else if(current_ekran.current_level == EKRAN_LIST_INPUTS_OUTPUTS)
              {
                if(++current_ekran.index_position >= MAX_ROW_FOR_LIST_INPUTS_OUTPUTS) current_ekran.index_position = 0;
                position_in_current_level_menu[EKRAN_LIST_INPUTS_OUTPUTS] = current_ekran.index_position;
                //������� ����� ������ ������ �����-������
                make_ekran_list_inputs_outputs();
              }
              else if ((current_ekran.current_level == EKRAN_STATE_INPUTS) || (current_ekran.current_level == EKRAN_STATE_OUTPUTS))
              {
                if (current_ekran.current_level == EKRAN_STATE_INPUTS)
                {
                  if(++current_ekran.index_position >= NUMBER_INPUTS) current_ekran.index_position = 0;
                }
                else
                {
                  if(++current_ekran.index_position >= NUMBER_OUTPUTS) current_ekran.index_position = 0;
                }
              
                position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;
                //������� ����� ������ ����� ��� ������� 
                make_ekran_state_inputs_or_outputs(current_ekran.current_level - EKRAN_STATE_INPUTS);
              }
              else if(current_ekran.current_level == EKRAN_LIST_REGISTRATORS)
              {
                if(++current_ekran.index_position >= MAX_ROW_FOR_LIST_REGISTRATORS) current_ekran.index_position = 0;
                position_in_current_level_menu[EKRAN_LIST_REGISTRATORS] = current_ekran.index_position;
                //������� ����� ������ ����������
                make_ekran_list_registrators();
              }
              else if (
                       (current_ekran.current_level == EKRAN_LIST_ANALOG_REGISTRATOR_RECORDS) ||
                       (current_ekran.current_level == EKRAN_LIST_DIGITAL_REGISTRATOR_RECORDS) ||
                       (current_ekran.current_level == EKRAN_LIST_REGISTRATOR_PROGRAM_ERROR_RECORDS)
                      )
              {
                unsigned int number_records;
                unsigned int type_registrator;
  
                if (current_ekran.current_level == EKRAN_LIST_ANALOG_REGISTRATOR_RECORDS)
                {
                  number_records = info_rejestrator_ar.number_records;
                  type_registrator = INDEX_ML_ANALOG_REGISTRATOR_INFO;
                }
                else if (current_ekran.current_level == EKRAN_LIST_DIGITAL_REGISTRATOR_RECORDS)
                {
                  number_records = info_rejestrator_dr.number_records;
                  type_registrator = INDEX_ML_DIGITAL_REGISTRATOR_INFO;
                }
                else
                {
                  number_records = info_rejestrator_pr_err.number_records;
                  type_registrator = INDEX_ML_PROGRAM_ERROE_REGISTRATOR_INFO;
                }
                
                if(++current_ekran.index_position >= ((int)number_records)) current_ekran.index_position = 0;
                position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;
                //������� ����� ����������� ������
                make_ekran_list_records_registrator(type_registrator);
              }
              else if (current_ekran.current_level == EKRAN_TITLES_DIGITAL_REGISTRATOR)
              {
                if(++current_ekran.index_position >= MAX_ROW_FOR_TITLES_DIGITAL_REGISTRATOR) current_ekran.index_position = 0;
                position_in_current_level_menu[EKRAN_TITLES_DIGITAL_REGISTRATOR] = current_ekran.index_position;
                //������� ����� ����������� ��������� ���� ��� ����������� ����������
                make_ekran_list_titles_for_record_of_digital_registrator();
              }
              else if (current_ekran.current_level == EKRAN_DATA_LADEL_DR)
              {
                if(++current_ekran.index_position >= MAX_ROW_FOR_EKRAN_DATA_LABEL) current_ekran.index_position =  0;
                position_in_current_level_menu[EKRAN_DATA_LADEL_DR] = current_ekran.index_position;
                //������� ����� ����������� ���� ���� ����������� ������ ����������� ����������
                make_ekran_data_and_time_of_records_registrator(0);
              }
              else if (current_ekran.current_level == EKRAN_CHANGES_SIGNALS_DR)
              {
                current_ekran.index_position++;
                //������� ����� ����������� ��� ������� - ��������� � ����������� ���������
                make_ekran_changing_signals_digital_registrator();
              }
              else if (current_ekran.current_level == EKRAN_TITLES_PR_ERR_REGISTRATOR)
              {
                if(++current_ekran.index_position >= MAX_ROW_FOR_TITLES_PR_ERR_REGISTRATOR) current_ekran.index_position = 0;
                position_in_current_level_menu[EKRAN_TITLES_PR_ERR_REGISTRATOR] = current_ekran.index_position;
                //������� ����� ����������� ��������� ���� ��� ����������� ����������
                make_ekran_list_titles_for_record_of_pr_err_registrator();
              }
              else if (current_ekran.current_level == EKRAN_DATA_LADEL_PR_ERR)
              {
                if(++current_ekran.index_position >= MAX_ROW_FOR_EKRAN_DATA_LABEL) current_ekran.index_position =  0;
                position_in_current_level_menu[EKRAN_DATA_LADEL_PR_ERR] = current_ekran.index_position;
                //������� ����� ����������� ���� ���� ����������� ������ ���������� ���������� ����
                make_ekran_data_and_time_of_records_registrator(1);
              }
              else if (current_ekran.current_level == EKRAN_CHANGES_DIAGNOSTICS_PR_ERR)
              {
                current_ekran.index_position++;
                //������� ����� ����������� ��� ��������� - ��������� � ��������� ���������� ����
                make_ekran_changing_diagnostics_pr_err_registrator();
              }
              else if (current_ekran.current_level == EKRAN_DATA_LADEL_AR)
              {
                if(++current_ekran.index_position >= MAX_ROW_FOR_EKRAN_DATA_LABEL) current_ekran.index_position =  0;
                position_in_current_level_menu[EKRAN_DATA_LADEL_AR] = current_ekran.index_position;
                //������� ����� ����������� ���� ���� ����������� ������ ����������� ����������
                make_ekran_data_and_time_of_records_registrator(2);
              }
            
              //�������� �����������, �� ��������� ������ 
              new_state_keyboard &= (unsigned int)(~(1<<BIT_KEY_DOWN));
            }
            else
            {
              //��������� ����� ������� ������ - �� � ����������� ��������, ���� ������� ����������� ��� �������� ������ � ������ �����
              unsigned int temp_data = new_state_keyboard;
              new_state_keyboard &= ~temp_data;
            }
          }
        }
        break;
      }
/****************************************************************************************************************************************/ 

/******************************************************************************************************************************************/      
    case EKRAN_CONTROL_ZDZ:
    case EKRAN_TIMEOUT_APV_GROUP1:
    case EKRAN_TIMEOUT_APV_GROUP2:
    case EKRAN_TIMEOUT_APV_GROUP3:
    case EKRAN_TIMEOUT_APV_GROUP4:
    case EKRAN_CONTROL_APV:
    case EKRAN_SETPOINT_UROV_GROUP1:
    case EKRAN_SETPOINT_UROV_GROUP2:
    case EKRAN_SETPOINT_UROV_GROUP3:
    case EKRAN_SETPOINT_UROV_GROUP4:
    case EKRAN_TIMEOUT_UROV_GROUP1:
    case EKRAN_TIMEOUT_UROV_GROUP2:
    case EKRAN_TIMEOUT_UROV_GROUP3:
    case EKRAN_TIMEOUT_UROV_GROUP4:
    case EKRAN_CONTROL_UROV:
    case EKRAN_SETPOINT_ZOP_GROUP1:
    case EKRAN_SETPOINT_ZOP_GROUP2:
    case EKRAN_SETPOINT_ZOP_GROUP3:
    case EKRAN_SETPOINT_ZOP_GROUP4:
    case EKRAN_TIMEOUT_ZOP_GROUP1:
    case EKRAN_TIMEOUT_ZOP_GROUP2:
    case EKRAN_TIMEOUT_ZOP_GROUP3:
    case EKRAN_TIMEOUT_ZOP_GROUP4:
    case EKRAN_CONTROL_ZOP:
    case EKRAN_SETPOINT_UMIN_GROUP1:
    case EKRAN_SETPOINT_UMIN_GROUP2:
    case EKRAN_SETPOINT_UMIN_GROUP3:
    case EKRAN_SETPOINT_UMIN_GROUP4:
    case EKRAN_TIMEOUT_UMIN_GROUP1:
    case EKRAN_TIMEOUT_UMIN_GROUP2:
    case EKRAN_TIMEOUT_UMIN_GROUP3:
    case EKRAN_TIMEOUT_UMIN_GROUP4:
    case EKRAN_CONTROL_UMIN:
    case EKRAN_SETPOINT_UMAX_GROUP1:
    case EKRAN_SETPOINT_UMAX_GROUP2:
    case EKRAN_SETPOINT_UMAX_GROUP3:
    case EKRAN_SETPOINT_UMAX_GROUP4:
    case EKRAN_TIMEOUT_UMAX_GROUP1:
    case EKRAN_TIMEOUT_UMAX_GROUP2:
    case EKRAN_TIMEOUT_UMAX_GROUP3:
    case EKRAN_TIMEOUT_UMAX_GROUP4:
    case EKRAN_CONTROL_UMAX:
    case EKRAN_SETPOINT_AVR_UMIN_GROUP1:
    case EKRAN_SETPOINT_AVR_UMIN_GROUP2:
    case EKRAN_SETPOINT_AVR_UMIN_GROUP3:
    case EKRAN_SETPOINT_AVR_UMIN_GROUP4:
    case EKRAN_SETPOINT_AVR_UMAX_GROUP1:
    case EKRAN_SETPOINT_AVR_UMAX_GROUP2:
    case EKRAN_SETPOINT_AVR_UMAX_GROUP3:
    case EKRAN_SETPOINT_AVR_UMAX_GROUP4:
    case EKRAN_TIMEOUT_AVR_GENERAL_GROUP1:
    case EKRAN_TIMEOUT_AVR_GENERAL_GROUP2:
    case EKRAN_TIMEOUT_AVR_GENERAL_GROUP3:
    case EKRAN_TIMEOUT_AVR_GENERAL_GROUP4:
    case EKRAN_TIMEOUT_AVR_UMIN_GROUP1:
    case EKRAN_TIMEOUT_AVR_UMIN_GROUP2:
    case EKRAN_TIMEOUT_AVR_UMIN_GROUP3:
    case EKRAN_TIMEOUT_AVR_UMIN_GROUP4:
    case EKRAN_TIMEOUT_AVR_UMAX_GROUP1:
    case EKRAN_TIMEOUT_AVR_UMAX_GROUP2:
    case EKRAN_TIMEOUT_AVR_UMAX_GROUP3:
    case EKRAN_TIMEOUT_AVR_UMAX_GROUP4:
    case EKRAN_CONTROL_AVR:
    case EKRAN_SETPOINT_CTRL_PHASE_GROUP1:
    case EKRAN_SETPOINT_CTRL_PHASE_GROUP2:
    case EKRAN_SETPOINT_CTRL_PHASE_GROUP3:
    case EKRAN_SETPOINT_CTRL_PHASE_GROUP4:
    case EKRAN_TIMEOUT_CTRL_PHASE_GROUP1:
    case EKRAN_TIMEOUT_CTRL_PHASE_GROUP2:
    case EKRAN_TIMEOUT_CTRL_PHASE_GROUP3:
    case EKRAN_TIMEOUT_CTRL_PHASE_GROUP4:
    case EKRAN_CONTROL_CTRL_PHASE:
    case EKRAN_TRANSFORMATOR_INFO_SETPOINT:
    case EKRAN_TRANSFORMATOR_INFO_CONTROL:
    case EKRAN_SETPOINT_SWITCH:
    case EKRAN_TIMEOUT_SWITCH:
    case EKRAN_CONTROL_SWITCH:
    case EKRAN_DOPUSK_DV_UVV:
    case EKRAN_TYPE_INPUT_UVV:
    case EKRAN_TYPE_INPUT_SIGNAL_UVV:
    case EKRAN_TYPE_OUTPUT_UVV:
    case EKRAN_TYPE_LED_UVV:
    case EKRAN_ADDRESS:
    case EKRAN_VIEW_SPEED_RS485:
    case EKRAN_VIEW_PARE_RS485:
    case EKRAN_VIEW_STOP_BITS_RS485:
    case EKRAN_VIEW_TIMEOUT_RS485:
    case EKRAN_GENERAL_PICKUPS_EL:
    case EKRAN_LIST_TYPE_DF:
    case EKRAN_TIMEOUT_DF1:
    case EKRAN_TIMEOUT_DF2:
    case EKRAN_TIMEOUT_DF3:
    case EKRAN_TIMEOUT_DF4:
    case EKRAN_TIMEOUT_DF5:
    case EKRAN_TIMEOUT_DF6:
    case EKRAN_TIMEOUT_DF7:
    case EKRAN_TIMEOUT_DF8:
    case EKRAN_TIMEOUT_ANALOG_REGISTRATOR:
    case EKRAN_VIEW_SETTING_LANGUAGE:
    case EKRAN_CHOSE_EXTRA_SETTINGS:
      {
        //������� �� ��� ���� �����������
        unsigned int maska_keyboard_bits = (1<<BIT_KEY_ENTER)| (1<<BIT_KEY_ESC)|(1<<BIT_REWRITE);
        
        if (current_ekran.edition == 1)
          maska_keyboard_bits |= (1<<BIT_KEY_RIGHT) | (1<<BIT_KEY_LEFT) | (1<<BIT_KEY_UP)|(1<<BIT_KEY_DOWN);
        else if (current_ekran.edition == 0)
          maska_keyboard_bits |= (1<<BIT_KEY_UP)|(1<<BIT_KEY_DOWN);
        
        new_state_keyboard &= maska_keyboard_bits;
        //������ �������� 䳿, ���� ��������� ������ �� ��� ����� ��������, ��� ����� ������� �������� �����
        if (new_state_keyboard !=0)
        {
          //�������� ����� �� ��������� ������
          if((new_state_keyboard & (1<<BIT_REWRITE)) !=0)
          {
            if (current_ekran.current_level == EKRAN_CONTROL_ZDZ)
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_CONTROL_ZDZ) current_ekran.index_position = 0;
              position_in_current_level_menu[EKRAN_CONTROL_ZDZ] = current_ekran.index_position;
              
              //������� ����� ����������� ���������� ��� ���
              make_ekran_control_zdz();
            }
            else if(
                    (current_ekran.current_level >= EKRAN_TIMEOUT_APV_GROUP1) &&
                    (current_ekran.current_level <= EKRAN_TIMEOUT_APV_GROUP4)
                   )   
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_TIMEOUT_APV) current_ekran.index_position = 0;
              position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;

              //������� ����� �������� ���
              int group = (current_ekran.current_level - EKRAN_TIMEOUT_APV_GROUP1);
              make_ekran_timeout_apv(group);
            }
            else if(current_ekran.current_level == EKRAN_CONTROL_APV)
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_CONTROL_APV) current_ekran.index_position = 0;
              position_in_current_level_menu[EKRAN_CONTROL_APV] = current_ekran.index_position;
              //������� ����� ����������� ���������� ��� ���
              make_ekran_control_apv();
            }
            else if(
                    (current_ekran.current_level >= EKRAN_SETPOINT_UROV_GROUP1) &&
                    (current_ekran.current_level <= EKRAN_SETPOINT_UROV_GROUP4)
                   )   
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_SETPOINT_UROV) current_ekran.index_position = 0;
              position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;

              //������� ����� ������� ����
              int group = (current_ekran.current_level - EKRAN_SETPOINT_UROV_GROUP1);
              make_ekran_setpoint_urov(group);
            }
            else if(
                    (current_ekran.current_level >= EKRAN_TIMEOUT_UROV_GROUP1) &&
                    (current_ekran.current_level <= EKRAN_TIMEOUT_UROV_GROUP4)
                   )   
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_TIMEOUT_UROV) current_ekran.index_position = 0;
              position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;

              //������� ����� �������� ����
              int group = (current_ekran.current_level - EKRAN_TIMEOUT_UROV_GROUP1);
              make_ekran_timeout_urov(group);
            }
            else if(current_ekran.current_level == EKRAN_CONTROL_UROV)
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_CONTROL_UROV) current_ekran.index_position = 0;
              position_in_current_level_menu[EKRAN_CONTROL_UROV] = current_ekran.index_position;

              //������� ����� ����������� ���������� ��� ����
              make_ekran_control_urov();
            }
            else if(
                    (current_ekran.current_level >= EKRAN_SETPOINT_ZOP_GROUP1) &&
                    (current_ekran.current_level <= EKRAN_SETPOINT_ZOP_GROUP4)
                   )   
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_SETPOINT_ZOP) current_ekran.index_position = 0;
              position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;

              //������� ����� ������� ���(���)
              int group = (current_ekran.current_level - EKRAN_SETPOINT_ZOP_GROUP1);
              make_ekran_setpoint_zop(group);
            }
            else if(
                    (current_ekran.current_level >= EKRAN_TIMEOUT_ZOP_GROUP1) &&
                    (current_ekran.current_level <= EKRAN_TIMEOUT_ZOP_GROUP4)
                   )   
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_TIMEOUT_ZOP) current_ekran.index_position = 0;
              position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;

              //������� ����� �������� ���(���)
              int group = (current_ekran.current_level - EKRAN_TIMEOUT_ZOP_GROUP1);
              make_ekran_timeout_zop(group);
            }
            else if(current_ekran.current_level == EKRAN_CONTROL_ZOP)
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_CONTROL_ZOP) current_ekran.index_position = 0;
              position_in_current_level_menu[EKRAN_CONTROL_ZOP] = current_ekran.index_position;
              //������� ����� ����������� ���������� ��� ���(���)
              make_ekran_control_zop();
            }
            else if(
                    (current_ekran.current_level >= EKRAN_SETPOINT_UMIN_GROUP1) &&
                    (current_ekran.current_level <= EKRAN_SETPOINT_UMIN_GROUP4)
                   )   
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_SETPOINT_UMIN) current_ekran.index_position = 0;
              position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;

              //������� ����� ������� Umin
              int group = (current_ekran.current_level - EKRAN_SETPOINT_UMIN_GROUP1);
              make_ekran_setpoint_Umin(group);
            }
            else if(
                    (current_ekran.current_level >= EKRAN_TIMEOUT_UMIN_GROUP1) &&
                    (current_ekran.current_level <= EKRAN_TIMEOUT_UMIN_GROUP4)
                   )   
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_TIMEOUT_UMIN) current_ekran.index_position = 0;
              position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;

              //������� ����� �������� Umin
              int group = (current_ekran.current_level - EKRAN_TIMEOUT_UMIN_GROUP1);
              make_ekran_timeout_Umin(group);
            }
            else if(current_ekran.current_level == EKRAN_CONTROL_UMIN)
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_CONTROL_UMIN) current_ekran.index_position = 0;
              position_in_current_level_menu[EKRAN_CONTROL_UMIN] = current_ekran.index_position;
              //������� ����� ����������� ���������� ��� Umin
              make_ekran_control_Umin();
            }
            else if(
                    (current_ekran.current_level >= EKRAN_SETPOINT_UMAX_GROUP1) &&
                    (current_ekran.current_level <= EKRAN_SETPOINT_UMAX_GROUP4)
                   )   
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_SETPOINT_UMAX) current_ekran.index_position = 0;
              position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;

              //������� ����� ������� Umax
              int group = (current_ekran.current_level - EKRAN_SETPOINT_UMAX_GROUP1);
              make_ekran_setpoint_Umax(group);
            }
            else if(
                    (current_ekran.current_level >= EKRAN_TIMEOUT_UMAX_GROUP1) &&
                    (current_ekran.current_level <= EKRAN_TIMEOUT_UMAX_GROUP4)
                   )   
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_TIMEOUT_UMAX) current_ekran.index_position = 0;
              position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;

              //������� ����� �������� Umax
              int group = (current_ekran.current_level - EKRAN_TIMEOUT_UMAX_GROUP1);
              make_ekran_timeout_Umax(group);
            }
            else if(current_ekran.current_level == EKRAN_CONTROL_UMAX)
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_CONTROL_UMAX) current_ekran.index_position = 0;
              position_in_current_level_menu[EKRAN_CONTROL_UMAX] = current_ekran.index_position;
              //������� ����� ����������� ���������� ��� Umax
              make_ekran_control_Umax();
            }
            else if(
                    (current_ekran.current_level >= EKRAN_SETPOINT_AVR_UMIN_GROUP1) &&
                    (current_ekran.current_level <= EKRAN_SETPOINT_AVR_UMIN_GROUP4)
                   )   
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_SETPOINT_AVR_UMIN) current_ekran.index_position = 0;
              position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;

              //������� ����� ������� ��� Umin
              int group = (current_ekran.current_level - EKRAN_SETPOINT_AVR_UMIN_GROUP1);
              make_ekran_setpoint_avr_Umin(group);
            }
            else if(
                    (current_ekran.current_level >= EKRAN_SETPOINT_AVR_UMAX_GROUP1) &&
                    (current_ekran.current_level <= EKRAN_SETPOINT_AVR_UMAX_GROUP4)
                   )   
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_SETPOINT_AVR_UMAX) current_ekran.index_position = 0;
              position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;

              //������� ����� ������� ��� Umax
              int group = (current_ekran.current_level - EKRAN_SETPOINT_AVR_UMAX_GROUP1);
              make_ekran_setpoint_avr_Umax(group);
            }
            else if(
                    (current_ekran.current_level >= EKRAN_TIMEOUT_AVR_GENERAL_GROUP1) &&
                    (current_ekran.current_level <= EKRAN_TIMEOUT_AVR_GENERAL_GROUP4)
                   )   
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_TIMEOUT_AVR_GENERAL) current_ekran.index_position = 0;
              position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;

              //������� ����� �������� ��� (��������)
              int group = (current_ekran.current_level - EKRAN_TIMEOUT_AVR_GENERAL_GROUP1);
              make_ekran_timeout_avr_general(group);
            }
            else if(
                    (current_ekran.current_level >= EKRAN_TIMEOUT_AVR_UMIN_GROUP1) &&
                    (current_ekran.current_level <= EKRAN_TIMEOUT_AVR_UMIN_GROUP4)
                   )   
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_TIMEOUT_AVR_UMIN) current_ekran.index_position = 0;
              position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;

              //������� ����� �������� ��� Umin
              int group = (current_ekran.current_level - EKRAN_TIMEOUT_AVR_UMIN_GROUP1);
              make_ekran_timeout_avr_Umin(group);
            }
            else if(
                    (current_ekran.current_level >= EKRAN_TIMEOUT_AVR_UMAX_GROUP1) &&
                    (current_ekran.current_level <= EKRAN_TIMEOUT_AVR_UMAX_GROUP4)
                   )   
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_TIMEOUT_AVR_UMAX) current_ekran.index_position = 0;
              position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;

              //������� ����� �������� ��� Umax
              int group = (current_ekran.current_level - EKRAN_TIMEOUT_AVR_UMAX_GROUP1);
              make_ekran_timeout_avr_Umax(group);
            }
            else if(current_ekran.current_level == EKRAN_CONTROL_AVR)
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_CONTROL_AVR) current_ekran.index_position = 0;
              position_in_current_level_menu[EKRAN_CONTROL_AVR] = current_ekran.index_position;
              //������� ����� ����������� ���������� ��� ���
              make_ekran_control_avr();
            }
            else if(
                    (current_ekran.current_level >= EKRAN_SETPOINT_CTRL_PHASE_GROUP1) &&
                    (current_ekran.current_level <= EKRAN_SETPOINT_CTRL_PHASE_GROUP4)
                   )   
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_SETPOINT_CTRL_PHASE) current_ekran.index_position = 0;
              position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;

              //������� ����� ������� "�������� ���������"
              int group = (current_ekran.current_level - EKRAN_SETPOINT_CTRL_PHASE_GROUP1);
              make_ekran_setpoint_ctrl_phase(group);
            }
            else if(
                    (current_ekran.current_level >= EKRAN_TIMEOUT_CTRL_PHASE_GROUP1) &&
                    (current_ekran.current_level <= EKRAN_TIMEOUT_CTRL_PHASE_GROUP4)
                   )   
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_TIMEOUT_CTRL_PHASE) current_ekran.index_position = 0;
              position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;

              //������� ����� �������� "�������� ���������"
              int group = (current_ekran.current_level - EKRAN_TIMEOUT_CTRL_PHASE_GROUP1);
              make_ekran_timeout_ctrl_phase(group);
            }
            else if(current_ekran.current_level == EKRAN_CONTROL_CTRL_PHASE)
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_CONTROL_CTRL_PHASE) current_ekran.index_position = 0;
              position_in_current_level_menu[EKRAN_CONTROL_CTRL_PHASE] = current_ekran.index_position;
              //������� ����� ����������� ���������� ��� "�������� ���������"
              make_ekran_control_ctrl_phase();
            }
            else if(current_ekran.current_level == EKRAN_SETPOINT_SWITCH)
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_SETPOINT_SWITCH) current_ekran.index_position = 0;
              position_in_current_level_menu[EKRAN_SETPOINT_SWITCH] = current_ekran.index_position;
              //������� ����� ������� �����������
              make_ekran_setpoint_switch();
            }
            else if(current_ekran.current_level == EKRAN_TRANSFORMATOR_INFO_SETPOINT)
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_TRANSFORMATOR_INFO_SETPOINT) current_ekran.index_position = 0;
              position_in_current_level_menu[EKRAN_TRANSFORMATOR_INFO_SETPOINT] = current_ekran.index_position;
              //������� ����� ���������� �� ���������������
              make_ekran_transformator();
            }
            else if(current_ekran.current_level == EKRAN_TRANSFORMATOR_INFO_CONTROL)
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_TRANSFORMATOR_INFO_CONTROL) current_ekran.index_position = 0;
              position_in_current_level_menu[EKRAN_TRANSFORMATOR_INFO_CONTROL] = current_ekran.index_position;
              //������� ����� ����������� ����������� ��� ���� "�������������"
              make_ekran_transformator_control();
            }
            else if(current_ekran.current_level == EKRAN_TIMEOUT_SWITCH)
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_TIMEOUT_SWITCH) current_ekran.index_position = 0;
              position_in_current_level_menu[EKRAN_TIMEOUT_SWITCH] = current_ekran.index_position;
              //������� ����� �������� �����������
              make_ekran_timeout_switch();
            }
            else if(current_ekran.current_level == EKRAN_CONTROL_SWITCH)
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_CONTROL_SWITCH) current_ekran.index_position = 0;
              position_in_current_level_menu[EKRAN_CONTROL_SWITCH] = current_ekran.index_position;
              //������� ����� ����������� ���������� ��� ��������
              make_ekran_control_switch();
            }
            else if(current_ekran.current_level == EKRAN_DOPUSK_DV_UVV)
            {
              if(current_ekran.index_position >= NUMBER_INPUTS) current_ekran.index_position = 0;
              position_in_current_level_menu[EKRAN_DOPUSK_DV_UVV] = current_ekran.index_position;
              //������� ����� ���������� �� �������� ��
              make_ekran_dopusk_dv();
            }
            else if((current_ekran.current_level == EKRAN_TYPE_INPUT_UVV) || (current_ekran.current_level == EKRAN_TYPE_INPUT_SIGNAL_UVV))
            {
              if(current_ekran.index_position >= NUMBER_INPUTS) current_ekran.index_position = 0;
              position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;
              //������� ����� ����������� ���������� ��� ���
              if (current_ekran.current_level == EKRAN_TYPE_INPUT_UVV)
                make_ekran_type_input_uvv(0);
              else
                make_ekran_type_input_uvv(1);
            }
            else if(current_ekran.current_level == EKRAN_TYPE_OUTPUT_UVV)
            {
              if(current_ekran.index_position >= NUMBER_OUTPUTS) current_ekran.index_position = 0;
              position_in_current_level_menu[EKRAN_TYPE_OUTPUT_UVV] = current_ekran.index_position;
              //������� ����� ���� ������
              make_ekran_type_output_uvv();
            }
            else if(current_ekran.current_level == EKRAN_TYPE_LED_UVV)
            {
              if(current_ekran.index_position >= NUMBER_LEDS) current_ekran.index_position = 0;
              position_in_current_level_menu[EKRAN_TYPE_LED_UVV] = current_ekran.index_position;
              //������� ����� ���� ���������������
              make_ekran_type_led_uvv();
            }
            else if(current_ekran.current_level == EKRAN_ADDRESS)
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_ADDRESS) current_ekran.index_position = 0;
              position_in_current_level_menu[EKRAN_ADDRESS] = current_ekran.index_position;
              //������� ����� ���������� �� �������������� �����
              make_ekran_address();
            }
            else if(current_ekran.current_level == EKRAN_VIEW_SPEED_RS485)
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_VIEW_SPEED_INTERFACE) current_ekran.index_position = 0;
              position_in_current_level_menu[EKRAN_VIEW_SPEED_RS485] = current_ekran.index_position;
              //������� ����� ���������� �� �������� �����
              make_ekran_speed_interface();
            }
            else if(current_ekran.current_level == EKRAN_VIEW_PARE_RS485)
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_VIEW_PARE_INTERFACE) current_ekran.index_position = 0;
              position_in_current_level_menu[EKRAN_VIEW_PARE_RS485] = current_ekran.index_position;
              //������� ����� ���������� �� �������� �������
              make_ekran_pare_interface();
            }
            else if(current_ekran.current_level == EKRAN_VIEW_STOP_BITS_RS485)
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_VIEW_STOP_BITS_INTERFACE) current_ekran.index_position = 0;
              position_in_current_level_menu[EKRAN_VIEW_STOP_BITS_RS485] = current_ekran.index_position;
              //������� ����� ���������� �� ������� �������� ��
              make_ekran_stopbits_interface();
            }
            else if(current_ekran.current_level == EKRAN_VIEW_TIMEOUT_RS485)
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_VIEW_TIMEOUT_INTERFACE) current_ekran.index_position = 0;
              position_in_current_level_menu[EKRAN_VIEW_TIMEOUT_RS485] = current_ekran.index_position;
              //������� ����� ���������� �� time-out ���������� �������
              make_ekran_timeout_interface();
            }
            else if(current_ekran.current_level == EKRAN_GENERAL_PICKUPS_EL)
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_GENERAL_PICKUPS_EL) current_ekran.index_position = 0;
              position_in_current_level_menu[EKRAN_GENERAL_PICKUPS_EL] = current_ekran.index_position;
              //������� ����� ����������� ��������� �������� ��� ��������� �����
              make_ekran_general_pickups_el();
            }
            else if(current_ekran.current_level == EKRAN_LIST_TYPE_DF)
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_TYPE_DF) current_ekran.index_position = 0;
              position_in_current_level_menu[EKRAN_LIST_TYPE_DF] = current_ekran.index_position;
              //������� ����� ����������� ���� ������������� �������
              make_ekran_type_df();
            }
            else if((current_ekran.current_level >= EKRAN_TIMEOUT_DF1) && (current_ekran.current_level <= EKRAN_TIMEOUT_DF8))
            {
              if(current_ekran.index_position >= MAX_ROW_TIMEOUT_DF) current_ekran.index_position = 0;
              position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;
              //������� ����� ������� ������������ �������
              make_ekran_timeout_df(current_ekran.current_level - EKRAN_TIMEOUT_DF1);
            }
            else if(current_ekran.current_level == EKRAN_TIMEOUT_ANALOG_REGISTRATOR)
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_TIMEOUT_ANALOG_REGISTRATOR) current_ekran.index_position = 0;
              position_in_current_level_menu[EKRAN_TIMEOUT_ANALOG_REGISTRATOR] = current_ekran.index_position;
              //������� ����� �������� ����������� ����������
              make_ekran_timeout_analog_registrator();
            }
            else if(current_ekran.current_level == EKRAN_VIEW_SETTING_LANGUAGE)
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_VIEW_SETTING_LANGUAGE) current_ekran.index_position = 0;
              position_in_current_level_menu[EKRAN_VIEW_SETTING_LANGUAGE] = current_ekran.index_position;
              //������� ����� ���������� �� ��� ����
              make_ekran_setting_language();
            }
            else if(current_ekran.current_level == EKRAN_CHOSE_EXTRA_SETTINGS)
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_CHOSE_EXTRA_SETTINGS) current_ekran.index_position = 0;
              position_in_current_level_menu[EKRAN_CHOSE_EXTRA_SETTINGS] = current_ekran.index_position;
              //������� ����� ����������� ���������� �����������
              make_ekran_chose_extra_settings();
            }

            //������� �� ���������� ������
            new_state_keyboard &= (unsigned int)(~(1<<BIT_REWRITE));
          }
          else
          {
            if (new_state_keyboard == (1<<BIT_KEY_ENTER))
            {
              //��������� ������ ENTER
              if(current_ekran.edition == 0)
              {
                int temp_current_level = current_ekran.current_level;
                
                //������� ����� ��������� � ��������� ��� �����������
                if (current_ekran.current_level == EKRAN_CONTROL_ZDZ)
                {
                  edition_settings.control_zdz = current_settings.control_zdz;
                }
                else if(
                        (current_ekran.current_level >= EKRAN_TIMEOUT_APV_GROUP1) &&
                        (current_ekran.current_level <= EKRAN_TIMEOUT_APV_GROUP4)
                       )   
                {
                  int group = (current_ekran.current_level - EKRAN_TIMEOUT_APV_GROUP1);

                  if (current_ekran.index_position == INDEX_ML_TMOAPV1)
                  {
                    edition_settings.timeout_apv_1[group] = current_settings.timeout_apv_1[group];
                    current_ekran.position_cursor_x = COL_TMO_APV_1_BEGIN;
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOAPV2)
                  {
                    edition_settings.timeout_apv_2[group] = current_settings.timeout_apv_2[group];
                    current_ekran.position_cursor_x = COL_TMO_APV_2_BEGIN;
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOAPV3)
                  {
                    edition_settings.timeout_apv_3[group] = current_settings.timeout_apv_3[group];
                    current_ekran.position_cursor_x = COL_TMO_APV_3_BEGIN;
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOAPV4)
                  {
                    edition_settings.timeout_apv_4[group] = current_settings.timeout_apv_4[group];
                    current_ekran.position_cursor_x = COL_TMO_APV_4_BEGIN;
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOAPV_BLOCK_VID_APV1)
                  {
                    edition_settings.timeout_apv_block_vid_apv1[group] = current_settings.timeout_apv_block_vid_apv1[group];
                    current_ekran.position_cursor_x = COL_TMO_APV_BLOCK_VID_APV1_BEGIN;
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOAPV_BLOCK_VID_APV2)
                  {
                    edition_settings.timeout_apv_block_vid_apv2[group] = current_settings.timeout_apv_block_vid_apv2[group];
                    current_ekran.position_cursor_x = COL_TMO_APV_BLOCK_VID_APV2_BEGIN;
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOAPV_BLOCK_VID_APV3)
                  {
                    edition_settings.timeout_apv_block_vid_apv3[group] = current_settings.timeout_apv_block_vid_apv3[group];
                    current_ekran.position_cursor_x = COL_TMO_APV_BLOCK_VID_APV3_BEGIN;
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOAPV_BLOCK_VID_APV4)
                  {
                    edition_settings.timeout_apv_block_vid_apv4[group] = current_settings.timeout_apv_block_vid_apv4[group];
                    current_ekran.position_cursor_x = COL_TMO_APV_BLOCK_VID_APV4_BEGIN;
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOAPV_BLOCK_VID_VV)
                  {
                    edition_settings.timeout_apv_block_vid_VV[group] = current_settings.timeout_apv_block_vid_VV[group];
                    current_ekran.position_cursor_x = COL_TMO_APV_BLOCK_VID_VV_BEGIN;
                  }
                }
                else if(current_ekran.current_level == EKRAN_CONTROL_APV)
                {
                  edition_settings.control_apv = current_settings.control_apv;
                }
                else if(
                        (current_ekran.current_level >= EKRAN_SETPOINT_UROV_GROUP1) &&
                        (current_ekran.current_level <= EKRAN_SETPOINT_UROV_GROUP4)
                       )   
                {
                  int group = (current_ekran.current_level - EKRAN_SETPOINT_UROV_GROUP1);

                  edition_settings.setpoint_urov[group] = current_settings.setpoint_urov[group];
                  current_ekran.position_cursor_x = COL_SETPOINT_UROV_BEGIN;
                }
                else if(
                        (current_ekran.current_level >= EKRAN_TIMEOUT_UROV_GROUP1) &&
                        (current_ekran.current_level <= EKRAN_TIMEOUT_UROV_GROUP4)
                       )   
                {
                  int group = (current_ekran.current_level - EKRAN_TIMEOUT_UROV_GROUP1);

                  if (current_ekran.index_position == INDEX_ML_TMOUROV1)
                  {
                    edition_settings.timeout_urov_1[group] = current_settings.timeout_urov_1[group];
                    current_ekran.position_cursor_x = COL_TMO_UROV_1_BEGIN;
                  }
                  else
                  {
                    edition_settings.timeout_urov_2[group] = current_settings.timeout_urov_2[group];
                    current_ekran.position_cursor_x = COL_TMO_UROV_2_BEGIN;
                  }
                }
                else if(current_ekran.current_level == EKRAN_CONTROL_UROV)
                {
                  edition_settings.control_urov = current_settings.control_urov;
                }
                else if(
                        (current_ekran.current_level >= EKRAN_SETPOINT_ZOP_GROUP1) &&
                        (current_ekran.current_level <= EKRAN_SETPOINT_ZOP_GROUP4)
                       )   
                {
                  int group = (current_ekran.current_level - EKRAN_SETPOINT_ZOP_GROUP1);

                  edition_settings.setpoint_zop[group] = current_settings.setpoint_zop[group];
                  current_ekran.position_cursor_x = COL_SETPOINT_ZOP_BEGIN;
                }
                else if(
                        (current_ekran.current_level >= EKRAN_TIMEOUT_ZOP_GROUP1) &&
                        (current_ekran.current_level <= EKRAN_TIMEOUT_ZOP_GROUP4)
                       )   
                {
                  int group = (current_ekran.current_level - EKRAN_TIMEOUT_ZOP_GROUP1);

                  edition_settings.timeout_zop[group] = current_settings.timeout_zop[group];
                  current_ekran.position_cursor_x = COL_TMO_ZOP_BEGIN;
                }
                else if(current_ekran.current_level == EKRAN_CONTROL_ZOP)
                {
                  edition_settings.control_zop = current_settings.control_zop;
                }
                else if(
                        (current_ekran.current_level >= EKRAN_SETPOINT_UMIN_GROUP1) &&
                        (current_ekran.current_level <= EKRAN_SETPOINT_UMIN_GROUP4)
                       )   
                {
                  int group = (current_ekran.current_level - EKRAN_SETPOINT_UMIN_GROUP1);
                  
                  if (current_ekran.index_position == INDEX_ML_STPUMIN1)
                  {
                    edition_settings.setpoint_Umin1[group] = current_settings.setpoint_Umin1[group];
                    current_ekran.position_cursor_x = COL_SETPOINT_UMIN1_BEGIN;
                  }
                  else if (current_ekran.index_position == INDEX_ML_STPUMIN1_IBLK)
                  {
                    edition_settings.setpoint_Umin1_Iblk[group] = current_settings.setpoint_Umin1_Iblk[group];
                    current_ekran.position_cursor_x = COL_SETPOINT_UMIN1_IBLK_BEGIN;
                  }
                  else if (current_ekran.index_position == INDEX_ML_STPUMIN2)
                  {
                    edition_settings.setpoint_Umin2[group] = current_settings.setpoint_Umin2[group];
                    current_ekran.position_cursor_x = COL_SETPOINT_UMIN2_BEGIN;
                  }
                  else if (current_ekran.index_position == INDEX_ML_STPUMIN2_IBLK)
                  {
                    edition_settings.setpoint_Umin2_Iblk[group] = current_settings.setpoint_Umin2_Iblk[group];
                    current_ekran.position_cursor_x = COL_SETPOINT_UMIN2_IBLK_BEGIN;
                  }
                }
                else if(
                        (current_ekran.current_level >= EKRAN_TIMEOUT_UMIN_GROUP1) &&
                        (current_ekran.current_level <= EKRAN_TIMEOUT_UMIN_GROUP4)
                       )   
                {
                  int group = (current_ekran.current_level - EKRAN_TIMEOUT_UMIN_GROUP1);
                  
                  if (current_ekran.index_position == INDEX_ML_TMOUMIN1)
                  {
                    edition_settings.timeout_Umin1[group] = current_settings.timeout_Umin1[group];
                    current_ekran.position_cursor_x = COL_TMO_UMIN1_BEGIN;
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOUMIN2)
                  {
                    edition_settings.timeout_Umin2[group] = current_settings.timeout_Umin2[group];
                    current_ekran.position_cursor_x = COL_TMO_UMIN2_BEGIN;
                  }
                }
                else if(current_ekran.current_level == EKRAN_CONTROL_UMIN)
                {
                  edition_settings.control_Umin = current_settings.control_Umin;
                }
                else if(
                        (current_ekran.current_level >= EKRAN_SETPOINT_UMAX_GROUP1) &&
                        (current_ekran.current_level <= EKRAN_SETPOINT_UMAX_GROUP4)
                       )   
                {
                  int group = (current_ekran.current_level - EKRAN_SETPOINT_UMAX_GROUP1);
                  
                  if (current_ekran.index_position == INDEX_ML_STPUMAX1)
                  {
                    edition_settings.setpoint_Umax1[group] = current_settings.setpoint_Umax1[group];
                    current_ekran.position_cursor_x = COL_SETPOINT_UMAX1_BEGIN;
                  }
                  else if (current_ekran.index_position == INDEX_ML_STPUMAX2)
                  {
                    edition_settings.setpoint_Umax2[group] = current_settings.setpoint_Umax2[group];
                    current_ekran.position_cursor_x = COL_SETPOINT_UMAX2_BEGIN;
                  }
                }
                else if(
                        (current_ekran.current_level >= EKRAN_TIMEOUT_UMAX_GROUP1) &&
                        (current_ekran.current_level <= EKRAN_TIMEOUT_UMAX_GROUP4)
                       )   
                {
                  int group = (current_ekran.current_level - EKRAN_TIMEOUT_UMAX_GROUP1);
                  
                  if (current_ekran.index_position == INDEX_ML_TMOUMAX1)
                  {
                    edition_settings.timeout_Umax1[group] = current_settings.timeout_Umax1[group];
                    current_ekran.position_cursor_x = COL_TMO_UMAX1_BEGIN;
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOUMAX2)
                  {
                    edition_settings.timeout_Umax2[group] = current_settings.timeout_Umax2[group];
                    current_ekran.position_cursor_x = COL_TMO_UMAX2_BEGIN;
                  }
                }
                else if(current_ekran.current_level == EKRAN_CONTROL_UMAX)
                {
                  edition_settings.control_Umax = current_settings.control_Umax;
                }
                else if(
                        (current_ekran.current_level >= EKRAN_SETPOINT_AVR_UMIN_GROUP1) &&
                        (current_ekran.current_level <= EKRAN_SETPOINT_AVR_UMIN_GROUP4)
                       )   
                {
                  int group = (current_ekran.current_level - EKRAN_SETPOINT_AVR_UMIN_GROUP1);
                  
                  if (current_ekran.index_position == INDEX_ML_STPAVR_TN1_U1_UMIN)
                  {
                    edition_settings.setpoint_avr_tn1_U1_Umin[group] = current_settings.setpoint_avr_tn1_U1_Umin[group];
                    current_ekran.position_cursor_x = COL_SETPOINT_AVR_TN1_U1_UMIN_BEGIN;
                  }
                  else if (current_ekran.index_position == INDEX_ML_STPAVR_TN1_U2_LOW_WORK)
                  {
                    edition_settings.setpoint_avr_tn1_U2_low_work[group] = current_settings.setpoint_avr_tn1_U2_low_work[group];
                    current_ekran.position_cursor_x = COL_SETPOINT_AVR_TN1_U2_LOW_WORK_BEGIN;
                  }
                  else if (current_ekran.index_position == INDEX_ML_STPAVR_TN2_U2_UMIN)
                  {
                    edition_settings.setpoint_avr_tn2_U2_Umin[group] = current_settings.setpoint_avr_tn2_U2_Umin[group];
                    current_ekran.position_cursor_x = COL_SETPOINT_AVR_TN2_U2_UMIN_BEGIN;
                  }
                  else if (current_ekran.index_position == INDEX_ML_STPAVR_TN2_U1_LOW_WORK)
                  {
                    edition_settings.setpoint_avr_tn2_U1_low_work[group] = current_settings.setpoint_avr_tn2_U1_low_work[group];
                    current_ekran.position_cursor_x = COL_SETPOINT_AVR_TN2_U1_LOW_WORK_BEGIN;
                  }
                }
                else if(
                        (current_ekran.current_level >= EKRAN_SETPOINT_AVR_UMAX_GROUP1) &&
                        (current_ekran.current_level <= EKRAN_SETPOINT_AVR_UMAX_GROUP4)
                       )   
                {
                  int group = (current_ekran.current_level - EKRAN_SETPOINT_AVR_UMAX_GROUP1);
                  
                  if (current_ekran.index_position == INDEX_ML_STPAVR_TN1_U1_UMAX)
                  {
                    edition_settings.setpoint_avr_tn1_U1_Umax[group] = current_settings.setpoint_avr_tn1_U1_Umax[group];
                    current_ekran.position_cursor_x = COL_SETPOINT_AVR_TN1_U1_UMAX_BEGIN;
                  }
                  else if (current_ekran.index_position == INDEX_ML_STPAVR_TN1_U2_HIGH_WORK)
                  {
                    edition_settings.setpoint_avr_tn1_U2_high_work[group] = current_settings.setpoint_avr_tn1_U2_high_work[group];
                    current_ekran.position_cursor_x = COL_SETPOINT_AVR_TN1_U2_HIGH_WORK_BEGIN;
                  }
                  else if (current_ekran.index_position == INDEX_ML_STPAVR_TN2_U2_UMAX)
                  {
                    edition_settings.setpoint_avr_tn2_U2_Umax[group] = current_settings.setpoint_avr_tn2_U2_Umax[group];
                    current_ekran.position_cursor_x = COL_SETPOINT_AVR_TN2_U2_UMAX_BEGIN;
                  }
                  else if (current_ekran.index_position == INDEX_ML_STPAVR_TN2_U1_HIGH_WORK)
                  {
                    edition_settings.setpoint_avr_tn2_U1_high_work[group] = current_settings.setpoint_avr_tn2_U1_high_work[group];
                    current_ekran.position_cursor_x = COL_SETPOINT_AVR_TN2_U1_HIGH_WORK_BEGIN;
                  }
                }
                else if(
                        (current_ekran.current_level >= EKRAN_TIMEOUT_AVR_GENERAL_GROUP1) &&
                        (current_ekran.current_level <= EKRAN_TIMEOUT_AVR_GENERAL_GROUP4)
                       )   
                {
                  int group = (current_ekran.current_level - EKRAN_TIMEOUT_AVR_GENERAL_GROUP1);
                  
                  if (current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_BLK_K1)
                  {
                    edition_settings.timeout_avr_blk_k1[group] = current_settings.timeout_avr_blk_k1[group];
                    current_ekran.position_cursor_x = COL_TMO_AVR_GENERAL_BLK_K1_BEGIN;
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_PUSK_K1)
                  {
                    edition_settings.timeout_avr_pusk_k1[group] = current_settings.timeout_avr_pusk_k1[group];
                    current_ekran.position_cursor_x = COL_TMO_AVR_GENERAL_PUSK_K1_BEGIN;
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_D_DIJI_K1)
                  {
                    edition_settings.timeout_avr_d_diji_k1[group] = current_settings.timeout_avr_d_diji_k1[group];
                    current_ekran.position_cursor_x = COL_TMO_AVR_GENERAL_D_DIJI_K1_BEGIN;
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_VVIMK_REZ_K1)
                  {
                    edition_settings.timeout_avr_vvimk_rez_k1[group] = current_settings.timeout_avr_vvimk_rez_k1[group];
                    current_ekran.position_cursor_x = COL_TMO_AVR_GENERAL_VVIMK_REZ_K1_BEGIN;
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_VVIMK_K1)
                  {
                    edition_settings.timeout_avr_vvimk_k1[group] = current_settings.timeout_avr_vvimk_k1[group];
                    current_ekran.position_cursor_x = COL_TMO_AVR_GENERAL_VVIMK_K1_BEGIN;
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_VYMK_K1)
                  {
                    edition_settings.timeout_avr_vymk_k1[group] = current_settings.timeout_avr_vymk_k1[group];
                    current_ekran.position_cursor_x = COL_TMO_AVR_GENERAL_VYMK_K1_BEGIN;
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_BLK_K2)
                  {
                    edition_settings.timeout_avr_blk_k2[group] = current_settings.timeout_avr_blk_k2[group];
                    current_ekran.position_cursor_x = COL_TMO_AVR_GENERAL_BLK_K2_BEGIN;
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_PUSK_K2)
                  {
                    edition_settings.timeout_avr_pusk_k2[group] = current_settings.timeout_avr_pusk_k2[group];
                    current_ekran.position_cursor_x = COL_TMO_AVR_GENERAL_PUSK_K2_BEGIN;
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_D_DIJI_K2)
                  {
                    edition_settings.timeout_avr_d_diji_k2[group] = current_settings.timeout_avr_d_diji_k2[group];
                    current_ekran.position_cursor_x = COL_TMO_AVR_GENERAL_D_DIJI_K2_BEGIN;
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_VVIMK_REZ_K2)
                  {
                    edition_settings.timeout_avr_vvimk_rez_k2[group] = current_settings.timeout_avr_vvimk_rez_k2[group];
                    current_ekran.position_cursor_x = COL_TMO_AVR_GENERAL_VVIMK_REZ_K2_BEGIN;
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_VVIMK_K2)
                  {
                    edition_settings.timeout_avr_vvimk_k2[group] = current_settings.timeout_avr_vvimk_k2[group];
                    current_ekran.position_cursor_x = COL_TMO_AVR_GENERAL_VVIMK_K2_BEGIN;
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_VYMK_K2)
                  {
                    edition_settings.timeout_avr_vymk_k2[group] = current_settings.timeout_avr_vymk_k2[group];
                    current_ekran.position_cursor_x = COL_TMO_AVR_GENERAL_VYMK_K2_BEGIN;
                  }
                }
                else if(
                        (current_ekran.current_level >= EKRAN_TIMEOUT_AVR_UMIN_GROUP1) &&
                        (current_ekran.current_level <= EKRAN_TIMEOUT_AVR_UMIN_GROUP4)
                       )   
                {
                  int group = (current_ekran.current_level - EKRAN_TIMEOUT_AVR_UMIN_GROUP1);
                  
                  if (current_ekran.index_position == INDEX_ML_TMOAVR_UMIN_VYMK_ROB_K1)
                  {
                    edition_settings.timeout_avr_vymk_rob_k1_Umin[group] = current_settings.timeout_avr_vymk_rob_k1_Umin[group];
                    current_ekran.position_cursor_x = COL_TMO_AVR_UMIN_VYMK_ROB_K1_BEGIN;
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOAVR_UMIN_VYMK_ROB_K2)
                  {
                    edition_settings.timeout_avr_vymk_rob_k2_Umin[group] = current_settings.timeout_avr_vymk_rob_k2_Umin[group];
                    current_ekran.position_cursor_x = COL_TMO_AVR_UMIN_VYMK_ROB_K2_BEGIN;
                  }
                }
                else if(
                        (current_ekran.current_level >= EKRAN_TIMEOUT_AVR_UMAX_GROUP1) &&
                        (current_ekran.current_level <= EKRAN_TIMEOUT_AVR_UMAX_GROUP4)
                       )   
                {
                  int group = (current_ekran.current_level - EKRAN_TIMEOUT_AVR_UMAX_GROUP1);
                  
                  if (current_ekran.index_position == INDEX_ML_TMOAVR_UMAX_VYMK_ROB_K1)
                  {
                    edition_settings.timeout_avr_vymk_rob_k1_Umax[group] = current_settings.timeout_avr_vymk_rob_k1_Umax[group];
                    current_ekran.position_cursor_x = COL_TMO_AVR_UMAX_VYMK_ROB_K1_BEGIN;
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOAVR_UMAX_VYMK_ROB_K2)
                  {
                    edition_settings.timeout_avr_vymk_rob_k2_Umax[group] = current_settings.timeout_avr_vymk_rob_k2_Umax[group];
                    current_ekran.position_cursor_x = COL_TMO_AVR_UMAX_VYMK_ROB_K2_BEGIN;
                  }
                }
                else if(current_ekran.current_level == EKRAN_CONTROL_AVR)
                {
                  edition_settings.control_avr = current_settings.control_avr;
                }
                else if(
                        (current_ekran.current_level >= EKRAN_SETPOINT_CTRL_PHASE_GROUP1) &&
                        (current_ekran.current_level <= EKRAN_SETPOINT_CTRL_PHASE_GROUP4)
                       )   
                {
                  int group = (current_ekran.current_level - EKRAN_SETPOINT_CTRL_PHASE_GROUP1);
                  
                  if (current_ekran.index_position == INDEX_ML_STPCTRL_PHASE_U)
                  {
                    edition_settings.setpoint_ctrl_phase_U[group] = current_settings.setpoint_ctrl_phase_U[group];
                    current_ekran.position_cursor_x = COL_SETPOINT_CTRL_PHASE_U_BEGIN;
                  }
                  else if (current_ekran.index_position == INDEX_ML_STPCTRL_PHASE_PHI)
                  {
                    edition_settings.setpoint_ctrl_phase_phi[group] = current_settings.setpoint_ctrl_phase_phi[group];
                    current_ekran.position_cursor_x = COL_SETPOINT_CTRL_PHASE_PHI_BEGIN;
                  }
                  else if (current_ekran.index_position == INDEX_ML_STPCTRL_PHASE_F)
                  {
                    edition_settings.setpoint_ctrl_phase_f[group] = current_settings.setpoint_ctrl_phase_f[group];
                    current_ekran.position_cursor_x = COL_SETPOINT_CTRL_PHASE_F_BEGIN;
                  }
                }
                else if(
                        (current_ekran.current_level >= EKRAN_TIMEOUT_CTRL_PHASE_GROUP1) &&
                        (current_ekran.current_level <= EKRAN_TIMEOUT_CTRL_PHASE_GROUP4)
                       )   
                {
                  int group = (current_ekran.current_level - EKRAN_TIMEOUT_CTRL_PHASE_GROUP1);
                  
                  if (current_ekran.index_position == INDEX_ML_TMOCTRL_PHASE_U)
                  {
                    edition_settings.timeout_ctrl_phase_U[group] = current_settings.timeout_ctrl_phase_U[group];
                    current_ekran.position_cursor_x = COL_TMO_CTRL_PHASE_U_BEGIN;
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOCTRL_PHASE_U_D)
                  {
                    edition_settings.timeout_ctrl_phase_U_d[group] = current_settings.timeout_ctrl_phase_U_d[group];
                    current_ekran.position_cursor_x = COL_TMO_CTRL_PHASE_U_D_BEGIN;
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOCTRL_PHASE_PHI)
                  {
                    edition_settings.timeout_ctrl_phase_phi[group] = current_settings.timeout_ctrl_phase_phi[group];
                    current_ekran.position_cursor_x = COL_TMO_CTRL_PHASE_PHI_BEGIN;
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOCTRL_PHASE_PHI_D)
                  {
                    edition_settings.timeout_ctrl_phase_phi_d[group] = current_settings.timeout_ctrl_phase_phi_d[group];
                    current_ekran.position_cursor_x = COL_TMO_CTRL_PHASE_PHI_D_BEGIN;
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOCTRL_PHASE_F)
                  {
                    edition_settings.timeout_ctrl_phase_f[group] = current_settings.timeout_ctrl_phase_f[group];
                    current_ekran.position_cursor_x = COL_TMO_CTRL_PHASE_F_BEGIN;
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOCTRL_PHASE_F_D)
                  {
                    edition_settings.timeout_ctrl_phase_f_d[group] = current_settings.timeout_ctrl_phase_f_d[group];
                    current_ekran.position_cursor_x = COL_TMO_CTRL_PHASE_F_D_BEGIN;
                  }
                }
                else if(current_ekran.current_level == EKRAN_CONTROL_CTRL_PHASE)
                {
                  edition_settings.control_ctrl_phase = current_settings.control_ctrl_phase;
                }
                else if(current_ekran.current_level == EKRAN_TRANSFORMATOR_INFO_SETPOINT)
                {
                  if (current_ekran.index_position == INDEX_ML_TT)
                  {
                    edition_settings.TCurrent = current_settings.TCurrent;
                    current_ekran.position_cursor_x = COL_TT_BEGIN;
                  }
                  else
                  {
                    edition_settings.TVoltage = current_settings.TVoltage;
                    current_ekran.position_cursor_x = COL_TN_BEGIN;
                  }
                }
                else if(current_ekran.current_level == EKRAN_TRANSFORMATOR_INFO_CONTROL)
                {
                  edition_settings.control_transformator = current_settings.control_transformator;
                }
                else if(current_ekran.current_level == EKRAN_SETPOINT_SWITCH)
                {
                  if (current_ekran.index_position == INDEX_ML_STPInom)
                  {
                    edition_settings.setpoint_Inom = current_settings.setpoint_Inom;
                    current_ekran.position_cursor_x = COL_TMO_SWCH_ON_BEGIN;
                  }
                  else if (current_ekran.index_position == INDEX_ML_STPRKS_Inom)
                  {
                    edition_settings.setpoint_r_kom_st_Inom = current_settings.setpoint_r_kom_st_Inom;
                    current_ekran.position_cursor_x = COL_SETPOINT_RKS_Inom_BEGIN;
                  }
                  else if (current_ekran.index_position == INDEX_ML_STPMInom_vymk)
                  {
                    edition_settings.setpoint_Inom_vymk = current_settings.setpoint_Inom_vymk;
                    current_ekran.position_cursor_x = COL_SETPOINT_Inom_vymk_BEGIN;
                  }
                  else if (current_ekran.index_position == INDEX_ML_STPRKS_Inom_vymk)
                  {
                    edition_settings.setpoint_r_kom_st_Inom_vymk = current_settings.setpoint_r_kom_st_Inom_vymk;
                    current_ekran.position_cursor_x = COL_SETPOINT_RKS_Inom_vymk_BEGIN;
                  }
                  else if (current_ekran.index_position == INDEX_ML_STPPOCHATKOVYJ_RESURS)
                  {
                    edition_settings.setpoint_pochatkovyj_resurs = current_settings.setpoint_pochatkovyj_resurs;
                    current_ekran.position_cursor_x = COL_SETPOINT_POCHATKOVYJ_RESURS_BEGIN;
                  }
                  else if (current_ekran.index_position == INDEX_ML_STPKRYTYCHNYJ_RESURS)
                  {
                    edition_settings.setpoint_krytychnyj_resurs = current_settings.setpoint_krytychnyj_resurs;
                    current_ekran.position_cursor_x = COL_SETPOINT_KRYTYCHNYJ_RESURS_BEGIN;
                  }
                  else if (current_ekran.index_position == INDEX_ML_STPPOCHATKOVA_K_VYMK)
                  {
                    edition_settings.setpoint_pochatkova_k_vymk = current_settings.setpoint_pochatkova_k_vymk;
                    current_ekran.position_cursor_x = COL_SETPOINT_POCHATKOVA_K_VYMK_BEGIN;
                  }
                }
                else if(current_ekran.current_level == EKRAN_TIMEOUT_SWITCH)
                {
                  if (current_ekran.index_position == INDEX_ML_TMOON)
                  {
                    edition_settings.timeout_swch_on = current_settings.timeout_swch_on;
                    current_ekran.position_cursor_x = COL_TMO_SWCH_ON_BEGIN;
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOOFF)
                  {
                    edition_settings.timeout_swch_off = current_settings.timeout_swch_off;
                    current_ekran.position_cursor_x = COL_TMO_SWCH_OFF_BEGIN;
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOUDL_BLK_ON)
                  {
                    edition_settings.timeout_swch_udl_blk_on = current_settings.timeout_swch_udl_blk_on;
                    current_ekran.position_cursor_x = COL_TMO_SWCH_UDL_BLK_ON_BEGIN;
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOPRYVODA_VV)
                  {
                    edition_settings.timeout_pryvoda_VV = current_settings.timeout_pryvoda_VV;
                    current_ekran.position_cursor_x = COL_TMO_PRYVODA_VV_BEGIN;
                  }
                }
                else if(current_ekran.current_level == EKRAN_CONTROL_SWITCH)
                {
                  edition_settings.control_switch = current_settings.control_switch;
                }
                else if(current_ekran.current_level == EKRAN_DOPUSK_DV_UVV)
                {
                  edition_settings.dopusk_dv[current_ekran.index_position] = current_settings.dopusk_dv[current_ekran.index_position];
                  current_ekran.position_cursor_x = COL_DOPUSK_DV_BEGIN;
                }
                else if(current_ekran.current_level == EKRAN_TYPE_INPUT_UVV)
                {
                  edition_settings.type_of_input = current_settings.type_of_input;
                }
                else if(current_ekran.current_level == EKRAN_TYPE_INPUT_SIGNAL_UVV)
                {
                  edition_settings.type_of_input_signal = current_settings.type_of_input_signal;
                }
                else if(current_ekran.current_level == EKRAN_TYPE_OUTPUT_UVV)
                {
                  edition_settings.type_of_output       = current_settings.type_of_output;
                  edition_settings.type_of_output_modif = current_settings.type_of_output_modif;
                }
                else if(current_ekran.current_level == EKRAN_TYPE_LED_UVV)
                {
                  edition_settings.type_of_led = current_settings.type_of_led;
                }
                else if(current_ekran.current_level == EKRAN_ADDRESS)
                {
                  edition_settings.address = current_settings.address;
                  current_ekran.position_cursor_x = COL_ADDRESS_BEGIN;
                }
                else if(current_ekran.current_level == EKRAN_VIEW_SPEED_RS485)
                {
                  edition_settings.speed_RS485 = current_settings.speed_RS485;
                }
                else if(current_ekran.current_level == EKRAN_VIEW_PARE_RS485)
                {
                  edition_settings.pare_bit_RS485 = current_settings.pare_bit_RS485;
                }
                else if(current_ekran.current_level == EKRAN_VIEW_STOP_BITS_RS485)
                {
                  edition_settings.number_stop_bit_RS485 = current_settings.number_stop_bit_RS485;
                }
                else if(current_ekran.current_level == EKRAN_VIEW_TIMEOUT_RS485)
                {
                  edition_settings.time_out_1_RS485 = current_settings.time_out_1_RS485;
                  current_ekran.position_cursor_x = COL_TIMEOUT_INTERFACE_BEGIN;
                }
                else if(current_ekran.current_level == EKRAN_GENERAL_PICKUPS_EL)
                {
                  if (current_ekran.index_position == INDEX_ML_NUMBER_INERATION)
                  {
                    edition_settings.number_iteration_el = current_settings.number_iteration_el;
                    current_ekran.position_cursor_x = COL_NUMBER_INERATION_BEGIN;
                  }
//                  else if (current_ekran.index_position == INDEX_ML_NUMBER_DEFINED_FUNCTIONS)
//                  {
//                    edition_settings.number_defined_df = current_settings.number_defined_df;
//                    current_ekran.position_cursor_x = COL_NUMBER_DEFINED_FUNCTIONS_BEGIN;
//                  }
//                  else if (current_ekran.index_position == INDEX_ML_NUMBER_DEFINED_TRIGGERS)
//                  {
//                    edition_settings.number_defined_dt = current_settings.number_defined_dt;
//                    current_ekran.position_cursor_x = COL_NUMBER_DEFINED_TRIGGERS_BEGIN;
//                  }
//                  else if (current_ekran.index_position == INDEX_ML_NUMBER_DEFINED_AND)
//                  {
//                    edition_settings.number_defined_and = current_settings.number_defined_and;
//                    current_ekran.position_cursor_x = COL_NUMBER_DEFINED_AND_BEGIN;
//                  }
//                  else if (current_ekran.index_position == INDEX_ML_NUMBER_DEFINED_OR)
//                  {
//                    edition_settings.number_defined_or = current_settings.number_defined_or;
//                    current_ekran.position_cursor_x = COL_NUMBER_DEFINED_OR_BEGIN;
//                  }
//                  else if (current_ekran.index_position == INDEX_ML_NUMBER_DEFINED_XOR)
//                  {
//                    edition_settings.number_defined_xor = current_settings.number_defined_xor;
//                    current_ekran.position_cursor_x = COL_NUMBER_DEFINED_XOR_BEGIN;
//                  }
//                  else if (current_ekran.index_position == INDEX_ML_NUMBER_DEFINED_NOT)
//                  {
//                    edition_settings.number_defined_not = current_settings.number_defined_not;
//                    current_ekran.position_cursor_x = COL_NUMBER_DEFINED_NOT_BEGIN;
//                  }
                }
                else if(current_ekran.current_level == EKRAN_LIST_TYPE_DF)
                {
                  edition_settings.type_df = current_settings.type_df;
                }
                else if((current_ekran.current_level >= EKRAN_TIMEOUT_DF1) && (current_ekran.current_level <= EKRAN_TIMEOUT_DF8))
                {
                  if (current_ekran.index_position == INDEX_ML_TMO_DF_PAUSE)
                  {
                    edition_settings.timeout_pause_df[current_ekran.current_level - EKRAN_TIMEOUT_DF1] = 
                      current_settings.timeout_pause_df[current_ekran.current_level - EKRAN_TIMEOUT_DF1];
                    current_ekran.position_cursor_x = COL_TMO_DF_PAUSE_BEGIN;
                  }
                  else
                  {
                    edition_settings.timeout_work_df[current_ekran.current_level - EKRAN_TIMEOUT_DF1] = 
                      current_settings.timeout_work_df[current_ekran.current_level - EKRAN_TIMEOUT_DF1];
                    current_ekran.position_cursor_x = COL_TMO_DF_PAUSE_BEGIN;
                  }
                }
                else if(current_ekran.current_level == EKRAN_TIMEOUT_ANALOG_REGISTRATOR)
                {
                  if (current_ekran.index_position == INDEX_ML_TMOPREFAULT)
                  {
                    edition_settings.prefault_number_periods = current_settings.prefault_number_periods;
                    current_ekran.position_cursor_x = COL_TMO_PREFAULT_BEGIN;
                  }
                  else
                  {
                    edition_settings.postfault_number_periods = current_settings.postfault_number_periods;
                    current_ekran.position_cursor_x = COL_TMO_POSTFAULT_BEGIN;
                  }
                }
                else if(current_ekran.current_level == EKRAN_VIEW_SETTING_LANGUAGE)
                {
                  edition_settings.language = current_settings.language;
                }
                else if(current_ekran.current_level == EKRAN_CHOSE_EXTRA_SETTINGS)
                {
                  edition_settings.control_extra_settings_1 = current_settings.control_extra_settings_1;
                }

                //ϳ�������� �� ������ ����������� - �������� �������� ������
                current_ekran.cursor_on = 1;
                current_ekran.cursor_blinking_on = 1;
                if (current_settings.password1 != 0)
                {
                  //���������� �� ���� ������ ������
                  current_ekran.current_level = EKRAN_LEVEL_PASSWORD;
                  previous_level_in_current_level_menu[current_ekran.current_level] = temp_current_level;
                  current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
                }
                else
                {
                  //���������� � ����� �����������
                  current_ekran.edition = 1;
                }
              }
              else if (current_ekran.edition == 1)
              {
                //���������� �� ���� ���� ��������
                unsigned int found_changes = 0;

                if (current_ekran.current_level == EKRAN_CONTROL_ZDZ)
                {
                  if (edition_settings.control_zdz != current_settings.control_zdz) found_changes = 1;
                }
                else if(
                        (current_ekran.current_level >= EKRAN_TIMEOUT_APV_GROUP1) &&
                        (current_ekran.current_level <= EKRAN_TIMEOUT_APV_GROUP4)
                       )   
                {
                  int group = (current_ekran.current_level - EKRAN_TIMEOUT_APV_GROUP1);
                 
                  if (current_ekran.index_position == INDEX_ML_TMOAPV1)
                  {
                    if (edition_settings.timeout_apv_1[group] != current_settings.timeout_apv_1[group]) found_changes = 1;
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOAPV2)
                  {
                    if (edition_settings.timeout_apv_2[group] != current_settings.timeout_apv_2[group]) found_changes = 1;
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOAPV3)
                  {
                    if (edition_settings.timeout_apv_3[group] != current_settings.timeout_apv_3[group]) found_changes = 1;
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOAPV4)
                  {
                    if (edition_settings.timeout_apv_4[group] != current_settings.timeout_apv_4[group]) found_changes = 1;
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOAPV_BLOCK_VID_APV1)
                  {
                    if (edition_settings.timeout_apv_block_vid_apv1[group] != current_settings.timeout_apv_block_vid_apv1[group]) found_changes = 1;
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOAPV_BLOCK_VID_APV2)
                  {
                    if (edition_settings.timeout_apv_block_vid_apv2[group] != current_settings.timeout_apv_block_vid_apv2[group]) found_changes = 1;
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOAPV_BLOCK_VID_APV3)
                  {
                    if (edition_settings.timeout_apv_block_vid_apv3[group] != current_settings.timeout_apv_block_vid_apv3[group]) found_changes = 1;
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOAPV_BLOCK_VID_APV4)
                  {
                    if (edition_settings.timeout_apv_block_vid_apv4[group] != current_settings.timeout_apv_block_vid_apv4[group]) found_changes = 1;
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOAPV_BLOCK_VID_VV)
                  {
                    if (edition_settings.timeout_apv_block_vid_VV[group] != current_settings.timeout_apv_block_vid_VV[group]) found_changes = 1;
                  }
                }
                else if(current_ekran.current_level == EKRAN_CONTROL_APV)
                {
                  if (edition_settings.control_apv != current_settings.control_apv) found_changes = 1;
                }
                else if(
                        (current_ekran.current_level >= EKRAN_SETPOINT_UROV_GROUP1) &&
                        (current_ekran.current_level <= EKRAN_SETPOINT_UROV_GROUP4)
                       )   
                {
                  int group = (current_ekran.current_level - EKRAN_SETPOINT_UROV_GROUP1);
                 
                  if (edition_settings.setpoint_urov[group] != current_settings.setpoint_urov[group]) found_changes = 1;
                }
                else if(
                        (current_ekran.current_level >= EKRAN_TIMEOUT_UROV_GROUP1) &&
                        (current_ekran.current_level <= EKRAN_TIMEOUT_UROV_GROUP4)
                       )   
                {
                  int group = (current_ekran.current_level - EKRAN_TIMEOUT_UROV_GROUP1);
                 
                  if (current_ekran.index_position == INDEX_ML_TMOUROV1)
                  {
                    if (edition_settings.timeout_urov_1[group] != current_settings.timeout_urov_1[group]) found_changes = 1;
                  }
                  else
                  {
                    if (edition_settings.timeout_urov_2[group] != current_settings.timeout_urov_2[group]) found_changes = 1;
                  }
                }
                else if(current_ekran.current_level == EKRAN_CONTROL_UROV)
                {
                  if (edition_settings.control_urov != current_settings.control_urov) found_changes = 1;
                }
                else if(
                        (current_ekran.current_level >= EKRAN_SETPOINT_ZOP_GROUP1) &&
                        (current_ekran.current_level <= EKRAN_SETPOINT_ZOP_GROUP4)
                       )   
                {
                  int group = (current_ekran.current_level - EKRAN_SETPOINT_ZOP_GROUP1);
                 
                  if (edition_settings.setpoint_zop[group] != current_settings.setpoint_zop[group]) found_changes = 1;
                }
                else if(
                        (current_ekran.current_level >= EKRAN_TIMEOUT_ZOP_GROUP1) &&
                        (current_ekran.current_level <= EKRAN_TIMEOUT_ZOP_GROUP4)
                       )   
                {
                  int group = (current_ekran.current_level - EKRAN_TIMEOUT_ZOP_GROUP1);
                 
                  if (edition_settings.timeout_zop[group] != current_settings.timeout_zop[group]) found_changes = 1;
                }
                else if(current_ekran.current_level == EKRAN_CONTROL_ZOP)
                {
                  if (edition_settings.control_zop != current_settings.control_zop) found_changes = 1;
                }
                else if(
                        (current_ekran.current_level >= EKRAN_SETPOINT_UMIN_GROUP1) &&
                        (current_ekran.current_level <= EKRAN_SETPOINT_UMIN_GROUP4)
                       )   
                {
                  int group = (current_ekran.current_level - EKRAN_SETPOINT_UMIN_GROUP1);
                 
                  if (current_ekran.index_position == INDEX_ML_STPUMIN1)
                  {
                    if (edition_settings.setpoint_Umin1[group] != current_settings.setpoint_Umin1[group]) found_changes = 1;
                  }
                  else if (current_ekran.index_position == INDEX_ML_STPUMIN1_IBLK)
                  {
                    if (edition_settings.setpoint_Umin1_Iblk[group] != current_settings.setpoint_Umin1_Iblk[group]) found_changes = 1;
                  }
                  else if (current_ekran.index_position == INDEX_ML_STPUMIN2)
                  {
                    if (edition_settings.setpoint_Umin2[group] != current_settings.setpoint_Umin2[group]) found_changes = 1;
                  }
                  else if (current_ekran.index_position == INDEX_ML_STPUMIN2_IBLK)
                  {
                    if (edition_settings.setpoint_Umin2_Iblk[group] != current_settings.setpoint_Umin2_Iblk[group]) found_changes = 1;
                  }
                }
                else if(
                        (current_ekran.current_level >= EKRAN_TIMEOUT_UMIN_GROUP1) &&
                        (current_ekran.current_level <= EKRAN_TIMEOUT_UMIN_GROUP4)
                       )   
                {
                  int group = (current_ekran.current_level - EKRAN_TIMEOUT_UMIN_GROUP1);
                  
                  if (current_ekran.index_position == INDEX_ML_TMOUMIN1)
                  {
                    if (edition_settings.timeout_Umin1[group] != current_settings.timeout_Umin1[group]) found_changes = 1;
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOUMIN2)
                  {
                    if (edition_settings.timeout_Umin2[group] != current_settings.timeout_Umin2[group]) found_changes = 1;
                  }
                }
                else if(current_ekran.current_level == EKRAN_CONTROL_UMIN)
                {
                  if (edition_settings.control_Umin != current_settings.control_Umin) found_changes = 1;
                }
                else if(
                        (current_ekran.current_level >= EKRAN_SETPOINT_UMAX_GROUP1) &&
                        (current_ekran.current_level <= EKRAN_SETPOINT_UMAX_GROUP4)
                       )   
                {
                  int group = (current_ekran.current_level - EKRAN_SETPOINT_UMAX_GROUP1);
                 
                  if (current_ekran.index_position == INDEX_ML_STPUMAX1)
                  {
                    if (edition_settings.setpoint_Umax1[group] != current_settings.setpoint_Umax1[group]) found_changes = 1;
                  }
                  else if (current_ekran.index_position == INDEX_ML_STPUMAX2)
                  {
                    if (edition_settings.setpoint_Umax2[group] != current_settings.setpoint_Umax2[group]) found_changes = 1;
                  }
                }
                else if(
                        (current_ekran.current_level >= EKRAN_TIMEOUT_UMAX_GROUP1) &&
                        (current_ekran.current_level <= EKRAN_TIMEOUT_UMAX_GROUP4)
                       )   
                {
                  int group = (current_ekran.current_level - EKRAN_TIMEOUT_UMAX_GROUP1);
                  
                  if (current_ekran.index_position == INDEX_ML_TMOUMAX1)
                  {
                    if (edition_settings.timeout_Umax1[group] != current_settings.timeout_Umax1[group]) found_changes = 1;
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOUMAX2)
                  {
                    if (edition_settings.timeout_Umax2[group] != current_settings.timeout_Umax2[group]) found_changes = 1;
                  }
                }
                else if(current_ekran.current_level == EKRAN_CONTROL_UMAX)
                {
                  if (edition_settings.control_Umax != current_settings.control_Umax) found_changes = 1;
                }
                else if(
                        (current_ekran.current_level >= EKRAN_SETPOINT_AVR_UMIN_GROUP1) &&
                        (current_ekran.current_level <= EKRAN_SETPOINT_AVR_UMIN_GROUP4)
                       )   
                {
                  int group = (current_ekran.current_level - EKRAN_SETPOINT_AVR_UMIN_GROUP1);
                 
                  if (current_ekran.index_position == INDEX_ML_STPAVR_TN1_U1_UMIN)
                  {
                    if (edition_settings.setpoint_avr_tn1_U1_Umin[group] != current_settings.setpoint_avr_tn1_U1_Umin[group]) found_changes = 1;
                  }
                  else if (current_ekran.index_position == INDEX_ML_STPAVR_TN1_U2_LOW_WORK)
                  {
                    if (edition_settings.setpoint_avr_tn1_U2_low_work[group] != current_settings.setpoint_avr_tn1_U2_low_work[group]) found_changes = 1;
                  }
                  else if (current_ekran.index_position == INDEX_ML_STPAVR_TN2_U2_UMIN)
                  {
                    if (edition_settings.setpoint_avr_tn2_U2_Umin[group] != current_settings.setpoint_avr_tn2_U2_Umin[group]) found_changes = 1;
                  }
                  else if (current_ekran.index_position == INDEX_ML_STPAVR_TN2_U1_LOW_WORK)
                  {
                    if (edition_settings.setpoint_avr_tn2_U1_low_work[group] != current_settings.setpoint_avr_tn2_U1_low_work[group]) found_changes = 1;
                  }
                }
                else if(
                        (current_ekran.current_level >= EKRAN_SETPOINT_AVR_UMAX_GROUP1) &&
                        (current_ekran.current_level <= EKRAN_SETPOINT_AVR_UMAX_GROUP4)
                       )   
                {
                  int group = (current_ekran.current_level - EKRAN_SETPOINT_AVR_UMAX_GROUP1);
                 
                  if (current_ekran.index_position == INDEX_ML_STPAVR_TN1_U1_UMAX)
                  {
                    if (edition_settings.setpoint_avr_tn1_U1_Umax[group] != current_settings.setpoint_avr_tn1_U1_Umax[group]) found_changes = 1;
                  }
                  else if (current_ekran.index_position == INDEX_ML_STPAVR_TN1_U2_HIGH_WORK)
                  {
                    if (edition_settings.setpoint_avr_tn1_U2_high_work[group] != current_settings.setpoint_avr_tn1_U2_high_work[group]) found_changes = 1;
                  }
                  else if (current_ekran.index_position == INDEX_ML_STPAVR_TN2_U2_UMAX)
                  {
                    if (edition_settings.setpoint_avr_tn2_U2_Umax[group] != current_settings.setpoint_avr_tn2_U2_Umax[group]) found_changes = 1;
                  }
                  else if (current_ekran.index_position == INDEX_ML_STPAVR_TN2_U1_HIGH_WORK)
                  {
                    if (edition_settings.setpoint_avr_tn2_U1_high_work[group] != current_settings.setpoint_avr_tn2_U1_high_work[group]) found_changes = 1;
                  }
                }
                else if(
                        (current_ekran.current_level >= EKRAN_TIMEOUT_AVR_GENERAL_GROUP1) &&
                        (current_ekran.current_level <= EKRAN_TIMEOUT_AVR_GENERAL_GROUP4)
                       )   
                {
                  int group = (current_ekran.current_level - EKRAN_TIMEOUT_AVR_GENERAL_GROUP1);
                  
                  if (current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_BLK_K1)
                  {
                    if (edition_settings.timeout_avr_blk_k1[group] != current_settings.timeout_avr_blk_k1[group]) found_changes = 1;
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_PUSK_K1)
                  {
                    if (edition_settings.timeout_avr_pusk_k1[group] != current_settings.timeout_avr_pusk_k1[group]) found_changes = 1;
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_D_DIJI_K1)
                  {
                    if (edition_settings.timeout_avr_d_diji_k1[group] != current_settings.timeout_avr_d_diji_k1[group]) found_changes = 1;
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_VVIMK_REZ_K1)
                  {
                    if (edition_settings.timeout_avr_vvimk_rez_k1[group] != current_settings.timeout_avr_vvimk_rez_k1[group]) found_changes = 1;
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_VVIMK_K1)
                  {
                    if (edition_settings.timeout_avr_vvimk_k1[group] != current_settings.timeout_avr_vvimk_k1[group]) found_changes = 1;
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_VYMK_K1)
                  {
                    if (edition_settings.timeout_avr_vymk_k1[group] != current_settings.timeout_avr_vymk_k1[group]) found_changes = 1;
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_BLK_K2)
                  {
                    if (edition_settings.timeout_avr_blk_k2[group] != current_settings.timeout_avr_blk_k2[group]) found_changes = 1;
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_PUSK_K2)
                  {
                    if (edition_settings.timeout_avr_pusk_k2[group] != current_settings.timeout_avr_pusk_k2[group]) found_changes = 1;
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_D_DIJI_K2)
                  {
                    if (edition_settings.timeout_avr_d_diji_k2[group] != current_settings.timeout_avr_d_diji_k2[group]) found_changes = 1;
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_VVIMK_REZ_K2)
                  {
                    if (edition_settings.timeout_avr_vvimk_rez_k2[group] != current_settings.timeout_avr_vvimk_rez_k2[group]) found_changes = 1;
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_VVIMK_K2)
                  {
                    if (edition_settings.timeout_avr_vvimk_k2[group] != current_settings.timeout_avr_vvimk_k2[group]) found_changes = 1;
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_VYMK_K2)
                  {
                    if (edition_settings.timeout_avr_vymk_k2[group] != current_settings.timeout_avr_vymk_k2[group]) found_changes = 1;
                  }
                }
                else if(
                        (current_ekran.current_level >= EKRAN_TIMEOUT_AVR_UMIN_GROUP1) &&
                        (current_ekran.current_level <= EKRAN_TIMEOUT_AVR_UMIN_GROUP4)
                       )   
                {
                  int group = (current_ekran.current_level - EKRAN_TIMEOUT_AVR_UMIN_GROUP1);
                  
                  if (current_ekran.index_position == INDEX_ML_TMOAVR_UMIN_VYMK_ROB_K1)
                  {
                    if (edition_settings.timeout_avr_vymk_rob_k1_Umin[group] != current_settings.timeout_avr_vymk_rob_k1_Umin[group]) found_changes = 1;
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOAVR_UMIN_VYMK_ROB_K2)
                  {
                    if (edition_settings.timeout_avr_vymk_rob_k2_Umin[group] != current_settings.timeout_avr_vymk_rob_k2_Umin[group]) found_changes = 1;
                  }
                }
                else if(
                        (current_ekran.current_level >= EKRAN_TIMEOUT_AVR_UMAX_GROUP1) &&
                        (current_ekran.current_level <= EKRAN_TIMEOUT_AVR_UMAX_GROUP4)
                       )   
                {
                  int group = (current_ekran.current_level - EKRAN_TIMEOUT_AVR_UMAX_GROUP1);
                  
                  if (current_ekran.index_position == INDEX_ML_TMOAVR_UMAX_VYMK_ROB_K1)
                  {
                    if (edition_settings.timeout_avr_vymk_rob_k1_Umax[group] != current_settings.timeout_avr_vymk_rob_k1_Umax[group]) found_changes = 1;
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOAVR_UMAX_VYMK_ROB_K2)
                  {
                    if (edition_settings.timeout_avr_vymk_rob_k2_Umax[group] != current_settings.timeout_avr_vymk_rob_k2_Umax[group]) found_changes = 1;
                  }
                }
                else if(current_ekran.current_level == EKRAN_CONTROL_AVR)
                {
                  if (edition_settings.control_avr != current_settings.control_avr) found_changes = 1;
                }
                else if(
                        (current_ekran.current_level >= EKRAN_SETPOINT_CTRL_PHASE_GROUP1) &&
                        (current_ekran.current_level <= EKRAN_SETPOINT_CTRL_PHASE_GROUP4)
                       )   
                {
                  int group = (current_ekran.current_level - EKRAN_SETPOINT_CTRL_PHASE_GROUP1);
                 
                  if (current_ekran.index_position == INDEX_ML_STPCTRL_PHASE_U)
                  {
                    if (edition_settings.setpoint_ctrl_phase_U[group] != current_settings.setpoint_ctrl_phase_U[group]) found_changes = 1;
                  }
                  else if (current_ekran.index_position == INDEX_ML_STPCTRL_PHASE_PHI)
                  {
                    if (edition_settings.setpoint_ctrl_phase_phi[group] != current_settings.setpoint_ctrl_phase_phi[group]) found_changes = 1;
                  }
                  else if (current_ekran.index_position == INDEX_ML_STPCTRL_PHASE_F)
                  {
                    if (edition_settings.setpoint_ctrl_phase_f[group] != current_settings.setpoint_ctrl_phase_f[group]) found_changes = 1;
                  }
                }
                else if(
                        (current_ekran.current_level >= EKRAN_TIMEOUT_CTRL_PHASE_GROUP1) &&
                        (current_ekran.current_level <= EKRAN_TIMEOUT_CTRL_PHASE_GROUP4)
                       )   
                {
                  int group = (current_ekran.current_level - EKRAN_TIMEOUT_CTRL_PHASE_GROUP1);
                  
                  if (current_ekran.index_position == INDEX_ML_TMOCTRL_PHASE_U)
                  {
                    if (edition_settings.timeout_ctrl_phase_U[group] != current_settings.timeout_ctrl_phase_U[group]) found_changes = 1;
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOCTRL_PHASE_U_D)
                  {
                    if (edition_settings.timeout_ctrl_phase_U_d[group] != current_settings.timeout_ctrl_phase_U_d[group]) found_changes = 1;
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOCTRL_PHASE_PHI)
                  {
                    if (edition_settings.timeout_ctrl_phase_phi[group] != current_settings.timeout_ctrl_phase_phi[group]) found_changes = 1;
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOCTRL_PHASE_PHI_D)
                  {
                    if (edition_settings.timeout_ctrl_phase_phi_d[group] != current_settings.timeout_ctrl_phase_phi_d[group]) found_changes = 1;
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOCTRL_PHASE_F)
                  {
                    if (edition_settings.timeout_ctrl_phase_f[group] != current_settings.timeout_ctrl_phase_f[group]) found_changes = 1;
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOCTRL_PHASE_F_D)
                  {
                    if (edition_settings.timeout_ctrl_phase_f_d[group] != current_settings.timeout_ctrl_phase_f_d[group]) found_changes = 1;
                  }
                }
                else if(current_ekran.current_level == EKRAN_CONTROL_CTRL_PHASE)
                {
                  if (edition_settings.control_ctrl_phase != current_settings.control_ctrl_phase) found_changes = 1;
                }
                else if(current_ekran.current_level == EKRAN_TRANSFORMATOR_INFO_SETPOINT)
                {
                  if (current_ekran.index_position == INDEX_ML_TT)
                  {
                    if (edition_settings.TCurrent != current_settings.TCurrent) found_changes = 1;
                  }
                  else
                  {
                    if (edition_settings.TVoltage != current_settings.TVoltage) found_changes = 1;
                  }
                }
                else if(current_ekran.current_level == EKRAN_TRANSFORMATOR_INFO_CONTROL)
                {
                  if (edition_settings.control_transformator != current_settings.control_transformator) found_changes = 1;
                }
                else if(current_ekran.current_level == EKRAN_SETPOINT_SWITCH)
                {
                  if (current_ekran.index_position == INDEX_ML_STPInom)
                  {
                    if (edition_settings.setpoint_Inom != current_settings.setpoint_Inom) found_changes = 1;
                  }
                  else if (current_ekran.index_position == INDEX_ML_STPRKS_Inom)
                  {
                    if (edition_settings.setpoint_r_kom_st_Inom != current_settings.setpoint_r_kom_st_Inom) found_changes = 1;
                  }
                  else if (current_ekran.index_position == INDEX_ML_STPMInom_vymk)
                  {
                    if (edition_settings.setpoint_Inom_vymk != current_settings.setpoint_Inom_vymk) found_changes = 1;
                  }
                  else if (current_ekran.index_position == INDEX_ML_STPRKS_Inom_vymk)
                  {
                    if (edition_settings.setpoint_r_kom_st_Inom_vymk != current_settings.setpoint_r_kom_st_Inom_vymk) found_changes = 1;
                  }
                  else if (current_ekran.index_position == INDEX_ML_STPPOCHATKOVYJ_RESURS)
                  {
                    if (edition_settings.setpoint_pochatkovyj_resurs != current_settings.setpoint_pochatkovyj_resurs) found_changes = 1;
                  }
                  else if (current_ekran.index_position == INDEX_ML_STPKRYTYCHNYJ_RESURS)
                  {
                    if (edition_settings.setpoint_krytychnyj_resurs != current_settings.setpoint_krytychnyj_resurs) found_changes = 1;
                  }
                  else if (current_ekran.index_position == INDEX_ML_STPPOCHATKOVA_K_VYMK)
                  {
                    if (edition_settings.setpoint_pochatkova_k_vymk != current_settings.setpoint_pochatkova_k_vymk) found_changes = 1;
                  }
                }
                else if(current_ekran.current_level == EKRAN_TIMEOUT_SWITCH)
                {
                  if (current_ekran.index_position == INDEX_ML_TMOON)
                  {
                    if (edition_settings.timeout_swch_on != current_settings.timeout_swch_on) found_changes = 1;
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOOFF)
                  {
                    if (edition_settings.timeout_swch_off != current_settings.timeout_swch_off) found_changes = 1;
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOUDL_BLK_ON)
                  {
                    if (edition_settings.timeout_swch_udl_blk_on != current_settings.timeout_swch_udl_blk_on) found_changes = 1;
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOPRYVODA_VV)
                  {
                    if (edition_settings.timeout_pryvoda_VV != current_settings.timeout_pryvoda_VV) found_changes = 1;
                  }
                }
                else if(current_ekran.current_level == EKRAN_CONTROL_SWITCH)
                {
                  if (edition_settings.control_switch != current_settings.control_switch) found_changes = 1;
                }
                else if(current_ekran.current_level == EKRAN_DOPUSK_DV_UVV)
                {
                  if (edition_settings.dopusk_dv[current_ekran.index_position] != current_settings.dopusk_dv[current_ekran.index_position])
                    found_changes = 1;
                }
                else if(current_ekran.current_level == EKRAN_TYPE_INPUT_UVV)
                {
                  if (edition_settings.type_of_input != current_settings.type_of_input) found_changes = 1;
                }
                else if(current_ekran.current_level == EKRAN_TYPE_INPUT_SIGNAL_UVV)
                {
                  if (edition_settings.type_of_input_signal != current_settings.type_of_input_signal) found_changes = 1;
                }
                else if(current_ekran.current_level == EKRAN_TYPE_OUTPUT_UVV)
                {
                  if (
                      (edition_settings.type_of_output       != current_settings.type_of_output      ) ||
                      (edition_settings.type_of_output_modif != current_settings.type_of_output_modif)
                     ) found_changes = 1;
                }
                else if(current_ekran.current_level == EKRAN_TYPE_LED_UVV)
                {
                  if (edition_settings.type_of_led != current_settings.type_of_led) found_changes = 1;
                }
                else if(current_ekran.current_level == EKRAN_ADDRESS)
                {
                  unsigned int edit_value = edition_settings.address;
                  if (edit_value != current_settings.address) found_changes = 1;
                }
                else if(current_ekran.current_level == EKRAN_VIEW_SPEED_RS485)
                {
                  if (edition_settings.speed_RS485 != current_settings.speed_RS485) found_changes = 1;
                }
                else if(current_ekran.current_level == EKRAN_VIEW_PARE_RS485)
                {
                  if (edition_settings.pare_bit_RS485 != current_settings.pare_bit_RS485) found_changes = 1;
                }
                else if(current_ekran.current_level == EKRAN_VIEW_STOP_BITS_RS485)
                {
                  if (edition_settings.number_stop_bit_RS485 != current_settings.number_stop_bit_RS485) found_changes = 1;
                }
                else if(current_ekran.current_level == EKRAN_VIEW_TIMEOUT_RS485)
                {
                  if (edition_settings.time_out_1_RS485 != current_settings.time_out_1_RS485) found_changes = 1;
                }
                else if(current_ekran.current_level == EKRAN_GENERAL_PICKUPS_EL)
                {
                  if (current_ekran.index_position == INDEX_ML_NUMBER_INERATION)
                  {
                    if (edition_settings.number_iteration_el != current_settings.number_iteration_el) found_changes = 1;
                  }
//                  else if (current_ekran.index_position == INDEX_ML_NUMBER_DEFINED_FUNCTIONS)
//                  {
//                    if (edition_settings.number_defined_df != current_settings.number_defined_df) found_changes = 1;
//                  }
//                  else if (current_ekran.index_position == INDEX_ML_NUMBER_DEFINED_TRIGGERS)
//                  {
//                    if (edition_settings.number_defined_dt != current_settings.number_defined_dt) found_changes = 1;
//                  }
//                  else if (current_ekran.index_position == INDEX_ML_NUMBER_DEFINED_AND)
//                  {
//                    if (edition_settings.number_defined_and != current_settings.number_defined_and) found_changes = 1;
//                  }
//                  else if (current_ekran.index_position == INDEX_ML_NUMBER_DEFINED_OR)
//                  {
//                    if (edition_settings.number_defined_or != current_settings.number_defined_or) found_changes = 1;
//                  }
//                  else if (current_ekran.index_position == INDEX_ML_NUMBER_DEFINED_XOR)
//                  {
//                    if (edition_settings.number_defined_xor != current_settings.number_defined_xor) found_changes = 1;
//                  }
//                  else if (current_ekran.index_position == INDEX_ML_NUMBER_DEFINED_NOT)
//                  {
//                    if (edition_settings.number_defined_not != current_settings.number_defined_not) found_changes = 1;
//                  }
                }
                else if(current_ekran.current_level == EKRAN_LIST_TYPE_DF)
                {
                  if (edition_settings.type_df != current_settings.type_df) found_changes = 1;
                }
                else if((current_ekran.current_level >= EKRAN_TIMEOUT_DF1) && (current_ekran.current_level <= EKRAN_TIMEOUT_DF8))
                {
                  if (current_ekran.index_position == INDEX_ML_TMO_DF_PAUSE)
                  {
                    if (edition_settings.timeout_pause_df[current_ekran.current_level - EKRAN_TIMEOUT_DF1] != 
                        current_settings.timeout_pause_df[current_ekran.current_level - EKRAN_TIMEOUT_DF1])
                      found_changes = 1;
                  }
                  else
                  {
                    if (edition_settings.timeout_work_df[current_ekran.current_level - EKRAN_TIMEOUT_DF1] != 
                        current_settings.timeout_work_df[current_ekran.current_level - EKRAN_TIMEOUT_DF1])
                      found_changes = 1;
                  }
                }
                else if(current_ekran.current_level == EKRAN_TIMEOUT_ANALOG_REGISTRATOR)
                {
                  if (current_ekran.index_position == INDEX_ML_TMOPREFAULT)
                  {
                    if (edition_settings.prefault_number_periods != current_settings.prefault_number_periods) found_changes = 1;
                  }
                  else
                  {
                    if (edition_settings.postfault_number_periods != current_settings.postfault_number_periods) found_changes = 1;
                  }
                }
                else if(current_ekran.current_level == EKRAN_VIEW_SETTING_LANGUAGE)
                {
                  if (edition_settings.language != current_settings.language) found_changes = 1;
                }
                else if(current_ekran.current_level == EKRAN_CHOSE_EXTRA_SETTINGS)
                {
                  if (edition_settings.control_extra_settings_1 != current_settings.control_extra_settings_1) found_changes = 1;
                }

                //�������� � ������ �����������
                if (found_changes == 0) current_ekran.edition = 0;
                else current_ekran.edition = 2;

                current_ekran.cursor_on = 0;
                current_ekran.cursor_blinking_on = 0;
              }
              else if (current_ekran.edition == 2)
              {
                //���������� ����������� �����������, �� ���� �� ���������
                current_ekran.edition = 3;
                //���������� ������������ �����
                if (current_ekran.current_level == EKRAN_CONTROL_ZDZ)
                {
                  if ((edition_settings.control_zdz & ((unsigned int)(~CTR_ZDZ_MASKA))) == 0)
                  {
                    if (edition_settings.control_zdz != current_settings.control_zdz)
                    {
                      //�������, �� ���� ��������� ����� ���� ������
                      changed_settings = CHANGED_ETAP_EXECUTION;
                        
                      current_settings.control_zdz = edition_settings.control_zdz;
                      //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                      fix_change_settings(0, 1);
                    }
                    //�������� � ������ �����������
                    current_ekran.edition = 0;
                  }
                }
                else if(
                        (current_ekran.current_level >= EKRAN_TIMEOUT_APV_GROUP1) &&
                        (current_ekran.current_level <= EKRAN_TIMEOUT_APV_GROUP4)
                       )   
                {
                  int group = (current_ekran.current_level - EKRAN_TIMEOUT_APV_GROUP1);
                  
                  if (current_ekran.index_position == INDEX_ML_TMOAPV1)
                  {
                    if (check_data_setpoint(edition_settings.timeout_apv_1[group], TIMEOUT_APV1_MIN, TIMEOUT_APV1_MAX) == 1)
                    {
                      if (edition_settings.timeout_apv_1[group] != current_settings.timeout_apv_1[group])
                      {
                        //�������, �� ���� ��������� ����� ���� ������
                        changed_settings = CHANGED_ETAP_EXECUTION;
                        
                        current_settings.timeout_apv_1[group] = edition_settings.timeout_apv_1[group];
                        //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                        fix_change_settings(0, 1);
                      }
                      //�������� � ������ �����������
                      current_ekran.edition = 0;
                    }
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOAPV2)
                  {
                    if (check_data_setpoint(edition_settings.timeout_apv_2[group], TIMEOUT_APV2_MIN, TIMEOUT_APV2_MAX) == 1)
                    {
                      if (edition_settings.timeout_apv_2[group] != current_settings.timeout_apv_2[group])
                      {
                        //�������, �� ���� ��������� ����� ���� ������
                        changed_settings = CHANGED_ETAP_EXECUTION;
                        
                        current_settings.timeout_apv_2[group] = edition_settings.timeout_apv_2[group];
                        //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                        fix_change_settings(0, 1);
                      }
                      //�������� � ������ �����������
                      current_ekran.edition = 0;
                    }
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOAPV3)
                  {
                    if (check_data_setpoint(edition_settings.timeout_apv_3[group], TIMEOUT_APV3_MIN, TIMEOUT_APV3_MAX) == 1)
                    {
                      if (edition_settings.timeout_apv_3[group] != current_settings.timeout_apv_3[group])
                      {
                        //�������, �� ���� ��������� ����� ���� ������
                        changed_settings = CHANGED_ETAP_EXECUTION;
                        
                        current_settings.timeout_apv_3[group] = edition_settings.timeout_apv_3[group];
                        //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                        fix_change_settings(0, 1);
                      }
                      //�������� � ������ �����������
                      current_ekran.edition = 0;
                    }
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOAPV4)
                  {
                    if (check_data_setpoint(edition_settings.timeout_apv_4[group], TIMEOUT_APV4_MIN, TIMEOUT_APV4_MAX) == 1)
                    {
                      if (edition_settings.timeout_apv_4[group] != current_settings.timeout_apv_4[group])
                      {
                        //�������, �� ���� ��������� ����� ���� ������
                        changed_settings = CHANGED_ETAP_EXECUTION;
                        
                        current_settings.timeout_apv_4[group] = edition_settings.timeout_apv_4[group];
                        //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                        fix_change_settings(0, 1);
                      }
                      //�������� � ������ �����������
                      current_ekran.edition = 0;
                    }
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOAPV_BLOCK_VID_APV1)
                  {
                    if (check_data_setpoint(edition_settings.timeout_apv_block_vid_apv1[group], TIMEOUT_APV_BLOCK_VID_APV1_MIN, TIMEOUT_APV_BLOCK_VID_APV1_MAX) == 1)
                    {
                      if (edition_settings.timeout_apv_block_vid_apv1[group] != current_settings.timeout_apv_block_vid_apv1[group])
                      {
                        //�������, �� ���� ��������� ����� ���� ������
                        changed_settings = CHANGED_ETAP_EXECUTION;
                        
                        current_settings.timeout_apv_block_vid_apv1[group] = edition_settings.timeout_apv_block_vid_apv1[group];
                        //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                        fix_change_settings(0, 1);
                      }
                      //�������� � ������ �����������
                      current_ekran.edition = 0;
                    }
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOAPV_BLOCK_VID_APV2)
                  {
                    if (check_data_setpoint(edition_settings.timeout_apv_block_vid_apv2[group], TIMEOUT_APV_BLOCK_VID_APV2_MIN, TIMEOUT_APV_BLOCK_VID_APV2_MAX) == 1)
                    {
                      if (edition_settings.timeout_apv_block_vid_apv2[group] != current_settings.timeout_apv_block_vid_apv2[group])
                      {
                        //�������, �� ���� ��������� ����� ���� ������
                        changed_settings = CHANGED_ETAP_EXECUTION;
                        
                        current_settings.timeout_apv_block_vid_apv2[group] = edition_settings.timeout_apv_block_vid_apv2[group];
                        //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                        fix_change_settings(0, 1);
                      }
                      //�������� � ������ �����������
                      current_ekran.edition = 0;
                    }
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOAPV_BLOCK_VID_APV3)
                  {
                    if (check_data_setpoint(edition_settings.timeout_apv_block_vid_apv3[group], TIMEOUT_APV_BLOCK_VID_APV3_MIN, TIMEOUT_APV_BLOCK_VID_APV3_MAX) == 1)
                    {
                      if (edition_settings.timeout_apv_block_vid_apv3[group] != current_settings.timeout_apv_block_vid_apv3[group])
                      {
                        //�������, �� ���� ��������� ����� ���� ������
                        changed_settings = CHANGED_ETAP_EXECUTION;
                        
                        current_settings.timeout_apv_block_vid_apv3[group] = edition_settings.timeout_apv_block_vid_apv3[group];
                        //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                        fix_change_settings(0, 1);
                      }
                      //�������� � ������ �����������
                      current_ekran.edition = 0;
                    }
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOAPV_BLOCK_VID_APV4)
                  {
                    if (check_data_setpoint(edition_settings.timeout_apv_block_vid_apv4[group], TIMEOUT_APV_BLOCK_VID_APV4_MIN, TIMEOUT_APV_BLOCK_VID_APV4_MAX) == 1)
                    {
                      if (edition_settings.timeout_apv_block_vid_apv4[group] != current_settings.timeout_apv_block_vid_apv4[group])
                      {
                        //�������, �� ���� ��������� ����� ���� ������
                        changed_settings = CHANGED_ETAP_EXECUTION;
                        
                        current_settings.timeout_apv_block_vid_apv4[group] = edition_settings.timeout_apv_block_vid_apv4[group];
                        //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                        fix_change_settings(0, 1);
                      }
                      //�������� � ������ �����������
                      current_ekran.edition = 0;
                    }
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOAPV_BLOCK_VID_VV)
                  {
                    if (check_data_setpoint(edition_settings.timeout_apv_block_vid_VV[group], TIMEOUT_APV_BLOCK_VID_VV_MIN, TIMEOUT_APV_BLOCK_VID_VV_MAX) == 1)
                    {
                      if (edition_settings.timeout_apv_block_vid_VV[group] != current_settings.timeout_apv_block_vid_VV[group])
                      {
                        //�������, �� ���� ��������� ����� ���� ������
                        changed_settings = CHANGED_ETAP_EXECUTION;
                        
                        current_settings.timeout_apv_block_vid_VV[group] = edition_settings.timeout_apv_block_vid_VV[group];
                        //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                        fix_change_settings(0, 1);
                      }
                      //�������� � ������ �����������
                      current_ekran.edition = 0;
                    }
                  }
                }
                else if(current_ekran.current_level == EKRAN_CONTROL_APV)
                {
                  if ((edition_settings.control_apv  & ((unsigned int)(~CTR_APV_MASKA))) == 0)
                  {
                    if (edition_settings.control_apv != current_settings.control_apv)
                    {
                      //�������, �� ���� ��������� ����� ���� ������
                      changed_settings = CHANGED_ETAP_EXECUTION;
                        
                      current_settings.control_apv = edition_settings.control_apv;
                      //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                      fix_change_settings(0, 1);
                    }
                    //�������� � ������ �����������
                    current_ekran.edition = 0;
                  }
                }
                else if(
                        (current_ekran.current_level >= EKRAN_SETPOINT_UROV_GROUP1) &&
                        (current_ekran.current_level <= EKRAN_SETPOINT_UROV_GROUP4)
                       )   
                {
                  int group = (current_ekran.current_level - EKRAN_SETPOINT_UROV_GROUP1);
                  
                  if (check_data_setpoint(edition_settings.setpoint_urov[group], SETPOINT_UROV_MIN, SETPOINT_UROV_MAX) == 1)
                  {
                    if (edition_settings.setpoint_urov[group] != current_settings.setpoint_urov[group])
                    {
                      //�������, �� ���� ��������� ����� ���� ������
                      changed_settings = CHANGED_ETAP_EXECUTION;
                        
                      current_settings.setpoint_urov[group] = edition_settings.setpoint_urov[group];
                      //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                      fix_change_settings(0, 1);
                    }
                    //�������� � ������ �����������
                    current_ekran.edition = 0;
                  }
                }
                else if(
                        (current_ekran.current_level >= EKRAN_TIMEOUT_UROV_GROUP1) &&
                        (current_ekran.current_level <= EKRAN_TIMEOUT_UROV_GROUP4)
                       )
                {
                  int group = (current_ekran.current_level - EKRAN_TIMEOUT_UROV_GROUP1);
                  
                  if (current_ekran.index_position == INDEX_ML_TMOUROV1)
                  {
                    if (check_data_setpoint(edition_settings.timeout_urov_1[group], TIMEOUT_UROV1_MIN, TIMEOUT_UROV1_MAX) == 1)
                    {
                      if (edition_settings.timeout_urov_1[group] != current_settings.timeout_urov_1[group])
                      {
                        //�������, �� ���� ��������� ����� ���� ������
                        changed_settings = CHANGED_ETAP_EXECUTION;
                        
                        current_settings.timeout_urov_1[group] = edition_settings.timeout_urov_1[group];
                        //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                        fix_change_settings(0, 1);
                      }
                      //�������� � ������ �����������
                      current_ekran.edition = 0;
                    }
                  }
                  else
                  {
                    if (check_data_setpoint(edition_settings.timeout_urov_2[group], TIMEOUT_UROV2_MIN, TIMEOUT_UROV2_MAX) == 1)
                    {
                      if (edition_settings.timeout_urov_2[group] != current_settings.timeout_urov_2[group])
                      {
                        //�������, �� ���� ��������� ����� ���� ������
                        changed_settings = CHANGED_ETAP_EXECUTION;
                        
                        current_settings.timeout_urov_2[group] = edition_settings.timeout_urov_2[group];
                        //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                        fix_change_settings(0, 1);
                      }
                      //�������� � ������ �����������
                      current_ekran.edition = 0;
                    }
                  }
                }
                else if(current_ekran.current_level == EKRAN_CONTROL_UROV)
                {
                  if ((edition_settings.control_urov  & ((unsigned int)(~CTR_UROV_MASKA))) == 0)
                  {
                    if (edition_settings.control_urov != current_settings.control_urov)
                    {
                      //�������, �� ���� ��������� ����� ���� ������
                      changed_settings = CHANGED_ETAP_EXECUTION;
                        
                      current_settings.control_urov = edition_settings.control_urov;
                      //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                      fix_change_settings(0, 1);
                    }
                    //�������� � ������ �����������
                    current_ekran.edition = 0;
                  }
                }
                else if(
                        (current_ekran.current_level >= EKRAN_SETPOINT_ZOP_GROUP1) &&
                        (current_ekran.current_level <= EKRAN_SETPOINT_ZOP_GROUP4)
                       )   
                {
                  int group = (current_ekran.current_level - EKRAN_SETPOINT_ZOP_GROUP1);
                  
                  if (check_data_setpoint(edition_settings.setpoint_zop[group], SETPOINT_ZOP_MIN, SETPOINT_ZOP_MAX) == 1)
                  {
                    if (edition_settings.setpoint_zop[group] != current_settings.setpoint_zop[group])
                    {
                      //�������, �� ���� ��������� ����� ���� ������
                      changed_settings = CHANGED_ETAP_EXECUTION;
                        
                      current_settings.setpoint_zop[group] = edition_settings.setpoint_zop[group];
                      //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                      fix_change_settings(0, 1);
                    }
                    //�������� � ������ �����������
                    current_ekran.edition = 0;
                  }
                }
                else if(
                        (current_ekran.current_level >= EKRAN_TIMEOUT_ZOP_GROUP1) &&
                        (current_ekran.current_level <= EKRAN_TIMEOUT_ZOP_GROUP4)
                       )   
                {
                  int group = (current_ekran.current_level - EKRAN_TIMEOUT_ZOP_GROUP1);
                  
                  if (check_data_setpoint(edition_settings.timeout_zop[group], TIMEOUT_ZOP_MIN, TIMEOUT_ZOP_MAX) == 1)
                  {
                    if (edition_settings.timeout_zop[group] != current_settings.timeout_zop[group])
                    {
                      //�������, �� ���� ��������� ����� ���� ������
                      changed_settings = CHANGED_ETAP_EXECUTION;
                        
                      current_settings.timeout_zop[group] = edition_settings.timeout_zop[group];
                      //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                      fix_change_settings(0, 1);
                    }
                    //�������� � ������ �����������
                    current_ekran.edition = 0;
                  }
                }
                else if(current_ekran.current_level == EKRAN_CONTROL_ZOP)
                {
                  if ((edition_settings.control_zop  & ((unsigned int)(~CTR_ZOP_MASKA))) == 0)
                  {
                    if (edition_settings.control_zop != current_settings.control_zop)
                    {
                      //�������, �� ���� ��������� ����� ���� ������
                      changed_settings = CHANGED_ETAP_EXECUTION;
                        
                      current_settings.control_zop = edition_settings.control_zop;
                      //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                      fix_change_settings(0, 1);
                    }
                    //�������� � ������ �����������
                    current_ekran.edition = 0;
                  }
                }
                else if(
                        (current_ekran.current_level >= EKRAN_SETPOINT_UMIN_GROUP1) &&
                        (current_ekran.current_level <= EKRAN_SETPOINT_UMIN_GROUP4)
                       )   
                {
                  int group = (current_ekran.current_level - EKRAN_SETPOINT_UMIN_GROUP1);
                  
                  if (current_ekran.index_position == INDEX_ML_STPUMIN1)
                  {
                    if (check_data_setpoint(edition_settings.setpoint_Umin1[group], SETPOINT_UMIN1_MIN, SETPOINT_UMIN1_MAX) == 1)
                    {
                      if (edition_settings.setpoint_Umin1[group] != current_settings.setpoint_Umin1[group])
                      {
                        //�������, �� ���� ��������� ����� ���� ������
                        changed_settings = CHANGED_ETAP_EXECUTION;
                        
                        current_settings.setpoint_Umin1[group] = edition_settings.setpoint_Umin1[group];
                        //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                        fix_change_settings(0, 1);
                      }
                      //�������� � ������ �����������
                      current_ekran.edition = 0;
                    }
                  }
                  else if (current_ekran.index_position == INDEX_ML_STPUMIN1_IBLK)
                  {
                    if (check_data_setpoint(edition_settings.setpoint_Umin1_Iblk[group], SETPOINT_UMIN1_IBLK_MIN, SETPOINT_UMIN1_IBLK_MAX) == 1)
                    {
                      if (edition_settings.setpoint_Umin1_Iblk[group] != current_settings.setpoint_Umin1_Iblk[group])
                      {
                        //�������, �� ���� ��������� ����� ���� ������
                        changed_settings = CHANGED_ETAP_EXECUTION;
                        
                        current_settings.setpoint_Umin1_Iblk[group] = edition_settings.setpoint_Umin1_Iblk[group];
                        //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                        fix_change_settings(0, 1);
                      }
                      //�������� � ������ �����������
                      current_ekran.edition = 0;
                    }
                  }
                  else if (current_ekran.index_position == INDEX_ML_STPUMIN2)
                  {
                    if (check_data_setpoint(edition_settings.setpoint_Umin2[group], SETPOINT_UMIN2_MIN, SETPOINT_UMIN2_MAX) == 1)
                    {
                      if (edition_settings.setpoint_Umin2[group] != current_settings.setpoint_Umin2[group])
                      {
                        //�������, �� ���� ��������� ����� ���� ������
                        changed_settings = CHANGED_ETAP_EXECUTION;
                        
                        current_settings.setpoint_Umin2[group] = edition_settings.setpoint_Umin2[group];
                        //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                        fix_change_settings(0, 1);
                      }
                      //�������� � ������ �����������
                      current_ekran.edition = 0;
                    }
                  }
                  else if (current_ekran.index_position == INDEX_ML_STPUMIN2_IBLK)
                  {
                    if (check_data_setpoint(edition_settings.setpoint_Umin2_Iblk[group], SETPOINT_UMIN2_IBLK_MIN, SETPOINT_UMIN2_IBLK_MAX) == 1)
                    {
                      if (edition_settings.setpoint_Umin2_Iblk[group] != current_settings.setpoint_Umin2_Iblk[group])
                      {
                        //�������, �� ���� ��������� ����� ���� ������
                        changed_settings = CHANGED_ETAP_EXECUTION;
                        
                        current_settings.setpoint_Umin2_Iblk[group] = edition_settings.setpoint_Umin2_Iblk[group];
                        //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                        fix_change_settings(0, 1);
                      }
                      //�������� � ������ �����������
                      current_ekran.edition = 0;
                    }
                  }
                }
                else if(
                        (current_ekran.current_level >= EKRAN_TIMEOUT_UMIN_GROUP1)&&
                        (current_ekran.current_level <= EKRAN_TIMEOUT_UMIN_GROUP4)
                       )   
                {
                  int group = (current_ekran.current_level - EKRAN_TIMEOUT_UMIN_GROUP1);
                  
                  if (current_ekran.index_position == INDEX_ML_TMOUMIN1)
                  {
                    if (check_data_setpoint(edition_settings.timeout_Umin1[group], TIMEOUT_UMIN1_MIN, TIMEOUT_UMIN1_MAX) == 1)
                    {
                      if (edition_settings.timeout_Umin1[group] != current_settings.timeout_Umin1[group])
                      {
                        //�������, �� ���� ��������� ����� ���� ������
                        changed_settings = CHANGED_ETAP_EXECUTION;
                        
                        current_settings.timeout_Umin1[group] = edition_settings.timeout_Umin1[group];
                        //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                        fix_change_settings(0, 1);
                      }
                      //�������� � ������ �����������
                      current_ekran.edition = 0;
                    }
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOUMIN2)
                  {
                    if (check_data_setpoint(edition_settings.timeout_Umin2[group], TIMEOUT_UMIN2_MIN, TIMEOUT_UMIN2_MAX) == 1)
                    {
                      if (edition_settings.timeout_Umin2[group] != current_settings.timeout_Umin2[group])
                      {
                        //�������, �� ���� ��������� ����� ���� ������
                        changed_settings = CHANGED_ETAP_EXECUTION;
                        
                        current_settings.timeout_Umin2[group] = edition_settings.timeout_Umin2[group];
                        //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                        fix_change_settings(0, 1);
                      }
                      //�������� � ������ �����������
                      current_ekran.edition = 0;
                    }
                  }
                }
                else if(current_ekran.current_level == EKRAN_CONTROL_UMIN)
                {
                  if ((edition_settings.control_Umin  & ((unsigned int)(~CTR_UMIN_MASKA))) == 0)
                  {
                    if (edition_settings.control_Umin != current_settings.control_Umin)
                    {
                      //�������, �� ���� ��������� ����� ���� ������
                      changed_settings = CHANGED_ETAP_EXECUTION;
                        
                      current_settings.control_Umin = edition_settings.control_Umin;
                      //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                      fix_change_settings(0, 1);
                    }
                    //�������� � ������ �����������
                    current_ekran.edition = 0;
                  }
                }
                else if(
                        (current_ekran.current_level >= EKRAN_SETPOINT_UMAX_GROUP1) &&
                        (current_ekran.current_level <= EKRAN_SETPOINT_UMAX_GROUP4)
                       )   
                {
                  int group = (current_ekran.current_level - EKRAN_SETPOINT_UMAX_GROUP1);
                  
                  if (current_ekran.index_position == INDEX_ML_STPUMAX1)
                  {
                    if (check_data_setpoint(edition_settings.setpoint_Umax1[group], SETPOINT_UMAX1_MIN, SETPOINT_UMAX1_MAX) == 1)
                    {
                      if (edition_settings.setpoint_Umax1[group] != current_settings.setpoint_Umax1[group])
                      {
                        //�������, �� ���� ��������� ����� ���� ������
                        changed_settings = CHANGED_ETAP_EXECUTION;
                        
                        current_settings.setpoint_Umax1[group] = edition_settings.setpoint_Umax1[group];
                        //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                        fix_change_settings(0, 1);
                      }
                      //�������� � ������ �����������
                      current_ekran.edition = 0;
                    }
                  }
                  else if (current_ekran.index_position == INDEX_ML_STPUMAX2)
                  {
                    if (check_data_setpoint(edition_settings.setpoint_Umax2[group], SETPOINT_UMAX2_MIN, SETPOINT_UMAX2_MAX) == 1)
                    {
                      if (edition_settings.setpoint_Umax2[group] != current_settings.setpoint_Umax2[group])
                      {
                        //�������, �� ���� ��������� ����� ���� ������
                        changed_settings = CHANGED_ETAP_EXECUTION;
                        
                        current_settings.setpoint_Umax2[group] = edition_settings.setpoint_Umax2[group];
                        //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                        fix_change_settings(0, 1);
                      }
                      //�������� � ������ �����������
                      current_ekran.edition = 0;
                    }
                  }
                }
                else if(
                        (current_ekran.current_level >= EKRAN_TIMEOUT_UMAX_GROUP1)&&
                        (current_ekran.current_level <= EKRAN_TIMEOUT_UMAX_GROUP4)
                       )   
                {
                  int group = (current_ekran.current_level - EKRAN_TIMEOUT_UMAX_GROUP1);
                  
                  if (current_ekran.index_position == INDEX_ML_TMOUMAX1)
                  {
                    if (check_data_setpoint(edition_settings.timeout_Umax1[group], TIMEOUT_UMAX1_MIN, TIMEOUT_UMAX1_MAX) == 1)
                    {
                      if (edition_settings.timeout_Umax1[group] != current_settings.timeout_Umax1[group])
                      {
                        //�������, �� ���� ��������� ����� ���� ������
                        changed_settings = CHANGED_ETAP_EXECUTION;
                        
                        current_settings.timeout_Umax1[group] = edition_settings.timeout_Umax1[group];
                        //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                        fix_change_settings(0, 1);
                      }
                      //�������� � ������ �����������
                      current_ekran.edition = 0;
                    }
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOUMAX2)
                  {
                    if (check_data_setpoint(edition_settings.timeout_Umax2[group], TIMEOUT_UMAX2_MIN, TIMEOUT_UMAX2_MAX) == 1)
                    {
                      if (edition_settings.timeout_Umax2[group] != current_settings.timeout_Umax2[group])
                      {
                        //�������, �� ���� ��������� ����� ���� ������
                        changed_settings = CHANGED_ETAP_EXECUTION;
                        
                        current_settings.timeout_Umax2[group] = edition_settings.timeout_Umax2[group];
                        //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                        fix_change_settings(0, 1);
                      }
                      //�������� � ������ �����������
                      current_ekran.edition = 0;
                    }
                  }
                }
                else if(current_ekran.current_level == EKRAN_CONTROL_UMAX)
                {
                  if ((edition_settings.control_Umax  & ((unsigned int)(~CTR_UMAX_MASKA))) == 0)
                  {
                    if (edition_settings.control_Umax != current_settings.control_Umax)
                    {
                      //�������, �� ���� ��������� ����� ���� ������
                      changed_settings = CHANGED_ETAP_EXECUTION;
                        
                      current_settings.control_Umax = edition_settings.control_Umax;
                      //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                      fix_change_settings(0, 1);
                    }
                    //�������� � ������ �����������
                    current_ekran.edition = 0;
                  }
                }
                else if(
                        (current_ekran.current_level >= EKRAN_SETPOINT_AVR_UMIN_GROUP1) &&
                        (current_ekran.current_level <= EKRAN_SETPOINT_AVR_UMIN_GROUP4)
                       )   
                {
                  int group = (current_ekran.current_level - EKRAN_SETPOINT_AVR_UMIN_GROUP1);
                  
                  if (current_ekran.index_position == INDEX_ML_STPAVR_TN1_U1_UMIN)
                  {
                    if (check_data_setpoint(edition_settings.setpoint_avr_tn1_U1_Umin[group], SETPOINT_AVR_TN1_U1_UMIN_MIN, SETPOINT_AVR_TN1_U1_UMIN_MAX) == 1)
                    {
                      if (edition_settings.setpoint_avr_tn1_U1_Umin[group] != current_settings.setpoint_avr_tn1_U1_Umin[group])
                      {
                        //�������, �� ���� ��������� ����� ���� ������
                        changed_settings = CHANGED_ETAP_EXECUTION;
                        
                        current_settings.setpoint_avr_tn1_U1_Umin[group] = edition_settings.setpoint_avr_tn1_U1_Umin[group];
                        //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                        fix_change_settings(0, 1);
                      }
                      //�������� � ������ �����������
                      current_ekran.edition = 0;
                    }
                  }
                  else if (current_ekran.index_position == INDEX_ML_STPAVR_TN1_U2_LOW_WORK)
                  {
                    if (check_data_setpoint(edition_settings.setpoint_avr_tn1_U2_low_work[group], SETPOINT_AVR_TN1_U2_LOW_WORK_MIN, SETPOINT_AVR_TN1_U2_LOW_WORK_MAX) == 1)
                    {
                      if (edition_settings.setpoint_avr_tn1_U2_low_work[group] != current_settings.setpoint_avr_tn1_U2_low_work[group])
                      {
                        //�������, �� ���� ��������� ����� ���� ������
                        changed_settings = CHANGED_ETAP_EXECUTION;
                        
                        current_settings.setpoint_avr_tn1_U2_low_work[group] = edition_settings.setpoint_avr_tn1_U2_low_work[group];
                        //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                        fix_change_settings(0, 1);
                      }
                      //�������� � ������ �����������
                      current_ekran.edition = 0;
                    }
                  }
                  else if (current_ekran.index_position == INDEX_ML_STPAVR_TN2_U2_UMIN)
                  {
                    if (check_data_setpoint(edition_settings.setpoint_avr_tn2_U2_Umin[group], SETPOINT_AVR_TN2_U2_UMIN_MIN, SETPOINT_AVR_TN2_U2_UMIN_MAX) == 1)
                    {
                      if (edition_settings.setpoint_avr_tn2_U2_Umin[group] != current_settings.setpoint_avr_tn2_U2_Umin[group])
                      {
                        //�������, �� ���� ��������� ����� ���� ������
                        changed_settings = CHANGED_ETAP_EXECUTION;
                        
                        current_settings.setpoint_avr_tn2_U2_Umin[group] = edition_settings.setpoint_avr_tn2_U2_Umin[group];
                        //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                        fix_change_settings(0, 1);
                      }
                      //�������� � ������ �����������
                      current_ekran.edition = 0;
                    }
                  }
                  else if (current_ekran.index_position == INDEX_ML_STPAVR_TN2_U1_LOW_WORK)
                  {
                    if (check_data_setpoint(edition_settings.setpoint_avr_tn2_U1_low_work[group], SETPOINT_AVR1_TN2_U1_LOW_WORK_MIN, SETPOINT_AVR1_TN2_U1_LOW_WORK_MAX) == 1)
                    {
                      if (edition_settings.setpoint_avr_tn2_U1_low_work[group] != current_settings.setpoint_avr_tn2_U1_low_work[group])
                      {
                        //�������, �� ���� ��������� ����� ���� ������
                        changed_settings = CHANGED_ETAP_EXECUTION;
                        
                        current_settings.setpoint_avr_tn2_U1_low_work[group] = edition_settings.setpoint_avr_tn2_U1_low_work[group];
                        //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                        fix_change_settings(0, 1);
                      }
                      //�������� � ������ �����������
                      current_ekran.edition = 0;
                    }
                  }
                }
                else if(
                        (current_ekran.current_level >= EKRAN_SETPOINT_AVR_UMAX_GROUP1) &&
                        (current_ekran.current_level <= EKRAN_SETPOINT_AVR_UMAX_GROUP4)
                       )   
                {
                  int group = (current_ekran.current_level - EKRAN_SETPOINT_AVR_UMAX_GROUP1);
                  
                  if (current_ekran.index_position == INDEX_ML_STPAVR_TN1_U1_UMAX)
                  {
                    if (check_data_setpoint(edition_settings.setpoint_avr_tn1_U1_Umax[group], SETPOINT_AVR_TN1_U1_UMAX_MIN, SETPOINT_AVR_TN1_U1_UMAX_MAX) == 1)
                    {
                      if (edition_settings.setpoint_avr_tn1_U1_Umax[group] != current_settings.setpoint_avr_tn1_U1_Umax[group])
                      {
                        //�������, �� ���� ��������� ����� ���� ������
                        changed_settings = CHANGED_ETAP_EXECUTION;
                        
                        current_settings.setpoint_avr_tn1_U1_Umax[group] = edition_settings.setpoint_avr_tn1_U1_Umax[group];
                        //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                        fix_change_settings(0, 1);
                      }
                      //�������� � ������ �����������
                      current_ekran.edition = 0;
                    }
                  }
                  else if (current_ekran.index_position == INDEX_ML_STPAVR_TN1_U2_HIGH_WORK)
                  {
                    if (check_data_setpoint(edition_settings.setpoint_avr_tn1_U2_high_work[group], SETPOINT_AVR1_TN1_U2_HIGH_WORK_MIN, SETPOINT_AVR1_TN1_U2_HIGH_WORK_MAX) == 1)
                    {
                      if (edition_settings.setpoint_avr_tn1_U2_high_work[group] != current_settings.setpoint_avr_tn1_U2_high_work[group])
                      {
                        //�������, �� ���� ��������� ����� ���� ������
                        changed_settings = CHANGED_ETAP_EXECUTION;
                        
                        current_settings.setpoint_avr_tn1_U2_high_work[group] = edition_settings.setpoint_avr_tn1_U2_high_work[group];
                        //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                        fix_change_settings(0, 1);
                      }
                      //�������� � ������ �����������
                      current_ekran.edition = 0;
                    }
                  }
                  else if (current_ekran.index_position == INDEX_ML_STPAVR_TN2_U2_UMAX)
                  {
                    if (check_data_setpoint(edition_settings.setpoint_avr_tn2_U2_Umax[group], SETPOINT_AVR_TN2_U2_UMAX_MIN, SETPOINT_AVR_TN2_U2_UMAX_MAX) == 1)
                    {
                      if (edition_settings.setpoint_avr_tn2_U2_Umax[group] != current_settings.setpoint_avr_tn2_U2_Umax[group])
                      {
                        //�������, �� ���� ��������� ����� ���� ������
                        changed_settings = CHANGED_ETAP_EXECUTION;
                        
                        current_settings.setpoint_avr_tn2_U2_Umax[group] = edition_settings.setpoint_avr_tn2_U2_Umax[group];
                        //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                        fix_change_settings(0, 1);
                      }
                      //�������� � ������ �����������
                      current_ekran.edition = 0;
                    }
                  }
                  else if (current_ekran.index_position == INDEX_ML_STPAVR_TN2_U1_HIGH_WORK)
                  {
                    if (check_data_setpoint(edition_settings.setpoint_avr_tn2_U1_high_work[group], SETPOINT_AVR1_TN2_U1_HIGH_WORK_MIN, SETPOINT_AVR1_TN2_U1_HIGH_WORK_MAX) == 1)
                    {
                      if (edition_settings.setpoint_avr_tn2_U1_high_work[group] != current_settings.setpoint_avr_tn2_U1_high_work[group])
                      {
                        //�������, �� ���� ��������� ����� ���� ������
                        changed_settings = CHANGED_ETAP_EXECUTION;
                        
                        current_settings.setpoint_avr_tn2_U1_high_work[group] = edition_settings.setpoint_avr_tn2_U1_high_work[group];
                        //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                        fix_change_settings(0, 1);
                      }
                      //�������� � ������ �����������
                      current_ekran.edition = 0;
                    }
                  }
                }
                else if(
                        (current_ekran.current_level >= EKRAN_TIMEOUT_AVR_GENERAL_GROUP1)&&
                        (current_ekran.current_level <= EKRAN_TIMEOUT_AVR_GENERAL_GROUP4)
                       )   
                {
                  int group = (current_ekran.current_level - EKRAN_TIMEOUT_AVR_GENERAL_GROUP1);
                  
                  if (current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_BLK_K1)
                  {
                    if (check_data_setpoint(edition_settings.timeout_avr_blk_k1[group], TIMEOUT_AVR_GENERAL_BLK_K1_MIN, TIMEOUT_AVR_GENERAL_BLK_K1_MAX) == 1)
                    {
                      if (edition_settings.timeout_avr_blk_k1[group] != current_settings.timeout_avr_blk_k1[group])
                      {
                        //�������, �� ���� ��������� ����� ���� ������
                        changed_settings = CHANGED_ETAP_EXECUTION;
                        
                        current_settings.timeout_avr_blk_k1[group] = edition_settings.timeout_avr_blk_k1[group];
                        //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                        fix_change_settings(0, 1);
                      }
                      //�������� � ������ �����������
                      current_ekran.edition = 0;
                    }
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_PUSK_K1)
                  {
                    if (check_data_setpoint(edition_settings.timeout_avr_pusk_k1[group], TIMEOUT_AVR_GENERAL_PUSK_K1_MIN, TIMEOUT_AVR_GENERAL_PUSK_K1_MAX) == 1)
                    {
                      if (edition_settings.timeout_avr_pusk_k1[group] != current_settings.timeout_avr_pusk_k1[group])
                      {
                        //�������, �� ���� ��������� ����� ���� ������
                        changed_settings = CHANGED_ETAP_EXECUTION;
                        
                        current_settings.timeout_avr_pusk_k1[group] = edition_settings.timeout_avr_pusk_k1[group];
                        //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                        fix_change_settings(0, 1);
                      }
                      //�������� � ������ �����������
                      current_ekran.edition = 0;
                    }
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_D_DIJI_K1)
                  {
                    if (check_data_setpoint(edition_settings.timeout_avr_d_diji_k1[group], TIMEOUT_AVR_GENERAL_D_DIJI_K1_MIN, TIMEOUT_AVR_GENERAL_D_DIJI_K1_MAX) == 1)
                    {
                      if (edition_settings.timeout_avr_d_diji_k1[group] != current_settings.timeout_avr_d_diji_k1[group])
                      {
                        //�������, �� ���� ��������� ����� ���� ������
                        changed_settings = CHANGED_ETAP_EXECUTION;
                        
                        current_settings.timeout_avr_d_diji_k1[group] = edition_settings.timeout_avr_d_diji_k1[group];
                        //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                        fix_change_settings(0, 1);
                      }
                      //�������� � ������ �����������
                      current_ekran.edition = 0;
                    }
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_VVIMK_REZ_K1)
                  {
                    if (check_data_setpoint(edition_settings.timeout_avr_vvimk_rez_k1[group], TIMEOUT_AVR_GENERAL_VVIMK_REZ_K1_MIN, TIMEOUT_AVR_GENERAL_VVIMK_REZ_K1_MAX) == 1)
                    {
                      if (edition_settings.timeout_avr_vvimk_rez_k1[group] != current_settings.timeout_avr_vvimk_rez_k1[group])
                      {
                        //�������, �� ���� ��������� ����� ���� ������
                        changed_settings = CHANGED_ETAP_EXECUTION;
                        
                        current_settings.timeout_avr_vvimk_rez_k1[group] = edition_settings.timeout_avr_vvimk_rez_k1[group];
                        //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                        fix_change_settings(0, 1);
                      }
                      //�������� � ������ �����������
                      current_ekran.edition = 0;
                    }
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_VVIMK_K1)
                  {
                    if (check_data_setpoint(edition_settings.timeout_avr_vvimk_k1[group], TIMEOUT_AVR_GENERAL_VVIMK_K1_MIN, TIMEOUT_AVR_GENERAL_VVIMK_K1_MAX) == 1)
                    {
                      if (edition_settings.timeout_avr_vvimk_k1[group] != current_settings.timeout_avr_vvimk_k1[group])
                      {
                        //�������, �� ���� ��������� ����� ���� ������
                        changed_settings = CHANGED_ETAP_EXECUTION;
                        
                        current_settings.timeout_avr_vvimk_k1[group] = edition_settings.timeout_avr_vvimk_k1[group];
                        //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                        fix_change_settings(0, 1);
                      }
                      //�������� � ������ �����������
                      current_ekran.edition = 0;
                    }
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_VYMK_K1)
                  {
                    if (check_data_setpoint(edition_settings.timeout_avr_vymk_k1[group], TIMEOUT_AVR_GENERAL_VYMK_K1_MIN, TIMEOUT_AVR_GENERAL_VYMK_K1_MAX) == 1)
                    {
                      if (edition_settings.timeout_avr_vymk_k1[group] != current_settings.timeout_avr_vymk_k1[group])
                      {
                        //�������, �� ���� ��������� ����� ���� ������
                        changed_settings = CHANGED_ETAP_EXECUTION;
                        
                        current_settings.timeout_avr_vymk_k1[group] = edition_settings.timeout_avr_vymk_k1[group];
                        //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                        fix_change_settings(0, 1);
                      }
                      //�������� � ������ �����������
                      current_ekran.edition = 0;
                    }
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_BLK_K2)
                  {
                    if (check_data_setpoint(edition_settings.timeout_avr_blk_k2[group], TIMEOUT_AVR_GENERAL_BLK_K2_MIN, TIMEOUT_AVR_GENERAL_BLK_K2_MAX) == 1)
                    {
                      if (edition_settings.timeout_avr_blk_k2[group] != current_settings.timeout_avr_blk_k2[group])
                      {
                        //�������, �� ���� ��������� ����� ���� ������
                        changed_settings = CHANGED_ETAP_EXECUTION;
                        
                        current_settings.timeout_avr_blk_k2[group] = edition_settings.timeout_avr_blk_k2[group];
                        //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                        fix_change_settings(0, 1);
                      }
                      //�������� � ������ �����������
                      current_ekran.edition = 0;
                    }
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_PUSK_K2)
                  {
                    if (check_data_setpoint(edition_settings.timeout_avr_pusk_k2[group], TIMEOUT_AVR_GENERAL_PUSK_K2_MIN, TIMEOUT_AVR_GENERAL_PUSK_K2_MAX) == 1)
                    {
                      if (edition_settings.timeout_avr_pusk_k2[group] != current_settings.timeout_avr_pusk_k2[group])
                      {
                        //�������, �� ���� ��������� ����� ���� ������
                        changed_settings = CHANGED_ETAP_EXECUTION;
                        
                        current_settings.timeout_avr_pusk_k2[group] = edition_settings.timeout_avr_pusk_k2[group];
                        //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                        fix_change_settings(0, 1);
                      }
                      //�������� � ������ �����������
                      current_ekran.edition = 0;
                    }
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_D_DIJI_K2)
                  {
                    if (check_data_setpoint(edition_settings.timeout_avr_d_diji_k2[group], TIMEOUT_AVR_GENERAL_D_DIJI_K2_MIN, TIMEOUT_AVR_GENERAL_D_DIJI_K2_MAX) == 1)
                    {
                      if (edition_settings.timeout_avr_d_diji_k2[group] != current_settings.timeout_avr_d_diji_k2[group])
                      {
                        //�������, �� ���� ��������� ����� ���� ������
                        changed_settings = CHANGED_ETAP_EXECUTION;
                        
                        current_settings.timeout_avr_d_diji_k2[group] = edition_settings.timeout_avr_d_diji_k2[group];
                        //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                        fix_change_settings(0, 1);
                      }
                      //�������� � ������ �����������
                      current_ekran.edition = 0;
                    }
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_VVIMK_REZ_K2)
                  {
                    if (check_data_setpoint(edition_settings.timeout_avr_vvimk_rez_k2[group], TIMEOUT_AVR_GENERAL_VVIMK_REZ_K2_MIN, TIMEOUT_AVR_GENERAL_VVIMK_REZ_K2_MAX) == 1)
                    {
                      if (edition_settings.timeout_avr_vvimk_rez_k2[group] != current_settings.timeout_avr_vvimk_rez_k2[group])
                      {
                        //�������, �� ���� ��������� ����� ���� ������
                        changed_settings = CHANGED_ETAP_EXECUTION;
                        
                        current_settings.timeout_avr_vvimk_rez_k2[group] = edition_settings.timeout_avr_vvimk_rez_k2[group];
                        //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                        fix_change_settings(0, 1);
                      }
                      //�������� � ������ �����������
                      current_ekran.edition = 0;
                    }
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_VVIMK_K2)
                  {
                    if (check_data_setpoint(edition_settings.timeout_avr_vvimk_k2[group], TIMEOUT_AVR_GENERAL_VVIMK_K2_MIN, TIMEOUT_AVR_GENERAL_VVIMK_K2_MAX) == 1)
                    {
                      if (edition_settings.timeout_avr_vvimk_k2[group] != current_settings.timeout_avr_vvimk_k2[group])
                      {
                        //�������, �� ���� ��������� ����� ���� ������
                        changed_settings = CHANGED_ETAP_EXECUTION;
                        
                        current_settings.timeout_avr_vvimk_k2[group] = edition_settings.timeout_avr_vvimk_k2[group];
                        //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                        fix_change_settings(0, 1);
                      }
                      //�������� � ������ �����������
                      current_ekran.edition = 0;
                    }
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_VYMK_K2)
                  {
                    if (check_data_setpoint(edition_settings.timeout_avr_vymk_k2[group], TIMEOUT_AVR_GENERAL_VYMK_K2_MIN, TIMEOUT_AVR_GENERAL_VYMK_K2_MAX) == 1)
                    {
                      if (edition_settings.timeout_avr_vymk_k2[group] != current_settings.timeout_avr_vymk_k2[group])
                      {
                        //�������, �� ���� ��������� ����� ���� ������
                        changed_settings = CHANGED_ETAP_EXECUTION;
                        
                        current_settings.timeout_avr_vymk_k2[group] = edition_settings.timeout_avr_vymk_k2[group];
                        //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                        fix_change_settings(0, 1);
                      }
                      //�������� � ������ �����������
                      current_ekran.edition = 0;
                    }
                  }
                }
                else if(
                        (current_ekran.current_level >= EKRAN_TIMEOUT_AVR_UMIN_GROUP1)&&
                        (current_ekran.current_level <= EKRAN_TIMEOUT_AVR_UMIN_GROUP4)
                       )   
                {
                  int group = (current_ekran.current_level - EKRAN_TIMEOUT_AVR_UMIN_GROUP1);
                  
                  if (current_ekran.index_position == INDEX_ML_TMOAVR_UMIN_VYMK_ROB_K1)
                  {
                    if (check_data_setpoint(edition_settings.timeout_avr_vymk_rob_k1_Umin[group], TIMEOUT_AVR_UMIN_VYMK_ROB_K1_MIN, TIMEOUT_AVR_UMIN_VYMK_ROB_K1_MAX) == 1)
                    {
                      if (edition_settings.timeout_avr_vymk_rob_k1_Umin[group] != current_settings.timeout_avr_vymk_rob_k1_Umin[group])
                      {
                        //�������, �� ���� ��������� ����� ���� ������
                        changed_settings = CHANGED_ETAP_EXECUTION;
                        
                        current_settings.timeout_avr_vymk_rob_k1_Umin[group] = edition_settings.timeout_avr_vymk_rob_k1_Umin[group];
                        //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                        fix_change_settings(0, 1);
                      }
                      //�������� � ������ �����������
                      current_ekran.edition = 0;
                    }
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOAVR_UMIN_VYMK_ROB_K2)
                  {
                    if (check_data_setpoint(edition_settings.timeout_avr_vymk_rob_k2_Umin[group], TIMEOUT_AVR_UMIN_VYMK_ROB_K2_MIN, TIMEOUT_AVR_UMIN_VYMK_ROB_K2_MAX) == 1)
                    {
                      if (edition_settings.timeout_avr_vymk_rob_k2_Umin[group] != current_settings.timeout_avr_vymk_rob_k2_Umin[group])
                      {
                        //�������, �� ���� ��������� ����� ���� ������
                        changed_settings = CHANGED_ETAP_EXECUTION;
                        
                        current_settings.timeout_avr_vymk_rob_k2_Umin[group] = edition_settings.timeout_avr_vymk_rob_k2_Umin[group];
                        //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                        fix_change_settings(0, 1);
                      }
                      //�������� � ������ �����������
                      current_ekran.edition = 0;
                    }
                  }
                }
                else if(
                        (current_ekran.current_level >= EKRAN_TIMEOUT_AVR_UMAX_GROUP1)&&
                        (current_ekran.current_level <= EKRAN_TIMEOUT_AVR_UMAX_GROUP4)
                       )   
                {
                  int group = (current_ekran.current_level - EKRAN_TIMEOUT_AVR_UMAX_GROUP1);
                  
                  if (current_ekran.index_position == INDEX_ML_TMOAVR_UMAX_VYMK_ROB_K1)
                  {
                    if (check_data_setpoint(edition_settings.timeout_avr_vymk_rob_k1_Umax[group], TIMEOUT_AVR_UMAX_VYMK_ROB_K1_MIN, TIMEOUT_AVR_UMAX_VYMK_ROB_K1_MAX) == 1)
                    {
                      if (edition_settings.timeout_avr_vymk_rob_k1_Umax[group] != current_settings.timeout_avr_vymk_rob_k1_Umax[group])
                      {
                        //�������, �� ���� ��������� ����� ���� ������
                        changed_settings = CHANGED_ETAP_EXECUTION;
                        
                        current_settings.timeout_avr_vymk_rob_k1_Umax[group] = edition_settings.timeout_avr_vymk_rob_k1_Umax[group];
                        //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                        fix_change_settings(0, 1);
                      }
                      //�������� � ������ �����������
                      current_ekran.edition = 0;
                    }
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOAVR_UMAX_VYMK_ROB_K2)
                  {
                    if (check_data_setpoint(edition_settings.timeout_avr_vymk_rob_k2_Umax[group], TIMEOUT_AVR_UMAX_VYMK_ROB_K2_MIN, TIMEOUT_AVR_UMAX_VYMK_ROB_K2_MAX) == 1)
                    {
                      if (edition_settings.timeout_avr_vymk_rob_k2_Umax[group] != current_settings.timeout_avr_vymk_rob_k2_Umax[group])
                      {
                        //�������, �� ���� ��������� ����� ���� ������
                        changed_settings = CHANGED_ETAP_EXECUTION;
                        
                        current_settings.timeout_avr_vymk_rob_k2_Umax[group] = edition_settings.timeout_avr_vymk_rob_k2_Umax[group];
                        //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                        fix_change_settings(0, 1);
                      }
                      //�������� � ������ �����������
                      current_ekran.edition = 0;
                    }
                  }
                }
                else if(current_ekran.current_level == EKRAN_CONTROL_AVR)
                {
                  if ((edition_settings.control_avr  & ((unsigned int)(~CTR_AVR_MASKA))) == 0)
                  {
                    if (edition_settings.control_avr != current_settings.control_avr)
                    {
                      //�������, �� ���� ��������� ����� ���� ������
                      changed_settings = CHANGED_ETAP_EXECUTION;
                        
                      current_settings.control_avr = edition_settings.control_avr;
                      //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                      fix_change_settings(0, 1);
                    }
                    //�������� � ������ �����������
                    current_ekran.edition = 0;
                  }
                }
                else if(
                        (current_ekran.current_level >= EKRAN_SETPOINT_CTRL_PHASE_GROUP1) &&
                        (current_ekran.current_level <= EKRAN_SETPOINT_CTRL_PHASE_GROUP4)
                       )   
                {
                  int group = (current_ekran.current_level - EKRAN_SETPOINT_CTRL_PHASE_GROUP1);
                  
                  if (current_ekran.index_position == INDEX_ML_STPCTRL_PHASE_U)
                  {
                    if (check_data_setpoint(edition_settings.setpoint_ctrl_phase_U[group], SETPOINT_CTRL_PHASE_U_MIN, SETPOINT_CTRL_PHASE_U_MAX) == 1)
                    {
                      if (edition_settings.setpoint_ctrl_phase_U[group] != current_settings.setpoint_ctrl_phase_U[group])
                      {
                        //�������, �� ���� ��������� ����� ���� ������
                        changed_settings = CHANGED_ETAP_EXECUTION;
                        
                        current_settings.setpoint_ctrl_phase_U[group] = edition_settings.setpoint_ctrl_phase_U[group];
                        //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                        fix_change_settings(0, 1);
                      }
                      //�������� � ������ �����������
                      current_ekran.edition = 0;
                    }
                  }
                  else if (current_ekran.index_position == INDEX_ML_STPCTRL_PHASE_PHI)
                  {
                    if (check_data_setpoint(edition_settings.setpoint_ctrl_phase_phi[group], SETPOINT_CTRL_PHASE_PHI_MIN, SETPOINT_CTRL_PHASE_PHI_MAX) == 1)
                    {
                      if (edition_settings.setpoint_ctrl_phase_phi[group] != current_settings.setpoint_ctrl_phase_phi[group])
                      {
                        //�������, �� ���� ��������� ����� ���� ������
                        changed_settings = CHANGED_ETAP_EXECUTION;
                        
                        current_settings.setpoint_ctrl_phase_phi[group] = edition_settings.setpoint_ctrl_phase_phi[group];
                        //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                        fix_change_settings(0, 1);
                      }
                      //�������� � ������ �����������
                      current_ekran.edition = 0;
                    }
                  }
                  else if (current_ekran.index_position == INDEX_ML_STPCTRL_PHASE_F)
                  {
                    if (check_data_setpoint(edition_settings.setpoint_ctrl_phase_f[group], SETPOINT_CTRL_PHASE_F_MIN, SETPOINT_CTRL_PHASE_F_MAX) == 1)
                    {
                      if (edition_settings.setpoint_ctrl_phase_f[group] != current_settings.setpoint_ctrl_phase_f[group])
                      {
                        //�������, �� ���� ��������� ����� ���� ������
                        changed_settings = CHANGED_ETAP_EXECUTION;
                        
                        current_settings.setpoint_ctrl_phase_f[group] = edition_settings.setpoint_ctrl_phase_f[group];
                        //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                        fix_change_settings(0, 1);
                      }
                      //�������� � ������ �����������
                      current_ekran.edition = 0;
                    }
                  }
                }
                else if(
                        (current_ekran.current_level >= EKRAN_TIMEOUT_CTRL_PHASE_GROUP1)&&
                        (current_ekran.current_level <= EKRAN_TIMEOUT_CTRL_PHASE_GROUP4)
                       )   
                {
                  int group = (current_ekran.current_level - EKRAN_TIMEOUT_CTRL_PHASE_GROUP1);
                  
                  if (current_ekran.index_position == INDEX_ML_TMOCTRL_PHASE_U)
                  {
                    if (check_data_setpoint(edition_settings.timeout_ctrl_phase_U[group], TIMEOUT_CTRL_PHASE_U_MIN, TIMEOUT_CTRL_PHASE_U_MAX) == 1)
                    {
                      if (edition_settings.timeout_ctrl_phase_U[group] != current_settings.timeout_ctrl_phase_U[group])
                      {
                        //�������, �� ���� ��������� ����� ���� ������
                        changed_settings = CHANGED_ETAP_EXECUTION;
                        
                        current_settings.timeout_ctrl_phase_U[group] = edition_settings.timeout_ctrl_phase_U[group];
                        //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                        fix_change_settings(0, 1);
                      }
                      //�������� � ������ �����������
                      current_ekran.edition = 0;
                    }
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOCTRL_PHASE_U_D)
                  {
                    if (check_data_setpoint(edition_settings.timeout_ctrl_phase_U_d[group], TIMEOUT_CTRL_PHASE_U_D_MIN, TIMEOUT_CTRL_PHASE_U_D_MAX) == 1)
                    {
                      if (edition_settings.timeout_ctrl_phase_U_d[group] != current_settings.timeout_ctrl_phase_U_d[group])
                      {
                        //�������, �� ���� ��������� ����� ���� ������
                        changed_settings = CHANGED_ETAP_EXECUTION;
                        
                        current_settings.timeout_ctrl_phase_U_d[group] = edition_settings.timeout_ctrl_phase_U_d[group];
                        //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                        fix_change_settings(0, 1);
                      }
                      //�������� � ������ �����������
                      current_ekran.edition = 0;
                    }
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOCTRL_PHASE_PHI)
                  {
                    if (check_data_setpoint(edition_settings.timeout_ctrl_phase_phi[group], TIMEOUT_CTRL_PHASE_PHI_MIN, TIMEOUT_CTRL_PHASE_PHI_MAX) == 1)
                    {
                      if (edition_settings.timeout_ctrl_phase_phi[group] != current_settings.timeout_ctrl_phase_phi[group])
                      {
                        //�������, �� ���� ��������� ����� ���� ������
                        changed_settings = CHANGED_ETAP_EXECUTION;
                        
                        current_settings.timeout_ctrl_phase_phi[group] = edition_settings.timeout_ctrl_phase_phi[group];
                        //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                        fix_change_settings(0, 1);
                      }
                      //�������� � ������ �����������
                      current_ekran.edition = 0;
                    }
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOCTRL_PHASE_PHI_D)
                  {
                    if (check_data_setpoint(edition_settings.timeout_ctrl_phase_phi_d[group], TIMEOUT_CTRL_PHASE_PHI_D_MIN, TIMEOUT_CTRL_PHASE_PHI_D_MAX) == 1)
                    {
                      if (edition_settings.timeout_ctrl_phase_phi_d[group] != current_settings.timeout_ctrl_phase_phi_d[group])
                      {
                        //�������, �� ���� ��������� ����� ���� ������
                        changed_settings = CHANGED_ETAP_EXECUTION;
                        
                        current_settings.timeout_ctrl_phase_phi_d[group] = edition_settings.timeout_ctrl_phase_phi_d[group];
                        //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                        fix_change_settings(0, 1);
                      }
                      //�������� � ������ �����������
                      current_ekran.edition = 0;
                    }
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOCTRL_PHASE_F)
                  {
                    if (check_data_setpoint(edition_settings.timeout_ctrl_phase_f[group], TIMEOUT_CTRL_PHASE_F_MIN, TIMEOUT_CTRL_PHASE_F_MAX) == 1)
                    {
                      if (edition_settings.timeout_ctrl_phase_f[group] != current_settings.timeout_ctrl_phase_f[group])
                      {
                        //�������, �� ���� ��������� ����� ���� ������
                        changed_settings = CHANGED_ETAP_EXECUTION;
                        
                        current_settings.timeout_ctrl_phase_f[group] = edition_settings.timeout_ctrl_phase_f[group];
                        //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                        fix_change_settings(0, 1);
                      }
                      //�������� � ������ �����������
                      current_ekran.edition = 0;
                    }
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOCTRL_PHASE_F_D)
                  {
                    if (check_data_setpoint(edition_settings.timeout_ctrl_phase_f_d[group], TIMEOUT_CTRL_PHASE_F_D_MIN, TIMEOUT_CTRL_PHASE_F_D_MAX) == 1)
                    {
                      if (edition_settings.timeout_ctrl_phase_f_d[group] != current_settings.timeout_ctrl_phase_f_d[group])
                      {
                        //�������, �� ���� ��������� ����� ���� ������
                        changed_settings = CHANGED_ETAP_EXECUTION;
                        
                        current_settings.timeout_ctrl_phase_f_d[group] = edition_settings.timeout_ctrl_phase_f_d[group];
                        //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                        fix_change_settings(0, 1);
                      }
                      //�������� � ������ �����������
                      current_ekran.edition = 0;
                    }
                  }
                }
                else if(current_ekran.current_level == EKRAN_CONTROL_CTRL_PHASE)
                {
                  if ((edition_settings.control_ctrl_phase  & ((unsigned int)(~CTR_CTRL_PHASE_MASKA))) == 0)
                  {
                    if (edition_settings.control_ctrl_phase != current_settings.control_ctrl_phase)
                    {
                      //�������, �� ���� ��������� ����� ���� ������
                      changed_settings = CHANGED_ETAP_EXECUTION;
                        
                      current_settings.control_ctrl_phase = edition_settings.control_ctrl_phase;
                      //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                      fix_change_settings(0, 1);
                    }
                    //�������� � ������ �����������
                    current_ekran.edition = 0;
                  }
                }
                else if(current_ekran.current_level == EKRAN_TRANSFORMATOR_INFO_SETPOINT)
                {
                  if (current_ekran.index_position == INDEX_ML_TT)
                  {
                    if (check_data_setpoint(edition_settings.TCurrent, KOEF_TT_MIN, KOEF_TT_MAX) == 1)
                    {
                      if (edition_settings.TCurrent != current_settings.TCurrent)
                      {
                        //�������, �� ���� ��������� ����� ���� ������
                        changed_settings = CHANGED_ETAP_EXECUTION;
                        
                        current_settings.TCurrent = edition_settings.TCurrent;
                        //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                        fix_change_settings(0, 1);
                      }
                      //�������� � ������ �����������
                      current_ekran.edition = 0;
                    }
                  }
                  else
                  {
                    if (check_data_setpoint(edition_settings.TVoltage, KOEF_TN_MIN, KOEF_TN_MAX) == 1)
                    {
                      if (edition_settings.TVoltage != current_settings.TVoltage)
                      {
                        //�������, �� ���� ��������� ����� ���� ������
                        changed_settings = CHANGED_ETAP_EXECUTION;
                        
                        current_settings.TVoltage = edition_settings.TVoltage;
                        //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                        fix_change_settings(0, 1);
                      }
                      //�������� � ������ �����������
                      current_ekran.edition = 0;
                    }
                  }
                }
                else if(current_ekran.current_level == EKRAN_TRANSFORMATOR_INFO_CONTROL)
                {
                  if ((edition_settings.control_transformator  & ((unsigned int)(~CTR_TRANSFORMATOR_MASKA))) == 0)
                  {
                    if (edition_settings.control_transformator != current_settings.control_transformator)
                    {
                      //�������, �� ���� ��������� ����� ���� ������
                      changed_settings = CHANGED_ETAP_EXECUTION;
                        
                      current_settings.control_transformator = edition_settings.control_transformator;
                      
                      //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                      fix_change_settings(0, 1);
                    }
                    //�������� � ������ �����������
                    current_ekran.edition = 0;
                  }
                }
                else if(current_ekran.current_level == EKRAN_SETPOINT_SWITCH)
                {
                  if (current_ekran.index_position == INDEX_ML_STPInom)
                  {
                    if (check_data_setpoint(edition_settings.setpoint_Inom, SETPOINT_Inom_MIN, SETPOINT_Inom_MAX) == 1)
                    {
                      if (edition_settings.setpoint_Inom != current_settings.setpoint_Inom)
                      {
                        //�������, �� ���� ��������� ����� ���� ������
                        changed_settings = CHANGED_ETAP_EXECUTION;
                        
                        current_settings.setpoint_Inom = edition_settings.setpoint_Inom;

                        //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                        fix_change_settings(0, 1);
                      }
                      //�������� � ������ �����������
                      current_ekran.edition = 0;
                    }
                  }
                  else if (current_ekran.index_position == INDEX_ML_STPRKS_Inom)
                  {
                    if (check_data_setpoint(edition_settings.setpoint_r_kom_st_Inom, SETPOINT_RKS_Inom_MIN, SETPOINT_RKS_Inom_MAX) == 1)
                    {
                      if (edition_settings.setpoint_r_kom_st_Inom != current_settings.setpoint_r_kom_st_Inom)
                      {
                        //�������, �� ���� ��������� ����� ���� ������
                        changed_settings = CHANGED_ETAP_EXECUTION;
                        
                        current_settings.setpoint_r_kom_st_Inom = edition_settings.setpoint_r_kom_st_Inom;

                        //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                        fix_change_settings(0, 1);
                      }
                      //�������� � ������ �����������
                      current_ekran.edition = 0;
                    }
                  }
                  else if (current_ekran.index_position == INDEX_ML_STPMInom_vymk)
                  {
                    if (check_data_setpoint(edition_settings.setpoint_Inom_vymk, SETPOINT_Inom_vymk_MIN, SETPOINT_Inom_vymk_MAX) == 1)
                    {
                      if (edition_settings.setpoint_Inom_vymk != current_settings.setpoint_Inom_vymk)
                      {
                        //�������, �� ���� ��������� ����� ���� ������
                        changed_settings = CHANGED_ETAP_EXECUTION;
                        
                        current_settings.setpoint_Inom_vymk = edition_settings.setpoint_Inom_vymk;

                        //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                        fix_change_settings(0, 1);
                      }
                      //�������� � ������ �����������
                      current_ekran.edition = 0;
                    }
                  }
                  else if (current_ekran.index_position == INDEX_ML_STPRKS_Inom_vymk)
                  {
                    if (check_data_setpoint(edition_settings.setpoint_r_kom_st_Inom_vymk, SETPOINT_RKS_Inom_vymk_MIN, SETPOINT_RKS_Inom_vymk_MAX) == 1)
                    {
                      if (edition_settings.setpoint_r_kom_st_Inom_vymk != current_settings.setpoint_r_kom_st_Inom_vymk)
                      {
                        //�������, �� ���� ��������� ����� ���� ������
                        changed_settings = CHANGED_ETAP_EXECUTION;
                        
                        current_settings.setpoint_r_kom_st_Inom_vymk = edition_settings.setpoint_r_kom_st_Inom_vymk;

                        //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                        fix_change_settings(0, 1);
                      }
                      //�������� � ������ �����������
                      current_ekran.edition = 0;
                    }
                  }
                  else if (current_ekran.index_position == INDEX_ML_STPPOCHATKOVYJ_RESURS)
                  {
                    if (check_data_setpoint(edition_settings.setpoint_pochatkovyj_resurs, (2*(current_settings.setpoint_r_kom_st_Inom/current_settings.setpoint_r_kom_st_Inom_vymk)), current_settings.setpoint_r_kom_st_Inom) == 1)
                    {
                      if (edition_settings.setpoint_pochatkovyj_resurs != current_settings.setpoint_pochatkovyj_resurs)
                      {
                        //�������, �� ���� ��������� ����� ���� ������
                        changed_settings = CHANGED_ETAP_EXECUTION;
                        
                        current_settings.setpoint_pochatkovyj_resurs = edition_settings.setpoint_pochatkovyj_resurs;
                        //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                        fix_change_settings(0, 1);
                      }
                      //�������� � ������ �����������
                      current_ekran.edition = 0;
                    }
                  }
                  else if (current_ekran.index_position == INDEX_ML_STPKRYTYCHNYJ_RESURS)
                  {
                    unsigned int chastka = current_settings.setpoint_r_kom_st_Inom/current_settings.setpoint_r_kom_st_Inom_vymk;
                    if (check_data_setpoint(edition_settings.setpoint_krytychnyj_resurs, chastka, (2*chastka)) == 1)
                    {
                      if (edition_settings.setpoint_krytychnyj_resurs != current_settings.setpoint_krytychnyj_resurs)
                      {
                        //�������, �� ���� ��������� ����� ���� ������
                        changed_settings = CHANGED_ETAP_EXECUTION;
                        
                        current_settings.setpoint_krytychnyj_resurs = edition_settings.setpoint_krytychnyj_resurs;
                        //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                        fix_change_settings(0, 1);
                      }
                      //�������� � ������ �����������
                      current_ekran.edition = 0;
                    }
                  }
                  else if (current_ekran.index_position == INDEX_ML_STPPOCHATKOVA_K_VYMK)
                  {
                    if (check_data_setpoint(edition_settings.setpoint_pochatkova_k_vymk, 0, current_settings.setpoint_r_kom_st_Inom) == 1)
                    {
                      if (edition_settings.setpoint_pochatkova_k_vymk != current_settings.setpoint_pochatkova_k_vymk)
                      {
                        //�������, �� ���� ��������� ����� ���� ������
                        changed_settings = CHANGED_ETAP_EXECUTION;
                        
                        current_settings.setpoint_pochatkova_k_vymk = edition_settings.setpoint_pochatkova_k_vymk;
                        //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                        fix_change_settings(0, 1);
                      }
                      //�������� � ������ �����������
                      current_ekran.edition = 0;
                    }
                  }
                }
                else if(current_ekran.current_level == EKRAN_TIMEOUT_SWITCH)
                {
                  if (current_ekran.index_position == INDEX_ML_TMOON)
                  {
                    if (check_data_setpoint(edition_settings.timeout_swch_on, TIMEOUT_SWCH_ON_MIN, TIMEOUT_SWCH_ON_MAX) == 1)
                    {
                      if (edition_settings.timeout_swch_on != current_settings.timeout_swch_on)
                      {
                        //�������, �� ���� ��������� ����� ���� ������
                        changed_settings = CHANGED_ETAP_EXECUTION;
                        
                        current_settings.timeout_swch_on = edition_settings.timeout_swch_on;
                        //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                        fix_change_settings(0, 1);
                      }
                      //�������� � ������ �����������
                      current_ekran.edition = 0;
                    }
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOOFF)
                  {
                    if (check_data_setpoint(edition_settings.timeout_swch_off, TIMEOUT_SWCH_OFF_MIN, TIMEOUT_SWCH_OFF_MAX) == 1)
                    {
                      if (edition_settings.timeout_swch_off != current_settings.timeout_swch_off)
                      {
                        //�������, �� ���� ��������� ����� ���� ������
                        changed_settings = CHANGED_ETAP_EXECUTION;
                        
                        current_settings.timeout_swch_off = edition_settings.timeout_swch_off;
                        //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                        fix_change_settings(0, 1);
                      }
                      //�������� � ������ �����������
                      current_ekran.edition = 0;
                    }
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOUDL_BLK_ON)
                  {
                    if (check_data_setpoint(edition_settings.timeout_swch_udl_blk_on, TIMEOUT_SWCH_UDL_BLK_ON_MIN, TIMEOUT_SWCH_UDL_BLK_ON_MAX) == 1)
                    {
                      if (edition_settings.timeout_swch_udl_blk_on != current_settings.timeout_swch_udl_blk_on)
                      {
                        //�������, �� ���� ��������� ����� ���� ������
                        changed_settings = CHANGED_ETAP_EXECUTION;
                        
                        current_settings.timeout_swch_udl_blk_on = edition_settings.timeout_swch_udl_blk_on;
                        //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                        fix_change_settings(0, 1);
                      }
                      //�������� � ������ �����������
                      current_ekran.edition = 0;
                    }
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOPRYVODA_VV)
                  {
                    if (check_data_setpoint(edition_settings.timeout_pryvoda_VV, TIMEOUT_PRYVODA_VV_MIN, TIMEOUT_PRYVODA_VV_MAX) == 1)
                    {
                      if (edition_settings.timeout_pryvoda_VV != current_settings.timeout_pryvoda_VV)
                      {
                        //�������, �� ���� ��������� ����� ���� ������
                        changed_settings = CHANGED_ETAP_EXECUTION;
                        
                        current_settings.timeout_pryvoda_VV = edition_settings.timeout_pryvoda_VV;
                        //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                        fix_change_settings(0, 1);
                      }
                      //�������� � ������ �����������
                      current_ekran.edition = 0;
                    }
                  }
                }
                else if(current_ekran.current_level == EKRAN_CONTROL_SWITCH)
                {
                  if ((edition_settings.control_switch & ((unsigned int)(~CTR_SWITCH_MASKA))) == 0)
                  {
                    if (edition_settings.control_switch != current_settings.control_switch)
                    {
                      //�������, �� ���� ��������� ����� ���� ������
                      changed_settings = CHANGED_ETAP_EXECUTION;
                        
                      current_settings.control_switch = edition_settings.control_switch;
                      //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                      fix_change_settings(0, 1);
                    }
                    //�������� � ������ �����������
                    current_ekran.edition = 0;
                  }
                }
                else if(current_ekran.current_level == EKRAN_DOPUSK_DV_UVV)
                {
                  unsigned int min_value;
                  if ((current_settings.type_of_input_signal & (1 << current_ekran.index_position)) == 0)
                    min_value = KOEF_DOPUSK_DV_POST_MIN;
                  else 
                    min_value = KOEF_DOPUSK_DV_ZMIN_MIN;
                  if (check_data_setpoint(edition_settings.dopusk_dv[current_ekran.index_position], min_value, KOEF_DOPUSK_DV_MAX) == 1)
                  {
                    if (edition_settings.dopusk_dv[current_ekran.index_position] != current_settings.dopusk_dv[current_ekran.index_position])
                    {
                      //�������, �� ���� ��������� ����� ���� ������
                      changed_settings = CHANGED_ETAP_EXECUTION;

                      current_settings.dopusk_dv[current_ekran.index_position] = edition_settings.dopusk_dv[current_ekran.index_position];
                      //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                      fix_change_settings(0, 1);
                    }
                    //�������� � ������ �����������
                    current_ekran.edition = 0;
                  }
                }
                else if(current_ekran.current_level == EKRAN_TYPE_INPUT_UVV)
                {
                  if ((edition_settings.type_of_input & ((unsigned int)(~((1<<NUMBER_INPUTS)-1)))) == 0)
                  {
                    if (edition_settings.type_of_input != current_settings.type_of_input)
                    {
                      //�������, �� ���� ��������� ����� ���� ������
                      changed_settings = CHANGED_ETAP_EXECUTION;
                      
                      current_settings.type_of_input = edition_settings.type_of_input;
                      //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                      fix_change_settings(0, 1);
                    }
                    //�������� � ������ �����������
                    current_ekran.edition = 0;
                  }
                }
                else if(current_ekran.current_level == EKRAN_TYPE_INPUT_SIGNAL_UVV)
                {
                  if ((edition_settings.type_of_input_signal & ((unsigned int)(~((1<<NUMBER_INPUTS)-1)))) == 0)
                  {
                    if (edition_settings.type_of_input_signal != current_settings.type_of_input_signal)
                    {
                      //�������, �� ���� ��������� ����� ���� ������
                      changed_settings = CHANGED_ETAP_EXECUTION;
                      
                      correct_dopusk_dv_when_type_of_input_signal_is_changed();
                      current_settings.type_of_input_signal = edition_settings.type_of_input_signal;
                      //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                      fix_change_settings(0, 1);
                    }
                    //�������� � ������ �����������
                    current_ekran.edition = 0;
                  }
                }
                else if(current_ekran.current_level == EKRAN_TYPE_OUTPUT_UVV)
                {
                  if (
                      ((edition_settings.type_of_output       & ((unsigned int)(~((1<<NUMBER_OUTPUTS)-1)))) == 0) &&
                      ((edition_settings.type_of_output_modif & ((unsigned int)(~((1<<NUMBER_OUTPUTS)-1)))) == 0)
                     )
                  {
                    if (
                        (edition_settings.type_of_output       != current_settings.type_of_output      ) ||
                        (edition_settings.type_of_output_modif != current_settings.type_of_output_modif)
                       )   
                    {
                      //�������, �� ���� ��������� ����� ���� ������
                      changed_settings = CHANGED_ETAP_EXECUTION;

                      current_settings.type_of_output       = edition_settings.type_of_output;
                      current_settings.type_of_output_modif = edition_settings.type_of_output_modif;
                      //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                      fix_change_settings(0, 1);
                    }
                    //�������� � ������ �����������
                    current_ekran.edition = 0;
                  }
                }
                else if(current_ekran.current_level == EKRAN_TYPE_LED_UVV)
                {
                  if ((edition_settings.type_of_led & ((unsigned int)(~((1<<NUMBER_LEDS)-1)))) == 0)
                  {
                    if (edition_settings.type_of_led != current_settings.type_of_led)
                    {
                      //�������, �� ���� ��������� ����� ���� ������
                      changed_settings = CHANGED_ETAP_EXECUTION;

                      current_settings.type_of_led = edition_settings.type_of_led;
                      //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                      fix_change_settings(0, 1);
                    }
                    //�������� � ������ �����������
                    current_ekran.edition = 0;
                  }
                }
                else if(current_ekran.current_level == EKRAN_ADDRESS)
                {
                  if (check_data_setpoint(edition_settings.address, KOEF_ADDRESS_MIN, KOEF_ADDRESS_MAX) == 1)
                  {
                    unsigned int edit_value = edition_settings.address;
                    if (edit_value != current_settings.address)
                    {
                      //�������, �� ���� ��������� ����� ���� ������
                      changed_settings = CHANGED_ETAP_EXECUTION;
                        
                      current_settings.address = edit_value;
                      //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                      fix_change_settings(0, 1);
                    }
                    //�������� � ������ �����������
                    current_ekran.edition = 0;
                  }
                }
                else if(current_ekran.current_level == EKRAN_VIEW_SPEED_RS485)
                {
                  if (check_data_setpoint(edition_settings.speed_RS485, VALUE_SPEED_INTERFACE_MIN, VALUE_SPEED_INTERFACE_MAX) == 1)
                  {
                    if (edition_settings.speed_RS485 != current_settings.speed_RS485)
                    {
                      //�������, �� ���� ��������� ����� ���� ������
                      changed_settings = CHANGED_ETAP_EXECUTION;
                        
                      current_settings.speed_RS485 = edition_settings.speed_RS485;
                      //ϳ��������� ���� �������� �������� � ����, ��� ����������� �� ������� � RS-485 ����� � ����������� �����������
                      calculate_namber_bit_waiting_for_rs_485();
                      //����������� ������� ��� ������������������ RS-485
                      make_reconfiguration_RS_485 = 0xff;
                      //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                      fix_change_settings(0, 1);
                    }
                    //�������� � ������ �����������
                    current_ekran.edition = 0;
                  }
                }
                else if(current_ekran.current_level == EKRAN_VIEW_PARE_RS485)
                {
                  if (check_data_setpoint(edition_settings.pare_bit_RS485, VALUE_PARE_INTERFACE_MIN, VALUE_PARE_INTERFACE_MAX) == 1)
                  {
                    if (edition_settings.pare_bit_RS485 != current_settings.pare_bit_RS485)
                    {
                      //�������, �� ���� ��������� ����� ���� ������
                      changed_settings = CHANGED_ETAP_EXECUTION;
                        
                      current_settings.pare_bit_RS485 = edition_settings.pare_bit_RS485;
                      //ϳ��������� ���� �������� �������� � ����, ��� ����������� �� ������� � RS-485 ����� � ����������� �����������
                      calculate_namber_bit_waiting_for_rs_485();
                      //����������� ������� ��� ������������������ RS-485
                      make_reconfiguration_RS_485 = 0xff;
                      //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                      fix_change_settings(0, 1);
                    }
                    //�������� � ������ �����������
                    current_ekran.edition = 0;
                  }
                }
                else if(current_ekran.current_level == EKRAN_VIEW_STOP_BITS_RS485)
                {
                  if (check_data_setpoint(edition_settings.number_stop_bit_RS485, VALUE_STOP_BITS_INTERFACE_MIN, VALUE_STOP_BITS_INTERFACE_MAX) == 1)
                  {
                    if (edition_settings.number_stop_bit_RS485 != current_settings.number_stop_bit_RS485)
                    {
                      //�������, �� ���� ��������� ����� ���� ������
                      changed_settings = CHANGED_ETAP_EXECUTION;
                        
                      current_settings.number_stop_bit_RS485 = edition_settings.number_stop_bit_RS485;
                      //ϳ��������� ���� �������� �������� � ����, ��� ����������� �� ������� � RS-485 ����� � ����������� �����������
                      calculate_namber_bit_waiting_for_rs_485();
                      //����������� ������� ��� ������������������ RS-485
                      make_reconfiguration_RS_485 = 0xff;
                      //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                      fix_change_settings(0, 1);
                    }
                    //�������� � ������ �����������
                    current_ekran.edition = 0;
                  }
                }
                else if(current_ekran.current_level == EKRAN_VIEW_TIMEOUT_RS485)
                {
                  if (check_data_setpoint(edition_settings.time_out_1_RS485, VALUE_TIME_OUT_1_INTERFACE_MIN, VALUE_TIME_OUT_1_INTERFACE_MAX) == 1)
                  {
                    if (edition_settings.time_out_1_RS485 != current_settings.time_out_1_RS485)
                    {
                      //�������, �� ���� ��������� ����� ���� ������
                      changed_settings = CHANGED_ETAP_EXECUTION;
                        
                      current_settings.time_out_1_RS485 = edition_settings.time_out_1_RS485;
                      //ϳ��������� ���� �������� �������� � ����, ��� ����������� �� ������� � RS-485 ����� � ����������� �����������
                      calculate_namber_bit_waiting_for_rs_485();
                      //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                      fix_change_settings(0, 1);
                    }
                    //�������� � ������ �����������
                    current_ekran.edition = 0;
                  }
                }
                else if(current_ekran.current_level == EKRAN_GENERAL_PICKUPS_EL)
                {
                  if (current_ekran.index_position == INDEX_ML_NUMBER_INERATION)
                  {
                    if (check_data_setpoint(edition_settings.number_iteration_el, NUMBER_ITERATION_EL_MIN, NUMBER_ITERATION_EL_MAX) == 1)
                    {
                      if (edition_settings.number_iteration_el != current_settings.number_iteration_el)
                      {
                        //�������, �� ���� ��������� ����� ���� ������
                        changed_settings = CHANGED_ETAP_EXECUTION;

                        current_settings.number_iteration_el = edition_settings.number_iteration_el;
                        //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                        fix_change_settings(0, 1);
                      }
                      //�������� � ������ �����������
                      current_ekran.edition = 0;
                    }
                  }
//                  else if (current_ekran.index_position == INDEX_ML_NUMBER_DEFINED_FUNCTIONS)
//                  {
//                    if (check_data_setpoint(edition_settings.number_defined_df, NUMBER_DEFINED_FUNCTIONS_MIN, NUMBER_DEFINED_FUNCTIONS_MAX) == 1)
//                    {
//                      if (edition_settings.number_defined_df != current_settings.number_defined_df)
//                      {
//                        //�������, �� ���� ��������� ����� ���� ������
//                        changed_settings = CHANGED_ETAP_EXECUTION;
//
//                        current_settings.number_defined_df = edition_settings.number_defined_df;
//                        //���������� ��������
//                        action_after_changing_number_el(&current_settings, 0);
//                      
//                        //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
//                        fix_change_settings(0, 1);
//                      }
//                      //�������� � ������ �����������
//                      current_ekran.edition = 0;
//                    }
//                  }
//                  else if (current_ekran.index_position == INDEX_ML_NUMBER_DEFINED_TRIGGERS)
//                  {
//                    if (check_data_setpoint(edition_settings.number_defined_dt, NUMBER_DEFINED_TRIGGERS_MIN, NUMBER_DEFINED_TRIGGERS_MAX) == 1)
//                    {
//                      if (edition_settings.number_defined_dt != current_settings.number_defined_dt)
//                      {
//                        //�������, �� ���� ��������� ����� ���� ������
//                        changed_settings = CHANGED_ETAP_EXECUTION;
//
//                        current_settings.number_defined_dt = edition_settings.number_defined_dt;
//                        //���������� ��������
//                        action_after_changing_number_el(&current_settings, 1);
//
//                        //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
//                        fix_change_settings(0, 1);
//                      }
//                      //�������� � ������ �����������
//                      current_ekran.edition = 0;
//                    }
//                  }
//                  else if (current_ekran.index_position == INDEX_ML_NUMBER_DEFINED_AND)
//                  {
//                    if (check_data_setpoint(edition_settings.number_defined_and, NUMBER_DEFINED_AND_MIN, NUMBER_DEFINED_AND_MAX) == 1)
//                    {
//                      if (edition_settings.number_defined_and != current_settings.number_defined_and)
//                      {
//                        //�������, �� ���� ��������� ����� ���� ������
//                        changed_settings = CHANGED_ETAP_EXECUTION;
//
//                        current_settings.number_defined_and = edition_settings.number_defined_and;
//                        //���������� ��������
//                        action_after_changing_number_el(&current_settings, 2);
//
//                        //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
//                        fix_change_settings(0, 1);
//                      }
//                      //�������� � ������ �����������
//                      current_ekran.edition = 0;
//                    }
//                  }
//                  else if (current_ekran.index_position == INDEX_ML_NUMBER_DEFINED_OR)
//                  {
//                    if (check_data_setpoint(edition_settings.number_defined_or, NUMBER_DEFINED_OR_MIN, NUMBER_DEFINED_OR_MAX) == 1)
//                    {
//                      if (edition_settings.number_defined_or != current_settings.number_defined_or)
//                      {
//                        //�������, �� ���� ��������� ����� ���� ������
//                        changed_settings = CHANGED_ETAP_EXECUTION;
//
//                        current_settings.number_defined_or = edition_settings.number_defined_or;
//                        //���������� ��������
//                        action_after_changing_number_el(&current_settings, 3);
//
//                        //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
//                        fix_change_settings(0, 1);
//                      }
//                      //�������� � ������ �����������
//                      current_ekran.edition = 0;
//                    }
//                  }
//                  else if (current_ekran.index_position == INDEX_ML_NUMBER_DEFINED_XOR)
//                  {
//                    if (check_data_setpoint(edition_settings.number_defined_xor, NUMBER_DEFINED_XOR_MIN, NUMBER_DEFINED_XOR_MAX) == 1)
//                    {
//                      if (edition_settings.number_defined_xor != current_settings.number_defined_xor)
//                      {
//                        //�������, �� ���� ��������� ����� ���� ������
//                        changed_settings = CHANGED_ETAP_EXECUTION;
//
//                        current_settings.number_defined_xor = edition_settings.number_defined_xor;
//                        //���������� ��������
//                        action_after_changing_number_el(&current_settings, 4);
//
//                        //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
//                        fix_change_settings(0, 1);
//                      }
//                      //�������� � ������ �����������
//                      current_ekran.edition = 0;
//                    }
//                  }
//                  else if (current_ekran.index_position == INDEX_ML_NUMBER_DEFINED_NOT)
//                  {
//                    if (check_data_setpoint(edition_settings.number_defined_not, NUMBER_DEFINED_NOT_MIN, NUMBER_DEFINED_NOT_MAX) == 1)
//                    {
//                      if (edition_settings.number_defined_not != current_settings.number_defined_not)
//                      {
//                        //�������, �� ���� ��������� ����� ���� ������
//                        changed_settings = CHANGED_ETAP_EXECUTION;
//
//                        current_settings.number_defined_not = edition_settings.number_defined_not;
//                        //���������� ��������
//                        action_after_changing_number_el(&current_settings, 5);
//
//                        //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
//                        fix_change_settings(0, 1);
//                      }
//                      //�������� � ������ �����������
//                      current_ekran.edition = 0;
//                    }
//                  }
                }
                else if(current_ekran.current_level == EKRAN_LIST_TYPE_DF)
                {
                  if ((edition_settings.type_df & ((unsigned int)(~((1<<NUMBER_DEFINED_FUNCTIONS)-1)))) == 0)
                  {
                    if (edition_settings.type_df != current_settings.type_df)
                    {
                      //�������, �� ���� ��������� ����� ���� ������
                      changed_settings = CHANGED_ETAP_EXECUTION;

                      current_settings.type_df = edition_settings.type_df;
                      //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                      fix_change_settings(0, 1);
                    }
                    //�������� � ������ �����������
                    current_ekran.edition = 0;
                  }
                }
                else if((current_ekran.current_level >= EKRAN_TIMEOUT_DF1) && (current_ekran.current_level <= EKRAN_TIMEOUT_DF8))
                {
                  if (current_ekran.index_position == INDEX_ML_TMO_DF_PAUSE)
                  {
                    if (check_data_setpoint(edition_settings.timeout_pause_df[current_ekran.current_level - EKRAN_TIMEOUT_DF1], TIMEOUT_DF_PAUSE_MIN, TIMEOUT_DF_PAUSE_MAX) == 1)
                    {
                      if (edition_settings.timeout_pause_df[current_ekran.current_level - EKRAN_TIMEOUT_DF1] != 
                          current_settings.timeout_pause_df[current_ekran.current_level - EKRAN_TIMEOUT_DF1])
                      {
                        //�������, �� ���� ��������� ����� ���� ������
                        changed_settings = CHANGED_ETAP_EXECUTION;

                        current_settings.timeout_pause_df[current_ekran.current_level - EKRAN_TIMEOUT_DF1] = 
                          edition_settings.timeout_pause_df[current_ekran.current_level - EKRAN_TIMEOUT_DF1];
                        //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                        fix_change_settings(0, 1);
                      }
                      //�������� � ������ �����������
                      current_ekran.edition = 0;
                    }
                  }
                  else
                  {
                    if (check_data_setpoint(edition_settings.timeout_work_df[current_ekran.current_level - EKRAN_TIMEOUT_DF1], TIMEOUT_DF_WORK_MIN, TIMEOUT_DF_WORK_MAX) == 1)
                    {
                      if (edition_settings.timeout_work_df[current_ekran.current_level - EKRAN_TIMEOUT_DF1] != 
                          current_settings.timeout_work_df[current_ekran.current_level - EKRAN_TIMEOUT_DF1])
                      {
                        //�������, �� ���� ��������� ����� ���� ������
                        changed_settings = CHANGED_ETAP_EXECUTION;

                        current_settings.timeout_work_df[current_ekran.current_level - EKRAN_TIMEOUT_DF1] = 
                          edition_settings.timeout_work_df[current_ekran.current_level - EKRAN_TIMEOUT_DF1];
                        //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                        fix_change_settings(0, 1);
                      }
                      //�������� � ������ �����������
                      current_ekran.edition = 0;
                    }
                  }
                }
                else if(current_ekran.current_level == EKRAN_TIMEOUT_ANALOG_REGISTRATOR)
                {
                  /*������������ ������� - ���� ����� ������ � ����, �� ���� ������ ������ ���� 
                  ���� �� ��� - �� �� ��� ���� ������������ ����� ����� �������� �� �����, ���� � ��� ��� ���� �����,
                  �� �� �� �������������� �, �������, ��������� ������ ����������� ���������� �� �����*/
                  semaphore_read_state_ar_record = 1;
                  
                  if (state_ar_record == STATE_AR_NO_RECORD)
                  {
                    /*�� ����� ������ �� ��� ����� �������� ����������� ��������� �������,
                    ���� ��� ���� ������� ��������� ��������� ������������ ���� ������
                    ����������� ���������� � ������������ �����*/
                    state_ar_record = STATE_AR_TEMPORARY_BLOCK; 
                    
                    if (current_ekran.index_position == INDEX_ML_TMOPREFAULT)
                    {
                      if (check_data_setpoint((edition_settings.prefault_number_periods*20), TIMEOUT_PREFAULT_MIN, TIMEOUT_PREFAULT_MAX) == 1)
                      {
                        if (edition_settings.prefault_number_periods != current_settings.prefault_number_periods)
                        {
                          //�������, �� ���� ��������� ����� ���� ������
                          changed_settings = CHANGED_ETAP_EXECUTION;
                        
                          current_settings.prefault_number_periods = edition_settings.prefault_number_periods;
                          //�������� 䳿 �� ���� ������� �������� ����������� ����������
                          actions_after_changing_tiomouts_ar();
                          //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                          fix_change_settings(0, 1);
                        }
                        //�������� � ������ �����������
                        current_ekran.edition = 0;
                      }
                    }
                    else
                    {
                      if (check_data_setpoint((edition_settings.postfault_number_periods*20), TIMEOUT_POSTFAULT_MIN, TIMEOUT_POSTFAULT_MAX) == 1)
                      {
                        if (edition_settings.postfault_number_periods != current_settings.postfault_number_periods)
                        {
                          //�������, �� ���� ��������� ����� ���� ������
                          changed_settings = CHANGED_ETAP_EXECUTION;
                        
                          current_settings.postfault_number_periods = edition_settings.postfault_number_periods;
                          //�������� 䳿 �� ���� ������� �������� ����������� ����������
                          actions_after_changing_tiomouts_ar();
                          //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                          fix_change_settings(0, 1);
                        }
                        //�������� � ������ �����������
                        current_ekran.edition = 0;
                      }
                    }
                    
                    //������������ ������ ����������� ����������
                    state_ar_record = STATE_AR_NO_RECORD;
                  }
                  
                  //������� �������
                  semaphore_read_state_ar_record = 0;
                }
                else if(current_ekran.current_level == EKRAN_VIEW_SETTING_LANGUAGE)
                {
                  if (check_data_setpoint(edition_settings.language, VALUE_SETTING_LANGUAGE_MIN, VALUE_SETTING_LANGUAGE_MAX) == 1)
                  {
                    if (edition_settings.language != current_settings.language)
                    {
                      //�������, �� ���� ��������� ����� ���� ������
                      changed_settings = CHANGED_ETAP_EXECUTION;
                        
                      current_settings.language = edition_settings.language;
                      //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                      fix_change_settings(0, 1);
                    }
                    //�������� � ������ �����������
                    current_ekran.edition = 0;
                  }
                }
                else if(current_ekran.current_level == EKRAN_CHOSE_EXTRA_SETTINGS)
                {
                  if ((edition_settings.control_extra_settings_1  & ((unsigned int)(~CTR_EXTRA_SETTINGS_1_MASKA))) == 0)
                  {
                    if (edition_settings.control_extra_settings_1 != current_settings.control_extra_settings_1)
                    {
                      //�������, �� ���� ��������� ����� ���� ������
                      changed_settings = CHANGED_ETAP_EXECUTION;
                        
                      current_settings.control_extra_settings_1 = edition_settings.control_extra_settings_1;
                      
                      //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                      fix_change_settings(0, 1);
                    }
                    //�������� � ������ �����������
                    current_ekran.edition = 0;
                  }
                }
                
              }
              else if (current_ekran.edition == 3)
              {
                //����� � ����� �����������
                current_ekran.edition = 0;
              }
              
              if(current_ekran.edition == 2) make_ekran_ask_rewrite();
              else if(current_ekran.edition == 3)
              {
                const unsigned char information_about_error1[MAX_NAMBER_LANGUAGE][MAX_COL_LCD] = 
                {
                  " ���.�� ��������",
                  " ���.�� �������",
                  "  Out of Limits ",
                  "���.�� �������� "
                };
                const unsigned char information_about_error2[MAX_NAMBER_LANGUAGE][MAX_COL_LCD] = 
                {
                  " ����.��.������.",
                  "����.����.������",
                  " Op.unavailable ",
                  " ����.��.������."
                };

                const unsigned char (*point_to_information_about_error)[MAX_COL_LCD] = information_about_error1;
                if(current_ekran.current_level == EKRAN_TIMEOUT_ANALOG_REGISTRATOR)
                {
                  if (state_ar_record != STATE_AR_NO_RECORD)
                    point_to_information_about_error = information_about_error2;
                }
                make_ekran_about_error(point_to_information_about_error);
              }
              else
                //����������� �� ���������� ������
                new_state_keyboard |= (1<<BIT_REWRITE);

              //�������� �����������, �� ��������� ������ 
              new_state_keyboard &= (unsigned int)(~(1<<BIT_KEY_ENTER));
            }
            else if (new_state_keyboard == (1<<BIT_KEY_ESC))
            {
              if(current_ekran.edition == 0)
              {
                //����� � ����� ������������
              //���������� � ��������� ����
              current_ekran.current_level = previous_level_in_current_level_menu[current_ekran.current_level];
              current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
              current_ekran.edition = 0;
              }
              else
              {
                //����� � ����� ����������� ��� �������� ���
                current_ekran.edition = 0;
              }

              //����������� ������� �� ����������� ������ ������
              new_state_keyboard |= (1<<BIT_REWRITE);
              //�������� �����������, �� ��������� ������ 
              new_state_keyboard &= (unsigned int)(~(1<<BIT_KEY_ESC));
            }
            else if (new_state_keyboard == (1<<BIT_KEY_UP))
            {
              //��������� ������ UP
              if (current_ekran.current_level == EKRAN_CONTROL_ZDZ)
              {
                current_ekran.index_position--;
                
                if(current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_CONTROL_ZDZ - 1;
                position_in_current_level_menu[EKRAN_CONTROL_ZDZ] = current_ekran.index_position;
                
                //������� ����� ����������� ���������� ��� ���
                make_ekran_control_zdz();
              }
              else if(
                      (current_ekran.current_level >= EKRAN_TIMEOUT_APV_GROUP1) &&
                      (current_ekran.current_level <= EKRAN_TIMEOUT_APV_GROUP4)
                     )   
              {
                int group = (current_ekran.current_level - EKRAN_TIMEOUT_APV_GROUP1);
                
                if(current_ekran.edition == 0)
                {
                  if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_TIMEOUT_APV - 1;
                  position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;
                }
                else
                {
                  //����������� �����
                  if (current_ekran.index_position == INDEX_ML_TMOAPV1)
                    edition_settings.timeout_apv_1[group] = edit_setpoint(1, edition_settings.timeout_apv_1[group], 1, COL_TMO_APV_1_COMMA, COL_TMO_APV_1_END, 10);
                  else if (current_ekran.index_position == INDEX_ML_TMOAPV2)
                    edition_settings.timeout_apv_2[group] = edit_setpoint(1, edition_settings.timeout_apv_2[group], 1, COL_TMO_APV_2_COMMA, COL_TMO_APV_2_END, 10);
                  else if (current_ekran.index_position == INDEX_ML_TMOAPV3)
                    edition_settings.timeout_apv_3[group] = edit_setpoint(1, edition_settings.timeout_apv_3[group], 1, COL_TMO_APV_3_COMMA, COL_TMO_APV_3_END, 10);
                  else if (current_ekran.index_position == INDEX_ML_TMOAPV4)
                    edition_settings.timeout_apv_4[group] = edit_setpoint(1, edition_settings.timeout_apv_4[group], 1, COL_TMO_APV_4_COMMA, COL_TMO_APV_4_END, 10);
                  else if (current_ekran.index_position == INDEX_ML_TMOAPV_BLOCK_VID_APV1)
                    edition_settings.timeout_apv_block_vid_apv1[group] = edit_setpoint(1, edition_settings.timeout_apv_block_vid_apv1[group], 1, COL_TMO_APV_BLOCK_VID_APV1_COMMA, COL_TMO_APV_BLOCK_VID_APV1_END, 10);
                  else if (current_ekran.index_position == INDEX_ML_TMOAPV_BLOCK_VID_APV2)
                    edition_settings.timeout_apv_block_vid_apv2[group] = edit_setpoint(1, edition_settings.timeout_apv_block_vid_apv2[group], 1, COL_TMO_APV_BLOCK_VID_APV2_COMMA, COL_TMO_APV_BLOCK_VID_APV2_END, 10);
                  else if (current_ekran.index_position == INDEX_ML_TMOAPV_BLOCK_VID_APV3)
                    edition_settings.timeout_apv_block_vid_apv3[group] = edit_setpoint(1, edition_settings.timeout_apv_block_vid_apv3[group], 1, COL_TMO_APV_BLOCK_VID_APV3_COMMA, COL_TMO_APV_BLOCK_VID_APV3_END, 10);
                  else if (current_ekran.index_position == INDEX_ML_TMOAPV_BLOCK_VID_APV4)
                    edition_settings.timeout_apv_block_vid_apv4[group] = edit_setpoint(1, edition_settings.timeout_apv_block_vid_apv4[group], 1, COL_TMO_APV_BLOCK_VID_APV4_COMMA, COL_TMO_APV_BLOCK_VID_APV4_END, 10);
                  else if (current_ekran.index_position == INDEX_ML_TMOAPV_BLOCK_VID_VV)
                    edition_settings.timeout_apv_block_vid_VV[group] = edit_setpoint(1, edition_settings.timeout_apv_block_vid_VV[group], 1, COL_TMO_APV_BLOCK_VID_VV_COMMA, COL_TMO_APV_BLOCK_VID_VV_END, 10);
                }
                //������� ����� �������� ���
                make_ekran_timeout_apv(group);
              }
              else if(current_ekran.current_level == EKRAN_CONTROL_APV)
              {
                current_ekran.index_position--;
                
                if(current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_CONTROL_APV - 1;
                position_in_current_level_menu[EKRAN_CONTROL_APV] = current_ekran.index_position;
                //������� ����� ����������� ���������� ��� ���
                make_ekran_control_apv();
              }
              else if(
                      (current_ekran.current_level >= EKRAN_SETPOINT_UROV_GROUP1) &&
                      (current_ekran.current_level <= EKRAN_SETPOINT_UROV_GROUP4)
                     )   
              {
                int group = (current_ekran.current_level - EKRAN_SETPOINT_UROV_GROUP1);
                
                if(current_ekran.edition == 0)
                {
                  if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_SETPOINT_UROV - 1;
                  position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;
                }
                else
                {
                  //����������� �����
                  edition_settings.setpoint_urov[group] = edit_setpoint(1, edition_settings.setpoint_urov[group], 1, COL_SETPOINT_UROV_COMMA, COL_SETPOINT_UROV_END, 10);
                }
                //������� ����� ������� ����
                make_ekran_setpoint_urov(group);
              }
              else if(
                      (current_ekran.current_level >= EKRAN_TIMEOUT_UROV_GROUP1) &&
                      (current_ekran.current_level <= EKRAN_TIMEOUT_UROV_GROUP4)
                     )   
              {
                int group = (current_ekran.current_level - EKRAN_TIMEOUT_UROV_GROUP1);
                
                if(current_ekran.edition == 0)
                {
                  if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_TIMEOUT_UROV - 1;
                  position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;
                }
                else
                {
                  //����������� �����
                  if (current_ekran.index_position == INDEX_ML_TMOUROV1)
                    edition_settings.timeout_urov_1[group] = edit_setpoint(1, edition_settings.timeout_urov_1[group], 1, COL_TMO_UROV_1_COMMA, COL_TMO_UROV_1_END, 10);
                  else
                    edition_settings.timeout_urov_2[group] = edit_setpoint(1, edition_settings.timeout_urov_2[group], 1, COL_TMO_UROV_2_COMMA, COL_TMO_UROV_2_END, 10);
                }
                //������� ����� �������� ����
                make_ekran_timeout_urov(group);
              }
              else if(current_ekran.current_level == EKRAN_CONTROL_UROV)
              {
                current_ekran.index_position--;
                
                if(current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_CONTROL_UROV - 1;
                position_in_current_level_menu[EKRAN_CONTROL_UROV] = current_ekran.index_position;

                //������� ����� ����������� ���������� ��� ����
                make_ekran_control_urov();
              }
              else if(
                      (current_ekran.current_level >= EKRAN_SETPOINT_ZOP_GROUP1) &&
                      (current_ekran.current_level <= EKRAN_SETPOINT_ZOP_GROUP4)
                     )   
              {
                int group = (current_ekran.current_level - EKRAN_SETPOINT_ZOP_GROUP1);
                
                if(current_ekran.edition == 0)
                {
                  if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_SETPOINT_ZOP - 1;
                  position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;
                }
                else
                {
                  //����������� �����
                  edition_settings.setpoint_zop[group] = edit_setpoint(1, edition_settings.setpoint_zop[group], 1, COL_SETPOINT_ZOP_COMMA, COL_SETPOINT_ZOP_END, 1);
                }
                //������� ����� ������� ����
                make_ekran_setpoint_zop(group);
              }
              else if(
                      (current_ekran.current_level >= EKRAN_TIMEOUT_ZOP_GROUP1) &&
                      (current_ekran.current_level <= EKRAN_TIMEOUT_ZOP_GROUP4)
                     )   
              {
                int group = (current_ekran.current_level - EKRAN_TIMEOUT_ZOP_GROUP1);
                
                if(current_ekran.edition == 0)
                {
                  if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_TIMEOUT_ZOP - 1;
                  position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;
                }
                else
                {
                  //����������� �����
                  edition_settings.timeout_zop[group] = edit_setpoint(1, edition_settings.timeout_zop[group], 1, COL_TMO_ZOP_COMMA, COL_TMO_ZOP_END, 10);
                }
                //������� ����� �������� ���(���)
                make_ekran_timeout_zop(group);
              }
              else if(current_ekran.current_level == EKRAN_CONTROL_ZOP)
              {
                if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_CONTROL_ZOP - 1;
                position_in_current_level_menu[EKRAN_CONTROL_ZOP] = current_ekran.index_position;
                //������� ����� ����������� ���������� ��� ���(���)
                make_ekran_control_zop();
              }
              else if(
                      (current_ekran.current_level >= EKRAN_SETPOINT_UMIN_GROUP1) &&
                      (current_ekran.current_level <= EKRAN_SETPOINT_UMIN_GROUP4)
                     )   
              {
                int group = (current_ekran.current_level - EKRAN_SETPOINT_UMIN_GROUP1);
                
                if(current_ekran.edition == 0)
                {
                  if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_SETPOINT_UMIN - 1;
                  position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;
                }
                else
                {
                  //����������� �����
                  if (current_ekran.index_position == INDEX_ML_STPUMIN1)
                    edition_settings.setpoint_Umin1[group] = edit_setpoint(1, edition_settings.setpoint_Umin1[group], 1, COL_SETPOINT_UMIN1_COMMA, COL_SETPOINT_UMIN1_END, 100);
                  else if (current_ekran.index_position == INDEX_ML_STPUMIN1_IBLK)
                    edition_settings.setpoint_Umin1_Iblk[group] = edit_setpoint(1, edition_settings.setpoint_Umin1_Iblk[group], 1, COL_SETPOINT_UMIN1_IBLK_COMMA, COL_SETPOINT_UMIN1_IBLK_END, 10);
                  else if (current_ekran.index_position == INDEX_ML_STPUMIN2)
                    edition_settings.setpoint_Umin2[group] = edit_setpoint(1, edition_settings.setpoint_Umin2[group], 1, COL_SETPOINT_UMIN2_COMMA, COL_SETPOINT_UMIN2_END, 100);
                  else if (current_ekran.index_position == INDEX_ML_STPUMIN2_IBLK)
                    edition_settings.setpoint_Umin2_Iblk[group] = edit_setpoint(1, edition_settings.setpoint_Umin2_Iblk[group], 1, COL_SETPOINT_UMIN2_IBLK_COMMA, COL_SETPOINT_UMIN2_IBLK_END, 10);
                }
                //������� ����� ������� Umin
                make_ekran_setpoint_Umin(group);
              }
              else if(
                      (current_ekran.current_level >= EKRAN_TIMEOUT_UMIN_GROUP1) &&
                      (current_ekran.current_level <= EKRAN_TIMEOUT_UMIN_GROUP4)
                     )   
              {
                int group = (current_ekran.current_level - EKRAN_TIMEOUT_UMIN_GROUP1);

                if(current_ekran.edition == 0)
                {
                  if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_TIMEOUT_UMIN - 1;
                  position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;
                }
                else
                {
                  //����������� �����
                  if (current_ekran.index_position == INDEX_ML_TMOUMIN1)
                    edition_settings.timeout_Umin1[group] = edit_setpoint(1, edition_settings.timeout_Umin1[group], 1, COL_TMO_UMIN1_COMMA, COL_TMO_UMIN1_END, 10);
                  else if (current_ekran.index_position == INDEX_ML_TMOUMIN2)
                    edition_settings.timeout_Umin2[group] = edit_setpoint(1, edition_settings.timeout_Umin2[group], 1, COL_TMO_UMIN2_COMMA, COL_TMO_UMIN2_END, 10);
                }
                //������� ����� �������� Umin
                make_ekran_timeout_Umin(group);
              }
              else if(current_ekran.current_level == EKRAN_CONTROL_UMIN)
              {
                if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_CONTROL_UMIN - 1;
                position_in_current_level_menu[EKRAN_CONTROL_UMIN] = current_ekran.index_position;
                //������� ����� ����������� ���������� ��� Umin
                make_ekran_control_Umin();
              }
              else if(
                      (current_ekran.current_level >= EKRAN_SETPOINT_UMAX_GROUP1) &&
                      (current_ekran.current_level <= EKRAN_SETPOINT_UMAX_GROUP4)
                     )   
              {
                int group = (current_ekran.current_level - EKRAN_SETPOINT_UMAX_GROUP1);
                
                if(current_ekran.edition == 0)
                {
                  if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_SETPOINT_UMAX - 1;
                  position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;
                }
                else
                {
                  //����������� �����
                  if (current_ekran.index_position == INDEX_ML_STPUMAX1)
                    edition_settings.setpoint_Umax1[group] = edit_setpoint(1, edition_settings.setpoint_Umax1[group], 1, COL_SETPOINT_UMAX1_COMMA, COL_SETPOINT_UMAX1_END, 100);
                  else if (current_ekran.index_position == INDEX_ML_STPUMAX2)
                    edition_settings.setpoint_Umax2[group] = edit_setpoint(1, edition_settings.setpoint_Umax2[group], 1, COL_SETPOINT_UMAX2_COMMA, COL_SETPOINT_UMAX2_END, 100);
                }
                //������� ����� ������� Umax
                make_ekran_setpoint_Umax(group);
              }
              else if(
                      (current_ekran.current_level >= EKRAN_TIMEOUT_UMAX_GROUP1) &&
                      (current_ekran.current_level <= EKRAN_TIMEOUT_UMAX_GROUP4)
                     )   
              {
                int group = (current_ekran.current_level - EKRAN_TIMEOUT_UMAX_GROUP1);

                if(current_ekran.edition == 0)
                {
                  if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_TIMEOUT_UMAX - 1;
                  position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;
                }
                else
                {
                  //����������� �����
                  if (current_ekran.index_position == INDEX_ML_TMOUMAX1)
                    edition_settings.timeout_Umax1[group] = edit_setpoint(1, edition_settings.timeout_Umax1[group], 1, COL_TMO_UMAX1_COMMA, COL_TMO_UMAX1_END, 10);
                  else if (current_ekran.index_position == INDEX_ML_TMOUMAX2)
                    edition_settings.timeout_Umax2[group] = edit_setpoint(1, edition_settings.timeout_Umax2[group], 1, COL_TMO_UMAX2_COMMA, COL_TMO_UMAX2_END, 10);
                }
                //������� ����� �������� Umax
                make_ekran_timeout_Umax(group);
              }
              else if(current_ekran.current_level == EKRAN_CONTROL_UMAX)
              {
                if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_CONTROL_UMAX - 1;
                position_in_current_level_menu[EKRAN_CONTROL_UMAX] = current_ekran.index_position;
                //������� ����� ����������� ���������� ��� Umax
                make_ekran_control_Umax();
              }
              else if(
                      (current_ekran.current_level >= EKRAN_SETPOINT_AVR_UMIN_GROUP1) &&
                      (current_ekran.current_level <= EKRAN_SETPOINT_AVR_UMIN_GROUP4)
                     )   
              {
                int group = (current_ekran.current_level - EKRAN_SETPOINT_AVR_UMIN_GROUP1);
                
                if(current_ekran.edition == 0)
                {
                  if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_SETPOINT_AVR_UMIN - 1;
                  position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;
                }
                else
                {
                  //����������� �����
                  if (current_ekran.index_position == INDEX_ML_STPAVR_TN1_U1_UMIN)
                    edition_settings.setpoint_avr_tn1_U1_Umin[group] = edit_setpoint(1, edition_settings.setpoint_avr_tn1_U1_Umin[group], 1, COL_SETPOINT_AVR_TN1_U1_UMIN_COMMA, COL_SETPOINT_AVR_TN1_U1_UMIN_END, 100);
                  else if (current_ekran.index_position == INDEX_ML_STPAVR_TN1_U2_LOW_WORK)
                    edition_settings.setpoint_avr_tn1_U2_low_work[group] = edit_setpoint(1, edition_settings.setpoint_avr_tn1_U2_low_work[group], 1, COL_SETPOINT_AVR_TN1_U2_LOW_WORK_COMMA, COL_SETPOINT_AVR_TN1_U2_LOW_WORK_END, 100);
                  else if (current_ekran.index_position == INDEX_ML_STPAVR_TN2_U2_UMIN)
                    edition_settings.setpoint_avr_tn2_U2_Umin[group] = edit_setpoint(1, edition_settings.setpoint_avr_tn2_U2_Umin[group], 1, COL_SETPOINT_AVR_TN2_U2_UMIN_COMMA, COL_SETPOINT_AVR_TN2_U2_UMIN_END, 100);
                  else if (current_ekran.index_position == INDEX_ML_STPAVR_TN2_U1_LOW_WORK)
                    edition_settings.setpoint_avr_tn2_U1_low_work[group] = edit_setpoint(1, edition_settings.setpoint_avr_tn2_U1_low_work[group], 1, COL_SETPOINT_AVR_TN2_U1_LOW_WORK_COMMA, COL_SETPOINT_AVR_TN2_U1_LOW_WORK_END, 100);
                }
                //������� ����� ������� ��� Umin
                make_ekran_setpoint_avr_Umin(group);
              }
              else if(
                      (current_ekran.current_level >= EKRAN_SETPOINT_AVR_UMAX_GROUP1) &&
                      (current_ekran.current_level <= EKRAN_SETPOINT_AVR_UMAX_GROUP4)
                     )   
              {
                int group = (current_ekran.current_level - EKRAN_SETPOINT_AVR_UMAX_GROUP1);
                
                if(current_ekran.edition == 0)
                {
                  if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_SETPOINT_AVR_UMAX - 1;
                  position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;
                }
                else
                {
                  //����������� �����
                  if (current_ekran.index_position == INDEX_ML_STPAVR_TN1_U1_UMAX)
                    edition_settings.setpoint_avr_tn1_U1_Umax[group] = edit_setpoint(1, edition_settings.setpoint_avr_tn1_U1_Umax[group], 1, COL_SETPOINT_AVR_TN1_U1_UMAX_COMMA, COL_SETPOINT_AVR_TN1_U1_UMAX_END, 100);
                  else if (current_ekran.index_position == INDEX_ML_STPAVR_TN1_U2_HIGH_WORK)
                    edition_settings.setpoint_avr_tn1_U2_high_work[group] = edit_setpoint(1, edition_settings.setpoint_avr_tn1_U2_high_work[group], 1, COL_SETPOINT_AVR_TN1_U2_HIGH_WORK_COMMA, COL_SETPOINT_AVR_TN1_U2_HIGH_WORK_END, 100);
                  else if (current_ekran.index_position == INDEX_ML_STPAVR_TN2_U2_UMAX)
                    edition_settings.setpoint_avr_tn2_U2_Umax[group] = edit_setpoint(1, edition_settings.setpoint_avr_tn2_U2_Umax[group], 1, COL_SETPOINT_AVR_TN2_U2_UMAX_COMMA, COL_SETPOINT_AVR_TN2_U2_UMAX_END, 100);
                  else if (current_ekran.index_position == INDEX_ML_STPAVR_TN2_U1_HIGH_WORK)
                    edition_settings.setpoint_avr_tn2_U1_high_work[group] = edit_setpoint(1, edition_settings.setpoint_avr_tn2_U1_high_work[group], 1, COL_SETPOINT_AVR_TN2_U1_HIGH_WORK_COMMA, COL_SETPOINT_AVR_TN2_U1_HIGH_WORK_END, 100);
                }
                //������� ����� ������� ��� Umax
                make_ekran_setpoint_avr_Umax(group);
              }
              else if(
                      (current_ekran.current_level >= EKRAN_TIMEOUT_AVR_GENERAL_GROUP1) &&
                      (current_ekran.current_level <= EKRAN_TIMEOUT_AVR_GENERAL_GROUP4)
                     )   
              {
                int group = (current_ekran.current_level - EKRAN_TIMEOUT_AVR_GENERAL_GROUP1);

                if(current_ekran.edition == 0)
                {
                  if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_TIMEOUT_AVR_GENERAL - 1;
                  position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;
                }
                else
                {
                  //����������� �����
                  if (current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_BLK_K1)
                    edition_settings.timeout_avr_blk_k1[group] = edit_setpoint(1, edition_settings.timeout_avr_blk_k1[group], 1, COL_TMO_AVR_GENERAL_BLK_K1_COMMA, COL_TMO_AVR_GENERAL_BLK_K1_END, 10);
                  else if (current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_PUSK_K1)
                    edition_settings.timeout_avr_pusk_k1[group] = edit_setpoint(1, edition_settings.timeout_avr_pusk_k1[group], 1, COL_TMO_AVR_GENERAL_PUSK_K1_COMMA, COL_TMO_AVR_GENERAL_PUSK_K1_END, 10);
                  else if (current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_D_DIJI_K1)
                    edition_settings.timeout_avr_d_diji_k1[group] = edit_setpoint(1, edition_settings.timeout_avr_d_diji_k1[group], 1, COL_TMO_AVR_GENERAL_D_DIJI_K1_COMMA, COL_TMO_AVR_GENERAL_D_DIJI_K1_END, 10);
                  else if (current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_VVIMK_REZ_K1)
                    edition_settings.timeout_avr_vvimk_rez_k1[group] = edit_setpoint(1, edition_settings.timeout_avr_vvimk_rez_k1[group], 1, COL_TMO_AVR_GENERAL_VVIMK_REZ_K1_COMMA, COL_TMO_AVR_GENERAL_VVIMK_REZ_K1_END, 10);
                  else if (current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_VVIMK_K1)
                    edition_settings.timeout_avr_vvimk_k1[group] = edit_setpoint(1, edition_settings.timeout_avr_vvimk_k1[group], 1, COL_TMO_AVR_GENERAL_VVIMK_K1_COMMA, COL_TMO_AVR_GENERAL_VVIMK_K1_END, 10);
                  else if (current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_VYMK_K1)
                    edition_settings.timeout_avr_vymk_k1[group] = edit_setpoint(1, edition_settings.timeout_avr_vymk_k1[group], 1, COL_TMO_AVR_GENERAL_VYMK_K1_COMMA, COL_TMO_AVR_GENERAL_VYMK_K1_END, 10);
                  else if (current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_BLK_K2)
                    edition_settings.timeout_avr_blk_k2[group] = edit_setpoint(1, edition_settings.timeout_avr_blk_k2[group], 1, COL_TMO_AVR_GENERAL_BLK_K2_COMMA, COL_TMO_AVR_GENERAL_BLK_K2_END, 10);
                  else if (current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_PUSK_K2)
                    edition_settings.timeout_avr_pusk_k2[group] = edit_setpoint(1, edition_settings.timeout_avr_pusk_k2[group], 1, COL_TMO_AVR_GENERAL_PUSK_K2_COMMA, COL_TMO_AVR_GENERAL_PUSK_K2_END, 10);
                  else if (current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_D_DIJI_K2)
                    edition_settings.timeout_avr_d_diji_k2[group] = edit_setpoint(1, edition_settings.timeout_avr_d_diji_k2[group], 1, COL_TMO_AVR_GENERAL_D_DIJI_K2_COMMA, COL_TMO_AVR_GENERAL_D_DIJI_K2_END, 10);
                  else if (current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_VVIMK_REZ_K2)
                    edition_settings.timeout_avr_vvimk_rez_k2[group] = edit_setpoint(1, edition_settings.timeout_avr_vvimk_rez_k2[group], 1, COL_TMO_AVR_GENERAL_VVIMK_REZ_K2_COMMA, COL_TMO_AVR_GENERAL_VVIMK_REZ_K2_END, 10);
                  else if (current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_VVIMK_K2)
                    edition_settings.timeout_avr_vvimk_k2[group] = edit_setpoint(1, edition_settings.timeout_avr_vvimk_k2[group], 1, COL_TMO_AVR_GENERAL_VVIMK_K2_COMMA, COL_TMO_AVR_GENERAL_VVIMK_K2_END, 10);
                  else if (current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_VYMK_K2)
                    edition_settings.timeout_avr_vymk_k2[group] = edit_setpoint(1, edition_settings.timeout_avr_vymk_k2[group], 1, COL_TMO_AVR_GENERAL_VYMK_K2_COMMA, COL_TMO_AVR_GENERAL_VYMK_K2_END, 10);
                }
                //������� ����� �������� ��� (��������)
                make_ekran_timeout_avr_general(group);
              }
              else if(
                      (current_ekran.current_level >= EKRAN_TIMEOUT_AVR_UMIN_GROUP1) &&
                      (current_ekran.current_level <= EKRAN_TIMEOUT_AVR_UMIN_GROUP4)
                     )   
              {
                int group = (current_ekran.current_level - EKRAN_TIMEOUT_AVR_UMIN_GROUP1);

                if(current_ekran.edition == 0)
                {
                  if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_TIMEOUT_AVR_UMIN - 1;
                  position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;
                }
                else
                {
                  //����������� �����
                  if (current_ekran.index_position == INDEX_ML_TMOAVR_UMIN_VYMK_ROB_K1)
                    edition_settings.timeout_avr_vymk_rob_k1_Umin[group] = edit_setpoint(1, edition_settings.timeout_avr_vymk_rob_k1_Umin[group], 1, COL_TMO_AVR_UMIN_VYMK_ROB_K1_COMMA, COL_TMO_AVR_UMIN_VYMK_ROB_K1_END, 10);
                  else if (current_ekran.index_position == INDEX_ML_TMOAVR_UMIN_VYMK_ROB_K2)
                    edition_settings.timeout_avr_vymk_rob_k2_Umin[group] = edit_setpoint(1, edition_settings.timeout_avr_vymk_rob_k2_Umin[group], 1, COL_TMO_AVR_UMIN_VYMK_ROB_K2_COMMA, COL_TMO_AVR_UMIN_VYMK_ROB_K2_END, 10);
                }
                //������� ����� �������� ��� Umin
                make_ekran_timeout_avr_Umin(group);
              }
              else if(
                      (current_ekran.current_level >= EKRAN_TIMEOUT_AVR_UMAX_GROUP1) &&
                      (current_ekran.current_level <= EKRAN_TIMEOUT_AVR_UMAX_GROUP4)
                     )   
              {
                int group = (current_ekran.current_level - EKRAN_TIMEOUT_AVR_UMAX_GROUP1);

                if(current_ekran.edition == 0)
                {
                  if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_TIMEOUT_AVR_UMAX - 1;
                  position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;
                }
                else
                {
                  //����������� �����
                  if (current_ekran.index_position == INDEX_ML_TMOAVR_UMAX_VYMK_ROB_K1)
                    edition_settings.timeout_avr_vymk_rob_k1_Umax[group] = edit_setpoint(1, edition_settings.timeout_avr_vymk_rob_k1_Umax[group], 1, COL_TMO_AVR_UMAX_VYMK_ROB_K1_COMMA, COL_TMO_AVR_UMAX_VYMK_ROB_K1_END, 10);
                  else if (current_ekran.index_position == INDEX_ML_TMOAVR_UMAX_VYMK_ROB_K2)
                    edition_settings.timeout_avr_vymk_rob_k2_Umax[group] = edit_setpoint(1, edition_settings.timeout_avr_vymk_rob_k2_Umax[group], 1, COL_TMO_AVR_UMAX_VYMK_ROB_K2_COMMA, COL_TMO_AVR_UMAX_VYMK_ROB_K2_END, 10);
                }
                //������� ����� �������� ��� Umax
                make_ekran_timeout_avr_Umax(group);
              }
              else if(current_ekran.current_level == EKRAN_CONTROL_AVR)
              {
                if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_CONTROL_AVR - 1;
                position_in_current_level_menu[EKRAN_CONTROL_AVR] = current_ekran.index_position;
                //������� ����� ����������� ���������� ��� ���
                make_ekran_control_avr();
              }
              else if(
                      (current_ekran.current_level >= EKRAN_SETPOINT_CTRL_PHASE_GROUP1) &&
                      (current_ekran.current_level <= EKRAN_SETPOINT_CTRL_PHASE_GROUP4)
                     )   
              {
                int group = (current_ekran.current_level - EKRAN_SETPOINT_CTRL_PHASE_GROUP1);
                
                if(current_ekran.edition == 0)
                {
                  if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_SETPOINT_CTRL_PHASE - 1;
                  position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;
                }
                else
                {
                  //����������� �����
                  if (current_ekran.index_position == INDEX_ML_STPCTRL_PHASE_U)
                    edition_settings.setpoint_ctrl_phase_U[group] = edit_setpoint(1, edition_settings.setpoint_ctrl_phase_U[group], 1, COL_SETPOINT_CTRL_PHASE_U_COMMA, COL_SETPOINT_CTRL_PHASE_U_END, 100);
                  else if (current_ekran.index_position == INDEX_ML_STPCTRL_PHASE_PHI)
                    edition_settings.setpoint_ctrl_phase_phi[group] = edit_setpoint(1, edition_settings.setpoint_ctrl_phase_phi[group], 1, COL_SETPOINT_CTRL_PHASE_PHI_COMMA, COL_SETPOINT_CTRL_PHASE_PHI_END, 1);
                  else if (current_ekran.index_position == INDEX_ML_STPCTRL_PHASE_F)
                    edition_settings.setpoint_ctrl_phase_f[group] = edit_setpoint(1, edition_settings.setpoint_ctrl_phase_f[group], 1, COL_SETPOINT_CTRL_PHASE_F_COMMA, COL_SETPOINT_CTRL_PHASE_F_END, 10);
                }
                //������� ����� ������� "�������� ���"
                make_ekran_setpoint_ctrl_phase(group);
              }
              else if(
                      (current_ekran.current_level >= EKRAN_TIMEOUT_CTRL_PHASE_GROUP1) &&
                      (current_ekran.current_level <= EKRAN_TIMEOUT_CTRL_PHASE_GROUP4)
                     )   
              {
                int group = (current_ekran.current_level - EKRAN_TIMEOUT_CTRL_PHASE_GROUP1);

                if(current_ekran.edition == 0)
                {
                  if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_TIMEOUT_CTRL_PHASE - 1;
                  position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;
                }
                else
                {
                  //����������� �����
                  if (current_ekran.index_position == INDEX_ML_TMOCTRL_PHASE_U)
                    edition_settings.timeout_ctrl_phase_U[group] = edit_setpoint(1, edition_settings.timeout_ctrl_phase_U[group], 1, COL_TMO_CTRL_PHASE_U_COMMA, COL_TMO_CTRL_PHASE_U_END, 10);
                  else if (current_ekran.index_position == INDEX_ML_TMOCTRL_PHASE_U_D)
                    edition_settings.timeout_ctrl_phase_U_d[group] = edit_setpoint(1, edition_settings.timeout_ctrl_phase_U_d[group], 1, COL_TMO_CTRL_PHASE_U_D_COMMA, COL_TMO_CTRL_PHASE_U_D_END, 10);
                  else if (current_ekran.index_position == INDEX_ML_TMOCTRL_PHASE_PHI)
                    edition_settings.timeout_ctrl_phase_phi[group] = edit_setpoint(1, edition_settings.timeout_ctrl_phase_phi[group], 1, COL_TMO_CTRL_PHASE_PHI_COMMA, COL_TMO_CTRL_PHASE_PHI_END, 10);
                  else if (current_ekran.index_position == INDEX_ML_TMOCTRL_PHASE_PHI_D)
                    edition_settings.timeout_ctrl_phase_phi_d[group] = edit_setpoint(1, edition_settings.timeout_ctrl_phase_phi_d[group], 1, COL_TMO_CTRL_PHASE_PHI_D_COMMA, COL_TMO_CTRL_PHASE_PHI_D_END, 10);
                  else if (current_ekran.index_position == INDEX_ML_TMOCTRL_PHASE_F)
                    edition_settings.timeout_ctrl_phase_f[group] = edit_setpoint(1, edition_settings.timeout_ctrl_phase_f[group], 1, COL_TMO_CTRL_PHASE_F_COMMA, COL_TMO_CTRL_PHASE_F_END, 10);
                  else if (current_ekran.index_position == INDEX_ML_TMOCTRL_PHASE_F_D)
                    edition_settings.timeout_ctrl_phase_f_d[group] = edit_setpoint(1, edition_settings.timeout_ctrl_phase_f_d[group], 1, COL_TMO_CTRL_PHASE_F_D_COMMA, COL_TMO_CTRL_PHASE_F_D_END, 10);
                }
                //������� ����� �������� "�������� ���"
                make_ekran_timeout_ctrl_phase(group);
              }
              else if(current_ekran.current_level == EKRAN_CONTROL_CTRL_PHASE)
              {
                if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_CONTROL_CTRL_PHASE - 1;
                position_in_current_level_menu[EKRAN_CONTROL_CTRL_PHASE] = current_ekran.index_position;
                //������� ����� ����������� ���������� ��� "�������� ���"
                make_ekran_control_ctrl_phase();
              }
              else if(current_ekran.current_level == EKRAN_TRANSFORMATOR_INFO_SETPOINT)
              {
                if(current_ekran.edition == 0)
                {
                  if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_TRANSFORMATOR_INFO_SETPOINT - 1;
                  position_in_current_level_menu[EKRAN_TRANSFORMATOR_INFO_SETPOINT] = current_ekran.index_position;
                }
                else
                {
                  //����������� �����
                  if (current_ekran.index_position == INDEX_ML_TT)
                    edition_settings.TCurrent = edit_setpoint(1, edition_settings.TCurrent, 0, 0, COL_TT_END, 1);
                  else
                    edition_settings.TVoltage = edit_setpoint(1, edition_settings.TVoltage, 0, 0, COL_TN_END, 1);
                }
                //������� ����� ���������� �� ���������������
                make_ekran_transformator();
              }
              else if(current_ekran.current_level == EKRAN_TRANSFORMATOR_INFO_CONTROL)
              {
                if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_TRANSFORMATOR_INFO_CONTROL - 1;
                position_in_current_level_menu[EKRAN_TRANSFORMATOR_INFO_CONTROL] = current_ekran.index_position;
                //������� ����� ����������� ����������� ���� "�������������"
                make_ekran_transformator_control();
              }
              else if(current_ekran.current_level == EKRAN_SETPOINT_SWITCH)
              {
                if(current_ekran.edition == 0)
                {
                  if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_SETPOINT_SWITCH - 1;
                  position_in_current_level_menu[EKRAN_SETPOINT_SWITCH] = current_ekran.index_position;
                }
                else
                {
                  //����������� �����
                  if (current_ekran.index_position == INDEX_ML_STPInom)
                    edition_settings.setpoint_Inom = edit_setpoint(1, edition_settings.setpoint_Inom, 0, 0, COL_SETPOINT_Inom_END, 1);
                  if (current_ekran.index_position == INDEX_ML_STPRKS_Inom)
                    edition_settings.setpoint_r_kom_st_Inom = edit_setpoint(1, edition_settings.setpoint_r_kom_st_Inom, 0, 0, COL_SETPOINT_RKS_Inom_END, 1);
                  else if (current_ekran.index_position == INDEX_ML_STPMInom_vymk)
                    edition_settings.setpoint_Inom_vymk = edit_setpoint(1, edition_settings.setpoint_Inom_vymk, 1, COL_SETPOINT_Inom_vymk_COMMA, COL_SETPOINT_Inom_vymk_END, 1);
                  else if (current_ekran.index_position == INDEX_ML_STPRKS_Inom_vymk)
                    edition_settings.setpoint_r_kom_st_Inom_vymk = edit_setpoint(1, edition_settings.setpoint_r_kom_st_Inom_vymk, 0, 0, COL_SETPOINT_RKS_Inom_vymk_END, 1);
                  else if (current_ekran.index_position == INDEX_ML_STPPOCHATKOVYJ_RESURS)
                    edition_settings.setpoint_pochatkovyj_resurs = edit_setpoint(1, edition_settings.setpoint_pochatkovyj_resurs, 0, 0, COL_SETPOINT_POCHATKOVYJ_RESURS_END, 1);
                  else if (current_ekran.index_position == INDEX_ML_STPKRYTYCHNYJ_RESURS)
                    edition_settings.setpoint_krytychnyj_resurs = edit_setpoint(1, edition_settings.setpoint_krytychnyj_resurs, 0, 0, COL_SETPOINT_KRYTYCHNYJ_RESURS_END, 1);
                  else if (current_ekran.index_position == INDEX_ML_STPPOCHATKOVA_K_VYMK)
                    edition_settings.setpoint_pochatkova_k_vymk = edit_setpoint(1, edition_settings.setpoint_pochatkova_k_vymk, 0, 0, COL_SETPOINT_POCHATKOVA_K_VYMK_END, 1);
                }
                //������� ����� ������� �����������
                make_ekran_setpoint_switch();
              }
              else if(current_ekran.current_level == EKRAN_TIMEOUT_SWITCH)
              {
                if(current_ekran.edition == 0)
                {
                  if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_TIMEOUT_SWITCH - 1;
                  position_in_current_level_menu[EKRAN_TIMEOUT_SWITCH] = current_ekran.index_position;
                }
                else
                {
                  //����������� �����
                  if (current_ekran.index_position == INDEX_ML_TMOON)
                    edition_settings.timeout_swch_on = edit_setpoint(1, edition_settings.timeout_swch_on, 1, COL_TMO_SWCH_ON_COMMA, COL_TMO_SWCH_ON_END, 10);
                  else if (current_ekran.index_position == INDEX_ML_TMOOFF)
                    edition_settings.timeout_swch_off = edit_setpoint(1, edition_settings.timeout_swch_off, 1, COL_TMO_SWCH_OFF_COMMA, COL_TMO_SWCH_OFF_END, 10);
                  else if (current_ekran.index_position == INDEX_ML_TMOUDL_BLK_ON)
                    edition_settings.timeout_swch_udl_blk_on = edit_setpoint(1, edition_settings.timeout_swch_udl_blk_on, 1, COL_TMO_SWCH_UDL_BLK_ON_COMMA, COL_TMO_SWCH_UDL_BLK_ON_END, 10);
                  else if (current_ekran.index_position == INDEX_ML_TMOPRYVODA_VV)
                    edition_settings.timeout_pryvoda_VV = edit_setpoint(1, edition_settings.timeout_pryvoda_VV, 1, COL_TMO_PRYVODA_VV_COMMA, COL_TMO_PRYVODA_VV_END, 10);
                }
                //������� ����� �������� �����������
                make_ekran_timeout_switch();
              }
              else if(current_ekran.current_level == EKRAN_CONTROL_SWITCH)
              {
                if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_CONTROL_SWITCH - 1;
                position_in_current_level_menu[EKRAN_CONTROL_SWITCH] = current_ekran.index_position;
                //������� ����� ����������� ���������� ��� ��������
                make_ekran_control_switch();
              }
              else if(current_ekran.current_level == EKRAN_DOPUSK_DV_UVV)
              {
                if(current_ekran.edition == 0)
                {
                  if(--current_ekran.index_position < 0) current_ekran.index_position = NUMBER_INPUTS - 1;
                  position_in_current_level_menu[EKRAN_DOPUSK_DV_UVV] = current_ekran.index_position;
                }
                else
                {
                  //����������� �����
                  edition_settings.dopusk_dv[current_ekran.index_position] = 
                    edit_setpoint(1, edition_settings.dopusk_dv[current_ekran.index_position], 0, 0, COL_DOPUSK_DV_END, 1);
                }
                //������� ����� ���������� �� �������� ��
                make_ekran_dopusk_dv();
              }
              else if((current_ekran.current_level == EKRAN_TYPE_INPUT_UVV) || (current_ekran.current_level == EKRAN_TYPE_INPUT_SIGNAL_UVV))
              {
                if(--current_ekran.index_position < 0) current_ekran.index_position = NUMBER_INPUTS - 1;
                position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;
                //������� ����� ����������� ���������� ��� ���
                if (current_ekran.current_level == EKRAN_TYPE_INPUT_UVV)
                  make_ekran_type_input_uvv(0);
                else
                  make_ekran_type_input_uvv(1);
              }
              else if(current_ekran.current_level == EKRAN_TYPE_OUTPUT_UVV)
              {
                if(--current_ekran.index_position < 0) current_ekran.index_position = NUMBER_OUTPUTS - 1;
                position_in_current_level_menu[EKRAN_TYPE_OUTPUT_UVV] = current_ekran.index_position;
                //������� ����� ���� ������
                make_ekran_type_output_uvv();
              }
              else if(current_ekran.current_level == EKRAN_TYPE_LED_UVV)
              {
                if(--current_ekran.index_position < 0) current_ekran.index_position = NUMBER_LEDS - 1;
                position_in_current_level_menu[EKRAN_TYPE_LED_UVV] = current_ekran.index_position;
                //������� ����� ���� ��������������
                make_ekran_type_led_uvv();
              }
              else if(current_ekran.current_level == EKRAN_ADDRESS)
              {
                if(current_ekran.edition == 0)
                {
                  if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_ADDRESS - 1;
                  position_in_current_level_menu[EKRAN_ADDRESS] = current_ekran.index_position;
                }
                else
                {
                  //����������� �����
                  edition_settings.address = edit_setpoint(1, edition_settings.address, 0, 0, COL_ADDRESS_END, 1);
                }
                //������� ����� ���������� �� �������������� �����
                make_ekran_address();
              }
              else if(current_ekran.current_level == EKRAN_VIEW_SPEED_RS485)
              {
                if(current_ekran.edition == 0)
                {
                  if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_VIEW_SPEED_INTERFACE - 1;
                  position_in_current_level_menu[EKRAN_VIEW_SPEED_RS485] = current_ekran.index_position;
                }
                else
                {
                  //����������� �����
                  edition_settings.speed_RS485--;
                  if (edition_settings.speed_RS485 < VALUE_SPEED_INTERFACE_MIN)
                    edition_settings.speed_RS485 = VALUE_SPEED_INTERFACE_MAX;
                }
                //������� ����� ���������� �� �������� �����
                make_ekran_speed_interface();
              }
              else if(current_ekran.current_level == EKRAN_VIEW_PARE_RS485)
              {
                if(current_ekran.edition == 0)
                {
                  if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_VIEW_PARE_INTERFACE - 1;
                  position_in_current_level_menu[EKRAN_VIEW_PARE_RS485] = current_ekran.index_position;
                }
                else
                {
                  //����������� �����
                  edition_settings.pare_bit_RS485--;
                  if (edition_settings.pare_bit_RS485 < VALUE_PARE_INTERFACE_MIN)
                    edition_settings.pare_bit_RS485 = VALUE_PARE_INTERFACE_MAX;
                }
                //������� ����� ���������� �� �������� �������
                make_ekran_pare_interface();
              }
              else if(current_ekran.current_level == EKRAN_VIEW_STOP_BITS_RS485)
              {
                if(current_ekran.edition == 0)
                {
                  if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_VIEW_STOP_BITS_INTERFACE - 1;
                  position_in_current_level_menu[EKRAN_VIEW_STOP_BITS_RS485] = current_ekran.index_position;
                }
                else
                {
                  //����������� �����
                  edition_settings.number_stop_bit_RS485--;
                  if (edition_settings.number_stop_bit_RS485 < VALUE_STOP_BITS_INTERFACE_MIN)
                    edition_settings.number_stop_bit_RS485 = VALUE_STOP_BITS_INTERFACE_MAX;
                }
                //������� ����� ���������� �� ������� �������� ��
                make_ekran_stopbits_interface();
              }
              else if(current_ekran.current_level == EKRAN_VIEW_TIMEOUT_RS485)
              {
                if(current_ekran.edition == 0)
                {
                  if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_VIEW_TIMEOUT_INTERFACE - 1;
                  position_in_current_level_menu[EKRAN_VIEW_TIMEOUT_RS485] = current_ekran.index_position;
                }
                else
                {
                  //����������� �����
                  edition_settings.time_out_1_RS485 = edit_setpoint(1, edition_settings.time_out_1_RS485, 1, COL_TIMEOUT_INTERFACE_COMMA, COL_TIMEOUT_INTERFACE_END, 1);
                }
                //������� ����� ���������� �� time-out ���������� �������
                make_ekran_timeout_interface();
              }
              else if(current_ekran.current_level == EKRAN_GENERAL_PICKUPS_EL)
              {
                if(current_ekran.edition == 0)
                {
                  if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_GENERAL_PICKUPS_EL - 1;
                  position_in_current_level_menu[EKRAN_GENERAL_PICKUPS_EL] = current_ekran.index_position;
                }
                else
                {
                  //����������� �����
                  if (current_ekran.index_position == INDEX_ML_NUMBER_INERATION)
                  {
                    edition_settings.number_iteration_el = edit_setpoint(1, edition_settings.number_iteration_el, 0, 0, COL_NUMBER_INERATION_END, 1);
                  }
//                  else if (current_ekran.index_position == INDEX_ML_NUMBER_DEFINED_FUNCTIONS)
//                  {
//                    edition_settings.number_defined_df = edit_setpoint(1, edition_settings.number_defined_df, 0, 0, COL_NUMBER_DEFINED_FUNCTIONS_END, 1);
//                  }
//                  else if (current_ekran.index_position == INDEX_ML_NUMBER_DEFINED_TRIGGERS)
//                  {
//                    edition_settings.number_defined_dt = edit_setpoint(1, edition_settings.number_defined_dt, 0, 0, COL_NUMBER_DEFINED_TRIGGERS_END, 1);
//                  }
//                  else if (current_ekran.index_position == INDEX_ML_NUMBER_DEFINED_AND)
//                  {
//                    edition_settings.number_defined_and = edit_setpoint(1, edition_settings.number_defined_and, 0, 0, COL_NUMBER_DEFINED_AND_END, 1);
//                  }
//                  else if (current_ekran.index_position == INDEX_ML_NUMBER_DEFINED_OR)
//                  {
//                    edition_settings.number_defined_or = edit_setpoint(1, edition_settings.number_defined_or, 0, 0, COL_NUMBER_DEFINED_OR_END, 1);
//                  }
//                  else if (current_ekran.index_position == INDEX_ML_NUMBER_DEFINED_XOR)
//                  {
//                    edition_settings.number_defined_xor = edit_setpoint(1, edition_settings.number_defined_xor, 0, 0, COL_NUMBER_DEFINED_XOR_END, 1);
//                  }
//                  else if (current_ekran.index_position == INDEX_ML_NUMBER_DEFINED_NOT)
//                  {
//                    edition_settings.number_defined_not = edit_setpoint(1, edition_settings.number_defined_not, 0, 0, COL_NUMBER_DEFINED_NOT_END, 1);
//                  }
                }
                //������� ����� ����������� ��������� �������� ��� ��������� �����
                make_ekran_general_pickups_el();
              }
              else if(current_ekran.current_level == EKRAN_LIST_TYPE_DF)
              {
                if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_TYPE_DF - 1;
                position_in_current_level_menu[EKRAN_LIST_TYPE_DF] = current_ekran.index_position;
                //������� ����� ����������� ���� ������������� �������
                make_ekran_type_df();
              }
              else if((current_ekran.current_level >= EKRAN_TIMEOUT_DF1) && (current_ekran.current_level <= EKRAN_TIMEOUT_DF8))
              {
                if(current_ekran.edition == 0)
                {
                  if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_TIMEOUT_DF - 1;
                  position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;
                }
                else
                {
                  //����������� �����
                  if (current_ekran.index_position == INDEX_ML_TMO_DF_PAUSE)
                    edition_settings.timeout_pause_df[current_ekran.current_level - EKRAN_TIMEOUT_DF1] = 
                      edit_setpoint(1, edition_settings.timeout_pause_df[current_ekran.current_level - EKRAN_TIMEOUT_DF1], 1, COL_TMO_DF_PAUSE_COMMA, COL_TMO_DF_PAUSE_END, 10);
                  else
                    edition_settings.timeout_work_df[current_ekran.current_level - EKRAN_TIMEOUT_DF1] = 
                      edit_setpoint(1, edition_settings.timeout_work_df[current_ekran.current_level - EKRAN_TIMEOUT_DF1], 1, COL_TMO_DF_WORK_COMMA, COL_TMO_DF_WORK_END, 10);
                }
                //������� ����� ������� ������������ �������
                make_ekran_timeout_df(current_ekran.current_level - EKRAN_TIMEOUT_DF1);
              }
              else if(current_ekran.current_level == EKRAN_TIMEOUT_ANALOG_REGISTRATOR)
              {
                if(current_ekran.edition == 0)
                {
                  if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_TIMEOUT_ANALOG_REGISTRATOR - 1;
                  position_in_current_level_menu[EKRAN_TIMEOUT_ANALOG_REGISTRATOR] = current_ekran.index_position;
                }
                else
                {
                  //����������� �����
                  if (current_ekran.index_position == INDEX_ML_TMOPREFAULT)
                  {
                    unsigned int temp_setpoint = edition_settings.prefault_number_periods*20;
                    do
                    {
                      //�������� �������� �������� ��������� �� 10 �� (�-��� edit_setpoint ������/������ � ������ ������� 1, 10 � �.�.), ��� �������� ���� 20 ��
                      temp_setpoint = edit_setpoint(1, temp_setpoint, 1, COL_TMO_PREFAULT_COMMA, COL_TMO_PREFAULT_END, 10);
                    }
                    while ((temp_setpoint % 20) != 0);
                    edition_settings.prefault_number_periods = temp_setpoint / 20;
                  }
                  else
                  {
                    unsigned int temp_setpoint = edition_settings.postfault_number_periods*20;
                    do
                    {
                      //�������� �������� �������� ��������� �� 10 �� (�-��� edit_setpoint ������/������ � ������ ������� 1, 10 � �.�.), ��� �������� ���� 20 ��
                      temp_setpoint = edit_setpoint(1, temp_setpoint, 1, COL_TMO_PREFAULT_COMMA, COL_TMO_PREFAULT_END, 10);
                    }
                    while ((temp_setpoint % 20) != 0);
                    edition_settings.postfault_number_periods = temp_setpoint / 20;
                  }
                }
                //������� ����� �������� ����������� ����������
                make_ekran_timeout_analog_registrator();
              }
              else if(current_ekran.current_level == EKRAN_VIEW_SETTING_LANGUAGE)
              {
                if(current_ekran.edition == 0)
                {
                  if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_VIEW_SETTING_LANGUAGE - 1;
                  position_in_current_level_menu[EKRAN_VIEW_SETTING_LANGUAGE] = current_ekran.index_position;
                }
                else
                {
                  //����������� �����
                  edition_settings.language--;
                  if (edition_settings.language < VALUE_SETTING_LANGUAGE_MIN)
                    edition_settings.language = VALUE_SETTING_LANGUAGE_MAX;
                }
                //������� ����� ���������� �� ��� ����
                make_ekran_setting_language();
              }
              else if(current_ekran.current_level == EKRAN_CHOSE_EXTRA_SETTINGS)
              {
                if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_CHOSE_EXTRA_SETTINGS - 1;
                position_in_current_level_menu[EKRAN_CHOSE_EXTRA_SETTINGS] = current_ekran.index_position;
                //������� ����� ����������� ���������� �����������
                make_ekran_chose_extra_settings();
              }

              //�������� �����������, �� ��������� ������ 
              new_state_keyboard &= (unsigned int)(~(1<<BIT_KEY_UP));
            }
            else if (new_state_keyboard == (1<<BIT_KEY_DOWN))
            {
              //��������� ������ DOWN
              if (current_ekran.current_level == EKRAN_CONTROL_ZDZ)
              {
                current_ekran.index_position++;
                
                if(current_ekran.index_position >= MAX_ROW_FOR_CONTROL_ZDZ) current_ekran.index_position = 0;
                position_in_current_level_menu[EKRAN_CONTROL_ZDZ] = current_ekran.index_position;
                
                //������� ����� ����������� ���������� ��� ���
                make_ekran_control_zdz();
              }
              else if(
                      (current_ekran.current_level >= EKRAN_TIMEOUT_APV_GROUP1) &&
                      (current_ekran.current_level <= EKRAN_TIMEOUT_APV_GROUP4)
                     )   
              {
                int group = (current_ekran.current_level - EKRAN_TIMEOUT_APV_GROUP1);

                if(current_ekran.edition == 0)
                {
                  if(++current_ekran.index_position >= MAX_ROW_FOR_TIMEOUT_APV) current_ekran.index_position = 0;
                  position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;
                }
                else
                {
                  //����������� �����
                  if (current_ekran.index_position == INDEX_ML_TMOAPV1)
                    edition_settings.timeout_apv_1[group] = edit_setpoint(0, edition_settings.timeout_apv_1[group], 1, COL_TMO_APV_1_COMMA, COL_TMO_APV_1_END, 10);
                  else if (current_ekran.index_position == INDEX_ML_TMOAPV2)
                    edition_settings.timeout_apv_2[group] = edit_setpoint(0, edition_settings.timeout_apv_2[group], 1, COL_TMO_APV_2_COMMA, COL_TMO_APV_2_END, 10);
                  else if (current_ekran.index_position == INDEX_ML_TMOAPV3)
                    edition_settings.timeout_apv_3[group] = edit_setpoint(0, edition_settings.timeout_apv_3[group], 1, COL_TMO_APV_3_COMMA, COL_TMO_APV_3_END, 10);
                  else if (current_ekran.index_position == INDEX_ML_TMOAPV4)
                    edition_settings.timeout_apv_4[group] = edit_setpoint(0, edition_settings.timeout_apv_4[group], 1, COL_TMO_APV_4_COMMA, COL_TMO_APV_4_END, 10);
                  else if (current_ekran.index_position == INDEX_ML_TMOAPV_BLOCK_VID_APV1)
                    edition_settings.timeout_apv_block_vid_apv1[group] = edit_setpoint(0, edition_settings.timeout_apv_block_vid_apv1[group], 1, COL_TMO_APV_BLOCK_VID_APV1_COMMA, COL_TMO_APV_BLOCK_VID_APV1_END, 10);
                  else if (current_ekran.index_position == INDEX_ML_TMOAPV_BLOCK_VID_APV2)
                    edition_settings.timeout_apv_block_vid_apv2[group] = edit_setpoint(0, edition_settings.timeout_apv_block_vid_apv2[group], 1, COL_TMO_APV_BLOCK_VID_APV2_COMMA, COL_TMO_APV_BLOCK_VID_APV2_END, 10);
                  else if (current_ekran.index_position == INDEX_ML_TMOAPV_BLOCK_VID_APV3)
                    edition_settings.timeout_apv_block_vid_apv3[group] = edit_setpoint(0, edition_settings.timeout_apv_block_vid_apv3[group], 1, COL_TMO_APV_BLOCK_VID_APV3_COMMA, COL_TMO_APV_BLOCK_VID_APV3_END, 10);
                  else if (current_ekran.index_position == INDEX_ML_TMOAPV_BLOCK_VID_APV4)
                    edition_settings.timeout_apv_block_vid_apv4[group] = edit_setpoint(0, edition_settings.timeout_apv_block_vid_apv4[group], 1, COL_TMO_APV_BLOCK_VID_APV4_COMMA, COL_TMO_APV_BLOCK_VID_APV4_END, 10);
                  else if (current_ekran.index_position == INDEX_ML_TMOAPV_BLOCK_VID_VV)
                    edition_settings.timeout_apv_block_vid_VV[group] = edit_setpoint(0, edition_settings.timeout_apv_block_vid_VV[group], 1, COL_TMO_APV_BLOCK_VID_VV_COMMA, COL_TMO_APV_BLOCK_VID_VV_END, 10);
                }
                //������� ����� �������� ���
                make_ekran_timeout_apv(group);
              }
              else if(current_ekran.current_level == EKRAN_CONTROL_APV)
              {
                current_ekran.index_position++;
                
                if(current_ekran.index_position >= MAX_ROW_FOR_CONTROL_APV) current_ekran.index_position = 0;
                position_in_current_level_menu[EKRAN_CONTROL_APV] = current_ekran.index_position;
                //������� ����� ����������� ���������� ��� ���
                make_ekran_control_apv();
              }
              else if(
                      (current_ekran.current_level >= EKRAN_SETPOINT_UROV_GROUP1) &&
                      (current_ekran.current_level <= EKRAN_SETPOINT_UROV_GROUP4)
                     )   
              {
                int group = (current_ekran.current_level - EKRAN_SETPOINT_UROV_GROUP1);

                if(current_ekran.edition == 0)
                {
                  if(++current_ekran.index_position >= MAX_ROW_FOR_SETPOINT_UROV) current_ekran.index_position = 0;
                  position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;
                }
                else
                {
                  //����������� �����
                  edition_settings.setpoint_urov[group] = edit_setpoint(0, edition_settings.setpoint_urov[group], 1, COL_SETPOINT_UROV_COMMA, COL_SETPOINT_UROV_END, 10);
                }
                //������� ����� ������� ����
                make_ekran_setpoint_urov(group);
              }
              else if(
                      (current_ekran.current_level >= EKRAN_TIMEOUT_UROV_GROUP1) &&
                      (current_ekran.current_level <= EKRAN_TIMEOUT_UROV_GROUP4)
                     )   
              {
                int group = (current_ekran.current_level - EKRAN_TIMEOUT_UROV_GROUP1);

                if(current_ekran.edition == 0)
                {
                  if(++current_ekran.index_position >= MAX_ROW_FOR_TIMEOUT_UROV) current_ekran.index_position = 0;
                  position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;
                }
                else
                {
                  //����������� �����
                  if (current_ekran.index_position == INDEX_ML_TMOUROV1)
                    edition_settings.timeout_urov_1[group] = edit_setpoint(0, edition_settings.timeout_urov_1[group], 1, COL_TMO_UROV_1_COMMA, COL_TMO_UROV_1_END, 10);
                  else
                    edition_settings.timeout_urov_2[group] = edit_setpoint(0, edition_settings.timeout_urov_2[group], 1, COL_TMO_UROV_2_COMMA, COL_TMO_UROV_2_END, 10);
                }
                //������� ����� �������� ����
                make_ekran_timeout_urov(group);
              }
              else if(current_ekran.current_level == EKRAN_CONTROL_UROV)
              {
                current_ekran.index_position++;
                
                if(current_ekran.index_position >= MAX_ROW_FOR_CONTROL_UROV) current_ekran.index_position = 0;
                position_in_current_level_menu[EKRAN_CONTROL_UROV] = current_ekran.index_position;

                //������� ����� ����������� ���������� ��� ����
                make_ekran_control_urov();
              }
              else if(
                      (current_ekran.current_level >= EKRAN_SETPOINT_ZOP_GROUP1) &&
                      (current_ekran.current_level <= EKRAN_SETPOINT_ZOP_GROUP4)
                     )   
              {
                int group = (current_ekran.current_level - EKRAN_SETPOINT_ZOP_GROUP1);

                if(current_ekran.edition == 0)
                {
                  if(++current_ekran.index_position >= MAX_ROW_FOR_SETPOINT_ZOP) current_ekran.index_position = 0;
                  position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;
                }
                else
                {
                  //����������� �����
                  edition_settings.setpoint_zop[group] = edit_setpoint(0, edition_settings.setpoint_zop[group], 1, COL_SETPOINT_ZOP_COMMA, COL_SETPOINT_ZOP_END, 1);
                }
                //������� ����� ������� ����
                make_ekran_setpoint_zop(group);
              }
              else if(
                      (current_ekran.current_level >= EKRAN_TIMEOUT_ZOP_GROUP1) &&
                      (current_ekran.current_level <= EKRAN_TIMEOUT_ZOP_GROUP4)
                     )   
              {
                int group = (current_ekran.current_level - EKRAN_TIMEOUT_ZOP_GROUP1);

                if(current_ekran.edition == 0)
                {
                  if(++current_ekran.index_position >= MAX_ROW_FOR_TIMEOUT_ZOP) current_ekran.index_position = 0;
                  position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;
                }
                else
                {
                  //����������� �����
                  edition_settings.timeout_zop[group] = edit_setpoint(0, edition_settings.timeout_zop[group], 1, COL_TMO_ZOP_COMMA, COL_TMO_ZOP_END, 10);
                }
                //������� ����� �������� ���(���)
                make_ekran_timeout_zop(group);
              }
              else if(current_ekran.current_level == EKRAN_CONTROL_ZOP)
              {
                if(++current_ekran.index_position >= MAX_ROW_FOR_CONTROL_ZOP) current_ekran.index_position = 0;
                position_in_current_level_menu[EKRAN_CONTROL_ZOP] = current_ekran.index_position;
                //������� ����� ����������� ���������� ��� ���(���)
                make_ekran_control_zop();
              }
              else if(
                      (current_ekran.current_level >= EKRAN_SETPOINT_UMIN_GROUP1) &&
                      (current_ekran.current_level <= EKRAN_SETPOINT_UMIN_GROUP4)
                     )   
              {
                int group = (current_ekran.current_level - EKRAN_SETPOINT_UMIN_GROUP1);
                
                if(current_ekran.edition == 0)
                {
                  if(++current_ekran.index_position >= MAX_ROW_FOR_SETPOINT_UMIN) current_ekran.index_position = 0;
                  position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;
                }
                else
                {
                  //����������� �����
                  if (current_ekran.index_position == INDEX_ML_STPUMIN1)
                    edition_settings.setpoint_Umin1[group] = edit_setpoint(0, edition_settings.setpoint_Umin1[group], 1, COL_SETPOINT_UMIN1_COMMA, COL_SETPOINT_UMIN1_END, 100);
                  else if (current_ekran.index_position == INDEX_ML_STPUMIN1_IBLK)
                    edition_settings.setpoint_Umin1_Iblk[group] = edit_setpoint(0, edition_settings.setpoint_Umin1_Iblk[group], 1, COL_SETPOINT_UMIN1_IBLK_COMMA, COL_SETPOINT_UMIN1_IBLK_END, 10);
                  else if (current_ekran.index_position == INDEX_ML_STPUMIN2)
                    edition_settings.setpoint_Umin2[group] = edit_setpoint(0, edition_settings.setpoint_Umin2[group], 1, COL_SETPOINT_UMIN2_COMMA, COL_SETPOINT_UMIN2_END, 100);
                  else if (current_ekran.index_position == INDEX_ML_STPUMIN2_IBLK)
                    edition_settings.setpoint_Umin2_Iblk[group] = edit_setpoint(0, edition_settings.setpoint_Umin2_Iblk[group], 1, COL_SETPOINT_UMIN2_IBLK_COMMA, COL_SETPOINT_UMIN2_IBLK_END, 10);
                }
                //������� ����� ������� Umin
                make_ekran_setpoint_Umin(group);
              }
              else if(
                      (current_ekran.current_level >= EKRAN_TIMEOUT_UMIN_GROUP1) &&
                      (current_ekran.current_level <= EKRAN_TIMEOUT_UMIN_GROUP4)
                     )   
              {
                int group = (current_ekran.current_level - EKRAN_TIMEOUT_UMIN_GROUP1);
                
                if(current_ekran.edition == 0)
                {
                  if(++current_ekran.index_position >= MAX_ROW_FOR_TIMEOUT_UMIN) current_ekran.index_position = 0;
                  position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;
                }
                else
                {
                  //����������� �����
                  if (current_ekran.index_position == INDEX_ML_TMOUMIN1)
                    edition_settings.timeout_Umin1[group] = edit_setpoint(0, edition_settings.timeout_Umin1[group], 1, COL_TMO_UMIN1_COMMA, COL_TMO_UMIN1_END, 10);
                  else if (current_ekran.index_position == INDEX_ML_TMOUMIN2)
                    edition_settings.timeout_Umin2[group] = edit_setpoint(0, edition_settings.timeout_Umin2[group], 1, COL_TMO_UMIN2_COMMA, COL_TMO_UMIN2_END, 10);
                }
                //������� ����� �������� Umin
                make_ekran_timeout_Umin(group);
              }
              else if(current_ekran.current_level == EKRAN_CONTROL_UMIN)
              {
                if(++current_ekran.index_position >= MAX_ROW_FOR_CONTROL_UMIN) current_ekran.index_position = 0;
                position_in_current_level_menu[EKRAN_CONTROL_UMIN] = current_ekran.index_position;
                //������� ����� ����������� ���������� ��� Umin
                make_ekran_control_Umin();
              }
              else if(
                      (current_ekran.current_level >= EKRAN_SETPOINT_UMAX_GROUP1) &&
                      (current_ekran.current_level <= EKRAN_SETPOINT_UMAX_GROUP4)
                     )   
              {
                int group = (current_ekran.current_level - EKRAN_SETPOINT_UMAX_GROUP1);
                
                if(current_ekran.edition == 0)
                {
                  if(++current_ekran.index_position >= MAX_ROW_FOR_SETPOINT_UMAX) current_ekran.index_position = 0;
                  position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;
                }
                else
                {
                  //����������� �����
                  if (current_ekran.index_position == INDEX_ML_STPUMAX1)
                    edition_settings.setpoint_Umax1[group] = edit_setpoint(0, edition_settings.setpoint_Umax1[group], 1, COL_SETPOINT_UMAX1_COMMA, COL_SETPOINT_UMAX1_END, 100);
                  else if (current_ekran.index_position == INDEX_ML_STPUMAX2)
                    edition_settings.setpoint_Umax2[group] = edit_setpoint(0, edition_settings.setpoint_Umax2[group], 1, COL_SETPOINT_UMAX2_COMMA, COL_SETPOINT_UMAX2_END, 100);
                }
                //������� ����� ������� Umax
                make_ekran_setpoint_Umax(group);
              }
              else if(
                      (current_ekran.current_level >= EKRAN_TIMEOUT_UMAX_GROUP1) &&
                      (current_ekran.current_level <= EKRAN_TIMEOUT_UMAX_GROUP4)
                     )   
              {
                int group = (current_ekran.current_level - EKRAN_TIMEOUT_UMAX_GROUP1);
                
                if(current_ekran.edition == 0)
                {
                  if(++current_ekran.index_position >= MAX_ROW_FOR_TIMEOUT_UMAX) current_ekran.index_position = 0;
                  position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;
                }
                else
                {
                  //����������� �����
                  if (current_ekran.index_position == INDEX_ML_TMOUMAX1)
                    edition_settings.timeout_Umax1[group] = edit_setpoint(0, edition_settings.timeout_Umax1[group], 1, COL_TMO_UMAX1_COMMA, COL_TMO_UMAX1_END, 10);
                  else if (current_ekran.index_position == INDEX_ML_TMOUMAX2)
                    edition_settings.timeout_Umax2[group] = edit_setpoint(0, edition_settings.timeout_Umax2[group], 1, COL_TMO_UMAX2_COMMA, COL_TMO_UMAX2_END, 10);
                }
                //������� ����� �������� Umax
                make_ekran_timeout_Umax(group);
              }
              else if(current_ekran.current_level == EKRAN_CONTROL_UMAX)
              {
                if(++current_ekran.index_position >= MAX_ROW_FOR_CONTROL_UMAX) current_ekran.index_position = 0;
                position_in_current_level_menu[EKRAN_CONTROL_UMAX] = current_ekran.index_position;
                //������� ����� ����������� ���������� ��� Umax
                make_ekran_control_Umax();
              }
              else if(
                      (current_ekran.current_level >= EKRAN_SETPOINT_AVR_UMIN_GROUP1) &&
                      (current_ekran.current_level <= EKRAN_SETPOINT_AVR_UMIN_GROUP4)
                     )   
              {
                int group = (current_ekran.current_level - EKRAN_SETPOINT_AVR_UMIN_GROUP1);
                
                if(current_ekran.edition == 0)
                {
                  if(++current_ekran.index_position >= MAX_ROW_FOR_SETPOINT_AVR_UMIN) current_ekran.index_position = 0;
                  position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;
                }
                else
                {
                  //����������� �����
                  if (current_ekran.index_position == INDEX_ML_STPAVR_TN1_U1_UMIN)
                    edition_settings.setpoint_avr_tn1_U1_Umin[group] = edit_setpoint(0, edition_settings.setpoint_avr_tn1_U1_Umin[group], 1, COL_SETPOINT_AVR_TN1_U1_UMIN_COMMA, COL_SETPOINT_AVR_TN1_U1_UMIN_END, 100);
                  else if (current_ekran.index_position == INDEX_ML_STPAVR_TN1_U2_LOW_WORK)
                    edition_settings.setpoint_avr_tn1_U2_low_work[group] = edit_setpoint(0, edition_settings.setpoint_avr_tn1_U2_low_work[group], 1, COL_SETPOINT_AVR_TN1_U2_LOW_WORK_COMMA, COL_SETPOINT_AVR_TN1_U2_LOW_WORK_END, 100);
                  else if (current_ekran.index_position == INDEX_ML_STPAVR_TN2_U2_UMIN)
                    edition_settings.setpoint_avr_tn2_U2_Umin[group] = edit_setpoint(0, edition_settings.setpoint_avr_tn2_U2_Umin[group], 1, COL_SETPOINT_AVR_TN2_U2_UMIN_COMMA, COL_SETPOINT_AVR_TN2_U2_UMIN_END, 100);
                  else if (current_ekran.index_position == INDEX_ML_STPAVR_TN2_U1_LOW_WORK)
                    edition_settings.setpoint_avr_tn2_U1_low_work[group] = edit_setpoint(0, edition_settings.setpoint_avr_tn2_U1_low_work[group], 1, COL_SETPOINT_AVR_TN2_U1_LOW_WORK_COMMA, COL_SETPOINT_AVR_TN2_U1_LOW_WORK_END, 100);
                }
                //������� ����� ������� ��� Umin
                make_ekran_setpoint_avr_Umin(group);
              }
              else if(
                      (current_ekran.current_level >= EKRAN_SETPOINT_AVR_UMAX_GROUP1) &&
                      (current_ekran.current_level <= EKRAN_SETPOINT_AVR_UMAX_GROUP4)
                     )   
              {
                int group = (current_ekran.current_level - EKRAN_SETPOINT_AVR_UMAX_GROUP1);
                
                if(current_ekran.edition == 0)
                {
                  if(++current_ekran.index_position >= MAX_ROW_FOR_SETPOINT_AVR_UMAX) current_ekran.index_position = 0;
                  position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;
                }
                else
                {
                  //����������� �����
                  if (current_ekran.index_position == INDEX_ML_STPAVR_TN1_U1_UMAX)
                    edition_settings.setpoint_avr_tn1_U1_Umax[group] = edit_setpoint(0, edition_settings.setpoint_avr_tn1_U1_Umax[group], 1, COL_SETPOINT_AVR_TN1_U1_UMAX_COMMA, COL_SETPOINT_AVR_TN1_U1_UMAX_END, 100);
                  else if (current_ekran.index_position == INDEX_ML_STPAVR_TN1_U2_HIGH_WORK)
                    edition_settings.setpoint_avr_tn1_U2_high_work[group] = edit_setpoint(0, edition_settings.setpoint_avr_tn1_U2_high_work[group], 1, COL_SETPOINT_AVR_TN1_U2_HIGH_WORK_COMMA, COL_SETPOINT_AVR_TN1_U2_HIGH_WORK_END, 100);
                  else if (current_ekran.index_position == INDEX_ML_STPAVR_TN2_U2_UMAX)
                    edition_settings.setpoint_avr_tn2_U2_Umax[group] = edit_setpoint(0, edition_settings.setpoint_avr_tn2_U2_Umax[group], 1, COL_SETPOINT_AVR_TN2_U2_UMAX_COMMA, COL_SETPOINT_AVR_TN2_U2_UMAX_END, 100);
                  else if (current_ekran.index_position == INDEX_ML_STPAVR_TN2_U1_HIGH_WORK)
                    edition_settings.setpoint_avr_tn2_U1_high_work[group] = edit_setpoint(0, edition_settings.setpoint_avr_tn2_U1_high_work[group], 1, COL_SETPOINT_AVR_TN2_U1_HIGH_WORK_COMMA, COL_SETPOINT_AVR_TN2_U1_HIGH_WORK_END, 100);
                }
                //������� ����� ������� ��� Umax
                make_ekran_setpoint_avr_Umax(group);
              }
              else if(
                      (current_ekran.current_level >= EKRAN_TIMEOUT_AVR_GENERAL_GROUP1) &&
                      (current_ekran.current_level <= EKRAN_TIMEOUT_AVR_GENERAL_GROUP4)
                     )   
              {
                int group = (current_ekran.current_level - EKRAN_TIMEOUT_AVR_GENERAL_GROUP1);
                
                if(current_ekran.edition == 0)
                {
                  if(++current_ekran.index_position >= MAX_ROW_FOR_TIMEOUT_AVR_GENERAL) current_ekran.index_position = 0;
                  position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;
                }
                else
                {
                  //����������� �����
                  if (current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_BLK_K1)
                    edition_settings.timeout_avr_blk_k1[group] = edit_setpoint(0, edition_settings.timeout_avr_blk_k1[group], 1, COL_TMO_AVR_GENERAL_BLK_K1_COMMA, COL_TMO_AVR_GENERAL_BLK_K1_END, 10);
                  else if (current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_PUSK_K1)
                    edition_settings.timeout_avr_pusk_k1[group] = edit_setpoint(0, edition_settings.timeout_avr_pusk_k1[group], 1, COL_TMO_AVR_GENERAL_PUSK_K1_COMMA, COL_TMO_AVR_GENERAL_PUSK_K1_END, 10);
                  else if (current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_D_DIJI_K1)
                    edition_settings.timeout_avr_d_diji_k1[group] = edit_setpoint(0, edition_settings.timeout_avr_d_diji_k1[group], 1, COL_TMO_AVR_GENERAL_D_DIJI_K1_COMMA, COL_TMO_AVR_GENERAL_D_DIJI_K1_END, 10);
                  else if (current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_VVIMK_REZ_K1)
                    edition_settings.timeout_avr_vvimk_rez_k1[group] = edit_setpoint(0, edition_settings.timeout_avr_vvimk_rez_k1[group], 1, COL_TMO_AVR_GENERAL_VVIMK_REZ_K1_COMMA, COL_TMO_AVR_GENERAL_VVIMK_REZ_K1_END, 10);
                  else if (current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_VVIMK_K1)
                    edition_settings.timeout_avr_vvimk_k1[group] = edit_setpoint(0, edition_settings.timeout_avr_vvimk_k1[group], 1, COL_TMO_AVR_GENERAL_VVIMK_K1_COMMA, COL_TMO_AVR_GENERAL_VVIMK_K1_END, 10);
                  else if (current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_VYMK_K1)
                    edition_settings.timeout_avr_vymk_k1[group] = edit_setpoint(0, edition_settings.timeout_avr_vymk_k1[group], 1, COL_TMO_AVR_GENERAL_VYMK_K1_COMMA, COL_TMO_AVR_GENERAL_VYMK_K1_END, 10);
                  else if (current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_BLK_K2)
                    edition_settings.timeout_avr_blk_k2[group] = edit_setpoint(0, edition_settings.timeout_avr_blk_k2[group], 1, COL_TMO_AVR_GENERAL_BLK_K2_COMMA, COL_TMO_AVR_GENERAL_BLK_K2_END, 10);
                  else if (current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_PUSK_K2)
                    edition_settings.timeout_avr_pusk_k2[group] = edit_setpoint(0, edition_settings.timeout_avr_pusk_k2[group], 1, COL_TMO_AVR_GENERAL_PUSK_K2_COMMA, COL_TMO_AVR_GENERAL_PUSK_K2_END, 10);
                  else if (current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_D_DIJI_K2)
                    edition_settings.timeout_avr_d_diji_k2[group] = edit_setpoint(0, edition_settings.timeout_avr_d_diji_k2[group], 1, COL_TMO_AVR_GENERAL_D_DIJI_K2_COMMA, COL_TMO_AVR_GENERAL_D_DIJI_K2_END, 10);
                  else if (current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_VVIMK_REZ_K2)
                    edition_settings.timeout_avr_vvimk_rez_k2[group] = edit_setpoint(0, edition_settings.timeout_avr_vvimk_rez_k2[group], 1, COL_TMO_AVR_GENERAL_VVIMK_REZ_K2_COMMA, COL_TMO_AVR_GENERAL_VVIMK_REZ_K2_END, 10);
                  else if (current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_VVIMK_K2)
                    edition_settings.timeout_avr_vvimk_k2[group] = edit_setpoint(0, edition_settings.timeout_avr_vvimk_k2[group], 1, COL_TMO_AVR_GENERAL_VVIMK_K2_COMMA, COL_TMO_AVR_GENERAL_VVIMK_K2_END, 10);
                  else if (current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_VYMK_K2)
                    edition_settings.timeout_avr_vymk_k2[group] = edit_setpoint(0, edition_settings.timeout_avr_vymk_k2[group], 1, COL_TMO_AVR_GENERAL_VYMK_K2_COMMA, COL_TMO_AVR_GENERAL_VYMK_K2_END, 10);
                }
                //������� ����� �������� ��� (��������)
                make_ekran_timeout_avr_general(group);
              }
              else if(
                      (current_ekran.current_level >= EKRAN_TIMEOUT_AVR_UMIN_GROUP1) &&
                      (current_ekran.current_level <= EKRAN_TIMEOUT_AVR_UMIN_GROUP4)
                     )   
              {
                int group = (current_ekran.current_level - EKRAN_TIMEOUT_AVR_UMIN_GROUP1);
                
                if(current_ekran.edition == 0)
                {
                  if(++current_ekran.index_position >= MAX_ROW_FOR_TIMEOUT_AVR_UMIN) current_ekran.index_position = 0;
                  position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;
                }
                else
                {
                  //����������� �����
                  if (current_ekran.index_position == INDEX_ML_TMOAVR_UMIN_VYMK_ROB_K1)
                    edition_settings.timeout_avr_vymk_rob_k1_Umin[group] = edit_setpoint(0, edition_settings.timeout_avr_vymk_rob_k1_Umin[group], 1, COL_TMO_AVR_UMIN_VYMK_ROB_K1_COMMA, COL_TMO_AVR_UMIN_VYMK_ROB_K1_END, 10);
                  else if (current_ekran.index_position == INDEX_ML_TMOAVR_UMIN_VYMK_ROB_K2)
                    edition_settings.timeout_avr_vymk_rob_k2_Umin[group] = edit_setpoint(0, edition_settings.timeout_avr_vymk_rob_k2_Umin[group], 1, COL_TMO_AVR_UMIN_VYMK_ROB_K2_COMMA, COL_TMO_AVR_UMIN_VYMK_ROB_K2_END, 10);
                }
                //������� ����� �������� ��� Umin
                make_ekran_timeout_avr_Umin(group);
              }
              else if(
                      (current_ekran.current_level >= EKRAN_TIMEOUT_AVR_UMAX_GROUP1) &&
                      (current_ekran.current_level <= EKRAN_TIMEOUT_AVR_UMAX_GROUP4)
                     )   
              {
                int group = (current_ekran.current_level - EKRAN_TIMEOUT_AVR_UMAX_GROUP1);
                
                if(current_ekran.edition == 0)
                {
                  if(++current_ekran.index_position >= MAX_ROW_FOR_TIMEOUT_AVR_UMAX) current_ekran.index_position = 0;
                  position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;
                }
                else
                {
                  //����������� �����
                  if (current_ekran.index_position == INDEX_ML_TMOAVR_UMAX_VYMK_ROB_K1)
                    edition_settings.timeout_avr_vymk_rob_k1_Umax[group] = edit_setpoint(0, edition_settings.timeout_avr_vymk_rob_k1_Umax[group], 1, COL_TMO_AVR_UMAX_VYMK_ROB_K1_COMMA, COL_TMO_AVR_UMAX_VYMK_ROB_K1_END, 10);
                  else if (current_ekran.index_position == INDEX_ML_TMOAVR_UMAX_VYMK_ROB_K2)
                    edition_settings.timeout_avr_vymk_rob_k2_Umax[group] = edit_setpoint(0, edition_settings.timeout_avr_vymk_rob_k2_Umax[group], 1, COL_TMO_AVR_UMAX_VYMK_ROB_K2_COMMA, COL_TMO_AVR_UMAX_VYMK_ROB_K2_END, 10);
                }
                //������� ����� �������� ��� Umax
                make_ekran_timeout_avr_Umax(group);
              }
              else if(current_ekran.current_level == EKRAN_CONTROL_AVR)
              {
                if(++current_ekran.index_position >= MAX_ROW_FOR_CONTROL_AVR) current_ekran.index_position = 0;
                position_in_current_level_menu[EKRAN_CONTROL_AVR] = current_ekran.index_position;
                //������� ����� ����������� ���������� ��� ���
                make_ekran_control_avr();
              }
              else if(
                      (current_ekran.current_level >= EKRAN_SETPOINT_CTRL_PHASE_GROUP1) &&
                      (current_ekran.current_level <= EKRAN_SETPOINT_CTRL_PHASE_GROUP4)
                     )   
              {
                int group = (current_ekran.current_level - EKRAN_SETPOINT_CTRL_PHASE_GROUP1);
                
                if(current_ekran.edition == 0)
                {
                  if(++current_ekran.index_position >= MAX_ROW_FOR_SETPOINT_CTRL_PHASE) current_ekran.index_position = 0;
                  position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;
                }
                else
                {
                  //����������� �����
                  if (current_ekran.index_position == INDEX_ML_STPCTRL_PHASE_U)
                    edition_settings.setpoint_ctrl_phase_U[group] = edit_setpoint(0, edition_settings.setpoint_ctrl_phase_U[group], 1, COL_SETPOINT_CTRL_PHASE_U_COMMA, COL_SETPOINT_CTRL_PHASE_U_END, 100);
                  else if (current_ekran.index_position == INDEX_ML_STPCTRL_PHASE_PHI)
                    edition_settings.setpoint_ctrl_phase_phi[group] = edit_setpoint(0, edition_settings.setpoint_ctrl_phase_phi[group], 1, COL_SETPOINT_CTRL_PHASE_PHI_COMMA, COL_SETPOINT_CTRL_PHASE_PHI_END, 1);
                  else if (current_ekran.index_position == INDEX_ML_STPCTRL_PHASE_F)
                    edition_settings.setpoint_ctrl_phase_f[group] = edit_setpoint(0, edition_settings.setpoint_ctrl_phase_f[group], 1, COL_SETPOINT_CTRL_PHASE_F_COMMA, COL_SETPOINT_CTRL_PHASE_F_END, 10);
                }
                //������� ����� ������� "�������� ���������"
                make_ekran_setpoint_ctrl_phase(group);
              }
              else if(
                      (current_ekran.current_level >= EKRAN_TIMEOUT_CTRL_PHASE_GROUP1) &&
                      (current_ekran.current_level <= EKRAN_TIMEOUT_CTRL_PHASE_GROUP4)
                     )   
              {
                int group = (current_ekran.current_level - EKRAN_TIMEOUT_CTRL_PHASE_GROUP1);
                
                if(current_ekran.edition == 0)
                {
                  if(++current_ekran.index_position >= MAX_ROW_FOR_TIMEOUT_CTRL_PHASE) current_ekran.index_position = 0;
                  position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;
                }
                else
                {
                  //����������� �����
                  if (current_ekran.index_position == INDEX_ML_TMOCTRL_PHASE_U)
                    edition_settings.timeout_ctrl_phase_U[group] = edit_setpoint(0, edition_settings.timeout_ctrl_phase_U[group], 1, COL_TMO_CTRL_PHASE_U_COMMA, COL_TMO_CTRL_PHASE_U_END, 10);
                  else if (current_ekran.index_position == INDEX_ML_TMOCTRL_PHASE_U_D)
                    edition_settings.timeout_ctrl_phase_U_d[group] = edit_setpoint(0, edition_settings.timeout_ctrl_phase_U_d[group], 1, COL_TMO_CTRL_PHASE_U_D_COMMA, COL_TMO_CTRL_PHASE_U_D_END, 10);
                  else if (current_ekran.index_position == INDEX_ML_TMOCTRL_PHASE_PHI)
                    edition_settings.timeout_ctrl_phase_phi[group] = edit_setpoint(0, edition_settings.timeout_ctrl_phase_phi[group], 1, COL_TMO_CTRL_PHASE_PHI_COMMA, COL_TMO_CTRL_PHASE_PHI_END, 10);
                  else if (current_ekran.index_position == INDEX_ML_TMOCTRL_PHASE_PHI_D)
                    edition_settings.timeout_ctrl_phase_phi_d[group] = edit_setpoint(0, edition_settings.timeout_ctrl_phase_phi_d[group], 1, COL_TMO_CTRL_PHASE_PHI_D_COMMA, COL_TMO_CTRL_PHASE_PHI_D_END, 10);
                  else if (current_ekran.index_position == INDEX_ML_TMOCTRL_PHASE_F)
                    edition_settings.timeout_ctrl_phase_f[group] = edit_setpoint(0, edition_settings.timeout_ctrl_phase_f[group], 1, COL_TMO_CTRL_PHASE_F_COMMA, COL_TMO_CTRL_PHASE_F_END, 10);
                  else if (current_ekran.index_position == INDEX_ML_TMOCTRL_PHASE_F_D)
                    edition_settings.timeout_ctrl_phase_f_d[group] = edit_setpoint(0, edition_settings.timeout_ctrl_phase_f_d[group], 1, COL_TMO_CTRL_PHASE_F_D_COMMA, COL_TMO_CTRL_PHASE_F_D_END, 10);
                }
                //������� ����� �������� "�������� ���������"
                make_ekran_timeout_ctrl_phase(group);
              }
              else if(current_ekran.current_level == EKRAN_CONTROL_CTRL_PHASE)
              {
                if(++current_ekran.index_position >= MAX_ROW_FOR_CONTROL_CTRL_PHASE) current_ekran.index_position = 0;
                position_in_current_level_menu[EKRAN_CONTROL_CTRL_PHASE] = current_ekran.index_position;
                //������� ����� ����������� ���������� ��� "�������� ���������"
                make_ekran_control_ctrl_phase();
              }
              else if(current_ekran.current_level == EKRAN_TRANSFORMATOR_INFO_SETPOINT)
              {
                if(current_ekran.edition == 0)
                {
                  if(++current_ekran.index_position >= MAX_ROW_FOR_TRANSFORMATOR_INFO_SETPOINT) current_ekran.index_position = 0;
                  position_in_current_level_menu[EKRAN_TRANSFORMATOR_INFO_SETPOINT] = current_ekran.index_position;
                }
                else
                {
                  //����������� �����
                  if (current_ekran.index_position == INDEX_ML_TT)
                    edition_settings.TCurrent = edit_setpoint(0, edition_settings.TCurrent, 0, 0, COL_TT_END, 1);
                  else
                    edition_settings.TVoltage = edit_setpoint(0, edition_settings.TVoltage, 0, 0, COL_TN_END, 1);
                }
                //������� ����� ���������� �� ���������������
                make_ekran_transformator();
              }
              else if(current_ekran.current_level == EKRAN_TRANSFORMATOR_INFO_CONTROL)
              {
                if(++current_ekran.index_position >= MAX_ROW_FOR_TRANSFORMATOR_INFO_CONTROL) current_ekran.index_position = 0;
                position_in_current_level_menu[EKRAN_TRANSFORMATOR_INFO_CONTROL] = current_ekran.index_position;
                //������� ����� ����������� ����������� ���� "�������������"
                make_ekran_transformator_control();
              }
              else if(current_ekran.current_level == EKRAN_SETPOINT_SWITCH)
              {
                if(current_ekran.edition == 0)
                {
                  if(++current_ekran.index_position >= MAX_ROW_FOR_SETPOINT_SWITCH) current_ekran.index_position = 0;
                  position_in_current_level_menu[EKRAN_SETPOINT_SWITCH] = current_ekran.index_position;
                }
                else
                {
                  //����������� �����
                  if (current_ekran.index_position == INDEX_ML_STPInom)
                    edition_settings.setpoint_Inom = edit_setpoint(0, edition_settings.setpoint_Inom, 0, 0, COL_SETPOINT_Inom_END, 1);
                  if (current_ekran.index_position == INDEX_ML_STPRKS_Inom)
                    edition_settings.setpoint_r_kom_st_Inom = edit_setpoint(0, edition_settings.setpoint_r_kom_st_Inom, 0, 0, COL_SETPOINT_RKS_Inom_END, 1);
                  else if (current_ekran.index_position == INDEX_ML_STPMInom_vymk)
                    edition_settings.setpoint_Inom_vymk = edit_setpoint(0, edition_settings.setpoint_Inom_vymk, 1, COL_SETPOINT_Inom_vymk_COMMA, COL_SETPOINT_Inom_vymk_END, 1);
                  else if (current_ekran.index_position == INDEX_ML_STPRKS_Inom_vymk)
                    edition_settings.setpoint_r_kom_st_Inom_vymk = edit_setpoint(0, edition_settings.setpoint_r_kom_st_Inom_vymk, 0, 0, COL_SETPOINT_RKS_Inom_vymk_END, 1);
                  else if (current_ekran.index_position == INDEX_ML_STPPOCHATKOVYJ_RESURS)
                    edition_settings.setpoint_pochatkovyj_resurs = edit_setpoint(0, edition_settings.setpoint_pochatkovyj_resurs, 0, 0, COL_SETPOINT_POCHATKOVYJ_RESURS_END, 1);
                  else if (current_ekran.index_position == INDEX_ML_STPKRYTYCHNYJ_RESURS)
                    edition_settings.setpoint_krytychnyj_resurs = edit_setpoint(0, edition_settings.setpoint_krytychnyj_resurs, 0, 0, COL_SETPOINT_KRYTYCHNYJ_RESURS_END, 1);
                  else if (current_ekran.index_position == INDEX_ML_STPPOCHATKOVA_K_VYMK)
                    edition_settings.setpoint_pochatkova_k_vymk = edit_setpoint(0, edition_settings.setpoint_pochatkova_k_vymk, 0, 0, COL_SETPOINT_POCHATKOVA_K_VYMK_END, 1);
                }
                //������� ����� ������� �����������
                make_ekran_setpoint_switch();
              }
              else if(current_ekran.current_level == EKRAN_TIMEOUT_SWITCH)
              {
                if(current_ekran.edition == 0)
                {
                  if(++current_ekran.index_position >= MAX_ROW_FOR_TIMEOUT_SWITCH) current_ekran.index_position = 0;
                  position_in_current_level_menu[EKRAN_TIMEOUT_SWITCH] = current_ekran.index_position;
                }
                else
                {
                  //����������� �����
                  if (current_ekran.index_position == INDEX_ML_TMOON)
                    edition_settings.timeout_swch_on = edit_setpoint(0, edition_settings.timeout_swch_on, 1, COL_TMO_SWCH_ON_COMMA, COL_TMO_SWCH_ON_END, 10);
                  else if (current_ekran.index_position == INDEX_ML_TMOOFF)
                    edition_settings.timeout_swch_off = edit_setpoint(0, edition_settings.timeout_swch_off, 1, COL_TMO_SWCH_OFF_COMMA, COL_TMO_SWCH_OFF_END, 10);
                  else if (current_ekran.index_position == INDEX_ML_TMOUDL_BLK_ON)
                    edition_settings.timeout_swch_udl_blk_on = edit_setpoint(0, edition_settings.timeout_swch_udl_blk_on, 1, COL_TMO_SWCH_UDL_BLK_ON_COMMA, COL_TMO_SWCH_UDL_BLK_ON_END, 10);
                  else if (current_ekran.index_position == INDEX_ML_TMOPRYVODA_VV)
                    edition_settings.timeout_pryvoda_VV = edit_setpoint(0, edition_settings.timeout_pryvoda_VV, 1, COL_TMO_PRYVODA_VV_COMMA, COL_TMO_PRYVODA_VV_END, 10);
                }
                //������� ����� �������� �����������
                make_ekran_timeout_switch();
              }
              else if(current_ekran.current_level == EKRAN_CONTROL_SWITCH)
              {
                if(++current_ekran.index_position >= MAX_ROW_FOR_CONTROL_SWITCH) current_ekran.index_position = 0;
                position_in_current_level_menu[EKRAN_CONTROL_SWITCH] = current_ekran.index_position;
                //������� ����� ����������� ���������� ��� ��������
                make_ekran_control_switch();
              }
              else if(current_ekran.current_level == EKRAN_DOPUSK_DV_UVV)
              {
                if(current_ekran.edition == 0)
                {
                  if(++current_ekran.index_position >= NUMBER_INPUTS) current_ekran.index_position = 0;
                  position_in_current_level_menu[EKRAN_DOPUSK_DV_UVV] = current_ekran.index_position;
                }
                else
                {
                  //����������� �����
                  edition_settings.dopusk_dv[current_ekran.index_position] = 
                    edit_setpoint(0, edition_settings.dopusk_dv[current_ekran.index_position], 0, 0, COL_DOPUSK_DV_END, 1);
                }
                //������� ����� ���������� �� �������� ��
                make_ekran_dopusk_dv();
              }
              else if((current_ekran.current_level == EKRAN_TYPE_INPUT_UVV) || (current_ekran.current_level == EKRAN_TYPE_INPUT_SIGNAL_UVV))
              {
                if(++current_ekran.index_position >= NUMBER_INPUTS) current_ekran.index_position = 0;
                position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;
                //������� ����� ����������� ���������� ��� ���
                if (current_ekran.current_level == EKRAN_TYPE_INPUT_UVV)
                  make_ekran_type_input_uvv(0);
                else
                  make_ekran_type_input_uvv(1);
              }
              else if(current_ekran.current_level == EKRAN_TYPE_OUTPUT_UVV)
              {
                if(++current_ekran.index_position >= NUMBER_OUTPUTS) current_ekran.index_position = 0;
                position_in_current_level_menu[EKRAN_TYPE_OUTPUT_UVV] = current_ekran.index_position;
                //������� ����� ���� ������
                make_ekran_type_output_uvv();
              }
              else if(current_ekran.current_level == EKRAN_TYPE_LED_UVV)
              {
                if(++current_ekran.index_position >= NUMBER_LEDS) current_ekran.index_position = 0;
                position_in_current_level_menu[EKRAN_TYPE_LED_UVV] = current_ekran.index_position;
                //������� ����� ���� ��������������
                make_ekran_type_led_uvv();
              }
              else if(current_ekran.current_level == EKRAN_ADDRESS)
              {
                if(current_ekran.edition == 0)
                {
                  if(++current_ekran.index_position >= MAX_ROW_FOR_ADDRESS) current_ekran.index_position = 0;
                  position_in_current_level_menu[EKRAN_ADDRESS] = current_ekran.index_position;
                }
                else
                {
                  //����������� �����
                  edition_settings.address = edit_setpoint(0, edition_settings.address, 0, 0, COL_ADDRESS_END, 1);
                }
                //������� ����� ���������� �� �������������� �����
                make_ekran_address();
              }
              else if(current_ekran.current_level == EKRAN_VIEW_SPEED_RS485)
              {
                if(current_ekran.edition == 0)
                {
                  if(++current_ekran.index_position >= MAX_ROW_FOR_VIEW_SPEED_INTERFACE) current_ekran.index_position = 0;
                  position_in_current_level_menu[EKRAN_VIEW_SPEED_RS485] = current_ekran.index_position;
                }
                else
                {
                  //����������� �����
                  edition_settings.speed_RS485++;
                  if (edition_settings.speed_RS485 > VALUE_SPEED_INTERFACE_MAX)
                    edition_settings.speed_RS485 = VALUE_SPEED_INTERFACE_MIN;
                }
                //������� ����� ���������� �� �������� �����
                make_ekran_speed_interface();
              }
              else if(current_ekran.current_level == EKRAN_VIEW_PARE_RS485)
              {
                if(current_ekran.edition == 0)
                {
                  if(++current_ekran.index_position >= MAX_ROW_FOR_VIEW_PARE_INTERFACE) current_ekran.index_position = 0;
                  position_in_current_level_menu[EKRAN_VIEW_PARE_RS485] = current_ekran.index_position;
                }
                else
                {
                  //����������� �����
                  edition_settings.pare_bit_RS485++;
                  if (edition_settings.pare_bit_RS485 > VALUE_PARE_INTERFACE_MAX)
                    edition_settings.pare_bit_RS485 = VALUE_PARE_INTERFACE_MIN;
                }
                //������� ����� ���������� �� �������� �������
                make_ekran_pare_interface();
              }
              else if(current_ekran.current_level == EKRAN_VIEW_STOP_BITS_RS485)
              {
                if(current_ekran.edition == 0)
                {
                  if(++current_ekran.index_position >= MAX_ROW_FOR_VIEW_STOP_BITS_INTERFACE) current_ekran.index_position = 0;
                  position_in_current_level_menu[EKRAN_VIEW_STOP_BITS_RS485] = current_ekran.index_position;
                }
                else
                {
                  //����������� �����
                  edition_settings.number_stop_bit_RS485++;
                  if (edition_settings.number_stop_bit_RS485 > VALUE_STOP_BITS_INTERFACE_MAX)
                    edition_settings.number_stop_bit_RS485 = VALUE_STOP_BITS_INTERFACE_MIN;
                }
                //������� ����� ���������� �� ������� �������� ��
                make_ekran_stopbits_interface();
              }
              else if(current_ekran.current_level == EKRAN_VIEW_TIMEOUT_RS485)
              {
                if(current_ekran.edition == 0)
                {
                  if(++current_ekran.index_position >= MAX_ROW_FOR_VIEW_TIMEOUT_INTERFACE) current_ekran.index_position = 0;
                  position_in_current_level_menu[EKRAN_VIEW_TIMEOUT_RS485] = current_ekran.index_position;
                }
                else
                {
                  //����������� �����
                  edition_settings.time_out_1_RS485 = edit_setpoint(0, edition_settings.time_out_1_RS485, 1, COL_TIMEOUT_INTERFACE_COMMA, COL_TIMEOUT_INTERFACE_END, 1);
                }
                //������� ����� ���������� �� time-out ���������� �������
                make_ekran_timeout_interface();
              }
              else if (current_ekran.current_level == EKRAN_GENERAL_PICKUPS_EL)
              {
                if(current_ekran.edition == 0)
                {
                  if(++current_ekran.index_position >= MAX_ROW_FOR_GENERAL_PICKUPS_EL) current_ekran.index_position = 0;
                  position_in_current_level_menu[EKRAN_GENERAL_PICKUPS_EL] = current_ekran.index_position;
                }
                else
                {
                  //����������� �����
                  if (current_ekran.index_position == INDEX_ML_NUMBER_INERATION)
                  {
                    edition_settings.number_iteration_el = edit_setpoint(0, edition_settings.number_iteration_el, 0, 0, COL_NUMBER_INERATION_END, 1);
                  }
//                  else if (current_ekran.index_position == INDEX_ML_NUMBER_DEFINED_FUNCTIONS)
//                  {
//                    edition_settings.number_defined_df = edit_setpoint(0, edition_settings.number_defined_df, 0, 0, COL_NUMBER_DEFINED_FUNCTIONS_END, 1);
//                  }
//                  else if (current_ekran.index_position == INDEX_ML_NUMBER_DEFINED_TRIGGERS)
//                  {
//                    edition_settings.number_defined_dt = edit_setpoint(0, edition_settings.number_defined_dt, 0, 0, COL_NUMBER_DEFINED_TRIGGERS_END, 1);
//                  }
//                  else if (current_ekran.index_position == INDEX_ML_NUMBER_DEFINED_AND)
//                  {
//                    edition_settings.number_defined_and = edit_setpoint(0, edition_settings.number_defined_and, 0, 0, COL_NUMBER_DEFINED_AND_END, 1);
//                  }
//                  else if (current_ekran.index_position == INDEX_ML_NUMBER_DEFINED_OR)
//                  {
//                    edition_settings.number_defined_or = edit_setpoint(0, edition_settings.number_defined_or, 0, 0, COL_NUMBER_DEFINED_OR_END, 1);
//                  }
//                  else if (current_ekran.index_position == INDEX_ML_NUMBER_DEFINED_XOR)
//                  {
//                    edition_settings.number_defined_xor = edit_setpoint(0, edition_settings.number_defined_xor, 0, 0, COL_NUMBER_DEFINED_XOR_END, 1);
//                  }
//                  else if (current_ekran.index_position == INDEX_ML_NUMBER_DEFINED_NOT)
//                  {
//                    edition_settings.number_defined_not = edit_setpoint(0, edition_settings.number_defined_not, 0, 0, COL_NUMBER_DEFINED_NOT_END, 1);
//                  }
                }
                //������� ����� ����������� ��������� �������� ��� ��������� �����
                make_ekran_general_pickups_el();
              }
              else if(current_ekran.current_level == EKRAN_LIST_TYPE_DF)
              {
                if(++current_ekran.index_position >= MAX_ROW_FOR_TYPE_DF) current_ekran.index_position = 0;
                position_in_current_level_menu[EKRAN_LIST_TYPE_DF] = current_ekran.index_position;
                //������� ����� ����������� ���� ������������� �������
                make_ekran_type_df();
              }
              else if((current_ekran.current_level >= EKRAN_TIMEOUT_DF1) && (current_ekran.current_level <= EKRAN_TIMEOUT_DF8))
              {
                if(current_ekran.edition == 0)
                {
                  if(++current_ekran.index_position >= MAX_ROW_TIMEOUT_DF) current_ekran.index_position = 0;
                  position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;
                }
                else
                {
                  //����������� �����
                  if (current_ekran.index_position == INDEX_ML_TMO_DF_PAUSE)
                    edition_settings.timeout_pause_df[current_ekran.current_level - EKRAN_TIMEOUT_DF1] = 
                      edit_setpoint(0, edition_settings.timeout_pause_df[current_ekran.current_level - EKRAN_TIMEOUT_DF1], 1, COL_TMO_DF_PAUSE_COMMA, COL_TMO_DF_PAUSE_END, 10);
                  else
                    edition_settings.timeout_work_df[current_ekran.current_level - EKRAN_TIMEOUT_DF1] = 
                      edit_setpoint(0, edition_settings.timeout_work_df[current_ekran.current_level - EKRAN_TIMEOUT_DF1], 1, COL_TMO_DF_WORK_COMMA, COL_TMO_DF_WORK_END, 10);
                }
                //������� ����� ������� ������������ �������
                make_ekran_timeout_df(current_ekran.current_level - EKRAN_TIMEOUT_DF1);
              }
              else if(current_ekran.current_level == EKRAN_TIMEOUT_ANALOG_REGISTRATOR)
              {
                if(current_ekran.edition == 0)
                {
                  if(++current_ekran.index_position >= MAX_ROW_FOR_TIMEOUT_ANALOG_REGISTRATOR) current_ekran.index_position = 0;
                  position_in_current_level_menu[EKRAN_TIMEOUT_ANALOG_REGISTRATOR] = current_ekran.index_position;
                }
                else
                {
                  //����������� �����
                  if (current_ekran.index_position == INDEX_ML_TMOPREFAULT)
                  {
                    unsigned int temp_setpoint = edition_settings.prefault_number_periods*20;
                    do
                    {
                      //�������� �������� �������� ��������� �� 10 �� (�-��� edit_setpoint ������/������ � ������ ������� 1, 10 � �.�.), ��� �������� ���� 20 ��
                      temp_setpoint = edit_setpoint(0, temp_setpoint, 1, COL_TMO_PREFAULT_COMMA, COL_TMO_PREFAULT_END, 10);
                    }
                    while ((temp_setpoint % 20) != 0);
                    edition_settings.prefault_number_periods = temp_setpoint / 20;
                  }
                  else
                  {
                    unsigned int temp_setpoint = edition_settings.postfault_number_periods*20;
                    do
                    {
                      //�������� �������� �������� ��������� �� 10 �� (�-��� edit_setpoint ������/������ � ������ ������� 1, 10 � �.�.), ��� �������� ���� 20 ��
                      temp_setpoint = edit_setpoint(0, temp_setpoint, 1, COL_TMO_PREFAULT_COMMA, COL_TMO_PREFAULT_END, 10);
                    }
                    while ((temp_setpoint % 20) != 0);
                    edition_settings.postfault_number_periods = temp_setpoint / 20;
                  }
                }
                //������� ����� �������� ����������� ����������
                make_ekran_timeout_analog_registrator();
              }
              else if(current_ekran.current_level == EKRAN_VIEW_SETTING_LANGUAGE)
              {
                if(current_ekran.edition == 0)
                {
                  if(++current_ekran.index_position >= MAX_ROW_FOR_VIEW_SETTING_LANGUAGE) current_ekran.index_position = 0;
                  position_in_current_level_menu[EKRAN_VIEW_SETTING_LANGUAGE] = current_ekran.index_position;
                }
                else
                {
                  //����������� �����
                  edition_settings.language++;
                  if (edition_settings.language > VALUE_SETTING_LANGUAGE_MAX)
                    edition_settings.language = VALUE_SETTING_LANGUAGE_MIN;
                }
                //������� ����� ���������� �� ��� ����
                make_ekran_setting_language();
              }
              else if(current_ekran.current_level == EKRAN_CHOSE_EXTRA_SETTINGS)
              {
                if(++current_ekran.index_position >= MAX_ROW_FOR_CHOSE_EXTRA_SETTINGS) current_ekran.index_position = 0;
                position_in_current_level_menu[EKRAN_CHOSE_EXTRA_SETTINGS] = current_ekran.index_position;
                //������� ����� ����������� ���������� �����������
                make_ekran_chose_extra_settings();
              }

              //�������� �����������, �� ��������� ������ 
              new_state_keyboard &= (unsigned int)(~(1<<BIT_KEY_DOWN));
            }
            else if (new_state_keyboard == (1<<BIT_KEY_RIGHT))
            {
              current_ekran.position_cursor_x++;
              //����������, �� �� �� ������ �� ��� ������� ��� �������� ���� �������, ��� ������� ����
              if (current_ekran.current_level == EKRAN_CONTROL_ZDZ)
              {
                unsigned int maska = 0;
          
                //��������, ���� �� ����� �����
                if (current_ekran.index_position == INDEX_ML_CTRZDZ_STATE) maska = CTR_ZDZ_STATE;
                else if (current_ekran.index_position == INDEX_ML_CTRZDZ_STARTED_FROM_MTZ1 ) maska = CTR_ZDZ_STARTED_FROM_MTZ1;
                else if (current_ekran.index_position == INDEX_ML_CTRZDZ_STARTED_FROM_MTZ2 ) maska = CTR_ZDZ_STARTED_FROM_MTZ2;
                else if (current_ekran.index_position == INDEX_ML_CTRZDZ_STARTED_FROM_MTZ3 ) maska = CTR_ZDZ_STARTED_FROM_MTZ3;
                else if (current_ekran.index_position == INDEX_ML_CTRZDZ_STARTED_FROM_MTZ4 ) maska = CTR_ZDZ_STARTED_FROM_MTZ4;
                
                //̳����� �� ����������� ��������� �� ��� ������� �������
                edition_settings.control_zdz ^= maska;

                //������� ����� ����������� ���������� ��� ���
                 make_ekran_control_zdz();
              }
              else if(
                      (current_ekran.current_level >= EKRAN_TIMEOUT_APV_GROUP1) &&
                      (current_ekran.current_level <= EKRAN_TIMEOUT_APV_GROUP4)
                     )   
              {
                if(current_ekran.index_position == INDEX_ML_TMOAPV1)
                {
                  if (current_ekran.position_cursor_x == COL_TMO_APV_1_COMMA )current_ekran.position_cursor_x++;
                  if ((current_ekran.position_cursor_x < COL_TMO_APV_1_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TMO_APV_1_END))
                    current_ekran.position_cursor_x = COL_TMO_APV_1_BEGIN;
                }
                else if(current_ekran.index_position == INDEX_ML_TMOAPV2)
                {
                  if (current_ekran.position_cursor_x == COL_TMO_APV_2_COMMA )current_ekran.position_cursor_x++;
                  if ((current_ekran.position_cursor_x < COL_TMO_APV_2_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TMO_APV_2_END))
                    current_ekran.position_cursor_x = COL_TMO_APV_2_BEGIN;
                }
                else if(current_ekran.index_position == INDEX_ML_TMOAPV3)
                {
                  if (current_ekran.position_cursor_x == COL_TMO_APV_3_COMMA )current_ekran.position_cursor_x++;
                  if ((current_ekran.position_cursor_x < COL_TMO_APV_3_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TMO_APV_3_END))
                    current_ekran.position_cursor_x = COL_TMO_APV_3_BEGIN;
                }
                else if(current_ekran.index_position == INDEX_ML_TMOAPV4)
                {
                  if (current_ekran.position_cursor_x == COL_TMO_APV_4_COMMA )current_ekran.position_cursor_x++;
                  if ((current_ekran.position_cursor_x < COL_TMO_APV_4_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TMO_APV_4_END))
                    current_ekran.position_cursor_x = COL_TMO_APV_4_BEGIN;
                }
                else if (current_ekran.index_position == INDEX_ML_TMOAPV_BLOCK_VID_APV1)
                {
                  if (current_ekran.position_cursor_x == COL_TMO_APV_BLOCK_VID_APV1_COMMA )current_ekran.position_cursor_x++;
                  if ((current_ekran.position_cursor_x < COL_TMO_APV_BLOCK_VID_APV1_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TMO_APV_BLOCK_VID_APV1_END))
                    current_ekran.position_cursor_x = COL_TMO_APV_BLOCK_VID_APV1_BEGIN;
                }
                else if (current_ekran.index_position == INDEX_ML_TMOAPV_BLOCK_VID_APV2)
                {
                  if (current_ekran.position_cursor_x == COL_TMO_APV_BLOCK_VID_APV2_COMMA )current_ekran.position_cursor_x++;
                  if ((current_ekran.position_cursor_x < COL_TMO_APV_BLOCK_VID_APV2_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TMO_APV_BLOCK_VID_APV2_END))
                    current_ekran.position_cursor_x = COL_TMO_APV_BLOCK_VID_APV2_BEGIN;
                }
                else if (current_ekran.index_position == INDEX_ML_TMOAPV_BLOCK_VID_APV3)
                {
                  if (current_ekran.position_cursor_x == COL_TMO_APV_BLOCK_VID_APV3_COMMA )current_ekran.position_cursor_x++;
                  if ((current_ekran.position_cursor_x < COL_TMO_APV_BLOCK_VID_APV3_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TMO_APV_BLOCK_VID_APV3_END))
                    current_ekran.position_cursor_x = COL_TMO_APV_BLOCK_VID_APV3_BEGIN;
                }
                else if (current_ekran.index_position == INDEX_ML_TMOAPV_BLOCK_VID_APV4)
                {
                  if (current_ekran.position_cursor_x == COL_TMO_APV_BLOCK_VID_APV4_COMMA )current_ekran.position_cursor_x++;
                  if ((current_ekran.position_cursor_x < COL_TMO_APV_BLOCK_VID_APV4_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TMO_APV_BLOCK_VID_APV4_END))
                    current_ekran.position_cursor_x = COL_TMO_APV_BLOCK_VID_APV4_BEGIN;
                }
                else if (current_ekran.index_position == INDEX_ML_TMOAPV_BLOCK_VID_VV)
                {
                  if (current_ekran.position_cursor_x == COL_TMO_APV_BLOCK_VID_VV_COMMA )current_ekran.position_cursor_x++;
                  if ((current_ekran.position_cursor_x < COL_TMO_APV_BLOCK_VID_VV_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TMO_APV_BLOCK_VID_VV_END))
                    current_ekran.position_cursor_x = COL_TMO_APV_BLOCK_VID_VV_BEGIN;
                }
                //������� ����� �������� ���
                int group = (current_ekran.current_level - EKRAN_TIMEOUT_APV_GROUP1);
                make_ekran_timeout_apv(group);
              }
              else if(current_ekran.current_level == EKRAN_CONTROL_APV)
              {
                unsigned int maska = 0;
          
                //��������, ���� �� ����� �����
                if (current_ekran.index_position == INDEX_ML_CTRAPV_STAGE_1) maska = CTR_APV_STAGE_1;
                else if (current_ekran.index_position == INDEX_ML_CTRAPV_STAGE_2) maska = CTR_APV_STAGE_2;
                else if (current_ekran.index_position == INDEX_ML_CTRAPV_STAGE_3) maska = CTR_APV_STAGE_3;
                else if (current_ekran.index_position == INDEX_ML_CTRAPV_STAGE_4) maska = CTR_APV_STAGE_4;
                else if (current_ekran.index_position == INDEX_ML_CTRAPV_STARTED_FROM_MTZ1) maska = CTR_APV_STARTED_FROM_MTZ1;
                else if (current_ekran.index_position == INDEX_ML_CTRAPV_STARTED_FROM_MTZ2) maska = CTR_APV_STARTED_FROM_MTZ2;
                else if (current_ekran.index_position == INDEX_ML_CTRAPV_STARTED_FROM_MTZ3) maska = CTR_APV_STARTED_FROM_MTZ3;
                else if (current_ekran.index_position == INDEX_ML_CTRAPV_STARTED_FROM_MTZ4) maska = CTR_APV_STARTED_FROM_MTZ4;
                
                //̳����� �� ����������� ��������� �� ��� ������� �������
                edition_settings.control_apv ^= maska;

                //������� ����� ����������� ���������� ��� ���
                 make_ekran_control_apv();
              }
              else if(
                      (current_ekran.current_level >= EKRAN_SETPOINT_UROV_GROUP1) &&
                      (current_ekran.current_level <= EKRAN_SETPOINT_UROV_GROUP4)
                     )   
              {
                if (current_ekran.position_cursor_x == COL_SETPOINT_UROV_COMMA )current_ekran.position_cursor_x++;
                if ((current_ekran.position_cursor_x < COL_SETPOINT_UROV_BEGIN) ||
                    (current_ekran.position_cursor_x > COL_SETPOINT_UROV_END))
                  current_ekran.position_cursor_x = COL_SETPOINT_UROV_BEGIN;

                //������� ����� ������� ����
                int group = (current_ekran.current_level - EKRAN_SETPOINT_UROV_GROUP1);
                make_ekran_setpoint_urov(group);
              }
              else if(
                      (current_ekran.current_level >= EKRAN_TIMEOUT_UROV_GROUP1) &&
                      (current_ekran.current_level <= EKRAN_TIMEOUT_UROV_GROUP4)
                     )   
              {
                if(current_ekran.index_position == INDEX_ML_TMOUROV1)
                {
                  if (current_ekran.position_cursor_x == COL_TMO_UROV_1_COMMA )current_ekran.position_cursor_x++;
                  if ((current_ekran.position_cursor_x < COL_TMO_UROV_1_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TMO_UROV_1_END))
                    current_ekran.position_cursor_x = COL_TMO_UROV_1_BEGIN;
                }
                else
                {
                  if (current_ekran.position_cursor_x == COL_TMO_UROV_2_COMMA )current_ekran.position_cursor_x++;
                  if ((current_ekran.position_cursor_x < COL_TMO_UROV_2_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TMO_UROV_2_END))
                    current_ekran.position_cursor_x = COL_TMO_UROV_2_BEGIN;
                }

                //������� ����� �������� ����
                int group = (current_ekran.current_level - EKRAN_TIMEOUT_UROV_GROUP1);
                make_ekran_timeout_urov(group);
              }
              else if(current_ekran.current_level == EKRAN_CONTROL_UROV)
              {
                unsigned int maska = 0;
          
                //��������, ���� �� ����� �����
                if (current_ekran.index_position == INDEX_ML_CTRUROV_STATE) maska = CTR_UROV_STATE;
                else if (current_ekran.index_position == INDEX_ML_CTRUROV_STARTED_FROM_MTZ1   ) maska = CTR_UROV_STARTED_FROM_MTZ1;
                else if (current_ekran.index_position == INDEX_ML_CTRUROV_STARTED_FROM_MTZ2   ) maska = CTR_UROV_STARTED_FROM_MTZ2;
                else if (current_ekran.index_position == INDEX_ML_CTRUROV_STARTED_FROM_MTZ3   ) maska = CTR_UROV_STARTED_FROM_MTZ3;
                else if (current_ekran.index_position == INDEX_ML_CTRUROV_STARTED_FROM_MTZ4   ) maska = CTR_UROV_STARTED_FROM_MTZ4;
                else if (current_ekran.index_position == INDEX_ML_CTRUROV_STARTED_FROM_ZDZ    ) maska = CTR_UROV_STARTED_FROM_ZDZ;
                else if (current_ekran.index_position == INDEX_ML_CTRUROV_STARTED_FROM_ZOP1   ) maska = CTR_UROV_STARTED_FROM_ZOP1;
                else if (current_ekran.index_position == INDEX_ML_CTRUROV_STARTED_FROM_UMIN1  ) maska = CTR_UROV_STARTED_FROM_UMIN1;
                else if (current_ekran.index_position == INDEX_ML_CTRUROV_STARTED_FROM_UMIN2  ) maska = CTR_UROV_STARTED_FROM_UMIN2;
                else if (current_ekran.index_position == INDEX_ML_CTRUROV_STARTED_FROM_UMAX1  ) maska = CTR_UROV_STARTED_FROM_UMAX1;
                else if (current_ekran.index_position == INDEX_ML_CTRUROV_STARTED_FROM_UMAX2  ) maska = CTR_UROV_STARTED_FROM_UMAX2;
                
                //̳����� �� ����������� ��������� �� ��� ������� �������
                edition_settings.control_urov ^= maska;

                //������� ����� ����������� ���������� ��� ����
                 make_ekran_control_urov();
              }
              else if(
                      (current_ekran.current_level >= EKRAN_SETPOINT_ZOP_GROUP1) &&
                      (current_ekran.current_level <= EKRAN_SETPOINT_ZOP_GROUP4)
                     )   
              {
                if (current_ekran.position_cursor_x == COL_SETPOINT_ZOP_COMMA )current_ekran.position_cursor_x++;
                if ((current_ekran.position_cursor_x < COL_SETPOINT_ZOP_BEGIN) ||
                    (current_ekran.position_cursor_x > COL_SETPOINT_ZOP_END))
                  current_ekran.position_cursor_x = COL_SETPOINT_ZOP_BEGIN;

                //������� ����� ������� ����
                int group = (current_ekran.current_level - EKRAN_SETPOINT_ZOP_GROUP1);
                make_ekran_setpoint_zop(group);
              }
              else if(
                      (current_ekran.current_level >= EKRAN_TIMEOUT_ZOP_GROUP1) &&
                      (current_ekran.current_level <= EKRAN_TIMEOUT_ZOP_GROUP4)
                     )   
              {
                if (current_ekran.position_cursor_x == COL_TMO_ZOP_COMMA )current_ekran.position_cursor_x++;
                if ((current_ekran.position_cursor_x < COL_TMO_ZOP_BEGIN) ||
                    (current_ekran.position_cursor_x > COL_TMO_ZOP_END))
                  current_ekran.position_cursor_x = COL_TMO_ZOP_BEGIN;

                //������� ����� �������� ���(���)
                int group = (current_ekran.current_level - EKRAN_TIMEOUT_ZOP_GROUP1);
                make_ekran_timeout_zop(group);
              }
              else if(current_ekran.current_level == EKRAN_CONTROL_ZOP)
              {
                unsigned int maska;
          
                //��������, ���� �� ����� �����
                maska = CTR_ZOP_STATE;
                
                //̳����� �� ����������� ��������� �� ��� ������� �������
                edition_settings.control_zop ^= maska;

                //������� ����� ����������� ���������� ��� ����
                 make_ekran_control_zop();
              }
              else if(
                      (current_ekran.current_level >= EKRAN_SETPOINT_UMIN_GROUP1) &&
                      (current_ekran.current_level <= EKRAN_SETPOINT_UMIN_GROUP4)
                     )   
              {
                if(current_ekran.index_position == INDEX_ML_STPUMIN1)
                {
                  if (current_ekran.position_cursor_x == COL_SETPOINT_UMIN1_COMMA )current_ekran.position_cursor_x++;
                  if ((current_ekran.position_cursor_x < COL_SETPOINT_UMIN1_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_SETPOINT_UMIN1_END))
                    current_ekran.position_cursor_x = COL_SETPOINT_UMIN1_BEGIN;
                }
                else if(current_ekran.index_position == INDEX_ML_STPUMIN1_IBLK)
                {
                  if (current_ekran.position_cursor_x == COL_SETPOINT_UMIN1_IBLK_COMMA )current_ekran.position_cursor_x++;
                  if ((current_ekran.position_cursor_x < COL_SETPOINT_UMIN1_IBLK_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_SETPOINT_UMIN1_IBLK_END))
                    current_ekran.position_cursor_x = COL_SETPOINT_UMIN1_IBLK_BEGIN;
                }
                else if(current_ekran.index_position == INDEX_ML_STPUMIN2)
                {
                  if (current_ekran.position_cursor_x == COL_SETPOINT_UMIN2_COMMA )current_ekran.position_cursor_x++;
                  if ((current_ekran.position_cursor_x < COL_SETPOINT_UMIN2_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_SETPOINT_UMIN2_END))
                    current_ekran.position_cursor_x = COL_SETPOINT_UMIN2_BEGIN;
                }
                else if(current_ekran.index_position == INDEX_ML_STPUMIN2_IBLK)
                {
                  if (current_ekran.position_cursor_x == COL_SETPOINT_UMIN2_IBLK_COMMA )current_ekran.position_cursor_x++;
                  if ((current_ekran.position_cursor_x < COL_SETPOINT_UMIN2_IBLK_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_SETPOINT_UMIN2_IBLK_END))
                    current_ekran.position_cursor_x = COL_SETPOINT_UMIN2_IBLK_BEGIN;
                }

                //������� ����� ������� Umin
                int group = (current_ekran.current_level - EKRAN_SETPOINT_UMIN_GROUP1);
                make_ekran_setpoint_Umin(group);
              }
              else if(
                      (current_ekran.current_level >= EKRAN_TIMEOUT_UMIN_GROUP1) &&
                      (current_ekran.current_level <= EKRAN_TIMEOUT_UMIN_GROUP4)
                     )  
              {
                if(current_ekran.index_position == INDEX_ML_TMOUMIN1)
                {
                  if (current_ekran.position_cursor_x == COL_TMO_UMIN1_COMMA )current_ekran.position_cursor_x++;
                  if ((current_ekran.position_cursor_x < COL_TMO_UMIN1_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TMO_UMIN1_END))
                    current_ekran.position_cursor_x = COL_TMO_UMIN1_BEGIN;
                }
                else if(current_ekran.index_position == INDEX_ML_TMOUMIN2)
                {
                  if (current_ekran.position_cursor_x == COL_TMO_UMIN2_COMMA )current_ekran.position_cursor_x++;
                  if ((current_ekran.position_cursor_x < COL_TMO_UMIN2_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TMO_UMIN2_END))
                    current_ekran.position_cursor_x = COL_TMO_UMIN2_BEGIN;
                }

                //������� ����� �������� Umin
                int group = (current_ekran.current_level - EKRAN_TIMEOUT_UMIN_GROUP1);
                make_ekran_timeout_Umin(group);
              }
              else if(current_ekran.current_level == EKRAN_CONTROL_UMIN)
              {
                unsigned int maska = 0;
          
                //��������, ���� �� ����� �����
                if      (current_ekran.index_position == INDEX_CTR_UMIN1          ) maska = CTR_UMIN1;
                else if (current_ekran.index_position == INDEX_CTR_PO_UMIN1_OR_AND) maska = CTR_PO_UMIN1_OR_AND;
                else if (current_ekran.index_position == INDEX_CTR_UMIN1_UBLK     ) maska = CTR_UMIN1_UBLK;
                else if (current_ekran.index_position == INDEX_CTR_UMIN1_IBLK     ) maska = CTR_UMIN1_IBLK;
                else if (current_ekran.index_position == INDEX_CTR_UMIN2          ) maska = CTR_UMIN2;
                else if (current_ekran.index_position == INDEX_CTR_PO_UMIN2_OR_AND) maska = CTR_PO_UMIN2_OR_AND;
                else if (current_ekran.index_position == INDEX_CTR_UMIN2_UBLK     ) maska = CTR_UMIN2_UBLK;
                else if (current_ekran.index_position == INDEX_CTR_UMIN2_IBLK     ) maska = CTR_UMIN2_IBLK;
                
                //̳����� �� ����������� ��������� �� ��� ������� �������
                edition_settings.control_Umin ^= maska;

                //������� ����� ����������� ���������� ��� Umin
                 make_ekran_control_Umin();
              }
              else if(
                      (current_ekran.current_level >= EKRAN_SETPOINT_UMAX_GROUP1) &&
                      (current_ekran.current_level <= EKRAN_SETPOINT_UMAX_GROUP4)
                     )   
              {
                if(current_ekran.index_position == INDEX_ML_STPUMAX1)
                {
                  if (current_ekran.position_cursor_x == COL_SETPOINT_UMAX1_COMMA )current_ekran.position_cursor_x++;
                  if ((current_ekran.position_cursor_x < COL_SETPOINT_UMAX1_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_SETPOINT_UMAX1_END))
                    current_ekran.position_cursor_x = COL_SETPOINT_UMAX1_BEGIN;
                }
                else if(current_ekran.index_position == INDEX_ML_STPUMAX2)
                {
                  if (current_ekran.position_cursor_x == COL_SETPOINT_UMAX2_COMMA )current_ekran.position_cursor_x++;
                  if ((current_ekran.position_cursor_x < COL_SETPOINT_UMAX2_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_SETPOINT_UMAX2_END))
                    current_ekran.position_cursor_x = COL_SETPOINT_UMAX2_BEGIN;
                }

                //������� ����� ������� Umax
                int group = (current_ekran.current_level - EKRAN_SETPOINT_UMAX_GROUP1);
                make_ekran_setpoint_Umax(group);
              }
              else if(
                      (current_ekran.current_level >= EKRAN_TIMEOUT_UMAX_GROUP1) &&
                      (current_ekran.current_level <= EKRAN_TIMEOUT_UMAX_GROUP4)
                     )  
              {
                if(current_ekran.index_position == INDEX_ML_TMOUMAX1)
                {
                  if (current_ekran.position_cursor_x == COL_TMO_UMAX1_COMMA )current_ekran.position_cursor_x++;
                  if ((current_ekran.position_cursor_x < COL_TMO_UMAX1_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TMO_UMAX1_END))
                    current_ekran.position_cursor_x = COL_TMO_UMAX1_BEGIN;
                }
                else if(current_ekran.index_position == INDEX_ML_TMOUMAX2)
                {
                  if (current_ekran.position_cursor_x == COL_TMO_UMAX2_COMMA )current_ekran.position_cursor_x++;
                  if ((current_ekran.position_cursor_x < COL_TMO_UMAX2_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TMO_UMAX2_END))
                    current_ekran.position_cursor_x = COL_TMO_UMAX2_BEGIN;
                }

                //������� ����� �������� Umax
                int group = (current_ekran.current_level - EKRAN_TIMEOUT_UMAX_GROUP1);
                make_ekran_timeout_Umax(group);
              }
              else if(current_ekran.current_level == EKRAN_CONTROL_UMAX)
              {
                unsigned int maska = 0;
          
                //��������, ���� �� ����� �����
                if      (current_ekran.index_position == INDEX_CTR_UMAX1          ) maska = CTR_UMAX1;
                else if (current_ekran.index_position == INDEX_CTR_PO_UMAX1_OR_AND) maska = CTR_PO_UMAX1_OR_AND;
                else if (current_ekran.index_position == INDEX_CTR_UMAX2          ) maska = CTR_UMAX2;
                else if (current_ekran.index_position == INDEX_CTR_PO_UMAX2_OR_AND) maska = CTR_PO_UMAX2_OR_AND;
                
                //̳����� �� ����������� ��������� �� ��� ������� �������
                edition_settings.control_Umax ^= maska;

                //������� ����� ����������� ���������� ��� Umax
                 make_ekran_control_Umax();
              }
              else if(
                      (current_ekran.current_level >= EKRAN_SETPOINT_AVR_UMIN_GROUP1) &&
                      (current_ekran.current_level <= EKRAN_SETPOINT_AVR_UMIN_GROUP4)
                     )   
              {
                if(current_ekran.index_position == INDEX_ML_STPAVR_TN1_U1_UMIN)
                {
                  if (current_ekran.position_cursor_x == COL_SETPOINT_AVR_TN1_U1_UMIN_COMMA )current_ekran.position_cursor_x++;
                  if ((current_ekran.position_cursor_x < COL_SETPOINT_AVR_TN1_U1_UMIN_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_SETPOINT_AVR_TN1_U1_UMIN_END))
                    current_ekran.position_cursor_x = COL_SETPOINT_AVR_TN1_U1_UMIN_BEGIN;
                }
                else if(current_ekran.index_position == INDEX_ML_STPAVR_TN1_U2_LOW_WORK)
                {
                  if (current_ekran.position_cursor_x == COL_SETPOINT_AVR_TN1_U2_LOW_WORK_COMMA )current_ekran.position_cursor_x++;
                  if ((current_ekran.position_cursor_x < COL_SETPOINT_AVR_TN1_U2_LOW_WORK_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_SETPOINT_AVR_TN1_U2_LOW_WORK_END))
                    current_ekran.position_cursor_x = COL_SETPOINT_AVR_TN1_U2_LOW_WORK_BEGIN;
                }
                else if(current_ekran.index_position == INDEX_ML_STPAVR_TN2_U2_UMIN)
                {
                  if (current_ekran.position_cursor_x == COL_SETPOINT_AVR_TN2_U2_UMIN_COMMA )current_ekran.position_cursor_x++;
                  if ((current_ekran.position_cursor_x < COL_SETPOINT_AVR_TN2_U2_UMIN_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_SETPOINT_AVR_TN2_U2_UMIN_END))
                    current_ekran.position_cursor_x = COL_SETPOINT_AVR_TN2_U2_UMIN_BEGIN;
                }
                else if(current_ekran.index_position == INDEX_ML_STPAVR_TN2_U1_LOW_WORK)
                {
                  if (current_ekran.position_cursor_x == COL_SETPOINT_AVR_TN2_U1_LOW_WORK_COMMA )current_ekran.position_cursor_x++;
                  if ((current_ekran.position_cursor_x < COL_SETPOINT_AVR_TN2_U1_LOW_WORK_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_SETPOINT_AVR_TN2_U1_LOW_WORK_END))
                    current_ekran.position_cursor_x = COL_SETPOINT_AVR_TN2_U1_LOW_WORK_BEGIN;
                }

                //������� ����� ������� ��� Umin
                int group = (current_ekran.current_level - EKRAN_SETPOINT_AVR_UMIN_GROUP1);
                make_ekran_setpoint_avr_Umin(group);
              }
              else if(
                      (current_ekran.current_level >= EKRAN_SETPOINT_AVR_UMAX_GROUP1) &&
                      (current_ekran.current_level <= EKRAN_SETPOINT_AVR_UMAX_GROUP4)
                     )   
              {
                if(current_ekran.index_position == INDEX_ML_STPAVR_TN1_U1_UMAX)
                {
                  if (current_ekran.position_cursor_x == COL_SETPOINT_AVR_TN1_U1_UMAX_COMMA )current_ekran.position_cursor_x++;
                  if ((current_ekran.position_cursor_x < COL_SETPOINT_AVR_TN1_U1_UMAX_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_SETPOINT_AVR_TN1_U1_UMAX_END))
                    current_ekran.position_cursor_x = COL_SETPOINT_AVR_TN1_U1_UMAX_BEGIN;
                }
                else if(current_ekran.index_position == INDEX_ML_STPAVR_TN1_U2_HIGH_WORK)
                {
                  if (current_ekran.position_cursor_x == COL_SETPOINT_AVR_TN1_U2_HIGH_WORK_COMMA )current_ekran.position_cursor_x++;
                  if ((current_ekran.position_cursor_x < COL_SETPOINT_AVR_TN1_U2_HIGH_WORK_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_SETPOINT_AVR_TN1_U2_HIGH_WORK_END))
                    current_ekran.position_cursor_x = COL_SETPOINT_AVR_TN1_U2_HIGH_WORK_BEGIN;
                }
                else if(current_ekran.index_position == INDEX_ML_STPAVR_TN2_U2_UMAX)
                {
                  if (current_ekran.position_cursor_x == COL_SETPOINT_AVR_TN2_U2_UMAX_COMMA )current_ekran.position_cursor_x++;
                  if ((current_ekran.position_cursor_x < COL_SETPOINT_AVR_TN2_U2_UMAX_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_SETPOINT_AVR_TN2_U2_UMAX_END))
                    current_ekran.position_cursor_x = COL_SETPOINT_AVR_TN2_U2_UMAX_BEGIN;
                }
                else if(current_ekran.index_position == INDEX_ML_STPAVR_TN2_U1_HIGH_WORK)
                {
                  if (current_ekran.position_cursor_x == COL_SETPOINT_AVR_TN2_U1_HIGH_WORK_COMMA )current_ekran.position_cursor_x++;
                  if ((current_ekran.position_cursor_x < COL_SETPOINT_AVR_TN2_U1_HIGH_WORK_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_SETPOINT_AVR_TN2_U1_HIGH_WORK_END))
                    current_ekran.position_cursor_x = COL_SETPOINT_AVR_TN2_U1_HIGH_WORK_BEGIN;
                }

                //������� ����� ������� ��� Umax
                int group = (current_ekran.current_level - EKRAN_SETPOINT_AVR_UMAX_GROUP1);
                make_ekran_setpoint_avr_Umax(group);
              }
              else if(
                      (current_ekran.current_level >= EKRAN_TIMEOUT_AVR_GENERAL_GROUP1) &&
                      (current_ekran.current_level <= EKRAN_TIMEOUT_AVR_GENERAL_GROUP4)
                     )  
              {
                if(current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_BLK_K1)
                {
                  if (current_ekran.position_cursor_x == COL_TMO_AVR_GENERAL_BLK_K1_COMMA )current_ekran.position_cursor_x++;
                  if ((current_ekran.position_cursor_x < COL_TMO_AVR_GENERAL_BLK_K1_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TMO_AVR_GENERAL_BLK_K1_END))
                    current_ekran.position_cursor_x = COL_TMO_AVR_GENERAL_BLK_K1_BEGIN;
                }
                else if(current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_PUSK_K1)
                {
                  if (current_ekran.position_cursor_x == COL_TMO_AVR_GENERAL_PUSK_K1_COMMA )current_ekran.position_cursor_x++;
                  if ((current_ekran.position_cursor_x < COL_TMO_AVR_GENERAL_PUSK_K1_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TMO_AVR_GENERAL_PUSK_K1_END))
                    current_ekran.position_cursor_x = COL_TMO_AVR_GENERAL_PUSK_K1_BEGIN;
                }
                else if (current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_D_DIJI_K1)
                {
                  if (current_ekran.position_cursor_x == COL_TMO_AVR_GENERAL_D_DIJI_K1_COMMA )current_ekran.position_cursor_x++;
                  if ((current_ekran.position_cursor_x < COL_TMO_AVR_GENERAL_D_DIJI_K1_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TMO_AVR_GENERAL_D_DIJI_K1_END))
                    current_ekran.position_cursor_x = COL_TMO_AVR_GENERAL_D_DIJI_K1_BEGIN;
                }
                else if (current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_VVIMK_REZ_K1)
                {
                  if (current_ekran.position_cursor_x == COL_TMO_AVR_GENERAL_VVIMK_REZ_K1_COMMA )current_ekran.position_cursor_x++;
                  if ((current_ekran.position_cursor_x < COL_TMO_AVR_GENERAL_VVIMK_REZ_K1_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TMO_AVR_GENERAL_VVIMK_REZ_K1_END))
                    current_ekran.position_cursor_x = COL_TMO_AVR_GENERAL_VVIMK_REZ_K1_BEGIN;
                }
                else if (current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_VVIMK_K1)
                {
                  if (current_ekran.position_cursor_x == COL_TMO_AVR_GENERAL_VVIMK_K1_COMMA )current_ekran.position_cursor_x++;
                  if ((current_ekran.position_cursor_x < COL_TMO_AVR_GENERAL_VVIMK_K1_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TMO_AVR_GENERAL_VVIMK_K1_END))
                    current_ekran.position_cursor_x = COL_TMO_AVR_GENERAL_VVIMK_K1_BEGIN;
                }
                else if (current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_VYMK_K1)
                {
                  if (current_ekran.position_cursor_x == COL_TMO_AVR_GENERAL_VYMK_K1_COMMA )current_ekran.position_cursor_x++;
                  if ((current_ekran.position_cursor_x < COL_TMO_AVR_GENERAL_VYMK_K1_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TMO_AVR_GENERAL_VYMK_K1_END))
                    current_ekran.position_cursor_x = COL_TMO_AVR_GENERAL_VYMK_K1_BEGIN;
                }
                else if(current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_BLK_K2)
                {
                  if (current_ekran.position_cursor_x == COL_TMO_AVR_GENERAL_BLK_K2_COMMA )current_ekran.position_cursor_x++;
                  if ((current_ekran.position_cursor_x < COL_TMO_AVR_GENERAL_BLK_K2_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TMO_AVR_GENERAL_BLK_K2_END))
                    current_ekran.position_cursor_x = COL_TMO_AVR_GENERAL_BLK_K2_BEGIN;
                }
                else if(current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_PUSK_K2)
                {
                  if (current_ekran.position_cursor_x == COL_TMO_AVR_GENERAL_PUSK_K2_COMMA )current_ekran.position_cursor_x++;
                  if ((current_ekran.position_cursor_x < COL_TMO_AVR_GENERAL_PUSK_K2_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TMO_AVR_GENERAL_PUSK_K2_END))
                    current_ekran.position_cursor_x = COL_TMO_AVR_GENERAL_PUSK_K2_BEGIN;
                }
                else if (current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_D_DIJI_K2)
                {
                  if (current_ekran.position_cursor_x == COL_TMO_AVR_GENERAL_D_DIJI_K2_COMMA )current_ekran.position_cursor_x++;
                  if ((current_ekran.position_cursor_x < COL_TMO_AVR_GENERAL_D_DIJI_K2_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TMO_AVR_GENERAL_D_DIJI_K2_END))
                    current_ekran.position_cursor_x = COL_TMO_AVR_GENERAL_D_DIJI_K2_BEGIN;
                }
                else if (current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_VVIMK_REZ_K2)
                {
                  if (current_ekran.position_cursor_x == COL_TMO_AVR_GENERAL_VVIMK_REZ_K2_COMMA )current_ekran.position_cursor_x++;
                  if ((current_ekran.position_cursor_x < COL_TMO_AVR_GENERAL_VVIMK_REZ_K2_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TMO_AVR_GENERAL_VVIMK_REZ_K2_END))
                    current_ekran.position_cursor_x = COL_TMO_AVR_GENERAL_VVIMK_REZ_K2_BEGIN;
                }
                else if (current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_VVIMK_K2)
                {
                  if (current_ekran.position_cursor_x == COL_TMO_AVR_GENERAL_VVIMK_K2_COMMA )current_ekran.position_cursor_x++;
                  if ((current_ekran.position_cursor_x < COL_TMO_AVR_GENERAL_VVIMK_K2_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TMO_AVR_GENERAL_VVIMK_K2_END))
                    current_ekran.position_cursor_x = COL_TMO_AVR_GENERAL_VVIMK_K2_BEGIN;
                }
                else if (current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_VYMK_K2)
                {
                  if (current_ekran.position_cursor_x == COL_TMO_AVR_GENERAL_VYMK_K2_COMMA )current_ekran.position_cursor_x++;
                  if ((current_ekran.position_cursor_x < COL_TMO_AVR_GENERAL_VYMK_K2_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TMO_AVR_GENERAL_VYMK_K2_END))
                    current_ekran.position_cursor_x = COL_TMO_AVR_GENERAL_VYMK_K2_BEGIN;
                }

                //������� ����� �������� ��� (��������)
                int group = (current_ekran.current_level - EKRAN_TIMEOUT_AVR_GENERAL_GROUP1);
                make_ekran_timeout_avr_general(group);
              }
              else if(
                      (current_ekran.current_level >= EKRAN_TIMEOUT_AVR_UMIN_GROUP1) &&
                      (current_ekran.current_level <= EKRAN_TIMEOUT_AVR_UMIN_GROUP4)
                     )  
              {
                if (current_ekran.index_position == INDEX_ML_TMOAVR_UMIN_VYMK_ROB_K1)
                {
                  if (current_ekran.position_cursor_x == COL_TMO_AVR_UMIN_VYMK_ROB_K1_COMMA )current_ekran.position_cursor_x++;
                  if ((current_ekran.position_cursor_x < COL_TMO_AVR_UMIN_VYMK_ROB_K1_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TMO_AVR_UMIN_VYMK_ROB_K1_END))
                    current_ekran.position_cursor_x = COL_TMO_AVR_UMIN_VYMK_ROB_K1_BEGIN;
                }
                else if (current_ekran.index_position == INDEX_ML_TMOAVR_UMIN_VYMK_ROB_K2)
                {
                  if (current_ekran.position_cursor_x == COL_TMO_AVR_UMIN_VYMK_ROB_K2_COMMA )current_ekran.position_cursor_x++;
                  if ((current_ekran.position_cursor_x < COL_TMO_AVR_UMIN_VYMK_ROB_K2_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TMO_AVR_UMIN_VYMK_ROB_K2_END))
                    current_ekran.position_cursor_x = COL_TMO_AVR_UMIN_VYMK_ROB_K2_BEGIN;
                }

                //������� ����� �������� ��� Umin      
                int group = (current_ekran.current_level - EKRAN_TIMEOUT_AVR_UMIN_GROUP1);
                make_ekran_timeout_avr_Umin(group);
              }
              else if(
                      (current_ekran.current_level >= EKRAN_TIMEOUT_AVR_UMAX_GROUP1) &&
                      (current_ekran.current_level <= EKRAN_TIMEOUT_AVR_UMAX_GROUP4)
                     )  
              {
                if (current_ekran.index_position == INDEX_ML_TMOAVR_UMAX_VYMK_ROB_K1)
                {
                  if (current_ekran.position_cursor_x == COL_TMO_AVR_UMAX_VYMK_ROB_K1_COMMA )current_ekran.position_cursor_x++;
                  if ((current_ekran.position_cursor_x < COL_TMO_AVR_UMAX_VYMK_ROB_K1_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TMO_AVR_UMAX_VYMK_ROB_K1_END))
                    current_ekran.position_cursor_x = COL_TMO_AVR_UMAX_VYMK_ROB_K1_BEGIN;
                }
                else if (current_ekran.index_position == INDEX_ML_TMOAVR_UMAX_VYMK_ROB_K2)
                {
                  if (current_ekran.position_cursor_x == COL_TMO_AVR_UMAX_VYMK_ROB_K2_COMMA )current_ekran.position_cursor_x++;
                  if ((current_ekran.position_cursor_x < COL_TMO_AVR_UMAX_VYMK_ROB_K2_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TMO_AVR_UMAX_VYMK_ROB_K2_END))
                    current_ekran.position_cursor_x = COL_TMO_AVR_UMAX_VYMK_ROB_K2_BEGIN;
                }

                //������� ����� �������� ��� Umax      
                int group = (current_ekran.current_level - EKRAN_TIMEOUT_AVR_UMAX_GROUP1);
                make_ekran_timeout_avr_Umax(group);
              }
              else if(current_ekran.current_level == EKRAN_CONTROL_AVR)
              {
                unsigned int maska = 0;
          
                //��������, ���� �� ����� �����
                if      (current_ekran.index_position == INDEX_CTR_AVR     ) maska = CTR_AVR;
                else if (current_ekran.index_position == INDEX_CTR_AVR_UMAX) maska = CTR_AVR_UMAX;
                else if (current_ekran.index_position == INDEX_CTR_AVR_BLK ) maska = CTR_AVR_BLK;
                
                //̳����� �� ����������� ��������� �� ��� ������� �������
                edition_settings.control_avr ^= maska;

                //������� ����� ����������� ���������� ��� ���
                 make_ekran_control_avr();
              }
              else if(
                      (current_ekran.current_level >= EKRAN_SETPOINT_CTRL_PHASE_GROUP1) &&
                      (current_ekran.current_level <= EKRAN_SETPOINT_CTRL_PHASE_GROUP4)
                     )   
              {
                if(current_ekran.index_position == INDEX_ML_STPCTRL_PHASE_U)
                {
                  if (current_ekran.position_cursor_x == COL_SETPOINT_CTRL_PHASE_U_COMMA )current_ekran.position_cursor_x++;
                  if ((current_ekran.position_cursor_x < COL_SETPOINT_CTRL_PHASE_U_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_SETPOINT_CTRL_PHASE_U_END))
                    current_ekran.position_cursor_x = COL_SETPOINT_CTRL_PHASE_U_BEGIN;
                }
                else if(current_ekran.index_position == INDEX_ML_STPCTRL_PHASE_PHI)
                {
                  if (current_ekran.position_cursor_x == COL_SETPOINT_CTRL_PHASE_PHI_COMMA )current_ekran.position_cursor_x++;
                  if ((current_ekran.position_cursor_x < COL_SETPOINT_CTRL_PHASE_PHI_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_SETPOINT_CTRL_PHASE_PHI_END))
                    current_ekran.position_cursor_x = COL_SETPOINT_CTRL_PHASE_PHI_BEGIN;
                }
                else if(current_ekran.index_position == INDEX_ML_STPCTRL_PHASE_F)
                {
                  if (current_ekran.position_cursor_x == COL_SETPOINT_CTRL_PHASE_F_COMMA )current_ekran.position_cursor_x++;
                  if ((current_ekran.position_cursor_x < COL_SETPOINT_CTRL_PHASE_F_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_SETPOINT_CTRL_PHASE_F_END))
                    current_ekran.position_cursor_x = COL_SETPOINT_CTRL_PHASE_F_BEGIN;
                }

                //������� ����� ������� "�������� ���������"
                int group = (current_ekran.current_level - EKRAN_SETPOINT_CTRL_PHASE_GROUP1);
                make_ekran_setpoint_ctrl_phase(group);
              }
              else if(
                      (current_ekran.current_level >= EKRAN_TIMEOUT_CTRL_PHASE_GROUP1) &&
                      (current_ekran.current_level <= EKRAN_TIMEOUT_CTRL_PHASE_GROUP4)
                     )  
              {
                if(current_ekran.index_position == INDEX_ML_TMOCTRL_PHASE_U)
                {
                  if (current_ekran.position_cursor_x == COL_TMO_CTRL_PHASE_U_COMMA )current_ekran.position_cursor_x++;
                  if ((current_ekran.position_cursor_x < COL_TMO_CTRL_PHASE_U_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TMO_CTRL_PHASE_U_END))
                    current_ekran.position_cursor_x = COL_TMO_CTRL_PHASE_U_BEGIN;
                }
                else if(current_ekran.index_position == INDEX_ML_TMOCTRL_PHASE_U_D)
                {
                  if (current_ekran.position_cursor_x == COL_TMO_CTRL_PHASE_U_D_COMMA )current_ekran.position_cursor_x++;
                  if ((current_ekran.position_cursor_x < COL_TMO_CTRL_PHASE_U_D_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TMO_CTRL_PHASE_U_D_END))
                    current_ekran.position_cursor_x = COL_TMO_CTRL_PHASE_U_D_BEGIN;
                }
                else if(current_ekran.index_position == INDEX_ML_TMOCTRL_PHASE_PHI)
                {
                  if (current_ekran.position_cursor_x == COL_TMO_CTRL_PHASE_PHI_COMMA )current_ekran.position_cursor_x++;
                  if ((current_ekran.position_cursor_x < COL_TMO_CTRL_PHASE_PHI_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TMO_CTRL_PHASE_PHI_END))
                    current_ekran.position_cursor_x = COL_TMO_CTRL_PHASE_PHI_BEGIN;
                }
                else if(current_ekran.index_position == INDEX_ML_TMOCTRL_PHASE_PHI_D)
                {
                  if (current_ekran.position_cursor_x == COL_TMO_CTRL_PHASE_PHI_D_COMMA )current_ekran.position_cursor_x++;
                  if ((current_ekran.position_cursor_x < COL_TMO_CTRL_PHASE_PHI_D_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TMO_CTRL_PHASE_PHI_D_END))
                    current_ekran.position_cursor_x = COL_TMO_CTRL_PHASE_PHI_D_BEGIN;
                }
                else if (current_ekran.index_position == INDEX_ML_TMOCTRL_PHASE_F)
                {
                  if (current_ekran.position_cursor_x == COL_TMO_CTRL_PHASE_F_COMMA )current_ekran.position_cursor_x++;
                  if ((current_ekran.position_cursor_x < COL_TMO_CTRL_PHASE_F_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TMO_CTRL_PHASE_F_END))
                    current_ekran.position_cursor_x = COL_TMO_CTRL_PHASE_F_BEGIN;
                }
                else if (current_ekran.index_position == INDEX_ML_TMOCTRL_PHASE_F_D)
                {
                  if (current_ekran.position_cursor_x == COL_TMO_CTRL_PHASE_F_D_COMMA )current_ekran.position_cursor_x++;
                  if ((current_ekran.position_cursor_x < COL_TMO_CTRL_PHASE_F_D_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TMO_CTRL_PHASE_F_D_END))
                    current_ekran.position_cursor_x = COL_TMO_CTRL_PHASE_F_D_BEGIN;
                }

                //������� ����� �������� "�������� ���������"
                int group = (current_ekran.current_level - EKRAN_TIMEOUT_CTRL_PHASE_GROUP1);
                make_ekran_timeout_ctrl_phase(group);
              }
              else if(current_ekran.current_level == EKRAN_CONTROL_CTRL_PHASE)
              {
                unsigned int maska = 0;
          
                //��������, ���� �� ����� �����
                if      (current_ekran.index_position == INDEX_CTR_CTRL_PHASE_U      ) maska = CTR_CTRL_PHASE_U;
                else if (current_ekran.index_position == INDEX_CTR_CTRL_PHASE_PHI    ) maska = CTR_CTRL_PHASE_PHI;
                else if (current_ekran.index_position == INDEX_CTR_CTRL_PHASE_F      ) maska = CTR_CTRL_PHASE_F;
                else if (current_ekran.index_position == INDEX_CTR_CTRL_PHASE_SEQ_TN1) maska = CTR_CTRL_PHASE_SEQ_TN1;
                else if (current_ekran.index_position == INDEX_CTR_CTRL_PHASE_SEQ_TN2) maska = CTR_CTRL_PHASE_SEQ_TN2;
                
                //̳����� �� ����������� ��������� �� ��� ������� �������
                edition_settings.control_ctrl_phase ^= maska;

                //������� ����� ����������� ���������� ��� "�������� ���������"
                 make_ekran_control_ctrl_phase();
              }
              else if(current_ekran.current_level == EKRAN_TRANSFORMATOR_INFO_SETPOINT)
              {
                if (current_ekran.index_position == INDEX_ML_TT)
                {
                  if ((current_ekran.position_cursor_x < COL_TT_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TT_END))
                    current_ekran.position_cursor_x = COL_TT_BEGIN;
                }
                else
                {
                  if ((current_ekran.position_cursor_x < COL_TN_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TN_END))
                    current_ekran.position_cursor_x = COL_TN_BEGIN;
                }
                //������� ����� ����������� ���������� �� ���������������
                make_ekran_transformator();
              }
              else if(current_ekran.current_level == EKRAN_TRANSFORMATOR_INFO_CONTROL)
              {
                //��������, ���� �� ����� �����
                unsigned int maska = (1 << current_ekran.index_position);
                
                //̳����� �� ����������� ��������� �� ��� ������� �������
                edition_settings.control_transformator ^= maska;

                //������� ����� ����������� ����������� ���� "�������������"
                make_ekran_transformator_control();
              }
              else if(current_ekran.current_level == EKRAN_SETPOINT_SWITCH)
              {
                if(current_ekran.index_position == INDEX_ML_STPInom)
                {
                  if ((current_ekran.position_cursor_x < COL_SETPOINT_Inom_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_SETPOINT_Inom_END))
                    current_ekran.position_cursor_x = COL_SETPOINT_Inom_BEGIN;
                }
                else if (current_ekran.index_position == INDEX_ML_STPRKS_Inom)
                {
                  if ((current_ekran.position_cursor_x < COL_SETPOINT_RKS_Inom_BEGIN) ||
                      (current_ekran.position_cursor_x > (COL_SETPOINT_RKS_Inom_END - 1)))
                    current_ekran.position_cursor_x = COL_SETPOINT_RKS_Inom_BEGIN;
                }
                else if (current_ekran.index_position == INDEX_ML_STPMInom_vymk)
                {
                  if (current_ekran.position_cursor_x == COL_SETPOINT_Inom_vymk_COMMA )current_ekran.position_cursor_x++;
                  if ((current_ekran.position_cursor_x < COL_SETPOINT_Inom_vymk_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_SETPOINT_Inom_vymk_END))
                    current_ekran.position_cursor_x = COL_SETPOINT_Inom_vymk_BEGIN;
                }
                else if (current_ekran.index_position == INDEX_ML_STPRKS_Inom_vymk)
                {
                  if ((current_ekran.position_cursor_x < COL_SETPOINT_RKS_Inom_vymk_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_SETPOINT_RKS_Inom_vymk_END))
                    current_ekran.position_cursor_x = COL_SETPOINT_RKS_Inom_vymk_BEGIN;
                }
                else if (current_ekran.index_position == INDEX_ML_STPPOCHATKOVYJ_RESURS)
                {
                  if ((current_ekran.position_cursor_x < COL_SETPOINT_POCHATKOVYJ_RESURS_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_SETPOINT_POCHATKOVYJ_RESURS_END))
                    current_ekran.position_cursor_x = COL_SETPOINT_POCHATKOVYJ_RESURS_BEGIN;
                }
                else if (current_ekran.index_position == INDEX_ML_STPKRYTYCHNYJ_RESURS)
                {
                  if ((current_ekran.position_cursor_x < COL_SETPOINT_KRYTYCHNYJ_RESURS_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_SETPOINT_KRYTYCHNYJ_RESURS_END))
                    current_ekran.position_cursor_x = COL_SETPOINT_KRYTYCHNYJ_RESURS_BEGIN;
                }
                else if (current_ekran.index_position == INDEX_ML_STPPOCHATKOVA_K_VYMK)
                {
                  if ((current_ekran.position_cursor_x < COL_SETPOINT_POCHATKOVA_K_VYMK_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_SETPOINT_POCHATKOVA_K_VYMK_END))
                    current_ekran.position_cursor_x = COL_SETPOINT_POCHATKOVA_K_VYMK_BEGIN;
                }
                //������� ����� ������� �����������
                make_ekran_setpoint_switch();
              }
              else if(current_ekran.current_level == EKRAN_TIMEOUT_SWITCH)
              {
                if(current_ekran.index_position == INDEX_ML_TMOON)
                {
                  if (current_ekran.position_cursor_x == COL_TMO_SWCH_ON_COMMA )current_ekran.position_cursor_x++;
                  if ((current_ekran.position_cursor_x < COL_TMO_SWCH_ON_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TMO_SWCH_ON_END))
                    current_ekran.position_cursor_x = COL_TMO_SWCH_ON_BEGIN;
                }
                else if (current_ekran.index_position == INDEX_ML_TMOOFF)
                {
                  if (current_ekran.position_cursor_x == COL_TMO_SWCH_OFF_COMMA )current_ekran.position_cursor_x++;
                  if ((current_ekran.position_cursor_x < COL_TMO_SWCH_OFF_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TMO_SWCH_OFF_END))
                    current_ekran.position_cursor_x = COL_TMO_SWCH_OFF_BEGIN;
                }
                else if (current_ekran.index_position == INDEX_ML_TMOUDL_BLK_ON)
                {
                  if (current_ekran.position_cursor_x == COL_TMO_SWCH_UDL_BLK_ON_COMMA )current_ekran.position_cursor_x++;
                  if ((current_ekran.position_cursor_x < COL_TMO_SWCH_UDL_BLK_ON_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TMO_SWCH_UDL_BLK_ON_END))
                    current_ekran.position_cursor_x = COL_TMO_SWCH_UDL_BLK_ON_BEGIN;
                }
                else if (current_ekran.index_position == INDEX_ML_TMOPRYVODA_VV)
                {
                  if (current_ekran.position_cursor_x == COL_TMO_PRYVODA_VV_COMMA )current_ekran.position_cursor_x++;
                  if ((current_ekran.position_cursor_x < COL_TMO_PRYVODA_VV_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TMO_PRYVODA_VV_END))
                    current_ekran.position_cursor_x = COL_TMO_PRYVODA_VV_BEGIN;
                }
                //������� ����� �������� �����������
                make_ekran_timeout_switch();
              }
              else if(current_ekran.current_level == EKRAN_CONTROL_SWITCH)
              {
                unsigned int maska = 0;
          
                //��������, ���� �� ����� �����
                if      (current_ekran.index_position == INDEX_ML_CTRPRYVOD_VV) maska = CTR_PRYVOD_VV;
                else if (current_ekran.index_position == INDEX_ML_CTRRESURS_VV) maska = CTR_RESURS_VV;
                
                //̳����� �� ����������� ��������� �� ��� ������� �������
                edition_settings.control_switch ^= maska;

                //������� ����� ����������� ���������� �����������
                 make_ekran_control_switch();
              }
              else if(current_ekran.current_level == EKRAN_DOPUSK_DV_UVV)
              {
                if (
                    (current_ekran.position_cursor_x < COL_DOPUSK_DV_BEGIN )
                    ||
                    (current_ekran.position_cursor_x > COL_DOPUSK_DV_END   )
                    ||  
                    (
                     (current_ekran.position_cursor_x == COL_DOPUSK_DV_END) &&
                     ((current_settings.type_of_input_signal & (1 << current_ekran.index_position)) != 0)
                    )
                   )
                  current_ekran.position_cursor_x = COL_DOPUSK_DV_BEGIN;

                //������� ����� ���������� �� �������� ��
                make_ekran_dopusk_dv();
              }
              else if((current_ekran.current_level == EKRAN_TYPE_INPUT_UVV ) || (current_ekran.current_level == EKRAN_TYPE_INPUT_SIGNAL_UVV) ||
                      (current_ekran.current_level == EKRAN_TYPE_LED_UVV   ))
              {
                unsigned int value = (1 << current_ekran.index_position);
          
                //̳����� �� ����������� ��������� �� ��� ������� ������� � ������� ����� ����������� ���������� ��� ���
                if (current_ekran.current_level == EKRAN_TYPE_INPUT_UVV)
                {
                  edition_settings.type_of_input ^= value;
                  make_ekran_type_input_uvv(0);
                }
                else if (current_ekran.current_level == EKRAN_TYPE_INPUT_SIGNAL_UVV)
                {
                  edition_settings.type_of_input_signal ^= value;
                  make_ekran_type_input_uvv(1);
                }
                else 
                {
                  edition_settings.type_of_led ^= value;
                  make_ekran_type_led_uvv();
                }
              }
              else if(current_ekran.current_level == EKRAN_TYPE_OUTPUT_UVV)
              {
                unsigned int maska = (1 << current_ekran.index_position);
                
                int value = ((edition_settings.type_of_output & maska) != 0);
                if (value == true) value += ((edition_settings.type_of_output_modif & maska) != 0); //����� � �������, ���� ����� ����������
                if ((++value) >= 3) value = 0;
                
                if (value == 0)
                {
                  edition_settings.type_of_output       &= (unsigned int)(~maska);
                  edition_settings.type_of_output_modif &= (unsigned int)(~maska);
                }
                else
                {
                  edition_settings.type_of_output |= maska;
                  if (value == 1) edition_settings.type_of_output_modif &= (unsigned int)(~maska);
                  else edition_settings.type_of_output_modif |= maska;
                }

                make_ekran_type_output_uvv();
              }
              else if(current_ekran.current_level == EKRAN_ADDRESS)
              {
                if ((current_ekran.position_cursor_x < COL_ADDRESS_BEGIN) ||
                    (current_ekran.position_cursor_x > COL_ADDRESS_END))
                  current_ekran.position_cursor_x = COL_ADDRESS_BEGIN;
                //������� ����� ���������� �� �������������� �����
                make_ekran_address();
              }
              else if(current_ekran.current_level == EKRAN_VIEW_TIMEOUT_RS485)
              {
                if (current_ekran.position_cursor_x == COL_TIMEOUT_INTERFACE_COMMA )current_ekran.position_cursor_x++;
                if ((current_ekran.position_cursor_x < COL_TIMEOUT_INTERFACE_BEGIN) ||
                    (current_ekran.position_cursor_x > COL_TIMEOUT_INTERFACE_END))
                  current_ekran.position_cursor_x = COL_TIMEOUT_INTERFACE_BEGIN;
                //������� ����� ���������� �� time-out ���������� �������
                make_ekran_timeout_interface();
              }
              else if(current_ekran.current_level == EKRAN_GENERAL_PICKUPS_EL)
              {
                if(current_ekran.index_position == INDEX_ML_NUMBER_INERATION)
                {
                  if ((current_ekran.position_cursor_x < COL_NUMBER_INERATION_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_NUMBER_INERATION_END))
                    current_ekran.position_cursor_x = COL_NUMBER_INERATION_BEGIN;
                }
//                else if(current_ekran.index_position == INDEX_ML_NUMBER_DEFINED_FUNCTIONS)
//                {
//                  if ((current_ekran.position_cursor_x < COL_NUMBER_DEFINED_FUNCTIONS_BEGIN) ||
//                      (current_ekran.position_cursor_x > COL_NUMBER_DEFINED_FUNCTIONS_END))
//                    current_ekran.position_cursor_x = COL_NUMBER_DEFINED_FUNCTIONS_BEGIN;
//                }
//                else if(current_ekran.index_position == INDEX_ML_NUMBER_DEFINED_TRIGGERS)
//                {
//                  if ((current_ekran.position_cursor_x < COL_NUMBER_DEFINED_TRIGGERS_BEGIN) ||
//                      (current_ekran.position_cursor_x > COL_NUMBER_DEFINED_TRIGGERS_END))
//                    current_ekran.position_cursor_x = COL_NUMBER_DEFINED_TRIGGERS_BEGIN;
//                }
//                else if(current_ekran.index_position == INDEX_ML_NUMBER_DEFINED_AND)
//                {
//                  if ((current_ekran.position_cursor_x < COL_NUMBER_DEFINED_AND_BEGIN) ||
//                      (current_ekran.position_cursor_x > COL_NUMBER_DEFINED_AND_END))
//                    current_ekran.position_cursor_x = COL_NUMBER_DEFINED_AND_BEGIN;
//                }
//                else if(current_ekran.index_position == INDEX_ML_NUMBER_DEFINED_OR)
//                {
//                  if ((current_ekran.position_cursor_x < COL_NUMBER_DEFINED_OR_BEGIN) ||
//                      (current_ekran.position_cursor_x > COL_NUMBER_DEFINED_OR_END))
//                    current_ekran.position_cursor_x = COL_NUMBER_DEFINED_OR_BEGIN;
//                }
//                else if(current_ekran.index_position == INDEX_ML_NUMBER_DEFINED_XOR)
//                {
//                  if ((current_ekran.position_cursor_x < COL_NUMBER_DEFINED_XOR_BEGIN) ||
//                      (current_ekran.position_cursor_x > COL_NUMBER_DEFINED_XOR_END))
//                    current_ekran.position_cursor_x = COL_NUMBER_DEFINED_XOR_BEGIN;
//                }
//                else if(current_ekran.index_position == INDEX_ML_NUMBER_DEFINED_NOT)
//                {
//                  if ((current_ekran.position_cursor_x < COL_NUMBER_DEFINED_NOT_BEGIN) ||
//                      (current_ekran.position_cursor_x > COL_NUMBER_DEFINED_NOT_END))
//                    current_ekran.position_cursor_x = COL_NUMBER_DEFINED_NOT_BEGIN;
//                }
                
                //������� ����� ����������� ��������� �������� ��� ��������� �����
                make_ekran_general_pickups_el();
              }
              else if(current_ekran.current_level == EKRAN_LIST_TYPE_DF)
              {
                unsigned int value = (1 << current_ekran.index_position);
          
                //̳����� �� ����������� ��������� �� ��� ������� �������
                edition_settings.type_df ^= value;

                //������� ����� ����������� ���� ������������� �������
                make_ekran_type_df();
              }
              else if((current_ekran.current_level >= EKRAN_TIMEOUT_DF1) && (current_ekran.current_level <= EKRAN_TIMEOUT_DF8))
              {
                if(current_ekran.index_position == INDEX_ML_TMO_DF_PAUSE)
                {
                  if (current_ekran.position_cursor_x == COL_TMO_DF_PAUSE_COMMA )current_ekran.position_cursor_x++;
                  if ((current_ekran.position_cursor_x < COL_TMO_DF_PAUSE_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TMO_DF_PAUSE_END))
                    current_ekran.position_cursor_x = COL_TMO_DF_PAUSE_BEGIN;
                }
                else
                {
                  if (current_ekran.position_cursor_x == COL_TMO_DF_WORK_COMMA )current_ekran.position_cursor_x++;
                  if ((current_ekran.position_cursor_x < COL_TMO_DF_WORK_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TMO_DF_WORK_END))
                    current_ekran.position_cursor_x = COL_TMO_DF_WORK_BEGIN;
                }
                //������� ����� ������� ������������ �������
                make_ekran_timeout_df(current_ekran.current_level - EKRAN_TIMEOUT_DF1);
              }
              else if(current_ekran.current_level == EKRAN_TIMEOUT_ANALOG_REGISTRATOR)
              {
                if(current_ekran.index_position == INDEX_ML_TMOPREFAULT)
                {
                  if (current_ekran.position_cursor_x == COL_TMO_PREFAULT_COMMA )current_ekran.position_cursor_x++;
                  if ((current_ekran.position_cursor_x < COL_TMO_PREFAULT_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TMO_PREFAULT_END))
                    current_ekran.position_cursor_x = COL_TMO_PREFAULT_BEGIN;
                }
                else
                {
                  if (current_ekran.position_cursor_x == COL_TMO_POSTFAULT_COMMA )current_ekran.position_cursor_x++;
                  if ((current_ekran.position_cursor_x < COL_TMO_POSTFAULT_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TMO_POSTFAULT_END))
                    current_ekran.position_cursor_x = COL_TMO_POSTFAULT_BEGIN;
                }
                //������� ����� �������� ����������� ����������
                make_ekran_timeout_analog_registrator();
              }
              else if(current_ekran.current_level == EKRAN_CHOSE_EXTRA_SETTINGS)
              {
                //��������, ���� �� ����� �����
                unsigned int maska = (1 << current_ekran.index_position);
                
                //̳����� �� ����������� ��������� �� ��� ������� �������
                edition_settings.control_extra_settings_1 ^= maska;

                //������� ����� ����������� ���������� �����������
                make_ekran_chose_extra_settings();
              }

              //�������� �����������, �� ��������� ������ 
              new_state_keyboard &= (unsigned int)(~(1<<BIT_KEY_RIGHT));
            }
            else if (new_state_keyboard == (1<<BIT_KEY_LEFT))
            {
              current_ekran.position_cursor_x--;
              //����������, �� �� �� ������ �� ��� ������� ��� �������� ���� �������, ��� ������� ����
              if (current_ekran.current_level == EKRAN_CONTROL_ZDZ)
              {
                unsigned int maska = 0;
          
                //��������, ���� �� ����� �����
                if (current_ekran.index_position == INDEX_ML_CTRZDZ_STATE) maska = CTR_ZDZ_STATE;
                else if (current_ekran.index_position == INDEX_ML_CTRZDZ_STARTED_FROM_MTZ1 ) maska = CTR_ZDZ_STARTED_FROM_MTZ1;
                else if (current_ekran.index_position == INDEX_ML_CTRZDZ_STARTED_FROM_MTZ2 ) maska = CTR_ZDZ_STARTED_FROM_MTZ2;
                else if (current_ekran.index_position == INDEX_ML_CTRZDZ_STARTED_FROM_MTZ3 ) maska = CTR_ZDZ_STARTED_FROM_MTZ3;
                else if (current_ekran.index_position == INDEX_ML_CTRZDZ_STARTED_FROM_MTZ4 ) maska = CTR_ZDZ_STARTED_FROM_MTZ4;
                
                //̳����� �� ����������� ��������� �� ��� ������� �������
                edition_settings.control_zdz ^= maska;

                //������� ����� ����������� ���������� ��� ���
                 make_ekran_control_zdz();
              }
              else if(
                      (current_ekran.current_level >= EKRAN_TIMEOUT_APV_GROUP1) &&
                      (current_ekran.current_level <= EKRAN_TIMEOUT_APV_GROUP4)
                     )   
              {
                if(current_ekran.index_position == INDEX_ML_TMOAPV1)
                {
                  if (current_ekran.position_cursor_x == COL_TMO_APV_1_COMMA )current_ekran.position_cursor_x--;
                  if ((current_ekran.position_cursor_x < COL_TMO_APV_1_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TMO_APV_1_END))
                    current_ekran.position_cursor_x = COL_TMO_APV_1_END;
                }
                else if(current_ekran.index_position == INDEX_ML_TMOAPV2)
                {
                  if (current_ekran.position_cursor_x == COL_TMO_APV_2_COMMA )current_ekran.position_cursor_x--;
                  if ((current_ekran.position_cursor_x < COL_TMO_APV_2_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TMO_APV_2_END))
                    current_ekran.position_cursor_x = COL_TMO_APV_2_END;
                }
                else if(current_ekran.index_position == INDEX_ML_TMOAPV3)
                {
                  if (current_ekran.position_cursor_x == COL_TMO_APV_3_COMMA )current_ekran.position_cursor_x--;
                  if ((current_ekran.position_cursor_x < COL_TMO_APV_3_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TMO_APV_3_END))
                    current_ekran.position_cursor_x = COL_TMO_APV_3_END;
                }
                else if(current_ekran.index_position == INDEX_ML_TMOAPV4)
                {
                  if (current_ekran.position_cursor_x == COL_TMO_APV_4_COMMA )current_ekran.position_cursor_x--;
                  if ((current_ekran.position_cursor_x < COL_TMO_APV_4_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TMO_APV_4_END))
                    current_ekran.position_cursor_x = COL_TMO_APV_4_END;
                }
                else if(current_ekran.index_position == INDEX_ML_TMOAPV_BLOCK_VID_APV1)
                {
                  if (current_ekran.position_cursor_x == COL_TMO_APV_BLOCK_VID_APV1_COMMA )current_ekran.position_cursor_x--;
                  if ((current_ekran.position_cursor_x < COL_TMO_APV_BLOCK_VID_APV1_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TMO_APV_BLOCK_VID_APV1_END))
                    current_ekran.position_cursor_x = COL_TMO_APV_BLOCK_VID_APV1_END;
                }
                else if(current_ekran.index_position == INDEX_ML_TMOAPV_BLOCK_VID_APV2)
                {
                  if (current_ekran.position_cursor_x == COL_TMO_APV_BLOCK_VID_APV2_COMMA )current_ekran.position_cursor_x--;
                  if ((current_ekran.position_cursor_x < COL_TMO_APV_BLOCK_VID_APV2_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TMO_APV_BLOCK_VID_APV2_END))
                    current_ekran.position_cursor_x = COL_TMO_APV_BLOCK_VID_APV2_END;
                }
                else if(current_ekran.index_position == INDEX_ML_TMOAPV_BLOCK_VID_APV3)
                {
                  if (current_ekran.position_cursor_x == COL_TMO_APV_BLOCK_VID_APV3_COMMA )current_ekran.position_cursor_x--;
                  if ((current_ekran.position_cursor_x < COL_TMO_APV_BLOCK_VID_APV3_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TMO_APV_BLOCK_VID_APV3_END))
                    current_ekran.position_cursor_x = COL_TMO_APV_BLOCK_VID_APV3_END;
                }
                else if(current_ekran.index_position == INDEX_ML_TMOAPV_BLOCK_VID_APV4)
                {
                  if (current_ekran.position_cursor_x == COL_TMO_APV_BLOCK_VID_APV4_COMMA )current_ekran.position_cursor_x--;
                  if ((current_ekran.position_cursor_x < COL_TMO_APV_BLOCK_VID_APV4_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TMO_APV_BLOCK_VID_APV4_END))
                    current_ekran.position_cursor_x = COL_TMO_APV_BLOCK_VID_APV4_END;
                }
                else if(current_ekran.index_position == INDEX_ML_TMOAPV_BLOCK_VID_VV)
                {
                  if (current_ekran.position_cursor_x == COL_TMO_APV_BLOCK_VID_VV_COMMA )current_ekran.position_cursor_x--;
                  if ((current_ekran.position_cursor_x < COL_TMO_APV_BLOCK_VID_VV_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TMO_APV_BLOCK_VID_VV_END))
                    current_ekran.position_cursor_x = COL_TMO_APV_BLOCK_VID_VV_END;
                }
                //������� ����� �������� ���
                int group = (current_ekran.current_level - EKRAN_TIMEOUT_APV_GROUP1);
                make_ekran_timeout_apv(group);
              }
              else if(current_ekran.current_level == EKRAN_CONTROL_APV)
              {
                unsigned int maska = 0;
          
                //��������, ���� �� ����� �����
                if (current_ekran.index_position == INDEX_ML_CTRAPV_STAGE_1) maska = CTR_APV_STAGE_1;
                else if (current_ekran.index_position == INDEX_ML_CTRAPV_STAGE_2) maska = CTR_APV_STAGE_2;
                else if (current_ekran.index_position == INDEX_ML_CTRAPV_STAGE_3) maska = CTR_APV_STAGE_3;
                else if (current_ekran.index_position == INDEX_ML_CTRAPV_STAGE_4) maska = CTR_APV_STAGE_4;
                else if (current_ekran.index_position == INDEX_ML_CTRAPV_STARTED_FROM_MTZ1) maska = CTR_APV_STARTED_FROM_MTZ1;
                else if (current_ekran.index_position == INDEX_ML_CTRAPV_STARTED_FROM_MTZ2) maska = CTR_APV_STARTED_FROM_MTZ2;
                else if (current_ekran.index_position == INDEX_ML_CTRAPV_STARTED_FROM_MTZ3) maska = CTR_APV_STARTED_FROM_MTZ3;
                else if (current_ekran.index_position == INDEX_ML_CTRAPV_STARTED_FROM_MTZ4) maska = CTR_APV_STARTED_FROM_MTZ4;
                
                //̳����� �� ����������� ��������� �� ��� ������� �������
                edition_settings.control_apv ^= maska;

                //������� ����� ����������� ���������� ��� ���
                 make_ekran_control_apv();
              }
              else if(
                      (current_ekran.current_level >= EKRAN_SETPOINT_UROV_GROUP1) &&
                      (current_ekran.current_level <= EKRAN_SETPOINT_UROV_GROUP4)
                     )   
              {
                if (current_ekran.position_cursor_x == COL_SETPOINT_UROV_COMMA )current_ekran.position_cursor_x--;
                if ((current_ekran.position_cursor_x < COL_SETPOINT_UROV_BEGIN) ||
                    (current_ekran.position_cursor_x > COL_SETPOINT_UROV_END))
                  current_ekran.position_cursor_x = COL_SETPOINT_UROV_END;

                //������� ����� ������� ����
                int group = (current_ekran.current_level - EKRAN_SETPOINT_UROV_GROUP1);
                make_ekran_setpoint_urov(group);
              }
              else if(
                      (current_ekran.current_level >= EKRAN_TIMEOUT_UROV_GROUP1) &&
                      (current_ekran.current_level <= EKRAN_TIMEOUT_UROV_GROUP4)
                     )   
              {
                if(current_ekran.index_position == INDEX_ML_TMOUROV1)
                {
                  if (current_ekran.position_cursor_x == COL_TMO_UROV_1_COMMA )current_ekran.position_cursor_x--;
                  if ((current_ekran.position_cursor_x < COL_TMO_UROV_1_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TMO_UROV_1_END))
                    current_ekran.position_cursor_x = COL_TMO_UROV_1_END;
                }
                else
                {
                  if (current_ekran.position_cursor_x == COL_TMO_UROV_2_COMMA )current_ekran.position_cursor_x--;
                  if ((current_ekran.position_cursor_x < COL_TMO_UROV_2_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TMO_UROV_2_END))
                    current_ekran.position_cursor_x = COL_TMO_UROV_2_END;
                }

                //������� ����� �������� ����
                int group = (current_ekran.current_level - EKRAN_TIMEOUT_UROV_GROUP1);
                 make_ekran_timeout_urov(group);
              }
              else if(current_ekran.current_level == EKRAN_CONTROL_UROV)
              {
                unsigned int maska = 0;
          
                //��������, ���� �� ����� �����
                if (current_ekran.index_position == INDEX_ML_CTRUROV_STATE) maska = CTR_UROV_STATE;
                else if (current_ekran.index_position == INDEX_ML_CTRUROV_STARTED_FROM_MTZ1   ) maska = CTR_UROV_STARTED_FROM_MTZ1;
                else if (current_ekran.index_position == INDEX_ML_CTRUROV_STARTED_FROM_MTZ2   ) maska = CTR_UROV_STARTED_FROM_MTZ2;
                else if (current_ekran.index_position == INDEX_ML_CTRUROV_STARTED_FROM_MTZ3   ) maska = CTR_UROV_STARTED_FROM_MTZ3;
                else if (current_ekran.index_position == INDEX_ML_CTRUROV_STARTED_FROM_MTZ4   ) maska = CTR_UROV_STARTED_FROM_MTZ4;
                else if (current_ekran.index_position == INDEX_ML_CTRUROV_STARTED_FROM_ZDZ    ) maska = CTR_UROV_STARTED_FROM_ZDZ;
                else if (current_ekran.index_position == INDEX_ML_CTRUROV_STARTED_FROM_ZOP1   ) maska = CTR_UROV_STARTED_FROM_ZOP1;
                else if (current_ekran.index_position == INDEX_ML_CTRUROV_STARTED_FROM_UMIN1  ) maska = CTR_UROV_STARTED_FROM_UMIN1;
                else if (current_ekran.index_position == INDEX_ML_CTRUROV_STARTED_FROM_UMIN2  ) maska = CTR_UROV_STARTED_FROM_UMIN2;
                else if (current_ekran.index_position == INDEX_ML_CTRUROV_STARTED_FROM_UMAX1  ) maska = CTR_UROV_STARTED_FROM_UMAX1;
                else if (current_ekran.index_position == INDEX_ML_CTRUROV_STARTED_FROM_UMAX2  ) maska = CTR_UROV_STARTED_FROM_UMAX2;
                
                //̳����� �� ����������� ��������� �� ��� ������� �������
                edition_settings.control_urov ^= maska;

                //������� ����� ����������� ���������� ��� ����
                 make_ekran_control_urov();
              }
              else if(
                      (current_ekran.current_level >= EKRAN_SETPOINT_ZOP_GROUP1) &&
                      (current_ekran.current_level <= EKRAN_SETPOINT_ZOP_GROUP4)
                     )   
              {
                if (current_ekran.position_cursor_x == COL_SETPOINT_ZOP_COMMA )current_ekran.position_cursor_x--;
                if ((current_ekran.position_cursor_x < COL_SETPOINT_ZOP_BEGIN) ||
                    (current_ekran.position_cursor_x > COL_SETPOINT_ZOP_END))
                  current_ekran.position_cursor_x = COL_SETPOINT_ZOP_END;

                //������� ����� ������� ���(���)
                int group = (current_ekran.current_level - EKRAN_SETPOINT_ZOP_GROUP1);
                make_ekran_setpoint_zop(group);
              }
              else if(
                      (current_ekran.current_level >= EKRAN_TIMEOUT_ZOP_GROUP1) &&
                      (current_ekran.current_level <= EKRAN_TIMEOUT_ZOP_GROUP4)
                     )   
              {
                if (current_ekran.position_cursor_x == COL_TMO_ZOP_COMMA )current_ekran.position_cursor_x--;
                if ((current_ekran.position_cursor_x < COL_TMO_ZOP_BEGIN) ||
                    (current_ekran.position_cursor_x > COL_TMO_ZOP_END))
                  current_ekran.position_cursor_x = COL_TMO_ZOP_END;

                //������� ����� �������� ���(���)
                int group = (current_ekran.current_level - EKRAN_TIMEOUT_ZOP_GROUP1);
                make_ekran_timeout_zop(group);
              }
              else if(current_ekran.current_level == EKRAN_CONTROL_ZOP)
              {
                unsigned int maska;
          
                //��������, ���� �� ����� �����
                maska = CTR_ZOP_STATE;
                
                //̳����� �� ����������� ��������� �� ��� ������� �������
                edition_settings.control_zop ^= maska;

                //������� ����� ����������� ���������� ��� ����
                 make_ekran_control_zop();
              }
              else if(
                      (current_ekran.current_level >= EKRAN_SETPOINT_UMIN_GROUP1) &&
                      (current_ekran.current_level <= EKRAN_SETPOINT_UMIN_GROUP4)
                     )   
              {
                if(current_ekran.index_position == INDEX_ML_STPUMIN1)
                {
                  if (current_ekran.position_cursor_x == COL_SETPOINT_UMIN1_COMMA )current_ekran.position_cursor_x--;
                  if ((current_ekran.position_cursor_x < COL_SETPOINT_UMIN1_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_SETPOINT_UMIN1_END))
                    current_ekran.position_cursor_x = COL_SETPOINT_UMIN1_END;
                }
                else if(current_ekran.index_position == INDEX_ML_STPUMIN1_IBLK)
                {
                  if (current_ekran.position_cursor_x == COL_SETPOINT_UMIN1_IBLK_COMMA )current_ekran.position_cursor_x--;
                  if ((current_ekran.position_cursor_x < COL_SETPOINT_UMIN1_IBLK_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_SETPOINT_UMIN1_IBLK_END))
                    current_ekran.position_cursor_x = COL_SETPOINT_UMIN1_IBLK_END;
                }
                else if(current_ekran.index_position == INDEX_ML_STPUMIN2)
                {
                  if (current_ekran.position_cursor_x == COL_SETPOINT_UMIN2_COMMA )current_ekran.position_cursor_x--;
                  if ((current_ekran.position_cursor_x < COL_SETPOINT_UMIN2_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_SETPOINT_UMIN2_END))
                    current_ekran.position_cursor_x = COL_SETPOINT_UMIN2_END;
                }
                else if(current_ekran.index_position == INDEX_ML_STPUMIN2_IBLK)
                {
                  if (current_ekran.position_cursor_x == COL_SETPOINT_UMIN2_IBLK_COMMA )current_ekran.position_cursor_x--;
                  if ((current_ekran.position_cursor_x < COL_SETPOINT_UMIN2_IBLK_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_SETPOINT_UMIN2_IBLK_END))
                    current_ekran.position_cursor_x = COL_SETPOINT_UMIN2_IBLK_END;
                }

                //������� ����� ������� Umin
                int group = (current_ekran.current_level - EKRAN_SETPOINT_UMIN_GROUP1);
                make_ekran_setpoint_Umin(group);
              }
              else if(
                      (current_ekran.current_level >= EKRAN_TIMEOUT_UMIN_GROUP1) &&
                      (current_ekran.current_level <= EKRAN_TIMEOUT_UMIN_GROUP4)
                     )   
              {
                if(current_ekran.index_position == INDEX_ML_TMOUMIN1)
                {
                  if (current_ekran.position_cursor_x == COL_TMO_UMIN1_COMMA )current_ekran.position_cursor_x--;
                  if ((current_ekran.position_cursor_x < COL_TMO_UMIN1_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TMO_UMIN1_END))
                    current_ekran.position_cursor_x = COL_TMO_UMIN1_END;
                }
                else if(current_ekran.index_position == INDEX_ML_TMOUMIN2)
                {
                  if (current_ekran.position_cursor_x == COL_TMO_UMIN2_COMMA )current_ekran.position_cursor_x--;
                  if ((current_ekran.position_cursor_x < COL_TMO_UMIN2_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TMO_UMIN2_END))
                    current_ekran.position_cursor_x = COL_TMO_UMIN2_END;
                }

                //������� ����� �������� Umin
                int group = (current_ekran.current_level - EKRAN_TIMEOUT_UMIN_GROUP1);
                make_ekran_timeout_Umin(group);
              }
              else if(current_ekran.current_level == EKRAN_CONTROL_UMIN)
              {
                unsigned int maska = 0;
          
                //��������, ���� �� ����� �����
                if      (current_ekran.index_position == INDEX_CTR_UMIN1          ) maska = CTR_UMIN1;
                else if (current_ekran.index_position == INDEX_CTR_PO_UMIN1_OR_AND) maska = CTR_PO_UMIN1_OR_AND;
                else if (current_ekran.index_position == INDEX_CTR_UMIN1_UBLK     ) maska = CTR_UMIN1_UBLK;
                else if (current_ekran.index_position == INDEX_CTR_UMIN1_IBLK     ) maska = CTR_UMIN1_IBLK;
                else if (current_ekran.index_position == INDEX_CTR_UMIN2          ) maska = CTR_UMIN2;
                else if (current_ekran.index_position == INDEX_CTR_PO_UMIN2_OR_AND) maska = CTR_PO_UMIN2_OR_AND;
                else if (current_ekran.index_position == INDEX_CTR_UMIN2_UBLK     ) maska = CTR_UMIN2_UBLK;
                else if (current_ekran.index_position == INDEX_CTR_UMIN2_IBLK     ) maska = CTR_UMIN2_IBLK;
                
                //̳����� �� ����������� ��������� �� ��� ������� �������
                edition_settings.control_Umin ^= maska;

                //������� ����� ����������� ���������� ��� Umin
                 make_ekran_control_Umin();
              }
              else if(
                      (current_ekran.current_level >= EKRAN_SETPOINT_UMAX_GROUP1) &&
                      (current_ekran.current_level <= EKRAN_SETPOINT_UMAX_GROUP4)
                     )   
              {
                if(current_ekran.index_position == INDEX_ML_STPUMAX1)
                {
                  if (current_ekran.position_cursor_x == COL_SETPOINT_UMAX1_COMMA )current_ekran.position_cursor_x--;
                  if ((current_ekran.position_cursor_x < COL_SETPOINT_UMAX1_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_SETPOINT_UMAX1_END))
                    current_ekran.position_cursor_x = COL_SETPOINT_UMAX1_END;
                }
                else if(current_ekran.index_position == INDEX_ML_STPUMAX2)
                {
                  if (current_ekran.position_cursor_x == COL_SETPOINT_UMAX2_COMMA )current_ekran.position_cursor_x--;
                  if ((current_ekran.position_cursor_x < COL_SETPOINT_UMAX2_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_SETPOINT_UMAX2_END))
                    current_ekran.position_cursor_x = COL_SETPOINT_UMAX2_END;
                }

                //������� ����� ������� Umax
                int group = (current_ekran.current_level - EKRAN_SETPOINT_UMAX_GROUP1);
                make_ekran_setpoint_Umax(group);
              }
              else if(
                      (current_ekran.current_level >= EKRAN_TIMEOUT_UMAX_GROUP1) &&
                      (current_ekran.current_level <= EKRAN_TIMEOUT_UMAX_GROUP4)
                     )   
              {
                if(current_ekran.index_position == INDEX_ML_TMOUMAX1)
                {
                  if (current_ekran.position_cursor_x == COL_TMO_UMAX1_COMMA )current_ekran.position_cursor_x--;
                  if ((current_ekran.position_cursor_x < COL_TMO_UMAX1_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TMO_UMAX1_END))
                    current_ekran.position_cursor_x = COL_TMO_UMAX1_END;
                }
                else if(current_ekran.index_position == INDEX_ML_TMOUMAX2)
                {
                  if (current_ekran.position_cursor_x == COL_TMO_UMAX2_COMMA )current_ekran.position_cursor_x--;
                  if ((current_ekran.position_cursor_x < COL_TMO_UMAX2_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TMO_UMAX2_END))
                    current_ekran.position_cursor_x = COL_TMO_UMAX2_END;
                }

                //������� ����� �������� Umax
                int group = (current_ekran.current_level - EKRAN_TIMEOUT_UMAX_GROUP1);
                make_ekran_timeout_Umax(group);
              }
              else if(current_ekran.current_level == EKRAN_CONTROL_UMAX)
              {
                unsigned int maska = 0;
          
                //��������, ���� �� ����� �����
                if      (current_ekran.index_position == INDEX_CTR_UMAX1          ) maska = CTR_UMAX1;
                else if (current_ekran.index_position == INDEX_CTR_PO_UMAX1_OR_AND) maska = CTR_PO_UMAX1_OR_AND;
                else if (current_ekran.index_position == INDEX_CTR_UMAX2          ) maska = CTR_UMAX2;
                else if (current_ekran.index_position == INDEX_CTR_PO_UMAX2_OR_AND) maska = CTR_PO_UMAX2_OR_AND;
                
                //̳����� �� ����������� ��������� �� ��� ������� �������
                edition_settings.control_Umax ^= maska;

                //������� ����� ����������� ���������� ��� Umax
                 make_ekran_control_Umax();
              }
              else if(
                      (current_ekran.current_level >= EKRAN_SETPOINT_AVR_UMIN_GROUP1) &&
                      (current_ekran.current_level <= EKRAN_SETPOINT_AVR_UMIN_GROUP4)
                     )   
              {
                if(current_ekran.index_position == INDEX_ML_STPAVR_TN1_U1_UMIN)
                {
                  if (current_ekran.position_cursor_x == COL_SETPOINT_AVR_TN1_U1_UMIN_COMMA )current_ekran.position_cursor_x--;
                  if ((current_ekran.position_cursor_x < COL_SETPOINT_AVR_TN1_U1_UMIN_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_SETPOINT_AVR_TN1_U1_UMIN_END))
                    current_ekran.position_cursor_x = COL_SETPOINT_AVR_TN1_U1_UMIN_END;
                }
                else if(current_ekran.index_position == INDEX_ML_STPAVR_TN1_U2_LOW_WORK)
                {
                  if (current_ekran.position_cursor_x == COL_SETPOINT_AVR_TN1_U2_LOW_WORK_COMMA )current_ekran.position_cursor_x--;
                  if ((current_ekran.position_cursor_x < COL_SETPOINT_AVR_TN1_U2_LOW_WORK_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_SETPOINT_AVR_TN1_U2_LOW_WORK_END))
                    current_ekran.position_cursor_x = COL_SETPOINT_AVR_TN1_U2_LOW_WORK_END;
                }
                else if(current_ekran.index_position == INDEX_ML_STPAVR_TN2_U2_UMIN)
                {
                  if (current_ekran.position_cursor_x == COL_SETPOINT_AVR_TN2_U2_UMIN_COMMA )current_ekran.position_cursor_x--;
                  if ((current_ekran.position_cursor_x < COL_SETPOINT_AVR_TN2_U2_UMIN_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_SETPOINT_AVR_TN2_U2_UMIN_END))
                    current_ekran.position_cursor_x = COL_SETPOINT_AVR_TN2_U2_UMIN_END;
                }
                else if(current_ekran.index_position == INDEX_ML_STPAVR_TN2_U1_LOW_WORK)
                {
                  if (current_ekran.position_cursor_x == COL_SETPOINT_AVR_TN2_U1_LOW_WORK_COMMA )current_ekran.position_cursor_x--;
                  if ((current_ekran.position_cursor_x < COL_SETPOINT_AVR_TN2_U1_LOW_WORK_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_SETPOINT_AVR_TN2_U1_LOW_WORK_END))
                    current_ekran.position_cursor_x = COL_SETPOINT_AVR_TN2_U1_LOW_WORK_END;
                }
                //������� ����� ������� ��� Umin
                int group = (current_ekran.current_level - EKRAN_SETPOINT_AVR_UMIN_GROUP1);
                make_ekran_setpoint_avr_Umin(group);
              }
              else if(
                      (current_ekran.current_level >= EKRAN_SETPOINT_AVR_UMAX_GROUP1) &&
                      (current_ekran.current_level <= EKRAN_SETPOINT_AVR_UMAX_GROUP4)
                     )   
              {
                if(current_ekran.index_position == INDEX_ML_STPAVR_TN1_U1_UMAX)
                {
                  if (current_ekran.position_cursor_x == COL_SETPOINT_AVR_TN1_U1_UMAX_COMMA )current_ekran.position_cursor_x--;
                  if ((current_ekran.position_cursor_x < COL_SETPOINT_AVR_TN1_U1_UMAX_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_SETPOINT_AVR_TN1_U1_UMAX_END))
                    current_ekran.position_cursor_x = COL_SETPOINT_AVR_TN1_U1_UMAX_END;
                }
                else if(current_ekran.index_position == INDEX_ML_STPAVR_TN1_U2_HIGH_WORK)
                {
                  if (current_ekran.position_cursor_x == COL_SETPOINT_AVR_TN1_U2_HIGH_WORK_COMMA )current_ekran.position_cursor_x--;
                  if ((current_ekran.position_cursor_x < COL_SETPOINT_AVR_TN1_U2_HIGH_WORK_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_SETPOINT_AVR_TN1_U2_HIGH_WORK_END))
                    current_ekran.position_cursor_x = COL_SETPOINT_AVR_TN1_U2_HIGH_WORK_END;
                }
                else if(current_ekran.index_position == INDEX_ML_STPAVR_TN2_U2_UMAX)
                {
                  if (current_ekran.position_cursor_x == COL_SETPOINT_AVR_TN2_U2_UMAX_COMMA )current_ekran.position_cursor_x--;
                  if ((current_ekran.position_cursor_x < COL_SETPOINT_AVR_TN2_U2_UMAX_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_SETPOINT_AVR_TN2_U2_UMAX_END))
                    current_ekran.position_cursor_x = COL_SETPOINT_AVR_TN2_U2_UMAX_END;
                }
                else if(current_ekran.index_position == INDEX_ML_STPAVR_TN2_U1_HIGH_WORK)
                {
                  if (current_ekran.position_cursor_x == COL_SETPOINT_AVR_TN2_U1_HIGH_WORK_COMMA )current_ekran.position_cursor_x--;
                  if ((current_ekran.position_cursor_x < COL_SETPOINT_AVR_TN2_U1_HIGH_WORK_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_SETPOINT_AVR_TN2_U1_HIGH_WORK_END))
                    current_ekran.position_cursor_x = COL_SETPOINT_AVR_TN2_U1_HIGH_WORK_END;
                }

                //������� ����� ������� ��� Umax
                int group = (current_ekran.current_level - EKRAN_SETPOINT_AVR_UMAX_GROUP1);
                make_ekran_setpoint_avr_Umax(group);
              }
              else if(
                      (current_ekran.current_level >= EKRAN_TIMEOUT_AVR_GENERAL_GROUP1) &&
                      (current_ekran.current_level <= EKRAN_TIMEOUT_AVR_GENERAL_GROUP4)
                     )   
              {
                if(current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_BLK_K1)
                {
                  if (current_ekran.position_cursor_x == COL_TMO_AVR_GENERAL_BLK_K1_COMMA )current_ekran.position_cursor_x--;
                  if ((current_ekran.position_cursor_x < COL_TMO_AVR_GENERAL_BLK_K1_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TMO_AVR_GENERAL_BLK_K1_END))
                    current_ekran.position_cursor_x = COL_TMO_AVR_GENERAL_BLK_K1_END;
                }
                else if(current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_PUSK_K1)
                {
                  if (current_ekran.position_cursor_x == COL_TMO_AVR_GENERAL_PUSK_K1_COMMA )current_ekran.position_cursor_x--;
                  if ((current_ekran.position_cursor_x < COL_TMO_AVR_GENERAL_PUSK_K1_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TMO_AVR_GENERAL_PUSK_K1_END))
                    current_ekran.position_cursor_x = COL_TMO_AVR_GENERAL_PUSK_K1_END;
                }
                else if(current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_D_DIJI_K1)
                {
                  if (current_ekran.position_cursor_x == COL_TMO_AVR_GENERAL_D_DIJI_K1_COMMA )current_ekran.position_cursor_x--;
                  if ((current_ekran.position_cursor_x < COL_TMO_AVR_GENERAL_D_DIJI_K1_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TMO_AVR_GENERAL_D_DIJI_K1_END))
                    current_ekran.position_cursor_x = COL_TMO_AVR_GENERAL_D_DIJI_K1_END;
                }
                else if(current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_VVIMK_REZ_K1)
                {
                  if (current_ekran.position_cursor_x == COL_TMO_AVR_GENERAL_VVIMK_REZ_K1_COMMA )current_ekran.position_cursor_x--;
                  if ((current_ekran.position_cursor_x < COL_TMO_AVR_GENERAL_VVIMK_REZ_K1_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TMO_AVR_GENERAL_VVIMK_REZ_K1_END))
                    current_ekran.position_cursor_x = COL_TMO_AVR_GENERAL_VVIMK_REZ_K1_END;
                }
                else if(current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_VVIMK_K1)
                {
                  if (current_ekran.position_cursor_x == COL_TMO_AVR_GENERAL_VVIMK_K1_COMMA )current_ekran.position_cursor_x--;
                  if ((current_ekran.position_cursor_x < COL_TMO_AVR_GENERAL_VVIMK_K1_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TMO_AVR_GENERAL_VVIMK_K1_END))
                    current_ekran.position_cursor_x = COL_TMO_AVR_GENERAL_VVIMK_K1_END;
                }
                else if(current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_VYMK_K1)
                {
                  if (current_ekran.position_cursor_x == COL_TMO_AVR_GENERAL_VYMK_K1_COMMA )current_ekran.position_cursor_x--;
                  if ((current_ekran.position_cursor_x < COL_TMO_AVR_GENERAL_VYMK_K1_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TMO_AVR_GENERAL_VYMK_K1_END))
                    current_ekran.position_cursor_x = COL_TMO_AVR_GENERAL_VYMK_K1_END;
                }
                else if(current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_BLK_K2)
                {
                  if (current_ekran.position_cursor_x == COL_TMO_AVR_GENERAL_BLK_K2_COMMA )current_ekran.position_cursor_x--;
                  if ((current_ekran.position_cursor_x < COL_TMO_AVR_GENERAL_BLK_K2_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TMO_AVR_GENERAL_BLK_K2_END))
                    current_ekran.position_cursor_x = COL_TMO_AVR_GENERAL_BLK_K2_END;
                }
                else if(current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_PUSK_K2)
                {
                  if (current_ekran.position_cursor_x == COL_TMO_AVR_GENERAL_PUSK_K2_COMMA )current_ekran.position_cursor_x--;
                  if ((current_ekran.position_cursor_x < COL_TMO_AVR_GENERAL_PUSK_K2_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TMO_AVR_GENERAL_PUSK_K2_END))
                    current_ekran.position_cursor_x = COL_TMO_AVR_GENERAL_PUSK_K2_END;
                }
                else if(current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_D_DIJI_K2)
                {
                  if (current_ekran.position_cursor_x == COL_TMO_AVR_GENERAL_D_DIJI_K2_COMMA )current_ekran.position_cursor_x--;
                  if ((current_ekran.position_cursor_x < COL_TMO_AVR_GENERAL_D_DIJI_K2_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TMO_AVR_GENERAL_D_DIJI_K2_END))
                    current_ekran.position_cursor_x = COL_TMO_AVR_GENERAL_D_DIJI_K2_END;
                }
                else if(current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_VVIMK_REZ_K2)
                {
                  if (current_ekran.position_cursor_x == COL_TMO_AVR_GENERAL_VVIMK_REZ_K2_COMMA )current_ekran.position_cursor_x--;
                  if ((current_ekran.position_cursor_x < COL_TMO_AVR_GENERAL_VVIMK_REZ_K2_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TMO_AVR_GENERAL_VVIMK_REZ_K2_END))
                    current_ekran.position_cursor_x = COL_TMO_AVR_GENERAL_VVIMK_REZ_K2_END;
                }
                else if(current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_VVIMK_K2)
                {
                  if (current_ekran.position_cursor_x == COL_TMO_AVR_GENERAL_VVIMK_K2_COMMA )current_ekran.position_cursor_x--;
                  if ((current_ekran.position_cursor_x < COL_TMO_AVR_GENERAL_VVIMK_K2_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TMO_AVR_GENERAL_VVIMK_K2_END))
                    current_ekran.position_cursor_x = COL_TMO_AVR_GENERAL_VVIMK_K2_END;
                }
                else if(current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_VYMK_K2)
                {
                  if (current_ekran.position_cursor_x == COL_TMO_AVR_GENERAL_VYMK_K2_COMMA )current_ekran.position_cursor_x--;
                  if ((current_ekran.position_cursor_x < COL_TMO_AVR_GENERAL_VYMK_K2_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TMO_AVR_GENERAL_VYMK_K2_END))
                    current_ekran.position_cursor_x = COL_TMO_AVR_GENERAL_VYMK_K2_END;
                }

                //������� ����� �������� ��� (��������)
                int group = (current_ekran.current_level - EKRAN_TIMEOUT_AVR_GENERAL_GROUP1);
                make_ekran_timeout_avr_general(group);
              }
              else if(
                      (current_ekran.current_level >= EKRAN_TIMEOUT_AVR_UMIN_GROUP1) &&
                      (current_ekran.current_level <= EKRAN_TIMEOUT_AVR_UMIN_GROUP4)
                     )   
              {
                if(current_ekran.index_position == INDEX_ML_TMOAVR_UMIN_VYMK_ROB_K1)
                {
                  if (current_ekran.position_cursor_x == COL_TMO_AVR_UMIN_VYMK_ROB_K1_COMMA )current_ekran.position_cursor_x--;
                  if ((current_ekran.position_cursor_x < COL_TMO_AVR_UMIN_VYMK_ROB_K1_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TMO_AVR_UMIN_VYMK_ROB_K1_END))
                    current_ekran.position_cursor_x = COL_TMO_AVR_UMIN_VYMK_ROB_K1_END;
                }
                else if(current_ekran.index_position == INDEX_ML_TMOAVR_UMIN_VYMK_ROB_K2)
                {
                  if (current_ekran.position_cursor_x == COL_TMO_AVR_UMIN_VYMK_ROB_K2_COMMA )current_ekran.position_cursor_x--;
                  if ((current_ekran.position_cursor_x < COL_TMO_AVR_UMIN_VYMK_ROB_K2_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TMO_AVR_UMIN_VYMK_ROB_K2_END))
                    current_ekran.position_cursor_x = COL_TMO_AVR_UMIN_VYMK_ROB_K2_END;
                }

                //������� ����� �������� ��� Umin
                int group = (current_ekran.current_level - EKRAN_TIMEOUT_AVR_UMIN_GROUP1);
                make_ekran_timeout_avr_Umin(group);
              }
              else if(
                      (current_ekran.current_level >= EKRAN_TIMEOUT_AVR_UMAX_GROUP1) &&
                      (current_ekran.current_level <= EKRAN_TIMEOUT_AVR_UMAX_GROUP4)
                     )   
              {
                if(current_ekran.index_position == INDEX_ML_TMOAVR_UMAX_VYMK_ROB_K1)
                {
                  if (current_ekran.position_cursor_x == COL_TMO_AVR_UMAX_VYMK_ROB_K1_COMMA )current_ekran.position_cursor_x--;
                  if ((current_ekran.position_cursor_x < COL_TMO_AVR_UMAX_VYMK_ROB_K1_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TMO_AVR_UMAX_VYMK_ROB_K1_END))
                    current_ekran.position_cursor_x = COL_TMO_AVR_UMAX_VYMK_ROB_K1_END;
                }
                else if(current_ekran.index_position == INDEX_ML_TMOAVR_UMAX_VYMK_ROB_K2)
                {
                  if (current_ekran.position_cursor_x == COL_TMO_AVR_UMAX_VYMK_ROB_K2_COMMA )current_ekran.position_cursor_x--;
                  if ((current_ekran.position_cursor_x < COL_TMO_AVR_UMAX_VYMK_ROB_K2_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TMO_AVR_UMAX_VYMK_ROB_K2_END))
                    current_ekran.position_cursor_x = COL_TMO_AVR_UMAX_VYMK_ROB_K2_END;
                }

                //������� ����� �������� ��� Umax
                int group = (current_ekran.current_level - EKRAN_TIMEOUT_AVR_UMAX_GROUP1);
                make_ekran_timeout_avr_Umax(group);
              }
              else if(current_ekran.current_level == EKRAN_CONTROL_AVR)
              {
                unsigned int maska = 0;
          
                //��������, ���� �� ����� �����
                if      (current_ekran.index_position == INDEX_CTR_AVR     ) maska = CTR_AVR;
                else if (current_ekran.index_position == INDEX_CTR_AVR_UMAX) maska = CTR_AVR_UMAX;
                else if (current_ekran.index_position == INDEX_CTR_AVR_BLK ) maska = CTR_AVR_BLK;
                
                //̳����� �� ����������� ��������� �� ��� ������� �������
                edition_settings.control_avr ^= maska;

                //������� ����� ����������� ���������� ��� ���
                 make_ekran_control_avr();
              }
              else if(
                      (current_ekran.current_level >= EKRAN_SETPOINT_CTRL_PHASE_GROUP1) &&
                      (current_ekran.current_level <= EKRAN_SETPOINT_CTRL_PHASE_GROUP4)
                     )   
              {
                if(current_ekran.index_position == INDEX_ML_STPCTRL_PHASE_U)
                {
                  if (current_ekran.position_cursor_x == COL_SETPOINT_CTRL_PHASE_U_COMMA )current_ekran.position_cursor_x--;
                  if ((current_ekran.position_cursor_x < COL_SETPOINT_CTRL_PHASE_U_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_SETPOINT_CTRL_PHASE_U_END))
                    current_ekran.position_cursor_x = COL_SETPOINT_CTRL_PHASE_U_END;
                }
                else if(current_ekran.index_position == INDEX_ML_STPCTRL_PHASE_PHI)
                {
                  if (current_ekran.position_cursor_x == COL_SETPOINT_CTRL_PHASE_PHI_COMMA )current_ekran.position_cursor_x--;
                  if ((current_ekran.position_cursor_x < COL_SETPOINT_CTRL_PHASE_PHI_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_SETPOINT_CTRL_PHASE_PHI_END))
                    current_ekran.position_cursor_x = COL_SETPOINT_CTRL_PHASE_PHI_END;
                }
                else if(current_ekran.index_position == INDEX_ML_STPCTRL_PHASE_F)
                {
                  if (current_ekran.position_cursor_x == COL_SETPOINT_CTRL_PHASE_F_COMMA )current_ekran.position_cursor_x--;
                  if ((current_ekran.position_cursor_x < COL_SETPOINT_CTRL_PHASE_F_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_SETPOINT_CTRL_PHASE_F_END))
                    current_ekran.position_cursor_x = COL_SETPOINT_CTRL_PHASE_F_END;
                }

                //������� ����� ������� "�������� ���������"
                int group = (current_ekran.current_level - EKRAN_SETPOINT_CTRL_PHASE_GROUP1);
                make_ekran_setpoint_ctrl_phase(group);
              }
              else if(
                      (current_ekran.current_level >= EKRAN_TIMEOUT_CTRL_PHASE_GROUP1) &&
                      (current_ekran.current_level <= EKRAN_TIMEOUT_CTRL_PHASE_GROUP4)
                     )   
              {
                if(current_ekran.index_position == INDEX_ML_TMOCTRL_PHASE_U)
                {
                  if (current_ekran.position_cursor_x == COL_TMO_CTRL_PHASE_U_COMMA )current_ekran.position_cursor_x--;
                  if ((current_ekran.position_cursor_x < COL_TMO_CTRL_PHASE_U_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TMO_CTRL_PHASE_U_END))
                    current_ekran.position_cursor_x = COL_TMO_CTRL_PHASE_U_END;
                }
                else if(current_ekran.index_position == INDEX_ML_TMOCTRL_PHASE_U_D)
                {
                  if (current_ekran.position_cursor_x == COL_TMO_CTRL_PHASE_U_D_COMMA )current_ekran.position_cursor_x--;
                  if ((current_ekran.position_cursor_x < COL_TMO_CTRL_PHASE_U_D_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TMO_CTRL_PHASE_U_D_END))
                    current_ekran.position_cursor_x = COL_TMO_CTRL_PHASE_U_D_END;
                }
                else if(current_ekran.index_position == INDEX_ML_TMOCTRL_PHASE_PHI)
                {
                  if (current_ekran.position_cursor_x == COL_TMO_CTRL_PHASE_PHI_COMMA )current_ekran.position_cursor_x--;
                  if ((current_ekran.position_cursor_x < COL_TMO_CTRL_PHASE_PHI_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TMO_CTRL_PHASE_PHI_END))
                    current_ekran.position_cursor_x = COL_TMO_CTRL_PHASE_PHI_END;
                }
                else if(current_ekran.index_position == INDEX_ML_TMOCTRL_PHASE_PHI_D)
                {
                  if (current_ekran.position_cursor_x == COL_TMO_CTRL_PHASE_PHI_D_COMMA )current_ekran.position_cursor_x--;
                  if ((current_ekran.position_cursor_x < COL_TMO_CTRL_PHASE_PHI_D_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TMO_CTRL_PHASE_PHI_D_END))
                    current_ekran.position_cursor_x = COL_TMO_CTRL_PHASE_PHI_D_END;
                }
                else if(current_ekran.index_position == INDEX_ML_TMOCTRL_PHASE_F)
                {
                  if (current_ekran.position_cursor_x == COL_TMO_CTRL_PHASE_F_COMMA )current_ekran.position_cursor_x--;
                  if ((current_ekran.position_cursor_x < COL_TMO_CTRL_PHASE_F_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TMO_CTRL_PHASE_F_END))
                    current_ekran.position_cursor_x = COL_TMO_CTRL_PHASE_F_END;
                }
                else if(current_ekran.index_position == INDEX_ML_TMOCTRL_PHASE_F_D)
                {
                  if (current_ekran.position_cursor_x == COL_TMO_CTRL_PHASE_F_D_COMMA )current_ekran.position_cursor_x--;
                  if ((current_ekran.position_cursor_x < COL_TMO_CTRL_PHASE_F_D_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TMO_CTRL_PHASE_F_D_END))
                    current_ekran.position_cursor_x = COL_TMO_CTRL_PHASE_F_D_END;
                }

                //������� ����� �������� "�������� ���������"
                int group = (current_ekran.current_level - EKRAN_TIMEOUT_CTRL_PHASE_GROUP1);
                make_ekran_timeout_ctrl_phase(group);
              }
              else if(current_ekran.current_level == EKRAN_CONTROL_CTRL_PHASE)
              {
                unsigned int maska = 0;
          
                //��������, ���� �� ����� �����
                if      (current_ekran.index_position == INDEX_CTR_CTRL_PHASE_U      ) maska = CTR_CTRL_PHASE_U;
                else if (current_ekran.index_position == INDEX_CTR_CTRL_PHASE_PHI    ) maska = CTR_CTRL_PHASE_PHI;
                else if (current_ekran.index_position == INDEX_CTR_CTRL_PHASE_F      ) maska = CTR_CTRL_PHASE_F;
                else if (current_ekran.index_position == INDEX_CTR_CTRL_PHASE_SEQ_TN1) maska = CTR_CTRL_PHASE_SEQ_TN1;
                else if (current_ekran.index_position == INDEX_CTR_CTRL_PHASE_SEQ_TN2) maska = CTR_CTRL_PHASE_SEQ_TN2;
                
                //̳����� �� ����������� ��������� �� ��� ������� �������
                edition_settings.control_ctrl_phase ^= maska;

                //������� ����� ����������� ���������� ��� "�������� ���������"
                 make_ekran_control_ctrl_phase();
              }
              else if(current_ekran.current_level == EKRAN_TRANSFORMATOR_INFO_SETPOINT)
              {
                if(current_ekran.index_position == INDEX_ML_TT)
                {
                  if ((current_ekran.position_cursor_x < COL_TT_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TT_END))
                    current_ekran.position_cursor_x = COL_TT_END;
                }
                else
                {
                  if ((current_ekran.position_cursor_x < COL_TN_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TN_END))
                    current_ekran.position_cursor_x = COL_TN_END;
                }
                //������� ����� ����������� ���������� �� ���������������
                make_ekran_transformator();
              }
              else if(current_ekran.current_level == EKRAN_TRANSFORMATOR_INFO_CONTROL)
              {
                //��������, ���� �� ����� �����
                unsigned int maska = (1 << current_ekran.index_position);
                
                //̳����� �� ����������� ��������� �� ��� ������� �������
                edition_settings.control_transformator ^= maska;

                //������� ����� ����������� ����������� ���� "�������������"
                make_ekran_transformator_control();
              }
              else if(current_ekran.current_level == EKRAN_SETPOINT_SWITCH)
              {
                if(current_ekran.index_position == INDEX_ML_STPInom)
                {
                  if ((current_ekran.position_cursor_x < COL_SETPOINT_Inom_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_SETPOINT_Inom_END))
                    current_ekran.position_cursor_x = COL_SETPOINT_Inom_END;
                }
                else if (current_ekran.index_position == INDEX_ML_STPRKS_Inom)
                {
                  if ((current_ekran.position_cursor_x < COL_SETPOINT_RKS_Inom_BEGIN) ||
                      (current_ekran.position_cursor_x > (COL_SETPOINT_RKS_Inom_END - 1)))
                    current_ekran.position_cursor_x = COL_SETPOINT_RKS_Inom_END - 1;
                }
                else if (current_ekran.index_position == INDEX_ML_STPMInom_vymk)
                {
                  if (current_ekran.position_cursor_x == COL_SETPOINT_Inom_vymk_COMMA )current_ekran.position_cursor_x--;
                  if ((current_ekran.position_cursor_x < COL_SETPOINT_Inom_vymk_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_SETPOINT_Inom_vymk_END))
                    current_ekran.position_cursor_x = COL_SETPOINT_Inom_vymk_END;
                }
                else if (current_ekran.index_position == INDEX_ML_STPRKS_Inom_vymk)
                {
                  if ((current_ekran.position_cursor_x < COL_SETPOINT_RKS_Inom_vymk_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_SETPOINT_RKS_Inom_vymk_END))
                    current_ekran.position_cursor_x = COL_SETPOINT_RKS_Inom_vymk_END;
                }
                else if (current_ekran.index_position == INDEX_ML_STPPOCHATKOVYJ_RESURS)
                {
                  if ((current_ekran.position_cursor_x < COL_SETPOINT_POCHATKOVYJ_RESURS_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_SETPOINT_POCHATKOVYJ_RESURS_END))
                    current_ekran.position_cursor_x = COL_SETPOINT_POCHATKOVYJ_RESURS_END;
                }
                else if (current_ekran.index_position == INDEX_ML_STPKRYTYCHNYJ_RESURS)
                {
                  if ((current_ekran.position_cursor_x < COL_SETPOINT_KRYTYCHNYJ_RESURS_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_SETPOINT_KRYTYCHNYJ_RESURS_END))
                    current_ekran.position_cursor_x = COL_SETPOINT_KRYTYCHNYJ_RESURS_END;
                }
                else if (current_ekran.index_position == INDEX_ML_STPPOCHATKOVA_K_VYMK)
                {
                  if ((current_ekran.position_cursor_x < COL_SETPOINT_POCHATKOVA_K_VYMK_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_SETPOINT_POCHATKOVA_K_VYMK_END))
                    current_ekran.position_cursor_x = COL_SETPOINT_POCHATKOVA_K_VYMK_END;
                }
                //������� ����� ������� �����������
                make_ekran_setpoint_switch();
              }
              else if(current_ekran.current_level == EKRAN_TIMEOUT_SWITCH)
              {
                if(current_ekran.index_position == INDEX_ML_TMOON)
                {
                  if (current_ekran.position_cursor_x == COL_TMO_SWCH_ON_COMMA )current_ekran.position_cursor_x--;
                  if ((current_ekran.position_cursor_x < COL_TMO_SWCH_ON_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TMO_SWCH_ON_END))
                    current_ekran.position_cursor_x = COL_TMO_SWCH_ON_END;
                }
                else if(current_ekran.index_position == INDEX_ML_TMOOFF)
                {
                  if (current_ekran.position_cursor_x == COL_TMO_SWCH_OFF_COMMA )current_ekran.position_cursor_x--;
                  if ((current_ekran.position_cursor_x < COL_TMO_SWCH_OFF_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TMO_SWCH_OFF_END))
                    current_ekran.position_cursor_x = COL_TMO_SWCH_OFF_END;
                }
                else if(current_ekran.index_position == INDEX_ML_TMOUDL_BLK_ON)
                {
                  if (current_ekran.position_cursor_x == COL_TMO_SWCH_UDL_BLK_ON_COMMA )current_ekran.position_cursor_x--;
                  if ((current_ekran.position_cursor_x < COL_TMO_SWCH_UDL_BLK_ON_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TMO_SWCH_UDL_BLK_ON_END))
                    current_ekran.position_cursor_x = COL_TMO_SWCH_UDL_BLK_ON_END;
                }
                else if(current_ekran.index_position == INDEX_ML_TMOPRYVODA_VV)
                {
                  if (current_ekran.position_cursor_x == COL_TMO_PRYVODA_VV_COMMA )current_ekran.position_cursor_x--;
                  if ((current_ekran.position_cursor_x < COL_TMO_PRYVODA_VV_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TMO_PRYVODA_VV_END))
                    current_ekran.position_cursor_x = COL_TMO_PRYVODA_VV_END;
                }
                //������� ����� �������� �����������
                make_ekran_timeout_switch();
              }
              else if(current_ekran.current_level == EKRAN_CONTROL_SWITCH)
              {
                unsigned int maska = 0;
          
                //��������, ���� �� ����� �����
                if      (current_ekran.index_position == INDEX_ML_CTRPRYVOD_VV) maska = CTR_PRYVOD_VV;
                else if (current_ekran.index_position == INDEX_ML_CTRRESURS_VV) maska = CTR_RESURS_VV;
                
                //̳����� �� ����������� ��������� �� ��� ������� �������
                edition_settings.control_switch ^= maska;

                //������� ����� ����������� ���������� ��� ��������
                 make_ekran_control_switch();
              }
              else if(current_ekran.current_level == EKRAN_DOPUSK_DV_UVV)
              {
                if (
                    (current_ekran.position_cursor_x < COL_DOPUSK_DV_BEGIN )
                    ||
                    (current_ekran.position_cursor_x > COL_DOPUSK_DV_END   )
                    ||  
                    (
                     (current_ekran.position_cursor_x == COL_DOPUSK_DV_END) &&
                     ((current_settings.type_of_input_signal & (1 << current_ekran.index_position)) != 0)
                    )
                   )
                {
                  if ((current_settings.type_of_input_signal & (1 << current_ekran.index_position)) != 0)
                    current_ekran.position_cursor_x = (COL_DOPUSK_DV_END - 1);
                  else 
                    current_ekran.position_cursor_x = COL_DOPUSK_DV_END;
                }
                
                //������� ����� ���������� �� �������� ��
                make_ekran_dopusk_dv();
              }
              else if((current_ekran.current_level == EKRAN_TYPE_INPUT_UVV ) || (current_ekran.current_level == EKRAN_TYPE_INPUT_SIGNAL_UVV) ||
                      (current_ekran.current_level == EKRAN_TYPE_LED_UVV   ))
              {
                unsigned int value = (1 << current_ekran.index_position);
          
                //̳����� �� ����������� ��������� �� ��� ������� ������� � ������� ����� ����������� ���������� ��� ���
                if (current_ekran.current_level == EKRAN_TYPE_INPUT_UVV)
                {
                  edition_settings.type_of_input ^= value;
                  make_ekran_type_input_uvv(0);
                }
                else if (current_ekran.current_level == EKRAN_TYPE_INPUT_SIGNAL_UVV)
                {
                  edition_settings.type_of_input_signal ^= value;
                  make_ekran_type_input_uvv(1);
                }
                else
                {
                  edition_settings.type_of_led ^= value;
                  make_ekran_type_led_uvv();
                }
              }
              else if(current_ekran.current_level == EKRAN_TYPE_OUTPUT_UVV)
              {
                unsigned int maska = (1 << current_ekran.index_position);
                
                int value = ((edition_settings.type_of_output & maska) != 0);
                if (value == true) value += ((edition_settings.type_of_output_modif & maska) != 0); //����� � �������, ���� ����� ����������
                if ((--value) < 0) value = 2;
                
                if (value == 0)
                {
                  edition_settings.type_of_output       &= (unsigned int)(~maska);
                  edition_settings.type_of_output_modif &= (unsigned int)(~maska);
                }
                else
                {
                  edition_settings.type_of_output |= maska;
                  if (value == 1) edition_settings.type_of_output_modif &= (unsigned int)(~maska);
                  else edition_settings.type_of_output_modif |= maska;
                }

                make_ekran_type_output_uvv();
              }
              else if(current_ekran.current_level == EKRAN_ADDRESS)
              {
                  if ((current_ekran.position_cursor_x < COL_ADDRESS_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_ADDRESS_END))
                    current_ekran.position_cursor_x = COL_ADDRESS_END;
                  //������� ����� ���������� �� �������������� �����
                  make_ekran_address();
              }
              else if(current_ekran.current_level == EKRAN_VIEW_TIMEOUT_RS485)
              {
                if (current_ekran.position_cursor_x == COL_TIMEOUT_INTERFACE_COMMA )current_ekran.position_cursor_x--;
                if ((current_ekran.position_cursor_x < COL_TIMEOUT_INTERFACE_BEGIN) ||
                    (current_ekran.position_cursor_x > COL_TIMEOUT_INTERFACE_END))
                  current_ekran.position_cursor_x = COL_TIMEOUT_INTERFACE_END;
                //������� ����� ���������� �� time-out ���������� �������
                make_ekran_timeout_interface();
              }
              else if(current_ekran.current_level == EKRAN_GENERAL_PICKUPS_EL)
              {
                if(current_ekran.index_position == INDEX_ML_NUMBER_INERATION)
                {
                  if ((current_ekran.position_cursor_x < COL_NUMBER_INERATION_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_NUMBER_INERATION_END))
                    current_ekran.position_cursor_x = COL_NUMBER_INERATION_END;
                }
//                else if(current_ekran.index_position == INDEX_ML_NUMBER_DEFINED_FUNCTIONS)
//                {
//                  if ((current_ekran.position_cursor_x < COL_NUMBER_DEFINED_FUNCTIONS_BEGIN) ||
//                      (current_ekran.position_cursor_x > COL_NUMBER_DEFINED_FUNCTIONS_END))
//                    current_ekran.position_cursor_x = COL_NUMBER_DEFINED_FUNCTIONS_END;
//                }
//                else if(current_ekran.index_position == INDEX_ML_NUMBER_DEFINED_TRIGGERS)
//                {
//                  if ((current_ekran.position_cursor_x < COL_NUMBER_DEFINED_TRIGGERS_BEGIN) ||
//                      (current_ekran.position_cursor_x > COL_NUMBER_DEFINED_TRIGGERS_END))
//                    current_ekran.position_cursor_x = COL_NUMBER_DEFINED_TRIGGERS_END;
//                }
//                else if(current_ekran.index_position == INDEX_ML_NUMBER_DEFINED_AND)
//                {
//                  if ((current_ekran.position_cursor_x < COL_NUMBER_DEFINED_AND_BEGIN) ||
//                      (current_ekran.position_cursor_x > COL_NUMBER_DEFINED_AND_END))
//                    current_ekran.position_cursor_x = COL_NUMBER_DEFINED_AND_END;
//                }
//                else if(current_ekran.index_position == INDEX_ML_NUMBER_DEFINED_OR)
//                {
//                  if ((current_ekran.position_cursor_x < COL_NUMBER_DEFINED_OR_BEGIN) ||
//                      (current_ekran.position_cursor_x > COL_NUMBER_DEFINED_OR_END))
//                    current_ekran.position_cursor_x = COL_NUMBER_DEFINED_OR_END;
//                }
//                else if(current_ekran.index_position == INDEX_ML_NUMBER_DEFINED_XOR)
//                {
//                  if ((current_ekran.position_cursor_x < COL_NUMBER_DEFINED_XOR_BEGIN) ||
//                      (current_ekran.position_cursor_x > COL_NUMBER_DEFINED_XOR_END))
//                    current_ekran.position_cursor_x = COL_NUMBER_DEFINED_XOR_END;
//                }
//                else if(current_ekran.index_position == INDEX_ML_NUMBER_DEFINED_NOT)
//                {
//                  if ((current_ekran.position_cursor_x < COL_NUMBER_DEFINED_NOT_BEGIN) ||
//                      (current_ekran.position_cursor_x > COL_NUMBER_DEFINED_NOT_END))
//                    current_ekran.position_cursor_x = COL_NUMBER_DEFINED_NOT_END;
//                }
                
                //������� ����� ����������� ��������� �������� ��� ��������� �����
                make_ekran_general_pickups_el();
              }
              else if(current_ekran.current_level == EKRAN_LIST_TYPE_DF)
              {
                unsigned int value = (1 << current_ekran.index_position);
          
                //̳����� �� ����������� ��������� �� ��� ������� �������
                edition_settings.type_df ^= value;

                //������� ����� ����������� ���� ������������� �������
                make_ekran_type_df();
              }
              else if((current_ekran.current_level >= EKRAN_TIMEOUT_DF1) && (current_ekran.current_level <= EKRAN_TIMEOUT_DF8))
              {
                if(current_ekran.index_position == INDEX_ML_TMO_DF_PAUSE)
                {
                  if (current_ekran.position_cursor_x == COL_TMO_DF_PAUSE_COMMA )current_ekran.position_cursor_x--;
                  if ((current_ekran.position_cursor_x < COL_TMO_DF_PAUSE_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TMO_DF_PAUSE_END))
                    current_ekran.position_cursor_x = COL_TMO_DF_PAUSE_END;
                }
                else
                {
                  if (current_ekran.position_cursor_x == COL_TMO_DF_WORK_COMMA )current_ekran.position_cursor_x--;
                  if ((current_ekran.position_cursor_x < COL_TMO_DF_WORK_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TMO_DF_WORK_END))
                    current_ekran.position_cursor_x = COL_TMO_DF_WORK_END;
                }
                //������� ����� ������� ������������ �������
                make_ekran_timeout_df(current_ekran.current_level - EKRAN_TIMEOUT_DF1);
              }
              else if(current_ekran.current_level == EKRAN_TIMEOUT_ANALOG_REGISTRATOR)
              {
                if(current_ekran.index_position == INDEX_ML_TMOPREFAULT)
                {
                  if (current_ekran.position_cursor_x == COL_TMO_PREFAULT_COMMA )current_ekran.position_cursor_x--;
                  if ((current_ekran.position_cursor_x < COL_TMO_PREFAULT_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TMO_PREFAULT_END))
                    current_ekran.position_cursor_x = COL_TMO_PREFAULT_END;
                }
                else
                {
                  if (current_ekran.position_cursor_x == COL_TMO_POSTFAULT_COMMA )current_ekran.position_cursor_x--;
                  if ((current_ekran.position_cursor_x < COL_TMO_POSTFAULT_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TMO_POSTFAULT_END))
                    current_ekran.position_cursor_x = COL_TMO_POSTFAULT_END;
                }
                //������� ����� �������� ����������� ����������
                make_ekran_timeout_analog_registrator();
              }
              else if(current_ekran.current_level == EKRAN_CHOSE_EXTRA_SETTINGS)
              {
                //��������, ���� �� ����� �����
                unsigned int maska = (1 << current_ekran.index_position);
                
                //̳����� �� ����������� ��������� �� ��� ������� �������
                edition_settings.control_extra_settings_1 ^= maska;

                //������� ����� ����������� ���������� �����������
                make_ekran_chose_extra_settings();
              }

              //�������� �����������, �� ��������� ������ 
              new_state_keyboard &= (unsigned int)(~(1<<BIT_KEY_LEFT));
            }
            else
            {
              //��������� ����� ������� ������ - �� � ����������� ��������, ���� ������� ����������� ��� �������� ������ � ������ �����
              unsigned int temp_data = new_state_keyboard;
              new_state_keyboard &= ~temp_data;
            }
          }
        }
        break;
      }
/******************************************************************************************************************************************/ 

/******************************************************************************************************************************************/      
    case EKRAN_RANGUVANNJA_INPUT_1:
    case EKRAN_RANGUVANNJA_INPUT_2:
    case EKRAN_RANGUVANNJA_INPUT_3:
    case EKRAN_RANGUVANNJA_INPUT_4:
    case EKRAN_RANGUVANNJA_INPUT_5:
    case EKRAN_RANGUVANNJA_INPUT_6:
    case EKRAN_RANGUVANNJA_INPUT_7:
    case EKRAN_RANGUVANNJA_INPUT_8:
    case EKRAN_RANGUVANNJA_INPUT_9:
    case EKRAN_RANGUVANNJA_INPUT_10:
    case EKRAN_RANGUVANNJA_OUTPUT_1:
    case EKRAN_RANGUVANNJA_OUTPUT_2:
    case EKRAN_RANGUVANNJA_OUTPUT_3:
    case EKRAN_RANGUVANNJA_OUTPUT_4:
    case EKRAN_RANGUVANNJA_OUTPUT_5:
    case EKRAN_RANGUVANNJA_OUTPUT_6:
    case EKRAN_RANGUVANNJA_OUTPUT_7:
    case EKRAN_RANGUVANNJA_OUTPUT_8:
    case EKRAN_RANGUVANNJA_OUTPUT_9:
    case EKRAN_RANGUVANNJA_OUTPUT_10:
    case EKRAN_RANGUVANNJA_LED_1:
    case EKRAN_RANGUVANNJA_LED_2:
    case EKRAN_RANGUVANNJA_LED_3:
    case EKRAN_RANGUVANNJA_LED_4:
    case EKRAN_RANGUVANNJA_LED_5:
    case EKRAN_RANGUVANNJA_LED_6:
    case EKRAN_RANGUVANNJA_LED_7:
    case EKRAN_RANGUVANNJA_LED_8:
    case EKRAN_RANGUVANNJA_ANALOG_REGISTRATOR:
    case EKRAN_RANGUVANNJA_DIGITAL_REGISTRATOR:
    case EKRAN_RANGUVANNJA_OFF_CB:
    case EKRAN_RANGUVANNJA_ON_CB:
    case EKRAN_RANGUVANNJA_DF1_PLUS:
    case EKRAN_RANGUVANNJA_DF1_MINUS:
    case EKRAN_RANGUVANNJA_DF1_BLK:
    case EKRAN_RANGUVANNJA_DF2_PLUS:
    case EKRAN_RANGUVANNJA_DF2_MINUS:
    case EKRAN_RANGUVANNJA_DF2_BLK:
    case EKRAN_RANGUVANNJA_DF3_PLUS:
    case EKRAN_RANGUVANNJA_DF3_MINUS:
    case EKRAN_RANGUVANNJA_DF3_BLK:
    case EKRAN_RANGUVANNJA_DF4_PLUS:
    case EKRAN_RANGUVANNJA_DF4_MINUS:
    case EKRAN_RANGUVANNJA_DF4_BLK:
    case EKRAN_RANGUVANNJA_DF5_PLUS:
    case EKRAN_RANGUVANNJA_DF5_MINUS:
    case EKRAN_RANGUVANNJA_DF5_BLK:
    case EKRAN_RANGUVANNJA_DF6_PLUS:
    case EKRAN_RANGUVANNJA_DF6_MINUS:
    case EKRAN_RANGUVANNJA_DF6_BLK:
    case EKRAN_RANGUVANNJA_DF7_PLUS:
    case EKRAN_RANGUVANNJA_DF7_MINUS:
    case EKRAN_RANGUVANNJA_DF7_BLK:
    case EKRAN_RANGUVANNJA_DF8_PLUS:
    case EKRAN_RANGUVANNJA_DF8_MINUS:
    case EKRAN_RANGUVANNJA_DF8_BLK:
    case EKRAN_RANGUVANNJA_SET_DT1_PLUS:
    case EKRAN_RANGUVANNJA_SET_DT1_MINUS:
    case EKRAN_RANGUVANNJA_RESET_DT1_PLUS:
    case EKRAN_RANGUVANNJA_RESET_DT1_MINUS:
    case EKRAN_RANGUVANNJA_SET_DT2_PLUS:
    case EKRAN_RANGUVANNJA_SET_DT2_MINUS:
    case EKRAN_RANGUVANNJA_RESET_DT2_PLUS:
    case EKRAN_RANGUVANNJA_RESET_DT2_MINUS:
    case EKRAN_RANGUVANNJA_SET_DT3_PLUS:
    case EKRAN_RANGUVANNJA_SET_DT3_MINUS:
    case EKRAN_RANGUVANNJA_RESET_DT3_PLUS:
    case EKRAN_RANGUVANNJA_RESET_DT3_MINUS:
    case EKRAN_RANGUVANNJA_SET_DT4_PLUS:
    case EKRAN_RANGUVANNJA_SET_DT4_MINUS:
    case EKRAN_RANGUVANNJA_RESET_DT4_PLUS:
    case EKRAN_RANGUVANNJA_RESET_DT4_MINUS:
    case EKRAN_RANGUVANNJA_D_AND1:
    case EKRAN_RANGUVANNJA_D_AND2:
    case EKRAN_RANGUVANNJA_D_AND3:
    case EKRAN_RANGUVANNJA_D_AND4:
    case EKRAN_RANGUVANNJA_D_AND5:
    case EKRAN_RANGUVANNJA_D_AND6:
    case EKRAN_RANGUVANNJA_D_AND7:
    case EKRAN_RANGUVANNJA_D_AND8:
    case EKRAN_RANGUVANNJA_D_OR1:
    case EKRAN_RANGUVANNJA_D_OR2:
    case EKRAN_RANGUVANNJA_D_OR3:
    case EKRAN_RANGUVANNJA_D_OR4:
    case EKRAN_RANGUVANNJA_D_OR5:
    case EKRAN_RANGUVANNJA_D_OR6:
    case EKRAN_RANGUVANNJA_D_OR7:
    case EKRAN_RANGUVANNJA_D_OR8:
    case EKRAN_RANGUVANNJA_D_XOR1:
    case EKRAN_RANGUVANNJA_D_XOR2:
    case EKRAN_RANGUVANNJA_D_XOR3:
    case EKRAN_RANGUVANNJA_D_XOR4:
    case EKRAN_RANGUVANNJA_D_XOR5:
    case EKRAN_RANGUVANNJA_D_XOR6:
    case EKRAN_RANGUVANNJA_D_XOR7:
    case EKRAN_RANGUVANNJA_D_XOR8:
    case EKRAN_RANGUVANNJA_D_NOT1:
    case EKRAN_RANGUVANNJA_D_NOT2:
    case EKRAN_RANGUVANNJA_D_NOT3:
    case EKRAN_RANGUVANNJA_D_NOT4:
    case EKRAN_RANGUVANNJA_D_NOT5:
    case EKRAN_RANGUVANNJA_D_NOT6:
    case EKRAN_RANGUVANNJA_D_NOT7:
    case EKRAN_RANGUVANNJA_D_NOT8:
    case EKRAN_RANGUVANNJA_D_NOT9:
    case EKRAN_RANGUVANNJA_D_NOT10:
    case EKRAN_RANGUVANNJA_D_NOT11:
    case EKRAN_RANGUVANNJA_D_NOT12:
    case EKRAN_RANGUVANNJA_D_NOT13:
    case EKRAN_RANGUVANNJA_D_NOT14:
    case EKRAN_RANGUVANNJA_D_NOT15:
    case EKRAN_RANGUVANNJA_D_NOT16:
    case EKRAN_RANGUVANNJA_BUTTON_1:
    case EKRAN_RANGUVANNJA_BUTTON_2:
    case EKRAN_RANGUVANNJA_BUTTON_3:
    case EKRAN_RANGUVANNJA_BUTTON_4:
    case EKRAN_RANGUVANNJA_BUTTON_5:
    case EKRAN_RANGUVANNJA_BUTTON_6:
      {
        //������� �� ��� ���� �����������
        unsigned int maska_keyboard_bits = (1<<BIT_KEY_ENTER)| (1<<BIT_KEY_ESC)|(1<<BIT_REWRITE);
        
        if (current_ekran.edition == 1)
          maska_keyboard_bits |= (1<<BIT_KEY_RIGHT) | (1<<BIT_KEY_LEFT) | (1<<BIT_KEY_UP)|(1<<BIT_KEY_DOWN);
        else if (current_ekran.edition == 0)
          maska_keyboard_bits |= (1<<BIT_KEY_UP)|(1<<BIT_KEY_DOWN);
        
        new_state_keyboard &= maska_keyboard_bits;
        //������ �������� 䳿, ���� ��������� ������ �� ��� ����� ��������, ��� ����� ������� �������� �����
        if (new_state_keyboard !=0)
        {
          //�������� ����� �� ��������� ������
          if((new_state_keyboard & (1<<BIT_REWRITE)) !=0)
          {
            if((current_ekran.current_level >= EKRAN_RANGUVANNJA_INPUT_1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_INPUT_10))
            {
              if(current_ekran.index_position >= MAX_ROW_RANGUVANNJA_INPUT) current_ekran.index_position = 0;
              if(current_ekran.edition == 0)
              {
                unsigned int temp_state[N_SMALL];
                temp_state[0] = current_settings.ranguvannja_inputs[N_SMALL*(current_ekran.current_level - EKRAN_RANGUVANNJA_INPUT_1)    ];
                temp_state[1] = current_settings.ranguvannja_inputs[N_SMALL*(current_ekran.current_level - EKRAN_RANGUVANNJA_INPUT_1) + 1];
                
                if (
                    (temp_state[0] == 0) &&
                    (temp_state[1] == 0)
                   ) current_ekran.index_position = 0;
                else
                {
                  // (x>>5) ��������� �������� x / 32 - ���� ������� �� ������ �� 32
                  // (x & 0x1f) ��������� �������� x % 32 - ������ �� ������ �� 32
                  while ((temp_state[current_ekran.index_position >> 5] & (1<<(current_ekran.index_position  & 0x1f))) == 0)
                  {
                    current_ekran.index_position++;
                    if(current_ekran.index_position >= MAX_ROW_RANGUVANNJA_INPUT) current_ekran.index_position = 0;
                  }
                }
              }
              else
              {
                unsigned int found_new_index = 0;
//                int add_filter[0 + 1] = 
//                {
//                  -1 /*������� ���������� ������*/
//                };
//                EL_FILTER_STRUCT el_filter[NUMBER_DEFINED_ELEMENTS] =
//                {
//                  {1, RANG_INPUT_DF1_IN , RANG_INPUT_DF8_IN   , 1, current_settings.number_defined_df },
//                  {1, RANG_INPUT_DT1_SET, RANG_INPUT_DT4_RESET, 2, current_settings.number_defined_dt },
//                  {0, 0                 , 0                   , 1, current_settings.number_defined_and},
//                  {0, 0                 , 0                   , 1, current_settings.number_defined_or },
//                  {0, 0                 , 0                   , 1, current_settings.number_defined_xor},
//                  {0, 0                 , 0                   , 1, current_settings.number_defined_not}
//                };
                
                //����������, �� ����� ������ ������� ��������� � ����� ������������ 
                while (found_new_index == 0)
                {
                  check_current_index_is_presented_in_configuration(&found_new_index,
                                                                     /*add_filter,*/
                                                                     /*el_filter,*/
                                                                     1,
                                                                     NUMBER_GENERAL_SIGNAL_FOR_RANG_INPUT,
                                                                     NUMBER_CTRL_PHASE_SIGNAL_FOR_RANG_INPUT,
                                                                     NUMBER_EL_SIGNAL_FOR_RANG_INPUT
                                                                    );
                    //����������, �� �� �� ������ �� ��������� ������� �������
                    if(current_ekran.index_position >= MAX_ROW_RANGUVANNJA_INPUT)
                    {
                      found_new_index = 0;
                      current_ekran.index_position = 0;
                    }
                }
              }
              position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;
              //������� ����� ����������� ����������� �������
              make_ekran_set_function_in_input(current_ekran.current_level);
            }
            else if((current_ekran.current_level >= EKRAN_RANGUVANNJA_BUTTON_1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_BUTTON_6))
            {
              if(current_ekran.index_position >= MAX_ROW_RANGUVANNJA_BUTTON) current_ekran.index_position = 0;
              if(current_ekran.edition == 0)
              {
                unsigned int temp_state = current_settings.ranguvannja_buttons[current_ekran.current_level - EKRAN_RANGUVANNJA_BUTTON_1];
                if (temp_state == 0) current_ekran.index_position = 0;
                else
                {
                  while ((temp_state & (1<<current_ekran.index_position)) ==0)
                  {
                    current_ekran.index_position++;
                    if(current_ekran.index_position >= MAX_ROW_RANGUVANNJA_BUTTON) current_ekran.index_position = 0;
                  }
                }
              }
              else
              {
                unsigned int found_new_index = 0;
//                int add_filter[0 + 1] = 
//                {
//                  -1 /*������� ���������� ������*/
//                };
//                EL_FILTER_STRUCT el_filter[NUMBER_DEFINED_ELEMENTS] =
//                {
//                  {1, RANG_BUTTON_DF1_IN , RANG_BUTTON_DF8_IN   , 1, current_settings.number_defined_df },
//                  {1, RANG_BUTTON_DT1_SET, RANG_BUTTON_DT4_RESET, 2, current_settings.number_defined_dt },
//                  {0, 0                  , 0                    , 1, current_settings.number_defined_and},
//                  {0, 0                  , 0                    , 1, current_settings.number_defined_or },
//                  {0, 0                  , 0                    , 1, current_settings.number_defined_xor},
//                  {0, 0                  , 0                    , 1, current_settings.number_defined_not}
//                };
                
                //����������, �� ����� ������ ������� ��������� � ����� ������������ 
                while (found_new_index == 0)
                {
                  check_current_index_is_presented_in_configuration(&found_new_index,
                                                                     /*add_filter,*/
                                                                     /*el_filter,*/
                                                                     1,
                                                                     NUMBER_GENERAL_SIGNAL_FOR_RANG_BUTTON,
                                                                     NUMBER_CTRL_PHASE_SIGNAL_FOR_RANG_BUTTON,
                                                                     NUMBER_EL_SIGNAL_FOR_RANG_BUTTON
                                                                    );
                    //����������, �� �� �� ������ �� ��������� ������� �������
                    if(current_ekran.index_position >= MAX_ROW_RANGUVANNJA_BUTTON)
                    {
                      found_new_index = 0;
                      current_ekran.index_position = 0;
                    }
                }
              }
              position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;
              //������� ����� ����������� ����������� �������
              make_ekran_set_function_in_button(current_ekran.current_level);
            }
            else if(
                    ((current_ekran.current_level >= EKRAN_RANGUVANNJA_OUTPUT_1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_OUTPUT_10          )) ||
                    ((current_ekran.current_level >= EKRAN_RANGUVANNJA_LED_1   ) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_LED_8              )) ||
                    ( current_ekran.current_level == EKRAN_RANGUVANNJA_ANALOG_REGISTRATOR                                                                 ) ||
                    ( current_ekran.current_level == EKRAN_RANGUVANNJA_OFF_CB                                                                             ) ||
                    ( current_ekran.current_level == EKRAN_RANGUVANNJA_ON_CB                                                                              ) ||
                    ((current_ekran.current_level >= EKRAN_RANGUVANNJA_DF1_PLUS) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_DF8_BLK            )) ||
                    ((current_ekran.current_level >= EKRAN_RANGUVANNJA_SET_DT1_PLUS) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_RESET_DT4_MINUS)) ||
                    ((current_ekran.current_level >= EKRAN_RANGUVANNJA_D_AND1      ) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_AND8         )) ||
                    ((current_ekran.current_level >= EKRAN_RANGUVANNJA_D_OR1       ) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_OR8          )) ||
                    ((current_ekran.current_level >= EKRAN_RANGUVANNJA_D_XOR1      ) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_XOR8         )) ||
                    ((current_ekran.current_level >= EKRAN_RANGUVANNJA_D_NOT1      ) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_NOT16        ))
                   )
            {
              int max_row_ranguvannja;
              
              if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_OUTPUT_1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_OUTPUT_10))
                max_row_ranguvannja = MAX_ROW_RANGUVANNJA_OUTPUT;
              else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_LED_1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_LED_8))
                max_row_ranguvannja = MAX_ROW_RANGUVANNJA_LED;
              else if (current_ekran.current_level == EKRAN_RANGUVANNJA_ANALOG_REGISTRATOR)
                max_row_ranguvannja = MAX_ROW_RANGUVANNJA_ANALOG_REGISTRATOR;
              else if (current_ekran.current_level == EKRAN_RANGUVANNJA_DIGITAL_REGISTRATOR)
                max_row_ranguvannja = MAX_ROW_RANGUVANNJA_DIGITAL_REGISTRATOR;
              else if (current_ekran.current_level == EKRAN_RANGUVANNJA_OFF_CB)
                max_row_ranguvannja = MAX_ROW_RANGUVANNJA_OFF_CB;
              else if (current_ekran.current_level == EKRAN_RANGUVANNJA_ON_CB)
                max_row_ranguvannja = MAX_ROW_RANGUVANNJA_ON_CB;
              else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_DF1_PLUS) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_DF8_BLK ))
                max_row_ranguvannja = MAX_ROW_RANGUVANNJA_DF;
              else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_SET_DT1_PLUS) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_RESET_DT4_MINUS))
                max_row_ranguvannja = MAX_ROW_RANGUVANNJA_DT;
              else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_D_AND1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_AND8))
                max_row_ranguvannja = MAX_ROW_RANGUVANNJA_D_AND;
              else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_D_OR1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_OR8))
                max_row_ranguvannja = MAX_ROW_RANGUVANNJA_D_OR;
              else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_D_XOR1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_XOR8))
                max_row_ranguvannja = MAX_ROW_RANGUVANNJA_D_XOR;
              else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_D_NOT1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_NOT16))
                max_row_ranguvannja = MAX_ROW_RANGUVANNJA_D_NOT;
                
              if(current_ekran.index_position >= max_row_ranguvannja) current_ekran.index_position = 0;
              if(current_ekran.edition == 0)
              {
                unsigned int temp_state[N_BIG];
                
                if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_OUTPUT_1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_OUTPUT_10))
                {
                  for (unsigned int i = 0; i < N_BIG; i++ ) temp_state[i] = current_settings.ranguvannja_outputs[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_OUTPUT_1)+i];
                }
                else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_LED_1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_LED_8))
                {
                  for (unsigned int i = 0; i < N_BIG; i++ ) temp_state[i] = current_settings.ranguvannja_leds[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_LED_1)+i];
                }
                else if (current_ekran.current_level == EKRAN_RANGUVANNJA_ANALOG_REGISTRATOR)
                {
                  for (unsigned int i = 0; i < N_BIG; i++ ) temp_state[i] = current_settings.ranguvannja_analog_registrator[i];
                }
                else if (current_ekran.current_level == EKRAN_RANGUVANNJA_DIGITAL_REGISTRATOR)
                {
                  for (unsigned int i = 0; i < N_BIG; i++ ) temp_state[i] = current_settings.ranguvannja_digital_registrator[i];
                }
                else if (current_ekran.current_level == EKRAN_RANGUVANNJA_OFF_CB)
                {
                  for (unsigned int i = 0; i < N_BIG; i++ ) temp_state[i] = current_settings.ranguvannja_off_cb[i];
                }
                else if (current_ekran.current_level == EKRAN_RANGUVANNJA_ON_CB)
                {
                  for (unsigned int i = 0; i < N_BIG; i++ ) temp_state[i] = current_settings.ranguvannja_on_cb[i];
                }
                else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_DF1_PLUS) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_DF8_BLK ))
                {
                  unsigned int index_in_ekran_list = current_ekran.current_level - EKRAN_RANGUVANNJA_DF1_PLUS;
                  unsigned int type_source = index_in_ekran_list % 3;
                  unsigned int index_of_df = index_in_ekran_list / 3;
    
                  if(type_source == 0)
                  {
                    for (unsigned int i = 0; i < N_BIG; i++ ) temp_state[i] = current_settings.ranguvannja_df_source_plus[N_BIG*index_of_df+i];
                  }
                  else if(type_source == 1)
                  {
                    for (unsigned int i = 0; i < N_BIG; i++ ) temp_state[i] = current_settings.ranguvannja_df_source_minus[N_BIG*index_of_df+i];
                  }
                  else
                  {
                    for (unsigned int i = 0; i < N_BIG; i++ ) temp_state[i] = current_settings.ranguvannja_df_source_blk[N_BIG*index_of_df+i];
                  }
                }
                else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_SET_DT1_PLUS) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_RESET_DT4_MINUS))
                {
                  unsigned int index_in_ekran_list = current_ekran.current_level - EKRAN_RANGUVANNJA_SET_DT1_PLUS;
                  unsigned int type_source = index_in_ekran_list % 2;
                  unsigned int type_of_action = (index_in_ekran_list / 2) & 0x1;
                  unsigned int index_of_dt = index_in_ekran_list / 4;
    
                  if (type_of_action == INDEX_ML_SET_DT)
                  {
                    if(type_source == INDEX_ML_LIST_TYPE_SOURCE_PLUS_DT)
                    {
                      for (unsigned int i = 0; i < N_BIG; i++ ) temp_state[i] = current_settings.ranguvannja_set_dt_source_plus[N_BIG*index_of_dt+i];
                    }
                    else
                    {
                      for (unsigned int i = 0; i < N_BIG; i++ ) temp_state[i] = current_settings.ranguvannja_set_dt_source_minus[N_BIG*index_of_dt+i];
                    }
                  }
                  else
                  {
                    if(type_source == INDEX_ML_LIST_TYPE_SOURCE_PLUS_DT)
                    {
                      for (unsigned int i = 0; i < N_BIG; i++ ) temp_state[i] = current_settings.ranguvannja_reset_dt_source_plus[N_BIG*index_of_dt+i];
                    }
                    else
                    {
                      for (unsigned int i = 0; i < N_BIG; i++ ) temp_state[i] = current_settings.ranguvannja_reset_dt_source_minus[N_BIG*index_of_dt+i];
                    }
                  }                    
                }
                else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_D_AND1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_AND8))
                {
                  for (unsigned int i = 0; i < N_BIG; i++ ) temp_state[i] = current_settings.ranguvannja_d_and[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_AND1)+i];
                }
                else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_D_OR1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_OR8))
                {
                  for (unsigned int i = 0; i < N_BIG; i++ ) temp_state[i] = current_settings.ranguvannja_d_or[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_OR1)+i];
                }
                else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_D_XOR1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_XOR8))
                {
                  for (unsigned int i = 0; i < N_BIG; i++ ) temp_state[i] = current_settings.ranguvannja_d_xor[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_XOR1)+i];
                }
                else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_D_NOT1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_NOT16))
                {
                  for (unsigned int i = 0; i < N_BIG; i++ ) temp_state[i] = current_settings.ranguvannja_d_not[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_NOT1)+i];
                }

                if (
                    (temp_state[0] == 0) &&
                    (temp_state[1] == 0) &&
                    (temp_state[2] == 0) &&
                    (temp_state[3] == 0) &&
                    (temp_state[4] == 0) &&
                    (temp_state[5] == 0) &&
                    (temp_state[6] == 0)
                   ) current_ekran.index_position = 0;
                else
                {
                  // (x>>5) ��������� �������� x / 32 - ���� ������� �� ������ �� 32
                  // (x & 0x1f) ��������� �������� x % 32 - ������ �� ������ �� 32
                  while ((temp_state[current_ekran.index_position >> 5] & (1<<(current_ekran.index_position  & 0x1f))) ==0)
                  {
                    current_ekran.index_position++;
                    if(current_ekran.index_position >= max_row_ranguvannja) current_ekran.index_position = 0;
                  }
                }
              }
              else
              {
                unsigned int found_new_index = 0;
//                int add_filter[3 + 1] = 
//                {
//                  RANG_PO_NZZ,
//                  RANG_NZZ,
//                  RANG_SECTOR_NZZ,
//                  -1 /*������� ���������� ������*/
//                };
//                EL_FILTER_STRUCT el_filter[NUMBER_DEFINED_ELEMENTS] =
//                {
//                  {1, RANG_DF1_IN , RANG_DF8_OUT, 2, current_settings.number_defined_df },
//                  {1, RANG_DT1_SET, RANG_DT4_OUT, 3, current_settings.number_defined_dt },
//                  {1, RANG_D_AND1 , RANG_D_AND8 , 1, current_settings.number_defined_and},
//                  {1, RANG_D_OR1  , RANG_D_OR8  , 1, current_settings.number_defined_or },
//                  {1, RANG_D_XOR1 , RANG_D_XOR8 , 1, current_settings.number_defined_xor},
//                  {1, RANG_D_NOT1 , RANG_D_NOT16, 1, current_settings.number_defined_not}
//                };
                
                //����������, �� ����� ������ ������� ��������� � ����� ������������ 
                while (found_new_index == 0)
                {
                  check_current_index_is_presented_in_configuration(&found_new_index,
                                                                     /*add_filter,*/
                                                                     /*el_filter,*/
                                                                     1,
                                                                     NUMBER_GENERAL_SIGNAL_FOR_RANG,
                                                                     NUMBER_CTRL_PHASE_SIGNAL_FOR_RANG,
                                                                     NUMBER_EL_SIGNAL_FOR_RANG
                                                                    );
                  
                  //����������, �� �� ��  �� ������ ������� �� ������ ���������, ��� ����� �������� ��� ������ ���� ����������
                  if (
                      ( current_ekran.current_level == EKRAN_RANGUVANNJA_ANALOG_REGISTRATOR ) ||   
                      ( current_ekran.current_level == EKRAN_RANGUVANNJA_DIGITAL_REGISTRATOR) ||
                      ( current_ekran.current_level == EKRAN_RANGUVANNJA_OFF_CB             ) ||   
                      ( current_ekran.current_level == EKRAN_RANGUVANNJA_ON_CB              )   
                     )   
                  {
                    unsigned int index_deleted_function;

                    if (current_ekran.current_level == EKRAN_RANGUVANNJA_ANALOG_REGISTRATOR)
                      index_deleted_function = RANG_WORK_A_REJESTRATOR;
                    else if (current_ekran.current_level == EKRAN_RANGUVANNJA_DIGITAL_REGISTRATOR)
                      index_deleted_function = RANG_WORK_D_REJESTRATOR;
                    else if (current_ekran.current_level == EKRAN_RANGUVANNJA_OFF_CB)
                      index_deleted_function = RANG_WORK_BO;
                    else if (current_ekran.current_level == EKRAN_RANGUVANNJA_ON_CB)
                      index_deleted_function = RANG_WORK_BV;
                    
                    if(index_deleted_function == current_ekran.index_position)
                    {
                      found_new_index = 0;
                      current_ekran.index_position++;
                    }
                  }
                  else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_DF1_PLUS) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_DF8_BLK))
                  {
                    unsigned int index_in_ekran_list = current_ekran.current_level - EKRAN_RANGUVANNJA_DF1_PLUS;
                    unsigned int index_of_df = index_in_ekran_list / 3;

                    for (unsigned int i = 0; i < 2; i++)
                    {
                      unsigned int index_deleted_function;
                      //������ ���������� ������� � ������ �������, ��� �� ���� �������� �����  ����� ���� ������������ �� �������, ��� ����� ���������
                      if (i == 0)
                      {
                        if(index_of_df == 0)
                          index_deleted_function = (RANG_DF1_OUT > RANG_DF1_IN) ? RANG_DF1_IN : RANG_DF1_OUT;
                        else if(index_of_df == 1)
                          index_deleted_function = (RANG_DF2_OUT > RANG_DF2_IN) ? RANG_DF2_IN : RANG_DF2_OUT;
                        else if(index_of_df == 2)
                          index_deleted_function = (RANG_DF3_OUT > RANG_DF3_IN) ? RANG_DF3_IN : RANG_DF3_OUT;
                        else if(index_of_df == 3)
                          index_deleted_function = (RANG_DF4_OUT > RANG_DF4_IN) ? RANG_DF4_IN : RANG_DF4_OUT;
                        else if(index_of_df == 4)
                          index_deleted_function = (RANG_DF5_OUT > RANG_DF5_IN) ? RANG_DF5_IN : RANG_DF5_OUT;
                        else if(index_of_df == 5)
                          index_deleted_function = (RANG_DF6_OUT > RANG_DF6_IN) ? RANG_DF6_IN : RANG_DF6_OUT;
                        else if(index_of_df == 6)
                          index_deleted_function = (RANG_DF7_OUT > RANG_DF7_IN) ? RANG_DF7_IN : RANG_DF7_OUT;
                        else
                          index_deleted_function = (RANG_DF8_OUT > RANG_DF8_IN) ? RANG_DF8_IN : RANG_DF8_OUT;
                      }
                      else
                      {
                        if(index_of_df == 0)
                          index_deleted_function = (RANG_DF1_OUT > RANG_DF1_IN) ? RANG_DF1_OUT : RANG_DF1_IN;
                        else if(index_of_df == 1)
                          index_deleted_function = (RANG_DF2_OUT > RANG_DF2_IN) ? RANG_DF2_OUT : RANG_DF2_IN;
                        else if(index_of_df == 2)
                          index_deleted_function = (RANG_DF3_OUT > RANG_DF3_IN) ? RANG_DF3_OUT : RANG_DF3_IN;
                        else if(index_of_df == 3)
                          index_deleted_function = (RANG_DF4_OUT > RANG_DF4_IN) ? RANG_DF4_OUT : RANG_DF4_IN;
                        else if(index_of_df == 4)
                          index_deleted_function = (RANG_DF5_OUT > RANG_DF5_IN) ? RANG_DF5_OUT : RANG_DF5_IN;
                        else if(index_of_df == 5)
                          index_deleted_function = (RANG_DF6_OUT > RANG_DF6_IN) ? RANG_DF6_OUT : RANG_DF6_IN;
                        else if(index_of_df == 6)
                          index_deleted_function = (RANG_DF7_OUT > RANG_DF7_IN) ? RANG_DF7_OUT : RANG_DF7_IN;
                        else
                          index_deleted_function = (RANG_DF8_OUT > RANG_DF8_IN) ? RANG_DF8_OUT : RANG_DF8_IN;
                      }
                    
                      if(index_deleted_function == current_ekran.index_position)
                      {
                        found_new_index = 0;
                        current_ekran.index_position++;
                      }
                    }
                  }
                  else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_SET_DT1_PLUS) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_RESET_DT4_MINUS))
                  {
                    unsigned int index_in_ekran_list = current_ekran.current_level - EKRAN_RANGUVANNJA_SET_DT1_PLUS;
                    unsigned int index_of_dt = index_in_ekran_list / 4;

                    for (unsigned int i = 0; i < 3; i++)
                    {
                      unsigned int index_deleted_function;
                      //������ ���������� ������� � ������ �������, ��� �� ���� �������� �����  ����� ���� ������������ �� �������, ��� ����� ���������
                      if (i == 0)
                      {
                        if(index_of_dt == 0)
                          index_deleted_function = RANG_DT1_SET;
                        else if(index_of_dt == 1)
                          index_deleted_function = RANG_DT2_SET;
                        else if(index_of_dt == 2)
                          index_deleted_function = RANG_DT3_SET;
                        else if(index_of_dt == 3)
                          index_deleted_function = RANG_DT4_SET;
                      }
                      else if (i == 1)
                      {
                        if(index_of_dt == 0)
                          index_deleted_function = RANG_DT1_RESET;
                        else if(index_of_dt == 1)
                          index_deleted_function = RANG_DT2_RESET;
                        else if(index_of_dt == 2)
                          index_deleted_function = RANG_DT3_RESET;
                        else if(index_of_dt == 3)
                          index_deleted_function = RANG_DT4_RESET;
                      }
                      else
                      {
                        if(index_of_dt == 0)
                          index_deleted_function = RANG_DT1_OUT;
                        else if(index_of_dt == 1)
                          index_deleted_function = RANG_DT2_OUT;
                        else if(index_of_dt == 2)
                          index_deleted_function = RANG_DT3_OUT;
                        else if(index_of_dt == 3)
                          index_deleted_function = RANG_DT4_OUT;
                      }
                    
                      if(index_deleted_function == current_ekran.index_position)
                      {
                        found_new_index = 0;
                        current_ekran.index_position++;
                      }
                    }
                  }
                  else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_D_AND1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_AND8))
                  {
                    unsigned int index_of_d_and = current_ekran.current_level - EKRAN_RANGUVANNJA_D_AND1;

                    //������ ���������� ������� � ������ �������, ��� �� ���� �������� �����  ����� ���� ������������ �� �������, ��� ����� ���������
                    unsigned int index_deleted_function = RANG_D_AND1 + index_of_d_and;
                    
                    if(index_deleted_function == current_ekran.index_position)
                    {
                      found_new_index = 0;
                      current_ekran.index_position++;
                    }
                  }
                  else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_D_OR1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_OR8))
                  {
                    unsigned int index_of_d_or = current_ekran.current_level - EKRAN_RANGUVANNJA_D_OR1;

                    //������ ���������� ������� � ������ �������, ��� �� ���� �������� �����  ����� ���� ������������ �� �������, ��� ����� ���������
                    unsigned int index_deleted_function = RANG_D_OR1 + index_of_d_or;
                    
                    if(index_deleted_function == current_ekran.index_position)
                    {
                      found_new_index = 0;
                      current_ekran.index_position++;
                    }
                  }
                  else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_D_XOR1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_XOR8))
                  {
                    unsigned int index_of_d_xor = current_ekran.current_level - EKRAN_RANGUVANNJA_D_XOR1;

                    //������ ���������� ������� � ������ �������, ��� �� ���� �������� �����  ����� ���� ������������ �� �������, ��� ����� ���������
                    unsigned int index_deleted_function = RANG_D_XOR1 + index_of_d_xor;
                    
                    if(index_deleted_function == current_ekran.index_position)
                    {
                      found_new_index = 0;
                      current_ekran.index_position++;
                    }
                  }
                  else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_D_NOT1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_NOT16))
                  {
                    unsigned int index_of_d_not = current_ekran.current_level - EKRAN_RANGUVANNJA_D_NOT1;

                    //������ ���������� ������� � ������ �������, ��� �� ���� �������� �����  ����� ���� ������������ �� �������, ��� ����� ���������
                    unsigned int index_deleted_function = RANG_D_NOT1 + index_of_d_not;
                    
                    if(index_deleted_function == current_ekran.index_position)
                    {
                      found_new_index = 0;
                      current_ekran.index_position++;
                    }
                  }
//                  else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_OUTPUT_1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_OUTPUT_10))
//                  {
//                    unsigned int current_number_output = current_ekran.current_level - EKRAN_RANGUVANNJA_OUTPUT_1;
//                      
//                    for (unsigned int i = 0; i < 2; i++)
//                    {
//                      unsigned int index_deleted_function;
//                      unsigned int maska_func[N_BIG] = {0, 0, 0, 0, 0, 0, 0, 0};
//                      unsigned int need_filtration = 0;
//                      //��������� ������ �������, ��� ���������� ������� ����� ���� ����������� �� �������
//                      //������ ���������� ������� � ������ �������, ��� �� ���� �������� �����  ����� ���� ������������ �� �������, ��� ����� ���������
//                      if (i == 0)
//                      {
//                        index_deleted_function = (RANG_WORK_BV > RANG_WORK_BO) ? RANG_WORK_BO : RANG_WORK_BV;
//                      }
//                      else
//                      {
//                        index_deleted_function = (RANG_WORK_BV > RANG_WORK_BO) ? RANG_WORK_BV : RANG_WORK_BO;
//                      }
//        
//                      //������� �����  ��� ���� �������
//                      _SET_BIT(maska_func, index_deleted_function);
//        
//                      unsigned int index = 0;
//                      while ((need_filtration == 0) && (index < NUMBER_OUTPUTS))
//                      {
//                        //���������� ������� ����� ������, �� �� ����� ���� ������� �� ������������ �� ��� �����������
//                        if (index != current_number_output)
//                        {
//                          if (
//                              ((current_settings.ranguvannja_outputs[N_BIG*index    ] & maska_func[0]) != 0) ||
//                              ((current_settings.ranguvannja_outputs[N_BIG*index + 1] & maska_func[1]) != 0) ||
//                              ((current_settings.ranguvannja_outputs[N_BIG*index + 2] & maska_func[2]) != 0) ||
//                              ((current_settings.ranguvannja_outputs[N_BIG*index + 3] & maska_func[3]) != 0) ||
//                              ((current_settings.ranguvannja_outputs[N_BIG*index + 4] & maska_func[4]) != 0) ||
//                              ((current_settings.ranguvannja_outputs[N_BIG*index + 5] & maska_func[5]) != 0) ||
//                              ((current_settings.ranguvannja_outputs[N_BIG*index + 6] & maska_func[6]) != 0) ||
//                              ((current_settings.ranguvannja_outputs[N_BIG*index + 7] & maska_func[7]) != 0)
//                             )
//                          {
//                            need_filtration = 1;
//                          }
//                        }
//                        index++;
//                      }
//                       
//                      //� �������, ���� ������������ � ��������, ���� ����� ����������� �������
//                      if (need_filtration != 0)
//                      {
//                        if(index_deleted_function == current_ekran.index_position)
//                        {
//                          found_new_index = 0;
//                          current_ekran.index_position++;
//                        }
//                      }
//                    }
//                  }

                  //����������, �� �� �� ������ �� ��������� ������� �������
                  if(current_ekran.index_position >= max_row_ranguvannja)
                  {
                    found_new_index = 0;
                    current_ekran.index_position = 0;
                  }
                }
              }
              position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;
              //������� ����� ����������� ����������� �������
              if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_OUTPUT_1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_OUTPUT_10))
                make_ekran_set_function_in_output_led_df_dt_reg(current_ekran.current_level, INDEX_VIEWING_OUTPUT);
              else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_LED_1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_LED_8))
                make_ekran_set_function_in_output_led_df_dt_reg(current_ekran.current_level, INDEX_VIEWING_LED);
              else if (current_ekran.current_level == EKRAN_RANGUVANNJA_ANALOG_REGISTRATOR)
                make_ekran_set_function_in_output_led_df_dt_reg(current_ekran.current_level, INDEX_VIEWING_A_REG);
              else if (current_ekran.current_level == EKRAN_RANGUVANNJA_DIGITAL_REGISTRATOR)
                make_ekran_set_function_in_output_led_df_dt_reg(current_ekran.current_level, INDEX_VIEWING_D_REG);
              else if (current_ekran.current_level == EKRAN_RANGUVANNJA_OFF_CB)
                make_ekran_set_function_in_output_led_df_dt_reg(current_ekran.current_level, INDEX_VIEWING_OFF_CB);
              else if (current_ekran.current_level == EKRAN_RANGUVANNJA_ON_CB)
                make_ekran_set_function_in_output_led_df_dt_reg(current_ekran.current_level, INDEX_VIEWING_ON_CB);
              else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_DF1_PLUS) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_DF8_BLK ))
                make_ekran_set_function_in_output_led_df_dt_reg(current_ekran.current_level, INDEX_VIEWING_DF);
              else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_SET_DT1_PLUS) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_RESET_DT4_MINUS))
                make_ekran_set_function_in_output_led_df_dt_reg(current_ekran.current_level, INDEX_VIEWING_DT);
              else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_D_AND1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_AND8))
                make_ekran_set_function_in_output_led_df_dt_reg(current_ekran.current_level, INDEX_VIEWING_D_AND);
              else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_D_OR1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_OR8))
                make_ekran_set_function_in_output_led_df_dt_reg(current_ekran.current_level, INDEX_VIEWING_D_OR);
              else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_D_XOR1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_XOR8))
                make_ekran_set_function_in_output_led_df_dt_reg(current_ekran.current_level, INDEX_VIEWING_D_XOR);
              else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_D_NOT1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_NOT16))
                make_ekran_set_function_in_output_led_df_dt_reg(current_ekran.current_level, INDEX_VIEWING_D_NOT);
            }
            
            //������� �� ���������� ������
            new_state_keyboard &= (unsigned int)(~(1<<BIT_REWRITE));
          }
          else
          {
            if (new_state_keyboard == (1<<BIT_KEY_ENTER))
            {
              //��������� ������ ENTER
              if(current_ekran.edition == 0)
              {
                //������� ���������� � ��������� ��� �����������
                if((current_ekran.current_level >= EKRAN_RANGUVANNJA_INPUT_1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_INPUT_10))
                {
                  edition_settings.ranguvannja_inputs[N_SMALL*(current_ekran.current_level - EKRAN_RANGUVANNJA_INPUT_1)] =
                    current_settings.ranguvannja_inputs[N_SMALL*(current_ekran.current_level - EKRAN_RANGUVANNJA_INPUT_1)];
                  edition_settings.ranguvannja_inputs[N_SMALL*(current_ekran.current_level - EKRAN_RANGUVANNJA_INPUT_1)+1] =
                    current_settings.ranguvannja_inputs[N_SMALL*(current_ekran.current_level - EKRAN_RANGUVANNJA_INPUT_1)+1];
                }
                else if((current_ekran.current_level >= EKRAN_RANGUVANNJA_BUTTON_1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_BUTTON_6))
                {
                  edition_settings.ranguvannja_buttons[current_ekran.current_level - EKRAN_RANGUVANNJA_BUTTON_1] =
                    current_settings.ranguvannja_buttons[current_ekran.current_level - EKRAN_RANGUVANNJA_BUTTON_1];
                }
                else if((current_ekran.current_level >= EKRAN_RANGUVANNJA_OUTPUT_1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_OUTPUT_10))
                {
                  for (unsigned int i = 0; i < N_BIG; i++)
                  {
                    edition_settings.ranguvannja_outputs[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_OUTPUT_1) + i] =
                      current_settings.ranguvannja_outputs[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_OUTPUT_1) + i];
                  }
                }
                else if((current_ekran.current_level >= EKRAN_RANGUVANNJA_LED_1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_LED_8))
                {
                  for (unsigned int i = 0; i < N_BIG; i++)
                  {
                    edition_settings.ranguvannja_leds[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_LED_1) + i] =
                      current_settings.ranguvannja_leds[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_LED_1) + i];
                  }
                }
                else if(current_ekran.current_level == EKRAN_RANGUVANNJA_ANALOG_REGISTRATOR)
                {
                  for (unsigned int i = 0; i < N_BIG; i++)
                  {
                    edition_settings.ranguvannja_analog_registrator[i] = current_settings.ranguvannja_analog_registrator[i];
                  }
                }
                else if(current_ekran.current_level == EKRAN_RANGUVANNJA_DIGITAL_REGISTRATOR)
                {
                  for (unsigned int i = 0; i < N_BIG; i++)
                  {
                    edition_settings.ranguvannja_digital_registrator[i] = current_settings.ranguvannja_digital_registrator[i];
                  }
                }
                else if(current_ekran.current_level == EKRAN_RANGUVANNJA_OFF_CB)
                {
                  for (unsigned int i = 0; i < N_BIG; i++)
                  {
                    edition_settings.ranguvannja_off_cb[i] = current_settings.ranguvannja_off_cb[i];
                  }
                }
                else if(current_ekran.current_level == EKRAN_RANGUVANNJA_ON_CB)
                {
                  for (unsigned int i = 0; i < N_BIG; i++)
                  {
                    edition_settings.ranguvannja_on_cb[i] = current_settings.ranguvannja_on_cb[i];
                  }
                }
                else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_DF1_PLUS) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_DF8_BLK ))
                {
                  unsigned int index_in_ekran_list = current_ekran.current_level - EKRAN_RANGUVANNJA_DF1_PLUS;
                  unsigned int type_source = index_in_ekran_list % 3;
                  unsigned int index_of_df = index_in_ekran_list / 3;
    
                  if(type_source == 0)
                  {
                    for (unsigned int i = 0; i < N_BIG; i++)
                    {
                      edition_settings.ranguvannja_df_source_plus[N_BIG*index_of_df + i] = current_settings.ranguvannja_df_source_plus[N_BIG*index_of_df + i];
                    }
                  }
                  else if(type_source == 1)
                  {
                    for (unsigned int i = 0; i < N_BIG; i++)
                    {
                      edition_settings.ranguvannja_df_source_minus[N_BIG*index_of_df + i] = current_settings.ranguvannja_df_source_minus[N_BIG*index_of_df + i];
                    }
                  }
                  else
                  {
                    for (unsigned int i = 0; i < N_BIG; i++)
                    {
                      edition_settings.ranguvannja_df_source_blk[N_BIG*index_of_df + i] = current_settings.ranguvannja_df_source_blk[N_BIG*index_of_df + i];
                    }
                  }
                }
                else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_SET_DT1_PLUS) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_RESET_DT4_MINUS))
                {
                  unsigned int index_in_ekran_list = current_ekran.current_level - EKRAN_RANGUVANNJA_SET_DT1_PLUS;
                  unsigned int type_source = index_in_ekran_list % 2;
                  unsigned int type_of_action = (index_in_ekran_list / 2) & 0x1;
                  unsigned int index_of_dt = index_in_ekran_list / 4;
    
                  if (type_of_action == INDEX_ML_SET_DT)
                  {
                    if(type_source == INDEX_ML_LIST_TYPE_SOURCE_PLUS_DT)
                    {
                      for (unsigned int i = 0; i < N_BIG; i++)
                      {
                        edition_settings.ranguvannja_set_dt_source_plus[N_BIG*index_of_dt + i] = current_settings.ranguvannja_set_dt_source_plus[N_BIG*index_of_dt + i];
                      }
                    }
                    else
                    {
                      for (unsigned int i = 0; i < N_BIG; i++)
                      {
                        edition_settings.ranguvannja_set_dt_source_minus[N_BIG*index_of_dt + i] = current_settings.ranguvannja_set_dt_source_minus[N_BIG*index_of_dt + i];
                      }
                    }
                  }
                  else
                  {
                    if(type_source == INDEX_ML_LIST_TYPE_SOURCE_PLUS_DT)
                    {
                      for (unsigned int i = 0; i < N_BIG; i++)
                      {
                        edition_settings.ranguvannja_reset_dt_source_plus[N_BIG*index_of_dt + i] = current_settings.ranguvannja_reset_dt_source_plus[N_BIG*index_of_dt + i];
                      }
                    }
                    else
                    {
                      for (unsigned int i = 0; i < N_BIG; i++)
                      {
                        edition_settings.ranguvannja_reset_dt_source_minus[N_BIG*index_of_dt + i] = current_settings.ranguvannja_reset_dt_source_minus[N_BIG*index_of_dt + i];
                      }
                    }
                  }
                }
                else if((current_ekran.current_level >= EKRAN_RANGUVANNJA_D_AND1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_AND8))
                {
                  for (unsigned int i = 0; i < N_BIG; i++)
                  {
                    edition_settings.ranguvannja_d_and[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_AND1) + i] =
                      current_settings.ranguvannja_d_and[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_AND1) + i];
                  }
                }
                else if((current_ekran.current_level >= EKRAN_RANGUVANNJA_D_OR1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_OR8))
                {
                  for (unsigned int i = 0; i < N_BIG; i++)
                  {
                    edition_settings.ranguvannja_d_or[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_OR1) + i] =
                      current_settings.ranguvannja_d_or[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_OR1) + i];
                  }
                }
                else if((current_ekran.current_level >= EKRAN_RANGUVANNJA_D_XOR1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_XOR8))
                {
                  for (unsigned int i = 0; i < N_BIG; i++)
                  {
                    edition_settings.ranguvannja_d_xor[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_XOR1) + i] =
                      current_settings.ranguvannja_d_xor[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_XOR1) + i];
                  }
                }
                else if((current_ekran.current_level >= EKRAN_RANGUVANNJA_D_NOT1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_NOT16))
                {
                  for (unsigned int i = 0; i < N_BIG; i++)
                  {
                    edition_settings.ranguvannja_d_not[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_NOT1) + i] =
                      current_settings.ranguvannja_d_not[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_NOT1) + i];
                  }
                }
                  
                //ϳ�������� �� ������ ����������� - �������� �������� ������
                int temp_current_level = current_ekran.current_level;
                current_ekran.cursor_on = 1;
                current_ekran.cursor_blinking_on = 1;
                if (current_settings.password1 != 0)
                {
                  //���������� �� ���� ������ ������
                  current_ekran.current_level = EKRAN_LEVEL_PASSWORD;
                  previous_level_in_current_level_menu[current_ekran.current_level] = temp_current_level;
                  current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
                }
                else
                {
                  //���������� � ����� �����������
                  current_ekran.edition = 1;
                }
              }
              else if (current_ekran.edition == 1)
              {
                //���������� �� ���� ���� ��������
                if((current_ekran.current_level >= EKRAN_RANGUVANNJA_INPUT_1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_INPUT_10))
                {
                  if (
                      (edition_settings.ranguvannja_inputs[N_SMALL*(current_ekran.current_level - EKRAN_RANGUVANNJA_INPUT_1)    ] == current_settings.ranguvannja_inputs[N_SMALL*(current_ekran.current_level - EKRAN_RANGUVANNJA_INPUT_1)    ]) &&
                      (edition_settings.ranguvannja_inputs[N_SMALL*(current_ekran.current_level - EKRAN_RANGUVANNJA_INPUT_1) + 1] == current_settings.ranguvannja_inputs[N_SMALL*(current_ekran.current_level - EKRAN_RANGUVANNJA_INPUT_1) + 1])
                     )   
                    current_ekran.edition = 0;
                  else current_ekran.edition = 2;
                }
                else if((current_ekran.current_level >= EKRAN_RANGUVANNJA_BUTTON_1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_BUTTON_6))
                {
                  if (edition_settings.ranguvannja_buttons[current_ekran.current_level - EKRAN_RANGUVANNJA_BUTTON_1] == 
                      current_settings.ranguvannja_buttons[current_ekran.current_level - EKRAN_RANGUVANNJA_BUTTON_1])
                    current_ekran.edition = 0;
                  else current_ekran.edition = 2;
                }
                else if((current_ekran.current_level >= EKRAN_RANGUVANNJA_OUTPUT_1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_OUTPUT_10))
                {
                  if (
                      (edition_settings.ranguvannja_outputs[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_OUTPUT_1)    ] == current_settings.ranguvannja_outputs[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_OUTPUT_1)    ]) &&
                      (edition_settings.ranguvannja_outputs[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_OUTPUT_1) + 1] == current_settings.ranguvannja_outputs[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_OUTPUT_1) + 1]) &&
                      (edition_settings.ranguvannja_outputs[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_OUTPUT_1) + 2] == current_settings.ranguvannja_outputs[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_OUTPUT_1) + 2]) &&
                      (edition_settings.ranguvannja_outputs[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_OUTPUT_1) + 3] == current_settings.ranguvannja_outputs[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_OUTPUT_1) + 3]) &&
                      (edition_settings.ranguvannja_outputs[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_OUTPUT_1) + 4] == current_settings.ranguvannja_outputs[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_OUTPUT_1) + 4]) &&
                      (edition_settings.ranguvannja_outputs[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_OUTPUT_1) + 5] == current_settings.ranguvannja_outputs[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_OUTPUT_1) + 5]) &&
                      (edition_settings.ranguvannja_outputs[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_OUTPUT_1) + 6] == current_settings.ranguvannja_outputs[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_OUTPUT_1) + 6])
                     )
                    current_ekran.edition = 0;
                  else current_ekran.edition = 2;
                }
                else if((current_ekran.current_level >= EKRAN_RANGUVANNJA_LED_1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_LED_8))
                {
                  if (
                      (edition_settings.ranguvannja_leds[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_LED_1)    ] == current_settings.ranguvannja_leds[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_LED_1)    ]) &&
                      (edition_settings.ranguvannja_leds[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_LED_1) + 1] == current_settings.ranguvannja_leds[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_LED_1) + 1]) &&
                      (edition_settings.ranguvannja_leds[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_LED_1) + 2] == current_settings.ranguvannja_leds[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_LED_1) + 2]) &&
                      (edition_settings.ranguvannja_leds[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_LED_1) + 3] == current_settings.ranguvannja_leds[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_LED_1) + 3]) &&
                      (edition_settings.ranguvannja_leds[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_LED_1) + 4] == current_settings.ranguvannja_leds[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_LED_1) + 4]) &&
                      (edition_settings.ranguvannja_leds[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_LED_1) + 5] == current_settings.ranguvannja_leds[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_LED_1) + 5]) &&
                      (edition_settings.ranguvannja_leds[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_LED_1) + 6] == current_settings.ranguvannja_leds[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_LED_1) + 6])
                     )
                    current_ekran.edition = 0;
                  else current_ekran.edition = 2;
                }
                else if(current_ekran.current_level == EKRAN_RANGUVANNJA_ANALOG_REGISTRATOR)
                {
                  if (
                      (edition_settings.ranguvannja_analog_registrator[0] == current_settings.ranguvannja_analog_registrator[0]) &&
                      (edition_settings.ranguvannja_analog_registrator[1] == current_settings.ranguvannja_analog_registrator[1]) &&
                      (edition_settings.ranguvannja_analog_registrator[2] == current_settings.ranguvannja_analog_registrator[2]) &&
                      (edition_settings.ranguvannja_analog_registrator[3] == current_settings.ranguvannja_analog_registrator[3]) &&
                      (edition_settings.ranguvannja_analog_registrator[4] == current_settings.ranguvannja_analog_registrator[4]) &&
                      (edition_settings.ranguvannja_analog_registrator[5] == current_settings.ranguvannja_analog_registrator[5]) &&
                      (edition_settings.ranguvannja_analog_registrator[6] == current_settings.ranguvannja_analog_registrator[6])
                     )
                    current_ekran.edition = 0;
                  else current_ekran.edition = 2;
                }
                else if(current_ekran.current_level == EKRAN_RANGUVANNJA_DIGITAL_REGISTRATOR)
                {
                  if (
                      (edition_settings.ranguvannja_digital_registrator[0] == current_settings.ranguvannja_digital_registrator[0]) &&
                      (edition_settings.ranguvannja_digital_registrator[1] == current_settings.ranguvannja_digital_registrator[1]) &&
                      (edition_settings.ranguvannja_digital_registrator[2] == current_settings.ranguvannja_digital_registrator[2]) &&
                      (edition_settings.ranguvannja_digital_registrator[3] == current_settings.ranguvannja_digital_registrator[3]) &&
                      (edition_settings.ranguvannja_digital_registrator[4] == current_settings.ranguvannja_digital_registrator[4]) &&
                      (edition_settings.ranguvannja_digital_registrator[5] == current_settings.ranguvannja_digital_registrator[5]) &&
                      (edition_settings.ranguvannja_digital_registrator[6] == current_settings.ranguvannja_digital_registrator[6])
                     )
                    current_ekran.edition = 0;
                  else current_ekran.edition = 2;
                }
                else if(current_ekran.current_level == EKRAN_RANGUVANNJA_OFF_CB)
                {
                  if (
                      (edition_settings.ranguvannja_off_cb[0] == current_settings.ranguvannja_off_cb[0]) &&
                      (edition_settings.ranguvannja_off_cb[1] == current_settings.ranguvannja_off_cb[1]) &&
                      (edition_settings.ranguvannja_off_cb[2] == current_settings.ranguvannja_off_cb[2]) &&
                      (edition_settings.ranguvannja_off_cb[3] == current_settings.ranguvannja_off_cb[3]) &&
                      (edition_settings.ranguvannja_off_cb[4] == current_settings.ranguvannja_off_cb[4]) &&
                      (edition_settings.ranguvannja_off_cb[5] == current_settings.ranguvannja_off_cb[5]) &&
                      (edition_settings.ranguvannja_off_cb[6] == current_settings.ranguvannja_off_cb[6])
                     )
                    current_ekran.edition = 0;
                  else current_ekran.edition = 2;
                }
                else if(current_ekran.current_level == EKRAN_RANGUVANNJA_ON_CB)
                {
                  if (
                      (edition_settings.ranguvannja_on_cb[0] == current_settings.ranguvannja_on_cb[0]) &&
                      (edition_settings.ranguvannja_on_cb[1] == current_settings.ranguvannja_on_cb[1]) &&
                      (edition_settings.ranguvannja_on_cb[2] == current_settings.ranguvannja_on_cb[2]) &&
                      (edition_settings.ranguvannja_on_cb[3] == current_settings.ranguvannja_on_cb[3]) &&
                      (edition_settings.ranguvannja_on_cb[4] == current_settings.ranguvannja_on_cb[4]) &&
                      (edition_settings.ranguvannja_on_cb[5] == current_settings.ranguvannja_on_cb[5]) &&
                      (edition_settings.ranguvannja_on_cb[6] == current_settings.ranguvannja_on_cb[6])
                     )
                    current_ekran.edition = 0;
                  else current_ekran.edition = 2;
                }
                else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_DF1_PLUS) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_DF8_BLK ))
                {
                  unsigned int index_in_ekran_list = current_ekran.current_level - EKRAN_RANGUVANNJA_DF1_PLUS;
                  unsigned int type_source = index_in_ekran_list % 3;
                  unsigned int index_of_df = index_in_ekran_list / 3;
    
                  if(type_source == 0)
                  {
                    if (
                        (edition_settings.ranguvannja_df_source_plus[N_BIG*index_of_df  ] == current_settings.ranguvannja_df_source_plus[N_BIG*index_of_df  ]) &&
                        (edition_settings.ranguvannja_df_source_plus[N_BIG*index_of_df+1] == current_settings.ranguvannja_df_source_plus[N_BIG*index_of_df+1]) &&
                        (edition_settings.ranguvannja_df_source_plus[N_BIG*index_of_df+2] == current_settings.ranguvannja_df_source_plus[N_BIG*index_of_df+2]) &&
                        (edition_settings.ranguvannja_df_source_plus[N_BIG*index_of_df+3] == current_settings.ranguvannja_df_source_plus[N_BIG*index_of_df+3]) &&
                        (edition_settings.ranguvannja_df_source_plus[N_BIG*index_of_df+4] == current_settings.ranguvannja_df_source_plus[N_BIG*index_of_df+4]) &&
                        (edition_settings.ranguvannja_df_source_plus[N_BIG*index_of_df+5] == current_settings.ranguvannja_df_source_plus[N_BIG*index_of_df+5]) &&
                        (edition_settings.ranguvannja_df_source_plus[N_BIG*index_of_df+6] == current_settings.ranguvannja_df_source_plus[N_BIG*index_of_df+6])
                       )
                      current_ekran.edition = 0;
                    else current_ekran.edition = 2;
                  }
                  else if(type_source == 1)
                  {
                    if (
                        (edition_settings.ranguvannja_df_source_minus[N_BIG*index_of_df  ] == current_settings.ranguvannja_df_source_minus[N_BIG*index_of_df  ]) &&
                        (edition_settings.ranguvannja_df_source_minus[N_BIG*index_of_df+1] == current_settings.ranguvannja_df_source_minus[N_BIG*index_of_df+1]) &&
                        (edition_settings.ranguvannja_df_source_minus[N_BIG*index_of_df+2] == current_settings.ranguvannja_df_source_minus[N_BIG*index_of_df+2]) &&
                        (edition_settings.ranguvannja_df_source_minus[N_BIG*index_of_df+3] == current_settings.ranguvannja_df_source_minus[N_BIG*index_of_df+3]) &&
                        (edition_settings.ranguvannja_df_source_minus[N_BIG*index_of_df+4] == current_settings.ranguvannja_df_source_minus[N_BIG*index_of_df+4]) &&
                        (edition_settings.ranguvannja_df_source_minus[N_BIG*index_of_df+5] == current_settings.ranguvannja_df_source_minus[N_BIG*index_of_df+5]) &&
                        (edition_settings.ranguvannja_df_source_minus[N_BIG*index_of_df+6] == current_settings.ranguvannja_df_source_minus[N_BIG*index_of_df+6])
                       )
                      current_ekran.edition = 0;
                    else current_ekran.edition = 2;
                  }
                  else
                  {
                    if (
                        (edition_settings.ranguvannja_df_source_blk[N_BIG*index_of_df  ] == current_settings.ranguvannja_df_source_blk[N_BIG*index_of_df  ]) &&
                        (edition_settings.ranguvannja_df_source_blk[N_BIG*index_of_df+1] == current_settings.ranguvannja_df_source_blk[N_BIG*index_of_df+1]) &&
                        (edition_settings.ranguvannja_df_source_blk[N_BIG*index_of_df+2] == current_settings.ranguvannja_df_source_blk[N_BIG*index_of_df+2]) &&
                        (edition_settings.ranguvannja_df_source_blk[N_BIG*index_of_df+3] == current_settings.ranguvannja_df_source_blk[N_BIG*index_of_df+3]) &&
                        (edition_settings.ranguvannja_df_source_blk[N_BIG*index_of_df+4] == current_settings.ranguvannja_df_source_blk[N_BIG*index_of_df+4]) &&
                        (edition_settings.ranguvannja_df_source_blk[N_BIG*index_of_df+5] == current_settings.ranguvannja_df_source_blk[N_BIG*index_of_df+5]) &&
                        (edition_settings.ranguvannja_df_source_blk[N_BIG*index_of_df+6] == current_settings.ranguvannja_df_source_blk[N_BIG*index_of_df+6])
                       )
                      current_ekran.edition = 0;
                    else current_ekran.edition = 2;
                  }
                }
                else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_SET_DT1_PLUS) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_RESET_DT4_MINUS))
                {
                  unsigned int index_in_ekran_list = current_ekran.current_level - EKRAN_RANGUVANNJA_SET_DT1_PLUS;
                  unsigned int type_source = index_in_ekran_list % 2;
                  unsigned int type_of_action = (index_in_ekran_list / 2) & 0x1;
                  unsigned int index_of_dt = index_in_ekran_list / 4;
    
                  if (type_of_action == INDEX_ML_SET_DT)
                  {
                    if(type_source == INDEX_ML_LIST_TYPE_SOURCE_PLUS_DT)
                    {
                      if (
                          (edition_settings.ranguvannja_set_dt_source_plus[N_BIG*index_of_dt  ] == current_settings.ranguvannja_set_dt_source_plus[N_BIG*index_of_dt  ]) &&
                          (edition_settings.ranguvannja_set_dt_source_plus[N_BIG*index_of_dt+1] == current_settings.ranguvannja_set_dt_source_plus[N_BIG*index_of_dt+1]) &&
                          (edition_settings.ranguvannja_set_dt_source_plus[N_BIG*index_of_dt+2] == current_settings.ranguvannja_set_dt_source_plus[N_BIG*index_of_dt+2]) &&
                          (edition_settings.ranguvannja_set_dt_source_plus[N_BIG*index_of_dt+3] == current_settings.ranguvannja_set_dt_source_plus[N_BIG*index_of_dt+3]) &&
                          (edition_settings.ranguvannja_set_dt_source_plus[N_BIG*index_of_dt+4] == current_settings.ranguvannja_set_dt_source_plus[N_BIG*index_of_dt+4]) &&
                          (edition_settings.ranguvannja_set_dt_source_plus[N_BIG*index_of_dt+5] == current_settings.ranguvannja_set_dt_source_plus[N_BIG*index_of_dt+5]) &&
                          (edition_settings.ranguvannja_set_dt_source_plus[N_BIG*index_of_dt+6] == current_settings.ranguvannja_set_dt_source_plus[N_BIG*index_of_dt+6])
                        )
                        current_ekran.edition = 0;
                      else current_ekran.edition = 2;
                    }
                    else
                    {
                      if (
                          (edition_settings.ranguvannja_set_dt_source_minus[N_BIG*index_of_dt  ] == current_settings.ranguvannja_set_dt_source_minus[N_BIG*index_of_dt  ]) &&
                          (edition_settings.ranguvannja_set_dt_source_minus[N_BIG*index_of_dt+1] == current_settings.ranguvannja_set_dt_source_minus[N_BIG*index_of_dt+1]) &&
                          (edition_settings.ranguvannja_set_dt_source_minus[N_BIG*index_of_dt+2] == current_settings.ranguvannja_set_dt_source_minus[N_BIG*index_of_dt+2]) &&
                          (edition_settings.ranguvannja_set_dt_source_minus[N_BIG*index_of_dt+3] == current_settings.ranguvannja_set_dt_source_minus[N_BIG*index_of_dt+3]) &&
                          (edition_settings.ranguvannja_set_dt_source_minus[N_BIG*index_of_dt+4] == current_settings.ranguvannja_set_dt_source_minus[N_BIG*index_of_dt+4]) &&
                          (edition_settings.ranguvannja_set_dt_source_minus[N_BIG*index_of_dt+5] == current_settings.ranguvannja_set_dt_source_minus[N_BIG*index_of_dt+5]) &&
                          (edition_settings.ranguvannja_set_dt_source_minus[N_BIG*index_of_dt+6] == current_settings.ranguvannja_set_dt_source_minus[N_BIG*index_of_dt+6])
                        )
                        current_ekran.edition = 0;
                      else current_ekran.edition = 2;
                    }
                  }
                  else
                  {
                    if(type_source == INDEX_ML_LIST_TYPE_SOURCE_PLUS_DT)
                    {
                      if (
                          (edition_settings.ranguvannja_reset_dt_source_plus[N_BIG*index_of_dt  ] == current_settings.ranguvannja_reset_dt_source_plus[N_BIG*index_of_dt  ]) &&
                          (edition_settings.ranguvannja_reset_dt_source_plus[N_BIG*index_of_dt+1] == current_settings.ranguvannja_reset_dt_source_plus[N_BIG*index_of_dt+1]) &&
                          (edition_settings.ranguvannja_reset_dt_source_plus[N_BIG*index_of_dt+2] == current_settings.ranguvannja_reset_dt_source_plus[N_BIG*index_of_dt+2]) &&
                          (edition_settings.ranguvannja_reset_dt_source_plus[N_BIG*index_of_dt+3] == current_settings.ranguvannja_reset_dt_source_plus[N_BIG*index_of_dt+3]) &&
                          (edition_settings.ranguvannja_reset_dt_source_plus[N_BIG*index_of_dt+4] == current_settings.ranguvannja_reset_dt_source_plus[N_BIG*index_of_dt+4]) &&
                          (edition_settings.ranguvannja_reset_dt_source_plus[N_BIG*index_of_dt+5] == current_settings.ranguvannja_reset_dt_source_plus[N_BIG*index_of_dt+5]) &&
                          (edition_settings.ranguvannja_reset_dt_source_plus[N_BIG*index_of_dt+6] == current_settings.ranguvannja_reset_dt_source_plus[N_BIG*index_of_dt+6])
                        )
                        current_ekran.edition = 0;
                      else current_ekran.edition = 2;
                    }
                    else
                    {
                      if (
                          (edition_settings.ranguvannja_reset_dt_source_minus[N_BIG*index_of_dt  ] == current_settings.ranguvannja_reset_dt_source_minus[N_BIG*index_of_dt  ]) &&
                          (edition_settings.ranguvannja_reset_dt_source_minus[N_BIG*index_of_dt+1] == current_settings.ranguvannja_reset_dt_source_minus[N_BIG*index_of_dt+1]) &&
                          (edition_settings.ranguvannja_reset_dt_source_minus[N_BIG*index_of_dt+2] == current_settings.ranguvannja_reset_dt_source_minus[N_BIG*index_of_dt+2]) &&
                          (edition_settings.ranguvannja_reset_dt_source_minus[N_BIG*index_of_dt+3] == current_settings.ranguvannja_reset_dt_source_minus[N_BIG*index_of_dt+3]) &&
                          (edition_settings.ranguvannja_reset_dt_source_minus[N_BIG*index_of_dt+4] == current_settings.ranguvannja_reset_dt_source_minus[N_BIG*index_of_dt+4]) &&
                          (edition_settings.ranguvannja_reset_dt_source_minus[N_BIG*index_of_dt+5] == current_settings.ranguvannja_reset_dt_source_minus[N_BIG*index_of_dt+5]) &&
                          (edition_settings.ranguvannja_reset_dt_source_minus[N_BIG*index_of_dt+6] == current_settings.ranguvannja_reset_dt_source_minus[N_BIG*index_of_dt+6])
                        )
                        current_ekran.edition = 0;
                      else current_ekran.edition = 2;
                    }
                  }
                }
                else if((current_ekran.current_level >= EKRAN_RANGUVANNJA_D_AND1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_AND8))
                {
                  if (
                      (edition_settings.ranguvannja_d_and[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_AND1)    ] == current_settings.ranguvannja_d_and[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_AND1)    ]) &&
                      (edition_settings.ranguvannja_d_and[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_AND1) + 1] == current_settings.ranguvannja_d_and[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_AND1) + 1]) &&
                      (edition_settings.ranguvannja_d_and[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_AND1) + 2] == current_settings.ranguvannja_d_and[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_AND1) + 2]) &&
                      (edition_settings.ranguvannja_d_and[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_AND1) + 3] == current_settings.ranguvannja_d_and[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_AND1) + 3]) &&
                      (edition_settings.ranguvannja_d_and[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_AND1) + 4] == current_settings.ranguvannja_d_and[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_AND1) + 4]) &&
                      (edition_settings.ranguvannja_d_and[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_AND1) + 5] == current_settings.ranguvannja_d_and[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_AND1) + 5]) &&
                      (edition_settings.ranguvannja_d_and[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_AND1) + 6] == current_settings.ranguvannja_d_and[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_AND1) + 6])
                     )
                    current_ekran.edition = 0;
                  else current_ekran.edition = 2;
                }
                else if((current_ekran.current_level >= EKRAN_RANGUVANNJA_D_OR1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_OR8))
                {
                  if (
                      (edition_settings.ranguvannja_d_or[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_OR1)    ] == current_settings.ranguvannja_d_or[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_OR1)    ]) &&
                      (edition_settings.ranguvannja_d_or[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_OR1) + 1] == current_settings.ranguvannja_d_or[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_OR1) + 1]) &&
                      (edition_settings.ranguvannja_d_or[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_OR1) + 2] == current_settings.ranguvannja_d_or[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_OR1) + 2]) &&
                      (edition_settings.ranguvannja_d_or[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_OR1) + 3] == current_settings.ranguvannja_d_or[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_OR1) + 3]) &&
                      (edition_settings.ranguvannja_d_or[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_OR1) + 4] == current_settings.ranguvannja_d_or[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_OR1) + 4]) &&
                      (edition_settings.ranguvannja_d_or[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_OR1) + 5] == current_settings.ranguvannja_d_or[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_OR1) + 5]) &&
                      (edition_settings.ranguvannja_d_or[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_OR1) + 6] == current_settings.ranguvannja_d_or[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_OR1) + 6])
                     )
                    current_ekran.edition = 0;
                  else current_ekran.edition = 2;
                }
                else if((current_ekran.current_level >= EKRAN_RANGUVANNJA_D_XOR1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_XOR8))
                {
                  if (
                      (edition_settings.ranguvannja_d_xor[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_XOR1)    ] == current_settings.ranguvannja_d_xor[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_XOR1)    ]) &&
                      (edition_settings.ranguvannja_d_xor[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_XOR1) + 1] == current_settings.ranguvannja_d_xor[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_XOR1) + 1]) &&
                      (edition_settings.ranguvannja_d_xor[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_XOR1) + 2] == current_settings.ranguvannja_d_xor[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_XOR1) + 2]) &&
                      (edition_settings.ranguvannja_d_xor[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_XOR1) + 3] == current_settings.ranguvannja_d_xor[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_XOR1) + 3]) &&
                      (edition_settings.ranguvannja_d_xor[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_XOR1) + 4] == current_settings.ranguvannja_d_xor[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_XOR1) + 4]) &&
                      (edition_settings.ranguvannja_d_xor[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_XOR1) + 5] == current_settings.ranguvannja_d_xor[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_XOR1) + 5]) &&
                      (edition_settings.ranguvannja_d_xor[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_XOR1) + 6] == current_settings.ranguvannja_d_xor[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_XOR1) + 6])
                     )
                    current_ekran.edition = 0;
                  else current_ekran.edition = 2;
                }
                else if((current_ekran.current_level >= EKRAN_RANGUVANNJA_D_NOT1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_NOT16))
                {
                  if (
                      (edition_settings.ranguvannja_d_not[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_NOT1)    ] == current_settings.ranguvannja_d_not[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_NOT1)    ]) &&
                      (edition_settings.ranguvannja_d_not[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_NOT1) + 1] == current_settings.ranguvannja_d_not[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_NOT1) + 1]) &&
                      (edition_settings.ranguvannja_d_not[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_NOT1) + 2] == current_settings.ranguvannja_d_not[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_NOT1) + 2]) &&
                      (edition_settings.ranguvannja_d_not[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_NOT1) + 3] == current_settings.ranguvannja_d_not[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_NOT1) + 3]) &&
                      (edition_settings.ranguvannja_d_not[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_NOT1) + 4] == current_settings.ranguvannja_d_not[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_NOT1) + 4]) &&
                      (edition_settings.ranguvannja_d_not[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_NOT1) + 5] == current_settings.ranguvannja_d_not[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_NOT1) + 5]) &&
                      (edition_settings.ranguvannja_d_not[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_NOT1) + 6] == current_settings.ranguvannja_d_not[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_NOT1) + 6])
                     )
                    current_ekran.edition = 0;
                  else current_ekran.edition = 2;
                }

                current_ekran.cursor_on = 0;
                current_ekran.cursor_blinking_on = 0;
              }
              else if (current_ekran.edition == 2)
              {
                //���������� ����������� �����������, �� ���� �� ���������
                current_ekran.edition = 3;
                //���������� ��������
                if((current_ekran.current_level >= EKRAN_RANGUVANNJA_INPUT_1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_INPUT_10))
                {
                  unsigned int* point = edition_settings.ranguvannja_inputs;
                  if (count_number_set_bit(
                                           (point + N_SMALL*(current_ekran.current_level - EKRAN_RANGUVANNJA_INPUT_1)),
                                           NUMBER_TOTAL_SIGNAL_FOR_RANG_INPUT
                                          ) <= MAX_FUNCTIONS_IN_INPUT)
                  {
                    //�������, �� ���� ��������� ����� ���� ������
                    changed_settings = CHANGED_ETAP_EXECUTION;

                    current_settings.ranguvannja_inputs[N_SMALL*(current_ekran.current_level - EKRAN_RANGUVANNJA_INPUT_1)] = 
                    edition_settings.ranguvannja_inputs[N_SMALL*(current_ekran.current_level - EKRAN_RANGUVANNJA_INPUT_1)];

                    current_settings.ranguvannja_inputs[N_SMALL*(current_ekran.current_level - EKRAN_RANGUVANNJA_INPUT_1)+1] = 
                    edition_settings.ranguvannja_inputs[N_SMALL*(current_ekran.current_level - EKRAN_RANGUVANNJA_INPUT_1)+1];

                    //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                    fix_change_settings(1, 1);
                    //�������� � ������ �����������
                    current_ekran.edition = 0;
                  }
                }
                else if((current_ekran.current_level >= EKRAN_RANGUVANNJA_BUTTON_1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_BUTTON_6))
                {
                  unsigned int* point = edition_settings.ranguvannja_buttons;
                  if (count_number_set_bit(
                                           (point + (current_ekran.current_level - EKRAN_RANGUVANNJA_BUTTON_1)),
                                           NUMBER_TOTAL_SIGNAL_FOR_RANG_BUTTON
                                          ) <= MAX_FUNCTIONS_IN_DB)
                  {
                    //�������, �� ���� ��������� ����� ���� ������
                    changed_settings = CHANGED_ETAP_EXECUTION;

                    current_settings.ranguvannja_buttons[current_ekran.current_level - EKRAN_RANGUVANNJA_BUTTON_1] = 
                    edition_settings.ranguvannja_buttons[current_ekran.current_level - EKRAN_RANGUVANNJA_BUTTON_1];
                    //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                    fix_change_settings(1, 1);
                    //�������� � ������ �����������
                    current_ekran.edition = 0;
                  }
                }
                else if((current_ekran.current_level >= EKRAN_RANGUVANNJA_OUTPUT_1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_OUTPUT_10))
                {
                  unsigned int* point = edition_settings.ranguvannja_outputs;
                  if (count_number_set_bit(
                                           (point + N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_OUTPUT_1)),
                                           NUMBER_TOTAL_SIGNAL_FOR_RANG
                                          ) <= MAX_FUNCTIONS_IN_OUTPUT)
                  {
                    //�������, �� ���� ��������� ����� ���� ������
                    changed_settings = CHANGED_ETAP_EXECUTION;

                    for (unsigned int i = 0; i < N_BIG; i++)
                    {
                      current_settings.ranguvannja_outputs[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_OUTPUT_1) + i] = 
                      edition_settings.ranguvannja_outputs[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_OUTPUT_1) + i];
                    }

                    //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                    fix_change_settings(1, 1);
                    //�������� � ������ �����������
                    current_ekran.edition = 0;
                  }
                }
                else if((current_ekran.current_level >= EKRAN_RANGUVANNJA_LED_1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_LED_8))
                {
                  unsigned int* point = edition_settings.ranguvannja_leds;
                  if (count_number_set_bit(
                                           (point + N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_LED_1)),
                                           NUMBER_TOTAL_SIGNAL_FOR_RANG
                                          ) <= MAX_FUNCTIONS_IN_LED)
                  {
                    //�������, �� ���� ��������� ����� ���� ������
                    changed_settings = CHANGED_ETAP_EXECUTION;

                    for (unsigned int i = 0; i < N_BIG; i++)
                    {
                      current_settings.ranguvannja_leds[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_LED_1) + i] = 
                      edition_settings.ranguvannja_leds[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_LED_1) + i];
                    }

                    //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                    fix_change_settings(1, 1);
                    //�������� � ������ �����������
                    current_ekran.edition = 0;
                  }
                }
                else if( current_ekran.current_level == EKRAN_RANGUVANNJA_ANALOG_REGISTRATOR)
                {
                  unsigned int* point = edition_settings.ranguvannja_analog_registrator;
                  if (count_number_set_bit(
                                           point,
                                           NUMBER_TOTAL_SIGNAL_FOR_RANG
                                          ) <= MAX_FUNCTIONS_IN_AREG)
                  {
                    //�������, �� ���� ��������� ����� ���� ������
                    changed_settings = CHANGED_ETAP_EXECUTION;

                    for (unsigned int i = 0; i < N_BIG; i++)
                    {
                      current_settings.ranguvannja_analog_registrator[i] = edition_settings.ranguvannja_analog_registrator[i];
                    }

                    //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                    fix_change_settings(1, 1);
                    //�������� � ������ �����������
                    current_ekran.edition = 0;
                  }
                }
                else if( current_ekran.current_level == EKRAN_RANGUVANNJA_DIGITAL_REGISTRATOR)
                {
                  unsigned int* point = edition_settings.ranguvannja_digital_registrator;
                  if (count_number_set_bit(
                                           point,
                                           NUMBER_TOTAL_SIGNAL_FOR_RANG
                                          ) <= MAX_FUNCTIONS_IN_DREG)
                  {
                    //�������, �� ���� ��������� ����� ���� ������
                    changed_settings = CHANGED_ETAP_EXECUTION;

                    for (unsigned int i = 0; i < N_BIG; i++)
                    {
                      current_settings.ranguvannja_digital_registrator[i] = edition_settings.ranguvannja_digital_registrator[i];
                    }

                    //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                    fix_change_settings(1, 1);
                    //�������� � ������ �����������
                    current_ekran.edition = 0;
                  }
                }
                else if( current_ekran.current_level == EKRAN_RANGUVANNJA_OFF_CB)
                {
                  unsigned int* point = edition_settings.ranguvannja_off_cb;
                  if (count_number_set_bit(
                                           point,
                                           NUMBER_TOTAL_SIGNAL_FOR_RANG
                                          ) <= MAX_FUNCTIONS_IN_OFF_CB)
                  {
                    //�������, �� ���� ��������� ����� ���� ������
                    changed_settings = CHANGED_ETAP_EXECUTION;

                    for (unsigned int i = 0; i < N_BIG; i++)
                    {
                      current_settings.ranguvannja_off_cb[i] = edition_settings.ranguvannja_off_cb[i];
                    }

                    //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                    fix_change_settings(1, 1);
                    //�������� � ������ �����������
                    current_ekran.edition = 0;
                  }
                }
                else if( current_ekran.current_level == EKRAN_RANGUVANNJA_ON_CB)
                {
                  unsigned int* point = edition_settings.ranguvannja_on_cb;
                  if (count_number_set_bit(
                                           point,
                                           NUMBER_TOTAL_SIGNAL_FOR_RANG
                                          ) <= MAX_FUNCTIONS_IN_ON_CB)
                  {
                    //�������, �� ���� ��������� ����� ���� ������
                    changed_settings = CHANGED_ETAP_EXECUTION;

                    for (unsigned int i = 0; i < N_BIG; i++)
                    {
                      current_settings.ranguvannja_on_cb[i] = edition_settings.ranguvannja_on_cb[i];
                    }

                    //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                    fix_change_settings(1, 1);
                    //�������� � ������ �����������
                    current_ekran.edition = 0;
                  }
                }
                else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_DF1_PLUS) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_DF8_BLK ))
                {
                  unsigned int index_in_ekran_list = current_ekran.current_level - EKRAN_RANGUVANNJA_DF1_PLUS;
                  unsigned int type_source = index_in_ekran_list % 3;
                  unsigned int index_of_df = index_in_ekran_list / 3;
    
                  unsigned int* point;
                  
                  if(type_source == 0)
                    point = edition_settings.ranguvannja_df_source_plus;
                  else if(type_source == 1)
                    point = edition_settings.ranguvannja_df_source_minus;
                  else 
                    point = edition_settings.ranguvannja_df_source_blk;

                  if (count_number_set_bit(
                                           (point + N_BIG*index_of_df),
                                           NUMBER_TOTAL_SIGNAL_FOR_RANG
                                          ) <= MAX_FUNCTIONS_IN_DF)
                  {
                    //�������, �� ���� ��������� ����� ���� ������
                    changed_settings = CHANGED_ETAP_EXECUTION;

                    if(type_source == 0)
                    {
                      for (unsigned int i = 0; i < N_BIG; i++)
                      {
                        current_settings.ranguvannja_df_source_plus[N_BIG*index_of_df + i] = edition_settings.ranguvannja_df_source_plus[N_BIG*index_of_df + i];
                      }
                    }
                    else if(type_source == 1)
                    {
                      for (unsigned int i = 0; i < N_BIG; i++)
                      {
                        current_settings.ranguvannja_df_source_minus[N_BIG*index_of_df + i] = edition_settings.ranguvannja_df_source_minus[N_BIG*index_of_df + i];
                      }
                    }
                    else
                    {
                      for (unsigned int i = 0; i < N_BIG; i++)
                      {
                        current_settings.ranguvannja_df_source_blk[N_BIG*index_of_df + i] = edition_settings.ranguvannja_df_source_blk[N_BIG*index_of_df + i];
                      }
                    }

                    //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                    fix_change_settings(1, 1);
                    //�������� � ������ �����������
                    current_ekran.edition = 0;
                  }
                }
                else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_SET_DT1_PLUS) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_RESET_DT4_MINUS))
                {
                  unsigned int index_in_ekran_list = current_ekran.current_level - EKRAN_RANGUVANNJA_SET_DT1_PLUS;
                  unsigned int type_source = index_in_ekran_list % 2;
                  unsigned int type_of_action = (index_in_ekran_list / 2) & 0x1;
                  unsigned int index_of_dt = index_in_ekran_list / 4;
    
                  unsigned int* point;
                  
                  if (type_of_action == INDEX_ML_SET_DT)
                  {
                    if(type_source == INDEX_ML_LIST_TYPE_SOURCE_PLUS_DT)
                      point = edition_settings.ranguvannja_set_dt_source_plus;
                    else
                      point = edition_settings.ranguvannja_set_dt_source_minus;
                  }
                  else
                  {
                    if(type_source == INDEX_ML_LIST_TYPE_SOURCE_PLUS_DT)
                      point = edition_settings.ranguvannja_reset_dt_source_plus;
                    else
                      point = edition_settings.ranguvannja_reset_dt_source_minus;
                  }

                  if (count_number_set_bit(
                                           (point + 3*index_of_dt),
                                           NUMBER_TOTAL_SIGNAL_FOR_RANG
                                          ) <= MAX_FUNCTIONS_IN_DT)
                  {
                    //�������, �� ���� ��������� ����� ���� ������
                    changed_settings = CHANGED_ETAP_EXECUTION;

                    if (type_of_action == INDEX_ML_SET_DT)
                    {
                      if(type_source == INDEX_ML_LIST_TYPE_SOURCE_PLUS_DT)
                      {
                        for (unsigned int i = 0; i < N_BIG; i++)
                        {
                          current_settings.ranguvannja_set_dt_source_plus[N_BIG*index_of_dt + i] = edition_settings.ranguvannja_set_dt_source_plus[N_BIG*index_of_dt + i];
                        }
                      }
                      else
                      {
                        for (unsigned int i = 0; i < N_BIG; i++)
                        {
                          current_settings.ranguvannja_set_dt_source_minus[N_BIG*index_of_dt + i] = edition_settings.ranguvannja_set_dt_source_minus[N_BIG*index_of_dt + i];
                        }
                      }
                    }
                    else
                    {
                      if(type_source == INDEX_ML_LIST_TYPE_SOURCE_PLUS_DT)
                      {
                        for (unsigned int i = 0; i < N_BIG; i++)
                        {
                          current_settings.ranguvannja_reset_dt_source_plus[N_BIG*index_of_dt + i] = edition_settings.ranguvannja_reset_dt_source_plus[N_BIG*index_of_dt + i];
                        }
                      }
                      else
                      {
                        for (unsigned int i = 0; i < N_BIG; i++)
                        {
                          current_settings.ranguvannja_reset_dt_source_minus[N_BIG*index_of_dt + i] = edition_settings.ranguvannja_reset_dt_source_minus[N_BIG*index_of_dt + i];
                        }
                      }
                    }

                    //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                    fix_change_settings(1, 1);
                    //�������� � ������ �����������
                    current_ekran.edition = 0;
                  }
                }
                else if((current_ekran.current_level >= EKRAN_RANGUVANNJA_D_AND1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_AND8))
                {
                  unsigned int* point = edition_settings.ranguvannja_d_and;
                  if (count_number_set_bit(
                                           (point + N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_AND1)),
                                           NUMBER_TOTAL_SIGNAL_FOR_RANG
                                          ) <= MAX_FUNCTIONS_IN_D_AND)
                  {
                    //�������, �� ���� ��������� ����� ���� ������
                    changed_settings = CHANGED_ETAP_EXECUTION;

                    for (unsigned int i = 0; i < N_BIG; i++)
                    {
                      current_settings.ranguvannja_d_and[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_AND1) + i] = 
                      edition_settings.ranguvannja_d_and[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_AND1) + i];
                    }

                    //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                    fix_change_settings(1, 1);
                    //�������� � ������ �����������
                    current_ekran.edition = 0;
                  }
                }
                else if((current_ekran.current_level >= EKRAN_RANGUVANNJA_D_OR1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_OR8))
                {
                  unsigned int* point = edition_settings.ranguvannja_d_or;
                  if (count_number_set_bit(
                                           (point + N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_OR1)),
                                           NUMBER_TOTAL_SIGNAL_FOR_RANG
                                          ) <= MAX_FUNCTIONS_IN_D_OR)
                  {
                    //�������, �� ���� ��������� ����� ���� ������
                    changed_settings = CHANGED_ETAP_EXECUTION;

                    for (unsigned int i = 0; i < N_BIG; i++)
                    {
                      current_settings.ranguvannja_d_or[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_OR1) + i] = 
                      edition_settings.ranguvannja_d_or[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_OR1) + i];
                    }

                    //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                    fix_change_settings(1, 1);
                    //�������� � ������ �����������
                    current_ekran.edition = 0;
                  }
                }
                else if((current_ekran.current_level >= EKRAN_RANGUVANNJA_D_XOR1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_XOR8))
                {
                  unsigned int* point = edition_settings.ranguvannja_d_xor;
                  if (count_number_set_bit(
                                           (point + N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_XOR1)),
                                           NUMBER_TOTAL_SIGNAL_FOR_RANG
                                          ) <= MAX_FUNCTIONS_IN_D_XOR)
                  {
                    //�������, �� ���� ��������� ����� ���� ������
                    changed_settings = CHANGED_ETAP_EXECUTION;

                    for (unsigned int i = 0; i < N_BIG; i++)
                    {
                      current_settings.ranguvannja_d_xor[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_XOR1) + i] = 
                      edition_settings.ranguvannja_d_xor[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_XOR1) + i];
                    }

                    //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                    fix_change_settings(1, 1);
                    //�������� � ������ �����������
                    current_ekran.edition = 0;
                  }
                }
                else if((current_ekran.current_level >= EKRAN_RANGUVANNJA_D_NOT1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_NOT16))
                {
                  unsigned int* point = edition_settings.ranguvannja_d_not;
                  if (count_number_set_bit(
                                           (point + N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_NOT1)),
                                           NUMBER_TOTAL_SIGNAL_FOR_RANG
                                          ) <= MAX_FUNCTIONS_IN_D_NOT)
                  {
                    //�������, �� ���� ��������� ����� ���� ������
                    changed_settings = CHANGED_ETAP_EXECUTION;

                    for (unsigned int i = 0; i < N_BIG; i++)
                    {
                      current_settings.ranguvannja_d_not[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_NOT1) + i] = 
                      edition_settings.ranguvannja_d_not[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_NOT1) + i];
                    }

                    //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
                    fix_change_settings(1, 1);
                    //�������� � ������ �����������
                    current_ekran.edition = 0;
                  }
                }
              }
              else if (current_ekran.edition == 3)
              {
                //����� � ����� �����������
                current_ekran.edition = 0;
              }
              
              if(current_ekran.edition == 2) make_ekran_ask_rewrite();
              else if(current_ekran.edition == 3)
              {
                const unsigned char information_about_error[MAX_NAMBER_LANGUAGE][MAX_COL_LCD] = 
                {
                  "����.����.���.�.",
                  "�����.����.��.�",
                  " Max.n.of F.Exc.",
                  "����.����.���.�."
                };
                make_ekran_about_error(information_about_error);
              }
              else
                //����������� �� ���������� ������
                new_state_keyboard |= (1<<BIT_REWRITE);

              //�������� �����������, �� ��������� ������ 
              new_state_keyboard &= (unsigned int)(~(1<<BIT_KEY_ENTER));
            }
            else if (new_state_keyboard == (1<<BIT_KEY_ESC))
            {
              if(current_ekran.edition == 0)
              {
                //����� � ����� ������������
                //���������� � ��������� ����
                current_ekran.current_level = previous_level_in_current_level_menu[current_ekran.current_level];
                current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
              }
              //������ ����������� � ����� ������������
              current_ekran.edition = 0;

              //����������� ������� �� ����������� ������ ������
              new_state_keyboard |= (1<<BIT_REWRITE);
              //�������� �����������, �� ��������� ������ 
              new_state_keyboard &= (unsigned int)(~(1<<BIT_KEY_ESC));
            }
            else if (new_state_keyboard == (1<<BIT_KEY_UP))
            {
              //��������� ������ UP
              if((current_ekran.current_level >= EKRAN_RANGUVANNJA_INPUT_1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_INPUT_10))
              {
                if(current_ekran.edition == 0)
                {
                  unsigned int temp_state[N_SMALL];
                  temp_state[0] = current_settings.ranguvannja_inputs[N_SMALL*(current_ekran.current_level - EKRAN_RANGUVANNJA_INPUT_1)    ];
                  temp_state[1] = current_settings.ranguvannja_inputs[N_SMALL*(current_ekran.current_level - EKRAN_RANGUVANNJA_INPUT_1) + 1];

                  if (
                      (temp_state[0] == 0) &&
                      (temp_state[1] == 0)
                     ) current_ekran.index_position = 0;
                  else
                  {
                    if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_RANGUVANNJA_INPUT - 1;
                    // (x>>5) ��������� �������� x / 32 - ���� ������� �� ������ �� 32
                    // (x & 0x1f) ��������� �������� x % 32 - ������ �� ������ �� 32
                    while ((temp_state[current_ekran.index_position >> 5] & (1<<(current_ekran.index_position  & 0x1f))) == 0)
                    {
                      current_ekran.index_position--;
                      if(current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_RANGUVANNJA_INPUT - 1;
                    }
                  }
                }
                else
                {
                  //�����������
                  unsigned int found_new_index = 0;
//                  int add_filter[0 + 1] = 
//                  {
//                    -1 /*������� ���������� ������*/
//                  };
//                  EL_FILTER_STRUCT el_filter[NUMBER_DEFINED_ELEMENTS] =
//                  {
//                    {1, RANG_INPUT_DF1_IN , RANG_INPUT_DF8_IN   , 1, current_settings.number_defined_df },
//                    {1, RANG_INPUT_DT1_SET, RANG_INPUT_DT4_RESET, 2, current_settings.number_defined_dt },
//                    {0, 0                 , 0                   , 1, current_settings.number_defined_and},
//                    {0, 0                 , 0                   , 1, current_settings.number_defined_or },
//                    {0, 0                 , 0                   , 1, current_settings.number_defined_xor},
//                    {0, 0                 , 0                   , 1, current_settings.number_defined_not}
//                  };
                
                  //����������� �� �������� �������
                  if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_RANGUVANNJA_INPUT - 1;
                  //����������, �� ����� ������ ������� ��������� � ����� ������������ 
                  while (found_new_index == 0)
                  {
                    check_current_index_is_presented_in_configuration(&found_new_index,
                                                                       /*add_filter,*/
                                                                       /*el_filter,*/
                                                                       0,
                                                                       NUMBER_GENERAL_SIGNAL_FOR_RANG_INPUT,
                                                                       NUMBER_CTRL_PHASE_SIGNAL_FOR_RANG_INPUT,
                                                                       NUMBER_EL_SIGNAL_FOR_RANG_INPUT
                                                                      );
                    //����������, �� �� �� ������ �� ��������� ������� �������
                    if(current_ekran.index_position < 0)
                    {
                      found_new_index = 0;
                      current_ekran.index_position = MAX_ROW_RANGUVANNJA_INPUT - 1;
                    }
                  }
                }
                position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;
                
                //������� ����� ����������� ����������� �������
                make_ekran_set_function_in_input(current_ekran.current_level);
              }
              else if((current_ekran.current_level >= EKRAN_RANGUVANNJA_BUTTON_1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_BUTTON_6))
              {
                if(current_ekran.edition == 0)
                {
                  unsigned int temp_state = current_settings.ranguvannja_buttons[current_ekran.current_level - EKRAN_RANGUVANNJA_BUTTON_1];
                  if (temp_state == 0) current_ekran.index_position = 0;
                  else
                  {
                    if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_RANGUVANNJA_BUTTON - 1;
                    while ((temp_state & (1<<current_ekran.index_position)) ==0)
                    {
                      current_ekran.index_position--;
                      if(current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_RANGUVANNJA_BUTTON - 1;
                    }
                  }
                }
                else
                {
                  //�����������
                  unsigned int found_new_index = 0;
//                  int add_filter[0 + 1] = 
//                  {
//                    -1 /*������� ���������� ������*/
//                  };
//                  EL_FILTER_STRUCT el_filter[NUMBER_DEFINED_ELEMENTS] =
//                  {
//                    {1, RANG_BUTTON_DF1_IN , RANG_BUTTON_DF8_IN   , 1, current_settings.number_defined_df },
//                    {1, RANG_BUTTON_DT1_SET, RANG_BUTTON_DT4_RESET, 2, current_settings.number_defined_dt },
//                    {0, 0                  , 0                    , 1, current_settings.number_defined_and},
//                    {0, 0                  , 0                    , 1, current_settings.number_defined_or },
//                    {0, 0                  , 0                    , 1, current_settings.number_defined_xor},
//                    {0, 0                  , 0                    , 1, current_settings.number_defined_not}
//                  };
                
                  //����������� �� �������� �������
                  if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_RANGUVANNJA_BUTTON - 1;
                  //����������, �� ����� ������ ������� ��������� � ����� ������������ 
                  while (found_new_index == 0)
                  {
                    check_current_index_is_presented_in_configuration(&found_new_index,
                                                                       /*add_filter,*/
                                                                       /*el_filter,*/
                                                                       0,
                                                                       NUMBER_GENERAL_SIGNAL_FOR_RANG_BUTTON,
                                                                       NUMBER_CTRL_PHASE_SIGNAL_FOR_RANG_BUTTON,
                                                                       NUMBER_EL_SIGNAL_FOR_RANG_BUTTON
                                                                      );
                    //����������, �� �� �� ������ �� ��������� ������� �������
                    if(current_ekran.index_position < 0)
                    {
                      found_new_index = 0;
                      current_ekran.index_position = MAX_ROW_RANGUVANNJA_BUTTON - 1;
                    }
                  }
                }
                position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;
                
                //������� ����� ����������� ����������� �������
                make_ekran_set_function_in_button(current_ekran.current_level);
              }
              else if(
                      ((current_ekran.current_level >= EKRAN_RANGUVANNJA_OUTPUT_1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_OUTPUT_10          )) ||
                      ((current_ekran.current_level >= EKRAN_RANGUVANNJA_LED_1   ) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_LED_8              )) ||
                      ( current_ekran.current_level == EKRAN_RANGUVANNJA_ANALOG_REGISTRATOR                                                                 ) ||
                      ( current_ekran.current_level == EKRAN_RANGUVANNJA_DIGITAL_REGISTRATOR                                                                ) ||
                      ( current_ekran.current_level == EKRAN_RANGUVANNJA_OFF_CB                                                                             ) ||
                      ( current_ekran.current_level == EKRAN_RANGUVANNJA_ON_CB                                                                              ) ||
                      ((current_ekran.current_level >= EKRAN_RANGUVANNJA_DF1_PLUS) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_DF8_BLK            )) ||
                      ((current_ekran.current_level >= EKRAN_RANGUVANNJA_SET_DT1_PLUS) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_RESET_DT4_MINUS)) ||
                      ((current_ekran.current_level >= EKRAN_RANGUVANNJA_D_AND1      ) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_AND8         )) ||
                      ((current_ekran.current_level >= EKRAN_RANGUVANNJA_D_OR1       ) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_OR8          )) ||
                      ((current_ekran.current_level >= EKRAN_RANGUVANNJA_D_XOR1      ) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_XOR8         )) ||
                      ((current_ekran.current_level >= EKRAN_RANGUVANNJA_D_NOT1      ) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_NOT16        ))
                     )
              {
                int max_row_ranguvannja;
                
                if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_OUTPUT_1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_OUTPUT_10))
                  max_row_ranguvannja = MAX_ROW_RANGUVANNJA_OUTPUT;
                else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_LED_1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_LED_8))
                  max_row_ranguvannja = MAX_ROW_RANGUVANNJA_LED;
                else if (current_ekran.current_level == EKRAN_RANGUVANNJA_ANALOG_REGISTRATOR)
                  max_row_ranguvannja = MAX_ROW_RANGUVANNJA_ANALOG_REGISTRATOR;
                else if (current_ekran.current_level == EKRAN_RANGUVANNJA_DIGITAL_REGISTRATOR)
                  max_row_ranguvannja = MAX_ROW_RANGUVANNJA_DIGITAL_REGISTRATOR;
                else if (current_ekran.current_level == EKRAN_RANGUVANNJA_OFF_CB)
                  max_row_ranguvannja = MAX_ROW_RANGUVANNJA_OFF_CB;
                else if (current_ekran.current_level == EKRAN_RANGUVANNJA_ON_CB)
                  max_row_ranguvannja = MAX_ROW_RANGUVANNJA_ON_CB;
                else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_DF1_PLUS) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_DF8_BLK ))
                  max_row_ranguvannja = MAX_ROW_RANGUVANNJA_DF;
                else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_SET_DT1_PLUS) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_RESET_DT4_MINUS))
                  max_row_ranguvannja = MAX_ROW_RANGUVANNJA_DT;
                else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_D_AND1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_AND8))
                  max_row_ranguvannja = MAX_ROW_RANGUVANNJA_D_AND;
                else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_D_OR1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_OR8))
                  max_row_ranguvannja = MAX_ROW_RANGUVANNJA_D_OR;
                else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_D_XOR1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_XOR8))
                  max_row_ranguvannja = MAX_ROW_RANGUVANNJA_D_XOR;
                else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_D_NOT1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_NOT16))
                  max_row_ranguvannja = MAX_ROW_RANGUVANNJA_D_NOT;

                if(current_ekran.edition == 0)
                {
                  unsigned int temp_state[N_BIG];
                  
                  if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_OUTPUT_1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_OUTPUT_10))
                  {
                    for (unsigned int i = 0; i < N_BIG; i++)
                    {
                      temp_state[i] = current_settings.ranguvannja_outputs[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_OUTPUT_1) + i];
                    }
                  }
                  else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_LED_1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_LED_8))
                  {
                    for (unsigned int i = 0; i < N_BIG; i++)
                    {
                      temp_state[i] = current_settings.ranguvannja_leds[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_LED_1) + i];
                    }
                  }
                  else if (current_ekran.current_level == EKRAN_RANGUVANNJA_ANALOG_REGISTRATOR)
                  {
                    for (unsigned int i = 0; i < N_BIG; i++)
                    {
                      temp_state[i] = current_settings.ranguvannja_analog_registrator[i];
                    }
                  }
                  else if (current_ekran.current_level == EKRAN_RANGUVANNJA_DIGITAL_REGISTRATOR)
                  {
                    for (unsigned int i = 0; i < N_BIG; i++)
                    {
                      temp_state[i] = current_settings.ranguvannja_digital_registrator[i];
                    }
                  }
                  else if (current_ekran.current_level == EKRAN_RANGUVANNJA_OFF_CB)
                  {
                    for (unsigned int i = 0; i < N_BIG; i++)
                    {
                      temp_state[i] = current_settings.ranguvannja_off_cb[i];
                    }
                  }
                  else if (current_ekran.current_level == EKRAN_RANGUVANNJA_ON_CB)
                  {
                    for (unsigned int i = 0; i < N_BIG; i++)
                    {
                      temp_state[i] = current_settings.ranguvannja_on_cb[i];
                    }
                  }
                  else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_DF1_PLUS) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_DF8_BLK ))
                  {
                    unsigned int index_in_ekran_list = current_ekran.current_level - EKRAN_RANGUVANNJA_DF1_PLUS;
                    unsigned int type_source = index_in_ekran_list % 3;
                    unsigned int index_of_df = index_in_ekran_list / 3;
    
                    if(type_source == 0)
                    {
                      for (unsigned int i = 0; i < N_BIG; i++)
                      {
                        temp_state[i] = current_settings.ranguvannja_df_source_plus[N_BIG*index_of_df + i];
                      }
                    }
                    else if(type_source == 1)
                    {
                      for (unsigned int i = 0; i < N_BIG; i++)
                      {
                        temp_state[i] = current_settings.ranguvannja_df_source_minus[N_BIG*index_of_df + i];
                      }
                    }
                    else
                    {
                      for (unsigned int i = 0; i < N_BIG; i++)
                      {
                        temp_state[i] = current_settings.ranguvannja_df_source_blk[N_BIG*index_of_df + i];
                      }
                    }
                  }
                  else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_SET_DT1_PLUS) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_RESET_DT4_MINUS))
                  {
                    unsigned int index_in_ekran_list = current_ekran.current_level - EKRAN_RANGUVANNJA_SET_DT1_PLUS;
                    unsigned int type_source = index_in_ekran_list % 2;
                    unsigned int type_of_action = (index_in_ekran_list / 2) & 0x1;
                    unsigned int index_of_dt = index_in_ekran_list / 4;
    
                    if (type_of_action == INDEX_ML_SET_DT)
                    {
                      if(type_source == INDEX_ML_LIST_TYPE_SOURCE_PLUS_DT)
                      {
                        for (unsigned int i = 0; i < N_BIG; i++)
                        {
                          temp_state[i] = current_settings.ranguvannja_set_dt_source_plus[N_BIG*index_of_dt + i];
                        }
                      }
                      else
                      {
                        for (unsigned int i = 0; i < N_BIG; i++)
                        {
                          temp_state[i] = current_settings.ranguvannja_set_dt_source_minus[N_BIG*index_of_dt + i];
                        }
                      }
                    }
                    else
                    {
                      if(type_source == INDEX_ML_LIST_TYPE_SOURCE_PLUS_DT)
                      {
                        for (unsigned int i = 0; i < N_BIG; i++)
                        {
                          temp_state[i] = current_settings.ranguvannja_reset_dt_source_plus[N_BIG*index_of_dt + i];
                        }
                      }
                      else
                      {
                        for (unsigned int i = 0; i < N_BIG; i++)
                        {
                          temp_state[i] = current_settings.ranguvannja_reset_dt_source_minus[N_BIG*index_of_dt + i];
                        }
                      }
                    }
                  }
                  else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_D_AND1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_AND8))
                  {
                    for (unsigned int i = 0; i < N_BIG; i++)
                    {
                      temp_state[i] = current_settings.ranguvannja_d_and[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_AND1) + i];
                    }
                  }
                  else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_D_OR1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_OR8))
                  {
                    for (unsigned int i = 0; i < N_BIG; i++)
                    {
                      temp_state[i] = current_settings.ranguvannja_d_or[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_OR1) + i];
                    }
                  }
                  else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_D_XOR1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_XOR8))
                  {
                    for (unsigned int i = 0; i < N_BIG; i++)
                    {
                      temp_state[i] = current_settings.ranguvannja_d_xor[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_XOR1) + i];
                    }
                  }
                  else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_D_NOT1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_NOT16))
                  {
                    for (unsigned int i = 0; i < N_BIG; i++)
                    {
                      temp_state[i] = current_settings.ranguvannja_d_not[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_NOT1) + i];
                    }
                  }
                  
                  if (
                      (temp_state[0] == 0) && 
                      (temp_state[1] == 0) &&
                      (temp_state[2] == 0) &&
                      (temp_state[3] == 0) &&
                      (temp_state[4] == 0) &&
                      (temp_state[5] == 0) &&
                      (temp_state[6] == 0)
                     ) current_ekran.index_position = 0;
                  else
                  {
                    if(--current_ekran.index_position < 0) current_ekran.index_position = max_row_ranguvannja - 1;
                    // (x>>5) ��������� �������� x / 32 - ���� ������� �� ������ �� 32
                    // (x & 0x1f) ��������� �������� x % 32 - ������ �� ������ �� 32
                    while ((temp_state[current_ekran.index_position >> 5] & (1<<(current_ekran.index_position  & 0x1f))) == 0)
                    {
                      current_ekran.index_position--;
                      if(current_ekran.index_position < 0) current_ekran.index_position = max_row_ranguvannja - 1;
                    }
                  }
                }
                else
                {
                  //�����������
                  unsigned int found_new_index = 0;
//                  int add_filter[3 + 1] = 
//                  {
//                    RANG_PO_NZZ,
//                    RANG_NZZ,
//                    RANG_SECTOR_NZZ,
//                    -1 /*������� ���������� ������*/
//                  };
//                  EL_FILTER_STRUCT el_filter[NUMBER_DEFINED_ELEMENTS] =
//                  {
//                    {1, RANG_DF1_IN , RANG_DF8_OUT, 2, current_settings.number_defined_df },
//                    {1, RANG_DT1_SET, RANG_DT4_OUT, 3, current_settings.number_defined_dt },
//                    {1, RANG_D_AND1 , RANG_D_AND8 , 1, current_settings.number_defined_and},
//                    {1, RANG_D_OR1  , RANG_D_OR8  , 1, current_settings.number_defined_or },
//                    {1, RANG_D_XOR1 , RANG_D_XOR8 , 1, current_settings.number_defined_xor},
//                    {1, RANG_D_NOT1 , RANG_D_NOT16, 1, current_settings.number_defined_not}
//                  };
                  
                  //����������� �� �������� �������
                  if(--current_ekran.index_position < 0) current_ekran.index_position = max_row_ranguvannja - 1;
                  //����������, �� ����� ������ ������� ��������� � ����� ������������ 
                  while (found_new_index == 0)
                  {
                    check_current_index_is_presented_in_configuration(&found_new_index,
                                                                       /*add_filter,*/
                                                                       /*el_filter,*/
                                                                       0,
                                                                       NUMBER_GENERAL_SIGNAL_FOR_RANG,
                                                                       NUMBER_CTRL_PHASE_SIGNAL_FOR_RANG,
                                                                       NUMBER_EL_SIGNAL_FOR_RANG
                                                                      );
                    //����������, �� �� ��  �� ������ ������� �� ������ ���������, ��� ����� �������� ��� ������ ���� ����������
                    if (
                        ( current_ekran.current_level == EKRAN_RANGUVANNJA_ANALOG_REGISTRATOR ) || 
                        ( current_ekran.current_level == EKRAN_RANGUVANNJA_DIGITAL_REGISTRATOR) ||
                        ( current_ekran.current_level == EKRAN_RANGUVANNJA_OFF_CB             ) || 
                        ( current_ekran.current_level == EKRAN_RANGUVANNJA_ON_CB              )  
                       )   
                    {
                      unsigned int index_deleted_function;
                      
                      if (current_ekran.current_level == EKRAN_RANGUVANNJA_ANALOG_REGISTRATOR)
                        index_deleted_function = RANG_WORK_A_REJESTRATOR;
                      else if (current_ekran.current_level == EKRAN_RANGUVANNJA_DIGITAL_REGISTRATOR)
                        index_deleted_function = RANG_WORK_D_REJESTRATOR;
                      else if (current_ekran.current_level == EKRAN_RANGUVANNJA_OFF_CB)
                        index_deleted_function = RANG_WORK_BO;
                      else if (current_ekran.current_level == EKRAN_RANGUVANNJA_ON_CB)
                        index_deleted_function = RANG_WORK_BV;
                    
                      if(index_deleted_function == current_ekran.index_position)
                      {
                        found_new_index = 0;
                        current_ekran.index_position--;
                      }
                    }
                    else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_DF1_PLUS) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_DF8_BLK))
                    {
                      unsigned int index_in_ekran_list = current_ekran.current_level - EKRAN_RANGUVANNJA_DF1_PLUS;
                      unsigned int index_of_df = index_in_ekran_list / 3;

                      for (unsigned int i = 0; i < 2; i++)
                      {
                        unsigned int index_deleted_function;
                        //������ ���������� ������� � ������ �������, ��� �� ���� �������� ����� ����� ���� ������������ �� �������, ��� ����� ���������
                        if (i == 0)
                        {
                          if(index_of_df == 0)
                            index_deleted_function = (RANG_DF1_OUT > RANG_DF1_IN) ? RANG_DF1_OUT : RANG_DF1_IN;
                          else if(index_of_df == 1)
                            index_deleted_function = (RANG_DF2_OUT > RANG_DF2_IN) ? RANG_DF2_OUT : RANG_DF2_IN;
                          else if(index_of_df == 2)
                            index_deleted_function = (RANG_DF3_OUT > RANG_DF3_IN) ? RANG_DF3_OUT : RANG_DF3_IN;
                          else if(index_of_df == 3)
                            index_deleted_function = (RANG_DF4_OUT > RANG_DF4_IN) ? RANG_DF4_OUT : RANG_DF4_IN;
                          else if(index_of_df == 4)
                            index_deleted_function = (RANG_DF5_OUT > RANG_DF5_IN) ? RANG_DF5_OUT : RANG_DF5_IN;
                          else if(index_of_df == 5)
                            index_deleted_function = (RANG_DF6_OUT > RANG_DF6_IN) ? RANG_DF6_OUT : RANG_DF6_IN;
                          else if(index_of_df == 6)
                            index_deleted_function = (RANG_DF7_OUT > RANG_DF7_IN) ? RANG_DF7_OUT : RANG_DF7_IN;
                          else
                            index_deleted_function = (RANG_DF8_OUT > RANG_DF8_IN) ? RANG_DF8_OUT : RANG_DF8_IN;
                        }
                        else
                        {
                          if(index_of_df == 0)
                            index_deleted_function = (RANG_DF1_OUT > RANG_DF1_IN) ? RANG_DF1_IN : RANG_DF1_OUT;
                          else if(index_of_df == 1)
                            index_deleted_function = (RANG_DF2_OUT > RANG_DF2_IN) ? RANG_DF2_IN : RANG_DF2_OUT;
                          else if(index_of_df == 2)
                            index_deleted_function = (RANG_DF3_OUT > RANG_DF3_IN) ? RANG_DF3_IN : RANG_DF3_OUT;
                          else if(index_of_df == 3)
                            index_deleted_function = (RANG_DF4_OUT > RANG_DF4_IN) ? RANG_DF4_IN : RANG_DF4_OUT;
                          else if(index_of_df == 4)
                            index_deleted_function = (RANG_DF5_OUT > RANG_DF5_IN) ? RANG_DF5_IN : RANG_DF5_OUT;
                          else if(index_of_df == 5)
                            index_deleted_function = (RANG_DF6_OUT > RANG_DF6_IN) ? RANG_DF6_IN : RANG_DF6_OUT;
                          else if(index_of_df == 6)
                            index_deleted_function = (RANG_DF7_OUT > RANG_DF7_IN) ? RANG_DF7_IN : RANG_DF7_OUT;
                          else
                            index_deleted_function = (RANG_DF8_OUT > RANG_DF8_IN) ? RANG_DF8_IN : RANG_DF8_OUT;
                        }
                    
                        if(index_deleted_function == current_ekran.index_position)
                        {
                          found_new_index = 0;
                          current_ekran.index_position--;
                        }
                      }
                    }
                    else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_SET_DT1_PLUS) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_RESET_DT4_MINUS))
                    {
                      unsigned int index_in_ekran_list = current_ekran.current_level - EKRAN_RANGUVANNJA_SET_DT1_PLUS;
                      unsigned int index_of_dt = index_in_ekran_list / 4;

                      for (unsigned int i = 0; i < 3; i++)
                      {
                        unsigned int index_deleted_function;
                        //������ ���������� ������� � ������ �������, ��� �� ���� �������� �����  ����� ���� ������������ �� �������, ��� ����� ���������
                        if (i == 0)
                        {
                          if(index_of_dt == 0)
                            index_deleted_function = RANG_DT1_OUT;
                          else if(index_of_dt == 1)
                            index_deleted_function = RANG_DT2_OUT;
                          else if(index_of_dt == 2)
                            index_deleted_function = RANG_DT3_OUT;
                          else if(index_of_dt == 3)
                            index_deleted_function = RANG_DT4_OUT;
                        }
                        else if (i == 1)
                        {
                          if(index_of_dt == 0)
                            index_deleted_function = RANG_DT1_RESET;
                          else if(index_of_dt == 1)
                            index_deleted_function = RANG_DT2_RESET;
                          else if(index_of_dt == 2)
                            index_deleted_function = RANG_DT3_RESET;
                          else if(index_of_dt == 3)
                            index_deleted_function = RANG_DT4_RESET;
                        }
                        else
                        {
                          if(index_of_dt == 0)
                            index_deleted_function = RANG_DT1_SET;
                          else if(index_of_dt == 1)
                            index_deleted_function = RANG_DT2_SET;
                          else if(index_of_dt == 2)
                            index_deleted_function = RANG_DT3_SET;
                          else if(index_of_dt == 3)
                            index_deleted_function = RANG_DT4_SET;
                        }
                    
                        if(index_deleted_function == current_ekran.index_position)
                        {
                          found_new_index = 0;
                          current_ekran.index_position--;
                        }
                      }
                    }
                    else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_D_AND1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_AND8))
                    {
                      unsigned int index_of_d_and = current_ekran.current_level - EKRAN_RANGUVANNJA_D_AND1;

                      //������ ���������� ������� � ������ �������, ��� �� ���� �������� �����  ����� ���� ������������ �� �������, ��� ����� ���������
                      unsigned int index_deleted_function = RANG_D_AND1 + index_of_d_and;
                    
                      if(index_deleted_function == current_ekran.index_position)
                      {
                        found_new_index = 0;
                        current_ekran.index_position--;
                      }
                    }
                    else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_D_OR1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_OR8))
                    {
                      unsigned int index_of_d_or = current_ekran.current_level - EKRAN_RANGUVANNJA_D_OR1;

                      //������ ���������� ������� � ������ �������, ��� �� ���� �������� �����  ����� ���� ������������ �� �������, ��� ����� ���������
                      unsigned int index_deleted_function = RANG_D_OR1 + index_of_d_or;
                    
                      if(index_deleted_function == current_ekran.index_position)
                      {
                        found_new_index = 0;
                        current_ekran.index_position--;
                      }
                    }
                    else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_D_XOR1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_XOR8))
                    {
                      unsigned int index_of_d_xor = current_ekran.current_level - EKRAN_RANGUVANNJA_D_XOR1;

                      //������ ���������� ������� � ������ �������, ��� �� ���� �������� �����  ����� ���� ������������ �� �������, ��� ����� ���������
                      unsigned int index_deleted_function = RANG_D_XOR1 + index_of_d_xor;
                    
                      if(index_deleted_function == current_ekran.index_position)
                      {
                        found_new_index = 0;
                        current_ekran.index_position--;
                      }
                    }
                    else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_D_NOT1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_NOT16))
                    {
                      unsigned int index_of_d_not = current_ekran.current_level - EKRAN_RANGUVANNJA_D_NOT1;

                      //������ ���������� ������� � ������ �������, ��� �� ���� �������� �����  ����� ���� ������������ �� �������, ��� ����� ���������
                      unsigned int index_deleted_function = RANG_D_NOT1 + index_of_d_not;
                    
                      if(index_deleted_function == current_ekran.index_position)
                      {
                        found_new_index = 0;
                        current_ekran.index_position--;
                      }
                    }
//                    else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_OUTPUT_1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_OUTPUT_10))
//                    {
//                      unsigned int current_number_output = current_ekran.current_level - EKRAN_RANGUVANNJA_OUTPUT_1;
//                      
//                      for (unsigned int i = 0; i < 2; i++)
//                      {
//                        unsigned int index_deleted_function;
//                        unsigned int maska_func[N_BIG] = {0, 0, 0, 0, 0, 0, 0, 0};
//                        unsigned int need_filtration = 0;
//                        //��������� ������ �������, ��� ���������� ������� ����� ���� ����������� �� �������
//                        //������ ���������� ������� � ������ �������, ��� �� ���� �������� ����� ����� ���� ������������ �� �������, ��� ����� ���������
//                        if (i == 0)
//                        {
//                          index_deleted_function = (RANG_WORK_BV > RANG_WORK_BO) ? RANG_WORK_BV : RANG_WORK_BO;
//                        }
//                        else
//                        {
//                          index_deleted_function = (RANG_WORK_BV > RANG_WORK_BO) ? RANG_WORK_BO : RANG_WORK_BV;
//                        }
//        
//                        //������� �����  ��� ���� �������
//                        _SET_BIT(maska_func, index_deleted_function);
//        
//                        unsigned int index = 0;
//                        while ((need_filtration == 0) && (index < NUMBER_OUTPUTS))
//                        {
//                          //���������� ������� ����� ������, �� �� ����� ���� ������� �� ������������ �� ��� �����������
//                          if (index != current_number_output)
//                          {
//                            if (
//                                ((current_settings.ranguvannja_outputs[N_BIG*index    ] & maska_func[0]) != 0) ||
//                                ((current_settings.ranguvannja_outputs[N_BIG*index + 1] & maska_func[1]) != 0) ||
//                                ((current_settings.ranguvannja_outputs[N_BIG*index + 2] & maska_func[2]) != 0) ||
//                                ((current_settings.ranguvannja_outputs[N_BIG*index + 3] & maska_func[3]) != 0) ||
//                                ((current_settings.ranguvannja_outputs[N_BIG*index + 4] & maska_func[4]) != 0) ||
//                                ((current_settings.ranguvannja_outputs[N_BIG*index + 5] & maska_func[5]) != 0) ||
//                                ((current_settings.ranguvannja_outputs[N_BIG*index + 6] & maska_func[6]) != 0) ||
//                                ((current_settings.ranguvannja_outputs[N_BIG*index + 7] & maska_func[7]) != 0)
//                               )
//                            {
//                              need_filtration = 1;
//                            }
//                          }
//                          index++;
//                        }
//                        
//                        //� �������, ���� ������������ � ��������, ���� ����� ����������� �������
//                        if (need_filtration != 0)
//                        {
//                          if(index_deleted_function == current_ekran.index_position)
//                          {
//                            found_new_index = 0;
//                            current_ekran.index_position--;
//                          }
//                        }
//                      }
//                    }
                    
                    //����������, �� �� �� ������ �� ��������� ������� �������
                    if(current_ekran.index_position < 0)
                    {
                      found_new_index = 0;
                      current_ekran.index_position = max_row_ranguvannja - 1;
                    }
                  }
                }
                position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;
                
                //������� ����� ����������� ����������� �������
                if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_OUTPUT_1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_OUTPUT_10))
                  make_ekran_set_function_in_output_led_df_dt_reg(current_ekran.current_level, INDEX_VIEWING_OUTPUT);
                else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_LED_1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_LED_8))
                  make_ekran_set_function_in_output_led_df_dt_reg(current_ekran.current_level, INDEX_VIEWING_LED);
                else if (current_ekran.current_level == EKRAN_RANGUVANNJA_ANALOG_REGISTRATOR)
                  make_ekran_set_function_in_output_led_df_dt_reg(current_ekran.current_level, INDEX_VIEWING_A_REG);
                else if (current_ekran.current_level == EKRAN_RANGUVANNJA_DIGITAL_REGISTRATOR)
                  make_ekran_set_function_in_output_led_df_dt_reg(current_ekran.current_level, INDEX_VIEWING_D_REG);
                else if (current_ekran.current_level == EKRAN_RANGUVANNJA_OFF_CB)
                  make_ekran_set_function_in_output_led_df_dt_reg(current_ekran.current_level, INDEX_VIEWING_OFF_CB);
                else if (current_ekran.current_level == EKRAN_RANGUVANNJA_ON_CB)
                  make_ekran_set_function_in_output_led_df_dt_reg(current_ekran.current_level, INDEX_VIEWING_ON_CB);
                else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_DF1_PLUS) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_DF8_BLK ))
                  make_ekran_set_function_in_output_led_df_dt_reg(current_ekran.current_level, INDEX_VIEWING_DF);
                else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_SET_DT1_PLUS) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_RESET_DT4_MINUS))
                  make_ekran_set_function_in_output_led_df_dt_reg(current_ekran.current_level, INDEX_VIEWING_DT);
                else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_D_AND1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_AND8))
                  make_ekran_set_function_in_output_led_df_dt_reg(current_ekran.current_level, INDEX_VIEWING_D_AND);
                else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_D_OR1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_OR8))
                  make_ekran_set_function_in_output_led_df_dt_reg(current_ekran.current_level, INDEX_VIEWING_D_OR);
                else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_D_XOR1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_XOR8))
                  make_ekran_set_function_in_output_led_df_dt_reg(current_ekran.current_level, INDEX_VIEWING_D_XOR);
                else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_D_NOT1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_NOT16))
                  make_ekran_set_function_in_output_led_df_dt_reg(current_ekran.current_level, INDEX_VIEWING_D_NOT);
              }
              
              //�������� �����������, �� ��������� ������ 
              new_state_keyboard &= (unsigned int)(~(1<<BIT_KEY_UP));
            }
            else if (new_state_keyboard == (1<<BIT_KEY_DOWN))
            {
              //��������� ������ DOWN
              if((current_ekran.current_level >= EKRAN_RANGUVANNJA_INPUT_1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_INPUT_10))
              {
                if(current_ekran.edition == 0)
                {
                  unsigned int temp_state[N_SMALL];
                  temp_state[0] = current_settings.ranguvannja_inputs[N_SMALL*(current_ekran.current_level - EKRAN_RANGUVANNJA_INPUT_1)    ];
                  temp_state[1] = current_settings.ranguvannja_inputs[N_SMALL*(current_ekran.current_level - EKRAN_RANGUVANNJA_INPUT_1) + 1];

                  if (
                      (temp_state[0] == 0) &&
                      (temp_state[1] == 0)
                     ) current_ekran.index_position = 0;
                  else
                  {
                    if(++current_ekran.index_position >= MAX_ROW_RANGUVANNJA_INPUT) current_ekran.index_position = 0;
                    // (x>>5) ��������� �������� x / 32 - ���� ������� �� ������ �� 32
                    // (x & 0x1f) ��������� �������� x % 32 - ������ �� ������ �� 32
                    while ((temp_state[current_ekran.index_position >> 5] & (1<<(current_ekran.index_position  & 0x1f))) ==0)
                    {
                      current_ekran.index_position++;
                      if(current_ekran.index_position >= MAX_ROW_RANGUVANNJA_INPUT) current_ekran.index_position = 0;
                    }
                  }
                }
                else
                {
                  //�����������
                  unsigned int found_new_index = 0;
//                  int add_filter[0 + 1] = 
//                  {
//                    -1 /*������� ���������� ������*/
//                  };
//                  EL_FILTER_STRUCT el_filter[NUMBER_DEFINED_ELEMENTS] =
//                  {
//                    {1, RANG_INPUT_DF1_IN , RANG_INPUT_DF8_IN   , 1, current_settings.number_defined_df },
//                    {1, RANG_INPUT_DT1_SET, RANG_INPUT_DT4_RESET, 2, current_settings.number_defined_dt },
//                    {0, 0                 , 0                   , 1, current_settings.number_defined_and},
//                    {0, 0                 , 0                   , 1, current_settings.number_defined_or },
//                    {0, 0                 , 0                   , 1, current_settings.number_defined_xor},
//                    {0, 0                 , 0                   , 1, current_settings.number_defined_not}
//                  };
                  
                  //����������� �� �������� �������
                  if(++current_ekran.index_position >= MAX_ROW_RANGUVANNJA_INPUT) current_ekran.index_position = 0;
                  //����������, �� ����� ������ ������� ��������� � ����� ������������ 
                  while (found_new_index == 0)
                  {
                    check_current_index_is_presented_in_configuration(&found_new_index,
                                                                       /*add_filter,*/
                                                                       /*el_filter,*/
                                                                       1,
                                                                       NUMBER_GENERAL_SIGNAL_FOR_RANG_INPUT,
                                                                       NUMBER_CTRL_PHASE_SIGNAL_FOR_RANG_INPUT,
                                                                       NUMBER_EL_SIGNAL_FOR_RANG_INPUT
                                                                      );
                      //����������, �� �� �� ������ �� ��������� ������� �������
                      if(current_ekran.index_position >= MAX_ROW_RANGUVANNJA_INPUT)
                      {
                        found_new_index = 0;
                        current_ekran.index_position = 0;
                      }
                  }
                }
                position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;
                
                //������� ����� ����������� ����������� �������
                make_ekran_set_function_in_input(current_ekran.current_level);
              }
              else if((current_ekran.current_level >= EKRAN_RANGUVANNJA_BUTTON_1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_BUTTON_6))
              {
                if(current_ekran.edition == 0)
                {
                  unsigned int temp_state = current_settings.ranguvannja_buttons[current_ekran.current_level - EKRAN_RANGUVANNJA_BUTTON_1];
                  if (temp_state == 0) current_ekran.index_position = 0;
                  else
                  {
                    if(++current_ekran.index_position >= MAX_ROW_RANGUVANNJA_BUTTON) current_ekran.index_position = 0;
                    while ((temp_state & (1<<current_ekran.index_position)) ==0)
                    {
                      current_ekran.index_position++;
                      if(current_ekran.index_position >= MAX_ROW_RANGUVANNJA_BUTTON) current_ekran.index_position = 0;
                    }
                  }
                }
                else
                {
                  //�����������
                  unsigned int found_new_index = 0;
//                  int add_filter[0 + 1] = 
//                  {
//                    -1 /*������� ���������� ������*/
//                  };
//                  EL_FILTER_STRUCT el_filter[NUMBER_DEFINED_ELEMENTS] =
//                  {
//                    {1, RANG_BUTTON_DF1_IN , RANG_BUTTON_DF8_IN   , 1, current_settings.number_defined_df },
//                    {1, RANG_BUTTON_DT1_SET, RANG_BUTTON_DT4_RESET, 2, current_settings.number_defined_dt },
//                    {0, 0                  , 0                    , 1, current_settings.number_defined_and},
//                    {0, 0                  , 0                    , 1, current_settings.number_defined_or },
//                    {0, 0                  , 0                    , 1, current_settings.number_defined_xor},
//                    {0, 0                  , 0                    , 1, current_settings.number_defined_not}
//                  };
                
                  //����������� �� �������� �������
                  if(++current_ekran.index_position >= MAX_ROW_RANGUVANNJA_BUTTON) current_ekran.index_position = 0;
                  //����������, �� ����� ������ ������� ��������� � ����� ������������ 
                  while (found_new_index == 0)
                  {
                    check_current_index_is_presented_in_configuration(&found_new_index,
                                                                       /*add_filter,*/
                                                                       /*el_filter,*/
                                                                       1,
                                                                       NUMBER_GENERAL_SIGNAL_FOR_RANG_BUTTON,
                                                                       NUMBER_CTRL_PHASE_SIGNAL_FOR_RANG_BUTTON,
                                                                       NUMBER_EL_SIGNAL_FOR_RANG_BUTTON
                                                                      );
                      //����������, �� �� �� ������ �� ��������� ������� �������
                      if(current_ekran.index_position >= MAX_ROW_RANGUVANNJA_BUTTON)
                      {
                        found_new_index = 0;
                        current_ekran.index_position = 0;
                      }
                  }
                }
                position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;
                
                //������� ����� ����������� ����������� �������
                make_ekran_set_function_in_button(current_ekran.current_level);
              }
              else if(
                      ((current_ekran.current_level >= EKRAN_RANGUVANNJA_OUTPUT_1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_OUTPUT_10          )) ||
                      ((current_ekran.current_level >= EKRAN_RANGUVANNJA_LED_1   ) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_LED_8              )) ||
                      ( current_ekran.current_level == EKRAN_RANGUVANNJA_ANALOG_REGISTRATOR                                                                 ) ||
                      ( current_ekran.current_level == EKRAN_RANGUVANNJA_DIGITAL_REGISTRATOR                                                                ) ||
                      ( current_ekran.current_level == EKRAN_RANGUVANNJA_OFF_CB                                                                             ) ||
                      ( current_ekran.current_level == EKRAN_RANGUVANNJA_ON_CB                                                                              ) ||
                      ((current_ekran.current_level >= EKRAN_RANGUVANNJA_DF1_PLUS) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_DF8_BLK            )) ||
                      ((current_ekran.current_level >= EKRAN_RANGUVANNJA_SET_DT1_PLUS) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_RESET_DT4_MINUS)) ||
                      ((current_ekran.current_level >= EKRAN_RANGUVANNJA_D_AND1      ) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_AND8         )) ||
                      ((current_ekran.current_level >= EKRAN_RANGUVANNJA_D_OR1       ) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_OR8          )) ||
                      ((current_ekran.current_level >= EKRAN_RANGUVANNJA_D_XOR1      ) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_XOR8         )) ||
                      ((current_ekran.current_level >= EKRAN_RANGUVANNJA_D_NOT1      ) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_NOT16        ))
                     )
              {
                int max_row_ranguvannja;
                
                if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_OUTPUT_1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_OUTPUT_10))
                  max_row_ranguvannja = MAX_ROW_RANGUVANNJA_OUTPUT;
                else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_LED_1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_LED_8))
                  max_row_ranguvannja = MAX_ROW_RANGUVANNJA_LED;
                else if (current_ekran.current_level == EKRAN_RANGUVANNJA_ANALOG_REGISTRATOR)
                  max_row_ranguvannja = MAX_ROW_RANGUVANNJA_ANALOG_REGISTRATOR;
                else if (current_ekran.current_level == EKRAN_RANGUVANNJA_DIGITAL_REGISTRATOR)
                  max_row_ranguvannja = MAX_ROW_RANGUVANNJA_DIGITAL_REGISTRATOR;
                else if (current_ekran.current_level == EKRAN_RANGUVANNJA_OFF_CB)
                  max_row_ranguvannja = MAX_ROW_RANGUVANNJA_ON_CB;
                else if (current_ekran.current_level == EKRAN_RANGUVANNJA_ON_CB)
                  max_row_ranguvannja = MAX_ROW_RANGUVANNJA_OFF_CB;
                else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_DF1_PLUS) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_DF8_BLK ))
                  max_row_ranguvannja = MAX_ROW_RANGUVANNJA_DF;
                else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_SET_DT1_PLUS) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_RESET_DT4_MINUS))
                  max_row_ranguvannja = MAX_ROW_RANGUVANNJA_DT;
                else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_D_AND1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_AND8))
                  max_row_ranguvannja = MAX_ROW_RANGUVANNJA_D_AND;
                else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_D_OR1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_OR8))
                  max_row_ranguvannja = MAX_ROW_RANGUVANNJA_D_OR;
                else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_D_XOR1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_XOR8))
                  max_row_ranguvannja = MAX_ROW_RANGUVANNJA_D_XOR;
                else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_D_NOT1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_NOT16))
                  max_row_ranguvannja = MAX_ROW_RANGUVANNJA_D_NOT;

                if(current_ekran.edition == 0)
                {
                  unsigned int temp_state[N_BIG];
                  
                  if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_OUTPUT_1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_OUTPUT_10))
                  {
                    for (unsigned int i = 0; i < N_BIG; i++)
                    {
                      temp_state[i] = current_settings.ranguvannja_outputs[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_OUTPUT_1) + i];
                    }
                  }
                  else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_LED_1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_LED_8))
                  {
                    for (unsigned int i = 0; i < N_BIG; i++)
                    {
                      temp_state[i] = current_settings.ranguvannja_leds[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_LED_1) + i];
                    }
                  }
                  else if (current_ekran.current_level == EKRAN_RANGUVANNJA_ANALOG_REGISTRATOR)
                  {
                    for (unsigned int i = 0; i < N_BIG; i++)
                    {
                      temp_state[i] = current_settings.ranguvannja_analog_registrator[i];
                    }
                  }
                  else if (current_ekran.current_level == EKRAN_RANGUVANNJA_DIGITAL_REGISTRATOR)
                  {
                    for (unsigned int i = 0; i < N_BIG; i++)
                    {
                      temp_state[i] = current_settings.ranguvannja_digital_registrator[i];
                    }
                  }
                  else if (current_ekran.current_level == EKRAN_RANGUVANNJA_OFF_CB)
                  {
                    for (unsigned int i = 0; i < N_BIG; i++)
                    {
                      temp_state[i] = current_settings.ranguvannja_off_cb[i];
                    }
                  }
                  else if (current_ekran.current_level == EKRAN_RANGUVANNJA_ON_CB)
                  {
                    for (unsigned int i = 0; i < N_BIG; i++)
                    {
                      temp_state[i] = current_settings.ranguvannja_on_cb[i];
                    }
                  }
                  else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_DF1_PLUS) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_DF8_BLK ))
                  {
                    unsigned int index_in_ekran_list = current_ekran.current_level - EKRAN_RANGUVANNJA_DF1_PLUS;
                    unsigned int type_source = index_in_ekran_list % 3;
                    unsigned int index_of_df = index_in_ekran_list / 3;
    
                    if(type_source == 0)
                    {
                      for (unsigned int i = 0; i < N_BIG; i++)
                      {
                        temp_state[i] = current_settings.ranguvannja_df_source_plus[N_BIG*index_of_df + i];
                      }
                    }
                    else if(type_source == 1)
                    {
                      for (unsigned int i = 0; i < N_BIG; i++)
                      {
                        temp_state[i] = current_settings.ranguvannja_df_source_minus[N_BIG*index_of_df + i];
                      }
                    }
                    else
                    {
                      for (unsigned int i = 0; i < N_BIG; i++)
                      {
                        temp_state[i] = current_settings.ranguvannja_df_source_blk[N_BIG*index_of_df + i];
                      }
                    }
                  }
                  else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_SET_DT1_PLUS) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_RESET_DT4_MINUS))
                  {
                    unsigned int index_in_ekran_list = current_ekran.current_level - EKRAN_RANGUVANNJA_SET_DT1_PLUS;
                    unsigned int type_source = index_in_ekran_list % 2;
                    unsigned int type_of_action = (index_in_ekran_list / 2) & 0x1;
                    unsigned int index_of_dt = index_in_ekran_list / 4;
    
                    if (type_of_action == INDEX_ML_SET_DT)
                    {
                      if(type_source == INDEX_ML_LIST_TYPE_SOURCE_PLUS_DT)
                      {
                        for (unsigned int i = 0; i < N_BIG; i++)
                        {
                          temp_state[i] = current_settings.ranguvannja_set_dt_source_plus[N_BIG*index_of_dt + i];
                        }
                      }
                      else
                      {
                        for (unsigned int i = 0; i < N_BIG; i++)
                        {
                          temp_state[i] = current_settings.ranguvannja_set_dt_source_minus[N_BIG*index_of_dt + i];
                        }
                      }
                    }
                    else
                    {
                      if(type_source == INDEX_ML_LIST_TYPE_SOURCE_PLUS_DT)
                      {
                        for (unsigned int i = 0; i < N_BIG; i++)
                        {
                          temp_state[i] = current_settings.ranguvannja_reset_dt_source_plus[N_BIG*index_of_dt + i];
                        }
                      }
                      else
                      {
                        for (unsigned int i = 0; i < N_BIG; i++)
                        {
                          temp_state[i] = current_settings.ranguvannja_reset_dt_source_minus[N_BIG*index_of_dt + i];
                        }
                      }
                    }
                  }
                  else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_D_AND1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_AND8))
                  {
                    for (unsigned int i = 0; i < N_BIG; i++)
                    {
                      temp_state[i] = current_settings.ranguvannja_d_and[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_AND1) + i];
                    }
                  }
                  else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_D_OR1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_OR8))
                  {
                    for (unsigned int i = 0; i < N_BIG; i++)
                    {
                      temp_state[i] = current_settings.ranguvannja_d_or[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_OR1) + i];
                    }
                  }
                  else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_D_XOR1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_XOR8))
                  {
                    for (unsigned int i = 0; i < N_BIG; i++)
                    {
                      temp_state[i] = current_settings.ranguvannja_d_xor[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_XOR1) + i];
                    }
                  }
                  else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_D_NOT1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_NOT16))
                  {
                    for (unsigned int i = 0; i < N_BIG; i++)
                    {
                      temp_state[i] = current_settings.ranguvannja_d_not[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_NOT1) + i];
                    }
                  }

                  if (
                      (temp_state[0] == 0) &&
                      (temp_state[1] == 0) &&
                      (temp_state[2] == 0) &&
                      (temp_state[3] == 0) &&
                      (temp_state[4] == 0) &&
                      (temp_state[5] == 0) &&
                      (temp_state[6] == 0)
                     ) current_ekran.index_position = 0;
                  else
                  {
                    if(++current_ekran.index_position >= max_row_ranguvannja) current_ekran.index_position = 0;
                    // (x>>5) ��������� �������� x / 32 - ���� ������� �� ������ �� 32
                    // (x & 0x1f) ��������� �������� x % 32 - ������ �� ������ �� 32
                    while ((temp_state[current_ekran.index_position >> 5] & (1<<(current_ekran.index_position  & 0x1f))) ==0)
                    {
                      current_ekran.index_position++;
                      if(current_ekran.index_position >= max_row_ranguvannja) current_ekran.index_position = 0;
                    }
                  }
                }
                else
                {
                  //�����������
                  unsigned int found_new_index = 0;
//                  int add_filter[3 + 1] = 
//                  {
//                    RANG_PO_NZZ,
//                    RANG_NZZ,
//                    RANG_SECTOR_NZZ,
//                    -1 /*������� ���������� ������*/
//                  };
//                  EL_FILTER_STRUCT el_filter[NUMBER_DEFINED_ELEMENTS] =
//                  {
//                    {1, RANG_DF1_IN , RANG_DF8_OUT, 2, current_settings.number_defined_df },
//                    {1, RANG_DT1_SET, RANG_DT4_OUT, 3, current_settings.number_defined_dt },
//                    {1, RANG_D_AND1 , RANG_D_AND8 , 1, current_settings.number_defined_and},
//                    {1, RANG_D_OR1  , RANG_D_OR8  , 1, current_settings.number_defined_or },
//                    {1, RANG_D_XOR1 , RANG_D_XOR8 , 1, current_settings.number_defined_xor},
//                    {1, RANG_D_NOT1 , RANG_D_NOT16, 1, current_settings.number_defined_not}
//                  };
                  
                  //����������� �� �������� �������
                  if(++current_ekran.index_position >= max_row_ranguvannja) current_ekran.index_position = 0;
                  //����������, �� ����� ������ ������� ��������� � ����� ������������ 
                  while (found_new_index == 0)
                  {
                    check_current_index_is_presented_in_configuration(&found_new_index,
                                                                       /*add_filter,*/
                                                                       /*el_filter,*/
                                                                       1,
                                                                       NUMBER_GENERAL_SIGNAL_FOR_RANG,
                                                                       NUMBER_CTRL_PHASE_SIGNAL_FOR_RANG,
                                                                       NUMBER_EL_SIGNAL_FOR_RANG
                                                                      );

                    //����������, �� �� ��  �� ������ ������� �� ������ ���������, ��� ����� �������� ��� ������ ���� ����������
                    if (
                        ( current_ekran.current_level == EKRAN_RANGUVANNJA_ANALOG_REGISTRATOR ) || 
                        ( current_ekran.current_level == EKRAN_RANGUVANNJA_DIGITAL_REGISTRATOR) ||
                        ( current_ekran.current_level == EKRAN_RANGUVANNJA_OFF_CB             ) || 
                        ( current_ekran.current_level == EKRAN_RANGUVANNJA_ON_CB              )  
                       )   
                    {
                      unsigned int index_deleted_function;
                      
                      if (current_ekran.current_level == EKRAN_RANGUVANNJA_ANALOG_REGISTRATOR)
                        index_deleted_function = RANG_WORK_A_REJESTRATOR;
                      else if (current_ekran.current_level == EKRAN_RANGUVANNJA_DIGITAL_REGISTRATOR)
                        index_deleted_function = RANG_WORK_D_REJESTRATOR;
                      else if (current_ekran.current_level == EKRAN_RANGUVANNJA_OFF_CB)
                        index_deleted_function = RANG_WORK_BO;
                      else if (current_ekran.current_level == EKRAN_RANGUVANNJA_ON_CB)
                        index_deleted_function = RANG_WORK_BV;
                    
                      if(index_deleted_function == current_ekran.index_position)
                      {
                        found_new_index = 0;
                        current_ekran.index_position++;
                      }
                    }
                    else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_DF1_PLUS) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_DF8_BLK))
                    {
                      unsigned int index_in_ekran_list = current_ekran.current_level - EKRAN_RANGUVANNJA_DF1_PLUS;
                      unsigned int index_of_df = index_in_ekran_list / 3;

                      for (unsigned int i = 0; i < 2; i++)
                      {
                        unsigned int index_deleted_function;
                        //������ ���������� ������� � ������ �������, ��� �� ���� �������� ����� ����� ���� ������������ �� �������, ��� ����� ���������
                        if (i == 0)
                        {
                          if(index_of_df == 0)
                            index_deleted_function = (RANG_DF1_OUT > RANG_DF1_IN) ? RANG_DF1_IN : RANG_DF1_OUT;
                          else if(index_of_df == 1)
                            index_deleted_function = (RANG_DF2_OUT > RANG_DF2_IN) ? RANG_DF2_IN : RANG_DF2_OUT;
                          else if(index_of_df == 2)
                            index_deleted_function = (RANG_DF3_OUT > RANG_DF3_IN) ? RANG_DF3_IN : RANG_DF3_OUT;
                          else if(index_of_df == 3)
                            index_deleted_function = (RANG_DF4_OUT > RANG_DF4_IN) ? RANG_DF4_IN : RANG_DF4_OUT;
                          else if(index_of_df == 4)
                            index_deleted_function = (RANG_DF5_OUT > RANG_DF5_IN) ? RANG_DF5_IN : RANG_DF5_OUT;
                          else if(index_of_df == 5)
                            index_deleted_function = (RANG_DF6_OUT > RANG_DF6_IN) ? RANG_DF6_IN : RANG_DF6_OUT;
                          else if(index_of_df == 6)
                            index_deleted_function = (RANG_DF7_OUT > RANG_DF7_IN) ? RANG_DF7_IN : RANG_DF7_OUT;
                          else
                            index_deleted_function = (RANG_DF8_OUT > RANG_DF8_IN) ? RANG_DF8_IN : RANG_DF8_OUT;
                        }
                        else
                        {
                          if(index_of_df == 0)
                            index_deleted_function = (RANG_DF1_OUT > RANG_DF1_IN) ? RANG_DF1_OUT : RANG_DF1_IN;
                          else if(index_of_df == 1)
                            index_deleted_function = (RANG_DF2_OUT > RANG_DF2_IN) ? RANG_DF2_OUT : RANG_DF2_IN;
                          else if(index_of_df == 2)
                            index_deleted_function = (RANG_DF3_OUT > RANG_DF3_IN) ? RANG_DF3_OUT : RANG_DF3_IN;
                          else if(index_of_df == 3)
                            index_deleted_function = (RANG_DF4_OUT > RANG_DF4_IN) ? RANG_DF4_OUT : RANG_DF4_IN;
                          else if(index_of_df == 4)
                            index_deleted_function = (RANG_DF5_OUT > RANG_DF5_IN) ? RANG_DF5_OUT : RANG_DF5_IN;
                          else if(index_of_df == 5)
                            index_deleted_function = (RANG_DF6_OUT > RANG_DF6_IN) ? RANG_DF6_OUT : RANG_DF6_IN;
                          else if(index_of_df == 6)
                            index_deleted_function = (RANG_DF7_OUT > RANG_DF7_IN) ? RANG_DF7_OUT : RANG_DF7_IN;
                          else
                            index_deleted_function = (RANG_DF8_OUT > RANG_DF8_IN) ? RANG_DF8_OUT : RANG_DF8_IN;
                        }
                    
                        if(index_deleted_function == current_ekran.index_position)
                        {
                          found_new_index = 0;
                          current_ekran.index_position++;
                        }
                      }
                    }
                    else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_SET_DT1_PLUS) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_RESET_DT4_MINUS))
                    {
                      unsigned int index_in_ekran_list = current_ekran.current_level - EKRAN_RANGUVANNJA_SET_DT1_PLUS;
                      unsigned int index_of_dt = index_in_ekran_list / 4;

                      for (unsigned int i = 0; i < 3; i++)
                      {
                        unsigned int index_deleted_function;
                        //������ ���������� ������� � ������ �������, ��� �� ���� �������� �����  ����� ���� ������������ �� �������, ��� ����� ���������
                        if (i == 0)
                        {
                          if(index_of_dt == 0)
                            index_deleted_function = RANG_DT1_SET;
                          else if(index_of_dt == 1)
                            index_deleted_function = RANG_DT2_SET;
                          else if(index_of_dt == 2)
                            index_deleted_function = RANG_DT3_SET;
                          else if(index_of_dt == 3)
                            index_deleted_function = RANG_DT4_SET;
                        }
                        else if (i == 1)
                        {
                          if(index_of_dt == 0)
                            index_deleted_function = RANG_DT1_RESET;
                          else if(index_of_dt == 1)
                            index_deleted_function = RANG_DT2_RESET;
                          else if(index_of_dt == 2)
                            index_deleted_function = RANG_DT3_RESET;
                          else if(index_of_dt == 3)
                            index_deleted_function = RANG_DT4_RESET;
                        }
                        else
                        {
                          if(index_of_dt == 0)
                            index_deleted_function = RANG_DT1_OUT;
                          else if(index_of_dt == 1)
                            index_deleted_function = RANG_DT2_OUT;
                          else if(index_of_dt == 2)
                            index_deleted_function = RANG_DT3_OUT;
                          else if(index_of_dt == 3)
                            index_deleted_function = RANG_DT4_OUT;
                        }
                    
                        if(index_deleted_function == current_ekran.index_position)
                        {
                          found_new_index = 0;
                          current_ekran.index_position++;
                        }
                      }
                    }
                    else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_D_AND1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_AND8))
                    {
                      unsigned int index_of_d_and = current_ekran.current_level - EKRAN_RANGUVANNJA_D_AND1;

                      //������ ���������� ������� � ������ �������, ��� �� ���� �������� �����  ����� ���� ������������ �� �������, ��� ����� ���������
                      unsigned int index_deleted_function = RANG_D_AND1 + index_of_d_and;
                    
                      if(index_deleted_function == current_ekran.index_position)
                      {
                        found_new_index = 0;
                        current_ekran.index_position++;
                      }
                    }
                    else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_D_OR1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_OR8))
                    {
                      unsigned int index_of_d_or = current_ekran.current_level - EKRAN_RANGUVANNJA_D_OR1;

                      //������ ���������� ������� � ������ �������, ��� �� ���� �������� �����  ����� ���� ������������ �� �������, ��� ����� ���������
                      unsigned int index_deleted_function = RANG_D_OR1 + index_of_d_or;
                    
                      if(index_deleted_function == current_ekran.index_position)
                      {
                        found_new_index = 0;
                        current_ekran.index_position++;
                      }
                    }
                    else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_D_XOR1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_XOR8))
                    {
                      unsigned int index_of_d_xor = current_ekran.current_level - EKRAN_RANGUVANNJA_D_XOR1;

                      //������ ���������� ������� � ������ �������, ��� �� ���� �������� �����  ����� ���� ������������ �� �������, ��� ����� ���������
                      unsigned int index_deleted_function = RANG_D_XOR1 + index_of_d_xor;
                    
                      if(index_deleted_function == current_ekran.index_position)
                      {
                        found_new_index = 0;
                        current_ekran.index_position++;
                      }
                    }
                    else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_D_NOT1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_NOT16))
                    {
                      unsigned int index_of_d_not = current_ekran.current_level - EKRAN_RANGUVANNJA_D_NOT1;

                      //������ ���������� ������� � ������ �������, ��� �� ���� �������� �����  ����� ���� ������������ �� �������, ��� ����� ���������
                      unsigned int index_deleted_function = RANG_D_NOT1 + index_of_d_not;
                    
                      if(index_deleted_function == current_ekran.index_position)
                      {
                        found_new_index = 0;
                        current_ekran.index_position++;
                      }
                    }
//                    else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_OUTPUT_1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_OUTPUT_10))
//                    {
//                      unsigned int current_number_output = current_ekran.current_level - EKRAN_RANGUVANNJA_OUTPUT_1;
//                      
//                      for (unsigned int i = 0; i < 2; i++)
//                      {
//                        unsigned int index_deleted_function;
//                        unsigned int maska_func[N_BIG] = {0, 0, 0, 0, 0, 0, 0, 0};
//                        unsigned int need_filtration = 0;
//                        //��������� ������ �������, ��� ���������� ������� ����� ���� ����������� �� �������
//                        //������ ���������� ������� � ������ �������, ��� �� ���� �������� �����  ����� ���� ������������ �� �������, ��� ����� ���������
//                        if (i == 0)
//                        {
//                          index_deleted_function = (RANG_WORK_BV > RANG_WORK_BO) ? RANG_WORK_BO : RANG_WORK_BV;
//                        }
//                        else
//                        {
//                          index_deleted_function = (RANG_WORK_BV > RANG_WORK_BO) ? RANG_WORK_BV : RANG_WORK_BO;
//                        }
//        
//                        //������� �����  ��� ���� �������
//                        _SET_BIT(maska_func, index_deleted_function);
//        
//                        unsigned int index = 0;
//                        while ((need_filtration == 0) && (index < NUMBER_OUTPUTS))
//                        {
//                          //���������� ������� ����� ������, �� �� ����� ���� ������� �� ������������ �� ��� �����������
//                          if (index != current_number_output)
//                          {
//                            if (
//                                ((current_settings.ranguvannja_outputs[N_BIG*index    ] & maska_func[0]) != 0) ||
//                                ((current_settings.ranguvannja_outputs[N_BIG*index + 1] & maska_func[1]) != 0) ||
//                                ((current_settings.ranguvannja_outputs[N_BIG*index + 2] & maska_func[2]) != 0) ||
//                                ((current_settings.ranguvannja_outputs[N_BIG*index + 3] & maska_func[3]) != 0) ||
//                                ((current_settings.ranguvannja_outputs[N_BIG*index + 4] & maska_func[4]) != 0) ||
//                                ((current_settings.ranguvannja_outputs[N_BIG*index + 5] & maska_func[5]) != 0) ||
//                                ((current_settings.ranguvannja_outputs[N_BIG*index + 6] & maska_func[6]) != 0) ||
//                                ((current_settings.ranguvannja_outputs[N_BIG*index + 7] & maska_func[7]) != 0)
//                               )
//                            {
//                              need_filtration = 1;
//                            }
//                          }
//                          index++;
//                        }
//                        
//                        //� �������, ���� ������������ � ��������, ���� ����� ����������� �������
//                        if (need_filtration != 0)
//                        {
//                          if(index_deleted_function == current_ekran.index_position)
//                          {
//                            found_new_index = 0;
//                            current_ekran.index_position++;
//                          }
//                        }
//                      }
//                    }

                    //����������, �� �� �� ������ �� ��������� ������� �������
                    if(current_ekran.index_position >= max_row_ranguvannja)
                    {
                      found_new_index = 0;
                      current_ekran.index_position = 0;
                    }
                  }
                }
                position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;
                
                //������� ����� ����������� ����������� �������
                if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_OUTPUT_1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_OUTPUT_10))
                  make_ekran_set_function_in_output_led_df_dt_reg(current_ekran.current_level, INDEX_VIEWING_OUTPUT);
                else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_LED_1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_LED_8))
                  make_ekran_set_function_in_output_led_df_dt_reg(current_ekran.current_level, INDEX_VIEWING_LED);
                else if (current_ekran.current_level == EKRAN_RANGUVANNJA_ANALOG_REGISTRATOR)
                  make_ekran_set_function_in_output_led_df_dt_reg(current_ekran.current_level, INDEX_VIEWING_A_REG);
                else if (current_ekran.current_level == EKRAN_RANGUVANNJA_DIGITAL_REGISTRATOR)
                  make_ekran_set_function_in_output_led_df_dt_reg(current_ekran.current_level, INDEX_VIEWING_D_REG);
                else if (current_ekran.current_level == EKRAN_RANGUVANNJA_OFF_CB)
                  make_ekran_set_function_in_output_led_df_dt_reg(current_ekran.current_level, INDEX_VIEWING_OFF_CB);
                else if (current_ekran.current_level == EKRAN_RANGUVANNJA_ON_CB)
                  make_ekran_set_function_in_output_led_df_dt_reg(current_ekran.current_level, INDEX_VIEWING_ON_CB);
                else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_DF1_PLUS) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_DF8_BLK ))
                  make_ekran_set_function_in_output_led_df_dt_reg(current_ekran.current_level, INDEX_VIEWING_DF);
                else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_SET_DT1_PLUS) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_RESET_DT4_MINUS))
                  make_ekran_set_function_in_output_led_df_dt_reg(current_ekran.current_level, INDEX_VIEWING_DT);
                else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_D_AND1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_AND8))
                  make_ekran_set_function_in_output_led_df_dt_reg(current_ekran.current_level, INDEX_VIEWING_D_AND);
                else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_D_OR1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_OR8))
                  make_ekran_set_function_in_output_led_df_dt_reg(current_ekran.current_level, INDEX_VIEWING_D_OR);
                else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_D_XOR1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_XOR8))
                  make_ekran_set_function_in_output_led_df_dt_reg(current_ekran.current_level, INDEX_VIEWING_D_XOR);
                else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_D_NOT1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_NOT16))
                  make_ekran_set_function_in_output_led_df_dt_reg(current_ekran.current_level, INDEX_VIEWING_D_NOT);
              }

              //�������� �����������, �� ��������� ������ 
              new_state_keyboard &= (unsigned int)(~(1<<BIT_KEY_DOWN));
            }
            else if ((new_state_keyboard == (1<<BIT_KEY_RIGHT)) || (new_state_keyboard == (1<<BIT_KEY_LEFT)))
            {
              //��������� ������ RIGHT ��� LEFT
              //̳����� �� ����������� ��������� �� ��� ������� �������
              if((current_ekran.current_level >= EKRAN_RANGUVANNJA_INPUT_1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_INPUT_10))
              {
                unsigned int offset, shift;
                offset =  current_ekran.index_position >> 5;        //�� �, ��������, ������ �� 32
                shift  = (current_ekran.index_position & (32 - 1)); //�� �, ��������, ���������� ������ �� ������ �� 32

                edition_settings.ranguvannja_inputs[N_SMALL*(current_ekran.current_level - EKRAN_RANGUVANNJA_INPUT_1) + offset] ^=
                  (1 << shift);

                //������� ����� ����������� ����������� �������
                make_ekran_set_function_in_input(current_ekran.current_level);
              }
              else if((current_ekran.current_level >= EKRAN_RANGUVANNJA_BUTTON_1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_BUTTON_6))
              {
                edition_settings.ranguvannja_buttons[current_ekran.current_level - EKRAN_RANGUVANNJA_BUTTON_1] ^=
                  (1<<current_ekran.index_position);

                //������� ����� ����������� ����������� �������
                make_ekran_set_function_in_button(current_ekran.current_level);
              }
              else if((current_ekran.current_level >= EKRAN_RANGUVANNJA_OUTPUT_1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_OUTPUT_10))
              {
                unsigned int offset, shift;
                offset =  current_ekran.index_position >> 5;        //�� �, ��������, ������ �� 32
                shift  = (current_ekran.index_position & (32 - 1)); //�� �, ��������, ���������� ������ �� ������ �� 32

                edition_settings.ranguvannja_outputs[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_OUTPUT_1) + offset] ^=
                  (1 << shift);

                //������� ����� ����������� ����������� �������
                make_ekran_set_function_in_output_led_df_dt_reg(current_ekran.current_level, INDEX_VIEWING_OUTPUT);
              }
              else if((current_ekran.current_level >= EKRAN_RANGUVANNJA_LED_1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_LED_8))
              {
                unsigned int offset, shift;
                offset =  current_ekran.index_position >> 5;        //�� �, ��������, ������ �� 32
                shift  = (current_ekran.index_position & (32 - 1)); //�� �, ��������, ���������� ������ �� ������ �� 32

                edition_settings.ranguvannja_leds[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_LED_1) + offset] ^=
                  (1 << shift);

                //������� ����� ����������� ����������� �������
                make_ekran_set_function_in_output_led_df_dt_reg(current_ekran.current_level, INDEX_VIEWING_LED);
              }
              else if(current_ekran.current_level == EKRAN_RANGUVANNJA_ANALOG_REGISTRATOR)
              {
                unsigned int offset, shift;
                offset =  current_ekran.index_position >> 5;        //�� �, ��������, ������ �� 32
                shift  = (current_ekran.index_position & (32 - 1)); //�� �, ��������, ���������� ������ �� ������ �� 32

                edition_settings.ranguvannja_analog_registrator[offset] ^= (1 << shift);

                //������� ����� ����������� ����������� �������
                make_ekran_set_function_in_output_led_df_dt_reg(current_ekran.current_level, INDEX_VIEWING_A_REG);
              }
              else if(current_ekran.current_level == EKRAN_RANGUVANNJA_DIGITAL_REGISTRATOR)
              {
                unsigned int offset, shift;
                offset =  current_ekran.index_position >> 5;        //�� �, ��������, ������ �� 32
                shift  = (current_ekran.index_position & (32 - 1)); //�� �, ��������, ���������� ������ �� ������ �� 32

                edition_settings.ranguvannja_digital_registrator[offset] ^= (1 << shift);

                //������� ����� ����������� ����������� �������
                make_ekran_set_function_in_output_led_df_dt_reg(current_ekran.current_level, INDEX_VIEWING_D_REG);
              }
              else if(current_ekran.current_level == EKRAN_RANGUVANNJA_OFF_CB)
              {
                unsigned int offset, shift;
                offset =  current_ekran.index_position >> 5;        //�� �, ��������, ������ �� 32
                shift  = (current_ekran.index_position & (32 - 1)); //�� �, ��������, ���������� ������ �� ������ �� 32

                edition_settings.ranguvannja_off_cb[offset] ^= (1 << shift);

                //������� ����� ����������� ����������� �������
                make_ekran_set_function_in_output_led_df_dt_reg(current_ekran.current_level, INDEX_VIEWING_OFF_CB);
              }
              else if(current_ekran.current_level == EKRAN_RANGUVANNJA_ON_CB)
              {
                unsigned int offset, shift;
                offset =  current_ekran.index_position >> 5;        //�� �, ��������, ������ �� 32
                shift  = (current_ekran.index_position & (32 - 1)); //�� �, ��������, ���������� ������ �� ������ �� 32

                edition_settings.ranguvannja_on_cb[offset] ^= (1 << shift);

                //������� ����� ����������� ����������� �������
                make_ekran_set_function_in_output_led_df_dt_reg(current_ekran.current_level, INDEX_VIEWING_ON_CB);
              }
              else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_DF1_PLUS) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_DF8_BLK ))
              {
                unsigned int offset, shift;
                offset =  current_ekran.index_position >> 5;        //�� �, ��������, ������ �� 32
                shift  = (current_ekran.index_position & (32 - 1)); //�� �, ��������, ���������� ������ �� ������ �� 32

                unsigned int index_in_ekran_list = current_ekran.current_level - EKRAN_RANGUVANNJA_DF1_PLUS;
                unsigned int type_source = index_in_ekran_list % 3;
                unsigned int index_of_df = index_in_ekran_list / 3;
    
                if(type_source == INDEX_ML_LIST_TYPE_SOURCE_PLUS_DF)
                  edition_settings.ranguvannja_df_source_plus[N_BIG*index_of_df + offset] ^= (1 << shift);
                else if(type_source == INDEX_ML_LIST_TYPE_SOURCE_MINUS_DF)
                  edition_settings.ranguvannja_df_source_minus[N_BIG*index_of_df + offset] ^= (1 << shift);
                else
                  edition_settings.ranguvannja_df_source_blk[N_BIG*index_of_df + offset] ^= (1 << shift);
                
                //������� ����� ����������� ����������� �������
                make_ekran_set_function_in_output_led_df_dt_reg(current_ekran.current_level, INDEX_VIEWING_DF);
              }
              else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_SET_DT1_PLUS) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_RESET_DT4_MINUS))
              {
                unsigned int offset, shift;
                offset =  current_ekran.index_position >> 5;        //�� �, ��������, ������ �� 32
                shift  = (current_ekran.index_position & (32 - 1)); //�� �, ��������, ���������� ������ �� ������ �� 32

                unsigned int index_in_ekran_list = current_ekran.current_level - EKRAN_RANGUVANNJA_SET_DT1_PLUS;
                unsigned int type_source = index_in_ekran_list % 2;
                unsigned int type_of_action = (index_in_ekran_list / 2) & 0x1;
                unsigned int index_of_dt = index_in_ekran_list / 4;
    
                if (type_of_action == INDEX_ML_SET_DT)
                {
                  if(type_source == INDEX_ML_LIST_TYPE_SOURCE_PLUS_DT)
                    edition_settings.ranguvannja_set_dt_source_plus[N_BIG*index_of_dt + offset] ^= (1 << shift);
                  else
                    edition_settings.ranguvannja_set_dt_source_minus[N_BIG*index_of_dt + offset] ^= (1 << shift);
                }
                else
                {
                  if(type_source == INDEX_ML_LIST_TYPE_SOURCE_PLUS_DT)
                    edition_settings.ranguvannja_reset_dt_source_plus[N_BIG*index_of_dt + offset] ^= (1 << shift);
                  else
                    edition_settings.ranguvannja_reset_dt_source_minus[N_BIG*index_of_dt + offset] ^= (1 << shift);
                }
                
                //������� ����� ����������� ����������� �������
                make_ekran_set_function_in_output_led_df_dt_reg(current_ekran.current_level, INDEX_VIEWING_DT);
              }
              else if((current_ekran.current_level >= EKRAN_RANGUVANNJA_D_AND1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_AND8))
              {
                unsigned int offset, shift;
                offset =  current_ekran.index_position >> 5;        //�� �, ��������, ������ �� 32
                shift  = (current_ekran.index_position & (32 - 1)); //�� �, ��������, ���������� ������ �� ������ �� 32

                edition_settings.ranguvannja_d_and[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_AND1) + offset] ^=
                  (1 << shift);

                //������� ����� ����������� ����������� �������
                make_ekran_set_function_in_output_led_df_dt_reg(current_ekran.current_level, INDEX_VIEWING_D_AND);
              }
              else if((current_ekran.current_level >= EKRAN_RANGUVANNJA_D_OR1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_OR8))
              {
                unsigned int offset, shift;
                offset =  current_ekran.index_position >> 5;        //�� �, ��������, ������ �� 32
                shift  = (current_ekran.index_position & (32 - 1)); //�� �, ��������, ���������� ������ �� ������ �� 32

                edition_settings.ranguvannja_d_or[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_OR1) + offset] ^=
                  (1 << shift);

                //������� ����� ����������� ����������� �������
                make_ekran_set_function_in_output_led_df_dt_reg(current_ekran.current_level, INDEX_VIEWING_D_OR);
              }
              else if((current_ekran.current_level >= EKRAN_RANGUVANNJA_D_XOR1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_XOR8))
              {
                unsigned int offset, shift;
                offset =  current_ekran.index_position >> 5;        //�� �, ��������, ������ �� 32
                shift  = (current_ekran.index_position & (32 - 1)); //�� �, ��������, ���������� ������ �� ������ �� 32

                edition_settings.ranguvannja_d_xor[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_XOR1) + offset] ^=
                  (1 << shift);

                //������� ����� ����������� ����������� �������
                make_ekran_set_function_in_output_led_df_dt_reg(current_ekran.current_level, INDEX_VIEWING_D_XOR);
              }
              else if((current_ekran.current_level >= EKRAN_RANGUVANNJA_D_NOT1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_NOT16))
              {
                unsigned int offset, shift;
                offset =  current_ekran.index_position >> 5;        //�� �, ��������, ������ �� 32
                shift  = (current_ekran.index_position & (32 - 1)); //�� �, ��������, ���������� ������ �� ������ �� 32

                edition_settings.ranguvannja_d_not[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_NOT1) + offset] ^=
                  (1 << shift);

                //������� ����� ����������� ����������� �������
                make_ekran_set_function_in_output_led_df_dt_reg(current_ekran.current_level, INDEX_VIEWING_D_NOT);
              }

              //�������� �����������, �� ��������� ������ 
              if (new_state_keyboard == (1<<BIT_KEY_RIGHT)) new_state_keyboard &= (unsigned int)(~(1<<BIT_KEY_RIGHT));
              else new_state_keyboard &= (unsigned int)(~(1<<BIT_KEY_LEFT));
            }
            else
            {
              //��������� ����� ������� ������ - �� � ����������� ��������, ���� ������� ����������� ��� �������� ������ � ������ �����
              unsigned int temp_data = new_state_keyboard;
              new_state_keyboard &= ~temp_data;
            }
          }
        }
        break;
      }
/******************************************************************************************************************************************/ 

/************************************* BEGIN  EKRAN_LEVEL_ *****************************************************************************************************/      
//    case 0xff:
//      {
//        //������� �� ��� ���� �����������
//        new_state_keyboard &= (1<<BIT_KEY_ENTER)|(1<<BIT_KEY_ESC)|(1<<BIT_KEY_UP)|(1<<BIT_KEY_DOWN)|(1<<BIT_REWRITE);
//        //������ �������� 䳿, ���� ��������� ������ �� ��� ����� ��������, ��� ����� ������� �������� �����
//        if (new_state_keyboard !=0)
//        {
//          //�������� ����� �� ��������� ������
//          if((new_state_keyboard & (1<<BIT_REWRITE)) !=0)
//          {
//            //������� �� ���������� ������
//            new_state_keyboard &= (unsigned int)(~(1<<BIT_REWRITE));
//          }
//          else
//          {
//            if (new_state_keyboard == (1<<BIT_KEY_ENTER))
//            {
//              //��������� ������ ENTER
//
//              //�������� �����������, �� ��������� ������ 
//              new_state_keyboard &= (unsigned int)(~(1<<BIT_KEY_ENTER));
//            }
//            else if (new_state_keyboard == (1<<BIT_KEY_ESC))
//            {
//              //���������� � ��������� ����
//              current_ekran.current_level = previous_level_in_current_level_menu[current_ekran.current_level];
//              current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
//              current_ekran.edition = 0;
//
//              //����������� ������� �� ����������� ������ ������
//              new_state_keyboard |= (1<<BIT_REWRITE);
//              //�������� �����������, �� ��������� ������ 
//              new_state_keyboard &= (unsigned int)(~(1<<BIT_KEY_ESC));
//            }
//            else if (new_state_keyboard == (1<<BIT_KEY_UP))
//            {
//              //��������� ������ UP
//
//              //�������� �����������, �� ��������� ������ 
//              new_state_keyboard &= (unsigned int)(~(1<<BIT_KEY_UP));
//            }
//            else if (new_state_keyboard == (1<<BIT_KEY_DOWN))
//            {
//              //��������� ������ DOWN
//
//              //�������� �����������, �� ��������� ������ 
//              new_state_keyboard &= (unsigned int)(~(1<<BIT_KEY_DOWN));
//            }
//            else if (new_state_keyboard == (1<<BIT_KEY_RIGHT))
//            {
//              //��������� ������ RIGHT
//
//              //�������� �����������, �� ��������� ������ 
//              new_state_keyboard &= (unsigned int)(~(1<<BIT_KEY_RIGHT));
//            }
//            else if (new_state_keyboard == (1<<BIT_KEY_LEFT))
//            {
//              //��������� ������ LEFT
//
//              //�������� �����������, �� ��������� ������ 
//              new_state_keyboard &= (unsigned int)(~(1<<BIT_KEY_LEFT));
//            }
//            else
//            {
//              //��������� ����� ������� ������ - �� � ����������� ��������, ���� ������� ����������� ��� �������� ������ � ������ �����
//              unsigned int temp_data = new_state_keyboard;
//              new_state_keyboard &= ~temp_data;
//            }
//          }
//        }
//        break;
//      }
/************************************* END  EKRAN_LEVEL_ *****************************************************************************************************/ 
    default:  break;
    }
  }
}
/*****************************************************/


/*****************************************************/
//��������� ��� ��������� ����� ��� ���������� ������
/*
  ������ ���������
  label_value - �������� �� ��������  �����
  inc_dec 
    0 - �������� �� �������
    1 - �������� �� �������
*/
/*****************************************************/
void inc_or_dec_value(unsigned int *label_value, unsigned int inc_dec)
{
  int temp_value = *label_value;
  
  if(inc_dec == 0) temp_value--;
  else if(inc_dec == 1) temp_value++;
  
  if(temp_value > 9) temp_value = 0;
  else if(temp_value < 0) temp_value = 9;
  
  *label_value = temp_value;
}
/*****************************************************/

/*****************************************************/
//������ ����������� ��� �� �� ����� ��� ���� ������ ����
/*****************************************************/
void make_ekran_ask_rewrite(void)
{
  const unsigned char name_string[MAX_NAMBER_LANGUAGE][2][MAX_COL_LCD] = 
  {
    {
     "������ ���������",
     "��-ENTER ���-ESC"
    },
    {
     "  ������ ����  ",
     "���-ENTER ͳ-ESC"
    },
    {
     " Enter changes  ",
     "Yes-ENTER No-ESC"
    },
    {
     "������ ���������",
     "��-ENTER ���-ESC"
    }
  };

  int index_language;
  
  if (current_ekran.current_level == EKRAN_VIEW_SETTING_LANGUAGE)
    index_language = index_language_in_array(edition_settings.language);
  else
    index_language = index_language_in_array(current_settings.language);

  //�������  ����� � ������� �����
  for (unsigned int i=0; i< MAX_ROW_LCD; i++)
  {
    for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_language][i][j];
  }
  
  //�������� �������� ���� �����
  current_ekran.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/

/*****************************************************/
//������ ����������� ������������ ��������� �������
/*****************************************************/
void make_ekran_about_activation_command(unsigned int index, unsigned char information[][MAX_NAMBER_LANGUAGE][MAX_COL_LCD])
{
  const unsigned char name_string[MAX_NAMBER_LANGUAGE][MAX_COL_LCD] = 
  {
    "��-ENTER ���-ESC",
    "���-ENTER ͳ-ESC",
    "Yes-ENTER No-ESC",
    "��-ENTER ���-ESC"
  };
  int index_language = index_language_in_array(current_settings.language);

  //�������  ����� � ������� �����
  for (unsigned int i=0; i< MAX_ROW_LCD; i++)
  {
    if (i == 0)
    {
      for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = information[index][index_language][j];
    }
    else
    {
      for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_language][j];
    }
  }
  
  //�������� �������� ���� �����
  current_ekran.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/

/*****************************************************/
//���������� ���� ��� �������
/*****************************************************/
void make_ekran_about_error(const unsigned char information[][MAX_COL_LCD])
{
  const unsigned char name_string[MAX_NAMBER_LANGUAGE][MAX_COL_LCD] = 
  {
    " ����� Enter/Esc",
    " ����� Enter/Esc",
    " Exit Enter/Esc ",
    " ����� Enter/Esc"
  };
  int index_language;

  if (current_ekran.current_level == EKRAN_VIEW_SETTING_LANGUAGE)
    index_language = index_language_in_array(edition_settings.language);
  else
    index_language = index_language_in_array(current_settings.language);
  
  //�������  ����� � ������� �����
  for (unsigned int i=0; i< MAX_ROW_LCD; i++)
  {
    if (i == 0)
    {
      for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = information[index_language][j];
    }
    else
    {
      for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_language][j];
    }
  }
  
  //�������� �������� ���� �����
  current_ekran.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/

/*****************************************************/
//����������� ������� �������� �������
/*****************************************************
������ ���������
  0 - �������� ������ ����
  1 - ��������� ������ �����
������ ���������
  ����
*****************************************************/
unsigned int edit_setpoint(unsigned int action, unsigned int value, unsigned int floating_value, unsigned int comma, unsigned int end, unsigned int min_step)
{
  unsigned int rozrjad, vaga = min_step, temp_value, data_return;
  //���������� ������ ����� �� ���� ����� ����� ������
  rozrjad = end - current_ekran.position_cursor_x;
  
  //� ��� ���� ���������� ����� � ������ � �����, �� ��������� ������� ����
  if (floating_value != 0)
    if (current_ekran.position_cursor_x < ((int)comma)) rozrjad--;
      
  for(unsigned int i=0; i < rozrjad; i++)  vaga *= 10;
  
  //�������� ����� , ��� ���� ������
  temp_value = (value / vaga) % 10;
  
  //� �������� ����, ���� ��� �������� ����������� ������ ������� � ���� ����������
  data_return = value - temp_value*vaga;
  
  //������� �������� ������
  inc_or_dec_value(&temp_value, action);
  
  //������� ������ ������ � ������� ���������
  data_return += temp_value*vaga;
  
  
  return data_return;
}
/*****************************************************/

/*****************************************************/
//���������� ������������ �����
/*
���������
  1 - ���� ���������
  0 - ���� �����������
*/
/*****************************************************/
unsigned int check_data_setpoint(unsigned int current_value, unsigned int min_value, unsigned int max_value)
{
  if ((current_value < min_value) || (current_value > max_value)) return 0;

  //����� � ������������, �� ������� � ����� �������
  return 1;
}
/*****************************************************/

/*****************************************************/
//
/*****************************************************/
/*****************************************************/
