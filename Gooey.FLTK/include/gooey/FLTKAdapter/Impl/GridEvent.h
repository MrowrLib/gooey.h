#pragma once

#include <FL/Fl_Box.H>

namespace gooey::FLTKAdapter::Impl {

    enum class GridEventType { LeftClick };

    struct GridEvent {
        GridEventType type;
        unsigned int  x, y, columnCount, rowCount;
    };
}
