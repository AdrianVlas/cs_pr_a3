#include "header.h"

/***********************************************************************************
Прийом даних через інтерфейс CANAL1_MO
***********************************************************************************/
void start_receive_data_via_CANAL1_MO(void)
{
  //Попередньо скидаємо повідомплення про помилки, які потім будемо виставляти
  clear_diagnostyka[0] |= WORD_0_MASKA_ERRORS_FROM_CANAL_1;
  clear_diagnostyka[1] |= WORD_1_MASKA_ERRORS_FROM_CANAL_1;
  clear_diagnostyka[2] |= WORD_2_MASKA_ERRORS_FROM_CANAL_1;
  
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
          IEC_board_present = true;
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
                  
                  size_t shift = Canal1_MO_Received[index + 0] | (Canal1_MO_Received[index + 1] << 8);
                  size_t size = Canal1_MO_Received[index + 2] | (Canal1_MO_Received[index + 3] << 8);
                  index += 4;

                  if ((index + size) < BUFFER_CANAL1_MO)
                  {
                    for (size_t i = 0; i < size; i++)
                    {
                      size_t shift_tmp = shift + i;
                      if (shift_tmp < size_block_rx)
                      {
                        p_buffer_rx[shift_tmp] = Canal1_MO_Received[index++];
                      }
                      else
                      {
                        shift_tmp -= size_block_rx;
                        if (shift_tmp < size_block_rx)
                        {
                          p_buffer_ctrl_rx[shift_tmp] = Canal1_MO_Received[index++];
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
                if (_GET_OUTPUT_STATE(confirm_diagnostyka_mo, ERROR_RECEIVING_CANAL_1)         ) _SET_BIT(set_diagnostyka, ERROR_IEC_RECEIVING_CANAL_1);
                if (_GET_OUTPUT_STATE(confirm_diagnostyka_mo, ERROR_RECEIVED_PACKET_CANAL_1   )) _SET_BIT(set_diagnostyka, ERROR_IEC_RECEIVED_PACKET_CANAL_1);
                if (_GET_OUTPUT_STATE(confirm_diagnostyka_mo, ERROR_REQUEST_CANAL_1)           ) _SET_BIT(set_diagnostyka, ERROR_IEC_REQUEST_CANAL_1);

                if (_GET_OUTPUT_STATE(confirm_diagnostyka_mo, ERROR_RECEIVING_CANAL_2)         ) _SET_BIT(set_diagnostyka, ERROR_IEC_RECEIVING_CANAL_2);
                if (_GET_OUTPUT_STATE(confirm_diagnostyka_mo, ERROR_RECEIVED_PACKET_CANAL_2   )) _SET_BIT(set_diagnostyka, ERROR_IEC_RECEIVED_PACKET_CANAL_2);
                if (_GET_OUTPUT_STATE(confirm_diagnostyka_mo, ERROR_REQUEST_CANAL_2)           ) _SET_BIT(set_diagnostyka, ERROR_IEC_REQUEST_CANAL_2);
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
    if (IEC_board_present == true) _SET_BIT(set_diagnostyka, ERROR_CPU_NO_ANSWER_CANAL_1);
//    IEC_board_present = false;
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

