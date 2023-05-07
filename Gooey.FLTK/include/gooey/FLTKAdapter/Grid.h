#pragma once

#include <Windows.h>
//

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Pack.H>
#include <FL/Fl_Shared_Image.H>
#include <gooey.h>

#include <format>
#include <functional>
#include <map>
#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

#include "IGrid.h"
#include "Impl/GridBox.h"
#include "Impl/GridEvent.h"
#include "Pack.h"
#include "WidgetContainer.h"

namespace gooey::FLTKAdapter {

    namespace Impl {

        class BetterGridButton : public ButtonWithBetterBackgroundImage {
            unsigned int                                       _row;
            unsigned int                                       _column;
            std::unique_ptr<Fl_PNG_Image>                      _image;
            std::vector<void (*)(unsigned int, unsigned int)>& _mouseOverCallbacks;
            std::vector<void (*)(unsigned int, unsigned int)>& _mouseLeaveCallbacks;
            std::vector<void (*)(unsigned int, unsigned int)>& _mouseLeftClickCallbacks;
            std::vector<void (*)(unsigned int, unsigned int)>& _mouseRightClickCallbacks;

        public:
            BetterGridButton(
                int x, int y, int w, int h,
                std::vector<void (*)(unsigned int, unsigned int)>& mouseOverCallbacks,
                std::vector<void (*)(unsigned int, unsigned int)>& mouseLeaveCallbacks,
                std::vector<void (*)(unsigned int, unsigned int)>& mouseLeftClickCallbacks,
                std::vector<void (*)(unsigned int, unsigned int)>& mouseRightClickCallbacks
            )
                : ButtonWithBetterBackgroundImage(x, y, w, h),
                  _mouseOverCallbacks(mouseOverCallbacks),
                  _mouseLeaveCallbacks(mouseLeaveCallbacks),
                  _mouseLeftClickCallbacks(mouseLeftClickCallbacks),
                  _mouseRightClickCallbacks(mouseRightClickCallbacks) {}

            void SetRow(unsigned int row) { _row = row; }
            void SetColumn(unsigned int column) { _column = column; }

            void SetBackgroundImage(const char* path) {
                _image = std::make_unique<Fl_PNG_Image>(path);
            }

            void OnMouseOver(void (*callback)(unsigned int, unsigned int)) {
                _mouseOverCallbacks.push_back(callback);
            }
            void OnMouseLeave(void (*callback)(unsigned int, unsigned int)) {
                _mouseLeaveCallbacks.push_back(callback);
            }
            void OnLeftClick(void (*callback)(unsigned int, unsigned int)) {
                _mouseLeftClickCallbacks.push_back(callback);
            }
            void OnRightClick(void (*callback)(unsigned int, unsigned int)) {
                _mouseRightClickCallbacks.push_back(callback);
            }

            int handle(int event) override {
                int x = _column;
                int y = _row;

                if (event == FL_ENTER)
                    for (auto& callback : _mouseOverCallbacks) callback(x, y);
                else if (event == FL_LEAVE)
                    for (auto& callback : _mouseLeaveCallbacks) callback(x, y);
                else if (event == FL_PUSH) {
                    if (Fl::event_button() == FL_LEFT_MOUSE) {
                        for (auto& callback : _mouseLeftClickCallbacks) callback(x, y);
                    } else if (Fl::event_button() == FL_RIGHT_MOUSE)
                        for (auto& callback : _mouseRightClickCallbacks) callback(x, y);
                }

                return Fl_Button::handle(event);
            }

            void draw() override {
                Fl_Color box_color = value() ? selection_color() : color();
                draw_box(value() ? (down_box() ? down_box() : fl_down(box())) : box(), box_color);

                if (_image) {
                    int img_x = x() + Fl::box_dx(box());
                    int img_y = y() + Fl::box_dy(box());
                    int img_w = w() - Fl::box_dw(box());
                    int img_h = h() - Fl::box_dh(box());

                    fl_push_clip(img_x, img_y, img_w, img_h);
                    std::unique_ptr<Fl_Image> scaledImage(_image->copy(img_w, img_h));
                    scaledImage->draw(img_x, img_y, img_w, img_h);
                    fl_pop_clip();
                }

                // Draw label
                draw_label();
            }
        };

        class FLTK_Grid : public Fl_Group {
            std::vector<void (*)(unsigned int, unsigned int)> _mouseOverCallbacks;
            std::vector<void (*)(unsigned int, unsigned int)> _mouseLeaveCallbacks;
            std::vector<void (*)(unsigned int, unsigned int)> _mouseLeftClickCallbacks;
            std::vector<void (*)(unsigned int, unsigned int)> _mouseRightClickCallbacks;
            std::unique_ptr<Fl_Color>                         _backgroundColor;
            int                                               _numCols, _numRows;
            int                                               _cellWidth, _cellHeight, _padding;
            std::vector<std::vector<Fl_Widget*>>              _gridElements;
            std::map<Fl_Widget*, std::pair<int, int>>         _widgetSizes;
            int                                               _initialWidth, _initialHeight;
            Fl_Shared_Image*                                  _backgroundImage = nullptr;
            std::function<void(GridEvent, int, int)>          _eventsCallback;

            void OnButtonMouseOver(unsigned int x, unsigned int y) {
                int columnNumber = x / (_cellWidth + _padding);
                int rowNumber    = y / (_cellHeight + _padding);
                for (auto& callback : _mouseOverCallbacks) callback(columnNumber, rowNumber);
            }
            void OnButtonMouseLeave(unsigned int x, unsigned int y) {
                int columnNumber = x / (_cellWidth + _padding);
                int rowNumber    = y / (_cellHeight + _padding);
                for (auto& callback : _mouseLeaveCallbacks) callback(columnNumber, rowNumber);
            }
            void OnButtonLeftClick(unsigned int x, unsigned int y) {
                int columnNumber = x / (_cellWidth + _padding);
                int rowNumber    = y / (_cellHeight + _padding);
                for (auto& callback : _mouseLeftClickCallbacks) callback(columnNumber, rowNumber);
            }
            void OnButtonRightClick(unsigned int x, unsigned int y) {
                int columnNumber = x / (_cellWidth + _padding);
                int rowNumber    = y / (_cellHeight + _padding);
                for (auto& callback : _mouseRightClickCallbacks) callback(columnNumber, rowNumber);
            }

        public:
            FLTK_Grid(int numCols, int numRows, int cellWidth, int cellHeight, int padding)
                : Fl_Group(0, 0, numCols * (cellWidth + padding), numRows * (cellHeight + padding)),
                  _numCols(numCols),
                  _numRows(numRows),
                  _cellWidth(cellWidth),
                  _cellHeight(cellHeight),
                  _padding(padding) {
                activate();
                resizable(this);

                _initialWidth  = w();
                _initialHeight = h();

                end();
                box(FL_NO_BOX);

                _gridElements.resize(_numRows, std::vector<Fl_Widget*>(_numCols, nullptr));
                for (int i = 0; i < _numRows; ++i) {
                    for (int j = 0; j < _numCols; ++j) {
                        AddButton("", j, i, 1, 1, false);
                    }
                }
            }

            void OnCellMouseOver(void (*callback)(unsigned int, unsigned int)) {
                _mouseOverCallbacks.push_back(callback);
            }
            void OnCellMouseLeave(void (*callback)(unsigned int, unsigned int)) {
                _mouseLeaveCallbacks.push_back(callback);
            }
            void OnCellLeftClick(void (*callback)(unsigned int, unsigned int)) {
                _mouseLeftClickCallbacks.push_back(callback);
            }
            void OnCellRightClick(void (*callback)(unsigned int, unsigned int)) {
                _mouseRightClickCallbacks.push_back(callback);
            }

            int GetInitialWidth() const { return _initialWidth; }
            int GetInitialHeight() const { return _initialHeight; }

            void SetBackgroundColor(Fl_Color color) {
                _backgroundColor = std::make_unique<Fl_Color>(color);
            }

            void SetBackgroundImage(const char* imagePath) {}

            void draw() override {
                // Draw the background color
                if (_backgroundColor) {
                    fl_color(*_backgroundColor);
                    fl_rectf(x(), y(), w(), h());
                }

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

            Impl::BetterGridButton* AddButton(
                const char* label, int x, int y, int cols, int rows, bool replace = true
            ) {
                if (!ValidPosition(x, y, cols, rows)) return nullptr;
                if (replace) ClearRange(x, y, cols, rows);
                auto button = new Impl::BetterGridButton(
                    x * (_cellWidth + _padding), y * (_cellHeight + _padding),
                    cols * _cellWidth + (cols - 1) * _padding,
                    rows * _cellHeight + (rows - 1) * _padding, _mouseOverCallbacks,
                    _mouseLeaveCallbacks, _mouseLeftClickCallbacks, _mouseRightClickCallbacks
                );

                button->SetColumn(x);
                button->SetRow(y);

                button->copy_label(label);

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
        Impl::FLTK_Grid*                                             _implGrid;
        std::vector<std::function<void(unsigned int, unsigned int)>> _cellLeftClickHandlers;

    public:
        Grid(Impl::PackWhichIncreasesSizeOfItsParent* pack, int numCols, int numRows)
            : _implGrid(new Impl::FLTK_Grid(
                  numCols, numRows, Defaults::GridCellWidth, Defaults::GridCellHeight,
                  Defaults::GridPadding
              )) {
            pack->add(_implGrid);
        }

        // EVENTS
        bool OnCellMouseOver(void (*callback)(unsigned int, unsigned int)) override {
            _implGrid->OnCellMouseOver(callback);
            return true;
        }
        bool OnCellMouseLeave(void (*callback)(unsigned int, unsigned int)) override {
            _implGrid->OnCellMouseLeave(callback);
            return true;
        }
        bool OnCellLeftClick(void (*callback)(unsigned int, unsigned int)) override {
            _implGrid->OnCellLeftClick(callback);
            return true;
        }
        bool OnCellRightClick(void (*callback)(unsigned int, unsigned int)) override {
            _implGrid->OnCellRightClick(callback);
            return true;
        }
        // // // // //

        Impl::FLTK_Grid* GetImplGrid() { return _implGrid; }

        bool SetBackgroundColor(unsigned int red, unsigned int green, unsigned int blue) override {
            // widget->color(fl_rgb_color(red, green, blue));
            _implGrid->SetBackgroundColor(fl_rgb_color(red, green, blue));
            return true;
        }

        bool SetForegroundColor(unsigned int red, unsigned int green, unsigned int blue) override {
            // widget->labelcolor(fl_rgb_color(red, green, blue));
            return true;
        }

        // bool OnCellLeftClick(void (*callback)(unsigned int, unsigned int)) override {
        //     _cellLeftClickHandlers.push_back(callback);
        //     return true;
        // }

        // Add Button
        UIButton* AddButton(
            const char* text, unsigned int x, unsigned int y, unsigned int cols, unsigned int rows
        ) override {
            auto implButton = _implGrid->AddButton(text, x, y, cols, rows);
            auto button     = std::make_unique<GridButton>(this, implButton);
            return static_cast<UIButton*>(AddWidget(std::move(button)));
        }

        bool AddBackgroundImage(
            const char* path, UIBackgroundImageStyle mode = UIBackgroundImageStyle::Default,
            UIHorizontalAlignment hAlign = UIHorizontalAlignment::Default,
            UIVerticalAlignment vAlign = UIVerticalAlignment::Default, unsigned int width = 0,
            unsigned int height = 0
        ) override {
            _implGrid->SetBackgroundImage(path);
            return true;
        }
    };
}

// UIPanel* AddVerticalPanel() override {
//     auto panel = std::make_unique<Panel>(_implPack, false);
//     return static_cast<UIPanel*>(AddWidget(std::move(panel)));
// }

// int handle(int event) override {
//     if (event == FL_PUSH) {
//         fl_message("PUSH!");
//         if (Fl::event_button() == FL_LEFT_MOUSE) {
//             fl_message("LEFT!");
//             if (Fl::event_clicks()) {
//                 fl_message("TWO?");
//             } else {
//                 fl_message("ONE!");
//                 fl_message("Left click at (%d, %d)", Fl::event_x(), Fl::event_y());
//                 // for (auto& callback : _callbacks[GridEventType::LeftClick]) {
//                 //     callback(GridEvent{
//                 //         GridEventType::LeftClick, _x, _y, _columnCount,
//                 _rowCount});
//                 // }
//             }
//         }
//     }
//     return Fl_Group::handle(event);
// }

// int handle(int event) override {
//     switch (event) {
//         case FL_PUSH:
//             if (Fl::event_button() == FL_LEFT_MOUSE) {
//                 if (Fl::event_clicks()) {
//                     // printf("Left double click\n");
//                 } else {
//                     printf("Left click\n");
//                     int x = Fl::event_x();
//                     int y = Fl::event_y();
//                 }
//             }
//             // } else if (Fl::event_button() == FL_RIGHT_MOUSE) {
//             //     printf("Right click\n");
//             // }
//             return 1;
//         // case FL_ENTER:
//         //     printf("Mouse over\n");
//         //     return 1;
//         // case FL_LEAVE:
//         //     printf("Mouse leave\n");
//         //     return 1;
//         default:
//             return Fl_Group::handle(event);
//     }
// }

// void AddBackgroundImage(const char* imagePath) {
//     if (_backgroundImage) _backgroundImage->release();

//     _backgroundImage = Fl_Shared_Image::get(imagePath);
//     if (!_backgroundImage)
//         throw std::runtime_error(std::format("Failed to load image: {}", imagePath));
//     // _backgroundImage->scale(w(), h(), 1, 1);
// }