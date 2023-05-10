#pragma once

#include <cstdint>  // for Fl.H use of intptr_t
//

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <gooey/base_classes.h>

#include "FLTKBackgroundImageCollection.h"

namespace gooey::fltk::impl {

    class FLTKBoxImpl : public Fl_Box {
        // FLTKBackgroundImageCollection _backgroundImagesCollection;

    public:
        FLTKBoxImpl(int width, int height) : Fl_Box(0, 0, width, height) {}
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