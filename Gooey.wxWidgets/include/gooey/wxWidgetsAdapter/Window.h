#pragma once

#include <gooey.h>
#include <wx/wx.h>

#include "WidgetContainer.h"

namespace gooey::wxWidgetsAdapter {

    namespace Impl {
        class MyFrame : public wxFrame {
            wxBoxSizer* verticalSizer;

        public:
            MyFrame() : wxFrame(nullptr, wxID_ANY, "") {
                verticalSizer = new wxBoxSizer(wxVERTICAL);
                SetSizer(verticalSizer);
            }
        };
    }

    class Window : public UIWindow, public WidgetContainer {
        Impl::MyFrame* implFrame;

    public:
        Window() : implFrame(new Impl::MyFrame()) { SetImplWindow(implFrame); }

        bool Show() override { return implFrame->Show(); }

        bool SetTitle(const char* title) override {
            implFrame->SetTitle(title);
            return true;
        }

        UILabel*  AddLabel(const char* text) override { return WidgetContainer::AddLabel(text); }
        UIButton* AddButton(const char* text, void (*callback)(UIButton*)) override {
            return WidgetContainer::AddButton(text, callback);
        }

        // bool SetBackgroundColor(unsigned int red, unsigned int green, unsigned int blue) override
        // {
        //     return implFrame->SetBackgroundColour(wxColour(red, green, blue, 0));
        // }

        // bool SetForegroundColor(unsigned int red, unsigned int green, unsigned int blue) override
        // {
        //     return implFrame->SetForegroundColour(wxColour(red, green, blue, 0));
        // }
    };
}
