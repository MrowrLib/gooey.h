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

            void draw() override {
                // Draw the background color
                fl_color(FL_RED);
                fl_rectf(x(), y(), w(), h());

                // Draw the background image if available
                // if (_backgroundImage) {
                //     _backgroundImage->draw(x(), y(), w(), h());
                // }

                // Draw the children (i.e., grid elements)
                draw_children();
            }

            void resize(int X, int Y, int W, int H) override {
                // Calculate the new dimensions while maintaining the aspect ratio
                float aspectRatio = static_cast<float>(_numCols) / static_cast<float>(_numRows);
                int   newWidth    = W;
                int   newHeight   = static_cast<int>(newWidth / aspectRatio);

                // Check if the new height is larger than the available height
                if (newHeight > H) {
                    newHeight = H;
                    newWidth  = static_cast<int>(newHeight * aspectRatio);
                }

                // Center the grid within the available space
                int newX = X + (W - newWidth) / 2;
                int newY = Y + (H - newHeight) / 2;

                // Call the base class resize() method with the calculated dimensions
                Fl_Group::resize(newX, newY, newWidth, newHeight);

                // Update the cell dimensions
                _cellWidth  = newWidth / _numCols - _padding;
                _cellHeight = newHeight / _numRows - _padding;

                // Update the positions and sizes of the child widgets (grid elements)
                for (int i = 0; i < _numRows; ++i) {
                    for (int j = 0; j < _numCols; ++j) {
                        Fl_Widget* widget = _gridElements[i][j];
                        widget->resize(
                            newX + j * (_cellWidth + _padding), newY + i * (_cellHeight + _padding),
                            _cellWidth, _cellHeight
                        );
                        widget->redraw();
                    }
                }

                redraw();
            }

            Fl_Button* AddButton(int x, int y, int cols, int rows, bool replace = true) {
                if (replace) {
                    ClearRange(x, y, cols, rows);
                }
                auto button = new Fl_Button(
                    x * (_cellWidth + _padding), y * (_cellHeight + _padding),
                    cols * _cellWidth + (cols - 1) * _padding,
                    rows * _cellHeight + (rows - 1) * _padding
                );
                button->label("I AM BUTTON");
                add(button);
                for (int i = y; i < y + rows; ++i) {
                    for (int j = x; j < x + cols; ++j) {
                        _gridElements[i][j] = button;
                    }
                }
                return button;
            }

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
        Impl::FLTK_Grid _implGrid;

    public:
        Grid(Fl_Pack* pack, int numCols, int numRows)
            : _implGrid(
                  numCols, numRows, Defaults::GridCellWidth, Defaults::GridCellHeight,
                  Defaults::GridPadding
              ) {
            _implGrid.color(FL_RED);

            pack->add(_implGrid);

            _implGrid.AddButton(0, 0, 2, 2);
            _implGrid.AddButton(3, 0, 1, 4);
            _implGrid.AddButton(6, 3, 2, 1);
        }

        // Add Button
    };
}
