#pragma once

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_Pack.H>
#include <FL/Fl_RGB_Image.H>
#include <FL/Fl_Tabs.H>
#include <gooey.h>

#include <memory>
#include <vector>

#include "Button.h"
#include "Label.h"


namespace gooey::FLTKAdapter {

    class WidgetContainer : public UIWidgetContainer {
        Fl_Pack* _implPack;

        std::vector<std::unique_ptr<UIWidget>> _widgets;

    public:
        WidgetContainer() = default;
        explicit WidgetContainer(Fl_Pack* pack) : _implPack(pack) {}

        void SetImplFlPack(Fl_Pack* pack) { _implPack = pack; }

        UIWidget* AddWidget(std::unique_ptr<UIWidget> widget) {
            _widgets.push_back(std::move(widget));
            return _widgets.back().get();
        }

        UILabel* AddLabel(const char* text) override {
            auto label = std::make_unique<Label>(_implPack);
            label->SetText(text);
            return static_cast<UILabel*>(AddWidget(std::move(label)));
        }

        UIButton* AddButton(const char* text) override {
            auto button = std::make_unique<Button>(_implPack);
            button->SetText(text);
            return static_cast<UIButton*>(AddWidget(std::move(button)));
        }

        // UIImage* AddImage(const char* path) override {
        //     auto image = std::make_unique<Image>(_implPack);
        //     image->SetImage(path);
        //     return static_cast<UIImage*>(AddWidget(std::move(image)));
        // }
        // UIPanel* AddHorizontalPanel() override {
        //     auto panel = std::make_unique<Panel>(_implPack, true);
        //     return static_cast<UIPanel*>(AddWidget(std::move(panel)));
        // }
        // UIPanel* AddVerticalPanel() override {
        //     auto panel = std::make_unique<Panel>(_implPack, false);
        //     return static_cast<UIPanel*>(AddWidget(std::move(panel)));
        // }
        // UIGrid* AddGrid(unsigned int cols, unsigned int rows) override {
        //     auto grid = std::make_unique<Grid>(_implPack, cols, rows);
        //     return static_cast<UIGrid*>(AddWidget(std::move(grid)));
        // }
        // UITabs* AddTabs() override {
        //     auto tabs = std::make_unique<Tabs>(_implPack);
        //     return static_cast<UITabs*>(AddWidget(std::move(tabs)));
        // }
    };
}
