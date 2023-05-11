#pragma once

#include <cstdint>  // for Fl.H use of intptr_t
//

#include <FL/Fl.H>
#include <FL/Fl_Button.H>

namespace gooey::fltk::impl {

    class FLTKGridCellImpl : public Fl_Button {
    public:
        FLTKGridCellImpl(int width, int height) : Fl_Button(50, 50, width, height) {
            // box(FL_FLAT_BOX);
            color(FL_DARK3);
            align(FL_ALIGN_INSIDE | FL_ALIGN_TOP | FL_ALIGN_LEFT);
            label("I AM CELL");
            labelcolor(FL_WHITE);
            labelsize(14);
        }
    };
}