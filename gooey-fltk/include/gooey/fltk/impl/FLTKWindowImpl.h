#pragma once

#include <FL/Fl.H>
#include <FL/Fl_Pack.H>
#include <FL/Fl_Window.H>
#include <gooey/base_classes.h>

#include "FLTKAspectRatioGroupImpl.h"
#include "FLTKAutoProportionalGroupImpl.h"
#include "FLTKBackgroundImageCollection.h"

namespace gooey::fltk::impl {

    class FLTKWindowImpl : public Fl_Window {
        FLTKAspectRatioGroupImpl*      aspect_ratio_group;
        FLTKAutoProportionalGroupImpl* full_size_group;
        FLTKBackgroundImageCollection  _backgroundImagesCollection;

    public:
        FLTKWindowImpl(int width, int height, const char* title = 0)
            : Fl_Window(width, height, title) {
            resizable(this);

            aspect_ratio_group = new FLTKAspectRatioGroupImpl(0, 0, w(), h());
            full_size_group    = new FLTKAutoProportionalGroupImpl(
                   0, 0, aspect_ratio_group->w(), aspect_ratio_group->h(), true, true
               );

            aspect_ratio_group->add(full_size_group);
            aspect_ratio_group->end();

            resizable(aspect_ratio_group);
            end();
        }

        void add(Fl_Widget* widget) { full_size_group->add(widget); }

        // void draw() override {
        //     aspect_ratio_group->resize(0, 0, w(), h());
        //     aspect_ratio_group->redraw();
        //     Fl_Window::draw();
        //     _backgroundImagesCollection.DrawAll(x(), y(), w(), h());
        // }

        void draw() override {
            // Draw the background images.
            _backgroundImagesCollection.DrawAll(x(), y(), w(), h());

            // Resize and redraw the aspect_ratio_group.
            aspect_ratio_group->resize(0, 0, w(), h());
            aspect_ratio_group->redraw();

            // Draw each child.
            for (int i = 0; i < children(); ++i) {
                Fl_Widget* child_widget = child(i);
                draw_child(*child_widget);
            }
        }

        // TODO - change the casing to snake_case
        bool AddBackgroundImage(const std::string& imagePath) {
            return _backgroundImagesCollection.AddImage(imagePath);
        }
        bool RemoveBackgroundImage(const std::string& imagePath) {
            return _backgroundImagesCollection.RemoveImage(imagePath);
        }
    };
}