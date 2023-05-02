#pragma once

#include <gooey.h>
#include <wx/wx.h>

#include <functional>
#include <string>

namespace gooey::wxWidgetsAdapter {

    class Button : public UIButton {
        std::string _text;
        wxButton*   implButton;
        // std::vector<std::function<void(UIButton*)>> _callbacks;

        // void RunClickCallbacks() {
        //     for (auto& callback : _callbacks) callback(this);
        // }

    public:
        Button(wxWindow* window) : implButton(new wxButton(window, wxID_ANY, "")) {
            window->GetSizer()->Add(implButton);
            implButton->Bind(wxEVT_BUTTON, [this](wxCommandEvent& event) {
                // RunClickCallbacks();
                event.Skip();
            });
            // implButton->Bind(wxEVT_BUTTON, [this](wxCommandEvent& event) {
            //     RunClickCallbacks();
            //     event.Skip();
            // });
        }

        bool SetText(const char* text) override {
            implButton->SetLabelText(text);
            return true;
        }
        const char* GetText() override {
            _text = implButton->GetLabelText().ToStdString();
            return _text.c_str();
        }

        // bool OnClick(void (*callback)(UIButton*)) override {
        //     _callbacks.push_back(callback);
        //     return true;
        // }

        // bool SetFont(const char* fontName, unsigned int fontSize) override {
        //     wxFont font(fontSize, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
        //     implButton->SetFont(font);
        //     return true;
        // }

        // bool SetBackgroundColor(unsigned int red, unsigned int green, unsigned int blue) override
        // {
        //     return implButton->SetBackgroundColour(wxColour(red, green, blue, 0));
        // }

        // bool SetForegroundColor(unsigned int red, unsigned int green, unsigned int blue) override
        // {
        //     return implButton->SetForegroundColour(wxColour(red, green, blue, 0));
        // }
    };
}
