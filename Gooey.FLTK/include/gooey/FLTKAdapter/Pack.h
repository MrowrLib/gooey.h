#pragma once

#include <cstdint>
//

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Pack.H>
#include <FL/Fl_Shared_Image.H>
#include <FL/fl_draw.H>
#include <gooey.h>

#include <map>
#include <memory>

// #include "Colors.h"
// #include "Grid.h"
// #include "WidgetContainer.h"

namespace gooey::FLTKAdapter {

    namespace Impl {

        class PackWhichIncreasesSizeOfItsParent : public Fl_Pack {
        public:
            PackWhichIncreasesSizeOfItsParent(
                int x, int y, int w, int h, const char* label = nullptr
            )
                : Fl_Pack(x, y, w, h, label) {}

            void add(Fl_Widget* widget) {
                Fl_Pack::add(widget);
                update_parent_size();
            }

            void update_parent_size() {
                if (!parent()) return;

                int width  = 0;
                int height = 0;

                for (int i = 0; i < children(); ++i) {
                    Fl_Widget* widget = child(i);
                    width += widget->w();
                    height += widget->h();
                }

                parent()->size(width, height);
            }
        };
    }
}