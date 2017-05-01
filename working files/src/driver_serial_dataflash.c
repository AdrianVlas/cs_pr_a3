#include "header.h"

/*****************************************************/
//Запустити передачу і прийом по SPI
/*****************************************************/
void start_exchange_via_spi_df(uint32_t index_chip, uint32_t number)
{
  //Позначаємо, що іде одмін по каналу SPI1
  state_execution_spi_df[index_chip] = TRANSACTION_EXECUTING;

  //Зупиняємо потік DMA на прийом даних якщо він запущений
  if ((DMA_StreamSPI_DF_Rx->CR & (uint32_t)DMA_SxCR_EN) !=0) DMA_StreamSPI_DF_Rx->CR &= ~(uint32_t)DMA_SxCR_EN;
  DMA_StreamSPI_DF_Rx->NDTR = number;
  //Зупиняємо потік DMA на передачу даних якщо він запущений
  if ((DMA_StreamSPI_DF_Tx->CR & (uint32_t)DMA_SxCR_EN) !=0) DMA_StreamSPI_DF_Tx->CR &= ~(uint32_t)DMA_SxCR_EN;
  DMA_StreamSPI_DF_Tx->NDTR = number;
  
  //Очищаємо прапореці, що сигналізує про завершення прийом/передачі даних для DMA1 по каналу SPI_DF_Rx і SPI_DF_Tx
  DMA_ClearFlag(DMA_StreamSPI_DF_Rx, DMA_FLAG_TCSPI_DF_Rx | DMA_FLAG_HTSPI_DF_Rx | DMA_FLAG_TEISPI_DF_Rx | DMA_FLAG_DMEISPI_DF_Rx | DMA_FLAG_FEISPI_DF_Rx);
  DMA_ClearFlag(DMA_StreamSPI_DF_Tx, DMA_FLAG_TCSPI_DF_Tx | DMA_FLAG_HTSPI_DF_Tx | DMA_FLAG_TEISPI_DF_Tx | DMA_FLAG_DMEISPI_DF_Tx | DMA_FLAG_FEISPI_DF_Tx);
  
  //Дозволяємо передачу через DMA
  if ((SPI_DF->CR2 & SPI_I2S_DMAReq_Tx) == 0) SPI_DF->CR2 |= SPI_I2S_DMAReq_Tx;
  //Дозволяємо прийом через DMA
  if ((SPI_DF->CR2 & SPI_I2S_DMAReq_Rx) == 0) SPI_DF->CR2 |= SPI_I2S_DMAReq_Rx;

  //Виставляємо chip_select
  if (index_chip == INDEX_DATAFLASH_1) GPIO_SPI_DF_TOGGLE->BSRRH = GPIO_SPI_DF_TOGGLE_Pin;//DF_TOGGLE - пін переводимо у 0 
  else if (index_chip == INDEX_DATAFLASH_2)GPIO_SPI_DF_TOGGLE->BSRRL = GPIO_SPI_DF_TOGGLE_Pin;//DF_TOGGLE - пін переводимо у 1
  else
  {
    //Відбцлася невизначена помилка, тому треба піти на перезавантаження
    total_error_sw_fixed(6);
  }
  GPIO_SPI_DF->BSRRH = GPIO_NSSPin_DF; //Виставляємо Chip_select переводом NSS  у 0

  //Дозволяэмо генерацыю переривань від потоку DMA_StreamSPI_DF_Rx
  DMA_StreamSPI_DF_Rx->CR |= DMA_IT_TC;
  
  //Очищаємо можливі помилкит
  SPI_DF->DR;
  SPI_DF->SR;

  //Запускаємо прийом-передачу 
  DMA_StreamSPI_DF_Rx->CR |= (uint32_t)DMA_SxCR_EN;
  DMA_StreamSPI_DF_Tx->CR |= (uint32_t)DMA_SxCR_EN;
}
/*****************************************************/

/*****************************************************/
//Управління обміном через SPI
/*****************************************************/
void main_routines_for_spi_df(uint32_t index_chip)
{
  //Тимчасові статичні змінні, які потрібні для виконання операцій читанння/запису мікросхеми DataFlash
  static uint32_t address_read_write_tmp[SIZE_ONE_RECORD_PR_ERR], number_bytes_read_write_tmp[SIZE_ONE_RECORD_PR_ERR];
  static int32_t etap_writing_df[SIZE_ONE_RECORD_PR_ERR];
  
  if (state_execution_spi_df[index_chip] == TRANSACTION_EXECUTING_NONE)
  {
    /*************************************************/
    //Зараз можна ініціювати нову трансакцію через SPI
    /*************************************************/
    
    if _GET_OUTPUT_STATE(control_spi_df_tasks[index_chip], TASK_READ_SR_DF_BIT)
    {
      //Читаємо регістр статусу з мікросхеми DataFlash
      TxBuffer_SPI_DF[0] = CODE_OPERATION_STATUS_READ;
      TxBuffer_SPI_DF[1] = 0; //Будь-який байт для того, щоб здійснити читання регістру статусу;
      
      //Запускаємо процес запису в EEPROM
      start_exchange_via_spi_df(index_chip, 2);
    }
    else if _GET_OUTPUT_STATE(control_spi_df_tasks[index_chip], TASK_MAKING_PAGE_SIZE_256_BIT)
    {
      //Запускаємо процес переводу мікросхеми DataFlash не розмір сторінки у 256 байт
      TxBuffer_SPI_DF[0] = 0x3D;
      TxBuffer_SPI_DF[1] = 0x2A;
      TxBuffer_SPI_DF[2] = 0x80;
      TxBuffer_SPI_DF[3] = 0xA6;

      start_exchange_via_spi_df(index_chip, 4);
    }
    else if _GET_OUTPUT_STATE(control_spi_df_tasks[index_chip], TASK_ERASING_DATAFLASH_BIT)
    {
      //Запускаємо процес стирання мікросхеми DataFlash
      TxBuffer_SPI_DF[0] = 0xC7;
      TxBuffer_SPI_DF[1] = 0x94;
      TxBuffer_SPI_DF[2] = 0x80;
      TxBuffer_SPI_DF[3] = 0x9A;

      start_exchange_via_spi_df(index_chip, 4);
    }
    else if _GET_OUTPUT_STATE(control_spi_df_tasks[index_chip], TASK_WRITING_SERIAL_DATAFLASH_BIT)
    {
      //Стоїть умова запису мікросхеми DataFlash
      
      if (etap_writing_df[index_chip] == ETAP_WRITING_DF_NONE)
      {
        //Треба почати нову операцію

        //Кількість байт до кінця буферу 
        int32_t size_to_end = number_bytes_read_write[index_chip] - (address_read_write_tmp[index_chip] - address_read_write[index_chip]);

        if (size_to_end > 0)
        {
          if (
              ((uint32_t)size_to_end >= size_page_serial_dataflash[index_chip])  &&
              ((address_read_write_tmp[index_chip] & (size_page_serial_dataflash[index_chip] - 1)) == 0)
             )
          {
            //Можна записувати зразу цілу сторінку операцією "Main Memory Page Program Through Buffer"
            number_bytes_read_write_tmp[index_chip] = size_page_serial_dataflash[index_chip];
            
            etap_writing_df[index_chip] = ETAP_WRITING_DF_MAIN_MEMORY_PROGRAM_THROUGH_BUFFER;
          }
          else
          {
            //Треба виконувати "довгий ланцюжок операцій" для запису і починається він з операції "Main Memory Page to Buffer Transfer"
            int32_t size_to_end_page = size_page_serial_dataflash[index_chip] - (address_read_write_tmp[index_chip] & (size_page_serial_dataflash[index_chip] - 1));
            if (size_to_end > size_to_end_page) number_bytes_read_write_tmp[index_chip] = size_to_end_page;
            else number_bytes_read_write_tmp[index_chip] = size_to_end;
            
            etap_writing_df[index_chip] = ETAP_WRITING_DF_MAIN_MEMORY_TO_BUFFER_TRANSFER;
          }
        }
        else
        {
          //Весь масив вже записаний, тому скидаємо умову запису мікросхеми DataFlash
          number_bytes_read_write_tmp[index_chip] = 0;
          
          etap_writing_df[index_chip] = ETAP_WRITING_DF_NONE;
        }
      }
      
      uint32_t number_transmit;
      
      switch (etap_writing_df[index_chip])
      {
      case ETAP_WRITING_DF_NONE:
        {
          //Треба завершити процедуру запису
          _CLEAR_STATE(control_spi_df_tasks[index_chip], TASK_WRITING_SERIAL_DATAFLASH_BIT);
          break;
        }
      case ETAP_WRITING_DF_MAIN_MEMORY_PROGRAM_THROUGH_BUFFER:
        {
          //Треба записати у пам'ять мікросхеми через буфер
          
          int32_t base_index = (address_read_write_tmp[index_chip] - address_read_write[index_chip]);
          if (
              ((base_index + size_page_serial_dataflash[index_chip]) > SIZE_BUFFER_SERIAL_DATAFLASH_READ_WRITE) ||
              (base_index < 0)  
             )   
          {
            //Відбулася невизначена помилка, тому треба піти на перезавантаження
            total_error_sw_fixed(9);
          }

          uint32_t address_internal = address_read_write_tmp[index_chip] & (number_page_serial_dataflash[index_chip]*size_page_serial_dataflash[index_chip] - 1);
          
          TxBuffer_SPI_DF[0] = CODE_OPERATION_WRITE_PAGE_THROUGH_BUFFER;
          TxBuffer_SPI_DF[1] = (address_internal >> 16) & 0xff; //старший байт адреси сторінки
          TxBuffer_SPI_DF[2] = (address_internal >>  8) & 0xff; //молодша байт адреси сторінки
          TxBuffer_SPI_DF[3] = (address_internal      ) & 0xff; //адреса в середині сторінки - теоретично має бути 0
          for (size_t i = 0; i < size_page_serial_dataflash[index_chip]; i++)
            TxBuffer_SPI_DF[4 + i] = buffer_serial_DataFlash_read_write[index_chip][base_index + i];
            
          number_transmit = 4 + size_page_serial_dataflash[index_chip];
          break;
        }
      case ETAP_WRITING_DF_MAIN_MEMORY_TO_BUFFER_TRANSFER:
        {
          //Треба зчитати визначену сторінку у буфер мікросхеми DataFlash 
          
          uint32_t address_internal = address_read_write_tmp[index_chip] & ((number_page_serial_dataflash[index_chip]*size_page_serial_dataflash[index_chip] - 1) & (uint32_t)(~(size_page_serial_dataflash[index_chip] - 1)));
          
          TxBuffer_SPI_DF[0] = CODE_OPERATION_READ_PAGE_INTO_BUFFER;
          TxBuffer_SPI_DF[1] = (address_internal >> 16) & 0xff; //старший байт адреси сторінки
          TxBuffer_SPI_DF[2] = (address_internal >>  8) & 0xff; //молодша байт адреси сторінки
          //Адреса в середині сторінки не має значення, але байт має піти
          
          number_transmit = 4;
          break;
        }
      case ETAP_WRITING_DF_BUFFER_WRITE:
        {
          //Треба модифікувати вмістиме буферу

          int32_t base_index = (address_read_write_tmp[index_chip] - address_read_write[index_chip]);
          if (
              ((base_index + number_bytes_read_write_tmp[index_chip]) > SIZE_BUFFER_SERIAL_DATAFLASH_READ_WRITE) ||
              (base_index < 0)  
             )
          {
            //Відбулася невизначена помилка, тому треба піти на перезавантаження
            total_error_sw_fixed(10);
          }

          uint32_t address_internal = address_read_write_tmp[index_chip] & (size_page_serial_dataflash[index_chip] - 1);
          
          TxBuffer_SPI_DF[0] = CODE_OPERATION_WRITE_BUFFER;
          TxBuffer_SPI_DF[1] = 0;                               //старший байт адреси сторінки не має значення
          TxBuffer_SPI_DF[2] = (address_internal >>  8) & 0xff; //молодша байт адреси сторінки не має значення
          TxBuffer_SPI_DF[3] = (address_internal      ) & 0xff; //адреса в середині сторінки - теоретично має бути 0
          for (size_t i = 0; i < number_bytes_read_write_tmp[index_chip]; i++)
            TxBuffer_SPI_DF[4 + i] = buffer_serial_DataFlash_read_write[index_chip][base_index + i];
            
          number_transmit = 4 + number_bytes_read_write_tmp[index_chip];
          break;
        }
      case ETAP_WRITING_DF_BUFFER_TO_MAIN_MEMORY_PROGRAM_WITH_BUIT_IN_ERASE:
        {
          //Треба записати буфер мікросхеми DataFlash у пам'ять мікросхеми DataFlash зі вказаного номеру сторінки
          
          uint32_t address_internal = address_read_write_tmp[index_chip] & ((number_page_serial_dataflash[index_chip]*size_page_serial_dataflash[index_chip] - 1) & (uint32_t)(~(size_page_serial_dataflash[index_chip] - 1)));
          
          TxBuffer_SPI_DF[0] = CODE_OPERATION_WRITE_BUFFER_INTO_MEMORY_WITH_ERASE;
          TxBuffer_SPI_DF[1] = (address_internal >> 16) & 0x01; //старший байт адреси сторінки
          TxBuffer_SPI_DF[2] = (address_internal >>  8) & 0xff; //молодша байт адреси сторінки
          //Адреса в середині сторінки не має значення, але байт має піти
          
          number_transmit = 4;
          break;
        }
      default:
        {
          //Відбулася невизначена помилка, тому треба піти на перезавантаження
          total_error_sw_fixed(8);
        }
      }

      
      if (etap_writing_df[index_chip] != ETAP_WRITING_DF_NONE)
      {
        //Запускаємо процес обміну DataFlash, якщ оє що передавати
        start_exchange_via_spi_df(index_chip, number_transmit);
      }
    }
    else if _GET_OUTPUT_STATE(control_spi_df_tasks[index_chip], TASK_READING_SERIAL_DATAFLASH_BIT)
    {
      //Стоїть умова читання мікросхеми DataFlash

      //Кількість байт до кінця буферу 
      int32_t size_to_end = number_bytes_read_write[index_chip] - (address_read_write_tmp[index_chip] - address_read_write[index_chip]); 
      
      if (size_to_end > 0)
      {
        uint32_t address_internal = address_read_write_tmp[index_chip] & (number_page_serial_dataflash[index_chip]*size_page_serial_dataflash[index_chip] - 1);
          
        TxBuffer_SPI_DF[0] = CODE_OPERATION_READ_HIGH_FREQ;
        TxBuffer_SPI_DF[1] = (address_internal >> 16) & 0x01; //старший байт адреси сторінки
        TxBuffer_SPI_DF[2] = (address_internal >>  8) & 0xff; //молодша байт адреси сторінки
        TxBuffer_SPI_DF[3] = (address_internal      ) & 0xff; //адреса в середині сторінки
        //Після адреси має іти один додатковй байт як буфер перед початком отримування реальних даних

        if ((uint32_t)(size_to_end + 5) <= SIZE_BUFFER_SERIAL_DATAFLASH_DMA) number_bytes_read_write_tmp[index_chip] = size_to_end;
        else number_bytes_read_write_tmp[index_chip] = (SIZE_BUFFER_SERIAL_DATAFLASH_DMA - 5);
        
        //Запускаємо процес читання з DataFlash
        start_exchange_via_spi_df(index_chip, (5 + number_bytes_read_write_tmp[index_chip]));
      }
      else
      {
        //Весь масив вже зчитаний, тому скидаємо умову читання мікросхеми DataFlash
        _CLEAR_STATE(control_spi_df_tasks[index_chip], TASK_READING_SERIAL_DATAFLASH_BIT);
      }
    }
    else if _GET_OUTPUT_STATE(control_spi_df_tasks[index_chip], TASK_START_MAKE_PAGE_SIZE_256_BIT)
    {
      //Скидаємо біт початку переведення мікросхеми до розміру сторінки у 256 байт і виставляємо біт переведення мікросхеми до розміру сторінки у 256 байт з бітом читання регістру статусу
      _SET_STATE(control_spi_df_tasks[index_chip], TASK_READ_SR_DF_BIT);
      _SET_STATE(control_spi_df_tasks[index_chip], TASK_MAKING_PAGE_SIZE_256_BIT);
      _CLEAR_STATE(control_spi_df_tasks[index_chip], TASK_START_MAKE_PAGE_SIZE_256_BIT);
    }
    else if _GET_OUTPUT_STATE(control_spi_df_tasks[index_chip], TASK_START_ERASE_DATAFLASH_BIT)
    {
      //Скидаємо біт початку стирання всієї мікросхеми DataFlash і виставляємо біт стирання мікросхеми DataFlash з бітом читання регістру статусу
      _SET_STATE(control_spi_df_tasks[index_chip], TASK_READ_SR_DF_BIT);
      _SET_STATE(control_spi_df_tasks[index_chip], TASK_ERASING_DATAFLASH_BIT);
      _CLEAR_STATE(control_spi_df_tasks[index_chip], TASK_START_ERASE_DATAFLASH_BIT);
    }
    else if _GET_OUTPUT_STATE(control_spi_df_tasks[index_chip], TASK_START_WRITE_SERIAL_DATAFLASH_BIT)
    {
//      /*****/
//      //Тільки для відладки
//      /*****/
//      for(unsigned int i = 0; i < number_bytes_read_write[index_chip]; i++)
//        buffer_serial_DataFlash_read_write[i] = (i + 1) & 0xff;
//      /*****/

      //Визначаємо адресу у мікросхемі DataFlash з якої треба почати записувати
      address_read_write_tmp[index_chip] = address_read_write[index_chip];
      //Помічаємо, що на даний момент ще не іде ніякий запис
      number_bytes_read_write_tmp[index_chip] = 0;
      //Помічаємо, що операція запису невизначена
      etap_writing_df[index_chip] = ETAP_WRITING_DF_NONE;
      
      //Скидаємо біт початку запису мікросхеми DataFlash і виставляємо біт запису мікросхеми DataFlash з бітом читання регістру статусу
      _SET_STATE(control_spi_df_tasks[index_chip], TASK_READ_SR_DF_BIT);
      _SET_STATE(control_spi_df_tasks[index_chip], TASK_WRITING_SERIAL_DATAFLASH_BIT);
      _CLEAR_STATE(control_spi_df_tasks[index_chip], TASK_START_WRITE_SERIAL_DATAFLASH_BIT);
    }
    else if _GET_OUTPUT_STATE(control_spi_df_tasks[index_chip], TASK_START_READ_SERIAL_DATAFLASH_BIT)
    {
      //Визначаємо адресу у мікросхемі DataFlash з якої треба почати читання
      address_read_write_tmp[index_chip] = address_read_write[index_chip];
      //Помічаємо, що на даний момент ще не іде ніяке зчитування
      number_bytes_read_write_tmp[index_chip] = 0;
      
      //Скидаємо біт початку читання мікросхеми DataFlash і виставляємо біт читання мікросхеми DataFlash з бітом читання регістру статусу
      _SET_STATE(control_spi_df_tasks[index_chip], TASK_READ_SR_DF_BIT);
      _SET_STATE(control_spi_df_tasks[index_chip], TASK_READING_SERIAL_DATAFLASH_BIT);
      _CLEAR_STATE(control_spi_df_tasks[index_chip], TASK_START_READ_SERIAL_DATAFLASH_BIT);
    }
    /*************************************************/
  }
  else if (state_execution_spi_df[index_chip] == TRANSACTION_EXECUTED_WAIT_ANALIZE)
  {
    /*************************************************/
    //Обмін завершився без помилок
    /*************************************************/

    //Виставляємо повідомлення, що SPI_DF готовий до нової транзакції 
    state_execution_spi_df[index_chip] = TRANSACTION_EXECUTING_NONE;

    if _GET_OUTPUT_STATE(control_spi_df_tasks[index_chip], TASK_READ_SR_DF_BIT)
    {
      //Цей блок має бути завжди першим після читання регістру статусу EEPROM, щоб коли іде перевірка на доступність запису не виконувалися помилковоінші задачі
      
      status_register_df[index_chip] = RxBuffer_SPI_DF[1 + 0];

      //Прочитано ресістр статусу
      if ((status_register_df[index_chip] & (1 << 7)) != 0)
      {
        //Мікросхема DataFlash не є у стані "BUSY"
        _CLEAR_STATE(control_spi_df_tasks[index_chip], TASK_READ_SR_DF_BIT);
      }
      else
      {
        //Інакше виконуємо повторно ту саму опрецію, поки Мікросхема DataFlash не перейде у стан "BUSY"
      }
    }
    else if _GET_OUTPUT_STATE(control_spi_df_tasks[index_chip], TASK_MAKING_PAGE_SIZE_256_BIT)
    {
      //Завершився процес переводу мікросхеми DataFlash на розмір сторінки у 256 байт

      //Виставляємо біт повторного читання регістру статусу мікросхеми DataFlash
      _SET_STATE(control_spi_df_tasks[index_chip], TASK_READ_SR_DF_BIT);

      //Скидаємо біт запуску переводу мікросхеми DataFlash не розмір сторінки у 256 байт
      _CLEAR_STATE(control_spi_df_tasks[index_chip], TASK_MAKING_PAGE_SIZE_256_BIT);
    }
    else if _GET_OUTPUT_STATE(control_spi_df_tasks[index_chip], TASK_ERASING_DATAFLASH_BIT)
    {
      //Завершився процес стирання мікросхеми DataFlash

      //Скидаємо біт стирання мікросхеми DataFlash
      _CLEAR_STATE(control_spi_df_tasks[index_chip], TASK_ERASING_DATAFLASH_BIT);
    }
    else if _GET_OUTPUT_STATE(control_spi_df_tasks[index_chip], TASK_WRITING_SERIAL_DATAFLASH_BIT)
    {
      //Завершився етап процесу запису інформації, визначеної змінною  number_bytes_read_write_tmp[index_chip], в мікросхему DataFlash
      
      if (
          (etap_writing_df[index_chip] == ETAP_WRITING_DF_MAIN_MEMORY_PROGRAM_THROUGH_BUFFER              ) ||
          (etap_writing_df[index_chip] == ETAP_WRITING_DF_BUFFER_TO_MAIN_MEMORY_PROGRAM_WITH_BUIT_IN_ERASE)
         ) 
      {
        //Завершилася операція запису порції інформації у пам'ять мікросхеми DataFlash

        //Збільшуємо адресу з якої, можливо, треба буде продовжити читання
        address_read_write_tmp[index_chip] += number_bytes_read_write_tmp[index_chip];
        
        //Помічаємо. що треба підготувати нову порцію інформації для запису
        etap_writing_df[index_chip] = ETAP_WRITING_DF_NONE;
      }
      else if (
               (etap_writing_df[index_chip] == ETAP_WRITING_DF_NONE                                            ) ||
               (etap_writing_df[index_chip] >  ETAP_WRITING_DF_BUFFER_TO_MAIN_MEMORY_PROGRAM_WITH_BUIT_IN_ERASE)  
              )   
      {
        //Відбулася невизначена помилка, тому треба піти на перезавантаження
        total_error_sw_fixed(11);
      }
      else
      {
        //Переходимо на наступний етап запису порції інформації визнаеної змінною  number_bytes_read_write_tmp[index_chip]
        etap_writing_df[index_chip]++;
      }

      //Виставляємо біт повторного читання регістру статусу мікросхеми DataFlash
      _SET_STATE(control_spi_df_tasks[index_chip], TASK_READ_SR_DF_BIT);
    }
    else if _GET_OUTPUT_STATE(control_spi_df_tasks[index_chip], TASK_READING_SERIAL_DATAFLASH_BIT)
    {
      //Завершився процес читання інформації, визнаеної змінною  number_bytes_read_write_tmp[index_chip], з мікросхеми DataFlash
      
      //Копіюємо отриману інформацію
      int32_t base_index = (address_read_write_tmp[index_chip] - address_read_write[index_chip]);
      if (
          ((base_index + number_bytes_read_write_tmp[index_chip]) > SIZE_BUFFER_SERIAL_DATAFLASH_READ_WRITE) ||
          (base_index < 0)  
         )   
      {
        //Відбулася невизначена помилка, тому треба піти на перезавантаження
        total_error_sw_fixed(7);
      }
      for(size_t i = 0; i < number_bytes_read_write_tmp[index_chip]; i++)
        buffer_serial_DataFlash_read_write[index_chip][base_index + i] = RxBuffer_SPI_DF[5 + i];
      
      //Збільшуємо адресу з якої, можливо, треба буде продовжити читання
      address_read_write_tmp[index_chip] += number_bytes_read_write_tmp[index_chip];

      //Виставляємо біт повторного читання регістру статусу мікросхеми DataFlash
      _SET_STATE(control_spi_df_tasks[index_chip], TASK_READ_SR_DF_BIT);
    }
    else
    {
      //Сюди, теоретично, ніколи не мала б дійти
      //У всіх інакших випадках нічого не робимо
    }
    /*************************************************/
  }
  else if (state_execution_spi_df[index_chip] == TRANSACTION_EXECUTED_ERROR)
  {
    /*************************************************/
    //Обмін завершився з помилкою
    /*************************************************/

    //Виставляємо повідомлення, що I2C готовий до нової транзакції 
    state_execution_spi_df[index_chip] = TRANSACTION_EXECUTING_NONE;

    //Визначаємося з наступними діями
    if _GET_OUTPUT_STATE(control_spi_df_tasks[index_chip], TASK_READ_SR_DF_BIT)
    {
      //Читається регістр статусу мікросхеми DataFlash 
      
      //Повторно читаємо регістр статусу мікросхеми DataFlash  
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
        //Виконується процес запис інформації в мікросхему DataFlash
      
        //Переводимо етап запису порції інформації (визнаеної змінною  number_bytes_read_write_tmp[index_chip]) у початковий стан
        etap_writing_df[index_chip] = ETAP_WRITING_DF_NONE;
      }
      
      //Виставляємо біт повторного читання регістру статусу мікросхеми DataFlash
      _SET_STATE(control_spi_df_tasks[index_chip], TASK_READ_SR_DF_BIT);
    }
    else
    {
      //У всіх інакших випадках нічого не робимо
    }
    /*************************************************/
  }
}
/*****************************************************/

/*****************************************************/
//
/*****************************************************/
/*****************************************************/
