#pragma once

#include <Windows.h>  // for icon support

#include <cstdint>  // <--- Require before FL/Fl.H
//

#include <FL/Fl.H>
#include <FL/Fl_Pack.H>
#include <FL/Fl_Shared_Image.H>
#include <FL/Fl_Window.H>
#include <FL/fl_ask.H>
#include <FL/fl_draw.H>
#include <FL/x.H>
#include <gooey.h>

#include <memory>

#include "Colors.h"
#include "Defaults.h"

// #include "Colors.h"
// #include "CommonEvents.h"
// #include "Grid.h"
// #include "Panel.h"
#include "Panel.h"
#include "WidgetContainer.h"

namespace gooey::FLTKAdapter {

    namespace Impl {
        class FLTKWindow : public Fl_Window {
            Fl_Pack                   _pack;
            std::unique_ptr<Fl_Image> _backgroundImage;
            UIBackgroundImageStyle    _BackgroundImageStyle = UIBackgroundImageStyle::Default;

        public:
            FLTKWindow(int w, int h) : Fl_Window(w, h), _pack(0, 0, w, h) {
                resizable(this);
                _pack.type(Fl_Pack::VERTICAL);
                _pack.spacing(10);  // Remove me

                // _backgroundImage.reset(Fl_Shared_Image::get("Logo.png")->copy());
            }

            Fl_Pack* GetFlPack() { return &_pack; }

            void SetBackgroundImage(const char* path, UIBackgroundImageStyle mode) {
                if (_backgroundImage) delete _backgroundImage.release();
                _backgroundImage      = std::make_unique<Fl_PNG_Image>(path);
                _BackgroundImageStyle = mode;
                if (_BackgroundImageStyle == UIBackgroundImageStyle::Default)
                    _BackgroundImageStyle = Defaults::BackgroundImageStyle;
            }

            // TODO GOALS: #1 - alignment #2 - overlapping

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

                // if (!_backgroundImage)
                //     _backgroundImage.reset(Fl_Shared_Image::get("Square.png")->copy());

                if (_backgroundImage) {
                    DrawBackgroundImage(x(), y(), w(), h());
                    // _backgroundImage->draw(0, 0, w(), h());
                    // fl_push_clip(x(), y(), w(), h());
                    // std::unique_ptr<Fl_Image> scaledImage(_backgroundImage->copy(w(), h()));
                    // scaledImage->draw(x(), y());
                    // fl_pop_clip();
                }
            }

            void resize(int x, int y, int w, int h) override {
                Fl_Window::resize(x, y, w, h);
                _pack.resize(0, 0, w, h);
                if (_backgroundImage) {
                    DrawBackgroundImage(x, y, w, h);
                    // _backgroundImage->draw(0, 0, w, h);
                }
            }
        };
    }

    class Frame : public UIWindow,
                  WidgetContainer {  //, CommonEvents {
        std::unique_ptr<Impl::FLTKWindow> _implWindow;

        void set_window_icon(Impl::FLTKWindow* window, const char* icon_path) {
            // Get the window handle
            HWND hwnd = fl_xid(window);

            // Load the icon from the file
            HICON hicon = (HICON)LoadImage(
                NULL, icon_path, IMAGE_ICON, 0, 0, LR_LOADFROMFILE | LR_DEFAULTSIZE | LR_SHARED
            );

            if (hicon) {
                // Set the window icon
                SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hicon);
                SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hicon);
            }
        }

    public:
        Frame()
            : _implWindow(
                  std::make_unique<Impl::FLTKWindow>(Defaults::WindowWidth, Defaults::WindowHeight)
              ) {
            SetImplFlPack(_implWindow.get()->GetFlPack());
        }

        GOOEY_FLTK_COLOR_SETTERS(_implWindow)

        UILabel*  AddLabel(const char* text) override { return WidgetContainer::AddLabel(text); }
        UIButton* AddButton(const char* text) override { return WidgetContainer::AddButton(text); }

        UIPanel* AddHorizontalPanel() override {
            auto panel = std::make_unique<Panel>(_implWindow.get()->GetFlPack(), true);
            return static_cast<UIPanel*>(AddWidget(std::move(panel)));
        }
        UIPanel* AddVerticalPanel() override {
            auto panel = std::make_unique<Panel>(_implWindow.get()->GetFlPack(), false);
            return static_cast<UIPanel*>(AddWidget(std::move(panel)));
        }

        bool SetTitle(const char* title) override {
            _implWindow->label(title);
            return true;
        }

        bool Show() override {
            _implWindow->show();
            // Here for when we want it later. Note it MUST be called AFTER show()
            // set_window_icon(_implWindow.get(), "xxx.ico");
            return true;
        }
    };
}