#pragma once

#include "RegisterToolkit.h"

// Include the default implementation first (has UserInterface_GetAPI macro)
#include "UserInterface/DefaultImplementation.h"

// Helper for UI apps:
#include "UserInterface/UI_Main.h"

// Load GUI backend
#include "UserInterface/Backends/Nana.h"

UserInterface_RegisterToolkit(Nana, UserInterface::Nana::Toolkit);
