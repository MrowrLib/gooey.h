#pragma once

#include <cstdint>
// ^ before Fl headers

#include <FL/Fl.H>
#include <FL/Fl_Button.H>
#include <FL/fl_ask.H>

#include <functional>
#include <unordered_map>
#include <vector>

#include "GridEvent.h"

namespace gooey::FLTKAdapter::Impl {

    class GridBox : public Fl_Button {
        unsigned int _x, _y, _rowCount, _columnCount;
        std::unordered_map<GridEventType, std::vector<std::function<void(GridEvent)>>> _callbacks;

    public:
        GridBox(unsigned int x, unsigned int y, unsigned int cols, unsigned int rows)
            : Fl_Button(x, y, cols, rows), _x(x), _y(y), _rowCount(rows), _columnCount(cols) {
            // box(FL_NO_BOX);
            box(FL_EMBOSSED_BOX);
        }

        void On(GridEventType type, std::function<void(GridEvent)> callback) {
            _callbacks[type].push_back(callback);
        }

        int handle(int event) override {
            if (event == FL_PUSH) {
                fl_message("PUSH!");
                if (Fl::event_button() == FL_LEFT_MOUSE) {
                    fl_message("LEFT!");
                    if (Fl::event_clicks()) {
                        fl_message("TWO?");
                    } else {
                        fl_message("ONE!");
                        fl_message("Left click at (%d, %d)", Fl::event_x(), Fl::event_y());
                        for (auto& callback : _callbacks[GridEventType::LeftClick]) {
                            callback(GridEvent{
                                GridEventType::LeftClick, _x, _y, _columnCount, _rowCount});
                        }
                    }
                }
            }
            return Fl_Button::handle(event);
        }
    };
}
