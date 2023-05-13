#pragma once

#include <gooey.h>

#include "GooeyQtApplication.h"

namespace gooey {

    UIApplication* create_gooey_application() {
        //
        return new Qt::GooeyQtApplication();
    }
}