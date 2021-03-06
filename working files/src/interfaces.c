#include "header.h"

/***********************************************************************************/
//�������� ����������� ���������� USB � ����������� ����� ������
/***********************************************************************************/
void Usb_routines(void)
{
  if (USB_OTG_dev.dev.device_status != USB_OTG_CONFIGURED)
  {
    data_usb_transmiting = false;
    return;
  }
  
  if (data_usb_transmiting == true)
  {
    if(USB_Tx_State != 1)
    {
      int usb_transmiting_count_tmp = usb_transmiting_count;
      usb_transmiting_count = 0;
      data_usb_transmiting = false;
      
      APP_FOPS.pIf_DataTx(usb_transmiting, usb_transmiting_count_tmp);
    }
  }
  else if (count_out != 0)
  {
    //Գ����� �������� ������� TIM4 � ���� ����� ���������� 10 ���
    uint16_t current_count_tim4_USB = ((uint16_t)TIM4->CNT);
    uint16_t delta_USB = 0;//�� ������������ 0, ��� ���� ������ ���� ������ ����� �� ������������ ������, ���� � ��� ��������, �� ���� ���� 0
    
    //���������� �� ����������� ������� ��� ���� - � ���� ���, �� ������� �������� ������� TIM4
    if (count_out_previous != count_out)
    {
      previous_count_tim4_USB = current_count_tim4_USB;
      count_out_previous = count_out;
    }
    else
    {
      //ϳ��� ��������� ���� ���� �� ���������� �� ������� ���� - ���� ������ ���������� �� ���� ��������
      
      //��������� ������ ���� �� ����������� ��� ���� �� USB
      if (current_count_tim4_USB >= previous_count_tim4_USB) delta_USB = current_count_tim4_USB - previous_count_tim4_USB;
      else delta_USB = (0x10000 - previous_count_tim4_USB) + current_count_tim4_USB; //0x10000 - �� ������ ����� �������, �� �� �������� ���� ���������� �������� [0; 65535]
    }
    
    if (delta_USB > 188) /*1 - ������� 10 ���, �� TIM4 ��������� � ����������� 10 ���. 188 �������� ��� 1880 ���. 1880 �� �� ��� 1,5 ������� �� �������� 9600 � ������ 1-start + 8-data + pare + 2-stop*/
    {
      //������� ������� �������� ����������
      usb_received_count = count_out;
      //����������� �������� USB - �� ����� �������� ������ � �������
      count_out = 0;
      count_out_previous = 0; 
      
      //���������� �� �� ������ ����� ������� ����� �������������
      if (
          (usb_received_count > 0) && /*���������� �� ����� ���� � ������ ������������*/
          (usb_received_count <= BUFFER_USB)
         )   
      {
        //������� �������� ���� � ������� �����
        for (int i = 0; i < usb_received_count; i++) usb_received[i] = buffer_out[i];
        //���������� ����� �� ��������� MODBUS-RTU ��������� � USB
//        modbus_rountines(USB_RECUEST);
        inputPacketParserUSB();
      }
      else
      {
        //��� ����� �� ������� ���������� - ���� ������ �������� ��������� ����� �����
        usb_received_count = 0;
      }
    }
  }
}  
/***********************************************************************************/

/***********************************************************************************/
//���������/������������� USART ��� RS-485
/***********************************************************************************/
void USART_RS485_Configure(void)
{
  USART_InitTypeDef USART_InitStructure;

  unsigned int baud_RS485;
  switch (settings_fix_prt.baud_RS485)
  {
  case 0:
    {
      baud_RS485 = 9600;
      break;
    }
  case 1:
    {
      baud_RS485 = 14400;
      break;
    }
  case 2:
    {
      baud_RS485 = 19200;
      break;
    }
  case 3:
    {
      baud_RS485 = 28800;
      break;
    }
  case 4:
    {
      baud_RS485 = 38400;
      break;
    }
  case 5:
    {
      baud_RS485 = 57600;
      break;
    }
  default:
    {
      baud_RS485 = 115200;
      break;
    }
  }
  
  unsigned int pare_RS485;
  switch (settings_fix_prt.pare_bit_RS485)
  {
  case 0:
    {
      pare_RS485 = USART_Parity_No;
      break;
    }
  case 1:
    {
      pare_RS485 = USART_Parity_Odd;
      break;
    }
  default:
    {
      pare_RS485 = USART_Parity_Even;
      break;
    }
  }

  //���������� ��������� �� ������
  GPIO_485DE->BSRRH = GPIO_PIN_485DE;

  //����������� ��������� ����������
  USART_ITConfig(USART_RS485, USART_IT_TC, DISABLE);
  USART_ITConfig(USART_RS485, USART_IT_IDLE, DISABLE);
  USART_ITConfig(USART_RS485, USART_IT_LBD, DISABLE);
  USART_ITConfig(USART_RS485, USART_IT_PE, DISABLE);
  USART_ITConfig(USART_RS485, USART_IT_ERR, DISABLE);

  //��������� ���� DMA_Tx ���� �� ���������
  if ((DMA_StreamRS485_Tx->CR & (uint32_t)DMA_SxCR_EN) !=0) DMA_StreamRS485_Tx->CR &= ~(uint32_t)DMA_SxCR_EN;
  DMA_StreamRS485_Tx->NDTR = 0;
  //����������� �������� ����� DMA, ���� �� ����������
  if ((USART_RS485->CR3 & USART_DMAReq_Tx) != 0) USART_RS485->CR3 &= (uint16_t)((~(uint32_t)USART_DMAReq_Tx) & 0xffff);
  // ������� ���������, �� �������� ��� ���������� �������� ����� ��� DMA1 �� ������ TX 
  DMA_ClearFlag(DMA_StreamRS485_Tx, DMA_FLAG_TCRS485_Tx | DMA_FLAG_HTRS485_Tx | DMA_FLAG_TEIRS485_Tx | DMA_FLAG_DMEIRS485_Tx | DMA_FLAG_FEIRS485_Tx);

  //��������� ���� DMA_Rx ���� �� ���������
  if ((DMA_StreamRS485_Rx->CR & (uint32_t)DMA_SxCR_EN) !=0) DMA_StreamRS485_Rx->CR &= ~(uint32_t)DMA_SxCR_EN;
  DMA_StreamRS485_Rx->NDTR = BUFFER_RS485;
  //����������� �������� ����� DMA, ���� �� ����������
  if ((USART_RS485->CR3 & USART_DMAReq_Rx) != 0) USART_RS485->CR3 &= (uint16_t)((~(uint32_t)USART_DMAReq_Rx) & 0xffff);
  // ������� ���������, �� �������� ��� ���������� �������� ����� ��� DMA1 �� ������ RX 
  DMA_ClearFlag(DMA_StreamRS485_Rx, DMA_FLAG_TCRS485_Rx | DMA_FLAG_HTRS485_Rx | DMA_FLAG_TEIRS485_Rx | DMA_FLAG_DMEIRS485_Rx | DMA_FLAG_FEIRS485_Rx);
  
  //������� ������� ��������� ����
  RxBuffer_RS485_count = 0;

  //���������� USART
  USART_RS485->CR1 &= (uint16_t)(~USART_CR1_UE);

  //���������� ���������
  USART_InitStructure.USART_BaudRate = baud_RS485;
  if (pare_RS485 == USART_Parity_No) USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  else USART_InitStructure.USART_WordLength = USART_WordLength_9b;
  if (settings_fix_prt.number_stop_bit_RS485 == 0) USART_InitStructure.USART_StopBits = USART_StopBits_1;
  else USART_InitStructure.USART_StopBits = USART_StopBits_2; 
  USART_InitStructure.USART_Parity = pare_RS485;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  
  //�������� ������������ USART_RS485
  USART_Init(USART_RS485, &USART_InitStructure);

  //���������� �������� ����� DMA
  USART_RS485->CR3 |= USART_DMAReq_Rx;
  USART_RS485->CR3 |= USART_DMAReq_Tx;

  //���������� ����������� �� USART ��� RS-485 ��� �������� �������
  USART_ITConfig(USART_RS485, USART_IT_IDLE, ENABLE);
  USART_ITConfig(USART_RS485, USART_IT_LBD, ENABLE);
  USART_ITConfig(USART_RS485, USART_IT_PE, ENABLE);
  USART_ITConfig(USART_RS485, USART_IT_ERR, ENABLE);

  //���������� USART_RS485
  USART_RS485->CR1 |= USART_CR1_UE;
}
/***********************************************************************************/

/***********************************************************************************/
//³��������� ����������� ������ RS-485
/***********************************************************************************/
void restart_monitoring_RS485(void)
{
  /***
  ���� ������ RS-485 (������� �����������)
  ***/
  test_answer_RS485 |= (1 << 4);
  /***/
    
  //������� �� ������ �������
  USART_RS485->SR;
  (unsigned short int)(USART_RS485->DR & (uint16_t)0x01FF);
      
  if ((DMA_StreamRS485_Rx->CR & (uint32_t)DMA_SxCR_EN) !=0) DMA_StreamRS485_Rx->CR &= ~(uint32_t)DMA_SxCR_EN;

  // ������� ���������, �� �������� ��� ���������� �������� ����� ��� DMA1 �� ������ RS-485_RX 
  DMA_ClearFlag(DMA_StreamRS485_Rx, DMA_FLAG_TCRS485_Rx | DMA_FLAG_HTRS485_Rx | DMA_FLAG_TEIRS485_Rx | DMA_FLAG_DMEIRS485_Rx | DMA_FLAG_FEIRS485_Rx);

  DMA_StreamRS485_Rx->NDTR = BUFFER_RS485;
  RxBuffer_RS485_count_previous = 0;
  RxBuffer_RS485_count = 0;
  //��������� ���������� �������
  DMA_StreamRS485_Rx->CR |= (uint32_t)DMA_SxCR_EN;
}
/***********************************************************************************/

/***********************************************************************************/
//������ ������� ��� �������� ����� ����� ��������� RS-485
/***********************************************************************************/
void start_transmint_data_via_RS_485(unsigned int count)
{
  //����������, �� ����� ���������� ����
  unsigned int current_time_tim4 = TIM4->CNT;
  unsigned int delta_time;

  //���������� ���, �������� ����� ��������������� �������
  if (
      (current_time_tim4 > time_last_receive_byte) ||
      (
       (current_time_tim4 == time_last_receive_byte) &&
       (mark_current_tick_RS_485 != 0)  
      ) 
     )   
    delta_time = current_time_tim4 - time_last_receive_byte;
  else 
    delta_time = current_time_tim4 + 0xffff - time_last_receive_byte;

  if (max_reaction_time_rs_485 < delta_time) max_reaction_time_rs_485 = delta_time;
  
  if (delta_time < MAX_TIMEOUT_PACKET)
  {
    //����� ��������� �� �����

    /***
    ���� ������ RS-485 (������� �� �������� �����)
    ***/
    test_answer_RS485 |= (1 << 1);
    /***/
    
    //���������� ��������� �� ��������
    GPIO_485DE->BSRRL = GPIO_PIN_485DE;

    //������� ��, �� ��������, �� ��������� ���� ���������
    USART_ClearFlag(USART_RS485, USART_FLAG_TC);

    //���������� ��������� �����������, ����  ���� �������� �� ����� �� DMA1 ����� ����� DMA1_ChannelRS485_TX
    DMA_StreamRS485_Tx->CR |= DMA_IT_TC;

    //��������� ���� DMA ���� �� ���������
    if ((DMA_StreamRS485_Tx->CR & (uint32_t)DMA_SxCR_EN) !=0) DMA_StreamRS485_Tx->CR &= ~(uint32_t)DMA_SxCR_EN;
    DMA_StreamRS485_Tx->NDTR = count;
    //���������� �������� ����� DMA
    if ((USART_RS485->CR3 & USART_DMAReq_Tx) == 0) USART_RS485->CR3 |= USART_DMAReq_Tx;

    //������� ���������, �� �������� ��� ���������� �������� ����� ��� DMA1 �� ������ RS-485_TX
    DMA_ClearFlag(DMA_StreamRS485_Tx, DMA_FLAG_TCRS485_Tx | DMA_FLAG_HTRS485_Tx | DMA_FLAG_TEIRS485_Tx | DMA_FLAG_DMEIRS485_Tx | DMA_FLAG_FEIRS485_Tx);
    //��������� ��������
    DMA_StreamRS485_Tx->CR |= (uint32_t)DMA_SxCR_EN;
  }
  else
  {
    /***
    ������� �������� (������� ���������� ����� ������ ���)
    ***/
    reason_of_restart_RS485 |= (1 << 0);
    /***/
    
    //�� ����� ��������� �� �����, �� ������� ��������� ������ ��� ��� ��������� ��� ���������� ������ - ����� ���������� �� ������ ������������ ���� RS-485
    restart_monitoring_RS485();
  }
}
/***********************************************************************************/

/***********************************************************************************/
//
/***********************************************************************************/
/***********************************************************************************/
