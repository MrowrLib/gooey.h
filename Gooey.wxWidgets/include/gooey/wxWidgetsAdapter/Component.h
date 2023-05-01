#pragma once

#include <gooey.h>
#include <wx/wx.h>

namespace gooey::wxWidgetsAdapter {

    class Component : public UIComponent {
        wxControl* implControl;

    protected:
        void SetWxControl(wxControl* control) { implControl = control; }

    public:
        bool SetBackgroundColor(unsigned int red, unsigned int green, unsigned int blue) override {
            if (!implControl) return false;
            return implControl->SetBackgroundColour(wxColour(red, green, blue, 0));
        }

        bool SetForegroundColor(unsigned int red, unsigned int green, unsigned int blue) override {
            if (!implControl) return false;
            return implControl->SetForegroundColour(wxColour(red, green, blue, 0));
        }
    }
}
