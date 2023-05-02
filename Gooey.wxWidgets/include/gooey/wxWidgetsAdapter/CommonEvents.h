#pragma once

#include <gooey.h>
#include <wx/wx.h>

#include <unordered_set>
#include <vector>

namespace gooey::wxWidgetsAdapter {

    class CommonEvents {
        wxEvtHandler* _implWidget;

        std::vector<void (*)(UIWidget*)> _onButton;
        std::vector<void (*)(UIWidget*)> _onLeftClick;
        std::vector<void (*)(UIWidget*)> _onRightClick;
        std::vector<void (*)(UIWidget*)> _onMouseEnter;
        std::vector<void (*)(UIWidget*)> _onMouseLeave;

        std::unordered_set<wxEvtHandler*> _registeredForButton;
        std::unordered_set<wxEvtHandler*> _registeredForLeftClick;
        std::unordered_set<wxEvtHandler*> _registeredForRightClick;
        std::unordered_set<wxEvtHandler*> _registeredForMouseEnter;
        std::unordered_set<wxEvtHandler*> _registeredForMouseLeave;

        bool MouseEnter() {
            for (auto& callback : _onMouseEnter) callback(nullptr);
            return true;
        }

    public:
        CommonEvents() : _implWidget(nullptr) {}
        explicit CommonEvents(wxEvtHandler* implWidget) : _implWidget(implWidget) {}

        void SetImplWidget(wxEvtHandler* implWidget) { _implWidget = implWidget; }

        bool OnMouseEnter(void (*callback)(UIWidget*)) {
            if (!callback) return false;
            if (!_implWidget) return false;
            _onMouseEnter.push_back(callback);
            if (_registeredForMouseEnter.find(_implWidget) == _registeredForMouseEnter.end()) {
                _implWidget->Bind(wxEVT_ENTER_WINDOW, [this](wxMouseEvent& event) {
                    MouseEnter();
                    event.Skip();
                });
                _registeredForMouseEnter.insert(_implWidget);
            }
            return true;
        }

        bool OnMouseLeave(void (*callback)(UIWidget*)) {
            if (!callback) return false;
            if (!_implWidget) return false;
            _onMouseLeave.push_back(callback);
            if (_registeredForMouseLeave.find(_implWidget) == _registeredForMouseLeave.end()) {
                _implWidget->Bind(wxEVT_LEAVE_WINDOW, [this](wxMouseEvent& event) {
                    for (auto& callback : _onMouseLeave) callback(nullptr);
                    event.Skip();
                });
                _registeredForMouseLeave.insert(_implWidget);
            }
            return true;
        }
    };
}
