//#include <QtWidgets>
//#include "loghandler.h"
//0-adr  1-func   2-ByteCount 3-RefType  4-MFileNumber   5-LFileNumber   6-MRecordNumber  7-LRecordNumber  8-MRecordLen  9-LRecordLen
//  byte inputPacket[] {0x1,      20,     7,          6,         0x0,               5,             0,             0,                  0,          9};

#include "header.h"

int inputPacketParser(void);
void inputPacketParserUSB(void);
void inputPacketParserRS485(void);
unsigned short int  AddCRC(unsigned char inpbyte, unsigned short int oldCRC);
int Error_modbus(unsigned int address, unsigned int function, unsigned int error, unsigned char *output_data);
int outputFunc20PacketEncoder(int adrUnit, int fileNumber, int recordNumber, int recordLen);
int outputFunc20PacketEncoderPro(int adrUnit, int recordNumber, int recordLen);
int outputFunc16PacketEncoder(int adrUnit, int adrReg, int cntReg);
int outputFunc15PacketEncoder(int adrUnit, int adrBit, int cntBit);
int outputFunc6PacketEncoder(int adrUnit, int adrReg, int dataReg);
int outputFunc5PacketEncoder(int adrUnit, int adrBit, int dataBit);
int outputFunc3PacketEncoder(int adrUnit, int adrReg, int cntReg);
int outputFunc1PacketEncoder(int adrUnit, int adrReg, int cntReg);
//void restart_monitoring_RS485(void);

unsigned char  *outputPacket;
unsigned char  outputPacket_USB[300];
unsigned char  outputPacket_RS485[300];

int sizeOutputPacket = 0;
unsigned char *inputPacket;
int *received_count;
int pointInterface=0;//метка интерфейса 0-USB 1-RS485
int globalcntBit  = 0;//к-во бит
int globalcntReg  = 0;//к-во регистров
int globalbeginAdrReg  = 0;//адрес нач регистра
int globalbeginAdrBit  = 0;//адрес нач бит
int upravlFlag=0;//флаг пакетов управления 1-есть управление
int upravlSetting=0;//флаг Setting
int upravlSchematic=0;//флаг Shematic
int upravlYust=0;//флаг юстировки
int upravlBroadcast=0;//флаг общей записи времени
int upravlconfig_and_settings=0;//флаг активации компонента
int globalResetFlag=0;//флаг глобального сброса

/**************************************/
//разбор входного пакета USB
/**************************************/
void inputPacketParserUSB(void)
{
  pointInterface=0;//метка интерфейса 0-USB 1-RS485
  upravlFlag=0;//флаг пакетов управления 1-есть управление
  upravlSetting=0;//флаг Setting
  upravlSchematic=0;//флаг Shematic
  globalResetFlag=0;//флаг глобального сброса
  upravlBroadcast=0;//флаг общей записи времени

  received_count = &usb_received_count;

  inputPacket = usb_received;
  outputPacket = outputPacket_USB;
  //Перевірка контрольної суми
  unsigned short CRC_sum;
  CRC_sum = 0xffff;
  for (int index = 0; index < (*received_count-2); index++) CRC_sum = AddCRC(*(inputPacket + index),CRC_sum);
  if((CRC_sum & 0xff)  != *(inputPacket+*received_count-2)) return;
  if ((CRC_sum >> 8  ) != *(inputPacket+*received_count-1)) return;

  if(inputPacket[0]==0)//глоб адрес
  if(inputPacket[1]==16)//номер ф-ции
  if(((unsigned int)inputPacket[3] +256*(unsigned int)inputPacket[2])==14224)
  if(((unsigned int)inputPacket[5] +256*(unsigned int)inputPacket[4])==7) upravlBroadcast=1;//флаг общей записи времени

  if(!(inputPacket[0]==settings_fix_prt.address||upravlBroadcast==1)) return;

  if(inputPacketParser()==0) return;

  if(upravlBroadcast) return;//флаг общей записи времени

  usb_transmiting_count = sizeOutputPacket;
  for (int i = 0; i < usb_transmiting_count; i++) usb_transmiting[i] = outputPacket[i];
  data_usb_transmiting = true;

//флаг глобального сброса
  if(globalResetFlag) restart_device = true;

}//inputPacketParserUSB(void)
/**************************************/
//разбор входного пакета RS485
/**************************************/
void inputPacketParserRS485(void)
{
  pointInterface=1;//метка интерфейса 0-USB 1-RS485
  globalResetFlag=0;//флаг глобального сброса
  upravlFlag=0;//флаг пакетов управления 1-есть управление
  upravlSetting=0;//флаг Setting
  upravlSchematic=0;//флаг Shematic
  upravlBroadcast=0;//флаг общей записи времени

  inputPacket = RxBuffer_RS485;

  received_count = &RxBuffer_RS485_count;
  outputPacket = outputPacket_RS485;
  //Перевірка контрольної суми
  unsigned short CRC_sum;
  CRC_sum = 0xffff;
  for (int index = 0; index < (*received_count-2); index++) CRC_sum = AddCRC(*(inputPacket + index),CRC_sum);
  if((CRC_sum & 0xff)  != *(inputPacket+*received_count-2) ||//) return;
      (CRC_sum >> 8  ) != *(inputPacket+*received_count-1))
    {
      /***
      12345
      Причина рестарту (не співпала контрольна сума)
      ***/
      reason_of_restart_RS485 |= (1 << 5);
      /***/
              
      restart_monitoring_RS485();
      return;
    }

//  if(inputPacket[0]!=settings_fix_prt.address)
  if(inputPacket[0]==0)//глоб адрес
  if(inputPacket[1]==16)//номер ф-ции
  if(((unsigned int)inputPacket[3] +256*(unsigned int)inputPacket[2])==14224)
  if(((unsigned int)inputPacket[5] +256*(unsigned int)inputPacket[4])==7) upravlBroadcast=1;//флаг общей записи времени

  if(!(inputPacket[0]==settings_fix_prt.address||upravlBroadcast==1)) 
    {
      /***
      12345
      Причина рестарту (не співпала адреса 2)
      ***/
      reason_of_restart_RS485 |= (1 << 6);
      /***/
              
      restart_monitoring_RS485();
      return;
    }

  if(inputPacketParser()==0)
    {
      /***
      12345
      Причина рестарту (запит пакету відповіді завеликого розміру)
      ***/
      reason_of_restart_RS485 |= (1 << 7);
      /***/
              
      restart_monitoring_RS485();
      return;
    }

  if(upravlBroadcast)//флаг общей записи времени
   {
      /***
      12345
      Причина рестарту (широкосмугова команда)
      ***/
      reason_of_restart_RS485 |= (1 << 8);
      /***/
              
      restart_monitoring_RS485();
      return;
   }//if

  TxBuffer_RS485_count = sizeOutputPacket;
  for (int i = 0; i < TxBuffer_RS485_count; i++) TxBuffer_RS485[i] = outputPacket[i];
  start_transmint_data_via_RS_485(TxBuffer_RS485_count);

//флаг глобального сброса
  if(globalResetFlag) restart_device = true;

}//inputPacketParserRS485(void)

/**************************************/
//разбор входного пакета
/**************************************/
int inputPacketParser(void)
{

  int adrUnit = inputPacket[0];
  int numFunc = inputPacket[1];//номер ф-ции

  sizeOutputPacket = 0;
  indexTW = 0;//индекс буфера записи
  switch(numFunc)
    {
    case 2:
    case 1:
    {
      globalbeginAdrBit  = (unsigned int)inputPacket[3] +256*(unsigned int)inputPacket[2];
      globalcntBit      = (unsigned int)inputPacket[5] +256*(unsigned int)inputPacket[4];
      if(globalcntBit>1000) return 0;//слишком длинный пакет
      //qDebug()<<"adrUnit="<<adrUnit<<" numFunc="<<numFunc<<" adrBit="<<adrBit<<" cntBit="<<cntBit;
      outputPacket[1] = (unsigned char)numFunc;
      sizeOutputPacket = outputFunc1PacketEncoder(adrUnit, globalbeginAdrBit, globalcntBit);
    }
    break;
    case 4:
    case 3:
    {
      globalbeginAdrReg  = (unsigned int)inputPacket[3] +256*(unsigned int)inputPacket[2];
      globalcntReg      = (unsigned int)inputPacket[5] +256*(unsigned int)inputPacket[4];
      if(globalcntReg>125) return 0;//слишком длинный пакет
      //qDebug()<<"adrUnit="<<adrUnit<<" numFunc="<<numFunc<<" adrReg="<<adrReg<<" cntReg="<<cntReg;
      outputPacket[1] = (unsigned char)numFunc;
      sizeOutputPacket = outputFunc3PacketEncoder(adrUnit, globalbeginAdrReg, globalcntReg);
    }
    break;
    case 5:
    {
      globalbeginAdrBit  = (unsigned int)inputPacket[3] +256*(unsigned int)inputPacket[2];
      int dataBit = (unsigned int)inputPacket[5] +256*(unsigned int)inputPacket[4];
      globalcntBit      = 1;
      switch(dataBit)
        {
        case 0xFF00:
          dataBit = 1;
          break;
        case 0x0000:
          dataBit = 0;
          break;
        default:
        {
          sizeOutputPacket = Error_modbus(adrUnit, // address,
                                          numFunc,//function,
                                          ERROR_ILLEGAL_DATA_VALUE,//error,
                                          outputPacket);//output_data
          return 1;
        }
        }//switch
      outputPacket[1] = (unsigned char)numFunc;
      sizeOutputPacket = outputFunc5PacketEncoder(adrUnit, globalbeginAdrBit, dataBit);
    }
    break;
    case 6:
    {
      globalbeginAdrReg  = (unsigned int)inputPacket[3] +256*(unsigned int)inputPacket[2];
      int dataReg = (unsigned int)inputPacket[5] +256*(unsigned int)inputPacket[4];
      globalcntReg      = 1;
      outputPacket[1] = (unsigned char)numFunc;
      sizeOutputPacket = outputFunc6PacketEncoder(adrUnit, globalbeginAdrReg, dataReg);
    }
    break;
    case 15:
    {
      globalbeginAdrBit  = (unsigned int)inputPacket[3] +256*(unsigned int)inputPacket[2];
      globalcntBit  = (unsigned int)inputPacket[5] +256*(unsigned int)inputPacket[4];
      int cntByte = (unsigned int)inputPacket[6];
      if(globalcntBit>125*16) return 0;//слишком длинный пакет

      for(int i=0; i<cntByte; i++)
        tempReadArray[i] = (unsigned short)(inputPacket[7+i]);
      outputPacket[1] = (unsigned char)numFunc;
      sizeOutputPacket = outputFunc15PacketEncoder(adrUnit, globalbeginAdrBit, globalcntBit);
    }
    break;
    case 16:
    {
      globalbeginAdrReg  = (unsigned int)inputPacket[3] +256*(unsigned int)inputPacket[2];
      globalcntReg  = (unsigned int)inputPacket[5] +256*(unsigned int)inputPacket[4];
      if(globalcntReg>125) return 0;//слишком длинный пакет

      for(int i=0; i<globalcntReg; i++)
        tempReadArray[i] = (unsigned short)(inputPacket[7+1+(i*2)]) +256*(unsigned short)(inputPacket[7+(i*2)]);
      outputPacket[1] = (unsigned char)numFunc;
      sizeOutputPacket = outputFunc16PacketEncoder(adrUnit, globalbeginAdrReg, globalcntReg);
    }
    break;
    case 20:
    {
      //int byteCount = inputPacket[2];
      // int refType   = inputPacket[3];
      int fileNumber   = (unsigned int)inputPacket[5] +256*(unsigned int)inputPacket[4];
      int recordNumber = (unsigned int)inputPacket[7] +256*(unsigned int)inputPacket[6];
      int recordLen    = (unsigned int)inputPacket[9] +256*(unsigned int)inputPacket[8];
      if(fileNumber==15) {//pro
      if(((unsigned int)recordLen)>6)
        {
          sizeOutputPacket = Error_modbus(adrUnit, // address,
                                          inputPacket[1],//function,
                                          2,//error,
                                          outputPacket);//output_data
          break;
        }//if
        outputPacket[1] = (unsigned char)numFunc;
        sizeOutputPacket = outputFunc20PacketEncoderPro(adrUnit, recordNumber, recordLen);
        break;
      }//if(fileNumber==15) 
      if(fileNumber<5 || fileNumber>14 || ((unsigned int)recordNumber)>9999 || ((unsigned int)recordLen)>9)
        {
          sizeOutputPacket = Error_modbus(adrUnit, // address,
                                          inputPacket[1],//function,
                                          2,//error,
                                          outputPacket);//output_data
          break;
        }//if

//      if(recordLen>125) return 0;//слишком длинный пакет
//      qDebug()<<"adrUnit="<<adrUnit<<" numFunc="<<numFunc<<" byteCount="<<byteCount<<" refType="<<refType<<
      //              " fileNumber="<<fileNumber<<" recordNumber="<<recordNumber<<" recordLen="<<recordLen;

      outputPacket[1] = (unsigned char)numFunc;
      sizeOutputPacket = outputFunc20PacketEncoder(adrUnit, fileNumber, recordNumber, recordLen);
    }
    break;

    default:
    {
      sizeOutputPacket = Error_modbus(adrUnit, // address,
                                      numFunc,//function,
                                      ERROR_ILLEGAL_FUNCTION,//error,
                                      outputPacket);//output_data
      return 1;
    }
    }//switch

  unsigned short CRC_sum = 0xffff;
  for (int index = 0; index < sizeOutputPacket; index++) CRC_sum = AddCRC((*(outputPacket + index)) ,CRC_sum);
  *(outputPacket + sizeOutputPacket)  = CRC_sum & 0xff;
  *(outputPacket + sizeOutputPacket+1)  = CRC_sum >> 8;
  sizeOutputPacket += 2;
  /*
    int tt1 = outputPacket[0];
    int tt2 = outputPacket[1];
    int tt3 = outputPacket[2];
    int tt4 = outputPacket[3];
    int tt5 = outputPacket[4];
    int tt6 = outputPacket[5];
    int tt7 = outputPacket[6];
    int tt8 = outputPacket[7];
    int tt9 = outputPacket[8];
    int tt10 = outputPacket[9];
    int tt11 = outputPacket[10];
    int tt12 = outputPacket[11];
    int tt13 = outputPacket[12];
    int tt14 = outputPacket[13];
    int tt15 = outputPacket[14];
    int tt16 = outputPacket[15];
    int tt17 = outputPacket[16];
  */
  return 1;
}//inputPacketParser

int outputFunc20PacketEncoderPro(int adrUnit, int recordNumber, int recordLen)
{
//выходной кодировщик 20 функции Pro
//  int bazaRecord = (fileNumber-5)*10000;
  unsigned int number_record_of_log = recordNumber;

//  if(number_record_of_log>number_record_of_pr_err_into_USB)
//    return Error_modbus(adrUnit, // address,
//                        outputPacket[1],//function,
//                        2,//error,
//                        outputPacket);//output_data
number_record_of_pr_err_into_USB = number_record_of_log;
_SET_STATE(control_tasks_dataflash, TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_USB_BIT);

      uint32_t delta_time = 0;
      uint32_t time_start = TIM4->CNT;
      while (
        ((control_tasks_dataflash &  MASKA_FOR_BIT(TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_USB_BIT )) != 0) &&
        (delta_time < MAX_TIMEOUT_WAITING_REQUESTED_DATA)
      )
        {
          uint32_t current_time_tim4 = TIM4->CNT;

          if (current_time_tim4 >= time_start)
            delta_time = current_time_tim4 - time_start;
          else
            delta_time = current_time_tim4 + 0x10000 - time_start;

          //Робота з Watchdog
          watchdog_routine();
        }//while

      if ((control_tasks_dataflash &  MASKA_FOR_BIT(TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_USB_BIT )) != 0)
        {
          //Ми не дочекалися завершення читання з мікросхеми DataFalash
          number_record_of_pr_err_into_USB = 0xffffffff;
          _CLEAR_STATE(control_tasks_dataflash, TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_USB_BIT);
          return Error_modbus(adrUnit, // address,
                              outputPacket[1],//function,
                              2,//error,
                              outputPacket);//output_data
        }//if
  short dataRegister[130];
  int   idxDataRegister = 0;
  int idxOutputPacket = 0;
//adrUnit
  outputPacket[idxOutputPacket] = (unsigned char)adrUnit;
  idxOutputPacket++;
//numFunc
  idxOutputPacket++;
//Resp. Data length
  outputPacket[idxOutputPacket] = (unsigned char)((2+recordLen*2)&0xFF);
  idxOutputPacket++;
//File resp. length
  outputPacket[idxOutputPacket] = (unsigned char)((1+recordLen*2)&0xFF);
  idxOutputPacket++;
//Ref. Type
  outputPacket[idxOutputPacket] = 6;
  idxOutputPacket++;

  for(; idxDataRegister<recordLen; idxDataRegister++)
    {
      int result = superReader20Pro(idxDataRegister);
      switch(result)
        {
        case MARKER_OUTPERIMETR:
          //  dataRegister[idxDataRegister] = -1;
//          dataRegister[idxDataRegister] = 0;//(short) result;
          break;
        case MARKER_ERRORPERIMETR://ошибка периметра
          //dataRegister[idxDataRegister] = -2;
//       break;
          return Error_modbus(adrUnit, // address,
                              outputPacket[1],//function,
                              10,//error,
                              outputPacket);//output_data
        default:
        {
          dataRegister[idxDataRegister] = (short) result;
        }
        }//switch
//      qDebug()<<"result= "<<dataRegister[idxDataRegister];
    }//for

  for(int i=0; i<idxDataRegister; i++)
    {
//Mdata
      outputPacket[idxOutputPacket] = (unsigned char)((dataRegister[i]>>8)&0xFF);
      idxOutputPacket++;
//Ldata
      outputPacket[idxOutputPacket] = (unsigned char)(dataRegister[i]&0xFF);
      idxOutputPacket++;
    }//for

  return idxOutputPacket;
}//outputFunc20PacketEncoderPro(int adrUnit, int recordNumber, int recordLen);

int outputFunc20PacketEncoder(int adrUnit, int fileNumber, int recordNumber, int recordLen)
{
//выходной кодировщик 20 функции
  int bazaRecord = (fileNumber-5)*10000;
  unsigned int number_record_of_log = bazaRecord + recordNumber;

  if(number_record_of_log>info_rejestrator_log.number_records)
    return Error_modbus(adrUnit, // address,
                        outputPacket[1],//function,
                        2,//error,
                        outputPacket);//output_data

  switch(pointInterface)  //метка интерфейса 0-USB 1-RS485
    {
    case 0:
    {
      //USB
      number_record_of_log_into_USB = number_record_of_log;//номер запису для читання;
      _SET_STATE(control_tasks_dataflash, TASK_MAMORY_READ_DATAFLASH_FOR_LOG_USB_BIT);

      uint32_t delta_time = 0;
      uint32_t time_start = TIM4->CNT;
      while (
        ((control_tasks_dataflash &  MASKA_FOR_BIT(TASK_MAMORY_READ_DATAFLASH_FOR_LOG_USB_BIT )) != 0) &&
        (delta_time < MAX_TIMEOUT_WAITING_REQUESTED_DATA)
      )
        {
          uint32_t current_time_tim4 = TIM4->CNT;

          if (current_time_tim4 >= time_start)
            delta_time = current_time_tim4 - time_start;
          else
            delta_time = current_time_tim4 + 0x10000 - time_start;

          //Робота з Watchdog
          watchdog_routine();
        }//while

      if ((control_tasks_dataflash &  MASKA_FOR_BIT(TASK_MAMORY_READ_DATAFLASH_FOR_LOG_USB_BIT )) != 0)
        {
          //Ми не дочекалися завершення читання з мікросхеми DataFalash
          number_record_of_log_into_USB = 0xffffffff;
          _CLEAR_STATE(control_tasks_dataflash, TASK_MAMORY_READ_DATAFLASH_FOR_LOG_USB_BIT);
          return Error_modbus(adrUnit, // address,
                              outputPacket[1],//function,
                              2,//error,
                              outputPacket);//output_data
        }//if
    }
    break;

    case 1:
    {
      //RS485
      number_record_of_log_into_RS485 = number_record_of_log;//номер запису для читання;
      _SET_STATE(control_tasks_dataflash, TASK_MAMORY_READ_DATAFLASH_FOR_LOG_RS485_BIT);

      uint32_t delta_time = 0;
      uint32_t time_start = TIM4->CNT;
      while (
        ((control_tasks_dataflash &  MASKA_FOR_BIT(TASK_MAMORY_READ_DATAFLASH_FOR_LOG_RS485_BIT )) != 0) &&
        (delta_time < MAX_TIMEOUT_WAITING_REQUESTED_DATA)
      )
        {
          uint32_t current_time_tim4 = TIM4->CNT;

          if (current_time_tim4 >= time_start)
            delta_time = current_time_tim4 - time_start;
          else
            delta_time = current_time_tim4 + 0x10000 - time_start;

          //Робота з Watchdog
          watchdog_routine();
        }//while

      if ((control_tasks_dataflash &  MASKA_FOR_BIT(TASK_MAMORY_READ_DATAFLASH_FOR_LOG_RS485_BIT )) != 0)
        {
          //Ми не дочекалися завершення читання з мікросхеми DataFalash
          number_record_of_log_into_RS485 = 0xffffffff;
          _CLEAR_STATE(control_tasks_dataflash, TASK_MAMORY_READ_DATAFLASH_FOR_LOG_RS485_BIT);
          return Error_modbus(adrUnit, // address,
                              outputPacket[1],//function,
                              2,//error,
                              outputPacket);//output_data
        }//if
    }
    break;


    }//switch

  //Успішне читання даних з енергонезалеженої пам'яті DataFlash

  short dataRegister[130];
  int   idxDataRegister = 0;
  int idxOutputPacket = 0;
//adrUnit
  outputPacket[idxOutputPacket] = (unsigned char)adrUnit;
  idxOutputPacket++;
//numFunc
  idxOutputPacket++;
//Resp. Data length
  outputPacket[idxOutputPacket] = (unsigned char)((2+recordLen*2)&0xFF);
  idxOutputPacket++;
//File resp. length
  outputPacket[idxOutputPacket] = (unsigned char)((1+recordLen*2)&0xFF);
  idxOutputPacket++;
//Ref. Type
  outputPacket[idxOutputPacket] = 6;
  idxOutputPacket++;

  for(; idxDataRegister<recordLen; idxDataRegister++)
    {
      int result = superReader20(idxDataRegister);
      switch(result)
        {
        case MARKER_OUTPERIMETR:
          //  dataRegister[idxDataRegister] = -1;
//          dataRegister[idxDataRegister] = 0;//(short) result;
          break;
        case MARKER_ERRORPERIMETR://ошибка периметра
          //dataRegister[idxDataRegister] = -2;
//       break;
          return Error_modbus(adrUnit, // address,
                              outputPacket[1],//function,
                              10,//error,
                              outputPacket);//output_data
        default:
        {
          dataRegister[idxDataRegister] = (short) result;
        }
        }//switch
//      qDebug()<<"result= "<<dataRegister[idxDataRegister];
    }//for

  for(int i=0; i<idxDataRegister; i++)
    {
//Mdata
      outputPacket[idxOutputPacket] = (unsigned char)((dataRegister[i]>>8)&0xFF);
      idxOutputPacket++;
//Ldata
      outputPacket[idxOutputPacket] = (unsigned char)(dataRegister[i]&0xFF);
      idxOutputPacket++;
    }//for

  return idxOutputPacket;
}//outputFunc20PacketEncoder(int adrUnit, int fileNumber, int recordNumber, int recordLen);

int outputFunc16PacketEncoder(int adrUnit, int adrReg, int cntReg)
{
//выходной кодировщик 16 функции
  short dataReg = 0;
  int   flag = 1;
  superPreWriteAction();//action до записи
  for(int i=0; i<cntReg; i++)
    {
      dataReg = tempReadArray[i];
      int result = superWriterRegister(adrReg+i, dataReg);
      switch(result)
        {
        case MARKER_OUTPERIMETR:
          result = -1;
          break;
        case MARKER_ERRORPERIMETR:
          result = -2;
          return Error_modbus(adrUnit, // address,
                              outputPacket[1],//function,
                              ERROR_ILLEGAL_DATA_ADDRESS,//error,
                              outputPacket);//output_data

        case MARKER_ERRORDIAPAZON:
          result = -3;
          return Error_modbus(adrUnit, // address,
                              outputPacket[1],//function,
                              ERROR_ILLEGAL_DATA_VALUE,//error,
                              outputPacket);//output_data
        default:
        {
          flag = 0;
        }
        }//switch
      //qDebug()<<"result= "<<result;
    }//for
  if(flag)//незначащие пакеты недопустимы
    return Error_modbus(adrUnit, // address,
                        outputPacket[1],//function,
                        ERROR_ILLEGAL_DATA_ADDRESS,//error,
                        outputPacket);//output_data

  int upravlReturn = superPostWriteAction();//action после записи
  if(upravlReturn) return upravlReturn;//сформировать пакет ошибки

  int idxOutputPacket = 0;
//adrUnit
  outputPacket[idxOutputPacket] = (unsigned char)adrUnit;
  idxOutputPacket++;
//numFunc
  idxOutputPacket++;
//MadrReg
  outputPacket[idxOutputPacket] = (unsigned char)((adrReg>>8)&0xFF);
  idxOutputPacket++;
//LadrReg
  outputPacket[idxOutputPacket] = (unsigned char)(adrReg&0xFF);
  idxOutputPacket++;
//MdataReg
  outputPacket[idxOutputPacket] = (unsigned char)((cntReg>>8)&0xFF);
  idxOutputPacket++;
//LdataReg
  outputPacket[idxOutputPacket] = (unsigned char)(cntReg&0xFF);
  idxOutputPacket++;
  return idxOutputPacket;
}//outputFunc16PacketEncoder(int adrUnit, int adrReg, int cntReg)

int outputFunc15PacketEncoder(int adrUnit, int adrBit, int cntBit)
{
//выходной кодировщик 16 функции
  short dataBit = 0;
  int   flag = 1;
  superPreWriteAction();//action до записи
  for(int i=0; i<cntBit; i++)
    {
      int idx = i/8;
      dataBit = tempReadArray[idx];
      short maska = 1<<(i%8);
      int result = superWriterBit(adrBit+i, dataBit&maska ? 1:0);
      switch(result)
        {
        case MARKER_OUTPERIMETR:
          result = -1;
          break;
        case MARKER_ERRORPERIMETR:
          result = -2;
          return Error_modbus(adrUnit, // address,
                              outputPacket[1],//function,
                              ERROR_ILLEGAL_DATA_ADDRESS,//error,
                              outputPacket);//output_data

        case MARKER_ERRORDIAPAZON:
          result = -3;
          return Error_modbus(adrUnit, // address,
                              outputPacket[1],//function,
                              ERROR_ILLEGAL_DATA_VALUE,//error,
                              outputPacket);//output_data
        default:
        {
          flag = 0;
        }
        }//switch
      //qDebug()<<"result= "<<result;
    }//for
  if(flag)//незначащие пакеты недопустимы
    return Error_modbus(adrUnit, // address,
                        outputPacket[1],//function,
                        ERROR_ILLEGAL_DATA_ADDRESS,//error,
                        outputPacket);//output_data

  int upravlReturn = superPostWriteAction();//action после записи
  if(upravlReturn) return upravlReturn;//сформировать пакет ошибки

  int idxOutputPacket = 0;
//adrUnit
  outputPacket[idxOutputPacket] = (unsigned char)adrUnit;
  idxOutputPacket++;
//numFunc
  idxOutputPacket++;
//MadrBit
  outputPacket[idxOutputPacket] = (unsigned char)((adrBit>>8)&0xFF);
  idxOutputPacket++;
//LadrBit
  outputPacket[idxOutputPacket] = (unsigned char)(adrBit&0xFF);
  idxOutputPacket++;
//McntBit
  outputPacket[idxOutputPacket] = (unsigned char)((cntBit>>8)&0xFF);
  idxOutputPacket++;
//LcntBit
  outputPacket[idxOutputPacket] = (unsigned char)(cntBit&0xFF);
  idxOutputPacket++;
  return idxOutputPacket;
}//outputFunc15PacketEncoder(int adrUnit, int adrBit, int cntBit)

int outputFunc6PacketEncoder(int adrUnit, int adrReg, int dataReg)
{
//выходной кодировщик 6 функции
  superPreWriteAction();//action до записи
  int result = superWriterRegister(adrReg, dataReg);
  switch(result)
    {
    case MARKER_OUTPERIMETR:
      result = -1;
      return Error_modbus(adrUnit, // address,
                          outputPacket[1],//function,
                          ERROR_ILLEGAL_DATA_ADDRESS,//error,
                          outputPacket);//output_data
    case MARKER_ERRORPERIMETR:
      result = -2;
      return Error_modbus(adrUnit, // address,
                          outputPacket[1],//function,
                          ERROR_ILLEGAL_DATA_ADDRESS,//error,
                          outputPacket);//output_data
    case MARKER_ERRORDIAPAZON:
      result = -3;
      return Error_modbus(adrUnit, // address,
                          outputPacket[1],//function,
                          ERROR_ILLEGAL_DATA_VALUE,//error,
                          outputPacket);//output_data
    }//switch

  int upravlReturn = superPostWriteAction();//action после записи
  if(upravlReturn) return upravlReturn;//сформировать пакет ошибки

  int idxOutputPacket = 0;
//adrUnit
  outputPacket[idxOutputPacket] = (unsigned char)adrUnit;
  idxOutputPacket++;
//numFunc
  idxOutputPacket++;
//MadrReg
  outputPacket[idxOutputPacket] = (unsigned char)((adrReg>>8)&0xFF);
  idxOutputPacket++;
//LadrReg
  outputPacket[idxOutputPacket] = (unsigned char)(adrReg&0xFF);
  idxOutputPacket++;
//MdataReg
  outputPacket[idxOutputPacket] = (unsigned char)((dataReg>>8)&0xFF);
  idxOutputPacket++;
//LdataReg
  outputPacket[idxOutputPacket] = (unsigned char)(dataReg&0xFF);
  idxOutputPacket++;
  return idxOutputPacket;
}//outputFunc6PacketEncoder(int adrUnit, int adrReg, int dataReg)

int outputFunc5PacketEncoder(int adrUnit, int adrBit, int dataBit)
{
//выходной кодировщик 5 функции
  superPreWriteAction();//action до записи
  int result = superWriterBit(adrBit, dataBit);
  switch(result)
    {
    case MARKER_OUTPERIMETR:
      result = -1;
      return Error_modbus(adrUnit, // address,
                          outputPacket[1],//function,
                          ERROR_ILLEGAL_DATA_ADDRESS,//error,
                          outputPacket);//output_data
    case MARKER_ERRORPERIMETR:
      result = -2;
      return Error_modbus(adrUnit, // address,
                          outputPacket[1],//function,
                          ERROR_ILLEGAL_DATA_ADDRESS,//error,
                          outputPacket);//output_data
    case MARKER_ERRORDIAPAZON:
      result = -3;
      return Error_modbus(adrUnit, // address,
                          outputPacket[1],//function,
                          ERROR_ILLEGAL_DATA_VALUE,//error,
                          outputPacket);//output_data
    }//switch

  int upravlReturn = superPostWriteAction();//action после записи
  if(upravlReturn) return upravlReturn;//сформировать пакет ошибки

  int idxOutputPacket = 0;
//adrUnit
  outputPacket[idxOutputPacket] = (unsigned char)adrUnit;
  idxOutputPacket++;
//numFunc
  idxOutputPacket++;
//MadrBit
  outputPacket[idxOutputPacket] = (unsigned char)((adrBit>>8)&0xFF);
  idxOutputPacket++;
//LadrBit
  outputPacket[idxOutputPacket] = (unsigned char)(adrBit&0xFF);
  idxOutputPacket++;
//MdataReg
  outputPacket[idxOutputPacket] = (unsigned char)(0xFF);
  if(dataBit==0) outputPacket[idxOutputPacket] = (unsigned char)(0x00);
  idxOutputPacket++;
//LdataReg
  outputPacket[idxOutputPacket] = (unsigned char)(0x0);
  idxOutputPacket++;
  return idxOutputPacket;
}//outputFunc5PacketEncoder(int adrUnit, int adrBit)

int outputFunc3PacketEncoder(int adrUnit, int adrReg, int cntReg)
{
//выходной кодировщик 3 функции
  short dataRegister[130];
  int   idxDataRegister = 0;
  int   flag = 1;
  superPreReadAction();//action до чтения
  for(; idxDataRegister<cntReg; idxDataRegister++)
    {
      int result = superReaderRegister(adrReg+ idxDataRegister);
      switch(result)
        {
        case MARKER_OUTPERIMETR:
          dataRegister[idxDataRegister] = -1;
          dataRegister[idxDataRegister] = 0;//(short) result;
          break;
        case MARKER_ERRORPERIMETR://ошибка периметра
          dataRegister[idxDataRegister] = -2;
//       break;
          return Error_modbus(adrUnit, // address,
                              outputPacket[1],//function,
                              ERROR_ILLEGAL_DATA_ADDRESS,//error,
                              outputPacket);//output_data
        default:
        {
          dataRegister[idxDataRegister] = (short) result;
          flag = 0;
        }
        }//switch
      //qDebug()<<"result= "<<dataRegister[idxDataRegister];
    }//for
  if(flag)//незначащие пакеты недопустимы
    return Error_modbus(adrUnit, // address,
                        outputPacket[1],//function,
                        ERROR_ILLEGAL_DATA_ADDRESS,//error,
                        outputPacket);//output_data
  superPostReadAction();//action после чтения

  int idxOutputPacket = 0;
//adrUnit
  outputPacket[idxOutputPacket] = (unsigned char)adrUnit;
  idxOutputPacket++;
//numFunc
  idxOutputPacket++;
//cnt
  outputPacket[idxOutputPacket] = (unsigned char)cntReg*2;
  idxOutputPacket++;
//data
  for(int i=0; i<idxDataRegister; i++)
    {
//Mdata
      outputPacket[idxOutputPacket] = (unsigned char)((dataRegister[i]>>8)&0xFF);
      idxOutputPacket++;
//Ldata
      outputPacket[idxOutputPacket] = (unsigned char)(dataRegister[i]&0xFF);
      idxOutputPacket++;
    }//for
  return idxOutputPacket;
}//outputFunc3PacketEncoder(int adrUnit, int adrReg, int cntReg)

int outputFunc1PacketEncoder(int adrUnit, int adrBit, int cntBit)
{
//выходной кодировщик 1 функции
  short dataRegister[130];
  for(int i=0; i<128; i++) dataRegister[i]=0;
  int   idxDataBit = 0;
  int   flag = 1;

  superPreReadAction();//action до чтения
  for(; idxDataBit<cntBit; idxDataBit++)
    {
      int result = superReaderBit(adrBit+ idxDataBit);
      int idxReg = idxDataBit/16;

      switch(result)
        {
        case MARKER_OUTPERIMETR:
          //dataRegister[idxReg] = 0;
          break;
        case MARKER_ERRORPERIMETR:
          dataRegister[idxReg] = -2;
//          break;
          return Error_modbus(adrUnit, // address,
                              outputPacket[1],//function,
                              ERROR_ILLEGAL_DATA_ADDRESS,//error,
                              outputPacket);//output_data
        default:
        {
          dataRegister[idxReg] |= (result<<(idxDataBit%16));
          flag = 0;
        }
        }//switch
      //qDebug()<<"result= "<<dataRegister[idxReg];
    }//for
  if(flag)//незначащие пакеты недопустимы
    return Error_modbus(adrUnit, // address,
                        outputPacket[1],//function,
                        ERROR_ILLEGAL_DATA_ADDRESS,//error,
                        outputPacket);//output_data
  superPostReadAction();//action после чтения

  int idxOutputPacket = 0;
//adrUnit
  outputPacket[idxOutputPacket] = (unsigned char)adrUnit;
  idxOutputPacket++;
//numFunc
  idxOutputPacket++;

  if(cntBit<9)
    {
//cnt
      outputPacket[idxOutputPacket] = (unsigned char)1;
      idxOutputPacket++;
//data
      outputPacket[idxOutputPacket] = (unsigned char)dataRegister[0];
      idxOutputPacket++;
    }//if
  else
    {
//cnt
      int cntReg = cntBit/16;
      if(cntBit%16) cntReg++;
      outputPacket[idxOutputPacket] = (unsigned char)cntReg*2;
      idxOutputPacket++;
//data
      for(int i=0; i<cntReg; i++)
        {
//Ldata
          outputPacket[idxOutputPacket] = (unsigned char)(dataRegister[i]&0xFF);
          idxOutputPacket++;
//Mdata
          outputPacket[idxOutputPacket] = (unsigned char)((dataRegister[i]>>8)&0xFF);
          idxOutputPacket++;
        }//for
    }
  return idxOutputPacket;
}//outputFunc3PacketEncoder(int adrUnit, int adrReg, int cntReg)

/**************************************/
//action до чтения
/**************************************/
void superPreReadAction(void)
{
  int i=0;
  for(; i<TOTAL_COMPONENT; i++)
    {
      config_array[i].preReadAction();
    }//for
}//superPreReadAction
/**************************************/
//action после чтения
/**************************************/
void superPostReadAction(void)
{
  int i=0;
  for(; i<TOTAL_COMPONENT; i++)
    {
      config_array[i].postReadAction();
    }//for
}//superPostReadAction

/**************************************/
//action до записи
/**************************************/
void superPreWriteAction(void)
{
  int i=0;
  for(; i<TOTAL_COMPONENT; i++)
    {
      config_array[i].preWriteAction();
    }//for
}//superPreWriteAction
/**************************************/
//action после записи
/**************************************/
int superPostWriteAction(void)
{
//сформировать пакет ошибки
  if(upravlFlag==0)  //флаг пакетов управления 1-есть управление
    {
      switch(pointInterface)  //метка интерфейса 0-USB 1-RS485
        {
        case 0://USB
          if(config_settings_modified&MASKA_FOR_BIT(BIT_MENU_LOCKS) ||
              config_settings_modified&MASKA_FOR_BIT(BIT_RS485_LOCKS))
            {
              return Error_modbus(inputPacket[0], // address,
                                  inputPacket[1],//function,
                                  ERROR_SLAVE_DEVICE_BUSY,//error,
                                  outputPacket);//output_data
            }//if
          break;
        case 1:
          if(config_settings_modified&MASKA_FOR_BIT(BIT_MENU_LOCKS) ||
              config_settings_modified&MASKA_FOR_BIT(BIT_USB_LOCKS))
            {
              return Error_modbus(inputPacket[0], // address,
                                  inputPacket[1],//function,
                                  ERROR_SLAVE_DEVICE_BUSY,//error,
                                  outputPacket);//output_data
            }//if
          break;
        }//switch
    }//if

  int i=0;
  for(; i<TOTAL_COMPONENT; i++)
    {
      switch(config_array[i].postWriteAction())//invalid param
      {
        case 2:
        return Error_modbus(inputPacket[0], // address,
                            inputPacket[1],//function,
                            ERROR_ILLEGAL_DATA_VALUE,//error,
                            outputPacket);//output_data
        case 3:
        return Error_modbus(inputPacket[0], // address,
                            inputPacket[1],//function,
                            ERROR_SLAVE_DEVICE_BUSY,//error,
                            outputPacket);//output_data
      }//switch
    }//for
  return 0;
}//superPostWriteAction

/**************************************/
//регистровый читатель 20-й функции
/**************************************/
int superReader20Pro(int offsetRegister)
{
  uint32_t word = buffer_for_USB_read_record_pr_err[8] | (buffer_for_USB_read_record_pr_err[9] << 8);
  switch(offsetRegister)
    {
    case 0://статус события
      return ((word >> 15) & 0x1);
    case 1://год месяц
      return ((buffer_for_USB_read_record_pr_err[7] << 8) | buffer_for_USB_read_record_pr_err[6]);
    case 2://день часы
      return ((buffer_for_USB_read_record_pr_err[5] << 8) | buffer_for_USB_read_record_pr_err[4]);
    case 3://минуты секунды
      return ((buffer_for_USB_read_record_pr_err[3] << 8) | buffer_for_USB_read_record_pr_err[2]);
    case 4://миллисекунды
      return ((buffer_for_USB_read_record_pr_err[1] >> 4)*10 + (buffer_for_USB_read_record_pr_err[1] &  0xf))*100;
    case 5://идентификатор объекта
      return (word & 0x7fff);
    }//switch
  return 0xAA;//просто так
}//superReader20Pro(int offsetRegister)

/**************************************/
//регистровый читатель 20-й функции
/**************************************/
int superReader20(int offsetRegister)
{
  switch(pointInterface)  //метка интерфейса 0-USB 1-RS485
    {
    case 0:
    {
      //USB
      uint32_t word = buffer_for_USB_read_record_log[8] | (buffer_for_USB_read_record_log[9] << 8) | (buffer_for_USB_read_record_log[10] << 16) | (buffer_for_USB_read_record_log[11] << 24);
      uint32_t number = buffer_for_USB_read_record_log[12] | (buffer_for_USB_read_record_log[13] << 8);
      switch(offsetRegister)
        {
        case 0://статус события
          return ((word >> 31) & 0x1);
        case 1://год месяц
          return ((buffer_for_USB_read_record_log[7] << 8) | buffer_for_USB_read_record_log[6]);
        case 2://день часы
          return ((buffer_for_USB_read_record_log[5] << 8) | buffer_for_USB_read_record_log[4]);
        case 3://минуты секунды
          return ((buffer_for_USB_read_record_log[3] << 8) | buffer_for_USB_read_record_log[2]);
        case 4://миллисекунды
          return 100*((buffer_for_USB_read_record_log[1]/16)*10 + (buffer_for_USB_read_record_log[1]%16));


        case 5://идентификатор объекта
          return (word & 0xffff);
        case 6://идентификатор объекта
          return ((word >> 16) & 0x7fff);
        case 7://значение
          return (number & 0xffff);
        case 8://значение
          return ((number >> 16) & 0xffff);
        }//switch
    }
    break;
    case 1:
    {
      //RS485
      uint32_t word = buffer_for_RS485_read_record_log[8] | (buffer_for_RS485_read_record_log[9] << 8) | (buffer_for_RS485_read_record_log[10] << 16) | (buffer_for_RS485_read_record_log[11] << 24);
      uint32_t number = buffer_for_RS485_read_record_log[12] | (buffer_for_RS485_read_record_log[13] << 8);
      switch(offsetRegister)
        {
        case 0://статус события
          return ((word >> 31) & 0x1);
        case 1://год месяц
          return ((buffer_for_RS485_read_record_log[7] << 8) | buffer_for_RS485_read_record_log[6]);
        case 2://день часы
          return ((buffer_for_RS485_read_record_log[5] << 8) | buffer_for_RS485_read_record_log[4]);
        case 3://минуты секунды
          return ((buffer_for_RS485_read_record_log[3] << 8) | buffer_for_RS485_read_record_log[2]);
        case 4://миллисекунды
          return buffer_for_RS485_read_record_log[1];
        case 5://идентификатор объекта
          return (word & 0xffff);
        case 6://идентификатор объекта
          return ((word >> 16) & 0x7fff);
        case 7://значение
          return (number & 0xffff);
        case 8://значение
          return ((number >> 16) & 0xffff);
        }//switch
    }
    break;
    }//switch
  return 0xAA;//просто так
}//superReader20(int fileNumber, int offsetRegister)

/**************************************/
//регистровый читатель
/**************************************/
int superReaderRegister(int adrReg)
{
  int result=0;
  int i=0;
  for(; i<TOTAL_COMPONENT; i++)
    {
      result = config_array[i].getModbusRegister(adrReg);
      if(!(result==MARKER_OUTPERIMETR)) break;
//      if(result==MARKER_ERRORPERIMETR) break;
    }//for
  if(i==TOTAL_COMPONENT) result = MARKER_OUTPERIMETR;
  return result;
}//superReaderRegister()

/**************************************/
//регистровый писатель
/**************************************/
int superWriterRegister(int adrReg, int dataReg)
{
  int result=0;
  int i=0;
  for(; i<TOTAL_COMPONENT; i++)
    {
      result = config_array[i].setModbusRegister(adrReg, dataReg);
      if(!(result==MARKER_OUTPERIMETR)) break;
    }//for
  if(i==TOTAL_COMPONENT) result = MARKER_OUTPERIMETR;
  return result;
}//superWriterRegister(int adrReg, int dataReg)

/**************************************/
//компонентная активация
/**************************************/
void superConfig_and_settings(void)
{
  for(int i=0; i<TOTAL_COMPONENT; i++)
    {
      config_array[i].config_and_settings();//action активации
    }//for
  upravlconfig_and_settings=0;//флаг активации компонента
}//superConfig_and_settings

/**************************************/
//bit читатель
/**************************************/
int superReaderBit(int adrBit)
{
  int result=0;
  int i=0;
  for(; i<TOTAL_COMPONENT; i++)
    {
      result = config_array[i].getModbusBit(adrBit);
      if(!(result==MARKER_OUTPERIMETR)) break;
//      if(result==MARKER_ERRORPERIMETR) break;
    }//for
  if(i==TOTAL_COMPONENT) result = MARKER_OUTPERIMETR;
  return result;
}//superReaderBit()

/**************************************/
//bit писатель
/**************************************/
int superWriterBit(int adrBit, int dataBit)
{
  int result=0;
  int i=0;
  for(; i<TOTAL_COMPONENT; i++)
    {
      result = config_array[i].setModbusBit(adrBit, dataBit);
      if(!(result==MARKER_OUTPERIMETR)) break;
//      if(result==MARKER_ERRORPERIMETR) break;
//      if(result==MARKER_ERRORDIAPAZON) break;
    }//for
  if(i==TOTAL_COMPONENT) result = MARKER_OUTPERIMETR;
  return result;
}//superReaderRegister()

/**************************************/
//установка оперативных маркеров
/**************************************/
void superSetOperativMarker(COMPONENT_OBJ *component, int adrReg)
{
  if(component->operativMarker[0]<0) component->operativMarker[0] = adrReg;
  else component->operativMarker[1] = adrReg;
}//superSetOperativMarker(COMPONENT_OBJ component, int adrReg)

/***********************************************************************************/
//Додавання числа до CRC суми
/***********************************************************************************/
unsigned short int  AddCRC(unsigned char inpbyte, unsigned short int oldCRC)
{
  unsigned short int v,temp;
  int i;
  unsigned char bt,m;

  bt = inpbyte;
  v  = oldCRC;

  for (i=0; i<8; i++)
    {
      temp = v;
      v = v >> 1;
      m = bt >> i;
      if (((temp ^m) & 1)== 1) v = v ^ 0xa001;
    }
  return v;
}
/***********************************************************************************/
//Функція відповіді по протоколу Modbus-RTU на помилку
/***********************************************************************************/
int Error_modbus(unsigned int address, unsigned int function, unsigned int error, unsigned char *output_data)
{
  output_data[0] = address & 0xff;
  output_data[1] = 0x80 | (function & 0xff);
  output_data[2] = error & 0xff;
  return 3;
}

void superSetTempWriteArray(int dataReg)
{
//записать в буфер
  if(indexTW>=MAXIMUMTW) return;
  tempWriteArray[indexTW] = dataReg;
  indexTW++;//индекс буфера записи
}//superSetTempWriteArray(int dataReg)

int superFindTempWriteArrayOffset(int adr)
{
//найти смещение TempWriteArray
  int iComponentOffset=0;
  int i=0;
  for(; i<TOTAL_COMPONENT; i++)
    {
      if(config_array[i].operativMarker[0]<0) continue;
      if(config_array[i].operativMarker[0]<adr)
        {
          if(config_array[i].operativMarker[1]<0) iComponentOffset++;
          else iComponentOffset+=(config_array[i].operativMarker[1]-config_array[i].operativMarker[0]+1);
        }//if
    }//for
  return iComponentOffset;
}//superFindTempWriteArrayOffset(int adr)

int finderMinimum(unsigned int data, int size, unsigned int *arr)
{
  unsigned int minData = data;
  unsigned int dataOld = 2000000000;
  for(int i=0; i<size; i++)
    {
      if(arr[i]==0) break;
      if(arr[i]<= minData) continue;
      if(arr[i]< dataOld) dataOld = arr[i];
    }//for
  if(dataOld == 2000000000) return 0;
  return dataOld;
}//finderMinimum(int)

void finderDubl(int idx, int size, unsigned int *arr)
{
  unsigned int data = arr[idx];
  if(data==0) return;
  for(int i=idx+1; i<size; i++) if(arr[i]==data) arr[i]=0;
}//finderDubl(int idx, int *arr) {

void superSortParam(int size, unsigned int *prm)
{
  unsigned int tmparr[150];//
  if(size>130) return;
  for(int i=0; i<size; i++)tmparr[i]=0;
//устранение повторов
  for(int i=0; i<size; i++) finderDubl(i, size, prm);
//устранение пробелов
  unsigned int tmpi=0;
  for(int i=0; i<size; i++)
    {
      if(prm[i])
        {
          tmparr[tmpi] = prm[i];
          prm[i]=0;
          tmpi++;
        }//if
    }//for

  if(tmpi)
    {
//сортировка
      unsigned int dataMin = finderMinimum(0, size, tmparr);
      prm[0] = dataMin;
      for(int i=1; i<size; i++)
        {
          if(tmparr[i]==0) break;
          dataMin = finderMinimum(dataMin, size, tmparr);
          prm[i] = dataMin;
        }//for
    }//if(tmpi)
}//superSortParam(int size, int *prm)

int superControlParam(int param)
{
//контроль параметров ранжирования
  int id  = (param>>8)&0xff;//id блока
  unsigned int cnt = param&0xff;//номер блока
//int num = param&0xffff;//номер выхода
  if(param==0) return 0;
  switch(id)
    {
    case _ID_FB_FIRST_ALL:
      if(cnt>1)return 1;
      break;
    case ID_FB_INPUT:
      if(cnt==0)return 1;
      if(cnt>current_config.n_input) return 1;
      break;
    case ID_FB_OUTPUT:
      if(cnt==0)return 1;
      if(cnt>current_config.n_output) return 1;
      break;
    case ID_FB_LED:
      if(cnt==0)return 1;
      if(cnt>current_config.n_led) return 1;
      break;
    case ID_FB_BUTTON:
      if(cnt==0)return 1;
      if(cnt>current_config.n_button) return 1;
      break;

    case ID_FB_ALARM:
      if(cnt==0)return 1;
      if(cnt>current_config.n_alarm) return 1;
      break;
    case ID_FB_GROUP_ALARM:
      if(cnt==0)return 1;
      if(cnt>4) return 1;
      break;
    case ID_FB_AND:
      if(cnt==0)return 1;
      if(cnt>current_config.n_and) return 1;
      break;
    case ID_FB_OR:
      if(cnt==0)return 1;
      if(cnt>current_config.n_or) return 1;
      break;
    case ID_FB_XOR:
      if(cnt==0)return 1;
      if(cnt>current_config.n_xor) return 1;
      break;
    case ID_FB_NOT:
      if(cnt==0)return 1;
      if(cnt>current_config.n_not) return 1;
      break;

    case ID_FB_TIMER:
      if(cnt==0)return 1;
      if(cnt>current_config.n_timer) return 1;
      break;
    case ID_FB_TRIGGER:
      if(cnt==0)return 1;
      if(cnt>current_config.n_trigger) return 1;
      break;

    case ID_FB_MEANDER:
      if(cnt==0)return 1;
      if(cnt>current_config.n_meander) return 1;
      break;
    case ID_FB_TU:
      if(cnt==0)return 1;
      if(cnt>current_config.n_tu) return 1;
      break;
    case ID_FB_TS:
      if(cnt==0)return 1;
      if(cnt>current_config.n_ts) return 1;
      break;

    case ID_FB_EVENT_LOG:
      if(cnt==0)return 1;
      if(cnt>current_config.n_log) return 1;
      break;
    default:
      return 1;
    }//switch id
  return 0;
}//superControlParam

int superControlParam_gi(int param)
{
//контроль параметров gi
  int id  = (param>>8)&0xff;//id блока
  unsigned int cnt = param&0xff;//номер блока
//int num = param&0xffff;//номер выхода
  if(param==0) return 0;
  switch(id)
    {

    case ID_FB_MEANDER:
      if(cnt==0)return 1;
      if(cnt>current_config.n_meander) return 1;
      break;
    default:
      return 1;
    }//switch id
  return 0;
}//superControlParam_gi

int superValidParam(uint32_t param)
{
//контроль валидности параметров
//параметр не должен быть наполовину нулевым
  if(param==0) return 0;
//  if(!(param&0x0000FFFF)) return 1;//номер выхода не может быть 0
//  if(!(param&0xFFFF0000)) return 1;
//кореляции
//  int id  = (param>>24)&0xff;//id блока
//  int out = param&0xffff;//номер выхода
  uint32_t id   = (param >> SFIFT_PARAM_ID ) & MASKA_PARAM_ID ;
  uint32_t n    = (param >> SFIFT_PARAM_N  ) & MASKA_PARAM_N  ;
  uint32_t out  = (param >> SFIFT_PARAM_OUT) & MASKA_PARAM_OUT;
  if ((id >= _ID_FB_FIRST_ALL) && (id < _ID_FB_LAST_ALL))
    {
      //Роблю тільки для USB, так як не заню , як визначити звідки іде запит
      uint32_t n_nodes;
      switch (id)
        {
        case ID_FB_CONTROL_BLOCK:
        {
          n_nodes = 1;
          break;
        }
        case ID_FB_INPUT:
        {
          n_nodes = current_config.n_input;
          break;
        }
        case ID_FB_OUTPUT:
        {
          n_nodes = current_config.n_output;
          break;
        }
        case ID_FB_LED:
        {
          n_nodes = current_config.n_led;
          break;
        }
        case ID_FB_BUTTON:
        {
          n_nodes = current_config.n_button;
          break;
        }
        case ID_FB_ALARM:
        {
          n_nodes = current_config.n_alarm;
          break;
        }
        case ID_FB_GROUP_ALARM:
        {
          n_nodes = current_config.n_group_alarm;
          break;
        }
        case ID_FB_AND:
        {
          n_nodes = current_config.n_and;
          break;
        }
        case ID_FB_OR:
        {
          n_nodes = current_config.n_or;
          break;
        }
        case ID_FB_XOR:
        {
          n_nodes = current_config.n_xor;
          break;
        }
        case ID_FB_NOT:
        {
          n_nodes = current_config.n_not;
          break;
        }
        case ID_FB_TIMER:
        {
          n_nodes = current_config.n_timer;
          break;
        }
        case ID_FB_TRIGGER:
        {
          n_nodes = current_config.n_trigger;
          break;
        }
        case ID_FB_MEANDER:
        {
          n_nodes = current_config.n_meander;
          break;
        }
        case ID_FB_TU:
        {
          n_nodes = current_config.n_tu;
          break;
        }
        case ID_FB_TS:
        {
          n_nodes = current_config.n_ts;
          break;
        }
        case ID_FB_EVENT_LOG:
        {
          n_nodes = 1;
          break;
        }
        default:
        {
          return 1;
        }
        }
      if ((n   == 0) || (n > n_nodes)) return 1;
      if ((out == 0) || (out > number_output_signals_logical_nodes[id - 1])) return 1;
    }
  else return 1;
//  switch(id)
//    {
//    case _ID_FB_FIRST_ALL:
//      if(out>FIX_BLOCK_SIGNALS_OUT) return 1;//номер выхода не может быть больше
//      break;
//    case ID_FB_INPUT:
//      if(out>INPUT_SIGNALS_OUT) return 1;//номер выхода не может быть больше
//      break;
//    case ID_FB_OUTPUT:
//      if(out>OUTPUT_LED_SIGNALS_OUT) return 1;//номер выхода не может быть больше
//      break;
//    case ID_FB_LED:
//      if(out>OUTPUT_LED_SIGNALS_OUT) return 1;//номер выхода не может быть больше
//      break;
//    case ID_FB_BUTTON:
//      if(out>BUTTON_SIGNALS_OUT) return 1;//номер выхода не может быть больше
//      break;
//
//    case ID_FB_ALARM:
//      if(out>ALARM_SIGNALS_OUT) return 1;//номер выхода не может быть больше
//      break;
//    case ID_FB_GROUP_ALARM:
//      if(out>GROUP_ALARM_SIGNALS_OUT) return 1;//номер выхода не может быть больше
//      break;
//    case ID_FB_AND:
//      if(out>STANDARD_LOGIC_SIGNALS_OUT) return 1;//номер выхода не может быть больше
//      break;
//    case ID_FB_OR:
//      if(out>STANDARD_LOGIC_SIGNALS_OUT) return 1;//номер выхода не может быть больше
//      break;
//    case ID_FB_XOR:
//      if(out>STANDARD_LOGIC_SIGNALS_OUT) return 1;//номер выхода не может быть больше
//      break;
//    case ID_FB_NOT:
//      if(out>STANDARD_LOGIC_SIGNALS_OUT) return 1;//номер выхода не может быть больше
//      break;
//
//    case ID_FB_TIMER:
//      if(out>TIMER_SIGNALS_OUT) return 1;//номер выхода не может быть больше
//      break;
//    case ID_FB_TRIGGER:
//      if(out>TRIGGER_SIGNALS_OUT) return 1;//номер выхода не может быть больше
//      break;
//
//    case ID_FB_MEANDER:
//      if(out>MEANDER_SIGNALS_OUT) return 1;//номер выхода не может быть больше
//      break;
//    case ID_FB_TU:
//      if(out>TU_SIGNALS_OUT) return 1;//номер выхода не может быть больше
//      break;
//    case ID_FB_TS:
//      if(out>TS_SIGNALS_OUT) return 1;//номер выхода не может быть больше
//      break;
//
//    case ID_FB_EVENT_LOG:
//      if(out>EVENT_LOG_SIGNALS_OUT) return 1;//номер выхода не может быть больше
//      break;
//    default:
//      return 1;
//    }//switch id
  return 0;
}//

