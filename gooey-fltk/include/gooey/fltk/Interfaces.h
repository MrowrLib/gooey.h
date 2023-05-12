#pragma once

#include <cstdint>  // for Fl.H use of intptr_t
//

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <gooey/base.h>

#include "impl/FLTKAutoProportionalGroupImpl.h"
#include "impl/FLTKBoxImpl.h"
#include "impl/FLTKGridImpl.h"
#include "impl/FLTKInputImpl.h"
#include "impl/FLTKWindowImpl.h"

namespace gooey::fltk {

    struct IFLTKGrid : public virtual UIGridBase {
        virtual impl::FLTKGridImpl* get_impl() = 0;
    };

    struct IFLTKLabel : public virtual UILabelBase {
        virtual impl::FLTKBoxImpl* get_impl() = 0;
    };

    struct IFLTKTextInput : public virtual UITextInputBase {
        virtual impl::FLTKInputImpl* get_impl() = 0;
    };

    struct IFLTKPanel : public virtual UIPanelBase {
        virtual impl::FLTKAutoProportionalGroupImpl* get_impl() = 0;
    };

    struct IFLTKWindow : public virtual UIWindowBase {
        virtual impl::FLTKWindowImpl* get_impl() = 0;
    };
}