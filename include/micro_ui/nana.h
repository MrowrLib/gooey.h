#pragma once

#include "register.h"

// Include the default implementation first (has MicroUI_GetAPI macro)
#include "default.h"

// Load GUI backend
#include "backends/Nana.h"

MicroUI_RegisterToolkit(Nana, MicroUI::Nana::Toolkit);
