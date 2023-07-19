
#define DEBUG_ETHERNET_WEBSERVER_PORT       Serial

//#include <Arduino.h>
// ESP32
#include "defines.h"

#include <WebServer_WT32_ETH01.h>         // https://github.com/khoih-prog/WebServer_WT32_ETH01/
// #include <ESPmDNS.h>
// #include <Update.h>

#include "web_handle.h"
#include "web_config.h"
#include "web_networkconfig.h"
#include "html_page_info.h"
#include "WebOTA.h"
#include "main.h"
#include "Wire.h"
#include "Hal_ads1110.h"
#include "km07reg.h"
#include <WiFi.h>


// #include "telnet_app.h"
#include <Ticker.h>

#include "FS.h"
#include <SPIFFS.h>
#include <EEPROM.h>
#define ASYNC_TCP_SSL_ENABLED       true
//#define ASYNC_TCP_SSL_ENABLED       false

#include <AsyncMQTT_ESP32.h>


#define FORMAT_SPIFFS_IF_FAILED true
#define LED1    2
#define LED2    4


// #define LED_LINK1 14     //  IO12 doesn't work
// #define LED_PORT1 15    //  input only

// #define LED_LINK0 4
// #define LED_PORT0 2

#define LED_LINK0 14     //  IO12 doesn't work
#define LED_PORT0 15    //  input only

#define LED_LINK1 4
#define LED_PORT1 2


#define SW_RST  35



// #define SDA_PIN 12
// #define SCL_PIN 14


// WebServer server(80);
// Set according to your local network if you need static IP
IPAddress myIP(192, 168, 1, 232);
IPAddress myGW(192, 168, 1, 1);
IPAddress mySN(255, 255, 255, 0);

// Google DNS Server IP
IPAddress myDNS(8, 8, 8, 8);
IPAddress myDNS2(8,8,8,8);

unsigned long tick_loop;
unsigned char led1,led2;

unsigned long tick_ledstatus;
unsigned int ledstatus_state;
#define LED_STA_TICK    70

unsigned long tick_RTS;
unsigned int RTS_act;
unsigned int loop_rts;
#define HW_RTS_TICK     5000


// Ticker telnet_app_handle;
Ticker ADC_app_handle;
Ticker Led_status_handle;
Ticker SW_RTS_handle;
Ticker Km07_handle;



Type_config config;
Type_ModbusTCP modbus_tcp[2];

void fail(const char* msg) {
  Serial.println(msg);
  while (true) {
    yield();
  }
}

void task_adc()
{
  if(millis()-tick_loop>1000){
    tick_loop=millis();
    Ads1110.run();
  }
}

//===============================================================
// This routine is executed when you open its IP in browser
//===============================================================
void handleRoot() {
 String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send web page
}

void handleADC() {
 //int a = analogRead(A0);
 String adcValue = String(Ads1110.Adc);
 
 server.send(200, "text/plane", adcValue); //Send ADC value only to client ajax request
}

void handleLED() {
 String ledState = "OFF";
 String t_state = server.arg("LEDstate"); //Refer  xhttp.open("GET", "setLED?LEDstate="+led, true);
 Serial.println(t_state);
 if(t_state == "1")
 {
  digitalWrite(LED1,HIGH); //LED ON
  ledState = "ON"; //Feedback parameter
 }
 else
 {
  digitalWrite(LED1,LOW); //LED OFF
  ledState = "OFF"; //Feedback parameter  
 }
 
 server.send(200, "text/plane", ledState); //Send web page
}

//format bytes
String formatBytes(size_t bytes)
{
  if (bytes < 1024)
  {
    return String(bytes) + "B";
  }
  else if (bytes < (1024 * 1024))
  {
    return String(bytes / 1024.0) + "KB";
  }
  else if (bytes < (1024 * 1024 * 1024))
  {
    return String(bytes / 1024.0 / 1024.0) + "MB";
  }
  else
  {
    return String(bytes / 1024.0 / 1024.0 / 1024.0) + "GB";
  }
}

void listDir()
{
  File root = SPIFFS.open("/");
  File file = root.openNextFile();
  while (file)
  {
    String fileName = file.name();
    size_t fileSize = file.size();
    Serial.printf("FS File: %s, size: %s\n", fileName.c_str(), formatBytes(fileSize).c_str());
    file = root.openNextFile();
  }

  Serial.println();
}

void task_sw_rst()
{
  if(digitalRead(SW_RST))
    {
      tick_RTS=millis();
      RTS_act=0;
      return;
    }
  //  SWITCH RST is ACTIVE LOW
  //
  RTS_act=1;
  if(millis()-tick_RTS>HW_RTS_TICK){
    tick_RTS=millis();
    Serial.println("Hard Reset to Factory Default");
	  EEPROM.write(0,0xFF);
	  EEPROM.write(1,0xFF);
	  EEPROM.write(2,0xFF);
    EEPROM.commit();
    delay(10);
    ESP.restart();
  }
}

void task_led_status()
{
  if(millis()-tick_ledstatus>LED_STA_TICK){
    tick_ledstatus=millis();
    
  // if(RTS_act==0)
  // {
  // if(ledstatus_state)
  //   {
  //   if(telnet_status[0].status) 
  //     {
  //       if(!telnet_status[0].tx_status)
  //         digitalWrite(LED_PORT0,1);
  //       else
  //         digitalWrite(LED_PORT0,0);
  //     }
  //   if(telnet_status[1].status) 
  //     {
  //       if(!telnet_status[1].tx_status)
  //         digitalWrite(LED_PORT1,1);
  //       else
  //         digitalWrite(LED_PORT1,0);
  //     }

  //   telnet_status[0].tx_status=0;
  //   telnet_status[1].tx_status=0;
      
  //    if(telnet_status[0].rx_status)
  //      {
  //        digitalWrite(LED_LINK0,telnet_status[0].rx_status);
  //        telnet_status[0].rx_status=0;
  //      } 

  //    if(telnet_status[1].rx_status)
  //      {
  //        digitalWrite(LED_LINK1,telnet_status[1].rx_status);
  //        telnet_status[1].rx_status=0;
  //      }
  //      ledstatus_state=0;
  //   }
  //   else
  //   {
  //   ledstatus_state=1;
  //   digitalWrite(LED_LINK0,0);
  //   digitalWrite(LED_LINK1,0);
  //   if(!telnet_status[0].status) 
  //       digitalWrite(LED_PORT0,0);
  //   if(!telnet_status[1].status) 
  //       digitalWrite(LED_PORT1,0);
  //   if(telnet_status[0].tx_status)
  //      {
  //        digitalWrite(LED_PORT0,0);
  //        telnet_status[0].tx_status=0;
  //      }
  //   if(telnet_status[1].tx_status)
  //      {
  //        digitalWrite(LED_PORT1,0);
  //        telnet_status[1].tx_status=0;
  //      } 
  //   }  
  // }
  // else
  // {
  //   loop_rts++;
  //   if(loop_rts>=14)  loop_rts=0;
  //   if(loop_rts>6)
  //     {
  //     digitalWrite(LED_PORT0,1);
  //     digitalWrite(LED_PORT1,1);
  //     digitalWrite(LED_LINK0,1);
  //     digitalWrite(LED_LINK1,1);
  //     }
  //   else{
  //     digitalWrite(LED_PORT0,0);
  //     digitalWrite(LED_PORT1,0);
  //     digitalWrite(LED_LINK0,0);
  //     digitalWrite(LED_LINK1,0);
  //     }
  // }
  
  }
}

void setup() {
  // put your setup code here, to run once:
  //pinMode(LED1,OUTPUT);
  //pinMode(LED2,OUTPUT);
  pinMode(LED_LINK0,OUTPUT);
  pinMode(LED_PORT0,OUTPUT);
  pinMode(LED_LINK1,OUTPUT);
  pinMode(LED_PORT1,OUTPUT);


  pinMode(SW_RST,INPUT);

  Serial.begin(57600);
  //Serial1.begin(115200,SERIAL_8N1,5,17);
  Serial.println("Initial Application");
  //Ads1110.init();
 //Init EEPROM
  EEPROM.begin(400);
  if (!ReadConfig())
  {
    Serial.println("load factory default");
    Load_default_config();
  }

  // To be called before ETH.begin()
  WT32_ETH01_onEvent();
  ETH.begin(ETH_PHY_ADDR, ETH_PHY_POWER);

  // Static IP, leave without this line to get IP via DHCP
  // ETH.config(myIP, myGW, mySN, myDNS);
  //config.dhcp=0;
  if(config.dhcp){
     // << dhcp mode 
     Serial.println("DHCP MODE");
  }else{
    // << static ip mode 
    Serial.println(WEBSERVER_WT32_ETH01_VERSION);
    Serial.println(ASYNC_MQTT_ESP32_VERSION);
    Serial.println("Static IP");
      myIP=IPAddress(config.IP[0],config.IP[1],config.IP[2],config.IP[3] );
      myGW=IPAddress(config.Gateway[0],config.Gateway[1],config.Gateway[2],config.Gateway[3] );
      mySN=IPAddress(config.Netmask[0],config.Netmask[1],config.Netmask[2],config.Netmask[3] );
      myDNS=IPAddress(config.dns1[0],config.dns1[1],config.dns1[2],config.dns1[3] );
      myDNS2=IPAddress(config.dns2[0],config.dns2[1],config.dns2[2],config.dns2[3] );
      ETH.config(myIP, myGW, mySN, myDNS, myDNS2);
  }


  WT32_ETH01_waitForConnect();
  
  Serial.println("HTTP server started with MAC: " + ETH.macAddress() + ", at IPv4: " + ETH.localIP().toString()+"\t"+ ETH.gatewayIP().toString());
  initial_OTA_web();
  //server.on("/", handleRoot);      //Which routine to handle at root location. This is display page
  

/* initialize SPIFFS */
  if (!SPIFFS.begin()) {
    fail("SPIFFS init failed");
  }
  listDir();

  //server.on("/setLED", handleLED);
  server.on("/readADC", handleADC);

  server.on ( "/", []() {
    server.send ( 200, "text/html", PAGE_IndexPage );
  });
  server.on ( "/favicon.ico",   []() {
    server.send ( 200, "text/html", "");
  });
  server.on ( "/index.html", []() {
    server.send ( 200, "text/html", PAGE_IndexPage );
  }  );


  server.on ( "/page2.html", []() {
    server.send ( 200, "text/html", PAGE_2 );
  }  );


   server.on ( "/page3.html", []() {
    server.send ( 200, "text/html", PAGE_3 );
  }  );


     server.on ( "/MQTT_config.html", []() {
    server.send ( 200, "text/html", mqtt_page );
  }  );

  

  server.on ( "/info.html", []() {
    server.send ( 200, "text/html", PAGE_Information );
  }  );
  server.on ( "/style.css", []() {
    server.send ( 200, "text/plain", PAGE_Style_css );
  } );
  server.on ( "/microajax.js", []() {
    server.send ( 200, "text/plain", PAGE_microajax_js );
  } );



//test microsjax
server.on ( "/microajax2.js", []() {
    server.send ( 200, "text/plain2", PAGE_microajax2_js );
  } );

server.on ( "/microajax3.js", []() {
    server.send ( 200, "text/plain3", PAGE_microajax3_js );
  } );


  
  server.on ( "/confignetwork.html", send_network_configuration_html );
  // page config tcp to uart
  server.on ( "/config.html", send_general_configuration_html );
  
  server.on ( "/admin/metervalue", send_meter_values_html );
  server.on ( "/admin/metervalue2", send_meter_values_html2 );
  server.on ( "/admin/metervalue3", send_meter_values_html3 );

  server.on ( "/myjsfile.js", send_jsfile );
  server.on ( "/admin/infovalues", send_information_values_html );
  // page config tcp to uart
  server.on ( "/admin/configvalues", send_general_configuration_values_html );
  server.on ( "/admin/configvalues", send_mqtt_configuration_values_html );
  server.on ( "/admin/configvalues", send_mqtt_configuration_html );

  server.on ( "/admin/values", send_network_configuration_values_html );
  server.on ( "/admin/generalvalues", send_general_configuration_values_html);

  server.serveStatic("/", SPIFFS, "/");

  server.begin();
  Serial.println();
  Serial.println("HTTP server started with MAC: " + ETH.macAddress() + ", at IPv4: " + ETH.localIP().toString()+"\t"+ ETH.gatewayIP().toString());
  Serial.printf("Serial Baudrate=%d port=%d\r\n",config.baudrate,config.port);
  Serial.printf("Serial1 Baudrate=%d port=%d\r\n",config.baudrate,config.port_2);

  ConfigSerial();
  ConfigSerial1();
  if(Serial1.available())
    {
      Serial.println("Start UART1");
    }
  Serial1.println("Start UART1");
  regKm07.init();
 
  // server_telnet[1].begin(config.port_2);
  // server_telnet[0].begin(config.port);
 
  // telnet_app_handle.attach(0.01,telnet_app2);
  Led_status_handle.attach(0.10,task_led_status);
  //SW_RTS_handle.attach(0.25,task_sw_rst);
 // ADC_app_handle.attach(0.1,task_adc);
  Km07_handle.attach(0.5,regKm07.update);
}


void loop() {
  server.handleClient();
  //telnet_app2();
  //digitalWrite(LED2,led2);
}