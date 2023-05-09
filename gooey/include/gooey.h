#pragma once

namespace gooey {

    extern "C" {

        struct UIDefaults {
            int  window_width   = 640;
            int  window_height  = 480;
            int  window_x       = 0;
            int  window_y       = 0;
            bool window_visible = true;
        };

        // struct UIObject {};

        // struct UIWidget {};

        // struct UIWidgetContainer {};

        struct UIApplication;
        struct UIWindow {
            virtual ~UIWindow()                                    = default;
            virtual UIApplication* get_application()               = 0;
            virtual bool           apply()                         = 0;
            virtual UIWindow*      set_title(const char* title)    = 0;
            virtual UIWindow*      set_size(int width, int height) = 0;
            virtual UIWindow*      set_position(int x, int y)      = 0;
            virtual UIWindow*      show()                          = 0;
        };

        struct UIApplication {
            virtual ~UIApplication()           = default;
            virtual UIDefaults* get_defaults() = 0;
            virtual UIWindow*   add_window()   = 0;
            virtual bool        render()       = 0;
            virtual bool        run_blocking() = 0;
            virtual bool        destroy()      = 0;
        };
    }
}