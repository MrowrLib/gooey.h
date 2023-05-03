#pragma once

#include <cstdint>
//

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Pack.H>
#include <FL/fl_draw.H>
#include <gooey.h>

#include <memory>

#include "Colors.h"
#include "WidgetContainer.h"

namespace gooey::FLTKAdapter {

    namespace Impl {
        class BackgroundImageBox : public Fl_Box {
            std::unique_ptr<Fl_PNG_Image> _image;

        public:
            BackgroundImageBox(int x, int y, int w, int h) : Fl_Box(x, y, w, h) {
                // box(FL_FLAT_BOX);
                // end();
            }

            void SetBackgroundImage(const char* path) {
                _image = std::make_unique<Fl_PNG_Image>(path);
            }

            void draw() override {
                // ONCE
                // if (_image) _image->draw(x(), y(), w(), h());

                // Repeating
                // if (_image) {
                //     fl_push_clip(x(), y(), w(), h());
                //     int imgW = _image->w();
                //     int imgH = _image->h();
                //     for (int X = x(); X < x() + w(); X += imgW) {
                //         for (int Y = y(); Y < y() + h(); Y += imgH) {
                //             _image->draw(X, Y, imgW, imgH, 0, 0);
                //         }
                //     }
                //     fl_pop_clip();
                // }

                // Stretch (maintain aspect ratio)
                // if (_image) {
                //     fl_push_clip(x(), y(), w(), h());

                //     // Calculate the aspect ratio of the image
                //     float imgAspectRatio =
                //         static_cast<float>(_image->w()) / static_cast<float>(_image->h());
                //     int drawW = w();
                //     int drawH = static_cast<int>(drawW / imgAspectRatio);

                //     // If the calculated height is less than the available height, adjust the
                //     width
                //     // accordingly
                //     if (drawH < h()) {
                //         drawH = h();
                //         drawW = static_cast<int>(drawH * imgAspectRatio);
                //     }

                //     _image->draw(x(), y(), drawW, drawH, 0, 0);

                //     fl_pop_clip();
                // }

                // Stetch (ignore aspect ratio)
                if (_image) {
                    fl_push_clip(x(), y(), w(), h());
                    std::unique_ptr<Fl_Image> scaledImage(_image->copy(w(), h()));
                    scaledImage->draw(x(), y());
                    fl_pop_clip();
                }

                Fl_Box::draw();
            }
        };
    }

    class Panel : public UIPanel, WidgetContainer {
        Fl_Group*                 _implGroup;
        Fl_Pack*                  _implPack;
        Impl::BackgroundImageBox* _implBackgroundImageBox;

    public:
        Panel(Fl_Pack* pack, bool horizontal)
            : _implGroup(new Fl_Group(0, 0, DefaultSizes::PanelWidth, DefaultSizes::PanelHeight)) {
            _implGroup->box(FL_UP_BOX);

            _implBackgroundImageBox = new Impl::BackgroundImageBox(
                0, 0, DefaultSizes::PanelWidth, DefaultSizes::PanelHeight
            );
            _implBackgroundImageBox->SetBackgroundImage("Logo.png");
            _implGroup->add(_implBackgroundImageBox);

            _implPack = new Fl_Pack(0, 0, DefaultSizes::PanelWidth, DefaultSizes::PanelHeight);
            _implPack->type(horizontal ? Fl_Pack::HORIZONTAL : Fl_Pack::VERTICAL);
            _implPack->spacing(10);  // Remove me

            // _implPack->end();
            _implGroup->end();
            SetImplFlPack(_implPack);
        }

        GOOEY_FLTK_COLOR_SETTERS(_implGroup)

        UILabel*  AddLabel(const char* text) override { return WidgetContainer::AddLabel(text); }
        UIButton* AddButton(const char* text) override { return WidgetContainer::AddButton(text); }

        // UIPanel* AddHorizontalPanel() override {
        // UIPanel* AddVerticalPanel() override {
    };
}
