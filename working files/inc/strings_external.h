#ifndef __STRINGS_EXTERNAL_H
#define __STRINGS_EXTERNAL_H

extern const uint8_t name_string_ask[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1];

extern const uint8_t information_no_edition[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1];
extern const uint8_t information_out_of_limits[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1];
extern const uint8_t information_error[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1];
extern const uint32_t cursor_x_error[MAX_NAMBER_LANGUAGE];
extern const uint8_t information_no_free_dyn_mem[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1];
extern const uint8_t information_on_off[MAX_NAMBER_LANGUAGE][2][MAX_COL_LCD + 1];
extern const uint32_t cursor_x_on_off[MAX_NAMBER_LANGUAGE][2];
extern const uint8_t information_request[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1];
extern const uint8_t information_about_info_1[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1];
extern const uint8_t information_empty[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1];
extern const uint32_t cursor_x_empty[MAX_NAMBER_LANGUAGE];
extern const uint8_t information_none[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1];
extern const uint32_t cursor_x_none[MAX_NAMBER_LANGUAGE];
extern const uint8_t ms[MAX_NAMBER_LANGUAGE][2];

extern const uint8_t calibrating[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1];

extern const uint8_t name_string_alarm_delay[MAX_NAMBER_LANGUAGE][ALARM_SET_DELAYS][MAX_COL_LCD + 1];
extern const uint8_t name_string_alarm_control[MAX_NAMBER_LANGUAGE][MAX_INDEX_CTRL_ALARM][MAX_COL_LCD + 1];
extern const uint8_t information_alarm_control[MAX_NAMBER_LANGUAGE][ALARM_MODES_NUMBER][MAX_COL_LCD + 1];
extern const unsigned int cursor_x_alarm_control[MAX_NAMBER_LANGUAGE][ALARM_MODES_NUMBER];
extern const uint8_t name_alarm_in_signals[MAX_NAMBER_LANGUAGE][ALARM_SIGNALS_IN][MAX_COL_LCD + 1];
extern const uint8_t name_alarm_out_signals[MAX_NAMBER_LANGUAGE][ALARM_SIGNALS_OUT][MAX_COL_LCD + 1];
extern const uint8_t name_alarm[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1];
extern const unsigned int first_index_number_alarm[MAX_NAMBER_LANGUAGE];

extern const uint8_t name_button_out_signals[MAX_NAMBER_LANGUAGE][BUTTON_SIGNALS_OUT][MAX_COL_LCD + 1];
extern const uint8_t name_fix_buttons[NUMBER_FIX_BUTTONS][MAX_COL_LCD + 1];
extern const uint8_t name_button[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1];
extern const uint32_t first_index_number_button[MAX_NAMBER_LANGUAGE];

extern const uint8_t name_event_log_out_signals[MAX_NAMBER_LANGUAGE][EVENT_LOG_SIGNALS_OUT][MAX_COL_LCD + 1];


extern const uint8_t name_string_choose_communication_parameters[MAX_NAMBER_LANGUAGE][MAX_ROW_CHCP_M2][MAX_COL_LCD + 1];
extern const uint8_t name_string_choose_communication_parameters_address[MAX_NAMBER_LANGUAGE][MAX_ROW_ADDRESS_M2][MAX_COL_LCD + 1];
extern const uint8_t name_string_choose_communication_parameters_RS485[MAX_NAMBER_LANGUAGE][MAX_ROW_SETTING_RS485_M2][MAX_COL_LCD + 1];
extern const uint8_t name_string_choose_communication_parameters_speed[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_VIEW_BAUD_RS485][MAX_COL_LCD + 1];
extern const uint8_t information_speed[MAX_NUMBER_BAUD_RS485][MAX_COL_LCD + 1];
extern const uint8_t name_stringe_communication_parameters_pare[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_VIEW_PARE_RS485][MAX_COL_LCD + 1];
extern const uint32_t cursor_x_communication_parameters_pare[MAX_NUMBER_BAUD_RS485];
extern const uint8_t information_pare[MAX_NAMBER_LANGUAGE][MAX_NUMBER_PARE_RS485][MAX_COL_LCD + 1];
extern const uint32_t cursor_x_pare[MAX_NAMBER_LANGUAGE][MAX_NUMBER_PARE_RS485 + 1];
extern const uint8_t name_stringe_communication_parameters_stopbits[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_VIEW_STOP_BITS_RS485][MAX_COL_LCD + 1];
extern const uint8_t information_stopbits[MAX_NAMBER_LANGUAGE][MAX_NUMBER_STOP_BITS_RS485][MAX_COL_LCD + 1];
extern const uint32_t cursor_x_stopbits[MAX_NAMBER_LANGUAGE][MAX_NUMBER_STOP_BITS_RS485];
extern const uint8_t name_stringe_communication_parameters_timeout[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_VIEW_TIMEOUT_RS485][MAX_COL_LCD + 1];

extern const uint8_t name_string_choose_settings_logical_nodes_delay[MAX_NAMBER_LANGUAGE][MAX_ROW_LIST_SETTINGS_D_M2][MAX_COL_LCD + 1];
extern const uint8_t name_string_choose_settings_logical_nodes_control[MAX_NAMBER_LANGUAGE][MAX_ROW_LIST_SETTINGS_C_M2][MAX_COL_LCD + 1];
extern const uint8_t name_string_choose_settings_logical_nodes_delay_control[MAX_NAMBER_LANGUAGE][MAX_ROW_LIST_SETTINGS_DC_M2][MAX_COL_LCD + 1];
extern const uint8_t name_string_choose_settings_logical_nodes_pickup_delay_control[MAX_NAMBER_LANGUAGE][MAX_ROW_LIST_SETTINGS_PDC_M2][MAX_COL_LCD + 1];

extern const uint8_t name_string_configuration[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_CONFIGURATION][MAX_COL_LCD + 1];

extern const uint8_t name_f_blocks[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_EDITOR_LIST_LOGICAL_NODES][MAX_COL_LCD + 1];
extern const uint8_t name_string_editor_logical_nodes[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_EDITOR_LIST_LOGICAL_NODES][MAX_COL_LCD + 1];

extern const uint8_t name_fix_block_in_signals[MAX_NAMBER_LANGUAGE][FIX_BLOCK_SIGNALS_IN][MAX_COL_LCD + 1];
extern const uint8_t name_fix_block_out_signals[MAX_NAMBER_LANGUAGE][FIX_BLOCK_SIGNALS_OUT][MAX_COL_LCD + 1];

extern const uint8_t name_string_group_alarm[MAX_NAMBER_LANGUAGE][MAX_INDEX_CTRL_GROUP_ALARM][MAX_COL_LCD + 1];
extern const uint8_t name_string_group_alarm_pickup[MAX_NAMBER_LANGUAGE][GROUP_ALARM_PICKUPS][MAX_COL_LCD + 1];
extern const uint8_t name_string_group_alarm_delay[MAX_NAMBER_LANGUAGE][GROUP_ALARM_SET_DELAYS][MAX_COL_LCD + 1];
extern const uint8_t name_group_alarm_out_signals[MAX_NAMBER_LANGUAGE][GROUP_ALARM_SIGNALS_OUT][MAX_COL_LCD + 1];
extern const uint8_t name_group_alarm[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1];
extern const unsigned int first_index_number_group_alarm[MAX_NAMBER_LANGUAGE];

extern const uint8_t name_string_info[MAX_NAMBER_LANGUAGE][MAX_ROW_INFO_M2][MAX_COL_LCD + 1];

extern const uint8_t name_string_input_control[MAX_NAMBER_LANGUAGE][MAX_INDEX_CTRL_INPUT][MAX_COL_LCD + 1];
extern const uint8_t information_input_control[MAX_NAMBER_LANGUAGE][2][MAX_COL_LCD + 1];
extern const unsigned int cursor_x_input_control[MAX_NAMBER_LANGUAGE][2];
extern const uint8_t name_string_input_delay[MAX_NAMBER_LANGUAGE][INPUT_SET_DELAYS][MAX_COL_LCD + 1];
extern const uint8_t name_input_out_signals[MAX_NAMBER_LANGUAGE][INPUT_SIGNALS_OUT][MAX_COL_LCD + 1];
extern const uint8_t name_input[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1]; 
extern const unsigned int first_index_number_input[MAX_NAMBER_LANGUAGE];

extern const uint8_t name_string_labels[MAX_NAMBER_LANGUAGE][MAX_ROW_LABELS_M2][MAX_COL_LCD + 1];

extern const uint8_t name_string_list_settings[MAX_NAMBER_LANGUAGE][MAX_ROW_LIST_SETTINGS_M2][MAX_COL_LCD + 1];

extern const uint8_t name_stringlist_settings_param[MAX_NAMBER_LANGUAGE][MAX_ROW_LIST_SETTINGS_PARAM_M2][MAX_COL_LCD + 1];
extern const uint8_t name_string_list_settings_param_info[MAX_NAMBER_LANGUAGE][2][MAX_COL_LCD + 1];

extern const uint8_t name_log[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1];
extern const unsigned int first_index_number_log[MAX_NAMBER_LANGUAGE];

extern const uint8_t name_string_main[MAX_NAMBER_LANGUAGE][MAX_ROW_MAIN_M2][MAX_COL_LCD + 1];

extern const uint8_t name_string_meander_delay[MAX_NAMBER_LANGUAGE][MAX_INDEX_DELAY_MEANDER][MAX_COL_LCD + 1];
extern const uint8_t name_meander_out_signals[MAX_NAMBER_LANGUAGE][MEANDER_SIGNALS_OUT][MAX_COL_LCD + 1];
extern const uint8_t name_meander[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1];
extern const unsigned int first_index_number_meander[MAX_NAMBER_LANGUAGE];

extern const uint32_t index_array[MAX_ROW_FOR_MEASURMENT_ANALOG_INPUT];

extern const uint8_t name_string_output_led_control[MAX_NAMBER_LANGUAGE][MAX_INDEX_CTRL_OUTPUT_LED][MAX_COL_LCD + 1];
extern const uint8_t information_output_led_control_N_T[MAX_NAMBER_LANGUAGE][2][MAX_COL_LCD + 1];
extern const uint32_t cursor_x_output_led_control_N_T[MAX_NAMBER_LANGUAGE][2];
extern const uint8_t information_output_led_control_C_I[MAX_NAMBER_LANGUAGE][2][MAX_COL_LCD + 1];
extern const uint32_t cursor_x_output_led_control_C_I[MAX_NAMBER_LANGUAGE][2];
extern const uint8_t information_output_led_control_SI_EI[MAX_NAMBER_LANGUAGE][2][MAX_COL_LCD + 1];
extern const uint32_t cursor_x_output_led_control_SI_EI[MAX_NAMBER_LANGUAGE][2];
extern const uint8_t value_name[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1];
extern const uint32_t number_symbols_in_name[MAX_NAMBER_LANGUAGE];
extern const uint8_t name_output_led_in_signals[MAX_NAMBER_LANGUAGE][OUTPUT_LED_SIGNALS_IN][MAX_COL_LCD + 1];
extern const uint8_t name_output_led_out_signals[MAX_NAMBER_LANGUAGE][OUTPUT_LED_SIGNALS_OUT][MAX_COL_LCD + 1];
extern const uint8_t name_output[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1];
extern const uint32_t first_index_number_output[MAX_NAMBER_LANGUAGE];
extern const uint8_t name_led[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1]; 
extern const uint32_t first_index_number_led[MAX_NAMBER_LANGUAGE];

extern const uint8_t name_string_level_password_1[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1];
extern const uint8_t name_string_level_password_2[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1];
extern const uint8_t password_item_level_password[MAX_ROW_LIST_PASSWORDS_M2][MAX_NAMBER_LANGUAGE][2][MAX_COL_LCD + 1];

extern const uint8_t name_string_registrators[MAX_NAMBER_LANGUAGE][MAX_ROW_LIST_REGISTRATORS_M2][MAX_COL_LCD + 1];
extern const uint8_t information_no_records[MAX_NAMBER_LANGUAGE][2][MAX_COL_LCD + 1];
extern const uint8_t name_string_pr_err[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_DIAGNOSTYKA][MAX_COL_LCD + 1];
extern const uint8_t passive_active[MAX_NAMBER_LANGUAGE][2][6];
extern const uint8_t info_data_corrupted[MAX_NAMBER_LANGUAGE][2][MAX_COL_LCD + 1];
extern const uint8_t information_timeout[MAX_NAMBER_LANGUAGE][2][MAX_COL_LCD + 1];

extern const uint8_t name_string_language[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_VIEW_SETTING_LANGUAGE][MAX_COL_LCD + 1];
extern uint8_t information_language[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1];
extern const unsigned int cursor_x_language[MAX_NAMBER_LANGUAGE];

extern const uint8_t name_standard_logic_in_signals[MAX_NAMBER_LANGUAGE][1][MAX_COL_LCD + 1];
extern const uint8_t name_standard_logic_out_signals[MAX_NAMBER_LANGUAGE][STANDARD_LOGIC_SIGNALS_OUT][MAX_COL_LCD + 1];
extern const uint8_t name_and[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1];
extern const uint32_t first_index_number_and[MAX_NAMBER_LANGUAGE];
extern const uint8_t name_or[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1]; 
extern const uint32_t first_index_number_or[MAX_NAMBER_LANGUAGE];
extern const uint8_t name_xor[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1];
extern const uint32_t first_index_number_xor[MAX_NAMBER_LANGUAGE];
extern const uint8_t name_not[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1];
extern const uint32_t first_index_number_not[MAX_NAMBER_LANGUAGE];

extern const uint8_t name_string_inputs_outputs[MAX_NAMBER_LANGUAGE][MAX_ROW_INPUT_OUTPUT_M2][MAX_COL_LCD + 1];

extern const uint8_t name_string_timer_delay[MAX_NAMBER_LANGUAGE][TIMER_SET_DELAYS][MAX_COL_LCD + 1]; 
extern const uint8_t name_timer_in_signals[MAX_NAMBER_LANGUAGE][TIMER_SIGNALS_IN][MAX_COL_LCD + 1];
extern const uint8_t name_timer_out_signals[MAX_NAMBER_LANGUAGE][TIMER_SIGNALS_OUT][MAX_COL_LCD + 1];
extern const uint8_t name_timer[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1];
extern const uint32_t first_index_number_timer[MAX_NAMBER_LANGUAGE];

extern const uint8_t name_trigger_in_signals[MAX_NAMBER_LANGUAGE][TRIGGER_SIGNALS_IN][MAX_COL_LCD + 1];
extern const uint8_t name_trigger_out_signals[MAX_NAMBER_LANGUAGE][TRIGGER_SIGNALS_OUT][MAX_COL_LCD + 1];
extern const uint8_t name_trigger[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1];
extern const uint32_t first_index_number_trigger[MAX_NAMBER_LANGUAGE];

extern const uint8_t name_tu_in_signals[MAX_NAMBER_LANGUAGE][TU_SIGNALS_IN][MAX_COL_LCD + 1];
extern const uint8_t name_tu_out_signals[MAX_NAMBER_LANGUAGE][TU_SIGNALS_OUT][MAX_COL_LCD + 1];
extern const uint8_t name_tu[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1];
extern const uint32_t first_index_number_tu[MAX_NAMBER_LANGUAGE];

extern const uint8_t name_ts_in_signals[MAX_NAMBER_LANGUAGE][TU_SIGNALS_IN][MAX_COL_LCD + 1];
extern const uint8_t name_ts_out_signals[MAX_NAMBER_LANGUAGE][TU_SIGNALS_OUT][MAX_COL_LCD + 1];
extern const uint8_t name_ts[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1];
extern const uint32_t first_index_number_ts[MAX_NAMBER_LANGUAGE];

#endif
