#pragma once

#include <gooey.h>
#include <wx/gbsizer.h>
#include <wx/grid.h>
#include <wx/wx.h>

#include "Colors.h"
#include "CommonEvents.h"
#include "WidgetContainer.h"

namespace gooey::wxWidgetsAdapter {

    class Grid : public UIGrid, WidgetContainer, CommonEvents {
        wxPanel*        implPanel;
        wxGridBagSizer* gridBagSizer;

    public:
        Grid(wxWindow* window, unsigned int cols, unsigned int rows) {
            gridBagSizer = new wxGridBagSizer(0, 0);
            implPanel    = new wxPanel(window, wxID_ANY);
            implPanel->SetSizer(gridBagSizer);

            for (int i = 0; i <= rows; ++i) {
                auto* spacerButton1 = new wxButton(
                    implPanel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxBORDER_NONE
                );
                spacerButton1->SetBackgroundColour(*wxWHITE);
                gridBagSizer->Add(
                    spacerButton1, wxGBPosition(i, 0), wxGBSpan(1, 1), wxEXPAND | wxALL
                );
                auto* spacerButton2 = new wxButton(
                    implPanel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxBORDER_NONE
                );
                spacerButton2->SetBackgroundColour(*wxWHITE);
                gridBagSizer->Add(
                    spacerButton2, wxGBPosition(i, cols), wxGBSpan(1, 1), wxEXPAND | wxALL
                );
            }
            for (int i = 1; i < cols; ++i) {
                auto* spacerButton1 = new wxButton(
                    implPanel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxBORDER_NONE
                );
                spacerButton1->SetBackgroundColour(*wxWHITE);
                gridBagSizer->Add(
                    spacerButton1, wxGBPosition(0, i), wxGBSpan(1, 1), wxEXPAND | wxALL
                );
                auto* spacerButton2 = new wxButton(
                    implPanel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxBORDER_NONE
                );
                spacerButton2->SetBackgroundColour(*wxWHITE);
                gridBagSizer->Add(
                    spacerButton2, wxGBPosition(rows, i), wxGBSpan(1, 1), wxEXPAND | wxALL
                );
            }

            for (int i = 0; i < rows; ++i) gridBagSizer->AddGrowableRow(i);
            for (int i = 0; i < cols; ++i) gridBagSizer->AddGrowableCol(i);

            window->GetSizer()->Add(implPanel, 1, wxEXPAND | wxALL);

            SetImplWindow(implPanel);
            SetImplWidget(implPanel);
        }

        GOOEY_WX_COLOR_SETTERS(implPanel)

        GOOEY_WX_ADD_COMMON_EVENTS()

        UIButton* AddButton(
            const char* text, unsigned int x, unsigned int y, unsigned int cols, unsigned int rows
        ) override {
            auto button = std::make_unique<Button>(implPanel, false);
            button->SetText(text);
            gridBagSizer->Add(
                button->GetImplButton(), wxGBPosition(x, y), wxGBSpan(cols, rows), wxEXPAND | wxALL
            );
            return static_cast<UIButton*>(AddWidget(std::move(button)));
        }
    };
}
