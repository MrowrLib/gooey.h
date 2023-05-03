#pragma once

#include <FL/Fl.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Pack.H>
#include <gooey.h>

#include <string>

#include "Colors.h"
#include "DefaultSizes.h"

namespace gooey::FLTKAdapter {

    class Button : public UIButton {
        Fl_Button* _implButton;

    public:
        Button(Fl_Pack* pack)
            : _implButton(new Fl_Button(0, 0, DefaultSizes::ButtonWidth, DefaultSizes::ButtonHeight)
              ) {
            pack->add(_implButton);
        }

        GOOEY_FLTK_COLOR_SETTERS(_implButton)

        bool SetText(const char* text) override {
            _implButton->label(text);
            return true;
        }
        const char* GetText() override { return _implButton->label(); }
    };
}
