// Server pages
// Insert this library after server definition

httpServer.on("/", []() {
  // Read all received get arguments and save in a array
  int num = httpServer.args();
  String vname[num];
  String value[num];
  for (int i = 0; i < num; i++) {
    vname[i] = httpServer.argName(i);
    value[i] = httpServer.arg(i);
    // Check the return value from Restart web page
    if(vname[i] == "restart" &&  value[i] == "1"){
      resetESP = 1;
    }
    else{
      resetESP = 0;
    }
  } 
  // Send page     
  String content = Startpage(num, vname, value);
  httpServer.sendHeader("Cache-Control", "no-cache");
  httpServer.send(200, "text/html", content);

  // Restart routine
  if(resetESP == 1){
    delay(3000); // Waiting time for system restart
    resetESP = 0;
    // Restart the ESP8266
    ESP.restart();
  }      
});

httpServer.on("/settings", []() {
  // Read all received get arguments and save in a array
  int num = httpServer.args();
  String vname[num];
  String value[num];
  for (int i = 0; i < num; i++) {
    vname[i] = httpServer.argName(i);
    value[i] = httpServer.arg(i);  
  } 
  // Send page
  String content = Settings(num, vname, value);
  httpServer.sendHeader("Cache-Control", "no-cache");
  httpServer.send(200, "text/html", content);  
});

httpServer.on("/restart", []() {
  // Read all received get arguments and save in a array
  int num = httpServer.args();
  String vname[num];
  String value[num];
  for (int i = 0; i < num; i++) {
    vname[i] = httpServer.argName(i);
    value[i] = httpServer.arg(i);  
  } 
  // Send page
  String content = Reset(num, vname, value);
  httpServer.sendHeader("Cache-Control", "no-cache");
  httpServer.send(200, "text/html", content);
});

httpServer.on("/firmware", []() {
  // Read all received get arguments and save in a array
  int num = httpServer.args();
  String vname[num];
  String value[num];
  for (int i = 0; i < num; i++) {
    vname[i] = httpServer.argName(i);
    value[i] = httpServer.arg(i);  
  } 
  // Send page
  String content = Firmware(num, vname, value);
  httpServer.sendHeader("Cache-Control", "no-cache");
  httpServer.send(200, "text/html", content);
});

httpServer.on("/devinfo", []() {
  String content = Devinfo();
  httpServer.sendHeader("Cache-Control", "no-cache");
  httpServer.send(200, "text/html", content);
});

httpServer.on("/windv", []() {
  String content = Windv();
  httpServer.sendHeader("Cache-Control", "no-cache");
  httpServer.send(200, "text/html", content);
});

httpServer.on("/windi", []() {
  String content = Windi();
  httpServer.sendHeader("Cache-Control", "no-cache");
  httpServer.send(200, "text/html", content);
});

httpServer.on("/favicon.ico", []() {
  String content = Icon();
  httpServer.sendHeader("Cache-Control", "max-age=600");
  httpServer.send(200, "image/svg+xml", content);
});

httpServer.on("/css", []() {
  String content = CSS();
   httpServer.sendHeader("Cache-Control", "no-cache");
  httpServer.send(200, "text/css", content);
});

httpServer.on("/js", []() {
  String content = JS();
  httpServer.sendHeader("Cache-Control", "no-cache");
  httpServer.send(200, "text/javascript", content);
});

httpServer.on("/tween-min.js", []() {
  httpServer.sendHeader("Cache-Control", "max-age=600");
  httpServer.sendHeader("content-encoding", "gzip");
  // Send binary data as compessed gz content
  httpServer.send_P(200, "text/javascript", tween_min_js_gz, sizeof(tween_min_js_gz));
});

httpServer.on("/steelseries_micro.js", []() {
  httpServer.sendHeader("Cache-Control", "max-age=600");
  httpServer.sendHeader("content-encoding", "gzip");
  // Send binary data as compessed gz content
  httpServer.send_P(200, "text/javascript", steelseries_micro_js_gz, sizeof(steelseries_micro_js_gz));
});

httpServer.on("/json", []() {
  String content = JSON();
  httpServer.sendHeader("Access-Control-Allow-Origin", "*"); // Needs new browser for CORS (Cross Origin Resource Sharing)
  httpServer.sendHeader("Cache-Control", "no-cache");
  httpServer.send(200, "application/json", content);
});

// Send JSON2 only for Diagnostic Mode
httpServer.on("/json2", []() {
  String content = JSON2();
  httpServer.sendHeader("Access-Control-Allow-Origin", "*"); // Needs new browser for CORS (Cross Origin Resource Sharing)
  httpServer.sendHeader("Cache-Control", "no-cache");
  httpServer.send(200, "application/json", content);
});

// Use no cash because the js was permanently modifyed (transaction ID)
httpServer.on("/MD5.js", []() {
  String content = MD5();
  httpServer.sendHeader("Cache-Control", "no-cache");
  httpServer.send(200, "text/javascript", content);
});

httpServer.onNotFound([]() {
  String content = Error();
  httpServer.send(404, "text/html", content);
});

