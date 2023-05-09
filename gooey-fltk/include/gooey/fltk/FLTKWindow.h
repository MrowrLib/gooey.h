#pragma once

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <gooey/base_classes.h>

#include <memory>
#include <vector>

#include "impl/FLTKWindowImpl.h"

namespace gooey::fltk {

    class FLTKWindow : public UIWindowBase {
        std::unique_ptr<impl::FLTKWindowImpl> _impl_window;

        // need to know if is attached...

        int _setup_x, _setup_y, _setup_width, _setup_height;

    public:
        FLTKWindow(UIApplicationBase* parent) : UIWindowBase(parent) {
            auto* defaults = parent->get_defaults();
            _impl_window   = std::make_unique<impl::FLTKWindowImpl>(
                defaults->window_width, defaults->window_height
            );
        }

        // bool apply() override {
        //     _impl_window->label(_title.c_str());
        //     _impl_window->size(_width, _height);
        //     _impl_window->position(_x, _y);
        //     return true;
        // }

        bool apply() {
            _impl_window->label("hi!");
            _impl_window->size(100, 100);
            _impl_window->position(100, 100);
            _impl_window->show();
            return true;
        }
    };
}