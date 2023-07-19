#include "main.h"
#include "web_handle.h"


const char PAGE_NetworkConfiguration[] PROGMEM = R"=====(
<html>

<head>
  <title>RM-012-IP</title>
</head>

<body>
  
  <style>
    
    .errorform {
      box-shadow: 0 0 3px red;
      }
      
      </style>
  <!-- <script src="js/config.js"></script> -->

  

<script>


  document.addEventListener('DOMContentLoaded', function() {
    const form = document.querySelector('form');
    const inputs = form.querySelectorAll('input');
  
    form.addEventListener('submit', function (event) {
      event.preventDefault();
  
      let isValid = true;
  
      inputs.forEach(function (input) {
        if (input.type === 'checkbox' && !input.checked) {
          isValid = false;
          input.classList.add('errorform');
        } else if (input.value.trim() === '') {
          isValid = false;
          input.classList.add('errorform');
        } else if (input.id === 'porA' && parseInt(input.value) < 100 || parseInt(input.value) > 50000) {
          isValid = false;
          input.classList.add('errorform');
          
        } else if (input.id === 'por_2' && parseInt(input.value) < 100 || parseInt(input.value) > 50000) {
          isValid = false;
          input.classList.add('errorform');
          
        } else {
          input.classList.remove('errorform');
        }
      });
      if(isValid){
        // form.submit();
      }
    });
  });
  


  function setNominalValue() {
  document.getElementById("dhcp").checked = true;
   
  document.getElementById("ip_0").value = "192";
  document.getElementById("ip_1").value = "168";
  document.getElementById("ip_2").value = "1";
  document.getElementById("ip_3").value = "1";


  document.getElementById("nm_0").value = "255";
  document.getElementById("nm_1").value = "255";
  document.getElementById("nm_2").value = "255";
  document.getElementById("nm_3").value = "0";

  document.getElementById("gw_0").value = "192";
  document.getElementById("gw_1").value = "168"; 
  document.getElementById("gw_2").value = "2"; 
  document.getElementById("gw_3").value = "100"; 

  document.getElementById("dns1_0").value = "8";
  document.getElementById("dns1_1").value = "8";
  document.getElementById("dns1_2").value = "8";
  document.getElementById("dns1_3").value = "8";
}








  </script>


  
  <link rel="stylesheet" href="css/mchp.css">
  <div id="shadow-one">
    <div id="shadow-two">
      <div id="shadow-three">
        <div id="shadow-four">
          <div id="page">
            <img src="assets/pmicon.png" alt="Primus Co., Ltd." />
            <div id="title">
              <div class="right">TCP/IP Bridge Configuration page</div><span id="hello">&nbsp;</span>
            </div>
            <div id="menu">
              <a href="index.html">Overview</a>
              <a href="config.html">Configuration</a>
              <a href="confignetwork.html">Network Configuration</a>
              <a href="MQTT_config.html">MQTT Configuration</a>
              <a href="info.html">Network Information</a>
              <!-- <a href="reset.html">Reboot</a> -->


            </div>
            <div id="setting">
              <fieldset>
                <form action="" method="get">
                  <h3 id="myHeadingnet" style="background-color: #096209; color: white; margin-top: auto;">Network Configuration</h3>
                  <table>
                    <tr>
                      <td align="right" style="background-color: #006600; color: white;"><strong>DHCP:</strong></td>
                      <td align="left"><input type="checkbox" id="dhcp" name="dhcp" onclick="updatedhcp();"></td>
                    </tr>
                    <tr>
                      <td align="right" style="background-color: #006600; color: white;"><strong>IP: </strong></td>
                      <td><input type="text" id="ip_0" name="ip_0" style="width:50px">.<input type="text" id="ip_1"
                          name="ip_1" style="width:50px">.<input type="text" id="ip_2" name="ip_2"
                          style="width:50px">.<input type="text" id="ip_3" name="ip_3" value="" style="width:50px"></td>
                    </tr>
                    <tr>
                      <td align="right" style="background-color: #006600; color: white;"><strong>Netmask:</strong></td>
                      <td><input type="text" id="nm_0" name="nm_0" style="width:50px">.<input type="text" id="nm_1"
                          name="nm_1" style="width:50px">.<input type="text" id="nm_2" name="nm_2"
                          style="width:50px">.<input type="text" id="nm_3" name="nm_3" style="width:50px"></td>
                    </tr>
                    <tr>
                      <td align="right" style="background-color: #006600; color: white;"><strong>Gateway:</strong></td>
                      <td><input type="text" id="gw_0" name="gw_0" style="width:50px">.<input type="text" id="gw_1"
                          name="gw_1" style="width:50px">.<input type="text" id="gw_2" name="gw_2"
                          style="width:50px">.<input type="text" id="gw_3" name="gw_3" style="width:50px"></td>
                    </tr>
                    <tr>
                      <td align="right" style="background-color: #006600; color: white;"><strong>DNS:</strong></td>
                      <td><input type="text" id="dns1_0" name="dns1_0" style="width:50px">.<input type="text"
                          id="dns1_1" name="dns1_1" style="width:50px">.<input type="text" id="dns1_2" name="dns1_2"
                          style="width:50px">.<input type="text" id="dns1_3" name="dns1_3" style="width:50px"></td>
                    </tr>
                    <!-- <tr><td align="right"><strong>Secondary DNS:</strong></td><td><input type="text" id="dns2_0" name="dns2_0" style="width:50px">.<input type="text" id="dns2_1" name="dns2_1" style="width:50px">.<input type="text" id="dns2_2" name="dns2_2" style="width:50px">.<input type="text" id="dns2_3" name="dns2_3" style="width:50px"></td></tr> -->
                    <tr>
                      <td colspan="2" align="center">
                        <input type="submit" style="width:150px" class="btn btn--m btn--blue" value="Save">
                        <!-- <input type="reset" style="width:150px"
                          class="btn btn--m btn--blue" value="Default" > -->
                        <button onclick="setNominalValue()">Default</button>

                      </td>
                    </tr>
                  </table>
                </form>

              </fieldset>
              <!-- END MAIN -->
            </div>
            <div class="spacer">&nbsp;</div>
            <div id="footer">Copyright &copy; 2012 Primus Co., Ltd.</div>
          </div>
        </div>
      </div>
    </div>
  </div>
</body>

</html>
</body>


<script>



  function GetState() {
    document.getElementById("networks").innerHTML = "Scanning...";
    setValues("/admin/connectionstate");

  }
  function selssid(value) {
    document.getElementById("ssid_sta").value = value;
  }
  function updatemodewifi() {
    if (document.getElementById("wrmode").value === "0") {
      // apmode 
      document.getElementById("ssid_ap").disabled = false
      document.getElementById("password_ap").disabled = false

      document.getElementById("ssid_sta").disabled = true
      document.getElementById("password_sta").disabled = true

      document.getElementById("enable_apmac_sta").disabled = true
      document.getElementById("apmac_sta").disabled = true

      document.getElementById("dhcp").disabled = true

      document.getElementById("ip_0").disabled = true
      document.getElementById("ip_1").disabled = true
      document.getElementById("ip_2").disabled = true
      document.getElementById("ip_3").disabled = true

      document.getElementById("nm_0").disabled = true
      document.getElementById("nm_1").disabled = true
      document.getElementById("nm_2").disabled = true
      document.getElementById("nm_3").disabled = true

      document.getElementById("gw_0").disabled = true
      document.getElementById("gw_1").disabled = true
      document.getElementById("gw_2").disabled = true
      document.getElementById("gw_3").disabled = true

      document.getElementById("dns1_0").disabled = true
      document.getElementById("dns1_1").disabled = true
      document.getElementById("dns1_2").disabled = true
      document.getElementById("dns1_3").disabled = true

      //document.getElementById("dns2_0").disabled = true 
      //document.getElementById("dns2_1").disabled = true
      //document.getElementById("dns2_2").disabled = true 
      //document.getElementById("dns2_3").disabled = true

    } else if (document.getElementById("wrmode").value === "1" || document.getElementById("wrmode").value === "2" || document.getElementById("wrmode").value === "3" || document.getElementById("wrmode").value === "4") {
      // ap and sta
      document.getElementById("ssid_ap").disabled = false
      document.getElementById("password_ap").disabled = false

      document.getElementById("ssid_sta").disabled = false
      document.getElementById("password_sta").disabled = false
      document.getElementById("enable_apmac_sta").disabled = false
      document.getElementById("dhcp").disabled = false

      updateapmac_sta();
      updatedhcp();
    } else {
      //sta mode 
      document.getElementById("ssid_ap").disabled = true
      document.getElementById("password_ap").disabled = true

      document.getElementById("ssid_sta").disabled = false
      document.getElementById("password_sta").disabled = false
      document.getElementById("enable_apmac_sta").disabled = false
      document.getElementById("dhcp").disabled = false

      updateapmac_sta();
      updatedhcp();


    }


  }

  function updatemodewifi2() {
    document.getElementById("dhcp").disabled = false

    updateapmac_sta();
    updatedhcp();
  }

  function updateapmac_sta() {
    document.getElementById("apmac_sta").disabled = (document.getElementById("enable_apmac_sta").value === "0") ? true : false
  }
  function updatedhcp() {

    document.getElementById("ip_0").disabled = document.getElementById("dhcp").checked;
    document.getElementById("ip_1").disabled = document.getElementById("dhcp").checked;
    document.getElementById("ip_2").disabled = document.getElementById("dhcp").checked;
    document.getElementById("ip_3").disabled = document.getElementById("dhcp").checked;

    document.getElementById("nm_0").disabled = document.getElementById("dhcp").checked;
    document.getElementById("nm_1").disabled = document.getElementById("dhcp").checked;
    document.getElementById("nm_2").disabled = document.getElementById("dhcp").checked;
    document.getElementById("nm_3").disabled = document.getElementById("dhcp").checked;

    document.getElementById("gw_0").disabled = document.getElementById("dhcp").checked;
    document.getElementById("gw_1").disabled = document.getElementById("dhcp").checked;
    document.getElementById("gw_2").disabled = document.getElementById("dhcp").checked;
    document.getElementById("gw_3").disabled = document.getElementById("dhcp").checked;

    document.getElementById("dns1_0").disabled = document.getElementById("dhcp").checked;
    document.getElementById("dns1_1").disabled = document.getElementById("dhcp").checked;
    document.getElementById("dns1_2").disabled = document.getElementById("dhcp").checked;
    document.getElementById("dns1_3").disabled = document.getElementById("dhcp").checked;

    //document.getElementById("dns1_0").disabled =  document.getElementById("dhcp").checked;
    //document.getElementById("dns1_1").disabled =  document.getElementById("dhcp").checked;
    //document.getElementById("dns1_2").disabled =  document.getElementById("dhcp").checked;
    //document.getElementById("dns1_3").disabled =  document.getElementById("dhcp").checked;


  }
  window.onload = function () {
    //  load("style.css","css", function() 
    //  {
    load("microajax.js", "js", function () {
      //setTimeout(updatemodewifi2,100);
      setValues("/admin/values");
      setTimeout(GetState, 3000);
    });

    //  });
  }
  function load(e, t, n) { if ("js" == t) { var a = document.createElement("script"); a.src = e, a.type = "text/javascript", a.async = !1, a.onload = function () { n() }, document.getElementsByTagName("head")[0].appendChild(a) } else if ("css" == t) { var a = document.createElement("link"); a.href = e, a.rel = "stylesheet", a.type = "text/css", a.async = !1, a.onload = function () { n() }, document.getElementsByTagName("head")[0].appendChild(a) } }
</script>

</html>

)=====";

const char PAGE_WaitAndReload[] PROGMEM = R"=====(
<meta http-equiv="refresh" content="5; URL=index.html">
<html>
<head>
<title>RM-012-IP</title>
</head>
<body>
<link rel="stylesheet" href="css/mchp.css">
<div id="shadow-one"><div id="shadow-two"><div id="shadow-three"><div id="shadow-four">
<div id="page">
<img src="assets/pmicon.gif" alt="Primus Co., Ltd." />
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
<h1>Reboot In Progress...</h1>
<p>Your settings were successfully saved, and the board is now rebooting 
to configure itself with the new settings.</p>
<p id="redir_message" align="center"></p>
<h3>Reconnection Instructions</h3>
<ol>
<li style="margin-bottom:10px"><b>Did you change the hostname, IP or MAC address?</b><br />
  It is necessary to clear the address caches in your web browser and OS.
  From the command prompt in Windows, enter "nbtstat&nbsp;-R" to clear the hostname cache, 
  close your current web browser, open a new web browser, and then try to access the web address above.</li>
<li style="margin-bottom:10px"><b>Did you try the IP address?</b><br />
  Try accessing the module directly at the IP address you know.
  (ex: enter "http://192.168.1.99/" into your browser).  If this fails, then 
  the IP address you set is not reachable.  Try reset to factory setting
    with hold down the reset button and power on about 2 second
    until led status to blink one time.</li>
</ol>
</div>
<div class="spacer">&nbsp;</div>
<div id="footer">Copyright &copy; 2012 Primus Co., Ltd.</div>
</div></div></div></div></div>
</body>
</html>
)=====";




String PAGE_Script = R"=====(

)=====";



void send_network_configuration_html()
{
	
	if (server.args() > 0 )  // Save Settings
	{
		String temp = "";
		config.dhcp = false;
		for ( uint8_t i = 0; i < server.args(); i++ ) {
      //if (server.argName(i) == "wrmode") if (checkRange(server.arg(i)))   config.wrmode =  server.arg(i).toInt();

      //if (server.argName(i) == "ssid_sta") config.ssid_sta =   urldecode(server.arg(i));
      //if (server.argName(i) == "password_sta") config.password_sta =    urldecode(server.arg(i)); 

      //if (server.argName(i) == "enable_apmac_sta") if (checkRange(server.arg(i)))   config.enable_apmac_sta =  server.arg(i).toInt();
      //if (server.argName(i) == "apmac_sta") config.apmac_sta =   urldecode(server.arg(i));
      
			//if (server.argName(i) == "ssid_ap") config.ssid_ap =   urldecode(server.arg(i));
			//if (server.argName(i) == "password_ap") config.password_ap =    urldecode(server.arg(i)); 
			if (server.argName(i) == "ip_0") if (checkRange(server.arg(i))) 	config.IP[0] =  server.arg(i).toInt();
			if (server.argName(i) == "ip_1") if (checkRange(server.arg(i))) 	config.IP[1] =  server.arg(i).toInt();
			if (server.argName(i) == "ip_2") if (checkRange(server.arg(i))) 	config.IP[2] =  server.arg(i).toInt();
			if (server.argName(i) == "ip_3") if (checkRange(server.arg(i))) 	config.IP[3] =  server.arg(i).toInt();
			if (server.argName(i) == "nm_0") if (checkRange(server.arg(i))) 	config.Netmask[0] =  server.arg(i).toInt();
			if (server.argName(i) == "nm_1") if (checkRange(server.arg(i))) 	config.Netmask[1] =  server.arg(i).toInt();
			if (server.argName(i) == "nm_2") if (checkRange(server.arg(i))) 	config.Netmask[2] =  server.arg(i).toInt();
			if (server.argName(i) == "nm_3") if (checkRange(server.arg(i))) 	config.Netmask[3] =  server.arg(i).toInt();
			if (server.argName(i) == "gw_0") if (checkRange(server.arg(i))) 	config.Gateway[0] =  server.arg(i).toInt();
			if (server.argName(i) == "gw_1") if (checkRange(server.arg(i))) 	config.Gateway[1] =  server.arg(i).toInt();
			if (server.argName(i) == "gw_2") if (checkRange(server.arg(i))) 	config.Gateway[2] =  server.arg(i).toInt();
			if (server.argName(i) == "gw_3") if (checkRange(server.arg(i))) 	config.Gateway[3] =  server.arg(i).toInt();

      if (server.argName(i) == "dns1_0") if (checkRange(server.arg(i))) 	config.dns1[0] =  server.arg(i).toInt();
			if (server.argName(i) == "dns1_1") if (checkRange(server.arg(i))) 	config.dns1[1] =  server.arg(i).toInt();
			if (server.argName(i) == "dns1_2") if (checkRange(server.arg(i))) 	config.dns1[2] =  server.arg(i).toInt();
			if (server.argName(i) == "dns1_3") if (checkRange(server.arg(i))) 	config.dns1[3] =  server.arg(i).toInt();

      //if (server.argName(i) == "dns2_0") if (checkRange(server.arg(i))) 	config.dns2[0] =  server.arg(i).toInt();
			//if (server.argName(i) == "dns2_1") if (checkRange(server.arg(i))) 	config.dns2[1] =  server.arg(i).toInt();
			//if (server.argName(i) == "dns2_2") if (checkRange(server.arg(i))) 	config.dns2[2] =  server.arg(i).toInt();
			//if (server.argName(i) == "dns2_3") if (checkRange(server.arg(i))) 	config.dns2[3] =  server.arg(i).toInt();


			if (server.argName(i) == "dhcp") config.dhcp = true;
		}
		server.send ( 200, "text/html", PAGE_WaitAndReload );
        Serial.println("Save Network Config ");
        Serial.println(config.port);
		WriteConfig();    
        delay(10);
        ESP.restart();
	}
	else
	{
    if(!server.authenticate(config.www_username.c_str(), config.www_password.c_str()))
      return server.requestAuthentication();
      
		server.send ( 200, "text/html", PAGE_NetworkConfiguration ); 
	}
//	Serial.println(__FUNCTION__); 
}

void send_network_configuration_values_html()
{

	String values ="";

  //values += "wrmode|" +  (String) config.wrmode + "|select\n";
	//values += "ssid_sta|" + (String) config.ssid_sta + "|input\n";
	//values += "password_sta|" +  (String) config.password_sta + "|input\n";

  //values += "enable_apmac_sta|" +  (String) config.enable_apmac_sta + "|select\n";
  //values += "apmac_sta|" +  (String) config.apmac_sta + "|input\n";
  
  //values += "ssid_ap|" + (String) config.ssid_ap + "|input\n";
  //values += "password_ap|" +  (String) config.password_ap + "|input\n";
	values += "ip_0|" +  (String) config.IP[0] + "|input\n";
	values += "ip_1|" +  (String) config.IP[1] + "|input\n";
	values += "ip_2|" +  (String) config.IP[2] + "|input\n";
	values += "ip_3|" +  (String) config.IP[3] + "|input\n";
	values += "nm_0|" +  (String) config.Netmask[0] + "|input\n";
	values += "nm_1|" +  (String) config.Netmask[1] + "|input\n";
	values += "nm_2|" +  (String) config.Netmask[2] + "|input\n";
	values += "nm_3|" +  (String) config.Netmask[3] + "|input\n";
	values += "gw_0|" +  (String) config.Gateway[0] + "|input\n";
	values += "gw_1|" +  (String) config.Gateway[1] + "|input\n";
	values += "gw_2|" +  (String) config.Gateway[2] + "|input\n";
	values += "gw_3|" +  (String) config.Gateway[3] + "|input\n";

  values += "dns1_0|" +  (String) config.dns1[0] + "|input\n";
	values += "dns1_1|" +  (String) config.dns1[1] + "|input\n";
	values += "dns1_2|" +  (String) config.dns1[2] + "|input\n";
	values += "dns1_3|" +  (String) config.dns1[3] + "|input\n";

  //values += "dns2_0|" +  (String) config.dns2[0] + "|input\n";
	//values += "dns2_1|" +  (String) config.dns2[1] + "|input\n";
	//values += "dns2_2|" +  (String) config.dns2[2] + "|input\n";
	//values += "dns2_3|" +  (String) config.dns2[3] + "|input\n";

	values += "dhcp|" +  (String) (config.dhcp ? "checked" : "") + "|chk\n";
	server.send ( 200, "text/plain", values);
//	Serial.println(__FUNCTION__); 
	
}


#if 0
const char PAGE_NetworkConfiguration[] PROGMEM = R"=====(
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
<div id="setting">
  <fieldset>
  <form action="" method="get">
  <h3>Network Configuration</h3>
  <div><label>DHCP Mode: </label>
    <!--<select id="wrmode" name="wrmode" width=100% onchange="updatemodewifi();" >-->
    <select id="wrmode" name="wrmode" width=100% onchange="updatemodewifi2();" >
      <option value=0 ~config_wrmode(0)~>AP mode</option>
      <option value=1 ~config_wrmode(1)~>STA and AP mode</option>
      <option value=2 ~config_wrmode(2)~>STA multiple join and AP mode</option>
      <option value=3 ~config_wrmode(3)~>STA Connected OFF AP mode</option>
      <option value=4 ~config_wrmode(4)~>STA multiple join Connected OFF AP mode</option>
      <option value=5 ~config_wrmode(5)~>STA </option>
      <option value=6 ~config_wrmode(6)~>STA  multiple join </option>
    </select>
  </div>
  <h3>AP Setting</h3>
  <table border="0"  cellspacing="0" cellpadding="3" style="width:400px"  >
  <tr><td align="right"><strong>SSID:</strong></td><td><input type="text" id="ssid_ap" name="ssid_ap" value="" ></td></tr>
  <tr><td align="right"><strong>Password:</strong></td><td><input type="password" id="password_ap" name="password_ap" value=""></td></tr>
  </table>
  <br>
  <h3>STA Setting</h3>
  <table border="0"  cellspacing="0" cellpadding="3" style="width:400px"  >
  <tr><td align="right"><strong>SSID:</strong></td><td><input type="text" id="ssid_sta" name="ssid_sta" value="" ></td></tr>
  <tr><td align="right"><strong>Password:</strong></td><td><input type="password" id="password_sta" name="password_sta" value=""></td></tr>

  <tr><td align="right"><strong>Mode STA By MAC Acesspoint :</strong></td><td>
  <select id="enable_apmac_sta" name="enable_apmac_sta"  onchange="updateapmac_sta();">
	<option value=0 ~config_enable_apmac_sta(0)~ >Disable</option>
	<option value=1 ~config_enable_apmac_sta(1)~>Enable</option>
  </select>
  </td></tr>
  <tr><td align="right"><strong>MAC Acesspoint :</strong></td><td><input type="text" id="apmac_sta" name="apmac_sta" value=""></td></tr>

  <tr><td align="right"><strong>DHCP:</strong></td><td align="left"><input type="checkbox" id="dhcp" name="dhcp" onclick="updatedhcp();"></td></tr>
  <tr><td align="right"><strong>IP:     </strong></td><td><input type="text" id="ip_0" name="ip_0" style="width:50px">.<input type="text" id="ip_1" name="ip_1" style="width:50px">.<input type="text" id="ip_2" name="ip_2" style="width:50px">.<input type="text" id="ip_3" name="ip_3" value="" style="width:50px"></td></tr>
  <tr><td align="right"><strong>Netmask:</strong></td><td><input type="text" id="nm_0" name="nm_0" style="width:50px">.<input type="text" id="nm_1" name="nm_1" style="width:50px">.<input type="text" id="nm_2" name="nm_2" style="width:50px">.<input type="text" id="nm_3" name="nm_3" style="width:50px"></td></tr>
  <tr><td align="right"><strong>Gateway:</strong></td><td><input type="text" id="gw_0" name="gw_0" style="width:50px">.<input type="text" id="gw_1" name="gw_1" style="width:50px">.<input type="text" id="gw_2" name="gw_2" style="width:50px">.<input type="text" id="gw_3" name="gw_3" style="width:50px"></td></tr>
  <tr><td colspan="2" align="center"><input type="submit" style="width:150px" class="btn btn--m btn--blue" value="Save"></td></tr>
  </table>
  </form>
  <hr>
  <strong>&nbsp;&nbsp;Connection State:</strong><div id="connectionstate">N/A</div>
  <hr>
  <strong>&nbsp;&nbsp;Networks:</strong><br>
  <table border="0"  cellspacing="3" style="width:310px" >
  <tr><td><div id="networks">Scanning...</div></td></tr>
  <tr><td align="center"><a href="javascript:GetState()" style="width:150px" class="btn btn--m btn--blue">Refresh</a></td></tr>
  </table>
  </fieldset>
<!-- END MAIN -->
</div>
<div class="spacer">&nbsp;</div>
<div id="footer">Copyright &copy; 2012 Primus Co., Ltd.</div>
</div></div></div></div></div>
</body>
</html>
</body>
<script>

function GetState()
{
  document.getElementById("networks").innerHTML = "Scanning..."; 
  setValues("/admin/connectionstate");
 
}
function selssid(value)
{
  document.getElementById("ssid_sta").value = value; 
}
function updatemodewifi()
{
   if (document.getElementById("wrmode").value === "0"){
     // apmode 
     document.getElementById("ssid_ap").disabled  = false
     document.getElementById("password_ap").disabled  = false
    
     document.getElementById("ssid_sta").disabled  = true
     document.getElementById("password_sta").disabled  = true
    
     document.getElementById("enable_apmac_sta").disabled  = true
     document.getElementById("apmac_sta").disabled = true

     document.getElementById("dhcp").disabled  = true
     
     document.getElementById("ip_0").disabled = true
     document.getElementById("ip_1").disabled = true
     document.getElementById("ip_2").disabled = true
     document.getElementById("ip_3").disabled = true

     document.getElementById("nm_0").disabled = true
     document.getElementById("nm_1").disabled = true
     document.getElementById("nm_2").disabled = true
     document.getElementById("nm_3").disabled = true

     document.getElementById("gw_0").disabled = true 
     document.getElementById("gw_1").disabled = true
     document.getElementById("gw_2").disabled = true 
     document.getElementById("gw_3").disabled = true
   }else if (document.getElementById("wrmode").value === "1" || document.getElementById("wrmode").value === "2" || document.getElementById("wrmode").value === "3" || document.getElementById("wrmode").value === "4" ){
        // ap and sta
    document.getElementById("ssid_ap").disabled  = false
    document.getElementById("password_ap").disabled  = false

    document.getElementById("ssid_sta").disabled  = false
    document.getElementById("password_sta").disabled  = false
    document.getElementById("enable_apmac_sta").disabled  = false
    document.getElementById("dhcp").disabled  = false
    
        updateapmac_sta();
        updatedhcp();
   }else{
     //sta mode 
    document.getElementById("ssid_ap").disabled  = true
    document.getElementById("password_ap").disabled  = true

    document.getElementById("ssid_sta").disabled  = false
    document.getElementById("password_sta").disabled  = false
    document.getElementById("enable_apmac_sta").disabled  = false
    document.getElementById("dhcp").disabled  = false

    updateapmac_sta();
    updatedhcp();
     
     
   }
  
 
}

function updatemodewifi2()
{
    document.getElementById("ssid_ap").disabled  = true
    document.getElementById("password_ap").disabled  = true

    document.getElementById("ssid_sta").disabled  = false
    document.getElementById("password_sta").disabled  = false
    document.getElementById("enable_apmac_sta").disabled  = false
    document.getElementById("dhcp").disabled  = false

    updateapmac_sta();
    updatedhcp();
}

function updateapmac_sta()
{
  document.getElementById("apmac_sta").disabled = (document.getElementById("enable_apmac_sta").value === "0" )?true:false
}
function updatedhcp()
{

  document.getElementById("ip_0").disabled =  document.getElementById("dhcp").checked;
  document.getElementById("ip_1").disabled =  document.getElementById("dhcp").checked;
  document.getElementById("ip_2").disabled =  document.getElementById("dhcp").checked;
  document.getElementById("ip_3").disabled =  document.getElementById("dhcp").checked;

  document.getElementById("nm_0").disabled =  document.getElementById("dhcp").checked;
  document.getElementById("nm_1").disabled =  document.getElementById("dhcp").checked;
  document.getElementById("nm_2").disabled =  document.getElementById("dhcp").checked;
  document.getElementById("nm_3").disabled =  document.getElementById("dhcp").checked;

  document.getElementById("gw_0").disabled =  document.getElementById("dhcp").checked;
  document.getElementById("gw_1").disabled =  document.getElementById("dhcp").checked;
  document.getElementById("gw_2").disabled =  document.getElementById("dhcp").checked;
  document.getElementById("gw_3").disabled =  document.getElementById("dhcp").checked;
  
}
window.onload = function ()
{
//  load("style.css","css", function() 
//  {
    load("microajax.js","js", function() 
    {
        //setTimeout(updatemodewifi2,100);
          setValues("/admin/values");
          setTimeout(GetState,3000);
    });
  
//  });
}
function load(e,t,n){if("js"==t){var a=document.createElement("script");a.src=e,a.type="text/javascript",a.async=!1,a.onload=function(){n()},document.getElementsByTagName("head")[0].appendChild(a)}else if("css"==t){var a=document.createElement("link");a.href=e,a.rel="stylesheet",a.type="text/css",a.async=!1,a.onload=function(){n()},document.getElementsByTagName("head")[0].appendChild(a)}}
</script>
</html>


)=====";
#endif