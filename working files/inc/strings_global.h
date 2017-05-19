#ifndef __STRINGS_VARIABLES_H
#define __STRINGS_VARIABLES_H

const uint8_t information_no_edition[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
{
  "Ред.не разрешено",
  "Ред.не дозволене",
  "Ed.isn't allowed",
  "Ред.не разрешено",
};

const uint8_t information_out_of_limits[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
{
  " Вых.за диапазон",
  " Вих.за діапазон",
  "  Out of Limits ",
  "Вых.за диапазон "
};

const uint8_t information_error[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
{
  "     Ошибка     ",
  "    Помилка     ",
  "     Error      ",
  "     Ошибка     "
};
const uint32_t cursor_x_error[MAX_NAMBER_LANGUAGE] = {4, 3, 4, 4};

const uint8_t information_no_free_dyn_mem[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
{
  " Дин.пам.недост.",
  " Дин.пам.недост.",
  " Дин.пам.недост.",
  " Дин.пам.недост."
};

const uint8_t information_on_off[MAX_NAMBER_LANGUAGE][2][MAX_COL_LCD + 1] = 
{
  {"     Откл.      ", "      Вкл.      "},
  {"     Вимк.      ", "     Ввімк.     "},
  {"      Off       ", "       On       "},
  {"     Сљнд.      ", "     Косу.      "}
};
const uint32_t cursor_x_on_off[MAX_NAMBER_LANGUAGE][2] = 
{
  {4, 5},
  {4, 4},
  {5, 6},
  {4, 4}
};

const uint8_t information_request[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
{
  "  Принять изм.  ",
  " Прийняти зміни ",
  "  Apply changes ",
  "  Принять изм.  "
};

const uint8_t information_about_info_1[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
{
  " Прев.кол.сигн. ",
  " Переб.кільк.с. ",
  " Max.n.of S.Exc.",
  " Прев.кол.сигн. "
};

const uint8_t information_empty[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
{
  "     Пусто      ",
  "     Пусто      ",
  "     Empty      ",
  "     Пусто      "
};
const uint32_t cursor_x_empty[MAX_NAMBER_LANGUAGE] = {4, 4, 4, 4};

const uint8_t information_none[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
{
  "      Нет       ",
  "      Нема      ",
  "      None      ",
  "      Нет       "
};
const uint32_t cursor_x_none[MAX_NAMBER_LANGUAGE] = {5, 5, 5, 5};

const uint8_t ms[MAX_NAMBER_LANGUAGE][2] = {"мс", "мс", "ms", "мс"};


const uint8_t calibrating[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
{
  "   Калибровка   ",
  "  Калібрування  ",
  "  Calibration   ",
  "   Калибровка   "
};

const uint8_t name_string_alarm_delay[MAX_NAMBER_LANGUAGE][ALARM_SET_DELAYS][MAX_COL_LCD + 1] = 
{
  {
    "     Период     "
  },
  {
    "     Період     "
  },
  {
    "     Period     "
  },
  {
    "     Период     "
  }
};
    
const uint8_t name_string_alarm_control[MAX_NAMBER_LANGUAGE][MAX_INDEX_CTRL_ALARM][MAX_COL_LCD + 1] = 
{
  {
    "     Режим      "
  },
  {
    "     Режим      "
  },
  {
    "      Mode      "
  },
  {
    "     Режим      "
  }
};

const uint8_t information_alarm_control[MAX_NAMBER_LANGUAGE][ALARM_MODES_NUMBER][MAX_COL_LCD + 1] = 
{
  {"    ПРОСТОЙ     ", "   ТРИГГЕНЫЙ    ", "    ЗАД.ВР.     "},
  {"    ПРОСТИЙ     ", "    ТРИҐЕНЫЙ    ", "    ЗАД.ЧАС     "},
  {"     SIMPLE     ", "    TRIGGER     ", "    ЗАД.ВР.     "},
  {"    ПРОСТИЙ     ", "   ТРИГГЕНЫЙ    ", "    ЗАД.ВР.     "}
};
const unsigned int cursor_x_alarm_control[MAX_NAMBER_LANGUAGE][ALARM_MODES_NUMBER] = 
{
  {3, 2, 3},
  {3, 3, 3},
  {4, 3, 3},
  {3, 2, 3}
};

const uint8_t name_alarm_in_signals[MAX_NAMBER_LANGUAGE][ALARM_SIGNALS_IN][MAX_COL_LCD + 1] =
{
  {NAME_ALARM_IN_SIGNALS_RU},  
  {NAME_ALARM_IN_SIGNALS_UA},  
  {NAME_ALARM_IN_SIGNALS_EN},  
  {NAME_ALARM_IN_SIGNALS_KZ}
};

const uint8_t name_alarm_out_signals[MAX_NAMBER_LANGUAGE][ALARM_SIGNALS_OUT][MAX_COL_LCD + 1] =
{
  {NAME_ALARM_OUT_SIGNALS_RU},  
  {NAME_ALARM_OUT_SIGNALS_UA},  
  {NAME_ALARM_OUT_SIGNALS_EN},  
  {NAME_ALARM_OUT_SIGNALS_KZ}
};

const uint8_t name_alarm[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
{
  " СЗС            ",
  " СЗС            ",
  " Alarm          ",
  " СЗС            "
};
const unsigned int first_index_number_alarm[MAX_NAMBER_LANGUAGE] = {4, 4, 6, 4};
    
const uint8_t name_button_out_signals[MAX_NAMBER_LANGUAGE][BUTTON_SIGNALS_OUT][MAX_COL_LCD + 1] =
{
  {NAME_BUTTON_OUT_SIGNALS_RU},  
  {NAME_BUTTON_OUT_SIGNALS_UA},  
  {NAME_BUTTON_OUT_SIGNALS_EN},  
  {NAME_BUTTON_OUT_SIGNALS_KZ}
};

const uint8_t name_fix_buttons[NUMBER_FIX_BUTTONS][MAX_COL_LCD + 1] = 
{
  "MUTE            ",
  "RESET           ",
  "TEST            "
};

const uint8_t name_button[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
{
  " ФК             ",
  " ФК             ",
  " DB             ",
  " ФК             "
};
const uint32_t first_index_number_button[MAX_NAMBER_LANGUAGE] = {3, 3, 3, 3};

const uint8_t name_event_log_out_signals[MAX_NAMBER_LANGUAGE][EVENT_LOG_SIGNALS_OUT][MAX_COL_LCD + 1] =
{
  {NAME_EVENT_LOG_OUT_SIGNALS_RU},  
  {NAME_EVENT_LOG_OUT_SIGNALS_UA},  
  {NAME_EVENT_LOG_OUT_SIGNALS_EN},  
  {NAME_EVENT_LOG_OUT_SIGNALS_KZ}
};



const uint8_t name_string_choose_communication_parameters[MAX_NAMBER_LANGUAGE][MAX_ROW_CHCP_M2][MAX_COL_LCD + 1] = 
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

const uint8_t name_string_choose_communication_parameters_address[MAX_NAMBER_LANGUAGE][MAX_ROW_ADDRESS_M2][MAX_COL_LCD + 1] = 
{
  "     Адрес      ",
  "     Адреса     ",
  "    Address     ",
  "     Адрес      "
};

const uint8_t name_string_choose_communication_parameters_RS485[MAX_NAMBER_LANGUAGE][MAX_ROW_SETTING_RS485_M2][MAX_COL_LCD + 1] = 
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

const uint8_t name_string_choose_communication_parameters_speed[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_VIEW_BAUD_RS485][MAX_COL_LCD + 1] = 
{
  " Скорость обмена",
  " Швидкість обм. ",
  "   Baud rate    ",
  " Скорость обмена"
};
const uint8_t information_speed[MAX_NUMBER_BAUD_RS485][MAX_COL_LCD + 1] = 
{
  "      9600      ",
  "     14400      ",
  "     19200      ",
  "     28800      ",
  "     38400      ",
  "     57600      ",
  "     115200     "
};

const uint8_t name_stringe_communication_parameters_pare[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_VIEW_PARE_RS485][MAX_COL_LCD + 1] = 
{
  " Контр.четности ",
  " Контр.парності ",
  "     Parity     ",
  " Контр.четности "
};
const uint32_t cursor_x_communication_parameters_pare[MAX_NUMBER_BAUD_RS485] = {5, 4, 4, 4, 4, 4, 4};
const uint8_t information_pare[MAX_NAMBER_LANGUAGE][MAX_NUMBER_PARE_RS485][MAX_COL_LCD + 1] = 
{
  {"      Нет       ", "     Нечет.     ", "      Чет.      "},
  {"      Нема      ", "    Непарн.     ", "      Парн.     "},
  {"      None      ", "      Odd       ", "      Even      "},
  {"      Нет       ", "     Нечет.     ", "      Чет.      "}
};
const uint32_t cursor_x_pare[MAX_NAMBER_LANGUAGE][MAX_NUMBER_PARE_RS485 + 1] = 
{
  {5, 4, 5, 4},
  {5, 3, 5, 3},
  {5, 5, 5, 4},
  {5, 4, 5, 4}
};

const uint8_t name_stringe_communication_parameters_stopbits[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_VIEW_STOP_BITS_RS485][MAX_COL_LCD + 1] = 
{
  " Колич.стоп-бит ",
  "Кільк.стоп-біт  ",
  "   Stop Bits    ",
  " Колич.стоп-бит "
};
const uint8_t information_stopbits[MAX_NAMBER_LANGUAGE][MAX_NUMBER_STOP_BITS_RS485][MAX_COL_LCD + 1] = 
{
  {"      Один      ", "      Два       "},
  {"      Один      ", "      Два       "},
  {"      One       ", "      Two       "},
  {"      Один      ", "      Два       "}
};
const uint32_t cursor_x_stopbits[MAX_NAMBER_LANGUAGE][MAX_NUMBER_STOP_BITS_RS485] = 
{
  {5, 5},
  {5, 5},
  {5, 5},
  {5, 5}
};

const uint8_t name_stringe_communication_parameters_timeout[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_VIEW_TIMEOUT_RS485][MAX_COL_LCD + 1] = 
{
  "  Конец приёма  ",
  "Кінець приймання",
  "End of Reception",
  "  Конец приёма  "
};

const uint8_t name_string_choose_settings_logical_nodes_delay[MAX_NAMBER_LANGUAGE][MAX_ROW_LIST_SETTINGS_D_M2][MAX_COL_LCD + 1] = 
{
  {
    " Выдержки       "
  },
  {
    " Витримки       "
  },
  {
    " Delay          "
  },
  {
    " Беріктік       "
  }
};

const uint8_t name_string_choose_settings_logical_nodes_control[MAX_NAMBER_LANGUAGE][MAX_ROW_LIST_SETTINGS_C_M2][MAX_COL_LCD + 1] = 
{
  {
    " Управление     "
  },
  {
    " Управління     "
  },
  {
    " Control        "
  },
  {
    " Баскару        "
  }
};

const uint8_t name_string_choose_settings_logical_nodes_delay_control[MAX_NAMBER_LANGUAGE][MAX_ROW_LIST_SETTINGS_DC_M2][MAX_COL_LCD + 1] = 
{
  {
    " Выдержки       ",
    " Управление     "
  },
  {
    " Витримки       ",
    " Управління     "
  },
  {
    " Delay          ",
    " Control        "
  },
  {
    " Беріктік       ",
    " Баскару        "
  }
};

const uint8_t name_string_choose_settings_logical_nodes_pickup_delay_control[MAX_NAMBER_LANGUAGE][MAX_ROW_LIST_SETTINGS_PDC_M2][MAX_COL_LCD + 1] = 
{
  {
    " Уставки        ",
    " Выдержки       ",
    " Управление     "
  },
  {
    " Уставки        ",
    " Витримки       ",
    " Управління     "
  },
  {
    " Pickups        ",
    " Delay          ",
    " Control        "
  },
  {
    " Баскару        ",
    " Кyрулар        ",
    " Беріктік       "
  }
};

const uint8_t name_string_configuration[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_CONFIGURATION][MAX_COL_LCD + 1] = 
{
  {
    "      СЗС       ",
    "      ШГС       ",
    "       И        ",
    "      ИЛИ       ",
    "    Искл.ИЛИ    ",
    "       НЕ       ",
    "   МФ-Таймер    ",
    "   D-Триггер    ",
    "      ГПС       ",
    "       ТУ       ",
    " Журнал событий "
  },
  {
    "      СЗС       ",
    "      ШГС       ",
    "       І        ",
    "      АБО       ",
    "    Викл.АБО    ",
    "       НЕ       ",
    "   БФ-Таймер    ",
    "    D-Триґер    ",
    "      ГПС       ",
    "       ТУ       ",
    "  Журнал подій  "
},
  {
    "      СЗС       ",
    "      ШГС       ",
    "      AND       ",
    "       OR       ",
    "      XOR       ",
    "      NOT       ",
    "    MF-Timer    ",
    "   D-Trigger    ",
    "      PSG       ",
    "       TC       ",
    "   Event Log    "
  },
  {
    "      СЗС       ",
    "      ШГС       ",
    "       И        ",
    "      ИЛИ       ",
    "    Искл.ИЛИ    ",
    "       НЕ       ",
    "   МФ-Таймер    ",
    "   D-Триггер    ",
    "      ГПС       ",
    "       ТУ       ",
    " Журнал событий "
  }
};

const uint8_t name_f_blocks[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_EDITOR_LIST_LOGICAL_NODES][MAX_COL_LCD + 1] = 
{
  {
    "                ",
    "Д.Вх            ",
    "В.Р             ",
    "Св              ",
    "ФК              ",
    "СЗС             ",
    "ШГС             ",
    "И               ",
    "ИЛИ             ",
    "И-ИЛИ           ",
    "НЕ              ",
    "МФТ             ",
    "D-Тр            ",
    "ГПС             ",
    "ТУ              ",
    "Ж.Cобытий       "
  },
  {
    "                ",
    "Д.Вх            ",
    "В.Р             ",
    "Св              ",
    "ФК              ",
    "СЗС             ",
    "ШГС             ",
    "І               ",
    "АБО             ",
    "В.АБО           ",
    "НЕ              ",
    "БФТ             ",
    "D-Тр            ",
    "ГПС             ",
    "ТУ              ",
    "Ж.Подій         "
  },
  {
    "                ",
    "D.In            ",
    "O.R             ",
    "LED             ",
    "DB              ",
    "СЗС             ",
    "ШГС             ",
    "AND             ",
    "OR              ",
    "XOR             ",
    "NOT             ",
    "MFT             ",
    "D-Tr            ",
    "PSG             ",
    "TC              ",
    "Ev.Log          "
  },
  {
    "                ",
    "Д.Вх            ",
    "В.Р             ",
    "Св              ",
    "ФК              ",
    "СЗС             ",
    "ШГС             ",
    "И               ",
    "ИЛИ             ",
    "И-ИЛИ           ",
    "НЕ              ",
    "МФТ             ",
    "D-Тр            ",
    "ГПС             ",
    "ТУ              ",
    "Ж.Событий       "
  }
};

const uint8_t name_string_editor_logical_nodes[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_EDITOR_LIST_LOGICAL_NODES][MAX_COL_LCD + 1] = 
{
  {
    " Общий блок     ",
    " Д.Входы        ",
    " В.Реле         ",
    " Светоиндикаторы",
    " ФК             ",
    " СЗС            ",
    " ШГС            ",
    " И              ",
    " ИЛИ            ",
    " Искл.ИЛИ       ",
    " НЕ             ",
    " МФ-Таймер      ",
    " D-Триггер      ",
    " ГПС            ",
    " ТУ             ",
    " Ж.Событий      "
  },
  {
    " Загальний блок ",
    " Д.Входи        ",
    " В.Реле         ",
    " Світоіндикатори",
    " ФК             ",
    " СЗС            ",
    " ШГС            ",
    " І              ",
    " АБО            ",
    " Викл.АБО       ",
    " НЕ             ",
    " БФ-Таймер      ",
    " D-Триґер       ",
    " ГПС            ",
    " ТУ             ",
    " Ж.Подій        "
  },
  {
    " General block  ",
    " D.Inputs       ",
    " O.Relays       ",
    " LEDs           ",
    " DB             ",
    " СЗС            ",
    " ШГС            ",
    " AND            ",
    " OR             ",
    " XOR            ",
    " NOT            ",
    " MF-Timer       ",
    " D-Trigger      ",
    " PSG            ",
    " TC             ",
    " Ev.Log         "
  },
  {
    " Общий блок     ",
    " Д.Входы        ",
    " В.Реле         ",
    " Светоиндикаторы",
    " ФК             ",
    " СЗС            ",
    " ШГС            ",
    " И              ",
    " ИЛИ            ",
    " Искл.ИЛИ       ",
    " НЕ             ",
    " МФ-Таймер      ",
    " D-Триггер      ",
    " ГПС            ",
    " ТУ             ",
    " Ж.Событий      "
  }
};

const uint8_t name_fix_block_in_signals[MAX_NAMBER_LANGUAGE][FIX_BLOCK_SIGNALS_IN][MAX_COL_LCD + 1] =
{
  {NAME_FIX_BLOCK_IN_SIGNALS_RU},  
  {NAME_FIX_BLOCK_IN_SIGNALS_UA},  
  {NAME_FIX_BLOCK_IN_SIGNALS_EN},  
  {NAME_FIX_BLOCK_IN_SIGNALS_KZ}
};
  
const uint8_t name_fix_block_out_signals[MAX_NAMBER_LANGUAGE][FIX_BLOCK_SIGNALS_OUT][MAX_COL_LCD + 1] =
{
  {NAME_FIX_BLOCK_OUT_SIGNALS_RU},  
  {NAME_FIX_BLOCK_OUT_SIGNALS_UA},  
  {NAME_FIX_BLOCK_OUT_SIGNALS_EN},  
  {NAME_FIX_BLOCK_OUT_SIGNALS_KZ}
};

const uint8_t name_string_group_alarm[MAX_NAMBER_LANGUAGE][MAX_INDEX_CTRL_GROUP_ALARM][MAX_COL_LCD + 1] = 
{
  {
    "   Состояние    ",
    "  Контроль ШГС  ",
    "      Ток       "
  },
  {
    "      Стан      ",
    "  Контроль ШГС  ",
    "     Струм      "
  },
  {
    "      Стан      ",
    "  Контроль ШГС  ",
    "    Current     "
  },
  {
     "   Состояние    ",
     "  Контроль ШГС  ",
     "      Ток       "
   }
};

const uint8_t name_string_group_alarm_pickup[MAX_NAMBER_LANGUAGE][GROUP_ALARM_PICKUPS][MAX_COL_LCD + 1] = 
{
  {
    "       ‰I       "
  },
  {
    "       ‰I       "
  },
  {
    "       ‰I       "
  },
  {
    "       ‰I       "
  }
};

const uint8_t name_string_group_alarm_delay[MAX_NAMBER_LANGUAGE][GROUP_ALARM_SET_DELAYS][MAX_COL_LCD + 1] = 
{
  {
    "   T Задержки   ",
  },
  {
    "   T Затримки   ",
  },
  {
    "   T Задержки   ",
  },
  {
    "   T Задержки   ",
  }
};

    
const uint8_t name_group_alarm_out_signals[MAX_NAMBER_LANGUAGE][GROUP_ALARM_SIGNALS_OUT][MAX_COL_LCD + 1] =
{
  {NAME_GROUP_ALARM_OUT_SIGNALS_RU},  
  {NAME_GROUP_ALARM_OUT_SIGNALS_UA},  
  {NAME_GROUP_ALARM_OUT_SIGNALS_EN},  
  {NAME_GROUP_ALARM_OUT_SIGNALS_KZ}
};

const uint8_t name_group_alarm[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
{
  " ШГС            ",
  " ШГС            ",
  " Gr.Alarm       ",
  " ШГС            "
};
const unsigned int first_index_number_group_alarm[MAX_NAMBER_LANGUAGE] = {4, 4, 9, 4};

const uint8_t name_string_info[MAX_NAMBER_LANGUAGE][MAX_ROW_INFO_M2][MAX_COL_LCD + 1] = 
{
  {
    "   Версия ПО    ",
    "   Версия КП    "
  },
  {
    "   Версія ПЗ    ",
    "   Версія КП    "
  },
  {
    "   VER.of F/W   ",
    "   VER.of MM    "
  },
  {
    "   Версия ПО    ",
    "   Версия КП    "
  }
};

const uint8_t name_string_input_control[MAX_NAMBER_LANGUAGE][MAX_INDEX_CTRL_INPUT][MAX_COL_LCD + 1] = 
{
  {
    " Входной сигнал "
  },
  {
    " Вхідний сигнал "
  },
  {
    "  Input signal  "
  },
  {
    " Входной сигнал "
  }
};

const uint8_t information_input_control[MAX_NAMBER_LANGUAGE][2][MAX_COL_LCD + 1] = 
{
  {"   ПОСТОЯННЫЙ   ", "   ПЕРЕМЕННЫЙ   "},
  {"   ПОСТІЙНИЙ    ", "    ЗМІННИЙ     "},
  {"     DIRECT     ", "   ALTERNATE    "},
  {"   ПОСТОЯННЫЙ   ", "   ПЕРЕМЕННЫЙ   "}
};
const unsigned int cursor_x_input_control[MAX_NAMBER_LANGUAGE][2] = 
{
  {2, 2},
  {2, 3},
  {4, 2},
  {2, 2}
};

const uint8_t name_string_input_delay[MAX_NAMBER_LANGUAGE][INPUT_SET_DELAYS][MAX_COL_LCD + 1] = 
{
  {
    " Допуск д.входа "
  },
  {
    " Допуск д.входу "
  },
  {
    " BIN Tolerance  "
  },
  {
    " Допуск д.входа "
  }
};
    
const uint8_t name_input_out_signals[MAX_NAMBER_LANGUAGE][INPUT_SIGNALS_OUT][MAX_COL_LCD + 1] =
{
  {NAME_INPUT_OUT_SIGNALS_RU},  
  {NAME_INPUT_OUT_SIGNALS_UA},  
  {NAME_INPUT_OUT_SIGNALS_EN},  
  {NAME_INPUT_OUT_SIGNALS_KZ}
};

const uint8_t name_input[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
{
  " Д.Вх.          ",
  " Д.Вх.          ",
  " DI             ",
  " Д.Вх.          "
};
const unsigned int first_index_number_input[MAX_NAMBER_LANGUAGE] = {6, 6, 3, 6};

const uint8_t name_string_labels[MAX_NAMBER_LANGUAGE][MAX_ROW_LABELS_M2][MAX_COL_LCD + 1] = 
{
  {
    " Метка конфиг.  ",
    " Метка настроек "
  },
  {
    " Мітка конфіг.  ",
    " Мітка налашт.  "
  },
  {
    " Configur.Mark  ",
    " Settings Mark  "
  },
  {
    " Метка конфиг.  ",
    " Метка настроек "
  }
};

const uint8_t name_string_list_settings[MAX_NAMBER_LANGUAGE][MAX_ROW_LIST_SETTINGS_M2][MAX_COL_LCD + 1] = 
{
  {
    " Конфигурация   ",
    " Параметриров.  ",
    " Редактор       ",
    " Язык           ",
    " Коммуникация   ",
    " Пароли         "
  },
  {
    " Конфігурація   ",
    " Параметрування ",
    " Редактор       ",
    " Мова           ",
    " Комунікація    ",
    " Паролі         "
  },
  {
    " Configuration  ",
    " Parametrization",
    " Editor         ",
    " Language       ",
    " Communication  ",
    " Passwords      "
  },
  {
    " Конфигурация   ",
    " Параметриров.  ",
    " Редактор       ",
    " Язык           ",
    " Коммуникация   ",
    " Пароли         "
  }
};

const uint8_t name_stringlist_settings_param[MAX_NAMBER_LANGUAGE][MAX_ROW_LIST_SETTINGS_PARAM_M2][MAX_COL_LCD + 1] = 
{
  {
    " Д.Входы        ",
    " В.Реле         ",
    " Светоиндикаторы",
    " СЗС            ",
    " ШГС            ",
    " Таймера        ",
    " ГПС            "
  },
  {
    " Д.Входи        ",
    " В.Реле         ",
    " Світоіндикатори",
    " СЗС            ",
    " ШГС            ",
    " Таймери        ",
    " ГПС            "
  },
  {
    " D.Inputs       ",
    " O.Relays       ",
    " LEDs           ",
    " Alarms         ",
    " Group Alarms   ",
    " Timers         ",
    " Meanders       "
  },
  {
    " Д.Входы        ",
    " В.Реле         ",
    " Светоиндикаторы",
    " СЗС            ",
    " ШГС            ",
    " Таймери        ",
    " ГПС            "
  }
};

const uint8_t name_string_list_settings_param_info[MAX_NAMBER_LANGUAGE][2][MAX_COL_LCD + 1] = 
{
  {
    "  ФБ отсутсвуют ",
    "  в устройстве  "
  },
  {
    "  ФБ відсутні   ",
    "   у пристрої   "
  },
  {
    " LN are absent  ",
    "   in device    "
  },
  {
    " ФБ отсутсвуют  ",
    "  в устройстве  "
  }
};

const uint8_t name_log[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
{
  " Ж.Событий      ",
  " Ж.Подій        ",
  " Ev.Log         ",
  " Ж.Событий      "
};
const unsigned int first_index_number_log[MAX_NAMBER_LANGUAGE] = {10, 8, 7, 10};

const uint8_t name_string_main[MAX_NAMBER_LANGUAGE][MAX_ROW_MAIN_M2][MAX_COL_LCD + 1] = 
{
  {
   " Часы           ",
   " Измерения      ",
   " Входы-Выходы   ",
   " Регистраторы   ",
   " Настройки      ",
   " Диагностика    ",
   " Метка настроек ",
   " Версия ПО и КП "
  },
  {
   " Годинник       ",
   " Вимірювання    ",
   " Входи-Виходи   ",
   " Реєстратори    ",
   " Налаштування   ",
   " Діагностика    ",
   " Мітка налашт.  ",
   " Версія ПЗ і КП "
  },
  {
   " Clock          ",
   " Measurement    ",
   " Inputs-Outputs ",
   " Recorders      ",
   " Settings       ",
   " Diagnostic     ",
   " Settings Mark  ",
   " VER.of F/W & MM"
  },
  {
   " Саfат          ",
   " Љлшем          ",
   " Кіріс-Шыfыс    ",
   " Тіркегіштер    ",
   " Реттегіш       ",
   " Диагностика    ",
   " Метка настроек ",
   " Версия ПО и КП "
  }
};

const uint8_t name_string_meander_delay[MAX_NAMBER_LANGUAGE][MAX_INDEX_DELAY_MEANDER][MAX_COL_LCD + 1] = 
{
  {
    "     Период     "
  },
  {
    "     Період     "
  },
  {
    "     Period     "
  },
  {
    "     Период     "
  }
};
    
const uint8_t name_meander_out_signals[MAX_NAMBER_LANGUAGE][MEANDER_SIGNALS_OUT][MAX_COL_LCD + 1] =
{
  {NAME_MEANDER_OUT_SIGNALS_RU},  
  {NAME_MEANDER_OUT_SIGNALS_UA},  
  {NAME_MEANDER_OUT_SIGNALS_EN},  
  {NAME_MEANDER_OUT_SIGNALS_KZ}
};

const uint8_t name_meander[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
{
  " ГПС            ",
  " ГПС            ",
  " PSG            ",
  " ГПС            "
};
const unsigned int first_index_number_meander[MAX_NAMBER_LANGUAGE] = {4, 4, 4, 4};

const uint32_t index_array[MAX_ROW_FOR_MEASURMENT_ANALOG_INPUT] = 
{
  IM_I1,
  IM_I2,
  IM_I3,
  IM_I4,
  IM_U
};

const uint8_t name_string_output_led_control[MAX_NAMBER_LANGUAGE][MAX_INDEX_CTRL_OUTPUT_LED][MAX_COL_LCD + 1] = 
{
  {
    "  Норм./Триг.   ",
    "   Пост./Имп.   ",
    " Имп-Пр/Имп-Расш",
    "   Частота 1    ",
    "   Частота 2    "
  },
  {
    "  Норм./Триґ.   ",
    "   Пост./Імп.   ",
    " Імп-Пр/Імп-Росш",
    "   Частота 1    ",
    "   Частота 2    "
  },
  {
    "  Norm./Trig.   ",
    "  Const./Imp.   ",
    "  Imp-S/Imp-Ex  ",
    "   Frequency 1  ",
    "   Frequency 2  "
  },
  {
    "   Имп./Триг.   ",
    "   Норм./Имп.   ",
    " Имп-Пр/Имп-Расш",
    "   Частота 1    ",
    "   Частота 2    "
  }
};

const uint8_t information_output_led_control_N_T[MAX_NAMBER_LANGUAGE][2][MAX_COL_LCD + 1] = 
{
  {"   НОРМАЛЬНЫЙ   ", "   ТРИГГЕРНЫЙ   "},
  {"   НОРМАЛЬНИЙ   ", "   ТРИҐЕРНИЙ    "},
  {"     NORMAL     ", "    TRIGGER     "},
  {"   НОРМАЛЬНЫЙ   ", "   ТРИГГЕРНЫЙ   "}
};
const uint32_t cursor_x_output_led_control_N_T[MAX_NAMBER_LANGUAGE][2] = 
{
  {2, 2},
  {2, 2},
  {4, 3},
  {2, 2}
};

const uint8_t information_output_led_control_C_I[MAX_NAMBER_LANGUAGE][2][MAX_COL_LCD + 1] = 
{
  {"   ПОСТОЯННЫЙ   ", "   ИМПУЛЬСНЫЙ   "},
  {"   ПОСТІЙНИЙ    ", "   ІМПУЛЬСНИЙ   "},
  {"    CONSTANT    ", "    IMPULSE     "},
  {"   ПОСТОЯННЫЙ   ", "   ИМПУЛЬСНЫЙ   "},
};
const uint32_t cursor_x_output_led_control_C_I[MAX_NAMBER_LANGUAGE][2] = 
{
  {2, 2},
  {2, 2},
  {3, 3},
  {2, 2}
};
          
const uint8_t information_output_led_control_SI_EI[MAX_NAMBER_LANGUAGE][2][MAX_COL_LCD + 1] = 
{
  {"  ИМП.ПРОСТОЙ   ", " ИМП.РАСШИРЕННЫЙ"},
  {"  ІМП.ПРОСТИЙ   ", " ІМП.РОЗШИРЕНИЙ "},
  {"   IMP.SIMPLE   ", "  IMP.EXPANDED  "},
  {"  ИМП.ПРОСТОЙ   ", " ИМП.РАСШИРЕННЫЙ"},
};
const uint32_t cursor_x_output_led_control_SI_EI[MAX_NAMBER_LANGUAGE][2] = 
{
  {1, 0},
  {1, 0},
  {2, 1},
  {1, 0}
};

const uint8_t value_name[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
{
  {"ГПС             "},
  {"ГПС             "},
  {"MEANDER         "},
  {"ГПС             "},
};
const uint32_t number_symbols_in_name[MAX_NAMBER_LANGUAGE] = {3, 3, 7, 3};

const uint8_t name_output_led_in_signals[MAX_NAMBER_LANGUAGE][OUTPUT_LED_SIGNALS_IN][MAX_COL_LCD + 1] =
{
  {NAME_OUTPUT_LED_IN_SIGNALS_RU},  
  {NAME_OUTPUT_LED_IN_SIGNALS_UA},  
  {NAME_OUTPUT_LED_IN_SIGNALS_EN},  
  {NAME_OUTPUT_LED_IN_SIGNALS_KZ}
};
  
const uint8_t name_output_led_out_signals[MAX_NAMBER_LANGUAGE][OUTPUT_LED_SIGNALS_OUT][MAX_COL_LCD + 1] =
{
  {NAME_OUTPUT_LED_OUT_SIGNALS_RU},  
  {NAME_OUTPUT_LED_OUT_SIGNALS_UA},  
  {NAME_OUTPUT_LED_OUT_SIGNALS_EN},  
  {NAME_OUTPUT_LED_OUT_SIGNALS_KZ}
};

const uint8_t name_output[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
{
  " В.Реле         ",
  " В.Реле         ",
  " DO             ",
  " В.Реле         "
};
const uint32_t first_index_number_output[MAX_NAMBER_LANGUAGE] = {7, 7, 3, 7};

const uint8_t name_led[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
{
  " Св.            ",
  " Св.            ",
  " LED            ",
  " Св.            "
};
const uint32_t first_index_number_led[MAX_NAMBER_LANGUAGE] = {4, 4, 4, 4};

const uint8_t name_string_level_password_1[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
{
  " Введите пароль:",
  " Введіть пароль:",
  " Enter password:",
  " Введите пароль:"
};

const uint8_t name_string_level_password_2[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
{
  "  Новый пароль: ",
  "  Новий пароль: ",
  "  New password: ",
  "  Новый пароль: "
};

const uint8_t password_item_level_password[MAX_ROW_LIST_PASSWORDS_M2][MAX_NAMBER_LANGUAGE][2][MAX_COL_LCD + 1] = 
{
  {
    {" Смена пароля 1 ", " Уст.пароля 1   "},
    {" Зміна паролю 1 ", " Вст.паролю 1   "},
    {" Pass.1 Change  ", " Password 1 Set "},
    {" Смена пароля 1 ", " Уст.пароля 1   "}
  },
  {
    {" Смена пароля 2 ", " Уст.пароля 2   "},
    {" Зміна паролю 2 ", " Вст.паролю 2   "},
    {" Pass.2 Change  ", " Password 2 Set "},
    {" Смена пароля 2 ", " Уст.пароля 2   "}
  },
};

const uint8_t name_string_registrators[MAX_NAMBER_LANGUAGE][MAX_ROW_LIST_REGISTRATORS_M2][MAX_COL_LCD + 1] = 
{
  {
    " Журнал событий ",
    " Архив диагност."
  },
  {
    " Журнал подій   ",
    " Архів діагност."
  },
  {
    " Event Log      ",
    " Diagn.Archive  "
  },
  {
    " Журнал событий ",
    " Архив диагност."
  }
};

const uint8_t information_no_records[MAX_NAMBER_LANGUAGE][2][MAX_COL_LCD + 1] = 
{
  {
    "      Нет       ",
    "    записей     "
  },
  {
    "     Нема       ",
    "    записів     "
  },
  {
    "    Records     ",
    "   are absent   "
  },
  {
    "      Нет       ",
    "    записей     "
  }
};

const uint8_t name_string_pr_err[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_DIAGNOSTYKA][MAX_COL_LCD + 1] = 
{
  {
    NAME_DIAGN_RU
  },
  {
    NAME_DIAGN_UA
  },
  {
    NAME_DIAGN_EN
  },
  {
    NAME_DIAGN_KZ
  }
};

const uint8_t passive_active[MAX_NAMBER_LANGUAGE][2][5 + 1] = 
{
  {"Пасс.", "Акт. "},
  {"Пас. ", "Акт. "},
  {"Pass.", "Act. "},
  {"Пасс.", "Акт. "}
};

const uint8_t info_data_corrupted[MAX_NAMBER_LANGUAGE][2][MAX_COL_LCD + 1] = 
{
  {
    "     Данные     ",
    "   повреждены   "
  },
  {
    "      Дані      ",
    "   пошкоджені   "
  },
  {
    "      Data      ",
    " are corrupted  "
  },
  {
    "     Данные     ",
    "   повреждены   "
  }
};

const uint8_t information_timeout[MAX_NAMBER_LANGUAGE][2][MAX_COL_LCD + 1] = 
{
  {
   "    Time-out    ",
   " ожидания истек "
  },
  {
   "    Time-out    ",
   " очікування вич."
  },
  {
   "    Time-out    ",
   "    is over     "
  },
  {
   "    Time-out    ",
   " ожидания истек "
  }
};

const uint8_t name_string_language[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_VIEW_SETTING_LANGUAGE][MAX_COL_LCD + 1] = 
{
  "      Язык      ",
  "      Мова      ",
  "    Language    ",
  "      Язык      "
};

uint8_t information_language[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
{
  "    Русский     ",
  "   Українська   ",
  "    English     ",
  "     Казак      "
};
const unsigned int cursor_x_language[MAX_NAMBER_LANGUAGE] = {3, 2, 3, 4};

const uint8_t name_standard_logic_in_signals[MAX_NAMBER_LANGUAGE][1][MAX_COL_LCD + 1] =
{
  {NAME_STANDARD_LOGIC_IN_SIGNALS_RU},  
  {NAME_STANDARD_LOGIC_IN_SIGNALS_UA},  
  {NAME_STANDARD_LOGIC_IN_SIGNALS_EN},  
  {NAME_STANDARD_LOGIC_IN_SIGNALS_KZ}
};

const uint8_t name_standard_logic_out_signals[MAX_NAMBER_LANGUAGE][STANDARD_LOGIC_SIGNALS_OUT][MAX_COL_LCD + 1] =
{
  {NAME_STANDARD_LOGIC_OUT_SIGNALS_RU},  
  {NAME_STANDARD_LOGIC_OUT_SIGNALS_UA},  
  {NAME_STANDARD_LOGIC_OUT_SIGNALS_EN},  
  {NAME_STANDARD_LOGIC_OUT_SIGNALS_KZ}
};

const uint8_t name_and[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
{
  " И              ",
  " І              ",
  " AND            ",
  " И              "
};
const uint32_t first_index_number_and[MAX_NAMBER_LANGUAGE] = {2, 2, 4, 2};

const uint8_t name_or[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
{
  " ИЛИ            ",
  " АБО            ",
  " OR             ",
  " ИЛИ            "
};
const uint32_t first_index_number_or[MAX_NAMBER_LANGUAGE] = {4, 4, 3, 4};

const uint8_t name_xor[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
{
  " Искл.ИЛИ       ",
  " Викл.АБО       ",
  " XOR            ",
  " Искл.ИЛИ       "
};
const uint32_t first_index_number_xor[MAX_NAMBER_LANGUAGE] = {9, 9, 4, 9};

const uint8_t name_not[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
{
    " НЕ             ",
    " НЕ             ",
    " NOT            ",
    " НЕ             ",
};
const uint32_t first_index_number_not[MAX_NAMBER_LANGUAGE] = {3, 3, 4, 3};

const uint8_t name_string_inputs_outputs[MAX_NAMBER_LANGUAGE][MAX_ROW_INPUT_OUTPUT_M2][MAX_COL_LCD + 1] = 
{
  {
    " Сост.ШГС       ",
    " Сост.входов    ",
    " Сост.выходов   "
  },
  {
    " Стан ШГС       ",
    " Стан входів    ",
    " Стан виходів   "
  },
  {
    " Inputs G.Alarms",
    " Inputs state   ",
    " Outputs state  "
  },
  {
    " Сост.ШГС       ",
    " Кіріс жаfдайы  ",
    " Шыfыс жаfдайы  "
  }
};

const uint8_t name_string_timer_delay[MAX_NAMBER_LANGUAGE][TIMER_SET_DELAYS][MAX_COL_LCD + 1] = 
{
  {
    "  Таймер паузы  ",
    " Таймер работы  "
  },
  {
    "  Таймер паузи  ",
    " Таймер роботи  "
  },
  {
    "  Pause Timer   ",
    " Operation Timer"
  },
  {
    "  Таймер паузы  ",
    " Таймер работы  "
  }
};
    
const uint8_t name_timer_in_signals[MAX_NAMBER_LANGUAGE][TIMER_SIGNALS_IN][MAX_COL_LCD + 1] =
{
  {NAME_TIMER_IN_SIGNALS_RU},  
  {NAME_TIMER_IN_SIGNALS_UA},  
  {NAME_TIMER_IN_SIGNALS_EN},  
  {NAME_TIMER_IN_SIGNALS_KZ}
};
  
const uint8_t name_timer_out_signals[MAX_NAMBER_LANGUAGE][TIMER_SIGNALS_OUT][MAX_COL_LCD + 1] =
{
  {NAME_TIMER_OUT_SIGNALS_RU},  
  {NAME_TIMER_OUT_SIGNALS_UA},  
  {NAME_TIMER_OUT_SIGNALS_EN},  
  {NAME_TIMER_OUT_SIGNALS_KZ}
};
 
const uint8_t name_timer[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
{
  " МФ-Таймер      ",
  " БФ-Таймер      ",
  " MF-Timer       ",
  " МФ-Таймер      "
};
const uint32_t first_index_number_timer[MAX_NAMBER_LANGUAGE] = {10, 10, 9, 10};


const uint8_t name_trigger_in_signals[MAX_NAMBER_LANGUAGE][TRIGGER_SIGNALS_IN][MAX_COL_LCD + 1] =
{
  {NAME_TRIGGER_IN_SIGNALS_RU},  
  {NAME_TRIGGER_IN_SIGNALS_UA},  
  {NAME_TRIGGER_IN_SIGNALS_EN},  
  {NAME_TRIGGER_IN_SIGNALS_KZ}
};

const uint8_t name_trigger_out_signals[MAX_NAMBER_LANGUAGE][TRIGGER_SIGNALS_OUT][MAX_COL_LCD + 1] =
{
  {NAME_TRIGGER_OUT_SIGNALS_RU},  
  {NAME_TRIGGER_OUT_SIGNALS_UA},  
  {NAME_TRIGGER_OUT_SIGNALS_EN},  
  {NAME_TRIGGER_OUT_SIGNALS_KZ}
};

const uint8_t name_trigger[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
{
 " D-Триггер      ",
 " D-Триґер       ",
 " D-Trigger      ",
 " D-Триггер      "
};
const uint32_t first_index_number_trigger[MAX_NAMBER_LANGUAGE] = {10, 9, 10, 10};

const uint8_t name_tu_in_signals[MAX_NAMBER_LANGUAGE][TU_SIGNALS_IN][MAX_COL_LCD + 1] =
{
  {NAME_TU_IN_SIGNALS_RU},  
  {NAME_TU_IN_SIGNALS_UA},  
  {NAME_TU_IN_SIGNALS_EN},  
  {NAME_TU_IN_SIGNALS_KZ}
};

const uint8_t name_tu_out_signals[MAX_NAMBER_LANGUAGE][TU_SIGNALS_OUT][MAX_COL_LCD + 1] =
{
  {NAME_TU_OUT_SIGNALS_RU},  
  {NAME_TU_OUT_SIGNALS_UA},  
  {NAME_TU_OUT_SIGNALS_EN},  
  {NAME_TU_OUT_SIGNALS_KZ}
};

const uint8_t name_tu[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
{
 " ТУ             ",
 " ТУ             ",
 " TC             ",
 " ТУ             "
};
const uint32_t first_index_number_tu[MAX_NAMBER_LANGUAGE] = {3, 3, 3, 3};

#endif
