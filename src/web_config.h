#pragma once

#define _ETHERNET_WEBSERVER_LOGLEVEL_       1

// Can be included as many times as necessary, without `Multiple Definitions` Linker Error
#include "WebServer_WT32_ETH01.hpp"

extern void send_general_configuration_html();
extern void send_general_configuration_values_html();