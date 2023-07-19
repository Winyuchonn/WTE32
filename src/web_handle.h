#pragma once

#define _ETHERNET_WEBSERVER_LOGLEVEL_       1

// Can be included as many times as necessary, without `Multiple Definitions` Linker Error
#include "WebServer_WT32_ETH01.hpp"

typedef struct 
{
	byte hour;
	byte minute;
	byte second;
	int year;
	byte month;
	byte day;
	byte wday;

}type_Datatime;

extern type_Datatime strDateTime;
extern WebServer server;
extern const char MAIN_page[];
extern const char PAGE_IndexPage[];
extern const char PAGE_Style_css[];
extern const char PAGE_microajax_js[];
extern const char PAGE_microajax2_js[];
extern const char PAGE_microajax3_js[];
extern const char PAGE_2[];
extern const char PAGE_3[];
extern const char mqtt_page[];


extern void send_jsfile ();


extern String GetMacAddress();


extern boolean checkRange(String Value);
extern String GetMacAddress();
extern String urldecode(String input);
extern unsigned char h2int(char c);

extern void send_meter_values_html ();
extern void send_meter_values_html2 ();
extern void send_meter_values_html3 ();
extern void send_mqtt_configuration_html();
extern void send_mqtt_configuration_values_html();

