#pragma once

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <gooey/base_classes.h>

#include <memory>
#include <vector>

#include "Interfaces.h"
#include "impl/FLTKBoxImpl.h"

namespace gooey::fltk {

    class FLTKLabel : public IFLTKLabel {
        std::unique_ptr<impl::FLTKBoxImpl> _impl_box;
        IFLTKWindow*                       _parentWindow;

    public:
        FLTKLabel(IFLTKWindow* parentWindow) : _parentWindow(parentWindow) {
            _impl_box = std::make_unique<impl::FLTKBoxImpl>(50, 20);
        }

        // IFLTKLabel
        impl::FLTKBoxImpl* get_impl() override { return _impl_box.get(); }

        // ...
        bool set_text(const char* text) override {
            _impl_box->copy_label(text);
            return true;
        }
    };
}