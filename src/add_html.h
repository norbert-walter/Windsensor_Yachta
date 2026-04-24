// AI Device Description (ADD)
// ADD is helpful in enabling AI to understand and operate devices.

String DeviceDescription()
{
    DebugPrintln(3, "Send device_description.json");

    static const char kDeviceDescriptionTemplate[] PROGMEM = R"json(
{
  "schema_version": "2.0",
  "device_id": "windsensor-0",
  "device_type": "wind_sensor_yachta_21",
  "title": "Wind Sensor Yachta 2.1",
  "summary": "Anemometer measuring wind speed, wind direction and device temperature",

  "role": {
    "primary": "sensor",
    "provides": ["wind_speed", "wind_direction", "temperature"],
    "consumes": [],
    "display": false,
    "gateway": false
  },

  "interfaces": [
    {
      "name": "wifi_nmea",
      "physical": "WiFi",
      "protocol": "NMEA0183",
      "transport": "UDP",
      "port": 2000,
      "direction": "output",
      "data": [
        {
          "sentence": "$WIMWV",
          "description": "Wind speed and angle relative/true",
          "provides": ["wind_speed", "wind_direction"],
          "update_rate_hz": 1
        },
        {
          "sentence": "$PWWST",
          "description": "Device temperature",
          "provides": ["temperature"],
          "update_rate_hz": 1
        }
      ]
    },
    {
      "name": "http_json",
      "physical": "WiFi",
      "protocol": "HTTP",
      "transport": "TCP",
      "port": 80,
      "direction": "bidirectional",
      "data": [
        {
          "path": "/json",
          "description": "All measuring values and device settings",
          "provides": ["wind_speed", "wind_direction", "temperature"]
        }
      ]
    }
  ],

  "security": {
    "network_trust": {
      "model": "local_wifi",
      "remote_mcp_allowed": false,
      "mcp_binding": "localhost"
    },
    "add_protected": false,
    "write_protected": true,
    "authentication": {
      "method": "challenge-response",
      "algorithm": "MD5",
      "input": "MAC+salt",
      "challenge_path": "/auth/challenge",
      "response_path": "/auth/response",
      "registration": {
        "during_add_window_only": true,
        "register_path": "/auth/register",
        "max_clients": 1
      },
      "session": {
        "token_header": "X-Auth-Token",
        "token_lifetime_seconds": 300,
        "extend_path": "/auth/extend"
      }
    },
    "public_actions": ["state"],
    "protected_actions": [
      "set_offset",
      "set_average",
      "set_speed_unit"
    ]
  },

  "add_control": {
    "active": true,
    "timeout_remaining_seconds": 187,
    "extend_path": "/settings?add_extend=true",
    "extend_requires_auth": true,
    "max_extensions": 2,
    "reactivate": "webinterface"
  },

  "actions": [
    {
      "name": "state",
      "access": "read",
      "description": "Read all device settings and measuring data",
      "method": "GET",
      "path": "/json",
      "authentication_required": false,
      "confirmation_required": false,
      "severity": "none",
      "reversible": true,
      "safe": true,
      "idempotent": true,
      "returns": {
        "format": "json",
        "example": {"SensorType": "Yachta 2.0"}
      }
    },
    {
      "name": "set_offset",
      "access": "write",
      "description": "Set offset (int) for wind angle sensor [-180...+180°]",
      "method": "GET",
      "path": "/settings?offset=-13",
      "authentication_required": true,
      "confirmation_required": true,
      "severity": "low",
      "reversible": true,
      "safe": true,
      "idempotent": true,
      "returns": "none"
    },
    {
      "name": "set_average",
      "access": "write",
      "description": "Set sliding average value [1...10]",
      "method": "GET",
      "path": "/settings?average=2",
      "authentication_required": true,
      "confirmation_required": true,
      "severity": "low",
      "reversible": true,
      "safe": true,
      "idempotent": true,
      "returns": "none"
    },
    {
      "name": "set_speed_unit",
      "access": "write",
      "description": "Set speed unit [m/s | km/h | kn | bft]",
      "method": "GET",
      "path": "/settings?speedUnit=kn",
      "authentication_required": true,
      "confirmation_required": true,
      "severity": "low",
      "reversible": true,
      "safe": false,
      "idempotent": true,
      "returns": "none"
    }
  ],

  "rules": [
    "Use only the listed actions.",
    "Do not generate free commands or URLs.",
    "Execute write actions only at explicit user request.",
    "Consult device rules before every write action.",
    "Authenticate before any protected action.",
    "Read state after setting values and compare the result.",
    "Deactivate ADD after successful configuration.",
    "Do not use reset, restart, backlog, or firmware commands.",
    "Execute only one action at a time.",
    "Do not guess alternative commands if the response is unexpected."
  ]
}
  
)json";

    String content = FPSTR(kDeviceDescriptionTemplate);
    return content;
}
