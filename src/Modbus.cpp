

#include "Modbus.h"

TypeModbus Modbus;
TypeModbus Modbus2;



void crc16(char *data, uint8_t len) {
  uint8_t i, j;  
  Modbus.CrcHi = Modbus.CrcLo = 0xFF;  
  for (i = 0; i < len; i++, data++)
  {
    j = Modbus.CrcHi ^ *data;
    Modbus.CrcHi = Modbus.CrcLo ^ CRCTableHigh[j];
    Modbus.CrcLo = CRCTableLow[j];
  }
}




uint8_t ucModbus_ConvertRTUtoTCP(const unsigned char *buff, uint8_t len) {
  const unsigned char *buffin = buff;
  uint8_t lenTCP = len - 2;      // all data - CRC
  uint8_t retlen = 0;

  crc16((char*)buffin, lenTCP);
  if(Modbus.CrcHi!=buffin[lenTCP] || Modbus.CrcLo!=buffin[lenTCP+1])
    return 0;

  retlen = 0;
  Modbus.RspBuf[retlen++] = Modbus.Slaveid >> 8;
  Modbus.RspBuf[retlen++] = Modbus.Slaveid & 0xFF;
  Modbus.RspBuf[retlen++] = Modbus.Protoid >> 8;
  Modbus.RspBuf[retlen++] = Modbus.Protoid & 0xFF;
  Modbus.RspBuf[retlen++] = lenTCP >> 8;
  Modbus.RspBuf[retlen++] = lenTCP & 0xFF;
  for(int i=0; i<lenTCP; i++) {
    Modbus.RspBuf[i+retlen] = buffin[i];
  }
//  memcpy(&Modbus.RspBuf[retlen], buffin, lenTCP);
  retlen += lenTCP;
  return retlen;
}

uint8_t ucModbus_ConvertTCPtoRTU(const unsigned char *buff, uint8_t Len) {
  const  unsigned char *buffin = buff;
  uint8_t lenRTU = Len - 6;     // all data - Trasaction id(2) - Protocol id(2) - lenght(2)
  uint8_t retlen = 0;

  if((buffin[MB_TCP_INDEX_LENGTH]<<8)+buffin[MB_TCP_INDEX_LENGTH+1] != lenRTU)
    return 0;

  Modbus.Slaveid = buffin[MB_TCP_INDEX_TRANID] << 8;
  Modbus.Slaveid += buffin[MB_TCP_INDEX_TRANID+1] & 0xFF;
  Modbus.Protoid = buffin[MB_TCP_INDEX_PROTOID] << 8;
  Modbus.Protoid += buffin[MB_TCP_INDEX_PROTOID+1] & 0xFF;

  for(int i=0; i<lenRTU; i++) {
    Modbus.ReqBuf[i] = buffin[6+i];
  }
  crc16(Modbus.ReqBuf, lenRTU);
  Modbus.ReqBuf[lenRTU++] = Modbus.CrcHi;
  Modbus.ReqBuf[lenRTU++] = Modbus.CrcLo;
  retlen = lenRTU;

  return retlen;
}

void crc16_2(char *data, uint8_t len) {
  uint8_t i, j;  
  Modbus2.CrcHi = Modbus2.CrcLo = 0xFF;  
  for (i = 0; i < len; i++, data++)
  {
    j = Modbus2.CrcHi ^ *data;
    Modbus2.CrcHi = Modbus2.CrcLo ^ CRCTableHigh[j];
    Modbus2.CrcLo = CRCTableLow[j];
  }
}

uint8_t ucModbus_ConvertRTUtoTCP1(const unsigned char *buff, uint8_t len) {
  const unsigned char *buffin = buff;
  uint8_t lenTCP = len - 2;      // all data - CRC
  uint8_t retlen = 0;

  crc16_2((char*)buffin, lenTCP);
  if(Modbus2.CrcHi!=buffin[lenTCP] || Modbus2.CrcLo!=buffin[lenTCP+1])
    return 0;

  retlen = 0;
  Modbus2.RspBuf[retlen++] = Modbus2.Slaveid >> 8;
  Modbus2.RspBuf[retlen++] = Modbus2.Slaveid & 0xFF;
  Modbus2.RspBuf[retlen++] = Modbus2.Protoid >> 8;
  Modbus2.RspBuf[retlen++] = Modbus2.Protoid & 0xFF;
  Modbus2.RspBuf[retlen++] = lenTCP >> 8;
  Modbus2.RspBuf[retlen++] = lenTCP & 0xFF;
  for(int i=0; i<lenTCP; i++) {
    Modbus2.RspBuf[i+retlen] = buffin[i];
  }
//  memcpy(&Modbus.RspBuf[retlen], buffin, lenTCP);
  retlen += lenTCP;
  return retlen;
}

uint8_t ucModbus_ConvertTCPtoRTU1(const unsigned char *buff, uint8_t Len) {
  const  unsigned char *buffin = buff;
  uint8_t lenRTU = Len - 6;     // all data - Trasaction id(2) - Protocol id(2) - lenght(2)
  uint8_t retlen = 0;

  if((buffin[MB_TCP_INDEX_LENGTH]<<8)+buffin[MB_TCP_INDEX_LENGTH+1] != lenRTU)
    return 0;

  Modbus2.Slaveid = buffin[MB_TCP_INDEX_TRANID] << 8;
  Modbus2.Slaveid += buffin[MB_TCP_INDEX_TRANID+1] & 0xFF;
  Modbus2.Protoid = buffin[MB_TCP_INDEX_PROTOID] << 8;
  Modbus2.Protoid += buffin[MB_TCP_INDEX_PROTOID+1] & 0xFF;

  for(int i=0; i<lenRTU; i++) {
    Modbus2.ReqBuf[i] = buffin[6+i];
  }
  crc16_2(Modbus2.ReqBuf, lenRTU);
  Modbus2.ReqBuf[lenRTU++] = Modbus2.CrcHi;
  Modbus2.ReqBuf[lenRTU++] = Modbus2.CrcLo;
  retlen = lenRTU;

  return retlen;
}
