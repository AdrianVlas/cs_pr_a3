#ifndef __CONST_LCD_AND_KEYBOARD__
#define __CONST_LCD_AND_KEYBOARD__

#define MAX_TIME_REWRITE_EKRAN  100 //x10 - ������������ ��� � �� ��� ������������� ���������� ������� ����, �� ����� ���������

#define MAX_NYMBER_EXTENDED_ASCII_SYMBOLS        69
#define MAX_NYMBER_EXTRA_EXTENDED_ASCII_SYMBOLS  13

#define LCD_BASE          Bank1_SRAM3_ADDR

#define POWER_MAX_COL_LCD       4
#define POWER_MAX_ROW_LCD       1
#define MAX_COL_LCD       (1<<POWER_MAX_COL_LCD)
#define MAX_ROW_LCD       (1<<POWER_MAX_ROW_LCD)

#define BF_BIT            7

#define NUMBER_KEY_KEYBOARD (4*3)
#define DEREVIACIA          8

enum _bit_key
{
  BIT_KEY_ENTER = 0,
  BIT_KEY_DOWN,
  BIT_KEY_RIGHT,
  BIT_KEY_ESC,
  BIT_KEY_LEFT,
  BIT_KEY_UP,
  
  _NUMBER_MOVING_KEY,
  
  BIT_KEY_MUTE = FIX_BUTTON_MUTE + _NUMBER_MOVING_KEY,
  BIT_KEY_RESET = FIX_BUTTON_RESET + _NUMBER_MOVING_KEY,
  BIT_KEY_TEST = FIX_BUTTON_TEST + _NUMBER_MOVING_KEY,
  BIT_KEY_1 = NUMBER_FIX_BUTTONS + _NUMBER_MOVING_KEY,
  BIT_KEY_2,

  BIT_REWRITE = 30
};

#define ACTION_WITH_CARRENT_EKRANE_NONE                      0
#define ACTION_WITH_CARRENT_EKRANE_ONLY_CHANGE_CURSOR        1
#define ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE   2


#define MAX_TIMEOUT_WAITING_REQUESTED_DATA    50000 // 500 ��, ���� ���������, �� ҲM4 ����� � ������� 10 ���

#endif
