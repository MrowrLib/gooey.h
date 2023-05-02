#pragma once

#include <gooey.h>
#include <wx/wx.h>

#include <memory>

#include "Window.h"

namespace gooey::wxWidgetsAdapter {

    namespace Impl {
        class Application : public wxApp {
        public:
            bool OnInit() override { return true; }
        };
    }

    class Application : public UIApplication {
        Impl::Application* implApp;

    public:
        Application() {
            wxImage::AddHandler(new wxPNGHandler);
            implApp = new Impl::Application();
            wxApp::SetInstance(implApp);
            wxEntryStart(0, nullptr);
            wxTheApp->CallOnInit();
        }

        bool Start() override {
            wxTheApp->OnRun();  // Blocks until exit!
            wxTheApp->OnExit();
            wxEntryCleanup();
            return true;
        }

        bool Shutdown() override {
            wxTheApp->ExitMainLoop();
            wxTheApp->OnExit();
            wxEntryCleanup();
            return true;
        }

        UIWindow* AddWindow() override { return new Window(); }
    };
}
