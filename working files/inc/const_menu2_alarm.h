#ifndef __CONST_ALARMS_MENU2__
#define __CONST_ALARMS_MENU2__

#define COL_DELAY_ALARM_PERIOD_BEGIN                6
#define COL_DELAY_ALARM_PERIOD_COMMA                8
#define COL_DELAY_ALARM_PERIOD_END                  9

#define MASKA_CTRL_ALARM_M2  ((1 << (alarm_ctrl_patten[MAX_INDEX_CTRL_ALARM - 1][0] + alarm_ctrl_patten[MAX_INDEX_CTRL_ALARM - 1][1])) - 1)

#define NAME_ALARM_IN_SIGNALS_RU        \
  "�.��.           ",                   \
  "������          ",                   \
  "����.           ",                   \
  "�����           "                    

#define NAME_ALARM_IN_SIGNALS_UA        \
  "�.��.           ",                   \
  "����            ",                   \
  "����.           ",                   \
  "����.           "                    


#define NAME_ALARM_IN_SIGNALS_EN        \
  "L.In.            ",                  \
  "Mute             ",                  \
  "Block            ",                  \
  "Reset            "                    

#define NAME_ALARM_IN_SIGNALS_KZ        \
  "�.��.           ",                   \
  "������          ",                   \
  "����.           ",                   \
  "�����           "                    

    
#define NAME_ALARM_OUT_SIGNALS_RU       \
  "�������         ",                   \
  "������          "

#define NAME_ALARM_OUT_SIGNALS_UA       \
  "�������         ",                   \
  "����            "

#define NAME_ALARM_OUT_SIGNALS_EN       \
  "Alarm            ",                  \
  "Mute             "

#define NAME_ALARM_OUT_SIGNALS_KZ       \
  "�������         ",                   \
  "������          "
    
#endif 
