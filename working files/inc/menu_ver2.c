#include "header.h"

/*****************************************************/
//Функція меню з якої здійснюються всі інші операції
/*****************************************************/
void main_manu_function_ver2(void)
{
  //Перевіряємо чи якась кнопка натиснута
  if (new_state_keyboard !=0)
  {
    static unsigned int prev_edit;
    
    unsigned int max_row = (current_state_menu2.p_max_row == NULL) ? current_state_menu2.max_row : *current_state_menu2.p_max_row;
    
    unsigned int action;
    switch (current_state_menu2.current_level)
    {
    case PASSWORD_MENU2_LEVEL:
      {
        //Зміння для фіксації стану курсору з попреднього рівня меню
        static __PREVIOUS_STATE_CURSOR previous_state_cursor;
        //Змінні для фіксації введеного паролю
        static unsigned int new_password;
        static unsigned int number_symbols;
        
        //Очищаємо всі біти краім упралінських
        new_state_keyboard &= (1<<BIT_KEY_ENTER)|(1<<BIT_KEY_ESC)|(1<<BIT_KEY_UP)|(1<<BIT_KEY_DOWN)|(1<<BIT_KEY_RIGHT)|(1<<BIT_KEY_LEFT)|(1<<BIT_REWRITE);

        if (new_state_keyboard !=0)
        {
          //Пріоритет стоїть на обновлені екрану
          if ( (action = (new_state_keyboard & (1<<BIT_REWRITE ))) !=0)
          {
            previous_state_cursor.position_cursor_x = current_state_menu2.position_cursor_x;              
            previous_state_cursor.cursor_on = current_state_menu2.cursor_on;
            previous_state_cursor.cursor_blinking_on = current_state_menu2.cursor_blinking_on;
            current_state_menu2.cursor_on = 1;
            current_state_menu2.cursor_blinking_on = 1;
            current_state_menu2.position_cursor_x = COL_NEW_PASSWORD_BEGIN;
            position_in_current_level_menu[current_ekran.current_level] = 1;
            //Скидаємо новий пароль у нуль і скидаємо кількість введених символів
            new_password = 0;
            number_symbols = 0;
            
            //Формуємо екран відображення
            p_menu_param_1 = &new_password;
            unsigned int view = false;
            p_menu_param_2 = &view;
            if (current_state_menu2.func_show != NULL) current_state_menu2.func_show();
            else
            {
              //Якщо сюди дійшла програма, значить відбулася недопустива помилка, тому треба зациклити програму, щоб вона пішла на перезагрузку
              total_error_sw_fixed(100);
            }
            //Очищаємо біт обновлення екрану
            new_state_keyboard &= (unsigned int)(~action);
          }
          else if (
                   ((action = (new_state_keyboard & (1<<BIT_KEY_UP   ))) !=0) ||
                   ((action = (new_state_keyboard & (1<<BIT_KEY_DOWN ))) !=0) ||
                   ((action = (new_state_keyboard & (1<<BIT_KEY_RIGHT))) !=0) ||
                   ((action = (new_state_keyboard & (1<<BIT_KEY_LEFT ))) !=0)
                  )   
          {
            unsigned int chosen_number;
            if      (action & (1<<BIT_KEY_UP   )) chosen_number = 1;
            else if (action & (1<<BIT_KEY_RIGHT)) chosen_number = 2;
            else if (action & (1<<BIT_KEY_DOWN )) chosen_number = 3;
            else if (action & (1<<BIT_KEY_LEFT )) chosen_number = 4;
            else
            {
              //Якщо сюди дійшла програма, значить відбулася недопустива помилка, тому треба зациклити програму, щоб вона пішла на перезагрузку
              total_error_sw_fixed(44);
            }
              
            new_password = new_password*10 + chosen_number;
            number_symbols++;
            current_state_menu2.position_cursor_x++;
              
            //Формуємо екран відображення
            unsigned int view = true;
            p_menu_param_2 = &view;
            if (current_state_menu2.func_show != NULL) current_state_menu2.func_show();
            else
            {
              //Якщо сюди дійшла програма, значить відбулася недопустива помилка, тому треба зациклити програму, щоб вона пішла на перезагрузку
              total_error_sw_fixed(101);
            }
              
            //Очистити сигналізацію, що натиснута кнопка 
            new_state_keyboard &= (unsigned int)(~action);
              
            //Перевіряємо чи не натиснуто максимальну кількість символів для паролю (4) і якщо це так, то автоматично приймаємо його
            if (number_symbols >= 4) new_state_keyboard |= (1<<BIT_KEY_ENTER);
          }
          else if ( (action = (new_state_keyboard & (1<<BIT_KEY_ENTER))) !=0)
          {
            //Натиснута кнопка ENTER
            current_state_menu2.current_level = next_level_in_current_level_menu2[current_state_menu2.current_level];
            current_state_menu2.index_position = position_in_current_level_menu2[current_state_menu2.current_level];
            current_state_menu2.position_cursor_x = previous_state_cursor.position_cursor_x;
            current_state_menu2.cursor_on = previous_state_cursor.cursor_on;
            current_state_menu2.cursor_blinking_on = previous_state_cursor.cursor_blinking_on;
            new_level_menu();

            if (
                (new_password == settings_fix.password_1) || 
                (new_password == settings_fix.password_2)
               )   
            {
              //Пароль зійшовся
              //Переходимо у попереднє меню у новому режимі дозволу редагування
              current_state_menu2.edition =  (new_password == settings_fix.password_2) ? 2 : 1;
            }
            else
            {
              //Пароль не зійшовся
              //Переходимо у попереднє меню з попереднім режимом редагування
              current_ekran.edition = prev_edit;
            }
              
            //Виставляємо біт обновлення екрану
            new_state_keyboard |= (1<<BIT_REWRITE);

            //Очистити сигналізацію, що натиснута кнопка 
            new_state_keyboard &= (unsigned int)(~action);
          }
          else if ( (action = (new_state_keyboard & (1<<BIT_KEY_ESC))) !=0)
          {
            //Натиснута кнопка ESC

            //Переходимо у попереднє меню з попереднім режимом редагування
            current_state_menu2.current_level = previous_level_in_current_level_menu2[current_state_menu2.current_level];
            current_state_menu2.index_position = position_in_current_level_menu2[current_state_menu2.current_level];
            current_state_menu2.position_cursor_x = previous_state_cursor.position_cursor_x;
            current_state_menu2.cursor_on = previous_state_cursor.cursor_on;
            current_state_menu2.cursor_blinking_on = previous_state_cursor.cursor_blinking_on;
            new_level_menu();
            current_state_menu2.edition = prev_edit;
              
            //Виставляємо біт обновлення екрану
            new_state_keyboard |= (1<<BIT_REWRITE);

            //Очистити сигналізацію, що натиснута кнопка 
            new_state_keyboard &= (unsigned int)(~action);
          }
          else
          {
            //Натиснуто зразу декілька кнопок - це є невизначена ситуація, тому скидаємо сигналізацію про натиснуті кнопки і чекаємо знову
            unsigned int temp_data = new_state_keyboard;
            new_state_keyboard &= ~temp_data;
          }
        }
        break;
      }
    case MAIN_MANU2_LEVEL:
    case MEASUREMENT_MENU2_LEVEL:
    case INPUTS_OUTPUTS_MENU2_LEVEL:
    case INPUTS_MENU2_LEVEL:
    case OUTPUTS_MENU2_LEVEL:
    case REGISTRATORS_MENU2_LEVEL:
    case DIAGNOSTICS_MENU2_LEVEL:
      {
        //Формуємо маску кнопок. які можуть бути натиснутими
        unsigned int maska_keyboard_bits = (1<<BIT_KEY_ENTER)| (1<<BIT_KEY_ESC)|(1<<BIT_REWRITE)| (1<<BIT_KEY_UP)|(1<<BIT_KEY_DOWN);
        //Очищаємо всі біти краім упралінський
        new_state_keyboard &= maska_keyboard_bits;

        if (new_state_keyboard !=0)
        {
          //Пріоритет стоїть на обновлені екрану
          if (
              ( (action = (new_state_keyboard & (1<<BIT_REWRITE ))) !=0) ||
              ( (action = (new_state_keyboard & (1<<BIT_KEY_UP  ))) !=0) ||
              ( (action = (new_state_keyboard & (1<<BIT_KEY_DOWN))) !=0)
             )   
          {
            if (current_state_menu2.func_show != NULL) current_state_menu2.func_move(action, max_row);
            else
            {
              //Якщо сюди дійшла програма, значить відбулася недопустива помилка, тому треба зациклити програму, щоб вона пішла на перезагрузку
              total_error_sw_fixed(84);
            }
            position_in_current_level_menu2[current_state_menu2.current_level] = current_state_menu2.index_position;
            //Формуємо екран відображення
            if (current_state_menu2.func_show != NULL) current_state_menu2.func_show();
            else
            {
              //Якщо сюди дійшла програма, значить відбулася недопустива помилка, тому треба зациклити програму, щоб вона пішла на перезагрузку
              total_error_sw_fixed(65);
            }
            //Очищаємо біт обновлення екрану
            new_state_keyboard &= (unsigned int)(~action);
          }
          else if ( (action = (new_state_keyboard & (1<<BIT_KEY_ENTER))) !=0)
          {
            //Натиснута кнопка ENTER
            const enum _menu2_levels next_for_main_menu2[MAX_ROW_MAIN_M2] = {TIME_MANU2_LEVEL, MEASUREMENT_MENU2_LEVEL, INPUTS_OUTPUTS_MENU2_LEVEL, REGISTRATORS_MENU2_LEVEL, MAIN_MANU2_LEVEL, DIAGNOSTICS_MENU2_LEVEL};
            const enum _menu2_levels next_for_input_output_menu2[MAX_ROW_INPUT_OUTPUT_M2] = {INPUTS_MENU2_LEVEL, OUTPUTS_MENU2_LEVEL};
            const enum _menu2_levels *p = NULL;
              
            switch (current_state_menu2.current_level)
            {
            case MAIN_MANU2_LEVEL:
              {
                p = next_for_main_menu2;
                break;
              }
            case MEASUREMENT_MENU2_LEVEL:
              {
                break;
              }
            case INPUTS_OUTPUTS_MENU2_LEVEL:
              {
                p = next_for_input_output_menu2;
                break;
              }
            }
              
            if (p != NULL)
            {
              enum _menu2_levels temp_current_level = p[current_state_menu2.index_position];
              if (current_state_menu2.current_level != temp_current_level) 
              {
                previous_level_in_current_level_menu2[temp_current_level] = current_state_menu2.current_level;
                
                current_state_menu2.current_level = temp_current_level;
                current_state_menu2.index_position = position_in_current_level_menu2[temp_current_level];
                new_level_menu();
              }
            }
              
//            else if(current_state_menu2.index_position == INDEX_MAIN_M2_SETTINGS)
//            {
//              //Переходимо на меню настройок
//              current_ekran.current_level = EKRAN_CHOSE_SETTINGS;
//              current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
//            }

            //Виставляємо команду на обновлекння нового екрану
            new_state_keyboard |= (1<<BIT_REWRITE);
              
            //Очистити сигналізацію, що натиснута кнопка 
            new_state_keyboard &= (unsigned int)(~action);
          }
          else if ( (action = (new_state_keyboard & (1<<BIT_KEY_ESC))) !=0)
          {
            //Натиснута кнопка ESC

            if (current_state_menu2.current_level != MAIN_MANU2_LEVEL)
            {
              //Переходимо у попереднє меню
              current_state_menu2.current_level = previous_level_in_current_level_menu2[current_state_menu2.current_level];
              current_state_menu2.index_position = position_in_current_level_menu2[current_state_menu2.current_level];
              new_level_menu();

              //Виставляємо команду на обновлекння нового екрану
              new_state_keyboard |= (1<<BIT_REWRITE);
            }

            //Очистити сигналізацію, що натиснута кнопка 
            new_state_keyboard &= (unsigned int)(~action);
          }
          else
          {
            //Натиснуто зразу декілька кнопок - це є невизначена ситуація, тому скидаємо сигналізацію про натиснуті кнопки і чекаємо знову
            unsigned int temp_data = new_state_keyboard;
            new_state_keyboard &= ~temp_data;
          }
        }
          
        break;
      }
    case TIME_MANU2_LEVEL:
      {
        //Формуємо маску кнопок. які можуть бути натиснутими
        unsigned int maska_keyboard_bits = (1<<BIT_KEY_ENTER)| (1<<BIT_KEY_ESC)|(1<<BIT_REWRITE)| (1<<BIT_KEY_UP)|(1<<BIT_KEY_DOWN);
        
        if (current_state_menu2.edition == 2)
          maska_keyboard_bits |= (1<<BIT_KEY_RIGHT) | (1<<BIT_KEY_LEFT) | (1<<BIT_KEY_UP)|(1<<BIT_KEY_DOWN);
        
        //Очищаємо всі біти краім упралінський
        new_state_keyboard &= maska_keyboard_bits;
        //Дальше виконуємо дії, якщо натиснута кнопка на яку треба реагівати, або стоїть команда обновити екран
        if (new_state_keyboard !=0)
        {
          //Пріоритет стоїть на обновлені екрану
          if( (action = (new_state_keyboard & (1<<BIT_REWRITE))) != 0)
          {
            if (current_state_menu2.func_show != NULL) current_state_menu2.func_move(action, max_row);
            else
            {
              //Якщо сюди дійшла програма, значить відбулася недопустива помилка, тому треба зациклити програму, щоб вона пішла на перезагрузку
              total_error_sw_fixed(87);
            }
            position_in_current_level_menu2[current_state_menu2.current_level] = current_state_menu2.index_position;

            if (current_state_menu2.edition <= 1)
            {
              current_state_menu2.cursor_on = 0;
              current_state_menu2.cursor_blinking_on = 0;
            }
            else
            {
              current_state_menu2.cursor_on = 1;
              current_state_menu2.cursor_blinking_on = 1;
            }

            //Формуємо екран відображення
            if (current_state_menu2.func_show != NULL) current_state_menu2.func_show();
            else
            {
              //Якщо сюди дійшла програма, значить відбулася недопустива помилка, тому треба зациклити програму, щоб вона пішла на перезагрузку
              total_error_sw_fixed(68);
            }
            //Очищаємо біт обновлення екрану
            new_state_keyboard &= (unsigned int)(~action);
          }
          else if (
                   ((action = (new_state_keyboard & (1<<BIT_KEY_UP  ))) !=0) ||
                   ((action = (new_state_keyboard & (1<<BIT_KEY_DOWN))) !=0)
                  )
          {
            //Натиснута кнопка UP
            if(current_state_menu2.edition <= 1)
            {
              //Переміщення у режимі спостерігання
              if (current_state_menu2.func_show != NULL) current_state_menu2.func_move(action, max_row);
              else
              {
                //Якщо сюди дійшла програма, значить відбулася недопустива помилка, тому треба зациклити програму, щоб вона пішла на перезагрузку
                total_error_sw_fixed(88);
              }
              position_in_current_level_menu2[current_state_menu2.current_level] = current_state_menu2.index_position;
            }
            else
            {
              //Редагування числа
              if (current_state_menu2.func_change != NULL) current_state_menu2.func_change(action); 
              else
              {
                //Якщо сюди дійшла програма, значить відбулася недопустива помилка, тому треба зациклити програму, щоб вона пішла на перезагрузку
                total_error_sw_fixed(77);
              }
            }

            //Формуємо екран
            if (current_state_menu2.func_show != NULL) current_state_menu2.func_show();
            else
            {
              //Якщо сюди дійшла програма, значить відбулася недопустива помилка, тому треба зациклити програму, щоб вона пішла на перезагрузку
              total_error_sw_fixed(69);
            }
            //Очистити сигналізацію, що натиснута кнопка 
            new_state_keyboard &= (unsigned int)(~action);
          }
          else if (
                   ((action = (new_state_keyboard & (1<<BIT_KEY_RIGHT))) !=0) ||
                   ((action = (new_state_keyboard & (1<<BIT_KEY_LEFT ))) !=0)
                  )
          {
            if (current_state_menu2.func_change != NULL) current_state_menu2.func_change(action); 
            else
            {
              //Якщо сюди дійшла програма, значить відбулася недопустива помилка, тому треба зациклити програму, щоб вона пішла на перезагрузку
              total_error_sw_fixed(81);
            }
                
            //Формуємо екран
            if (current_state_menu2.func_show != NULL) current_state_menu2.func_show();
            else
            {
              //Якщо сюди дійшла програма, значить відбулася недопустива помилка, тому треба зациклити програму, щоб вона пішла на перезагрузку
              total_error_sw_fixed(73);
            }
            //Очистити сигналізацію, що натиснута кнопка 
            new_state_keyboard &= (unsigned int)(~action);
          }
          else if ( (action = (new_state_keyboard & (1<<BIT_KEY_ENTER))) != 0)
          {
            //Натиснута кнопка ENTER
            unsigned int result;
            if (current_state_menu2.func_edit != NULL) result = current_state_menu2.func_edit();
            else
            {
              //Якщо сюди дійшла програма, значить відбулася недопустива помилка, тому треба зациклити програму, щоб вона пішла на перезагрузку
              total_error_sw_fixed(76);
            }
            if(current_state_menu2.edition <= 1)
            {
              prev_edit = current_state_menu2.edition;
               
              if ((settings_fix.password_2 != 0) || (current_state_menu2.edition == 0))
              {
                //Переходимо на меню запиту паролю
                next_level_in_current_level_menu2[PASSWORD_MENU2_LEVEL] = previous_level_in_current_level_menu2[PASSWORD_MENU2_LEVEL] = current_state_menu2.current_level;
                current_state_menu2.current_level = PASSWORD_MENU2_LEVEL;
                current_state_menu2.index_position = position_in_current_level_menu2[current_state_menu2.current_level];
                new_level_menu();
              }
              else
              {
                //Переходимо у режим редагування
                current_state_menu2.edition = 2;
              }
            }
            else if (current_state_menu2.edition == 2)
            {
              //Проводимо аналіз над редагованими даними
              switch (result)
              {
              case 1:
                {
                  //Дані не зазнали змін
                  current_state_menu2.edition = prev_edit;
                  break;
                }
              case 2:
                {
                  //Дані зазнали змін і є у діапазоні
                  current_state_menu2.edition = 3;
                  break;
                }
              case 3:
                {
                  //Дані зазнали змін але не є у діапазоні
                  current_state_menu2.edition = 4;
                  break;
                }
              }
            }
            else if (current_state_menu2.edition == 3)
            {
              current_state_menu2.edition = prev_edit;
            }
            else if (current_state_menu2.edition == 4)
            {
              current_state_menu2.edition = 2;
            }

            if(current_state_menu2.edition == 3) make_ekran_ask_rewrite();
            else if(current_state_menu2.edition == 4) 
            {
              const unsigned char information_about_error[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
              {
                " Вых.за диапазон",
                " Вих.за діапазон",
                "  Out of Limits ",
                "Вых.за диапазон "
              };
              make_ekran_about_error(information_about_error);
            }
            else
            {
              //Виставляємо біт обновлення екрану
              new_state_keyboard |= (1<<BIT_REWRITE);
            }
              
            //Очистити сигналізацію, що натиснута кнопка 
            new_state_keyboard &= (unsigned int)(~action);
          }
          else if ( (action = (new_state_keyboard & (1<<BIT_KEY_ESC))) !=0)
          {
            //Натиснута кнопка ESC

            if(current_state_menu2.edition <= 1)
            {
              //Вихід у режимі спостерігання
              //Переходимо у попереднє меню
              current_state_menu2.current_level = previous_level_in_current_level_menu2[current_state_menu2.current_level];
              current_state_menu2.index_position = position_in_current_level_menu2[current_state_menu2.current_level];
              new_level_menu();
            }
            else
            {
              //Вихід у режимі редагування без введення змін
              current_state_menu2.edition = prev_edit;
            }

            //Виставляємо команду на обновлекння нового екрану
            new_state_keyboard |= (1<<BIT_REWRITE);

            //Очистити сигналізацію, що натиснута кнопка 
            new_state_keyboard &= (unsigned int)(~action);
          }
          else
          {
            //Натиснуто зразу декілька кнопок - це є невизначена ситуація, тому скидаємо сигналізацію про натиснуті кнопки і чекаємо знову
            unsigned int temp_data = new_state_keyboard;
            new_state_keyboard &= ~temp_data;
          }
        }
        break;
      }
    default:
      {
        //Якщо сюди дійшла програма, значить відбулася недопустива помилка, тому треба зациклити програму, щоб вона пішла на перезагрузку
        total_error_sw_fixed(62);
      }
    }
  }
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
void move_into_ekran_simple(unsigned int action, int max_row)
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
/*****************************************************/

/*****************************************************/
//Робимо повідомлення про те чи треба щоб зміни набули сили
/*****************************************************/
void make_ekran_ask_rewrite(void)
{
  const uint8_t name_string[MAX_NAMBER_LANGUAGE][2][MAX_COL_LCD + 1] = 
  {
    {
     "Ввести изменения",
     "Да-ENTER Нет-ESC"
    },
    {
     "  Ввести зміни  ",
     "Так-ENTER Ні-ESC"
    },
    {
     " Enter changes  ",
     "Yes-ENTER No-ESC"
    },
    {
     "Ввести изменения",
     "Да-ENTER Нет-ESC"
    }
  };

  int index_language;
  
  if (current_ekran.current_level == EKRAN_VIEW_SETTING_LANGUAGE)
    index_language = index_language_in_array(edition_settings.language);
  else
    index_language = index_language_in_array(settings_fix.language);

  //Копіюємо  рядки у робочий екран
  for (size_t i = 0; i < MAX_ROW_LCD; i++)
  {
    for (size_t j = 0; j < MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_language][i][j];
  }
  
  //Курсор не видимий
  current_state_menu2.cursor_on = 0;
  //Курсор не мигає
  current_state_menu2.cursor_blinking_on = 0;
  //Обновити повністю весь екран
  current_state_menu2.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/


/*****************************************************/
//Формування вікна про помилку
/*****************************************************/
void make_ekran_about_error(const unsigned char information[][MAX_COL_LCD + 1])
{
  const uint8_t name_string[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
  {
    "Повтор?Enter/Esc",
    "Повтор?Enter/Esc",
    "Repeat?Enter/Esc",
    "Повтор?Enter/Esc"
  };
  int index_language;

  if (current_ekran.current_level == EKRAN_VIEW_SETTING_LANGUAGE)
    index_language = index_language_in_array(edition_settings.language);
  else
    index_language = index_language_in_array(settings_fix.language);
  
  //Копіюємо  рядки у робочий екран
  for (size_t i = 0; i< MAX_ROW_LCD; i++)
  {
    for (size_t j = 0; j < MAX_COL_LCD; j++) working_ekran[i][j] = (i == 0) ? information[index_language][j] : name_string[index_language][j];
  }
  
  //Курсор не видимий
  current_state_menu2.cursor_on = 0;
  //Курсор не мигає
  current_state_menu2.cursor_blinking_on = 0;
  //Обновити повністю весь екран
  current_state_menu2.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/

/*****************************************************/
//Збільшення або зменшення числа при натисканні кнопки
/*
  Вхідні параменти
  label_value - вказівник на змінюване  число
  inc_dec 
    0 - зменшити на одиницю
    1 - збільшити на одиницю
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
//Зміна стану при зміні робочого екрану
/*****************************************************/
void new_level_menu(void)
{
  switch (current_state_menu2.current_level)
  {
  case MAIN_MANU2_LEVEL:
    {
      current_state_menu2.p_max_row = NULL;
      current_state_menu2.max_row = MAX_ROW_MAIN_M2;
      current_state_menu2.func_move = move_into_main;
      current_state_menu2.func_show = make_ekran_main;
      current_state_menu2.func_edit = NULL;
      current_state_menu2.func_change = NULL;
      current_state_menu2.edition = 0;
      current_state_menu2.cursor_on = 1;
      current_state_menu2.cursor_blinking_on = 0;

      break;
    }
  case TIME_MANU2_LEVEL:
    {
      time_rewrite = 0;
      
      current_state_menu2.p_max_row = NULL;
      current_state_menu2.max_row = MAX_ROW_TIME_CALIBRATION_M2;
      current_state_menu2.func_move = move_into_time;
      current_state_menu2.func_show = make_ekran_time;
      current_state_menu2.func_edit = edit_time;
      current_state_menu2.func_change = change_time;
      current_state_menu2.edition = 1;
      current_state_menu2.cursor_on = 0;
      current_state_menu2.cursor_blinking_on = 0;
      break;
    }
  case MEASUREMENT_MENU2_LEVEL:
    {
      time_rewrite = 0;
      
      current_state_menu2.p_max_row = NULL;
      current_state_menu2.max_row = MAX_ROW_FOR_MEASURMENT_ANALOG_INPUT;
      current_state_menu2.func_move = move_into_ekran_simple;
      current_state_menu2.func_show = make_ekran_measurement;
      current_state_menu2.func_edit = NULL;
      current_state_menu2.func_change = NULL;
      current_state_menu2.edition = 0;
      current_state_menu2.cursor_on = 1;
      current_state_menu2.cursor_blinking_on = 0;
      break;
    }
  case INPUTS_OUTPUTS_MENU2_LEVEL:
    {
      current_state_menu2.p_max_row = NULL;
      current_state_menu2.max_row = MAX_ROW_INPUT_OUTPUT_M2;
      current_state_menu2.func_move = move_into_ekran_simple;
      current_state_menu2.func_show = make_ekran_list_inputs_outputs;
      current_state_menu2.func_edit = NULL;
      current_state_menu2.func_change = NULL;
      current_state_menu2.edition = 0;
      current_state_menu2.cursor_on = 1;
      current_state_menu2.cursor_blinking_on = 0;
      break;
    }
  case INPUTS_MENU2_LEVEL:
  case OUTPUTS_MENU2_LEVEL:
    {
      time_rewrite = 0;
      
      if (current_state_menu2.current_level == INPUTS_MENU2_LEVEL) current_state_menu2.p_max_row = (int*)&current_config.n_input;
      else current_state_menu2.p_max_row = (int*)&current_config.n_output;
      current_state_menu2.max_row = 0;
      current_state_menu2.func_move = move_into_ekran_input_or_output;
      current_state_menu2.func_show = make_ekran_state_inputs_or_outputs;
      current_state_menu2.func_edit = NULL;
      current_state_menu2.func_change = NULL;
      current_state_menu2.edition = 0;
      current_state_menu2.cursor_on = 0;
      current_state_menu2.cursor_blinking_on = 0;
      break;
    }
   case REGISTRATORS_MENU2_LEVEL:
    {
      current_state_menu2.p_max_row = NULL;
      current_state_menu2.max_row = MAX_ROW_LIST_REGISTRATORS_M2;
      current_state_menu2.func_move = move_into_ekran_simple;
      current_state_menu2.func_show = make_ekran_list_registrators;
      current_state_menu2.func_edit = NULL;
      current_state_menu2.func_change = NULL;
      current_state_menu2.edition = 0;
      current_state_menu2.cursor_on = 1;
      current_state_menu2.cursor_blinking_on = 0;
      break;
    }
  case DIAGNOSTICS_MENU2_LEVEL:
    {
      time_rewrite = 0;
      
      current_state_menu2.p_max_row = NULL;
      current_state_menu2.max_row = MAX_ROW_FOR_DIAGNOSTYKA;
      current_state_menu2.func_move = move_into_diagnostics;
      current_state_menu2.func_show = make_ekran_diagnostics;
      current_state_menu2.func_edit = NULL;
      current_state_menu2.func_change = NULL;
      current_state_menu2.edition = 0;
      current_state_menu2.cursor_on = 1;
      current_state_menu2.cursor_blinking_on = 0;
      break;
    }
  case PASSWORD_MENU2_LEVEL:
    {
      current_state_menu2.p_max_row = NULL;
      current_state_menu2.max_row = MAX_ROW_PASSWORD_M2;
      current_state_menu2.func_move = NULL;
      current_state_menu2.func_show = make_ekran_password;
      current_state_menu2.func_edit = NULL;
      current_state_menu2.func_change = NULL;
      current_state_menu2.edition = 0;
      current_state_menu2.cursor_on = 1;
      current_state_menu2.cursor_blinking_on = 1;
      break;
    }
  default:
    {
      //Якщо сюди дійшла програма, значить відбулася недопустива помилка, тому треба зациклити програму, щоб вона пішла на перезагрузку
      total_error_sw_fixed(64);
    }
  }
}
/*****************************************************/
