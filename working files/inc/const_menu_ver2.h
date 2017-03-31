#ifndef __CONST_MENU_VER2__
#define __CONST_MENU_VER2__

enum _edition_stats
{
  ED_VIEWING = 0,               /* 0 - вікно зараз не в режимі редагується  */
  ED_CAN_BE_EDITED,             /* 1 - вікно зараз не в режимі редагується але з правом переходу в режим редагування без додаткої перевірки паролю  */
  ED_EDITION,                   /* 2 - вікно зараз в режимі редагування  */
  ED_CONFIRM_CHANGES,           /* 3 - вікно чекає підтвердження редагування  */ 
  ED_WARNING_EDITION_BUSY,      /* 4 - у процесі виконання виникнула помилка  про неможливість переходу у режим редагування (виводиться вікно про помилку з єдиною кнопкою Enter функцією make_ekran_about_info. По натискуванні Enter залишаємося у тому самому вікні)*/
  ED_WARNING_ENTER_ESC,         /* 5 - у процесі виконання виникнула помилка  (виводиться вікно про помилку з двома Enter/Esc кнопками функцією make_ekran_about_info. По натискуванні Enter залишаємося у тому самому вікні)*/
  ED_WARNING_ENTER,             /* 6 - у процесі виконання виникнула помилка  (виводиться вікно про помилку з єдиною кнопкою Enter функцією make_ekran_about_info. По натискуванні Enter залишаємося у тому самому вікні)*/
  ED_INFO,                      /* 7 - у процесі виконання виникнуло необхідність проінформувати на екрані певне повідомлення  (виводиться вікно інформації з єдиною кнопкою Enter функцією make_ekran_about_info) По натискуванні Enter повертаємося у попереднє вікно*/
  ED_ERROR                      /* 8 - у процесі виконання виникнула критична помилка  (виводимо інформацію без будь-якої можливості натиснути будь-яку кнопку)*/
};

enum _result_pressed_enter_during_edition
{
  RPEDE_NONE = 0,
  RPEDE_DATA_NOT_CHANGED,
  RPEDE_DATA_CHANGED_OK,
  RPEDE_DATA_CHANGED_OUT_OF_RANGE,
  RPEDE_DATA_CHANGED_WRONG_RETURN_OK,
  RPEDE_DATA_CHANGED_WRONG_RETURN_BAD
};

enum _menu2_levels
{
  MAIN_MANU2_LEVEL = 0,
    TIME_MANU2_LEVEL,
    MEASUREMENT_MENU2_LEVEL,
    INPUTS_OUTPUTS_MENU2_LEVEL,
      INPUTS_MENU2_LEVEL,
      OUTPUTS_MENU2_LEVEL,
    REGISTRATORS_MENU2_LEVEL,
    
    __BEGIN_SETTINGS_MENU2_LEVEL,
    
    LIST_SETTINGS_MENU2_LEVEL = __BEGIN_SETTINGS_MENU2_LEVEL,
      CONFIGURATION_MENU2_LEVEL,
      LIST_SETTINGS_PARAM_MENU2_LEVEL,
        LIST_INPUTS_MENU2_LEVEL,
          LIST_SETTINGS_INPUT_MENU2_LEVEL,
            DELAY_INPUT_MENU2_LEVEL,
            CTRL_INPUT_MENU2_LEVEL,
        LIST_OUTPUTS_MENU2_LEVEL,
          LIST_SETTINGS_OUTPUT_MENU2_LEVEL,
            CTRL_OUTPUT_MENU2_LEVEL,
        LIST_LEDS_MENU2_LEVEL,
          LIST_SETTINGS_LED_MENU2_LEVEL,
            CTRL_LED_MENU2_LEVEL,
        LIST_ALARMS_MENU2_LEVEL,
          LIST_SETTINGS_ALARM_MENU2_LEVEL,
            DELAY_ALARM_MENU2_LEVEL,
            CTRL_ALARM_MENU2_LEVEL,
        LIST_GROUP_ALARMS_MENU2_LEVEL,
          LIST_SETTINGS_GROUP_ALARM_MENU2_LEVEL,
            PICKUP_GROUP_ALARM_MENU2_LEVEL,
            DELAY_GROUP_ALARM_MENU2_LEVEL,
            CTRL_GROUP_ALARM_MENU2_LEVEL,
        LIST_TIMERS_MENU2_LEVEL,
          LIST_SETTINGS_TIMER_MENU2_LEVEL,
            DELAY_TIMER_MENU2_LEVEL,
        LIST_MEANDERS_MENU2_LEVEL,
          LIST_SETTINGS_MEANDER_MENU2_LEVEL,
            DELAY_MEANDER_MENU2_LEVEL,
      EDITOR_LIST_LOGICAL_NODES_FOR_INPUT_MENU2_LEVEL,
      
        __BEGIN_EDITOR_LIST_SELECTED_TYPE_LOGICAL_NODE_FOR_INPUT_MENU2_LEVEL,
        EDITOR_LIST_INPUTS_FOR_INPUT_MENU2_LEVEL = __BEGIN_EDITOR_LIST_SELECTED_TYPE_LOGICAL_NODE_FOR_INPUT_MENU2_LEVEL,
        EDITOR_LIST_OUTPUTS_FOR_INPUT_MENU2_LEVEL,
        EDITOR_LIST_LEDS_FOR_INPUT_MENU2_LEVEL,
        EDITOR_LIST_BUTTONS_FOR_INPUT_MENU2_LEVEL,
        EDITOR_LIST_ALARMS_FOR_INPUT_MENU2_LEVEL,
        EDITOR_LIST_GROUP_ALARMS_FOR_INPUT_MENU2_LEVEL,
        EDITOR_LIST_ANDS_FOR_INPUT_MENU2_LEVEL,
        EDITOR_LIST_ORS_FOR_INPUT_MENU2_LEVEL,
        EDITOR_LIST_XORS_FOR_INPUT_MENU2_LEVEL,
        EDITOR_LIST_NOTS_FOR_INPUT_MENU2_LEVEL,
        EDITOR_LIST_TIMERS_FOR_INPUT_MENU2_LEVEL,
        EDITOR_LIST_TRIGGERS_FOR_INPUT_MENU2_LEVEL,
        EDITOR_LIST_MEANDERS_FOR_INPUT_MENU2_LEVEL,
        EDITOR_LIST_TUS_FOR_INPUT_MENU2_LEVEL,
        __NEXT_AFTER_EDITOR_LIST_SELECTED_TYPE_LOGICAL_NODE_FOR_INPUT_MENU2_LEVEL,
        
          EDITOR_LIST_INPUTS_OF_SELECTED_LOGICAL_NODE_MENU2_LEVEL = __NEXT_AFTER_EDITOR_LIST_SELECTED_TYPE_LOGICAL_NODE_FOR_INPUT_MENU2_LEVEL,
            EDITOR_VIEW_CHOSEN_SIGNAL_OF_SELECTED_LOGICAL_NODE_MENU2_LEVEL,
              EDITOR_LIST_LOGICAL_NODES_FOR_OUTPUT_MENU2_LEVEL,
      
                __BEGIN_EDITOR_LIST_SELECTED_TYPE_LOGICAL_NODE_FOR_OUTPUT_MENU2_LEVEL,
                EDITOR_LIST_INPUTS_FOR_OUTPUT_MENU2_LEVEL = __BEGIN_EDITOR_LIST_SELECTED_TYPE_LOGICAL_NODE_FOR_OUTPUT_MENU2_LEVEL,
                EDITOR_LIST_OUTPUTS_FOR_OUTPUT_MENU2_LEVEL,
                EDITOR_LIST_LEDS_FOR_OUTPUT_MENU2_LEVEL,
                EDITOR_LIST_BUTTONS_FOR_OUTPUT_MENU2_LEVEL,
                EDITOR_LIST_ALARMS_FOR_OUTPUT_MENU2_LEVEL,
                EDITOR_LIST_GROUP_ALARMS_FOR_OUTPUT_MENU2_LEVEL,
                EDITOR_LIST_ANDS_FOR_OUTPUT_MENU2_LEVEL,
                EDITOR_LIST_ORS_FOR_OUTPUT_MENU2_LEVEL,
                EDITOR_LIST_XORS_FOR_OUTPUT_MENU2_LEVEL,
                EDITOR_LIST_NOTS_FOR_OUTPUT_MENU2_LEVEL,
                EDITOR_LIST_TIMERS_FOR_OUTPUT_MENU2_LEVEL,
                EDITOR_LIST_TRIGGERS_FOR_OUTPUT_MENU2_LEVEL,
                EDITOR_LIST_MEANDERS_FOR_OUTPUT_MENU2_LEVEL,
                EDITOR_LIST_TUS_FOR_OUTPUT_MENU2_LEVEL,
                __NEXT_AFTER_EDITOR_LIST_SELECTED_TYPE_LOGICAL_NODE_FOR_OUTPUT_MENU2_LEVEL,
        
                  EDITOR_LIST_OUTPUTS_OF_SELECTED_LOGICAL_NODE_MENU2_LEVEL = __NEXT_AFTER_EDITOR_LIST_SELECTED_TYPE_LOGICAL_NODE_FOR_OUTPUT_MENU2_LEVEL,
        
      LANGUAGE_MENU2_LEVEL,
      LIST_SETTINGS_COMMUNIACATION_PARAMETERS_MENU2_LEVEL,
        NAME_OF_CELL_MENU2_LEVEL,
        ADDRESS_MENU2_LEVEL,
        SETTINGS_RS485_MENU2_LEVEL,
          BAUD_RS485_MENU2_LEVEL,
          PARE_RS485_MENU2_LEVEL,
          STOP_BITS_RS485_MENU2_LEVEL,
          TIMEOUT_RS485_MENU2_LEVEL,
      LIST_PASSWORDS_MENU2_LEVEL,
        SET_NEW_PASSWORD_MENU2_LEVEL,
    
    __NEXT_AFTER_SETTINGS_MENU2_LEVEL,
    
    DIAGNOSTICS_MENU2_LEVEL = __NEXT_AFTER_SETTINGS_MENU2_LEVEL,
    LABELS_MENU2_LEVEL,
      CONFIG_LABEL_MENU2_LEVEL,
      SETTINGS_LABEL_MENU2_LEVEL,
    INFO_MENU2_LEVEL,
      DATE_TIME_INFO_MENU2_LEVEL,
    
  PASSWORD_MENU2_LEVEL,
  
  MAX_NUMBER_MENU2_LEVEL
};

#endif
