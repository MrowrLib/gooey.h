#pragma once

#include <cstdint>  // for Fl.H use of intptr_t
//

#include <FL/Fl.H>
#include <FL/Fl_Group.H>

#include <cmath>

namespace gooey::fltk::impl {

    class FLTKAspectRatioGroup : public Fl_Group {
        double aspect_ratio;

    public:
        FLTKAspectRatioGroup(int X, int Y, int W, int H, const char* L = 0)
            : Fl_Group(X, Y, W, H, L), aspect_ratio(static_cast<double>(W) / H) {}

        void resize(int X, int Y, int W, int H) override {
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
        }
    };
}