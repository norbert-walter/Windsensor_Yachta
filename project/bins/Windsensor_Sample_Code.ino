//************************************************
// Windsensor with two hall sensors and ESP8266
//
// Tested with Arduino 1.8.5
// Norbert Walter (C) 2018
//
// Output via serial line with 115200Bd 8N1
//************************************************

#include <Ticker.h>
 
#define INT_PIN1 5          // Hall sensor wind speed D1, GPIO 5
#define INT_PIN2 4          // Hall sensor wind direction D2, GPIO 4
 
int marker1 = 0;            // Wind speed
int marker2 = 0;            // Wind direction
int icounter = 0;           // Interrupt counter for rotation detection
int icounterold = 0;        // Old interrupt counter for rotation detektion
unsigned long counter1;     // Wind spped
unsigned long counter2;     // Wind direction
float time1;                // Wind speed (time in [ms] for one rotation)
float time2;                // Wind direction (time in [ms] between wind speed sensor and wind direction sensor)
float radius = 0.06;        // Radius between center and middle of half hemisphere position
float lamda = 0.3;          // Lambda is a constant for amemometer type with 3 hemisphere, lamda = 0,3
float pi = 3.14159265359;   // Pi constant
float windspeed_hz;         // Wind speed in [Hz]
float windspeed_mps;        // Wind speed in [m/s]
float windspeed_kn;         // Wind speed in [kn]
float windspeed_kph;        // Wind speed in [km/h]
int windspeed_bft;          // Wind speed in [bft]
float term3;                // 3te term
float term2;                // 2te term
float term1;                // 1te term
float winddirection;        // Wind direction [°] in relation to midle of ship line (midle = 0°)
float dirresolution;        // Resolution of wind direction [°]
 
Ticker Timer;
 
// Interrupt routine for wind speed
void interruptRoutine1() {
  if(marker1 == 0){
    time1 = float(counter1);
    time2 = float(counter2);
    counter1 = 0;
    counter2 = 0;
    marker1 = 1;
    marker2 = 1;
    icounter += 1;
  }
  else{
    marker1 = 0;
  }
}
// Interrupt routine for wind direction
void interruptRoutine2() {
  marker2 = 0;
}

// 1ms counter
void counter() {
  if(marker1 == 1){
    counter1 += 1;
   }
  if(marker2 == 1){
    counter2 += 1;
   }
} 
 
void setup()
{
 
  pinMode(INT_PIN1, INPUT_PULLUP);
  pinMode(INT_PIN2, INPUT_PULLUP);
  
  Serial.begin(115200);
  Timer.attach_ms(1, counter);     // Start timer function "counter" each 1ms
 
 
  // Start interrupts
  attachInterrupt(INT_PIN1, interruptRoutine1, FALLING);
  attachInterrupt(INT_PIN2, interruptRoutine2, FALLING);

}
 
void loop()
{
 // time1 = time in [ms] for one rotation
 // time2 = time in [ms] between wind speed sensor and wind direction sensor
 if(time1 == 0.0){
  time1 = 0.0001;
 }
 // Wind direction dir[°] = time2[ms] / time1[ms] / 2 *360
 winddirection = time2 / time1 * 360;
 // Wind direction resolution res[°] = 360 / time2[ms]
 dirresolution = 360 / time1;
 if(dirresolution > 20.0){
  dirresolution = 0.0;
 }
 // Wind speed n[Hz] = 1 / time1[ms] *1000
 windspeed_hz = 1.0 / time1 * 1000;
 // If rotation off then windspeed_hz = 0
 if(icounter == icounterold){
  windspeed_hz = 0.0;
 }
 icounterold = icounter;
 // Wind speed, v[m/s] = (2 * Pi * n[Hz] * r[m]) / lamda[1]
 windspeed_mps = (2 * pi * windspeed_hz * radius) / lamda;
 // Wind speed, v[kn] = v[m/s] * 1.94384
 windspeed_kn = windspeed_mps * 1.94384;
 term3 = 0.0000222 * windspeed_kn;
 term3 *= windspeed_kn;
 term3 *= windspeed_kn;
 term2 = 0.0034132 * windspeed_kn;
 term2 *= windspeed_kn;
 term1 = 0.2981666 * windspeed_kn;
 // Wind speed v[bft] = 0.0000222 * v³[kn] - 0.0034132 * v²[kn] + 0.2981666 * v[kn] + 0.1467082
 windspeed_bft = int(term3 - term2 + term1 + 0.1467082);
 // Limiting wind speed for bft lower than 12
 if(windspeed_bft > 12){
  windspeed_bft = 12;
 }
 Serial.print(digitalRead(INT_PIN1)); 
 Serial.print("SS ");
 Serial.print(digitalRead(INT_PIN2));
 Serial.print("WS ");
 Serial.print(time1); 
 Serial.print("ms ");
 Serial.print(time2);
 Serial.print("ms ");
 Serial.print(winddirection);
 Serial.print("° ");
 Serial.print(dirresolution);
 Serial.print("° ");
 Serial.print(windspeed_hz);
 Serial.print("Hz ");
 Serial.print(windspeed_mps);
 Serial.print("m/s ");
 Serial.print(windspeed_kn);
 Serial.print("kn ");
 Serial.print(windspeed_bft);
 Serial.print("bft ");
 Serial.println("");
 delay(1000); 
}
