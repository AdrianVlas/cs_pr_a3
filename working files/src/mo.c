#include "header.h"

/***********************************************************************************
Прийом даних через інтерфейс CANAL1_MO
***********************************************************************************/
void start_receive_data_via_CANAL1_MO(void)
{
  //Попередньо скидаємо повідомплення про помилки, які потім будемо виставляти
  clear_diagnostyka[0] |= WORD_0_MASKA_ERRORS_FROM_CANAL_1_2;
  clear_diagnostyka[1] |= WORD_1_MASKA_ERRORS_FROM_CANAL_1_2;
  clear_diagnostyka[2] |= WORD_2_MASKA_ERRORS_FROM_CANAL_1_2;
  
  //Зупиняэмо канал приймання
  if ((DMA_StreamCANAL1_MO_Rx->CR & (uint32_t)DMA_SxCR_EN) !=0) DMA_StreamCANAL1_MO_Rx->CR &= ~(uint32_t)DMA_SxCR_EN;  
  
  int32_t size_packet = BUFFER_CANAL1_MO - (uint16_t)(DMA_StreamCANAL1_MO_Rx->NDTR);
  if(size_packet != 0)
  {
    uint32_t error_status = CANAL1_MO->SR &  (USART_FLAG_ORE | USART_FLAG_NE | USART_FLAG_FE | USART_FLAG_PE);
    
    //Прийняті дані з комунікаційної плати по каналу 1
    if (
        (error_status == 0) &&
        (size_packet >= 3) &&
        (Canal1_MO_Received[0] == START_BYTE_MO) && 
        (Canal1_MO_Received[size_packet - 1] == STOP_BYTE_MO)  
       )   
    {
      //Перевіряємо адресу
      if (
          (Canal1_MO_Received[1] == BROADCAST_ADDRESS_MO) ||
          (Canal1_MO_Received[1] == my_address_mo)
         )   
      {
        //Перевіряємо контрольну суму
        uint8_t sum = 0;
        for (int32_t i = 0; i < (size_packet - 3); i++) sum += Canal1_MO_Received[1 + i];
        if (sum == Canal1_MO_Received[size_packet - 2])
        { 
          IEC_board_uncall = 0;
          IEC_board_address = Canal1_MO_Received[2];
          
          uint32_t index = 4;
          switch (Canal1_MO_Received[3])
          {
          case SENDING_GOOSE_INFO:
            {
              //Черга з КП для обміну між КП і БАВ
              uint32_t IEC_queue_mo = 0;
              uint8_t *point = (uint8_t*)(&IEC_queue_mo);
              for (uint32_t i = 0; ((i < sizeof(IEC_queue_mo)) && (index < BUFFER_CANAL1_MO)); i++) 
              {
                *(point++) = Canal1_MO_Received[index++];
              }
              
              if (_GET_OUTPUT_STATE(IEC_queue_mo, IEC_STATE_QUEUE_MO_ASK_BASIC_SETTINGS)) 
                _SET_STATE(queue_mo_irq, STATE_QUEUE_MO_ASK_BASIC_SETTINGS);
              else 
                _CLEAR_STATE(queue_mo_irq, STATE_QUEUE_MO_ASK_BASIC_SETTINGS);

              if (_GET_OUTPUT_STATE(IEC_queue_mo, IEC_STATE_QUEUE_MO_ASK_MAKING_MEMORY_BLOCK)) 
                _SET_STATE(queue_mo_irq, STATE_QUEUE_MO_ASK_MAKING_MEMORY_BLOCK);
              else 
                _CLEAR_STATE(queue_mo_irq, STATE_QUEUE_MO_ASK_MAKING_MEMORY_BLOCK);

              if (_GET_OUTPUT_STATE(IEC_queue_mo, IEC_STATE_QUEUE_MO_ASK_FULL_DESCRIPTION)) 
                _SET_STATE(queue_mo_irq, STATE_QUEUE_MO_ASK_FULL_DESCRIPTION);
              else 
                _CLEAR_STATE(queue_mo_irq, STATE_QUEUE_MO_ASK_FULL_DESCRIPTION);

              if (_GET_OUTPUT_STATE(IEC_queue_mo, IEC_STATE_QUEUE_MO_ASK_SENDING_SETTING_NETWORK_LAYER)) 
                _SET_STATE(queue_mo_irq, STATE_QUEUE_MO_ASK_SENDING_SETTING_NETWORK_LAYER);
              else 
                _CLEAR_STATE(queue_mo_irq, STATE_QUEUE_MO_ASK_SENDING_SETTING_NETWORK_LAYER);


              if (_GET_OUTPUT_STATE(IEC_queue_mo, IEC_STATE_QUEUE_MO_TRANSACTION_PROGRESS)) 
                _SET_STATE(queue_mo_irq, STATE_QUEUE_MO_TRANSACTION_PROGRESS_IN_IEC);
              else 
                _CLEAR_STATE(queue_mo_irq, STATE_QUEUE_MO_TRANSACTION_PROGRESS_IN_IEC);
              
              //Синхронізація часу
              uint32_t goose_time = 0;
              point = (uint8_t*)&goose_time;
              index += sizeof(time);
              for (uint32_t i = 0; ((i < sizeof(uint32_t)) && (index < BUFFER_CANAL1_MO)); i++) 
              {
                *(point++) = Canal1_MO_Received[index++];
              }
              if (goose_time != 0)
              {
                //Деякі позиції системного часу/дати треба записати
                uint8_t *label_to_time_array;
                if (copying_time == 2) label_to_time_array = time_copy;
                else label_to_time_array = time;
                int32_t index_tmp = index - sizeof(time) - sizeof(uint32_t);
                if (index_tmp > 0)
                {
                  for (uint32_t i = 0; i < sizeof(time); i++) 
                  {
                    if ((goose_time & (1 << i)) != 0) IEC_time_edit[i] = Canal1_MO_Received[index_tmp];
                    else IEC_time_edit[i] = *(label_to_time_array + i);
                  
                    index_tmp++;
                  }
                  IEC_save_time = true;
                }
                else total_error_sw_fixed(24);
              }
              
              /***
              Оперативні дані
              ***/
              while (
                     (Canal1_MO_Received[index] == START_LABEL_NEW_TM) &&
                     (index < BUFFER_CANAL1_MO)  
                    )   
              {
                index++;
                size_t index_ln = Canal1_MO_Received[index++];
                if (array_control_struct[index_ln].off_on == true)
                {
                  uint8_t *p_buffer_rx = array_control_struct[index_ln].p_buffer_rx;
                  uint8_t *p_buffer_ctrl_rx = array_control_struct[index_ln].p_buffer_ctrl_rx;
                  size_t size_block_rx = array_control_struct[index_ln].size_block_rx;
                  
                  size_t size_struct = array_control_struct[index_ln].size_struct;
                  
                  size_t shift = Canal1_MO_Received[index + 0] | (Canal1_MO_Received[index + 1] << 8);
                  size_t size = Canal1_MO_Received[index + 2] | (Canal1_MO_Received[index + 3] << 8);
                  index += 4;

                  if ((index + size) < BUFFER_CANAL1_MO)
                  {
                    for (size_t i = 0; i < size; i++)
                    {
                      size_t shift_tmp = shift + i;
                      uint32_t n = shift_tmp / (2*size_block_rx);
                      shift_tmp -= (n*2*size_block_rx);
                      
                      if (shift_tmp < size_block_rx)
                      {
                        p_buffer_rx[n*size_struct + shift_tmp] = Canal1_MO_Received[index++];
                      }
                      else
                      {
                        shift_tmp -= size_block_rx;
                        if (shift_tmp < size_block_rx)
                        {
                          p_buffer_ctrl_rx[n*size_struct + shift_tmp] = Canal1_MO_Received[index++];
                        }
                        else total_error_sw_fixed(27);
                      }
                    }
                  }
                  else total_error_sw_fixed(28);
                }
                else total_error_sw_fixed(29);
              }

              if(
                 ((index + 1 +  sizeof(confirm_diagnostyka_mo)) < BUFFER_CANAL1_MO) &&
                 (Canal1_MO_Received[index++] == START_LABEL_CONF_DIAGN)
                )   
              {
                //Діагностика обміну по Каналу1
                point = (uint8_t*)(&confirm_diagnostyka_mo);
                for (uint32_t i = 0; i < sizeof(confirm_diagnostyka_mo); i++) 
                {
                  *(point++) = Canal1_MO_Received[index++];
                }
                if (_GET_OUTPUT_STATE(confirm_diagnostyka_mo, ERROR_RECEIVING_CANAL_1)      ) _SET_BIT(set_diagnostyka, ERROR_IEC_RECEIVING_CANAL_1);
                if (_GET_OUTPUT_STATE(confirm_diagnostyka_mo, ERROR_RECEIVED_PACKET_CANAL_1)) _SET_BIT(set_diagnostyka, ERROR_IEC_RECEIVED_PACKET_CANAL_1);
                if (_GET_OUTPUT_STATE(confirm_diagnostyka_mo, ERROR_REQUEST_CANAL_1)        ) _SET_BIT(set_diagnostyka, ERROR_IEC_REQUEST_CANAL_1);
                if (_GET_OUTPUT_STATE(confirm_diagnostyka_mo, ERROR_NO_ANSWER_CANAL_1)      ) _SET_BIT(set_diagnostyka, ERROR_IEC_NO_ANSWER_CANAL_1);

                if (_GET_OUTPUT_STATE(confirm_diagnostyka_mo, ERROR_RECEIVING_CANAL_2)      ) _SET_BIT(set_diagnostyka, ERROR_IEC_RECEIVING_CANAL_2);
                if (_GET_OUTPUT_STATE(confirm_diagnostyka_mo, ERROR_RECEIVED_PACKET_CANAL_2)) _SET_BIT(set_diagnostyka, ERROR_IEC_RECEIVED_PACKET_CANAL_2);
                if (_GET_OUTPUT_STATE(confirm_diagnostyka_mo, ERROR_REQUEST_CANAL_2)        ) _SET_BIT(set_diagnostyka, ERROR_IEC_REQUEST_CANAL_2);
              }
              
              
              /***/
              break;
            }
          default:
            {
              _SET_BIT(set_diagnostyka, ERROR_CPU_ANSWER_CANAL_1);
              
              break;
            }
          }
        }
        else _SET_BIT(set_diagnostyka, ERROR_CPU_RECEIVED_PACKET_CANAL_1);
      }
    }
    else _SET_BIT(set_diagnostyka, ERROR_CPU_RECEIVING_CANAL_1);
  }
  else
  {
    //Не прийняті дані з комунікаційної плати по каналу 1
    if (IEC_board_uncall == 0) _SET_BIT(set_diagnostyka, ERROR_CPU_NO_ANSWER_CANAL_1);
//    else IEC_board_uncall--;
  }
      
  //Скидуємо всі можливі помилки
  CANAL1_MO->SR;
  (unsigned short int)(CANAL1_MO->DR & (uint16_t)0x01FF);
  CANAL1_MO->SR = (uint16_t)(~(uint32_t)USART_FLAG_LBD);
      
  // Очищаємо прапореці, що сигналізує про завершення передачі даних для DMA1 по каналу RS-485_RX 
  DMA_ClearFlag(DMA_StreamCANAL1_MO_Rx, DMA_FLAG_TCCANAL1_MO_Rx | DMA_FLAG_HTCANAL1_MO_Rx | DMA_FLAG_TEICANAL1_MO_Rx | DMA_FLAG_DMEICANAL1_MO_Rx | DMA_FLAG_FEICANAL1_MO_Rx);

  DMA_StreamCANAL1_MO_Rx->NDTR = BUFFER_CANAL1_MO;
  //Запускаємо очікування прийому
  DMA_StreamCANAL1_MO_Rx->CR |= (uint32_t)DMA_SxCR_EN;
}
/***********************************************************************************/

/***********************************************************************************
Подача команди нва передачу даних через інтерфейс CANAL1_MO
***********************************************************************************/
void start_transmint_data_via_CANAL1_MO(void)
{
  uint8_t sum = 0;
  uint32_t index = 0;
  
         Canal1_MO_Transmit[index++] = START_BYTE_MO;
  sum += Canal1_MO_Transmit[index++] = BROADCAST_ADDRESS_MO;
  sum += Canal1_MO_Transmit[index++] = my_address_mo;
  
  sum += Canal1_MO_Transmit[index++] = SENDIND_TM_INFO;
    
  uint8_t *label_to_time_array;
  if (copying_time == 2) 
  {
    sum += Canal1_MO_Transmit[index++] = thousandths_time_copy;
    label_to_time_array = time_copy;
  }
  else 
  {
    sum += Canal1_MO_Transmit[index++] = thousandths_time;
    label_to_time_array = time;
  }
  for(uint32_t i = 0; ((i < sizeof(time)) && (index < BUFFER_CANAL1_MO)); i++) 
  {
    sum += Canal1_MO_Transmit[index++] = *(label_to_time_array + i);
  }
  
  //Оперативні дані
  for (size_t index_ln = 0; index_ln < NUMBER_ALL_BLOCKS; index_ln++)
  {
    if (array_control_struct[index_ln].off_on == true)
    {
      uint32_t n = array_control_struct[index_ln].n;
      size_t size_struct = array_control_struct[index_ln].size_struct;
  
      uint8_t *p_buffer_tx = array_control_struct[index_ln].p_buffer_tx;
      size_t size_block_tx = array_control_struct[index_ln].size_block_tx;
      uint8_t *p_add_data_tx = array_control_struct[index_ln].p_add_data_tx;
      size_t size_add_data_tx = array_control_struct[index_ln].size_add_data_tx;
  
      size_t size_full_block_tx = n*(size_block_tx + size_add_data_tx);
      if (size_full_block_tx != 0)
      {
        if ((index + 1 + 1 + 2 + 2 + size_full_block_tx) < BUFFER_CANAL1_MO)
        {
          sum += Canal1_MO_Transmit[index++] = START_LABEL_NEW_TM;
    
          sum += Canal1_MO_Transmit[index++] = index_ln;
    
          sum += Canal1_MO_Transmit[index++] = 0;
          sum += Canal1_MO_Transmit[index++] = 0;
          
          sum += Canal1_MO_Transmit[index++] = (size_full_block_tx  & 0xff);
          sum += Canal1_MO_Transmit[index++] = ((size_full_block_tx >> 8) & 0xff);

          for (size_t n_tmp = 0; n_tmp < n; n_tmp++)
          {
            for (uint32_t i = 0; i < size_block_tx; i++) 
            {
              sum += Canal1_MO_Transmit[index++] = p_buffer_tx[i];
            }
            //Переводимо вказівник на наступний елемент
            p_buffer_tx += size_struct;
          
            if (size_add_data_tx != 0)
            {
              for (uint32_t i = 0; i < size_add_data_tx; i++) 
              {
                sum += Canal1_MO_Transmit[index++] = p_add_data_tx[i];
              }

              //Переводимо вказівник на наступний елемент
              p_add_data_tx +=size_struct;
            }
          }
        }
        else break;
      }
    }
    else break;
  }
    
  if ((index + 1 + sizeof(confirm_diagnostyka_mo)) < BUFFER_CANAL1_MO)
  {
    sum += Canal1_MO_Transmit[index++] = START_LABEL_CONF_DIAGN;
    uint8_t *point = (uint8_t*)(&confirm_diagnostyka_mo);
    for (uint32_t i = 0; i < sizeof(confirm_diagnostyka_mo); i++) 
    {
      sum += Canal1_MO_Transmit[index++] = *(point++);
    }
    confirm_diagnostyka_mo = 0; //Очищаємо підтверджену діагностику каналу обміну епо Куналу 1
  }

  if ((index + 2) >= BUFFER_CANAL1_MO) total_error_sw_fixed(30);
  
  Canal1_MO_Transmit[index++] = sum;
  Canal1_MO_Transmit[index++] = STOP_BYTE_MO;
  
  //Скидаємо біт, що символізує, що опстанній байт переданий
  USART_ClearFlag(CANAL1_MO, USART_FLAG_TC);

  //Зупиняємо потік DMA якщо він запущений
  if ((DMA_StreamCANAL1_MO_Tx->CR & (uint32_t)DMA_SxCR_EN) !=0) DMA_StreamCANAL1_MO_Tx->CR &= ~(uint32_t)DMA_SxCR_EN;
  DMA_StreamCANAL1_MO_Tx->NDTR = index;
  //Дозволяємо передачу через DMA
  if ((CANAL1_MO->CR3 & USART_DMAReq_Tx) == 0) CANAL1_MO->CR3 |= USART_DMAReq_Tx;

  //Очищаємо прапореці, що сигналізує про завершення передачі даних для DMA1 по потоку CANAL1_MO_TX
  DMA_ClearFlag(DMA_StreamCANAL1_MO_Tx, DMA_FLAG_TCCANAL1_MO_Tx | DMA_FLAG_HTCANAL1_MO_Tx | DMA_FLAG_TEICANAL1_MO_Tx | DMA_FLAG_DMEICANAL1_MO_Tx | DMA_FLAG_FEICANAL1_MO_Tx);
  //Запускаємо передачу
  DMA_StreamCANAL1_MO_Tx->CR |= (uint32_t)DMA_SxCR_EN;
}
/***********************************************************************************/

/***********************************************************************************
Модуль прийому-передачі даних через інтерфейс CANAL2_MO
***********************************************************************************/
void CANAL2_MO_routine()
{
  queue_mo &= (uint32_t)(~QUEUQ_MO_IRQ);
  queue_mo |= queue_mo_irq;
  
  typedef enum _CANAL2_MO_states
  {
    CANAL2_MO_FREE = 0,
    CANAL2_MO_SENDING,
    CANAL2_MO_RECEIVING,
    CANAL2_MO_RECEIVED,
    CANAL2_MO_ERROR,
    CANAL2_MO_BREAK_LAST_ACTION
  } __CANAL2_MO_states;
  
  static __CANAL2_MO_states CANAL2_MO_state;
  static uint32_t tick;
  static uint32_t rx_ndtr;
  static uint32_t packet_number;
  static size_t current_bln;
  static uint32_t number_bln;
  
  uint8_t sum;
  uint32_t index_w;
  uint32_t repeat = false;
  do
  {
    sum = 0;
    index_w = 0;
    
    if (CANAL2_MO_state == CANAL2_MO_BREAK_LAST_ACTION)
    {
      queue_mo &= (uint32_t)(~QUEUQ_MO_PROGRESS);
      
      if ( (config_settings_modified & MASKA_FOR_BIT(BIT_NET_LOCKS)) != 0)
      {
        config_settings_modified = 0;
      }

             Canal2_MO_Transmit[index_w++] = START_BYTE_MO;
      sum += Canal2_MO_Transmit[index_w++] = IEC_board_address;
      sum += Canal2_MO_Transmit[index_w++] = my_address_mo;
  
      sum += Canal2_MO_Transmit[index_w++] = BREAK_LAST_ACTION;

      _SET_STATE(queue_mo, STATE_QUEUE_MO_BREAK_LAST_ACTION_IN_IEC);
    }  
    else if (CANAL2_MO_state == CANAL2_MO_FREE)
    {
      //На даний момент не іде передавання даних по Каналу 2
      if (
          (repeat == true) ||
          (!_GET_OUTPUT_STATE(queue_mo, STATE_QUEUE_MO_TRANSACTION_PROGRESS_IN_IEC))
         )   
      {
        if (
            (repeat == true) ||
            (Canal1 == true)
           )   
        {
          if (
              (
               (repeat == false) &&
               (  
                (_GET_OUTPUT_STATE(queue_mo, STATE_QUEUE_MO_ASK_BASIC_SETTINGS)) ||
                (_GET_OUTPUT_STATE(queue_mo, STATE_QUEUE_MO_SEND_BASIC_SETTINGS))
               )   
              )
              ||  
              (
               (repeat == true) &&
               (_GET_OUTPUT_STATE(queue_mo, STATE_QUEUE_MO_TRANSMITING_BASIC_SETTINGS))
              ) 
             )   
          {
                   Canal2_MO_Transmit[index_w++] = START_BYTE_MO;
            sum += Canal2_MO_Transmit[index_w++] = IEC_board_address;
            sum += Canal2_MO_Transmit[index_w++] = my_address_mo;
  
            sum += Canal2_MO_Transmit[index_w++] = SENDING_BASIC_SETTINGS;
          
            sum += Canal2_MO_Transmit[index_w++] = VERSIA_PZ;
            sum += Canal2_MO_Transmit[index_w++] = MODYFIKACIA_VERSII_PZ;
            sum += Canal2_MO_Transmit[index_w++] = ZBIRKA_VERSII_PZ;
            sum += Canal2_MO_Transmit[index_w++] = ZBIRKA_PIDVERSII_PZ;

            sum += Canal2_MO_Transmit[index_w++] = serial_number_dev & 0xff;
            sum += Canal2_MO_Transmit[index_w++] = (serial_number_dev >> 8) & 0xff;
          
            sum += Canal2_MO_Transmit[index_w++] = settings_fix_prt.IPv4[0] & 0xff;
            sum += Canal2_MO_Transmit[index_w++] = settings_fix_prt.IPv4[1] & 0xff;
            sum += Canal2_MO_Transmit[index_w++] = settings_fix_prt.IPv4[2] & 0xff;
            sum += Canal2_MO_Transmit[index_w++] = settings_fix_prt.IPv4[3] & 0xff;
        
            sum += Canal2_MO_Transmit[index_w++] = settings_fix_prt.mask;

            sum += Canal2_MO_Transmit[index_w++] = settings_fix_prt.gateway[0] & 0xff;
            sum += Canal2_MO_Transmit[index_w++] = settings_fix_prt.gateway[1] & 0xff;
            sum += Canal2_MO_Transmit[index_w++] = settings_fix_prt.gateway[2] & 0xff;
            sum += Canal2_MO_Transmit[index_w++] = settings_fix_prt.gateway[3] & 0xff;
            
            unsigned int period = TIM2_CCR1_VAL*2000/*Prescaler*//60/*вхдна частота таймера у МГц*/; /*результат у мкс*/
            sum += Canal2_MO_Transmit[index_w++] = period        & 0xff;
            sum += Canal2_MO_Transmit[index_w++] = (period >> 8) & 0xff;
            
        
            _CLEAR_STATE(queue_mo, STATE_QUEUE_MO_SEND_BASIC_SETTINGS);
            _SET_STATE(queue_mo, STATE_QUEUE_MO_TRANSMITING_BASIC_SETTINGS);
          } 
          else if (
                   (
                    (repeat == false) &&
                    (_GET_OUTPUT_STATE(queue_mo, STATE_QUEUE_MO_ASK_MAKING_MEMORY_BLOCK))
                   )
                   ||  
                   (
                    (repeat == true) &&
                    (_GET_OUTPUT_STATE(queue_mo, STATE_QUEUE_MO_TRANSMITING_MAKING_MEMORY_BLOCK))
                   )
                  )   
          {
            size_t current_bln_tmp;
            if (_GET_OUTPUT_STATE(queue_mo, STATE_QUEUE_MO_TRANSMITING_MAKING_MEMORY_BLOCK)) 
            {
              packet_number++; /*номерування пакетів продовжуємо*/
              current_bln_tmp = current_bln + 1;
            }
            else 
            {
              number_bln = 0;
              while ((array_control_struct[number_bln].off_on == true) && (number_bln < NUMBER_ALL_BLOCKS)) number_bln++;

              packet_number = 0; /*номерування пакетів починаємо з початку*/
              current_bln_tmp = 0;
            }

            Canal2_MO_Transmit[index_w++] = START_BYTE_MO;
            sum += Canal2_MO_Transmit[index_w++] = IEC_board_address;
            sum += Canal2_MO_Transmit[index_w++] = my_address_mo;
  
            sum += Canal2_MO_Transmit[index_w++] = MAKING_NEW_BLOCKS;
            sum += Canal2_MO_Transmit[index_w++] = number_bln & 0xff; /*LSB: загальна кількість блоків, які треба створити*/
            sum += Canal2_MO_Transmit[index_w++] = (number_bln >> 8) & 0xff; /*MSB: загальна кількість блоків, які треба створити*/
        
          
            sum += Canal2_MO_Transmit[index_w++] = packet_number & 0xff; /*LSB: номер пакету*/
            sum += Canal2_MO_Transmit[index_w++] = (packet_number >> 8) & 0xff; /*MSB: номер пакету*/
          
            while (
                   (current_bln_tmp < number_bln) &&
                   ((index_w + 1 + 1 + 1 + 1 + 2 + 2 + 2 + 4 + SIZE_LN_MAME) < BUFFER_CANAL2_MO)  
                  )
            {
              sum += Canal2_MO_Transmit[index_w++] = START_LABEL_NEW_BLOCK; /*признак початку інформації по створюваному блоку*/
              sum += Canal2_MO_Transmit[index_w++] = current_bln_tmp; /*ID створюваного блоку*/
            
              sum += Canal2_MO_Transmit[index_w++] = array_control_struct[current_bln_tmp].id; /*Тип логічного вузла для немодульного приладу*/
              sum += Canal2_MO_Transmit[index_w++] = array_control_struct[current_bln_tmp].n; /*Кількість елементів даного типу*/

              size_t size_block_tx_full = array_control_struct[current_bln_tmp].size_block_tx + array_control_struct[current_bln_tmp].size_add_data_tx;
              sum += Canal2_MO_Transmit[index_w++] = size_block_tx_full        & 0xff; /*LSB: Розмір буферу на прийом оперативних даних у КП з ПЛ*/
              sum += Canal2_MO_Transmit[index_w++] = (size_block_tx_full >> 8) & 0xff; /*MSB: Розмір буферу на прийом оперативних даних у КП з ПЛ*/

              size_t size_block_rx = array_control_struct[current_bln_tmp].size_block_rx;
              sum += Canal2_MO_Transmit[index_w++] = size_block_rx        & 0xff; /*LSB: Розмір буферу на передачу оперативних даних з КП у ПЛ*/
              sum += Canal2_MO_Transmit[index_w++] = (size_block_rx >> 8) & 0xff; /*MSB: Розмір буферу на передачу оперативних даних з КП у ПЛ*/

              sum += Canal2_MO_Transmit[index_w++] = size_block_rx        & 0xff; /*LSB: Розмір буферу на передачу признаків активації оперативних даних з КП у ПЛ*/
              sum += Canal2_MO_Transmit[index_w++] = (size_block_rx >> 8) & 0xff; /*MSB: Розмір буферу на передачу признаків активації оперативних даних з КП у ПЛ*/
  
              size_t size_description = 0;
              sum += Canal2_MO_Transmit[index_w++] = size_description         & 0xff; /*LSW->LSB: Розмір буферу описової частини оперативних даних*/
              sum += Canal2_MO_Transmit[index_w++] = (size_description >>  8) & 0xff; /*LSW->MSB: Розмір буферу описової частини оперативних даних*/
              sum += Canal2_MO_Transmit[index_w++] = (size_description >> 16) & 0xff; /*MSW->LSB: Розмір буферу описової частини оперативних даних*/
              sum += Canal2_MO_Transmit[index_w++] = (size_description >> 24) & 0xff; /*MSW->MSB: Розмір буферу описової частини оперативних даних*/
              
              unsigned int null_founded = false;
              for (size_t i = 0; i < SIZE_LN_MAME; i++)
              {
                if (null_founded == false)
                {
                  uint8_t symbol = *(array_control_struct[current_bln_tmp].p_ln_name + i);
                  sum += Canal2_MO_Transmit[index_w++] = symbol;
                  if (symbol == '\0') null_founded = true;
                }
                else sum += Canal2_MO_Transmit[index_w++] = '\0';
              }
            
              current_bln_tmp++;
            }

            sum += Canal2_MO_Transmit[index_w++] = (current_bln_tmp != number_bln); /*Буде/Небуде продовження передавання взагальному*/
        
            _SET_STATE(queue_mo, STATE_QUEUE_MO_TRANSMITING_MAKING_MEMORY_BLOCK);
          }
          else if (
                   (
                    (repeat == false) &&
                    (_GET_OUTPUT_STATE(queue_mo, STATE_QUEUE_MO_ASK_SENDING_SETTING_NETWORK_LAYER))
                   )
                   ||  
                   (
                    (repeat == true) &&
                    (_GET_OUTPUT_STATE(queue_mo, STATE_QUEUE_MO_RECEIVING_SETTING_NETWORK_LAYER))
                   )
                  )   
          {
            
            if (
                (config_settings_modified == 0) &&
                (_CHECK_SET_BIT(control_i2c_taskes, TASK_START_WRITE_CONFIG_EEPROM_BIT  ) == 0) &&
                (_CHECK_SET_BIT(control_i2c_taskes, TASK_WRITING_CONFIG_EEPROM_BIT      ) == 0) &&
                (_CHECK_SET_BIT(control_i2c_taskes, TASK_START_READ_CONFIG_EEPROM_BIT   ) == 0) &&
                (_CHECK_SET_BIT(control_i2c_taskes, TASK_READING_CONFIG_EEPROM_BIT      ) == 0) &&
                (_CHECK_SET_BIT(control_i2c_taskes, TASK_START_WRITE_SETTINGS_EEPROM_BIT) == 0) &&
                (_CHECK_SET_BIT(control_i2c_taskes, TASK_WRITING_SETTINGS_EEPROM_BIT    ) == 0) &&
                (_CHECK_SET_BIT(control_i2c_taskes, TASK_START_READ_SETTINGS_EEPROM_BIT ) == 0) &&
                (_CHECK_SET_BIT(control_i2c_taskes, TASK_READING_SETTINGS_EEPROM_BIT    ) == 0)
               )
            {
              //Фіксуємо, що система Net захопила "монополію" на зміну конфігурації і налаштувань
              config_settings_modified = MASKA_FOR_BIT(BIT_NET_LOCKS);
            
                     Canal2_MO_Transmit[index_w++] = START_BYTE_MO;
              sum += Canal2_MO_Transmit[index_w++] = IEC_board_address;
              sum += Canal2_MO_Transmit[index_w++] = my_address_mo;
  
              sum += Canal2_MO_Transmit[index_w++] = REQUEST_SETTINGS_NETWORK_LAYER;
        
              _SET_STATE(queue_mo, STATE_QUEUE_MO_RECEIVING_SETTING_NETWORK_LAYER);
            }
          }
        }
      }
      else
      {
        uint32_t tick_tmp = TIM4->CNT;
        uint32_t delta;
        if (tick_tmp >= tick) delta = tick_tmp - tick;
        else delta = (0x10000 - tick) + tick_tmp; //0x10000 - це повний період таймера, бо ми настроїли його тактуватиу інтервалі [0; 65535]
      
        if (delta > 500 /*500x10мкс = 5000мкс = 5мс*/) CANAL2_MO_state = CANAL2_MO_BREAK_LAST_ACTION;
      }
    }
    else if (CANAL2_MO_state == CANAL2_MO_SENDING)
    {
      if (DMA_StreamCANAL2_MO_Tx->NDTR == 0) 
      {
        CANAL2_MO_state = CANAL2_MO_RECEIVING;
        tick = TIM4->CNT;
        rx_ndtr = DMA_StreamCANAL2_MO_Rx->NDTR;
      }
    }
    else if (CANAL2_MO_state == CANAL2_MO_RECEIVING)
    {
      uint32_t rx_ndtr_tmp = DMA_StreamCANAL2_MO_Rx->NDTR;
      if (rx_ndtr_tmp != rx_ndtr)
      {
        rx_ndtr = rx_ndtr_tmp;
      }
      else
      {
        uint32_t tick_tmp = TIM4->CNT;
        uint32_t delta;
        if (tick_tmp >= tick) delta = tick_tmp - tick;
        else delta = (0x10000 - tick) + tick_tmp; //0x10000 - це повний період таймера, бо ми настроїли його тактуватиу інтервалі [0; 65535]
      
        if (rx_ndtr == BUFFER_CANAL2_MO)
        {
          //Не прийнято жодного байту
          if (delta > 500 /*500x10мкс = 5000мкс = 5мс*/) CANAL2_MO_state = CANAL2_MO_ERROR;
        }
        else
        {
          //Є прийняті байти
          if (delta > 1 /*10мкс = 10мкс*/) CANAL2_MO_state = CANAL2_MO_RECEIVED;
        }
      
        //Робимо перевірку пакету
        if (
            (CANAL2_MO_state == CANAL2_MO_RECEIVED) ||
            (CANAL2_MO_state == CANAL2_MO_ERROR)  
           )
        {
          //Попередньо скидаємо повідомплення про помилки прийому Каналу 2, які потім будемо виставляти
          clear_diagnostyka[0] |= WORD_0_MASKA_RECEIVING_ERRORS_CANAL_2;
          clear_diagnostyka[1] |= WORD_1_MASKA_RECEIVING_ERRORS_CANAL_2;
          clear_diagnostyka[2] |= WORD_2_MASKA_RECEIVING_ERRORS_CANAL_2;

          int32_t size_packet = BUFFER_CANAL2_MO - rx_ndtr;
          if(size_packet != 0)
          {
            uint32_t error_status = CANAL2_MO->SR &  (USART_FLAG_ORE | USART_FLAG_NE | USART_FLAG_FE | USART_FLAG_PE);
    
            //Прийняті дані з комунікаційної плати по каналу 1
            if (
                (error_status == 0) &&
                (size_packet >= 3) &&
                (Canal2_MO_Received[0] == START_BYTE_MO) && 
                (Canal2_MO_Received[size_packet - 1] == STOP_BYTE_MO)  
              )   
            {
              if ((Canal2_MO_Received[1] == my_address_mo))
              {
                //Перевіряємо контрольну суму
                sum = 0;
                for (int32_t i = 0; i < (size_packet - 3); i++) sum += Canal2_MO_Received[1 + i];
                if (sum == Canal2_MO_Received[size_packet - 2])
                { 
                  if (
                      !(
                        ((_GET_OUTPUT_STATE(queue_mo, STATE_QUEUE_MO_BREAK_LAST_ACTION_IN_IEC       )) && (Canal2_MO_Received[3] == CONFIRM_BREAKING_LAST_ACTION  )       ) ||
                        ((_GET_OUTPUT_STATE(queue_mo, STATE_QUEUE_MO_TRANSMITING_MAKING_MEMORY_BLOCK)) && (Canal2_MO_Received[3] == ANSWER_FOR_MAKING_NEW_BLOCKS  )       ) ||
                        ((_GET_OUTPUT_STATE(queue_mo, STATE_QUEUE_MO_TRANSMITING_BASIC_SETTINGS     )) && (Canal2_MO_Received[3] == ANY_CONFIRMATION              )       ) ||
                        ((_GET_OUTPUT_STATE(queue_mo, STATE_QUEUE_MO_RECEIVING_SETTING_NETWORK_LAYER)) && (
                                                                                                           (Canal2_MO_Received[3] == SENDING_SETTINGS_NETWORK_LAYER) ||
                                                                                                           (Canal2_MO_Received[3] == ANY_CONFIRMATION              )
                                                                                                          )                                                               )
                       )   
                     )
                  {
                    _SET_BIT(set_diagnostyka, ERROR_CPU_ANSWER_CANAL_2);
                    CANAL2_MO_state = CANAL2_MO_ERROR;
                  }
                }
                else 
                {
                  _SET_BIT(set_diagnostyka, ERROR_CPU_RECEIVED_PACKET_CANAL_2);
                }
              }
            }
            else 
            {
              _SET_BIT(set_diagnostyka, ERROR_CPU_RECEIVING_CANAL_2);
              CANAL2_MO_state = CANAL2_MO_ERROR;
            }
          }
          else 
          {
            _SET_BIT(set_diagnostyka, ERROR_CPU_NO_ANSWER_CANAL_2);
            CANAL2_MO_state = CANAL2_MO_ERROR;
          }
        }
      }
    }
  
    repeat = false;

    if (
        (CANAL2_MO_state == CANAL2_MO_RECEIVED) ||
        (CANAL2_MO_state == CANAL2_MO_ERROR)  
       )   
    {
      if (CANAL2_MO_state == CANAL2_MO_RECEIVED)
      {
        sum = 0;
  
               Canal2_MO_Transmit[index_w++] = START_BYTE_MO;
        sum += Canal2_MO_Transmit[index_w++] = IEC_board_address;
        sum += Canal2_MO_Transmit[index_w++] = my_address_mo;
  
        if (_GET_OUTPUT_STATE(queue_mo, STATE_QUEUE_MO_BREAK_LAST_ACTION_IN_IEC)) 
        {
          index_w = 0;
          _CLEAR_STATE(queue_mo, STATE_QUEUE_MO_BREAK_LAST_ACTION_IN_IEC);

          CANAL2_MO_state = CANAL2_MO_FREE;
          Canal2 = true;
        }
        else if (_GET_OUTPUT_STATE(queue_mo, STATE_QUEUE_MO_TRANSMITING_BASIC_SETTINGS)) 
        {
          index_w = 0;
          _CLEAR_STATE(queue_mo, STATE_QUEUE_MO_TRANSMITING_BASIC_SETTINGS);
        
          if (Canal2_MO_Received[4] == true)
          {
            CANAL2_MO_state = CANAL2_MO_FREE;
            Canal2 = true;
          }
          else
          {
            CANAL2_MO_state = CANAL2_MO_ERROR;
          }
        }
        else if (_GET_OUTPUT_STATE(queue_mo, STATE_QUEUE_MO_TRANSMITING_MAKING_MEMORY_BLOCK)) 
        {
          index_w = 0;
          state_array_control_state = Canal2_MO_Received[4] | (Canal2_MO_Received[5] << 8);
          current_bln = (Canal2_MO_Received[6] | (Canal2_MO_Received[7] << 8));
        
          if ((state_array_control_state & MASKA_FOR_BIT(ACS_MADE)) != 0)
          {
            if (
                ((state_array_control_state & MASKA_FOR_BIT(ACS_ALL_BLOCKS_CREATED)) != 0) &&
                ((current_bln + 1) == number_bln)
               )
            {
              _CLEAR_STATE(queue_mo, STATE_QUEUE_MO_TRANSMITING_MAKING_MEMORY_BLOCK);
              CANAL2_MO_state = CANAL2_MO_FREE;
              Canal2 = true;
            }
            else if ((state_array_control_state & MASKA_FOR_BIT(ACS_BLOCKS_CREATED_OF_LAST_REQUEST)) != 0)
            {
              CANAL2_MO_state = CANAL2_MO_FREE;
              repeat = true;
            }
            else
            {
              CANAL2_MO_state = CANAL2_MO_ERROR;
            }
          }
          else
          {
            _CLEAR_STATE(queue_mo, STATE_QUEUE_MO_TRANSMITING_MAKING_MEMORY_BLOCK);
            CANAL2_MO_state = CANAL2_MO_ERROR;
          }
        }
        else if (_GET_OUTPUT_STATE(queue_mo, STATE_QUEUE_MO_RECEIVING_SETTING_NETWORK_LAYER)) 
        {
          if (Canal2_MO_Received[3] == SENDING_SETTINGS_NETWORK_LAYER)
          {
            //Прийняти налаштування мережевого рівня Ethernet

            settings_fix_edit.IPv4[0] = Canal2_MO_Received[4];
            settings_fix_edit.IPv4[1] = Canal2_MO_Received[5];
            settings_fix_edit.IPv4[2] = Canal2_MO_Received[6];
            settings_fix_edit.IPv4[3] = Canal2_MO_Received[7];
            settings_fix_edit.mask = Canal2_MO_Received[8];
            settings_fix_edit.gateway[0] = Canal2_MO_Received[9];
            settings_fix_edit.gateway[1] = Canal2_MO_Received[10];
            settings_fix_edit.gateway[2] = Canal2_MO_Received[11];
            settings_fix_edit.gateway[3] = Canal2_MO_Received[12];
            
            //Відправити підтвердження прийняття налаштувань мережевого рівня Ethernet
            sum += Canal2_MO_Transmit[index_w++] = CONFIRM_RECEIVING_SETTINGS_NETWORK_LAYER;
            sum += Canal2_MO_Transmit[index_w++] = true;
          }
          else 
          {
            index_w = 0;
            _CLEAR_STATE(queue_mo, STATE_QUEUE_MO_RECEIVING_SETTING_NETWORK_LAYER);
          
            if (
                (Canal2_MO_Received[3] == ANY_CONFIRMATION) &&
                (Canal2_MO_Received[4] == true)
               )
            {
              CANAL2_MO_state = CANAL2_MO_FREE;
              
              if (
                  (settings_fix.IPv4[0] != settings_fix_edit.IPv4[0]) ||
                  (settings_fix.IPv4[1] != settings_fix_edit.IPv4[1]) ||
                  (settings_fix.IPv4[2] != settings_fix_edit.IPv4[2]) ||
                  (settings_fix.IPv4[3] != settings_fix_edit.IPv4[3]) ||
                  (settings_fix.mask != settings_fix_edit.mask) ||
                  (settings_fix.gateway[0] != settings_fix_edit.gateway[0]) ||
                  (settings_fix.gateway[1] != settings_fix_edit.gateway[1]) ||
                  (settings_fix.gateway[2] != settings_fix_edit.gateway[2]) ||
                  (settings_fix.gateway[3] != settings_fix_edit.gateway[3])
                 )
              {
                //Є реальні зміни
                config_settings_modified |= MASKA_FOR_BIT(BIT_CHANGED_SETTINGS);
              
                settings_fix.IPv4[0] = settings_fix_edit.IPv4[0];
                settings_fix.IPv4[1] = settings_fix_edit.IPv4[1];
                settings_fix.IPv4[2] = settings_fix_edit.IPv4[2];
                settings_fix.IPv4[3] = settings_fix_edit.IPv4[3];
                settings_fix.mask = settings_fix_edit.mask;
                settings_fix.gateway[0] = settings_fix_edit.gateway[0];
                settings_fix.gateway[1] = settings_fix_edit.gateway[1];
                settings_fix.gateway[2] = settings_fix_edit.gateway[2];
                settings_fix.gateway[3] = settings_fix_edit.gateway[3];

                //Треба активувати нові налаштуваня
                unsigned int result = set_config_and_settings(1, NET_PARAMS_FIX_CHANGES);
                if (result != 0)
                {
                  //Повідомляємо про критичну помилку
                  current_state_menu2.edition = ED_ERROR;
                  CANAL2_MO_state = CANAL2_MO_ERROR;
                }
                config_settings_modified = 0;
              }
              else config_settings_modified = 0;
              
              if (CANAL2_MO_state == CANAL2_MO_FREE) Canal2 = true;
            }
            else
            {
              CANAL2_MO_state = CANAL2_MO_ERROR;
              unsigned int result = set_config_and_settings(0, NO_MATTER_PARAMS_FIX_CHANGES);
              if (result != 0)
              {
                //Повідомляємо про критичну помилку
                current_state_menu2.edition = ED_ERROR;
              }
            }
          }
        }
      }
    
      if (CANAL2_MO_state == CANAL2_MO_ERROR)
      {
        CANAL2_MO_state = CANAL2_MO_BREAK_LAST_ACTION;
        repeat = true;
      }
  
      tick = TIM4->CNT; /*стан лічильника коли буда завершена остання трасакція повністю з помилкою або без неї*/
    }
  }
  while(repeat == true);
  
  if (index_w != 0)
  {
    CANAL2_MO_state = CANAL2_MO_SENDING;

    //Додаємомконтрольну суму і мітку зафершенняпакету
    Canal2_MO_Transmit[index_w++] = sum;
    Canal2_MO_Transmit[index_w++] = STOP_BYTE_MO;
  
    /*
    Підготовляємо канал до прийняття даних
    */
    //Зупиняємо канал приймання
    if ((DMA_StreamCANAL2_MO_Rx->CR & (uint32_t)DMA_SxCR_EN) !=0) DMA_StreamCANAL2_MO_Rx->CR &= ~(uint32_t)DMA_SxCR_EN;  
      
    //Скидуємо всі можливі помилки
    CANAL2_MO->SR;
    (unsigned short int)(CANAL2_MO->DR & (uint16_t)0x01FF);
    CANAL2_MO->SR = (uint16_t)(~(uint32_t)USART_FLAG_LBD);
      
    // Очищаємо прапореці, що сигналізує про завершення передачі даних для DMA 
    DMA_ClearFlag(DMA_StreamCANAL2_MO_Rx, DMA_FLAG_TCCANAL2_MO_Rx | DMA_FLAG_HTCANAL2_MO_Rx | DMA_FLAG_TEICANAL2_MO_Rx | DMA_FLAG_DMEICANAL2_MO_Rx | DMA_FLAG_FEICANAL2_MO_Rx);

    DMA_StreamCANAL2_MO_Rx->NDTR = BUFFER_CANAL2_MO;
    //Запускаємо очікування прийому
    DMA_StreamCANAL2_MO_Rx->CR |= (uint32_t)DMA_SxCR_EN;
    /***/

    /*
    Починаємо відправляти дані
    */
    //Скидаємо біт, що символізує, що опстанній байт переданий
    USART_ClearFlag(CANAL2_MO, USART_FLAG_TC);

    //Зупиняємо потік DMA якщо він запущений
    if ((DMA_StreamCANAL2_MO_Tx->CR & (uint32_t)DMA_SxCR_EN) !=0) DMA_StreamCANAL2_MO_Tx->CR &= ~(uint32_t)DMA_SxCR_EN;
    DMA_StreamCANAL2_MO_Tx->NDTR = index_w;
    //Дозволяємо передачу через DMA
    if ((CANAL2_MO->CR3 & USART_DMAReq_Tx) == 0) USART2->CR3 |= USART_DMAReq_Tx;

    //Очищаємо прапореці, що сигналізує про завершення передачі даних для DMA1 по потоку CANAL1_MO_TX
    DMA_ClearFlag(DMA_StreamCANAL2_MO_Tx, DMA_FLAG_TCCANAL2_MO_Tx | DMA_FLAG_HTCANAL2_MO_Tx | DMA_FLAG_TEICANAL2_MO_Tx | DMA_FLAG_DMEICANAL2_MO_Tx | DMA_FLAG_FEICANAL2_MO_Tx);
    //Запускаємо передачу
    DMA_StreamCANAL2_MO_Tx->CR |= (uint32_t)DMA_SxCR_EN;
    /***/
  }
}
/***********************************************************************************/


