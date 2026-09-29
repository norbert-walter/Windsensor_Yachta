## Plan: MQTT-Telemetrie integrieren

MQTT im vorhandenen Server-Modus `2` als exklusiven Telemetrie-Ausgang ergänzen. Brokerdaten werden über die Web-Einstellungen verwaltet; Messwerte gehen in einem kompakten JSON-Payload an ein sensorindividuelles Topic. Verbindungsaufbau und Publish müssen nicht-blockierend bleiben, damit Messwerterfassung, HTTP-Konfiguration und MQTT-Keepalive weiterlaufen.

**Schritte**
1. MQTT-Client-Bibliothek für ESP8266 (voraussichtlich PubSubClient) als PlatformIO-Abhängigkeit aufnehmen und Broker-Client mit `WiFiClient` anlegen.
2. Brokerkonfiguration ergänzen: Host, Port, optionaler Benutzername und Passwort als Felder in `configData`; EEPROM-Strukturversion erhöhen und beim Booten bestehende Konfigurationen migrieren, statt sämtliche Nutzereinstellungen durch neue Defaults zu ersetzen. `settings_html.h` und `Settings()` um Eingabe und Validierung ergänzen.
3. Zugangsdaten nicht über die bestehende GET-Übergabe von `/settings` senden: Formular/Handler für diese Speicherung auf POST umstellen oder GET für übrige Einstellungen beibehalten und Broker-Zugangsdaten separat per POST übernehmen. Passwort nicht unnötig im Formular als Klartext vorbelegen. Hinweis: HTTP und EEPROM bleiben ohne zusätzliche Maßnahmen unverschlüsselt.
4. `WiFi_Windsensor.cpp`: Brokerparameter setzen, Verbindung nach vorhandener WLAN-Verbindung herstellen und Reconnect mit `millis()`-Backoff statt blockierender Dauerschleife ausführen. MQTT-Protokollpflege muss im äußeren `loop()` und auch in der bestehenden wartenden TCP-Client-Schleife stattfinden; andernfalls kann `mqttClient.loop()` verhungern.
5. Bei `serverMode == 2` nur MQTT publizieren. Kleines JSON-Payload für Windrichtung/-geschwindigkeit und konfigurierte optionale Temperatur-/Umweltdaten auf ein eindeutiges Topic wie `windsensor/<sensorID>/telemetry`; dafür stabile Snapshot-Werte aus den globalen Messgrößen verwenden und die MQTT-Paketgrößenbegrenzung berücksichtigen. Publish-Takt zunächst an den vorhandenen normalen/reduzierten Sendetakten ausrichten.
6. Verbindungsstatus und Fehler knapp über vorhandenes Debug-Logging ausgeben; bei nicht verfügbarem Broker Sensorberechnung, Webserver und andere Betriebsmodi unbeeinträchtigt lassen.

**Relevante Dateien**
- `/home/coder/Windsensor_Yachta/platformio.ini` — MQTT-Bibliothek hinzufügen.
- `/home/coder/Windsensor_Yachta/src/WiFi_Windsensor.cpp` — Clientinitialisierung, Reconnect, Loop-Service und Publish im Modus 2.
- `/home/coder/Windsensor_Yachta/src/Configuration.h` — persistente Brokerfelder und Konfigurationsversionsnummer.
- `/home/coder/Windsensor_Yachta/src/FunctionsLib.h` — EEPROM-Laden/Speichern; vorhandene Implementierung liest/schreibt das gesamte Struct.
- `/home/coder/Windsensor_Yachta/src/settings_html.h` — Broker-Eingaben und Update der Settings.
- `/home/coder/Windsensor_Yachta/src/ServerPages.h` — HTTP-Methode/Handler für sichere Übermittlung der Brokerdaten.
- `/home/coder/Windsensor_Yachta/src/Definitions.h` — aktuelle globale Messwerte und Sendetimer/Flags als Quelle für das Payload und Publishintervall.

**Verifikation**
1. PlatformIO-Build für `d1_mini` ausführen.
2. Mit MQTT-Broker testen: Verbindung/Authentifizierung, Topic und JSON-Payload, aktiver und ruhender Wind, optionale Sensorwerte sowie `serverMode == 2`.
3. Broker-Ausfall/Neustart testen: Firmware bleibt responsiv, reconnectet begrenzt und MQTT-Keepalive bleibt bei einem verbundenen TCP-Client aktiv.
4. Bestehende EEPROM-Konfiguration mit neuer Firmware laden und sicherstellen, dass alte WLAN-/Sensor-Einstellungen erhalten bleiben; danach Brokerdaten speichern und Neustartpersistenz prüfen.
5. Modus 0, 1, 3 und 4 smoke-testen, um unveränderte HTTP/NMEA-, Diagnose- und Demo-Funktionen sicherzustellen.

**Entscheidungen**
- Vom Nutzer gewählt: Brokerkonfiguration in der Web-Einstellungsseite; gemeinsames JSON-Paket; MQTT exklusiv in Server-Modus 2.
- Angenommen: ausgehende Telemetrie ohne MQTT-Subscriptions oder Remote-Steuerung; QoS 0 genügt zunächst; Topic enthält die `sensorID`.
- Sicherheit: Broker-Passwort darf nicht in GET-URLs erscheinen. HTTP/EEPROM-Verschlüsselung und TLS zum Broker sind nicht im Basisumfang und müssen bei Anforderungen an Schutz außerhalb des lokalen Netzes separat festgelegt werden.