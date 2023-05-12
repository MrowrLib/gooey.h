#pragma once

#include <cstdint>  // for Fl.H use of intptr_t
//

#include <FL/Fl.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_draw.H>

#include <cmath>

namespace gooey::fltk::impl {

    class FLTKAspectRatioGroupImpl : public Fl_Group {
        double aspect_ratio;

    public:
        FLTKAspectRatioGroupImpl(int X, int Y, int W, int H, const char* L = 0)
            : Fl_Group(X, Y, W, H, L), aspect_ratio(static_cast<double>(W) / H) {}

        void resize(int X, int Y, int W, int H) override {
            Fl::lock();
            double new_aspect_ratio = static_cast<double>(W) / H;
            if (abs(new_aspect_ratio - aspect_ratio) > 0.01) {
                if (H * aspect_ratio <= W) {
                    Fl_Group::resize(X, Y, static_cast<int>(H * aspect_ratio), H);
                } else {
                    Fl_Group::resize(X, Y, W, static_cast<int>(W / aspect_ratio));
                }
            } else {
                Fl_Group::resize(X, Y, W, H);
            }
            Fl::unlock();
            Fl::awake();
        }

        // void draw() override {
        //     // draw blue outline
        //     // fl_color(FL_BLUE);
        //     // fl_rect(x(), y(), w(), h());

        //     // background color blue
        //     fl_color(FL_BLUE);
        //     fl_rectf(x(), y(), w(), h());

        //     Fl_Group::draw();
        // }
    };
}