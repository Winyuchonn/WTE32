#include "main.h"
#include "html_page_info.h"
#include "web_handle.h"

const char PAGE_Information[] PROGMEM = R"=====(
<html>
<head>
<title>RM-012-IP</title>
</head>
<body>
<link rel="stylesheet" href="css/mchp.css">
<div id="shadow-one"><div id="shadow-two"><div id="shadow-three"><div id="shadow-four">
<div id="page">
<img src="assets/pmicon.png" alt="Primus Co., Ltd." />
<div id="title"><div class="right">TCP/IP Bridge Configuration page</div><span id="hello">&nbsp;</span></div>
<div id="menu" >


              <a href="index.html">Overview</a>
              <a href="config.html">Configuration</a>
              <a href="confignetwork.html">Network Configuration</a>
              <a href="MQTT_config.html">MQTT Configuration</a>
              <a href="info.html">Network Information</a>
              <!-- <a href="reset.html">Reboot</a> -->

</div>
<div id="content">
<h1>Information</h1>
<fieldset>
<h3 class="top" style= "background-color: #096209; color: white"; >Device Info</h3>
<table border="0"  cellspacing="0" cellpadding="3" style="width:310px" >
<tr><td align="right" style="width:180px">MAC Address :</td><td><span id="x_mac"></span></td></tr>
</table><br>

<h3 class="top"style= "background-color: #096209; color: white"; color: white; >Network</h3>
<!--<div><label>Network</label></div><br>-->
<table style="border: 20px;">
<tr><td align="right" style="width:180px">IP :</td><td><span id="x_ip"></span></td></tr>
<tr><td align="right" style="width:180px">Netmask :</td><td><span id="x_netmask"></span></td></tr>
<tr><td align="right" style="width:180px">Gateway :</td><td><span id="x_gateway"></span></td></tr>
<tr><td align="right" style="width:180px">DNS :</td><td><span id="x_dns1"></span></td></tr>
</table>

<h3 style= "background-color: #096209; color: white">Port1 information</h3>
<table style="border: 20px;">
<tr><td align="right" style="width:180px">Status :</td><td><span id="x_port1sta"></span></td></tr>
<tr><td align="right" style="width:180px">Port :</td><td><span id="x_port"></span></td></tr>
<tr><td align="right" style="width:180px">baud :</td><td><span id="x_baud"></span></td></tr>
<tr><td align="right" style="width:180px">Config :</td><td><span id="x_config"></span></td></tr>
<tr><td align="right" style="width:180px">Protocol :</td><td><span id="x_protocol"></span></td></tr>
</table>


<h3 style= "background-color: #096209; color: white">Port2 information</h3>
<table style="border: 20px;">
<tr><td align="right" style="width:180px">Status2 :</td><td><span id="x_port2sta"></span></td></tr>
<tr><td align="right" style="width:180px">Port2 :</td><td><span id="x_port2"></span></td></tr>
<tr><td align="right" style="width:180px">baud2 :</td><td><span id="x_baud2"></span></td></tr>
<tr><td align="right" style="width:180px">Config2 :</td><td><span id="x_config2"></span></td></tr>
<tr><td align="right" style="width:180px">Protocol2 :</td><td><span id="x_protocol2"></span></td></tr>
</table>


</fieldset>
<!-- END MAIN -->
</div>
<div class="spacer">&nbsp;</div>
<div id="footer">Copyright &copy; 2012 Primus Co., Ltd.</div>
</body>
</html>
</body>
<script>
function GetState()
{
 // document.getElementById("x_waiting").innerHTML = "Waiting...."; 
  setValues("/admin/infovalues");
}
function update_infor()
{
  document.getElementById("ssid_ap").disabled  = false
}

window.onload = function ()
{
//  load("style.css","css", function() 
//  {
    load("microajax.js","js", function() 
    {
        GetState();
        update_infor();
    });
//  });
}

function load(e,t,n){if("js"==t){var a=document.createElement("script");a.src=e,a.type="text/javascript",a.async=!1,a.onload=function(){n()},document.getElementsByTagName("head")[0].appendChild(a)}else if("css"==t){var a=document.createElement("link");a.href=e,a.rel="stylesheet",a.type="text/css",a.async=!1,a.onload=function(){n()},document.getElementsByTagName("head")[0].appendChild(a)}}
</script>
)=====" ;

const String baud_str[]={
"2400 bps","4800 bps","9600 bps","19200 bps","38400 bps","57600 bps","115200 bps"
};
const String parity_str[]={
  "None","Odd","Even"
};
const String stopbit_str[]={
  "N/A","One","Two"
};
const String Datasize_str[]={
  "7 bits","8 bits"
};


void send_information_values_html ()
{
  String values ="";
  String state = "N/A";
  String protocol = "N/A";
  String protocol1 = "N/A";
  String connecttype = "N/A";
  String port0state="N/A";
  String port1state="N/A";
  String baud="N/A";
  String baud1="N/A";
  String uart_config="N/A";
  String uart_config1="N/A";
  int quality=0,rssi;
  if (WiFi.status() == 0) state = "Idle";
  else if (WiFi.status() == 1) state = "NO SSID AVAILBLE";
  else if (WiFi.status() == 2) state = "SCAN COMPLETED";
  else if (WiFi.status() == 3) state = "CONNECTED";
  else if (WiFi.status() == 4) state = "CONNECT FAILED";
  else if (WiFi.status() == 5) state = "CONNECTION LOST";
  else if (WiFi.status() == 6) state = "DISCONNECTED";
  

//  rssi = getRSSI(config.ssid_sta.c_str());
//  rssi = WiFi.RSSI();
  if(rssi <= -100) {
      quality = 0;
  } else if(rssi >= -50) {
      quality = 100;
  } else  {
    quality = 2 * (rssi + 100);
  }

  if(config.commode == 1) {
    protocol = "TCP Socket";
  } else {
    protocol = "Modbus";
  }
  if(config.commode_2 == 1) {
    protocol1 = "TCP Socket";
  } else {
    protocol1 = "Modbus";
  }

  if(config.ipmode == IP_CLIENT_MODE) {
    connecttype = "TCP Client";
  } else {
    connecttype = "TCP Server";
  }

  // if(telnet_status[0].status)
  // {  port0state="In use";  }
  // else
  // {  port0state="Available";   }
  // if(telnet_status[1].status)
  // {   port1state="In use";}
  // else
  // {  port1state="Available";}

  baud=baud_str[config.baudrate];
  baud1=baud_str[config.baudrate_2];
  uart_config=Datasize_str[config.datasize]+", "+parity_str[config.parity]+", "+stopbit_str[config.stopbit];
  uart_config1=Datasize_str[config.datasize_2]+", "+parity_str[config.parity_2]+", "+stopbit_str[config.stopbit_2];
	//values += "x_ssid|" + (String)config.ssid_sta +  "|div\n";
  //values += "x_ssidap|" + (String)config.ssid_ap +  "|div\n";
	values += "x_ip|" +  (String) ETH.localIP()[0] + "." +  (String) ETH.localIP()[1] + "." +  (String) ETH.localIP()[2] + "." + (String) ETH.localIP()[3] +  "|div\n";
	values += "x_gateway|" +  (String) ETH.gatewayIP()[0] + "." +  (String) ETH.gatewayIP()[1] + "." +  (String) ETH.gatewayIP()[2] + "." + (String) ETH.gatewayIP()[3] +  "|div\n";
	values += "x_netmask|" +  (String) ETH.subnetMask()[0] + "." +  (String) ETH.subnetMask()[1] + "." +  (String) ETH.subnetMask()[2] + "." + (String) ETH.subnetMask()[3] +  "|div\n";
  values += "x_dns1|" +  (String) ETH.dnsIP()[0] + "." +  (String) ETH.dnsIP()[1] + "." +  (String) ETH.dnsIP()[2] + "." + (String) ETH.dnsIP()[3] +  "|div\n";
  //values += "dns1_0|" +  (String) config.dns1[0]+ (String) config.dns1[1]+(String) config.dns1[2]+(String) config.dns1[3] +  "|div\n";
  //values += "dns1_0|" +  (String) config.dns2[0]+ (String) config.dns2[1]+(String) config.dns2[2]+(String) config.dns2[3] +  "|div\n";
  //values += "x_dns2|" +  (String) ETH.dnsIP()[0] + "." +  (String) ETH.gatewayIP()[1] + "." +  (String) ETH.gatewayIP()[2] + "." + (String) ETH.gatewayIP()[3] +  "|div\n";

	values += "x_mac|" + GetMacAddress() +  "|div\n";

  values += "x_port|" + (String)config.port +  "|div\n";
  values += "x_baud|" + baud +  "|div\n";
  values += "x_config|" + uart_config +  "|div\n";
  values += "x_protocol|" + protocol +  "|div\n";
  values += "x_port1sta|" + port0state+  "|div\n";

  //values += "x_port_2|"+ (String)config.port + "|div\n";

  values += "x_port2|" + (String)config.port_2 +  "|div\n";
  values += "x_baud2|" + baud1 +  "|div\n";
  values += "x_config2|" + uart_config1 +  "|div\n";
  values += "x_protocol2|" + protocol1 +  "|div\n";
  values += "x_port2sta|" + port1state+  "|div\n";

	server.send ( 200, "text/plain", values);
//	Serial.println(__FUNCTION__); 

}