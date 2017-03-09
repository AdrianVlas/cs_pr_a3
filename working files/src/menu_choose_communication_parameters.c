#include "header.h"

/*****************************************************/
//Формуємо екран відображення заголовків настроювання комунікації
/*****************************************************/
void make_ekran_choose_communication_parameters(void)
{
  const uint8_t name_string[MAX_NAMBER_LANGUAGE][MAX_ROW_CHCP_M2][MAX_COL_LCD + 1] = 
  {
    {
      " Имя ячейки     ",
      " Адрес ячейки   ",
      " Настр.RS-485   "
    },
    {
      " Ім'я комірки   ",
      " Адреса комірки ",
      " Налашт.RS-485  "
    },
    {
      " Bay name       ",
      " Bay Address    ",
      " RS-485 Settings"
    },
    {
      " Имя ячейки     ",
      " Адрес ячейки   ",
      " Настр.RS-485   "
    }
  };
  int index_language = index_language_in_array(select_struct_settings_fix()->language);

  unsigned int position_temp = current_state_menu2.index_position;
  unsigned int index_in_ekran = (position_temp >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;

  
  //Копіюємо  рядки у робочий екран
  for (size_t i = 0; i < MAX_ROW_LCD; i++)
  {
    for (size_t j = 0; j < MAX_COL_LCD; j++) 
    {
      working_ekran[i][j] = (index_in_ekran < MAX_ROW_CHCP_M2) ? name_string[index_language][index_in_ekran][j] : ' ';
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
//Формуємо екран відображення імені ячейки
/*****************************************************/
void make_ekran_name_of_cell(void)
{
  //Можливо треба буде додати  нові символи при зміні мови цією функцією
  index_language_in_array(select_struct_settings_fix()->language);
  
  unsigned int position_temp = current_state_menu2.index_position;
  unsigned int index_in_ekran = (position_temp >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;
  
    uint8_t *p_name_of_cell;
    p_name_of_cell = (current_state_menu2.edition == ED_VIEWING) ? settings_fix_prt.name_of_cell : settings_fix.name_of_cell;
  //Копіюємо  рядки у робочий екран
  for (size_t i = 0; i < MAX_ROW_LCD; i++)
  {
    for (size_t j = 0; j<MAX_COL_LCD; j++)
    {
       uint8_t symbol = (((index_in_ekran << POWER_MAX_COL_LCD) + j) < MAX_CHAR_IN_NAME_OF_CELL) ? p_name_of_cell[(index_in_ekran << POWER_MAX_COL_LCD) + j] : ' ';
       working_ekran[i][j] = (symbol >= 0x20) ? symbol : ' ';
    }

    index_in_ekran++;
  }

  //Курсор по горизонталі відображається на першій позиції
  current_state_menu2.position_cursor_x = 0;
  //Відображення курору по вертикалі
  current_state_menu2.position_cursor_y = position_temp & (MAX_ROW_LCD - 1);
  //Курсор  не видимий
  current_state_menu2.cursor_on = 0;
  //Курсор не мигає
  current_state_menu2.cursor_blinking_on = 0;
  //Обновити повністю весь екран
  current_state_menu2.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/

/*****************************************************/
//Формуємо екран відображення адреси для комунікації з верхнім рівнем
/*****************************************************/
void make_ekran_address(void)
{
  if (current_state_menu2.edition == ED_WARNING_ENTER_ESC)
  {
    const unsigned char information_about_error[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
    {
      " Вых.за диапазон",
      " Вих.за діапазон",
      "  Out of Limits ",
      "Вых.за диапазон "
    };
    make_ekran_about_info(true, information_about_error);
  }
  else
  {
    const uint8_t name_string[MAX_NAMBER_LANGUAGE][MAX_ROW_ADDRESS_M2][MAX_COL_LCD + 1] = 
    {
      "     Адрес      ",
      "     Адреса     ",
      "    Address     ",
      "     Адрес      "
    };
    int index_language = index_language_in_array(select_struct_settings_fix()->language);
  
    unsigned int position_temp = current_state_menu2.index_position;
    //Множення на два величини position_temp потрібне для того, бо на одну позицію ми використовуємо два рядки (назва + значення)
    unsigned int index_in_ekran = ((position_temp << 1) >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;

    uint32_t *p_address;
    if (current_state_menu2.edition == ED_VIEWING) p_address = &settings_fix_prt.address;
    else if (current_state_menu2.edition == ED_CAN_BE_EDITED) p_address = &settings_fix.address;
    else p_address = &settings_fix_edit.address;
  
    unsigned int first_symbol;
    uint32_t vaga, value;
    size_t col_begin, col_end;
  
    for (size_t i = 0; i < MAX_ROW_LCD; i++)
    {
      unsigned int index_in_ekran_tmp = index_in_ekran >> 1;
      if (index_in_ekran_tmp < MAX_ROW_ADDRESS_M2)
      {
        if ((i & 0x1) == 0)
        {
          //У непарному номері рядку виводимо заголовок
          for (size_t j = 0; j < MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_language][index_in_ekran_tmp][j];
          first_symbol = 0; //помічаємо, що ще ніодин значущий символ не виведений

          switch (index_in_ekran_tmp)
          {
          case INDEX_M2_ADDRESS:
            {
              vaga = 100; //максимальний ваговий коефіцієнт
              col_begin = COL_ADDRESS_BEGIN;
              col_end = COL_ADDRESS_END;
            
              value = *p_address;
          
              break;
            }
          }
        }
        else
        {
          //У парному номері рядку виводимо значення уставки
          for (size_t j = 0; j < MAX_COL_LCD; j++)
          {
            if ((j < col_begin) ||  (j > col_end ))working_ekran[i][j] = ' ';
            else
              calc_int_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol);
          }
        }
      }
      else
        for (size_t j = 0; j < MAX_COL_LCD; j++) working_ekran[i][j] = ' ';

      index_in_ekran++;
    }

    //Відображення курору по вертикалі і курсор завжди має бути у полі із значенням устаки
    current_state_menu2.position_cursor_y = ((position_temp<<1) + 1) & (MAX_ROW_LCD - 1);
    //Курсор по горизонталі відображається на першому символі у випадку, коли ми не в режимі редагування, інакше позиція буде визначена у функцї main_manu_function
    if (current_state_menu2.edition <= ED_CAN_BE_EDITED)
    {
      int last_position_cursor_x = MAX_COL_LCD;
      switch (current_state_menu2.index_position)
      {
      case INDEX_M2_ADDRESS:
        {
          current_state_menu2.position_cursor_x = COL_ADDRESS_BEGIN;
          last_position_cursor_x = COL_ADDRESS_END;
          break;
        }
      }

      //Підтягуємо курсор до першого символу
      while (
             ((working_ekran[current_state_menu2.position_cursor_y][current_state_menu2.position_cursor_x + 1]) == ' ') && 
             (current_state_menu2.position_cursor_x < (last_position_cursor_x -1))
            )
      {
        current_state_menu2.position_cursor_x++;
      }

      //Курсор ставимо так, щоб він був перед числом
      if (
          ((working_ekran[current_state_menu2.position_cursor_y][current_state_menu2.position_cursor_x]) != ' ') && 
          (current_state_menu2.position_cursor_x > 0)
         )
      {
        current_state_menu2.position_cursor_x--;
      }
    }
    //Курсор видимий
    current_state_menu2.cursor_on = 1;
    //Курсор не мигає
    if(current_state_menu2.edition <= ED_CAN_BE_EDITED) current_state_menu2.cursor_blinking_on = 0;
    else current_state_menu2.cursor_blinking_on = 1;
  }
  //Обновити повністю весь екран
  current_state_menu2.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/

/*****************************************************/
/*
Натискування Enter у вікні відображення адреси
*/
/*****************************************************/
enum _result_pressed_enter_during_edition press_enter_in_address(void)
{
  enum _result_pressed_enter_during_edition result = RPEDE_NONE;
  switch (current_state_menu2.edition)
  {
  case ED_VIEWING:
  case ED_CAN_BE_EDITED:
    {
      switch (current_state_menu2.index_position)
      {
      case INDEX_M2_ADDRESS:
        {
          current_state_menu2.position_cursor_x = COL_ADDRESS_BEGIN;
          break;
        }
      }
      break;
    }
  case ED_EDITION:
    {
      //Перевіряємо, чи дані рельно змінилися
      result = RPEDE_DATA_NOT_CHANGED;
      
      uint32_t *p_value_edit = &settings_fix_edit.address;
      uint32_t *p_value_cont = &settings_fix.address;
      switch (current_state_menu2.index_position)
      {
      case INDEX_M2_ADDRESS:
        {
          if (*p_value_cont != *p_value_edit) 
          {
            if (check_data_setpoint(*p_value_edit, KOEF_ADDRESS_MIN, KOEF_ADDRESS_MAX) == 1)
            {
              *p_value_cont = *p_value_edit;
              
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
Натискування ESC у вікні витримок дискретного входу
*/
/*****************************************************/
void press_esc_in_address(void)
{
  uint32_t *p_value_edit = &settings_fix_edit.address;
  uint32_t *p_value_cont = &settings_fix.address;
  switch (current_state_menu2.index_position)
  {
  case INDEX_DELAY_INPUT_M2_DOPUSK:
    {
      *p_value_edit = *p_value_cont;
      break;
    }
  }
}
/*****************************************************/

/*****************************************************/
//Зміна налаштувань допуску дискретного входу
/*****************************************************
Вхідні параметри
(1 << BIT_KEY_DOWN) - натснуто кнопку вниз
(1 << BIT_KEY_UP)   - атиснуто кнопку вверх
(1 << BIT_KEY_RIGHT)- натснуто кнопку праворуч
(1 << BIT_KEY_LEFT) - атиснуто кнопку ліворуч

Вхідні параметри
  Немає
*****************************************************/
void change_address(unsigned int action)
{
  //Вводимо число у відповідне поле
  if (action & ((1 << BIT_KEY_DOWN) | (1 << BIT_KEY_UP)))
  {
    uint32_t *p_value = NULL;
    unsigned int col_end;
    switch (current_state_menu2.index_position)
    {
    case INDEX_M2_ADDRESS:
      {
        p_value = &settings_fix_edit.address;
        col_end = COL_ADDRESS_END;
        break;
      }
    }
    
    if (p_value != NULL)
    {
      *p_value = edit_setpoint(((action & (1 << BIT_KEY_UP)) != 0), *p_value, 0, 0, col_end, 1);
    }
  }
  else if (
           ((action & (1 << BIT_KEY_LEFT )) != 0) ||
           ((action & (1 << BIT_KEY_RIGHT)) != 0)
          )   
  {
    int col_begin, col_end;
    switch (current_state_menu2.index_position)
    {
    case INDEX_M2_ADDRESS:
      {
        col_begin = COL_ADDRESS_BEGIN;
        col_end = COL_ADDRESS_END;

        break;
      }
    }
    
    if (action & (1 << BIT_KEY_LEFT ))
    {
      current_state_menu2.position_cursor_x--;
      if ((current_state_menu2.position_cursor_x < col_begin) ||
          (current_state_menu2.position_cursor_x > col_end))
        current_state_menu2.position_cursor_x = col_end;
    }
    else
    {
      current_state_menu2.position_cursor_x++;
      if ((current_state_menu2.position_cursor_x < col_begin) ||
          (current_state_menu2.position_cursor_x > col_end))
        current_state_menu2.position_cursor_x = col_begin;
    }
    
  }
}
/*****************************************************/

/*****************************************************/
//Формуємо екран відображення заголовків настроювання комунікації
/*****************************************************/
void make_ekran_chose_setting_rs485(void)
{
  const unsigned char name_string[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_CHOSE_SETTING_RS485][MAX_COL_LCD] = 
  {
    {
      " Скорость обмена",
      " Контр.четности ",
      " Колич.стоп-бит ",
      " Конец приёма   "
    },
    {
      " Швидкість обм. ",
      " Контр.парності ",
      "Кільк.стоп-біт  ",
      "Кінець приймання"
    },
    {
      " Baud rate      ",
      " Parity         ",
      " Stop Bits      ",
      "End of Reception"
    },
    {
      " Скорость обмена",
      " Контр.четности ",
      " Колич.стоп-бит ",
      " Конец приёма   "
    }
  };
  int index_language = index_language_in_array(current_settings.language);
  
  unsigned int position_temp = current_ekran.index_position;
  unsigned int index_of_ekran;
  
  
  index_of_ekran = (position_temp >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;

  
  //Копіюємо  рядки у робочий екран
  for (unsigned int i=0; i< MAX_ROW_LCD; i++)
  {
    //Наступні рядки треба перевірити, чи їх требе відображати у текучій коффігурації
    if (index_of_ekran < MAX_ROW_FOR_CHOSE_SETTING_RS485)
      for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_language][index_of_ekran][j];
    else
      for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = ' ';

    index_of_ekran++;
  }

  //Курсор по горизонталі відображається на першій позиції
  current_ekran.position_cursor_x = 0;
  //Відображення курору по вертикалі
  current_ekran.position_cursor_y = position_temp & (MAX_ROW_LCD - 1);
  //Курсор видимий
  current_ekran.cursor_on = 1;
  //Курсор не мигає
  current_ekran.cursor_blinking_on = 0;
  //Обновити повністю весь екран
  current_ekran.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/

/*****************************************************/
//Формуємо екран відображення швидкостіобміну для інтерфейсу
/*****************************************************/
void make_ekran_speed_interface()
{
  const unsigned char name_string[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_VIEW_SPEED_INTERFACE][MAX_COL_LCD] = 
  {
    " Скорость обмена",
    " Швидкість обм. ",
    "   Baud rate    ",
    " Скорость обмена"
  };
  int index_language = index_language_in_array(current_settings.language);
  
  unsigned int position_temp = current_ekran.index_position;
  unsigned int index_of_ekran;
  
  //Множення на два величини position_temp потрібне для того, бо на одну позицію ми використовуємо два рядки (назва + значення)
  index_of_ekran = ((position_temp<<1) >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;

  
  for (unsigned int i=0; i< MAX_ROW_LCD; i++)
  {
    if (index_of_ekran < (MAX_ROW_FOR_VIEW_SPEED_INTERFACE<<1))//Множення на два константи MAX_ROW_FOR_VIEW_SPEED_INTERFACE потрібне для того, бо на одну позицію ми використовуємо два рядки (назва + значення)
    {
      if ((i & 0x1) == 0)
      {
        //У непарному номері рядку виводимо заголовок
        for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_language][index_of_ekran>>1][j];
      }
      else
      {
        //У парному номері рядку виводимо значення уставки
        const unsigned char information[MAX_NUMBER_SPEEDS_INTERFACE][MAX_COL_LCD] = 
        {
          "      9600      ",
          "     14400      ",
          "     19200      ",
          "     28800      ",
          "     38400      ",
          "     57600      ",
          "     115200     "
        };
        const unsigned int cursor_x[MAX_NUMBER_SPEEDS_INTERFACE] = {5, 4, 4, 4, 4, 4, 4};

        unsigned int temp_data;
          
        if(current_ekran.edition == 0) temp_data = current_settings.speed_RS485;
        else temp_data = edition_settings.speed_RS485;
          
        if (temp_data < MAX_NUMBER_SPEEDS_INTERFACE)
        {
          for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = information[temp_data][j];
          current_ekran.position_cursor_x = cursor_x[temp_data];
        }
        else
        {
          const unsigned char information_error[MAX_NAMBER_LANGUAGE][MAX_COL_LCD] = 
          {
            "     Ошибка     ",
            "    Помилка     ",
            "     Error      ",
            "     Ошибка     "
          };
          const unsigned int cursor_x_error[MAX_NAMBER_LANGUAGE] = {4, 3, 4, 4};

          for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = information_error[index_language][j];
          current_ekran.position_cursor_x = cursor_x_error[index_language];
        }
      }
    }
    else
      for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = ' ';

    index_of_ekran++;
  }

  //Відображення курору по вертикалі і курсор завжди має бути у полі із значенням устаки
  current_ekran.position_cursor_y = ((position_temp<<1) + 1) & (MAX_ROW_LCD - 1);

  //Курсор видимий, якщо ми у режимі редагування
  if (current_ekran.edition == 0) current_ekran.cursor_on = 0;
  else current_ekran.cursor_on = 1;

  //Курсор не мигає, якщо ми у режимі редагування
  if(current_ekran.edition == 0)current_ekran.cursor_blinking_on = 0;
  else current_ekran.cursor_blinking_on = 1;

  //Обновити повністю весь екран
  current_ekran.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/

/*****************************************************/
//Формуємо екран відображення контролю парності для інтерфейсу
/*****************************************************/
void make_ekran_pare_interface()
{
  const unsigned char name_string[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_VIEW_PARE_INTERFACE][MAX_COL_LCD] = 
  {
    " Контр.четности ",
    " Контр.парності ",
    "     Parity     ",
    " Контр.четности "
  };
  int index_language = index_language_in_array(current_settings.language);
  
  unsigned int position_temp = current_ekran.index_position;
  unsigned int index_of_ekran;
  
  //Множення на два величини position_temp потрібне для того, бо на одну позицію ми використовуємо два рядки (назва + значення)
  index_of_ekran = ((position_temp<<1) >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;

  
  for (unsigned int i=0; i< MAX_ROW_LCD; i++)
  {
    if (index_of_ekran < (MAX_ROW_FOR_VIEW_PARE_INTERFACE<<1))//Множення на два константи MAX_ROW_FOR_VIEW_PARE_INTERFACE потрібне для того, бо на одну позицію ми використовуємо два рядки (назва + значення)
    {
      if ((i & 0x1) == 0)
      {
        //У непарному номері рядку виводимо заголовок
        for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_language][index_of_ekran>>1][j];
      }
      else
      {
        const unsigned char information[MAX_NAMBER_LANGUAGE][MAX_NUMBER_PARE_INTERFACE + 1][MAX_COL_LCD] = 
        {
          {"      Нет       ", "     Нечет.     ", "      Чет.      ", "     Ошибка     "},
          {"      Нема      ", "    Непарн.     ", "      Парн.     ", "    Помилка     "},
          {"      None      ", "      Odd       ", "      Even      ", "     Error      "},
          {"      Нет       ", "     Нечет.     ", "      Чет.      ", "     Ошибка     "}
        };
        const unsigned int cursor_x[MAX_NAMBER_LANGUAGE][MAX_NUMBER_PARE_INTERFACE + 1] = 
        {
          {5, 4, 5, 4},
          {5, 3, 5, 3},
          {5, 5, 5, 4},
          {5, 4, 5, 4}
        };

        unsigned int temp_data;
          
        if(current_ekran.edition == 0) temp_data = current_settings.pare_bit_RS485;
        else temp_data = edition_settings.pare_bit_RS485;

        if (temp_data < MAX_NUMBER_PARE_INTERFACE)
        {
          for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = information[index_language][temp_data][j];
          current_ekran.position_cursor_x = cursor_x[index_language][temp_data];
        }
        else
        {
          for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = information[index_language][MAX_NUMBER_PARE_INTERFACE][j];
          current_ekran.position_cursor_x = cursor_x[index_language][MAX_NUMBER_PARE_INTERFACE];
        }
      }
    }
    else
      for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = ' ';

    index_of_ekran++;
  }

  //Відображення курору по вертикалі і курсор завжди має бути у полі із значенням устаки
  current_ekran.position_cursor_y = ((position_temp<<1) + 1) & (MAX_ROW_LCD - 1);

  //Курсор видимий, якщо ми у режимі редагування
  if (current_ekran.edition == 0) current_ekran.cursor_on = 0;
  else current_ekran.cursor_on = 1;

  //Курсор не мигає, якщо ми у режимі редагування
  if(current_ekran.edition == 0)current_ekran.cursor_blinking_on = 0;
  else current_ekran.cursor_blinking_on = 1;

  //Обновити повністю весь екран
  current_ekran.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/

/*****************************************************/
//Формуємо екран відображення stop-bit для інтерфейсу
/*****************************************************/
void make_ekran_stopbits_interface()
{
  const unsigned char name_string[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_VIEW_STOP_BITS_INTERFACE][MAX_COL_LCD] = 
  {
    " Колич.стоп-бит ",
    "Кільк.стоп-біт  ",
    "   Stop Bits    ",
    " Колич.стоп-бит "
  };
  int index_language = index_language_in_array(current_settings.language);
  
  unsigned int position_temp = current_ekran.index_position;
  unsigned int index_of_ekran;
  
  //Множення на два величини position_temp потрібне для того, бо на одну позицію ми використовуємо два рядки (назва + значення)
  index_of_ekran = ((position_temp<<1) >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;

  
  for (unsigned int i=0; i< MAX_ROW_LCD; i++)
  {
    if (index_of_ekran < (MAX_ROW_FOR_VIEW_STOP_BITS_INTERFACE<<1))//Множення на два константи MAX_ROW_FOR_VIEW_STOP_BITS_INTERFACE потрібне для того, бо на одну позицію ми використовуємо два рядки (назва + значення)
    {
      if ((i & 0x1) == 0)
      {
        //У непарному номері рядку виводимо заголовок
        for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_language][index_of_ekran>>1][j];
      }
      else
      {
        const unsigned char information[MAX_NAMBER_LANGUAGE][MAX_NUMBER_STOP_BITS_INTERFACE + 1][MAX_COL_LCD] = 
        {
          {"      Один      ", "      Два       ", "     Ошибка     "},
          {"      Один      ", "      Два       ", "    Помилка     "},
          {"      One       ", "      Two       ", "     Error      "},
          {"      Один      ", "      Два       ", "     Ошибка     "}
        };
        const unsigned int cursor_x[MAX_NAMBER_LANGUAGE][MAX_NUMBER_STOP_BITS_INTERFACE + 1] = 
        {
          {5, 5, 4},
          {5, 5, 3},
          {5, 5, 4},
          {5, 5, 4}
        };

        unsigned int temp_data;
          
        if(current_ekran.edition == 0) temp_data = current_settings.number_stop_bit_RS485;
        else temp_data = edition_settings.number_stop_bit_RS485;
          
        if (temp_data < MAX_NUMBER_STOP_BITS_INTERFACE)
        {
          for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = information[index_language][temp_data][j];
          current_ekran.position_cursor_x = cursor_x[index_language][temp_data];
        }
        else
        {
          for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = information[index_language][MAX_NUMBER_STOP_BITS_INTERFACE][j];
          current_ekran.position_cursor_x = cursor_x[index_language][MAX_NUMBER_STOP_BITS_INTERFACE];
        }
      }
    }
    else
      for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = ' ';

    index_of_ekran++;
  }

  //Відображення курору по вертикалі і курсор завжди має бути у полі із значенням устаки
  current_ekran.position_cursor_y = ((position_temp<<1) + 1) & (MAX_ROW_LCD - 1);

  //Курсор видимий, якщо ми у режимі редагування
  if (current_ekran.edition == 0) current_ekran.cursor_on = 0;
  else current_ekran.cursor_on = 1;

  //Курсор не мигає, якщо ми у режимі редагування
  if(current_ekran.edition == 0)current_ekran.cursor_blinking_on = 0;
  else current_ekran.cursor_blinking_on = 1;

  //Обновити повністю весь екран
  current_ekran.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/

/*****************************************************/
//Формуємо екран відображення time-out наступного символу для інтерфейсу
/*****************************************************/
void make_ekran_timeout_interface()
{
  const unsigned char name_string[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_VIEW_TIMEOUT_INTERFACE][MAX_COL_LCD] = 
  {
    "  Конец приёма  ",
    "Кінець приймання",
    "End of Reception",
    "  Конец приёма  "
  };
  const unsigned char symbols[MAX_NAMBER_LANGUAGE][5] = {"симв.", "симв.", "symb.", "симв."};
  int index_language = index_language_in_array(current_settings.language);
  
  unsigned int position_temp = current_ekran.index_position;
  unsigned int index_of_ekran;
  unsigned int vaga, value, first_symbol;
  
  //Множення на два величини position_temp потрібне для того, бо на одну позицію ми використовуємо два рядки (назва + значення)
  index_of_ekran = ((position_temp<<1) >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;

  
  for (unsigned int i=0; i< MAX_ROW_LCD; i++)
  {
    //Наступні рядки треба перевірити, чи їх требе відображати у текучій коффігурації
    if (index_of_ekran < (MAX_ROW_FOR_VIEW_TIMEOUT_INTERFACE<<1))//Множення на два константи MAX_ROW_FOR_VIEW_TIMEOUT_INTERFACE потрібне для того, бо на одну позицію ми використовуємо два рядки (назва + значення)
    {
      if ((i & 0x1) == 0)
      {
        //У непарному номері рядку виводимо заголовок
        for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_language][index_of_ekran>>1][j];

        vaga = 100; //максимальний ваговий коефіцієнт для вилілення старшого розряду
        if (current_ekran.edition == 0) value = current_settings.time_out_1_RS485; //у змінну value поміщаємо значення time-out наступного символу 
        else value = edition_settings.time_out_1_RS485;
        first_symbol = 0; //помічаємо, що ще ніодин значущий символ не виведений
      }
      else
      {
        //У парному номері рядку виводимо значення уставки
        for (unsigned int j = 0; j<MAX_COL_LCD; j++)
        {
          if (
              ((j < COL_TIMEOUT_INTERFACE_BEGIN) ||  (j > COL_TIMEOUT_INTERFACE_END )) &&
              (
               !((j >= (COL_TIMEOUT_INTERFACE_END + 2)) && (j <= (COL_TIMEOUT_INTERFACE_END + 6)))
              )    
             )working_ekran[i][j] = ' ';
          else if (j == COL_TIMEOUT_INTERFACE_COMMA )working_ekran[i][j] = ',';
          else if ((j >= (COL_TIMEOUT_INTERFACE_END + 2)) && (j <= (COL_TIMEOUT_INTERFACE_END + 6)))
            working_ekran[i][j] = symbols[index_language][j - (COL_TIMEOUT_INTERFACE_END + 2)];
          else
            calc_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol, j, COL_TIMEOUT_INTERFACE_COMMA, 0);
        }
      }
        
    }
    else
      for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = ' ';

    index_of_ekran++;
  }

  //Відображення курору по вертикалі і курсор завжди має бути у полі із значенням устаки
  current_ekran.position_cursor_y = ((position_temp<<1) + 1) & (MAX_ROW_LCD - 1);
  //Курсор по горизонталі відображається на першому символі у випадку, коли ми не в режимі редагування, інакше позиція буде визначена у функцї main_manu_function
  if (current_ekran.edition == 0)
  {
    current_ekran.position_cursor_x = COL_TIMEOUT_INTERFACE_BEGIN;
    int last_position_cursor_x = COL_TIMEOUT_INTERFACE_END;
    
    //Підтягуємо курсор до першого символу
    while (((working_ekran[current_ekran.position_cursor_y][current_ekran.position_cursor_x + 1]) == ' ') && 
           (current_ekran.position_cursor_x < (last_position_cursor_x -1))) current_ekran.position_cursor_x++;

    //Курсор ставимо так, щоб він був перед числом
    if (((working_ekran[current_ekran.position_cursor_y][current_ekran.position_cursor_x]) != ' ') && 
        (current_ekran.position_cursor_x > 0)) current_ekran.position_cursor_x--;
  }
  //Курсор видимий, якщо ми у режимі редагування
  if (current_ekran.edition == 0) current_ekran.cursor_on = 0;
  else current_ekran.cursor_on = 1;

  //Курсор не мигає
  if(current_ekran.edition == 0)current_ekran.cursor_blinking_on = 0;
  else current_ekran.cursor_blinking_on = 1;
  //Обновити повністю весь екран
  current_ekran.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/

/*****************************************************/
//
/*****************************************************/
/*****************************************************/
