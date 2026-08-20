#include "ui.h"

#include "config.h"
#include <Arduino.h>

namespace ui
{

    namespace
    {
        uint32_t frameCount = 0;
        uint32_t lastUptimeSeconds = UINT32_MAX;
        bool lastGpsHasFix = false;
        uint32_t lastNodesInMesh = UINT32_MAX;
        uint8_t lastActiveScreen = UINT8_MAX;
    }

    void begin(Adafruit_ST7789 &tft)
    {
        tft.fillScreen(ST77XX_BLACK);

        tft.setTextWrap(false);
        tft.setTextColor(ST77XX_GREEN, ST77XX_BLACK);
        tft.setTextSize(2);
        tft.setCursor(10, 10+31);
        tft.print(NODE_NAME);
        tft.drawBitmap(10, 10, altoidsBMP, 160, 21, ST77XX_CYAN);

        tft.drawFastHLine(0, 34+31, TFT_WIDTH, ST77XX_WHITE);
    }

    void render(Adafruit_ST7789 &tft, const NodeState &state)
    {
        tft.setTextSize(1);
        tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);

        const int lineWidth = TFT_WIDTH - 20;
        const int lineHeight = 16;

        if (state.uptimeSeconds != lastUptimeSeconds)
        {
            unsigned long days = state.uptimeSeconds / 86400;
            unsigned long hours = (state.uptimeSeconds / 3600) % 24;
            unsigned long mins = (state.uptimeSeconds / 60) % 60;
            unsigned long secs = state.uptimeSeconds % 60;
            tft.fillRect(10, 50+31, lineWidth, lineHeight, ST77XX_BLACK);
            tft.setCursor(10, 50+31);
            tft.print("uptime: ");
            tft.print(days);
            tft.print("d ");
            tft.print(hours);
            tft.print("h ");
            tft.print(mins);
            tft.print("m ");
            tft.print(secs);
            tft.print("s");
            
            lastUptimeSeconds = state.uptimeSeconds;
        }

        if (state.gpsHasFix != lastGpsHasFix)
        {
            tft.fillRect(10, 65+31, lineWidth, lineHeight, ST77XX_BLACK);
            tft.setCursor(10, 65+31);
            tft.print("gps fix: ");
            tft.print(state.gpsHasFix ? "yes" : "no");
            lastGpsHasFix = state.gpsHasFix;
        }

        if (state.nodesInMesh != lastNodesInMesh)
        {
            tft.fillRect(10, 80+31, lineWidth, lineHeight, ST77XX_BLACK);
            tft.setCursor(10, 80+31);
            tft.print("mesh nodes: ");
            tft.print(state.nodesInMesh);
            lastNodesInMesh = state.nodesInMesh;
        }

        if (state.activeScreen != lastActiveScreen)
        {
            tft.fillRect(10, 95+31, lineWidth, lineHeight, ST77XX_BLACK);
            tft.setCursor(10, 95+31);
            tft.print("screen: ");
            tft.print(state.activeScreen);
            lastActiveScreen = state.activeScreen;
        }

        if (frameCount % 100 == 0)
        {
            tft.fillRect(0, TFT_HEIGHT - 20, TFT_WIDTH, 20, ST77XX_BLACK);
            tft.setTextSize(1);
            tft.setTextColor(ST77XX_GREEN, ST77XX_BLACK);
            tft.setCursor(15, TFT_HEIGHT - 15);
            tft.printf("Free heap: %u KB", ESP.getFreeHeap() / 1024);
        }

        int cx = TFT_WIDTH - 20;
        int cy = TFT_HEIGHT - 20;
        tft.fillCircle(cx, cy, 6, (frameCount % 30 < 15) ? ST77XX_CYAN : ST77XX_BLACK);
        tft.drawCircle(cx, cy, 6, ST77XX_WHITE);

        frameCount++;
    }

} // namespace ui
