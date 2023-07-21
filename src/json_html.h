String JSON()
{
    DebugPrintln(3, "Send json.html");

    // Read the digital signals from Hall sensors
    sensor1 = boolToInt(digitalRead(INT_PIN1));    // Hall sensor for wind speed
    sensor2 = boolToInt(digitalRead(INT_PIN2));    // Hall sensor for wind direction
    
    // Calculation of wind speed and wind direction see main loop.
    // The main loop calculate the data all 1s.
    // This limited the data rate

    // Wind speed value for Web interface depends on unit
    windspeed = windspeed_mps;
    if (String(actconf.speedUnit) == "km/h") {
       windspeed = windspeed_kph;
     }
     if (String(actconf.speedUnit) == "kn") {
       windspeed = windspeed_kn;
     }
     if (String(actconf.speedUnit) == "bft") {
       windspeed = windspeed_bft;
     }
     if ((winddirection > (180 - actconf.downWindRange)) && (winddirection < (actconf.downWindRange + 180))){
      dwspeed = windspeed;
     }
     else{
      dwspeed = 0;
     }
        
    // Page content
    String content = "";
    content +=F(  "{");
    content +=F( "\"Device\": {");
    content +=F( "\"Type\": \"");
    content += String(actconf.devname);
    content +=F( "\",");
    content +=F( "\"CopyRights\": \"");
    content += String(actconf.crights);
    content +=F( "\",");
    content +=F( "\"FirmwareVersion\": \"");
    content += String(actconf.fversion);
    content +=F( "\",");
    content +=F( "\"License\": \"");
    content += String(actconf.license);
    content +=F( "\",");
    content +=F( "\"ESP8266\": {");
    content +=F( "\"SDKVersion\": \"");
    content += String(ESP.getSdkVersion());
    content +=F( "\",");
    content +=F( "\"ChipID\": ");
    content += String(ESP.getChipId());
    content +=F( ",");
    content +=F( "\"CPUSpeed\": {");
    content +=F( "\"Value\": ");
    content += String(ESP.getCpuFreqMHz());
    content +=F( ",");
    content +=F( "\"Unit\": \"MHz\"");
    content +=F( "},");
    content +=F( "\"FreeHeapSize\": {");
    content +=F( "\"Value\": ");
    content += String(ESP.getFreeHeap());
    content +=F( ",");
    content +=F( "\"Unit\": \"Byte\"");
    content +=F( "}");
    content +=F( "},");
    content +=F( "\"NetworkParameter\": {");
    content +=F( "\"WLANClientSSID\": \"");
    content += String(actconf.cssid);
    content +=F( "\",");
    content +=F( "\"WLANClientIP\": \"");
    content += WiFi.localIP().toString();
    content +=F( "\",");

    content +=F( "\"FieldStrength\": {");
    content +=F( "\"Value\": ");
    content += String(fieldstrength);
    content +=F( ",");
    content +=F( "\"Unit\": \"dBm\"");
    content +=F( "},");
    content +=F( "\"ConnectionQuality\": {");
    content +=F( "\"Value\": ");
    content += String(quality);
    content +=F( ",");
    content +=F( "\"Unit\": \"%\"");
    content +=F( "},");
    
    content +=F( "\"WLANServerSSID\": \"");
    content += String(actconf.sssid);
    content +=F( "\",");
    content +=F( "\"WLANServerIP\": \"");
    content += WiFi.softAPIP().toString();
    content +=F( "\",");
    content +=F( "\"ServerMode\": ");
    content += String(actconf.serverMode);
    content +=F( ",");
    content +=F( "\"ServerHostName\": \"");
    content += String(actconf.hostname);
    content +=F( "\"");
    content +=F( "},");
    content +=F( "\"DisplaySettings\": {");
    content +=F( "\"Skin\": ");
    content += String(actconf.skin);
    content +=F( ",");
    content +=F( "\"InstrumentType\": \"");
    content += String(actconf.instrumentType);
    content +=F( "\",");
    content +=F( "\"InstrumentSize\": \"");
    content += String(actconf.instrumentSize);
    content +=F( "\"");
    content +=F( "},");
    content +=F( "\"DeviceSettings\": {");
    content +=F( "\"SerialDebugMode\": ");
    content += String(actconf.serverMode);
    content +=F( ",");
    content +=F( "\"SerialSpeed\": ");
    content += String(actconf.serspeed);
    content +=F( ",");
    content +=F( "\"SensorID\": ");
    content += String(actconf.sensorID);
    content +=F( ",");
    content +=F( "\"SensorType\": \"");
    content += String(actconf.windSensorType);
    content +=F( "\",");
    content +=F( "\"SendWindData\": ");
    content += String(actconf.windSensor);
    content +=F( ",");
    content +=F( "\"WindType\": \"");
    content += String(actconf.windType);
    content +=F( "\",");
    content +=F( "\"Average\": ");
    content += String(actconf.average);
    content +=F( ",");
    content +=F( "\"SpeedUnit\": \"");
    content += String(actconf.speedUnit);
    content +=F( "\",");
    content +=F( "\"DownWindSensor\": ");
    content += String(actconf.downWindSensor);
    content +=F( ",");
    content +=F( "\"DownWindRange\": ");
    content += String(actconf.downWindRange);
    content +=F( ",");
    content +=F( "\"TempSensorType\": \"");
    content += String(actconf.tempSensorType);
    content +=F( "\",");
    content +=F( "\"TempSensorData\": ");
    content += String(actconf.tempSensor);
    content +=F( ",");
    content +=F( "\"TempUnit\": \"°");
    content += String(actconf.tempUnit);
    content +=F( "\"");
    content +=F( "},");
    content +=F( "\"MeasuringValues\": {");
    content +=F( "\"DeviceTemperature\": {");
    content +=F( "\"Value\": ");
    content += String(temperature);
    content +=F( ",");
    content +=F( "\"Unit\": \"°");
    content += String(actconf.tempUnit);
    content +=F( "\"");
    content +=F( "},");
    content +=F( "\"WindDirection\": {");
    content +=F( "\"Value\": ");
    content += String(winddirection);
    content +=F( ",");
    content +=F( "\"Unit\": \"°\"");
    content +=F( "},");
    content +=F( "\"Resolution\": {");
    content +=F( "\"Value\": ");
    content += String(dirresolution);
    content +=F( ",");
    content +=F( "\"Unit\": \"°\"");
    content +=F( "},");
    content +=F( "\"WindSpeed\": {");
    content +=F( "\"Value\": ");
    content += String(windspeed);
    content +=F( ",");
    content +=F( "\"Unit\": \"");
    content += String(actconf.speedUnit);
    content +=F( "\"");
    content +=F( "},");
    content +=F( "\"DownWindSpeed\": {");
    content +=F( "\"Value\": ");
    content += String(dwspeed);
    content +=F( ",");
    content +=F( "\"Unit\": \"");
    content += String(actconf.speedUnit);
    content +=F( "\"");
    content +=F( "},");
    content +=F( "\"Sensor1\": {");
    content +=F( "\"Value\": ");
    content += String(sensor1);
    content +=F( ",");
    content +=F( "\"Unit\": \"bin\"");
    content +=F( "},");
    content +=F( "\"Sensor2\": {");
    content +=F( "\"Value\": ");
    content += String(sensor2);
    content +=F( ",");
    content +=F( "\"Unit\": \"bin\"");
    content +=F( "},");

    content +=F( "\"MagFluxDensity\": {");
    content +=F( "\"Value\": ");
    content += String(magnitude);
    content +=F( ",");
    content +=F( "\"Unit\": \"mT\"");
    content +=F( "},");  
    content +=F( "\"MagnetSensor\": {");
    content +=F( "\"Value\": ");
    content += String(magsensor);
    content +=F( ",");
    content +=F( "\"Unit\": \"°\"");
    content +=F( "},");
    
    content +=F( "\"PulseCounter\": {");
    content +=F( "\"Value\": ");
    content += String(pcounter);
    content +=F( ",");
    content +=F( "\"Unit\": \"n\"");
    content +=F( "},");
       
    content +=F( "\"Time1\": {");
    content +=F( "\"Value\": ");
    content += String(time1);
    content +=F( ",");
    content +=F( "\"Unit\": \"ms\"");
    content +=F( "},");
    
    content +=F( "\"Time2\": {");
    content +=F( "\"Value\": ");
    content += String(time2);
    content +=F( ",");
    content +=F( "\"Unit\": \"ms\"");
    content +=F( "},");
    
    content +=F( "\"RotationSpeed\": {");
    content +=F( "\"Value\": ");
    content += String(windspeed_hz);
    content +=F( ",");
    content +=F( "\"Unit\": \"rps\"");
    content +=F( "},");

    content +=F( "\"AirTemperature\": {");
    content +=F( "\"Value\": ");
    content += String(airtemperature);
    content +=F( ",");
    content +=F( "\"Unit\": \"°");
    content += String(actconf.tempUnit);
    content +=F( "\"");
    content +=F( "},");

    content +=F( "\"AirPressure\": {");
    content +=F( "\"Value\": ");
    content += String(airpressure);
    content +=F( ",");
    content +=F( "\"Unit\": \"mbar\"");
    content +=F( "},");

    content +=F( "\"AirHumidity\": {");
    content +=F( "\"Value\": ");
    content += String(airhumidity);
    content +=F( ",");
    content +=F( "\"Unit\": \"%\"");
    content +=F( "},");

    content +=F( "\"Dewpoint\": {");
    content +=F( "\"Value\": ");
    content += String(dewpoint);
    content +=F( ",");
    content +=F( "\"Unit\": \"°");
    content += String(actconf.tempUnit);
    content +=F( "\"");
    content +=F( "},");

    content +=F( "\"Altitude\": {");
    content +=F( "\"Value\": ");
    content += String(altitude);
    content +=F( ",");
    content +=F( "\"Unit\": \"m\"");
    content +=F( "}");
    
    content +=F( "},");
    content +=F( "\"NMEAValues\": {");
    content +=F( "\"String1\": \"");
    content += sendMWV(0);
    content +=F( "\",");
    content +=F( "\"String2\": \"");
    content += sendVWR(0);
    content +=F( "\",");
    content +=F( "\"String3\": \"");
    content += sendVPW(0);
    content +=F( "\",");
    content +=F( "\"String4\": \"");
    content += sendINF(0);
    content +=F( "\",");
    content +=F( "\"String5\": \"");
    content += sendWST(0);
    content +=F( "\"");
    content +=F( "}");
    content +=F( "}");
    content +=F( "}");
    
    return content;
}
