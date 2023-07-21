// Wind values webpage
String Windv()
{
 // Debug info 
 DebugPrintln(3, "Send windv.html");

 // Page content with JavaScript and JSON for updating
 String content;
 content +=F( "<!DOCTYPE html>");
 content +=F( "<html>");
 content +=F( "<head>");
 content +=F( "<title>Windsensor Values</title>");
 content +=F( "<link rel='stylesheet' type='text/css' href='/css'>");
 content +=F( "<meta http-equiv='content-type' content='text/html; charset=UTF-8'>");
 content +=F( "<meta name=viewport content='width=device-width, initial-scale=1'>");

 // Special local format
 content +=F( "<style>");
 content +=F( "</style>");
 content +=F( "</head>");
 content +=F( "<body>");
 
 content +=F( "<script>");
 content +=F( "var xmlhttp = new XMLHttpRequest();");
 content +=F( "xmlhttp.onreadystatechange = function() {");
 content +=F( "if (this.readyState == 4 && this.status == 200) {");
 content +=F( "var myObj = JSON.parse(this.responseText);");

 content +=F( "var winddir = 0;");
 content +=F( "var dirunit = '  ';");
 content +=F( "winddir = myObj.Device.MeasuringValues.WindDirection.Value;");
 content +=F( "winddir = Math.round(winddir*10)/10;");
 content +=F( "dirunit = myObj.Device.MeasuringValues.WindDirection.Unit;");
 content +=F( "var dir = winddir + ' ' + dirunit;");
 content +=F( "document.getElementById('winddir').innerHTML = dir;");

 content +=F( "var windspeed = 0;");
 content +=F( "var speedunit = '  ';");
 content +=F( "windspeed = myObj.Device.MeasuringValues.WindSpeed.Value;");
 content +=F( "windspeed = Math.round(windspeed*10)/10;");
 content +=F( "speedunit = myObj.Device.MeasuringValues.WindSpeed.Unit;");
 content +=F( "var speed = windspeed + ' ' + speedunit;");
 content +=F( "document.getElementById('windspeed').innerHTML = speed;");

 if(String(actconf.tempSensorType) == "DS18B20"){
   content +=F( "var owtemp = 0;");
   content +=F( "var owunit = '  ';");
   content +=F( "owtemp = myObj.Device.MeasuringValues.DeviceTemperature.Value;");
   content +=F( "owtemp = Math.round(owtemp*10)/10;");
   content +=F( "owunit = myObj.Device.MeasuringValues.DeviceTemperature.Unit;");
   content +=F( "var tempstring = owtemp + ' ' + owunit;");
   content +=F( "document.getElementById('owtemp').innerHTML = tempstring;");
 }

 if(String(actconf.tempSensorType) == "BME280"){
   content +=F( "var airtemp = 0;");
   content +=F( "var tunit = '  ';");
   content +=F( "airtemp = myObj.Device.MeasuringValues.AirTemperature.Value;");
   content +=F( "airtemp = Math.round(airtemp*10)/10;");
   content +=F( "tunit = myObj.Device.MeasuringValues.AirTemperature.Unit;");
   content +=F( "var temp = airtemp + ' ' + tunit;");
   content +=F( "document.getElementById('airtemp').innerHTML = temp;");
  
   content +=F( "var airpressure = 0;");
   content +=F( "var aunit = '  ';");
   content +=F( "airpressure = myObj.Device.MeasuringValues.AirPressure.Value;");
   content +=F( "airpressure = Math.round(airpressure*10)/10;");
   content +=F( "aunit = myObj.Device.MeasuringValues.AirPressure.Unit;");
   content +=F( "var pressure = airpressure + ' ' + aunit;");
   content +=F( "document.getElementById('airpressure').innerHTML = pressure;");
  
   content +=F( "var airhumidity = 0;");
   content +=F( "var hunit = '  ';");
   content +=F( "airhumidity = myObj.Device.MeasuringValues.AirHumidity.Value;");
   content +=F( "airhumidity = Math.round(airhumidity*10)/10;");
   content +=F( "hunit = myObj.Device.MeasuringValues.AirHumidity.Unit;");
   content +=F( "var humidity = airhumidity + ' ' + hunit;");
   content +=F( "document.getElementById('airhumidity').innerHTML = humidity;");
  
   content +=F( "var dewpoint = 0;");
   content +=F( "var dunit = '  ';");
   content +=F( "dewpoint = myObj.Device.MeasuringValues.Dewpoint.Value;");
   content +=F( "dewpoint = Math.round(dewpoint*10)/10;");
   content +=F( "dunit = myObj.Device.MeasuringValues.Dewpoint.Unit;");
   content +=F( "var dpoint = dewpoint + ' ' + dunit;");
   content +=F( "document.getElementById('dewpoint').innerHTML = dpoint;");
  
   content +=F( "var altitude = 0;");
   content +=F( "var aunit = '  ';");
   content +=F( "altitude = myObj.Device.MeasuringValues.Altitude.Value;");
   content +=F( "altitude = Math.round(altitude*10)/10;");
   content +=F( "aunit = myObj.Device.MeasuringValues.Altitude.Unit;");
   content +=F( "var alti = altitude + ' ' + aunit;");
   content +=F( "document.getElementById('altitude').innerHTML = alti;");
 }
 
 content +=F( "document.getElementById('quality').innerHTML = myObj.Device.NetworkParameter.ConnectionQuality.Value;");

 // If Demo Mode active the give out a message
 content += F("servermode = myObj.Device.NetworkParameter.ServerMode;");
 content += F("if (servermode == 4) {");
 content += F("document.getElementById('info').innerHTML = '(Demo Mode)';");
 if(String(actconf.tempSensorType) == "BME280"){
  content += F("document.getElementById('info2').innerHTML = '(Demo Mode)';");
 }
 content += F("}");
 content += F("else {");
 content += F("document.getElementById('info').innerHTML = '';");
 content += F("}");

 content +=F( "}");
 content +=F( "};");
 content +=F( "function read_json() {");
// content +=F( "xmlhttp.open('GET', 'http://192.168.4.1/json', true);");
 content +=F( "xmlhttp.open('GET', '/json', true);");
 content +=F( "xmlhttp.send();");
 content +=F( "}");
 content +=F( "setInterval(function(){read_json(); }, 1000);");
 content +=F( " </script>");
 
 // Web page title
 content +=F( "<h2>");
 content += String(actconf.devname) + " " + String(actconf.windSensorType);
 content +=F( "</h2>");
 content += String(actconf.crights);
 content +=F( ", "); 
 content += String(actconf.fversion);
 content +=F( ", CQ: <data id = 'quality'></data>%");
 content +=F( "<hr align='left'>");
 
 content +=F( "<h3>Windsensor Values  <blink><data id='info'></data></blink></h3>");
 
 content +=F( "<FONT SIZE='4'>");
 
 content +=F( "<table>");
 
 content +=F( "<tr>");
 content +=F( "<td>");
 content +=F( "<div class='svg'>");
 content +=F( "<svg xmlns='http://www.w3.org/2000/svg' class='icon icon-tabler icon-tabler-gps' width='30' height='30' viewBox='0 0 24 24' stroke-width='1.5' stroke='#FFFFFF' fill='none' stroke-linecap='round' stroke-linejoin='round'>");
 content +=F( "<path stroke='none' d='M0 0h24v24H0z' fill='none'/>");
 content +=F( "<circle cx='12' cy='12' r='9' />");
 content +=F( "<path d='M12 17l-1 -4l-4 -1l9 -4z' />");
 content +=F( "</svg>");
 content +=F( "</div>");
 content +=F( "</td>");
 content +=F( "<td>Dir:</td>");
 content +=F( "<td><data id='winddir'></data></td>");
 content +=F( "<td><data id='dirunit'></data></td>");
 content +=F( "</tr>");

 content +=F( "<tr>");
 content +=F( "<td>");
 content +=F( "<div class='svg'>");
 content +=F( "<svg xmlns='http://www.w3.org/2000/svg' class='icon icon-tabler icon-tabler-wind' width='30' height='30' viewBox='0 0 24 24' stroke-width='1.5' stroke='#FFFFFF' fill='none' stroke-linecap='round' stroke-linejoin='round'>");
 content +=F( "<path stroke='none' d='M0 0h24v24H0z' fill='none'/>");
 content +=F( "<path d='M5 8h8.5a2.5 2.5 0 1 0 -2.34 -3.24' />");
 content +=F( "<path d='M3 12h15.5a2.5 2.5 0 1 1 -2.34 3.24' />");
 content +=F( "<path d='M4 16h5.5a2.5 2.5 0 1 1 -2.34 3.24' />");
 content +=F( "</svg>");
 content +=F( "</div>");
 content +=F( "</td>");
 content +=F( "<td>Spd:</td>");
 content +=F( "<td><data id='windspeed'></data></td>");
 content +=F( "<td><data id='speedunit'></data></td>");
 content +=F( "</tr>");

 if(String(actconf.tempSensorType) == "DS18B20"){
   content +=F( "<tr>");
   content +=F( "<td>");
   content +=F( "<div class='svg'>");
   content +=F( "<svg xmlns='http://www.w3.org/2000/svg' class='icon icon-tabler icon-tabler-temperature' width='30' height='30' viewBox='0 0 24 24' stroke-width='1.5' stroke='#FFFFFF' fill='none' stroke-linecap='round' stroke-linejoin='round'>");
   content +=F( "<path stroke='none' d='M0 0h24v24H0z' fill='none'/>");
   content +=F( "<path d='M10 13.5a4 4 0 1 0 4 0v-8.5a2 2 0 0 0 -4 0v8.5' />");
   content +=F( "<line x1='10' y1='9' x2='14' y2='9' />");
   content +=F( "</svg>");
   content +=F( "</div>");
   content +=F( "</td>");
   content +=F( "<td>Temp:</td>");
   content +=F( "<td><data id='owtemp'></data></td>");
   content +=F( "<td><data id='owunit'></data></td>");
   content +=F( "</tr>");
 }

 content +=F( "</table>");

 content +=F( "</FONT>");

 //########### Environment Values #############
 
 if(String(actconf.windSensorType) == "Ventus" && String(actconf.tempSensorType) == "BME280"){
   content +=F( "<hr align='left'>");
  
   content +=F( "<h3>Environment Values  <blink><data id='info2'></data></blink></h3>");
   
   content +=F( "<FONT SIZE='4'>");
   
   content +=F( "<table>");
   
   content +=F( "<tr>");
   content +=F( "<td>");
   content +=F( "<div class='svg'>");
   content +=F( "<svg xmlns='http://www.w3.org/2000/svg' class='icon icon-tabler icon-tabler-temperature' width='30' height='30' viewBox='0 0 24 24' stroke-width='1.5' stroke='#FFFFFF' fill='none' stroke-linecap='round' stroke-linejoin='round'>");
   content +=F( "<path stroke='none' d='M0 0h24v24H0z' fill='none'/>");
   content +=F( "<path d='M10 13.5a4 4 0 1 0 4 0v-8.5a2 2 0 0 0 -4 0v8.5' />");
   content +=F( "<line x1='10' y1='9' x2='14' y2='9' />");
   content +=F( "</svg>");
   content +=F( "</div>");
   content +=F( "</td>");
   content +=F( "<td>Temp:</td>");
   content +=F( "<td><data id='airtemp'></data></td>");
   content +=F( "<td><data id='tunit'></data></td>");
   content +=F( "</tr>");
   
   content +=F( "<tr>");
   content +=F( "<td>");
   content +=F( "<svg xmlns='http://www.w3.org/2000/svg' class='icon icon-tabler icon-tabler-gauge' width='30' height='30' viewBox='0 0 24 24' stroke-width='1.5' stroke='#FFFFFF' fill='none' stroke-linecap='round' stroke-linejoin='round'>");
   content +=F( "<path stroke='none' d='M0 0h24v24H0z' fill='none'/>");
   content +=F( "<circle cx='12' cy='12' r='9' />");
   content +=F( "<circle cx='12' cy='12' r='1' />");
   content +=F( "<line x1='13.41' y1='10.59' x2='16' y2='8' />");
   content +=F( "<path d='M7 12a5 5 0 0 1 5 -5' />");
   content +=F( "</svg>");
   content +=F( "</td>");
   content +=F( "<td>Press:</td>");
   content +=F( "<td><data id='airpressure'></data></td>");
   content +=F( "<td><data id='punit'></data></td>");
   content +=F( "</tr>");
  
   content +=F( "<tr>");
   content +=F( "<td>");
   content +=F( "<div class='svg'>");
   content +=F( "<svg xmlns='http://www.w3.org/2000/svg' class='icon icon-tabler icon-tabler-droplet' width='30' height='30' viewBox='0 0 24 24' stroke-width='1.5' stroke='#FFFFFF' fill='none' stroke-linecap='round' stroke-linejoin='round'>");
   content +=F( "<path stroke='none' d='M0 0h24v24H0z' fill='none'/>");
   content +=F( "<path d='M6.8 11a6 6 0 1 0 10.396 0l-5.197 -8l-5.2 8z' />");
   content +=F( "</svg>");
   content +=F( "</div>");
   content +=F( "</td>");
   content +=F( "<td>Hum:</td>");
   content +=F( "<td><data id='airhumidity'></data></td>");
   content +=F( "<td><data id='hunit'></data></td>");
   content +=F( "</tr>");
  
   content +=F( "<tr>");
   content +=F( "<td>");
   content +=F( "<div class='svg'>");
   content +=F( "<svg xmlns='http://www.w3.org/2000/svg' width='30' height='30' viewBox='0 0 16 16' stroke-width='1.0' stroke='#FFFFFF' fill='none' stroke-linecap='round' stroke-linejoin='round'>");
   content +=F( "<path stroke='none' d='M0 0h1v16H0z' fill='none'/>");
   content +=F( "<path d='M 11 1 C 11 1 10 2.366 10 3 C 10 3.634 10.448 4 11 4 C 11.552 4 12 3.634 12 3 C 12 2.366 11 1 11 1 z M 5.5117188 2 C 6.3389914 2 7.0117188 2.6727273 7.0117188 3.5 L 7.0117188 9.2871094 A 0.50005 0.50005 0 0 0 7.1757812 9.6582031 C 7.6819004 10.118998 8 10.766999 8 11.5 C 8 12.886833 6.886833 14 5.5 14 C 4.113167 14 3 12.886833 3 11.5 C 3 10.757148 3.3263782 10.103677 3.84375 9.6425781 A 0.50005 0.50005 0 0 0 4.0117188 9.2695312 L 4.0117188 3.5 C 4.0117188 2.6727273 4.684446 2 5.5117188 2 z M 13.5 4.625 C 13.5 4.625 12 6.62275 12 7.46875 C 12 8.31475 12.672 9 13.5 9 C 14.328 9 15 8.31475 15 7.46875 C 15 6.62275 13.5 4.625 13.5 4.625 z M 12 10 C 12 10 11 11.366 11 12 C 11 12.634 11.448 13 12 13 C 12.552 13 13 12.634 13 12 C 13 11.366 12 10 12 10 z'/>");
   content +=F( "</svg>");
   content +=F( "</div>");
   content +=F( "</td>");
   content +=F( "<td>Dew:</td>");
   content +=F( "<td><data id='dewpoint'></data></td>");
   content +=F( "<td><data id='dunit'></data></td>");
   content +=F( "</tr>");
  
   content +=F( "<tr>");
   content +=F( "<td>");
   content +=F( "<div class='svg'>"); 
   content +=F( "<svg xmlns='http://www.w3.org/2000/svg' width='30' height='30' viewBox='0 0 50 50' stroke-width='3.0' stroke='#2c3e50' fill='none' stroke-linecap='round' stroke-linejoin='round'>");
   content +=F( "<path stroke='none' d='M0 0h50v50H0z' fill='none'/>");
   content +=F( "<path d='M 26.048828 6.9199219 L 18.619141 19.75 L 16.201172 23.929688 L 14.789062 26.369141 L 13.269531 24.855469 L 11.75 23.335938 L 1.8691406 42 L 4.1328125 42 L 45.855469 42 L 48.140625 42 L 48.144531 42 L 44.099609 34.720703 L 42.080078 31.080078 L 42.078125 31.082031 L 40.107422 34.035156 L 39.90625 33.648438 L 32.859375 20.050781 L 32.857422 20.052734 L 26.048828 6.9199219 z'/>");
   content +=F( "</svg>");
   content +=F( "</div>");
   content +=F( "</td>");
   content +=F( "<td>Alt:</td>");
   content +=F( "<td><data id='altitude'></data></td>");
   content +=F( "<td><data id='aunit'></data></td>");
   content +=F( "</tr>");
  
   content +=F( "</table>");
 }  

 content +=F( "</FONT>");

 content +=F( "<hr align='left'>");
 content +=F( "<br>");
 content +=F( "<form action='/'><button type='submit'>Back</button></form>");
 content +=F( "</body>");
 content +=F( "</html>");

 return content;
}
