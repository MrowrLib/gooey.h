#pragma once

#include <memory>
#include <nana/gui.hpp>
#include <nana/gui/place.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/checkbox.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/panel.hpp>
#include <nana/gui/widgets/slider.hpp>
#include <nana/gui/widgets/tabbar.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <string>
#include <unordered_map>
#include <vector>

#include "../../micro_ui.h"

namespace MicroUI::Nana {

    class Label : public UILabel {
        nana::label _nanaLabel;

    public:
        Label(nana::panel<true>* nanaPanel) : _nanaLabel(*nanaPanel) {}

        nana::label* GetNanaLabel() { return &_nanaLabel; }
        void         SetText(const char* text) { _nanaLabel.caption(text); }
        const char*  GetText() { return nullptr; }
    };

    class Textbox : public UITextbox {
        nana::textbox _nanaTextbox;

    public:
        Textbox(nana::panel<true>* nanaPanel) : _nanaTextbox(*nanaPanel) {}

        nana::textbox* GetNanaTextbox() { return &_nanaTextbox; }
        void           SetText(const char* text) { _nanaTextbox.caption(text); }
        const char*    GetText() { return nullptr; }
    };

    class Button : public UIButton {
        std::string  _text;
        nana::button _nanaButton;

    public:
        Button(nana::panel<true>* nanaPanel, void (*callback)(UIButton*))
            : _nanaButton(*nanaPanel) {
            _nanaButton.events().click([&, callback]() { callback(static_cast<UIButton*>(this)); });
        }

        nana::button* GetNanaButton() { return &_nanaButton; }
        const char*   GetText() override {
            _text = _nanaButton.caption();
            return _text.c_str();
        }
        void SetText(const char* text) override { _nanaButton.caption(text); }
    };

    class WidgetContainer : public UIWidgetContainer {
        std::string _fieldsPlaceString;
        // TODO: why is this a unique_ptr? Try to make it a vector<UIWidget*>
        std::unique_ptr<std::vector<std::unique_ptr<UIWidget>>> _widgets;
        nana::panel<true>*                                      _nanaPanel;
        nana::place*                                            _nanaPanelPlace;

    public:
        WidgetContainer(
            const std::string& fieldsPlaceString, nana::panel<true>* nanaPanel,
            nana::place* nanaPanelPlace
        )
            : _fieldsPlaceString(fieldsPlaceString),
              _widgets(std::make_unique<std::vector<std::unique_ptr<UIWidget>>>()),
              _nanaPanel(nanaPanel),
              _nanaPanelPlace(nanaPanelPlace) {}

        UILabel* AddLabel(const char* text) override {
            auto* label = new Label(_nanaPanel);
            label->SetText(text);
            _nanaPanelPlace->field(_fieldsPlaceString.c_str()) << *label->GetNanaLabel();
            _nanaPanelPlace->collocate();
            _widgets->push_back(std::unique_ptr<UIWidget>(label));
            return label;
        }
        UITextbox* AddTextbox(const char* text) override {
            auto* textbox = new Textbox(_nanaPanel);
            textbox->SetText(text);
            _nanaPanelPlace->field(_fieldsPlaceString.c_str()) << *textbox->GetNanaTextbox();
            _nanaPanelPlace->collocate();
            _widgets->push_back(std::unique_ptr<UIWidget>(textbox));
            return textbox;
        }
        UIButton* AddButton(const char* text, void (*callback)(UIButton*)) override {
            auto* button = new Button(_nanaPanel, callback);
            button->SetText(text);
            _nanaPanelPlace->field(_fieldsPlaceString.c_str()) << *button->GetNanaButton();
            _nanaPanelPlace->collocate();
            _widgets->push_back(std::unique_ptr<UIWidget>(button));
            return button;
        }
    };

    class Window;

    class Tab : public WidgetContainer, public UITab {
        std::string       _title;
        nana::panel<true> _nanaPanel;
        nana::place       _nanaPlace;
        nana::place*      _windowPlace;

    public:
        Tab(nana::form* nanaForm, nana::place* windowPlace, const char* title)
            : WidgetContainer("fields", &_nanaPanel, &_nanaPlace),
              _title(title),
              _nanaPanel(*nanaForm),
              _nanaPlace(_nanaPanel),
              _windowPlace(windowPlace) {
            _nanaPlace.div("vert <vert fields gap=5 arrange=[25,repeated]>");
        }

        nana::panel<true>* GetNanaPanel() { return &_nanaPanel; }
        void               Show() { _nanaPanel.show(); }
        void               Hide() { _nanaPanel.hide(); }

        const char* GetTitle() override { return _title.c_str(); }
        UILabel*    AddLabel(const char* text) override {
            auto* label = WidgetContainer::AddLabel(text);
            _nanaPlace.collocate();
            _windowPlace->collocate();
            return label;
        }
        UITextbox* AddTextbox(const char* text) override {
            auto* textbox = WidgetContainer::AddTextbox(text);
            _nanaPlace.collocate();
            _windowPlace->collocate();
            return textbox;
        }
        UIButton* AddButton(const char* text, void (*callback)(UIButton*)) override {
            auto* button = WidgetContainer::AddButton(text, callback);
            _nanaPlace.collocate();
            _windowPlace->collocate();
            return button;
        }
    };

    class Window : public WidgetContainer, public UIWindow {
        std::function<void()>             _onCloseCallback;
        bool                              _isVisible       = false;
        bool                              _tabsInitialized = false;
        std::vector<std::unique_ptr<Tab>> _tabs;
        nana::form                        _nanaForm{};
        nana::place                       _nanaMainPlace{_nanaForm};
        nana::panel<true>                 _nanaWindowWidgetsPanel{_nanaForm};
        nana::place                       _nanaWindowWidgetsPlace{_nanaWindowWidgetsPanel};
        nana::tabbar<std::string>         _nanaTabBar{_nanaForm};

        void InitializeTabs() {
            if (_tabsInitialized) return;
            _nanaMainPlace.div("vert <tabBar weight=30><tabPanels><mainWidgetsPanel>");
            _nanaMainPlace.field("tabBar") << _nanaTabBar;
            _nanaMainPlace.collocate();
            _tabsInitialized = true;
            _nanaTabBar.events().activated([&](const nana::arg_tabbar<std::string>& tabbar) {
                for (size_t i = 0; i < _tabs.size(); i++) {
                    if (tabbar.item_pos == i) {
                        _tabs[i]->Show();
                    } else {
                        _tabs[i]->Hide();
                    }
                }
            });
        }

    public:
        Window(std::function<void()> onCloseCallback)
            : _onCloseCallback(onCloseCallback),
              WidgetContainer("fields", &_nanaWindowWidgetsPanel, &_nanaWindowWidgetsPlace) {
            _nanaMainPlace.div("vert <mainWidgetsPanel margin=5>");
            _nanaMainPlace.field("mainWidgetsPanel") << _nanaWindowWidgetsPanel;
            _nanaMainPlace.collocate();
            _nanaWindowWidgetsPlace.div("vert <vert fields gap=5 arrange=[25,repeated]>");
            _nanaForm.events().unload([&](const nana::arg_unload& arg) {
                _isVisible = false;
                _onCloseCallback();
            });
        }

        nana::form* GetNanaForm() { return &_nanaForm; }

        bool IsVisible() { return _isVisible; }

        bool Show() override {
            _nanaForm.show();
            _isVisible = true;
            return true;
        }

        bool Hide() override {
            _nanaForm.hide();
            _isVisible = false;
            return true;
        }

        bool Close() override {
            _nanaForm.close();
            _isVisible = false;
            return true;
        }

        bool SetTitle(const char* title) override {
            _nanaForm.caption(title);
            return true;
        }

        bool SetHeight(unsigned int height) override {
            _nanaForm.size({_nanaForm.size().width, height});
            return true;
        }

        bool SetWidth(unsigned int width) override {
            _nanaForm.size({width, _nanaForm.size().height});
            return true;
        }

        UITab* AddTab(const char* tabTitle) override {
            InitializeTabs();
            auto tab = std::make_unique<Tab>(&_nanaForm, &_nanaMainPlace, tabTitle);
            _nanaTabBar.push_back(tabTitle);
            _nanaMainPlace.field("tabPanels").fasten(*tab->GetNanaPanel());
            _tabs.push_back(std::move(tab));
            return _tabs.back().get();
        }

        UILabel* AddLabel(const char* text) override {
            auto* label = WidgetContainer::AddLabel(text);
            _nanaWindowWidgetsPlace.collocate();
            return label;
        }
        UITextbox* AddTextbox(const char* text) override {
            auto* textbox = WidgetContainer::AddTextbox(text);
            _nanaWindowWidgetsPlace.collocate();
            return textbox;
        }
        UIButton* AddButton(const char* text, void (*callback)(UIButton*)) override {
            auto* button = WidgetContainer::AddButton(text, callback);
            _nanaWindowWidgetsPlace.collocate();
            return button;
        }
    };

    class Application : public UIApplication {
        std::vector<std::unique_ptr<Window>> _windows;

        void OnClose() {
            bool anyWindowsAreVisible = false;
            for (auto& window : _windows) {
                if (window->IsVisible()) {
                    anyWindowsAreVisible = true;
                    break;
                }
            }
            if (!anyWindowsAreVisible) nana::API::exit();
        }

    public:
        void Run() override {
            nana::exec();
            _windows.clear();
            nana::API::exit_all();
        }

        UIWindow* NewWindow(const char* title) override {
            auto window = std::make_unique<Window>([this]() { OnClose(); });
            window->SetTitle(title);
            _windows.push_back(std::move(window));
            return _windows.back().get();
        }
    };

    class Toolkit : public UIToolkit {
        std::unique_ptr<Application> _application;

    public:
        UIApplication* GetApplication() override {
            if (!_application) _application = std::make_unique<Application>();
            return _application.get();
        }
    };
}
