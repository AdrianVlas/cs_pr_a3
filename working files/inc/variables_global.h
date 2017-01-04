#ifndef __GLOBAL_VARIABLES_H
#define __GLOBAL_VARIABLES_H

//Вимірювальна система
volatile unsigned int semaphore_adc_irq = false;
volatile unsigned int adc_DATA_VAL_read = false;
volatile unsigned int adc_TEST_VAL_read = false;
volatile unsigned int status_adc_read_work = 0;
const unsigned int input_adc[NUMBER_INPUTs_ADCs][2]={
                                                     {1,0x8370},
                                                     {1,0x8770},
                                                     {1,0x8b70},
                                                     {1,0x8f70},
                                                     {1,0x9370},
                                                     {1,0x9770},
                                                     {1,0x9b70},
                                                     {1,0x9f70},
                                                     {1,0xa370},
                                                     {1,0xa770},
                                                     {1,0xab70},
                                                     {1,0xaf70},
                                                     {1,0xb370},
                                                     {1,0xb770},
                                                     {1,0xbb70},
                                                     {1,0xbf70}
                                                    };
EXTENDED_OUTPUT_DATA output_adc[NUMBER_INPUTs_ADCs];

unsigned int command_word_adc = 0, command_word_adc_work = 0, active_index_command_word_adc = 0;
unsigned int state_reading_ADCs = STATE_READING_ADCs_NONE;

uint32_t previous_tick_VAL = 0;

const unsigned int index_GND_ADC[NUMBER_GND_ADC] = {C_GND_ADC_1, C_GND_ADC_2, C_GND_ADC_3, C_GND_ADC_4, C_GND_ADC_5};
unsigned int gnd_adc_moment_value[NUMBER_GND_ADC][NUMBER_POINT];
unsigned int gnd_adc_averange_sum[NUMBER_GND_ADC];
unsigned int gnd_adc_averange[NUMBER_GND_ADC];
unsigned int gnd_adc;

unsigned int vref_adc_moment_value[NUMBER_POINT];
unsigned int vref_adc_averange_sum = VREF_NORMAL_VALUE*NUMBER_POINT;
unsigned int vref_adc = VREF_NORMAL_VALUE;

unsigned int vdd_adc_moment_value[NUMBER_POINT];
unsigned int vdd_adc_averange_sum = VDD_NORMAL_VALUE*NUMBER_POINT;
unsigned int vdd_adc = VDD_NORMAL_VALUE;

unsigned int index_array_of_one_value = 0;

EXTENDED_SAMPLE ADCs_data_raw[NUMBER_ANALOG_CANALES];
int ADCs_data[NUMBER_ANALOG_CANALES];
int current_data[NUMBER_ANALOG_CANALES*NUMBER_POINT*NUMBER_PERIOD_TRANSMIT];
unsigned int index_array_of_current_data_value = 0;

volatile unsigned int changed_ustuvannja = CHANGED_ETAP_NONE; 
unsigned char crc_ustuvannja;
unsigned int ustuvannja_meas[NUMBER_ANALOG_CANALES], ustuvannja[NUMBER_ANALOG_CANALES], edit_ustuvannja[NUMBER_ANALOG_CANALES];

uint32_t sqr_current_data[NUMBER_POINT][NUMBER_ANALOG_CANALES];
uint32_t index_array_of_sqr_current_data;
uint32_t bank_sum_sqr_data;
uint64_t sum_sqr_data_irq[NUMBER_ANALOG_CANALES];
uint64_t sum_sqr_data[2][NUMBER_ANALOG_CANALES];

volatile unsigned int semaphore_measure_values_low1 = 0;

unsigned int number_inputs_for_fix_one_second = 0;
volatile unsigned int measurement[NUMBER_ANALOG_CANALES]; 
unsigned int measurement_high[2][NUMBER_ANALOG_CANALES] , bank_measurement_high = 0; 
unsigned int measurement_middle[NUMBER_ANALOG_CANALES]; 
unsigned int measurement_low[NUMBER_ANALOG_CANALES]; 

volatile unsigned int state_inputs = 0; //"є сигнал " - відповідає встановленому біту (1); "немає сигналу" - відповідає скинутому біту (0)
unsigned int state_outputs = 0;
volatile unsigned int state_leds = 0;
volatile unsigned int active_functions[N_BIG]  = {0, 0, 0, 0, 0, 0, 0};
unsigned int trigger_active_functions[N_BIG]  = {0, 0, 0, 0, 0, 0, 0}, trigger_active_functions_ctrl[N_BIG];
unsigned char crc_trg_func, crc_trg_func_ctrl;
volatile unsigned int trigger_functions_USB[N_BIG] = {0, 0, 0, 0, 0, 0, 0};
volatile unsigned int trigger_functions_RS485[N_BIG] = {0, 0, 0, 0, 0, 0, 0};
unsigned int copying_active_functions = 0;
volatile unsigned int active_functions_copy[N_BIG]  = {0, 0, 0, 0, 0, 0, 0};
volatile unsigned int active_functions_trg[N_BIG]  = {0, 0, 0, 0, 0, 0, 0};
unsigned int pressed_buttons = 0;
volatile unsigned int activation_function_from_interface = 0;
volatile unsigned int reset_trigger_function_from_interface = 0;
unsigned int diagnostyka_before[3] = {0, 0, 0};
volatile unsigned int diagnostyka[3] = {0, 0, 0};
volatile unsigned int set_diagnostyka[3] = {0, 0, 0};
volatile unsigned int clear_diagnostyka[3] = {0, 0, 0};

int global_timers[MAX_NUMBER_GLOBAL_TIMERS]; //Масив глобальних таймерів
unsigned int timer_meander = 0;
unsigned int output_timer_meander = false;
unsigned int etap_execution_df[NUMBER_DEFINED_FUNCTIONS]; //Етап виконання опреділюваної функції

unsigned char working_ekran[MAX_ROW_LCD][MAX_COL_LCD];
unsigned int rewrite_ekran_once_more = 0;

volatile unsigned int new_state_keyboard = 0;
unsigned char time_set_keyboard[NUMBER_KEY_KEYBOARD];

unsigned int time_rewrite = 0; //Час який пройшов після останнього обновлення

__CURRENT_EKRAN current_ekran;
int position_in_current_level_menu[MAX_LEVEL_MENU]; //Масив у якому збкрігається індекс текучоїпозиції
int previous_level_in_current_level_menu[MAX_LEVEL_MENU]; //Масив у якому збкрігається занчення попередніх екранів для даного рівня меню

volatile unsigned int periodical_tasks_TEST_CONFIG = false;
volatile unsigned int periodical_tasks_TEST_SETTINGS = false;
volatile unsigned int periodical_tasks_TEST_USTUVANNJA = false;
volatile unsigned int periodical_tasks_TEST_TRG_FUNC = false;
volatile unsigned int periodical_tasks_TEST_TRG_FUNC_LOCK = false;
volatile unsigned int periodical_tasks_TEST_INFO_REJESTRATOR_AR = false;
volatile unsigned int periodical_tasks_TEST_INFO_REJESTRATOR_AR_LOCK = false;
volatile unsigned int periodical_tasks_TEST_INFO_REJESTRATOR_DR = false;
volatile unsigned int periodical_tasks_TEST_INFO_REJESTRATOR_DR_LOCK = false;
volatile unsigned int periodical_tasks_TEST_INFO_REJESTRATOR_PR_ERR = false;
volatile unsigned int periodical_tasks_TEST_INFO_REJESTRATOR_PR_ERR_LOCK = false;
volatile unsigned int periodical_tasks_TEST_FLASH_MEMORY = false;

const unsigned char odynyci_vymirjuvannja[MAX_NAMBER_LANGUAGE][NUMBER_ODYNYCI_VYMIRJUVANNJA] =
{
  {'А', 'В', '°', 'с'},
  {'А', 'В', '°', 'с'},
  {'A', 'V', '°', 's'},
  {'А', 'В', '°', 'с'}
};

unsigned int fixed_power_down_into_RTC = 0; 
unsigned char time[7]; 
unsigned char time_copy[7]; 
unsigned char calibration;
unsigned char calibration_copy;
unsigned int copying_time = 0;
unsigned char time_edit[7]; 
unsigned char calibration_edit;
unsigned int copy_register8_RTC;
int etap_reset_of_bit = ETAP_CLEAR_OF_NONE;
int etap_settings_test_frequency = -1;
unsigned char temp_register_rtc[2];

//Налаштування
__CONFIG current_config[3]; //0-1 це стуктура для захистів-структура контейнер; 2 для редагування
size_t intex_current_config;
volatile unsigned int changed_config = CHANGED_ETAP_NONE; 
unsigned char crc_config;

volatile unsigned int changed_settings = CHANGED_ETAP_NONE; 
unsigned char crc_settings;
__SETTINGS current_settings_prt, current_settings, edition_settings, current_settings_interfaces;

//Ресурс++
volatile unsigned int restart_resurs_count = 0;
unsigned int resurs_temp = 0;
unsigned int resurs_global = 0;
unsigned int resurs_global_min;
unsigned int resurs_global_max = 0;

unsigned int restart_timing_watchdog = 0;
unsigned int time_1_watchdog_input = 0;
unsigned int time_2_watchdog_input = 0;
unsigned int time_delta_watchdog_input = 0;
unsigned int time_delta_watchdog_input_min = 0xffff*10;
unsigned int time_delta_watchdog_input_max = 0;

unsigned int time_1_watchdog_output = 0;
unsigned int time_2_watchdog_output = 0;
unsigned int time_delta_watchdog_output = 0;
unsigned int time_delta_watchdog_output_min = 0xffff*10;
unsigned int time_delta_watchdog_output_max = 0;


//I2C
unsigned char Temporaty_I2C_Buffer[SIZE_PAGE_EEPROM + 2];
unsigned int number_busy_state = 0;
unsigned int type_error_of_exchanging_via_i2c = 0;
unsigned int low_speed_i2c = 0;
__DRIVER_I2C driver_i2c;
unsigned int control_i2c_taskes[2]  = {0,0};
unsigned int comparison_writing = 0; /*очищений біт означає, що іде зчитування у робочий об'єкт, встановлений біт означає що іде порівняння записаної інформації після операції запису*/
unsigned int state_i2c_task = STATE_FIRST_READING_RTC;
unsigned char read_write_i2c_buffer[SIZE_BUFFER_FOR_EEPROM_EXCHNGE];

//DataFlash
unsigned char RxBuffer_SPI_DF[SIZE_PAGE_DATAFLASH_MAX + 10];
unsigned char TxBuffer_SPI_DF[SIZE_PAGE_DATAFLASH_MAX + 10];
unsigned int number_bytes_transfer_spi_df;
unsigned int number_bytes_transfer_spi_df_copy;
unsigned char TxBuffer_SPI_DF_copy[SIZE_PAGE_DATAFLASH_MAX + 10];
unsigned int code_operation_copy;
int number_chip_dataflsh_exchange = -1;
__DRIVER_SPI_DF driver_spi_df[NUMBER_DATAFLASH_CHIP] = {
                                                        {TRANSACTION_EXECUTING_NONE, CODE_OPERATION_NONE},
                                                        {TRANSACTION_EXECUTING_NONE, CODE_OPERATION_NONE}
                                                       };
volatile unsigned int error_into_spi_df = 0;/*Ненульве значення означає, що зафіксована помилка при прийом/передачі через SPI_DF*/
unsigned int dataflash_not_busy = 0;
volatile unsigned int control_tasks_dataflash = 0;
unsigned char buffer_for_manu_read_record[SIZE_BUFFER_FOR_DR_RECORD];
unsigned char buffer_for_USB_read_record_ar[SIZE_PAGE_DATAFLASH_2];
unsigned char buffer_for_RS485_read_record_ar[SIZE_PAGE_DATAFLASH_2];
unsigned char buffer_for_USB_read_record_dr[SIZE_BUFFER_FOR_DR_RECORD];
unsigned char buffer_for_RS485_read_record_dr[SIZE_BUFFER_FOR_DR_RECORD];
unsigned char buffer_for_USB_read_record_pr_err[SIZE_ONE_RECORD_PR_ERR];
unsigned char buffer_for_RS485_read_record_pr_err[SIZE_ONE_RECORD_PR_ERR];

unsigned int what_we_are_reading_from_dataflash_1;
unsigned int what_we_are_reading_from_dataflash_2;

//Аналоговий реєстратор
unsigned char crc_info_rejestrator_ar;
volatile __INFO_REJESTRATOR info_rejestrator_ar;
unsigned char crc_info_rejestrator_ar_ctrl;
__INFO_REJESTRATOR info_rejestrator_ar_ctrl;
volatile unsigned int size_one_ar_record = 0;
unsigned int number_word_digital_part_ar;
volatile unsigned int max_number_records_ar = 0; //Максимальна кількість записів в аналоговому реєстраторі при вибраних витримках (розраховується з витрмиок доаварійного і післяаварійного часу)
volatile unsigned int semaphore_read_state_ar_record = 0; //Коли цей симафор встановлений, то якщо не йде запис, то новий запис не можна починати, а якщо іде, то можна продовжувати запис
unsigned int continue_previous_record_ar = 0; //Сигналізує, не зняті вще всі джерела запуску аналогового реєстратора після його попе6реднього запуску
volatile int state_ar_record = STATE_AR_NO_RECORD;
SRAM1 short int array_ar[SIZE_BUFFER_FOR_AR];
SRAM1 short int word_SRAM1;
unsigned int index_array_ar_current = 0;
volatile unsigned int index_array_ar_heat;
volatile unsigned int index_array_ar_tail;
unsigned int prescaler_ar = 0; //Потрібний для того, щоб з 32 виборок на секунду зробити 16 виборки на секунду
__HEADER_AR header_ar;
unsigned char buffer_for_save_ar_record[SIZE_PAGE_DATAFLASH_2];
unsigned int temporary_address_ar;
volatile unsigned int count_to_save;
volatile unsigned int permit_copy_new_data;
unsigned int copied_number_samples, total_number_samples;
unsigned int etap_writing_part_page_ar_into_dataflash = ETAP_NONE;
unsigned int number_record_of_ar_for_menu = 0xffff; //Це число означає, що номер запису не вибраний
unsigned int number_record_of_ar_for_USB = 0xffff; //Це число означає, що номер запису не вибраний
unsigned int number_record_of_ar_for_RS485 = 0xffff; //Це число означає, що номер запису не вибраний
int first_number_time_sample_for_USB;// -1 - заголовок запису ан.р.; 0 - перший часовий зріз доаварійного масиву і т.д.
int last_number_time_sample_for_USB;// -1 - заголовок запису ан.р.; 0 - перший часовий зріз доаварійного масиву і т.д.
int first_number_time_sample_for_RS485;// -1 - заголовок запису ан.р.; 0 - перший часовий зріз доаварійного масиву і т.д.
int last_number_time_sample_for_RS485;// -1 - заголовок запису ан.р.; 0 - перший часовий зріз доаварійного масиву і т.д.

//Дискретний реєстратор
unsigned char crc_info_rejestrator_dr;
volatile __INFO_REJESTRATOR info_rejestrator_dr;
unsigned char crc_info_rejestrator_dr_ctrl;
__INFO_REJESTRATOR info_rejestrator_dr_ctrl;
unsigned int state_dr_record = STATE_DR_NO_RECORD;
unsigned int number_records_dr_waiting_for_saving_operation = 0;
unsigned char buffer_for_save_dr_record[SIZE_BUFFER_FOR_DR_RECORD];
unsigned char buffer_for_save_dr_record_level_1[SIZE_BUFFER_FOR_DR_RECORD];
unsigned char buffer_for_save_dr_record_level_2[SIZE_BUFFER_FOR_DR_RECORD];
unsigned int part_writing_dr_into_dataflash;
unsigned int number_record_of_dr_for_menu = 0xffff; //Це число означає, що номер запису не вибраний
unsigned int number_record_of_dr_for_USB = 0xffff; //Це число означає, що номер запису не вибраний
unsigned int number_record_of_dr_for_RS485 = 0xffff; //Це число означає, що номер запису не вибраний
unsigned int part_reading_dr_from_dataflash_for_menu = 0;
unsigned int part_reading_dr_from_dataflash_for_USB = 0;
unsigned int part_reading_dr_from_dataflash_for_RS485 = 0;

//Реєстратор програмних помилок
unsigned char crc_info_rejestrator_pr_err;
volatile __INFO_REJESTRATOR info_rejestrator_pr_err;
unsigned char crc_info_rejestrator_pr_err_ctrl;
__INFO_REJESTRATOR info_rejestrator_pr_err_ctrl;
unsigned char buffer_pr_err_records[SIZE_BUFFER_FOR_PR_ERR];
volatile unsigned int head_fifo_buffer_pr_err_records = 0;
volatile unsigned int tail_fifo_buffer_pr_err_records = 0;
volatile unsigned int temporary_block_writing_records_pr_err_into_DataFlash = 0;
unsigned int etap_writing_pr_err_into_dataflash = ETAP_NONE;
unsigned int number_recods_writing_into_dataflash_now = 0;
unsigned int number_record_of_pr_err_into_menu = 0xffff;
unsigned int number_record_of_pr_err_into_USB = 0xffff;
unsigned int number_record_of_pr_err_into_RS485 = 0xffff;

//Очистка інформації по реєстраторах
volatile unsigned int clean_rejestrators = 0;

//RS-485
unsigned char TxBuffer_RS485[BUFFER_RS485];
unsigned char RxBuffer_RS485[BUFFER_RS485];
int TxBuffer_RS485_count = 0;
int volatile RxBuffer_RS485_count = 0;
int RxBuffer_RS485_count_previous = 0;
unsigned int time_last_receive_byte;
unsigned int max_reaction_time_rs_485 = 0;
unsigned int make_reconfiguration_RS_485 = 0;
volatile unsigned int number_bits_rs_485_waiting = 0;
unsigned int mark_current_tick_RS_485 = 0;
unsigned int timeout_idle_RS485;

//USB
uint8_t  USART_Rx_Buffer[USART_RX_DATA_SIZE]; 
uint32_t USART_Rx_ptr_in = 0;
uint32_t USART_Rx_ptr_out = 0;
uint32_t USART_Rx_length  = 0;

extern uint8_t  USB_Tx_State;

//Для UDP
u32 volatile count_out = 0;
u32 count_out_previous = 0;
uint16_t previous_count_tim4_USB;
u8 buffer_out[BUFFER_USB];
unsigned char usb_received[BUFFER_USB];
unsigned char usb_transmiting[BUFFER_USB];
int usb_received_count = 0;
int usb_transmiting_count = 0;
unsigned char data_usb_transmiting = false;
unsigned int timeout_idle_USB;

//MODBUS-RTU
unsigned int registers_address_read =0x20000000;
unsigned int registers_address_write =0x20000000;
unsigned int data_write_to_memory;
unsigned int number_registers_read = 0;
unsigned short int registers_values[64]/* @ "variables_RAM1"*/;
unsigned int action_is_continued = false;
unsigned int part_transmit_carrent_data = 0;
unsigned int command_to_receive_current_data = false;
int current_data_transmit[NUMBER_ANALOG_CANALES*NUMBER_POINT*NUMBER_PERIOD_TRANSMIT] /*@ "variables_RAM1"*/; 
volatile unsigned int wait_of_receiving_current_data  = false; 
unsigned int password_set_USB = 1, password_set_RS485 = 1;
unsigned int password_changed;
unsigned int password_ustuvannja = 0;
unsigned int *point_to_edited_rang = NULL;
unsigned int number_32bit_in_target = 0;
unsigned int clear_array_rang[N_BIG] = {0, 0, 0, 0, 0, 0, 0};
unsigned int set_array_rang[N_BIG]   = {0, 0, 0, 0, 0, 0, 0};
unsigned int restart_timeout_interface = 0;
unsigned int timeout_idle_new_settings;
unsigned int restart_timeout_idle_new_settings = 0;
unsigned int type_of_settings_changed = 0;

unsigned int serial_number_dev = 0;                         //Заводський номер пристрою
unsigned int edit_serial_number_dev;

volatile unsigned int control_word_of_watchdog = 0;
unsigned int test_watchdogs = 0;

//Змінна глобальної помилки
unsigned int total_error;

const unsigned char letters[69][2] =
{
{ 176, 223 },  //°
{ 178, 73  }, // І
{ 179, 105 }, // і
{ 192, 65  }, // А
{ 193, 160 }, // Б
{ 194, 66  }, // В
{ 195, 161 }, // Г
{ 196, 224 }, // Д
{ 197, 69  }, // Е
{ 168, 162 }, // Ё
{ 198, 163 }, // Ж
{ 199, 164 }, // З
{ 200, 165 }, // И
{ 201, 166 }, // Й
{ 202, 75  }, // К
{ 203, 167 }, // Л
{ 204, 77  }, // М
{ 205, 72  }, // Н
{ 206, 79  }, // О
{ 207, 168 }, // П
{ 208, 80  }, // Р
{ 209, 67  }, // С
{ 210, 84  }, // Т
{ 211, 169 }, // У
{ 212, 170 }, // Ф
{ 213, 88  }, // Х
{ 214, 225 }, // Ц
{ 215, 171 }, // Ч
{ 216, 172 }, // Ш
{ 217, 226 }, // Щ
{ 218, 173 }, // Ъ
{ 220, 98  }, // Ь
{ 219, 174 }, // Ы
{ 221, 175 }, // Э
{ 222, 176 }, // Ю
{ 223, 177 }, // Я
{ 224, 97  }, // а
{ 225, 178 }, // б
{ 226, 179 }, // в
{ 227, 180 }, // г
{ 228, 227 }, // д
{ 229, 101 }, // е
{ 184, 181 }, // ё
{ 230, 182 }, // ж
{ 231, 183 }, // з
{ 232, 184 }, // и
{ 233, 185 }, // й
{ 234, 186 }, // к
{ 235, 187 }, // л
{ 236, 188 }, // м
{ 237, 189 }, // н
{ 238, 111 }, // о
{ 239, 190 }, // п
{ 240, 112 }, // р
{ 241, 99  }, // с
{ 242, 191 }, // т
{ 243, 121 }, // у
{ 244, 228 }, // Ф
{ 245, 120 }, // х
{ 246, 229 }, // ц
{ 247, 192 }, // ч
{ 248, 193 }, // ш
{ 249, 230 }, // щ
{ 250, 194 }, // ъ
{ 252, 196 }, // ь
{ 251, 195 }, // ы
{ 253, 197 }, // э
{ 254, 198 }, // ю
{ 255, 199 } // я
};

const unsigned char extra_letters[12][1 + MAX_NAMBER_LANGUAGE] =
{
/*CODE   RU    UA    EN    KZ     */  
{ 0xAF, 0xFF, 0x00, 0x00, 0xFF}, // Ї або велика біква Омега для англійської розкладки клавіатури
{ 0xBF, 0xFF, 0x01, 0xFF, 0xFF}, // ї
{ 0xA5, 0xFF, 0x02, 0xFF, 0xFF}, // Ґ
{ 0xB4, 0xFF, 0x03, 0xFF, 0xFF}, // ґ
{ 0xAA, 0xFF, 0x04, 0xFF, 0xFF}, // Є
{ 0xBA, 0xFF, 0x05, 0xFF, 0xFF}, // є
{ 0x8A, 0xFF, 0xFF, 0xFF, 0x00}, // Љ - замінний символ з даним кодом для WIN1251
{ 0x9A, 0xFF, 0xFF, 0xFF, 0x01}, // љ - замінний символ з даним кодом для WIN1251
{ 0xBD, 0xFF, 0xFF, 0xFF, 0x02}, // Ѕ - замінний символ з даним кодом для WIN1251
{ 0xBE, 0xFF, 0xFF, 0xFF, 0x03}, // ѕ - замінний символ з даним кодом для WIN1251
{ 0x80, 0xFF, 0xFF, 0xFF, 0x04}, // Ђ - замінний символ з даним кодом для WIN1251
{ 0x90, 0xFF, 0xFF, 0xFF, 0x05}  // ђ - замінний символ з даним кодом для WIN1251
};

int current_language = LANGUAGE_ABSENT;

extern unsigned short const __checksum;
extern unsigned int __checksum_begin;
extern unsigned int __checksum_end;

extern unsigned int __ICFEDIT_region_RAM1_start__;
extern unsigned int __ICFEDIT_region_RAM1_size__;

#ifdef DEBUG_TEST
//unsigned int time_1 = 0xffff0000, time_2 = 0xffff0000, max_delay = 0;

//Тимчасові змінні
//unsigned int temp_value_for_debbuging_1 = 0;
//unsigned int temp_value_for_debbuging_2 = 0;
//unsigned int temp_value_for_debbuging_3 = 0;


#endif


#endif
