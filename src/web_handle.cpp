#include "main.h"
#include "web_handle.h"
#include "km07reg.h"


WebServer server(80);
type_Datatime strDateTime;
static const uint8_t monthDays[]={31,28,31,30,31,30,31,31,30,31,30,31}; 
#define LEAP_YEAR(Y) ( ((1970+Y)>0) && !((1970+Y)%4) && ( ((1970+Y)%100) || !((1970+Y)%400) ) )


const char PAGE_IndexPage[] PROGMEM = R"=====(
<html>
<head>
<title>KM-07T</title>
<link rel="stylesheet" href="css/mchp.css">
</head>
<body>
  
  <style>
  
  .next {
	background-color: #096209;
	color: white;
  }



	table {
	border-collapse: collapse;
	margin: 0 auto;
	}

	table,
	th,
	td {
	border: 1px solid black;
	}
    
	#myTable th,
    #myTable td {
	padding: 8px;
	text-align: center;
	border-bottom: 1px solid black;
	
    }

    #myTable th {
	background-color: rgb(255, 255, 255);
    }

    #myTable .column1 {
	background-color: #0ba30b;
	color: white;

	
  }
  
  #myTable .column2 {
	background-color: #ddd;
	
  }

  .myweight {

	font-weight: bolder;
  }


	.center {
            	display: flex;
                justify-content: center;
            }

 .btn-next{
	text-decoration: none;
	display: inline-block;
	padding: 8px 16px;
	font-weight: bolder;
	border-radius: 5px;
}

.btn-next:hover {

	background-color: #ddd;
	color: black;

}


.btn-next2{
	text-decoration: none;
	display: inline-block;
	padding: 8px 16px;
	font-weight: bolder;
}

.pageshow {


	text-decoration: none;
	display: inline-block;
	padding: 8px 16px;
	font-weight: bolder;
	
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



            <p><b>
                <font color="#006600">This Device is used to convert data from TCPIP to RS485 or RS232</font>
              </b></p>


            <div>
              <table id="myTable">

                <tr>

                </tr>

                <tr>

                  <td class="column1 myweight">VoltR</td>
                  <td class="column2 myweight" id="x_vr" ></td>
                  <td class="column1 myweight">VoltS</td>
                  <td class="column2 myweight" id="x_vs"></td>


                </tr>
                <tr>

                  <td class="column1 myweight">VoltT</td>
                  <td class="column2 myweight"  id="x_vt" ></td>
                  <td class="column1 myweight">AvgVoltphase</td>
                  <td class="column2 myweight"  id="x_vpavg" ></td>


                </tr>

                <tr>

                  <td class="column1 myweight">Volt_RS</td>
                  <td class="column2 myweight"  id="x_rs"></td>
                  <td class="column1 myweight">Volt_ST</td>
                  <td class="column2 myweight"  id="x_st"></td>

                </tr>


                <tr>

                  <td class="column1 myweight">Volt_TR</td>
                  <td class="column2 myweight"  id="x_tr"></td>
                  <td class="column1 myweight">AvgVoltLL</td>
                  <td class="column2 myweight"  id="AvgV"></td>


                </tr>


                <tr>
                  <td class="column1 myweight">Volt_unit</td>
                  <td class="column2 myweight" id="Volt_u"></td>
                  <td class="column1 myweight">Volt_DP</td>
                  <td class="column2 myweight" id="Volt_dp"></td>

                </tr>



                <tr>

                  <td class="column1 myweight">Amp_R</td>
                  <td class="column2 myweight"  id="a_r"></td>
                  <td class="column1 myweight">Amp_S</td>
                  <td class="column2 myweight"  id="a_s"></td>


                </tr>

                <tr>

                  <td class="column1 myweight">Amp_T</td>
                  <td class="column2 myweight" id="a_t"></td>
                  <td class="column1 myweight">Amp_N</td>
                  <td class="column2 myweight" id="a_n"></td>

                </tr>


                <tr>

                  <td class="column1 myweight">Amp_AVG</td>
                  <td class="column2 myweight" id="a_avg"></td>
                  <td class="column1 myweight">Amp_DP</td>
                  <td class="column2 myweight" id="a_dp"></td>

                </tr>



              </table>
              <br>


              <style>
                .center {
                  display: flex;
                  justify-content: center;
                }
              </style>

              <div style="display: flex;justify-content:space-between">
                <div> </div>
                <a style="margin-left:140px ;text-decoration: none;" class="btn-next2 .previous"></a>
                <a style="margin-left: 1px; " class="pageshow">Page 1</a>
                <a href="page2.html" style="margin-right:30px ;text-decoration: none;" class="next btn-next">Next</a>
              </div>






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

<script>
function GetState()
{
 // document.getElementById("x_waiting").innerHTML = "Waiting...."; 
  setValues("/admin/metervalue");
}
function update_infor()
{
  document.getElementById("ssid_ap").disabled  = false
}

window.onload = function ()
{
    load("microajax.js","js", function() 
    {
        GetState();
        update_infor();
    });

	setInterval(function(){
		GetState();
	},2000);
}


function load(e,t,n){if("js"==t){var a=document.createElement("script");a.src=e,a.type="text/javascript",a.async=!1,a.onload=function(){n()},document.getElementsByTagName("head")[0].appendChild(a)}else if("css"==t){var a=document.createElement("link");a.href=e,a.rel="stylesheet",a.type="text/css",a.async=!1,a.onload=function(){n()},document.getElementsByTagName("head")[0].appendChild(a)}}
</script>





)=====";



const char PAGE_Style_css[] PROGMEM = R"=====(
body { color: #000000; font-family: avenir, helvetica, arial, sans-serif;  letter-spacing: 0.15em;} 
hr {    background-color: #eee;    border: 0 none;   color: #eee;    height: 1px; } 
.btn, .btn:link, .btn:visited {  
	border-radius: 0.3em;  
	border-style: solid;  
	border-width: 1px;  
color: #111;  
display: inline-block;  
	font-family: avenir, helvetica, arial, sans-serif;  
	letter-spacing: 0.15em;  
	margin-bottom: 0.5em;  
padding: 1em 0.75em;  
	text-decoration: none;  
	text-transform: uppercase;  
	-webkit-transition: color 0.4s, background-color 0.4s, border 0.4s;  
transition: color 0.4s, background-color 0.4s, border 0.4s; 
} 
.btn:hover, .btn:focus {
color: #7FDBFF;  
border: 1px solid #7FDBFF;  
	-webkit-transition: background-color 0.3s, color 0.3s, border 0.3s;  
transition: background-color 0.3s, color 0.3s, border 0.3s; 
}
	.btn:active {  
color: #0074D9;  
border: 1px solid #0074D9;  
		-webkit-transition: background-color 0.3s, color 0.3s, border 0.3s;  
transition: background-color 0.3s, color 0.3s, border 0.3s; 
	} 
	.btn--s 
	{  
		font-size: 12px; 
	}
	.btn--m { 
		font-size: 14px; 
	}
	.btn--l {  
		font-size: 20px;  border-radius: 0.25em !important; 
	} 
	.btn--full, .btn--full:link {
		border-radius: 0.25em; 
display: block;  
			margin-left: auto; 
			margin-right: auto; 
			text-align: center; 
width: 100%; 
	} 
	.btn--blue:link, .btn--blue:visited {
color: #fff;  
		background-color: #0074D9; 
	}
	.btn--blue:hover, .btn--blue:focus {
color: #fff !important;  
		background-color: #0063aa;  
		border-color: #0063aa; 
	}
	.btn--blue:active {
color: #fff; 
		background-color: #001F3F;  border-color: #001F3F; 
	}
	@media screen and (min-width: 32em) {
		.btn--full {  
			max-width: 16em !important; } 
	}
)=====";

const char PAGE_microajax_js[] PROGMEM = R"=====(
function microAjax(B,A){this.bindFunction=function(E,D){return function(){return E.apply(D,[D])}};this.stateChange=function(D){if(this.request.readyState==4){this.callbackFunction(this.request.responseText)}};this.getRequest=function(){if(window.ActiveXObject){return new ActiveXObject("Microsoft.XMLHTTP")}else{if(window.XMLHttpRequest){return new XMLHttpRequest()}}return false};this.postBody=(arguments[2]||"");this.callbackFunction=A;this.url=B;this.request=this.getRequest();if(this.request){var C=this.request;C.onreadystatechange=this.bindFunction(this.stateChange,this);if(this.postBody!==""){C.open("POST",B,true);C.setRequestHeader("X-Requested-With","XMLHttpRequest");C.setRequestHeader("Content-type","application/x-www-form-urlencoded");C.setRequestHeader("Connection","close")}else{C.open("GET",B,true)}C.send(this.postBody)}};

function setValues(url)
{
	microAjax(url, function (res)
	{
		res.split(String.fromCharCode(10)).forEach(function(entry) {
		fields = entry.split("|");
    console.log(fields);
		if(fields[2] == "input")
		{
				document.getElementById(fields[0]).value = fields[1];
		}
		else if(fields[2] == "div")
		{
				document.getElementById(fields[0]).innerHTML  = fields[1];
		}
		else if(fields[2] == "chk")
		{
				document.getElementById(fields[0]).checked  = fields[1];
		}
    else if(fields[2] == "select")
    {
      document.getElementById(fields[0]).value  = fields[1];
    }
	  });
	});
}

)=====";



//test microajax2
const char PAGE_microajax2_js[] PROGMEM = R"=====(
function microAjax(B,A){this.bindFunction=function(E,D){return function(){return E.apply(D,[D])}};this.stateChange=function(D){if(this.request.readyState==4){this.callbackFunction(this.request.responseText)}};this.getRequest=function(){if(window.ActiveXObject){return new ActiveXObject("Microsoft.XMLHTTP")}else{if(window.XMLHttpRequest){return new XMLHttpRequest()}}return false};this.postBody=(arguments[2]||"");this.callbackFunction=A;this.url=B;this.request=this.getRequest();if(this.request){var C=this.request;C.onreadystatechange=this.bindFunction(this.stateChange,this);if(this.postBody!==""){C.open("POST",B,true);C.setRequestHeader("X-Requested-With","XMLHttpRequest");C.setRequestHeader("Content-type","application/x-www-form-urlencoded");C.setRequestHeader("Connection","close")}else{C.open("GET",B,true)}C.send(this.postBody)}};

function setValues(url)
{
	microAjax(url, function (res)
	{
		res.split(String.fromCharCode(10)).forEach(function(entry) {
		fields = entry.split("|");
    console.log(fields);
		if(fields[2] == "input")
		{
				document.getElementById(fields[0]).value = fields[1];
		}
		else if(fields[2] == "div")
		{
				document.getElementById(fields[0]).innerHTML  = fields[1];
		}
		else if(fields[2] == "chk")
		{
				document.getElementById(fields[0]).checked  = fields[1];
		}
    else if(fields[2] == "select")
    {
      document.getElementById(fields[0]).value  = fields[1];
    }
	  });
	});
}

)=====";




//test microajax3
const char PAGE_microajax3_js[] PROGMEM = R"=====(
function microAjax(B,A){this.bindFunction=function(E,D){return function(){return E.apply(D,[D])}};this.stateChange=function(D){if(this.request.readyState==4){this.callbackFunction(this.request.responseText)}};this.getRequest=function(){if(window.ActiveXObject){return new ActiveXObject("Microsoft.XMLHTTP")}else{if(window.XMLHttpRequest){return new XMLHttpRequest()}}return false};this.postBody=(arguments[2]||"");this.callbackFunction=A;this.url=B;this.request=this.getRequest();if(this.request){var C=this.request;C.onreadystatechange=this.bindFunction(this.stateChange,this);if(this.postBody!==""){C.open("POST",B,true);C.setRequestHeader("X-Requested-With","XMLHttpRequest");C.setRequestHeader("Content-type","application/x-www-form-urlencoded");C.setRequestHeader("Connection","close")}else{C.open("GET",B,true)}C.send(this.postBody)}};

function setValues(url)
{
	microAjax(url, function (res)
	{
		res.split(String.fromCharCode(10)).forEach(function(entry) {
		fields = entry.split("|");
    console.log(fields);
		if(fields[2] == "input")
		{
				document.getElementById(fields[0]).value = fields[1];
		}
		else if(fields[2] == "div")
		{
				document.getElementById(fields[0]).innerHTML  = fields[1];
		}
		else if(fields[2] == "chk")
		{
				document.getElementById(fields[0]).checked  = fields[1];
		}
    else if(fields[2] == "select")
    {
      document.getElementById(fields[0]).value  = fields[1];
    }
	  });
	});
}

)=====";
















// test next page2
const char PAGE_2[] PROGMEM = R"=====(

<html>
<head>
<title>KM-07T</title>
<link rel="stylesheet" href="css/mchp.css">
</head>
<body>
  <style>
    
  .next {
	background-color: #096209;
	color: white;
  }



	table {
	border-collapse: collapse;
	margin: 0 auto;
	}

	table,
	th,
	td {
	border: 1px solid black;
	}
    
	#myTable th,
    #myTable td {
	padding: 8px;
	text-align: center;
	border-bottom: 1px solid black;
	
    }

    #myTable th {
	background-color: rgb(255, 255, 255);
    }

    #myTable .column1 {
	background-color: #0ba30b;
	color: white;

	
  }
  
  #myTable .column2 {
	background-color: #ddd;
	
  }

  .myweight {

	font-weight: bolder;
  }


	.center {
            	display: flex;
                justify-content: center;
            }

 .btn-next{
	text-decoration: none;
	display: inline-block;
	padding: 8px 16px;
	font-weight: bolder;
	border-radius: 5px;
}

.btn-next:hover {

	background-color: #ddd;
	color: black;

}


.btn-next2{
	text-decoration: none;
	display: inline-block;
	padding: 8px 16px;
	font-weight: bolder;
}

.pageshow {


	text-decoration: none;
	display: inline-block;
	padding: 8px 16px;
	font-weight: bolder;
	
  }


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



            <p><b>
                <font color="#006600">This Device is used to convert data from TCPIP to RS485 or RS232</font>
              </b></p>


            <div>
              <table id="myTable">

                <tr>

                </tr>

                <tr>

                  <td class="column1 myweight">PF_R</td>
                  <td class="column2 myweight" id="pf_r"></td>
                  
                  <td class="column1 myweight">PF_S</td>
                  <td class="column2 myweight" id = "pf_s"></td>


                </tr>
                <tr>

                  <td class="column1 myweight">PF_T</td>
                  <td class="column2 myweight" id = "pf_t"></td>
                  <td class="column1 myweight">Avg_PF</td>
                  <td class="column2 myweight" id ="pf_avg"></td>


                </tr>

                <tr>

                  <td class="column1 myweight">Freq_R</td>
                  <td class="column2 myweight" id = "f_r"></td>
                  <td class="column1 myweight">Freq_S</td>
                  <td class="column2 myweight" id = "f_s"></td>

                </tr>


                <tr>

                  <td class="column1 myweight">Freq_T</td>
                  <td class="column2 myweight" id = "f_t"></td>
                  <td class="column1 myweight">Watt_R</td>
                  <td class="column2 myweight" id = "w_r"></td>


                </tr>


                <tr>
                  <td class="column1 myweight">Watt_S</td>
                  <td class="column2 myweight" id ="w_s"></td>
                  <td class="column1 myweight">Watt_T</td>
                  <td class="column2 myweight" id = "w_t"></td>

                </tr>



                <tr>

                  <td class="column1 myweight">TotalWatt</td>
                  <td class="column2 myweight" id = "w_tt"></td>
                  <td class="column1 myweight">var_R</td>
                  <td class="column2 myweight" id= "v_r"></td>


                </tr>

                <tr>

                  <td class="column1 myweight">var_S</td>
                  <td class="column2 myweight" id = "v_s"></td>
                  <td class="column1 myweight">var_T</td>
                  <td class="column2 myweight" id = "v_t"></td>

                </tr>


                <tr>

                  <td class="column1 myweight">Total_var</td>
                  <td class="column2 myweight" id = "v_tt"></td>
                  <td class="column1 myweight">VA_R</td>
                  <td class="column2 myweight" id = "va_r"></td>

                </tr>



              </table>
              <br>


              <style>
                .center {
                  display: flex;
                  justify-content: center;
                }
              </style>

              <div style="display: flex;justify-content:space-between">
                <div> </div>
                <a href="index.html" style="margin-left:140px ;text-decoration: none;" class="next btn-next">Previous</a>
                <a style="margin-left: 1px; " class="pageshow">Page 2</a>
                <a href="page3.html" style="margin-right:30px ;text-decoration: none;" class="next btn-next">Next</a>
              </div>






            </div>
            <div class="spacer">&nbsp;</div>
            <div id="footer">Copyright &copy; 2012 Primus Co., Ltd.</div>
          </div>
        </div>
      </div>
    </div>
  </div>
</body>


<script>
  function GetState() {
    // document.getElementById("x_waiting").innerHTML = "Waiting...."; 
    setValues("/admin/metervalue2");
  }
  function update_infor() {
    document.getElementById("ssid_ap").disabled = false
  }

  window.onload = function () {
     
  
    load("microajax2.js", "js", function () {
      GetState();
      update_infor();
    });

	setinterval(function(){
		GetState();
	},2000);

    
  }

  function load(e, t, n) { if ("js" == t) { var a = document.createElement("script"); a.src = e, a.type = "text/javascript", a.async = !1, a.onload = function () { n() }, document.getElementsByTagName("head")[0].appendChild(a) } else if ("css" == t) { var a = document.createElement("link"); a.href = e, a.rel = "stylesheet", a.type = "text/css", a.async = !1, a.onload = function () { n() }, document.getElementsByTagName("head")[0].appendChild(a) } }
</script>

</html>

	)=====";


const char PAGE_3[] PROGMEM = R"=====(


<html>
<head>
<title>KM-07T</title>
<link rel="stylesheet" href="css/mchp.css">
</head>
<body>
  <style>
    
  .next {
	background-color: #096209;
	color: white;
  }



	table {
	border-collapse: collapse;
	margin: 0 auto;
	}

	table,
	th,
	td {
	border: 1px solid black;
	}
    
	#myTable th,
    #myTable td {
	padding: 8px;
	text-align: center;
	border-bottom: 1px solid black;
	
    }

    #myTable th {
	background-color: rgb(255, 255, 255);
    }

    #myTable .column1 {
	background-color: #0ba30b;
	color: white;

	
  }
  
  #myTable .column2 {
	background-color: #ddd;
	
  }

  .myweight {

	font-weight: bolder;
  }


	.center {
            	display: flex;
                justify-content: center;
            }

 .btn-next{
	text-decoration: none;
	display: inline-block;
	padding: 8px 16px;
	font-weight: bolder;
	border-radius: 5px;
}

.btn-next:hover {

	background-color: #ddd;
	color: black;

}


.btn-next2{
	text-decoration: none;
	display: inline-block;
	padding: 8px 16px;
	font-weight: bolder;
}

.pageshow {


	text-decoration: none;
	display: inline-block;
	padding: 8px 16px;
	font-weight: bolder;
	
  }


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



            <p><b>
                <font color="#006600">This Device is used to convert data from TCPIP to RS485 or RS232</font>
              </b></p>


            <div>
              <table id="myTable">

                <tr>

                </tr>

                <tr>

                  <td class="column1 myweight">VA_S</td>
                  <td class="column2 myweight" id = "va_s"></td>
                  <td class="column1 myweight">VA_T</td>
                  <td class="column2 myweight" id = "va_t"></td>


                </tr>
                <tr>

                  <td class="column1 myweight">Total_VA</td>
                  <td class="column2 myweight" id = "va_tt"></td>
                  <td class="column1 myweight">Power_Unit</td>
                  <td class="column2 myweight" id = "pw_u"></td>


                </tr>

                <tr>

                  <td class="column1 myweight">Power_Dp</td>
                  <td class="column2 myweight" id = "pw_dp"></td>
                  <td class="column1 myweight">Demand_kW</td>
                  <td class="column2 myweight" id = "de_kw" ></td>

                </tr>


                <tr>

                  <td class="column1 myweight">Demand_kvar</td>
                  <td class="column2 myweight" id = "de_kv"></td>
                  <td class="column1 myweight">Demand_kVA</td>
                  <td class="column2 myweight" id = "de_kva"></td>


                </tr>


                <tr>
                  <td class="column1 myweight">UangleR</td>
                  <td class="column2 myweight" id = "ua_ler"></td>
                  <td class="column1 myweight">UangleS</td>
                  <td class="column2 myweight" id = "ua_les"></td>

                </tr>



                <tr>

                  <td class="column1 myweight">UangleT</td>
                  <td class="column2 myweight" id = "ua_let"></td>
                  <td class="column1 myweight">IangleR</td>
                  <td class="column2 myweight" id = "Ian_r"></td>


                </tr>

                <tr>

                  <td class="column1 myweight">IangleS</td>
                  <td class="column2 myweight" id = "Ian_s"></td>
                  <td class="column1 myweight">IangleT</td>
                  <td class="column2 myweight" id = "Ian_t"></td>

                </tr>




              </table>
              <br>


              <style>
                .center {
                  display: flex;
                  justify-content: center;
                }
              </style>

              <div style="display: flex;justify-content:space-between">
                <div> </div>
                <a href="page2.html" style="margin-left:140px ;text-decoration: none;" class="next btn-next">Previous</a>
                <a style="margin-left: 1px; " class="pageshow">Page 3</a>
                <a href="index.html" style="margin-right:30px ;text-decoration: none;" class="next btn-next">Main page</a>
              </div>






            </div>
            <div class="spacer">&nbsp;</div>
            <div id="footer">Copyright &copy; 2012 Primus Co., Ltd.</div>
          </div>
        </div>
      </div>
    </div>
  </div>
</body>






<script>
  function GetState() {
    // document.getElementById("x_waiting").innerHTML = "Waiting...."; 
    setValues("/admin/metervalue3");
  }
  function update_infor() {
    document.getElementById("ssid_ap").disabled = false
  }

  window.onload = function () {
     
  
    load("microajax3.js", "js", function () {
      GetState();
      update_infor();
    });

	setinterval(function(){
		GetState();
	},2000);

    
  }

  function load(e, t, n) { if ("js" == t) { var a = document.createElement("script"); a.src = e, a.type = "text/javascript", a.async = !1, a.onload = function () { n() }, document.getElementsByTagName("head")[0].appendChild(a) } else if ("css" == t) { var a = document.createElement("link"); a.href = e, a.rel = "stylesheet", a.type = "text/css", a.async = !1, a.onload = function () { n() }, document.getElementsByTagName("head")[0].appendChild(a) } }
</script>

</html>

	)=====";



const char mqtt_page[] PROGMEM = R"=====(
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
              <h1>MQTT Configuration</h1>
              <p>Enter the new settings for MQTT:</p>
              <form action="" method="get">
                <fieldset>
                  <h3 class="top" style="background-color: #096209; color: white;">Host</h3>
                  <div><label>Hostname:</label>
                    <input type="text" id="h_name" name="h_name" value="" />
                  </div>

                  <h3 id="myHeading" style="background-color: #096209; color: white;"> Port </h3>
                  <div><label>Port: </label>
                    <input type="text" id="por_mqtt" name="por_mqtt" value="" maxlength="5" placeholder="Port number ">
                    <p>Port for MQTT</p>
                  </div>
                  <div>
                  </div>
                  <br>
                  <h3 style="background-color: #096209; color: white;">Account for MQTT</h3>
                  <div><label>Username: </label>
                    <input type="text" id="user_mqtt" name="user_mqtt" value="" maxlength="8" placeholder="Username">
                  </div>
                  <div><label>Password: </label>
                    <input type="password" id="pass_mqtt" name="pass_mqtt" value="" maxlength="8" placeholder="Password">
                    <br>
                    Maximum characters of 8
                  </div>
                 
                  <br>
                  <h3 style="background-color: #096209; color: white;">Topic for MQTT</h3>
                   <div><label>Publish Topic: </label>
                    <input type="text" id="pub_topic" name="pub_topic" value="" placeholder="Publish Topic">
                    </div>
                    <br>
                    <div><label>subscribe Topic: </label>
                    <input type="text" id="sub_topic" name="sub_topic" value="" placeholder="subscribe Topic">
                    </div>

                  <br>
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









void ConvertUnixTimeStamp( unsigned long TimeStamp, type_Datatime* DateTime)
{
		uint8_t year;
	uint8_t month, monthLength;
	uint32_t time;
	unsigned long days;
	  time = (uint32_t)TimeStamp;
	  DateTime->second = time % 60;
	  time /= 60; // now it is minutes
	  DateTime->minute = time % 60;
	  time /= 60; // now it is hours
	  DateTime->hour = time % 24;
	  time /= 24; // now it is days
	  DateTime->wday = ((time + 4) % 7) + 1;  // Sunday is day 1 
  
	  year = 0;  
	days = 0;
	while((unsigned)(days += (LEAP_YEAR(year) ? 366 : 365)) <= time) {
		year++;
	}
	DateTime->year = year; // year is offset from 1970 
  
	  days -= LEAP_YEAR(year) ? 366 : 365;
	  time  -= days; // now it is days in this year, starting at 0
  
	  days=0;
	  month=0;
	  monthLength=0;
	  for (month=0; month<12; month++) {
		if (month==1) { // february
		  if (LEAP_YEAR(year)) {
			monthLength=29;
		  } else {
			monthLength=28;
		  }
		} else {
		  monthLength = monthDays[month];
		}
    
		if (time >= monthLength) {
		  time -= monthLength;
		} else {
			break;
		}
	  }
	  DateTime->month = month + 1;  // jan is month 1  
	  DateTime->day = time + 1;     // day of month
	  DateTime->year += 1970;

	 
}

String GetMacAddress()
{
	uint8_t mac[6];
    char macStr[18] = {0};
	ETH.macAddress(mac);
    sprintf(macStr, "%02X:%02X:%02X:%02X:%02X:%02X", mac[0],  mac[1], mac[2], mac[3], mac[4], mac[5]);
    return  String(macStr);
}

boolean checkRange(String Value)
{
	 if (Value.toInt() < 0 || Value.toInt() > 255)
	 {
		 return false;
	 }
	 else
	 {
		 return true;
	 }
}

// convert a single hex digit character to its integer value (from https://code.google.com/p/avr-netino/)
unsigned char h2int(char c)
{
    if (c >= '0' && c <='9'){
        return((unsigned char)c - '0');
    }
    if (c >= 'a' && c <='f'){
        return((unsigned char)c - 'a' + 10);
    }
    if (c >= 'A' && c <='F'){
        return((unsigned char)c - 'A' + 10);
    }
    return(0);
}

String urldecode(String input) // (based on https://code.google.com/p/avr-netino/)
{
	 char c;
	 String ret = "";
	 
	 for(byte t=0;t<input.length();t++)
	 {
		 c = input[t];
		 if (c == '+') c = ' ';
         if (c == '%') {


         t++;
         c = input[t];
         t++;
         c = (h2int(c) << 4) | h2int(input[t]);
		 }
		
		 ret.concat(c);
	 }
	 return ret;


  
  
}


void send_jsfile ()
{
   String Script_checkIntPro = "";
    if(config.ipmode == 1)
   {
     Script_checkIntPro = "<script>function initRemoteIP() {\ndocument.getElementById(\"ip_0\").disabled = false;\ndocument.getElementById(\"ip_1\").disabled = false;\ndocument.getElementById(\"ip_2\").disabled = false;\ndocument.getElementById(\"ip_3\").disabled = false;\n}</script>";
   }
   else
   {
     Script_checkIntPro = "<script>function initRemoteIP() {\ndocument.getElementById(\"ip_0\").disabled = true;\ndocument.getElementById(\"ip_1\").disabled = true;\ndocument.getElementById(\"ip_2\").disabled = true;\ndocument.getElementById(\"ip_3\").disabled = true;\n}</script>";
   }
   server.send ( 200, "text/html", Script_checkIntPro);
}


void send_meter_values_html ()
{



  String values ="";
  values += "x_vr|" +(String)regKm07.VoltR+"|div\n"; 
  values += "x_vs|" +(String)regKm07.VoltS +"|div\n";
  values += "x_vt|" +(String)regKm07.VoltT +"|div\n";
  values += "x_vpavg|" +(String)regKm07.AvgVoltphase +"|div\n";
  values += "x_rs|" +(String)regKm07.Volt_RS +"|div\n";
  values += "x_st|" +(String)regKm07.Volt_ST +"|div\n";
  values += "x_tr|" +(String)regKm07.Volt_TR +"|div\n";
  values += "AvgV|" +(String)regKm07.AvgVoltLL +"|div\n";
  values += "Volt_u|" +(String)regKm07.Volt_unit +"|div\n";
  values += "Volt_dp|" +(String)regKm07.Volt_DP +"|div\n";
  values += "a_r|" +(String)regKm07.Amp_R +"|div\n";
  values += "a_s|" +(String)regKm07.Amp_S +"|div\n";
  values += "a_t|" +(String)regKm07.Amp_T +"|div\n";
  values += "a_avg|" +(String)regKm07.Amp_AVG +"|div\n";
  values += "a_n|" +(String)regKm07.Amp_N +"|div\n";
  values += "a_dp|" +(String)regKm07.Amp_DP +"|div\n";
 
  

  server.send ( 200, "text/plain", values);
}


void send_meter_values_html2 ()
{

String values ="";
values += "pf_r|" +(String)regKm07.PF_R+"|div\n"; 
values += "pf_s|" +(String)regKm07.PF_S +"|div\n";
values += "pf_t|" +(String)regKm07.PF_T +"|div\n";
values += "pf_avg|" +(String)regKm07.Avg_PF +"|div\n";
values += "f_r|" +(String)regKm07.Freq_R +"|div\n";
values += "f_s|" +(String)regKm07.Freq_S +"|div\n";
values += "f_t|" +(String)regKm07.Freq_T +"|div\n";
values += "w_r|" +(String)regKm07.Watt_R +"|div\n";
values += "w_s|" +(String)regKm07.Watt_S +"|div\n";
values += "w_t|" +(String)regKm07.Watt_T +"|div\n";
values += "w_tt|" +(String)regKm07.TotalWatt +"|div\n";
values += "v_s|" +(String)regKm07.var_S +"|div\n";
values += "v_t|" +(String)regKm07.var_T +"|div\n";
values += "v_tt|" +(String)regKm07.Total_var +"|div\n";
values += "va_r|" +(String)regKm07.VA_R +"|div\n";
values += "v_r|" +(String)regKm07.var_R +"|div\n";









server.send ( 200, "text/plain2", values);

}


void send_meter_values_html3 ()
{

String values ="";
values += "va_s|" +(String)regKm07.VA_S + "|div\n";
values += "va_t|" +(String)regKm07.VA_T +"|div\n";
values += "va_tt|" +(String)regKm07.Total_VA +"|div\n";
values += "pw_u|" +(String)regKm07.Power_Unit +"|div\n";
values += "pw_dp|" +(String)regKm07.Power_Dp +"|div\n";
values += "de_kw|" +(String)regKm07.Demand_kW +"|div\n";
values += "de_kv|" +(String)regKm07.Demand_kvar +"|div\n";
values += "de_kva|" +(String)regKm07.Demand_kVA +"|div\n";
values += "ua_ler|" +(String)regKm07.UangleR+"|div\n";
values += "ua_les|" +(String)regKm07.UangleS +"|div\n";
values += "ua_let|" +(String)regKm07.UangleT +"|div\n";
values += "Ian_r|" +(String)regKm07.IangleR +"|div\n";
values += "Ian_s|" +(String)regKm07.IangleS +"|div\n";
values += "Ian_t|" +(String)regKm07.IangleT +"|div\n";

server.send ( 200, "text/plain3", values);

}






void send_mqtt_configuration_html()
{

//     String Script_checkIntPro = "";
//   if (server.args() > 0 )  // Save Settings
//   {
//     String temp = "";
//     for ( uint8_t i = 0; i < server.args(); i++ ) {


//       if (server.argName(i) == "h_name") config.h_name =  server.arg(i).toInt();
//       if (server.argName(i) == "por_mqtt") config.por_mqtt =  server.arg(i).toInt();
//       if (server.argName(i) == "user_mqtt") config.user_mqtt =  urldecode(server.arg(i));
//       if (server.argName(i) == "pass_mqtt") config.pass_mqtt =  urldecode(server.arg(i));


//     }

// 		WriteConfig();    
//       delay(10);
//     ESP.restart();
// //    ConfigSerial();
//     //ts.enable(4);
    
//   }
//   // else
//   //   {
//   //   if(!server.authenticate(config.www_username.c_str(), config.www_password.c_str()))
//   //       return server.requestAuthentication();
//   //   }
//     server.send ( 200, "text/html", mqtt_page  ); 
}



void send_mqtt_configuration_values_html()
{
  
  // String values ="";
  

  // values += "h_name|" + (String) config.h_name + "|input\n";
  // values += "por_mqtt|" +  (String) config.por_mqtt + "|select\n";
  // values += "user_mqtt|" +  (String) config.user_mqtt + "|select\n";
  // values += "pass_mqtt|" +  (String) config.pass_mqtt + "|select\n";


  // server.send ( 200, "text/plain", values);
  
}

