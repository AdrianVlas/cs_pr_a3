#include "header.h"

#define BACKLIGHTING_ON         1
#define BACKLIGHTING_OFF        300

uint32_t time_backlighting =    BACKLIGHTING_ON*100;

/*****************************************************/
//Перевірка на помилки у процесі транзакції черз I2C
/*****************************************************/
inline ErrorStatus check_errors_i2c(void)
{
   if (I2C_GetFlagStatus(I2C, I2C_FLAG_TIMEOUT | I2C_FLAG_OVR | I2C_FLAG_AF | I2C_FLAG_ARLO | I2C_FLAG_BERR))
   {
     I2C_ClearFlag(I2C, I2C_FLAG_TIMEOUT | I2C_FLAG_OVR | I2C_FLAG_AF | I2C_FLAG_ARLO | I2C_FLAG_BERR);
     return ERROR;
   }
   else return SUCCESS;
}
/*****************************************************/

/*****************************************************/
//Перевірка стану кнопки
/*****************************************************/
inline void check_state_key(GPIO_TypeDef* GPIOx, uint16_t mask_bit, unsigned int number_bit)
{
  if((time_set_keyboard[number_bit] == 0) && ((new_state_keyboard & (1<< number_bit)) == 0))
  {
    //Кнопка до цього моменту не була зафіксована, що вона натиснута
    if (GPIO_ReadInputDataBit(GPIOx, mask_bit) == RESET) time_set_keyboard[number_bit]++;
  }
  else if((time_set_keyboard[number_bit] > 0) && (time_set_keyboard[number_bit] < DEREVIACIA))
  {
    //Перевіряємо чи пройшов час очікування, і якщо стан кнопки підтверджується, то виставляємо повідомлення. що кнопка натиснута, алеще не оброблена
    if(++time_set_keyboard[number_bit] == DEREVIACIA)
    {
      if (GPIO_ReadInputDataBit(GPIOx, mask_bit) == RESET) new_state_keyboard |= 1<< number_bit;
      else time_set_keyboard[number_bit] = 0;
    }
  }
  else
  {
    if (time_set_keyboard[number_bit] != 0)
    {
      //Перевіряємо чи кнопка вже відтиснута
     if (GPIO_ReadInputDataBit(GPIOx, mask_bit) != RESET) time_set_keyboard[number_bit] = 0;
    }
  }
}
/*****************************************************/

/*****************************************************/
//Переривання від I2C
/*****************************************************/
void I2C_EV_IRQHandler(void)
{
#ifdef SYSTEM_VIEWER_ENABLE
  SEGGER_SYSVIEW_RecordEnterISR();
#endif
  
  switch (I2C_GetLastEvent(I2C))
  {
  case I2C_EVENT_MASTER_MODE_SELECT:                 /* EV5 */
    {
      if((driver_i2c.action == 0) || (driver_i2c.action == 2))
      {
        /* Посилаємо EEPROM адресу для запису */
        I2C->DR = (uint8_t)(driver_i2c.device_id & ((uint8_t)(~I2C_OAR1_ADD0)));
      }
      else
      {
        /* Посилаємо EEPROM адресу для читання */
        I2C->DR = (uint8_t)(driver_i2c.device_id | I2C_OAR1_ADD0);
      }
      break;
    }
  case I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED:  /* EV6 */
    {
      //Зупиняємо генерацію переривань від подій
      I2C->CR2 &= (uint16_t)((~(uint32_t)I2C_IT_EVT) & 0xffff);
      
      //Помилки не зафіксовані
      unsigned int number_transmit_with_i2c;
      if(driver_i2c.action == 0)
      {
        //Підготовлюємо буфер для передачі в мікросхему для запису (адреса)
        if (driver_i2c.device_id == EEPROM_ADDRESS)
        {
          //Внутрішня адреса для EEPROM сттановить 2 байти
          Temporaty_I2C_Buffer[0] = ((driver_i2c.internal_address & 0xFF00) >> 8);
          Temporaty_I2C_Buffer[1] = (driver_i2c.internal_address & 0x00FF);
          number_transmit_with_i2c = 2;
        }
        else
        {
          //Внутрішня адреса для RTC сттановить 1 байт
          Temporaty_I2C_Buffer[0] = (driver_i2c.internal_address & 0x00FF);
          number_transmit_with_i2c = 1;
        }
      }
      else if(driver_i2c.action == 2)
      {
        //Підготовлюємо буфер для передачі в мікросхему для запису (адреса + корисні дані)
        if (driver_i2c.device_id == EEPROM_ADDRESS)
        {
          //Запис корисних байт іде разом із двома байтами внутрішньої адреси для EEPROM
          Temporaty_I2C_Buffer[0] = ((driver_i2c.internal_address & 0xFF00) >> 8);
          Temporaty_I2C_Buffer[1] = (driver_i2c.internal_address & 0x00FF);
          for (unsigned int i= 0; i < driver_i2c.number_bytes; i++)
          {
            Temporaty_I2C_Buffer[2 + i] = *(driver_i2c.point_buffer + i);
          }
          number_transmit_with_i2c = 2 + driver_i2c.number_bytes;
        }
        else
        {
          //Запис корисних байт іде разом із одним байтами внутрішньої адреси для RTC
          Temporaty_I2C_Buffer[0] = (driver_i2c.internal_address & 0x00FF);
          for (unsigned int i= 0; i < driver_i2c.number_bytes; i++)
          {
            Temporaty_I2C_Buffer[1 + i] = *(driver_i2c.point_buffer + i);
          }
          number_transmit_with_i2c = 1 + driver_i2c.number_bytes;
        }
      }
        
      //Зупиняємо потік DMA якщо він запущений
      if ((DMA_StreamI2C_Tx->CR & (uint32_t)DMA_SxCR_EN) !=0) DMA_StreamI2C_Tx->CR &= ~(uint32_t)DMA_SxCR_EN;
      DMA_StreamI2C_Tx->M0AR = (uint32_t)Temporaty_I2C_Buffer;
      DMA_StreamI2C_Tx->NDTR = number_transmit_with_i2c;
        
      /* Set Last bit to have a NACK on the last received byte */
      I2C->CR2 |= I2C_CR2_LAST;
          
      //Очищаємо всі події по DMA_FLAG_GLI2C_Tx
      DMA_ClearFlag(DMA_StreamI2C_Tx, DMA_FLAG_TCI2C_Tx | DMA_FLAG_HTI2C_Tx | DMA_FLAG_TEII2C_Tx | DMA_FLAG_DMEII2C_Tx | DMA_FLAG_FEII2C_Tx);
        
      //Дозволяємо генерацію переривань від потоку DMA1_ChannelI2C_TX
      DMA_StreamI2C_Tx->CR |= DMA_IT_TC;

      /* Дозволяємо для I2C передачу по DMA */
      I2C->CR2 |= I2C_CR2_DMAEN;

      /* Дозволяємо DMA_StreamI2C_Tx */
      DMA_StreamI2C_Tx->CR |= (uint32_t)DMA_SxCR_EN;
      
      break;
    }
  case I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED:
    {
      //Зупиняємо генерацію переривань від подій
      I2C->CR2 &= (uint16_t)((~(uint32_t)I2C_IT_EVT) & 0xffff);
      
      if (driver_i2c.number_bytes != 1)
      {
        //Якщо читання буде проводитися більше ніж один байт, то читання здійснюємо через DMA_FLAG_GLI2C_Rx
          
        //Зупиняємо потік DMA якщо він запущений
        if ((DMA_StreamI2C_Rx->CR & (uint32_t)DMA_SxCR_EN) !=0) DMA_StreamI2C_Rx->CR &= ~(uint32_t)DMA_SxCR_EN;
        DMA_StreamI2C_Rx->M0AR = (uint32_t)driver_i2c.point_buffer;
        DMA_StreamI2C_Rx->NDTR = driver_i2c.number_bytes;
        
        //Очищаємо всі події по DMA_FLAG_GLI2C_Rx
        DMA_ClearFlag(DMA_StreamI2C_Rx, DMA_FLAG_TCI2C_Rx | DMA_FLAG_HTI2C_Rx | DMA_FLAG_TEII2C_Rx | DMA_FLAG_DMEII2C_Rx | DMA_FLAG_FEII2C_Rx);
        
        //Дозволяэмо генерацыю переривань від потоку DMA1_ChannelI2C_RX
        DMA_StreamI2C_Rx->CR |= DMA_IT_TC;

        /* Дозволяємо для I2C передачу по DMA */
        I2C->CR2 |= I2C_CR2_DMAEN;

        /* Дозволяємо DMA1_ChannelI2C_RX */
        DMA_StreamI2C_Rx->CR |= (uint32_t)DMA_SxCR_EN;
      }
      else
      {
        //Читання буде проходити тільки одного байту без DMA_FLAG_GLI2C_Rx
         
        I2C->CR1 &= (uint16_t)(~I2C_CR1_ACK);
        I2C->CR1 |= I2C_CR1_STOP;

        /* Дозволяємо для I2C генерацію переривань по подіях і прийятому новому байту*/
        I2C->CR2 |= I2C_IT_EVT | I2C_IT_BUF;
      }

      break;
    }
  case I2C_EVENT_MASTER_BYTE_RECEIVED_NO_BUSY:
    {
      /* Забороняємо для I2C генерацію переривань по подіях і прийятому новому байту*/
      I2C->CR2 &= (uint16_t)~(I2C_IT_EVT | I2C_IT_BUF);
      *driver_i2c.point_buffer = (uint8_t)I2C->DR;

      //Повідомляємо, що читання завершився
      driver_i2c.state_execution = 1;
      break;
    }
  default: 
    {
      break;
    }
  }
  
#ifdef SYSTEM_VIEWER_ENABLE
  SEGGER_SYSVIEW_RecordExitISR();
#endif
}
/*****************************************************/

/*****************************************************/
//Генерація переривань від помилки під час обміну по I2C
/*****************************************************/
void I2C_ER_IRQHandler(void)
{
#ifdef SYSTEM_VIEWER_ENABLE
  SEGGER_SYSVIEW_RecordEnterISR();
#endif
  
  I2C->CR1 |= I2C_CR1_STOP;
  
  //Зупиняємо потоки DMA якщо вони запущені
  if ((DMA_StreamI2C_Tx->CR & (uint32_t)DMA_SxCR_EN) !=0) DMA_StreamI2C_Tx->CR &= ~(uint32_t)DMA_SxCR_EN;
  if ((DMA_StreamI2C_Rx->CR & (uint32_t)DMA_SxCR_EN) !=0) DMA_StreamI2C_Rx->CR &= ~(uint32_t)DMA_SxCR_EN;
  
  check_errors_i2c();
  
  type_error_of_exchanging_via_i2c |= (1<<ERROR_FIX_ERRORS_BIT);
  driver_i2c.state_execution = 2;
  
#ifdef SYSTEM_VIEWER_ENABLE
  SEGGER_SYSVIEW_RecordExitISR();
#endif
}
/*****************************************************/


/*****************************************************/
//Перереривання від завершення передачі DMA_StreamI2C_Tx
/*****************************************************/
void DMA_StreamI2C_Tx_IRQHandler(void)
{
#ifdef SYSTEM_VIEWER_ENABLE
  SEGGER_SYSVIEW_RecordEnterISR();
#endif

  //Забороняємо генерацію переривань від потоку DMA_StreamI2C_Tx
  DMA_StreamI2C_Tx->CR &= ~DMA_IT_TC;
  
  //Зупиняємо потік DMA
  DMA_StreamI2C_Tx->CR &= ~(uint32_t)DMA_SxCR_EN;
  DMA_StreamI2C_Tx->NDTR = 0;
  
  /* Забороняємо для I2C передачу по DMA */
  I2C->CR2 &= (uint16_t)(~I2C_CR2_DMAEN);

  /* Очищаємо прапореці, що сигналізує про завершення передачі даних для DMA1 по потоку I2C_TX */
  DMA_ClearFlag(DMA_StreamI2C_Tx, DMA_FLAG_TCI2C_Tx | DMA_FLAG_HTI2C_Tx | DMA_FLAG_TEII2C_Tx | DMA_FLAG_DMEII2C_Tx | DMA_FLAG_FEII2C_Tx);
  
  //Чекаємо, поки останній байт успішно переасться
  while (I2C_GetFlagStatus(I2C, I2C_FLAG_BTF) == RESET);

  if (driver_i2c.action == 0)
  {
    //Переходимо в режим зчитування
    driver_i2c.action = 1;
    /* Посилаємо RESTART умову */
    I2C->CR1 |= I2C_CR1_START;
    /* Дозволяємо для I2C генерацію переривань по подіях */
    I2C->CR2 |= I2C_IT_EVT;
  }
  else if (driver_i2c.action == 2)
  {
    /* Посилаємо STOP умову */
    I2C->CR1 |= I2C_CR1_STOP;
    //Повідомляємо, що запис завершився
    driver_i2c.state_execution = 1;
  }
  
#ifdef SYSTEM_VIEWER_ENABLE
  SEGGER_SYSVIEW_RecordExitISR();
#endif
}
/*****************************************************/

/*****************************************************/
//Перереривання від завершення передачі DMA_StreamI2C_Rx
/*****************************************************/
void DMA_StreamI2C_Rx_IRQHandler(void)
{
#ifdef SYSTEM_VIEWER_ENABLE
  SEGGER_SYSVIEW_RecordEnterISR();
#endif

  //Забороняємо генерацію переривань від потоку DMA_StreamI2C_Rx
  DMA_StreamI2C_Rx->CR &= ~DMA_IT_TC;
  
  //Зупиняємо потік DMA
  DMA_StreamI2C_Rx->CR &= ~(uint32_t)DMA_SxCR_EN;
  DMA_StreamI2C_Rx->NDTR = 0;
  
  /* Забороняємо для I2C передачу по DMA */
  I2C->CR2 &= (uint16_t)(~I2C_CR2_DMAEN);

  /* Очищаємо прапореці, що сигналізує про завершення передачі даних для DMA1 по каналу I2C_TX */
  DMA_ClearFlag(DMA_StreamI2C_Rx, DMA_FLAG_TCI2C_Rx | DMA_FLAG_HTI2C_Rx | DMA_FLAG_TEII2C_Rx | DMA_FLAG_DMEII2C_Rx | DMA_FLAG_FEII2C_Rx);
  
  /* Посилаємо STOP умову */
  I2C->CR1 |= I2C_CR1_STOP;
  //Повідомляємо, що читання завершився
  driver_i2c.state_execution = 1;
  
#ifdef SYSTEM_VIEWER_ENABLE
  SEGGER_SYSVIEW_RecordExitISR();
#endif
}
/*****************************************************/

/*****************************************************/
//Переривання від таймеру TIM5, який обслуговує вимірювальну систему
/*****************************************************/
void TIM5_IRQHandler(void)
{
#ifdef SYSTEM_VIEWER_ENABLE
  SEGGER_SYSVIEW_RecordEnterISR();
#endif
  
  if (TIM_GetITStatus(TIM5, TIM_IT_CC1) != RESET)
  {
    /***********************************************************************************************/
    //Переривання відбулося вік каналу 1, який генерує переривання для початку зчитування даних з АЦП
    /***********************************************************************************************/
    TIM5->SR = (uint16_t)((~(uint32_t)TIM_IT_CC1) & 0xffff); //TIM5->SR скидується для виходу з переривання
    uint32_t current_tick = previous_tick_VAL = TIM5->CCR1;
    
    /*
    Виставляємо повідослення пор необхідність оцифрувати канали групи 1 
    для розрахунку ортогональних складових
    */
    adc_DATA_VAL_read = true;
    /*
    Виставляємо повідослення про необхідність оцифрувати каналів тестових значень
    */
    adc_TEST_VAL_read = true;
    
    /***********************************************************/
    //Встановлюємо "значення лічильника для наступного переривання"
    /***********************************************************/
    uint32_t capture_new;
    unsigned int delta;
    TIM5->CCR1 = (capture_new = (current_tick + (delta = TIM5_CCR1_VAL)));
    
    unsigned int repeat;
    unsigned int previous_tick;
    do
    {
      repeat = 0;
      current_tick = TIM5->CNT;

      uint32_t delta_time = 0;
      if (capture_new < current_tick)
      { 
        uint64_t delta_time_64 = capture_new + 0x100000000 - current_tick;
        delta_time = delta_time_64;
      }
      else delta_time = capture_new - current_tick;

      if ((delta_time > delta) || (delta_time == 0))
      {
        if (TIM_GetITStatus(TIM5, TIM_IT_CC1) == RESET)
        {
          if (delta < TIM5_CCR1_VAL)
          {
            uint32_t delta_tick;
            if (current_tick < previous_tick)
            {
              uint64_t delta_tick_64 = current_tick + 0x100000000 - previous_tick;
              delta_tick = delta_tick_64;
            }
            else delta_tick = current_tick - previous_tick;
              
            delta = delta_tick + 1;
          }
          else if (delta == TIM5_CCR1_VAL)
            delta = 1; /*Намагаємося, щоб нове переивання запустилося як омога скоріше*/
          else
          {
            //Теоретично цього ніколи не мало б бути
            total_error_sw_fixed(75);
          }
          TIM5->CCR1 = (capture_new = (TIM5->CNT +  delta));
          previous_tick = current_tick;
          repeat = 0xff;
        }
      }
    }
    while (repeat != 0);
    /***********************************************************/

    /***********************************************************/
    //Виставляємо повідомлення про те, що почато оцифровку групи віимірювань 1 для перетворення Фур'є
    /***********************************************************/
    control_word_of_watchdog |= WATCHDOG_MEASURE_START_ALL_VAL;
    /***********************************************************/
    /***********************************************************************************************/
  }
  
  //Подальші дії виконуємо тільки тоді, коли зараз не іде обмін
  if (
      ((GPIO_SPI_ADC->ODR & GPIO_NSSPin_ADC) != 0) &&
      (semaphore_adc_irq == false)  
     )   
  {
    /*
    Це є умовою на цьому місці (переривання від таймеру має вищий пріоритет
    ніж перериванні від SPI) не ведеться зчитування значень з АЦП або їх обробка
    */
    control_reading_ADCs();
  }
  
#ifdef SYSTEM_VIEWER_ENABLE
  SEGGER_SYSVIEW_RecordExitISR();
#endif
}
/*****************************************************/

/*****************************************************/
//Переривання від таймеру TIM4, який обслуговує інтерфейси, клавіатуру і DataFlash
/*****************************************************/
void TIM4_IRQHandler(void)
{
#ifdef SYSTEM_VIEWER_ENABLE
  SEGGER_SYSVIEW_RecordEnterISR();
#endif
  
  if (TIM_GetITStatus(TIM4, TIM_IT_CC3) != RESET)
  {
    /***********************************************************************************************/
    //Переривання відбулося вік каналу 3, який генерує переривання з періодом, який визначений настройками, для очікування наступного символа по RS-485
    /***********************************************************************************************/
    TIM4->SR = (uint16_t)((~(uint32_t)TIM_IT_CC3) & 0xffff);
    uint16_t current_tick = TIM4->CNT;

    //Знімаємо мітку, що на останньому перериванні відбулася фіксація прийняття цілого фрейму
    mark_current_tick_RS_485 = 0;

    /******/
    //Перевіряємо інтерфейс RS-485 тільки коли запущений DMA для прийому, бо інакше стоїть умова аналізу прийнятого пакету
    /******/
    if ((DMA_StreamRS485_Rx->CR & (uint32_t)DMA_SxCR_EN) !=0)
    {
      RxBuffer_RS485_count = BUFFER_RS485 - (uint16_t)(DMA_StreamRS485_Rx->NDTR);
      current_tick = TIM4->CNT; /*фіксуємо час, коли ми зафіксували кількість прийнятих байт відносно якого будемо визначати новий час генерації переривання*/
    
      if( RxBuffer_RS485_count != 0 )
      {
        /***
        Тест роботи RS-485 (приймається новий пакет)
        ***/
        test_answer_RS485 = 0;
        reason_of_restart_RS485 = 0;
        /***/
        
        if (RxBuffer_RS485_count_previous == RxBuffer_RS485_count)
        {
          //Прийнятий цілий фрейм

          //Зупиняємо потік DMA
          if ((DMA_StreamRS485_Rx->CR & (uint32_t)DMA_SxCR_EN) !=0) DMA_StreamRS485_Rx->CR &= ~(uint32_t)DMA_SxCR_EN;

          //Зчитуємо можливі помилки і перевіряємо, чи вони присутні
          unsigned int error_status = USART_RS485->SR &  (USART_FLAG_ORE | USART_FLAG_NE | USART_FLAG_FE | USART_FLAG_PE);
          if (error_status == 0)
          {
            //Помилок немає
            
            //Перевіряємо адресу
            unsigned int global_requect;
            if(
               ((global_requect = (RxBuffer_RS485[0] == BROADCAST_ADDRESS_MODBUS_RTU)) != 0) ||
               (RxBuffer_RS485[0] == settings_fix_prt.address)
              )   
            {
              /***
              Тест роботи RS-485 (прийнято успішно пакет)
              ***/
              test_answer_RS485 |= (1 << 0);
              /***/

              //Інакше прийнятий пакет буде стояти в очікуванні на подальшу обробку - якщо не виконувати більше тут ніяких дій (не перезапускати моніторинг)

              if (global_requect == 0) time_last_receive_byte = TIM4->CNT;

              //Встановлюємо мітку, що на останньому перериванні відбулася фіксація прийняття цілого фрейму
              mark_current_tick_RS_485 = 0xff;
            }
            else
            {
              /***
              Причина рестарту (не співпала адреса 1)
              ***/
              reason_of_restart_RS485 |= (1 << 1);
              /***/
              
              //Адреса не співпадає - відновити моніторинг лінії
              restart_monitoring_RS485();
            }
          }
          else
          {
            /***
            Причина рестарту (помилки при передачі)
            ***/
            reason_of_restart_RS485 |= (1 << 2);
            /***/
              
            //Зафіксовані помилки  - відновити моніторинг лінії
            restart_monitoring_RS485();
          }
        }
        else
        {
          //Фрейм на стадії прийому
          RxBuffer_RS485_count_previous = RxBuffer_RS485_count;
        }
      }
    }
    /******/

    /***********************************************************/
    //Встановлюємо "значення лічильника для наступного переривання"
    /***********************************************************/
    if (number_bits_rs_485_waiting < 10) calculate_namber_bit_waiting_for_rs_485();
    uint16_t /*current_tick = TIM4->CNT,*/ capture_new;
    unsigned int delta, step_tmp;
    TIM4->CCR3 = (capture_new = (current_tick + (delta = step_tmp =(TIM4_CCR3_VAL*number_bits_rs_485_waiting))));
    
    unsigned int repeat;
    unsigned int previous_tick;
    do
    {
      repeat = 0;
      current_tick = TIM4->CNT;

      uint32_t delta_time = 0;
      if (capture_new < current_tick)
        delta_time = capture_new + 0x10000 - current_tick;
      else delta_time = capture_new - current_tick;

      if ((delta_time > delta) || (delta_time == 0))
      {
        if (TIM_GetITStatus(TIM4, TIM_IT_CC3) == RESET)
        {
          if (delta < step_tmp)
          {
            uint32_t delta_tick;
            if (current_tick < previous_tick)
              delta_tick = current_tick + 0x10000 - previous_tick;
            else delta_tick = current_tick - previous_tick;
              
            delta = delta_tick + 1;
          }
          else if (delta == step_tmp)
            delta = 1; /*Намагаємося, щоб нове переривання запустилося як омога скоріше*/
          else
          {
            //Теоретично цього ніколи не мало б бути
            total_error_sw_fixed(78);
          }
          TIM4->CCR3 = (capture_new = (TIM4->CNT +  delta));
          previous_tick = current_tick;
          repeat = 0xff;
        }
      }
    }
    while (repeat != 0);
    /***********************************************************/

    /***********************************************************/
    //Виставляємо повідомлення про те, що канал 3 TIM4 працює, що відповідає за періодичні функції фнтерфейсу RS-485
    /***********************************************************/
    control_word_of_watchdog |= WATCHDOG_RS485;
    /***********************************************************/

    /***********************************************************************************************/
  }
  else if (TIM_GetITStatus(TIM4, TIM_IT_CC1) != RESET)
  {
    /***********************************************************************************************/
    //Переривання відбулося вік каналу 1, який генерує переривання кожні 10 мс, для опрацьовування клавіатури
    /***********************************************************************************************/
    TIM4->SR = (uint16_t)((~(uint32_t)TIM_IT_CC1) & 0xffff);
    uint16_t current_tick = TIM4->CCR1;
  
    /***********************************************************/
    //Опрцювання пінів клавіатури
    /***********************************************************/
    /***************************/
    //Перебираємо всі рядки
    /***************************/
    //Рядок - 1
    GPIO_ResetBits(KEYBOARD, KEYBOARD_SW_1_PIN);
    check_state_key(KEYBOARD_SW_A, KEYBOARD_SW_A_PIN, BIT_KEY_ENTER);
    check_state_key(KEYBOARD_SW_B, KEYBOARD_SW_B_PIN, BIT_KEY_DOWN);
    check_state_key(KEYBOARD_SW_C, KEYBOARD_SW_C_PIN, BIT_KEY_RIGHT);
    GPIO_SetBits(KEYBOARD, KEYBOARD_SW_1_PIN);
    
    //Робимо невелику затримку
    for(unsigned int delay_local = 0; delay_local < 100; delay_local++) __no_operation();
    
    //Рядок - 2
    GPIO_ResetBits(KEYBOARD, KEYBOARD_SW_2_PIN);
    check_state_key(KEYBOARD_SW_A, KEYBOARD_SW_A_PIN, BIT_KEY_ESC);
    check_state_key(KEYBOARD_SW_B, KEYBOARD_SW_B_PIN, BIT_KEY_LEFT);
    check_state_key(KEYBOARD_SW_C, KEYBOARD_SW_C_PIN, BIT_KEY_UP);
    GPIO_SetBits(KEYBOARD, KEYBOARD_SW_2_PIN);

    //Робимо невелику затримку
    for(unsigned int delay_local = 0; delay_local < 100; delay_local++) __no_operation();

    //Рядок - 3
    GPIO_ResetBits(KEYBOARD, KEYBOARD_SW_3_PIN);
    check_state_key(KEYBOARD_SW_A, KEYBOARD_SW_A_PIN, BIT_KEY_1);
    check_state_key(KEYBOARD_SW_B, KEYBOARD_SW_B_PIN, BIT_KEY_2);
    GPIO_SetBits(KEYBOARD, KEYBOARD_SW_3_PIN);

    //Робимо невелику затримку
    for(unsigned int delay_local = 0; delay_local < 100; delay_local++) __no_operation();

    //Рядок - 4
    GPIO_ResetBits(KEYBOARD, KEYBOARD_SW_4_PIN);
    check_state_key(KEYBOARD_SW_A, KEYBOARD_SW_A_PIN, BIT_KEY_MUTE);
    check_state_key(KEYBOARD_SW_B, KEYBOARD_SW_B_PIN, BIT_KEY_RESET);
    check_state_key(KEYBOARD_SW_C, KEYBOARD_SW_C_PIN, BIT_KEY_TEST);
    GPIO_SetBits(KEYBOARD, KEYBOARD_SW_4_PIN);
    /***************************/
  
    uint32_t  maska_all_keys = (uint32_t)(
                                          (1<<BIT_KEY_ENTER) |
                                          (1<<BIT_KEY_DOWN) |
                                          (1<<BIT_KEY_RIGHT) |
                                          (1<<BIT_KEY_ESC) |
                                          (1<<BIT_KEY_LEFT) |
                                          (1<<BIT_KEY_UP) |
                                          (1<<BIT_KEY_MUTE) |
                                          (1<<BIT_KEY_RESET) |
                                          (1<<BIT_KEY_TEST) |
                                          (1<<BIT_KEY_1) |
                                          (1<<BIT_KEY_2)
                                         );
    if ((LCD_BL->ODR & LCD_BL_PIN) != (uint32_t)Bit_RESET)
    {
      //Підсвітка ввімкнута
      if ((new_state_keyboard & maska_all_keys) != 0) time_backlighting = BACKLIGHTING_OFF*100;
      if (
           (time_backlighting > 0) && /*випадок старту з викнутою підсвіткою*/
           (--time_backlighting == 0) /*закінчився час роботи приладу без підсвітки після старту приладу*/
         )
      {
        //Умова вивмкнення підсвітки
        LCD_BL->BSRRH = LCD_BL_PIN;
      }
      
    }
    else
    {
      //Підсвітка вимкнута
      if (
          ((new_state_keyboard & maska_all_keys) != 0) /*умова ввімкнення підсвітки по натискуванні кнопки*/
          ||  
          (
           (time_backlighting > 0)  && /*випадок старту з викнутою підсвіткою*/
           (--time_backlighting == 0) && /*закінчився час роботи приладу без підсвітки після старту приладу*/
           ((POWER_CTRL->IDR & POWER_CTRL_PIN) != (uint32_t)Bit_RESET) /*є оперативне живлення*/
          )   
         )
      {
        //Умова ввімкнення підсвітки після старту приладу
        LCD_BL->BSRRL = LCD_BL_PIN;
        time_backlighting = BACKLIGHTING_OFF*100;

        uint32_t  maska_wake_up_keys = (uint32_t)(
                                                  (1<<BIT_KEY_ENTER) |
                                                  (1<<BIT_KEY_DOWN) |
                                                  (1<<BIT_KEY_RIGHT) |
                                                  (1<<BIT_KEY_ESC) |
                                                  (1<<BIT_KEY_LEFT) |
                                                  (1<<BIT_KEY_UP)
                                                 );
        new_state_keyboard &= (unsigned int)(~maska_wake_up_keys);
      }
    }
  
    /***************************/
    //Обробка алгоритму функціональних кнопок
    /***************************/
    uint32_t pressed_buttons = (new_state_keyboard & ( (1<<BIT_KEY_1) | (1<<BIT_KEY_2) | (1<<BIT_KEY_MUTE) | (1<<BIT_KEY_RESET) | (1<<BIT_KEY_TEST) )) >> _NUMBER_MOVING_KEY;
    new_state_keyboard &= (unsigned int)(~( (1<<BIT_KEY_1) | (1<<BIT_KEY_2) | (1<<BIT_KEY_MUTE) | (1<<BIT_KEY_RESET) | (1<<BIT_KEY_TEST) ));

    __LN_BUTTON *p_button = (__LN_BUTTON*)(spca_of_p_prt[ID_FB_BUTTON - _ID_FB_FIRST_VAR]);
    for (uint32_t i = 0; i < current_config_prt.n_button; i++)
    {
      if ((pressed_buttons & (1 << i)) != 0)
      {
        //Зафіксовано, що кнопка зараз натиснута
        
        //Встановлюємо MUTEX
        p_button->internal_input[BUTTON_INT_MUTEX >> 3] |= (1 << (BUTTON_INT_MUTEX & ((1 << 3) - 1)));
        
        //Встановлюємо вхідну інформацію
        p_button->internal_input[BUTTON_INT_ACTIVATION >> 3] |= (1 << (BUTTON_INT_ACTIVATION & ((1 << 3) - 1)));

        //Скидаємо MUTEX
        p_button->internal_input[BUTTON_INT_MUTEX >> 3] &= (uint8_t)(~(1 << (BUTTON_INT_MUTEX & ((1 << 3) - 1))));
      }
      p_button++;
    }
    /***************************/
    /***********************************************************/
  
    /***********************************************************/
    //Перевіряємо чи треба обновляти з часом 1 с дані на екрані
    /***********************************************************/
    if (
        ((current_state_menu2.current_level == TIME_MANU2_LEVEL) && (current_state_menu2.edition <= ED_CAN_BE_EDITED)) ||
        (current_state_menu2.current_level == MEASUREMENT_MENU2_LEVEL ) ||
        (current_state_menu2.current_level == INPUTS_MENU2_LEVEL) ||
        (current_state_menu2.current_level == OUTPUTS_MENU2_LEVEL) ||
        (current_state_menu2.current_level == ANALOG_INPUTS_MENU2_LEVEL) ||
        (current_state_menu2.current_level == DIAGNOSTICS_MENU2_LEVEL) 
       )
    {
      if(++time_rewrite > MAX_TIME_REWRITE_EKRAN)
      {
        time_rewrite = 0;
        new_state_keyboard |= (1<<BIT_REWRITE);
      }
    }
    /***********************************************************/

    /***********************************************************/
    //Аналіз запуску, або розблоукування запуску періодичних задач
    /***********************************************************/
    if (_CHECK_SET_BIT(control_i2c_taskes, TASK_BLK_WRITING_EEPROM_BIT) != 0)
    {
      //Розблоковуємо запуск заблокованих задач для драйверу I2C
       _CLEAR_BIT(control_i2c_taskes, TASK_BLK_WRITING_EEPROM_BIT);
      //Остаточне розблокування відбудеться після засинхронізацією з зняття миттєвих виборок з АЦП
      _SET_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT);
    }
    /***********************************************************/

    /***********************************************************/
    //Лічильник ресурсу + періодичні операції раз у секунду
    /***********************************************************/
    static unsigned int number_ticks_for_OF_bit_reset;

    if (etap_reset_of_bit == ETAP_CLEAR_OF_ST_START_WAITING_5S)
    {
      etap_reset_of_bit = ETAP_CLEAR_OF_ST_WAITING_5S;
      number_ticks_for_OF_bit_reset = 0;
    }
    else if (etap_reset_of_bit == ETAP_CLEAR_OF_ST_WAITING_5S)
    {
      number_ticks_for_OF_bit_reset++;
      if (number_ticks_for_OF_bit_reset > 500) etap_reset_of_bit = ETAP_CLEAR_OF_WRITE_OF_0;
    }
    
    if(++number_inputs_for_fix_one_second >= 100)
    {
      
      //Запуск читання часу з RTC тільки піся успішного зчитування настройок
      //При цьому виставляємо біт блокування негайного запуску операції, щоб засинхронізуватися з роботою вимірювальної системи
      if ((state_i2c_task & MASKA_FOR_BIT(STATE_SETTINGS_EEPROM_GOOD_BIT)) != 0) 
      {
        _SET_BIT(control_i2c_taskes, TASK_START_READ_RTC_BIT);
        _SET_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT);
      }
      
      //Запусаємо раз у секунду самоконтроль важливих змінних
      periodical_tasks_TEST_CONFIG                  = 
      periodical_tasks_TEST_SETTINGS                = 
      periodical_tasks_TEST_USTUVANNJA              = 
      periodical_tasks_TEST_TRG_FUNC                = 
      periodical_tasks_TEST_INFO_REJESTRATOR_LOG    = 
      periodical_tasks_TEST_INFO_REJESTRATOR_PR_ERR = 
      periodical_tasks_TEST_FLASH_MEMORY            = true;
      
      number_inputs_for_fix_one_second = 0;
      
      if(++number_seconds >= 60)
      {
        number_seconds = 0;
        if((POWER_CTRL->IDR & POWER_CTRL_PIN) != (uint32_t)Bit_RESET)
        {
          reinit_LCD = true;
        }
      }
      
      //Робота з таймером очікування нових змін налаштувань
      if (
          (restart_timeout_idle_new_settings != 0) ||
          (_CHECK_SET_BIT(fix_block_active_state, FIX_BLOCK_SETTINGS_CHANGED) == 0) ||
          ((config_settings_modified & MASKA_FOR_BIT(BIT_MENU_LOCKS)) != 0) 
         )
      {
        timeout_idle_new_settings  = 0;
        if (restart_timeout_idle_new_settings != 0) restart_timeout_idle_new_settings = false;
      }
      else 
      { 
        if (timeout_idle_new_settings < (settings_fix_prt.timeout_idle_new_settings)) timeout_idle_new_settings++;
      }

      //Робота з таймерами простою USB
      if ((restart_timeout_interface & (1 << USB_RECUEST  )) != 0) 
      {
        timeout_idle_USB  = 0;
        restart_timeout_interface &= (unsigned int)(~(1 << USB_RECUEST));
      }
      else 
      {
        if (timeout_idle_USB < (settings_fix_prt.timeout_deactivation_password_interface_USB)) timeout_idle_USB++;
      }

      //Робота з таймерами простою RS-485
      if ((restart_timeout_interface & (1 << RS485_RECUEST)) != 0) 
      {
        timeout_idle_RS485 = 0;
        restart_timeout_interface &= (unsigned int)(~(1 << RS485_RECUEST));
      }
      else 
      {
        if (timeout_idle_RS485 < (settings_fix_prt.timeout_deactivation_password_interface_RS485)) timeout_idle_RS485++;
      }

      //Ресурс
      if (restart_resurs_count == 0)
      {
        resurs_global = resurs_temp;
        resurs_temp = 0;
        if (resurs_global < resurs_global_min) resurs_global_min = resurs_global;
        if (resurs_global > resurs_global_max) resurs_global_max = resurs_global;
      }
      else
      {
        restart_resurs_count = 0;
        
        resurs_global = 0;
        resurs_temp = 0;
        resurs_global_min = 0xffffffff;
        resurs_global_max = 0;
      }
    }
    /***********************************************************/

    /***********************************************************/
    //Корекція десятих і сотих секунд
    /***********************************************************/
    if (copying_time == 0)
    {
      //На даний момент не іде встановлення або зчитування часу

      /*
      Помічаємо, що зараз  будемо змінювати час (при цьому встановлення або
      читання з мікросхеми не може початися, бо ми у перериванні, а ці операції
      виконуються з фонового режиму; відбір же даних буде іти коректно)
      */
      copying_time = 2; 
      
      unsigned int rozrjad = 0;
      for(unsigned int i = 0; i < 7; i++)
      {
        unsigned int data_tmp = 10*((time[i] >> 4) & 0xf) + (time[i] & 0xf);
        
        unsigned int porig;
        switch (i)
        {
        case 0:
        case 6:
          {
            porig = 99;
            break;
          }
        case 1:
        case 2:
          {
            porig = 59;
            break;
          }
        case 3:
          {
            porig = 23;
            break;
          }
        case 4:
          {
            unsigned int month = 10*((time[5] >> 4) & 0xf) + (time[5] & 0xf);
            if (month == 0x2/*BCD*/)
            {
              unsigned int year = 10*((time[6] >> 4) & 0xf) + (time[6] & 0xf);
              if (
                  ((year & 0x3) == 0) && /*остача від ділення на 4*/
                  (
                   ((year % 100) != 0) /* ||
                   ((year % 400) == 0) */ /*не кратний 100 або кратний 400*/
                  )  
                 )
              {
                porig = 29;
              } 
              else
              {
                porig = 28;
              }
            }
            else if (
                     ((month <= 0x7/*BCD*/) && ( (month & 1))) ||
                     ((month >  0x7/*BCD*/) && (!(month & 1)))
                    ) 
            {
              porig = 31;
            }
            else
            {
              porig = 30;
            }
            break;
          }
        case 5:
          {
            porig = 12;
            break;
          }
        default:
          {
            //Якщо сюди дійшла програма, значить відбулася недопустива помилка, тому треба зациклити програму, щоб вона пішла на перезагрузку
            total_error_sw_fixed(14);
          }
        }
        
        if ((++data_tmp) > porig)
        {
          rozrjad = 1;
          
          if ((i == 4) || (i == 5)) data_tmp = 1;
          else data_tmp = 0;
        }
        else rozrjad = 0;
        
        unsigned int high = data_tmp / 10;
        unsigned int low = data_tmp - high*10;
        time[i] = (high << 4) | low;
        
        if (rozrjad == false) break;
      }

      copying_time = 1; 
      
      for(unsigned int i = 0; i < 7; i++) time_copy[i] = time[i];
      
      copying_time = 0; 
    }
    /***********************************************************/

    /***********************************************************/
    //Встановлюємо "значення лічильника для наступного переривання"
    /***********************************************************/
    uint16_t capture_new;
    unsigned int delta;
    TIM4->CCR1 = (capture_new = (current_tick + (delta = TIM4_CCR1_VAL)));
    
    unsigned int repeat;
    unsigned int previous_tick;
    do
    {
      repeat = 0;
      current_tick = TIM4->CNT;

      uint32_t delta_time = 0;
      if (capture_new < current_tick)
        delta_time = capture_new + 0x10000 - current_tick;
      else delta_time = capture_new - current_tick;

      if ((delta_time > delta) || (delta_time == 0))
      {
        if (TIM_GetITStatus(TIM4, TIM_IT_CC1) == RESET)
        {
          if (delta < TIM4_CCR1_VAL)
          {
            uint32_t delta_tick;
            if (current_tick < previous_tick)
              delta_tick = current_tick + 0x10000 - previous_tick;
            else delta_tick = current_tick - previous_tick;
              
            delta = delta_tick + 1;
          }
          else if (delta == TIM4_CCR1_VAL)
            delta = 1; /*Намагаємося, щоб нове переивання запустилося як омога скоріше*/
          else
          {
            //Теоретично цього ніколи не мало б бути
            total_error_sw_fixed(79);
          }
          TIM4->CCR1 = (capture_new = (TIM4->CNT +  delta));
          previous_tick = current_tick;
          repeat = 0xff;
        }
      }
    }
    while (repeat != 0);
    /***********************************************************/

    /***********************************************************/
    //Виставляємо повідомлення про те, що канал 1 TIM4, що відповідає за періодичні функції клавіатури працює
    /***********************************************************/
    control_word_of_watchdog |= WATCHDOG_KYYBOARD;
    /***********************************************************/
    /***********************************************************************************************/
  }
  else if (TIM_GetITStatus(TIM4, TIM_IT_CC2) != RESET)
  {
    /***********************************************************************************************/
    //Переривання відбулося вік каналу 2, який генерує переривання кожні 1 мс, для опраціьовування управління мікросхемами DataFlash і формування нових записів реєстратора програмних подій
    /***********************************************************************************************/
    TIM4->SR = (uint16_t)((~(uint32_t)TIM_IT_CC2) & 0xffff);
    uint16_t current_tick = TIM4->CCR2;
    
    /***********************************************************/
    //Перевіряємо необхідність очистки реєстратора програмних подій
    /***********************************************************/
    if (
        ((clean_rejestrators & MASKA_FOR_BIT(CLEAN_PR_ERR_BIT)) != 0)
        &&  
        (
         (control_tasks_dataflash & (
                                     MASKA_FOR_BIT(TASK_WRITE_PR_ERR_RECORDS_INTO_DATAFLASH_BIT   ) |
                                     MASKA_FOR_BIT(TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_USB_BIT  ) |
                                     MASKA_FOR_BIT(TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_RS485_BIT) |
                                     MASKA_FOR_BIT(TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_MENU_BIT )
                                    )
         ) == 0
        )
       )   
    {
      //Виставлено каманда очистити реєстратор програмних подій

      //Виставляємо команду запису цієї структури у EEPROM
      _SET_BIT(control_i2c_taskes, TASK_START_WRITE_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT);

      //Очищаємо структуру інформації по реєстраторі програмних помилок
      info_rejestrator_pr_err.next_address = info_rejestrator_pr_err.previous_address = MIN_ADDRESS_PR_ERR_AREA;
      info_rejestrator_pr_err.number_records = 0;

      //Помічаємо, що номер запису не вибраний
      number_record_of_pr_err_into_menu  = 0xffffffff;
      number_record_of_pr_err_into_USB   = 0xffffffff;
      number_record_of_pr_err_into_RS485 = 0xffffffff;

      //Знімаємо команду очистки реєстратора програмних подій
      clean_rejestrators &= (unsigned int)(~MASKA_FOR_BIT(CLEAN_PR_ERR_BIT));
    }
    /***********************************************************/
    
    /***********************************************************/
    //Підготовлюємо новий запис для реєстратора програмних подій
    /***********************************************************/
    changing_diagnostyka_state();
    /***********************************************************/
    
    /***********************************************************/
    //Перевірка на необхідність зроботи резервну копію даних для самоконтролю
    /***********************************************************/
    //Реєстратор програмних подій
    if (periodical_tasks_TEST_INFO_REJESTRATOR_PR_ERR != 0)
    {
      //Стоїть у черзі активна задача зроботи резервні копії даних
      if ((state_i2c_task & MASKA_FOR_BIT(STATE_INFO_REJESTRATOR_PR_ERR_EEPROM_GOOD_BIT)) != 0)
      {
        //Робимо копію тільки тоді, коли структура інформації реєстратора успішно зчитана і сформована контрольна сума
        if (
            (_CHECK_SET_BIT(control_i2c_taskes, TASK_START_WRITE_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT) == 0) &&
            (_CHECK_SET_BIT(control_i2c_taskes, TASK_WRITING_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT    ) == 0) &&
            (_CHECK_SET_BIT(control_i2c_taskes, TASK_START_READ_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT ) == 0) &&
            (_CHECK_SET_BIT(control_i2c_taskes, TASK_READING_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT    ) == 0)
           ) 
        {
          //На даний моммент не іде читання-запис структури інформації реєстратора, тому можна здійснити копіювання
          info_rejestrator_pr_err_ctrl = info_rejestrator_pr_err;
          crc_info_rejestrator_pr_err_ctrl = crc_info_rejestrator_pr_err;

          //Скидаємо активну задачу формування резервної копії 
          periodical_tasks_TEST_INFO_REJESTRATOR_PR_ERR = false;
          //Виставляємо активну задачу контролю достовірності по резервній копії 
          periodical_tasks_TEST_INFO_REJESTRATOR_PR_ERR_LOCK = true;
        }
      }
      else
      {
        //Скидаємо активну задачу формування резервної копії 
        periodical_tasks_TEST_INFO_REJESTRATOR_PR_ERR = false;
      }
    }
    /***********************************************************/

    /***********************************************************/
    //Періодично запускаємо звертання то мікросхем DataFlash
    /***********************************************************/
    uint32_t number_chip_dataflash_exchange_local = number_chip_dataflash_exchange;
    if (number_chip_dataflash_exchange_local < NUMBER_DATAFLASH_CHIP)
    {
      if (state_execution_spi_df[number_chip_dataflash_exchange_local] != TRANSACTION_EXECUTING)
      {
        //Немає обміну по вибраній мікросехмі
        
        //Змінюємо номер мікросхеми, до якої ми будемо звертатися при натупних трансакціях, якщо зараз не запущена ніяка трансакція
        number_chip_dataflash_exchange_local = number_chip_dataflash_exchange = (number_chip_dataflash_exchange_local < (NUMBER_DATAFLASH_CHIP - 1)) ? (number_chip_dataflash_exchange_local++) : INDEX_DATAFLASH_1;

        if (control_spi_df_tasks[number_chip_dataflash_exchange_local] != 0) main_routines_for_spi_df(number_chip_dataflash_exchange_local);
        
        if (control_spi_df_tasks[number_chip_dataflash_exchange_local] == 0)
        {
          static uint32_t control_tasks_dataflash_active;
          /***
          Оброка трансакцій, які вже були запущені
          ***/
          switch (number_chip_dataflash_exchange_local)
          {
          case INDEX_DATAFLASH_1:
            {
              if ((control_tasks_dataflash_active & (MASKA_FOR_BIT(_SEPARATOR_BIT_TASKS_DATADLASH1_AND_TASKS_DATADLASH2) - 1)) != 0)
              {
                if ((control_tasks_dataflash_active & MASKA_FOR_BIT(TASK_ERASE_DATAFLASH_1_BIT)) != 0)
                {
                  //Покищо ця опреція є реалізованою, але не використовується

                  /***
                  Скидаємо команду стирання DataFlash1
                  ***/
                  _CLEAR_STATE(control_tasks_dataflash_active, TASK_ERASE_DATAFLASH_1_BIT);
                  _CLEAR_STATE(control_tasks_dataflash       , TASK_ERASE_DATAFLASH_1_BIT);
                  /***/
                }
                else if ((control_tasks_dataflash_active & TASK_FOR_LOG) != 0)
                {
                  //Дії над Журналом подій
                  if ((control_tasks_dataflash_active & MASKA_FOR_BIT(TASK_WRITE_LOG_RECORDS_INTO_DATAFLASH_BIT)) != 0)
                  {
                    /***
                    Виставляємо команду запису структури Журналу подій у EEPROM
                    ***/
                    _SET_BIT(control_i2c_taskes, TASK_START_WRITE_INFO_REJESTRATOR_LOG_EEPROM_BIT);
                    info_rejestrator_log.previous_address = info_rejestrator_log.next_address;
                    /***/

                    /***
                    Скидаємо команду запису даних у DataFlash
                    ***/
                    _CLEAR_STATE(control_tasks_dataflash_active, TASK_WRITE_LOG_RECORDS_INTO_DATAFLASH_BIT);
                    _CLEAR_STATE(control_tasks_dataflash       , TASK_WRITE_LOG_RECORDS_INTO_DATAFLASH_BIT);
                    /***/
                  }
                  else
                  {
                    uint8_t *point_buffer = NULL;
                    
                    if ((control_tasks_dataflash_active & MASKA_FOR_BIT(TASK_MAMORY_READ_DATAFLASH_FOR_LOG_MENU_BIT )) != 0) point_buffer = buffer_for_menu_read_record;
                    else if ((control_tasks_dataflash_active & MASKA_FOR_BIT(TASK_MAMORY_READ_DATAFLASH_FOR_LOG_USB_BIT )) != 0) point_buffer = buffer_for_USB_read_record_log;
                    else if ((control_tasks_dataflash_active & MASKA_FOR_BIT(TASK_MAMORY_READ_DATAFLASH_FOR_LOG_RS485_BIT )) != 0) point_buffer = buffer_for_RS485_read_record_log;
                    
                    if (point_buffer != NULL)
                    {
                      for (size_t i = 0; i < SIZE_ONE_RECORD_LOG; i++) point_buffer[i] = buffer_serial_DataFlash_read_write[INDEX_DATAFLASH_1][i];

                      /***
                      Скидаємо команду читання даних з DataFlash
                      
                      Так як і робота з верхнім рівнем і з меню ведеться на найнижчому пріоритеті, то за умови очікування зчитування даних не може бути одночасно виставлено команду читати для різних джерел
                      ***/
                      control_tasks_dataflash_active &= (uint32_t)(~(MASKA_FOR_BIT(TASK_MAMORY_READ_DATAFLASH_FOR_LOG_MENU_BIT ) | MASKA_FOR_BIT(TASK_MAMORY_READ_DATAFLASH_FOR_LOG_USB_BIT ) |  MASKA_FOR_BIT(TASK_MAMORY_READ_DATAFLASH_FOR_LOG_RS485_BIT )));
                      control_tasks_dataflash        &= (uint32_t)(~(MASKA_FOR_BIT(TASK_MAMORY_READ_DATAFLASH_FOR_LOG_MENU_BIT ) | MASKA_FOR_BIT(TASK_MAMORY_READ_DATAFLASH_FOR_LOG_USB_BIT ) |  MASKA_FOR_BIT(TASK_MAMORY_READ_DATAFLASH_FOR_LOG_RS485_BIT )));
                      /***/
                    }
                  } 
                }
                else
                {
                  //Дії над Реєстратором програмних подій
                  if ((control_tasks_dataflash_active & MASKA_FOR_BIT(TASK_WRITE_PR_ERR_RECORDS_INTO_DATAFLASH_BIT)) != 0)
                  {
                    /***
                    Виставляємо команду запису структури реєстратора програмних подій у EEPROM
                    ***/
                    _SET_BIT(control_i2c_taskes, TASK_START_WRITE_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT);
                    info_rejestrator_pr_err.previous_address = info_rejestrator_pr_err.next_address;
                    /***/

                    /***
                    Скидаємо команду запису даних у DataFlash
                    ***/
                    _CLEAR_STATE(control_tasks_dataflash_active, TASK_WRITE_PR_ERR_RECORDS_INTO_DATAFLASH_BIT);
                    _CLEAR_STATE(control_tasks_dataflash       , TASK_WRITE_PR_ERR_RECORDS_INTO_DATAFLASH_BIT);
                    /***/
                  }
                  else
                  {
                    uint8_t *point_buffer = NULL;
                    
                    if ((control_tasks_dataflash_active & MASKA_FOR_BIT(TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_MENU_BIT )) != 0) point_buffer = buffer_for_menu_read_record;
                    else if ((control_tasks_dataflash_active & MASKA_FOR_BIT(TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_USB_BIT )) != 0) point_buffer = buffer_for_USB_read_record_pr_err;
                    else if ((control_tasks_dataflash_active & MASKA_FOR_BIT(TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_RS485_BIT )) != 0) point_buffer = buffer_for_RS485_read_record_pr_err;
                    
                    if (point_buffer != NULL)
                    {
                      for (size_t i = 0; i < SIZE_ONE_RECORD_PR_ERR; i++) point_buffer[i] = buffer_serial_DataFlash_read_write[INDEX_DATAFLASH_1][i];

                      /***
                      Скидаємо команду читання даних з DataFlash
                      
                      Так як і робюота з верхнім рівнем і з меню ведеться на найнижчому пріоритеті. то за умови очікування зчитування даних не може бути одночасно виставлено команду читати для різних джерел
                      ***/
                      control_tasks_dataflash_active &= (uint32_t)(~(MASKA_FOR_BIT(TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_MENU_BIT ) | MASKA_FOR_BIT(TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_USB_BIT ) |  MASKA_FOR_BIT(TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_RS485_BIT )));
                      control_tasks_dataflash        &= (uint32_t)(~(MASKA_FOR_BIT(TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_MENU_BIT ) | MASKA_FOR_BIT(TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_USB_BIT ) |  MASKA_FOR_BIT(TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_RS485_BIT )));
                      /***/
                    }
                  } 
                }
              }
              break;
            }
          case INDEX_DATAFLASH_2:
            {
              if ((control_tasks_dataflash_active & (uint32_t)(~(MASKA_FOR_BIT(_SEPARATOR_BIT_TASKS_DATADLASH1_AND_TASKS_DATADLASH2) - 1))) != 0)
              {
                if ((control_tasks_dataflash_active & MASKA_FOR_BIT(TASK_ERASE_DATAFLASH_2_BIT)) != 0)
                {
                  //Покищо ця опреція є реалізованою, але не використовується

                  /***
                  Скидаємо команду стирання DataFlash2
                  ***/
                  _CLEAR_STATE(control_tasks_dataflash_active, TASK_ERASE_DATAFLASH_2_BIT);
                  _CLEAR_STATE(control_tasks_dataflash       , TASK_ERASE_DATAFLASH_2_BIT);
                  /***/
                }
              }
              break;
            }
          }
          /***/
          
          /***
          Підготовлюємо  нові трансакції по необхідності
          ***/
          switch (number_chip_dataflash_exchange_local)
          {
          case INDEX_DATAFLASH_1:
            {
              /***
              Підготовка нових записів для запису у Журнал подій
              ***/
              uint32_t head = head_fifo_buffer_log_records, tail = tail_fifo_buffer_log_records;
              if ((POWER_CTRL->IDR & POWER_CTRL_PIN) != (uint32_t)Bit_RESET) /*На даний момент на вході блоку живлення подається живлення*/ 
              {
                if (head != tail) _SET_STATE(control_tasks_dataflash, TASK_WRITE_LOG_RECORDS_INTO_DATAFLASH_BIT);  //Є нові записи у буфері подій  
              }
              /***/
              if ((control_tasks_dataflash & (
                                               MASKA_FOR_BIT(TASK_WRITE_LOG_RECORDS_INTO_DATAFLASH_BIT   ) |
                                               MASKA_FOR_BIT(TASK_MAMORY_READ_DATAFLASH_FOR_LOG_USB_BIT  ) |
                                               MASKA_FOR_BIT(TASK_MAMORY_READ_DATAFLASH_FOR_LOG_RS485_BIT) |
                                               MASKA_FOR_BIT(TASK_MAMORY_READ_DATAFLASH_FOR_LOG_MENU_BIT )
                                              )) != 0)
              {
                //Дії над Журналом подій
                if ((control_tasks_dataflash & MASKA_FOR_BIT(TASK_WRITE_LOG_RECORDS_INTO_DATAFLASH_BIT)) != 0)
                {
                  //Початок запису нових записів у Журнал подій
                  
                  /***
                  Виставляємо активну задачу запису записів Журналу подій
                  ***/
                  _SET_STATE(control_tasks_dataflash_active, TASK_WRITE_LOG_RECORDS_INTO_DATAFLASH_BIT);                  
                  /***/
                  
                  /***
                  Виставляємо команди: запису даних у DataFlash і запису структури Журналу подій у EEPROM
                  ***/
                  _SET_BIT(control_i2c_taskes, TASK_START_WRITE_INFO_REJESTRATOR_LOG_EEPROM_BIT);
                  _SET_STATE(control_spi_df_tasks[INDEX_DATAFLASH_1], TASK_START_WRITE_SERIAL_DATAFLASH_BIT);
                  /***/
                  
                  /***
                  Визначаємо адресу з якої треба записувати
                  ***/
                  address_read_write[INDEX_DATAFLASH_1] = info_rejestrator_log.next_address;
                  /***/

                  /***
                  Визначаємо кількість байт для запису
                  ***/
                  number_bytes_read_write[INDEX_DATAFLASH_1] = 0;
                  /***/
                    
                  size_t i = 0;
                  while (
                         (head != tail) &&
                         ((i + SIZE_ONE_RECORD_LOG) <= SIZE_BUFFER_SERIAL_DATAFLASH_READ_WRITE)  
                        )   
                  {
                    /***
                    Визначаємо індекс у масиві буферу Журналу подій з якого треба почати заповнювати дані
                    ***/
                    uint32_t index_into_buffer_log = (tail++)*SIZE_ONE_RECORD_LOG;
                    while (tail >= MAX_NUMBER_RECORDS_LOG_INTO_BUFFER) tail -= MAX_NUMBER_RECORDS_LOG_INTO_BUFFER;
                    /***/
                    
                    /***
                    Копіюємо дані для запису
                    ***/
                    for (size_t j = 0; j < SIZE_ONE_RECORD_LOG; j++ ) buffer_serial_DataFlash_read_write[INDEX_DATAFLASH_1][i++] = buffer_log_records[index_into_buffer_log++];
                    /***/
                    
                    /***
                    Визначаємо кількість байт для запису
                    ***/
                    number_bytes_read_write[INDEX_DATAFLASH_1] += SIZE_ONE_RECORD_LOG;
                    /***/

                    /***
                    Визначаємо кількість записів у Реєстраторі програмних подій
                    ***/
                    if (info_rejestrator_log.number_records < MAX_NUMBER_RECORDS_INTO_LOG) info_rejestrator_log.number_records++;
                    /***/
                    
                    /***
                    Визначаємо наступну адресу з якої треба буде записувати
                    ***/
                    info_rejestrator_log.next_address += SIZE_ONE_RECORD_LOG;
                    if (info_rejestrator_log.next_address > MAX_ADDRESS_LOG_AREA_WORK) 
                    {
                      info_rejestrator_log.next_address = MIN_ADDRESS_LOG_AREA;
                      
                      //Треба припинити заповнювати буфер, записвати пфідготовлені значення, а аж потім продовжити  знову записувати незаписані дані
                      break;
                    }
                    /***/
                  }
                  tail_fifo_buffer_log_records = tail;
                }
                else
                {
                  //Початок читання записів з Журналу подій
                  uint32_t number_record = 0xffffffff;
                  if ((control_tasks_dataflash & MASKA_FOR_BIT(TASK_MAMORY_READ_DATAFLASH_FOR_LOG_MENU_BIT )) != 0) 
                  {
                    /***
                    Виставляємо активну задачу читання запису Журналу подій для меню
                    ***/
                    _SET_STATE(control_tasks_dataflash_active, TASK_MAMORY_READ_DATAFLASH_FOR_LOG_MENU_BIT);                  
                    /***/
                    number_record = number_record_of_log_into_menu;
                  }
                  else if ((control_tasks_dataflash & MASKA_FOR_BIT(TASK_MAMORY_READ_DATAFLASH_FOR_LOG_USB_BIT )) != 0) 
                  {
                    /***
                    Виставляємо активну задачу читання запису Журналу подій для USB
                    ***/
                    _SET_STATE(control_tasks_dataflash_active, TASK_MAMORY_READ_DATAFLASH_FOR_LOG_USB_BIT);                  
                    /***/
                    number_record = number_record_of_log_into_USB;
                  }
                  else if ((control_tasks_dataflash & MASKA_FOR_BIT(TASK_MAMORY_READ_DATAFLASH_FOR_LOG_RS485_BIT )) != 0) 
                  {
                    /***
                    Виставляємо активну задачу читання запису Журналу подій для RS485
                    ***/
                    _SET_STATE(control_tasks_dataflash_active, TASK_MAMORY_READ_DATAFLASH_FOR_LOG_RS485_BIT);                  
                    /***/
                    number_record = number_record_of_log_into_RS485;
                  }
                  
                  if (number_record < info_rejestrator_log.number_records)
                  {
                    uint32_t address_1 = info_rejestrator_log.next_address;
                    int32_t address_2 = address_1 - (number_record + 1)*SIZE_ONE_RECORD_LOG;
                    while  (address_2 < MIN_ADDRESS_LOG_AREA) address_2 += SIZE_LOG_AREA - (SIZE_LOG_AREA % SIZE_ONE_RECORD_LOG);

                    /***
                    Визначаємо адресу з якої треба зчитувати
                    ***/
                    address_read_write[INDEX_DATAFLASH_1] = (uint32_t)address_2;
                    /***/

                    /***
                    Визначаємо кількість байт для зчитування
                    ***/
                    number_bytes_read_write[INDEX_DATAFLASH_1] = SIZE_ONE_RECORD_LOG;
                    /***/

                    /***
                    Виставляємо команду читання даних з DataFlash
                    ***/
                    _SET_STATE(control_spi_df_tasks[INDEX_DATAFLASH_1], TASK_START_READ_SERIAL_DATAFLASH_BIT);
                    /***/
                  }
                  else
                  {
                    //Думаю, що це є нереальна ситуація
                    uint8_t *point_buffer = NULL;
                    
                    if ((control_tasks_dataflash & MASKA_FOR_BIT(TASK_MAMORY_READ_DATAFLASH_FOR_LOG_MENU_BIT )) != 0) point_buffer = buffer_for_menu_read_record;
                    else if ((control_tasks_dataflash & MASKA_FOR_BIT(TASK_MAMORY_READ_DATAFLASH_FOR_LOG_USB_BIT )) != 0) point_buffer = buffer_for_USB_read_record_log;
                    else if ((control_tasks_dataflash & MASKA_FOR_BIT(TASK_MAMORY_READ_DATAFLASH_FOR_LOG_RS485_BIT )) != 0) point_buffer = buffer_for_RS485_read_record_log;
                    
                    if (point_buffer != NULL)
                    {
                      for (size_t i = 0; i < SIZE_ONE_RECORD_LOG; i++) point_buffer[i] = 0;
                    }

                    /***
                    Скидаємо команду читання даних з DataFlash
                      
                    Так як і робюота з верхнім рівнем і з меню ведеться на найнижчому пріоритеті, то за умови очікування зчитування даних не може бути одночасно виставлено команду читати для різних джерел
                    ***/
                    control_tasks_dataflash_active &= (uint32_t)(~(MASKA_FOR_BIT(TASK_MAMORY_READ_DATAFLASH_FOR_LOG_MENU_BIT ) | MASKA_FOR_BIT(TASK_MAMORY_READ_DATAFLASH_FOR_LOG_USB_BIT ) |  MASKA_FOR_BIT(TASK_MAMORY_READ_DATAFLASH_FOR_LOG_RS485_BIT )));
                    control_tasks_dataflash        &= (uint32_t)(~(MASKA_FOR_BIT(TASK_MAMORY_READ_DATAFLASH_FOR_LOG_MENU_BIT ) | MASKA_FOR_BIT(TASK_MAMORY_READ_DATAFLASH_FOR_LOG_USB_BIT ) |  MASKA_FOR_BIT(TASK_MAMORY_READ_DATAFLASH_FOR_LOG_RS485_BIT )));
                    /***/
                  }
                }
                
                //Вихід після запуску дій по роботі з Журналом подій
                break;
              }
              
              /***
              Підготовка нових записів для запису у Реєстратор програмних подій
              ***/
              head = head_fifo_buffer_pr_err_records, tail = tail_fifo_buffer_pr_err_records;
              if (
                  /***
                  Перший раз вже зчитаний час з моменту перезапуску
                  ***/
                  (diagnostyka     != NULL) &&
                  (set_diagnostyka != NULL) &&
                  (_CHECK_SET_BIT(    diagnostyka, EVENT_START_SYSTEM_BIT       ) == 0) &&
                  (_CHECK_SET_BIT(set_diagnostyka, EVENT_START_SYSTEM_BIT       ) == 0) &&
                  (_CHECK_SET_BIT(    diagnostyka, EVENT_RESTART_SYSTEM_BIT     ) == 0) &&
                  (_CHECK_SET_BIT(set_diagnostyka, EVENT_RESTART_SYSTEM_BIT     ) == 0) &&
                  (_CHECK_SET_BIT(    diagnostyka, EVENT_SOFT_RESTART_SYSTEM_BIT) == 0) &&
                  (_CHECK_SET_BIT(set_diagnostyka, EVENT_SOFT_RESTART_SYSTEM_BIT) == 0) &&
                  /***/
                  ((POWER_CTRL->IDR & POWER_CTRL_PIN) != (uint32_t)Bit_RESET) && /*На даний момент на вході блоку живлення подається живлення*/ 
                  /***/
                  (temporary_block_writing_records_pr_err_into_DataFlash     == 0) /*Блокування запису підготовлених записів реєстратора програмних подій у мікросхему DataFlash1*/
                )
              {
                if (head != tail) _SET_STATE(control_tasks_dataflash, TASK_WRITE_PR_ERR_RECORDS_INTO_DATAFLASH_BIT);  //Є нові записи у буфері подій  
              }
              /***/
              if ((control_tasks_dataflash & (
                                               MASKA_FOR_BIT(TASK_WRITE_PR_ERR_RECORDS_INTO_DATAFLASH_BIT   ) |
                                               MASKA_FOR_BIT(TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_USB_BIT  ) |
                                               MASKA_FOR_BIT(TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_RS485_BIT) |
                                               MASKA_FOR_BIT(TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_MENU_BIT )
                                              )) != 0)
              {
                //Дії над реєстратором програмних подій
                if ((control_tasks_dataflash & MASKA_FOR_BIT(TASK_WRITE_PR_ERR_RECORDS_INTO_DATAFLASH_BIT)) != 0)
                {
                  //Початок запису нових записів у Реєстратор програмних подій
                  
                  /***
                  Виставляємо активну задачу запису записів Реєстратора програмних подій
                  ***/
                  _SET_STATE(control_tasks_dataflash_active, TASK_WRITE_PR_ERR_RECORDS_INTO_DATAFLASH_BIT);                  
                  /***/
                  
                  /***
                  Виставляємо команди: запису даних у DataFlash і запису структури реєстратора програмних подій у EEPROM
                  ***/
                  _SET_BIT(control_i2c_taskes, TASK_START_WRITE_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT);
                  _SET_STATE(control_spi_df_tasks[INDEX_DATAFLASH_1], TASK_START_WRITE_SERIAL_DATAFLASH_BIT);
                  /***/
                  
                  /***
                  Визначаємо адресу з якої треба записувати
                  ***/
                  address_read_write[INDEX_DATAFLASH_1] = info_rejestrator_pr_err.next_address;
                  /***/

                  /***
                  Визначаємо кількість байт для запису
                  ***/
                  number_bytes_read_write[INDEX_DATAFLASH_1] = 0;
                  /***/
                    
                  size_t i = 0;
                  while (
                         (head != tail) &&
                         ((i + SIZE_ONE_RECORD_PR_ERR) <= SIZE_BUFFER_SERIAL_DATAFLASH_READ_WRITE)  
                        )   
                  {
                    /***
                    Визначаємо індекс у масиві буферу програмних помилок з якого треба почати заповнювати дані
                    ***/
                    uint32_t index_into_buffer_pr_err = (tail++)*SIZE_ONE_RECORD_PR_ERR;
                    while (tail >= MAX_NUMBER_RECORDS_PR_ERR_INTO_BUFFER) tail -= MAX_NUMBER_RECORDS_PR_ERR_INTO_BUFFER;
                    /***/
                    
                    /***
                    Копіюємо дані для запису
                    ***/
                    for (size_t j = 0; j < SIZE_ONE_RECORD_PR_ERR; j++ ) buffer_serial_DataFlash_read_write[INDEX_DATAFLASH_1][i++] = buffer_pr_err_records[index_into_buffer_pr_err++];
                    /***/
                    
                    /***
                    Визначаємо кількість байт для запису
                    ***/
                    number_bytes_read_write[INDEX_DATAFLASH_1] += SIZE_ONE_RECORD_PR_ERR;
                    /***/

                    /***
                    Визначаємо кількість записів у Реєстраторі програмних подій
                    ***/
                    if (info_rejestrator_pr_err.number_records < MAX_NUMBER_RECORDS_INTO_PR_ERR) info_rejestrator_pr_err.number_records++;
                    /***/
                    
                    /***
                    Визначаємо наступну адресу з якої треба буде записувати
                    ***/
                    info_rejestrator_pr_err.next_address += SIZE_ONE_RECORD_PR_ERR;
                    if (info_rejestrator_pr_err.next_address > MAX_ADDRESS_PR_ERR_AREA_WORK) 
                    {
                      info_rejestrator_pr_err.next_address = MIN_ADDRESS_PR_ERR_AREA;
                      
                      //Треба припинити заповнювати буфер, записвати пфідготовлені значення, а аж потім продовжити  знову записувати незаписані дані
                      break;
                    }
                    /***/
                  }
                  tail_fifo_buffer_pr_err_records = tail;
                }
                else
                {
                  //Початок читання записів з Реєстратора програмних подій
                  uint32_t number_record = 0xffffffff;
                  if ((control_tasks_dataflash & MASKA_FOR_BIT(TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_MENU_BIT )) != 0) 
                  {
                    /***
                    Виставляємо активну задачу читання запису Реєстратора програмних подій для меню
                    ***/
                    _SET_STATE(control_tasks_dataflash_active, TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_MENU_BIT);                  
                    /***/
                    number_record = number_record_of_pr_err_into_menu;
                  }
                  else if ((control_tasks_dataflash & MASKA_FOR_BIT(TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_USB_BIT )) != 0) 
                  {
                    /***
                    Виставляємо активну задачу читання запису Реєстратора програмних подій для меню
                    ***/
                    _SET_STATE(control_tasks_dataflash_active, TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_USB_BIT);                  
                    /***/
                    number_record = number_record_of_pr_err_into_USB;
                  }
                  else if ((control_tasks_dataflash & MASKA_FOR_BIT(TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_RS485_BIT )) != 0) 
                  {
                    /***
                    Виставляємо активну задачу читання запису Реєстратора програмних подій для меню
                    ***/
                    _SET_STATE(control_tasks_dataflash_active, TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_RS485_BIT);                  
                    /***/
                    number_record = number_record_of_pr_err_into_RS485;
                  }
                  
                  if (number_record < info_rejestrator_pr_err.number_records)
                  {
                    uint32_t address_1 = info_rejestrator_pr_err.next_address;
                    int32_t address_2 = address_1 - (number_record + 1)*SIZE_ONE_RECORD_PR_ERR;
                    while  (address_2 < MIN_ADDRESS_PR_ERR_AREA) address_2 += SIZE_PR_ERR_AREA - (SIZE_PR_ERR_AREA % SIZE_ONE_RECORD_PR_ERR);

                    /***
                    Визначаємо адресу з якої треба зчитувати
                    ***/
                    address_read_write[INDEX_DATAFLASH_1] = (uint32_t)address_2;
                    /***/

                    /***
                    Визначаємо кількість байт для зчитування
                    ***/
                    number_bytes_read_write[INDEX_DATAFLASH_1] = SIZE_ONE_RECORD_PR_ERR;
                    /***/

                    /***
                    Виставляємо команду читання даних з DataFlash
                    ***/
                    _SET_STATE(control_spi_df_tasks[INDEX_DATAFLASH_1], TASK_START_READ_SERIAL_DATAFLASH_BIT);
                    /***/
                  }
                  else
                  {
                    //Думаю, що це є нереальна ситуація
                    uint8_t *point_buffer = NULL;
                    
                    if ((control_tasks_dataflash & MASKA_FOR_BIT(TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_MENU_BIT )) != 0) point_buffer = buffer_for_menu_read_record;
                    else if ((control_tasks_dataflash & MASKA_FOR_BIT(TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_USB_BIT )) != 0) point_buffer = buffer_for_USB_read_record_pr_err;
                    else if ((control_tasks_dataflash & MASKA_FOR_BIT(TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_RS485_BIT )) != 0) point_buffer = buffer_for_RS485_read_record_pr_err;
                    
                    if (point_buffer != NULL)
                    {
                      for (size_t i = 0; i < SIZE_ONE_RECORD_PR_ERR; i++) point_buffer[i] = 0;
                    }

                    /***
                    Скидаємо команду читання даних з DataFlash
                      
                    Так як і робюота з верхнім рівнем і з меню ведеться на найнижчому пріоритеті. то за умови очікування зчитування даних не може бути одночасно виставлено команду читати для різних джерел
                    ***/
                    control_tasks_dataflash_active &= (uint32_t)(~(MASKA_FOR_BIT(TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_MENU_BIT ) | MASKA_FOR_BIT(TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_USB_BIT ) |  MASKA_FOR_BIT(TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_RS485_BIT )));
                    control_tasks_dataflash        &= (uint32_t)(~(MASKA_FOR_BIT(TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_MENU_BIT ) | MASKA_FOR_BIT(TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_USB_BIT ) |  MASKA_FOR_BIT(TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_RS485_BIT )));
                    /***/
                  }
                }
                
                //Вихід після запуску дій по роботі з Реєстратором програмних подій
                break;
              }
              
              //Вихід якщо ні з Журналом подій, ні з Реєстратором програмних подій ніяких дій не готувалося
              break;
            }
          case INDEX_DATAFLASH_2:
            {
              break;
            }
          }
          /***/
          
          /***
          Якщо для вибраної мікросхеми є що виконувати, то виконуємо ці дії
          ***/
          if (control_spi_df_tasks[number_chip_dataflash_exchange_local] != 0) main_routines_for_spi_df(number_chip_dataflash_exchange_local);
          /***/
        }
      }
    }
    else
    {
      //Відбулася невизначена помилка, тому треба піти на перезавантаження
      total_error_sw_fixed(38);
    }
    /***********************************************************/
    
    /***********************************************************/
    //Встановлюємо "значення лічильника для наступного переривання"
    /***********************************************************/
    uint16_t /*current_tick = TIM4->CNT,*/ capture_new;
    unsigned int delta;
    TIM4->CCR2 = (capture_new = (current_tick + (delta = TIM4_CCR2_VAL)));
    
    unsigned int repeat;
    unsigned int previous_tick;
    do
    {
      repeat = 0;
      current_tick = TIM4->CNT;

      uint32_t delta_time = 0;
      if (capture_new < current_tick)
        delta_time = capture_new + 0x10000 - current_tick;
      else delta_time = capture_new - current_tick;

      if ((delta_time > delta) || (delta_time == 0))
      {
        if (TIM_GetITStatus(TIM4, TIM_IT_CC2) == RESET)
        {
          if (delta < TIM4_CCR2_VAL)
          {
            uint32_t delta_tick;
            if (current_tick < previous_tick)
              delta_tick = current_tick + 0x10000 - previous_tick;
            else delta_tick = current_tick - previous_tick;
              
            delta = delta_tick + 1;
          }
          else if (delta == TIM4_CCR2_VAL)
            delta = 1; /*Намагаємося, щоб нове переивання запустилося як омога скоріше*/
          else
          {
            //Теоретично цього ніколи не мало б бути
            total_error_sw_fixed(80);
          }
          TIM4->CCR2 = (capture_new = (TIM4->CNT +  delta));
          previous_tick = current_tick;
          repeat = 0xff;
        }
      }
    }
    while (repeat != 0);
    
    /*Vidladka*/
#ifdef DEBUG_TEST
    static unsigned int t_1, t_2, delta_tmp;
    t_1 = TIM4->CCR2;
    t_2 = TIM4->CNT;
    if (t_1 >= t_2) delta_tmp = t_1 - t_2;
    else delta_tmp = t_1 + 0xffff - t_2;
    
    if (
        (delta_tmp > TIM4_CCR2_VAL) &&
        (TIM_GetITStatus(TIM4, TIM_IT_CC2) == RESET)  
       )   
    {
      while(delta_tmp > 0);
    }
#endif
    /***/
    /***********************************************************/

    /***********************************************************/
    //Виставляємо повідомлення про те, що канал 2 TIM4, що відповідає за періодичні функції для DataFlash працює
    /***********************************************************/
    control_word_of_watchdog |= WATCHDOG_DATAFLASH;
    /***********************************************************/
    /***********************************************************************************************/
  }

#ifdef SYSTEM_VIEWER_ENABLE
  SEGGER_SYSVIEW_RecordExitISR();
#endif
}
/*****************************************************/

/*****************************************************/
//Переривання від генеррації події про помилку для SPI_DF
/*****************************************************/
void SPI_DF_IRQHandler(void)
{
#ifdef SYSTEM_VIEWER_ENABLE
  SEGGER_SYSVIEW_RecordEnterISR();
#endif

  /*
  Відбулася помилкова ситуація - треба повторно виконати попередньо виконувану трансакцію
  */
  
  /*
  Запам'ятовуємо регістр статусу, який зчитаний зразу після генерації переривання - 
  у ньому має бути зафіксована причина генерації переривання
  Цю змінну будемо використовувати при аналізі помилки
  */
  uint16_t spi_df_status = SPI_DF->SR;
  
  /*Забороняємо генерацію переривань від потоку DMA_StreamSPI_DF_Rx*/
  DMA_StreamSPI_DF_Rx->CR &= ~DMA_IT_TC;

  /*
  Можливо зараз ще продовжується робота DMA контролера по прийом/передачі даних,
  але осекільки зафіксовано помилку у процесі обміну, то зупиняємо їх
  */
  DMA_StreamSPI_DF_Tx->CR &= ~(uint32_t)DMA_SxCR_EN;
  DMA_StreamSPI_DF_Tx->NDTR = 0;
  DMA_StreamSPI_DF_Rx->CR &= ~(uint32_t)DMA_SxCR_EN;
  DMA_StreamSPI_DF_Rx->NDTR = 0;

  /*Тимчасово забороняємо переривання від помилок на SPI_DF*/
  SPI_I2S_ITConfig(SPI_DF, SPI_I2S_IT_ERR, DISABLE);

  /*
  Очікуємо поки TXE=1 і BSY=0 - це ознака повногго завершення передачі даних,
  а ознакою завершення прийому дані - це є генерація цього переривання
  */
  while ((SPI_DF->SR & SPI_I2S_FLAG_TXE) == 0);
  while ((SPI_DF->SR & SPI_I2S_FLAG_BSY) != 0);

  /*Знімаємо Chip_select переводом NSS  у 1*/
  GPIO_SPI_DF->BSRRL = GPIO_NSSPin_DF;

  if (
      ((spi_df_status & SPI_I2S_FLAG_OVR) != 0) ||
      ((SPI_DF->SR    & SPI_I2S_FLAG_OVR) != 0)
     )
  {
    //Подія про переповнення приймача
    
    do
    {
      //Очищаємо цю подією такою комбінацією читань:
      SPI_DF->DR;
      SPI_DF->SR;
    }
    while((SPI_DF->SR & SPI_I2S_FLAG_OVR) != 0);
  }

  if (
      ((spi_df_status & SPI_FLAG_MODF) != 0) ||
      ((SPI_DF->SR    & SPI_FLAG_MODF) != 0)  
     )   
  {
    //Подія "Master mode fault" - теоретично нікли не малаб виникати

    do
    {
      //Очищаємо цю подією такою комбінацією:
      SPI_DF->SR;

      //Забороняємо SPI_DF
      SPI_Cmd(SPI_DF, DISABLE);
      //Забороняємо SPI_DF DMA Tx запити
      SPI_I2S_DMACmd(SPI_DF, SPI_I2S_DMAReq_Tx, DISABLE);
      //Забороняємо SPI_DF DMA Rx запити
      SPI_I2S_DMACmd(SPI_DF, SPI_I2S_DMAReq_Rx, DISABLE);
    
      //Примусово переводимо SPI_DF у Slave-режимі
      SPI_InitTypeDef  SPI_InitStructure;
      SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
      SPI_InitStructure.SPI_Mode = SPI_Mode_Slave;
      SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
      SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
      SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
      SPI_InitStructure.SPI_NSS =  SPI_NSS_Soft;
      SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4/*SPI_BaudRatePrescaler_2*/;
      SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
      SPI_InitStructure.SPI_CRCPolynomial = 7;
      SPI_Init(SPI_DF, &SPI_InitStructure);
      //Дозволяємо SPI_DF - у Slave-режимі
      SPI_Cmd(SPI_DF, ENABLE);

      //Знову забороняємо SPI_DF для перенастройки у Master-режим
      SPI_Cmd(SPI_DF, DISABLE);
    
      //Повертаємо SPI_DF у Master-режим
      SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
      SPI_Init(SPI_DF, &SPI_InitStructure);

      //Забороняємо SPI_DF DMA Tx запити
      SPI_I2S_DMACmd(SPI_DF, SPI_I2S_DMAReq_Tx, DISABLE);
      //Забороняємо SPI_DF DMA Rx запити
      SPI_I2S_DMACmd(SPI_DF, SPI_I2S_DMAReq_Rx, DISABLE);

      //Очищаємо прапореці, що сигналізує про завершення прийом/передачі даних для DMA по потоку DMA_StreamSPI_DF_Rx і DMA_StreamSPI_DF_Tx
      DMA_ClearFlag(DMA_StreamSPI_DF_Rx, DMA_FLAG_TCSPI_DF_Rx | DMA_FLAG_HTSPI_DF_Rx | DMA_FLAG_TEISPI_DF_Rx | DMA_FLAG_DMEISPI_DF_Rx | DMA_FLAG_FEISPI_DF_Rx);
      DMA_ClearFlag(DMA_StreamSPI_DF_Tx, DMA_FLAG_TCSPI_DF_Tx | DMA_FLAG_HTSPI_DF_Tx | DMA_FLAG_TEISPI_DF_Tx | DMA_FLAG_DMEISPI_DF_Tx | DMA_FLAG_FEISPI_DF_Tx);

      //Дозволяємо SPI_DF
      SPI_Cmd(SPI_DF, ENABLE);
    }
    while ((SPI_DF->SR & SPI_FLAG_MODF) != 0);
  }

  if (
      ((spi_df_status & SPI_FLAG_CRCERR) != 0) ||
      ((SPI_DF->SR    & SPI_FLAG_CRCERR) != 0)  
     )   
  {
    //Подія "CRC error" - ніколи не мала б виникати у нашоій програмі

    //Відбулася невизначена помилка, тому треба піти на перезавантаження
    total_error_sw_fixed(34);
  }

   if (number_chip_dataflash_exchange < NUMBER_DATAFLASH_CHIP)
  {
    if(state_execution_spi_df[number_chip_dataflash_exchange] != TRANSACTION_EXECUTING_NONE)
    {
      //Помічаємо, що відбулася помилка у процесі виконання попередньої операції прийом-передачі
      state_execution_spi_df[number_chip_dataflash_exchange] = TRANSACTION_EXECUTED_ERROR;
    }
  }
  else
  {
    //Відбулася невизначена помилка, тому треба піти на перезавантаження
    total_error_sw_fixed(35);
  }
  
  /*Виставляємо повідомлення про помилку обміну через SPI_DF*/
  if (set_diagnostyka != NULL) _SET_BIT(set_diagnostyka, ERROR_SPI_DF_BIT);

  //Дозволяємо переривання від помилок на SPI_DF
  SPI_I2S_ITConfig(SPI_DF, SPI_I2S_IT_ERR, ENABLE);
  
#ifdef SYSTEM_VIEWER_ENABLE
  SEGGER_SYSVIEW_RecordExitISR();
#endif
}
/*****************************************************/
  
/*****************************************************/
//Перереривання від завершення прийому DMA_StreamSPI_DF_Rx
/*****************************************************/
void DMA_StreamSPI_DF_Rx_IRQHandler(void)
{
#ifdef SYSTEM_VIEWER_ENABLE
  SEGGER_SYSVIEW_RecordEnterISR();
#endif

  /*
  Очікуємо поки TXE=1 і BSY=0 - це ознака повногго завершення передачі даних,
  а ознакою завершення прийому дані - це є генерація цього переривання
  */
  while ((SPI_DF->SR & SPI_I2S_FLAG_TXE) == 0);
  while ((SPI_DF->SR & SPI_I2S_FLAG_BSY) != 0);

  //Знімаємо Chip_select переводом NSS  у 1
  GPIO_SPI_DF->BSRRL = GPIO_NSSPin_DF;
  
  //Зупиняємо потоки DMA
  DMA_StreamSPI_DF_Tx->CR &= ~(uint32_t)DMA_SxCR_EN;
  DMA_StreamSPI_DF_Tx->NDTR = 0;
  DMA_StreamSPI_DF_Rx->CR &= ~(uint32_t)DMA_SxCR_EN;
  DMA_StreamSPI_DF_Rx->NDTR = 0;

  //Забороняємо генерацію переривань від потоку DMA_StreamSPI_DF_Rx
  DMA_StreamSPI_DF_Rx->CR &= ~DMA_IT_TC;
  
  //Очищаємо прапореці, що сигналізує про завершення передачі даних для DMA по потоку DMA_StreamSPI_DF_Rx
  DMA_ClearFlag(DMA_StreamSPI_DF_Rx, DMA_FLAG_TCSPI_DF_Rx | DMA_FLAG_HTSPI_DF_Rx | DMA_FLAG_TEISPI_DF_Rx | DMA_FLAG_DMEISPI_DF_Rx | DMA_FLAG_FEISPI_DF_Rx);
  
  //Виставляємо повідомлення, що дані передані і готові до наступного аналізу
  if (number_chip_dataflash_exchange < NUMBER_DATAFLASH_CHIP)
    state_execution_spi_df[number_chip_dataflash_exchange] = TRANSACTION_EXECUTED_WAIT_ANALIZE;
  else
  {
    //Відбулася невизначена помилка, тому треба піти на перезавантаження
    total_error_sw_fixed(20);
  }
      
  //Обмін відбувся вдало - скидаємо повідомлення про попередньо можливу помилку обміну через SPI_DF
  if (clear_diagnostyka != NULL) _SET_BIT(clear_diagnostyka, ERROR_SPI_DF_BIT);
  
#ifdef SYSTEM_VIEWER_ENABLE
  SEGGER_SYSVIEW_RecordExitISR();
#endif
}
/*****************************************************/

/*****************************************************/
//Переривання від USART RS-485
/*****************************************************/
void USARTRS485_IRQHandler(void)
{
#ifdef SYSTEM_VIEWER_ENABLE
  SEGGER_SYSVIEW_RecordEnterISR();
#endif

  if (USART_GetITStatus(USART_RS485, USART_IT_TC) != RESET)
  {
    /***
    Тест роботи RS-485 (відправлено останній байт)
    ***/
    test_answer_RS485 |= (1 << 3);
    /***/
    
    //Переводимо мікросхкму на прийом
    GPIO_485DE->BSRRH = GPIO_PIN_485DE;

    //Забороняємо генерацію переривань при завершенні передачі байту
    USART_ITConfig(USART_RS485, USART_IT_TC, DISABLE);
      
    //Скидаємо біт, що символізує, що опстанній байт переданий
    USART_ClearFlag(USART_RS485, USART_FLAG_TC);

    //Відновлюємо моніторинг каналу RS-485 , якщо не стоїть умова реконфігурувати інтерфейс
    if (make_reconfiguration_RS_485 == 0) 
    {
      /***
      Причина рестарту (рестарт після відправки останнього байту)
      ***/
      reason_of_restart_RS485 |= (1 << 3);
      /***/
              
      restart_monitoring_RS485();
    }
  }
  
  if(USART_GetITStatus(USART_RS485, USART_IT_IDLE) != RESET)
  {
    //Зафіксовано IDLE стан
    if ((DMA_StreamRS485_Rx->CR & (uint32_t)DMA_SxCR_EN) !=0) DMA_StreamRS485_Rx->CR &= ~(uint32_t)DMA_SxCR_EN;
    USART_RS485->SR;
    (uint16_t)(USART_RS485->DR & (uint16_t)0x01FF);

    // Очищаємо прапореці, що сигналізує про завершення передачі даних для DMA1 по каналу RS-485_RX 
    DMA_ClearFlag(DMA_StreamRS485_Rx, DMA_FLAG_TCRS485_Rx | DMA_FLAG_HTRS485_Rx | DMA_FLAG_TEIRS485_Rx | DMA_FLAG_DMEIRS485_Rx | DMA_FLAG_FEIRS485_Rx);
    uint32_t NDTR_tmp = DMA_StreamRS485_Rx->NDTR;
    DMA_StreamRS485_Rx->NDTR = NDTR_tmp;
    DMA_StreamRS485_Rx->CR |= (uint32_t)DMA_SxCR_EN;
  }

  if(USART_GetITStatus(USART_RS485, USART_IT_LBD) != RESET)
  {
    //Зафіксовано Break стан
    USART_ClearFlag(USART_RS485, USART_FLAG_LBD);
  }

  unsigned int error_status = USART_RS485->SR &  (USART_FLAG_ORE | USART_FLAG_NE | USART_FLAG_FE | USART_FLAG_PE);
  if (error_status != 0)
/*    
  if(
     (USART_GetITStatus(USART_RS485, USART_IT_PE  ) != RESET) ||
     (USART_GetITStatus(USART_RS485, USART_IT_NE  ) != RESET) ||
     (USART_GetITStatus(USART_RS485, USART_IT_FE  ) != RESET) ||
     (USART_GetITStatus(USART_RS485, USART_IT_ORE ) != RESET)
    )
*/    
  {
    //Зафіксовано помилку під час прийому - перезапускаємо прийом через DMA
    if ((DMA_StreamRS485_Rx->CR & (uint32_t)DMA_SxCR_EN) !=0) DMA_StreamRS485_Rx->CR &= ~(uint32_t)DMA_SxCR_EN;
    USART_RS485->SR;
    (uint16_t)(USART_RS485->DR & (uint16_t)0x01FF);
    // Очищаємо прапореці, що сигналізує про завершення передачі даних для DMA1 по каналу RS-485_RX 
    DMA_ClearFlag(DMA_StreamRS485_Rx, DMA_FLAG_TCRS485_Rx | DMA_FLAG_HTRS485_Rx | DMA_FLAG_TEIRS485_Rx | DMA_FLAG_DMEIRS485_Rx | DMA_FLAG_FEIRS485_Rx);
    DMA_StreamRS485_Rx->NDTR = BUFFER_RS485;
    RxBuffer_RS485_count_previous = 0;
    RxBuffer_RS485_count = 0;
    DMA_StreamRS485_Rx->CR |= (uint32_t)DMA_SxCR_EN;
  }
  
#ifdef SYSTEM_VIEWER_ENABLE
  SEGGER_SYSVIEW_RecordExitISR();
#endif
}
/*****************************************************/

/*****************************************************/
//Переривання від завершення передачі даних через DMA потоку DMA_StreamRS485_Tx
/*****************************************************/
void DMA_StreamRS485_Tx_IRQHandler(void)
{
#ifdef SYSTEM_VIEWER_ENABLE
  SEGGER_SYSVIEW_RecordEnterISR();
#endif

  /***
  Тест роботи RS-485 (передані всі дані через DMA)
  ***/
  test_answer_RS485 |= (1 << 2);
  /***/
    
  //Дозволяємо генерацію переривань при завершенні передачі байту
  USART_ITConfig(USART_RS485, USART_IT_TC, ENABLE);

  //Забороняємо генерацію переривання від DMA_StreamRS485_Tx
  DMA_StreamRS485_Tx->CR &= ~DMA_IT_TC;

  //Зупиняємо потоку DMA
  DMA_StreamRS485_Tx->CR &= ~(uint32_t)DMA_SxCR_EN;
  DMA_StreamRS485_Tx->NDTR = 0;

  //Очищаємо прапореці, що сигналізує про завершення передачі даних для DMA1 по потоку RS-485_TX
  DMA_ClearFlag(DMA_StreamRS485_Tx, DMA_FLAG_TCRS485_Tx | DMA_FLAG_HTRS485_Tx | DMA_FLAG_TEIRS485_Tx | DMA_FLAG_DMEIRS485_Tx | DMA_FLAG_FEIRS485_Tx);
  
#ifdef SYSTEM_VIEWER_ENABLE
  SEGGER_SYSVIEW_RecordExitISR();
#endif
}
/*****************************************************/

/*****************************************************/
//Переривання від I2C
/*****************************************************/
void EXITI_POWER_IRQHandler(void)
{
#ifdef SYSTEM_VIEWER_ENABLE
  SEGGER_SYSVIEW_RecordEnterISR();
#endif

  if(EXTI_GetITStatus(EXTI_Line_POWER) != RESET)
  {
    /* Clear the EXTI line 0 pending bit */
    EXTI_ClearITPendingBit(EXTI_Line_POWER);
    
    if ((POWER_CTRL->IDR & POWER_CTRL_PIN) != (uint32_t)Bit_RESET)
    {
      //Живлення появилося на вході блоку живлення

      //Виставляємо повідомлення про цю подію
      if (clear_diagnostyka != NULL) _SET_BIT(clear_diagnostyka, EVENT_DROP_POWER_BIT);
      reinit_LCD = true;
    }
    else
    {
      //Живлення пропало на вході блоку живлення

      //Вимикаємо підсвітку
      LCD_BL->BSRRH = LCD_BL_PIN;
      time_backlighting = 0;

      //Виставляємо повідомлення про цю подію
      if (set_diagnostyka != NULL) _SET_BIT(set_diagnostyka, EVENT_DROP_POWER_BIT);
    }
  }
  
#ifdef SYSTEM_VIEWER_ENABLE
  SEGGER_SYSVIEW_RecordExitISR();
#endif
}
/*****************************************************/

/*****************************************************/
//
/*****************************************************/
/*****************************************************/

