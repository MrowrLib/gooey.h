#pragma once

#include <gooey.h>
#include <wx/wx.h>

#include "Colors.h"
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
            window->GetSizer()->Add(
                implPanel, 1, wxEXPAND | wxALL, 5
            );  // Adding a final param here for border results in a cool look
            SetImplWindow(implPanel);
            SetImplWidget(implPanel);
        }

        GOOEY_WX_COLOR_SETTERS(implPanel)

        GOOEY_WX_ADD_COMMON_EVENTS()

        UILabel*  AddLabel(const char* text) override { return WidgetContainer::AddLabel(text); }
        UIButton* AddButton(const char* text) override { return WidgetContainer::AddButton(text); }
        UIImage*  AddImage(const char* path) override { return WidgetContainer::AddImage(path); }

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
    };
}
