#include <Arduino.h>

#include "config.h"
#include "shared_state.h"
#include "tasks/display_task.h"
#include "tasks/system_task.h"

// Not started yet — implement + uncomment when ready:
// #include "tasks/gps_task.h"
// #include "tasks/input_task.h"
// #include "tasks/mesh_task.h"

void setup() {
    Serial.begin(9600);
    delay(200);  // let USB CDC settle
    Serial.printf("\n%s booting...\n", NODE_NAME);

    sharedState.begin();

    displayTaskStart();
    systemTaskStart();

    // gpsTaskStart();
    // inputTaskStart();
    // meshTaskStart();

    Serial.println("setup() done — tasks running under FreeRTOS.");
}

void loop() {
    // Intentionally empty: all work happens in FreeRTOS tasks.
    // Arduino's loop() itself runs as a low-priority task on core 1;
    // we just idle it here.
    vTaskDelay(pdMS_TO_TICKS(1000));
}
