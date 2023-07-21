// Firmware update webpage
String Firmware(int num, String vname[20], String value[20])
{
 String hash = "";
  
 // Print all received get arguments
 for(int i = 0; i < num; i++)
  {
    String out = vname[i] + " : " + value[i];
    DebugPrintln(3, out);
    
    if(vname[i] == "password"){
      hash = value[i];
    }
  }
   
 DebugPrintln(3, "Send firmware.html");

 // Check page password
 if(actconf.crypt == 1 && (hash.length() == 0 || hash != cryptPassword(String(actconf.password)))){
   // Generate a new transaction ID
   transID();
   
   // Page content for password input
   String content;
   content +=F( "<!DOCTYPE html>");
   content +=F( "<html>");
   content +=F( "<head>");
   content +=F( "<title>Restart Windsensor</title>");
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
   content +=F( "<form id='pwdForm' action='firmware' method='get'><input size=20 type='text' name='password' id='password' onkeypress='return event.keyCode != 13;'><br/><br/><button TYPE='button' onClick='proc()'>Send</button></form>");
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
   content +=F( "<!DOCTYPE html>");
   content +=F( "<html>");
   content +=F( "<head>");
   content +=F( "<meta http-equiv='content-type' content='text/html; charset=UTF-8'>");
   content +=F( "<meta name=viewport content='width=device-width, initial-scale=1'>");
   content +=F( "<title>Update Windsensor</title>");
   
   content +=F( "<link rel='stylesheet' type='text/css' href='/css'>");
   content +=F( " <style>");
  // content += CSS();
   content +=F( "</style>");
  
   content +=F( "<script type='text/javascript'>");
  
   content +=F( "var link;");
   content +=F( "var data;"); // Firmware file as blob
   content +=F( "var internet = 0;");
   content +=F( "var actualversion = '");
   content += String(actconf.fversion);
   content +=F( "';");
  
   content +=F( "var xmlhttp = new XMLHttpRequest();");
   content +=F( "var xmlhttp2 = new XMLHttpRequest();");
   
   content +=F( "xmlhttp.onreadystatechange = function() {");
   // If internet connection available            
   content +=F( "if (this.readyState == 4 && this.status == 200) {");
   content +=F( "internet = 1;");
   // Read link to firmware and firmware version
   content +=F( "link = this.responseText;");
   content +=F( "var firmware =  link.slice(54, 100);");
   content +=F( "var version = link.slice(63, 68);");
   content +=F( "document.upform1.firmware.value = firmware;");
   content +=F( "document.upform1.version.value = version;");
   // New firmware available
   content +=F( "if(actualversion != version){");
   content +=F( "document.getElementById('sub2').disabled = false;");
   content +=F( "document.getElementById('sub2').hidden = false;");
   content +=F( "document.getElementById('info').innerHTML = 'New firmware is available.';");
   content +=F( "}");
   // Firmware is actual
   content +=F( "else{");
   content +=F( "document.getElementById('sub2').disabled = true;");
   content +=F( "document.getElementById('sub2').hidden = true;");
   content +=F( "document.getElementById('info').innerHTML = 'Your firmware is actual.';");
   content +=F( "}");
   // No internet connetion
   content +=F( "} else {");
   content +=F( "internet = 0;");
   content +=F( "document.getElementById('sub2').disabled = true;");
   content +=F( "document.getElementById('sub2').hidden = true;");
   content +=F( "document.upform1.firmware.value = 'No Internet Connection!';");
   content +=F( "document.upform1.version.value = '---';");
   content +=F( "document.getElementById('info').innerHTML = 'Try later for update.';");
   content +=F( "}");
   // Download new firmware file
   content +=F( "xmlhttp2.open('GET', link, true);");
   content +=F( "xmlhttp2.responseType = 'arraybuffer';"); // Is a array buffer for binary data
   content +=F( "xmlhttp2.send();"); 
   content +=F( "};");
  
   content +=F( "xmlhttp2.onreadystatechange = function() {");
   content +=F( "if (this.readyState == 4 && this.status == 200) {");
   // Save file in a blob as octec-stream and create URL
   content +=F( "data = new Blob([this.response], { type: 'application/octet-stream' });");
   content +=F( "}");
   content +=F( "};");
  
   content +=F( "function check_internet() {");
   content +=F( "xmlhttp.open('GET', 'https://norbertwalter67.gitlab.io/plain-html/firmware/ActualVersion.txt', true);");
   content +=F( "xmlhttp.send();");
   content +=F( "};");
  
   
   content +=F( "function check_file() {");
   // Load filepaht with filename
   content +=F( "var filename = document.upform.image.value;");
   // Split file extension
   content +=F( "var extension = filename.split('.');");
   content +=F( "extension = extension[extension.length - 1];");
   // Enable or disable the submit button depends on file type
   content +=F( "if(extension == 'bin' || extension == 'wsb'){");
   content +=F( "document.getElementById('sub').disabled=false;");
   content +=F( "}");
   content +=F( "else{");
   content +=F( "alert('Wrong file type!');");
   content +=F( "document.getElementById('sub').disabled=true;");
   content +=F( "}");
   content +=F( "}");

   content +=F( "function send_image() {");
   content +=F( "var xhr = new XMLHttpRequest();");
   content +=F( "xhr.open('POST', '/update', true);");
   content +=F( "var formData = new FormData();");
   content +=F( "formData.append('file', data, 'firmware.bin');");
   // Action after uploading
   content +=F( "xhr.onload = function(e) {");
   content +=F( "alert('Update successful!');");
   content +=F( "console.log('File uploading completed');");
   content +=F( "};");
   content +=F( "var r = confirm('Update firmware?');");
   content +=F( "if (r == true) {");
   content +=F( "");
   content +=F( "");
   content +=F( "");
   content +=F( "console.log('File uploading started');");
   content +=F( "xhr.send(formData);");
   content +=F( "}");
   content +=F( "else {");
   content +=F( "console.log('File uploading stoped');");
   content +=F( "}");
   content +=F( "}");
   
   content +=F( "</script>");
   
   content +=F( "</head>");
   content +=F( "<body onload='check_internet();'>");
   
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
   
   content +=F( "<h3>Firmware Update</h3>");
   
   content +=F( "<form name='upform' action='/update' method='post' enctype='multipart/form-data'>Select a local file for firmware upload (firmware_xxxx.wsb):");
   content +=F( "<p>");
   content +=F( "<input type='file' required name='image' onchange='check_file()'>");
   content +=F( "<p>");
   content +=F( "<button type='submit' id='sub'>Update Firmware</button>");
   content +=F( "</form>");
   content +=F( "<hr align='left'>");
   
   content +=F( "<form name='upform1' action='/update' method='post' enctype='multipart/form-data'>Or use the actual online firmware on GitLab:");
   content +=F( "<p>");
   content +=F( "<input type='text' name='firmware' size='20' value='' onchange='check_file()'> Version:");
   content +=F( "<input type='text' name='version' size='5' value='' maxlength='20'>");
   content +=F( "<p><font size='2'><data id='info'></data></font>");
   content +=F( "</form>");
  
   content +=F( "<button type='submit' id='sub2' onclick='send_image()'>Update Firmware</button>");
   content +=F( "<br>");
   
   content +=F( "<br><b>Info:</b> A message is displayed afer successful update.");
   content +=F( "<hr align='left'>");
   content +=F( "<br>");
   content +=F( "<form action='/'>");
   content +=F( "<button type='submit'>Back</button>");
   content +=F( "</form>");
   content +=F( "</body>");
   content +=F( "</html>");
  
   return content;
 }  
}
