#pragma once

#include <cstdint>  // for Fl.H use of intptr_t
//

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Window.H>
#include <FL/fl_draw.H>

#include <memory>

#include "FLTKAspectRatioGroupImpl.h"
#include "FLTKGridCellImpl.h"

namespace gooey::fltk::impl {

    class FLTKGridImpl : public FLTKAspectRatioGroupImpl {
        // size
        unsigned int _columnCount, _rowCount, _cellHeight, _cellWidth, _padding;

        // grid lines
        bool     _gridLines_enabled = true;
        Fl_Color _gridLines_color   = FL_RED;  // FL_BACKGROUND_COLOR;

    public:
        FLTKGridImpl(
            unsigned int columnCount, unsigned int rowCount, unsigned int cellSize,
            unsigned int padding
        )
            : FLTKAspectRatioGroupImpl(
                  0, 0, columnCount * (cellSize + padding), rowCount * (cellSize + padding)
              ),
              _columnCount(columnCount),
              _rowCount(rowCount),
              _cellHeight(cellSize),
              _cellWidth(cellSize),
              _padding(padding) {
            //
            // auto* someBox = new FLTKGridCellImpl(100, 50);
            // add(someBox);
            //

            end();
        }

        // Make it render ANYTHING.

        unsigned int generateHeight() {
            // return _rowCount * (_cellHeight + _padding) - _padding;
            return h();
        }

        unsigned int generateWidth() {
            // return _columnCount * (_cellWidth + _padding) - _padding;
            return w();
        }

        void draw_vertical_lines() {
            if (_gridLines_enabled && _gridLines_color) {
                double calculatedCellWidth =
                    static_cast<double>(w()) / _columnCount;  // TODO take padding into account
                double calculatedCellHeight = static_cast<double>(h()) / _rowCount;

                fl_color(_gridLines_color);
                fl_line_style(FL_SOLID, 1);
                // Draw vertical lines
                for (int i = 1; i < _columnCount; ++i) {
                    int xPos = x() + (i * calculatedCellWidth);
                    fl_line(xPos, y(), xPos, y() + h());
                }
                // Draw horizontal lines
                for (int i = 1; i < _rowCount; ++i) {
                    int yPos = y() + (i * calculatedCellHeight);
                    fl_line(x(), yPos, x() + w(), yPos);
                }
                fl_line_style(0);
            }
        }

        void draw() override {
            // Draw the background
            fl_color(FL_BLUE);
            fl_rectf(x(), y(), w(), h());

            // Draw the border
            fl_color(FL_BLACK);
            fl_rect(x(), y(), w(), h());

            // Draw the grid lines
            draw_vertical_lines();

            // Draw the children
            Fl_Group::draw_children();
        }
    };
}