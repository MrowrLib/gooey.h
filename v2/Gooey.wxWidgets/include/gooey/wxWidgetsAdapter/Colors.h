#pragma once

#define GOOEY_WX_COLOR_SETTERS(widget)                                                          \
    bool SetBackgroundColor(unsigned int red, unsigned int green, unsigned int blue) override { \
        return widget->SetBackgroundColour(wxColour(red, green, blue, 0));                      \
    }                                                                                           \
    bool SetForegroundColor(unsigned int red, unsigned int green, unsigned int blue) override { \
        return widget->SetForegroundColour(wxColour(red, green, blue, 0));                      \
    }