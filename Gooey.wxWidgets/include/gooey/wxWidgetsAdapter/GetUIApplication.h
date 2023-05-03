#pragma once

#include "Application.h"

namespace gooey {

    UIApplication* GetUIApplication() {
        static wxWidgetsAdapter::Application app;
        return &app;
    }
}
