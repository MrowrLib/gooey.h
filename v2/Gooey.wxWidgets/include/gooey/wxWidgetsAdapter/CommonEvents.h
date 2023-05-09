#pragma once

#include <gooey.h>
#include <wx/wx.h>

#include <unordered_set>
#include <vector>

#define GOOEY_WX_DEFINE_COMMON_EVENT(eventName, eventType)                                        \
private:                                                                                          \
    std::vector<void (*)(UIWidget*)>  _on##eventName;                                             \
    std::unordered_set<wxEvtHandler*> _registeredFor##eventName;                                  \
                                                                                                  \
    bool Invoke##eventName() {                                                                    \
        for (auto& callback : _on##eventName) callback(nullptr);                                  \
        return true;                                                                              \
    }                                                                                             \
                                                                                                  \
public:                                                                                           \
    bool On##eventName(void (*callback)(UIWidget*)) {                                             \
        if (!callback) return false;                                                              \
        if (!GetImplWidget()) return false;                                                       \
        _on##eventName.push_back(callback);                                                       \
        if (_registeredFor##eventName.find(GetImplWidget()) == _registeredFor##eventName.end()) { \
            GetImplWidget()->Bind(eventType, [this](wxEvent& event) {                             \
                Invoke##eventName();                                                              \
                event.Skip();                                                                     \
            });                                                                                   \
            _registeredFor##eventName.insert(GetImplWidget());                                    \
        }                                                                                         \
        return true;                                                                              \
    }

#define GOOEY_WX_DEFINE_COMMON_EVENT_OVERRIDE(eventName, eventType)                               \
private:                                                                                          \
    std::vector<void (*)(UIWidget*)>  _on##eventName;                                             \
    std::unordered_set<wxEvtHandler*> _registeredFor##eventName;                                  \
                                                                                                  \
    bool Invoke##eventName() {                                                                    \
        for (auto& callback : _on##eventName) callback(nullptr);                                  \
        return true;                                                                              \
    }                                                                                             \
                                                                                                  \
public:                                                                                           \
    bool On##eventName(void (*callback)(UIWidget*)) override {                                    \
        if (!callback) return false;                                                              \
        if (!GetImplWidget()) return false;                                                       \
        _on##eventName.push_back(callback);                                                       \
        if (_registeredFor##eventName.find(GetImplWidget()) == _registeredFor##eventName.end()) { \
            GetImplWidget()->Bind(eventType, [this](wxEvent& event) {                             \
                Invoke##eventName();                                                              \
                event.Skip();                                                                     \
            });                                                                                   \
            _registeredFor##eventName.insert(GetImplWidget());                                    \
        }                                                                                         \
        return true;                                                                              \
    }

#define GOOEY_WX_ADD_COMMON_EVENTS()                               \
    bool OnMouseEnter(void (*callback)(UIWidget*)) override {      \
        CommonEvents::OnMouseEnter(callback);                      \
        return true;                                               \
    }                                                              \
    bool OnMouseLeave(void (*callback)(UIWidget*)) override {      \
        CommonEvents::OnMouseLeave(callback);                      \
        return true;                                               \
    }                                                              \
    bool OnLeftClick(void (*callback)(UIWidget*)) override {       \
        CommonEvents::OnLeftClick(callback);                       \
        return true;                                               \
    }                                                              \
    bool OnRightClick(void (*callback)(UIWidget*)) override {      \
        CommonEvents::OnRightClick(callback);                      \
        return true;                                               \
    }                                                              \
    bool OnMiddleClick(void (*callback)(UIWidget*)) override {     \
        CommonEvents::OnMiddleClick(callback);                     \
        return true;                                               \
    }                                                              \
    bool OnLeftDoubleClick(void (*callback)(UIWidget*)) override { \
        CommonEvents::OnLeftDoubleClick(callback);                 \
        return true;                                               \
    }

namespace gooey::wxWidgetsAdapter {

    class CommonEvents {
        wxEvtHandler* _implWidget;

    public:
        CommonEvents() : _implWidget(nullptr) {}
        explicit CommonEvents(wxEvtHandler* implWidget) : _implWidget(implWidget) {}

        void          SetImplWidget(wxEvtHandler* implWidget) { _implWidget = implWidget; }
        wxEvtHandler* GetImplWidget() { return _implWidget; }

        GOOEY_WX_DEFINE_COMMON_EVENT(MouseEnter, wxEVT_ENTER_WINDOW)
        GOOEY_WX_DEFINE_COMMON_EVENT(MouseLeave, wxEVT_LEAVE_WINDOW)
        GOOEY_WX_DEFINE_COMMON_EVENT(Button, wxEVT_BUTTON)
        GOOEY_WX_DEFINE_COMMON_EVENT(LeftClick, wxEVT_LEFT_DOWN)
        GOOEY_WX_DEFINE_COMMON_EVENT(RightClick, wxEVT_RIGHT_DOWN)
        GOOEY_WX_DEFINE_COMMON_EVENT(MiddleClick, wxEVT_MIDDLE_DOWN)
        GOOEY_WX_DEFINE_COMMON_EVENT(LeftDoubleClick, wxEVT_LEFT_DCLICK)
        GOOEY_WX_DEFINE_COMMON_EVENT(RightDoubleClick, wxEVT_RIGHT_DCLICK)
        GOOEY_WX_DEFINE_COMMON_EVENT(MiddleDoubleClick, wxEVT_MIDDLE_DCLICK)
        GOOEY_WX_DEFINE_COMMON_EVENT(Focus, wxEVT_SET_FOCUS)
        GOOEY_WX_DEFINE_COMMON_EVENT(Blur, wxEVT_KILL_FOCUS)
    };
}
