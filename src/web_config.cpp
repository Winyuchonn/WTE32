#include "main.h"
#include "web_config.h"
#include "web_handle.h"

const char PAGE_GeneralConfiguration[] PROGMEM = R"=====(
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
            <div id="content">
              <h1 >General Configuration</h1>
              <p>This page allows the configuration of the board's network settings.</p>
              <p class="warning">
                <b>CAUTION:</b> Incorrect settings may cause the board to lose network
                connectivity. Recovery options will be provided on the next page.
              </p>
              <p>Enter the new settings for the board below:</p>
              <form action="" method="get">
                <fieldset>
                  <h3 class="top" style="background-color: #096209; color: white;">Device Info</h3>
                  <div><label>MAC Address:</label>
                    <input type="text" id="x_mac" name="x_mac" value="" />
                  </div>

                  <h3 style="background-color: #096209; color: white;"> Port 1</h3>
                  <div><label>Bridge port: </label>
                    <input type="text" id="porA" name="porA" value="" maxlength="5" placeholder="Port number 1">
                    <p>Port number must be 100 to 50000 only</p>
                  </div>
                  <div><label>Baud Rate: </label>
                    <select id="bauA" name="bauA" width=100%>
                      <option value=0 ~config_baudA(0)~>2400 bps</option>
                      <option value=1 ~config_baudA(1)~>4800 bps</option>
                      <option value=2 ~config_baudA(2)~>9600 bps</option>
                      <option value=3 ~config_baudA(3)~>19200 bps</option>
                      <option value=4 ~config_baudA(4)~>38400 bps</option>
                      <option value=5 ~config_baudA(5)~>57600 bps</option>
                      <!--<option value=6 ~config_baudA(6)~>115200 bps</option>-->
                    </select>
                  </div>
                  <div><label>Data size: </label>
                    <select id="sizA" name="sizA" width=100%>
                      <option value=0 ~config_sizeA(0)~>7</option>
                      <option value=1 ~config_sizeA(1)~>8</option>
                    </select>
                  </div>
                  <div><label>Parity: </label>
                    <select id="parA" name="parA" width=100%>
                      <option value=0 ~config_parityA(0)~>None</option>
                      <option value=1 ~config_parityA(1)~>Odd</option>
                      <option value=2 ~config_parityA(2)~>Even</option>
                    </select>
                  </div>
                  <div><label>Stop Bits: </label>
                    <select id="stoA" name="stoA" width=100%>
                      <option value=1 ~config_stopbitA(0)~>One</option>
                      <option value=2 ~config_stopbitA(1)~>Two</option>
                    </select>
                  </div>
                  <div><label>Communication Mode: </label>
                    <select id="modA" name="modA" width=100%>
                      <option value=0 ~config_modeA(0)~>Modbus</option>
                      <option value=1 ~config_modeA(1)~>Modbus Over TCP</option>
                    </select>
                  </div>
                  <br>

                  <h3 id="myHeading" style="background-color: #096209; color: white;"> Port 2</h3>
                  <div><label>Bridge port: </label>
                    <input type="text" id="por_2" name="por_2" value="" maxlength="5" placeholder="Port number 2">
                    <p>Port number must be 100 to 50000 only</p>
                  </div>
                  <div><label>Baud Rate: </label>
                    <select id="bau_2" name="bau_2" width=100%>
                      <option value=0 ~config_baud_2(0)~>2400 bps</option>
                      <option value=1 ~config_baud_2(1)~>4800 bps</option>
                      <option value=2 ~config_baud_2(2)~>9600 bps</option>
                      <option value=3 ~config_baud_2(3)~>19200 bps</option>
                      <option value=4 ~config_baud_2(4)~>38400 bps</option>
                      <option value=5 ~config_baud_2(5)~>57600 bps</option>
                      <option value=6 ~config_baud_2(6)~>115200 bps</option>
                    </select>
                  </div>
                  <div><label>Data size: </label>
                    <select id="siz_2" name="siz_2" width=100%>
                      <option value=0 ~config_size_2(0)~>7</option>
                      <option value=1 ~config_size_2(1)~>8</option>
                    </select>
                  </div>
                  <div><label>Parity: </label>
                    <select id="par_2" name="par_2" width=100%>
                      <option value=0 ~config_parity_2(0)~>None</option>
                      <option value=1 ~config_parity_2(1)~>Odd</option>
                      <option value=2 ~config_parity_2(2)~>Even</option>
                    </select>
                  </div>
                  <div><label>Stop Bits: </label>
                    <select id="sto_2" name="sto_2" width=100%>
                      <option value=1 ~config_stopbit_2(0)~>One</option>
                      <option value=2 ~config_stopbit_2(1)~>Two</option>
                    </select>
                  </div>
                  <div><label>Communication Mode: </label>
                    <select id="mod_2" name="mod_2" width=100%>
                      <option value=0 ~config_mode_2(0)~>Modbus</option>
                      <option value=1 ~config_mode_2(1)~>Modbus Over TCP</option>
                    </select>
                  </div>
                  <br>
                  <h3 style="background-color: #096209; color: white;">Account Setting</h3>
                  <div><label>Username: </label>
                    <input type="text" id="user" name="user" value="" maxlength="8" placeholder="Username">
                  </div>
                  <div><label>Password: </label>
                    <input type="password" id="pass" name="pass" value="" maxlength="8" placeholder="Password">
                    <br>
                    <br>
              
                    Maximum characters of 8
                  </div>
                  <br>
                </fieldset>
                <div>
                  <div align="center">
                    <p><input type="submit" class="sm" value="Save" /></p>
                  </div>
                </div>
              </form>
            </div>


            <!--
<div id="content">
<fieldset>
      <h3 class="top">Update Firmware</h3>
      <form method="POST" action="#" enctype="multipart/form-data" id="upload_form">
        <input type="file" name="update" id="file">
        <input type="submit" style="width: 6rem;" value="Update">
      </form>
      
      <div id="prg_wrap" style=" padding:0.5rem ;border: 0px solid; width: 70%;">
         <div id="prg" style="text-shadow: 2px 2px 3px black; border-radius: 1rem;  display: none; border: 1px solid #006600; background: #006600; text-align: center; color: white;"></div>
      </div>
</fieldset>
</div>
//-->

            <div class="spacer">&nbsp;</div>
            <div id="footer">Copyright &copy; 2012 Primus Co., Ltd.</div>
          </div>
        </div>
      </div>
    </div>
  </div>
</body>
<script>
  var domReady = function (callback) {
    document.readyState === "interactive" || document.readyState === "complete" ? callback() : document.addEventListener("DOMContentLoaded", callback);
  };

  domReady(function () {
    var myform = document.getElementById('upload_form');
    var filez = document.getElementById('file');

    myform.onsubmit = function (event) {
      event.preventDefault();

      var formData = new FormData();
      var file = filez.files[0];

      if (!file) { return false; }

      formData.append("files", file, file.name);

      var xhr = new XMLHttpRequest();
      xhr.upload.addEventListener("progress", function (evt) {
        if (evt.lengthComputable) {
          var per = Math.round((evt.loaded / evt.total) * 100);
          var prg = document.getElementById('prg');

          prg.innerHTML = per + "%"
          prg.style.width = (per * 0.7) + "%" //size prg 80% width
          prg.style.display = "block"
        }
      }, false);
      xhr.open('POST', '/upload_ota', true);

      // Set up a handler for when the request finishes.
      xhr.onload = function () {
        if (xhr.status === 200) {
          alert('Success');
          setTimeout(function () {
            window.location.reload();
          }, 2000);

        } else {
          alert('An error occurred!');
        }
      };

      xhr.send(formData);
    }
  });
</script>
<script>

</script>
<script>
  window.onload = function () {
    load("microajax.js", "js", function () { setValues("/admin/configvalues"); });
    //  initRemoteIP();
    load("myjsfile.js", "js", function () {

    });
  }
  function load(e, t, n) { if ("js" == t) { var a = document.createElement("script"); a.src = e, a.type = "text/javascript", a.async = !1, a.onload = function () { n() }, document.getElementsByTagName("head")[0].appendChild(a) } else if ("css" == t) { var a = document.createElement("link"); a.href = e, a.rel = "stylesheet", a.type = "text/css", a.async = !1, a.onload = function () { n() }, document.getElementsByTagName("head")[0].appendChild(a) } }
</script>
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
      form.submit();
    }
  });
});




</script>

</html>
)=====";

const char PAGE_WaitRestart[] PROGMEM = R"=====(
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




void send_general_configuration_html()
{

    String Script_checkIntPro = "";
  if (server.args() > 0 )  // Save Settings
  {
    String temp = "";
    for ( uint8_t i = 0; i < server.args(); i++ ) {


      if (server.argName(i) == "porA") config.port =  server.arg(i).toInt();
      if (server.argName(i) == "sizA") config.datasize =  server.arg(i).toInt();
      if (server.argName(i) == "parA") config.parity =  server.arg(i).toInt();
      if (server.argName(i) == "bauA") config.baudrate =  server.arg(i).toInt();
      if (server.argName(i) == "stoA") config.stopbit =  server.arg(i).toInt();
      if (server.argName(i) == "modA") config.commode =  server.arg(i).toInt();

      //if (server.argName(i) == "ipmod") config.ipmode =  server.arg(i).toInt();
      if (server.argName(i) == "user") config.www_username =  urldecode(server.arg(i));
      if (server.argName(i) == "pass") config.www_password =  urldecode(server.arg(i));


      if(server.argName(i) == "por_2") config.port_2 =  server.arg(i).toInt();
      if(server.argName(i) == "siz_2") config.datasize_2 =  server.arg(i).toInt();
      if(server.argName(i) == "par_2") config.parity_2 =  server.arg(i).toInt();
      if(server.argName(i) == "bau_2") config.baudrate_2 =  server.arg(i).toInt();
      if(server.argName(i) == "sto_2") config.stopbit_2 =  server.arg(i).toInt();
      if(server.argName(i) == "mod_2") config.commode_2 =  server.arg(i).toInt();

    }
    server.send ( 200, "text/html", PAGE_WaitRestart );
    Serial.println("Save config ");
   Serial.println(config.port);
		WriteConfig();    
      delay(10);
    ESP.restart();
//    ConfigSerial();
    //ts.enable(4);
    
  }
  else
    {
    if(!server.authenticate(config.www_username.c_str(), config.www_password.c_str()))
        return server.requestAuthentication();
    }
    server.send ( 200, "text/html", PAGE_GeneralConfiguration  ); 
}

void send_general_configuration_values_html()
{
  
  String values ="";
  
  values += "x_mac|" + GetMacAddress() +  "|input\n";
  //values += "ip_0|" +  (String) config.IP_client[0] + "|input\n";
  //values += "ip_1|" +  (String) config.IP_client[1] + "|input\n";
  //values += "ip_2|" +  (String) config.IP_client[2] + "|input\n";
  //values += "ip_3|" +  (String) config.IP_client[3] + "|input\n";
  values += "porA|" + (String) config.port + "|input\n";
  values += "bauA|" +  (String) config.baudrate + "|select\n";
  values += "sizA|" +  (String) config.datasize + "|select\n";
  values += "parA|" +  (String) config.parity + "|select\n";
  values += "stoA|" +  (String) config.stopbit + "|select\n";
  values += "modA|" +  (String) config.commode + "|select\n";

  values += "por_2|" + (String) config.port_2 + "|input\n";
  values += "bau_2|" +  (String) config.baudrate_2 + "|select\n";
  values += "siz_2|" +  (String) config.datasize_2 + "|select\n";
  values += "par_2|" +  (String) config.parity_2 + "|select\n";
  values += "sto_2|" +  (String) config.stopbit_2 + "|select\n";
  values += "mod_2|" +  (String) config.commode_2 + "|select\n";

  //values += "ipmod|" +  (String) config.ipmode + "|select\n";
  values += "user|" +  (String) config.www_username + "|input\n";
  values += "pass|" +  (String) config.www_password + "|input\n";
  server.send ( 200, "text/plain", values);
  
}


#if 0

#endif