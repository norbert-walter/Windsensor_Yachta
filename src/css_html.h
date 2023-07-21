String CSS()
{
 // Debug info 
 DebugPrintln(3, "Send css.html");

 String content;

 // Page daystyle in black background and white font
 // ************************************************
 String blackcontent; 
 // Button style and color
 blackcontent += F("button {");
 blackcontent += F("font-family: Arial, Helvetica, sans-serif;");
 blackcontent += F("font-size: 14px;");
 blackcontent += F("color: #000000;");
 blackcontent += F("padding: 10px 20px;");
 blackcontent += F("background: -moz-linear-gradient(");
 blackcontent += F("top,");
 blackcontent += F("#ffffff 0%,");
 blackcontent += F("#ffffff 50%,");
 blackcontent += F("#bdbbbd);");
 blackcontent += F("background: -webkit-gradient(");
 blackcontent += F("linear, left top, left bottom,");
 blackcontent += F("from(#ffffff),");
 blackcontent += F("color-stop(0.50, #ffffff),");
 blackcontent += F("to(#bdbbbd));");
 blackcontent += F("-moz-border-radius: 10px;");
 blackcontent += F("-webkit-border-radius: 10px;");
 blackcontent += F("border-radius: 10px;");
 blackcontent += F("border: 3px solid #dedcd5;");
 blackcontent += F("-moz-box-shadow:");
 blackcontent += F("0px 1px 3px rgba(000,000,000,0.5),");
 blackcontent += F("inset 0px 0px 3px rgba(255,255,255,1);");
 blackcontent += F("-webkit-box-shadow:");
 blackcontent += F("0px 1px 3px rgba(000,000,000,0.5),");
 blackcontent += F("inset 0px 0px 3px rgba(255,255,255,1);");
 blackcontent += F("box-shadow:");
 blackcontent += F("0px 1px 3px rgba(000,000,000,0.5),");
 blackcontent += F("inset 0px 0px 3px rgba(255,255,255,1);");
 blackcontent += F("text-shadow:");
 blackcontent += F("0px -1px 0px rgba(000,000,000,0.1),");
 blackcontent += F("0px 1px 0px rgba(255,255,255,1);");
 blackcontent += F("}");
 
 // Text color definitions for head letters
 blackcontent += F("a: {color: rgb(255,255,255);}");
 blackcontent += F("h1 {color: rgb(255,255,255);}");
 blackcontent += F("h2 {color: rgb(255,255,255);}");
 blackcontent += F("h3 {color: rgb(255,255,255);}");
 blackcontent += F("h4 {color: rgb(255,255,255);}");
 blackcontent += F("h5 {color: rgb(255,255,255);}");
 blackcontent += F("h6 {color: rgb(255,255,255);}");
 blackcontent += F("h7 {color: rgb(255,255,255);}");
 
 // General text definitions
 blackcontent += F("body {");
 blackcontent += F("color: rgb(200,200,200);");
 blackcontent += F("font-family: arial;");
 blackcontent += F("}");

 // Blinking text definition
 blackcontent += F("blink {");
 blackcontent += F("animation: blinker 0.6s linear infinite;");
 blackcontent += F("}");
 blackcontent += F("@keyframes blinker {");
 blackcontent += F("50% { opacity: 0; }");
 blackcontent += F("}");
 
 // Background definitions
 blackcontent += F("body {");
 blackcontent += F("background-color: rgb(32, 32, 32);");
 blackcontent += F("background-image: linear-gradient(45deg, black 25%, transparent 25%, transparent 75%, black 75%, black),");
 blackcontent += F("linear-gradient(45deg, black 25%, transparent 25%, transparent 75%, black 75%, black),");
 blackcontent += F("linear-gradient(to bottom, rgb(8, 8, 8), rgb(32, 32, 32));");
 blackcontent += F("background-size: 10px 10px, 10px 10px, 10px 5px;");
 blackcontent += F("background-position: 0px 0px, 5px 5px, 0px 0px;");
 blackcontent += F("}");

 // SVG line colors
 blackcontent += F("svg {");
 blackcontent += F("stroke: #FFFFFF;");
 blackcontent += F("}");

 // Page nightstyle in black background an red font
 // ***********************************************
 String redcontent;
 // Button style and color
 redcontent += F("button {");
 redcontent += F("font-family: Arial, Helvetica, sans-serif;");
 redcontent += F("font-size: 14px;");
 redcontent += F("color: #050505;");
 redcontent += F("padding: 10px 20px;");
 redcontent += F("background: -moz-linear-gradient(");
 redcontent += F("top,");
 redcontent += F("#363636 0%,");
 redcontent += F("#d95f5f 50%,");
 redcontent += F("#ff0000 50%,");
 redcontent += F("#f70000);");
 redcontent += F("background: -webkit-gradient(");
 redcontent += F("linear, left top, left bottom,");
 redcontent += F("from(#363636),");
 redcontent += F("color-stop(0.50, #d95f5f),");
 redcontent += F("color-stop(0.50, #ff0000),");
 redcontent += F("to(#f70000));");
 redcontent += F("-moz-border-radius: 10px;");
 redcontent += F("-webkit-border-radius: 10px;");
 redcontent += F("border-radius: 10px;");
 redcontent += F("border: 3px solid #eb1717;");
 redcontent += F("-moz-box-shadow:");
 redcontent += F("0px 1px 3px rgba(000,000,000,0.5),");
 redcontent += F("inset 0px 0px 2px rgba(245,12,12,1);");
 redcontent += F("-webkit-box-shadow:");
 redcontent += F("0px 1px 3px rgba(000,000,000,0.5),");
 redcontent += F("inset 0px 0px 2px rgba(245,12,12,1);");
 redcontent += F("box-shadow:");
 redcontent += F("0px 1px 3px rgba(000,000,000,0.5),");
 redcontent += F("inset 0px 0px 2px rgba(245,12,12,1);");
 redcontent += F("text-shadow:");content +=F( "<td></td>");
 redcontent += F("0px -1px 0px rgba(000,000,000,0.2),");
 redcontent += F("0px 1px 0px rgba(71,68,71,0.4);");
 redcontent += F("}");

 // Text color definitions for heat letters
 redcontent += F("a: {color: rgb(255,0,0);}");
 redcontent += F("h1 {color: rgb(255,0,0);}");
 redcontent += F("h2 {color: rgb(255,0,0);}");
 redcontent += F("h3 {color: rgb(255,0,0);}");
 redcontent += F("h4 {color: rgb(255,0,0);}");
 redcontent += F("h5 {color: rgb(255,0,0);}");
 redcontent += F("h6 {color: rgb(255,0,0);}");
 redcontent += F("h7 {color: rgb(255,0,0);}");
 
 // General text definitions
 redcontent += F("body {");
 redcontent += F("color: rgb(200,0,0);");
 redcontent += F("font-family: arial;");
 redcontent += F("}");

 // Blinking text definition
 redcontent += F("blink {");
 redcontent += F("animation: blinker 0.6s linear infinite;");
 redcontent += F("}");
 redcontent += F("@keyframes blinker {");
 redcontent += F("50% { opacity: 0; }");
 redcontent += F("}");
 
 // Background definitions
 redcontent += F("body {");
 redcontent += F("background-color: rgb(32, 32, 32);");
 redcontent += F("background-image: linear-gradient(45deg, black 25%, transparent 25%, transparent 75%, black 75%, black), linear-gradient(45deg, black 25%, transparent 25%, transparent 75%, black 75%, black), linear-gradient(to bottom, rgb(8, 8, 8), rgb(32, 32, 32));");
 redcontent += F("background-size: 10px 10px, 10px 10px, 10px 5px;");
 redcontent += F("background-position: 0px 0px, 5px 5px, 0px 0px;");
 redcontent += F("}");

 // SVG line colors
 redcontent += F("svg {");
 redcontent += F("stroke: #C0C0C0;");
 redcontent += F("}");

 // Page daystyle in white background an black font
 // ***********************************************
 String whitecontent;
 // Button style and color
 whitecontent += F("button {");
 whitecontent += F("font-family: Arial, Helvetica, sans-serif;");
 whitecontent += F("font-size: 14px;");
 whitecontent += F("color: #ffffff;");
 whitecontent += F("padding: 10px 20px;");
 whitecontent += F("background: -moz-linear-gradient(");
 whitecontent += F("top,");
 whitecontent += F("#a3a3a3 0%,");
 whitecontent += F("#3b3b3b 50%,");
 whitecontent += F("#242424 50%,");
 whitecontent += F("#000000);");
 whitecontent += F("background: -webkit-gradient(");
 whitecontent += F("linear, left top, left bottom,");
 whitecontent += F("from(#a3a3a3),");
 whitecontent += F("color-stop(0.50, #3b3b3b),");
 whitecontent += F("color-stop(0.50, #242424),");
 whitecontent += F("to(#000000));");
 whitecontent += F("-moz-border-radius: 10px;");
 whitecontent += F("-webkit-border-radius: 10px;");
 whitecontent += F("border-radius: 10px;");
 whitecontent += F("border: 3px solid #000000;");
 whitecontent += F("-moz-box-shadow:");
 whitecontent += F("0px 1px 3px rgba(000,000,000,0.5),");
 whitecontent += F("inset 0px 0px 1px rgba(255,255,255,0.6);");
 whitecontent += F("-webkit-box-shadow:");
 whitecontent += F("0px 1px 3px rgba(000,000,000,0.5),");
 whitecontent += F("inset 0px 0px 1px rgba(255,255,255,0.6);");
 whitecontent += F("box-shadow:");
 whitecontent += F("0px 1px 3px rgba(000,000,000,0.5),");
 whitecontent += F("inset 0px 0px 1px rgba(255,255,255,0.6);");
 whitecontent += F("text-shadow:");
 whitecontent += F("0px -1px 0px rgba(000,000,000,1),");
 whitecontent += F("0px 1px 0px rgba(255,255,255,0.2);");
 whitecontent += F("}");

 // Text color definitions for heat letters
 whitecontent += F("a: {color: rgb(0,0,0);}");
 whitecontent += F("h1 {color: rgb(0,0,0);}");
 whitecontent += F("h2 {color: rgb(0,0,0);}");
 whitecontent += F("h3 {color: rgb(0,0,0);}");
 whitecontent += F("h4 {color: rgb(0,0,0);}");
 whitecontent += F("h5 {color: rgb(0,0,0);}");
 whitecontent += F("h6 {color: rgb(0,0,0);}");
 whitecontent += F("h7 {color: rgb(0,0,0);}");
 
 // General text definitions
 whitecontent += F("body {");
 whitecontent += F("color: rgb(100,100,100);");
 whitecontent += F("font-family: arial;");
 whitecontent += F("}");

 // Blinking text definition
 whitecontent += F("blink {");
 whitecontent += F("animation: blinker 0.6s linear infinite;");
 whitecontent += F("}");
 whitecontent += F("@keyframes blinker {");
 whitecontent += F("50% { opacity: 0; }");
 whitecontent += F("}");
 
 // Background definitions
 whitecontent += F("body {");
 whitecontent += F("background-color: rgb(255, 255, 255);");
// whitecontent += F("  background-color: rgb(0, 0, 0);");
 whitecontent += F("background-image: linear-gradient(to right, rgba(0,0,0,0), rgba(0,0,0,0.4));");
// whitecontent += F("  background-image: url('https://www.transparenttextures.com/patterns/knitted-netting.png');"); 
 whitecontent += F("}");

 // SVG line colors
 whitecontent += F("svg {");
 whitecontent += F("stroke: #404040;");
 whitecontent += F("}");

 // Style activation
 switch (style) {
  case 0:
    // Night style red
    content = redcontent;
    break;
  case 1:
    // Day style black
    content = blackcontent;
    break;
  case 2:
    // Day style white
    content = whitecontent;
    break;  
  default:
    // Day style white
    content = whitecontent;
}
 
 return content;
}
