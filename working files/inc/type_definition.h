#ifndef __TYPE_DEFINITION__
#define __TYPE_DEFINITION__

#define SRAM1 _Pragma("location=\"variables_RAM1\"")

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
  RPEDE_DATA_CHANGED_WRONG_RETURN_BAD,
};

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
Дискретний вхід
**********/
typedef struct
{
  int32_t delay;
  
} __delays_for_INPUT;

typedef struct
{
  
  __delays_for_INPUT delay;
  uint32_t control;
  
} __settings_for_INPUT;

typedef struct
{
  __settings_for_INPUT settings;
  
  __delays_for_INPUT delay;
  uint8_t active_state[DIV_TO_HIGHER(INPUT_SIGNALS, 8)];
  uint8_t trigger_state[DIV_TO_HIGHER(INPUT_SIGNALS, 8)];

} __LN_INPUT;
/**********/

/**********
Дискретний вхід (Реле)
**********/
typedef struct
{
  
  uint32_t control;
  uint32_t param[OUTPUT_MAX_NUMBER];
  
} __settings_for_OUTPUT;

typedef struct
{
  __settings_for_OUTPUT settings;

  uint8_t active_state[DIV_TO_HIGHER(OUTPUT_SIGNALS, 8)];
  uint8_t trigger_state[DIV_TO_HIGHER(OUTPUT_SIGNALS, 8)];

} __LN_OUTPUT;
/**********/

/**********
Світлоіндикатор
**********/

typedef struct
{
  
  uint32_t control;
  uint32_t param[LED_MAX_NUMBER];
  
} __settings_for_LED;

typedef struct
{
  __settings_for_LED settings;

  uint8_t active_state[DIV_TO_HIGHER(LED_SIGNALS, 8)];
  uint8_t trigger_state[DIV_TO_HIGHER(LED_SIGNALS, 8)];

} __LN_LED;
/**********/

/**********
Елемент стандартної логіки "І"
**********/
typedef struct
{
  
  uint32_t param[NUMBER_IN_AND];
  
} __settings_for_AND;

typedef struct
{
  __settings_for_AND settings;

  uint8_t active_state[DIV_TO_HIGHER(AND_SIGNALS, 8)];
  uint8_t trigger_state[DIV_TO_HIGHER(AND_SIGNALS, 8)];

} __LN_AND;
/**********/

/**********
Елемент стандартної логіки "АБО"
**********/
typedef struct
{
  
  uint32_t param[NUMBER_IN_OR];
  
} __settings_for_OR;

typedef struct
{
  
  __settings_for_OR settings;

  uint8_t active_state[DIV_TO_HIGHER(OR_SIGNALS, 8)];
  uint8_t trigger_state[DIV_TO_HIGHER(OR_SIGNALS, 8)];
  
} __LN_OR;
/**********/

/**********
Елемент стандартної логіки "Викл.АБО"
**********/
typedef struct
{
  
  uint32_t param[2];
  
} __settings_for_XOR;

typedef struct
{
  __settings_for_XOR settings;
  
  uint8_t active_state[DIV_TO_HIGHER(XOR_SIGNALS, 8)];
  uint8_t trigger_state[DIV_TO_HIGHER(XOR_SIGNALS, 8)];
  
} __LN_XOR;
/**********/

/**********
Елемент стандартної логіки "НЕ"
**********/
typedef struct
{
  
  uint32_t param;
  
} __settings_for_NOT;

typedef struct
{
  
  __settings_for_NOT settings;
  
  uint8_t active_state[DIV_TO_HIGHER(NOT_SIGNALS, 8)];
  uint8_t trigger_state[DIV_TO_HIGHER(NOT_SIGNALS, 8)];
  
} __LN_NOT;
/**********/

/**********
Багатофункціональний таймер
**********/
typedef struct
{
  int32_t delay_pause;
  int32_t delay_work;
  
} __delays_for_TIMER;

typedef struct
{
  
  uint32_t param[TIMER_MAX_NUMBER];
  uint32_t control;
  __delays_for_TIMER delay;
  
} __settings_for_TIMER;

typedef struct
{
  
  __settings_for_TIMER settings;
  
  __delays_for_TIMER delay;
  uint8_t active_state[DIV_TO_HIGHER(TIMER_SIGNALS, 8)];
  uint8_t trigger_state[DIV_TO_HIGHER(TIMER_SIGNALS, 8)];
  
} __LN_TIMER;
/**********/

/**********
Триґер
**********/
typedef struct
{
  
  uint32_t param[INPUT_TRIGGER_SIGNALS];
  
} __settings_for_TRIGGER;

typedef struct
{
  
  __settings_for_TRIGGER settings;
  
  uint8_t active_state[DIV_TO_HIGHER(TRIGGER_SIGNALS, 8)];
  uint8_t trigger_state[DIV_TO_HIGHER(TRIGGER_SIGNALS, 8)];
  
} __LN_TRIGGER;
/**********/

/**********
Функціональний блок "Генератор періодичного сигналу"
**********/
typedef struct
{
  int32_t delay;
  
} __delays_for_MEANDER;

typedef struct
{
  
  __delays_for_MEANDER delay;
  
} __settings_for_MEANDER;

typedef struct
{
  
  __settings_for_MEANDER settings;
  
  __delays_for_MEANDER delay;
  uint8_t active_state[DIV_TO_HIGHER(MEANDER_SIGNALS, 8)];
  
} __LN_MEANDER;
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
  DYN_MEM_NO_ENOUGH_MEM,
  DYN_MEM_SELECT_OK
    
} __result_dym_mem_select;

/**********
Конфігурація
**********/
typedef struct
{
  uint32_t device_id;                   //Тип пристрою
  
  uint32_t n_input;                     //Кількість дискретних входів
  uint32_t n_output;                    //Кількість дискретних виходів
  uint32_t n_led;                       //Кількість дискретних світлоіндикаторів
  
  uint32_t n_and;                       //Кількість елементів "І"
  uint32_t n_or;                        //Кількість елементів "АБО"
  uint32_t n_xor;                       //Кількість елементів "Викл.АБО"
  uint32_t n_not;                       //Кількість елементів "НЕ"
  uint32_t n_timer;                     //Кількість таймерів
  uint32_t n_trigger;                   //Кількість триґерів

  uint32_t n_meander;                   //Кількість генераторів меандру
  uint32_t n_alarm;                     //Кількість блоків сигналізацій
  uint32_t n_ctrl_analog_inputs;        //Ввімк./Вимк. Контролю приростів струмів


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
  
  unsigned char time_setpoints[7+1];                            //Час останніх змін уставок-витримок-управління
                                                                //Останній байт масиву сигналізує мітку звідки зміни були проведені
                                                                //0 - мінімальні параметри
                                                                //1 - клавіатура
                                                                //2 - USB
                                                                //3 - RS-485
  
} __SETTINGS_FIX;
/**********/

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
  unsigned int next_address;
  unsigned int saving_execution;
  unsigned int number_records;
} __INFO_REJESTRATOR;

typedef struct
{
  unsigned int state_execution;     //стан виконуваної заразоперації
  
  unsigned int code_operation;      //Код виконуваної операції

} __DRIVER_SPI_DF;

typedef enum __STATE_READING_ADCs {
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

typedef struct
{
  unsigned int present;
  int start_index;
  int stop_index;
  int number_per_index;
  int real_number;
} EL_FILTER_STRUCT;

#endif
