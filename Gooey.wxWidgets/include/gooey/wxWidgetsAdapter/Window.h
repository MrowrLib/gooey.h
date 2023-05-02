#pragma once

#include <gooey.h>
#include <wx/wx.h>

#include "Colors.h"
#include "CommonEvents.h"
#include "Grid.h"
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

        GOOEY_WX_COLOR_SETTERS(implFrame)

        GOOEY_WX_ADD_COMMON_EVENTS()

        UILabel*  AddLabel(const char* text) override { return WidgetContainer::AddLabel(text); }
        UIButton* AddButton(const char* text) override { return WidgetContainer::AddButton(text); }
        UIImage*  AddImage(const char* path) override { return WidgetContainer::AddImage(path); }
        UIPanel*  AddHorizontalPanel() override {
            auto panel = std::make_unique<Panel>(implFrame, true);
            return static_cast<UIPanel*>(AddWidget(std::move(panel)));
        }
        UIPanel* AddVerticalPanel() override {
            auto panel = std::make_unique<Panel>(implFrame, false);
            return static_cast<UIPanel*>(AddWidget(std::move(panel)));
        }
        UIGrid* AddGrid(unsigned int cols, unsigned int rows) override {
            auto grid = std::make_unique<Grid>(implFrame, cols, rows);
            return static_cast<UIGrid*>(AddWidget(std::move(grid)));
        }

        bool SetTitle(const char* title) override {
            implFrame->SetTitle(title);
            return true;
        }

        bool Show() override {
            implFrame->SetSizeHints(400, 300);
            implFrame->Fit();
            return implFrame->Show();
        }
    };
}
