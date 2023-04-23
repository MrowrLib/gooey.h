#pragma once

#include <functional>

namespace MicroUI::ToolkitRegistration::Private {
    class FunctionRunner {
        std::function<void()> _function;

    public:
        FunctionRunner(std::function<void()> function) : _function(function) { function(); }
    };
}

#define MicroUI_RegisterToolkit(name, toolkitClassName)                                          \
    MicroUI::ToolkitRegistration::Private::FunctionRunner __RegisterMicroUITookkit_##name([]() { \
        MicroUI_GetAPI()->GetToolkitRegistry()->RegisterToolkit(#name, new toolkitClassName());  \
    });
