#pragma once

#define GOOEY_FLTK_COLOR_SETTERS(widget)                                                        \
    bool SetBackgroundColor(unsigned int red, unsigned int green, unsigned int blue) override { \
        widget->color(fl_rgb_color(red, green, blue));                                          \
        return true;                                                                            \
    }                                                                                           \
    bool SetForegroundColor(unsigned int red, unsigned int green, unsigned int blue) override { \
        widget->labelcolor(fl_rgb_color(red, green, blue));                                     \
        return true;                                                                            \
    }