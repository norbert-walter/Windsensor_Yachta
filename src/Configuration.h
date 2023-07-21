#ifndef Configuration_h
#define Configuration_h

// Default configuration
// Types 'byte' und 'word' doesn't work!
typedef struct {
  int valid = 11;                           // Number of configuration (Please change when the structure or values are changed)
  int crypt = 0;                            // Activate for critical webside a password query [0 = off|1 = on]
  char password[31] = "12345678";           // Password for critical websides (settings, update and reboot)
  char devname[21] = "Windsensor";          // Device name for web configuration
  char crights[14] = "NoWa (C) 2023";       // Copy rights
  char fversion[6] = "V1.18";               // Firmware version
  char license[12] = "GNU GPL V3";          // License type
  int debug = 3;                            // Debug mode 0=off 1=Errors 2=Errors + Warnings 3=Errors + Warnings + Messages
  char cssid[31] = "MyBoat";                // SSID of WiFi Client
  char cpassword[31] = "S6587rr94P";        // Password of WiFi Client
  int timeout = 30;                         // Connection timeout for client in [s] [30|90|120|150|180|210|240|270|300]
  char sssid[31] = "NoWa";                  // SSID of WiFi Server
  char spassword[31] = "12345678";          // Password of WiFi Server
  int apchannel = 1;                        // Assess Point channel [1...13]
  int maxconnections = 2;                   // Max number of connection for WiFi clients [1...4]
  int mDNS = 1;                             // Using mDNS service [0|1] 0=off, 1=on
  char hostname [31] = "windsensor";        // Hostname WiFi Server
  int dataport = 6666;                      // Port for NMEA data output
  int httpport = 80;                        // Port for HTTP and update pages
  int serverMode = 0;                       // Used server mode [0|1|2|3|4] 0=HTTP (JSON, NMEA), 1=NMEA Serial, 2=MQTT, 3=Diagnostic, 4=Demo (Simulation data)
  int serspeed = 115200;                    // Serial speed in [Bd] 8N1 [300|1200|2400|4800|9600|19200|38400|57600|74880|115200]
  int skin = 0;                             // Skin for websides [0|1|2]
  char instrumentType[8] = "complex";       // Instrument type [simple|complex] simple = Canvas HTML5 , complex = Canvas Steel Series library
  int instrumentSize = 400;                 // Instrument size X * Y [pix] [200|250|300|350|400|450|500|550|600]
  int sensorID = 0;                         // ID of sensor [0...9]
  char windSensorType[15] = "Yachta";       // Type of wind sensor [WiFi 1000|Yachta|Yachta 2.0|Jukolein|Ventus]
  int windSensor = 1;                       // Send wind data 0=off 1=on (WIMWV, WIVWR, WIVPW, PWINF) or Serial or JSON
  char windType[2] = "R";                   // Type of wind R=relative, T=true
  int offset = 0;                           // Offset of wind direction [-180°...+180°]
  int average = 1;                          // Number of values for average building [1...10], for high speed use 1, default use 2
  char speedUnit[5] = "kn";                 // Unit of speed [m/s|km/h|kn|bft] for WIMWV
  int downWindSensor = 1;                   // Send data to down wind 0=off 1=on (WIVPW)
  int downWindRange = 50;                   // Down wind area = 180° +/- downWindRange
  float calslope = 1.0;                     // Speed sensor calibration slope, default 1.0
  float caloffset = 0.0;                    // Speed sensor calibration offset, default 0.0
  char tempSensorType[10] = "DS18B20";      // Type of temperature sensor [Off|DS18B20|BME280]
  int tempSensor = 1;                       // Send data for temp 0=off 1=on (PWWST)
  char tempUnit[2] = "C";                   // Unit of temperature [C|F]
} configData;

#endif
