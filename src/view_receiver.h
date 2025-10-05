#pragma once

#include "common.h"

class view_receiver_t : public view_t {
   public:
    void setup(void) override;
    bool loop(void) override;
    void close(void) override;

   private:
    static constexpr int BAR_HEIGHT = 128;
    static constexpr int CONSOLE_Y  = 152;

    uint32_t timer;
    size_t data_idx = 0;
    M5Canvas canvas;
    bool graph_view = false;
    uint8_t visible[DMX_MAX_PACKET_SIZE];
    uint8_t data[2][DMX_MAX_PACKET_SIZE];
    bool dmxIsConnected = false;

    uint32_t getBarColor(int32_t y);
    void fillBar(LovyanGFX* gfx, int32_t x, int32_t y, int32_t w, int32_t h,
                 size_t ch = 0);
    void updateDisplay(int32_t duration);
};
