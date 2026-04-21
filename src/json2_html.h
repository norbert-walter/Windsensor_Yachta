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
    
    // Page content (readable template with placeholder replacement)
    static const char kJson2DataTemplate[] PROGMEM = R"json(
{
  "ConnectionQuality": {"Value": <<CONNECTION_QUALITY>>, "Unit": "%"},
  "Speed": {"Value": <<SPEED_MPS>>, "Unit": "mps"},
  "Direction": {"Value": <<RAW_WIND_DIR>>, "Unit": "°"},
  "Sensor1": {
    "Length": {"Value": 200, "Unit": "n"},
    "Time1": {"Value": <<TIME1>>, "Unit": "ms"},
    "Data": {"Value": [<<SENSOR1_DATA>>], "Unit": "bin"}
  },
  "Sensor2": {
    "Length": {"Value": 200, "Unit": "n"},
    "Time2": {"Value": <<TIME2>>, "Unit": "ms"},
    "PulseCounter": {"Value": <<PULSE_COUNTER>>, "Unit": "n"},
    "Data": {"Value": [<<SENSOR2_DATA>>], "Unit": "bin"}
  }
}
)json";

    static const char kJson2NoDataTemplate[] PROGMEM = R"json(
{
  "Status": "No Data"
}
)json";

    String content = "";

    // Build content if Server Mode = 3
    if(actconf.serverMode == 3 && scounter == 10000){
      content = FPSTR(kJson2DataTemplate);
      content.replace("<<CONNECTION_QUALITY>>", String(quality));
      content.replace("<<SPEED_MPS>>", String(windspeed_mps));
      content.replace("<<RAW_WIND_DIR>>", String(rawwinddirection));
      content.replace("<<TIME1>>", String(time1));
      content.replace("<<SENSOR1_DATA>>", sensor1);
      content.replace("<<TIME2>>", String(time2));
      content.replace("<<PULSE_COUNTER>>", String(pcounter));
      content.replace("<<SENSOR2_DATA>>", sensor2);
    }
    else{
      content = FPSTR(kJson2NoDataTemplate);
    }

    // Reset marker3 and scounter for new data collecting (Hall sensors)
    if(scounter == 10000){
      scounter = 0;       // Reset the data saving counter
      marker3 = 0;        // Stop data saving of Hall sensor data
    }

    return content;
}
