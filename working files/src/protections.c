#include "header.h"
#include "../v_A_shm/I_Shm.h"
#include "../v_A_shm/prtTmr.h"
/*****************************************************/
//ĳ��������� ���
/*****************************************************/
inline void diagnostyca_adc_execution(void)
{
  if (gnd_adc >0x51) _SET_BIT(set_diagnostyka, ERROR_GND_ADC_TEST_BIT);
  else _SET_BIT(clear_diagnostyka, ERROR_GND_ADC_TEST_BIT);

  if ((vref_adc <0x709) || (vref_adc > 0x8f5)) _SET_BIT(set_diagnostyka, ERROR_VREF_ADC_TEST_BIT);
  else _SET_BIT(clear_diagnostyka,ERROR_VREF_ADC_TEST_BIT);

  if ((vdd_adc <0x8F9) || (vdd_adc > 0xC24)) _SET_BIT(set_diagnostyka, ERROR_VDD_ADC_TEST_BIT);
  else _SET_BIT(clear_diagnostyka, ERROR_VDD_ADC_TEST_BIT);
}
/*****************************************************/

/*****************************************************/
//����� ���������� �����
/*****************************************************/
inline unsigned int norma_value(unsigned long long y)
{
  unsigned long long temp=y;
  unsigned int rezultat =0;
  if (temp == 0) return 0;

  while(temp !=0)
  {
    temp = temp>>1;
    rezultat++;
  }
  return rezultat-1;
}
/*****************************************************/

/*****************************************************/
//����� ���������� ����� ���� int
/*****************************************************/
inline unsigned int get_order(int value)
{
  unsigned int i = 0;

  if (value == 0) return 1;  
  if (value < 0) value =-value;

  while ((value >> (++i)) != 0); 

  return i;    
}
/*****************************************************/

/*****************************************************/
//���������� ������ ����������� ������� ����������� ������  � �������������� ���������� �����
/*****************************************************/
unsigned int sqrt_64(unsigned long long y)
{
   unsigned int b;
   unsigned int a;
   unsigned int c;
   unsigned int norma_rez;
   unsigned long long temp;
   
   norma_rez = norma_value(y)>>1;
   
   a = (1<<norma_rez) - 1;
   b = (1<<(norma_rez+1));
 
   do 
    {
     c = (a + b)>>1;
     temp = (unsigned long long)c*(unsigned long long)c; 
     if (temp != y)
       {
        if ( temp > y) b= c; else a= c;
       } 
     else return c;
    }
   while ((b-a)>1);

   c = (a + b)>>1;

   return c ;
}
/*****************************************************/

/*****************************************************/
//���������� ������ ����������� ������� ����������� ������  � �������������� ���������� �����
/*****************************************************/
inline unsigned int sqrt_32(unsigned int y)
{
   unsigned int b;
   unsigned int a;
   unsigned int c;
   unsigned int norma_rez;
   unsigned int temp;
   
   norma_rez = norma_value(y)>>1;
   
   a = (1<<norma_rez) - 1;
   b = (1<<(norma_rez+1));
 
   do 
    {
     c = (a + b)>>1;
     temp = c*c; 
     if (temp != y)
       {
        if ( temp > y) b= c; else a= c;
       } 
     else return c;
    }
   while ((b-a)>1);

   c = (a + b)>>1;

   return c ;
}
/*****************************************************/

/*****************************************************/
//���������� ���������
/*****************************************************/
inline void calc_measurement(void)
{
  uint32_t sqrt_sum_sqr_data_local[NUMBER_ANALOG_CANALES];
  
  //������� ������ �������� � �������� �����
  /*
  ������� ��� ������������� ���������� ���� �������� � ����� ������� �� �����, 
  �� ��� ����������� ������� ��������� ������ �� ������� �������, �� �� �� ������ ����� � ������ ��������
  */
  unsigned int bank_sum_sqr_data_tmp = bank_sum_sqr_data;
  bank_sum_sqr_data = (bank_sum_sqr_data + 1) & 0x1;
  for(uint32_t i =0; i < NUMBER_ANALOG_CANALES; i++ )
  {
    /***/
    //����������� ���� �������� 3I0 �� ������������ �������
    /***/
    /*�������� ���������� �����*/
    sqrt_sum_sqr_data_local[i] = sqrt_64(sum_sqr_data[bank_sum_sqr_data_tmp][i]);
//    uint64_t in_64 = sum_sqr_data[bank_sum_sqr_data_tmp][i];
//    if ((in_64 & (uint64_t)(~0x7FFFFFFF)) == 0)
//    {
//      q31_t in = in_64, out;
//      arm_sqrt_q31(in, &out);
//      sqrt_sum_sqr_data_local[i] = out;
//    }
//    else
//    {
//      q31_t in = (in_64 >> 4), out;
//      arm_sqrt_q31(in, &out);
//      sqrt_sum_sqr_data_local[i] = out << 2;
//    }
      
  
    /*��� ���������� ����� �������� � ��/�� ����� ��������� �� ��� ����������*/
    /*�� ������ ����� � ��������� � 16 ���, ���� ���� ���� �� 16*/

    /*
    �� ���� �� �������� ����� ������� �� ����� � NUMBER_POINT = 32 = 16*2
    ����� �� ���� ������� �� 4*sqrt(2)
    4 �� ������� �� 2
    ((MNOGNYK_I * X )>> VAGA_DILENNJA_I)/sqrt(2) �������
   (MNOGNYK_I_DIJUCHE * X )>> VAGA_DILENNJA_I_DIJUCHE 

    ((MNOGNYK_U * X )>> VAGA_DILENNJA_U)/sqrt(2) �������
   (MNOGNYK_U_DIJUCHE * X )>> VAGA_DILENNJA_D_DIJUCHE 
    
    ���� ������ ����� ���� (MNOGNYK_I_DIJUCHE;VAGA_DILENNJA_I_DIJUCHE)/(MNOGNYK_U_DIJUCHE;VAGA_DILENNJA_U_DIJUCHE) � (MNOGNYK_I;VAGA_DILENNJA_I)/(MNOGNYK_U;VAGA_DILENNJA_U)
    �� ������ ������� ��� ���������� ����� �������� (�� ���� ���� ��� ������� ������ ��� ����������. � �� �� ����).
    ���� ����� ��� �� ��� ��������� ������
    */
    
    float mnognyk = (i < (NUMBER_ANALOG_CANALES - 1)) ? MNOGNYK_I_DIJUCHE_FLOAT : MNOGNYK_U_DIJUCHE_FLOAT;
    float value_float = mnognyk*((float)sqrt_sum_sqr_data_local[i])/(64.0f); /*64 = 4*16. 16 - �� ��������� ������ "Analog Input"; 4 - �� sqrt(16), � 16 �������� � ����, �� 32 = 16*2 */
    measurement[i] = (unsigned int)value_float; 
    /***/
  }
}
/*****************************************************/

/*****************************************************/
//������ ������� ���������� �����
/*****************************************************/
//inline void input_scan(void)
//{
//  unsigned int state_inputs_into_pin, temp_state_inputs_into_pin; //����� � ��� ������� �������� ����� �������� �� ����� ��������� (����)
//  static unsigned int state_inputs_into_pin_trigger; //� ��� ������ ���������� ���������� ���� ���, � ������� ���� �� ���������� .�� ���������� ��� ���� �� ���� ���������� ������� �������
//
//  /***************************/
//  //� ��� ������� ������� ����� ����� ��������� (����), �� ���������� �� ��������� �����
//  /*
//  -----------------------------
//  �������� ��������� � ��������� ��� ����� state_inputs_into_pin
//    "�     ������ " - ������� ������������� ��� (1)
//    "���� �������" - ������� ���������     ��� (0)
//  -----------------------------
//  */
//  unsigned int temp_state_inputs_into_pin_1 = _DEVICE_REGISTER(Bank1_SRAM2_ADDR, OFFSET_INPUTS_1) & ((1 << NUMBER_INPUTS_1) - 1);
//  unsigned int temp_state_inputs_into_pin_2 = _DEVICE_REGISTER(Bank1_SRAM2_ADDR, OFFSET_INPUTS_2) & ((1 << NUMBER_INPUTS_2) - 1);
//  temp_state_inputs_into_pin = temp_state_inputs_into_pin_1 | (temp_state_inputs_into_pin_2 << NUMBER_INPUTS_1);
//  
//  //������� �������, ��� �������� ����� �������� ��������� �� ������
//  state_inputs_into_pin = 0;
//  for (unsigned int index = 0; index < NUMBER_INPUTS; index++)
//  {
//    if ((temp_state_inputs_into_pin & (1 << index)) != 0) 
//    {
//      if (index < NUMBER_INPUTS_1)
//        state_inputs_into_pin |= 1 << (NUMBER_INPUTS_1 - index - 1);
//      else
//        state_inputs_into_pin |= 1 << index;
//    }
//  }
//  /***************************/
//  
//  /***************************/
//  //������� ������� ������� ���������� �����
//  /***************************/
//  for(unsigned int i = 0; i < NUMBER_INPUTS; i++)
//  {
//    unsigned int maska = 1<<i;
//    int max_value_timer = /*current_settings_prt.dopusk_dv[i]*/60;
//
//    if (global_timers[INDEX_TIMER_INPUT_START + i] < 0)
//    {
//      //������� �� ���� ����� ����������� ����� ����������� ����� ���, ���� �������� ������� � ��'�����
//      //�� ������ �� ������ �� ��������� � ���������� ������
//      
//      //���������� �� ���������� ���� ����� ������� ������������ �����
//      if ((state_inputs_into_pin & maska) != (state_inputs & maska))
//      {
//        //���� ���� ����� �������, �� �������� 䳿 �� ���� �����
//
//        //1-��: �����'������� ������� ���� �����
//        state_inputs_into_pin_trigger &= ~maska;
//        state_inputs_into_pin_trigger |= (state_inputs_into_pin & maska);
//
//        //2-��: ��������� ������ ������� ����������� �����
//        global_timers[INDEX_TIMER_INPUT_START + i] = 0;
//      }
//    }
//    else
//    {
//      //���� ������ ��������� �������� 䳿 � ��������
//      if (global_timers[INDEX_TIMER_INPUT_START + i] < max_value_timer)
//      {
//        //���� ������ �� �� ����� �� ����� ���������, �� ������ �������� ���� ��������
//        global_timers[INDEX_TIMER_INPUT_START + i] += DELTA_TIME_FOR_TIMERS;
//        
//        //� �������, ���� ��� ������� �� ���� �������� ������
//        //� �� ���������� �� �� ������� ������� "� ������"->"���� �������"
//        //�� ����� ������� �� ��� ���������� ������� ������� ������, �� ������ �� ���� � - 
//        //� �� ������, �� ����� �������� n�����, �� �������� "� ������"->"���� �������" �� ������ ���������� ������� �� ����������� 
//        if ((0/*current_settings_prt.type_of_input_signal*/ & maska) != 0)
//        {
//           if ((state_inputs_into_pin_trigger & maska) == 0)
//           {
//             if ((state_inputs_into_pin & maska) != 0)
//               global_timers[INDEX_TIMER_INPUT_START + i] = -1;
//           }
//        }
//      }
//    }
//    
//    //���� �������� ������� ������� ����������� � ����� ������������� ��������, �� ����������, �� �������� ������� ����� �����
//    if (global_timers[INDEX_TIMER_INPUT_START + i] >= max_value_timer)
//    {
//      //����������, �� ���� ��� ������� � ��������� �� ������, ���� ��� �� ������ ������� ������� ������� ����������� �����
//      unsigned int state_1, state_2;
//        
//      state_1 = state_inputs_into_pin_trigger & maska;
//      state_2 = state_inputs_into_pin  & maska;
//        
//      if (state_1 == state_2)
//      {
//        //���� ��� ����� ����������, �� �� �������, �� �������� ��� ����� ����������� ����� � ������� ����� ���� �����
//        //��� ����� ��������� �� ��� �������    ����� 1 - �� �������� ����, � 0 - �� �������� ����
//        //                        ��� ���������� ����� 0 - �� �������� ����, � 1 - �� �������� ����
//          state_inputs &=  ~maska;
//          state_inputs |=   state_2;
//      }
//        
//      //� ����-����� ������, �� ������� ���� �����, �� ��, � ������� ������ ������� ���������� �� ����, �� ������������� � �������� ��'���� ��������
//      global_timers[INDEX_TIMER_INPUT_START + i] = -1;
//    }
//  }
//  /***************************/
//}
/*****************************************************/

/*****************************************************/
//������� ������� �������
/*****************************************************/
//inline void clocking_global_timers(void)
//{
//  //����������� ��������� �����
//  input_scan();
//  
//  //����������� �� ����� ������� �����
//  for (unsigned int i = INDEX_TIMER_TEMP; i < MAX_NUMBER_GLOBAL_TIMERS; i++)
//  {
//    if (global_timers[i] >= 0)
//    {
//      //������ ������ ����, �� ������ ����� ��������� � ��� ����, �� �������� ������� �� ��'����
//
//      //���������� �� ����� ���������� �������� �������, ���� �� �� �� �������� ����� ���������
//      if (global_timers[i] <= (0x7fffffff - DELTA_TIME_FOR_TIMERS)) global_timers[i] += DELTA_TIME_FOR_TIMERS;
//    }
//  }
//}
/*****************************************************/

/*****************************************************/
//������� ������� � ��� ����������� �� ���� ��������
/*****************************************************/
inline void main_protection(void)
{
  /**************************/
  //��������, �� ����� �������� ������� �������
  /**************************/
  if (reset_trigger_function_from_interface !=0)
  {
    
    //������� �� �� �������� ������� �� �Ѳ� �����������
    reset_trigger_function_from_interface = 0;
  }
  /**************************/

  /**************************/
  //����������� �������� ������
  /**************************/
  __LN_BUTTON *p_button = (__LN_BUTTON*)(spca_of_p_prt[ID_FB_BUTTON - _ID_FB_FIRST_VAR]);
  for (uint32_t i = 0; i < current_config_prt.n_button; i++)
  {
    //�������  ���������� ����
    p_button->active_state [BUTTON_OUT >> 3]  &= (uint8_t)(~( 1 << (BUTTON_OUT & ((1 << 3) - 1))));
    
    //����������, �� �� ������������ MUTEX
    if ((p_button->internal_input[BUTTON_INT_MUTEX >> 3] & (1 << (BUTTON_INT_MUTEX & ((1 << 3) - 1)))) == 0)
    {
      //MUTEX �� ������������
      
      //��������� ���� ������ ����������
      uint32_t state_tmp = ((p_button->internal_input[BUTTON_INT_ACTIVATION >> 3] & (1 << (BUTTON_INT_ACTIVATION & ((1 << 3) - 1)))) != 0);
      if (state_tmp)
      {
        //������������ �����
        p_button->active_state[BUTTON_OUT >> 3]  |= (1 << (BUTTON_OUT & ((1 << 3) - 1)));
        
        //������� ���������� � �����
        p_button->internal_input[BUTTON_INT_ACTIVATION >> 3] &= (uint8_t)(~(1 << (BUTTON_INT_ACTIVATION & ((1 << 3) - 1))));
      }
    }
    //���������� �������� �� �������� ������
    p_button++;
  }
  /**************************/
    
  /**************************/
  //����������� ������� � ��/Goose
  /**************************/
  if (activation_function_from_interface != 0)
  {

    //������� ������ ��������� ������� � ���������, �� �� ��� ����������
  }
  activation_function_from_interface = 0;
  /**************************/

  /***********************************************************/
  //���������� ���������
  /***********************************************************/
  calc_measurement();
  RdHrdIn((void*)&DiHrdStateUI32Bit);
  
  SetHrdOut((void*)&DoStateUI32Bit);
  SetHrdLed((void*)&LedStateUI32Bit);
  //TmrCalls();
  DoCalcWrp();
  //������� ���������� ��� ����������������� � ����������������� �������
  unsigned int bank_measurement_high_tmp = (bank_measurement_high ^ 0x1) & 0x1;
  if(semaphore_measure_values_low1 == 0)
  {
    for (unsigned int i = 0; i < NUMBER_ANALOG_CANALES; i++) 
    {
      measurement_high[bank_measurement_high_tmp][i] = measurement_middle[i] = measurement[i];
    }
  }
  else
  {
    for (unsigned int i = 0; i < NUMBER_ANALOG_CANALES; i++) 
    {
      measurement_high[bank_measurement_high_tmp][i] = measurement[i];
    }
  }
  bank_measurement_high = bank_measurement_high_tmp;
  /**************************/

  /**************************/
  //������ "������������ �����"
  /**************************/
  diagnostyca_adc_execution();

  unsigned int diagnostyka_tmp[2];
  diagnostyka_tmp[0] = diagnostyka[0];
  diagnostyka_tmp[1] = diagnostyka[1];

  diagnostyka_tmp[0] &= (unsigned int)(~clear_diagnostyka[0]); 
  diagnostyka_tmp[0] |= set_diagnostyka[0]; 

  diagnostyka_tmp[1] &= (unsigned int)(~clear_diagnostyka[1]); 
  diagnostyka_tmp[1] |= set_diagnostyka[1]; 

  _CLEAR_BIT(diagnostyka_tmp, EVENT_START_SYSTEM_BIT);
  _CLEAR_BIT(diagnostyka_tmp, EVENT_DROP_POWER_BIT);
  if (
      (diagnostyka_tmp[0] != 0) ||
      (diagnostyka_tmp[1] != 0)
     )   
  {
    _SET_BIT(fix_block_active_state, FIX_BLOCK_DEFECT);
    /**************************/
    //������ "������������ ���������"
    /**************************/
    if (
        ((diagnostyka_tmp[0] & MASKA_AVAR_ERROR_0) != 0) ||
        ((diagnostyka_tmp[1] & MASKA_AVAR_ERROR_1) != 0)
       )   
    {
      _SET_BIT(fix_block_active_state, FIX_BLOCK_AVAR_DEFECT);
    }
    else
    {
      _CLEAR_BIT(fix_block_active_state, FIX_BLOCK_AVAR_DEFECT);
    }
    /**************************/
  }
  else
  {
    _CLEAR_BIT(fix_block_active_state, FIX_BLOCK_DEFECT);
    _CLEAR_BIT(fix_block_active_state, FIX_BLOCK_AVAR_DEFECT);
  }
  /**************************/

  
  //������ ����� ����� ��������� ����� � ���� �������, ���� ��� ������� "��������� �������������"
  if (_CHECK_SET_BIT(fix_block_active_state, FIX_BLOCK_AVAR_DEFECT) == 0)
  {
    //������� �������� �� �����������

  }
  else
  {
    //������� �������� �����������
    
    //������� �� ������� �������, ��� �������������
    
    //������������ �� ����
    
    //������� �� �������, �� �������� � �����
    
  }

  /**************************/
  //������ � ���������, �� ����� ������������ � ��������������� ���'���
  /**************************/
//  unsigned int comparison_true = true;
//
//  if (comparison_true != true)
//  {
//    /*
//    �������, �������� ���� ���������� � ��������������� ���'1��� ��������.
//    ������ ������� �� �� ����� � ��������������� ���'���
//    */
//    _SET_BIT(control_i2c_taskes, TASK_START_WRITE_TRG_FUNC_EEPROM_BIT);
//  }
  /**************************/
  /**************************/

  /**************************/
  //���� ���������� �� ������
  /**************************/
  
  if (_CHECK_SET_BIT(fix_block_active_state, FIX_BLOCK_AVAR_DEFECT) == 0)
  {
    //�� ����������� ������� ��������, ���� ������������� ���� �����
    
  }
  else
  {
    //����������� ������e ��������, ���� ���������� �� ����!!!

    //������������ �� ����
  }
  
  //�������� ���������� �� ������� �� ��� ��������� (� ����������� �������)
//  unsigned int temp_state_outputs = 0;
//  for (unsigned int index = 0; index < NUMBER_OUTPUTS; index++)
//  {
//    if ((state_outputs & (1 << index)) != 0)
//    {
//      if (index < NUMBER_OUTPUTS_1)
//        temp_state_outputs |= 1 << (NUMBER_OUTPUTS_1 - index - 1);
//      else
//        temp_state_outputs |= 1 << index;
//    }
//  }
//  unsigned int temp_state_outputs_1 =  temp_state_outputs                      & ((1 << NUMBER_OUTPUTS_1) - 1);
//  unsigned int temp_state_outputs_2 = (temp_state_outputs >> NUMBER_OUTPUTS_1) & ((1 << NUMBER_OUTPUTS_2) - 1);
//  _DEVICE_REGISTER(Bank1_SRAM2_ADDR, OFFSET_OUTPUTS_1) = temp_state_outputs_1;
//  _DEVICE_REGISTER(Bank1_SRAM2_ADDR, OFFSET_OUTPUTS_2) = temp_state_outputs_2;
  /**************************/

  /**************************/
  //���� ���������� �� ���������
  /**************************/
  //�������� ����������, �� �� �������������� ������� "����� ���������" - � ���� ���, �� ���������� ������� ��� ���������
  
  //�������� ���������� �� ��������������� �� ���������
//  _DEVICE_REGISTER(Bank1_SRAM2_ADDR, OFFSET_LEDS) = state_leds;
  /**************************/

  /**************************/
  //
  /**************************/
  /**************************/
}
/*****************************************************/

/*****************************************************/
//����������� �� ������� TIM2, ���� ��������� ������� �������
/*****************************************************/
void TIM2_IRQHandler(void)
{
#ifdef SYSTEM_VIEWER_ENABLE
  SEGGER_SYSVIEW_RecordEnterISR();
#endif
  
  if (TIM_GetITStatus(TIM2, TIM_IT_CC1) != RESET)
  {
    /***********************************************************************************************/
    //����������� �������� �� ������ 1, ���� ������ ����������� ����� 1 ��, ��� ��������������� ������� � ������ �������
    /***********************************************************************************************/
    TIM2->SR = (uint16_t)((~(uint32_t)TIM_IT_CC1) & 0xffff);
    uint32_t current_tick = TIM2->CCR1;
    
    /***********************************************************/
    //���������� ������� �������� � ���������� ����� ����� ���� ��������� ������ ���������
    /***********************************************************/
//    clocking_global_timers();
    /***********************************************************/
    
    /***********************************************************/
    //���������� ������� �������
    /***********************************************************/
//    //ĳ��������� �����, ��� ����� ��������� ����� ��� ����� �������� ��������������� ����� ��������
//    unsigned int control_state_outputs_1 = (( (~((unsigned int)(_DEVICE_REGISTER(Bank1_SRAM2_ADDR, OFFSET_OUTPUTS_1)))) >> 8) & ((1 << NUMBER_OUTPUTS_1) - 1));
//    unsigned int control_state_outputs_2 = (( (~((unsigned int)(_DEVICE_REGISTER(Bank1_SRAM2_ADDR, OFFSET_OUTPUTS_2)))) >> 8) & ((1 << NUMBER_OUTPUTS_2) - 1));
//    unsigned int control_state_outputs = control_state_outputs_1 | (control_state_outputs_2 << NUMBER_OUTPUTS_1);
//    //������� ����� ������ � ���������� �� ������ ���������
//    unsigned int temp_state_outputs = 0;
//    for (unsigned int index = 0; index < NUMBER_OUTPUTS; index++)
//    {
//      if ((state_outputs & (1 << index)) != 0) 
//      {
//        if (index < NUMBER_OUTPUTS_1)
//          temp_state_outputs |= 1 << (NUMBER_OUTPUTS_1 - index - 1);
//        else
//          temp_state_outputs |= 1 << index;
//      }
//    }
//    if (control_state_outputs != temp_state_outputs) _SET_BIT(set_diagnostyka, ERROR_DIGITAL_OUTPUTS_BIT);
////    else _SET_BIT(clear_diagnostyka, ERROR_DIGITAL_OUTPUTS_BIT);
    
    //������� �������
    main_protection();
    /***********************************************************/

    /***********************************************************/
    //���������� ������������ ������� ������� ����
    /***********************************************************/
    //������ ����
    if (
        ((clean_rejestrators & MASKA_FOR_BIT(CLEAN_LOG_BIT)) != 0)
        &&  
        (
         (control_tasks_dataflash & (
                                     MASKA_FOR_BIT(TASK_WRITE_LOG_RECORDS_INTO_DATAFLASH_BIT   ) |
                                     MASKA_FOR_BIT(TASK_MAMORY_READ_DATAFLASH_FOR_LOG_USB_BIT  ) |
                                     MASKA_FOR_BIT(TASK_MAMORY_READ_DATAFLASH_FOR_LOG_RS485_BIT) |
                                     MASKA_FOR_BIT(TASK_MAMORY_READ_DATAFLASH_FOR_LOG_MENU_BIT )
                                    )
         ) == 0
        )
       )   
    {
      //���������� ������� �������� ������ ����

      //����������� ������� ������ ���� ��������� � EEPROM
      _SET_BIT(control_i2c_taskes, TASK_START_WRITE_INFO_REJESTRATOR_LOG_EEPROM_BIT);

      //������� ��������� ���������� �� ������ ����
      info_rejestrator_log.next_address = info_rejestrator_log.previous_address = MIN_ADDRESS_LOG_AREA;
      info_rejestrator_log.number_records = 0;

      //�������, �� ����� ������ �� ��������
      number_record_of_log_into_menu  = 0xffff;
      number_record_of_log_into_USB   = 0xffff;
      number_record_of_log_into_RS485 = 0xffff;

      //������� ������� ������� ������� ����
      clean_rejestrators &= (unsigned int)(~MASKA_FOR_BIT(CLEAN_LOG_BIT));
    }
    /***********************************************************/
    
    /***********************************************************/
    //ϳ����������� ����� ����� ��� ������� ����
    /***********************************************************/
    /***********************************************************/
    
    /***********************************************************/
    //�������� �� ������������ ������� �������� ���� ����� ��� ������������
    /***********************************************************/
    //��������� ���������� ����
    if (periodical_tasks_TEST_INFO_REJESTRATOR_LOG != 0)
    {
      //����� � ���� ������� ������ ������� �������� ��ﳿ �����
      if ((state_i2c_task & MASKA_FOR_BIT(STATE_INFO_REJESTRATOR_LOG_EEPROM_GOOD_BIT)) != 0)
      {
        //������ ���� ����� ���, ���� ��������� ���������� ���������� ������ ������� � ���������� ���������� ����
        if (
            (_CHECK_SET_BIT(control_i2c_taskes, TASK_START_WRITE_INFO_REJESTRATOR_LOG_EEPROM_BIT) == 0) &&
            (_CHECK_SET_BIT(control_i2c_taskes, TASK_WRITING_INFO_REJESTRATOR_LOG_EEPROM_BIT    ) == 0) &&
            (_CHECK_SET_BIT(control_i2c_taskes, TASK_START_READ_INFO_REJESTRATOR_LOG_EEPROM_BIT ) == 0) &&
            (_CHECK_SET_BIT(control_i2c_taskes, TASK_READING_INFO_REJESTRATOR_LOG_EEPROM_BIT    ) == 0)
           ) 
        {
          //�� ����� ������� �� ��� �������-����� ��������� ���������� ����������, ���� ����� �������� ���������
          info_rejestrator_log_ctrl = info_rejestrator_log;
          crc_info_rejestrator_log_ctrl = crc_info_rejestrator_log;

          //������� ������� ������ ���������� �������� ��ﳿ 
          periodical_tasks_TEST_INFO_REJESTRATOR_LOG = false;
          //����������� ������� ������ �������� ����������� �� ��������� ��ﳿ 
          periodical_tasks_TEST_INFO_REJESTRATOR_LOG_LOCK = true;
        }
      }
      else
      {
        //������� ������� ������ ���������� �������� ��ﳿ 
        periodical_tasks_TEST_INFO_REJESTRATOR_LOG = false;
      }
    }
    /***********************************************************/

    /***********************************************************/
    //�������� �� ������������ ������� �������� ��ﳿ ����� ��� ������������
    /***********************************************************/
    //������� ����������
    if (periodical_tasks_TEST_TRG_FUNC != 0)
    {
      //����� � ���� ������� ������ ������� �������� ��ﳿ �����
      if ((state_i2c_task & MASKA_FOR_BIT(STATE_TRG_FUNC_EEPROM_GOOD_BIT)) != 0)
      {
        //������ ���� ����� ���, ���� ������� ���������� ������ ������� � ���������� ���������� ����
        if (
            (_CHECK_SET_BIT(control_i2c_taskes, TASK_START_WRITE_TRG_FUNC_EEPROM_BIT) == 0) &&
            (_CHECK_SET_BIT(control_i2c_taskes, TASK_WRITING_TRG_FUNC_EEPROM_BIT    ) == 0) &&
            (_CHECK_SET_BIT(control_i2c_taskes, TASK_START_READ_TRG_FUNC_EEPROM_BIT ) == 0) &&
            (_CHECK_SET_BIT(control_i2c_taskes, TASK_READING_TRG_FUNC_EEPROM_BIT    ) == 0)
           ) 
        {
          //�� ����� ������� �� ��� �������-����� ������� ����������, ���� ����� �������� ���������
          for (__id_fb block_tmp = _ID_FB_FIRST_ALL; block_tmp < _ID_FB_LAST_ALL; block_tmp++)
          {
            switch (block_tmp)
            {
            case ID_FB_OUTPUT:
            case ID_FB_LED:
              {
                size_t n_max_block = ((block_tmp == ID_FB_OUTPUT) ? current_config_prt.n_output : current_config_prt.n_led);
                size_t n_max = DIV_TO_HIGHER(TRIGGER_D_TRIGGER_TOTAL, 8);
                for (size_t n_block = 0; n_block < n_max_block; n_block++)
                {
                  uint8_t *array_source = (((__LN_OUTPUT_LED*)spca_of_p_prt[block_tmp - _ID_FB_FIRST_VAR]) + n_block)->d_trigger_state_tmp;
                  uint8_t *array_target = (((__LN_OUTPUT_LED*)spca_of_p_prt[block_tmp - _ID_FB_FIRST_VAR]) + n_block)->d_trigger_state;
                  for (size_t n = 0; n < n_max; n++) array_source[n] = array_target[n];
                }
                break;
              }
            case ID_FB_ALARM:
              {
                size_t n_max_block = current_config_prt.n_alarm;
                size_t n_max = DIV_TO_HIGHER(ALARM_D_TRIGGER_TOTAL, 8);
                for (size_t n_block = 0; n_block < n_max_block; n_block++)
                {
                  uint8_t *array_source = (((__LN_ALARM*)spca_of_p_prt[ID_FB_ALARM - _ID_FB_FIRST_VAR]) + n_block)->d_trigger_state_tmp;
                  uint8_t *array_target = (((__LN_ALARM*)spca_of_p_prt[ID_FB_ALARM - _ID_FB_FIRST_VAR]) + n_block)->d_trigger_state;
                  for (size_t n = 0; n < n_max; n++) array_source[n] = array_target[n];
                }
                break;
              }
            case ID_FB_TRIGGER:
              {
                size_t n_max_block = current_config_prt.n_trigger;
                size_t n_max = DIV_TO_HIGHER(TRIGGER_D_TRIGGER_TOTAL, 8);
                for (size_t n_block = 0; n_block < n_max_block; n_block++)
                {
                  uint8_t *array_source = (((__LN_TRIGGER*)spca_of_p_prt[ID_FB_TRIGGER - _ID_FB_FIRST_VAR]) + n_block)->d_trigger_state_tmp;
                  uint8_t *array_target = (((__LN_TRIGGER*)spca_of_p_prt[ID_FB_TRIGGER - _ID_FB_FIRST_VAR]) + n_block)->d_trigger_state;
                  for (size_t n = 0; n < n_max; n++) array_source[n] = array_target[n];
                }
                break;
              }
            }
          }
          crc_trg_func_ctrl = crc_trg_func;

          //������� ������� ������ ���������� �������� ��ﳿ 
          periodical_tasks_TEST_TRG_FUNC = false;
          //����������� ������� ������ �������� ����������� �� ��������� ��ﳿ 
          periodical_tasks_TEST_TRG_FUNC_LOCK = true;
        }
      }
      else
      {
        //������� ������� ������ ���������� �������� ��ﳿ 
        periodical_tasks_TEST_TRG_FUNC = false;
      }
    }
    /***********************************************************/

    /***********************************************************/
    //������������ "�������� ��������� ��� ���������� �����������"
    /***********************************************************/
    uint32_t capture_new;
    unsigned int delta;
    TIM2->CCR1 = (capture_new = (current_tick + (delta = TIM2_CCR1_VAL)));
    
    unsigned int repeat;
    unsigned int previous_tick;
    do
    {
      repeat = 0;
      current_tick = TIM2->CNT;

      uint64_t delta_time = 0;
      if (capture_new < current_tick)
        delta_time = capture_new + 0x100000000 - current_tick;
      else delta_time = capture_new - current_tick;

      if ((delta_time > delta) || (delta_time == 0))
      {
        if (TIM_GetITStatus(TIM2, TIM_IT_CC1) == RESET)
        {
          if (delta < TIM2_CCR1_VAL)
          {
            uint64_t delta_tick;
            if (current_tick < previous_tick)
              delta_tick = current_tick + 0x100000000 - previous_tick;
            else delta_tick = current_tick - previous_tick;
              
            delta = delta_tick + 1;
          }
          else if (delta == TIM2_CCR1_VAL)
            delta = 1; /*����������, ��� ���� ���������� ����������� �� ����� ������*/
          else
          {
            //���������� ����� ������ �� ���� � ����
            total_error_sw_fixed(83);
          }
          TIM2->CCR1 = (capture_new = (TIM2->CNT +  delta));
          previous_tick = current_tick;
          repeat = 0xff;
        }
      }
    }
    while (repeat != 0);
    /***********************************************************/
    
    /***********************************************************/
    //����������� ����������� ��� ��, ������� ������ �������
    /***********************************************************/
    control_word_of_watchdog |= WATCHDOG_PROTECTION;
    /***********************************************************/
    /***********************************************************************************************/
  }
  else
  {
    total_error_sw_fixed(23);
  }
  
#ifdef SYSTEM_VIEWER_ENABLE
  SEGGER_SYSVIEW_RecordExitISR();
#endif
}
/*****************************************************/

/*****************************************************/
//������� �������� ��� ���� � ������ ����
/*****************************************************/
void event_log_handler(void)
{
  //��������� ������� ��������� ������ � ����� ��� ������� ����
  int32_t number_empty_cells;
  uint32_t head = head_fifo_buffer_log_records, tail = tail_fifo_buffer_log_records;
  number_empty_cells = (int32_t)(tail - head);
  if (
      (number_empty_cells == 0) &&
      (_CHECK_SET_BIT(diagnostyka, ERROR_LOG_OVERLOAD_BIT) == 0)
     )
  {
    number_empty_cells = MAX_NUMBER_RECORDS_LOG_INTO_BUFFER;
  }
  while (number_empty_cells < 0) number_empty_cells += MAX_NUMBER_RECORDS_LOG_INTO_BUFFER;

  /***
  ��� �������� ����
  ***/
  uint8_t *label_to_time_array;
  if (copying_time == 0) label_to_time_array = time;
  else label_to_time_array = time_copy;
  /***/
  
  uint32_t *p_param = ((__LOG_INPUT*)spca_of_p_prt[ID_FB_EVENT_LOG - _ID_FB_FIRST_VAR]); /*���� �� �������� ����� �� ������� �� ����������� ������� �������, ��� ���-������������� �����, �� �������� ���� ��� ��������� �� ������ ���� ��� ���� � ����*/
  uint32_t param;
  
  size_t i = 0;
  while (
         (i < (current_config_prt.n_log*LOG_SIGNALS_IN)) &&
         ((param = (*(++p_param))) != 0) &&
         (number_empty_cells > 0)  
        )   
  {
    uint32_t state_before = (param >> SFIFT_PARAM_INTERNAL_BITS) & MASKA_PARAM_INTERNAL_BITS;
    uint32_t id_input     = (param >> SFIFT_PARAM_ID           ) & MASKA_PARAM_ID ;
    uint32_t n_input      = (param >> SFIFT_PARAM_N            ) & MASKA_PARAM_N  ;
    uint32_t out_input    = (param >> SFIFT_PARAM_OUT          ) & MASKA_PARAM_OUT;
    
    uint32_t state_now;
    uint32_t NNC_now = 0, NNC_before = 0;
    __LN_GROUP_ALARM *point;
    
    switch (id_input)
    {
    case ID_FB_CONTROL_BLOCK:
      {
        state_now = (fix_block_active_state[out_input >> 3] &  (out_input & ((1 << 3) - 1)) != 0);
        break;
      }
    case ID_FB_INPUT:
      {
        state_now = (((__LN_INPUT*)spca_of_p_prt[ID_FB_INPUT - _ID_FB_FIRST_VAR] + n_input)->active_state[out_input >> 3] &  (out_input & ((1 << 3) - 1)) != 0);
        break;
      }
    case ID_FB_OUTPUT:
    case ID_FB_LED:
      {
        state_now = (((__LN_OUTPUT_LED*)spca_of_p_prt[id_input - _ID_FB_FIRST_VAR] + n_input)->active_state[out_input >> 3] &  (out_input & ((1 << 3) - 1)) != 0);
        break;
      }
    case ID_FB_BUTTON:
      {
        state_now = (((__LN_BUTTON*)spca_of_p_prt[ID_FB_BUTTON - _ID_FB_FIRST_VAR] + n_input)->active_state[out_input >> 3] &  (out_input & ((1 << 3) - 1)) != 0);
        break;
      }
    case ID_FB_ALARM:
      {
        state_now = (((__LN_ALARM*)spca_of_p_prt[ID_FB_ALARM - _ID_FB_FIRST_VAR] + n_input)->active_state[out_input >> 3] &  (out_input & ((1 << 3) - 1)) != 0);
        break;
      }
    case ID_FB_GROUP_ALARM:
      {
        point = (__LN_GROUP_ALARM*)spca_of_p_prt[ID_FB_GROUP_ALARM - _ID_FB_FIRST_VAR] + n_input;
        state_now = (point->active_state[out_input >> 3] &  (out_input & ((1 << 3) - 1)) != 0);
        NNC_now = point->NNC;
        NNC_before = point->NNC_before;
        break;
      }
    case ID_FB_AND:
      {
        state_now = (((__LN_AND*)spca_of_p_prt[ID_FB_AND - _ID_FB_FIRST_VAR] + n_input)->active_state[out_input >> 3] &  (out_input & ((1 << 3) - 1)) != 0);
        break;
      }
    case ID_FB_OR:
      {
        state_now = (((__LN_OR*)spca_of_p_prt[ID_FB_OR - _ID_FB_FIRST_VAR] + n_input)->active_state[out_input >> 3] &  (out_input & ((1 << 3) - 1)) != 0);
        break;
      }
    case ID_FB_XOR:
      {
        state_now = (((__LN_XOR*)spca_of_p_prt[ID_FB_XOR - _ID_FB_FIRST_VAR] + n_input)->active_state[out_input >> 3] &  (out_input & ((1 << 3) - 1)) != 0);
        break;
      }
    case ID_FB_NOT:
      {
        state_now = (((__LN_NOT*)spca_of_p_prt[ID_FB_NOT - _ID_FB_FIRST_VAR] + n_input)->active_state[out_input >> 3] &  (out_input & ((1 << 3) - 1)) != 0);
        break;
      }
    case ID_FB_TIMER:
      {
        state_now = (((__LN_TIMER*)spca_of_p_prt[ID_FB_TIMER - _ID_FB_FIRST_VAR] + n_input)->active_state[out_input >> 3] &  (out_input & ((1 << 3) - 1)) != 0);
        break;
      }
    case ID_FB_TRIGGER:
      {
        state_now = (((__LN_TRIGGER*)spca_of_p_prt[ID_FB_TRIGGER - _ID_FB_FIRST_VAR] + n_input)->active_state[out_input >> 3] &  (out_input & ((1 << 3) - 1)) != 0);
        break;
      }
    case ID_FB_MEANDER:
      {
        state_now = (((__LN_MEANDER*)spca_of_p_prt[ID_FB_MEANDER - _ID_FB_FIRST_VAR] + n_input)->active_state[out_input >> 3] &  (out_input & ((1 << 3) - 1)) != 0);
        break;
      }
    case ID_FB_TU:
      {
        state_now = (((__LN_TU*)spca_of_p_prt[ID_FB_TU - _ID_FB_FIRST_VAR] + n_input)->active_state[out_input >> 3] &  (out_input & ((1 << 3) - 1)) != 0);
        break;
      }
    case ID_FB_TS:
      {
        state_now = (((__LN_TS*)spca_of_p_prt[ID_FB_TS - _ID_FB_FIRST_VAR] + n_input)->active_state[out_input >> 3] &  (out_input & ((1 << 3) - 1)) != 0);
        break;
      }
    case ID_FB_EVENT_LOG:
      {
        state_now = (*((__LOG_INPUT*)spca_of_p_prt[ID_FB_EVENT_LOG - _ID_FB_FIRST_VAR]) & (out_input & ((1 << 5) - 1)) != 0);
        break;
      }
    default:
      {
        //���� ���� ����� ��������, ������� �������� ����������� �������, ���� ����� ��������� ��������, ��� ���� ���� �� ������������
        total_error_sw_fixed(6);
      }
    }
        
    if (
        (state_before != state_now) ||
        (
         (id_input == ID_FB_GROUP_ALARM) &&
         (state_now == true) && 
         (NNC_now != NNC_before)  
        )   
       )   
    {
      //� �� ���������� � ������ ����

      /***
      ��������� ������ � ����� ����� ������� ���� � ����� ����� ������ ����������� ����
      ***/
      uint32_t index_into_buffer_log = head*SIZE_ONE_RECORD_LOG;
      /***/
      
      /***
      ������� ��� �����
      ***/
      //������� ���� ������� ������
      buffer_log_records[index_into_buffer_log++] = LABEL_START_RECORD_LOG;
      //���� � ��� ��䳿
      for(size_t j = 0; j < 7; j++) buffer_log_records[index_into_buffer_log++] = *(label_to_time_array + j);
      
      //��������� ����� ���� � ���� ���������
      param = (param & (uint32_t)(~(MASKA_PARAM_INTERNAL_BITS << SFIFT_PARAM_INTERNAL_BITS))) | ((state_now & MASKA_PARAM_INTERNAL_BITS) << SFIFT_PARAM_INTERNAL_BITS);
      *p_param = param;
      
      buffer_log_records[index_into_buffer_log++] = (param >> (0*8)) & 0xff;
      buffer_log_records[index_into_buffer_log++] = (param >> (1*8)) & 0xff;
      buffer_log_records[index_into_buffer_log++] = (param >> (2*8)) & 0xff;
      buffer_log_records[index_into_buffer_log++] = (param >> (3*8)) & 0xff;

      buffer_log_records[index_into_buffer_log] = NNC_now;
      if (id_input == ID_FB_GROUP_ALARM)
      {
        point->NNC_before = NNC_now;
      } 
      /***/

      /***
      ĳ� �� ���������� ���������� ������
      ***/
      //ʳ������ ������ ��������� ��� ������
      number_empty_cells--;
          
      //Head ������ FIFO
      head++;
      while (head >= MAX_NUMBER_RECORDS_LOG_INTO_BUFFER) head -= MAX_NUMBER_RECORDS_LOG_INTO_BUFFER;
      /***/
    }
    
    i++;
  }
  head_fifo_buffer_log_records = head;

  if  (
       (number_empty_cells == 0) &&
       (param != 0) &&
       (i < (current_config_prt.n_log*LOG_SIGNALS_IN))
      ) 
  {
    _SET_BIT(set_diagnostyka, ERROR_LOG_OVERLOAD_BIT);
  }
  else
  {
    _SET_BIT(clear_diagnostyka, ERROR_LOG_OVERLOAD_BIT);
  }
}
/*****************************************************/


