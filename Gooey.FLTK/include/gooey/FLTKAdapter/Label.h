#pragma once

#include <Windows.h>
//

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Pack.H>
#include <gooey.h>

#include <string>

#include "Colors.h"
#include "DefaultSizes.h"

namespace gooey::FLTKAdapter {

    class Label : public UILabel {
        Fl_Box* _implLabel;

    public:
        Label(Fl_Pack* pack)
            : _implLabel(new Fl_Box(0, 0, DefaultSizes::LabelWidth, DefaultSizes::LabelHeight)) {
            _implLabel->box(FL_FLAT_BOX);
            pack->add(_implLabel);
        }

        GOOEY_FLTK_COLOR_SETTERS(_implLabel)

        bool SetText(const char* text) override {
            _implLabel->label(text);
            return true;
        }
        const char* GetText() override { return _implLabel->label(); }
    };
}
