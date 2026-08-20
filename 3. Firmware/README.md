# ESP32-S3-N18R8 Metastatic Node — boilerplate

FreeRTOS-based skeleton for a mesh node built around the ESP32-S3 (8MB PSRAM)
and an ST7789V TFT LCD. Right now it only brings up the display so you can
design the UI; other subsystems are scaffolded as stub tasks so they drop
in later without restructuring anything.

## Structure

```
platformio.ini            Build config, board, libs
include/
  config.h                Pin mapping + task stack/priority/core sizing
  shared_state.h           Mutex-guarded NodeState shared across tasks
src/
  main.cpp                 setup()/loop(): creates shared state, starts tasks
  shared_state.cpp          Global SharedState instance
  ui/
    ui.h / ui.cpp           <-- DESIGN THE DISPLAY LOOK HERE
  tasks/
    display_task.h/.cpp     Owns the SPI panel + render loop, calls ui::render()
    system_task.h/.cpp      Heartbeat: updates uptime, prints serial status
    gps_task.h/.cpp          Stub — not started yet
    input_task.h/.cpp       Stub — not started yet
    mesh_task.h/.cpp        Stub — not started yet (Meshtastic goes here)
```

## Why it's laid out this way

- **One task per subsystem**, each pinned to a core and given a priority in
  `config.h`. Display/system run now; GPS/input/mesh are already sized and
  prioritized but not started (commented out in `main.cpp`).
- **`SharedState`** is the only thing tasks share. It's a mutex-protected
  struct (`NodeState`) with `read()` and `update()` helpers — no task talks
  to another task directly, which keeps things sane once GPS, input, and
  Meshtastic are all producing/consuming data at the same time.
- **`ui.cpp` is intentionally decoupled from `display_task.cpp`.** The task
  owns the SPI bus and the timing loop; `ui::render()` just gets a `tft`
  reference and a read-only `NodeState` snapshot every frame. Redesign the
  look by editing `ui.cpp` only — you shouldn't need to touch the task code.

## Before you build

1. **Wiring** — `include/config.h` has placeholder SPI pins for the ST7789V
   (`TFT_SCLK/MOSI/CS/DC/RST/BL`). Update them to match your actual wiring.
2. **Panel size** — defaults to 240x240; change `TFT_WIDTH`/`TFT_HEIGHT` if
   your module is 240x320 (and adjust `TFT_ROTATION` as needed).
3. **Board** — `platformio.ini` targets `esp32-s3-devkitc-1` with QIO octal
   PSRAM (`qio_opi`) and a 16MB flash partition table. Adjust
   `board_upload.flash_size` / `board_build.partitions` if your module's
   flash size differs from what "N18" maps to on your specific board.

## Build / flash

```
pio run -t upload
pio device monitor
```

You should get a black screen with a green node-name header, a live
uptime/status readout, and a blinking dot in the bottom-right corner
confirming the render loop is alive — that's your canvas to redesign.

## Next steps (already scaffolded, not wired in)

- **GPS**: implement `gps_task.cpp` (e.g. with TinyGPS++ over `Serial1` on
  `GPS_RX_PIN`/`GPS_TX_PIN`), then uncomment `gpsTaskStart()` in `main.cpp`.
- **Input**: implement `input_task.cpp` against `BTN_*_PIN` (or swap in an
  encoder library), then uncomment `inputTaskStart()`.
- **Meshtastic**: implement `mesh_task.cpp` around the Meshtastic firmware
  components/library of choice, then uncomment `meshTaskStart()`. It's
  already given the highest task priority in `config.h` since radio timing
  tends to be the most latency-sensitive thing on the node.
