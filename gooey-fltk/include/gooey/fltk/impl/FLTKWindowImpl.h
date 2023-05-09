#pragma once

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <gooey/base_classes.h>

namespace gooey::fltk::impl {

    class FLTKWindowImpl : public Fl_Window {
    public:
        FLTKWindowImpl(int width, int height) : Fl_Window(width, height) {}
    };
}