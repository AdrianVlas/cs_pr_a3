#ifndef __TYPE_DEFINITION__
#define __TYPE_DEFINITION__

#define SRAM1 _Pragma("location=\"variables_RAM1\"")

typedef enum _id_fb  __id_fb;

typedef struct
{
  enum _menu2_levels current_level;   //Текучий рівень відображуваного екрану
  uint16_t number_selection;          //Номер вибраного елементу (функціонального блоку, паролю...)
  
  int16_t index_position;             //Вказує на якій ми зараз є позиції

  int16_t position_cursor_x;          //X - координата курсору
  int16_t position_cursor_y;          //Y - координата курсору
  
  int *p_max_row;                     //Вказівник на максимальну кількість рядків
  int max_row;                        //Максимальна кількість рядків
  
  void (*func_move)(unsigned int, int);                                 //Вказівник на функцію, для переміщення по вибраному меню  
  void (*func_show)(void);                                              //Вказівник на функцію, для відображення вибраного меню  
  enum _result_pressed_enter_during_edition (*func_press_enter)(void);  //Вказівник на функцію, для виконання дії по натискуванні кнопки Enter
  void (*func_press_esc)(void);                                         //Вказівник на функцію, для виконання дії по натискуванні кнопки Esc
  void (*func_change)(unsigned int);                                    //Вказівник на функцію, для зміни занчення вибраної позиції у вибраному меню
  
  unsigned int binary_data;           //1 - екран відображення бінарної інформації/0 - екран відображення небінарної інформації
  
  enum _edition_stats edition;
  
  unsigned int cursor_on;             //1 - курсор відображається/ 0 - курсор не відображається
  unsigned int cursor_blinking_on;    //1 - курсор мигає/ 0 - курсор не мигає
  
  unsigned int current_action;        //Дія яку треба виконати з текучим екраном
                                      //0 - Нічого не виконувати
                                      //1 - Перемістити курсор, ш/або змінити стан його відображення
                                      //2 - Повністю обновити інформацію
}__CURRENT_STATE_MENU2;

typedef struct
{
  int position_cursor_x;              //X - координата курсору

  unsigned int cursor_on;             //1 - курсор відображається/ 0 - курсор не відображається
  unsigned int cursor_blinking_on;    //1 - курсор мигає/ 0 - курсор не мигає
} __PREVIOUS_STATE_CURSOR;

/**********
Конфігурація
**********/
typedef struct
{
  uint32_t device_id;                   //Тип пристрою
  
  uint32_t n_input;                     //Кількість дискретних входів
  uint32_t n_output;                    //Кількість дискретних виходів
  uint32_t n_led;                       //Кількість дискретних світлоіндикаторів
  uint32_t n_button;                    //Кількість ФК
  
  uint32_t n_alarm;                     //Кількість блоків сигналізацій
  uint32_t n_group_alarm;               //Контроль приростів струмів
  uint32_t n_and;                       //Кількість елементів "І"
  uint32_t n_or;                        //Кількість елементів "АБО"
  uint32_t n_xor;                       //Кількість елементів "Викл.АБО"
  uint32_t n_not;                       //Кількість елементів "НЕ"
  uint32_t n_timer;                     //Кількість таймерів
  uint32_t n_trigger;                   //Кількість триґерів

  uint32_t n_meander;                   //Кількість генераторів меандру

  uint32_t n_tu;                        //Кількість ТУ
  uint32_t n_ts;                        //Кількість ТС

  uint32_t n_input_GOOSE_block;         //Кількість Вх.GOOSE блоків
  uint32_t n_input_MMS_block;           //Кількість Вх.MMS блоків
  uint32_t n_network_output_block;      //Кількість Мережевих вихідних блоків
  
  uint32_t n_log;                       //Кількість субмодулів Журналу подій

  uint8_t time_config[7+1];       //Час останніх змін уставок-витримок-управління
                                        //Останній байт масиву сигналізує мітку звідки зміни були проведені
                                        //0 - мінімальні параметри
                                        //1 - клавіатура
                                        //2 - USB
                                        //3 - RS-485
  
} __CONFIG;
/**********/

/**********
Налаштування, які завжди присутні у даному тппі пристрою
**********/
typedef struct
{
  uint32_t n_iteration;                                         //Кількість ітерацій для пошуку стаціонарного стану
  uint32_t param[FIX_BLOCK_SIGNALS_IN];                         //Сигнали на входах
  
  uint32_t password_1;                                          //Пароль для проглядання з меню
  uint32_t password_2;                                          //Пароль для редагування з меню
  uint32_t timeout_deactivation_password_interface_USB;         //Час деактивації паролю для редагування з інтерфейсу USB
  uint32_t password_interface_USB;                              //Пароль для редагування з інтерфейсу USB
  uint32_t timeout_deactivation_password_interface_RS485;       //Час деактивації паролю для редагування з інтерфейсу RS485
  uint32_t password_interface_RS485;                             //Пароль для редагування з інтерфейсу RS485
  
  uint32_t timeout_idle_new_settings;
  
  //Комунікація
  uint8_t name_of_cell[MAX_CHAR_IN_NAME_OF_CELL];              //І'мя ячейки
  uint16_t user_register[(M_ADDRESS_LAST_USER_REGISTER_DATA - M_ADDRESS_FIRST_USER_REGISTER_DATA) + 1]; //Регістри користувача
  uint32_t address;                                             //Адреса
  int32_t baud_RS485;                                           //швидкість обміну
                                                                // 0 - 9600
                                                                // 1 - 14400
                                                                // 2 - 19200
                                                                // 3 - 28800
                                                                // 4 - 38400
                                                                // 5 - 57600
                                                                // 6 - 115200
  int32_t pare_bit_RS485;                                       //паритет
                                                                // 0 - NONE
                                                                // 1 - ODD
                                                                // 2 - EVEN
  int32_t number_stop_bit_RS485;                                //кількість стоп-біт
                                                                // 0 - 1 stop-bit
                                                                // 1 - 2 stop-bits
  uint32_t time_out_1_RS485;                                    //time-out наступного символу = X/10 символу
  
  int32_t language;                                             //мова меню  0= змінна мов не підтримується; 1=RU; 2=UA; 3=EN; 4=KZ; 5=др.

  //IPv4
  uint16_t IPv4[4];                                             //XXX.XXX.XXX.XXX Можна б було обійтися типом в один байт, але для редагування може виходити число 999, тому я вибрав двобайтний тип
  uint32_t mask;                                                //XX
  uint16_t gateway[4];                                          //XXX.XXX.XXX.XXX Можна б було обійтися типом в один байт, але для редагування може виходити число 999, тому я вибрав двобайтний тип
  
  uint16_t schematic;                                           //Схема
                                                                /*
                                                                Молодший байт
                                                                0 - Не модифікована
                                                                1 - Модифікована

                                                                Старший байт
                                                                0 - Основа  - Мінімальні налаштування
                                                                1 - Основа - Схема 1
                                                                2 - Основа - Схема 2
                                                                3 - Основа - Схема 3
                                                                4 - Основа - Схема 4
                                                                ...
                                                                */
  
  uint8_t time_setpoints[7+1];                                  //Час останніх змін уставок-витримок-управління
                                                                //Останній байт масиву сигналізує мітку звідки зміни були проведені
                                                                //0 - мінімальні параметри
                                                                //1 - клавіатура
                                                                //2 - USB
                                                                //3 - RS-485

  uint8_t time_schematic[7+1];                                  //Час останніх змін зв'язків між елементами
                                                                //Останній байт масиву сигналізує мітку звідки зміни були проведені
                                                                //0 - мінімальні параметри
                                                                //1 - клавіатура
                                                                //2 - USB
                                                                //3 - RS-485
  
} __SETTINGS_FIX;
/**********/

/**********
Дискретний вхід
**********/
typedef struct
{
  int32_t _n;
  int32_t _link;
  
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
Дискретний вихід (Реле)+ Світлоіндикатор
**********/
typedef struct
{
  int32_t _n;
  int32_t _link;
  
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
ФК
**********/
typedef struct
{
  int32_t _n;
  int32_t _link;
  
} __settings_for_BUTTON;

typedef struct
{
  __settings_for_BUTTON settings;
  
  uint8_t active_state[DIV_TO_HIGHER(BUTTON_SIGNALS_OUT, 8)];
  
  uint8_t internal_input[DIV_TO_HIGHER(BUTTON_SIGNALS_INT_IN, 8)];

} __LN_BUTTON;
/**********/

/**********
Світлозвукова сигналізація
**********/
typedef struct
{
  int32_t _n;
  int32_t _link;
  
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
ШГС
**********/
typedef struct
{
  int32_t _n;
  int32_t _link;
  
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
  
  uint32_t NNC_before; /*попередній стан NNC*/

} __LN_GROUP_ALARM;
/**********/

/**********
Елемент стандартної логіки "І"
**********/
typedef struct
{
  int32_t _n;
  int32_t _link;
  
  uint32_t param[AND_SIGNALS_IN];
  
} __settings_for_AND;

typedef struct
{
  __settings_for_AND settings;

  uint8_t active_state[DIV_TO_HIGHER(STANDARD_LOGIC_SIGNALS_OUT, 8)];

} __LN_AND;
/**********/

/**********
Елемент стандартної логіки "АБО"
**********/
typedef struct
{
  int32_t _n;
  int32_t _link;
  
  uint32_t param[OR_SIGNALS_IN];
  
} __settings_for_OR;

typedef struct
{
  
  __settings_for_OR settings;

  uint8_t active_state[DIV_TO_HIGHER(STANDARD_LOGIC_SIGNALS_OUT, 8)];
  
} __LN_OR;
/**********/

/**********
Елемент стандартної логіки "Викл.АБО"
**********/
typedef struct
{
  int32_t _n;
  int32_t _link;
  
  uint32_t param[2];
  
} __settings_for_XOR;

typedef struct
{
  __settings_for_XOR settings;
  
  uint8_t active_state[DIV_TO_HIGHER(STANDARD_LOGIC_SIGNALS_OUT, 8)];
  
} __LN_XOR;
/**********/

/**********
Елемент стандартної логіки "НЕ"
**********/
typedef struct
{
  int32_t _n;
  int32_t _link;
  
  uint32_t param[1];
  
} __settings_for_NOT;

typedef struct
{
  
  __settings_for_NOT settings;
  
  uint8_t active_state[DIV_TO_HIGHER(STANDARD_LOGIC_SIGNALS_OUT, 8)];
  
} __LN_NOT;
/**********/

/**********
Багатофункціональний таймер
**********/
typedef struct
{
  int32_t _n;
  int32_t _link;
  
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
Триґер
**********/
typedef struct
{
  int32_t _n;
  int32_t _link;
  
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
Функціональний блок "Генератор періодичного сигналу"
**********/
typedef struct
{
  int32_t _n;
  int32_t _link;
  
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
Функціональний блок "ТУ"
**********/
typedef struct
{
  int32_t _n;
  int32_t _link;
  
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
Функціональний блок "ТС"
**********/
typedef struct
{
  int32_t _n;
  int32_t _link;
  
  uint32_t param[TS_SIGNALS_IN];
  
} __settings_for_TS;

typedef struct
{
  
  __settings_for_TS settings;
  
  uint8_t active_state[DIV_TO_HIGHER(TS_SIGNALS_OUT, 8)];
  uint8_t add_input_state[DIV_TO_HIGHER(TS_SIGNALS_ADD_INPUT, 8)];
  
  uint8_t internal_input[DIV_TO_HIGHER(TS_SIGNALS_INT_IN, 8)];

} __LN_TS;
/**********/

/**********
Функціональний блок "Вх.GOOSE блок"
**********/
typedef struct
{
  uint32_t param[INPUT_GOOSE_BLOCK_SIGNALS_IN];
  
} __settings_for_INPUT_GOOSE_BLOCK;

typedef struct
{
  
  __settings_for_INPUT_GOOSE_BLOCK settings;
  
  uint8_t active_state[DIV_TO_HIGHER(INPUT_GOOSE_BLOCK_SIGNALS_OUT, 8)];

  uint8_t internal_input[DIV_TO_HIGHER(INPUT_GOOSE_BLOCK_SIGNALS_INT_IN, 8)];
  uint8_t internal_input_ctrl[DIV_TO_HIGHER(INPUT_GOOSE_BLOCK_SIGNALS_INT_IN, 8)];

} __LN_INPUT_GOOSE_BLOCK;
/**********/

/**********
Функціональний блок "Вх.MMS блок"
**********/
typedef struct
{
  uint32_t param[INPUT_MMS_BLOCK_SIGNALS_IN];
  
} __settings_for_INPUT_MMS_BLOCK;

typedef struct
{
  
  __settings_for_INPUT_MMS_BLOCK settings;
  
  uint8_t active_state[DIV_TO_HIGHER(INPUT_MMS_BLOCK_SIGNALS_OUT, 8)];

  uint8_t internal_input[DIV_TO_HIGHER(INPUT_MMS_BLOCK_SIGNALS_INT_IN, 8)];
  uint8_t internal_input_ctrl[DIV_TO_HIGHER(INPUT_MMS_BLOCK_SIGNALS_INT_IN, 8)];

} __LN_INPUT_MMS_BLOCK;
/**********/

/**********
Функціональний блок "Мережевий вихідний блок"
**********/
typedef struct
{
  uint32_t param[NETWORK_OUTPUT_BLOCK_SIGNALS_IN];
  
} __settings_for_NETWORK_OUTPUT_BLOCK;

typedef struct
{
  
  __settings_for_NETWORK_OUTPUT_BLOCK settings;
  
  uint8_t active_state[DIV_TO_HIGHER(NETWORK_OUTPUT_BLOCK_SIGNALS_OUT, 8)];

} __LN_NETWORK_OUTPUT_BLOCK;
/**********/

/**********
Журнал подій
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
  //Стан обміну
  int16_t state_execution;        //-1 - драйвер готовий до початку нових транзакцій
                              // 0 - відбувається обмін
                              // 1 - обмін завершений без помилок
                              // 2 - обмін завершений з помилками
  
  
  //Ідентифікатор пристрою, з яким ведетьсяобмін
  int16_t device_id;              //-1 - пристрій не визначений
                              // EEPROM_ADDRESS - EEPROM
                              // RTC_ADDRESS - RTC
  //Код операції
  int16_t action;                 //-1 - не визначений
                              // 0 - запис адреси для подальшого зчитування
                              // 1 - зчитування
                              // 2 - запис адреси і запис даних
  

  //Внутрішня адреса по якій буде іти звертання
  uint16_t internal_address;

  //Кількість байт для читання/запису (корисних)
  unsigned int number_bytes;
  
  //Вказівник на буфер (корисний)
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
  int state_execution;     //стан виконуваної заразоперації
  
  unsigned int code_operation;      //Код виконуваної операції

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

typedef struct _control_struct
{
  uint32_t off_on;
  
  uint32_t id;
  const uint8_t *p_ln_name;
  
  uint32_t n;
  uintptr_t size_struct;
  
  uint8_t *p_buffer_tx;
  uintptr_t size_block_tx;
  uint8_t *p_add_data_tx;
  uintptr_t size_add_data_tx;
  
  uint8_t *p_buffer_rx;
  uint8_t *p_buffer_ctrl_rx;
  uintptr_t size_block_rx;
  
} __control_struct;


#endif
