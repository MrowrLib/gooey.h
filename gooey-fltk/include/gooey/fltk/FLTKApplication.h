#pragma once

#include <FL/Fl.H>
#include <gooey/base_classes.h>

#include <memory>
#include <vector>

#include "FLTKWindow.h"

namespace gooey::fltk {

    class FLTKApplication : public UIApplicationBase {
        std::vector<std::unique_ptr<UIWindow>> _windows;

    public:
        FLTKApplication() { fl_register_images(); }

        UIWindow* add_window() override {
            auto* window = new FLTKWindow(this);
            _windows.emplace_back(window);
            return window;
        }
        bool render() override {
            Fl::check();
            return true;
        }
        bool run_blocking() override {
            Fl::run();
            return true;
        }
        // bool      destroy() override; // just close all windows :)
    };
}