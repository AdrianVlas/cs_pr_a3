#ifndef __CONST_GROUP_ALARMS_MENU2__
#define __CONST_GROUP_ALARMS_MENU2__

#define COL_PICKUP_GROUP_ALARM_DELTA_I_BEGIN             4
#define COL_PICKUP_GROUP_ALARM_DELTA_I_COMMA             5
#define COL_PICKUP_GROUP_ALARM_DELTA_I_END               8

#define COL_DELAY_GROUP_ALARM_DELAY_BEGIN                6
#define COL_DELAY_GROUP_ALARM_DELAY_COMMA                8
#define COL_DELAY_GROUP_ALARM_DELAY_END                  9

#define MASKA_CTRL_GROUP_ALARM_M2 ((1 << _MAX_INDEX_CTRL_GROUP_ALARM_BITS_SETTINGS) - 1)

#define NAME_GROUP_ALARM_OUT_SIGNALS_RU \
  "Увелич.         ",                   \
  "Уменш.          ",                   \
  "Выход           ",                   \
  "Ош.контроля     ",                   \
  "Прев.тока       "

#define NAME_GROUP_ALARM_OUT_SIGNALS_UA \
  "Збільш.         ",                   \
  "Зменш.          ",                   \
  "Вихід           ",                   \
  "Пом.контролю    ",                   \
  "Перев.стр.     "

#define NAME_GROUP_ALARM_OUT_SIGNALS_EN \
  "Inc.            ",                   \
  "Dec.            ",                   \
  "Output          ",                   \
  "Ch.Err.         ",                   \
  "OC              "

#define NAME_GROUP_ALARM_OUT_SIGNALS_KZ \
  "Увелич.         ",                   \
  "Уменш.          ",                   \
  "Выход           ",                   \
  "Ош.контроля     ",                   \
  "Прев.тока       "

//const uint8_t name_string_group_alarm[MAX_NAMBER_LANGUAGE][MAX_INDEX_CTRL_GROUP_ALARM][MAX_COL_LCD + 1] = 
//{
//  {
//    "   Состояние    ",
//    "  Контроль ШГС  ",
//    "      Ток       "
//  },
//  {
//    "      Стан      ",
//    "  Контроль ШГС  ",
//    "     Струм      "
//  },
//  {
//    "      Стан      ",
//    "  Контроль ШГС  ",
//    "    Current     "
//  },
//  {
//     "   Состояние    ",
//     "  Контроль ШГС  ",
//     "      Ток       "
//   }
//};
//
//const uint8_t name_string_group_alarm_pickup[MAX_NAMBER_LANGUAGE][GROUP_ALARM_PICKUPS][MAX_COL_LCD + 1] = 
//{
//  {
//    "       ‰I       "
//  },
//  {
//    "       ‰I       "
//  },
//  {
//    "       ‰I       "
//  },
//  {
//    "       ‰I       "
//  }
//};
//
//const uint8_t name_string_group_alarm_delay[MAX_NAMBER_LANGUAGE][GROUP_ALARM_SET_DELAYS][MAX_COL_LCD + 1] = 
//{
//  {
//    "   T Задержки   ",
//  },
//  {
//    "   T Затримки   ",
//  },
//  {
//    "   T Задержки   ",
//  },
//  {
//    "   T Задержки   ",
//  }
//};
//
//    
//const uint8_t name_group_alarm_out_signals[MAX_NAMBER_LANGUAGE][GROUP_ALARM_SIGNALS_OUT][MAX_COL_LCD + 1] =
//{
//  {NAME_GROUP_ALARM_OUT_SIGNALS_RU},  
//  {NAME_GROUP_ALARM_OUT_SIGNALS_UA},  
//  {NAME_GROUP_ALARM_OUT_SIGNALS_EN},  
//  {NAME_GROUP_ALARM_OUT_SIGNALS_KZ}
//};
//
//const uint8_t name_group_alarm[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
//{
//  " ШГС            ",
//  " ШГС            ",
//  " Gr.Alarm       ",
//  " ШГС            "
//};
//const unsigned int first_index_number_group_alarm[MAX_NAMBER_LANGUAGE] = {4, 4, 9, 4};

#endif 

//extern const uint8_t name_string_group_alarm[MAX_NAMBER_LANGUAGE][MAX_INDEX_CTRL_GROUP_ALARM][MAX_COL_LCD + 1];
//extern const uint8_t name_string_group_alarm_pickup[MAX_NAMBER_LANGUAGE][GROUP_ALARM_PICKUPS][MAX_COL_LCD + 1];
//extern const uint8_t name_string_group_alarm_delay[MAX_NAMBER_LANGUAGE][GROUP_ALARM_SET_DELAYS][MAX_COL_LCD + 1];
//extern const uint8_t name_group_alarm_out_signals[MAX_NAMBER_LANGUAGE][GROUP_ALARM_SIGNALS_OUT][MAX_COL_LCD + 1];
//extern const uint8_t name_group_alarm[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1];
//extern const unsigned int first_index_number_group_alarm[MAX_NAMBER_LANGUAGE];

