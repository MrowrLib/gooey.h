#pragma once

#include <cstdint>
//

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Pack.H>
#include <gooey.h>

#include "Colors.h"
#include "WidgetContainer.h"

namespace gooey::FLTKAdapter {

    class Panel : public UIPanel, WidgetContainer {
        Fl_Group* _implGroup;
        Fl_Pack*  _implPack;

    public:
        Panel(Fl_Pack* pack, bool horizontal)
            : _implGroup(new Fl_Group(0, 0, DefaultSizes::PanelWidth, DefaultSizes::PanelHeight)) {
            _implGroup->box(FL_UP_BOX);
            _implPack = new Fl_Pack(0, 0, DefaultSizes::PanelWidth, DefaultSizes::PanelHeight);
            _implPack->type(horizontal ? Fl_Pack::HORIZONTAL : Fl_Pack::VERTICAL);
            _implPack->spacing(10);  // Remove me
            // _implPack->end();
            _implGroup->end();
            SetImplFlPack(_implPack);
        }

        GOOEY_FLTK_COLOR_SETTERS(_implGroup)

        UILabel*  AddLabel(const char* text) override { return WidgetContainer::AddLabel(text); }
        UIButton* AddButton(const char* text) override { return WidgetContainer::AddButton(text); }

        // UIPanel* AddHorizontalPanel() override {
        // UIPanel* AddVerticalPanel() override {
    };
}
