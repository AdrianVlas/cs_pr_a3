#ifndef __EXTERNAL_FUNCTIONS_H
#define __EXTERNAL_FUNCTIONS_H

extern USB_OTG_CORE_HANDLE           USB_OTG_dev;
extern uint32_t USBD_OTG_ISR_Handler (USB_OTG_CORE_HANDLE *pdev);

#ifdef USB_OTG_HS_DEDICATED_EP1_ENABLED 
extern uint32_t USBD_OTG_EP1IN_ISR_Handler (USB_OTG_CORE_HANDLE *pdev);
extern uint32_t USBD_OTG_EP1OUT_ISR_Handler (USB_OTG_CORE_HANDLE *pdev);
#endif

extern CDC_IF_Prop_TypeDef  APP_FOPS;

extern void Configure_I2C(I2C_TypeDef*);
extern void FSMC_SRAM_Init(void);

extern int main(void);
extern void periodical_operations(void);
extern void global_vareiables_installation(void);
extern void start_settings_peripherals(void);
extern void start_tim4_canal2_for_interrupt_1mc(void);
extern void start_tim4_canal3_for_interrupt_10mkc(void);
extern void min_config(__CONFIG *);
extern void scheme2_config(__CONFIG *);
extern void min_settings(__SETTINGS_FIX *);
extern void scheme2_settings(__CONFIG *, __SETTINGS_FIX *, uintptr_t *[]);
extern void min_settings_INPUT(unsigned int, uintptr_t *, size_t, size_t);
extern void copy_settings_INPUT(unsigned int, unsigned int, uintptr_t *, uintptr_t *, size_t, size_t);
extern void min_settings_OUTPUT_LED(unsigned int, uintptr_t *, size_t, size_t);
extern void copy_settings_OUTPUT_LED(unsigned int, unsigned int, uintptr_t *, uintptr_t *, size_t, size_t);
extern void min_settings_BUTTON(unsigned int, uintptr_t *, size_t, size_t);
extern void min_settings_ALARM(unsigned int, uintptr_t *, size_t, size_t);
extern void copy_settings_ALARM(unsigned int, unsigned int, uintptr_t *, uintptr_t *, size_t, size_t);
extern void min_settings_GROUP_ALARM(unsigned int, uintptr_t *, size_t, size_t);
extern void copy_settings_GROUP_ALARM(unsigned int, unsigned int, uintptr_t *, uintptr_t *, size_t, size_t);
extern void min_settings_AND(unsigned int, uintptr_t *, size_t, size_t);
extern void copy_settings_AND(unsigned int, unsigned int, uintptr_t *, uintptr_t *, size_t, size_t);
extern void min_settings_OR(unsigned int, uintptr_t *, size_t, size_t);
extern void copy_settings_OR(unsigned int, unsigned int, uintptr_t *, uintptr_t *, size_t, size_t);
extern void min_settings_XOR(unsigned int, uintptr_t *, size_t, size_t);
extern void copy_settings_XOR(unsigned int, unsigned int, uintptr_t *, uintptr_t *, size_t, size_t);
extern void min_settings_NOT(unsigned int, uintptr_t *, size_t, size_t);
extern void copy_settings_NOT(unsigned int, unsigned int, uintptr_t *, uintptr_t *, size_t, size_t);
extern void min_settings_TIMER(unsigned int, uintptr_t *, size_t, size_t);
extern void copy_settings_TIMER(unsigned int, unsigned int, uintptr_t *, uintptr_t *, size_t, size_t);
extern void min_settings_TRIGGER(unsigned int, uintptr_t *, size_t, size_t);
extern void copy_settings_TRIGGER(unsigned int, unsigned int, uintptr_t *, uintptr_t *, size_t, size_t);
extern void min_settings_MEANDER(unsigned int, uintptr_t *, size_t, size_t);
extern void copy_settings_MEANDER(unsigned int, unsigned int, uintptr_t *, uintptr_t *, size_t, size_t);
extern void min_settings_TU(unsigned int, uintptr_t *, size_t, size_t);
extern void copy_settings_TU(unsigned int, unsigned int, uintptr_t *, uintptr_t *, size_t, size_t);
extern void min_settings_TS(unsigned int, uintptr_t *, size_t, size_t);
extern void copy_settings_TS(unsigned int, unsigned int, uintptr_t *, uintptr_t *, size_t, size_t);
extern void min_settings_LOG(unsigned int, uintptr_t *, size_t, size_t);
extern void copy_settings_LOG(unsigned int, unsigned int, uintptr_t *, uintptr_t *, size_t, size_t);
extern size_t size_all_settings(void);
extern void copy_settings(__CONFIG *, __SETTINGS_FIX *, __SETTINGS_FIX *, uintptr_t *[], uintptr_t *[]);
extern unsigned int set_config_and_settings(unsigned int, unsigned int);
extern void error_reading_with_eeprom(void);
extern void move_into_editor_list_logical_nodes(unsigned int, int);
extern void make_ekran_editor_list_logical_node(void);
extern enum _result_pressed_enter_during_edition  press_enter_in_editor_list_logical_node(void);
extern void press_esc_in_editor_list_logical_node(void);
extern void make_ekran_editor_list_inputs_of_selected_logical_node(void);
extern void move_into_editor_view_chosen_of_selected_logical_node(unsigned int, int);
extern void make_ekran_editor_view_chosen_of_selected_logical_node(void);
extern void change_set_signal(unsigned int);
extern void make_ekran_editor_edit_list_outputs_of_selected_logical_node(void);
extern void select_input_signal_ln(void);

extern void Interrupts_Config(void);

extern void lcd_init(void);
extern unsigned int wait_lcd_ready(void);
extern unsigned int clear_lcd(void);
extern unsigned int mode_viewing(unsigned int, unsigned int, unsigned int);
extern unsigned int hd44780_puts(unsigned char *, unsigned int);
extern unsigned int Win1251toHd44780 (unsigned int);
extern unsigned int write_data_to_lcd(unsigned char);
extern unsigned int write_command_to_lcd(unsigned char);
extern unsigned int hd44780_gotoxy(unsigned char, unsigned char);
extern unsigned int hd44780_puts_xy (unsigned char, unsigned char, unsigned char *);
extern void view_whole_ekran(void);
extern void check_state_key(GPIO_TypeDef*, uint16_t, unsigned int);
extern __SETTINGS_FIX* select_struct_settings_fix(void);
extern int index_language_in_array(int);
extern void make_ekran_choose_communication_parameters(void);
extern void make_ekran_name_of_cell(void);
extern void make_ekran_address(void);
extern enum _result_pressed_enter_during_edition press_enter_in_address(void);
extern void press_esc_in_address(void);
extern void change_address(unsigned int);
extern void make_ekran_choose_setting_RS485(void);
extern void make_ekran_baud_RS485(void);
extern enum _result_pressed_enter_during_edition press_enter_in_baud_RS485(void);
extern void press_esc_in_baud_RS485(void);
extern void change_baud_RS485(unsigned int);
extern void make_ekran_pare_RS485(void);
extern enum _result_pressed_enter_during_edition press_enter_in_pare_RS485(void);
extern void press_esc_in_pare_RS485(void);
extern void change_pare_RS485(unsigned int);
extern void make_ekran_stopbits_RS485(void);
extern enum _result_pressed_enter_during_edition press_enter_in_stopbits_RS485(void);
extern void press_esc_in_stopbits_RS485(void);
extern void change_stopbits_RS485(unsigned int);
extern void make_ekran_timeout_RS485(void);
extern enum _result_pressed_enter_during_edition press_enter_in_timeout_RS485(void);
extern void press_esc_in_timeout_RS485(void);
extern void change_timeout_RS485(unsigned int);
extern void make_ekran_choose_passwords(void);
extern void make_ekran_password(void);
extern void inc_or_dec_value(unsigned int *, unsigned int);
extern unsigned int bcd_to_int(unsigned char);
extern void calc_symbol_and_put_into_working_ekran(uint8_t*, void*, void*, unsigned int*, unsigned int, unsigned int, unsigned int);
extern void calc_int_symbol_and_put_into_working_ekran(uint8_t*, uint32_t*, uint32_t*, unsigned int*);
extern unsigned int edit_setpoint(unsigned int,  uint32_t, unsigned int, int, unsigned int, unsigned int);
extern unsigned int check_data_setpoint(unsigned int, unsigned int, unsigned int);
extern void main_manu_function_ver2(void);
extern void new_level_menu(void);
extern void make_ekran_main(void);
extern void move_into_main(unsigned int, int);
extern enum _result_pressed_enter_during_edition press_enter_in_ekran_with_request(void);
extern void make_ekran_time(void);
extern void move_into_time(unsigned int, int);
extern void change_time(unsigned int);
extern enum _result_pressed_enter_during_edition press_enter_in_time(void);
extern void make_ekran_ask_rewrite(void);
extern unsigned int check_data_for_data_time_menu(void);
extern void make_ekran_about_info(unsigned int, const uint8_t [][MAX_COL_LCD + 1]);
extern void make_ekran_configuration(void);
extern enum _result_pressed_enter_during_edition press_enter_in_configuration(void);
extern void change_configuration(unsigned int);
extern void make_ekran_measurement(void);
extern void move_into_ekran_simple(unsigned int, int);
extern void convert_and_insert_char_for_measurement(unsigned int, unsigned int, unsigned int, unsigned int, unsigned char *, unsigned int);
extern void make_ekran_choose_pickup_delay_control(void);
extern void make_ekran_choose_delay_control(void);
extern void make_ekran_choose_delay(void);
extern void make_ekran_choose_control(void);
extern void move_into_list_settings(unsigned int, int);
extern void make_ekran_list_settings(void);
extern void press_esc_in_list_settings(void);
extern void move_into_list_settings_param(unsigned int, int);
extern void make_ekran_list_settings_param(void);
extern void press_esc_in_configuration(void);
extern void make_ekran_list_logical_nodes(void);
extern void make_ekran_delay_timer(void);
extern enum _result_pressed_enter_during_edition press_enter_in_delay_timer(void);
extern void press_esc_in_delay_timer(void);
extern void change_delay_timer(unsigned int);
extern void make_ekran_delay_meander(void);
extern enum _result_pressed_enter_during_edition press_enter_in_delay_meander(void);
extern void press_esc_in_delay_meander(void);
extern void change_delay_meander(unsigned int);
extern void make_ekran_control_alarm(void);
extern enum _result_pressed_enter_during_edition press_enter_in_control_alarm(void);
extern void press_esc_in_control_alarm(void);
extern void change_control_alarm(unsigned int);
extern void make_ekran_delay_alarm(void);
extern enum _result_pressed_enter_during_edition press_enter_in_delay_alarm(void);
extern void press_esc_in_delay_alarm(void);
extern void change_delay_alarm(unsigned int);
extern void make_ekran_pickup_group_alarm(void);
extern enum _result_pressed_enter_during_edition press_enter_in_pickup_group_alarm(void);
extern void press_esc_in_pickup_group_alarm(void);
extern void change_pickup_group_alarm(unsigned int);
extern void make_ekran_delay_group_alarm(void);
extern enum _result_pressed_enter_during_edition press_enter_in_delay_group_alarm(void);
extern void press_esc_in_delay_group_alarm(void);
extern void change_delay_group_alarm(unsigned int);
extern void make_ekran_control_group_alarm(void);
extern enum _result_pressed_enter_during_edition press_enter_in_control_group_alarm(void);
extern void press_esc_in_control_group_alarm(void);
extern void change_control_group_alarm(unsigned int);
extern void make_ekran_control_input(void);
extern enum _result_pressed_enter_during_edition press_enter_in_control_input(void);
extern void press_esc_in_control_input(void);
extern void change_control_input(unsigned int);
extern void make_ekran_delay_input(void);
extern enum _result_pressed_enter_during_edition press_enter_in_delay_input(void);
extern void press_esc_in_delay_input(void);
extern void change_delay_input(unsigned int);
extern void make_ekran_control_output_led(void);
extern enum _result_pressed_enter_during_edition press_enter_in_control_output_led(void);
extern void press_esc_in_control_output_led(void);
extern void change_control_output_led(unsigned int);
extern void make_ekran_setting_language(void);
extern void make_ekran_info(void);
extern void make_ekran_date_time_pz(void);
extern void make_ekran_list_labels(void);
extern void make_ekran_time_config_or_settings(void);
extern void move_into_diagnostics(unsigned int, int);
extern void make_ekran_diagnostics(void);
extern void move_into_ekran_list_inputs_outputs(unsigned int, int);
extern void make_ekran_list_inputs_outputs(void);
extern unsigned int max_number_digit_in_number(int);
extern void make_ekran_state_inputs_or_outputs(void);
extern void move_into_ekran_state_analog_inputs(unsigned int, int);
extern void make_ekran_state_analog_inputs(void);
extern void move_into_ekran_input_or_output(unsigned int, int);
extern void make_ekran_list_registrators(void);
extern enum _result_pressed_enter_during_edition press_enter_in_setting_language(void);
extern void press_esc_in_setting_language(void);
extern void change_setting_language(unsigned int);
extern void move_into_ekran_event_registraqtors(unsigned int, int);
extern void make_ekran_list_event_log(void);
extern void make_ekran_list_event_pr_err(void);
extern void make_ekran_data_reg(void);

extern __result_dym_mem_select allocate_dynamic_memory_for_diagnostyka(__action_dym_mem_select, uint32_t, uint32_t);
extern __result_dym_mem_select allocate_dynamic_memory_for_settings(__action_dym_mem_select, unsigned int, uintptr_t *[], uintptr_t *[], __CONFIG *, __CONFIG *, __CONFIG *);
extern __result_dym_mem_select action_after_changing_of_configuration(void);
extern void calculate_namber_bit_waiting_for_rs_485(void);
extern void restore_trigger_functions(unsigned int*);
extern void changing_diagnostyka_state(void);
extern unsigned int count_number_set_bit(unsigned int*, unsigned int);

extern void set_bit(unsigned int*, unsigned int);
extern void clear_bit(unsigned int*, unsigned int);
//extern void input_scan(void);
extern void main_protection(void);
extern void diagnostyca_adc_execution(void);

extern void Usb_routines(void);
extern void USART_RS485_Configure(void);
extern void restart_monitoring_RS485(void);
extern void start_transmint_data_via_RS_485(unsigned int);

extern ErrorStatus check_errors_i2c(void);
extern unsigned int start_write_buffer_via_I2C(uint32_t, uint16_t, uint8_t *, uint32_t);
extern unsigned int start_read_buffer_via_I2C(uint32_t, uint16_t, uint8_t *, uint32_t);
extern void main_routines_for_i2c(void);
extern void error_start_i2c(void);

extern void control_reading_ADCs(void);
extern void operate_test_ADCs(void);
//extern void method_sum_sqr_data(void);
extern void calc_measurement(void);
extern unsigned int norma_value(unsigned long long);
extern unsigned int sqrt_32(unsigned int);
extern unsigned int sqrt_64(unsigned long long);
extern unsigned int get_order(int);

extern uint32_t event_log_handler(void);

extern void start_checking_dataflash(void);
extern void start_exchange_via_spi_df(uint32_t, uint32_t);
extern void main_routines_for_spi_df(uint32_t);

extern void control_config(unsigned int);
extern void control_settings(unsigned int);
extern void control_ustuvannja(void);
extern void control_trg_func(void);
extern unsigned int control_info_rejestrator(__INFO_REJESTRATOR*, uint8_t);

extern void test_external_SRAM(void);

extern void watchdog_routine(void);
extern void total_error_sw_fixed(unsigned int);

extern void NMI_Handler(void);
extern void HardFault_Handler(void);
extern void MemManage_Handler(void);
extern void BusFault_Handler(void);
extern void UsageFault_Handler(void);
extern void SVC_Handler(void);
extern void DebugMon_Handler(void);
extern void PendSV_Handler(void);
extern void SysTick_Handler(void);
extern void USB_LP_CAN1_RX0_IRQHandler(void);
extern void TIM2_IRQHandler(void);
extern void TIM3_IRQHandler(void);
extern void TIM4_IRQHandler(void);
extern void TIM5_IRQHandler(void);
extern void I2C_EV_IRQHandler(void);
extern void I2C_ER_IRQHandler(void);
extern void DMA_StreamI2C_Tx_IRQHandler(void);
extern void DMA_StreamI2C_Rx_IRQHandler(void);
extern void SPI_ADC_IRQHandler(void);
extern void DMA_StreamSPI_DF_Rx_IRQHandler(void);
extern void SPI_DF_IRQHandler(void);
extern void USARTRS485_IRQHandler(void);
extern void DMA_StreamRS485_Tx_IRQHandler(void);
extern void EXITI_POWER_IRQHandler(void);

extern int str_to_int_DATE_Mmm(void);

extern long ChangeCfg(void* pv);

//extern void inputPacketParser(void);
extern void inputPacketParserUSB(void);
extern void inputPacketParserRS485(void);

#ifdef TEST_MODE
extern void empty_settings(void);
#endif

#endif
