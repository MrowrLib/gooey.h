#pragma once

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <gooey/base_classes.h>

#include <memory>
#include <vector>

#include "FLTKGrid.h"
#include "FLTKLabel.h"
#include "FLTKPanel.h"
#include "FLTKTextInput.h"
#include "Interfaces.h"
#include "impl/FLTKWindowImpl.h"

namespace gooey::fltk {

    class FLTKWindow : public IFLTKWindow {
        std::unique_ptr<impl::FLTKWindowImpl> _impl_window;

    public:
        FLTKWindow(UIApplicationBase* parent) : gooey::UIWindowBase(parent) {
            auto* defaults = parent->get_defaults();
            _impl_window   = std::make_unique<impl::FLTKWindowImpl>(
                defaults->window_width, defaults->window_height
            );
        }

        // IFLTKWindow
        impl::FLTKWindowImpl* get_impl() override { return _impl_window.get(); }

        // ...
        bool set_title(const char* title) override {
            _impl_window->label(title);
            return true;
        }

        bool set_size(unsigned int width, unsigned int height) override {
            _impl_window->size(width, height);
            return true;
        }

        bool set_position(unsigned int x, unsigned int y) override {
            _impl_window->position(x, y);
            return true;
        }

        bool show() override {
            _impl_window->show();
            return true;
        }

        bool set_background_color(UIColor color) override {
            _impl_window->color(fl_rgb_color(color.red, color.green, color.blue));
            return true;
        }

        bool unset_background_color() override {
            _impl_window->color(FL_BACKGROUND_COLOR);
            return true;
        }

        bool add_background_image(const char* imagePath) override {
            _impl_window->AddBackgroundImage(imagePath);
            return true;
        }

        bool remove_background_image(const char* imagePath) override {
            _impl_window->RemoveBackgroundImage(imagePath);
            return true;
        }

        // TODO: track the pointers of our own structures (widgets collection of unique_ptr)

        // UIWidgetContainer
        UILabel* add_label(const char* text) override {
            auto* label = new FLTKLabel(this);
            label->set_text(text);
            _impl_window->add(label->get_impl());
            return label;
        }
        UITextInput* add_text_input() override {
            auto* textInput = new FLTKTextInput(this);
            _impl_window->add(textInput->get_impl());
            return textInput;
        }
        UIPanel* add_horizontal_panel(bool absolute) override {
            auto* panel = new FLTKPanel(this, true);
            _impl_window->add(panel->get_impl());
            return panel;
        }
        UIPanel* add_vertical_panel(bool absolute) override {
            auto* panel = new FLTKPanel(this, false);
            _impl_window->add(panel->get_impl());
            return panel;
        }
        UIGrid* add_grid(
            unsigned int columnCount, unsigned int rowCount, unsigned int cellSize,
            unsigned int padding
        ) override {
            auto* grid = new FLTKGrid();
            _impl_window->add(grid->get_impl());
            return grid;
        }
    };
}