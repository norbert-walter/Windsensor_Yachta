String Icon()
{
 // Debug info 
 DebugPrintln(3, "Send favicon.ico");

 String content; 
 // Favorit icon as SVG/XML file
 content +=F( "<svg width='100' height='100' xmlns='http://www.w3.org/2000/svg'><g>");
 content +=F( "<ellipse ry='30' rx='30' id='svg_1' cy='50' cx='50' stroke-width='10' stroke='#000' fill='#fff'/>");
 content +=F( "<line id='svg_2' y2='50' x2='50' y1='28.8' x1='71.2' stroke-width='10' stroke='#000' fill='none'/>");
 content +=F( "</g></svg>");
  
 return content;
}
