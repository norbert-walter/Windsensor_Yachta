// Start webpage
String Startpage(int num, String vname[20], String value[20])
{
 // Print all received get arguments
 for(int i = 0; i < num; i++)
  {
   String out = vname[i] + " : " + value[i];
    DebugPrintln(3, out);
  }

 // Style the display between day and night illumination
 for(int i = 0; i < num; i++)
  {
   if(vname[i] == "style"){
     style = toInteger(value[i]) + 1;
     style %= 3;    // Modulo function, style 0,1,2
   }
  } 

 // Debug info 
 DebugPrintln(3, "Send main.html"); 

 // Page content
 String content;
 content +=F( "<!DOCTYPE html>");
 content +=F( "<html>");
 content +=F( "<head>");
 content +=F( "<title>Windsensor</title>");
 content +=F( "<link rel='stylesheet' type='text/css' href='/css'>");
 content +=F( "<meta http-equiv='content-type' content='text/html; charset=UTF-8'>");
 content +=F( "<meta name=viewport content='width=device-width, initial-scale=1'>");
 
 content +=F( "<style>");
 // Table special definitions
 content +=F( "table,th, td {");
 content +=F( "padding: 10px;");
 content +=F( "}");
 content +=F( "button {height: 55px; width: 120px;}");
 content +=F( "</style>");
 
 content +=F( "</head>");
 content +=F( " <body onload='read_json()'> ");

 //#######################################################
 content +=F( "<script>");
 content +=F( "var xmlhttp = new XMLHttpRequest();");
 content +=F( "xmlhttp.onreadystatechange = function() {");
 content +=F( "if (this.readyState == 4 && this.status == 200) {");
 content +=F( "var myObj = JSON.parse(this.responseText);");

 // If Debug Mode active the give out a message
 content += F("servermode = myObj.Device.NetworkParameter.ServerMode;");
 content += F("if (servermode == 3) {");
 content += F("document.getElementById('info').innerHTML = '(Diagnostic Mode)';");
 content += F("document.getElementById('windi').disabled=true;");
 content += F("document.getElementById('firmware').disabled=true;");
 content += F("document.getElementById('windv').disabled=true;");
 content += F("document.getElementById('restart').disabled=true;");
 content += F("document.getElementById('devinfo').disabled=true;");
 content += F("document.getElementById('style').disabled=true;");
 content += F("}");
 content += F("else {");
 content += F("document.getElementById('windi').disabled=false;");
 content += F("document.getElementById('firmware').disabled=false;");
 content += F("document.getElementById('windv').disabled=false;");
 content += F("document.getElementById('restart').disabled=false;");
 content += F("document.getElementById('devinfo').disabled=false;");
 content += F("document.getElementById('style').disabled=false;");
 content += F("}");

 content +=F( "}");
 content +=F( "};");
 content +=F( "function read_json() {");
// content +=F( "xmlhttp.open('GET', 'http://192.168.4.1/json', true);");
 content +=F( "xmlhttp.open('GET', '/json', true);");
 content +=F( "xmlhttp.send();");
 content +=F( "}");
 content +=F( " </script>");
 //#######################################################
 
 // Web page title
 content +=F( "<h2>");
 content += String(actconf.devname) + " " + String(actconf.windSensorType);
 content +=F( "</h2>");
 content += String(actconf.crights);
 content +=F( ", "); 
 content += String(actconf.fversion);
 content +=F( ", CQ: ");
 content += String(int(quality));
 content +=F( "%"); 
 content +=F( "<hr align='left'>");
 content +=F( "<h3><blink><data id='info'></data></blink></h3>");

 content +=F( "<table>");
 
 content +=F( "<tr>");
 content +=F( "<td><form action='windi'><button type='submit' id='windi'>Wind Instrument</button></form></td>");
 content +=F( "<td><form action='firmware'><button type='submit' id='firmware'>Firmware Update</button></form></td>");
 content +=F( "<td></td>");
 content +=F( "</tr>");

 content +=F( "<tr>");
 content +=F( "<td><form action='windv'><button type='submit' id='windv'>Wind Values</button></form></td>");
 content +=F( "<td><form action='restart'><button type='submit' id='restart'>Restart Device</button></form></td>");
 content +=F( "<td></td>");
 content +=F( "</tr>");

 content +=F( "<tr>");
 content +=F( "<td><form action='devinfo'><button type='submit' id='devinfo'>Device Info</button></form></td>");
 content +=F( "<td>");
 content +=F( "<form action='/'><input type='hidden' name='style' value='");
 content += style;
 content +=F( "'><button type='submit' id='style'>Style</button></form>");
 content +=F( "</td>");
 content +=F( "<td></td>");
 content +=F( "</tr>");
 
 content +=F( "<tr>");
 content +=F( "<td><form action='settings'><button type='submit' id='settings'>Device Settings</button></form></td>");
 content +=F( "<td><form action='https://norbertwalter67.gitlab.io/plain-html/index_");
 content += String(actconf.fversion);
 content +=F( ".html'><button type='submit'  id='help'>System Help</button></form></td>");
 content +=F( "<td></td>");
 content +=F( "</tr>");

 content +=F( "</table>");

 content +=F( "<br>");
 content +=F( "<hr align='left'>");
 content +=F( "</body>");
 content +=F( "</html>");
 
 return content;
}
