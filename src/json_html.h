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
        
    // Page content (readable template with placeholder replacement)
    static const char kJsonTemplate[] PROGMEM = R"json(
{
  "Device": {
    "Type": "<<DEVNAME>>",
    "CopyRights": "<<CRIGHTS>>",
    "FirmwareVersion": "<<FVERSION>>",
    "License": "<<LICENSE>>",

    "ESP8266": {
      "SDKVersion": "<<SDK_VERSION>>",
      "ChipID": <<CHIP_ID>>,
      "CPUSpeed": { "Value": <<CPU_SPEED>>, "Unit": "MHz" },
      "FreeHeapSize": { "Value": <<FREE_HEAP>>, "Unit": "Byte" }
    },

    "NetworkParameter": {
      "WLANClientSSID": "<<WLAN_CLIENT_SSID>>",
      "WLANClientIP": "<<WLAN_CLIENT_IP>>",
      "FieldStrength": { "Value": <<FIELD_STRENGTH>>, "Unit": "dBm" },
      "ConnectionQuality": { "Value": <<CONNECTION_QUALITY>>, "Unit": "%" },
      "WLANServerSSID": "<<WLAN_SERVER_SSID>>",
      "WLANServerIP": "<<WLAN_SERVER_IP>>",
      "ServerMode": <<SERVER_MODE>>,
      "ServerHostName": "<<SERVER_HOSTNAME>>"
    },

    "DisplaySettings": {
      "Skin": <<SKIN>>,
      "InstrumentType": "<<INSTRUMENT_TYPE>>",
      "InstrumentSize": "<<INSTRUMENT_SIZE>>"
    },

    "DeviceSettings": {
      "SerialDebugMode": <<SERIAL_DEBUG_MODE>>,
      "SerialSpeed": <<SERIAL_SPEED>>,
      "SensorID": <<SENSOR_ID>>,
      "SensorType": "<<SENSOR_TYPE>>",
      "SendWindData": <<SEND_WIND_DATA>>,
      "WindType": "<<WIND_TYPE>>",
      "Average": <<AVERAGE>>,
      "SpeedUnit": "<<SPEED_UNIT>>",
      "DownWindSensor": <<DOWNWIND_SENSOR>>,
      "DownWindRange": <<DOWNWIND_RANGE>>,
      "TempSensorType": "<<TEMP_SENSOR_TYPE>>",
      "TempSensorData": <<TEMP_SENSOR_DATA>>,
      "TempUnit": "°<<TEMP_UNIT>>"
    },

    "MeasuringValues": {
      "DeviceTemperature": { "Value": <<DEVICE_TEMP>>, "Unit": "°<<TEMP_UNIT>>" },
      "WindDirection": { "Value": <<WIND_DIR>>, "Unit": "°" },
      "Resolution": { "Value": <<DIR_RESOLUTION>>, "Unit": "°" },
      "WindSpeed": { "Value": <<WIND_SPEED>>, "Unit": "<<SPEED_UNIT>>" },
      "DownWindSpeed": { "Value": <<DOWNWIND_SPEED>>, "Unit": "<<SPEED_UNIT>>" },
      "Sensor1": { "Value": <<SENSOR1>>, "Unit": "bin" },
      "Sensor2": { "Value": <<SENSOR2>>, "Unit": "bin" },
      "MagFluxDensity": { "Value": <<MAG_FLUX_DENSITY>>, "Unit": "mT" },
      "MagnetSensor": { "Value": <<MAGNET_SENSOR>>, "Unit": "°" },
      "PulseCounter": { "Value": <<PULSE_COUNTER>>, "Unit": "n" },
      "Time1": { "Value": <<TIME1>>, "Unit": "ms" },
      "Time2": { "Value": <<TIME2>>, "Unit": "ms" },
      "RotationSpeed": { "Value": <<ROTATION_SPEED>>, "Unit": "rps" },
      "AirTemperature": { "Value": <<AIR_TEMP>>, "Unit": "°<<TEMP_UNIT>>" },
      "AirPressure": { "Value": <<AIR_PRESSURE>>, "Unit": "mbar" },
      "AirHumidity": { "Value": <<AIR_HUMIDITY>>, "Unit": "%" },
      "Dewpoint": { "Value": <<DEWPOINT>>, "Unit": "°<<TEMP_UNIT>>" },
      "Altitude": { "Value": <<ALTITUDE>>, "Unit": "m" }
    },

    "NMEAValues": {
      "String1": "<<NMEA_STRING1>>",
      "String2": "<<NMEA_STRING2>>",
      "String3": "<<NMEA_STRING3>>",
      "String4": "<<NMEA_STRING4>>",
      "String5": "<<NMEA_STRING5>>"
    }
  }
}
)json";

    String content = FPSTR(kJsonTemplate);
    content.replace("<<DEVNAME>>", actconf.devname);
    content.replace("<<CRIGHTS>>", actconf.crights);
    content.replace("<<FVERSION>>", actconf.fversion);
    content.replace("<<LICENSE>>", actconf.license);
    content.replace("<<SDK_VERSION>>", ESP.getSdkVersion());
    content.replace("<<CHIP_ID>>", String(ESP.getChipId()));
    content.replace("<<CPU_SPEED>>", String(ESP.getCpuFreqMHz()));
    content.replace("<<FREE_HEAP>>", String(ESP.getFreeHeap()));
    content.replace("<<WLAN_CLIENT_SSID>>", actconf.cssid);
    content.replace("<<WLAN_CLIENT_IP>>", WiFi.localIP().toString());
    content.replace("<<FIELD_STRENGTH>>", String(fieldstrength));
    content.replace("<<CONNECTION_QUALITY>>", String(quality));
    content.replace("<<WLAN_SERVER_SSID>>", actconf.sssid);
    content.replace("<<WLAN_SERVER_IP>>", WiFi.softAPIP().toString());
    content.replace("<<SERVER_MODE>>", String(actconf.serverMode));
    content.replace("<<SERVER_HOSTNAME>>", actconf.hostname);
    content.replace("<<SKIN>>", String(actconf.skin));
    content.replace("<<INSTRUMENT_TYPE>>", actconf.instrumentType);
    content.replace("<<INSTRUMENT_SIZE>>", String(actconf.instrumentSize));
    content.replace("<<SERIAL_DEBUG_MODE>>", String(actconf.serverMode));
    content.replace("<<SERIAL_SPEED>>", String(actconf.serspeed));
    content.replace("<<SENSOR_ID>>", String(actconf.sensorID));
    content.replace("<<SENSOR_TYPE>>", actconf.windSensorType);
    content.replace("<<SEND_WIND_DATA>>", String(actconf.windSensor));
    content.replace("<<WIND_TYPE>>", actconf.windType);
    content.replace("<<AVERAGE>>", String(actconf.average));
    content.replace("<<SPEED_UNIT>>", actconf.speedUnit);
    content.replace("<<DOWNWIND_SENSOR>>", String(actconf.downWindSensor));
    content.replace("<<DOWNWIND_RANGE>>", String(actconf.downWindRange));
    content.replace("<<TEMP_SENSOR_TYPE>>", actconf.tempSensorType);
    content.replace("<<TEMP_SENSOR_DATA>>", String(actconf.tempSensor));
    content.replace("<<TEMP_UNIT>>", actconf.tempUnit);
    content.replace("<<DEVICE_TEMP>>", String(temperature));
    content.replace("<<WIND_DIR>>", String(winddirection));
    content.replace("<<DIR_RESOLUTION>>", String(dirresolution));
    content.replace("<<WIND_SPEED>>", String(windspeed));
    content.replace("<<DOWNWIND_SPEED>>", String(dwspeed));
    content.replace("<<SENSOR1>>", String(sensor1));
    content.replace("<<SENSOR2>>", String(sensor2));
    content.replace("<<MAG_FLUX_DENSITY>>", String(magnitude));
    content.replace("<<MAGNET_SENSOR>>", String(magsensor));
    content.replace("<<PULSE_COUNTER>>", String(pcounter));
    content.replace("<<TIME1>>", String(time1));
    content.replace("<<TIME2>>", String(time2));
    content.replace("<<ROTATION_SPEED>>", String(windspeed_hz));
    content.replace("<<AIR_TEMP>>", String(airtemperature));
    content.replace("<<AIR_PRESSURE>>", String(airpressure));
    content.replace("<<AIR_HUMIDITY>>", String(airhumidity));
    content.replace("<<DEWPOINT>>", String(dewpoint));
    content.replace("<<ALTITUDE>>", String(altitude));
    content.replace("<<NMEA_STRING1>>", sendMWV(0));
    content.replace("<<NMEA_STRING2>>", sendVWR(0));
    content.replace("<<NMEA_STRING3>>", sendVPW(0));
    content.replace("<<NMEA_STRING4>>", sendINF(0));
    content.replace("<<NMEA_STRING5>>", sendWST(0));
    
    return content;
}
