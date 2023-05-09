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

        struct UIComponent {
            virtual bool set_background_color(int red, int green, int blue) = 0;
            virtual bool unset_background_color()                           = 0;
            virtual bool add_background_image(const char* imagePath)        = 0;
            virtual bool remove_background_image(const char* imagePath)     = 0;
        };

        // struct UIWidget {};

        // struct UIWidgetContainer {};

        struct UIApplication;
        struct UIWindow : public UIComponent {
            virtual ~UIWindow()                                    = default;
            virtual UIApplication* get_application()               = 0;
            virtual bool           set_title(const char* title)    = 0;
            virtual bool           set_size(int width, int height) = 0;
            virtual bool           set_position(int x, int y)      = 0;
            virtual bool           show()                          = 0;
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