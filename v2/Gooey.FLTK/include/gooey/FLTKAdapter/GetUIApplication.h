#pragma once

#include "Application.h"

namespace gooey {

    UIApplication* GetUIApplication() {
        static FLTKAdapter::Application app;
        return &app;
    }
}
