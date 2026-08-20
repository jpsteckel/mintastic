#pragma once

// STUB — not started by main.cpp yet.
//
// When ready to integrate Meshtastic (or a custom LoRa mesh stack):
//   1. Implement mesh_task.cpp around the radio driver/library of choice,
//      updating sharedState (nodesInMesh, lastRssi, etc.) as packets
//      arrive, and reading it for anything the mesh needs to transmit
//      (e.g. GPS position from the gps_task).
//   2. Call meshTaskStart() from main.cpp's setup().
//   3. Give it real priority — MESH_TASK_PRIORITY in config.h is already
//      set higher than display/system since radio timing tends to matter.
void meshTaskStart();
