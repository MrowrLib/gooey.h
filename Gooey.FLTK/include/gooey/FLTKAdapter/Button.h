#pragma once

#include <FL/Fl.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_Pack.H>
#include <FL/fl_ask.H>
#include <FL/fl_draw.H>
#include <gooey.h>

#include <memory>
#include <string>
#include <vector>

#include "Colors.h"
#include "Defaults.h"
#include "IGrid.h"
#include "Pack.h"

namespace gooey::FLTKAdapter {

    namespace Impl {
        class ButtonWithBetterBackgroundImage : public Fl_Button {
            std::unique_ptr<Fl_PNG_Image>                     _image;
            std::unique_ptr<Fl_Color>                         _backgroundColor;
            std::vector<void (*)(unsigned int, unsigned int)> _mouseOverCallbacks;
            std::vector<void (*)(unsigned int, unsigned int)> _mouseLeaveCallbacks;
            std::vector<void (*)(unsigned int, unsigned int)> _mouseLeftClickCallbacks;
            std::vector<void (*)(unsigned int, unsigned int)> _mouseRightClickCallbacks;

        public:
            ButtonWithBetterBackgroundImage(int x, int y, int w, int h) : Fl_Button(x, y, w, h) {}

            void SetBackgroundImage(const char* path) {
                _image = std::make_unique<Fl_PNG_Image>(path);
            }

            void SetBackgroundColor(unsigned int red, unsigned int green, unsigned int blue) {
                _backgroundColor = std::make_unique<Fl_Color>(fl_rgb_color(red, green, blue));
            }

            void SetBackgroundColor(Fl_Color color) {
                _backgroundColor = std::make_unique<Fl_Color>(color);
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
                int x = Fl::event_x();
                int y = Fl::event_y();

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
                // Fl_Color box_color = value() ? selection_color() : color();
                // draw_box(value() ? (down_box() ? down_box() : fl_down(box())) : box(),
                // box_color);
                if (_backgroundColor) {
                    fl_color(*_backgroundColor);
                    fl_rectf(x(), y(), w(), h());
                } else {
                    Fl_Button::draw();
                }

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
    }

    class Button : public UIButton {
        Impl::ButtonWithBetterBackgroundImage* _implButton;

    public:
        Button() = default;
        Button(Impl::PackWhichIncreasesSizeOfItsParent* pack)
            : _implButton(new Impl::ButtonWithBetterBackgroundImage(
                  0, 0, Defaults::ButtonWidth, Defaults::ButtonHeight
              )) {
            // _implButton->SetBackgroundImage("Logo.png");
            pack->add(_implButton);
        }

        GOOEY_FLTK_COLOR_SETTERS(_implButton)

        bool SetText(const char* text) override {
            _implButton->label(text);
            return true;
        }
        const char* GetText() override { return _implButton->label(); }
    };
}

// Draw image if available

// ONCE
// if (_image) {
//     fl_push_clip(
//         x() + Fl::box_dx(box()), y() + Fl::box_dy(box()), w() -
//         Fl::box_dw(box()), h() - Fl::box_dh(box())
//     );
//     _image->draw(x() + Fl::box_dx(box()), y() + Fl::box_dy(box()));
//     fl_pop_clip();
// }

// STRETCH