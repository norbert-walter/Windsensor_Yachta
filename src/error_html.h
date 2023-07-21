// Error info webpage
String Error()
{
 // Debug info 
 DebugPrintln(3, "Send error.html"); 

 // Page content with auto redirect to main page after 5 seconds
 String content;
 content +=F( "<!DOCTYPE html>\r\n");
 content +=F( "<html>\r\n");
 content +=F( "<head>\r\n");
 content +=F( "<title>Error Windsensor</title>\r\n");
 content +=F( "<link rel='stylesheet' type='text/css' href='/css'>\r\n");
 content +=F( "<meta http-equiv='content-type' content='text/html; charset=UTF-8'>\r\n");
 content +=F( "<meta name=viewport content='width=device-width, initial-scale=1'>\r\n");
 content +=F( "<meta http-equiv='refresh' content='5; URL=/'>\r\n");
 content +=F( " <style>");
// content += CSS();
 content +=F( "</style>\r\n");
 content +=F( "</head>\r\n");
 content +=F( "<body>\r\n");
 
 // Web page title
 content +=F( "<h2>");
 content += String(actconf.devname) + " " + String(actconf.windSensorType);
 content +=F( "</h2>");
 content += String(actconf.crights);
 content +=F( ", "); 
 content += String(actconf.fversion);
 content +=F( ", CQ: ");
 content += String(wlanquality());
 content +=F( "%\r\n"); 
 content +=F( "<hr align='left'>\r\n");
 
 content +=F( "<h3>Error 404: Page not found</h3>\r\n");
 content +=F( "</body>\r\n");
 content +=F( "</html>\r\n");

 return content;
}
