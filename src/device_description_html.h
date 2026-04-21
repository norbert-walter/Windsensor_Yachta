String DeviceDescription()
{
    DebugPrintln(3, "Send device_description.json");

    static const char kDeviceDescriptionTemplate[] PROGMEM = R"json({
  "schema_version": "1.0",
  "device_id": "windsensor-0",
  "device_type": "wind_sensor_yachta_21",
  "title": "Wind Sensor Yachta 2.1",
  "summary": "Wind snesor Yachta is a anemometer to measure wind speed, wind direction and device temperature",
  "endpoint": "http://192.168.5.1",
  "actions": [
    {
      "name": "state",
      "access": "read",
      "description": "Read all device setting data and measuring data",
      "method": "GET",
      "path": "/json",
      "safe": true,
      "idempotent": true,
      "returns": {
        "format": "json",
        "example": {
          "SensorType": "Yachta 2.0"
        }
      }
    },
    {
      "name": "set_offset",
      "access": "write",
      "description": "Set offset (int) for wind angle sensor in range of [-180...+180°].",
      "method": "GET",
      "path": "/settings?offset=-13",
      "safe": true,
      "idempotent": true,
      "returns": "none"
    },
    {
      "name": "set_average",
      "access": "write",
      "description": "Set value (int) for sliding average. Range [1...10].",
      "method": "GET",
      "path": "/settings?average=2",
      "safe": true,
      "idempotent": true,
      "returns": "none"
    },
    {
      "name": "set_speed_unit",
      "access": "write",
      "description": "Set the speed unit as [m/s|km/h|kn|bft].",
      "method": "GET",
      "path": "/settings?speedUnit=kn",
      "safe": false,
      "idempotent": true,
      "returns": "none"
    }
  ],
  "rules": [
    "Use only the listed actions.",
    "Do not generate free commands or URLs.",
    "Execute write actions only at the explicit user request.",
    "Read state after setting values and compare the result.",
    "Do not use reset, restart, backlog, or firmware commands.",
    "Execute only one action at a time.",
    "Do not guess alternative commands if the response is unexpected."
  ]
})json";

    String content = FPSTR(kDeviceDescriptionTemplate);
    return content;
}
