


typedef struct{
  unsigned char HB;
  unsigned char LB;
  unsigned char Config;
  int16_t Adc;
  unsigned long tick;
  uint16_t (*run)(void);
  void (*init)(void);
}Type_HAL_ADS1110;

extern Type_HAL_ADS1110 Ads1110;

