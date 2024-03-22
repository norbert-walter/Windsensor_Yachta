//*********************************************************************************************
// WiFi and NMEA server for transmitting wind sensor data via TCP connection
// (C) Norbert Walter 2023
// License: GNU GPL V3
// https://www.gnu.org/licenses/gpl-3.0.txt
//
// WiFi_Windsensor.cpp
//
// Tested and compiled with Visual Studio Code and PlatformIO
// Board esp8266 V2.7.4 (2.2.2-dev(38a443e))
// The server use different NMEA centeces
//
// Wind direction and speed:  $WIMWV,x.x,a,x.x,a,A*hh
// Wind direction and speed:  $WIVWR,x.x,a,x.x,N,x.x,M,x.x,K*hh
// Down wind speed:           $WIVPW,x.x,N,x.x,M*hh                               (Wind speed parallel to wind direction)
// Wind speed informations:   $PWINF,0,x.x,D,x.x,D,x.x,M,x.x,K,x.x,N,x.x,B,A*hh   (Custom sentence)
// Wind sensor temperature:   $PWWST,C,0,x.x,A*hh                                 (Custom sentence)
//
//*********************************************************************************************

// Includes
#include <ESP8266WiFi.h>    // WiFi lib with TCP server and client

#include <WiFiClient.h>             // WiFi lib for clients
#include <ESP8266WebServer.h>       // WebServer lib
#include <ESP8266mDNS.h>            // DNS lib
#include <ESP8266HTTPUpdateServer.h>// Web Update server

#include <Ticker.h>         // Timer lib
#include <EEPROM.h>         // EEPROM lib
#include <WString.h>        // Needs for structures
#include <OneWire.h>        // 1Wire network lib
#include <Wire.h>           // Lib for I2C
#include <Adafruit_Sensor.h>// Adafuit sensor lib
#include <Adafruit_BME280.h>// Lib for BME280
#include "AS5600.h"         // Lib for magnetic rotation sensor AS5600
#include "MT6701_I2C.h"     // Lib for magnetic rotation sensor MT6701
#include <DallasTemperature.h>// Dallas 1Wire lib
#include <SimplyAtomic.h>   // This library includes the ATOMIC_BLOCK macro
#include "Configuration.h"  // Setup data structure in header file
#include "Definitions.h"    // Local definitions in additional file

AMS_5600 ams5600;            // Declare magnetic rotation sensor AS5600
MT6701I2C mt6701(&Wire);    // Declare magnetic rotation sensor MT6701
Adafruit_BME280 bme;        // Declare environment sensor BME280
OneWire oneWire(ONE_WIRE_BUS); // Declare 1Wire
DallasTemperature DS18B20(&oneWire); // Declare DS18B20
configData actconf;         // Actual configuration, Global variable
                            // Overload with old EEPROM configuration by start. It is necessarry for port and serspeed
                            // Don't change the position!

#include "Calculation.h"    // Function library for wind data calculation
#include "FunctionsLib.h"   // Function library
#include "NMEATelegrams.h"  // Function library for NMEA telegrams
#include "icon_html.h"      // Favorit icon
#include "css_html.h"       // CSS cascading style sheets
#include "steel_html.h"     // JavaScript steelseries_micro.js.gz library
#include "tween_html.h"     // JavaScript tween-min.js.gz library
#include "js_html.h"        // JavaScript functions
#include "main_html.h"      // Main webpage
#include "settings_html.h"  // Settings webpage
#include "firmware_html.h"  // Firmware update webpage
#include "json_html.h"      // JSON webpage
#include "json2_html.h"     // JSON webpage for Hall sensor signals
#include "MD5_html.h"       // JavaScript crypt password with MD5
#include "restart_html.h"   // Reset info webpage
#include "devinfo_html.h"   // Device info webpage
#include "windv_html.h"     // Wind value webpage
#include "windi_html.h"     // Wind instrument webpage
#include "error_html.h"     // Error 404 webpage

// Declarations
int value;                  // Value from first byte in EEPROM
int empty;                  // If EEPROM empty without configutation then set to 1 otherwise 0
configData defconf;         // Definition of default configuration data
configData oldconf;         // Configuration stucture for old config data in EEPROM
configData newconf;         // Configuration stucture for new config data in EEPROM

ESP8266WebServer httpServer(actconf.httpport);  // Port for HTTP server
ESP8266HTTPUpdateServer httpUpdater;            // Declaration update server
MDNSResponder mdns;                             // Activate DNS responder

Ticker Timer2;              // Declare Timer2 for average building
Ticker Timer3;              // Declare Timer3 for normal NMEA data sending
Ticker Timer4;              // Declare Timer4 for reduced NMEA data sending
Ticker Timer5;              // Declare Timer5 for calculation of windspeed und winddirection 
WiFiServer server(actconf.dataport);  // Declare WiFi NMEA server port
 
//*********************************************************************************************
// Setup section
//*********************************************************************************************
void setup() {
   // Start bus systems
   Wire.begin();                        // Start I2C
   bme.begin(i2cAddressBME280);         // Start BME280

   // !!!!!! Uncomment this line if you using a new configuration structure !!!!!!
//  saveEEPROMConfig(defconf);
  
  // Read the first byte from the EEPROM
  EEPROM.begin(sizeEEPROM);
  value = EEPROM.read(cfgStart);
  EEPROM.end(); 
  // If the fist Byte not identical to the first value in the default configuration then saving a default configuration in EEPROM.
  // Means if the EEPROM empty then saving a default configuration.
  if(value == defconf.valid){
    empty = 0;                  // Marker for configuration is present
  }
  else{
    saveEEPROMConfig(defconf);
    empty = 1;                  // Marker for configuration is missing
  }

  // Loading EEPROM configuration
  actconf = loadEEPROMConfig(); // Overload with old EEPROM configuration by start. It is necessarry for serspeed

  // If the firmware version in EEPROM different to defconf then save the new version in EEPROM
  if(String(actconf.fversion) != String(defconf.fversion)){
    String fver = defconf.fversion;
    fver.toCharArray(actconf.fversion, 6);
    saveEEPROMConfig(actconf);
  }
 
  // Pin definitions and settings for wind sensor types Yachta and Jukolein
  if(String(actconf.windSensorType) == "Jukolein"){
    
    // Pin redefinition for other wind sensor types (Original values see Definition.h)
    // Attention! GPIO 12 is not available! (1Wire)
    // Existing pins
    ledPin = 14;                // LED GPIO 14 (fake) (D5)
    INT_PIN1 = 2;               // Wind speed GPIO 2 (Hall sensor) (D4)
    INT_PIN2 = 16;              // Wind direction GPIO 16 (Hall sensor fake) (D0)
    // New pins
    I2C_SCL = 5;                // Wind direction magnetic sensor SCL GPIO 5 (AS5600) (D1)
    I2C_SDA = 4;                // Wind direction magnetic sensor SDA GPIO 4 (AS6500) (D2)
  }

  // Pin definitions and settings for wind sensor types Yachta
  if(String(actconf.windSensorType) == "Yachta"){
    
    // Pin redefinition for other wind sensor types (Original values see Definition.h)
    // Attention! GPIO 12 is not available! (1Wire)
    // Existing pins
    ledPin = 2;                 // LED GPIO 2 (D4)
    INT_PIN1 = 14;              // Wind speed GPIO 14 (Reed switch) (D5), pin need 10k and 100n for spike reduction
    INT_PIN2 = 16;              // Wind direction GPIO 16 (Hall sensor fake) (D0)
    // New pins
    I2C_SCL = 5;                // Wind direction magnetic sensor SCL GPIO 5 (AS5600) (D1)
    I2C_SDA = 4;                // Wind direction magnetic sensor SDA GPIO 4 (AS6500) (D2)
  }

  if(String(actconf.windSensorType) == "Yachta 2.0"){
    
    // Pin redefinition for other wind sensor types (Original values see Definition.h)
    // Attention! GPIO 12 is not available! (1Wire)
    // Existing pins
    ledPin = 2;                 // LED GPIO 2 (D4)
    INT_PIN1 = 14;              // Wind speed GPIO 14 (Reed switch) (D5), pin need 10k and 100n for spike reduction
    INT_PIN2 = 16;              // Wind direction GPIO 16 (Hall sensor fake) (D0)
    // New pins
    I2C_SCL = 5;                // Wind direction magnetic sensor SCL GPIO 5 (MT6701) (D1)
    I2C_SDA = 4;                // Wind direction magnetic sensor SDA GPIO 4 (MT6701) (D2)
    mt6701.begin(I2C_SDA, I2C_SCL);
  }

  // Pin definitions and settings for wind sensor types Ventus
  if(String(actconf.windSensorType) == "Ventus"){
    
    // Pin redefinition for other wind sensor types (Original values see Definition.h)
    // Attention! GPIO 12 is not available! (1Wire)
    // Existing pins
    ledPin = 2;                 // LED GPIO 2 (D4)
    INT_PIN1 = 14;              // Wind speed GPIO 14 (Reed switch) (D5), pin need 10k and 100n for spike reduction
    INT_PIN2 = 16;              // Wind direction GPIO 16 (Hall sensor fake) (D0)
    // New pins
    I2C_SCL = 5;                // Wind direction magnetic sensor SCL GPIO 5 (AS5600) (D1)
    I2C_SDA = 4;                // Wind direction magnetic sensor SDA GPIO 4 (AS6500) (D2)
  }
  
  // Pin settings
  pinMode(INT_PIN1, INPUT_PULLUP);  // Interrupt input 1 speed
  pinMode(INT_PIN2, INPUT_PULLUP);  // Interrupt input 2 direction
  pinMode(ledPin, OUTPUT);          // LED Pin output
  digitalWrite(ledPin, LOW);        // Switch LED on (inverted!)

  Serial.begin(actconf.serspeed);   // Start serial communication
  delay(10);

//  DebugPrint(3, "First EEPROM byte: ");
//  DebugPrintln(3, value);

  // ESP8266 Information Data
  DebugPrintln(3, "Booting Sketch...");
  DebugPrint(3, actconf.devname);
  DebugPrint(3, " ");
  DebugPrint(3, actconf.windSensorType);
  DebugPrint(3, " ");
  DebugPrint(3, actconf.fversion);
  DebugPrintln(3, " (C) Norbert Walter");
  DebugPrintln(3, "*********************************************");
  DebugPrintln(3, "");
  DebugPrintln(3, "Modul Type: ESP8266");
  DebugPrint(3, "SDK-Version: ");
  DebugPrintln(3, ESP.getSdkVersion());
  DebugPrint(3, "ESP8266 Chip-ID: ");
  DebugPrintln(3, ESP.getChipId());
  DebugPrint(3, "ESP8266 Speed [MHz]: ");  
  DebugPrintln(3, ESP.getCpuFreqMHz());
  DebugPrint(3, "Free Heap Size [Bytes]: ");
  DebugPrintln(3, ESP.getFreeHeap());
  DebugPrintln(3, "");
  DebugPrint(3, "Sensor ID: ");
  DebugPrintln(3, actconf.sensorID);
  DebugPrint(3, "Wind Sensor Type: ");
  DebugPrintln(3, actconf.windSensorType);
  DebugPrintln(3, "Sensor Type: Wind Speed");
  DebugPrint(3, "Input Pin: GPIO ");
  DebugPrintln(3, INT_PIN1);
  DebugPrintln(3, "Value Range [kn]: 0...73");
  DebugPrint(3, "Sensor Type: ");
  if(String(actconf.windType) == "R"){
      DebugPrintln(3, "Relative ");
    }
    else{
      DebugPrintln(3, "True ");
    }    
  if(String(actconf.windSensorType) == "WiFi 1000"){  
    DebugPrintln(3, "Wind direction");
    DebugPrint(3, "Input Pin: GPIO ");
    DebugPrintln(3, INT_PIN2);
    DebugPrintln(3, "Value Range [°]: 0...360");
  }
  if(String(actconf.windSensorType) == "Yachta" || String(actconf.windSensorType) == "Jukolein" || String(actconf.windSensorType) == "Ventus"){
    DebugPrintln(3, "Wind direction: AS5600");
    DebugPrint(3, "SCL: GPIO ");
    DebugPrintln(3, SCL);
    DebugPrint(3, "SDA: GPIO ");
    DebugPrintln(3, SDA);
    DebugPrint(3, "Scan I2C at address 0x");
    if (i2cAddressAS5600 < 0x10) {
      DebugPrint(3, "0");
    }
    DebugPrint(3, String(i2cAddressAS5600, HEX));
    DebugPrint(3, ": ");
    Wire.beginTransmission(i2cAddressAS5600);
    if(Wire.endTransmission() == 0){
      i2creadyAS5600 = 1;                        // Result I2C scan
      DebugPrintln(3, "ready");
      DebugPrint(3, "Magnitude [1]: ");
      DebugPrintln(3, ams5600.getMagnitude());
      DebugPrint(3, "Raw Angle [°]: ");
      magsensor = ams5600.getRawAngle() * 0.087; // 0...4096 which is 0.087 of a degree
      DebugPrintln(3, magsensor);
    }
    else{
      i2creadyAS5600 = 0;                        // Result I2C scan
      DebugPrintln(3, "error");
      DebugPrintln(3, "Stop I2C for device AS5600");
    }
  }

  if(String(actconf.windSensorType) == "Yachta 2.0"){
    DebugPrintln(3, "Wind direction: MT6701");
    DebugPrint(3, "SCL: GPIO ");
    DebugPrintln(3, SCL);
    DebugPrint(3, "SDA: GPIO ");
    DebugPrintln(3, SDA);
    DebugPrint(3, "Scan I2C at address 0x");
    if (i2cAddressMT6701 < 0x10) {
      DebugPrint(3, "0");
    }
    DebugPrint(3, String(i2cAddressMT6701, HEX));
    DebugPrint(3, ": ");
    Wire.beginTransmission(i2cAddressMT6701);
    if(Wire.endTransmission() == 0){
      i2creadyMT6701 = 1;                       // Result I2C scan
      DebugPrintln(3, "ready");
      DebugPrint(3, "Raw Value: ");
      mt6701.begin();
      DebugPrintln(3, mt6701.getRawAngle());
      DebugPrint(3, "Raw Angle [°]: ");
      magsensor = mt6701.getDegreesAngle();     // 0...16384 which is 0.0219 of a degree
      DebugPrintln(3, magsensor);
    }
    else{
      i2creadyMT6701 = 0;                       // Result I2C scan
      DebugPrintln(3, "error");
      DebugPrintln(3, "Stop I2C for device MT6701");
    }
  }

  if(String(actconf.windSensorType) == "Ventus"){
    DebugPrintln(3, "Environment Sensor: BME280");
    DebugPrint(3, "SCL: GPIO ");
    DebugPrintln(3, SCL);
    DebugPrint(3, "SDA: GPIO ");
    DebugPrintln(3, SDA);
    DebugPrint(3, "Scan I2C at address 0x");
    if (i2cAddressBME280 < 0x10) {
      DebugPrint(3, "0");
    }
    DebugPrint(3, String(i2cAddressBME280, HEX));
    DebugPrint(3, ": ");
    Wire.beginTransmission(i2cAddressBME280);
    if(Wire.endTransmission() == 0){
      i2creadyBME280 = 1;                        // Result I2C scan
      DebugPrintln(3, "ready");
      DebugPrint(3, "Temperature [°C]: ");
      airtemperature = bme.readTemperature();
      DebugPrintln(3, airtemperature);      
      DebugPrint(3, "Air Pressure [mbar]: ");
      airpressure = bme.readPressure() / 100;
      DebugPrintln(3, airpressure);
      DebugPrint(3, "Air Humidity [%]: ");
      airhumidity = bme.readHumidity();
      DebugPrintln(3, airhumidity);
      DebugPrint(3, "Altitude [m]: ");
      altitude = bme.readAltitude(SEALEVELPRESSURE_HPA);
      DebugPrintln(3, altitude);
    }
    else{
      i2creadyBME280 = 0;                        // Result I2C scan
      DebugPrintln(3, "error");
      DebugPrintln(3, "Stop I2C for device BME280");
    }
  }
    
  DebugPrintln(3, "Sensor Type: Sensor Temp 1Wire");
  DebugPrint(3, "Input Pin: GPIO ");
  DebugPrintln(3, ONE_WIRE_BUS);
  DebugPrintln(3, "Value Range [°C]: -55...125");
  DebugPrint(3, "Send Period [ms]: ");
  DebugPrintln(3, SendPeriod);
  DebugPrint(3, "Reduced Send Period [ms]: ");
  DebugPrintln(3, RedSendPeriod);
  DebugPrintln(3, "");

  // Debug info for initialize the EEPROM
  if(empty == 1){
    DebugPrintln(3, "EEPROM config missing, initialization done");
  }
  else{
    DebugPrintln(3, "EEPROM config present");
  }

  // Loading EEPROM config
  DebugPrintln(3, "Loading actual EEPROM config");
  actconf = loadEEPROMConfig();
  DebugPrintln(3, "");

  // Starting access point for update server
  DebugPrint(3, "Access point started with SSID ");
  DebugPrintln(3, actconf.sssid);
  DebugPrint(3, "Access point channel: ");
  DebugPrintln(3, WiFi.channel());
//  DebugPrintln(3, actconf.apchannel);
  DebugPrint(3, "Max AP connections: ");
  DebugPrintln(3, actconf.maxconnections);
  WiFi.mode(WIFI_AP_STA);
  IPAddress local_IP(192,168,5,1);
  IPAddress gateway(192,168,5,255);
  IPAddress subnet(255,255,255,0);
  WiFi.softAPConfig(local_IP, gateway, subnet);
  WiFi.softAP(actconf.sssid, actconf.spassword, actconf.apchannel, false, actconf.maxconnections);
  hname = String(actconf.hostname) + "-" + String(actconf.sensorID);
  WiFi.hostname(hname);   // Provide the hostname
  DebugPrint(3, "Host name: ");
  DebugPrintln(3, hname);
  if(actconf.mDNS == 1){
    MDNS.begin(hname);      // Start mDNS service
    MDNS.addService("http", "tcp", actconf.httpport);       // HTTP service
    MDNS.addService("nmea-0183", "tcp", actconf.dataport);  // NMEA0183 data service for AVnav
  }  
  DebugPrintln(3, "mDNS service: activ");
  DebugPrint(3, "mDNS name: ");
  DebugPrint(3, hname);
  DebugPrintln(3, ".local");
  
  // Sart update server
  httpUpdater.setup(&httpServer);
  httpServer.begin();
  DebugPrint(3, "HTTP Update Server started at port: ");
  DebugPrintln(3, actconf.httpport);
  DebugPrint(3, "Use this URL: ");
  DebugPrint(3, "http://");
  DebugPrint(3, WiFi.softAPIP());
  DebugPrintln(3, "/update");
  DebugPrintln(3, "");

  #include "ServerPages.h"    // Webserver pages request functions
  
  // Connect to WiFi network
  DebugPrint(3, "Connecting WiFi client to ");
  DebugPrintln(3, actconf.cssid);

  // Load connection timeout from configuration (maxccount = (timeout[s] * 1000) / 500[ms])
  maxccounter = (actconf.timeout * 1000) / 500;

  // Wait until is connected otherwise abort connection after x connection trys
  WiFi.begin(actconf.cssid, actconf.cpassword);
  ccounter = 0;
  while ((WiFi.status() != WL_CONNECTED) && (ccounter <= maxccounter)) {
    delay(500);
    DebugPrint(3, ".");
    ccounter ++;
  }
  DebugPrintln(3, "");
  if (WiFi.status() == WL_CONNECTED){
    DebugPrint(3, "WiFi client connected with IP: ");
    DebugPrintln(3, WiFi.localIP());
    DebugPrintln(3, "");
    digitalWrite(ledPin, HIGH);           // LED off (Low activ)
    
    delay(100);
  }
  else{
    WiFi.disconnect(true);                // Abort connection
    DebugPrintln(3, "Connection aborted");
    DebugPrintln(3, "");
    for(int i = 0; i <= 5; i++){
      digitalWrite(ledPin, HIGH);         // LED off (Low activ)
      delay(100);
      digitalWrite(ledPin, LOW);          // LED on (Low activ)
      delay(100);
    }
  }
  
  // Start the NMEA TCP server
  server.begin();
  DebugPrint(3, "NMEA-Server started at port: ");
  DebugPrintln(3, actconf.dataport);
  // Print the IP address
  DebugPrint(3, "Use this URL : ");
  DebugPrint(3, "http://");
  if (WiFi.status() == WL_CONNECTED){
    DebugPrintln(3, WiFi.localIP());
  }
  else{
    DebugPrintln(3, WiFi.softAPIP());
  };

  //*************************************************
  timer1_attachInterrupt(counter);              // Start interrupt routine counter
  timer1_enable(TIM_DIV16, TIM_EDGE, TIM_LOOP); // 80MHz / 16 => 0,2us
  timer1_write(500);                            // Start timer1 100us @ 0,2us
  Timer2.attach_ms(50, buildaverage);           // Start timer all 50ms for average building and reading magnetic sensor
  Timer3.attach_ms(SendPeriod, sendNMEA);       // Data transmission timer for NMEA
  Timer4.attach_ms(RedSendPeriod, sendNMEA2);   // Data transmission timer with reduced frequence for NMEA
  Timer5.attach_ms(500, winddata);              // Start Timer all 500ms for wind data calculation
  
  // Work around for start problem by high wind speed > 7rpm (cyclic boot loop)
  // Start interrupts at first in low level mode and wait 4s then change in falling slope mode 
  attachInterrupt(INT_PIN1, interruptRoutine1, LOW); // Start interrupt for wind speed
  attachInterrupt(INT_PIN2, interruptRoutine2, LOW); // Start Interrupt for wind direction
  delay(4000);
  // Start interrupts in falling slope mode
  attachInterrupt(INT_PIN1, interruptRoutine1, FALLING); // Start interrupt for wind speed
  attachInterrupt(INT_PIN2, interruptRoutine2, FALLING); // Start Interrupt for wind direction

  //**************************************************
   
  // Reset the time variables
  time1 = 0;
  time2 = 0;
  time1_avg = 0;
  time2_avg = 0;

}
 
//*********************************************************************************************
// Loop section
//*********************************************************************************************
void loop() {
  
  httpServer.handleClient();        // HTTP Server-handler for HTTP update server
  MDNS.update();                    // Update DNS info
  
  // Check if a client is connected
  WiFiClient client = server.available();
  int i = 0;
  
  if(!client.connected() && WiFi.status() != WL_CONNECTED){
    digitalWrite(ledPin, LOW);      // LED on (Low activ)
    i = 0;
  }

  // While client is connected or Serial Mode is active
  while (client.connected() && !client.available()) {
    digitalWrite(ledPin, HIGH);     // LED off (Low activ)
    
    httpServer.handleClient();      // HTTP Server-handler for HTTP update server
    if(actconf.mDNS == 1){
      MDNS.update();                // Update DNS info  
    }  
    
    if ((i == 0) && ((int(actconf.serverMode) == 0) || (int(actconf.serverMode) == 4))) {
      DebugPrintln(3, "Client connected");
      DebugPrintln(3, "");
    }

    // Wind speed and wind direction data calculated via Timer5 interrupt all 500ms

    // Sending NMEA data with normal speed
    if (windspeed_mps > 0 && flag1 == true){     
      i++;
      DebugPrintln(3, "");
      DebugPrint(3, "Send package:");
      DebugPrintln(3, i);
          
      if((int(actconf.serverMode) == 0) || (int(actconf.serverMode) == 1) || (int(actconf.serverMode) == 4)){
         if(int(actconf.windSensor) == 1){
          client.println(sendMWV(1));  // Send NMEA telegrams
          client.println(sendVWR(1));
          client.println(sendVPW(1));
          client.println(sendINF(1));
         }
        if(int(actconf.tempSensor) == 1){
          if(String(actconf.tempSensorType) == "DS18B20"){
            client.println(sendWST(1));
          }
          if(String(actconf.tempSensorType) == "BME280"){
            client.println(sendWSE(1));
          }    
        } 
      }
         
      flashLED(10);                 // Flash LED for data transmission
      flag1 = false;                // Reset the flag
    }

    // Sending NMEA data with reduced speed
    if (windspeed_mps <= 0 && flag2 == true){
      i++;
      DebugPrintln(3, "");
      DebugPrint(3, "Send package:");
      DebugPrintln(3, i);
      
      if((int(actconf.serverMode) == 0) || (int(actconf.serverMode) == 1) || (int(actconf.serverMode) == 4)){
        if(int(actconf.windSensor) == 1){
          client.println(sendMWV(1));  // Send NMEA telegrams
          client.println(sendVWR(1));
          client.println(sendVPW(1));
          client.println(sendINF(1));
        }
        if(int(actconf.tempSensor) == 1){
          if(String(actconf.tempSensorType) == "DS18B20"){
            client.println(sendWST(1));
          }
          if(String(actconf.tempSensorType) == "BME280"){
            client.println(sendWSE(1));
          }    
        }
      }
           
      flashLED(10);                 // Flash LED for data transmission
      flag2 = false;                // Reset the flag
    }

  }

  // If client not connected and server mode 1 (NMEA Serial) or server mode 4 (Demo)
  if(!client.connected() && (int(actconf.serverMode) == 1 || int(actconf.serverMode) == 4)){
    // Sending NMEA data with normal speed
    if (windspeed_mps > 0 && flag1 == true){  
      if(int(actconf.windSensor) == 1){
        sendMWV(1);  // Send NMEA telegrams
        sendVWR(1);
        sendVPW(1);
        sendINF(1);
      }
      if(int(actconf.tempSensor) == 1){
        if(String(actconf.tempSensorType) == "DS18B20"){
          sendWST(1);
        }
        if(String(actconf.tempSensorType) == "BME280"){
          sendWSE(1);
        }    
      }

      flashLED(10);                 // Flash LED for data transmission
      flag1 = false;                // Reset the flag
    }

    // Sending NMEA data with reduced speed
    if (windspeed_mps <= 0 && flag2 == true){      
      if(int(actconf.windSensor) == 1){
        sendMWV(1);  // Send NMEA telegrams
        sendVWR(1);
        sendVPW(1);
        sendINF(1);
      }
      if(int(actconf.tempSensor) == 1){
        if(String(actconf.tempSensorType) == "DS18B20"){
          sendWST(1);
        }
        if(String(actconf.tempSensorType) == "BME280"){
          sendWSE(1);
        }    
      }
           
      flashLED(10);                 // Flash LED for data transmission
      flag2 = false;                // Reset the flag
    }
  }

  delay(150);                       // Delay for load reducing
}
