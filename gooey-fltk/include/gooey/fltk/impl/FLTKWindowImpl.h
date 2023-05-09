#pragma once

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <gooey/base_classes.h>

#include "FLTKBackgroundImageCollection.h"

namespace gooey::fltk::impl {

    class FLTKWindowImpl : public Fl_Window {
        FLTKBackgroundImageCollection _backgroundImagesCollection;

    public:
        FLTKWindowImpl(int width, int height) : Fl_Window(width, height) { resizable(this); }

        bool AddBackgroundImage(const std::string& imagePath) {
            return _backgroundImagesCollection.AddImage(imagePath);
        }

        bool RemoveBackgroundImage(const std::string& imagePath) {
            return _backgroundImagesCollection.RemoveImage(imagePath);
        }

        void draw() override {
            // Fl_Window::draw();
            _backgroundImagesCollection.DrawAll(x(), y(), w(), h());
        }
    };
}