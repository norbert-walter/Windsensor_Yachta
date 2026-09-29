# Copilot-Chat: Python-Umgebung und Chat-Sicherung

## Python und `run`

Das Shell-Skript `run` installiert `esptool` und PlatformIO mit `pip3` und kompiliert anschließend die Firmware. Auf dem verwendeten Debian-13-System fehlten zunächst `python3` und damit auch `pip3`.

Nach Installation von Python, pip und venv lässt sich eine virtuelle Umgebung im Projekt mit folgendem Befehl erstellen:

```bash
python3 -m venv .venv
```

Das ist normalerweise einmal nötig, solange der Ordner `.venv` erhalten bleibt. Nach einem neuen Terminal muss die Umgebung aktiviert werden:

```bash
source .venv/bin/activate
```

Wird der Workspace neu erstellt und `.venv` dabei gelöscht, muss sie neu angelegt werden.

## Copilot-Chat sichern

Copilot-Chats werden nicht automatisch im Projektordner gespeichert. Für eine dauerhafte Projektnotiz können wichtige Nachrichten oder Zusammenfassungen als Markdown im Projekt abgelegt werden. Diese Datei liegt unter `docs/chats/copilot-chat.md`.

Vor dem Commit prüfen, dass keine vertraulichen Informationen wie Tokens oder Passwörter enthalten sind.
