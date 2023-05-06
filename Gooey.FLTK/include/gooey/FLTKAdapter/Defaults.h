#pragma once

#include <gooey.h>

namespace gooey::FLTKAdapter::Impl {
    bool MonitorResizeEvents = true;
}

namespace gooey::FLTKAdapter::Defaults {
    unsigned int           ButtonWidth                = 100;
    unsigned int           ButtonHeight               = 20;
    unsigned int           LabelWidth                 = 100;
    unsigned int           LabelHeight                = 20;
    unsigned int           ImageWidth                 = 100;
    unsigned int           ImageHeight                = 100;
    unsigned int           PanelWidth                 = 300;
    unsigned int           PanelHeight                = 100;
    unsigned int           WindowWidth                = 400;
    unsigned int           WindowHeight               = 300;
    unsigned int           GridCellWidth              = 20;
    unsigned int           GridCellHeight             = 20;
    unsigned int           GridPadding                = 0;
    UIBackgroundImageStyle BackgroundImageStyle       = UIBackgroundImageStyle::Fill;
    UIHorizontalAlignment  DefaultHorizontalAlignment = UIHorizontalAlignment::Center;
    UIVerticalAlignment    DefaultVerticalAlignment   = UIVerticalAlignment::Center;
}
