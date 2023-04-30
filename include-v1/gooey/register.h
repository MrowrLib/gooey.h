#pragma once

#include <functional>

namespace Gooey::ToolkitRegistration::Private {
    class FunctionRunner {
        std::function<void()> _function;

    public:
        FunctionRunner(std::function<void()> function) : _function(function) { function(); }
    };
}

#define Gooey_RegisterToolkit(name, toolkitClassName)                                         \
    Gooey::ToolkitRegistration::Private::FunctionRunner __RegisterGooeyTookkit_##name([]() {  \
        Gooey_GetAPI()->GetToolkitRegistry()->RegisterToolkit(#name, new toolkitClassName()); \
    });
