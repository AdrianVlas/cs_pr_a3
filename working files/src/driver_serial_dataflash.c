#include "header.h"

/*****************************************************/
//Запустити передачу і прийом по SPI
/*****************************************************/
//void start_exchange_via_spi(int index_chip, unsigned int number_bytes_transfer)
//{
//  //Фіксуємо скільки байт ми будем передавати (це потрібно на випадок винекнення помилки - щоб можна було повторно запустити цю операцію)
//  number_bytes_transfer_spi_df = number_bytes_transfer;
//  
//  //Зупиняємо потік DMA на прийом даних якщо він запущений
//  if ((DMA_StreamSPI_DF_Rx->CR & (uint32_t)DMA_SxCR_EN) !=0) DMA_StreamSPI_DF_Rx->CR &= ~(uint32_t)DMA_SxCR_EN;
//  DMA_StreamSPI_DF_Rx->NDTR = number_bytes_transfer;
//  //Зупиняємо потік DMA на передачу даних якщо він запущений
//  if ((DMA_StreamSPI_DF_Tx->CR & (uint32_t)DMA_SxCR_EN) !=0) DMA_StreamSPI_DF_Tx->CR &= ~(uint32_t)DMA_SxCR_EN;
//  DMA_StreamSPI_DF_Tx->NDTR = number_bytes_transfer;
//  
//  //Очищаємо прапореці, що сигналізує про завершення прийом/передачі даних для DMA1 по каналу SPI_DF_Rx і SPI_DF_Tx
//  DMA_ClearFlag(DMA_StreamSPI_DF_Rx, DMA_FLAG_TCSPI_DF_Rx | DMA_FLAG_HTSPI_DF_Rx | DMA_FLAG_TEISPI_DF_Rx | DMA_FLAG_DMEISPI_DF_Rx | DMA_FLAG_FEISPI_DF_Rx);
//  DMA_ClearFlag(DMA_StreamSPI_DF_Tx, DMA_FLAG_TCSPI_DF_Tx | DMA_FLAG_HTSPI_DF_Tx | DMA_FLAG_TEISPI_DF_Tx | DMA_FLAG_DMEISPI_DF_Tx | DMA_FLAG_FEISPI_DF_Tx);
//  
//  //Дозволяємо передачу через DMA
//  if ((SPI_DF->CR2 & SPI_I2S_DMAReq_Tx) == 0) SPI_DF->CR2 |= SPI_I2S_DMAReq_Tx;
//  //Дозволяємо прийом через DMA
//  if ((SPI_DF->CR2 & SPI_I2S_DMAReq_Rx) == 0) SPI_DF->CR2 |= SPI_I2S_DMAReq_Rx;
//
//  //Виставляємо chip_select  з встановленням у драйвері повідомлення, що іде обмін
//  if (index_chip == INDEX_DATAFLASH_1) GPIO_SPI_DF_TOGGLE->BSRRH = GPIO_SPI_DF_TOGGLE_Pin;//DF_TOGGLE - пін переводимо у 0 
//  else if (index_chip == INDEX_DATAFLASH_2)GPIO_SPI_DF_TOGGLE->BSRRL = GPIO_SPI_DF_TOGGLE_Pin;//DF_TOGGLE - пін переводимо у 1
//  else
//  {
//    //Відбцлася невизначена помилка, тому треба піти на перезавантаження
//    total_error_sw_fixed(6);
//  }
//  state_execution_spi_df[index_chip] = TRANSACTION_EXECUTING;
//  GPIO_SPI_DF->BSRRH = GPIO_NSSPin_DF; //Виставляємо Chip_select переводом NSS  у 0
//
//  //Дозволяэмо генерацыю переривань від потоку DMA_StreamSPI_DF_Rx
//  DMA_StreamSPI_DF_Rx->CR |= DMA_IT_TC;
//  
//  //Очищаємо можливі помилкит
//  SPI_DF->DR;
//  SPI_DF->SR;
//
//  //Запускаємо прийом-передачу 
//  DMA_StreamSPI_DF_Rx->CR |= (uint32_t)DMA_SxCR_EN;
//  DMA_StreamSPI_DF_Tx->CR |= (uint32_t)DMA_SxCR_EN;
//}
/*****************************************************/

/*****************************************************/
//
/*****************************************************/
/*****************************************************/
