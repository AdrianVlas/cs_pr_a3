//#include <QtWidgets>
//#include "loghandler.h"

#include "header.h"

void inputPacketParser();
void inputPacketParserUSB();
void inputPacketParserRS485();
unsigned short int  AddCRC(unsigned char inpbyte, unsigned short int oldCRC);
int Error_modbus(unsigned int address, unsigned int function, unsigned int error, unsigned char *output_data);
int outputFunc16PacketEncoder(int adrUnit, int adrReg, int cntReg);
int outputFunc15PacketEncoder(int adrUnit, int adrBit, int cntBit);
int outputFunc6PacketEncoder(int adrUnit, int adrReg, int dataReg);
int outputFunc5PacketEncoder(int adrUnit, int adrBit);
int outputFunc3PacketEncoder(int adrUnit, int adrReg, int cntReg);
int outputFunc1PacketEncoder(int adrUnit, int adrReg, int cntReg);

unsigned char  *outputPacket;
unsigned char  outputPacket_USB[300];
unsigned char  outputPacket_RS485[300];

int sizeOutputPacket = 0;
unsigned char *inputPacket;// = usb_received;
int *received_count;// = &usb_received_count;

/**************************************/
//разбор входного пакета USB
/**************************************/
void inputPacketParserUSB(void)
{
 inputPacket = usb_received;
 received_count = &usb_received_count;

 outputPacket = outputPacket_USB;
 inputPacketParser();

 usb_transmiting_count = sizeOutputPacket;
 for (int i = 0; i < usb_transmiting_count; i++) usb_transmiting[i] = outputPacket[i];
 data_usb_transmiting = true;
}//inputPacketParserUSB(void)
/**************************************/
//разбор входного пакета RS485
/**************************************/
void inputPacketParserRS485(void)
{
// inputPacket = usb_received;
// received_count = &usb_received_count;
 outputPacket = outputPacket_RS485;
 inputPacketParser();

// usb_transmiting_count = sizeOutputPacket;
// for (int i = 0; i < usb_transmiting_count; i++) usb_transmiting[i] = outputPacket[i];
// data_usb_transmiting = true;
}//inputPacketParserRS485(void)
/**************************************/
//разбор входного пакета
/**************************************/
void inputPacketParser(void)
{
//rprAdresRegister[0] = 0;
//rprAdresRegister[1] = 1;
//rprAdresRegister[2] = 2;
//rprAdresRegister[3] = 3;
//rprAdresRegister[4] = 4;
//rprAdresRegister[5] = 5;
//rprAdresRegister[6] = 6;
  //for(int i=0; i<100; i++) outputPacket[i] = -1;
                     //0-adr 1-func   2-MadrReg    3-LadrReg   4-Mcnt   5-Lcnt
  //byte inputPacket[] {0x1,     3,     0x2,        0xBB,       0x0,     0x7};

                      //0-adr 1-func   2-MadrReg    3-LadrReg   4-Mcnt   5-Lcnt
//  byte inputPacket[] {0x1,      2,     0x3e,        0x80,       0x0,     64};
                    //0-adr   1-func  2-MadrBit    3-LadrBit   4-Mdata   5-Ldata
//  byte inputPacket[] {0x1,      5,     0x56,         0x01,       0xFF,       0};
                    //0-adr  1-func   2-MadrReg    3-LadrReg   4-Mdata   5-Ldata
//  byte inputPacket[] {0x1,      6,     0x2,         0x59,       0x0,       0};
                              //0-adr 1-func   2-MadrBit    3-LadrBit   4-Mcnt    5-Lcnt  6-cntByte  7-data1  
//  unsigned char inputPacket[] {0x1,      15,     0x56,         0x02,       0x0,       2,      1,         1     };
                               //0-adr 1-func   2-MadrReg    3-LadrReg   4-Mcnt    5-Lcnt  6-cntByte  7-Mdata1  8-Ldata1   9-Mdata2  10-Ldata2   11-Mdata3  12-Ldata3   11-Mdata4  12-Ldata4   11-Mdata5  12-Ldata5   11-Mdata6  12-Ldata6   11-Mdata7  12-Ldata7   11-Mdata8  12-Ldata8
//  unsigned char inputPacket[] {0x1,      16,     0x4,         0x81,       0x0,       8,      16,         0,       11,          0,       12,         0,        13,         0,        14,         0,        15,         0,        16,         0,        17,         0,        18};
///*

//    unsigned char *inputPacket = usb_received;
//    int *received_count = &usb_received_count;
  //Перевірка контрольної суми
  unsigned short CRC_sum;
  CRC_sum = 0xffff;
  for (int index = 0; index < (*received_count-2); index++) CRC_sum = AddCRC(*(inputPacket + index),CRC_sum);
  if((CRC_sum & 0xff)  != *(inputPacket+*received_count-2)) return;
  if ((CRC_sum >> 8  ) != *(inputPacket+*received_count-1)) return;
//*/
  int adrUnit = inputPacket[0];
  int numFunc = inputPacket[1];
  //Перевірка address
  if(adrUnit!=settings_fix.address) return;

  sizeOutputPacket = 0;
  indexTW = 0;//индекс буфера записи
  switch(numFunc)
    {
    case 2:
    case 1:
    {
      int adrBit  = (unsigned int)inputPacket[3] +256*(unsigned int)inputPacket[2];
      int cntBit  = (unsigned int)inputPacket[5] +256*(unsigned int)inputPacket[4];
      if(cntBit>125) return;//слишком длинный пакет
      //qDebug()<<"adrUnit="<<adrUnit<<" numFunc="<<numFunc<<" adrBit="<<adrBit<<" cntBit="<<cntBit;
      outputPacket[1] = (unsigned char)numFunc;
      sizeOutputPacket = outputFunc1PacketEncoder(adrUnit, adrBit, cntBit);
    }
    break;
    case 4:
    case 3:
    {
      int adrReg  = (unsigned int)inputPacket[3] +256*(unsigned int)inputPacket[2];
      int cntReg  = (unsigned int)inputPacket[5] +256*(unsigned int)inputPacket[4];
      if(cntReg>125) return;//слишком длинный пакет
      //qDebug()<<"adrUnit="<<adrUnit<<" numFunc="<<numFunc<<" adrReg="<<adrReg<<" cntReg="<<cntReg;
      outputPacket[1] = (unsigned char)numFunc;
      sizeOutputPacket = outputFunc3PacketEncoder(adrUnit, adrReg, cntReg);
    }
    break;
    case 5:
    {
      int adrBit  = (unsigned int)inputPacket[3] +256*(unsigned int)inputPacket[2];
      int dataBit = (unsigned int)inputPacket[5] +256*(unsigned int)inputPacket[4];
      if(dataBit!=0xFF00) return;
//      if(cntReg>125) return;//слишком длинный пакет
      //qDebug()<<"adrUnit="<<adrUnit<<" numFunc="<<numFunc<<" adrBit="<<adrBit;//<<" dataReg="<<dataReg;
      outputPacket[1] = (unsigned char)numFunc;
      sizeOutputPacket = outputFunc5PacketEncoder(adrUnit, adrBit);//, dataReg);
    }
    break;
    case 6:
    {
      int adrReg  = (unsigned int)inputPacket[3] +256*(unsigned int)inputPacket[2];
      int dataReg = (unsigned int)inputPacket[5] +256*(unsigned int)inputPacket[4];
//      if(cntReg>125) return;//слишком длинный пакет
      //qDebug()<<"adrUnit="<<adrUnit<<" numFunc="<<numFunc<<" adrReg="<<adrReg<<" dataReg="<<dataReg;
      outputPacket[1] = (unsigned char)numFunc;
      sizeOutputPacket = outputFunc6PacketEncoder(adrUnit, adrReg, dataReg);
    }
    break;
    case 15:
    {
      int adrBit  = (unsigned int)inputPacket[3] +256*(unsigned int)inputPacket[2];
      int cntBit  = (unsigned int)inputPacket[5] +256*(unsigned int)inputPacket[4];
      int cntByte = (unsigned int)inputPacket[6];
      if(cntBit>125*16) return;//слишком длинный пакет
      //qDebug()<<"adrUnit="<<adrUnit<<" numFunc="<<numFunc<<" adrBit="<<adrBit<<" cntBit="<<cntBit;
      for(int i=0; i<cntByte; i++) 
              tempReadArray[i] = (unsigned short)(inputPacket[7+i]);
      outputPacket[1] = (unsigned char)numFunc;
      sizeOutputPacket = outputFunc15PacketEncoder(adrUnit, adrBit, cntBit);
    }
    break;
    case 16:
    {
      int adrReg  = (unsigned int)inputPacket[3] +256*(unsigned int)inputPacket[2];
      int cntReg  = (unsigned int)inputPacket[5] +256*(unsigned int)inputPacket[4];
      if(cntReg>125) return;//слишком длинный пакет
      //qDebug()<<"adrUnit="<<adrUnit<<" numFunc="<<numFunc<<" adrReg="<<adrReg<<" cntReg="<<cntReg;
      for(int i=0; i<cntReg; i++) 
              tempReadArray[i] = (unsigned short)(inputPacket[7+1+(i*2)]) +256*(unsigned short)(inputPacket[7+(i*2)]);
      outputPacket[1] = (unsigned char)numFunc;
      sizeOutputPacket = outputFunc16PacketEncoder(adrUnit, adrReg, cntReg);
    }
    break;
    default: return;
    }//switch

 // unsigned short CRC_sum;
  CRC_sum = 0xffff;
  for (int index = 0; index < sizeOutputPacket; index++) CRC_sum = AddCRC((*(outputPacket + index)) ,CRC_sum);
  *(outputPacket + sizeOutputPacket)  = CRC_sum & 0xff;
  *(outputPacket + sizeOutputPacket+1)  = CRC_sum >> 8;
  sizeOutputPacket += 2;
///*
//  usb_transmiting_count = sizeOutputPacket;
//  for (int i = 0; i < usb_transmiting_count; i++) usb_transmiting[i] = outputPacket[i];
//  data_usb_transmiting = true;
//*/

  //qDebug()<<" "<<outputPacket[0]<<" "<<outputPacket[1]<<" "<<outputPacket[2]<<" "<<outputPacket[3]<<
    //      " "<<outputPacket[4]<<" "<<outputPacket[5]<<" "<<outputPacket[6]<<" "<<outputPacket[7]<<
    //      " "<<outputPacket[8]<<" "<<outputPacket[9]<<" "<<outputPacket[10]<<" "<<outputPacket[11]<<
    //      " "<<outputPacket[12]<<" "<<outputPacket[13]<<" "<<outputPacket[14]<<" "<<outputPacket[15]<<
    //      " "<<outputPacket[16]<<" "<<outputPacket[17]<<" "<<outputPacket[18]<<" "<<outputPacket[19]<<
    //      " "<<outputPacket[20]<<" "<<outputPacket[21]<<" "<<outputPacket[22]<<" "<<outputPacket[23]<<
     //     " "<<outputPacket[24];
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

int outputFunc5PacketEncoder(int adrUnit, int adrBit)
{
//выходной кодировщик 5 функции
  superPreWriteAction();//action до записи
  int result = superWriterBit(adrBit, 1);
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
//MadrBit
  outputPacket[idxOutputPacket] = (unsigned char)((adrBit>>8)&0xFF);
  idxOutputPacket++;
//LadrBit
  outputPacket[idxOutputPacket] = (unsigned char)(adrBit&0xFF);
  idxOutputPacket++;
//MdataReg
  outputPacket[idxOutputPacket] = (unsigned char)(0xFF);
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
 break;
 case ID_FB_INPUT:
  if(cnt>=current_config.n_input) return 1;
 break;
 case ID_FB_OUTPUT:
  if(cnt>=current_config.n_output) return 1;
 break;
 case ID_FB_LED:
  if(cnt>=current_config.n_led) return 1;
 break;
 case ID_FB_BUTTON:
  if(cnt>=current_config.n_button) return 1;
 break;

 case ID_FB_ALARM:
  if(cnt>=current_config.n_alarm) return 1;
 break;
case ID_FB_GROUP_ALARM:
  if(cnt>=4) return 1;
 break;
 case ID_FB_AND:
  if(cnt>=current_config.n_and) return 1;
 break;
 case ID_FB_OR:
  if(cnt>=current_config.n_or) return 1;
 break;
 case ID_FB_XOR:
  if(cnt>=current_config.n_xor) return 1;
 break;
 case ID_FB_NOT:
  if(cnt>=current_config.n_not) return 1;
 break;

 case ID_FB_TIMER:
  if(cnt>=current_config.n_timer) return 1;
 break;
 case ID_FB_TRIGGER:
  if(cnt>=current_config.n_trigger) return 1;
 break;

 case ID_FB_MEANDER:
  if(cnt>=current_config.n_meander) return 1;
 break;
 case ID_FB_TU:
  if(cnt>=current_config.n_tu) return 1;
 break;
 case ID_FB_TS:
  if(cnt>=current_config.n_ts) return 1;
 break;

 case ID_FB_EVENT_LOG:
  if(cnt>=current_config.n_log) return 1;
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
  if(cnt>=current_config.n_meander) return 1;
 break;
 default: return 1;
}//switch id
return 0;
}//superControlParam_gi
