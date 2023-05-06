#pragma once

#include <Windows.h>  // for icon support

#include <cstdint>  // <--- Require before FL/Fl.H
//

#include <FL/Enumerations.H>
#include <FL/Fl.H>
#include <FL/Fl_Pack.H>
#include <FL/Fl_Shared_Image.H>
#include <FL/Fl_Window.H>
#include <FL/fl_ask.H>
#include <FL/fl_draw.H>
#include <FL/x.H>
#include <gooey.h>

#include <map>
#include <memory>

#include "Colors.h"
#include "Defaults.h"
#include "Grid.h"
#include "Pack.h"
#include "Panel.h"
#include "WidgetContainer.h"

namespace gooey::FLTKAdapter {

    namespace Impl {
        class FLTKWindow : public Fl_Window {
            int                                      _initialWidth = 0, _initialHeight = 0;
            Impl::PackWhichIncreasesSizeOfItsParent* _pack;
            std::unique_ptr<Fl_Image>                _backgroundImage;
            UIBackgroundImageStyle _BackgroundImageStyle = UIBackgroundImageStyle::Default;

        public:
            FLTKWindow(int w, int h)
                : Fl_Window(w, h),
                  _pack(new Impl::PackWhichIncreasesSizeOfItsParent(0, 0, w, h)),
                  _initialWidth(w),
                  _initialHeight(h) {
                resizable(this);
                _pack->type(Fl_Pack::VERTICAL);
                _pack->init_sizes();
                resizable(_pack);
            }

            Impl::PackWhichIncreasesSizeOfItsParent* GetFlPack() { return _pack; }

            void SetBackgroundImage(const char* path, UIBackgroundImageStyle mode) {
                if (_backgroundImage) delete _backgroundImage.release();
                _backgroundImage      = std::make_unique<Fl_PNG_Image>(path);
                _BackgroundImageStyle = mode;
                if (_BackgroundImageStyle == UIBackgroundImageStyle::Default)
                    _BackgroundImageStyle = Defaults::BackgroundImageStyle;
            }

            void DrawBackgroundImage(
                int x, int y, int w, int h,
                UIBackgroundImageStyle mode = UIBackgroundImageStyle::Default
            ) {
                fl_push_clip(x, y, w, h);
                std::unique_ptr<Fl_Image> scaledImage(_backgroundImage->copy(w, h));
                scaledImage->draw(x, y);
                fl_pop_clip();
            }

            void draw() override {
                Fl_Window::draw();

                if (_backgroundImage) DrawBackgroundImage(x(), y(), w(), h());
            }

            void show() override {
                Fl_Window::show();
                this->init_sizes();
                this->redraw();
            }

            void resizeGridWidget(Fl_Widget* widget, int W, int H) {
                if (!MonitorResizeEvents) return;
                if (FLTK_Grid* grid = dynamic_cast<FLTK_Grid*>(widget)) {
                    grid->resize(0, 0, W, H);
                } else if (Fl_Pack* pack = dynamic_cast<Fl_Pack*>(widget)) {
                    // pack->resize(0, 0, W, H);
                    for (int i = 0; i < pack->children(); ++i) {
                        Fl_Widget* child_widget = pack->child(i);
                        resizeGridWidget(child_widget, W, H);
                    }
                    // if (Impl::PackWhichIncreasesSizeOfItsParent* ourPack =
                    //         dynamic_cast<Impl::PackWhichIncreasesSizeOfItsParent*>(widget)) {
                    //     ourPack->update_parent_size();
                    // }
                } else if (Fl_Group* group = dynamic_cast<Fl_Group*>(widget)) {
                    // group->resize(0, 0, W, H);
                    for (int i = 0; i < group->children(); ++i) {
                        Fl_Widget* child_widget = group->child(i);
                        resizeGridWidget(child_widget, W, H);
                    }
                }
            }

            void resizeOurPacks(Fl_Widget* widget, int W, int H) {
                if (!MonitorResizeEvents) return;
                if (PackWhichIncreasesSizeOfItsParent* pack =
                        dynamic_cast<PackWhichIncreasesSizeOfItsParent*>(widget)) {
                    // grid->resize(0, 0, W, H);
                    pack->update_parent_size();
                } else if (Fl_Pack* pack = dynamic_cast<Fl_Pack*>(widget)) {
                    pack->resize(0, 0, W, H);
                    for (int i = 0; i < pack->children(); ++i) {
                        Fl_Widget* child_widget = pack->child(i);
                        resizeOurPacks(child_widget, W, H);
                    }
                    // if (Impl::PackWhichIncreasesSizeOfItsParent* ourPack =
                    //         dynamic_cast<Impl::PackWhichIncreasesSizeOfItsParent*>(widget)) {
                    //     ourPack->update_parent_size();
                    // }
                } else if (Fl_Group* group = dynamic_cast<Fl_Group*>(widget)) {
                    group->resize(0, 0, W, H);
                    for (int i = 0; i < group->children(); ++i) {
                        Fl_Widget* child_widget = group->child(i);
                        resizeOurPacks(child_widget, W, H);
                    }
                }
            }

            // void resizeOtherCollectionWidget(Fl_Widget* widget, int W, int H) {
            //     if (!MonitorResizeEvents) return;
            //     if (FLTK_Grid* grid = dynamic_cast<FLTK_Grid*>(widget)) {
            //         // grid->resize(0, 0, W, H);
            //     } else if (Fl_Pack* pack = dynamic_cast<Fl_Pack*>(widget)) {
            //         // pack->resize(0, 0, W, H);
            //         for (int i = 0; i < pack->children(); ++i) {
            //             Fl_Widget* child_widget = pack->child(i);
            //             resizeOtherCollectionWidget(child_widget, W, H);
            //         }
            //         // if (Impl::PackWhichIncreasesSizeOfItsParent* ourPack =
            //         //         dynamic_cast<Impl::PackWhichIncreasesSizeOfItsParent*>(widget)) {
            //         //     ourPack->update_parent_size();
            //         // }
            //     } else if (Fl_Group* group = dynamic_cast<Fl_Group*>(widget)) {
            //         // group->resize(0, 0, W, H);
            //         for (int i = 0; i < group->children(); ++i) {
            //             Fl_Widget* child_widget = group->child(i);
            //             resizeOtherCollectionWidget(child_widget, W, H);
            //         }
            //     }
            // }

            void resize(int x, int y, int w, int h) override {
                if (!MonitorResizeEvents) return;

                for (int i = 0; i < children(); ++i) {
                    Fl_Widget* widget = child(i);
                    resizeGridWidget(widget, w, h);
                }

                Fl_Window::resize(x, y, w, h);

                for (int i = 0; i < children(); ++i) {
                    Fl_Widget* widget = child(i);
                    resizeOurPacks(widget, w, h);
                }

                // Again?
                for (int i = 0; i < children(); ++i) {
                    Fl_Widget* widget = child(i);
                    resizeOurPacks(widget, w, h);
                }

                _pack->update_parent_size();
            }

            // void resize(int X, int Y, int W, int H) override {
            //     Fl_Window::resize(X, Y, W, H);
            //     for (int i = 0; i < children(); ++i) {
            //         Fl_Widget* widget = child(i);
            //         process_widget(widget, W, H);
            //     }
            // }

            void process_widget(Fl_Widget* widget, int W, int H) {
                if (FLTK_Grid* grid = dynamic_cast<FLTK_Grid*>(widget)) {
                    grid->resize(0, 0, W, H);
                } else if (Fl_Pack* pack = dynamic_cast<Fl_Pack*>(widget)) {
                    for (int i = 0; i < pack->children(); ++i) {
                        Fl_Widget* child_widget = pack->child(i);
                        process_widget(child_widget, W, H);
                        pack->resize(0, 0, W, H);
                    }
                }
            }
        };
    }

    class Frame : public UIWindow, WidgetContainer {
        Impl::FLTKWindow* _implWindow;

    public:
        Frame() : _implWindow(new Impl::FLTKWindow(Defaults::WindowWidth, Defaults::WindowHeight)) {
            SetImplFlPack(_implWindow->GetFlPack());
        }

        GOOEY_FLTK_COLOR_SETTERS(_implWindow)

        UILabel*  AddLabel(const char* text) override { return WidgetContainer::AddLabel(text); }
        UIButton* AddButton(const char* text) override { return WidgetContainer::AddButton(text); }

        UIPanel* AddHorizontalPanel() override {
            auto panel = std::make_unique<Panel>(_implWindow->GetFlPack(), true);
            return static_cast<UIPanel*>(AddWidget(std::move(panel)));
        }
        UIPanel* AddVerticalPanel() override {
            auto panel = std::make_unique<Panel>(_implWindow->GetFlPack(), false);
            return static_cast<UIPanel*>(AddWidget(std::move(panel)));
        }
        UIGrid* AddGrid(unsigned int cols, unsigned int rows) override {
            auto grid = std::make_unique<Grid>(_implWindow->GetFlPack(), cols, rows);
            return static_cast<UIGrid*>(AddWidget(std::move(grid)));
        }

        bool SetTitle(const char* title) override {
            _implWindow->label(title);
            return true;
        }

        bool Show() override {
            _implWindow->show();
            // Fl::check();
            // _implWindow->resize(
            //     _implWindow->x(), _implWindow->y(), _implWindow->w(), _implWindow->h()
            // );
            // _implWindow->redraw();
            return true;
        }
    };
}
