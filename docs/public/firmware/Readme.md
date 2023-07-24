**20230724 firmware_V1.18.wsb `(stable)`**

* Repository changed from GitLab to GitHub
* Gitpod integration
* Temperature compensation for DS18B20
* Supports wind sensor PCB Yachta 2.0 with new magnetic rotation sensor MT6701 
* WLAN default settings (SSID: NoWa, Pass: 12345678, IP: 192.168.4.1)

`Attention! After update changes all settings to default values. Please renew the settings.`

**20220906 firmware_V1.17.wsb `(old)`**

* Fix for calibration
* WLAN default settings (SSID: NoWa, Pass: 12345678, IP: 192.168.4.1)

**20220901 firmware_V1.16.wsb `(old)`**

* Fix for negativ wind speed when using calibration
* Fix libs for compiling  with arduino IDE 1.8.19
* Modification for longer passwords with special character
* WLAN default settings (SSID: NoWa, Pass: 12345678, IP: 192.168.4.1)

**20220520 firmware_V1.15.wsb `(old)`**

* Fix for wind direction offset (hanging values)
* Fix for calibration (eliminates negativ values to zero)
* WLAN default settings (SSID: NoWa, Pass: 12345678, IP: 192.168.4.1)

**20210910 firmware_V1.14.wsb `(old)`**

* Support for new PCB for wind sensor Yachta
* 1Wire pin canged from GPIO15 to GPIO12 (new PCB)
* WLAN default settings (SSID: NoWa, Pass: 12345678, IP: 192.168.4.1)

`Attention! No support for old PCB from Udo for wind sensor Yachta.`

**20210827 firmware_V1.13.wsb `(old)`**

* Support for modifyed wind sensor Ventus W132
* New values for device informations page
* New values for Wind Values page
* Support BME280 and DS18B20
* New NMEA0183 custom telegram WSE for BME280
* Solved problem for TCP telegram transmission (remove CR for unselected telegrams)
* WLAN default settings (SSID: NoWa, Pass: 12345678, IP: 192.168.4.1)

**20210819 firmware_V1.12.wsb `(old)`**

* Secure function for autopilot (limit and reduce jumping measured values)
* WLAN default settings (SSID: NoWa, Pass: 12345678, IP: 192.168.4.1)

**20210811 firmware_V1.11.wsb `(old)`**

* Fix for hanging I2C bus if the AS5600 is not present by WiFi1000 wind sensor
* Limit jumping direction values by using AS5600
* Rename the wind sensor types and add two new sensors:
	old: (NOWA1000|Udo1|Udo2)
	new: (WiFi1000|Yachta|Jukolein|Davis|Ventus)
* Using different speed calculations for different wind sensor types (radius)
* Using pictograms for wind values
* WLAN default settings (SSID: NoWa, Pass: 12345678, IP: 192.168.4.1)
* `Needs new Android App!`

`Attention! After update changes all settings to default values. Please renew the settings.`

**20210805 firmware_V1.10.wsb `(critical)`**

* Add two new wind sensor types ([Yachta](https://www.thingiverse.com/thing:2261719) and [Jukolein](https://github.com/jukolein/NMEA0183-Windsensor))
* WLAN default settings (SSID: NoWa, Pass: 12345678, IP: 192.168.4.1)

**20210501 firmware_V1.09.wsb `(old)`**

* CPU speed changed from 80 MHz to 160 MHz for more performance
* nDNS service added for NMEA0183 ZeroConfig with AVnav
* Hostmane support fixed
* WLAN default settings (SSID: NoWa, Pass: 12345678, IP: 192.168.4.1)

`Attention! After update changes all settings to default values. Please renew the settings.`

**20210325 firmware_V1.08.wsb `(old)`**

* Downwind values now correct
* Diagnostic Mode fixed
* Average building fixed

**20200711 firmware_V1.07.wsb `(old)`**

* Boot problem fixed by wind speed higher 4bft (Boot Loop)
* Elektronic tested until 180km/h wind speed with sysntetic signals
* Direction accuracy 10x improved. Now is accuracy by 1° for 12bft or 78kn wind speed
* Display problem fixed for negativ wind direction in Canvas Steel instrument
* New parameter added for WiFi channel setting (1...13)
* WiFi connections reduced from 4 to 2 clients for better performance 
* WLAN default settings (SSID: NoWa, Pass: 12345678, IP: 192.168.4.1)

`Attention! After update changes all settings to default values. Please renew the settings.`


**20200427 firmware_V1.06.wsb `(old)`**

* Firmware update changed (GitLab download now available)
* For SSID special characters added (A..z, 0..9, _-)
* WLAN indicator for connection quality fixed
* WLAN default settings (SSID: NoWa, Pass: 12345678, IP: 192.168.4.1)

`Attention! After update changes all settings to default values. Please renew the settings.`


**20190928 firmware_V1.05.wsb `(old)`**

* Using the actual Espressif SDK 2.2.1(cfd48f3)
* Restart now available via Web configuration
* Firmware update changed (GitLab download has been removed)
* New feature! Added a new calibration function for wind speed
* New feature! Added password for configuration pages (default: 12345678)
* WLAN default settings (SSID: NoWa, Pass: 12345678, IP: 192.168.4.1)
* Diagnostic Mode fixed (No connection and answare from wind sensor by using newer web browser)

`Attention! After update changes all settings to default values. Please renew the settings.`

**20190428 firmware_V1.04.wsb `(old)`**

* Reset start values for speed and direction after reboot (eleminate start spikes)
* Link problem in HTML error page 404 solved
* JSON string for ServerMode fixed (before string, after int)
* New feature! Oscilloscope function included
* New JSON device created for oscilloscope data sending
* Diagnostic Mode activated (starts the oscilloscope function, usable with external Diagnostic Tool)
* Pulse Counter added in Device Info page (count the pulse per revolution for the direction Hall sensor)
* New complex instrument added when true wind selected (instrument with full degree scale and cardinal points, without sections, useful for Weather Station Mode)

**20190424 firmware_V1.03.wsb `(old)`**

* Fixing the wind speed problem by slow winds
* Fixing the wind speed problem for bft unit (uncorrect calculation)
* Fixing the wind speed problem for m/s and km/h in Demo Mode (missing values)
* Fixing WLAN connection quality for Demo Mode (if no connection then uncorrect values )
* Adding in Web configuration a new parameter "Connection Timeout" (solved the start problem with OpenPlotter)
* Styling changed in page "Settings"

`Attention! After update changes all settings to default values. Please renew the settings.`

**20190220 firmware_V1.02.wsb `(old)`**

* Blinking text in demo mode fixed (red syle)
* Individual help text depends on firmware version

**20190220 firmware_V1.01.wsb `(old)`**

* Problem with average setting solved (now updating directly)
* Average value 10 now usable
* Info message in Demo Mode for Instrument page and Device Info page
* Offset for wind direction inserted (new feature)
* Two step update not more necessary
* Any english messages changed

**20190217 firmware_V1.00.wsb `(old)`**

* First actual firmware V1.00
* Critical WLAN settings solved (now checking all input values)
* Implement online update function via GitLab
* SSID: MyBoat
* Pass: S6587rr94P

