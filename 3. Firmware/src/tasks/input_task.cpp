#include "input_task.h"

#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "config.h"

namespace {

void inputTaskFn(void *pvParameters) {
    // TODO: pinMode(BTN_UP_PIN, INPUT_PULLUP); etc.
    // TODO: debounce, then sharedState.update([](NodeState &s){ ... });
    for (;;) {
        vTaskDelay(pdMS_TO_TICKS(20));
    }
}

}  // namespace

void inputTaskStart() {
    xTaskCreatePinnedToCore(
        inputTaskFn,
        "input_task",
        INPUT_TASK_STACK,
        nullptr,
        INPUT_TASK_PRIORITY,
        nullptr,
        INPUT_TASK_CORE
    );
}
