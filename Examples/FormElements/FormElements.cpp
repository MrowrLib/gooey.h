#include "example_setup.h"

using namespace gooey;

int main() {
    UIApplication* app    = create_gooey_application();
    UIWindow*      window = app->add_window();
    window->set_title("Form Elements");
    window->show();
    window->set_background_color({0, 0, 255});

    auto* text_input1 = window->add_text_input();
    auto* text_input2 = window->add_text_input();
    auto* text_input3 = window->add_text_input();

    return app->run_blocking();
}
