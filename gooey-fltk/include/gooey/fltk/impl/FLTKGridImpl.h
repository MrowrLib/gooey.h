#pragma once

#include <cstdint>  // for Fl.H use of intptr_t
//

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Window.H>
#include <FL/fl_draw.H>

#include "FLTKGridCellImpl.h"

namespace gooey::fltk::impl {

    class FLTKGridImpl : public Fl_Group {
    public:
        FLTKGridImpl(int width = 200, int height = 100) : Fl_Group(10, 10, width, height) {
            auto* cell = new FLTKGridCellImpl(100, 30);
            add(cell);
            end();
        }

        // Make it render ANYTHING.

        void draw() override {
            // Draw the background
            fl_color(FL_BLUE);
            fl_rectf(x(), y(), w(), h());

            // Draw the border
            fl_color(FL_BLACK);
            fl_rect(x(), y(), w(), h());

            // Draw the children
            Fl_Group::draw_children();
        }
    };
}