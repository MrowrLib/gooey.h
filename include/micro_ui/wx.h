#pragma once

#include "register.h"

// Include the default implementation first (has MicroUI_GetAPI macro)
#include "default.h"

// Load GUI backend
#include "backends/wxWidgets.h"

MicroUI_RegisterToolkit(wxWidgets, MicroUI::wxWidgets::Toolkit);
