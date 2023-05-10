#pragma once

#include <cstdint>  // for Fl.H use of intptr_t
//

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <gooey.h>

#include <memory>

#include "FLTKBackgroundImageCollection.h"

namespace gooey::fltk::impl {

    class FLTKBoxImpl : public Fl_Box {
        std::unique_ptr<Fl_Color> _backgroundColor;
        std::unique_ptr<Fl_Color> _foregroundColor;

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

        void draw() override {
            if (_backgroundColor) {
                fl_color(*_backgroundColor);
                fl_rectf(x(), y(), w(), h());
            }

            Fl_Box::draw();
            // _backgroundImagesCollection.DrawAll(x(), y(), w(), h());
        }

        void set_background_color(UIColor color) {
            _backgroundColor.reset(new Fl_Color(fl_rgb_color(color.red, color.green, color.blue)));
        }
    };
}