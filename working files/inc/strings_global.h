#ifndef __STRINGS_GLOBAL_H
#define __STRINGS_GLOBAL_H

const uint8_t name_string_ask[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
{
  "��-Enter/���-Esc",
  "���-Enter/ͳ-Esc",
  "Yes-Enter/No-Esc",
  "��-Enter/���-Esc"
};

const uint8_t information_no_edition[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
{
  "���.�� ���������",
  "���.�� ���������",
  "Ed.isn't allowed",
  "���.�� ���������",
};

const uint8_t information_out_of_limits[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
{
  " ���.�� ��������",
  " ���.�� �������",
  "  Out of Limits ",
  "���.�� �������� "
};

const uint8_t information_error[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
{
  "     ������     ",
  "    �������     ",
  "     Error      ",
  "     ������     "
};
const uint32_t cursor_x_error[MAX_NAMBER_LANGUAGE] = {4, 3, 4, 4};

const uint8_t information_no_free_dyn_mem[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
{
  " ���.���.������.",
  " ���.���.������.",
  " ���.���.������.",
  " ���.���.������."
};

const uint8_t information_on_off[MAX_NAMBER_LANGUAGE][2][MAX_COL_LCD + 1] = 
{
  {"     ����.      ", "      ���.      "},
  {"     ����.      ", "     ����.     "},
  {"      Off       ", "       On       "},
  {"     њ��.      ", "     ����.      "}
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
  "  ������� ���.  ",
  " �������� ���� ",
  "  Apply changes ",
  "  ������� ���.  "
};

const uint8_t information_about_info_1[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
{
  " ����.���.����. ",
  " �����.����.�. ",
  " Max.n.of S.Exc.",
  " ����.���.����. "
};

const uint8_t information_empty[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
{
  "     �����      ",
  "     �����      ",
  "     Empty      ",
  "     �����      "
};
const uint32_t cursor_x_empty[MAX_NAMBER_LANGUAGE] = {4, 4, 4, 4};

const uint8_t information_none[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
{
  "      ���       ",
  "      ����      ",
  "      None      ",
  "      ���       "
};
const uint32_t cursor_x_none[MAX_NAMBER_LANGUAGE] = {5, 5, 5, 5};

const uint8_t ms[MAX_NAMBER_LANGUAGE][2] = {"��", "��", "ms", "��"};


const uint8_t calibrating[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
{
  "   ����������   ",
  "  �����������  ",
  "  Calibration   ",
  "   ����������   "
};

const uint8_t name_string_alarm_delay[MAX_NAMBER_LANGUAGE][ALARM_SET_DELAYS][MAX_COL_LCD + 1] = 
{
  {
    "     ������     "
  },
  {
    "     �����     "
  },
  {
    "     Period     "
  },
  {
    "     ������     "
  }
};
    
const uint8_t name_string_alarm_control[MAX_NAMBER_LANGUAGE][MAX_INDEX_CTRL_ALARM][MAX_COL_LCD + 1] = 
{
  {
    "     �����      "
  },
  {
    "     �����      "
  },
  {
    "      Mode      "
  },
  {
    "     �����      "
  }
};

const uint8_t information_alarm_control[MAX_NAMBER_LANGUAGE][ALARM_MODES_NUMBER][MAX_COL_LCD + 1] = 
{
  {"    �������     ", "   ����������   ", "    ���.��.     "},
  {"    �������     ", "   ��ȥ�����    ", "    ���.���     "},
  {"     SIMPLE     ", "    TRIGGER     ", "    ���.��.     "},
  {"    �������     ", "   ����������   ", "    ���.��.     "}
};
const unsigned int cursor_x_alarm_control[MAX_NAMBER_LANGUAGE][ALARM_MODES_NUMBER] = 
{
  {3, 2, 3},
  {3, 2, 3},
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
  " ���            ",
  " ���            ",
  " Alarm          ",
  " ���            "
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
  " ��             ",
  " ��             ",
  " DB             ",
  " ��             "
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
    " ��� ������     ",
    " ����� ������   ",
    " �����.RS-485   "
  },
  {
    " ��'� ������   ",
    " ������ ������ ",
    " ������.RS-485  "
  },
  {
    " Bay name       ",
    " Bay Address    ",
    " RS-485 Settings"
  },
  {
    " ��� ������     ",
    " ����� ������   ",
    " �����.RS-485   "
  }
};

const uint8_t name_string_choose_communication_parameters_address[MAX_NAMBER_LANGUAGE][MAX_ROW_ADDRESS_M2][MAX_COL_LCD + 1] = 
{
  "     �����      ",
  "     ������     ",
  "    Address     ",
  "     �����      "
};

const uint8_t name_string_choose_communication_parameters_RS485[MAX_NAMBER_LANGUAGE][MAX_ROW_SETTING_RS485_M2][MAX_COL_LCD + 1] = 
{
  {
    " �������� ������",
    " �����.�������� ",
    " �����.����-��� ",
    " ����� �����   "
  },
  {
    " �������� ���. ",
    " �����.������� ",
    "ʳ���.����-��  ",
    "ʳ���� ���������"
  },
  {
    " Baud rate      ",
    " Parity         ",
    " Stop Bits      ",
    "End of Reception"
  },
  {
    " �������� ������",
    " �����.�������� ",
    " �����.����-��� ",
    " ����� �����   "
  }
};

const uint8_t name_string_choose_communication_parameters_speed[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_VIEW_BAUD_RS485][MAX_COL_LCD + 1] = 
{
  " �������� ������",
  " �������� ���. ",
  "   Baud rate    ",
  " �������� ������"
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
  " �����.�������� ",
  " �����.������� ",
  "     Parity     ",
  " �����.�������� "
};
const uint32_t cursor_x_communication_parameters_pare[MAX_NUMBER_BAUD_RS485] = {5, 4, 4, 4, 4, 4, 4};
const uint8_t information_pare[MAX_NAMBER_LANGUAGE][MAX_NUMBER_PARE_RS485][MAX_COL_LCD + 1] = 
{
  {"      ���       ", "     �����.     ", "      ���.      "},
  {"      ����      ", "    ������.     ", "      ����.     "},
  {"      None      ", "      Odd       ", "      Even      "},
  {"      ���       ", "     �����.     ", "      ���.      "}
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
  " �����.����-��� ",
  "ʳ���.����-��  ",
  "   Stop Bits    ",
  " �����.����-��� "
};
const uint8_t information_stopbits[MAX_NAMBER_LANGUAGE][MAX_NUMBER_STOP_BITS_RS485][MAX_COL_LCD + 1] = 
{
  {"      ����      ", "      ���       "},
  {"      ����      ", "      ���       "},
  {"      One       ", "      Two       "},
  {"      ����      ", "      ���       "}
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
  "  ����� �����  ",
  "ʳ���� ���������",
  "End of Reception",
  "  ����� �����  "
};

const uint8_t name_string_choose_settings_logical_nodes_delay[MAX_NAMBER_LANGUAGE][MAX_ROW_LIST_SETTINGS_D_M2][MAX_COL_LCD + 1] = 
{
  {
    " ��������       "
  },
  {
    " ��������       "
  },
  {
    " Delay          "
  },
  {
    " ������       "
  }
};

const uint8_t name_string_choose_settings_logical_nodes_control[MAX_NAMBER_LANGUAGE][MAX_ROW_LIST_SETTINGS_C_M2][MAX_COL_LCD + 1] = 
{
  {
    " ����������     "
  },
  {
    " ���������     "
  },
  {
    " Control        "
  },
  {
    " �������        "
  }
};

const uint8_t name_string_choose_settings_logical_nodes_delay_control[MAX_NAMBER_LANGUAGE][MAX_ROW_LIST_SETTINGS_DC_M2][MAX_COL_LCD + 1] = 
{
  {
    " ��������       ",
    " ����������     "
  },
  {
    " ��������       ",
    " ���������     "
  },
  {
    " Delay          ",
    " Control        "
  },
  {
    " ������       ",
    " �������        "
  }
};

const uint8_t name_string_choose_settings_logical_nodes_pickup_delay_control[MAX_NAMBER_LANGUAGE][MAX_ROW_LIST_SETTINGS_PDC_M2][MAX_COL_LCD + 1] = 
{
  {
    " �������        ",
    " ��������       ",
    " ����������     "
  },
  {
    " �������        ",
    " ��������       ",
    " ���������     "
  },
  {
    " Pickups        ",
    " Delay          ",
    " Control        "
  },
  {
    " �������        ",
    " �y�����        ",
    " ������       "
  }
};

const uint8_t name_string_configuration[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_CONFIGURATION][MAX_COL_LCD + 1] = 
{
  {
    "      ���       ",
    "      ���       ",
    "       �        ",
    "      ���       ",
    "    ����.���    ",
    "       ��       ",
    "   ��-������    ",
    "   D-�������    ",
    "      ���       ",
    "       ��       ",
    "       ��       ",
    " ������ ������� "
  },
  {
    "      ���       ",
    "      ���       ",
    "       �        ",
    "      ���       ",
    "    ����.���    ",
    "       ��       ",
    "   ��-������    ",
    "    D-�����    ",
    "      ���       ",
    "       ��       ",
    "       ��       ",
    "  ������ ����  "
},
  {
    "      ���       ",
    "      ���       ",
    "      AND       ",
    "       OR       ",
    "      XOR       ",
    "      NOT       ",
    "    MF-Timer    ",
    "   D-Trigger    ",
    "      PSG       ",
    "       TC       ",
    "       TS       ",
    "   Event Log    "
  },
  {
    "      ���       ",
    "      ���       ",
    "       �        ",
    "      ���       ",
    "    ����.���    ",
    "       ��       ",
    "   ��-������    ",
    "   D-�������    ",
    "      ���       ",
    "       ��       ",
    "       ��       ",
    " ������ ������� "
  }
};

const uint8_t name_f_blocks[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_EDITOR_LIST_LOGICAL_NODES][MAX_COL_LCD + 1] = 
{
  {
    "                ",
    "�.��            ",
    "�.�             ",
    "��              ",
    "��              ",
    "���             ",
    "���             ",
    "�               ",
    "���             ",
    "�-���           ",
    "��              ",
    "���             ",
    "D-��            ",
    "���             ",
    "��              ",
    "��              ",
    "�.C������       "
  },
  {
    "                ",
    "�.��            ",
    "�.�             ",
    "��              ",
    "��              ",
    "���             ",
    "���             ",
    "�               ",
    "���             ",
    "�.���           ",
    "��              ",
    "���             ",
    "D-��            ",
    "���             ",
    "��              ",
    "��              ",
    "�.����         "
  },
  {
    "                ",
    "D.In            ",
    "O.R             ",
    "LED             ",
    "DB              ",
    "���             ",
    "���             ",
    "AND             ",
    "OR              ",
    "XOR             ",
    "NOT             ",
    "MFT             ",
    "D-Tr            ",
    "PSG             ",
    "TC              ",
    "TS              ",
    "Ev.Log          "
  },
  {
    "                ",
    "�.��            ",
    "�.�             ",
    "��              ",
    "��              ",
    "���             ",
    "���             ",
    "�               ",
    "���             ",
    "�-���           ",
    "��              ",
    "���             ",
    "D-��            ",
    "���             ",
    "��              ",
    "��              ",
    "�.�������       "
  }
};

const uint8_t name_string_editor_logical_nodes[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_EDITOR_LIST_LOGICAL_NODES][MAX_COL_LCD + 1] = 
{
  {
    " ����� ����     ",
    " �.�����        ",
    " �.����         ",
    " ���������������",
    " ��             ",
    " ���            ",
    " ���            ",
    " �              ",
    " ���            ",
    " ����.���       ",
    " ��             ",
    " ��-������      ",
    " D-�������      ",
    " ���            ",
    " ��             ",
    " ��             ",
    " �.�������      "
  },
  {
    " ��������� ���� ",
    " �.�����        ",
    " �.����         ",
    " �������������",
    " ��             ",
    " ���            ",
    " ���            ",
    " �              ",
    " ���            ",
    " ����.���       ",
    " ��             ",
    " ��-������      ",
    " D-�����       ",
    " ���            ",
    " ��             ",
    " ��             ",
    " �.����        "
  },
  {
    " General block  ",
    " D.Inputs       ",
    " O.Relays       ",
    " LEDs           ",
    " DB             ",
    " ���            ",
    " ���            ",
    " AND            ",
    " OR             ",
    " XOR            ",
    " NOT            ",
    " MF-Timer       ",
    " D-Trigger      ",
    " PSG            ",
    " TC             ",
    " TS             ",
    " Ev.Log         "
  },
  {
    " ����� ����     ",
    " �.�����        ",
    " �.����         ",
    " ���������������",
    " ��             ",
    " ���            ",
    " ���            ",
    " �              ",
    " ���            ",
    " ����.���       ",
    " ��             ",
    " ��-������      ",
    " D-�������      ",
    " ���            ",
    " ��             ",
    " ��             ",
    " �.�������      "
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
    "   ���������    ",
    "  �������� ���  ",
    "      ���       "
  },
  {
    "      ����      ",
    "  �������� ���  ",
    "     �����      "
  },
  {
    "      ����      ",
    "  �������� ���  ",
    "    Current     "
  },
  {
     "   ���������    ",
     "  �������� ���  ",
     "      ���       "
   }
};

const uint8_t name_string_group_alarm_pickup[MAX_NAMBER_LANGUAGE][GROUP_ALARM_PICKUPS][MAX_COL_LCD + 1] = 
{
  {
    "       �I       "
  },
  {
    "       �I       "
  },
  {
    "       �I       "
  },
  {
    "       �I       "
  }
};

const uint8_t name_string_group_alarm_delay[MAX_NAMBER_LANGUAGE][GROUP_ALARM_SET_DELAYS][MAX_COL_LCD + 1] = 
{
  {
    "   T ��������   ",
  },
  {
    "   T ��������   ",
  },
  {
    "   T ��������   ",
  },
  {
    "   T ��������   ",
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
  " ���            ",
  " ���            ",
  " Gr.Alarm       ",
  " ���            "
};
const unsigned int first_index_number_group_alarm[MAX_NAMBER_LANGUAGE] = {4, 4, 9, 4};

const uint8_t name_string_info[MAX_NAMBER_LANGUAGE][MAX_ROW_INFO_M2][MAX_COL_LCD + 1] = 
{
  {
    "   ������ ��    ",
    "   ������ ��    "
  },
  {
    "   ����� ��    ",
    "   ����� ��    "
  },
  {
    "   VER.of F/W   ",
    "   VER.of MM    "
  },
  {
    "   ������ ��    ",
    "   ������ ��    "
  }
};

const uint8_t name_string_input_control[MAX_NAMBER_LANGUAGE][MAX_INDEX_CTRL_INPUT][MAX_COL_LCD + 1] = 
{
  {
    " ������� ������ "
  },
  {
    " ������� ������ "
  },
  {
    "  Input signal  "
  },
  {
    " ������� ������ "
  }
};

const uint8_t information_input_control[MAX_NAMBER_LANGUAGE][2][MAX_COL_LCD + 1] = 
{
  {"   ����������   ", "   ����������   "},
  {"   ���Ҳ����    ", "    �̲����     "},
  {"     DIRECT     ", "   ALTERNATE    "},
  {"   ����������   ", "   ����������   "}
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
    " ������ �.����� "
  },
  {
    " ������ �.����� "
  },
  {
    " BIN Tolerance  "
  },
  {
    " ������ �.����� "
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
  " �.��.          ",
  " �.��.          ",
  " DI             ",
  " �.��.          "
};
const unsigned int first_index_number_input[MAX_NAMBER_LANGUAGE] = {6, 6, 3, 6};

const uint8_t name_string_labels[MAX_NAMBER_LANGUAGE][MAX_ROW_LABELS_M2][MAX_COL_LCD + 1] = 
{
  {
    " ����� ������.  ",
    " ����� �������� "
  },
  {
    " ̳��� ������.  ",
    " ̳��� ������.  "
  },
  {
    " Configur.Mark  ",
    " Settings Mark  "
  },
  {
    " ����� ������.  ",
    " ����� �������� "
  }
};

const uint8_t name_string_list_settings[MAX_NAMBER_LANGUAGE][MAX_ROW_LIST_SETTINGS_M2][MAX_COL_LCD + 1] = 
{
  {
    " ������������   ",
    " ������������.  ",
    " ��������       ",
    " ����           ",
    " ������������   ",
    " ������         "
  },
  {
    " ������������   ",
    " �������������� ",
    " ��������       ",
    " ����           ",
    " ����������    ",
    " �����         "
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
    " ������������   ",
    " ������������.  ",
    " ��������       ",
    " ����           ",
    " ������������   ",
    " ������         "
  }
};

const uint8_t name_stringlist_settings_param[MAX_NAMBER_LANGUAGE][MAX_ROW_LIST_SETTINGS_PARAM_M2][MAX_COL_LCD + 1] = 
{
  {
    " �.�����        ",
    " �.����         ",
    " ���������������",
    " ���            ",
    " ���            ",
    " �������        ",
    " ���            "
  },
  {
    " �.�����        ",
    " �.����         ",
    " �������������",
    " ���            ",
    " ���            ",
    " �������        ",
    " ���            "
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
    " �.�����        ",
    " �.����         ",
    " ���������������",
    " ���            ",
    " ���            ",
    " �������        ",
    " ���            "
  }
};

const uint8_t name_string_list_settings_param_info[MAX_NAMBER_LANGUAGE][2][MAX_COL_LCD + 1] = 
{
  {
    "  �� ���������� ",
    "  � ����������  "
  },
  {
    "  �� ������   ",
    "   � �������   "
  },
  {
    " LN are absent  ",
    "   in device    "
  },
  {
    " �� ����������  ",
    "  � ����������  "
  }
};

const uint8_t name_log[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
{
  " �.�������      ",
  " �.����        ",
  " Ev.Log         ",
  " �.�������      "
};
const unsigned int first_index_number_log[MAX_NAMBER_LANGUAGE] = {10, 8, 7, 10};

const uint8_t name_string_main[MAX_NAMBER_LANGUAGE][MAX_ROW_MAIN_M2][MAX_COL_LCD + 1] = 
{
  {
   " ����           ",
   " ���������      ",
   " �����-������   ",
   " ������������   ",
   " ���������      ",
   " �����������    ",
   " ����� �������� ",
   " ������ �� � �� "
  },
  {
   " ��������       ",
   " ����������    ",
   " �����-������   ",
   " ����������    ",
   " ������������   ",
   " ĳ���������    ",
   " ̳��� ������.  ",
   " ����� �� � �� "
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
   " ��f��          ",
   " �����          ",
   " ʳ��-��f��    ",
   " ҳ��������    ",
   " �������       ",
   " �����������    ",
   " ����� �������� ",
   " ������ �� � �� "
  }
};

const uint8_t name_string_meander_delay[MAX_NAMBER_LANGUAGE][MAX_INDEX_DELAY_MEANDER][MAX_COL_LCD + 1] = 
{
  {
    "     ������     "
  },
  {
    "     �����     "
  },
  {
    "     Period     "
  },
  {
    "     ������     "
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
  " ���            ",
  " ���            ",
  " PSG            ",
  " ���            "
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
    "  ����./����.   ",
    "   ����./���.   ",
    " ���-��/���-����",
    "   ������� 1    ",
    "   ������� 2    "
  },
  {
    "  ����./���.   ",
    "   ����./���.   ",
    " ���-��/���-����",
    "   ������� 1    ",
    "   ������� 2    "
  },
  {
    "  Norm./Trig.   ",
    "  Const./Imp.   ",
    "  Imp-S/Imp-Ex  ",
    "   Frequency 1  ",
    "   Frequency 2  "
  },
  {
    "   ���./����.   ",
    "   ����./���.   ",
    " ���-��/���-����",
    "   ������� 1    ",
    "   ������� 2    "
  }
};

const uint8_t information_output_led_control_N_T[MAX_NAMBER_LANGUAGE][2][MAX_COL_LCD + 1] = 
{
  {"   ����������   ", "   ����������   "},
  {"   ����������   ", "   ��ȥ�����    "},
  {"     NORMAL     ", "    TRIGGER     "},
  {"   ����������   ", "   ����������   "}
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
  {"   ����������   ", "   ����������   "},
  {"   ���Ҳ����    ", "   ����������   "},
  {"    CONSTANT    ", "    IMPULSE     "},
  {"   ����������   ", "   ����������   "},
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
  {"  ���.�������   ", " ���.�����������"},
  {"  ���.�������   ", " ���.���������� "},
  {"   IMP.SIMPLE   ", "  IMP.EXPANDED  "},
  {"  ���.�������   ", " ���.�����������"},
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
  {"���             "},
  {"���             "},
  {"MEANDER         "},
  {"���             "},
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
  " �.����         ",
  " �.����         ",
  " DO             ",
  " �.����         "
};
const uint32_t first_index_number_output[MAX_NAMBER_LANGUAGE] = {7, 7, 3, 7};

const uint8_t name_led[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
{
  " ��.            ",
  " ��.            ",
  " LED            ",
  " ��.            "
};
const uint32_t first_index_number_led[MAX_NAMBER_LANGUAGE] = {4, 4, 4, 4};

const uint8_t name_string_level_password_1[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
{
  " ������� ������:",
  " ������ ������:",
  " Enter password:",
  " ������� ������:"
};

const uint8_t name_string_level_password_2[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
{
  "  ����� ������: ",
  "  ����� ������: ",
  "  New password: ",
  "  ����� ������: "
};

const uint8_t password_item_level_password[MAX_ROW_LIST_PASSWORDS_M2][MAX_NAMBER_LANGUAGE][2][MAX_COL_LCD + 1] = 
{
  {
    {" ����� ������ 1 ", " ���.������ 1   "},
    {" ���� ������ 1 ", " ���.������ 1   "},
    {" Pass.1 Change  ", " Password 1 Set "},
    {" ����� ������ 1 ", " ���.������ 1   "}
  },
  {
    {" ����� ������ 2 ", " ���.������ 2   "},
    {" ���� ������ 2 ", " ���.������ 2   "},
    {" Pass.2 Change  ", " Password 2 Set "},
    {" ����� ������ 2 ", " ���.������ 2   "}
  },
};

const uint8_t name_string_registrators[MAX_NAMBER_LANGUAGE][MAX_ROW_LIST_REGISTRATORS_M2][MAX_COL_LCD + 1] = 
{
  {
    " ������ ������� ",
    " ����� ��������."
  },
  {
    " ������ ����   ",
    " ����� �������."
  },
  {
    " Event Log      ",
    " Diagn.Archive  "
  },
  {
    " ������ ������� ",
    " ����� ��������."
  }
};

const uint8_t information_no_records[MAX_NAMBER_LANGUAGE][2][MAX_COL_LCD + 1] = 
{
  {
    "      ���       ",
    "    �������     "
  },
  {
    "     ����       ",
    "    ������     "
  },
  {
    "    Records     ",
    "   are absent   "
  },
  {
    "      ���       ",
    "    �������     "
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
  {"����.", "���. "},
  {"���. ", "���. "},
  {"Pass.", "Act. "},
  {"����.", "���. "}
};

const uint8_t info_data_corrupted[MAX_NAMBER_LANGUAGE][2][MAX_COL_LCD + 1] = 
{
  {
    "     ������     ",
    "   ����������   "
  },
  {
    "      ���      ",
    "   ���������   "
  },
  {
    "      Data      ",
    " are corrupted  "
  },
  {
    "     ������     ",
    "   ����������   "
  }
};

const uint8_t information_timeout[MAX_NAMBER_LANGUAGE][2][MAX_COL_LCD + 1] = 
{
  {
   "    Time-out    ",
   " �������� ����� "
  },
  {
   "    Time-out    ",
   " ���������� ���."
  },
  {
   "    Time-out    ",
   "    is over     "
  },
  {
   "    Time-out    ",
   " �������� ����� "
  }
};

const uint8_t name_string_language[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_VIEW_SETTING_LANGUAGE][MAX_COL_LCD + 1] = 
{
  "      ����      ",
  "      ����      ",
  "    Language    ",
  "      ����      "
};

uint8_t information_language[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
{
  "    �������     ",
  "   ���������   ",
  "    English     ",
  "     �����      "
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
  " �              ",
  " �              ",
  " AND            ",
  " �              "
};
const uint32_t first_index_number_and[MAX_NAMBER_LANGUAGE] = {2, 2, 4, 2};

const uint8_t name_or[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
{
  " ���            ",
  " ���            ",
  " OR             ",
  " ���            "
};
const uint32_t first_index_number_or[MAX_NAMBER_LANGUAGE] = {4, 4, 3, 4};

const uint8_t name_xor[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
{
  " ����.���       ",
  " ����.���       ",
  " XOR            ",
  " ����.���       "
};
const uint32_t first_index_number_xor[MAX_NAMBER_LANGUAGE] = {9, 9, 4, 9};

const uint8_t name_not[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
{
    " ��             ",
    " ��             ",
    " NOT            ",
    " ��             ",
};
const uint32_t first_index_number_not[MAX_NAMBER_LANGUAGE] = {3, 3, 4, 3};

const uint8_t name_string_inputs_outputs[MAX_NAMBER_LANGUAGE][MAX_ROW_INPUT_OUTPUT_M2][MAX_COL_LCD + 1] = 
{
  {
    " ����.���       ",
    " ����.������    ",
    " ����.�������   "
  },
  {
    " ���� ���       ",
    " ���� �����    ",
    " ���� ������   "
  },
  {
    " Inputs G.Alarms",
    " Inputs state   ",
    " Outputs state  "
  },
  {
    " ����.���       ",
    " ʳ�� ��f����  ",
    " ��f�� ��f����  "
  }
};

const uint8_t name_string_timer_delay[MAX_NAMBER_LANGUAGE][TIMER_SET_DELAYS][MAX_COL_LCD + 1] = 
{
  {
    "  ������ �����  ",
    " ������ ������  "
  },
  {
    "  ������ �����  ",
    " ������ ������  "
  },
  {
    "  Pause Timer   ",
    " Operation Timer"
  },
  {
    "  ������ �����  ",
    " ������ ������  "
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
  " ��-������      ",
  " ��-������      ",
  " MF-Timer       ",
  " ��-������      "
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
 " D-�������      ",
 " D-�����       ",
 " D-Trigger      ",
 " D-�������      "
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
 " ��             ",
 " ��             ",
 " TC             ",
 " ��             "
};
const uint32_t first_index_number_tu[MAX_NAMBER_LANGUAGE] = {3, 3, 3, 3};

const uint8_t name_ts_in_signals[MAX_NAMBER_LANGUAGE][TS_SIGNALS_IN][MAX_COL_LCD + 1] =
{
  {NAME_TS_IN_SIGNALS_RU},  
  {NAME_TS_IN_SIGNALS_UA},  
  {NAME_TS_IN_SIGNALS_EN},  
  {NAME_TS_IN_SIGNALS_KZ}
};

const uint8_t name_ts_out_signals[MAX_NAMBER_LANGUAGE][TS_SIGNALS_OUT][MAX_COL_LCD + 1] =
{
  {NAME_TS_OUT_SIGNALS_RU},  
  {NAME_TS_OUT_SIGNALS_UA},  
  {NAME_TS_OUT_SIGNALS_EN},  
  {NAME_TS_OUT_SIGNALS_KZ}
};

const uint8_t name_ts[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
{
 " ��             ",
 " ��             ",
 " TS             ",
 " ��             "
};
const uint32_t first_index_number_ts[MAX_NAMBER_LANGUAGE] = {3, 3, 3, 3};

#endif
