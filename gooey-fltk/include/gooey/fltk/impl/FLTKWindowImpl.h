#pragma once

#include <FL/Fl.H>
#include <FL/Fl_Pack.H>
#include <FL/Fl_Window.H>
#include <gooey/base_classes.h>

#include "FLTKAspectRatioGroup.h"
#include "FLTKAutoProportionalGroupImpl.h"
#include "FLTKBackgroundImageCollection.h"

namespace gooey::fltk::impl {

    class FLTKWindowImpl : public Fl_Window {
        FLTKBackgroundImageCollection        _backgroundImagesCollection;
        impl::FLTKAutoProportionalGroupImpl* _topLevelHorizontalGroup;
        impl::FLTKAutoProportionalGroupImpl* _secondLevelVerticalGroup;

    public:
        FLTKWindowImpl(int width, int height) : Fl_Window(width, height) {
            resizable(this);

            _topLevelHorizontalGroup =
                new impl::FLTKAutoProportionalGroupImpl(0, 0, width, height, true, false);
            _secondLevelVerticalGroup =
                new impl::FLTKAutoProportionalGroupImpl(0, 0, width, height, false, true);

            _topLevelHorizontalGroup->add(_secondLevelVerticalGroup);
            _topLevelHorizontalGroup->end();

            resizable(_topLevelHorizontalGroup);
            end();
        }

        impl::FLTKAutoProportionalGroupImpl* get_group() { return _secondLevelVerticalGroup; }

        bool AddBackgroundImage(const std::string& imagePath) {
            return _backgroundImagesCollection.AddImage(imagePath);
        }

        bool RemoveBackgroundImage(const std::string& imagePath) {
            return _backgroundImagesCollection.RemoveImage(imagePath);
        }

        // void draw() override {
        //     Fl_Window::draw();
        //     _backgroundImagesCollection.DrawAll(x(), y(), w(), h());
        // }
    };
}