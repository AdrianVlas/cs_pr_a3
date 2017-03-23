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



#endif
