
#include "Arduino.h"
#include "Hal_ads1110.h"
#include "Wire.h"

#define SDA 12
#define SCL 14
#define ADS1110_ADR 0x4E

void initial();
uint16_t handle_ads110();

Type_HAL_ADS1110 Ads1110={
    .HB=0,
    .LB=0,
    .Config=0,
    .Adc=0,
    .tick=0,
    .run=&handle_ads110,
    .init=&initial,
};

void initial()
{
  Wire.setPins(SDA,SCL);
  Wire.begin(SDA,SCL);
}


uint16_t handle_ads110()
{
  Wire.requestFrom(ADS1110_ADR,3);
  while(Wire.available())
  {
    Ads1110.HB=Wire.read();
    Ads1110.LB=Wire.read();
    Ads1110.Config=Wire.read();
  }
  Ads1110.Adc=(int16_t)Ads1110.HB;
  Ads1110.Adc=Ads1110.Adc<<8;
  Ads1110.Adc+=Ads1110.LB;
  return(1);
}