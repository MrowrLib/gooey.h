#pragma once

#include <gooey.h>
#include <wx/wx.h>

#include <functional>
#include <string>

#include "Colors.h"
#include "CommonEvents.h"

namespace gooey::wxWidgetsAdapter {

    class Button : public UIButton, CommonEvents {
        std::string _text;
        wxButton*   implButton;

    public:
        Button(wxWindow* window) : implButton(new wxButton(window, wxID_ANY, "")) {
            window->GetSizer()->Add(implButton, 0, wxEXPAND | wxALL);
            SetImplWidget(implButton);
        }

        GOOEY_WX_COLOR_SETTERS(implButton)

        GOOEY_WX_ADD_COMMON_EVENTS()
        GOOEY_WX_DEFINE_COMMON_EVENT_OVERRIDE(ButtonPress, wxEVT_BUTTON)

        bool SetText(const char* text) override {
            implButton->SetLabelText(text);
            return true;
        }
        const char* GetText() override {
            _text = implButton->GetLabelText().ToStdString();
            return _text.c_str();
        }
    };
}
