// Gauge instrument webpage
String Windi()
{
 // Debug info 
 DebugPrintln(3, "Send windi.html");

 // Prepare instrument scaling
 scalefactor = float(actconf.instrumentSize) / 200.0;

 // Style activation
 String framecolor, backcolor, lcdcolor;
 
 switch (style) {
  case 0:
    // Night style
    icolor = "#FF0000";
    framecolor = "ANTHRACITE";
    backcolor = "BLACK";
    lcdcolor = "GREEN";
    break;
  case 1:
    // Day style black
    icolor = "#FFFFFF";
    framecolor = "BLACK_METAL";
    backcolor = "ANTHRACITE";
    lcdcolor = "STANDARD";
    break;
  case 2:
    // Day style whithe
    icolor = "#000000";
    framecolor = "BLACK_METAL";
    backcolor = "ANTHRACITE";
    lcdcolor = "STANDARD";
    break;  
  default:
    // Day style white
    icolor = "#000000";
    framecolor = "BLACK_METAL";
    backcolor = "ANTHRACITE";
    lcdcolor = "STANDARD";
 }
 
 // Page content with outo reload (polling)
 String content;
 content += F("<!DOCTYPE html>");
 content += F("<html>");
 content += F("<head>");
 content += F("<title>Windsensor Instrument</title>");
 content += F("<link rel='stylesheet' type='text/css' href='/css'>");
 content += F("<script src='/tween-min.js' type='text/javascript'></script>");
 content += F("<script src='/steelseries_micro.js' type='text/javascript'></script>");
 content += F("<meta http-equiv='content-type' content='text/html; charset=UTF-8'>");
 content += F("<meta name=viewport content='width=device-width, initial-scale=1'>");
 content += F("<style>");
 //content += CSS();
 content += F("</style>");
 content += F("</head>");
 content += F("<body>");
 
 // Web page title
 content += F("<h2>");
 content += String(actconf.devname) + " " + String(actconf.windSensorType);
 content += F("</h2>");
 content += String(actconf.crights);
 content += F(", "); 
 content += String(actconf.fversion);
 content += F(", CQ: <data id = 'quality'></data>%");
 content += F("<hr align='left'>");
 
 content += F("<h3>Windsensor Instrument  <blink><data id='info'></data></blink></h3>");

 content += F("<canvas id='myCanvas' width='");
 content += String(actconf.instrumentSize);
 content += F("' height='");
 content += String(actconf.instrumentSize);
 content += F("' style='border:0px solid #000000;'>");
 content += F("Your browser does not support the HTML5 canvas tag.");
 content += F("</canvas>");

 content += F("<script>");
 content += F("var winddir = 0;");
 content += F("var windunit = '°';");
 content += F("var windspeed = 0;");
 content += F("var speedunit = 'kn';");
 content += F("var windGauge;");
 content += F("var internet = 0;");
 content += F("var flag = 0;");
 content += F("var itype = 'simple';");
 
 // Simple Instrument
 content += F("function simple_instrument() {");
 content += F("var c = document.getElementById('myCanvas');");
 content += F("var ctx = c.getContext('2d');");
 // Save all start settings for next start
 content += F("ctx.save();");
 // Set scale factor for all values
 content += F("ctx.scale(");
 content += String(scalefactor);
 content += F(",");
 content += String(scalefactor);
 content += F(");");
 // Settings
 content += F("var width = 200;");
 content += F("var height = 200;");
 content += F("var radius = 80;");
 content += F("var pointer_lenght = 60;");
 content += F("var pointer_linewidth = 4;");
 content += F("var circle_linewidth = 1;");
 content += F("var value_min = 0;");
 content += F("var value_max = 360;");
 content += F("var angle_scala = 360;");
 content += F("var angle_offset = 0;");
 // Calculation of pointer rotation
 content += F("var angle = ((angle_scala) / (value_max - value_min) * winddir) + angle_offset;");
 // Clear Canvas complete
 content += F("ctx.clearRect(0, 0, width, height);");
 // Write inner circle in center position
 content += F("ctx.beginPath();");
 content += F("ctx.strokeStyle = '");
 content += icolor;
 content += F("';");
 content += F("ctx.lineWidth = circle_linewidth;");
 content += F("ctx.arc(width / 2 ,height / 2,radius*0.8,0,2*Math.PI);");
 content += F("ctx.stroke();");
 // Write left partial circle
 content += F("ctx.beginPath();");
 content += F("ctx.strokeStyle = '#888888';");
 content += F("ctx.lineWidth = 10;");
 content += F("start = 210;");
 content += F("end = 250;");
 content += F("ctx.arc(width / 2 ,height / 2,radius*0.9,2*Math.PI/360*start,2*Math.PI/360*end);");
 content += F("ctx.stroke();");
 // Write right partial circle
 content += F("ctx.beginPath();");
 content += F("ctx.strokeStyle = '#888888';");
 content += F("ctx.lineWidth = 10;");
 content += F("start = 290;");
 content += F("end = 330;");
 content += F("ctx.arc(width / 2 ,height / 2,radius*0.9,2*Math.PI/360*start,2*Math.PI/360*end);");
 content += F("ctx.stroke();");
 // Write partial circle
 content += F("ctx.beginPath();");
 content += F("ctx.strokeStyle = '#888888';");
 content += F("ctx.lineWidth = 10;");
 content += F("start = ");
 int start = 90 - int(actconf.downWindRange);
 content += String(start);
 content += F(";");
 content += F("end = ");
 int ende = 90 + int(actconf.downWindRange);
 content += String(ende);
 content += F(";");
 content += F("ctx.arc(width / 2 ,height / 2,radius*0.9,2*Math.PI/360*start,2*Math.PI/360*end);");
 content += F("ctx.stroke();");
 // Write scale
 content += F("for (i = 0; i < 12; i++){");
 content += F("ctx.beginPath();");
 content += F("ctx.strokeStyle = '");
 content += icolor;
 content += F("';");
 content += F("ctx.lineWidth = 10;");
 content += F("start = i*30;");
 content += F("end = i*30+2;");
 content += F("ctx.arc(width / 2 ,height / 2,radius*0.9,2*Math.PI/360*start,2*Math.PI/360*end);");
 content += F("ctx.stroke();");
 content += F("}");
 // Create text
 content += F("ctx.strokeStyle = '");
 content += icolor;
 content += F("';");
 content += F("ctx.font = '20px Arial';");
 content += F("ctx.fillStyle = '");
 content += icolor;
 content += F("';");
 content += F("ctx.fillText(winddir + '");
 content += F("°");
 content += F("',width/2*0.65,height/2*0.95);");
 content += F("ctx.fillText(windspeed + '");
 content += String(actconf.speedUnit);
 content += F("',width/2*0.65,height/2*1.15);");
 // Move the pointer from 0,0 to center position
 content += F("ctx.translate(width / 2 ,height / 2);");
 // Rotate
 content += F("ctx.rotate(angle * Math.PI / 180);");
 // Write pointer
 content += F("ctx.beginPath();");
 content += F("ctx.lineWidth = pointer_linewidth;");
 content += F("ctx.lineCap = 'round';");
 content += F("ctx.moveTo(0,(-pointer_lenght - (-pointer_lenght / 3)));");
 content += F("ctx.lineTo(0,-pointer_lenght);");
 content += F("ctx.stroke();");
 // Restore all start settings for next start
 content += F("ctx.lineTo(0,-pointer_lenght);");
 content += F("ctx.restore();");
 content += F("};");

 // Complex instrument for relatv wind
 content += F("function complex_instrument() {");
 content += F("windGauge = new steelseries.WindDirection2('myCanvas', {");
 content += F("size: ");
 int cisize = float(actconf.instrumentSize) * 0.85;
 content += String(cisize);
 content += F(",");
 content += F("section: [");
 // Upwind range
 content += F("steelseries.Section(-60, -20, 'rgba(255, 0, 0, 0.8)'),");
 content += F("steelseries.Section(20, 60, 'rgba(0, 255, 0, 0.8)'),");
 // Down wind range
 int cistart = 180 - int(actconf.downWindRange);
 int ciende = -180 + int(actconf.downWindRange);
 content += F("steelseries.Section(");
 content += String(cistart);
 content += F(", ");
 content += String(ciende);
 content += F(", 'rgba(255, 255, 0, 0.5)')");
 content += F("],");
 content += F("pointSymbolsVisible: false,");
 
 content += F("frameDesign: steelseries.FrameDesign.");
 content += String(framecolor);
 content += F(",");
 content += F("backgroundColor: steelseries.BackgroundColor.");
 content += String(backcolor);
 content += F(",");
 content += F("lcdVisible: true,");
 content += F("lcdColor: steelseries.LcdColor.");
 content += String(lcdcolor);
 content += F(",");
 content += F("lcdTitleStrings: ['Direction [°]', 'Speed [");
 content += String(actconf.speedUnit);
 content += F("]'],");
 content += F("pointerColor: steelseries.ColorDef.RED,");
 content += F("pointerTypeLatest: steelseries.PointerType.TYPE6,");
 content += F("pointerTypeAverage: steelseries.PointerType.TYPE6,");
 content += F("degreeScaleHalf: true,");
 //content += F("fullScaleDeflectionTime: 0.1,");                 // Only when using setValueAnimatedAverage (actually is the lib faulty)
 content += F("});");
 // Start values
 content += F("windGauge.setValueAnimatedAverage(0);");
 content += F("windGauge.setValueAnimatedLatest(0);");
 content += F("}");

 // Complex instrument 2 for true wind
 content += F("function complex_instrument2() {");
 content += F("windGauge = new steelseries.WindDirection2('myCanvas', {");
 content += F("size: ");
 cisize = float(actconf.instrumentSize) * 0.85;
 content += String(cisize);
 content += F(",");
 content += F("pointSymbolsVisible: true,");
 
 content += F("frameDesign: steelseries.FrameDesign.");
 content += String(framecolor);
 content += F(",");
 content += F("backgroundColor: steelseries.BackgroundColor.");
 content += String(backcolor);
 content += F(",");
 content += F("lcdVisible: true,");
 content += F("lcdColor: steelseries.LcdColor.");
 content += String(lcdcolor);
 content += F(",");
 content += F("lcdTitleStrings: ['Direction [°]', 'Speed [");
 content += String(actconf.speedUnit);
 content += F("]'],");
 content += F("pointerColor: steelseries.ColorDef.RED,");
 content += F("pointerTypeLatest: steelseries.PointerType.TYPE6,");
 content += F("pointerTypeAverage: steelseries.PointerType.TYPE6,");
 content += F("degreeScaleHalf: true,");
 //content += F("fullScaleDeflectionTime: 0.1,");                 // Only when using setValueAnimatedAverage (actually is the lib faulty)
 content += F("});");
 // Start values
 content += F("windGauge.setValueAnimatedAverage(0);");
 content += F("windGauge.setValueAnimatedLatest(0);");
 content += F("}");

 // Read all JSON data strings
 content += F("var xmlhttp = new XMLHttpRequest();");
 content += F("xmlhttp.onreadystatechange = function() {");
 content += F("if (this.readyState == 4 && this.status == 200) {");
 content += F("var myObj = JSON.parse(this.responseText);");
 content += F("windtype = myObj.Device.DeviceSettings.WindType;");
 content += F("winddir = myObj.Device.MeasuringValues.WindDirection.Value;");
 content += F("winddir = Math.round(winddir*10)/10;");
 content += F("dirunit = myObj.Device.MeasuringValues.WindDirection.Unit;");
 content += F("windspeed = myObj.Device.MeasuringValues.WindSpeed.Value;");
 content += F("windspeed = Math.round(windspeed*10)/10;");
 content += F("speedunit = myObj.Device.MeasuringValues.WindSpeed.Unit;");
 content += F("document.getElementById('quality').innerHTML = myObj.Device.NetworkParameter.ConnectionQuality.Value;");
 // If Demo Mode active the give out a message
 content += F("servermode = myObj.Device.NetworkParameter.ServerMode;");
 content += F("if (servermode == 4) {");
 content += F("document.getElementById('info').innerHTML = '(Demo Mode)';");
 content += F("}");
 content += F("else {");
 content += F("document.getElementById('info').innerHTML = '';");
 content += F("}");
 
 content += F("itype = myObj.Device.DisplaySettings.InstrumentType;");
 // Complex Instrument
 content += F("if(internet == 1 && itype == 'complex'){");
 content += F("if(flag == 0){");

 content += F("if(windtype == 'R'){");
 content += F("complex_instrument();");
 content += F("}");
 content += F("else{");
 content += F("complex_instrument2();");
 content += F("}");
 
 // content += F("complex_instrument();");
 
 content += F("flag = 1;");
 content += F("}");
 //content += F("windGauge.setValueAnimatedAverage(windspeed);");   //setValueAnimatedAverage is in lib defect
 //content += F("windGauge.setValueAnimatedLatest(winddir);");      //setValueAnimatedAverage is in lib defect
 content += F("windGauge.setValueAverage(windspeed);");
 content += F("windGauge.setValueLatest(winddir);");
 content += F("}");
 // Simple instrument
 content += F("if(internet == 0 || itype == 'simple'){");
 content += F("simple_instrument();");
 content += F("}");
 content += F("}");
 content += F("};");
 
 // Load JSON data
 content += F("function read_json() {");
// content += F("xmlhttp.open('GET', 'http://192.168.4.1/json', true);");
 content += F("xmlhttp.open('GET', '/json', true);");
 content += F("xmlhttp.send();");
 content += F("};");

 // Check the internet status
 content += F("var xmlhttp2 = new XMLHttpRequest();");
 content += F("xmlhttp2.onreadystatechange = function() {");
 content += F("if (this.readyState == 4 && this.status == 200) {internet = 1;}");
 content += F("else {internet = 0;}");
 content += F("};");
 // Open the webside from GitLab for internet connection check
 content += F("function check_internet() {");
// content += F("xmlhttp2.open('GET', 'http://192.168.4.1/tween-min.js', true);");
 content += F("xmlhttp2.open('GET', '/tween-min.js', true);");
 content += F("xmlhttp2.send();");
 content += F("};");

 content += F("check_internet();");
 content += F("setInterval(function(){read_json(); }, 1000);");

 
 
 content += F("</script>");

 content += F("<br>");
 content += F("<hr align='left'>");
 content += F("<br>");
 content += F("<form action='/'><button type='submit'>Back</button></form>");
 
 content += F("</body>");
 content += F("</html>");
 
 return content;
}
