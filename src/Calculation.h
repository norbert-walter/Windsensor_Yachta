// Calculations of wind speed and wind direction
// Data are defined as global data

// Round float to int
int roundFloat2Int(float x)
{
  if(x>0) return (int)(x + 0.5);
  return (int)(x - 0.5);
}

// Convert °C to °F
float convertCtoF(float value){
 float fahrenheit = (value * 9 / 5) + 32;
 return fahrenheit;
}

// Dewpoint calculation
// Refer: https://de.wikipedia.org/wiki/Taupunkt
float dewp(float temp, float humidity) {
//  float K1 = 6.112;   // [hPa]
  float K2 = 17.62;   // [1]
  float K3 = 243.12;  // [°C]
  float term1 = (K2 * temp) / (K3 + temp);
  float term2 = (K2 * K3) / (K3 + temp);
  float term3 = log(humidity / 100);                  // Humidiy range 0...1
  float dewp = K3 *((term1 + term3)/(term2 - term3));
  return dewp;
}

void calculationData(){
  // Atomic Block (not interruptible)
  ATOMIC(){
    // Is connected with extern WLAN network
    if(WiFi.localIP().toString() != "0.0.0.0"){
      fieldstrength = float(WiFi.RSSI());
      if(fieldstrength > 0){
        fieldstrength = -100.0;
      }
      quality = 100  - (((fieldstrength * -1) - 50) * 2);
      if(quality < 0){
        quality = 0;
      }
      if(quality > 100){
        quality = 100;
      }
    }
    else{
      fieldstrength = 0;
      quality = 0;
    }

    // Read device temperature 1Wire DS18B20
    if(String(actconf.tempSensorType) == "DS18B20"){
      DS18B20.requestTemperatures();
      if(String(actconf.tempUnit) == "C"){
        temperature = float(DS18B20.getTempCByIndex(0));
      }
      else{
        temperature = float(DS18B20.getTempFByIndex(0));
      }
    }

    // time1 = time in [ms] for one rotation
    // time2 = time in [ms] between wind speed sensor and wind direction sensor
    if(time1_avg == 0){
      time1_avg = 0.1;
    }

    // Calculate wind direction for WiFi1000 wind sensor
    if(String(actconf.windSensorType) == "WiFi 1000"){
      // Calculate only wind direction when time values ok
      if(time1_avg < 1000 && time2_avg < 1000){
        // Raw wind direction 0...360°, dir[°] = time2[ms] / time1[ms] *360
        rawwinddirection = time2_avg / time1_avg * 360;
      }
      magnitude = 0; // Set values for AS5600
      magsensor = 0;
    }
    
    // Calculate wind direction for Yachta, Jukolein and Ventus wind sensor
    if(String(actconf.windSensorType) == "Yachta" || String(actconf.windSensorType) == "Jukolein"){
      // Read only magnetic values if the I2C device is ready
      if(i2creadyAS5600 == 1){
        magnitude = ams5600.getMagnitude();
        magsensor = ams5600.getRawAngle() * 0.087; // 0...4096 which is 0.087 of a degree
        // Limiting values outer range
        if(magsensor < 0){
          magsensor = 0;
        }
        if(magsensor > 360){
          magsensor = 360;
        }
      }
      else{
        magnitude = 0;
        magsensor = 0;
      }
      rawwinddirection = magsensor;
    }

    // Calculate wind direction for Yachta 2.0 (Attention! Inverse rotation because the MT6701 measure counter clock)
    if(String(actconf.windSensorType) == "Yachta 2.0"){
      // Read only magnetic values if the I2C device is ready
      if(i2creadyMT6701 == 1){
        magnitude = mt6701.getRawAngle();     // 0...16384 which is 0.0219 of a degree
        magsensor = 360 - mt6701.getDegreesAngle(); // value in degree
        // Limiting values outer range
        if(magsensor < 0){
          magsensor = 0;
        }
        if(magsensor > 360){
          magsensor = 360;
        }
      }
      else{
        magnitude = 0;
        magsensor = 0;
      }
      rawwinddirection = magsensor;
    }

    // Calculate wind direction for Ventus wind sensor (Attention! Inverse rotation because the AS5600 measure on bottom side)
    if(String(actconf.windSensorType) == "Ventus"){
      // Read only magnetic values if the I2C device is ready
      if(i2creadyAS5600 == 1){
        magnitude = ams5600.getMagnitude();
        magsensor = 360 - ams5600.getRawAngle() * 0.087; // 0...4096 which is 0.087 of a degree
        // Limiting values outer range
        if(magsensor < 0){
          magsensor = 0;
        }
        if(magsensor > 360){
          magsensor = 360;
        }
      }
      else{
        magnitude = 0;
        magsensor = 0;
      }
      rawwinddirection = magsensor;
      
      if(i2creadyBME280 == 1 && String(actconf.tempSensorType) == "BME280"){
        if(String(actconf.tempUnit) == "C"){
          airtemperature = bme.readTemperature();
        }
        else{
          airtemperature = convertCtoF(bme.readTemperature());
        }
        airpressure = bme.readPressure() / 100;
        airhumidity = bme.readHumidity();
        dewpoint = dewp(airtemperature, airhumidity);
        altitude = bme.readAltitude(SEALEVELPRESSURE_HPA);
      }
      else{
        airtemperature = 0;
        airpressure = 0;
        airhumidity = 0;
        dewpoint = 0;
        altitude = 0;
      }
      rawwinddirection = magsensor;
      
    }
    
    // Wind direction with offset
    if((rawwinddirection + actconf.offset) >= 0 && (rawwinddirection + actconf.offset) <= 360){
      winddirection = rawwinddirection + actconf.offset;
    }
    if((rawwinddirection + actconf.offset) > 360){
      winddirection = rawwinddirection + actconf.offset - 360;
    }
    if((rawwinddirection + actconf.offset) < 0){
      winddirection = 360 - (abs(actconf.offset) - rawwinddirection);
    }
    
    // Limiting max deviations between two measuring values of wind direction
    if(abs(winddirection - winddirection_old) > maxwinddirdev && winddirection > maxwinddirdev && winddirection < 360 -maxwinddirdev){
      if(winddirection - winddirection_old > 0){
        winddirection = winddirection_old + maxwinddirdev;
      }
      else{
        winddirection = winddirection_old - maxwinddirdev;
      }
    }
    winddirection_old = winddirection;
    
    // Wind direction 0...180° for each boat side
    if(winddirection >= 0 && winddirection <= 180){
      winddirection2 = winddirection;
    }
    else{
      winddirection2 = 360 - winddirection;
    }
    // Calculate wind direction resolution for NoRa1000 wind sensor
    if(String(actconf.windSensorType) == "WiFi 1000"){
      // Wind direction resolution res[°] = 360 / time1
      dirresolution = 360 / (time1 * 10);  // now 100us counter
      if(dirresolution > 20.0){
        dirresolution = 0.0;
      }
    }
    // Calculate wind direction resolution for Yachta and Jukolein wind sensor
    if(String(actconf.windSensorType) == "Yachta" || String(actconf.windSensorType) == "Jukolein" || String(actconf.windSensorType) == "Ventus"){
      dirresolution = 0.087;
    }
    // Calculate wind direction resolution for Yachta 2.0 wind sensor
    if(String(actconf.windSensorType) == "Yachta 2.0"){
      dirresolution = 0.0219;
    }
    // Calculate only wind speed when time values ok
    if(time1_avg < 1000 && time2_avg < 1000){
      if(String(actconf.windSensorType) == "WiFi 1000" || String(actconf.windSensorType) == "Ventus"){
        // Wind speed n[Hz] = 1 / time1[ms] *1000  // 1 pulse per round
        windspeed_hz = 1.0 / time1_avg * 1000;
      }
      if(String(actconf.windSensorType) == "Yachta" || String(actconf.windSensorType) == "Jukolein"){
        // Wind speed n[Hz] = 1 / time1[ms] *1000 / 2
        windspeed_hz = 1.0 / time1_avg * 1000 / 2; // 2 pulses per round
      }
    }

    // Eleminate the big start value direct after wind sensor start
    if(windspeed_hz > 100){
      windspeed_hz = 0;
    }

    // If zero wind speed the set wind speed to 0 Hz
    // Controlled via Timer4 routine
    if(flag3 == true){
       windspeed_hz = 0.0;
    }

    if(String(actconf.windSensorType) == "WiFi 1000"){
      // Wind speed, v[m/s] = (2 * Pi * n[Hz] * r[m]) / lamda[1]
      windspeed_mps = (2 * pi * windspeed_hz * radius) / lamda;
    }
    if(String(actconf.windSensorType) == "Yachta" || String(actconf.windSensorType) == "Jukolein"){
      // Wind speed, v[m/s] = (2 * Pi * n[Hz] * r[m]) / lamda[1]
      windspeed_mps = (2 * pi * windspeed_hz * radius2) / lamda;
    }
    if(String(actconf.windSensorType) == "Ventus"){
      // Wind speed, v[m/s] = (2 * Pi * n[Hz] * r[m]) / lamda[1]
      windspeed_mps = (2 * pi * windspeed_hz * radius3) / lamda;
    }
    
    // Calibration of wind speed data
    windspeed_mps = windspeed_mps * actconf.calslope + actconf.caloffset;
    if(windspeed_mps < 0){
      windspeed_mps = 0;
    }

    // Wind speed, v[km/h] = v[m/s] * 3.6
    windspeed_kph = windspeed_mps * 3.6;
    // Wind speed, v[kn] = v[m/s] * 1.94384
    windspeed_kn = windspeed_mps * 1.94384;
    term3 = 0.0000222 * windspeed_kn;
    term3 *= windspeed_kn;
    term3 *= windspeed_kn;
    term2 = 0.0034132 * windspeed_kn;
    term2 *= windspeed_kn;
    term1 = 0.2981666 * windspeed_kn;
    // Wind speed v[bft] = 0.0000222 * v³[kn] - 0.0034132 * v²[kn] + 0.2981666 * v[kn] + 0.1467082
    windspeed_bft = roundFloat2Int(term3 - term2 + term1 + 0.1467082);
    // Limiting wind speed for bft lower than 12
    if(windspeed_bft > 12){
     windspeed_bft = 12;
    }
  }
}

void simulationData(){
  // Atomic Block (not interruptible)
  ATOMIC(){
    int i = 0;
    int speedmps;         // Actual calculated speed in [m/s]
    int winddir;          // Actual calculated wind direction in [°]
    int steps = 600;      // Number of steps for one pointer round
                          // Time for oune round is steps * 500ms
    
    fieldstrength = -100;    // No signal
     quality = 100  - (((fieldstrength * -1) - 50) * 2);
      
     if(String(actconf.tempUnit) == "C"){
      //Basis unit is °C
      temperature = float(random(210, 220)) / 10;
     }
     else{
      temperature = float(random(210, 220)) / 10;
      //(0 °C × 9/5) + 32 = 32 °F
      temperature = (temperature * 9 / 5) + 32;
     }
     sensor1 =  int(random(0, 2));
     sensor2 =  int(random(0, 2));

     magnitude = int(random(300, 450));
     magsensor = int(random(0, 360));

     airtemperature = float(random(210, 230)) / 10;
     airpressure = float(random(9000, 10100)) / 10;
     airhumidity = float(random(700, 800)) / 10;
     dewpoint = float(random(10, 150)) / 10;
     altitude = float(random(500, 560)) / 10;
     
//**************************************************************************

    // Calculate demo data in timearrays with random numbers for DEMO mode
    randomSeed(micros());
    for (i = 0; i < average; i++){
     // Calculate demo data for wind speed
     speedmps = ((demoSet % steps) * 38 / steps) + 1;
     // Add 40% noise
     speedmps += speedmps * 0.4 * float(random(0, 10)) / 10;
     // t1[ms] = (2 * Pi * 1000 * radius[m]) / (speed[m/s] * lamda)
     time1 = (2 * pi * 1000 * radius) / (speedmps * lamda);
     timearray1[i] = time1;
     // Calculate demo data for wind direction
     winddir = ((demoSet % steps) * 360 / steps);
     // Add 40% noise
     winddir += winddir * 0.4 * float(random(0, 10)) / 10;
     // t2[ms] = (t1 * winddir[°]) / 360°
     time2 = (timearray1[i] * winddir) / 360;
     timearray2[i] = time2;
    }
    demoSet ++;
    /*
    Serial.print("Ratio: ");
    Serial.print((timearray2[0]/timearray1[0]));
    Serial.print("   1: " );
    Serial.print(timearray1[0]);
    Serial.print("   2: " );
    Serial.println(timearray2[0]);
    */

//**************************************************************************

    // time1 = time in [ms] for one rotation
    // time2 = time in [ms] between wind speed sensor and wind direction sensor
    if(time1_avg == 0){
      time1_avg = 0.1;
    }

    // Calculate only wind direction when time values ok
    if(time1_avg < 1000 && time2_avg < 1000){
      // Raw wind direction 0...360°, dir[°] = time2[ms] / time1[ms] *360
      rawwinddirection = time2_avg / time1_avg * 360;
    }
    // Wind direction with offset
    if((rawwinddirection + actconf.offset) > 360){
      winddirection = rawwinddirection + actconf.offset - 360;
    }
    else{
      winddirection = rawwinddirection + actconf.offset;
    }
    
    // Wind direction 0...180° for each boat side
    if(winddirection >= 0 && winddirection <= 180){
      winddirection2 = winddirection;
    }
    else{
      winddirection2 = 360 - winddirection;
    }
    // Wind direction resolution res[°] = 360 / time1
    dirresolution = 360 / (time1 * 10);  // now 100us counter
    if(dirresolution > 20.0){
      dirresolution = 0.0;
    }
    // Calculate only wind speed when time values ok
    if(time1_avg < 1000 && time2_avg < 1000){
      // Wind speed n[Hz] = 1 / time1[ms] *1000
      windspeed_hz = 1.0 / time1_avg * 1000;
    }

    // Eleminate the big start value direct after wind sensor start
    if(windspeed_hz > 100){
      windspeed_hz = 0;
    }

    // Wind speed, v[m/s] = (2 * Pi * n[Hz] * r[m]) / lamda[1]
    windspeed_mps = (2 * pi * windspeed_hz * radius) / lamda;
    // Calibration of wind speed data
    windspeed_mps = windspeed_mps * actconf.calslope + actconf.caloffset;
    // Wind speed, v[km/h] = v[m/s] * 3.6
    windspeed_kph = windspeed_mps * 3.6;
    // Wind speed, v[kn] = v[m/s] * 1.94384
    windspeed_kn = windspeed_mps * 1.94384;
    term3 = 0.0000222 * windspeed_kn;
    term3 *= windspeed_kn;
    term3 *= windspeed_kn;
    term2 = 0.0034132 * windspeed_kn;
    term2 *= windspeed_kn;
    term1 = 0.2981666 * windspeed_kn;
    // Wind speed v[bft] = 0.0000222 * v³[kn] - 0.0034132 * v²[kn] + 0.2981666 * v[kn] + 0.1467082
    windspeed_bft = roundFloat2Int(term3 - term2 + term1 + 0.1467082);
    // Limiting wind speed for bft lower than 12
    if(windspeed_bft > 12){
     windspeed_bft = 12;
    }
  }
}
