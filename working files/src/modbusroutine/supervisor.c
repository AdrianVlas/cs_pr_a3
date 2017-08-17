//#include <QtWidgets>
//#include "loghandler.h"

#include "header.h"

int inputPacketParser(void);
void inputPacketParserUSB(void);
void inputPacketParserRS485(void);
unsigned short int  AddCRC(unsigned char inpbyte, unsigned short int oldCRC);
int Error_modbus(unsigned int address, unsigned int function, unsigned int error, unsigned char *output_data);
int outputFunc16PacketEncoder(int adrUnit, int adrReg, int cntReg);
int outputFunc15PacketEncoder(int adrUnit, int adrBit, int cntBit);
int outputFunc6PacketEncoder(int adrUnit, int adrReg, int dataReg);
int outputFunc5PacketEncoder(int adrUnit, int adrBit, int dataBit);
int outputFunc3PacketEncoder(int adrUnit, int adrReg, int cntReg);
int outputFunc1PacketEncoder(int adrUnit, int adrReg, int cntReg);
void superrestart_monitoring_RS485(void);

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

/**************************************/
//разбор входного пакета USB
/**************************************/
void inputPacketParserUSB(void)
{
 pointInterface=0;//метка интерфейса 0-USB 1-RS485
 received_count = &usb_received_count;

 inputPacket = usb_received;
 outputPacket = outputPacket_USB;
  //Перевірка контрольної суми
  unsigned short CRC_sum;
  CRC_sum = 0xffff;
  for (int index = 0; index < (*received_count-2); index++) CRC_sum = AddCRC(*(inputPacket + index),CRC_sum);
  if((CRC_sum & 0xff)  != *(inputPacket+*received_count-2)) return;
  if ((CRC_sum >> 8  ) != *(inputPacket+*received_count-1)) return;
  if(inputPacket[0]!=settings_fix_prt.address) return;

 switch(inputPacket[1]) {//номер ф-ции
  case 1:
  case 2:
  case 3:
  case 4:
  break;
  case 5:
  case 6:
  case 15:
  case 16:
	 if(config_settings_modified&MASKA_FOR_BIT(BIT_MENU_LOCKS) ||//) return;
	    config_settings_modified&MASKA_FOR_BIT(BIT_RS485_LOCKS)) { //return;
                 sizeOutputPacket=Error_modbus(inputPacket[0], // address,
                              0x80|inputPacket[1],//function,
                              0x55,//error,
                              outputPacket);//output_data
  CRC_sum = 0xffff;
  for (int index = 0; index < sizeOutputPacket; index++) CRC_sum = AddCRC((*(outputPacket + index)) ,CRC_sum);
  *(outputPacket + sizeOutputPacket)  = CRC_sum & 0xff;
  *(outputPacket + sizeOutputPacket+1)  = CRC_sum >> 8;
  sizeOutputPacket += 2;

              usb_transmiting_count = sizeOutputPacket;
              for (int i = 0; i < usb_transmiting_count; i++) usb_transmiting[i] = outputPacket[i];
              data_usb_transmiting = true;
              return;
            }//if
  break;
  default:return;
 }//switch


 if(inputPacketParser()==0) return;

 switch(inputPacket[1]) {//номер ф-ции
  case 1:
  case 2:
  case 3:
  case 4:
  break;
  case 5:
  case 6:
  case 15:
  case 16:
  if(!(outputPacket[1]&0x80))//function
      config_settings_modified |= MASKA_FOR_BIT(BIT_USB_LOCKS);
  break;
  default:return;
 }//switch

 usb_transmiting_count = sizeOutputPacket;
 for (int i = 0; i < usb_transmiting_count; i++) usb_transmiting[i] = outputPacket[i];
 data_usb_transmiting = true;
 
}//inputPacketParserUSB(void)
/**************************************/
//разбор входного пакета RS485
/**************************************/
void inputPacketParserRS485(void)
{
 pointInterface=1;//метка интерфейса 0-USB 1-RS485
inputPacket = RxBuffer_RS485;

received_count = &RxBuffer_RS485_count;
 outputPacket = outputPacket_RS485;
  //Перевірка контрольної суми
  unsigned short CRC_sum;
  CRC_sum = 0xffff;
  for (int index = 0; index < (*received_count-2); index++) CRC_sum = AddCRC(*(inputPacket + index),CRC_sum);
  if((CRC_sum & 0xff)  != *(inputPacket+*received_count-2) ||//) return;
     (CRC_sum >> 8  ) != *(inputPacket+*received_count-1)) {superrestart_monitoring_RS485();return;}
  if(inputPacket[0]!=settings_fix_prt.address) {superrestart_monitoring_RS485();return;}

 switch(inputPacket[1]) {//номер ф-ции
  case 1:
  case 2:
  case 3:
  case 4:
  break;
  case 5:
//   if(received_count!=8) return;
  case 6:
  case 15:
  case 16:
	 if(config_settings_modified&MASKA_FOR_BIT(BIT_MENU_LOCKS) ||//) return;
	    config_settings_modified&MASKA_FOR_BIT(BIT_RS485_LOCKS)) { //return;
             sizeOutputPacket=Error_modbus(inputPacket[0], // address,
                              0x80|inputPacket[1],//function,
                              0x55,//error,
                              outputPacket);//output_data
  CRC_sum = 0xffff;
  for (int index = 0; index < sizeOutputPacket; index++) CRC_sum = AddCRC((*(outputPacket + index)) ,CRC_sum);
  *(outputPacket + sizeOutputPacket)  = CRC_sum & 0xff;
  *(outputPacket + sizeOutputPacket+1)  = CRC_sum >> 8;
  sizeOutputPacket += 2;

             TxBuffer_RS485_count = sizeOutputPacket;
             for (int i = 0; i < TxBuffer_RS485_count; i++) TxBuffer_RS485[i] = outputPacket[i];
             start_transmint_data_via_RS_485(TxBuffer_RS485_count);
             return;
            }//if
  break;
  default:{superrestart_monitoring_RS485();return;}
 }//switch

// received_count = &usb_received_count;
// outputPacket = outputPacket_RS485;
 if(inputPacketParser()==0) {superrestart_monitoring_RS485();return;}

 switch(inputPacket[1]) {//номер ф-ции
  case 1:
  case 2:
  case 3:
  case 4:
  break;
  case 5:
  case 6:
  case 15:
  case 16:
  if(!(outputPacket[1]&0x80))//function
       config_settings_modified |= MASKA_FOR_BIT(BIT_RS485_LOCKS);
  break;
  default:return;
 }//switch

TxBuffer_RS485_count = sizeOutputPacket;
for (int i = 0; i < TxBuffer_RS485_count; i++) TxBuffer_RS485[i] = outputPacket[i];
start_transmint_data_via_RS_485(TxBuffer_RS485_count);

// usb_transmiting_count = sizeOutputPacket;
// for (int i = 0; i < usb_transmiting_count; i++) usb_transmiting[i] = outputPacket[i];
// data_usb_transmiting = true;
}//inputPacketParserRS485(void)
//void superrestart_monitoring_RS485() {
 //для продовження приймати нові пакети
//restart_monitoring_RS485(); //для продовження приймати нові пакети
//}//superrestart_monitoring_RS485

/**************************************/
//разбор входного пакета
/**************************************/
int inputPacketParser(void)
{
/*
  //Перевірка контрольної суми
  unsigned short CRC_sum;
  CRC_sum = 0xffff;
  for (int index = 0; index < (*received_count-2); index++) CRC_sum = AddCRC(*(inputPacket + index),CRC_sum);
  if((CRC_sum & 0xff)  != *(inputPacket+*received_count-2)) return 0;
  if ((CRC_sum >> 8  ) != *(inputPacket+*received_count-1)) return 0;
*/
  int adrUnit = inputPacket[0];
  int numFunc = inputPacket[1];//номер ф-ции
  //Перевірка address
//  if(adrUnit!=settings_fix.address) return 0;

  sizeOutputPacket = 0;
  indexTW = 0;//индекс буфера записи
  switch(numFunc)
    {
    case 2:
    case 1:
    {
      globalbeginAdrBit  = (unsigned int)inputPacket[3] +256*(unsigned int)inputPacket[2];
      globalcntBit      = (unsigned int)inputPacket[5] +256*(unsigned int)inputPacket[4];
      if(globalcntBit>125) return 0;//слишком длинный пакет
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
      switch(dataBit) {
        case 0xFF00:
         dataBit = 1;
        break;
        case 0x0000:
         dataBit = 0;
        break;
        default: {
          sizeOutputPacket = Error_modbus(adrUnit, // address,
                              numFunc|0x80,//function,
                              3,//error,
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
    default: return 0;
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
//       break;
          return Error_modbus(adrUnit, // address,
                              outputPacket[1],//function,
                              10,//error,
                              outputPacket);//output_data

        case MARKER_ERRORDIAPAZON:
          result = -3;
//       break;
          return Error_modbus(adrUnit, // address,
                              outputPacket[1],//function,
                              10,//error,
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
                        10,//error,
                        outputPacket);//output_data

  superPostWriteAction();//action после записи

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
//       break;
          return Error_modbus(adrUnit, // address,
                              outputPacket[1],//function,
                              10,//error,
                              outputPacket);//output_data

        case MARKER_ERRORDIAPAZON:
          result = -3;
//       break;
          return Error_modbus(adrUnit, // address,
                              outputPacket[1],//function,
                              10,//error,
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
                        10,//error,
                        outputPacket);//output_data

  superPostWriteAction();//action после записи

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
//      break;
          return Error_modbus(adrUnit, // address,
                              outputPacket[1],//function,
                              10,//error,
                              outputPacket);//output_data
    case MARKER_ERRORPERIMETR:
      result = -2;
//      break;
          return Error_modbus(adrUnit, // address,
                              outputPacket[1],//function,
                              10,//error,
                              outputPacket);//output_data
    case MARKER_ERRORDIAPAZON:
      result = -3;
//      break;
          return Error_modbus(adrUnit, // address,
                              outputPacket[1],//function,
                              10,//error,
                              outputPacket);//output_data
    }//switch
  //qDebug()<<"result= "<<result;

  superPostWriteAction();//action после записи

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
//      break;
          return Error_modbus(adrUnit, // address,
                              outputPacket[1],//function,
                              10,//error,
                              outputPacket);//output_data
    case MARKER_ERRORPERIMETR:
      result = -2;
//      break;
          return Error_modbus(adrUnit, // address,
                              outputPacket[1],//function,
                              10,//error,
                              outputPacket);//output_data
    case MARKER_ERRORDIAPAZON:
      result = -3;
//      break;
          return Error_modbus(adrUnit, // address,
                              outputPacket[1],//function,
                              10,//error,
                              outputPacket);//output_data
    }//switch

  superPostWriteAction();//action после записи

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
                              10,//error,
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
                        10,//error,
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
                              10,//error,
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
                        10,//error,
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
void superPostWriteAction(void)
{
  int i=0;
  for(; i<TOTAL_COMPONENT; i++)
    {
      config_array[i].postWriteAction();
    }//for
}//superPostWriteAction

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
      if(result==MARKER_ERRORPERIMETR) break;
    }//for
  if(i==TOTAL_COMPONENT) result = MARKER_OUTPERIMETR;
  //qDebug()<<"("<<i<<")";
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
      if(result==MARKER_ERRORPERIMETR) break;
      if(result==MARKER_ERRORDIAPAZON) break;
    }//for
  if(i==TOTAL_COMPONENT) result = MARKER_OUTPERIMETR;
  //qDebug()<<"("<<i<<")";
  return result;
}//superWriterRegister(int adrReg, int dataReg)

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
      if(result==MARKER_ERRORPERIMETR) break;
    }//for
  if(i==TOTAL_COMPONENT) result = MARKER_OUTPERIMETR;
  //qDebug()<<"("<<i<<")";
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
      if(result==MARKER_ERRORPERIMETR) break;
      if(result==MARKER_ERRORDIAPAZON) break;
    }//for
  if(i==TOTAL_COMPONENT) result = MARKER_OUTPERIMETR;
  //qDebug()<<"("<<i<<")";
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

int superFindTempWriteArrayOffset(int adr) {
//найти смещение TempWriteArray
  int iComponentOffset=0;
  int i=0;
  for(; i<TOTAL_COMPONENT; i++)
    {
     if(config_array[i].operativMarker[0]<0) continue;
     if(config_array[i].operativMarker[0]<adr) {
       if(config_array[i].operativMarker[1]<0) iComponentOffset++;
       else iComponentOffset+=(config_array[i].operativMarker[1]-config_array[i].operativMarker[0]+1);
     }//if
    }//for
  return iComponentOffset;
}//superFindTempWriteArrayOffset(int adr) 

 int finderMinimum(unsigned int data, int size, unsigned int *arr) {
unsigned int minData = data;
unsigned int dataOld = 2000000000;
for(int i=0; i<size; i++) {
 if(arr[i]==0) break;
 if(arr[i]<= minData) continue;
 if(arr[i]< dataOld) dataOld = arr[i];
}//for
if(dataOld == 2000000000) return 0;
return dataOld;
}//finderMinimum(int)

 void finderDubl(int idx, int size, unsigned int *arr) {
unsigned int data = arr[idx];
if(data==0) return;
for(int i=idx+1; i<size; i++) if(arr[i]==data) arr[i]=0;
}//finderDubl(int idx, int *arr) {

 void superSortParam(int size, unsigned int *prm)
{
unsigned int tmparr[10];//
for(int i=0; i<size; i++)tmparr[i]=0;
//устранение повторов
for(int i=0; i<size; i++) finderDubl(i, size, prm);
//qDebug()<<"  finderDubl= "<<param[0]<<" "<<param[1]<<" "<<param[2]<<" "<<param[3]<<" "<<param[4]<<" "<<param[5]<<" "<<param[6]<<" "<<param[7];
//устранение пробелов
unsigned int tmpi=0;
for(int i=0; i<size; i++) {
if(prm[i]) {
 tmparr[tmpi] = prm[i];
 prm[i]=0;
 tmpi++;
}//if
}//for
//qDebug()<<"finderSpace1= "<<tmparr[0]<<" "<<tmparr[1]<<" "<<tmparr[2]<<" "<<tmparr[3]<<" "<<tmparr[4]<<" "<<tmparr[5]<<" "<<tmparr[6]<<" "<<tmparr[7];
//qDebug()<<"finderSpace2= "<<param[0]<<" "<<param[1]<<" "<<param[2]<<" "<<param[3]<<" "<<param[4]<<" "<<param[5]<<" "<<param[6]<<" "<<param[7];

if(tmpi) {
//сортировка
 unsigned int dataMin = finderMinimum(0, size, tmparr);
 prm[0] = dataMin;
for(int i=1; i<size; i++) {
 if(tmparr[i]==0) break;
 dataMin = finderMinimum(dataMin, size, tmparr);
 prm[i] = dataMin;
}//for
}//if(tmpi)

//qDebug()<<" "<<tmparr[0]<<" "<<tmparr[1]<<" "<<tmparr[2]<<" "<<tmparr[3]<<" "<<tmparr[4]<<" "<<tmparr[5]<<" "<<tmparr[6]<<" "<<tmparr[7];

//qDebug()<<" ";
//qDebug()<<" ";
//qDebug()<<" "<<param[0]<<" "<<param[1]<<" "<<param[2]<<" "<<param[3]<<" "<<param[4]<<" "<<param[5]<<" "<<param[6]<<" "<<param[7];
}//superSortParam(int size, int *prm)

int superControlParam(int param) 
{
//контроль параметров ранжирования
int id  = (param>>8)&0xff;//id блока
unsigned int cnt = param&0xff;//номер блока
//int num = param&0xffff;//номер выхода
if(param==0) return 0;
switch(id){
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
 default: return 1;
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
switch(id){

 case ID_FB_MEANDER:
  if(cnt==0)return 1;
  if(cnt>current_config.n_meander) return 1;
 break;
 default: return 1;
}//switch id
return 0;
}//superControlParam_gi
