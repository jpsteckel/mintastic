#pragma once

// STUB — not started by main.cpp yet.
//
// When ready to wire in buttons/encoder:
//   1. Implement input_task.cpp (debounce BTN_UP_PIN/BTN_DOWN_PIN/
//      BTN_SELECT_PIN, or swap in an encoder library), updating
//      sharedState (e.g. s.activeScreen) to drive what ui::render() shows.
//   2. Call inputTaskStart() from main.cpp's setup().
void inputTaskStart();
