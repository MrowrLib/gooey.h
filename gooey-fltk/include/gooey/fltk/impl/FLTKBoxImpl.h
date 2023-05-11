#pragma once

#include <cstdint>  // for Fl.H use of intptr_t
//

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/fl_draw.H>
#include <gooey.h>

#include <memory>

namespace gooey::fltk::impl {

    class FLTKBoxImpl : public Fl_Box {
        std::unique_ptr<Fl_Color> _backgroundColor;
        std::unique_ptr<Fl_Color> _foregroundColor;

    public:
        FLTKBoxImpl(int width, int height) : Fl_Box(0, 0, width, height) {}

        void draw() override {
            if (_backgroundColor) {
                fl_color(*_backgroundColor);
                fl_rectf(x(), y(), w(), h());
            }
            Fl_Box::draw();
        }

        void set_background_color(UIColor color) {
            _backgroundColor.reset(new Fl_Color(fl_rgb_color(color.red, color.green, color.blue)));
        }
    };
}