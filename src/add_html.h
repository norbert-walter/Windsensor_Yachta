String DeviceDescriptionHTML()
{
    DebugPrintln(3, "Send device_description.html");

    static const char HTMLTemplate1[] PROGMEM = R"html(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>ADD – AI Device Description</title>

    <style>
        body {
            font-family: system-ui, sans-serif;
            max-width: 860px;
            margin: 2rem auto;
            padding: 0 1rem;
            color: #1a1a1a;
        }

        h1 {
            font-size: 1.4rem;
            margin-bottom: 0.25rem;
        }

        .meta {
            color: #555;
            font-size: 0.9rem;
            margin-bottom: 1.5rem;
        }

        .meta a {
            color: #0066cc;
        }

        pre {
            background: #f4f4f4;
            border: 1px solid #ddd;
            border-radius: 6px;
            padding: 1.2rem;
            overflow-x: auto;
            font-size: 0.85rem;
            line-height: 1.5;
            white-space: pre-wrap;
        }

        .badge {
            display: inline-block;
            background: #0066cc;
            color: white;
            border-radius: 4px;
            padding: 2px 8px;
            font-size: 0.8rem;
            margin-left: 0.5rem;
        }
    </style>
</head>

<body>

    <h1>
        AI Device Description (ADD)
        <span class="badge">Level 2</span>
    </h1>

    <p class="meta">
        Device: <strong>Wind Sensor Yachta V2.1</strong>
        &nbsp;|&nbsp;
        Schema: ADD v1.0
        &nbsp;|&nbsp;
        <a href="https://norbert-walter.github.io/ai-device-description-add/ADD_AI_Reference_v1_0.html"
           target="_blank">Specification</a>
        &nbsp;|&nbsp;
        <a href="/add">Raw JSON</a>
    </p>

    <pre id="add-json">
)html";

    static const char HTMLTemplate2[] PROGMEM = R"html(
    </pre>

</body>
</html>
)html";

    String json = FPSTR(kDeviceDescriptionTemplate);

    // Escape the JSON for safe display inside HTML
    json.replace("&", "&amp;");
    json.replace("<", "&lt;");
    json.replace(">", "&gt;");

    String content;

    content.reserve(
        strlen_P(HTMLTemplate1) +
        json.length() +
        strlen_P(HTMLTemplate2)
    );

    content += FPSTR(HTMLTemplate1);
    content += json;
    content += FPSTR(HTMLTemplate2);

    return content;
}