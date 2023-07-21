String JSON2()
{
    DebugPrintln(3, "Send json2.html");
    
    // Seting variables
    int i = 0;
    String sensor1 = "";
    String sensor2 = "";
    
    // Read data arryas
    for(i = 0; i < 1000; i++){
      if(i > 0){
        sensor1 += ",";
      }
      sensor1 += String(boolToInt(sensor1TimeArray[i]));
      if(i > 0){
        sensor2 += ",";
      }
      sensor2 += String(boolToInt(sensor2TimeArray[i])); 
    }
    
    // Page content
    String content = "";

    // Build content if Server Mode = 3
    if(actconf.serverMode == 3 && scounter == 10000){
      content +=F(  "{");
      
        content +=F( "\"ConnectionQuality\": {");
        content +=F( "\"Value\": ");
        content += String(quality);
        content +=F( ",");
        content +=F( "\"Unit\": \"%\"");
        content +=F( "},");
  
        content +=F( "\"Speed\": {");
        content +=F( "\"Value\": ");
        content += String(windspeed_mps);
        content +=F( ",");
        content +=F( "\"Unit\": \"mps\"");
        content +=F( "},");
  
        content +=F( "\"Direction\": {");
        content +=F( "\"Value\": ");
        content += String(rawwinddirection);
        content +=F( ",");
        content +=F( "\"Unit\": \"°\"");
        content +=F( "},");
  
        content +=F(  "\"Sensor1\": {");
        
          content +=F( "\"Length\": {");
          content +=F( "\"Value\": 200,");
          content +=F( "\"Unit\": \"n\"");
          content +=F( "},");
    
          content +=F( "\"Time1\": {");
          content +=F( "\"Value\": ");
          content += String(time1);
          content +=F( ",");
          content +=F( "\"Unit\": \"ms\"");
          content +=F( "},");
    
          content +=F( "\"Data\": {");
          content +=F( "\"Value\": [");
          content += String(sensor1);
          content +=F( "],");
          content +=F( "\"Unit\": \"bin\"");
          content +=F( "}");
        
        content +=F( "},");
  
        content +=F(  "\"Sensor2\": {");
        
          content +=F( "\"Length\": {");
          content +=F( "\"Value\": 200,");
          content +=F( "\"Unit\": \"n\"");
          content +=F( "},");
    
          content +=F( "\"Time2\": {");
          content +=F( "\"Value\": ");
          content += String(time2);
          content +=F( ",");
          content +=F( "\"Unit\": \"ms\"");
          content +=F( "},");
  
          content +=F( "\"PulseCounter\": {");
          content +=F( "\"Value\": ");
          content += String(pcounter);
          content +=F( ",");
          content +=F( "\"Unit\": \"n\"");
          content +=F( "},");
    
          content +=F( "\"Data\": {");
          content +=F( "\"Value\": [");
          content += String(sensor2);
          content +=F( "],");
          content +=F( "\"Unit\": \"bin\"");
          content +=F( "}");
        
        content +=F( "}");
    
      content +=F(  "}");
    }
    else{
      content +=F(  "{");
      content +=F(  "\"Status\":\"No Data\"");
      content +=F(  "}");
    }

    // Reset marker3 and scounter for new data collecting (Hall sensors)
    if(scounter == 10000){
      scounter = 0;       // Reset the data saving counter
      marker3 = 0;        // Stop data saving of Hall sensor data
    }

    return content;
}
