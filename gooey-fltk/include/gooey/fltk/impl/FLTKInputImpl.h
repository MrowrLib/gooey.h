#pragma once

#include <cstdint>  // for Fl.H use of intptr_t
//

#include <FL/Fl.H>
#include <FL/Fl_Input.H>

namespace gooey::fltk::impl {

    class FLTKInputImpl : public Fl_Input {
    public:
        FLTKInputImpl(int width, int height) : Fl_Input(0, 0, width, height) {}
    };
}