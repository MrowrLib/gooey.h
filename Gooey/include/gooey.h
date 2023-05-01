#pragma once

namespace gooey {

    struct UIComponent {
        // virtual bool IsDetached()                        = 0;
        // virtual void Detach()                                  = 0;
        // virtual void OnDetatch(void (*callback)(UIComponent*)) = 0;
        virtual bool SetBackgroundColor(unsigned int red, unsigned int green, unsigned int blue) {
            return false;
        }
        virtual bool SetForegroundColor(unsigned int red, unsigned int green, unsigned int blue) {
            return false;
        }
    };

    struct UIWidget {};

    struct UILabel : public UIWidget {
        virtual ~UILabel() = default;
        virtual bool        SetText(const char* text) { return false; }
        virtual const char* GetText() { return nullptr; }
    };

    struct UIButton : public UIWidget {
        virtual ~UIButton() = default;
        virtual bool        SetText(const char* text) { return false; }
        virtual const char* GetText() { return nullptr; }
        virtual bool        OnClick(void (*callback)(UIButton*)) { return false; }
        virtual bool        Click() { return false; }
    };

    struct UIPanel;

    struct UIWidgetContainer {
        virtual ~UIWidgetContainer() = default;
        virtual size_t    GetWidgetCount() { return 0; }
        virtual UIWidget* GetWidget(size_t index) { return nullptr; }
        virtual UIPanel*  AddHorizontalPanel() { return nullptr; }
        virtual UIPanel*  AddVerticalPanel() { return nullptr; }
        virtual UILabel*  AddLabel(const char* text) { return nullptr; }
        virtual UIButton* AddButton(const char* text, void (*callback)(UIButton*)) {
            return nullptr;
        }
        // virtual bool      AddImage(const char* path) { return false; }
        // virtual bool      AddSpacer(unsigned int size) { return false; }
    };

    struct UIGrid : public UIWidgetContainer {};

    struct UIPanel : public UIWidget, public UIWidgetContainer {
        virtual ~UIPanel() = default;
    };

    struct UITab : public UIWidgetContainer {};

    struct UIWindow : public UIComponent, public UIWidgetContainer {
        virtual ~UIWindow() = default;
        virtual bool        IsVisible() { return false; }
        virtual bool        Show() { return false; }
        virtual bool        Hide() { return false; }
        virtual bool        Close() { return false; }
        virtual bool        SetTitle(const char* title) { return false; }
        virtual const char* GetTitle() { return nullptr; }
        virtual bool        OnShow(void (*callback)(UIWindow*)) { return false; }
        virtual bool        OnHide(void (*callback)(UIWindow*)) { return false; }
        virtual bool        OnClose(void (*callback)(UIWindow*)) { return false; }
    };

    struct UIApplication {
        virtual ~UIApplication() = default;
        virtual bool      Start() { return false; }
        virtual bool      Shutdown() { return false; }
        virtual UIWindow* CreateWindow() { return nullptr; }
    };
}
