#include "header.h"

/*****************************************************/
//Функція меню з якої здійснюються всі інші операції
/*****************************************************/
void main_manu_function(void)
{
  //Перевіряємо чи якась кнопка натиснута
  if (new_state_keyboard !=0)
  {
    //Аналізуємо в якому ми зараз робочому екрані і виконуємо відповідні дії
    switch (current_ekran.current_level)
    {

/******************************************************************************************************************************************/ 
    case EKRAN_LEVEL_SET_NEW_PASSWORD:
      {
        //Змінні для фіксації введеного паролю
        static unsigned int new_setting_password;
        static int number_symbols_new_setting_password;
        
        //Очищаємо всі біти краім упралінських
        unsigned int maska_keyboard_bits = (1<<BIT_KEY_ENTER)| (1<<BIT_KEY_ESC)|(1<<BIT_REWRITE);
        
        if (current_ekran.edition == 1)
          maska_keyboard_bits |= (1<<BIT_KEY_RIGHT) | (1<<BIT_KEY_LEFT) | (1<<BIT_KEY_UP)|(1<<BIT_KEY_DOWN);
        
        new_state_keyboard &= maska_keyboard_bits;

        if (new_state_keyboard !=0)
        {
          //Пріоритет стоїть на обновлені екрану
          if((new_state_keyboard & (1<<BIT_REWRITE)) !=0)
          {
            if (current_ekran.edition == 1)
            {
              current_ekran.cursor_on = 1;
              current_ekran.cursor_blinking_on = 1;
              current_ekran.position_cursor_x = COL_NEW_PASSWORD_BEGIN;
              position_in_current_level_menu[current_ekran.current_level] = 1;
              //Встановлюємо початкове значення нового паролю і скидаємо кількість введених символів
              new_setting_password = current_settings.password;
              number_symbols_new_setting_password = 0;
              
              unsigned int temp_value = new_setting_password;
              while (temp_value != 0)
              {
                number_symbols_new_setting_password++;
                temp_value /= 10;
              }
              if (number_symbols_new_setting_password == 0) number_symbols_new_setting_password = 1; //Це випадок коли current_settings.password = 0, тоді кількість символів рівна 0, бо число є "0"
            
              //Формуємо екран рівня password
//              make_ekran_password(new_setting_password, 1);
              //Очищаємо біт обновлення екрану
              new_state_keyboard &= (unsigned int)(~(1<<BIT_REWRITE));
            }
            else
            {
              //Переходимо у попереднє меню і анульовуємо процес редагування
              current_ekran.current_level = previous_level_in_current_level_menu[current_ekran.current_level];
              current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
              current_ekran.edition = 0;
              
              //Біт, який сигналізує про обновлекння екрану не скидаємто, бо його ще раз треба перерисувати
            }
          }
          else
          {
            if (new_state_keyboard == (1<<BIT_KEY_ENTER))
            {
              //Натиснута кнопка ENTER
              if (current_ekran.edition == 1)
              {
                //Виходимо з режиму редагування
                if (current_settings.password == new_setting_password)
                {
                  //Переходимо на попередній рівень
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
                //Помічаємо, що поле структури зараз буде змінене
                changed_settings = CHANGED_ETAP_EXECUTION;
                        
                //Вводимо нове значення у дію
                current_settings.password = new_setting_password;

                //Помічаємо, що таблиця змінилася і її треба буде з системи захистів зкопіювати у таблицю з якою працює система захистів (хоч ця операція і є зайвою, бо не було змін тих полів, які використовуються системою захистів, але це я зробив для універсальності, щоб завжди дві таблиці були ідентичні)
                changed_settings = CHANGED_ETAP_ENDED;
                
                //Не формуємо запис у таблиці настройок про зміну конфігурації, бо її як такої не було. Просто змінився пароль доступу з меню
                //але ініціюємо запис у EEPROM настройок
                //Запускаємо запис у EEPROM
                if (_CHECK_SET_BIT(active_functions, RANG_SETTINGS_CHANGED) == 0) current_settings_interfaces = current_settings;
                _SET_BIT(control_i2c_taskes, TASK_START_WRITE_SETTINGS_EEPROM_BIT);
                
                //Вихід у режимі редагування
                current_ekran.edition = 0;
                //Переходимо на попередній рівень
                current_ekran.current_level = previous_level_in_current_level_menu[current_ekran.current_level];
                current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
                current_ekran.cursor_on = 0;
                current_ekran.cursor_blinking_on = 0;
              }
              else if (current_ekran.edition == 3)
              {
                //Вихід у режимі редагування
                current_ekran.edition = 0;
                //Переходимо на попередній рівень
                current_ekran.current_level = previous_level_in_current_level_menu[current_ekran.current_level];
                current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
                current_ekran.cursor_on = 0;
                current_ekran.cursor_blinking_on = 0;
              }
              else
              {
                //По ідеї сюди програма ніколи б не мала дійти і виставляється повідомлення про помилку
                current_ekran.edition = 3;
              }
                
              if(current_ekran.edition == 2) make_ekran_ask_rewrite();
              else if (current_ekran.edition == 0)
              {
                //Виставляємо біт обновлення екрану
                new_state_keyboard |= (1<<BIT_REWRITE);
              }
              else if (current_ekran.edition == 3)
              {
                const unsigned char information_about_error[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
                {
                  " Неопред.ошибка ",
                  " Невизн.помилка ",
                  " Undefined error",
                  " Неопред.ошибка "
                };
                current_ekran.cursor_on = 0;
                current_ekran.cursor_blinking_on = 0;
                make_ekran_about_info(true, information_about_error);
              }

              //Очистити сигналізацію, що натиснута кнопка 
              new_state_keyboard &= (unsigned int)(~(1<<BIT_KEY_ENTER));
            }
            else if (new_state_keyboard == (1<<BIT_KEY_ESC))
            {
              //Натиснута кнопка ESC

              //Переходимо у попереднє меню і анульовуємо процес редагування
              current_ekran.current_level = previous_level_in_current_level_menu[current_ekran.current_level];
              current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
              current_ekran.edition = 0;
              
              //Очистити сигналізацію, що натиснута кнопка 
              new_state_keyboard &= (unsigned int)(~(1<<BIT_KEY_ESC));
              //Виставляємо біт обновлення екрану
              new_state_keyboard |= (1<<BIT_REWRITE);
            }
            else if (new_state_keyboard == (1<<BIT_KEY_UP))
            {
              //Натиснута кнопка UP
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
                    if (current_ekran.current_level != EKRAN_LEVEL_SET_NEW_PASSWORD) edit_rozrjad = 1;
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
              //Формуємо екран рівня password
//              make_ekran_password(new_setting_password, 1);
              //Очистити сигналізацію, що натиснута кнопка 
              new_state_keyboard &= (unsigned int)(~(1<<BIT_KEY_UP));
            }
            else if (new_state_keyboard == (1<<BIT_KEY_DOWN))
            {
              //Натиснута кнопка DOWN
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
                      if (current_ekran.current_level != EKRAN_LEVEL_SET_NEW_PASSWORD) edit_rozrjad = 4;
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
                  if (current_ekran.current_level != EKRAN_LEVEL_SET_NEW_PASSWORD) new_setting_password = 4;
                  else new_setting_password = 0;
                }
                  
              }
              else
                new_setting_password = (vyshchi_rozrjady*vaga*10) + edit_rozrjad*vaga + ostacha;

              //Формуємо екран рівня password
//              make_ekran_password(new_setting_password, 1);
              //Очистити сигналізацію, що натиснута кнопка 
              new_state_keyboard &= (unsigned int)(~(1<<BIT_KEY_DOWN));
            }
            else if (new_state_keyboard == (1<<BIT_KEY_RIGHT))
            {
              //Натиснута кнопка RIGHT
              if (new_setting_password !=0)
              {
                if (++current_ekran.position_cursor_x > COL_NEW_PASSWORD_END) current_ekran.position_cursor_x = COL_NEW_PASSWORD_BEGIN;
                if (number_symbols_new_setting_password < (current_ekran.position_cursor_x - COL_NEW_PASSWORD_BEGIN + 1))
                {
                  new_setting_password = new_setting_password*10 + 1;
                  number_symbols_new_setting_password++;
                }
              }

              //Формуємо екран рівня password
//              make_ekran_password(new_setting_password, 1);
              //Очистити сигналізацію, що натиснута кнопка 
              new_state_keyboard &= (unsigned int)(~(1<<BIT_KEY_RIGHT));
            }
            else if (new_state_keyboard == (1<<BIT_KEY_LEFT))
            {
              //Натиснута кнопка LEFT
              if (new_setting_password !=0)
              {
                if (--current_ekran.position_cursor_x < COL_NEW_PASSWORD_BEGIN) current_ekran.position_cursor_x = COL_NEW_PASSWORD_BEGIN + number_symbols_new_setting_password - 1;
              }

              //Формуємо екран рівня password
//              make_ekran_password(new_setting_password, 1);
              //Очистити сигналізацію, що натиснута кнопка 
              new_state_keyboard &= (unsigned int)(~(1<<BIT_KEY_LEFT));
            }
            else
            {
              //Натиснуто зразу декілька кнопок - це є невизначена ситуація, тому скидаємо сигналізацію про натиснуті кнопки і чекаємо знову
              unsigned int temp_data = new_state_keyboard;
              new_state_keyboard &= ~temp_data;
            }
          }
          
        }
        break;
      }
/******************************************************************************************************************************************/ 
      

/****************************************************************************************************************************************/      
    case EKRAN_CHOOSE_SETTINGS_CTRL_PHASE:
    case EKRAN_LEVEL_CHOOSE_PASSWORDS:
    case EKRAN_LIST_OUTPUTS_FOR_RANGUVANNJA:
    case EKRAN_LIST_LEDS_FOR_RANGUVANNJA:
    case EKRAN_LIST_ALARMS:
    case EKRAN_CHOOSE_SETTINGS_ALARMS1:
    case EKRAN_CHOOSE_SETTINGS_ALARMS2:
    case EKRAN_CHOOSE_SETTINGS_UVV:
    case EKRAN_CHOSE_COMMUNICATION_PARAMETERS:
    case EKRAN_VIEW_NAME_OF_CELL:
    case EKRAN_CHOSE_SETTING_RS485:
    case EKRAN_VIEW_LIST_OF_REGISTRATORS:
    case EKRAN_VIEW_SETTINGS_OF_ANALOG_REGISTRATORS:
    case EKRAN_EXTENDED_LIGIC:
    case EKRAN_LIST_DF_FOR_RANGUVANNJA:
    case EKRAN_LIST_DF_FOR_TIMEOUT_SETTINGS:
    case EKRAN_LIST_DT:
    case EKRAN_SET_RESET_DT1:
    case EKRAN_SET_RESET_DT2:
    case EKRAN_SET_RESET_DT3:
    case EKRAN_SET_RESET_DT4:
    case EKRAN_LIST_D_AND:
    case EKRAN_LIST_D_OR:
    case EKRAN_LIST_D_XOR:
    case EKRAN_LIST_D_NOT:
    case EKRAN_STATE_OUTPUTS:
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
        //Очищаємо всі біти краім упралінських
        new_state_keyboard &= (1<<BIT_KEY_ENTER)|(1<<BIT_KEY_ESC)|(1<<BIT_KEY_UP)|(1<<BIT_KEY_DOWN)|(1<<BIT_REWRITE);
        //Дальше виконуємо дії, якщо натиснута кнопка на яку треба реагівати, або стоїть команда обновити екран
        if (new_state_keyboard !=0)
        {
          //Пріоритет стоїть на обновлені екрану
          if((new_state_keyboard & (1<<BIT_REWRITE)) !=0)
          {
            if (
                (current_ekran.current_level == EKRAN_CHOOSE_SETTINGS_CTRL_PHASE)
               )   
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_CHOSE_SETTINGS_ANY_PROTECTION) current_ekran.index_position = 0;
              position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;

              //Формуємо екран уставки-витримки-настройки для всіх захистів
              make_ekran_chose_settings_any_protection();
            }
            else if (current_ekran.current_level == EKRAN_LIST_ALARMS)
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_LIST_ALARMS) current_ekran.index_position = 0;
              
              position_in_current_level_menu[EKRAN_LIST_ALARMS] = current_ekran.index_position;

              //Формуємо екран списку сигналізацій
              make_ekran_choose_list_alarms();
            }
            else if ((current_ekran.current_level >= EKRAN_CHOOSE_SETTINGS_ALARMS1) && (current_ekran.current_level <= EKRAN_CHOOSE_SETTINGS_ALARMS2))
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_CHOOSE_SETTINGS_ALARMS) current_ekran.index_position = 0;
              
              position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;

              //Формуємо екран вибору налаштувань для сигналізації
              make_ekran_choose_settings_alarms();
            }
            else if (current_ekran.current_level == EKRAN_LEVEL_CHOOSE_PASSWORDS)
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_CHOOSE_PASSWORDS) current_ekran.index_position = 0;
              position_in_current_level_menu[EKRAN_LEVEL_CHOOSE_PASSWORDS] = current_ekran.index_position;
            
              //Формуємо екран заголовків паролів
              make_ekran_chose_passwords();
            }
            else if (current_ekran.current_level == EKRAN_CHOOSE_SETTINGS_UVV)
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_CHOSE_SETTINGS_UVV) current_ekran.index_position = 0;
              position_in_current_level_menu[EKRAN_CHOOSE_SETTINGS_UVV] = current_ekran.index_position;
                //Формуємо екран вибору настройок УВВ
              make_ekran_chose_settings_uvv();
            }
            else if (current_ekran.current_level == EKRAN_CHOSE_COMMUNICATION_PARAMETERS)
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_CHOSE_COMMUNICATION_PARAMETERS) current_ekran.index_position = 0;
              position_in_current_level_menu[EKRAN_CHOSE_COMMUNICATION_PARAMETERS] = current_ekran.index_position;
              //Формуємо екран вибору настройок парамеирів комунікації
              make_ekran_chose_communication_parameters();
            }
            else if (current_ekran.current_level == EKRAN_VIEW_NAME_OF_CELL)
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_VIEW_NAME_OF_CELL) current_ekran.index_position = 0;
              position_in_current_level_menu[EKRAN_VIEW_NAME_OF_CELL] = current_ekran.index_position;
              //Формуємо екран відображення імені ячейки
              make_ekran_name_of_cell();
            }
            else if (current_ekran.current_level == EKRAN_CHOSE_SETTING_RS485)
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_CHOSE_SETTING_RS485) current_ekran.index_position = 0;
              position_in_current_level_menu[EKRAN_CHOSE_SETTING_RS485] = current_ekran.index_position;
              //Формуємо екран відображення списку настройок для інтерфейсу RS-485
              make_ekran_chose_setting_rs485();
            }
            else if (current_ekran.current_level == EKRAN_VIEW_LIST_OF_REGISTRATORS)
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_LIST_OF_REGISTRATORS) current_ekran.index_position = 0;
              position_in_current_level_menu[EKRAN_VIEW_LIST_OF_REGISTRATORS] = current_ekran.index_position;
              //Формуємо екран вибору реєстратора
              make_ekran_chose_registrators();
            }
            else if (current_ekran.current_level == EKRAN_VIEW_SETTINGS_OF_ANALOG_REGISTRATORS)
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_SETTINGS_OF_ANALOG_REGISTRATOR) current_ekran.index_position = 0;
              position_in_current_level_menu[EKRAN_VIEW_SETTINGS_OF_ANALOG_REGISTRATORS] = current_ekran.index_position;
              //Формуємо екран вибору ностройок аналогового реєстратора
              make_ekran_settings_analog_registrators();
            }
            else if (current_ekran.current_level == EKRAN_EXTENDED_LIGIC)
            {
              do
              {
                if(current_ekran.index_position >= MAX_ROW_FOR_EXTENDED_LIGIC) current_ekran.index_position = 0;
                
                if ((current_ekran.index_position == INDEX_OF_DEFINED_FUNCTIONS) && (current_settings.number_defined_df  == 0))
                  current_ekran.index_position++;
                if ((current_ekran.index_position == INDEX_OF_DEFINED_TRIGGERS) && (current_settings.number_defined_dt  == 0))
                  current_ekran.index_position++;
                if ((current_ekran.index_position == INDEX_OF_DEFINED_AND) && (current_settings.number_defined_and  == 0))
                  current_ekran.index_position++;
                if ((current_ekran.index_position == INDEX_OF_DEFINED_OR) && (current_settings.number_defined_or  == 0))
                  current_ekran.index_position++;
                if ((current_ekran.index_position == INDEX_OF_DEFINED_XOR) && (current_settings.number_defined_xor  == 0))
                  current_ekran.index_position++;
                if ((current_ekran.index_position == INDEX_OF_DEFINED_NOT) && (current_settings.number_defined_not  == 0))
                  current_ekran.index_position++;
              }
              while (current_ekran.index_position >= MAX_ROW_FOR_EXTENDED_LIGIC);

              position_in_current_level_menu[EKRAN_EXTENDED_LIGIC] = current_ekran.index_position;
              //Формуємо екран вибору налаштувань розширеної логіки
              make_ekran_extended_logic();
            }
            else if ((current_ekran.current_level >= EKRAN_SET_RESET_DT1) && (current_ekran.current_level <= EKRAN_SET_RESET_DT4))
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_LIST_SET_RESET_DT) current_ekran.index_position = 0;
              position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;
              //Формуємо екран заголовків активація-деактивація опреділювальних триґерів
              make_ekran_set_reset_trigger();
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

              //Формуємо екран відображення записів
              make_ekran_list_records_registrator(type_registrator);
            }
            else if (current_ekran.current_level == EKRAN_TITLES_DIGITAL_REGISTRATOR)
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_TITLES_DIGITAL_REGISTRATOR) current_ekran.index_position = 0;
              position_in_current_level_menu[EKRAN_TITLES_DIGITAL_REGISTRATOR] = current_ekran.index_position;
              //Формуємо екран відображення заголовків груп для дискретного реєстратора
              make_ekran_list_titles_for_record_of_digital_registrator();
            }
            else if (current_ekran.current_level == EKRAN_DATA_LADEL_DR)
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_EKRAN_DATA_LABEL) current_ekran.index_position = 0;
              position_in_current_level_menu[EKRAN_DATA_LADEL_DR] = current_ekran.index_position;
              //Формуємо екран відображення мітки часу прочитаного запису дискретного реєстратора
              make_ekran_data_and_time_of_records_registrator(0);
            }
            else if (current_ekran.current_level == EKRAN_CHANGES_SIGNALS_DR)
            {
              //Формуємо екран відображення змін сигналів - записаних у дискретному реєстраторі
              make_ekran_changing_signals_digital_registrator();
            }
            else if (current_ekran.current_level == EKRAN_TITLES_PR_ERR_REGISTRATOR)
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_TITLES_PR_ERR_REGISTRATOR) current_ekran.index_position = 0;
              position_in_current_level_menu[EKRAN_TITLES_PR_ERR_REGISTRATOR] = current_ekran.index_position;
              //Формуємо екран відображення заголовків груп для реєстратора програмних подій
              make_ekran_list_titles_for_record_of_pr_err_registrator();
            }
            else if (current_ekran.current_level == EKRAN_DATA_LADEL_PR_ERR)
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_EKRAN_DATA_LABEL) current_ekran.index_position = 0;
              position_in_current_level_menu[EKRAN_DATA_LADEL_PR_ERR] = current_ekran.index_position;
              //Формуємо екран відображення мітки часу прочитаного запису реєстратора програмних подій
              make_ekran_data_and_time_of_records_registrator(1);
            }
            else if (current_ekran.current_level == EKRAN_CHANGES_DIAGNOSTICS_PR_ERR)
            {
              //Формуємо екран відображення змін діагностик - записаних у реєстраторі програмних подій
              make_ekran_changing_diagnostics_pr_err_registrator();
            }
            else if (current_ekran.current_level == EKRAN_DATA_LADEL_AR)
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_EKRAN_DATA_LABEL) current_ekran.index_position = 0;
              position_in_current_level_menu[EKRAN_DATA_LADEL_AR] = current_ekran.index_position;
              //Формуємо екран відображення мітки часу прочитаного запису аналогового реєстратора
              make_ekran_data_and_time_of_records_registrator(2);
            }
            
            //Очищаємо біт обновлення екрану
            new_state_keyboard &= (unsigned int)(~(1<<BIT_REWRITE));
          }
          else
          {
            if (new_state_keyboard == (1<<BIT_KEY_ENTER))
            {
              //Натиснута кнопка ENTER
              int temp_current_level = current_ekran.current_level;
              
              if (current_ekran.current_level == EKRAN_CHOOSE_SETTINGS_CTRL_PHASE)
              {
                //Натисну кнопка Enter у вікні вибору група1-...-групаN-настройки "Перевірки фазування"
                if(current_ekran.index_position == INDEX_ML_SETPOINT)
                {
                  //Запам'ятовуємо поперердній екран
                  //Переходимо на меню відображення уставок для "Перевірки фазування"
                  current_ekran.current_level = EKRAN_SETPOINT_CTRL_PHASE;
                }
                else if(current_ekran.index_position == INDEX_ML_TIMEOUT)
                {
                  //Запам'ятовуємо поперердній екран
                  //Переходимо на меню відображення витримок для "Перевірки фазування"
                  current_ekran.current_level = EKRAN_TIMEOUT_CTRL_PHASE;
                }
                else if (current_ekran.index_position == INDEX_ML_CONTROL)
                {
                  //Запам'ятовуємо поперердній екран
                  //Переходимо на меню відображення управлінської інформації для "Перевірки фазування"
                  current_ekran.current_level = EKRAN_CONTROL_CTRL_PHASE;
                } 

                current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
                current_ekran.edition = 0;
                current_ekran.cursor_on = 1;
                current_ekran.cursor_blinking_on = 0;
              }
              else if (current_ekran.current_level == EKRAN_LIST_ALARMS)
              {
                //Натисну кнопка Enter у вікні вибору сигналізації
                if(current_ekran.index_position == INDEX_ML_ALARMS_1)
                {
                  //Запам'ятовуємо поперердній екран
                  //Переходимо на меню відображення вибору налаштувань для сигналізації 1
                  current_ekran.current_level = EKRAN_CHOOSE_SETTINGS_ALARMS1;
                }
                else if(current_ekran.index_position == INDEX_ML_ALARMS_2)
                {
                  //Запам'ятовуємо поперердній екран
                  //Переходимо на меню відображення вибору налаштувань для сигналізації 2
                  current_ekran.current_level = EKRAN_CHOOSE_SETTINGS_ALARMS2;
                }
                current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
                current_ekran.edition = 0;
                current_ekran.cursor_on = 1;
                current_ekran.cursor_blinking_on = 0;
              }
              else if ((current_ekran.current_level >= EKRAN_CHOOSE_SETTINGS_ALARMS1) && (current_ekran.current_level <= EKRAN_CHOOSE_SETTINGS_ALARMS2))
              {
                //Натисну кнопка Enter у вікні вибору настройок сигналізації
                if (current_ekran.index_position == INDEX_ML_TIMEOUT_ALARMS)
                {
                  //Запам'ятовуємо поперердній екран
                  //Переходимо на меню відображення витримок для сигналізації
                  current_ekran.current_level = EKRAN_TIMEOUT_ALARMS1 + (current_ekran.current_level - EKRAN_CHOOSE_SETTINGS_ALARMS1);
                } 
                else if (current_ekran.index_position == INDEX_ML_CONTROL_ALARMS)
                {
                  //Запам'ятовуємо поперердній екран
                  //Переходимо на меню відображення управлінської інформації для сигналізації
                  current_ekran.current_level = EKRAN_CONTROL_ALARMS1 + (current_ekran.current_level - EKRAN_CHOOSE_SETTINGS_ALARMS1);
                } 
                else if (current_ekran.index_position == INDEX_ML_RANG_ALARMS)
                {
                  //Запам'ятовуємо поперердній екран
                  //Переходимо на меню відображення ранжування ББвимк.
                  current_ekran.current_level = EKRAN_RANGUVANNJA_ALARMS1 +  (current_ekran.current_level - EKRAN_CHOOSE_SETTINGS_ALARMS1);
                  //Для того, щоб при першому входженні завжди список починався із першої ранжованої функції обнуляємо цю позицію
                  position_in_current_level_menu[current_ekran.current_level] = 0;
                } 
                current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
                current_ekran.edition = 0;
                current_ekran.cursor_on = 1;
                current_ekran.cursor_blinking_on = 0;
              }
              else if (current_ekran.current_level == EKRAN_LEVEL_CHOOSE_PASSWORDS)
              {
                //Натисну кнопка Enter у вікні вибору паролів
//                if(current_ekran.index_position == INDEX_OF_PASSWORD1)
//                {
                  //Запам'ятовуємо поперердній екран
                  //Переходимо на меню зміни паролю
                  current_ekran.current_level = EKRAN_LEVEL_SET_NEW_PASSWORD;
//                }
                current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
                current_ekran.edition = 1;
              }
              else if (current_ekran.current_level == EKRAN_LIST_OUTPUTS_FOR_RANGUVANNJA)
              {
                //Запам'ятовуємо поперердній екран
                //Переходимо на меню відображення списку ранжованих функцій
                current_ekran.current_level = EKRAN_RANGUVANNJA_OUTPUT_1 + current_ekran.index_position;
                //Для того, щоб при першому входженні завжди список починався із першої ранжованої функції обнуляємо цю позицію
                position_in_current_level_menu[current_ekran.current_level] = 0;
                current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
                current_ekran.edition = 0;
              }
              else if (current_ekran.current_level == EKRAN_LIST_LEDS_FOR_RANGUVANNJA)
              {
                //Запам'ятовуємо поперердній екран
                //Переходимо на меню відображення списку ранжованих функцій
                current_ekran.current_level = EKRAN_RANGUVANNJA_LED_1 + current_ekran.index_position;
                //Для того, щоб при першому входженні завжди список починався із першої ранжованої функції обнуляємо цю позицію
                position_in_current_level_menu[current_ekran.current_level] = 0;
                current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
                current_ekran.edition = 0;
              }
              else if (current_ekran.current_level == EKRAN_CHOOSE_SETTINGS_UVV)
              {
                //Натисну кнопка Enter у вікні вибору вікна настройок УВВ
                if(current_ekran.index_position == INDEX_ML_UVV_DOPUSKT)
                {
                  //Запам'ятовуємо поперердній екран
                  //Переходимо на меню відображення списку дискретних входів
                  current_ekran.current_level = EKRAN_DOPUSK_DV_UVV;
                }
                else if(current_ekran.index_position == INDEX_ML_UVV_TYPE_INPUT_SIGNAL)
                {
                  //Запам'ятовуємо поперердній екран
                  //Переходимо на меню відображення списку дискретних входів
                  current_ekran.current_level = EKRAN_TYPE_INPUT_SIGNAL_UVV;
                }

                current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
                current_ekran.edition = 0;
              }
              else if (current_ekran.current_level == EKRAN_CHOSE_COMMUNICATION_PARAMETERS)
              {
                //Натисну кнопка Enter у вікні вибору вікна настройок комунікації
                if(current_ekran.index_position == INDEX_ML_CHCP_NAME)
                {
                  //Запам'ятовуємо поперердній екран
                  //Переходимо на меню відображення імені ячейки
                  current_ekran.current_level = EKRAN_VIEW_NAME_OF_CELL;
                }
                else if(current_ekran.index_position == INDEX_ML_CHCP_ADDRESS)
                {
                  //Запам'ятовуємо поперердній екран
                  //Переходимо на меню відображення мережевої адреси
                  current_ekran.current_level = EKRAN_ADDRESS;
                }
                else if(current_ekran.index_position == INDEX_ML_CHCP_SETTING_RS485)
                {
                  //Запам'ятовуємо поперердній екран
                  //Переходимо на меню відображення мережевої адреси
                  current_ekran.current_level = EKRAN_CHOSE_SETTING_RS485;
                }
                current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
                current_ekran.edition = 0;
              }
              else if (current_ekran.current_level == EKRAN_CHOSE_SETTING_RS485)
              {
                //Натисну кнопка Enter у вікні вибору вікна настройок RS-485
                if(current_ekran.index_position == INDEX_ML_CHSRS485_SPEED)
                {
                  //Запам'ятовуємо поперердній екран
                  //Переходимо на меню відображення швидкості обміну
                  current_ekran.current_level = EKRAN_VIEW_SPEED_RS485;
                }
                else if(current_ekran.index_position == INDEX_ML_CHSRS485_PARE_BIT)
                {
                  //Запам'ятовуємо поперердній екран
                  //Переходимо на меню відображення інформації по бітупаритету
                  current_ekran.current_level = EKRAN_VIEW_PARE_RS485;
                }
                else if(current_ekran.index_position == INDEX_ML_CHSRS485_NUMBER_STOP_BIT)
                {
                  //Запам'ятовуємо поперердній екран
                  //Переходимо на меню відображення інфрпмації по стоп-біту
                  current_ekran.current_level = EKRAN_VIEW_STOP_BITS_RS485;
                }
                else if(current_ekran.index_position == INDEX_ML_CHSRS485_TIMEOUT)
                {
                  //Запам'ятовуємо поперердній екран
                  //Переходимо на меню відображення інфрпмації по time-out наступного символу
                  current_ekran.current_level = EKRAN_VIEW_TIMEOUT_RS485;
                }
                current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
                current_ekran.edition = 0;
              }
              else if (current_ekran.current_level == EKRAN_VIEW_LIST_OF_REGISTRATORS)
              {
                if(current_ekran.index_position == INDEX_ML_DIGITAL_REGISTRATOR)
                {
                  //Запам'ятовуємо поперердній екран
                  //Переходимо на меню відображення списку ранжованих функцій для дискретного реєстратора
                  current_ekran.current_level = EKRAN_RANGUVANNJA_DIGITAL_REGISTRATOR;
                  //Для того, щоб при першому входженні завжди список починався із першої ранжованої функції обнуляємо цю позицію
                  position_in_current_level_menu[current_ekran.current_level] = 0;
                }
                else if(current_ekran.index_position == INDEX_ML_ANALOG_REGISTRATOR)
                {
                  //Запам'ятовуємо поперердній екран
                  //Переходимо на меню відображення списку настройок для аналогового реєстратора
                  current_ekran.current_level = EKRAN_VIEW_SETTINGS_OF_ANALOG_REGISTRATORS;
                }
                current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
                current_ekran.edition = 0;
              }
              else if (current_ekran.current_level == EKRAN_VIEW_SETTINGS_OF_ANALOG_REGISTRATORS)
              {
                if(current_ekran.index_position == INDEX_ML_SOURCE_ANALOG_REGISTRATOR)
                {
                  //Запам'ятовуємо поперердній екран
                  //Переходимо на меню відображення списку ранжованих функцій для аналогового реєстратора
                  current_ekran.current_level = EKRAN_RANGUVANNJA_ANALOG_REGISTRATOR;
                  //Для того, щоб при першому входженні завжди список починався із першої ранжованої функції обнуляємо цю позицію
                  position_in_current_level_menu[current_ekran.current_level] = 0;
                }
                else if(current_ekran.index_position == INDEX_ML_TIMEOUT_ANALOG_REGISTRATOR)
                {
                  //Запам'ятовуємо поперердній екран
                  //Переходимо на меню відображення витримок для аналогового реєстратора
                  current_ekran.current_level = EKRAN_TIMEOUT_ANALOG_REGISTRATOR;
                }
                current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
                current_ekran.edition = 0;
              }
              else if (current_ekran.current_level == EKRAN_EXTENDED_LIGIC)
              {
                if(current_ekran.index_position == INDEX_OF_GENERAL_PICKUP_EL)
                {
                  //Запам'ятовуємо поперердній екран
                  //Переходимо на меню відображення загальних уставок для розширеної логіки
                  current_ekran.current_level = EKRAN_GENERAL_PICKUPS_EL;
                }
                else if(current_ekran.index_position == INDEX_OF_DEFINED_TRIGGERS)
                {
                  //Запам'ятовуємо поперердній екран
                  //Переходимо на меню відображення списку опреділювальних триґерів
                  current_ekran.current_level = EKRAN_LIST_DT;
                }
                else if(current_ekran.index_position == INDEX_OF_DEFINED_AND)
                {
                  //Запам'ятовуємо поперердній екран
                  //Переходимо на меню відображення списку визначуваних "І"
                  current_ekran.current_level = EKRAN_LIST_D_AND;
                }
                else if(current_ekran.index_position == INDEX_OF_DEFINED_OR)
                {
                  //Запам'ятовуємо поперердній екран
                  //Переходимо на меню відображення списку визначуваних "АБО"
                  current_ekran.current_level = EKRAN_LIST_D_OR;
                }
                else if(current_ekran.index_position == INDEX_OF_DEFINED_XOR)
                {
                  //Запам'ятовуємо поперердній екран
                  //Переходимо на меню відображення списку визначуваних "Викл.АБО"
                  current_ekran.current_level = EKRAN_LIST_D_XOR;
                }
                else if(current_ekran.index_position == INDEX_OF_DEFINED_NOT)
                {
                  //Запам'ятовуємо поперердній екран
                  //Переходимо на меню відображення списку визначуваних "НЕ"
                  current_ekran.current_level = EKRAN_LIST_D_NOT;
                }
                current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
                current_ekran.edition = 0;
              }
              else if (current_ekran.current_level == EKRAN_LIST_DF_FOR_RANGUVANNJA)
              {
                //Запам'ятовуємо поперердній екран
                //Переходимо на меню відображення вибору типу джерел списку ранжованих функцій
                current_ekran.current_level = EKRAN_RANGUVANNJA_DF1 + current_ekran.index_position;
                //Для того, щоб при першому входженні завжди список починався із першої ранжованої функції обнуляємо цю позицію
                position_in_current_level_menu[current_ekran.current_level] = 0;
                current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
                current_ekran.edition = 0;
              }
              else if (current_ekran.current_level == EKRAN_LIST_DT)
              {
                //Запам'ятовуємо поперердній екран
                //Переходимо на меню відображення заголовків активація-деактивація опреділювальних триґерів
                current_ekran.current_level = EKRAN_SET_RESET_DT1 + current_ekran.index_position;
                current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
                current_ekran.edition = 0;
              }
              else if ((current_ekran.current_level >= EKRAN_SET_RESET_DT1) && (current_ekran.current_level <= EKRAN_SET_RESET_DT4))
              {
                //Запам'ятовуємо поперердній екран
                //Переходимо на меню відображення списку ранжованих функцій
                current_ekran.current_level = EKRAN_RANGUVANNJA_SET_DT1 + 2*(current_ekran.current_level - EKRAN_SET_RESET_DT1) + current_ekran.index_position;
                //Для того, щоб при першому входженні завжди список починався із першої ранжованої функції обнуляємо цю позицію
                position_in_current_level_menu[current_ekran.current_level] = 0;
                current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
                current_ekran.edition = 0;
              }
              else if (current_ekran.current_level == EKRAN_LIST_D_AND)
              {
                //Запам'ятовуємо поперердній екран
                //Переходимо на меню відображення списку ранжованих функцій
                current_ekran.current_level = EKRAN_RANGUVANNJA_D_AND1 + current_ekran.index_position;
                //Для того, щоб при першому входженні завжди список починався із першої ранжованої функції обнуляємо цю позицію
                position_in_current_level_menu[current_ekran.current_level] = 0;
                current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
                current_ekran.edition = 0;
              }
              else if (current_ekran.current_level == EKRAN_LIST_D_OR)
              {
                //Запам'ятовуємо поперердній екран
                //Переходимо на меню відображення списку ранжованих функцій
                current_ekran.current_level = EKRAN_RANGUVANNJA_D_OR1 + current_ekran.index_position;
                //Для того, щоб при першому входженні завжди список починався із першої ранжованої функції обнуляємо цю позицію
                position_in_current_level_menu[current_ekran.current_level] = 0;
                current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
                current_ekran.edition = 0;
              }
              else if (current_ekran.current_level == EKRAN_LIST_D_XOR)
              {
                //Запам'ятовуємо поперердній екран
                //Переходимо на меню відображення списку ранжованих функцій
                current_ekran.current_level = EKRAN_RANGUVANNJA_D_XOR1 + current_ekran.index_position;
                //Для того, щоб при першому входженні завжди список починався із першої ранжованої функції обнуляємо цю позицію
                position_in_current_level_menu[current_ekran.current_level] = 0;
                current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
                current_ekran.edition = 0;
              }
              else if (current_ekran.current_level == EKRAN_LIST_D_NOT)
              {
                //Запам'ятовуємо поперердній екран
                //Переходимо на меню відображення списку ранжованих функцій
                current_ekran.current_level = EKRAN_RANGUVANNJA_D_NOT1 + current_ekran.index_position;
                //Для того, щоб при першому входженні завжди список починався із першої ранжованої функції обнуляємо цю позицію
                position_in_current_level_menu[current_ekran.current_level] = 0;
                current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
                current_ekran.edition = 0;
              }
              else if (
                       (current_ekran.current_level == EKRAN_LIST_ANALOG_REGISTRATOR_RECORDS) &&
                       (info_rejestrator_ar.number_records > 0) &&
                       ((clean_rejestrators & CLEAN_AR) == 0)
                      )
              {
                //Натисну кнопка Enter у вікні вибору запису аналогового реєстратора і реально є записи для відображення
                
                //Запам'ятовуємо, який номер запису дискретного реєстратори ми намагаємося продивитися
                number_record_of_ar_for_menu = current_ekran.index_position;
                
                //Подаємо команду зчитати дані у бувер пам'яті
                control_tasks_dataflash |= TASK_MAMORY_READ_DATAFLASH_FOR_AR_MENU;
                
                //Виставляємо повідомлення, що поки дані не будуть зчитані, то екран треба перерисовувати кожну секунду
                rewrite_ekran_once_more = 1;
                //Виставляємо новий екран, який треба відобразити на РКІ
                current_ekran.current_level = EKRAN_DATA_LADEL_AR;
                current_ekran.index_position = 0; //При відкриванні цих вікон з старших розділів меню завжди треба попадати на найновіший запис
                current_ekran.edition = 0;
              }
              else if (
                       (current_ekran.current_level == EKRAN_LIST_DIGITAL_REGISTRATOR_RECORDS) && 
                       (info_rejestrator_dr.number_records > 0) &&
                       ((clean_rejestrators & CLEAN_DR) == 0)
                      )
              {
                //Натисну кнопка Enter у вікні вибору запису дискретного реєстратора і реально є записи для відображення
                
                //Запам'ятовуємо, який номер запису дискретного реєстратори ми намагаємося продивитися
                number_record_of_dr_for_menu = current_ekran.index_position;
                
                //Виставляємо першу частину запису
                part_reading_dr_from_dataflash_for_menu = 0;
                //Подаємо команду зчитати дані у бувер пам'яті
                control_tasks_dataflash |= TASK_MAMORY_READ_DATAFLASH_FOR_DR_MENU;
                
                //Виставляємо повідомлення, що поки дані не будуть зчитані, то екран треба перерисовувати кожну секунду
                rewrite_ekran_once_more = 1;
                //Виставляємо новий екран, який треба відобразити на РКІ
                current_ekran.current_level = EKRAN_TITLES_DIGITAL_REGISTRATOR;
                current_ekran.index_position = 0; //При відкриванні цих вікон з старших розділів меню завжди треба попадати на найновіший запис
                current_ekran.edition = 0;
              }
              else if (current_ekran.current_level == EKRAN_TITLES_DIGITAL_REGISTRATOR)
              {
                //Натисну кнопка Enter у вікні вибору груп інформації по запису дискретного реєстра
                if (rewrite_ekran_once_more == 0)
                {
                  if(current_ekran.index_position == INDEX_ML_TITLE_DR_DATA_AND_TIME)
                  {
                    //Переходимо на меню відображення мітки часу запису дискретного реєстратора
                    current_ekran.current_level = EKRAN_DATA_LADEL_DR;
                  }
                  else if(current_ekran.index_position == INDEX_ML_TITLE_DR_CHANGES_SIGNALS)
                  {
                    //Переходимо на меню відображення зафіксованих змін сигналів у запису дискретного реєстратора
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
                //Натисну кнопка Enter у вікні вибору запису реєстратора програмних подій і реально є записи для відображення
                
                //Запам'ятовуємо, який номер запису реєстратора програмних подій ми намагаємося продивитися
                number_record_of_pr_err_into_menu = current_ekran.index_position;
                
                //Подаємо команду зчитати дані у бувер пам'яті
                control_tasks_dataflash |= TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_MENU;
                
                //Виставляємо повідомлення, що поки дані не будуть зчитані, то екран треба перерисовувати кожну секунду
                rewrite_ekran_once_more = 1;
                //Виставляємо новий екран, який треба відобразити на РКІ
                current_ekran.current_level = EKRAN_TITLES_PR_ERR_REGISTRATOR;
                current_ekran.index_position = 0; //При відкриванні цих вікон з старших розділів меню завжди треба попадати на найновіший запис
                current_ekran.edition = 0;
              }
              else if (current_ekran.current_level == EKRAN_TITLES_PR_ERR_REGISTRATOR)
              {
                //Натисну кнопка Enter у вікні вибору груп інформації по запису дискретного реєстра
                if (rewrite_ekran_once_more == 0)
                {
                  if(current_ekran.index_position == INDEX_ML_TITLE_PR_ERR_DATA_AND_TIME)
                  {
                    //Переходимо на меню відображення мітки часу запису реєстратора програмних подій
                    current_ekran.current_level = EKRAN_DATA_LADEL_PR_ERR;
                  }
                  else if(current_ekran.index_position == INDEX_ML_TITLE_PR_ERR_CHANGES_DIAGNOSTICS)
                  {
                    //Переходимо на меню відображення зафіксованих змін діагностик у запису реєстратора програмних подій
                    current_ekran.current_level = EKRAN_CHANGES_DIAGNOSTICS_PR_ERR;
                  }
                  current_ekran.index_position = 0;
                  current_ekran.edition = 0;
                }
              }
             
              //У разі, якщо текучий екран змінився, то запам'ятовуємо екран в який требе буде повернутися
              if (temp_current_level != current_ekran.current_level) 
              {
                previous_level_in_current_level_menu[current_ekran.current_level] = temp_current_level;
              
                if ((current_ekran.current_level == EKRAN_LEVEL_SET_NEW_PASSWORD) && (current_settings.password != 0))
                {
                  //У випавдку, якщо ми намагаємося перейти у вікно зміни паролю, то спочатку треба запитати старий пароль доступу, якщо він встановлений
                  if (current_ekran.current_level == EKRAN_LEVEL_SET_NEW_PASSWORD) 
                  {
                    current_ekran.current_level = EKRAN_LEVEL_PASSWORD;
                    previous_level_in_current_level_menu[current_ekran.current_level] = EKRAN_LEVEL_SET_NEW_PASSWORD;
                  }
                  else
                  {
                    //Теоретично цього ніколи не мало б бути
                    total_error_sw_fixed(71);
                  }
                  current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
                  current_ekran.cursor_on = 1;
                  current_ekran.cursor_blinking_on = 1;
                }
              }

              //Очистити сигналізацію, що натиснута кнопка 
              new_state_keyboard &= (unsigned int)(~(1<<BIT_KEY_ENTER));
              //Виставляємо команду на обновлекння нового екрану
              new_state_keyboard |= (1<<BIT_REWRITE);
            }
            else if (new_state_keyboard == (1<<BIT_KEY_ESC))
            {
              //Переходимо у попереднє меню
              current_ekran.current_level = previous_level_in_current_level_menu[current_ekran.current_level];
              current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
              current_ekran.edition = 0;

              //Виставляємо команду на обновлекння нового екрану
              new_state_keyboard |= (1<<BIT_REWRITE);
              //Очистити сигналізацію, що натиснута кнопка 
              new_state_keyboard &= (unsigned int)(~(1<<BIT_KEY_ESC));
            }
            else if (new_state_keyboard == (1<<BIT_KEY_UP))
            {
              //Натиснута кнопка UP
              if (
                  (current_ekran.current_level == EKRAN_CHOOSE_SETTINGS_CTRL_PHASE)
                 )   
              {
                if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_CHOSE_SETTINGS_ANY_PROTECTION - 1;
                position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;
                //Формуємо екран уставки-витримки-настройки для всіх захистів
                make_ekran_chose_settings_any_protection();
              }
              else if (current_ekran.current_level == EKRAN_LIST_ALARMS)
              {
                if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_LIST_ALARMS - 1;
              
                position_in_current_level_menu[EKRAN_LIST_ALARMS] = current_ekran.index_position;

                //Формуємо екран вибору сигналізації
                make_ekran_choose_list_alarms();
              }
              else if ((current_ekran.current_level >= EKRAN_CHOOSE_SETTINGS_ALARMS1) && (current_ekran.current_level <= EKRAN_CHOOSE_SETTINGS_ALARMS2))
              {
                if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_CHOOSE_SETTINGS_ALARMS - 1;
              
                position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;

                //Формуємо екран вибору налаштувань для сигналізації
                make_ekran_choose_settings_alarms();
              }
              else if (current_ekran.current_level == EKRAN_LEVEL_CHOOSE_PASSWORDS)
              {
                if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_CHOOSE_PASSWORDS - 1;
                position_in_current_level_menu[EKRAN_LEVEL_CHOOSE_PASSWORDS] = current_ekran.index_position;
                //Формуємо екран заголовків паролів
                make_ekran_chose_passwords();
              }
              else if (current_ekran.current_level == EKRAN_CHOOSE_SETTINGS_UVV)
              {
                if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_CHOSE_SETTINGS_UVV - 1;
                position_in_current_level_menu[EKRAN_CHOOSE_SETTINGS_UVV] = current_ekran.index_position;
                //Формуємо екран вибору настройок УВВ
                make_ekran_chose_settings_uvv();
              }
              else if (current_ekran.current_level == EKRAN_CHOSE_COMMUNICATION_PARAMETERS)
              {
                if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_CHOSE_COMMUNICATION_PARAMETERS - 1;
                position_in_current_level_menu[EKRAN_CHOSE_COMMUNICATION_PARAMETERS] = current_ekran.index_position;
                //Формуємо екран вибору настройок парамеирів комунікації
                make_ekran_chose_communication_parameters();
              }
              else if (current_ekran.current_level == EKRAN_VIEW_NAME_OF_CELL)
              {
                current_ekran.index_position -= MAX_ROW_LCD;
                if(current_ekran.index_position < 0) current_ekran.index_position = (MAX_ROW_FOR_VIEW_NAME_OF_CELL - 1) & (~(MAX_ROW_LCD - 1));
                position_in_current_level_menu[EKRAN_VIEW_NAME_OF_CELL] = current_ekran.index_position;
                //Формуємо екран відображення імені ячейки
                make_ekran_name_of_cell();
              }
              else if (current_ekran.current_level == EKRAN_CHOSE_SETTING_RS485)
              {
                if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_CHOSE_SETTING_RS485 - 1;
                position_in_current_level_menu[EKRAN_CHOSE_SETTING_RS485] = current_ekran.index_position;
               //Формуємо екран відображення списку настройок для інтерфейсу RS-485
               make_ekran_chose_setting_rs485();
              }
              else if (current_ekran.current_level == EKRAN_VIEW_LIST_OF_REGISTRATORS)
              {
                if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_LIST_OF_REGISTRATORS - 1;
                position_in_current_level_menu[EKRAN_VIEW_LIST_OF_REGISTRATORS] = current_ekran.index_position;
                //Формуємо екран вибору реєстратора
                make_ekran_chose_registrators();
              }
              else if (current_ekran.current_level == EKRAN_VIEW_SETTINGS_OF_ANALOG_REGISTRATORS)
              {
                if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_SETTINGS_OF_ANALOG_REGISTRATOR - 1;
                position_in_current_level_menu[EKRAN_VIEW_SETTINGS_OF_ANALOG_REGISTRATORS] = current_ekran.index_position;
                //Формуємо екран вибору настройок аналогового реєстратора
                make_ekran_settings_analog_registrators();
              }
              else if (current_ekran.current_level == EKRAN_EXTENDED_LIGIC)
              {
                current_ekran.index_position--;
                do
                {
                  if(current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_EXTENDED_LIGIC - 1;

                  if ((current_ekran.index_position == INDEX_OF_DEFINED_NOT) && (current_settings.number_defined_not  == 0))
                    current_ekran.index_position--;
                  if ((current_ekran.index_position == INDEX_OF_DEFINED_XOR) && (current_settings.number_defined_xor  == 0))
                    current_ekran.index_position--;
                  if ((current_ekran.index_position == INDEX_OF_DEFINED_OR) && (current_settings.number_defined_or  == 0))
                    current_ekran.index_position--;
                  if ((current_ekran.index_position == INDEX_OF_DEFINED_AND) && (current_settings.number_defined_and  == 0))
                    current_ekran.index_position--;
                  if ((current_ekran.index_position == INDEX_OF_DEFINED_TRIGGERS) && (current_settings.number_defined_dt  == 0))
                    current_ekran.index_position--;
                  if ((current_ekran.index_position == INDEX_OF_DEFINED_FUNCTIONS) && (current_settings.number_defined_df  == 0))
                    current_ekran.index_position--;
                }
                while (current_ekran.index_position < 0);
                
                position_in_current_level_menu[EKRAN_EXTENDED_LIGIC] = current_ekran.index_position;
                //Формуємо екран вибору налаштувань розширеної логіки
                make_ekran_extended_logic();
              }
              else if ((current_ekran.current_level >= EKRAN_SET_RESET_DT1) && (current_ekran.current_level <= EKRAN_SET_RESET_DT4))
              {
                if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_LIST_SET_RESET_DT - 1;
                position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;
                //Формуємо екран заголовків активація-деактивація опреділювальних триґерів
                make_ekran_set_reset_trigger();
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

                //Формуємо екран відображення записів
                make_ekran_list_records_registrator(type_registrator);
              }
              else if (current_ekran.current_level == EKRAN_TITLES_DIGITAL_REGISTRATOR)
              {
                if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_TITLES_DIGITAL_REGISTRATOR - 1;
                position_in_current_level_menu[EKRAN_TITLES_DIGITAL_REGISTRATOR] = current_ekran.index_position;
                //Формуємо екран відображення заголовків груп для дискретного реєстратора
                make_ekran_list_titles_for_record_of_digital_registrator();
              }
              else if (current_ekran.current_level == EKRAN_DATA_LADEL_DR)
              {
                if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_EKRAN_DATA_LABEL - 1;
                position_in_current_level_menu[EKRAN_DATA_LADEL_DR] = current_ekran.index_position;
                //Формуємо екран відображення мітки часу прочитаного запису дискретного реєстратора
                make_ekran_data_and_time_of_records_registrator(0);
              }
              else if (current_ekran.current_level == EKRAN_CHANGES_SIGNALS_DR)
              {
                current_ekran.index_position--;
                //Формуємо екран відображення змін сигналів - записаних у дискретному реєстраторі
                make_ekran_changing_signals_digital_registrator();
              }
              else if (current_ekran.current_level == EKRAN_TITLES_PR_ERR_REGISTRATOR)
              {
                if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_TITLES_PR_ERR_REGISTRATOR - 1;
                position_in_current_level_menu[EKRAN_TITLES_PR_ERR_REGISTRATOR] = current_ekran.index_position;
                //Формуємо екран відображення заголовків груп для дискретного реєстратора
                make_ekran_list_titles_for_record_of_pr_err_registrator();
              }
              else if (current_ekran.current_level == EKRAN_DATA_LADEL_PR_ERR)
              {
                if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_EKRAN_DATA_LABEL - 1;
                position_in_current_level_menu[EKRAN_DATA_LADEL_PR_ERR] = current_ekran.index_position;
                //Формуємо екран відображення мітки часу прочитаного запису реєстратора програмних подій
                make_ekran_data_and_time_of_records_registrator(1);
              }
              else if (current_ekran.current_level == EKRAN_CHANGES_DIAGNOSTICS_PR_ERR)
              {
                current_ekran.index_position--;
                //Формуємо екран відображення змін діагностик - записаних у реєстраторі програмних подій
                make_ekran_changing_diagnostics_pr_err_registrator();
              }
              else if (current_ekran.current_level == EKRAN_DATA_LADEL_AR)
              {
                if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_EKRAN_DATA_LABEL - 1;
                position_in_current_level_menu[EKRAN_DATA_LADEL_AR] = current_ekran.index_position;
                //Формуємо екран відображення мітки часу прочитаного запису аналогового реєстратора
                make_ekran_data_and_time_of_records_registrator(2);
              }
              
              //Очистити сигналізацію, що натиснута кнопка 
              new_state_keyboard &= (unsigned int)(~(1<<BIT_KEY_UP));
            }
            else if (new_state_keyboard == (1<<BIT_KEY_DOWN))
            {
              //Натиснута кнопка DOWN
              if (
                  (current_ekran.current_level == EKRAN_CHOOSE_SETTINGS_CTRL_PHASE)
                 )   
              {
                if(++current_ekran.index_position >= MAX_ROW_FOR_CHOSE_SETTINGS_ANY_PROTECTION) current_ekran.index_position = 0;
                position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;

                //Формуємо екран уставки-витримки-настройки для всіх захистів
                make_ekran_chose_settings_any_protection();
              }
              else if (current_ekran.current_level == EKRAN_LIST_ALARMS)
              {
                if(++current_ekran.index_position >= MAX_ROW_FOR_LIST_ALARMS) current_ekran.index_position = 0;
              
                position_in_current_level_menu[EKRAN_LIST_ALARMS] = current_ekran.index_position;

                //Формуємо екран вибору сигналізацій
                make_ekran_choose_list_alarms();
              }
              else if ((current_ekran.current_level >= EKRAN_CHOOSE_SETTINGS_ALARMS1) && (current_ekran.current_level <= EKRAN_CHOOSE_SETTINGS_ALARMS2))
              {
                if(++current_ekran.index_position >= MAX_ROW_FOR_CHOOSE_SETTINGS_ALARMS) current_ekran.index_position = 0;
              
                position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;

                //Формуємо екран вибору налаштувань сигналізації
                make_ekran_choose_settings_alarms();
              }
              else if (current_ekran.current_level == EKRAN_LEVEL_CHOOSE_PASSWORDS)
              {
                //Натиснута кнопка DOWN
                if(++current_ekran.index_position >= MAX_ROW_FOR_CHOOSE_PASSWORDS) current_ekran.index_position = 0;
                position_in_current_level_menu[EKRAN_LEVEL_CHOOSE_PASSWORDS] = current_ekran.index_position;
            
                //Формуємо екран заголовків паролів
                make_ekran_chose_passwords();
              }
              else if (current_ekran.current_level == EKRAN_CHOOSE_SETTINGS_UVV)
              {
                if(++current_ekran.index_position >= MAX_ROW_FOR_CHOSE_SETTINGS_UVV) current_ekran.index_position = 0;
                position_in_current_level_menu[EKRAN_CHOOSE_SETTINGS_UVV] = current_ekran.index_position;
                //Формуємо екран вибору настройок УВВ
                make_ekran_chose_settings_uvv();
              }
              else if (current_ekran.current_level == EKRAN_CHOSE_COMMUNICATION_PARAMETERS)
              {
                if(++current_ekran.index_position >= MAX_ROW_FOR_CHOSE_COMMUNICATION_PARAMETERS) current_ekran.index_position = 0;
                position_in_current_level_menu[EKRAN_CHOSE_COMMUNICATION_PARAMETERS] = current_ekran.index_position;
                //Формуємо екран вибору настройок парамеирів комунікації
                make_ekran_chose_communication_parameters();
              }
              else if (current_ekran.current_level == EKRAN_VIEW_NAME_OF_CELL)
              {
                current_ekran.index_position += MAX_ROW_LCD;
                if(current_ekran.index_position >= MAX_ROW_FOR_VIEW_NAME_OF_CELL) current_ekran.index_position = 0;
                position_in_current_level_menu[EKRAN_VIEW_NAME_OF_CELL] = current_ekran.index_position;
                //Формуємо екран відображення імені ячейки
                make_ekran_name_of_cell();
              }
              else if (current_ekran.current_level == EKRAN_CHOSE_SETTING_RS485)
              {
                if(++current_ekran.index_position >= MAX_ROW_FOR_CHOSE_SETTING_RS485) current_ekran.index_position = 0;
                position_in_current_level_menu[EKRAN_CHOSE_SETTING_RS485] = current_ekran.index_position;
               //Формуємо екран відображення списку настройок для інтерфейсу RS-485
                make_ekran_chose_setting_rs485();
              }
              else if (current_ekran.current_level == EKRAN_VIEW_LIST_OF_REGISTRATORS)
              {
                if(++current_ekran.index_position >= MAX_ROW_FOR_LIST_OF_REGISTRATORS) current_ekran.index_position = 0;
                position_in_current_level_menu[EKRAN_VIEW_LIST_OF_REGISTRATORS] = current_ekran.index_position;
                //Формуємо екран вибору реєстратора
                make_ekran_chose_registrators();
              }
              else if (current_ekran.current_level == EKRAN_VIEW_SETTINGS_OF_ANALOG_REGISTRATORS)
              {
                if(++current_ekran.index_position >= MAX_ROW_FOR_SETTINGS_OF_ANALOG_REGISTRATOR) current_ekran.index_position = 0;
                position_in_current_level_menu[EKRAN_VIEW_SETTINGS_OF_ANALOG_REGISTRATORS] = current_ekran.index_position;
                //Формуємо екран вибору настройок аналогового реєстратора
                make_ekran_settings_analog_registrators();
              }
              else if (current_ekran.current_level == EKRAN_EXTENDED_LIGIC)
              {
                current_ekran.index_position++;
                do
                {
                  if(current_ekran.index_position >= MAX_ROW_FOR_EXTENDED_LIGIC) current_ekran.index_position = 0;
                
                  if ((current_ekran.index_position == INDEX_OF_DEFINED_FUNCTIONS) && (current_settings.number_defined_df == 0))
                    current_ekran.index_position++;
                  if ((current_ekran.index_position == INDEX_OF_DEFINED_TRIGGERS) && (current_settings.number_defined_dt == 0))
                    current_ekran.index_position++;
                  if ((current_ekran.index_position == INDEX_OF_DEFINED_AND) && (current_settings.number_defined_and == 0))
                    current_ekran.index_position++;
                  if ((current_ekran.index_position == INDEX_OF_DEFINED_OR) && (current_settings.number_defined_or == 0))
                    current_ekran.index_position++;
                  if ((current_ekran.index_position == INDEX_OF_DEFINED_XOR) && (current_settings.number_defined_xor == 0))
                    current_ekran.index_position++;
                  if ((current_ekran.index_position == INDEX_OF_DEFINED_NOT) && (current_settings.number_defined_not == 0))
                    current_ekran.index_position++;
                }
                while (current_ekran.index_position >= MAX_ROW_FOR_EXTENDED_LIGIC);
              
                position_in_current_level_menu[EKRAN_EXTENDED_LIGIC] = current_ekran.index_position;
                //Формуємо екран вибору налаштувань розширеної логіки
                make_ekran_extended_logic();
              }
              else if ((current_ekran.current_level >= EKRAN_SET_RESET_DT1) && (current_ekran.current_level <= EKRAN_SET_RESET_DT4))
              {
                if(++current_ekran.index_position >= MAX_ROW_FOR_LIST_SET_RESET_DT) current_ekran.index_position = 0;
                position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;
                //Формуємо екран заголовків активація-деактивація опреділювальних триґерів
                make_ekran_set_reset_trigger();
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
                //Формуємо екран відображення записів
                make_ekran_list_records_registrator(type_registrator);
              }
              else if (current_ekran.current_level == EKRAN_TITLES_DIGITAL_REGISTRATOR)
              {
                if(++current_ekran.index_position >= MAX_ROW_FOR_TITLES_DIGITAL_REGISTRATOR) current_ekran.index_position = 0;
                position_in_current_level_menu[EKRAN_TITLES_DIGITAL_REGISTRATOR] = current_ekran.index_position;
                //Формуємо екран відображення заголовків груп для дискретного реєстратора
                make_ekran_list_titles_for_record_of_digital_registrator();
              }
              else if (current_ekran.current_level == EKRAN_DATA_LADEL_DR)
              {
                if(++current_ekran.index_position >= MAX_ROW_FOR_EKRAN_DATA_LABEL) current_ekran.index_position =  0;
                position_in_current_level_menu[EKRAN_DATA_LADEL_DR] = current_ekran.index_position;
                //Формуємо екран відображення мітки часу прочитаного запису дискретного реєстратора
                make_ekran_data_and_time_of_records_registrator(0);
              }
              else if (current_ekran.current_level == EKRAN_CHANGES_SIGNALS_DR)
              {
                current_ekran.index_position++;
                //Формуємо екран відображення змін сигналів - записаних у дискретному реєстраторі
                make_ekran_changing_signals_digital_registrator();
              }
              else if (current_ekran.current_level == EKRAN_TITLES_PR_ERR_REGISTRATOR)
              {
                if(++current_ekran.index_position >= MAX_ROW_FOR_TITLES_PR_ERR_REGISTRATOR) current_ekran.index_position = 0;
                position_in_current_level_menu[EKRAN_TITLES_PR_ERR_REGISTRATOR] = current_ekran.index_position;
                //Формуємо екран відображення заголовків груп для дискретного реєстратора
                make_ekran_list_titles_for_record_of_pr_err_registrator();
              }
              else if (current_ekran.current_level == EKRAN_DATA_LADEL_PR_ERR)
              {
                if(++current_ekran.index_position >= MAX_ROW_FOR_EKRAN_DATA_LABEL) current_ekran.index_position =  0;
                position_in_current_level_menu[EKRAN_DATA_LADEL_PR_ERR] = current_ekran.index_position;
                //Формуємо екран відображення мітки часу прочитаного запису реєстратора програмних подій
                make_ekran_data_and_time_of_records_registrator(1);
              }
              else if (current_ekran.current_level == EKRAN_CHANGES_DIAGNOSTICS_PR_ERR)
              {
                current_ekran.index_position++;
                //Формуємо екран відображення змін діагностик - записаних у реєстраторі програмних подій
                make_ekran_changing_diagnostics_pr_err_registrator();
              }
              else if (current_ekran.current_level == EKRAN_DATA_LADEL_AR)
              {
                if(++current_ekran.index_position >= MAX_ROW_FOR_EKRAN_DATA_LABEL) current_ekran.index_position =  0;
                position_in_current_level_menu[EKRAN_DATA_LADEL_AR] = current_ekran.index_position;
                //Формуємо екран відображення мітки часу прочитаного запису аналогового реєстратора
                make_ekran_data_and_time_of_records_registrator(2);
              }
            
              //Очистити сигналізацію, що натиснута кнопка 
              new_state_keyboard &= (unsigned int)(~(1<<BIT_KEY_DOWN));
            }
            else
            {
              //Натиснуто зразу декілька кнопок - це є невизначена ситуація, тому скидаємо сигналізацію про натиснуті кнопки і чекаємо знову
              unsigned int temp_data = new_state_keyboard;
              new_state_keyboard &= ~temp_data;
            }
          }
        }
        break;
      }
/****************************************************************************************************************************************/ 

/******************************************************************************************************************************************/      
    case EKRAN_SETPOINT_CTRL_PHASE:
    case EKRAN_TIMEOUT_CTRL_PHASE:
    case EKRAN_CONTROL_CTRL_PHASE:
    case EKRAN_TIMEOUT_ALARMS1:
    case EKRAN_TIMEOUT_ALARMS2:
    case EKRAN_CONTROL_ALARMS1:
    case EKRAN_CONTROL_ALARMS2:
    case EKRAN_DOPUSK_DV_UVV:
    case EKRAN_TYPE_INPUT_SIGNAL_UVV:
    case EKRAN_ADDRESS:
    case EKRAN_VIEW_SPEED_RS485:
    case EKRAN_VIEW_PARE_RS485:
    case EKRAN_VIEW_STOP_BITS_RS485:
    case EKRAN_VIEW_TIMEOUT_RS485:
    case EKRAN_GENERAL_PICKUPS_EL:
    case EKRAN_LIST_TYPE_DF:
    case EKRAN_TIMEOUT_ANALOG_REGISTRATOR:
    case EKRAN_VIEW_SETTING_LANGUAGE:
      {
        //Очищаємо всі біти краім упралінських
        unsigned int maska_keyboard_bits = (1<<BIT_KEY_ENTER)| (1<<BIT_KEY_ESC)|(1<<BIT_REWRITE);
        
        if (current_ekran.edition == 1)
          maska_keyboard_bits |= (1<<BIT_KEY_RIGHT) | (1<<BIT_KEY_LEFT) | (1<<BIT_KEY_UP)|(1<<BIT_KEY_DOWN);
        else if (current_ekran.edition == 0)
          maska_keyboard_bits |= (1<<BIT_KEY_UP)|(1<<BIT_KEY_DOWN);
        
        new_state_keyboard &= maska_keyboard_bits;
        //Дальше виконуємо дії, якщо натиснута кнопка на яку треба реагівати, або стоїть команда обновити екран
        if (new_state_keyboard !=0)
        {
          //Пріоритет стоїть на обновлені екрану
          if((new_state_keyboard & (1<<BIT_REWRITE)) !=0)
          {
            if(
               (current_ekran.current_level == EKRAN_SETPOINT_CTRL_PHASE)
              )   
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_SETPOINT_CTRL_PHASE) current_ekran.index_position = 0;
              position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;

              //Формуємо екран уставок "Перевірки фазування"
              make_ekran_setpoint_ctrl_phase();
            }
            else if(
                    (current_ekran.current_level == EKRAN_TIMEOUT_CTRL_PHASE)
                   )   
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_TIMEOUT_CTRL_PHASE) current_ekran.index_position = 0;
              position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;

              //Формуємо екран витримок "Перевірки фазування"
              make_ekran_timeout_ctrl_phase();
            }
            else if(current_ekran.current_level == EKRAN_CONTROL_CTRL_PHASE)
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_CONTROL_CTRL_PHASE) current_ekran.index_position = 0;
              position_in_current_level_menu[EKRAN_CONTROL_CTRL_PHASE] = current_ekran.index_position;
              //Формуємо екран управлінської інформації для "Перевірки фазування"
              make_ekran_control_ctrl_phase();
            }
            else if((current_ekran.current_level >= EKRAN_TIMEOUT_ALARMS1) && (current_ekran.current_level <= EKRAN_TIMEOUT_ALARMS2))
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_TIMEOUT_ALARMS) current_ekran.index_position = 0;
              position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;
              //Формуємо екран витримок сигналізації
              make_ekran_timeout_alarms(current_ekran.current_level - EKRAN_TIMEOUT_ALARMS1);
            }
            else if((current_ekran.current_level >= EKRAN_CONTROL_ALARMS1) && (current_ekran.current_level <= EKRAN_CONTROL_ALARMS2))
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_CONTROL_ALARMS) current_ekran.index_position = 0;
              position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;
              //Формуємо екран управлінської інформації для сигналізації
              make_ekran_control_alarms(current_ekran.current_level - EKRAN_CONTROL_ALARMS1);
            }
            else if(current_ekran.current_level == EKRAN_DOPUSK_DV_UVV)
            {
              if(current_ekran.index_position >= NUMBER_INPUTS) current_ekran.index_position = 0;
              position_in_current_level_menu[EKRAN_DOPUSK_DV_UVV] = current_ekran.index_position;
              //Формуємо екран інфтрмації по допусках ДВ
              make_ekran_dopusk_dv();
            }
            else if (current_ekran.current_level == EKRAN_TYPE_INPUT_SIGNAL_UVV)
            {
              if(current_ekran.index_position >= NUMBER_INPUTS) current_ekran.index_position = 0;
              position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;
              //Формуємо екран управлінської інформації для УВВ
              make_ekran_type_input_uvv();
            }
            else if(current_ekran.current_level == EKRAN_ADDRESS)
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_ADDRESS) current_ekran.index_position = 0;
              position_in_current_level_menu[EKRAN_ADDRESS] = current_ekran.index_position;
              //Формуємо екран інфтрмації по комунікаційній адресі
              make_ekran_address();
            }
            else if(current_ekran.current_level == EKRAN_VIEW_SPEED_RS485)
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_VIEW_SPEED_INTERFACE) current_ekran.index_position = 0;
              position_in_current_level_menu[EKRAN_VIEW_SPEED_RS485] = current_ekran.index_position;
              //Формуємо екран інформації по швидкості обміну
              make_ekran_speed_interface();
            }
            else if(current_ekran.current_level == EKRAN_VIEW_PARE_RS485)
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_VIEW_PARE_INTERFACE) current_ekran.index_position = 0;
              position_in_current_level_menu[EKRAN_VIEW_PARE_RS485] = current_ekran.index_position;
              //Формуємо екран інформації по контролю парності
              make_ekran_pare_interface();
            }
            else if(current_ekran.current_level == EKRAN_VIEW_STOP_BITS_RS485)
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_VIEW_STOP_BITS_INTERFACE) current_ekran.index_position = 0;
              position_in_current_level_menu[EKRAN_VIEW_STOP_BITS_RS485] = current_ekran.index_position;
              //Формуємо екран інформації по кількості стопових біт
              make_ekran_stopbits_interface();
            }
            else if(current_ekran.current_level == EKRAN_VIEW_TIMEOUT_RS485)
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_VIEW_TIMEOUT_INTERFACE) current_ekran.index_position = 0;
              position_in_current_level_menu[EKRAN_VIEW_TIMEOUT_RS485] = current_ekran.index_position;
              //Формуємо екран інформації по time-out наступного символу
              make_ekran_timeout_interface();
            }
            else if(current_ekran.current_level == EKRAN_GENERAL_PICKUPS_EL)
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_GENERAL_PICKUPS_EL) current_ekran.index_position = 0;
              position_in_current_level_menu[EKRAN_GENERAL_PICKUPS_EL] = current_ekran.index_position;
              //Формуємо екран відображення загальних витримок для розширеної логіки
              make_ekran_general_pickups_el();
            }
            else if(current_ekran.current_level == EKRAN_TIMEOUT_ANALOG_REGISTRATOR)
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_TIMEOUT_ANALOG_REGISTRATOR) current_ekran.index_position = 0;
              position_in_current_level_menu[EKRAN_TIMEOUT_ANALOG_REGISTRATOR] = current_ekran.index_position;
              //Формуємо екран витримок аналогового реєстратора
              make_ekran_timeout_analog_registrator();
            }
            else if(current_ekran.current_level == EKRAN_VIEW_SETTING_LANGUAGE)
            {
              if(current_ekran.index_position >= MAX_ROW_FOR_VIEW_SETTING_LANGUAGE) current_ekran.index_position = 0;
              position_in_current_level_menu[EKRAN_VIEW_SETTING_LANGUAGE] = current_ekran.index_position;
              //Формуємо екран інформації по мові меню
              make_ekran_setting_language();
            }

            //Очищаємо біт обновлення екрану
            new_state_keyboard &= (unsigned int)(~(1<<BIT_REWRITE));
          }
          else
          {
            if (new_state_keyboard == (1<<BIT_KEY_ENTER))
            {
              //Натиснута кнопка ENTER
              if(current_ekran.edition == 0)
              {
                int temp_current_level = current_ekran.current_level;
                
                //Копіюємо текчі настройки у структуру для редагування
                if(
                   (current_ekran.current_level == EKRAN_SETPOINT_CTRL_PHASE)
                  )   
                {
                  if (current_ekran.index_position == INDEX_ML_STPCTRL_PHASE_U)
                  {
                    edition_settings.setpoint_ctrl_phase_U = current_settings.setpoint_ctrl_phase_U;
                    current_ekran.position_cursor_x = COL_SETPOINT_CTRL_PHASE_U_BEGIN;
                  }
                  else if (current_ekran.index_position == INDEX_ML_STPCTRL_PHASE_PHI)
                  {
                    edition_settings.setpoint_ctrl_phase_phi = current_settings.setpoint_ctrl_phase_phi;
                    current_ekran.position_cursor_x = COL_SETPOINT_CTRL_PHASE_PHI_BEGIN;
                  }
                  else if (current_ekran.index_position == INDEX_ML_STPCTRL_PHASE_F)
                  {
                    edition_settings.setpoint_ctrl_phase_f = current_settings.setpoint_ctrl_phase_f;
                    current_ekran.position_cursor_x = COL_SETPOINT_CTRL_PHASE_F_BEGIN;
                  }
                }
                else if(
                        (current_ekran.current_level == EKRAN_TIMEOUT_CTRL_PHASE)
                       )   
                {
                  if (current_ekran.index_position == INDEX_ML_TMOCTRL_PHASE_U)
                  {
                    edition_settings.timeout_ctrl_phase_U = current_settings.timeout_ctrl_phase_U;
                    current_ekran.position_cursor_x = COL_TMO_CTRL_PHASE_U_BEGIN;
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOCTRL_PHASE_U_D)
                  {
                    edition_settings.timeout_ctrl_phase_U_d = current_settings.timeout_ctrl_phase_U_d;
                    current_ekran.position_cursor_x = COL_TMO_CTRL_PHASE_U_D_BEGIN;
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOCTRL_PHASE_PHI)
                  {
                    edition_settings.timeout_ctrl_phase_phi = current_settings.timeout_ctrl_phase_phi;
                    current_ekran.position_cursor_x = COL_TMO_CTRL_PHASE_PHI_BEGIN;
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOCTRL_PHASE_PHI_D)
                  {
                    edition_settings.timeout_ctrl_phase_phi_d = current_settings.timeout_ctrl_phase_phi_d;
                    current_ekran.position_cursor_x = COL_TMO_CTRL_PHASE_PHI_D_BEGIN;
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOCTRL_PHASE_F)
                  {
                    edition_settings.timeout_ctrl_phase_f = current_settings.timeout_ctrl_phase_f;
                    current_ekran.position_cursor_x = COL_TMO_CTRL_PHASE_F_BEGIN;
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOCTRL_PHASE_F_D)
                  {
                    edition_settings.timeout_ctrl_phase_f_d = current_settings.timeout_ctrl_phase_f_d;
                    current_ekran.position_cursor_x = COL_TMO_CTRL_PHASE_F_D_BEGIN;
                  }
                }
                else if(current_ekran.current_level == EKRAN_CONTROL_CTRL_PHASE)
                {
                  edition_settings.control_ctrl_phase = current_settings.control_ctrl_phase;
                }
                else if((current_ekran.current_level >= EKRAN_TIMEOUT_ALARMS1) && (current_ekran.current_level <= EKRAN_TIMEOUT_ALARMS2))
                {
                  if (current_ekran.index_position == INDEX_ML_ALARM_SOUND_PERIOD)
                  {
                    edition_settings.timeout_alarm_sound_period[current_ekran.current_level - EKRAN_TIMEOUT_ALARMS1] = current_settings.timeout_alarm_sound_period[current_ekran.current_level - EKRAN_TIMEOUT_ALARMS1];
                    current_ekran.position_cursor_x = COL_TMO_ALARM_SOUND_PERIOD_BEGIN;
                  }
                }
                else if((current_ekran.current_level >= EKRAN_CONTROL_ALARMS1) && (current_ekran.current_level <= EKRAN_CONTROL_ALARMS2))
                {
                  edition_settings.control_alarm = current_settings.control_alarm;
                }
                else if(current_ekran.current_level == EKRAN_DOPUSK_DV_UVV)
                {
                  edition_settings.dopusk_dv[current_ekran.index_position] = current_settings.dopusk_dv[current_ekran.index_position];
                  current_ekran.position_cursor_x = COL_DOPUSK_DV_BEGIN;
                }
                else if(current_ekran.current_level == EKRAN_TYPE_INPUT_SIGNAL_UVV)
                {
                  edition_settings.type_of_input_signal = current_settings.type_of_input_signal;
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
                  else if (current_ekran.index_position == INDEX_ML_NUMBER_DEFINED_FUNCTIONS)
                  {
                    edition_settings.number_defined_df = current_settings.number_defined_df;
                    current_ekran.position_cursor_x = COL_NUMBER_DEFINED_FUNCTIONS_BEGIN;
                  }
                  else if (current_ekran.index_position == INDEX_ML_NUMBER_DEFINED_TRIGGERS)
                  {
                    edition_settings.number_defined_dt = current_settings.number_defined_dt;
                    current_ekran.position_cursor_x = COL_NUMBER_DEFINED_TRIGGERS_BEGIN;
                  }
                  else if (current_ekran.index_position == INDEX_ML_NUMBER_DEFINED_AND)
                  {
                    edition_settings.number_defined_and = current_settings.number_defined_and;
                    current_ekran.position_cursor_x = COL_NUMBER_DEFINED_AND_BEGIN;
                  }
                  else if (current_ekran.index_position == INDEX_ML_NUMBER_DEFINED_OR)
                  {
                    edition_settings.number_defined_or = current_settings.number_defined_or;
                    current_ekran.position_cursor_x = COL_NUMBER_DEFINED_OR_BEGIN;
                  }
                  else if (current_ekran.index_position == INDEX_ML_NUMBER_DEFINED_XOR)
                  {
                    edition_settings.number_defined_xor = current_settings.number_defined_xor;
                    current_ekran.position_cursor_x = COL_NUMBER_DEFINED_XOR_BEGIN;
                  }
                  else if (current_ekran.index_position == INDEX_ML_NUMBER_DEFINED_NOT)
                  {
                    edition_settings.number_defined_not = current_settings.number_defined_not;
                    current_ekran.position_cursor_x = COL_NUMBER_DEFINED_NOT_BEGIN;
                  }
                }
                else if(current_ekran.current_level == EKRAN_LIST_TYPE_DF)
                {
                  edition_settings.type_df = current_settings.type_df;
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

                //Підготовка до режиму редагування - включаємо мигаючий курсор
                current_ekran.cursor_on = 1;
                current_ekran.cursor_blinking_on = 1;
                if (current_settings.password != 0)
                {
                  //Переходимо на меню запиту паролю
                  current_ekran.current_level = EKRAN_LEVEL_PASSWORD;
                  previous_level_in_current_level_menu[current_ekran.current_level] = temp_current_level;
                  current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
                }
                else
                {
                  //Переходимо у режим редагування
                  current_ekran.edition = 1;
                }
              }
              else if (current_ekran.edition == 1)
              {
                //Перевіряємо чи якісь зміни відбулися
                unsigned int found_changes = 0;

                if(
                   (current_ekran.current_level == EKRAN_SETPOINT_CTRL_PHASE)
                  )   
                {
                  if (current_ekran.index_position == INDEX_ML_STPCTRL_PHASE_U)
                  {
                    if (edition_settings.setpoint_ctrl_phase_U != current_settings.setpoint_ctrl_phase_U) found_changes = 1;
                  }
                  else if (current_ekran.index_position == INDEX_ML_STPCTRL_PHASE_PHI)
                  {
                    if (edition_settings.setpoint_ctrl_phase_phi != current_settings.setpoint_ctrl_phase_phi) found_changes = 1;
                  }
                  else if (current_ekran.index_position == INDEX_ML_STPCTRL_PHASE_F)
                  {
                    if (edition_settings.setpoint_ctrl_phase_f != current_settings.setpoint_ctrl_phase_f) found_changes = 1;
                  }
                }
                else if(
                        (current_ekran.current_level == EKRAN_TIMEOUT_CTRL_PHASE)
                       )   
                {
                  if (current_ekran.index_position == INDEX_ML_TMOCTRL_PHASE_U)
                  {
                    if (edition_settings.timeout_ctrl_phase_U != current_settings.timeout_ctrl_phase_U) found_changes = 1;
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOCTRL_PHASE_U_D)
                  {
                    if (edition_settings.timeout_ctrl_phase_U_d != current_settings.timeout_ctrl_phase_U_d) found_changes = 1;
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOCTRL_PHASE_PHI)
                  {
                    if (edition_settings.timeout_ctrl_phase_phi != current_settings.timeout_ctrl_phase_phi) found_changes = 1;
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOCTRL_PHASE_PHI_D)
                  {
                    if (edition_settings.timeout_ctrl_phase_phi_d != current_settings.timeout_ctrl_phase_phi_d) found_changes = 1;
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOCTRL_PHASE_F)
                  {
                    if (edition_settings.timeout_ctrl_phase_f != current_settings.timeout_ctrl_phase_f) found_changes = 1;
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOCTRL_PHASE_F_D)
                  {
                    if (edition_settings.timeout_ctrl_phase_f_d != current_settings.timeout_ctrl_phase_f_d) found_changes = 1;
                  }
                }
                else if(current_ekran.current_level == EKRAN_CONTROL_CTRL_PHASE)
                {
                  if (edition_settings.control_ctrl_phase != current_settings.control_ctrl_phase) found_changes = 1;
                }
                else if((current_ekran.current_level >= EKRAN_TIMEOUT_ALARMS1) && (current_ekran.current_level <= EKRAN_TIMEOUT_ALARMS2))
                {
                  if (current_ekran.index_position == INDEX_ML_ALARM_SOUND_PERIOD)
                  {
                    if (edition_settings.timeout_alarm_sound_period[current_ekran.current_level - EKRAN_TIMEOUT_ALARMS1] != current_settings.timeout_alarm_sound_period[current_ekran.current_level - EKRAN_TIMEOUT_ALARMS1]) found_changes = 1;
                  }
                }
                else if((current_ekran.current_level >= EKRAN_CONTROL_ALARMS1) && (current_ekran.current_level <= EKRAN_CONTROL_ALARMS2))
                {
                  if (edition_settings.control_alarm != current_settings.control_alarm) found_changes = 1;
                }
                else if(current_ekran.current_level == EKRAN_DOPUSK_DV_UVV)
                {
                  if (edition_settings.dopusk_dv[current_ekran.index_position] != current_settings.dopusk_dv[current_ekran.index_position])
                    found_changes = 1;
                }
                else if(current_ekran.current_level == EKRAN_TYPE_INPUT_SIGNAL_UVV)
                {
                  if (edition_settings.type_of_input_signal != current_settings.type_of_input_signal) found_changes = 1;
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
                  else if (current_ekran.index_position == INDEX_ML_NUMBER_DEFINED_FUNCTIONS)
                  {
                    if (edition_settings.number_defined_df != current_settings.number_defined_df) found_changes = 1;
                  }
                  else if (current_ekran.index_position == INDEX_ML_NUMBER_DEFINED_TRIGGERS)
                  {
                    if (edition_settings.number_defined_dt != current_settings.number_defined_dt) found_changes = 1;
                  }
                  else if (current_ekran.index_position == INDEX_ML_NUMBER_DEFINED_AND)
                  {
                    if (edition_settings.number_defined_and != current_settings.number_defined_and) found_changes = 1;
                  }
                  else if (current_ekran.index_position == INDEX_ML_NUMBER_DEFINED_OR)
                  {
                    if (edition_settings.number_defined_or != current_settings.number_defined_or) found_changes = 1;
                  }
                  else if (current_ekran.index_position == INDEX_ML_NUMBER_DEFINED_XOR)
                  {
                    if (edition_settings.number_defined_xor != current_settings.number_defined_xor) found_changes = 1;
                  }
                  else if (current_ekran.index_position == INDEX_ML_NUMBER_DEFINED_NOT)
                  {
                    if (edition_settings.number_defined_not != current_settings.number_defined_not) found_changes = 1;
                  }
                }
                else if(current_ekran.current_level == EKRAN_LIST_TYPE_DF)
                {
                  if (edition_settings.type_df != current_settings.type_df) found_changes = 1;
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

                //Виходимо з режиму редагування
                if (found_changes == 0) current_ekran.edition = 0;
                else current_ekran.edition = 2;

                current_ekran.cursor_on = 0;
                current_ekran.cursor_blinking_on = 0;
              }
              else if (current_ekran.edition == 2)
              {
                //Попередньо виставляємо повідомлення, що дані не достовірні
                current_ekran.edition = 3;
                //Перевіряємо достовірність даних
                if(
                   (current_ekran.current_level == EKRAN_SETPOINT_CTRL_PHASE)
                  )   
                {
                  if (current_ekran.index_position == INDEX_ML_STPCTRL_PHASE_U)
                  {
                    if (check_data_setpoint(edition_settings.setpoint_ctrl_phase_U, SETPOINT_CTRL_PHASE_U_MIN, SETPOINT_CTRL_PHASE_U_MAX) == 1)
                    {
                      if (edition_settings.setpoint_ctrl_phase_U != current_settings.setpoint_ctrl_phase_U)
                      {
                        //Помічаємо, що поле структури зараз буде змінене
                        changed_settings = CHANGED_ETAP_EXECUTION;
                        
                        current_settings.setpoint_ctrl_phase_U = edition_settings.setpoint_ctrl_phase_U;
                        //Формуємо запис у таблиці настройок про зміну конфігурації і ініціюємо запис у EEPROM нових настройок
                        fix_change_settings(0, 1);
                      }
                      //Виходимо з режиму редагування
                      current_ekran.edition = 0;
                    }
                  }
                  else if (current_ekran.index_position == INDEX_ML_STPCTRL_PHASE_PHI)
                  {
                    if (check_data_setpoint(edition_settings.setpoint_ctrl_phase_phi, SETPOINT_CTRL_PHASE_PHI_MIN, SETPOINT_CTRL_PHASE_PHI_MAX) == 1)
                    {
                      if (edition_settings.setpoint_ctrl_phase_phi != current_settings.setpoint_ctrl_phase_phi)
                      {
                        //Помічаємо, що поле структури зараз буде змінене
                        changed_settings = CHANGED_ETAP_EXECUTION;
                        
                        current_settings.setpoint_ctrl_phase_phi = edition_settings.setpoint_ctrl_phase_phi;
                        //Формуємо запис у таблиці настройок про зміну конфігурації і ініціюємо запис у EEPROM нових настройок
                        fix_change_settings(0, 1);
                      }
                      //Виходимо з режиму редагування
                      current_ekran.edition = 0;
                    }
                  }
                  else if (current_ekran.index_position == INDEX_ML_STPCTRL_PHASE_F)
                  {
                    if (check_data_setpoint(edition_settings.setpoint_ctrl_phase_f, SETPOINT_CTRL_PHASE_F_MIN, SETPOINT_CTRL_PHASE_F_MAX) == 1)
                    {
                      if (edition_settings.setpoint_ctrl_phase_f != current_settings.setpoint_ctrl_phase_f)
                      {
                        //Помічаємо, що поле структури зараз буде змінене
                        changed_settings = CHANGED_ETAP_EXECUTION;
                        
                        current_settings.setpoint_ctrl_phase_f = edition_settings.setpoint_ctrl_phase_f;
                        //Формуємо запис у таблиці настройок про зміну конфігурації і ініціюємо запис у EEPROM нових настройок
                        fix_change_settings(0, 1);
                      }
                      //Виходимо з режиму редагування
                      current_ekran.edition = 0;
                    }
                  }
                }
                else if(
                        (current_ekran.current_level == EKRAN_TIMEOUT_CTRL_PHASE)
                       )   
                {
                  if (current_ekran.index_position == INDEX_ML_TMOCTRL_PHASE_U)
                  {
                    if (check_data_setpoint(edition_settings.timeout_ctrl_phase_U, TIMEOUT_CTRL_PHASE_U_MIN, TIMEOUT_CTRL_PHASE_U_MAX) == 1)
                    {
                      if (edition_settings.timeout_ctrl_phase_U != current_settings.timeout_ctrl_phase_U)
                      {
                        //Помічаємо, що поле структури зараз буде змінене
                        changed_settings = CHANGED_ETAP_EXECUTION;
                        
                        current_settings.timeout_ctrl_phase_U = edition_settings.timeout_ctrl_phase_U;
                        //Формуємо запис у таблиці настройок про зміну конфігурації і ініціюємо запис у EEPROM нових настройок
                        fix_change_settings(0, 1);
                      }
                      //Виходимо з режиму редагування
                      current_ekran.edition = 0;
                    }
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOCTRL_PHASE_U_D)
                  {
                    if (check_data_setpoint(edition_settings.timeout_ctrl_phase_U_d, TIMEOUT_CTRL_PHASE_U_D_MIN, TIMEOUT_CTRL_PHASE_U_D_MAX) == 1)
                    {
                      if (edition_settings.timeout_ctrl_phase_U_d != current_settings.timeout_ctrl_phase_U_d)
                      {
                        //Помічаємо, що поле структури зараз буде змінене
                        changed_settings = CHANGED_ETAP_EXECUTION;
                        
                        current_settings.timeout_ctrl_phase_U_d = edition_settings.timeout_ctrl_phase_U_d;
                        //Формуємо запис у таблиці настройок про зміну конфігурації і ініціюємо запис у EEPROM нових настройок
                        fix_change_settings(0, 1);
                      }
                      //Виходимо з режиму редагування
                      current_ekran.edition = 0;
                    }
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOCTRL_PHASE_PHI)
                  {
                    if (check_data_setpoint(edition_settings.timeout_ctrl_phase_phi, TIMEOUT_CTRL_PHASE_PHI_MIN, TIMEOUT_CTRL_PHASE_PHI_MAX) == 1)
                    {
                      if (edition_settings.timeout_ctrl_phase_phi != current_settings.timeout_ctrl_phase_phi)
                      {
                        //Помічаємо, що поле структури зараз буде змінене
                        changed_settings = CHANGED_ETAP_EXECUTION;
                        
                        current_settings.timeout_ctrl_phase_phi = edition_settings.timeout_ctrl_phase_phi;
                        //Формуємо запис у таблиці настройок про зміну конфігурації і ініціюємо запис у EEPROM нових настройок
                        fix_change_settings(0, 1);
                      }
                      //Виходимо з режиму редагування
                      current_ekran.edition = 0;
                    }
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOCTRL_PHASE_PHI_D)
                  {
                    if (check_data_setpoint(edition_settings.timeout_ctrl_phase_phi_d, TIMEOUT_CTRL_PHASE_PHI_D_MIN, TIMEOUT_CTRL_PHASE_PHI_D_MAX) == 1)
                    {
                      if (edition_settings.timeout_ctrl_phase_phi_d != current_settings.timeout_ctrl_phase_phi_d)
                      {
                        //Помічаємо, що поле структури зараз буде змінене
                        changed_settings = CHANGED_ETAP_EXECUTION;
                        
                        current_settings.timeout_ctrl_phase_phi_d = edition_settings.timeout_ctrl_phase_phi_d;
                        //Формуємо запис у таблиці настройок про зміну конфігурації і ініціюємо запис у EEPROM нових настройок
                        fix_change_settings(0, 1);
                      }
                      //Виходимо з режиму редагування
                      current_ekran.edition = 0;
                    }
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOCTRL_PHASE_F)
                  {
                    if (check_data_setpoint(edition_settings.timeout_ctrl_phase_f, TIMEOUT_CTRL_PHASE_F_MIN, TIMEOUT_CTRL_PHASE_F_MAX) == 1)
                    {
                      if (edition_settings.timeout_ctrl_phase_f != current_settings.timeout_ctrl_phase_f)
                      {
                        //Помічаємо, що поле структури зараз буде змінене
                        changed_settings = CHANGED_ETAP_EXECUTION;
                        
                        current_settings.timeout_ctrl_phase_f = edition_settings.timeout_ctrl_phase_f;
                        //Формуємо запис у таблиці настройок про зміну конфігурації і ініціюємо запис у EEPROM нових настройок
                        fix_change_settings(0, 1);
                      }
                      //Виходимо з режиму редагування
                      current_ekran.edition = 0;
                    }
                  }
                  else if (current_ekran.index_position == INDEX_ML_TMOCTRL_PHASE_F_D)
                  {
                    if (check_data_setpoint(edition_settings.timeout_ctrl_phase_f_d, TIMEOUT_CTRL_PHASE_F_D_MIN, TIMEOUT_CTRL_PHASE_F_D_MAX) == 1)
                    {
                      if (edition_settings.timeout_ctrl_phase_f_d != current_settings.timeout_ctrl_phase_f_d)
                      {
                        //Помічаємо, що поле структури зараз буде змінене
                        changed_settings = CHANGED_ETAP_EXECUTION;
                        
                        current_settings.timeout_ctrl_phase_f_d = edition_settings.timeout_ctrl_phase_f_d;
                        //Формуємо запис у таблиці настройок про зміну конфігурації і ініціюємо запис у EEPROM нових настройок
                        fix_change_settings(0, 1);
                      }
                      //Виходимо з режиму редагування
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
                      //Помічаємо, що поле структури зараз буде змінене
                      changed_settings = CHANGED_ETAP_EXECUTION;
                        
                      current_settings.control_ctrl_phase = edition_settings.control_ctrl_phase;
                      //Формуємо запис у таблиці настройок про зміну конфігурації і ініціюємо запис у EEPROM нових настройок
                      fix_change_settings(0, 1);
                    }
                    //Виходимо з режиму редагування
                    current_ekran.edition = 0;
                  }
                }
                else if((current_ekran.current_level >= EKRAN_TIMEOUT_ALARMS1) && (current_ekran.current_level <= EKRAN_TIMEOUT_ALARMS2))
                {
                  if (current_ekran.index_position == INDEX_ML_ALARM_SOUND_PERIOD)
                  {
                    if (check_data_setpoint(edition_settings.timeout_alarm_sound_period[current_ekran.current_level - EKRAN_TIMEOUT_ALARMS1], TIMEOUT_ALARM_SOUND_PERIOD_MIN, TIMEOUT_ALARM_SOUND_PERIOD_MAX) == 1)
                    {
                      if (edition_settings.timeout_alarm_sound_period[current_ekran.current_level - EKRAN_TIMEOUT_ALARMS1] != current_settings.timeout_alarm_sound_period[current_ekran.current_level - EKRAN_TIMEOUT_ALARMS1])
                      {
                        //Помічаємо, що поле структури зараз буде змінене
                        changed_settings = CHANGED_ETAP_EXECUTION;
                        
                        current_settings.timeout_alarm_sound_period[current_ekran.current_level - EKRAN_TIMEOUT_ALARMS1] = edition_settings.timeout_alarm_sound_period[current_ekran.current_level - EKRAN_TIMEOUT_ALARMS1];
                        //Формуємо запис у таблиці настройок про зміну конфігурації і ініціюємо запис у EEPROM нових настройок
                        fix_change_settings(0, 1);
                      }
                      //Виходимо з режиму редагування
                      current_ekran.edition = 0;
                    }
                  }
                }
                else if((current_ekran.current_level >= EKRAN_CONTROL_ALARMS1) && (current_ekran.current_level <= EKRAN_CONTROL_ALARMS2))
                {
                  if (( ( edition_settings.control_alarm >> (ALARMS_SEPARATOR*(current_ekran.current_level - EKRAN_CONTROL_ALARMS1)) ) & ((1 << ALARMS_SEPARATOR) - 1) & ((unsigned int)(~CTR_ALARMS_MASKA))) == 0)
                  {
                    if (edition_settings.control_alarm != current_settings.control_alarm)
                    {
                      //Помічаємо, що поле структури зараз буде змінене
                      changed_settings = CHANGED_ETAP_EXECUTION;
                        
                      current_settings.control_alarm = edition_settings.control_alarm;
                      //Формуємо запис у таблиці настройок про зміну конфігурації і ініціюємо запис у EEPROM нових настройок
                      fix_change_settings(0, 1);
                    }
                    //Виходимо з режиму редагування
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
                      //Помічаємо, що поле структури зараз буде змінене
                      changed_settings = CHANGED_ETAP_EXECUTION;

                      current_settings.dopusk_dv[current_ekran.index_position] = edition_settings.dopusk_dv[current_ekran.index_position];
                      //Формуємо запис у таблиці настройок про зміну конфігурації і ініціюємо запис у EEPROM нових настройок
                      fix_change_settings(0, 1);
                    }
                    //Виходимо з режиму редагування
                    current_ekran.edition = 0;
                  }
                }
                else if(current_ekran.current_level == EKRAN_TYPE_INPUT_SIGNAL_UVV)
                {
                  if ((edition_settings.type_of_input_signal & ((unsigned int)(~((1<<NUMBER_INPUTS)-1)))) == 0)
                  {
                    if (edition_settings.type_of_input_signal != current_settings.type_of_input_signal)
                    {
                      //Помічаємо, що поле структури зараз буде змінене
                      changed_settings = CHANGED_ETAP_EXECUTION;
                      
                      correct_dopusk_dv_when_type_of_input_signal_is_changed();
                      current_settings.type_of_input_signal = edition_settings.type_of_input_signal;
                      //Формуємо запис у таблиці настройок про зміну конфігурації і ініціюємо запис у EEPROM нових настройок
                      fix_change_settings(0, 1);
                    }
                    //Виходимо з режиму редагування
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
                      //Помічаємо, що поле структури зараз буде змінене
                      changed_settings = CHANGED_ETAP_EXECUTION;
                        
                      current_settings.address = edit_value;
                      //Формуємо запис у таблиці настройок про зміну конфігурації і ініціюємо запис у EEPROM нових настройок
                      fix_change_settings(0, 1);
                    }
                    //Виходимо з режиму редагування
                    current_ekran.edition = 0;
                  }
                }
                else if(current_ekran.current_level == EKRAN_VIEW_SPEED_RS485)
                {
                  if (check_data_setpoint(edition_settings.speed_RS485, VALUE_SPEED_INTERFACE_MIN, VALUE_SPEED_INTERFACE_MAX) == 1)
                  {
                    if (edition_settings.speed_RS485 != current_settings.speed_RS485)
                    {
                      //Помічаємо, що поле структури зараз буде змінене
                      changed_settings = CHANGED_ETAP_EXECUTION;
                        
                      current_settings.speed_RS485 = edition_settings.speed_RS485;
                      //Підраховуємо нову величину затримки у бітах, яка допускається між байтами у RS-485 згідно з визначеними настройками
                      calculate_namber_bit_waiting_for_rs_485();
                      //Виставляємо команду про переконфігурування RS-485
                      make_reconfiguration_RS_485 = 0xff;
                      //Формуємо запис у таблиці настройок про зміну конфігурації і ініціюємо запис у EEPROM нових настройок
                      fix_change_settings(0, 1);
                    }
                    //Виходимо з режиму редагування
                    current_ekran.edition = 0;
                  }
                }
                else if(current_ekran.current_level == EKRAN_VIEW_PARE_RS485)
                {
                  if (check_data_setpoint(edition_settings.pare_bit_RS485, VALUE_PARE_INTERFACE_MIN, VALUE_PARE_INTERFACE_MAX) == 1)
                  {
                    if (edition_settings.pare_bit_RS485 != current_settings.pare_bit_RS485)
                    {
                      //Помічаємо, що поле структури зараз буде змінене
                      changed_settings = CHANGED_ETAP_EXECUTION;
                        
                      current_settings.pare_bit_RS485 = edition_settings.pare_bit_RS485;
                      //Підраховуємо нову величину затримки у бітах, яка допускається між байтами у RS-485 згідно з визначеними настройками
                      calculate_namber_bit_waiting_for_rs_485();
                      //Виставляємо команду про переконфігурування RS-485
                      make_reconfiguration_RS_485 = 0xff;
                      //Формуємо запис у таблиці настройок про зміну конфігурації і ініціюємо запис у EEPROM нових настройок
                      fix_change_settings(0, 1);
                    }
                    //Виходимо з режиму редагування
                    current_ekran.edition = 0;
                  }
                }
                else if(current_ekran.current_level == EKRAN_VIEW_STOP_BITS_RS485)
                {
                  if (check_data_setpoint(edition_settings.number_stop_bit_RS485, VALUE_STOP_BITS_INTERFACE_MIN, VALUE_STOP_BITS_INTERFACE_MAX) == 1)
                  {
                    if (edition_settings.number_stop_bit_RS485 != current_settings.number_stop_bit_RS485)
                    {
                      //Помічаємо, що поле структури зараз буде змінене
                      changed_settings = CHANGED_ETAP_EXECUTION;
                        
                      current_settings.number_stop_bit_RS485 = edition_settings.number_stop_bit_RS485;
                      //Підраховуємо нову величину затримки у бітах, яка допускається між байтами у RS-485 згідно з визначеними настройками
                      calculate_namber_bit_waiting_for_rs_485();
                      //Виставляємо команду про переконфігурування RS-485
                      make_reconfiguration_RS_485 = 0xff;
                      //Формуємо запис у таблиці настройок про зміну конфігурації і ініціюємо запис у EEPROM нових настройок
                      fix_change_settings(0, 1);
                    }
                    //Виходимо з режиму редагування
                    current_ekran.edition = 0;
                  }
                }
                else if(current_ekran.current_level == EKRAN_VIEW_TIMEOUT_RS485)
                {
                  if (check_data_setpoint(edition_settings.time_out_1_RS485, VALUE_TIME_OUT_1_INTERFACE_MIN, VALUE_TIME_OUT_1_INTERFACE_MAX) == 1)
                  {
                    if (edition_settings.time_out_1_RS485 != current_settings.time_out_1_RS485)
                    {
                      //Помічаємо, що поле структури зараз буде змінене
                      changed_settings = CHANGED_ETAP_EXECUTION;
                        
                      current_settings.time_out_1_RS485 = edition_settings.time_out_1_RS485;
                      //Підраховуємо нову величину затримки у бітах, яка допускається між байтами у RS-485 згідно з визначеними настройками
                      calculate_namber_bit_waiting_for_rs_485();
                      //Формуємо запис у таблиці настройок про зміну конфігурації і ініціюємо запис у EEPROM нових настройок
                      fix_change_settings(0, 1);
                    }
                    //Виходимо з режиму редагування
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
                        //Помічаємо, що поле структури зараз буде змінене
                        changed_settings = CHANGED_ETAP_EXECUTION;

                        current_settings.number_iteration_el = edition_settings.number_iteration_el;
                        //Формуємо запис у таблиці настройок про зміну конфігурації і ініціюємо запис у EEPROM нових настройок
                        fix_change_settings(0, 1);
                      }
                      //Виходимо з режиму редагування
                      current_ekran.edition = 0;
                    }
                  }
                  else if (current_ekran.index_position == INDEX_ML_NUMBER_DEFINED_FUNCTIONS)
                  {
                    if (check_data_setpoint(edition_settings.number_defined_df, NUMBER_DEFINED_FUNCTIONS_MIN, NUMBER_DEFINED_FUNCTIONS_MAX) == 1)
                    {
                      if (edition_settings.number_defined_df != current_settings.number_defined_df)
                      {
                        //Помічаємо, що поле структури зараз буде змінене
                        changed_settings = CHANGED_ETAP_EXECUTION;

                        current_settings.number_defined_df = edition_settings.number_defined_df;
                        //Обновляємо значення
//                        action_after_changing_number_el(&current_settings, 0);
                      
                        //Формуємо запис у таблиці настройок про зміну конфігурації і ініціюємо запис у EEPROM нових настройок
                        fix_change_settings(0, 1);
                      }
                      //Виходимо з режиму редагування
                      current_ekran.edition = 0;
                    }
                  }
                  else if (current_ekran.index_position == INDEX_ML_NUMBER_DEFINED_TRIGGERS)
                  {
                    if (check_data_setpoint(edition_settings.number_defined_dt, NUMBER_DEFINED_TRIGGERS_MIN, NUMBER_DEFINED_TRIGGERS_MAX) == 1)
                    {
                      if (edition_settings.number_defined_dt != current_settings.number_defined_dt)
                      {
                        //Помічаємо, що поле структури зараз буде змінене
                        changed_settings = CHANGED_ETAP_EXECUTION;

                        current_settings.number_defined_dt = edition_settings.number_defined_dt;
                        //Обновляємо значення
//                        action_after_changing_number_el(&current_settings, 1);

                        //Формуємо запис у таблиці настройок про зміну конфігурації і ініціюємо запис у EEPROM нових настройок
                        fix_change_settings(0, 1);
                      }
                      //Виходимо з режиму редагування
                      current_ekran.edition = 0;
                    }
                  }
                  else if (current_ekran.index_position == INDEX_ML_NUMBER_DEFINED_AND)
                  {
                    if (check_data_setpoint(edition_settings.number_defined_and, NUMBER_DEFINED_AND_MIN, NUMBER_DEFINED_AND_MAX) == 1)
                    {
                      if (edition_settings.number_defined_and != current_settings.number_defined_and)
                      {
                        //Помічаємо, що поле структури зараз буде змінене
                        changed_settings = CHANGED_ETAP_EXECUTION;

                        current_settings.number_defined_and = edition_settings.number_defined_and;
                        //Обновляємо значення
//                        action_after_changing_number_el(&current_settings, 2);

                        //Формуємо запис у таблиці настройок про зміну конфігурації і ініціюємо запис у EEPROM нових настройок
                        fix_change_settings(0, 1);
                      }
                      //Виходимо з режиму редагування
                      current_ekran.edition = 0;
                    }
                  }
                  else if (current_ekran.index_position == INDEX_ML_NUMBER_DEFINED_OR)
                  {
                    if (check_data_setpoint(edition_settings.number_defined_or, NUMBER_DEFINED_OR_MIN, NUMBER_DEFINED_OR_MAX) == 1)
                    {
                      if (edition_settings.number_defined_or != current_settings.number_defined_or)
                      {
                        //Помічаємо, що поле структури зараз буде змінене
                        changed_settings = CHANGED_ETAP_EXECUTION;

                        current_settings.number_defined_or = edition_settings.number_defined_or;
                        //Обновляємо значення
//                        action_after_changing_number_el(&current_settings, 3);

                        //Формуємо запис у таблиці настройок про зміну конфігурації і ініціюємо запис у EEPROM нових настройок
                        fix_change_settings(0, 1);
                      }
                      //Виходимо з режиму редагування
                      current_ekran.edition = 0;
                    }
                  }
                  else if (current_ekran.index_position == INDEX_ML_NUMBER_DEFINED_XOR)
                  {
                    if (check_data_setpoint(edition_settings.number_defined_xor, NUMBER_DEFINED_XOR_MIN, NUMBER_DEFINED_XOR_MAX) == 1)
                    {
                      if (edition_settings.number_defined_xor != current_settings.number_defined_xor)
                      {
                        //Помічаємо, що поле структури зараз буде змінене
                        changed_settings = CHANGED_ETAP_EXECUTION;

                        current_settings.number_defined_xor = edition_settings.number_defined_xor;
                        //Обновляємо значення
//                        action_after_changing_number_el(&current_settings, 4);

                        //Формуємо запис у таблиці настройок про зміну конфігурації і ініціюємо запис у EEPROM нових настройок
                        fix_change_settings(0, 1);
                      }
                      //Виходимо з режиму редагування
                      current_ekran.edition = 0;
                    }
                  }
                  else if (current_ekran.index_position == INDEX_ML_NUMBER_DEFINED_NOT)
                  {
                    if (check_data_setpoint(edition_settings.number_defined_not, NUMBER_DEFINED_NOT_MIN, NUMBER_DEFINED_NOT_MAX) == 1)
                    {
                      if (edition_settings.number_defined_not != current_settings.number_defined_not)
                      {
                        //Помічаємо, що поле структури зараз буде змінене
                        changed_settings = CHANGED_ETAP_EXECUTION;

                        current_settings.number_defined_not = edition_settings.number_defined_not;
                        //Обновляємо значення
//                        action_after_changing_number_el(&current_settings, 5);

                        //Формуємо запис у таблиці настройок про зміну конфігурації і ініціюємо запис у EEPROM нових настройок
                        fix_change_settings(0, 1);
                      }
                      //Виходимо з режиму редагування
                      current_ekran.edition = 0;
                    }
                  }
                }
                else if(current_ekran.current_level == EKRAN_LIST_TYPE_DF)
                {
                  if ((edition_settings.type_df & ((unsigned int)(~((1<<NUMBER_DEFINED_FUNCTIONS)-1)))) == 0)
                  {
                    if (edition_settings.type_df != current_settings.type_df)
                    {
                      //Помічаємо, що поле структури зараз буде змінене
                      changed_settings = CHANGED_ETAP_EXECUTION;

                      current_settings.type_df = edition_settings.type_df;
                      //Формуємо запис у таблиці настройок про зміну конфігурації і ініціюємо запис у EEPROM нових настройок
                      fix_change_settings(0, 1);
                    }
                    //Виходимо з режиму редагування
                    current_ekran.edition = 0;
                  }
                }
                else if(current_ekran.current_level == EKRAN_TIMEOUT_ANALOG_REGISTRATOR)
                {
                  /*Встановлюємо симафор - суть якого полягає у тому, що якщо процес запису нової 
                  аварії не йде - то на час його установлення новий запис починати не можна, якщо ж вже іде ноий запис,
                  то він має продовжуватися і, навпаки, блокувати роботу аналогового реєстратора не можна*/
                  semaphore_read_state_ar_record = 1;
                  
                  if (state_ar_record == STATE_AR_NO_RECORD)
                  {
                    /*На даний момент не йде запис текучого аналогового аварійного процесу,
                    тому для зміни часових настройок тимчасово встановлюємо стан роботи
                    аналогового реєстратора у заблокований режим*/
                    state_ar_record = STATE_AR_TEMPORARY_BLOCK; 
                    
                    if (current_ekran.index_position == INDEX_ML_TMOPREFAULT)
                    {
                      if (check_data_setpoint((edition_settings.prefault_number_periods*20), TIMEOUT_PREFAULT_MIN, TIMEOUT_PREFAULT_MAX) == 1)
                      {
                        if (edition_settings.prefault_number_periods != current_settings.prefault_number_periods)
                        {
                          //Помічаємо, що поле структури зараз буде змінене
                          changed_settings = CHANGED_ETAP_EXECUTION;
                        
                          current_settings.prefault_number_periods = edition_settings.prefault_number_periods;
                          //Виконуємо дії по зміні часових витримок аналогового реєстратора
                          actions_after_changing_tiomouts_ar();
                          //Формуємо запис у таблиці настройок про зміну конфігурації і ініціюємо запис у EEPROM нових настройок
                          fix_change_settings(0, 1);
                        }
                        //Виходимо з режиму редагування
                        current_ekran.edition = 0;
                      }
                    }
                    else
                    {
                      if (check_data_setpoint((edition_settings.postfault_number_periods*20), TIMEOUT_POSTFAULT_MIN, TIMEOUT_POSTFAULT_MAX) == 1)
                      {
                        if (edition_settings.postfault_number_periods != current_settings.postfault_number_periods)
                        {
                          //Помічаємо, що поле структури зараз буде змінене
                          changed_settings = CHANGED_ETAP_EXECUTION;
                        
                          current_settings.postfault_number_periods = edition_settings.postfault_number_periods;
                          //Виконуємо дії по зміні часових витримок аналогового реєстратора
                          actions_after_changing_tiomouts_ar();
                          //Формуємо запис у таблиці настройок про зміну конфігурації і ініціюємо запис у EEPROM нових настройок
                          fix_change_settings(0, 1);
                        }
                        //Виходимо з режиму редагування
                        current_ekran.edition = 0;
                      }
                    }
                    
                    //Розблоковуємо роботу аналогового реєстратора
                    state_ar_record = STATE_AR_NO_RECORD;
                  }
                  
                  //Знімаємо семафор
                  semaphore_read_state_ar_record = 0;
                }
                else if(current_ekran.current_level == EKRAN_VIEW_SETTING_LANGUAGE)
                {
                  if (check_data_setpoint(edition_settings.language, VALUE_SETTING_LANGUAGE_MIN, VALUE_SETTING_LANGUAGE_MAX) == 1)
                  {
                    if (edition_settings.language != current_settings.language)
                    {
                      //Помічаємо, що поле структури зараз буде змінене
                      changed_settings = CHANGED_ETAP_EXECUTION;
                        
                      current_settings.language = edition_settings.language;
                      //Формуємо запис у таблиці настройок про зміну конфігурації і ініціюємо запис у EEPROM нових настройок
                      fix_change_settings(0, 1);
                    }
                    //Виходимо з режиму редагування
                    current_ekran.edition = 0;
                  }
                }
                
              }
              else if (current_ekran.edition == 3)
              {
                //Вихід у режимі редагування
                current_ekran.edition = 0;
              }
              
              if(current_ekran.edition == 2) make_ekran_ask_rewrite();
              else if(current_ekran.edition == 3)
              {
                const unsigned char information_about_error1[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
                {
                  " Вых.за диапазон",
                  " Вих.за діапазон",
                  "  Out of Limits ",
                  "Вых.за диапазон "
                };
                const unsigned char information_about_error2[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
                {
                  " Опер.вр.недост.",
                  "Опер.тимч.недост",
                  " Op.unavailable ",
                  " Опер.вр.недост."
                };

                const unsigned char (*point_to_information_about_error)[MAX_COL_LCD + 1] = information_about_error1;
                if(current_ekran.current_level == EKRAN_TIMEOUT_ANALOG_REGISTRATOR)
                {
                  if (state_ar_record != STATE_AR_NO_RECORD)
                    point_to_information_about_error = information_about_error2;
                }
                make_ekran_about_info(true, point_to_information_about_error);
              }
              else
                //Виставляємо біт обновлення екрану
                new_state_keyboard |= (1<<BIT_REWRITE);

              //Очистити сигналізацію, що натиснута кнопка 
              new_state_keyboard &= (unsigned int)(~(1<<BIT_KEY_ENTER));
            }
            else if (new_state_keyboard == (1<<BIT_KEY_ESC))
            {
              if(current_ekran.edition == 0)
              {
                //Вихід у режимі спостерігання
              //Переходимо у попереднє меню
              current_ekran.current_level = previous_level_in_current_level_menu[current_ekran.current_level];
              current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
              current_ekran.edition = 0;
              }
              else
              {
                //Вихід у режимі редагування без введення змін
                current_ekran.edition = 0;
              }

              //Виставляємо команду на обновлекння нового екрану
              new_state_keyboard |= (1<<BIT_REWRITE);
              //Очистити сигналізацію, що натиснута кнопка 
              new_state_keyboard &= (unsigned int)(~(1<<BIT_KEY_ESC));
            }
            else if (new_state_keyboard == (1<<BIT_KEY_UP))
            {
              //Натиснута кнопка UP
              if(
                 (current_ekran.current_level == EKRAN_SETPOINT_CTRL_PHASE)
                )   
              {
                if(current_ekran.edition == 0)
                {
                  if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_SETPOINT_CTRL_PHASE - 1;
                  position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;
                }
                else
                {
                  //Редагування числа
                  if (current_ekran.index_position == INDEX_ML_STPCTRL_PHASE_U)
                    edition_settings.setpoint_ctrl_phase_U = edit_setpoint(1, edition_settings.setpoint_ctrl_phase_U, 1, COL_SETPOINT_CTRL_PHASE_U_COMMA, COL_SETPOINT_CTRL_PHASE_U_END, 100);
                  else if (current_ekran.index_position == INDEX_ML_STPCTRL_PHASE_PHI)
                    edition_settings.setpoint_ctrl_phase_phi = edit_setpoint(1, edition_settings.setpoint_ctrl_phase_phi, 1, COL_SETPOINT_CTRL_PHASE_PHI_COMMA, COL_SETPOINT_CTRL_PHASE_PHI_END, 1);
                  else if (current_ekran.index_position == INDEX_ML_STPCTRL_PHASE_F)
                    edition_settings.setpoint_ctrl_phase_f = edit_setpoint(1, edition_settings.setpoint_ctrl_phase_f, 1, COL_SETPOINT_CTRL_PHASE_F_COMMA, COL_SETPOINT_CTRL_PHASE_F_END, 10);
                }
                //Формуємо екран уставок "Перевірки фаз"
                make_ekran_setpoint_ctrl_phase();
              }
              else if(
                      (current_ekran.current_level == EKRAN_TIMEOUT_CTRL_PHASE)
                     )   
              {
                if(current_ekran.edition == 0)
                {
                  if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_TIMEOUT_CTRL_PHASE - 1;
                  position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;
                }
                else
                {
                  //Редагування числа
                  if (current_ekran.index_position == INDEX_ML_TMOCTRL_PHASE_U)
                    edition_settings.timeout_ctrl_phase_U = edit_setpoint(1, edition_settings.timeout_ctrl_phase_U, 1, COL_TMO_CTRL_PHASE_U_COMMA, COL_TMO_CTRL_PHASE_U_END, 10);
                  else if (current_ekran.index_position == INDEX_ML_TMOCTRL_PHASE_U_D)
                    edition_settings.timeout_ctrl_phase_U_d = edit_setpoint(1, edition_settings.timeout_ctrl_phase_U_d, 1, COL_TMO_CTRL_PHASE_U_D_COMMA, COL_TMO_CTRL_PHASE_U_D_END, 10);
                  else if (current_ekran.index_position == INDEX_ML_TMOCTRL_PHASE_PHI)
                    edition_settings.timeout_ctrl_phase_phi = edit_setpoint(1, edition_settings.timeout_ctrl_phase_phi, 1, COL_TMO_CTRL_PHASE_PHI_COMMA, COL_TMO_CTRL_PHASE_PHI_END, 10);
                  else if (current_ekran.index_position == INDEX_ML_TMOCTRL_PHASE_PHI_D)
                    edition_settings.timeout_ctrl_phase_phi_d = edit_setpoint(1, edition_settings.timeout_ctrl_phase_phi_d, 1, COL_TMO_CTRL_PHASE_PHI_D_COMMA, COL_TMO_CTRL_PHASE_PHI_D_END, 10);
                  else if (current_ekran.index_position == INDEX_ML_TMOCTRL_PHASE_F)
                    edition_settings.timeout_ctrl_phase_f = edit_setpoint(1, edition_settings.timeout_ctrl_phase_f, 1, COL_TMO_CTRL_PHASE_F_COMMA, COL_TMO_CTRL_PHASE_F_END, 10);
                  else if (current_ekran.index_position == INDEX_ML_TMOCTRL_PHASE_F_D)
                    edition_settings.timeout_ctrl_phase_f_d = edit_setpoint(1, edition_settings.timeout_ctrl_phase_f_d, 1, COL_TMO_CTRL_PHASE_F_D_COMMA, COL_TMO_CTRL_PHASE_F_D_END, 10);
                }
                //Формуємо екран витримок "Перевірки фаз"
                make_ekran_timeout_ctrl_phase();
              }
              else if(current_ekran.current_level == EKRAN_CONTROL_CTRL_PHASE)
              {
                if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_CONTROL_CTRL_PHASE - 1;
                position_in_current_level_menu[EKRAN_CONTROL_CTRL_PHASE] = current_ekran.index_position;
                //Формуємо екран управлінської інформації для "Перевірки фаз"
                make_ekran_control_ctrl_phase();
              }
              else if((current_ekran.current_level >= EKRAN_TIMEOUT_ALARMS1) && (current_ekran.current_level <= EKRAN_TIMEOUT_ALARMS2))
              {
                if(current_ekran.edition == 0)
                {
                  if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_TIMEOUT_ALARMS - 1;
                  position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;
                }
                else
                {
                  //Редагування числа
                  if (current_ekran.index_position == INDEX_ML_ALARM_SOUND_PERIOD)
                    edition_settings.timeout_alarm_sound_period[current_ekran.current_level - EKRAN_TIMEOUT_ALARMS1] = edit_setpoint(1, edition_settings.timeout_alarm_sound_period[current_ekran.current_level - EKRAN_TIMEOUT_ALARMS1], 1, COL_TMO_ALARM_SOUND_PERIOD_COMMA, COL_TMO_ALARM_SOUND_PERIOD_END, 100);
                }
                //Формуємо екран витримок виключателя
                make_ekran_timeout_alarms(current_ekran.current_level - EKRAN_TIMEOUT_ALARMS1);
              }
              else if((current_ekran.current_level >= EKRAN_CONTROL_ALARMS1) && (current_ekran.current_level <= EKRAN_CONTROL_ALARMS2))
              {
                if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_FOR_CONTROL_ALARMS - 1;
                position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;
                //Формуємо екран управлінської інформації для сигналізації
                make_ekran_control_alarms(current_ekran.current_level - EKRAN_CONTROL_ALARMS1);
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
                  //Редагування числа
                  edition_settings.dopusk_dv[current_ekran.index_position] = 
                    edit_setpoint(1, edition_settings.dopusk_dv[current_ekran.index_position], 0, 0, COL_DOPUSK_DV_END, 1);
                }
                //Формуємо екран інфтрмації по допусках ДВ
                make_ekran_dopusk_dv();
              }
              else if (current_ekran.current_level == EKRAN_TYPE_INPUT_SIGNAL_UVV)
              {
                if(--current_ekran.index_position < 0) current_ekran.index_position = NUMBER_INPUTS - 1;
                position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;
                //Формуємо екран управлінської інформації для УВВ
                make_ekran_type_input_uvv();
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
                  //Редагування числа
                  edition_settings.address = edit_setpoint(1, edition_settings.address, 0, 0, COL_ADDRESS_END, 1);
                }
                //Формуємо екран інфтрмації по комунікаційній адресі
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
                  //Редагування числа
                  edition_settings.speed_RS485--;
                  if (edition_settings.speed_RS485 < VALUE_SPEED_INTERFACE_MIN)
                    edition_settings.speed_RS485 = VALUE_SPEED_INTERFACE_MAX;
                }
                //Формуємо екран інформації по швидкості обміну
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
                  //Редагування числа
                  edition_settings.pare_bit_RS485--;
                  if (edition_settings.pare_bit_RS485 < VALUE_PARE_INTERFACE_MIN)
                    edition_settings.pare_bit_RS485 = VALUE_PARE_INTERFACE_MAX;
                }
                //Формуємо екран інформації по контролю парності
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
                  //Редагування числа
                  edition_settings.number_stop_bit_RS485--;
                  if (edition_settings.number_stop_bit_RS485 < VALUE_STOP_BITS_INTERFACE_MIN)
                    edition_settings.number_stop_bit_RS485 = VALUE_STOP_BITS_INTERFACE_MAX;
                }
                //Формуємо екран інформації по кількості стопових біт
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
                  //Редагування числа
                  edition_settings.time_out_1_RS485 = edit_setpoint(1, edition_settings.time_out_1_RS485, 1, COL_TIMEOUT_INTERFACE_COMMA, COL_TIMEOUT_INTERFACE_END, 1);
                }
                //Формуємо екран інформації по time-out наступного символу
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
                  //Редагування числа
                  if (current_ekran.index_position == INDEX_ML_NUMBER_INERATION)
                  {
                    edition_settings.number_iteration_el = edit_setpoint(1, edition_settings.number_iteration_el, 0, 0, COL_NUMBER_INERATION_END, 1);
                  }
                  else if (current_ekran.index_position == INDEX_ML_NUMBER_DEFINED_FUNCTIONS)
                  {
                    edition_settings.number_defined_df = edit_setpoint(1, edition_settings.number_defined_df, 0, 0, COL_NUMBER_DEFINED_FUNCTIONS_END, 1);
                  }
                  else if (current_ekran.index_position == INDEX_ML_NUMBER_DEFINED_TRIGGERS)
                  {
                    edition_settings.number_defined_dt = edit_setpoint(1, edition_settings.number_defined_dt, 0, 0, COL_NUMBER_DEFINED_TRIGGERS_END, 1);
                  }
                  else if (current_ekran.index_position == INDEX_ML_NUMBER_DEFINED_AND)
                  {
                    edition_settings.number_defined_and = edit_setpoint(1, edition_settings.number_defined_and, 0, 0, COL_NUMBER_DEFINED_AND_END, 1);
                  }
                  else if (current_ekran.index_position == INDEX_ML_NUMBER_DEFINED_OR)
                  {
                    edition_settings.number_defined_or = edit_setpoint(1, edition_settings.number_defined_or, 0, 0, COL_NUMBER_DEFINED_OR_END, 1);
                  }
                  else if (current_ekran.index_position == INDEX_ML_NUMBER_DEFINED_XOR)
                  {
                    edition_settings.number_defined_xor = edit_setpoint(1, edition_settings.number_defined_xor, 0, 0, COL_NUMBER_DEFINED_XOR_END, 1);
                  }
                  else if (current_ekran.index_position == INDEX_ML_NUMBER_DEFINED_NOT)
                  {
                    edition_settings.number_defined_not = edit_setpoint(1, edition_settings.number_defined_not, 0, 0, COL_NUMBER_DEFINED_NOT_END, 1);
                  }
                }
                //Формуємо екран відображення загальних витримок для розширеної логіки
                make_ekran_general_pickups_el();
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
                  //Редагування числа
                  if (current_ekran.index_position == INDEX_ML_TMOPREFAULT)
                  {
                    unsigned int temp_setpoint = edition_settings.prefault_number_periods*20;
                    do
                    {
                      //Величину витримки збільшуємо почергого на 10 мс (ф-ція edit_setpoint збільшує/зменшує з крогом кратних 1, 10 і т.д.), щоб отримати крок 20 мс
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
                      //Величину витримки збільшуємо почергого на 10 мс (ф-ція edit_setpoint збільшує/зменшує з крогом кратних 1, 10 і т.д.), щоб отримати крок 20 мс
                      temp_setpoint = edit_setpoint(1, temp_setpoint, 1, COL_TMO_PREFAULT_COMMA, COL_TMO_PREFAULT_END, 10);
                    }
                    while ((temp_setpoint % 20) != 0);
                    edition_settings.postfault_number_periods = temp_setpoint / 20;
                  }
                }
                //Формуємо екран витримок аналогового реєстратора
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
                  //Редагування числа
                  edition_settings.language--;
                  if (edition_settings.language < VALUE_SETTING_LANGUAGE_MIN)
                    edition_settings.language = VALUE_SETTING_LANGUAGE_MAX;
                }
                //Формуємо екран інформації по мові меню
                make_ekran_setting_language();
              }

              //Очистити сигналізацію, що натиснута кнопка 
              new_state_keyboard &= (unsigned int)(~(1<<BIT_KEY_UP));
            }
            else if (new_state_keyboard == (1<<BIT_KEY_DOWN))
            {
              //Натиснута кнопка DOWN
              if(
                 (current_ekran.current_level == EKRAN_SETPOINT_CTRL_PHASE)
                )   
              {
                if(current_ekran.edition == 0)
                {
                  if(++current_ekran.index_position >= MAX_ROW_FOR_SETPOINT_CTRL_PHASE) current_ekran.index_position = 0;
                  position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;
                }
                else
                {
                  //Редагування числа
                  if (current_ekran.index_position == INDEX_ML_STPCTRL_PHASE_U)
                    edition_settings.setpoint_ctrl_phase_U = edit_setpoint(0, edition_settings.setpoint_ctrl_phase_U, 1, COL_SETPOINT_CTRL_PHASE_U_COMMA, COL_SETPOINT_CTRL_PHASE_U_END, 100);
                  else if (current_ekran.index_position == INDEX_ML_STPCTRL_PHASE_PHI)
                    edition_settings.setpoint_ctrl_phase_phi = edit_setpoint(0, edition_settings.setpoint_ctrl_phase_phi, 1, COL_SETPOINT_CTRL_PHASE_PHI_COMMA, COL_SETPOINT_CTRL_PHASE_PHI_END, 1);
                  else if (current_ekran.index_position == INDEX_ML_STPCTRL_PHASE_F)
                    edition_settings.setpoint_ctrl_phase_f = edit_setpoint(0, edition_settings.setpoint_ctrl_phase_f, 1, COL_SETPOINT_CTRL_PHASE_F_COMMA, COL_SETPOINT_CTRL_PHASE_F_END, 10);
                }
                //Формуємо екран уставок "Перевірки фазування"
                make_ekran_setpoint_ctrl_phase();
              }
              else if(
                      (current_ekran.current_level == EKRAN_TIMEOUT_CTRL_PHASE)
                     )   
              {
                if(current_ekran.edition == 0)
                {
                  if(++current_ekran.index_position >= MAX_ROW_FOR_TIMEOUT_CTRL_PHASE) current_ekran.index_position = 0;
                  position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;
                }
                else
                {
                  //Редагування числа
                  if (current_ekran.index_position == INDEX_ML_TMOCTRL_PHASE_U)
                    edition_settings.timeout_ctrl_phase_U = edit_setpoint(0, edition_settings.timeout_ctrl_phase_U, 1, COL_TMO_CTRL_PHASE_U_COMMA, COL_TMO_CTRL_PHASE_U_END, 10);
                  else if (current_ekran.index_position == INDEX_ML_TMOCTRL_PHASE_U_D)
                    edition_settings.timeout_ctrl_phase_U_d = edit_setpoint(0, edition_settings.timeout_ctrl_phase_U_d, 1, COL_TMO_CTRL_PHASE_U_D_COMMA, COL_TMO_CTRL_PHASE_U_D_END, 10);
                  else if (current_ekran.index_position == INDEX_ML_TMOCTRL_PHASE_PHI)
                    edition_settings.timeout_ctrl_phase_phi = edit_setpoint(0, edition_settings.timeout_ctrl_phase_phi, 1, COL_TMO_CTRL_PHASE_PHI_COMMA, COL_TMO_CTRL_PHASE_PHI_END, 10);
                  else if (current_ekran.index_position == INDEX_ML_TMOCTRL_PHASE_PHI_D)
                    edition_settings.timeout_ctrl_phase_phi_d = edit_setpoint(0, edition_settings.timeout_ctrl_phase_phi_d, 1, COL_TMO_CTRL_PHASE_PHI_D_COMMA, COL_TMO_CTRL_PHASE_PHI_D_END, 10);
                  else if (current_ekran.index_position == INDEX_ML_TMOCTRL_PHASE_F)
                    edition_settings.timeout_ctrl_phase_f = edit_setpoint(0, edition_settings.timeout_ctrl_phase_f, 1, COL_TMO_CTRL_PHASE_F_COMMA, COL_TMO_CTRL_PHASE_F_END, 10);
                  else if (current_ekran.index_position == INDEX_ML_TMOCTRL_PHASE_F_D)
                    edition_settings.timeout_ctrl_phase_f_d = edit_setpoint(0, edition_settings.timeout_ctrl_phase_f_d, 1, COL_TMO_CTRL_PHASE_F_D_COMMA, COL_TMO_CTRL_PHASE_F_D_END, 10);
                }
                //Формуємо екран витримок "Перевірки фазування"
                make_ekran_timeout_ctrl_phase();
              }
              else if(current_ekran.current_level == EKRAN_CONTROL_CTRL_PHASE)
              {
                if(++current_ekran.index_position >= MAX_ROW_FOR_CONTROL_CTRL_PHASE) current_ekran.index_position = 0;
                position_in_current_level_menu[EKRAN_CONTROL_CTRL_PHASE] = current_ekran.index_position;
                //Формуємо екран управлінської інформації для "Перевірки фазування"
                make_ekran_control_ctrl_phase();
              }
              else if((current_ekran.current_level >= EKRAN_TIMEOUT_ALARMS1) && (current_ekran.current_level <= EKRAN_TIMEOUT_ALARMS2))
              {
                if(current_ekran.edition == 0)
                {
                  if(++current_ekran.index_position >= MAX_ROW_FOR_TIMEOUT_ALARMS) current_ekran.index_position = 0;
                  position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;
                }
                else
                {
                  //Редагування числа
                  if (current_ekran.index_position == INDEX_ML_ALARM_SOUND_PERIOD)
                    edition_settings.timeout_alarm_sound_period[current_ekran.current_level - EKRAN_TIMEOUT_ALARMS1] = edit_setpoint(0, edition_settings.timeout_alarm_sound_period[current_ekran.current_level - EKRAN_TIMEOUT_ALARMS1], 1, COL_TMO_ALARM_SOUND_PERIOD_COMMA, COL_TMO_ALARM_SOUND_PERIOD_END, 100);
                }
                //Формуємо екран витримок виключателя
                make_ekran_timeout_alarms(current_ekran.current_level - EKRAN_TIMEOUT_ALARMS1);
              }
              else if((current_ekran.current_level >= EKRAN_CONTROL_ALARMS1) && (current_ekran.current_level <= EKRAN_CONTROL_ALARMS2))
              {
                if(++current_ekran.index_position >= MAX_ROW_FOR_CONTROL_ALARMS) current_ekran.index_position = 0;
                position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;
                //Формуємо екран управлінської інформації для сигналізації
                make_ekran_control_alarms(current_ekran.current_level - EKRAN_CONTROL_ALARMS1);
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
                  //Редагування числа
                  edition_settings.dopusk_dv[current_ekran.index_position] = 
                    edit_setpoint(0, edition_settings.dopusk_dv[current_ekran.index_position], 0, 0, COL_DOPUSK_DV_END, 1);
                }
                //Формуємо екран інфтрмації по допусках ДВ
                make_ekran_dopusk_dv();
              }
              else if (current_ekran.current_level == EKRAN_TYPE_INPUT_SIGNAL_UVV)
              {
                if(++current_ekran.index_position >= NUMBER_INPUTS) current_ekran.index_position = 0;
                position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;
                //Формуємо екран управлінської інформації для УВВ
                make_ekran_type_input_uvv();
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
                  //Редагування числа
                  edition_settings.address = edit_setpoint(0, edition_settings.address, 0, 0, COL_ADDRESS_END, 1);
                }
                //Формуємо екран інфтрмації по комунікаційній адресі
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
                  //Редагування числа
                  edition_settings.speed_RS485++;
                  if (edition_settings.speed_RS485 > VALUE_SPEED_INTERFACE_MAX)
                    edition_settings.speed_RS485 = VALUE_SPEED_INTERFACE_MIN;
                }
                //Формуємо екран інформації по швидкості обміну
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
                  //Редагування числа
                  edition_settings.pare_bit_RS485++;
                  if (edition_settings.pare_bit_RS485 > VALUE_PARE_INTERFACE_MAX)
                    edition_settings.pare_bit_RS485 = VALUE_PARE_INTERFACE_MIN;
                }
                //Формуємо екран інформації по контролю парності
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
                  //Редагування числа
                  edition_settings.number_stop_bit_RS485++;
                  if (edition_settings.number_stop_bit_RS485 > VALUE_STOP_BITS_INTERFACE_MAX)
                    edition_settings.number_stop_bit_RS485 = VALUE_STOP_BITS_INTERFACE_MIN;
                }
                //Формуємо екран інформації по кількості стопових біт
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
                  //Редагування числа
                  edition_settings.time_out_1_RS485 = edit_setpoint(0, edition_settings.time_out_1_RS485, 1, COL_TIMEOUT_INTERFACE_COMMA, COL_TIMEOUT_INTERFACE_END, 1);
                }
                //Формуємо екран інформації по time-out наступного символу
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
                  //Редагування числа
                  if (current_ekran.index_position == INDEX_ML_NUMBER_INERATION)
                  {
                    edition_settings.number_iteration_el = edit_setpoint(0, edition_settings.number_iteration_el, 0, 0, COL_NUMBER_INERATION_END, 1);
                  }
                  else if (current_ekran.index_position == INDEX_ML_NUMBER_DEFINED_FUNCTIONS)
                  {
                    edition_settings.number_defined_df = edit_setpoint(0, edition_settings.number_defined_df, 0, 0, COL_NUMBER_DEFINED_FUNCTIONS_END, 1);
                  }
                  else if (current_ekran.index_position == INDEX_ML_NUMBER_DEFINED_TRIGGERS)
                  {
                    edition_settings.number_defined_dt = edit_setpoint(0, edition_settings.number_defined_dt, 0, 0, COL_NUMBER_DEFINED_TRIGGERS_END, 1);
                  }
                  else if (current_ekran.index_position == INDEX_ML_NUMBER_DEFINED_AND)
                  {
                    edition_settings.number_defined_and = edit_setpoint(0, edition_settings.number_defined_and, 0, 0, COL_NUMBER_DEFINED_AND_END, 1);
                  }
                  else if (current_ekran.index_position == INDEX_ML_NUMBER_DEFINED_OR)
                  {
                    edition_settings.number_defined_or = edit_setpoint(0, edition_settings.number_defined_or, 0, 0, COL_NUMBER_DEFINED_OR_END, 1);
                  }
                  else if (current_ekran.index_position == INDEX_ML_NUMBER_DEFINED_XOR)
                  {
                    edition_settings.number_defined_xor = edit_setpoint(0, edition_settings.number_defined_xor, 0, 0, COL_NUMBER_DEFINED_XOR_END, 1);
                  }
                  else if (current_ekran.index_position == INDEX_ML_NUMBER_DEFINED_NOT)
                  {
                    edition_settings.number_defined_not = edit_setpoint(0, edition_settings.number_defined_not, 0, 0, COL_NUMBER_DEFINED_NOT_END, 1);
                  }
                }
                //Формуємо екран відображення загальних витримок для розширеної логіки
                make_ekran_general_pickups_el();
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
                  //Редагування числа
                  if (current_ekran.index_position == INDEX_ML_TMOPREFAULT)
                  {
                    unsigned int temp_setpoint = edition_settings.prefault_number_periods*20;
                    do
                    {
                      //Величину витримки зменшуємо почергого на 10 мс (ф-ція edit_setpoint збільшує/зменшує з крогом кратних 1, 10 і т.д.), щоб отримати крок 20 мс
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
                      //Величину витримки зменшуємо почергого на 10 мс (ф-ція edit_setpoint збільшує/зменшує з крогом кратних 1, 10 і т.д.), щоб отримати крок 20 мс
                      temp_setpoint = edit_setpoint(0, temp_setpoint, 1, COL_TMO_PREFAULT_COMMA, COL_TMO_PREFAULT_END, 10);
                    }
                    while ((temp_setpoint % 20) != 0);
                    edition_settings.postfault_number_periods = temp_setpoint / 20;
                  }
                }
                //Формуємо екран витримок аналогового реєстратора
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
                  //Редагування числа
                  edition_settings.language++;
                  if (edition_settings.language > VALUE_SETTING_LANGUAGE_MAX)
                    edition_settings.language = VALUE_SETTING_LANGUAGE_MIN;
                }
                //Формуємо екран інформації по мові меню
                make_ekran_setting_language();
              }

              //Очистити сигналізацію, що натиснута кнопка 
              new_state_keyboard &= (unsigned int)(~(1<<BIT_KEY_DOWN));
            }
            else if (new_state_keyboard == (1<<BIT_KEY_RIGHT))
            {
              current_ekran.position_cursor_x++;
              //Перевіряємо, чи ми не вийшли за межі виділені для значення даної уставки, або позицію коми
              if(
                 (current_ekran.current_level == EKRAN_SETPOINT_CTRL_PHASE)
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

                //Формуємо екран уставок "Перевірки фазування"
                make_ekran_setpoint_ctrl_phase();
              }
              else if(
                      (current_ekran.current_level == EKRAN_TIMEOUT_CTRL_PHASE)
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

                //Формуємо екран витримок "Перевірки фазування"
                make_ekran_timeout_ctrl_phase();
              }
              else if(current_ekran.current_level == EKRAN_CONTROL_CTRL_PHASE)
              {
                unsigned int maska = 0;
          
                //Виділяємо, який біт треба міняти
                if      (current_ekran.index_position == INDEX_CTR_CTRL_PHASE_U      ) maska = CTR_CTRL_PHASE_U;
                else if (current_ekran.index_position == INDEX_CTR_CTRL_PHASE_PHI    ) maska = CTR_CTRL_PHASE_PHI;
                else if (current_ekran.index_position == INDEX_CTR_CTRL_PHASE_F      ) maska = CTR_CTRL_PHASE_F;
                else if (current_ekran.index_position == INDEX_CTR_CTRL_PHASE_SEQ_TN1) maska = CTR_CTRL_PHASE_SEQ_TN1;
                else if (current_ekran.index_position == INDEX_CTR_CTRL_PHASE_SEQ_TN2) maska = CTR_CTRL_PHASE_SEQ_TN2;
                
                //Міняємо на протилежний відповідний біт для вибраної позиції
                edition_settings.control_ctrl_phase ^= maska;

                //Формуємо екран управлінської інформації для "Пкпквірки фазування"
                 make_ekran_control_ctrl_phase();
              }
              else if((current_ekran.current_level >= EKRAN_TIMEOUT_ALARMS1) && (current_ekran.current_level <= EKRAN_TIMEOUT_ALARMS2))
              {
                if(current_ekran.index_position == INDEX_ML_ALARM_SOUND_PERIOD)
                {
                  if (current_ekran.position_cursor_x == COL_TMO_ALARM_SOUND_PERIOD_COMMA )current_ekran.position_cursor_x++;
                  if ((current_ekran.position_cursor_x < COL_TMO_ALARM_SOUND_PERIOD_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TMO_ALARM_SOUND_PERIOD_END))
                    current_ekran.position_cursor_x = COL_TMO_ALARM_SOUND_PERIOD_BEGIN;
                }
                //Формуємо екран витримок виключателя
                make_ekran_timeout_alarms(current_ekran.current_level - EKRAN_TIMEOUT_ALARMS1);
              }
              else if((current_ekran.current_level >= EKRAN_CONTROL_ALARMS1) && (current_ekran.current_level <= EKRAN_CONTROL_ALARMS2))
              {
                unsigned int maska = 0;
          
                //Виділяємо, який біт треба міняти
                if (current_ekran.index_position == INDEX_ML_CTR_ALARMS_MODE) maska = CTR_ALARMS_MODE << (ALARMS_SEPARATOR*(current_ekran.current_level - EKRAN_CONTROL_ALARMS1));
                
                //Міняємо на протилежний відповідний біт для вибраної позиції
                edition_settings.control_alarm ^= maska;

                //Формуємо екран управлінської інформації для сигналізації
                make_ekran_control_alarms(current_ekran.current_level - EKRAN_CONTROL_ALARMS1);
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

                //Формуємо екран інфтрмації по допусках ДВ
                make_ekran_dopusk_dv();
              }
              else if (current_ekran.current_level == EKRAN_TYPE_INPUT_SIGNAL_UVV)
              {
                unsigned int value = (1 << current_ekran.index_position);
          
                //Міняємо на протилежний відповідний біт для вибраної позиції і формуємо екран управлінської інформації для УВВ
                edition_settings.type_of_input_signal ^= value;
                make_ekran_type_input_uvv();
              }
              else if(current_ekran.current_level == EKRAN_ADDRESS)
              {
                if ((current_ekran.position_cursor_x < COL_ADDRESS_BEGIN) ||
                    (current_ekran.position_cursor_x > COL_ADDRESS_END))
                  current_ekran.position_cursor_x = COL_ADDRESS_BEGIN;
                //Формуємо екран інфтрмації по комунікаційній адресі
                make_ekran_address();
              }
              else if(current_ekran.current_level == EKRAN_VIEW_TIMEOUT_RS485)
              {
                if (current_ekran.position_cursor_x == COL_TIMEOUT_INTERFACE_COMMA )current_ekran.position_cursor_x++;
                if ((current_ekran.position_cursor_x < COL_TIMEOUT_INTERFACE_BEGIN) ||
                    (current_ekran.position_cursor_x > COL_TIMEOUT_INTERFACE_END))
                  current_ekran.position_cursor_x = COL_TIMEOUT_INTERFACE_BEGIN;
                //Формуємо екран інформації по time-out наступного символу
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
                else if(current_ekran.index_position == INDEX_ML_NUMBER_DEFINED_FUNCTIONS)
                {
                  if ((current_ekran.position_cursor_x < COL_NUMBER_DEFINED_FUNCTIONS_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_NUMBER_DEFINED_FUNCTIONS_END))
                    current_ekran.position_cursor_x = COL_NUMBER_DEFINED_FUNCTIONS_BEGIN;
                }
                else if(current_ekran.index_position == INDEX_ML_NUMBER_DEFINED_TRIGGERS)
                {
                  if ((current_ekran.position_cursor_x < COL_NUMBER_DEFINED_TRIGGERS_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_NUMBER_DEFINED_TRIGGERS_END))
                    current_ekran.position_cursor_x = COL_NUMBER_DEFINED_TRIGGERS_BEGIN;
                }
                else if(current_ekran.index_position == INDEX_ML_NUMBER_DEFINED_AND)
                {
                  if ((current_ekran.position_cursor_x < COL_NUMBER_DEFINED_AND_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_NUMBER_DEFINED_AND_END))
                    current_ekran.position_cursor_x = COL_NUMBER_DEFINED_AND_BEGIN;
                }
                else if(current_ekran.index_position == INDEX_ML_NUMBER_DEFINED_OR)
                {
                  if ((current_ekran.position_cursor_x < COL_NUMBER_DEFINED_OR_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_NUMBER_DEFINED_OR_END))
                    current_ekran.position_cursor_x = COL_NUMBER_DEFINED_OR_BEGIN;
                }
                else if(current_ekran.index_position == INDEX_ML_NUMBER_DEFINED_XOR)
                {
                  if ((current_ekran.position_cursor_x < COL_NUMBER_DEFINED_XOR_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_NUMBER_DEFINED_XOR_END))
                    current_ekran.position_cursor_x = COL_NUMBER_DEFINED_XOR_BEGIN;
                }
                else if(current_ekran.index_position == INDEX_ML_NUMBER_DEFINED_NOT)
                {
                  if ((current_ekran.position_cursor_x < COL_NUMBER_DEFINED_NOT_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_NUMBER_DEFINED_NOT_END))
                    current_ekran.position_cursor_x = COL_NUMBER_DEFINED_NOT_BEGIN;
                }
                
                //Формуємо екран відображення загальних витримок для розширеної логіки
                make_ekran_general_pickups_el();
              }
              else if(current_ekran.current_level == EKRAN_LIST_TYPE_DF)
              {
                unsigned int value = (1 << current_ekran.index_position);
          
                //Міняємо на протилежний відповідний біт для вибраної позиції
                edition_settings.type_df ^= value;

                //Формуємо екран відображення типу опреділювальної функції
                make_ekran_type_df();
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
                //Формуємо екран витримок аналогового реєстратора
                make_ekran_timeout_analog_registrator();
              }

              //Очистити сигналізацію, що натиснута кнопка 
              new_state_keyboard &= (unsigned int)(~(1<<BIT_KEY_RIGHT));
            }
            else if (new_state_keyboard == (1<<BIT_KEY_LEFT))
            {
              current_ekran.position_cursor_x--;
              //Перевіряємо, чи ми не вийшли за межі виділені для значення даної уставки, або позицію коми
              if(
                 (current_ekran.current_level == EKRAN_SETPOINT_CTRL_PHASE)
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

                //Формуємо екран уставок "Перевірки фазування"
                make_ekran_setpoint_ctrl_phase();
              }
              else if(
                      (current_ekran.current_level == EKRAN_TIMEOUT_CTRL_PHASE)
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

                //Формуємо екран витримок "Перевірки фазування"
                make_ekran_timeout_ctrl_phase();
              }
              else if(current_ekran.current_level == EKRAN_CONTROL_CTRL_PHASE)
              {
                unsigned int maska = 0;
          
                //Виділяємо, який біт треба міняти
                if      (current_ekran.index_position == INDEX_CTR_CTRL_PHASE_U      ) maska = CTR_CTRL_PHASE_U;
                else if (current_ekran.index_position == INDEX_CTR_CTRL_PHASE_PHI    ) maska = CTR_CTRL_PHASE_PHI;
                else if (current_ekran.index_position == INDEX_CTR_CTRL_PHASE_F      ) maska = CTR_CTRL_PHASE_F;
                else if (current_ekran.index_position == INDEX_CTR_CTRL_PHASE_SEQ_TN1) maska = CTR_CTRL_PHASE_SEQ_TN1;
                else if (current_ekran.index_position == INDEX_CTR_CTRL_PHASE_SEQ_TN2) maska = CTR_CTRL_PHASE_SEQ_TN2;
                
                //Міняємо на протилежний відповідний біт для вибраної позиції
                edition_settings.control_ctrl_phase ^= maska;

                //Формуємо екран управлінської інформації для "Перевірки фазування"
                 make_ekran_control_ctrl_phase();
              }
              else if((current_ekran.current_level >= EKRAN_TIMEOUT_ALARMS1) && (current_ekran.current_level <= EKRAN_TIMEOUT_ALARMS2))
              {
                if(current_ekran.index_position == INDEX_ML_ALARM_SOUND_PERIOD)
                {
                  if (current_ekran.position_cursor_x == COL_TMO_ALARM_SOUND_PERIOD_COMMA )current_ekran.position_cursor_x--;
                  if ((current_ekran.position_cursor_x < COL_TMO_ALARM_SOUND_PERIOD_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_TMO_ALARM_SOUND_PERIOD_END))
                    current_ekran.position_cursor_x = COL_TMO_ALARM_SOUND_PERIOD_END;
                }
                //Формуємо екран витримок виключателя
               make_ekran_timeout_alarms(current_ekran.current_level - EKRAN_TIMEOUT_ALARMS1);
              }
              else if((current_ekran.current_level >= EKRAN_CONTROL_ALARMS1) && (current_ekran.current_level <= EKRAN_CONTROL_ALARMS2))
              {
                unsigned int maska = 0;
          
                //Виділяємо, який біт треба міняти
                if (current_ekran.index_position == INDEX_ML_CTR_ALARMS_MODE) maska = CTR_ALARMS_MODE << (ALARMS_SEPARATOR*(current_ekran.current_level - EKRAN_CONTROL_ALARMS1));
                
                //Міняємо на протилежний відповідний біт для вибраної позиції
                edition_settings.control_alarm ^= maska;

                //Формуємо екран управлінської інформації для сигналізації
                make_ekran_control_alarms(current_ekran.current_level - EKRAN_CONTROL_ALARMS1);
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
                
                //Формуємо екран інфтрмації по допусках ДВ
                make_ekran_dopusk_dv();
              }
              else if (current_ekran.current_level == EKRAN_TYPE_INPUT_SIGNAL_UVV)
              {
                unsigned int value = (1 << current_ekran.index_position);
          
                //Міняємо на протилежний відповідний біт для вибраної позиції і формуємо екран управлінської інформації для УВВ
                edition_settings.type_of_input_signal ^= value;
                make_ekran_type_input_uvv();
              }
              else if(current_ekran.current_level == EKRAN_ADDRESS)
              {
                  if ((current_ekran.position_cursor_x < COL_ADDRESS_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_ADDRESS_END))
                    current_ekran.position_cursor_x = COL_ADDRESS_END;
                  //Формуємо екран інфтрмації по комунікаційній адресі
                  make_ekran_address();
              }
              else if(current_ekran.current_level == EKRAN_VIEW_TIMEOUT_RS485)
              {
                if (current_ekran.position_cursor_x == COL_TIMEOUT_INTERFACE_COMMA )current_ekran.position_cursor_x--;
                if ((current_ekran.position_cursor_x < COL_TIMEOUT_INTERFACE_BEGIN) ||
                    (current_ekran.position_cursor_x > COL_TIMEOUT_INTERFACE_END))
                  current_ekran.position_cursor_x = COL_TIMEOUT_INTERFACE_END;
                //Формуємо екран інформації по time-out наступного символу
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
                else if(current_ekran.index_position == INDEX_ML_NUMBER_DEFINED_FUNCTIONS)
                {
                  if ((current_ekran.position_cursor_x < COL_NUMBER_DEFINED_FUNCTIONS_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_NUMBER_DEFINED_FUNCTIONS_END))
                    current_ekran.position_cursor_x = COL_NUMBER_DEFINED_FUNCTIONS_END;
                }
                else if(current_ekran.index_position == INDEX_ML_NUMBER_DEFINED_TRIGGERS)
                {
                  if ((current_ekran.position_cursor_x < COL_NUMBER_DEFINED_TRIGGERS_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_NUMBER_DEFINED_TRIGGERS_END))
                    current_ekran.position_cursor_x = COL_NUMBER_DEFINED_TRIGGERS_END;
                }
                else if(current_ekran.index_position == INDEX_ML_NUMBER_DEFINED_AND)
                {
                  if ((current_ekran.position_cursor_x < COL_NUMBER_DEFINED_AND_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_NUMBER_DEFINED_AND_END))
                    current_ekran.position_cursor_x = COL_NUMBER_DEFINED_AND_END;
                }
                else if(current_ekran.index_position == INDEX_ML_NUMBER_DEFINED_OR)
                {
                  if ((current_ekran.position_cursor_x < COL_NUMBER_DEFINED_OR_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_NUMBER_DEFINED_OR_END))
                    current_ekran.position_cursor_x = COL_NUMBER_DEFINED_OR_END;
                }
                else if(current_ekran.index_position == INDEX_ML_NUMBER_DEFINED_XOR)
                {
                  if ((current_ekran.position_cursor_x < COL_NUMBER_DEFINED_XOR_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_NUMBER_DEFINED_XOR_END))
                    current_ekran.position_cursor_x = COL_NUMBER_DEFINED_XOR_END;
                }
                else if(current_ekran.index_position == INDEX_ML_NUMBER_DEFINED_NOT)
                {
                  if ((current_ekran.position_cursor_x < COL_NUMBER_DEFINED_NOT_BEGIN) ||
                      (current_ekran.position_cursor_x > COL_NUMBER_DEFINED_NOT_END))
                    current_ekran.position_cursor_x = COL_NUMBER_DEFINED_NOT_END;
                }
                
                //Формуємо екран відображення загальних витримок для розширеної логіки
                make_ekran_general_pickups_el();
              }
              else if(current_ekran.current_level == EKRAN_LIST_TYPE_DF)
              {
                unsigned int value = (1 << current_ekran.index_position);
          
                //Міняємо на протилежний відповідний біт для вибраної позиції
                edition_settings.type_df ^= value;

                //Формуємо екран відображення типу опреділювальної функції
                make_ekran_type_df();
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
                //Формуємо екран витримок аналогового реєстратора
                make_ekran_timeout_analog_registrator();
              }

              //Очистити сигналізацію, що натиснута кнопка 
              new_state_keyboard &= (unsigned int)(~(1<<BIT_KEY_LEFT));
            }
            else
            {
              //Натиснуто зразу декілька кнопок - це є невизначена ситуація, тому скидаємо сигналізацію про натиснуті кнопки і чекаємо знову
              unsigned int temp_data = new_state_keyboard;
              new_state_keyboard &= ~temp_data;
            }
          }
        }
        break;
      }
/******************************************************************************************************************************************/ 

/******************************************************************************************************************************************/      
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
    case EKRAN_RANGUVANNJA_SILENCE:
    case EKRAN_RANGUVANNJA_RESET:
    case EKRAN_RANGUVANNJA_TEST:
    case EKRAN_RANGUVANNJA_ANALOG_REGISTRATOR:
    case EKRAN_RANGUVANNJA_DIGITAL_REGISTRATOR:
    case EKRAN_RANGUVANNJA_ALARMS1:
    case EKRAN_RANGUVANNJA_ALARMS2:
    case EKRAN_RANGUVANNJA_DF1:
    case EKRAN_RANGUVANNJA_DF2:
    case EKRAN_RANGUVANNJA_DF3:
    case EKRAN_RANGUVANNJA_DF4:
    case EKRAN_RANGUVANNJA_DF5:
    case EKRAN_RANGUVANNJA_DF6:
    case EKRAN_RANGUVANNJA_DF7:
    case EKRAN_RANGUVANNJA_DF8:
    case EKRAN_RANGUVANNJA_SET_DT1:
    case EKRAN_RANGUVANNJA_RESET_DT1:
    case EKRAN_RANGUVANNJA_SET_DT2:
    case EKRAN_RANGUVANNJA_RESET_DT2:
    case EKRAN_RANGUVANNJA_SET_DT3:
    case EKRAN_RANGUVANNJA_RESET_DT3:
    case EKRAN_RANGUVANNJA_SET_DT4:
    case EKRAN_RANGUVANNJA_RESET_DT4:
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
      {
        //Очищаємо всі біти краім упралінських
        unsigned int maska_keyboard_bits = (1<<BIT_KEY_ENTER)| (1<<BIT_KEY_ESC)|(1<<BIT_REWRITE);
        
        if (current_ekran.edition == 1)
          maska_keyboard_bits |= (1<<BIT_KEY_RIGHT) | (1<<BIT_KEY_LEFT) | (1<<BIT_KEY_UP)|(1<<BIT_KEY_DOWN);
        else if (current_ekran.edition == 0)
          maska_keyboard_bits |= (1<<BIT_KEY_UP)|(1<<BIT_KEY_DOWN);
        
        new_state_keyboard &= maska_keyboard_bits;
        //Дальше виконуємо дії, якщо натиснута кнопка на яку треба реагівати, або стоїть команда обновити екран
        if (new_state_keyboard !=0)
        {
          //Пріоритет стоїть на обновлені екрану
          if((new_state_keyboard & (1<<BIT_REWRITE)) !=0)
          {
            if (
                ((current_ekran.current_level >= EKRAN_RANGUVANNJA_OUTPUT_1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_OUTPUT_10)) ||
                ((current_ekran.current_level >= EKRAN_RANGUVANNJA_LED_1   ) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_LED_8    )) ||
                ( current_ekran.current_level == EKRAN_RANGUVANNJA_SILENCE                                                                  ) ||
                ( current_ekran.current_level == EKRAN_RANGUVANNJA_RESET                                                                    ) ||
                ( current_ekran.current_level == EKRAN_RANGUVANNJA_ANALOG_REGISTRATOR                                                       ) ||
                ( current_ekran.current_level == EKRAN_RANGUVANNJA_DIGITAL_REGISTRATOR                                                      ) ||
                ((current_ekran.current_level >= EKRAN_RANGUVANNJA_ALARMS1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_ALARMS2   )) ||
                ((current_ekran.current_level >= EKRAN_RANGUVANNJA_DF1    ) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_DF8       )) ||
                ((current_ekran.current_level >= EKRAN_RANGUVANNJA_SET_DT1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_RESET_DT4 )) ||
                ((current_ekran.current_level >= EKRAN_RANGUVANNJA_D_AND1 ) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_AND8    )) ||
                ((current_ekran.current_level >= EKRAN_RANGUVANNJA_D_OR1  ) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_OR8     )) ||
                ((current_ekran.current_level >= EKRAN_RANGUVANNJA_D_XOR1 ) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_XOR8    )) ||
                ((current_ekran.current_level >= EKRAN_RANGUVANNJA_D_NOT1 ) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_NOT16   ))
               )
            {
              int max_row_ranguvannja;
              
              if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_OUTPUT_1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_OUTPUT_10))
                max_row_ranguvannja = MAX_ROW_RANGUVANNJA_OUTPUT;
              else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_LED_1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_LED_8))
                max_row_ranguvannja = MAX_ROW_RANGUVANNJA_LED;
              else if (current_ekran.current_level == EKRAN_RANGUVANNJA_SILENCE)
                max_row_ranguvannja = MAX_ROW_RANGUVANNJA_SILENCE;
              else if (current_ekran.current_level == EKRAN_RANGUVANNJA_RESET)
                max_row_ranguvannja = MAX_ROW_RANGUVANNJA_RESET;
              else if (current_ekran.current_level == EKRAN_RANGUVANNJA_ANALOG_REGISTRATOR)
                max_row_ranguvannja = MAX_ROW_RANGUVANNJA_ANALOG_REGISTRATOR;
              else if (current_ekran.current_level == EKRAN_RANGUVANNJA_DIGITAL_REGISTRATOR)
                max_row_ranguvannja = MAX_ROW_RANGUVANNJA_DIGITAL_REGISTRATOR;
              else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_ALARMS1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_ALARMS2))
                max_row_ranguvannja = MAX_ROW_RANGUVANNJA_ALARMS;
              else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_SET_DT1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_RESET_DT4))
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
                else if (current_ekran.current_level == EKRAN_RANGUVANNJA_SILENCE)
                {
                  for (unsigned int i = 0; i < N_BIG; i++ ) temp_state[i] = current_settings.ranguvannja_silence[i];
                }
                else if (current_ekran.current_level == EKRAN_RANGUVANNJA_RESET)
                {
                  for (unsigned int i = 0; i < N_BIG; i++ ) temp_state[i] = current_settings.ranguvannja_reset[i];
                }
                else if (current_ekran.current_level == EKRAN_RANGUVANNJA_ANALOG_REGISTRATOR)
                {
                  for (unsigned int i = 0; i < N_BIG; i++ ) temp_state[i] = current_settings.ranguvannja_analog_registrator[i];
                }
                else if (current_ekran.current_level == EKRAN_RANGUVANNJA_DIGITAL_REGISTRATOR)
                {
                  for (unsigned int i = 0; i < N_BIG; i++ ) temp_state[i] = current_settings.ranguvannja_digital_registrator[i];
                }
                else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_ALARMS1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_ALARMS2))
                {
                  for (unsigned int i = 0; i < N_BIG; i++ ) temp_state[i] = current_settings.ranguvannja_alarms[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_ALARMS1)+i];
                }
                else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_DF1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_DF8))
                {
                  for (unsigned int i = 0; i < N_BIG; i++ ) temp_state[i] = current_settings.ranguvannja_df[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_DF1)+i];
                }
                else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_SET_DT1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_RESET_DT4))
                {
                  unsigned int index_in_ekran_list = current_ekran.current_level - EKRAN_RANGUVANNJA_SET_DT1;
                  unsigned int index_of_dt = index_in_ekran_list / 2;
                  unsigned int type_of_action = index_in_ekran_list & 0x1;
    
                  if (type_of_action == INDEX_ML_SET_DT)
                  {
                      for (unsigned int i = 0; i < N_BIG; i++ ) temp_state[i] = current_settings.ranguvannja_set_dt[N_BIG*index_of_dt+i];
                  }
                  else
                  {
                      for (unsigned int i = 0; i < N_BIG; i++ ) temp_state[i] = current_settings.ranguvannja_reset_dt[N_BIG*index_of_dt+i];
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
                  // (x>>5) аналогічне операції x / 32 - ціла частина від ділення на 32
                  // (x & 0x1f) аналогічне операції x % 32 - остача від ділення на 32
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
//                  -1 /*признак завершення масиву*/
//                };
                EL_FILTER_STRUCT el_filter[NUMBER_DEFINED_ELEMENTS] =
                {
                  {1, RANG_DF1_IN , RANG_DF8_OUT, 2, current_settings.number_defined_df },
                  {1, RANG_DT1_SET, RANG_DT4_OUT, 3, current_settings.number_defined_dt },
                  {1, RANG_D_AND1 , RANG_D_AND8 , 1, current_settings.number_defined_and},
                  {1, RANG_D_OR1  , RANG_D_OR8  , 1, current_settings.number_defined_or },
                  {1, RANG_D_XOR1 , RANG_D_XOR8 , 1, current_settings.number_defined_xor},
                  {1, RANG_D_NOT1 , RANG_D_NOT16, 1, current_settings.number_defined_not}
                };
                
                //Перевіряємо, чи даний індекс функції присутній у даній конфігурації 
                while (found_new_index == 0)
                {
                  check_current_index_is_presented_in_configuration(&found_new_index,
                                                                     /*add_filter,*/
                                                                     el_filter,
                                                                     1,
                                                                     NUMBER_GENERAL_SIGNAL_FOR_RANG + NUMBER_EL_SIGNAL_FOR_RANG,
                                                                     NUMBER_CTRL_PHASE_SIGNAL_FOR_RANG
                                                                    );
                  
                  //Перевіряємо, чи ми не  на індексі функцій із списку загальних, яку треба викинути для даного типу ранжування
                  if (
                      ( current_ekran.current_level == EKRAN_RANGUVANNJA_SILENCE            ) ||   
                      ( current_ekran.current_level == EKRAN_RANGUVANNJA_RESET              ) ||   
                      ( current_ekran.current_level == EKRAN_RANGUVANNJA_ANALOG_REGISTRATOR ) ||   
                      ( current_ekran.current_level == EKRAN_RANGUVANNJA_DIGITAL_REGISTRATOR) ||
                      (
                       (current_ekran.current_level >= EKRAN_RANGUVANNJA_ALARMS1) &&
                       (current_ekran.current_level <= EKRAN_RANGUVANNJA_ALARMS2)
                      )   
                     )   
                  {
                    unsigned int index_deleted_function;

                    if (current_ekran.current_level == EKRAN_RANGUVANNJA_SILENCE)
                      index_deleted_function = RANG_SILENCE;
                    else if (current_ekran.current_level == EKRAN_RANGUVANNJA_RESET)
                      index_deleted_function = RANG_RESET;
                    else if (current_ekran.current_level == EKRAN_RANGUVANNJA_ANALOG_REGISTRATOR)
                      index_deleted_function = RANG_WORK_A_REJESTRATOR;
                    else if (current_ekran.current_level == EKRAN_RANGUVANNJA_DIGITAL_REGISTRATOR)
                      index_deleted_function = RANG_WORK_D_REJESTRATOR;
                    else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_ALARMS1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_ALARMS2))
                      index_deleted_function = RANG_ALARM1 + (current_ekran.current_level - EKRAN_RANGUVANNJA_ALARMS1);
                    
                    if(index_deleted_function == current_ekran.index_position)
                    {
                      found_new_index = 0;
                      current_ekran.index_position++;
                    }
                  }
                  else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_DF1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_DF8))
                  {
                    unsigned int index_in_ekran_list = current_ekran.current_level - EKRAN_RANGUVANNJA_DF1;

                    for (unsigned int i = 0; i < 2; i++)
                    {
                      unsigned int index_deleted_function;
                      //Першою перевіряємо функцію з меншим номером, щоб за одну операцію циклу  можна було переміститися на функцію, яку можна ранжувати
                      if (i == 0)
                      {
                        if(index_in_ekran_list == 0)
                          index_deleted_function = (RANG_DF1_OUT > RANG_DF1_IN) ? RANG_DF1_IN : RANG_DF1_OUT;
                        else if(index_in_ekran_list == 1)
                          index_deleted_function = (RANG_DF2_OUT > RANG_DF2_IN) ? RANG_DF2_IN : RANG_DF2_OUT;
                        else if(index_in_ekran_list == 2)
                          index_deleted_function = (RANG_DF3_OUT > RANG_DF3_IN) ? RANG_DF3_IN : RANG_DF3_OUT;
                        else if(index_in_ekran_list == 3)
                          index_deleted_function = (RANG_DF4_OUT > RANG_DF4_IN) ? RANG_DF4_IN : RANG_DF4_OUT;
                        else if(index_in_ekran_list == 4)
                          index_deleted_function = (RANG_DF5_OUT > RANG_DF5_IN) ? RANG_DF5_IN : RANG_DF5_OUT;
                        else if(index_in_ekran_list == 5)
                          index_deleted_function = (RANG_DF6_OUT > RANG_DF6_IN) ? RANG_DF6_IN : RANG_DF6_OUT;
                        else if(index_in_ekran_list == 6)
                          index_deleted_function = (RANG_DF7_OUT > RANG_DF7_IN) ? RANG_DF7_IN : RANG_DF7_OUT;
                        else
                          index_deleted_function = (RANG_DF8_OUT > RANG_DF8_IN) ? RANG_DF8_IN : RANG_DF8_OUT;
                      }
                      else
                      {
                        if(index_in_ekran_list == 0)
                          index_deleted_function = (RANG_DF1_OUT > RANG_DF1_IN) ? RANG_DF1_OUT : RANG_DF1_IN;
                        else if(index_in_ekran_list == 1)
                          index_deleted_function = (RANG_DF2_OUT > RANG_DF2_IN) ? RANG_DF2_OUT : RANG_DF2_IN;
                        else if(index_in_ekran_list == 2)
                          index_deleted_function = (RANG_DF3_OUT > RANG_DF3_IN) ? RANG_DF3_OUT : RANG_DF3_IN;
                        else if(index_in_ekran_list == 3)
                          index_deleted_function = (RANG_DF4_OUT > RANG_DF4_IN) ? RANG_DF4_OUT : RANG_DF4_IN;
                        else if(index_in_ekran_list == 4)
                          index_deleted_function = (RANG_DF5_OUT > RANG_DF5_IN) ? RANG_DF5_OUT : RANG_DF5_IN;
                        else if(index_in_ekran_list == 5)
                          index_deleted_function = (RANG_DF6_OUT > RANG_DF6_IN) ? RANG_DF6_OUT : RANG_DF6_IN;
                        else if(index_in_ekran_list == 6)
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
                  else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_SET_DT1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_RESET_DT4))
                  {
                    unsigned int index_in_ekran_list = current_ekran.current_level - EKRAN_RANGUVANNJA_SET_DT1;
                    unsigned int index_of_dt = index_in_ekran_list / 2;

                    for (unsigned int i = 0; i < 3; i++)
                    {
                      unsigned int index_deleted_function;
                      //Першою перевіряємо функцію з меншим номером, щоб за одну операцію циклу  можна було переміститися на функцію, яку можна ранжувати
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

                    //Першою перевіряємо функцію з меншим номером, щоб за одну операцію циклу  можна було переміститися на функцію, яку можна ранжувати
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

                    //Першою перевіряємо функцію з меншим номером, щоб за одну операцію циклу  можна було переміститися на функцію, яку можна ранжувати
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

                    //Першою перевіряємо функцію з меншим номером, щоб за одну операцію циклу  можна було переміститися на функцію, яку можна ранжувати
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

                    //Першою перевіряємо функцію з меншим номером, щоб за одну операцію циклу  можна було переміститися на функцію, яку можна ранжувати
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
//                      //Визначаємо індекс функції, яку потенційно можливо треба буде фільтрувати із сприску
//                      //Першою перевіряємо функцію з меншим номером, щоб за одну операцію циклу  можна було переміститися на функцію, яку можна ранжувати
//                      if (i == 0)
//                      {
//                        index_deleted_function = (RANG_WORK_BV > RANG_WORK_BO) ? RANG_WORK_BO : RANG_WORK_BV;
//                      }
//                      else
//                      {
//                        index_deleted_function = (RANG_WORK_BV > RANG_WORK_BO) ? RANG_WORK_BV : RANG_WORK_BO;
//                      }
//        
//                      //Формуємо маску  для цієї функції
//                      _SET_BIT(maska_func, index_deleted_function);
//        
//                      unsigned int index = 0;
//                      while ((need_filtration == 0) && (index < NUMBER_OUTPUTS))
//                      {
//                        //Пропускаємо текучий номер виходу, бо на ньому дана функція має відображатися під час редагування
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
//                      //У випадку, якщо ввстановлено є ситуація, коли треба фільтрувати функції
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

                  //Перевіряємо, чи ми не вийшли за допустиму кількість функцій
                  if(current_ekran.index_position >= max_row_ranguvannja)
                  {
                    found_new_index = 0;
                    current_ekran.index_position = 0;
                  }
                }
              }
              position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;
              //Формуємо екран відображення зранжованих функцій
              if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_OUTPUT_1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_OUTPUT_10))
                make_ekran_set_function_in_output_led_df_dt_reg(current_ekran.current_level, INDEX_VIEWING_OUTPUT);
              else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_LED_1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_LED_8))
                make_ekran_set_function_in_output_led_df_dt_reg(current_ekran.current_level, INDEX_VIEWING_LED);
              else if (current_ekran.current_level == EKRAN_RANGUVANNJA_SILENCE)
                make_ekran_set_function_in_output_led_df_dt_reg(current_ekran.current_level, INDEX_VIEWING_SILENCE);
              else if (current_ekran.current_level == EKRAN_RANGUVANNJA_RESET)
                make_ekran_set_function_in_output_led_df_dt_reg(current_ekran.current_level, INDEX_VIEWING_RESET);
              else if (current_ekran.current_level == EKRAN_RANGUVANNJA_ANALOG_REGISTRATOR)
                make_ekran_set_function_in_output_led_df_dt_reg(current_ekran.current_level, INDEX_VIEWING_A_REG);
              else if (current_ekran.current_level == EKRAN_RANGUVANNJA_DIGITAL_REGISTRATOR)
                make_ekran_set_function_in_output_led_df_dt_reg(current_ekran.current_level, INDEX_VIEWING_D_REG);
              else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_ALARMS1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_ALARMS2))
                make_ekran_set_function_in_output_led_df_dt_reg(current_ekran.current_level, INDEX_VIEWING_ALARMS);
              else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_DF1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_DF8))
                make_ekran_set_function_in_output_led_df_dt_reg(current_ekran.current_level, INDEX_VIEWING_DF);
              else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_SET_DT1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_RESET_DT4))
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
            else if (current_ekran.current_level == EKRAN_RANGUVANNJA_TEST)
            {
              if(current_ekran.index_position >= MAX_ROW_RANGUVANNJA_TEST) current_ekran.index_position = 0;
              if(current_ekran.edition == 0)
              {
                unsigned int temp_state = current_settings.ranguvannja_test;
                if (temp_state == 0) current_ekran.index_position = 0;
                else
                {
                  while ((temp_state & (1<<current_ekran.index_position)) == 0)
                  {
                    current_ekran.index_position++;
                    if(current_ekran.index_position >= MAX_ROW_RANGUVANNJA_TEST) current_ekran.index_position = 0;
                  }
                }
              }
              else
              {
                //Перевіряємо, чи ми не вийшли за допустиму кількість функцій
                if(current_ekran.index_position >= MAX_ROW_RANGUVANNJA_TEST) current_ekran.index_position = 0;
              }
              position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;
              //Формуємо екран відображення зранжованих функцій
              make_ekran_set_function_in_test();
            }
            
            //Очищаємо біт обновлення екрану
            new_state_keyboard &= (unsigned int)(~(1<<BIT_REWRITE));
          }
          else
          {
            if (new_state_keyboard == (1<<BIT_KEY_ENTER))
            {
              //Натиснута кнопка ENTER
              if(current_ekran.edition == 0)
              {
                //Копіюємо ранжування у структуру для редагування
                if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_OUTPUT_1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_OUTPUT_10))
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
                else if(current_ekran.current_level == EKRAN_RANGUVANNJA_SILENCE)
                {
                  for (unsigned int i = 0; i < N_BIG; i++)
                  {
                    edition_settings.ranguvannja_silence[i] = current_settings.ranguvannja_silence[i];
                  }
                }
                else if(current_ekran.current_level == EKRAN_RANGUVANNJA_RESET)
                {
                  for (unsigned int i = 0; i < N_BIG; i++)
                  {
                    edition_settings.ranguvannja_reset[i] = current_settings.ranguvannja_reset[i];
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
                else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_ALARMS1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_ALARMS2))
                {
                  for (unsigned int i = 0; i < N_BIG; i++)
                  {
                    edition_settings.ranguvannja_alarms[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_ALARMS1) + i] =
                      current_settings.ranguvannja_alarms[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_ALARMS1) + i];
                  }
                }
                else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_DF1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_DF8))
                {
                  for (unsigned int i = 0; i < N_BIG; i++)
                  {
                    edition_settings.ranguvannja_df[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_DF1) + i] =
                      current_settings.ranguvannja_df[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_DF1) + i];
                  }
                }
                else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_SET_DT1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_RESET_DT4))
                {
                  unsigned int index_in_ekran_list = current_ekran.current_level - EKRAN_RANGUVANNJA_SET_DT1;
                  unsigned int index_of_dt = index_in_ekran_list / 2;
                  unsigned int type_of_action = index_in_ekran_list & 0x1;
    
                  if (type_of_action == INDEX_ML_SET_DT)
                  {
                    for (unsigned int i = 0; i < N_BIG; i++)
                    {
                      edition_settings.ranguvannja_set_dt[N_BIG*index_of_dt + i] = current_settings.ranguvannja_set_dt[N_BIG*index_of_dt + i];
                    }
                  }
                  else
                  {
                    for (unsigned int i = 0; i < N_BIG; i++)
                    {
                      edition_settings.ranguvannja_reset_dt[N_BIG*index_of_dt + i] = current_settings.ranguvannja_reset_dt[N_BIG*index_of_dt + i];
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
                else if(current_ekran.current_level == EKRAN_RANGUVANNJA_TEST)
                {
                  edition_settings.ranguvannja_test = current_settings.ranguvannja_test;
                }
                  
                //Підготовка до режиму редагування - включаємо мигаючий курсор
                int temp_current_level = current_ekran.current_level;
                current_ekran.cursor_on = 1;
                current_ekran.cursor_blinking_on = 1;
                if (current_settings.password != 0)
                {
                  //Переходимо на меню запиту паролю
                  current_ekran.current_level = EKRAN_LEVEL_PASSWORD;
                  previous_level_in_current_level_menu[current_ekran.current_level] = temp_current_level;
                  current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
                }
                else
                {
                  //Переходимо у режим редагування
                  current_ekran.edition = 1;
                }
              }
              else if (current_ekran.edition == 1)
              {
                //Перевіряємо чи якісь зміни відбулися
                if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_OUTPUT_1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_OUTPUT_10))
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
                else if(current_ekran.current_level == EKRAN_RANGUVANNJA_SILENCE)
                {
                  if (
                      (edition_settings.ranguvannja_silence[0] == current_settings.ranguvannja_silence[0]) &&
                      (edition_settings.ranguvannja_silence[1] == current_settings.ranguvannja_silence[1]) &&
                      (edition_settings.ranguvannja_silence[2] == current_settings.ranguvannja_silence[2]) &&
                      (edition_settings.ranguvannja_silence[3] == current_settings.ranguvannja_silence[3]) &&
                      (edition_settings.ranguvannja_silence[4] == current_settings.ranguvannja_silence[4]) &&
                      (edition_settings.ranguvannja_silence[5] == current_settings.ranguvannja_silence[5]) &&
                      (edition_settings.ranguvannja_silence[6] == current_settings.ranguvannja_silence[6])
                     )
                    current_ekran.edition = 0;
                  else current_ekran.edition = 2;
                }
                else if(current_ekran.current_level == EKRAN_RANGUVANNJA_RESET)
                {
                  if (
                      (edition_settings.ranguvannja_reset[0] == current_settings.ranguvannja_reset[0]) &&
                      (edition_settings.ranguvannja_reset[1] == current_settings.ranguvannja_reset[1]) &&
                      (edition_settings.ranguvannja_reset[2] == current_settings.ranguvannja_reset[2]) &&
                      (edition_settings.ranguvannja_reset[3] == current_settings.ranguvannja_reset[3]) &&
                      (edition_settings.ranguvannja_reset[4] == current_settings.ranguvannja_reset[4]) &&
                      (edition_settings.ranguvannja_reset[5] == current_settings.ranguvannja_reset[5]) &&
                      (edition_settings.ranguvannja_reset[6] == current_settings.ranguvannja_reset[6])
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
                else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_ALARMS1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_ALARMS2))
                {
                  if (
                      (edition_settings.ranguvannja_alarms[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_ALARMS1)    ] == current_settings.ranguvannja_alarms[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_ALARMS1)    ]) &&
                      (edition_settings.ranguvannja_alarms[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_ALARMS1) + 1] == current_settings.ranguvannja_alarms[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_ALARMS1) + 1]) &&
                      (edition_settings.ranguvannja_alarms[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_ALARMS1) + 2] == current_settings.ranguvannja_alarms[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_ALARMS1) + 2]) &&
                      (edition_settings.ranguvannja_alarms[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_ALARMS1) + 3] == current_settings.ranguvannja_alarms[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_ALARMS1) + 3]) &&
                      (edition_settings.ranguvannja_alarms[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_ALARMS1) + 4] == current_settings.ranguvannja_alarms[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_ALARMS1) + 4]) &&
                      (edition_settings.ranguvannja_alarms[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_ALARMS1) + 5] == current_settings.ranguvannja_alarms[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_ALARMS1) + 5]) &&
                      (edition_settings.ranguvannja_alarms[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_ALARMS1) + 6] == current_settings.ranguvannja_alarms[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_ALARMS1) + 6])
                     )
                    current_ekran.edition = 0;
                  else current_ekran.edition = 2;
                }
                else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_DF1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_DF8))
                {
                  if (
                      (edition_settings.ranguvannja_df[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_DF1)    ] == current_settings.ranguvannja_df[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_DF1)    ]) &&
                      (edition_settings.ranguvannja_df[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_DF1) + 1] == current_settings.ranguvannja_df[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_DF1) + 1]) &&
                      (edition_settings.ranguvannja_df[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_DF1) + 2] == current_settings.ranguvannja_df[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_DF1) + 2]) &&
                      (edition_settings.ranguvannja_df[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_DF1) + 3] == current_settings.ranguvannja_df[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_DF1) + 3]) &&
                      (edition_settings.ranguvannja_df[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_DF1) + 4] == current_settings.ranguvannja_df[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_DF1) + 4]) &&
                      (edition_settings.ranguvannja_df[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_DF1) + 5] == current_settings.ranguvannja_df[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_DF1) + 5]) &&
                      (edition_settings.ranguvannja_df[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_DF1) + 6] == current_settings.ranguvannja_df[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_DF1) + 6])
                     )
                    current_ekran.edition = 0;
                  else current_ekran.edition = 2;
                }
                else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_SET_DT1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_RESET_DT4))
                {
                  unsigned int index_in_ekran_list = current_ekran.current_level - EKRAN_RANGUVANNJA_SET_DT1;
                  unsigned int index_of_dt = index_in_ekran_list / 2;
                  unsigned int type_of_action = index_in_ekran_list & 0x1;
    
                  if (type_of_action == INDEX_ML_SET_DT)
                  {
                    if (
                        (edition_settings.ranguvannja_set_dt[N_BIG*index_of_dt  ] == current_settings.ranguvannja_set_dt[N_BIG*index_of_dt  ]) &&
                        (edition_settings.ranguvannja_set_dt[N_BIG*index_of_dt+1] == current_settings.ranguvannja_set_dt[N_BIG*index_of_dt+1]) &&
                        (edition_settings.ranguvannja_set_dt[N_BIG*index_of_dt+2] == current_settings.ranguvannja_set_dt[N_BIG*index_of_dt+2]) &&
                        (edition_settings.ranguvannja_set_dt[N_BIG*index_of_dt+3] == current_settings.ranguvannja_set_dt[N_BIG*index_of_dt+3]) &&
                        (edition_settings.ranguvannja_set_dt[N_BIG*index_of_dt+4] == current_settings.ranguvannja_set_dt[N_BIG*index_of_dt+4]) &&
                        (edition_settings.ranguvannja_set_dt[N_BIG*index_of_dt+5] == current_settings.ranguvannja_set_dt[N_BIG*index_of_dt+5]) &&
                        (edition_settings.ranguvannja_set_dt[N_BIG*index_of_dt+6] == current_settings.ranguvannja_set_dt[N_BIG*index_of_dt+6])
                       )
                      current_ekran.edition = 0;
                    else current_ekran.edition = 2;
                  }
                  else
                  {
                    if (
                        (edition_settings.ranguvannja_reset_dt[N_BIG*index_of_dt  ] == current_settings.ranguvannja_reset_dt[N_BIG*index_of_dt  ]) &&
                        (edition_settings.ranguvannja_reset_dt[N_BIG*index_of_dt+1] == current_settings.ranguvannja_reset_dt[N_BIG*index_of_dt+1]) &&
                        (edition_settings.ranguvannja_reset_dt[N_BIG*index_of_dt+2] == current_settings.ranguvannja_reset_dt[N_BIG*index_of_dt+2]) &&
                        (edition_settings.ranguvannja_reset_dt[N_BIG*index_of_dt+3] == current_settings.ranguvannja_reset_dt[N_BIG*index_of_dt+3]) &&
                        (edition_settings.ranguvannja_reset_dt[N_BIG*index_of_dt+4] == current_settings.ranguvannja_reset_dt[N_BIG*index_of_dt+4]) &&
                        (edition_settings.ranguvannja_reset_dt[N_BIG*index_of_dt+5] == current_settings.ranguvannja_reset_dt[N_BIG*index_of_dt+5]) &&
                        (edition_settings.ranguvannja_reset_dt[N_BIG*index_of_dt+6] == current_settings.ranguvannja_reset_dt[N_BIG*index_of_dt+6])
                       )
                      current_ekran.edition = 0;
                    else current_ekran.edition = 2;
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
                else if(current_ekran.current_level == EKRAN_RANGUVANNJA_TEST)
                {
                  if (edition_settings.ranguvannja_test == current_settings.ranguvannja_test) current_ekran.edition = 0;
                  else current_ekran.edition = 2;
                }

                current_ekran.cursor_on = 0;
                current_ekran.cursor_blinking_on = 0;
              }
              else if (current_ekran.edition == 2)
              {
                //Попередньо виставляємо повідомлення, що дані не достовірні
                current_ekran.edition = 3;
                //Обновляємо значення
                if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_OUTPUT_1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_OUTPUT_10))
                {
                  unsigned int* point = edition_settings.ranguvannja_outputs;
                  if (count_number_set_bit(
                                           (point + N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_OUTPUT_1)),
                                           NUMBER_TOTAL_SIGNAL_FOR_RANG
                                          ) <= MAX_FUNCTIONS_IN_OUTPUT)
                  {
                    //Помічаємо, що поле структури зараз буде змінене
                    changed_settings = CHANGED_ETAP_EXECUTION;

                    for (unsigned int i = 0; i < N_BIG; i++)
                    {
                      current_settings.ranguvannja_outputs[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_OUTPUT_1) + i] = 
                      edition_settings.ranguvannja_outputs[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_OUTPUT_1) + i];
                    }

                    //Формуємо запис у таблиці настройок про зміну конфігурації і ініціюємо запис у EEPROM нових настройок
                    fix_change_settings(1, 1);
                    //Виходимо з режиму редагування
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
                    //Помічаємо, що поле структури зараз буде змінене
                    changed_settings = CHANGED_ETAP_EXECUTION;

                    for (unsigned int i = 0; i < N_BIG; i++)
                    {
                      current_settings.ranguvannja_leds[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_LED_1) + i] = 
                      edition_settings.ranguvannja_leds[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_LED_1) + i];
                    }

                    //Формуємо запис у таблиці настройок про зміну конфігурації і ініціюємо запис у EEPROM нових настройок
                    fix_change_settings(1, 1);
                    //Виходимо з режиму редагування
                    current_ekran.edition = 0;
                  }
                }
                else if( current_ekran.current_level == EKRAN_RANGUVANNJA_SILENCE)
                {
                  unsigned int* point = edition_settings.ranguvannja_silence;
                  if (count_number_set_bit(
                                           point,
                                           NUMBER_TOTAL_SIGNAL_FOR_RANG
                                          ) <= MAX_FUNCTIONS_IN_SILENCE)
                  {
                    //Помічаємо, що поле структури зараз буде змінене
                    changed_settings = CHANGED_ETAP_EXECUTION;

                    for (unsigned int i = 0; i < N_BIG; i++)
                    {
                      current_settings.ranguvannja_silence[i] = edition_settings.ranguvannja_silence[i];
                    }

                    //Формуємо запис у таблиці настройок про зміну конфігурації і ініціюємо запис у EEPROM нових настройок
                    fix_change_settings(1, 1);
                    //Виходимо з режиму редагування
                    current_ekran.edition = 0;
                  }
                }
                else if( current_ekran.current_level == EKRAN_RANGUVANNJA_RESET)
                {
                  unsigned int* point = edition_settings.ranguvannja_reset;
                  if (count_number_set_bit(
                                           point,
                                           NUMBER_TOTAL_SIGNAL_FOR_RANG
                                          ) <= MAX_FUNCTIONS_IN_RESET)
                  {
                    //Помічаємо, що поле структури зараз буде змінене
                    changed_settings = CHANGED_ETAP_EXECUTION;

                    for (unsigned int i = 0; i < N_BIG; i++)
                    {
                      current_settings.ranguvannja_reset[i] = edition_settings.ranguvannja_reset[i];
                    }

                    //Формуємо запис у таблиці настройок про зміну конфігурації і ініціюємо запис у EEPROM нових настройок
                    fix_change_settings(1, 1);
                    //Виходимо з режиму редагування
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
                    //Помічаємо, що поле структури зараз буде змінене
                    changed_settings = CHANGED_ETAP_EXECUTION;

                    for (unsigned int i = 0; i < N_BIG; i++)
                    {
                      current_settings.ranguvannja_analog_registrator[i] = edition_settings.ranguvannja_analog_registrator[i];
                    }

                    //Формуємо запис у таблиці настройок про зміну конфігурації і ініціюємо запис у EEPROM нових настройок
                    fix_change_settings(1, 1);
                    //Виходимо з режиму редагування
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
                    //Помічаємо, що поле структури зараз буде змінене
                    changed_settings = CHANGED_ETAP_EXECUTION;

                    for (unsigned int i = 0; i < N_BIG; i++)
                    {
                      current_settings.ranguvannja_digital_registrator[i] = edition_settings.ranguvannja_digital_registrator[i];
                    }

                    //Формуємо запис у таблиці настройок про зміну конфігурації і ініціюємо запис у EEPROM нових настройок
                    fix_change_settings(1, 1);
                    //Виходимо з режиму редагування
                    current_ekran.edition = 0;
                  }
                }
                else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_ALARMS1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_ALARMS2))
                {
                  unsigned int* point = edition_settings.ranguvannja_alarms;
                  if (count_number_set_bit(
                                           (point + N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_ALARMS1)),
                                           NUMBER_TOTAL_SIGNAL_FOR_RANG
                                          ) <= MAX_FUNCTIONS_IN_ALARMS)
                  {
                    //Помічаємо, що поле структури зараз буде змінене
                    changed_settings = CHANGED_ETAP_EXECUTION;

                    for (unsigned int i = 0; i < N_BIG; i++)
                    {
                      current_settings.ranguvannja_alarms[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_ALARMS1) + i] = 
                      edition_settings.ranguvannja_alarms[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_ALARMS1) + i];
                    }

                    //Формуємо запис у таблиці настройок про зміну конфігурації і ініціюємо запис у EEPROM нових настройок
                    fix_change_settings(1, 1);
                    //Виходимо з режиму редагування
                    current_ekran.edition = 0;
                  }
                }
                else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_DF1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_DF8))
                {
                  unsigned int* point = edition_settings.ranguvannja_df;
                  if (count_number_set_bit(
                                           (point + N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_DF1)),
                                           NUMBER_TOTAL_SIGNAL_FOR_RANG
                                          ) <= MAX_FUNCTIONS_IN_DF)
                  {
                    //Помічаємо, що поле структури зараз буде змінене
                    changed_settings = CHANGED_ETAP_EXECUTION;

                    for (unsigned int i = 0; i < N_BIG; i++)
                    {
                      current_settings.ranguvannja_df[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_DF1) + i] = 
                      edition_settings.ranguvannja_df[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_DF1) + i];
                    }

                    //Формуємо запис у таблиці настройок про зміну конфігурації і ініціюємо запис у EEPROM нових настройок
                    fix_change_settings(1, 1);
                    //Виходимо з режиму редагування
                    current_ekran.edition = 0;
                  }
                }
                else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_SET_DT1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_RESET_DT4))
                {
                  unsigned int index_in_ekran_list = current_ekran.current_level - EKRAN_RANGUVANNJA_SET_DT1;
                  unsigned int index_of_dt = index_in_ekran_list / 2;
                  unsigned int type_of_action = index_in_ekran_list & 0x1;
    
                  unsigned int* point;
                  
                  if (type_of_action == INDEX_ML_SET_DT)
                  {
                    point = edition_settings.ranguvannja_set_dt;
                  }
                  else
                  {
                    point = edition_settings.ranguvannja_reset_dt;
                  }

                  if (count_number_set_bit(
                                           (point + N_BIG*index_of_dt),
                                           NUMBER_TOTAL_SIGNAL_FOR_RANG
                                          ) <= MAX_FUNCTIONS_IN_DT)
                  {
                    //Помічаємо, що поле структури зараз буде змінене
                    changed_settings = CHANGED_ETAP_EXECUTION;

                    if (type_of_action == INDEX_ML_SET_DT)
                    {
                      for (unsigned int i = 0; i < N_BIG; i++)
                      {
                        current_settings.ranguvannja_set_dt[N_BIG*index_of_dt + i] = edition_settings.ranguvannja_set_dt[N_BIG*index_of_dt + i];
                      }
                    }
                    else
                    {
                      for (unsigned int i = 0; i < N_BIG; i++)
                      {
                        current_settings.ranguvannja_reset_dt[N_BIG*index_of_dt + i] = edition_settings.ranguvannja_reset_dt[N_BIG*index_of_dt + i];
                      }
                    }

                    //Формуємо запис у таблиці настройок про зміну конфігурації і ініціюємо запис у EEPROM нових настройок
                    fix_change_settings(1, 1);
                    //Виходимо з режиму редагування
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
                    //Помічаємо, що поле структури зараз буде змінене
                    changed_settings = CHANGED_ETAP_EXECUTION;

                    for (unsigned int i = 0; i < N_BIG; i++)
                    {
                      current_settings.ranguvannja_d_and[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_AND1) + i] = 
                      edition_settings.ranguvannja_d_and[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_AND1) + i];
                    }

                    //Формуємо запис у таблиці настройок про зміну конфігурації і ініціюємо запис у EEPROM нових настройок
                    fix_change_settings(1, 1);
                    //Виходимо з режиму редагування
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
                    //Помічаємо, що поле структури зараз буде змінене
                    changed_settings = CHANGED_ETAP_EXECUTION;

                    for (unsigned int i = 0; i < N_BIG; i++)
                    {
                      current_settings.ranguvannja_d_or[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_OR1) + i] = 
                      edition_settings.ranguvannja_d_or[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_OR1) + i];
                    }

                    //Формуємо запис у таблиці настройок про зміну конфігурації і ініціюємо запис у EEPROM нових настройок
                    fix_change_settings(1, 1);
                    //Виходимо з режиму редагування
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
                    //Помічаємо, що поле структури зараз буде змінене
                    changed_settings = CHANGED_ETAP_EXECUTION;

                    for (unsigned int i = 0; i < N_BIG; i++)
                    {
                      current_settings.ranguvannja_d_xor[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_XOR1) + i] = 
                      edition_settings.ranguvannja_d_xor[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_XOR1) + i];
                    }

                    //Формуємо запис у таблиці настройок про зміну конфігурації і ініціюємо запис у EEPROM нових настройок
                    fix_change_settings(1, 1);
                    //Виходимо з режиму редагування
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
                    //Помічаємо, що поле структури зараз буде змінене
                    changed_settings = CHANGED_ETAP_EXECUTION;

                    for (unsigned int i = 0; i < N_BIG; i++)
                    {
                      current_settings.ranguvannja_d_not[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_NOT1) + i] = 
                      edition_settings.ranguvannja_d_not[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_NOT1) + i];
                    }

                    //Формуємо запис у таблиці настройок про зміну конфігурації і ініціюємо запис у EEPROM нових настройок
                    fix_change_settings(1, 1);
                    //Виходимо з режиму редагування
                    current_ekran.edition = 0;
                  }
                }
                else if(current_ekran.current_level == EKRAN_RANGUVANNJA_TEST)
                {
                  if (count_number_set_bit(
                                           &edition_settings.ranguvannja_test,
                                           NUMBER_INPUTS
                                          ) <= MAX_FUNCTIONS_IN_TEST)
                  {
                    //Помічаємо, що поле структури зараз буде змінене
                    changed_settings = CHANGED_ETAP_EXECUTION;

                    current_settings.ranguvannja_test = edition_settings.ranguvannja_test;
                    //Формуємо запис у таблиці настройок про зміну конфігурації і ініціюємо запис у EEPROM нових настройок
                    fix_change_settings(1, 1);
                    //Виходимо з режиму редагування
                    current_ekran.edition = 0;
                  }
                }
              }
              else if (current_ekran.edition == 3)
              {
                //Вихід у режимі редагування
                current_ekran.edition = 0;
              }
              
              if(current_ekran.edition == 2) make_ekran_ask_rewrite();
              else if(current_ekran.edition == 3)
              {
                const unsigned char information_about_error[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
                {
                  "Прев.макс.кол.ф.",
                  "Переб.макс.кіл.ф",
                  " Max.n.of F.Exc.",
                  "Прев.макс.кол.ф."
                };
                make_ekran_about_info(true, information_about_error);
              }
              else
                //Виставляємо біт обновлення екрану
                new_state_keyboard |= (1<<BIT_REWRITE);

              //Очистити сигналізацію, що натиснута кнопка 
              new_state_keyboard &= (unsigned int)(~(1<<BIT_KEY_ENTER));
            }
            else if (new_state_keyboard == (1<<BIT_KEY_ESC))
            {
              if(current_ekran.edition == 0)
              {
                //Вихід у режимі спостерігання
                //Переходимо у попереднє меню
                current_ekran.current_level = previous_level_in_current_level_menu[current_ekran.current_level];
                current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
              }
              //Інекше переходдимо у режим спостерігання
              current_ekran.edition = 0;

              //Виставляємо команду на обновлекння нового екрану
              new_state_keyboard |= (1<<BIT_REWRITE);
              //Очистити сигналізацію, що натиснута кнопка 
              new_state_keyboard &= (unsigned int)(~(1<<BIT_KEY_ESC));
            }
            else if (new_state_keyboard == (1<<BIT_KEY_UP))
            {
              //Натиснута кнопка UP
              if (
                  ((current_ekran.current_level >= EKRAN_RANGUVANNJA_OUTPUT_1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_OUTPUT_10)) ||
                  ((current_ekran.current_level >= EKRAN_RANGUVANNJA_LED_1   ) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_LED_8    )) ||
                  ( current_ekran.current_level == EKRAN_RANGUVANNJA_SILENCE                                                                  ) ||
                  ( current_ekran.current_level == EKRAN_RANGUVANNJA_RESET                                                                    ) ||
                  ( current_ekran.current_level == EKRAN_RANGUVANNJA_ANALOG_REGISTRATOR                                                       ) ||
                  ( current_ekran.current_level == EKRAN_RANGUVANNJA_DIGITAL_REGISTRATOR                                                      ) ||
                  ((current_ekran.current_level >= EKRAN_RANGUVANNJA_ALARMS1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_ALARMS2   )) ||
                  ((current_ekran.current_level >= EKRAN_RANGUVANNJA_DF1    ) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_DF8       )) ||
                  ((current_ekran.current_level >= EKRAN_RANGUVANNJA_SET_DT1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_RESET_DT4 )) ||
                  ((current_ekran.current_level >= EKRAN_RANGUVANNJA_D_AND1 ) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_AND8    )) ||
                  ((current_ekran.current_level >= EKRAN_RANGUVANNJA_D_OR1  ) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_OR8     )) ||
                  ((current_ekran.current_level >= EKRAN_RANGUVANNJA_D_XOR1 ) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_XOR8    )) ||
                  ((current_ekran.current_level >= EKRAN_RANGUVANNJA_D_NOT1 ) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_NOT16   ))
                 )
              {
                int max_row_ranguvannja;
                
                if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_OUTPUT_1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_OUTPUT_10))
                  max_row_ranguvannja = MAX_ROW_RANGUVANNJA_OUTPUT;
                else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_LED_1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_LED_8))
                  max_row_ranguvannja = MAX_ROW_RANGUVANNJA_LED;
                else if (current_ekran.current_level == EKRAN_RANGUVANNJA_SILENCE)
                  max_row_ranguvannja = MAX_ROW_RANGUVANNJA_SILENCE;
                else if (current_ekran.current_level == EKRAN_RANGUVANNJA_RESET)
                  max_row_ranguvannja = MAX_ROW_RANGUVANNJA_RESET;
                else if (current_ekran.current_level == EKRAN_RANGUVANNJA_ANALOG_REGISTRATOR)
                  max_row_ranguvannja = MAX_ROW_RANGUVANNJA_ANALOG_REGISTRATOR;
                else if (current_ekran.current_level == EKRAN_RANGUVANNJA_DIGITAL_REGISTRATOR)
                  max_row_ranguvannja = MAX_ROW_RANGUVANNJA_DIGITAL_REGISTRATOR;
                else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_ALARMS1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_ALARMS2))
                  max_row_ranguvannja = MAX_ROW_RANGUVANNJA_ALARMS;
                else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_SET_DT1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_RESET_DT4))
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
                  else if (current_ekran.current_level == EKRAN_RANGUVANNJA_SILENCE)
                  {
                    for (unsigned int i = 0; i < N_BIG; i++)
                    {
                      temp_state[i] = current_settings.ranguvannja_silence[i];
                    }
                  }
                  else if (current_ekran.current_level == EKRAN_RANGUVANNJA_RESET)
                  {
                    for (unsigned int i = 0; i < N_BIG; i++)
                    {
                      temp_state[i] = current_settings.ranguvannja_reset[i];
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
                  else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_ALARMS1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_ALARMS2))
                  {
                    for (unsigned int i = 0; i < N_BIG; i++)
                    {
                      temp_state[i] = current_settings.ranguvannja_alarms[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_ALARMS1) + i];
                    }
                  }
                  else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_DF1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_DF8))
                  {
                    for (unsigned int i = 0; i < N_BIG; i++)
                    {
                      temp_state[i] = current_settings.ranguvannja_df[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_DF1) + i];
                    }
                  }
                  else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_SET_DT1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_RESET_DT4))
                  {
                    unsigned int index_in_ekran_list = current_ekran.current_level - EKRAN_RANGUVANNJA_SET_DT1;
                    unsigned int index_of_dt = index_in_ekran_list / 2;
                    unsigned int type_of_action = index_in_ekran_list & 0x1;
    
                    if (type_of_action == INDEX_ML_SET_DT)
                    {
                      for (unsigned int i = 0; i < N_BIG; i++)
                      {
                        temp_state[i] = current_settings.ranguvannja_set_dt[N_BIG*index_of_dt + i];
                      }
                    }
                    else
                    {
                      for (unsigned int i = 0; i < N_BIG; i++)
                      {
                        temp_state[i] = current_settings.ranguvannja_reset_dt[N_BIG*index_of_dt + i];
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
                    // (x>>5) аналогічне операції x / 32 - ціла частина від ділення на 32
                    // (x & 0x1f) аналогічне операції x % 32 - остача від ділення на 32
                    while ((temp_state[current_ekran.index_position >> 5] & (1<<(current_ekran.index_position  & 0x1f))) == 0)
                    {
                      current_ekran.index_position--;
                      if(current_ekran.index_position < 0) current_ekran.index_position = max_row_ranguvannja - 1;
                    }
                  }
                }
                else
                {
                  //Редагування
                  unsigned int found_new_index = 0;
//                  int add_filter[3 + 1] = 
//                  {
//                    RANG_PO_NZZ,
//                    RANG_NZZ,
//                    RANG_SECTOR_NZZ,
//                    -1 /*признак завершення масиву*/
//                  };
                  EL_FILTER_STRUCT el_filter[NUMBER_DEFINED_ELEMENTS] =
                  {
                    {1, RANG_DF1_IN , RANG_DF8_OUT, 2, current_settings.number_defined_df },
                    {1, RANG_DT1_SET, RANG_DT4_OUT, 3, current_settings.number_defined_dt },
                    {1, RANG_D_AND1 , RANG_D_AND8 , 1, current_settings.number_defined_and},
                    {1, RANG_D_OR1  , RANG_D_OR8  , 1, current_settings.number_defined_or },
                    {1, RANG_D_XOR1 , RANG_D_XOR8 , 1, current_settings.number_defined_xor},
                    {1, RANG_D_NOT1 , RANG_D_NOT16, 1, current_settings.number_defined_not}
                  };
                  
                  //Переміщаємося на наступну функцію
                  if(--current_ekran.index_position < 0) current_ekran.index_position = max_row_ranguvannja - 1;
                  //Перевіряємо, чи даний індекс функції присутній у даній конфігурації 
                  while (found_new_index == 0)
                  {
                    check_current_index_is_presented_in_configuration(&found_new_index,
                                                                       /*add_filter,*/
                                                                       el_filter,
                                                                       0,
                                                                       NUMBER_GENERAL_SIGNAL_FOR_RANG + NUMBER_EL_SIGNAL_FOR_RANG,
                                                                       NUMBER_CTRL_PHASE_SIGNAL_FOR_RANG
                                                                      );
                    //Перевіряємо, чи ми не  на індексі функцій із списку загальних, яку треба викинути для даного типу ранжування
                    if (
                        ( current_ekran.current_level == EKRAN_RANGUVANNJA_SILENCE            ) || 
                        ( current_ekran.current_level == EKRAN_RANGUVANNJA_RESET              ) || 
                        ( current_ekran.current_level == EKRAN_RANGUVANNJA_DIGITAL_REGISTRATOR) ||
                        ( current_ekran.current_level == EKRAN_RANGUVANNJA_ANALOG_REGISTRATOR ) || 
                        ( current_ekran.current_level == EKRAN_RANGUVANNJA_DIGITAL_REGISTRATOR) ||
                        (
                         (current_ekran.current_level >= EKRAN_RANGUVANNJA_ALARMS1) &&
                         (current_ekran.current_level <= EKRAN_RANGUVANNJA_ALARMS2)
                        ) 
                       )   
                    {
                      unsigned int index_deleted_function;
                      
                      if (current_ekran.current_level == EKRAN_RANGUVANNJA_SILENCE)
                        index_deleted_function = RANG_SILENCE;
                      else if (current_ekran.current_level == EKRAN_RANGUVANNJA_RESET)
                        index_deleted_function = RANG_RESET;
                      else if (current_ekran.current_level == EKRAN_RANGUVANNJA_ANALOG_REGISTRATOR)
                        index_deleted_function = RANG_WORK_A_REJESTRATOR;
                      else if (current_ekran.current_level == EKRAN_RANGUVANNJA_DIGITAL_REGISTRATOR)
                        index_deleted_function = RANG_WORK_D_REJESTRATOR;
                      else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_ALARMS1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_ALARMS2))
                        index_deleted_function = RANG_ALARM1 + (current_ekran.current_level - EKRAN_RANGUVANNJA_ALARMS1);
                    
                      if(index_deleted_function == current_ekran.index_position)
                      {
                        found_new_index = 0;
                        current_ekran.index_position--;
                      }
                    }
                    else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_DF1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_DF8))
                    {
                      unsigned int index_in_ekran_list = current_ekran.current_level - EKRAN_RANGUVANNJA_DF1;

                      for (unsigned int i = 0; i < 2; i++)
                      {
                        unsigned int index_deleted_function;
                        //Першою перевіряємо функцію з більшим номером, щоб за одну операцію циклу можна було переміститися на функцію, яку можна ранжувати
                        if (i == 0)
                        {
                          if(index_in_ekran_list == 0)
                            index_deleted_function = (RANG_DF1_OUT > RANG_DF1_IN) ? RANG_DF1_OUT : RANG_DF1_IN;
                          else if(index_in_ekran_list == 1)
                            index_deleted_function = (RANG_DF2_OUT > RANG_DF2_IN) ? RANG_DF2_OUT : RANG_DF2_IN;
                          else if(index_in_ekran_list == 2)
                            index_deleted_function = (RANG_DF3_OUT > RANG_DF3_IN) ? RANG_DF3_OUT : RANG_DF3_IN;
                          else if(index_in_ekran_list == 3)
                            index_deleted_function = (RANG_DF4_OUT > RANG_DF4_IN) ? RANG_DF4_OUT : RANG_DF4_IN;
                          else if(index_in_ekran_list == 4)
                            index_deleted_function = (RANG_DF5_OUT > RANG_DF5_IN) ? RANG_DF5_OUT : RANG_DF5_IN;
                          else if(index_in_ekran_list == 5)
                            index_deleted_function = (RANG_DF6_OUT > RANG_DF6_IN) ? RANG_DF6_OUT : RANG_DF6_IN;
                          else if(index_in_ekran_list == 6)
                            index_deleted_function = (RANG_DF7_OUT > RANG_DF7_IN) ? RANG_DF7_OUT : RANG_DF7_IN;
                          else
                            index_deleted_function = (RANG_DF8_OUT > RANG_DF8_IN) ? RANG_DF8_OUT : RANG_DF8_IN;
                        }
                        else
                        {
                          if(index_in_ekran_list == 0)
                            index_deleted_function = (RANG_DF1_OUT > RANG_DF1_IN) ? RANG_DF1_IN : RANG_DF1_OUT;
                          else if(index_in_ekran_list == 1)
                            index_deleted_function = (RANG_DF2_OUT > RANG_DF2_IN) ? RANG_DF2_IN : RANG_DF2_OUT;
                          else if(index_in_ekran_list == 2)
                            index_deleted_function = (RANG_DF3_OUT > RANG_DF3_IN) ? RANG_DF3_IN : RANG_DF3_OUT;
                          else if(index_in_ekran_list == 3)
                            index_deleted_function = (RANG_DF4_OUT > RANG_DF4_IN) ? RANG_DF4_IN : RANG_DF4_OUT;
                          else if(index_in_ekran_list == 4)
                            index_deleted_function = (RANG_DF5_OUT > RANG_DF5_IN) ? RANG_DF5_IN : RANG_DF5_OUT;
                          else if(index_in_ekran_list == 5)
                            index_deleted_function = (RANG_DF6_OUT > RANG_DF6_IN) ? RANG_DF6_IN : RANG_DF6_OUT;
                          else if(index_in_ekran_list == 6)
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
                    else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_SET_DT1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_RESET_DT4))
                    {
                      unsigned int index_in_ekran_list = current_ekran.current_level - EKRAN_RANGUVANNJA_SET_DT1;
                      unsigned int index_of_dt = index_in_ekran_list / 2;

                      for (unsigned int i = 0; i < 3; i++)
                      {
                        unsigned int index_deleted_function;
                        //Першою перевіряємо функцію з більшим номером, щоб за одну операцію циклу  можна було переміститися на функцію, яку можна ранжувати
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

                      //Першою перевіряємо функцію з меншим номером, щоб за одну операцію циклу  можна було переміститися на функцію, яку можна ранжувати
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

                      //Першою перевіряємо функцію з меншим номером, щоб за одну операцію циклу  можна було переміститися на функцію, яку можна ранжувати
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

                      //Першою перевіряємо функцію з меншим номером, щоб за одну операцію циклу  можна було переміститися на функцію, яку можна ранжувати
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

                      //Першою перевіряємо функцію з меншим номером, щоб за одну операцію циклу  можна було переміститися на функцію, яку можна ранжувати
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
//                        //Визначаємо індекс функції, яку потенційно можливо треба буде фільтрувати із сприску
//                        //Першою перевіряємо функцію з більшим номером, щоб за одну операцію циклу можна було переміститися на функцію, яку можна ранжувати
//                        if (i == 0)
//                        {
//                          index_deleted_function = (RANG_WORK_BV > RANG_WORK_BO) ? RANG_WORK_BV : RANG_WORK_BO;
//                        }
//                        else
//                        {
//                          index_deleted_function = (RANG_WORK_BV > RANG_WORK_BO) ? RANG_WORK_BO : RANG_WORK_BV;
//                        }
//        
//                        //Формуємо маску  для цієї функції
//                        _SET_BIT(maska_func, index_deleted_function);
//        
//                        unsigned int index = 0;
//                        while ((need_filtration == 0) && (index < NUMBER_OUTPUTS))
//                        {
//                          //Пропускаємо текучий номер виходу, бо на ньому дана функція має відображатися під час редагування
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
//                        //У випадку, якщо ввстановлено є ситуація, коли треба фільтрувати функції
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
                    
                    //Перевіряємо, чи ми не вийшли за допустиму кількість функцій
                    if(current_ekran.index_position < 0)
                    {
                      found_new_index = 0;
                      current_ekran.index_position = max_row_ranguvannja - 1;
                    }
                  }
                }
                position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;
                
                //Формуємо екран відображення зранжованих функцій
                if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_OUTPUT_1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_OUTPUT_10))
                  make_ekran_set_function_in_output_led_df_dt_reg(current_ekran.current_level, INDEX_VIEWING_OUTPUT);
                else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_LED_1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_LED_8))
                  make_ekran_set_function_in_output_led_df_dt_reg(current_ekran.current_level, INDEX_VIEWING_LED);
                else if (current_ekran.current_level == EKRAN_RANGUVANNJA_SILENCE)
                  make_ekran_set_function_in_output_led_df_dt_reg(current_ekran.current_level, INDEX_VIEWING_SILENCE);
                else if (current_ekran.current_level == EKRAN_RANGUVANNJA_RESET)
                  make_ekran_set_function_in_output_led_df_dt_reg(current_ekran.current_level, INDEX_VIEWING_RESET);
                else if (current_ekran.current_level == EKRAN_RANGUVANNJA_ANALOG_REGISTRATOR)
                  make_ekran_set_function_in_output_led_df_dt_reg(current_ekran.current_level, INDEX_VIEWING_A_REG);
                else if (current_ekran.current_level == EKRAN_RANGUVANNJA_DIGITAL_REGISTRATOR)
                  make_ekran_set_function_in_output_led_df_dt_reg(current_ekran.current_level, INDEX_VIEWING_D_REG);
                else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_ALARMS1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_ALARMS2))
                  make_ekran_set_function_in_output_led_df_dt_reg(current_ekran.current_level, INDEX_VIEWING_ALARMS);
                else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_DF1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_DF8))
                  make_ekran_set_function_in_output_led_df_dt_reg(current_ekran.current_level, INDEX_VIEWING_DF);
                else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_SET_DT1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_RESET_DT4))
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
              else if(current_ekran.current_level == EKRAN_RANGUVANNJA_TEST)
              {
                if(current_ekran.edition == 0)
                {
                  unsigned int temp_state = current_settings.ranguvannja_test;
                  if (temp_state == 0) current_ekran.index_position = 0;
                  else
                  {
                    if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_RANGUVANNJA_TEST - 1;
                    while ((temp_state & (1<<current_ekran.index_position)) == 0)
                    {
                      current_ekran.index_position--;
                      if(current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_RANGUVANNJA_TEST - 1;
                    }
                  }
                }
                else
                {
                  //Редагування
                  //Переміщаємося на наступну функцію
                  if(--current_ekran.index_position < 0) current_ekran.index_position = MAX_ROW_RANGUVANNJA_TEST - 1;
                }
                position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;
                
                //Формуємо екран відображення зранжованих функцій
                make_ekran_set_function_in_test();
              }
              
              //Очистити сигналізацію, що натиснута кнопка 
              new_state_keyboard &= (unsigned int)(~(1<<BIT_KEY_UP));
            }
            else if (new_state_keyboard == (1<<BIT_KEY_DOWN))
            {
              //Натиснута кнопка DOWN
              if (
                  ((current_ekran.current_level >= EKRAN_RANGUVANNJA_OUTPUT_1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_OUTPUT_10)) ||
                  ((current_ekran.current_level >= EKRAN_RANGUVANNJA_LED_1   ) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_LED_8    )) ||
                  ( current_ekran.current_level == EKRAN_RANGUVANNJA_SILENCE                                                                  ) ||
                  ( current_ekran.current_level == EKRAN_RANGUVANNJA_RESET                                                                    ) ||
                  ( current_ekran.current_level == EKRAN_RANGUVANNJA_ANALOG_REGISTRATOR                                                       ) ||
                  ( current_ekran.current_level == EKRAN_RANGUVANNJA_DIGITAL_REGISTRATOR                                                      ) ||
                  ((current_ekran.current_level >= EKRAN_RANGUVANNJA_ALARMS1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_ALARMS2   )) ||
                  ((current_ekran.current_level >= EKRAN_RANGUVANNJA_DF1    ) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_DF8       )) ||
                  ((current_ekran.current_level >= EKRAN_RANGUVANNJA_SET_DT1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_RESET_DT4 )) ||
                  ((current_ekran.current_level >= EKRAN_RANGUVANNJA_D_AND1 ) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_AND8    )) ||
                  ((current_ekran.current_level >= EKRAN_RANGUVANNJA_D_OR1  ) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_OR8     )) ||
                  ((current_ekran.current_level >= EKRAN_RANGUVANNJA_D_XOR1 ) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_XOR8    )) ||
                  ((current_ekran.current_level >= EKRAN_RANGUVANNJA_D_NOT1 ) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_NOT16   ))
                 )
              {
                int max_row_ranguvannja;
                
                if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_OUTPUT_1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_OUTPUT_10))
                  max_row_ranguvannja = MAX_ROW_RANGUVANNJA_OUTPUT;
                else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_LED_1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_LED_8))
                  max_row_ranguvannja = MAX_ROW_RANGUVANNJA_LED;
                else if (current_ekran.current_level == EKRAN_RANGUVANNJA_SILENCE)
                  max_row_ranguvannja = MAX_ROW_RANGUVANNJA_SILENCE;
                else if (current_ekran.current_level == EKRAN_RANGUVANNJA_RESET)
                  max_row_ranguvannja = MAX_ROW_RANGUVANNJA_RESET;
                else if (current_ekran.current_level == EKRAN_RANGUVANNJA_ANALOG_REGISTRATOR)
                  max_row_ranguvannja = MAX_ROW_RANGUVANNJA_ANALOG_REGISTRATOR;
                else if (current_ekran.current_level == EKRAN_RANGUVANNJA_DIGITAL_REGISTRATOR)
                  max_row_ranguvannja = MAX_ROW_RANGUVANNJA_DIGITAL_REGISTRATOR;
                else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_ALARMS1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_ALARMS2))
                  max_row_ranguvannja = MAX_ROW_RANGUVANNJA_ALARMS;
                else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_SET_DT1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_RESET_DT4))
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
                  else if (current_ekran.current_level == EKRAN_RANGUVANNJA_SILENCE)
                  {
                    for (unsigned int i = 0; i < N_BIG; i++)
                    {
                      temp_state[i] = current_settings.ranguvannja_silence[i];
                    }
                  }
                  else if (current_ekran.current_level == EKRAN_RANGUVANNJA_RESET)
                  {
                    for (unsigned int i = 0; i < N_BIG; i++)
                    {
                      temp_state[i] = current_settings.ranguvannja_reset[i];
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
                  else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_ALARMS1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_ALARMS2))
                  {
                    for (unsigned int i = 0; i < N_BIG; i++)
                    {
                      temp_state[i] = current_settings.ranguvannja_alarms[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_ALARMS1) + i];
                    }
                  }
                  else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_DF1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_DF8))
                  {
                    for (unsigned int i = 0; i < N_BIG; i++)
                    {
                      temp_state[i] = current_settings.ranguvannja_df[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_DF1) + i];
                    }
                  }
                  else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_SET_DT1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_RESET_DT4))
                  {
                    unsigned int index_in_ekran_list = current_ekran.current_level - EKRAN_RANGUVANNJA_SET_DT1;
                    unsigned int index_of_dt = index_in_ekran_list / 2;
                    unsigned int type_of_action = index_in_ekran_list & 0x1;
    
                    if (type_of_action == INDEX_ML_SET_DT)
                    {
                      for (unsigned int i = 0; i < N_BIG; i++)
                      {
                        temp_state[i] = current_settings.ranguvannja_set_dt[N_BIG*index_of_dt + i];
                      }
                    }
                    else
                    {
                      for (unsigned int i = 0; i < N_BIG; i++)
                      {
                        temp_state[i] = current_settings.ranguvannja_reset_dt[N_BIG*index_of_dt + i];
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
                    // (x>>5) аналогічне операції x / 32 - ціла частина від ділення на 32
                    // (x & 0x1f) аналогічне операції x % 32 - остача від ділення на 32
                    while ((temp_state[current_ekran.index_position >> 5] & (1<<(current_ekran.index_position  & 0x1f))) ==0)
                    {
                      current_ekran.index_position++;
                      if(current_ekran.index_position >= max_row_ranguvannja) current_ekran.index_position = 0;
                    }
                  }
                }
                else
                {
                  //Редагування
                  unsigned int found_new_index = 0;
//                  int add_filter[3 + 1] = 
//                  {
//                    RANG_PO_NZZ,
//                    RANG_NZZ,
//                    RANG_SECTOR_NZZ,
//                    -1 /*признак завершення масиву*/
//                  };
                  EL_FILTER_STRUCT el_filter[NUMBER_DEFINED_ELEMENTS] =
                  {
                    {1, RANG_DF1_IN , RANG_DF8_OUT, 2, current_settings.number_defined_df },
                    {1, RANG_DT1_SET, RANG_DT4_OUT, 3, current_settings.number_defined_dt },
                    {1, RANG_D_AND1 , RANG_D_AND8 , 1, current_settings.number_defined_and},
                    {1, RANG_D_OR1  , RANG_D_OR8  , 1, current_settings.number_defined_or },
                    {1, RANG_D_XOR1 , RANG_D_XOR8 , 1, current_settings.number_defined_xor},
                    {1, RANG_D_NOT1 , RANG_D_NOT16, 1, current_settings.number_defined_not}
                  };
                  
                  //Переміщаємося на наступну функцію
                  if(++current_ekran.index_position >= max_row_ranguvannja) current_ekran.index_position = 0;
                  //Перевіряємо, чи даний індекс функції присутній у даній конфігурації 
                  while (found_new_index == 0)
                  {
                    check_current_index_is_presented_in_configuration(&found_new_index,
                                                                       /*add_filter,*/
                                                                       el_filter,
                                                                       1,
                                                                       NUMBER_GENERAL_SIGNAL_FOR_RANG + NUMBER_EL_SIGNAL_FOR_RANG,
                                                                       NUMBER_CTRL_PHASE_SIGNAL_FOR_RANG
                                                                      );

                    //Перевіряємо, чи ми не  на індексі функцій із списку загальних, яку треба викинути для даного типу ранжування
                    if (
                        ( current_ekran.current_level == EKRAN_RANGUVANNJA_SILENCE            ) || 
                        ( current_ekran.current_level == EKRAN_RANGUVANNJA_RESET              ) ||
                        ( current_ekran.current_level == EKRAN_RANGUVANNJA_ANALOG_REGISTRATOR ) || 
                        ( current_ekran.current_level == EKRAN_RANGUVANNJA_DIGITAL_REGISTRATOR) ||
                        (
                         (current_ekran.current_level >= EKRAN_RANGUVANNJA_ALARMS1) && 
                         (current_ekran.current_level <= EKRAN_RANGUVANNJA_ALARMS2)
                        ) 
                       )   
                    {
                      unsigned int index_deleted_function;
                      
                      if (current_ekran.current_level == EKRAN_RANGUVANNJA_SILENCE)
                        index_deleted_function = RANG_SILENCE;
                      else if (current_ekran.current_level == EKRAN_RANGUVANNJA_RESET)
                        index_deleted_function = RANG_RESET;
                      else if (current_ekran.current_level == EKRAN_RANGUVANNJA_ANALOG_REGISTRATOR)
                        index_deleted_function = RANG_WORK_A_REJESTRATOR;
                      else if (current_ekran.current_level == EKRAN_RANGUVANNJA_DIGITAL_REGISTRATOR)
                        index_deleted_function = RANG_WORK_D_REJESTRATOR;
                      else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_ALARMS1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_ALARMS2))
                        index_deleted_function = RANG_ALARM1 + (current_ekran.current_level - EKRAN_RANGUVANNJA_ALARMS1);
                    
                      if(index_deleted_function == current_ekran.index_position)
                      {
                        found_new_index = 0;
                        current_ekran.index_position++;
                      }
                    }
                    else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_DF1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_DF8))
                    {
                      unsigned int index_in_ekran_list = current_ekran.current_level - EKRAN_RANGUVANNJA_DF1;

                      for (unsigned int i = 0; i < 2; i++)
                      {
                        unsigned int index_deleted_function;
                        //Першою перевіряємо функцію з меншим номером, щоб за одну операцію циклу можна було переміститися на функцію, яку можна ранжувати
                        if (i == 0)
                        {
                          if(index_in_ekran_list == 0)
                            index_deleted_function = (RANG_DF1_OUT > RANG_DF1_IN) ? RANG_DF1_IN : RANG_DF1_OUT;
                          else if(index_in_ekran_list == 1)
                            index_deleted_function = (RANG_DF2_OUT > RANG_DF2_IN) ? RANG_DF2_IN : RANG_DF2_OUT;
                          else if(index_in_ekran_list == 2)
                            index_deleted_function = (RANG_DF3_OUT > RANG_DF3_IN) ? RANG_DF3_IN : RANG_DF3_OUT;
                          else if(index_in_ekran_list == 3)
                            index_deleted_function = (RANG_DF4_OUT > RANG_DF4_IN) ? RANG_DF4_IN : RANG_DF4_OUT;
                          else if(index_in_ekran_list == 4)
                            index_deleted_function = (RANG_DF5_OUT > RANG_DF5_IN) ? RANG_DF5_IN : RANG_DF5_OUT;
                          else if(index_in_ekran_list == 5)
                            index_deleted_function = (RANG_DF6_OUT > RANG_DF6_IN) ? RANG_DF6_IN : RANG_DF6_OUT;
                          else if(index_in_ekran_list == 6)
                            index_deleted_function = (RANG_DF7_OUT > RANG_DF7_IN) ? RANG_DF7_IN : RANG_DF7_OUT;
                          else
                            index_deleted_function = (RANG_DF8_OUT > RANG_DF8_IN) ? RANG_DF8_IN : RANG_DF8_OUT;
                        }
                        else
                        {
                          if(index_in_ekran_list == 0)
                            index_deleted_function = (RANG_DF1_OUT > RANG_DF1_IN) ? RANG_DF1_OUT : RANG_DF1_IN;
                          else if(index_in_ekran_list == 1)
                            index_deleted_function = (RANG_DF2_OUT > RANG_DF2_IN) ? RANG_DF2_OUT : RANG_DF2_IN;
                          else if(index_in_ekran_list == 2)
                            index_deleted_function = (RANG_DF3_OUT > RANG_DF3_IN) ? RANG_DF3_OUT : RANG_DF3_IN;
                          else if(index_in_ekran_list == 3)
                            index_deleted_function = (RANG_DF4_OUT > RANG_DF4_IN) ? RANG_DF4_OUT : RANG_DF4_IN;
                          else if(index_in_ekran_list == 4)
                            index_deleted_function = (RANG_DF5_OUT > RANG_DF5_IN) ? RANG_DF5_OUT : RANG_DF5_IN;
                          else if(index_in_ekran_list == 5)
                            index_deleted_function = (RANG_DF6_OUT > RANG_DF6_IN) ? RANG_DF6_OUT : RANG_DF6_IN;
                          else if(index_in_ekran_list == 6)
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
                    else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_SET_DT1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_RESET_DT4))
                    {
                      unsigned int index_in_ekran_list = current_ekran.current_level - EKRAN_RANGUVANNJA_SET_DT1;
                      unsigned int index_of_dt = index_in_ekran_list / 2;

                      for (unsigned int i = 0; i < 3; i++)
                      {
                        unsigned int index_deleted_function;
                        //Першою перевіряємо функцію з меншим номером, щоб за одну операцію циклу  можна було переміститися на функцію, яку можна ранжувати
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

                      //Першою перевіряємо функцію з меншим номером, щоб за одну операцію циклу  можна було переміститися на функцію, яку можна ранжувати
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

                      //Першою перевіряємо функцію з меншим номером, щоб за одну операцію циклу  можна було переміститися на функцію, яку можна ранжувати
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

                      //Першою перевіряємо функцію з меншим номером, щоб за одну операцію циклу  можна було переміститися на функцію, яку можна ранжувати
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

                      //Першою перевіряємо функцію з меншим номером, щоб за одну операцію циклу  можна було переміститися на функцію, яку можна ранжувати
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
//                        //Визначаємо індекс функції, яку потенційно можливо треба буде фільтрувати із сприску
//                        //Першою перевіряємо функцію з меншим номером, щоб за одну операцію циклу  можна було переміститися на функцію, яку можна ранжувати
//                        if (i == 0)
//                        {
//                          index_deleted_function = (RANG_WORK_BV > RANG_WORK_BO) ? RANG_WORK_BO : RANG_WORK_BV;
//                        }
//                        else
//                        {
//                          index_deleted_function = (RANG_WORK_BV > RANG_WORK_BO) ? RANG_WORK_BV : RANG_WORK_BO;
//                        }
//        
//                        //Формуємо маску  для цієї функції
//                        _SET_BIT(maska_func, index_deleted_function);
//        
//                        unsigned int index = 0;
//                        while ((need_filtration == 0) && (index < NUMBER_OUTPUTS))
//                        {
//                          //Пропускаємо текучий номер виходу, бо на ньому дана функція має відображатися під час редагування
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
//                        //У випадку, якщо ввстановлено є ситуація, коли треба фільтрувати функції
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

                    //Перевіряємо, чи ми не вийшли за допустиму кількість функцій
                    if(current_ekran.index_position >= max_row_ranguvannja)
                    {
                      found_new_index = 0;
                      current_ekran.index_position = 0;
                    }
                  }
                }
                position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;
                
                //Формуємо екран відображення зранжованих функцій
                if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_OUTPUT_1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_OUTPUT_10))
                  make_ekran_set_function_in_output_led_df_dt_reg(current_ekran.current_level, INDEX_VIEWING_OUTPUT);
                else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_LED_1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_LED_8))
                  make_ekran_set_function_in_output_led_df_dt_reg(current_ekran.current_level, INDEX_VIEWING_LED);
                else if (current_ekran.current_level == EKRAN_RANGUVANNJA_SILENCE)
                  make_ekran_set_function_in_output_led_df_dt_reg(current_ekran.current_level, INDEX_VIEWING_SILENCE);
                else if (current_ekran.current_level == EKRAN_RANGUVANNJA_RESET)
                  make_ekran_set_function_in_output_led_df_dt_reg(current_ekran.current_level, INDEX_VIEWING_RESET);
                else if (current_ekran.current_level == EKRAN_RANGUVANNJA_ANALOG_REGISTRATOR)
                  make_ekran_set_function_in_output_led_df_dt_reg(current_ekran.current_level, INDEX_VIEWING_A_REG);
                else if (current_ekran.current_level == EKRAN_RANGUVANNJA_DIGITAL_REGISTRATOR)
                  make_ekran_set_function_in_output_led_df_dt_reg(current_ekran.current_level, INDEX_VIEWING_D_REG);
                else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_ALARMS1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_ALARMS2))
                  make_ekran_set_function_in_output_led_df_dt_reg(current_ekran.current_level, INDEX_VIEWING_ALARMS);
                else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_DF1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_DF8))
                  make_ekran_set_function_in_output_led_df_dt_reg(current_ekran.current_level, INDEX_VIEWING_DF);
                else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_SET_DT1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_RESET_DT4))
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
              else if (current_ekran.current_level == EKRAN_RANGUVANNJA_TEST)
              {
                if(current_ekran.edition == 0)
                {
                  unsigned int temp_state = current_settings.ranguvannja_test;
                  if (temp_state == 0) current_ekran.index_position = 0;
                  else
                  {
                    if(++current_ekran.index_position >= MAX_ROW_RANGUVANNJA_TEST) current_ekran.index_position = 0;
                    while ((temp_state & (1<<current_ekran.index_position)) ==0)
                    {
                      current_ekran.index_position++;
                      if(current_ekran.index_position >= MAX_ROW_RANGUVANNJA_TEST) current_ekran.index_position = 0;
                    }
                  }
                }
                else
                {
                  //Редагування
                
                  //Переміщаємося на наступну функцію
                  if(++current_ekran.index_position >= MAX_ROW_RANGUVANNJA_TEST) current_ekran.index_position = 0;
                }
                position_in_current_level_menu[current_ekran.current_level] = current_ekran.index_position;
                
                //Формуємо екран відображення зранжованих функцій
                make_ekran_set_function_in_test();
              }

              //Очистити сигналізацію, що натиснута кнопка 
              new_state_keyboard &= (unsigned int)(~(1<<BIT_KEY_DOWN));
            }
            else if ((new_state_keyboard == (1<<BIT_KEY_RIGHT)) || (new_state_keyboard == (1<<BIT_KEY_LEFT)))
            {
              //Натиснута кнопка RIGHT або LEFT
              //Міняємо на протилежний відповідний біт для вибраної функції
              if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_OUTPUT_1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_OUTPUT_10))
              {
                unsigned int offset, shift;
                offset =  current_ekran.index_position >> 5;        //Це є, фактично, ділення на 32
                shift  = (current_ekran.index_position & (32 - 1)); //Це є, фактично, визначення остачі від ділення на 32

                edition_settings.ranguvannja_outputs[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_OUTPUT_1) + offset] ^=
                  (1 << shift);

                //Формуємо екран відображення зранжованих функцій
                make_ekran_set_function_in_output_led_df_dt_reg(current_ekran.current_level, INDEX_VIEWING_OUTPUT);
              }
              else if((current_ekran.current_level >= EKRAN_RANGUVANNJA_LED_1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_LED_8))
              {
                unsigned int offset, shift;
                offset =  current_ekran.index_position >> 5;        //Це є, фактично, ділення на 32
                shift  = (current_ekran.index_position & (32 - 1)); //Це є, фактично, визначення остачі від ділення на 32

                edition_settings.ranguvannja_leds[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_LED_1) + offset] ^=
                  (1 << shift);

                //Формуємо екран відображення зранжованих функцій
                make_ekran_set_function_in_output_led_df_dt_reg(current_ekran.current_level, INDEX_VIEWING_LED);
              }
              else if(current_ekran.current_level == EKRAN_RANGUVANNJA_SILENCE)
              {
                unsigned int offset, shift;
                offset =  current_ekran.index_position >> 5;        //Це є, фактично, ділення на 32
                shift  = (current_ekran.index_position & (32 - 1)); //Це є, фактично, визначення остачі від ділення на 32

                edition_settings.ranguvannja_silence[offset] ^= (1 << shift);

                //Формуємо екран відображення зранжованих функцій
                make_ekran_set_function_in_output_led_df_dt_reg(current_ekran.current_level, INDEX_VIEWING_SILENCE);
              }
              else if(current_ekran.current_level == EKRAN_RANGUVANNJA_RESET)
              {
                unsigned int offset, shift;
                offset =  current_ekran.index_position >> 5;        //Це є, фактично, ділення на 32
                shift  = (current_ekran.index_position & (32 - 1)); //Це є, фактично, визначення остачі від ділення на 32

                edition_settings.ranguvannja_silence[offset] ^= (1 << shift);

                //Формуємо екран відображення зранжованих функцій
                make_ekran_set_function_in_output_led_df_dt_reg(current_ekran.current_level, INDEX_VIEWING_RESET);
              }
              else if(current_ekran.current_level == EKRAN_RANGUVANNJA_ANALOG_REGISTRATOR)
              {
                unsigned int offset, shift;
                offset =  current_ekran.index_position >> 5;        //Це є, фактично, ділення на 32
                shift  = (current_ekran.index_position & (32 - 1)); //Це є, фактично, визначення остачі від ділення на 32

                edition_settings.ranguvannja_analog_registrator[offset] ^= (1 << shift);

                //Формуємо екран відображення зранжованих функцій
                make_ekran_set_function_in_output_led_df_dt_reg(current_ekran.current_level, INDEX_VIEWING_A_REG);
              }
              else if(current_ekran.current_level == EKRAN_RANGUVANNJA_DIGITAL_REGISTRATOR)
              {
                unsigned int offset, shift;
                offset =  current_ekran.index_position >> 5;        //Це є, фактично, ділення на 32
                shift  = (current_ekran.index_position & (32 - 1)); //Це є, фактично, визначення остачі від ділення на 32

                edition_settings.ranguvannja_digital_registrator[offset] ^= (1 << shift);

                //Формуємо екран відображення зранжованих функцій
                make_ekran_set_function_in_output_led_df_dt_reg(current_ekran.current_level, INDEX_VIEWING_D_REG);
              }
              else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_ALARMS1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_ALARMS2))
              {
                unsigned int offset, shift;
                offset =  current_ekran.index_position >> 5;        //Це є, фактично, ділення на 32
                shift  = (current_ekran.index_position & (32 - 1)); //Це є, фактично, визначення остачі від ділення на 32

                edition_settings.ranguvannja_alarms[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_ALARMS1) + offset] ^= (1 << shift);

                //Формуємо екран відображення зранжованих функцій
                make_ekran_set_function_in_output_led_df_dt_reg(current_ekran.current_level, INDEX_VIEWING_ALARMS);
              }
              else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_DF1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_DF8))
              {
                unsigned int offset, shift;
                offset =  current_ekran.index_position >> 5;        //Це є, фактично, ділення на 32
                shift  = (current_ekran.index_position & (32 - 1)); //Це є, фактично, визначення остачі від ділення на 32

                edition_settings.ranguvannja_df[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_DF1) + offset] ^= (1 << shift);
                
                //Формуємо екран відображення зранжованих функцій
                make_ekran_set_function_in_output_led_df_dt_reg(current_ekran.current_level, INDEX_VIEWING_DF);
              }
              else if ((current_ekran.current_level >= EKRAN_RANGUVANNJA_SET_DT1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_RESET_DT4))
              {
                unsigned int offset, shift;
                offset =  current_ekran.index_position >> 5;        //Це є, фактично, ділення на 32
                shift  = (current_ekran.index_position & (32 - 1)); //Це є, фактично, визначення остачі від ділення на 32

                unsigned int index_in_ekran_list = current_ekran.current_level - EKRAN_RANGUVANNJA_SET_DT1;
                unsigned int index_of_dt = index_in_ekran_list / 2;
                unsigned int type_of_action = index_in_ekran_list & 0x1;
    
                if (type_of_action == INDEX_ML_SET_DT)
                {
                  edition_settings.ranguvannja_set_dt[N_BIG*index_of_dt + offset] ^= (1 << shift);
                }
                else
                {
                  edition_settings.ranguvannja_reset_dt[N_BIG*index_of_dt + offset] ^= (1 << shift);
                }
                
                //Формуємо екран відображення зранжованих функцій
                make_ekran_set_function_in_output_led_df_dt_reg(current_ekran.current_level, INDEX_VIEWING_DT);
              }
              else if((current_ekran.current_level >= EKRAN_RANGUVANNJA_D_AND1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_AND8))
              {
                unsigned int offset, shift;
                offset =  current_ekran.index_position >> 5;        //Це є, фактично, ділення на 32
                shift  = (current_ekran.index_position & (32 - 1)); //Це є, фактично, визначення остачі від ділення на 32

                edition_settings.ranguvannja_d_and[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_AND1) + offset] ^=
                  (1 << shift);

                //Формуємо екран відображення зранжованих функцій
                make_ekran_set_function_in_output_led_df_dt_reg(current_ekran.current_level, INDEX_VIEWING_D_AND);
              }
              else if((current_ekran.current_level >= EKRAN_RANGUVANNJA_D_OR1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_OR8))
              {
                unsigned int offset, shift;
                offset =  current_ekran.index_position >> 5;        //Це є, фактично, ділення на 32
                shift  = (current_ekran.index_position & (32 - 1)); //Це є, фактично, визначення остачі від ділення на 32

                edition_settings.ranguvannja_d_or[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_OR1) + offset] ^=
                  (1 << shift);

                //Формуємо екран відображення зранжованих функцій
                make_ekran_set_function_in_output_led_df_dt_reg(current_ekran.current_level, INDEX_VIEWING_D_OR);
              }
              else if((current_ekran.current_level >= EKRAN_RANGUVANNJA_D_XOR1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_XOR8))
              {
                unsigned int offset, shift;
                offset =  current_ekran.index_position >> 5;        //Це є, фактично, ділення на 32
                shift  = (current_ekran.index_position & (32 - 1)); //Це є, фактично, визначення остачі від ділення на 32

                edition_settings.ranguvannja_d_xor[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_XOR1) + offset] ^=
                  (1 << shift);

                //Формуємо екран відображення зранжованих функцій
                make_ekran_set_function_in_output_led_df_dt_reg(current_ekran.current_level, INDEX_VIEWING_D_XOR);
              }
              else if((current_ekran.current_level >= EKRAN_RANGUVANNJA_D_NOT1) && (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_NOT16))
              {
                unsigned int offset, shift;
                offset =  current_ekran.index_position >> 5;        //Це є, фактично, ділення на 32
                shift  = (current_ekran.index_position & (32 - 1)); //Це є, фактично, визначення остачі від ділення на 32

                edition_settings.ranguvannja_d_not[N_BIG*(current_ekran.current_level - EKRAN_RANGUVANNJA_D_NOT1) + offset] ^=
                  (1 << shift);

                //Формуємо екран відображення зранжованих функцій
                make_ekran_set_function_in_output_led_df_dt_reg(current_ekran.current_level, INDEX_VIEWING_D_NOT);
              }
              else if(current_ekran.current_level == EKRAN_RANGUVANNJA_TEST)
              {
                edition_settings.ranguvannja_test ^= (1 << current_ekran.index_position);

                //Формуємо екран відображення зранжованих функцій
                make_ekran_set_function_in_test();
              }

              //Очистити сигналізацію, що натиснута кнопка 
              if (new_state_keyboard == (1<<BIT_KEY_RIGHT)) new_state_keyboard &= (unsigned int)(~(1<<BIT_KEY_RIGHT));
              else new_state_keyboard &= (unsigned int)(~(1<<BIT_KEY_LEFT));
            }
            else
            {
              //Натиснуто зразу декілька кнопок - це є невизначена ситуація, тому скидаємо сигналізацію про натиснуті кнопки і чекаємо знову
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
//        //Очищаємо всі біти краім упралінських
//        new_state_keyboard &= (1<<BIT_KEY_ENTER)|(1<<BIT_KEY_ESC)|(1<<BIT_KEY_UP)|(1<<BIT_KEY_DOWN)|(1<<BIT_REWRITE);
//        //Дальше виконуємо дії, якщо натиснута кнопка на яку треба реагівати, або стоїть команда обновити екран
//        if (new_state_keyboard !=0)
//        {
//          //Пріоритет стоїть на обновлені екрану
//          if((new_state_keyboard & (1<<BIT_REWRITE)) !=0)
//          {
//            //Очищаємо біт обновлення екрану
//            new_state_keyboard &= (unsigned int)(~(1<<BIT_REWRITE));
//          }
//          else
//          {
//            if (new_state_keyboard == (1<<BIT_KEY_ENTER))
//            {
//              //Натиснута кнопка ENTER
//
//              //Очистити сигналізацію, що натиснута кнопка 
//              new_state_keyboard &= (unsigned int)(~(1<<BIT_KEY_ENTER));
//            }
//            else if (new_state_keyboard == (1<<BIT_KEY_ESC))
//            {
//              //Переходимо у попереднє меню
//              current_ekran.current_level = previous_level_in_current_level_menu[current_ekran.current_level];
//              current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
//              current_ekran.edition = 0;
//
//              //Виставляємо команду на обновлекння нового екрану
//              new_state_keyboard |= (1<<BIT_REWRITE);
//              //Очистити сигналізацію, що натиснута кнопка 
//              new_state_keyboard &= (unsigned int)(~(1<<BIT_KEY_ESC));
//            }
//            else if (new_state_keyboard == (1<<BIT_KEY_UP))
//            {
//              //Натиснута кнопка UP
//
//              //Очистити сигналізацію, що натиснута кнопка 
//              new_state_keyboard &= (unsigned int)(~(1<<BIT_KEY_UP));
//            }
//            else if (new_state_keyboard == (1<<BIT_KEY_DOWN))
//            {
//              //Натиснута кнопка DOWN
//
//              //Очистити сигналізацію, що натиснута кнопка 
//              new_state_keyboard &= (unsigned int)(~(1<<BIT_KEY_DOWN));
//            }
//            else if (new_state_keyboard == (1<<BIT_KEY_RIGHT))
//            {
//              //Натиснута кнопка RIGHT
//
//              //Очистити сигналізацію, що натиснута кнопка 
//              new_state_keyboard &= (unsigned int)(~(1<<BIT_KEY_RIGHT));
//            }
//            else if (new_state_keyboard == (1<<BIT_KEY_LEFT))
//            {
//              //Натиснута кнопка LEFT
//
//              //Очистити сигналізацію, що натиснута кнопка 
//              new_state_keyboard &= (unsigned int)(~(1<<BIT_KEY_LEFT));
//            }
//            else
//            {
//              //Натиснуто зразу декілька кнопок - це є невизначена ситуація, тому скидаємо сигналізацію про натиснуті кнопки і чекаємо знову
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
//
/*****************************************************/
/*****************************************************/
