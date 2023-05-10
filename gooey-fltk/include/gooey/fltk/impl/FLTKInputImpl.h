#pragma once

#include <cstdint>  // for Fl.H use of intptr_t
//

#include <FL/Fl.H>
#include <FL/Fl_Input.H>
// #include <gooey/base_classes.h>

#include "FLTKBackgroundImageCollection.h"

namespace gooey::fltk::impl {

    class FLTKInputImpl : public Fl_Input {
        // FLTKBackgroundImageCollection _backgroundImagesCollection;

    public:
        FLTKInputImpl(int width, int height) : Fl_Input(0, 0, width, height) {}
        // FLTKWindowImpl(int width, int height) : Fl_Window(width, height) { resizable(this); }

        // bool AddBackgroundImage(const std::string& imagePath) {
        //     return _backgroundImagesCollection.AddImage(imagePath);
        // }

        // bool RemoveBackgroundImage(const std::string& imagePath) {
        //     return _backgroundImagesCollection.RemoveImage(imagePath);
        // }

        // void draw() override {
        //     Fl_Window::draw();
        //     _backgroundImagesCollection.DrawAll(x(), y(), w(), h());
        // }
    };
}