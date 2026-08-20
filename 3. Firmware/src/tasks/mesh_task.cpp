#include "mesh_task.h"

#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "config.h"

namespace {

void meshTaskFn(void *pvParameters) {
    // TODO: bring up radio, run Meshtastic (or custom) protocol stack,
    // update sharedState as mesh state changes.
    for (;;) {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

}  // namespace

void meshTaskStart() {
    xTaskCreatePinnedToCore(
        meshTaskFn,
        "mesh_task",
        MESH_TASK_STACK,
        nullptr,
        MESH_TASK_PRIORITY,
        nullptr,
        MESH_TASK_CORE
    );
}
