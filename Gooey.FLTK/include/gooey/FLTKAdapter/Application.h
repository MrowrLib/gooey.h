#pragma once

#include <cstdint>  // <--- cstdint required before FL/Fl.H
#include <memory>
#include <vector>
//

#include <FL/Fl.H>
#include <FL/Fl_BMP_Image.H>
#include <FL/Fl_GIF_Image.H>
#include <FL/Fl_JPEG_Image.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_SVG_Image.H>
#include <FL/Fl_Shared_Image.H>
#include <gooey.h>

#include "Frame.h"

namespace gooey::FLTKAdapter {

    class Application : public UIApplication {
        std::vector<std::unique_ptr<Frame>> _frames;

    public:
        Application() { fl_register_images(); }

        bool Start() override {
            Fl::run();
            return true;
        }

        bool Shutdown() override {
            // Really weird behavior, if you hide all windows ::run will return
            for (auto& window : _frames) window->Hide();
            return true;
        }

        UIWindow* AddWindow() override {
            auto window = std::make_unique<Frame>();
            _frames.push_back(std::move(window));
            return _frames.back().get();
        }
    };
}
