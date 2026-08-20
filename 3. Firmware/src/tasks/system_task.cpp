#include "system_task.h"

#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "config.h"
#include "shared_state.h"

namespace {

void systemTaskFn(void *pvParameters) {
    const TickType_t interval = pdMS_TO_TICKS(1000);
    TickType_t lastWake = xTaskGetTickCount();
    uint32_t seconds = 0;

    for (;;) {
        seconds++;

        sharedState.update([seconds](NodeState &s) {
            s.uptimeSeconds = seconds;
        });

        Serial.printf("[system] %s up %lus, heap=%u free_psram=%u\n",
                      NODE_NAME,
                      (unsigned long)seconds,
                      (unsigned)ESP.getFreeHeap(),
                      (unsigned)ESP.getFreePsram());

        vTaskDelayUntil(&lastWake, interval);
    }
}

}  // namespace

void systemTaskStart() {
    xTaskCreatePinnedToCore(
        systemTaskFn,
        "system_task",
        SYSTEM_TASK_STACK,
        nullptr,
        SYSTEM_TASK_PRIORITY,
        nullptr,
        SYSTEM_TASK_CORE
    );
}
