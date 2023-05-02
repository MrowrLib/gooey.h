#pragma once

#include <gooey.h>
#include <wx/wx.h>

#include "CommonEvents.h"
#include "Panel.h"
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

    class Window : public UIWindow, WidgetContainer, CommonEvents {
        Impl::MyFrame* implFrame;

    public:
        Window() : implFrame(new Impl::MyFrame()) {
            SetImplWindow(implFrame);
            SetImplWidget(implFrame);
        }

        GOOEY_WX_ADD_COMMON_EVENTS()

        bool Show() override { return implFrame->Show(); }

        bool SetTitle(const char* title) override {
            implFrame->SetTitle(title);
            return true;
        }

        UILabel*  AddLabel(const char* text) override { return WidgetContainer::AddLabel(text); }
        UIButton* AddButton(const char* text) override { return WidgetContainer::AddButton(text); }

        UIPanel* AddHorizontalPanel() override {
            auto panel = std::make_unique<Panel>(implFrame, true);
            return static_cast<UIPanel*>(AddWidget(std::move(panel)));
        }

        UIPanel* AddVerticalPanel() override {
            auto panel = std::make_unique<Panel>(implFrame, false);
            return static_cast<UIPanel*>(AddWidget(std::move(panel)));
        }

        // UIPanel* AddHorizontalPanel() override {
        //     if (!implWindow) return nullptr;
        //     auto panel = std::make_unique<Panel>(implWindow, true);
        //     widgets.push_back(std::move(panel));
        //     return static_cast<UIPanel*>(widgets.back().get());
        // }

        // UIPanel* AddVerticalPanel() override {
        //     if (!implWindow) return nullptr;
        //     auto panel = std::make_unique<Panel>(implWindow, false);
        //     widgets.push_back(std::move(panel));
        //     return static_cast<UIPanel*>(widgets.back().get());
        // }

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
