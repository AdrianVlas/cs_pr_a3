#include "header.h"

/*****************************************************/
//��������� �������� � ������ �� SPI
/*****************************************************/
void start_exchange_via_spi_df(uint32_t index_chip, uint32_t number)
{
  //���������, �� ��� ���� �� ������ SPI1
  state_execution_spi_df[index_chip] = TRANSACTION_EXECUTING;

  //��������� ���� DMA �� ������ ����� ���� �� ���������
  if ((DMA_StreamSPI_DF_Rx->CR & (uint32_t)DMA_SxCR_EN) !=0) DMA_StreamSPI_DF_Rx->CR &= ~(uint32_t)DMA_SxCR_EN;
  DMA_StreamSPI_DF_Rx->NDTR = number;
  //��������� ���� DMA �� �������� ����� ���� �� ���������
  if ((DMA_StreamSPI_DF_Tx->CR & (uint32_t)DMA_SxCR_EN) !=0) DMA_StreamSPI_DF_Tx->CR &= ~(uint32_t)DMA_SxCR_EN;
  DMA_StreamSPI_DF_Tx->NDTR = number;
  
  //������� ���������, �� �������� ��� ���������� ������/�������� ����� ��� DMA1 �� ������ SPI_DF_Rx � SPI_DF_Tx
  DMA_ClearFlag(DMA_StreamSPI_DF_Rx, DMA_FLAG_TCSPI_DF_Rx | DMA_FLAG_HTSPI_DF_Rx | DMA_FLAG_TEISPI_DF_Rx | DMA_FLAG_DMEISPI_DF_Rx | DMA_FLAG_FEISPI_DF_Rx);
  DMA_ClearFlag(DMA_StreamSPI_DF_Tx, DMA_FLAG_TCSPI_DF_Tx | DMA_FLAG_HTSPI_DF_Tx | DMA_FLAG_TEISPI_DF_Tx | DMA_FLAG_DMEISPI_DF_Tx | DMA_FLAG_FEISPI_DF_Tx);
  
  //���������� �������� ����� DMA
  if ((SPI_DF->CR2 & SPI_I2S_DMAReq_Tx) == 0) SPI_DF->CR2 |= SPI_I2S_DMAReq_Tx;
  //���������� ������ ����� DMA
  if ((SPI_DF->CR2 & SPI_I2S_DMAReq_Rx) == 0) SPI_DF->CR2 |= SPI_I2S_DMAReq_Rx;

  //����������� chip_select
  if (index_chip == INDEX_DATAFLASH_1) GPIO_SPI_DF_TOGGLE->BSRRH = GPIO_SPI_DF_TOGGLE_Pin;//DF_TOGGLE - �� ���������� � 0 
  else if (index_chip == INDEX_DATAFLASH_2)GPIO_SPI_DF_TOGGLE->BSRRL = GPIO_SPI_DF_TOGGLE_Pin;//DF_TOGGLE - �� ���������� � 1
  else
  {
    //³������� ����������� �������, ���� ����� ��� �� ����������������
    total_error_sw_fixed(6);
  }
  GPIO_SPI_DF->BSRRH = GPIO_NSSPin_DF; //����������� Chip_select ��������� NSS  � 0

  //���������� ��������� ���������� �� ������ DMA_StreamSPI_DF_Rx
  DMA_StreamSPI_DF_Rx->CR |= DMA_IT_TC;
  
  //������� ������ ��������
  SPI_DF->DR;
  SPI_DF->SR;

  //��������� ������-�������� 
  DMA_StreamSPI_DF_Rx->CR |= (uint32_t)DMA_SxCR_EN;
  DMA_StreamSPI_DF_Tx->CR |= (uint32_t)DMA_SxCR_EN;
}
/*****************************************************/

/*****************************************************/
//��������� ������ ����� SPI
/*****************************************************/
void main_routines_for_spi_df(uint32_t index_chip)
{
  //�������� ������� ����, �� ������ ��� ��������� �������� ��������/������ ��������� DataFlash
  static uint32_t address_read_write_tmp[SIZE_ONE_RECORD_PR_ERR], number_bytes_read_write_tmp[SIZE_ONE_RECORD_PR_ERR];
  static int32_t etap_writing_df[SIZE_ONE_RECORD_PR_ERR];
  
  if (state_execution_spi_df[index_chip] == TRANSACTION_EXECUTING_NONE)
  {
    /*************************************************/
    //����� ����� ��������� ���� ���������� ����� SPI
    /*************************************************/
    
    if _GET_OUTPUT_STATE(control_spi_df_tasks[index_chip], TASK_READ_SR_DF_BIT)
    {
      //������ ������ ������� � ��������� DataFlash
      TxBuffer_SPI_DF[0] = CODE_OPERATION_STATUS_READ;
      TxBuffer_SPI_DF[1] = 0; //����-���� ���� ��� ����, ��� �������� ������� ������� �������;
      
      //��������� ������ ������ � EEPROM
      start_exchange_via_spi_df(index_chip, 2);
    }
    else if _GET_OUTPUT_STATE(control_spi_df_tasks[index_chip], TASK_MAKING_PAGE_SIZE_256_BIT)
    {
      //��������� ������ �������� ��������� DataFlash �� ����� ������� � 256 ����
      TxBuffer_SPI_DF[0] = 0x3D;
      TxBuffer_SPI_DF[1] = 0x2A;
      TxBuffer_SPI_DF[2] = 0x80;
      TxBuffer_SPI_DF[3] = 0xA6;

      start_exchange_via_spi_df(index_chip, 4);
    }
    else if _GET_OUTPUT_STATE(control_spi_df_tasks[index_chip], TASK_ERASING_DATAFLASH_BIT)
    {
      //��������� ������ �������� ��������� DataFlash
      TxBuffer_SPI_DF[0] = 0xC7;
      TxBuffer_SPI_DF[1] = 0x94;
      TxBuffer_SPI_DF[2] = 0x80;
      TxBuffer_SPI_DF[3] = 0x9A;

      start_exchange_via_spi_df(index_chip, 4);
    }
    else if _GET_OUTPUT_STATE(control_spi_df_tasks[index_chip], TASK_WRITING_SERIAL_DATAFLASH_BIT)
    {
      //����� ����� ������ ��������� DataFlash
      
      if (etap_writing_df[index_chip] == ETAP_WRITING_DF_NONE)
      {
        //����� ������ ���� ��������

        //ʳ������ ���� �� ���� ������ 
        int32_t size_to_end = number_bytes_read_write[index_chip] - (address_read_write_tmp[index_chip] - address_read_write[index_chip]);

        if (size_to_end > 0)
        {
          if (
              ((uint32_t)size_to_end >= size_page_serial_dataflash[index_chip])  &&
              ((address_read_write_tmp[index_chip] & (size_page_serial_dataflash[index_chip] - 1)) == 0)
             )
          {
            //����� ���������� ����� ���� ������� ��������� "Main Memory Page Program Through Buffer"
            number_bytes_read_write_tmp[index_chip] = size_page_serial_dataflash[index_chip];
            
            etap_writing_df[index_chip] = ETAP_WRITING_DF_MAIN_MEMORY_PROGRAM_THROUGH_BUFFER;
          }
          else
          {
            //����� ���������� "������ �������� ��������" ��� ������ � ���������� �� � �������� "Main Memory Page to Buffer Transfer"
            int32_t size_to_end_page = size_page_serial_dataflash[index_chip] - (address_read_write_tmp[index_chip] & (size_page_serial_dataflash[index_chip] - 1));
            if (size_to_end > size_to_end_page) number_bytes_read_write_tmp[index_chip] = size_to_end_page;
            else number_bytes_read_write_tmp[index_chip] = size_to_end;
            
            etap_writing_df[index_chip] = ETAP_WRITING_DF_MAIN_MEMORY_TO_BUFFER_TRANSFER;
          }
        }
        else
        {
          //���� ����� ��� ���������, ���� ������� ����� ������ ��������� DataFlash
          number_bytes_read_write_tmp[index_chip] = 0;
          
          etap_writing_df[index_chip] = ETAP_WRITING_DF_NONE;
        }
      }
      
      uint32_t number_transmit;
      
      switch (etap_writing_df[index_chip])
      {
      case ETAP_WRITING_DF_NONE:
        {
          //����� ��������� ��������� ������
          _CLEAR_STATE(control_spi_df_tasks[index_chip], TASK_WRITING_SERIAL_DATAFLASH_BIT);
          break;
        }
      case ETAP_WRITING_DF_MAIN_MEMORY_PROGRAM_THROUGH_BUFFER:
        {
          //����� �������� � ���'��� ��������� ����� �����
          
          int32_t base_index = (address_read_write_tmp[index_chip] - address_read_write[index_chip]);
          if (
              ((base_index + size_page_serial_dataflash[index_chip]) > SIZE_BUFFER_SERIAL_DATAFLASH_READ_WRITE) ||
              (base_index < 0)  
             )   
          {
            //³������� ����������� �������, ���� ����� ��� �� ����������������
            total_error_sw_fixed(9);
          }

          uint32_t address_internal = address_read_write_tmp[index_chip] & (number_page_serial_dataflash[index_chip]*size_page_serial_dataflash[index_chip] - 1);
          
          TxBuffer_SPI_DF[0] = CODE_OPERATION_WRITE_PAGE_THROUGH_BUFFER;
          TxBuffer_SPI_DF[1] = (address_internal >> 16) & 0xff; //������� ���� ������ �������
          TxBuffer_SPI_DF[2] = (address_internal >>  8) & 0xff; //������� ���� ������ �������
          TxBuffer_SPI_DF[3] = (address_internal      ) & 0xff; //������ � ������� ������� - ���������� �� ���� 0
          for (size_t i = 0; i < size_page_serial_dataflash[index_chip]; i++)
            TxBuffer_SPI_DF[4 + i] = buffer_serial_DataFlash_read_write[index_chip][base_index + i];
            
          number_transmit = 4 + size_page_serial_dataflash[index_chip];
          break;
        }
      case ETAP_WRITING_DF_MAIN_MEMORY_TO_BUFFER_TRANSFER:
        {
          //����� ������� ��������� ������� � ����� ��������� DataFlash 
          
          uint32_t address_internal = address_read_write_tmp[index_chip] & ((number_page_serial_dataflash[index_chip]*size_page_serial_dataflash[index_chip] - 1) & (uint32_t)(~(size_page_serial_dataflash[index_chip] - 1)));
          
          TxBuffer_SPI_DF[0] = CODE_OPERATION_READ_PAGE_INTO_BUFFER;
          TxBuffer_SPI_DF[1] = (address_internal >> 16) & 0xff; //������� ���� ������ �������
          TxBuffer_SPI_DF[2] = (address_internal >>  8) & 0xff; //������� ���� ������ �������
          //������ � ������� ������� �� �� ��������, ��� ���� �� ���
          
          number_transmit = 4;
          break;
        }
      case ETAP_WRITING_DF_BUFFER_WRITE:
        {
          //����� ������������ ������� ������

          int32_t base_index = (address_read_write_tmp[index_chip] - address_read_write[index_chip]);
          if (
              ((base_index + number_bytes_read_write_tmp[index_chip]) > SIZE_BUFFER_SERIAL_DATAFLASH_READ_WRITE) ||
              (base_index < 0)  
             )
          {
            //³������� ����������� �������, ���� ����� ��� �� ����������������
            total_error_sw_fixed(10);
          }

          uint32_t address_internal = address_read_write_tmp[index_chip] & (size_page_serial_dataflash[index_chip] - 1);
          
          TxBuffer_SPI_DF[0] = CODE_OPERATION_WRITE_BUFFER;
          TxBuffer_SPI_DF[1] = 0;                               //������� ���� ������ ������� �� �� ��������
          TxBuffer_SPI_DF[2] = (address_internal >>  8) & 0xff; //������� ���� ������ ������� �� �� ��������
          TxBuffer_SPI_DF[3] = (address_internal      ) & 0xff; //������ � ������� ������� - ���������� �� ���� 0
          for (size_t i = 0; i < number_bytes_read_write_tmp[index_chip]; i++)
            TxBuffer_SPI_DF[4 + i] = buffer_serial_DataFlash_read_write[index_chip][base_index + i];
            
          number_transmit = 4 + number_bytes_read_write_tmp[index_chip];
          break;
        }
      case ETAP_WRITING_DF_BUFFER_TO_MAIN_MEMORY_PROGRAM_WITH_BUIT_IN_ERASE:
        {
          //����� �������� ����� ��������� DataFlash � ���'��� ��������� DataFlash � ��������� ������ �������
          
          uint32_t address_internal = address_read_write_tmp[index_chip] & ((number_page_serial_dataflash[index_chip]*size_page_serial_dataflash[index_chip] - 1) & (uint32_t)(~(size_page_serial_dataflash[index_chip] - 1)));
          
          TxBuffer_SPI_DF[0] = CODE_OPERATION_WRITE_BUFFER_INTO_MEMORY_WITH_ERASE;
          TxBuffer_SPI_DF[1] = (address_internal >> 16) & 0x01; //������� ���� ������ �������
          TxBuffer_SPI_DF[2] = (address_internal >>  8) & 0xff; //������� ���� ������ �������
          //������ � ������� ������� �� �� ��������, ��� ���� �� ���
          
          number_transmit = 4;
          break;
        }
      default:
        {
          //³������� ����������� �������, ���� ����� ��� �� ����������������
          total_error_sw_fixed(8);
        }
      }

      
      if (etap_writing_df[index_chip] != ETAP_WRITING_DF_NONE)
      {
        //��������� ������ ����� DataFlash, ��� � �� ����������
        start_exchange_via_spi_df(index_chip, number_transmit);
      }
    }
    else if _GET_OUTPUT_STATE(control_spi_df_tasks[index_chip], TASK_READING_SERIAL_DATAFLASH_BIT)
    {
      //����� ����� ������� ��������� DataFlash

      //ʳ������ ���� �� ���� ������ 
      int32_t size_to_end = number_bytes_read_write[index_chip] - (address_read_write_tmp[index_chip] - address_read_write[index_chip]); 
      
      if (size_to_end > 0)
      {
        uint32_t address_internal = address_read_write_tmp[index_chip] & (number_page_serial_dataflash[index_chip]*size_page_serial_dataflash[index_chip] - 1);
          
        TxBuffer_SPI_DF[0] = CODE_OPERATION_READ_HIGH_FREQ;
        TxBuffer_SPI_DF[1] = (address_internal >> 16) & 0x01; //������� ���� ������ �������
        TxBuffer_SPI_DF[2] = (address_internal >>  8) & 0xff; //������� ���� ������ �������
        TxBuffer_SPI_DF[3] = (address_internal      ) & 0xff; //������ � ������� �������
        //ϳ��� ������ �� ��� ���� ��������� ���� �� ����� ����� �������� ����������� �������� �����

        if ((uint32_t)(size_to_end + 5) <= SIZE_BUFFER_SERIAL_DATAFLASH_DMA) number_bytes_read_write_tmp[index_chip] = size_to_end;
        else number_bytes_read_write_tmp[index_chip] = (SIZE_BUFFER_SERIAL_DATAFLASH_DMA - 5);
        
        //��������� ������ ������� � DataFlash
        start_exchange_via_spi_df(index_chip, (5 + number_bytes_read_write_tmp[index_chip]));
      }
      else
      {
        //���� ����� ��� ��������, ���� ������� ����� ������� ��������� DataFlash
        _CLEAR_STATE(control_spi_df_tasks[index_chip], TASK_READING_SERIAL_DATAFLASH_BIT);
      }
    }
    else if _GET_OUTPUT_STATE(control_spi_df_tasks[index_chip], TASK_START_MAKE_PAGE_SIZE_256_BIT)
    {
      //������� �� ������� ����������� ��������� �� ������ ������� � 256 ���� � ����������� �� ����������� ��������� �� ������ ������� � 256 ���� � ���� ������� ������� �������
      _SET_STATE(control_spi_df_tasks[index_chip], TASK_READ_SR_DF_BIT);
      _SET_STATE(control_spi_df_tasks[index_chip], TASK_MAKING_PAGE_SIZE_256_BIT);
      _CLEAR_STATE(control_spi_df_tasks[index_chip], TASK_START_MAKE_PAGE_SIZE_256_BIT);
    }
    else if _GET_OUTPUT_STATE(control_spi_df_tasks[index_chip], TASK_START_ERASE_DATAFLASH_BIT)
    {
      //������� �� ������� �������� �񳺿 ��������� DataFlash � ����������� �� �������� ��������� DataFlash � ���� ������� ������� �������
      _SET_STATE(control_spi_df_tasks[index_chip], TASK_READ_SR_DF_BIT);
      _SET_STATE(control_spi_df_tasks[index_chip], TASK_ERASING_DATAFLASH_BIT);
      _CLEAR_STATE(control_spi_df_tasks[index_chip], TASK_START_ERASE_DATAFLASH_BIT);
    }
    else if _GET_OUTPUT_STATE(control_spi_df_tasks[index_chip], TASK_START_WRITE_SERIAL_DATAFLASH_BIT)
    {
//      /*****/
//      //ҳ���� ��� �������
//      /*****/
//      for(unsigned int i = 0; i < number_bytes_read_write[index_chip]; i++)
//        buffer_serial_DataFlash_read_write[i] = (i + 1) & 0xff;
//      /*****/

      //��������� ������ � �������� DataFlash � ��� ����� ������ ����������
      address_read_write_tmp[index_chip] = address_read_write[index_chip];
      //�������, �� �� ����� ������ �� �� ��� ����� �����
      number_bytes_read_write_tmp[index_chip] = 0;
      //�������, �� �������� ������ �����������
      etap_writing_df[index_chip] = ETAP_WRITING_DF_NONE;
      
      //������� �� ������� ������ ��������� DataFlash � ����������� �� ������ ��������� DataFlash � ���� ������� ������� �������
      _SET_STATE(control_spi_df_tasks[index_chip], TASK_READ_SR_DF_BIT);
      _SET_STATE(control_spi_df_tasks[index_chip], TASK_WRITING_SERIAL_DATAFLASH_BIT);
      _CLEAR_STATE(control_spi_df_tasks[index_chip], TASK_START_WRITE_SERIAL_DATAFLASH_BIT);
    }
    else if _GET_OUTPUT_STATE(control_spi_df_tasks[index_chip], TASK_START_READ_SERIAL_DATAFLASH_BIT)
    {
      //��������� ������ � �������� DataFlash � ��� ����� ������ �������
      address_read_write_tmp[index_chip] = address_read_write[index_chip];
      //�������, �� �� ����� ������ �� �� ��� ���� ����������
      number_bytes_read_write_tmp[index_chip] = 0;
      
      //������� �� ������� ������� ��������� DataFlash � ����������� �� ������� ��������� DataFlash � ���� ������� ������� �������
      _SET_STATE(control_spi_df_tasks[index_chip], TASK_READ_SR_DF_BIT);
      _SET_STATE(control_spi_df_tasks[index_chip], TASK_READING_SERIAL_DATAFLASH_BIT);
      _CLEAR_STATE(control_spi_df_tasks[index_chip], TASK_START_READ_SERIAL_DATAFLASH_BIT);
    }
    /*************************************************/
  }
  else if (state_execution_spi_df[index_chip] == TRANSACTION_EXECUTED_WAIT_ANALIZE)
  {
    /*************************************************/
    //���� ���������� ��� �������
    /*************************************************/

    //����������� �����������, �� SPI_DF ������� �� ���� ���������� 
    state_execution_spi_df[index_chip] = TRANSACTION_EXECUTING_NONE;

    if _GET_OUTPUT_STATE(control_spi_df_tasks[index_chip], TASK_READ_SR_DF_BIT)
    {
      //��� ���� �� ���� ������ ������ ���� ������� ������� ������� EEPROM, ��� ���� ��� �������� �� ���������� ������ �� ������������ ������������ ������
      
      status_register_df[index_chip] = RxBuffer_SPI_DF[1 + 0];

      //��������� ������ �������
      if ((status_register_df[index_chip] & (1 << 7)) != 0)
      {
        //̳�������� DataFlash �� � � ���� "BUSY"
        _CLEAR_STATE(control_spi_df_tasks[index_chip], TASK_READ_SR_DF_BIT);
      }
      else
      {
        //������ �������� �������� �� ���� �������, ���� ̳�������� DataFlash �� ������� � ���� "BUSY"
      }
    }
    else if _GET_OUTPUT_STATE(control_spi_df_tasks[index_chip], TASK_MAKING_PAGE_SIZE_256_BIT)
    {
      //���������� ������ �������� ��������� DataFlash �� ����� ������� � 256 ����

      //����������� �� ���������� ������� ������� ������� ��������� DataFlash
      _SET_STATE(control_spi_df_tasks[index_chip], TASK_READ_SR_DF_BIT);

      //������� �� ������� �������� ��������� DataFlash �� ����� ������� � 256 ����
      _CLEAR_STATE(control_spi_df_tasks[index_chip], TASK_MAKING_PAGE_SIZE_256_BIT);
    }
    else if _GET_OUTPUT_STATE(control_spi_df_tasks[index_chip], TASK_ERASING_DATAFLASH_BIT)
    {
      //���������� ������ �������� ��������� DataFlash

      //������� �� �������� ��������� DataFlash
      _CLEAR_STATE(control_spi_df_tasks[index_chip], TASK_ERASING_DATAFLASH_BIT);
    }
    else if _GET_OUTPUT_STATE(control_spi_df_tasks[index_chip], TASK_WRITING_SERIAL_DATAFLASH_BIT)
    {
      //���������� ���� ������� ������ ����������, ��������� ������  number_bytes_read_write_tmp[index_chip], � ��������� DataFlash
      
      if (
          (etap_writing_df[index_chip] == ETAP_WRITING_DF_MAIN_MEMORY_PROGRAM_THROUGH_BUFFER              ) ||
          (etap_writing_df[index_chip] == ETAP_WRITING_DF_BUFFER_TO_MAIN_MEMORY_PROGRAM_WITH_BUIT_IN_ERASE)
         ) 
      {
        //����������� �������� ������ ������ ���������� � ���'��� ��������� DataFlash

        //�������� ������ � ���, �������, ����� ���� ���������� �������
        address_read_write_tmp[index_chip] += number_bytes_read_write_tmp[index_chip];
        
        //�������. �� ����� ���������� ���� ������ ���������� ��� ������
        etap_writing_df[index_chip] = ETAP_WRITING_DF_NONE;
      }
      else if (
               (etap_writing_df[index_chip] == ETAP_WRITING_DF_NONE                                            ) ||
               (etap_writing_df[index_chip] >  ETAP_WRITING_DF_BUFFER_TO_MAIN_MEMORY_PROGRAM_WITH_BUIT_IN_ERASE)  
              )   
      {
        //³������� ����������� �������, ���� ����� ��� �� ����������������
        total_error_sw_fixed(11);
      }
      else
      {
        //���������� �� ��������� ���� ������ ������ ���������� �������� ������  number_bytes_read_write_tmp[index_chip]
        etap_writing_df[index_chip]++;
      }

      //����������� �� ���������� ������� ������� ������� ��������� DataFlash
      _SET_STATE(control_spi_df_tasks[index_chip], TASK_READ_SR_DF_BIT);
    }
    else if _GET_OUTPUT_STATE(control_spi_df_tasks[index_chip], TASK_READING_SERIAL_DATAFLASH_BIT)
    {
      //���������� ������ ������� ����������, �������� ������  number_bytes_read_write_tmp[index_chip], � ��������� DataFlash
      
      //������� �������� ����������
      int32_t base_index = (address_read_write_tmp[index_chip] - address_read_write[index_chip]);
      if (
          ((base_index + number_bytes_read_write_tmp[index_chip]) > SIZE_BUFFER_SERIAL_DATAFLASH_READ_WRITE) ||
          (base_index < 0)  
         )   
      {
        //³������� ����������� �������, ���� ����� ��� �� ����������������
        total_error_sw_fixed(7);
      }
      for(size_t i = 0; i < number_bytes_read_write_tmp[index_chip]; i++)
        buffer_serial_DataFlash_read_write[index_chip][base_index + i] = RxBuffer_SPI_DF[5 + i];
      
      //�������� ������ � ���, �������, ����� ���� ���������� �������
      address_read_write_tmp[index_chip] += number_bytes_read_write_tmp[index_chip];

      //����������� �� ���������� ������� ������� ������� ��������� DataFlash
      _SET_STATE(control_spi_df_tasks[index_chip], TASK_READ_SR_DF_BIT);
    }
    else
    {
      //����, ����������, ����� �� ���� � ����
      //� ��� ������� �������� ����� �� ������
    }
    /*************************************************/
  }
  else if (state_execution_spi_df[index_chip] == TRANSACTION_EXECUTED_ERROR)
  {
    /*************************************************/
    //���� ���������� � ��������
    /*************************************************/

    //����������� �����������, �� I2C ������� �� ���� ���������� 
    state_execution_spi_df[index_chip] = TRANSACTION_EXECUTING_NONE;

    //����������� � ���������� ����
    if _GET_OUTPUT_STATE(control_spi_df_tasks[index_chip], TASK_READ_SR_DF_BIT)
    {
      //�������� ������ ������� ��������� DataFlash 
      
      //�������� ������ ������ ������� ��������� DataFlash  
    }
    else if (
             _GET_OUTPUT_STATE(control_spi_df_tasks[index_chip], TASK_MAKING_PAGE_SIZE_256_BIT) ||
             _GET_OUTPUT_STATE(control_spi_df_tasks[index_chip], TASK_ERASING_DATAFLASH_BIT) ||
             _GET_OUTPUT_STATE(control_spi_df_tasks[index_chip], TASK_WRITING_SERIAL_DATAFLASH_BIT) ||
             _GET_OUTPUT_STATE(control_spi_df_tasks[index_chip], TASK_READING_SERIAL_DATAFLASH_BIT)
            )   
    {
      if _GET_OUTPUT_STATE(control_spi_df_tasks[index_chip], TASK_WRITING_SERIAL_DATAFLASH_BIT)
      {
        //���������� ������ ����� ���������� � ��������� DataFlash
      
        //���������� ���� ������ ������ ���������� (�������� ������  number_bytes_read_write_tmp[index_chip]) � ���������� ����
        etap_writing_df[index_chip] = ETAP_WRITING_DF_NONE;
      }
      
      //����������� �� ���������� ������� ������� ������� ��������� DataFlash
      _SET_STATE(control_spi_df_tasks[index_chip], TASK_READ_SR_DF_BIT);
    }
    else
    {
      //� ��� ������� �������� ����� �� ������
    }
    /*************************************************/
  }
}
/*****************************************************/

/*****************************************************/
//
/*****************************************************/
/*****************************************************/
