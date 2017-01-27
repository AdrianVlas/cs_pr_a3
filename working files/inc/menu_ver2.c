#include "header.h"

/*****************************************************/
//Функція меню з якої здійснюються всі інші операції
/*****************************************************/
void main_manu_function_ver2(void)
{
  //Перевіряємо чи якась кнопка натиснута
  if (new_state_keyboard !=0)
  {
    switch (current_state_menu2.current_level)
    {
    case MAIN_MANU2_LEVEL:
      {
        if (new_state_keyboard !=0)
        {
          //Визначаємо скільки рядків є даному пункті меню
          int max_row = (current_state_menu2.max_row_p != NULL) ? *current_state_menu2.max_row_p : current_state_menu2.max_row_c;
          
          //Пріоритет стоїть на обновлені екрану
          if((new_state_keyboard & (1<<BIT_REWRITE)) !=0)
          {
            if(current_state_menu2.index_position >= max_row) current_ekran.index_position = 0;
            while (
                   (
                    (current_state_menu2.current_level == MAIN_MANU2_LEVEL) &&
                    (current_state_menu2.index_position == INDEX_MAIN_M2_MEASURMENTS) &&
                    (current_config.ctrl_analog_inputs != 0)
                   )
                  )
            {
              if(++current_state_menu2.index_position >= max_row) current_state_menu2.index_position = 0;
            }
            position_in_current_level_menu2[current_state_menu2.current_level] = current_state_menu2.index_position;
            
            //Формуємо екран відображення
            current_state_menu2.func_move();
            //Очищаємо біт обновлення екрану
            new_state_keyboard &= (unsigned int)(~(1<<BIT_REWRITE));
          }
          else
          {
            if (new_state_keyboard == (1<<BIT_KEY_ENTER))
            {
              int temp_current_level = current_ekran.current_level;
              
              //Натиснута кнопка ENTER
              if(current_ekran.index_position == INDEX_ML1_TIME)
              {
                //Запам'ятовуємо поперердній екран
                //Переходимо на меню часу-калібровки
                time_rewrite = 0;
                current_ekran.current_level = EKRAN_TIME;
                current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
                current_ekran.edition = 0;
                current_ekran.cursor_on = 0;
                current_ekran.cursor_blinking_on = 0;
                
                /**************************************************/
                //Курсор має бути на першому символі рядка з даними
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
                //Переходимо на меню вибору відображення вимірювань струмів
                current_ekran.current_level = EKRAN_MEASURMENT_CURRENT;
                current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
                current_ekran.edition = 0;
                current_ekran.cursor_on = 1;
                current_ekran.cursor_blinking_on = 0;
              }
              else if(current_ekran.index_position == INDEX_ML1_INPUTS_OUTPUTS)
              {
                //Переходимо на меню вибору відображення списку вибору входів-виходів для відображення їх миттєвого стану
                current_ekran.current_level = EKRAN_LIST_INPUTS_OUTPUTS;
                current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
              }
              else if(current_ekran.index_position == INDEX_ML1_REGISTRATORS)
              {
                //Переходимо на меню вибору відображення списку реєстраторів
                current_ekran.current_level = EKRAN_LIST_REGISTRATORS;
                current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
              }
              else if(current_ekran.index_position == INDEX_ML1_LANGUAGE)
              {
                //Переходимо на меню вибору мови відображення меню
                current_ekran.current_level = EKRAN_VIEW_SETTING_LANGUAGE;
                current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
              }
              else if(current_ekran.index_position == INDEX_ML1_SETTINGS)
              {
                //Переходимо на меню настройок
                current_ekran.current_level = EKRAN_CHOSE_SETTINGS;
                current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
                current_ekran.edition = 0;
                current_ekran.cursor_on = 1;
                current_ekran.cursor_blinking_on = 0;
              }
              else if(current_ekran.index_position == INDEX_ML1_DIAGNOSTYKA)
              {
                //Переходимо на меню настройок
                current_ekran.current_level = EKRAN_DIAGNOSTYKA;
                //Для того, щоб при першому входженні завжди список починався із першої помилки обнуляємо цю позицію
                position_in_current_level_menu[current_ekran.current_level] = 0;
                current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
                current_ekran.edition = 0;
              }
              else if(current_ekran.index_position == INDEX_ML1_KONF)
              {
                //Переходимо на меню конфігурації
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
                //Переходимо на меню Перевірки фазування
                if(current_ekran.index_position == INDEX_ML1_CTRL_PHASE) current_ekran.current_level = EKRAN_CHOOSE_SETTINGS_CTRL_PHASE;
                
                current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
                current_ekran.edition = 0;
                current_ekran.cursor_on = 1;
                current_ekran.cursor_blinking_on = 0;
              }
              //У разі, якщо текучий екран змінився, то запам'ятовуємо екран в який требе буде повернутися
              if (temp_current_level != current_ekran.current_level) 
                previous_level_in_current_level_menu[current_ekran.current_level] = temp_current_level;

              //Виставляємо команду на обновлекння нового екрану
              new_state_keyboard |= (1<<BIT_REWRITE);
              
              //Очистити сигналізацію, що натиснута кнопка 
              new_state_keyboard &= (unsigned int)(~(1<<BIT_KEY_ENTER));
            }
            else if (new_state_keyboard == (1<<BIT_KEY_UP))
            {
              //Натиснута кнопка UP
              current_state_menu2.index_position--;
              do
              {
                if(current_state_menu2.index_position < 0) current_state_menu2.index_position = max_row - 1;
                while (
                        (
                        (current_state_menu2.current_level == MAIN_MANU2_LEVEL) &&
                        (current_state_menu2.index_position == INDEX_MAIN_M2_MEASURMENTS) &&
                        (current_config.ctrl_analog_inputs != 0)
                       )
                      )
                {
                  if(--current_state_menu2.index_position < 0) current_state_menu2.index_position = max_row - 1;
                }
              }
              while (current_state_menu2.index_position < 0);
              position_in_current_level_menu2[current_state_menu2.current_level] = current_state_menu2.index_position;
              
              //Формуємо екран рівня головного меню
              current_state_menu2.func_move();
              //Очистити сигналізацію, що натиснута кнопка 
              new_state_keyboard &= (unsigned int)(~(1<<BIT_KEY_UP));
            }
            else if (new_state_keyboard == (1<<BIT_KEY_DOWN))
            {
              //Натиснута кнопка DOWN
              //current_ekran.index_position вказує номер у повному списку полів
              current_ekran.index_position++;
              do
              {
                if(current_ekran.index_position >= MAX_ROW_FOR_EKRAN_MAIN) current_ekran.index_position = 0;
 
                while (
                       (
                        (current_ekran.index_position == INDEX_ML1_MEASURMENTS) || 
                        (current_ekran.index_position == INDEX_ML1_CTRL_PHASE )
                       )
                       &&
                       ((current_settings.configuration & (1<<CTRL_PHASE_BIT_CONFIGURATION)) == 0)
                      )
                {
                  current_ekran.index_position++;
                }
              }
              while (current_ekran.index_position >= MAX_ROW_FOR_EKRAN_MAIN);
              position_in_current_level_menu[EKRAN_MAIN] = current_ekran.index_position;
              
              //Формуємо екран рівня головного меню
              make_ekran_main();
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
    default:
      {
        //Якщо сюди дійшла програма, значить відбулася недопустива помилка, тому треба зациклити програму, щоб вона пішла на перезагрузку
        total_error_sw_fixed(62);
      }
    }
  }
}
/*****************************************************/

