#pragma once

#include <gooey/base_classes.h>

#include "Interfaces.h"
#include "impl/FLTKGridImpl.h"

namespace gooey::fltk {

    class FLTKGrid : public IFLTKGrid {
        impl::FLTKGridImpl* _impl_grid;

    public:
        FLTKGrid() { _impl_grid = new impl::FLTKGridImpl(); }

        // IFLTKGrid
        impl::FLTKGridImpl* get_impl() override { return _impl_grid; }
    };
}