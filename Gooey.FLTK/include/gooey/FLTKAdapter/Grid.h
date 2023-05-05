#pragma once

#include <Windows.h>
//

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Pack.H>
#include <gooey.h>

#include <string>

#include "WidgetContainer.h"
// #include "Colors.h"
// #include "Defaults.h"

#include <vector>

namespace gooey::FLTKAdapter {

    namespace Impl {
        class FLTK_Grid : public Fl_Group {
        private:
            int                                  _numCols, _numRows;
            int                                  _cellWidth, _cellHeight, _padding;
            std::vector<std::vector<Fl_Widget*>> _gridElements;

        public:
            FLTK_Grid(int numCols, int numRows, int cellWidth, int cellHeight, int padding)
                : Fl_Group(0, 0, numCols * (cellWidth + padding), numRows * (cellHeight + padding)),
                  _numCols(numCols),
                  _numRows(numRows),
                  _cellWidth(cellWidth),
                  _cellHeight(cellHeight),
                  _padding(padding) {
                end();

                _gridElements.resize(_numRows, std::vector<Fl_Widget*>(_numCols, nullptr));
                for (int i = 0; i < _numRows; ++i) {
                    for (int j = 0; j < _numCols; ++j) {
                        auto box = new Fl_Box(
                            j * (_cellWidth + _padding), i * (_cellHeight + _padding), _cellWidth,
                            _cellHeight
                        );
                        add(box);
                        _gridElements[i][j] = box;
                    }
                }
            }

            // ButtonWithBackgroundImage* AddButton(
            //     int x, int y, int cols, int rows, bool replace = true
            // ) {
            //     if (replace) {
            //         ClearRange(x, y, cols, rows);
            //     }
            //     auto button = new ButtonWithBackgroundImage(
            //         x * (_cellWidth + _padding), y * (_cellHeight + _padding),
            //         cols * _cellWidth + (cols - 1) * _padding,
            //         rows * _cellHeight + (rows - 1) * _padding
            //     );
            //     add(button);
            //     for (int i = y; i < y + rows; ++i) {
            //         for (int j = x; j < x + cols; ++j) {
            //             _gridElements[i][j] = button;
            //         }
            //     }
            //     return button;
            // }

            // BoxWithBackgroundImage* AddLabel(
            //     int x, int y, int cols, int rows, bool replace = true
            // ) {
            //     if (replace) {
            //         ClearRange(x, y, cols, rows);
            //     }
            //     auto label = new BoxWithBackgroundImage(
            //         x * (_cellWidth + _padding), y * (_cellHeight + _padding),
            //         cols * _cellWidth + (cols - 1) * _padding,
            //         rows * _cellHeight + (rows - 1) * _padding
            //     );
            //     add(label);
            //     for (int i = y; i < y + rows; ++i) {
            //         for (int j = x; j < x + cols; ++j) {
            //             _gridElements[i][j] = label;
            //         }
            //     }
            //     return label;
            // }

            bool HasElementAt(int x, int y) {
                if (!ValidPosition(x, y)) {
                    return false;
                }
                return _gridElements[y][x] != nullptr;
            }

            void RemoveElementAt(int x, int y) {
                if (!ValidPosition(x, y)) {
                    return;
                }
                auto element = _gridElements[y][x];
                if (element != nullptr) {
                    remove(element);
                    for (int i = 0; i < _numRows; ++i) {
                        for (int j = 0; j < _numCols; ++j) {
                            if (_gridElements[i][j] == element) {
                                _gridElements[i][j] = nullptr;
                            }
                        }
                    }
                    delete element;
                }
            }

            void Clear() {
                for (int i = 0; i < _numRows; ++i) {
                    for (int j = 0; j < _numCols; ++j) {
                        RemoveElementAt(j, i);
                    }
                }
            }

            void ClearRange(int x, int y, int cols, int rows) {
                for (int i = y; i < y + rows; ++i) {
                    for (int j = x; j < x + cols; ++j) {
                        RemoveElementAt(j, i);
                    }
                }
            }

        private:
            bool ValidPosition(int x, int y) {
                return x >= 0 && x < _numCols && y >= 0 && y < _numRows;
            }
        };
    }

    class Grid : public UIGrid {
        // public:

        // Label(Fl_Pack* pack, unsigned int col) {}
        // : _implLabel(new Fl_Box(0, 0, Defaults::LabelWidth, Defaults::LabelHeight)) {
        // _implLabel->box(FL_FLAT_BOX);
        // pack->add(_implLabel);
        // }

        // GOOEY_FLTK_COLOR_SETTERS(_implLabel)

        // bool SetText(const char* text) override {
        //     _implLabel->label(text);
        //     return true;
        // }
        // const char* GetText() override { return _implLabel->label(); }
    };
}
