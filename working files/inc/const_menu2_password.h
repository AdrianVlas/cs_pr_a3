#ifndef __CONST_PASSWORDS_MENU2__
#define __CONST_PASSWORDS_MENU2__

enum __index_password_m2
{
  INDEX_PASSWORD_M2_LINE1 = 0,
  INDEX_PASSWORD_M2_LINE2,

  MAX_ROW_PASSWORD_M2
};

#define MAX_ROW_FOR_LEVEL_PASSWORD    2

#define MAX_VALUE_DIGIT_PASSWORD        4

#define MAX_NUMBER_OF_SYMPOLS_IN_PASSWORD       4
#define COL_NEW_PASSWORD_BEGIN                  5
#define COL_NEW_PASSWORD_END                    (COL_NEW_PASSWORD_BEGIN + MAX_NUMBER_OF_SYMPOLS_IN_PASSWORD - 1)

enum __index_list_passwords_m2
{
  INDEX_LIST_PASSWORDS_M2_1 = 0,
  INDEX_LIST_PASSWORDS_M2_2,

  MAX_ROW_LIST_PASSWORDS_M2
};

//const uint8_t name_string_level_password_1[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
//{
//  " Введите пароль:",
//  " Введіть пароль:",
//  " Enter password:",
//  " Введите пароль:"
//};
//
//const uint8_t name_string_level_password_2[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
//{
//  "  Новый пароль: ",
//  "  Новий пароль: ",
//  "  New password: ",
//  "  Новый пароль: "
//};
//
//const uint8_t password_item_level_password[MAX_ROW_LIST_PASSWORDS_M2][MAX_NAMBER_LANGUAGE][2][MAX_COL_LCD + 1] = 
//{
//  {
//    {" Смена пароля 1 ", " Уст.пароля 1   "},
//    {" Зміна паролю 1 ", " Вст.паролю 1   "},
//    {" Pass.1 Change  ", " Password 1 Set "},
//    {" Смена пароля 1 ", " Уст.пароля 1   "}
//  },
//  {
//    {" Смена пароля 2 ", " Уст.пароля 2   "},
//    {" Зміна паролю 2 ", " Вст.паролю 2   "},
//    {" Pass.2 Change  ", " Password 2 Set "},
//    {" Смена пароля 2 ", " Уст.пароля 2   "}
//  },
//};

#endif

//extern const uint8_t name_string_level_password_1[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1];
//extern const uint8_t name_string_level_password_2[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1];
//extern const uint8_t password_item_level_password[MAX_ROW_LIST_PASSWORDS_M2][MAX_NAMBER_LANGUAGE][2][MAX_COL_LCD + 1];
