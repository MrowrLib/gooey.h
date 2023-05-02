#pragma once

#include <gooey.h>
#include <wx/wx.h>

#include <string>

#include "Colors.h"
#include "CommonEvents.h"

namespace gooey::wxWidgetsAdapter {

    class Label : public UILabel, CommonEvents {
        std::string   _text;
        wxStaticText* implLabel;

    public:
        Label(wxWindow* window) : implLabel(new wxStaticText(window, wxID_ANY, "")) {
            window->GetSizer()->Add(implLabel, wxCENTER);
            SetImplWidget(implLabel);
        }

        GOOEY_WX_COLOR_SETTERS(implLabel)

        GOOEY_WX_ADD_COMMON_EVENTS()

        bool SetText(const char* text) override {
            implLabel->SetLabelText(text);
            return true;
        }
        const char* GetText() override {
            _text = implLabel->GetLabelText().ToStdString();
            return _text.c_str();
        }

        // bool SetFont(const char* fontName, unsigned int fontSize) override {
        //     wxFont font(fontSize, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
        //     implLabel->SetFont(font);
        //     return true;
        // }
    };
}
