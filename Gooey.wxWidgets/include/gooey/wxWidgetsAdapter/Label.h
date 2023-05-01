#pragma once

#include <gooey.h>
#include <wx/wx.h>

#include <string>

namespace gooey::wxWidgetsAdapter {

    class Label : public UILabel {
        std::string   _text;
        wxStaticText* implLabel;

    public:
        Label(wxWindow* window) : implLabel(new wxStaticText(window, wxID_ANY, "")) {
            window->GetSizer()->Add(implLabel);
        }

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

        // bool SetBackgroundColor(unsigned int red, unsigned int green, unsigned int blue) override
        // {
        //     return implLabel->SetBackgroundColour(wxColour(red, green, blue, 0));
        // }

        // bool SetForegroundColor(unsigned int red, unsigned int green, unsigned int blue) override
        // {
        //     return implLabel->SetForegroundColour(wxColour(red, green, blue, 0));
        // }
    };
}
