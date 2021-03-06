#ifndef __GLOBAL_VARIABLES_H
#define __GLOBAL_VARIABLES_H

//����������� �������
unsigned int semaphore_adc_irq = false;
unsigned int adc_DATA_VAL_read = false;
unsigned int adc_TEST_VAL_read = false;
unsigned int status_adc_read_work = 0;
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

unsigned int changed_ustuvannja = CHANGED_ETAP_NONE; 
unsigned char crc_ustuvannja;
unsigned int ustuvannja_meas[NUMBER_ANALOG_CANALES], ustuvannja[NUMBER_ANALOG_CANALES], edit_ustuvannja[NUMBER_ANALOG_CANALES];
int32_t ustuvannja_shift_meas[NUMBER_INPUTs_ADCs], ustuvannja_shift[NUMBER_INPUTs_ADCs], ustuvannja_shift_work[NUMBER_INPUTs_ADCs];
int ustuvannja_measure_shift = -1;

uint32_t sqr_current_data[NUMBER_POINT][NUMBER_ANALOG_CANALES];
uint32_t index_array_of_sqr_current_data;
uint32_t bank_sum_sqr_data;
uint64_t sum_sqr_data_irq[NUMBER_ANALOG_CANALES];
uint64_t sum_sqr_data[2][NUMBER_ANALOG_CANALES];

unsigned int semaphore_measure_values_low1 = 0;

unsigned int number_inputs_for_fix_one_second = 0;
unsigned int measurement[NUMBER_ANALOG_CANALES]; 
//unsigned int measurement_high[2][NUMBER_ANALOG_CANALES] , bank_measurement_high = 0; 
unsigned int measurement_middle[NUMBER_ANALOG_CANALES]; 
unsigned int measurement_low[NUMBER_ANALOG_CANALES]; 

const uint32_t alarm_ctrl_patten[MAX_INDEX_CTRL_ALARM][2] = {0, 2};
const uint32_t group_alarm_analog_ctrl_patten[MAX_INDEX_CTRL_GROUP_ALARM - _MAX_INDEX_CTRL_GROUP_ALARM_BITS_SETTINGS][2] = {{0, 8}};
uint8_t fix_block_active_state[DIV_TO_HIGHER(FIX_BLOCK_SIGNALS_OUT, 8)];
unsigned char crc_trg_func, crc_trg_func_ctrl;
uint32_t *diagnostyka_before = NULL;
uint32_t *diagnostyka = NULL;
uint32_t *set_diagnostyka = NULL;
uint32_t *clear_diagnostyka = NULL;
uint32_t *set_diagnostyka_tmp = NULL;
uint32_t *clear_diagnostyka_tmp = NULL;
uint32_t *value_changes_diagnostyka = NULL;
uint32_t *diagnostyka_tmp_high = NULL;
uint32_t *diagnostyka_tmp_low = NULL;
uint32_t ** const diagnostika_arrays[N_DIAGN_ARRAYS] = {
                                                        &diagnostyka_before, 
                                                        &diagnostyka,
                                                        &set_diagnostyka,
                                                        &clear_diagnostyka,
                                                        &set_diagnostyka_tmp,
                                                        &clear_diagnostyka_tmp,
                                                        &value_changes_diagnostyka,
                                                        &diagnostyka_tmp_high,
                                                        &diagnostyka_tmp_low,
                                                       };
__diagnostyka_arrays_located diagnostyka_arrays_located = DIAGN_ARRAYS_NONE;

//SRAM1 int global_timers[MAX_NUMBER_GLOBAL_TIMERS]; //����� ���������� �������

SRAM1 unsigned char working_ekran[MAX_ROW_LCD][MAX_COL_LCD];
SRAM1 uint16_t rewrite_ekran_once_more/* = 0*/;

unsigned int new_state_keyboard = 0;
SRAM1 unsigned char time_set_keyboard[NUMBER_KEY_KEYBOARD];

SRAM1 uint16_t time_rewrite/* = 0*/; //��� ���� ������� ���� ���������� ����������
unsigned int reinit_LCD;

//���� ���� 2
SRAM1 __CURRENT_STATE_MENU2 current_state_menu2;
SRAM1 int16_t position_in_current_level_menu2[MAX_NUMBER_MENU2_LEVEL]; //����� � ����� ���������� ������ ������ �������
SRAM1 enum _menu2_levels previous_level_in_current_level_menu2[MAX_NUMBER_MENU2_LEVEL]; //����� � ����� ���������� �������� ���������� ������� ��� ������ ���� ����
SRAM1 enum _menu2_levels next_level_in_current_level_menu2[MAX_NUMBER_MENU2_LEVEL];    //����� � ����� ���������� �������� ������� ���� �� ������ ������� � ��������� ������
SRAM1 void *p_menu_param_1, *p_menu_param_2;
const size_t array_n_similar_input_signals[NUMBER_ALL_BLOCKS] = 
{
  1, 
  0, 
  1, 
  1, 
  0,
  1, 
  0, 
  AND_SIGNALS_IN, 
  OR_SIGNALS_IN, 
  2, 
  1, 
  1, 
  1, 
  0,
  1,
  1,
  LOG_SIGNALS_IN
};
const unsigned int number_output_signals_logical_nodes[NUMBER_ALL_BLOCKS] = 
{
  FIX_BLOCK_SIGNALS_OUT,
  INPUT_SIGNALS_OUT,
  OUTPUT_LED_SIGNALS_OUT,
  OUTPUT_LED_SIGNALS_OUT,
  BUTTON_SIGNALS_OUT,
  ALARM_SIGNALS_OUT,
  GROUP_ALARM_SIGNALS_OUT,
  STANDARD_LOGIC_SIGNALS_OUT,
  STANDARD_LOGIC_SIGNALS_OUT,
  STANDARD_LOGIC_SIGNALS_OUT,
  STANDARD_LOGIC_SIGNALS_OUT,
  TIMER_SIGNALS_OUT,
  TRIGGER_SIGNALS_OUT,
  MEANDER_SIGNALS_OUT,
  TU_SIGNALS_OUT,
  TS_SIGNALS_OUT,
  EVENT_LOG_SIGNALS_OUT
};

const uint8_t * const array_p_name_out[NUMBER_ALL_BLOCKS] = 
{
  (const uint8_t*)name_fix_block_out_signals, 
  (const uint8_t*)name_input_out_signals, 
  (const uint8_t*)name_output_led_out_signals, 
  (const uint8_t*)name_output_led_out_signals, 
  (const uint8_t*)name_button_out_signals, 
  (const uint8_t*)name_alarm_out_signals, 
  (const uint8_t*)name_group_alarm_out_signals, 
  (const uint8_t*)name_standard_logic_out_signals, 
  (const uint8_t*)name_standard_logic_out_signals, 
  (const uint8_t*)name_standard_logic_out_signals, 
  (const uint8_t*)name_standard_logic_out_signals, 
  (const uint8_t*)name_timer_out_signals, 
  (const uint8_t*)name_trigger_out_signals, 
  (const uint8_t*)name_meander_out_signals,
  (const uint8_t*)name_tu_out_signals,
  (const uint8_t*)name_ts_out_signals,
  (const uint8_t*)name_event_log_out_signals
};


const unsigned int number_input_signals_logical_nodes[NUMBER_ALL_BLOCKS] = 
{
  FIX_BLOCK_SIGNALS_IN,
  0,
  OUTPUT_LED_SIGNALS_IN,
  OUTPUT_LED_SIGNALS_IN,
  0,
  ALARM_SIGNALS_IN,
  0,
  1,
  1,
  1,
  1,
  TIMER_SIGNALS_IN,
  TRIGGER_SIGNALS_IN,
  0,
  TU_SIGNALS_IN,
  TS_SIGNALS_IN,
  0
};

unsigned int restart_device = false;
unsigned int periodical_tasks_TEST_CONFIG = false;
unsigned int periodical_tasks_TEST_SETTINGS = false;
unsigned int periodical_tasks_TEST_USTUVANNJA = false;
unsigned int periodical_tasks_TEST_TRG_FUNC = false;
unsigned int periodical_tasks_TEST_TRG_FUNC_LOCK = false;
unsigned int periodical_tasks_TEST_INFO_REJESTRATOR_LOG = false;
unsigned int periodical_tasks_TEST_INFO_REJESTRATOR_LOG_LOCK = false;
unsigned int periodical_tasks_TEST_INFO_REJESTRATOR_PR_ERR = false;
unsigned int periodical_tasks_TEST_INFO_REJESTRATOR_PR_ERR_LOCK = false;
unsigned int periodical_tasks_TEST_FLASH_MEMORY = false;

const unsigned char odynyci_vymirjuvannja[MAX_NAMBER_LANGUAGE][NUMBER_ODYNYCI_VYMIRJUVANNJA] =
{
  {'�', '�', '�'},
  {'�', '�', '�'},
  {'A', 'V', 's'},
  {'�', '�', '�'}
};

SRAM1 uint16_t fixed_power_down_into_RTC/* = 0*/; 
SRAM1 unsigned char time[7]; 
SRAM1 unsigned char time_copy[7]; 
SRAM1 unsigned char calibration;
SRAM1 unsigned char calibration_copy;
SRAM1 uint16_t copying_time/* = 0*/;
SRAM1 unsigned char time_edit[7]; 
SRAM1 unsigned char calibration_edit;
SRAM1 uint16_t copy_register8_RTC;
SRAM1 int16_t etap_reset_of_bit/* = ETAP_CLEAR_OF_NONE*/;
SRAM1 int16_t etap_settings_test_frequency/* = -1*/;
SRAM1 unsigned char temp_register_rtc[2];

//������������ � ������������
__CONFIG current_config_prt, current_config, current_config_edit;
uintptr_t *spca_of_p_prt[NUMBER_VAR_BLOCKS], *sca_of_p[NUMBER_VAR_BLOCKS], *sca_of_p_edit[NUMBER_VAR_BLOCKS]; /*spca_of_p_prt = settings & protection control array of point for protection; sca_of_p = settings control array of point*/
unsigned char crc_config;

__SETTINGS_FIX settings_fix_prt, settings_fix, settings_fix_edit;
uint8_t crc_settings;
unsigned int config_settings_modified = 0;

//���������� ������ � ������� � �����
unsigned int number_seconds;

//������++
unsigned int restart_resurs_count = 0;
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

SRAM1 short int word_SRAM1;

//I2C
SRAM1 unsigned char Temporaty_I2C_Buffer[SIZE_PAGE_EEPROM + 2];
SRAM1 uint16_t number_busy_state/* = 0*/;
SRAM1 uint16_t type_error_of_exchanging_via_i2c/* = 0*/;
SRAM1 uint16_t low_speed_i2c/* = 0*/;
SRAM1 __DRIVER_I2C driver_i2c;
uint32_t control_i2c_taskes[2]  = {0,0};
SRAM1 uint16_t comparison_writing/* = 0*/; /*�������� �� ������, �� ��� ���������� � ������� ��'���, ������������ �� ������ �� ��� ��������� �������� ���������� ���� �������� ������*/
uint32_t state_i2c_task = MASKA_FOR_BIT(STATE_FIRST_READING_RTC_BIT);
SRAM1 unsigned char read_write_i2c_buffer[SIZE_BUFFER_FOR_EEPROM_EXCHNGE];

//DataFlash
uint8_t RxBuffer_SPI_DF[SIZE_BUFFER_SERIAL_DATAFLASH_DMA];
uint8_t TxBuffer_SPI_DF[SIZE_BUFFER_SERIAL_DATAFLASH_DMA];
uint32_t number_chip_dataflash_exchange = INDEX_DATAFLASH_1;
uint32_t state_execution_spi_df[NUMBER_DATAFLASH_CHIP] = {TRANSACTION_EXECUTING_NONE, TRANSACTION_EXECUTING_NONE};
uint32_t status_register_df[NUMBER_DATAFLASH_CHIP];
uint32_t address_read_write[NUMBER_DATAFLASH_CHIP];
uint32_t number_bytes_read_write[NUMBER_DATAFLASH_CHIP];
uint8_t buffer_serial_DataFlash_read_write[NUMBER_DATAFLASH_CHIP][SIZE_BUFFER_SERIAL_DATAFLASH_READ_WRITE];
const uint32_t size_page_serial_dataflash[NUMBER_DATAFLASH_CHIP] = {SIZE_PAGE_DATAFLASH_1, SIZE_PAGE_DATAFLASH_2};
const uint32_t number_page_serial_dataflash[NUMBER_DATAFLASH_CHIP] = {NUMBER_PAGES_INTO_DATAFLASH_1, NUMBER_PAGES_INTO_DATAFLASH_2};
uint32_t control_spi_df_tasks[NUMBER_DATAFLASH_CHIP] = {0, 0};
volatile uint32_t control_tasks_dataflash = 0;

SRAM1 uint8_t buffer_for_menu_read_record[SIZE_MAX_ONE_RECORD];
SRAM1 uint8_t buffer_for_USB_read_record_log[SIZE_ONE_RECORD_LOG];
SRAM1 uint8_t buffer_for_RS485_read_record_log[SIZE_ONE_RECORD_LOG];
SRAM1 uint8_t buffer_for_USB_read_record_pr_err[SIZE_ONE_RECORD_PR_ERR];
SRAM1 uint8_t buffer_for_RS485_read_record_pr_err[SIZE_ONE_RECORD_PR_ERR];

//������ ����
uint8_t crc_info_rejestrator_log;
__INFO_REJESTRATOR info_rejestrator_log;
uint8_t crc_info_rejestrator_log_ctrl;
__INFO_REJESTRATOR info_rejestrator_log_ctrl;
uint8_t buffer_log_records[SIZE_BUFFER_FOR_LOG];
volatile uint32_t head_fifo_buffer_log_records = 0;
volatile uint32_t tail_fifo_buffer_log_records = 0;
uint32_t log_record_check_ok;
uint8_t log_into_menu_time_label[7];
uint32_t number_record_of_log_into_menu = 0xffffffff;
uint32_t number_record_of_log_into_USB = 0xffffffff;
uint32_t number_record_of_log_into_RS485 = 0xffffffff;

//��������� ���������� �������
uint8_t crc_info_rejestrator_pr_err;
__INFO_REJESTRATOR info_rejestrator_pr_err;
uint8_t crc_info_rejestrator_pr_err_ctrl;
__INFO_REJESTRATOR info_rejestrator_pr_err_ctrl;
uint8_t buffer_pr_err_records[SIZE_BUFFER_FOR_PR_ERR];
volatile uint32_t head_fifo_buffer_pr_err_records = 0;
volatile uint32_t tail_fifo_buffer_pr_err_records = 0;
uint32_t temporary_block_writing_records_pr_err_into_DataFlash = 0;
uint32_t pr_err_record_check_ok;
uint8_t pr_err_into_menu_time_label[7];
uint32_t number_record_of_pr_err_into_menu = 0xffffffff;
uint32_t number_record_of_pr_err_into_USB = 0xffffffff;
uint32_t number_record_of_pr_err_into_RS485 = 0xffffffff;

//������� ���������� �� �����������
uint32_t clean_rejestrators = 0;

//RS-485
SRAM1 unsigned char TxBuffer_RS485[BUFFER_RS485];
SRAM1 unsigned char RxBuffer_RS485[BUFFER_RS485];
int TxBuffer_RS485_count = 0;
int RxBuffer_RS485_count = 0;
int RxBuffer_RS485_count_previous = 0;
uint32_t time_last_receive_byte;
uint32_t max_reaction_time_rs_485 = 0;
SRAM1 uint16_t make_reconfiguration_RS_485/* = 0*/;
SRAM1 uint16_t number_bits_rs_485_waiting/* = 0*/;
SRAM1 uint16_t mark_current_tick_RS_485/* = 0*/;
unsigned int timeout_idle_RS485;
uint32_t test_answer_RS485 = 0;
uint32_t reason_of_restart_RS485 = 0;

//USB
uint8_t  USART_Rx_Buffer[USART_RX_DATA_SIZE]; 
uint32_t USART_Rx_ptr_in = 0;
uint32_t USART_Rx_ptr_out = 0;
uint32_t USART_Rx_length  = 0;

extern uint8_t  USB_Tx_State;

//��� UDP
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
SRAM1 uint32_t registers_address_read/* =0x20000000*/;
SRAM1 uint32_t registers_address_write/* =0x20000000*/;
SRAM1 uint32_t data_write_to_memory;
SRAM1 uint16_t number_registers_read/* = 0*/;
SRAM1 uint16_t registers_values[64]/* @ "variables_RAM1"*/;
SRAM1 uint16_t action_is_continued/* = false*/;
SRAM1 uint16_t part_transmit_carrent_data/* = 0*/;
SRAM1 uint16_t command_to_receive_current_data/* = false*/;
int16_t current_data_transmit[NUMBER_ANALOG_CANALES*NUMBER_POINT*NUMBER_PERIOD_TRANSMIT] /*@ "variables_RAM1"*/; 
SRAM1 volatile uint16_t wait_of_receiving_current_data/*  = false*/; 
SRAM1 uint16_t password_set_USB/* = 1*/, password_set_RS485/* = 1*/;
SRAM1 uint16_t password_changed;
SRAM1 uint16_t password_ustuvannja/* = 0*/;
uint32_t *point_to_edited_rang = NULL;
SRAM1 uint16_t number_32bit_in_target/* = 0*/;
//uint32_t clear_array_rang[N_BIG] = {0, 0, 0, 0, 0, 0, 0};
//uint32_t set_array_rang[N_BIG]   = {0, 0, 0, 0, 0, 0, 0};
SRAM1 uint16_t restart_timeout_interface/* = 0*/;
unsigned int timeout_idle_new_settings;
SRAM1 uint16_t restart_timeout_idle_new_settings/* = 0*/;
SRAM1 uint16_t type_of_settings_changed_from_interface/* = 0*/;

unsigned int serial_number_dev = 0;                         //���������� ����� ��������
unsigned int edit_serial_number_dev;

unsigned int control_word_of_watchdog = 0;
unsigned int test_watchdogs = 0;

//����� ��������� �������
unsigned int total_error;

const uint8_t letters[MAX_NYMBER_EXTENDED_ASCII_SYMBOLS][2] =
{
{ 176, 223 },  //�
{ 178, 73  }, // �
{ 179, 105 }, // �
{ 192, 65  }, // �
{ 193, 160 }, // �
{ 194, 66  }, // �
{ 195, 161 }, // �
{ 196, 224 }, // �
{ 197, 69  }, // �
{ 168, 162 }, // �
{ 198, 163 }, // �
{ 199, 164 }, // �
{ 200, 165 }, // �
{ 201, 166 }, // �
{ 202, 75  }, // �
{ 203, 167 }, // �
{ 204, 77  }, // �
{ 205, 72  }, // �
{ 206, 79  }, // �
{ 207, 168 }, // �
{ 208, 80  }, // �
{ 209, 67  }, // �
{ 210, 84  }, // �
{ 211, 169 }, // �
{ 212, 170 }, // �
{ 213, 88  }, // �
{ 214, 225 }, // �
{ 215, 171 }, // �
{ 216, 172 }, // �
{ 217, 226 }, // �
{ 218, 173 }, // �
{ 220, 98  }, // �
{ 219, 174 }, // �
{ 221, 175 }, // �
{ 222, 176 }, // �
{ 223, 177 }, // �
{ 224, 97  }, // �
{ 225, 178 }, // �
{ 226, 179 }, // �
{ 227, 180 }, // �
{ 228, 227 }, // �
{ 229, 101 }, // �
{ 184, 181 }, // �
{ 230, 182 }, // �
{ 231, 183 }, // �
{ 232, 184 }, // �
{ 233, 185 }, // �
{ 234, 186 }, // �
{ 235, 187 }, // �
{ 236, 188 }, // �
{ 237, 189 }, // �
{ 238, 111 }, // �
{ 239, 190 }, // �
{ 240, 112 }, // �
{ 241, 99  }, // �
{ 242, 191 }, // �
{ 243, 121 }, // �
{ 244, 228 }, // �
{ 245, 120 }, // �
{ 246, 229 }, // �
{ 247, 192 }, // �
{ 248, 193 }, // �
{ 249, 230 }, // �
{ 250, 194 }, // �
{ 252, 196 }, // �
{ 251, 195 }, // �
{ 253, 197 }, // �
{ 254, 198 }, // �
{ 255, 199 } // �
};

const uint8_t extra_letters[MAX_NYMBER_EXTRA_EXTENDED_ASCII_SYMBOLS][1 + MAX_NAMBER_LANGUAGE] =
{
/*CODE   RU    UA    EN    KZ     */  
{ 0xAF, 0xFF, 0x00, 0x00, 0xFF}, // � ��� ������ ���� ����� ��� ��������� ��������� ���������
{ 0xBF, 0xFF, 0x01, 0xFF, 0xFF}, // �
{ 0xA5, 0xFF, 0x02, 0xFF, 0xFF}, // �
{ 0xB4, 0xFF, 0x03, 0xFF, 0xFF}, // �
{ 0xAA, 0xFF, 0x04, 0xFF, 0xFF}, // �
{ 0xBA, 0xFF, 0x05, 0xFF, 0xFF}, // �
{ 0x8A, 0xFF, 0xFF, 0xFF, 0x00}, // � - ������� ������ � ����� ����� ��� WIN1251
{ 0x9A, 0xFF, 0xFF, 0xFF, 0x01}, // � - ������� ������ � ����� ����� ��� WIN1251
{ 0xBD, 0xFF, 0xFF, 0xFF, 0x02}, // � - ������� ������ � ����� ����� ��� WIN1251
{ 0xBE, 0xFF, 0xFF, 0xFF, 0x03}, // � - ������� ������ � ����� ����� ��� WIN1251
{ 0x80, 0xFF, 0xFF, 0xFF, 0x04}, // � - ������� ������ � ����� ����� ��� WIN1251
{ 0x90, 0xFF, 0xFF, 0xFF, 0x05},  // � - ������� ������ � ����� ����� ��� WIN1251
{ 0x89, 0x00, 0x06, 0x01, 0x06}  // � - ������� ������ � ����� ����� ��� WIN1251
};

int current_language = LANGUAGE_ABSENT;

extern unsigned short const __checksum;
extern unsigned int __checksum_begin;
extern unsigned int __checksum_end;

extern unsigned int __ICFEDIT_region_RAM1_start__;
extern unsigned int __ICFEDIT_region_RAM1_size__;

#ifdef DEBUG_TEST
//unsigned int time_1 = 0xffff0000, time_2 = 0xffff0000, max_delay = 0;

//�������� �����
//unsigned int temp_value_for_debbuging_1 = 0;
//unsigned int temp_value_for_debbuging_2 = 0;
//unsigned int temp_value_for_debbuging_3 = 0;


#endif


#endif
