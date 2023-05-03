#pragma once

#include <cstdint>  // <--- Require before FL/Fl.H
//

#include <FL/Fl.H>
#include <gooey.h>

#include <memory>
#include <vector>

#include "Window.h"

namespace gooey::FLTKAdapter {

    class Application : public UIApplication {
        std::vector<std::unique_ptr<Window>> _windows;

    public:
        Application() {}

        bool Start() override {
            Fl::run();
            return true;
        }

        bool Shutdown() override {
            // Really weird behavior, if you hide all windows ::run will return
            for (auto& window : _windows) window->Hide();
            return true;
        }

        UIWindow* AddWindow() override {
            auto window = std::make_unique<Window>();
            _windows.push_back(std::move(window));
            return _windows.back().get();
        }
    };
}
