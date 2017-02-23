#ifndef __CONST_MENU_CHOSE_SETTING_PROTECTION__
#define __CONST_MENU_CHOSE_SETTING_PROTECTION__

#define EKRAN_CHOOSE_SETTINGS_CTRL_PHASE                (EKRAN_MEASURMENT_CURRENT + 1)

#define MAX_ROW_FOR_CHOSE_SETTINGS_ANY_PROTECTION                    3
#define MAX_ROW_FOR_CHOSE_SETTINGS_PROTECTION_WITH_CONTROL           1
#define MAX_ROW_FOR_CHOSE_SETTINGS_PROTECTION_WITH_TIMEOUT           1
#define MAX_ROW_FOR_CHOSE_SETTINGS_PROTECTION_WITH_SETPOINTS_CONTROL 2

//Це є основні позиції
#define INDEX_ML_SETPOINT                                 0
#define INDEX_ML_TIMEOUT                                  1
#define INDEX_ML_CONTROL                                  2

//Це є додаткові позиції, якщо вони не співпадають з основними
#define INDEX_ML_WITH_CONTROL_CONTROL                     0
#define INDEX_ML_WITH_TIMEOUT_TIMEOUT                     0
#define INDEX_ML_WITH_SETPOINT_CONTROL_SETPOINT           0
#define INDEX_ML_WITH_SETPOINT_CONTROL_CONTROL            1


#endif
