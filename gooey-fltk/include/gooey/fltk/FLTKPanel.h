#pragma once

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <gooey/base_classes.h>

#include <memory>
#include <vector>

#include "FLTKLabel.h"
#include "FLTKTextInput.h"
#include "Interfaces.h"
#include "impl/FLTKAutoProportionalGroupImpl.h"

namespace gooey::fltk {

    class FLTKPanel : public IFLTKPanel {
        std::unique_ptr<impl::FLTKAutoProportionalGroupImpl> _impl_group;
        IFLTKWindow*                                         _parentWindow;

    public:
        FLTKPanel(IFLTKWindow* parentWindow, bool horizontal) : _parentWindow(parentWindow) {
            _impl_group = std::make_unique<impl::FLTKAutoProportionalGroupImpl>(
                0, 0, 50, 50, horizontal, !horizontal
            );
        }

        // IFLTKLabel
        impl::FLTKAutoProportionalGroupImpl* get_impl() override { return _impl_group.get(); }

        // UIWidgetContainer
        UILabel* add_label(const char* text) override {
            auto* label = new FLTKLabel(_parentWindow);
            label->set_text(text);
            _impl_group->add(label->get_impl());
            return label;
        }
        UITextInput* add_text_input() override {
            auto* textInput = new FLTKTextInput(_parentWindow);
            _impl_group->add(textInput->get_impl());
            return textInput;
        }
        UIPanel* add_horizontal_panel(bool absolute) override {
            auto* panel = new FLTKPanel(_parentWindow, true);
            _impl_group->add(panel->get_impl());
            return panel;
        }
        UIPanel* add_vertical_panel(bool absolute) override {
            auto* panel = new FLTKPanel(_parentWindow, false);
            _impl_group->add(panel->get_impl());
            return panel;
        }

        // ...
        bool set_background_color(UIColor color) override {
            _impl_group->color(fl_rgb_color(color.red, color.green, color.blue));
            return true;
        }

        bool unset_background_color() override {
            _impl_group->color(FL_BACKGROUND_COLOR);
            return true;
        }

        // bool add_background_image(const char* imagePath) override {
        //     _impl_group->AddBackgroundImage(imagePath);
        //     return true;
        // }

        // bool remove_background_image(const char* imagePath) override {
        //     _impl_group->RemoveBackgroundImage(imagePath);
        //     return true;
        // }
    };
}