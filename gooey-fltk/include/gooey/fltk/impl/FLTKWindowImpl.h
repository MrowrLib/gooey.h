#pragma once

#include <FL/Fl.H>
#include <FL/Fl_Pack.H>
#include <FL/Fl_Window.H>
#include <gooey/base_classes.h>

#include "FLTKBackgroundImageCollection.h"

namespace gooey::fltk::impl {

    class FLTKWindowImpl : public Fl_Window {
        FLTKBackgroundImageCollection _backgroundImagesCollection;
        Fl_Pack*                      _pack;

    public:
        FLTKWindowImpl(int width, int height) : Fl_Window(width, height) {
            _pack = new Fl_Pack(0, 0, width, height);
            _pack->type(Fl_Pack::VERTICAL);
            resizable(this);
        }

        bool AddBackgroundImage(const std::string& imagePath) {
            return _backgroundImagesCollection.AddImage(imagePath);
        }

        bool RemoveBackgroundImage(const std::string& imagePath) {
            return _backgroundImagesCollection.RemoveImage(imagePath);
        }

        bool add_widget(Fl_Widget* widget) {
            _pack->add(widget);
            return true;
        }

        void draw() override {
            Fl_Window::draw();
            _backgroundImagesCollection.DrawAll(x(), y(), w(), h());
        }
    };
}