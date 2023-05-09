#pragma once

#include <memory>

#include "../gooey.h"

namespace gooey {

    // struct UIObject {};

    // struct UIWidget {};

    // struct UIWidgetContainer {};

    class UIComponentBase : public UIComponent {
        bool set_background_color(int red, int green, int blue) { return false; }
        bool unset_background_color() { return false; }
        bool add_background_image(const char* imagePath) { return false; }
        bool remove_background_image(const char* imagePath) { return false; }
    };

    struct UIApplication;
    class UIWindowBase : public UIWindow, public UIComponentBase {
        UIApplication* _base_uiApplication;

    public:
        ~UIWindowBase() override = default;
        UIWindowBase(UIApplication* uiApplication) : _base_uiApplication(uiApplication) {}
        UIApplication* get_application() override { return _base_uiApplication; }
        bool           set_title(const char* title) override { return false; }
        bool           set_size(int width, int height) override { return false; }
        bool           set_position(int x, int y) override { return false; }
        bool           show() override { return false; }
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