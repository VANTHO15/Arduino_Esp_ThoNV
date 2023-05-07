#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ArduinoOTA.h>
MDNSResponder mdns;
ESP8266WebServer server(80);

const char* ssid = "Bao Truc";
const char* pass = "24682468";

const char* www_username = "admin";
const char* www_password = "123456";
const char* www_realm = "Custom Auth Realm";
String authFailResponse = "Authentication Failed";

#define LED1 2
#define LED2 16

int trangthairelay1 = 0;
int trangthairelay2 = 0;

int bien = 0;
int bien1 = 0;
int bien2 = 0;
const char webpage[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <meta http-equiv="refresh" content="3000">
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js"></script>
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.1.3/css/bootstrap.min.css">
    <script src="https://maxcdn.bootstrapcdn.com/bootstrap/4.1.3/js/bootstrap.min.js"></script>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/paho-mqtt/1.0.1/mqttws31.js" type="text/javascript"></script> 
</head>

<style>
body {font-family: Time New Roman;}
.tab {
    overflow: hidden;
    border: 1px solid #ccc;
    background-color: #FFCC00;
}

.tabcontent {
    display: none;
    padding: 6px 12px;
    border: 1px solid #ccc;
    border-top: none;

}

</style>

<script type="text/javascript">

   function changeFunc() {
    var selectBox = document.getElementById("selectBox");
    var selectedValue = selectBox.options[selectBox.selectedIndex].value;
    console.log(selectedValue);
  if(selectedValue == 1)
  {
    openCity(event, 'Dieukhien');
  }
  else if(selectedValue == 2)
  {
    openCity(event, 'CamBien');
  }
  else if(selectedValue == 3)
  {
    openCity(event, 'DuPhong1');
  }
  else if(selectedValue == 4)
  {
    openCity(event, 'DuPhong2');
  }
  else
  {
    openCity(event, 'GioiThieu');
  }
   }
  </script>

<body onload="openCity(event, 'GioiThieu')" style= "background-color: #00FFFF;">
        
        <div style="position: fixed">

              <span style = "color: Blue ;"> <b>Chọn</b> </span> 
                  <select id="selectBox"  onchange="changeFunc()">
                      <option value = "0" >Giới Thiệu</option>
                    <option value = "1">Điều Khiển</option>
                    <option value = "2">Cảm Biến</option>
                    <option value = "3">Dự Phòng 1</option>
                    <option value = "4">Dự Phòng 2</option>      
                  </select>
        </div>    
          
<div id="Dieukhien" class="tabcontent"> 
     <table width="1000" height="400" border="6" cellpadding="10" align="center">  
   <tr>
        <th bgcolor="#FF9900"  colspan="5"> <center> <font size="10"> <span style = "color: red"> Điều Khiển Thiết Bị</span></font></center></th>
   </tr>  
   
   
   <tr>
        <td bgcolor="#FFFF00" colspan="1"> <center> <span style = "color: Blue"> <b>  Line 1 </b>  </span> </center> </td>
        <td bgcolor="#00FF00" colspan="1" align="center" >  
          <button id="btnOn1"   type="button" class="btn btn-success" onclick="ON1Click()" >ON 1</button> 
              <button id="btnOff1" type="button" class="btn btn-danger" onclick="OFF1Click()" >OFF 1</button>       
        </td>
    <td bgcolor="#FFFF00" colspan="1"> <center> <span style = "color: Blue"> <b>  Line 2 </b>  </span> </center> </td>
    <td bgcolor="#00FF00" colspan="2" align="center">  
         <button id="btnOn2" type="button" class="btn btn-success"onclick="ON2Click()">ON 2</button>    
           <button id="btnOff2" type="button" class="btn btn-danger" onclick="OFF2Click()" >OFF 2</button>          
        </td>   
     </tr>
   
   <tr>
        <td bgcolor="#FFFF00" colspan="1"> <center> <span style = "color: Blue"> <b>  Line 3 </b>  </span> </center> </td>
        <td bgcolor="#00FF00" colspan="1" align="center">  
          <button id="btnOn1"   type="button" class="btn btn-success" onclick="ON3Click()" >ON 3</button> 
              <button id="btnOff1" type="button" class="btn btn-danger" onclick="OFF3Click()" >OFF 3</button>       
        </td>
    <td bgcolor="#FFFF00" colspan="1"> <center> <span style = "color: Blue"> <b>  Line 4 </b>  </span> </center> </td>
    <td bgcolor="#00FF00" colspan="2" align="center">  
         <button id="btnOn2" type="button" class="btn btn-success"onclick="ON4Click()">ON 4</button>    
           <button id="btnOff2" type="button" class="btn btn-danger" onclick="OFF4Click()" >OFF 4</button>          
        </td>   
     </tr>
   <tr>
        <td bgcolor="#FFFF00" colspan="1"> <center> <span style = "color: Blue"> <b>  Line 5 </b>  </span> </center> </td>
        <td bgcolor="#00FF00" colspan="1" align="center">  
          <button id="btnOn1"   type="button" class="btn btn-success" onclick="ON3Click()" >ON 3</button> 
              <button id="btnOff1" type="button" class="btn btn-danger" onclick="OFF3Click()" >OFF 3</button>       
        </td>
    <td bgcolor="#FFFF00" colspan="1"> <center> <span style = "color: Blue"> <b>  Line 6 </b>  </span> </center> </td>
    <td bgcolor="#00FF00" colspan="2" align="center">  
         <button id="btnOn2" type="button" class="btn btn-success"onclick="ON4Click()">ON 4</button>    
           <button id="btnOff2" type="button" class="btn btn-danger" onclick="OFF4Click()" >OFF 4</button>            
        </td>   
     </tr>
   <tr>
        <td bgcolor="#FFFF00" colspan="1"> <center> <span style = "color: Blue"> <b>  Line 7 </b>  </span> </center> </td>
        <td bgcolor="#00FF00" colspan="1" align="center">  
          <button id="btnOn1"   type="button" class="btn btn-success" onclick="ON3Click()" >ON 3</button> 
              <button id="btnOff1" type="button" class="btn btn-danger" onclick="OFF3Click()" >OFF 3</button>       
        </td>
    <td bgcolor="#FFFF00" colspan="1"> <center> <span style = "color: Blue"> <b>  Line 8 </b>  </span> </center> </td>
    <td bgcolor="#00FF00" colspan="2" align="center">  
         <button id="btnOn2" type="button" class="btn btn-success"onclick="ON4Click()">ON 4</button>    
           <button id="btnOff2" type="button" class="btn btn-danger" onclick="OFF4Click()" >OFF 4</button>            
        </td>   
     </tr>
   <tr>
        <td bgcolor="#FFFF00" colspan="1"> <center> <span style = "color: Blue"> <b>  Line 9 </b>  </span> </center> </td>
        <td bgcolor="#00FF00" colspan="1" align="center">  
          <button id="btnOn1"   type="button" class="btn btn-success" onclick="ON3Click()" >ON 3</button> 
              <button id="btnOff1" type="button" class="btn btn-danger" onclick="OFF3Click()" >OFF 3</button>       
        </td>
    <td bgcolor="#FFFF00" colspan="1"> <center> <span style = "color: Blue"> <b>  Line 10 </b>  </span> </center> </td>
    <td bgcolor="#00FF00" colspan="2" align="center">  
         <button id="btnOn2" type="button" class="btn btn-success"onclick="ON4Click()">ON 4</button>    
           <button id="btnOff2" type="button" class="btn btn-danger" onclick="OFF4Click()" >OFF 4</button>          
        </td>   
     </tr>
   
   <tr>
        <td bgcolor="#FFFF00" colspan="1"> <center> <span style = "color: Blue"> <b>  Line 9 </b>  </span> </center> </td>
        <td bgcolor="#00FF00" colspan="1" align="center">  
          <button id="btnOn1"   type="button" class="btn btn-success" onclick="ON3Click()" >ON 3</button> 
              <button id="btnOff1" type="button" class="btn btn-danger" onclick="OFF3Click()" >OFF 3</button>       
        </td>
    <td bgcolor="#FFFF00" colspan="1"> <center> <span style = "color: Blue"> <b>  Line 10 </b>  </span> </center> </td>
    <td bgcolor="#00FF00" colspan="2" align="center">  
         <button id="btnOn2" type="button" class="btn btn-success"onclick="ON4Click()">ON 4</button>    
           <button id="btnOff2" type="button" class="btn btn-danger" onclick="OFF4Click()" >OFF 4</button>          
        </td>   
     </tr>
   
   <tr>
        <td bgcolor="#FFFF00" colspan="1"> <center> <span style = "color: Blue"> <b>  Line 9 </b>  </span> </center> </td>
        <td bgcolor="#00FF00" colspan="1" align="center">  
          <button id="btnOn1"   type="button" class="btn btn-success" onclick="ON3Click()" >ON 3</button> 
              <button id="btnOff1" type="button" class="btn btn-danger" onclick="OFF3Click()" >OFF 3</button>       
        </td>
    <td bgcolor="#FFFF00" colspan="1"> <center> <span style = "color: Blue"> <b>  Line 10 </b>  </span> </center> </td>
    <td bgcolor="#00FF00" colspan="2" align="center">  
         <button id="btnOn2" type="button" class="btn btn-success"onclick="ON4Click()">ON 4</button>    
           <button id="btnOff2" type="button" class="btn btn-danger" onclick="OFF4Click()" >OFF 4</button>          
        </td>   
     </tr>
   
   <tr>
        <td bgcolor="#FFFF00" colspan="1"> <center> <span style = "color: Blue"> <b>  Line 9 </b>  </span> </center> </td>
        <td bgcolor="#00FF00" colspan="1" align="center">  
          <button id="btnOn1"   type="button" class="btn btn-success" onclick="ON3Click()" >ON 3</button> 
              <button id="btnOff1" type="button" class="btn btn-danger" onclick="OFF3Click()" >OFF 3</button>       
        </td>
    <td bgcolor="#FFFF00" colspan="1"> <center> <span style = "color: Blue"> <b>  Line 10 </b>  </span> </center> </td>
    <td bgcolor="#00FF00" colspan="2" align="center">  
         <button id="btnOn2" type="button" class="btn btn-success"onclick="ON4Click()">ON 4</button>    
           <button id="btnOff2" type="button" class="btn btn-danger" onclick="OFF4Click()" >OFF 4</button>          
        </td>   
     </tr>
   
   <tr>
        <td bgcolor="#FFFF00" colspan="1"> <center> <span style = "color: Blue"> <b>  Line 9 </b>  </span> </center> </td>
        <td bgcolor="#00FF00" colspan="1" align="center">  
          <button id="btnOn1"   type="button" class="btn btn-success" onclick="ON3Click()" >ON 3</button> 
              <button id="btnOff1" type="button" class="btn btn-danger" onclick="OFF3Click()" >OFF 3</button>       
        </td>
    <td bgcolor="#FFFF00" colspan="1"> <center> <span style = "color: Blue"> <b>  Line 10 </b>  </span> </center> </td>
    <td bgcolor="#00FF00" colspan="2" align="center">  
         <button id="btnOn2" type="button" class="btn btn-success"onclick="ON4Click()">ON 4</button>    
           <button id="btnOff2" type="button" class="btn btn-danger" onclick="OFF4Click()" >OFF 4</button>          
        </td>   
     </tr>
   
   <tr>
        <td bgcolor="#FFFF00" colspan="1"> <center> <span style = "color: Blue"> <b>  Line 9 </b>  </span> </center> </td>
        <td bgcolor="#00FF00" colspan="1" align="center">  
          <button id="btnOn1"   type="button" class="btn btn-success" onclick="ON3Click()" >ON 3</button> 
              <button id="btnOff1" type="button" class="btn btn-danger" onclick="OFF3Click()" >OFF 3</button>       
        </td>
    <td bgcolor="#FFFF00" colspan="1"> <center> <span style = "color: Blue"> <b>  Line 10 </b>  </span> </center> </td>
    <td bgcolor="#00FF00" colspan="2" align="center">  
         <button id="btnOn2" type="button" class="btn btn-success"onclick="ON4Click()">ON 4</button>    
           <button id="btnOff2" type="button" class="btn btn-danger" onclick="OFF4Click()" >OFF 4</button>          
        </td>   
     </tr>
   
   <tr>
        <td bgcolor="#FFFF00" colspan="1"> <center> <span style = "color: Blue"> <b>  Line 9 </b>  </span> </center> </td>
        <td bgcolor="#00FF00" colspan="1" align="center">  
          <button id="btnOn1"   type="button" class="btn btn-success" onclick="ON3Click()" >ON 3</button> 
              <button id="btnOff1" type="button" class="btn btn-danger" onclick="OFF3Click()" >OFF 3</button>       
        </td>
    <td bgcolor="#FFFF00" colspan="1"> <center> <span style = "color: Blue"> <b>  Line 10 </b>  </span> </center> </td>
    <td bgcolor="#00FF00" colspan="2" align="center">  
         <button id="btnOn2" type="button" class="btn btn-success"onclick="ON4Click()">ON 4</button>    
           <button id="btnOff2" type="button" class="btn btn-danger" onclick="OFF4Click()" >OFF 4</button>          
        </td>   
     </tr>
   
   <tr>
        <td bgcolor="#FFFF00" colspan="1"> <center> <span style = "color: Blue"> <b>  Line 9 </b>  </span> </center> </td>
        <td bgcolor="#00FF00" colspan="1" align="center">  
          <button id="btnOn1"   type="button" class="btn btn-success" onclick="ON3Click()" >ON 3</button> 
              <button id="btnOff1" type="button" class="btn btn-danger" onclick="OFF3Click()" >OFF 3</button>       
        </td>
    <td bgcolor="#FFFF00" colspan="1"> <center> <span style = "color: Blue"> <b>  Line 10 </b>  </span> </center> </td>
    <td bgcolor="#00FF00" colspan="2" align="center">  
         <button id="btnOn2" type="button" class="btn btn-success"onclick="ON4Click()">ON 4</button>    
           <button id="btnOff2" type="button" class="btn btn-danger" onclick="OFF4Click()" >OFF 4</button>          
        </td>   
     </tr>
   
   <tr>
        <td bgcolor="#FFFF00" colspan="1"> <center> <span style = "color: Blue"> <b>  Line 9 </b>  </span> </center> </td>
        <td bgcolor="#00FF00" colspan="1" align="center">  
          <button id="btnOn1"   type="button" class="btn btn-success" onclick="ON3Click()" >ON 3</button> 
              <button id="btnOff1" type="button" class="btn btn-danger" onclick="OFF3Click()" >OFF 3</button>       
        </td>
    <td bgcolor="#FFFF00" colspan="1"> <center> <span style = "color: Blue"> <b>  Line 10 </b>  </span> </center> </td>
    <td bgcolor="#00FF00" colspan="2" align="center">  
         <button id="btnOn2" type="button" class="btn btn-success"onclick="ON4Click()">ON 4</button>    
           <button id="btnOff2" type="button" class="btn btn-danger" onclick="OFF4Click()" >OFF 4</button>          
        </td>   
     </tr>
   <tr>
        <td bgcolor="#FFFF00" colspan="1"> <center> <span style = "color: Blue"> <b>  Line 9 </b>  </span> </center> </td>
        <td bgcolor="#00FF00" colspan="1" align="center">  
          <button id="btnOn1"   type="button" class="btn btn-success" onclick="ON3Click()" >ON 3</button> 
              <button id="btnOff1" type="button" class="btn btn-danger" onclick="OFF3Click()" >OFF 3</button>       
        </td>
    <td bgcolor="#FFFF00" colspan="1"> <center> <span style = "color: Blue"> <b>  Line 10 </b>  </span> </center> </td>
    <td bgcolor="#00FF00" colspan="2" align="center">  
         <button id="btnOn2" type="button" class="btn btn-success"onclick="ON4Click()">ON 4</button>    
           <button id="btnOff2" type="button" class="btn btn-danger" onclick="OFF4Click()" >OFF 4</button>          
        </td>   
     </tr>
   <tr>
        <td bgcolor="#FFFF00" colspan="1"> <center> <span style = "color: Blue"> <b>  Line 9 </b>  </span> </center> </td>
        <td bgcolor="#00FF00" colspan="1" align="center">  
          <button id="btnOn1"   type="button" class="btn btn-success" onclick="ON3Click()" >ON 3</button> 
              <button id="btnOff1" type="button" class="btn btn-danger" onclick="OFF3Click()" >OFF 3</button>       
        </td>
    <td bgcolor="#FFFF00" colspan="1"> <center> <span style = "color: Blue"> <b>  Line 10 </b>  </span> </center> </td>
    <td bgcolor="#00FF00" colspan="2" align="center">  
         <button id="btnOn2" type="button" class="btn btn-success"onclick="ON4Click()">ON 4</button>    
           <button id="btnOff2" type="button" class="btn btn-danger" onclick="OFF4Click()" >OFF 4</button>          
        </td>   
     </tr>
   <tr>
        <td bgcolor="#FFFF00" colspan="1"> <center> <span style = "color: Blue"> <b>  Line 9 </b>  </span> </center> </td>
        <td bgcolor="#00FF00" colspan="1" align="center">  
          <button id="btnOn1"   type="button" class="btn btn-success" onclick="ON3Click()" >ON 3</button> 
              <button id="btnOff1" type="button" class="btn btn-danger" onclick="OFF3Click()" >OFF 3</button>       
        </td>
    <td bgcolor="#FFFF00" colspan="1"> <center> <span style = "color: Blue"> <b>  Line 10 </b>  </span> </center> </td>
    <td bgcolor="#00FF00" colspan="2" align="center">  
         <button id="btnOn2" type="button" class="btn btn-success"onclick="ON4Click()">ON 4</button>    
           <button id="btnOff2" type="button" class="btn btn-danger" onclick="OFF4Click()" >OFF 4</button>          
        </td>   
     </tr>
   <tr>
        <td bgcolor="#FFFF00" colspan="1"> <center> <span style = "color: Blue"> <b>  Line 9 </b>  </span> </center> </td>
        <td bgcolor="#00FF00" colspan="1" align="center">  
          <button id="btnOn1"   type="button" class="btn btn-success" onclick="ON3Click()" >ON 3</button> 
              <button id="btnOff1" type="button" class="btn btn-danger" onclick="OFF3Click()" >OFF 3</button>       
        </td>
    <td bgcolor="#FFFF00" colspan="1"> <center> <span style = "color: Blue"> <b>  Line 10 </b>  </span> </center> </td>
    <td bgcolor="#00FF00" colspan="2" align="center">  
         <button id="btnOn2" type="button" class="btn btn-success"onclick="ON4Click()">ON 4</button>    
           <button id="btnOff2" type="button" class="btn btn-danger" onclick="OFF4Click()" >OFF 4</button>          
        </td>   
     </tr>
   <tr>
        <td bgcolor="#FFFF00" colspan="1"> <center> <span style = "color: Blue"> <b>  Line 9 </b>  </span> </center> </td>
        <td bgcolor="#00FF00" colspan="1" align="center">  
          <button id="btnOn1"   type="button" class="btn btn-success" onclick="ON3Click()" >ON 3</button> 
              <button id="btnOff1" type="button" class="btn btn-danger" onclick="OFF3Click()" >OFF 3</button>       
        </td>
    <td bgcolor="#FFFF00" colspan="1"> <center> <span style = "color: Blue"> <b>  Line 10 </b>  </span> </center> </td>
    <td bgcolor="#00FF00" colspan="2" align="center">  
         <button id="btnOn2" type="button" class="btn btn-success"onclick="ON4Click()">ON 4</button>    
           <button id="btnOff2" type="button" class="btn btn-danger" onclick="OFF4Click()" >OFF 4</button>          
        </td>   
     </tr>

       
   </table> 
  
</div>

<div id="CamBien" class="tabcontent">

  <table width="1000" height="400" border="6" cellpadding="10" align="center">
     <tr>
        <th  bgcolor="#FF9900" colspan="2"> <center> <font size="10"> <span style = "color: red"> THÔNG SỐ CẢM BIẾN</span></font></center></th>
   </tr>
    
   <tr>
        <td  bgcolor="#FFFF00" colspan="1"> <center> <span style = "color: Blue"> <b> Nhiệt Độ </b> </span> </center> </td>
        <td bgcolor="#FF00FF" colspan="1">
        <input id="DOLUX" type="text" size="40" placeholder="Độ Lux Hiện Tại" >
        </td>
     </tr>
   
   <tr>
        <td  bgcolor="#FFFF00" colspan="1"> <center> <span style = "color: Blue"> <b> Độ Ẩm </b> </span> </center> </td>
        <td bgcolor="#FF00FF" colspan="1">
        <input id="SETUP_LUX" type="text" size="40" placeholder="Độ Lux Đã Cài Đặt" >
        </td>
     </tr>
   
   <tr>
        <td  bgcolor="#FFFF00" colspan="1"> <center> <span style = "color: Blue"> <b> Ánh Sáng </b> </span> </center> </td>
        <td bgcolor="#FF00FF" colspan="1">
        <input id="CONGSUAT" type="text" size="40" placeholder="Công Suất Điều Khiển" >
        </td>
     </tr>
   
   <tr>
        <td  bgcolor="#FFFF00" colspan="1"> <center> <span style = "color: Blue"> <b> Cài Đặt Lux (AUTO)</b> </span> </center> </td>
        <td bgcolor="#FF00FF" colspan="1">
        <input id="SETUP_LUX_SEND" type="text" size="40" placeholder="Cài Đặt Lux" >
      <button id="btnSEND" type="button" class="btn btn-success" onclick = "SEND_LUX()">Send</button>
        </td>
     </tr>
   
  
  </table>
  
</div>
<div id="DuPhong1" class="tabcontent">

<table width="1000" height="400" border="6" cellpadding="10" align="center">

   <tr>
        <th bgcolor="#FF9900" colspan="2"> <center> <font size="10"> <span style = "color: red"> CHẾ ĐỘ MANUAL</span></font></center></th>
   </tr>
   
    <tr>
        <td  bgcolor="#FFFF00" colspan="1"> <center> <span style = "color: Blue"> <b>  Độ Lux </b> </span> </center> </td>
        <td bgcolor="#FF00FF" colspan="1">
        <input id="DoLuxCamBien_Manual" type="text" size="40" placeholder="Độ Lux Cảm Biến" >
        </td>
     </tr>
   
   <tr>
        <th bgcolor="#00FF00" colspan="2"> <center> <font size="10"> <span style = "color: red"> Công Suất Điều Khiển Từng Line</span></font></center></th>
   </tr>
   
   
   <tr>
        <td  bgcolor="#FFFF00" colspan="1"> <center> <span style = "color: Blue"> <b>  Line 1</b> </span> </center> </td>
        <td bgcolor="#FF00FF" colspan="1">
        <input id="CONGSUAT_LINE1" type="text" size="40" placeholder="Công Suất Điều Khiển Line 1" >
        </td>
     </tr>
   
   <tr>
        <td  bgcolor="#FFFF00" colspan="1"> <center> <span style = "color: Blue"> <b>  Line 2</b> </span> </center> </td>
        <td bgcolor="#FF00FF" colspan="1">
        <input id="CONGSUAT_LINE2" type="text" size="40" placeholder="Công Suất Điều Khiển Line 2" >
        </td>
     </tr>
   
   <tr>
        <td  bgcolor="#FFFF00" colspan="1"> <center> <span style = "color: Blue"> <b>  Line 3</b> </span> </center> </td>
        <td bgcolor="#FF00FF" colspan="1">
        <input id="CONGSUAT_LINE3" type="text" size="40" placeholder="Công Suất Điều Khiển Line 3" >
        </td>
     </tr>
   
   <tr>
        <td  bgcolor="#FFFF00" colspan="1"> <center> <span style = "color: Blue"> <b>  Line 4</b> </span> </center> </td>
        <td bgcolor="#FF00FF" colspan="1">
        <input id="CONGSUAT_LINE4" type="text" size="40" placeholder="Công Suất Điều Khiển Line 4" >
        </td>
     </tr>
   
   <tr>
        <th bgcolor="#00FF00" colspan="2"> <center> <font size="10"> <span style = "color: red"> Điều Khiển Công Suất Theo Line</span></font></center></th>
   </tr>   
   <tr>
        <td  bgcolor="#FFFF00" colspan="1"> 
         
         <center>  
              <span style = "color: Blue"> <b> Chọn Line</b> </span> 
                  <select id = "chon">
                      <option value = "ALL">All</option>
                    <option value = "1">1</option>
                    <option value = "2">2</option>
                    <option value = "3">3</option>
                    <option value = "4">4</option>       
                  </select>
       </center>
    </td>
    
    
        <td bgcolor="#FF00FF" colspan="1">
        <input type = "range" style = "width:350px " min = "1" max = "100" id = "get00" step = "1" onchange= "fetch00()"/>
      <input type = "text" size = "2" id = "put00" value = "51%"/> 
      <button style="height:50px;width:100px" id="btnSendDim" type="button" class="btn btn-success" onclick = "SETDIM()">Set</button>
      </br>
      <font size="5"> <span style = "color: Blue"> Line 1  :  &nbsp </span></font>
      <input type = "text" size = "2" id = "LINE1" placeholder = "0%"/> 
      
      <font size="5"> <span style = "color: Blue"> Line 2 : &nbsp </span></font>
      <input type = "text" size = "2" id = "LINE2" placeholder = "0%"/> 
      
      <font size="5"> <span style = "color: Blue"> Line 3 : &nbsp </span></font>
      <input type = "text" size = "2" id = "LINE3" placeholder = "0%"/> 
      
      <font size="5"> <span style = "color: Blue"> Line 4 : &nbsp </span></font>
      <input type = "text" size = "2" id = "LINE4" placeholder = "0%"/>       
        </td>   
     </tr> 
  </table>
</div>
</br>


<div id="DuPhong2" class="tabcontent">
  <table width="1000" height="400" border="6" cellpadding="10" align="center">
  
    <tr>
        <th bgcolor="#FF9900" colspan="11"> <center> <font size="10"> <span style = "color: red"> DỮ LIỆU CHUNG</span></font></center></th>
      </tr>
    
    <tr>
          <td bgcolor="#00FF00" colspan="11"> 
        <span style = "color: Blue"> <b> Đèn  </b> </span>  
        <input id="Den" type="text" size="5" placeholder="Đèn" >
        
        <span style = "color: Blue"> <b> Line  </b> </span>  
        <input id="Line" type="text" size="5" placeholder="Line" >
        
        <span style = "color: Blue"> <b> Điện Áp  </b> </span>
        <input id="DienAp" type="text" size="5" placeholder="Điện Áp" >
        
        <span style = "color: Blue"> <b> Dòng Điện  </b> </span>
        <input id="DongDien" type="text" size="5" placeholder="Dòng Điện" >
        
        <span style = "color: Blue"> <b> Công Suất  </b> </span>
        <input id="CongSuat" type="text" size="5" placeholder="Công Suất" >
        
        <span style = "color: Blue"> <b> Note  </b> </span>
        <input id="GhiChu" type="text" size="20" placeholder="Ghi Chú" >
        
      </td>
      </tr>
    
        <tr>
        <th bgcolor="#FF9900" colspan="11"> <center> <font size="6"> <span style = "color: red"> THÔNG SỐ HIỆN TẠI ĐÈN</span></font></center></th>
      </tr>
    
    

    
    <tr>
        <td bgcolor="#FFFF00" colspan="1">
           <span style = "color: Blue"> <b> Đèn 1  </b> </span>  
      </td>
            <td bgcolor="#00FF00" colspan="10"> 
        
        <span style = "color: Blue"> <b> Line  </b> </span>  
        <input id="Line1" type="text" size="5" placeholder="Line" >
        
        <span style = "color: Blue"> <b> Điện Áp  </b> </span>
        <input id="DienAp1" type="text" size="5" placeholder="Điện Áp" >
        
        <span style = "color: Blue"> <b> Dòng Điện  </b> </span>
        <input id="DongDien1" type="text" size="5" placeholder="Dòng Điện" >
        
        <span style = "color: Blue"> <b> Công Suất  </b> </span>
        <input id="CongSuat1" type="text" size="5" placeholder="Công Suất" >
        
        <span style = "color: Blue"> <b> Ghi Chú  </b> </span>
        <input id="GhiChu1" type="text" size="20" placeholder="Ghi Chú" >
        
      </td>
             
        </tr>
    
    
    <tr>
      <td bgcolor="#FFFF00" colspan="1">
           <span style = "color: Blue"> <b> Đèn 2  </b> </span>  
      </td>
      
            <td bgcolor="#00FF00" colspan="10"> 
          
        <span style = "color: Blue"> <b> Line  </b> </span>  
        <input id="Line2" type="text" size="5" placeholder="Line" >
        
        <span style = "color: Blue"> <b> Điện Áp  </b> </span>
        <input id="DienAp2" type="text" size="5" placeholder="Điện Áp" >
        
        <span style = "color: Blue"> <b> Dòng Điện  </b> </span>
        <input id="DongDien2" type="text" size="5" placeholder="Dòng Điện" >
        
        <span style = "color: Blue"> <b> Công Suất  </b> </span>
        <input id="CongSuat2" type="text" size="5" placeholder="Công Suất" >
        
        <span style = "color: Blue"> <b> Ghi Chú  </b> </span>
        <input id="GhiChu2" type="text" size="20" placeholder="Ghi Chú" >
        
      </td>
             
        </tr>
    
    
    <tr>
      <td bgcolor="#FFFF00" colspan="1">
           <span style = "color: Blue"> <b> Đèn 3  </b> </span>  
      </td>
      
            <td bgcolor="#00FF00" colspan="10"> 
         
        
        <span style = "color: Blue"> <b> Line  </b> </span>  
        <input id="Line3" type="text" size="5" placeholder="Line" >
        
        <span style = "color: Blue"> <b> Điện Áp  </b> </span>
        <input id="DienAp3" type="text" size="5" placeholder="Điện Áp" >
        
        <span style = "color: Blue"> <b> Dòng Điện  </b> </span>
        <input id="DongDien3" type="text" size="5" placeholder="Dòng Điện" >
        
        <span style = "color: Blue"> <b> Công Suất  </b> </span>
        <input id="CongSuat3" type="text" size="5" placeholder="Công Suất" >
        
        <span style = "color: Blue"> <b> Ghi Chú  </b> </span>
        <input id="GhiChu3" type="text" size="20" placeholder="Ghi Chú" >
      </td>
             
        </tr>
    
      
    <tr>
      
      <td bgcolor="#FFFF00" colspan="1">
           <span style = "color: Blue"> <b> Đèn 4  </b> </span>  
      </td>
      
            <td bgcolor="#00FF00"colspan="10"> 
          
        <span style = "color: Blue"> <b> Line  </b> </span>  
        <input id="Line4" type="text" size="5" placeholder="Line" >
        
        <span style = "color: Blue"> <b> Điện Áp  </b> </span>
        <input id="DienAp4" type="text" size="5" placeholder="Điện Áp" >
        
        <span style = "color: Blue"> <b> Dòng Điện  </b> </span>
        <input id="DongDien4" type="text" size="5" placeholder="Dòng Điện" >
        
        <span style = "color: Blue"> <b> Công Suất  </b> </span>
        <input id="CongSuat4" type="text" size="5" placeholder="Công Suất" >
        
        <span style = "color: Blue"> <b> Ghi Chú  </b> </span>
        <input id="GhiChu4" type="text" size="20" placeholder="Ghi Chú" >
        
      </td>
             
        </tr>   
  </table> 
</div>

<div id="GioiThieu" class="tabcontent">

   <h1>Xin Chào!!! Lớp Học IOT Online</h1>
</div>
</br>

<script>
function openCity(evt, cityName) {
    var i, tabcontent, tablinks;
    tabcontent = document.getElementsByClassName("tabcontent");
    for (i = 0; i < tabcontent.length; i++) {
        tabcontent[i].style.display = "none";
    }
    tablinks = document.getElementsByClassName("tablinks");
    for (i = 0; i < tablinks.length; i++) {
        tablinks[i].className = tablinks[i].className.replace(" active", "");
    }
    document.getElementById(cityName).style.display = "block";
    evt.currentTarget.className += " active";

}

</script>
</body>
</html> 
)=====";



void setup()
{
  Serial.begin(9600);
  while (!Serial);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  WiFi.mode(WIFI_AP_STA);
  WiFi.disconnect();
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println();
  Serial.println("Connect WiFi");
  Serial.print("Address IP esp: ");
  Serial.println(WiFi.localIP());

  server.on("/", []() {
    if (!server.authenticate(www_username, www_password))
      return server.requestAuthentication(DIGEST_AUTH, www_realm, authFailResponse);
      server.send(200, "text/html", webpage);
  });

  
  server.on("/", [] {
    server.send(200, "text/html", webpage);
  });

  server.on("/OnClick1", [] {
    Serial.println(">>Onclick button 111111");
    
    bien++;
    Serial.print("bien:"); 
    Serial.println(bien);
    if(bien%2 == 1)
    {
      Serial.println(">>ON LED 1");
      digitalWrite(LED1, LOW);
      trangthairelay1 = 1;
    }
    else
    {
      Serial.println(">>OFF LED 1");
      digitalWrite(LED1, HIGH);
      trangthairelay1 = 0;
    }
    server.send(200, "text/html", webpage );
  });


  

   server.on("/OnClick2", [] {
    Serial.println(">>Onclick button 222222");
    if(trangthairelay2 == 0)
    {
      Serial.println(">>ON LED 2");
      trangthairelay2 = 1;
      digitalWrite(LED2, HIGH);
    }
    else if(trangthairelay2 == 1)
    {
      Serial.println(">>OFF LED 2");
      trangthairelay2 = 0;
      digitalWrite(LED2, LOW);
    }
    server.send(200, "text/html", webpage );
  });
  


  server.on("/sendtext1", [] {
    Serial.println(server.arg("ssid1"));
    // gửi uno mySerial.println(server.arg("ssid1"));
    // xử lý cho esp
    String text1 = "";
    text1 = server.arg("ssid1");
    Serial.print("text1:");
     Serial.println(text1);
    server.send(200, "text/html", webpage );
  });


  server.on("/sendtext2", [] {
    Serial.println(server.arg("ssid2"));
     // gửi uno mySerial.println(server.arg("ssid2"));
    server.send(200, "text/html", webpage );
  });
  
  server.begin();

  Serial.println("Server start");

  
}

void loop() 
{
  
  server.handleClient();

}




void SendDataWeb( String sensor1 ,  String sensor2 ,  String sensor3 , String sensor4 )
{
  // Data json {"nhietdo":"giatrinhietdo", "doam":"giatridoam" , "anhsang":"giatrianhanh"}
  //"{\"nhietdo\":\" ", \"doam\":\"giatridoam\" , \"anhsang\":\"giatrianhanh\"}";
  String ChuoiSendWebJson = "";
 // ChuoiSendWebJson = "{\"nhietdo\":\"" + String(sensor1) + "\",\"doam\":\"" + String(sensor2) + "\",\"anhsang\":\"" + String(sensor3) + "\",\"relay1\":\"" + String(sensor4) + "\"}";
  ChuoiSendWebJson = "{\"nhietdo\":\"" + String(sensor1) + "\","+
                         "\"doam\":\"" + String(sensor2) + "\","+
                      "\"anhsang\":\"" + String(sensor3) + "\","+
                       "\"relay1\":\"" + String(sensor4) + "\"}";

 //Serial.print("ChuoiSendWebJson:");
  //Serial.println(ChuoiSendWebJson);
}
