#include "gps_task.h"

#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "config.h"

namespace {

void gpsTaskFn(void *pvParameters) {
    // TODO: Serial1.begin(GPS_BAUD, SERIAL_8N1, GPS_RX_PIN, GPS_TX_PIN);
    // TODO: feed bytes into a NMEA parser (e.g. TinyGPS++) and write
    //       results into sharedState.
    for (;;) {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

}  // namespace

void gpsTaskStart() {
    xTaskCreatePinnedToCore(
        gpsTaskFn,
        "gps_task",
        GPS_TASK_STACK,
        nullptr,
        GPS_TASK_PRIORITY,
        nullptr,
        GPS_TASK_CORE
    );
}
