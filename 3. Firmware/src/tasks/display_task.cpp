#include "display_task.h"

#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "config.h"
#include "shared_state.h"
#include "ui/ui.h"

namespace {
SPIClass tftSPI(HSPI);
Adafruit_ST7789 tft(&tftSPI, TFT_CS, TFT_DC, TFT_RST);

void initDisplay() {
    if (TFT_BL >= 0) {
        pinMode(TFT_BL, OUTPUT);
        digitalWrite(TFT_BL, HIGH);
    }

    tftSPI.begin(TFT_SCLK, TFT_MISO, TFT_MOSI, TFT_CS);
    tft.init(TFT_WIDTH, TFT_HEIGHT);
    tft.setSPISpeed(TFT_SPI_HZ);
    tft.setRotation(TFT_ROTATION);
    tft.fillScreen(ST77XX_BLACK);
}

void displayTaskFn(void *pvParameters) {
    initDisplay();
    ui::begin(tft);

    TickType_t lastWake = xTaskGetTickCount();
    const TickType_t frameInterval = pdMS_TO_TICKS(DISPLAY_FRAME_INTERVAL_MS);

    NodeState state;

    for (;;) {
        sharedState.read(state);

        ui::render(tft, state);

        vTaskDelayUntil(&lastWake, frameInterval);
    }
}

}  // namespace

void displayTaskStart() {
    xTaskCreatePinnedToCore(
        displayTaskFn,
        "display_task",
        DISPLAY_TASK_STACK,
        nullptr,
        DISPLAY_TASK_PRIORITY,
        nullptr,
        DISPLAY_TASK_CORE
    );
}
