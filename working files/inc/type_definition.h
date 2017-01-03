#ifndef __TYPE_DEFINITION__
#define __TYPE_DEFINITION__

#define SRAM1 _Pragma("location=\"variables_RAM1\"")

typedef struct
{
  int current_level;                  //Текучий рівень відображуваного екрану
 
  int index_position;                 //Вказує на якій ми зараз є позиції

  int position_cursor_x;              //X - координата курсору
  int position_cursor_y;              //Y - координата курсору
  
  unsigned int edition;               //0 - вікно зараз не в режимі редагується;
                                      //1 - вікно зараз в режимі редагування;
                                      //2 - вікно чекає підтвердження редагування
                                      //3 - у вікні виведено повідомлення про те, що під час введення даних була зафіксована помилка величиниданих
  
  unsigned int cursor_on;             //1 - курсор відображається/ 0 - курсор не відображається
  unsigned int cursor_blinking_on;    //1 - курсор мигає/ 0 - курсор не мигає
  
  unsigned int current_action;        //Дія яку треба виконати з текучим екраном
                                      //0 - Нічого не виконувати
                                      //1 - Перемістити курсор, ш/або змінити стан його відображення
                                      //2 - Повністю обновити інформацію

} __CURRENT_EKRAN;

typedef struct
{
  int position_cursor_x;              //X - координата курсору

  unsigned int cursor_on;             //1 - курсор відображається/ 0 - курсор не відображається
  unsigned int cursor_blinking_on;    //1 - курсор мигає/ 0 - курсор не мигає
} __PREVIOUS_STATE_CURSOR;

typedef struct
{
  uint32_t device_id;                   //Тип пристрою
  
  uint32_t n_alarms;                    //Кількість блоків сигналізацій
  uint32_t n_meanders;                  //Кількість генераторів меандру

  uint32_t n_timers;                    //Кількість таймерів
  uint32_t n_triggers;                  //Кількість триґерів
  uint32_t n_and;                       //Кількість елементів "І"
  uint32_t n_or;                        //Кількість елементів "АБО"
  uint32_t n_xor;                       //Кількість елементів "Викл.АБО"
  uint32_t n_not;                       //Кількість елементів "НЕ"
  
} __CONFIG;

typedef struct
{
  //Тип пристрою
  unsigned int device_id;
  
  //Дискретні входи
  unsigned int type_of_input_signal;                   //Тип сигналу дискретного входу 0 - постійний , 1 - змінний
  unsigned int dopusk_dv[NUMBER_INPUTS];              //Допуски ДВ
    
  unsigned int ranguvannja_outputs[N_BIG*NUMBER_OUTPUTS]; //Ранжування дискретних вхиодів
  unsigned int ranguvannja_leds[N_BIG*NUMBER_LEDS];       //Ранжування свіотіндикаторів

  unsigned int ranguvannja_analog_registrator[N_BIG];     //Ранжування аналогового реєстратора
  unsigned int ranguvannja_digital_registrator[N_BIG];    //Ранжування дискретного реєстратора
  
  //Блок сигналізації
  unsigned int ranguvannja_alarms[N_BIG*NUMBER_ALARMS];   //Ранжування cигналізацій
  //Тиша
  unsigned int ranguvannja_silence[N_BIG];      //Ранжування cигналізацій
  //Скидання
  unsigned int ranguvannja_reset[N_BIG];        //Ранжування cигналізацій
  //Тест
  unsigned int ranguvannja_test;                //Ранжування Тесту
  
  unsigned int number_iteration_el;                                             //Максимадбна кількість ітерацій для розширеної логіки
  unsigned int number_defined_df;                                               //Кількість визначуваних функцій у конфігурації приладу
  unsigned int number_defined_dt;                                               //Кількість визначуваних тригерів у конфігурації приладу
  unsigned int number_defined_and;                                              //Кількість визначуваних "І" у конфігурації приладу
  unsigned int number_defined_or;                                               //Кількість визначуваних "АБО" у конфігурації приладу
  unsigned int number_defined_xor;                                              //Кількість визначуваних "Викл.ВБО" у конфігурації приладу
  unsigned int number_defined_not;                                              //Кількість визначуваних "НЕ" у конфігурації приладу

  //Опреділювальні функції
  unsigned int type_df;                                                 //Тип опреділювальної функції
                                                                        //0 - Пряма
                                                                        //1 - Зворотня
  unsigned int timeout_pause_df[NUMBER_DEFINED_FUNCTIONS];              //Час затримки спрацюваня опреділювальної функції
  unsigned int timeout_work_df[NUMBER_DEFINED_FUNCTIONS];               //Час роботи опреділювальної функції
  unsigned int ranguvannja_df[N_BIG*NUMBER_DEFINED_FUNCTIONS];          //Ранжування команд опреділювальниї функцій

  unsigned int ranguvannja_set_dt[N_BIG*NUMBER_DEFINED_TRIGGERS];       //Ранжування прямих команд встановлення опреділювальних триґерів
  unsigned int ranguvannja_reset_dt[N_BIG*NUMBER_DEFINED_TRIGGERS];     //Ранжування прямих команд скидання опреділювальних триґерів

  unsigned int ranguvannja_d_and[N_BIG*NUMBER_DEFINED_AND];                     //Ранжування команд джерел визначуваних "І"
  unsigned int ranguvannja_d_or[N_BIG*NUMBER_DEFINED_OR];                       //Ранжування команд джерел визначуваних "АБО"
  unsigned int ranguvannja_d_xor[N_BIG*NUMBER_DEFINED_XOR];                     //Ранжування команд джерел визначуваних "Викл.АБО"
  unsigned int ranguvannja_d_not[N_BIG*NUMBER_DEFINED_NOT];                     //Ранжування команд джерел визначуваних "НЕ"
  
  unsigned int configuration;         //Конфігурація приладу
  
  //Перевірка фазування
  unsigned int setpoint_ctrl_phase_U;                                           //Уставка UФАЗ
  unsigned int setpoint_ctrl_phase_phi;                                         //Уставка PHIФАЗ
  unsigned int setpoint_ctrl_phase_f;                                           //Уставка FФАЗ
  int timeout_ctrl_phase_U;                                                     //Витримка UФАЗ
  int timeout_ctrl_phase_U_d;                                                   //Витримка UФАЗ подовження
  int timeout_ctrl_phase_phi;                                                   //Витримка PHIФАЗ
  int timeout_ctrl_phase_phi_d;                                                 //Витримка PHIФАЗ подовження
  int timeout_ctrl_phase_f;                                                     //Витримка FФАЗ
  int timeout_ctrl_phase_f_d;                                                   //Витримка FФАЗ подовження
  unsigned int control_ctrl_phase;

  unsigned int password;                                        //Пароль для редагування з меню
  unsigned int timeout_deactivation_password_interface_USB;     //Час деактивації паролю для редагування з інтерфейсу USB
  unsigned int password_interface_USB;                          //Пароль для редагування з інтерфейсу USB
  unsigned int timeout_deactivation_password_interface_RS485;   //Час деактивації паролю для редагування з інтерфейсу RS485
  unsigned int password_interface_RS485;                        //Пароль для редагування з інтерфейсу RS485
  
  unsigned int timeout_idle_new_settings;
  
  //Сигналізація
  int timeout_alarm_sound_period[NUMBER_ALARMS];        //Витримка "Тривалість звукового сигналу"
  unsigned int control_alarm;                           //Поле для управління сигналізаціями
  
  //Аналоговий реєстратор
  unsigned int prefault_number_periods; //Час доаварійного масиву (кількість періодів промислової частоти)
  unsigned int postfault_number_periods;//Час післяарійного масиву (кількість періодів промислової частоти)

  //Комунікація
  unsigned int name_of_cell[MAX_CHAR_IN_NAME_OF_CELL];//І'мя ячейки
  unsigned short int user_register[(M_ADDRESS_LAST_USER_REGISTER_DATA - M_ADDRESS_FIRST_USER_REGISTER_DATA) + 1]; //Регістри користувача
  unsigned int volatile address;                      //Адреса
  int speed_RS485;                                    //швидкість обміну
                                                        // 0 - 9600
                                                        // 1 - 14400
                                                        // 2 - 19200
                                                        // 3 - 28800
                                                        // 4 - 38400
                                                        // 5 - 57600
                                                        // 6 - 115200
  int pare_bit_RS485;                                 //паритет
                                                        // 0 - NONE
                                                        // 1 - ODD
                                                        // 2 - EVEN
  int number_stop_bit_RS485;                          //кількість стоп-біт
                                                        // 0 - 1 stop-bit
                                                        // 1 - 2 stop-bits
  unsigned int time_out_1_RS485;                        //time-out наступного символу = X/10 символу
  
  int language;                                         //мова меню  0= змінна мов не підтримується; 1=RU; 2=UA; 3=EN; 4=KZ; 5=др.
  
  unsigned char time_setpoints[7+1];                     //Час останніх змін уставок-витримок-управління
                                                         //Останній байт масиву сигналізує мітку звідки зміни були проведені
                                                            //0 - мінімальні параметри
                                                            //1 - клавіатура
                                                            //2 - USB
                                                            //3 - RS-485
  
  unsigned char time_ranguvannja[7+1];                    //Час останніх змін ранжування
                                                            //0 - мінімальні параметри
                                                            //1 - клавіатура
                                                            //2 - USB
                                                            //3 - RS-485
} __SETTINGS;

typedef struct
{
  //Стан обміну
  int state_execution;        //-1 - драйвер готовий до початку нових транзакцій
                              // 0 - відбувається обмін
                              // 1 - обмін завершений без помилок
                              // 2 - обмін завершений з помилками
  
  
  //Ідентифікатор пристрою, з яким ведетьсяобмін
  int device_id;              //-1 - пристрій не визначений
                              // EEPROM_ADDRESS - EEPROM
                              // RTC_ADDRESS - RTC
  //Код операції
  int action;                 //-1 - не визначений
                              // 0 - запис адреси для подальшого зчитування
                              // 1 - зчитування
                              // 2 - запис адреси і запис даних
  

  //Внутрішня адреса по якій буде іти звертання
  unsigned int internal_address;

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

typedef struct
{
  unsigned char label_start_record;
  unsigned char time[7]; 
  unsigned char name_of_cell[MAX_CHAR_IN_NAME_OF_CELL];
} __HEADER_AR;

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
