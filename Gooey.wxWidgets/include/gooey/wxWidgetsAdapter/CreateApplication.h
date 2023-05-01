#pragma once

#include "Application.h"

namespace gooey {

    UIApplication* CreateApplication() { return new wxWidgetsAdapter::Application(); }
}
