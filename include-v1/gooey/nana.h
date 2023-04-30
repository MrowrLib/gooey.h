#pragma once

#include "register.h"

// Include the default implementation first (has Gooey_GetAPI macro)
#include "default.h"

// Load GUI backend
#include "backends/Nana.h"

Gooey_RegisterToolkit(Nana, Gooey::Nana::Toolkit);
