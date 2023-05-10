#pragma once

#include <cstdint>  // for Fl.H use of intptr_t
//

#include <FL/Fl.H>
#include <FL/Fl_Group.H>

namespace gooey::fltk::impl {

    class FLTKAutoProportionalGroupImpl : public Fl_Group {
        bool manage_width;
        bool manage_height;

    public:
        FLTKAutoProportionalGroupImpl(
            int X, int Y, int W, int H, bool manage_width = true, bool manage_height = false,
            const char* L = 0
        )
            : Fl_Group(X, Y, W, H, L), manage_width(manage_width), manage_height(manage_height) {}

        void resize(int X, int Y, int W, int H) override {
            Fl_Group::resize(X, Y, W, H);
            int num_children = children();

            int total_width  = 0;
            int total_height = 0;
            for (int i = 0; i < num_children; ++i) {
                Fl_Widget* child_widget = child(i);
                total_width += child_widget->w();
                total_height += child_widget->h();
            }

            int cur_x = X;
            int cur_y = Y;
            for (int i = 0; i < num_children; ++i) {
                Fl_Widget* child_widget = child(i);
                int        child_width  = child_widget->w();
                int        child_height = child_widget->h();

                if (manage_width) {
                    child_width = static_cast<int>(
                        W * (static_cast<double>(child_widget->w()) / total_width)
                    );
                }

                if (manage_height) {
                    child_height = static_cast<int>(
                        H * (static_cast<double>(child_widget->h()) / total_height)
                    );
                }

                child_widget->resize(cur_x, cur_y, child_width, child_height);

                if (manage_width) {
                    cur_x += child_width;
                }
                if (manage_height) {
                    cur_y += child_height;
                }
            }
        }
    };
}