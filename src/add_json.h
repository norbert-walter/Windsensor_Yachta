// AI Device Description (ADD) as JSON answare
// ADD is helpful in enabling AI to understand and operate devices.

String DeviceDescriptionJSON()
{
    DebugPrintln(3, "Send device_description.json");

    // For JSON content refer the central dokument add.h

    String content = FPSTR(kDeviceDescriptionTemplate);
    return content;
}
