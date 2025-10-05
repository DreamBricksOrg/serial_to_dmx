# Serial to DMX (forked from DMX512Tools)

### target devices
 - M5Stack BASIC / GRAY / GO / FIRE
 - M5Stack Core2

### Required Libraries
 - [esp_dmx](https://github.com/someweisguy/esp_dmx/)
 - [M5Unified](https://github.com/M5Stack/M5Unified/)
 - [M5GFX](https://github.com/M5Stack/M5GFX/)

### Code Overview
- `serial_to_dmx.ino` – minimal Arduino sketch that delegates to the PlatformIO
  `src` directory so the project works in both build systems.
- `src/src.cpp` – initializes the M5 device, configures the DMX interface and
  drives the top-level scene selection between receiver and sender modes.
- `src/common.h` – shared definitions such as DMX configuration constants,
  FreeRTOS queue handle, color table, and lightweight UI helpers for buttons
  and views.
- `src/view_receiver.h` – implements the DMX monitor, reading packets from the
  queue and rendering both bar graph and console views of channel activity.
- `src/view_sender.h` – provides the interactive DMX transmitter with channel
  selection, value adjustment controls, and packet updates.
- `src/logo_sender.h` – sprite data used to decorate the sender interface.

