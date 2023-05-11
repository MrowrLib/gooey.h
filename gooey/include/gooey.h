#pragma once

#define uint unsigned int
#define cstring const char*

namespace gooey {

    extern "C" {

        enum class UIGridCellStyle { Button, Flat };

        struct UIColor {
            uint red   = 0;
            uint green = 0;
            uint blue  = 0;
        };

        struct UIDefaults {
            uint            window_width     = 640;
            uint            window_height    = 480;
            uint            window_x         = 0;
            uint            window_y         = 0;
            bool            window_visible   = true;
            UIColor         background_color = {255, 255, 255};
            UIColor         foreground_color = {0, 0, 0};
            UIGridCellStyle grid_cell_style  = UIGridCellStyle::Button;
        };

        // struct UIObject {};

        struct UIComponent {
            virtual ~UIComponent()                                  = default;
            virtual bool set_background_color(UIColor color)        = 0;
            virtual bool unset_background_color()                   = 0;
            virtual bool add_background_image(cstring imagePath)    = 0;
            virtual bool remove_background_image(cstring imagePath) = 0;
        };

        // struct UIWidget {};

        struct UILabel : public UIComponent {
            virtual ~UILabel()                                 = default;
            virtual bool     set_size(uint width, uint height) = 0;
            virtual bool     set_position(uint x, uint y)      = 0;
            virtual bool     set_text(cstring text)            = 0;
            virtual cstring* get_text()                        = 0;
        };

        struct UITextInput : public UIComponent {
            virtual ~UITextInput()                             = default;
            virtual bool     set_size(uint width, uint height) = 0;
            virtual bool     set_position(uint x, uint y)      = 0;
            virtual bool     set_text(cstring text)            = 0;
            virtual cstring* get_text()                        = 0;
        };

        struct UIGridCell {
            virtual ~UIGridCell()                             = default;
            virtual bool     set_text(cstring text)           = 0;
            virtual UILabel* get_text()                       = 0;
            virtual bool     set_style(UIGridCellStyle style) = 0;
        };

        struct UIGrid {
            virtual ~UIGrid() = default;
            virtual UIGridCell* add_cell(
                uint x, uint y, uint columnCount = 1, uint rowCount = 1, bool visible = true
            ) = 0;
        };

        // struct Panel <-- todo next

        struct UIPanel;

        struct UIWidgetContainer {
            virtual ~UIWidgetContainer() = default;
            // add children() (and make sure UIWidget has parent() - which will always be a
            // WidgetContainer))
            virtual UILabel*     add_label(cstring text) = 0;
            virtual UITextInput* add_text_input()        = 0;

            //
            virtual UIPanel* add_vertical_panel(bool absolute = false)   = 0;
            virtual UIPanel* add_horizontal_panel(bool absolute = false) = 0;

            //
            virtual UIGrid* add_grid(
                uint columnCount, uint rowCount, uint cellSize = 0, uint padding = 0
            ) = 0;
        };

        struct UIPanel : public UIWidgetContainer, public UIComponent {
            virtual ~UIPanel() = default;
            //
        };

        struct UIApplication;

        struct UIWindow : public UIComponent, public UIWidgetContainer {
            virtual ~UIWindow()                                      = default;
            virtual UIApplication* get_application()                 = 0;
            virtual bool           set_title(cstring title)          = 0;
            virtual bool           set_size(uint width, uint height) = 0;
            virtual bool           set_position(uint x, uint y)      = 0;
            virtual bool           show()                            = 0;
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

#undef uint
#undef cstring
