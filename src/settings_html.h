// Settings webpage
String Settings(int num, String vname[30], String value[30])
{ 
  String hash = "";
  
  // Print all received get arguments
  for (int i = 0; i < num; i++)
  {
    String out = vname[i] + " : " + value[i];
     DebugPrintln(3, out);
  }

  // Check new settings and save it in configuration
  for (int i = 0; i < num; i++)
  {
    if(vname[i] == "password"){
      hash = value[i];
    }
    if (vname[i] == "usepassword") {
      actconf.crypt = toInteger(value[i]);
    }
    if (vname[i] == "pagepasswd") {
      value[i].toCharArray(actconf.password, 31);
    }
    if (vname[i] == "itype") {
      value[i].toCharArray(actconf.instrumentType, 8);
    }
    if (vname[i] == "isize") {
      actconf.instrumentSize = toInteger(value[i]);
    }
    if (vname[i] == "cssid") {
      value[i].toCharArray(actconf.cssid, 31);
    }
    if (vname[i] == "cpasswd") {
      value[i].toCharArray(actconf.cpassword, 31);
    }
    if (vname[i] == "timeout") {
      actconf.timeout = toInteger(value[i]);
    }
    if (vname[i] == "sssid") {
      value[i].toCharArray(actconf.sssid, 31);
    }
    if (vname[i] == "spasswd") {
      value[i].toCharArray(actconf.spassword, 31);
    }
     if (vname[i] == "apchannel") {
      actconf.apchannel = toInteger(value[i]);
    }
    if (vname[i] == "servermode") {
      actconf.serverMode = toInteger(value[i]);
    }
    if (vname[i] == "mdnsservice") {
      actconf.mDNS = toInteger(value[i]);
    }
    if (vname[i] == "debugmode") {
      actconf.debug = toInteger(value[i]);
    }
    if (vname[i] == "serspeed") {
      actconf.serspeed = toInteger(value[i]);
    }
    if (vname[i] == "sensorid") {
      actconf.sensorID = toInteger(value[i]);
    }
    if (vname[i] == "wstype") {
      value[i].toCharArray(actconf.windSensorType, 15);
    }
    if (vname[i] == "sendwsdata") {
      actconf.windSensor = toInteger(value[i]);
    }
    if (vname[i] == "windtype") {
      value[i].toCharArray(actconf.windType, 2);
    }
    if (vname[i] == "offset") {
      if (toInteger(value[i]) >= -180 && toInteger(value[i]) <= 180){
        actconf.offset = toInteger(value[i]);
      }
      if (toInteger(value[i]) < -180){
        actconf.offset = -180;
      }
      if (toInteger(value[i]) > 180){
        actconf.offset = 180;
      }  
    }
    if (vname[i] == "average") {
      actconf.average = toInteger(value[i]);
    }
    if (vname[i] == "speedunit") {
      value[i].toCharArray(actconf.speedUnit, 5);
    }
    if (vname[i] == "dwsensor") {
      actconf.downWindSensor = toInteger(value[i]);
    }
    if (vname[i] == "dwrange") {
      actconf.downWindRange = toInteger(value[i]);
    }
    if (vname[i] == "tstype") {
      value[i].toCharArray(actconf.tempSensorType, 10);
    }
     if (vname[i] == "sendtsd") {
      actconf.tempSensor = toInteger(value[i]);
    }
    if (vname[i] == "tempunit") {
      value[i].toCharArray(actconf.tempUnit, 2);
    }
    if (vname[i] == "cslope") {
      actconf.calslope = toFloat(value[i]);
    }
    if (vname[i] == "coffset") {
      actconf.caloffset = toFloat(value[i]);
    }
  }

  // Save the settings if the number of return values is greater 0
  if(num > 0) {
    saveEEPROMConfig(actconf);      // Save the new settings in EEPROM
    DebugPrintln(3, "New settings saved");
  }

  // Debug info
  DebugPrintln(3, "Send settings.html");

  // Check page password
 if(actconf.crypt == 1 && (hash.length() == 0 || hash != cryptPassword(String(actconf.password)))){
   // Generate a new transaction ID
   transID();
   
   // Page content for password input
   String content;
   content +=F( "<!DOCTYPE html>");
   content +=F( "<html>");
   content +=F( "<head>");
   content +=F( "<title>Settings Windsensor</title>");
   content +=F( "<link rel='stylesheet' type='text/css' href='/css'>");
   content +=F( "<meta http-equiv='content-type' content='text/html; charset=UTF-8'>");
   content +=F( "<meta name=viewport content='width=device-width, initial-scale=1'>");
   content +=F( "<script src='MD5.js' type='text/javascript'></script>");
   content +=F( " <style>");
  // content += CSS();
   content +=F( "</style>");
   content +=F( "</head>");
   content +=F( "<body>");
   
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
   
   content +=F( "<h3>Password Required</h3>");
   content +=F( "<form id='pwdForm' action='settings' method='get'><input size=30 type='text' name='password' id='password' onkeypress='return event.keyCode != 13;'><br/><br/><button TYPE='button' onClick='proc()'>Send</button></form>");
   content +=F( "<br>");
   content +=F( "<hr align='left'>");
   content +=F( "<br>");
   content +=F( "<form id='pwdForm2' action='/' method='get'><button type='button' onClick='document.getElementById(\"pwdForm2\").submit();'>Back</button></form>");
   content +=F( "</body>");
   content +=F( "</html>");
  
   return content;
 }
 else{
   // Generate a new transaction ID
   transID();

    // Page content
    String content;
    content += F("<!DOCTYPE html>");
    content += F("<html>");
    content += F("<head>");
    content += F("<title>Settings Windsensor</title>");
    content += F("<link rel='stylesheet' type='text/css' href='/css'>");
    content += F("<meta http-equiv='content-type' content='text/html; charset=UTF-8'>");
    content += F("<meta name=viewport content='width=device-width, initial-scale=1'>");
    content += F("<style type='text/css'>");
    content += F("select {width:150px;}");
    content += F("input {width:145px;}");
    // content += CSS();
    content += F("</style>");
    content += F("<script>");
    content += F("function setSelections() {");
  
    content += F("document.SetForm.usepassword.selectedIndex = ");
    content += getindex(usepassword, String(actconf.crypt));
    content += F(";");
    
    content += F("document.SetForm.itype.selectedIndex = ");
    content += getindex(itype, String(actconf.instrumentType));
    content += F(";");
    content += F("document.SetForm.isize.selectedIndex = ");
    content += getindex(isize, String(actconf.instrumentSize));
    content += F(";");
  
    content += F("document.SetForm.timeout.selectedIndex = ");
    content += getindex(timeout, String(actconf.timeout));
    content += F(";");
    
    content += F("document.SetForm.apchannel.selectedIndex = ");
    content += getindex(apchannel, String(actconf.apchannel));
    content += F(";");
    content += F("document.SetForm.servermode.selectedIndex = ");
    content += getindex(servermode, String(actconf.serverMode));
    content += F(";");
    content += F("document.SetForm.mdnsservice.selectedIndex = ");
    content += getindex(mdnsservice, String(actconf.mDNS));
    content += F(";");
    content += F("document.SetForm.debugmode.selectedIndex = ");
    content += getindex(debugmode, String(actconf.debug));
    content += F(";");
    content += F("document.SetForm.serspeed.selectedIndex = ");
    content += getindex(serspeed, String(actconf.serspeed));
    content += F(";");
    content += F("document.SetForm.sensorid.selectedIndex = ");
    content += getindex(sensorid, String(actconf.sensorID));
    content += F(";");
    content += F("document.SetForm.wstype.selectedIndex = ");
    content += getindex(wstype, String(actconf.windSensorType));
    content += F(";");   
    content += F("document.SetForm.sendwsdata.selectedIndex = ");
    content += getindex(sendwsdata, String(actconf.windSensor));
    content += F(";");
    content += F("document.SetForm.windtype.selectedIndex = ");
    content += getindex(windtype, String(actconf.windType));
    content += F(";");
    content += F("document.SetForm.average.selectedIndex = ");
    content += getindex(averages, String(actconf.average));
    content += F(";");
    content += F("document.SetForm.speedunit.selectedIndex = ");
    content += getindex(speedunits, String(actconf.speedUnit));
    content += F(";");
    content += F("document.SetForm.dwsensor.selectedIndex = ");
    content += getindex(dwsensor, String(actconf.downWindSensor));
    content += F(";");
    content += F("document.SetForm.dwrange.selectedIndex = ");
    content += getindex(dwrange, String(actconf.downWindRange));
    content += F(";");
    content += F("document.SetForm.tstype.selectedIndex = ");
    content += getindex(tstype, String(actconf.tempSensorType));
    content += F(";"); 
    content += F("document.SetForm.sendtsd.selectedIndex = ");
    content += getindex(sendtsd, String(actconf.tempSensor));
    content += F(";");  
    content += F("document.SetForm.tempunit.selectedIndex = ");
    content += getindex(tempunits, String(actconf.tempUnit));
    content += F(";");   
    content += F("}");
  
    content += F("function check_ssid(iname) {");
    content += F("var valuestring = \"\";");
    content += F("if(iname == \"cssid\"){valuestring = document.SetForm.cssid.value;}");
    content += F("if(iname == \"sssid\"){valuestring = document.SetForm.sssid.value;}");
    content += F("var reguexp = /[^\x20-\x7E]/;");
    content += F("if(reguexp.exec(valuestring) || valuestring.length < 1 || valuestring.length > 30)");
    content += F("{");
    content += F("document.getElementById('sub').disabled = true;");   
    content += F("alert('Error!\\nUse only printable ASCII characters\\nSSID Length 1-30');");
    content += F("}");
    content += F("else{");
    content += F("document.getElementById('sub').disabled = false;");
    content += F("}");
    content += F("}");
  
    content += F("function check_passwd(iname) {");
    content += F("var valuestring = \"\";");
    content += F("if(iname == \"pagepasswd\"){valuestring = document.SetForm.sidepasswd.value;}");
    content += F("if(iname == \"cpasswd\"){valuestring = document.SetForm.cpasswd.value;}");
    content += F("if(iname == \"spasswd\"){valuestring = document.SetForm.spasswd.value;}");
    content += F("var reguexp = /[^\x20-\x7E]/;");
    content += F("if(reguexp.exec(valuestring) || valuestring.length < 8 || valuestring.length > 30)");
    content += F("{");
    content += F("document.getElementById('sub').disabled = true;");    
    content += F("alert('Error!\\nUse only printable ASCII characters\\nPassword Length 8-30');");
    content += F("}");
    content += F("else{");
    content += F("document.getElementById('sub').disabled = false;");
    content += F("}");
    content += F("}");
      
    content += F("</script>");
    content += F("</head>");
    content += F("<body onload='setSelections();'>");
    
    // Web page title
    content += F("<h2>");
    content += String(actconf.devname) + " " + String(actconf.windSensorType);
    content += F("</h2>");
    content += String(actconf.crights);
    content += F(", "); 
    content += String(actconf.fversion);
    content += F(", CQ: ");
    content += String(int(quality));
    content += F("%"); 
    content += F("<hr align='left'>");
  
    content += F("<form id='form1' name='SetForm' method='get' action='settings'>");
    content += F("<table>");
  
    content += F("<tr>");
    content += F("<td><h3>Password Settings</h3></td>");
    content += F("<td></td>");
    content += F("<td></td>");
    content += F("</tr>");
  
    content += F("<tr>");
    content += F("<td>Use Page Password</td>");
    content += F("<td>");
    content += F("<select name='usepassword' size='1'>");
    content += F("<option value='0'>Off</option>");
    content += F("<option value='1'>On</option>");
    content += F("</select>");
    content += F("</td>");
    content += F("<td></td>");
    content += F("</tr>");
  
    content += F("<tr>");
    content += F("<td>Page Password</td>");
    content += F("<td><input type='text' required name='pagepasswd' size='20' value='");
    content += String(actconf.password);  
    content += F("' maxlength='30' onchange='check_passwd(\"pagepasswd\")'></td>");
    content += F("<td></td>");
    content += F("</tr>");
    
    content += F("<tr>");
    content += F("<td><h3>Display Settings</h3></td>");
    content += F("<td></td>");
    content += F("<td></td>");
    content += F("</tr>");
  
    content += F("<tr>");
    content += F("<td>Instrument Type</td>");
    content += F("<td>");
    content += F("<select name='itype' size='1'>");
    content += F("<option value='simple'>simple</option>");
    content += F("<option value='complex'>complex</option>");
    content += F("</select>");
    content += F("</td>");
    content += F("<td></td>");
    content += F("</tr>");
  
    content += F("<tr>");
    content += F("<td>Instrument Size</td>");
    content += F("<td>");
    content += F("<select name='isize' size='1'>");
    content += F("<option value='200'>200x200 pix</option>");
    content += F("<option value='250'>250x250 pix</option>");
    content += F("<option value='300'>300x300 pix</option>");
    content += F("<option value='350'>350x350 pix</option>");
    content += F("<option value='400'>400x400 pix</option>");
    content += F("<option value='450'>450x450 pix</option>");
    content += F("<option value='500'>500x500 pix</option>");
    content += F("<option value='550'>550x550 pix</option>");
    content += F("<option value='600'>600x600 pix</option>");
    content += F("</select>");
    content += F("</td>");
    content += F("<td></td>");
    content += F("</tr>");
  
    content += F("<tr>");
    content += F("<td><h3>Network Settings</h3></td>");
    content += F("<td></td>");
    content += F("<td></td>");
    content += F("</tr>");
  
    content += F("<tr>");
    content += F("<td>WLAN Client SSID</td>");
    content += F("<td><input type='text' required name='cssid' size='20' value='");
    content += String(actconf.cssid);
    content += F("' maxlength='30' onchange='check_ssid(\"cssid\")'></td>");
    content += F("<td></td>");
    content += F("</tr>");
  
    content += F("<tr>");
    content += F("<td>WLAN Client Password</td>");
    content += F("<td><input type='text' required name='cpasswd' size='20' value='");
    content += String(actconf.cpassword);
    content += F("' maxlength='30' onchange='check_passwd(\"cpasswd\")'></td>");
    content += F("<td></td>");
    content += F("</tr>");
  
    content += F("<tr>");
    content += F("<td>Connection Timeout</td>");
    content += F("<td>");
    content += F("<select name='timeout' size='1'>");
    content += F("<option value='30'>30s</option>");
    content += F("<option value='60'>1 min</option>");
    content += F("<option value='90'>1.5 min</option>");
    content += F("<option value='120'>2 min</option>");
    content += F("<option value='150'>2.5 min</option>");
    content += F("<option value='180'>3 min</option>");
    content += F("<option value='210'>3.5 min</option>");
    content += F("<option value='240'>4 min</option>");
    content += F("<option value='270'>4.5 min</option>");
    content += F("<option value='300'>5 min</option>");
    content += F("</select>");
    content += F("</td>");
    content += F("<td></td>");
    content += F("</tr>");
  
    content += F("<tr>");
    content += F("<td>WLAN Server SSID</td>");
    content += F("<td><input type='text' required name='sssid' size='20' value='");
    content += String(actconf.sssid);
    content += F("' maxlength='30' onchange='check_ssid(\"sssid\")'></td>");
    content += F("<td></td>");
    content += F("</tr>");
  
    content += F("<tr>");
    content += F("<td>WLAN Server Password</td>");
    content += F("<td><input type='text' required name='spasswd' size='20' value='");
    content += String(actconf.spassword);  
    content += F("' maxlength='30' onchange='check_passwd(\"spasswd\")'></td>");
    content += F("<td></td>");
    content += F("</tr>");

    content += F("<tr>");
    content += F("<td>AP Channel</td>");
    content += F("<td>");
    content += F("<select name='apchannel' size='1'>");
    content += F("<option value='1'>1</option>");
    content += F("<option value='2'>2</option>");
    content += F("<option value='3'>3</option>");
    content += F("<option value='4'>4</option>");
    content += F("<option value='5'>5</option>");
    content += F("<option value='6'>6</option>");
    content += F("<option value='7'>7</option>");
    content += F("<option value='8'>8</option>");
    content += F("<option value='9'>9</option>");
    content += F("<option value='10'>10</option>");
    content += F("<option value='11'>11</option>");
    content += F("<option value='12'>12</option>");
    content += F("<option value='13'>13</option>");
    content += F("</select>");
    content += F("</td>");
    content += F("<td></td>");
    content += F("</tr>");
  
    content += F("<tr>");
    content += F("<td>Server Mode</td>");
    content += F("<td>");
    content += F("<select name='servermode' size='1'>");
    content += F("<option value='0'>HTTP (JSON, NMEA)</option>");
    content += F("<option value='1'>NMEA Serial</option>");
    content += F("<option value='2'>MQTT</option>");
    content += F("<option value='3'>Diagnostic</option>");
    content += F("<option value='4'>Demo Mode</option>");
    content += F("</select>");
    content += F("</td>");
    content += F("<td></td>");
    content += F("</tr>");

    content += F("<tr>");
    content += F("<td>mDNS Service</td>");
    content += F("<td>");
    content += F("<select name='mdnsservice' size='1'>");
    content += F("<option value='0'>Off</option>");
    content += F("<option value='1'>On</option>");
    content += F("</select>");
    content += F("</td>");
    content += F("<td></td>");
    content += F("</tr>");
  
    content += F("<tr>");
    content += F("<td><h3>Device Settings</h3></td>");
    content += F("<td></td>");
    content += F("<td></td>");
    content += F("</tr>");
  
    content += F("<tr>");
    content += F("<td>Serial Debug Mode</td>");
    content += F("<td>");
    content += F("<select name='debugmode' size='1'>");
    content += F("<option value='0'>Off</option>");
    content += F("<option value='1'>Errors</option>");
    content += F("<option value='2'>Errors + Warnings</option>");
    content += F("<option value='3'>Errors + Warnings + Messages</option>");
    content += F("</select>");
    content += F("</td>");
    content += F("<td></td>");
    content += F("</tr>");
  
    content += F("<tr>");
    content += F("<td>Serial Speed</td>");
    content += F("<td>");
    content += F("<select name='serspeed' size='1'>");
    content += F("<option value='300'>300 Bd</option>");
    content += F("<option value='1200'>1200 Bd</option>");
    content += F("<option value='2400'>2400 Bd</option>");
    content += F("<option value='4800'>4800 Bd</option>");
    content += F("<option value='9600'>9600 Bd</option>");
    content += F("<option value='19200'>19200 Bd</option>");
    content += F("<option value='38400'>38400 Bd</option>");
    content += F("<option value='57600'>57600 Bd</option>");
    content += F("<option value='74880'>74880 Bd</option>");
    content += F("<option value='115200'>115200 Bd</option>");
    content += F("</select>");
    content += F("</td>");
    content += F("<td></td>");
    content += F("</tr>");
  
    content += F("<tr>");
    content += F("<td>Sensor ID</td>");
    content += F("<td>");
    content += F("<select name='sensorid' size='1'>");
    content += F("<option value='0'>0</option>");
    content += F("<option value='1'>1</option>");
    content += F("<option value='2'>2</option>");
    content += F("<option value='3'>3</option>");
    content += F("<option value='4'>4</option>");
    content += F("<option value='5'>5</option>");
    content += F("<option value='6'>6</option>");
    content += F("<option value='7'>7</option>");
    content += F("<option value='8'>8</option>");
    content += F("<option value='9'>9</option>");
    content += F("</select>");
    content += F("</td>");
    content += F("<td></td>");
    content += F("</tr>");
  
    content += F("<tr>");
    content += F("<td>Wind Sensor Type</td>");
    content += F("<td>");
    content += F("<select name='wstype' size='1'>");
    content += F("<option value='WiFi 1000'>WiFi 1000</option>");
    content += F("<option value='Yachta'>Yachta</option>");
    content += F("<option value='Yachta 2.0'>Yachta 2.0</option>");
    content += F("<option value='Jukolein'>Jukolein</option>");
    content += F("<option value='Ventus'>Ventus</option>");
    content += F("</select>");
    content += F("</td>");
    content += F("<td></td>");
    content += F("</tr>");
  
    content += F("<tr>");
    content += F("<td>Send Wind Data</td>");
    content += F("<td>");
    content += F("<select name='sendwsdata' size='1'>");
    content += F("<option value='0'>Off</option>");
    content += F("<option value='1'>On</option>");
    content += F("</select>");
    content += F("</td>");
    content += F("<td></td>");
    content += F("</tr>");
  
    content += F("<tr>");
    content += F("<td>Wind Type</td>");
    content += F("<td>");
    content += F("<select name='windtype' size='1'>");
    content += F("<option value='R'>Relative Wind</option>");
    content += F("<option value='T'>True Wind</option>");
    content += F("</select>");
    content += F("</td>");
    content += F("<td></td>");
    content += F("</tr>");
  
    content += F("<tr>");
    content += F("<td>Offset</td>");
    content += F("<td><input type='text' name='offset' size='20' value='");
    content += String(actconf.offset);  
    content += F("' maxlength='4'></td>");
    content += F("<td>[°]</td>");
    content += F("</tr>");
    
    content += F("<tr>");
    content += F("<td>Average</td>");
    content += F("<td>");
    content += F("<select name='average' size='1'>");
    content += F("<option value='1'>1</option>");
    content += F("<option value='2'>2</option>");
    content += F("<option value='3'>3</option>");
    content += F("<option value='4'>4</option>");
    content += F("<option value='5'>5</option>");
    content += F("<option value='6'>6</option>");
    content += F("<option value='7'>7</option>");
    content += F("<option value='8'>8</option>");
    content += F("<option value='9'>9</option>");
    content += F("<option value='10'>10</option>");
    content += F("</select>");
    content += F("</td>");
    content += F("<td></td>");
    content += F("</tr>");
  
    content += F("<tr>");
    content += F("<td>Speed Unit</td>");
    content += F("<td>");
    content += F("<select name='speedunit' size='1'>");
    content += F("<option value='m/s'>m/s</option>");
    content += F("<option value='km/h'>km/h</option>");
    content += F("<option value='kn'>kn</option>");
    content += F("<option value='bft'>bft</option>");
    content += F("</select>");
    content += F("</td>");
    content += F("<td></td>");
    content += F("</tr>");
  
    content += F("<tr>");
    content += F("<td>Down Wind Sensor</td>");
    content += F("<td>");
    content += F("<select name='dwsensor' size='1'>");
    content += F("<option value='0'>Off</option>");
    content += F("<option value='1'>On</option>");
    content += F("</select>");
    content += F("</td>");
    content += F("<td></td>");
    content += F("</tr>");
  
    content += F("<tr>");
    content += F("<td>Down Wind Range</td>");
    content += F("<td>");
    content += F("<select name='dwrange' size='1'>");
    content += F("<option value='20'>180&deg; +/-20&deg;</option>");
    content += F("<option value='25'>180&deg; +/-25&deg;</option>");
    content += F("<option value='30'>180&deg; +/-30&deg;</option>");
    content += F("<option value='35'>180&deg; +/-35&deg;</option>");
    content += F("<option value='40'>180&deg; +/-40&deg;</option>");
    content += F("<option value='45'>180&deg; +/-45&deg;</option>");
    content += F("<option value='50'>180&deg; +/-50&deg;</option>");
    content += F("<option value='55'>180&deg; +/-55&deg;</option>");
    content += F("<option value='60'>180&deg; +/-60&deg;</option>");
    content += F("</select>");
    content += F("</td>");
    content += F("<td></td>");
    content += F("</tr>");
  
    content += F("<tr>");
    content += F("<td>Temp Sensor Type</td>");
    content += F("<td>");
    content += F("<select name='tstype' size='1'>");
    content += F("<option value='Off'>Off</option>");
    content += F("<option value='DS18B20'>DS18B20</option>");
    content += F("<option value='BME280'>BME280</option>");
    content += F("</select>");
    content += F("</td>");
    content += F("<td></td>");
    content += F("</tr>");
  
    content += F("<tr>");
    content += F("<td>Send Temp Data</td>");
    content += F("<td>");
    content += F("<select name='sendtsd' size='1'>");
    content += F("<option value='0'>Off</option>");
    content += F("<option value='1'>On</option>");
    content += F("</select>");
    content += F("</td>");
    content += F("<td></td>");
    content += F("</tr>");
  
    content += F("<tr>");
    content += F("<td>Temp Unit</td>");
    content += F("<td>");
    content += F("<select name='tempunit' size='1'>");
    content += F("<option value='C'>&deg;C</option>");
    content += F("<option value='F'>&deg;F</option>");
    content += F("</select>");
    content += F("</td>");
    content += F("<td></td>");
    content += F("</tr>");
  
    content += F("<tr>");
    content += F("<td><h3>Speed Sensor Calibration</h3></td>");
    content += F("<td></td>");
    content += F("<td></td>");
    content += F("</tr>");
  
    content += F("<tr>");
    content += F("<td>Calibration Slope</td>");
    content += F("<td><input type='text' required name='cslope' size='20' value='");
    char cslope[20];
    sprintf(cslope, "%.5f", actconf.calslope);
    content += cslope;
    content += F("' maxlength='20'></td>");
    content += F("<td>[1]</td>");
    content += F("</tr>");
  
    content += F("<tr>");
    content += F("<td>Calibration Offset</td>");
    content += F("<td><input type='text' required name='coffset' size='20' value='");
    char coffset[20];
    sprintf(coffset, "%.5f", actconf.caloffset);
    content += coffset;
    content += F("' maxlength='20'></td>");
    content += F("<td>[m/s]</td>");
    content += F("</tr>");
  
    content += F("<tr>");
    content += F("<td><br><button id='sub' type='submit'>Save</button></td>");
    content += F("<td></td>");
    content += F("<td></td>");
    content += F("</tr>");
  
    content += F("</table>");
  
    // Hidden input field for hash
    content += F("<input type='hidden' required name='password' size='20' value='");
    content += String(cryptPassword(String(actconf.password)));
    content += F("' maxlength='20'>");
    
    content += F("</form>");
    content += F("<br>");
  
    content += F("<hr align='left'>");
    content += F("<br>");
  /*
    content += F("<form id='form2' action='http://192.168.4.1/settings'>");
  
    content += F("<input hidden type='text' name='itype' value='simple'>");  
    content += F("<input hidden type='text' name='isize' value='200'>");  
    content += F("<input hidden type='text' name='cssid' value='MyBoat'>");
    content += F("<input hidden type='text' name='cpasswd' value='S6587rr94P'>");
    content += F("<input hidden type='text' name='sssid' value='NoWa'>");
    content += F("<input hidden type='text' name='spasswd' value='12345678'>");
    content += F("<input hidden type='text' name='servermode' value='0'>");
    content += F("<input hidden type='text' name='debugmode' value='3'>");
    content += F("<input hidden type='text' name='serspeed' value='115200'>");
    content += F("<input hidden type='text' name='sensorid' value='0'>");
    content += F("<input hidden type='text' name='wstype' value='WiFi 1000'>");
    content += F("<input hidden type='text' name='sendwsdata' value='1'>");
    content += F("<input hidden type='text' name='windtype' value='R'>");
    content += F("<input hidden type='text' name='average' value='1'>");
    content += F("<input hidden type='text' name='speedunit' value='kn'>");
    content += F("<input hidden type='text' name='dwsensor' value='1'>");
    content += F("<input hidden type='text' name='dwrange' value='50'>");
    content += F("<input hidden type='text' name='tstype' value='Off'>");
    content += F("<input hidden type='text' name='sendtsd' value='0'>");
    content += F("<input hidden type='text' name='tempunit' value='C'>");
    
    content += F("<button type='submit'>Set Defaults</button></form>");
  */  
    content += F("<br>"); 
    
    content += F("<form id='form3' action='/'><button type='submit'>Back</button></form>");
    
    content += F("<br>");
    content += F("<br>");
  
    content += F("</body>");
    content += F("</html>");
  
    return content;
 }  
}

