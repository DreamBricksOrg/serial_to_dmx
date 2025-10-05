#pragma once

#include "common.h"
#include "logo_sender.h"

class view_sender_t : public view_t {
   public:
    void setup(void) override;
    bool loop(void) override;
    void close(void) override;

   private:
    static constexpr int BAR_HEIGHT = 64;
    static constexpr int CONSOLE_Y  = 88;

    size_t data_idx = 0;
    M5Canvas canvas[2];
    bool canvas_flip = false;

    uint16_t enable_channels[DMX_MAX_PACKET_SIZE];
    uint16_t enable_channel_count = 0;

    uint8_t visible[DMX_MAX_PACKET_SIZE]{};
    uint8_t data[2][DMX_MAX_PACKET_SIZE];
    uint16_t target_channel_index = 0;
    uint16_t target_channel       = 0;
    int16_t target_value          = 0;
    int16_t scroll_y              = 0;
    int16_t scroll_y_add          = 0;
    static constexpr uint16_t scroll_width     = 250;
    static constexpr uint8_t scroll_height     = 240;
    static constexpr uint8_t channel_item_cols = 5;
    static constexpr uint8_t channel_item_width =
        scroll_width / channel_item_cols;
    static constexpr uint8_t channel_item_height = 54;
    static constexpr uint16_t slider_x           = scroll_width + 28;
    static constexpr uint8_t slider_w            = 16;
    static constexpr uint8_t slider_y            = 72;  // 40;
    static constexpr uint8_t slider_btn_height   = 32;

    int16_t circle_ui_x  = 160;
    int16_t circle_ui_y  = 160;
    int16_t circle_ui_r0 = 40;
    int16_t circle_ui_r1 = 72;

    enum ui_mode_t {
        mode_channel_select,
        mode_value_setting,
    };

    ui_mode_t ui_mode = mode_channel_select;

    void setUIMode(ui_mode_t new_mode);
    bool scrollToTargetItem(void);
    void drawFocusBox(LovyanGFX* gfx, int x, int y, int w, int h, int fw);
    void hideUIValueSet(void);
    void drawUIValueUpDown(int sign = 0);
    void drawUIValueSet(uint16_t new_value, bool force_redraw = false);
    uint32_t getBarColor(int32_t y);
    void fillBar(LovyanGFX* gfx, int32_t x, int32_t y, int32_t w, int32_t h,
                 size_t ch = 0);
    void updateDisplay(bool full_redraw = false);
};
