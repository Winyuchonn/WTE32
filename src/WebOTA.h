
#pragma once

#define _ETHERNET_WEBSERVER_LOGLEVEL_       1

// Can be included as many times as necessary, without `Multiple Definitions` Linker Error
#include "WebServer_WT32_ETH01.hpp"

extern void initial_OTA_web();
extern const char* loginIndex;
extern const char* host;
extern const char* serverIndex;

