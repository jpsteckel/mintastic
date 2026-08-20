#pragma once

// Creates and starts the system/heartbeat FreeRTOS task. Call once from
// setup(). Currently just updates uptime and prints a serial heartbeat;
// this is a reasonable place to later add battery monitoring, watchdog
// feeding, etc.
void systemTaskStart();
