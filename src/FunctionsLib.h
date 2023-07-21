#ifndef FunctionsLib_h
#define FunctionsLib_h

// Debugging functions
void DebugPrintln(int type, const char* x){
  if(type <= actconf.debug){
    Serial.println(x);
  }
}

void DebugPrintln(int type, char x[]){
  if(type <= actconf.debug){
    Serial.println(x);
  }
}

void DebugPrintln(int type, float x){
  if(type <= actconf.debug){
    Serial.println(x);
  }
}

void DebugPrintln(int type, char x){
  if(type <= actconf.debug){
    Serial.println(x);
  }
}

void DebugPrintln(int type, int x){
  if(type <= actconf.debug){
    Serial.println(x);
  }
}

void DebugPrintln(int type, uint32_t x){
  if(type <= actconf.debug){
    Serial.println(x);
  }
}

void DebugPrintln(int type, unsigned long x){
  if(type <= actconf.debug){
    Serial.println(x);
  }
}

void DebugPrintln(int type, String x){
  if(type <= actconf.debug){
    Serial.println(x);
  }
}

void DebugPrintln(int type, IPAddress x){
  if(type <= actconf.debug){
    Serial.println(x);
  }
}

void DebugPrint(int type, const char* x){
  if(type <= actconf.debug){
    Serial.print(x);
  }
}

void DebugPrint(int type, char x[]){
  if(type <= actconf.debug){
    Serial.print(x);
  }
}

void DebugPrint(int type, float x){
  if(type <= actconf.debug){
    Serial.print(x);
  }
}

void DebugPrint(int type, char x){
  if(type <= actconf.debug){
    Serial.print(x);
  }
}

void DebugPrint(int type, int x){
  if(type <= actconf.debug){
    Serial.print(x);
  }
}

void DebugPrint(int type, uint32_t x){
  if(type <= actconf.debug){
    Serial.print(x);
  }
}

void DebugPrint(int type, unsigned long x){
  if(type <= actconf.debug){
    Serial.print(x);
  }
}

void DebugPrint(int type, String x){
  if(type <= actconf.debug){
    Serial.print(x);
  }
}

void DebugPrint(int type, IPAddress x){
  if(type <= actconf.debug){
    Serial.print(x);
  }
}

// Interrupt routine for wind speed and Hall sensor data array saving
void ICACHE_RAM_ATTR interruptRoutine1() {
  noInterrupts();
  // Run if not Demo mode
  if (actconf.serverMode != 4){
    if(marker1 == 0){
      time1 = float(counter1) / 10;     // Time1 in ms for speed
      time2 = float(counter2) / 10;     // Time2 in ms for direction
      if(time1 > 1000){                 // Limiting time1 for correct average building
        time1 = 1000;
      }
      if(time2 > 1000){                 // Limiting time2 for correct average building
        time2 = 1000;
      }
      mc = icounter % average;          // Modulo counter for average building, average see Definition.h
      timearray1[mc] = time1;
      if(time2 <= (time1 / 2)){         // Overflow exception from 0° to 360° and backwarts
        timearray2[mc] = time2;         // build positiv values in range 0°...180°
      }
      else{
        timearray2[mc] = time2 - time1; // build negativ values in range >180°...360°
      }
      counter1 = 0;
      counter2 = 0;
      marker1 = 1;
      marker2 = 1;
      
      icounter += 1;
      
      marker3 = 1;                      // Set marker for Hall sensor saving, marker3 reset in json2_html.h after JSON string sending
    }
    else{
      marker1 = 0;
      pcounter = rpcounter;             // Write pcounter for JSON
      rpcounter = 0;                    // Reset raw pulse counter for wind direction sensor
    }
  }
  interrupts();
}

// Interrupt routine for wind direction
void ICACHE_RAM_ATTR interruptRoutine2() {
  noInterrupts();
  // Run if not Demo mode
  if (actconf.serverMode != 4){
    marker2 = 0;
    if(marker1 == 1){
      rpcounter += 1;                   // Increment raw pulse counter for wind direction sensor
    }
  }
  interrupts();
}

// Timer1 hardware interrupt routine for 100us counter
void ICACHE_RAM_ATTR counter(){
  noInterrupts();
  if(marker1 == 1){
    counter1 += 1;
  }
  if(marker2 == 1){
    counter2 += 1;
  }
  // Save Hall sensor data if marker3 == 1 (Rising signal on sensor 1)
  if(marker3 == 1 && scounter < 10000){
    // Save only every 10 values one value
    if(scounter % 10 == 0){
      sensor1TimeArray[scounter / 10] = digitalRead(INT_PIN1);
      sensor2TimeArray[scounter / 10] = digitalRead(INT_PIN2);
    }
    scounter += 1;
  }
  interrupts();  
}

// Timer2 routine for average building
void buildaverage() {
  noInterrupts();
  int i = 0;
  float value1 = 0.0;
  float value2 = 0.0;

  average = actconf.average;
  // Limiting for average
  if(average < 1){
    DebugPrintln(1, "Limit error for average [1...10]");
    DebugPrint(1, "average = ");
    DebugPrintln(1, average);
    average = 1;
  }
  if(average > 10){
    DebugPrintln(1, "Limit error for average [1...10]");
    DebugPrint(1, "average = ");
    DebugPrintln(1, average);
    average = 10;
  }

  // Calculate average values
  for(i = 0; i < average; i++){
    value1 += timearray1[i];
    value2 += timearray2[i];
  }
  
  time1_avg =  value1 / average;
  
  // Overflow exception from 0° to 360° and backwarts for time2_avg
  if((value2 / average) >= 0){                    // If average value from time2 positiv (in range 0°...180°)
    time2_avg =  value2 / average;
  }
  else{                                           // If average value from time2 negativ (in range >180°...360°)
    time2_avg =  time1_avg + (value2 / average);
  }
  interrupts();
}

// Timer3 routine for NMEA data sending with normal speed (all 1s)
void sendNMEA() {
  noInterrupts();
  // Set data sending flag1
  flag1 = true;
  interrupts();
}

// Timer4 routine for NMEA data sending with reduced speed (all 3s)
void sendNMEA2() {
  noInterrupts();
  // Set data sending flag2
  flag2 = true;
  // Flag for zero wind speed detection (true = zero)
  if(icounter == icounterold){
    flag3 = true;
  }
  else{
    flag3 = false;
  }
  icounterold = icounter;
  interrupts();
}

// Timer5 routine for calculation of wind data (all 500ms)
void winddata(){
  noInterrupts();
  // Simulation if Server Mode 4
  if(actconf.serverMode == 4){
    simulationData();
  }
  else{
    calculationData();
  }
  interrupts();
}

// Checksum calculation for NMEA
char CheckSum(String NMEAData) {
  char checksum = 0;
  // Iterate over the string, XOR each byte with the total sum
  for (unsigned long c = 0; c < NMEAData.length(); c++) {
    checksum = char(checksum ^ NMEAData.charAt(c));
  } 
  // Return the result
  return checksum;
}

void eraseEEPROMConfig(configData cfg) {
  // Reset EEPROM bytes to '0' for the length of the data structure
  noInterrupts();                       // Stop all interrupts important for writing in EEPROM
  EEPROM.begin(sizeEEPROM);
  for (unsigned long i = cfgStart ; i < sizeof(cfg) ; i++) {
    EEPROM.write(i, 0);
  }
  delay(200);
  EEPROM.commit();
  EEPROM.end();
  interrupts();                         // Activate all interrupts
}

void saveEEPROMConfig(configData cfg) {
  // Save configuration from RAM into EEPROM
  noInterrupts();                       // Stop all interrupts important for writing in EEPROM
  EEPROM.begin(sizeEEPROM);
  EEPROM.put( cfgStart, cfg );
  delay(200);
  EEPROM.commit();                      // Only needed for ESP8266 to get data written
  EEPROM.end();                         // Free RAM copy of structure
  interrupts();                         // Activate all interrupts
}

configData loadEEPROMConfig() {
  // Loads configuration from EEPROM into RAM
  configData cfg;
  EEPROM.begin(sizeEEPROM);
  EEPROM.get( cfgStart, cfg );
  EEPROM.end();
  return cfg;
}

// Converting bool to int
int boolToInt(bool value){
  if(value == HIGH){
    return 1;
  }
  else{
    return 0;
  }
}

// Converting string to int
 int toInteger(String settingValue){
   char intbuf[settingValue.length()+1];
   settingValue.toCharArray(intbuf, sizeof(intbuf));
   int f = atof(intbuf);
   return f;
 }

// Converting string to float
float toFloat(String settingValue){
  char floatbuf[settingValue.length()+1];
  settingValue.toCharArray(floatbuf, sizeof(floatbuf));
  float f = atof(floatbuf);
  return f;
}

// Converting string to long
long toLong(String settingValue){
  char longbuf[settingValue.length()+1];
  settingValue.toCharArray(longbuf, sizeof(longbuf));
  long l = atol(longbuf);
  return l;
}

// Converting String to integer and then to boolean
// 1 = true
// 0 = false
boolean toBoolean(String settingValue) {
  if(settingValue.toInt()==1){
    return true;
  } else {
    return false;
  }
}

// Convert string to char
char* toChar(String command){
    if(command.length()!=0){
        char *p = const_cast<char*>(command.c_str());
        return p;
    }
    else{
      return 0;
    }
}

// Seaching the index for a value in a string array
int getindex(String data[], String compare){
  // For all array elements
  for(int i=0; data[i].length() != 0; i++){
    DebugPrint(3, i);
    DebugPrint(3, " : ");
     DebugPrintln(3, data[i]);
    if(data[i] == compare){
      return i; 
    }
  }
  return 0;
}

// Displays a WLAN field strength symbol with characters
// 0))))
String wlansymbol(){
  String symbol = "O";
  float fieldstr = float(WiFi.RSSI());
  if(fieldstr > 0){
    fieldstr = -100.0;
  }
  float wlqual = 100  - (((fieldstr * -1) - 50) * 2);
  if(wlqual < 0){
    wlqual = 0;
  }
  if(wlqual > 100){
    wlqual = 100;
  }
  if(wlqual > 20){symbol = "0)";}
  if(wlqual > 40){symbol = "0))";}
  if(wlqual > 60){symbol = "0)))";}
  if(wlqual > 80){symbol = "0))))";}
  return symbol;
}

// Displays a WLAN field strength quality in %
int wlanquality(){
  float fieldstr = float(WiFi.RSSI());
  if(fieldstr > 0){
    fieldstr = -100.0;
  }
  int wlqual = 100  - (((fieldstr * -1) - 50) * 2);
  if(wlqual < 0){
    wlqual = 0;
  }
  if(wlqual > 100){
    wlqual = 100;
  }
  return wlqual;
}

// Truncate a float number 23.234 -> 23.2
float truncate1(float value){
  float result = roundf(value * 10) / 10;
  return result;
}

// Truncate a float number 23.234 -> 23.23
float truncate2(float value){
  float result = roundf(value * 100) / 100;
  return result;
}

// Flash LED for x ms
void flashLED(int duration){
 digitalWrite(ledPin, LOW);   // On (Low activ)
 delay(duration);
 digitalWrite(ledPin, HIGH);  // Off
}

String transID(){
  transactionID = String(random(0, 99999999));    // Generate a random transaction ID, global defined

  return transactionID;
}

String cryptPassword(String password){
  MD5Builder md5;
  md5.begin();
  raw = password + transactionID;
  md5.add(raw);
  md5.calculate();
  crypt = md5.toString();
  DebugPrintln(3, "Crypt password");
  DebugPrint(3, "Password: ");
  DebugPrintln(3, password);
  DebugPrint(3, "Transaction ID: ");
  DebugPrintln(3, transactionID);
  DebugPrint(3, "Raw Data: ");
  DebugPrintln(3, raw);
  DebugPrint(3, "MD5 Hash: ");
  DebugPrintln(3, crypt);
  // Give back the crypted password
  return crypt;
}

int encryptPassword(String password, String md5hash){
  MD5Builder md5;
  md5.begin();
  raw = password + transactionID;
  md5.add(raw);
  md5.calculate();
  crypt = md5.toString();
  DebugPrintln(3, "Encrypt password");
  DebugPrint(3, "Password: ");
  DebugPrintln(3, password);
  DebugPrint(3, "Transaction ID: ");
  DebugPrintln(3, transactionID);
  DebugPrint(3, "Raw Data: ");
  DebugPrintln(3, raw);
  DebugPrint(3, "MD5 Hash: ");
  DebugPrintln(3, crypt);
  DebugPrint(3, "MD5 Hash2: ");
  DebugPrintln(3, crypt);
  // Compare the received hash
  if(crypt == md5hash){
    return 1;
  }
  else{
    return 0;
  }
}
#endif
