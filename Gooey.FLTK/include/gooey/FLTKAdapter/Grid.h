#pragma once

#include <Windows.h>
//

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Pack.H>
#include <FL/Fl_Shared_Image.H>
#include <gooey.h>

#include <format>
#include <map>
#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

#include "IGrid.h"
#include "Pack.h"
#include "WidgetContainer.h"

namespace gooey::FLTKAdapter {

    namespace Impl {
        class FLTK_Grid : public Fl_Group {
        private:
            int                                       _numCols, _numRows;
            int                                       _cellWidth, _cellHeight, _padding;
            std::vector<std::vector<Fl_Widget*>>      _gridElements;
            std::map<Fl_Widget*, std::pair<int, int>> _widgetSizes;
            int                                       _initialWidth, _initialHeight;
            // Fl_Shared_Image*                          _backgroundImage = nullptr;

        public:
            FLTK_Grid(int numCols, int numRows, int cellWidth, int cellHeight, int padding)
                : Fl_Group(0, 0, numCols * (cellWidth + padding), numRows * (cellHeight + padding)),
                  _numCols(numCols),
                  _numRows(numRows),
                  _cellWidth(cellWidth),
                  _cellHeight(cellHeight),
                  _padding(padding) {
                // color(FL_WHITE);
                resizable(this);

                _initialWidth  = w();
                _initialHeight = h();

                end();
                box(FL_NO_BOX);

                _gridElements.resize(_numRows, std::vector<Fl_Widget*>(_numCols, nullptr));
                for (int i = 0; i < _numRows; ++i) {
                    for (int j = 0; j < _numCols; ++j) {
                        auto box = new Fl_Box(
                            j * (_cellWidth + _padding), i * (_cellHeight + _padding), _cellWidth,
                            _cellHeight
                        );
                        // box->color(FL_WHITE);
                        add(box);
                        _gridElements[i][j] = box;
                    }
                }
            }

            ~FLTK_Grid() override {
                // if (_backgroundImage) _backgroundImage->release();
            }

            int GetInitialWidth() const { return _initialWidth; }
            int GetInitialHeight() const { return _initialHeight; }

            // void AddBackgroundImage(const char* imagePath) {
            //     if (_backgroundImage) _backgroundImage->release();

            //     _backgroundImage = Fl_Shared_Image::get(imagePath);
            //     if (!_backgroundImage)
            //         throw std::runtime_error(std::format("Failed to load image: {}", imagePath));
            //     // _backgroundImage->scale(w(), h(), 1, 1);
            // }

            void draw() override {
                // Draw the background color
                // fl_color(FL_WHITE);
                // fl_rectf(x(), y(), w(), h());

                // // Draw the background image if available
                // if (_backgroundImage) {
                //     _backgroundImage->draw(x(), y(), w(), h());
                // }

                // Draw the grid lines
                fl_color(FL_WHITE);  // Choose the color of the grid lines
                int lineWidth = 1;   // Choose the width of the grid lines
                fl_line_style(
                    FL_SOLID, lineWidth
                );  // Set line style and width (use FL_DASH or FL_DOT for dashed/dotted lines)

                // Draw vertical lines
                for (int j = 1; j < _numCols; ++j) {
                    int xPos = x() + j * (_cellWidth + _padding) - (_padding / 2);
                    fl_line(xPos, y(), xPos, y() + h());
                }

                // Draw horizontal lines
                for (int i = 1; i <= _numRows; ++i) {
                    int yPos = y() + i * (_cellHeight + _padding) - (_padding / 2);
                    fl_line(x(), yPos, x() + w(), yPos);
                }

                // Reset the line style
                fl_line_style(0);

                // Draw the children (i.e., grid elements)
                draw_children();
            }

            void resize(int X, int Y, int W, int H) override {
                if (!MonitorResizeEvents) {
                    return;
                }

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

                // Keep track of the processed widgets to avoid duplicate processing
                std::unordered_set<Fl_Widget*> processedWidgets;

                // Update the positions and sizes of the child widgets (grid elements)
                for (int i = 0; i < _numRows; ++i) {
                    for (int j = 0; j < _numCols; ++j) {
                        Fl_Widget* widget = _gridElements[i][j];

                        if (widget && processedWidgets.find(widget) == processedWidgets.end()) {
                            int widgetCols = _widgetSizes[widget].first;
                            int widgetRows = _widgetSizes[widget].second;

                            int widgetWidth = widgetCols * _cellWidth + (widgetCols - 1) * _padding;
                            int widgetHeight =
                                widgetRows * _cellHeight + (widgetRows - 1) * _padding;

                            widget->resize(
                                newX + j * (_cellWidth + _padding),
                                newY + i * (_cellHeight + _padding), widgetWidth, widgetHeight
                            );
                            widget->redraw();

                            // Mark the widget as processed
                            processedWidgets.insert(widget);
                        }
                    }
                }

                redraw();
            }

            Impl::ButtonWithBetterBackgroundImage* AddButton(
                const char* label, int x, int y, int cols, int rows, bool replace = true
            ) {
                if (!ValidPosition(x, y, cols, rows)) return nullptr;
                if (replace) ClearRange(x, y, cols, rows);
                auto button = new Impl::ButtonWithBetterBackgroundImage(
                    x * (_cellWidth + _padding), y * (_cellHeight + _padding),
                    cols * _cellWidth + (cols - 1) * _padding,
                    rows * _cellHeight + (rows - 1) * _padding
                );
                // auto label = std::format("({},{}) [{},{}]", x, y, cols, rows);
                // button->copy_label(label.c_str());
                button->copy_label(label);
                // button->color(fl_rgb_color(247, 17, 205));
                add(button);
                for (int i = y; i < y + rows; ++i) {
                    for (int j = x; j < x + cols; ++j) {
                        _gridElements[i][j] = button;
                    }
                }
                _widgetSizes[button] = std::make_pair(cols, rows);
                return button;
            }

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
            bool ValidPosition(int x, int y, int cols = 1, int rows = 1) {
                return x >= 0 && x + cols <= _numCols && y >= 0 && y + rows <= _numRows;
            }
        };
    }

    class GridButton : public UIButton {
        Impl::ButtonWithBetterBackgroundImage* _implButton;
        IGrid*                                 _grid;

    public:
        GridButton(IGrid* grid, Impl::ButtonWithBetterBackgroundImage* implButton)
            : _grid(grid), _implButton(implButton) {}

        GOOEY_FLTK_COLOR_SETTERS(_implButton)

        bool SetText(const char* text) override {
            _implButton->label(text);
            return true;
        }
        const char* GetText() override { return _implButton->label(); }

        bool AddBackgroundImage(
            const char* path, UIBackgroundImageStyle mode = UIBackgroundImageStyle::Default,
            UIHorizontalAlignment hAlign = UIHorizontalAlignment::Default,
            UIVerticalAlignment vAlign = UIVerticalAlignment::Default, unsigned int width = 0,
            unsigned int height = 0
        ) override {
            _implButton->SetBackgroundImage(path);
            return true;
        }
    };

    class Grid : public UIGrid, public IGrid, WidgetContainer {
        Impl::FLTK_Grid* _implGrid;

    public:
        Grid(Impl::PackWhichIncreasesSizeOfItsParent* pack, int numCols, int numRows)
            : _implGrid(new Impl::FLTK_Grid(
                  numCols, numRows, Defaults::GridCellWidth, Defaults::GridCellHeight,
                  Defaults::GridPadding
              )) {
            // _implGrid->AddButton(0, 0, 2, 2);
            // _implGrid->AddButton(2, 2, 1, 3);
            // _implGrid->AddButton(3, 0, 1, 4);
            // _implGrid->AddButton(6, 3, 2, 1);

            pack->add(_implGrid);
        }

        Impl::FLTK_Grid* GetImplGrid() { return _implGrid; }

        // Add Button
        UIButton* AddButton(
            const char* text, unsigned int x, unsigned int y, unsigned int cols, unsigned int rows
        ) override {
            auto implButton = _implGrid->AddButton(text, x, y, cols, rows);
            auto button     = std::make_unique<GridButton>(this, implButton);
            return static_cast<UIButton*>(AddWidget(std::move(button)));
        }

        // bool AddBackgroundImage(
        //     const char* path, UIBackgroundImageStyle mode = UIBackgroundImageStyle::Default,
        //     UIHorizontalAlignment hAlign = UIHorizontalAlignment::Default,
        //     UIVerticalAlignment vAlign = UIVerticalAlignment::Default, unsigned int width = 0,
        //     unsigned int height = 0
        // ) override {
        //     _implGrid->AddBackgroundImage(path);
        //     return true;
        // }

        // UIPanel* AddVerticalPanel() override {
        //     auto panel = std::make_unique<Panel>(_implPack, false);
        //     return static_cast<UIPanel*>(AddWidget(std::move(panel)));
        // }
    };
}
