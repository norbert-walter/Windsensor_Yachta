String JS()
{
 // Debug info 
 DebugPrintln(3, "Send js.html");

 String content;

 content +=F( "var xmlhttp = new XMLHttpRequest();");
 content +=F( "xmlhttp.onreadystatechange = function() {");
 content +=F( "if (this.readyState == 4 && this.status == 200) {");
 content +=F( "var myObj = JSON.parse(this.responseText);");
 
/* 
 content +=F( "document.getElementById('type').innerHTML = myObj.Device.Type;");
 content +=F( "document.getElementById('firmware').innerHTML = myObj.Device.FirmwareVersion;");
 content +=F( "document.getElementById('license').innerHTML = myObj.Device.License;");

 content +=F( "document.getElementById('sdkversion').innerHTML = myObj.Device.ESP8266.SDKVersion;");
 content +=F( "document.getElementById('chipid').innerHTML = myObj.Device.ESP8266.ChipID;");
 content +=F( "document.getElementById('cpuspeed').innerHTML = myObj.Device.ESP8266.CPUSpeed.Value;");
 content +=F( "document.getElementById('csunit').innerHTML = myObj.Device.ESP8266.CPUSpeed.Unit;");
 content +=F( "document.getElementById('freeheapsize').innerHTML = myObj.ESP8266.FreeHeapSize.Value;");
 content +=F( "document.getElementById('fhsunit').innerHTML = myObj.Device.ESP8266.FreeHeapSize.Unit;");

 content +=F( "document.getElementById('cssid').innerHTML = myObj.Device.NetworkParameter.WLANClientSSID;");
 content +=F( "document.getElementById('sssid').innerHTML = myObj.Device.NetworkParameter.WLANServerSSID;");
 content +=F( "document.getElementById('servermode').innerHTML = myObj.Device.NetworkParameter.ServerMode;");
 content +=F( "document.getElementById('skin').innerHTML = myObj.Device.DisplaySetings.Skin;");
 content +=F( "document.getElementById('itype').innerHTML = myObj.Device.DisplaySetings.InstrumentType;");
 content +=F( "document.getElementById('isize').innerHTML = myObj.Device.DisplaySetings.InstrumentSize;");

 content +=F( "document.getElementById('debugmode').innerHTML = myObj.Device.DeviceSetings.SerialDebugMode;");
 content +=F( "document.getElementById('serspeed').innerHTML = myObj.Device.DeviceSetings.SerialSpeed;");
 content +=F( "document.getElementById('sensorid').innerHTML = myObj.Device.DeviceSetings.SensorID;");
 content +=F( "document.getElementById('sensortype').innerHTML = myObj.Device.DeviceSetings.SensorType;");
 content +=F( "document.getElementById('sendwdata').innerHTML = myObj.Device.DeviceSetings.SendWindData;");
 content +=F( "document.getElementById('windtype').innerHTML = myObj.Device.DeviceSetings.WindType;");
 content +=F( "document.getElementById('average').innerHTML = myObj.Device.DeviceSetings.Average;"); 
 content +=F( "document.getElementById('speedunit').innerHTML = myObj.Device.DeviceSetings.SpeedUnit;");
 content +=F( "document.getElementById('senddwdata').innerHTML = myObj.Device.DeviceSetings.DownWindSensor;");
 content +=F( "document.getElementById('dwrange').innerHTML = myObj.Device.DeviceSetings.DownWindRange;");
 content +=F( "document.getElementById('tsensortype').innerHTML = myObj.Device.DeviceSetings.TempSensorType;");
 content +=F( "document.getElementById('sendtdata').innerHTML = myObj.Device.DeviceSetings.TempSensorData;");
 content +=F( "document.getElementById('tempunit').innerHTML = myObj.Device.DeviceSetings.TempUnit;");
*/
 content +=F( "cssid = document.getElementById('cssid');");
 content +=F( "cssid.value = myObj.Device.NetworkParameter.WLANClientSSID;");
 content +=F( "sssid = document.getElementById('sssid');");
 content +=F( "sssid.value = myObj.Device.NetworkParameter.WLANServerSSID;");
 
 content +=F( "heapsize = document.getElementById('heapsize');");
 content +=F( "heapsize.value = myObj.Device.ESP8266.FreeHeapSize.Value;");
 content +=F( "document.getElementById('hunit').innerHTML = myObj.Device.ESP8266.FreeHeapSize.Unit;");

 content +=F( "strength = document.getElementById('strength');");
 content +=F( "strength.value = myObj.Device.NetworkParameter.FieldStrength.Value;");
 content +=F( "document.getElementById('sunit').innerHTML = myObj.Device.NetworkParameter.FieldStrength.Unit;");
 content +=F( "quality = document.getElementById('quality');");
 content +=F( "quality.value = myObj.Device.NetworkParameter.ConnectionQuality.Value;");
 content +=F( "document.getElementById('qunit').innerHTML = myObj.Device.NetworkParameter.ConnectionQuality.Unit;");
 content +=F( "document.getElementById('quality2').innerHTML = myObj.Device.NetworkParameter.ConnectionQuality.Value;");
 
 if(String(actconf.tempSensorType) == "DS18B20"){
   content +=F( "temp = document.getElementById('temp');");
   content +=F( "temp.value = myObj.Device.MeasuringValues.DeviceTemperature.Value;");
   content +=F( "document.getElementById('tunit').innerHTML = myObj.Device.MeasuringValues.DeviceTemperature.Unit;");
 }
 
 content +=F( "winddir = document.getElementById('winddir');");
 content +=F( "winddir.value = myObj.Device.MeasuringValues.WindDirection.Value;");
 content +=F( "document.getElementById('dirunit').innerHTML = myObj.Device.MeasuringValues.WindDirection.Unit;");
 content +=F( "resolution = document.getElementById('resolution');");
 content +=F( "resolution.value = myObj.Device.MeasuringValues.Resolution.Value;");
 content +=F( "document.getElementById('resunit').innerHTML = myObj.Device.MeasuringValues.Resolution.Unit;");
 content +=F( "windspeed = document.getElementById('windspeed');");
 content +=F( "windspeed.value = myObj.Device.MeasuringValues.WindSpeed.Value;");
 content +=F( "document.getElementById('speedunit').innerHTML = myObj.Device.MeasuringValues.WindSpeed.Unit;");
 content +=F( "dwspeed = document.getElementById('dwspeed');");
 content +=F( "dwspeed.value = myObj.Device.MeasuringValues.DownWindSpeed.Value;");
 content +=F( "document.getElementById('dwunit').innerHTML = myObj.Device.MeasuringValues.DownWindSpeed.Unit;");
 content +=F( "sensor1 = document.getElementById('sensor1');");
 content +=F( "sensor1.value = myObj.Device.MeasuringValues.Sensor1.Value;");
 content +=F( "document.getElementById('s1unit').innerHTML = myObj.Device.MeasuringValues.Sensor1.Unit;");
 if(String(actconf.windSensorType) == "WiFi 1000"){
   content +=F( "sensor2 = document.getElementById('sensor2');");
   content +=F( "sensor2.value = myObj.Device.MeasuringValues.Sensor2.Value;");
   content +=F( "document.getElementById('s2unit').innerHTML = myObj.Device.MeasuringValues.Sensor2.Unit;");
   content +=F( "pcounter = document.getElementById('pcounter');");
   content +=F( "pcounter.value = myObj.Device.MeasuringValues.PulseCounter.Value;");
   content +=F( "document.getElementById('pcunit').innerHTML = myObj.Device.MeasuringValues.PulseCounter.Unit;");
   content +=F( "time1 = document.getElementById('time1');");
   content +=F( "time1.value = myObj.Device.MeasuringValues.Time1.Value;");
   content +=F( "document.getElementById('t1unit').innerHTML = myObj.Device.MeasuringValues.Time1.Unit;");
   content +=F( "time2 = document.getElementById('time2');");
   content +=F( "time2.value = myObj.Device.MeasuringValues.Time2.Value;");
   content +=F( "document.getElementById('t2unit').innerHTML = myObj.Device.MeasuringValues.Time2.Unit;");
 }
 if(String(actconf.windSensorType) == "Yachta" || String(actconf.windSensorType) == "Jukolein" || String(actconf.windSensorType) == "Ventus"){
   content +=F( "magnitude = document.getElementById('magnitude');");
   content +=F( "magnitude.value = myObj.Device.MeasuringValues.MagFluxDensity.Value;");
   content +=F( "document.getElementById('magnitudeunit').innerHTML = myObj.Device.MeasuringValues.MagFluxDensity.Unit;");
   
   content +=F( "magsensor = document.getElementById('magsensor');");
   content +=F( "magsensor.value = myObj.Device.MeasuringValues.MagnetSensor.Value;");
   content +=F( "document.getElementById('magunit').innerHTML = myObj.Device.MeasuringValues.MagnetSensor.Unit;");
 }
 if(String(actconf.windSensorType) == "Ventus" && String(actconf.tempSensorType) == "BME280"){
   content +=F( "atemp = document.getElementById('atemp');");
   content +=F( "atemp.value = myObj.Device.MeasuringValues.AirTemperature.Value;");
   content +=F( "document.getElementById('aunit').innerHTML = myObj.Device.MeasuringValues.AirTemperature.Unit;");

   content +=F( "pres = document.getElementById('pres');");
   content +=F( "pres.value = myObj.Device.MeasuringValues.AirPressure.Value;");
   content +=F( "document.getElementById('punit').innerHTML = myObj.Device.MeasuringValues.AirPressure.Unit;");

   content +=F( "hum = document.getElementById('hum');");
   content +=F( "hum.value = myObj.Device.MeasuringValues.AirHumidity.Value;");
   content +=F( "document.getElementById('humunit').innerHTML = myObj.Device.MeasuringValues.AirHumidity.Unit;");
 }
 content +=F( "rotspeed = document.getElementById('rotspeed');");
 content +=F( "rotspeed.value = myObj.Device.MeasuringValues.RotationSpeed.Value;");
 content +=F( "document.getElementById('rotunit').innerHTML = myObj.Device.MeasuringValues.RotationSpeed.Unit;");
/*
 content +=F( "document.getElementById('temp').innerHTML = myObj.Device.MeasuringValues.DeviceTemperature.Value;");
 content +=F( "document.getElementById('tunit').innerHTML = myObj.Device.MeasuringValues.DeviceTemperature.Unit;");
 content +=F( "document.getElementById('winddir').innerHTML = myObj.Device.MeasuringValues.WindDirection.Value;");
 content +=F( "document.getElementById('dirunit').innerHTML = myObj.Device.MeasuringValues.WindDirection.Unit;");
 content +=F( "document.getElementById('resolution').innerHTML = myObj.Device.MeasuringValues.Resolution.Value;");
 content +=F( "document.getElementById('resunit').innerHTML = myObj.Device.MeasuringValues.Resolution.Unit;");
 content +=F( "document.getElementById('windspeed').innerHTML = myObj.Device.MeasuringValues.WindSpeed.Value;");
 content +=F( "document.getElementById('speedunit').innerHTML = myObj.Device.MeasuringValues.WindSpeed.Unit;");
 content +=F( "document.getElementById('dwspeed').innerHTML = myObj.Device.MeasuringValues.DownWindSpeed.Value;");
 content +=F( "document.getElementById('dwunit').innerHTML = myObj.Device.MeasuringValues.DownWindSpeed.Unit;");
 content +=F( "document.getElementById('sensor1').innerHTML = myObj.Device.MeasuringValues.Sensor1.Value;");
 content +=F( "document.getElementById('s1unit').innerHTML = myObj.Device.MeasuringValues.Sensor1.Unit;");
 content +=F( "document.getElementById('sensor2').innerHTML = myObj.Device.MeasuringValues.Sensor2.Value;");
 content +=F( "document.getElementById('s2unit').innerHTML = myObj.Device.MeasuringValues.Sensor2.Unit;");
 content +=F( "document.getElementById('time1').innerHTML = myObj.Device.MeasuringValues.Time1.Value;");
 content +=F( "document.getElementById('t1unit').innerHTML = myObj.Device.MeasuringValues.Time1.Unit;");
 content +=F( "document.getElementById('time2').innerHTML = myObj.Device.MeasuringValues.Time2.Value;");
 content +=F( "document.getElementById('t2unit').innerHTML = myObj.Device.MeasuringValues.Time2.Unit;");
 content +=F( "document.getElementById('rotspeed').innerHTML = myObj.Device.MeasuringValues.RotationSpeed.Value;");
 content +=F( "document.getElementById('rotunit').innerHTML = myObj.Device.MeasuringValues.Rotation.Unit;");

 content +=F( "document.getElementById('string1').innerHTML = myObj.Device.NMEAValues.String1;");
 content +=F( "document.getElementById('string2').innerHTML = myObj.Device.NMEAValues.String2;");
 content +=F( "document.getElementById('string3').innerHTML = myObj.Device.NMEAValues.String3;");
 content +=F( "document.getElementById('string4').innerHTML = myObj.Device.NMEAValues.String4;");
 content +=F( "document.getElementById('string5').innerHTML = myObj.Device.NMEAValues.String5;");
*/
 // If Demo Mode active the give out a message
 content += F("servermode = myObj.Device.NetworkParameter.ServerMode;");
 content += F("if (servermode == 4) {");
 content += F("document.getElementById('info').innerHTML = '(Demo Mode)';");
 content += F("document.getElementById('info2').innerHTML = '(Demo Mode)';");
 content += F("}");
 content += F("else {");
 content += F("document.getElementById('info').innerHTML = '';");
 content += F("}");
 
 content +=F( "}");
 content +=F( "};");

 content +=F( "function read_json() {");
//content +=F( "xmlhttp.open('GET', 'http://192.168.4.1/json', true);");
 content +=F( "xmlhttp.open('GET', '/json', true);");
 content +=F( "xmlhttp.send();");
 content +=F( "}");

 content +=F( "setInterval(function(){read_json(); }, 1000);");

 return content;
}
