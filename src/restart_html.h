// Restart info webpage
String Reset(int num, String vname[20], String value[20])
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

 // Debug info 
 DebugPrintln(3, "Send restart.html"); 

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
   content +=F( "<form id='pwdForm' action='restart' method='get'><input size=20 type='text' name='password' id='password' onkeypress='return event.keyCode != 13;'><br/><br/><button TYPE='button' onClick='proc()'>Send</button></form>");
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
   
   // Page content when password correct
   String content;
   content +=F( "<!DOCTYPE html>");
   content +=F( "<html>");
   content +=F( "<head>");
   content +=F( "<title>Restart Windsensor</title>");
   content +=F( "<link rel='stylesheet' type='text/css' href='/css'>");
   content +=F( "<meta http-equiv='content-type' content='text/html; charset=UTF-8'>");
   content +=F( "<meta name=viewport content='width=device-width, initial-scale=1'>");
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
   
   content +=F( "<h3>Restart Windsensor</h3>");
   content +=F( "After Restart change the system automatically to the main page.");
   content +=F( "<br>");
   content +=F( "<br>");
   content +=F( "<form action='/'><input type='hidden' name='restart' value='1'><button type='submit'>Restart</button></form>");
   content +=F( "<br>");
   content +=F( "<hr align='left'>");
   content +=F( "<br>");
   content +=F( "<form action='/'><input type='hidden' name='restart' value='0'><button type='submit'>Back</button></form>");
   content +=F( "</body>");
   content +=F( "</html>");
  
   return content;
 }
}
