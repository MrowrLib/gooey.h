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
#include <FL/Fl_Window.H>
#include <FL/fl_draw.H>
#include <gooey.h>

#include <map>
#include <memory>

// #include "Colors.h"
// #include "Grid.h"
// #include "WidgetContainer.h"
#include "Defaults.h"

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

            void update_size() {
                int width  = 0;
                int height = 0;

                for (int i = 0; i < children(); ++i) {
                    Fl_Widget* widget = child(i);
                    width += widget->w();
                    height += widget->h();
                }

                MonitorResizeEvents = false;
                size(width, height);
                MonitorResizeEvents = true;
            }

            void set_parent_size(int W, int H) {
                if (!parent()) return;

                // If parent is a window, return
                if (dynamic_cast<Fl_Window*>(parent())) return;

                MonitorResizeEvents = false;
                parent()->size(W, H);
                MonitorResizeEvents = true;
            }

            std::pair<int, int> getFullWidthAndHeightOfChildren() {
                int width  = 0;
                int height = 0;

                for (int i = 0; i < children(); ++i) {
                    // Fl_Widget* widget = child(i);
                    // width += widget->w();
                    // height += widget->h();
                    if (auto* pack = dynamic_cast<PackWhichIncreasesSizeOfItsParent*>(child(i))) {
                        auto [w, h] = pack->getFullWidthAndHeightOfChildren();
                        width += w;
                        height += h;
                    } else {
                        width += child(i)->w();
                        height += child(i)->h();
                    }
                }

                return {width, height};
            }

            void update_parent_size() {
                if (!parent()) return;

                // If parent is a window, return
                if (dynamic_cast<Fl_Window*>(parent())) return;

                auto widthAndHeight = getFullWidthAndHeightOfChildren();

                int width  = widthAndHeight.first;
                int height = widthAndHeight.second;

                // int width  = 0;
                // int height = 0;

                // for (int i = 0; i < children(); ++i) {
                //     Fl_Widget* widget = child(i);
                //     if (auto* pack = dynamic_cast<PackWhichIncreasesSizeOfItsParent*>(widget)) {

                //     }
                //     // width += widget->w();
                //     // height += widget->h();

                // }

                MonitorResizeEvents = false;
                parent()->size(width, height);
                MonitorResizeEvents = true;
            }
        };
    }
}