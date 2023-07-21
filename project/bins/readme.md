**20230331 firmware_V1.06.bmb `(actual)`**

* Fix for DS18B20
* WLAN default settings (SSID: NoWa, Pass: 12345678, IP: 192.168.4.1)

**20230312 firmware_V1.05.bmb `(old)`**

* Add boot screen
* Add VE.Direct read and write
* Support for Victron devices with VE.Direct port
* Add NMEA0183 sentences for VE.Direct
* Fix for wrong GPS informations
* Cyclic updating of all information on the OLED display
* Add separate task for LoRa functions
* Stable Web sites
* Project changed from GitLab to GitHub
* WLAN default settings (SSID: NoWa, Pass: 12345678, IP: 192.168.4.1)

`Attention! After update changes all settings to default values. Please renew the settings.`

**20221119 firmware_V1.03.bmb `(old)`**

* Fixing hanging GPS data
* Fixing hanging telegram counter
* Fixing a lot of other bugs
* Validate checksum for NMEA0183 GPS Data and validate RMC content for China fake GPS modul with wrong telegrams
* Add a checksum for TTN upload messages
* Add NMEA0183 output on port 6666 for measuring and GPS values
* All measuring values update permantent on OLED
* Support TTN V3 (TTS)
* WLAN default settings (SSID: NoWa, Pass: 12345678, IP: 192.168.4.1)

`Attention! After update changes all settings to default values. Please renew the settings.`


**20210616 firmware_V1.01.bmb `(old)`**

* Add page for device info, LoRa info and sensor values
* WLAN default settings (SSID: NoWa, Pass: 12345678, IP: 192.168.4.1)

`Attention! After update changes all settings to default values. Please renew the settings.`


**20210530 firmware_V1.00.bmb `(old)`**

* Initial firmware with limited functionality (only settings, no view for measuring results)
* WLAN default settings (SSID: NoWa, Pass: 12345678, IP: 192.168.4.1)
