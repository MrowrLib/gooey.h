#pragma once

namespace gooey {

    extern "C" {
        enum class UIBackgroundImageStyle { Default, Original, Fill, Repeat };

        enum class UIVerticalAlignment { Default, Top, Center, Bottom };

        enum class UIHorizontalAlignment { Default, Left, Center, Right };

        struct UIComponent {
            // TODO
            // virtual bool IsDetached()                        = 0;
            // virtual void Detach()                                  = 0;
            // virtual void OnDetatch(void (*callback)(UIComponent*)) = 0;

            UIComponent* GetParent() { return nullptr; }

            virtual bool SetBackgroundColor(
                unsigned int red, unsigned int green, unsigned int blue
            ) {
                return false;
            }
            virtual bool SetForegroundColor(
                unsigned int red, unsigned int green, unsigned int blue
            ) {
                return false;
            }
            virtual bool AddBackgroundImage(
                const char* path, UIBackgroundImageStyle mode = UIBackgroundImageStyle::Default,
                UIHorizontalAlignment hAlign = UIHorizontalAlignment::Default,
                UIVerticalAlignment vAlign = UIVerticalAlignment::Default, unsigned int width = 0,
                unsigned int height = 0
            ) {
                return false;
            }
            virtual bool RemoveBackgroundImage(const char* path) { return false; }
        };

        struct UIWidget;

        struct UICommonEvents {
            virtual bool OnMouseEnter(void (*callback)(UIWidget*)) { return false; }
            virtual bool OnMouseLeave(void (*callback)(UIWidget*)) { return false; }
            virtual bool OnLeftClick(void (*callback)(UIWidget*)) { return false; }
            virtual bool OnRightClick(void (*callback)(UIWidget*)) { return false; }
            virtual bool OnMiddleClick(void (*callback)(UIWidget*)) { return false; }
            virtual bool OnLeftDoubleClick(void (*callback)(UIWidget*)) { return false; }
            virtual bool OnRightDoubleClick(void (*callback)(UIWidget*)) { return false; }
            virtual bool OnMiddleDoubleClick(void (*callback)(UIWidget*)) { return false; }
        };

        struct UIWidget : public UIComponent, public UICommonEvents {
            virtual bool Show() { return false; }
            virtual bool Hide() { return false; }
        };

        // struct UISpacer : public UIWidget {
        //     virtual ~UISpacer() = default;
        // };

        struct UIImage : public UIWidget {};

        struct UILabel : public UIWidget {
            virtual ~UILabel() = default;
            virtual bool        SetText(const char* text) { return false; }
            virtual const char* GetText() { return nullptr; }
        };

        struct UIButton : public UIWidget {
            virtual ~UIButton() = default;
            virtual bool        SetText(const char* text) { return false; }
            virtual const char* GetText() { return nullptr; }
            virtual bool        OnButtonPress(void (*callback)(UIWidget*)) { return false; }
            virtual bool        SetFlat() { return false; }
        };

        struct UIPanel;
        struct UIGrid;

        struct UIWidgetContainer {
            virtual ~UIWidgetContainer() = default;
            virtual size_t    GetWidgetCount() { return 0; }
            virtual UIWidget* GetWidget(size_t index) { return nullptr; }
            virtual UIPanel*  AddHorizontalPanel() { return nullptr; }
            virtual UIPanel*  AddVerticalPanel() { return nullptr; }
            virtual UIGrid*   AddGrid(unsigned int cols, unsigned int rows) { return nullptr; }
            virtual UILabel*  AddLabel(const char* text) { return nullptr; }
            virtual UIButton* AddButton(const char* text) { return nullptr; }
            virtual UIImage*  AddImage(const char* path) { return nullptr; }
            // virtual UISpacer* AddSpacer(unsigned int size) { return nullptr; }
        };

        struct UIGrid : public UIWidget, public UIWidgetContainer {
            virtual ~UIGrid() = default;
            virtual bool      HasElementAt(unsigned int x, unsigned int y) { return false; }
            virtual bool      RemoveElementAt(unsigned int x, unsigned int y) { return false; }
            virtual UIWidget* GetWidgetAt(unsigned int x, unsigned int y) { return nullptr; }
            virtual bool      ConfigureGridLines(
                     bool enabled, unsigned int red, unsigned int green, unsigned int blue
                 ) {
                return false;
            }
            virtual bool SetDefaultCellColor(
                unsigned int red, unsigned int green, unsigned int blue
            ) {
                return false;
            }
            virtual bool SetDefaultCellBackgroundImage(
                const char* path, UIBackgroundImageStyle mode = UIBackgroundImageStyle::Default,
                UIHorizontalAlignment hAlign = UIHorizontalAlignment::Default,
                UIVerticalAlignment vAlign = UIVerticalAlignment::Default, unsigned int width = 0,
                unsigned int height = 0
            ) {
                return false;
            }
            virtual bool Clear() { return false; }
            virtual bool ClearRange(
                unsigned int x, unsigned int y, unsigned int cols, unsigned int rows
            ) {
                return false;
            }
            virtual bool OnCellMouseOver(void (*callback)(unsigned int, unsigned int)) {
                return false;
            }
            virtual bool OnCellMouseLeave(void (*callback)(unsigned int, unsigned int)) {
                return false;
            }
            virtual bool OnCellLeftClick(void (*callback)(unsigned int, unsigned int)) {
                return false;
            }
            virtual bool OnCellRightClick(void (*callback)(unsigned int, unsigned int)) {
                return false;
            }
            virtual UIPanel* AddHorizontalPanel(
                unsigned int x, unsigned int y, unsigned int cols, unsigned int rows
            ) {
                return nullptr;
            }
            virtual UIPanel* AddVerticalPanel(
                unsigned int x, unsigned int y, unsigned int cols, unsigned int rows
            ) {
                return nullptr;
            }
            virtual UIGrid* AddGrid(
                unsigned int cols, unsigned int rows, unsigned int x, unsigned int y,
                unsigned int childCols, unsigned int childRows
            ) {
                return nullptr;
            }
            virtual UILabel* AddLabel(
                const char* text, unsigned int x, unsigned int y, unsigned int cols,
                unsigned int rows
            ) {
                return nullptr;
            }
            virtual UIButton* AddButton(
                const char* text, unsigned int x, unsigned int y, unsigned int cols,
                unsigned int rows
            ) {
                return nullptr;
            }
            virtual UIImage* AddImage(
                const char* path, unsigned int x, unsigned int y, unsigned int cols,
                unsigned int rows
            ) {
                return nullptr;
            }
        };

        struct UIPanel : public UIWidget, public UIWidgetContainer {
            virtual ~UIPanel() = default;
        };

        struct UITab : public UIWidgetContainer {};

        struct UIWindow : public UIComponent, public UIWidgetContainer, public UICommonEvents {
            virtual ~UIWindow() = default;
            // virtual bool OnClick(void (*callback)(UIWindow*)) { return false; }
            // virtual bool OnMouseEnter(void (*callback)(UIWindow*)) { return false; }
            // virtual bool OnMouseLeave(void (*callback)(UIWindow*)) { return false; }
            // virtual bool OnClose(void (*callback)(UIWindow*)) { return false; }
            // virtual bool OnHide(void (*callback)(UIWindow*)) { return false; }
            // virtual bool OnShow(void (*callback)(UIWindow*)) { return false; }
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
            virtual UIWindow* AddWindow() { return nullptr; }
        };
    }
}