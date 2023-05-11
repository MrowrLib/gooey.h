#pragma once

#include <gooey/base_classes.h>

#include "Interfaces.h"
#include "impl/FLTKGridImpl.h"

namespace gooey::fltk {

    class FLTKGrid : public IFLTKGrid {
        impl::FLTKGridImpl* _impl_grid;

    public:
        FLTKGrid(unsigned int columnCount, unsigned int rowCount, unsigned int cellSize, unsigned int padding) {
            _impl_grid = new impl::FLTKGridImpl(columnCount, rowCount, cellSize, padding);
        }

        // IFLTKGrid
        impl::FLTKGridImpl* get_impl() override { return _impl_grid; }
    };
}