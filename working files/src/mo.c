#include "header.h"

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
  uint32_t index_ln = 0;
  for (size_t id = _ID_FB_FIRST_ALL; id < _ID_FB_LAST_ALL; id++)
  {
    size_t size_block = 0, size_add_data = 0, size_struct = 0;
    uint8_t *p_buffer = NULL, *p_add_data = NULL;
    uint32_t n = 0;
    switch (id)
    {
    case ID_FB_CONTROL_BLOCK:
      {
        n = 1;
        size_block = DIV_TO_HIGHER(FIX_BLOCK_SIGNALS_OUT, 8);
        p_buffer = fix_block_active_state;
        size_struct = 0; /*ця змінна не мала б використовуватися для "Загального блоку"*/
        break;
      }
    case ID_FB_INPUT:
      {
        n = current_config_prt.n_input;
        if (n != 0)
        {
          size_block = DIV_TO_HIGHER(INPUT_SIGNALS_OUT, 8);
          p_buffer = ((__LN_INPUT*)spca_of_p_prt[ID_FB_INPUT - _ID_FB_FIRST_VAR])->active_state;
          size_struct = sizeof(__LN_INPUT);
        }
        break;
      }
    case ID_FB_OUTPUT:
      {
        n = current_config_prt.n_output;
        if (n != 0)
        {
          size_block = DIV_TO_HIGHER(OUTPUT_LED_SIGNALS_OUT_TOTAL, 8);
          p_buffer = ((__LN_OUTPUT_LED*)spca_of_p_prt[ID_FB_OUTPUT - _ID_FB_FIRST_VAR])->active_state;
          size_struct = sizeof(__LN_OUTPUT_LED);
        }
        break;
      }
    case ID_FB_LED:
      {
        n = current_config_prt.n_led;
        if (n != 0)
        {
          size_block = DIV_TO_HIGHER(OUTPUT_LED_SIGNALS_OUT_TOTAL, 8);
          p_buffer = ((__LN_OUTPUT_LED*)spca_of_p_prt[ID_FB_LED - _ID_FB_FIRST_VAR])->active_state;
          size_struct = sizeof(__LN_OUTPUT_LED);
        }
        break;
      }
    case ID_FB_BUTTON:
      {
        n = current_config_prt.n_button;
        if (n != 0)
        {
          size_block = DIV_TO_HIGHER(BUTTON_SIGNALS_OUT, 8);
          p_buffer = ((__LN_BUTTON*)spca_of_p_prt[ID_FB_BUTTON - _ID_FB_FIRST_VAR])->active_state;
          size_struct = sizeof(__LN_BUTTON);
        }
        break;
      }
    case ID_FB_ALARM:
      {
        n = current_config_prt.n_alarm;
        if (n != 0)
        {
          size_block = DIV_TO_HIGHER(ALARM_SIGNALS_OUT, 8);
          p_buffer = ((__LN_ALARM*)spca_of_p_prt[ID_FB_ALARM - _ID_FB_FIRST_VAR])->active_state;
          size_struct = sizeof(__LN_ALARM);
        }
        break;
      }
    case ID_FB_GROUP_ALARM:
      {
        n = current_config_prt.n_group_alarm;
        if (n != 0)
        {
          size_block = DIV_TO_HIGHER(GROUP_ALARM_SIGNALS_OUT, 8);
          size_add_data = sizeof(uint32_t);
          p_buffer = ((__LN_GROUP_ALARM*)spca_of_p_prt[ID_FB_GROUP_ALARM - _ID_FB_FIRST_VAR])->active_state;
          p_add_data = (uint8_t*)(&(((__LN_GROUP_ALARM*)spca_of_p_prt[ID_FB_GROUP_ALARM - _ID_FB_FIRST_VAR])->NNC));
          size_struct = sizeof(__LN_GROUP_ALARM);
        }
        break;
      }
    case ID_FB_INPUT_GOOSE_BLOCK:
      {
        n = current_config_prt.n_input_GOOSE_block;
        if (n != 0)
        {
          size_block = DIV_TO_HIGHER(INPUT_GOOSE_BLOCK_SIGNALS_OUT, 8);
          p_buffer = ((__LN_INPUT_GOOSE_BLOCK*)spca_of_p_prt[ID_FB_INPUT_GOOSE_BLOCK - _ID_FB_FIRST_VAR])->active_state;
          size_struct = sizeof(__LN_INPUT_GOOSE_BLOCK);
        }
        break;
      }
    case ID_FB_INPUT_MMS_BLOCK:
      {
        n = current_config_prt.n_input_MMS_block;
        if (n != 0)
        {
          size_block = DIV_TO_HIGHER(FIX_BLOCK_SIGNALS_OUT, 8);
          p_buffer = ((__LN_INPUT_MMS_BLOCK*)spca_of_p_prt[ID_FB_INPUT_MMS_BLOCK - _ID_FB_FIRST_VAR])->active_state;
          size_struct = sizeof(__LN_INPUT_MMS_BLOCK);
        }
        break;
      }
    case ID_FB_NETWORK_OUTPUT_BLOCK:
      {
        n = current_config_prt.n_network_output_block;
        if (n != 0)
        {
          size_block = DIV_TO_HIGHER(INPUT_MMS_BLOCK_SIGNALS_OUT, 8);
          p_buffer = ((__LN_NETWORK_OUTPUT_BLOCK*)spca_of_p_prt[ID_FB_NETWORK_OUTPUT_BLOCK - _ID_FB_FIRST_VAR])->active_state;
          size_struct = sizeof(__LN_NETWORK_OUTPUT_BLOCK);
        }
        break;
      }
    case ID_FB_EVENT_LOG:
      {
        n = 1;
        size_block = DIV_TO_HIGHER(NETWORK_OUTPUT_BLOCK_SIGNALS_OUT, 8);
        p_buffer = (uint8_t*)((__LOG_INPUT*)spca_of_p_prt[ID_FB_EVENT_LOG - _ID_FB_FIRST_VAR]);
        size_struct = 0;/*ця змінна не мала б використовуватися для "Журналу подій"*/
        break;
      }
    default: break;
    }
    
    if (n != 0)
    {
      size_t size_full_block = size_block + size_add_data;
      for (size_t n_tmp = 0; n_tmp < n; n_tmp++)
      {
        if ((index + 1 + 1 + 2 + 2 + size_full_block) < BUFFER_CANAL1_MO)
        {
          sum += Canal1_MO_Transmit[index++] = START_LABEL_NEW_TM;
    
          sum += Canal1_MO_Transmit[index++] = index_ln++;
    
          sum += Canal1_MO_Transmit[index++] = 0;
          sum += Canal1_MO_Transmit[index++] = 0;
          
          sum += Canal1_MO_Transmit[index++] = (size_full_block  & 0xff);
          sum += Canal1_MO_Transmit[index++] = ((size_full_block >> 8) & 0xff);
    
          for (uint32_t i = 0; i < size_block; i++) 
          {
            sum += Canal1_MO_Transmit[index++] = p_buffer[i];
          }
          for (uint32_t i = 0; i < size_add_data; i++) 
          {
            sum += Canal1_MO_Transmit[index++] = p_add_data[i];
          }
        }
        else break;

        //Переводимо вказівник на наступний елемент
        p_buffer += size_struct;
        p_add_data +=size_struct;
      }
    }

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

  if ((index + 2) >= BUFFER_CANAL1_MO) total_error_sw_fixed(22);
  
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

