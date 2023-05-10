#pragma once

#include <cstdint>  // for Fl.H use of intptr_t
//

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <gooey/base_classes.h>

#include "impl/FLTKTextInputImpl.h"
#include "impl/FLTKWindowImpl.h"

namespace gooey::fltk {

    struct IFLTKTextInput : public virtual UITextInputBase {
        virtual ~IFLTKTextInput()                   = default;
        virtual impl::FLTKTextInputImpl* get_impl() = 0;
    };

    struct IFLTKWindow : public virtual UIWindowBase {
        virtual ~IFLTKWindow()                   = default;
        virtual impl::FLTKWindowImpl* get_impl() = 0;
    };
}