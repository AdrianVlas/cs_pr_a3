#include "header.h"

/*****************************************************/
//Формуємо екран відображення зранжованих сигналів на активацію команди "Тест"
/*****************************************************/
void make_ekran_set_function_in_test(void)
{
#define NUMBER_ROW_FOR_NOTHING_INFORMATION 2
  
  const unsigned char name_string[MAX_NAMBER_LANGUAGE][MAX_ROW_RANGUVANNJA_TEST][MAX_COL_LCD] = 
  {
    {
      "      Нет       ",
      "  ранжирования  "
    },
    {
      "      Нема      ",
      "   ранжування   "
    },
    {
      "       No       ",
      "    ranking     "
    },
    {
      "      Нет       ",
      "  ранжирования  "
    }
  };
  unsigned char name_string_tmp[NUMBER_ROW_FOR_NOTHING_INFORMATION + MAX_ROW_RANGUVANNJA_TEST][MAX_COL_LCD];

  int index_language = index_language_in_array(current_settings.language);
  for(int index_1 = 0; index_1 < NUMBER_ROW_FOR_NOTHING_INFORMATION; index_1++)
  {
    for(int index_2 = 0; index_2 < MAX_COL_LCD; index_2++)
      name_string_tmp[index_1][index_2] = name_string[index_language][index_1][index_2];
  }
  for(int index_1 = 0; index_1 < MAX_ROW_RANGUVANNJA_TEST; index_1++)
  {
    const unsigned char d_input[MAX_NAMBER_LANGUAGE][MAX_COL_LCD] = 
    {
      "    Д.Вход xx   ",
      "    Д.Вхід xx   ",
      "   D.Input xx   ",
      "    Д.Вход xx   "
    };
    const unsigned int digit_position[MAX_NAMBER_LANGUAGE] = {11, 11, 11, 11};
    for(int index_2 = 0; index_2 < MAX_COL_LCD; index_2++)
    {
      if (index_2 == digit_position[index_language])
      {
        unsigned int number = index_1 + 1;
        if (number < 10)
        {
          name_string_tmp[NUMBER_ROW_FOR_NOTHING_INFORMATION + index_1][index_2] = '0' + number;
        }
        else if (number < 100)
        {
          name_string_tmp[NUMBER_ROW_FOR_NOTHING_INFORMATION + index_1][index_2] = '0' + (number / 10);
        }
      }
      else if (index_2 == (digit_position[index_language] + 1))
      {
        unsigned int number = index_1 + 1;
        if (number < 10)
        {
          name_string_tmp[NUMBER_ROW_FOR_NOTHING_INFORMATION + index_1][index_2] = ' ';
        }
        else if (number < 100)
        {
          name_string_tmp[NUMBER_ROW_FOR_NOTHING_INFORMATION + index_1][index_2] = '0' + (number % 10);
        }
      }
      else name_string_tmp[NUMBER_ROW_FOR_NOTHING_INFORMATION + index_1][index_2] = d_input[index_language][index_2];
    }
  }
  
  if(current_ekran.edition == 0)
  {
    //Випадок, коли ми продивляємося зранжовані функції
    unsigned int state_viewing_input = current_settings.ranguvannja_test;
    
    if (state_viewing_input == 0)
    {
      //Це означає, що нічого не відранжовано на кнопку
      
      //Текучу позицію в сипску переводимо на сам початок
      current_ekran.index_position = 0;
      position_in_current_level_menu[EKRAN_RANGUVANNJA_TEST] = 0;

      //Копіюємо  рядки у робочий екран
      for (unsigned int i=0; i< MAX_ROW_LCD; i++)
      {
        //Копіюємо в робочий екран інформацію, що нічого не відранжовано
        if (i < NUMBER_ROW_FOR_NOTHING_INFORMATION)
          for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string_tmp[i][j];
        else
          for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = ' ';
      }

      //Відображення курсору по вертикалі
      current_ekran.position_cursor_y = 0;
      //Курсор невидимий
      current_ekran.cursor_on = 0;
    }
    else
    {
      /************************************************************/
      //Формуємо список із функцій, які реально відранжовані
      /************************************************************/
      unsigned int position_temp = current_ekran.index_position;
      unsigned int index_of_ekran;
      unsigned int i = 0, offset = 0;

      while ((i + offset) < MAX_ROW_RANGUVANNJA_TEST)
      {
        if ((state_viewing_input & (1<<(i + offset))) == 0)
        {
          for (unsigned int j = i; j < (MAX_ROW_RANGUVANNJA_TEST - offset); j++)
          {
            if ((j + 1) < (MAX_ROW_RANGUVANNJA_TEST - offset))
            {
              for (unsigned int k = 0; k<MAX_COL_LCD; k++)
                name_string_tmp[NUMBER_ROW_FOR_NOTHING_INFORMATION + j][k] = name_string_tmp[NUMBER_ROW_FOR_NOTHING_INFORMATION + j + 1][k];
            }
            else 
            {
              for (unsigned int k = 0; k<MAX_COL_LCD; k++)
                name_string_tmp[NUMBER_ROW_FOR_NOTHING_INFORMATION + j][k] = ' ';
            }
          }
          if (current_ekran.index_position >= ((int)(i + offset))) position_temp--;
          offset++;
        }
        else i++;
      }
      /************************************************************/

    
      index_of_ekran = (position_temp >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;
      
      //Копіюємо  рядки у робочий екран
      for (i=0; i< MAX_ROW_LCD; i++)
      {
        //Наступні рядки треба перевірити, чи їх требе відображати у текучій коффігурації
        if (index_of_ekran < (MAX_ROW_RANGUVANNJA_TEST - offset))
        {
          for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string_tmp[NUMBER_ROW_FOR_NOTHING_INFORMATION + index_of_ekran][j];

          //Підтягуємо назву, щоб не було спереді багато пробілів
          unsigned int iteration = 0;
          while (
                 (working_ekran[i][0] == ' ') &&
                 (working_ekran[i][1] == ' ') &&
                 (iteration < (MAX_COL_LCD - 1 - 1))
                )
          {
            for (unsigned int j = 1; j < MAX_COL_LCD; j++)
            {
              if ((j + 1) < MAX_COL_LCD)
                working_ekran[i][j] = working_ekran[i][j + 1];
              else
                working_ekran[i][j] = ' ';
            }
            iteration++;
          }
        }
        else
          for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = ' ';

        index_of_ekran++;
      }
      //Відображення курору по вертикалі
      current_ekran.position_cursor_y = position_temp & (MAX_ROW_LCD - 1);
      //Курсор видимий
      current_ekran.cursor_on = 1;
    }
    
    //Курсор по горизонталі відображається на першій позиції
    current_ekran.position_cursor_x = 0;
    //Курсор не мигає
    current_ekran.cursor_blinking_on = 0;
  }
  else
  {
    unsigned int temp_data = edition_settings.ranguvannja_test;
    unsigned int position_temp = current_ekran.index_position;
    unsigned int index_of_ekran;
    unsigned int i;
      
    //Множення на два величини position_temp потрібне для того, бо на одну позицію ми використовуємо два рядки (назва + значення)
    index_of_ekran = ((position_temp<<1) >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;

    for (i=0; i< MAX_ROW_LCD; i++)
    {
     if (index_of_ekran < (MAX_ROW_RANGUVANNJA_TEST<<1))//Множення на два константи  MAX_ROW_RANGUVANNJA_TEST потрібне для того, бо на одну позицію ми використовуємо два рядки (назва + значення)
     {
       if ((i & 0x1) == 0)
       {
         //У непарному номері рядку виводимо заголовок
         for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string_tmp[NUMBER_ROW_FOR_NOTHING_INFORMATION + (index_of_ekran>>1)][j];
       }
       else
       {
         //У парному номері рядку виводимо значення
         const unsigned char information[MAX_NAMBER_LANGUAGE][2][MAX_COL_LCD] = 
         {
           {"      ОТКЛ      ", "      ВКЛ       "},
           {"      ВИМК      ", "     ВВІМК      "},
           {"      OFF       ", "       ON       "},
           {"      СЉНД      ", "      КОСУ      "}
        };
        unsigned int maska = 1 << (index_of_ekran >> 1);
          
        for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = information[index_language][((temp_data & maska) != 0)][j];
       }
     }
     else
      for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = ' ';

     index_of_ekran++;
    }

    const unsigned int cursor_x[MAX_NAMBER_LANGUAGE][2] = 
    {
      {5, 5},
      {5, 4},
      {5, 6},
      {5, 5}
    };

    //Відображення курору по вертикалі і курсор завжди має бути у полі із значенням устаки
    current_ekran.position_cursor_x =  cursor_x[index_language][((temp_data & (1 << position_temp)) != 0)];
    current_ekran.position_cursor_y = ((position_temp<<1) + 1) & (MAX_ROW_LCD - 1);
    
    //Курсор мигає
    current_ekran.cursor_blinking_on = 1;
    //Режим відображення у режимі редагування
  }
  

  //Обновити повністю весь екран
  current_ekran.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;

#undef NUMBER_ROW_FOR_NOTHING_INFORMATION
}
/*****************************************************/

/*****************************************************/
//Формуємо екран відображення зранжованих сигналів на вибраний вихід-світлоіндикаторів-о-функцій-реєстраторів
/*****************************************************/
void make_ekran_set_function_in_output_led_df_dt_reg(unsigned int number_ekran, unsigned int type_ekran)
{
#define NUMBER_ROW_FOR_NOTHING_INFORMATION 2
  
  unsigned int state_viewing_input[N_BIG];
  unsigned int max_row_ranguvannja;
  const unsigned char name_string[MAX_NAMBER_LANGUAGE][MAX_ROW_RANGUVANNJA_OUTPUT + NUMBER_ROW_FOR_NOTHING_INFORMATION][MAX_COL_LCD] = 
  {
    {
      "      Нет       ",
      "  ранжирования  ",
      NAME_RANG_RU
    },
    {
      "      Нема      ",
      "   ранжування   ",
      NAME_RANG_UA
    },
    {
      "       No       ",
      "    ranking     ",
      NAME_RANG_EN
    },
    {
      "      Нет       ",
      "  ранжирования  ",
      NAME_RANG_KZ
    },
  };
  unsigned char name_string_tmp[MAX_ROW_RANGUVANNJA_OUTPUT + NUMBER_ROW_FOR_NOTHING_INFORMATION][MAX_COL_LCD];

  int index_language = index_language_in_array(current_settings.language);
  for(int index_1 = 0; index_1 < (MAX_ROW_RANGUVANNJA_OUTPUT + NUMBER_ROW_FOR_NOTHING_INFORMATION); index_1++)
  {
    for(int index_2 = 0; index_2 < MAX_COL_LCD; index_2++)
      name_string_tmp[index_1][index_2] = name_string[index_language][index_1][index_2];
  }
  
  if (type_ekran == INDEX_VIEWING_DT)
  {
    unsigned int index_in_ekran_list = number_ekran - EKRAN_RANGUVANNJA_SET_DT1;
    unsigned int index_of_dt = index_in_ekran_list / 2;
    unsigned int type_of_action = index_in_ekran_list & 0x1;
    
    if(current_ekran.edition == 0)
    {
      if (type_of_action == INDEX_ML_SET_DT)
      {
        for (unsigned int i = 0; i < N_BIG; i++)
        {
          state_viewing_input[i] = current_settings.ranguvannja_set_dt[N_BIG*index_of_dt + i];
        }
      }
      else
      {
        for (unsigned int i = 0; i < N_BIG; i++)
        {
          state_viewing_input[i] = current_settings.ranguvannja_reset_dt[N_BIG*index_of_dt + i];
        }
      }
    }
    else
    {
      if (type_of_action == INDEX_ML_SET_DT)
      {
        for (unsigned int i = 0; i < N_BIG; i++)
        {
          state_viewing_input[i] = edition_settings.ranguvannja_set_dt[N_BIG*index_of_dt + i];
        }
      }
      else
      {
        for (unsigned int i = 0; i < N_BIG; i++)
        {
          state_viewing_input[i] = edition_settings.ranguvannja_reset_dt[N_BIG*index_of_dt + i];
        }
      }
    }
    max_row_ranguvannja = MAX_ROW_RANGUVANNJA_DT;
  }
  else if(type_ekran == INDEX_VIEWING_D_AND)
  {
    if(current_ekran.edition == 0)
    {
      for (unsigned int i = 0; i < N_BIG; i++)
      {
        state_viewing_input[i] = current_settings.ranguvannja_d_and[N_BIG*(number_ekran - EKRAN_RANGUVANNJA_D_AND1) + i];
      }
    }
    else
    {
      for (unsigned int i = 0; i < N_BIG; i++)
      {
        state_viewing_input[i] = edition_settings.ranguvannja_d_and[N_BIG*(number_ekran - EKRAN_RANGUVANNJA_D_AND1) + i];
      }
    }
    max_row_ranguvannja = MAX_ROW_RANGUVANNJA_D_AND;
  }
  else if(type_ekran == INDEX_VIEWING_D_OR)
  {
    if(current_ekran.edition == 0)
    {
      for (unsigned int i = 0; i < N_BIG; i++)
      {
        state_viewing_input[i] = current_settings.ranguvannja_d_or[N_BIG*(number_ekran - EKRAN_RANGUVANNJA_D_OR1) + i];
      }
    }
    else
    {
      for (unsigned int i = 0; i < N_BIG; i++)
      {
        state_viewing_input[i] = edition_settings.ranguvannja_d_or[N_BIG*(number_ekran - EKRAN_RANGUVANNJA_D_OR1) + i];
      }
    }
    max_row_ranguvannja = MAX_ROW_RANGUVANNJA_D_OR;
  }
  else if(type_ekran == INDEX_VIEWING_D_XOR)
  {
    if(current_ekran.edition == 0)
    {
      for (unsigned int i = 0; i < N_BIG; i++)
      {
        state_viewing_input[i] = current_settings.ranguvannja_d_xor[N_BIG*(number_ekran - EKRAN_RANGUVANNJA_D_XOR1) + i];
      }
    }
    else
    {
      for (unsigned int i = 0; i < N_BIG; i++)
      {
        state_viewing_input[i] = edition_settings.ranguvannja_d_xor[N_BIG*(number_ekran - EKRAN_RANGUVANNJA_D_XOR1) + i];
      }
    }
    max_row_ranguvannja = MAX_ROW_RANGUVANNJA_D_XOR;
  }
  else if(type_ekran == INDEX_VIEWING_D_NOT)
  {
    if(current_ekran.edition == 0)
    {
      for (unsigned int i = 0; i < N_BIG; i++)
      {
        state_viewing_input[i] = current_settings.ranguvannja_d_not[N_BIG*(number_ekran - EKRAN_RANGUVANNJA_D_NOT1) + i];
      }
    }
    else
    {
      for (unsigned int i = 0; i < N_BIG; i++)
      {
        state_viewing_input[i] = edition_settings.ranguvannja_d_not[N_BIG*(number_ekran - EKRAN_RANGUVANNJA_D_NOT1) + i];
      }
    }
    max_row_ranguvannja = MAX_ROW_RANGUVANNJA_D_NOT;
  }
  else if(type_ekran == INDEX_VIEWING_OUTPUT)
  {
    if(current_ekran.edition == 0)
    {
      for (unsigned int i = 0; i < N_BIG; i++)
      {
        state_viewing_input[i] = current_settings.ranguvannja_outputs[N_BIG*(number_ekran - EKRAN_RANGUVANNJA_OUTPUT_1) + i];
      }
    }
    else
    {
      for (unsigned int i = 0; i < N_BIG; i++)
      {
        state_viewing_input[i] = edition_settings.ranguvannja_outputs[N_BIG*(number_ekran - EKRAN_RANGUVANNJA_OUTPUT_1) + i];
      }
    }
    max_row_ranguvannja = MAX_ROW_RANGUVANNJA_OUTPUT;
  }
  else if(type_ekran == INDEX_VIEWING_LED)
  {
    if(current_ekran.edition == 0)
    {
      for (unsigned int i = 0; i < N_BIG; i++)
      {
        state_viewing_input[i] = current_settings.ranguvannja_leds[N_BIG*(number_ekran - EKRAN_RANGUVANNJA_LED_1) + i];
      }
    }
    else
    {
      for (unsigned int i = 0; i < N_BIG; i++)
      {
        state_viewing_input[i] = edition_settings.ranguvannja_leds[N_BIG*(number_ekran - EKRAN_RANGUVANNJA_LED_1) + i];
      }
    }
    max_row_ranguvannja = MAX_ROW_RANGUVANNJA_LED;
  }
  else if(type_ekran == INDEX_VIEWING_SILENCE)
  {
    if(current_ekran.edition == 0)
    {
      for (unsigned int i = 0; i < N_BIG; i++)
      {
        state_viewing_input[i] = current_settings.ranguvannja_silence[i];
      }
    }
    else
    {
      for (unsigned int i = 0; i < N_BIG; i++)
      {
        state_viewing_input[i] = edition_settings.ranguvannja_silence[i];
      }
    }
    max_row_ranguvannja = MAX_ROW_RANGUVANNJA_SILENCE;
  }
  else if(type_ekran == INDEX_VIEWING_RESET)
  {
    if(current_ekran.edition == 0)
    {
      for (unsigned int i = 0; i < N_BIG; i++)
      {
        state_viewing_input[i] = current_settings.ranguvannja_reset[i];
      }
    }
    else
    {
      for (unsigned int i = 0; i < N_BIG; i++)
      {
        state_viewing_input[i] = edition_settings.ranguvannja_reset[i];
      }
    }
    max_row_ranguvannja = MAX_ROW_RANGUVANNJA_SILENCE;
  }
  else if(type_ekran == INDEX_VIEWING_A_REG)
  {
    if(current_ekran.edition == 0)
    {
      for (unsigned int i = 0; i < N_BIG; i++)
      {
        state_viewing_input[i] = current_settings.ranguvannja_analog_registrator[i];
      }
    }
    else
    {
      for (unsigned int i = 0; i < N_BIG; i++)
      {
        state_viewing_input[i] = edition_settings.ranguvannja_analog_registrator[i];
      }
    }
    max_row_ranguvannja = MAX_ROW_RANGUVANNJA_ANALOG_REGISTRATOR;
  }
  else if(type_ekran == INDEX_VIEWING_D_REG)
  {
    if(current_ekran.edition == 0)
    {
      for (unsigned int i = 0; i < N_BIG; i++)
      {
        state_viewing_input[i] = current_settings.ranguvannja_digital_registrator[i];
      }
    }
    else
    {
      for (unsigned int i = 0; i < N_BIG; i++)
      {
        state_viewing_input[i] = edition_settings.ranguvannja_digital_registrator[i];
      }
    }
    max_row_ranguvannja = MAX_ROW_RANGUVANNJA_DIGITAL_REGISTRATOR;
  }
  else if(type_ekran == INDEX_VIEWING_ALARMS)
  {
    if(current_ekran.edition == 0)
    {
      for (unsigned int i = 0; i < N_BIG; i++)
      {
        state_viewing_input[i] = current_settings.ranguvannja_alarms[N_BIG*(number_ekran - EKRAN_RANGUVANNJA_ALARMS1) + i];
      }
    }
    else
    {
      for (unsigned int i = 0; i < N_BIG; i++)
      {
        state_viewing_input[i] = edition_settings.ranguvannja_alarms[N_BIG*(number_ekran - EKRAN_RANGUVANNJA_ALARMS1) + i];
      }
    }
    max_row_ranguvannja = MAX_ROW_RANGUVANNJA_ALARMS;
  }

  if(current_ekran.edition == 0)
  {
    //Випадок, коли ми продивляємося зранжовані функції на вході
    if (
        (state_viewing_input[0] == 0) && 
        (state_viewing_input[1] == 0) &&
        (state_viewing_input[2] == 0) &&
        (state_viewing_input[3] == 0) &&
        (state_viewing_input[4] == 0) &&
        (state_viewing_input[5] == 0) &&
        (state_viewing_input[6] == 0)
       )
    {
      //Це означає, що на даний вхід нічого не відранжовано
      
      //Текучу позицію в сипску переводимо на сам початок
      current_ekran.index_position = 0;
      position_in_current_level_menu[number_ekran] = 0;

      //Копіюємо  рядки у робочий екран
      for (unsigned int i=0; i< MAX_ROW_LCD; i++)
      {
        //Копіюємо в робочий екран інформацію, що нічого не відранжовано
        if (i < NUMBER_ROW_FOR_NOTHING_INFORMATION)
          for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string_tmp[i][j];
        else
          for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = ' ';
      }

      //Відображення курсору по вертикалі
      current_ekran.position_cursor_y = 0;
      //Курсор невидимий
      current_ekran.cursor_on = 0;
    }
    else
    {
      /************************************************************/
      //Формуємо список із функцій, які реально відранжовані
      /************************************************************/
      unsigned int position_temp = current_ekran.index_position;
      unsigned int index_of_ekran;
      unsigned int i = 0, offset = 0;
      unsigned int state_current_bit;
      
      while ((i + offset) < max_row_ranguvannja)
      {
        state_current_bit = state_viewing_input[(i + offset)>>5] & (1<<((i + offset) & 0x1f));
          
        if (state_current_bit == 0)
        {
          for (unsigned int j = i; j < (max_row_ranguvannja - offset); j++)
          {
            if ((j + 1) < (max_row_ranguvannja - offset))
            {
              for (unsigned int k = 0; k<MAX_COL_LCD; k++)
                name_string_tmp[j + NUMBER_ROW_FOR_NOTHING_INFORMATION][k] = name_string_tmp[j + NUMBER_ROW_FOR_NOTHING_INFORMATION + 1][k];
            }
            else 
            {
              for (unsigned int k = 0; k<MAX_COL_LCD; k++)
                name_string_tmp[j + NUMBER_ROW_FOR_NOTHING_INFORMATION][k] = ' ';
            }
          }
          if (current_ekran.index_position >= ((int)(i + offset))) position_temp--;
          offset++;
        }
        else i++;
      }
      /************************************************************/

      index_of_ekran = (position_temp >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;
      
      //Копіюємо  рядки у робочий екран
      for (i=0; i< MAX_ROW_LCD; i++)
      {
        //Наступні рядки треба перевірити, чи їх требе відображати у текучій кофігурації
        if (index_of_ekran < max_row_ranguvannja)
        {
          for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string_tmp[index_of_ekran + NUMBER_ROW_FOR_NOTHING_INFORMATION][j];

          //Підтягуємо назву, щоб не було спереді багато пробілів
          unsigned int iteration = 0;
          while (
                 (working_ekran[i][0] == ' ') &&
                 (working_ekran[i][1] == ' ') &&
                 (iteration < (MAX_COL_LCD - 1 - 1))
                )
          {
            for (unsigned int j = 1; j < MAX_COL_LCD; j++)
            {
              if ((j + 1) < MAX_COL_LCD)
                working_ekran[i][j] = working_ekran[i][j + 1];
              else
                working_ekran[i][j] = ' ';
            }
            iteration++;
          }
        }
        else
          for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = ' ';

        index_of_ekran++;
      }
      //Відображення курору по вертикалі
      current_ekran.position_cursor_y = position_temp & (MAX_ROW_LCD - 1);
      //Курсор видимий
      current_ekran.cursor_on = 1;
    }

    //Курсор по горизонталі відображається на першій позиції
    current_ekran.position_cursor_x = 0;
    //Курсор не мигає
    current_ekran.cursor_blinking_on = 0;
  }
  else
  {
    unsigned int position_temp = current_ekran.index_position;
    unsigned int index_of_ekran;
    unsigned int i, offset = 0;

    /*************************************************************/
    //Фільтруємо сигнали, яких у даній конфігурації неприсутні
    /*************************************************************/
    if(
       (type_ekran == INDEX_VIEWING_SILENCE ) ||
       (type_ekran == INDEX_VIEWING_RESET   )
      )
    {
      /*************************************************************/
      //У випадку, якщо відображення здійснюється вікна аналогового реєстратора чи дискретного реєстратора, то відктдпємо ті функції, які не можуть бути джерелати
      /*************************************************************/
      unsigned int index_deleted_function;
      
      if (type_ekran == INDEX_VIEWING_SILENCE)
        index_deleted_function = RANG_SILENCE;
      else if (type_ekran == INDEX_VIEWING_RESET)
        index_deleted_function = RANG_RESET;
      
      /*************************************************************/
      //Відкидаємо ім'я даної функції і зміщаємо біти
      /*************************************************************/

      //Формуємо маску біт, які не треба переміщати при переміщенні імен полів
      unsigned int maska[N_BIG] = {0, 0, 0, 0, 0, 0, 0};
      for (unsigned int j = 0; j < (index_deleted_function - offset); j++) _SET_BIT(maska, j);
          
      /***/
      //Зміщуємо біти стану реанжування функцій разом із їх назвами
      /***/
      unsigned int new_temp_data_1[N_BIG], new_temp_data_2[N_BIG];

      for (unsigned int k = 0; k < N_BIG; k++)
      {
        new_temp_data_1[k] = state_viewing_input[k] & maska[k];

        new_temp_data_2[k] = state_viewing_input[k] & (~maska[k]);
      }

      for (unsigned int k = 0; k < (N_BIG - 1); k++)
      {
        new_temp_data_2[k] = ( (new_temp_data_2[k] >> 1) | ((new_temp_data_2[k + 1] & 0x1) << 31) ) & (~maska[k]);
      }
      new_temp_data_2[N_BIG - 1] =  (new_temp_data_2[N_BIG - 1] >> 1) & (~maska[N_BIG - 1]);
                
      for (unsigned int k = 0; k < N_BIG; k++)
      {
        state_viewing_input[k] = new_temp_data_1[k] | new_temp_data_2[k];
      }
      /***/
      for (unsigned int j = (index_deleted_function - offset); j < (max_row_ranguvannja - offset); j++)
      {
        if ((j + 1) < (max_row_ranguvannja - offset))
        {
          for (unsigned int k = 0; k<MAX_COL_LCD; k++)
            name_string_tmp[j + NUMBER_ROW_FOR_NOTHING_INFORMATION][k] = name_string_tmp[j + NUMBER_ROW_FOR_NOTHING_INFORMATION + 1][k];
        }
        else 
        {
          for (unsigned int k = 0; k<MAX_COL_LCD; k++)
            name_string_tmp[j + NUMBER_ROW_FOR_NOTHING_INFORMATION][k] = ' ';
        }
      }
      if (current_ekran.index_position >= ((int)index_deleted_function)) position_temp--;
      offset++;
      /*************************************************************/

      /*************************************************************/
    }
    else if(
       (type_ekran == INDEX_VIEWING_SILENCE) ||
       (type_ekran == INDEX_VIEWING_RESET  ) ||
       (type_ekran == INDEX_VIEWING_A_REG  ) ||
       (type_ekran == INDEX_VIEWING_D_REG  )
      )
    {
      /*************************************************************/
      //У випадку, якщо відображення здійснюється вікна аналогового реєстратора чи дискретного реєстратора, то відктдпємо ті функції, які не можуть бути джерелати
      /*************************************************************/
      unsigned int index_deleted_function;
      
      if (type_ekran == INDEX_VIEWING_SILENCE)
        index_deleted_function = RANG_SILENCE;
      else if (type_ekran == INDEX_VIEWING_RESET)
        index_deleted_function = RANG_RESET;
      else if (type_ekran == INDEX_VIEWING_A_REG)
        index_deleted_function = RANG_WORK_A_REJESTRATOR;
      else if (type_ekran == INDEX_VIEWING_D_REG)
        index_deleted_function = RANG_WORK_D_REJESTRATOR;
      
      /*************************************************************/
      //Відкидаємо ім'я даної функції і зміщаємо біти
      /*************************************************************/

      //Формуємо маску біт, які не треба переміщати при переміщенні імен полів
      unsigned int maska[N_BIG] = {0, 0, 0, 0, 0, 0, 0};
      for (unsigned int j = 0; j < (index_deleted_function - offset); j++) _SET_BIT(maska, j);
          
      /***/
      //Зміщуємо біти стану реанжування функцій разом із їх назвами
      /***/
      unsigned int new_temp_data_1[N_BIG], new_temp_data_2[N_BIG];

      for (unsigned int k = 0; k < N_BIG; k++)
      {
        new_temp_data_1[k] = state_viewing_input[k] & maska[k];

        new_temp_data_2[k] = state_viewing_input[k] & (~maska[k]);
      }

      for (unsigned int k = 0; k < (N_BIG - 1); k++)
      {
        new_temp_data_2[k] = ( (new_temp_data_2[k] >> 1) | ((new_temp_data_2[k + 1] & 0x1) << 31) ) & (~maska[k]);
      }
      new_temp_data_2[N_BIG - 1] =  (new_temp_data_2[N_BIG - 1] >> 1) & (~maska[N_BIG - 1]);
                
      for (unsigned int k = 0; k < N_BIG; k++)
      {
        state_viewing_input[k] = new_temp_data_1[k] | new_temp_data_2[k];
      }
      /***/
      for (unsigned int j = (index_deleted_function - offset); j < (max_row_ranguvannja - offset); j++)
      {
        if ((j + 1) < (max_row_ranguvannja - offset))
        {
          for (unsigned int k = 0; k<MAX_COL_LCD; k++)
            name_string_tmp[j + NUMBER_ROW_FOR_NOTHING_INFORMATION][k] = name_string_tmp[j + NUMBER_ROW_FOR_NOTHING_INFORMATION + 1][k];
        }
        else 
        {
          for (unsigned int k = 0; k<MAX_COL_LCD; k++)
            name_string_tmp[j + NUMBER_ROW_FOR_NOTHING_INFORMATION][k] = ' ';
        }
      }
      if (current_ekran.index_position >= ((int)index_deleted_function)) position_temp--;
      offset++;
      /*************************************************************/

      /*************************************************************/
    }
//    else if(type_ekran == INDEX_VIEWING_OUTPUT)
//    {
//      /*************************************************************/
//      //У випадку, якщо відображення здійснюється вікна виходів, то відкидаємо ті функції, які не можуть бути зранжовані на дискретний вихід
//      /*
//      А це:
//            "Робота БО" - якщо вона вже є зранжованою на інші виходи (не той що зараз ранжується, щоб мати можливість його зняти)
//            "Робота БВ" - якщо вона вже є зранжованою на інші виходи (не той що зараз ранжується, щоб мати можливість його зняти)
//      */
//      
//      unsigned int current_number_output = number_ekran - EKRAN_RANGUVANNJA_OUTPUT_1;
//
//      for (i = 0; i < 2; i++)
//      {
//        unsigned int index_deleted_function;
//        unsigned int maska_func[N_BIG] = {0, 0, 0, 0, 0, 0, 0, 0};
//        unsigned int need_filtration = 0;
//        //Визначаємо індекс функції, яку потенційно можливо треба буде фільтрувати із сприску
//        //Першою фільтруємо функцію з меншим номером
//        if (i == 0)
//        {
//          index_deleted_function = (RANG_WORK_BV > RANG_WORK_BO) ? RANG_WORK_BO : RANG_WORK_BV;
//        }
//        else
//        {
//          index_deleted_function = (RANG_WORK_BV > RANG_WORK_BO) ? RANG_WORK_BV : RANG_WORK_BO;
//        }
//        
//        //Формуємо маску  для цієї функції
//        _SET_BIT(maska_func, index_deleted_function);
//        
//        unsigned int index = 0;
//        while ((need_filtration == 0) && (index < NUMBER_OUTPUTS))
//        {
//          //Пропускаємо текучий номер виходу, бо на ньому дана функція має відображатися під час редагування
//          if (index != current_number_output)
//          {
//            if (
//                ((current_settings.ranguvannja_outputs[N_BIG*index    ] & maska_func[0]) != 0) ||
//                ((current_settings.ranguvannja_outputs[N_BIG*index + 1] & maska_func[1]) != 0) ||
//                ((current_settings.ranguvannja_outputs[N_BIG*index + 2] & maska_func[2]) != 0) ||
//                ((current_settings.ranguvannja_outputs[N_BIG*index + 3] & maska_func[3]) != 0) ||
//                ((current_settings.ranguvannja_outputs[N_BIG*index + 4] & maska_func[4]) != 0) ||
//                ((current_settings.ranguvannja_outputs[N_BIG*index + 5] & maska_func[5]) != 0) ||
//                ((current_settings.ranguvannja_outputs[N_BIG*index + 6] & maska_func[6]) != 0) ||
//                ((current_settings.ranguvannja_outputs[N_BIG*index + 7] & maska_func[7]) != 0)
//               )
//            {
//              need_filtration = 1;
//            }
//          }
//          index++;
//        }
//        
//        //У випадку, якщо ввстановлено що дану функцію треба відфільтрувати, то відктдпємо її
//        if (need_filtration != 0)
//        {
//          //Формуємо маску біт, які не треба переміщати при переміщенні імен полів
//          unsigned int maska[N_BIG] = {0, 0, 0, 0, 0, 0, 0, 0};
//          for (unsigned int j = 0; j < (index_deleted_function - offset); j++) _SET_BIT(maska, j);
//          
//          /***/
//          //Зміщуємо біти стану реанжування функцій разом із їх назвами
//          /***/
//          unsigned int new_temp_data_1[N_BIG], new_temp_data_2[N_BIG];
//
//          for (unsigned int k = 0; k < N_BIG; k++)
//          {
//            new_temp_data_1[k] = state_viewing_input[k] & maska[k];
//
//            new_temp_data_2[k] = state_viewing_input[k] & (~maska[k]);
//          }
//
//          for (unsigned int k = 0; k < (N_BIG - 1); k++)
//          {
//            new_temp_data_2[k] = ( (new_temp_data_2[k] >> 1) | ((new_temp_data_2[k + 1] & 0x1) << 31) ) & (~maska[k]);
//          }
//          new_temp_data_2[N_BIG - 1] =  (new_temp_data_2[N_BIG - 1] >> 1) & (~maska[N_BIG - 1]);
//                
//          for (unsigned int k = 0; k < N_BIG; k++)
//          {
//            state_viewing_input[k] = new_temp_data_1[k] | new_temp_data_2[k];
//          }
//          /***/
//          for (unsigned int j = (index_deleted_function - offset); j < (max_row_ranguvannja - offset); j++)
//          {
//            if ((j + 1) < (max_row_ranguvannja - offset))
//            {
//              for (unsigned int k = 0; k<MAX_COL_LCD; k++)
//                name_string_tmp[j + NUMBER_ROW_FOR_NOTHING_INFORMATION][k] = name_string_tmp[j + NUMBER_ROW_FOR_NOTHING_INFORMATION + 1][k];
//            }
//            else 
//            {
//              for (unsigned int k = 0; k<MAX_COL_LCD; k++)
//                name_string_tmp[j + NUMBER_ROW_FOR_NOTHING_INFORMATION][k] = ' ';
//            }
//          }
//          if (current_ekran.index_position >= ((int)index_deleted_function)) position_temp--;
//          offset++;
//          /*************************************************************/
//        }
//      }
//      /*************************************************************/
//    }

    //Функції загального призначення пропускаємо (вони знаходяться у початку списку), тому починаємо з розширеної длгіки і дальше по конфігурованій сигналізації
    int index_in_list = NUMBER_GENERAL_SIGNAL_FOR_RANG;
    
    /*
    Розширена логіка
    */

    //Відкидати імена функцій і зміщати біти треба тільки у тому випадку, якщо функції присутні у списку для ранжування для даного захисту
    //Формуємо маску біт, які не треба переміщати при переміщенні імен полів
    {
      unsigned int maska[N_BIG] = {0, 0, 0, 0, 0, 0, 0};
      unsigned int j1;
      for (j1 = 0; j1 < (NUMBER_GENERAL_SIGNAL_FOR_RANG - offset); j1++) _SET_BIT(maska, j1);
         
    //Відкидаємо назви функцій із списку, які є зайвими
      while(index_in_list <= (NUMBER_GENERAL_SIGNAL_FOR_RANG + NUMBER_EL_SIGNAL_FOR_RANG - 1))
      {
        if (
            (
             (
              (index_in_list >= (int)(RANG_DF1_IN + 2*current_settings.number_defined_df)) &&
              (index_in_list <= RANG_DF8_OUT)
             )
             ||
             (
              (type_ekran == INDEX_VIEWING_DF) &&
              (
               (index_in_list == (RANG_DF1_IN  + 2*(number_ekran - EKRAN_RANGUVANNJA_DF1))) ||
               (index_in_list == (RANG_DF1_OUT + 2*(number_ekran - EKRAN_RANGUVANNJA_DF1)))
              )  
             )
            )   
            ||  
            (
             (
              (index_in_list >= (int)(RANG_DT1_SET + 3*current_settings.number_defined_dt)) &&
              (index_in_list <= RANG_DT4_OUT)
             )
             ||
             (
              (type_ekran == INDEX_VIEWING_DT) &&
              (
               (index_in_list == (RANG_DT1_SET   + 3*((number_ekran - EKRAN_RANGUVANNJA_SET_DT1) / 2))) ||
               (index_in_list == (RANG_DT1_RESET + 3*((number_ekran - EKRAN_RANGUVANNJA_SET_DT1) / 2))) ||
               (index_in_list == (RANG_DT1_OUT   + 3*((number_ekran - EKRAN_RANGUVANNJA_SET_DT1) / 2)))
              )  
             ) 
            )   
            ||  
            (
             (
              (index_in_list >= (int)(RANG_D_AND1 + current_settings.number_defined_and)) &&
              (index_in_list <= RANG_D_AND8)
             )   
             ||
             (
              (type_ekran == INDEX_VIEWING_D_AND) &&
              (index_in_list == (RANG_D_AND1 + (number_ekran - EKRAN_RANGUVANNJA_D_AND1)))
             )   
            )   
            ||  
            (
             (
              (index_in_list >= (int)(RANG_D_OR1 + current_settings.number_defined_or)) &&
              (index_in_list <= RANG_D_OR8)
             )   
             ||
             (
              (type_ekran == INDEX_VIEWING_D_OR) &&
              (index_in_list == (RANG_D_OR1 + (number_ekran - EKRAN_RANGUVANNJA_D_OR1)))
             )   
            )   
            ||  
            (
             (
              (index_in_list >= (int)(RANG_D_XOR1 + current_settings.number_defined_xor)) &&
              (index_in_list <= RANG_D_XOR8)
             )   
             ||
             (
              (type_ekran == INDEX_VIEWING_D_XOR) &&
              (index_in_list == (RANG_D_XOR1 + (number_ekran - EKRAN_RANGUVANNJA_D_XOR1)))
             )   
            )   
            ||  
            (
             (
              (index_in_list >= (int)(RANG_D_NOT1 + current_settings.number_defined_not)) &&
              (index_in_list <= RANG_D_NOT16)
             )   
             ||
             (
              (type_ekran == INDEX_VIEWING_D_NOT) &&
              (index_in_list == (RANG_D_NOT1 + (number_ekran - EKRAN_RANGUVANNJA_D_NOT1)))
             )   
            )   
           )
        {
          /***/
          //Зміщуємо біти стану реанжування функцій разом із їх назвами
          /***/
          unsigned int new_temp_data_1[N_BIG], new_temp_data_2[N_BIG];

          for (unsigned int k = 0; k < N_BIG; k++)
          {
            new_temp_data_1[k] = state_viewing_input[k] & maska[k];

            new_temp_data_2[k] = state_viewing_input[k] & (~maska[k]);
          }

          for (unsigned int k = 0; k < (N_BIG - 1); k++)
          {
            new_temp_data_2[k] = ( (new_temp_data_2[k] >> 1) | ((new_temp_data_2[k + 1] & 0x1) << 31) ) & (~maska[k]);
          }
          new_temp_data_2[N_BIG - 1] =  (new_temp_data_2[N_BIG - 1] >> 1) & (~maska[N_BIG - 1]);
         
          for (unsigned int k = 0; k < N_BIG; k++)
          {
            state_viewing_input[k] = new_temp_data_1[k] | new_temp_data_2[k];
          }
          /***/
          for (unsigned int j = (index_in_list - offset); j < (max_row_ranguvannja - offset); j++)
          {
            if ((j + 1) < (max_row_ranguvannja - offset))
            {
              for (unsigned int k = 0; k < MAX_COL_LCD; k++)
                name_string_tmp[j + NUMBER_ROW_FOR_NOTHING_INFORMATION][k] = name_string_tmp[j + NUMBER_ROW_FOR_NOTHING_INFORMATION + 1][k];
            }
            else 
            {
              for (unsigned int k = 0; k<MAX_COL_LCD; k++)
                name_string_tmp[j + NUMBER_ROW_FOR_NOTHING_INFORMATION][k] = ' ';
             }
          }
          if (current_ekran.index_position >= index_in_list) position_temp--;
          
          offset++;
        }
        else
        {
          _SET_BIT(maska, j1);
          j1++;
        }
         
        index_in_list++;
      }
    }
            
    int min_max_number[TOTAL_NUMBER_PROTECTION][2] =
    {
      {
       (NUMBER_GENERAL_SIGNAL_FOR_RANG + NUMBER_EL_SIGNAL_FOR_RANG),
       (NUMBER_GENERAL_SIGNAL_FOR_RANG + NUMBER_EL_SIGNAL_FOR_RANG + NUMBER_CTRL_PHASE_SIGNAL_FOR_RANG - 1)
      }
    };
    for (i = 0; i < TOTAL_NUMBER_PROTECTION; i++)
    {
      
      if((current_settings.configuration & (1 << i)) != 0)
      {
        //Захист присутнійсть, тому функції фільтрувати не потрібно - переводимо індекс на наступні функції
        //Додаємо кількість функцій до поточного індексу, якщо для поточного захисту реально були присутні функції,
        //бо інкаше ми вже знаходимося на індексі наступного захисту
        if(min_max_number[i][0] >=0)
        {
          index_in_list += ((min_max_number[i][1] - min_max_number[i][0]) + 1);
        }
      }
      else if (min_max_number[i][0] >=0)
      {
        //Відкидати імена функцій і зміщати біти треба тільки у тому випадку, якщо функції пристні у списку для ранжування для даного захисту
        //Формуємо маску біт, які не треба переміщати при переміщенні імен полів
        unsigned int maska[N_BIG] = {0, 0, 0, 0, 0, 0, 0};
        for (unsigned int j = 0; j < (min_max_number[i][0] - offset); j++) _SET_BIT(maska, j);
          
        //Відкидаємо назви функцій із списку, які є зайвими
        while(index_in_list <= min_max_number[i][1])
        {
          /***/
          //Зміщуємо біти стану реанжування функцій разом із їх назвами
          /***/
          unsigned int new_temp_data_1[N_BIG], new_temp_data_2[N_BIG];

          for (unsigned int k = 0; k < N_BIG; k++)
          {
            new_temp_data_1[k] = state_viewing_input[k] & maska[k];

            new_temp_data_2[k] = state_viewing_input[k] & (~maska[k]);
          }

          for (unsigned int k = 0; k < (N_BIG - 1); k++)
          {
            new_temp_data_2[k] = ( (new_temp_data_2[k] >> 1) | ((new_temp_data_2[k + 1] & 0x1) << 31) ) & (~maska[k]);
          }
          new_temp_data_2[N_BIG - 1] =  (new_temp_data_2[N_BIG - 1] >> 1) & (~maska[N_BIG - 1]);
                
          for (unsigned int k = 0; k < N_BIG; k++)
          {
            state_viewing_input[k] = new_temp_data_1[k] | new_temp_data_2[k];
          }
          /***/
          for (unsigned int j = (index_in_list - offset); j < (max_row_ranguvannja - offset); j++)
          {
            if ((j + 1) < (max_row_ranguvannja - offset))
            {
              for (unsigned int k = 0; k<MAX_COL_LCD; k++)
                name_string_tmp[j + NUMBER_ROW_FOR_NOTHING_INFORMATION][k] = name_string_tmp[j + NUMBER_ROW_FOR_NOTHING_INFORMATION + 1][k];
            }
            else 
            {
              for (unsigned int k = 0; k<MAX_COL_LCD; k++)
                name_string_tmp[j + NUMBER_ROW_FOR_NOTHING_INFORMATION][k] = ' ';
            }
          }
          if (current_ekran.index_position >= index_in_list) position_temp--;
          
          offset++;
          index_in_list++;
        }
      }
    }
    /*************************************************************/

    //Множення на два величини position_temp потрібне для того, бо на одну позицію ми використовуємо два рядки (назва + значення)
    index_of_ekran = ((position_temp<<1) >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;

    for (i=0; i< MAX_ROW_LCD; i++)
    {
     if (index_of_ekran < (max_row_ranguvannja<<1))//Множення на два константи  max_row_ranguvannja потрібне для того, бо на одну позицію ми використовуємо два рядки (назва + значення)
     {
       if ((i & 0x1) == 0)
       {
         //У непарному номері рядку виводимо заголовок
         for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string_tmp[(index_of_ekran>>1) + NUMBER_ROW_FOR_NOTHING_INFORMATION][j];
       }
       else
       {
         //У парному номері рядку виводимо стан функції
         const unsigned char information[MAX_NAMBER_LANGUAGE][2][MAX_COL_LCD] = 
         {
           {"      ОТКЛ      ", "      ВКЛ       "},
           {"      ВИМК      ", "     ВВІМК      "},
           {"      OFF       ", "       ON       "},
           {"      СЉНД      ", "      КОСУ      "}
         };
         unsigned int index_bit = index_of_ekran >> 1;
         
         for (unsigned int j = 0; j < MAX_COL_LCD; j++) working_ekran[i][j] = information[index_language][((state_viewing_input[index_bit >> 5] & ( 1<< (index_bit & 0x1f))) != 0)][j];
       }
     }
     else
     for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = ' ';

     index_of_ekran++;
    }
    
    const unsigned int cursor_x[MAX_NAMBER_LANGUAGE][2] = 
    {
      {5, 5},
      {5, 4},
      {5, 6},
      {5, 5}
    };

    //Відображення курору по вертикалі і курсор завжди має бути у полі із значенням устаки
    current_ekran.position_cursor_x =  cursor_x[index_language][((state_viewing_input[position_temp >> 5] & (1 << (position_temp & 0x1f))) != 0)];
    current_ekran.position_cursor_y = ((position_temp<<1) + 1) & (MAX_ROW_LCD - 1);
    
    //Курсор мигає
    current_ekran.cursor_blinking_on = 1;
    //Режим відображення у режимі редагування
  }
  

  //Обновити повністю весь екран
  current_ekran.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;

#undef NUMBER_ROW_FOR_NOTHING_INFORMATION
}
/*****************************************************/

/*****************************************************/
//Перевірка, чи текучий індекс вказує на функцію, яка присутня у даній конфігурації
/*****************************************************/
void check_current_index_is_presented_in_configuration(
                                                         unsigned int* found_new_index_tmp,
                                                                  /*int* add_filter_point,*/
                                                                  EL_FILTER_STRUCT el_filter[],
                                                                  int plus_minus,
                                                                  int number_general_function_plus_number_el_function,
                                                                  int number_ctrl_phase_function
                                                        )
{
  if(plus_minus == 1)
  {
    if (current_ekran.index_position < number_general_function_plus_number_el_function) *found_new_index_tmp = 1;
    else
    {
      if (current_ekran.index_position < (number_general_function_plus_number_el_function + number_ctrl_phase_function))
      {
        if ((current_settings.configuration & (1<<CTRL_PHASE_BIT_CONFIGURATION)) != 0) *found_new_index_tmp = 1;
        else current_ekran.index_position = number_general_function_plus_number_el_function + number_ctrl_phase_function;
      }
    }

    for (unsigned int i = 0; i < NUMBER_DEFINED_ELEMENTS; i++)
    {
      if (
          (el_filter[i].present != 0) &&
          (current_ekran.index_position >= (el_filter[i].start_index + el_filter[i].number_per_index*el_filter[i].real_number)) &&
          (current_ekran.index_position <=  el_filter[i].stop_index)
         )
      {
        *found_new_index_tmp = 0;
        current_ekran.index_position++;
        break; //вихід із циклу
      }
    }
  }
  else
  {
    if (current_ekran.index_position < number_general_function_plus_number_el_function) *found_new_index_tmp = 1;
    else
    {
      if (current_ekran.index_position < (number_general_function_plus_number_el_function + number_ctrl_phase_function))
      {
        if ((current_settings.configuration & (1<<CTRL_PHASE_BIT_CONFIGURATION)) != 0) *found_new_index_tmp = 1;
        else current_ekran.index_position = number_general_function_plus_number_el_function - 1;
      }
    }

    for (unsigned int i = 0; i < NUMBER_DEFINED_ELEMENTS; i++)
    {
      if (
          (el_filter[i].present != 0) &&
          (current_ekran.index_position >= (el_filter[i].start_index + el_filter[i].number_per_index*el_filter[i].real_number)) &&
          (current_ekran.index_position <=  el_filter[i].stop_index)
         )
      {
        *found_new_index_tmp = 0;
        current_ekran.index_position--;
        break; //вихід із циклу
      }
    }
  }
}
/*****************************************************/

/*****************************************************/
//
/*****************************************************/
/*****************************************************/
