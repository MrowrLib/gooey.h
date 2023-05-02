#pragma once

#include <gooey.h>
#include <wx/wx.h>

#include <string>

#include "CommonEvents.h"

namespace gooey::wxWidgetsAdapter {

    class Image : public UIImage, CommonEvents {
        wxStaticBitmap* implImage;

    public:
        Image(wxWindow* window, const char* path)
            : implImage(new wxStaticBitmap(window, wxID_ANY, wxBitmap(path, wxBITMAP_TYPE_ANY))) {
            window->GetSizer()->Add(implImage, 1, wxEXPAND | wxALL);
            SetImplWidget(implImage);
        }

        GOOEY_WX_ADD_COMMON_EVENTS()
    };
}
