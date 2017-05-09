#ifndef __CONST_EDITOR_LOGICAL_NODES_MENU2__
#define __CONST_EDITOR_LOGICAL_NODES_MENU2__

#define MAX_ROW_FOR_EDITOR_LIST_LOGICAL_NODES                   NUMBER_ALL_BLOCKS

enum _index_editor_list_logical_nodes_m2
{
  INDEX_EDITOR_LIST_LOGICAL_NODES_M2_CONTROL_BLOCK = 0,
  INDEX_EDITOR_LIST_LOGICAL_NODES_M2_INPUTS,
  INDEX_EDITOR_LIST_LOGICAL_NODES_M2_OUTPUTS,
  INDEX_EDITOR_LIST_LOGICAL_NODES_M2_LEDS,
  INDEX_EDITOR_LIST_LOGICAL_NODES_M2_BUTTON,
  INDEX_EDITOR_LIST_LOGICAL_NODES_M2_ALARM,
  INDEX_EDITOR_LIST_LOGICAL_NODES_M2_GROUP_ALARMS,
  INDEX_EDITOR_LIST_LOGICAL_NODES_M2_ANDS,
  INDEX_EDITOR_LIST_LOGICAL_NODES_M2_ORS,
  INDEX_EDITOR_LIST_LOGICAL_NODES_M2_XORS,
  INDEX_EDITOR_LIST_LOGICAL_NODES_M2_NOTS,
  INDEX_EDITOR_LIST_LOGICAL_NODES_M2_TIMERS,
  INDEX_EDITOR_LIST_LOGICAL_NODES_M2_TRIGGERS,
  INDEX_EDITOR_LIST_LOGICAL_NODES_M2_MEANDERS,
  INDEX_EDITOR_LIST_LOGICAL_NODES_M2_TU,
  INDEX_EDITOR_LIST_LOGICAL_NODES_M2_LOG,
  
  MAX_ROW_EDITOR_LIST_LOGICAL_NODES_M2
};

//const uint8_t name_f_blocks[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_EDITOR_LIST_LOGICAL_NODES][MAX_COL_LCD + 1] = 
//{
//  {
//    "                ",
//    "Д.Вх            ",
//    "В.Р             ",
//    "Св              ",
//    "ФК              ",
//    "СЗС             ",
//    "ШГС             ",
//    "И               ",
//    "ИЛИ             ",
//    "И-ИЛИ           ",
//    "НЕ              ",
//    "МФТ             ",
//    "D-Тр            ",
//    "ГПС             ",
//    "ТУ              ",
//    "Ж.Cобытий       "
//  },
//  {
//    "                ",
//    "Д.Вх            ",
//    "В.Р             ",
//    "Св              ",
//    "ФК              ",
//    "СЗС             ",
//    "ШГС             ",
//    "І               ",
//    "АБО             ",
//    "В.АБО           ",
//    "НЕ              ",
//    "БФТ             ",
//    "D-Тр            ",
//    "ГПС             ",
//    "ТУ              ",
//    "Ж.Подій         "
//  },
//  {
//    "                ",
//    "D.In            ",
//    "O.R             ",
//    "LED             ",
//    "DB              ",
//    "СЗС             ",
//    "ШГС             ",
//    "AND             ",
//    "OR              ",
//    "XOR             ",
//    "NOT             ",
//    "MFT             ",
//    "D-Tr            ",
//    "PSG             ",
//    "TC              ",
//    "Ev.Log          "
//  },
//  {
//    "                ",
//    "Д.Вх            ",
//    "В.Р             ",
//    "Св              ",
//    "ФК              ",
//    "СЗС             ",
//    "ШГС             ",
//    "И               ",
//    "ИЛИ             ",
//    "И-ИЛИ           ",
//    "НЕ              ",
//    "МФТ             ",
//    "D-Тр            ",
//    "ГПС             ",
//    "ТУ              ",
//    "Ж.Событий       "
//  }
//};
//
//const uint8_t name_string_editor_logical_nodes[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_EDITOR_LIST_LOGICAL_NODES][MAX_COL_LCD + 1] = 
//{
//  {
//    " Общий блок     ",
//    " Д.Входы        ",
//    " В.Реле         ",
//    " Светоиндикаторы",
//    " ФК             ",
//    " СЗС            ",
//    " ШГС            ",
//    " И              ",
//    " ИЛИ            ",
//    " Искл.ИЛИ       ",
//    " НЕ             ",
//    " МФ-Таймер      ",
//    " D-Триггер      ",
//    " ГПС            ",
//    " ТУ             ",
//    " Ж.Событий      "
//  },
//  {
//    " Загальний блок ",
//    " Д.Входи        ",
//    " В.Реле         ",
//    " Світоіндикатори",
//    " ФК             ",
//    " СЗС            ",
//    " ШГС            ",
//    " І              ",
//    " АБО            ",
//    " Викл.АБО       ",
//    " НЕ             ",
//    " БФ-Таймер      ",
//    " D-Триґер       ",
//    " ГПС            ",
//    " ТУ             ",
//    " Ж.Подій        "
//  },
//  {
//    " General block  ",
//    " D.Inputs       ",
//    " O.Relays       ",
//    " LEDs           ",
//    " DB             ",
//    " СЗС            ",
//    " ШГС            ",
//    " AND            ",
//    " OR             ",
//    " XOR            ",
//    " NOT            ",
//    " MF-Timer       ",
//    " D-Trigger      ",
//    " PSG            ",
//    " TC             ",
//    " Ev.Log         "
//  },
//  {
//    " Общий блок     ",
//    " Д.Входы        ",
//    " В.Реле         ",
//    " Светоиндикаторы",
//    " ФК             ",
//    " СЗС            ",
//    " ШГС            ",
//    " И              ",
//    " ИЛИ            ",
//    " Искл.ИЛИ       ",
//    " НЕ             ",
//    " МФ-Таймер      ",
//    " D-Триггер      ",
//    " ГПС            ",
//    " ТУ             ",
//    " Ж.Событий      "
//  }
//};

#endif

//extern const uint8_t name_f_blocks[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_EDITOR_LIST_LOGICAL_NODES][MAX_COL_LCD + 1];
//extern const uint8_t name_string_editor_logical_nodes[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_EDITOR_LIST_LOGICAL_NODES][MAX_COL_LCD + 1];
