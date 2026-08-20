#pragma once

#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>

// =============================================================================
// shared_state.h — single source of truth for data that multiple tasks need
// to read/write (display, future GPS task, future input task, future mesh
// task). Guarded by one mutex; keep critical sections short.
// =============================================================================

struct NodeState {
    // --- system -------------------------------------------------------
    uint32_t uptimeSeconds = 0;
    float    batteryVoltage = 0.0f;
    bool     wifiConnected = false;

    // --- GPS (populated once gps_task is wired in) --------------------
    bool     gpsHasFix = false;
    double   latitude = 0.0;
    double   longitude = 0.0;
    float    altitudeMeters = 0.0f;
    uint8_t  satellites = 0;

    // --- mesh / meshtastic (populated once mesh_task is wired in) -----
    uint32_t nodesInMesh = 0;
    int8_t   lastRssi = 0;

    // --- UI / input (populated once input_task is wired in) -----------
    uint8_t  activeScreen = 0;   // which UI screen is selected
};

class SharedState {
public:
    void begin() {
        _mutex = xSemaphoreCreateMutex();
    }

    // Copies the current state into 'out'. Safe to call from any task.
    bool read(NodeState &out, TickType_t timeout = pdMS_TO_TICKS(50)) {
        if (xSemaphoreTake(_mutex, timeout) != pdTRUE) return false;
        out = _state;
        xSemaphoreGive(_mutex);
        return true;
    }

    // Runs 'mutator' against the live state under the lock.
    // Usage: sharedState.update([](NodeState &s){ s.satellites = 7; });
    template <typename Fn>
    bool update(Fn mutator, TickType_t timeout = pdMS_TO_TICKS(50)) {
        if (xSemaphoreTake(_mutex, timeout) != pdTRUE) return false;
        mutator(_state);
        xSemaphoreGive(_mutex);
        return true;
    }

private:
    NodeState _state;
    SemaphoreHandle_t _mutex = nullptr;
};

// Single global instance shared across all tasks.
extern SharedState sharedState;
