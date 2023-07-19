#include "main.h"
#include <EEPROM.h>

int EnableTime;             // Driver Enable/Disable Timing

// #define UART1RX_PIN         5
// #define UART1TX_PIN         17

#define UART1RX_PIN         5
#define UART1TX_PIN         17

#define UART0RX_PIN         3
#define UART0TX_PIN         1

//#define UART0RX_PIN         1
//#define UART0TX_PIN         3

void WriteStringToEEPROM(int beginaddress, String string)
{
	char  charBuf[string.length()+1];
	string.toCharArray(charBuf, string.length()+1);
	for (int t=  0; t<sizeof(charBuf);t++)
	{
			EEPROM.write(beginaddress + t,charBuf[t]);
	}
}

String  ReadStringFromEEPROM(int beginaddress)
{
	byte counter=0;
	char rChar;
	String retString = "";
	while (1)
	{
		rChar = EEPROM.read(beginaddress + counter);
		if (rChar == 0) break;
		if (counter > 31) break;
		counter++;
		retString.concat(rChar);

	}
	return retString;
}
void EEPROMWritelong(int address, long value)
      {
      byte four = (value & 0xFF);
      byte three = ((value >> 8) & 0xFF);
      byte two = ((value >> 16) & 0xFF);
      byte one = ((value >> 24) & 0xFF);

      //Write the 4 bytes into the eeprom memory.
      EEPROM.write(address, four);
      EEPROM.write(address + 1, three);
      EEPROM.write(address + 2, two);
      EEPROM.write(address + 3, one);
      }
long EEPROMReadlong(long address)
      {
      //Read the 4 bytes from the eeprom memory.
      long four = EEPROM.read(address);
      long three = EEPROM.read(address + 1);
      long two = EEPROM.read(address + 2);
      long one = EEPROM.read(address + 3);

      //Return the recomposed long by using bitshift.
      return ((four << 0) & 0xFF) + ((three << 8) & 0xFFFF) + ((two << 16) & 0xFFFFFF) + ((one << 24) & 0xFFFFFFFF);
}

void Load_default_config()
{
    // DEFAULT CONFIG
    config.ssid_sta = "MYSSID";
    config.password_sta = "MYPASSWORD";
    config.apmac_sta = "00:00:00:00:00:00";
    config.enable_apmac_sta = 0;
    config.ssid_ap = "RM-012-IP";
    config.password_ap = "12345678";
    config.dhcp = false;
    config.IP_client[0] = 192; config.IP_client[1] = 168; config.IP_client[2] = 1; config.IP_client[3] = 100;
    config.IP[0] = 192; config.IP[1] = 168; config.IP[2] = 1; config.IP[3] = 99;
    config.Netmask[0] = 255; config.Netmask[1] = 255; config.Netmask[2] = 255; config.Netmask[3] = 0;
    config.Gateway[0] = 192; config.Gateway[1] = 168; config.Gateway[2] = 1; config.Gateway[3] = 254;
    config.dns1[0] = 8; config.dns1[1] = 8; config.dns1[2] = 8; config.dns1[3] = 8;
    config.dns2[0] = 0; config.dns2[1] = 0; config.dns2[2] = 0; config.dns2[3] = 0;
    config.port =  9761;
 
    config.timezone = -10;
    config.daylight = true;
    config.www_username = "user";
    config.www_password = "1234";
    // Port0 --> Serial 1  >< Telnet port0
    config.baudrate = 2;                        // Default 9600 bps
    config.datasize = 1;                        // Default 8 bit
    config.parity = 0;                          // Default None
    config.stopbit = 1;                         // Default 1
    config.commode = 0;                         // Default TCP Socket

    //Port1 --> Serial 0  >< Telnet port1
     config.port_2 =  9762;
    config.baudrate_2 = 2;                        // Default 9600 bps
    config.datasize_2 = 1;                        // Default 8 bit
    config.parity_2 = 0;                          // Default None
    config.stopbit_2 = 1;                         // Default 1
    config.commode_2 = 0;                         // Default TCP Socket

    config.wrmode = WORK_AP_MODE;               // Default AP MODE
    config.ipmode = IP_SERVER_MODE;             // Default TCP Server
    WriteConfig();
}

boolean ReadConfig()
{
  delay(100);
//	Serial.println("Reading Configuration");
	if (EEPROM.read(0) == 'C' && EEPROM.read(1) == 'F'  && EEPROM.read(2) == 'G' )
	{
//		Serial.println("Configurarion Found!");
	    config.dhcp = 	EEPROM.read(16);
		config.daylight = EEPROM.read(17);
		config.port = EEPROMReadlong(18); // 4 Byte
		config.timezone = EEPROMReadlong(22); // 4 Byte

		config.wrmode = EEPROM.read(26);
		config.ipmode = EEPROM.read(27);

        config.IP[0] = EEPROM.read(28);
        config.IP[1] = EEPROM.read(29);
        config.IP[2] = EEPROM.read(30);
        config.IP[3] = EEPROM.read(31);
    
		config.IP_client[0] = EEPROM.read(32);
		config.IP_client[1] = EEPROM.read(33);
		config.IP_client[2] = EEPROM.read(34);
		config.IP_client[3] = EEPROM.read(35);
		config.Netmask[0] = EEPROM.read(36);
		config.Netmask[1] = EEPROM.read(37);
		config.Netmask[2] = EEPROM.read(38);
		config.Netmask[3] = EEPROM.read(39);
		config.Gateway[0] = EEPROM.read(40);
		config.Gateway[1] = EEPROM.read(41);
		config.Gateway[2] = EEPROM.read(42);
		config.Gateway[3] = EEPROM.read(43);
		config.ssid_sta = ReadStringFromEEPROM(64);
		config.password_sta = ReadStringFromEEPROM(96);
    
        config.enable_apmac_sta = EEPROM.read(309);  // << enable_apmac_sta ต้องเป็น 0 ， 1 เท่านั้น
        config.apmac_sta = ReadStringFromEEPROM(310);
        if(config.enable_apmac_sta == 255){  // <<  load data fail  reinital 
            WriteStringToEEPROM(310,config.apmac_sta); // << size + 17  00:00:00:00:00:00
            EEPROM.write(309,config.enable_apmac_sta); //<< enable status 
            config.enable_apmac_sta = 0;
            config.apmac_sta = "00:00:00:00:00:00";
        }
   
		config.ntpServerName = ReadStringFromEEPROM(128);
        config.www_username = ReadStringFromEEPROM(160);
        config.www_password = ReadStringFromEEPROM(192);
        config.ssid_ap = ReadStringFromEEPROM(224);
        config.password_ap = ReadStringFromEEPROM(256);
        config.baudrate = EEPROM.read(300);
        config.parity = EEPROM.read(301);
        config.stopbit = EEPROM.read(302);
        config.commode = EEPROM.read(303);
        config.datasize = EEPROM.read(304);


		config.port_2 = EEPROMReadlong(350); // 4 Byte
   	config.baudrate_2 = EEPROM.read(355);
		config.parity_2 = EEPROM.read(356);
		config.stopbit_2 = EEPROM.read(357);
		config.commode_2 = EEPROM.read(358);
    config.datasize_2 = EEPROM.read(359);

    config.dns1[0]=EEPROM.read(360);
    config.dns1[1]=EEPROM.read(361);
    config.dns1[2]=EEPROM.read(362);
    config.dns1[3]=EEPROM.read(363);

    config.dns2[0]=EEPROM.read(364);
    config.dns2[1]=EEPROM.read(365);
    config.dns2[2]=EEPROM.read(366);
    config.dns2[3]=EEPROM.read(367);

		return true;
		
	}
	else
	{
		Serial.println("Configurarion NOT FOUND!!!!");
		return false;
	}
}

void WriteConfig() {
	Serial.println("Writing Config");
	EEPROM.write(0,'C');
	EEPROM.write(1,'F');
	EEPROM.write(2,'G');

	EEPROM.write(16,config.dhcp);
	EEPROM.write(17,config.daylight);
	
	EEPROMWritelong(18,config.port); // 4 Byte

	EEPROMWritelong(22,config.timezone);  // 4 Byte

	EEPROM.write(26,config.wrmode);
	EEPROM.write(27,config.ipmode);

    EEPROM.write(28,config.IP[0]);
    EEPROM.write(29,config.IP[1]);
    EEPROM.write(30,config.IP[2]);
    EEPROM.write(31,config.IP[3]);
//	EEPROM.write(28,config.LED_B);

	EEPROM.write(32,config.IP_client[0]);
	EEPROM.write(33,config.IP_client[1]);
	EEPROM.write(34,config.IP_client[2]);
	EEPROM.write(35,config.IP_client[3]);

	EEPROM.write(36,config.Netmask[0]);
	EEPROM.write(37,config.Netmask[1]);
	EEPROM.write(38,config.Netmask[2]);
	EEPROM.write(39,config.Netmask[3]);

	EEPROM.write(40,config.Gateway[0]);
	EEPROM.write(41,config.Gateway[1]);
	EEPROM.write(42,config.Gateway[2]);
	EEPROM.write(43,config.Gateway[3]);


	WriteStringToEEPROM(64,config.ssid_sta);
	WriteStringToEEPROM(96,config.password_sta);
  WriteStringToEEPROM(310,config.apmac_sta); // << size + 17  00:00:00:00:00:00
  EEPROM.write(309,config.enable_apmac_sta); //<< enable status 

    WriteStringToEEPROM(128,config.ntpServerName);
    WriteStringToEEPROM(160,config.www_username);
    WriteStringToEEPROM(192,config.www_password);
    WriteStringToEEPROM(224,config.ssid_ap);
    WriteStringToEEPROM(256,config.password_ap);
  

	EEPROM.write(300,config.baudrate);
	EEPROM.write(301,config.parity);
	EEPROM.write(302,config.stopbit);
	EEPROM.write(303,config.commode);
  EEPROM.write(304,config.datasize);

  EEPROMWritelong(350,config.port_2); // 4 Byte
  EEPROM.write(355,config.baudrate_2);
	EEPROM.write(356,config.parity_2);
	EEPROM.write(357,config.stopbit_2);
	EEPROM.write(358,config.commode_2);
  EEPROM.write(359,config.datasize_2);
	
  EEPROM.write(360,config.dns1[0]);
	EEPROM.write(361,config.dns1[1]);
	EEPROM.write(362,config.dns1[2]);
	EEPROM.write(363,config.dns1[3]);

  EEPROM.write(364,config.dns2[0]);
	EEPROM.write(365,config.dns2[1]);
	EEPROM.write(366,config.dns2[2]);
	EEPROM.write(367,config.dns2[3]);

	EEPROM.commit();
}



/*=====================================================================================================
**
** CONFIGURATION SERIAL
**
=====================================================================================================*/
void ConfigSerial()
{
  uint32_t serconfig = SERIAL_8N1;
  int serbaudrate = 9600;
  
  if(config.datasize == 0) {
    if(config.stopbit == 1) {
      switch(config.parity) {
        case 0 : serconfig = SERIAL_7N1;
          break; 
        case 1 : serconfig = SERIAL_7E1;
          break; 
        case 2 : serconfig = SERIAL_7O1;
          break; 
      }
    }else if(config.stopbit == 2) {
      switch(config.parity) {
        case 0 : serconfig = SERIAL_7N2;
          break; 
        case 1 : serconfig = SERIAL_7E2;
          break; 
        case 2 : serconfig = SERIAL_7O2;
          break; 
      }
    }
  }else if(config.datasize == 1) {
    if(config.stopbit == 1) {
      switch(config.parity) {
        case 0 : serconfig = SERIAL_8N1;
          break; 
        case 1 : serconfig = SERIAL_8O1;
          break; 
        case 2 : serconfig = SERIAL_8E1;
          break; 
      }
    }else if(config.stopbit == 2) {
      switch(config.parity) {
        case 0 : serconfig = SERIAL_8N2;
          break; 
        case 1 : serconfig = SERIAL_8O2;
          break; 
        case 2 : serconfig = SERIAL_8E2;
          break; 
      }
    }
  }

  switch(config.baudrate) {
    case 0 : serbaudrate = 2400; EnableTime = 3700;
        break; 
    case 1 : serbaudrate = 4800; EnableTime = 2000;
      break; 
    case 2 : serbaudrate = 9600; EnableTime = 2000;
      break; 
    case 3 : serbaudrate = 19200; EnableTime = 2000;
      break; 
    case 4 : serbaudrate = 38400; EnableTime = 1500;
      break; 
    case 5 : serbaudrate = 57600; EnableTime = 1000;
      break; 
    case 6 : serbaudrate = 115200; EnableTime = 1000;
      break; 
    default :serbaudrate = 9600; EnableTime = 2000;
      break;
  }

  Serial1.begin(serbaudrate, serconfig,UART1RX_PIN,UART1TX_PIN);
  //Serial1.begin(serbaudrate, serconfig,UART0RX_PIN,UART0TX_PIN);
}


void ConfigSerial1()
{
  uint32_t serconfig2 = SERIAL_8N1;
  int serbaudrate2 = 9600;
  
  if(config.datasize_2 == 0) {
    if(config.stopbit_2 == 1) {
      switch(config.parity_2) {
        case 0 : serconfig2 = SERIAL_7N1;
          break; 
        case 1 : serconfig2 = SERIAL_7E1;
          break; 
        case 2 : serconfig2 = SERIAL_7O1;
          break; 
      }
    }else if(config.stopbit_2 == 2) {
      switch(config.parity_2) {
        case 0 : serconfig2 = SERIAL_7N2;
          break; 
        case 1 : serconfig2 = SERIAL_7E2;
          break; 
        case 2 : serconfig2 = SERIAL_7O2;
          break; 
      }
    }
  }else if(config.datasize_2 == 1) {
    if(config.stopbit_2 == 1) {
      switch(config.parity_2) {
        case 0 : serconfig2 = SERIAL_8N1;
          break; 
        case 1 : serconfig2 = SERIAL_8O1;
          break; 
        case 2 : serconfig2 = SERIAL_8E1;
          break; 
      }
    }else if(config.stopbit_2 == 2) {
      switch(config.parity_2) {
        case 0 : serconfig2 = SERIAL_8N2;
          break; 
        case 1 : serconfig2 = SERIAL_8O2;
          break; 
        case 2 : serconfig2 = SERIAL_8E2;
          break; 
      }
    }
  }

  switch(config.baudrate_2) {
    case 0 : serbaudrate2 = 2400; EnableTime = 3700;
        break; 
    case 1 : serbaudrate2 = 4800; EnableTime = 2000;
      break; 
    case 2 : serbaudrate2 = 9600; EnableTime = 2000;
      break; 
    case 3 : serbaudrate2 = 19200; EnableTime = 2000;
      break; 
    case 4 : serbaudrate2 = 38400; EnableTime = 1500;
      break; 
    case 5 : serbaudrate2 = 57600; EnableTime = 1000;
      break; 
    case 6 : serbaudrate2 = 115200; EnableTime = 1000;
      break; 
    default :serbaudrate2 = 9600; EnableTime = 2000;
      break;
  }

  Serial.begin(serbaudrate2, serconfig2,UART0RX_PIN,UART0TX_PIN);
  //Serial.begin(serbaudrate2, serconfig2,UART1RX_PIN,UART1TX_PIN);
}