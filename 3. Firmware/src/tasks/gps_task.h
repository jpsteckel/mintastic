#pragma once

// STUB — not started by main.cpp yet.
//
// When ready to wire in a GPS module:
//   1. Implement gps_task.cpp (read NMEA over UART on GPS_RX_PIN/GPS_TX_PIN,
//      e.g. with TinyGPS++), writing results into sharedState via
//      sharedState.update([&](NodeState &s){ s.latitude = ...; }).
//   2. Call gpsTaskStart() from main.cpp's setup().
void gpsTaskStart();
