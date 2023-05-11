#pragma once

#include <cstdint>  // for Fl.H use of intptr_t
//

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Group.H>

namespace gooey::fltk::impl {

    class FLTKGridImpl : public Fl_Group {
    public:
        FLTKGridImpl(int width = 200, int height = 100) : Fl_Group(0, 0, width, height) {
            box(FL_FLAT_BOX);
            color(FL_DARK3);
            auto* box = new Fl_Box(0, 0, width, height);
            box->box(FL_FLAT_BOX);
            box->color(FL_DARK3);
            box->align(FL_ALIGN_INSIDE | FL_ALIGN_TOP | FL_ALIGN_LEFT);
            box->label("Grid");
            box->labelcolor(FL_WHITE);
            box->labelsize(14);
            add(box);
        }

        // Make it render ANYTHING.
    };
}