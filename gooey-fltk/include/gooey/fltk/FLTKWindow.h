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

    public:
        FLTKWindow(UIApplicationBase* parent) : UIWindowBase(parent) {
            auto* defaults = parent->get_defaults();
            _impl_window   = std::make_unique<impl::FLTKWindowImpl>(
                defaults->window_width, defaults->window_height
            );
        }

        bool set_title(const char* title) override {
            _impl_window->label(title);
            return true;
        }

        bool set_size(int width, int height) override {
            _impl_window->size(width, height);
            return true;
        }

        bool set_position(int x, int y) override {
            _impl_window->position(x, y);
            return true;
        }

        bool show() override {
            _impl_window->show();
            return true;
        }

        bool set_background_color(int red, int green, int blue) override {
            _impl_window->color(fl_rgb_color(red, green, blue));
            return true;
        }

        bool unset_background_color() override {
            _impl_window->color(FL_BACKGROUND_COLOR);
            return true;
        }

        bool add_background_image(const char* imagePath) override {
            _impl_window->AddBackgroundImage(imagePath);
            return true;
        }

        bool remove_background_image(const char* imagePath) override {
            _impl_window->RemoveBackgroundImage(imagePath);
            return true;
        }
    };
}