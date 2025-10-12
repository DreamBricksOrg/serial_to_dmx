# Serial to DMX (forked from DMX512Tools)

## Overview
Serial to DMX bundles the original DMX512Tools sketches into a single
PlatformIO project that also remains compatible with the Arduino IDE via a
minimal wrapper sketch. The runtime configures the ESP32 DMX driver, allocates
an event queue, and dynamically selects the correct UART pins for different
M5Stack boards so the same firmware runs on Core, Core2, and CoreS3 hardware
without code changes.【F:src/src.cpp†L37-L70】

The application presents two scenes:

- **DMX Receiver** – listens for DMX packets, renders a live bar graph of all
  visible channels, and logs activity or errors to a scrolling console.
  Touching the lower half of the display or pressing BtnB toggles between the
  console and a strip-chart style graph view.【F:src/view_receiver.cpp†L7-L121】
- **DMX Sender** – exposes all 512 channels in a touch grid with hardware button
  shortcuts for channel selection and value entry. A dedicated slider and
  up/down controls adjust the active channel, while serial input can stream
  comma-separated values to update successive channels in bulk.【F:src/view_sender.cpp†L9-L208】【F:src/view_sender.cpp†L209-L318】【F:src/view_sender.cpp†L319-L470】

By default the firmware boots directly into sender mode thanks to the
`START_IN_SENDER_MODE` flag, but the receiver scene remains available via the
mode selector when the flag is removed or when a scene exits back to the
selector.【F:src/src.cpp†L9-L107】

## Supported Hardware
- M5Stack BASIC / GRAY / GO / FIRE
- M5Stack Core2
- M5Stack CoreS3 / CoreS3 SE

Board-specific pin assignments for the DMX transceiver are set up
automatically at runtime; no manual wiring changes or reconfiguration is
required when moving the binary between supported devices.【F:src/src.cpp†L37-L70】

## Building
The project targets the ESP32 Arduino framework.

- **PlatformIO** – `platformio.ini` includes ready-to-use environments for the
  latest Espressif32 toolchains as well as older Arduino cores. Running
  `pio run` builds the firmware and `pio run -t upload` flashes it to the
  connected device.【F:platformio.ini†L1-L29】
- **Arduino IDE** – the root `serial_to_dmx.ino` sketch simply delegates to the
  `src` directory so the codebase remains accessible to the Arduino build
  system.【F:serial_to_dmx.ino†L1-L3】

Install the following libraries before building:

- [esp_dmx](https://github.com/someweisguy/esp_dmx/)
- [M5Unified](https://github.com/M5Stack/M5Unified/)
- [M5GFX](https://github.com/M5Stack/M5GFX/)

These dependencies are also declared in `platformio.ini` for automatic
retrieval when using PlatformIO.【F:platformio.ini†L18-L25】

## Using the Application
1. **Boot & Select Mode** – With `START_IN_SENDER_MODE` enabled the sender scene
   appears immediately. If you build without the flag or return to the selector,
   tap the on-screen buttons or use BtnA/BtnC to highlight a choice and BtnB to
   confirm.【F:src/src.cpp†L15-L106】
2. **Sender Controls**
   - Tap a channel tile to focus it, or use BtnA/BtnC to step through channels.
   - Enter value mode with BtnB or a second tap, then drag the slider, tap the
     +/- buttons, or hold BtnA/BtnC for fine adjustments.
   - Stream values over USB by sending newline-terminated lists of integers;
     the firmware parses each token, clamps it to 0–255, and writes the updated
     packet to the DMX bus.【F:src/view_sender.cpp†L55-L208】【F:src/view_sender.cpp†L209-L318】
3. **Receiver View**
   - Observe channel levels in the top bar chart; values are color-coded and
     labelled with both channel and hexadecimal intensity.
   - Press BtnB or tap the console region to toggle between the textual console
     and a scrolling history graph of channel changes.【F:src/view_receiver.cpp†L18-L121】

Both scenes double-buffer DMX packets so updates remain responsive without
tearing, and they reuse common UI helpers for button rendering and color
selection defined in `common.h`.【F:src/view_sender.cpp†L103-L153】【F:src/view_receiver.cpp†L71-L121】【F:src/common.h†L1-L58】
