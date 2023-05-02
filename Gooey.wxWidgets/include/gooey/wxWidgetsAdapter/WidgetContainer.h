#pragma once

#include <gooey.h>
#include <wx/wx.h>

#include <memory>

#include "Button.h"
#include "Label.h"

namespace gooey::wxWidgetsAdapter {

    class WidgetContainer : public UIWidgetContainer {
        wxWindow* implWindow;

        std::vector<std::unique_ptr<UIWidget>> widgets;

    public:
        WidgetContainer() = default;
        explicit WidgetContainer(wxWindow* window) : implWindow(window) {}

        UIWidget* AddWidget(std::unique_ptr<UIWidget> widget) {
            widgets.push_back(std::move(widget));
            return widgets.back().get();
        }

        wxWindow* GetImplWindow() { return implWindow; }
        void      SetImplWindow(wxWindow* window) { implWindow = window; }

        size_t    GetWidgetCount() override { return widgets.size(); }
        UIWidget* GetWidget(size_t index) override {
            if (index >= widgets.size()) return nullptr;
            return widgets[index].get();
        }

        UILabel* AddLabel(const char* text) override {
            if (!implWindow) return nullptr;
            auto label = std::make_unique<Label>(implWindow);
            label->SetText(text);
            widgets.push_back(std::move(label));
            return static_cast<UILabel*>(widgets.back().get());
        }

        UIButton* AddButton(const char* text) override {
            if (!implWindow) return nullptr;
            auto button = std::make_unique<Button>(implWindow);
            button->SetText(text);
            widgets.push_back(std::move(button));
            return static_cast<UIButton*>(widgets.back().get());
        }

        // bool AddImage(const char* path) override {
        //     wxImage image(path);
        //     if (!image.IsOk()) return false;
        //     wxBitmap        bitmap(image);
        //     wxStaticBitmap* staticBitmap = new wxStaticBitmap(implFrame, wxID_ANY, bitmap);
        //     implFrame->GetSizer()->Add(staticBitmap, 0, wxALL | wxALIGN_CENTER);
        //     return true;
        // }

        // bool AddSpacer(unsigned int size) override {
        //     implWindow->GetSizer()->AddSpacer(size);
        //     return true;
        // }
    };
}
