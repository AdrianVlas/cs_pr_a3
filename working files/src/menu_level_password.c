#include "header.h"

/*****************************************************/
//Формуємо екран паролю
/*****************************************************/
void make_ekran_password(void)
{
  //Визначаємо з яким масивом будемо працювати
  const uint8_t (*point_to_working_array)[MAX_COL_LCD + 1];
  if (current_state_menu2.current_level == SET_NEW_PASSWORD_MENU2_LEVEL)
    point_to_working_array = name_string_level_password_2;
  else
    point_to_working_array = name_string_level_password_1;

  uint8_t name_string_tmp[MAX_ROW_FOR_LEVEL_PASSWORD][MAX_COL_LCD + 1];

  int index_language = index_language_in_array(select_struct_settings_fix()->language);
  
  for(size_t index_1 = 0; index_1 < MAX_ROW_FOR_LEVEL_PASSWORD; index_1++)
  {
    for(size_t index_2 = 0; index_2 < (MAX_COL_LCD + 1); index_2++)
    {
      name_string_tmp[index_1][index_2] = (index_1 == INDEX_PASSWORD_M2_LINE1) ? point_to_working_array[index_language][index_2] : ' ';
    }
  }
  
  unsigned int password = *((unsigned int*)p_menu_param_1);
  if (*((unsigned int*)p_menu_param_2) != 0)
  {
    unsigned int position_cursor = COL_NEW_PASSWORD_BEGIN;
    if (password != 0)
    {
      unsigned int temp_value[MAX_NUMBER_OF_SYMPOLS_IN_PASSWORD];
      unsigned int password_tmp = (unsigned int)password;

      for (intptr_t i = (MAX_NUMBER_OF_SYMPOLS_IN_PASSWORD - 1); i >= 0; i--)
      {
        temp_value[i] = password_tmp % 10;
        password_tmp /= 10;
      }

      for (size_t i = 0; i < MAX_NUMBER_OF_SYMPOLS_IN_PASSWORD; i++)
      {
        if(temp_value[i] != 0) name_string_tmp[INDEX_PASSWORD_M2_LINE2][position_cursor++] = temp_value[i] + 0x30;
      }
    }
    else
    {
      name_string_tmp[INDEX_PASSWORD_M2_LINE2][position_cursor++] = (current_state_menu2.current_level == SET_NEW_PASSWORD_MENU2_LEVEL) ? '0' : '?';
    }
  }

  //Копіюємо  рядки у робочий екран
  for (unsigned int i=0; i< MAX_ROW_LCD; i++)
  {
    for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string_tmp[i][j];
  }
  
  //Відображення курору по вертикалі
  current_state_menu2.position_cursor_y = 1;
  //Курсор видимий
  current_state_menu2.cursor_on = 1;
  //Курсор мигає
  current_state_menu2.cursor_blinking_on = 1;
  //Обновити повністю весь екран
  current_state_menu2.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/

/*****************************************************/
//Формуємо екран відображення заголовків паролів
/*****************************************************/
void make_ekran_choose_passwords(void)
{
  if (current_state_menu2.edition == ED_WARNING_EDITION_BUSY)
  {
    make_ekran_about_info(0, information_no_edition);
  }
  else
  {
    int index_language = index_language_in_array(select_struct_settings_fix()->language);
  
    unsigned int position_temp = current_state_menu2.index_position;
    unsigned int index_in_ekran = (position_temp >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;

    __SETTINGS_FIX *p_settings_fix;
    p_settings_fix = (current_state_menu2.edition == ED_VIEWING) ? &settings_fix_prt : &settings_fix;
    
    //Копіюємо  рядки у робочий екран
    for (size_t i = 0; i < MAX_ROW_LCD; i++)
    {
      if (index_in_ekran < MAX_ROW_LIST_PASSWORDS_M2)
      {
        unsigned int password;
        if (index_in_ekran == INDEX_LIST_PASSWORDS_M2_1)
          password = p_settings_fix->password_1;
        else
          password = p_settings_fix->password_2;
      
        unsigned int index_of_information = ( password != 0) ? 0 : 1;
        for (size_t j = 0; j < MAX_COL_LCD; j++) working_ekran[i][j] = password_item_level_password[index_in_ekran][index_language][index_of_information][j];
      } 
      else
        for (size_t j = 0; j < MAX_COL_LCD; j++) working_ekran[i][j] = ' ';

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
  }
  //Обновити повністю весь екран
  current_state_menu2.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/

/*****************************************************/
// 
/*****************************************************/
/*****************************************************/

