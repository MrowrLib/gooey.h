#pragma once

#include <memory>

#include "../gooey.h"

namespace gooey {

    // struct UIObject {};

    // struct UIWidget {};

    // struct UIWidgetContainer {};

    struct UIApplication;
    class UIWindowBase : public UIWindow {
        UIApplication* _base_uiApplication;

    public:
        ~UIWindowBase() override = default;
        UIWindowBase(UIApplication* uiApplication) : _base_uiApplication(uiApplication) {}
        UIApplication* get_application() override { return _base_uiApplication; }
        bool           apply() override { return false; }
        UIWindow*      set_title(const char* title) override { return this; }
        UIWindow*      set_size(int width, int height) override { return this; }
        UIWindow*      set_position(int x, int y) override { return this; }
        UIWindow*      show() override { return this; }
    };

    class UIApplicationBase : public UIApplication {
        std::unique_ptr<UIDefaults> _base_uiDefaults;

    public:
        ~UIApplicationBase() override = default;
        UIApplicationBase() : _base_uiDefaults(std::make_unique<UIDefaults>()) {}
        UIDefaults* get_defaults() override { return _base_uiDefaults.get(); }
        UIWindow*   add_window() override { return nullptr; }
        bool        render() override { return false; }
        bool        run_blocking() override { return false; }
        bool        destroy() override { return false; }
    };
}