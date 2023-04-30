#pragma once

#include "register.h"

// Include the default implementation first (has Gooey_GetAPI macro)
#include "default.h"

// Load GUI backend
#include "backends/Qt.h"

Gooey_RegisterToolkit(Qt, Gooey::Qt::Toolkit);
