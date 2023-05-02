#pragma once

#include <gooey.h>
#include <wx/wx.h>

#include "CommonEvents.h"
#include "WidgetContainer.h"

namespace gooey::wxWidgetsAdapter {

    class Panel : public UIPanel, WidgetContainer, CommonEvents {
        wxPanel* implPanel;

    public:
        Panel(wxWindow* window, bool horizontal) {
            wxBoxSizer* sizer;
            if (horizontal) sizer = new wxBoxSizer(wxHORIZONTAL);
            else sizer = new wxBoxSizer(wxVERTICAL);
            implPanel = new wxPanel(window, wxID_ANY);
            implPanel->SetSizer(sizer);
            window->GetSizer()->Add(implPanel);
            SetImplWindow(implPanel);
            SetImplWidget(implPanel);
        }

        GOOEY_WX_ADD_COMMON_EVENTS()

        UIPanel* AddHorizontalPanel() override {
            if (!GetImplWindow()) return nullptr;
            auto panel = std::make_unique<Panel>(GetImplWindow(), true);
            return static_cast<UIPanel*>(AddWidget(std::move(panel)));
        }

        UIPanel* AddVerticalPanel() override {
            if (!GetImplWindow()) return nullptr;
            auto panel = std::make_unique<Panel>(GetImplWindow(), false);
            return static_cast<UIPanel*>(AddWidget(std::move(panel)));
        }

        UILabel* AddLabel(const char* text) override { return WidgetContainer::AddLabel(text); }

        // UISpacer* AddSpacer(unsigned int size) override { return
        // WidgetContainer::AddSpacer(size); }

        // bool SetBackgroundColor(unsigned int red, unsigned int green, unsigned int blue) override
        // {
        //     return implPanel->SetBackgroundColour(wxColour(red, green, blue, 0));
        // }

        // bool SetForegroundColor(unsigned int red, unsigned int green, unsigned int blue) override
        // {
        //     return implPanel->SetForegroundColour(wxColour(red, green, blue, 0));
        // }
    };
}
