#pragma once

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <gooey/base.h>

#include <memory>
#include <vector>

#include "Interfaces.h"
#include "impl/FLTKInputImpl.h"

namespace gooey::fltk {

    class FLTKTextInput : public IFLTKTextInput {
        std::unique_ptr<impl::FLTKInputImpl> _impl_textInput;
        IFLTKWindow*                         _parentWindow;

    public:
        FLTKTextInput(IFLTKWindow* parentWindow) : _parentWindow(parentWindow) {
            _impl_textInput = std::make_unique<impl::FLTKInputImpl>(50, 20);
        }

        // IFLTKTextInput
        impl::FLTKInputImpl* get_impl() override { return _impl_textInput.get(); }

        // ...
        bool set_text(const char* text) override {
            _impl_textInput->copy_label(text);
            return true;
        }

        bool set_background_color(UIColor color) override {
            _impl_textInput->color(fl_rgb_color(color.red, color.green, color.blue));
            return true;
        }
    };
}