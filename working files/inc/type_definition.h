#ifndef __TYPE_DEFINITION__
#define __TYPE_DEFINITION__

#define SRAM1 _Pragma("location=\"variables_RAM1\"")

typedef enum _id_fb  __id_fb;

typedef struct
{
  enum _menu2_levels current_level;   //������� ����� �������������� ������
  uint16_t number_selection;          //����� ��������� �������� (��������������� �����, ������...)
  
  int16_t index_position;             //����� �� ��� �� ����� � �������

  int16_t position_cursor_x;          //X - ���������� �������
  int16_t position_cursor_y;          //Y - ���������� �������
  
  int *p_max_row;                     //�������� �� ����������� ������� �����
  int max_row;                        //����������� ������� �����
  
  void (*func_move)(unsigned int, int);                                 //�������� �� �������, ��� ���������� �� ��������� ����  
  void (*func_show)(void);                                              //�������� �� �������, ��� ����������� ��������� ����  
  enum _result_pressed_enter_during_edition (*func_press_enter)(void);  //�������� �� �������, ��� ��������� 䳿 �� ����������� ������ Enter
  void (*func_press_esc)(void);                                         //�������� �� �������, ��� ��������� 䳿 �� ����������� ������ Esc
  void (*func_change)(unsigned int);                                    //�������� �� �������, ��� ���� �������� ������� ������� � ��������� ����
  
  unsigned int binary_data;           //1 - ����� ����������� ������ ����������/0 - ����� ����������� �������� ����������
  
  enum _edition_stats edition;
  
  unsigned int cursor_on;             //1 - ������ ������������/ 0 - ������ �� ������������
  unsigned int cursor_blinking_on;    //1 - ������ ����/ 0 - ������ �� ����
  
  unsigned int current_action;        //ĳ� ��� ����� �������� � ������� �������
                                      //0 - ͳ���� �� ����������
                                      //1 - ���������� ������, �/��� ������ ���� ���� �����������
                                      //2 - ������� �������� ����������
}__CURRENT_STATE_MENU2;

typedef struct
{
  int position_cursor_x;              //X - ���������� �������

  unsigned int cursor_on;             //1 - ������ ������������/ 0 - ������ �� ������������
  unsigned int cursor_blinking_on;    //1 - ������ ����/ 0 - ������ �� ����
} __PREVIOUS_STATE_CURSOR;

/**********
������������
**********/
typedef struct
{
  uint32_t device_id;                   //��� ��������
  
  uint32_t n_input;                     //ʳ������ ���������� �����
  uint32_t n_output;                    //ʳ������ ���������� ������
  uint32_t n_led;                       //ʳ������ ���������� ��������������
  uint32_t n_button;                    //ʳ������ ��
  
  uint32_t n_alarm;                     //ʳ������ ����� �����������
  uint32_t n_group_alarm;               //�������� �������� ������
  uint32_t n_and;                       //ʳ������ �������� "�"
  uint32_t n_or;                        //ʳ������ �������� "���"
  uint32_t n_xor;                       //ʳ������ �������� "����.���"
  uint32_t n_not;                       //ʳ������ �������� "��"
  uint32_t n_timer;                     //ʳ������ �������
  uint32_t n_trigger;                   //ʳ������ ������

  uint32_t n_meander;                   //ʳ������ ���������� �������

  uint32_t n_tu;                        //ʳ������ ��
  uint32_t n_ts;                        //ʳ������ ��
  
  uint32_t n_log;                       //ʳ������ ��������� ������� ����

  uint8_t time_config[7+1];       //��� ������� ��� �������-��������-���������
                                        //������� ���� ������ �������� ���� ����� ���� ���� ��������
                                        //0 - ������� ���������
                                        //1 - ���������
                                        //2 - USB
                                        //3 - RS-485
  
} __CONFIG;
/**********/

/**********
������������, �� ������ ������� � ������ ��� ��������
**********/
typedef struct
{
  uint32_t n_iteration;                                         //ʳ������ �������� ��� ������ ������������� �����
  uint32_t param[FIX_BLOCK_SIGNALS_IN];                         //������� �� ������
  
  uint32_t password_1;                                          //������ ��� ����������� � ����
  uint32_t password_2;                                          //������ ��� ����������� � ����
  uint32_t timeout_deactivation_password_interface_USB;         //��� ����������� ������ ��� ����������� � ���������� USB
  uint32_t password_interface_USB;                              //������ ��� ����������� � ���������� USB
  uint32_t timeout_deactivation_password_interface_RS485;       //��� ����������� ������ ��� ����������� � ���������� RS485
  uint32_t password_interface_RS485;                             //������ ��� ����������� � ���������� RS485
  
  uint32_t timeout_idle_new_settings;
  
  //����������
  uint8_t name_of_cell[MAX_CHAR_IN_NAME_OF_CELL];              //�'�� ������
  uint16_t user_register[(M_ADDRESS_LAST_USER_REGISTER_DATA - M_ADDRESS_FIRST_USER_REGISTER_DATA) + 1]; //������� �����������
  uint32_t address;                                             //������
  int32_t baud_RS485;                                           //�������� �����
                                                                // 0 - 9600
                                                                // 1 - 14400
                                                                // 2 - 19200
                                                                // 3 - 28800
                                                                // 4 - 38400
                                                                // 5 - 57600
                                                                // 6 - 115200
  int32_t pare_bit_RS485;                                       //�������
                                                                // 0 - NONE
                                                                // 1 - ODD
                                                                // 2 - EVEN
  int32_t number_stop_bit_RS485;                                //������� ����-��
                                                                // 0 - 1 stop-bit
                                                                // 1 - 2 stop-bits
  uint32_t time_out_1_RS485;                                    //time-out ���������� ������� = X/10 �������
  
  int32_t language;                                             //���� ����  0= ����� ��� �� �����������; 1=RU; 2=UA; 3=EN; 4=KZ; 5=��.
  
  uint16_t schematic;                                           //�����
                                                                /*
                                                                �������� ����
                                                                0 - �� ������������
                                                                1 - ������������

                                                                ������� ����
                                                                0 - ������  - ̳������ ������������
                                                                1 - ������ - ����� 1
                                                                2 - ������ - ����� 2
                                                                3 - ������ - ����� 3
                                                                4 - ������ - ����� 4
                                                                ...
                                                                */
  
  uint8_t time_setpoints[7+1];                                  //��� ������� ��� �������-��������-���������
                                                                //������� ���� ������ �������� ���� ����� ���� ���� ��������
                                                                //0 - ������� ���������
                                                                //1 - ���������
                                                                //2 - USB
                                                                //3 - RS-485

  uint8_t time_schematic[7+1];                                  //��� ������� ��� ��'���� �� ����������
                                                                //������� ���� ������ �������� ���� ����� ���� ���� ��������
                                                                //0 - ������� ���������
                                                                //1 - ���������
                                                                //2 - USB
                                                                //3 - RS-485
  
} __SETTINGS_FIX;
/**********/

/**********
���������� ����
**********/
typedef struct
{
  
  int32_t set_delay[INPUT_SET_DELAYS];
  uint32_t control;
  
} __settings_for_INPUT;

typedef struct
{
  __settings_for_INPUT settings;
  
//  int32_t work_delay[INPUT_WORK_DELAYS];
  uint8_t active_state[DIV_TO_HIGHER(INPUT_SIGNALS_OUT, 8)];

} __LN_INPUT;
/**********/

/**********
���������� ����� (����)+ �������������
**********/
typedef struct
{
  
  uint32_t control;
  uint32_t param[OUTPUT_LED_SIGNALS_IN_TOTAL];
  
} __settings_for_OUTPUT_LED;

typedef struct
{
  __settings_for_OUTPUT_LED settings;

  uint8_t active_state[DIV_TO_HIGHER(OUTPUT_LED_SIGNALS_OUT_TOTAL, 8)];

  uint8_t d_trigger_state[DIV_TO_HIGHER(OUTPUT_LED_D_TRIGGER_TOTAL, 8)];
  uint8_t d_trigger_state_tmp[DIV_TO_HIGHER(OUTPUT_LED_D_TRIGGER_TOTAL, 8)];

} __LN_OUTPUT_LED;
/**********/

/**********
��
**********/
typedef struct
{
  uint8_t active_state[DIV_TO_HIGHER(BUTTON_SIGNALS_OUT, 8)];
  
  uint8_t internal_input[DIV_TO_HIGHER(BUTTON_SIGNALS_INT_IN, 8)];

} __LN_BUTTON;
/**********/

/**********
������������ �����������
**********/
typedef struct
{
  int32_t set_delay[ALARM_SET_DELAYS];
  uint32_t control;
  uint32_t param[ALARM_SIGNALS_IN];
  
} __settings_for_ALARM;

typedef struct
{
  __settings_for_ALARM settings;

//  int32_t work_delay[ALARM_WORK_DELAYS];
  uint8_t active_state[DIV_TO_HIGHER(ALARM_SIGNALS_OUT, 8)];

  uint8_t d_trigger_state[DIV_TO_HIGHER(ALARM_D_TRIGGER_TOTAL, 8)];
  uint8_t d_trigger_state_tmp[DIV_TO_HIGHER(ALARM_D_TRIGGER_TOTAL, 8)];

} __LN_ALARM;
/**********/

/**********
���
**********/
typedef struct
{
  int32_t pickup[GROUP_ALARM_PICKUPS];
  int32_t set_delay[GROUP_ALARM_SET_DELAYS];
  uint32_t control;
  uint32_t analog_input_control;
  
} __settings_for_GROUP_ALARM;

typedef struct
{
  __settings_for_GROUP_ALARM settings;

//  int32_t work_delay[GROUP_ALARM_WORK_DELAYS];
  uint8_t active_state[DIV_TO_HIGHER(GROUP_ALARM_SIGNALS_OUT, 8)];
  uint32_t NNC; /*New number of Curcuit*/
  
  uint32_t NNC_before; /*��������� ���� NNC*/

} __LN_GROUP_ALARM;
/**********/

/**********
������� ���������� ����� "�"
**********/
typedef struct
{
  
  uint32_t param[AND_SIGNALS_IN];
  
} __settings_for_AND;

typedef struct
{
  __settings_for_AND settings;

  uint8_t active_state[DIV_TO_HIGHER(STANDARD_LOGIC_SIGNALS_OUT, 8)];

} __LN_AND;
/**********/

/**********
������� ���������� ����� "���"
**********/
typedef struct
{
  
  uint32_t param[OR_SIGNALS_IN];
  
} __settings_for_OR;

typedef struct
{
  
  __settings_for_OR settings;

  uint8_t active_state[DIV_TO_HIGHER(STANDARD_LOGIC_SIGNALS_OUT, 8)];
  
} __LN_OR;
/**********/

/**********
������� ���������� ����� "����.���"
**********/
typedef struct
{
  
  uint32_t param[2];
  
} __settings_for_XOR;

typedef struct
{
  __settings_for_XOR settings;
  
  uint8_t active_state[DIV_TO_HIGHER(STANDARD_LOGIC_SIGNALS_OUT, 8)];
  
} __LN_XOR;
/**********/

/**********
������� ���������� ����� "��"
**********/
typedef struct
{
  
  uint32_t param[1];
  
} __settings_for_NOT;

typedef struct
{
  
  __settings_for_NOT settings;
  
  uint8_t active_state[DIV_TO_HIGHER(STANDARD_LOGIC_SIGNALS_OUT, 8)];
  
} __LN_NOT;
/**********/

/**********
�������������������� ������
**********/
typedef struct
{
  
  int32_t set_delay[TIMER_SET_DELAYS];
  uint32_t param[TIMER_SIGNALS_IN];
  
} __settings_for_TIMER;

typedef struct
{
  
  __settings_for_TIMER settings;
  
//  int32_t work_delay[TIMER_WORK_DELAYS];
  uint8_t active_state[DIV_TO_HIGHER(TIMER_SIGNALS_OUT, 8)];
  
} __LN_TIMER;
/**********/

/**********
�����
**********/
typedef struct
{
  
  uint32_t param[TRIGGER_SIGNALS_IN];
  
} __settings_for_TRIGGER;

typedef struct
{
  
  __settings_for_TRIGGER settings;
  
  uint8_t active_state[DIV_TO_HIGHER(TRIGGER_SIGNALS_OUT, 8)];

  uint8_t d_trigger_state[DIV_TO_HIGHER(TRIGGER_D_TRIGGER_TOTAL, 8)];
  uint8_t d_trigger_state_tmp[DIV_TO_HIGHER(TRIGGER_D_TRIGGER_TOTAL, 8)];
  
} __LN_TRIGGER;
/**********/

/**********
�������������� ���� "��������� ����������� �������"
**********/
typedef struct
{
  
  int32_t set_delay[MEANDER_SET_DELAYS];
  
} __settings_for_MEANDER;

typedef struct
{
  
  __settings_for_MEANDER settings;
  
//  int32_t work_delay[MEANDER_WORK_DELAYS];
  uint8_t active_state[DIV_TO_HIGHER(MEANDER_SIGNALS_OUT, 8)];
  
} __LN_MEANDER;
/**********/

/**********
�������������� ���� "��"
**********/
typedef struct
{
  uint32_t param[TU_SIGNALS_IN];
  
} __settings_for_TU;

typedef struct
{
  
  __settings_for_TU settings;
  
  uint8_t active_state[DIV_TO_HIGHER(TU_SIGNALS_OUT, 8)];
  
  uint8_t internal_input[DIV_TO_HIGHER(TU_SIGNALS_INT_IN, 8)];
  
} __LN_TU;
/**********/

/**********
�������������� ���� "��"
**********/
typedef struct
{
  uint32_t param[TS_SIGNALS_IN];
  
} __settings_for_TS;

typedef struct
{
  
  __settings_for_TS settings;
  
  uint8_t active_state[DIV_TO_HIGHER(TS_SIGNALS_OUT, 8)];
  
  uint8_t internal_input[DIV_TO_HIGHER(TS_SIGNALS_INT_IN, 8)];

} __LN_TS;
/**********/

/**********
������ ����
**********/
typedef uint32_t __LOG_INPUT;
//typedef struct
//{
//  
//  uint32_t param[LOG_SIGNALS_IN];
//  
//} __settings_for_LOG;
//
//typedef struct
//{
//  __settings_for_LOG settings;
//  
//} __LN_LOG;
/**********/


typedef enum _action_dyn_mem_select
{
  MAKE_DYN_MEM = 0,
  REMAKE_DYN_MEM,
  RESTORE_DYN_MEM
    
} __action_dym_mem_select;

typedef enum _result_dyn_mem_select
{
  DYN_MEM_TOTAL_ERROR = 0,
  PRT_MEM_ERROR,
  DYN_MEM_NO_ENOUGH_MEM,
  DYN_MEM_SELECT_OK
    
} __result_dym_mem_select;

typedef enum _diagnostyka_arrays_located
{
  DIAGN_ARRAYS_NONE = 0,
  DIAGN_ARRAYS_CHANGING,
  DIAGN_ARRAYS_ERROR,
  DIAGN_ARRAYS_SHORT,
  DIAGN_ARRAYS_ALL

} __diagnostyka_arrays_located;


typedef struct
{
  //���� �����
  int16_t state_execution;        //-1 - ������� ������� �� ������� ����� ����������
                              // 0 - ���������� ����
                              // 1 - ���� ���������� ��� �������
                              // 2 - ���� ���������� � ���������
  
  
  //������������� ��������, � ���� ������������
  int16_t device_id;              //-1 - ������� �� ����������
                              // EEPROM_ADDRESS - EEPROM
                              // RTC_ADDRESS - RTC
  //��� ��������
  int16_t action;                 //-1 - �� ����������
                              // 0 - ����� ������ ��� ���������� ����������
                              // 1 - ����������
                              // 2 - ����� ������ � ����� �����
  

  //�������� ������ �� ��� ���� ��� ���������
  uint16_t internal_address;

  //ʳ������ ���� ��� �������/������ (��������)
  unsigned int number_bytes;
  
  //�������� �� ����� (��������)
  uint8_t volatile* point_buffer;

} __DRIVER_I2C;

typedef struct
{
  uint32_t next_address;
  uint32_t previous_address;
  uint32_t number_records;
} __INFO_REJESTRATOR;

typedef struct
{
  int state_execution;     //���� ���������� �������������
  
  unsigned int code_operation;      //��� ���������� ��������

} __DRIVER_SPI_DF;

typedef enum __STATE_READING_ADCs 
{
  STATE_READING_ADCs_NONE = 0,
  STATE_READING_WRITE,
  STATE_READING_WRITE_READ,
  STATE_READING_READ
} STATE_READING_ADCs;

typedef struct
{
  uint32_t tick;
  unsigned int value;

} EXTENDED_OUTPUT_DATA;

typedef struct
{
  uint32_t tick;
  int value;
} EXTENDED_SAMPLE;

typedef enum _getting_data
{
  GET_DATA_FOR_EDITING = 0,
  GET_DATA_IMMEDITATE
} __getting_data;

typedef enum _setting_data
{
  SET_DATA_INTO_EDIT_TABLE = 0,
  SET_DATA_IMMEDITATE
} __settings_data;

typedef enum _bit_byte
{
  BIT_REQUEST = 0,
  BYTE_REQUEST
    
} __bit_byte;

#endif
