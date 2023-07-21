// Device information webpage
String Devinfo()
{
 // Debug info
 DebugPrintln(3, "Send info.html");

 // Page content with auto reload
 String content;
 content +=F( "<!DOCTYPE html>");
 content +=F( "<html>");
 content +=F( "<head>");
 content +=F( "<title>Info Windsensor</title>");
 content +=F( "<link rel='stylesheet' type='text/css' href='/css'>");
 content +=F( "<meta http-equiv='content-type' content='text/html; charset=UTF-8'>");
 content +=F( "<meta name=viewport content='width=device-width, initial-scale=1'>");
 content +=F( "<style>");
// content += CSS();
 content +=F( "</style>");
 content +=F( "</head>");
 content +=F( "<body>");
 content +=F( "<script src='/js' type='text/javascript'></script>");
 
 // Web page title
 content +=F( "<h2>");
 content += String(actconf.devname) + " " + String(actconf.windSensorType);
 content +=F( "</h2>");
 content += String(actconf.crights);
 content +=F( ", "); 
 content += String(actconf.fversion);
 content +=F( ", CQ: <data id = 'quality2'></data>%");
 content +=F( "<hr align='left'>");
 
 content +=F( "<table>");

 content +=F( "<tr>");
 content +=F( "<td><h3>Firmware Information</h3></td>");
 content +=F( "<td></td>");
 content +=F( "<td></td>");
 content +=F( "</tr>");
 
 content +=F( "<tr>");
 content +=F( "<td>Firmware Version</td>");
 content +=F( "<td><input type='text' name='fwv' size='15' value='");
 content += String(actconf.fversion);
 content +=F( "'></td>");
 content +=F( "<td></td>");
 content +=F( "</tr>");

 content +=F( "<tr>");
 content +=F( "<td>License Type</td>");
 content +=F( "<td><input type='text' name='lic' size='15' value='");
 content += String(actconf.license);
 content +=F( "'></td>");
 content +=F( "<td></td>");
 content +=F( "</tr>");
 
 content +=F( "<tr>");
 content +=F( "<td><h3>ESP8266 Informations</h3></td>");
 content +=F( "<td></td>");
 content +=F( "<td></td>");
 content +=F( "</tr>");
 
 content +=F( "<tr>");
 content +=F( "<td>SDK Version</td>");
 content +=F( "<td><input type='text' name='sdk' size='15' value='");
 content += String(ESP.getSdkVersion());
 content +=F( "'></td>");
 content +=F( "<td></td>");
 content +=F( "</tr>");

 content +=F( "<tr>");
 content +=F( "<td>ESP8266 Chip ID</td>");
 content +=F( "<td><input type='text' name='cid' size='15' value='");
 content += String(ESP.getChipId());
 content +=F( "'></td>");
 content +=F( "<td></td>");
 content +=F( "</tr>");

 content +=F( "<tr>");
 content +=F( "<td>ESP8266 Speed</td>");
 content +=F( "<td><input type='text' name='spd' size='15' value='");
 content += String(ESP.getCpuFreqMHz());
 content +=F( "'></td>");
 content +=F( "<td>[MHz]</td>");
 content +=F( "</tr>");

 // String(ESP.getFreeHeap());
 content +=F( "<tr>");
 content +=F( "<td>Free Heap Size</td>");
 content +=F( "<td><input id='heapsize' type='text' name='heapsize' size='15' value='0'></td>");
 content +=F( "<td>[<data id='hunit'></data>]</td>");
 content +=F( "</tr>");

 content +=F( "<tr>");
 content +=F( "<td><h3>Network Parameter</h3></td>");
 content +=F( "<td></td>");
 content +=F( "<td></td>");
 content +=F( "</tr>");
 
 content +=F( "<tr>");
 content +=F( "<td>Hostname</td>");
 content +=F( "<td><input id='hostname' type='text' name='hostname' size='15' value='");
 content += String(hname);
 content +=F( "'></td>");
 content +=F( "<td></td>");
 content +=F( "</tr>");

 content +=F( "<tr>");
 content +=F( "<td>mDNS Name</td>");
 content +=F( "<td><input id='mdnsname' type='text' name='mdnsname' size='15' value='");
 if(actconf.mDNS == 1){
  content += String(hname) + ".local";
 }
 else{
  content +=F( "not activ");
 }
 content +=F( "'></td>");
 content +=F( "<td></td>");
 content +=F( "</tr>");
 
 content +=F( "<tr>");
 content +=F( "<td>WLAN Server SSID</td>");
 content +=F( "<td><input id='sssid' type='text' name='sssid' size='15' value=' '></td>");
 content +=F( "<td></td>");
 content +=F( "</tr>");

 content +=F( "<tr>");
 content +=F( "<td>WLAN Server IP</td>");
 content +=F( "<td><input type='text' name='serverip' size='15' value='");
 content += WiFi.softAPIP().toString();
 content +=F( "'></td>");
 content +=F( "<td></td>");
 content +=F( "</tr>");

 content +=F( "<tr>");
 content +=F( "<td>Activ AP Channel</td>");
 content +=F( "<td><input type='text' name='apchannel' size='15' value='");
 content += String(WiFi.channel());
 content +=F( "'></td>");
 content +=F( "<td></td>");
 content +=F( "</tr>");

 content +=F( "<tr>");
 content +=F( "<td>WLAN Client SSID</td>");
 content +=F( "<td><input id='cssid' type='text' name='cssid' size='15' value=' '></td>");
 content +=F( "<td></td>");
 content +=F( "</tr>");

 content +=F( "<tr>");
 content +=F( "<td>WLAN Client IP</td>");
 content +=F( "<td><input type='text' name='clientip' size='15' value='");
 content += WiFi.localIP().toString();
 content +=F( "'></td>");
 content +=F( "<td></td>");
 content +=F( "</tr>");

 content +=F( "<tr>");
 content +=F( "<td>Client Field Strength</td>");
 content +=F( "<td><input id='strength' type='text' name='strength' size='15' value='0'></td>");
 content +=F( "<td>[<data id='sunit'></data>]</td>");
 content +=F( "</tr>");
 
 content +=F( "<tr>");
 content +=F( "<td>Connection Quality</td>");
 content +=F( "<td><input id='quality' type='text' name='quality' size='15' value='0'></td>");
 content +=F( "<td>[<data id='qunit'></data>]</td>");
 content +=F( "</tr>");
 
 content +=F( "<tr>");
 content +=F( "<td><h3>Device Informations<br><blink><data id='info'></data></blink></h3></td>");
 content +=F( "<td></td>");
 content +=F( "<td></td>");
 content +=F( "</tr>");
 
 if(String(actconf.tempSensorType) == "DS18B20"){
   content +=F( "<tr>");
   content +=F( "<td>Device Temperature</td>");
   content +=F( "<td><input id='temp' type='text' name='wstemp' size='15' value='0'></td>");
   content +=F( "<td>[<data id='tunit'></data>]</td>");
   content +=F( "</tr>");
 }

 content +=F( "<tr>");
 content +=F( "<td>Wind Direction</td>");
 content +=F( "<td><input id='winddir' type='text' name='wdir' size='15' value='0'></td>");
 content +=F( "<td>[<data id='dirunit'></data>]</td>");
 content +=F( "</tr>");

 content +=F( "<tr>");
 content +=F( "<td>Resolution Wind Direction</td>");
 content +=F( "<td><input id='resolution' type='text' name='wdirres' size='15' value='0'></td>");
 content +=F( "<td>[<data id='resunit'></data>]</td>");
 content +=F( "</tr>");

 content +=F( "<tr>");
 content +=F( "<td>Wind Speed</td>");
 content +=F( "<td><input id='windspeed' type='text' name='wspeed' size='15' value='0'></td>");
 content +=F( "<td>[<data id='speedunit'></data>]</td>");
 content +=F( "</tr>");

 content +=F( "<tr>");
 content +=F( "<td>Down Wind Speed</td>");
 content +=F( "<td><input id='dwspeed' type='text' name='dwspeed' size='15' value='0'></td>");
 content +=F( "<td>[<data id='dwunit'></data>]</td>");
 content +=F( "</tr>");

 content +=F( "<tr>");
 content +=F( "<td>Sensor 1 (Speed)</td>");
 content +=F( "<td><input id='sensor1' type='text' name='wsensor1' size='15' value='0'></td>");
 content +=F( "<td>[<data id='s1unit'></data>]</td>");
 content +=F( "</tr>");

 if(String(actconf.windSensorType) == "WiFi 1000"){
   content +=F( "<tr>");
   content +=F( "<td>Sensor 2 (Direction)</td>");
   content +=F( "<td><input id='sensor2' type='text' name='wsensor2' size='15' value='0'></td>");
   content +=F( "<td>[<data id='s2unit'></data>]</td>");
   content +=F( "</tr>");

   content +=F( "<tr>");
   content +=F( "<td>Pulse Counter</td>");
   content +=F( "<td><input id='pcounter' type='text' name='pcounter' size='15' value='0'></td>");
   content +=F( "<td>[<data id='pcunit'></data>]</td>");
   content +=F( "</tr>");
  
   content +=F( "<tr>");
   content +=F( "<td>Time 1 (Speed)</td>");
   content +=F( "<td><input id='time1' type='text' name='wtime1' size='15' value='0'></td>");
   content +=F( "<td>[<data id='t1unit'></data>]</td>");
   content +=F( "</tr>");
  
   content +=F( "<tr>");
   content +=F( "<td>Time 2 (Direction)</td>");
   content +=F( "<td><input id='time2' type='text' name='wtime2' size='15' value='0'></td>");
   content +=F( "<td>[<data id='t2unit'></data>]</td>");
   content +=F( "</tr>");
 }

 if(String(actconf.windSensorType) == "Yachta" || String(actconf.windSensorType) == "Jukolein" || String(actconf.windSensorType) == "Ventus"){
   content +=F( "<tr>");
   content +=F( "<td>Magn. Flux Density</td>");
   content +=F( "<td><input id='magnitude' type='text' name='magnitude' size='15' value='0'></td>");
   content +=F( "<td>[<data id='magnitudeunit'></data>]</td>");
   content +=F( "</tr>");
   
   content +=F( "<tr>");
   content +=F( "<td>Magn. Sensor (Direction)</td>");
   content +=F( "<td><input id='magsensor' type='text' name='magsensor' size='15' value='0'></td>");
   content +=F( "<td>[<data id='magunit'></data>]</td>");
   content +=F( "</tr>");
 }
  
 content +=F( "<tr>");
 content +=F( "<td>Rotation Speed</td>");
 content +=F( "<td><input id='rotspeed' type='text' name='wrotspeed' size='15' value='0'></td>");
 content +=F( "<td>[<data id='rotunit'></data>]</td>");
 content +=F( "</tr>");

 if(String(actconf.windSensorType) == "Ventus" && String(actconf.tempSensorType) == "BME280"){
   content +=F( "<tr>");
   content +=F( "<td><h3>BME280 Informations<br><blink><data id='info2'></data></blink></h3></td>");
   content +=F( "<td></td>");
   content +=F( "<td></td>");
   content +=F( "</tr>");
   
   content +=F( "<tr>");
   content +=F( "<td>Air Temperature</td>");
   content +=F( "<td><input id='atemp' type='text' name='atemp' size='15' value='0'></td>");
   content +=F( "<td>[<data id='aunit'></data>]</td>");
   content +=F( "</tr>");
  
   content +=F( "<tr>");
   content +=F( "<td>Air Pressure</td>");
   content +=F( "<td><input id='pres' type='text' name='pres' size='15' value='0'></td>");
   content +=F( "<td>[<data id='punit'></data>]</td>");
   content +=F( "</tr>");
  
   content +=F( "<tr>");
   content +=F( "<td>Air Humidity</td>");
   content +=F( "<td><input id='hum' type='text' name='hum' size='15' value='0'></td>");
   content +=F( "<td>[<data id='humunit'></data>]</td>");
   content +=F( "</tr>");
 }
 
 content +=F( "</table>");

 content +=F( "<br>");
 content +=F( "<hr align='left'>");
 content +=F( "<br>");
 content +=F( "<form action='/'><button type='submit'>Back</button></form>");
 content +=F( "<br>");
 content +=F( "<br>");
 content +=F( "</body>");
 content +=F( "</html>");

 return content;
}
