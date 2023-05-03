#pragma once

#include <Windows.h>  // for icon support

#include <cstdint>  // <--- Require before FL/Fl.H
//

#include <FL/Fl.H>
#include <FL/Fl_Pack.H>
#include <FL/Fl_Window.H>
#include <FL/x.H>
#include <gooey.h>

#include <memory>

#include "Colors.h"
#include "DefaultSizes.h"

// #include "Colors.h"
// #include "CommonEvents.h"
// #include "Grid.h"
// #include "Panel.h"
#include "Panel.h"
#include "WidgetContainer.h"

namespace gooey::FLTKAdapter {

    namespace Impl {
        class WindowWithFullSizePack : public Fl_Window {
            Fl_Pack _pack;

        public:
            WindowWithFullSizePack(int w, int h) : Fl_Window(w, h), _pack(0, 0, w, h) {
                resizable(this);
                _pack.type(Fl_Pack::VERTICAL);
                _pack.spacing(10);  // Remove me
                // _pack.end();
                // end();
            }

            Fl_Pack* GetFlPack() { return &_pack; }

        protected:
            void resize(int x, int y, int w, int h) {
                Fl_Window::resize(x, y, w, h);
                _pack.resize(0, 0, w, h);
            }
        };
    }

    class Window : public UIWindow, WidgetContainer {  //, CommonEvents {
        std::unique_ptr<Impl::WindowWithFullSizePack> _implWindow;

        // Impl::MyFrame* implFrame;

        void set_window_icon(Impl::WindowWithFullSizePack* window, const char* icon_path) {
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
        Window()
            : _implWindow(std::make_unique<Impl::WindowWithFullSizePack>(
                  DefaultSizes::WindowWidth, DefaultSizes::WindowHeight
              )) {
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
