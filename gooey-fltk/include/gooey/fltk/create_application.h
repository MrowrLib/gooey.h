#pragma once

#include "FLTKApplication.h"

namespace gooey {

    UIApplication* create_gooey_application() { return new fltk::FLTKApplication(); }
}