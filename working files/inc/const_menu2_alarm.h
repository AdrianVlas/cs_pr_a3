#ifndef __CONST_ALARMS_MENU2__
#define __CONST_ALARMS_MENU2__

#define COL_DELAY_ALARM_PERIOD_BEGIN                6
#define COL_DELAY_ALARM_PERIOD_COMMA                8
#define COL_DELAY_ALARM_PERIOD_END                  9

#define MASKA_CTRL_ALARM_M2  ((1 << (alarm_ctrl_patten[MAX_INDEX_CTRL_ALARM - 1][0] + alarm_ctrl_patten[MAX_INDEX_CTRL_ALARM - 1][1])) - 1)

#define NAME_ALARM_IN_SIGNALS_RU        \
  "Ë.Âõ.           ",                   \
  "Òèøèíà          ",                   \
  "Áëîê.           ",                   \
  "Ñáðîñ           "                    

#define NAME_ALARM_IN_SIGNALS_UA        \
  "Ë.Âõ.           ",                   \
  "Òèøà            ",                   \
  "Áëîê.           ",                   \
  "Ñêèä.           "                    


#define NAME_ALARM_IN_SIGNALS_EN        \
  "L.In.           ",                  \
  "Mute            ",                  \
  "Block           ",                  \
  "Reset           "                    

#define NAME_ALARM_IN_SIGNALS_KZ        \
  "Ë.Âõ.           ",                   \
  "Òèøèíà          ",                   \
  "Áëîê.           ",                   \
  "Ñáðîñ           "                    

    
#define NAME_ALARM_OUT_SIGNALS_RU       \
  "Òðèâîãà         ",                   \
  "Òèøèíà          "

#define NAME_ALARM_OUT_SIGNALS_UA       \
  "Òðèâîãà         ",                   \
  "Òèøà            "

#define NAME_ALARM_OUT_SIGNALS_EN       \
  "Alarm           ",                  \
  "Mute            "

#define NAME_ALARM_OUT_SIGNALS_KZ       \
  "Òðèâîãà         ",                   \
  "Òèøèíà          "

//const uint8_t name_string_alarm_delay[MAX_NAMBER_LANGUAGE][ALARM_SET_DELAYS][MAX_COL_LCD + 1] = 
//{
//  {
//    "     Ïåðèîä     "
//  },
//  {
//    "     Ïåð³îä     "
//  },
//  {
//    "     Period     "
//  },
//  {
//    "     Ïåðèîä     "
//  }
//};
//    
//const uint8_t name_string_alarm_control[MAX_NAMBER_LANGUAGE][MAX_INDEX_CTRL_ALARM][MAX_COL_LCD + 1] = 
//{
//  {
//    "     Ðåæèì      "
//  },
//  {
//    "     Ðåæèì      "
//  },
//  {
//    "      Mode      "
//  },
//  {
//    "     Ðåæèì      "
//  }
//};
//
//const uint8_t information_alarm_control[MAX_NAMBER_LANGUAGE][ALARM_MODES_NUMBER][MAX_COL_LCD + 1] = 
//{
//  {"    ÏÐÎÑÒÎÉ     ", "   ÒÐÈÃÃÅÍÛÉ    ", "    ÇÀÄ.ÂÐ.     "},
//  {"    ÏÐÎÑÒÈÉ     ", "    ÒÐÈ¥ÅÍÛÉ    ", "    ÇÀÄ.×ÀÑ     "},
//  {"     SIMPLE     ", "    TRIGGER     ", "    ÇÀÄ.ÂÐ.     "},
//  {"    ÏÐÎÑÒÈÉ     ", "   ÒÐÈÃÃÅÍÛÉ    ", "    ÇÀÄ.ÂÐ.     "}
//};
//const unsigned int cursor_x_alarm_control[MAX_NAMBER_LANGUAGE][ALARM_MODES_NUMBER] = 
//{
//  {3, 2, 3},
//  {3, 3, 3},
//  {4, 3, 3},
//  {3, 2, 3}
//};
//
//const uint8_t name_alarm_in_signals[MAX_NAMBER_LANGUAGE][ALARM_SIGNALS_IN][MAX_COL_LCD + 1] =
//{
//  {NAME_ALARM_IN_SIGNALS_RU},  
//  {NAME_ALARM_IN_SIGNALS_UA},  
//  {NAME_ALARM_IN_SIGNALS_EN},  
//  {NAME_ALARM_IN_SIGNALS_KZ}
//};
//
//const uint8_t name_alarm_out_signals[MAX_NAMBER_LANGUAGE][ALARM_SIGNALS_OUT][MAX_COL_LCD + 1] =
//{
//  {NAME_ALARM_OUT_SIGNALS_RU},  
//  {NAME_ALARM_OUT_SIGNALS_UA},  
//  {NAME_ALARM_OUT_SIGNALS_EN},  
//  {NAME_ALARM_OUT_SIGNALS_KZ}
//};
//
//const uint8_t name_alarm[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
//{
//  " ÑÇÑ            ",
//  " ÑÇÑ            ",
//  " Alarm          ",
//  " ÑÇÑ            "
//};
//const unsigned int first_index_number_alarm[MAX_NAMBER_LANGUAGE] = {4, 4, 6, 4};
//    
#endif 

//extern const uint8_t name_string_alarm_delay[MAX_NAMBER_LANGUAGE][ALARM_SET_DELAYS][MAX_COL_LCD + 1];
//extern const uint8_t name_string_alarm_control[MAX_NAMBER_LANGUAGE][MAX_INDEX_CTRL_ALARM][MAX_COL_LCD + 1];
//extern const uint8_t information_alarm_control[MAX_NAMBER_LANGUAGE][ALARM_MODES_NUMBER][MAX_COL_LCD + 1];
//extern const unsigned int cursor_x_alarm_control[MAX_NAMBER_LANGUAGE][ALARM_MODES_NUMBER];
//extern const uint8_t name_alarm_in_signals[MAX_NAMBER_LANGUAGE][ALARM_SIGNALS_IN][MAX_COL_LCD + 1];
//extern const uint8_t name_alarm_out_signals[MAX_NAMBER_LANGUAGE][ALARM_SIGNALS_OUT][MAX_COL_LCD + 1];
//extern const uint8_t name_alarm[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1];
//extern const unsigned int first_index_number_alarm[MAX_NAMBER_LANGUAGE];

