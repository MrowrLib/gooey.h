#pragma once

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <gooey/base_classes.h>

#include <memory>
#include <vector>

#include "Interfaces.h"
#include "impl/FLTKTextInputImpl.h"

namespace gooey::fltk {

    class FLTKTextInput : public IFLTKTextInput {
        std::unique_ptr<impl::FLTKTextInputImpl> _impl_textInput;
        IFLTKWindow*                             _parentWindow;

    public:
        FLTKTextInput(IFLTKWindow* parentWindow) : _parentWindow(parentWindow) {
            _impl_textInput = std::make_unique<impl::FLTKTextInputImpl>(100, 20);
        }

        // IFLTKTextInput
        impl::FLTKTextInputImpl* get_impl() override { return _impl_textInput.get(); }
    };
}