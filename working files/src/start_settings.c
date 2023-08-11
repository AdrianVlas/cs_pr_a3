#include "header.h"

#ifdef TEST_MODE

const uint8_t string_test_info[MAX_NAMBER_LANGUAGE][1][MAX_COL_LCD + 1] = 
{
  {
    " ���.���������  "
  },
  {
    "̳�.������������"
  },
  {
    "  Min.settings  "
  },
  {
    " ���.���������  "
  } 
};
#endif

const uint8_t string_info[MAX_NAMBER_LANGUAGE][7][MAX_COL_LCD + 1] = 
{
  {
    "������������ ���",
    " ��.������������",
    " ������.�����.�.",
    "  �������� ���  ",
    "  ��.��������   ",
    "  ����.���.���  ",
    "  ��.����.���.  "
  },
  {
    "   ����.����    ",
    "���.������������",
    " ������.�����.�.",
    "����������� ����",
    " ���.�����������",
    " ���.���.����  ",
    " ���.���.���.  "
  },
  {
    "    No Conf.    ",
    "   Conf.Err.    ",
    "No enough dyn.m.",
    "  No settings   ",
    " Settings Err.  ",
    "  ����.���.���  ",
    "  ��.����.���.  "
  },
  {
    "������������ ���",
    " ��.������������",
    " ������.�����.�.",
    "  �������� ���  ",
    "  ��.��������   ",
    "  ����.���.���  ",
    "  ��.����.���.  "
  } 
};
const uint8_t string_action[MAX_NAMBER_LANGUAGE][3][MAX_COL_LCD + 1] =
{
  {
    "���.�����.:Enter",
    " ��������: Enter",
    " ����� 2: Enter "
  },
  {
    "̳�.�����.:Enter",
    " �������: Enter ",
    " ����� 2: Enter "
  },
  {
    "Min.param :Enter",
    "  Reset: Enter  ",
    " Scheme 2: Enter"
  },
  {
    "���.�����.:Enter",
    " ��������: Enter",
    " ����� 2: Enter "
  }
};

const uint8_t name_string_restart[MAX_NAMBER_LANGUAGE][2][MAX_COL_LCD + 1] = 
{
  {
    " �������������  ",
    "   ����������   "
  },
  {
    " ������������  ",
    "    �������    "
  },
  {
    "     Reset      ",
    "   the device   "
  },
  {
    " �������������  ",
    "   ����������   "
  }
};
  
/**************************************/
//���������� �������� SRAM
/**************************************/
inline void test_external_SRAM(void)
{
  //���������� ������� ���������� ���
  unsigned int size_SRAM_word = (((unsigned int)&__ICFEDIT_region_RAM1_size__) + 1) >> 1;
  
  unsigned short int *point = ((unsigned short int *)&__ICFEDIT_region_RAM1_start__);
  unsigned int error = 0, i = 0;
  unsigned short int temp_data;
  while((i < size_SRAM_word) && (error == 0))
  {
    temp_data = *point;
    *point = (unsigned short int)(i & 0xffff);
    if ((*point) == ((unsigned short int)(i & 0xffff)))
    {
      //���� ���� ������ ������� �����
      *point++ = temp_data;
      i++;
    }
    else
    {
      //���� ���� ������ �� ������� �����
      
      error = 0xff;
      //����������� ����������� ��� ������� ����� ������� ���������� ���'��
      if (set_diagnostyka != NULL) _SET_BIT(set_diagnostyka, ERROR_EXTERNAL_SRAM_BIT);
      *point = temp_data;
    }
  }
}
/**************************************/

/**************************************/
//�������� ����������� ������
/**************************************/
void global_vareiables_installation(void)
{
  low_speed_i2c = 0;
  
  /**************************/
  //����������� �������
  /**************************/
  for (unsigned int i = 0; i < NUMBER_INPUTs_ADCs; i++)
  {
    output_adc[i].tick = 0;
    output_adc[i].value = 0;
    
    ustuvannja_shift_work[i] = ustuvannja_shift[i] = ustuvannja_shift_meas[i] = 0;
  }
  
  for (unsigned int i = 0; i < NUMBER_GND_ADC; i++)
  {
    for(unsigned int j = 0; j < NUMBER_POINT; j++)
    {
      gnd_adc_moment_value[i][j] = GND_NORMAL_VALUE;
    }
    gnd_adc_averange_sum[i] = GND_NORMAL_VALUE*NUMBER_POINT;
    gnd_adc_averange[i] = GND_NORMAL_VALUE;
  }
  gnd_adc = GND_NORMAL_VALUE;

  for(unsigned int i = 0; i < NUMBER_POINT; i++)
  {
    vref_adc_moment_value[i] = VREF_NORMAL_VALUE;
    vdd_adc_moment_value[i] = VDD_NORMAL_VALUE;

    vref_adc_moment_value[i] = VREF_NORMAL_VALUE;
    vdd_adc_moment_value[i] = VDD_NORMAL_VALUE;
  }
  
  for(unsigned int i=0; i<(NUMBER_ANALOG_CANALES*NUMBER_POINT*NUMBER_PERIOD_TRANSMIT); i++)
    current_data[i] = 0;
  
  for(unsigned int i=0; i<NUMBER_ANALOG_CANALES; i++)
  {
    ADCs_data_raw[i].tick = 0;
    ADCs_data_raw[i].value = 0;
      
    ustuvannja_meas[i] = ustuvannja[i] = DEFAULT_USTUVANNJA_VALUE;
  }

  /**************************/

  /**************************/
  //����������� ���������� �������
  /**************************/
//  for(unsigned int i = 0; i < MAX_NUMBER_GLOBAL_TIMERS; i++) global_timers[i] = -1;
  /**************************/

  /**************************/
  //
  /**************************/
  /**************************/

  for(unsigned int i = 0; i < MAX_ROW_LCD; i++)
  {
    for (unsigned int j = 0; j < MAX_COL_LCD; j++) working_ekran[i][j] = ' ';
  }
  for (unsigned int i=0; i<NUMBER_KEY_KEYBOARD; i++) time_set_keyboard[i] = 0;
 
  for(enum _menu2_levels i = MAIN_MANU2_LEVEL; i < MAX_NUMBER_MENU2_LEVEL; i++)
  {
    if ((i == PASSWORD_MENU2_LEVEL) || (i == SET_NEW_PASSWORD_MENU2_LEVEL)) position_in_current_level_menu2[i] = INDEX_PASSWORD_M2_LINE1;
    else  position_in_current_level_menu2[i] = 0;
  }
  
  //���������� ����������� ����� ������
  current_state_menu2.current_level = MAIN_MANU2_LEVEL;
  current_state_menu2.index_position = position_in_current_level_menu2[current_state_menu2.current_level];
  current_state_menu2.position_cursor_y = current_state_menu2.index_position;
  current_state_menu2.p_max_row = NULL;
  current_state_menu2.max_row = MAX_ROW_MAIN_M2;
  current_state_menu2.func_move = move_into_main;
  current_state_menu2.func_show = make_ekran_main;
  current_state_menu2.func_press_enter = press_enter_in_ekran_with_request;
  current_state_menu2.func_press_esc = NULL;
  current_state_menu2.func_change = NULL;
  current_state_menu2.binary_data = false;
  current_state_menu2.edition = ED_VIEWING;
  current_state_menu2.edition_option = 0;

  time[0] = 0x0;
  time[1] = 0x0;
  time[2] = 0x0;
  time[3] = 0x0;
  time[4] = 0x0;
  time[5] = 0x0;
  time[6] = 0x0;
  calibration = 0;

  time_copy[0] = 0x0;
  time_copy[1] = 0x0;
  time_copy[2] = 0x0;
  time_copy[3] = 0x0;
  time_copy[4] = 0x0;
  time_copy[5] = 0x0;
  time_copy[6] = 0x0;
  calibration_copy = 0;
  
  /**************************/
  //����������� ��������� ���������� ��������� I2C
  /**************************/
  //���� �����
  driver_i2c.state_execution = -1;
  //������������� ��������, � ���� ������������
  driver_i2c.device_id = -1;
  //��� ��������
  driver_i2c.action =- 1;
  //�������� ����� ���� ���� �� ��� ��� 
  /**************************/
  
  global_component_installation();  
}
/**************************************/

/**************************************/
//������������ I2C
/**************************************/
void Configure_I2C(I2C_TypeDef* I2Cx)
{
  I2C_InitTypeDef  I2C_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
  uint16_t current_count_tim4, new_count_tim4;
  unsigned int delta;

  /* ����������� I2C  */
  I2C_Cmd(I2Cx, DISABLE);

  /***
  ����������, ��� �� SDA ������������ 1
  ***/
  /* ���������� I2C ��� SCL Output Open-drain */
  GPIO_InitStructure.GPIO_Pin = GPIO_I2C_SCL;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_Init(GPIO_I2C, &GPIO_InitStructure);
  /* ������������ ��� SCL � ������� �����*/
  GPIO_SetBits(GPIO_I2C, GPIO_I2C_SCL);
  while(GPIO_ReadOutputDataBit(GPIO_I2C, GPIO_I2C_SCL) == Bit_RESET);

  /*���������� I2C ��� SDA  �� ���*/
  GPIO_InitStructure.GPIO_Pin = GPIO_I2C_SDA;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIO_I2C, &GPIO_InitStructure);
  
  while(GPIO_ReadInputDataBit(GPIO_I2C, GPIO_I2C_SDA) == RESET)
  {
    /* SCL -> "0" */
    GPIO_ResetBits(GPIO_I2C, GPIO_I2C_SCL);
    current_count_tim4 = ((uint16_t)TIM4->CNT);
    delta = 0;
    while (delta < 4) // <= 4x10 = 40(���)
    {
      new_count_tim4 = ((uint16_t)TIM4->CNT);
      if (new_count_tim4 >= current_count_tim4) delta = new_count_tim4 - current_count_tim4;
      else delta = (0x10000 - current_count_tim4) + new_count_tim4; //0x10000 - �� ������ ����� �������, �� �� �������� ���� ���������� �������� [0; 65535]
    }

    /* SCL -> "1" */
    GPIO_SetBits(GPIO_I2C, GPIO_I2C_SCL);
    while(GPIO_ReadOutputDataBit(GPIO_I2C, GPIO_I2C_SCL) == Bit_RESET);
    current_count_tim4 = ((uint16_t)TIM4->CNT);
    delta = 0;
    while (delta < 4) // <= 4x10 = 40(���)
    {
      new_count_tim4 = ((uint16_t)TIM4->CNT);
      if (new_count_tim4 >= current_count_tim4) delta = new_count_tim4 - current_count_tim4;
      else delta = (0x10000 - current_count_tim4) + new_count_tim4; //0x10000 - �� ������ ����� �������, �� �� �������� ���� ���������� �������� [0; 65535]
    }
  }
  /*******/
  
  /***
  ���������� ��� �� �������� ��������������
  ***/
  /* ���������� I2C �� SDA �� Output Open-drain */
  GPIO_InitStructure.GPIO_Pin = GPIO_I2C_SDA;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_Init(GPIO_I2C, &GPIO_InitStructure);
  /* ������������ ��� SCL � SDA � ������� �����*/
  GPIO_SetBits(GPIO_I2C, (GPIO_I2C_SCL | GPIO_I2C_SDA));
  while(GPIO_ReadOutputDataBit(GPIO_I2C, GPIO_I2C_SCL) == Bit_RESET);
  /*******/
  
  /***
  ��������� SOFTWARE RESET ��� EEPROM: Start + 9-bit + Start + Stop 
  ****/

  /*- Start -*/
  /*SCL = 1 � SCA = 1*/

  /* SCL -> "0" */
  GPIO_ResetBits(GPIO_I2C, GPIO_I2C_SCL);
  current_count_tim4 = ((uint16_t)TIM4->CNT);
  delta = 0;
  while (delta < 2) // <= 2x10 = 20(���)
  {
    new_count_tim4 = ((uint16_t)TIM4->CNT);
    if (new_count_tim4 >= current_count_tim4) delta = new_count_tim4 - current_count_tim4;
    else delta = (0x10000 - current_count_tim4) + new_count_tim4; //0x10000 - �� ������ ����� �������, �� �� �������� ���� ���������� �������� [0; 65535]
  }
    
  /* SCL -> "1" */
  GPIO_SetBits(GPIO_I2C, GPIO_I2C_SCL);
  while(GPIO_ReadOutputDataBit(GPIO_I2C, GPIO_I2C_SCL) == Bit_RESET);
  current_count_tim4 = ((uint16_t)TIM4->CNT);
  delta = 0;
  while (delta < 2) // <= 2x10 = 20(���)
  {
    new_count_tim4 = ((uint16_t)TIM4->CNT);
    if (new_count_tim4 >= current_count_tim4) delta = new_count_tim4 - current_count_tim4;
    else delta = (0x10000 - current_count_tim4) + new_count_tim4; //0x10000 - �� ������ ����� �������, �� �� �������� ���� ���������� �������� [0; 65535]
  }
  
  /* SDA -> "0" */
  GPIO_ResetBits(GPIO_I2C, GPIO_I2C_SDA);
  current_count_tim4 = ((uint16_t)TIM4->CNT);
  delta = 0;
  while (delta < 2) // <= 2x10 = 20(���)
  {
    new_count_tim4 = ((uint16_t)TIM4->CNT);
    if (new_count_tim4 >= current_count_tim4) delta = new_count_tim4 - current_count_tim4;
    else delta = (0x10000 - current_count_tim4) + new_count_tim4; //0x10000 - �� ������ ����� �������, �� �� �������� ���� ���������� �������� [0; 65535]
  }

  /* SCL -> "0" */
  GPIO_ResetBits(GPIO_I2C, GPIO_I2C_SCL);
  current_count_tim4 = ((uint16_t)TIM4->CNT);
  delta = 0;
  while (delta < 2) // <= 2x10 = 20(���)
  {
    new_count_tim4 = ((uint16_t)TIM4->CNT);
    if (new_count_tim4 >= current_count_tim4) delta = new_count_tim4 - current_count_tim4;
    else delta = (0x10000 - current_count_tim4) + new_count_tim4; //0x10000 - �� ������ ����� �������, �� �� �������� ���� ���������� �������� [0; 65535]
  }
  
  /* SDA -> "1" */
  GPIO_SetBits(GPIO_I2C, GPIO_I2C_SDA);

  /*- 9 ����� -*/
  for(unsigned int i = 0; i < 9; i++)
  {
    /* SCL = "0" */
    current_count_tim4 = ((uint16_t)TIM4->CNT);
    delta = 0;
    while (delta < 2) // <= 2x10 = 20(���)
    {
      new_count_tim4 = ((uint16_t)TIM4->CNT);
      if (new_count_tim4 >= current_count_tim4) delta = new_count_tim4 - current_count_tim4;
      else delta = (0x10000 - current_count_tim4) + new_count_tim4; //0x10000 - �� ������ ����� �������, �� �� �������� ���� ���������� �������� [0; 65535]
    }

    /* SCL -> "1" */
    GPIO_SetBits(GPIO_I2C, GPIO_I2C_SCL);
    while(GPIO_ReadOutputDataBit(GPIO_I2C, GPIO_I2C_SCL) == Bit_RESET);
    current_count_tim4 = ((uint16_t)TIM4->CNT);
    delta = 0;
    while (delta < 4) // <= 4x10 = 40(���)
    {
      new_count_tim4 = ((uint16_t)TIM4->CNT);
      if (new_count_tim4 >= current_count_tim4) delta = new_count_tim4 - current_count_tim4;
      else delta = (0x10000 - current_count_tim4) + new_count_tim4; //0x10000 - �� ������ ����� �������, �� �� �������� ���� ���������� �������� [0; 65535]
    }

    /* SCL -> "0" */
    GPIO_ResetBits(GPIO_I2C, GPIO_I2C_SCL);
    current_count_tim4 = ((uint16_t)TIM4->CNT);
    delta = 0;
    while (delta < 2) // <= 2x10 = 20(���)
    {
      new_count_tim4 = ((uint16_t)TIM4->CNT);
      if (new_count_tim4 >= current_count_tim4) delta = new_count_tim4 - current_count_tim4;
      else delta = (0x10000 - current_count_tim4) + new_count_tim4; //0x10000 - �� ������ ����� �������, �� �� �������� ���� ���������� �������� [0; 65535]
    }
  }

  /*- Start -*/
  /*SCL = 0 � SCA = 1*/

  current_count_tim4 = ((uint16_t)TIM4->CNT);
  delta = 0;
  while (delta < 2) // <= 2x10 = 20(���)
  {
    new_count_tim4 = ((uint16_t)TIM4->CNT);
    if (new_count_tim4 >= current_count_tim4) delta = new_count_tim4 - current_count_tim4;
    else delta = (0x10000 - current_count_tim4) + new_count_tim4; //0x10000 - �� ������ ����� �������, �� �� �������� ���� ���������� �������� [0; 65535]
  }
    
  /* SCL -> "1" */
  GPIO_SetBits(GPIO_I2C, GPIO_I2C_SCL);
  while(GPIO_ReadOutputDataBit(GPIO_I2C, GPIO_I2C_SCL) == Bit_RESET);
  current_count_tim4 = ((uint16_t)TIM4->CNT);
  delta = 0;
  while (delta < 2) // <= 2x10 = 20(���)
  {
    new_count_tim4 = ((uint16_t)TIM4->CNT);
    if (new_count_tim4 >= current_count_tim4) delta = new_count_tim4 - current_count_tim4;
    else delta = (0x10000 - current_count_tim4) + new_count_tim4; //0x10000 - �� ������ ����� �������, �� �� �������� ���� ���������� �������� [0; 65535]
  }
  
  /* SDA -> "0" */
  GPIO_ResetBits(GPIO_I2C, GPIO_I2C_SDA);
  current_count_tim4 = ((uint16_t)TIM4->CNT);
  delta = 0;
  while (delta < 2) // <= 2x10 = 20(���)
  {
    new_count_tim4 = ((uint16_t)TIM4->CNT);
    if (new_count_tim4 >= current_count_tim4) delta = new_count_tim4 - current_count_tim4;
    else delta = (0x10000 - current_count_tim4) + new_count_tim4; //0x10000 - �� ������ ����� �������, �� �� �������� ���� ���������� �������� [0; 65535]
  }

  /* SCL -> "0" */
  GPIO_ResetBits(GPIO_I2C, GPIO_I2C_SCL);
  current_count_tim4 = ((uint16_t)TIM4->CNT);
  delta = 0;
  while (delta < 2) // <= 2x10 = 20(���)
  {
    new_count_tim4 = ((uint16_t)TIM4->CNT);
    if (new_count_tim4 >= current_count_tim4) delta = new_count_tim4 - current_count_tim4;
    else delta = (0x10000 - current_count_tim4) + new_count_tim4; //0x10000 - �� ������ ����� �������, �� �� �������� ���� ���������� �������� [0; 65535]
  }

  /*- Stop -*/
  /*SCL = 0 � SCA = 0*/

  current_count_tim4 = ((uint16_t)TIM4->CNT);
  delta = 0;
  while (delta < 2) // <= 2x10 = 20(���)
  {
    new_count_tim4 = ((uint16_t)TIM4->CNT);
    if (new_count_tim4 >= current_count_tim4) delta = new_count_tim4 - current_count_tim4;
    else delta = (0x10000 - current_count_tim4) + new_count_tim4; //0x10000 - �� ������ ����� �������, �� �� �������� ���� ���������� �������� [0; 65535]
  }
    
  /* SCL -> "1" */
  GPIO_SetBits(GPIO_I2C, GPIO_I2C_SCL);
  while(GPIO_ReadOutputDataBit(GPIO_I2C, GPIO_I2C_SCL) == Bit_RESET);
  current_count_tim4 = ((uint16_t)TIM4->CNT);
  delta = 0;
  while (delta < 2) // <= 2x10 = 20(���)
  {
    new_count_tim4 = ((uint16_t)TIM4->CNT);
    if (new_count_tim4 >= current_count_tim4) delta = new_count_tim4 - current_count_tim4;
    else delta = (0x10000 - current_count_tim4) + new_count_tim4; //0x10000 - �� ������ ����� �������, �� �� �������� ���� ���������� �������� [0; 65535]
  }
  
  /* SDA -> "1" */
  GPIO_SetBits(GPIO_I2C, GPIO_I2C_SDA);
  current_count_tim4 = ((uint16_t)TIM4->CNT);
  delta = 0;
  while (delta < 2) // <= 2x10 = 20(���)
  {
    new_count_tim4 = ((uint16_t)TIM4->CNT);
    if (new_count_tim4 >= current_count_tim4) delta = new_count_tim4 - current_count_tim4;
    else delta = (0x10000 - current_count_tim4) + new_count_tim4; //0x10000 - �� ������ ����� �������, �� �� �������� ���� ���������� �������� [0; 65535]
  }

  /* SCL -> "0" */
  GPIO_ResetBits(GPIO_I2C, GPIO_I2C_SCL);
  current_count_tim4 = ((uint16_t)TIM4->CNT);
  delta = 0;
  while (delta < 2) // <= 2x10 = 20(���)
  {
    new_count_tim4 = ((uint16_t)TIM4->CNT);
    if (new_count_tim4 >= current_count_tim4) delta = new_count_tim4 - current_count_tim4;
    else delta = (0x10000 - current_count_tim4) + new_count_tim4; //0x10000 - �� ������ ����� �������, �� �� �������� ���� ���������� �������� [0; 65535]
  }

  /* ������������ ��� SCL � SDA � ������� �����*/
  GPIO_SetBits(GPIO_I2C, (GPIO_I2C_SCL | GPIO_I2C_SDA));
  while(GPIO_ReadOutputDataBit(GPIO_I2C, GPIO_I2C_SCL) == Bit_RESET);
  /*******/
  
  /*
  ��������� ��� �� ��������� I2C
  */
  //����������� ��� PB8/I2C1_SCL � PB9/I2C1_SDA
  GPIO_PinAFConfig(GPIO_I2C, GPIO_I2C_SCLSource, GPIO_AF_I2C);
  GPIO_PinAFConfig(GPIO_I2C, GPIO_I2C_SDASource, GPIO_AF_I2C);

  /* ���������� I2C ���: SCL � SDA */
  GPIO_InitStructure.GPIO_Pin =  GPIO_I2C_SCL | GPIO_I2C_SDA;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_Init(GPIO_I2C, &GPIO_InitStructure);
  /*******/

  /* ������� �� I2C ������� */
  I2C_SoftwareResetCmd(I2Cx, ENABLE);
  I2C_SoftwareResetCmd(I2Cx, DISABLE);

  /* ���������� I2C*/
  I2C_Cmd(I2Cx, ENABLE);


  I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
  I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
  I2C_InitStructure.I2C_OwnAddress1 = EEPROM_ADDRESS;
  I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
  I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
  I2C_InitStructure.I2C_ClockSpeed = (low_speed_i2c == 0 ) ? CLOCKSPEED_1MBIT : CLOCKSPEED;
  I2C_Init(I2Cx, &I2C_InitStructure);

  /* ���������� ��� I2C ��������� ���������� �� �������� */
  I2C_ITConfig(I2Cx, I2C_IT_ERR, ENABLE);
}
/**************************************/

/**************************************/
//�������� ����������� ������� ���������
/**************************************/
void start_settings_peripherals(void)
{
  /**********************/
  //������������ ��������������: ���� + �������
  /**********************/
  Set_System();
  /**********************/

  /**********************/
  //���������� DBG ������
  /**********************/
  DBGMCU_APB1PeriphConfig(DBGMCU_TIM2_STOP | DBGMCU_TIM5_STOP | DBGMCU_TIM3_STOP | DBGMCU_TIM4_STOP | DBGMCU_I2C1_SMBUS_TIMEOUT, ENABLE);
  /**********************/

  /**********************/
  //������������ ����������
  /**********************/
  Interrupts_Config();
  /**********************/

  /**********************/
  //������������ ������� ����
  /**********************/
//  FSMC_SRAM_Init();
  _DEVICE_REGISTER(Bank1_SRAM2_ADDR, OFFSET_OUTPUTS_1) = 0;
  _DEVICE_REGISTER(Bank1_SRAM2_ADDR, OFFSET_OUTPUTS_2) = 0;
  _DEVICE_REGISTER(Bank1_SRAM2_ADDR, OFFSET_LEDS) = 0;
  /**********************/

  /**********************/
  //������������ ��� ���������
  /**********************/
  GPIO_InitTypeDef GPIO_InitStructure;

  /**************/
  //ϳ�� �� ����
  /**************/
  /* ϳ� ���������� Watchdog, �� Output push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_PIN_EXTERNAL_WATCHDOG;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_Init(GPIO_EXTERNAL_WATCHDOG, &GPIO_InitStructure);
  /* ������ �� ���������� Watchdog */
  GPIO_ResetBits(GPIO_EXTERNAL_WATCHDOG, GPIO_PIN_EXTERNAL_WATCHDOG);
  
  /*
  �������� �������� ����������� ������? � ���� ������� Watchdog
  ϳ��� ����� ���������� ��������� �������
  
  �� �������, ��� �������� ����������� �������
  */
  /**********************/
  //������� ������� SRAM
  /**********************/
  test_external_SRAM();
  /**********************/
  
  //������� ���� ��� ���������� Watchdog �� �����������
  GPIO_WriteBit(
                GPIO_EXTERNAL_WATCHDOG,
                GPIO_PIN_EXTERNAL_WATCHDOG,
                (BitAction)(1 - GPIO_ReadOutputDataBit(GPIO_EXTERNAL_WATCHDOG, GPIO_PIN_EXTERNAL_WATCHDOG))
               );
    
  /**********************/
  //�������� ����������� ������ � �������� � � ������� SRAM
  /**********************/
  global_vareiables_installation();
  /**********************/
    
  //������� ���� ��� ���������� Watchdog �� �����������
  GPIO_WriteBit(
                GPIO_EXTERNAL_WATCHDOG,
                GPIO_PIN_EXTERNAL_WATCHDOG,
                (BitAction)(1 - GPIO_ReadOutputDataBit(GPIO_EXTERNAL_WATCHDOG, GPIO_PIN_EXTERNAL_WATCHDOG))
               );
  /*****/ 

  /*
  ���������� ���������� ����������� �������  
  */

  /**************/
  //ϳ�� �� ����
  /**************/
  /* ������������ ��� CON-L, �� Output push-pull */
  GPIO_InitStructure.GPIO_Pin = CON_L_PIN;
  GPIO_Init(CON_L, &GPIO_InitStructure);
  /* ������� �� CON-L, ��� ������ ��������� ��������������� �� ����� ����*/
  GPIO_ResetBits(CON_L, CON_L_PIN);

  /* ������������ ��� CON-OUTPUTS, �� Output push-pull */
  GPIO_InitStructure.GPIO_Pin = CON_1_OUTPUTS_PIN;
  GPIO_Init(CON_OUTPUTS, &GPIO_InitStructure);
  /* ������ �� CON-OUTPUTS-1, ��� ������ ��������� �������� �� ����� ����*/
  GPIO_ResetBits(CON_OUTPUTS, CON_1_OUTPUTS_PIN);

  GPIO_InitStructure.GPIO_Pin = CON_2_OUTPUTS_PIN;
  GPIO_Init(CON_OUTPUTS, &GPIO_InitStructure);
  /* ������ �� CON-OUTPUTS-2, ��� ������ ��������� ��������� �� ����� ����*/
  GPIO_ResetBits(CON_OUTPUTS, CON_2_OUTPUTS_PIN);

  GPIO_InitStructure.GPIO_Pin = CON_3_OUTPUTS_PIN;
  GPIO_Init(CON_OUTPUTS, &GPIO_InitStructure);
  /* ������ �� CON-OUTPUTS-3, ��� ������ ��������� �������� �� ����� ����*/
  GPIO_ResetBits(CON_OUTPUTS, CON_3_OUTPUTS_PIN);
  
  /* ������������ ��� LCD-BL, �� Output push-pull */
  GPIO_InitStructure.GPIO_Pin = LCD_BL_PIN;
  GPIO_Init(LCD_BL, &GPIO_InitStructure);
  /* ������������ �� LCD-BL ��� ����, ��� �������� ������� LCD*/
  GPIO_ResetBits(LCD_BL, LCD_BL_PIN);

  /* ������������ ��� LCD-R/W, �� Output push-pull */
  GPIO_InitStructure.GPIO_Pin = LCD_RW_PIN;
  GPIO_Init(LCD_RW, &GPIO_InitStructure);
  /* ������ �� LCD-R/W*/
  GPIO_ResetBits(LCD_RW, LCD_RW_PIN);

  /* ������������ ��� LCD-RS, �� Output push-pull */
  GPIO_InitStructure.GPIO_Pin = LCD_RS_PIN;
  GPIO_Init(LCD_RS, &GPIO_InitStructure);
  /* ������ �� LCD-RS*/
  GPIO_ResetBits(LCD_RS, LCD_RS_PIN);

  /*SW_1 ��������� */
  GPIO_InitStructure.GPIO_Pin = KEYBOARD_SW_1_PIN;
  GPIO_Init(KEYBOARD, &GPIO_InitStructure);
  /* ����������� �� SW1*/
  GPIO_SetBits(KEYBOARD, KEYBOARD_SW_1_PIN);

  /*SW_2 ��������� */
  GPIO_InitStructure.GPIO_Pin = KEYBOARD_SW_2_PIN;
  GPIO_Init(KEYBOARD, &GPIO_InitStructure);
  /* ����������� �� SW2*/
  GPIO_SetBits(KEYBOARD, KEYBOARD_SW_2_PIN);

  /*SW_3 ��������� */
  GPIO_InitStructure.GPIO_Pin = KEYBOARD_SW_3_PIN;
  GPIO_Init(KEYBOARD, &GPIO_InitStructure);
  /*����������� �� SW3*/
  GPIO_SetBits(KEYBOARD, KEYBOARD_SW_3_PIN);

  /*SW_4 ��������� */
  GPIO_InitStructure.GPIO_Pin = KEYBOARD_SW_4_PIN;
  GPIO_Init(KEYBOARD, &GPIO_InitStructure);
  /*����������� �� SW4*/
  GPIO_SetBits(KEYBOARD, KEYBOARD_SW_4_PIN);

  /*���� ��� */
  GPIO_InitStructure.GPIO_Pin = GPIO_SELECTPin_ADC;
  GPIO_Init(GPIO_SELECT_ADC, &GPIO_InitStructure);
  GPIO_ResetBits(GPIO_SELECT_ADC, GPIO_SELECTPin_ADC);

  /*NSS_ADC ������ SPI_ADC */
  GPIO_InitStructure.GPIO_Pin = GPIO_NSSPin_ADC;
  GPIO_Init(GPIO_SPI_ADC, &GPIO_InitStructure);
  GPIO_SetBits(GPIO_SPI_ADC, GPIO_NSSPin_ADC);

  /*NSS_ADC ������ SPI_DF */
  GPIO_InitStructure.GPIO_Pin = GPIO_NSSPin_DF;
  GPIO_Init(GPIO_SPI_DF, &GPIO_InitStructure);
  GPIO_SetBits(GPIO_SPI_DF, GPIO_NSSPin_DF);

  /*GPIO_SPI_DF_TOGGLE - ���� ��������� DataFlash*/
  GPIO_InitStructure.GPIO_Pin = GPIO_SPI_DF_TOGGLE_Pin;
  GPIO_Init(GPIO_SPI_DF_TOGGLE, &GPIO_InitStructure);
  /*�������� ��������� � 1��*/
  GPIO_SetBits(GPIO_SPI_DF_TOGGLE, GPIO_SPI_DF_TOGGLE_Pin);

  /*GPIO_SPI_EDF_A1 - ���� ��������� DataFlash*/
  GPIO_InitStructure.GPIO_Pin = GPIO_SPI_EDF_A1_Pin;
  GPIO_Init(GPIO_SPI_EDF_A1, &GPIO_InitStructure);
  //�������� EEPROM
  GPIO_ResetBits(GPIO_SPI_EDF_A1, GPIO_SPI_EDF_A1_Pin);
  
  /* ϳ� 485DE*/
  GPIO_InitStructure.GPIO_Pin = GPIO_PIN_485DE;
  GPIO_Init(GPIO_485DE, &GPIO_InitStructure);
  /* ������ �� 485DE */
  GPIO_ResetBits(GPIO_485DE, GPIO_PIN_485DE);
  /**************/

  /**************/
  //ϳ�� �� ���
  /**************/
  /*SW_A ��������� */
  GPIO_InitStructure.GPIO_Pin = KEYBOARD_SW_A_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(KEYBOARD_SW_A, &GPIO_InitStructure);

  /*SW_B ��������� */
  GPIO_InitStructure.GPIO_Pin = KEYBOARD_SW_B_PIN;
  GPIO_Init(KEYBOARD_SW_B, &GPIO_InitStructure);

  /*SW_C ��������� */
  GPIO_InitStructure.GPIO_Pin = KEYBOARD_SW_C_PIN;
  GPIO_Init(KEYBOARD_SW_C, &GPIO_InitStructure);

  /*�������� �������� */
  GPIO_InitStructure.GPIO_Pin = POWER_CTRL_PIN;
  GPIO_Init(POWER_CTRL, &GPIO_InitStructure);
  if ((POWER_CTRL->IDR & POWER_CTRL_PIN) == (uint32_t)Bit_RESET)
  {
    if (set_diagnostyka != NULL) _SET_BIT(set_diagnostyka, EVENT_DROP_POWER_BIT);
  }
  /**************/

  /**************/
  //ϳ�� �������������� �������
  /**************/
  //���������� ��� PB13/SPI2_SCK, PB14/SPI2_MISO �  PB15/SPI2_MOSI
  GPIO_PinAFConfig(GPIO_SPI_ADC, GPIO_SCKPin_ADCSource, GPIO_AF_SPI_ADC);
  GPIO_PinAFConfig(GPIO_SPI_ADC, GPIO_MISOPin_ADCSource, GPIO_AF_SPI_ADC);
  GPIO_PinAFConfig(GPIO_SPI_ADC, GPIO_MOSIPin_ADCSource, GPIO_AF_SPI_ADC);

  /* Configure SPI_ADC SCK, MISO � MOSI */
  GPIO_InitStructure.GPIO_Pin = GPIO_SCKPin_ADC | GPIO_MISOPin_ADC | GPIO_MOSIPin_ADC;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_Init(GPIO_SPI_ADC, &GPIO_InitStructure);

  //���������� ��� PA5/SPI1_SCK, PA6/SPI1_MISO �  PA7/SPI1_MOSI
  GPIO_PinAFConfig(GPIO_SPI_DF, GPIO_SCKPin_DFSource, GPIO_AF_SPI_DF);
  GPIO_PinAFConfig(GPIO_SPI_DF, GPIO_MISOPin_DFSource, GPIO_AF_SPI_DF);
  GPIO_PinAFConfig(GPIO_SPI_DF, GPIO_MOSIPin_DFSource, GPIO_AF_SPI_DF);

  /* Configure SPI_DF SCK, MISO � MOSI */
  GPIO_InitStructure.GPIO_Pin = GPIO_SCKPin_DF | GPIO_MISOPin_DF | GPIO_MOSIPin_DF;
  GPIO_Init(GPIO_SPI_DF, &GPIO_InitStructure);

  //���������� ��� PA2/Tx_RS-485, PA3/Rx_RS-485
  GPIO_PinAFConfig(GPIO_USART_RS485, GPIO_TxPin_RS485Source, GPIO_AF_USART_RS_485);
  GPIO_PinAFConfig(GPIO_USART_RS485, GPIO_RxPin_RS485Source, GPIO_AF_USART_RS_485);

  /* Configure USART_RS485 Rx/Tx as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_TxPin_RS485 | GPIO_RxPin_RS485;
  GPIO_Init(GPIO_USART_RS485, &GPIO_InitStructure);
  /**********************/

  /* ϳ�'������� EXTI Line0 to POWER_CTRL_PIN ��� */
  SYSCFG_EXTILineConfig(EXTI_PortSource_POWER, EXTI_PinSource_POWER);  
  /**********************/

   /* �������������� EXTI Line0 */
  EXTI_InitTypeDef   EXTI_InitStructure;

  EXTI_InitStructure.EXTI_Line = EXTI_Line_POWER;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;  
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
  /**********************/

  /**********************/
  //������������ DMA ����������
  /**********************/
  DMA_InitTypeDef  DMA_InitStructure;

  /* DMA ���������� ��� ������� ����� �� I2C*/
  DMA_DeInit(DMA_StreamI2C_Rx);
  while (DMA_GetCmdStatus(DMA_StreamI2C_Rx) != DISABLE);
  
  DMA_InitStructure.DMA_Channel = DMA_ChannelI2C_Rx;
  DMA_InitStructure.DMA_PeripheralBaseAddr = I2C_DR_Address;
  DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)Temporaty_I2C_Buffer;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
  DMA_InitStructure.DMA_BufferSize = SIZE_PAGE_EEPROM + 2;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_MemoryDataSize_Byte;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
  DMA_Init(DMA_StreamI2C_Rx, &DMA_InitStructure);
  DMA_ClearFlag(DMA_StreamI2C_Rx, DMA_FLAG_TCI2C_Rx | DMA_FLAG_HTI2C_Rx | DMA_FLAG_TEII2C_Rx | DMA_FLAG_DMEII2C_Rx | DMA_FLAG_FEII2C_Rx);

  /* DMA ���������� ��� ����������� ����� �� I2C*/
  DMA_DeInit(DMA_StreamI2C_Tx);
  while (DMA_GetCmdStatus(DMA_StreamI2C_Tx) != DISABLE);
  
  DMA_InitStructure.DMA_Channel = DMA_ChannelI2C_Tx;
  DMA_InitStructure.DMA_PeripheralBaseAddr = I2C_DR_Address;
  DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)Temporaty_I2C_Buffer;
  DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;
  DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;
  DMA_Init(DMA_StreamI2C_Tx, &DMA_InitStructure);
  DMA_ClearFlag(DMA_StreamI2C_Tx, DMA_FLAG_TCI2C_Tx | DMA_FLAG_HTI2C_Tx | DMA_FLAG_TEII2C_Tx | DMA_FLAG_DMEII2C_Tx | DMA_FLAG_FEII2C_Tx);

  /* DMA ���������� ��� �������� ����� �� SPI_DF*/
  DMA_DeInit(DMA_StreamSPI_DF_Tx);
  while (DMA_GetCmdStatus(DMA_StreamSPI_DF_Tx) != DISABLE);
  
  DMA_InitStructure.DMA_Channel = DMA_ChannelSPI_DF_Tx;
  DMA_InitStructure.DMA_PeripheralBaseAddr = SPI_DF_DR_Address;
  DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)TxBuffer_SPI_DF;
  DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;
  DMA_InitStructure.DMA_BufferSize = SIZE_BUFFER_SERIAL_DATAFLASH_DMA;
  DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh; /*��� �� � ������ DMA_StreamSPI_DF_Tx > �� � ������ DMA_StreamSPI_DF_Rx, �� DMA_StreamSPI_DF_Rx �� ������� ��� DMA_StreamSPI_DF_Tx ��� ���������� ����������� ��������*/
  DMA_Init(DMA_StreamSPI_DF_Tx, &DMA_InitStructure);
  DMA_ClearFlag(DMA_StreamSPI_DF_Tx, DMA_FLAG_TCSPI_DF_Tx | DMA_FLAG_HTSPI_DF_Tx | DMA_FLAG_TEISPI_DF_Tx | DMA_FLAG_DMEISPI_DF_Tx | DMA_FLAG_FEISPI_DF_Tx);

  /* DMA ���������� ��� ������� ����� �� SPI_DF*/
  DMA_DeInit(DMA_StreamSPI_DF_Rx);
  while (DMA_GetCmdStatus(DMA_StreamSPI_DF_Rx) != DISABLE);
  
  DMA_InitStructure.DMA_Channel = DMA_ChannelSPI_DF_Rx;
  DMA_InitStructure.DMA_PeripheralBaseAddr = SPI_DF_DR_Address;
  DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)RxBuffer_SPI_DF;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
  DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh; /*��� �� � ������ DMA_StreamSPI_DF_Tx > �� � ������ DMA_StreamSPI_DF_Rx, �� DMA_StreamSPI_DF_Rx �� ������� ��� DMA_StreamSPI_DF_Tx ��� ���������� ����������� ��������*/
  DMA_Init(DMA_StreamSPI_DF_Rx, &DMA_InitStructure);
  DMA_ClearFlag(DMA_StreamSPI_DF_Rx, DMA_FLAG_TCSPI_DF_Rx | DMA_FLAG_HTSPI_DF_Rx | DMA_FLAG_TEISPI_DF_Rx | DMA_FLAG_DMEISPI_DF_Rx | DMA_FLAG_FEISPI_DF_Rx);

  /* ������ �� RS-485*/
  DMA_DeInit(DMA_StreamRS485_Rx);
  while (DMA_GetCmdStatus(DMA_StreamRS485_Rx) != DISABLE);
  
  DMA_InitStructure.DMA_Channel = DMA_ChannelRS485_Rx;
  DMA_InitStructure.DMA_PeripheralBaseAddr = USARTRS485_DR_Base;
  DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)RxBuffer_RS485;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
  DMA_InitStructure.DMA_BufferSize = BUFFER_RS485;
  DMA_InitStructure.DMA_Priority = DMA_Priority_Low;
  DMA_Init(DMA_StreamRS485_Rx, &DMA_InitStructure);
  DMA_ClearFlag(DMA_StreamRS485_Rx, DMA_FLAG_TCRS485_Rx | DMA_FLAG_HTRS485_Rx | DMA_FLAG_TEIRS485_Rx | DMA_FLAG_DMEIRS485_Rx | DMA_FLAG_FEIRS485_Rx);
  
  /* �������� �� RS-485*/
  DMA_DeInit(DMA_StreamRS485_Tx);
  while (DMA_GetCmdStatus(DMA_StreamRS485_Tx) != DISABLE);

  DMA_InitStructure.DMA_Channel = DMA_ChannelRS485_Tx;
  DMA_InitStructure.DMA_PeripheralBaseAddr = USARTRS485_DR_Base;
  DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)TxBuffer_RS485;
  DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;
  DMA_InitStructure.DMA_BufferSize = 0;
  DMA_InitStructure.DMA_Priority = DMA_Priority_Low;
  DMA_Init(DMA_StreamRS485_Tx, &DMA_InitStructure);
  DMA_ClearFlag(DMA_StreamRS485_Tx, DMA_FLAG_TCRS485_Tx | DMA_FLAG_HTRS485_Tx | DMA_FLAG_TEIRS485_Tx | DMA_FLAG_DMEIRS485_Tx | DMA_FLAG_FEIRS485_Tx);
  /**********************/

  /**********************/
  //������������ SPI ���  ��� � ���������� ������������ ��
  /**********************/
  SPI_InitTypeDef  SPI_InitStructure;
  
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_16b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
  SPI_InitStructure.SPI_NSS =  SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;/*30���/2 = 15 ���*/
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
  SPI_Init(SPI_ADC, &SPI_InitStructure);

  /* ���������� SPI_ADC */
  SPI_Cmd(SPI_ADC, ENABLE);
  
  //��������� ������ ���
  //������� �������� �������
  if  (SPI_I2S_GetFlagStatus(SPI_ADC, SPI_I2S_FLAG_RXNE) == SET) SPI_I2S_ReceiveData(SPI_ADC);
  while (SPI_I2S_GetFlagStatus(SPI_ADC, SPI_I2S_FLAG_OVR) == SET) SPI_I2S_ReceiveData(SPI_ADC);
      
  for (unsigned int i = 0; i < NUMBER_ADCs; i++)
  {
//    if (i == 0) GPIO_SELECT_ADC->BSRRH = GPIO_SELECTPin_ADC;
//    else GPIO_SELECT_ADC->BSRRL = GPIO_SELECTPin_ADC; 
    
    //�������� ����� ����� 0xffff
    while (SPI_I2S_GetFlagStatus(SPI_ADC, SPI_I2S_FLAG_TXE) == RESET);          //�������, ���� SPI ����� ������
    GPIO_ResetBits(GPIO_SPI_ADC, GPIO_NSSPin_ADC);                              //����������� chip_select
    SPI_I2S_SendData(SPI_ADC, 0xFFFF);                                          //³���������� ����� 0xffff
    while (SPI_I2S_GetFlagStatus(SPI_ADC, SPI_I2S_FLAG_RXNE) == RESET);         //������� ���������� ���������� �� �������� ����� �� MISO
    GPIO_SetBits(GPIO_SPI_ADC, GPIO_NSSPin_ADC);                                //������ chip_select
    SPI_I2S_ReceiveData(SPI_ADC);                                               //������ ������� ���

    //�������� ����� ����� 0xffff
    while (SPI_I2S_GetFlagStatus(SPI_ADC, SPI_I2S_FLAG_TXE) == RESET);          //�������, ���� SPI ����� ������
    GPIO_ResetBits(GPIO_SPI_ADC, GPIO_NSSPin_ADC);                              //����������� chip_select
    SPI_I2S_SendData(SPI_ADC, 0xFFFF);                                          //³���������� ����� 0xffff
    while (SPI_I2S_GetFlagStatus(SPI_ADC, SPI_I2S_FLAG_RXNE) == RESET);         //������� ���������� ���������� �� �������� ����� �� MISO
    GPIO_SetBits(GPIO_SPI_ADC, GPIO_NSSPin_ADC);                                //������ chip_select
    SPI_I2S_ReceiveData(SPI_ADC);                                               //������ ������� ���
  }
  
  //���������� ����������� �� ���������� ����� �� SPI
  SPI_I2S_ITConfig(SPI_ADC, SPI_I2S_IT_RXNE, ENABLE);
  /**********************/

  /**********************/
  //������������ TIM4 �� ��������� ���������� ���� 10 �� ��� ��������� � 1 �� ��� ����������������� �����
  /**********************/
  /* ���������� TIM4 */
  /* ---------------------------------------------------------------
  TIM4 ������������: Output Compare Timing Mode:
  TIM4CLK = (30*2) ���, Prescaler = 600, TIM4 counter clock = 100 ���
  CC1 update rate = TIM4 counter clock / CCR1_Val = 100 Hz
  CC2 update rate = TIM4 counter clock / CCR1_Val = 1000 Hz
  --------------------------------------------------------------- */
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;

  TIM_TimeBaseStructure.TIM_Period = 65535;
  TIM_TimeBaseStructure.TIM_Prescaler = (600-1);
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

  /* Output Compare Timing Mode ������������: �����:1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Timing;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Disable;
  TIM_OCInitStructure.TIM_Pulse = TIM4_CCR1_VAL;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OC1Init(TIM4, &TIM_OCInitStructure);
  
  TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Disable);

  /* ���������� ����������� �� ������ 1 ������� 4*/
  TIM_ITConfig(TIM4, TIM_IT_CC1, ENABLE);

  /* ��������� ������ ������� */
  TIM_Cmd(TIM4, ENABLE);
  /**********************/

  /**********************/
  //����������� I2C
  /**********************/
  Configure_I2C(I2C);
  /**********************/

  /**********************/
  //������ �������� ��� ��������� � EEPROM
  /**********************/
  comparison_writing &= (uint16_t)(~MASKA_FOR_BIT(COMPARISON_WRITING_USTUVANNJA_BIT));/*����������, � �� ���������*/
  _SET_BIT(control_i2c_taskes, TASK_START_READ_USTUVANNJA_EEPROM_BIT);
  while(
        (control_i2c_taskes[0]     != 0) ||
        (control_i2c_taskes[1]     != 0) ||
        (driver_i2c.state_execution > 0)
       )
  {
    //������ � watchdogs
    if ((control_word_of_watchdog & WATCHDOG_KYYBOARD) == WATCHDOG_KYYBOARD)
    {
      //������� ���� ��� ���������� Watchdog �� �����������
      GPIO_WriteBit(
                    GPIO_EXTERNAL_WATCHDOG,
                    GPIO_PIN_EXTERNAL_WATCHDOG,
                    (BitAction)(1 - GPIO_ReadOutputDataBit(GPIO_EXTERNAL_WATCHDOG, GPIO_PIN_EXTERNAL_WATCHDOG))
                   );
      control_word_of_watchdog &= (uint32_t)(~WATCHDOG_KYYBOARD);
    }

    main_routines_for_i2c();
    changing_diagnostyka_state();//ϳ����������� ����� ���������� �������� ����� ��� ���������� ���������� ����
    if (_CHECK_SET_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT) != 0)
    {
      //����� ���������������� ����� � ����������� ��� �������� I2C
      _CLEAR_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT);
    }
  }
  /**********************/

  /**********************/
  //������ �������� ��� ������� ���� � EEPROM
  /**********************/
  comparison_writing &= (uint16_t)(~MASKA_FOR_BIT(COMPARISON_WRITING_INFO_REJESTRATOR_LOG_BIT));/*����������, � �� ���������*/
  _SET_BIT(control_i2c_taskes, TASK_START_READ_INFO_REJESTRATOR_LOG_EEPROM_BIT);
  while(
        (control_i2c_taskes[0]     != 0) ||
        (control_i2c_taskes[1]     != 0) ||
        (driver_i2c.state_execution > 0)
       )
  {
    //������ � watchdogs
    if ((control_word_of_watchdog & WATCHDOG_KYYBOARD) == WATCHDOG_KYYBOARD)
    {
      //������� ���� ��� ���������� Watchdog �� �����������
      GPIO_WriteBit(
                    GPIO_EXTERNAL_WATCHDOG,
                    GPIO_PIN_EXTERNAL_WATCHDOG,
                    (BitAction)(1 - GPIO_ReadOutputDataBit(GPIO_EXTERNAL_WATCHDOG, GPIO_PIN_EXTERNAL_WATCHDOG))
                   );
      control_word_of_watchdog &= (uint32_t)(~WATCHDOG_KYYBOARD);
    }

    main_routines_for_i2c();
    changing_diagnostyka_state();//ϳ����������� ����� ���������� �������� ����� ��� ���������� ���������� ����
    if (_CHECK_SET_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT) != 0)
    {
      //����� ���������������� ����� � ����������� ��� �������� I2C
      _CLEAR_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT);
    }
  }
  /**********************/

  /**********************/
  //������ �������� ��� ���������� ���������� ���� � EEPROM
  /**********************/
  comparison_writing &= (uint16_t)(~MASKA_FOR_BIT(COMPARISON_WRITING_INFO_REJESTRATOR_PR_ERR_BIT));/*����������, � �� ���������*/
  _SET_BIT(control_i2c_taskes, TASK_START_READ_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT);
  while(
        (control_i2c_taskes[0]     != 0) ||
        (control_i2c_taskes[1]     != 0) ||
        (driver_i2c.state_execution > 0)
       )
  {
    //������ � watchdogs
    if ((control_word_of_watchdog & WATCHDOG_KYYBOARD) == WATCHDOG_KYYBOARD)
    {
      //������� ���� ��� ���������� Watchdog �� �����������
      GPIO_WriteBit(
                    GPIO_EXTERNAL_WATCHDOG,
                    GPIO_PIN_EXTERNAL_WATCHDOG,
                    (BitAction)(1 - GPIO_ReadOutputDataBit(GPIO_EXTERNAL_WATCHDOG, GPIO_PIN_EXTERNAL_WATCHDOG))
                   );
      control_word_of_watchdog &= (uint32_t)(~WATCHDOG_KYYBOARD);
    }

    main_routines_for_i2c();
    changing_diagnostyka_state();//ϳ����������� ����� ���������� �������� ����� ��� ���������� ���������� ����
    if (_CHECK_SET_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT) != 0)
    {
      //����� ���������������� ����� � ����������� ��� �������� I2C
      _CLEAR_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT);
    }
  }
  /**********************/

  /**********************/
  //������ �������� ��� ������������ � EEPROM
  /**********************/
  comparison_writing &= (uint16_t)(~MASKA_FOR_BIT(COMPARISON_WRITING_CONFIG_BIT));/*����������, � �� ���������*/
  _SET_BIT(control_i2c_taskes, TASK_START_READ_CONFIG_EEPROM_BIT);
  while(
        (control_i2c_taskes[0]     != 0) ||
        (control_i2c_taskes[1]     != 0) ||
        (driver_i2c.state_execution > 0)
       )
  {
    //������ � watchdogs
    if ((control_word_of_watchdog & WATCHDOG_KYYBOARD) == WATCHDOG_KYYBOARD)
    {
      //������� ���� ��� ���������� Watchdog �� �����������
      GPIO_WriteBit(
                    GPIO_EXTERNAL_WATCHDOG,
                    GPIO_PIN_EXTERNAL_WATCHDOG,
                    (BitAction)(1 - GPIO_ReadOutputDataBit(GPIO_EXTERNAL_WATCHDOG, GPIO_PIN_EXTERNAL_WATCHDOG))
                   );
      control_word_of_watchdog &= (uint32_t)(~WATCHDOG_KYYBOARD);
    }

    main_routines_for_i2c();
    changing_diagnostyka_state();//ϳ����������� ����� ���������� �������� ����� ��� ���������� ���������� ����
    if (_CHECK_SET_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT) != 0)
    {
      //����� ���������������� ����� � ����������� ��� �������� I2C
      _CLEAR_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT);
    }
  }
  /**********************/

  if((state_i2c_task & MASKA_FOR_BIT(STATE_CONFIG_EEPROM_GOOD_BIT)) != 0)
  {
    /**********************/
    //������ �������� ��� ��������� � EEPROM
    /**********************/
    comparison_writing &= (uint16_t)(~MASKA_FOR_BIT(COMPARISON_WRITING_SETTINGS_BIT));/*����������, � �� ���������*/
    _SET_BIT(control_i2c_taskes, TASK_START_READ_SETTINGS_EEPROM_BIT);
    while(
          (control_i2c_taskes[0]     != 0) ||
          (control_i2c_taskes[1]     != 0) ||
          (driver_i2c.state_execution > 0)
         )
    {
      //������ � watchdogs
      if ((control_word_of_watchdog & WATCHDOG_KYYBOARD) == WATCHDOG_KYYBOARD)
      {
        //������� ���� ��� ���������� Watchdog �� �����������
        GPIO_WriteBit(
                      GPIO_EXTERNAL_WATCHDOG,
                      GPIO_PIN_EXTERNAL_WATCHDOG,
                      (BitAction)(1 - GPIO_ReadOutputDataBit(GPIO_EXTERNAL_WATCHDOG, GPIO_PIN_EXTERNAL_WATCHDOG))
                     );
        control_word_of_watchdog &= (uint32_t)(~WATCHDOG_KYYBOARD);
      }

      main_routines_for_i2c();
      changing_diagnostyka_state();//ϳ����������� ����� ���������� �������� ����� ��� ���������� ���������� ����
      if (_CHECK_SET_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT) != 0)
      {
        //����� ���������������� ����� � ����������� ��� �������� I2C
        _CLEAR_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT);
      }
    }
    /**********************/

    /**********************/
    //������ �������� ��� ��� �������� ����������
    /**********************/
    comparison_writing &= (uint16_t)(~MASKA_FOR_BIT(COMPARISON_WRITING_TRG_FUNC_BIT));/*����������, � �� ���������*/
    _SET_BIT(control_i2c_taskes, TASK_START_READ_TRG_FUNC_EEPROM_BIT);
    while(
          (control_i2c_taskes[0]     != 0) ||
          (control_i2c_taskes[1]     != 0) ||
          (driver_i2c.state_execution > 0)
        )
    {
      //������ � watchdogs
      if ((control_word_of_watchdog & WATCHDOG_KYYBOARD) == WATCHDOG_KYYBOARD)
      {
        //������� ���� ��� ���������� Watchdog �� �����������
        GPIO_WriteBit(
                      GPIO_EXTERNAL_WATCHDOG,
                      GPIO_PIN_EXTERNAL_WATCHDOG,
                      (BitAction)(1 - GPIO_ReadOutputDataBit(GPIO_EXTERNAL_WATCHDOG, GPIO_PIN_EXTERNAL_WATCHDOG))
                     );
        control_word_of_watchdog &= (uint32_t)(~WATCHDOG_KYYBOARD);
      }

      main_routines_for_i2c();
      changing_diagnostyka_state();//ϳ����������� ����� ���������� �������� ����� ��� ���������� ���������� ����
      if (_CHECK_SET_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT) != 0)
      {
        //����� ���������������� ����� � ����������� ��� �������� I2C
        _CLEAR_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT);
      }
    }
    /**********************/
  }
  else
  {
    /*
    ������� ������������ ��������� ����, ���� ���� ����� ��������� ������������,
    ������� ����������
    
    ���� ������� ����������, �� ��������������� ���������� ����
    */
    //�������, �� ���������� ���� ��������� � ������
    state_i2c_task &= (uint32_t)(~(MASKA_FOR_BIT(STATE_SETTINGS_EEPROM_FAIL_BIT) | MASKA_FOR_BIT(STATE_SETTINGS_EEPROM_GOOD_BIT)));
    state_i2c_task |= MASKA_FOR_BIT(STATE_SETTINGS_EEPROM_EMPTY_BIT);
    //���������� ����������� � ���� ����������
    if (clear_diagnostyka != NULL) _SET_BIT(clear_diagnostyka, ERROR_SETTINGS_EEPROM_BIT);
    if (set_diagnostyka != NULL) _SET_BIT(set_diagnostyka, ERROR_SETTINGS_EEPROM_EMPTY_BIT);

    //�������, �� ���������� ���� � ������
    state_i2c_task &= (uint32_t)(~(MASKA_FOR_BIT(STATE_TRG_FUNC_EEPROM_FAIL_BIT) | MASKA_FOR_BIT(STATE_TRG_FUNC_EEPROM_GOOD_BIT)));
    state_i2c_task |= MASKA_FOR_BIT(STATE_TRG_FUNC_EEPROM_EMPTY_BIT);
    //���������� ����������� � ���� ����������
    if (clear_diagnostyka != NULL) _SET_BIT(clear_diagnostyka, ERROR_TRG_FUNC_EEPROM_BIT);
    if (set_diagnostyka != NULL) _SET_BIT(set_diagnostyka, ERROR_TRG_FUNC_EEPROM_EMPTY_BIT);
  }

  /**********************/
  //����������� ��������� ���������� �� ������ � �������������� � ���������� � ���� ������
  /**********************/
  {
    //�������� ���������� �� ��������������� �� ���������
//    _DEVICE_REGISTER(Bank1_SRAM2_ADDR, OFFSET_LEDS) = state_leds;
    //����������� �� CON-L, ��� ����� ���� ��������� ���������������
    GPIO_SetBits(CON_L, CON_L_PIN);

    //�������� ���������� �� ������� �� ��� ��������� (� ����������� �������)
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
//    unsigned int temp_state_outputs_1 =  temp_state_outputs                      & ((1 << NUMBER_OUTPUTS_1) - 1);
//    unsigned int temp_state_outputs_2 = (temp_state_outputs >> NUMBER_OUTPUTS_1) & ((1 << NUMBER_OUTPUTS_2) - 1);
//    _DEVICE_REGISTER(Bank1_SRAM2_ADDR, OFFSET_OUTPUTS_1) = temp_state_outputs_1;
//    _DEVICE_REGISTER(Bank1_SRAM2_ADDR, OFFSET_OUTPUTS_2) = temp_state_outputs_2;
    //����������� �� CON-OUTPUTS-1, ��� ����� ���� ��������� ��������
    GPIO_SetBits(CON_OUTPUTS, CON_1_OUTPUTS_PIN);
    //������ �� CON-OUTPUTS-2, ��� ����� ���� ��������� ���������
    GPIO_ResetBits(CON_OUTPUTS, CON_2_OUTPUTS_PIN);
    //�����������  �� CON-OUTPUTS-3, ��� ����� ���� ��������� ��������
    GPIO_SetBits(CON_OUTPUTS, CON_3_OUTPUTS_PIN);
  }
  /**********************/

  //����������������� I2C
  low_speed_i2c = 0xff;
  Configure_I2C(I2C);


  /**********************/
  //������������ TIM3 �� ��������� ���������� ���� 1 �� ��� �����
  /**********************/
  /* ���������� TIM3 */
  /* ---------------------------------------------------------------
  TIM3 ������������: Output Compare Timing Mode:
  TIM3CLK = (30*2) ���, Prescaler = 2000, TIM3 counter clock = 30 ���
  CC1 update rate = TIM3 counter clock / CCR1_Val = 1000 Hz
  --------------------------------------------------------------- */
  TIM_TimeBaseStructure.TIM_Period = 65535;
  TIM_TimeBaseStructure.TIM_Prescaler = (2000-1);
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

  /* Output Compare Timing Mode ������������: �����:1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Timing;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Disable;
  TIM_OCInitStructure.TIM_Pulse = TIM3_CCR1_VAL;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OC1Init(TIM3, &TIM_OCInitStructure);
  
  TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Disable);

  /* ���������� ����������� �� ������ 1 ������� 3*/
  TIM_ITConfig(TIM3, TIM_IT_CC1, ENABLE);
  /**********************/

  /**********************/
  //������������ TIM2 �� ��������� ���������� ���� 1 �� ��� ������� �������
  /**********************/
  /* ���������� TIM2 */
  /* ---------------------------------------------------------------
  TIM2 ������������: Output Compare Timing Mode:
  TIM2CLK = 30*2 ���, Prescaler = 2000, TIM2 counter clock = 30 ���
  CC1 update rate = TIM2 counter clock / CCR1_Val = 1000 Hz
  --------------------------------------------------------------- */
  TIM_TimeBaseStructure.TIM_Period = 0xffffffff;
  TIM_TimeBaseStructure.TIM_Prescaler = (2000-1);
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

  /* Output Compare Timing Mode ������������: �����:1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Timing;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Disable;
  TIM_OCInitStructure.TIM_Pulse = TIM2_CCR1_VAL;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OC1Init(TIM2, &TIM_OCInitStructure);
  
  TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Disable);

  /* ���������� ����������� �� ������ 1 ������� 2*/
  TIM_ITConfig(TIM2, TIM_IT_CC1, ENABLE);
  /**********************/

  /**********************/
  //������������ TIM5 �� ��������� ���������� ���� 0,625 ��
  /**********************/
  /* ���������� TIM5 */
  /* ---------------------------------------------------------------
  TIM5 ������������: Output Compare Timing Mode:
  TIM2CLK = 30*2 ���, Prescaler = 1, TIM5 counter clock = 60 ���
  CC1 update rate = TIM5 counter clock / CCR1_Val = 1600 Hz
  --------------------------------------------------------------- */
  TIM_TimeBaseStructure.TIM_Period = 0xffffffff;
  TIM_TimeBaseStructure.TIM_Prescaler = (1-1);
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);

  /* Output Compare Timing Mode ������������: �����:1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Timing;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Disable;
  TIM_OCInitStructure.TIM_Pulse = TIM5_CCR1_VAL;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OC1Init(TIM5, &TIM_OCInitStructure);
  TIM_OC1PreloadConfig(TIM5, TIM_OCPreload_Disable);

  /* ���������� ����������� �� ������ 1 ������� 5*/
  TIM_ITConfig(TIM5, TIM_IT_CC1, ENABLE);
  /**********************/
  
  /**********************/
  //������������ SPI ���  DataFlash � ���������� �������� , �� ��������� ��������� � �������� �����
  /**********************/
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
  SPI_InitStructure.SPI_NSS =  SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = /*SPI_BaudRatePrescaler_4*/SPI_BaudRatePrescaler_2;
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
  SPI_Init(SPI_DF, &SPI_InitStructure);

  /* ����������� SPI_DF DMA Tx ������ */
  SPI_I2S_DMACmd(SPI_DF, SPI_I2S_DMAReq_Tx, DISABLE);
  /* ����������� SPI_DF DMA Rx ������ */
  SPI_I2S_DMACmd(SPI_DF, SPI_I2S_DMAReq_Rx, DISABLE);

  //������� ���������, �� �������� ��� ���������� ������/�������� ����� ��� DMA �� ������ DMA_StreamSPI_DF_Rx � DMA_StreamSPI_DF_Tx
  DMA_ClearFlag(DMA_StreamSPI_DF_Rx, DMA_FLAG_TCSPI_DF_Rx | DMA_FLAG_HTSPI_DF_Rx | DMA_FLAG_TEISPI_DF_Rx | DMA_FLAG_DMEISPI_DF_Rx | DMA_FLAG_FEISPI_DF_Rx);
  DMA_ClearFlag(DMA_StreamSPI_DF_Tx, DMA_FLAG_TCSPI_DF_Tx | DMA_FLAG_HTSPI_DF_Tx | DMA_FLAG_TEISPI_DF_Tx | DMA_FLAG_DMEISPI_DF_Tx | DMA_FLAG_FEISPI_DF_Tx);

  //���������� ����������� �� ������� �� SPI_DF
  SPI_I2S_ITConfig(SPI_DF, SPI_I2S_IT_ERR, ENABLE);

  /* ���������� SPI_DF */
  SPI_Cmd(SPI_DF, ENABLE);
  /**********************/

    //������ � watchdogs
    if ((control_word_of_watchdog & WATCHDOG_KYYBOARD) == WATCHDOG_KYYBOARD)
    {
      //������� ���� ��� ���������� Watchdog �� �����������
      GPIO_WriteBit(
                    GPIO_EXTERNAL_WATCHDOG,
                    GPIO_PIN_EXTERNAL_WATCHDOG,
                    (BitAction)(1 - GPIO_ReadOutputDataBit(GPIO_EXTERNAL_WATCHDOG, GPIO_PIN_EXTERNAL_WATCHDOG))
                   );
      control_word_of_watchdog &= (uint32_t)(~WATCHDOG_KYYBOARD);
    }

  /**********************/
  //����������� USB
  /**********************/
  USBD_Init(&USB_OTG_dev,
#ifdef USE_USB_OTG_HS 
            USB_OTG_HS_CORE_ID,
#else            
            USB_OTG_FS_CORE_ID,
#endif  
            &USR_desc, 
            &USBD_CDC_cb, 
            &USR_cb);
  /**********************/

    //������ � watchdogs
    if ((control_word_of_watchdog & WATCHDOG_KYYBOARD) == WATCHDOG_KYYBOARD)
    {
      //������� ���� ��� ���������� Watchdog �� �����������
      GPIO_WriteBit(
                    GPIO_EXTERNAL_WATCHDOG,
                    GPIO_PIN_EXTERNAL_WATCHDOG,
                    (BitAction)(1 - GPIO_ReadOutputDataBit(GPIO_EXTERNAL_WATCHDOG, GPIO_PIN_EXTERNAL_WATCHDOG))
                   );
      control_word_of_watchdog &= (uint32_t)(~WATCHDOG_KYYBOARD);
    }
}
/**************************************/

/**************************************/
//̳������� ������������
/**************************************/
void min_config(__CONFIG *target_label)
{
  target_label->device_id = VERSIA_PZ;

  target_label->n_input = NUMBER_INPUTS;
  target_label->n_output = NUMBER_OUTPUTS;
  target_label->n_led = NUMBER_LEDS;
  target_label->n_button = NUMBER_BUTTONS;
  
  target_label->n_alarm = 0;
  target_label->n_group_alarm = 0;
  target_label->n_and = 0;
  target_label->n_or = 0;
  target_label->n_xor = 0;
  target_label->n_not = 0;
  target_label->n_timer = 0;
  target_label->n_trigger = 0;
  
  target_label->n_meander = 0;

  target_label->n_tu = 0;
  target_label->n_ts = 0;

  target_label->n_log = 0;
  
  uint8_t *label_to_time_array;
  if (copying_time == 2) label_to_time_array = time_copy;
  else label_to_time_array = time;
     
  for (size_t i = 0; i < 7; i++) target_label->time_config[i] = *(label_to_time_array + i);
  target_label->time_config[7] = DEFAULT_PARAMS_FIX_CHANGES;
}
/**************************************/

/**************************************/
//������������ �������������� ������������ 2
/**************************************/
void scheme2_config(__CONFIG *target_label)
{
  target_label->device_id = VERSIA_PZ;

  target_label->n_input = NUMBER_INPUTS;
  target_label->n_output = NUMBER_OUTPUTS;
  target_label->n_led = NUMBER_LEDS;
  target_label->n_button = NUMBER_BUTTONS;
  
  uint32_t n_group_alarm;
#if (NUMBER_ANALOG_CANALES - 1) > 0 /*���� ����� ����������*/
  n_group_alarm = NUMBER_ANALOG_CANALES - 1; 
#elif
  n_group_alarm = 0; /*���� ����� ����������*/
#endif
  
  uint32_t n_binary_chanal;
#if (NUMBER_INPUTS - 4) > 0 /*Reset, Mute, Block, Test - ������������� � ��� �����*/
  n_binary_chanal = NUMBER_INPUTS - 4;
#elif
  n_binary_chanal = 0;
#endif
  
  target_label->n_group_alarm = n_group_alarm;
  target_label->n_timer = n_group_alarm + n_binary_chanal;
  target_label->n_alarm = target_label->n_timer;
  target_label->n_and = target_label->n_group_alarm;
  target_label->n_or = 4/*Reset, Mute, Block, Test*/ + 
                       DIV_TO_HIGHER(2*n_group_alarm, OR_SIGNALS_IN)/*��������� ������� ��� ���*/ +
                       DIV_TO_HIGHER(target_label->n_alarm + (target_label->n_alarm / OR_SIGNALS_IN) + (((target_label->n_alarm % OR_SIGNALS_IN) != 0) && ((target_label->n_alarm / OR_SIGNALS_IN) != ((target_label->n_alarm + (target_label->n_alarm / OR_SIGNALS_IN)) / OR_SIGNALS_IN))), OR_SIGNALS_IN)/*��'������� MUTE-������ ��� ���*/ + 
                       DIV_TO_HIGHER((target_label->n_alarm - (target_label->n_alarm >> 1)) + ((target_label->n_alarm - (target_label->n_alarm >> 1)) / OR_SIGNALS_IN) + ((((target_label->n_alarm - (target_label->n_alarm >> 1)) % OR_SIGNALS_IN) != 0) && (((target_label->n_alarm - (target_label->n_alarm >> 1)) / OR_SIGNALS_IN) != (((target_label->n_alarm - (target_label->n_alarm >> 1)) + ((target_label->n_alarm - (target_label->n_alarm >> 1)) / OR_SIGNALS_IN)) / OR_SIGNALS_IN))), OR_SIGNALS_IN)/*��'������� ALARM-������ ��� ��� ��� ������� �����������*/ +
                       DIV_TO_HIGHER((target_label->n_alarm >> 1) + ((target_label->n_alarm >> 1) / OR_SIGNALS_IN) + ((((target_label->n_alarm >> 1) % OR_SIGNALS_IN) != 0) && (((target_label->n_alarm >> 1) / OR_SIGNALS_IN) != (((target_label->n_alarm >> 1) + ((target_label->n_alarm >> 1) / OR_SIGNALS_IN)) / OR_SIGNALS_IN))), OR_SIGNALS_IN)/*��'������� ALARM-������ ��� ��� ��� ��������������� �����������*/ +
                       1/*��'������� ������ ��� ��� ALARM-������ ��������������� ��� � ��� ALARM-������ ������� ���*/;
  target_label->n_xor = 0;
  target_label->n_not = 0;
  target_label->n_trigger = 1;
  
  target_label->n_meander = 0;

  target_label->n_tu = 0;
  target_label->n_ts = 0;
  
  target_label->n_log = DIV_TO_HIGHER((
                                       3/*"����������� ��������" + "����������� �������" + "�����"*/ + 
                                       ((target_label->n_input > 4/*Reset, Mute, Block, Test*/) ? (target_label->n_input - 4) : 0) + 
                                       ((target_label->n_output >= 4/*��.�������, ��.�������, ���.�������, ���.�������*/) ? 4 : target_label->n_output) +
                                       ((target_label->n_led >= (n_group_alarm + n_binary_chanal)) ? (n_group_alarm + n_binary_chanal) : target_label->n_led) +
                                       target_label->n_group_alarm*GROUP_ALARM_SIGNALS_OUT
                                      ), LOG_SIGNALS_IN);
                         
  
  uint8_t *label_to_time_array;
  if (copying_time == 2) label_to_time_array = time_copy;
  else label_to_time_array = time;
     
  for (size_t i = 0; i < 7; i++) target_label->time_config[i] = *(label_to_time_array + i);
  target_label->time_config[7] = DEFAULT_PARAMS_FIX_CHANGES;
}
/**************************************/

/**************************************/
//̳������ ������������
/**************************************/
void min_settings(__SETTINGS_FIX *target_label)
{
  target_label->n_iteration = NUMBER_ITERATION_EL_MAX;
  for (size_t i = 0; i < FIX_BLOCK_SIGNALS_IN; i++) target_label->param[i] = 0;

  target_label->password_1 = 0;
  target_label->password_2 = 0;
  target_label->timeout_deactivation_password_interface_USB = TIMEOUT_DEACTIVATION_PASSWORD_MIN;
  target_label->password_interface_USB = 0;
  target_label->timeout_deactivation_password_interface_RS485 = TIMEOUT_DEACTIVATION_PASSWORD_MIN;
  target_label->password_interface_RS485 = 0;
  
  target_label->timeout_idle_new_settings = TIMEOUT_NEW_SETTINGS_MIN;
  
  for(unsigned int i=0; i< ((M_ADDRESS_LAST_USER_REGISTER_DATA - M_ADDRESS_FIRST_USER_REGISTER_DATA) + 1); i++) target_label->user_register[i] = 0;

  for(unsigned int i=0; i<MAX_CHAR_IN_NAME_OF_CELL; i++) target_label->name_of_cell[i] = ' ';
  target_label->name_of_cell[4 ] = 'N';
  target_label->name_of_cell[5 ] = 'o';
  target_label->name_of_cell[7 ] = 'n';
  target_label->name_of_cell[8 ] = 'a';
  target_label->name_of_cell[9 ] = 'm';
  target_label->name_of_cell[10] = 'e';
  
  target_label->address = KOEF_ADDRESS_MIN;
  target_label->baud_RS485 = VALUE_BAUD_RS485_MIN;
  target_label->pare_bit_RS485 = VALUE_PARE_RS485_MAX; //������ ���������� �������� ������� �� ���� � EVEN - � �� ����� ������� VALUE_PARE_INTERFACE_MAX
  target_label->number_stop_bit_RS485 = VALUE_STOP_BITS_RS485_MIN;
  target_label->time_out_1_RS485 = VALUE_TIME_OUT_1_RS485_MIN;
  
  target_label->language = LANGUAGE_EN;
  
  target_label->schematic = 0; /*������� ��������� �����������*/

  uint8_t *label_to_time_array;
  if (copying_time == 2) label_to_time_array = time_copy;
  else label_to_time_array = time;
     
  for (size_t i = 0; i < 7; i++) 
  {
    target_label->time_schematic[i] = target_label->time_setpoints[i] = *(label_to_time_array + i);
  }
  target_label->time_schematic[7] = target_label->time_setpoints[7] = DEFAULT_PARAMS_FIX_CHANGES;
}
/**************************************/

/**************************************/
//̳������ ������������
/**************************************/
void scheme2_settings(__CONFIG *target_config, __SETTINGS_FIX *target_fix_settings,  uintptr_t *target_sca_of_p[])
{
  if (
      (target_sca_of_p == sca_of_p) ||
      (target_sca_of_p == sca_of_p_edit)
     )   
  {
    uint32_t n_binary_chanal;
#if (NUMBER_INPUTS - 4) > 0 /*Reset, Mute, Block, Test - ������������� � ��� �����*/
    n_binary_chanal = NUMBER_INPUTS - 4;
#elif
    n_binary_chanal = 0;
#endif
  
    size_t n;
    /***
    ������� �����: ������� �������������
    ***/
    /***/

    /***
    ������ ����
    ***/
    //����� ������ �����������
    n = 4/*Reset, Mute, Block, Test*/ + 
        DIV_TO_HIGHER(2*target_config->n_group_alarm, OR_SIGNALS_IN)/*��������� ������� ��� ���*/ +
        DIV_TO_HIGHER(target_config->n_alarm + (target_config->n_alarm / OR_SIGNALS_IN) + (((target_config->n_alarm % OR_SIGNALS_IN) != 0) && ((target_config->n_alarm / OR_SIGNALS_IN) != ((target_config->n_alarm + (target_config->n_alarm / OR_SIGNALS_IN)) / OR_SIGNALS_IN))), OR_SIGNALS_IN)/*��'������� MUTE-������ ��� ���*/ + 
        DIV_TO_HIGHER((target_config->n_alarm - (target_config->n_alarm >> 1)) + ((target_config->n_alarm - (target_config->n_alarm >> 1)) / OR_SIGNALS_IN) + ((((target_config->n_alarm - (target_config->n_alarm >> 1)) % OR_SIGNALS_IN) != 0) && (((target_config->n_alarm - (target_config->n_alarm >> 1)) / OR_SIGNALS_IN) != (((target_config->n_alarm - (target_config->n_alarm >> 1)) + ((target_config->n_alarm - (target_config->n_alarm >> 1)) / OR_SIGNALS_IN)) / OR_SIGNALS_IN))), OR_SIGNALS_IN)/*��'������� ALARM-������ ��� ��� ��� ������� �����������*/;

    if ((target_config->n_output >= 6) && (target_config->n_or >= n)) ((__settings_for_OUTPUT_LED*)target_sca_of_p[ID_FB_OUTPUT - _ID_FB_FIRST_VAR] + (6 - 1))->param[OUTPUT_LED_LOGIC_INPUT] = ((ID_FB_OR & MASKA_PARAM_ID) << SFIFT_PARAM_ID) | ((n & MASKA_PARAM_N) << SFIFT_PARAM_N) | (((STANDARD_LOGIC_OUT + 1) & MASKA_PARAM_OUT) << SFIFT_PARAM_OUT);
    if ((target_config->n_output >= 7) && (target_config->n_or >= n)) ((__settings_for_OUTPUT_LED*)target_sca_of_p[ID_FB_OUTPUT - _ID_FB_FIRST_VAR] + (7 - 1))->param[OUTPUT_LED_LOGIC_INPUT] = ((ID_FB_OR & MASKA_PARAM_ID) << SFIFT_PARAM_ID) | ((n & MASKA_PARAM_N) << SFIFT_PARAM_N) | (((STANDARD_LOGIC_OUT + 1) & MASKA_PARAM_OUT) << SFIFT_PARAM_OUT);
    
    n += DIV_TO_HIGHER((target_config->n_alarm >> 1) + ((target_config->n_alarm >> 1) / OR_SIGNALS_IN) + ((((target_config->n_alarm >> 1) % OR_SIGNALS_IN) != 0) && (((target_config->n_alarm >> 1) / OR_SIGNALS_IN) != (((target_config->n_alarm >> 1) + ((target_config->n_alarm >> 1) / OR_SIGNALS_IN)) / OR_SIGNALS_IN))), OR_SIGNALS_IN)/*��'������� ALARM-������ ��� ��� ��� ��������������� �����������*/;

    if ((target_config->n_output >= 3) && (target_config->n_or >= n)) ((__settings_for_OUTPUT_LED*)target_sca_of_p[ID_FB_OUTPUT - _ID_FB_FIRST_VAR] + (3 - 1))->param[OUTPUT_LED_LOGIC_INPUT] = ((ID_FB_OR & MASKA_PARAM_ID) << SFIFT_PARAM_ID) | ((n & MASKA_PARAM_N) << SFIFT_PARAM_N) | (((STANDARD_LOGIC_OUT + 1) & MASKA_PARAM_OUT) << SFIFT_PARAM_OUT);
    if ((target_config->n_output >= 4) && (target_config->n_or >= n)) ((__settings_for_OUTPUT_LED*)target_sca_of_p[ID_FB_OUTPUT - _ID_FB_FIRST_VAR] + (4 - 1))->param[OUTPUT_LED_LOGIC_INPUT] = ((ID_FB_OR & MASKA_PARAM_ID) << SFIFT_PARAM_ID) | ((n & MASKA_PARAM_N) << SFIFT_PARAM_N) | (((STANDARD_LOGIC_OUT + 1) & MASKA_PARAM_OUT) << SFIFT_PARAM_OUT);
    
    n += 1/*��'������� ������ ��� ��� ALARM-������ ��������������� ��� � ��� ALARM-������ ������� ���*/;
    
    if (target_config->n_output >= 5) ((__settings_for_OUTPUT_LED*) target_sca_of_p[ID_FB_OUTPUT - _ID_FB_FIRST_VAR] + (5 - 1))->param[OUTPUT_LED_LOGIC_INPUT] = ((ID_FB_CONTROL_BLOCK & MASKA_PARAM_ID) << SFIFT_PARAM_ID) | ((1 & MASKA_PARAM_N) << SFIFT_PARAM_N) | (((FIX_BLOCK_RUN + 1) & MASKA_PARAM_OUT) << SFIFT_PARAM_OUT);

    for (size_t i = 2; i < 7; i++)
    {
      if ((target_config->n_output >= (i + 1)) && (target_config->n_or >= 1)) ((__settings_for_OUTPUT_LED*)target_sca_of_p[ID_FB_OUTPUT - _ID_FB_FIRST_VAR] + i)->param[OUTPUT_LED_RESET] = ((ID_FB_OR & MASKA_PARAM_ID) << SFIFT_PARAM_ID) | ((1 & MASKA_PARAM_N) << SFIFT_PARAM_N) | (((STANDARD_LOGIC_OUT + 1) & MASKA_PARAM_OUT) << SFIFT_PARAM_OUT);
      else break;
    }
    /***/
    
    /***
    ��������������
    ***/
    for (size_t i = 0; i < target_config->n_group_alarm; i++)
    {
      if ((target_config->n_led >= (i + 1)) && (target_config->n_and >= (i + 1))) ((__settings_for_OUTPUT_LED*)target_sca_of_p[ID_FB_LED - _ID_FB_FIRST_VAR] + i)->param[OUTPUT_LED_LOGIC_INPUT] = ((ID_FB_AND & MASKA_PARAM_ID) << SFIFT_PARAM_ID) | (((i + 1) & MASKA_PARAM_N) << SFIFT_PARAM_N) | (((STANDARD_LOGIC_OUT + 1) & MASKA_PARAM_OUT) << SFIFT_PARAM_OUT);
      else break;
    }
    
    n = target_config->n_group_alarm;
    for (size_t i = 0; i < n_binary_chanal; i++)
    {
      if ((target_config->n_led >= (i + n + 1)) && (target_config->n_timer >= (i + n + 1))) ((__settings_for_OUTPUT_LED*)target_sca_of_p[ID_FB_LED - _ID_FB_FIRST_VAR] + (i + n))->param[OUTPUT_LED_LOGIC_INPUT] = ((ID_FB_TIMER & MASKA_PARAM_ID) << SFIFT_PARAM_ID) | (((i + n + 1) & MASKA_PARAM_N) << SFIFT_PARAM_N) | (((TIMER_OUT_RISE_DELAY + 1) & MASKA_PARAM_OUT) << SFIFT_PARAM_OUT);
      else break;
    }

    n += n_binary_chanal;
    if ((target_config->n_led >= (n + 1)) && (target_config->n_or >= 5)) ((__settings_for_OUTPUT_LED*)target_sca_of_p[ID_FB_LED - _ID_FB_FIRST_VAR] + n)->param[OUTPUT_LED_LOGIC_INPUT] = ((ID_FB_OR & MASKA_PARAM_ID) << SFIFT_PARAM_ID) | ((5 & MASKA_PARAM_N) << SFIFT_PARAM_N) | (((STANDARD_LOGIC_OUT + 1) & MASKA_PARAM_OUT) << SFIFT_PARAM_OUT);

    n += 1;
    if (target_config->n_led >= (n + 1)) ((__settings_for_OUTPUT_LED*)target_sca_of_p[ID_FB_LED - _ID_FB_FIRST_VAR] + n)->param[OUTPUT_LED_LOGIC_INPUT] = ((ID_FB_EVENT_LOG & MASKA_PARAM_ID) << SFIFT_PARAM_ID) | ((1 & MASKA_PARAM_N) << SFIFT_PARAM_N) | (((EVENT_LOG_WORK + 1) & MASKA_PARAM_OUT) << SFIFT_PARAM_OUT);

    n += 1;
    for (size_t i = 0; i < n; i++)
    {
      if ((target_config->n_led >= (i + 1)) && (target_config->n_or >= 1)) ((__settings_for_OUTPUT_LED*)target_sca_of_p[ID_FB_LED - _ID_FB_FIRST_VAR] + i)->param[OUTPUT_LED_RESET] = ((ID_FB_OR & MASKA_PARAM_ID) << SFIFT_PARAM_ID) | ((1 & MASKA_PARAM_N) << SFIFT_PARAM_N) | (((STANDARD_LOGIC_OUT + 1) & MASKA_PARAM_OUT) << SFIFT_PARAM_OUT);
      else break;
    }
    /***/
    
    /***
    ���
    ***/
    for (size_t i = 0; i < target_config->n_alarm; i++)
    {
      if (target_config->n_timer >= (i + 1)) ((__settings_for_ALARM*)target_sca_of_p[ID_FB_ALARM - _ID_FB_FIRST_VAR] + i)->param[ALARM_LOGIC_INPUT] = ((ID_FB_TIMER & MASKA_PARAM_ID) << SFIFT_PARAM_ID) | (((i + 1) & MASKA_PARAM_N) << SFIFT_PARAM_N) | (((TIMER_OUT_RISE_DELAY + 1) & MASKA_PARAM_OUT) << SFIFT_PARAM_OUT);
      else break;

      if (target_config->n_or >= 1) ((__settings_for_ALARM*)target_sca_of_p[ID_FB_ALARM - _ID_FB_FIRST_VAR] + i)->param[ALARM_RESET]    = ((ID_FB_OR & MASKA_PARAM_ID) << SFIFT_PARAM_ID) | ((1 & MASKA_PARAM_N) << SFIFT_PARAM_N) | (((STANDARD_LOGIC_OUT + 1) & MASKA_PARAM_OUT) << SFIFT_PARAM_OUT);
      if (target_config->n_or >= 2) ((__settings_for_ALARM*)target_sca_of_p[ID_FB_ALARM - _ID_FB_FIRST_VAR] + i)->param[ALARM_IN_MUTE]  = ((ID_FB_OR & MASKA_PARAM_ID) << SFIFT_PARAM_ID) | ((2 & MASKA_PARAM_N) << SFIFT_PARAM_N) | (((STANDARD_LOGIC_OUT + 1) & MASKA_PARAM_OUT) << SFIFT_PARAM_OUT);
      if (target_config->n_trigger >= 1) ((__settings_for_ALARM*)target_sca_of_p[ID_FB_ALARM - _ID_FB_FIRST_VAR] + i)->param[ALARM_IN_BLOCK] = ((ID_FB_TRIGGER & MASKA_PARAM_ID) << SFIFT_PARAM_ID) | ((1 & MASKA_PARAM_N) << SFIFT_PARAM_N) | (((TRIGGER_OUT + 1) & MASKA_PARAM_OUT) << SFIFT_PARAM_OUT);
    } 
    /***/
    
    /***
    ���
    ***/
    uint32_t maska = (1 << group_alarm_analog_ctrl_patten[INDEX_CTRL_GROUP_ALARM_I - _MAX_INDEX_CTRL_GROUP_ALARM_BITS_SETTINGS][1]) - 1;
    uint32_t shift = group_alarm_analog_ctrl_patten[INDEX_CTRL_GROUP_ALARM_I - _MAX_INDEX_CTRL_GROUP_ALARM_BITS_SETTINGS][0];
    for (size_t i = 0; i < target_config->n_group_alarm; i++)
    {
      ((__settings_for_GROUP_ALARM*)target_sca_of_p[ID_FB_GROUP_ALARM - _ID_FB_FIRST_VAR] + i)->control = (1 << INDEX_CTRL_GROUP_ALARM_STATE);
      
      size_t i_tmp = i + 1;
      if ((i_tmp >= 1) && (i_tmp <= (NUMBER_ANALOG_CANALES - 1))) ((__settings_for_GROUP_ALARM*)target_sca_of_p[ID_FB_GROUP_ALARM - _ID_FB_FIRST_VAR] + i)->analog_input_control = (i_tmp & maska) << shift;
      else break;
    } 
    /***/
    
    /***
    "�"
    ***/
    for (size_t i = 0; i < target_config->n_and; i++)
    {
      if (target_config->n_group_alarm >= (i + 1)) ((__settings_for_AND*)target_sca_of_p[ID_FB_AND - _ID_FB_FIRST_VAR] + i)->param[0] = ((ID_FB_GROUP_ALARM & MASKA_PARAM_ID) << SFIFT_PARAM_ID) | (((i + 1) & MASKA_PARAM_N) << SFIFT_PARAM_N) | (((GROUP_ALARM_OUT_CC   + 1) & MASKA_PARAM_OUT) << SFIFT_PARAM_OUT);
      if (target_config->n_timer       >= (i + 1)) ((__settings_for_AND*)target_sca_of_p[ID_FB_AND - _ID_FB_FIRST_VAR] + i)->param[1] = ((ID_FB_TIMER       & MASKA_PARAM_ID) << SFIFT_PARAM_ID) | (((i + 1) & MASKA_PARAM_N) << SFIFT_PARAM_N) | (((TIMER_OUT_RISE_DELAY + 1) & MASKA_PARAM_OUT) << SFIFT_PARAM_OUT);
    } 
    /***/
    
    /***
    "���"
    ***/
    for (size_t i = 0; i < target_config->n_or; i++)
    {
      size_t i_tmp = i;
      if (i_tmp < 4)
      {
        uint32_t button;
        switch (i_tmp)
        {
        case 0:
          {
            button = FIX_BUTTON_RESET;
            break;
          }
        case 1:
          {
            button = FIX_BUTTON_MUTE;
            break;
          }
        case 2:
          {
            button = NUMBER_FIX_BUTTONS;
            break;
          }
        case 3:
          {
            button = FIX_BUTTON_TEST;
            break;
          }
        }
        if (target_config->n_input  >= (i_tmp  + 1)) ((__settings_for_OR*)target_sca_of_p[ID_FB_OR - _ID_FB_FIRST_VAR] + i)->param[0] = ((ID_FB_INPUT  & MASKA_PARAM_ID) << SFIFT_PARAM_ID) | (((i_tmp  + 1) & MASKA_PARAM_N) << SFIFT_PARAM_N) | (((INPUT_OUT  + 1) & MASKA_PARAM_OUT) << SFIFT_PARAM_OUT);
        if (target_config->n_button >= (button + 1)) ((__settings_for_OR*)target_sca_of_p[ID_FB_OR - _ID_FB_FIRST_VAR] + i)->param[1] = ((ID_FB_BUTTON & MASKA_PARAM_ID) << SFIFT_PARAM_ID) | (((button + 1) & MASKA_PARAM_N) << SFIFT_PARAM_N) | (((BUTTON_OUT + 1) & MASKA_PARAM_OUT) << SFIFT_PARAM_OUT);
      }
      else if ((i_tmp -= 4) < DIV_TO_HIGHER(2*target_config->n_group_alarm, OR_SIGNALS_IN))
      {
        for (size_t j = 0; j < (OR_SIGNALS_IN >> 1); j++)
        {
          if (target_config->n_group_alarm  >= (i_tmp*(OR_SIGNALS_IN >> 1) + j + 1))
          {
            ((__settings_for_OR*)target_sca_of_p[ID_FB_OR - _ID_FB_FIRST_VAR] + i)->param[(j << 1) + 0] = ((ID_FB_GROUP_ALARM  & MASKA_PARAM_ID) << SFIFT_PARAM_ID) | ((((i_tmp*(OR_SIGNALS_IN >> 1) + j) + 1) & MASKA_PARAM_N) << SFIFT_PARAM_N) | (((GROUP_ALARM_OUT_CE + 1) & MASKA_PARAM_OUT) << SFIFT_PARAM_OUT);
            ((__settings_for_OR*)target_sca_of_p[ID_FB_OR - _ID_FB_FIRST_VAR] + i)->param[(j << 1) + 1] = ((ID_FB_GROUP_ALARM  & MASKA_PARAM_ID) << SFIFT_PARAM_ID) | ((((i_tmp*(OR_SIGNALS_IN >> 1) + j) + 1) & MASKA_PARAM_N) << SFIFT_PARAM_N) | (((GROUP_ALARM_OUT_OC + 1) & MASKA_PARAM_OUT) << SFIFT_PARAM_OUT);
          }
          else break;
        }
      }
      else if ((i_tmp -= DIV_TO_HIGHER(2*target_config->n_group_alarm, OR_SIGNALS_IN)) < DIV_TO_HIGHER(target_config->n_alarm + (target_config->n_alarm / OR_SIGNALS_IN) + (((target_config->n_alarm % OR_SIGNALS_IN) != 0) && ((target_config->n_alarm / OR_SIGNALS_IN) != ((target_config->n_alarm + (target_config->n_alarm / OR_SIGNALS_IN)) / OR_SIGNALS_IN))), OR_SIGNALS_IN))
      {
        for (size_t j = 0; j < OR_SIGNALS_IN; j++)
        {
          if (target_config->n_alarm  >= (i_tmp*OR_SIGNALS_IN + j + 1))
          {
            ((__settings_for_OR*)target_sca_of_p[ID_FB_OR - _ID_FB_FIRST_VAR] + i)->param[j] = ((ID_FB_ALARM  & MASKA_PARAM_ID) << SFIFT_PARAM_ID) | (((i_tmp*OR_SIGNALS_IN + j + 1) & MASKA_PARAM_N) << SFIFT_PARAM_N) | (((ALARM_OUT_MUTE + 1) & MASKA_PARAM_OUT) << SFIFT_PARAM_OUT);
          }
          else if ((i_tmp*OR_SIGNALS_IN + j - target_config->n_alarm) < ((target_config->n_alarm / OR_SIGNALS_IN) + (((target_config->n_alarm % OR_SIGNALS_IN) != 0) && ((target_config->n_alarm / OR_SIGNALS_IN) != ((target_config->n_alarm + (target_config->n_alarm / OR_SIGNALS_IN)) / OR_SIGNALS_IN)))))
          {
            size_t _n = 4/*Reset, Mute, Block, Test*/ + 
            DIV_TO_HIGHER(2*target_config->n_group_alarm, OR_SIGNALS_IN)/*��������� ������� ��� ���*/ + 
            (i_tmp*OR_SIGNALS_IN + j - target_config->n_alarm);
            ((__settings_for_OR*)target_sca_of_p[ID_FB_OR - _ID_FB_FIRST_VAR] + i)->param[j] = ((ID_FB_OR  & MASKA_PARAM_ID) << SFIFT_PARAM_ID) | (((_n + 1) & MASKA_PARAM_N) << SFIFT_PARAM_N) | (((STANDARD_LOGIC_OUT + 1) & MASKA_PARAM_OUT) << SFIFT_PARAM_OUT);
          }
          else break;
        }
      }
      else if ((i_tmp -= DIV_TO_HIGHER(target_config->n_alarm + (target_config->n_alarm / OR_SIGNALS_IN) + (((target_config->n_alarm % OR_SIGNALS_IN) != 0) && ((target_config->n_alarm / OR_SIGNALS_IN) != ((target_config->n_alarm + (target_config->n_alarm / OR_SIGNALS_IN)) / OR_SIGNALS_IN))), OR_SIGNALS_IN)) < DIV_TO_HIGHER((target_config->n_alarm - (target_config->n_alarm >> 1)) + ((target_config->n_alarm - (target_config->n_alarm >> 1)) / OR_SIGNALS_IN) + ((((target_config->n_alarm - (target_config->n_alarm >> 1)) % OR_SIGNALS_IN) != 0) && (((target_config->n_alarm - (target_config->n_alarm >> 1)) / OR_SIGNALS_IN) != (((target_config->n_alarm - (target_config->n_alarm >> 1)) + ((target_config->n_alarm - (target_config->n_alarm >> 1)) / OR_SIGNALS_IN)) / OR_SIGNALS_IN))), OR_SIGNALS_IN))
      {
        for (size_t j = 0; j < OR_SIGNALS_IN; j++)
        {
          if ((target_config->n_alarm - (target_config->n_alarm >> 1)) >= (i_tmp*OR_SIGNALS_IN + j + 1))
          {
            ((__settings_for_OR*)target_sca_of_p[ID_FB_OR - _ID_FB_FIRST_VAR] + i)->param[j] = ((ID_FB_ALARM  & MASKA_PARAM_ID) << SFIFT_PARAM_ID) | (((2*(i_tmp*OR_SIGNALS_IN + j) + 1) & MASKA_PARAM_N) << SFIFT_PARAM_N) | (((ALARM_OUT_ALARM + 1) & MASKA_PARAM_OUT) << SFIFT_PARAM_OUT);
          }
          else if ((i_tmp*OR_SIGNALS_IN + j - (target_config->n_alarm - (target_config->n_alarm >> 1))) < (((target_config->n_alarm - (target_config->n_alarm >> 1)) / OR_SIGNALS_IN) + ((((target_config->n_alarm - (target_config->n_alarm >> 1)) % OR_SIGNALS_IN) != 0) && (((target_config->n_alarm - (target_config->n_alarm >> 1)) / OR_SIGNALS_IN) != (((target_config->n_alarm - (target_config->n_alarm >> 1)) + ((target_config->n_alarm - (target_config->n_alarm >> 1)) / OR_SIGNALS_IN)) / OR_SIGNALS_IN)))))
          {
            size_t _n = 4/*Reset, Mute, Block, Test*/ + 
            DIV_TO_HIGHER(2*target_config->n_group_alarm, OR_SIGNALS_IN)/*��������� ������� ��� ���*/ + 
            DIV_TO_HIGHER(target_config->n_alarm + (target_config->n_alarm / OR_SIGNALS_IN) + (((target_config->n_alarm % OR_SIGNALS_IN) != 0) && ((target_config->n_alarm / OR_SIGNALS_IN) != ((target_config->n_alarm + (target_config->n_alarm / OR_SIGNALS_IN)) / OR_SIGNALS_IN))), OR_SIGNALS_IN)/*��'������� MUTE-������ ��� ���*/ + 
            (i_tmp*OR_SIGNALS_IN + j - (target_config->n_alarm - (target_config->n_alarm >> 1)));
            ((__settings_for_OR*)target_sca_of_p[ID_FB_OR - _ID_FB_FIRST_VAR] + i)->param[j] = ((ID_FB_OR  & MASKA_PARAM_ID) << SFIFT_PARAM_ID) | (((_n + 1) & MASKA_PARAM_N) << SFIFT_PARAM_N) | (((STANDARD_LOGIC_OUT + 1) & MASKA_PARAM_OUT) << SFIFT_PARAM_OUT);
          }
          else break;
        }
      }
      else if ((i_tmp -= DIV_TO_HIGHER((target_config->n_alarm - (target_config->n_alarm >> 1)) + ((target_config->n_alarm - (target_config->n_alarm >> 1)) / OR_SIGNALS_IN) + ((((target_config->n_alarm - (target_config->n_alarm >> 1)) % OR_SIGNALS_IN) != 0) && (((target_config->n_alarm - (target_config->n_alarm >> 1)) / OR_SIGNALS_IN) != (((target_config->n_alarm - (target_config->n_alarm >> 1)) + ((target_config->n_alarm - (target_config->n_alarm >> 1)) / OR_SIGNALS_IN)) / OR_SIGNALS_IN))), OR_SIGNALS_IN)) < DIV_TO_HIGHER((target_config->n_alarm >> 1) + ((target_config->n_alarm >> 1) / OR_SIGNALS_IN) + ((((target_config->n_alarm >> 1) % OR_SIGNALS_IN) != 0) && (((target_config->n_alarm >> 1) / OR_SIGNALS_IN) != (((target_config->n_alarm >> 1) + ((target_config->n_alarm >> 1) / OR_SIGNALS_IN)) / OR_SIGNALS_IN))), OR_SIGNALS_IN))
      {
        for (size_t j = 0; j < OR_SIGNALS_IN; j++)
        {
          if ((target_config->n_alarm >> 1) >= (i_tmp*OR_SIGNALS_IN + j + 1))
          {
            ((__settings_for_OR*)target_sca_of_p[ID_FB_OR - _ID_FB_FIRST_VAR] + i)->param[j] = ((ID_FB_ALARM  & MASKA_PARAM_ID) << SFIFT_PARAM_ID) | ((((2*(i_tmp*OR_SIGNALS_IN + j) + 1) + 1) & MASKA_PARAM_N) << SFIFT_PARAM_N) | (((ALARM_OUT_ALARM + 1) & MASKA_PARAM_OUT) << SFIFT_PARAM_OUT);
          }
          else if ((i_tmp*OR_SIGNALS_IN + j - (target_config->n_alarm >> 1)) < (((target_config->n_alarm >> 1) / OR_SIGNALS_IN) + ((((target_config->n_alarm >> 1) % OR_SIGNALS_IN) != 0) && (((target_config->n_alarm >> 1) / OR_SIGNALS_IN) != (((target_config->n_alarm >> 1) + ((target_config->n_alarm >> 1) / OR_SIGNALS_IN)) / OR_SIGNALS_IN)))))
          {
            size_t _n = 4/*Reset, Mute, Block, Test*/ + 
            DIV_TO_HIGHER(2*target_config->n_group_alarm, OR_SIGNALS_IN)/*��������� ������� ��� ���*/ + 
            DIV_TO_HIGHER(target_config->n_alarm + (target_config->n_alarm / OR_SIGNALS_IN) + (((target_config->n_alarm % OR_SIGNALS_IN) != 0) && ((target_config->n_alarm / OR_SIGNALS_IN) != ((target_config->n_alarm + (target_config->n_alarm / OR_SIGNALS_IN)) / OR_SIGNALS_IN))), OR_SIGNALS_IN)/*��'������� MUTE-������ ��� ���*/ + 
            DIV_TO_HIGHER((target_config->n_alarm - (target_config->n_alarm >> 1)) + ((target_config->n_alarm - (target_config->n_alarm >> 1)) / OR_SIGNALS_IN) + ((((target_config->n_alarm - (target_config->n_alarm >> 1)) % OR_SIGNALS_IN) != 0) && (((target_config->n_alarm - (target_config->n_alarm >> 1)) / OR_SIGNALS_IN) != (((target_config->n_alarm - (target_config->n_alarm >> 1)) + ((target_config->n_alarm - (target_config->n_alarm >> 1)) / OR_SIGNALS_IN)) / OR_SIGNALS_IN))), OR_SIGNALS_IN)/*��'������� ALARM-������ ��� ��� ��� ������� �����������*/ +
            (i_tmp*OR_SIGNALS_IN + j - (target_config->n_alarm >> 1));
            ((__settings_for_OR*)target_sca_of_p[ID_FB_OR - _ID_FB_FIRST_VAR] + i)->param[j] = ((ID_FB_OR  & MASKA_PARAM_ID) << SFIFT_PARAM_ID) | (((_n + 1) & MASKA_PARAM_N) << SFIFT_PARAM_N) | (((STANDARD_LOGIC_OUT + 1) & MASKA_PARAM_OUT) << SFIFT_PARAM_OUT);
          }
          else break;
        }
      }
      else if ((i_tmp -= DIV_TO_HIGHER((target_config->n_alarm >> 1) + ((target_config->n_alarm >> 1) / OR_SIGNALS_IN) + ((((target_config->n_alarm >> 1) % OR_SIGNALS_IN) != 0) && (((target_config->n_alarm >> 1) / OR_SIGNALS_IN) != (((target_config->n_alarm >> 1) + ((target_config->n_alarm >> 1) / OR_SIGNALS_IN)) / OR_SIGNALS_IN))), OR_SIGNALS_IN)) < 1)
      {
        size_t _n = 4/*Reset, Mute, Block, Test*/ + 
        DIV_TO_HIGHER(2*target_config->n_group_alarm, OR_SIGNALS_IN)/*��������� ������� ��� ���*/ + 
        DIV_TO_HIGHER(target_config->n_alarm + (target_config->n_alarm / OR_SIGNALS_IN) + (((target_config->n_alarm % OR_SIGNALS_IN) != 0) && ((target_config->n_alarm / OR_SIGNALS_IN) != ((target_config->n_alarm + (target_config->n_alarm / OR_SIGNALS_IN)) / OR_SIGNALS_IN))), OR_SIGNALS_IN)/*��'������� MUTE-������ ��� ���*/ +
        DIV_TO_HIGHER((target_config->n_alarm - (target_config->n_alarm >> 1)) + ((target_config->n_alarm - (target_config->n_alarm >> 1)) / OR_SIGNALS_IN) + ((((target_config->n_alarm - (target_config->n_alarm >> 1)) % OR_SIGNALS_IN) != 0) && (((target_config->n_alarm - (target_config->n_alarm >> 1)) / OR_SIGNALS_IN) != (((target_config->n_alarm - (target_config->n_alarm >> 1)) + ((target_config->n_alarm - (target_config->n_alarm >> 1)) / OR_SIGNALS_IN)) / OR_SIGNALS_IN))), OR_SIGNALS_IN)/*��'������� ALARM-������ ��� ��� ��� ������� �����������*/;
        ((__settings_for_OR*)target_sca_of_p[ID_FB_OR - _ID_FB_FIRST_VAR] + i)->param[0] = ((ID_FB_OR  & MASKA_PARAM_ID) << SFIFT_PARAM_ID) | ((((_n - 1) + 1) & MASKA_PARAM_N) << SFIFT_PARAM_N) | (((STANDARD_LOGIC_OUT + 1) & MASKA_PARAM_OUT) << SFIFT_PARAM_OUT);
        
        _n += DIV_TO_HIGHER((target_config->n_alarm >> 1) + ((target_config->n_alarm >> 1) / OR_SIGNALS_IN) + ((((target_config->n_alarm >> 1) % OR_SIGNALS_IN) != 0) && (((target_config->n_alarm >> 1) / OR_SIGNALS_IN) != (((target_config->n_alarm >> 1) + ((target_config->n_alarm >> 1) / OR_SIGNALS_IN)) / OR_SIGNALS_IN))), OR_SIGNALS_IN)/*��'������� ALARM-������ ��� ��� ��� ��������������� �����������*/;
        ((__settings_for_OR*)target_sca_of_p[ID_FB_OR - _ID_FB_FIRST_VAR] + i)->param[1] = ((ID_FB_OR  & MASKA_PARAM_ID) << SFIFT_PARAM_ID) | ((((_n - 1) + 1) & MASKA_PARAM_N) << SFIFT_PARAM_N) | (((STANDARD_LOGIC_OUT + 1) & MASKA_PARAM_OUT) << SFIFT_PARAM_OUT);
      }
      else break;
    } 
    /***/
    
    /***
    ����."���"
    ***/
    /***/

    /***
    "��"
    ***/
    /***/
    
    /***
    ��-������
    ***/
    for (size_t i = 0; i < target_config->n_timer; i++)
    {
      if (target_config->n_group_alarm >= (i + 1)) 
      {
        ((__settings_for_TIMER*)target_sca_of_p[ID_FB_TIMER - _ID_FB_FIRST_VAR] + i)->param[TIMER_LOGIC_INPUT] = ((ID_FB_GROUP_ALARM & MASKA_PARAM_ID) << SFIFT_PARAM_ID) | (((i + 1) & MASKA_PARAM_N) << SFIFT_PARAM_N) | (((GROUP_ALARM_OUT_NNP + 1) & MASKA_PARAM_OUT) << SFIFT_PARAM_OUT);
      }
      else if (target_config->n_input >= (i - target_config->n_group_alarm + 4 + 1)) 
      {
        ((__settings_for_TIMER*)target_sca_of_p[ID_FB_TIMER - _ID_FB_FIRST_VAR] + i)->param[TIMER_LOGIC_INPUT] = ((ID_FB_INPUT & MASKA_PARAM_ID) << SFIFT_PARAM_ID) | (((i - target_config->n_group_alarm + 4 + 1) & MASKA_PARAM_N) << SFIFT_PARAM_N) | (((INPUT_OUT + 1) & MASKA_PARAM_OUT) << SFIFT_PARAM_OUT);
      }
      else break;
    }
    /***/
    
    /***
    D-�����
    ***/
    if (target_config->n_trigger >= (0 + 1))
    {
      ((__settings_for_TRIGGER*)target_sca_of_p[ID_FB_TRIGGER - _ID_FB_FIRST_VAR] + 0)->param[INPUT_TRIGGER_D] = ((ID_FB_TRIGGER & MASKA_PARAM_ID) << SFIFT_PARAM_ID) | (((0 + 1) & MASKA_PARAM_N) << SFIFT_PARAM_N) | (((TRIGGER_OUT_INV + 1) & MASKA_PARAM_OUT) << SFIFT_PARAM_OUT);    
      if (target_config->n_or >= (2 + 1)) ((__settings_for_TRIGGER*)target_sca_of_p[ID_FB_TRIGGER - _ID_FB_FIRST_VAR] + 0)->param[INPUT_TRIGGER_C] = ((ID_FB_OR & MASKA_PARAM_ID) << SFIFT_PARAM_ID) | (((2 + 1) & MASKA_PARAM_N) << SFIFT_PARAM_N) | (((STANDARD_LOGIC_OUT + 1) & MASKA_PARAM_OUT) << SFIFT_PARAM_OUT);    
    }
    /***/
    
    /***
    ���
    ***/
    /***/
    
    /***
    Գ�������� ����
    ***/
    {
      if (target_config->n_trigger >= (0 + 1)) target_fix_settings->param[FIX_BLOCK_BLOCK] = ((ID_FB_TRIGGER & MASKA_PARAM_ID) << SFIFT_PARAM_ID) | (((0 + 1) & MASKA_PARAM_N) << SFIFT_PARAM_N) | (((TRIGGER_OUT + 1) & MASKA_PARAM_OUT) << SFIFT_PARAM_OUT);    
      if (target_config->n_or >= (3 + 1)) target_fix_settings->param[FIX_BLOCK_TEST_INPUT] = ((ID_FB_OR & MASKA_PARAM_ID) << SFIFT_PARAM_ID) | (((3 + 1) & MASKA_PARAM_N) << SFIFT_PARAM_N) | (((STANDARD_LOGIC_OUT + 1) & MASKA_PARAM_OUT) << SFIFT_PARAM_OUT);    
      if (target_config->n_or >= 1) target_fix_settings->param[FIX_BLOCK_TEST_RESET] = ((ID_FB_OR & MASKA_PARAM_ID) << SFIFT_PARAM_ID) | ((1 & MASKA_PARAM_N) << SFIFT_PARAM_N) | (((STANDARD_LOGIC_OUT + 1) & MASKA_PARAM_OUT) << SFIFT_PARAM_OUT);

      size_t _n = 4/*Reset, Mute, Block, Test*/ + 
      DIV_TO_HIGHER(2*target_config->n_group_alarm, OR_SIGNALS_IN)/*��������� ������� ��� ���*/ + 
      DIV_TO_HIGHER(target_config->n_alarm + (target_config->n_alarm / OR_SIGNALS_IN) + (((target_config->n_alarm % OR_SIGNALS_IN) != 0) && ((target_config->n_alarm / OR_SIGNALS_IN) != ((target_config->n_alarm + (target_config->n_alarm / OR_SIGNALS_IN)) / OR_SIGNALS_IN))), OR_SIGNALS_IN)/*��'������� MUTE-������ ��� ���*/;
      if (target_config->n_or >= ((_n - 1) + 1)) target_fix_settings->param[FIX_BLOCK_MUTE] = ((ID_FB_OR  & MASKA_PARAM_ID) << SFIFT_PARAM_ID) | ((((_n - 1) + 1) & MASKA_PARAM_N) << SFIFT_PARAM_N) | (((STANDARD_LOGIC_OUT + 1) & MASKA_PARAM_OUT) << SFIFT_PARAM_OUT);

      _n += DIV_TO_HIGHER((target_config->n_alarm - (target_config->n_alarm >> 1)) + ((target_config->n_alarm - (target_config->n_alarm >> 1)) / OR_SIGNALS_IN) + ((((target_config->n_alarm - (target_config->n_alarm >> 1)) % OR_SIGNALS_IN) != 0) && (((target_config->n_alarm - (target_config->n_alarm >> 1)) / OR_SIGNALS_IN) != (((target_config->n_alarm - (target_config->n_alarm >> 1)) + ((target_config->n_alarm - (target_config->n_alarm >> 1)) / OR_SIGNALS_IN)) / OR_SIGNALS_IN))), OR_SIGNALS_IN)/*��'������� ALARM-������ ��� ��� ��� ������� �����������*/ + 
            DIV_TO_HIGHER((target_config->n_alarm >> 1) + ((target_config->n_alarm >> 1) / OR_SIGNALS_IN) + ((((target_config->n_alarm >> 1) % OR_SIGNALS_IN) != 0) && (((target_config->n_alarm >> 1) / OR_SIGNALS_IN) != (((target_config->n_alarm >> 1) + ((target_config->n_alarm >> 1) / OR_SIGNALS_IN)) / OR_SIGNALS_IN))), OR_SIGNALS_IN)/*��'������� ALARM-������ ��� ��� ��� ��������������� �����������*/ + 
            1;
      if (target_config->n_or >= ((_n - 1) + 1)) target_fix_settings->param[FIX_BLOCK_ALARM] = ((ID_FB_OR  & MASKA_PARAM_ID) << SFIFT_PARAM_ID) | ((((_n - 1) + 1) & MASKA_PARAM_N) << SFIFT_PARAM_N) | (((STANDARD_LOGIC_OUT + 1) & MASKA_PARAM_OUT) << SFIFT_PARAM_OUT);
    }
    /***/
    
    /***
    "������ ����"
    ***/
    n = 0;
    if ((target_config->n_log*LOG_SIGNALS_IN) >= (n + 0 + 1)) *((__LOG_INPUT*)target_sca_of_p[ID_FB_EVENT_LOG - _ID_FB_FIRST_VAR] + n + 0) = ((ID_FB_CONTROL_BLOCK & MASKA_PARAM_ID) << SFIFT_PARAM_ID) | ((1 & MASKA_PARAM_N) << SFIFT_PARAM_N) | (((FIX_BLOCK_DEFECT      + 1) & MASKA_PARAM_OUT) << SFIFT_PARAM_OUT);
    if ((target_config->n_log*LOG_SIGNALS_IN) >= (n + 1 + 1)) *((__LOG_INPUT*)target_sca_of_p[ID_FB_EVENT_LOG - _ID_FB_FIRST_VAR] + n + 1) = ((ID_FB_CONTROL_BLOCK & MASKA_PARAM_ID) << SFIFT_PARAM_ID) | ((1 & MASKA_PARAM_N) << SFIFT_PARAM_N) | (((FIX_BLOCK_AVAR_DEFECT + 1) & MASKA_PARAM_OUT) << SFIFT_PARAM_OUT);
    if ((target_config->n_log*LOG_SIGNALS_IN) >= (n + 2 + 1)) *((__LOG_INPUT*)target_sca_of_p[ID_FB_EVENT_LOG - _ID_FB_FIRST_VAR] + n + 2) = ((ID_FB_CONTROL_BLOCK & MASKA_PARAM_ID) << SFIFT_PARAM_ID) | ((1 & MASKA_PARAM_N) << SFIFT_PARAM_N) | (((FIX_BLOCK_VCE         + 1) & MASKA_PARAM_OUT) << SFIFT_PARAM_OUT);
    n += 3;
      
    for (size_t i = 4/*Reset, Mute, Block, Test*/; i < target_config->n_input; i++)
    {
      if ((target_config->n_log*LOG_SIGNALS_IN) >= (n + i - 4 + 1)) *((__LOG_INPUT*)target_sca_of_p[ID_FB_EVENT_LOG - _ID_FB_FIRST_VAR] + n + i - 4) = ((ID_FB_INPUT & MASKA_PARAM_ID) << SFIFT_PARAM_ID) | (((i + 1) & MASKA_PARAM_N) << SFIFT_PARAM_N) | (((INPUT_OUT + 1) & MASKA_PARAM_OUT) << SFIFT_PARAM_OUT);
      else break;
    }
    n += ((target_config->n_input > 4/*Reset, Mute, Block, Test*/) ? (target_config->n_input - 4) : 0);

    if ((target_config->n_log*LOG_SIGNALS_IN) >= (n + 0 + 1)) *((__LOG_INPUT*)target_sca_of_p[ID_FB_EVENT_LOG - _ID_FB_FIRST_VAR] + n + 0) = ((ID_FB_OUTPUT & MASKA_PARAM_ID) << SFIFT_PARAM_ID) | (((2 + 1) & MASKA_PARAM_N) << SFIFT_PARAM_N) | (((OUTPUT_LED_OUT + 1) & MASKA_PARAM_OUT) << SFIFT_PARAM_OUT);
    if ((target_config->n_log*LOG_SIGNALS_IN) >= (n + 1 + 1)) *((__LOG_INPUT*)target_sca_of_p[ID_FB_EVENT_LOG - _ID_FB_FIRST_VAR] + n + 1) = ((ID_FB_OUTPUT & MASKA_PARAM_ID) << SFIFT_PARAM_ID) | (((3 + 1) & MASKA_PARAM_N) << SFIFT_PARAM_N) | (((OUTPUT_LED_OUT + 1) & MASKA_PARAM_OUT) << SFIFT_PARAM_OUT);
    if ((target_config->n_log*LOG_SIGNALS_IN) >= (n + 2 + 1)) *((__LOG_INPUT*)target_sca_of_p[ID_FB_EVENT_LOG - _ID_FB_FIRST_VAR] + n + 2) = ((ID_FB_OUTPUT & MASKA_PARAM_ID) << SFIFT_PARAM_ID) | (((5 + 1) & MASKA_PARAM_N) << SFIFT_PARAM_N) | (((OUTPUT_LED_OUT + 1) & MASKA_PARAM_OUT) << SFIFT_PARAM_OUT);
    if ((target_config->n_log*LOG_SIGNALS_IN) >= (n + 3 + 1)) *((__LOG_INPUT*)target_sca_of_p[ID_FB_EVENT_LOG - _ID_FB_FIRST_VAR] + n + 3) = ((ID_FB_OUTPUT & MASKA_PARAM_ID) << SFIFT_PARAM_ID) | (((6 + 1) & MASKA_PARAM_N) << SFIFT_PARAM_N) | (((OUTPUT_LED_OUT + 1) & MASKA_PARAM_OUT) << SFIFT_PARAM_OUT);
    n += ((target_config->n_output >= 4/*��.�������, ��.�������, ���.�������, ���.�������*/) ? 4 : target_config->n_output);
    

    uint32_t led_to_log = target_config->n_group_alarm + n_binary_chanal;
    if (target_config->n_led < led_to_log) led_to_log = target_config->n_led;
    for (size_t i = 0; i < led_to_log; i++)
    {
      if ((target_config->n_log*LOG_SIGNALS_IN) >= (n + i + 1)) *((__LOG_INPUT*)target_sca_of_p[ID_FB_EVENT_LOG - _ID_FB_FIRST_VAR] + n + i) = ((ID_FB_LED & MASKA_PARAM_ID) << SFIFT_PARAM_ID) | (((i + 1) & MASKA_PARAM_N) << SFIFT_PARAM_N) | (((OUTPUT_LED_OUT + 1) & MASKA_PARAM_OUT) << SFIFT_PARAM_OUT);
      else break;
    }
    n += led_to_log;

    for (size_t i = 0; i < target_config->n_group_alarm; i++)
    {
      if ((target_config->n_log*LOG_SIGNALS_IN) >= (n + i*GROUP_ALARM_SIGNALS_OUT + 0 + 1)) *((__LOG_INPUT*)target_sca_of_p[ID_FB_EVENT_LOG - _ID_FB_FIRST_VAR] + n + i*GROUP_ALARM_SIGNALS_OUT + 0) = ((ID_FB_GROUP_ALARM & MASKA_PARAM_ID) << SFIFT_PARAM_ID) | (((i + 1) & MASKA_PARAM_N) << SFIFT_PARAM_N) | (((GROUP_ALARM_OUT_NNP + 1) & MASKA_PARAM_OUT) << SFIFT_PARAM_OUT);
      else break;
      if ((target_config->n_log*LOG_SIGNALS_IN) >= (n + i*GROUP_ALARM_SIGNALS_OUT + 1 + 1)) *((__LOG_INPUT*)target_sca_of_p[ID_FB_EVENT_LOG - _ID_FB_FIRST_VAR] + n + i*GROUP_ALARM_SIGNALS_OUT + 1) = ((ID_FB_GROUP_ALARM & MASKA_PARAM_ID) << SFIFT_PARAM_ID) | (((i + 1) & MASKA_PARAM_N) << SFIFT_PARAM_N) | (((GROUP_ALARM_OUT_NNM + 1) & MASKA_PARAM_OUT) << SFIFT_PARAM_OUT);
      else break;
      if ((target_config->n_log*LOG_SIGNALS_IN) >= (n + i*GROUP_ALARM_SIGNALS_OUT + 2 + 1)) *((__LOG_INPUT*)target_sca_of_p[ID_FB_EVENT_LOG - _ID_FB_FIRST_VAR] + n + i*GROUP_ALARM_SIGNALS_OUT + 2) = ((ID_FB_GROUP_ALARM & MASKA_PARAM_ID) << SFIFT_PARAM_ID) | (((i + 1) & MASKA_PARAM_N) << SFIFT_PARAM_N) | (((GROUP_ALARM_OUT_CC  + 1) & MASKA_PARAM_OUT) << SFIFT_PARAM_OUT);
      else break;
      if ((target_config->n_log*LOG_SIGNALS_IN) >= (n + i*GROUP_ALARM_SIGNALS_OUT + 3 + 1)) *((__LOG_INPUT*)target_sca_of_p[ID_FB_EVENT_LOG - _ID_FB_FIRST_VAR] + n + i*GROUP_ALARM_SIGNALS_OUT + 3) = ((ID_FB_GROUP_ALARM & MASKA_PARAM_ID) << SFIFT_PARAM_ID) | (((i + 1) & MASKA_PARAM_N) << SFIFT_PARAM_N) | (((GROUP_ALARM_OUT_CE  + 1) & MASKA_PARAM_OUT) << SFIFT_PARAM_OUT);
      else break;
      if ((target_config->n_log*LOG_SIGNALS_IN) >= (n + i*GROUP_ALARM_SIGNALS_OUT + 4 + 1)) *((__LOG_INPUT*)target_sca_of_p[ID_FB_EVENT_LOG - _ID_FB_FIRST_VAR] + n + i*GROUP_ALARM_SIGNALS_OUT + 4) = ((ID_FB_GROUP_ALARM & MASKA_PARAM_ID) << SFIFT_PARAM_ID) | (((i + 1) & MASKA_PARAM_N) << SFIFT_PARAM_N) | (((GROUP_ALARM_OUT_OC  + 1) & MASKA_PARAM_OUT) << SFIFT_PARAM_OUT);
      else break;
    }
    n += target_config->n_group_alarm*GROUP_ALARM_SIGNALS_OUT;
    /***/
    
    target_fix_settings->schematic = 2 << 8; /*������� ����� 2*/
    
    uint8_t *label_to_time_array;
    if (copying_time == 2) label_to_time_array = time_copy;
    else label_to_time_array = time;
     
    for (size_t i = 0; i < 7; i++) 
    {
      target_fix_settings->time_schematic[i] = target_fix_settings->time_setpoints[i] = *(label_to_time_array + i);
    }
    target_fix_settings->time_schematic[7] = target_fix_settings->time_setpoints[7] = DEFAULT_PARAMS_FIX_CHANGES;
  }
  else
  {
    //���� ���� ����� ��������, ������� �������� ����������� �������, ���� ����� ��������� ��������, ��� ���� ���� �� ������������
    total_error_sw_fixed(123);
  }
}
/**************************************/

/**************************************/
//�������� ����������� ��� ��, �� ��������� �� ������ ������
/**************************************/
void error_reading_with_eeprom()
{
  static unsigned int writing_configure_before;
  
  int index_language;
  if (((state_i2c_task & MASKA_FOR_BIT(STATE_CONFIG_EEPROM_GOOD_BIT)) == 0) || ((state_i2c_task & MASKA_FOR_BIT(STATE_SETTINGS_EEPROM_GOOD_BIT)) == 0)) index_language = index_language_in_array(LANGUAGE_ABSENT);
  else index_language = index_language_in_array(settings_fix_prt.language);

  if ((state_i2c_task & (
                         MASKA_FOR_BIT(STATE_CONFIG_EEPROM_EMPTY_BIT)          | 
                         MASKA_FOR_BIT(STATE_CONFIG_EEPROM_FAIL_BIT)           | 
                         MASKA_FOR_BIT(STATE_CONFIG_EEPROM_NO_FREE_MEMORY_BIT) |
                         MASKA_FOR_BIT(STATE_SETTINGS_EEPROM_EMPTY_BIT)        | 
                         MASKA_FOR_BIT(STATE_SETTINGS_EEPROM_FAIL_BIT)         | 
                         MASKA_FOR_BIT(STATE_TRG_FUNC_EEPROM_EMPTY_BIT)        | 
                         MASKA_FOR_BIT(STATE_TRG_FUNC_EEPROM_FAIL_BIT)
                        )) != 0)
  {
    //������ � watchdogs
    if ((control_word_of_watchdog & WATCHDOG_KYYBOARD) == WATCHDOG_KYYBOARD)
    {
      //������� ���� ��� ���������� Watchdog �� �����������
      GPIO_WriteBit(
                    GPIO_EXTERNAL_WATCHDOG,
                    GPIO_PIN_EXTERNAL_WATCHDOG,
                    (BitAction)(1 - GPIO_ReadOutputDataBit(GPIO_EXTERNAL_WATCHDOG, GPIO_PIN_EXTERNAL_WATCHDOG))
                   );
      control_word_of_watchdog &= (uint32_t)(~WATCHDOG_KYYBOARD);
    }
    
    unsigned int index_info, index_action, information_type;
    if((state_i2c_task & MASKA_FOR_BIT(STATE_CONFIG_EEPROM_EMPTY_BIT)) != 0)
    {
      index_info = 0;
      index_action = 2;
      information_type = 1;
    }
    else if((state_i2c_task & MASKA_FOR_BIT(STATE_CONFIG_EEPROM_FAIL_BIT)) != 0)
    {
      index_info = 1;
      index_action = 2;
      information_type = 1;
    }
    else if((state_i2c_task & MASKA_FOR_BIT(STATE_CONFIG_EEPROM_NO_FREE_MEMORY_BIT)) != 0)
    {
      index_info = 2;
      index_action = 2;
      information_type = 1;
    }
    else if((state_i2c_task & MASKA_FOR_BIT(STATE_SETTINGS_EEPROM_EMPTY_BIT)) != 0)
    {
      index_info = 3;
      index_action =  (writing_configure_before != false) ? 2 : 0;
      information_type = 2;
    }
    else if((state_i2c_task & MASKA_FOR_BIT(STATE_SETTINGS_EEPROM_FAIL_BIT)) != 0)
    {
      index_info = 4;
      index_action = 0;
      information_type = 2;
    }
    else if((state_i2c_task & MASKA_FOR_BIT(STATE_TRG_FUNC_EEPROM_EMPTY_BIT)) != 0)
    {
      index_info = 5;
      index_action = 1;
      information_type = 3;
    }
    else if((state_i2c_task & MASKA_FOR_BIT(STATE_TRG_FUNC_EEPROM_FAIL_BIT)) != 0)
    {
      index_info = 6;
      index_action = 1;
      information_type = 3;
    }

    //�������  ����� � ������� �����
    for (unsigned int i=0; i< MAX_ROW_LCD; i++)
    {
      for (unsigned int j = 0; j<MAX_COL_LCD; j++) 
      {
        if (i == 0) working_ekran[i][j] = string_info[index_language][index_info][j];
        else if (i == 1) working_ekran[i][j] = string_action[index_language][index_action][j];
        else working_ekran[i][j] = ' ';
      }
    }
  
    //�������� ������� ���� �����
    current_state_menu2.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;

    //���������� ���������� �� �����
    view_whole_ekran();
    
    //������ ���� �� ���� ��������� ������ ENTER
    while ((new_state_keyboard & (1<<BIT_KEY_ENTER)) ==0)
    {
      //������ � watchdogs
      if ((control_word_of_watchdog & WATCHDOG_KYYBOARD) == WATCHDOG_KYYBOARD)
      {
        //������� ���� ��� ���������� Watchdog �� �����������
        GPIO_WriteBit(
                      GPIO_EXTERNAL_WATCHDOG,
                      GPIO_PIN_EXTERNAL_WATCHDOG,
                      (BitAction)(1 - GPIO_ReadOutputDataBit(GPIO_EXTERNAL_WATCHDOG, GPIO_PIN_EXTERNAL_WATCHDOG))
                     );
        control_word_of_watchdog &= (uint32_t)(~WATCHDOG_KYYBOARD);
      }
    }

    new_state_keyboard = 0;
    
    if (information_type == 1)
    {
      //�������� �������� ������������
      if (index_action == 2) 
      {
        scheme2_config(&current_config);
        writing_configure_before = true;
      }
      else min_config(&current_config);
      _SET_BIT(control_i2c_taskes, TASK_START_WRITE_CONFIG_EEPROM_BIT);
    }
    else if (information_type == 2)
    {
      //�������� �������� ������������
      min_settings(&settings_fix); /*��� ����������� ����� ���� ���������� ��������� ����������� � ���������������� ������������*/
      if (index_action == 2) 
      {
        scheme2_settings(&current_config, &settings_fix, sca_of_p);
        writing_configure_before = false;
      }
      _SET_BIT(control_i2c_taskes, TASK_START_WRITE_SETTINGS_EEPROM_BIT);
    }
    else if (information_type == 3)
    {
      //�������� ������� ������� ����������
      _SET_BIT(control_i2c_taskes, TASK_START_WRITE_TRG_FUNC_EEPROM_BIT);
    }
    
    //������ ���������� ������
    while(
          (control_i2c_taskes[0]     != 0) ||
          (control_i2c_taskes[1]     != 0) ||
          (driver_i2c.state_execution > 0)
         )
    {
      //������ � watchdogs
      if ((control_word_of_watchdog & WATCHDOG_KYYBOARD) == WATCHDOG_KYYBOARD)
      {
        //������� ���� ��� ���������� Watchdog �� �����������
        GPIO_WriteBit(
                      GPIO_EXTERNAL_WATCHDOG,
                      GPIO_PIN_EXTERNAL_WATCHDOG,
                      (BitAction)(1 - GPIO_ReadOutputDataBit(GPIO_EXTERNAL_WATCHDOG, GPIO_PIN_EXTERNAL_WATCHDOG))
                     );
        control_word_of_watchdog &= (uint32_t)(~WATCHDOG_KYYBOARD);
      }

      main_routines_for_i2c();
      changing_diagnostyka_state();//ϳ����������� ����� ���������� �������� ����� ��� ���������� ���������� ����
      //������� �� ����� ����������� ������� �� ���������, �� �� �������� ����� ������ ���
      if (_CHECK_SET_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT) != 0)
      {
        //����� ���������������� ������ ������������ ����� ������ � EEPROM ��� �������� I2C
        _CLEAR_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT);
      }
    }

    if (information_type == 1)
    {
      //��������� ������� ������������
      comparison_writing &= (uint16_t)(~MASKA_FOR_BIT(COMPARISON_WRITING_CONFIG_BIT));/*����������, � �� ���������*/
      _SET_BIT(control_i2c_taskes, TASK_START_READ_CONFIG_EEPROM_BIT);
    }
    else if (information_type == 2)
    {
      //��������� ������� ������������
      comparison_writing &= (uint16_t)(~MASKA_FOR_BIT(COMPARISON_WRITING_SETTINGS_BIT));/*����������, � �� ���������*/
      _SET_BIT(control_i2c_taskes, TASK_START_READ_SETTINGS_EEPROM_BIT);
    }
    else if (information_type == 3)
    {
      //��������� ������� ������� ����������
      comparison_writing &= (uint16_t)(~MASKA_FOR_BIT(COMPARISON_WRITING_TRG_FUNC_BIT));/*����������, � �� ���������*/
      _SET_BIT(control_i2c_taskes, TASK_START_READ_TRG_FUNC_EEPROM_BIT);
    }

    //������ ���������� �������
    while(
          (control_i2c_taskes[0]     != 0) ||
          (control_i2c_taskes[1]     != 0) ||
          (driver_i2c.state_execution > 0)
         )
    {
      //������ � watchdogs
      if ((control_word_of_watchdog & WATCHDOG_KYYBOARD) == WATCHDOG_KYYBOARD)
      {
        //������� ���� ��� ���������� Watchdog �� �����������
        GPIO_WriteBit(
                      GPIO_EXTERNAL_WATCHDOG,
                      GPIO_PIN_EXTERNAL_WATCHDOG,
                      (BitAction)(1 - GPIO_ReadOutputDataBit(GPIO_EXTERNAL_WATCHDOG, GPIO_PIN_EXTERNAL_WATCHDOG))
                     );
        control_word_of_watchdog &= (uint32_t)(~WATCHDOG_KYYBOARD);
      }
      
      main_routines_for_i2c();
      changing_diagnostyka_state();//ϳ����������� ����� ���������� �������� ����� ��� ���������� ���������� ����
      //������� �� ����� ����������� ������� �� ���������, �� �� �������� ����� ������ ���
      if (_CHECK_SET_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT) != 0)
      {
        //����� ���������������� ������ ������������ ����� ������ � EEPROM ��� �������� I2C
        _CLEAR_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT);
      }
    }
  }
}  
/**************************************/

/**************************************/
//�������� �������� (� ��� ����������� ������������� �� ������ ���������) DataFlash
/**************************************/
void start_checking_dataflash(void)
{
  //������ ������� ��������
  uint32_t page_size_256, page_size_256_total = 1;
  
  for (unsigned int i = 0; i < NUMBER_DATAFLASH_CHIP; i++)
  {
    number_chip_dataflash_exchange = INDEX_DATAFLASH_1 + i;
    
    page_size_256 = 1;

    _SET_STATE(control_spi_df_tasks[number_chip_dataflash_exchange], TASK_READ_SR_DF_BIT);
    while(
          (control_spi_df_tasks[number_chip_dataflash_exchange] != 0) ||
          (state_execution_spi_df[number_chip_dataflash_exchange] != TRANSACTION_EXECUTING_NONE)
         )
    {
      main_routines_for_spi_df(number_chip_dataflash_exchange);

      //������ � watchdogs
      if ((control_word_of_watchdog & WATCHDOG_KYYBOARD) == WATCHDOG_KYYBOARD)
      {
        //������� ���� ��� ���������� Watchdog �� �����������
        GPIO_WriteBit(
                      GPIO_EXTERNAL_WATCHDOG,
                      GPIO_PIN_EXTERNAL_WATCHDOG,
                      (BitAction)(1 - GPIO_ReadOutputDataBit(GPIO_EXTERNAL_WATCHDOG, GPIO_PIN_EXTERNAL_WATCHDOG))
                     );
        control_word_of_watchdog &= (uint32_t)(~WATCHDOG_KYYBOARD);
      }
    }
    
    page_size_256 &= status_register_df[number_chip_dataflash_exchange] & (1<< 0); 
    if (page_size_256 == 0)
    {
      //����� ������ ������� �� ������ ��������� � ������� ������� 256 ����
      
      _SET_STATE(control_spi_df_tasks[number_chip_dataflash_exchange], TASK_START_MAKE_PAGE_SIZE_256_BIT);
      while(
            (control_spi_df_tasks[number_chip_dataflash_exchange] != 0) ||
            (state_execution_spi_df[number_chip_dataflash_exchange] != TRANSACTION_EXECUTING_NONE)
           )
      {
        main_routines_for_spi_df(number_chip_dataflash_exchange);
 
        //������ � watchdogs
        if ((control_word_of_watchdog & WATCHDOG_KYYBOARD) == WATCHDOG_KYYBOARD)
        {
          //������� ���� ��� ���������� Watchdog �� �����������
          GPIO_WriteBit(
                        GPIO_EXTERNAL_WATCHDOG,
                        GPIO_PIN_EXTERNAL_WATCHDOG,
                        (BitAction)(1 - GPIO_ReadOutputDataBit(GPIO_EXTERNAL_WATCHDOG, GPIO_PIN_EXTERNAL_WATCHDOG))
                       );
          control_word_of_watchdog &= (uint32_t)(~WATCHDOG_KYYBOARD);
        }
      }
    }

    page_size_256_total &=  page_size_256;
  }
  
  if (page_size_256_total == 0)
  {
    int index_language = index_language_in_array(settings_fix_prt.language);
    
    //������ � watchdogs
    if ((control_word_of_watchdog & WATCHDOG_KYYBOARD) == WATCHDOG_KYYBOARD)
    {
      //������� ���� ��� ���������� Watchdog �� �����������
      GPIO_WriteBit(
                    GPIO_EXTERNAL_WATCHDOG,
                    GPIO_PIN_EXTERNAL_WATCHDOG,
                    (BitAction)(1 - GPIO_ReadOutputDataBit(GPIO_EXTERNAL_WATCHDOG, GPIO_PIN_EXTERNAL_WATCHDOG))
                   );
      control_word_of_watchdog &= (uint32_t)(~WATCHDOG_KYYBOARD);
    }

    //�������  ����� � ������� �����
    for (size_t i= 0; i < MAX_ROW_LCD; i++)
    {
      for (size_t j = 0; j < MAX_COL_LCD; j++) working_ekran[i][j] = name_string_restart[index_language][i][j];
    }
  
    //�������� ������� ���� �����
    current_state_menu2.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;

    //���������� ���������� �� �����
    view_whole_ekran();
    
    //������, ���� ������� ���� �������������
    while(1)
    {
      //������ � watchdogs
      if ((control_word_of_watchdog & WATCHDOG_KYYBOARD) == WATCHDOG_KYYBOARD)
      {
        //������� ���� ��� ���������� Watchdog �� �����������
        GPIO_WriteBit(
                      GPIO_EXTERNAL_WATCHDOG,
                      GPIO_PIN_EXTERNAL_WATCHDOG,
                      (BitAction)(1 - GPIO_ReadOutputDataBit(GPIO_EXTERNAL_WATCHDOG, GPIO_PIN_EXTERNAL_WATCHDOG))
                     );
        control_word_of_watchdog &= (uint32_t)(~WATCHDOG_KYYBOARD);
      }
    }
  }

  number_chip_dataflash_exchange = INDEX_DATAFLASH_1;
}
/**************************************/

/**************************************/
//��������� ����� 2 ������� 4 �� ��������� ���������� ����� 1 ��
/**************************************/
void start_tim4_canal2_for_interrupt_1mc(void)
{
  TIM_OCInitTypeDef  TIM_OCInitStructure;

  /* Output Compare Timing Mode ������������: �����:2 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Timing;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Disable;
  TIM_OCInitStructure.TIM_Pulse = ((uint16_t)TIM4->CNT) + TIM4_CCR2_VAL;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OC2Init(TIM4, &TIM_OCInitStructure);
  
  TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Disable);

  /* ���������� ����������� �� ������ 2 ������� 4*/
  TIM_ITConfig(TIM4, TIM_IT_CC2, ENABLE);

//  //���������� ����� ��� ������� �����������
//  TIM4->CCR2 = ((uint16_t)TIM4->CNT) + TIM4_CCR2_VAL;
}
/**************************************/

/**************************************/
//��������� ����� 3 ������� 4 �� ��������� ���������� �� ����� 10 ���
/**************************************/
void start_tim4_canal3_for_interrupt_10mkc(void)
{
  TIM_OCInitTypeDef  TIM_OCInitStructure;
  
  if (number_bits_rs_485_waiting < 10) calculate_namber_bit_waiting_for_rs_485();

  /* Output Compare Timing Mode ������������: �����:2 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Timing;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Disable;
  unsigned int delta = TIM4_CCR3_VAL*number_bits_rs_485_waiting;
  TIM_OCInitStructure.TIM_Pulse = ((uint16_t)TIM4->CNT) + delta;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OC3Init(TIM4, &TIM_OCInitStructure);
  
  TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Disable);

  /* ���������� ����������� �� ������ 3 ������� 4*/
  TIM_ITConfig(TIM4, TIM_IT_CC3, ENABLE);
}
/**************************************/

/**************************************/
//������� ����������� �� "��������" ������� �� ��� ���������� �������
/**************************************/
#ifdef TEST_MODE
void empty_settings()
{
  int index_language;
  if (((state_i2c_task & MASKA_FOR_BIT(STATE_CONFIG_EEPROM_GOOD_BIT)) == 0) || ((state_i2c_task & MASKA_FOR_BIT(STATE_SETTINGS_EEPROM_GOOD_BIT)) == 0)) index_language = index_language_in_array(LANGUAGE_ABSENT);
  else index_language = index_language_in_array(settings_fix_prt.language);

  //�������  ����� � ������� �����
  for (unsigned int i=0; i< MAX_ROW_LCD; i++)
  {
    for (unsigned int j = 0; j<MAX_COL_LCD; j++) 
    {
      if (i == 0) working_ekran[i][j] = string_test_info[index_language][0][j];
      else if (i == 1) working_ekran[i][j] = name_string_ask[index_language][j];
      else working_ekran[i][j] = ' ';
    }
  }
  
  //�������� ������� ���� �����
  current_state_menu2.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;

  //���������� ���������� �� �����
  view_whole_ekran();
    
  //������ ���� �� ���� ��������� ������ ENTER
  while ((new_state_keyboard & ((1<<BIT_KEY_ENTER) | (1<<BIT_KEY_ESC))) == 0)
  {
    //������ � watchdogs
    if ((control_word_of_watchdog & WATCHDOG_KYYBOARD) == WATCHDOG_KYYBOARD)
    {
      //������� ���� ��� ���������� Watchdog �� �����������
      GPIO_WriteBit(
                    GPIO_EXTERNAL_WATCHDOG,
                    GPIO_PIN_EXTERNAL_WATCHDOG,
                    (BitAction)(1 - GPIO_ReadOutputDataBit(GPIO_EXTERNAL_WATCHDOG, GPIO_PIN_EXTERNAL_WATCHDOG))
                   );
      control_word_of_watchdog &= (uint32_t)(~WATCHDOG_KYYBOARD);
    }
  }
  
  if ((new_state_keyboard & (1<<BIT_KEY_ENTER)) != 0)
  {
    //��������� ��� ���'���
    for (__id_fb index_1 = _ID_FB_FIRST_VAR; index_1 < _ID_FB_LAST_VAR; index_1++)
    {
      free(sca_of_p_edit[index_1 - _ID_FB_FIRST_VAR]);
      sca_of_p_edit[index_1 - _ID_FB_FIRST_VAR] = NULL;
      
      free(sca_of_p[index_1 - _ID_FB_FIRST_VAR]);
      sca_of_p[index_1 - _ID_FB_FIRST_VAR] = NULL;
      
      free(spca_of_p_prt[index_1 - _ID_FB_FIRST_VAR]);
      spca_of_p_prt[index_1 - _ID_FB_FIRST_VAR] = NULL;
    }
    
    __CONFIG current_config_tmp;
    min_config(&current_config_tmp);
    current_config_prt.device_id = current_config.device_id = current_config_edit.device_id = current_config_tmp.device_id;
    
    __result_dym_mem_select          result = allocate_dynamic_memory_for_settings(MAKE_DYN_MEM, true, spca_of_p_prt , NULL         , &current_config_prt , &current_config_tmp, NULL               );
    if (result == DYN_MEM_SELECT_OK) result = allocate_dynamic_memory_for_settings(MAKE_DYN_MEM, false, sca_of_p     , spca_of_p_prt, &current_config     , &current_config_tmp, &current_config_prt);
    if (result == DYN_MEM_SELECT_OK) result = allocate_dynamic_memory_for_settings(MAKE_DYN_MEM, false, sca_of_p_edit, sca_of_p     , &current_config_edit, &current_config_tmp, &current_config    );
    for (size_t t = 0; t < (7 + 1); t++) current_config_edit.time_config[t] = current_config.time_config[t] = current_config_prt.time_config[t] = current_config_tmp.time_config[t];

    if (result == DYN_MEM_SELECT_OK) 
    {
      min_settings(&settings_fix); /*��� ����������� ����� ���� ���������� ��������� ����������� � ���������������� ������������*/
        
      _SET_BIT(control_i2c_taskes, TASK_START_WRITE_CONFIG_EEPROM_BIT);
      _SET_BIT(control_i2c_taskes, TASK_START_WRITE_SETTINGS_EEPROM_BIT);
      _SET_BIT(control_i2c_taskes, TASK_START_WRITE_TRG_FUNC_EEPROM_BIT);
        
      //������ ���������� ������
      while(
            (control_i2c_taskes[0]     != 0) ||
            (control_i2c_taskes[1]     != 0) ||
            (driver_i2c.state_execution > 0)
           )
      {
        //������ � watchdogs
        if ((control_word_of_watchdog & WATCHDOG_KYYBOARD) == WATCHDOG_KYYBOARD)
        {
          //������� ���� ��� ���������� Watchdog �� �����������
          GPIO_WriteBit(
                        GPIO_EXTERNAL_WATCHDOG,
                        GPIO_PIN_EXTERNAL_WATCHDOG,
                        (BitAction)(1 - GPIO_ReadOutputDataBit(GPIO_EXTERNAL_WATCHDOG, GPIO_PIN_EXTERNAL_WATCHDOG))
                       );
          control_word_of_watchdog &= (uint32_t)(~WATCHDOG_KYYBOARD);
        }

        main_routines_for_i2c();
        changing_diagnostyka_state();//ϳ����������� ����� ���������� �������� ����� ��� ���������� ���������� ����
        //������� �� ����� ����������� ������� �� ���������, �� �� �������� ����� ������ ���
        if (_CHECK_SET_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT) != 0)
        {
          //����� ���������������� ������ ������������ ����� ������ � EEPROM ��� �������� I2C
          _CLEAR_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT);
        }
      }
      //��������� ������� ������������-������������-�������� ����������
      comparison_writing &= (uint16_t)(~(
                                         MASKA_FOR_BIT(COMPARISON_WRITING_CONFIG_BIT  ) |
                                         MASKA_FOR_BIT(COMPARISON_WRITING_SETTINGS_BIT) |
                                         MASKA_FOR_BIT(COMPARISON_WRITING_TRG_FUNC_BIT)
                                        )   
                                      );/*����������, � �� ���������*/
      _SET_BIT(control_i2c_taskes, TASK_START_READ_CONFIG_EEPROM_BIT);
      _SET_BIT(control_i2c_taskes, TASK_START_READ_SETTINGS_EEPROM_BIT);
      _SET_BIT(control_i2c_taskes, TASK_START_READ_TRG_FUNC_EEPROM_BIT);

      //������ ���������� �������
      while(
            (control_i2c_taskes[0]     != 0) ||
            (control_i2c_taskes[1]     != 0) ||
            (driver_i2c.state_execution > 0)
           )
      {
        //������ � watchdogs
        if ((control_word_of_watchdog & WATCHDOG_KYYBOARD) == WATCHDOG_KYYBOARD)
        {
          //������� ���� ��� ���������� Watchdog �� �����������
          GPIO_WriteBit(
                        GPIO_EXTERNAL_WATCHDOG,
                        GPIO_PIN_EXTERNAL_WATCHDOG,
                        (BitAction)(1 - GPIO_ReadOutputDataBit(GPIO_EXTERNAL_WATCHDOG, GPIO_PIN_EXTERNAL_WATCHDOG))
                       );
          control_word_of_watchdog &= (uint32_t)(~WATCHDOG_KYYBOARD);
        }
      
        main_routines_for_i2c();
        changing_diagnostyka_state();//ϳ����������� ����� ���������� �������� ����� ��� ���������� ���������� ����
        //������� �� ����� ����������� ������� �� ���������, �� �� �������� ����� ������ ���
        if (_CHECK_SET_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT) != 0)
        {
          //����� ���������������� ������ ������������ ����� ������ � EEPROM ��� �������� I2C
          _CLEAR_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT);
        }
      }
    }
    else
    {
      state_i2c_task |= MASKA_FOR_BIT(STATE_CONFIG_EEPROM_NO_FREE_MEMORY_BIT);

      //���������� ����������� � ���� ����������
      if (set_diagnostyka != NULL) _SET_BIT(set_diagnostyka, ERROR_NO_FREE_DYNAMIC_MEMORY_BIT);
      
      //��������� ��� ���'���
      for (__id_fb index_1 = _ID_FB_FIRST_VAR; index_1 < _ID_FB_LAST_VAR; index_1++)
      {
        free(sca_of_p_edit[index_1 - _ID_FB_FIRST_VAR]);
        sca_of_p_edit[index_1 - _ID_FB_FIRST_VAR] = NULL;
        
        free(sca_of_p[index_1 - _ID_FB_FIRST_VAR]);
        sca_of_p[index_1 - _ID_FB_FIRST_VAR] = NULL;
        
        free(spca_of_p_prt[index_1 - _ID_FB_FIRST_VAR]);
        spca_of_p_prt[index_1 - _ID_FB_FIRST_VAR] = NULL;
      }
    }
  }
  
  new_state_keyboard = 0;
}  
#endif
/**************************************/


/**************************************/
//
/**************************************/
/**************************************/
