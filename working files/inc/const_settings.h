#ifndef __CONST_SETTINGS__
#define __CONST_SETTINGS__

#define BIT_CHANGED_CONFIGURATION       0
#define MASKA_CHANGED_CONFIGURATION     (1 << BIT_CHANGED_CONFIGURATION)
#define BIT_CHANGED_SETTINGS            1
#define MASKA_CHANGED_SETTINGS          (1 << BIT_CHANGED_SETTINGS)
#define BIT_MENU_LOCKS                  2
#define MASKA_MENU_LOCKS                (1 << BIT_MENU_LOCKS)
#define BIT_USB_LOCKS                   3
#define MASKA_USB_LOCKS                 (1 << BIT_USB_LOCKS)
#define BIT_RS485_LOCKS                 4
#define MASKA_RS485_LOCKS               (1 << BIT_RS485_LOCKS)

#define AND_SIGNALS_IN                  8
#define OR_SIGNALS_IN                   8

#define SFIFT_PARAM_ID                  24
#define SFIFT_PARAM_N                   16
#define SFIFT_PARAM_OUT                 0

#define MASKA_PARAM_ID                  ((1 << (8*sizeof(uint32_t) - SFIFT_PARAM_ID )) - 1)
#define MASKA_PARAM_N                   ((1 << (SFIFT_PARAM_ID     - SFIFT_PARAM_N  )) - 1)
#define MASKA_PARAM_OUT                 ((1 << (SFIFT_PARAM_N      - SFIFT_PARAM_OUT)) - 1)

#define NUMBER_FIX_BLOCKS       (_ID_FB_LAST_FIX - _ID_FB_FIRST_FIX)

#define NUMBER_VAR_BLOCKS_NONE_CHANGED  (_ID_FB_LAST_VAR_NONE_CHANGED - _ID_FB_FIRST_VAR_NONE_CHANGED)
#define NUMBER_VAR_BLOCKS_CHANGED       (_ID_FB_LAST_VAR_CHANGED      - _ID_FB_FIRST_VAR_CHANGED     )

#define NUMBER_VAR_BLOCKS       (NUMBER_VAR_BLOCKS_NONE_CHANGED + NUMBER_VAR_BLOCKS_CHANGED)
#define NUMBER_ALL_BLOCKS       (NUMBER_FIX_BLOCKS + NUMBER_VAR_BLOCKS)

/*
���� ��������� �������
*/
enum _FIX_BLOCK_output_signals 
{
  FIX_BLOCK_DEFECT = 0,
  FIX_BLOCK_AVAR_DEFECT,
  FIX_BLOCK_SETTINGS_LOG_WORK,
  FIX_BLOCK_SETTINGS_CHANGED,
  
  FIX_BLOCK_SIGNALS_OUT
};

enum _FIX_BLOCK_input_signals
{
  FIX_BLOCK_ALARM = 0,
  FIX_BLOCK_MUTE,
  FIX_BLOCK_BLOCK,
  
  FIX_BLOCK_SIGNALS_IN
};
/***/

/*
�������� �����
*/
enum _settings_delay_of_INPUT
{
  INPUT_SET_DELAY_DOPUSK = 0,
  
  INPUT_SET_DELAYS
};

enum _work_delay_of_INPUT
{
  INPUT_WORK_DELAY_DOPUSK = 0,
  
  INPUT_WORK_DELAYS
};

enum __index_ctrl_input
{
  INDEX_CTRL_INPUT_TYPE_SIGNAL = 0,
  
  MAX_INDEX_CTRL_INPUT
};

enum _INPUT_output_signals
{
  INPUT_OUT = 0,
  
  INPUT_SIGNALS_OUT
    
};
/***/

/*
�������� ������+��������������
*/
enum _OUTPUT_LED_output_signals
{
  OUTPUT_LED_OUT = 0,
  
  OUTPUT_LED_SIGNALS_OUT,

  OUTPUT_LED_BOARD = OUTPUT_LED_SIGNALS_OUT,
    
  OUTPUT_LED_SIGNALS_OUT_TOTAL
};

enum _OUTPUT_LED_input_signals
{
  OUTPUT_LED_LOGIC_INPUT = 0,
  OUTPUT_LED_RESET,
  OUTPUT_LED_BL_IMP,
  OUTPUT_LED_MEANDER1_MEANDER2,

  OUTPUT_LED_SIGNALS_IN,
  
  OUTPUT_LED_MEANDER1 = OUTPUT_LED_SIGNALS_IN,
  OUTPUT_LED_MEANDER2,
  
  OUTPUT_LED_SIGNALS_IN_TOTAL
};

enum __index_ctrl_output_led
{
  INDEX_CTRL_OUTPUT_LED_N_T = 0, /*N - normal; T - trigger*/
  INDEX_CTRL_OUTPUT_LED_C_I, /*C - Constant; I - impulse*/
  INDEX_CTRL_OUTPUT_LED_SI_EI, /*SI - simple impulse; EI - expanded impulse*/

  _MAX_INDEX_CTRL_OUTPUT_LED_BITS_SETTINGS,
  
  INDEX_CTRL_OUTPUT_LED_MEANDER1 = _MAX_INDEX_CTRL_OUTPUT_LED_BITS_SETTINGS,
  INDEX_CTRL_OUTPUT_LED_MEANDER2,
  
  MAX_INDEX_CTRL_OUTPUT_LED
};
/***/

/*
��+��
*/
enum _BUTTON_TU_output_signals
{
  BUTTON_TU_OUT = 0,
  
  BUTTON_TU_SIGNALS_OUT
};
/***/

/*
������������ �����������
*/
enum _settings_delay_of_ALARM
{
  ALARM_SET_DELAY_PERIOD = 0,
  
  ALARM_SET_DELAYS
};

enum _work_delay_of_ALARM
{
  ALARM_WORK_DELAY_PERIOD = 0,
  
  ALARM_WORK_DELAYS
};

enum _ALARM_output_signals
{
  ALARM_OUT_ALARM = 0,
  ALARM_OUT_MUTE,
  ALARM_OUT_BLOCK,
  
  ALARM_SIGNALS_OUT
    
};
enum _ALARM_input_signals
{
  ALARM_LOGIC_INPUT = 0,
  ALARM_IN_MUTE,
  ALARM_IN_BLOCK,
  ALARM_RESET,
  
  ALARM_SIGNALS_IN
};

enum __index_ctrl_alarm
{
  _MAX_INDEX_CTRL_ALARM_BITS_SETTINGS = 0,
  
  INDEX_CTRL_ALARM_MODE = _MAX_INDEX_CTRL_ALARM_BITS_SETTINGS,
  
  MAX_INDEX_CTRL_ALARM
};

enum _ALARM_modes
{
  ALARM_MODE_SIMPLE = 0,
  ALARM_MODE_TRIGGER,
  ALARM_MODE_PERIOD,
  
  ALARM_MODES_NUMBER
};
/***/

/*
���
*/
enum _settings_pickup_of_GROUP_ALARM
{
  GROUP_ALARM_PICKUP_DELTA_I = 0,
  
  GROUP_ALARM_PICKUPS
};

enum _settings_delay_of_GROUP_ALARM
{
  GROUP_ALARM_SET_DELAY_DELAY = 0,
  
  GROUP_ALARM_SET_DELAYS
};

enum _work_delay_of_GROUP_ALARM
{
  GROUP_ALARM_WORK_DELAY_DELAY = 0,
  
  GROUP_ALARM_WORK_DELAYS
};

enum _GROUP_ALARM_output_signals
{
  GROUP_ALARM_OUT_NNP = 0,
  GROUP_ALARM_OUT_NNM,
  GROUP_ALARM_OUT_CC,
  GROUP_ALARM_OUT_CE,
  GROUP_ALARM_OUT_OC,
  
  GROUP_ALARM_SIGNALS_OUT
    
};

enum __index_ctrl_group_alarm
{
  INDEX_CTRL_GROUP_ALARM_STATE = 0,
  INDEX_CTRL_GROUP_ALARM_CTRL_STATE,

  _MAX_INDEX_CTRL_GROUP_ALARM_BITS_SETTINGS,
  
  INDEX_CTRL_GROUP_ALARM_I = _MAX_INDEX_CTRL_GROUP_ALARM_BITS_SETTINGS,
  
  MAX_INDEX_CTRL_GROUP_ALARM
};
/***/

/*
"���������� �����" ("�", "���", "����.���", "��")
*/
enum _STANDARD_LOGIC_output_signals
{
  STANDARD_LOGIC_OUT = 0,
  
  STANDARD_LOGIC_SIGNALS_OUT
    
};
/***/

/*
"��-������"
*/
enum _settings_delay_of_TIMER
{
  TIMER_SET_DELAY_PAUSE = 0,
  TIMER_SET_DELAY_WORK,
  
  TIMER_SET_DELAYS
};

enum _work_delay_of_TIMER
{
  TIMER_WORK_DELAY_PAUSE_RISE = 0,
  TIMER_WORK_DELAY_PAUSE_FALL,
  TIMER_WORK_DELAY_WORK_IMPULSE_RISE,
  TIMER_WORK_DELAY_WORK_DELAY_RISE,
  TIMER_WORK_DELAY_WORK_IMPULSE_FALL,
  
  TIMER_WORK_DELAYS
};

enum _TIMER_output_signals
{
  TIMER_OUT_RISE_IMPULSE = 0,
  TIMER_OUT_RISE_DELAY,
  TIMER_OUT_FALL_IMPULSE,
  
  TIMER_SIGNALS_OUT
    
};
enum _TIMER_input_signals
{
  TIMER_LOGIC_INPUT = 0,
  TIMER_RESET,
  
  TIMER_SIGNALS_IN
};
/***/

/*
�����
*/
enum _TRIGGER_output_signals
{
  TRIGGER_OUT = 0,
  TRIGGER_OUT_INV,
  
  TRIGGER_SIGNALS_OUT
    
};

enum _TRIGGER_input_signals
{
  INPUT_TRIGGER_SET = 0,
  INPUT_TRIGGER_RESET,
  INPUT_TRIGGER_D,
  INPUT_TRIGGER_C,
  
  TRIGGER_SIGNALS_IN
    
};
/***/

/*
���
*/
enum _settings_delay_of_MEANDER
{
  MEANDER_SET_DELAY_PERIOD = 0,
  
  MEANDER_SET_DELAYS
};

enum _work_delay_of_MEANDER
{
  MEANDER_WORK_DELAY_PERIOD = 0,
  
  MEANDER_WORK_DELAYS
};

enum _MEANDER_output_signals
{
  MEANDER_OUT = 0,
  
  MEANDER_SIGNALS_OUT
    
};

enum __index_delay_meander
{
  INDEX_DELAY_MEANDER_PERIOD = 0,
  
  MAX_INDEX_DELAY_MEANDER
};
/***/

#endif
