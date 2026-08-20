#pragma once

// =============================================================================
// config.h — central place for pin mapping, task sizing, and node identity.
// Edit the DISPLAY PINS section to match your actual wiring.
// =============================================================================

// ---------------------------------------------------------------------------
// Node identity (placeholder — will matter once Meshtastic is integrated)
// ---------------------------------------------------------------------------
#define NODE_NAME "META-NODE-01"

// ---------------------------------------------------------------------------
// Display: ST7789V TFT, driven over SPI
// ---------------------------------------------------------------------------
// Adjust these to match your wiring. Values below are a common default for
// ESP32-S3 dev boards with the display on the "default" VSPI-ish pins.
#define TFT_SCLK   13
#define TFT_MOSI   12
#define TFT_MISO   -1      // not used by most ST7789 modules
#define TFT_CS     14
#define TFT_DC      15
#define TFT_RST     11
#define TFT_BL      -1      // backlight, set -1 if tied directly to 3V3

// Panel geometry — common ST7789V modules are 240x240 or 240x320.
#define TFT_WIDTH   240
#define TFT_HEIGHT  320
#define TFT_ROTATION 0

// SPI clock for the panel
#define TFT_SPI_HZ  40000000UL

// ---------------------------------------------------------------------------
// Future peripherals (not wired up yet — placeholders for pin planning)
// ---------------------------------------------------------------------------
// GPS (e.g. UART NMEA module)
#define GPS_RX_PIN      17
#define GPS_TX_PIN      18
#define GPS_BAUD        9600

// User input (buttons / rotary encoder — adjust to your hardware)
#define BTN_UP_PIN      4
#define BTN_DOWN_PIN    5
#define BTN_SELECT_PIN  6

// ---------------------------------------------------------------------------
// FreeRTOS task sizing
// ---------------------------------------------------------------------------
// ESP32-S3 is dual-core (PRO_CPU = 0, APP_CPU = 1). Arduino's loop() and
// WiFi/BT stack normally run on core 1, so we pin the display task there too
// (it's not timing critical relative to core 0) and leave core 0 free for
// future radio/mesh work, which tends to be latency sensitive.
#define DISPLAY_TASK_STACK      (4 * 1024)
#define DISPLAY_TASK_PRIORITY   2
#define DISPLAY_TASK_CORE       1

#define SYSTEM_TASK_STACK       (2 * 1024)
#define SYSTEM_TASK_PRIORITY    1
#define SYSTEM_TASK_CORE        1

// Reserved for when GPS/input/mesh tasks are wired in:
#define GPS_TASK_STACK          (3 * 1024)
#define GPS_TASK_PRIORITY       3
#define GPS_TASK_CORE           0

#define INPUT_TASK_STACK        (2 * 1024)
#define INPUT_TASK_PRIORITY     3
#define INPUT_TASK_CORE         1

#define MESH_TASK_STACK         (8 * 1024)
#define MESH_TASK_PRIORITY      4
#define MESH_TASK_CORE          0

// Target UI frame interval (ms). 33ms ≈ 30fps — plenty for a status UI.
#define DISPLAY_FRAME_INTERVAL_MS  33
