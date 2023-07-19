
#include <Arduino.h>
// #include "telnet_app.h"
#define WORK_AP_MODE      0
#define WORK_STA_MODE     1
#define WORK_STA_MULTI_JOIN     2
#define WORK_STA_CONNECTED_OFF_AP_MODE     3
#define WORK_STA_MULTI_JOIN_CONNECTED_OFF_AP_MODE     4
#define WORK_STA_ONLY_MODE     5
#define WORK_STA_MULTI_JOIN_ONLY_MODE     6

// define Internet Protocol mode
#define IP_SERVER_MODE    0
#define IP_CLIENT_MODE    1

#define TCP_SOCKET  1
#define MODBUS_TCP  0

#define LED_PORT_1 10
#define LED_PORT_2 12

#define LED_LINK_1 9
#define LED_LINK_2 11



typedef struct strConfig {
  String ssid_sta;                  // SSID for STA mode
  String password_sta;              // PASSWORD for STA mode
  String apmac_sta;                 // Aceespoint mac STA mode // default 00:00:00:00:00:00 allow all ap
  byte   enable_apmac_sta;          // enable status
  
  String ssid_ap;                   // SSID for AP mode
  String password_ap;               // PASSWORD for AP mode
  byte  IP_client[4];               // IP for TCP Client
  byte  IP[4];                      // IP Address
  byte  Netmask[4];                 // Subnet Mask
  byte  Gateway[4];                 // Default Gateway
  byte  dns1[4];                    // primary DNS
  byte  dns2[4];                    // secondary Gateway
  boolean dhcp;                     // DHCP
  
  String ntpServerName;
   // Port 1 parameter 
  long port;
  long timezone;
  boolean daylight;
  String www_username;
  String www_password;
  byte baudrate;                    
  byte datasize;
  byte parity;
  byte stopbit;
  byte commode;                      // Communication mode (Socket, Modbus)
  byte wrmode;                       // Work mode (STA, AP)
  byte ipmode;                       // Internet Protocol mode (Client, Server)
     // Port 2 parameter 
  long port_2;
  byte baudrate_2;                    
  byte datasize_2;
  byte parity_2;
  byte stopbit_2;
  byte commode_2;                      // Communication mode (Socket, Modbus)



}Type_config;

typedef struct{
  unsigned char revice_index = 0;
  unsigned char revice_message[50];

  unsigned char buffer_serial[50];
}
Type_ModbusTCP;



extern Type_ModbusTCP modbus_tcp[2];

extern Type_config config;

extern boolean ReadConfig();
extern void WriteConfig();
extern void Load_default_config();
extern void ConfigSerial();
extern void ConfigSerial1();



